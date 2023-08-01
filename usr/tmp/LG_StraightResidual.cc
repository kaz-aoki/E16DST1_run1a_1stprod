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

  if(argc!=4){
    std::cerr << "./bin [out.pdf] [out.root] [maxevent]" << std::endl;
    return -1;
  }
  auto out_pdf_name = argv[1];
  auto out_root_name = argv[2];
  auto maxevent = stoi(argv[3]);
   
  auto in_chain = new TChain("tree", "tree");
  in_chain->Add("/ccj/w/data06a/E16/user/nakasuga/output/run0dana/mergeroot/run040277.root");
  in_chain->Add("/ccj/w/data06a/E16/user/nakasuga/output/run0dana/mergeroot/run040278.root");
  // in_chain->Add("/ccj/w/data06a/E16/user/nakasuga/output/run0dana/mergeroot/run030400.root");

  E16ANA_LGStraightTrackRoot* t = new E16ANA_LGStraightTrackRoot(in_chain);
  t->Residual(out_pdf_name,out_root_name,maxevent);
  
  delete in_chain;
  return 0;

}
