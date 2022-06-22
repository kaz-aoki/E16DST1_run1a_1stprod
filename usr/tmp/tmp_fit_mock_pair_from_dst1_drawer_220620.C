#define tmp_fit_mock_pair_from_dst1_drawer_220620_cxx
#include "tmp_fit_mock_pair_from_dst1_drawer_220620.h"

#include <array>
#include <iostream>

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

using namespace std;

void tmp_fit_mock_pair_from_dst1_drawer_220620::Draw(const TString& name, array<array<TH1F, 2>, 4>* hists, TCanvas* canvas) {
  canvas->Clear();
  canvas->Divide(4, 2);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 2; ++j) {
      canvas->cd(1 + 2 * i + j);
      hists->at(i)[j].Draw();
    }
  }
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
  array<TH1F, 4> h_mass;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 2; ++j) {
      h_mom_res_x[i][j]    = TH1F(Form("h_mom_res_x_%d_%d",    i, j), Form("h_mom_res_x_%d_%d",    i, j), 100, -5., 5.);
      h_mom_res_y[i][j]    = TH1F(Form("h_mom_res_y_%d_%d",    i, j), Form("h_mom_res_y_%d_%d",    i, j), 100, -5., 5.);
      h_mom_res_z[i][j]    = TH1F(Form("h_mom_res_z_%d_%d",    i, j), Form("h_mom_res_z_%d_%d",    i, j), 100, -5., 5.);
      h_vtx_x[i][j]        = TH1F(Form("h_vtx_x_%d_%d",        i, j), Form("h_vtx_x_%d_%d",        i, j), 100, -5., 5.);
      h_vtx_y[i][j]        = TH1F(Form("h_vtx_y_%d_%d",        i, j), Form("h_vtx_y_%d_%d",        i, j), 100, -5., 5.);
      h_ssd_res_x[i][j]    = TH1F(Form("h_ssd_res_x_%d_%d",    i, j), Form("h_ssd_res_x_%d_%d",    i, j), 100, -5., 5.);
      h_ssd_res_y[i][j]    = TH1F(Form("h_ssd_res_y_%d_%d",    i, j), Form("h_ssd_res_y_%d_%d",    i, j), 100, -5., 5.);
      h_gtr100_res_x[i][j] = TH1F(Form("h_gtr100_res_x_%d_%d", i, j), Form("h_gtr100_res_x_%d_%d", i, j), 100, -5., 5.);
      h_gtr100_res_y[i][j] = TH1F(Form("h_gtr100_res_y_%d_%d", i, j), Form("h_gtr100_res_y_%d_%d", i, j), 100, -5., 5.);
      h_gtr200_res_x[i][j] = TH1F(Form("h_gtr200_res_x_%d_%d", i, j), Form("h_gtr200_res_x_%d_%d", i, j), 100, -5., 5.);
      h_gtr200_res_y[i][j] = TH1F(Form("h_gtr200_res_y_%d_%d", i, j), Form("h_gtr200_res_y_%d_%d", i, j), 100, -5., 5.);
      h_gtr300_res_x[i][j] = TH1F(Form("h_gtr300_res_x_%d_%d", i, j), Form("h_gtr300_res_x_%d_%d", i, j), 100, -5., 5.);
      h_gtr300_res_y[i][j] = TH1F(Form("h_gtr300_res_y_%d_%d", i, j), Form("h_gtr300_res_y_%d_%d", i, j), 100, -5., 5.);
    }
    h_mass[i] = TH1F(Form("h_mass_%d", i), Form("h_mass_%d", i), 80, 0.8, 1.2);
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
  }

  auto canvas = TCanvas();
  canvas.Print(out_name + "[");
  Draw(out_name, &h_mom_res_x,    &canvas);
  Draw(out_name, &h_mom_res_y,    &canvas);
  Draw(out_name, &h_mom_res_z,    &canvas);
  Draw(out_name, &h_vtx_x,        &canvas);
  Draw(out_name, &h_vtx_y,        &canvas);
  Draw(out_name, &h_ssd_res_x,    &canvas);
  Draw(out_name, &h_ssd_res_y,    &canvas);
  Draw(out_name, &h_gtr100_res_x, &canvas);
  Draw(out_name, &h_gtr100_res_y, &canvas);
  Draw(out_name, &h_gtr200_res_x, &canvas);
  Draw(out_name, &h_gtr200_res_y, &canvas);
  Draw(out_name, &h_gtr300_res_x, &canvas);
  Draw(out_name, &h_gtr300_res_y, &canvas);
  canvas.Clear();
  canvas.Divide(2, 2);
  for (int i = 0; i < 4; ++i) {
    canvas.cd(1 + i);
    h_mass[i].Draw();
  }
  canvas.Print(out_name);
  canvas.Print(out_name + "]");
}
