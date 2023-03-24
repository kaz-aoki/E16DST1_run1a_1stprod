#include "E16ANA_LGGainCalibwoTrack.hh"
#include "E16ANA_LGGainCalibwoTrackRoot.hh"
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

  if ( argc!=3 && argc!=4 ) {
    std::cerr << "./bin [outfile] [maxevent]" << std::endl;
    return -1;
  }
  auto out_file_name = argv[1];
  auto maxevent = stoi(argv[2]);
  auto in_file_prefix = argv[3];

  auto in_chain = new TChain("tree", "tree");

  if(argc==3){
    in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/wotrack/v3/*run020908.root");
    in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/wotrack/v3/*run020909.root");
    in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/wotrack/v3/*run020914.root");
    in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/wotrack/v3/*run020921.root");
    in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/wotrack/v3/*run020924.root");
    in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/wotrack/v3/*run020927.root");
    in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/wotrack/v3/*run020987.root");
    in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/wotrack/v3/*run020989.root");
    // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/wotrack/v3/*.root");
  }
  else if(argc==4){
    in_chain->Add(Form("%s*.root",in_file_prefix));
  }

  E16ANA_LGGainCalibwoTrackRoot* t = new E16ANA_LGGainCalibwoTrackRoot(in_chain);
  t->ResidualforLGmix(out_file_name, maxevent);
  
  delete in_chain;
  return 0;

}
