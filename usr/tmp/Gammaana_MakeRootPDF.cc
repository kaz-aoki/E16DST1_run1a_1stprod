#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TRandom.h>
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
#include "E16ANA_LGCheckHist.hh"
#include "E16ANA_Massw2Gamma.hh"
#include "E16ANA_GammaAnalyzer.hh"
#include "E16DST_Constant.hh"

using namespace std;
// namespace  bpo = boost::program_options;

#define TRG_ON

int main(int argc, char* argv[]) {
  if (argc != 6) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst0] [output.root] [output.pdf] [run ID] [max physics event (all: -1)] " << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  auto out_pdf_name = argv[3];
  auto run_id        = stoi(argv[4]);
  auto max_event     = stoi(argv[5]);

  TFile* fout = new TFile(out_file_name,"recreate");

  auto *analyzer = new E16ANA_GammaAnalyzer();

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

  // E16ANA_GTRcalibPedestal gtrped;
  // gtrped.ReadCalibData( calib.CurrentRunID() );
  E16ANA_LGBasic lgbasic;
  E16ANA_LGDeadChannel lgdead;
  lgbasic.SetMap();
  lgbasic.SetCalibMap();//it is necessary to use energy deposit and calibrated timing.
  lgbasic.SetTemplate();
  lgdead.ReadDeadChannelData();

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  E16ANA_GeometryV2::SetGlobalPointer(geometry);
  
  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }
  E16DST_DST1PhysicsRecord record;

  // E16ANA_GTRPedestal *gtr_pedestal = new E16ANA_GTRPedestal();
  // gtr_pedestal->Read(argv[5]);
  // auto dst1 = new E16DST_DST1();
  // auto dst1 = new E16DST_DST0();
  // if (!dst1->Open(out_file_name, E16DST_DST0::WriteMode)) {
  //   std::cerr << "Cannot open output file: " << out_file_name << std::endl;
  //   return -1;
  // }

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
      // std::cout<<event0->LG().NumberOfHits()<<" "<<event0->TriggerLG().NumberOfHits()<<std::endl;
      auto event_id = event0->EventID();

      E16DST_DST1LGFactory(lg_hits0, &record.LG(), 2, geometry); // w/ fit
      record.LG().AddHitAndClusterIds();
      record.LG().UpdatePtrs();
#ifdef TRG_ON
      E16DST_DST1TriggerFactory(trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record.Trigger());
      record.Trigger().AddHitAndClusterIDs();
      record.Trigger().UpdatePtrs();
#endif

//// Check begin

//dst1_lg_hit

      auto& lg_hits1 = record.LG().Hits();
      int n_lghits = lg_hits1.size();
      int ihit[2] = {0, 0};
      for(ihit[0]=0; ihit[0]<n_lghits; ihit[0]++){
	auto& lghit0 = lg_hits1[ihit[0]];
	auto lpos0 = lghit0.LocalPos(*geometry);
	auto gpos0 = lghit0.GlobalPos(*geometry);
	analyzer->ClearHit0();
	analyzer->SetHit0(lghit0.HitId(), lghit0.ModuleId(), lghit0.ChannelId(), lpos0.X(), lpos0.Y(), lpos0.Z(), gpos0.X(), gpos0.Y(), gpos0.Z(), lghit0.FitPeak(), lghit0.FitTiming(), lghit0.FitFlag());
	if( analyzer->Hit0isInvalid() ) continue;

      	for(ihit[1]=ihit[0]+1; ihit[1]<n_lghits; ihit[1]++){
	  auto& lghit1 = lg_hits1[ihit[1]];
	  auto lpos1 = lghit1.LocalPos(*geometry);
	  auto gpos1 = lghit1.GlobalPos(*geometry);
	  analyzer->ClearHit1();
	  analyzer->SetHit1(lghit1.HitId(), lghit1.ModuleId(), lghit1.ChannelId(), lpos1.X(), lpos1.Y(), lpos1.Z(), gpos1.X(), gpos1.Y(), gpos1.Z(), lghit1.FitPeak(), lghit1.FitTiming(), lghit0.FitFlag());
	  if( analyzer->Hit1isInvalid() ) continue;
	  if( analyzer->HitsareInvalid() ) continue;

      	  //calc im
	  analyzer->FillForeHist();

      	  //calc mix im
	  analyzer->FillMixHist();
      	}
      }

      //set mixhits
      analyzer->ClearMixEvent();
      for(int jhit=0;jhit<n_lghits;jhit++){
      	auto& lghit = lg_hits1[jhit];
      	auto lpos = lghit.LocalPos(*geometry);
      	auto gpos = lghit.GlobalPos(*geometry);
      	E16ANA_GammaAnalyzer::hitset hit;
      	analyzer->SetHit(hit, lghit.HitId(), lghit.ModuleId(), lghit.ChannelId(), lpos.X(), lpos.Y(), lpos.Z(), gpos.X(), gpos.Y(), gpos.Z(), lghit.FitPeak(), lghit.FitTiming(), lghit.FitFlag());
      	if( analyzer->HitisInvalid( hit ) ) continue;
      	analyzer->PushBackMixHit( hit );
      }
      analyzer->PushBackMixEvent();

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

  TString fsout = Form("%s",out_pdf_name);
  TCanvas* c = new TCanvas("c","c",1000,700);
  c->SaveAs(fsout+"[","pdf");
  analyzer->Draw(fsout,c);
  c->SaveAs(fsout+"]","pdf");

  fout->Write();
  fout->Close();

  delete geometry;
  delete dst0;
  //  dst1->Close();
  return 0;
}
