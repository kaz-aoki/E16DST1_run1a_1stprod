#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1.hh"
#include "E16DST_Constant.hh"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGConstant.hh"
#include "E16ANA_LGWaveform.hh"
#include "E16ANA_LGDeadChannel.hh"

int E16DST_DST1LGFactory(E16DST_DST0Detector<E16DST_DST0LGHit>& hits0, E16DST_DST0Detector<E16DST_DST1LGHit>* hits1, E16DST_DST0Detector<E16DST_DST1LGCluster>* clusters1, int fitoption ) {

  static E16ANA_LGBasic lgbasic;
  static E16ANA_LGDeadChannel lgdead;
  static bool is_first=true;
  if(is_first){
    lgbasic.SetMap();
    lgbasic.SetCalibMap();
    lgbasic.SetTemplate();
    lgdead.ReadDeadChannelData();
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
    int status = lgdead.Status(hit0.ModuleID(),hit0.BlockID());
    if( status!=0 ){
      //std::cout<<"Dead Channel Status: "<<hit0.ModuleID()<<" "<<hit0.BlockID()<<" "<<status<<std::endl;
      continue;
    }

    double waveform[E16DST_Constant::NSamplesLG] = {E16DST_DST1Constant::kInvalidValue};
    for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
      int ph = hit0.Waveform()[cell];
      waveform[cell] = ph*wftype;
    }

    E16ANA_LGWaveform* lgwf = new E16ANA_LGWaveform();
    if(fitoption==0){
      lgwf->SimpleMethod(waveform); // 700 event/sec @1e10
    }
    else if(fitoption==1){
      lgwf->FitMethod(waveform,t0); // 14 event/sec @1e10
    }
    else{
      std::cout<<fitoption<<" is Invalid FitOption"<<std::endl;
      delete lgwf;
      exit(1);
    }


    int hitflag = lgwf->GetHitFlag();

    /*
    if( hitflag==0 ){ // applied in MethodForTrack
      //std::cout<<"no hit for track"<<std::endl;
      delete lgwf;
      continue;
    }
    */

    int fitflag = lgwf->GetFitOK();
    int npsfit = lgwf->GetNpsFit();
    bool spikeflag = lgwf->GetSpikeFlag();

    if( fitflag==0&&npsfit==0 ){ // applied in FitMethod
      //std::cout<<"no hit"<<std::endl;
      delete lgwf;
      continue;
    }
    if( fitflag==0&&npsfit==1&&spikeflag==true ){ // applied in FitMethod
      //std::cout<<"it is spike noise"<<std::endl;
      delete lgwf;
      continue;
    }

    double timing = lgwf->GetTiming();
    double peakheight = lgwf->GetPeak();
    double peaktime = lgwf->GetPeakx();
    double baseline = lgwf->GetBaseline();
    double baselinerms = lgwf->GetBaselineRms();
    double integral = lgwf->GetIntegral();
    double falltime = lgwf->GetFalltime();

    int npeaks = lgwf->GetNpeaks();
    int npeak = 0;
    for(int l=0;l<npeaks;l++){//npeaks loop
      double fitpeak = lgwf->GetPeaks()[l];
      double fitpeaktime = lgwf->GetPeakxs()[l];
































      double fittiming = lgwf->GetTimings()[l];
      double fitwidth = lgwf->GetWidths()[l];
      double fitchi2 = lgwf->GetChi2s()[l];

      //if( (falltime-peaktime)>5 && //to remove spike noise
      //peakheight>E16ANA_LGConstant::kHitThreshold && 
      if( peaktime>E16ANA_LGConstant::kHitTimeStart && 
	peaktime<E16ANA_LGConstant::kHitTimeEnd && timing>-100 ){//dst1hit condition

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

      }//dst1hit conidition

    }//npeaks loop

    delete lgwf;

  }//dst0hit loop

  hits1->Resize(n_dst1hit);

  return hits1->GetEventSize();

}
