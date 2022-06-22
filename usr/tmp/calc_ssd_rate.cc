#include <iostream>

#include "TFile.h"
#include "TH1.h"
#include "TTree.h"

#include "E16ANA_SSDcalib.hh"
#include "E16DST_DST0.hh"

using namespace std;
using namespace E16DST_Constant;

int main(int argc, char* argv[]) {
  if (argc != 5) {
    cerr << "./bin input.dst0 output.root run_ID max_events" << endl;
    return -1;
  }
  auto in_name    = static_cast<string>(argv[1]);
  auto out_name   = static_cast<TString>(argv[2]);
  auto run_id     = stoi(argv[3]);
  auto max_events = stoi(argv[4]);

  auto dst0 = E16DST_DST0();
  dst0.Open(in_name, E16DST_DST0::ReadMode);
  
  auto ssd_pedestal = E16ANA_SSDcalibPedestal();
  ssd_pedestal.ReadCalibData(run_id);

  auto out_file = TFile(out_name, "recreate");
  auto out_tree = TTree("tree", "tree");
  int event_id;
  vector<int> module_id;
  vector<int> channel_id;
  vector<int> max_t;
  vector<int> max_adc;
  vector<vector<double>> wave_form;
  out_tree.Branch("event_id",   &event_id, "event_id/I");
  out_tree.Branch("channel_id", &channel_id);
  out_tree.Branch("max_t",      &max_t);
  out_tree.Branch("max_adc",    &max_adc);
  out_tree.Branch("wave_form",  &wave_form);
  auto h_ssd_ped_diff   = TH1F("h_ssd_ped_diff",   "h_ssd_ped_diff",   1500, 0., 150.);
  auto h_ssd_sigma_diff = TH1F("h_ssd_sigma_diff", "h_ssd_sigma_diff", 1500, 0., 150.);

  for (int m = 0; m < 6; ++m) {
    for (int cid = 0; cid < 768; ++cid) {
      double min_ped = 10000.;
      double max_ped = -10000.;
      for (int j = 0; j < NSamplesSSD; ++j) {
        auto ped = ssd_pedestal.Pedestal(m, cid, j);
        if (ped < min_ped) {
          min_ped = ped;
        }
        if (ped > max_ped) {
          max_ped = ped;
        }
      }
      h_ssd_ped_diff.Fill(max_ped - min_ped);
    }
  }

  int n_events = 0;
  while (dst0.ReadAnEvent()) {
    if (n_events % 1000 == 0) {
      cout << "event: " << n_events << endl;
    }
    ++n_events;
    if (max_events > 0 && n_events > max_events) {
      break;
    }
    auto event_type = dst0.EventType();
    if (event_type != E16DST_DST0EventType::Physics) {
      continue;
    }
    auto event = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0.Event());
    auto& ssd = event->SSD();
    module_id.clear();
    channel_id.clear();
    max_t.clear();
    max_adc.clear();
    auto n_hits = ssd.NumberOfHits();
    wave_form.resize(n_hits);
    for (int i = 0; i < n_hits; ++i) {
      auto& hit = ssd.Hit(i);
      auto mid = hit.ModuleID();
      auto cid = hit.ChannelID();
      module_id.emplace_back(mid);
      channel_id.emplace_back(cid);
      wave_form[i].resize(NSamplesSSD);
      auto wf = hit.Waveform();
      int    tmp_t;
      double tmp_adc = -1000.;
      int m;
      if (mid < 105) {
        m = mid - 102;
      } else {
        m = mid - 103;
      }
//      if (cid == 0 || cid == 127 || cid == 128 || cid == 255 || cid == 256 || cid == 383 || cid == 384 || cid == 511 || cid == 512 || cid == 639 || cid == 640 || cid == 767 ||
//          (mid==108 && cid > 127 && cid < 256) {
//      } else if (get_max(hit.Waveform()) > 950 || get_min(hit.Waveform()) < 100 || get_dev(hit.Waveform()) < 100 || get_mode(hit.Waveform()) >= 3) {
//      }
      for (int j = 0; j < NSamplesSSD; ++j) {
//if (ssd_pedestal.Pedestal(m, cid, j) != 0) {
//  cout << ssd_pedestal.Pedestal(m, cid, j) << endl;
//  cout << ssd_pedestal.Sigma(m, cid, j) << endl;
//}
        wave_form[i][j] = wf[j] - ssd_pedestal.Pedestal(m, cid, j);
        if (wave_form[i][j] > tmp_adc) {
          tmp_t = j;
          tmp_adc = wave_form[i][j];
        }
      }
      max_t.emplace_back(tmp_t);
      max_adc.emplace_back(tmp_adc);
    }
    out_tree.Fill();
  }
  out_file.Write();
  return 0;
}
