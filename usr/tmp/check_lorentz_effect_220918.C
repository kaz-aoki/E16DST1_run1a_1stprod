#define check_lorentz_effect_220918_cxx
#include "check_lorentz_effect_220918.h"

#include <iostream>

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "check_lorentz_effect_220918_parameter.hh"

using namespace std;
using namespace check_lorentz_effect_220918_parameter;

void check_lorentz_effect_220918::Set(E16ANA_GeometryV2* _geometry, E16ANA_MagneticFieldMap* _bfield_map, E16ANA_MultiTrack* _fitter) {
  geometry = _geometry;
  bfield_map = _bfield_map;
  fitter = _fitter;
  return;
}

void check_lorentz_effect_220918::Clear() {
  lorentz_id0.clear();
  lorentz_param0.clear();
  lorentz_id1.clear();
  lorentz_param1.clear();
  lorentz_id2.clear();
  lorentz_param2.clear();
  chi2_wo_tgt.clear();
  tgt_x.clear();
  tgt_y.clear();
  tgt_z.clear();
  chi2_wo_ssd.clear();
  ssd_xres.clear();
  lorentz_id0.resize(kNumDivides3);
  lorentz_param0.resize(kNumDivides3);
  lorentz_id1.resize(kNumDivides3);
  lorentz_param1.resize(kNumDivides3);
  lorentz_id2.resize(kNumDivides3);
  lorentz_param2.resize(kNumDivides3);
  chi2_wo_tgt.resize(kNumDivides3);
  tgt_x.resize(kNumDivides3);
  tgt_y.resize(kNumDivides3);
  tgt_z.resize(kNumDivides3);
  chi2_wo_ssd.resize(kNumDivides3);
  ssd_xres.resize(kNumDivides3);
  return;
}

bool check_lorentz_effect_220918::IsGoodTrack(int n) {
  if (rk_proj_x0_mom_gy->at(n) == 0.) {
    return false;
  }
//// plus only
//  if (rk_charge->at(n) != 1) {
//    return false;
//  }
// 106 only
  if (rk_fit_ssd_mid->at(n) != 106) {
    return false;
  }
  if (rk_fit_gtr100_mid->at(n) != 106) {
    return false;
  }
  if (rk_fit_gtr200_mid->at(n) != 106) {
    return false;
  }
  if (rk_fit_gtr300_mid->at(n) != 106) {
    return false;
  }
//// 104 or 106
//  bool is_selected_module = false;
//  if (rk_fit_ssd_mid->at(n) == 104) {
//    if (rk_fit_gtr100_mid->at(n) == 104) {
//      if (rk_fit_gtr200_mid->at(n) == 104) {
//        if (rk_fit_gtr300_mid->at(n) == 104) {
//          is_selected_module = true;
//        }
//      }
//    }
//  } else if (rk_fit_ssd_mid->at(n) == 106) {
//    if (rk_fit_gtr100_mid->at(n) == 106) {
//      if (rk_fit_gtr200_mid->at(n) == 106) {
//        if (rk_fit_gtr300_mid->at(n) == 106) {
//          is_selected_module = true;
//        }
//      }
//    }
//  }
//  if (!is_selected_module) {
//    return false;
//  }
//
  bool has_hbd = false;
  auto ref = TVector3(rk_fit_hbd_x->at(n), rk_fit_hbd_y->at(n), 0.);
  for (int i = 0; i < rk_proj_n_hbd->at(n); ++i) {
    if ((kHBDForward && rk_proj_hbd_cprob->at(n)[i] < 0.5) || (!kHBDForward && rk_proj_hbd_eprob->at(n)[i] < 0.5)) {
      continue;
    }
    if (fabs(rk_proj_hbd_x->at(n)[i] - ref.X()) > kMaxHBDXResidual) {
      continue;
    }
    if (fabs(rk_proj_hbd_y->at(n)[i] - ref.Y()) > kMaxHBDYResidual) {
      continue;
    }
    has_hbd = true;
    break;
  }
  if (!has_hbd) {
    return false;
  }
  return true;
}

int check_lorentz_effect_220918::ChargeID(int n) {
  auto c = rk_charge->at(n);
  if (c == 1) {
    return kChargePlus;
  }
  return kChargeMinus;
}

int check_lorentz_effect_220918::TargetID(int n) {
  auto cid = ChargeID(n);
  auto z = rk_proj_x0_gz->at(n);
  for (int i = 0; i < kNumTargets; ++i) {
    if (z > kTargetZRange[cid][i][0] && z < kTargetZRange[cid][i][1]) {
      return i;
    }
  }
  return kNumTargets;
}

void check_lorentz_effect_220918::FillPreValues(int n, int tid) {
  out_track_id = track_id->at(n);
  tgt_id = tid;
  module_id = rk_fit_gtr300_mid->at(n);
  charge = rk_charge->at(n);
  pre_chi2 = chi_square->at(n);
  pre_x0_y = rk_proj_x0_gy->at(n);
  pre_x0_z = rk_proj_x0_gz->at(n);
  return;
}

