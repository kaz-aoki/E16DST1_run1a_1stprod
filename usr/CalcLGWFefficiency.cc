#include "SingleTrackAnalyzerForRes.hh"
#include "E16ANA_LGClustering.hh"
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

   if ( argc<6||argc>7 ) {
     std::cerr << "./bin [runNo.] [maxevent] [wfthr high] [wfthr low] [in_dir(~/)] (allrun?)" << std::endl;
     return -1;
   }
   auto runnum = stoi(argv[1]);
   auto maxevent = stoi(argv[2]);
   auto wfthrh = stoi(argv[3]);
   auto wfthrl = stoi(argv[4]);
   auto in_file = argv[5];

  auto in_chain = new TChain("tree", "tree");

  if(argc==6){
    in_chain->Add(Form("%srun%06d_0_000_ev0-2999.root",in_file,runnum));
    in_chain->Add(Form("%srun%06d_1_000_ev0-2999.root",in_file,runnum));
    in_chain->Add(Form("%srun%06d_2_000_ev0-2999.root",in_file,runnum));
  }
  else if(argc==7){
    in_chain->Add(Form("%srun%06d*.root",in_file,runnum));
  }

  SingleTrackAnalyzerForRes* t = new SingleTrackAnalyzerForRes(in_chain);
  t->CalcLGWFefficiency(runnum,maxevent,wfthrh,wfthrl);
  
  delete in_chain;
  return 0;

}
