#define E16ANA_TrackAnalyzerFromTree_cxx
#include "E16ANA_TrackAnalyzerFromTreeV2.hh"

#include <array>
#include <vector>

#include "E16ANA_TrackAnalyzerFromTreeParameterV2.hh"
#include "E16ANA_StepTrack.hh"
#include "E16DST_DST1.hh"

namespace track_const = E16ANA_TrackConstant;
namespace cmn_param   = E16ANA_TrackAnalyzerFromTreeParameter;
namespace st_param    = E16ANA_TrackAnalyzerFromTreeSingleTrackParameter;
namespace pit_param   = E16ANA_TrackAnalyzerFromTreePionSingleTrackParameter;
namespace pt_param    = E16ANA_TrackAnalyzerFromTreePairTrackParameter;

void E16ANA_TrackAnalyzerFromTree::ClearOutBranch() {
  out_run_id = run_id;
  out_event_id = event_id;
  out_spill_id = spill_id;
  out_timestamp_in_spill = timestamp_in_spill;
  out_trigger_fine_time= trigger_fine_time;
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
  out_minus_mom.clear();
  out_minus_mom_gx.clear();
  out_minus_mom_gy.clear();
  out_minus_mom_gz.clear();
  out_plus_mom.clear();
  out_plus_mom_gx.clear();
  out_plus_mom_gy.clear();
  out_plus_mom_gz.clear();
  out_minus_ssd_mid.clear();
  out_minus_gtr100_mid.clear();
  out_minus_gtr200_mid.clear();
  out_minus_gtr300_mid.clear();
  out_minus_hbd_mid.clear();
  out_minus_lg_c_mid.clear();
  out_minus_lg_b_mid.clear();
  out_minus_lg_a_mid.clear();
  out_plus_ssd_mid.clear();
  out_plus_gtr100_mid.clear();
  out_plus_gtr200_mid.clear();
  out_plus_gtr300_mid.clear();
  out_plus_hbd_mid.clear();
  out_plus_lg_c_mid.clear();
  out_plus_lg_b_mid.clear();
  out_plus_lg_a_mid.clear();
  
  out_minus_proj_has_hbd_cluster_e.clear();
  out_plus_proj_has_hbd_cluster_e.clear();
  out_minus_proj_has_lg_hit_e.clear();
  out_plus_proj_has_lg_hit_e.clear();
  out_minus_proj_has_lg_cluster_e.clear();
  out_plus_proj_has_lg_cluster_e.clear();
  out_minus_proj_n_hbd_clusters.clear();
  out_minus_proj_hbd_cluster_res.clear();
  out_minus_proj_hbd_cluster_res_x.clear();
  out_minus_proj_hbd_cluster_res_y.clear();
  out_minus_proj_hbd_cluster_adc.clear();
  out_minus_proj_hbd_cluster_t.clear();
  out_minus_proj_hbd_cluster_eprob.clear();
  out_minus_proj_hbd_cluster_cprob.clear();
  out_plus_proj_n_hbd_clusters.clear();
  out_plus_proj_hbd_cluster_res.clear();
  out_plus_proj_hbd_cluster_res_x.clear();
  out_plus_proj_hbd_cluster_res_y.clear();
  out_plus_proj_hbd_cluster_adc.clear();
  out_plus_proj_hbd_cluster_t.clear();
  out_plus_proj_hbd_cluster_eprob.clear();
  out_plus_proj_hbd_cluster_cprob.clear();
  out_minus_proj_n_lg_hits.clear();
  out_minus_proj_lg_hit_type.clear();
  out_minus_proj_lg_hit_res.clear();
  out_minus_proj_lg_hit_res_x.clear();
  out_minus_proj_lg_hit_res_y.clear();
  out_minus_proj_lg_hit_adc.clear();
  out_minus_proj_lg_hit_t.clear();
  out_minus_proj_lg_hit_ise.clear();
  out_plus_proj_n_lg_hits.clear();
  out_plus_proj_lg_hit_type.clear();
  out_plus_proj_lg_hit_res.clear();
  out_plus_proj_lg_hit_res_x.clear();
  out_plus_proj_lg_hit_res_y.clear();
  out_plus_proj_lg_hit_adc.clear();
  out_plus_proj_lg_hit_t.clear();
  out_plus_proj_lg_hit_ise.clear();
  out_minus_proj_n_lg_clusters.clear();
  out_minus_proj_lg_cluster_type.clear();
  out_minus_proj_lg_cluster_res.clear();
  out_minus_proj_lg_cluster_res_x.clear();
  out_minus_proj_lg_cluster_res_y.clear();
  out_minus_proj_lg_cluster_adc.clear();
  out_minus_proj_lg_cluster_t.clear();
  out_minus_proj_lg_cluster_ise.clear();
  out_plus_proj_n_lg_clusters.clear();
  out_plus_proj_lg_cluster_type.clear();
  out_plus_proj_lg_cluster_res.clear();
  out_plus_proj_lg_cluster_res_x.clear();
  out_plus_proj_lg_cluster_res_y.clear();
  out_plus_proj_lg_cluster_adc.clear();
  out_plus_proj_lg_cluster_t.clear();
  out_plus_proj_lg_cluster_ise.clear();
  out_minus_proj_hbd_cluster_x.clear();
  out_minus_proj_hbd_cluster_y.clear();
  out_minus_proj_lg_hit_x.clear();
  out_minus_proj_lg_hit_y.clear();
  out_minus_proj_lg_hit_z.clear();
  out_minus_proj_lg_cluster_x.clear();
  out_minus_proj_lg_cluster_y.clear();
  out_minus_proj_lg_cluster_z.clear();
  out_plus_proj_hbd_cluster_x.clear();
  out_plus_proj_hbd_cluster_y.clear();
  out_plus_proj_lg_hit_x.clear();
  out_plus_proj_lg_hit_y.clear();
  out_plus_proj_lg_hit_z.clear();
  out_plus_proj_lg_cluster_x.clear();
  out_plus_proj_lg_cluster_y.clear();
  out_plus_proj_lg_cluster_z.clear();

  out_minus_ssd_hit_x.clear();
  out_minus_ssd_hit_y.clear();
  out_minus_ssd_hit_z.clear();
  out_minus_gtr100_hit_x.clear();
  out_minus_gtr100_hit_y.clear();
  out_minus_gtr100_hit_z.clear();
  out_minus_gtr200_hit_x.clear();
  out_minus_gtr200_hit_y.clear();
  out_minus_gtr200_hit_z.clear();
  out_minus_gtr300_hit_x.clear();
  out_minus_gtr300_hit_y.clear();
  out_minus_gtr300_hit_z.clear();
  out_plus_ssd_hit_x.clear();
  out_plus_ssd_hit_y.clear();
  out_plus_ssd_hit_z.clear();
  out_plus_gtr100_hit_x.clear();
  out_plus_gtr100_hit_y.clear();
  out_plus_gtr100_hit_z.clear();
  out_plus_gtr200_hit_x.clear();
  out_plus_gtr200_hit_y.clear();
  out_plus_gtr200_hit_z.clear();
  out_plus_gtr300_hit_x.clear();
  out_plus_gtr300_hit_y.clear();
  out_plus_gtr300_hit_z.clear();
  out_minus_ssd_hit_gx.clear();
  out_minus_ssd_hit_gy.clear();
  out_minus_ssd_hit_gz.clear();
  out_minus_ssd_hit_t.clear();
  out_minus_ssd_hit_adc.clear();
  out_minus_gtr100_hit_gx.clear();
  out_minus_gtr100_hit_gy.clear();
  out_minus_gtr100_hit_gz.clear();
  out_minus_gtr100_hit_xt.clear();
  out_minus_gtr100_hit_yt.clear();
  out_minus_gtr100_hit_xadc.clear();
  out_minus_gtr100_hit_yadc.clear();
  out_minus_gtr200_hit_gx.clear();
  out_minus_gtr200_hit_gy.clear();
  out_minus_gtr200_hit_gz.clear();
  out_minus_gtr200_hit_xt.clear();
  out_minus_gtr200_hit_yt.clear();
  out_minus_gtr200_hit_xadc.clear();
  out_minus_gtr200_hit_yadc.clear();
  out_minus_gtr300_hit_gx.clear();
  out_minus_gtr300_hit_gy.clear();
  out_minus_gtr300_hit_gz.clear();
  out_minus_gtr300_hit_xt.clear();
  out_minus_gtr300_hit_yt.clear();
  out_minus_gtr300_hit_xadc.clear();
  out_minus_gtr300_hit_yadc.clear();
  out_plus_ssd_hit_gx.clear();
  out_plus_ssd_hit_gy.clear();
  out_plus_ssd_hit_gz.clear();
  out_plus_ssd_hit_t.clear();
  out_plus_ssd_hit_adc.clear();
  out_plus_gtr100_hit_gx.clear();
  out_plus_gtr100_hit_gy.clear();
  out_plus_gtr100_hit_gz.clear();
  out_plus_gtr100_hit_xt.clear();
  out_plus_gtr100_hit_yt.clear();
  out_plus_gtr100_hit_xadc.clear();
  out_plus_gtr100_hit_yadc.clear();
  out_plus_gtr200_hit_gx.clear();
  out_plus_gtr200_hit_gy.clear();
  out_plus_gtr200_hit_gz.clear();
  out_plus_gtr200_hit_xt.clear();
  out_plus_gtr200_hit_yt.clear();
  out_plus_gtr200_hit_xadc.clear();
  out_plus_gtr200_hit_yadc.clear();
  out_plus_gtr300_hit_gx.clear();
  out_plus_gtr300_hit_gy.clear();
  out_plus_gtr300_hit_gz.clear();
  out_plus_gtr300_hit_xt.clear();
  out_plus_gtr300_hit_yt.clear();
  out_plus_gtr300_hit_xadc.clear();
  out_plus_gtr300_hit_yadc.clear();
  
  out_minus_ssd_fit_x.clear();
  out_minus_ssd_fit_y.clear();
  out_minus_ssd_fit_z.clear();
  out_minus_gtr100_fit_x.clear();
  out_minus_gtr100_fit_y.clear();
  out_minus_gtr100_fit_z.clear();
  out_minus_gtr200_fit_x.clear();
  out_minus_gtr200_fit_y.clear();
  out_minus_gtr200_fit_z.clear();
  out_minus_gtr300_fit_x.clear();
  out_minus_gtr300_fit_y.clear();
  out_minus_gtr300_fit_z.clear();
  out_plus_ssd_fit_x.clear();
  out_plus_ssd_fit_y.clear();
  out_plus_ssd_fit_z.clear();
  out_plus_gtr100_fit_x.clear();
  out_plus_gtr100_fit_y.clear();
  out_plus_gtr100_fit_z.clear();
  out_plus_gtr200_fit_x.clear();
  out_plus_gtr200_fit_y.clear();
  out_plus_gtr200_fit_z.clear();
  out_plus_gtr300_fit_x.clear();
  out_plus_gtr300_fit_y.clear();
  out_plus_gtr300_fit_z.clear();
  out_minus_ssd_fit_gx.clear();
  out_minus_ssd_fit_gy.clear();
  out_minus_ssd_fit_gz.clear();
  out_minus_gtr100_fit_gx.clear();
  out_minus_gtr100_fit_gy.clear();
  out_minus_gtr100_fit_gz.clear();
  out_minus_gtr200_fit_gx.clear();
  out_minus_gtr200_fit_gy.clear();
  out_minus_gtr200_fit_gz.clear();
  out_minus_gtr300_fit_gx.clear();
  out_minus_gtr300_fit_gy.clear();
  out_minus_gtr300_fit_gz.clear();
  out_plus_ssd_fit_gx.clear();
  out_plus_ssd_fit_gy.clear();
  out_plus_ssd_fit_gz.clear();
  out_plus_gtr100_fit_gx.clear();
  out_plus_gtr100_fit_gy.clear();
  out_plus_gtr100_fit_gz.clear();
  out_plus_gtr200_fit_gx.clear();
  out_plus_gtr200_fit_gy.clear();
  out_plus_gtr200_fit_gz.clear();
  out_plus_gtr300_fit_gx.clear();
  out_plus_gtr300_fit_gy.clear();
  out_plus_gtr300_fit_gz.clear();
  out_minus_hbd_fit_x.clear();
  out_minus_hbd_fit_y.clear();
  out_minus_hbd_fit_z.clear();
  out_minus_hbd_fit_gx.clear();
  out_minus_hbd_fit_gy.clear();
  out_minus_hbd_fit_gz.clear();
  out_minus_lg_c_fit_x.clear();
  out_minus_lg_c_fit_y.clear();
  out_minus_lg_c_fit_z.clear();
  out_minus_lg_c_fit_gx.clear();
  out_minus_lg_c_fit_gy.clear();
  out_minus_lg_c_fit_gz.clear();
  out_minus_lg_b_fit_x.clear();
  out_minus_lg_b_fit_y.clear();
  out_minus_lg_b_fit_z.clear();
  out_minus_lg_b_fit_gx.clear();
  out_minus_lg_b_fit_gy.clear();
  out_minus_lg_b_fit_gz.clear();
  out_minus_lg_a_fit_x.clear();
  out_minus_lg_a_fit_y.clear();
  out_minus_lg_a_fit_z.clear();
  out_minus_lg_a_fit_gx.clear();
  out_minus_lg_a_fit_gy.clear();
  out_minus_lg_a_fit_gz.clear();
  out_plus_hbd_fit_x.clear();
  out_plus_hbd_fit_y.clear();
  out_plus_hbd_fit_z.clear();
  out_plus_hbd_fit_gx.clear();
  out_plus_hbd_fit_gy.clear();
  out_plus_hbd_fit_gz.clear();
  out_plus_lg_c_fit_x.clear();
  out_plus_lg_c_fit_y.clear();
  out_plus_lg_c_fit_z.clear();
  out_plus_lg_c_fit_gx.clear();
  out_plus_lg_c_fit_gy.clear();
  out_plus_lg_c_fit_gz.clear();
  out_plus_lg_b_fit_x.clear();
  out_plus_lg_b_fit_y.clear();
  out_plus_lg_b_fit_z.clear();
  out_plus_lg_b_fit_gx.clear();
  out_plus_lg_b_fit_gy.clear();
  out_plus_lg_b_fit_gz.clear();
  out_plus_lg_a_fit_x.clear();
  out_plus_lg_a_fit_y.clear();
  out_plus_lg_a_fit_z.clear();
  out_plus_lg_a_fit_gx.clear();
  out_plus_lg_a_fit_gy.clear();
  out_plus_lg_a_fit_gz.clear();
  
  out_minus_ssd_fit_mom_x.clear();
  out_minus_ssd_fit_mom_y.clear();
  out_minus_ssd_fit_mom_z.clear();
  out_minus_ssd_fit_mom_tan.clear();
  out_minus_ssd_fit_mom_gx.clear();
  out_minus_ssd_fit_mom_gy.clear();
  out_minus_ssd_fit_mom_gz.clear();
  out_minus_gtr100_fit_mom_x.clear();
  out_minus_gtr100_fit_mom_y.clear();
  out_minus_gtr100_fit_mom_z.clear();
  out_minus_gtr100_fit_mom_tan.clear();
  out_minus_gtr100_fit_mom_gx.clear();
  out_minus_gtr100_fit_mom_gy.clear();
  out_minus_gtr100_fit_mom_gz.clear();
  out_minus_gtr200_fit_mom_x.clear();
  out_minus_gtr200_fit_mom_y.clear();
  out_minus_gtr200_fit_mom_z.clear();
  out_minus_gtr200_fit_mom_tan.clear();
  out_minus_gtr200_fit_mom_gx.clear();
  out_minus_gtr200_fit_mom_gy.clear();
  out_minus_gtr200_fit_mom_gz.clear();
  out_minus_gtr300_fit_mom_x.clear();
  out_minus_gtr300_fit_mom_y.clear();
  out_minus_gtr300_fit_mom_z.clear();
  out_minus_gtr300_fit_mom_tan.clear();
  out_minus_gtr300_fit_mom_gx.clear();
  out_minus_gtr300_fit_mom_gy.clear();
  out_minus_gtr300_fit_mom_gz.clear();
  out_plus_ssd_fit_mom_x.clear();
  out_plus_ssd_fit_mom_y.clear();
  out_plus_ssd_fit_mom_z.clear();
  out_plus_ssd_fit_mom_tan.clear();
  out_plus_ssd_fit_mom_gx.clear();
  out_plus_ssd_fit_mom_gy.clear();
  out_plus_ssd_fit_mom_gz.clear();
  out_plus_gtr100_fit_mom_x.clear();
  out_plus_gtr100_fit_mom_y.clear();
  out_plus_gtr100_fit_mom_z.clear();
  out_plus_gtr100_fit_mom_tan.clear();
  out_plus_gtr100_fit_mom_gx.clear();
  out_plus_gtr100_fit_mom_gy.clear();
  out_plus_gtr100_fit_mom_gz.clear();
  out_plus_gtr200_fit_mom_x.clear();
  out_plus_gtr200_fit_mom_y.clear();
  out_plus_gtr200_fit_mom_z.clear();
  out_plus_gtr200_fit_mom_tan.clear();
  out_plus_gtr200_fit_mom_gx.clear();
  out_plus_gtr200_fit_mom_gy.clear();
  out_plus_gtr200_fit_mom_gz.clear();
  out_plus_gtr300_fit_mom_x.clear();
  out_plus_gtr300_fit_mom_y.clear();
  out_plus_gtr300_fit_mom_z.clear();
  out_plus_gtr300_fit_mom_tan.clear();
  out_plus_gtr300_fit_mom_gx.clear();
  out_plus_gtr300_fit_mom_gy.clear();
  out_plus_gtr300_fit_mom_gz.clear();
  out_minus_hbd_fit_mom_x.clear();
  out_minus_hbd_fit_mom_y.clear();
  out_minus_hbd_fit_mom_z.clear();
  out_minus_hbd_fit_mom_tan.clear();
  out_minus_hbd_fit_mom_gx.clear();
  out_minus_hbd_fit_mom_gy.clear();
  out_minus_hbd_fit_mom_gz.clear();
  out_minus_lg_c_fit_mom_x.clear();
  out_minus_lg_c_fit_mom_y.clear();
  out_minus_lg_c_fit_mom_z.clear();
  out_minus_lg_c_fit_mom_tan.clear();
  out_minus_lg_c_fit_mom_gx.clear();
  out_minus_lg_c_fit_mom_gy.clear();
  out_minus_lg_c_fit_mom_gz.clear();
  out_minus_lg_b_fit_mom_x.clear();
  out_minus_lg_b_fit_mom_y.clear();
  out_minus_lg_b_fit_mom_z.clear();
  out_minus_lg_b_fit_mom_tan.clear();
  out_minus_lg_b_fit_mom_gx.clear();
  out_minus_lg_b_fit_mom_gy.clear();
  out_minus_lg_b_fit_mom_gz.clear();
  out_minus_lg_a_fit_mom_x.clear();
  out_minus_lg_a_fit_mom_y.clear();
  out_minus_lg_a_fit_mom_z.clear();
  out_minus_lg_a_fit_mom_tan.clear();
  out_minus_lg_a_fit_mom_gx.clear();
  out_minus_lg_a_fit_mom_gy.clear();
  out_minus_lg_a_fit_mom_gz.clear();
  out_plus_hbd_fit_mom_x.clear();
  out_plus_hbd_fit_mom_y.clear();
  out_plus_hbd_fit_mom_z.clear();
  out_plus_hbd_fit_mom_tan.clear();
  out_plus_hbd_fit_mom_gx.clear();
  out_plus_hbd_fit_mom_gy.clear();
  out_plus_hbd_fit_mom_gz.clear();
  out_plus_lg_c_fit_mom_x.clear();
  out_plus_lg_c_fit_mom_y.clear();
  out_plus_lg_c_fit_mom_z.clear();
  out_plus_lg_c_fit_mom_tan.clear();
  out_plus_lg_c_fit_mom_gx.clear();
  out_plus_lg_c_fit_mom_gy.clear();
  out_plus_lg_c_fit_mom_gz.clear();
  out_plus_lg_b_fit_mom_x.clear();
  out_plus_lg_b_fit_mom_y.clear();
  out_plus_lg_b_fit_mom_z.clear();
  out_plus_lg_b_fit_mom_tan.clear();
  out_plus_lg_b_fit_mom_gx.clear();
  out_plus_lg_b_fit_mom_gy.clear();
  out_plus_lg_b_fit_mom_gz.clear();
  out_plus_lg_a_fit_mom_x.clear();
  out_plus_lg_a_fit_mom_y.clear();
  out_plus_lg_a_fit_mom_z.clear();
  out_plus_lg_a_fit_mom_tan.clear();
  out_plus_lg_a_fit_mom_gx.clear();
  out_plus_lg_a_fit_mom_gy.clear();
  out_plus_lg_a_fit_mom_gz.clear();
  
  out_minus_ssd_res.clear();
  out_minus_gtr100_res.clear();
  out_minus_gtr200_res.clear();
  out_minus_gtr300_res.clear();
  out_plus_ssd_res.clear();
  out_plus_gtr100_res.clear();
  out_plus_gtr200_res.clear();
  out_plus_gtr300_res.clear();
  out_minus_ssd_res_x.clear();
  out_minus_ssd_res_y.clear();
  out_minus_ssd_res_z.clear();
  out_minus_gtr100_res_x.clear();
  out_minus_gtr100_res_y.clear();
  out_minus_gtr100_res_z.clear();
  out_minus_gtr200_res_x.clear();
  out_minus_gtr200_res_y.clear();
  out_minus_gtr200_res_z.clear();
  out_minus_gtr300_res_x.clear();
  out_minus_gtr300_res_y.clear();
  out_minus_gtr300_res_z.clear();
  out_plus_ssd_res_x.clear();
  out_plus_ssd_res_y.clear();
  out_plus_ssd_res_z.clear();
  out_plus_gtr100_res_x.clear();
  out_plus_gtr100_res_y.clear();
  out_plus_gtr100_res_z.clear();
  out_plus_gtr200_res_x.clear();
  out_plus_gtr200_res_y.clear();
  out_plus_gtr200_res_z.clear();
  out_plus_gtr300_res_x.clear();
  out_plus_gtr300_res_y.clear();
  out_plus_gtr300_res_z.clear();
  
  out_ee_mass.clear();
  out_pipi_mass.clear();
  out_pip_mass.clear();
  out_ks_pos_at_x0_gx.clear();
  out_ks_pos_at_x0_gy.clear();
  out_ks_pos_at_x0_gz.clear();
  out_ks_mom_at_x0_gx.clear();
  out_ks_mom_at_x0_gy.clear();
  out_ks_mom_at_x0_gz.clear();
  out_ks_t_at_x0.clear();
  return;
}

