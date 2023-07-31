#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1.hh"
#include "E16DST_Constant.hh"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGConstant.hh"
#include "E16ANA_LGWaveform.hh"
#include "E16ANA_LGDeadChannel.hh"
#include "E16ANA_LGClustering.hh"
#include "E16DST_DST1DefaultFilePath.hh"

#define REMOVE_SPIKE

int E16DST_DST1LGFactory(E16DST_DST0Detector<E16DST_DST0LGHit>& hits0, E16DST_DST1Detector<E16DST_DST1LGHit, E16DST_DST1LGCluster>* lg1, int fitoption, E16ANA_GeometryV2* geometry ) {

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

  //auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));

  auto& hits1 = lg1->Hits();
  auto max_hit = hits0.NumberOfHits();
  hits1.resize(max_hit*2);

  int n_dst1hit = 0;
  for (int n_hit = 0; n_hit < hits0.NumberOfHits(); ++n_hit) {//dst0hit loop
    auto hit0 = hits0.Hit(n_hit);

    auto spec = lgbasic.GetSpec(hit0.ModuleID(),hit0.BlockID());
    double wftype = spec->WF_TYPE;//relative gain of DRS4module
    //std::cout<<"WFTYPE:"<<wftype<<std::endl;
    double t0 = lgbasic.GetT0(hit0.ModuleID(),hit0.BlockID());
    int status = lgdead.Status(hit0.ModuleID(),hit0.BlockID());
    if( status!=0 ){
      //std::cout<<"Dead Channel Status: "<<hit0.ModuleID()<<" "<<hit0.BlockID()<<" "<<status<<std::endl;
      continue;
    }

    double waveform[E16DST_Constant::NSamplesLG] = {E16DST_DST1Constant::kInvalidValue};
#ifdef REMOVE_SPIKE
    for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
      int ph = hit0.Waveform()[cell];
      waveform[cell] = ph;
    }
    E16ANA_LGWaveform::RemoveSpike(waveform);
    for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
      waveform[cell] = waveform[cell]*wftype;
    }
#else
    for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
      int ph = hit0.Waveform()[cell];
      waveform[cell] = ph*wftype;
    }
