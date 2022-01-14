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
  int ssd_m[CMAX];
  int ssd_cs[CMAX];
  float ssd_tdc[CMAX];
  float ssd_adc[CMAX];
  float ssd_lx[CMAX];
  int gtr_nh, gtr_nc;
  int g100_nh;
  int g100_nc;
  int g100_m[CMAX];
  int g100_cs[CMAX];
  float g100_tdc[CMAX];
  float g100_adc[CMAX];
  float g100_lx[CMAX];
  float g100_ly[CMAX];
  int g200_nh;
  int g200_nc;
  int g200_m[CMAX];
  int g200_cs[CMAX];
  float g200_tdc[CMAX];
  float g200_adc[CMAX];
  float g200_lx[CMAX];
  float g200_ly[CMAX];
  int g300_nh;
  int g300_nc;
  int g300_m[CMAX];
  int g300_cs[CMAX];
  float g300_tdc[CMAX];
  float g300_adc[CMAX];
  float g300_lx[CMAX];
  float g300_ly[CMAX];
  int hbd_nh;
  int hbd_nc;
  int hbd_m[CMAX];
  int hbd_cs[CMAX];
  float hbd_tdc[CMAX];
  float hbd_adc[CMAX];
  float hbd_lx[CMAX];
  float hbd_ly[CMAX];
  float hbd_ise[CMAX];
  int lg_nh;
  int lg_nc;
  int lg_m[HMAX];
  int lg_cs[HMAX];
  float lg_tdc[HMAX];
  float lg_adc[HMAX];
  float lg_lx[HMAX];
  float lg_ly[HMAX];

  tree->Branch("Event",&event,"Event/I");
  tree->Branch("ssd_nh",&ssd_nh,"ssd_nh/I");
  tree->Branch("ssd_nc",&ssd_nc,"ssd_nc/I");
  tree->Branch("ssd_m",ssd_m,"ssd_m[ssd_nc]/I");
  tree->Branch("ssd_cs",ssd_cs,"ssd_cs[ssd_nc]/I");
  tree->Branch("ssd_tdc",ssd_tdc,"ssd_tdc[ssd_nc]/F");
  tree->Branch("ssd_adc",ssd_adc,"ssd_adc[ssd_nc]/F");
  tree->Branch("ssd_lx",ssd_lx,"ssd_lx[ssd_nc]/F");
  tree->Branch("gtr_nh",&gtr_nh,"gtr_nh/I");
  tree->Branch("gtr_nc",&gtr_nc,"gtr_nc/I");
  tree->Branch("g100_nh",&g100_nh,"g100_nh/I");
  tree->Branch("g100_nc",&g100_nc,"g100_nc/I");
  tree->Branch("g100_m",g100_m,"g100_m[g100_nc]/I");
  tree->Branch("g100_cs",g100_cs,"g100_cs[g100_nc]/I");
  tree->Branch("g100_tdc",g100_tdc,"g100_tdc[g100_nc]/F");
  tree->Branch("g100_adc",g100_adc,"g100_adc[g100_nc]/F");
  tree->Branch("g100_lx",g100_lx,"g100_lx[g100_nc]/F");
  tree->Branch("g100_ly",g100_ly,"g100_ly[g100_nc]/F");
  tree->Branch("g200_nh",&g200_nh,"g200_nh/I");
  tree->Branch("g200_nc",&g200_nc,"g200_nc/I");
  tree->Branch("g200_m",g200_m,"g200_m[g200_nc]/I");
  tree->Branch("g200_cs",g200_cs,"g200_cs[g200_nc]/I");
  tree->Branch("g200_tdc",g200_tdc,"g200_tdc[g200_nc]/F");
  tree->Branch("g200_adc",g200_adc,"g200_adc[g200_nc]/F");
  tree->Branch("g200_lx",g200_lx,"g200_lx[g200_nc]/F");
  tree->Branch("g200_ly",g200_ly,"g200_ly[g200_nc]/F");
  tree->Branch("g300_nh",&g300_nh,"g300_nh/I");
  tree->Branch("g300_nc",&g300_nc,"g300_nc/I");
  tree->Branch("g300_m",g300_m,"g300_m[g300_nc]/I");
  tree->Branch("g300_cs",g300_cs,"g300_cs[g300_nc]/I");
  tree->Branch("g300_tdc",g300_tdc,"g300_tdc[g300_nc]/F");
  tree->Branch("g300_adc",g300_adc,"g300_adc[g300_nc]/F");
  tree->Branch("g300_lx",g300_lx,"g300_lx[g300_nc]/F");
  tree->Branch("g300_ly",g300_ly,"g300_ly[g300_nc]/F");
  tree->Branch("hbd_nh",&hbd_nh,"hbd_nh/I");
  tree->Branch("hbd_nc",&hbd_nc,"hbd_nc/I");
  tree->Branch("hbd_m",hbd_m,"hbd_m[hbd_nc]/I");
  tree->Branch("hbd_cs",hbd_cs,"hbd_cs[hbd_nc]/I");
  tree->Branch("hbd_tdc",hbd_tdc,"hbd_tdc[hbd_nc]/F");
  tree->Branch("hbd_adc",hbd_adc,"hbd_adc[hbd_nc]/F");
  tree->Branch("hbd_lx",hbd_lx,"hbd_lx[hbd_nc]/F");
  tree->Branch("hbd_ly",hbd_ly,"hbd_ly[hbd_nc]/F");
  tree->Branch("hbd_ise",hbd_ise,"hbd_ise[hbd_nc]/F");
  tree->Branch("lg_nh",&lg_nh,"lg_nh/I");
  tree->Branch("lg_nc",&lg_nc,"lg_nc/I");
  tree->Branch("lg_m",lg_m,"lg_m[lg_nh]/I");
  tree->Branch("lg_cs",lg_cs,"lg_cs[lg_nh]/I");
  tree->Branch("lg_tdc",lg_tdc,"lg_tdc[lg_nh]/F");
  tree->Branch("lg_adc",lg_adc,"lg_adc[lg_nh]/F");
  tree->Branch("lg_lx",lg_lx,"lg_lx[lg_nh]/F");
  tree->Branch("lg_ly",lg_ly,"lg_ly[lg_nh]/F");


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
      E16DST_DST1LGFactory(lg_hits0, &record->LG(), 1);
