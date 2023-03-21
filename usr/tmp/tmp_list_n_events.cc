#include <array>
#include <iostream>

#include "TString.h"

#include "E16DST_DST0.hh"

using namespace std;

constexpr array<int, 2> kRunIDs = {30717, 30778};
const string kDST0Name = "/ccj/w/data06z/E16/Run0c/prod-1/dst0/all-OK/";

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "./bin output.txt" << endl;
    return -1;
  }
  auto out_name = TString(argv[1]);

  auto out_text = ofstream();
  out_text.open(out_name);
  for (int run_id = kRunIDs[0]; run_id <= kRunIDs[1]; ++run_id) {
    cout << "run ID: " << run_id << endl;
    for (int sink_id = 0; sink_id < 3; ++sink_id) {
      for (int data_id = 0; true; ++data_id) {
        auto in_name = string(kDST0Name + Form("all-run%06d_sink%d_%03d.dst0", run_id, sink_id, data_id));
        FILE* fp = fopen(in_name.c_str(), "r");
        if (!fp) {
          cerr << "Cannot find file: " << in_name << endl;
          break;
        }
        fclose(fp);
        auto dst0 = new E16DST_DST0();
        if (!dst0->Open(in_name, E16DST_DST0::ReadMode)) {
          cerr << "Cannot open DST0 file: " << in_name << endl;
          break;
        }
        int n_events = 0;
        while (dst0->ReadAnEvent()) {
          if (n_events % 1000 == 0) {
            cout << in_name << ": " << n_events << endl;
          }
          ++n_events;
        }
        out_text << in_name << " " << n_events << endl;
        delete dst0;
      }
    }
  }
  
  return 0;
}
