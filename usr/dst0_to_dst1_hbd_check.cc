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

  int n_hits;
  int n_clusters;

  int h_module[HMAX];
  int h_ch[HMAX]; 
  float h_chi2[HMAX];
  float h_pe[HMAX];
  float h_tdc[HMAX];
  float h_pos[HMAX][3];
  
  int c_module[CMAX];
  int c_maxch[CMAX];
  float c_maxheight[CMAX];
  float c_tdc[CMAX];
  float c_adc[CMAX];
  float c_tdc_fastest[CMAX];
  float c_tdc_diff[CMAX];
  int c_size[CMAX];
  float c_pe[CMAX];
  float c_pos[CMAX][3];
  float c_cprob[CMAX];
  float c_eprob[CMAX];
  
  tree->Branch("event", &event, "event/I");

  tree->Branch("n_hits", &n_hits, "n_hits/I");
  tree->Branch("n_clusters", &n_clusters, "n_clusters/I");
  
  tree->Branch("h_module", h_module, "h_module[n_hits]/I");
  tree->Branch("h_ch", h_ch, "h_ch[n_hits]/I");
  tree->Branch("h_chi2", h_chi2, "h_chi2[n_hits]/F");
  tree->Branch("h_pe", h_pe, "h_pe[n_hits]/F");
  tree->Branch("h_tdc", h_tdc, "h_tdc[n_hits]/F");
  tree->Branch("h_pos", h_pos, "h_pos[n_hits][3]/F");

  tree->Branch("c_module", c_module, "c_module[n_clusters]/I");
  tree->Branch("c_maxch", c_maxch, "c_maxch[n_clusters]/I");
  tree->Branch("c_maxheight", c_maxheight, "c_maxheight[n_clusters]/F");
  tree->Branch("c_tdc", c_tdc, "c_tdc[n_clusters]/F");
  tree->Branch("c_adc", c_adc, "c_adc[n_clusters]/F");
  tree->Branch("c_tdc_fastest", c_tdc_fastest, "c_tdc_fastest[n_clusters]/F");
  tree->Branch("c_tdc_diff", c_tdc_diff, "c_tdc_diff[n_clusters]/F");
  tree->Branch("c_size", c_size, "c_size[n_clusters]/I");
  tree->Branch("c_pe", c_pe, "c_pe[n_clusters]/F");
  tree->Branch("c_pos", c_pos, "c_pos[n_clusters][3]/F");
  tree->Branch("c_cprob", c_cprob, "c_cprob[n_clusters]/F");
  tree->Branch("c_eprob", c_eprob, "c_eprob[n_clusters]/F");
  
  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
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
      auto& hbd_hits0         = event0->HBD();
      
      E16DST_DST1HBDFactory(hbd_hits0, hbd_calib, hbd_cut, wf1d_fitter, &record->HBD());
      event = event0->EventID();

      auto& hbd_hits1 = record->HBD().Hits();
      auto& hbd_clusters1 = record->HBD().Clusters();
      n_hits = hbd_hits1.size();
      n_clusters = hbd_clusters1.size();

      if(hbd_hits1.size() != 0){
	for(int i=0; i<n_hits; i++){
	  auto &hit = hbd_hits1[i];
	  h_module[i] = hit.ModuleId();
	  h_ch[i] = hit.ChannelId();
	  h_chi2[i] = hit.Chi2();
	  h_pe[i] = hit.PeakHeight();
	  h_tdc[i] = hit.Timing();
	  h_pos[i][0] = hit.LocalPos(*geometry).X();
	  h_pos[i][1] = hit.LocalPos(*geometry).Y();
	  h_pos[i][2] = hit.LocalPos(*geometry).Z();
	}
      }
      
      if(hbd_clusters1.size() != 0) {
	for(int i=0; i<n_clusters; i++){//cluster loop
	  auto& cluster = hbd_clusters1[i];
	  c_module[i] = cluster.ModuleId();
	  c_maxch[i] = cluster.MaxPeakCh();
	  c_tdc[i] = cluster.Timing();
	  c_adc[i] = cluster.SADC();
	  c_tdc_fastest[i] = cluster.FastestTiming();
	  c_tdc_diff[i] = cluster.TimeDifference();
	  c_size[i] = cluster.ClusterSize();
	  c_pe[i] = cluster.PeakSum();
	  c_pos[i][0] = cluster.LocalPos().X();
	  c_pos[i][1] = cluster.LocalPos().Y();
	  c_pos[i][2] = cluster.LocalPos().Z();
	  c_cprob[i] = cluster.IsChargedParticle();
	  c_eprob[i] = cluster.IsE();
	}//cluster loop
      }//hbd cluster bool
      
      tree->Fill();
      
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

  delete dst0;
  return 0;
}
