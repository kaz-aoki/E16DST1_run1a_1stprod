#include <iostream>

#include "TChain.h"
#include "TString.h"
#include "tmp_check_pos_smear_220627.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3 && argc != 4) {
    cerr << "./bin input_header output_header (max_events)" << endl;
    return -1;
  }
  auto in_header = static_cast<TString>(argv[1]);
  auto out_name  = static_cast<TString>(argv[2]);
  int max_events = -1;
  if (argc == 4) {
    max_events = stoi(argv[3]);
  }

  auto in_chain = TChain("tree");
  in_chain.Add(in_header + "*");
  auto analyzer = tmp_check_pos_smear_220627(&in_chain);
  analyzer.Loop(max_events, out_name);
  return 0;
}
