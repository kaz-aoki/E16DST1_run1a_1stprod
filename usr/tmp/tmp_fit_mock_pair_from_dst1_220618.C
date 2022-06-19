#define tmp_fit_mock_pair_from_dst1_220618_cxx
#include "tmp_fit_mock_pair_from_dst1_220618.h"

#include <iostream>

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_MagneticFieldMap.hh"
#include "E16ANA_MultiTrack.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "tmp_fit_mock_pair_220616_parameter.hh"

using namespace std;
using namespace tmp_fit_mock_pair_220616_parameter;

double tmp_fit_mock_pair_from_dst1_220618::CalcMass(const TVector3& mom0, const TVector3& mom1) {
  constexpr double kElectronMass = 511.99894641e-6;
  constexpr double kElectronMass2 = kElectronMass * kElectronMass;
//  constexpr double kPionMass = 139.57039e-3;
//  constexpr double kPionMass2 = kPionMass * kPionMass;
//  constexpr double kProtonMass    = 938.272081e-3;
//  constexpr double kProtonMass2   = kProtonMass * kProtonMass;
  double mass2[2];
  mass2[0] = kElectronMass2;
  mass2[1] = kElectronMass2;
  double p0 = mom0.X() * mom0.X() + mom0.Y() * mom0.Y() + mom0.Z() * mom0.Z();
  double p1 = mom1.X() * mom1.X() + mom1.Y() * mom1.Y() + mom1.Z() * mom1.Z();
  double e0 = sqrt(p0 + mass2[0]);
  double e1 = sqrt(p1 + mass2[1]);
  double p0p1 = mom0.X() * mom1.X() + mom0.Y() * mom1.Y() + mom0.Z() * mom1.Z();
  return sqrt(mass2[0] + mass2[1] + 2. * (e0 * e1 - p0p1));
}

