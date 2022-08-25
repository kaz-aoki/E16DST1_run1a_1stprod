#define track_analyzer_220715_cxx
#include "track_analyzer_220715.h"

#include <iostream>

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

using namespace std;
using namespace track_analyzer_220715_parameter;

void track_analyzer_220715::MakeBranches(TTree* tree) {
  tree->Branch("run_id",                           &run_id,      "run_id/I");
  tree->Branch("event_id",                         &event_id,    "event_id/I");
  tree->Branch("n_cands",                          &n_cands,     "n_cands/I");
  tree->Branch("n_pairs",                          &out_n_pairs, "n_pairs/I");
  tree->Branch("plus_track_id",                    &out_plus_track_id);
  tree->Branch("hit_plus_ssd_id",                  &out_hit_plus_ssd_id);
  tree->Branch("hit_plus_ssd_lx",                  &out_hit_plus_ssd_lx);
  tree->Branch("hit_plus_ssd_t",                   &out_hit_plus_ssd_t);
  tree->Branch("hit_plus_ssd_adc",                 &out_hit_plus_ssd_adc);
  tree->Branch("hit_plus_ssd_size",                &out_hit_plus_ssd_size);
  tree->Branch("hit_plus_gtr100_xid",              &out_hit_plus_gtr100_xid);
  tree->Branch("hit_plus_gtr100_yid",              &out_hit_plus_gtr100_yid);
  tree->Branch("hit_plus_gtr100_lx",               &out_hit_plus_gtr100_lx);
  tree->Branch("hit_plus_gtr100_ly",               &out_hit_plus_gtr100_ly);
  tree->Branch("hit_plus_gtr100_xt",               &out_hit_plus_gtr100_xt);
  tree->Branch("hit_plus_gtr100_yt",               &out_hit_plus_gtr100_yt);
  tree->Branch("hit_plus_gtr100_xadc",             &out_hit_plus_gtr100_xadc);
  tree->Branch("hit_plus_gtr100_yadc",             &out_hit_plus_gtr100_yadc);
  tree->Branch("hit_plus_gtr100_xsize",            &out_hit_plus_gtr100_xsize);
  tree->Branch("hit_plus_gtr100_ysize",            &out_hit_plus_gtr100_ysize);
  tree->Branch("hit_plus_gtr200_xid",              &out_hit_plus_gtr200_xid);
  tree->Branch("hit_plus_gtr200_yid",              &out_hit_plus_gtr200_yid);
  tree->Branch("hit_plus_gtr200_lx",               &out_hit_plus_gtr200_lx);
  tree->Branch("hit_plus_gtr200_ly",               &out_hit_plus_gtr200_ly);
  tree->Branch("hit_plus_gtr200_xt",               &out_hit_plus_gtr200_xt);
  tree->Branch("hit_plus_gtr200_yt",               &out_hit_plus_gtr200_yt);
  tree->Branch("hit_plus_gtr200_xadc",             &out_hit_plus_gtr200_xadc);
  tree->Branch("hit_plus_gtr200_yadc",             &out_hit_plus_gtr200_yadc);
  tree->Branch("hit_plus_gtr200_xsize",            &out_hit_plus_gtr200_xsize);
  tree->Branch("hit_plus_gtr200_ysize",            &out_hit_plus_gtr200_ysize);
  tree->Branch("hit_plus_gtr300_xid",              &out_hit_plus_gtr300_xid);
  tree->Branch("hit_plus_gtr300_yid",              &out_hit_plus_gtr300_yid);
  tree->Branch("hit_plus_gtr300_lx",               &out_hit_plus_gtr300_lx);
  tree->Branch("hit_plus_gtr300_ly",               &out_hit_plus_gtr300_ly);
  tree->Branch("hit_plus_gtr300_xt",               &out_hit_plus_gtr300_xt);
  tree->Branch("hit_plus_gtr300_yt",               &out_hit_plus_gtr300_yt);
  tree->Branch("hit_plus_gtr300_xadc",             &out_hit_plus_gtr300_xadc);
  tree->Branch("hit_plus_gtr300_yadc",             &out_hit_plus_gtr300_yadc);
  tree->Branch("hit_plus_gtr300_xsize",            &out_hit_plus_gtr300_xsize);
  tree->Branch("hit_plus_gtr300_ysize",            &out_hit_plus_gtr300_ysize);
  tree->Branch("minus_track_id",                   &out_plus_track_id);
  tree->Branch("hit_minus_ssd_id",                 &out_hit_minus_ssd_id);
  tree->Branch("hit_minus_ssd_lx",                 &out_hit_minus_ssd_lx);
  tree->Branch("hit_minus_ssd_t",                  &out_hit_minus_ssd_t);
  tree->Branch("hit_minus_ssd_adc",                &out_hit_minus_ssd_adc);
  tree->Branch("hit_minus_ssd_size",               &out_hit_minus_ssd_size);
  tree->Branch("hit_minus_gtr100_xid",             &out_hit_minus_gtr100_xid);
  tree->Branch("hit_minus_gtr100_yid",             &out_hit_minus_gtr100_yid);
  tree->Branch("hit_minus_gtr100_lx",              &out_hit_minus_gtr100_lx);
  tree->Branch("hit_minus_gtr100_ly",              &out_hit_minus_gtr100_ly);
  tree->Branch("hit_minus_gtr100_xt",              &out_hit_minus_gtr100_xt);
  tree->Branch("hit_minus_gtr100_yt",              &out_hit_minus_gtr100_yt);
  tree->Branch("hit_minus_gtr100_xadc",            &out_hit_minus_gtr100_xadc);
  tree->Branch("hit_minus_gtr100_yadc",            &out_hit_minus_gtr100_yadc);
  tree->Branch("hit_minus_gtr100_xsize",           &out_hit_minus_gtr100_xsize);
  tree->Branch("hit_minus_gtr100_ysize",           &out_hit_minus_gtr100_ysize);
  tree->Branch("hit_minus_gtr200_xid",             &out_hit_minus_gtr200_xid);
  tree->Branch("hit_minus_gtr200_yid",             &out_hit_minus_gtr200_yid);
  tree->Branch("hit_minus_gtr200_lx",              &out_hit_minus_gtr200_lx);
  tree->Branch("hit_minus_gtr200_ly",              &out_hit_minus_gtr200_ly);
  tree->Branch("hit_minus_gtr200_xt",              &out_hit_minus_gtr200_xt);
  tree->Branch("hit_minus_gtr200_yt",              &out_hit_minus_gtr200_yt);
  tree->Branch("hit_minus_gtr200_xadc",            &out_hit_minus_gtr200_xadc);
  tree->Branch("hit_minus_gtr200_yadc",            &out_hit_minus_gtr200_yadc);
  tree->Branch("hit_minus_gtr200_xsize",           &out_hit_minus_gtr200_xsize);
  tree->Branch("hit_minus_gtr200_ysize",           &out_hit_minus_gtr200_ysize);
  tree->Branch("hit_minus_gtr300_xid",             &out_hit_minus_gtr300_xid);
  tree->Branch("hit_minus_gtr300_yid",             &out_hit_minus_gtr300_yid);
  tree->Branch("hit_minus_gtr300_lx",              &out_hit_minus_gtr300_lx);
  tree->Branch("hit_minus_gtr300_ly",              &out_hit_minus_gtr300_ly);
  tree->Branch("hit_minus_gtr300_xt",              &out_hit_minus_gtr300_xt);
  tree->Branch("hit_minus_gtr300_yt",              &out_hit_minus_gtr300_yt);
  tree->Branch("hit_minus_gtr300_xadc",            &out_hit_minus_gtr300_xadc);
  tree->Branch("hit_minus_gtr300_yadc",            &out_hit_minus_gtr300_yadc);
  tree->Branch("hit_minus_gtr300_xsize",           &out_hit_minus_gtr300_xsize);
  tree->Branch("hit_minus_gtr300_ysize",           &out_hit_minus_gtr300_ysize);
  tree->Branch("chi2",                             &out_chi2);
  tree->Branch("flag",                             &out_flag);
  tree->Branch("distance",                         &out_distance);
  tree->Branch("dir_id",                           &out_dir_id);
  tree->Branch("vtx_x",                            &out_vtx_x);
  tree->Branch("vtx_y",                            &out_vtx_y);
  tree->Branch("vtx_z",                            &out_vtx_z);
  tree->Branch("plus_mom",                         &out_plus_mom);
  tree->Branch("plus_mom_x",                       &out_plus_mom_x);
  tree->Branch("plus_mom_y",                       &out_plus_mom_y);
  tree->Branch("plus_mom_z",                       &out_plus_mom_z);
  tree->Branch("plus_mom_theta",                   &out_plus_mom_theta);
  tree->Branch("plus_mom_phi",                     &out_plus_mom_phi);
  tree->Branch("minus_mom",                        &out_minus_mom);
  tree->Branch("minus_mom_x",                      &out_minus_mom_x);
  tree->Branch("minus_mom_y",                      &out_minus_mom_y);
  tree->Branch("minus_mom_z",                      &out_minus_mom_z);
  tree->Branch("minus_mom_theta",                  &out_minus_mom_theta);
  tree->Branch("minus_mom_phi",                    &out_minus_mom_phi);
  tree->Branch("mom_angle",                        &out_mom_angle);
  tree->Branch("ee_mass",                          &out_ee_mass);
  tree->Branch("pipi_mass",                        &out_pipi_mass);
  tree->Branch("pip_mass",                         &out_pip_mass);
  tree->Branch("kk_mass",                          &out_kk_mass);
  tree->Branch("plus_ssd_mid",                     &out_plus_ssd_mid);
  tree->Branch("plus_gtr100_mid",                  &out_plus_gtr100_mid);
  tree->Branch("plus_gtr200_mid",                  &out_plus_gtr200_mid);
  tree->Branch("plus_gtr300_mid",                  &out_plus_gtr300_mid);
  tree->Branch("plus_hbd_mid",                     &out_plus_hbd_mid);
  tree->Branch("plus_lg_c_mid",                    &out_plus_lg_c_mid);
  tree->Branch("plus_lg_b_mid",                    &out_plus_lg_b_mid);
  tree->Branch("plus_lg_a_mid",                    &out_plus_lg_a_mid);
  tree->Branch("minus_ssd_mid",                    &out_minus_ssd_mid);
  tree->Branch("minus_gtr100_mid",                 &out_minus_gtr100_mid);
  tree->Branch("minus_gtr200_mid",                 &out_minus_gtr200_mid);
  tree->Branch("minus_gtr300_mid",                 &out_minus_gtr300_mid);
  tree->Branch("minus_hbd_mid",                    &out_minus_hbd_mid);
  tree->Branch("minus_lg_c_mid",                   &out_minus_lg_c_mid);
  tree->Branch("minus_lg_b_mid",                   &out_minus_lg_b_mid);
  tree->Branch("minus_lg_a_mid",                   &out_minus_lg_a_mid);
  tree->Branch("fit_plus_ssd_lx",                  &out_fit_plus_ssd_lx);
  tree->Branch("fit_plus_ssd_ly",                  &out_fit_plus_ssd_ly);
  tree->Branch("fit_plus_gtr100_lx",               &out_fit_plus_gtr100_lx);
  tree->Branch("fit_plus_gtr100_ly",               &out_fit_plus_gtr100_ly);
  tree->Branch("fit_plus_gtr200_lx",               &out_fit_plus_gtr200_lx);
  tree->Branch("fit_plus_gtr200_ly",               &out_fit_plus_gtr200_ly);
  tree->Branch("fit_plus_gtr300_lx",               &out_fit_plus_gtr300_lx);
  tree->Branch("fit_plus_gtr300_ly",               &out_fit_plus_gtr300_ly);
  tree->Branch("fit_plus_hbd_lx",                  &out_fit_plus_hbd_lx);
  tree->Branch("fit_plus_hbd_ly",                  &out_fit_plus_hbd_ly);
  tree->Branch("fit_plus_lg_c_lx",                 &out_fit_plus_lg_c_lx);
  tree->Branch("fit_plus_lg_c_ly",                 &out_fit_plus_lg_c_ly);
  tree->Branch("fit_plus_lg_b_lx",                 &out_fit_plus_lg_b_lx);
  tree->Branch("fit_plus_lg_b_ly",                 &out_fit_plus_lg_b_ly);
  tree->Branch("fit_plus_lg_a_lx",                 &out_fit_plus_lg_a_lx);
  tree->Branch("fit_plus_lg_a_ly",                 &out_fit_plus_lg_a_ly);
  tree->Branch("fit_plus_tgt_minus_x",             &out_fit_plus_tgt_minus_x);
  tree->Branch("fit_plus_tgt_minus_y",             &out_fit_plus_tgt_minus_y);
  tree->Branch("fit_plus_tgt_zero_x",              &out_fit_plus_tgt_zero_x);
  tree->Branch("fit_plus_tgt_zero_y",              &out_fit_plus_tgt_zero_y);
  tree->Branch("fit_plus_tgt_plus_x",              &out_fit_plus_tgt_plus_x);
  tree->Branch("fit_plus_tgt_plus_y",              &out_fit_plus_tgt_plus_y);
  tree->Branch("fit_minus_ssd_lx",                 &out_fit_minus_ssd_lx);
  tree->Branch("fit_minus_ssd_ly",                 &out_fit_minus_ssd_ly);
  tree->Branch("fit_minus_gtr100_lx",              &out_fit_minus_gtr100_lx);
  tree->Branch("fit_minus_gtr100_ly",              &out_fit_minus_gtr100_ly);
  tree->Branch("fit_minus_gtr200_lx",              &out_fit_minus_gtr200_lx);
  tree->Branch("fit_minus_gtr200_ly",              &out_fit_minus_gtr200_ly);
  tree->Branch("fit_minus_gtr300_lx",              &out_fit_minus_gtr300_lx);
  tree->Branch("fit_minus_gtr300_ly",              &out_fit_minus_gtr300_ly);
  tree->Branch("fit_minus_hbd_lx",                 &out_fit_minus_hbd_lx);
  tree->Branch("fit_minus_hbd_ly",                 &out_fit_minus_hbd_ly);
  tree->Branch("fit_minus_lg_c_lx",                &out_fit_minus_lg_c_lx);
  tree->Branch("fit_minus_lg_c_ly",                &out_fit_minus_lg_c_ly);
  tree->Branch("fit_minus_lg_b_lx",                &out_fit_minus_lg_b_lx);
  tree->Branch("fit_minus_lg_b_ly",                &out_fit_minus_lg_b_ly);
  tree->Branch("fit_minus_lg_a_lx",                &out_fit_minus_lg_a_lx);
  tree->Branch("fit_minus_lg_a_ly",                &out_fit_minus_lg_a_ly);
  tree->Branch("fit_minus_tgt_minus_x",            &out_fit_minus_tgt_minus_x);
  tree->Branch("fit_minus_tgt_minus_y",            &out_fit_minus_tgt_minus_y);
  tree->Branch("fit_minus_tgt_zero_x",             &out_fit_minus_tgt_zero_x);
  tree->Branch("fit_minus_tgt_zero_y",             &out_fit_minus_tgt_zero_y);
  tree->Branch("fit_minus_tgt_plus_x",             &out_fit_minus_tgt_plus_x);
  tree->Branch("fit_minus_tgt_plus_y",             &out_fit_minus_tgt_plus_y);
  tree->Branch("res_plus_ssd_lx",                  &out_res_plus_ssd_lx);
//  tree->Branch("res_plus_ssd_ly",                  &out_res_plus_ssd_ly);
  tree->Branch("res_plus_gtr100_lx",               &out_res_plus_gtr100_lx);
  tree->Branch("res_plus_gtr100_ly",               &out_res_plus_gtr100_ly);
  tree->Branch("res_plus_gtr200_lx",               &out_res_plus_gtr200_lx);
  tree->Branch("res_plus_gtr200_ly",               &out_res_plus_gtr200_ly);
  tree->Branch("res_plus_gtr300_lx",               &out_res_plus_gtr300_lx);
  tree->Branch("res_plus_gtr300_ly",               &out_res_plus_gtr300_ly);
  tree->Branch("res_minus_ssd_lx",                 &out_res_minus_ssd_lx);
//  tree->Branch("res_minus_ssd_ly",                 &out_res_minus_ssd_ly);
  tree->Branch("res_minus_gtr100_lx",              &out_res_minus_gtr100_lx);
  tree->Branch("res_minus_gtr100_ly",              &out_res_minus_gtr100_ly);
  tree->Branch("res_minus_gtr200_lx",              &out_res_minus_gtr200_lx);
  tree->Branch("res_minus_gtr200_ly",              &out_res_minus_gtr200_ly);
  tree->Branch("res_minus_gtr300_lx",              &out_res_minus_gtr300_lx);
  tree->Branch("res_minus_gtr300_ly",              &out_res_minus_gtr300_ly);
  tree->Branch("fit_parent_mom_x",                 &out_fit_parent_mom_x);
  tree->Branch("fit_parent_mom_y",                 &out_fit_parent_mom_y);
  tree->Branch("fit_parent_mom_z",                 &out_fit_parent_mom_z);
  tree->Branch("fit_parent_tgt_minus_x",           &out_fit_parent_tgt_minus_x);
  tree->Branch("fit_parent_tgt_minus_y",           &out_fit_parent_tgt_minus_y);
  tree->Branch("fit_parent_tgt_minus_flight_path", &out_fit_parent_tgt_minus_flight_path);
  tree->Branch("fit_parent_tgt_zero_x",            &out_fit_parent_tgt_zero_x);
  tree->Branch("fit_parent_tgt_zero_y",            &out_fit_parent_tgt_zero_y);
  tree->Branch("fit_parent_tgt_zero_flight_path",  &out_fit_parent_tgt_zero_flight_path);
  tree->Branch("fit_parent_tgt_plus_x",            &out_fit_parent_tgt_plus_x);
  tree->Branch("fit_parent_tgt_plus_y",            &out_fit_parent_tgt_plus_y);
  tree->Branch("fit_parent_tgt_plus_flight_path",  &out_fit_parent_tgt_plus_flight_path);
  tree->Branch("fit_parent_best_tgt_id",           &out_fit_parent_best_tgt_id);
  tree->Branch("fit_parent_good_tgt_id_set",       &out_fit_parent_good_tgt_id_set);
  tree->Branch("fit_parent_good_tgt_ids",          &out_fit_parent_good_tgt_ids);
  tree->Branch("proj_plus_n_hbds",                 &out_proj_plus_n_hbds);
  tree->Branch("proj_plus_hbd_id",                 &out_proj_plus_hbd_id);
  tree->Branch("proj_plus_hbd_lx",                 &out_proj_plus_hbd_lx);
  tree->Branch("proj_plus_hbd_ly",                 &out_proj_plus_hbd_ly);
  tree->Branch("proj_plus_hbd_resx",               &out_proj_plus_hbd_resx);
  tree->Branch("proj_plus_hbd_resy",               &out_proj_plus_hbd_resy);
  tree->Branch("proj_plus_hbd_adc",                &out_proj_plus_hbd_adc);
  tree->Branch("proj_plus_hbd_size",               &out_proj_plus_hbd_size);
  tree->Branch("proj_plus_hbd_eprob",              &out_proj_plus_hbd_eprob);
  tree->Branch("proj_minus_n_hbds",                &out_proj_minus_n_hbds);
  tree->Branch("proj_minus_hbd_id",                &out_proj_minus_hbd_id);
  tree->Branch("proj_minus_hbd_lx",                &out_proj_minus_hbd_lx);
  tree->Branch("proj_minus_hbd_ly",                &out_proj_minus_hbd_ly);
  tree->Branch("proj_minus_hbd_resx",              &out_proj_minus_hbd_resx);
  tree->Branch("proj_minus_hbd_resy",              &out_proj_minus_hbd_resy);
  tree->Branch("proj_minus_hbd_adc",               &out_proj_minus_hbd_adc);
  tree->Branch("proj_minus_hbd_size",              &out_proj_minus_hbd_size);
  tree->Branch("proj_minus_hbd_eprob",             &out_proj_minus_hbd_eprob);
  return;
}

