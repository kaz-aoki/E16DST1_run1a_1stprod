#define E16ANA_TrackAnalyzerFromTree_cxx
#include "E16ANA_TrackAnalyzerFromTree.hh"

#include <array>
#include <vector>

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "E16ANA_TrackAnalyzerFromTreeParameter.hh"
#include "E16ANA_StepTrack.hh"

namespace track_const = E16ANA_TrackConstant;
namespace st_param    = E16ANA_TrackAnalyzerFromTreeSingleTrackParameter;
namespace pt_param    = E16ANA_TrackAnalyzerFromTreePairTrackParameter;

void E16ANA_TrackAnalyzerFromTree::ClearOutBranch() {
  out_run_id = run_id;
  out_event_id = event_id;
  out_n_tracks = n_cands;
  out_n_pairs = 0;
  out_n_selected_pairs = 0;
  out_is_selected.clear();
  out_minus_track_id.clear();
  out_plus_track_id.clear();
  out_chi_square.clear();
  out_vtx_gx.clear();
  out_vtx_gy.clear();
  out_vtx_gz.clear();
  out_minus_mom_gx.clear();
  out_minus_mom_gy.clear();
  out_minus_mom_gz.clear();
  out_plus_mom_gx.clear();
  out_plus_mom_gy.clear();
  out_plus_mom_gz.clear();
  out_minus_ssd_mid.clear();
  out_minus_gtr100_mid.clear();
  out_minus_gtr200_mid.clear();
  out_minus_gtr300_mid.clear();
  out_plus_ssd_mid.clear();
  out_plus_gtr100_mid.clear();
  out_plus_gtr200_mid.clear();
  out_plus_gtr300_mid.clear();
  out_minus_ssd_hit_pos_gx.clear();
  out_minus_ssd_hit_pos_gy.clear();
  out_minus_ssd_hit_pos_gz.clear();
  out_minus_gtr100_hit_pos_gx.clear();
  out_minus_gtr100_hit_pos_gy.clear();
  out_minus_gtr100_hit_pos_gz.clear();
  out_minus_gtr200_hit_pos_gx.clear();
  out_minus_gtr200_hit_pos_gy.clear();
  out_minus_gtr200_hit_pos_gz.clear();
  out_minus_gtr300_hit_pos_gx.clear();
  out_minus_gtr300_hit_pos_gy.clear();
  out_minus_gtr300_hit_pos_gz.clear();
  out_plus_ssd_hit_pos_gx.clear();
  out_plus_ssd_hit_pos_gy.clear();
  out_plus_ssd_hit_pos_gz.clear();
  out_plus_gtr100_hit_pos_gx.clear();
  out_plus_gtr100_hit_pos_gy.clear();
  out_plus_gtr100_hit_pos_gz.clear();
  out_plus_gtr200_hit_pos_gx.clear();
  out_plus_gtr200_hit_pos_gy.clear();
  out_plus_gtr200_hit_pos_gz.clear();
  out_plus_gtr300_hit_pos_gx.clear();
  out_plus_gtr300_hit_pos_gy.clear();
  out_plus_gtr300_hit_pos_gz.clear();
  out_minus_ssd_fit_pos_gx.clear();
  out_minus_ssd_fit_pos_gy.clear();
  out_minus_ssd_fit_pos_gz.clear();
  out_minus_gtr100_fit_pos_gx.clear();
  out_minus_gtr100_fit_pos_gy.clear();
  out_minus_gtr100_fit_pos_gz.clear();
  out_minus_gtr200_fit_pos_gx.clear();
  out_minus_gtr200_fit_pos_gy.clear();
  out_minus_gtr200_fit_pos_gz.clear();
  out_minus_gtr300_fit_pos_gx.clear();
  out_minus_gtr300_fit_pos_gy.clear();
  out_minus_gtr300_fit_pos_gz.clear();
  out_plus_ssd_fit_pos_gx.clear();
  out_plus_ssd_fit_pos_gy.clear();
  out_plus_ssd_fit_pos_gz.clear();
  out_plus_gtr100_fit_pos_gx.clear();
  out_plus_gtr100_fit_pos_gy.clear();
  out_plus_gtr100_fit_pos_gz.clear();
  out_plus_gtr200_fit_pos_gx.clear();
  out_plus_gtr200_fit_pos_gy.clear();
  out_plus_gtr200_fit_pos_gz.clear();
  out_plus_gtr300_fit_pos_gx.clear();
  out_plus_gtr300_fit_pos_gy.clear();
  out_plus_gtr300_fit_pos_gz.clear();
  out_minus_ssd_fit_mom_gx.clear();
  out_minus_ssd_fit_mom_gy.clear();
  out_minus_ssd_fit_mom_gz.clear();
  out_minus_gtr100_fit_mom_gx.clear();
  out_minus_gtr100_fit_mom_gy.clear();
  out_minus_gtr100_fit_mom_gz.clear();
  out_minus_gtr200_fit_mom_gx.clear();
  out_minus_gtr200_fit_mom_gy.clear();
  out_minus_gtr200_fit_mom_gz.clear();
  out_minus_gtr300_fit_mom_gx.clear();
  out_minus_gtr300_fit_mom_gy.clear();
  out_minus_gtr300_fit_mom_gz.clear();
  out_plus_ssd_fit_mom_gx.clear();
  out_plus_ssd_fit_mom_gy.clear();
  out_plus_ssd_fit_mom_gz.clear();
  out_plus_gtr100_fit_mom_gx.clear();
  out_plus_gtr100_fit_mom_gy.clear();
  out_plus_gtr100_fit_mom_gz.clear();
  out_plus_gtr200_fit_mom_gx.clear();
  out_plus_gtr200_fit_mom_gy.clear();
  out_plus_gtr200_fit_mom_gz.clear();
  out_plus_gtr300_fit_mom_gx.clear();
  out_plus_gtr300_fit_mom_gy.clear();
  out_plus_gtr300_fit_mom_gz.clear();
  out_minus_ssd_fit_res_x.clear();
  out_minus_ssd_fit_res_y.clear();
  out_minus_ssd_fit_res_z.clear();
  out_minus_gtr100_fit_res_x.clear();
  out_minus_gtr100_fit_res_y.clear();
  out_minus_gtr100_fit_res_z.clear();
  out_minus_gtr200_fit_res_x.clear();
  out_minus_gtr200_fit_res_y.clear();
  out_minus_gtr200_fit_res_z.clear();
  out_minus_gtr300_fit_res_x.clear();
  out_minus_gtr300_fit_res_y.clear();
  out_minus_gtr300_fit_res_z.clear();
  out_plus_ssd_fit_res_x.clear();
  out_plus_ssd_fit_res_y.clear();
  out_plus_ssd_fit_res_z.clear();
  out_plus_gtr100_fit_res_x.clear();
  out_plus_gtr100_fit_res_y.clear();
  out_plus_gtr100_fit_res_z.clear();
  out_plus_gtr200_fit_res_x.clear();
  out_plus_gtr200_fit_res_y.clear();
  out_plus_gtr200_fit_res_z.clear();
  out_plus_gtr300_fit_res_x.clear();
  out_plus_gtr300_fit_res_y.clear();
  out_plus_gtr300_fit_res_z.clear();
  out_mass.clear();
  return;
}

