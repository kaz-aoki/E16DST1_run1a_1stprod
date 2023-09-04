#include <iostream>

#include "TChain.h"
#include "TString.h"
#include "tmp_fit_mock_pair_from_dst1_220618.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 6 && argc != 7) {
    cerr << "./bin input_header output.root vtx_z_flag mass_flag vertex_z_coefficient (max_events)" << endl;
    cerr << "vtx z flag" << endl;
    cerr << "  0: vtx z free, 1: vtx z = -20, 2: vtx z = 0, 3: vtx z = 20" << endl;
    cerr << "mass flag" << endl;
    cerr << "  0: e, e, 1: pi, pi" << endl;
    cerr << "vertex z coefficient = 0.: vertex z is free" << endl;
    return -1;
  }
  auto in_header  = static_cast<TString>(argv[1]);
  auto out_name   = static_cast<TString>(argv[2]);
  auto vtx_z_flag = stoi(argv[3]);
  auto mass_flag  = stoi(argv[4]);
  auto vtx_z_coef = stod(argv[5]);
  int max_events  = -1;
  if (argc == 7) {
    max_events = stoi(argv[6]);
  }

  auto in_chain = TChain("tree");
  in_chain.Add(in_header + "*");
  auto analyzer = tmp_fit_mock_pair_from_dst1_220618(&in_chain);
  analyzer.Loop(vtx_z_flag, mass_flag, vtx_z_coef, max_events, out_name);
  return 0;
}