void track_analyzer_220715::SetHBDs() {
  for (auto& hbd : hbd_indexs) {
    hbd.clear();
  }
  for (int i = 0; i < n_hbd_clusters; ++i) {
    if (kHBDSelection == kUseHBDEProb) {
      auto eprob = hbd_cluster_eprob->at(i);
      if (eprob < 0.5) {
        continue;
      }
    } else if (kHBDSelection == kUseHBDCProb) {
      auto cprob = hbd_cluster_cprob->at(i);
      if (cprob < 0.5) {
        continue;
      }
    } else if (kHBDSelection == kNotUseHBDProb) {
      auto adc = hbd_cluster_adc->at(i);
      auto csize = hbd_cluster_size->at(i);
      if (adc < kMinHBDADC || csize < kMinHBDSize) {
        continue;
      }
    }
    auto mid = hbd_cluster_mid->at(i);
    if (mid < 101 || mid > 109) {
      E16INFO("Invalid HBD cluster module ID: %d. Run ID: %d, Event ID: %d", mid, run_id, event_id);
      continue;
    }
    hbd_indexs[mid - 101].emplace_back(i);
  }
  return;
}

bool track_analyzer_220715::HasAssociatedHBD(int mid, const TVector3& track_pos, vector<int>* _associated_hbd_indexs) {
  bool has_hbd = false;
  _associated_hbd_indexs->clear();
  for (const auto& i : hbd_indexs[mid - 101]) {
    auto cluster_pos = TVector3(hbd_cluster_x->at(i), hbd_cluster_y->at(i), 0.);
    auto res = cluster_pos - track_pos;
    if (fabs(res.X()) > kMaxHBDXResidual) {
      continue;
    }
    if (fabs(res.Y()) > kMaxHBDYResidual) {
      continue;
    }
    has_hbd = true;
    _associated_hbd_indexs->emplace_back(i);
  }
  return has_hbd;
}

bool track_analyzer_220715::HasAssociatedHBD(int n) {
  auto mid = rk_fit_hbd_mid->at(n);
  if (mid < 101 || mid > 109) {
    return false;
  }
  auto track_lpos = TVector3(rk_fit_hbd_x->at(n), rk_fit_hbd_y->at(n), 0.);
  return HasAssociatedHBD(mid, track_lpos, &associated_hbd_indexs[n]);
}

bool track_analyzer_220715::HasUsedCluster(const array<int, kNumTrackingDetectors>& cids) {
  for (int i = 0; i < kNumTrackingDetectors; ++i) {
    for (const auto& used_id : used_cluster_ids[i]) {
      if (cids[i] == used_id) {
        return true;
      }
    }
  }
  return false;
}

bool track_analyzer_220715::IsGoodTrack(int n) {
  auto mom = TVector3(rk_fit_init_mom_gx->at(n), rk_fit_init_mom_gy->at(n), rk_fit_init_mom_gz->at(n));
  if (kUseMinMomCut && mom.Mag() < kMinMom) {
    return false;
  }
  if (kUseMaxMomCut && mom.Mag() > kMaxMom) {
    return false;
  }
  if (kUseHBDAssociationCut && !HasAssociatedHBD(n)) {
    return false;
  }
  if (kUseClulsterDuplicationCut == kSSDAndGTRDuplicationCut) {
    array<int, kNumTrackingDetectors> cids = {rk_hit_ssd_id->at(n),     rk_hit_gtr100_xid->at(n), rk_hit_gtr100_yid->at(n),
                                              rk_hit_gtr200_xid->at(n), rk_hit_gtr200_yid->at(n), rk_hit_gtr300_xid->at(n), rk_hit_gtr300_yid->at(n)};
    if(HasUsedCluster(cids)) {
      return false;
    }
    for (int i = 0; i < kNumTrackingDetectors; ++i) {
      used_cluster_ids[i].emplace_back(cids[i]);
    }
  }
  return true;
}