bool E16ANA_TrackAnalyzerFromTree::IsGoodTrack(int track_index) {
  // write your selection criteria begin
  if (chi_square->at(track_index) > st_param::kChiSquareThreshold) {
    return false;
  }
//  if (rk_proj_hbd0_id->at(n) < 0) {
  if (rk_proj_n_hbd->at(track_index) == 0) {
    return false;
  }
//  if (rk_proj_lg0_id->at(n) < 0) {
  if (rk_proj_n_lg->at(track_index) == 0) {
    return false;
  }
  if (rk_res_ssd_x->at(track_index) > st_param::kSSDResidualThreshold) {
    return false;
  }
  if (rk_res_gtr100_x->at(track_index) > st_param::kGTR100xResidualThreshold) {
    return false;
  }
  if (rk_res_gtr100_y->at(track_index) > st_param::kGTR100yResidualThreshold) {
    return false;
  }
  if (rk_res_gtr200_x->at(track_index) > st_param::kGTR200xResidualThreshold) {
    return false;
  }
  if (rk_res_gtr200_y->at(track_index) > st_param::kGTR200yResidualThreshold) {
    return false;
  }
  if (rk_res_gtr300_x->at(track_index) > st_param::kGTR300xResidualThreshold) {
    return false;
  }
  if (rk_res_gtr300_y->at(track_index) > st_param::kGTR300yResidualThreshold) {
    return false;
  }
  bool is_near_target = false;
  double x[3] = {rk_proj_tgt0_gx->at(track_index), rk_proj_tgt1_gx->at(track_index), rk_proj_tgt2_gx->at(track_index)};
  double y[3] = {rk_proj_tgt0_gy->at(track_index), rk_proj_tgt1_gy->at(track_index), rk_proj_tgt2_gy->at(track_index)};
  for (int i = 0; i < 3; ++i) {
    if (x[i] * x[i] + y[i] * y[i] < st_param::kNearTargetSquareThreshold) {
      is_near_target = true;
    }
  }
  if (!is_near_target) {
    return false;
  }
  // write your selection criteria end
  return true;
}

