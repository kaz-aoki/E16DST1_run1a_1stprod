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
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/v30/*.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/v33/*.root");

      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030722.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030718.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030717.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030727.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030734.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030742.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030740.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030721.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030743.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030736.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030748.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030745.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030749.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030746.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030752.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030751.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030723.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/lsf/track_run030747.root");

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
  t->DrawForTrackSelection(runtype,maxevent,out_file_name);
  
  delete in_chain;
  return 0;

}
