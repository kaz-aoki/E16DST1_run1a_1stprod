#include <array>
#include <iostream>
#include <stdlib.h>

#include <CLHEP/Vector/ThreeVector.h>
#include "TCanvas.h"
#include "TFile.h"
#include "TH2.h"
#include "TROOT.h"
#include "TString.h"

#include "E16ANA_ParamManager.hh"
#include "E16ANA_ErrorMessage.hh"
#include "E16ANA_MagneticFieldMap.hh"

using namespace std;
using namespace CLHEP;

constexpr int kNumMaps = 2;
const array<string,  kNumMaps> kMapNames  = {"/ccj/u/E16/database/fieldmap/Bmap-SKS-block-far-191218-2450A-rev1.binary",
                                             "/ccj/u/E16/database/fieldmap/Bmap_201207010_mod.binary"};
const array<TString, kNumMaps> kMapTitles = {"map_mix", "map_calc"};

constexpr int    kNumZXPoints = 120;
constexpr double kZXRange     = 600.;
constexpr int    kNumYPoints  = 7;
constexpr double kYPitch      = 20.;

void Draw(const TString& pdf_name, const TString& canvas_name, array<TH2F, kNumYPoints>& hists) {
  auto canvas = TCanvas();
  canvas.SetName(canvas_name);
  canvas.SetTitle(canvas_name);
  canvas.Divide(3, 3);
  for (int y = 0; y < kNumYPoints; ++y) {
    canvas.cd(1 + y);
    hists[y].Draw("colz");
  }
  canvas.Print(pdf_name);
  return;
}

void Draw(const TString& pdf_name, const TString& canvas_name, array<array<TH2F, kNumYPoints>, kNumMaps>& hists) {
  for (int m = 0; m < kNumMaps; ++m) {
    Draw(pdf_name, canvas_name + "_" + kMapTitles[m], hists[m]);
  }
  return;
}

double Y(int i) {
  return (i - (kNumYPoints - 1.) / 2.) * kYPitch;
}

double ZX(int i) {
  return (i - (kNumZXPoints - 1.) / 2.) * 2. * kZXRange / kNumZXPoints;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "./bin output_header" << endl;
    return -1;
  }
  auto out_name = TString(argv[1]);
  gROOT->ProcessLine(".x ~/.rootlogon.C");
  
  E16INFO("initialize...");
  array<E16ANA_MagneticFieldMap3D*, kNumMaps> fields;
  for (int m = 0; m < kNumMaps; ++m) {
    fields[m] = new E16ANA_MagneticFieldMap3D(kMapNames[m]);
    fields[m]->Initialize_binary();
  }
  E16INFO("----map initialize end----------");

  auto file = TFile(out_name + ".root", "recreate");
  array<array<TH2F, kNumYPoints>, kNumMaps> h_zx_maps;
  array<TH2F, kNumYPoints> h_percentage_zx_maps;
  for (int y = 0; y < kNumYPoints; ++y) {
    auto name  = TString(Form("_%d", y));
    auto title = TString(Form("_y%lf", Y(y)));
    for (int m = 0; m < kNumMaps; ++m) {
      auto name1 = name + Form("_%d", m);
      auto title1 = title + "_" + kMapTitles[m];
      h_zx_maps[m][y] = TH2F("h_zx_maps" + name1, "h_zx_maps" + title1, kNumZXPoints, -1. * kZXRange, kZXRange, kNumZXPoints, -1. * kZXRange, kZXRange);
    }
    h_percentage_zx_maps[y] = TH2F("h_percentage_zx_maps" + name, "h_percentage_zx_maps" + title,
                                   kNumZXPoints, -1. * kZXRange, kZXRange, kNumZXPoints, -1. * kZXRange, kZXRange);
  }

  for (int yid = 0; yid < kNumYPoints; ++yid) {
    cout << "y ID: " << yid << endl;
    auto y = Y(yid);
    for (int zid = 0; zid < kNumZXPoints; ++zid) {
      auto z = ZX(zid);
      for (int xid = 0; xid < kNumZXPoints; ++xid) {
        auto x = ZX(xid);
        array<double, kNumMaps> b_mag;
        for (int m = 0; m < kNumMaps; ++m) {
          double point[3] = {x * 0.1, y * 0.1, z * 0.1};
          double b[3];
          int flag = 0;
          fields[m]->GetFieldValue(point, b, flag);
          b_mag[m] = sqrt(b[0] * b[0] + b[1] * b[1] + b[2] * b[2]) * 0.0001;
          h_zx_maps[m][yid].Fill(z, x, b_mag[m]);
        }
        h_percentage_zx_maps[yid].Fill(z, x, (b_mag[1] - b_mag[0]) / b_mag[0] * 100.);
      }
    }
  }
  
  auto pdf_name = out_name + ".pdf";
  auto canvas = TCanvas();
  canvas.Print(pdf_name + "[");
  Draw(pdf_name, "c_zx_maps",            h_zx_maps);
  Draw(pdf_name, "c_percentage_zx_maps", h_percentage_zx_maps);
  canvas.Print(pdf_name + "]");
  file.Write();
  return 0;
}
