#include <iostream>
#include <boost/program_options.hpp>

//#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16DST_TriggerCoincidenceMap.hh"

using namespace std;
namespace  bpo = boost::program_options;

int main(int argc, char* argv[]) {
  if (argc != 5) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst0] [output.dst1] [run number] [max event]" << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  auto run_num       = stoi(argv[3]);
  auto max_event     = stoi(argv[4]);
  bpo::variables_map vm;
//  string in_file_name;
//  string out_file_name;
//  int run_num;
  array<string, 12> coincidence_map_files;
  array<string, 3>  trigger_channel_map_files;

//  bpo::options_description command_options("command options");
//  command_options.add_options()
//    ("in",                           bpo::value<string>(&in_file_name),                                                                "Input file name (string)\n")
//    ("out",                          bpo::value<string>(&out_file_name),                                                               "Output file name (string)\n")
//    ("coincidence-map-file-w-mag0",  bpo::value<string>(&coincidence_map_files[0])->default_value(string(CoincidenceMapWMagFile0)),    "Coincidence map file w/ mag 0 (string)\n");
//    ("coincidence-map-file-w-mag1",  bpo::value<string>(&coincidence_map_files[1])->default_value(string(CoincidenceMapWMagFile1)),    "Coincidence map file w/ mag 1 (string)\n");
//    ("coincidence-map-file-w-mag2",  bpo::value<string>(&coincidence_map_files[2])->default_value(string(CoincidenceMapWMagFile2)),    "Coincidence map file w/ mag 2 (string)\n");
//    ("coincidence-map-file-w-mag3",  bpo::value<string>(&coincidence_map_files[3])->default_value(string(CoincidenceMapWMagFile3)),    "Coincidence map file w/ mag 3 (string)\n");
//    ("coincidence-map-file-w-mag4",  bpo::value<string>(&coincidence_map_files[4])->default_value(string(CoincidenceMapWMagFile4)),    "Coincidence map file w/ mag 4 (string)\n");
//    ("coincidence-map-file-w-mag5",  bpo::value<string>(&coincidence_map_files[5])->default_value(string(CoincidenceMapWMagFile5)),    "Coincidence map file w/ mag 5 (string)\n");
//    ("coincidence-map-file-wo-mag0", bpo::value<string>(&coincidence_map_files[6])->default_value(string(CoincidenceMapWoMagFile0)),   "Coincidence map file w/o mag 0 (string)\n");
//    ("coincidence-map-file-wo-mag1", bpo::value<string>(&coincidence_map_files[7])->default_value(string(CoincidenceMapWoMagFile1)),   "Coincidence map file w/o mag 1 (string)\n");
//    ("coincidence-map-file-wo-mag2", bpo::value<string>(&coincidence_map_files[8])->default_value(string(CoincidenceMapWoMagFile2)),   "Coincidence map file w/o mag 2 (string)\n");
//    ("coincidence-map-file-wo-mag3", bpo::value<string>(&coincidence_map_files[9])->default_value(string(CoincidenceMapWoMagFile3)),   "Coincidence map file w/o mag 3 (string)\n");
//    ("coincidence-map-file-wo-mag4", bpo::value<string>(&coincidence_map_files[10])->default_value(string(CoincidenceMapWoMagFile4)),  "Coincidence map file w/o mag 4 (string)\n");
//    ("coincidence-map-file-wo-mag5", bpo::value<string>(&coincidence_map_files[11])->default_value(string(CoincidenceMapWoMagFile5)),  "Coincidence map file w/o mag 5 (string)\n");
//    ("trigger-gtr-channel-map",      bpo::value<string>(&trigger_channel_map_files[0])->default_value(string(TriggerChannelMapFile0)), "Trigger GTR channel map file (string)\n");
//    ("trigger-hbd-channel-map",      bpo::value<string>(&trigger_channel_map_files[1])->default_value(string(TriggerChannelMapFile1)), "Trigger HBD channel map file (string)\n");
//    ("trigger-lg-channel-map",       bpo::value<string>(&trigger_channel_map_files[2])->default_value(string(TriggerChannelMapFile2)), "Trigger LG channel map file (string)\n");
//
//  auto file_check = [&vm, &in_file_name, &out_file_name]() {
//    if (in_file_name.empty()) {
//      throw invalid_argument("Invalid input file name: "s + in_file_name);
//    }
//    if (out_file_name.empty()) {
//      throw invalid_argument("Invalid output file name: "s + out_file_name);
//    }
//  };
  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }
//  auto dst1 = new E16DST_DST1();
//  auto dst1 = new E16DST_DST0();
//  if (!dst1->Open(out_file_name, E16DST_DST0::WriteMode)) {
//    std::cerr << "Cannot open output file: " << out_file_name << std::endl;
//    return -1;
//   }
//  E16ANA_CalibDBManager& calib = E16ANA_CalibDBManager::Instance();
//  auto calib_file_name = calib.CalibFileName("SSD-pedestal", run_rum);
//  std::cout << calib_file_name << std::endl;
  int n_event = 0;
  while (dst0->ReadAnEvent()) {
    if (n_event >= max_event) {
      break;
    }
    if (n_event % 1000 == 0) {
      cout << "Number of event: " << n_event << endl;
    }
    auto event_type = dst0->EventType();
//    dst1->SetEventType(event_type);
    if (event_type == E16DST_DST0EventType::Physics) {
      auto event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
//      auto event1 = dynamic_cast<E16DST_DST1PhysicsEvent*>(dst1->Event());
      auto event1 = new E16DST_DST1PhysicsEvent();
      auto ssd_hits0         = event0->SSD();
      auto gtr_hits0         = event0->GTR();
      auto hbd_hits0         = event0->HBD();
      auto lg_hits0          = event0->LG();
      auto trigger_gtr_hits0 = event0->TriggerGTR();
      auto trigger_hbd_hits0 = event0->TriggerHBD();
      auto trigger_lg_hits0  = event0->TriggerLG();
      auto timestamp         = event0->TimeStamp();
//      E16DST_DST1SSDFactory(ssd_hits0, &event1->SSDHits(), &event1->SSDClusters());
//      E16DST_DST1GTRFactory(gtr_hits0, &event1->GTRHits(), &event1->GTRClusters()),
//      E16DST_DST1HBDFactory(hbd_hits0, &event1->HBDHits(), &event1->HBDClusters());
//      E16DST_DST1LGFactory(lg_hits0,   &event1->LGHits(),  &event1->LGClusters());
      E16DST_DST1TriggerFactory(event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), timestamp, &event1->Trigger());
      event1->Trigger().SetValidFlag(1);



      event1->Trigger().Print();
//      cout << "Event ID: " << n_event << endl;
//      auto max_track = event1->Trigger().TrackSets().NumberOfHits();
//      cout << "Number of tracks: " << max_track << endl;
//      cout << endl;
//      for (int n_track = 0; n_track < max_track; ++n_track) {
//        cout << "Track ID: " << n_track << endl;
//        auto track_set = event1->Trigger().TrackSets().Hit(n_track);
//        auto n_gtr_hits = track_set.NumGTRHits();
//        auto n_hbd_hits = track_set.NumHBDHits();
//        auto n_lg_hits = track_set.NumLGHits();
//        cout << "Number of tracked GTR: " << n_gtr_hits << endl;
//        cout << "Number of tracked HBD: " << n_hbd_hits << endl;
//        cout << "Number of tracked LG: " << n_lg_hits << endl;
//        for (int n_hit = 0; n_hit < n_gtr_hits; ++n_hit) {
//          auto order = track_set.GTRHitOrder(n_hit);
//          auto hit = event1->Trigger().GTRHits().Hit(order);
//          cout << "Tracked GTR hit: order = " << order << ", module = " << hit.ModuleId() << ", channel = " << hit.ChannelId() << endl;
//        }
//        for (int n_hit = 0; n_hit < n_hbd_hits; ++n_hit) {
//          auto order = track_set.HBDHitOrder(n_hit);
//          auto hit = event1->Trigger().HBDHits().Hit(order);
//          cout << "Tracked HBD hit: order = " << order << ", module = " << hit.ModuleId() << ", channel = " << hit.ChannelId() << endl;
//        }
//        if (track_set.NumLGHits() == 1) {
//          auto order = track_set.LGHitOrder(0);
//          auto hit = event1->Trigger().LGHits().Hit(order);
//          cout << "Tracked LG hit: order = " << order << ", module = " << hit.ModuleId() << ", channel = " << hit.ChannelId() << endl;
//        } else {
//          cerr << "Invalid number of LG Hits: " << track_set.NumLGHits() << endl;
//        }
//        cout << endl;
//      }
//      cout << endl;



//      dst1->WriteAnEvent();
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
  }
  delete dst0;
//  dst1->Close();
  return 0;
}