#endif

    E16ANA_LGWaveform* lgwf = new E16ANA_LGWaveform();
    if(fitoption==0){
      lgwf->SimpleMethod(waveform); // 700 event/sec @1e10
    }
    else if(fitoption==1){
      lgwf->FitMethod(waveform,t0); // 14 event/sec @1e10
    }
    else if(fitoption==2){
      lgwf->woFitMethod(waveform,t0);
    }
    else{
      std::cout<<fitoption<<" is Invalid FitOption"<<std::endl;
      delete lgwf;
      exit(1);
    }

    int fitflag = lgwf->GetFitOK();
    int npsfit = lgwf->GetNpsFit();
    bool spikeflag = lgwf->GetSpikeFlag();
    //std::cout<<fitflag<<" "<<npsfit<<" "<<spikeflag<<std::endl;

    double timing = lgwf->GetTiming();
    double peakheight = lgwf->GetPeak();
    double peaktime = lgwf->GetPeakx();
    double baseline = lgwf->GetBaseline();
    double baselinerms = lgwf->GetBaselineRms();
    double integral = lgwf->GetIntegral();
    double falltime = lgwf->GetFalltime();

    bool isHitOp0 = true;
    bool isHitOp1 = true;
    if( peakheight<E16ANA_LGConstant::kHitThreshold || spikeflag==true || timing<70. || timing>130. ){
      isHitOp0 = false;
    }
    if( isHitOp0==false && fitoption==0 ){
      delete lgwf;
      continue;
    }
    if( fitflag==0 && (npsfit==0||(npsfit==1&&spikeflag==true)) ){
      isHitOp1 = false;
    }

    if(isHitOp0==false&&isHitOp1==false){
      delete lgwf;
      continue;
    }

    int npeaks = lgwf->GetNpeaks();
    int npeak = 0;
    for(int l=0;l<npeaks;l++){//npeaks loop
      double fitpeak = lgwf->GetPeaks()[l];
      double fitpeaktime = lgwf->GetPeakxs()[l];
      double fittiming = lgwf->GetTimings()[l];
      double fitwidth = lgwf->GetWidths()[l];
      double fitchi2 = lgwf->GetChi2s()[l];

      hits1[n_dst1hit].SetInvalid();
      hits1[n_dst1hit].SetIds(hit0.ModuleID(), hit0.BlockID());
      hits1[n_dst1hit].SetHitId(n_hit);

      if(isHitOp1==true){
	hits1[n_dst1hit].SetNpeaks((int)npeaks);
	hits1[n_dst1hit].SetNpeak((int)npeak);
	hits1[n_dst1hit].SetFitFlag((int)fitflag);
	hits1[n_dst1hit].SetFitPeak((float)fitpeak);
	hits1[n_dst1hit].SetFitPeakTime((float)fitpeaktime);
	hits1[n_dst1hit].SetFitTiming((float)fittiming);
	hits1[n_dst1hit].SetFitWidth((float)fitwidth);
	hits1[n_dst1hit].SetFitChi2((float)fitchi2);
      }
      else{
	hits1[n_dst1hit].SetNpeaks(1);
	hits1[n_dst1hit].SetNpeak((int)npeak);
	hits1[n_dst1hit].SetFitFlag(3);
	hits1[n_dst1hit].SetFitPeak((float)peakheight);
	hits1[n_dst1hit].SetFitPeakTime((float)peaktime);
	hits1[n_dst1hit].SetFitTiming((float)(timing+100.-lgbasic.GetT0(hit0.ModuleID(), hit0.BlockID())));
	hits1[n_dst1hit].SetFitWidth((float)E16DST_DST1Constant::kInvalidValue);
	hits1[n_dst1hit].SetFitChi2((float)E16DST_DST1Constant::kInvalidValue);
      }

      if(isHitOp0==true&&npeak==0){
	hits1[n_dst1hit].SetTiming((float)timing);
	hits1[n_dst1hit].SetPeakHeight((float)peakheight);
	hits1[n_dst1hit].SetPeakTime((int)peaktime);
	hits1[n_dst1hit].SetBaseline((float)baseline);
	hits1[n_dst1hit].SetBaselineRms((float)baselinerms);
	hits1[n_dst1hit].SetIntegral((float)integral);
      }
      else{
	hits1[n_dst1hit].SetTiming((float)E16DST_DST1Constant::kInvalidValue);
	hits1[n_dst1hit].SetPeakHeight((float)E16DST_DST1Constant::kInvalidValue);
	hits1[n_dst1hit].SetPeakTime((int)E16DST_DST1Constant::kInvalidValue);
	hits1[n_dst1hit].SetBaseline((float)E16DST_DST1Constant::kInvalidValue);
	hits1[n_dst1hit].SetBaselineRms((float)E16DST_DST1Constant::kInvalidValue);
	hits1[n_dst1hit].SetIntegral((float)E16DST_DST1Constant::kInvalidValue);
      }
      npeak++;
      n_dst1hit++;

    }//npeaks loop

    delete lgwf;

  }//dst0hit loop

  hits1.resize(n_dst1hit);


  E16ANA_LGClustering lgclustering;
  int nhits=0;
  for (int idst1hit = 0; idst1hit < n_dst1hit; idst1hit++) {//dst1hit loop
    auto& dst1hit = hits1[idst1hit];
    if(dst1hit.FitFlag()<2){
      lgclustering.SetHitData( 
      	dst1hit.HitId(),
      	dst1hit.ModuleId(),
      	dst1hit.ChannelId(),
      	dst1hit.FitPeak(),
      	dst1hit.FitTiming(),
      	dst1hit.Integral(),
      	dst1hit.LocalPos(*geometry).X(),
      	dst1hit.LocalPos(*geometry).Y(),
      	dst1hit.LocalPos(*geometry).Z());
      nhits++;
      // std::cout<<dst1hit.HitId()<<" "<<dst1hit.ModuleId()<<" "<<dst1hit.ChannelId()<<" "<<dst1hit.FitPeak()<<" "<<dst1hit.FitTiming()<<" "<<dst1hit.Integral()<<" "<<dst1hit.LocalPos(*geometry).X()<<" "<<dst1hit.LocalPos(*geometry).Y()<<std::endl;
    }
  }//dst1hit loop
  // std::cout<<"***"<<nhits<<std::endl;

  lgclustering.Clustering();
  // lgclustering.ClusteringXY();

  auto& clusters1 = lg1->Clusters();
  auto max_cluster = lgclustering.LGClusterSize();
  clusters1.resize(max_cluster);
  for(int icluster=0;icluster<max_cluster;icluster++){
    E16ANA_LGClustering::lgcluster cith = lgclustering.LGClusterIth(icluster);
    clusters1[icluster].SetClusterId(icluster);
    clusters1[icluster].SetModuleId(cith.mid);
    clusters1[icluster].SetMaxPeakCh(cith.maxcid);
    clusters1[icluster].SetMaxPeakHeight(cith.maxpeak);
    clusters1[icluster].SetTiming(cith.fasttiming);
    clusters1[icluster].SetPeakSum(cith.peaksum);
    clusters1[icluster].SetHitOrders(cith.hids);
    clusters1[icluster].SetTimeDifference(cith.timediff);
    clusters1[icluster].SetLocalx(cith.lx);
    clusters1[icluster].SetLocaly(cith.ly);
    clusters1[icluster].SetLocalz(cith.lz);
     // std::cout<<cith.hids.size()<<" "<<icluster<<" "<<cith.mid<<" "<<cith.peaksum<<" "<<cith.fasttiming<<" "<<cith.timediff<<" "<<cith.intsum<<" "<<cith.maxcid<<" "<<cith.maxpeak<<" "<<cith.lx<<" "<<cith.ly<<"CLUSTER"<<std::endl;
  }
  // std::cout<<"****"<<max_cluster<<std::endl;
  clusters1.resize(max_cluster);

//  return hits1.GetEventSize();
  return 1;

}
