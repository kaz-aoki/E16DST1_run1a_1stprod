#define E16ANA_TrackAnalyzerFromTree_cxx
#include "E16ANA_TrackAnalyzerFromTree.hh"

#include <array>
#include <vector>

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "E16ANA_TrackAnalyzerFromTreeParameter.hh"
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
  out_plus_ssd_mid.clear();
  out_plus_gtr100_mid.clear();
  out_plus_gtr200_mid.clear();
  out_plus_gtr300_mid.clear();
  out_minus_proj_lg_max_adc.clear();
  out_minus_proj_hbd_max_adc.clear();
  out_plus_proj_lg_max_adc.clear();
  out_plus_proj_hbd_max_adc.clear();
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
  out_minus_ssd_fit_pos_x.clear();
  out_minus_ssd_fit_pos_y.clear();
  out_minus_ssd_fit_pos_z.clear();
  out_minus_gtr100_fit_pos_x.clear();
  out_minus_gtr100_fit_pos_y.clear();
  out_minus_gtr100_fit_pos_z.clear();
  out_minus_gtr200_fit_pos_x.clear();
  out_minus_gtr200_fit_pos_y.clear();
  out_minus_gtr200_fit_pos_z.clear();
  out_minus_gtr300_fit_pos_x.clear();
  out_minus_gtr300_fit_pos_y.clear();
  out_minus_gtr300_fit_pos_z.clear();
  out_plus_ssd_fit_pos_x.clear();
  out_plus_ssd_fit_pos_y.clear();
  out_plus_ssd_fit_pos_z.clear();
  out_plus_gtr100_fit_pos_x.clear();
  out_plus_gtr100_fit_pos_y.clear();
  out_plus_gtr100_fit_pos_z.clear();
  out_plus_gtr200_fit_pos_x.clear();
  out_plus_gtr200_fit_pos_y.clear();
  out_plus_gtr200_fit_pos_z.clear();
  out_plus_gtr300_fit_pos_x.clear();
  out_plus_gtr300_fit_pos_y.clear();
  out_plus_gtr300_fit_pos_z.clear();
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
  out_minus_ssd_fit_mom.clear();
  out_minus_ssd_fit_mom_x.clear();
  out_minus_ssd_fit_mom_y.clear();
  out_minus_ssd_fit_mom_z.clear();
  out_minus_ssd_fit_mom_tan.clear();
  out_minus_ssd_fit_mom_gx.clear();
  out_minus_ssd_fit_mom_gy.clear();
  out_minus_ssd_fit_mom_gz.clear();
  out_minus_gtr100_fit_mom.clear();
  out_minus_gtr100_fit_mom_x.clear();
  out_minus_gtr100_fit_mom_y.clear();
  out_minus_gtr100_fit_mom_z.clear();
  out_minus_gtr100_fit_mom_tan.clear();
  out_minus_gtr100_fit_mom_gx.clear();
  out_minus_gtr100_fit_mom_gy.clear();
  out_minus_gtr100_fit_mom_gz.clear();
  out_minus_gtr200_fit_mom.clear();
  out_minus_gtr200_fit_mom_x.clear();
  out_minus_gtr200_fit_mom_y.clear();
  out_minus_gtr200_fit_mom_z.clear();
  out_minus_gtr200_fit_mom_tan.clear();
  out_minus_gtr200_fit_mom_gx.clear();
  out_minus_gtr200_fit_mom_gy.clear();
  out_minus_gtr200_fit_mom_gz.clear();
  out_minus_gtr300_fit_mom.clear();
  out_minus_gtr300_fit_mom_x.clear();
  out_minus_gtr300_fit_mom_y.clear();
  out_minus_gtr300_fit_mom_z.clear();
  out_minus_gtr300_fit_mom_tan.clear();
  out_minus_gtr300_fit_mom_gx.clear();
  out_minus_gtr300_fit_mom_gy.clear();
  out_minus_gtr300_fit_mom_gz.clear();
  out_plus_ssd_fit_mom.clear();
  out_plus_ssd_fit_mom_x.clear();
  out_plus_ssd_fit_mom_y.clear();
  out_plus_ssd_fit_mom_z.clear();
  out_plus_ssd_fit_mom_tan.clear();
  out_plus_ssd_fit_mom_gx.clear();
  out_plus_ssd_fit_mom_gy.clear();
  out_plus_ssd_fit_mom_gz.clear();
  out_plus_gtr100_fit_mom.clear();
  out_plus_gtr100_fit_mom_x.clear();
  out_plus_gtr100_fit_mom_y.clear();
  out_plus_gtr100_fit_mom_z.clear();
  out_plus_gtr100_fit_mom_tan.clear();
  out_plus_gtr100_fit_mom_gx.clear();
  out_plus_gtr100_fit_mom_gy.clear();
  out_plus_gtr100_fit_mom_gz.clear();
  out_plus_gtr200_fit_mom.clear();
  out_plus_gtr200_fit_mom_x.clear();
  out_plus_gtr200_fit_mom_y.clear();
  out_plus_gtr200_fit_mom_z.clear();
  out_plus_gtr200_fit_mom_tan.clear();
  out_plus_gtr200_fit_mom_gx.clear();
  out_plus_gtr200_fit_mom_gy.clear();
  out_plus_gtr200_fit_mom_gz.clear();
  out_plus_gtr300_fit_mom.clear();
  out_plus_gtr300_fit_mom_x.clear();
  out_plus_gtr300_fit_mom_y.clear();
  out_plus_gtr300_fit_mom_z.clear();
  out_plus_gtr300_fit_mom_tan.clear();
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

  out_minus_proj_hbd_id.clear();
  out_minus_proj_hbd_mid.clear();
  out_minus_proj_hbd_x.clear();
  out_minus_proj_hbd_y.clear();
  //  out_minus_proj_hbd_gx.clear();
  //  out_minus_proj_hbd_gy.clear();
  //  out_minus_proj_hbd_gz.clear();
  //  out_minus_proj_hbd_adc.clear();
  out_minus_proj_hbd_t.clear();
  out_minus_proj_hbd_ftime.clear();
  out_minus_proj_hbd_tdiff.clear();
  out_minus_proj_hbd_size.clear();
  out_minus_proj_hbd_eprob.clear();
  out_minus_proj_hbd_cprob.clear();
  out_minus_proj_lg_id.clear();
  out_minus_proj_lg_mid.clear();
  out_minus_proj_lg_x.clear();
  out_minus_proj_lg_y.clear();
  //  out_minus_proj_lg_gx.clear();
  //  out_minus_proj_lg_gy.clear();
  //  out_minus_proj_lg_gz.clear();
  //  out_minus_proj_lg_adc.clear();
  out_minus_proj_lg_t.clear();
  out_minus_proj_lg_npeaks.clear();
  out_minus_proj_lg_fflag.clear();
  out_plus_proj_hbd_id.clear();
  out_plus_proj_hbd_mid.clear();
  out_plus_proj_hbd_x.clear();
  out_plus_proj_hbd_y.clear();
  //  out_plus_proj_hbd_gx.clear();
  //  out_plus_proj_hbd_gy.clear();
  //  out_plus_proj_hbd_gz.clear();
  //  out_plus_proj_hbd_adc.clear();
  out_plus_proj_hbd_t.clear();
  out_plus_proj_hbd_ftime.clear();
  out_plus_proj_hbd_tdiff.clear();
  out_plus_proj_hbd_size.clear();
  out_plus_proj_hbd_eprob.clear();
  out_plus_proj_hbd_cprob.clear();
  out_plus_proj_lg_id.clear();
  out_plus_proj_lg_mid.clear();
  out_plus_proj_lg_x.clear();
  out_plus_proj_lg_y.clear();
  //  out_plus_proj_lg_gx.clear();
  //  out_plus_proj_lg_gy.clear();
  //  out_plus_proj_lg_gz.clear();
  //  out_plus_proj_lg_adc.clear();
  out_plus_proj_lg_t.clear();
  out_plus_proj_lg_npeaks.clear();
  out_plus_proj_lg_fflag.clear();

  out_n_hbd_clusters = n_hbd_clusters;
  out_n_lg_hits = n_lg_hits;
  out_n_single_tracks = n_cands;
  out_hbd_cluster_id.resize(n_hbd_clusters*2);
  out_hbd_cluster_mid.resize(n_hbd_clusters);
  out_hbd_cluster_x.resize(n_hbd_clusters);
  out_hbd_cluster_y.resize(n_hbd_clusters);
  out_hbd_cluster_gx.resize(n_hbd_clusters);
  out_hbd_cluster_gy.resize(n_hbd_clusters);
  out_hbd_cluster_gz.resize(n_hbd_clusters);
  out_hbd_cluster_adc.resize(n_hbd_clusters);
  out_hbd_cluster_t.resize(n_hbd_clusters);
  out_hbd_cluster_ftime.resize(n_hbd_clusters);
  out_hbd_cluster_tdiff.resize(n_hbd_clusters);
  out_hbd_cluster_size.resize(n_hbd_clusters);
  out_hbd_cluster_eprob.resize(n_hbd_clusters);
  out_hbd_cluster_cprob.resize(n_hbd_clusters);
  out_lg_hit_id.resize(n_lg_hits);
  out_lg_hit_mid.resize(n_lg_hits);
  out_lg_hit_x.resize(n_lg_hits);
  out_lg_hit_y.resize(n_lg_hits);
  out_lg_hit_gx.resize(n_lg_hits);
  out_lg_hit_gy.resize(n_lg_hits);
  out_lg_hit_gz.resize(n_lg_hits);
  out_lg_hit_adc.resize(n_lg_hits);
  out_lg_hit_t.resize(n_lg_hits);
  out_lg_hit_npeaks.resize(n_lg_hits);
  out_lg_hit_fflag.resize(n_lg_hits);
  out_single_track_id.resize(n_cands);
  out_single_chi_square.resize(n_cands);
  out_rk_fit_hbd_mid.resize(n_cands);
  out_rk_fit_hbd_x.resize(n_cands);
  out_rk_fit_hbd_y.resize(n_cands);
  out_rk_fit_hbd_gx.resize(n_cands);
  out_rk_fit_hbd_gy.resize(n_cands);
  out_rk_fit_hbd_gz.resize(n_cands);
  out_rk_fit_lg_c_mid.resize(n_cands);
  out_rk_fit_lg_c_x.resize(n_cands);
  out_rk_fit_lg_c_y.resize(n_cands);
  out_rk_fit_lg_c_gx.resize(n_cands);
  out_rk_fit_lg_c_gy.resize(n_cands);
  out_rk_fit_lg_c_gz.resize(n_cands);
  out_rk_fit_lg_b_mid.resize(n_cands);
  out_rk_fit_lg_b_x.resize(n_cands);
  out_rk_fit_lg_b_y.resize(n_cands);
  out_rk_fit_lg_b_gx.resize(n_cands);
  out_rk_fit_lg_b_gy.resize(n_cands);
  out_rk_fit_lg_b_gz.resize(n_cands);
  out_rk_fit_lg_a_mid.resize(n_cands);
  out_rk_fit_lg_a_x.resize(n_cands);
  out_rk_fit_lg_a_y.resize(n_cands);
  out_rk_fit_lg_a_gx.resize(n_cands);
  out_rk_fit_lg_a_gy.resize(n_cands);
  out_rk_fit_lg_a_gz.resize(n_cands);
  out_rk_res_ssd_x.resize(n_cands);
  out_rk_res_gtr100_x.resize(n_cands);
  out_rk_res_gtr100_y.resize(n_cands);
  out_rk_res_gtr200_x.resize(n_cands);
  out_rk_res_gtr200_y.resize(n_cands);
  out_rk_res_gtr300_x.resize(n_cands);
  out_rk_res_gtr300_y.resize(n_cands);
  out_rk_proj_tgt0_gx.resize(n_cands);
  out_rk_proj_tgt0_gy.resize(n_cands);
  out_rk_proj_tgt0_gz.resize(n_cands);
  out_rk_proj_tgt1_gx.resize(n_cands);
  out_rk_proj_tgt1_gy.resize(n_cands);
  out_rk_proj_tgt1_gz.resize(n_cands);
  out_rk_proj_tgt2_gx.resize(n_cands);
  out_rk_proj_tgt2_gy.resize(n_cands);
  out_rk_proj_tgt2_gz.resize(n_cands);
  out_rk_proj_tgt0_mom_gx.resize(n_cands);
  out_rk_proj_tgt0_mom_gy.resize(n_cands);
  out_rk_proj_tgt0_mom_gz.resize(n_cands);
  out_rk_proj_n_hbd.resize(n_cands);
  out_rk_proj_hbd0_id.resize(n_cands);
  out_rk_proj_hbd0_mid.resize(n_cands);
  out_rk_proj_hbd1_id.resize(n_cands);
  out_rk_proj_hbd1_mid.resize(n_cands);
  out_rk_proj_hbd2_id.resize(n_cands);
  out_rk_proj_hbd2_mid.resize(n_cands);
  out_rk_proj_hbd3_id.resize(n_cands);
  out_rk_proj_hbd3_mid.resize(n_cands);
  out_rk_proj_n_lg.resize(n_cands);
  out_rk_proj_lg0_id.resize(n_cands);
  out_rk_proj_lg1_id.resize(n_cands);
  out_rk_proj_lg2_id.resize(n_cands);
  out_rk_proj_lg3_id.resize(n_cands);

  copy( hbd_cluster_id->begin(), hbd_cluster_id->end(), out_hbd_cluster_id.begin() );
  copy( hbd_cluster_mid->begin(), hbd_cluster_mid->end(), out_hbd_cluster_mid.begin() );
  copy( hbd_cluster_x->begin(), hbd_cluster_x->end(), out_hbd_cluster_x.begin() );
  copy( hbd_cluster_y->begin(), hbd_cluster_y->end(), out_hbd_cluster_y.begin() );
  copy( hbd_cluster_gx->begin(), hbd_cluster_gx->end(), out_hbd_cluster_gx.begin() );
  copy( hbd_cluster_gy->begin(), hbd_cluster_gy->end(), out_hbd_cluster_gy.begin() );
  copy( hbd_cluster_gz->begin(), hbd_cluster_gz->end(), out_hbd_cluster_gz.begin() );
  copy( hbd_cluster_adc->begin(), hbd_cluster_adc->end(), out_hbd_cluster_adc.begin() );
  copy( hbd_cluster_t->begin(), hbd_cluster_t->end(), out_hbd_cluster_t.begin() );
  copy( hbd_cluster_ftime->begin(), hbd_cluster_ftime->end(), out_hbd_cluster_ftime.begin() );
  copy( hbd_cluster_tdiff->begin(), hbd_cluster_tdiff->end(), out_hbd_cluster_tdiff.begin() );
  copy( hbd_cluster_size->begin(), hbd_cluster_size->end(), out_hbd_cluster_size.begin() );
  copy( hbd_cluster_eprob->begin(), hbd_cluster_eprob->end(), out_hbd_cluster_eprob.begin() );
  copy( hbd_cluster_cprob->begin(), hbd_cluster_cprob->end(), out_hbd_cluster_cprob.begin() );
  copy( lg_hit_id->begin(), lg_hit_id->end(), out_lg_hit_id.begin() );
  copy( lg_hit_mid->begin(), lg_hit_mid->end(), out_lg_hit_mid.begin() );
  copy( lg_hit_x->begin(), lg_hit_x->end(), out_lg_hit_x.begin() );
  copy( lg_hit_y->begin(), lg_hit_y->end(), out_lg_hit_y.begin() );
  copy( lg_hit_gx->begin(), lg_hit_gx->end(), out_lg_hit_gx.begin() );
  copy( lg_hit_gy->begin(), lg_hit_gy->end(), out_lg_hit_gy.begin() );
  copy( lg_hit_gz->begin(), lg_hit_gz->end(), out_lg_hit_gz.begin() );
  copy( lg_hit_adc->begin(), lg_hit_adc->end(), out_lg_hit_adc.begin() );
  copy( lg_hit_t->begin(), lg_hit_t->end(), out_lg_hit_t.begin() );
  copy( lg_hit_npeaks->begin(), lg_hit_npeaks->end(), out_lg_hit_npeaks.begin() );
  copy( lg_hit_fflag->begin(), lg_hit_fflag->end(), out_lg_hit_fflag.begin() );
  copy( track_id->begin(), track_id->end(), out_single_track_id.begin() );
  copy( chi_square->begin(), chi_square->end(), out_single_chi_square.begin() );
  copy( rk_fit_hbd_mid->begin(), rk_fit_hbd_mid->end(), out_rk_fit_hbd_mid.begin() );
  copy( rk_fit_hbd_x->begin(), rk_fit_hbd_x->end(), out_rk_fit_hbd_x.begin() );
  copy( rk_fit_hbd_y->begin(), rk_fit_hbd_y->end(), out_rk_fit_hbd_y.begin() );
  copy( rk_fit_hbd_gx->begin(), rk_fit_hbd_gx->end(), out_rk_fit_hbd_gx.begin() );
  copy( rk_fit_hbd_gy->begin(), rk_fit_hbd_gy->end(), out_rk_fit_hbd_gy.begin() );
  copy( rk_fit_hbd_gz->begin(), rk_fit_hbd_gz->end(), out_rk_fit_hbd_gz.begin() );
  copy( rk_fit_lg_c_mid->begin(), rk_fit_lg_c_mid->end(), out_rk_fit_lg_c_mid.begin() );
  copy( rk_fit_lg_c_x->begin(), rk_fit_lg_c_x->end(), out_rk_fit_lg_c_x.begin() );
  copy( rk_fit_lg_c_y->begin(), rk_fit_lg_c_y->end(), out_rk_fit_lg_c_y.begin() );
  copy( rk_fit_lg_c_gx->begin(), rk_fit_lg_c_gx->end(), out_rk_fit_lg_c_gx.begin() );
  copy( rk_fit_lg_c_gy->begin(), rk_fit_lg_c_gy->end(), out_rk_fit_lg_c_gy.begin() );
  copy( rk_fit_lg_c_gz->begin(), rk_fit_lg_c_gz->end(), out_rk_fit_lg_c_gz.begin() );
  copy( rk_fit_lg_b_mid->begin(), rk_fit_lg_b_mid->end(), out_rk_fit_lg_b_mid.begin() );
  copy( rk_fit_lg_b_x->begin(), rk_fit_lg_b_x->end(), out_rk_fit_lg_b_x.begin() );
  copy( rk_fit_lg_b_y->begin(), rk_fit_lg_b_y->end(), out_rk_fit_lg_b_y.begin() );
  copy( rk_fit_lg_b_gx->begin(), rk_fit_lg_b_gx->end(), out_rk_fit_lg_b_gx.begin() );
  copy( rk_fit_lg_b_gy->begin(), rk_fit_lg_b_gy->end(), out_rk_fit_lg_b_gy.begin() );
  copy( rk_fit_lg_b_gz->begin(), rk_fit_lg_b_gz->end(), out_rk_fit_lg_b_gz.begin() );
  copy( rk_fit_lg_a_mid->begin(), rk_fit_lg_a_mid->end(), out_rk_fit_lg_a_mid.begin() );
  copy( rk_fit_lg_a_x->begin(), rk_fit_lg_a_x->end(), out_rk_fit_lg_a_x.begin() );
  copy( rk_fit_lg_a_y->begin(), rk_fit_lg_a_y->end(), out_rk_fit_lg_a_y.begin() );
  copy( rk_fit_lg_a_gx->begin(), rk_fit_lg_a_gx->end(), out_rk_fit_lg_a_gx.begin() );
  copy( rk_fit_lg_a_gy->begin(), rk_fit_lg_a_gy->end(), out_rk_fit_lg_a_gy.begin() );
  copy( rk_fit_lg_a_gz->begin(), rk_fit_lg_a_gz->end(), out_rk_fit_lg_a_gz.begin() );
  copy( rk_res_ssd_x->begin(), rk_res_ssd_x->end(), out_rk_res_ssd_x.begin() );
  copy( rk_res_gtr100_x->begin(), rk_res_gtr100_x->end(), out_rk_res_gtr100_x.begin() );
  copy( rk_res_gtr100_y->begin(), rk_res_gtr100_y->end(), out_rk_res_gtr100_y.begin() );
  copy( rk_res_gtr200_x->begin(), rk_res_gtr200_x->end(), out_rk_res_gtr200_x.begin() );
  copy( rk_res_gtr200_y->begin(), rk_res_gtr200_y->end(), out_rk_res_gtr200_y.begin() );
  copy( rk_res_gtr300_x->begin(), rk_res_gtr300_x->end(), out_rk_res_gtr300_x.begin() );
  copy( rk_res_gtr300_y->begin(), rk_res_gtr300_y->end(), out_rk_res_gtr300_y.begin() );
  copy( rk_proj_tgt0_gx->begin(), rk_proj_tgt0_gx->end(), out_rk_proj_tgt0_gx.begin() );
  copy( rk_proj_tgt0_gy->begin(), rk_proj_tgt0_gy->end(), out_rk_proj_tgt0_gy.begin() );
  copy( rk_proj_tgt0_gz->begin(), rk_proj_tgt0_gz->end(), out_rk_proj_tgt0_gz.begin() );
  copy( rk_proj_tgt1_gx->begin(), rk_proj_tgt1_gx->end(), out_rk_proj_tgt1_gx.begin() );
  copy( rk_proj_tgt1_gy->begin(), rk_proj_tgt1_gy->end(), out_rk_proj_tgt1_gy.begin() );
  copy( rk_proj_tgt1_gz->begin(), rk_proj_tgt1_gz->end(), out_rk_proj_tgt1_gz.begin() );
  copy( rk_proj_tgt2_gx->begin(), rk_proj_tgt2_gx->end(), out_rk_proj_tgt2_gx.begin() );
  copy( rk_proj_tgt2_gy->begin(), rk_proj_tgt2_gy->end(), out_rk_proj_tgt2_gy.begin() );
  copy( rk_proj_tgt2_gz->begin(), rk_proj_tgt2_gz->end(), out_rk_proj_tgt2_gz.begin() );
  copy( rk_proj_tgt0_mom_gx->begin(), rk_proj_tgt0_mom_gx->end(), out_rk_proj_tgt0_mom_gx.begin() );
  copy( rk_proj_tgt0_mom_gy->begin(), rk_proj_tgt0_mom_gy->end(), out_rk_proj_tgt0_mom_gy.begin() );
  copy( rk_proj_tgt0_mom_gz->begin(), rk_proj_tgt0_mom_gz->end(), out_rk_proj_tgt0_mom_gz.begin() );
  copy( rk_proj_n_hbd->begin(), rk_proj_n_hbd->end(), out_rk_proj_n_hbd.begin() );
  copy( rk_proj_hbd0_id->begin(), rk_proj_hbd0_id->end(), out_rk_proj_hbd0_id.begin() );
  copy( rk_proj_hbd0_mid->begin(), rk_proj_hbd0_mid->end(), out_rk_proj_hbd0_mid.begin() );
  copy( rk_proj_hbd1_id->begin(), rk_proj_hbd1_id->end(), out_rk_proj_hbd1_id.begin() );
  copy( rk_proj_hbd1_mid->begin(), rk_proj_hbd1_mid->end(), out_rk_proj_hbd1_mid.begin() );
  copy( rk_proj_hbd2_id->begin(), rk_proj_hbd2_id->end(), out_rk_proj_hbd2_id.begin() );
  copy( rk_proj_hbd2_mid->begin(), rk_proj_hbd2_mid->end(), out_rk_proj_hbd2_mid.begin() );
  copy( rk_proj_hbd3_id->begin(), rk_proj_hbd3_id->end(), out_rk_proj_hbd3_id.begin() );
  copy( rk_proj_hbd3_mid->begin(), rk_proj_hbd3_mid->end(), out_rk_proj_hbd3_mid.begin() );
  copy( rk_proj_n_lg->begin(), rk_proj_n_lg->end(), out_rk_proj_n_lg.begin() );
  copy( rk_proj_lg0_id->begin(), rk_proj_lg0_id->end(), out_rk_proj_lg0_id.begin() );
  copy( rk_proj_lg1_id->begin(), rk_proj_lg1_id->end(), out_rk_proj_lg1_id.begin() );
  copy( rk_proj_lg2_id->begin(), rk_proj_lg2_id->end(), out_rk_proj_lg2_id.begin() );
  copy( rk_proj_lg3_id->begin(), rk_proj_lg3_id->end(), out_rk_proj_lg3_id.begin() );
  return;
}