bool E16ANA_TrackAnalyzerFromTree::HasHBDClusters(int track_mid, const TVector3& track_lpos, std::vector<int>* cluster_indexs) {
  for (int clst_i = 0; clst_i < n_hbd_clusters; ++clst_i) {
    auto c_prob = hbd_cluster_cprob->at(clst_i);
    auto e_prob = hbd_cluster_eprob->at(clst_i);
//    if (particle_flag == cmn_param::kPionFlag && c_prob < 0.5) {
//      continue;
//    }
//    if (particle_flag == cmn_param::kElectronFlag && e_prob < 0.5) {
//      continue;
//    }
    auto mid = hbd_cluster_mid->at(clst_i);
    if (mid != track_mid) {
      continue;
    }
    auto lpos = TVector3(hbd_cluster_x->at(clst_i), hbd_cluster_y->at(clst_i), 0.);
    auto residual = (lpos - track_lpos).Mag();
    if (residual > st_param::kHBDResidualThreshold) {
      continue;
    }
    cluster_indexs->emplace_back(clst_i);
  }
  return cluster_indexs->size() != 0;
}

bool E16ANA_TrackAnalyzerFromTree::IsTrackLGValidY(const double track_ys[], bool track_valids[]) {
  bool tmp_is_valid = false;
  for (int i = 0; i < cmn_param::kNumLGTypes; ++i) {
    auto y  = track_ys[i];
    if (y > cmn_param::kLGMinY[i] && y < cmn_param::kLGMaxY[i]) {
      track_valids[i] = true;
      tmp_is_valid = true;
    } else {
      track_valids[i] = false;
    }
  }
  return tmp_is_valid;
}

bool E16ANA_TrackAnalyzerFromTree::HasLGHits(double track_mom, const int track_mids[], const double track_xs[], const bool track_valids[], std::vector<int>* hit_indexs) {
  for (int hit_i = 0; hit_i < n_lg_hits; ++hit_i) {
    auto adc = lg_hit_adc->at(hit_i);
//    if (particle_flag == cmn_param::kElectronFlag && E16DST_DST1LGHit::IsE(track_mom, adc) < 0.5) {
//      continue;
//    }
    // type decision
    auto ch_y = int{lg_hit_cid->at(hit_i)} / 10;
    int type = -1;
    if (ch_y == 0 || ch_y == 5) {
      type = cmn_param::kLGTypeC;
    } else if (ch_y == 1 || ch_y == 4) {
      type = cmn_param::kLGTypeB;
    } else if (ch_y == 2 || ch_y == 3) {
      type = cmn_param::kLGTypeA;
    }
    if (type == -1) {
      std::cerr << "Invalid LG hit y" << std::endl;
      continue;
    }
    // y match
    if (!track_valids[type]) {
      continue;
    }
    // Module match
    auto mid = lg_hit_mid->at(hit_i);
    if (mid != track_mids[type]) {
      continue;
    }
    // x match
    auto x = lg_hit_x->at(hit_i);
    if (fabs(x - track_xs[type]) > st_param::kLGHitXResidualThreshold) {
      continue;
    }
    hit_indexs->emplace_back(hit_i);
  }
  return hit_indexs->size() != 0;
}