void E16ANA_TrackAnalyzerFromTree::CheckUsedClusters(int track_index, std::array<std::vector<int>, track_const::kNumTrackingLayers>* used_cluster_ids,
                                                     std::vector<int>* selected_track_index) {
  int ids[7] = {rk_hit_ssd_id->at(track_index),
                rk_hit_gtr100_xid->at(track_index), rk_hit_gtr100_yid->at(track_index),
                rk_hit_gtr200_xid->at(track_index), rk_hit_gtr200_yid->at(track_index),
                rk_hit_gtr300_xid->at(track_index), rk_hit_gtr300_yid->at(track_index)};
  for (const auto& id : used_cluster_ids->at(0)) {
    if (id == ids[0]) {
      return;
    }
  }
  for (const auto& id : used_cluster_ids->at(1)) {
    if (id == ids[1] || id == ids[2]) {
      return;
    }
  }
  for (const auto& id : used_cluster_ids->at(2)) {
    if (id == ids[3] || id == ids[4]) {
      return;
    }
  }
  for (const auto& id : used_cluster_ids->at(3)) {
    if (id == ids[5] || id == ids[6]) {
      return;
    }
  }
  used_cluster_ids->at(0).emplace_back(ids[0]);
  used_cluster_ids->at(1).emplace_back(ids[1]);
  used_cluster_ids->at(1).emplace_back(ids[2]);
  used_cluster_ids->at(2).emplace_back(ids[3]);
  used_cluster_ids->at(2).emplace_back(ids[4]);
  used_cluster_ids->at(3).emplace_back(ids[5]);
  used_cluster_ids->at(3).emplace_back(ids[6]);
  selected_track_index->emplace_back(track_index);
  return;
}

void E16ANA_TrackAnalyzerFromTree::SelectTrack(int track_index, std::array<std::vector<int>, track_const::kNumTrackingLayers>* used_cluster_ids,
                                               std::vector<int>* selected_track_index) {
  if (IsGoodTrack(track_index)) {
    CheckUsedClusters(track_index, used_cluster_ids, selected_track_index);
  }
  return;
}

void E16ANA_TrackAnalyzerFromTree::SelectTracks(std::vector<int>* selected_track_index) {
  std::array<std::vector<int>, track_const::kNumTrackingLayers> used_cluster_ids;
  for (int track_index = 0; track_index < n_cands; ++track_index) {
    SelectTrack(track_index, &used_cluster_ids, selected_track_index);
  }
  return;
}

//int E16ANA_TrackAnalyzerFromTree::CalcCharge(int cand_index) {
//  double x[3] = {rk_fit_init_pos_gx->at(cand_index), rk_fit_ssd_gx->at(cand_index), rk_fit_gtr100_gx->at(cand_index)};
//  double z[3] = {rk_fit_init_pos_gz->at(cand_index), rk_fit_ssd_gz->at(cand_index), rk_fit_gtr100_gz->at(cand_index)};
//  double coef1 = (z[2] - z[0]) / (x[2] - x[0]);
//  double coef0 = -coef1 * x[0] + z[0];
//  double z_at_ssd = coef1 * x[1] + coef0;
//  int is_left;
//  if (x[1] > 0) {
//    is_left = 1;
//  } else {
//    is_left = -1;
//  }
//  if (z[1] > z_at_ssd) {
//    return is_left;
//  } else {
//    return -is_left;
//  }
//  return 0;
//}

//double E16ANA_TrackAnalyzerFromTree::SearchVertex(int minus_index, int plus_index, TVector3* minus_mom, TVector3* plus_mom) {
////  auto t_init_pos0 = TVector3(rk_fit_init_pos_gx->at(minus_index), rk_fit_init_pos_gy->at(minus_index). rk_fit_init_pos_gz->at(minus_index));
////  auto t_init_pos1 = TVector3(rk_fit_init_pos_gx->at(plus_index),  rk_fit_init_pos_gy->at(plus_index).  rk_fit_init_pos_gz->at(plus_index));
////  auto t_init_mom0 = TVector3(rk_fit_init_mom_gx->at(minus_index), rk_fit_init_mom_gy->at(minus_index). rk_fit_init_mom_gz->at(minus_index));
////  auto t_init_mom1 = TVector3(rk_fit_init_mom_gx->at(plus_index),  rk_fit_init_mom_gy->at(plus_index).  rk_fit_init_mom_gz->at(plus_index));
////  Hep3Vector init_pos0(t_init_pos0(0) * 0.1, t_init_pos0(1) * 0.1, t_init_pos0(2) * 0.1);
////  Hep3Vector init_mom0(t_init_mom0(0),       t_init_mom0(1),       t_init_mom0(2));
////  Hep3Vector init_pos1(t_init_pos1(0) * 0.1, t_init_pos1(1) * 0.1, t_init_pos1(2) * 0.1);
////  Hep3Vector init_mom1(t_init_mom1(0),       t_init_mom1(1),       t_init_mom1(2));
//  auto init_pos0 = Hep3Vector3(rk_fit_init_pos_gx->at(minus_index) * 0.1, rk_fit_init_pos_gy->at(minus_index) * 0.1, rk_fit_init_pos_gz->at(minus_index) * 0.1);
//  auto init_pos1 = Hep3Vector3(rk_fit_init_pos_gx->at(plus_index)  * 0.1, rk_fit_init_pos_gy->at(plus_index)  * 0.1, rk_fit_init_pos_gz->at(plus_index)  * 0.1);
//  auto init_mom0 = Hep3Vector3(rk_fit_init_mom_gx->at(minus_index),       rk_fit_init_mom_gy->at(minus_index),       rk_fit_init_mom_gz->at(minus_index));
//  auto init_mom1 = Hep3Vector3(rk_fit_init_mom_gx->at(plus_index),        rk_fit_init_mom_gy->at(plus_index),        rk_fit_init_mom_gz->at(plus_index));
//  E16ANA_StepTrack step_track0(bfield_map, init_pos0, init_mom0, -1, pt_param::kStepTrackStepSizeCm, pt_param::kStepTrackArraySize);
//  E16ANA_StepTrack step_track1(bfield_map, init_pos1, init_mom1,  1, pt_param::kStepTrackStepSizeCm, pt_param::kStepTrackArraySize);
//  double distance;
//  Hep3Vector cross_point;
//  Hep3Vector mom0;
//  Hep3Vector mom1;
//  auto flag = step_track0.Cross(step_track1, &distance, &cross_point, &mom0, &mom1);
////  track_pair->vtx = {cross_point.x() * 10., cross_point.y() * 10., cross_point.z() * 10.};
////  track_pair->distance = distance * 10.;
//  minus_mom = {mom0.x(), mom0.y(), mom0.z()};
//  plus_mom  = {mom1.x(), mom1.y(), mom1.z()};
//  return distance * 10.;
//}

