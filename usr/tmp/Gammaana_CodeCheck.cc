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
#include "E16ANA_LGStraightProj.hh"
#include "E16ANA_Massw2Gamma.hh"
#include "E16ANA_GammaAnalyzer.hh"
#include "E16DST_Constant.hh"

using namespace std;
// namespace  bpo = boost::program_options;

int main(int argc, char* argv[]) {
  if (argc != 4) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.txt] [output.root] [output.pdf]" << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  auto out_pdf_name = argv[3];

  // std::ifstream fin("/ccj/u/nakasuga/work/dst1ana/track/etajamout.txt");
  std::ifstream fin(in_file_name);
  TFile* fout = new TFile(out_file_name,"recreate");

  auto *analyzer = new E16ANA_GammaAnalyzer();

  E16ANA_LGStraightProj proj;
  TVector3 initpos(0., 0., 20.);

  int n_event = 0;
  while (!fin.eof()) {
    if (n_event % 1000 == 0) {
      cout << "Number of event: " << n_event << endl;
    }

    double gx1, gy1, gz1, gx2, gy2, gz2, ene1, ene2;
    fin >> gx1 >> gy1 >> gz1 >> ene1 >> gx2 >> gy2 >> gz2 >> ene2;

    TVector3 initdir1(gx1,gy1,gz1);
    proj.SetInitInfo(initpos,initdir1);
    if( !proj.CalcCrossInfo() ) continue;

    analyzer->ClearHit0();
    // analyzer->SetHit0(0, 0, 0, 0., 0., 0., gx1, gy1, gz1, ene1/analyzer->PhtoEnergy(), 0., 0, 10.);
    double adc1 = ene1/analyzer->PhtoEnergy();
    analyzer->SetHit0(
      0, proj.Module(), proj.Block(), 
      proj.LCross1_x(), proj.LCross1_y(), proj.LCross1_z(), 
      proj.GPos_x(), proj.GPos_y(), proj.GPos_z(), 
      adc1, 0., 0, 10.);
    if( analyzer->Hit0isInvalid() ) continue;

    TVector3 initdir2(gx2,gy2,gz2);
    proj.SetInitInfo(initpos,initdir2);
    if( !proj.CalcCrossInfo() ) continue;

    analyzer->ClearHit1();
    // analyzer->SetHit1(0, 0, 0, 1000., 1000., 1000., gx2, gy2, gz2, ene2/analyzer->PhtoEnergy(), 0., 0, 10.);
    double adc2 = ene2/analyzer->PhtoEnergy();
    analyzer->SetHit1(
      0, proj.Module(), proj.Block(), 
      proj.LCross1_x(), proj.LCross1_y(), proj.LCross1_z(), 
      proj.GPos_x(), proj.GPos_y(), proj.GPos_z(), 
      adc2, 0., 0, 10.);
    if( analyzer->Hit1isInvalid() ) continue;
    if( analyzer->HitsareInvalid() ) continue;

    analyzer->ClearBranch();
    analyzer->FillHit0();
    analyzer->FillHit1();
    //calc im
    analyzer->FillForeHist();
    //calc mix im
    analyzer->FillTree();

    ++n_event;

  }

  TString fsout = Form("%s",out_pdf_name);
  TCanvas* c = new TCanvas("c","c",1000,700);
  c->SaveAs(fsout+"[","pdf");
  analyzer->Draw(fsout,c);
  c->SaveAs(fsout+"]","pdf");

  fout->Write();
  fout->Close();

  return 0;
}
