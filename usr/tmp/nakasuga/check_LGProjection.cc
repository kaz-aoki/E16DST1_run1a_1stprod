#include <stdio.h>
#include <iostream>
#include <fstream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TRandom.h>
// #include <boost/program_options.hpp>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"
#include "E16ANA_LGConstant.hh"
#include "E16ANA_LGDeadChannel.hh"
#include "E16ANA_LGClustering.hh"
#include "E16ANA_LGCheckHist.hh"
#include "E16ANA_LGProjection.hh"
#include "E16ANA_Massw2Gamma.hh"
#include "E16ANA_GammaAnalyzer.hh"
#include "E16DST_Constant.hh"

using namespace std;
// namespace  bpo = boost::program_options;

int main(int argc, char* argv[]) {
  if (argc != 5) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.txt] [output.root] [output.pdf] [max event]" << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  auto out_pdf_name = argv[3];
  auto maxevent = stoi(argv[4]);

  std::ifstream fin(in_file_name);
  // TFile* fout = new TFile(out_file_name,"recreate");

  // auto *analyzer = new E16ANA_GammaAnalyzer();

  E16ANA_LGProjection proj;
  TVector3 initpos(0., 0., 0.);
  // TVector3 initpos( 25., 0., -40.);//left up
  // TVector3 initpos( 25., 0.,  40.);//left down
  // TVector3 initpos(-25., 0., -40.);//right up
  // TVector3 initpos(-25., 0.,  40.);//right down

  int n_event = 0;
  while (!fin.eof()) {
    if (n_event % 1000 == 0) {
      cout << "Number of event: " << n_event << endl;
    }
    if (maxevent!=-1 && n_event>=maxevent) {
      break;
    }

    int eventid, pid;
    double impactp, mass, px, py, pz;
    std::string name;
    fin >> eventid >> impactp >> pid >> mass >> name >> px >> py >> pz;

    std::cout<<"************"<<std::endl;
    std::cout<<px<<" "<<py<<" "<<pz<<" "<<sqrt(px*px+py*py+pz*pz)<<std::endl;
    TVector3 initmom1(px,py,pz);
    proj.SetInitInfo(initpos,initmom1);
    bool is_crossed = proj.CalcCrossInfoStraight();
    std::cout<<is_crossed<<" "<<proj.Module()<<" "<<proj.Block()<<std::endl;
    proj.SetInitInfo(initpos,initmom1,1.);
    is_crossed = proj.CalcCrossInfo();
    std::cout<<is_crossed<<" "<<proj.Module()<<" "<<proj.Block()<<std::endl;

    ++n_event;

  }

  // TString fsout = Form("%s",out_pdf_name);
  // TCanvas* c = new TCanvas("c","c",1000,700);
  // c->SaveAs(fsout+"[","pdf");
  // analyzer->Draw(fsout,c);
  // c->SaveAs(fsout+"]","pdf");

  // fout->Write();
  // fout->Close();

  return 0;
}
