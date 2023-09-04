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

  if(argc<5){
    std::cerr << "./bin [Ks:0, vmeson:1, eIDrev:3, eIDfwd:4] [out.pdf] [out.root] [maxevent]" << std::endl;
    return -1;
  }

  auto runtype = stoi(argv[1]);
  auto out_file_name = argv[2];
  auto out_root_name = argv[3];
  auto maxevent = stoi(argv[4]);
  auto in_file_name = argv[5];

  if(argc==5&&strlen(out_file_name)>4&&strlen(out_root_name)>5){
    //default
  }
  else if(argc==6&&strlen(out_file_name)>4&&strlen(out_root_name)>5&&strlen(in_file_name)>5){
    //supply input file
  }
  else{
    std::cerr << "./bin [Ks:0, vmeson:1, eIDrev:3, eIDfwd:4] [out.pdf] [out.root] [maxevent]" << std::endl;
    return -1;
  }
   
  auto in_chain = new TChain("tree", "tree");

  if(argc==5){
    if(runtype==0){
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root03a/trackselection_prod220212_chisq30.root");
    }
    else if(runtype==1){
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/v30/*.root");//vmeson
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/v33/*.root");//trigger study
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/v31/*.root");//trigger study
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDadd_22033101.root");//eID(LG+)
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDcalib_22031701.root");//eID(LG)
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDcalib_prod220216_22033104.root");//eID(HBD)
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDcalib_22032501.root");//gas
      //*******
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/rootphi/v36/*.root");//vmeson; production new
    }
    else if(runtype==2){
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_1e9FM*.root");
    }
    else if(runtype==3){
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDadd_22033101.root");//eID(LG+)
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDcalib_22031701.root");//eID(LG)
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDcalib_prod220216_22033104.root");//eID(HBD)
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDcalib_22032501.root");//gas
    }
  }
  else if(argc==6){
    in_chain->Add(in_file_name);
  }


  AnalyzerTrackSelection* t = new AnalyzerTrackSelection(in_chain);
  double hbdoptype=-1;
  if(runtype==0){hbdoptype=0;}
  if(runtype==1){hbdoptype=1;}
  if(runtype==3){hbdoptype=1;}
  if(runtype==4){hbdoptype=0;}

  t->DrawForLGRejection(runtype,maxevent,out_file_name,out_root_name,hbdoptype);
  
  delete in_chain;
  return 0;

}