bool E16ANA_TrackAnalyzerFromTree::IsGoodTrack(int track_index) {
  // write your selection criteria begin
  if (chi_square->at(track_index) > st_param::kChiSquareThreshold) {
    return false;
  }
  if (rk_proj_n_hbd->at(track_index) == 0) {
    return false;
  }
  if (rk_proj_n_lg->at(track_index) == 0) {
    return false;
  }
//  bool is_hbd_electron = false;
//  if (rk_proj_n_hbd->at(track_index) >= 1 && rk_proj_hbd0_eprob->at(track_index) > 0.5) {
//    is_hbd_electron = true;
//  } else if (rk_proj_n_hbd->at(track_index) >= 2 && rk_proj_hbd1_eprob->at(track_index) > 0.5) {
//    is_hbd_electron = true;
//  } else if (rk_proj_n_hbd->at(track_index) >= 3 && rk_proj_hbd2_eprob->at(track_index) > 0.5) {
//    is_hbd_electron = true;
//  } else if (rk_proj_n_hbd->at(track_index) >= 4 && rk_proj_hbd3_eprob->at(track_index) > 0.5) {
//    is_hbd_electron = true;
//  }
//  if (!is_hbd_electron) {
//    return false;
//  }
//  bool is_lg_high = false;
//  auto mom = TVector3(rk_fit_init_mom_gx->at(track_index), rk_fit_init_mom_gy->at(track_index), rk_fit_init_mom_gz->at(track_index));
////  if (rk_proj_n_lg->at(track_index) >= 1 && rk_proj_lg0_adc->at(track_index) > st_param::kLGADCThreshold) {
//  if (rk_proj_n_lg->at(track_index) >= 1 && E16DST_DST1LGHit::IsE(mom.Mag(), rk_proj_lg0_adc->at(track_index)) > 0.5) {
//    is_lg_high = true;
////  } else if (rk_proj_n_lg->at(track_index) >= 2 && rk_proj_lg1_adc->at(track_index) > st_param::kLGADCThreshold) {
//  } else if (rk_proj_n_lg->at(track_index) >= 2 && E16DST_DST1LGHit::IsE(mom.Mag(), rk_proj_lg1_adc->at(track_index)) > 0.5) {
//    is_lg_high = true;
////  } else if (rk_proj_n_lg->at(track_index) >= 3 && rk_proj_lg2_adc->at(track_index) > st_param::kLGADCThreshold) {
//  } else if (rk_proj_n_lg->at(track_index) >= 3 && E16DST_DST1LGHit::IsE(mom.Mag(), rk_proj_lg2_adc->at(track_index)) > 0.5) {
//    is_lg_high = true;
////  } else if (rk_proj_n_lg->at(track_index) >= 4 && rk_proj_lg3_adc->at(track_index) > st_param::kLGADCThreshold) {
//  } else if (rk_proj_n_lg->at(track_index) >= 4 && E16DST_DST1LGHit::IsE(mom.Mag(), rk_proj_lg3_adc->at(track_index)) > 0.5) {
//    is_lg_high = true;
//  }
//  if (!is_lg_high) {
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
  if (rk_proj_n_hbd->at(track_index) == 0) {
    return false;
  }
  if (rk_proj_n_lg->at(track_index) == 0) {
    return false;
  }
  bool is_hbd_pion = false;
  if (rk_proj_n_hbd->at(track_index) >= 1 && rk_proj_hbd0_eprob->at(track_index) < 0.5 && rk_proj_hbd0_cprob->at(track_index) > 0.5) {
    is_hbd_pion = true;
  } else if (rk_proj_n_hbd->at(track_index) >= 2 && rk_proj_hbd1_eprob->at(track_index) > 0.5 && rk_proj_hbd1_cprob->at(track_index) > 0.5) {
    is_hbd_pion = true;
  } else if (rk_proj_n_hbd->at(track_index) >= 3 && rk_proj_hbd2_eprob->at(track_index) > 0.5 && rk_proj_hbd2_cprob->at(track_index) > 0.5) {
    is_hbd_pion = true;
  } else if (rk_proj_n_hbd->at(track_index) >= 4 && rk_proj_hbd3_eprob->at(track_index) > 0.5 && rk_proj_hbd3_cprob->at(track_index) > 0.5) {
    is_hbd_pion = true;
  }
  if (!is_hbd_pion) {
    return false;
  }
  bool is_lg_low = false;
  if (rk_proj_n_lg->at(track_index) >= 1 && rk_proj_lg0_adc->at(track_index) < pit_param::kLGADCThreshold) {
    is_lg_low = true;
  }
  if (rk_proj_n_lg->at(track_index) >= 2 && rk_proj_lg1_adc->at(track_index) < pit_param::kLGADCThreshold) {
    is_lg_low = true;
  }
  if (rk_proj_n_lg->at(track_index) >= 3 && rk_proj_lg2_adc->at(track_index) < pit_param::kLGADCThreshold) {
    is_lg_low = true;
  }
  if (rk_proj_n_lg->at(track_index) >= 4 && rk_proj_lg3_adc->at(track_index) < pit_param::kLGADCThreshold) {
    is_lg_low = true;
  }
  if (!is_lg_low) {
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
  if ((particle_flag == cmn_param::kElectronFlag && IsGoodTrack(track_index)) || (particle_flag == cmn_param::kPionFlag && IsGoodPionTrack(track_index))) {
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

void E16ANA_TrackAnalyzerFromTree::UpdateFitResult(const int track_index_pair[]) {
  out_minus_track_id.emplace_back(track_id->at(track_index_pair[0]));
  out_plus_track_id.emplace_back(track_id->at(track_index_pair[1]));
  double hbd_adc[2] = {-10000., -10000.};
  double lg_adc[2]  = {-10000., -10000.};
  double hbd_id[2] = {-10000., -10000.};
  double hbd_mid[2] = {-10000., -10000.};
  double hbd_x[2] = {-10000., -10000.};
  double hbd_y[2] = {-10000., -10000.};
  double hbd_t[2] = {-10000., -10000.};
  double hbd_ftime[2] = {-10000., -10000.};
  double hbd_tdiff[2] = {-10000., -10000.};
  double hbd_size[2] = {-10000., -10000.};
  double hbd_eprob[2] = {-10000., -10000.};
  double hbd_cprob[2] = {-10000., -10000.};
  double lg_id[2] = {-10000., -10000.};
  double lg_mid[2] = {-10000., -10000.};
  double lg_x[2] = {-10000., -10000.};
  double lg_y[2] = {-10000., -10000.};
  double lg_t[2] = {-10000., -10000.};
  double lg_npeaks[2] = {-10000., -10000.};
  double lg_fflag[2] = {-10000., -10000.};
  for (int i = 0; i < 2; ++i) {
    if (rk_proj_n_hbd->at(track_index_pair[i]) >= 1) {
      if (rk_proj_hbd0_adc->at(track_index_pair[i]) > hbd_adc[i]) {
        hbd_adc[i] = rk_proj_hbd0_adc->at(track_index_pair[i]);
	hbd_id[i] = rk_proj_hbd0_id->at(track_index_pair[i]);
	hbd_mid[i] = rk_proj_hbd0_mid->at(track_index_pair[i]);
	hbd_x[i] = rk_proj_hbd0_x->at(track_index_pair[i]);
	hbd_y[i] = rk_proj_hbd0_y->at(track_index_pair[i]);
	hbd_t[i] = rk_proj_hbd0_t->at(track_index_pair[i]);
	hbd_ftime[i] = rk_proj_hbd0_ftime->at(track_index_pair[i]);
	hbd_tdiff[i] = rk_proj_hbd0_tdiff->at(track_index_pair[i]);
	hbd_size[i] = rk_proj_hbd0_size->at(track_index_pair[i]);
	hbd_eprob[i] = rk_proj_hbd0_eprob->at(track_index_pair[i]);
	hbd_cprob[i] = rk_proj_hbd0_cprob->at(track_index_pair[i]);
      }
    }
    if (rk_proj_n_hbd->at(track_index_pair[i]) >= 2) {
      if (rk_proj_hbd1_adc->at(track_index_pair[i]) > hbd_adc[i]) {
        hbd_adc[i] = rk_proj_hbd1_adc->at(track_index_pair[i]);
	hbd_id[i] = rk_proj_hbd1_id->at(track_index_pair[i]);
	hbd_mid[i] = rk_proj_hbd1_mid->at(track_index_pair[i]);
	hbd_x[i] = rk_proj_hbd1_x->at(track_index_pair[i]);
	hbd_y[i] = rk_proj_hbd1_y->at(track_index_pair[i]);
	hbd_t[i] = rk_proj_hbd1_t->at(track_index_pair[i]);
	hbd_ftime[i] = rk_proj_hbd1_ftime->at(track_index_pair[i]);
	hbd_tdiff[i] = rk_proj_hbd1_tdiff->at(track_index_pair[i]);
	hbd_size[i] = rk_proj_hbd1_size->at(track_index_pair[i]);
	hbd_eprob[i] = rk_proj_hbd1_eprob->at(track_index_pair[i]);
	hbd_cprob[i] = rk_proj_hbd1_cprob->at(track_index_pair[i]);
      }
    }
    if (rk_proj_n_hbd->at(track_index_pair[i]) >= 3) {
      if (rk_proj_hbd2_adc->at(track_index_pair[i]) > hbd_adc[i]) {
        hbd_adc[i] = rk_proj_hbd2_adc->at(track_index_pair[i]);
	hbd_id[i] = rk_proj_hbd2_id->at(track_index_pair[i]);
	hbd_mid[i] = rk_proj_hbd2_mid->at(track_index_pair[i]);
	hbd_x[i] = rk_proj_hbd2_x->at(track_index_pair[i]);
	hbd_y[i] = rk_proj_hbd2_y->at(track_index_pair[i]);
	hbd_t[i] = rk_proj_hbd2_t->at(track_index_pair[i]);
	hbd_ftime[i] = rk_proj_hbd2_ftime->at(track_index_pair[i]);
	hbd_tdiff[i] = rk_proj_hbd2_tdiff->at(track_index_pair[i]);
	hbd_size[i] = rk_proj_hbd2_size->at(track_index_pair[i]);
	hbd_eprob[i] = rk_proj_hbd2_eprob->at(track_index_pair[i]);
	hbd_cprob[i] = rk_proj_hbd2_cprob->at(track_index_pair[i]);
      }
    }
    if (rk_proj_n_hbd->at(track_index_pair[i]) >= 4) {
      if (rk_proj_hbd3_adc->at(track_index_pair[i]) > hbd_adc[i]) {
        hbd_adc[i] = rk_proj_hbd3_adc->at(track_index_pair[i]);
	hbd_id[i] = rk_proj_hbd3_id->at(track_index_pair[i]);
	hbd_mid[i] = rk_proj_hbd3_mid->at(track_index_pair[i]);
	hbd_x[i] = rk_proj_hbd3_x->at(track_index_pair[i]);
	hbd_y[i] = rk_proj_hbd3_y->at(track_index_pair[i]);
	hbd_t[i] = rk_proj_hbd3_t->at(track_index_pair[i]);
	hbd_ftime[i] = rk_proj_hbd3_ftime->at(track_index_pair[i]);
	hbd_tdiff[i] = rk_proj_hbd3_tdiff->at(track_index_pair[i]);
	hbd_size[i] = rk_proj_hbd3_size->at(track_index_pair[i]);
	hbd_eprob[i] = rk_proj_hbd3_eprob->at(track_index_pair[i]);
	hbd_cprob[i] = rk_proj_hbd3_cprob->at(track_index_pair[i]);
      }
    }
    if (rk_proj_n_lg->at(track_index_pair[i]) >= 1) {
      if (rk_proj_lg0_adc->at(track_index_pair[i]) > lg_adc[i]) {
        lg_adc[i] = rk_proj_lg0_adc->at(track_index_pair[i]);
	lg_id[i] = rk_proj_lg0_id->at(track_index_pair[i]);
	lg_mid[i] = rk_proj_lg0_mid->at(track_index_pair[i]);
	lg_x[i] = rk_proj_lg0_x->at(track_index_pair[i]);
	lg_y[i] = rk_proj_lg0_y->at(track_index_pair[i]);
	lg_t[i] = rk_proj_lg0_t->at(track_index_pair[i]);
	lg_npeaks[i] = rk_proj_lg0_npeaks->at(track_index_pair[i]);
	lg_fflag[i] = rk_proj_lg0_fflag->at(track_index_pair[i]);
      }
    }
    if (rk_proj_n_lg->at(track_index_pair[i]) >= 2) {
      if (rk_proj_lg1_adc->at(track_index_pair[i]) > lg_adc[i]) {
        lg_adc[i] = rk_proj_lg1_adc->at(track_index_pair[i]);
	lg_id[i] = rk_proj_lg1_id->at(track_index_pair[i]);
	lg_mid[i] = rk_proj_lg1_mid->at(track_index_pair[i]);
	lg_x[i] = rk_proj_lg1_x->at(track_index_pair[i]);
	lg_y[i] = rk_proj_lg1_y->at(track_index_pair[i]);
	lg_t[i] = rk_proj_lg1_t->at(track_index_pair[i]);
	lg_npeaks[i] = rk_proj_lg1_npeaks->at(track_index_pair[i]);
	lg_fflag[i] = rk_proj_lg1_fflag->at(track_index_pair[i]);
      }
    }
    if (rk_proj_n_lg->at(track_index_pair[i]) >= 3) {
      if (rk_proj_lg2_adc->at(track_index_pair[i]) > lg_adc[i]) {
        lg_adc[i] = rk_proj_lg2_adc->at(track_index_pair[i]);
	lg_id[i] = rk_proj_lg2_id->at(track_index_pair[i]);
	lg_mid[i] = rk_proj_lg2_mid->at(track_index_pair[i]);
	lg_x[i] = rk_proj_lg2_x->at(track_index_pair[i]);
	lg_y[i] = rk_proj_lg2_y->at(track_index_pair[i]);
	lg_t[i] = rk_proj_lg2_t->at(track_index_pair[i]);
	lg_npeaks[i] = rk_proj_lg2_npeaks->at(track_index_pair[i]);
	lg_fflag[i] = rk_proj_lg2_fflag->at(track_index_pair[i]);
      }
    }
    if (rk_proj_n_lg->at(track_index_pair[i]) >= 4) {
      if (rk_proj_lg3_adc->at(track_index_pair[i]) > lg_adc[i]) {
        lg_adc[i] = rk_proj_lg3_adc->at(track_index_pair[i]);
	lg_id[i] = rk_proj_lg3_id->at(track_index_pair[i]);
	lg_mid[i] = rk_proj_lg3_mid->at(track_index_pair[i]);
	lg_x[i] = rk_proj_lg3_x->at(track_index_pair[i]);
	lg_y[i] = rk_proj_lg3_y->at(track_index_pair[i]);
	lg_t[i] = rk_proj_lg3_t->at(track_index_pair[i]);
	lg_npeaks[i] = rk_proj_lg3_npeaks->at(track_index_pair[i]);
	lg_fflag[i] = rk_proj_lg3_fflag->at(track_index_pair[i]);
      }
    }
  }
  out_minus_proj_hbd_max_adc.emplace_back(hbd_adc[0]);
  out_minus_proj_lg_max_adc.emplace_back(lg_adc[0]);
  out_plus_proj_hbd_max_adc.emplace_back(hbd_adc[1]);
  out_plus_proj_lg_max_adc.emplace_back(lg_adc[1]);
  out_minus_proj_hbd_id.emplace_back(hbd_id[0]);
  out_minus_proj_hbd_mid.emplace_back(hbd_mid[0]);
  out_minus_proj_hbd_x.emplace_back(hbd_x[0]);
  out_minus_proj_hbd_y.emplace_back(hbd_y[0]);
  out_minus_proj_hbd_t.emplace_back(hbd_t[0]);
  out_minus_proj_hbd_ftime.emplace_back(hbd_ftime[0]);
  out_minus_proj_hbd_tdiff.emplace_back(hbd_tdiff[0]);
  out_minus_proj_hbd_size.emplace_back(hbd_size[0]);
  out_minus_proj_hbd_eprob.emplace_back(hbd_eprob[0]);
  out_minus_proj_hbd_cprob.emplace_back(hbd_cprob[0]);
  out_minus_proj_lg_id.emplace_back(lg_id[0]);
  out_minus_proj_lg_mid.emplace_back(lg_mid[0]);
  out_minus_proj_lg_x.emplace_back(lg_x[0]);
  out_minus_proj_lg_y.emplace_back(lg_y[0]);
  out_minus_proj_lg_t.emplace_back(lg_t[0]);
  out_minus_proj_lg_npeaks.emplace_back(lg_npeaks[0]);
  out_minus_proj_lg_fflag.emplace_back(lg_fflag[0]);
  out_plus_proj_hbd_id.emplace_back(hbd_id[1]);
  out_plus_proj_hbd_mid.emplace_back(hbd_mid[1]);
  out_plus_proj_hbd_x.emplace_back(hbd_x[1]);
  out_plus_proj_hbd_y.emplace_back(hbd_y[1]);
  out_plus_proj_hbd_t.emplace_back(hbd_t[1]);
  out_plus_proj_hbd_ftime.emplace_back(hbd_ftime[1]);
  out_plus_proj_hbd_tdiff.emplace_back(hbd_tdiff[1]);
  out_plus_proj_hbd_size.emplace_back(hbd_size[1]);
  out_plus_proj_hbd_eprob.emplace_back(hbd_eprob[1]);
  out_plus_proj_hbd_cprob.emplace_back(hbd_cprob[1]);
  out_plus_proj_lg_id.emplace_back(lg_id[1]);
  out_plus_proj_lg_mid.emplace_back(lg_mid[1]);
  out_plus_proj_lg_x.emplace_back(lg_x[1]);
  out_plus_proj_lg_y.emplace_back(lg_y[1]);
  out_plus_proj_lg_t.emplace_back(lg_t[1]);
  out_plus_proj_lg_npeaks.emplace_back(lg_npeaks[1]);
  out_plus_proj_lg_fflag.emplace_back(lg_fflag[1]);
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
  FillTVector3ToDouble(lpos[0][0], &out_minus_ssd_fit_pos_x,    &out_minus_ssd_fit_pos_y,    &out_minus_ssd_fit_pos_z);
  FillTVector3ToDouble(lpos[0][1], &out_minus_gtr100_fit_pos_x, &out_minus_gtr100_fit_pos_y, &out_minus_gtr100_fit_pos_z);
  FillTVector3ToDouble(lpos[0][2], &out_minus_gtr200_fit_pos_x, &out_minus_gtr200_fit_pos_y, &out_minus_gtr200_fit_pos_z);
  FillTVector3ToDouble(lpos[0][3], &out_minus_gtr300_fit_pos_x, &out_minus_gtr300_fit_pos_y, &out_minus_gtr300_fit_pos_z);
  FillTVector3ToDouble(lpos[1][0], &out_plus_ssd_fit_pos_x,     &out_plus_ssd_fit_pos_y,     &out_plus_ssd_fit_pos_z);
  FillTVector3ToDouble(lpos[1][1], &out_plus_gtr100_fit_pos_x,  &out_plus_gtr100_fit_pos_y,  &out_plus_gtr100_fit_pos_z);
  FillTVector3ToDouble(lpos[1][2], &out_plus_gtr200_fit_pos_x,  &out_plus_gtr200_fit_pos_y,  &out_plus_gtr200_fit_pos_z);
  FillTVector3ToDouble(lpos[1][3], &out_plus_gtr300_fit_pos_x,  &out_plus_gtr300_fit_pos_y,  &out_plus_gtr300_fit_pos_z);
  FillTVector3ToDouble(gpos[0][0], &out_minus_ssd_fit_pos_gx,    &out_minus_ssd_fit_pos_gy,    &out_minus_ssd_fit_pos_gz);
  FillTVector3ToDouble(gpos[0][1], &out_minus_gtr100_fit_pos_gx, &out_minus_gtr100_fit_pos_gy, &out_minus_gtr100_fit_pos_gz);
  FillTVector3ToDouble(gpos[0][2], &out_minus_gtr200_fit_pos_gx, &out_minus_gtr200_fit_pos_gy, &out_minus_gtr200_fit_pos_gz);
  FillTVector3ToDouble(gpos[0][3], &out_minus_gtr300_fit_pos_gx, &out_minus_gtr300_fit_pos_gy, &out_minus_gtr300_fit_pos_gz);
  FillTVector3ToDouble(gpos[1][0], &out_plus_ssd_fit_pos_gx,     &out_plus_ssd_fit_pos_gy,     &out_plus_ssd_fit_pos_gz);
  FillTVector3ToDouble(gpos[1][1], &out_plus_gtr100_fit_pos_gx,  &out_plus_gtr100_fit_pos_gy,  &out_plus_gtr100_fit_pos_gz);
  FillTVector3ToDouble(gpos[1][2], &out_plus_gtr200_fit_pos_gx,  &out_plus_gtr200_fit_pos_gy,  &out_plus_gtr200_fit_pos_gz);
  FillTVector3ToDouble(gpos[1][3], &out_plus_gtr300_fit_pos_gx,  &out_plus_gtr300_fit_pos_gy,  &out_plus_gtr300_fit_pos_gz);
  out_minus_ssd_fit_mom.emplace_back(lmom[0][0].Mag());
  out_minus_gtr100_fit_mom.emplace_back(lmom[0][1].Mag());
  out_minus_gtr200_fit_mom.emplace_back(lmom[0][2].Mag());
  out_minus_gtr300_fit_mom.emplace_back(lmom[0][3].Mag());
  out_plus_ssd_fit_mom.emplace_back(lmom[1][0].Mag());
  out_plus_gtr100_fit_mom.emplace_back(lmom[1][1].Mag());
  out_plus_gtr200_fit_mom.emplace_back(lmom[1][2].Mag());
  out_plus_gtr300_fit_mom.emplace_back(lmom[1][3].Mag());
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
  FillTVector3ToDouble(lres[0][0], &out_minus_ssd_fit_res_x,     &out_minus_ssd_fit_res_y,     &out_minus_ssd_fit_res_z);
  FillTVector3ToDouble(lres[0][1], &out_minus_gtr100_fit_res_x,  &out_minus_gtr100_fit_res_y,  &out_minus_gtr100_fit_res_z);
  FillTVector3ToDouble(lres[0][2], &out_minus_gtr200_fit_res_x,  &out_minus_gtr200_fit_res_y,  &out_minus_gtr200_fit_res_z);
  FillTVector3ToDouble(lres[0][3], &out_minus_gtr300_fit_res_x,  &out_minus_gtr300_fit_res_y,  &out_minus_gtr300_fit_res_z);
  FillTVector3ToDouble(lres[1][0], &out_plus_ssd_fit_res_x,      &out_plus_ssd_fit_res_y,      &out_plus_ssd_fit_res_z);
  FillTVector3ToDouble(lres[1][1], &out_plus_gtr100_fit_res_x,   &out_plus_gtr100_fit_res_y,   &out_plus_gtr100_fit_res_z);
  FillTVector3ToDouble(lres[1][2], &out_plus_gtr200_fit_res_x,   &out_plus_gtr200_fit_res_y,   &out_plus_gtr200_fit_res_z);
  FillTVector3ToDouble(lres[1][3], &out_plus_gtr300_fit_res_x,   &out_plus_gtr300_fit_res_y,   &out_plus_gtr300_fit_res_z);
  out_ee_mass.emplace_back(CalcMass(pt_param::kCalcEEMassFlag,     tmp_minus_mom, tmp_plus_mom));
  out_pipi_mass.emplace_back(CalcMass(pt_param::kCalcPiPiMassFlag, tmp_minus_mom, tmp_plus_mom));
  out_pip_mass.emplace_back(CalcMass(pt_param::kCalcPiPMassFlag,   tmp_minus_mom, tmp_plus_mom));
  FillKsTrackInfo();
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

void E16ANA_TrackAnalyzerFromTree::PionPairTracking(const int track_index_pair[]) {
  AddPionTracks(track_index_pair);
  pair_fitter->SetRungeKuttaStepSize(pt_param::kStepSize);
  pair_fitter->SetMaxSteps(pt_param::kMaxSteps);
  out_chi_square.emplace_back(pair_fitter->Fit(pt_param::kVertexXyFixFlag, pt_param::kPyFixFlag, pt_param::kVertexZFixFlagPion,
                                               pt_param::kMinuitStrategy, pt_param::kMaxFunctionCalls));
  UpdateFitResult(track_index_pair);
  return;
}

void E16ANA_TrackAnalyzerFromTree::AnalyzePionTrackPairs(std::vector<int>* selected_track_index) {
  int n_selected_tracks = selected_track_index->size();
  for (int index0 = 0; index0 < n_selected_tracks - 1; ++index0) {
    auto selected_track_index0 = selected_track_index->at(index0);
    auto charge0 = rk_charge->at(selected_track_index0);
    for (int index1 = index0 + 1; index1 < n_selected_tracks; ++index1) {
      auto selected_track_index1 = selected_track_index->at(index1);
      auto charge1 = rk_charge->at(selected_track_index1);
      if (charge0 == charge1) {
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
      PionPairTracking(track_index_pair);
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
    if (particle_flag == cmn_param::kElectronFlag) {
      AnalyzeTrackPairs(&selected_track_index);
    } else if (particle_flag == cmn_param::kPionFlag) {
      AnalyzePionTrackPairs(&selected_track_index);
    }
  }
  out_file->Write();
  return;
}
