#include "E16ANA_LGStraightTrackRoot.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>

#include <TH1.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "TROOT.h"

int main(int argc, char* argv[]) {

  // auto runtype = stoi(argv[1]);
  // auto out_file_name = argv[2];
  // auto out_root_name = argv[3];
  // auto maxevent = stoi(argv[4]);
  // if(argc==5){
  //   std::cerr << "./bin [Ks:0, vmeson:1, eIDrev:3, eIDfwd:4] [out.pdf] [out.root] [maxevent]" << std::endl;
  //   return -1;
  // }
   
  auto in_chain = new TChain("tree", "tree");
  in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/test.root");

  E16ANA_LGStraightTrackRoot* t = new E16ANA_LGStraightTrackRoot(in_chain);
  t->Residual();
  
  delete in_chain;
  return 0;

}