int check_lorentz_effect_220918::ModuleID2020To2013(int m) {
  return kModuleID2020To2013[m - 100];
}

double check_lorentz_effect_220918::FitWoTarget(int n, double lparam0, double lparam1, double lparam2) {
  constexpr int track_id = 0;
  auto init_pos = TVector3(0., 0., rk_proj_x0_gz->at(n));
  auto init_mom = TVector3(rk_proj_x0_mom_gx->at(n), rk_proj_x0_mom_gy->at(n), rk_proj_x0_mom_gz->at(n));
  array<int, 4> mids = {ModuleID2020To2013(rk_fit_ssd_mid->at(n)),
                        ModuleID2020To2013(rk_fit_gtr100_mid->at(n)),
                        ModuleID2020To2013(rk_fit_gtr200_mid->at(n)),
                        ModuleID2020To2013(rk_fit_gtr300_mid->at(n))};
  array<TVector3, 4> poss = {TVector3(rk_hit_ssd_x->at(n), 0., 0.),
                             TVector3(rk_hit_gtr100_tx2->at(n) + lparam0, rk_hit_gtr100_ty->at(n), 0.),
                             TVector3(rk_hit_gtr200_tx2->at(n) + lparam1, rk_hit_gtr200_ty->at(n), 0.),
                             TVector3(rk_hit_gtr300_tx2->at(n) + lparam2, rk_hit_gtr300_ty->at(n), 0.)};
  fitter->Clear();
  fitter->SetRungeKuttaStepSize(kStepSize);
  fitter->SetMaxSteps(kMaxSteps);
  fitter->SetInitialVertex(init_pos, TVector3(0., 0., 0.));
  fitter->SetInitialMomentum(track_id, init_mom);
  fitter->SetCharge(track_id, rk_charge->at(n));
  for (int i = 0; i < 4; ++i) {
    if (i == 0) {
      fitter->AddHit(track_id, i, geometry->SSD(mids[i]), poss[i], kSSDSigma);
    } else {
      fitter->AddHit(track_id, i, geometry->GTR(mids[i], i - 1), poss[i], kGTRSigma[i - 1]);
    }
  }
  auto chisq = fitter->Fit(kFixVertexXY[kFitWoTarget], kFixPy, kFixVertexZ[kFitWoTarget], kMinuitStrategy, kMaxMinuitFunctionCalls,
                           kInitXRange[0], kInitXRange[1], kInitYRange[0], kInitYRange[1], kInitZRange[0], kInitZRange[1]);
  return chisq;
}

double check_lorentz_effect_220918::FitWoSSD(int n, int tid, double lparam0, double lparam1, double lparam2) {
  auto init_pos = TVector3(0., 0., kTargetZ[tid]);
  auto init_mom = TVector3(rk_proj_x0_mom_gx->at(n), rk_proj_x0_mom_gy->at(n), rk_proj_x0_mom_gz->at(n));
  array<int, 3> gtr_mid = {ModuleID2020To2013(rk_fit_gtr100_mid->at(n)),
                           ModuleID2020To2013(rk_fit_gtr200_mid->at(n)),
                           ModuleID2020To2013(rk_fit_gtr300_mid->at(n))};
  array<TVector3, 3> gtr_pos = {TVector3(rk_hit_gtr100_tx2->at(n) + lparam0, rk_hit_gtr100_ty->at(n), 0.),
                                TVector3(rk_hit_gtr200_tx2->at(n) + lparam1, rk_hit_gtr200_ty->at(n), 0.),
                                TVector3(rk_hit_gtr300_tx2->at(n) + lparam2, rk_hit_gtr300_ty->at(n), 0.)};
  fitter->Clear();
  fitter->SetRungeKuttaStepSize(kStepSize);
  fitter->SetMaxSteps(kMaxSteps);
  fitter->SetInitialVertex(init_pos, kInitPosError);
  fitter->SetInitialMomentum(0, init_mom);
  fitter->SetCharge(0, rk_charge->at(n));
  fitter->AddHit(0, 0, geometry->GTR(ModuleID2020To2013(rk_fit_gtr100_mid->at(n)), 0), gtr_pos[0], kGTRSigma[0]);
  fitter->AddHit(0, 1, geometry->GTR(ModuleID2020To2013(rk_fit_gtr200_mid->at(n)), 1), gtr_pos[1], kGTRSigma[1]);
  fitter->AddHit(0, 2, geometry->GTR(ModuleID2020To2013(rk_fit_gtr300_mid->at(n)), 2), gtr_pos[2], kGTRSigma[2]);
  auto chisq = fitter->Fit(kFixVertexXY[kFitWoSSD], kFixPy, kFixVertexZ[kFitWoSSD], kMinuitStrategy, kMaxMinuitFunctionCalls,
                           kInitXRange[0], kInitXRange[1], kInitYRange[0], kInitYRange[1], kInitZRange[0], kInitZRange[1]);
  return chisq;
}

