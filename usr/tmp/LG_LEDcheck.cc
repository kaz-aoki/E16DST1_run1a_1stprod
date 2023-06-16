#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>

#include "E16ANA_LGOnlineAnalyzer.hh"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"
#include "E16ANA_LGConstant.hh"
#include "E16ANA_LGDeadChannel.hh"
#include "E16ANA_LGClustering.hh"
#include "E16DST_Constant.hh"

using namespace std;

int main(int argc, char* argv[]) {
  if ( argc == 1 || argc == 2 ) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [FMOFF:0, FMON:1] [n_runs] [run no.1] [scale1] [run no.2] [scale2] ..." << endl;
    return -1;
  }

  auto FMstate = stoi(argv[1]);
  auto n_runs = stoi(argv[2]);

  if ( argc != n_runs*2+3 ) {
    cerr << "Invalid argc: " << argc << endl;
    return -1;
  }

  std::vector<int> inrunid;
  std::vector<double> scale;
  for(int i=0;i<n_runs;i++){
    inrunid.push_back(stoi(argv[3+i*2]));
    scale.push_back(stof(argv[4+i*2]));
  }

  std::vector<TH1F*> h[8];
  std::vector<TH1F*> hs[8];

  for(int irun=0;irun<n_runs;irun++){
    auto in_chain = new TChain("tree", "tree");
    in_chain->Add(Form("/e16/w/data101z1/calibdata/LG/230615/root/run%06d.root",inrunid.at(irun)));
    E16ANA_LGOnlineAnalyzer* t = new E16ANA_LGOnlineAnalyzer(in_chain);
    TH1F* th[8];
    TH1F* ths[8];
    t->LEDHist(FMstate, inrunid.at(irun), scale.at(irun), th, ths, -1);
    std::cout<<irun<<" "<<inrunid.at(irun)<<std::endl;
    for(int ib=0;ib<8;ib++){
      h[ib].push_back(th[ib]);
      hs[ib].push_back(ths[ib]);
    }
  }

  TCanvas* c = new TCanvas("c","c",1400,500);
  TString fout = "LED.pdf";
  c->SaveAs(fout+"[","pdf");
  c->Clear();
  c->Divide(4,2);
  for(int ib=0;ib<8;ib++){
    c->cd(ib+1);
    for(int irun=0;irun<n_runs;irun++){
      h[ib].at(irun)->SetLineColor(irun+1);
      h[ib].at(irun)->DrawNormalized("hist sames");
    }
  }
  c->SaveAs(fout,"pdf");
  c->Clear();
  c->Divide(4,2);
  for(int ib=0;ib<8;ib++){
    c->cd(ib+1);
    for(int irun=0;irun<n_runs;irun++){
      hs[ib].at(irun)->SetLineColor(irun+1);
      hs[ib].at(irun)->DrawNormalized("hist sames");
    }
  }
  c->SaveAs(fout,"pdf");
  c->SaveAs(fout+"]","pdf");

  return 0;
}
