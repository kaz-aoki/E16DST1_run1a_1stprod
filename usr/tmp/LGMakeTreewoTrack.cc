#include "GainCalibwoTrack.hh"
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
     std::cerr << "./bin [5e9fwd:0, 5e9rev:1, 1e9FM-:2, eIDcalib:3] [outfile] [maxevent]" << std::endl;
     return -1;
   }
   auto runtype = stoi(argv[1]);
   auto out_file_name = argv[2];
   auto maxevent = stoi(argv[3]);
   auto in_file_prefix = argv[4];

  auto in_chain = new TChain("tree", "tree");

  if(argc==4){
    if(runtype==0){
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020908*.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020909*.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020914*.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020921*.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020924*.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020927*.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020987*.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020989*.root");
    }
    else if(runtype==1){
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/single221017/run030743*.root");
    }
    else if(runtype==2){
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/minusmag/*.root");
    }
    else if(runtype==3){
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/calib221003/*.root");
    }
  }
  else if(argc==5){
    in_chain->Add(Form("%s*.root",in_file_prefix));
  }


  GainCalibwoTrack* t = new GainCalibwoTrack(in_chain);
  t->MakeTree(runtype,maxevent,out_file_name);
  
  delete in_chain;
  return 0;

}
