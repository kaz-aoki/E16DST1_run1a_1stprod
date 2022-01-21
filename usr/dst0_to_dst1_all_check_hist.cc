#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
//#include <boost/program_options.hpp>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_Constant.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16DST_DST1DefaultFilePath.hh"

#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"

#include "E16ANA_WaveformFitter.hh"
#include "E16ANA_HBDCalibration.hh"
#include "E16ANA_HBDCut.hh"
#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_HBDChannelManager.hh"
#include "E16ANA_HBDConstant.hh"
#include "E16ANA_HBDClusterAnalysis.hh"

#include "E16ANA_GTRcalib.hh"
#include "GTR/GTRCheckHist.hh"
#include "E16ANA_TargetInfo.hh"

#define MKTREE 1

using namespace std;
//namespace  bpo = boost::program_options;

int c_mid(int mid){
  int c=-1;
  if(mid==101||mid==102||mid==103||mid==104){
    c=mid-101;
  }
  if(mid==106||mid==107||mid==108||mid==109){
    c=mid-102;
  }
  return c;
}

int m_cid(int cid){
  int m=-1;
  if(cid==0||cid==1||cid==2||cid==3){
    m=cid+101;
  }
  if(cid==4||cid==5||cid==6||cid==7){
    m=cid+102;
  }
  return m;
}

int main(int argc, char* argv[]) {
  if (argc != 5) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst0] [output.dst1] [run ID] [max physics event (all: -1)] " << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  auto run_id        = stoi(argv[3]);
  auto max_event     = stoi(argv[4]);
//  bpo::variables_map vm;
//  string in_file_name;
//  string out_file_name;
//  int run_num;


  TFile *fout = new TFile(out_file_name,"recreate");
  TTree *tree = new TTree("tree","tree");

  int event;

  const int HMAX = 1000;
  const int CMAX = 1000;

  int ssd_nh;
  int ssd_nc;
  int ssd_allnh, ssd_allnc;
  vector<int> ssd_m;
  vector<int> ssd_cs;
  vector<float> ssd_tdc;
  vector<float> ssd_adc;
  vector<float> ssd_lx;
  int gtr_nh, gtr_nc;
  int g100_nh;
  int g100_nc;
  int g100_allnh, g100_allnc;
  vector<int> g100_m;
  vector<int> g100_cs;
  vector<int> g100_type;
  vector<float> g100_tdc;
  vector<float> g100_adc;
  vector<float> g100_lx;
  vector<float> g100_ly;
  vector<float> g100_localx;
  vector<float> g100_maxph;
  vector<int> g100_maxpc;
  vector<float> g100_tdcpos;
  vector<float> g100_tantheta;
  int g200_nh;
  int g200_nc;
  int g200_allnh, g200_allnc;
  vector<int> g200_m;
  vector<int> g200_cs;
  vector<int> g200_type;
  vector<float> g200_tdc;
  vector<float> g200_adc;
  vector<float> g200_lx;
  vector<float> g200_ly;
  vector<float> g200_localx;
  vector<float> g200_maxph;
  vector<int> g200_maxpc;
  vector<float> g200_tdcpos;
  vector<float> g200_tantheta;
  int g300_nh;
  int g300_nc;
  int g300_allnh, g300_allnc;
  vector<int> g300_m;
  vector<int> g300_cs;
  vector<int> g300_type;
  vector<float> g300_tdc;
  vector<float> g300_adc;
  vector<float> g300_lx;
  vector<float> g300_ly;
  vector<float> g300_localx;
  vector<float> g300_maxph;
  vector<int> g300_maxpc;
  vector<float> g300_tdcpos;
  vector<float> g300_tantheta;
  int hbd_nh;
  int hbd_nc;
  int hbd_allnh, hbd_allnc;
  vector<int> hbd_m;
  vector<int> hbd_cs;
  vector<float> hbd_tdc;
  vector<float> hbd_adc;
  vector<float> hbd_sadc;
  vector<float> hbd_ise;
  vector<float> hbd_lx;
  vector<float> hbd_ly;
  int lg_nh;
  int lg_nc;
  int lg_allnh, lg_allnc;
  vector<int> lg_m;
  vector<int> lg_cs;
  vector<float> lg_tdc;
  vector<float> lg_adc;
  vector<float> lg_lx;
  vector<float> lg_ly;

