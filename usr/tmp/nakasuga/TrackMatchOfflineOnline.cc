#include "E16ANA_EIDSingleTrackAnalyzerV2.hh"
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

  if(argc!=3&&argc!=4){
    std::cerr << "./bin [out.root] [maxevent] [input.root]" << std::endl;
    return -1;
  }
  auto out_root_name = argv[1];
  auto maxevent = stoi(argv[2]);
  auto in_root_name = argv[3];
   
  auto in_chain = new TChain("tree", "tree");
  if(argc==3){
    // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020991*.root");//for 1e9106
    // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020994*.root");//for 1e9106
    // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020995*.root");//for 1e9106
    // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020999*.root");//for 1e9106
    //****
    in_chain->Add("/work22/nakasuga/lsf_file/23110900-v1/root_finished/run020995*.root");//for 1e9106
    // in_chain->Add("/work22/nakasuga/lsf_file/23110901-v3/root_finished/run020995*.root");//for 1e9106
    //****
    // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run020928*.root");//for 5e9106
    // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/run0b221021/run02098*.root");//for 1e91M3
    // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/calib221003/run030322*.root");
    // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/root/invmag/run030464*.root");
  }
  else{
    in_chain->Add(in_root_name);
  }

  E16ANA_EIDSingleTrackAnalyzerV2* t = new E16ANA_EIDSingleTrackAnalyzerV2(in_chain);
  t->TrackMatchOfflineOnline(maxevent,out_root_name);
  
  delete in_chain;
  return 0;

}