//int E16ANA_TrackAnalyzerFromTree::SearchClusterIndex(int cluster_id, std::vector<int>& cluster_ids) {
//  for (int i = 0; i < cluster_ids.size(); ++i) {
//    if (cluster_ids[i] == cluster_id) {
//      return i;
//    }
//  }
//  E16FATAL("cannot find cluster ID : %d", cluster_id);
//  std::exit(-1);
//}

void E16ANA_TrackAnalyzerFromTree::AddTracks(const int track_index_pair[], double tgt_z) {
  pair_fitter->Clear();
  pair_fitter->SetInitialVertex(TVector3(0., 0., tgt_z), pt_param::kVertexSigma);
  pair_fitter->SetCharge(0, -1.);
  pair_fitter->SetCharge(1, 1.);
  TVector3 pair_mom;
  for (int i =0; i < 2; ++i) {
    auto tmp_mom = TVector3(rk_fit_init_mom_gx->at(track_index_pair[i]), rk_fit_init_mom_gy->at(track_index_pair[i]), rk_fit_init_mom_gz->at(track_index_pair[i]));
    pair_fitter->SetInitialMomentum(i, tmp_mom);
  }
  for (int track_index_in_pair = 0; track_index_in_pair < 2; ++track_index_in_pair) {
    auto tindex = track_index_pair[track_index_in_pair];
//    auto ssd_cid     = rk_hit_ssd_id->at(tindex);
//    auto gtr100x_cid = rk_hit_gtr100_xid->at(tindex);
//    auto gtr200x_cid = rk_hit_gtr200_xid->at(tindex);
//    auto gtr300x_cid = rk_hit_gtr300_xid->at(tindex);
//    int ssd_mid    = ssd_cluster_mid->at(SearchClusterIndex(ssd_cid, *ssd_cluster_id));
//    int gtr100_mid = gtr100x_cluster_mid->at(SearchClusterIndex(gtr100x_cid, *gtr100x_cluster_id));
//    int gtr200_mid = gtr200x_cluster_mid->at(SearchClusterIndex(gtr200x_cid, *gtr200x_cluster_id));
//    int gtr300_mid = gtr300x_cluster_mid->at(SearchClusterIndex(gtr300x_cid, *gtr300x_cluster_id));
    auto ssd_mid = rk_fit_ssd_mid->at(tindex);
    auto gtr100_mid = rk_fit_gtr100_mid->at(tindex);
    auto gtr200_mid = rk_fit_gtr200_mid->at(tindex);
    auto gtr300_mid = rk_fit_gtr300_mid->at(tindex);
    auto ssd_gpos    = TVector3(rk_hit_ssd_gx->at(tindex),    rk_hit_ssd_gy->at(tindex),    rk_hit_ssd_gz->at(tindex));
    auto gtr100_gpos = TVector3(rk_hit_gtr100_gx->at(tindex), rk_hit_gtr100_gy->at(tindex), rk_hit_gtr100_gz->at(tindex));
    auto gtr200_gpos = TVector3(rk_hit_gtr200_gx->at(tindex), rk_hit_gtr200_gy->at(tindex), rk_hit_gtr200_gz->at(tindex));
    auto gtr300_gpos = TVector3(rk_hit_gtr300_gx->at(tindex), rk_hit_gtr300_gy->at(tindex), rk_hit_gtr300_gz->at(tindex));
    pair_fitter->AddHit(track_index_in_pair, 0, geometry->SSD(track_const::ModuleID2020To2013(ssd_mid)),
                        geometry->SSD(track_const::ModuleID2020To2013(ssd_mid))->GetLPos(ssd_gpos),          pt_param::kSSDSigma);
    pair_fitter->AddHit(track_index_in_pair, 1, geometry->GTR(track_const::ModuleID2020To2013(gtr100_mid), 0),
                        geometry->GTR(track_const::ModuleID2020To2013(gtr100_mid), 0)->GetLPos(gtr100_gpos), pt_param::kGTR100Sigma);
    pair_fitter->AddHit(track_index_in_pair, 2, geometry->GTR(track_const::ModuleID2020To2013(gtr200_mid), 1),
                        geometry->GTR(track_const::ModuleID2020To2013(gtr200_mid), 1)->GetLPos(gtr200_gpos), pt_param::kGTR200Sigma);
    pair_fitter->AddHit(track_index_in_pair, 3, geometry->GTR(track_const::ModuleID2020To2013(gtr300_mid), 2),
                        geometry->GTR(track_const::ModuleID2020To2013(gtr300_mid), 2)->GetLPos(gtr300_gpos), pt_param::kGTR300Sigma);
  }
  return;
}