double check_lorentz_effect_220918::ProjectionSSDX(int n, const TVector3& vtx, const TVector3& mom) {
  vector<int> mids;
  vector<TVector3> lposs;
  fitter->Clear();
  fitter->SetMaxSteps(kMaxSteps);
  fitter->AddHit(0, 0, geometry->SSD(ModuleID2020To2013(rk_fit_ssd_mid->at(n))), TVector3(0., 0., 0.), TVector3(0., 0., 0.));
  fitter->RungeKuttaTracking(0, vtx, mom, rk_charge->at(n));
  fitter->GetFitLPos(0, 0, mids, lposs);
  return lposs[0].X();
}

void check_lorentz_effect_220918::Loop(const TString& out_name) {
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  
  auto file = TFile(out_name, "recreate");
  auto tree = TTree("tree", "tree");
  tree.Branch("run_id",         &run_id,       "run_id/I");
  tree.Branch("event_id",       &event_id,     "event_id/I");
  tree.Branch("track_id",       &out_track_id, "track_id/I");
  tree.Branch("tgt_id",         &tgt_id,       "tgt_id/I");
  tree.Branch("module_id",      &module_id,    "module_id/I");
  tree.Branch("charge",         &charge,       "charge/I");
  tree.Branch("pre_chi2",       &pre_chi2,     "pre_chi2/D");
  tree.Branch("pre_x0_y",       &pre_x0_y,     "pre_x0_y/D");
  tree.Branch("pre_x0_z",       &pre_x0_z,     "pre_x0_z/D");
  tree.Branch("lorentz_id0",    &lorentz_id0);
  tree.Branch("lorentz_param0", &lorentz_param0);
  tree.Branch("lorentz_id1",    &lorentz_id1);
  tree.Branch("lorentz_param1", &lorentz_param1);
  tree.Branch("lorentz_id2",    &lorentz_id2);
  tree.Branch("lorentz_param2", &lorentz_param2);
  tree.Branch("chi2_wo_tgt",    &chi2_wo_tgt);
  tree.Branch("tgt_x",          &tgt_x);
  tree.Branch("tgt_y",          &tgt_y);
  tree.Branch("tgt_z",          &tgt_z);
  tree.Branch("chi2_wo_ssd",    &chi2_wo_ssd);
  tree.Branch("ssd_xres",       &ssd_xres);

//  array<array<TH1*, kNumTargets>, kNumDivides> h_chi2;
//  array<array<TH1*, kNumTargets>, kNumDivides> h_ssd_res;
//  array<TH1*, kNumDivides> h_tgt;
//  for (int i = 0; i < kNumDivides; ++i) {
//    for (int j = 0; j < kNumTargets; ++j) {
//      auto name = Form("h_ssd_res_lonretz_%d_tgt_%d", i, j);
//      h_ssd_res = new TH1F(name, name, 4000, 2., 2.);
//    }
//    auto name = Form("h_tgt_%d", i);
//    h_tgt = new TH1F(name, name, 2000, -100., 100.);
//  }

  for (Long64_t jentry = 0; jentry < nentries; ++jentry) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
    if (jentry % 100 == 0) {
      cout << jentry << " / " << nentries << endl;
    }
    for (int i = 0; i < n_cands; ++i) {
      if (chi_square->at(i) > kMaxChi2) {
        break;
      }
      if (!IsGoodTrack(i)) {
        continue;
      }
      auto tid = TargetID(i);
      if (tid == kNumTargets) {
        continue;
      }
      Clear();
      FillPreValues(i, tid);
      auto ssdx = rk_hit_ssd_x->at(i);
      for (int i0 = 0; i0 < kNumDivides; ++i0) {
        double lparam0 = kLorentzOffset[0] * (kParamOffset[0] + kParamRange[0] * i0 / (kNumDivides - 1.));
        for (int i1 = 0; i1 < kNumDivides; ++i1) {
          double lparam1 = kLorentzOffset[1] * (kParamOffset[1] + kParamRange[1] * i1 / (kNumDivides - 1.));
          for (int i2 = 0; i2 < kNumDivides; ++i2) {
            double lparam2 = kLorentzOffset[2] * (kParamOffset[2] + kParamRange[2] * i2 / (kNumDivides - 1.));
            int id = i0 * kNumDivides2 + i1 * kNumDivides + i2;
            lorentz_id0[id] = i0;
            lorentz_param0[id] = lparam0;
            lorentz_id1[id] = i1;
            lorentz_param1[id] = lparam1;
            lorentz_id2[id] = i2;
            lorentz_param2[id] = lparam2;
            chi2_wo_tgt[id] = FitWoTarget(i, lparam0, lparam1, lparam2);
            auto vtx = fitter->GetFitVertex();
            tgt_x[id] = vtx.X();
            tgt_y[id] = vtx.Y();
            tgt_z[id] = vtx.Z();
            chi2_wo_ssd[id] = FitWoSSD(i, tid, lparam0, lparam1, lparam2);
            vtx = fitter->GetFitVertex();
            auto mom = fitter->GetFitMomentum(0);
            auto proj_ssdx = ProjectionSSDX(i, vtx, mom);
            ssd_xres[id] = proj_ssdx - ssdx;
          }
        }
      }
      tree.Fill();
    }
  }
  file.Write();
  return;
}