//      E16DST_DST1TriggerFactory(*trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &event1->Trigger());


//// Check begin
      //auto event_id = event0->EventID();
      //cout << "Event ID: " << event_id << endl;

      event = event0->EventID();

// SSD
      auto& ssd_hits1 = record->SSD().Hits();
      auto& ssd_clusters1 = record->SSD().Clusters();
      ssd_nh = ssd_hits1.size();
      ssd_nc = ssd_clusters1.size();
      if (ssd_clusters1.size() != 0) {
	for(int i=0;i<ssd_nc;i++){//cluster loop
	  auto& ssdcluster = ssd_clusters1[i];
	  ssd_m[i] = ssdcluster.ModuleId();
	  ssd_cs[i] = ssdcluster.NumHits();
	  ssd_tdc[i] = ssdcluster.Timing();
	  ssd_adc[i] = ssdcluster.PeakSum();
	  ssd_lx[i] = ssdcluster.CogPos();
	}//cluster loop
      }//ssd cluster bool

// GTR

      auto& gtr_hits1 = record->GTR().Hits();
      auto& gtr_clusters1 = record->GTR().Clusters();
      gtr_nh = gtr_hits1.size();
      gtr_nc = gtr_clusters1.size();

      //hits
      g100_nh = 0;
      g200_nh = 0;
      g300_nh = 0;
      if (gtr_hits1.size() != 0) {
	for(int i=0;i<gtr_nh;i++){//hit loop
	  auto& gtrhit = gtr_hits1[i];
	  if(gtrhit.LayerId()==0){
	    g100_nh++;
	  } else if(gtrhit.LayerId()==1){
	    g200_nh++;
	  } else if(gtrhit.LayerId()==2){
	    g300_nh++;
	  } else{
	  }
	}//hit loop
      }//gtr hit bool

      //clusters
      g100_nc = 0;
      g200_nc = 0;
      g300_nc = 0;
      if (gtr_clusters1.size() != 0) {
	for(int i=0;i<gtr_nc;i++){//cluster loop
	  auto& gtrcluster = gtr_clusters1[i];
	  if(gtrcluster.LayerId()==0){
	    g100_m[g100_nc] = gtrcluster.ModuleId();
	    g100_cs[g100_nc] = gtrcluster.NumHits();
	    g100_tdc[g100_nc] = gtrcluster.Timing();
	    g100_adc[g100_nc] = gtrcluster.PeakSum();
	    if(gtrcluster.IsX()){
	      g100_lx[g100_nc] = gtrcluster.CogPos();
	      g100_ly[g100_nc] = -1000;
	    }
	    else{
	      g100_lx[g100_nc] = -1000;
	      g100_ly[g100_nc] = gtrcluster.CogPos();
	    }
	    g100_nc++;
	  } else if(gtrcluster.LayerId()==1){
	    g200_m[g200_nc] = gtrcluster.ModuleId();
	    g200_cs[g200_nc] = gtrcluster.NumHits();
	    g200_tdc[g200_nc] = gtrcluster.Timing();
	    g200_adc[g200_nc] = gtrcluster.PeakSum();
	    if(gtrcluster.IsX()){
	      g200_lx[g200_nc] = gtrcluster.CogPos();
	      g200_ly[g200_nc] = -1000;
	    }
	    else{
	      g200_lx[g200_nc] = -1000;
	      g200_ly[g200_nc] = gtrcluster.CogPos();
	    }
	    g200_nc++;
	  } else if(gtrcluster.LayerId()==2){
	    g300_m[g300_nc] = gtrcluster.ModuleId();
	    g300_cs[g300_nc] = gtrcluster.NumHits();
	    g300_tdc[g300_nc] = gtrcluster.Timing();
	    g300_adc[g300_nc] = gtrcluster.PeakSum();
	    if(gtrcluster.IsX()){
	      g300_lx[g300_nc] = gtrcluster.CogPos();
	      g300_ly[g300_nc] = -1000;
	    }
	    else{
	      g300_lx[g300_nc] = -1000;
	      g300_ly[g300_nc] = gtrcluster.CogPos();
	    }
	    g300_nc++;
	  } else{
	  }

	}//cluster loop
      }//gtr cluster bool

