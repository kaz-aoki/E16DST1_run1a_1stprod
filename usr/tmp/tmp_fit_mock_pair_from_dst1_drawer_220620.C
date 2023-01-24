#define tmp_fit_mock_pair_from_dst1_drawer_220620_cxx
#include "tmp_fit_mock_pair_from_dst1_drawer_220620.h"

#include <array>
#include <iostream>

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>

using namespace std;

int tmp_fit_mock_pair_from_dst1_drawer_220620::DirID() {
  enum {
    kLR,
    kRL,
    kLL,
    kRR
  };
  auto pmid = plus_gtr300_mid  - 105;
  auto mmid = minus_gtr300_mid - 105;
  if (pmid > 0) {
    if (mmid > 0) {
      return kLL;
    } else {
      return kLR;
    }
  } else {
    if (mmid > 0) {
      return kRL;
    } else {
      return kRR;
    }
  }
}

void tmp_fit_mock_pair_from_dst1_drawer_220620::Draw(const TString& name, array<array<TH1F, 2>, 4>* hists, TCanvas* canvas) {
  canvas->Clear();
  canvas->Divide(4, 2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 4; ++j) {
      canvas->cd(1 + 4 * i + j);
      hists->at(j)[i].Draw();
    }
  }
  canvas->Print(name);
  return;
}

void tmp_fit_mock_pair_from_dst1_drawer_220620::Draw(const TString& name, array<array<TH1F*, 3>, 5>* hists, TCanvas* canvas) {
  static const TString kName[3] = {"mock", "single", "pair"};
  auto legend = TLegend(0., 0., 1., 1.);
  for (int i = 0; i < 3; ++i) {
    legend.AddEntry(hists->at(4)[i], kName[i], "l");
  }
  canvas->Clear();
  canvas->Divide(3, 2);
  for (int i = 0; i < 5; ++i) {
    canvas->cd(1 + i);
    for (int j = 0; j < 3; ++j) {
      hists->at(i)[j]->SetLineColor(1 + j);
      hists->at(i)[j]->SetLineStyle(1 + j);
      if (j == 0) {
        hists->at(i)[j]->Draw();
      } else {
        hists->at(i)[j]->Draw("same");
      }
    }
  }
  canvas->cd(6);
  legend.Draw();
  canvas->Print(name);
  return;
}

void tmp_fit_mock_pair_from_dst1_drawer_220620::Draw(const TString& name, array<array<TH2F*, 3>, 5>* hists, TCanvas* canvas) {
  for (int i = 0; i < 5; ++i) {
    canvas->Clear();
    canvas->Divide(2, 2);
    for (int j = 0; j < 3; ++j) {
      canvas->cd(1 + j);
      hists->at(i)[j]->Draw("colz");
    }
    canvas->Print(name);
  }
  return;
}

void tmp_fit_mock_pair_from_dst1_drawer_220620::Draw(const TString& name, array<array<TH1F*, 2>, 5>* hists, TCanvas* canvas) {
  static const TString kName[3] = {"single", "pair"};
  auto legend = TLegend(0., 0., 1., 1.);
  for (int i = 0; i < 2; ++i) {
    legend.AddEntry(hists->at(4)[i], kName[i], "l");
  }
  canvas->Clear();
  canvas->Divide(3, 2);
  for (int i = 0; i < 5; ++i) {
    canvas->cd(1 + i);
    hists->at(i)[0]->Draw();
    hists->at(i)[1]->SetLineColor(2);
    hists->at(i)[1]->SetLineStyle(2);
    hists->at(i)[1]->Draw("same");
  }
  canvas->cd(6);
  legend.Draw();
  canvas->Print(name);
  return;
}