void E16ANA_TrackAnalyzerFromTree::FillTVector3ToDouble(TVector3 t_vector, std::vector<double>* x, std::vector<double>* y, std::vector<double>* z) {
  x->emplace_back(t_vector.X());
  y->emplace_back(t_vector.Y());
  z->emplace_back(t_vector.Z());
  return;
}

double E16ANA_TrackAnalyzerFromTree::CalcMass(TVector3 mom0, TVector3 mom1) {
  double p0 = mom0.X() * mom0.X() + mom0.Y() * mom0.Y() + mom0.Z() * mom0.Z();
  double p1 = mom1.X() * mom1.X() + mom1.Y() * mom1.Y() + mom1.Z() * mom1.Z();
  double e0 = sqrt(p0 * p0 + pt_param::kElectronMass2);
  double e1 = sqrt(p1 * p1 + pt_param::kElectronMass2);
  double p0p1 = mom0.X() * mom1.X() + mom0.Y() * mom1.Y() + mom0.Z() * mom1.Z();
  return sqrt(2. * (pt_param::kElectronMass2 + e0 * e1 - p0p1));
}

void E16ANA_TrackAnalyzerFromTree::UpdateFitResult(const int track_index_pair[]) {
  out_minus_track_id.emplace_back(track_id->at(track_index_pair[0]));
  out_plus_track_id.emplace_back(track_id->at(track_index_pair[1]));
  auto tmp_vtx       = pair_fitter->GetFitVertex();
  auto tmp_minus_mom = pair_fitter->GetFitMomentum(0);
  auto tmp_plus_mom  = pair_fitter->GetFitMomentum(1);
  FillTVector3ToDouble(tmp_vtx,       &out_vtx_gx,       &out_vtx_gy,       &out_vtx_gz);
  FillTVector3ToDouble(tmp_minus_mom, &out_minus_mom_gx, &out_minus_mom_gy, &out_minus_mom_gz);
  FillTVector3ToDouble(tmp_plus_mom,  &out_plus_mom_gx,  &out_plus_mom_gy,  &out_plus_mom_gz);
  int      mid[2][track_const::kNumTrackingLayers];
  TVector3 gpos[2][track_const::kNumTrackingLayers];
  TVector3 gmom[2][track_const::kNumTrackingLayers];
  TVector3 lres[2][track_const::kNumTrackingLayers];
  for (int track_index_in_pair = 0; track_index_in_pair < 2; ++track_index_in_pair) {
    for (int layer_index = 0; layer_index < track_const::kNumTrackingLayers; ++layer_index) {
      int hid = 0; // hit ID
      std::vector<int>      tmp_mid;
      std::vector<TVector3> tmp_lpos;
      std::vector<TVector3> tmp_lmom;
      std::vector<TVector3> tmp_lres;
      pair_fitter->GetFitLPos(track_index_in_pair,     layer_index, tmp_mid, tmp_lpos);
      pair_fitter->GetFitLMom(track_index_in_pair,     layer_index, tmp_mid, tmp_lmom);
      pair_fitter->GetFitResidual(track_index_in_pair, layer_index, tmp_mid, tmp_lres);
      mid[track_index_in_pair][layer_index]  = track_const::ModuleID2013To2020(tmp_mid[hid]);
      if (layer_index == 0) {
        gpos[track_index_in_pair][layer_index] = geometry->SSD(tmp_mid[hid])->GetGPos(tmp_lpos[hid]);
        gmom[track_index_in_pair][layer_index] = geometry->SSD(tmp_mid[hid])->GetGMom(tmp_lmom[hid]);
      } else {
        gpos[track_index_in_pair][layer_index] = geometry->GTR(tmp_mid[hid], layer_index - 1)->GetGPos(tmp_lpos[hid]);
        gmom[track_index_in_pair][layer_index] = geometry->GTR(tmp_mid[hid], layer_index - 1)->GetGMom(tmp_lpos[hid]);
      }
      lres[track_index_in_pair][layer_index] = tmp_lres[hid];
    }
  }
  out_minus_ssd_mid.emplace_back(mid[0][0]);
  out_minus_gtr100_mid.emplace_back(mid[0][1]);
  out_minus_gtr200_mid.emplace_back(mid[0][2]);
  out_minus_gtr300_mid.emplace_back(mid[0][3]);
  out_plus_ssd_mid.emplace_back(mid[1][0]);
  out_plus_gtr100_mid.emplace_back(mid[1][1]);
  out_plus_gtr200_mid.emplace_back(mid[1][2]);
  out_plus_gtr300_mid.emplace_back(mid[1][3]);
  out_minus_ssd_hit_pos_gx.emplace_back(rk_hit_ssd_gx->at(track_index_pair[0]));
  out_minus_ssd_hit_pos_gy.emplace_back(rk_hit_ssd_gy->at(track_index_pair[0]));
  out_minus_ssd_hit_pos_gz.emplace_back(rk_hit_ssd_gz->at(track_index_pair[0]));
  out_minus_gtr100_hit_pos_gx.emplace_back(rk_hit_gtr100_gx->at(track_index_pair[0]));
  out_minus_gtr100_hit_pos_gy.emplace_back(rk_hit_gtr100_gy->at(track_index_pair[0]));
  out_minus_gtr100_hit_pos_gz.emplace_back(rk_hit_gtr100_gz->at(track_index_pair[0]));
  out_minus_gtr200_hit_pos_gx.emplace_back(rk_hit_gtr200_gx->at(track_index_pair[0]));
  out_minus_gtr200_hit_pos_gy.emplace_back(rk_hit_gtr200_gy->at(track_index_pair[0]));
  out_minus_gtr200_hit_pos_gz.emplace_back(rk_hit_gtr200_gz->at(track_index_pair[0]));
  out_minus_gtr300_hit_pos_gx.emplace_back(rk_hit_gtr300_gx->at(track_index_pair[0]));
  out_minus_gtr300_hit_pos_gy.emplace_back(rk_hit_gtr300_gy->at(track_index_pair[0]));
  out_minus_gtr300_hit_pos_gz.emplace_back(rk_hit_gtr300_gz->at(track_index_pair[0]));
  out_plus_ssd_hit_pos_gx.emplace_back(rk_hit_ssd_gx->at(track_index_pair[1]));
  out_plus_ssd_hit_pos_gy.emplace_back(rk_hit_ssd_gy->at(track_index_pair[1]));
  out_plus_ssd_hit_pos_gz.emplace_back(rk_hit_ssd_gz->at(track_index_pair[1]));
  out_plus_gtr100_hit_pos_gx.emplace_back(rk_hit_gtr100_gx->at(track_index_pair[1]));
  out_plus_gtr100_hit_pos_gy.emplace_back(rk_hit_gtr100_gy->at(track_index_pair[1]));
  out_plus_gtr100_hit_pos_gz.emplace_back(rk_hit_gtr100_gz->at(track_index_pair[1]));
  out_plus_gtr200_hit_pos_gx.emplace_back(rk_hit_gtr200_gx->at(track_index_pair[1]));
  out_plus_gtr200_hit_pos_gy.emplace_back(rk_hit_gtr200_gy->at(track_index_pair[1]));
  out_plus_gtr200_hit_pos_gz.emplace_back(rk_hit_gtr200_gz->at(track_index_pair[1]));
  out_plus_gtr300_hit_pos_gx.emplace_back(rk_hit_gtr300_gx->at(track_index_pair[1]));
  out_plus_gtr300_hit_pos_gy.emplace_back(rk_hit_gtr300_gy->at(track_index_pair[1]));
  out_plus_gtr300_hit_pos_gz.emplace_back(rk_hit_gtr300_gz->at(track_index_pair[1]));
  FillTVector3ToDouble(gpos[0][0], &out_minus_ssd_fit_pos_gx,    &out_minus_ssd_fit_pos_gy,    &out_minus_ssd_fit_pos_gz);
  FillTVector3ToDouble(gpos[0][1], &out_minus_gtr100_fit_pos_gx, &out_minus_gtr100_fit_pos_gy, &out_minus_gtr100_fit_pos_gz);
  FillTVector3ToDouble(gpos[0][2], &out_minus_gtr200_fit_pos_gx, &out_minus_gtr200_fit_pos_gy, &out_minus_gtr200_fit_pos_gz);
  FillTVector3ToDouble(gpos[0][3], &out_minus_gtr300_fit_pos_gx, &out_minus_gtr300_fit_pos_gy, &out_minus_gtr300_fit_pos_gz);
  FillTVector3ToDouble(gpos[1][0], &out_plus_ssd_fit_pos_gx,     &out_plus_ssd_fit_pos_gy,     &out_plus_ssd_fit_pos_gz);
  FillTVector3ToDouble(gpos[1][1], &out_plus_gtr100_fit_pos_gx,  &out_plus_gtr100_fit_pos_gy,  &out_plus_gtr100_fit_pos_gz);
  FillTVector3ToDouble(gpos[1][2], &out_plus_gtr200_fit_pos_gx,  &out_plus_gtr200_fit_pos_gy,  &out_plus_gtr200_fit_pos_gz);
  FillTVector3ToDouble(gpos[1][3], &out_plus_gtr300_fit_pos_gx,  &out_plus_gtr300_fit_pos_gy,  &out_plus_gtr300_fit_pos_gz);
  FillTVector3ToDouble(gmom[0][0], &out_minus_ssd_fit_mom_gx,    &out_minus_ssd_fit_mom_gy,    &out_minus_ssd_fit_mom_gz);
  FillTVector3ToDouble(gmom[0][1], &out_minus_gtr100_fit_mom_gx, &out_minus_gtr100_fit_mom_gy, &out_minus_gtr100_fit_mom_gz);
  FillTVector3ToDouble(gmom[0][2], &out_minus_gtr200_fit_mom_gx, &out_minus_gtr200_fit_mom_gy, &out_minus_gtr200_fit_mom_gz);
  FillTVector3ToDouble(gmom[0][3], &out_minus_gtr300_fit_mom_gx, &out_minus_gtr300_fit_mom_gy, &out_minus_gtr300_fit_mom_gz);
  FillTVector3ToDouble(gmom[1][0], &out_plus_ssd_fit_mom_gx,     &out_plus_ssd_fit_mom_gy,     &out_plus_ssd_fit_mom_gz);
  FillTVector3ToDouble(gmom[1][1], &out_plus_gtr100_fit_mom_gx,  &out_plus_gtr100_fit_mom_gy,  &out_plus_gtr100_fit_mom_gz);
  FillTVector3ToDouble(gmom[1][2], &out_plus_gtr200_fit_mom_gx,  &out_plus_gtr200_fit_mom_gy,  &out_plus_gtr200_fit_mom_gz);
  FillTVector3ToDouble(gmom[1][3], &out_plus_gtr300_fit_mom_gx,  &out_plus_gtr300_fit_mom_gy,  &out_plus_gtr300_fit_mom_gz);
  FillTVector3ToDouble(lres[0][0], &out_minus_ssd_fit_res_x,     &out_minus_ssd_fit_res_y,     &out_minus_ssd_fit_res_z);
  FillTVector3ToDouble(lres[0][1], &out_minus_gtr100_fit_res_x,  &out_minus_gtr100_fit_res_y,  &out_minus_gtr100_fit_res_z);
  FillTVector3ToDouble(lres[0][2], &out_minus_gtr200_fit_res_x,  &out_minus_gtr200_fit_res_y,  &out_minus_gtr200_fit_res_z);
  FillTVector3ToDouble(lres[0][3], &out_minus_gtr300_fit_res_x,  &out_minus_gtr300_fit_res_y,  &out_minus_gtr300_fit_res_z);
  FillTVector3ToDouble(lres[1][0], &out_plus_ssd_fit_res_x,      &out_plus_ssd_fit_res_y,      &out_plus_ssd_fit_res_z);
  FillTVector3ToDouble(lres[1][1], &out_plus_gtr100_fit_res_x,   &out_plus_gtr100_fit_res_y,   &out_plus_gtr100_fit_res_z);
  FillTVector3ToDouble(lres[1][2], &out_plus_gtr200_fit_res_x,   &out_plus_gtr200_fit_res_y,   &out_plus_gtr200_fit_res_z);
  FillTVector3ToDouble(lres[1][3], &out_plus_gtr300_fit_res_x,   &out_plus_gtr300_fit_res_y,   &out_plus_gtr300_fit_res_z);
  out_mass.emplace_back(CalcMass(tmp_minus_mom, tmp_plus_mom));
  return;
}