bool E16ANA_TrackAnalyzerFromTree::HasLGClusters(double track_mom, const int track_mids[], const double track_xs[], const bool track_valids[], std::vector<int>* cluster_indexs) {
  for (int clst_i = 0; clst_i < n_lg_clusters; ++clst_i) {
    auto adc = lg_cluster_adc->at(clst_i);
//    if (particle_flag == cmn_param::kElectronFlag && E16DST_DST1LGHit::IsE(track_mom, adc) < 0.5) {
//      continue;
//    }
    // type decision
    auto z = lg_cluster_z->at(clst_i);
    int type;
    for (type = 0; type < cmn_param::kNumLGTypes + 1; ++type) {
      if (fabs(z - cmn_param::kLGLocalZ[type]) < 0.1) {
        break;
      }
    }
    if (type == cmn_param::kNumLGTypes) {
      std::cerr << "Invalid LG cluster z" << std::endl;
      continue;
    }
    // y match
    if (!track_valids[type]) {
      continue;
    }
    // module match
    auto mid = lg_cluster_mid->at(clst_i);
    if (mid != track_mids[type]) {
      continue;
    }
    // x match
    auto x = lg_cluster_x->at(clst_i);
    if (fabs(x - track_xs[type]) > st_param::kLGClusterXResidualThreshold) {
      continue;
    }
    cluster_indexs->emplace_back(clst_i);
  }
  return cluster_indexs->size() != 0;
}

bool E16ANA_TrackAnalyzerFromTree::HasHBDAndLGProjection(int track_index) {
  auto track_hbd_mid  = rk_fit_hbd_mid->at(track_index);
  auto track_hbd_lpos = TVector3(rk_fit_hbd_x->at(track_index), rk_fit_hbd_y->at(track_index), 0.);
  auto track_mom_v = TVector3(rk_fit_init_mom_gx->at(track_index), rk_fit_init_mom_gy->at(track_index), rk_fit_init_mom_gz->at(track_index));
  auto track_mom   = track_mom_v.Mag();
  int    track_lg_mids[cmn_param::kNumLGTypes] = {rk_fit_lg_c_mid->at(track_index), rk_fit_lg_b_mid->at(track_index), rk_fit_lg_a_mid->at(track_index)};
  double track_lg_xs[cmn_param::kNumLGTypes]   = {rk_fit_lg_c_x->at(track_index),   rk_fit_lg_b_x->at(track_index),   rk_fit_lg_a_x->at(track_index)};
  double track_lg_ys[cmn_param::kNumLGTypes]   = {rk_fit_lg_c_y->at(track_index),   rk_fit_lg_b_y->at(track_index),   rk_fit_lg_a_y->at(track_index)};
  bool   track_lg_valids[cmn_param::kNumLGTypes];
  std::vector<int> tmp_hbd_clst_indexs;
  std::vector<int> tmp_lg_hit_indexs;
  std::vector<int> tmp_lg_clst_indexs;
  if (!HasHBDClusters(track_hbd_mid, track_hbd_lpos, &tmp_hbd_clst_indexs)) {
    return false;
  }
  if (!IsTrackLGValidY(track_lg_ys, track_lg_valids)) {
    return false;
  }
  if (!HasLGHits(track_mom,     track_lg_mids, track_lg_xs, track_lg_valids, &tmp_lg_hit_indexs) ||
      !HasLGClusters(track_mom, track_lg_mids, track_lg_xs, track_lg_valids, &tmp_lg_clst_indexs)) {
    return false;
  }
  return true;
}

//bool HasTimeCorrelationInTrack() {
//}

bool E16ANA_TrackAnalyzerFromTree::IsGoodTrack(int track_index) {
  // write your selection criteria begin
  if (chi_square->at(track_index) > st_param::kChiSquareThreshold) {
    return false;
  }
  if (fabs(rk_res_ssd_x->at(track_index)) > st_param::kSSDResidualThreshold) {
    return false;
  }
  if (fabs(rk_res_gtr100_x->at(track_index)) > st_param::kGTR100xResidualThreshold) {
    return false;
  }
  if (fabs(rk_res_gtr100_y->at(track_index)) > st_param::kGTR100yResidualThreshold) {
    return false;
  }
  if (fabs(rk_res_gtr200_x->at(track_index)) > st_param::kGTR200xResidualThreshold) {
    return false;
  }
  if (fabs(rk_res_gtr200_y->at(track_index)) > st_param::kGTR200yResidualThreshold) {
    return false;
  }
  if (fabs(rk_res_gtr300_x->at(track_index)) > st_param::kGTR300xResidualThreshold) {
    return false;
  }
  if (fabs(rk_res_gtr300_y->at(track_index)) > st_param::kGTR300yResidualThreshold) {
    return false;
  }
  if (fabs(rk_fit_init_pos_gx->at(track_index)) > st_param::kTargetXThreshold) {
    return false;
  }
  if (fabs(rk_fit_init_pos_gy->at(track_index)) > st_param::kTargetYThreshold) {
    return false;
  }
  if (!HasHBDAndLGProjection(track_index)) {
    return false;
  }
  // HasTimeCorrelationInTrack()
  // write your selection criteria end
  return true;
}

double E16ANA_TrackAnalyzerFromTree::CalcSingleTrackChiSquareWoTarget(int track_index) {
  double chi_square_from_tgt = 0.;
  auto init_pos = TVector3(rk_fit_init_pos_gx->at(track_index), rk_fit_init_pos_gy->at(track_index), rk_fit_init_pos_gz->at(track_index));
  for (int i = 0; i < 3; ++i) {
    if (pit_param::kInitPosError(i) == 0.) {
      continue;
    }
    chi_square_from_tgt += pow(init_pos(i) / pit_param::kInitPosError(i), 2.);
  }
  return chi_square->at(track_index) - chi_square_from_tgt;
}

bool E16ANA_TrackAnalyzerFromTree::IsGoodPionTrack(int track_index) {
  // write your selection criteria begin
  if (chi_square->at(track_index) > pit_param::kChiSquareThreshold) {
//  if (CalcSingleTrackChiSquareWoTarget(track_index) > pit_param::kChiSquareThreshold) {
    return false;
  }
//  if (rk_proj_n_hbd->at(track_index) == 0) {
//    return false;
//  }
//  if (rk_proj_n_lg->at(track_index) == 0) {
//    return false;
//  }
//  bool is_hbd_pion = false;
//  if (rk_proj_n_hbd->at(track_index) >= 1 && rk_proj_hbd0_eprob->at(track_index) < 0.5 && rk_proj_hbd0_cprob->at(track_index) > 0.5) {
//    is_hbd_pion = true;
//  } else if (rk_proj_n_hbd->at(track_index) >= 2 && rk_proj_hbd1_eprob->at(track_index) > 0.5 && rk_proj_hbd1_cprob->at(track_index) > 0.5) {
//    is_hbd_pion = true;
//  } else if (rk_proj_n_hbd->at(track_index) >= 3 && rk_proj_hbd2_eprob->at(track_index) > 0.5 && rk_proj_hbd2_cprob->at(track_index) > 0.5) {
//    is_hbd_pion = true;
//  } else if (rk_proj_n_hbd->at(track_index) >= 4 && rk_proj_hbd3_eprob->at(track_index) > 0.5 && rk_proj_hbd3_cprob->at(track_index) > 0.5) {
//    is_hbd_pion = true;
//  }
//  if (!is_hbd_pion) {
//    return false;
//  }
//  bool is_lg_low = false;
//  if (rk_proj_n_lg->at(track_index) >= 1 && rk_proj_lg0_adc->at(track_index) < pit_param::kLGADCThreshold) {
//    is_lg_low = true;
//  }
//  if (rk_proj_n_lg->at(track_index) >= 2 && rk_proj_lg1_adc->at(track_index) < pit_param::kLGADCThreshold) {
//    is_lg_low = true;
//  }
//  if (rk_proj_n_lg->at(track_index) >= 3 && rk_proj_lg2_adc->at(track_index) < pit_param::kLGADCThreshold) {
//    is_lg_low = true;
//  }
//  if (rk_proj_n_lg->at(track_index) >= 4 && rk_proj_lg3_adc->at(track_index) < pit_param::kLGADCThreshold) {
//    is_lg_low = true;
//  }
//  if (!is_lg_low) {
//    return false;
//  }
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
  if (!HasHBDAndLGProjection(track_index)) {
    return false;
  }
  // HasTimeCorrelationInTrack()
  // write your selection criteria end
  return true;
}

void E16ANA_TrackAnalyzerFromTree::CheckUsedClusters(int track_index, std::array<std::vector<int>, track_const::kNumTrackingLayers>* used_cluster_ids) {
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
  selected_track_indexs.emplace_back(track_index);
  return;
}

void E16ANA_TrackAnalyzerFromTree::SelectTrack(int track_index, std::array<std::vector<int>, track_const::kNumTrackingLayers>* used_cluster_ids) {
  if ((particle_flag == cmn_param::kElectronFlag && IsGoodTrack(track_index)) || (particle_flag == cmn_param::kPionFlag     && IsGoodPionTrack(track_index))) {
    CheckUsedClusters(track_index, used_cluster_ids);
  }
  return;
}

void E16ANA_TrackAnalyzerFromTree::SelectTracks() {
  std::array<std::vector<int>, track_const::kNumTrackingLayers> used_cluster_ids;
  for (int track_index = 0; track_index < n_cands; ++track_index) {
    SelectTrack(track_index, &used_cluster_ids);
  }
  return;
}

