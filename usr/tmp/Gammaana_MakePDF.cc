#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TRandom.h>
// #include <boost/program_options.hpp>

#include "E16ANA_GammaAnalyzer.hh"

using namespace std;
// namespace  bpo = boost::program_options;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.root] [output.pdf] " << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];

  // TFile* fout = new TFile(out_file_name,"recreate");

  auto *analyzer = new E16ANA_GammaAnalyzer();
  analyzer->SetRootFile(in_file_name);
  analyzer->SetHists();

  TString fsout = Form("%s",out_file_name);
  TCanvas* c = new TCanvas("c","c",1000,700);
  c->SaveAs(fsout+"[","pdf");
  analyzer->Draw(fsout,c);
  c->SaveAs(fsout+"]","pdf");

  // fout->Write();
  // fout->Close();

  return 0;
}