void E16ANA_TrackAnalyzerFromTree::PairTracking(const int track_index_pair[], double tgt_z) {
  AddTracks(track_index_pair, tgt_z);
  pair_fitter->SetRungeKuttaStepSize(pt_param::kStepSize);
  pair_fitter->SetMaxSteps(pt_param::kMaxSteps);
  out_chi_square.emplace_back(pair_fitter->Fit(pt_param::kVertexXyFixFlag, pt_param::kPyFixFlag, pt_param::kVertexZFixFlag,
                                               pt_param::kMinuitStrategy, pt_param::kMaxFunctionCalls));
  UpdateFitResult(track_index_pair);
  return;
}

std::vector<int> E16ANA_TrackAnalyzerFromTree::SortedTrackPairIndex() {
  std::vector<std::pair<int, double>> index_chi2_pair;
  for (int i = 0; i < out_n_pairs; ++i) {
    index_chi2_pair.emplace_back(std::make_pair(i, out_chi_square[i]));
  }
  std::sort(index_chi2_pair.begin(), index_chi2_pair.end(), [](auto& lhs ,auto& rhs) {
    return lhs.second < rhs.second;
  });
  std::vector<int> sorted_pair_index(out_n_pairs);
  for (int i = 0; i < out_n_pairs; ++i) {
    sorted_pair_index[i] = index_chi2_pair[i].first;
  }
  return sorted_pair_index;
}

