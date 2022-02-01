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

using namespace std;

int get_max(int16_t* v_wave){
  int max = -1000;
  for(int sample=0; sample<8; sample++){
    if(max < v_wave[sample]){
      max = v_wave[sample];
    }
  }
  return max;
}

int get_min(int16_t* v_wave){
  int min = 1000;
  for(int sample=0; sample<8; sample++){
    if(min > v_wave[sample]){
      min = v_wave[sample];
    }
  }
  return min;
}

double get_dev(int16_t* v_wave){
  double sum=0;
  double sum_sqr=0;
  double dev=0;
  double ave=0;
  double ave_sqr=0;
  for(int sample=0; sample<8; sample++){
    sum += v_wave[sample];
    sum_sqr += v_wave[sample]*v_wave[sample];
  }
  ave = sum/8;
  ave_sqr = sum_sqr/8;
  dev = ave_sqr-ave*ave;
  return dev;
}

int get_mode(int16_t* v_wave){
  int num=1;
  int mode_num=0;
  vector<int16_t> wave;
  wave.resize(8);
  for(int i=0; i<8; i++){
    wave.at(i)=v_wave[i];
  }
  sort(wave.begin(),wave.end(),greater<int16_t>());
  for(int sample=0; sample<7; sample++){
    if(wave.at(sample) == wave.at(sample+1)){
      num++;
    }
    else{
      if(num > mode_num){
	mode_num=num;
	num=1;
      }
    }
  }
  return mode_num;
}

int E16DST_DST1SSDFactory(E16DST_DST0Detector<E16DST_DST0SSDHit>& hits0, E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster>* ssd1) {
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

#if 1
  for (auto &a : ssd_analyzers->analyzer_map){
    a.second->AnalyzeV11();//run analyzer for all module(101~109)
//    a.second->Analyze();//run analyzer for all module(101~109)
//    cout << endl;
  }
#else
  cout << "module=102" << endl;
  // ssd_analyzers->analyzer_map[OnlineGTR::IDs(102,0).value64]->AnalyzeV11();
  // cout << "module=103" << endl;
  // ssd_analyzers->analyzer_map[OnlineGTR::IDs(103,0).value64]->AnalyzeV11();
  // cout << "module=104" << endl;
  // ssd_analyzers->analyzer_map[OnlineGTR::IDs(104,0).value64]->AnalyzeV11();
#endif

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
	/* Bug fixed 220130
	if(ha.StripTiming(j)>0){//nakasuga
	  sumtiming += ha.StripTiming(j);//nakasuga
	  ntiming++;//nakasuga
	}//nakasuga
	*/
      }
      /* Bug fixed 220130
      if(ntiming==0){//nakasuga
	ntiming = 1;//nakasuga
	sumtiming = -1000;//nakasuga
      }//nakasuga
      */
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

  //plot
  /*
  // TCanvas *c0 = new TCanvas("c","c",0,0,1000,700);
  // TH1D *h0_hittime;
  // h0_hittime = new TH1D("hit time","h",150,-50,100);
  // TH1D *h0_peaktime;
  // h0_hitpeak = new TH1D("peak time","h",150,-50,100);
  // for(int mid=101; mid<110; mid++){
  //   std::vector<std::vector<double>> &params = ssd_analyzers->analyzer_map[OnlineGTR::IDs(mid, 0).value64]->GetStripX()->GetParams();
  // }

  static bool isFirstplot = true;
  static bool isSecondplot = false;
  if(isFirstplot){
    double adc[8];
    double time[8];
    double param[3];

    TCanvas *c = new TCanvas("c","c",0,0,1000,700);
    c->Divide(5,5);
    for(int mid=101; mid<110; mid++){
      std::vector<std::vector<double>> &plots = ssd_analyzers->analyzer_map[OnlineGTR::IDs(mid, 0).value64]->GetStripX()->GetPlots();
      string modNo = to_string(mid);
      string name = "fit.pdf";
      TString fname = modNo + name;
      cout << "hit in " << mid << " is " << plots.size() << endl;
      for(int i=0; i<plots.size(); i++){
	if(i>24){
	  break;
	}
	c->cd(i+1);
	for(int j=0; j<8; j++){
	  adc[j]=plots.at(i).at(j);
	  time[j]=plots.at(i).at(j+8);
	}
 	TGraph* gr = new TGraph(8,time,adc);
	gr->SetMarkerStyle(3);
	gr->Draw("AP");
	for(int j=0; j<3; j++){
	  param[j]=plots.at(i).at(j+16);
	}
	TF1 *f_fit;
	f_fit = new TF1("f","[1]*(x-[2])/[0]*exp(-(x-[2])/[0])",0,200);
	f_fit->SetParameter(0,param[0]);
	f_fit->SetParameter(1,param[1]);
	f_fit->SetParameter(2,param[2]);
	f_fit->Draw("same");
	TText *t = new TText(1,1,"");
	t->DrawTextNDC(0.1,0.95,Form("[0]=%lf",param[0]));
	t->DrawTextNDC(0.1,0.85,Form("[1]=%lf",param[1]));
	t->DrawTextNDC(0.1,0.75,Form("[2]=%lf",param[2]));
	c->SaveAs(fname,"pdf");
	cout << "made " << fname << endl; 
      }
    }
    if(isSecondplot){
      isFirstplot=false;
    }
    isSecondplot=true;
  }

  //plot no pedestal

  static bool isFirstplot0 = true;
  static bool isSecondplot0 = false;
  if(isFirstplot0){
    double adc[8];
    double time[8];
    double param[3];

    TCanvas *c2 = new TCanvas("c2","c2",0,0,1000,700);
    c2->Divide(5,5);
    for(int mid=101; mid<110; mid++){
      std::vector<std::vector<double>> &plots0 = ssd_analyzers->analyzer_map[OnlineGTR::IDs(mid, 0).value64]->GetStripX()->GetPlots0();
      string modNo = to_string(mid);
      string name = "fit0.pdf";
      TString fname = modNo + name;
      cout << "hit in " << mid << " is " << plots0.size() << endl;
      for(int i=0; i<plots0.size(); i++){
  	if(i>24){
  	  break;
  	}
  	c2->cd(i+1);
  	for(int j=0; j<8; j++){
  	  adc[j]=plots0.at(i).at(j);
  	  time[j]=plots0.at(i).at(j+8);
  	}
  	TGraph* gr = new TGraph(8,time,adc);
  	gr->SetMarkerStyle(3);
  	gr->Draw("AP");
  	for(int j=0; j<3; j++){
  	  param[j]=plots0.at(i).at(j+16);
  	}
  	TF1 *f_fit;
  	f_fit = new TF1("f","[1]*(x-[2])/[0]*exp(-(x-[2])/[0])",0,200);
  	f_fit->SetParameter(0,param[0]);
  	f_fit->SetParameter(1,param[1]);
  	f_fit->SetParameter(2,param[2]);
  	f_fit->Draw("same");
  	TText *t = new TText(1,1,"");
  	t->DrawTextNDC(0.1,0.95,Form("[0]=%lf",param[0]));
  	t->DrawTextNDC(0.1,0.85,Form("[1]=%lf",param[1]));
  	t->DrawTextNDC(0.1,0.75,Form("[2]=%lf",param[2]));
  	c2->SaveAs(fname,"pdf");
  	cout << "made " << fname << endl; 
      }
    }
    if(isSecondplot0){
      isFirstplot0=false;
    }
    isSecondplot0=true;
  }
  */

//  return hits1->GetEventSize();
  return 1;
}