void track_analyzer_220715::SetTracks() {
  associated_hbd_indexs.clear();
  associated_hbd_indexs.resize(n_cands);
  good_track_indexs.clear();
  for (int i = 0; i < n_cands; ++i) {
    if (kUseChi2Cut && chi_square->at(i) > kMaxChi2) {
      break;
    }
    if (IsGoodTrack(i)) {
      good_track_indexs.emplace_back(i);
    }
  }
  return;
}

bool track_analyzer_220715::IsGoodPair(int n, int m) {
  if (kUseSSDTimeDiffCut) {
    auto ssdt0 = rk_hit_ssd_t->at(n);
    auto ssdt1 = rk_hit_ssd_t->at(m);
    if (fabs(ssdt0 - ssdt1) > kMaxSSDTimeDiff) {
      return false;
    }
  }
  return true;
}

void track_analyzer_220715::SetPairs() {
  good_pair_indexs.clear();
  auto n_good_tracks = good_track_indexs.size();
  if (n_good_tracks < 2) {
    return;
  }
  for (int index0 = 0; index0 < n_good_tracks - 1; ++index0) {
    auto i = good_track_indexs[index0];
    auto charge0 = rk_charge->at(i);
    for (int index1 = index0 + 1; index1 < n_good_tracks; ++index1) {
      auto j = good_track_indexs[index1];
      auto charge1 = rk_charge->at(j);
      if (charge0 == charge1) {
        continue;
      }
      bool is_good_pair;
      if (charge0 == 1) {
        if (IsGoodPair(i, j)) {
          good_pair_indexs.emplace_back(array<int, 2>({i, j}));
        }
      } else {
        if (IsGoodPair(j, i)) {
          good_pair_indexs.emplace_back(array<int, 2>({j, i}));
        }
      }
    }
  }
  return;
}

