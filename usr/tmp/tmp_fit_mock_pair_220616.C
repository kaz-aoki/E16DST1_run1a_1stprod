//#define FROM_MOCK

#define tmp_fit_mock_pair_220616_cxx
#include "tmp_fit_mock_pair_220616.h"

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

array<int, 4> tmp_fit_mock_pair_220616::ModuleIDs2020To2013(int cid) {
  array<int, 4> mids;
  if (cid == 0) {
    mids[0] = ModuleID2020To2013(plus_ssd_mid);
    mids[1] = ModuleID2020To2013(plus_gtr100_mid);
    mids[2] = ModuleID2020To2013(plus_gtr200_mid);
    mids[3] = ModuleID2020To2013(plus_gtr300_mid);
  } else {
    mids[0] = ModuleID2020To2013(minus_ssd_mid);
    mids[1] = ModuleID2020To2013(minus_gtr100_mid);
    mids[2] = ModuleID2020To2013(minus_gtr200_mid);
    mids[3] = ModuleID2020To2013(minus_gtr300_mid);
  }
  return mids;
}

double tmp_fit_mock_pair_220616::CalcMass(const TVector3& mom0, const TVector3& mom1) {
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

void tmp_fit_mock_pair_220616::Loop(int max_events, const TString& out_name) {
//   In a ROOT session, you can do:
//      root> .L tmp_fit_mock_pair_220616.C
//      root> tmp_fit_mock_pair_220616 t
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
//  TVector3 plus_ssd_lpos;
//  TVector3 plus_gtr100_lpos;
//  TVector3 plus_gtr200_lpos;
//  TVector3 plus_gtr300_lpos;
//  TVector3 minus_ssd_lpos;
//  TVector3 minus_gtr100_lpos;
//  TVector3 minus_gtr200_lpos;
//  TVector3 minus_gtr300_lpos;
  // pre fit
  double pre_mass;
  // pair fit
  double mass;
  double chi2;
  TVector3 vtx;
  TVector3 plus_mom;
  TVector3 plus_ssd_res;
  TVector3 plus_gtr100_res;
  TVector3 plus_gtr200_res;
  TVector3 plus_gtr300_res;
  TVector3 minus_mom;
  TVector3 minus_ssd_res;
  TVector3 minus_gtr100_res;
  TVector3 minus_gtr200_res;
  TVector3 minus_gtr300_res;
  // single fit
  double   smass;
  double   splus_chi2;
  TVector3 splus_mom;
  TVector3 splus_init_gpos;
  TVector3 splus_ssd_lpos;
  TVector3 splus_gtr100_lpos;
  TVector3 splus_gtr200_lpos;
  TVector3 splus_gtr300_lpos;
  double   sminus_chi2;
  TVector3 sminus_mom;
  TVector3 sminus_init_gpos;
  TVector3 sminus_ssd_lpos;
  TVector3 sminus_gtr100_lpos;
  TVector3 sminus_gtr200_lpos;
  TVector3 sminus_gtr300_lpos;
  // common
  out_tree.Branch("run_id",                 &run_id,          "run_id/I");
  out_tree.Branch("event_id",               &event_id,        "event_id/I");
  out_tree.Branch("plus_ssd_mid",           &plus_ssd_mid,    "plus_ssd_mid/I");
  out_tree.Branch("plus_ssd_gpos",          &plus_ssd_gpos);
  out_tree.Branch("plus_gtr100_mid",        &plus_gtr100_mid, "plus_gtr100_mid/I");
  out_tree.Branch("plus_gtr100_gpos",       &plus_gtr100_gpos);
  out_tree.Branch("plus_gtr200_mid",        &plus_gtr200_mid, "plus_gtr200_mid/I");
  out_tree.Branch("plus_gtr200_gpos",       &plus_gtr200_gpos);
  out_tree.Branch("plus_gtr300_mid",        &plus_gtr300_mid, "plus_gtr300_mid/I");
  out_tree.Branch("plus_gtr300_gpos",       &plus_gtr300_gpos);
  out_tree.Branch("minus_ssd_mid",          &minus_ssd_mid,    "minus_ssd_mid/I");
  out_tree.Branch("minus_ssd_gpos",         &minus_ssd_gpos);
  out_tree.Branch("minus_gtr100_mid",       &minus_gtr100_mid, "minus_gtr100_mid/I");
  out_tree.Branch("minus_gtr100_gpos",      &minus_gtr100_gpos);
  out_tree.Branch("minus_gtr200_mid",       &minus_gtr200_mid, "minus_gtr200_mid/I");
  out_tree.Branch("minus_gtr200_gpos",      &minus_gtr200_gpos);
  out_tree.Branch("minus_gtr300_mid",       &minus_gtr300_mid, "minus_gtr300_mid/I");
  out_tree.Branch("minus_gtr300_gpos",      &minus_gtr300_gpos);
//  out_tree.Branch("plus_ssd_lpos",          &plus_ssd_lpos);
//  out_tree.Branch("plus_gtr100_lpos",       &plus_gtr100_lpos);
//  out_tree.Branch("plus_gtr200_lpos",       &plus_gtr200_lpos);
//  out_tree.Branch("plus_gtr300_lpos",       &plus_gtr300_lpos);
//  out_tree.Branch("minus_ssd_lpos",         &minus_ssd_lpos);
//  out_tree.Branch("minus_gtr100_lpos",      &minus_gtr100_lpos);
//  out_tree.Branch("minus_gtr200_lpos",      &minus_gtr200_lpos);
//  out_tree.Branch("minus_gtr300_lpos",      &minus_gtr300_lpos);
//  out_tree.Branch("mock_plus_ssd_lpos",     &mock_plus_ssd_lpos);
//  out_tree.Branch("mock_plus_gtr100_lpos",  &mock_plus_gtr100_lpos);
//  out_tree.Branch("mock_plus_gtr200_lpos",  &mock_plus_gtr200_lpos);
//  out_tree.Branch("mock_plus_gtr300_lpos",  &mock_plus_gtr300_lpos);
//  out_tree.Branch("mock_minus_ssd_lpos",    &mock_minus_ssd_lpos);
//  out_tree.Branch("mock_minus_gtr100_lpos", &mock_minus_gtr100_lpos);
//  out_tree.Branch("mock_minus_gtr200_lpos", &mock_minus_gtr200_lpos);
//  out_tree.Branch("mock_minus_gtr300_lpos", &mock_minus_gtr300_lpos);
  // pre fit
  out_tree.Branch("pre_mass",               &pre_mass, "pre_mass/D");
  out_tree.Branch("pre_plus_chi2",          &plus_chi2, "pre_plus_chi2/D");
  out_tree.Branch("pre_plus_mom",           &plus_init_mom);
  out_tree.Branch("pre_plus_init_gpos",     &plus_init_gpos);
  out_tree.Branch("pre_plus_ssd_gpos",      &plus_ssd_fit_gpos);
  out_tree.Branch("pre_plus_gtr100_gpos",   &plus_gtr100_fit_gpos);
  out_tree.Branch("pre_plus_gtr200_gpos",   &plus_gtr200_fit_gpos);
  out_tree.Branch("pre_plus_gtr300_gpos",   &plus_gtr300_fit_gpos);
  out_tree.Branch("pre_minus_chi2",         &minus_chi2, "pre_minus_chi2/D");
  out_tree.Branch("pre_minus_mom",          &minus_init_mom);
  out_tree.Branch("pre_minus_init_gpos",    &minus_init_gpos);
  out_tree.Branch("pre_minus_ssd_gpos",     &minus_ssd_fit_gpos);
  out_tree.Branch("pre_minus_gtr100_gpos",  &minus_gtr100_fit_gpos);
  out_tree.Branch("pre_minus_gtr200_gpos",  &minus_gtr200_fit_gpos);
  out_tree.Branch("pre_minus_gtr300_gpos",  &minus_gtr300_fit_gpos);
  // pair fit
  out_tree.Branch("mass",             &mass, "mass/D");
  out_tree.Branch("chi2",             &chi2, "chi2/D");
  out_tree.Branch("vtx",              &vtx);
  out_tree.Branch("plus_mom",         &plus_mom);
  out_tree.Branch("plus_ssd_res",     &plus_ssd_res);
  out_tree.Branch("plus_gtr100_res",  &plus_gtr100_res);
  out_tree.Branch("plus_gtr200_res",  &plus_gtr200_res);
  out_tree.Branch("plus_gtr300_res",  &plus_gtr300_res);
  out_tree.Branch("minus_mom",        &minus_mom);
  out_tree.Branch("minus_ssd_res",    &minus_ssd_res);
  out_tree.Branch("minus_gtr100_res", &minus_gtr100_res);
  out_tree.Branch("minus_gtr200_res", &minus_gtr200_res);
  out_tree.Branch("minus_gtr300_res", &minus_gtr300_res);
  // single fit
  out_tree.Branch("smass",              &smass,       "smass/D");
  out_tree.Branch("splus_chi2",         &splus_chi2,  "splus_chi2/D");
  out_tree.Branch("splus_mom",          &splus_mom);
  out_tree.Branch("splus_init_gpos",    &splus_init_gpos);
  out_tree.Branch("splus_ssd_lpos",     &splus_ssd_lpos);
  out_tree.Branch("splus_gtr100_lpos",  &splus_gtr100_lpos);
  out_tree.Branch("splus_gtr200_lpos",  &splus_gtr200_lpos);
  out_tree.Branch("splus_gtr300_lpos",  &splus_gtr300_lpos);
  out_tree.Branch("sminus_chi2",        &sminus_chi2, "sminus_chi2/D");
  out_tree.Branch("sminus_mom",         &sminus_mom);
  out_tree.Branch("sminus_init_gpos",   &sminus_init_gpos);
  out_tree.Branch("sminus_ssd_lpos",    &sminus_ssd_lpos);
  out_tree.Branch("sminus_gtr100_lpos", &sminus_gtr100_lpos);
  out_tree.Branch("sminus_gtr200_lpos", &sminus_gtr200_lpos);
  out_tree.Branch("sminus_gtr300_lpos", &sminus_gtr300_lpos);

  if (max_events == -1) {
    max_events = nentries;
  }
//  for (Long64_t jentry = 0; jentry < nentries; ++jentry) {
  for (Long64_t jentry = 0; jentry < max_events; ++jentry) {
    if (jentry % 10 == 0) {
      cout << jentry << " / " << nentries << endl;
    }
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
//    if (Cut(ientry) < 0) continue;
    // pre fit
    pre_mass = CalcMass(*plus_init_mom, *minus_init_mom);
    // pair fit
    fitter.Clear();
    fitter.SetInitialVertex(kInitVertex, kVertexSigma);
    fitter.SetCharge(0, 1.);
#ifndef FROM_MOCK
    fitter.SetInitialMomentum(0, *plus_init_mom);
#else // FROM_MOCK
    fitter.SetInitialMomentum(0, *mock_plus_init_mom);
#endif // FROM_MOCK
    auto mids0 = ModuleIDs2020To2013(0);
#ifndef FROM_MOCK
    fitter.AddHit(0, 0, geometry->SSD(mids0[0]),    geometry->SSD(mids0[0])->GetLPos(*plus_ssd_gpos),       kSSDSigma);
    fitter.AddHit(0, 1, geometry->GTR(mids0[1], 0), geometry->GTR(mids0[1], 0)->GetLPos(*plus_gtr100_gpos), kGTR100Sigma);
    fitter.AddHit(0, 2, geometry->GTR(mids0[2], 1), geometry->GTR(mids0[2], 1)->GetLPos(*plus_gtr100_gpos), kGTR200Sigma);
    fitter.AddHit(0, 3, geometry->GTR(mids0[3], 2), geometry->GTR(mids0[3], 2)->GetLPos(*plus_gtr100_gpos), kGTR300Sigma);
//    fitter.AddHit(0, 0, geometry->SSD(mids0[0]),    geometry->SSD(mids0[0])->GetLPos(*plus_ssd_fit_gpos),       kSSDSigma);
//    fitter.AddHit(0, 1, geometry->GTR(mids0[1], 0), geometry->GTR(mids0[1], 0)->GetLPos(*plus_gtr100_fit_gpos), kGTR100Sigma);
//    fitter.AddHit(0, 2, geometry->GTR(mids0[2], 1), geometry->GTR(mids0[2], 1)->GetLPos(*plus_gtr100_fit_gpos), kGTR200Sigma);
//    fitter.AddHit(0, 3, geometry->GTR(mids0[3], 2), geometry->GTR(mids0[3], 2)->GetLPos(*plus_gtr100_fit_gpos), kGTR300Sigma);
#else // FROM_MOCK
    fitter.AddHit(0, 0, geometry->SSD(mids0[0]),    *mock_plus_ssd_lpos,    kSSDSigma);
    fitter.AddHit(0, 1, geometry->GTR(mids0[1], 0), *mock_plus_gtr100_lpos, kGTR100Sigma);
    fitter.AddHit(0, 2, geometry->GTR(mids0[2], 1), *mock_plus_gtr200_lpos, kGTR200Sigma);
    fitter.AddHit(0, 3, geometry->GTR(mids0[3], 2), *mock_plus_gtr300_lpos, kGTR300Sigma);
#endif // FROM_MOCK
    fitter.SetCharge(1, -1.);
#ifndef FROM_MOCK
    fitter.SetInitialMomentum(1, *minus_init_mom);
#else // FROM_MOCK
    fitter.SetInitialMomentum(1, *mock_minus_init_mom);
#endif // FROM_MOCK
    auto mids1 = ModuleIDs2020To2013(1);
#ifndef FROM_MOCK
    fitter.AddHit(1, 0, geometry->SSD(mids1[0]),    geometry->SSD(mids1[0])->GetLPos(*minus_ssd_gpos),       kSSDSigma);
    fitter.AddHit(1, 1, geometry->GTR(mids1[1], 0), geometry->GTR(mids1[1], 0)->GetLPos(*minus_gtr100_gpos), kGTR100Sigma);
    fitter.AddHit(1, 2, geometry->GTR(mids1[2], 1), geometry->GTR(mids1[2], 1)->GetLPos(*minus_gtr100_gpos), kGTR200Sigma);
    fitter.AddHit(1, 3, geometry->GTR(mids1[3], 2), geometry->GTR(mids1[3], 2)->GetLPos(*minus_gtr100_gpos), kGTR300Sigma);
//    fitter.AddHit(1, 0, geometry->SSD(mids1[0]),    geometry->SSD(mids1[0])->GetLPos(*minus_ssd_fit_gpos),       kSSDSigma);
//    fitter.AddHit(1, 1, geometry->GTR(mids1[1], 0), geometry->GTR(mids1[1], 0)->GetLPos(*minus_gtr100_fit_gpos), kGTR100Sigma);
//    fitter.AddHit(1, 2, geometry->GTR(mids1[2], 1), geometry->GTR(mids1[2], 1)->GetLPos(*minus_gtr100_fit_gpos), kGTR200Sigma);
//    fitter.AddHit(1, 3, geometry->GTR(mids1[3], 2), geometry->GTR(mids1[3], 2)->GetLPos(*minus_gtr100_fit_gpos), kGTR300Sigma);
#else // FROM_MOCK
    fitter.AddHit(1, 0, geometry->SSD(mids1[0]),    *mock_minus_ssd_lpos,    kSSDSigma);
    fitter.AddHit(1, 1, geometry->GTR(mids1[1], 0), *mock_minus_gtr100_lpos, kGTR100Sigma);
    fitter.AddHit(1, 2, geometry->GTR(mids1[2], 1), *mock_minus_gtr200_lpos, kGTR200Sigma);
    fitter.AddHit(1, 3, geometry->GTR(mids1[3], 2), *mock_minus_gtr300_lpos, kGTR300Sigma);
#endif // FROM_MOCK
    fitter.SetRungeKuttaStepSize(kStepSize);
    fitter.SetMaxSteps(kMaxSteps);
    chi2 = fitter.Fit(kFixVtxXY, kFixPy, kFixVtxZ, kStrategy, kMaxFuncCalls, kVtxXRange[0], kVtxXRange[1], kVtxYRange[0], kVtxYRange[1], kVtxZRange[0], kVtxZRange[1]);
    vtx       = fitter.GetFitVertex();
    plus_mom  = fitter.GetFitMomentum(0);
    minus_mom = fitter.GetFitMomentum(1);
    mass      = CalcMass(plus_mom, minus_mom);
    for (int t = 0; t < 2; ++t) {
      for (int l = 0; l < 4; ++l) {
        vector<int>      mids;
        vector<TVector3> ress;
        fitter.GetFitResidual(t, l, mids, ress);
        if (t == 0) {
          if (l == 0) {
            plus_ssd_res = ress[0];
          } else if (l == 1) {
            plus_gtr100_res = ress[0];
          } else if (l == 2) {
            plus_gtr200_res = ress[0];
          } else {
            plus_gtr300_res = ress[0];
          }
        } else {
          if (l == 0) {
            minus_ssd_res = ress[0];
          } else if (l == 1) {
            minus_gtr100_res = ress[0];
          } else if (l == 2) {
            minus_gtr200_res = ress[0];
          } else {
            minus_gtr300_res = ress[0];
          }
        }
      }
    }
//cout << "minimize status " << fitter.GetMinimizeStatus() << endl;
//cout << "matrix status " << matrix_stat = fitter.GetMatrixStatus() << endl;
//cout << "num calls " << fitter.GetNumCalls() << endl;
    // single fit
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
        sfitter.SetInitialMomentum(0, *plus_init_mom);
#else // FROM_MOCK
        sfitter.SetInitialMomentum(0, *mock_plus_init_mom);
#endif // FROM_MOCK
      } else {
#ifndef FROM_MOCK
        sfitter.SetInitialMomentum(0, *minus_init_mom);
#else // FROM_MOCK
        sfitter.SetInitialMomentum(0, *mock_minus_init_mom);
#endif // FROM_MOCK
      }
      if (t == 0) {
#ifndef FROM_MOCK
        sfitter.AddHit(0, 0, geometry->SSD(mids0[0]),    geometry->SSD(mids0[0])->GetLPos(*plus_ssd_gpos),       kSSDSigma);
        sfitter.AddHit(0, 1, geometry->GTR(mids0[1], 0), geometry->GTR(mids0[1], 0)->GetLPos(*plus_gtr100_gpos), kGTR100Sigma);
        sfitter.AddHit(0, 2, geometry->GTR(mids0[2], 1), geometry->GTR(mids0[2], 1)->GetLPos(*plus_gtr100_gpos), kGTR200Sigma);
        sfitter.AddHit(0, 3, geometry->GTR(mids0[3], 2), geometry->GTR(mids0[3], 2)->GetLPos(*plus_gtr100_gpos), kGTR300Sigma);
#else // FROM_MOCK
        sfitter.AddHit(0, 0, geometry->SSD(mids0[0]),    *mock_plus_ssd_lpos,    kSSDSigma);
        sfitter.AddHit(0, 1, geometry->GTR(mids0[1], 0), *mock_plus_gtr100_lpos, kGTR100Sigma);
        sfitter.AddHit(0, 2, geometry->GTR(mids0[2], 1), *mock_plus_gtr200_lpos, kGTR200Sigma);
        sfitter.AddHit(0, 3, geometry->GTR(mids0[3], 2), *mock_plus_gtr300_lpos, kGTR300Sigma);
#endif // FROM_MOCK
      } else {
#ifndef FROM_MOCK
        sfitter.AddHit(0, 0, geometry->SSD(mids1[0]),    geometry->SSD(mids1[0])->GetLPos(*minus_ssd_gpos),       kSSDSigma);
        sfitter.AddHit(0, 1, geometry->GTR(mids1[1], 0), geometry->GTR(mids1[1], 0)->GetLPos(*minus_gtr100_gpos), kGTR100Sigma);
        sfitter.AddHit(0, 2, geometry->GTR(mids1[2], 1), geometry->GTR(mids1[2], 1)->GetLPos(*minus_gtr100_gpos), kGTR200Sigma);
        sfitter.AddHit(0, 3, geometry->GTR(mids1[3], 2), geometry->GTR(mids1[3], 2)->GetLPos(*minus_gtr100_gpos), kGTR300Sigma);
#else // FROM_MOCK
        sfitter.AddHit(0, 0, geometry->SSD(mids1[0]),    *mock_minus_ssd_lpos,    kSSDSigma);
        sfitter.AddHit(0, 1, geometry->GTR(mids1[1], 0), *mock_minus_gtr100_lpos, kGTR100Sigma);
        sfitter.AddHit(0, 2, geometry->GTR(mids1[2], 1), *mock_minus_gtr200_lpos, kGTR200Sigma);
        sfitter.AddHit(0, 3, geometry->GTR(mids1[3], 2), *mock_minus_gtr300_lpos, kGTR300Sigma);
#endif // FROM_MOCK
      }
      sfitter.SetRungeKuttaStepSize(kStepSize);
      sfitter.SetMaxSteps(kMaxSteps);
      auto tmp_chi2      = sfitter.Fit(kFixVtxXY, kFixPy, kFixVtxZ, kStrategy, kMaxFuncCalls,
                                       kVtxXRange[0], kVtxXRange[1], kVtxYRange[0], kVtxYRange[1], kVtxZRange[0], kVtxZRange[1]);
      auto tmp_mom       = sfitter.GetFitMomentum(0);
      auto tmp_init_gpos = sfitter.GetFitVertex();
      array<TVector3, 4> tmp_lposs;
      for (int l = 0; l < 4; ++l) {
        vector<int> tmp_mid;
        vector<TVector3> tmp_lpos;
        sfitter.GetFitLPos(0, l, tmp_mid, tmp_lpos);
        tmp_lposs[l] = tmp_lpos[0];
      }
      if (t == 0) {
        splus_chi2        = tmp_chi2;
        splus_mom         = tmp_mom;
        splus_init_gpos   = tmp_init_gpos;
        splus_ssd_lpos    = tmp_lposs[0];
        splus_gtr100_lpos = tmp_lposs[1];
        splus_gtr200_lpos = tmp_lposs[2];
        splus_gtr300_lpos = tmp_lposs[3];
      } else {
        sminus_chi2        = tmp_chi2;
        sminus_mom         = tmp_mom;
        sminus_init_gpos   = tmp_init_gpos;
        sminus_ssd_lpos    = tmp_lposs[0];
        sminus_gtr100_lpos = tmp_lposs[1];
        sminus_gtr200_lpos = tmp_lposs[2];
        sminus_gtr300_lpos = tmp_lposs[3];
      }
    }
    smass = CalcMass(splus_mom, sminus_mom);
    out_tree.Fill();
  }
  out_file.Write();
  delete geometry;
  delete bfield_map;
  return;
}