// HBD

      auto& hbd_hits1 = record->HBD().Hits();
      auto& hbd_clusters1 = record->HBD().Clusters();
      hbd_nh = hbd_hits1.size();
      hbd_nc = hbd_clusters1.size();
      if (hbd_clusters1.size() != 0) {
	for(int i=0;i<hbd_nc;i++){//cluster loop
	  auto& hbdcluster = hbd_clusters1[i];
	  hbd_m[i] = hbdcluster.ModuleId();
	  hbd_cs[i] = hbdcluster.ClusterSize();
	  hbd_tdc[i] = hbdcluster.Timing();
	  hbd_adc[i] = hbdcluster.PeakSum();
	  hbd_lx[i] = hbdcluster.LocalPos().X();
	  hbd_ly[i] = hbdcluster.LocalPos().Y();
	  hbd_ise[i] = hbdcluster.IsE();
	}//cluster loop
      }//hbd cluster bool


// LG
      auto& lg_hits1 = record->LG().Hits();
      auto& lg_clusters1 = record->LG().Clusters();
      lg_nh = lg_hits1.size();
      lg_nc = lg_clusters1.size();
      if (lg_hits1.size() != 0) {
	for(int i=0;i<lg_nh;i++){//hit loop
	  auto& lghit = lg_hits1[i];
	  lg_m[i] = lghit.ModuleId();
	  lg_cs[i] = 1;
	  lg_tdc[i] = lghit.FitTiming();
	  lg_adc[i] = lghit.FitPeak();
	  lg_lx[i] = lghit.LocalPos(*geometry).X();
	  lg_ly[i] = lghit.LocalPos(*geometry).Y();
	  //hcs[5][c_mid(lg_m[i])]->Fill(lg_cs[i]);
	  //htd[5][c_mid(lg_m[i])]->Fill(lg_td[i]);
	  //had[5][c_mid(lg_m[i])]->Fill(lg_ad[i]);
	  //hlx[5][c_mid(lg_m[i])]->Fill(lg_lx[i]);
	  //hly[5][c_mid(lg_m[i])]->Fill(lg_ly[i]);
	}//hit loop
      }//lg hit bool

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