void track_analyzer_220715::ClearAndResizeBranches() {
  out_n_pairs = good_pair_indexs.size();
  out_plus_track_id.clear();
  out_hit_plus_ssd_id.clear();
  out_hit_plus_ssd_lx.clear();
  out_hit_plus_ssd_t.clear();
  out_hit_plus_ssd_adc.clear();
  out_hit_plus_ssd_size.clear();
  out_hit_plus_gtr100_xid.clear();
  out_hit_plus_gtr100_yid.clear();
  out_hit_plus_gtr100_lx.clear();
  out_hit_plus_gtr100_ly.clear();
  out_hit_plus_gtr100_xt.clear();
  out_hit_plus_gtr100_yt.clear();
  out_hit_plus_gtr100_xadc.clear();
  out_hit_plus_gtr100_yadc.clear();
  out_hit_plus_gtr100_xsize.clear();
  out_hit_plus_gtr100_ysize.clear();
  out_hit_plus_gtr200_xid.clear();
  out_hit_plus_gtr200_yid.clear();
  out_hit_plus_gtr200_lx.clear();
  out_hit_plus_gtr200_ly.clear();
  out_hit_plus_gtr200_xt.clear();
  out_hit_plus_gtr200_yt.clear();
  out_hit_plus_gtr200_xadc.clear();
  out_hit_plus_gtr200_yadc.clear();
  out_hit_plus_gtr200_xsize.clear();
  out_hit_plus_gtr200_ysize.clear();
  out_hit_plus_gtr300_xid.clear();
  out_hit_plus_gtr300_yid.clear();
  out_hit_plus_gtr300_lx.clear();
  out_hit_plus_gtr300_ly.clear();
  out_hit_plus_gtr300_xt.clear();
  out_hit_plus_gtr300_yt.clear();
  out_hit_plus_gtr300_xadc.clear();
  out_hit_plus_gtr300_yadc.clear();
  out_hit_plus_gtr300_xsize.clear();
  out_hit_plus_gtr300_ysize.clear();
  out_minus_track_id.clear();
  out_hit_minus_ssd_id.clear();
  out_hit_minus_ssd_lx.clear();
  out_hit_minus_ssd_t.clear();
  out_hit_minus_ssd_adc.clear();
  out_hit_minus_ssd_size.clear();
  out_hit_minus_gtr100_xid.clear();
  out_hit_minus_gtr100_yid.clear();
  out_hit_minus_gtr100_lx.clear();
  out_hit_minus_gtr100_ly.clear();
  out_hit_minus_gtr100_xt.clear();
  out_hit_minus_gtr100_yt.clear();
  out_hit_minus_gtr100_xadc.clear();
  out_hit_minus_gtr100_yadc.clear();
  out_hit_minus_gtr100_xsize.clear();
  out_hit_minus_gtr100_ysize.clear();
  out_hit_minus_gtr200_xid.clear();
  out_hit_minus_gtr200_yid.clear();
  out_hit_minus_gtr200_lx.clear();
  out_hit_minus_gtr200_ly.clear();
  out_hit_minus_gtr200_xt.clear();
  out_hit_minus_gtr200_yt.clear();
  out_hit_minus_gtr200_xadc.clear();
  out_hit_minus_gtr200_yadc.clear();
  out_hit_minus_gtr200_xsize.clear();
  out_hit_minus_gtr200_ysize.clear();
  out_hit_minus_gtr300_xid.clear();
  out_hit_minus_gtr300_yid.clear();
  out_hit_minus_gtr300_lx.clear();
  out_hit_minus_gtr300_ly.clear();
  out_hit_minus_gtr300_xt.clear();
  out_hit_minus_gtr300_yt.clear();
  out_hit_minus_gtr300_xadc.clear();
  out_hit_minus_gtr300_yadc.clear();
  out_hit_minus_gtr300_xsize.clear();
  out_hit_minus_gtr300_ysize.clear();
  out_chi2.clear();
  out_flag.clear();
  out_distance.clear();
  out_dir_id.clear();
  out_vtx_x.clear();
  out_vtx_y.clear();
  out_vtx_z.clear();
  out_plus_mom.clear();
  out_plus_mom_x.clear();
  out_plus_mom_y.clear();
  out_plus_mom_z.clear();
  out_plus_mom_theta.clear();
  out_plus_mom_phi.clear();
  out_minus_mom.clear();
  out_minus_mom_x.clear();
  out_minus_mom_y.clear();
  out_minus_mom_z.clear();
  out_minus_mom_theta.clear();
  out_minus_mom_phi.clear();
  out_mom_angle.clear();
  out_ee_mass.clear();
  out_pipi_mass.clear();
  out_pip_mass.clear();
  out_kk_mass.clear();
  out_plus_ssd_mid.clear();
  out_plus_gtr100_mid.clear();
  out_plus_gtr200_mid.clear();
  out_plus_gtr300_mid.clear();
  out_plus_hbd_mid.clear();
  out_plus_lg_c_mid.clear();
  out_plus_lg_b_mid.clear();
  out_plus_lg_a_mid.clear();
  out_minus_ssd_mid.clear();
  out_minus_gtr100_mid.clear();
  out_minus_gtr200_mid.clear();
  out_minus_gtr300_mid.clear();
  out_minus_hbd_mid.clear();
  out_minus_lg_c_mid.clear();
  out_minus_lg_b_mid.clear();
  out_minus_lg_a_mid.clear();
  out_fit_plus_ssd_lx.clear();
  out_fit_plus_ssd_ly.clear();
  out_fit_plus_gtr100_lx.clear();
  out_fit_plus_gtr100_ly.clear();
  out_fit_plus_gtr200_lx.clear();
  out_fit_plus_gtr200_ly.clear();
  out_fit_plus_gtr300_lx.clear();
  out_fit_plus_gtr300_ly.clear();
  out_fit_plus_hbd_lx.clear();
  out_fit_plus_hbd_ly.clear();
  out_fit_plus_lg_c_lx.clear();
  out_fit_plus_lg_c_ly.clear();
  out_fit_plus_lg_b_lx.clear();
  out_fit_plus_lg_b_ly.clear();
  out_fit_plus_lg_a_lx.clear();
  out_fit_plus_lg_a_ly.clear();
  out_fit_plus_tgt_minus_x.clear();
  out_fit_plus_tgt_minus_y.clear();
  out_fit_plus_tgt_zero_x.clear();
  out_fit_plus_tgt_zero_y.clear();
  out_fit_plus_tgt_plus_x.clear();
  out_fit_plus_tgt_plus_y.clear();
  out_fit_minus_ssd_lx.clear();
  out_fit_minus_ssd_ly.clear();
  out_fit_minus_gtr100_lx.clear();
  out_fit_minus_gtr100_ly.clear();
  out_fit_minus_gtr200_lx.clear();
  out_fit_minus_gtr200_ly.clear();
  out_fit_minus_gtr300_lx.clear();
  out_fit_minus_gtr300_ly.clear();
  out_fit_minus_hbd_lx.clear();
  out_fit_minus_hbd_ly.clear();
  out_fit_minus_lg_c_lx.clear();
  out_fit_minus_lg_c_ly.clear();
  out_fit_minus_lg_b_lx.clear();
  out_fit_minus_lg_b_ly.clear();
  out_fit_minus_lg_a_lx.clear();
  out_fit_minus_lg_a_ly.clear();
  out_fit_minus_tgt_minus_x.clear();
  out_fit_minus_tgt_minus_y.clear();
  out_fit_minus_tgt_zero_x.clear();
  out_fit_minus_tgt_zero_y.clear();
  out_fit_minus_tgt_plus_x.clear();
  out_fit_minus_tgt_plus_y.clear();
  out_res_plus_ssd_lx.clear();
//  out_res_plus_ssd_ly.clear();
  out_res_plus_gtr100_lx.clear();
  out_res_plus_gtr100_ly.clear();
  out_res_plus_gtr200_lx.clear();
  out_res_plus_gtr200_ly.clear();
  out_res_plus_gtr300_lx.clear();
  out_res_plus_gtr300_ly.clear();
  out_res_minus_ssd_lx.clear();
//  out_res_minus_ssd_ly.clear();
  out_res_minus_gtr100_lx.clear();
  out_res_minus_gtr100_ly.clear();
  out_res_minus_gtr200_lx.clear();
  out_res_minus_gtr200_ly.clear();
  out_res_minus_gtr300_lx.clear();
  out_res_minus_gtr300_ly.clear();
  out_fit_parent_mom_x.clear();
  out_fit_parent_mom_y.clear();
  out_fit_parent_mom_z.clear();
  out_fit_parent_tgt_minus_x.clear();
  out_fit_parent_tgt_minus_y.clear();
  out_fit_parent_tgt_minus_flight_path.clear();
  out_fit_parent_tgt_zero_x.clear();
  out_fit_parent_tgt_zero_y.clear();
  out_fit_parent_tgt_zero_flight_path.clear();
  out_fit_parent_tgt_plus_x.clear();
  out_fit_parent_tgt_plus_y.clear();
  out_fit_parent_tgt_plus_flight_path.clear();
  out_fit_parent_best_tgt_id.clear();
  out_fit_parent_good_tgt_id_set.clear();
  out_fit_parent_good_tgt_ids.clear();
  out_proj_plus_n_hbds.clear();
  out_proj_plus_hbd_id.clear();
  out_proj_plus_hbd_lx.clear();
  out_proj_plus_hbd_ly.clear();
  out_proj_plus_hbd_resx.clear();
  out_proj_plus_hbd_resy.clear();
  out_proj_plus_hbd_adc.clear();
  out_proj_plus_hbd_size.clear();
  out_proj_plus_hbd_eprob.clear();
  out_proj_minus_n_hbds.clear();
  out_proj_minus_hbd_id.clear();
  out_proj_minus_hbd_lx.clear();
  out_proj_minus_hbd_ly.clear();
  out_proj_minus_hbd_resx.clear();
  out_proj_minus_hbd_resy.clear();
  out_proj_minus_hbd_adc.clear();
  out_proj_minus_hbd_size.clear();
  out_proj_minus_hbd_eprob.clear();
  out_plus_track_id.resize(out_n_pairs);
  out_hit_plus_ssd_id.resize(out_n_pairs);
  out_hit_plus_ssd_lx.resize(out_n_pairs);
  out_hit_plus_ssd_t.resize(out_n_pairs);
  out_hit_plus_ssd_adc.resize(out_n_pairs);
  out_hit_plus_ssd_size.resize(out_n_pairs);
  out_hit_plus_gtr100_xid.resize(out_n_pairs);
  out_hit_plus_gtr100_yid.resize(out_n_pairs);
  out_hit_plus_gtr100_lx.resize(out_n_pairs);
  out_hit_plus_gtr100_ly.resize(out_n_pairs);
  out_hit_plus_gtr100_xt.resize(out_n_pairs);
  out_hit_plus_gtr100_yt.resize(out_n_pairs);
  out_hit_plus_gtr100_xadc.resize(out_n_pairs);
  out_hit_plus_gtr100_yadc.resize(out_n_pairs);
  out_hit_plus_gtr100_xsize.resize(out_n_pairs);
  out_hit_plus_gtr100_ysize.resize(out_n_pairs);
  out_hit_plus_gtr200_xid.resize(out_n_pairs);
  out_hit_plus_gtr200_yid.resize(out_n_pairs);
  out_hit_plus_gtr200_lx.resize(out_n_pairs);
  out_hit_plus_gtr200_ly.resize(out_n_pairs);
  out_hit_plus_gtr200_xt.resize(out_n_pairs);
  out_hit_plus_gtr200_yt.resize(out_n_pairs);
  out_hit_plus_gtr200_xadc.resize(out_n_pairs);
  out_hit_plus_gtr200_yadc.resize(out_n_pairs);
  out_hit_plus_gtr200_xsize.resize(out_n_pairs);
  out_hit_plus_gtr200_ysize.resize(out_n_pairs);
  out_hit_plus_gtr300_xid.resize(out_n_pairs);
  out_hit_plus_gtr300_yid.resize(out_n_pairs);
  out_hit_plus_gtr300_lx.resize(out_n_pairs);
  out_hit_plus_gtr300_ly.resize(out_n_pairs);
  out_hit_plus_gtr300_xt.resize(out_n_pairs);
  out_hit_plus_gtr300_yt.resize(out_n_pairs);
  out_hit_plus_gtr300_xadc.resize(out_n_pairs);
  out_hit_plus_gtr300_yadc.resize(out_n_pairs);
  out_hit_plus_gtr300_xsize.resize(out_n_pairs);
  out_hit_plus_gtr300_ysize.resize(out_n_pairs);
  out_minus_track_id.resize(out_n_pairs);
  out_hit_minus_ssd_id.resize(out_n_pairs);
  out_hit_minus_ssd_lx.resize(out_n_pairs);
  out_hit_minus_ssd_t.resize(out_n_pairs);
  out_hit_minus_ssd_adc.resize(out_n_pairs);
  out_hit_minus_ssd_size.resize(out_n_pairs);
  out_hit_minus_gtr100_xid.resize(out_n_pairs);
  out_hit_minus_gtr100_yid.resize(out_n_pairs);
  out_hit_minus_gtr100_lx.resize(out_n_pairs);
  out_hit_minus_gtr100_ly.resize(out_n_pairs);
  out_hit_minus_gtr100_xt.resize(out_n_pairs);
  out_hit_minus_gtr100_yt.resize(out_n_pairs);
  out_hit_minus_gtr100_xadc.resize(out_n_pairs);
  out_hit_minus_gtr100_yadc.resize(out_n_pairs);
  out_hit_minus_gtr100_xsize.resize(out_n_pairs);
  out_hit_minus_gtr100_ysize.resize(out_n_pairs);
  out_hit_minus_gtr200_xid.resize(out_n_pairs);
  out_hit_minus_gtr200_yid.resize(out_n_pairs);
  out_hit_minus_gtr200_lx.resize(out_n_pairs);
  out_hit_minus_gtr200_ly.resize(out_n_pairs);
  out_hit_minus_gtr200_xt.resize(out_n_pairs);
  out_hit_minus_gtr200_yt.resize(out_n_pairs);
  out_hit_minus_gtr200_xadc.resize(out_n_pairs);
  out_hit_minus_gtr200_yadc.resize(out_n_pairs);
  out_hit_minus_gtr200_xsize.resize(out_n_pairs);
  out_hit_minus_gtr200_ysize.resize(out_n_pairs);
  out_hit_minus_gtr300_xid.resize(out_n_pairs);
  out_hit_minus_gtr300_yid.resize(out_n_pairs);
  out_hit_minus_gtr300_lx.resize(out_n_pairs);
  out_hit_minus_gtr300_ly.resize(out_n_pairs);
  out_hit_minus_gtr300_xt.resize(out_n_pairs);
  out_hit_minus_gtr300_yt.resize(out_n_pairs);
  out_hit_minus_gtr300_xadc.resize(out_n_pairs);
  out_hit_minus_gtr300_yadc.resize(out_n_pairs);
  out_hit_minus_gtr300_xsize.resize(out_n_pairs);
  out_hit_minus_gtr300_ysize.resize(out_n_pairs);
  out_chi2.resize(out_n_pairs);
  out_flag.resize(out_n_pairs);
  out_distance.resize(out_n_pairs);
  out_dir_id.resize(out_n_pairs);
  out_vtx_x.resize(out_n_pairs);
  out_vtx_y.resize(out_n_pairs);
  out_vtx_z.resize(out_n_pairs);
  out_plus_mom.resize(out_n_pairs);
  out_plus_mom_x.resize(out_n_pairs);
  out_plus_mom_y.resize(out_n_pairs);
  out_plus_mom_z.resize(out_n_pairs);
  out_plus_mom_theta.resize(out_n_pairs);
  out_plus_mom_phi.resize(out_n_pairs);
  out_minus_mom.resize(out_n_pairs);
  out_minus_mom_x.resize(out_n_pairs);
  out_minus_mom_y.resize(out_n_pairs);
  out_minus_mom_z.resize(out_n_pairs);
  out_minus_mom_theta.resize(out_n_pairs);
  out_minus_mom_phi.resize(out_n_pairs);
  out_mom_angle.resize(out_n_pairs);
  out_ee_mass.resize(out_n_pairs);
  out_pipi_mass.resize(out_n_pairs);
  out_pip_mass.resize(out_n_pairs);
  out_kk_mass.resize(out_n_pairs);
  out_plus_ssd_mid.resize(out_n_pairs);
  out_plus_gtr100_mid.resize(out_n_pairs);
  out_plus_gtr200_mid.resize(out_n_pairs);
  out_plus_gtr300_mid.resize(out_n_pairs);
  out_plus_hbd_mid.resize(out_n_pairs);
  out_plus_lg_c_mid.resize(out_n_pairs);
  out_plus_lg_b_mid.resize(out_n_pairs);
  out_plus_lg_a_mid.resize(out_n_pairs);
  out_minus_ssd_mid.resize(out_n_pairs);
  out_minus_gtr100_mid.resize(out_n_pairs);
  out_minus_gtr200_mid.resize(out_n_pairs);
  out_minus_gtr300_mid.resize(out_n_pairs);
  out_minus_hbd_mid.resize(out_n_pairs);
  out_minus_lg_c_mid.resize(out_n_pairs);
  out_minus_lg_b_mid.resize(out_n_pairs);
  out_minus_lg_a_mid.resize(out_n_pairs);
  out_fit_plus_ssd_lx.resize(out_n_pairs);
  out_fit_plus_ssd_ly.resize(out_n_pairs);
  out_fit_plus_gtr100_lx.resize(out_n_pairs);
  out_fit_plus_gtr100_ly.resize(out_n_pairs);
  out_fit_plus_gtr200_lx.resize(out_n_pairs);
  out_fit_plus_gtr200_ly.resize(out_n_pairs);
  out_fit_plus_gtr300_lx.resize(out_n_pairs);
  out_fit_plus_gtr300_ly.resize(out_n_pairs);
  out_fit_plus_hbd_lx.resize(out_n_pairs);
  out_fit_plus_hbd_ly.resize(out_n_pairs);
  out_fit_plus_lg_c_lx.resize(out_n_pairs);
  out_fit_plus_lg_c_ly.resize(out_n_pairs);
  out_fit_plus_lg_b_lx.resize(out_n_pairs);
  out_fit_plus_lg_b_ly.resize(out_n_pairs);
  out_fit_plus_lg_a_lx.resize(out_n_pairs);
  out_fit_plus_lg_a_ly.resize(out_n_pairs);
  out_fit_plus_tgt_minus_x.resize(out_n_pairs);
  out_fit_plus_tgt_minus_y.resize(out_n_pairs);
  out_fit_plus_tgt_zero_x.resize(out_n_pairs);
  out_fit_plus_tgt_zero_y.resize(out_n_pairs);
  out_fit_plus_tgt_plus_x.resize(out_n_pairs);
  out_fit_plus_tgt_plus_y.resize(out_n_pairs);
  out_fit_minus_ssd_lx.resize(out_n_pairs);
  out_fit_minus_ssd_ly.resize(out_n_pairs);
  out_fit_minus_gtr100_lx.resize(out_n_pairs);
  out_fit_minus_gtr100_ly.resize(out_n_pairs);
  out_fit_minus_gtr200_lx.resize(out_n_pairs);
  out_fit_minus_gtr200_ly.resize(out_n_pairs);
  out_fit_minus_gtr300_lx.resize(out_n_pairs);
  out_fit_minus_gtr300_ly.resize(out_n_pairs);
  out_fit_minus_hbd_lx.resize(out_n_pairs);
  out_fit_minus_hbd_ly.resize(out_n_pairs);
  out_fit_minus_lg_c_lx.resize(out_n_pairs);
  out_fit_minus_lg_c_ly.resize(out_n_pairs);
  out_fit_minus_lg_b_lx.resize(out_n_pairs);
  out_fit_minus_lg_b_ly.resize(out_n_pairs);
  out_fit_minus_lg_a_lx.resize(out_n_pairs);
  out_fit_minus_lg_a_ly.resize(out_n_pairs);
  out_fit_minus_tgt_minus_x.resize(out_n_pairs);
  out_fit_minus_tgt_minus_y.resize(out_n_pairs);
  out_fit_minus_tgt_zero_x.resize(out_n_pairs);
  out_fit_minus_tgt_zero_y.resize(out_n_pairs);
  out_fit_minus_tgt_plus_x.resize(out_n_pairs);
  out_fit_minus_tgt_plus_y.resize(out_n_pairs);
  out_res_plus_ssd_lx.resize(out_n_pairs);
//  out_res_plus_ssd_ly.resize(out_n_pairs);
  out_res_plus_gtr100_lx.resize(out_n_pairs);
  out_res_plus_gtr100_ly.resize(out_n_pairs);
  out_res_plus_gtr200_lx.resize(out_n_pairs);
  out_res_plus_gtr200_ly.resize(out_n_pairs);
  out_res_plus_gtr300_lx.resize(out_n_pairs);
  out_res_plus_gtr300_ly.resize(out_n_pairs);
  out_res_minus_ssd_lx.resize(out_n_pairs);
//  out_res_minus_ssd_ly.resize(out_n_pairs);
  out_res_minus_gtr100_lx.resize(out_n_pairs);
  out_res_minus_gtr100_ly.resize(out_n_pairs);
  out_res_minus_gtr200_lx.resize(out_n_pairs);
  out_res_minus_gtr200_ly.resize(out_n_pairs);
  out_res_minus_gtr300_lx.resize(out_n_pairs);
  out_res_minus_gtr300_ly.resize(out_n_pairs);
  out_fit_parent_mom_x.resize(out_n_pairs);
  out_fit_parent_mom_y.resize(out_n_pairs);
  out_fit_parent_mom_z.resize(out_n_pairs);
  out_fit_parent_tgt_minus_x.resize(out_n_pairs);
  out_fit_parent_tgt_minus_y.resize(out_n_pairs);
  out_fit_parent_tgt_minus_flight_path.resize(out_n_pairs);
  out_fit_parent_tgt_zero_x.resize(out_n_pairs);
  out_fit_parent_tgt_zero_y.resize(out_n_pairs);
  out_fit_parent_tgt_zero_flight_path.resize(out_n_pairs);
  out_fit_parent_tgt_plus_x.resize(out_n_pairs);
  out_fit_parent_tgt_plus_y.resize(out_n_pairs);
  out_fit_parent_tgt_plus_flight_path.resize(out_n_pairs);
  out_fit_parent_best_tgt_id.resize(out_n_pairs);
  out_fit_parent_good_tgt_id_set.resize(out_n_pairs);
  out_fit_parent_good_tgt_ids.resize(out_n_pairs);
  out_proj_plus_n_hbds.resize(out_n_pairs);
  out_proj_plus_hbd_id.resize(out_n_pairs);
  out_proj_plus_hbd_lx.resize(out_n_pairs);
  out_proj_plus_hbd_ly.resize(out_n_pairs);
  out_proj_plus_hbd_resx.resize(out_n_pairs);
  out_proj_plus_hbd_resy.resize(out_n_pairs);
  out_proj_plus_hbd_adc.resize(out_n_pairs);
  out_proj_plus_hbd_size.resize(out_n_pairs);
  out_proj_plus_hbd_eprob.resize(out_n_pairs);
  out_proj_minus_n_hbds.resize(out_n_pairs);
  out_proj_minus_hbd_id.resize(out_n_pairs);
  out_proj_minus_hbd_lx.resize(out_n_pairs);
  out_proj_minus_hbd_ly.resize(out_n_pairs);
  out_proj_minus_hbd_resx.resize(out_n_pairs);
  out_proj_minus_hbd_resy.resize(out_n_pairs);
  out_proj_minus_hbd_adc.resize(out_n_pairs);
  out_proj_minus_hbd_size.resize(out_n_pairs);
  out_proj_minus_hbd_eprob.resize(out_n_pairs);
  return;
}

