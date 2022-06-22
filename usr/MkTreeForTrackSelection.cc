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

   if ( argc<7 || argc>8 ) {
     std::cerr << "./bin [5e9fwd:0, 5e9rev:1, 1e9FM-:2, eIDcalib:3] [outfile] [maxevent] [module_of_track@HBD] [charge or 0(all)] [chi_square]" << std::endl;
     return -1;
   }
   auto runtype = stoi(argv[1]);
   auto out_file_name = argv[2];
   auto maxevent = stoi(argv[3]);
   auto hbd_track_module = stoi(argv[4]);
   auto track_charge = stoi(argv[5]);
   auto max_chi_square = stoi(argv[6]);
   auto in_file_prefix = argv[7];

  auto in_chain = new TChain("tree", "tree");

  if(argc==7){
    if(runtype==0){
      // in_chain->Add("./root/run0b/run20*_211122_ccj.root");

      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b220212-0/*.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b220212-1/*.root");

      in_chain->Add("/ccj/w/data06a/E16/user/ichikawa/lsf_file/22032400-v1/root_finished/*.root");//5e9ks+1e9ks
      in_chain->Add("/ccj/w/data06a/E16/user/ichikawa/lsf_file/22032401-v1/root_finished/*.root");//5e9ks+1e9ks

      // in_chain->Add("/work22/ichikawa/lsf_file/22041000-v1/root_finished/*.root");//1e9ks

    }
    else if(runtype==1){
      //    in_chain->Add("./root/calib/*.root");
      //    in_chain->Add("./root/single/run0307*.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/single220131/run0307*.root");
    }
    else if(runtype==2){
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/minusmag/*.root");
    }
    else if(runtype==3){
      // in_chain->Add("./root/calib220208/run03029*.root");
      // in_chain->Add("./root/calib220208/run030300*.root");
      // in_chain->Add("./root/calib220208/run030301*.root");
      // in_chain->Add("./root/calib220208/run030302*.root");
      // in_chain->Add("./root/calib220208/run030303*.root");
      // in_chain->Add("./root/calib220208/run030304*.root");
      // in_chain->Add("./root/calib220208/run030305*.root");
      // in_chain->Add("./root/calib220208/run030306*.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/calib220211/*.root");
      // in_chain->Add("./root/calib220216/run03030*.root");
      // in_chain->Add("./root/calib220216/run03031*.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/1e10etc220331/run0307*.root");
      in_chain->Add("/ccj/w/data06a/E16/user/ymorino/2204/job/x3run03029*.root");
    }
  }
  else if(argc==8){
    in_chain->Add(Form("%s*.root",in_file_prefix));
  }


  SingleTrackAnalyzerForRes* t = new SingleTrackAnalyzerForRes(in_chain);
  t->MkTreeForTrackSelection(runtype,maxevent,out_file_name,hbd_track_module,track_charge,max_chi_square);
  
  delete in_chain;
  return 0;

}
