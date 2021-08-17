//#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1.hh"
#include "E16DST_Constant.hh"
#include "E16ANA_LGBasic.hh"

int E16DST_DST1LGFactory(E16DST_DST0Detector<E16DST_DST0LGHit>& hits0, E16DST_DST0Detector<E16DST_DST1LGHit>* hits1, E16DST_DST0Detector<E16DST_DST1LGCluster>* clusters1) {
//  E16ANA_CalibDBManager& calib = E16ANA_CalibDBManager::Instance();
//  int run_id = 2255;
//  char* file_name = calib.CalibFileName("SSD-pedestal", run_id);
//  std::cout << file_name << std::endl;


//  static E16ANA_LGBasic *lgbasic = new E16ANA_LGBasic;
  static E16ANA_LGBasic lgbasic;
  bool is_first=true;
  if(is_first){
    lgbasic.MakeMap();//read calib_files
    lgbasic.SetMap();//make channel_map
    is_first=false;
  }

  auto hit1 = new E16DST_DST1LGHit();
  //  auto cluster1 = new E16DST_DST1LGClusters();//cluster_temporary
  auto max_hit = hits0.NumberOfHits();
  hits1->Reserve(max_hit);
  //  clusters1->Reserve(max_hit);//cluster_temporary

  int ps = E16DST_DST1Constant::kLgPeakSearchStart;
  int pe = E16DST_DST1Constant::kLgPeakSearchEnd;
  int tr = E16DST_DST1Constant::kLgTimingSearchRegion;
  int bs = E16DST_DST1Constant::kLgBaselineStart;
  int be = E16DST_DST1Constant::kLgBaselineEnd;
  int is = E16DST_DST1Constant::kLgIntegralStart;
  int ie = E16DST_DST1Constant::kLgIntegralEnd;

  for (int n_hit = 0; n_hit < hits0.NumberOfHits(); ++n_hit) {//dst0hit loop
    hit1->SetInvalid();
    //    cluster1->SetInvalid();//cluster_temporary
    auto hit0 = hits0.Hit(n_hit);
    hit1->SetIds(hit0.ModuleID(), hit0.BlockID());
    //    cluster1->SetModuleId(hit0.ModuleID());//cluster_temporary

    auto spec = lgbasic.GetSpec(hit0.ModuleID(),hit0.BlockID());
    double wftype = spec->WF_TYPE;
    float waveform[E16DST_Constant::NSamplesLG] = {E16DST_DST1Constant::kInvalidValue};
    float peakheight = E16DST_DST1Constant::kInvalidValue;
    int peaktime = E16DST_DST1Constant::kInvalidValue;
    float timing = E16DST_DST1Constant::kInvalidValue;
    float baseline = E16DST_DST1Constant::kInvalidValue;
    float baseline_sum = 0.;
    float baseline_sq_sum = 0.;
    float baselinerms = E16DST_DST1Constant::kInvalidValue;
    float integral_sum = 0.;
    float integral = E16DST_DST1Constant::kInvalidValue;
    float falltime = E16DST_DST1Constant::kInvalidValue;

    for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){//peak search
      int ph = hit0.Waveform()[cell];
      waveform[cell] = ph*wftype;
      if(waveform[cell]>peakheight){
	if(ps<cell&&cell<pe){
	  peakheight = waveform[cell];
	  peaktime = cell;
	}
      }
    }//peak search
    //std::cout<<"peakheight:"<<peakheight<<std::endl;
    //std::cout<<"peaktime:"<<peaktime<<std::endl;

    for(int i=0;i<tr;i++){//timing search
      int cell = peaktime-i;
      float peakhalf = peakheight/2.;
      if(cell<0||cell>E16DST_Constant::NSamplesLG){
	timing=E16DST_DST1Constant::kInvalidValue;
	break;
      }
      if(waveform[cell]>peakheight){
	timing=E16DST_DST1Constant::kInvalidValue;
	break;
      }
      if(!(cell==peaktime)&&waveform[cell]<peakhalf){
	timing=(peakhalf-waveform[cell])*(1./E16DST_DST1Constant::kLgTimeScale)/(waveform[cell-1]-waveform[cell])+cell;
	break;
      }
    }//timing search
    //std::cout<<"timing:"<<timing<<std::endl;

    for(int cell=(peaktime+bs);cell<(peaktime+be);cell++){//baseline calculation
      baseline_sum += waveform[cell];
      baseline_sq_sum += waveform[cell]*waveform[cell];
    }
    baseline = baseline_sum/(float)(be-bs);
    baselinerms = sqrt( baseline_sq_sum/(float)(be-bs) - baseline*baseline );
    //std::cout<<"baseline:"<<baseline<<std::endl;
    //std::cout<<"baselinerms:"<<baselinerms<<std::endl;
    //baseline calculation

    //integral calculation
    bool peakcheck = false;
    int fallcount = 0;
    for(int cell=(peaktime+is);cell<(peaktime+ie);cell++){
      if(cell<0||cell>E16DST_Constant::NSamplesLG){
	integral_sum = E16DST_DST1Constant::kInvalidValue;
	break;
      }
      integral_sum += waveform[cell]-baseline;
      if((waveform[cell]-baseline)<(waveform[peaktime]-baseline)*0.1&&peakcheck==false&&cell>peaktime){
	if(fallcount>1){
	  std::cout<<"FalltimeSearch is failed."<<std::endl;
	  continue;
	}
	falltime = cell;
	fallcount += 1;
	if(fallcount>1){
	  peakcheck=true;
	}
      }
    }
    integral = integral_sum;
    //std::cout<<"integral:"<<integral<<std::endl;
    //integral calculation

    if((falltime-peaktime)>5&&peakheight>E16DST_DST1Constant::kLgHitThreshold&&E16DST_DST1Constant::kLgHitTimingStart<timing&&timing<E16DST_DST1Constant::kLgHitTimingEnd){
      //std::cout<<timing<<" "<<peakheight<<" "<<peaktime<<" "<<baseline<<" "<<baselinerms<<" "<<integral<<std::endl;
      hit1->SetTiming(timing);
      hit1->SetPeakHeight(peakheight);
      hit1->SetPeakTime(peaktime);
      hit1->SetBaseline(baseline);
      hit1->SetBaselineRms(baselinerms);
      hit1->SetIntegral(integral);
      hits1->PushBack(*hit1);
      //      cluster1->SetMaxPeakCh(hit0.BlockID());//cluster_temporary
      //      cluster1->SetMaxPeakHeight(peakheight);//cluster_temporary
      //      cluster1->SetTiming(timing);//cluster_temporary
      //      cluster1->SetMaxPeakSum(peakheight);//cluster_temporary
    }

  }//dst0hit loop

  return hits1->GetEventSize();

}