double track_analyzer_220715::CalcMass(int flag, const TVector3& pmom, const TVector3& mmom) {
  double mass2[2];
  if (flag == kEE) {
    mass2[0] = kElectronMass2;
    mass2[1] = kElectronMass2;
  } else if (flag == kPiPi) {
    mass2[0] = kPionMass2;
    mass2[1] = kPionMass2;
  } else if (flag == kPiP) {
    mass2[0] = kPionMass2;
    mass2[1] = kProtonMass2;
  } else if (flag == kKK) {
    mass2[0] = kKaonMass2;
    mass2[1] = kKaonMass2;
  } else {
    std::cerr << "Invalid calculation flag : " << flag << std::endl;
    return -1.;
  }
  double p0 = pmom.X() * pmom.X() + pmom.Y() * pmom.Y() + pmom.Z() * pmom.Z();
  double p1 = mmom.X() * mmom.X() + mmom.Y() * mmom.Y() + mmom.Z() * mmom.Z();
  double e0 = sqrt(p0 + mass2[0]);
  double e1 = sqrt(p1 + mass2[1]);
  double p0p1 = pmom.X() * mmom.X() + pmom.Y() * mmom.Y() + pmom.Z() * mmom.Z();
  return sqrt(mass2[0] + mass2[1] + 2. * (e0 * e1 - p0p1));
}

void track_analyzer_220715::FillTVector3(int n, const TVector3& tvec, vector<double>* x, vector<double>* y, vector<double>* z) {
  x->at(n) = tvec.X();
  y->at(n) = tvec.Y();
  z->at(n) = tvec.Z();
  return;
}

void track_analyzer_220715::FillTVector3(int n, const TVector3& tvec, vector<double>* x, vector<double>* y) {
  x->at(n) = tvec.X();
  y->at(n) = tvec.Y();
  return;
}

void track_analyzer_220715::FillBranchesFromPairFit(int n, double chi2) {
  auto vtx       = fitter->GetFitVertex();
  array<TVector3, 2> moms;
  array<array<TVector3, 4>, 2> lposs;
  for (int t = 0; t < 2; ++t) {
    moms[t] = fitter->GetFitMomentum(t);
    for (int l = 0; l < 4; ++l) {
      vector<int>      tmp_mids;
      vector<TVector3> tmp_lposs;
      fitter->GetFitLPos(t, l, tmp_mids, tmp_lposs);
      lposs[t][l] = tmp_lposs[0];
    }
  }
  out_chi2[n]            = chi2;
  out_plus_mom[n]        = moms[0].Mag();
  out_plus_mom_theta[n]  = moms[0].Theta();
  out_plus_mom_phi[n]    = moms[0].Phi();
  out_minus_mom[n]       = moms[1].Mag();
  out_minus_mom_theta[n] = moms[1].Theta();
  out_minus_mom_phi[n]   = moms[1].Phi();
  out_mom_angle[n]       = moms[0].Angle(moms[1]);
  out_ee_mass[n]         = CalcMass(kEE,   moms[0], moms[1]);
  out_pipi_mass[n]       = CalcMass(kPiPi, moms[0], moms[1]);
  out_pip_mass[n]        = CalcMass(kPiP,  moms[0], moms[1]);
  out_kk_mass[n]         = CalcMass(kKK,   moms[0], moms[1]);
  FillTVector3(n, vtx,         &out_vtx_x,               &out_vtx_y,               &out_vtx_z);
  FillTVector3(n, moms[0],     &out_plus_mom_x,          &out_plus_mom_y,          &out_plus_mom_z);
  FillTVector3(n, moms[1],     &out_minus_mom_x,         &out_minus_mom_y,         &out_minus_mom_z);
  FillTVector3(n, lposs[0][0], &out_fit_plus_ssd_lx,     &out_fit_plus_ssd_ly);
  FillTVector3(n, lposs[0][1], &out_fit_plus_gtr100_lx,  &out_fit_plus_gtr100_ly);
  FillTVector3(n, lposs[0][2], &out_fit_plus_gtr200_lx,  &out_fit_plus_gtr200_ly);
  FillTVector3(n, lposs[0][3], &out_fit_plus_gtr300_lx,  &out_fit_plus_gtr300_ly);
  FillTVector3(n, lposs[1][0], &out_fit_minus_ssd_lx,    &out_fit_minus_ssd_ly);
  FillTVector3(n, lposs[1][1], &out_fit_minus_gtr100_lx, &out_fit_minus_gtr100_ly);
  FillTVector3(n, lposs[1][2], &out_fit_minus_gtr200_lx, &out_fit_minus_gtr200_ly);
  FillTVector3(n, lposs[1][3], &out_fit_minus_gtr300_lx, &out_fit_minus_gtr300_ly);
  return;
}

int track_analyzer_220715::ModuleID2013(int m) {
  return kModuleID2013[1][m - 100];
}

void track_analyzer_220715::PairFit(int n) {
  fitter->Clear();
  fitter->SetInitialVertex(kInitVertex, kVertexSigma);
  for (int tid = 0; tid < 2; ++tid) {
    auto i = good_pair_indexs[n][tid];
    if (tid == 0) {
      fitter->SetCharge(tid, 1.);
    } else {
      fitter->SetCharge(tid, -1.);
    }
    fitter->SetInitialMomentum(tid, TVector3(rk_fit_init_mom_gx->at(i), rk_fit_init_mom_gy->at(i), rk_fit_init_mom_gz->at(i)));
    fitter->AddHit(tid, 0, geometry->SSD(ModuleID2013(rk_fit_ssd_mid->at(i))),       TVector3(rk_hit_ssd_x->at(i),      0.,                      0.), kSSDSigma);
    fitter->AddHit(tid, 1, geometry->GTR(ModuleID2013(rk_fit_gtr100_mid->at(i)), 0), TVector3(rk_hit_gtr100_tx2->at(i), rk_hit_gtr100_ty->at(i), 0.), kGTR100Sigma);
    fitter->AddHit(tid, 2, geometry->GTR(ModuleID2013(rk_fit_gtr200_mid->at(i)), 1), TVector3(rk_hit_gtr200_tx2->at(i), rk_hit_gtr200_ty->at(i), 0.), kGTR200Sigma);
    fitter->AddHit(tid, 3, geometry->GTR(ModuleID2013(rk_fit_gtr300_mid->at(i)), 2), TVector3(rk_hit_gtr300_tx2->at(i), rk_hit_gtr300_ty->at(i), 0.), kGTR300Sigma);
  }
  fitter->SetRungeKuttaStepSize(kStepSize);
  fitter->SetMaxSteps(kMaxSteps);
  auto chi2 = fitter->Fit(kFixVtxXY, kFixPy, kFixVtxZ, kStrategy, kMaxFuncCalls,
                          kVtxXRange[0], kVtxXRange[1], kVtxYRange[0], kVtxYRange[1], kVtxZRange[0], kVtxZRange[1]);
  FillBranchesFromPairFit(n, chi2);
  return;
}

void track_analyzer_220715::FillBranchesFromStepTrack(int n, int flag, double dist_cm, const Hep3Vector& hep_vtx, const Hep3Vector& hep_plus_mom, const Hep3Vector& hep_minus_mom) {
  out_flag[n]        = flag;
  out_distance[n]    = dist_cm           * 10.;
  out_vtx_x[n]       = hep_vtx.x()       * 10.;
  out_vtx_y[n]       = hep_vtx.y()       * 10.;
  out_vtx_z[n]       = hep_vtx.z()       * 10.;
  auto pmom = TVector3(hep_plus_mom.x(),  hep_plus_mom.y(),  hep_plus_mom.z());
  auto mmom = TVector3(hep_minus_mom.x(), hep_minus_mom.y(), hep_minus_mom.z());
  out_plus_mom[n]        = pmom.Mag();
  out_plus_mom_x[n]      = pmom.X();
  out_plus_mom_y[n]      = pmom.Y();
  out_plus_mom_z[n]      = pmom.Z();
  out_plus_mom_theta[n]  = pmom.Theta();
  out_plus_mom_phi[n]    = pmom.Phi();
  out_minus_mom[n]       = mmom.Mag();
  out_minus_mom_x[n]     = mmom.X();
  out_minus_mom_y[n]     = mmom.Y();
  out_minus_mom_z[n]     = mmom.Z();
  out_minus_mom_theta[n] = mmom.Theta();
  out_minus_mom_phi[n]   = mmom.Phi();
  out_mom_angle[n]       = pmom.Angle(mmom);
  out_ee_mass[n]         = CalcMass(kEE,   pmom, mmom);
  out_pipi_mass[n]       = CalcMass(kPiPi, pmom, mmom);
  out_pip_mass[n]        = CalcMass(kPiP,  pmom, mmom);
  out_kk_mass[n]         = CalcMass(kKK,   pmom, mmom);
  return;
}