bool E16ANA_TrackAnalyzerFromTree::IsGoodPair(int pair_index) {
  // write your selection criteria begin
  if (out_chi_square[pair_index] > pt_param::kChiSquareThreshold) {
    return false;
  }
  // write your selection criteria end
  return true;
}

void E16ANA_TrackAnalyzerFromTree::CheckUsedTracks(int pair_index, std::vector<int>* used_minus_tracks, std::vector<int>* used_plus_tracks) {
  auto mtid = out_minus_track_id[pair_index];
  auto ptid = out_plus_track_id[pair_index];
  for (const auto& track_id : *used_minus_tracks) {
    if (mtid == track_id) {
      return;
    }
  }
  for (const auto& track_id : *used_plus_tracks) {
    if (ptid == track_id) {
      return;
    }
  }
  used_minus_tracks->emplace_back(mtid);
  used_plus_tracks->emplace_back(ptid);
  ++out_n_selected_pairs;
  out_is_selected[pair_index] = true;
  return;
}

void E16ANA_TrackAnalyzerFromTree::SelectTrackPair(int pair_index, std::vector<int>* used_minus_tracks, std::vector<int>* used_plus_tracks) {
  if (IsGoodPair(pair_index)) {
    CheckUsedTracks(pair_index, used_minus_tracks, used_plus_tracks);
  }
  return;
}