#ifdef MKTREE
  tree->Branch("Event",&event,"Event/I");
  tree->Branch("ssd_nh",&ssd_allnh,"ssd_nh/I");
  tree->Branch("ssd_nc",&ssd_allnc,"ssd_nc/I");
  tree->Branch("ssd_m",&ssd_m);
  tree->Branch("ssd_cs",&ssd_cs);
  tree->Branch("ssd_tdc",&ssd_tdc);
  tree->Branch("ssd_adc",&ssd_adc);
  tree->Branch("ssd_lx",&ssd_lx);
  //  tree->Branch("gtr_nh",&gtr_nh,"gtr_nh/I");
  //  tree->Branch("gtr_nc",&gtr_nc,"gtr_nc/I");
  tree->Branch("g100_nh",&g100_allnh,"g100_nh/I");
  tree->Branch("g100_nc",&g100_allnc,"g100_nc/I");
  tree->Branch("g100_m",&g100_m);
  tree->Branch("g100_cs",&g100_cs);
  tree->Branch("g100_type",&g100_type);
  tree->Branch("g100_tdc",&g100_tdc);
  tree->Branch("g100_adc",&g100_adc);
  tree->Branch("g100_lx",&g100_lx);
  tree->Branch("g100_ly",&g100_ly);
  tree->Branch("g100_localx",&g100_localx);
  tree->Branch("g100_maxph",&g100_maxph);
  tree->Branch("g100_maxpc",&g100_maxpc);
  tree->Branch("g100_tdcpos",&g100_tdcpos);
  tree->Branch("g100_tantheta",&g100_tantheta);
  tree->Branch("g200_nh",&g200_allnh,"g200_nh/I");
  tree->Branch("g200_nc",&g200_allnc,"g200_nc/I");
  tree->Branch("g200_m",&g200_m);
  tree->Branch("g200_cs",&g200_cs);
  tree->Branch("g200_type",&g200_type);
  tree->Branch("g200_tdc",&g200_tdc);
  tree->Branch("g200_adc",&g200_adc);
  tree->Branch("g200_lx",&g200_lx);
  tree->Branch("g200_ly",&g200_ly);
  tree->Branch("g200_localx",&g200_localx);
  tree->Branch("g200_maxph",&g200_maxph);
  tree->Branch("g200_maxpc",&g200_maxpc);
  tree->Branch("g200_tdcpos",&g200_tdcpos);
  tree->Branch("g200_tantheta",&g200_tantheta);
  tree->Branch("g300_nh",&g300_allnh,"g300_nh/I");
  tree->Branch("g300_nc",&g300_allnc,"g300_nc/I");
  tree->Branch("g300_m",&g300_m);
  tree->Branch("g300_cs",&g300_cs);
  tree->Branch("g300_type",&g300_type);
  tree->Branch("g300_tdc",&g300_tdc);
  tree->Branch("g300_adc",&g300_adc);
  tree->Branch("g300_lx",&g300_lx);
  tree->Branch("g300_ly",&g300_ly);
  tree->Branch("g300_localx",&g300_localx);
  tree->Branch("g300_maxph",&g300_maxph);
  tree->Branch("g300_maxpc",&g300_maxpc);
  tree->Branch("g300_tdcpos",&g300_tdcpos);
  tree->Branch("g300_tantheta",&g300_tantheta);
  tree->Branch("hbd_nh",&hbd_allnh,"hbd_nh/I");
  tree->Branch("hbd_nc",&hbd_allnc,"hbd_nc/I");
  tree->Branch("hbd_m",&hbd_m);
  tree->Branch("hbd_cs",&hbd_cs);
  tree->Branch("hbd_tdc",&hbd_tdc);
  tree->Branch("hbd_adc",&hbd_adc);
  tree->Branch("hbd_sadc",&hbd_sadc);
  tree->Branch("hbd_ise",&hbd_ise);
  tree->Branch("hbd_lx",&hbd_lx);
  tree->Branch("hbd_ly",&hbd_ly);
  tree->Branch("lg_nh",&lg_allnh,"lg_nh/I");
  tree->Branch("lg_nc",&lg_allnc,"lg_nc/I");
  tree->Branch("lg_m",&lg_m);
  tree->Branch("lg_cs",&lg_cs);
  tree->Branch("lg_tdc",&lg_tdc);
  tree->Branch("lg_adc",&lg_adc);
  tree->Branch("lg_lx",&lg_lx);
  tree->Branch("lg_ly",&lg_ly);