void track_analyzer_220715::NearestPoint(int n) {
  array<Hep3Vector, 2> init_poss;
  array<Hep3Vector, 2> init_moms;
  array<E16ANA_StepTrack*, 2> tracks;
  for (int t = 0; t < 2; ++t) {
    auto i = good_pair_indexs[n][t];
    auto pos = Hep3Vector(rk_fit_init_pos_gx->at(i) * 0.1, rk_fit_init_pos_gy->at(i) * 0.1, rk_fit_init_pos_gz->at(i) * 0.1);
    auto mom = Hep3Vector(rk_fit_init_mom_gx->at(i), rk_fit_init_mom_gy->at(i), rk_fit_init_mom_gz->at(i));
    double charge;
    if (t == 0) {
      charge = 1.;
    } else {
      charge = -1.;
    }
    tracks[t] = new E16ANA_StepTrack(bfield_map, pos, mom, charge, kStepTrackSizeCm, kStepTrackArraySize);
  }
  auto dist_cm       = double();
  auto hep_vtx       = Hep3Vector();
  auto hep_plus_mom  = Hep3Vector();
  auto hep_minus_mom = Hep3Vector();
  auto flag = tracks[0]->Cross(*tracks[1], &dist_cm, &hep_vtx, &hep_plus_mom, &hep_minus_mom);
  FillBranchesFromStepTrack(n, flag, dist_cm, hep_vtx, hep_plus_mom, hep_minus_mom);
  for (auto& track : tracks) {
    delete track;
  }
  return;
}

int track_analyzer_220715::DirID(int i, int j) {
  auto mid0 = rk_fit_gtr300_mid->at(i);
  auto mid1 = rk_fit_gtr300_mid->at(j);
  if (mid0 > 105) {
    if (mid1 > 105) {
      return kLL;
    } else {
      return kLR;
    }
  } else {
    if (mid1 > 105) {
      return kRL;
    } else {
      return kRR;
    }
  }
  return kNumDirs;
}

int track_analyzer_220715::ModuleID2013_27(int m) {
  return kModuleID2013[1][m - 100 + 1];
}

void track_analyzer_220715::ProjectionHBDAndLG(int n) {
  for (int t = 0; t < 2; ++t) {
    auto i = good_pair_indexs[n][t];
    proj_fitter->Clear();
    int tid = 0;
    TVector3 lpos(0., 0., 0.);
    TVector3 lsigma(0., 0., 0.);
    int mid;
    if (t == 0) {
      mid = out_plus_gtr300_mid[n];
    } else {
      mid = out_minus_gtr300_mid[n];
    }
    int lid = 0; // only 1 layer in 1 RK
    int hid = 0; // oonly 1 hit in 1 RK
    auto init_pos = TVector3(out_vtx_x[n], out_vtx_y[n], out_vtx_z[n]);
    TVector3 init_mom;
    double charge;
    if (t == 0) {
      init_mom.SetXYZ(out_plus_mom_x[n],  out_plus_mom_y[n],  out_plus_mom_z[n]);
      charge = 1.;
    } else {
      init_mom.SetXYZ(out_minus_mom_x[n], out_minus_mom_y[n], out_minus_mom_z[n]);
      charge = -1.;
    }
    std::vector<int> mids;
    std::vector<TVector3> lposs;
    std::vector<TVector3> lmoms;
    for (int l = 0; l < 4; ++l) {
      int nstps = 100000;
//      double r;
      for (int m = mid - 2; m <= mid + 2; ++m) {
        if (m < 101 || m == 105 || m > 109) {
          continue;
        }
        auto mid2013 = ModuleID2013_27(m);
        proj_fitter->Clear();
        if (l == 0) {
          auto tmp_geom = geometry->HBD(mid2013);
          proj_fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
        } else {
          auto tmp_geom = geometry->LG(mid2013, kTypicalLGBlocks[l - 1]);
          proj_fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
        }
        proj_fitter->SetMaxSteps(kProjectionMaxSteps);
        proj_fitter->RungeKuttaTracking(tid, init_pos, init_mom, charge);
        proj_fitter->GetFitLPos(tid, lid, mids, lposs);
        proj_fitter->GetFitLMom(tid, lid, mids, lmoms);
        auto lpos = lposs[hid];
        auto lmom = lmoms[hid];
//        if (fabs(lpos.X()) >= fabs(E16DST_DST1Constant::kInvalidValue)) {
//          continue;
//        }
        TVector3 gpos;
        TVector3 gmom;
        if (l == 0) {
          gpos = geometry->HBD(mid2013)->GetGPos(lpos);
          gmom = geometry->HBD(mid2013)->GetGMom(lmom);
        } else {
          gpos = geometry->LG(mid2013, kTypicalLGBlocks[l - 1])->GetGPos(lpos);
          gmom = geometry->LG(mid2013, kTypicalLGBlocks[l - 1])->GetGMom(lmom);
        }
        auto nstps_tmp = proj_fitter->GetTrackSteps(tid).size();
        if (nstps_tmp < nstps) {
  //      if (gpos.Mag() < r) {
          if (l == 0) {
            if (t == 0) {
              out_plus_hbd_mid[n]    = m;
              out_fit_plus_hbd_lx[n] = lpos.X();
              out_fit_plus_hbd_ly[n] = lpos.Y();
            } else {
              out_minus_hbd_mid[n]    = m;
              out_fit_minus_hbd_lx[n] = lpos.X();
              out_fit_minus_hbd_ly[n] = lpos.Y();
            }
          } else {
            auto lpos_lgvd = geometry->LGVD(mid2013)->GetLPos(gpos);
            if (l == 1) {
              if (t == 0) {
                out_plus_lg_c_mid[n]    = m;
                out_fit_plus_lg_c_lx[n] = lpos_lgvd.X();
                out_fit_plus_lg_c_ly[n] = lpos_lgvd.Y();
              } else {
                out_minus_lg_c_mid[n]    = m;
                out_fit_minus_lg_c_lx[n] = lpos_lgvd.X();
                out_fit_minus_lg_c_ly[n] = lpos_lgvd.Y();
              }
            } else if (l == 2) {
              if (t == 0) {
                out_plus_lg_b_mid[n]    = m;
                out_fit_plus_lg_b_lx[n] = lpos_lgvd.X();
                out_fit_plus_lg_b_ly[n] = lpos_lgvd.Y();
              } else {
                out_minus_lg_b_mid[n]    = m;
                out_fit_minus_lg_b_lx[n] = lpos_lgvd.X();
                out_fit_minus_lg_b_ly[n] = lpos_lgvd.Y();
              }
            } else {
              if (t == 0) {
                out_plus_lg_a_mid[n]    = m;
                out_fit_plus_lg_a_lx[n] = lpos_lgvd.X();
                out_fit_plus_lg_a_ly[n] = lpos_lgvd.Y();
              } else {
                out_minus_lg_a_mid[n]    = m;
                out_fit_minus_lg_a_lx[n] = lpos_lgvd.X();
                out_fit_minus_lg_a_ly[n] = lpos_lgvd.Y();
              }
            }
          }
          nstps = nstps_tmp;
  //        r = gpos.Mag();
        }
      }
    }
  }
  return;
}

int track_analyzer_220715::BestTargetID(int n) {
  out_fit_parent_good_tgt_id_set[n] = 0;
  array<TVector3, kNumTgts> tgt_poss;
  tgt_poss[0].SetXYZ(out_fit_parent_tgt_minus_x[n], out_fit_parent_tgt_minus_y[n], 0.);
  tgt_poss[1].SetXYZ(out_fit_parent_tgt_zero_x[n],  out_fit_parent_tgt_zero_y[n],  0.);
  tgt_poss[2].SetXYZ(out_fit_parent_tgt_plus_x[n],  out_fit_parent_tgt_plus_y[n],  0.);
//  array<double, kNumTgts> r = {pow(out_fit_parent_tgt_minus_x[n] * out_fit_parent_tgt_minus_x[n] + out_fit_parent_tgt_minus_y[n] * out_fit_parent_tgt_minus_y[n], 0.5),
//                               pow(out_fit_parent_tgt_zero_x[n]  * out_fit_parent_tgt_zero_x[n]  + out_fit_parent_tgt_zero_y[n]  * out_fit_parent_tgt_zero_y[n], 0.5),
//                               pow(out_fit_parent_tgt_plus_x[n]  * out_fit_parent_tgt_plus_x[n]  + out_fit_parent_tgt_plus_y[n]  * out_fit_parent_tgt_plus_y[n], 0.5)};
  int best_id = 0;
  double best_r = 10000.;
  for (int i = 0; i < kNumTgts; ++i) {
    if (out_vtx_z[n] < kTargetZ[i] - kMaxDiffTgtAndVtx) {
      continue;
    }
    auto r = tgt_poss[i].Perp();
    if (i == 0) {
      out_fit_parent_tgt_minus_flight_path[n] = r;
    } else if (i == 1) {
      out_fit_parent_tgt_zero_flight_path[n]  = r;
    } else if (i == 2) {
      out_fit_parent_tgt_plus_flight_path[n]  = r;
    }
    if (r < best_r) {
      best_id = i;
      best_r  = r;
    }
    if (fabs(tgt_poss[i].X()) < kMaxGoodTgtXDiff && fabs(tgt_poss[i].Y()) < kMaxGoodTgtYDiff) {
      out_fit_parent_good_tgt_ids[n].emplace_back(i);
      out_fit_parent_good_tgt_id_set[n] += pow(2, i);
    }
  }
  return best_id;
}

void track_analyzer_220715::ParentInfo(int n) {
  out_fit_parent_mom_x[n]       = out_plus_mom_x[n] + out_minus_mom_x[n];
  out_fit_parent_mom_y[n]       = out_plus_mom_y[n] + out_minus_mom_y[n];
  out_fit_parent_mom_z[n]       = out_plus_mom_z[n] + out_minus_mom_z[n];
  out_fit_parent_tgt_minus_x[n] = out_vtx_x[n] + out_fit_parent_mom_x[n] * (kTargetZ[0] - out_vtx_z[n]) / out_fit_parent_mom_z[n];
  out_fit_parent_tgt_minus_y[n] = out_vtx_y[n] + out_fit_parent_mom_y[n] * (kTargetZ[0] - out_vtx_z[n]) / out_fit_parent_mom_z[n];
  out_fit_parent_tgt_zero_x[n]  = out_vtx_x[n] + out_fit_parent_mom_x[n] * (kTargetZ[1] - out_vtx_z[n]) / out_fit_parent_mom_z[n];
  out_fit_parent_tgt_zero_y[n]  = out_vtx_y[n] + out_fit_parent_mom_y[n] * (kTargetZ[1] - out_vtx_z[n]) / out_fit_parent_mom_z[n];
  out_fit_parent_tgt_plus_x[n]  = out_vtx_x[n] + out_fit_parent_mom_x[n] * (kTargetZ[2] - out_vtx_z[n]) / out_fit_parent_mom_z[n];
  out_fit_parent_tgt_plus_y[n]  = out_vtx_y[n] + out_fit_parent_mom_y[n] * (kTargetZ[2] - out_vtx_z[n]) / out_fit_parent_mom_z[n];
  out_fit_parent_best_tgt_id[n] = BestTargetID(n);
  return;
}