void E16ANA_TrackAnalyzerFromTree::SelectTrackPairs() {
  out_n_pairs = out_chi_square.size();
  out_is_selected.assign(out_n_pairs, false);
  auto sorted_pair_index = SortedTrackPairIndex();
  std::vector<int> used_minus_tracks;
  std::vector<int> used_plus_tracks;
  for (const auto& pair_index : sorted_pair_index) {
    SelectTrackPair(pair_index, &used_minus_tracks, &used_plus_tracks);
  }
  return;
}

void E16ANA_TrackAnalyzerFromTree::AnalyzeTrackPairs(std::vector<int>* selected_track_index) {
  int n_selected_tracks = selected_track_index->size();
  for (int index0 = 0; index0 < n_selected_tracks - 1; ++index0) {
    auto selected_track_index0 = selected_track_index->at(index0);
//    auto charge0 = CalcCharge(selected_track_index0);
    auto charge0 = rk_charge->at(selected_track_index0);
    auto tgt_z0 = rk_hit_init_pos_gz->at(selected_track_index0);
    for (int index1 = index0 + 1; index1 < n_selected_tracks; ++index1) {
      auto selected_track_index1 = selected_track_index->at(index1);
//      auto charge1 = CalcCharge(selected_track_index1);
      auto charge1 = rk_charge->at(selected_track_index1);
      auto tgt_z1 = rk_hit_init_pos_gz->at(selected_track_index1);
      if (charge0 == charge1 || tgt_z0 != tgt_z1) {
        continue;
      }
      int track_index_pair[2]; // 0 : minus, 1 : plus
      if (charge0 == -1) {
        track_index_pair[0] = selected_track_index0;
        track_index_pair[1] = selected_track_index1;
      } else {
        track_index_pair[0] = selected_track_index1;
        track_index_pair[1] = selected_track_index0;
      }
//      TVector3 st_minus_mom;
//      TVector3 st_plus_mom;
//      SearchVertex(minus_index, plus_index, &st_minus_mom, &st_plus_mom);
      PairTracking(track_index_pair, tgt_z0);
    }
  }
  SelectTrackPairs();
  out_tree->Fill();
  return;
}

void E16ANA_TrackAnalyzerFromTree::Loop() {
//   In a ROOT session, you can do:
//      root> .L E16ANA_TrackAnalyzerFromTree.C
//      root> E16ANA_TrackAnalyzerFromTree t
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

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    if (jentry % 10 == 0) {
      std::cout << jentry << " / " << nentries << std::endl;
    }
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (Cut(ientry) < 0) continue;
    ClearOutBranch();
    std::vector<int> selected_track_index;
    SelectTracks(&selected_track_index);
    AnalyzeTrackPairs(&selected_track_index);
  }
  out_file->Write();
  return;
}
