#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
// #include <boost/program_options.hpp>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"
#include "E16ANA_LGConstant.hh"
#include "E16ANA_LGDeadChannel.hh"
#include "E16ANA_LGClustering.hh"
#include "E16ANA_LGStraightProj.hh"
#include "straightRoot.hh"
#include "E16DST_Constant.hh"

using namespace std;
// namespace  bpo = boost::program_options;

#define TRG_ON

int main(int argc, char* argv[]) {
  if (argc != 6) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst0] [input.root] [output.root] [run ID] [max physics event (all: -1)] " << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto in_st_file_name  = argv[2];
  auto out_file_name = argv[3];
  auto run_id        = stoi(argv[4]);
  auto max_event     = stoi(argv[5]);

  //straight
  auto in_chain = new TChain("tree", "tree");
  // in_chain->Add("/ccj/w/data06a/E16/user/nakasuga/output/straightroot/murakami/out_all_nakasuga.root");
  in_chain->Add(in_st_file_name);
  straightRoot* t = new straightRoot(in_chain);
  t->MakeMap(run_id,-1);

  E16ANA_LGStraightProj proj;

  //out root
  TFile *fout = new TFile(out_file_name,"recreate");
  TTree *tree = new TTree("tree","tree");

  Int_t out_run_id;
  Int_t out_event_id;
  Int_t out_spill_id;
  int out_n_tracks;
  vector<double> out_trk_initpos_x;
  vector<double> out_trk_initpos_y;
  vector<double> out_trk_initpos_z;
  vector<double> out_trk_initdir_x;
  vector<double> out_trk_initdir_y;
  vector<double> out_trk_initdir_z;
  vector<int> out_trk_mid;
  vector<int> out_trk_cid;
  vector<double> out_trk_lx;
  vector<double> out_trk_ly;
  vector<double> out_trk_timing_100x;
  vector<double> out_trk_timing_100y;
  vector<double> out_trk_timing_200x;
  vector<double> out_trk_timing_200y;
  vector<double> out_trk_timing_300x;
  vector<double> out_trk_timing_300y;
  vector<double> out_trk_timing2_100x;
  vector<double> out_trk_timing2_100y;
  vector<double> out_trk_timing2_200x;
  vector<double> out_trk_timing2_200y;
  vector<double> out_trk_timing2_300x;
  vector<double> out_trk_timing2_300y;
  vector<double> out_trk_residual_100x;
  vector<double> out_trk_residual_100y;
  vector<double> out_trk_residual_200x;
  vector<double> out_trk_residual_200y;
  vector<double> out_trk_residual_300x;
  vector<double> out_trk_residual_300y;
  vector<double> out_trk_chi2_x;
  vector<double> out_trk_chi2_y;
  vector<double> out_trk_tgt_z;
  int out_n_lg_hits;
  vector<int> out_lg_mid;
  vector<int> out_lg_cid;
  vector<double> out_lg_lx;
  vector<double> out_lg_ly;
  vector<double> out_lg_adc;
  vector<double> out_lg_calibadc;
  vector<double> out_lg_t;
  vector<int> out_lg_fflag;
  int out_n_lg_trg_hits;
  vector<int> out_lg_trg_mid;
  vector<int> out_lg_trg_cid;
  vector<float> out_lg_trg_t;
  vector<bool> out_lg_trg;
  vector<bool> out_lg_trg_trk;

  tree->Branch("run_id",&out_run_id,"run_id/I");
  tree->Branch("event_id",&out_event_id,"event_id/I");
  tree->Branch("spill_id",&out_spill_id,"spill_id/I");
  tree->Branch("n_tracks",&out_n_tracks,"n_tracks/I");
  tree->Branch("trk_initpos_x", &out_trk_initpos_x);
  tree->Branch("trk_initpos_y", &out_trk_initpos_y);
  tree->Branch("trk_initpos_z", &out_trk_initpos_z);
  tree->Branch("trk_initdir_x", &out_trk_initdir_x);
  tree->Branch("trk_initdir_y", &out_trk_initdir_y);
  tree->Branch("trk_initdir_z", &out_trk_initdir_z);
  tree->Branch("trk_mid", &out_trk_mid);
  tree->Branch("trk_cid", &out_trk_cid);
  tree->Branch("trk_lx", &out_trk_lx);
  tree->Branch("trk_ly", &out_trk_ly);
  tree->Branch("trk_timing_100x", &out_trk_timing_100x);
  tree->Branch("trk_timing_100y", &out_trk_timing_100y);
  tree->Branch("trk_timing_200x", &out_trk_timing_200x);
  tree->Branch("trk_timing_200y", &out_trk_timing_200y);
  tree->Branch("trk_timing_300x", &out_trk_timing_300x);
  tree->Branch("trk_timing_300y", &out_trk_timing_300y);
  tree->Branch("trk_timing2_100x", &out_trk_timing2_100x);
  tree->Branch("trk_timing2_100y", &out_trk_timing2_100y);
  tree->Branch("trk_timing2_200x", &out_trk_timing2_200x);
  tree->Branch("trk_timing2_200y", &out_trk_timing2_200y);
  tree->Branch("trk_timing2_300x", &out_trk_timing2_300x);
  tree->Branch("trk_timing2_300y", &out_trk_timing2_300y);
  tree->Branch("trk_residual_100x", &out_trk_residual_100x);
  tree->Branch("trk_residual_100y", &out_trk_residual_100y);
  tree->Branch("trk_residual_200x", &out_trk_residual_200x);
  tree->Branch("trk_residual_200y", &out_trk_residual_200y);
  tree->Branch("trk_residual_300x", &out_trk_residual_300x);
  tree->Branch("trk_residual_300y", &out_trk_residual_300y);
  tree->Branch("trk_chi2_x", &out_trk_chi2_x);
  tree->Branch("trk_chi2_y", &out_trk_chi2_y);
  tree->Branch("trk_tgt_z", &out_trk_tgt_z);
  tree->Branch("n_lg_hits",&out_n_lg_hits,"n_lg_hits/I");
  tree->Branch("lg_mid", &out_lg_mid);
  tree->Branch("lg_cid", &out_lg_cid);
  tree->Branch("lg_lx", &out_lg_lx);
  tree->Branch("lg_ly", &out_lg_ly);
  tree->Branch("lg_adc", &out_lg_adc);
  tree->Branch("lg_calibadc", &out_lg_calibadc);
  tree->Branch("lg_t", &out_lg_t);
  tree->Branch("lg_fflag", &out_lg_fflag);
  tree->Branch("n_lg_trg_hits",&out_n_lg_trg_hits,"n_lg_trg_hits/I");
  tree->Branch("lg_trg_mid", &out_lg_trg_mid);
  tree->Branch("lg_trg_cid", &out_lg_trg_cid);
  tree->Branch("lg_trg_t", &out_lg_trg_t);
  tree->Branch("lg_trg", &out_lg_trg);
  tree->Branch("lg_trg_trk", &out_lg_trg_trk);

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
#ifdef TRG_ON
  E16ANA_TriggerCalibParam trigger_param;
  trigger_param.ReadConstantData(calib.CurrentRunID());
  bool TrigIsAWmax = trigger_param.IsMaximumWidth();
  int TrigAWmax = trigger_param.MaximumWidth();
  int TrigAWmin = trigger_param.MinimumWidth();
  int TrigTW = trigger_param.TimeWidth();
  if(!TrigIsAWmax){TrigAWmax=10000;}
  std::cout<<TrigIsAWmax<<" "<<TrigAWmax<<" "<<TrigAWmin<<" "<<TrigTW<<std::endl;