void track_analyzer_220715::AssociatedHBDAndLG(int n) {
  for (int t = 0; t < 2; ++t) {
    auto i = good_pair_indexs[n][t];
    int mid;
    TVector3 track_pos;
    if (t == 0) {
      mid = out_plus_hbd_mid[n];
      track_pos.SetXYZ(out_fit_plus_hbd_lx[n], out_fit_plus_hbd_ly[n], 0.);
    } else {
      mid = out_minus_hbd_mid[n];
      track_pos.SetXYZ(out_fit_minus_hbd_lx[n], out_fit_minus_hbd_ly[n], 0.);
    }
    vector<int> tmp_hbd_indexs;
    HasAssociatedHBD(mid, track_pos, &tmp_hbd_indexs);
    auto n_hbds = tmp_hbd_indexs.size();
    if (t == 0) {
      out_proj_plus_n_hbds[n] = n_hbds;
      out_proj_plus_hbd_id[n].resize(n_hbds);
      out_proj_plus_hbd_lx[n].resize(n_hbds);
      out_proj_plus_hbd_ly[n].resize(n_hbds);
      out_proj_plus_hbd_resx[n].resize(n_hbds);
      out_proj_plus_hbd_resy[n].resize(n_hbds);
      out_proj_plus_hbd_adc[n].resize(n_hbds);
      out_proj_plus_hbd_size[n].resize(n_hbds);
      out_proj_plus_hbd_eprob[n].resize(n_hbds);
      for (int j = 0; j < n_hbds; ++j) {
        auto index = tmp_hbd_indexs[j];
        out_proj_plus_hbd_id[n][j]    = hbd_cluster_id->at(index);
        out_proj_plus_hbd_lx[n][j]    = hbd_cluster_x->at(index);
        out_proj_plus_hbd_ly[n][j]    = hbd_cluster_y->at(index);
        out_proj_plus_hbd_resx[n][j]  = hbd_cluster_x->at(index) - track_pos.X();
        out_proj_plus_hbd_resy[n][j]  = hbd_cluster_y->at(index) - track_pos.Y();
        out_proj_plus_hbd_adc[n][j]   = hbd_cluster_adc->at(index);
        out_proj_plus_hbd_size[n][j]  = hbd_cluster_size->at(index);
        out_proj_plus_hbd_eprob[n][j] = hbd_cluster_eprob->at(index);
      }
    } else {
      out_proj_minus_n_hbds[n] = n_hbds;
      out_proj_minus_hbd_id[n].resize(n_hbds);
      out_proj_minus_hbd_lx[n].resize(n_hbds);
      out_proj_minus_hbd_ly[n].resize(n_hbds);
      out_proj_minus_hbd_resx[n].resize(n_hbds);
      out_proj_minus_hbd_resy[n].resize(n_hbds);
      out_proj_minus_hbd_adc[n].resize(n_hbds);
      out_proj_minus_hbd_size[n].resize(n_hbds);
      out_proj_minus_hbd_eprob[n].resize(n_hbds);
      for (int j = 0; j < n_hbds; ++j) {
        auto index = tmp_hbd_indexs[j];
        out_proj_minus_hbd_id[n][j]    = hbd_cluster_id->at(index);
        out_proj_minus_hbd_lx[n][j]    = hbd_cluster_x->at(index);
        out_proj_minus_hbd_ly[n][j]    = hbd_cluster_y->at(index);
        out_proj_minus_hbd_resx[n][j]  = hbd_cluster_x->at(index) - track_pos.X();
        out_proj_minus_hbd_resy[n][j]  = hbd_cluster_y->at(index) - track_pos.Y();
        out_proj_minus_hbd_adc[n][j]   = hbd_cluster_adc->at(index);
        out_proj_minus_hbd_size[n][j]  = hbd_cluster_size->at(index);
        out_proj_minus_hbd_eprob[n][j] = hbd_cluster_eprob->at(index);
      }
    }
  }
  return;
}

