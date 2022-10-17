#define tmp_add_lorentz_effect_221007_cxx
#include "tmp_add_lorentz_effect_221007.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

bool tmp_add_lorentz_effect_221007::IsGoodPair(int n) {



}

void tmp_add_lorentz_effect_221007::AddTrack(int n, int tid, double charge, E16ANA_MultiTrack* fitter) {
  fitter->SetCharge(tid, charge);
  if (charge == 1.) {
    fitter->SetInitialMomentum(tid, TVector3(plus_mom_x->at(n), plus_mom_y->at(n), plus_mom_z->at(n)));
    fitter->AddHit(tid, 0, geometry->SSD(ModuleID2013(plus_ssd_mid->at(n))), TVector3(hit_plus_ssd_lx->at(n), 0., 0.), kSSDSigma);
    fitter->AddHit(tid, 1, geometry->GTR(ModuleID2013(plus_gtr100_mid->at(n)), 0),
                   TVector3(hit_plus_gtr100_lx->at(n) + GTRLorentzCorr[0], hit_plus_gtr100_ly->at(n), 0.), kGTR100Sigma);
    fitter->AddHit(tid, 2, geometry->GTR(ModuleID2013(plus_gtr200_mid->at(n)), 0),
                   TVector3(hit_plus_gtr200_lx->at(n) + GTRLorentzCorr[1], hit_plus_gtr200_ly->at(n), 0.), kGTR200Sigma);
    fitter->AddHit(tid, 3, geometry->GTR(ModuleID2013(plus_gtr300_mid->at(n)), 0),
                   TVector3(hit_plus_gtr300_lx->at(n) + GTRLorentzCorr[2], hit_plus_gtr300_ly->at(n), 0.), kGTR300Sigma);
  } else {
    fitter->SetInitialMomentum(tid, TVector3(minus_mom_x->at(n), minus_mom_y->at(n), minus_mom_z->at(n)));
    fitter->AddHit(tid, 0, geometry->SSD(ModuleID2013(minus_ssd_mid->at(n))), TVector3(hit_minus_ssd_lx->at(n), 0., 0.), kSSDSigma);
    fitter->AddHit(tid, 1, geometry->GTR(ModuleID2013(minus_gtr100_mid->at(n)), 0),
                   TVector3(hit_minus_gtr100_lx->at(n) + GTRLorentzCorr[0], hit_minus_gtr100_ly->at(n), 0.), kGTR100Sigma);
    fitter->AddHit(tid, 2, geometry->GTR(ModuleID2013(minus_gtr200_mid->at(n)), 0),
                   TVector3(hit_minus_gtr200_lx->at(n) + GTRLorentzCorr[1], hit_minus_gtr200_ly->at(n), 0.), kGTR200Sigma);
    fitter->AddHit(tid, 3, geometry->GTR(ModuleID2013(minus_gtr300_mid->at(n)), 0),
                   TVector3(hit_minus_gtr300_lx->at(n) + GTRLorentzCorr[2], hit_minus_gtr300_ly->at(n), 0.), kGTR300Sigma);
  }
  return;
}

void tmp_add_lorentz_effect_221007::SingleFit(int n) {
  fitter->Clear();
/  fitter->SetInitialVertex(TVector3(vtx_x->at(n), vtx_y->at(n), vtx_z->at(n)), kVertexSigma);
/  AddTrack(n, 0,  1., fitter);
  fitter->SetRungeKuttaStepSize(kStepSize);
  fitter->SetMaxSteps(kMaxSteps);
  auto chi2 = fitter->Fit(kFixVtxXY, kFixPy, kFixVtxZ, kStrategy, kMaxFuncCalls,
                          kVtxXRange[0], kVtxXRange[1], kVtxYRange[0], kVtxYRange[1], kVtxZRange[0], kVtxZRange[1]);
//  FillBranchesFromPairFit(n, chi2);
  return;
}

void tmp_add_lorentz_effect_221007::PairFit(int n) {
  pair_fitter->Clear();
  pair_fitter->SetInitialVertex(TVector3(vtx_x->at(n), vtx_y->at(n), vtx_z->at(n)), kVertexSigma);
  AddTrack(n, 0,  1., pair_fitter);
  AddTrack(n, 1, -1., pair_fitter);
  pair_fitter->SetRungeKuttaStepSize(kStepSize);
  pair_fitter->SetMaxSteps(kMaxSteps);
  auto chi2 = pair_fitter->Fit(kFixVtxXY, kFixPy, kFixVtxZ, kStrategy, kMaxFuncCalls,
                               kVtxXRange[0], kVtxXRange[1], kVtxYRange[0], kVtxYRange[1], kVtxZRange[0], kVtxZRange[1]);
//  FillBranchesFromPairFit(n, chi2);
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
