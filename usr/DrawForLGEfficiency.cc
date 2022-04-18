#include "AnalyzerTrackSelection.hh"
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

  if ( argc<4 || argc>5 ) {
    std::cerr << "./bin [5e9fwd:0, 5e9rev:1, 1e9FM-:2, eIDcalb:3] [outfile] [maxevent]" << std::endl;
    return -1;
  }
  auto runtype = stoi(argv[1]);
  auto out_file_name = argv[2];
  auto maxevent = stoi(argv[3]);
  auto in_file_name = argv[4];
   
  auto in_chain = new TChain("tree", "tree");

  if(argc==4){
    if(runtype==0){
      // in_chain->Add("./out/root03a/trackselection_chisq30_fflag01.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root03a/trackselection_prod220212_chisq30.root");
    }
    else if(runtype==1){
      // in_chain->Add("./out/root/trackselection_5e9*.root");
      // in_chain->Add("./out/root/trackselection_5e9rev_prod220131.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_5e9rev_prod220131_chisq20_modall_morino.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/v30/*.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/v33/*.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/v31/*.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDadd_22033101.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDcalib_22031701.root");//eID(LG)
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDcalib_22032501.root");//gas
    }
    else if(runtype==2){
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_1e9FM*.root");
    }
    else if(runtype==3){
      // in_chain->Add("./out/root03a/trackselection_eIDcalib_chisq20_fflag01.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root03a/trackselection_eIDcalib_chisq20.root");
    }
  }
  else if(argc==5){
    in_chain->Add(in_file_name);
  }


  AnalyzerTrackSelection* t = new AnalyzerTrackSelection(in_chain);
  t->DrawForLGEfficiency(runtype,maxevent,out_file_name);
  
  delete in_chain;
  return 0;

}