void E16ANA_TrackAnalyzerFromTree::AddTracks(const int track_index_pair[], double tgt_z) {
  pair_fitter->Clear();
  pair_fitter->SetInitialVertex(TVector3(0., 0., tgt_z), pt_param::kVertexSigma);
  pair_fitter->SetCharge(0, -1.);
  pair_fitter->SetCharge(1, 1.);
  TVector3 pair_mom;
  for (int i = 0; i < 2; ++i) {
    auto tmp_mom = TVector3(rk_fit_init_mom_gx->at(track_index_pair[i]), rk_fit_init_mom_gy->at(track_index_pair[i]), rk_fit_init_mom_gz->at(track_index_pair[i]));
    pair_fitter->SetInitialMomentum(i, tmp_mom);
  }
  for (int track_index_in_pair = 0; track_index_in_pair < 2; ++track_index_in_pair) {
    auto tindex = track_index_pair[track_index_in_pair];
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

void E16ANA_TrackAnalyzerFromTree::ProjectionHBDAndLG(const TVector3& vertex, const TVector3& mom, double charge, int track_index,
                                                      TVector3 out_lposs[], TVector3 out_gposs[], TVector3 out_lmoms[], TVector3 out_gmoms[]) {
  const int n_layers = E16ANA_TrackConstant::kNumDetectorLayers - E16ANA_TrackConstant::kHBD;
  const int tid = 0;
  const TVector3 lpos(0., 0., 0.);
  const TVector3 lsigma(0., 0., 0.);
  const int lid = 0; // only 1 layer in 1 RK
  const int hid = 0; // only 1 hit in 1 RK
  const int max_steps = 2000;
  const int tmp_lg_block_id[3] = {0, 10, 20};
  
  std::vector<int> mids;
  std::vector<TVector3> lposs;
  std::vector<TVector3> lmoms;
  int mid[n_layers] = {rk_fit_hbd_mid->at(track_index), rk_fit_lg_c_mid->at(track_index), rk_fit_lg_b_mid->at(track_index), rk_fit_lg_a_mid->at(track_index)};
  for (int l = 0; l < n_layers; ++l) {
    auto mid2013 = E16ANA_TrackConstant::ModuleID2020To2013_27(mid[l]);
    pair_fitter->Clear();
    if (l == 0) { // HBD
      auto tmp_geom = geometry->HBD(mid2013);
      pair_fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
    } else {
      auto tmp_geom = geometry->LG(mid2013, tmp_lg_block_id[l - 1]);
      pair_fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
    }
    pair_fitter->SetMaxSteps(max_steps);
    pair_fitter->RungeKuttaTracking(tid, vertex, mom, charge);
    pair_fitter->GetFitLPos(tid, lid, mids, lposs);
    pair_fitter->GetFitLMom(tid, lid, mids, lmoms);
    out_lmoms[l] = lmoms[hid];
    if (l == 0) {
      out_lposs[l] = lposs[hid];
      out_gposs[l] = geometry->HBD(mid2013)->GetGPos(lposs[hid]);
      out_gmoms[l] = geometry->HBD(mid2013)->GetGPos(lmoms[hid]);
    } else {
      out_lposs[l] = geometry->LGVD(mid2013)->GetLPos(lposs[hid]);
      out_gposs[l] = geometry->LG(mid2013, tmp_lg_block_id[l - 1])->GetGPos(lposs[hid]);
      out_gmoms[l] = geometry->LG(mid2013, tmp_lg_block_id[l - 1])->GetGMom(lmoms[hid]);
    }
  }
  return;
}

double E16ANA_TrackAnalyzerFromTree::CalcMass(int flag, TVector3 mom0, TVector3 mom1) {
  double mass2[2];
  if (flag == pt_param::kCalcEEMassFlag) {
    mass2[0] = pt_param::kElectronMass2;
    mass2[1] = pt_param::kElectronMass2;
  } else if (flag == pt_param::kCalcPiPiMassFlag) {
    mass2[0] = pt_param::kPionMass2;
    mass2[1] = pt_param::kPionMass2;
  } else if (flag == pt_param::kCalcPiPMassFlag) {
    mass2[0] = pt_param::kPionMass2;
    mass2[1] = pt_param::kProtonMass2;
  } else {
    std::cerr << "Invalid calculation flag : " << flag << std::endl;
    return -1.;
  }
  double p0 = mom0.X() * mom0.X() + mom0.Y() * mom0.Y() + mom0.Z() * mom0.Z();
  double p1 = mom1.X() * mom1.X() + mom1.Y() * mom1.Y() + mom1.Z() * mom1.Z();
  double e0 = sqrt(p0 + mass2[0]);
  double e1 = sqrt(p1 + mass2[1]);
  double p0p1 = mom0.X() * mom1.X() + mom0.Y() * mom1.Y() + mom0.Z() * mom1.Z();
  return sqrt(mass2[0] + mass2[1] + 2. * (e0 * e1 - p0p1));
}

void E16ANA_TrackAnalyzerFromTree::ProjectionX0(int pair_index, TVector3 pos, TVector3 mom) {
  out_ks_pos_at_x0_gx[pair_index] = 0.;
  out_ks_pos_at_x0_gy[pair_index] = pos(1) - mom(1) / mom(0) * pos(0);
  out_ks_pos_at_x0_gz[pair_index] = pos(2) - mom(2) / mom(0) * pos(0);
  out_ks_mom_at_x0_gx[pair_index] = mom(0);
  out_ks_mom_at_x0_gy[pair_index] = mom(1);
  out_ks_mom_at_x0_gz[pair_index] = mom(2);
  double l_x0 = sqrt(mom(1) * mom(1) + mom(2) * mom(2)) / mom(0) * pos(0);
  double v = 1. / sqrt(pow(mom.Mag() / cmn_param::kKsMass / cmn_param::kLightSpeed, 2) + 1) * cmn_param::kLightSpeed;
  out_ks_t_at_x0[pair_index] = -l_x0 / 1000. / v;
  return;
}

void E16ANA_TrackAnalyzerFromTree::FillKsTrackInfo() {
  if (particle_flag == cmn_param::kElectronFlag) {
    out_ks_pos_at_x0_gx.assign(n_pairs, -10000.);
    out_ks_pos_at_x0_gy.assign(n_pairs, -10000.);
    out_ks_pos_at_x0_gz.assign(n_pairs, -10000.);
    out_ks_mom_at_x0_gx.assign(n_pairs, -10000.);
    out_ks_mom_at_x0_gy.assign(n_pairs, -10000.);
    out_ks_mom_at_x0_gz.assign(n_pairs, -10000.);
    out_ks_t_at_x0.assign(n_pairs, -10000.);
  } else if (particle_flag == cmn_param::kPionFlag) {
    out_ks_pos_at_x0_gx.resize(n_pairs);
    out_ks_pos_at_x0_gy.resize(n_pairs);
    out_ks_pos_at_x0_gz.resize(n_pairs);
    out_ks_mom_at_x0_gx.resize(n_pairs);
    out_ks_mom_at_x0_gy.resize(n_pairs);
    out_ks_mom_at_x0_gz.resize(n_pairs);
    out_ks_t_at_x0.resize(n_pairs);
    for (int i = 0; i < n_pairs; ++i) {
      auto ks_pos = TVector3(out_vtx_gx[i], out_vtx_gy[i], out_vtx_gz[i]);
      auto ks_mom = TVector3(out_minus_mom_gx[i] + out_plus_mom_gx[i],
                             out_minus_mom_gy[i] + out_plus_mom_gy[i],
                             out_minus_mom_gz[i] + out_plus_mom_gz[i]);
      ProjectionX0(i, ks_pos, ks_mom);
    }
  }
  return;
}

void E16ANA_TrackAnalyzerFromTree::UpdateFitResult(const int track_indexs_index_pair[]) {
  int track_index_pair[2];
  for (int i = 0; i < 2; ++i) {
    auto tmp_i = track_indexs_index_pair[i];
    track_index_pair[i] = selected_track_indexs[tmp_i];
  }
  out_minus_track_id.emplace_back(track_id->at(track_index_pair[0]));
  out_plus_track_id.emplace_back(track_id->at(track_index_pair[1]));

  auto tmp_vtx       = pair_fitter->GetFitVertex();
  auto tmp_minus_mom = pair_fitter->GetFitMomentum(0);
  auto tmp_plus_mom  = pair_fitter->GetFitMomentum(1);
  FillTVector3ToDouble(tmp_vtx,       &out_vtx_gx,       &out_vtx_gy,       &out_vtx_gz);
  FillTVector3ToDouble(tmp_minus_mom, &out_minus_mom_gx, &out_minus_mom_gy, &out_minus_mom_gz);
  FillTVector3ToDouble(tmp_plus_mom,  &out_plus_mom_gx,  &out_plus_mom_gy,  &out_plus_mom_gz);
  out_minus_mom.emplace_back(tmp_minus_mom.Mag());
  out_plus_mom.emplace_back(tmp_plus_mom.Mag());
  int      mid[2][track_const::kNumTrackingLayers];
  TVector3 lpos[2][track_const::kNumTrackingLayers];
  TVector3 lmom[2][track_const::kNumTrackingLayers];
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
      lpos[track_index_in_pair][layer_index] = tmp_lpos[hid];
      lmom[track_index_in_pair][layer_index] = tmp_lmom[hid];
      if (layer_index == 0) {
        gpos[track_index_in_pair][layer_index] = geometry->SSD(tmp_mid[hid])->GetGPos(tmp_lpos[hid]);
        gmom[track_index_in_pair][layer_index] = geometry->SSD(tmp_mid[hid])->GetGMom(tmp_lmom[hid]);
      } else {
        gpos[track_index_in_pair][layer_index] = geometry->GTR(tmp_mid[hid], layer_index - 1)->GetGPos(tmp_lpos[hid]);
        gmom[track_index_in_pair][layer_index] = geometry->GTR(tmp_mid[hid], layer_index - 1)->GetGMom(tmp_lmom[hid]);
      }
      lres[track_index_in_pair][layer_index] = tmp_lres[hid];
    }
  }
  
  out_minus_ssd_mid.emplace_back(mid[0][0]);
  out_minus_gtr100_mid.emplace_back(mid[0][1]);
  out_minus_gtr200_mid.emplace_back(mid[0][2]);
  out_minus_gtr300_mid.emplace_back(mid[0][3]);
  out_minus_hbd_mid.emplace_back(rk_fit_hbd_mid->at(track_index_pair[0]));
  out_minus_lg_c_mid.emplace_back(rk_fit_lg_c_mid->at(track_index_pair[0]));
  out_minus_lg_b_mid.emplace_back(rk_fit_lg_b_mid->at(track_index_pair[0]));
  out_minus_lg_a_mid.emplace_back(rk_fit_lg_a_mid->at(track_index_pair[0]));
  out_plus_ssd_mid.emplace_back(mid[1][0]);
  out_plus_gtr100_mid.emplace_back(mid[1][1]);
  out_plus_gtr200_mid.emplace_back(mid[1][2]);
  out_plus_gtr300_mid.emplace_back(mid[1][3]);
  out_plus_hbd_mid.emplace_back(rk_fit_hbd_mid->at(track_index_pair[1]));
  out_plus_lg_c_mid.emplace_back(rk_fit_lg_c_mid->at(track_index_pair[1]));
  out_plus_lg_b_mid.emplace_back(rk_fit_lg_b_mid->at(track_index_pair[1]));
  out_plus_lg_a_mid.emplace_back(rk_fit_lg_a_mid->at(track_index_pair[1]));
  
  TVector3 hit_gpos[2][track_const::kNumTrackingLayers];
  TVector3 hit_lpos[2][track_const::kNumTrackingLayers];
  for (int i = 0; i < 2; ++i) {
    hit_gpos[i][0] = TVector3(rk_hit_ssd_gx->at(track_index_pair[i]),
                              rk_hit_ssd_gy->at(track_index_pair[i]),
                              rk_hit_ssd_gz->at(track_index_pair[i]));
    hit_gpos[i][1] = TVector3(rk_hit_gtr100_gx->at(track_index_pair[i]),
                              rk_hit_gtr100_gy->at(track_index_pair[i]),
                              rk_hit_gtr100_gz->at(track_index_pair[i]));
    hit_gpos[i][2] = TVector3(rk_hit_gtr200_gx->at(track_index_pair[i]),
                              rk_hit_gtr200_gy->at(track_index_pair[i]),
                              rk_hit_gtr200_gz->at(track_index_pair[i]));
    hit_gpos[i][3] = TVector3(rk_hit_gtr300_gx->at(track_index_pair[i]),
                              rk_hit_gtr300_gy->at(track_index_pair[i]),
                              rk_hit_gtr300_gz->at(track_index_pair[i]));
    hit_lpos[i][0] = geometry->SSD(track_const::ModuleID2020To2013(mid[i][0]))->GetLPos(hit_gpos[i][0]);
    hit_lpos[i][1] = geometry->GTR(track_const::ModuleID2020To2013(mid[i][1]), 0)->GetLPos(hit_gpos[i][1]);
    hit_lpos[i][2] = geometry->GTR(track_const::ModuleID2020To2013(mid[i][2]), 1)->GetLPos(hit_gpos[i][2]);
    hit_lpos[i][3] = geometry->GTR(track_const::ModuleID2020To2013(mid[i][3]), 2)->GetLPos(hit_gpos[i][3]);
  }
  FillTVector3ToDouble(hit_lpos[0][0], &out_minus_ssd_hit_x,     &out_minus_ssd_hit_y,     &out_minus_ssd_hit_z);
  FillTVector3ToDouble(hit_lpos[0][1], &out_minus_gtr100_hit_x,  &out_minus_gtr100_hit_y,  &out_minus_gtr100_hit_z);
  FillTVector3ToDouble(hit_lpos[0][2], &out_minus_gtr200_hit_x,  &out_minus_gtr200_hit_y,  &out_minus_gtr200_hit_z);
  FillTVector3ToDouble(hit_lpos[0][3], &out_minus_gtr300_hit_x,  &out_minus_gtr300_hit_y,  &out_minus_gtr300_hit_z);
  FillTVector3ToDouble(hit_lpos[1][0], &out_plus_ssd_hit_x,      &out_plus_ssd_hit_y,      &out_plus_ssd_hit_z);
  FillTVector3ToDouble(hit_lpos[1][1], &out_plus_gtr100_hit_x,   &out_plus_gtr100_hit_y,   &out_plus_gtr100_hit_z);
  FillTVector3ToDouble(hit_lpos[1][2], &out_plus_gtr200_hit_x,   &out_plus_gtr200_hit_y,   &out_plus_gtr200_hit_z);
  FillTVector3ToDouble(hit_lpos[1][3], &out_plus_gtr300_hit_x,   &out_plus_gtr300_hit_y,   &out_plus_gtr300_hit_z);
  FillTVector3ToDouble(hit_gpos[0][0], &out_minus_ssd_hit_gx,    &out_minus_ssd_hit_gy,    &out_minus_ssd_hit_gz);
  FillTVector3ToDouble(hit_gpos[0][1], &out_minus_gtr100_hit_gx, &out_minus_gtr100_hit_gy, &out_minus_gtr100_hit_gz);
  FillTVector3ToDouble(hit_gpos[0][2], &out_minus_gtr200_hit_gx, &out_minus_gtr200_hit_gy, &out_minus_gtr200_hit_gz);
  FillTVector3ToDouble(hit_gpos[0][3], &out_minus_gtr300_hit_gx, &out_minus_gtr300_hit_gy, &out_minus_gtr300_hit_gz);
  FillTVector3ToDouble(hit_gpos[1][0], &out_plus_ssd_hit_gx,     &out_plus_ssd_hit_gy,     &out_plus_ssd_hit_gz);
  FillTVector3ToDouble(hit_gpos[1][1], &out_plus_gtr100_hit_gx,  &out_plus_gtr100_hit_gy,  &out_plus_gtr100_hit_gz);
  FillTVector3ToDouble(hit_gpos[1][2], &out_plus_gtr200_hit_gx,  &out_plus_gtr200_hit_gy,  &out_plus_gtr200_hit_gz);
  FillTVector3ToDouble(hit_gpos[1][3], &out_plus_gtr300_hit_gx,  &out_plus_gtr300_hit_gy,  &out_plus_gtr300_hit_gz);

//  out_minus_ssd_hit_gx.emplace_back(rk_hit_ssd_gx->at(track_index_pair[0]));
//  out_minus_ssd_hit_gy.emplace_back(rk_hit_ssd_gy->at(track_index_pair[0]));
//  out_minus_ssd_hit_gz.emplace_back(rk_hit_ssd_gz->at(track_index_pair[0]));
  out_minus_ssd_hit_t.emplace_back(rk_hit_ssd_t->at(track_index_pair[0]));
  out_minus_ssd_hit_adc.emplace_back(rk_hit_ssd_adc->at(track_index_pair[0]));
//  out_minus_gtr100_hit_gx.emplace_back(rk_hit_gtr100_gx->at(track_index_pair[0]));
//  out_minus_gtr100_hit_gy.emplace_back(rk_hit_gtr100_gy->at(track_index_pair[0]));
//  out_minus_gtr100_hit_gz.emplace_back(rk_hit_gtr100_gz->at(track_index_pair[0]));
  out_minus_gtr100_hit_xt.emplace_back(rk_hit_gtr100_xt->at(track_index_pair[0]));
  out_minus_gtr100_hit_yt.emplace_back(rk_hit_gtr100_yt->at(track_index_pair[0]));
  out_minus_gtr100_hit_xadc.emplace_back(rk_hit_gtr100_xadc->at(track_index_pair[0]));
  out_minus_gtr100_hit_yadc.emplace_back(rk_hit_gtr100_yadc->at(track_index_pair[0]));
//  out_minus_gtr200_hit_gx.emplace_back(rk_hit_gtr200_gx->at(track_index_pair[0]));
//  out_minus_gtr200_hit_gy.emplace_back(rk_hit_gtr200_gy->at(track_index_pair[0]));
//  out_minus_gtr200_hit_gz.emplace_back(rk_hit_gtr200_gz->at(track_index_pair[0]));
  out_minus_gtr200_hit_xt.emplace_back(rk_hit_gtr200_xt->at(track_index_pair[0]));
  out_minus_gtr200_hit_yt.emplace_back(rk_hit_gtr200_yt->at(track_index_pair[0]));
  out_minus_gtr200_hit_xadc.emplace_back(rk_hit_gtr200_xadc->at(track_index_pair[0]));
  out_minus_gtr200_hit_yadc.emplace_back(rk_hit_gtr200_yadc->at(track_index_pair[0]));
//  out_minus_gtr300_hit_gx.emplace_back(rk_hit_gtr300_gx->at(track_index_pair[0]));
//  out_minus_gtr300_hit_gy.emplace_back(rk_hit_gtr300_gy->at(track_index_pair[0]));
//  out_minus_gtr300_hit_gz.emplace_back(rk_hit_gtr300_gz->at(track_index_pair[0]));
  out_minus_gtr300_hit_xt.emplace_back(rk_hit_gtr300_xt->at(track_index_pair[0]));
  out_minus_gtr300_hit_yt.emplace_back(rk_hit_gtr300_yt->at(track_index_pair[0]));
  out_minus_gtr300_hit_xadc.emplace_back(rk_hit_gtr300_xadc->at(track_index_pair[0]));
  out_minus_gtr300_hit_yadc.emplace_back(rk_hit_gtr300_yadc->at(track_index_pair[0]));
//  out_plus_ssd_hit_gx.emplace_back(rk_hit_ssd_gx->at(track_index_pair[1]));
//  out_plus_ssd_hit_gy.emplace_back(rk_hit_ssd_gy->at(track_index_pair[1]));
//  out_plus_ssd_hit_gz.emplace_back(rk_hit_ssd_gz->at(track_index_pair[1]));
  out_plus_ssd_hit_t.emplace_back(rk_hit_ssd_t->at(track_index_pair[1]));
  out_plus_ssd_hit_adc.emplace_back(rk_hit_ssd_adc->at(track_index_pair[1]));
//  out_plus_gtr100_hit_gx.emplace_back(rk_hit_gtr100_gx->at(track_index_pair[1]));
//  out_plus_gtr100_hit_gy.emplace_back(rk_hit_gtr100_gy->at(track_index_pair[1]));
//  out_plus_gtr100_hit_gz.emplace_back(rk_hit_gtr100_gz->at(track_index_pair[1]));
  out_plus_gtr100_hit_xt.emplace_back(rk_hit_gtr100_xt->at(track_index_pair[1]));
  out_plus_gtr100_hit_yt.emplace_back(rk_hit_gtr100_yt->at(track_index_pair[1]));
  out_plus_gtr100_hit_xadc.emplace_back(rk_hit_gtr100_xadc->at(track_index_pair[1]));
  out_plus_gtr100_hit_yadc.emplace_back(rk_hit_gtr100_yadc->at(track_index_pair[1]));
//  out_plus_gtr200_hit_gx.emplace_back(rk_hit_gtr200_gx->at(track_index_pair[1]));
//  out_plus_gtr200_hit_gy.emplace_back(rk_hit_gtr200_gy->at(track_index_pair[1]));
//  out_plus_gtr200_hit_gz.emplace_back(rk_hit_gtr200_gz->at(track_index_pair[1]));
  out_plus_gtr200_hit_xt.emplace_back(rk_hit_gtr200_xt->at(track_index_pair[1]));
  out_plus_gtr200_hit_yt.emplace_back(rk_hit_gtr200_yt->at(track_index_pair[1]));
  out_plus_gtr200_hit_xadc.emplace_back(rk_hit_gtr200_xadc->at(track_index_pair[1]));
  out_plus_gtr200_hit_yadc.emplace_back(rk_hit_gtr200_yadc->at(track_index_pair[1]));
//  out_plus_gtr300_hit_gx.emplace_back(rk_hit_gtr300_gx->at(track_index_pair[1]));
//  out_plus_gtr300_hit_gy.emplace_back(rk_hit_gtr300_gy->at(track_index_pair[1]));
//  out_plus_gtr300_hit_gz.emplace_back(rk_hit_gtr300_gz->at(track_index_pair[1]));
  out_plus_gtr300_hit_xt.emplace_back(rk_hit_gtr300_xt->at(track_index_pair[1]));
  out_plus_gtr300_hit_yt.emplace_back(rk_hit_gtr300_yt->at(track_index_pair[1]));
  out_plus_gtr300_hit_xadc.emplace_back(rk_hit_gtr300_xadc->at(track_index_pair[1]));
  out_plus_gtr300_hit_yadc.emplace_back(rk_hit_gtr300_yadc->at(track_index_pair[1]));
  FillTVector3ToDouble(lpos[0][0], &out_minus_ssd_fit_x,     &out_minus_ssd_fit_y,     &out_minus_ssd_fit_z);
  FillTVector3ToDouble(lpos[0][1], &out_minus_gtr100_fit_x,  &out_minus_gtr100_fit_y,  &out_minus_gtr100_fit_z);
  FillTVector3ToDouble(lpos[0][2], &out_minus_gtr200_fit_x,  &out_minus_gtr200_fit_y,  &out_minus_gtr200_fit_z);
  FillTVector3ToDouble(lpos[0][3], &out_minus_gtr300_fit_x,  &out_minus_gtr300_fit_y,  &out_minus_gtr300_fit_z);
  FillTVector3ToDouble(lpos[1][0], &out_plus_ssd_fit_x,      &out_plus_ssd_fit_y,      &out_plus_ssd_fit_z);
  FillTVector3ToDouble(lpos[1][1], &out_plus_gtr100_fit_x,   &out_plus_gtr100_fit_y,   &out_plus_gtr100_fit_z);
  FillTVector3ToDouble(lpos[1][2], &out_plus_gtr200_fit_x,   &out_plus_gtr200_fit_y,   &out_plus_gtr200_fit_z);
  FillTVector3ToDouble(lpos[1][3], &out_plus_gtr300_fit_x,   &out_plus_gtr300_fit_y,   &out_plus_gtr300_fit_z);
  FillTVector3ToDouble(gpos[0][0], &out_minus_ssd_fit_gx,    &out_minus_ssd_fit_gy,    &out_minus_ssd_fit_gz);
  FillTVector3ToDouble(gpos[0][1], &out_minus_gtr100_fit_gx, &out_minus_gtr100_fit_gy, &out_minus_gtr100_fit_gz);
  FillTVector3ToDouble(gpos[0][2], &out_minus_gtr200_fit_gx, &out_minus_gtr200_fit_gy, &out_minus_gtr200_fit_gz);
  FillTVector3ToDouble(gpos[0][3], &out_minus_gtr300_fit_gx, &out_minus_gtr300_fit_gy, &out_minus_gtr300_fit_gz);
  FillTVector3ToDouble(gpos[1][0], &out_plus_ssd_fit_gx,     &out_plus_ssd_fit_gy,     &out_plus_ssd_fit_gz);
  FillTVector3ToDouble(gpos[1][1], &out_plus_gtr100_fit_gx,  &out_plus_gtr100_fit_gy,  &out_plus_gtr100_fit_gz);
  FillTVector3ToDouble(gpos[1][2], &out_plus_gtr200_fit_gx,  &out_plus_gtr200_fit_gy,  &out_plus_gtr200_fit_gz);
  FillTVector3ToDouble(gpos[1][3], &out_plus_gtr300_fit_gx,  &out_plus_gtr300_fit_gy,  &out_plus_gtr300_fit_gz);
  FillTVector3ToDouble(lmom[0][0], &out_minus_ssd_fit_mom_x,    &out_minus_ssd_fit_mom_y,    &out_minus_ssd_fit_mom_z);
  FillTVector3ToDouble(lmom[0][1], &out_minus_gtr100_fit_mom_x, &out_minus_gtr100_fit_mom_y, &out_minus_gtr100_fit_mom_z);
  FillTVector3ToDouble(lmom[0][2], &out_minus_gtr200_fit_mom_x, &out_minus_gtr200_fit_mom_y, &out_minus_gtr200_fit_mom_z);
  FillTVector3ToDouble(lmom[0][3], &out_minus_gtr300_fit_mom_x, &out_minus_gtr300_fit_mom_y, &out_minus_gtr300_fit_mom_z);
  FillTVector3ToDouble(lmom[1][0], &out_plus_ssd_fit_mom_x,     &out_plus_ssd_fit_mom_y,     &out_plus_ssd_fit_mom_z);
  FillTVector3ToDouble(lmom[1][1], &out_plus_gtr100_fit_mom_x,  &out_plus_gtr100_fit_mom_y,  &out_plus_gtr100_fit_mom_z);
  FillTVector3ToDouble(lmom[1][2], &out_plus_gtr200_fit_mom_x,  &out_plus_gtr200_fit_mom_y,  &out_plus_gtr200_fit_mom_z);
  FillTVector3ToDouble(lmom[1][3], &out_plus_gtr300_fit_mom_x,  &out_plus_gtr300_fit_mom_y,  &out_plus_gtr300_fit_mom_z);
  FillTVector3ToDouble(gmom[0][0], &out_minus_ssd_fit_mom_gx,    &out_minus_ssd_fit_mom_gy,    &out_minus_ssd_fit_mom_gz);
  FillTVector3ToDouble(gmom[0][1], &out_minus_gtr100_fit_mom_gx, &out_minus_gtr100_fit_mom_gy, &out_minus_gtr100_fit_mom_gz);
  FillTVector3ToDouble(gmom[0][2], &out_minus_gtr200_fit_mom_gx, &out_minus_gtr200_fit_mom_gy, &out_minus_gtr200_fit_mom_gz);
  FillTVector3ToDouble(gmom[0][3], &out_minus_gtr300_fit_mom_gx, &out_minus_gtr300_fit_mom_gy, &out_minus_gtr300_fit_mom_gz);
  FillTVector3ToDouble(gmom[1][0], &out_plus_ssd_fit_mom_gx,     &out_plus_ssd_fit_mom_gy,     &out_plus_ssd_fit_mom_gz);
  FillTVector3ToDouble(gmom[1][1], &out_plus_gtr100_fit_mom_gx,  &out_plus_gtr100_fit_mom_gy,  &out_plus_gtr100_fit_mom_gz);
  FillTVector3ToDouble(gmom[1][2], &out_plus_gtr200_fit_mom_gx,  &out_plus_gtr200_fit_mom_gy,  &out_plus_gtr200_fit_mom_gz);
  FillTVector3ToDouble(gmom[1][3], &out_plus_gtr300_fit_mom_gx,  &out_plus_gtr300_fit_mom_gy,  &out_plus_gtr300_fit_mom_gz);
  out_minus_ssd_fit_mom_tan.emplace_back(lmom[0][0](0) / lmom[0][0](2));
  out_minus_gtr100_fit_mom_tan.emplace_back(lmom[0][1](0) / lmom[0][1](2));
  out_minus_gtr200_fit_mom_tan.emplace_back(lmom[0][2](0) / lmom[0][2](2));
  out_minus_gtr300_fit_mom_tan.emplace_back(lmom[0][3](0) / lmom[0][3](2));
  out_plus_ssd_fit_mom_tan.emplace_back(lmom[1][0](0) / lmom[1][0](2));
  out_plus_gtr100_fit_mom_tan.emplace_back(lmom[1][1](0) / lmom[1][1](2));
  out_plus_gtr200_fit_mom_tan.emplace_back(lmom[1][2](0) / lmom[1][2](2));
  out_plus_gtr300_fit_mom_tan.emplace_back(lmom[1][3](0) / lmom[1][3](2));
  out_minus_ssd_res.emplace_back(lres[0][0].Mag());
  out_minus_gtr100_res.emplace_back(lres[0][1].Mag());
  out_minus_gtr200_res.emplace_back(lres[0][2].Mag());
  out_minus_gtr300_res.emplace_back(lres[0][3].Mag());
  out_plus_ssd_res.emplace_back(lres[1][0].Mag());
  out_plus_gtr100_res.emplace_back(lres[1][1].Mag());
  out_plus_gtr200_res.emplace_back(lres[1][2].Mag());
  out_plus_gtr300_res.emplace_back(lres[1][3].Mag());
  FillTVector3ToDouble(lres[0][0], &out_minus_ssd_res_x,     &out_minus_ssd_res_y,     &out_minus_ssd_res_z);
  FillTVector3ToDouble(lres[0][1], &out_minus_gtr100_res_x,  &out_minus_gtr100_res_y,  &out_minus_gtr100_res_z);
  FillTVector3ToDouble(lres[0][2], &out_minus_gtr200_res_x,  &out_minus_gtr200_res_y,  &out_minus_gtr200_res_z);
  FillTVector3ToDouble(lres[0][3], &out_minus_gtr300_res_x,  &out_minus_gtr300_res_y,  &out_minus_gtr300_res_z);
  FillTVector3ToDouble(lres[1][0], &out_plus_ssd_res_x,      &out_plus_ssd_res_y,      &out_plus_ssd_res_z);
  FillTVector3ToDouble(lres[1][1], &out_plus_gtr100_res_x,   &out_plus_gtr100_res_y,   &out_plus_gtr100_res_z);
  FillTVector3ToDouble(lres[1][2], &out_plus_gtr200_res_x,   &out_plus_gtr200_res_y,   &out_plus_gtr200_res_z);
  FillTVector3ToDouble(lres[1][3], &out_plus_gtr300_res_x,   &out_plus_gtr300_res_y,   &out_plus_gtr300_res_z);

  TVector3 tmp_lposs[2][4];
  TVector3 tmp_gposs[2][4];
  TVector3 tmp_lmoms[2][4];
  TVector3 tmp_gmoms[2][4];
  ProjectionHBDAndLG(tmp_vtx, tmp_minus_mom, -1, track_index_pair[0], tmp_lposs[0], tmp_gposs[0], tmp_lmoms[0], tmp_gmoms[0]);
  FillTVector3ToDouble(tmp_lposs[0][0], &out_minus_hbd_fit_x,       &out_minus_hbd_fit_y,       &out_minus_hbd_fit_z);
  FillTVector3ToDouble(tmp_gposs[0][0], &out_minus_hbd_fit_gx,      &out_minus_hbd_fit_gy,      &out_minus_hbd_fit_gz);
  FillTVector3ToDouble(tmp_lmoms[0][0], &out_minus_hbd_fit_mom_x,   &out_minus_hbd_fit_mom_y,   &out_minus_hbd_fit_mom_z);
  FillTVector3ToDouble(tmp_gmoms[0][0], &out_minus_hbd_fit_mom_gx,  &out_minus_hbd_fit_mom_gy,  &out_minus_hbd_fit_mom_gz);
  FillTVector3ToDouble(tmp_lposs[0][1], &out_minus_lg_c_fit_x,      &out_minus_lg_c_fit_y,      &out_minus_lg_c_fit_z);
  FillTVector3ToDouble(tmp_gposs[0][1], &out_minus_lg_c_fit_gx,     &out_minus_lg_c_fit_gy,     &out_minus_lg_c_fit_gz);
  FillTVector3ToDouble(tmp_lmoms[0][1], &out_minus_lg_c_fit_mom_x,  &out_minus_lg_c_fit_mom_y,  &out_minus_lg_c_fit_mom_z);
  FillTVector3ToDouble(tmp_gmoms[0][1], &out_minus_lg_c_fit_mom_gx, &out_minus_lg_c_fit_mom_gy, &out_minus_lg_c_fit_mom_gz);
  FillTVector3ToDouble(tmp_lposs[0][2], &out_minus_lg_b_fit_x,      &out_minus_lg_b_fit_y,      &out_minus_lg_b_fit_z);
  FillTVector3ToDouble(tmp_gposs[0][2], &out_minus_lg_b_fit_gx,     &out_minus_lg_b_fit_gy,     &out_minus_lg_b_fit_gz);
  FillTVector3ToDouble(tmp_lmoms[0][2], &out_minus_lg_b_fit_mom_x,  &out_minus_lg_b_fit_mom_y,  &out_minus_lg_b_fit_mom_z);
  FillTVector3ToDouble(tmp_gmoms[0][2], &out_minus_lg_b_fit_mom_gx, &out_minus_lg_b_fit_mom_gy, &out_minus_lg_b_fit_mom_gz);
  FillTVector3ToDouble(tmp_lposs[0][3], &out_minus_lg_a_fit_x,      &out_minus_lg_a_fit_y,      &out_minus_lg_a_fit_z);
  FillTVector3ToDouble(tmp_gposs[0][3], &out_minus_lg_a_fit_gx,     &out_minus_lg_a_fit_gy,     &out_minus_lg_a_fit_gz);
  FillTVector3ToDouble(tmp_lmoms[0][3], &out_minus_lg_a_fit_mom_x,  &out_minus_lg_a_fit_mom_y,  &out_minus_lg_a_fit_mom_z);
  FillTVector3ToDouble(tmp_gmoms[0][3], &out_minus_lg_a_fit_mom_gx, &out_minus_lg_a_fit_mom_gy, &out_minus_lg_a_fit_mom_gz);
  out_minus_hbd_fit_mom_tan.emplace_back(tmp_lmoms[0][0](0) / tmp_lmoms[0][0](2));
  out_minus_lg_c_fit_mom_tan.emplace_back(tmp_lmoms[0][1](0) / tmp_lmoms[0][1](2));
  out_minus_lg_b_fit_mom_tan.emplace_back(tmp_lmoms[0][2](0) / tmp_lmoms[0][2](2));
  out_minus_lg_a_fit_mom_tan.emplace_back(tmp_lmoms[0][3](0) / tmp_lmoms[0][3](2));
  ProjectionHBDAndLG(tmp_vtx, tmp_plus_mom, 1, track_index_pair[1], tmp_lposs[1], tmp_gposs[1], tmp_lmoms[1], tmp_gmoms[1]);
  FillTVector3ToDouble(tmp_lposs[1][0], &out_plus_hbd_fit_x,       &out_plus_hbd_fit_y,       &out_plus_hbd_fit_z);
  FillTVector3ToDouble(tmp_gposs[1][0], &out_plus_hbd_fit_gx,      &out_plus_hbd_fit_gy,      &out_plus_hbd_fit_gz);
  FillTVector3ToDouble(tmp_lmoms[1][0], &out_plus_hbd_fit_mom_x,   &out_plus_hbd_fit_mom_y,   &out_plus_hbd_fit_mom_z);
  FillTVector3ToDouble(tmp_gmoms[1][0], &out_plus_hbd_fit_mom_gx,  &out_plus_hbd_fit_mom_gy,  &out_plus_hbd_fit_mom_gz);
  FillTVector3ToDouble(tmp_lposs[1][1], &out_plus_lg_c_fit_x,      &out_plus_lg_c_fit_y,      &out_plus_lg_c_fit_z);
  FillTVector3ToDouble(tmp_gposs[1][1], &out_plus_lg_c_fit_gx,     &out_plus_lg_c_fit_gy,     &out_plus_lg_c_fit_gz);
  FillTVector3ToDouble(tmp_lmoms[1][1], &out_plus_lg_c_fit_mom_x,  &out_plus_lg_c_fit_mom_y,  &out_plus_lg_c_fit_mom_z);
  FillTVector3ToDouble(tmp_gmoms[1][1], &out_plus_lg_c_fit_mom_gx, &out_plus_lg_c_fit_mom_gy, &out_plus_lg_c_fit_mom_gz);
  FillTVector3ToDouble(tmp_lposs[1][2], &out_plus_lg_b_fit_x,      &out_plus_lg_b_fit_y,      &out_plus_lg_b_fit_z);
  FillTVector3ToDouble(tmp_gposs[1][2], &out_plus_lg_b_fit_gx,     &out_plus_lg_b_fit_gy,     &out_plus_lg_b_fit_gz);
  FillTVector3ToDouble(tmp_lmoms[1][2], &out_plus_lg_b_fit_mom_x,  &out_plus_lg_b_fit_mom_y,  &out_plus_lg_b_fit_mom_z);
  FillTVector3ToDouble(tmp_gmoms[1][2], &out_plus_lg_b_fit_mom_gx, &out_plus_lg_b_fit_mom_gy, &out_plus_lg_b_fit_mom_gz);
  FillTVector3ToDouble(tmp_lposs[1][3], &out_plus_lg_a_fit_x,      &out_plus_lg_a_fit_y,      &out_plus_lg_a_fit_z);
  FillTVector3ToDouble(tmp_gposs[1][3], &out_plus_lg_a_fit_gx,     &out_plus_lg_a_fit_gy,     &out_plus_lg_a_fit_gz);
  FillTVector3ToDouble(tmp_lmoms[1][3], &out_plus_lg_a_fit_mom_x,  &out_plus_lg_a_fit_mom_y,  &out_plus_lg_a_fit_mom_z);
  FillTVector3ToDouble(tmp_gmoms[1][3], &out_plus_lg_a_fit_mom_gx, &out_plus_lg_a_fit_mom_gy, &out_plus_lg_a_fit_mom_gz);
  out_plus_hbd_fit_mom_tan.emplace_back(tmp_lmoms[1][0](0) / tmp_lmoms[1][0](2));
  out_plus_lg_c_fit_mom_tan.emplace_back(tmp_lmoms[1][1](0) / tmp_lmoms[1][1](2));
  out_plus_lg_b_fit_mom_tan.emplace_back(tmp_lmoms[1][2](0) / tmp_lmoms[1][2](2));
  out_plus_lg_a_fit_mom_tan.emplace_back(tmp_lmoms[1][3](0) / tmp_lmoms[1][3](2));
  
  std::vector<int> hbd_clst_indexs[2];
  HasHBDClusters(out_minus_hbd_mid.back(), tmp_lposs[0][0], &hbd_clst_indexs[0]);
  out_minus_proj_n_hbd_clusters.emplace_back(hbd_clst_indexs[0].size());
  out_minus_proj_hbd_cluster_x.emplace_back(std::vector<double>());
  out_minus_proj_hbd_cluster_y.emplace_back(std::vector<double>());
  out_minus_proj_hbd_cluster_res.emplace_back(std::vector<double>());
  out_minus_proj_hbd_cluster_res_x.emplace_back(std::vector<double>());
  out_minus_proj_hbd_cluster_res_y.emplace_back(std::vector<double>());
  out_minus_proj_hbd_cluster_adc.emplace_back(std::vector<double>());
  out_minus_proj_hbd_cluster_t.emplace_back(std::vector<double>());
  out_minus_proj_hbd_cluster_eprob.emplace_back(std::vector<double>());
  HasHBDClusters(out_plus_hbd_mid.back(), tmp_lposs[1][0], &hbd_clst_indexs[1]);
  out_plus_proj_n_hbd_clusters.emplace_back(hbd_clst_indexs[1].size());
  out_plus_proj_hbd_cluster_x.emplace_back(std::vector<double>());
  out_plus_proj_hbd_cluster_y.emplace_back(std::vector<double>());
  out_plus_proj_hbd_cluster_res.emplace_back(std::vector<double>());
  out_plus_proj_hbd_cluster_res_x.emplace_back(std::vector<double>());
  out_plus_proj_hbd_cluster_res_y.emplace_back(std::vector<double>());
  out_plus_proj_hbd_cluster_adc.emplace_back(std::vector<double>());
  out_plus_proj_hbd_cluster_t.emplace_back(std::vector<double>());
  out_plus_proj_hbd_cluster_eprob.emplace_back(std::vector<double>());
  out_plus_proj_hbd_cluster_cprob.emplace_back(std::vector<double>());
  bool tmp_has_e = false;
  for (const auto& index : hbd_clst_indexs[0]) {
    auto& x     = out_minus_proj_hbd_cluster_x.back();
    auto& y     = out_minus_proj_hbd_cluster_y.back();
    auto& res   = out_minus_proj_hbd_cluster_res.back();
    auto& res_x = out_minus_proj_hbd_cluster_res_x.back();
    auto& res_y = out_minus_proj_hbd_cluster_res_y.back();
    auto& adc   = out_minus_proj_hbd_cluster_adc.back();
    auto& t     = out_minus_proj_hbd_cluster_t.back();
    auto& eprob = out_minus_proj_hbd_cluster_eprob.back();
    auto& cprob = out_minus_proj_hbd_cluster_cprob.back();
    auto tmp_x = hbd_cluster_x->at(index);
    auto tmp_y = hbd_cluster_y->at(index);
    x.emplace_back(tmp_x);
    y.emplace_back(tmp_y);
    auto tmp_res_x = tmp_x - tmp_lposs[0][0].X();
    auto tmp_res_y = tmp_y - tmp_lposs[0][0].Y();
    res.emplace_back(sqrt(tmp_res_x * tmp_res_x + tmp_res_y * tmp_res_y));
    res_x.emplace_back(tmp_res_x);
    res_y.emplace_back(tmp_res_y);
    adc.emplace_back(hbd_cluster_adc->at(index));
    t.emplace_back(hbd_cluster_t->at(index));
    eprob.emplace_back(hbd_cluster_eprob->at(index));
    cprob.emplace_back(hbd_cluster_cprob->at(index));
    if (eprob.back() > 0.5) {
      tmp_has_e = true;
    }
  }
  out_minus_proj_has_hbd_cluster_e.emplace_back(tmp_has_e);
  tmp_has_e = false;
  for (const auto& index : hbd_clst_indexs[1]) {
    auto& x     = out_plus_proj_hbd_cluster_x.back();
    auto& y     = out_plus_proj_hbd_cluster_y.back();
    auto& res   = out_plus_proj_hbd_cluster_res.back();
    auto& res_x = out_plus_proj_hbd_cluster_res_x.back();
    auto& res_y = out_plus_proj_hbd_cluster_res_y.back();
    auto& adc   = out_plus_proj_hbd_cluster_adc.back();
    auto& t     = out_plus_proj_hbd_cluster_t.back();
    auto& eprob = out_plus_proj_hbd_cluster_eprob.back();
    auto& cprob = out_plus_proj_hbd_cluster_cprob.back();
    auto tmp_x = hbd_cluster_x->at(index);
    auto tmp_y = hbd_cluster_y->at(index);
    x.emplace_back(tmp_x);
    y.emplace_back(tmp_y);
    auto tmp_res_x = tmp_x - tmp_lposs[1][0].X();
    auto tmp_res_y = tmp_y - tmp_lposs[1][0].Y();
    res.emplace_back(sqrt(tmp_res_x * tmp_res_x + tmp_res_y * tmp_res_y));
    res_x.emplace_back(tmp_res_x);
    res_y.emplace_back(tmp_res_y);
    adc.emplace_back(hbd_cluster_adc->at(index));
    t.emplace_back(hbd_cluster_t->at(index));
    eprob.emplace_back(hbd_cluster_eprob->at(index));
    cprob.emplace_back(hbd_cluster_cprob->at(index));
    if (eprob.back() > 0.5) {
      tmp_has_e = true;
    }
  }
  out_plus_proj_has_hbd_cluster_e.emplace_back(tmp_has_e);

  std::vector<int> lg_hit_indexs[2];
  std::vector<int> lg_clst_indexs[2];
  int    track_lg_mids[2][cmn_param::kNumLGTypes] = {{out_minus_lg_c_mid.back(),  out_minus_lg_b_mid.back(),  out_minus_lg_a_mid.back()},
                                                     {out_plus_lg_c_mid.back(),   out_plus_lg_b_mid.back(),   out_plus_lg_a_mid.back()}};
  double track_lg_xs[2][cmn_param::kNumLGTypes]  = {{tmp_lposs[0][1].X(),         tmp_lposs[0][2].X(),        tmp_lposs[0][3].X()},
                                                    {tmp_lposs[1][1].X(),         tmp_lposs[1][2].X(),        tmp_lposs[1][3].X()}};
  double track_lg_ys[2][cmn_param::kNumLGTypes]  = {{tmp_lposs[0][1].Y(),         tmp_lposs[0][2].Y(),        tmp_lposs[0][3].Y()},
                                                    {tmp_lposs[1][1].Y(),         tmp_lposs[1][2].Y(),        tmp_lposs[1][3].Y()}};
  bool track_lg_valids[2][cmn_param::kNumLGTypes];
  IsTrackLGValidY(track_lg_ys[0], track_lg_valids[0]);
  IsTrackLGValidY(track_lg_ys[1], track_lg_valids[1]);
  HasLGHits(tmp_minus_mom.Mag(),     track_lg_mids[0], track_lg_xs[0], track_lg_valids[0], &lg_hit_indexs[0]);
  HasLGHits(tmp_plus_mom.Mag(),      track_lg_mids[1], track_lg_xs[1], track_lg_valids[1], &lg_hit_indexs[1]);
  HasLGClusters(tmp_minus_mom.Mag(), track_lg_mids[0], track_lg_xs[0], track_lg_valids[0], &lg_clst_indexs[0]);
  HasLGClusters(tmp_plus_mom.Mag(),  track_lg_mids[1], track_lg_xs[1], track_lg_valids[1], &lg_clst_indexs[1]);
  out_minus_proj_n_lg_hits.emplace_back(lg_hit_indexs[0].size());
  out_minus_proj_lg_hit_x.emplace_back(std::vector<double>());
  out_minus_proj_lg_hit_y.emplace_back(std::vector<double>());
  out_minus_proj_lg_hit_z.emplace_back(std::vector<double>());
  out_minus_proj_lg_hit_type.emplace_back(std::vector<double>());
  out_minus_proj_lg_hit_res.emplace_back(std::vector<double>());
  out_minus_proj_lg_hit_res_x.emplace_back(std::vector<double>());
  out_minus_proj_lg_hit_res_y.emplace_back(std::vector<double>());
  out_minus_proj_lg_hit_adc.emplace_back(std::vector<double>());
  out_minus_proj_lg_hit_t.emplace_back(std::vector<double>());
  out_minus_proj_lg_hit_ise.emplace_back(std::vector<double>());
  out_plus_proj_n_lg_hits.emplace_back(lg_hit_indexs[1].size());
  out_plus_proj_lg_hit_x.emplace_back(std::vector<double>());
  out_plus_proj_lg_hit_y.emplace_back(std::vector<double>());
  out_plus_proj_lg_hit_z.emplace_back(std::vector<double>());
  out_plus_proj_lg_hit_type.emplace_back(std::vector<double>());
  out_plus_proj_lg_hit_res.emplace_back(std::vector<double>());
  out_plus_proj_lg_hit_res_x.emplace_back(std::vector<double>());
  out_plus_proj_lg_hit_res_y.emplace_back(std::vector<double>());
  out_plus_proj_lg_hit_adc.emplace_back(std::vector<double>());
  out_plus_proj_lg_hit_t.emplace_back(std::vector<double>());
  out_plus_proj_lg_hit_ise.emplace_back(std::vector<double>());
  out_minus_proj_n_lg_clusters.emplace_back(lg_clst_indexs[0].size());
  out_minus_proj_lg_cluster_x.emplace_back(std::vector<double>());
  out_minus_proj_lg_cluster_y.emplace_back(std::vector<double>());
  out_minus_proj_lg_cluster_z.emplace_back(std::vector<double>());
  out_minus_proj_lg_cluster_type.emplace_back(std::vector<double>());
  out_minus_proj_lg_cluster_res.emplace_back(std::vector<double>());
  out_minus_proj_lg_cluster_res_x.emplace_back(std::vector<double>());
  out_minus_proj_lg_cluster_res_y.emplace_back(std::vector<double>());
  out_minus_proj_lg_cluster_adc.emplace_back(std::vector<double>());
  out_minus_proj_lg_cluster_t.emplace_back(std::vector<double>());
  out_minus_proj_lg_cluster_ise.emplace_back(std::vector<double>());
  out_plus_proj_n_lg_clusters.emplace_back(lg_clst_indexs[1].size());
  out_plus_proj_lg_cluster_x.emplace_back(std::vector<double>());
  out_plus_proj_lg_cluster_y.emplace_back(std::vector<double>());
  out_plus_proj_lg_cluster_z.emplace_back(std::vector<double>());
  out_plus_proj_lg_cluster_type.emplace_back(std::vector<double>());
  out_plus_proj_lg_cluster_res.emplace_back(std::vector<double>());
  out_plus_proj_lg_cluster_res_x.emplace_back(std::vector<double>());
  out_plus_proj_lg_cluster_res_y.emplace_back(std::vector<double>());
  out_plus_proj_lg_cluster_adc.emplace_back(std::vector<double>());
  out_plus_proj_lg_cluster_t.emplace_back(std::vector<double>());
  out_plus_proj_lg_cluster_ise.emplace_back(std::vector<double>());
  tmp_has_e = false;
  for (const auto& index : lg_hit_indexs[0]) {
    auto& x     = out_minus_proj_lg_hit_x.back();
    auto& y     = out_minus_proj_lg_hit_y.back();
    auto& z     = out_minus_proj_lg_hit_z.back();
    auto& type  = out_minus_proj_lg_hit_type.back();
    auto& res   = out_minus_proj_lg_hit_res.back();
    auto& res_x = out_minus_proj_lg_hit_res_x.back();
    auto& res_y = out_minus_proj_lg_hit_res_y.back();
    auto& adc   = out_minus_proj_lg_hit_adc.back();
    auto& t     = out_minus_proj_lg_hit_t.back();
    auto& ise   = out_minus_proj_lg_hit_ise.back();
    auto tmp_x     = lg_hit_x->at(index);
    auto tmp_y     = lg_hit_y->at(index);
    auto tmp_z     = lg_hit_z->at(index);
    int  tmp_cid_y = int{lg_hit_cid->at(index)} / 10;
    int  tmp_type;
    if (tmp_cid_y == 0 || tmp_cid_y == 5) {
      tmp_type = cmn_param::kLGTypeC;
    } else if (tmp_cid_y == 1 || tmp_cid_y == 4) {
      tmp_type = cmn_param::kLGTypeB;
    } else if (tmp_cid_y == 2 || tmp_cid_y == 3) {
      tmp_type = cmn_param::kLGTypeA;
    } else {
      tmp_type = cmn_param::kNumLGTypes;
      continue;
    }
    type.emplace_back(tmp_type);
    x.emplace_back(tmp_x);
    y.emplace_back(tmp_y);
    z.emplace_back(tmp_z);
    auto tmp_res_x = tmp_x - track_lg_xs[0][tmp_type];
    auto tmp_res_y = tmp_y - track_lg_ys[0][tmp_type];
    res.emplace_back(sqrt(tmp_res_x * tmp_res_x + tmp_res_y * tmp_res_y));
    res_x.emplace_back(tmp_res_x);
    res_y.emplace_back(tmp_res_y);
    adc.emplace_back(lg_hit_adc->at(index));
    t.emplace_back(lg_hit_t->at(index));
    ise.emplace_back(E16DST_DST1LGHit::IsE(tmp_minus_mom.Mag(), lg_hit_adc->at(index)));
    if (ise.back() > 0.5) {
      tmp_has_e = true;
    }
  }
  out_minus_proj_has_lg_hit_e.emplace_back(tmp_has_e);
  tmp_has_e = false;
  for (const auto& index : lg_hit_indexs[1]) {
    auto& x     = out_plus_proj_lg_hit_x.back();
    auto& y     = out_plus_proj_lg_hit_y.back();
    auto& z     = out_plus_proj_lg_hit_z.back();
    auto& type  = out_plus_proj_lg_hit_type.back();
    auto& res   = out_plus_proj_lg_hit_res.back();
    auto& res_x = out_plus_proj_lg_hit_res_x.back();
    auto& res_y = out_plus_proj_lg_hit_res_y.back();
    auto& adc   = out_plus_proj_lg_hit_adc.back();
    auto& t     = out_plus_proj_lg_hit_t.back();
    auto& ise   = out_plus_proj_lg_hit_ise.back();
    auto tmp_x     = lg_hit_x->at(index);
    auto tmp_y     = lg_hit_y->at(index);
    auto tmp_z     = lg_hit_z->at(index);
    int  tmp_cid_y = int{lg_hit_cid->at(index)} / 10;
    int  tmp_type;
    if (tmp_cid_y == 0 || tmp_cid_y == 5) {
      tmp_type = cmn_param::kLGTypeC;
    } else if (tmp_cid_y == 1 || tmp_cid_y == 4) {
      tmp_type = cmn_param::kLGTypeB;
    } else if (tmp_cid_y == 2 || tmp_cid_y == 3) {
      tmp_type = cmn_param::kLGTypeA;
    } else {
      tmp_type = cmn_param::kNumLGTypes;
      continue;
    }
    type.emplace_back(tmp_type);
    x.emplace_back(tmp_x);
    y.emplace_back(tmp_y);
    z.emplace_back(tmp_z);
    auto tmp_res_x = tmp_x - track_lg_xs[1][tmp_type];
    auto tmp_res_y = tmp_y - track_lg_ys[1][tmp_type];
    res.emplace_back(sqrt(tmp_res_x * tmp_res_x + tmp_res_y * tmp_res_y));
    res_x.emplace_back(tmp_res_x);
    res_y.emplace_back(tmp_res_y);
    adc.emplace_back(lg_hit_adc->at(index));
    t.emplace_back(lg_hit_t->at(index));
    ise.emplace_back(E16DST_DST1LGHit::IsE(tmp_minus_mom.Mag(), lg_hit_adc->at(index)));
    if (ise.back() > 0.5) {
      tmp_has_e = true;
    }
  }
  out_plus_proj_has_lg_hit_e.emplace_back(tmp_has_e);
  tmp_has_e = false;
  for (const auto& index : lg_clst_indexs[0]) {
    auto& x     = out_minus_proj_lg_cluster_x.back();
    auto& y     = out_minus_proj_lg_cluster_y.back();
    auto& z     = out_minus_proj_lg_cluster_z.back();
    auto& type  = out_minus_proj_lg_cluster_type.back();
    auto& res   = out_minus_proj_lg_cluster_res.back();
    auto& res_x = out_minus_proj_lg_cluster_res_x.back();
    auto& res_y = out_minus_proj_lg_cluster_res_y.back();
    auto& adc   = out_minus_proj_lg_cluster_adc.back();
    auto& t     = out_minus_proj_lg_cluster_t.back();
    auto& ise   = out_minus_proj_lg_cluster_ise.back();
    auto tmp_x = lg_hit_x->at(index);
    auto tmp_y = lg_hit_y->at(index);
    auto tmp_z = lg_hit_z->at(index);
    int  tmp_type;
    for (tmp_type = 0; tmp_type < cmn_param::kNumLGTypes + 1; ++tmp_type) {
      if (fabs(tmp_z - cmn_param::kLGLocalZ[tmp_type]) < 0.1) {
        break;
      }
    }
    if (tmp_type == cmn_param::kNumLGTypes) {
      std::cerr << "Invalid LG hit z" << std::endl;
      continue;
    }
    type.emplace_back(tmp_type);
    x.emplace_back(tmp_x);
    y.emplace_back(tmp_y);
    z.emplace_back(tmp_z);
    auto tmp_res_x = tmp_x - track_lg_xs[0][tmp_type];
    auto tmp_res_y = tmp_y - track_lg_ys[0][tmp_type];
    res.emplace_back(sqrt(tmp_res_x * tmp_res_x + tmp_res_y * tmp_res_y));
    res_x.emplace_back(tmp_res_x);
    res_y.emplace_back(tmp_res_y);
    adc.emplace_back(lg_cluster_adc->at(index));
    t.emplace_back(lg_cluster_t->at(index));
    ise.emplace_back(E16DST_DST1LGHit::IsE(tmp_minus_mom.Mag(), lg_cluster_adc->at(index)));
    if (ise.back() > 0.5) {
      tmp_has_e = true;
    }
  }
  out_minus_proj_has_lg_cluster_e.emplace_back(tmp_has_e);
  tmp_has_e = false;
  for (const auto& index : lg_clst_indexs[1]) {
    auto& x     = out_plus_proj_lg_cluster_x.back();
    auto& y     = out_plus_proj_lg_cluster_y.back();
    auto& z     = out_plus_proj_lg_cluster_z.back();
    auto& type  = out_plus_proj_lg_cluster_type.back();
    auto& res   = out_plus_proj_lg_cluster_res.back();
    auto& res_x = out_plus_proj_lg_cluster_res_x.back();
    auto& res_y = out_plus_proj_lg_cluster_res_y.back();
    auto& adc   = out_plus_proj_lg_cluster_adc.back();
    auto& t     = out_plus_proj_lg_cluster_t.back();
    auto& ise   = out_plus_proj_lg_cluster_ise.back();
    auto tmp_x = lg_hit_x->at(index);
    auto tmp_y = lg_hit_y->at(index);
    auto tmp_z = lg_hit_z->at(index);
    int  tmp_type;
    for (tmp_type = 0; tmp_type < cmn_param::kNumLGTypes + 1; ++tmp_type) {
      if (fabs(tmp_z - cmn_param::kLGLocalZ[tmp_type]) < 0.1) {
        break;
      }
    }
    if (tmp_type == cmn_param::kNumLGTypes) {
      std::cerr << "Invalid LG hit z" << std::endl;
      continue;
    }
    type.emplace_back(tmp_type);
    x.emplace_back(tmp_x);
    y.emplace_back(tmp_y);
    z.emplace_back(tmp_z);
    auto tmp_res_x = tmp_x - track_lg_xs[1][tmp_type];
    auto tmp_res_y = tmp_y - track_lg_ys[1][tmp_type];
    res.emplace_back(sqrt(tmp_res_x * tmp_res_x + tmp_res_y * tmp_res_y));
    res_x.emplace_back(tmp_res_x);
    res_y.emplace_back(tmp_res_y);
    adc.emplace_back(lg_cluster_adc->at(index));
    t.emplace_back(lg_cluster_t->at(index));
    ise.emplace_back(E16DST_DST1LGHit::IsE(tmp_minus_mom.Mag(), lg_cluster_adc->at(index)));
    if (ise.back() > 0.5) {
      tmp_has_e = true;
    }
  }
  out_plus_proj_has_lg_cluster_e.emplace_back(tmp_has_e);

  out_ee_mass.emplace_back(CalcMass(pt_param::kCalcEEMassFlag,     tmp_minus_mom, tmp_plus_mom));
  out_pipi_mass.emplace_back(CalcMass(pt_param::kCalcPiPiMassFlag, tmp_minus_mom, tmp_plus_mom));
  out_pip_mass.emplace_back(CalcMass(pt_param::kCalcPiPMassFlag,   tmp_minus_mom, tmp_plus_mom));
  FillKsTrackInfo();
  return;
}

