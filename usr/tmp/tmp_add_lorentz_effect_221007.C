#define tmp_add_lorentz_effect_221007_cxx
#include "tmp_add_lorentz_effect_221007.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

bool tmp_add_lorentz_effect_221007::IsGoodPair(int n) {



}

void tmp_add_lorentz_effect_221007::Fit(int n) {


  return;
}

void tmp_add_lorentz_effect_221007::PairFit(int n) {
  pair_fitter->Clear();
  pair_fitter->SetInitialVertex(kInitVertex, kVertexSigma);
  for (int tid = 0; tid < 2; ++tid) {
    auto i = good_pair_indexs[n][tid];
    if (!kForgiveSameCharge) {
      if (tid == 0) {
        pair_fitter->SetCharge(tid, 1.);
      } else {
        pair_fitter->SetCharge(tid, -1.);
      }
    } else {
      pair_fitter->SetCharge(tid, ChargeID(rk_charge->at(i)));
    }
    pair_fitter->SetInitialMomentum(tid, TVector3(rk_fit_init_mom_gx->at(i), rk_fit_init_mom_gy->at(i), rk_fit_init_mom_gz->at(i)));
    pair_fitter->AddHit(tid, 0, geometry->SSD(ModuleID2013(rk_fit_ssd_mid->at(i))),       TVector3(rk_hit_ssd_x->at(i),      0.,                      0.), kSSDSigma);
    pair_fitter->AddHit(tid, 1, geometry->GTR(ModuleID2013(rk_fit_gtr100_mid->at(i)), 0), TVector3(rk_hit_gtr100_tx2->at(i), rk_hit_gtr100_ty->at(i), 0.), kGTR100Sigma);
    pair_fitter->AddHit(tid, 2, geometry->GTR(ModuleID2013(rk_fit_gtr200_mid->at(i)), 1), TVector3(rk_hit_gtr200_tx2->at(i), rk_hit_gtr200_ty->at(i), 0.), kGTR200Sigma);
    pair_fitter->AddHit(tid, 3, geometry->GTR(ModuleID2013(rk_fit_gtr300_mid->at(i)), 2), TVector3(rk_hit_gtr300_tx2->at(i), rk_hit_gtr300_ty->at(i), 0.), kGTR300Sigma);
  }
  pair_fitter->SetRungeKuttaStepSize(kStepSize);
  pair_fitter->SetMaxSteps(kMaxSteps);
  auto chi2 = pair_fitter->Fit(kFixVtxXY, kFixPy, kFixVtxZ, kStrategy, kMaxFuncCalls,
                          kVtxXRange[0], kVtxXRange[1], kVtxYRange[0], kVtxYRange[1], kVtxZRange[0], kVtxZRange[1]);
  FillBranchesFromPairFit(n, chi2);
  return;
}

void tmp_add_lorentz_effect_221007::Loop(const TString& out_name) {
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;

  auto file = TFile(out_name, "recreate");
  auto tree = TTree("tree", "tree");

  for (Long64_t jentry = 0; jentry < nentries; ++jentry) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
    for (int i = 0; i < n_pairs; ++i) {
      if (!IsGoodPair(i)) {
        continue;
      }
      SignleFit(i);
      PairFit(i);
    }
    tree.Fill();
  }
  file.Write();
  return;
}