#endif

  const char par[7][12] = {"Nhits", "Nclusters", "ClusterSize", "Tdc", "Adc", "Lx", "Ly"};
  const char det[6][10] = {"SSD", "GTR100", "GTR200", "GTR300", "HBD", "LG"};
  const char mod[9][5] = {"101", "102", "103", "104", "106", "107", "108", "109", "All"};

  TH1F* hnh[6][9];
  TH1F* hnc[6][9];
  TH1F* hcs[6][9];
  TH1F* htd[6][9];
  TH1F* had[6][9];
  TH1F* hlx[6][9];
  TH1F* hly[6][9];
  TH1F* hlcx[4][9];
  TH1F* hmph[4][9];
  TH1F* hmpc[4][9];
  TH1F* htdp[4][9];
  TH1F* htth[4][9];
  TH1F* htdp3[9];
  TH1F* htth3[9];
  TH1F* hadr4[9];
  TH1F* hise4[9];

  for(int i=0;i<6;i++){//det loop
    for(int j=0;j<9;j++){// mod loop
      hnh[i][j] = new TH1F(Form("hnh%d%d",i,j),Form("%s%s%s",par[0],det[i],mod[j]),1000,0,1000);
      hnc[i][j] = new TH1F(Form("hnc%d%d",i,j),Form("%s%s%s",par[1],det[i],mod[j]),300,0,300);
      hcs[i][j] = new TH1F(Form("hcs%d%d",i,j),Form("%s%s%s",par[2],det[i],mod[j]),50,0,50);
      htd[i][j] = new TH1F(Form("htd%d%d",i,j),Form("%s%s%s",par[3],det[i],mod[j]),700,-100,600);
      hlx[i][j] = new TH1F(Form("hlx%d%d",i,j),Form("%s%s%s",par[5],det[i],mod[j]),800,-400,400);
      hly[i][j] = new TH1F(Form("hly%d%d",i,j),Form("%s%s%s",par[6],det[i],mod[j]),200,-400,400);
      if(i>0&&i<4){
	hlcx[i][j] = new TH1F(Form("hlcx%d%d",i,j),Form("LocalX%s%s",det[i],mod[j]),1000,-100,100);
	hmph[i][j] = new TH1F(Form("hmph%d%d",i,j),Form("MaxPeakHeight%s%s",det[i],mod[j]),3000,0,3000);
	hmpc[i][j] = new TH1F(Form("hmpc%d%d",i,j),Form("MaxPeakCh%s%s",det[i],mod[j]),500,0,500);
	htdp[i][j] = new TH1F(Form("htdp%d%d",i,j),Form("TdcPos%s%s",det[i],mod[j]),10000,-10000,10000);
	htth[i][j] = new TH1F(Form("htth%d%d",i,j),Form("TanTheta%s%s",det[i],mod[j]),1000,-500,500);
      }
    }
  }
  for(int j=0;j<9;j++){// mod loop
    had[0][j] = new TH1F(Form("had%d%d",0,j),Form("%s%s%s",par[4],det[0],mod[j]),100,0,10000);//ssd
    had[1][j] = new TH1F(Form("had%d%d",1,j),Form("%s%s%s",par[4],det[1],mod[j]),100,0,50000);//gtr100
    had[2][j] = new TH1F(Form("had%d%d",2,j),Form("%s%s%s",par[4],det[2],mod[j]),100,0,50000);//gtr200
    had[3][j] = new TH1F(Form("had%d%d",3,j),Form("%s%s%s",par[4],det[3],mod[j]),100,0,50000);//gtr300
    had[4][j] = new TH1F(Form("had%d%d",4,j),Form("%s%s%s",par[4],det[4],mod[j]),2000,0,20);//hbd
    hadr4[j] = new TH1F(Form("hadr%d%d",4,j),Form("%sRaw%s%s",par[4],det[4],mod[j]),2000,0,2000);//hbd
    hise4[j] = new TH1F(Form("hise%d%d",4,j),Form("IsE%s%s",det[4],mod[j]),10,0,2);//hbd
    had[5][j] = new TH1F(Form("had%d%d",5,j),Form("%s%s%s",par[4],det[5],mod[j]),1000,0,1000);//lg
  }





  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  auto trigger_param = new E16ANA_TriggerCalibParam();
  trigger_param->ReadConstantData(calib.CurrentRunID());
  E16ANA_GTRcalibPedestal gtrped;
  gtrped.ReadCalibData( calib.CurrentRunID() );
  E16ANA_LGBasic lgbasic;
  lgbasic.SetCalibMap();//it is necessary to use energy deposit and calibrated timing.
  E16ANA_TargetInfoManager& targets = E16ANA_TargetInfoManager::Instance();
  targets.ReadInfoWithRunID( calib.CurrentRunID());
  targets.Print();
  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));

  //HBD initialize
  E16ANA_HBDCalibration *hbd_calib = new E16ANA_HBDCalibration();
  hbd_calib->ReadCalibrationData(calib.CurrentRunID());
  E16ANA_HBDCut *hbd_cut = new E16ANA_HBDCut();
  hbd_cut->ReadCutData(calib.CurrentRunID());
  std::string hbd_waveform_template = calib.CalibFileName("HBD-waveform-template", 0);
  E16ANA_WaveformFitter *wf1d_fitter = new E16ANA_WaveformFitter(hbd_waveform_template);


  auto record = new E16DST_DST1PhysicsRecord();

  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }

  int n_event = 0;
  int n_physics_event = 0;
  while (dst0->ReadAnEvent()) {
    if (max_event != -1 && n_physics_event >= max_event) {
      break;
    }
    if (n_event % 1000 == 0) {
      cout << "Number of event: " << n_event << endl;
    }
    auto event_type = dst0->EventType();
////////    dst1->SetEventType(event_type);
    if (event_type == E16DST_DST0EventType::Physics) {
      auto event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
      auto& ssd_hits0         = event0->SSD();
      auto& gtr_hits0         = event0->GTR();
      auto& hbd_hits0         = event0->HBD();
      auto& lg_hits0          = event0->LG();
      auto& trigger_gtr_hits0 = event0->TriggerGTR();
      auto& trigger_hbd_hits0 = event0->TriggerHBD();
      auto& trigger_lg_hits0  = event0->TriggerLG();

      //HBD initialize
      //E16ANA_HBDCalibration *hbd_calib = new E16ANA_HBDCalibration();
      //hbd_calib->ReadCalibrationData(calib.CurrentRunID());
      //E16ANA_HBDCut *hbd_cut = new E16ANA_HBDCut();
      //hbd_cut->ReadCutData(calib.CurrentRunID());
      //std::string hbd_waveform_template = calib.CalibFileName("HBD-waveform-template", 0);
      //E16ANA_WaveformFitter *wf1d_fitter = new E16ANA_WaveformFitter(hbd_waveform_template);

      E16DST_DST1SSDFactory(ssd_hits0, &record->SSD());
      E16DST_DST1GTRFactory(gtr_hits0, &record->GTR(), gtrped);
      E16DST_DST1HBDFactory(hbd_hits0, hbd_calib, hbd_cut, wf1d_fitter, &record->HBD());
      E16DST_DST1LGFactory(lg_hits0, &record->LG(), 1, geometry);
//      E16DST_DST1TriggerFactory(*trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &event1->Trigger());

      record->SSD().UpdatePtrs();
      record->GTR().UpdatePtrs();
      record->HBD().UpdatePtrs();
      record->LG().UpdatePtrs();


//// Check begin
      //auto event_id = event0->EventID();
      //cout << "Event ID: " << event_id << endl;

      event = event0->EventID();

// SSD
      ssd_allnh = 0;
      ssd_allnc = 0;
      ssd_m.clear();
      ssd_cs.clear();
      ssd_tdc.clear();
      ssd_adc.clear();
      ssd_lx.clear();
      for(int j=0;j<8;j++){//module loop
	int mod = m_cid(j);
	auto& ssd_hits1 = record->SSD().HitPtrs(mod,0,0);
	auto& ssd_clusters1 = record->SSD().ClusterPtrs(mod,0,0);
	ssd_nh = ssd_hits1.size();
	ssd_nc = ssd_clusters1.size();
	hnh[0][j]->Fill(ssd_nh);
	hnc[0][j]->Fill(ssd_nc);
	ssd_allnh += ssd_nh;
	ssd_allnc += ssd_nc;
	hnh[0][8]->Fill(ssd_nh);
	hnc[0][8]->Fill(ssd_nc);
	if (ssd_clusters1.size() != 0) {
	  for(int i=0;i<ssd_nc;i++){//cluster loop
	    auto& ssdcluster = ssd_clusters1[i];
	    hcs[0][j]->Fill(ssdcluster->NumHits());
	    htd[0][j]->Fill(ssdcluster->Timing());
	    had[0][j]->Fill(ssdcluster->PeakSum());
	    hlx[0][j]->Fill(ssdcluster->CogPos());
#ifdef MKTREE
	    ssd_m.push_back(mod);
	    ssd_cs.push_back(ssdcluster->NumHits());
	    ssd_tdc.push_back(ssdcluster->Timing());
	    ssd_adc.push_back(ssdcluster->PeakSum());
	    ssd_lx.push_back(ssdcluster->CogPos());
#endif
	    hcs[0][8]->Fill(ssdcluster->NumHits());
	    htd[0][8]->Fill(ssdcluster->Timing());
	    had[0][8]->Fill(ssdcluster->PeakSum());
	    hlx[0][8]->Fill(ssdcluster->CogPos());
	  }//cluster loop
	}//ssd cluster bool
      }//module loop

// GTR

      g100_allnh = 0;
      g100_allnc = 0;
      g100_m.clear();
      g100_cs.clear();
      g100_type.clear();
      g100_tdc.clear();
      g100_adc.clear();
      g100_lx.clear();
      g100_ly.clear();
      g100_localx.clear();
      g100_maxph.clear();
      g100_maxpc.clear();
      g100_tdcpos.clear();
      g100_tantheta.clear();
      g200_allnh = 0;
      g200_allnc = 0;
      g200_m.clear();
      g200_cs.clear();
      g200_type.clear();
      g200_tdc.clear();
      g200_adc.clear();
      g200_lx.clear();
      g200_ly.clear();
      g200_localx.clear();
      g200_maxph.clear();
      g200_maxpc.clear();
      g200_tdcpos.clear();
      g200_tantheta.clear();
      g300_allnh = 0;
      g300_allnc = 0;
      g300_m.clear();
      g300_cs.clear();
      g300_type.clear();
      g300_tdc.clear();
      g300_adc.clear();
      g300_lx.clear();
      g300_ly.clear();
      g300_localx.clear();
      g300_maxph.clear();
      g300_maxpc.clear();
      g300_tdcpos.clear();
      g300_tantheta.clear();
      for(int j=0;j<8;j++){//module loop
	int mod = m_cid(j);
	for(int k=0;k<3;k++){//layer loop
	  gtr_nh = 0;
	  gtr_nc = 0;
	  for(int l=0;l<3;l++){//type loop
	    if(l==2&&k!=0){continue;}
	    auto& gtr_hits1 = record->GTR().HitPtrs(mod,k,l);
	    auto& gtr_clusters1 = record->GTR().ClusterPtrs(mod,k,l);
	    gtr_nh += gtr_hits1.size();
	    gtr_nc += gtr_clusters1.size();
	    if(k==0){g100_allnh += gtr_nh; g100_allnc += gtr_nc;}
	    if(k==1){g200_allnh += gtr_nh; g200_allnc += gtr_nc;}
	    if(k==2){g300_allnh += gtr_nh; g300_allnc += gtr_nc;}
	    if (gtr_clusters1.size() != 0) {
	      for(int i=0;i<gtr_clusters1.size();i++){//cluster loop
		auto& gtrcluster = gtr_clusters1[i];
		hcs[k+1][j]->Fill(gtrcluster->NumHits());
		htd[k+1][j]->Fill(gtrcluster->Timing());
		had[k+1][j]->Fill(gtrcluster->PeakSum());
		hlcx[k+1][j]->Fill(gtrcluster->LocalX());
		hmph[k+1][j]->Fill(gtrcluster->MaxPeakHeight());
		hmpc[k+1][j]->Fill(gtrcluster->MaxPeakCh());
		htdp[k+1][j]->Fill(gtrcluster->TdcPos());
		htth[k+1][j]->Fill(gtrcluster->TanTheta());
#ifdef MKTREE
		if(k==0){
		  g100_m.push_back(mod);
		  g100_cs.push_back(gtrcluster->NumHits());
		  g100_type.push_back(l);
		  g100_tdc.push_back(gtrcluster->Timing());
		  g100_adc.push_back(gtrcluster->PeakSum());
		  g100_localx.push_back(gtrcluster->LocalX());
		  g100_maxph.push_back(gtrcluster->MaxPeakHeight());
		  g100_maxpc.push_back(gtrcluster->MaxPeakCh());
		  g100_tdcpos.push_back(gtrcluster->TdcPos());
		  g100_tantheta.push_back(gtrcluster->TanTheta());
		}
		if(k==1){g200_m.push_back(mod);
		  g200_m.push_back(mod);
		  g200_cs.push_back(gtrcluster->NumHits());
		  g200_type.push_back(l);
		  g200_tdc.push_back(gtrcluster->Timing());
		  g200_adc.push_back(gtrcluster->PeakSum());
		  g200_localx.push_back(gtrcluster->LocalX());
		  g200_maxph.push_back(gtrcluster->MaxPeakHeight());
		  g200_maxpc.push_back(gtrcluster->MaxPeakCh());
		  g200_tdcpos.push_back(gtrcluster->TdcPos());
		  g200_tantheta.push_back(gtrcluster->TanTheta());
		}
		if(k==2){g300_m.push_back(mod);
		  g300_m.push_back(mod);
		  g300_cs.push_back(gtrcluster->NumHits());
		  g300_type.push_back(l);
		  g300_tdc.push_back(gtrcluster->Timing());
		  g300_adc.push_back(gtrcluster->PeakSum());
		  g300_localx.push_back(gtrcluster->LocalX());
		  g300_maxph.push_back(gtrcluster->MaxPeakHeight());
		  g300_maxpc.push_back(gtrcluster->MaxPeakCh());
		  g300_tdcpos.push_back(gtrcluster->TdcPos());
		  g300_tantheta.push_back(gtrcluster->TanTheta());
		}
#endif
		hcs[k+1][8]->Fill(gtrcluster->NumHits());
		htd[k+1][8]->Fill(gtrcluster->Timing());
		had[k+1][8]->Fill(gtrcluster->PeakSum());
		hlcx[k+1][8]->Fill(gtrcluster->LocalX());
		hmph[k+1][8]->Fill(gtrcluster->MaxPeakHeight());
		hmpc[k+1][8]->Fill(gtrcluster->MaxPeakCh());
		htdp[k+1][8]->Fill(gtrcluster->TdcPos());
		htth[k+1][8]->Fill(gtrcluster->TanTheta());

		if(l==0){
		  hlx[k+1][j]->Fill(gtrcluster->CogPos());
#ifdef MKTREE
		  if(k==0){g100_lx.push_back(gtrcluster->CogPos());}
		  if(k==1){g200_lx.push_back(gtrcluster->CogPos());}
		  if(k==2){g300_lx.push_back(gtrcluster->CogPos());}
#endif
		  hlx[k+1][8]->Fill(gtrcluster->CogPos());
		}
		else{
		  hly[k+1][j]->Fill(gtrcluster->CogPos());
#ifdef MKTREE
		  if(k==0){g100_ly.push_back(gtrcluster->CogPos());}
		  if(k==1){g200_ly.push_back(gtrcluster->CogPos());}
		  if(k==2){g300_ly.push_back(gtrcluster->CogPos());}
#endif
		  hly[k+1][8]->Fill(gtrcluster->CogPos());
		}
	      }//cluster loop
	    }//gtr cluster bool
	  }//type loop

	  hnh[k+1][j]->Fill(gtr_nh);
	  hnc[k+1][j]->Fill(gtr_nc);
	  hnh[k+1][8]->Fill(gtr_nh);
	  hnc[k+1][8]->Fill(gtr_nc);

	}//layer loop
      }//module loop

// HBD

      hbd_allnh = 0;
      hbd_allnc = 0;
      hbd_m.clear();
      hbd_cs.clear();
      hbd_tdc.clear();
      hbd_adc.clear();
      hbd_sadc.clear();
      hbd_ise.clear();
      hbd_lx.clear();
      hbd_ly.clear();
      for(int j=0;j<8;j++){//module loop
	int mod = m_cid(j);
	auto& hbd_hits1 = record->HBD().HitPtrs(mod,0,0);;
	auto& hbd_clusters1 = record->HBD().ClusterPtrs(mod,0,0);
	hbd_nh = hbd_hits1.size();
	hbd_nc = hbd_clusters1.size();
	hnh[4][j]->Fill(hbd_nh);
	hnc[4][j]->Fill(hbd_nc);
	hbd_allnh += hbd_nh;
	hbd_allnc += hbd_nc;
	hnh[4][8]->Fill(hbd_nh);
	hnc[4][8]->Fill(hbd_nc);
	if (hbd_clusters1.size() != 0) {
	  for(int i=0;i<hbd_nc;i++){//cluster loop
	    auto& hbdcluster = hbd_clusters1[i];
	    hcs[4][j]->Fill(hbdcluster->ClusterSize());
	    htd[4][j]->Fill(hbdcluster->Timing());
	    had[4][j]->Fill(hbdcluster->PeakSum());
	    hadr4[j]->Fill(hbdcluster->SADC());
	    hise4[j]->Fill(hbdcluster->IsE());
	    hlx[4][j]->Fill(hbdcluster->LocalPos().X());
	    hly[4][j]->Fill(hbdcluster->LocalPos().Y());
#ifdef MKTREE
	    hbd_m.push_back(mod);
	    hbd_cs.push_back(hbdcluster->ClusterSize());
	    hbd_tdc.push_back(hbdcluster->Timing());
	    hbd_adc.push_back(hbdcluster->PeakSum());
	    hbd_sadc.push_back(hbdcluster->SADC());
	    hbd_ise.push_back(hbdcluster->IsE());
	    hbd_lx.push_back(hbdcluster->LocalPos().X());
	    hbd_ly.push_back(hbdcluster->LocalPos().Y());
#endif
	    hcs[4][8]->Fill(hbdcluster->ClusterSize());
	    htd[4][8]->Fill(hbdcluster->Timing());
	    had[4][8]->Fill(hbdcluster->PeakSum());
	    hadr4[8]->Fill(hbdcluster->SADC());
	    hise4[8]->Fill(hbdcluster->IsE());
	    hlx[4][8]->Fill(hbdcluster->LocalPos().X());
	    hly[4][8]->Fill(hbdcluster->LocalPos().Y());
	  }//cluster loop
	}//hbd cluster bool
      }//module loop

// LG

      lg_allnh = 0;
      lg_allnc = 0;
      lg_m.clear();
      lg_cs.clear();
      lg_tdc.clear();
      lg_adc.clear();
      lg_lx.clear();
      lg_ly.clear();
      for(int j=0;j<8;j++){//module loop
	int mod = m_cid(j);
	auto& lg_hits1 = record->LG().HitPtrs(mod,0,0);;
	auto& lg_clusters1 = record->LG().ClusterPtrs(mod,0,0);
	lg_nh = lg_hits1.size();
	lg_nc = lg_clusters1.size();
	hnh[5][j]->Fill(lg_nh);
	hnc[5][j]->Fill(lg_nc);
	lg_allnh += lg_nh;
	lg_allnc += lg_nc;
	hnh[5][8]->Fill(lg_nh);
	hnc[5][8]->Fill(lg_nc);
	if (lg_hits1.size() != 0) {
	  for(int i=0;i<lg_nh;i++){//cluster loop
	    auto& lghit = lg_hits1[i];
	    hcs[5][j]->Fill(1);
	    htd[5][j]->Fill( lghit->GetCalibTiming(lgbasic, lghit->FitTiming()) );
	    had[5][j]->Fill(lghit->FitPeak());
	    hlx[5][j]->Fill(lghit->LocalPos(*geometry).X());
	    hly[5][j]->Fill(lghit->LocalPos(*geometry).Y());
#ifdef MKTREE
	    lg_m.push_back(mod);
	    lg_cs.push_back(1);
	    lg_tdc.push_back(lghit->GetCalibTiming(lgbasic, lghit->FitTiming()));
	    lg_adc.push_back(lghit->FitPeak());
	    lg_lx.push_back(lghit->LocalPos(*geometry).X());
	    lg_ly.push_back(lghit->LocalPos(*geometry).Y());
#endif
	    hcs[5][8]->Fill(1);
	    htd[5][8]->Fill( lghit->GetCalibTiming(lgbasic, lghit->FitTiming()) );
	    had[5][8]->Fill(lghit->FitPeak());
	    hlx[5][8]->Fill(lghit->LocalPos(*geometry).X());
	    hly[5][8]->Fill(lghit->LocalPos(*geometry).Y());
	  }//cluster loop
	}//lg cluster bool
      }//module loop

#ifdef MKTREE
      tree->Fill();
#endif

//// trigger
//      event1->Trigger().Print(*geometry);
//
//// Check end

//      dst1->WriteAnEvent();
//      delete event0;
//      delete record;

    } else if (event_type == E16DST_DST0EventType::Scaler) {
      //auto event0 = dynamic_cast<E16DST_DST0ScalerEvent*>(dst0->Event());
      //E16DST_DST0UT3 ut3 = evnet0->UT3();
//      dst1->WriteAnEvent(event0);
    } else if (event_type == E16DST_DST0EventType::SpillStart) {
      auto event0 = dynamic_cast<E16DST_DST0SpillStartEvent*>(dst0->Event());
//      dst1->WriteAnEvent(event0);
    } else if (event_type == E16DST_DST0EventType::SpillEnd) {
      auto event0 = dynamic_cast<E16DST_DST0SpillEndEvent*>(dst0->Event());
//      dst1->WriteAnEvent(event0);
    } else {
      std::cerr << "Invalid Event Type: " << event_type << std::endl;
      return -1;
    }
    ++n_event;
    ++n_physics_event;
  }

  fout->Write();
  fout->Close();

  delete geometry;
  delete dst0;
//  dst1->Close();
  return 0;
}
