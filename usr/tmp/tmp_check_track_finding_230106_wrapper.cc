#include <iostream>

#include "TChain.h"
#include "TROOT.h"
#include "TString.h"

#include "tmp_check_track_finding_230106.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 4) {
    cerr << "./bin input_header output.root smear_coefficient" << endl;
    return -1;
  }
  auto in_name    = TString(argv[1]);
  auto out_name   = TString(argv[2]);
  auto smear_coef = stod(argv[3]);
  gROOT->ProcessLine(".x ~/.rootlogon.C");

  auto chain = TChain("tree");
  chain.Add(in_name + "*");
  auto analyzer = tmp_check_track_finding_230106(&chain);
  analyzer.Loop(smear_coef, out_name);
  return 0;
}
