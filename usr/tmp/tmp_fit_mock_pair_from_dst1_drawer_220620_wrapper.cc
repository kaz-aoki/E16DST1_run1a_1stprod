#include <iostream>

#include "TChain.h"
#include "TROOT.h"
#include "TString.h"
#include "tmp_fit_mock_pair_from_dst1_drawer_220620.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "./bin input_header output_header" << endl;
    return -1;
  }
  auto in_name  = static_cast<TString>(argv[1]);
  auto out_name = static_cast<TString>(argv[2]);
  gROOT->ProcessLine(".x ~/.rootlogon.C");

  auto in_chain = TChain("tree");
  in_chain.Add(in_name + "*");
  auto analyzer = tmp_fit_mock_pair_from_dst1_drawer_220620(&in_chain);
  analyzer.Loop(out_name);
  return 0;
}
