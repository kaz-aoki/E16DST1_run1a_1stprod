#include "E16ANA_LGOnlineAnalyzer.hh"
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

   if ( argc!=7 ) {
     std::cerr << "./bin [FMOFF:0, FMON:1] [run No.] [runxxxxxx.root] [preHVtable.txt] [newHVtable prefix] [maxevent]" << std::endl;
     return -1;
   }
   auto FMstate = stoi(argv[1]);
   auto run_id = stoi(argv[2]);
   auto runfile = argv[3];
   auto prefile = argv[4];
   auto newfile_prefix = argv[5];
   auto maxevent = stoi(argv[6]);

   auto in_chain = new TChain("tree", "tree");

   in_chain->Add(Form("%s",runfile));

   std::cout<<" FM:"<<FMstate<<" | run"<<run_id<<" | prefile:"<<prefile<<" | newfile:"<<newfile_prefix<<".txt"<<std::endl;

   E16ANA_LGOnlineAnalyzer* t = new E16ANA_LGOnlineAnalyzer(in_chain);
   t->MakeHVTable(FMstate, run_id, prefile, newfile_prefix, maxevent);
  
   delete in_chain;
   return 0;

}
