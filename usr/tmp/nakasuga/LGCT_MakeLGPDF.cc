#include "E16ANA_LGCTOnlineAnalyzer.hh"
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
     std::cerr << "./bin [run No.] [runxxxxxx.root] [outfile.pdf] [maxevent]" << std::endl;
     return -1;
   }
   auto run_id = std::stoi(argv[1]);
   auto infile = argv[2];
   auto outfile = argv[3];
   auto maxevent = std::stoi(argv[4]);

   auto in_chain = new TChain("tree", "tree");

   in_chain->Add(Form("%s",infile));

   E16ANA_LGCTOnlineAnalyzer* t = new E16ANA_LGCTOnlineAnalyzer(in_chain);
   t->MakeLGPDF(run_id, outfile, maxevent);
  
   delete in_chain;
   return 0;

}
