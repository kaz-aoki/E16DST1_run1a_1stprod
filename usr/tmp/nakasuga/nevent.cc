#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
// #include <boost/program_options.hpp>

// #include "E16ANA_CalibDBManager.hh"
// #include "E16ANA_GTRcalib.hh"
// #include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16DST_DST1DefaultFilePath.hh"
// #include "E16ANA_LGBasic.hh"
// #include "E16ANA_LGWaveform.hh"
// #include "E16ANA_LGConstant.hh"
// #include "E16ANA_LGDeadChannel.hh"
// #include "E16ANA_LGClustering.hh"
// #include "E16ANA_LGCheckHist.hh"
#include "E16DST_Constant.hh"

using namespace std;
// namespace  bpo = boost::program_options;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst0]" << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto max_event     = -1;

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
    // if (n_event % 1000 == 0) {
    //   cout << "Number of event: " << n_event << endl;
    // }
    // auto event_type = dst0->EventType();
    // if (event_type == E16DST_DST0EventType::Physics) {
    //   auto event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
    //   auto event_id = event0->EventID();
    // } else if (event_type == E16DST_DST0EventType::Scaler) {
    //   auto event0 = dynamic_cast<E16DST_DST0ScalerEvent*>(dst0->Event());
    //   // frun<<"Scaler: "<<event0->RunNumber()<<" "<<event0->SpillID()<<" "<<event0->EventIDInSpill()<<" "<<event0->EventID()<<" "<<event0->UnixTime()<<" "<<event0->TimeStamp()<<" "<<event0->TimeStampInSpill()<<std::endl;
    // } else if (event_type == E16DST_DST0EventType::SpillStart) {
    //   auto event0 = dynamic_cast<E16DST_DST0SpillStartEvent*>(dst0->Event());
    //   // frun<<"SpillS: "<<event0->RunNumber()<<" "<<event0->SpillID()<<" "<<event0->EventIDInSpill()<<" "<<event0->EventID()<<" "<<event0->UnixTime()<<" "<<event0->TimeStamp()<<" "<<event0->TimeStampInSpill()<<std::endl;
    // } else if (event_type == E16DST_DST0EventType::SpillEnd) {
    //   auto event0 = dynamic_cast<E16DST_DST0SpillEndEvent*>(dst0->Event());
    //   // frun<<"SpillE: "<<event0->RunNumber()<<" "<<event0->SpillID()<<" "<<event0->EventIDInSpill()<<" "<<event0->EventID()<<" "<<event0->UnixTime()<<" "<<event0->TimeStamp()<<" "<<event0->TimeStampInSpill()<<std::endl;
    // } else {
    //   std::cerr << "Invalid Event Type: " << event_type << std::endl;
    //   return -1;
    // }
    ++n_event;
    ++n_physics_event;
  }

  std::cout<<n_event<<std::endl;

  delete dst0;
//  dst1->Close();
  return 0;
}
