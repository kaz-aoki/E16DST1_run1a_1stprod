#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1.hh"
#include "E16DST_Constant.hh"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGConstant.hh"

int E16DST_DST1LGFactory(E16DST_DST0Detector<E16DST_DST0LGHit>& hits0, E16DST_DST1Detector<E16DST_DST1LGHit, E16DST_DST1LGCluster>* lg1) {
  auto& hits1 = lg1->Hits();
  auto& clusters1 = lg1->Clusters();

//  E16ANA_CalibDBManager& calib = E16ANA_CalibDBManager::Instance();
//  int run_id = 2255;
//  char* file_name = calib.CalibFileName("SSD-pedestal", run_id);
//  std::cout << file_name << std::endl;


//  static E16ANA_LGBasic *lgbasic = new E16ANA_LGBasic;
  static E16ANA_LGBasic lgbasic;
  static bool is_first=true;
  if(is_first){
    lgbasic.MakeMap();//read calib_files
    lgbasic.SetMap();//make channel_map
    is_first=false;
  }

  auto hit1 = new E16DST_DST1LGHit();
  //  auto cluster1 = new E16DST_DST1LGClusters();
  auto max_hit = hits0.NumberOfHits();
  hits1->Reserve(max_hit);
  //  clusters1->Reserve(max_hit);

  for (int n_hit = 0; n_hit < hits0.NumberOfHits(); ++n_hit) {//dst0hit loop
    hit1->SetInvalid();
    //    cluster1->SetInvalid();
    auto hit0 = hits0.Hit(n_hit);
    hit1->SetIds(hit0.ModuleID(), hit0.BlockID());
    //    cluster1->SetModuleId(hit0.ModuleID());

    auto spec = lgbasic.GetSpec(hit0.ModuleID(),hit0.BlockID());
    double wftype = spec->WF_TYPE;//relative gain of DRS4module
    float waveform[E16DST_Constant::NSamplesLG] = {E16DST_DST1Constant::kInvalidValue};
    float peakheight = E16DST_DST1Constant::kInvalidValue;
    int peaktime = E16DST_DST1Constant::kInvalidValue;
    float timing = E16DST_DST1Constant::kInvalidValue;
    float baseline = E16DST_DST1Constant::kInvalidValue;
    float baselinerms = E16DST_DST1Constant::kInvalidValue;
    float integral = E16DST_DST1Constant::kInvalidValue;
    float falltime = E16DST_DST1Constant::kInvalidValue;


    for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
      int ph = hit0.Waveform()[cell];
      waveform[cell] = ph*wftype;
    }

    lgbasic.LGWFPeak(waveform, &peakheight, &peaktime, &timing);
    lgbasic.LGWFBaseline(waveform, peaktime, &baseline, &baselinerms);
    lgbasic.LGWFIntegral(waveform, peaktime, baseline, &integral, &falltime);

    if( (falltime-peaktime)>5 && peakheight>E16ANA_LGConstant::kHitThreshold && E16ANA_LGConstant::kHitTimingStart<timing && timing<E16ANA_LGConstant::kHitTimingEnd){
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