void tmp_fit_mock_pair_from_dst1_220618::Loop(int max_events, const TString& out_name) {
//   In a ROOT session, you can do:
//      root> .L tmp_fit_mock_pair_from_dst1_220618.C
//      root> tmp_fit_mock_pair_from_dst1_220618 t
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

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  E16ANA_GeometryV2::SetGlobalPointer(geometry);
  auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
  bfield_map->Initialize_binary();
  E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
  E16ANA_MultiTrack fitter(bfield_map, geometry, 2);
  E16ANA_MultiTrack sfitter(bfield_map, geometry, 1);

  auto out_file = TFile(out_name, "recreate");
  auto out_tree = TTree("tree", "tree");
  // common
  int      plus_ssd_mid;
  int      plus_gtr100_mid;
  int      plus_gtr200_mid;
  int      plus_gtr300_mid;
  TVector3 plus_ssd_lpos;
  TVector3 plus_gtr100_lpos;
  TVector3 plus_gtr200_lpos;
  TVector3 plus_gtr300_lpos;
  int      minus_ssd_mid;
  int      minus_gtr100_mid;
  int      minus_gtr200_mid;
  int      minus_gtr300_mid;
  TVector3 minus_ssd_lpos;
  TVector3 minus_gtr100_lpos;
  TVector3 minus_gtr200_lpos;
  TVector3 minus_gtr300_lpos;
  // pre fit
  double   pre_fit_plus_chi2;
  TVector3 pre_fit_plus_init_mom;
  TVector3 pre_fit_plus_init_pos;
  TVector3 pre_fit_plus_ssd_lpos;
  TVector3 pre_fit_plus_gtr100_lpos;
  TVector3 pre_fit_plus_gtr200_lpos;
  TVector3 pre_fit_plus_gtr300_lpos;
  double   pre_fit_minus_chi2;
  TVector3 pre_fit_minus_init_mom;
  TVector3 pre_fit_minus_init_pos;
  TVector3 pre_fit_minus_ssd_lpos;
  TVector3 pre_fit_minus_gtr100_lpos;
  TVector3 pre_fit_minus_gtr200_lpos;
  TVector3 pre_fit_minus_gtr300_lpos;
  double   pre_fit_mass;
  // fit
  double   fit_plus_chi2;
  TVector3 fit_plus_init_mom;
  TVector3 fit_plus_init_pos;
  TVector3 fit_plus_ssd_lpos;
  TVector3 fit_plus_gtr100_lpos;
  TVector3 fit_plus_gtr200_lpos;
  TVector3 fit_plus_gtr300_lpos;
  double   fit_minus_chi2;
  TVector3 fit_minus_init_mom;
  TVector3 fit_minus_init_pos;
  TVector3 fit_minus_ssd_lpos;
  TVector3 fit_minus_gtr100_lpos;
  TVector3 fit_minus_gtr200_lpos;
  TVector3 fit_minus_gtr300_lpos;
  double   fit_mass;
  
  out_tree.Branch("run_id",                    &run_id,          "run_id/I");
  out_tree.Branch("event_id",                  &event_id,        "event_id/I");
  out_tree.Branch("plus_ssd_mid",              &plus_ssd_mid,    "plus_ssd_mid/I");
  out_tree.Branch("plus_gtr100_mid",           &plus_gtr100_mid, "plus_gtr100_mid/I");
  out_tree.Branch("plus_gtr200_mid",           &plus_gtr200_mid, "plus_gtr200_mid/I");
  out_tree.Branch("plus_gtr300_mid",           &plus_gtr300_mid, "plus_gtr300_mid/I");
  out_tree.Branch("plus_ssd_lpos",             &plus_ssd_lpos);
  out_tree.Branch("plus_gtr100_lpos",          &plus_gtr100_lpos);
  out_tree.Branch("plus_gtr200_lpos",          &plus_gtr200_lpos);
  out_tree.Branch("plus_gtr300_lpos",          &plus_gtr300_lpos);
  out_tree.Branch("minus_ssd_mid",             &minus_ssd_mid,    "minus_ssd_mid/I");
  out_tree.Branch("minus_gtr100_mid",          &minus_gtr100_mid, "minus_gtr100_mid/I");
  out_tree.Branch("minus_gtr200_mid",          &minus_gtr200_mid, "minus_gtr200_mid/I");
  out_tree.Branch("minus_gtr300_mid",          &minus_gtr300_mid, "minus_gtr300_mid/I");
  out_tree.Branch("minus_ssd_lpos",            &minus_ssd_lpos);
  out_tree.Branch("minus_gtr100_lpos",         &minus_gtr100_lpos);
  out_tree.Branch("minus_gtr200_lpos",         &minus_gtr200_lpos);
  out_tree.Branch("minus_gtr300_lpos",         &minus_gtr300_lpos);
  out_tree.Branch("pre_fit_plus_chi2",         &pre_fit_plus_chi2, "pre_fit_plus_chi2/D");
  out_tree.Branch("pre_fit_plus_init_mom",     &pre_fit_plus_init_mom);
  out_tree.Branch("pre_fit_plus_init_pos",     &pre_fit_plus_init_pos);
  out_tree.Branch("pre_fit_plus_ssd_lpos",     &pre_fit_plus_ssd_lpos);
  out_tree.Branch("pre_fit_plus_gtr100_lpos",  &pre_fit_plus_gtr100_lpos);
  out_tree.Branch("pre_fit_plus_gtr200_lpos",  &pre_fit_plus_gtr200_lpos);
  out_tree.Branch("pre_fit_plus_gtr300_lpos",  &pre_fit_plus_gtr300_lpos);
  out_tree.Branch("pre_fit_minus_chi2",        &pre_fit_minus_chi2, "pre_fit_minus_chi2/D");
  out_tree.Branch("pre_fit_minus_init_mom",    &pre_fit_minus_init_mom);
  out_tree.Branch("pre_fit_minus_init_pos",    &pre_fit_minus_init_pos);
  out_tree.Branch("pre_fit_minus_ssd_lpos",    &pre_fit_minus_ssd_lpos);
  out_tree.Branch("pre_fit_minus_gtr100_lpos", &pre_fit_minus_gtr100_lpos);
  out_tree.Branch("pre_fit_minus_gtr200_lpos", &pre_fit_minus_gtr200_lpos);
  out_tree.Branch("pre_fit_minus_gtr300_lpos", &pre_fit_minus_gtr300_lpos);
  out_tree.Branch("pre_fit_mass",              &pre_fit_mass, "pre_fit_mass/D");
  out_tree.Branch("fit_plus_chi2",             &fit_plus_chi2, "fit_plus_chi2/D");
  out_tree.Branch("fit_plus_init_mom",         &fit_plus_init_mom);
  out_tree.Branch("fit_plus_init_pos",         &fit_plus_init_pos);
  out_tree.Branch("fit_plus_ssd_lpos",         &fit_plus_ssd_lpos);
  out_tree.Branch("fit_plus_gtr100_lpos",      &fit_plus_gtr100_lpos);
  out_tree.Branch("fit_plus_gtr200_lpos",      &fit_plus_gtr200_lpos);
  out_tree.Branch("fit_plus_gtr300_lpos",      &fit_plus_gtr300_lpos);
  out_tree.Branch("fit_minus_chi2",            &fit_minus_chi2, "fit_minus_chi2/D");
  out_tree.Branch("fit_minus_init_mom",        &fit_minus_init_mom);
  out_tree.Branch("fit_minus_init_pos",        &fit_minus_init_pos);
  out_tree.Branch("fit_minus_ssd_lpos",        &fit_minus_ssd_lpos);
  out_tree.Branch("fit_minus_gtr100_lpos",     &fit_minus_gtr100_lpos);
  out_tree.Branch("fit_minus_gtr200_lpos",     &fit_minus_gtr200_lpos);
  out_tree.Branch("fit_minus_gtr300_lpos",     &fit_minus_gtr300_lpos);
  out_tree.Branch("fit_mass",                  &fit_mass, "fit_mass/D");

  if (max_events == -1) {
    max_events = nentries;
  }
  for (Long64_t jentry = 0; jentry < max_events; ++jentry) {
    if (jentry % 100 == 0) {
      cout << jentry << " / " << nentries << endl;
    }
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
//    if (Cut(ientry) < 0) continue;
    if (!sim_track_detected->at(0) || !sim_track_detected->at(1)) {
      continue;
    }
    array<bool, 2> is_sim_filled;
    is_sim_filled.fill(false);
    for (int i = 0; i < n_cands; ++i) {
      if (!is_sim_track->at(i)) {
        continue;
      }
      if (rk_charge->at(i) == 1) {
        is_sim_filled[0] = true;
        plus_ssd_mid     = rk_fit_ssd_mid->at(i);
        plus_gtr100_mid  = rk_fit_gtr100_mid->at(i);
        plus_gtr200_mid  = rk_fit_gtr200_mid->at(i);
        plus_gtr300_mid  = rk_fit_gtr300_mid->at(i);
        plus_ssd_lpos    = geometry->SSD(ModuleID2020To2013(plus_ssd_mid))->GetLPos(TVector3(rk_hit_ssd_gx->at(i), rk_hit_ssd_gy->at(i), rk_hit_ssd_gz->at(i)));
        plus_gtr100_lpos = geometry->GTR(ModuleID2020To2013(plus_gtr100_mid), 0)->GetLPos(TVector3(rk_hit_gtr100_gtx2->at(i), rk_hit_gtr100_gty->at(i), rk_hit_gtr100_gtz2->at(i)));
        plus_gtr200_lpos = geometry->GTR(ModuleID2020To2013(plus_gtr100_mid), 1)->GetLPos(TVector3(rk_hit_gtr200_gtx2->at(i), rk_hit_gtr200_gty->at(i), rk_hit_gtr200_gtz2->at(i)));
        plus_gtr300_lpos = geometry->GTR(ModuleID2020To2013(plus_gtr100_mid), 2)->GetLPos(TVector3(rk_hit_gtr300_gtx2->at(i), rk_hit_gtr300_gty->at(i), rk_hit_gtr300_gtz2->at(i)));
        pre_fit_plus_chi2        = chi_square->at(i);
        pre_fit_plus_init_mom    = TVector3(rk_fit_init_mom_gx->at(i), rk_fit_init_mom_gy->at(i), rk_fit_init_mom_gz->at(i));
        pre_fit_plus_init_pos    = TVector3(rk_fit_init_pos_gx->at(i), rk_fit_init_pos_gy->at(i), rk_fit_init_pos_gz->at(i));
        pre_fit_plus_ssd_lpos    = TVector3(rk_fit_ssd_x->at(i),    rk_fit_ssd_y->at(i),    0.);
        pre_fit_plus_gtr100_lpos = TVector3(rk_fit_gtr100_x->at(i), rk_fit_gtr100_y->at(i), 0.);
        pre_fit_plus_gtr200_lpos = TVector3(rk_fit_gtr200_x->at(i), rk_fit_gtr200_y->at(i), 0.);
        pre_fit_plus_gtr300_lpos = TVector3(rk_fit_gtr300_x->at(i), rk_fit_gtr300_y->at(i), 0.);
      } else {
        is_sim_filled[1] = true;
        minus_ssd_mid     = rk_fit_ssd_mid->at(i);
        minus_gtr100_mid  = rk_fit_gtr100_mid->at(i);
        minus_gtr200_mid  = rk_fit_gtr200_mid->at(i);
        minus_gtr300_mid  = rk_fit_gtr300_mid->at(i);
        minus_ssd_lpos    = geometry->SSD(ModuleID2020To2013(plus_ssd_mid))->GetLPos(TVector3(rk_hit_ssd_gx->at(i), rk_hit_ssd_gy->at(i), rk_hit_ssd_gz->at(i)));
        minus_gtr100_lpos = geometry->GTR(ModuleID2020To2013(plus_gtr100_mid), 0)->GetLPos(TVector3(rk_hit_gtr100_gtx2->at(i), rk_hit_gtr100_gty->at(i), rk_hit_gtr100_gtz2->at(i)));
        minus_gtr200_lpos = geometry->GTR(ModuleID2020To2013(plus_gtr100_mid), 1)->GetLPos(TVector3(rk_hit_gtr200_gtx2->at(i), rk_hit_gtr200_gty->at(i), rk_hit_gtr200_gtz2->at(i)));
        minus_gtr300_lpos = geometry->GTR(ModuleID2020To2013(plus_gtr100_mid), 2)->GetLPos(TVector3(rk_hit_gtr300_gtx2->at(i), rk_hit_gtr300_gty->at(i), rk_hit_gtr300_gtz2->at(i)));
        pre_fit_minus_chi2        = chi_square->at(i);
        pre_fit_minus_init_mom    = TVector3(rk_fit_init_mom_gx->at(i), rk_fit_init_mom_gy->at(i), rk_fit_init_mom_gz->at(i));
        pre_fit_minus_init_pos    = TVector3(rk_fit_init_pos_gx->at(i), rk_fit_init_pos_gy->at(i), rk_fit_init_pos_gz->at(i));
        pre_fit_minus_ssd_lpos    = TVector3(rk_fit_ssd_x->at(i),    rk_fit_ssd_y->at(i),    0.);
        pre_fit_minus_gtr100_lpos = TVector3(rk_fit_gtr100_x->at(i), rk_fit_gtr100_y->at(i), 0.);
        pre_fit_minus_gtr200_lpos = TVector3(rk_fit_gtr200_x->at(i), rk_fit_gtr200_y->at(i), 0.);
        pre_fit_minus_gtr300_lpos = TVector3(rk_fit_gtr300_x->at(i), rk_fit_gtr300_y->at(i), 0.);
      }
      if (is_sim_filled[0] && is_sim_filled[1]) {
        break;
      }
    }
    for (int t = 0; t < 2; ++t) {
      sfitter.Clear();
      sfitter.SetInitialVertex(TVector3(0., 0., 0.), kVertexSigma);
      if (t == 0) {
        sfitter.SetCharge(0, 1.);
      } else {
        sfitter.SetCharge(0, -1.);
      }
      if (t == 0) {
#ifndef FROM_MOCK
        sfitter.SetInitialMomentum(0, pre_fit_plus_init_mom);
#else // FROM_MOCK
        sfitter.SetInitialMomentum(0, *mock_plus_init_mom);
#endif // FROM_MOCK
      } else {
#ifndef FROM_MOCK
        sfitter.SetInitialMomentum(0, pre_fit_minus_init_mom);
#else // FROM_MOCK
        sfitter.SetInitialMomentum(0, *mock_minus_init_mom);
#endif // FROM_MOCK
      }
      if (t == 0) {
#ifndef FROM_MOCK
        sfitter.AddHit(0, 0, geometry->SSD(ModuleID2020To2013(plus_ssd_mid)),       plus_ssd_lpos,    kSSDSigma);
        sfitter.AddHit(0, 1, geometry->GTR(ModuleID2020To2013(plus_gtr100_mid), 0), plus_gtr100_lpos, kGTR100Sigma);
        sfitter.AddHit(0, 2, geometry->GTR(ModuleID2020To2013(plus_gtr200_mid), 1), plus_gtr200_lpos, kGTR200Sigma);
        sfitter.AddHit(0, 3, geometry->GTR(ModuleID2020To2013(plus_gtr300_mid), 2), plus_gtr300_lpos, kGTR300Sigma);
//#else // FROM_MOCK
//        sfitter.AddHit(0, 0, geometry->SSD(mids0[0]),    *mock_plus_ssd_lpos,    kSSDSigma);
//        sfitter.AddHit(0, 1, geometry->GTR(mids0[1], 0), *mock_plus_gtr100_lpos, kGTR100Sigma);
//        sfitter.AddHit(0, 2, geometry->GTR(mids0[2], 1), *mock_plus_gtr200_lpos, kGTR200Sigma);
//        sfitter.AddHit(0, 3, geometry->GTR(mids0[3], 2), *mock_plus_gtr300_lpos, kGTR300Sigma);
#endif // FROM_MOCK
      } else {
#ifndef FROM_MOCK
        sfitter.AddHit(0, 0, geometry->SSD(ModuleID2020To2013(minus_ssd_mid)),       minus_ssd_lpos,    kSSDSigma);
        sfitter.AddHit(0, 1, geometry->GTR(ModuleID2020To2013(minus_gtr100_mid), 0), minus_gtr100_lpos, kGTR100Sigma);
        sfitter.AddHit(0, 2, geometry->GTR(ModuleID2020To2013(minus_gtr200_mid), 1), minus_gtr200_lpos, kGTR200Sigma);
        sfitter.AddHit(0, 3, geometry->GTR(ModuleID2020To2013(minus_gtr300_mid), 2), minus_gtr300_lpos, kGTR300Sigma);
//#else // FROM_MOCK
//        sfitter.AddHit(0, 0, geometry->SSD(mids1[0]),    *mock_minus_ssd_lpos,    kSSDSigma);
//        sfitter.AddHit(0, 1, geometry->GTR(mids1[1], 0), *mock_minus_gtr100_lpos, kGTR100Sigma);
//        sfitter.AddHit(0, 2, geometry->GTR(mids1[2], 1), *mock_minus_gtr200_lpos, kGTR200Sigma);
//        sfitter.AddHit(0, 3, geometry->GTR(mids1[3], 2), *mock_minus_gtr300_lpos, kGTR300Sigma);
#endif // FROM_MOCK
      }
      sfitter.SetRungeKuttaStepSize(kStepSize);
      sfitter.SetMaxSteps(kMaxSteps);
      auto tmp_chi2     = sfitter.Fit(kFixVtxXY, kFixPy, kFixVtxZ, kStrategy, kMaxFuncCalls, kVtxXRange[0], kVtxXRange[1], kVtxYRange[0], kVtxYRange[1], kVtxZRange[0], kVtxZRange[1]);
      auto tmp_mom      = sfitter.GetFitMomentum(0);
      auto tmp_init_pos = sfitter.GetFitVertex();
      array<TVector3, 4> tmp_lposs;
      for (int l = 0; l < 4; ++l) {
        vector<int> tmp_mid;
        vector<TVector3> tmp_lpos;
        sfitter.GetFitLPos(0, l, tmp_mid, tmp_lpos);
        tmp_lposs[l] = tmp_lpos[0];
      }
      if (t == 0) {
        fit_plus_chi2        = tmp_chi2;
        fit_plus_init_mom    = tmp_mom;
        fit_plus_init_pos    = tmp_init_pos;
        fit_plus_ssd_lpos    = tmp_lposs[0];
        fit_plus_gtr100_lpos = tmp_lposs[1];
        fit_plus_gtr200_lpos = tmp_lposs[2];
        fit_plus_gtr300_lpos = tmp_lposs[3];
      } else {
        fit_minus_chi2        = tmp_chi2;
        fit_minus_init_mom    = tmp_mom;
        fit_minus_init_pos    = tmp_init_pos;
        fit_minus_ssd_lpos    = tmp_lposs[0];
        fit_minus_gtr100_lpos = tmp_lposs[1];
        fit_minus_gtr200_lpos = tmp_lposs[2];
        fit_minus_gtr300_lpos = tmp_lposs[3];
      }
    }
    pre_fit_mass = CalcMass(pre_fit_plus_init_mom, pre_fit_minus_init_mom);
    fit_mass     = CalcMass(fit_plus_init_mom,     fit_minus_init_mom);
    out_tree.Fill();
  }
  out_file.Write();
}
