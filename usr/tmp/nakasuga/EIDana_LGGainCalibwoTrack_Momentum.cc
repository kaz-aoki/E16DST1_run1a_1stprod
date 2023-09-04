#include "E16ANA_LGGainCalibwoTrack.hh"
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

   if ( argc!=4 && argc!=5 ) {
     std::cerr << "./bin [out pdf file] [out root file] [maxevent]" << std::endl;
     return -1;
   }
   auto out_pdf_file = argv[1];
   auto out_root_file = argv[2];
   auto maxevent = stoi(argv[3]);
   auto in_file_prefix = argv[4];

  auto in_chain = new TChain("tree", "tree");

  if(argc==4){
    in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020908*.root");
    in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020909*.root");
    in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020914*.root");
    in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020921*.root");
    in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020924*.root");
    in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020927*.root");
    in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020987*.root");
    in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020989*.root");
  }
  else if(argc==5){
    in_chain->Add(Form("%s*.root",in_file_prefix));
  }


  E16ANA_LGGainCalibwoTrack* t = new E16ANA_LGGainCalibwoTrack(in_chain);
  t->MomentumEachBlock(out_pdf_file, out_root_file, maxevent);
  
  delete in_chain;
  return 0;

}
