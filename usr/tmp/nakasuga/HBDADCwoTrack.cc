#include "E16ANA_HBDADCwoTrack.hh"
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
     std::cerr << "./bin [out pdf file] [out root file] [maxevent] [input file prefix]" << std::endl;
     return -1;
   }
   auto out_pdf_file = argv[1];
   auto out_root_file = argv[2];
   auto maxevent = stoi(argv[3]);
   auto in_file_prefix = argv[4];

  auto in_chain = new TChain("tree", "tree");
  in_chain->Add(Form("%s*.root",in_file_prefix));

  E16ANA_HBDADCwoTrack* t = new E16ANA_HBDADCwoTrack(in_chain);
  t->MakeHist(maxevent,out_pdf_file,out_root_file);
  
  delete in_chain;
  return 0;

}
