#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
//#include <boost/program_options.hpp>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"

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

  /*
  TH1F *hph[7][56];
  TH1F *hpt[7][56];
  TH1F *htm[7][56];
  TH1F *hbl[7][56];
  TH1F *hbr[7][56];
  TH1F *hit[7][56];
  TH1F *ht0[7][56];
  TH1F *hed[7][56];
  TH1F *hnp[7][56];
  TH1F *hff[7][56];
  TH1F *hfp[7][56];
  TH1F *hfx[7][56];
  TH1F *hft[7][56];
  TH1F *hfw[7][56];
  TH1F *hfc[7][56];
  for(int i=0;i<7;i++){
    for(int j=0;j<56;j++){
      hph[i][j] = new TH1F(Form("hph%d%d",i,j),Form("PeakHeight%d%d",i,j),1100,-100,1000);
      hpt[i][j] = new TH1F(Form("hpt%d%d",i,j),Form("PeakTime%d%d",i,j),200,0,200);
      htm[i][j] = new TH1F(Form("htm%d%d",i,j),Form("Timing%d%d",i,j),200,0,200);
      hbl[i][j] = new TH1F(Form("hbl%d%d",i,j),Form("Baseline%d%d",i,j),200,-100,100);
      hbr[i][j] = new TH1F(Form("hbr%d%d",i,j),Form("BaselineRms%d%d",i,j),200,-100,100);
      hit[i][j] = new TH1F(Form("hit%d%d",i,j),Form("Integral%d%d",i,j),1100,-100,1000);
      ht0[i][j] = new TH1F(Form("ht0%d%d",i,j),Form("CalibTiming%d%d",i,j),1000,0,200);
      hed[i][j] = new TH1F(Form("hed%d%d",i,j),Form("EnergyDeposit%d%d",i,j),1100,-1,10);
      hnp[i][j] = new TH1F(Form("hnp%d%d",i,j),Form("Npeaks%d%d",i,j),5,0,5);
      hff[i][j] = new TH1F(Form("hff%d%d",i,j),Form("FitFlag%d%d",i,j),5,0,5);
      hfp[i][j] = new TH1F(Form("hfp%d%d",i,j),Form("FitPeak%d%d",i,j),1100,-100,1000);
      hfx[i][j] = new TH1F(Form("hfx%d%d",i,j),Form("FitPeakTime%d%d",i,j),200,0,200);
      hft[i][j] = new TH1F(Form("hft%d%d",i,j),Form("FitTiming%d%d",i,j),200,0,200);
      hfw[i][j] = new TH1F(Form("hfw%d%d",i,j),Form("FitWidth%d%d",i,j),200,0,2);
      hfc[i][j] = new TH1F(Form("hfc%d%d",i,j),Form("FitChi2%d%d",i,j),200,0,50);
    }
  }
  */

  int event;
  const int NMOD = 8;
  const int CMAX = 100;
  int lg_nm;
  int lg_nh[NMOD];
  int lg_nc[NMOD];
  float lg_cs[NMOD][CMAX];
  float lg_tdc[NMOD][CMAX];
  float lg_adc[NMOD][CMAX];

  tree->Branch("Event",&event,"Event/I");
  tree->Branch("lg_nm",&lg_nm,"lg_nm/I");
  tree->Branch("lg_nh",lg_nh,"lg_nh[lg_nm]/I");
  tree->Branch("lg_nc",lg_nc,"lg_nc[lg_nm]/I");
  tree->Branch("lg_cs",&lg_cs,"lg_cs[lg_nm][lg_nc[lg_nm]]/F");
  tree->Branch("lg_tdc",&lg_tdc,"lg_cs[lg_nm][lg_nc[lg_nm]]/F");
  tree->Branch("lg_adc",&lg_adc,"lg_cs[lg_nm][lg_nc[lg_nm]]/F");

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  //auto trigger_param = new E16ANA_TriggerCalibParam();
  //trigger_param->ReadConstantData(calib.CurrentRunID());
  //E16ANA_GTRcalibPedestal gtrped;
  //gtrped.ReadCalibData( calib.CurrentRunID() );
  E16ANA_LGBasic lgbasic;
  lgbasic.SetCalibMap();//it is necessary to use energy deposit and calibrated timing.

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  
  auto record = new E16DST_DST1PhysicsRecord();

  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }
//  E16ANA_GTRPedestal *gtr_pedestal = new E16ANA_GTRPedestal();
//  gtr_pedestal->Read(argv[5]);
//  auto dst1 = new E16DST_DST1();
//  auto dst1 = new E16DST_DST0();
//  if (!dst1->Open(out_file_name, E16DST_DST0::WriteMode)) {
//    std::cerr << "Cannot open output file: " << out_file_name << std::endl;
//    return -1;
//   }

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
////////      E16DST_DST0Detector<E16DST_DST1LGHit> lg_hits1;
////////      E16DST_DST0Detector<E16DST_DST1LGCluster> lg_clusters1;
////////      auto& lg_hits1 = record->LG().Hits();
////////      auto& lg_clusters1 = record->LG().Clusters();
//      E16DST_DST1SSDFactory(ssd_hits0, &event1->SSDHits(), &event1->SSDClusters());
//      std::cout << "GTR factory returns :: " << E16DST_DST1GTRHitAndClusterFactory(gtr_hits0, &event1->GTRHits(), &event1->GTRClusters(), gtrped) << std::endl;
//      E16DST_DST1GTRFactoryDST1Detector(gtr_hits0, &event1->GTR());
//      E16DST_DST1HBDFactory(hbd_hits0, &event1->HBDHits(), &event1->HBDClusters());
      E16DST_DST1LGFactory(lg_hits0, &record->LG(), 1);
//      E16DST_DST1TriggerFactory(*trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &event1->Trigger());


//// Check begin
      //auto event_id = event0->EventID();
      //cout << "Event ID: " << event_id << endl;
//// SSD
//
//// GTR
//      cout << "Number of event: " << n_event << endl << endl;
//      auto n_gtr_hits = event1->GTRHits().NumberOfHits();
//      cout << "Number of GTR hits: " << n_gtr_hits << endl;
//      for (int n_hit = 0; n_hit < n_gtr_hits; ++n_hit) {
//        auto hit = event1->GTRHits().Hit(n_hit);
//        hit.Print();
//      }
//      auto n_gtr_clusters = event1->GTRClusters().NumberOfHits();
//      cout << endl << endl;
//      cout << "Number of GTR clusters: " << n_gtr_clusters << endl;
//      for (int n_cluster = 0; n_cluster < n_gtr_clusters; ++n_cluster) {
//        auto cluster = event1->GTRClusters().Hit(n_cluster);
//        cluster.Print();
//      }
//      
//// HBD
//
//// LG
      event = event0->EventID();
      lg_nm = 8;
      for(int i=0;i<lg_nm;i++){
	lg_nh[i] = 0;
	lg_nc[i] = 0;
      }
      auto& lg_hits1 = record->LG().Hits();
      auto& lg_clusters1 = record->LG().Clusters();
      int n_lghits = lg_hits1.size();
      int n_lgclusters = lg_clusters1.size();
      int module;
      if (lg_hits1.size() != 0) {
	for(int i=0;i<n_lghits;i++){//hit loop
	  auto& lghit = lg_hits1[i];
	  module = lghit.ModuleId();
	  for(int i=0;i<lg_nm;i++){
	    if(module==m_cid(i)){
	      int ct = c_mid(module);
	      lg_cs[ct][lg_nh[ct]] = 1;
	      lg_tdc[ct][lg_nh[ct]] = lghit.FitTiming();
	      lg_adc[ct][lg_nh[ct]] = lghit.FitPeak();
	      lg_nh[ct]++;
	      break;
	    }
	  }
	}//hit loop
      }//lg hit bool

      if (lg_clusters1.size() != 0) {
	for(int i=0;i<n_lgclusters;i++){//cluster loop
	  auto& lgcluster = lg_clusters1[i];
	  module = lgcluster.ModuleId();
	  for(int i=0;i<lg_nm;i++){
	    if(module==m_cid(i)){
	      int ct = c_mid(module);
	      lg_nc[ct]++;
	      break;
	    }
	  }
	}//cluster loop
      }//lg cluster bool

      tree->Fill();



//// trigger
//      event1->Trigger().Print(*geometry);
//
//// Check end

//      dst1->WriteAnEvent();
//      delete event0;
//      delete record;

    } else if (event_type == E16DST_DST0EventType::Scaler) {
      auto event0 = dynamic_cast<E16DST_DST0ScalerEvent*>(dst0->Event());
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
