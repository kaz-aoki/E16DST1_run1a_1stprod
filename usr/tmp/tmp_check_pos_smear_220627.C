#define tmp_check_pos_smear_220627_cxx
#include "tmp_check_pos_smear_220627.h"

#include <array>
#include <iostream>

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TROOT.h>

using namespace std;

void tmp_check_pos_smear_220627::Loop(int max_events, const TString& out_name) {
//   In a ROOT session, you can do:
//      root> .L tmp_check_pos_smear_220627.C
//      root> tmp_check_pos_smear_220627 t
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
  
  gROOT->ProcessLine(".x ~/.rootlogon.C");
  auto out_file = TFile(out_name + ".root", "recreate");
  auto h_ssd_x_res      = TH1F("h_ssd_x_res",      "h_ssd_x_res",      600, -3.,  3.);
  auto h_gtr100_x_res   = TH1F("h_gtr100_x_res",   "h_gtr100_x_res",   600, -3.,  3.);
  auto h_gtr100_y_res   = TH1F("h_gtr100_y_res",   "h_gtr100_y_res",   600, -3.,  3.);
  auto h_gtr200_x_res   = TH1F("h_gtr200_x_res",   "h_gtr200_x_res",   600, -3.,  3.);
  auto h_gtr200_y_res   = TH1F("h_gtr200_y_res",   "h_gtr200_y_res",   600, -3.,  3.);
  auto h_gtr300_x_res   = TH1F("h_gtr300_x_res",   "h_gtr300_x_res",   600, -3.,  3.);
  auto h_gtr300_y_res   = TH1F("h_gtr300_y_res",   "h_gtr300_y_res",   600, -3.,  3.);
  auto h_ssd_merged     = TH1F("h_ssd_merged",     "h_ssd_merged",       5, -0.5, 4.5);
  auto h_gtr100x_merged = TH1F("h_gtr100x_merged", "h_gtr100x_merged",   5, -0.5, 4.5);
  auto h_gtr100y_merged = TH1F("h_gtr100y_merged", "h_gtr100y_merged",   5, -0.5, 4.5);
  auto h_gtr200x_merged = TH1F("h_gtr200x_merged", "h_gtr200x_merged",   5, -0.5, 4.5);
  auto h_gtr200y_merged = TH1F("h_gtr200y_merged", "h_gtr200y_merged",   5, -0.5, 4.5);
  auto h_gtr300x_merged = TH1F("h_gtr300x_merged", "h_gtr300x_merged",   5, -0.5, 4.5);
  auto h_gtr300y_merged = TH1F("h_gtr300y_merged", "h_gtr300y_merged",   5, -0.5, 4.5);
  int n_merged;
//  array<int, 2> n_merged;
//  array<TVector3, 2> pos;
  if (max_events == -1) {
    max_events = nentries;
  }
  for (Long64_t jentry = 0; jentry < max_events; ++jentry) {
    if (jentry % 1000 == 0) {
      cout << jentry << " / " << nentries << endl;
    }
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
//    if (Cut(ientry) < 0) continue;
//    auto id = mock_n_tracks - 2;
//    for (int i = 0; i < 2; ++i) {
//      pos[i].SetXYZ(mock_ssd_lpos_x->at(id + i), mock_ssd_lpos_y->at(id + i), mock_ssd_lpos_z->at(id + i));
//    }
//    n_merged.fill(0);
    n_merged = 0;
    for (int i = 0; i < n_ssd_clusters; ++i) {
      if (ssd_cluster_is_merged->at(i)) {
        ++n_merged;
      }
    }
    h_ssd_merged.Fill(n_merged);
    
    n_merged = 0;
    for (int i = 0; i < n_gtr100x_clusters; ++i) {
      if (gtr100x_cluster_is_merged->at(i)) {
        ++n_merged;
      }
    }
    h_gtr100x_merged.Fill(n_merged);
    
    n_merged = 0;
    for (int i = 0; i < n_gtr100y_clusters; ++i) {
      if (gtr100y_cluster_is_merged->at(i)) {
        ++n_merged;
      }
    }
    h_gtr100y_merged.Fill(n_merged);
    
    n_merged = 0;
    for (int i = 0; i < n_gtr200x_clusters; ++i) {
      if (gtr200x_cluster_is_merged->at(i)) {
        ++n_merged;
      }
    }
    h_gtr200x_merged.Fill(n_merged);
    
    n_merged = 0;
    for (int i = 0; i < n_gtr200y_clusters; ++i) {
      if (gtr200y_cluster_is_merged->at(i)) {
        ++n_merged;
      }
    }
    h_gtr200y_merged.Fill(n_merged);
    
    n_merged = 0;
    for (int i = 0; i < n_gtr300x_clusters; ++i) {
      if (gtr300x_cluster_is_merged->at(i)) {
        ++n_merged;
      }
    }
    h_gtr300x_merged.Fill(n_merged);
    
    n_merged = 0;
    for (int i = 0; i < n_gtr300y_clusters; ++i) {
      if (gtr300y_cluster_is_merged->at(i)) {
        ++n_merged;
      }
    }
    h_gtr300y_merged.Fill(n_merged);
    if (!sim_track_detected->at(0) && !sim_track_detected->at(1)) {
      continue;
    }
    array<bool, 2> is_filled;
    is_filled.fill(false);
    for (int i = 0; i < n_cands; ++i) {
      if (!is_sim_track->at(i)) {
        continue;
      }
      int id = mock_n_tracks;
      if (rk_charge->at(i) == 1) {
        is_filled[0] = true;
        id -= 2;
      } else {
        is_filled[0] = false;
        id -= 1;
      }
      h_ssd_x_res.Fill(rk_hit_ssd_x->at(i) - mock_ssd_lpos_x->at(id));
      h_gtr100_x_res.Fill(rk_hit_gtr100_tx2->at(i) - mock_gtr100_lpos_x->at(id));
      h_gtr100_y_res.Fill(rk_hit_gtr100_ty->at(i)  - mock_gtr100_lpos_y->at(id));
      h_gtr200_x_res.Fill(rk_hit_gtr200_tx2->at(i) - mock_gtr200_lpos_x->at(id));
      h_gtr200_y_res.Fill(rk_hit_gtr200_ty->at(i)  - mock_gtr200_lpos_y->at(id));
      h_gtr300_x_res.Fill(rk_hit_gtr300_tx2->at(i) - mock_gtr300_lpos_x->at(id));
      h_gtr300_y_res.Fill(rk_hit_gtr300_ty->at(i)  - mock_gtr300_lpos_y->at(id));
      if (is_filled[0] && is_filled[1]) {
        break;
      }
    }
  }
  out_file.Write();

  auto canvas = TCanvas();
  canvas.Print(out_name + ".pdf[");
  canvas.Divide(4, 2);
  canvas.cd(1);
  h_ssd_x_res.Draw();
  canvas.cd(3);
  h_gtr100_x_res.Draw();
  canvas.cd(4);
  h_gtr100_y_res.Draw();
  canvas.cd(5);
  h_gtr200_x_res.Draw();
  canvas.cd(6);
  h_gtr200_y_res.Draw();
  canvas.cd(7);
  h_gtr300_x_res.Draw();
  canvas.cd(8);
  h_gtr300_y_res.Draw();
  canvas.Print(out_name + ".pdf");
  canvas.Print(out_name + ".pdf]");
}