void E16ANA_TrackAnalyzerFromTree::PairTracking(const int track_indexs_index_pair[], double tgt_z) {
  int track_index_pair[2] = {selected_track_indexs[track_indexs_index_pair[0]], selected_track_indexs[track_indexs_index_pair[1]]};
  AddTracks(track_index_pair, tgt_z);
  pair_fitter->SetRungeKuttaStepSize(pt_param::kStepSize);
  pair_fitter->SetMaxSteps(pt_param::kMaxSteps);
  out_chi_square.emplace_back(pair_fitter->Fit(pt_param::kVertexXyFixFlag, pt_param::kPyFixFlag, pt_param::kVertexZFixFlag,
                                               pt_param::kMinuitStrategy, pt_param::kMaxFunctionCalls));
  UpdateFitResult(track_indexs_index_pair);
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

//bool HasTimeCorrelationInterTracks() {
//}

bool E16ANA_TrackAnalyzerFromTree::IsGoodPair(int pair_index) {
  // write your selection criteria begin
  if (out_chi_square[pair_index] > pt_param::kChiSquareThreshold) {
    return false;
  }
//  if (!HasTimeCorrelationInterTracks()) {
//    return false;;
//  }
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

void E16ANA_TrackAnalyzerFromTree::AnalyzeTrackPairs() {
  int n_selected_tracks = selected_track_indexs.size();
  for (int index0 = 0; index0 < n_selected_tracks - 1; ++index0) {
    auto selected_track_index0 = selected_track_indexs[index0];
    auto charge0 = rk_charge->at(selected_track_index0);
    auto tgt_z0 = rk_hit_init_pos_gz->at(selected_track_index0);
    for (int index1 = index0 + 1; index1 < n_selected_tracks; ++index1) {
      auto selected_track_index1 = selected_track_indexs[index1];
      auto charge1 = rk_charge->at(selected_track_index1);
      auto tgt_z1 = rk_hit_init_pos_gz->at(selected_track_index1);
      if (charge0 == charge1) {
        continue;
      }
      if (tgt_z0 != tgt_z1) {
        continue;
      }
      int track_indexs_index_pair[2]; // 0 : minus, 1 : plus
      if (charge0 == -1) {
        track_indexs_index_pair[0] = index0;
        track_indexs_index_pair[1] = index1;
      } else {
        track_indexs_index_pair[0] = index1;
        track_indexs_index_pair[1] = index0;
      }
//      TVector3 st_minus_mom;
//      TVector3 st_plus_mom;
//      SearchVertex(minus_index, plus_index, &st_minus_mom, &st_plus_mom);
      PairTracking(track_indexs_index_pair, tgt_z0);
    }
  }
  SelectTrackPairs();
  out_tree->Fill();
  return;
}

double E16ANA_TrackAnalyzerFromTree::SearchVertex(const int track_index_pair[], TVector3* vtx_pos, TVector3* minus_mom, TVector3* plus_mom) {
  auto init_pos0 = Hep3Vector(rk_fit_init_pos_gx->at(track_index_pair[0]) * 0.1, rk_fit_init_pos_gy->at(track_index_pair[0]) * 0.1, rk_fit_init_pos_gz->at(track_index_pair[0]) * 0.1);
  auto init_pos1 = Hep3Vector(rk_fit_init_pos_gx->at(track_index_pair[1]) * 0.1, rk_fit_init_pos_gy->at(track_index_pair[1]) * 0.1, rk_fit_init_pos_gz->at(track_index_pair[1]) * 0.1);
  auto init_mom0 = Hep3Vector(rk_fit_init_mom_gx->at(track_index_pair[0]),       rk_fit_init_mom_gy->at(track_index_pair[0]),       rk_fit_init_mom_gz->at(track_index_pair[0]));
  auto init_mom1 = Hep3Vector(rk_fit_init_mom_gx->at(track_index_pair[1]),       rk_fit_init_mom_gy->at(track_index_pair[1]),       rk_fit_init_mom_gz->at(track_index_pair[1]));
  E16ANA_StepTrack step_track0(bfield_map, init_pos0, init_mom0, -1, cmn_param::kStepTrackStepSizeCm, cmn_param::kStepTrackArraySize);
  E16ANA_StepTrack step_track1(bfield_map, init_pos1, init_mom1,  1, cmn_param::kStepTrackStepSizeCm, cmn_param::kStepTrackArraySize);
  double distance;
  Hep3Vector cross_point;
  Hep3Vector mom0;
  Hep3Vector mom1;
  auto flag = step_track0.Cross(step_track1, &distance, &cross_point, &mom0, &mom1);
  *vtx_pos = {cross_point.x() * 10., cross_point.y() * 10., cross_point.z() * 10.};
  *minus_mom = {mom0.x(), mom0.y(), mom0.z()};
  *plus_mom  = {mom1.x(), mom1.y(), mom1.z()};
  return distance * 10.;
}

void E16ANA_TrackAnalyzerFromTree::AddPionTracks(const int track_index_pair[]) {
  pair_fitter->Clear();
  TVector3 tmp_vtx_pos;
  TVector3 tmp_minus_mom;
  TVector3 tmp_plus_mom;
  SearchVertex(track_index_pair, &tmp_vtx_pos, &tmp_minus_mom, &tmp_plus_mom);
  pair_fitter->SetInitialVertex(tmp_vtx_pos, TVector3(0., 0., 0.));
  pair_fitter->SetInitialMomentum(0, tmp_minus_mom);
  pair_fitter->SetInitialMomentum(1, tmp_plus_mom);
  pair_fitter->SetCharge(0, -1.);
  pair_fitter->SetCharge(1, 1.);
  TVector3 pair_mom;
//  for (int i =0; i < 2; ++i) {
//    auto tmp_mom = TVector3(rk_fit_init_mom_gx->at(track_index_pair[i]), rk_fit_init_mom_gy->at(track_index_pair[i]), rk_fit_init_mom_gz->at(track_index_pair[i]));
//    pair_fitter->SetInitialMomentum(i, tmp_mom);
//  }
  for (int track_index_in_pair = 0; track_index_in_pair < 2; ++track_index_in_pair) {
    auto tindex = track_index_pair[track_index_in_pair];
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

void E16ANA_TrackAnalyzerFromTree::PionPairTracking(const int track_indexs_index_pair[]) {
  int track_index_pair[2] = {selected_track_indexs[track_indexs_index_pair[0]], selected_track_indexs[track_indexs_index_pair[1]]};
  AddPionTracks(track_index_pair);
  pair_fitter->SetRungeKuttaStepSize(pt_param::kStepSize);
  pair_fitter->SetMaxSteps(pt_param::kMaxSteps);
  out_chi_square.emplace_back(pair_fitter->Fit(pt_param::kVertexXyFixFlag, pt_param::kPyFixFlag, pt_param::kVertexZFixFlagPion,
                                               pt_param::kMinuitStrategy, pt_param::kMaxFunctionCalls));
  UpdateFitResult(track_indexs_index_pair);
  return;
}

void E16ANA_TrackAnalyzerFromTree::AnalyzePionTrackPairs() {
  int n_selected_tracks = selected_track_indexs.size();
  for (int index0 = 0; index0 < n_selected_tracks - 1; ++index0) {
    auto selected_track_index0 = selected_track_indexs[index0];
    auto charge0 = rk_charge->at(selected_track_index0);
    for (int index1 = index0 + 1; index1 < n_selected_tracks; ++index1) {
      auto selected_track_index1 = selected_track_indexs[index1];
      auto charge1 = rk_charge->at(selected_track_index1);
      if (charge0 == charge1) {
        continue;
      }
      int track_indexs_index_pair[2]; // 0 : minus, 1 : plus
      if (charge0 == -1) {
        track_indexs_index_pair[0] = index0;
        track_indexs_index_pair[1] = index1;
      } else {
        track_indexs_index_pair[0] = index1;
        track_indexs_index_pair[1] = index0;
      }
      PionPairTracking(track_indexs_index_pair);
    }
  }
  SelectTrackPairs();
//  out_tree->Fill();
  out_tree1->Fill();
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
  for (Long64_t jentry = 0; jentry < nentries; ++jentry) {
    if (jentry % 10 == 0) {
      std::cout << jentry << " / " << nentries << std::endl;
    }
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if (Cut(ientry) < 0) continue;
//    ClearOutBranch();
//    selected_track_indexs.clear();
//    selected_track_proj_hbd_cluster_indexs.clear();
//    selected_track_proj_lg_hit_indexs.clear();
//    selected_track_proj_lg_cluster_indexs.clear();
//    SelectTracks();
//    if (particle_flag == cmn_param::kElectronFlag) {
//      AnalyzeTrackPairs();
//    } else if (particle_flag == cmn_param::kPionFlag) {
//      AnalyzePionTrackPairs();
//    }
    if (analyze_flag == cmn_param::kElectronFlag || analyze_flag == cmn_param::kBothFlag) {
      particle_flag = cmn_param::kElectronFlag;
      ClearOutBranch();
      selected_track_indexs.clear();
      SelectTracks();
      AnalyzeTrackPairs();
    }
    if (analyze_flag == cmn_param::kPionFlag || analyze_flag == cmn_param::kBothFlag) {
      particle_flag = cmn_param::kElectronFlag;
      ClearOutBranch();
      selected_track_indexs.clear();
      SelectTracks();
      AnalyzePionTrackPairs();
    }
  }
  out_file->Write();
  return;
}
