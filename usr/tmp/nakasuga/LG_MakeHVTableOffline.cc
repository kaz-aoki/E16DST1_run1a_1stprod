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

   if ( argc!=4 ) {
     std::cerr << "./bin [gainmap.txt] [preHVtable.txt] [newHVtable prefix]" << std::endl;
     return -1;
   }
   auto gainfile = argv[1];
   auto prefile = argv[2];
   auto newfile_prefix = argv[3];

   E16ANA_LGOnlineAnalyzer::MakeHVTableOffline(gainfile, prefile, newfile_prefix);

   return 0;

}