#else
  bool TrigIsAWmax = false;
  int TrigAWmax = -10000;
  int TrigAWmin = -10000;
  int TrigTW = -10000;
#endif

  E16ANA_LGBasic lgbasic;
  E16ANA_LGDeadChannel lgdead;
  lgbasic.SetMap();
  lgbasic.SetCalibMap();//it is necessary to use energy deposit and calibrated timing.
  lgbasic.SetTemplate();
  lgdead.ReadDeadChannelData();

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  
  // auto record = new E16DST_DST1PhysicsRecord();
  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }
  E16DST_DST1PhysicsRecord record;

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
    if (event_type == E16DST_DST0EventType::Physics) {
      auto event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
      // auto& ssd_hits0         = event0->SSD();
      // auto& gtr_hits0         = event0->GTR();
      // auto& hbd_hits0         = event0->HBD();
      auto& lg_hits0          = event0->LG();
      auto& trigger_gtr_hits0 = event0->TriggerGTR();
      auto& trigger_hbd_hits0 = event0->TriggerHBD();
      auto& trigger_lg_hits0  = event0->TriggerLG();
      auto event_id = event0->EventID();

      E16DST_DST1LGFactory(lg_hits0, &record.LG(), 2, geometry); // w/ fit
      record.LG().AddHitAndClusterIds();
      record.LG().UpdatePtrs();
#ifdef TRG_ON
#ifdef TMP_NIM_TRIGGER
      auto time_stamp = event0->TimeStamp();
      E16DST_DST1TriggerFactory(time_stamp, trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record.Trigger());
#else // TMP_NIM_TRIGGER
      E16DST_DST1TriggerFactory(trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record.Trigger());
#endif // TMP_NIM_TRIGGER
      record.Trigger().AddHitAndClusterIDs();
      record.Trigger().UpdatePtrs();
#endif

//// Check begin

      out_trk_initpos_x.clear();
      out_trk_initpos_y.clear();
      out_trk_initpos_z.clear();
      out_trk_initdir_x.clear();
      out_trk_initdir_y.clear();
      out_trk_initdir_z.clear();
      out_trk_mid.clear();
      out_trk_cid.clear();
      out_trk_lx.clear();
      out_trk_ly.clear();
      out_trk_timing_100x.clear();
      out_trk_timing_100y.clear();
      out_trk_timing_200x.clear();
      out_trk_timing_200y.clear();
      out_trk_timing_300x.clear();
      out_trk_timing_300y.clear();
      out_trk_timing2_100x.clear();
      out_trk_timing2_100y.clear();
      out_trk_timing2_200x.clear();
      out_trk_timing2_200y.clear();
      out_trk_timing2_300x.clear();
      out_trk_timing2_300y.clear();
      out_trk_residual_100x.clear();
      out_trk_residual_100y.clear();
      out_trk_residual_200x.clear();
      out_trk_residual_200y.clear();
      out_trk_residual_300x.clear();
      out_trk_residual_300y.clear();
      out_trk_chi2_x.clear();
      out_trk_chi2_y.clear();
      out_trk_tgt_z.clear();
      out_lg_mid.clear();
      out_lg_cid.clear();
      out_lg_lx.clear();
      out_lg_ly.clear();
      out_lg_adc.clear();
      out_lg_calibadc.clear();
      out_lg_t.clear();
      out_lg_fflag.clear();
      out_lg_trg_mid.clear();
      out_lg_trg_cid.clear();
      out_lg_trg_t.clear();
      out_lg_trg.clear();
      out_lg_trg_trk.clear();

//run
      out_run_id = run_id;
      out_event_id = event0->EventID();
      out_spill_id = event0->SpillID();

//// LG
      auto& lg_hits1 = record.LG().Hits();
      int n_lghits = lg_hits1.size();
      int n_lg_hits = 0;
      if (lg_hits1.size() != 0) {
      	for(int i=0;i<n_lghits;i++){
      	  auto& lghit = lg_hits1[i];
	  if( lghit.FitFlag()<2 ){
	    int lg_mid = lghit.ModuleId();
	    int lg_cid = lghit.ChannelId();
	    auto lpos = lghit.LocalPos(*geometry);
	    double lg_lx = lpos.X();
	    double lg_ly = lpos.Y();
	    double lg_adc = lghit.FitPeak();
	    double gainparam = lgbasic.GetGain(lg_mid, lg_cid);
	    double lg_calibadc = lghit.FitPeak()*gainparam;
	    double lg_t = lghit.FitTiming();
	    int lg_fflag = lghit.FitFlag();
	    out_lg_mid.push_back(lg_mid);
	    out_lg_cid.push_back(lg_cid);
	    out_lg_lx.push_back(lg_lx);
	    out_lg_ly.push_back(lg_ly);
	    out_lg_adc.push_back(lg_adc);
	    out_lg_calibadc.push_back(lg_calibadc);
	    out_lg_t.push_back(lg_t);
	    out_lg_fflag.push_back(lg_fflag);
	    n_lg_hits++;
	  }
      	}
      }
      out_n_lg_hits = n_lg_hits;

//// Trg
      int n_trg_lg_hits = record.Trigger().NumLGHits();
      int n_lg_trg_hits = 0;
      for(int itrg=0;itrg<n_trg_lg_hits;itrg++){
      	auto& trghit = record.Trigger().LGHit(itrg);
      	int trg_mid = trghit.ModuleId();
      	int trg_cid = trghit.ChannelId();
      	double trg_t = trghit.Timing();
      	// if( trg_t>3050 && trg_t<3200 ){
      	  out_lg_trg_mid.push_back(trg_mid);
      	  out_lg_trg_cid.push_back(trg_cid);
      	  out_lg_trg_t.push_back(trg_t);
      	  n_lg_trg_hits++;
      	// }
      }
      out_n_lg_trg_hits = n_lg_trg_hits;

//// Track
      t->SetEntry(out_event_id);
      std::vector<TVector3> initposs;
      std::vector<TVector3> initdirs;
      std::vector<double> timing_100x;
      std::vector<double> timing_100y;
      std::vector<double> timing_200x;
      std::vector<double> timing_200y;
      std::vector<double> timing_300x;
      std::vector<double> timing_300y;
      std::vector<double> timing2_100x;
      std::vector<double> timing2_100y;
      std::vector<double> timing2_200x;
      std::vector<double> timing2_200y;
      std::vector<double> timing2_300x;
      std::vector<double> timing2_300y;
      std::vector<double> residual_100x;
      std::vector<double> residual_100y;
      std::vector<double> residual_200x;
      std::vector<double> residual_200y;
      std::vector<double> residual_300x;
      std::vector<double> residual_300y;
      std::vector<double> chi2_x;
      std::vector<double> chi2_y;
      std::vector<double> tgt_z;
      t->GetInitPos(initposs);
      t->GetInitDir(initdirs);
      t->GetTiming100X(timing_100x);
      t->GetTiming100Y(timing_100y);
      t->GetTiming200X(timing_200x);
      t->GetTiming200Y(timing_200y);
      t->GetTiming300X(timing_300x);
      t->GetTiming300Y(timing_300y);
      t->GetTiming2100X(timing2_100x);
      t->GetTiming2100Y(timing2_100y);
      t->GetTiming2200X(timing2_200x);
      t->GetTiming2200Y(timing2_200y);
      t->GetTiming2300X(timing2_300x);
      t->GetTiming2300Y(timing2_300y);
      t->GetResidual100X(residual_100x);
      t->GetResidual100Y(residual_100y);
      t->GetResidual200X(residual_200x);
      t->GetResidual200Y(residual_200y);
      t->GetResidual300X(residual_300x);
      t->GetResidual300Y(residual_300y);
      t->GetChi2X(chi2_x);
      t->GetChi2Y(chi2_y);
      t->GetTgtZ(tgt_z);
      int n_trk = 0;
      for(int itrack=0; itrack<t->Ntracks(); itrack++){
	TVector3 tinitpos = initposs.at(itrack);
	TVector3 tinitdir = initdirs.at(itrack);
	proj.SetInitInfo(tinitpos,tinitdir);
	if( proj.CalcCrossInfo() ){
	  out_trk_initpos_x.push_back( tinitpos.X() );
	  out_trk_initpos_y.push_back( tinitpos.Y() );
	  out_trk_initpos_z.push_back( tinitpos.Z() );
	  out_trk_initdir_x.push_back( tinitdir.X() );
	  out_trk_initdir_y.push_back( tinitdir.Y() );
	  out_trk_initdir_z.push_back( tinitdir.Z() );
	  out_trk_mid.push_back( proj.Module() );
	  out_trk_cid.push_back( proj.Block() );
	  out_trk_lx.push_back( proj.LCross1_x() );
	  out_trk_ly.push_back( proj.LCross1_y() );
	  out_trk_timing_100x.push_back( timing_100x.at(itrack) );
	  out_trk_timing_100y.push_back( timing_100y.at(itrack) );
	  out_trk_timing_200x.push_back( timing_200x.at(itrack) );
	  out_trk_timing_200y.push_back( timing_200y.at(itrack) );
	  out_trk_timing_300x.push_back( timing_300x.at(itrack) );
	  out_trk_timing_300y.push_back( timing_300y.at(itrack) );
	  out_trk_timing2_100x.push_back( timing2_100x.at(itrack) );
	  out_trk_timing2_100y.push_back( timing2_100y.at(itrack) );
	  out_trk_timing2_200x.push_back( timing2_200x.at(itrack) );
	  out_trk_timing2_200y.push_back( timing2_200y.at(itrack) );
	  out_trk_timing2_300x.push_back( timing2_300x.at(itrack) );
	  out_trk_timing2_300y.push_back( timing2_300y.at(itrack) );
	  out_trk_residual_100x.push_back( residual_100x.at(itrack) );
	  out_trk_residual_100y.push_back( residual_100y.at(itrack) );
	  out_trk_residual_200x.push_back( residual_200x.at(itrack) );
	  out_trk_residual_200y.push_back( residual_200y.at(itrack) );
	  out_trk_residual_300x.push_back( residual_300x.at(itrack) );
	  out_trk_residual_300y.push_back( residual_300y.at(itrack) );
	  out_trk_chi2_x.push_back( chi2_x.at(itrack) );
	  out_trk_chi2_y.push_back( chi2_y.at(itrack) );
	  out_trk_tgt_z.push_back( tgt_z.at(itrack) );
	  n_trk++;
	}
      }
      out_n_tracks = n_trk;

      tree->Fill();

    } else if (event_type == E16DST_DST0EventType::Scaler) {
      auto event0 = dynamic_cast<E16DST_DST0ScalerEvent*>(dst0->Event());
      // frun<<"Scaler: "<<event0->RunNumber()<<" "<<event0->SpillID()<<" "<<event0->EventIDInSpill()<<" "<<event0->EventID()<<" "<<event0->UnixTime()<<" "<<event0->TimeStamp()<<" "<<event0->TimeStampInSpill()<<std::endl;
//      dst1->WriteAnEvent(event0);
    } else if (event_type == E16DST_DST0EventType::SpillStart) {
      auto event0 = dynamic_cast<E16DST_DST0SpillStartEvent*>(dst0->Event());
      // frun<<"SpillS: "<<event0->RunNumber()<<" "<<event0->SpillID()<<" "<<event0->EventIDInSpill()<<" "<<event0->EventID()<<" "<<event0->UnixTime()<<" "<<event0->TimeStamp()<<" "<<event0->TimeStampInSpill()<<std::endl;
//      dst1->WriteAnEvent(event0);
    } else if (event_type == E16DST_DST0EventType::SpillEnd) {
      auto event0 = dynamic_cast<E16DST_DST0SpillEndEvent*>(dst0->Event());
      // frun<<"SpillE: "<<event0->RunNumber()<<" "<<event0->SpillID()<<" "<<event0->EventIDInSpill()<<" "<<event0->EventID()<<" "<<event0->UnixTime()<<" "<<event0->TimeStamp()<<" "<<event0->TimeStampInSpill()<<std::endl;
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
  delete in_chain;
//  dst1->Close();
  return 0;
}