void track_analyzer_220715::FillCommonBranches() {
  for (int i = 0; i < out_n_pairs; ++i) {
    auto i0 = good_pair_indexs[i][0];
    auto i1 = good_pair_indexs[i][1];
    out_plus_track_id[i]         = track_id->at(i0);
    out_hit_plus_ssd_id[i]       = rk_hit_ssd_id->at(i0);
    out_hit_plus_ssd_lx[i]       = rk_hit_ssd_x->at(i0);
    out_hit_plus_ssd_t[i]        = rk_hit_ssd_t->at(i0);
    out_hit_plus_ssd_adc[i]      = rk_hit_ssd_adc->at(i0);
//    out_hit_plus_ssd_size[i] = rk_hit_ssd_
    out_hit_plus_gtr100_xid[i]   = rk_hit_gtr100_xid->at(i0);
    out_hit_plus_gtr100_yid[i]   = rk_hit_gtr100_yid->at(i0);
    out_hit_plus_gtr100_lx[i]    = rk_hit_gtr100_tx2->at(i0);
    out_hit_plus_gtr100_ly[i]    = rk_hit_gtr100_ty->at(i0);
    out_hit_plus_gtr100_xt[i]    = rk_hit_gtr100_xt2->at(i0);
    out_hit_plus_gtr100_yt[i]    = rk_hit_gtr100_yt2->at(i0);
    out_hit_plus_gtr100_xadc[i]  = rk_hit_gtr100_xadc->at(i0);
    out_hit_plus_gtr100_yadc[i]  = rk_hit_gtr100_yadc->at(i0);
//    out_hit_plus_gtr100_xsize[i] = rk_hit_gtr100_
    out_hit_plus_gtr200_xid[i]   = rk_hit_gtr200_xid->at(i0);
    out_hit_plus_gtr200_yid[i]   = rk_hit_gtr200_yid->at(i0);
    out_hit_plus_gtr200_lx[i]    = rk_hit_gtr200_tx2->at(i0);
    out_hit_plus_gtr200_ly[i]    = rk_hit_gtr200_ty->at(i0);
    out_hit_plus_gtr200_xt[i]    = rk_hit_gtr200_xt2->at(i0);
    out_hit_plus_gtr200_yt[i]    = rk_hit_gtr200_yt2->at(i0);
    out_hit_plus_gtr200_xadc[i]  = rk_hit_gtr200_xadc->at(i0);
    out_hit_plus_gtr200_yadc[i]  = rk_hit_gtr200_yadc->at(i0);
    out_hit_plus_gtr300_xid[i]   = rk_hit_gtr300_xid->at(i0);
    out_hit_plus_gtr300_yid[i]   = rk_hit_gtr300_yid->at(i0);
    out_hit_plus_gtr300_lx[i]    = rk_hit_gtr300_tx2->at(i0);
    out_hit_plus_gtr300_ly[i]    = rk_hit_gtr300_ty->at(i0);
    out_hit_plus_gtr300_xt[i]    = rk_hit_gtr300_xt2->at(i0);
    out_hit_plus_gtr300_yt[i]    = rk_hit_gtr300_yt2->at(i0);
    out_hit_plus_gtr300_xadc[i]  = rk_hit_gtr300_xadc->at(i0);
    out_hit_plus_gtr300_yadc[i]  = rk_hit_gtr300_yadc->at(i0);
    out_minus_track_id[i]        = track_id->at(i1);
    out_hit_minus_ssd_id[i]      = rk_hit_ssd_id->at(i1);
    out_hit_minus_ssd_lx[i]      = rk_hit_ssd_x->at(i1);
    out_hit_minus_ssd_t[i]       = rk_hit_ssd_t->at(i1);
    out_hit_minus_ssd_adc[i]     = rk_hit_ssd_adc->at(i1);
//    out_hit_minus_ssd_size[i] = rk_hit_ssd_
    out_hit_minus_gtr100_xid[i]  = rk_hit_gtr100_xid->at(i1);
    out_hit_minus_gtr100_yid[i]  = rk_hit_gtr100_yid->at(i1);
    out_hit_minus_gtr100_lx[i]   = rk_hit_gtr100_tx2->at(i1);
    out_hit_minus_gtr100_ly[i]   = rk_hit_gtr100_ty->at(i1);
    out_hit_minus_gtr100_xt[i]   = rk_hit_gtr100_xt2->at(i1);
    out_hit_minus_gtr100_yt[i]   = rk_hit_gtr100_yt2->at(i1);
    out_hit_minus_gtr100_xadc[i] = rk_hit_gtr100_xadc->at(i1);
    out_hit_minus_gtr100_yadc[i] = rk_hit_gtr100_yadc->at(i1);
//    out_hit_minus_gtr100_xsize[i] = rk_hit_gtr100_
    out_hit_minus_gtr200_xid[i]  = rk_hit_gtr200_xid->at(i1);
    out_hit_minus_gtr200_yid[i]  = rk_hit_gtr200_yid->at(i1);
    out_hit_minus_gtr200_lx[i]   = rk_hit_gtr200_tx2->at(i1);
    out_hit_minus_gtr200_ly[i]   = rk_hit_gtr200_ty->at(i1);
    out_hit_minus_gtr200_xt[i]   = rk_hit_gtr200_xt2->at(i1);
    out_hit_minus_gtr200_yt[i]   = rk_hit_gtr200_yt2->at(i1);
    out_hit_minus_gtr200_xadc[i] = rk_hit_gtr200_xadc->at(i1);
    out_hit_minus_gtr200_yadc[i] = rk_hit_gtr200_yadc->at(i1);
    out_hit_minus_gtr300_xid[i]  = rk_hit_gtr300_xid->at(i1);
    out_hit_minus_gtr300_yid[i]  = rk_hit_gtr300_yid->at(i1);
    out_hit_minus_gtr300_lx[i]   = rk_hit_gtr300_tx2->at(i1);
    out_hit_minus_gtr300_ly[i]   = rk_hit_gtr300_ty->at(i1);
    out_hit_minus_gtr300_xt[i]   = rk_hit_gtr300_xt2->at(i1);
    out_hit_minus_gtr300_yt[i]   = rk_hit_gtr300_yt2->at(i1);
    out_hit_minus_gtr300_xadc[i] = rk_hit_gtr300_xadc->at(i1);
    out_hit_minus_gtr300_yadc[i] = rk_hit_gtr300_yadc->at(i1);
    out_dir_id[i]                = DirID(i0, i1);
    out_plus_ssd_mid[i]          = rk_fit_ssd_mid->at(i0);
    out_plus_gtr100_mid[i]       = rk_fit_gtr100_mid->at(i0);
    out_plus_gtr200_mid[i]       = rk_fit_gtr200_mid->at(i0);
    out_plus_gtr300_mid[i]       = rk_fit_gtr300_mid->at(i0);
    out_minus_ssd_mid[i]         = rk_fit_ssd_mid->at(i1);
    out_minus_gtr100_mid[i]      = rk_fit_gtr100_mid->at(i1);
    out_minus_gtr200_mid[i]      = rk_fit_gtr200_mid->at(i1);
    out_minus_gtr300_mid[i]      = rk_fit_gtr300_mid->at(i1);
    if (kAnalyzeFlag == kAnalyzePairFit) {
      ProjectionHBDAndLG(i);
    } else if (kAnalyzeFlag == kAnalyzeNearestPoint) {
      out_plus_hbd_mid[i]          = rk_fit_hbd_mid->at(i0);
      out_plus_lg_c_mid[i]         = rk_fit_lg_c_mid->at(i0);
      out_plus_lg_b_mid[i]         = rk_fit_lg_b_mid->at(i0);
      out_plus_lg_a_mid[i]         = rk_fit_lg_a_mid->at(i0);
      out_minus_hbd_mid[i]         = rk_fit_hbd_mid->at(i1);
      out_minus_lg_c_mid[i]        = rk_fit_lg_c_mid->at(i1);
      out_minus_lg_b_mid[i]        = rk_fit_lg_b_mid->at(i1);
      out_minus_lg_a_mid[i]        = rk_fit_lg_a_mid->at(i1);
      out_fit_plus_hbd_lx[i]       = rk_fit_hbd_x->at(i0);
      out_fit_plus_hbd_ly[i]       = rk_fit_hbd_y->at(i0);
      out_fit_plus_lg_c_lx[i]      = rk_fit_lg_c_x->at(i0);
      out_fit_plus_lg_c_ly[i]      = rk_fit_lg_c_y->at(i0);
      out_fit_plus_lg_b_lx[i]      = rk_fit_lg_b_x->at(i0);
      out_fit_plus_lg_b_ly[i]      = rk_fit_lg_b_y->at(i0);
      out_fit_plus_lg_a_lx[i]      = rk_fit_lg_a_x->at(i0);
      out_fit_plus_lg_a_ly[i]      = rk_fit_lg_a_y->at(i0);
      out_fit_plus_tgt_minus_x[i]  = rk_proj_tgt0_gx->at(i0);
      out_fit_plus_tgt_minus_y[i]  = rk_proj_tgt0_gy->at(i0);
      out_fit_plus_tgt_zero_x[i]   = rk_proj_tgt1_gx->at(i0);
      out_fit_plus_tgt_zero_y[i]   = rk_proj_tgt1_gy->at(i0);
      out_fit_plus_tgt_plus_x[i]   = rk_proj_tgt2_gx->at(i0);
      out_fit_plus_tgt_plus_y[i]   = rk_proj_tgt2_gy->at(i0);
      out_fit_minus_hbd_lx[i]      = rk_fit_hbd_x->at(i1);
      out_fit_minus_hbd_ly[i]      = rk_fit_hbd_y->at(i1);
      out_fit_minus_lg_c_lx[i]     = rk_fit_lg_c_x->at(i1);
      out_fit_minus_lg_c_ly[i]     = rk_fit_lg_c_y->at(i1);
      out_fit_minus_lg_b_lx[i]     = rk_fit_lg_b_x->at(i1);
      out_fit_minus_lg_b_ly[i]     = rk_fit_lg_b_y->at(i1);
      out_fit_minus_lg_a_lx[i]     = rk_fit_lg_a_x->at(i1);
      out_fit_minus_lg_a_ly[i]     = rk_fit_lg_a_y->at(i1);
      out_fit_minus_tgt_minus_x[i] = rk_proj_tgt0_gx->at(i1);
      out_fit_minus_tgt_minus_y[i] = rk_proj_tgt0_gy->at(i1);
      out_fit_minus_tgt_zero_x[i]  = rk_proj_tgt1_gx->at(i1);
      out_fit_minus_tgt_zero_y[i]  = rk_proj_tgt1_gy->at(i1);
      out_fit_minus_tgt_plus_x[i]  = rk_proj_tgt2_gx->at(i1);
      out_fit_minus_tgt_plus_y[i]  = rk_proj_tgt2_gy->at(i1);
    }
    out_res_plus_ssd_lx[i]     = out_hit_plus_ssd_lx[i]     - out_fit_plus_ssd_lx[i];
    out_res_plus_gtr100_lx[i]  = out_hit_plus_gtr100_lx[i]  - out_fit_plus_gtr100_lx[i];
    out_res_plus_gtr100_ly[i]  = out_hit_plus_gtr100_ly[i]  - out_fit_plus_gtr100_ly[i];
    out_res_plus_gtr200_lx[i]  = out_hit_plus_gtr200_lx[i]  - out_fit_plus_gtr200_lx[i];
    out_res_plus_gtr200_ly[i]  = out_hit_plus_gtr200_ly[i]  - out_fit_plus_gtr200_ly[i];
    out_res_plus_gtr300_lx[i]  = out_hit_plus_gtr300_lx[i]  - out_fit_plus_gtr300_lx[i];
    out_res_plus_gtr300_ly[i]  = out_hit_plus_gtr300_ly[i]  - out_fit_plus_gtr300_ly[i];
    out_res_minus_ssd_lx[i]    = out_hit_minus_ssd_lx[i]    - out_fit_minus_ssd_lx[i];
    out_res_minus_gtr100_lx[i] = out_hit_minus_gtr100_lx[i] - out_fit_minus_gtr100_lx[i];
    out_res_minus_gtr100_ly[i] = out_hit_minus_gtr100_ly[i] - out_fit_minus_gtr100_ly[i];
    out_res_minus_gtr200_lx[i] = out_hit_minus_gtr200_lx[i] - out_fit_minus_gtr200_lx[i];
    out_res_minus_gtr200_ly[i] = out_hit_minus_gtr200_ly[i] - out_fit_minus_gtr200_ly[i];
    out_res_minus_gtr300_lx[i] = out_hit_minus_gtr300_lx[i] - out_fit_minus_gtr300_lx[i];
    out_res_minus_gtr300_ly[i] = out_hit_minus_gtr300_ly[i] - out_fit_minus_gtr300_ly[i];
    ParentInfo(i);
    if (kAnalyzeFlag == kAnalyzePairFit) {
      AssociatedHBDAndLG(i);
    } else if (kAnalyzeFlag == kAnalyzeNearestPoint) {
//      out_proj_plus_n_hbds[i] = rk_proj_n_hbd->at(i0);
//      copy(rk_proj_hbd_id->at(i0).begin(),    rk_proj_hbd_id->at(i0).end(),    back_inserter(out_proj_plus_hbd_id[i]));
//      copy(rk_proj_hbd_x->at(i0).begin(),     rk_proj_hbd_x->at(i0).end(),     back_inserter(out_proj_plus_hbd_lx[i]));
//      copy(rk_proj_hbd_y->at(i0).begin(),     rk_proj_hbd_y->at(i0).end(),     back_inserter(out_proj_plus_hbd_ly[i]));
//      copy(rk_proj_hbd_adc->at(i0).begin(),   rk_proj_hbd_adc->at(i0).end(),   back_inserter(out_proj_plus_hbd_adc[i]));
//      copy(rk_proj_hbd_size->at(i0).begin(),  rk_proj_hbd_size->at(i0).end(),  back_inserter(out_proj_plus_hbd_size[i]));
//      copy(rk_proj_hbd_eprob->at(i0).begin(), rk_proj_hbd_eprob->at(i0).end(), back_inserter(out_proj_plus_hbd_eprob[i]));
//      out_proj_minus_n_hbds[i] = rk_proj_n_hbd->at(i1);
//      copy(rk_proj_hbd_id->at(i1).begin(),    rk_proj_hbd_id->at(i1).end(),    back_inserter(out_proj_minus_hbd_id[i]));
//      copy(rk_proj_hbd_x->at(i1).begin(),     rk_proj_hbd_x->at(i1).end(),     back_inserter(out_proj_minus_hbd_lx[i]));
//      copy(rk_proj_hbd_y->at(i1).begin(),     rk_proj_hbd_y->at(i1).end(),     back_inserter(out_proj_minus_hbd_ly[i]));
//      copy(rk_proj_hbd_adc->at(i1).begin(),   rk_proj_hbd_adc->at(i1).end(),   back_inserter(out_proj_minus_hbd_adc[i]));
//      copy(rk_proj_hbd_size->at(i1).begin(),  rk_proj_hbd_size->at(i1).end(),  back_inserter(out_proj_minus_hbd_size[i]));
//      copy(rk_proj_hbd_eprob->at(i1).begin(), rk_proj_hbd_eprob->at(i1).end(), back_inserter(out_proj_minus_hbd_eprob[i]));
//      out_proj_plus_hbd_resx[i].resize(out_proj_plus_n_hbds[i]);
//      out_proj_plus_hbd_resy[i].resize(out_proj_plus_n_hbds[i]);
//      for (int j = 0; j < out_proj_plus_n_hbds[i]; ++j) {
//        out_proj_plus_hbd_resx[i][j] = out_proj_plus_hbd_lx[i][j] - out_fit_plus_hbd_lx[i];
//        out_proj_plus_hbd_resy[i][j] = out_proj_plus_hbd_ly[i][j] - out_fit_plus_hbd_ly[i];
//      }
//      out_proj_minus_hbd_resx[i].resize(out_proj_minus_n_hbds[i]);
//      out_proj_minus_hbd_resy[i].resize(out_proj_minus_n_hbds[i]);
//      for (int j = 0; j < out_proj_minus_n_hbds[i]; ++j) {
//        out_proj_minus_hbd_resx[i][j] = out_proj_minus_hbd_lx[i][j] - out_fit_minus_hbd_lx[i];
//        out_proj_minus_hbd_resy[i][j] = out_proj_minus_hbd_ly[i][j] - out_fit_minus_hbd_ly[i];
//      }
      auto n_hbds = associated_hbd_indexs[i0].size();
      out_proj_plus_n_hbds[i] = n_hbds;
      out_proj_plus_hbd_id[i].resize(n_hbds);
      out_proj_plus_hbd_lx[i].resize(n_hbds);
      out_proj_plus_hbd_ly[i].resize(n_hbds);
      out_proj_plus_hbd_resx[i].resize(n_hbds);
      out_proj_plus_hbd_resy[i].resize(n_hbds);
      out_proj_plus_hbd_adc[i].resize(n_hbds);
      out_proj_plus_hbd_size[i].resize(n_hbds);
      out_proj_plus_hbd_eprob[i].resize(n_hbds);
      for (int j = 0; j < n_hbds; ++j) {
        auto ii = associated_hbd_indexs[i0][j];
        out_proj_plus_hbd_id[i][j] = hbd_cluster_id->at(ii);
        out_proj_plus_hbd_lx[i][j] = hbd_cluster_x->at(ii);
        out_proj_plus_hbd_ly[i][j] = hbd_cluster_y->at(ii);
        out_proj_plus_hbd_resx[i][j] = hbd_cluster_x->at(ii) - out_fit_plus_hbd_lx[i];
        out_proj_plus_hbd_resy[i][j] = hbd_cluster_y->at(ii) - out_fit_plus_hbd_ly[i];
        out_proj_plus_hbd_adc[i][j] = hbd_cluster_adc->at(ii);
        out_proj_plus_hbd_size[i][j] = hbd_cluster_size->at(ii);
        out_proj_plus_hbd_eprob[i][j] = hbd_cluster_eprob->at(ii);
      }
      n_hbds = associated_hbd_indexs[i1].size();
      out_proj_minus_n_hbds[i] = n_hbds;
      out_proj_minus_hbd_id[i].resize(n_hbds);
      out_proj_minus_hbd_lx[i].resize(n_hbds);
      out_proj_minus_hbd_ly[i].resize(n_hbds);
      out_proj_minus_hbd_resx[i].resize(n_hbds);
      out_proj_minus_hbd_resy[i].resize(n_hbds);
      out_proj_minus_hbd_adc[i].resize(n_hbds);
      out_proj_minus_hbd_size[i].resize(n_hbds);
      out_proj_minus_hbd_eprob[i].resize(n_hbds);
      for (int j = 0; j < n_hbds; ++j) {
        auto ii = associated_hbd_indexs[i1][j];
        out_proj_minus_hbd_id[i][j] = hbd_cluster_id->at(ii);
        out_proj_minus_hbd_lx[i][j] = hbd_cluster_x->at(ii);
        out_proj_minus_hbd_ly[i][j] = hbd_cluster_y->at(ii);
        out_proj_minus_hbd_resx[i][j] = hbd_cluster_x->at(ii) - out_fit_minus_hbd_lx[i];
        out_proj_minus_hbd_resy[i][j] = hbd_cluster_y->at(ii) - out_fit_minus_hbd_ly[i];
        out_proj_minus_hbd_adc[i][j] = hbd_cluster_adc->at(ii);
        out_proj_minus_hbd_size[i][j] = hbd_cluster_size->at(ii);
        out_proj_minus_hbd_eprob[i][j] = hbd_cluster_eprob->at(ii);
      }
    }
  }
  return;
}

void track_analyzer_220715::Analyze() {
cout << "Number of pairs: " << good_pair_indexs.size() << endl;
  if (kAnalyzeFlag == kAnalyzePairFit) {
    for (int i = 0; i < good_pair_indexs.size(); ++i) {
      PairFit(i);
    }
  } else if (kAnalyzeFlag == kAnalyzeNearestPoint) {
    for (int i = 0; i < good_pair_indexs.size(); ++i) {
      NearestPoint(i);
    }
  }
  FillCommonBranches();
  return;
}

void track_analyzer_220715::Loop(const TString& out_name) {
//   In a ROOT session, you can do:
//      root> .L track_analyzer_220715.C
//      root> track_analyzer_220715 t
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
  auto file = TFile(out_name, "recreate");
  auto tree = TTree("tree", "tree");
  MakeBranches(&tree);
  for (Long64_t jentry = 0; jentry < nentries; ++jentry) {
    cout << jentry << " / " << nentries << endl;
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
//    if (Cut(ientry) < 0) continue;
    for (auto& ids : used_cluster_ids) {
      ids.clear();
    }
    SetHBDs();
    SetTracks();
    SetPairs();
    ClearAndResizeBranches();
    Analyze();
    tree.Fill();
  }
  file.Write();
}