void tmp_fit_mock_pair_from_dst1_drawer_220620::Loop(const TString& out_name) {
//   In a ROOT session, you can do:
//      root> .L tmp_fit_mock_pair_from_dst1_drawer_220620.C
//      root> tmp_fit_mock_pair_from_dst1_drawer_220620 t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;

  const TString kChargeName[2]  = {"plus", "minus"};
  const TString kMethodName[4]  = {"mock", "pre", "single", "pair"};
  const TString kMethodName2[3] = {"mock", "near", "pair"};
  const TString kDirName[5]     = {"LR", "RL", "LL", "RR", "all"};
  auto file = TFile(out_name + ".root", "recreate");
  array<array<TH1F, 2>, 4> h_mom_res_x;
  array<array<TH1F, 2>, 4> h_mom_res_y;
  array<array<TH1F, 2>, 4> h_mom_res_z;
  array<array<TH1F, 2>, 4> h_vtx_x;
  array<array<TH1F, 2>, 4> h_vtx_y;
  array<array<TH1F, 2>, 4> h_ssd_res_x;
  array<array<TH1F, 2>, 4> h_ssd_res_y;
  array<array<TH1F, 2>, 4> h_gtr100_res_x;
  array<array<TH1F, 2>, 4> h_gtr100_res_y;
  array<array<TH1F, 2>, 4> h_gtr200_res_x;
  array<array<TH1F, 2>, 4> h_gtr200_res_y;
  array<array<TH1F, 2>, 4> h_gtr300_res_x;
  array<array<TH1F, 2>, 4> h_gtr300_res_y;
//  array<TH1F, 4> h_vtx_res_x;
//  array<TH1F, 4> h_vtx_res_y;
//  array<TH1F, 4> h_vtx_res_z;
  array<TH1F, 4> h_mass;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 2; ++j) {
      TString name = "_" + kMethodName[i] + "_" + kChargeName[j];
      h_mom_res_x[i][j]    = TH1F(Form("h_mom_res_x_%d_%d",    i, j), "h_mom_res_x"    + name, 100, -0.2, 0.2);
      h_mom_res_y[i][j]    = TH1F(Form("h_mom_res_y_%d_%d",    i, j), "h_mom_res_y"    + name, 100, -0.2, 0.2);
      h_mom_res_z[i][j]    = TH1F(Form("h_mom_res_z_%d_%d",    i, j), "h_mom_res_z"    + name, 100, -0.2, 0.2);
      h_vtx_x[i][j]        = TH1F(Form("h_vtx_x_%d_%d",        i, j), "h_vtx_x"        + name, 100, -5.,  5.);
      h_vtx_y[i][j]        = TH1F(Form("h_vtx_y_%d_%d",        i, j), "h_vtx_y"        + name, 100, -5.,  5.);
      h_ssd_res_x[i][j]    = TH1F(Form("h_ssd_res_x_%d_%d",    i, j), "h_ssd_res_x"    + name, 100, -1.,  1.);
      h_ssd_res_y[i][j]    = TH1F(Form("h_ssd_res_y_%d_%d",    i, j), "h_ssd_res_y"    + name, 100, -3.,  3.);
      h_gtr100_res_x[i][j] = TH1F(Form("h_gtr100_res_x_%d_%d", i, j), "h_gtr100_res_x" + name, 100, -1.,  1.);
      h_gtr100_res_y[i][j] = TH1F(Form("h_gtr100_res_y_%d_%d", i, j), "h_gtr100_res_y" + name, 100, -3.,  3.);
      h_gtr200_res_x[i][j] = TH1F(Form("h_gtr200_res_x_%d_%d", i, j), "h_gtr200_res_x" + name, 100, -1.,  1.);
      h_gtr200_res_y[i][j] = TH1F(Form("h_gtr200_res_y_%d_%d", i, j), "h_gtr200_res_y" + name, 100, -3.,  3.);
      h_gtr300_res_x[i][j] = TH1F(Form("h_gtr300_res_x_%d_%d", i, j), "h_gtr300_res_x" + name, 100, -1.,  1.);
      h_gtr300_res_y[i][j] = TH1F(Form("h_gtr300_res_y_%d_%d", i, j), "h_gtr300_res_y" + name, 100, -3.,  3.);
    }
