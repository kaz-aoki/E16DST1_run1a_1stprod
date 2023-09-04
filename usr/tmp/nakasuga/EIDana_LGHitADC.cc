#include "E16ANA_EIDSingleTrackAnalyzer.hh"
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

   if ( argc!=5 ) {
     std::cerr << "./bin [maxevent] [out.pdf] [out.root] [input_prefix]*.root" << std::endl;
     return -1;
   }
   auto maxevent = stoi(argv[1]);
   auto out_pdf_file = argv[2];
   auto out_root_file = argv[3];
   auto input_prefix = argv[4];

  auto in_chain = new TChain("tree", "tree");

  in_chain->Add(Form("%s*.root",input_prefix));

  E16ANA_EIDSingleTrackAnalyzer* t = new E16ANA_EIDSingleTrackAnalyzer(in_chain);
  t->LGHitADC(maxevent,out_pdf_file,out_root_file);
  
  delete in_chain;
  return 0;

}
