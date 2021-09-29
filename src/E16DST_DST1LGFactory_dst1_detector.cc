#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1.hh"
#include "E16DST_Constant.hh"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGConstant.hh"

int E16DST_DST1LGFactoryDST1Detector(E16DST_DST0Detector<E16DST_DST0LGHit>& hits0, E16DST_DST1Detector<E16DST_DST1LGHit, E16DST_DST1LGCluster>* lg) {
  auto hits1     = &lg->Hits();
  auto clusters1 = &lg->Clusters();

  static E16ANA_LGBasic lgbasic;
  static bool is_first=true;
  if(is_first){
    //lgbasic.MakeMap();//read calib_files and make a binary file
    lgbasic.SetMap();//make channel_map from binary file
    is_first=false;
  }

  //  auto hit1 = new E16DST_DST1LGHit();
  //  auto cluster1 = new E16DST_DST1LGClusters();
  auto max_hit = hits0.NumberOfHits();
  //  hits1->Reserve(max_hit);
  hits1->resize(max_hit);
  //  clusters1->Reserve(max_hit);

  int n_dst1hit = 0;
  for (int n_hit = 0; n_hit < hits0.NumberOfHits(); ++n_hit) {//dst0hit loop
    //    hit1->SetInvalid();
    //    cluster1->SetInvalid();
    auto hit0 = hits0.Hit(n_hit);
    //    hit1->SetIds(hit0.ModuleID(), hit0.BlockID());
    //    cluster1->SetModuleId(hit0.ModuleID());

    auto spec = lgbasic.GetSpec(hit0.ModuleID(),hit0.BlockID());
    double wftype = spec->WF_TYPE;//relative gain of DRS4module
    double waveform[E16DST_Constant::NSamplesLG] = {E16DST_DST1Constant::kInvalidValue};
    double peakheight = E16DST_DST1Constant::kInvalidValue;
    int peaktime = E16DST_DST1Constant::kInvalidValue;
    double timing = E16DST_DST1Constant::kInvalidValue;
    double baseline = E16DST_DST1Constant::kInvalidValue;
    double baselinerms = E16DST_DST1Constant::kInvalidValue;
    double integral = E16DST_DST1Constant::kInvalidValue;
    int falltime = E16DST_DST1Constant::kInvalidValue;
    int npeaks = E16DST_DST1Constant::kInvalidValue;
    double xpos[20] = {E16DST_DST1Constant::kInvalidValue};
    double ypos[20] = {E16DST_DST1Constant::kInvalidValue};

    for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
      int ph = hit0.Waveform()[cell];
      waveform[cell] = ph*wftype;
    }

    lgbasic.LGWFPeak(waveform, &peakheight, &peaktime, &timing);
    lgbasic.LGWFBaseline(waveform, peaktime, &baseline, &baselinerms);
    peakheight = peakheight - baseline;
    lgbasic.LGWFIntegral(waveform, peaktime, baseline, &integral, &falltime);
    npeaks = lgbasic.LGWFPeakSearch(waveform, xpos, ypos);

    if( (falltime-peaktime)>5 && //to remove spike noise
	peakheight>E16ANA_LGConstant::kHitThreshold && 
	timing>E16ANA_LGConstant::kHitTimingStart && 
	timing<E16ANA_LGConstant::kHitTimingEnd ){
      hits1->at(n_dst1hit).SetInvalid();
      hits1->at(n_dst1hit).SetIds(hit0.ModuleID(), hit0.BlockID());
      hits1->at(n_dst1hit).SetTiming((float)timing);
      hits1->at(n_dst1hit).SetPeakHeight((float)peakheight);
      hits1->at(n_dst1hit).SetPeakTime(peaktime);
      hits1->at(n_dst1hit).SetBaseline((float)baseline);
      hits1->at(n_dst1hit).SetBaselineRms((float)baselinerms);
      hits1->at(n_dst1hit).SetIntegral((float)integral);
      hits1->at(n_dst1hit).SetNpeaks((int)npeaks);

      //      cluster1->SetMaxPeakCh(hit0.BlockID());
      //      cluster1->SetMaxPeakHeight(peakheight);
      //      cluster1->SetTiming(timing);
      //      cluster1->SetMaxPeakSum(peakheight);
      n_dst1hit++;
    }

  }//dst0hit loop

  hits1->resize(n_dst1hit);

//  return hits1->GetEventSize();
  return 1;

}
