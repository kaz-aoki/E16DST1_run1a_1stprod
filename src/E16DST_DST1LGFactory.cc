#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1.hh"
#include "E16DST_Constant.hh"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGConstant.hh"
#include "E16ANA_LGWaveform.hh"

int E16DST_DST1LGFactory(E16DST_DST0Detector<E16DST_DST0LGHit>& hits0, E16DST_DST0Detector<E16DST_DST1LGHit>* hits1, E16DST_DST0Detector<E16DST_DST1LGCluster>* clusters1) {

  static E16ANA_LGBasic lgbasic;
  //  static E16ANA_LGWaveform lgwf;
  static bool is_first=true;
  if(is_first){
    lgbasic.SetMap();//make channel_map from binary file
    lgbasic.SetCalibMap();
    lgbasic.SetTemplate();
    is_first=false;
  }

  //  auto hit1 = new E16DST_DST1LGHit();
  //  auto cluster1 = new E16DST_DST1LGClusters();
  auto max_hit = hits0.NumberOfHits();
  //  hits1->Reserve(max_hit);
  hits1->Resize(max_hit*2);
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
    double t0 = lgbasic.GetT0(hit0.ModuleID(),hit0.BlockID());
    double waveform[E16DST_Constant::NSamplesLG] = {E16DST_DST1Constant::kInvalidValue};
    /*
    double mwf[E16DST_Constant::NSamplesLG] = {E16DST_DST1Constant::kInvalidValue};//modified waveform
    double peakheight = E16DST_DST1Constant::kInvalidValue;
    int peaktime = E16DST_DST1Constant::kInvalidValue;
    double timing = E16DST_DST1Constant::kInvalidValue;
    double baseline = E16DST_DST1Constant::kInvalidValue;
    double baselinerms = E16DST_DST1Constant::kInvalidValue;
    double integral = E16DST_DST1Constant::kInvalidValue;
    int falltime = E16DST_DST1Constant::kInvalidValue;
    int npeaks = E16DST_DST1Constant::kInvalidValue;
    double peakxs[20] = {E16DST_DST1Constant::kInvalidValue};
    double peakys[20] = {E16DST_DST1Constant::kInvalidValue};
    */
    for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
      int ph = hit0.Waveform()[cell];
      waveform[cell] = ph*wftype;
    }
    /*
    lgwf.Peak(waveform, &peakheight, &peaktime, &timing);
    lgwf.Baseline(waveform, peaktime, &baseline, &baselinerms);
    peakheight = peakheight - baseline;
    lgwf.Integral(waveform, peaktime, baseline, &integral, &falltime);
    npeaks = lgwf.PeakSearch(waveform, t0, mwf, peakxs, peakys); fifna
    lgwf.Fit(waveform, mwf, npeaks, peakxs, peakys);
    lgwf.FitMethod(waveform,t0);
    */
    E16ANA_LGWaveform* lgwf = new E16ANA_LGWaveform();
    //lgwf->SimpleMethod(waveform);
    lgwf->FitMethod(waveform,t0);
    double timing = lgwf->GetTiming();
    double peakheight = lgwf->GetPeak();
    double peaktime = lgwf->GetPeakx();
    double baseline = lgwf->GetBaseline();
    double baselinerms = lgwf->GetBaselineRms();
    double integral = lgwf->GetIntegral();
    double falltime = lgwf->GetFalltime();
    int npeaks = lgwf->GetNpeaks();
    int npeak = 0;
    for(int l=0;l<npeaks;l++){
      //int npsfit = lgwf->GetNpsFit();
      int fitflag = lgwf->GetFitOK();
      double fitpeak = lgwf->GetPeaks()[l];
      float fitpeaktime = lgwf->GetPeakxs()[l];
      double fittiming = lgwf->GetTimings()[l];
      double fitwidth = lgwf->GetWidths()[l];
      double fitchi2 = lgwf->GetChi2s()[l];

      //if( (falltime-peaktime)>5 && //to remove spike noise
      //peakheight>E16ANA_LGConstant::kHitThreshold && 
      //timing>E16ANA_LGConstant::kHitTimingStart && 
      //timing<E16ANA_LGConstant::kHitTimingEnd ){
      hits1->Hit(n_dst1hit).SetInvalid();
      hits1->Hit(n_dst1hit).SetIds(hit0.ModuleID(), hit0.BlockID());

      hits1->Hit(n_dst1hit).SetTiming((float)timing);
      hits1->Hit(n_dst1hit).SetPeakHeight((float)peakheight);
      hits1->Hit(n_dst1hit).SetPeakTime(peaktime);
      hits1->Hit(n_dst1hit).SetBaseline((float)baseline);
      hits1->Hit(n_dst1hit).SetBaselineRms((float)baselinerms);
      hits1->Hit(n_dst1hit).SetIntegral((float)integral);
      //hits1->Hit(n_dst1hit).SetNpeaks((int)npsfit);
      hits1->Hit(n_dst1hit).SetNpeaks((int)npeaks);
      hits1->Hit(n_dst1hit).SetNpeak((int)npeak);
      hits1->Hit(n_dst1hit).SetFitFlag((int)fitflag);
      hits1->Hit(n_dst1hit).SetFitPeak((float)fitpeak);
      hits1->Hit(n_dst1hit).SetFitPeakTime((float)fitpeaktime);
      hits1->Hit(n_dst1hit).SetFitTiming((float)fittiming);
      hits1->Hit(n_dst1hit).SetFitWidth((float)fitwidth);
      hits1->Hit(n_dst1hit).SetFitChi2((float)fitchi2);
      //      cluster1->SetMaxPeakCh(hit0.BlockID());
      //      cluster1->SetMaxPeakHeight(peakheight);
      //      cluster1->SetTiming(timing);
      //      cluster1->SetMaxPeakSum(peakheight);
      npeak++;
      n_dst1hit++;
      //}dst1hit condition
    }
    delete lgwf;


  }//dst0hit loop

  hits1->Resize(n_dst1hit);

  return hits1->GetEventSize();

}