//    h_vtx_res_x[i] = TH1F(Form("h_vtx_res_x_%d", i), "h_vtx_res_x" + "_" + kMethodName[i], 100, -0.2, 0.2);
//    h_vtx_res_y[i] = TH1F(Form("h_vtx_res_y_%d", i), "h_vtx_res_y" + "_" + kMethodName[i], 100, -0.2, 0.2);
//    h_vtx_res_z[i] = TH1F(Form("h_vtx_res_z_%d", i), "h_vtx_res_z" + "_" + kMethodName[i], 100, -0.2, 0.2);
//    h_mass[i] = TH1F(Form("h_mass_%d", i), Form("h_mass_%d", i), 160, 0.8, 1.2);
    h_mass[i] = TH1F(Form("h_mass_%d", i), "h_mass_" + kMethodName[i], 160, 0.3, 0.7);
  }

  array<array<TH1F*, 3>, 5> h2_vtx_x;
  array<array<TH1F*, 3>, 5> h2_vtx_y;
  array<array<TH1F*, 3>, 5> h2_vtx_z;
  array<array<TH1F*, 3>, 5> h2_plus_mom;
  array<array<TH1F*, 3>, 5> h2_plus_mom_x;
  array<array<TH1F*, 3>, 5> h2_plus_mom_y;
  array<array<TH1F*, 3>, 5> h2_plus_mom_z;
  array<array<TH1F*, 3>, 5> h2_minus_mom;
  array<array<TH1F*, 3>, 5> h2_minus_mom_x;
  array<array<TH1F*, 3>, 5> h2_minus_mom_y;
  array<array<TH1F*, 3>, 5> h2_minus_mom_z;
  array<array<TH1F*, 3>, 5> h2_mom_angle;
  array<array<TH1F*, 3>, 5> h2_mass;
  array<array<TH2F*, 3>, 5> h2_mass_vtxz;
  
  array<array<TH1F*, 2>, 5> h2_vtx_x_res;
  array<array<TH1F*, 2>, 5> h2_vtx_y_res;
  array<array<TH1F*, 2>, 5> h2_vtx_z_res;
  array<array<TH1F*, 2>, 5> h2_plus_mom_res;
  array<array<TH1F*, 2>, 5> h2_plus_mom_x_res;
  array<array<TH1F*, 2>, 5> h2_plus_mom_y_res;
  array<array<TH1F*, 2>, 5> h2_plus_mom_z_res;
  array<array<TH1F*, 2>, 5> h2_minus_mom_res;
  array<array<TH1F*, 2>, 5> h2_minus_mom_x_res;
  array<array<TH1F*, 2>, 5> h2_minus_mom_y_res;
  array<array<TH1F*, 2>, 5> h2_minus_mom_z_res;
  array<array<TH1F*, 2>, 5> h2_mom_angle_res;
  array<array<TH1F*, 2>, 5> h2_mass_res;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 3; ++j) {
      TString name = static_cast<TString>(Form("_%d_%d", i, j));
      TString title = "_" + kDirName[i] + "_" + kMethodName2[j];
      h2_vtx_x[i][j]       = new TH1F("h2_vtx_x"       + name, "h2_vtx_x"       + title, 300, -150., 150.);
      h2_vtx_y[i][j]       = new TH1F("h2_vtx_y"       + name, "h2_vtx_y"       + title, 300, -150., 150.);
      h2_vtx_z[i][j]       = new TH1F("h2_vtx_z"       + name, "h2_vtx_z"       + title, 300, -150., 150.);
      h2_plus_mom[i][j]    = new TH1F("h2_plus_mom"    + name, "h2_plus_mom"    + title, 100,    0.,   5.);
      h2_plus_mom_x[i][j]  = new TH1F("h2_plus_mom_x"  + name, "h2_plus_mom_x"  + title, 100,   -5.,   5.);
      h2_plus_mom_y[i][j]  = new TH1F("h2_plus_mom_y"  + name, "h2_plus_mom_y"  + title, 100,   -5.,   5.);
      h2_plus_mom_z[i][j]  = new TH1F("h2_plus_mom_z"  + name, "h2_plus_mom_z"  + title, 100,   -5.,   5.);
      h2_minus_mom[i][j]   = new TH1F("h2_minus_mom"   + name, "h2_minus_mom"   + title, 100,    0.,   5.);
      h2_minus_mom_x[i][j] = new TH1F("h2_minus_mom_x" + name, "h2_minus_mom_x" + title, 100,   -5.,   5.);
      h2_minus_mom_y[i][j] = new TH1F("h2_minus_mom_y" + name, "h2_minus_mom_y" + title, 100,   -5.,   5.);
      h2_minus_mom_z[i][j] = new TH1F("h2_minus_mom_z" + name, "h2_minus_mom_z" + title, 100,   -5.,   5.);
      h2_mom_angle[i][j]   = new TH1F("h2_mom_angle"   + name, "h2_mom_angle"   + title,  64,   -3.2,  3.2);
      h2_mass[i][j]        = new TH1F("h2_mass"        + name, "h2_mass"        + title, 200,    0.4,  0.6);
      h2_mass_vtxz[i][j]   = new TH2F("h2_mass_vtxz"   + name, "h2_mass_vtxz"   + title,  50, -150., 150., 50, 0.4, 0.6);
      if (j != 0) {
        h2_vtx_x_res[i][j - 1]       = new TH1F("h2_vtx_x_res"       + name, "h2_vtx_x_res"       + title, 100,  -10.,  10.);
        h2_vtx_y_res[i][j - 1]       = new TH1F("h2_vtx_y_res"       + name, "h2_vtx_y_res"       + title, 100,  -10.,  10.);
        h2_vtx_z_res[i][j - 1]       = new TH1F("h2_vtx_z_res"       + name, "h2_vtx_z_res"       + title, 100,  -10.,  10.);
        h2_plus_mom_res[i][j - 1]    = new TH1F("h2_plus_mom_res"    + name, "h2_plus_mom_res"    + title, 100,   -0.2,  0.2);
        h2_plus_mom_x_res[i][j - 1]  = new TH1F("h2_plus_mom_x_res"  + name, "h2_plus_mom_x_res"  + title, 100,   -0.2,  0.2);
        h2_plus_mom_y_res[i][j - 1]  = new TH1F("h2_plus_mom_y_res"  + name, "h2_plus_mom_y_res"  + title, 100,   -0.2,  0.2);
        h2_plus_mom_z_res[i][j - 1]  = new TH1F("h2_plus_mom_z_res"  + name, "h2_plus_mom_z_res"  + title, 100,   -0.2,  0.2);
        h2_minus_mom_res[i][j - 1]   = new TH1F("h2_minus_mom_res"   + name, "h2_minus_mom_res"   + title, 100,   -0.2,  0.2);
        h2_minus_mom_x_res[i][j - 1] = new TH1F("h2_minus_mom_x_res" + name, "h2_minus_mom_x_res" + title, 100,   -0.2,  0.2);
        h2_minus_mom_y_res[i][j - 1] = new TH1F("h2_minus_mom_y_res" + name, "h2_minus_mom_y_res" + title, 100,   -0.2,  0.2);
        h2_minus_mom_z_res[i][j - 1] = new TH1F("h2_minus_mom_z_res" + name, "h2_minus_mom_z_res" + title, 100,   -0.2,  0.2);
        h2_mom_angle_res[i][j - 1]   = new TH1F("h2_mom_angle_res"   + name, "h2_mom_angle_res"   + title,  64,   -0.2,  0.2);
        h2_mass_res[i][j - 1]        = new TH1F("h2_mass_res"        + name, "h2_mass_res"        + title, 100,   -0.2,  0.2);
      }
    }
  }

  for (Long64_t jentry = 0; jentry < nentries; ++jentry) {
    if (jentry % 1000 == 0) {
      cout << jentry << " / " << nentries << endl;
    }
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
//    if (Cut(ientry) < 0) continue;
    // mock
    h_mom_res_x[0][0].Fill(mock_plus_init_mom->X()  - mock_plus_init_mom->X());
    h_mom_res_x[0][1].Fill(mock_minus_init_mom->X() - mock_minus_init_mom->X());
    h_mom_res_y[0][0].Fill(mock_plus_init_mom->Y()  - mock_plus_init_mom->Y());
    h_mom_res_y[0][1].Fill(mock_minus_init_mom->Y() - mock_minus_init_mom->Y());
    h_mom_res_z[0][0].Fill(mock_plus_init_mom->Z()  - mock_plus_init_mom->Z());
    h_mom_res_z[0][1].Fill(mock_minus_init_mom->Z() - mock_minus_init_mom->Z());
    h_vtx_x[0][0].Fill(mock_vtx->X());
    h_vtx_x[0][1].Fill(mock_vtx->X());
    h_vtx_y[0][0].Fill(mock_vtx->Y());
    h_vtx_y[0][1].Fill(mock_vtx->Y());
//    h_ssd_res_x[0][0].Fill(mock_plus_ssd_lpos->X()        - mock_plus_ssd_lpos->X());
//    h_ssd_res_x[0][1].Fill(mock_minus_ssd_lpos->X()       - mock_minus_ssd_lpos->X());
//    h_ssd_res_y[0][0].Fill(mock_plus_ssd_lpos->Y()        - mock_plus_ssd_lpos->Y());
//    h_ssd_res_y[0][1].Fill(mock_minus_ssd_lpos->Y()       - mock_minus_ssd_lpos->Y());
//    h_gtr100_res_x[0][0].Fill(mock_plus_gtr100_lpos->X()  - mock_plus_gtr100_lpos->X());
//    h_gtr100_res_x[0][1].Fill(mock_minus_gtr100_lpos->X() - mock_minus_gtr100_lpos->X());
//    h_gtr100_res_y[0][0].Fill(mock_plus_gtr100_lpos->Y()  - mock_plus_gtr100_lpos->Y());
//    h_gtr100_res_y[0][1].Fill(mock_minus_gtr100_lpos->Y() - mock_minus_gtr100_lpos->Y());
//    h_gtr200_res_x[0][0].Fill(mock_plus_gtr200_lpos->X()  - mock_plus_gtr200_lpos->X());
//    h_gtr200_res_x[0][1].Fill(mock_minus_gtr200_lpos->X() - mock_minus_gtr200_lpos->X());
//    h_gtr200_res_y[0][0].Fill(mock_plus_gtr200_lpos->Y()  - mock_plus_gtr200_lpos->Y());
//    h_gtr200_res_y[0][1].Fill(mock_minus_gtr200_lpos->Y() - mock_minus_gtr200_lpos->Y());
//    h_gtr300_res_x[0][0].Fill(mock_plus_gtr300_lpos->X()  - mock_plus_gtr300_lpos->X());
//    h_gtr300_res_x[0][1].Fill(mock_minus_gtr300_lpos->X() - mock_minus_gtr300_lpos->X());
//    h_gtr300_res_y[0][0].Fill(mock_plus_gtr300_lpos->Y()  - mock_plus_gtr300_lpos->Y());
//    h_gtr300_res_y[0][1].Fill(mock_minus_gtr300_lpos->Y() - mock_minus_gtr300_lpos->Y());
    h_ssd_res_x[0][0].Fill(plus_ssd_lpos->X()        - mock_plus_ssd_lpos->X());
    h_ssd_res_x[0][1].Fill(minus_ssd_lpos->X()       - mock_minus_ssd_lpos->X());
    h_ssd_res_y[0][0].Fill(plus_ssd_lpos->Y()        - mock_plus_ssd_lpos->Y());
    h_ssd_res_y[0][1].Fill(minus_ssd_lpos->Y()       - mock_minus_ssd_lpos->Y());
    h_gtr100_res_x[0][0].Fill(plus_gtr100_lpos->X()  - mock_plus_gtr100_lpos->X());
    h_gtr100_res_x[0][1].Fill(minus_gtr100_lpos->X() - mock_minus_gtr100_lpos->X());
    h_gtr100_res_y[0][0].Fill(plus_gtr100_lpos->Y()  - mock_plus_gtr100_lpos->Y());
    h_gtr100_res_y[0][1].Fill(minus_gtr100_lpos->Y() - mock_minus_gtr100_lpos->Y());
    h_gtr200_res_x[0][0].Fill(plus_gtr200_lpos->X()  - mock_plus_gtr200_lpos->X());
    h_gtr200_res_x[0][1].Fill(minus_gtr200_lpos->X() - mock_minus_gtr200_lpos->X());
    h_gtr200_res_y[0][0].Fill(plus_gtr200_lpos->Y()  - mock_plus_gtr200_lpos->Y());
    h_gtr200_res_y[0][1].Fill(minus_gtr200_lpos->Y() - mock_minus_gtr200_lpos->Y());
    h_gtr300_res_x[0][0].Fill(plus_gtr300_lpos->X()  - mock_plus_gtr300_lpos->X());
    h_gtr300_res_x[0][1].Fill(minus_gtr300_lpos->X() - mock_minus_gtr300_lpos->X());
    h_gtr300_res_y[0][0].Fill(plus_gtr300_lpos->Y()  - mock_plus_gtr300_lpos->Y());
    h_gtr300_res_y[0][1].Fill(minus_gtr300_lpos->Y() - mock_minus_gtr300_lpos->Y());
    h_mass[0].Fill(mock_mass);
    // pre fit
    h_mom_res_x[1][0].Fill(pre_fit_plus_init_mom->X()  - mock_plus_init_mom->X());
    h_mom_res_x[1][1].Fill(pre_fit_minus_init_mom->X() - mock_minus_init_mom->X());
    h_mom_res_y[1][0].Fill(pre_fit_plus_init_mom->Y()  - mock_plus_init_mom->Y());
    h_mom_res_y[1][1].Fill(pre_fit_minus_init_mom->Y() - mock_minus_init_mom->Y());
    h_mom_res_z[1][0].Fill(pre_fit_plus_init_mom->Z()  - mock_plus_init_mom->Z());
    h_mom_res_z[1][1].Fill(pre_fit_minus_init_mom->Z() - mock_minus_init_mom->Z());
    h_vtx_x[1][0].Fill(pre_fit_plus_init_pos->X());
    h_vtx_x[1][1].Fill(pre_fit_minus_init_pos->X());
    h_vtx_y[1][0].Fill(pre_fit_plus_init_pos->Y());
    h_vtx_y[1][1].Fill(pre_fit_minus_init_pos->Y());
    h_ssd_res_x[1][0].Fill(pre_fit_plus_ssd_lpos->X()        - mock_plus_ssd_lpos->X());
    h_ssd_res_x[1][1].Fill(pre_fit_minus_ssd_lpos->X()       - mock_minus_ssd_lpos->X());
    h_ssd_res_y[1][0].Fill(pre_fit_plus_ssd_lpos->Y()        - mock_plus_ssd_lpos->Y());
    h_ssd_res_y[1][1].Fill(pre_fit_minus_ssd_lpos->Y()       - mock_minus_ssd_lpos->Y());
    h_gtr100_res_x[1][0].Fill(pre_fit_plus_gtr100_lpos->X()  - mock_plus_gtr100_lpos->X());
    h_gtr100_res_x[1][1].Fill(pre_fit_minus_gtr100_lpos->X() - mock_minus_gtr100_lpos->X());
    h_gtr100_res_y[1][0].Fill(pre_fit_plus_gtr100_lpos->Y()  - mock_plus_gtr100_lpos->Y());
    h_gtr100_res_y[1][1].Fill(pre_fit_minus_gtr100_lpos->Y() - mock_minus_gtr100_lpos->Y());
    h_gtr200_res_x[1][0].Fill(pre_fit_plus_gtr200_lpos->X()  - mock_plus_gtr200_lpos->X());
    h_gtr200_res_x[1][1].Fill(pre_fit_minus_gtr200_lpos->X() - mock_minus_gtr200_lpos->X());
    h_gtr200_res_y[1][0].Fill(pre_fit_plus_gtr200_lpos->Y()  - mock_plus_gtr200_lpos->Y());
    h_gtr200_res_y[1][1].Fill(pre_fit_minus_gtr200_lpos->Y() - mock_minus_gtr200_lpos->Y());
    h_gtr300_res_x[1][0].Fill(pre_fit_plus_gtr300_lpos->X()  - mock_plus_gtr300_lpos->X());
    h_gtr300_res_x[1][1].Fill(pre_fit_minus_gtr300_lpos->X() - mock_minus_gtr300_lpos->X());
    h_gtr300_res_y[1][0].Fill(pre_fit_plus_gtr300_lpos->Y()  - mock_plus_gtr300_lpos->Y());
    h_gtr300_res_y[1][1].Fill(pre_fit_minus_gtr300_lpos->Y() - mock_minus_gtr300_lpos->Y());
    h_mass[1].Fill(pre_fit_mass);
    // single fit
    h_mom_res_x[2][0].Fill(fit_plus_init_mom->X()  - mock_plus_init_mom->X());
    h_mom_res_x[2][1].Fill(fit_minus_init_mom->X() - mock_minus_init_mom->X());
    h_mom_res_y[2][0].Fill(fit_plus_init_mom->Y()  - mock_plus_init_mom->Y());
    h_mom_res_y[2][1].Fill(fit_minus_init_mom->Y() - mock_minus_init_mom->Y());
    h_mom_res_z[2][0].Fill(fit_plus_init_mom->Z()  - mock_plus_init_mom->Z());
    h_mom_res_z[2][1].Fill(fit_minus_init_mom->Z() - mock_minus_init_mom->Z());
    h_vtx_x[2][0].Fill(fit_plus_init_pos->X());
    h_vtx_x[2][1].Fill(fit_minus_init_pos->X());
    h_vtx_y[2][0].Fill(fit_plus_init_pos->Y());
    h_vtx_y[2][1].Fill(fit_minus_init_pos->Y());
    h_ssd_res_x[2][0].Fill(fit_plus_ssd_lpos->X()        - mock_plus_ssd_lpos->X());
    h_ssd_res_x[2][1].Fill(fit_minus_ssd_lpos->X()       - mock_minus_ssd_lpos->X());
    h_ssd_res_y[2][0].Fill(fit_plus_ssd_lpos->Y()        - mock_plus_ssd_lpos->Y());
    h_ssd_res_y[2][1].Fill(fit_minus_ssd_lpos->Y()       - mock_minus_ssd_lpos->Y());
    h_gtr100_res_x[2][0].Fill(fit_plus_gtr100_lpos->X()  - mock_plus_gtr100_lpos->X());
    h_gtr100_res_x[2][1].Fill(fit_minus_gtr100_lpos->X() - mock_minus_gtr100_lpos->X());
    h_gtr100_res_y[2][0].Fill(fit_plus_gtr100_lpos->Y()  - mock_plus_gtr100_lpos->Y());
    h_gtr100_res_y[2][1].Fill(fit_minus_gtr100_lpos->Y() - mock_minus_gtr100_lpos->Y());
    h_gtr200_res_x[2][0].Fill(fit_plus_gtr200_lpos->X()  - mock_plus_gtr200_lpos->X());
    h_gtr200_res_x[2][1].Fill(fit_minus_gtr200_lpos->X() - mock_minus_gtr200_lpos->X());
    h_gtr200_res_y[2][0].Fill(fit_plus_gtr200_lpos->Y()  - mock_plus_gtr200_lpos->Y());
    h_gtr200_res_y[2][1].Fill(fit_minus_gtr200_lpos->Y() - mock_minus_gtr200_lpos->Y());
    h_gtr300_res_x[2][0].Fill(fit_plus_gtr300_lpos->X()  - mock_plus_gtr300_lpos->X());
    h_gtr300_res_x[2][1].Fill(fit_minus_gtr300_lpos->X() - mock_minus_gtr300_lpos->X());
    h_gtr300_res_y[2][0].Fill(fit_plus_gtr300_lpos->Y()  - mock_plus_gtr300_lpos->Y());
    h_gtr300_res_y[2][1].Fill(fit_minus_gtr300_lpos->Y() - mock_minus_gtr300_lpos->Y());
    h_mass[2].Fill(fit_mass);
    // pair fit
    h_mom_res_x[3][0].Fill(pair_fit_plus_init_mom->X()  - mock_plus_init_mom->X());
    h_mom_res_x[3][1].Fill(pair_fit_minus_init_mom->X() - mock_minus_init_mom->X());
    h_mom_res_y[3][0].Fill(pair_fit_plus_init_mom->Y()  - mock_plus_init_mom->Y());
    h_mom_res_y[3][1].Fill(pair_fit_minus_init_mom->Y() - mock_minus_init_mom->Y());
    h_mom_res_z[3][0].Fill(pair_fit_plus_init_mom->Z()  - mock_plus_init_mom->Z());
    h_mom_res_z[3][1].Fill(pair_fit_minus_init_mom->Z() - mock_minus_init_mom->Z());
    h_vtx_x[3][0].Fill(pair_fit_vtx->X());
    h_vtx_x[3][1].Fill(pair_fit_vtx->X());
    h_vtx_y[3][0].Fill(pair_fit_vtx->Y());
    h_vtx_y[3][1].Fill(pair_fit_vtx->Y());
    h_ssd_res_x[3][0].Fill(pair_fit_plus_ssd_lpos->X()        - mock_plus_ssd_lpos->X());
    h_ssd_res_x[3][1].Fill(pair_fit_minus_ssd_lpos->X()       - mock_minus_ssd_lpos->X());
    h_ssd_res_y[3][0].Fill(pair_fit_plus_ssd_lpos->Y()        - mock_plus_ssd_lpos->Y());
    h_ssd_res_y[3][1].Fill(pair_fit_minus_ssd_lpos->Y()       - mock_minus_ssd_lpos->Y());
    h_gtr100_res_x[3][0].Fill(pair_fit_plus_gtr100_lpos->X()  - mock_plus_gtr100_lpos->X());
    h_gtr100_res_x[3][1].Fill(pair_fit_minus_gtr100_lpos->X() - mock_minus_gtr100_lpos->X());
    h_gtr100_res_y[3][0].Fill(pair_fit_plus_gtr100_lpos->Y()  - mock_plus_gtr100_lpos->Y());
    h_gtr100_res_y[3][1].Fill(pair_fit_minus_gtr100_lpos->Y() - mock_minus_gtr100_lpos->Y());
    h_gtr200_res_x[3][0].Fill(pair_fit_plus_gtr200_lpos->X()  - mock_plus_gtr200_lpos->X());
    h_gtr200_res_x[3][1].Fill(pair_fit_minus_gtr200_lpos->X() - mock_minus_gtr200_lpos->X());
    h_gtr200_res_y[3][0].Fill(pair_fit_plus_gtr200_lpos->Y()  - mock_plus_gtr200_lpos->Y());
    h_gtr200_res_y[3][1].Fill(pair_fit_minus_gtr200_lpos->Y() - mock_minus_gtr200_lpos->Y());
    h_gtr300_res_x[3][0].Fill(pair_fit_plus_gtr300_lpos->X()  - mock_plus_gtr300_lpos->X());
    h_gtr300_res_x[3][1].Fill(pair_fit_minus_gtr300_lpos->X() - mock_minus_gtr300_lpos->X());
    h_gtr300_res_y[3][0].Fill(pair_fit_plus_gtr300_lpos->Y()  - mock_plus_gtr300_lpos->Y());
    h_gtr300_res_y[3][1].Fill(pair_fit_minus_gtr300_lpos->Y() - mock_minus_gtr300_lpos->Y());
    h_mass[3].Fill(pair_fit_mass);
    
    array<TVector3, 3> vtx2;
    array<TVector3, 3> pmom2;
    array<TVector3, 3> mmom2;
    array<double,   3> mass2;
    vtx2[0]  = *mock_vtx;
    vtx2[1]  = *wo_fit_vtx;
    vtx2[2]  = *pair_fit_vtx;
    pmom2[0] = *mock_plus_init_mom;
    pmom2[1] = *wo_fit_plus_init_mom;
    pmom2[2] = *pair_fit_plus_init_mom;
    mmom2[0] = *mock_minus_init_mom;
    mmom2[1] = *wo_fit_minus_init_mom;
    mmom2[2] = *pair_fit_minus_init_mom;
    mass2[0] = mock_mass;
    mass2[1] = wo_fit_mass;
    mass2[2] = pair_fit_mass;
    auto d = DirID();
    for (int i = 0; i < 3; ++i) {
      h2_vtx_x[d][i]->Fill(vtx2[i].X());
      h2_vtx_y[d][i]->Fill(vtx2[i].Y());
      h2_vtx_z[d][i]->Fill(vtx2[i].Z());
      h2_plus_mom[d][i]->Fill(pmom2[i].Mag());
      h2_plus_mom_x[d][i]->Fill(pmom2[i].X());
      h2_plus_mom_y[d][i]->Fill(pmom2[i].Y());
      h2_plus_mom_z[d][i]->Fill(pmom2[i].Z());
      h2_minus_mom[d][i]->Fill(mmom2[i].Mag());
      h2_minus_mom_x[d][i]->Fill(mmom2[i].X());
      h2_minus_mom_y[d][i]->Fill(mmom2[i].Y());
      h2_minus_mom_z[d][i]->Fill(mmom2[i].Z());
      h2_mom_angle[d][i]->Fill(pmom2[i].Angle(mmom2[i]));
      h2_mass[d][i]->Fill(mass2[i]);
      h2_mass_vtxz[d][i]->Fill(vtx2[i].Z(), mass2[i]);
      h2_vtx_x[4][i]->Fill(vtx2[i].X());
      h2_vtx_y[4][i]->Fill(vtx2[i].Y());
      h2_vtx_z[4][i]->Fill(vtx2[i].Z());
      h2_plus_mom[4][i]->Fill(pmom2[i].Mag());
      h2_plus_mom_x[4][i]->Fill(pmom2[i].X());
      h2_plus_mom_y[4][i]->Fill(pmom2[i].Y());
      h2_plus_mom_z[4][i]->Fill(pmom2[i].Z());
      h2_minus_mom[4][i]->Fill(mmom2[i].Mag());
      h2_minus_mom_x[4][i]->Fill(mmom2[i].X());
      h2_minus_mom_y[4][i]->Fill(mmom2[i].Y());
      h2_minus_mom_z[4][i]->Fill(mmom2[i].Z());
      h2_mom_angle[4][i]->Fill(pmom2[i].Angle(mmom2[i]));
      h2_mass[4][i]->Fill(mass2[i]);
      h2_mass_vtxz[4][i]->Fill(vtx2[i].Z(), mass2[i]);
      if (i < 2) {
        h2_vtx_x_res[d][i]->Fill(vtx2[1 + i].X() - vtx2[0].X());
        h2_vtx_y_res[d][i]->Fill(vtx2[1 + i].Y() - vtx2[0].Y());
        h2_vtx_z_res[d][i]->Fill(vtx2[1 + i].Z() - vtx2[0].Z());
        h2_plus_mom_res[d][i]->Fill(pmom2[1 + i].Mag() - pmom2[0].Mag());
        h2_plus_mom_x_res[d][i]->Fill(pmom2[1 + i].X() - pmom2[0].X());
        h2_plus_mom_y_res[d][i]->Fill(pmom2[1 + i].Y() - pmom2[0].Y());
        h2_plus_mom_z_res[d][i]->Fill(pmom2[1 + i].Z() - pmom2[0].Z());
        h2_minus_mom_res[d][i]->Fill(mmom2[1 + i].Mag() - mmom2[0].Mag());
        h2_minus_mom_x_res[d][i]->Fill(mmom2[1 + i].X() - mmom2[0].X());
        h2_minus_mom_y_res[d][i]->Fill(mmom2[1 + i].Y() - mmom2[0].Y());
        h2_minus_mom_z_res[d][i]->Fill(mmom2[1 + i].Z() - mmom2[0].Z());
        h2_mom_angle_res[d][i]->Fill(pmom2[1 + i].Angle(mmom2[1 + i]) - pmom2[0].Angle(mmom2[0]));
        h2_mass_res[d][i]->Fill(mass2[1 + i] - mass2[0]);
        h2_vtx_x_res[4][i]->Fill(vtx2[1 + i].X() - vtx2[0].X());
        h2_vtx_y_res[4][i]->Fill(vtx2[1 + i].Y() - vtx2[0].Y());
        h2_vtx_z_res[4][i]->Fill(vtx2[1 + i].Z() - vtx2[0].Z());
        h2_plus_mom_res[4][i]->Fill(pmom2[1 + i].Mag() - pmom2[0].Mag());
        h2_plus_mom_x_res[4][i]->Fill(pmom2[1 + i].X() - pmom2[0].X());
        h2_plus_mom_y_res[4][i]->Fill(pmom2[1 + i].Y() - pmom2[0].Y());
        h2_plus_mom_z_res[4][i]->Fill(pmom2[1 + i].Z() - pmom2[0].Z());
        h2_minus_mom_res[4][i]->Fill(mmom2[1 + i].Mag() - mmom2[0].Mag());
        h2_minus_mom_x_res[4][i]->Fill(mmom2[1 + i].X() - mmom2[0].X());
        h2_minus_mom_y_res[4][i]->Fill(mmom2[1 + i].Y() - mmom2[0].Y());
        h2_minus_mom_z_res[4][i]->Fill(mmom2[1 + i].Z() - mmom2[0].Z());
        h2_mom_angle_res[4][i]->Fill(pmom2[1 + i].Angle(mmom2[1 + i]) - pmom2[0].Angle(mmom2[0]));
        h2_mass_res[4][i]->Fill(mass2[1 + i] - mass2[0]);
      }
    }
  }

  auto canvas = TCanvas();
  auto pdf_name = out_name + ".pdf";
  canvas.Print(pdf_name + "[");
  Draw(pdf_name, &h_mom_res_x,    &canvas);
  Draw(pdf_name, &h_mom_res_y,    &canvas);
  Draw(pdf_name, &h_mom_res_z,    &canvas);
  Draw(pdf_name, &h_vtx_x,        &canvas);
  Draw(pdf_name, &h_vtx_y,        &canvas);
  Draw(pdf_name, &h_ssd_res_x,    &canvas);
  Draw(pdf_name, &h_ssd_res_y,    &canvas);
  Draw(pdf_name, &h_gtr100_res_x, &canvas);
  Draw(pdf_name, &h_gtr100_res_y, &canvas);
  Draw(pdf_name, &h_gtr200_res_x, &canvas);
  Draw(pdf_name, &h_gtr200_res_y, &canvas);
  Draw(pdf_name, &h_gtr300_res_x, &canvas);
  Draw(pdf_name, &h_gtr300_res_y, &canvas);
  canvas.Clear();
  canvas.Divide(2, 2);
  for (int i = 0; i < 4; ++i) {
    canvas.cd(1 + i);
    h_mass[i].Draw();
  }
  canvas.Print(pdf_name);
  Draw(pdf_name, &h2_vtx_x,           &canvas);
  Draw(pdf_name, &h2_vtx_y,           &canvas);
  Draw(pdf_name, &h2_vtx_z,           &canvas);
  Draw(pdf_name, &h2_plus_mom,        &canvas);
  Draw(pdf_name, &h2_plus_mom_x,      &canvas);
  Draw(pdf_name, &h2_plus_mom_y,      &canvas);
  Draw(pdf_name, &h2_plus_mom_z,      &canvas);
  Draw(pdf_name, &h2_minus_mom,       &canvas);
  Draw(pdf_name, &h2_minus_mom_x,     &canvas);
  Draw(pdf_name, &h2_minus_mom_y,     &canvas);
  Draw(pdf_name, &h2_minus_mom_z,     &canvas);
  Draw(pdf_name, &h2_mom_angle,       &canvas);
  Draw(pdf_name, &h2_mass,            &canvas);
  Draw(pdf_name, &h2_mass_vtxz,       &canvas);
  Draw(pdf_name, &h2_vtx_x_res,       &canvas);
  Draw(pdf_name, &h2_vtx_y_res,       &canvas);
  Draw(pdf_name, &h2_vtx_z_res,       &canvas);
  Draw(pdf_name, &h2_plus_mom_res,    &canvas);
  Draw(pdf_name, &h2_plus_mom_x_res,  &canvas);
  Draw(pdf_name, &h2_plus_mom_y_res,  &canvas);
  Draw(pdf_name, &h2_plus_mom_z_res,  &canvas);
  Draw(pdf_name, &h2_minus_mom_res,   &canvas);
  Draw(pdf_name, &h2_minus_mom_x_res, &canvas);
  Draw(pdf_name, &h2_minus_mom_y_res, &canvas);
  Draw(pdf_name, &h2_minus_mom_z_res, &canvas);
  Draw(pdf_name, &h2_mom_angle_res,   &canvas);
  Draw(pdf_name, &h2_mass_res,        &canvas);
  canvas.Print(pdf_name + "]");
  file.Write();
}
