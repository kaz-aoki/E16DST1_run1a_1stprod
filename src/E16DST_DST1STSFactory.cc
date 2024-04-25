#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1SSDAnalyzerMaker.hh"
#include "OnlineGTRUtility.h"
#include "E16ANA_SSDcalib.hh"
#include "E16ANA_ErrorMessage.hh"
#include <TCanvas.h>
#include <TGraph.h>
#include <TF1.h>
#include <TText.h>
#include <TRandom.h>

#include "STS/E16ANA_STSGeometry.hh"
#include "STS/E16ANA_STSGlobalGeometry.hh"

using namespace std;

//#define STS_MODULE_RAND


int E16DST_DST1STSFactory(E16DST_DST0Detector<E16DST_DST0STSGlobal>& stsg_dst0,
			  E16DST_DST0Detector<E16DST_DST0STSHit>& sts_dst0,
			  E16DST_DST1Detector<E16DST_DST1STSHit, E16DST_DST1STSCluster>* sts_dst1) {
  //std::cout << "DST1STSFactory." << std::endl;

  //auto& hitsg0 = sts_dst0.Hits();
#ifdef STS_MODULE_RAND
  static TRandom rnd;
  auto get_module_rnd = []() {
    // 101-109
    int mod = (int)(rnd.Rndm()*7.9999999999999);
    int m[]={101,102,103,104,106,107,108,109};    
    return m[mod];
  };
  std::cout << "WARNING!!!! Module ID intentionally randomized for debugging purpose." << std::endl;
#endif
  if ( stsg_dst0.NumberOfHits() > 1 ) {
    std::cout << "STS Global has more than 1 entries. DST0 of STSs are merged." << std::endl;
  }
  if ( stsg_dst0.NumberOfHits() == 0 ) return 0;

  auto& hitg0 = stsg_dst0.Hit(0);
  std::map<int,int> hitgmap;
  static bool first = true;
  for ( int i = 0 ; i < stsg_dst0.NumberOfHits() ; i ++ ) {
    hitgmap[stsg_dst0.Hit(i).get_e16sts()] = i;
    if ( first ) {
      std::cout << "hitgmap: e16sts=" << stsg_dst0.Hit(i).get_e16sts() << " --> stsg_dst0[" << i << "]" << std::endl;
    }
  }
  if ( first ) first = false;

  auto& hits1 = sts_dst1->Hits(); // hits1 is std::vector<T>
  hits1.clear();
  constexpr uint64_t bitmask_emu = (1<<14) - 1;
  int emu_timestamp = hitg0.get_emu_timestamp() & bitmask_emu;

  auto lgeom = E16ANA_STSGeometry::instance();
  auto ggeom = E16ANA_STSGlobalGeometry::instance();

  for (int i = 0;i < sts_dst0.NumberOfHits(); i++){
    auto& hit0 = sts_dst0.Hit(i);
    //if( hit0.ADC() <= 0 ) continue;
    if( hit0.ADC() == 0xffff ) continue; // invalid.
    hits1.emplace_back();
    auto& hit1 = hits1.back();
#ifdef STS_MODULE_RAND
    hit1.SetIds(get_module_rnd(),hit0.ChannelID());
#else
    hit1.SetIds(hit0.ModuleID(),hit0.ChannelID());
#endif
    hit1.SetPeakHeight(hit0.ADC());
    int emu_timestamp = stsg_dst0.Hit(hitgmap[hit0.E16sts()]).get_emu_timestamp() & bitmask_emu;
    if ( hit0.TDC() != 0xffff ) hit1.SetTiming(hit0.TDC()-emu_timestamp);
    hit1.SetPN(hit0.PN());
    hit1.SetElink(hit0.Elink());
    hit1.SetGeriTimestamp(hit0.GeriTimestamp());
    hit1.SetTDC(hit0.TDC());
    hit1.SetADC(hit0.ADC());
    hit1.SetE16sts(hit0.E16sts());
    TVector3 lpos(lgeom->GetLocalX_fromN(hit0.ChannelID()),0,0);
    if ( hit0.PN() == 0 ) {
      // P
    }else{
      // N
      hit1.SetLocalPos(lpos);
    }
    double local[3]= {lpos.X(),lpos.Y(),lpos.Z()};
    double global[3]={0,0,0};
    ggeom->Local2Global(hit1.ModuleId(),local,global);
    hit1.SetGlobalPos(TVector3(global[0],global[1],global[2]));
  }
  
  
  //  auto lgeom = E16ANA_STSGeometry::instance();
  //std::cout << " local coordinte " << lgeom->GetLocalX_fromN(0) << std::endl;

  /*
  auto& hits1 = ssd1->Hits();
  auto& clusters1 = ssd1->Clusters();
  //  E16ANA_CalibDBManager& calib = E16ANA_CalibDBManager::Instance();
  //  int run_id = 2255;
  //  char* file_name = calib.CalibFileName("SSD-pedestal", run_id);
  //  std::cout << file_name << std::endl;

  const int n_module = 6;
  const int n_module_half = 3;
  const int n_strip = 128;
  const int n_strip_all = 768;
  const int n_sample = 8;

    
  static bool isFirst = true;
  static E16DST_DST1SSDAnalyzerMaker *ssd_analyzers;
  double _pedestal[n_module][n_strip_all][n_sample];

  if(isFirst){
    ssd_analyzers = new E16DST_DST1SSDAnalyzerMaker();//set analyzer class (for each module)
    E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();
    int runID = calib.CurrentRunID();
    // E16ANA_SSDcalibPedestal ssdped;
    // ssdped.ReadCalibData(calib.CurrentRunID());
    // for(int module=0; module<n_module; module++){
    //   for(int strip=0; strip<n_strip_all; strip++){
    // 	for(int sample=0; sample<n_sample; sample++){
    // 	  _pedestal[module][strip][sample] = {(double)ssdped.Pedestal(module, strip, sample)};
    // 	}
    //   }
    // }
    E16ANA_SSDcalibTimeConstant ssdtime;
    ssdtime.ReadConstantData(runID);
    for(int moduleID=101; moduleID<110; moduleID++){
      ssd_analyzers->analyzer_map[OnlineGTR::IDs(moduleID,0).value64]->SetOffset(ssdtime.TDCoffset());
      ssd_analyzers->analyzer_map[OnlineGTR::IDs(moduleID,0).value64]->SetTimegain(ssdtime.TDCtimeGain());
    }

    E16ANA_SSDcalibPedestal ssdped;
    ssdped.ReadCalibData(calib.CurrentRunID());

    for(int moduleID=101; moduleID<110; moduleID++){
      for(int stripID=0; stripID<n_strip_all; stripID++){
	double pedestal[n_sample]={-1};
	for(int sample=0; sample<n_sample; sample++){
	  if(moduleID==102||moduleID==103||moduleID==104){
	    pedestal[sample]=ssdped.Pedestal(moduleID-102, stripID, sample);
    }
	  else if(moduleID==106||moduleID==107||moduleID==108){
	    pedestal[sample]=ssdped.Pedestal(moduleID-106+3, stripID, sample);
	  }
	  else{
	    pedestal[sample]={-1};
	  }
	}
	ssd_analyzers->analyzer_map[OnlineGTR::IDs(moduleID,0).value64]->SetPedestal(stripID, pedestal);//set adc pedestal
      }
    }
    isFirst = false;
    std::cout << "SSD first calling" << std::endl;
    E16MESSAGE("SSD first");
  }// if isFirst

  auto max_hit = hits0.NumberOfHits();//number of hit (each event)
  int _TDC = -1;
  if(max_hit>0){
    E16DST_DST0SSDHit &_hit = hits0.Hit(0);
    _TDC = _hit.TDC();
  }

  for(int moduleID=101; moduleID<110; moduleID++){
    ssd_analyzers->analyzer_map[OnlineGTR::IDs(moduleID,0).value64]->Clear();
    ssd_analyzers->analyzer_map[OnlineGTR::IDs(moduleID,0).value64]->SetTDC(_TDC);
  }
  int16_t invalid_adc[8]={-10000};

  for (int n_hit = 0; n_hit < max_hit; n_hit++) {//for each hit 
    //  for (int n_hit = 0; n_hit < max_hit; ++n_hit) {
    E16DST_DST0SSDHit &hit = hits0.Hit(n_hit);//set information of hit
    int mid = hit.ModuleID();
    int sid = hit.StripID();
    //    if(isSSDStripNoisy(mid,sid)){
    //      continue;
    //    }
    if(//takaura cut
      sid==0||sid==127||sid==128||sid==255||sid==256||sid==383||sid==384||sid==511||sid==512||sid==639||sid==640||sid==767
      ||(mid==106 && (sid==0||sid==128||sid==256||sid==384||sid==512||sid==640))
      ||(mid==107 && (sid==127||sid==255||sid==383||sid==384||sid==511||sid==639||sid==767))
      ||(mid==108 && (sid==0||(sid>127&&sid<256)||sid==256||sid==384||sid==512||sid==640))
    ){
      ssd_analyzers->analyzer_map[OnlineGTR::IDs(mid,0).value64]->SetFadc(sid, invalid_adc);//set invalid adc value for hot channel
    }
    else if(
      get_max(hit.Waveform()) > 950 
      || get_min(hit.Waveform()) < 100
      || get_dev(hit.Waveform()) < 100
      || get_mode(hit.Waveform()) >=3
    ){
      ssd_analyzers->analyzer_map[OnlineGTR::IDs(mid,0).value64]->SetFadc(sid, invalid_adc);//set invalid adc value for hot channel
    }
    else{
      ssd_analyzers->analyzer_map[OnlineGTR::IDs(mid,0).value64]->SetFadc(sid, hit.Waveform());//set adc value for (mid,sid)
    }
  }

  for (auto &a : ssd_analyzers->analyzer_map){
    a.second->AnalyzeV11();//run analyzer for all module(101~109)
  }

  int dst1_hits_size=0;
  int dst1_clusters_size=0;


  for(int mid=101; mid<110; mid++){
    std::vector<E16ANA_SSDAnalyzedStripHit> &hits_0a_temp = ssd_analyzers->analyzer_map[OnlineGTR::IDs(mid, 0).value64]->GetStripX()->GetAnalyzedHits();
    dst1_clusters_size += hits_0a_temp.size();
    for(int i=0; i<hits_0a_temp.size(); i++){
      E16ANA_SSDAnalyzedStripHit &ha_temp = hits_0a_temp[i];      
      //      cout << "temp_size=" << ha_temp.NumHit() << endl;
      dst1_hits_size += ha_temp.NumHit();
    }
  }
  hits1.resize(dst1_hits_size);
  clusters1.resize(dst1_clusters_size);


  int h_id_in_event=0;
  int cl_id_in_event=0;
  for(int mid=101; mid<110; mid++){
    std::vector<E16ANA_SSDSingleStripHit> &hits_0s = ssd_analyzers->analyzer_map[OnlineGTR::IDs(mid, 0).value64]->GetStripX()->GetSingleStripHits();//
    std::vector<E16ANA_SSDAnalyzedStripHit> &hits_0a = ssd_analyzers->analyzer_map[OnlineGTR::IDs(mid, 0).value64]->GetStripX()->GetAnalyzedHits();//vector: get information of all analyzed hit for module=mid
    
    int h_id_in_module=0;
    float sumtiming = 0;//nakasuga
    int ntiming = 0;//nakasuga
    for(int i=0; i<hits_0a.size(); i++){//number of cluster (module=mid)
      vector<short> hit_indexs;
      int h_id_in_cluster=0;
      E16ANA_SSDAnalyzedStripHit &ha = hits_0a[i];//get information of analyzed hit(cluster) for each module
      sumtiming = 0;//nakasuga
      ntiming = 0;//nakasuga
      for(int j=0; j<ha.NumHit(); j++){ //number of hit per cluster
	//E16ANA_SSDSingleStripHit &hs = hits_0s[h_id_in_module];
	E16DST_DST1SSDHit &hit1 = hits1[h_id_in_event];
	hit1.SetInvalid();
	hit1.SetIds(mid, ha.StripID(j));
	hit1.SetTiming(ha.StripTiming(j));
	//hit1.SetPeakHeight(hs.FitScale());
	//hit1.SetHitTime(hs.FitT0());
	//hit1.SetPeakTime(hs.FitRisetime());
	hit1.SetPeakHeight(ha.StripFitScale(j));
	hit1.SetHitTime(ha.StripFitT0(j));
	hit1.SetPeakTime(ha.StripFitT0(j)+ha.StripFitRiseTime(j));
	hit_indexs.push_back(h_id_in_cluster);
	h_id_in_event++;
	h_id_in_module++;
	h_id_in_cluster++;
      }

      
      E16DST_DST1SSDCluster &cluster1 = clusters1[cl_id_in_event];
      cluster1.SetInvalid();
      cluster1.SetModuleId(mid);
      cluster1.SetTiming(ha.Timing());
      //cluster1.SetTiming(sumtiming/(float)ntiming);//nakasuga Bug fixed 220130
      cluster1.SetPeakSum(ha.ClusterCharge());
      cluster1.SetCogPos(ha.CogHit());
      cluster1.SetTdcPos(ha.TdcHit());
      cluster1.SetTanTheta(ha.TanTheta());
      cluster1.SetHitOrders(hit_indexs);


      cluster1.SetCogPosFit(ha.CogHitFit());
      cluster1.SetTimingFit(ha.TimingFit());
      cluster1.SetPeakSumFit(ha.ClusterChargeFit());
      cluster1.SetChi2NdfFit(ha.Chi2NdfFit());

      cl_id_in_event++;
    }
  }
  */
  return 1;
}
