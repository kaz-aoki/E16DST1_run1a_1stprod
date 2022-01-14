//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Oct 30 15:37:48 2021 by ROOT version 6.18/04
// from TTree tree/tree
// found on file: /ccj/w/data03a/E16/user/ichikawa/lsf_file/21102900-v1/root/run030734_0_001_ev12000-14999.root
//////////////////////////////////////////////////////////

#ifndef E16ANA_TrackAnalyzerFromTree_h
#define E16ANA_TrackAnalyzerFromTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

#include "TVector3.h"
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_MagneticFieldMap.hh"
#include "E16ANA_MultiTrack.hh"
#include "E16ANA_TrackConstant.hh"

class E16ANA_TrackAnalyzerFromTree {
 public:
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

  // Declaration of leaf types
  Int_t           run_id;
  Int_t           event_id;
  Int_t           spill_id;
  ULong64_t       timestamp_in_spill;
  Int_t           n_fill;
  Int_t           n_ssd_clusters;
  std::vector<int>     *ssd_cluster_id;
  std::vector<int>     *ssd_cluster_mid;
  std::vector<double>  *ssd_cluster_x;
  std::vector<double>  *ssd_cluster_gx;
  std::vector<double>  *ssd_cluster_gz;
  std::vector<float>   *ssd_cluster_adc;
  std::vector<double>  *ssd_cluster_t;
  Int_t           n_gtr100x_clusters;
  std::vector<int>     *gtr100x_cluster_id;
  std::vector<int>     *gtr100x_cluster_mid;
  std::vector<double>  *gtr100x_cluster_x;
  std::vector<double>  *gtr100x_cluster_gx;
  std::vector<double>  *gtr100x_cluster_gz;
  std::vector<float>   *gtr100x_cluster_adc;
  std::vector<double>  *gtr100x_cluster_t;
  Int_t           n_gtr200x_clusters;
  std::vector<int>     *gtr200x_cluster_id;
  std::vector<int>     *gtr200x_cluster_mid;
  std::vector<double>  *gtr200x_cluster_x;
  std::vector<double>  *gtr200x_cluster_gx;
  std::vector<double>  *gtr200x_cluster_gz;
  std::vector<float>   *gtr200x_cluster_adc;
  std::vector<double>  *gtr200x_cluster_t;
  Int_t           n_gtr300x_clusters;
  std::vector<int>     *gtr300x_cluster_id;
  std::vector<int>     *gtr300x_cluster_mid;
  std::vector<double>  *gtr300x_cluster_x;
  std::vector<double>  *gtr300x_cluster_gx;
  std::vector<double>  *gtr300x_cluster_gz;
  std::vector<float>   *gtr300x_cluster_adc;
  std::vector<double>  *gtr300x_cluster_t;
  Int_t           n_gtr100y_clusters;
  std::vector<int>     *gtr100y_cluster_id;
  std::vector<int>     *gtr100y_cluster_mid;
  std::vector<double>  *gtr100y_cluster_y;
  std::vector<float>   *gtr100y_cluster_adc;
  std::vector<double>  *gtr100y_cluster_t;
  Int_t           n_gtr100yb_clusters;
  std::vector<int>     *gtr100yb_cluster_id;
  std::vector<int>     *gtr100yb_cluster_mid;
  std::vector<double>  *gtr100yb_cluster_y;
  std::vector<float>   *gtr100yb_cluster_adc;
  std::vector<double>  *gtr100yb_cluster_t;
  Int_t           n_gtr200y_clusters;
  std::vector<int>     *gtr200y_cluster_id;
  std::vector<int>     *gtr200y_cluster_mid;
  std::vector<double>  *gtr200y_cluster_y;
  std::vector<float>   *gtr200y_cluster_adc;
  std::vector<double>  *gtr200y_cluster_t;
  Int_t           n_gtr300y_clusters;
  std::vector<int>     *gtr300y_cluster_id;
  std::vector<int>     *gtr300y_cluster_mid;
  std::vector<double>  *gtr300y_cluster_y;
  std::vector<float>   *gtr300y_cluster_adc;
  std::vector<double>  *gtr300y_cluster_t;
  Int_t           n_hbd_clusters;
  std::vector<int>     *hbd_cluster_id;
  std::vector<int>     *hbd_cluster_mid;
  std::vector<double>  *hbd_cluster_x;
  std::vector<double>  *hbd_cluster_y;
  std::vector<double>  *hbd_cluster_gx;
  std::vector<double>  *hbd_cluster_gy;
  std::vector<double>  *hbd_cluster_gz;
  std::vector<float>   *hbd_cluster_adc;
  std::vector<double>  *hbd_cluster_t;
  std::vector<float>   *hbd_cluster_ftime;
  std::vector<float>   *hbd_cluster_tdiff;
  std::vector<int>     *hbd_cluster_size;
  std::vector<float>   *hbd_cluster_eprob;
  std::vector<float>   *hbd_cluster_cprob;
  Int_t           n_lg_hits;
  std::vector<int>     *lg_hit_id;
  std::vector<int>     *lg_hit_mid;
  std::vector<double>  *lg_hit_x;
  std::vector<double>  *lg_hit_y;
  std::vector<double>  *lg_hit_gx;
  std::vector<double>  *lg_hit_gy;
  std::vector<double>  *lg_hit_gz;
  std::vector<float>   *lg_hit_adc;
  std::vector<float>   *lg_hit_t;
  std::vector<int>     *lg_hit_npeaks;
  std::vector<int>     *lg_hit_fflag;
  Int_t           n_x_cands;
  Int_t           n_y_cands;
  Int_t           n_cands;
  Int_t           n_selected;
  Int_t           n_pairs;
  Int_t           n_refit_pairs;
  std::vector<int>     *track_id;
  std::vector<bool>    *has_e_hbd_cluster;
  std::vector<bool>    *has_e_lg_hit;
  std::vector<bool>    *is_large_residual;
  std::vector<bool>    *is_near_target;
  std::vector<bool>    *is_cluster_used;
  std::vector<bool>    *is_selected;
  std::vector<double>  *x_rough_fit_chi_square;
  std::vector<double>  *x_rough_fit_coef0;
  std::vector<double>  *x_rough_fit_coef1;
  std::vector<double>  *x_rough_fit_coef2;
  std::vector<double>  *y_rough_fit_chi_square;
  std::vector<double>  *y_rough_fit_coef0;
  std::vector<double>  *y_rough_fit_coef1;
  std::vector<double>  *chi_square;
  std::vector<int>     *n_steps;
  std::vector<int>     *n_calls;
  std::vector<int>     *rk_charge;
  std::vector<double>  *rk_hit_init_mom_gx;
  std::vector<double>  *rk_hit_init_mom_gy;
  std::vector<double>  *rk_hit_init_mom_gz;
  std::vector<double>  *rk_hit_init_pos_gx;
  std::vector<double>  *rk_hit_init_pos_gy;
  std::vector<double>  *rk_hit_init_pos_gz;
  std::vector<int>     *rk_hit_ssd_id;
  std::vector<double>  *rk_hit_ssd_gx;
  std::vector<double>  *rk_hit_ssd_gy;
  std::vector<double>  *rk_hit_ssd_gz;
  std::vector<float>   *rk_hit_ssd_adc;
  std::vector<float>   *rk_hit_ssd_t;
  std::vector<int>     *rk_hit_gtr100_xid;
  std::vector<int>     *rk_hit_gtr100_yid;
  std::vector<double>  *rk_hit_gtr100_gx;
  std::vector<double>  *rk_hit_gtr100_gy;
  std::vector<double>  *rk_hit_gtr100_gz;
  std::vector<float>   *rk_hit_gtr100_xadc;
  std::vector<float>   *rk_hit_gtr100_yadc;
  std::vector<float>   *rk_hit_gtr100_xt;
  std::vector<float>   *rk_hit_gtr100_yt;
  std::vector<int>     *rk_hit_gtr200_xid;
  std::vector<int>     *rk_hit_gtr200_yid;
  std::vector<double>  *rk_hit_gtr200_gx;
  std::vector<double>  *rk_hit_gtr200_gy;
  std::vector<double>  *rk_hit_gtr200_gz;
  std::vector<float>   *rk_hit_gtr200_xadc;
  std::vector<float>   *rk_hit_gtr200_yadc;
  std::vector<float>   *rk_hit_gtr200_xt;
  std::vector<int>     *rk_hit_gtr300_xid;
  std::vector<int>     *rk_hit_gtr300_yid;
  std::vector<float>   *rk_hit_gtr200_yt;
  std::vector<double>  *rk_hit_gtr300_gx;
  std::vector<double>  *rk_hit_gtr300_gy;
  std::vector<double>  *rk_hit_gtr300_gz;
  std::vector<float>   *rk_hit_gtr300_xadc;
  std::vector<float>   *rk_hit_gtr300_yadc;
  std::vector<float>   *rk_hit_gtr300_xt;
  std::vector<float>   *rk_hit_gtr300_yt;
  std::vector<double>  *rk_fit_init_mom_gx;
  std::vector<double>  *rk_fit_init_mom_gy;
  std::vector<double>  *rk_fit_init_mom_gz;
  std::vector<double>  *rk_fit_init_pos_gx;
  std::vector<double>  *rk_fit_init_pos_gy;
  std::vector<double>  *rk_fit_init_pos_gz;
  std::vector<int>     *rk_fit_ssd_mid;
  std::vector<double>  *rk_fit_ssd_gx;
  std::vector<double>  *rk_fit_ssd_gy;
  std::vector<double>  *rk_fit_ssd_gz;
  std::vector<int>     *rk_fit_gtr100_mid;
  std::vector<double>  *rk_fit_gtr100_gx;
  std::vector<double>  *rk_fit_gtr100_gy;
  std::vector<double>  *rk_fit_gtr100_gz;
  std::vector<int>     *rk_fit_gtr200_mid;
  std::vector<double>  *rk_fit_gtr200_gx;
  std::vector<double>  *rk_fit_gtr200_gy;
  std::vector<double>  *rk_fit_gtr200_gz;
  std::vector<int>     *rk_fit_gtr300_mid;
  std::vector<double>  *rk_fit_gtr300_gx;
  std::vector<double>  *rk_fit_gtr300_gy;
  std::vector<double>  *rk_fit_gtr300_gz;
  std::vector<int>     *rk_fit_hbd_mid;
  std::vector<double>  *rk_fit_hbd_x;
  std::vector<double>  *rk_fit_hbd_y;
  std::vector<double>  *rk_fit_hbd_gx;
  std::vector<double>  *rk_fit_hbd_gy;
  std::vector<double>  *rk_fit_hbd_gz;
  std::vector<int>     *rk_fit_lg_c_mid;
  std::vector<double>  *rk_fit_lg_c_x;
  std::vector<double>  *rk_fit_lg_c_y;
  std::vector<double>  *rk_fit_lg_c_gx;
  std::vector<double>  *rk_fit_lg_c_gy;
  std::vector<double>  *rk_fit_lg_c_gz;
  std::vector<int>     *rk_fit_lg_b_mid;
  std::vector<double>  *rk_fit_lg_b_x;
  std::vector<double>  *rk_fit_lg_b_y;
  std::vector<double>  *rk_fit_lg_b_gx;
  std::vector<double>  *rk_fit_lg_b_gy;
  std::vector<double>  *rk_fit_lg_b_gz;
  std::vector<int>     *rk_fit_lg_a_mid;
  std::vector<double>  *rk_fit_lg_a_x;
  std::vector<double>  *rk_fit_lg_a_y;
  std::vector<double>  *rk_fit_lg_a_gx;
  std::vector<double>  *rk_fit_lg_a_gy;
  std::vector<double>  *rk_fit_lg_a_gz;
  std::vector<double>  *rk_res_init_pos_gx;
  std::vector<double>  *rk_res_init_pos_gy;
  std::vector<double>  *rk_res_init_pos_gz;
  std::vector<double>  *rk_res_init_mom_gx;
  std::vector<double>  *rk_res_init_mom_gy;
  std::vector<double>  *rk_res_init_mom_gz;
  std::vector<double>  *rk_res_ssd_x;
  std::vector<double>  *rk_res_gtr100_x;
  std::vector<double>  *rk_res_gtr100_y;
  std::vector<double>  *rk_res_gtr200_x;
  std::vector<double>  *rk_res_gtr200_y;
  std::vector<double>  *rk_res_gtr300_x;
  std::vector<double>  *rk_res_gtr300_y;
  std::vector<double>  *rk_proj_tgt0_gx;
  std::vector<double>  *rk_proj_tgt0_gy;
  std::vector<double>  *rk_proj_tgt0_gz;
  std::vector<double>  *rk_proj_tgt1_gx;
  std::vector<double>  *rk_proj_tgt1_gy;
  std::vector<double>  *rk_proj_tgt1_gz;
  std::vector<double>  *rk_proj_tgt2_gx;
  std::vector<double>  *rk_proj_tgt2_gy;
  std::vector<double>  *rk_proj_tgt2_gz;
  std::vector<double>  *rk_proj_tgt0_mom_gx;
  std::vector<double>  *rk_proj_tgt0_mom_gy;
  std::vector<double>  *rk_proj_tgt0_mom_gz;
  std::vector<double>  *rk_proj_tgt1_mom_gx;
  std::vector<double>  *rk_proj_tgt1_mom_gy;
  std::vector<double>  *rk_proj_tgt1_mom_gz;
  std::vector<double>  *rk_proj_tgt2_mom_gx;
  std::vector<double>  *rk_proj_tgt2_mom_gy;
  std::vector<double>  *rk_proj_tgt2_mom_gz;
  std::vector<double>  *rk_proj_x0_gx;
  std::vector<double>  *rk_proj_x0_gy;
  std::vector<double>  *rk_proj_x0_gz;
  std::vector<double>  *rk_proj_x0_mom_gx;
  std::vector<double>  *rk_proj_x0_mom_gy;
  std::vector<double>  *rk_proj_x0_mom_gz;
  std::vector<int>     *rk_proj_n_hbd;
  std::vector<int>     *rk_proj_hbd0_id;
  std::vector<int>     *rk_proj_hbd0_mid;
  std::vector<double>  *rk_proj_hbd0_x;
  std::vector<double>  *rk_proj_hbd0_y;
  std::vector<float>   *rk_proj_hbd0_adc;
  std::vector<float>   *rk_proj_hbd0_t;
  std::vector<float>   *rk_proj_hbd0_ftime;
  std::vector<float>   *rk_proj_hbd0_tdiff;
  std::vector<int>     *rk_proj_hbd0_size;
  std::vector<float>   *rk_proj_hbd0_eprob;
  std::vector<float>   *rk_proj_hbd0_cprob;
  std::vector<int>     *rk_proj_hbd1_id;
  std::vector<int>     *rk_proj_hbd1_mid;
  std::vector<double>  *rk_proj_hbd1_x;
  std::vector<double>  *rk_proj_hbd1_y;
  std::vector<float>   *rk_proj_hbd1_adc;
  std::vector<float>   *rk_proj_hbd1_t;
  std::vector<float>   *rk_proj_hbd1_ftime;
  std::vector<float>   *rk_proj_hbd1_tdiff;
  std::vector<int>     *rk_proj_hbd1_size;
  std::vector<float>   *rk_proj_hbd1_eprob;
  std::vector<float>   *rk_proj_hbd1_cprob;
  std::vector<int>     *rk_proj_hbd2_id;
  std::vector<int>     *rk_proj_hbd2_mid;
  std::vector<double>  *rk_proj_hbd2_x;
  std::vector<double>  *rk_proj_hbd2_y;
  std::vector<float>   *rk_proj_hbd2_adc;
  std::vector<float>   *rk_proj_hbd2_t;
  std::vector<float>   *rk_proj_hbd2_ftime;
  std::vector<float>   *rk_proj_hbd2_tdiff;
  std::vector<int>     *rk_proj_hbd2_size;
  std::vector<float>   *rk_proj_hbd2_eprob;
  std::vector<float>   *rk_proj_hbd2_cprob;
  std::vector<int>     *rk_proj_hbd3_id;
  std::vector<int>     *rk_proj_hbd3_mid;
  std::vector<double>  *rk_proj_hbd3_x;
  std::vector<double>  *rk_proj_hbd3_y;
  std::vector<float>   *rk_proj_hbd3_adc;
  std::vector<float>   *rk_proj_hbd3_t;
  std::vector<float>   *rk_proj_hbd3_ftime;
  std::vector<float>   *rk_proj_hbd3_tdiff;
  std::vector<int>     *rk_proj_hbd3_size;
  std::vector<float>   *rk_proj_hbd3_eprob;
  std::vector<float>   *rk_proj_hbd3_cprob;
  std::vector<int>     *rk_proj_n_lg;
  std::vector<int>     *rk_proj_lg0_id;
  std::vector<int>     *rk_proj_lg0_mid;
  std::vector<double>  *rk_proj_lg0_x;
  std::vector<double>  *rk_proj_lg0_y;
  std::vector<float>   *rk_proj_lg0_adc;
  std::vector<float>   *rk_proj_lg0_t;
  std::vector<int>     *rk_proj_lg0_npeaks;
  std::vector<int>     *rk_proj_lg0_fflag;
  std::vector<int>     *rk_proj_lg1_id;
  std::vector<int>     *rk_proj_lg1_mid;
  std::vector<double>  *rk_proj_lg1_x;
  std::vector<double>  *rk_proj_lg1_y;
  std::vector<float>   *rk_proj_lg1_adc;
  std::vector<float>   *rk_proj_lg1_t;
  std::vector<int>     *rk_proj_lg1_npeaks;
  std::vector<int>     *rk_proj_lg1_fflag;
  std::vector<int>     *rk_proj_lg2_id;
  std::vector<int>     *rk_proj_lg2_mid;
  std::vector<double>  *rk_proj_lg2_x;
  std::vector<double>  *rk_proj_lg2_y;
  std::vector<float>   *rk_proj_lg2_adc;
  std::vector<float>   *rk_proj_lg2_t;
  std::vector<int>     *rk_proj_lg2_npeaks;
  std::vector<int>     *rk_proj_lg2_fflag;
  std::vector<int>     *rk_proj_lg3_id;
  std::vector<int>     *rk_proj_lg3_mid;
  std::vector<double>  *rk_proj_lg3_x;
  std::vector<double>  *rk_proj_lg3_y;
  std::vector<float>   *rk_proj_lg3_adc;
  std::vector<float>   *rk_proj_lg3_t;
  std::vector<int>     *rk_proj_lg3_npeaks;
  std::vector<int>     *rk_proj_lg3_fflag;
  std::vector<int>     *rk_pair_minus_track_id;
  std::vector<int>     *rk_pair_minus_gtr300_mid;
  std::vector<double>  *rk_pair_minus_chi_square;
  std::vector<double>  *rk_pair_minus_mom_gx;
  std::vector<double>  *rk_pair_minus_mom_gy;
  std::vector<double>  *rk_pair_minus_mom_gz;
  std::vector<double>  *rk_pair_minus_ssd_t;
  std::vector<double>  *rk_pair_minus_lg0_t;
  std::vector<double>  *rk_pair_minus_lg1_t;
  std::vector<double>  *rk_pair_minus_lg2_t;
  std::vector<double>  *rk_pair_minus_lg3_t;
  std::vector<int>     *rk_pair_plus_track_id;
  std::vector<int>     *rk_pair_plus_gtr300_mid;
  std::vector<double>  *rk_pair_plus_chi_square;
  std::vector<double>  *rk_pair_plus_mom_gx;
  std::vector<double>  *rk_pair_plus_mom_gy;
  std::vector<double>  *rk_pair_plus_mom_gz;
  std::vector<double>  *rk_pair_plus_ssd_t;
  std::vector<double>  *rk_pair_plus_lg0_t;
  std::vector<double>  *rk_pair_plus_lg1_t;
  std::vector<double>  *rk_pair_plus_lg2_t;
  std::vector<double>  *rk_pair_plus_lg3_t;
  std::vector<double>  *rk_pair_distance;
  std::vector<double>  *rk_pair_vtx_gx;
  std::vector<double>  *rk_pair_vtx_gy;
  std::vector<double>  *rk_pair_vtx_gz;
  std::vector<bool>    *rk_pair_is_refit;
  std::vector<bool>    *rk_pair_is_selected;
  std::vector<double>  *rk_pair_chi_square_refit;
  std::vector<double>  *rk_pair_vtx_refit_gx;
  std::vector<double>  *rk_pair_vtx_refit_gy;
  std::vector<double>  *rk_pair_vtx_refit_gz;
  std::vector<double>  *rk_pair_minus_mom_refit_gx;
  std::vector<double>  *rk_pair_minus_mom_refit_gy;
  std::vector<double>  *rk_pair_minus_mom_refit_gz;
  std::vector<double>  *rk_pair_plus_mom_refit_gx;
  std::vector<double>  *rk_pair_plus_mom_refit_gy;
  std::vector<double>  *rk_pair_plus_mom_refit_gz;
  std::vector<double>  *rk_pair_minus_ssd_pos_refit_gx;
  std::vector<double>  *rk_pair_minus_ssd_pos_refit_gy;
  std::vector<double>  *rk_pair_minus_ssd_pos_refit_gz;
  std::vector<double>  *rk_pair_minus_gtr100_pos_refit_gx;
  std::vector<double>  *rk_pair_minus_gtr100_pos_refit_gy;
  std::vector<double>  *rk_pair_minus_gtr100_pos_refit_gz;
  std::vector<double>  *rk_pair_minus_gtr200_pos_refit_gx;
  std::vector<double>  *rk_pair_minus_gtr200_pos_refit_gy;
  std::vector<double>  *rk_pair_minus_gtr200_pos_refit_gz;
  std::vector<double>  *rk_pair_minus_gtr300_pos_refit_gx;
  std::vector<double>  *rk_pair_minus_gtr300_pos_refit_gy;
  std::vector<double>  *rk_pair_minus_gtr300_pos_refit_gz;
  std::vector<double>  *rk_pair_plus_ssd_pos_refit_gx;
  std::vector<double>  *rk_pair_plus_ssd_pos_refit_gy;
  std::vector<double>  *rk_pair_plus_ssd_pos_refit_gz;
  std::vector<double>  *rk_pair_plus_gtr100_pos_refit_gx;
  std::vector<double>  *rk_pair_plus_gtr100_pos_refit_gy;
  std::vector<double>  *rk_pair_plus_gtr100_pos_refit_gz;
  std::vector<double>  *rk_pair_plus_gtr200_pos_refit_gx;
  std::vector<double>  *rk_pair_plus_gtr200_pos_refit_gy;
  std::vector<double>  *rk_pair_plus_gtr200_pos_refit_gz;
  std::vector<double>  *rk_pair_plus_gtr300_pos_refit_gx;
  std::vector<double>  *rk_pair_plus_gtr300_pos_refit_gy;
  std::vector<double>  *rk_pair_plus_gtr300_pos_refit_gz;
  std::vector<double>  *rk_pair_minus_ssd_mom_refit_gx;
  std::vector<double>  *rk_pair_minus_ssd_mom_refit_gy;
  std::vector<double>  *rk_pair_minus_ssd_mom_refit_gz;
  std::vector<double>  *rk_pair_minus_gtr100_mom_refit_gx;
  std::vector<double>  *rk_pair_minus_gtr100_mom_refit_gy;
  std::vector<double>  *rk_pair_minus_gtr100_mom_refit_gz;
  std::vector<double>  *rk_pair_minus_gtr200_mom_refit_gx;
  std::vector<double>  *rk_pair_minus_gtr200_mom_refit_gy;
  std::vector<double>  *rk_pair_minus_gtr200_mom_refit_gz;
  std::vector<double>  *rk_pair_minus_gtr300_mom_refit_gx;
  std::vector<double>  *rk_pair_minus_gtr300_mom_refit_gy;
  std::vector<double>  *rk_pair_minus_gtr300_mom_refit_gz;
  std::vector<double>  *rk_pair_plus_ssd_mom_refit_gx;
  std::vector<double>  *rk_pair_plus_ssd_mom_refit_gy;
  std::vector<double>  *rk_pair_plus_ssd_mom_refit_gz;
  std::vector<double>  *rk_pair_plus_gtr100_mom_refit_gx;
  std::vector<double>  *rk_pair_plus_gtr100_mom_refit_gy;
  std::vector<double>  *rk_pair_plus_gtr100_mom_refit_gz;
  std::vector<double>  *rk_pair_plus_gtr200_mom_refit_gx;
  std::vector<double>  *rk_pair_plus_gtr200_mom_refit_gy;
  std::vector<double>  *rk_pair_plus_gtr200_mom_refit_gz;
  std::vector<double>  *rk_pair_plus_gtr300_mom_refit_gx;
  std::vector<double>  *rk_pair_plus_gtr300_mom_refit_gy;
  std::vector<double>  *rk_pair_plus_gtr300_mom_refit_gz;
  std::vector<double>  *rk_pair_minus_ssd_res_refit_x;
  std::vector<double>  *rk_pair_minus_ssd_res_refit_y;
  std::vector<double>  *rk_pair_minus_ssd_res_refit_z;
  std::vector<double>  *rk_pair_minus_gtr100_res_refit_x;
  std::vector<double>  *rk_pair_minus_gtr100_res_refit_y;
  std::vector<double>  *rk_pair_minus_gtr100_res_refit_z;
  std::vector<double>  *rk_pair_minus_gtr200_res_refit_x;
  std::vector<double>  *rk_pair_minus_gtr200_res_refit_y;
  std::vector<double>  *rk_pair_minus_gtr200_res_refit_z;
  std::vector<double>  *rk_pair_minus_gtr300_res_refit_x;
  std::vector<double>  *rk_pair_minus_gtr300_res_refit_y;
  std::vector<double>  *rk_pair_minus_gtr300_res_refit_z;
  std::vector<double>  *rk_pair_plus_ssd_res_refit_x;
  std::vector<double>  *rk_pair_plus_ssd_res_refit_y;
  std::vector<double>  *rk_pair_plus_ssd_res_refit_z;
  std::vector<double>  *rk_pair_plus_gtr100_res_refit_x;
  std::vector<double>  *rk_pair_plus_gtr100_res_refit_y;
  std::vector<double>  *rk_pair_plus_gtr100_res_refit_z;
  std::vector<double>  *rk_pair_plus_gtr200_res_refit_x;
  std::vector<double>  *rk_pair_plus_gtr200_res_refit_y;
  std::vector<double>  *rk_pair_plus_gtr200_res_refit_z;
  std::vector<double>  *rk_pair_plus_gtr300_res_refit_x;
  std::vector<double>  *rk_pair_plus_gtr300_res_refit_y;
  std::vector<double>  *rk_pair_plus_gtr300_res_refit_z;
  std::vector<double>  *rk_pair_mass_refit;

  // List of branches
  TBranch        *b_run_id;   //!
  TBranch        *b_event_id;   //!
  TBranch        *b_spill_id;   //!
  TBranch        *b_timestamp_in_spill;   //!
  TBranch        *b_n_fill;   //!
  TBranch        *b_n_ssd_clusters;   //!
  TBranch        *b_ssd_cluster_id;   //!
  TBranch        *b_ssd_cluster_mid;   //!
  TBranch        *b_ssd_cluster_x;   //!
  TBranch        *b_ssd_cluster_gx;   //!
  TBranch        *b_ssd_cluster_gz;   //!
  TBranch        *b_ssd_cluster_adc;   //!
  TBranch        *b_ssd_cluster_t;   //!
  TBranch        *b_n_gtr100x_clusters;   //!
  TBranch        *b_gtr100x_cluster_id;   //!
  TBranch        *b_gtr100x_cluster_mid;   //!
  TBranch        *b_gtr100x_cluster_x;   //!
  TBranch        *b_gtr100x_cluster_gx;   //!
  TBranch        *b_gtr100x_cluster_gz;   //!
  TBranch        *b_gtr100x_cluster_adc;   //!
  TBranch        *b_gtr100x_cluster_t;   //!
  TBranch        *b_n_gtr200x_clusters;   //!
  TBranch        *b_gtr200x_cluster_id;   //!
  TBranch        *b_gtr200x_cluster_mid;   //!
  TBranch        *b_gtr200x_cluster_x;   //!
  TBranch        *b_gtr200x_cluster_gx;   //!
  TBranch        *b_gtr200x_cluster_gz;   //!
  TBranch        *b_gtr200x_cluster_adc;   //!
  TBranch        *b_gtr200x_cluster_t;   //!
  TBranch        *b_n_gtr300x_clusters;   //!
  TBranch        *b_gtr300x_cluster_id;   //!
  TBranch        *b_gtr300x_cluster_mid;   //!
  TBranch        *b_gtr300x_cluster_x;   //!
  TBranch        *b_gtr300x_cluster_gx;   //!
  TBranch        *b_gtr300x_cluster_gz;   //!
  TBranch        *b_gtr300x_cluster_adc;   //!
  TBranch        *b_gtr300x_cluster_t;   //!
  TBranch        *b_n_gtr100y_clusters;   //!
  TBranch        *b_gtr100y_cluster_id;   //!
  TBranch        *b_gtr100y_cluster_mid;   //!
  TBranch        *b_gtr100y_cluster_y;   //!
  TBranch        *b_gtr100y_cluster_adc;   //!
  TBranch        *b_gtr100y_cluster_t;   //!
  TBranch        *b_n_gtr100yb_clusters;   //!
  TBranch        *b_gtr100yb_cluster_id;   //!
  TBranch        *b_gtr100yb_cluster_mid;   //!
  TBranch        *b_gtr100yb_cluster_y;   //!
  TBranch        *b_gtr100yb_cluster_adc;   //!
  TBranch        *b_gtr100yb_cluster_t;   //!
  TBranch        *b_n_gtr200y_clusters;   //!
  TBranch        *b_gtr200y_cluster_id;   //!
  TBranch        *b_gtr200y_cluster_mid;   //!
  TBranch        *b_gtr200y_cluster_y;   //!
  TBranch        *b_gtr200y_cluster_adc;   //!
  TBranch        *b_gtr200y_cluster_t;   //!
  TBranch        *b_n_gtr300y_clusters;   //!
  TBranch        *b_gtr300y_cluster_id;   //!
  TBranch        *b_gtr300y_cluster_mid;   //!
  TBranch        *b_gtr300y_cluster_y;   //!
  TBranch        *b_gtr300y_cluster_adc;   //!
  TBranch        *b_gtr300y_cluster_t;   //!
  TBranch        *b_n_hbd_clusters;   //!
  TBranch        *b_hbd_cluster_id;   //!
  TBranch        *b_hbd_cluster_mid;   //!
  TBranch        *b_hbd_cluster_x;   //!
  TBranch        *b_hbd_cluster_y;   //!
  TBranch        *b_hbd_cluster_gx;   //!
  TBranch        *b_hbd_cluster_gy;   //!
  TBranch        *b_hbd_cluster_gz;   //!
  TBranch        *b_hbd_cluster_adc;   //!
  TBranch        *b_hbd_cluster_t;   //!
  TBranch        *b_hbd_cluster_ftime;   //!
  TBranch        *b_hbd_cluster_tdiff;   //!
  TBranch        *b_hbd_cluster_size;   //!
  TBranch        *b_hbd_cluster_eprob;   //!
  TBranch        *b_hbd_cluster_cprob;   //!
  TBranch        *b_n_lg_hits;   //!
  TBranch        *b_lg_hit_id;   //!
  TBranch        *b_lg_hit_mid;   //!
  TBranch        *b_lg_hit_x;   //!
  TBranch        *b_lg_hit_y;   //!
  TBranch        *b_lg_hit_gx;   //!
  TBranch        *b_lg_hit_gy;   //!
  TBranch        *b_lg_hit_gz;   //!
  TBranch        *b_lg_hit_adc;   //!
  TBranch        *b_lg_hit_t;   //!
  TBranch        *b_lg_hit_npeaks;   //!
  TBranch        *b_lg_hit_fflag;   //!
  TBranch        *b_n_x_cands;   //!
  TBranch        *b_n_y_cands;   //!
  TBranch        *b_n_cands;   //!
  TBranch        *b_n_selected;   //!
  TBranch        *b_n_pairs;   //!
  TBranch        *b_n_refit_pairs;   //!
  TBranch        *b_track_id;   //!
  TBranch        *b_has_e_hbd_cluster;   //!
  TBranch        *b_has_e_lg_hit;   //!
  TBranch        *b_is_large_residual;   //!
  TBranch        *b_is_near_target;   //!
  TBranch        *b_is_cluster_used;   //!
  TBranch        *b_is_selected;   //!
  TBranch        *b_x_rough_fit_chi_square;   //!
  TBranch        *b_x_rough_fit_coef0;   //!
  TBranch        *b_x_rough_fit_coef1;   //!
  TBranch        *b_x_rough_fit_coef2;   //!
  TBranch        *b_y_rough_fit_chi_square;   //!
  TBranch        *b_y_rough_fit_coef0;   //!
  TBranch        *b_y_rough_fit_coef1;   //!
  TBranch        *b_chi_square;   //!
  TBranch        *b_n_steps;   //!
  TBranch        *b_n_calls;   //!
  TBranch        *b_rk_charge;   //!
  TBranch        *b_rk_hit_init_mom_gx;   //!
  TBranch        *b_rk_hit_init_mom_gy;   //!
  TBranch        *b_rk_hit_init_mom_gz;   //!
  TBranch        *b_rk_hit_init_pos_gx;   //!
  TBranch        *b_rk_hit_init_pos_gy;   //!
  TBranch        *b_rk_hit_init_pos_gz;   //!
  TBranch        *b_rk_hit_ssd_id;   //!
  TBranch        *b_rk_hit_ssd_gx;   //!
  TBranch        *b_rk_hit_ssd_gy;   //!
  TBranch        *b_rk_hit_ssd_gz;   //!
  TBranch        *b_rk_hit_ssd_adc;   //!
  TBranch        *b_rk_hit_ssd_t;   //!
  TBranch        *b_rk_hit_gtr100_xid;   //!
  TBranch        *b_rk_hit_gtr100_yid;   //!
  TBranch        *b_rk_hit_gtr100_gx;   //!
  TBranch        *b_rk_hit_gtr100_gy;   //!
  TBranch        *b_rk_hit_gtr100_gz;   //!
  TBranch        *b_rk_hit_gtr100_xadc;   //!
  TBranch        *b_rk_hit_gtr100_yadc;   //!
  TBranch        *b_rk_hit_gtr100_xt;   //!
  TBranch        *b_rk_hit_gtr100_yt;   //!
  TBranch        *b_rk_hit_gtr200_xid;   //!
  TBranch        *b_rk_hit_gtr200_yid;   //!
  TBranch        *b_rk_hit_gtr200_gx;   //!
  TBranch        *b_rk_hit_gtr200_gy;   //!
  TBranch        *b_rk_hit_gtr200_gz;   //!
  TBranch        *b_rk_hit_gtr200_xadc;   //!
  TBranch        *b_rk_hit_gtr200_yadc;   //!
  TBranch        *b_rk_hit_gtr200_xt;   //!
  TBranch        *b_rk_hit_gtr300_xid;   //!
  TBranch        *b_rk_hit_gtr300_yid;   //!
  TBranch        *b_rk_hit_gtr200_yt;   //!
  TBranch        *b_rk_hit_gtr300_gx;   //!
  TBranch        *b_rk_hit_gtr300_gy;   //!
  TBranch        *b_rk_hit_gtr300_gz;   //!
  TBranch        *b_rk_hit_gtr300_xadc;   //!
  TBranch        *b_rk_hit_gtr300_yadc;   //!
  TBranch        *b_rk_hit_gtr300_xt;   //!
  TBranch        *b_rk_hit_gtr300_yt;   //!
  TBranch        *b_rk_fit_init_mom_gx;   //!
  TBranch        *b_rk_fit_init_mom_gy;   //!
  TBranch        *b_rk_fit_init_mom_gz;   //!
  TBranch        *b_rk_fit_init_pos_gx;   //!
  TBranch        *b_rk_fit_init_pos_gy;   //!
  TBranch        *b_rk_fit_init_pos_gz;   //!
  TBranch        *b_rk_fit_ssd_mid;   //!
  TBranch        *b_rk_fit_ssd_gx;   //!
  TBranch        *b_rk_fit_ssd_gy;   //!
  TBranch        *b_rk_fit_ssd_gz;   //!
  TBranch        *b_rk_fit_gtr100_mid;   //!
  TBranch        *b_rk_fit_gtr100_gx;   //!
  TBranch        *b_rk_fit_gtr100_gy;   //!
  TBranch        *b_rk_fit_gtr100_gz;   //!
  TBranch        *b_rk_fit_gtr200_mid;   //!
  TBranch        *b_rk_fit_gtr200_gx;   //!
  TBranch        *b_rk_fit_gtr200_gy;   //!
  TBranch        *b_rk_fit_gtr200_gz;   //!
  TBranch        *b_rk_fit_gtr300_mid;   //!
  TBranch        *b_rk_fit_gtr300_gx;   //!
  TBranch        *b_rk_fit_gtr300_gy;   //!
  TBranch        *b_rk_fit_gtr300_gz;   //!
  TBranch        *b_rk_fit_hbd_mid;   //!
  TBranch        *b_rk_fit_hbd_x;   //!
  TBranch        *b_rk_fit_hbd_y;   //!
  TBranch        *b_rk_fit_hbd_gx;   //!
  TBranch        *b_rk_fit_hbd_gy;   //!
  TBranch        *b_rk_fit_hbd_gz;   //!
  TBranch        *b_rk_fit_lg_c_mid;   //!
  TBranch        *b_rk_fit_lg_c_x;   //!
  TBranch        *b_rk_fit_lg_c_y;   //!
  TBranch        *b_rk_fit_lg_c_gx;   //!
  TBranch        *b_rk_fit_lg_c_gy;   //!
  TBranch        *b_rk_fit_lg_c_gz;   //!
  TBranch        *b_rk_fit_lg_b_mid;   //!
  TBranch        *b_rk_fit_lg_b_x;   //!
  TBranch        *b_rk_fit_lg_b_y;   //!
  TBranch        *b_rk_fit_lg_b_gx;   //!
  TBranch        *b_rk_fit_lg_b_gy;   //!
  TBranch        *b_rk_fit_lg_b_gz;   //!
  TBranch        *b_rk_fit_lg_a_mid;   //!
  TBranch        *b_rk_fit_lg_a_x;   //!
  TBranch        *b_rk_fit_lg_a_y;   //!
  TBranch        *b_rk_fit_lg_a_gx;   //!
  TBranch        *b_rk_fit_lg_a_gy;   //!
  TBranch        *b_rk_fit_lg_a_gz;   //!
  TBranch        *b_rk_res_init_pos_gx;   //!
  TBranch        *b_rk_res_init_pos_gy;   //!
  TBranch        *b_rk_res_init_pos_gz;   //!
  TBranch        *b_rk_res_init_mom_gx;   //!
  TBranch        *b_rk_res_init_mom_gy;   //!
  TBranch        *b_rk_res_init_mom_gz;   //!
  TBranch        *b_rk_res_ssd_x;   //!
  TBranch        *b_rk_res_gtr100_x;   //!
  TBranch        *b_rk_res_gtr100_y;   //!
  TBranch        *b_rk_res_gtr200_x;   //!
  TBranch        *b_rk_res_gtr200_y;   //!
  TBranch        *b_rk_res_gtr300_x;   //!
  TBranch        *b_rk_res_gtr300_y;   //!
  TBranch        *b_rk_proj_tgt0_gx;   //!
  TBranch        *b_rk_proj_tgt0_gy;   //!
  TBranch        *b_rk_proj_tgt0_gz;   //!
  TBranch        *b_rk_proj_tgt1_gx;   //!
  TBranch        *b_rk_proj_tgt1_gy;   //!
  TBranch        *b_rk_proj_tgt1_gz;   //!
  TBranch        *b_rk_proj_tgt2_gx;   //!
  TBranch        *b_rk_proj_tgt2_gy;   //!
  TBranch        *b_rk_proj_tgt2_gz;   //!
  TBranch        *b_rk_proj_tgt0_mom_gx;   //!
  TBranch        *b_rk_proj_tgt0_mom_gy;   //!
  TBranch        *b_rk_proj_tgt0_mom_gz;   //!
  TBranch        *b_rk_proj_tgt1_mom_gx;   //!
  TBranch        *b_rk_proj_tgt1_mom_gy;   //!
  TBranch        *b_rk_proj_tgt1_mom_gz;   //!
  TBranch        *b_rk_proj_tgt2_mom_gx;   //!
  TBranch        *b_rk_proj_tgt2_mom_gy;   //!
  TBranch        *b_rk_proj_tgt2_mom_gz;   //!
  TBranch        *b_rk_proj_x0_gx;   //!
  TBranch        *b_rk_proj_x0_gy;   //!
  TBranch        *b_rk_proj_x0_gz;   //!
  TBranch        *b_rk_proj_x0_mom_gx;   //!
  TBranch        *b_rk_proj_x0_mom_gy;   //!
  TBranch        *b_rk_proj_x0_mom_gz;   //!
  TBranch        *b_rk_proj_n_hbd;   //!
  TBranch        *b_rk_proj_hbd0_id;   //!
  TBranch        *b_rk_proj_hbd0_mid;   //!
  TBranch        *b_rk_proj_hbd0_x;   //!
  TBranch        *b_rk_proj_hbd0_y;   //!
  TBranch        *b_rk_proj_hbd0_adc;   //!
  TBranch        *b_rk_proj_hbd0_t;   //!
  TBranch        *b_rk_proj_hbd0_ftime;   //!
  TBranch        *b_rk_proj_hbd0_tdiff;   //!
  TBranch        *b_rk_proj_hbd0_size;   //!
  TBranch        *b_rk_proj_hbd0_eprob;   //!
  TBranch        *b_rk_proj_hbd0_cprob;   //!
  TBranch        *b_rk_proj_hbd1_id;   //!
  TBranch        *b_rk_proj_hbd1_mid;   //!
  TBranch        *b_rk_proj_hbd1_x;   //!
  TBranch        *b_rk_proj_hbd1_y;   //!
  TBranch        *b_rk_proj_hbd1_adc;   //!
  TBranch        *b_rk_proj_hbd1_t;   //!
  TBranch        *b_rk_proj_hbd1_ftime;   //!
  TBranch        *b_rk_proj_hbd1_tdiff;   //!
  TBranch        *b_rk_proj_hbd1_size;   //!
  TBranch        *b_rk_proj_hbd1_eprob;   //!
  TBranch        *b_rk_proj_hbd1_cprob;   //!
  TBranch        *b_rk_proj_hbd2_id;   //!
  TBranch        *b_rk_proj_hbd2_mid;   //!
  TBranch        *b_rk_proj_hbd2_x;   //!
  TBranch        *b_rk_proj_hbd2_y;   //!
  TBranch        *b_rk_proj_hbd2_adc;   //!
  TBranch        *b_rk_proj_hbd2_t;   //!
  TBranch        *b_rk_proj_hbd2_ftime;   //!
  TBranch        *b_rk_proj_hbd2_tdiff;   //!
  TBranch        *b_rk_proj_hbd2_size;   //!
  TBranch        *b_rk_proj_hbd2_eprob;   //!
  TBranch        *b_rk_proj_hbd2_cprob;   //!
  TBranch        *b_rk_proj_hbd3_id;   //!
  TBranch        *b_rk_proj_hbd3_mid;   //!
  TBranch        *b_rk_proj_hbd3_x;   //!
  TBranch        *b_rk_proj_hbd3_y;   //!
  TBranch        *b_rk_proj_hbd3_adc;   //!
  TBranch        *b_rk_proj_hbd3_t;   //!
  TBranch        *b_rk_proj_hbd3_ftime;   //!
  TBranch        *b_rk_proj_hbd3_tdiff;   //!
  TBranch        *b_rk_proj_hbd3_size;   //!
  TBranch        *b_rk_proj_hbd3_eprob;   //!
  TBranch        *b_rk_proj_hbd3_cprob;   //!
  TBranch        *b_rk_proj_n_lg;   //!
  TBranch        *b_rk_proj_lg0_id;   //!
  TBranch        *b_rk_proj_lg0_mid;   //!
  TBranch        *b_rk_proj_lg0_x;   //!
  TBranch        *b_rk_proj_lg0_y;   //!
  TBranch        *b_rk_proj_lg0_adc;   //!
  TBranch        *b_rk_proj_lg0_t;   //!
  TBranch        *b_rk_proj_lg0_npeaks;   //!
  TBranch        *b_rk_proj_lg0_fflag;   //!
  TBranch        *b_rk_proj_lg1_id;   //!
  TBranch        *b_rk_proj_lg1_mid;   //!
  TBranch        *b_rk_proj_lg1_x;   //!
  TBranch        *b_rk_proj_lg1_y;   //!
  TBranch        *b_rk_proj_lg1_adc;   //!
  TBranch        *b_rk_proj_lg1_t;   //!
  TBranch        *b_rk_proj_lg1_npeaks;   //!
  TBranch        *b_rk_proj_lg1_fflag;   //!
  TBranch        *b_rk_proj_lg2_id;   //!
  TBranch        *b_rk_proj_lg2_mid;   //!
  TBranch        *b_rk_proj_lg2_x;   //!
  TBranch        *b_rk_proj_lg2_y;   //!
  TBranch        *b_rk_proj_lg2_adc;   //!
  TBranch        *b_rk_proj_lg2_t;   //!
  TBranch        *b_rk_proj_lg2_npeaks;   //!
  TBranch        *b_rk_proj_lg2_fflag;   //!
  TBranch        *b_rk_proj_lg3_id;   //!
  TBranch        *b_rk_proj_lg3_mid;   //!
  TBranch        *b_rk_proj_lg3_x;   //!
  TBranch        *b_rk_proj_lg3_y;   //!
  TBranch        *b_rk_proj_lg3_adc;   //!
  TBranch        *b_rk_proj_lg3_t;   //!
  TBranch        *b_rk_proj_lg3_npeaks;   //!
  TBranch        *b_rk_proj_lg3_fflag;   //!
  TBranch        *b_rk_pair_minus_track_id;   //!
  TBranch        *b_rk_pair_minus_gtr300_mid;   //!
  TBranch        *b_rk_pair_minus_chi_square;   //!
  TBranch        *b_rk_pair_minus_mom_gx;   //!
  TBranch        *b_rk_pair_minus_mom_gy;   //!
  TBranch        *b_rk_pair_minus_mom_gz;   //!
  TBranch        *b_rk_pair_minus_ssd_t;   //!
  TBranch        *b_rk_pair_minus_lg0_t;   //!
  TBranch        *b_rk_pair_minus_lg1_t;   //!
  TBranch        *b_rk_pair_minus_lg2_t;   //!
  TBranch        *b_rk_pair_minus_lg3_t;   //!
  TBranch        *b_rk_pair_plus_track_id;   //!
  TBranch        *b_rk_pair_plus_gtr300_mid;   //!
  TBranch        *b_rk_pair_plus_chi_square;   //!
  TBranch        *b_rk_pair_plus_mom_gx;   //!
  TBranch        *b_rk_pair_plus_mom_gy;   //!
  TBranch        *b_rk_pair_plus_mom_gz;   //!
  TBranch        *b_rk_pair_plus_ssd_t;   //!
  TBranch        *b_rk_pair_plus_lg0_t;   //!
  TBranch        *b_rk_pair_plus_lg1_t;   //!
  TBranch        *b_rk_pair_plus_lg2_t;   //!
  TBranch        *b_rk_pair_plus_lg3_t;   //!
  TBranch        *b_rk_pair_distance;   //!
  TBranch        *b_rk_pair_vtx_gx;   //!
  TBranch        *b_rk_pair_vtx_gy;   //!
  TBranch        *b_rk_pair_vtx_gz;   //!
  TBranch        *b_rk_pair_is_refit;   //!
  TBranch        *b_rk_pair_is_selected;   //!
  TBranch        *b_rk_pair_chi_square_refit;   //!
  TBranch        *b_rk_pair_vtx_refit_gx;   //!
  TBranch        *b_rk_pair_vtx_refit_gy;   //!
  TBranch        *b_rk_pair_vtx_refit_gz;   //!
  TBranch        *b_rk_pair_minus_mom_refit_gx;   //!
  TBranch        *b_rk_pair_minus_mom_refit_gy;   //!
  TBranch        *b_rk_pair_minus_mom_refit_gz;   //!
  TBranch        *b_rk_pair_plus_mom_refit_gx;   //!
  TBranch        *b_rk_pair_plus_mom_refit_gy;   //!
  TBranch        *b_rk_pair_plus_mom_refit_gz;   //!
  TBranch        *b_rk_pair_minus_ssd_pos_refit_gx;   //!
  TBranch        *b_rk_pair_minus_ssd_pos_refit_gy;   //!
  TBranch        *b_rk_pair_minus_ssd_pos_refit_gz;   //!
  TBranch        *b_rk_pair_minus_gtr100_pos_refit_gx;   //!
  TBranch        *b_rk_pair_minus_gtr100_pos_refit_gy;   //!
  TBranch        *b_rk_pair_minus_gtr100_pos_refit_gz;   //!
  TBranch        *b_rk_pair_minus_gtr200_pos_refit_gx;   //!
  TBranch        *b_rk_pair_minus_gtr200_pos_refit_gy;   //!
  TBranch        *b_rk_pair_minus_gtr200_pos_refit_gz;   //!
  TBranch        *b_rk_pair_minus_gtr300_pos_refit_gx;   //!
  TBranch        *b_rk_pair_minus_gtr300_pos_refit_gy;   //!
  TBranch        *b_rk_pair_minus_gtr300_pos_refit_gz;   //!
  TBranch        *b_rk_pair_plus_ssd_pos_refit_gx;   //!
  TBranch        *b_rk_pair_plus_ssd_pos_refit_gy;   //!
  TBranch        *b_rk_pair_plus_ssd_pos_refit_gz;   //!
  TBranch        *b_rk_pair_plus_gtr100_pos_refit_gx;   //!
  TBranch        *b_rk_pair_plus_gtr100_pos_refit_gy;   //!
  TBranch        *b_rk_pair_plus_gtr100_pos_refit_gz;   //!
  TBranch        *b_rk_pair_plus_gtr200_pos_refit_gx;   //!
  TBranch        *b_rk_pair_plus_gtr200_pos_refit_gy;   //!
  TBranch        *b_rk_pair_plus_gtr200_pos_refit_gz;   //!
  TBranch        *b_rk_pair_plus_gtr300_pos_refit_gx;   //!
  TBranch        *b_rk_pair_plus_gtr300_pos_refit_gy;   //!
  TBranch        *b_rk_pair_plus_gtr300_pos_refit_gz;   //!
  TBranch        *b_rk_pair_minus_ssd_mom_refit_gx;   //!
  TBranch        *b_rk_pair_minus_ssd_mom_refit_gy;   //!
  TBranch        *b_rk_pair_minus_ssd_mom_refit_gz;   //!
  TBranch        *b_rk_pair_minus_gtr100_mom_refit_gx;   //!
  TBranch        *b_rk_pair_minus_gtr100_mom_refit_gy;   //!
  TBranch        *b_rk_pair_minus_gtr100_mom_refit_gz;   //!
  TBranch        *b_rk_pair_minus_gtr200_mom_refit_gx;   //!
  TBranch        *b_rk_pair_minus_gtr200_mom_refit_gy;   //!
  TBranch        *b_rk_pair_minus_gtr200_mom_refit_gz;   //!
  TBranch        *b_rk_pair_minus_gtr300_mom_refit_gx;   //!
  TBranch        *b_rk_pair_minus_gtr300_mom_refit_gy;   //!
  TBranch        *b_rk_pair_minus_gtr300_mom_refit_gz;   //!
  TBranch        *b_rk_pair_plus_ssd_mom_refit_gx;   //!
  TBranch        *b_rk_pair_plus_ssd_mom_refit_gy;   //!
  TBranch        *b_rk_pair_plus_ssd_mom_refit_gz;   //!
  TBranch        *b_rk_pair_plus_gtr100_mom_refit_gx;   //!
  TBranch        *b_rk_pair_plus_gtr100_mom_refit_gy;   //!
  TBranch        *b_rk_pair_plus_gtr100_mom_refit_gz;   //!
  TBranch        *b_rk_pair_plus_gtr200_mom_refit_gx;   //!
  TBranch        *b_rk_pair_plus_gtr200_mom_refit_gy;   //!
  TBranch        *b_rk_pair_plus_gtr200_mom_refit_gz;   //!
  TBranch        *b_rk_pair_plus_gtr300_mom_refit_gx;   //!
  TBranch        *b_rk_pair_plus_gtr300_mom_refit_gy;   //!
  TBranch        *b_rk_pair_plus_gtr300_mom_refit_gz;   //!
  TBranch        *b_rk_pair_minus_ssd_res_refit_x;   //!
  TBranch        *b_rk_pair_minus_ssd_res_refit_y;   //!
  TBranch        *b_rk_pair_minus_ssd_res_refit_z;   //!
  TBranch        *b_rk_pair_minus_gtr100_res_refit_x;   //!
  TBranch        *b_rk_pair_minus_gtr100_res_refit_y;   //!
  TBranch        *b_rk_pair_minus_gtr100_res_refit_z;   //!
  TBranch        *b_rk_pair_minus_gtr200_res_refit_x;   //!
  TBranch        *b_rk_pair_minus_gtr200_res_refit_y;   //!
  TBranch        *b_rk_pair_minus_gtr200_res_refit_z;   //!
  TBranch        *b_rk_pair_minus_gtr300_res_refit_x;   //!
  TBranch        *b_rk_pair_minus_gtr300_res_refit_y;   //!
  TBranch        *b_rk_pair_minus_gtr300_res_refit_z;   //!
  TBranch        *b_rk_pair_plus_ssd_res_refit_x;   //!
  TBranch        *b_rk_pair_plus_ssd_res_refit_y;   //!
  TBranch        *b_rk_pair_plus_ssd_res_refit_z;   //!
  TBranch        *b_rk_pair_plus_gtr100_res_refit_x;   //!
  TBranch        *b_rk_pair_plus_gtr100_res_refit_y;   //!
  TBranch        *b_rk_pair_plus_gtr100_res_refit_z;   //!
  TBranch        *b_rk_pair_plus_gtr200_res_refit_x;   //!
  TBranch        *b_rk_pair_plus_gtr200_res_refit_y;   //!
  TBranch        *b_rk_pair_plus_gtr200_res_refit_z;   //!
  TBranch        *b_rk_pair_plus_gtr300_res_refit_x;   //!
  TBranch        *b_rk_pair_plus_gtr300_res_refit_y;   //!
  TBranch        *b_rk_pair_plus_gtr300_res_refit_z;   //!
  TBranch        *b_rk_pair_mass_refit;   //!

  E16ANA_TrackAnalyzerFromTree(TTree *tree,   int _particle_flag,
                               E16ANA_GeometryV2* _geometry, E16ANA_MagneticFieldMap* _bfield_map, E16ANA_MultiTrack* _pair_fitter, TFile* _out_file);
  E16ANA_TrackAnalyzerFromTree(TChain *chain, int _particle_flag,
                               E16ANA_GeometryV2* _geometry, E16ANA_MagneticFieldMap* _bfield_map, E16ANA_MultiTrack* _pair_fitter, TFile* _out_file);
  virtual ~E16ANA_TrackAnalyzerFromTree();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
 private:
  void InitOutTree();
  void ClearOutBranch();
  bool IsGoodTrack(int track_index);
  double CalcSingleTrackChiSquareWoTarget(int track_index);
  bool IsGoodPionTrack(int track_index);
  void CheckUsedClusters(int track_index, std::array<std::vector<int>, E16ANA_TrackConstant::kNumTrackingLayers>* used_cluster_ids,
                         std::vector<int>* selected_track_index);
  void SelectTrack(int track_index, std::array<std::vector<int>, E16ANA_TrackConstant::kNumTrackingLayers>* used_cluster_ids,
                         std::vector<int>* selected_track_index);
  void SelectTracks(std::vector<int>* selected_track_index);
  void AddTracks(const int track_index_pair[], double tgt_z);
  void FillTVector3ToDouble(TVector3 t_vector, std::vector<double>* x, std::vector<double>* y, std::vector<double>* z);
  double CalcMass(int flag, TVector3 mom0, TVector3 mom1);
  void ProjectionX0(int pair_index, TVector3 pos, TVector3 mom);
  void FillKsTrackInfo();
  void UpdateFitResult(const int track_index_pair[]);
  void PairTracking(const int track_index_pair[], double tgt_z);
  std::vector<int> SortedTrackPairIndex();
  bool IsGoodPair(const int track_index_pair);
  void CheckUsedTracks(const int track_index_pair, std::vector<int>* used_minus_tracks, std::vector<int>* used_plus_tracks);
  void SelectTrackPair(const int track_index_pair, std::vector<int>* used_minus_tracks, std::vector<int>* used_plus_tracks);
  void SelectTrackPairs();
  void AnalyzeTrackPairs(std::vector<int>* selected_track_index);
  double SearchVertex(const int track_index_pair[], TVector3* vtx_pos, TVector3* minus_mom, TVector3* plus_mom);
  void AddPionTracks(const int track_index_pair[]);
  void PionPairTracking(const int track_index_pair[]);
  void AnalyzePionTrackPairs(std::vector<int>* selected_track_index);
  int particle_flag; // 0 : electron, 1 : pion
  E16ANA_GeometryV2* geometry;
  E16ANA_MagneticFieldMap* bfield_map;
  E16ANA_MultiTrack* pair_fitter;
  TFile* out_file;
  TTree* out_tree;
  int out_run_id;
  int out_event_id;
  int out_n_tracks;
  int out_n_pairs;
  int out_n_selected_pairs;
  std::vector<bool> out_is_selected;
  std::vector<int> out_minus_track_id;
  std::vector<int> out_plus_track_id;
  std::vector<double> out_chi_square;
  std::vector<double> out_vtx_gx;
  std::vector<double> out_vtx_gy;
  std::vector<double> out_vtx_gz;
  std::vector<double> out_minus_mom;
  std::vector<double> out_minus_mom_gx;
  std::vector<double> out_minus_mom_gy;
  std::vector<double> out_minus_mom_gz;
  std::vector<double> out_plus_mom;
  std::vector<double> out_plus_mom_gx;
  std::vector<double> out_plus_mom_gy;
  std::vector<double> out_plus_mom_gz;
  std::vector<int> out_minus_ssd_mid;
  std::vector<int> out_minus_gtr100_mid;
  std::vector<int> out_minus_gtr200_mid;
  std::vector<int> out_minus_gtr300_mid;
  std::vector<int> out_plus_ssd_mid;
  std::vector<int> out_plus_gtr100_mid;
  std::vector<int> out_plus_gtr200_mid;
  std::vector<int> out_plus_gtr300_mid;
  std::vector<double> out_minus_proj_hbd_max_adc;
  std::vector<double> out_minus_proj_lg_max_adc;
  std::vector<double> out_plus_proj_hbd_max_adc;
  std::vector<double> out_plus_proj_lg_max_adc;
  std::vector<double> out_minus_ssd_hit_pos_gx;
  std::vector<double> out_minus_ssd_hit_pos_gy;
  std::vector<double> out_minus_ssd_hit_pos_gz;
  std::vector<double> out_minus_gtr100_hit_pos_gx;
  std::vector<double> out_minus_gtr100_hit_pos_gy;
  std::vector<double> out_minus_gtr100_hit_pos_gz;
  std::vector<double> out_minus_gtr200_hit_pos_gx;
  std::vector<double> out_minus_gtr200_hit_pos_gy;
  std::vector<double> out_minus_gtr200_hit_pos_gz;
  std::vector<double> out_minus_gtr300_hit_pos_gx;
  std::vector<double> out_minus_gtr300_hit_pos_gy;
  std::vector<double> out_minus_gtr300_hit_pos_gz;
  std::vector<double> out_plus_ssd_hit_pos_gx;
  std::vector<double> out_plus_ssd_hit_pos_gy;
  std::vector<double> out_plus_ssd_hit_pos_gz;
  std::vector<double> out_plus_gtr100_hit_pos_gx;
  std::vector<double> out_plus_gtr100_hit_pos_gy;
  std::vector<double> out_plus_gtr100_hit_pos_gz;
  std::vector<double> out_plus_gtr200_hit_pos_gx;
  std::vector<double> out_plus_gtr200_hit_pos_gy;
  std::vector<double> out_plus_gtr200_hit_pos_gz;
  std::vector<double> out_plus_gtr300_hit_pos_gx;
  std::vector<double> out_plus_gtr300_hit_pos_gy;
  std::vector<double> out_plus_gtr300_hit_pos_gz;
  std::vector<double> out_minus_ssd_fit_pos_x;
  std::vector<double> out_minus_ssd_fit_pos_y;
  std::vector<double> out_minus_ssd_fit_pos_z;
  std::vector<double> out_minus_gtr100_fit_pos_x;
  std::vector<double> out_minus_gtr100_fit_pos_y;
  std::vector<double> out_minus_gtr100_fit_pos_z;
  std::vector<double> out_minus_gtr200_fit_pos_x;
  std::vector<double> out_minus_gtr200_fit_pos_y;
  std::vector<double> out_minus_gtr200_fit_pos_z;
  std::vector<double> out_minus_gtr300_fit_pos_x;
  std::vector<double> out_minus_gtr300_fit_pos_y;
  std::vector<double> out_minus_gtr300_fit_pos_z;
  std::vector<double> out_plus_ssd_fit_pos_x;
  std::vector<double> out_plus_ssd_fit_pos_y;
  std::vector<double> out_plus_ssd_fit_pos_z;
  std::vector<double> out_plus_gtr100_fit_pos_x;
  std::vector<double> out_plus_gtr100_fit_pos_y;
  std::vector<double> out_plus_gtr100_fit_pos_z;
  std::vector<double> out_plus_gtr200_fit_pos_x;
  std::vector<double> out_plus_gtr200_fit_pos_y;
  std::vector<double> out_plus_gtr200_fit_pos_z;
  std::vector<double> out_plus_gtr300_fit_pos_x;
  std::vector<double> out_plus_gtr300_fit_pos_y;
  std::vector<double> out_plus_gtr300_fit_pos_z;
  std::vector<double> out_minus_ssd_fit_pos_gx;
  std::vector<double> out_minus_ssd_fit_pos_gy;
  std::vector<double> out_minus_ssd_fit_pos_gz;
  std::vector<double> out_minus_gtr100_fit_pos_gx;
  std::vector<double> out_minus_gtr100_fit_pos_gy;
  std::vector<double> out_minus_gtr100_fit_pos_gz;
  std::vector<double> out_minus_gtr200_fit_pos_gx;
  std::vector<double> out_minus_gtr200_fit_pos_gy;
  std::vector<double> out_minus_gtr200_fit_pos_gz;
  std::vector<double> out_minus_gtr300_fit_pos_gx;
  std::vector<double> out_minus_gtr300_fit_pos_gy;
  std::vector<double> out_minus_gtr300_fit_pos_gz;
  std::vector<double> out_plus_ssd_fit_pos_gx;
  std::vector<double> out_plus_ssd_fit_pos_gy;
  std::vector<double> out_plus_ssd_fit_pos_gz;
  std::vector<double> out_plus_gtr100_fit_pos_gx;
  std::vector<double> out_plus_gtr100_fit_pos_gy;
  std::vector<double> out_plus_gtr100_fit_pos_gz;
  std::vector<double> out_plus_gtr200_fit_pos_gx;
  std::vector<double> out_plus_gtr200_fit_pos_gy;
  std::vector<double> out_plus_gtr200_fit_pos_gz;
  std::vector<double> out_plus_gtr300_fit_pos_gx;
  std::vector<double> out_plus_gtr300_fit_pos_gy;
  std::vector<double> out_plus_gtr300_fit_pos_gz;
  std::vector<double> out_minus_ssd_fit_mom;
  std::vector<double> out_minus_ssd_fit_mom_x;
  std::vector<double> out_minus_ssd_fit_mom_y;
  std::vector<double> out_minus_ssd_fit_mom_z;
  std::vector<double> out_minus_ssd_fit_mom_tan;
  std::vector<double> out_minus_ssd_fit_mom_gx;
  std::vector<double> out_minus_ssd_fit_mom_gy;
  std::vector<double> out_minus_ssd_fit_mom_gz;
  std::vector<double> out_minus_gtr100_fit_mom;
  std::vector<double> out_minus_gtr100_fit_mom_x;
  std::vector<double> out_minus_gtr100_fit_mom_y;
  std::vector<double> out_minus_gtr100_fit_mom_z;
  std::vector<double> out_minus_gtr100_fit_mom_tan;
  std::vector<double> out_minus_gtr100_fit_mom_gx;
  std::vector<double> out_minus_gtr100_fit_mom_gy;
  std::vector<double> out_minus_gtr100_fit_mom_gz;
  std::vector<double> out_minus_gtr200_fit_mom;
  std::vector<double> out_minus_gtr200_fit_mom_x;
  std::vector<double> out_minus_gtr200_fit_mom_y;
  std::vector<double> out_minus_gtr200_fit_mom_z;
  std::vector<double> out_minus_gtr200_fit_mom_tan;
  std::vector<double> out_minus_gtr200_fit_mom_gx;
  std::vector<double> out_minus_gtr200_fit_mom_gy;
  std::vector<double> out_minus_gtr200_fit_mom_gz;
  std::vector<double> out_minus_gtr300_fit_mom;
  std::vector<double> out_minus_gtr300_fit_mom_x;
  std::vector<double> out_minus_gtr300_fit_mom_y;
  std::vector<double> out_minus_gtr300_fit_mom_z;
  std::vector<double> out_minus_gtr300_fit_mom_tan;
  std::vector<double> out_minus_gtr300_fit_mom_gx;
  std::vector<double> out_minus_gtr300_fit_mom_gy;
  std::vector<double> out_minus_gtr300_fit_mom_gz;
  std::vector<double> out_plus_ssd_fit_mom;
  std::vector<double> out_plus_ssd_fit_mom_x;
  std::vector<double> out_plus_ssd_fit_mom_y;
  std::vector<double> out_plus_ssd_fit_mom_z;
  std::vector<double> out_plus_ssd_fit_mom_tan;
  std::vector<double> out_plus_ssd_fit_mom_gx;
  std::vector<double> out_plus_ssd_fit_mom_gy;
  std::vector<double> out_plus_ssd_fit_mom_gz;
  std::vector<double> out_plus_gtr100_fit_mom;
  std::vector<double> out_plus_gtr100_fit_mom_x;
  std::vector<double> out_plus_gtr100_fit_mom_y;
  std::vector<double> out_plus_gtr100_fit_mom_z;
  std::vector<double> out_plus_gtr100_fit_mom_tan;
  std::vector<double> out_plus_gtr100_fit_mom_gx;
  std::vector<double> out_plus_gtr100_fit_mom_gy;
  std::vector<double> out_plus_gtr100_fit_mom_gz;
  std::vector<double> out_plus_gtr200_fit_mom;
  std::vector<double> out_plus_gtr200_fit_mom_x;
  std::vector<double> out_plus_gtr200_fit_mom_y;
  std::vector<double> out_plus_gtr200_fit_mom_z;
  std::vector<double> out_plus_gtr200_fit_mom_tan;
  std::vector<double> out_plus_gtr200_fit_mom_gx;
  std::vector<double> out_plus_gtr200_fit_mom_gy;
  std::vector<double> out_plus_gtr200_fit_mom_gz;
  std::vector<double> out_plus_gtr300_fit_mom;
  std::vector<double> out_plus_gtr300_fit_mom_x;
  std::vector<double> out_plus_gtr300_fit_mom_y;
  std::vector<double> out_plus_gtr300_fit_mom_z;
  std::vector<double> out_plus_gtr300_fit_mom_tan;
  std::vector<double> out_plus_gtr300_fit_mom_gx;
  std::vector<double> out_plus_gtr300_fit_mom_gy;
  std::vector<double> out_plus_gtr300_fit_mom_gz;
  std::vector<double> out_minus_ssd_fit_res_x;
  std::vector<double> out_minus_ssd_fit_res_y;
  std::vector<double> out_minus_ssd_fit_res_z;
  std::vector<double> out_minus_gtr100_fit_res_x;
  std::vector<double> out_minus_gtr100_fit_res_y;
  std::vector<double> out_minus_gtr100_fit_res_z;
  std::vector<double> out_minus_gtr200_fit_res_x;
  std::vector<double> out_minus_gtr200_fit_res_y;
  std::vector<double> out_minus_gtr200_fit_res_z;
  std::vector<double> out_minus_gtr300_fit_res_x;
  std::vector<double> out_minus_gtr300_fit_res_y;
  std::vector<double> out_minus_gtr300_fit_res_z;
  std::vector<double> out_plus_ssd_fit_res_x;
  std::vector<double> out_plus_ssd_fit_res_y;
  std::vector<double> out_plus_ssd_fit_res_z;
  std::vector<double> out_plus_gtr100_fit_res_x;
  std::vector<double> out_plus_gtr100_fit_res_y;
  std::vector<double> out_plus_gtr100_fit_res_z;
  std::vector<double> out_plus_gtr200_fit_res_x;
  std::vector<double> out_plus_gtr200_fit_res_y;
  std::vector<double> out_plus_gtr200_fit_res_z;
  std::vector<double> out_plus_gtr300_fit_res_x;
  std::vector<double> out_plus_gtr300_fit_res_y;
  std::vector<double> out_plus_gtr300_fit_res_z;
  std::vector<double> out_ee_mass;
  std::vector<double> out_pipi_mass;
  std::vector<double> out_pip_mass;
  std::vector<double> out_ks_pos_at_x0_gx;
  std::vector<double> out_ks_pos_at_x0_gy;
  std::vector<double> out_ks_pos_at_x0_gz;
  std::vector<double> out_ks_mom_at_x0_gx;
  std::vector<double> out_ks_mom_at_x0_gy;
  std::vector<double> out_ks_mom_at_x0_gz;
  std::vector<double> out_ks_t_at_x0;

  std::vector<int> out_minus_proj_hbd_id;
  std::vector<int> out_minus_proj_hbd_mid;
  std::vector<double> out_minus_proj_hbd_x;
  std::vector<double> out_minus_proj_hbd_y;
  //  std::vector<double> out_minus_proj_hbd_gx;
  //  std::vector<double> out_minus_proj_hbd_gy;
  //  std::vector<double> out_minus_proj_hbd_gz;
  //  std::vector<float> out_minus_proj_hbd_adc;
  std::vector<double> out_minus_proj_hbd_t;
  std::vector<float> out_minus_proj_hbd_ftime;
  std::vector<float> out_minus_proj_hbd_tdiff;
  std::vector<int> out_minus_proj_hbd_size;
  std::vector<float> out_minus_proj_hbd_eprob;
  std::vector<float> out_minus_proj_hbd_cprob;
  std::vector<int> out_minus_proj_lg_id;
  std::vector<int> out_minus_proj_lg_mid;
  std::vector<double> out_minus_proj_lg_x;
  std::vector<double> out_minus_proj_lg_y;
  //  std::vector<double> out_minus_proj_lg_gx;
  //  std::vector<double> out_minus_proj_lg_gy;
  //  std::vector<double> out_minus_proj_lg_gz;
  //  std::vector<float> out_minus_proj_lg_adc;
  std::vector<float> out_minus_proj_lg_t;
  std::vector<int> out_minus_proj_lg_npeaks;
  std::vector<int> out_minus_proj_lg_fflag;
  std::vector<int> out_plus_proj_hbd_id;
  std::vector<int> out_plus_proj_hbd_mid;
  std::vector<double> out_plus_proj_hbd_x;
  std::vector<double> out_plus_proj_hbd_y;
  //  std::vector<double> out_plus_proj_hbd_gx;
  //  std::vector<double> out_plus_proj_hbd_gy;
  //  std::vector<double> out_plus_proj_hbd_gz;
  //  std::vector<float> out_plus_proj_hbd_adc;
  std::vector<double> out_plus_proj_hbd_t;
  std::vector<float> out_plus_proj_hbd_ftime;
  std::vector<float> out_plus_proj_hbd_tdiff;
  std::vector<int> out_plus_proj_hbd_size;
  std::vector<float> out_plus_proj_hbd_eprob;
  std::vector<float> out_plus_proj_hbd_cprob;
  std::vector<int> out_plus_proj_lg_id;
  std::vector<int> out_plus_proj_lg_mid;
  std::vector<double> out_plus_proj_lg_x;
  std::vector<double> out_plus_proj_lg_y;
  //  std::vector<double> out_plus_proj_lg_gx;
  //  std::vector<double> out_plus_proj_lg_gy;
  //  std::vector<double> out_plus_proj_lg_gz;
  //  std::vector<float> out_plus_proj_lg_adc;
  std::vector<float> out_plus_proj_lg_t;
  std::vector<int> out_plus_proj_lg_npeaks;
  std::vector<int> out_plus_proj_lg_fflag;

  int out_n_hbd_clusters;
  std::vector<int> out_hbd_cluster_id;
  std::vector<int> out_hbd_cluster_mid;
  std::vector<double> out_hbd_cluster_x;
  std::vector<double> out_hbd_cluster_y;
  std::vector<double> out_hbd_cluster_gx;
  std::vector<double> out_hbd_cluster_gy;
  std::vector<double> out_hbd_cluster_gz;
  std::vector<float> out_hbd_cluster_adc;
  std::vector<double> out_hbd_cluster_t;
  std::vector<float> out_hbd_cluster_ftime;
  std::vector<float> out_hbd_cluster_tdiff;
  std::vector<int> out_hbd_cluster_size;
  std::vector<float> out_hbd_cluster_eprob;
  std::vector<float> out_hbd_cluster_cprob;
  int out_n_lg_hits;
  std::vector<int> out_lg_hit_id;
  std::vector<int> out_lg_hit_mid;
  std::vector<double> out_lg_hit_x;
  std::vector<double> out_lg_hit_y;
  std::vector<double> out_lg_hit_gx;
  std::vector<double> out_lg_hit_gy;
  std::vector<double> out_lg_hit_gz;
  std::vector<float> out_lg_hit_adc;
  std::vector<float> out_lg_hit_t;
  std::vector<int> out_lg_hit_npeaks;
  std::vector<int> out_lg_hit_fflag;
  int out_n_single_tracks;
  std::vector<int> out_single_track_id;
  std::vector<double> out_single_chi_square;
  std::vector<int> out_rk_fit_hbd_mid;
  std::vector<double> out_rk_fit_hbd_x;
  std::vector<double> out_rk_fit_hbd_y;
  std::vector<double> out_rk_fit_hbd_gx;
  std::vector<double> out_rk_fit_hbd_gy;
  std::vector<double> out_rk_fit_hbd_gz;
  std::vector<int> out_rk_fit_lg_c_mid;
  std::vector<double> out_rk_fit_lg_c_x;
  std::vector<double> out_rk_fit_lg_c_y;
  std::vector<double> out_rk_fit_lg_c_gx;
  std::vector<double> out_rk_fit_lg_c_gy;
  std::vector<double> out_rk_fit_lg_c_gz;
  std::vector<int> out_rk_fit_lg_b_mid;
  std::vector<double> out_rk_fit_lg_b_x;
  std::vector<double> out_rk_fit_lg_b_y;
  std::vector<double> out_rk_fit_lg_b_gx;
  std::vector<double> out_rk_fit_lg_b_gy;
  std::vector<double> out_rk_fit_lg_b_gz;
  std::vector<int> out_rk_fit_lg_a_mid;
  std::vector<double> out_rk_fit_lg_a_x;
  std::vector<double> out_rk_fit_lg_a_y;
  std::vector<double> out_rk_fit_lg_a_gx;
  std::vector<double> out_rk_fit_lg_a_gy;
  std::vector<double> out_rk_fit_lg_a_gz;
  std::vector<double> out_rk_res_ssd_x;
  std::vector<double> out_rk_res_gtr100_x;
  std::vector<double> out_rk_res_gtr100_y;
  std::vector<double> out_rk_res_gtr200_x;
  std::vector<double> out_rk_res_gtr200_y;
  std::vector<double> out_rk_res_gtr300_x;
  std::vector<double> out_rk_res_gtr300_y;
  std::vector<double> out_rk_proj_tgt0_gx;
  std::vector<double> out_rk_proj_tgt0_gy;
  std::vector<double> out_rk_proj_tgt0_gz;
  std::vector<double> out_rk_proj_tgt1_gx;
  std::vector<double> out_rk_proj_tgt1_gy;
  std::vector<double> out_rk_proj_tgt1_gz;
  std::vector<double> out_rk_proj_tgt2_gx;
  std::vector<double> out_rk_proj_tgt2_gy;
  std::vector<double> out_rk_proj_tgt2_gz;
  std::vector<double> out_rk_proj_tgt0_mom_gx;
  std::vector<double> out_rk_proj_tgt0_mom_gy;
  std::vector<double> out_rk_proj_tgt0_mom_gz;
  std::vector<int> out_rk_proj_n_hbd;
  std::vector<int> out_rk_proj_hbd0_id;
  std::vector<int> out_rk_proj_hbd0_mid;
  std::vector<int> out_rk_proj_hbd1_id;
  std::vector<int> out_rk_proj_hbd1_mid;
  std::vector<int> out_rk_proj_hbd2_id;
  std::vector<int> out_rk_proj_hbd2_mid;
  std::vector<int> out_rk_proj_hbd3_id;
  std::vector<int> out_rk_proj_hbd3_mid;
  std::vector<int> out_rk_proj_n_lg;
  std::vector<int> out_rk_proj_lg0_id;
  std::vector<int> out_rk_proj_lg1_id;
  std::vector<int> out_rk_proj_lg2_id;
  std::vector<int> out_rk_proj_lg3_id;
};

#endif

#ifdef E16ANA_TrackAnalyzerFromTree_cxx
E16ANA_TrackAnalyzerFromTree::E16ANA_TrackAnalyzerFromTree(TTree *tree, int _particle_flag, E16ANA_GeometryV2* _geometry, E16ANA_MagneticFieldMap* _bfield_map, E16ANA_MultiTrack* _pair_fitter, TFile* _out_file)
    : fChain(0), particle_flag(_particle_flag), geometry(_geometry), bfield_map(_bfield_map), pair_fitter(_pair_fitter), out_file(_out_file) {
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
//  if (tree == 0) {
////    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/ccj/w/data03a/E16/user/ichikawa/lsf_file/21102900-v1/root/run030734_0_001_ev12000-14999.root");
////    if (!f || !f->IsOpen()) {
////      f = new TFile("/ccj/w/data03a/E16/user/ichikawa/lsf_file/21102900-v1/root/run030734_0_001_ev12000-14999.root");
////    }
////    f->GetObject("tree",tree);
////
//    std::cerr << "tree == 0" << std::endl;
//    std::exit(-1);
//  }
  Init(tree);
  out_tree = new TTree("tree", "tree");
  InitOutTree();
}

E16ANA_TrackAnalyzerFromTree::E16ANA_TrackAnalyzerFromTree(TChain *chain, int _particle_flag, E16ANA_GeometryV2* _geometry, E16ANA_MagneticFieldMap* _bfield_map, E16ANA_MultiTrack* _pair_fitter, TFile* _out_file)
    : fChain(0), particle_flag(_particle_flag), geometry(_geometry), bfield_map(_bfield_map), pair_fitter(_pair_fitter), out_file(_out_file) {
std::cout << chain->GetEntries() << std::endl;
  Init(dynamic_cast<TTree*>(chain));
  out_tree = new TTree("tree", "tree");
  InitOutTree();
}

E16ANA_TrackAnalyzerFromTree::~E16ANA_TrackAnalyzerFromTree() {
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t E16ANA_TrackAnalyzerFromTree::GetEntry(Long64_t entry) {
// Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t E16ANA_TrackAnalyzerFromTree::LoadTree(Long64_t entry) {
// Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void E16ANA_TrackAnalyzerFromTree::Init(TTree *tree) {
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  ssd_cluster_id = 0;
  ssd_cluster_mid = 0;
  ssd_cluster_x = 0;
  ssd_cluster_gx = 0;
  ssd_cluster_gz = 0;
  ssd_cluster_adc = 0;
  ssd_cluster_t = 0;
  gtr100x_cluster_id = 0;
  gtr100x_cluster_mid = 0;
  gtr100x_cluster_x = 0;
  gtr100x_cluster_gx = 0;
  gtr100x_cluster_gz = 0;
  gtr100x_cluster_adc = 0;
  gtr100x_cluster_t = 0;
  gtr200x_cluster_id = 0;
  gtr200x_cluster_mid = 0;
  gtr200x_cluster_x = 0;
  gtr200x_cluster_gx = 0;
  gtr200x_cluster_gz = 0;
  gtr200x_cluster_adc = 0;
  gtr200x_cluster_t = 0;
  gtr300x_cluster_id = 0;
  gtr300x_cluster_mid = 0;
  gtr300x_cluster_x = 0;
  gtr300x_cluster_gx = 0;
  gtr300x_cluster_gz = 0;
  gtr300x_cluster_adc = 0;
  gtr300x_cluster_t = 0;
  gtr100y_cluster_id = 0;
  gtr100y_cluster_mid = 0;
  gtr100y_cluster_y = 0;
  gtr100y_cluster_adc = 0;
  gtr100y_cluster_t = 0;
  gtr100yb_cluster_id = 0;
  gtr100yb_cluster_mid = 0;
  gtr100yb_cluster_y = 0;
  gtr100yb_cluster_adc = 0;
  gtr100yb_cluster_t = 0;
  gtr200y_cluster_id = 0;
  gtr200y_cluster_mid = 0;
  gtr200y_cluster_y = 0;
  gtr200y_cluster_adc = 0;
  gtr200y_cluster_t = 0;
  gtr300y_cluster_id = 0;
  gtr300y_cluster_mid = 0;
  gtr300y_cluster_y = 0;
  gtr300y_cluster_adc = 0;
  gtr300y_cluster_t = 0;
  hbd_cluster_id = 0;
  hbd_cluster_mid = 0;
  hbd_cluster_x = 0;
  hbd_cluster_y = 0;
  hbd_cluster_gx = 0;
  hbd_cluster_gy = 0;
  hbd_cluster_gz = 0;
  hbd_cluster_adc = 0;
  hbd_cluster_t = 0;
  hbd_cluster_ftime = 0;
  hbd_cluster_tdiff = 0;
  hbd_cluster_size = 0;
  hbd_cluster_eprob = 0;
  hbd_cluster_cprob = 0;
  lg_hit_id = 0;
  lg_hit_mid = 0;
  lg_hit_x = 0;
  lg_hit_y = 0;
  lg_hit_gx = 0;
  lg_hit_gy = 0;
  lg_hit_gz = 0;
  lg_hit_adc = 0;
  lg_hit_t = 0;
  lg_hit_npeaks = 0;
  lg_hit_fflag = 0;
  track_id = 0;
  has_e_hbd_cluster = 0;
  has_e_lg_hit = 0;
  is_large_residual = 0;
  is_near_target = 0;
  is_cluster_used = 0;
  is_selected = 0;
  x_rough_fit_chi_square = 0;
  x_rough_fit_coef0 = 0;
  x_rough_fit_coef1 = 0;
  x_rough_fit_coef2 = 0;
  y_rough_fit_chi_square = 0;
  y_rough_fit_coef0 = 0;
  y_rough_fit_coef1 = 0;
  chi_square = 0;
  n_steps = 0;
  n_calls = 0;
  rk_charge= 0;
  rk_hit_init_mom_gx = 0;
  rk_hit_init_mom_gy = 0;
  rk_hit_init_mom_gz = 0;
  rk_hit_init_pos_gx = 0;
  rk_hit_init_pos_gy = 0;
  rk_hit_init_pos_gz = 0;
  rk_hit_ssd_id = 0;
  rk_hit_ssd_gx = 0;
  rk_hit_ssd_gy = 0;
  rk_hit_ssd_gz = 0;
  rk_hit_ssd_adc = 0;
  rk_hit_ssd_t = 0;
  rk_hit_gtr100_xid = 0;
  rk_hit_gtr100_yid = 0;
  rk_hit_gtr100_gx = 0;
  rk_hit_gtr100_gy = 0;
  rk_hit_gtr100_gz = 0;
  rk_hit_gtr100_xadc = 0;
  rk_hit_gtr100_yadc = 0;
  rk_hit_gtr100_xt = 0;
  rk_hit_gtr100_yt = 0;
  rk_hit_gtr200_xid = 0;
  rk_hit_gtr200_yid = 0;
  rk_hit_gtr200_gx = 0;
  rk_hit_gtr200_gy = 0;
  rk_hit_gtr200_gz = 0;
  rk_hit_gtr200_xadc = 0;
  rk_hit_gtr200_yadc = 0;
  rk_hit_gtr200_xt = 0;
  rk_hit_gtr300_xid = 0;
  rk_hit_gtr300_yid = 0;
  rk_hit_gtr200_yt = 0;
  rk_hit_gtr300_gx = 0;
  rk_hit_gtr300_gy = 0;
  rk_hit_gtr300_gz = 0;
  rk_hit_gtr300_xadc = 0;
  rk_hit_gtr300_yadc = 0;
  rk_hit_gtr300_xt = 0;
  rk_hit_gtr300_yt = 0;
  rk_fit_init_mom_gx = 0;
  rk_fit_init_mom_gy = 0;
  rk_fit_init_mom_gz = 0;
  rk_fit_init_pos_gx = 0;
  rk_fit_init_pos_gy = 0;
  rk_fit_init_pos_gz = 0;
  rk_fit_ssd_mid = 0;
  rk_fit_ssd_gx = 0;
  rk_fit_ssd_gy = 0;
  rk_fit_ssd_gz = 0;
  rk_fit_gtr100_mid = 0;
  rk_fit_gtr100_gx = 0;
  rk_fit_gtr100_gy = 0;
  rk_fit_gtr100_gz = 0;
  rk_fit_gtr200_mid = 0;
  rk_fit_gtr200_gx = 0;
  rk_fit_gtr200_gy = 0;
  rk_fit_gtr200_gz = 0;
  rk_fit_gtr300_mid = 0;
  rk_fit_gtr300_gx = 0;
  rk_fit_gtr300_gy = 0;
  rk_fit_gtr300_gz = 0;
  rk_fit_hbd_mid = 0;
  rk_fit_hbd_x = 0;
  rk_fit_hbd_y = 0;
  rk_fit_hbd_gx = 0;
  rk_fit_hbd_gy = 0;
  rk_fit_hbd_gz = 0;
  rk_fit_lg_c_mid = 0;
  rk_fit_lg_c_x = 0;
  rk_fit_lg_c_y = 0;
  rk_fit_lg_c_gx = 0;
  rk_fit_lg_c_gy = 0;
  rk_fit_lg_c_gz = 0;
  rk_fit_lg_b_mid = 0;
  rk_fit_lg_b_x = 0;
  rk_fit_lg_b_y = 0;
  rk_fit_lg_b_gx = 0;
  rk_fit_lg_b_gy = 0;
  rk_fit_lg_b_gz = 0;
  rk_fit_lg_a_mid = 0;
  rk_fit_lg_a_x = 0;
  rk_fit_lg_a_y = 0;
  rk_fit_lg_a_gx = 0;
  rk_fit_lg_a_gy = 0;
  rk_fit_lg_a_gz = 0;
  rk_res_init_pos_gx = 0;
  rk_res_init_pos_gy = 0;
  rk_res_init_pos_gz = 0;
  rk_res_init_mom_gx = 0;
  rk_res_init_mom_gy = 0;
  rk_res_init_mom_gz = 0;
  rk_res_ssd_x = 0;
  rk_res_gtr100_x = 0;
  rk_res_gtr100_y = 0;
  rk_res_gtr200_x = 0;
  rk_res_gtr200_y = 0;
  rk_res_gtr300_x = 0;
  rk_res_gtr300_y = 0;
  rk_proj_tgt0_gx = 0;
  rk_proj_tgt0_gy = 0;
  rk_proj_tgt0_gz = 0;
  rk_proj_tgt1_gx = 0;
  rk_proj_tgt1_gy = 0;
  rk_proj_tgt1_gz = 0;
  rk_proj_tgt2_gx = 0;
  rk_proj_tgt2_gy = 0;
  rk_proj_tgt2_gz = 0;
  rk_proj_tgt0_mom_gx = 0;
  rk_proj_tgt0_mom_gy = 0;
  rk_proj_tgt0_mom_gz = 0;
  rk_proj_tgt1_mom_gx = 0;
  rk_proj_tgt1_mom_gy = 0;
  rk_proj_tgt1_mom_gz = 0;
  rk_proj_tgt2_mom_gx = 0;
  rk_proj_tgt2_mom_gy = 0;
  rk_proj_tgt2_mom_gz = 0;
  rk_proj_x0_gx = 0;
  rk_proj_x0_gy = 0;
  rk_proj_x0_gz = 0;
  rk_proj_x0_mom_gx = 0;
  rk_proj_x0_mom_gy = 0;
  rk_proj_x0_mom_gz = 0;
  rk_proj_n_hbd = 0;
  rk_proj_hbd0_id = 0;
  rk_proj_hbd0_mid = 0;
  rk_proj_hbd0_x = 0;
  rk_proj_hbd0_y = 0;
  rk_proj_hbd0_adc = 0;
  rk_proj_hbd0_t = 0;
  rk_proj_hbd0_ftime = 0;
  rk_proj_hbd0_tdiff = 0;
  rk_proj_hbd0_size = 0;
  rk_proj_hbd0_eprob = 0;
  rk_proj_hbd0_cprob = 0;
  rk_proj_hbd1_id = 0;
  rk_proj_hbd1_mid = 0;
  rk_proj_hbd1_x = 0;
  rk_proj_hbd1_y = 0;
  rk_proj_hbd1_adc = 0;
  rk_proj_hbd1_t = 0;
  rk_proj_hbd1_ftime = 0;
  rk_proj_hbd1_tdiff = 0;
  rk_proj_hbd1_size = 0;
  rk_proj_hbd1_eprob = 0;
  rk_proj_hbd1_cprob = 0;
  rk_proj_hbd2_id = 0;
  rk_proj_hbd2_mid = 0;
  rk_proj_hbd2_x = 0;
  rk_proj_hbd2_y = 0;
  rk_proj_hbd2_adc = 0;
  rk_proj_hbd2_t = 0;
  rk_proj_hbd2_ftime = 0;
  rk_proj_hbd2_tdiff = 0;
  rk_proj_hbd2_size = 0;
  rk_proj_hbd2_eprob = 0;
  rk_proj_hbd2_cprob = 0;
  rk_proj_hbd3_id = 0;
  rk_proj_hbd3_mid = 0;
  rk_proj_hbd3_x = 0;
  rk_proj_hbd3_y = 0;
  rk_proj_hbd3_adc = 0;
  rk_proj_hbd3_t = 0;
  rk_proj_hbd3_ftime = 0;
  rk_proj_hbd3_tdiff = 0;
  rk_proj_hbd3_size = 0;
  rk_proj_hbd3_eprob = 0;
  rk_proj_hbd3_cprob = 0;
  rk_proj_n_lg = 0;
  rk_proj_lg0_id = 0;
  rk_proj_lg0_mid = 0;
  rk_proj_lg0_x = 0;
  rk_proj_lg0_y = 0;
  rk_proj_lg0_adc = 0;
  rk_proj_lg0_t = 0;
  rk_proj_lg0_npeaks = 0;
  rk_proj_lg0_fflag = 0;
  rk_proj_lg1_id = 0;
  rk_proj_lg1_mid = 0;
  rk_proj_lg1_x = 0;
  rk_proj_lg1_y = 0;
  rk_proj_lg1_adc = 0;
  rk_proj_lg1_t = 0;
  rk_proj_lg1_npeaks = 0;
  rk_proj_lg1_fflag = 0;
  rk_proj_lg2_id = 0;
  rk_proj_lg2_mid = 0;
  rk_proj_lg2_x = 0;
  rk_proj_lg2_y = 0;
  rk_proj_lg2_adc = 0;
  rk_proj_lg2_t = 0;
  rk_proj_lg2_npeaks = 0;
  rk_proj_lg2_fflag = 0;
  rk_proj_lg3_id = 0;
  rk_proj_lg3_mid = 0;
  rk_proj_lg3_x = 0;
  rk_proj_lg3_y = 0;
  rk_proj_lg3_adc = 0;
  rk_proj_lg3_t = 0;
  rk_proj_lg3_npeaks = 0;
  rk_proj_lg3_fflag = 0;
  rk_pair_minus_track_id = 0;
  rk_pair_minus_gtr300_mid = 0;
  rk_pair_minus_chi_square = 0;
  rk_pair_minus_mom_gx = 0;
  rk_pair_minus_mom_gy = 0;
  rk_pair_minus_mom_gz = 0;
  rk_pair_minus_ssd_t = 0;
  rk_pair_minus_lg0_t = 0;
  rk_pair_minus_lg1_t = 0;
  rk_pair_minus_lg2_t = 0;
  rk_pair_minus_lg3_t = 0;
  rk_pair_plus_track_id = 0;
  rk_pair_plus_gtr300_mid = 0;
  rk_pair_plus_chi_square = 0;
  rk_pair_plus_mom_gx = 0;
  rk_pair_plus_mom_gy = 0;
  rk_pair_plus_mom_gz = 0;
  rk_pair_plus_ssd_t = 0;
  rk_pair_plus_lg0_t = 0;
  rk_pair_plus_lg1_t = 0;
  rk_pair_plus_lg2_t = 0;
  rk_pair_plus_lg3_t = 0;
  rk_pair_distance = 0;
  rk_pair_vtx_gx = 0;
  rk_pair_vtx_gy = 0;
  rk_pair_vtx_gz = 0;
  rk_pair_is_refit = 0;
  rk_pair_is_selected = 0;
  rk_pair_chi_square_refit = 0;
  rk_pair_vtx_refit_gx = 0;
  rk_pair_vtx_refit_gy = 0;
  rk_pair_vtx_refit_gz = 0;
  rk_pair_minus_mom_refit_gx = 0;
  rk_pair_minus_mom_refit_gy = 0;
  rk_pair_minus_mom_refit_gz = 0;
  rk_pair_plus_mom_refit_gx = 0;
  rk_pair_plus_mom_refit_gy = 0;
  rk_pair_plus_mom_refit_gz = 0;
  rk_pair_minus_ssd_pos_refit_gx = 0;
  rk_pair_minus_ssd_pos_refit_gy = 0;
  rk_pair_minus_ssd_pos_refit_gz = 0;
  rk_pair_minus_gtr100_pos_refit_gx = 0;
  rk_pair_minus_gtr100_pos_refit_gy = 0;
  rk_pair_minus_gtr100_pos_refit_gz = 0;
  rk_pair_minus_gtr200_pos_refit_gx = 0;
  rk_pair_minus_gtr200_pos_refit_gy = 0;
  rk_pair_minus_gtr200_pos_refit_gz = 0;
  rk_pair_minus_gtr300_pos_refit_gx = 0;
  rk_pair_minus_gtr300_pos_refit_gy = 0;
  rk_pair_minus_gtr300_pos_refit_gz = 0;
  rk_pair_plus_ssd_pos_refit_gx = 0;
  rk_pair_plus_ssd_pos_refit_gy = 0;
  rk_pair_plus_ssd_pos_refit_gz = 0;
  rk_pair_plus_gtr100_pos_refit_gx = 0;
  rk_pair_plus_gtr100_pos_refit_gy = 0;
  rk_pair_plus_gtr100_pos_refit_gz = 0;
  rk_pair_plus_gtr200_pos_refit_gx = 0;
  rk_pair_plus_gtr200_pos_refit_gy = 0;
  rk_pair_plus_gtr200_pos_refit_gz = 0;
  rk_pair_plus_gtr300_pos_refit_gx = 0;
  rk_pair_plus_gtr300_pos_refit_gy = 0;
  rk_pair_plus_gtr300_pos_refit_gz = 0;
  rk_pair_minus_ssd_mom_refit_gx = 0;
  rk_pair_minus_ssd_mom_refit_gy = 0;
  rk_pair_minus_ssd_mom_refit_gz = 0;
  rk_pair_minus_gtr100_mom_refit_gx = 0;
  rk_pair_minus_gtr100_mom_refit_gy = 0;
  rk_pair_minus_gtr100_mom_refit_gz = 0;
  rk_pair_minus_gtr200_mom_refit_gx = 0;
  rk_pair_minus_gtr200_mom_refit_gy = 0;
  rk_pair_minus_gtr200_mom_refit_gz = 0;
  rk_pair_minus_gtr300_mom_refit_gx = 0;
  rk_pair_minus_gtr300_mom_refit_gy = 0;
  rk_pair_minus_gtr300_mom_refit_gz = 0;
  rk_pair_plus_ssd_mom_refit_gx = 0;
  rk_pair_plus_ssd_mom_refit_gy = 0;
  rk_pair_plus_ssd_mom_refit_gz = 0;
  rk_pair_plus_gtr100_mom_refit_gx = 0;
  rk_pair_plus_gtr100_mom_refit_gy = 0;
  rk_pair_plus_gtr100_mom_refit_gz = 0;
  rk_pair_plus_gtr200_mom_refit_gx = 0;
  rk_pair_plus_gtr200_mom_refit_gy = 0;
  rk_pair_plus_gtr200_mom_refit_gz = 0;
  rk_pair_plus_gtr300_mom_refit_gx = 0;
  rk_pair_plus_gtr300_mom_refit_gy = 0;
  rk_pair_plus_gtr300_mom_refit_gz = 0;
  rk_pair_minus_ssd_res_refit_x = 0;
  rk_pair_minus_ssd_res_refit_y = 0;
  rk_pair_minus_ssd_res_refit_z = 0;
  rk_pair_minus_gtr100_res_refit_x = 0;
  rk_pair_minus_gtr100_res_refit_y = 0;
  rk_pair_minus_gtr100_res_refit_z = 0;
  rk_pair_minus_gtr200_res_refit_x = 0;
  rk_pair_minus_gtr200_res_refit_y = 0;
  rk_pair_minus_gtr200_res_refit_z = 0;
  rk_pair_minus_gtr300_res_refit_x = 0;
  rk_pair_minus_gtr300_res_refit_y = 0;
  rk_pair_minus_gtr300_res_refit_z = 0;
  rk_pair_plus_ssd_res_refit_x = 0;
  rk_pair_plus_ssd_res_refit_y = 0;
  rk_pair_plus_ssd_res_refit_z = 0;
  rk_pair_plus_gtr100_res_refit_x = 0;
  rk_pair_plus_gtr100_res_refit_y = 0;
  rk_pair_plus_gtr100_res_refit_z = 0;
  rk_pair_plus_gtr200_res_refit_x = 0;
  rk_pair_plus_gtr200_res_refit_y = 0;
  rk_pair_plus_gtr200_res_refit_z = 0;
  rk_pair_plus_gtr300_res_refit_x = 0;
  rk_pair_plus_gtr300_res_refit_y = 0;
  rk_pair_plus_gtr300_res_refit_z = 0;
  rk_pair_mass_refit = 0;
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("run_id", &run_id, &b_run_id);
  fChain->SetBranchAddress("event_id", &event_id, &b_event_id);
  fChain->SetBranchAddress("spill_id", &spill_id, &b_spill_id);
  fChain->SetBranchAddress("timestamp_in_spill", &timestamp_in_spill, &b_timestamp_in_spill);
  fChain->SetBranchAddress("n_fill", &n_fill, &b_n_fill);
  fChain->SetBranchAddress("n_ssd_clusters", &n_ssd_clusters, &b_n_ssd_clusters);
  fChain->SetBranchAddress("ssd_cluster_id", &ssd_cluster_id, &b_ssd_cluster_id);
  fChain->SetBranchAddress("ssd_cluster_mid", &ssd_cluster_mid, &b_ssd_cluster_mid);
  fChain->SetBranchAddress("ssd_cluster_x", &ssd_cluster_x, &b_ssd_cluster_x);
  fChain->SetBranchAddress("ssd_cluster_gx", &ssd_cluster_gx, &b_ssd_cluster_gx);
  fChain->SetBranchAddress("ssd_cluster_gz", &ssd_cluster_gz, &b_ssd_cluster_gz);
  fChain->SetBranchAddress("ssd_cluster_adc", &ssd_cluster_adc, &b_ssd_cluster_adc);
  fChain->SetBranchAddress("ssd_cluster_t", &ssd_cluster_t, &b_ssd_cluster_t);
  fChain->SetBranchAddress("n_gtr100x_clusters", &n_gtr100x_clusters, &b_n_gtr100x_clusters);
  fChain->SetBranchAddress("gtr100x_cluster_id", &gtr100x_cluster_id, &b_gtr100x_cluster_id);
  fChain->SetBranchAddress("gtr100x_cluster_mid", &gtr100x_cluster_mid, &b_gtr100x_cluster_mid);
  fChain->SetBranchAddress("gtr100x_cluster_x", &gtr100x_cluster_x, &b_gtr100x_cluster_x);
  fChain->SetBranchAddress("gtr100x_cluster_gx", &gtr100x_cluster_gx, &b_gtr100x_cluster_gx);
  fChain->SetBranchAddress("gtr100x_cluster_gz", &gtr100x_cluster_gz, &b_gtr100x_cluster_gz);
  fChain->SetBranchAddress("gtr100x_cluster_adc", &gtr100x_cluster_adc, &b_gtr100x_cluster_adc);
  fChain->SetBranchAddress("gtr100x_cluster_t", &gtr100x_cluster_t, &b_gtr100x_cluster_t);
  fChain->SetBranchAddress("n_gtr200x_clusters", &n_gtr200x_clusters, &b_n_gtr200x_clusters);
  fChain->SetBranchAddress("gtr200x_cluster_id", &gtr200x_cluster_id, &b_gtr200x_cluster_id);
  fChain->SetBranchAddress("gtr200x_cluster_mid", &gtr200x_cluster_mid, &b_gtr200x_cluster_mid);
  fChain->SetBranchAddress("gtr200x_cluster_x", &gtr200x_cluster_x, &b_gtr200x_cluster_x);
  fChain->SetBranchAddress("gtr200x_cluster_gx", &gtr200x_cluster_gx, &b_gtr200x_cluster_gx);
  fChain->SetBranchAddress("gtr200x_cluster_gz", &gtr200x_cluster_gz, &b_gtr200x_cluster_gz);
  fChain->SetBranchAddress("gtr200x_cluster_adc", &gtr200x_cluster_adc, &b_gtr200x_cluster_adc);
  fChain->SetBranchAddress("gtr200x_cluster_t", &gtr200x_cluster_t, &b_gtr200x_cluster_t);
  fChain->SetBranchAddress("n_gtr300x_clusters", &n_gtr300x_clusters, &b_n_gtr300x_clusters);
  fChain->SetBranchAddress("gtr300x_cluster_id", &gtr300x_cluster_id, &b_gtr300x_cluster_id);
  fChain->SetBranchAddress("gtr300x_cluster_mid", &gtr300x_cluster_mid, &b_gtr300x_cluster_mid);
  fChain->SetBranchAddress("gtr300x_cluster_x", &gtr300x_cluster_x, &b_gtr300x_cluster_x);
  fChain->SetBranchAddress("gtr300x_cluster_gx", &gtr300x_cluster_gx, &b_gtr300x_cluster_gx);
  fChain->SetBranchAddress("gtr300x_cluster_gz", &gtr300x_cluster_gz, &b_gtr300x_cluster_gz);
  fChain->SetBranchAddress("gtr300x_cluster_adc", &gtr300x_cluster_adc, &b_gtr300x_cluster_adc);
  fChain->SetBranchAddress("gtr300x_cluster_t", &gtr300x_cluster_t, &b_gtr300x_cluster_t);
  fChain->SetBranchAddress("n_gtr100y_clusters", &n_gtr100y_clusters, &b_n_gtr100y_clusters);
  fChain->SetBranchAddress("gtr100y_cluster_id", &gtr100y_cluster_id, &b_gtr100y_cluster_id);
  fChain->SetBranchAddress("gtr100y_cluster_mid", &gtr100y_cluster_mid, &b_gtr100y_cluster_mid);
  fChain->SetBranchAddress("gtr100y_cluster_y", &gtr100y_cluster_y, &b_gtr100y_cluster_y);
  fChain->SetBranchAddress("gtr100y_cluster_adc", &gtr100y_cluster_adc, &b_gtr100y_cluster_adc);
  fChain->SetBranchAddress("gtr100y_cluster_t", &gtr100y_cluster_t, &b_gtr100y_cluster_t);
  fChain->SetBranchAddress("n_gtr100yb_clusters", &n_gtr100yb_clusters, &b_n_gtr100yb_clusters);
  fChain->SetBranchAddress("gtr100yb_cluster_id", &gtr100yb_cluster_id, &b_gtr100yb_cluster_id);
  fChain->SetBranchAddress("gtr100yb_cluster_mid", &gtr100yb_cluster_mid, &b_gtr100yb_cluster_mid);
  fChain->SetBranchAddress("gtr100yb_cluster_y", &gtr100yb_cluster_y, &b_gtr100yb_cluster_y);
  fChain->SetBranchAddress("gtr100yb_cluster_adc", &gtr100yb_cluster_adc, &b_gtr100yb_cluster_adc);
  fChain->SetBranchAddress("gtr100yb_cluster_t", &gtr100yb_cluster_t, &b_gtr100yb_cluster_t);
  fChain->SetBranchAddress("n_gtr200y_clusters", &n_gtr200y_clusters, &b_n_gtr200y_clusters);
  fChain->SetBranchAddress("gtr200y_cluster_id", &gtr200y_cluster_id, &b_gtr200y_cluster_id);
  fChain->SetBranchAddress("gtr200y_cluster_mid", &gtr200y_cluster_mid, &b_gtr200y_cluster_mid);
  fChain->SetBranchAddress("gtr200y_cluster_y", &gtr200y_cluster_y, &b_gtr200y_cluster_y);
  fChain->SetBranchAddress("gtr200y_cluster_adc", &gtr200y_cluster_adc, &b_gtr200y_cluster_adc);
  fChain->SetBranchAddress("gtr200y_cluster_t", &gtr200y_cluster_t, &b_gtr200y_cluster_t);
  fChain->SetBranchAddress("n_gtr300y_clusters", &n_gtr300y_clusters, &b_n_gtr300y_clusters);
  fChain->SetBranchAddress("gtr300y_cluster_id", &gtr300y_cluster_id, &b_gtr300y_cluster_id);
  fChain->SetBranchAddress("gtr300y_cluster_mid", &gtr300y_cluster_mid, &b_gtr300y_cluster_mid);
  fChain->SetBranchAddress("gtr300y_cluster_y", &gtr300y_cluster_y, &b_gtr300y_cluster_y);
  fChain->SetBranchAddress("gtr300y_cluster_adc", &gtr300y_cluster_adc, &b_gtr300y_cluster_adc);
  fChain->SetBranchAddress("gtr300y_cluster_t", &gtr300y_cluster_t, &b_gtr300y_cluster_t);
  fChain->SetBranchAddress("n_hbd_clusters", &n_hbd_clusters, &b_n_hbd_clusters);
  fChain->SetBranchAddress("hbd_cluster_id", &hbd_cluster_id, &b_hbd_cluster_id);
  fChain->SetBranchAddress("hbd_cluster_mid", &hbd_cluster_mid, &b_hbd_cluster_mid);
  fChain->SetBranchAddress("hbd_cluster_x", &hbd_cluster_x, &b_hbd_cluster_x);
  fChain->SetBranchAddress("hbd_cluster_y", &hbd_cluster_y, &b_hbd_cluster_y);
  fChain->SetBranchAddress("hbd_cluster_gx", &hbd_cluster_gx, &b_hbd_cluster_gx);
  fChain->SetBranchAddress("hbd_cluster_gy", &hbd_cluster_gy, &b_hbd_cluster_gy);
  fChain->SetBranchAddress("hbd_cluster_gz", &hbd_cluster_gz, &b_hbd_cluster_gz);
  fChain->SetBranchAddress("hbd_cluster_adc", &hbd_cluster_adc, &b_hbd_cluster_adc);
  fChain->SetBranchAddress("hbd_cluster_t", &hbd_cluster_t, &b_hbd_cluster_t);
  fChain->SetBranchAddress("hbd_cluster_ftime", &hbd_cluster_ftime, &b_hbd_cluster_ftime);
  fChain->SetBranchAddress("hbd_cluster_tdiff", &hbd_cluster_tdiff, &b_hbd_cluster_tdiff);
  fChain->SetBranchAddress("hbd_cluster_size", &hbd_cluster_size, &b_hbd_cluster_size);
  fChain->SetBranchAddress("hbd_cluster_eprob", &hbd_cluster_eprob, &b_hbd_cluster_eprob);
  fChain->SetBranchAddress("hbd_cluster_cprob", &hbd_cluster_cprob, &b_hbd_cluster_cprob);
  fChain->SetBranchAddress("n_lg_hits", &n_lg_hits, &b_n_lg_hits);
  fChain->SetBranchAddress("lg_hit_id", &lg_hit_id, &b_lg_hit_id);
  fChain->SetBranchAddress("lg_hit_mid", &lg_hit_mid, &b_lg_hit_mid);
  fChain->SetBranchAddress("lg_hit_x", &lg_hit_x, &b_lg_hit_x);
  fChain->SetBranchAddress("lg_hit_y", &lg_hit_y, &b_lg_hit_y);
  fChain->SetBranchAddress("lg_hit_gx", &lg_hit_gx, &b_lg_hit_gx);
  fChain->SetBranchAddress("lg_hit_gy", &lg_hit_gy, &b_lg_hit_gy);
  fChain->SetBranchAddress("lg_hit_gz", &lg_hit_gz, &b_lg_hit_gz);
  fChain->SetBranchAddress("lg_hit_adc", &lg_hit_adc, &b_lg_hit_adc);
  fChain->SetBranchAddress("lg_hit_t", &lg_hit_t, &b_lg_hit_t);
  fChain->SetBranchAddress("lg_hit_npeaks", &lg_hit_npeaks, &b_lg_hit_npeaks);
  fChain->SetBranchAddress("lg_hit_fflag", &lg_hit_fflag, &b_lg_hit_fflag);
  fChain->SetBranchAddress("n_x_cands", &n_x_cands, &b_n_x_cands);
  fChain->SetBranchAddress("n_y_cands", &n_y_cands, &b_n_y_cands);
  fChain->SetBranchAddress("n_cands", &n_cands, &b_n_cands);
  fChain->SetBranchAddress("n_selected", &n_selected, &b_n_selected);
  fChain->SetBranchAddress("n_pairs", &n_pairs, &b_n_pairs);
  fChain->SetBranchAddress("n_refit_pairs", &n_refit_pairs, &b_n_refit_pairs);
  fChain->SetBranchAddress("track_id", &track_id, &b_track_id);
  fChain->SetBranchAddress("has_e_hbd_cluster", &has_e_hbd_cluster, &b_has_e_hbd_cluster);
  fChain->SetBranchAddress("has_e_lg_hit", &has_e_lg_hit, &b_has_e_lg_hit);
  fChain->SetBranchAddress("is_large_residual", &is_large_residual, &b_is_large_residual);
  fChain->SetBranchAddress("is_near_target", &is_near_target, &b_is_near_target);
  fChain->SetBranchAddress("is_cluster_used", &is_cluster_used, &b_is_cluster_used);
  fChain->SetBranchAddress("is_selected", &is_selected, &b_is_selected);
  fChain->SetBranchAddress("x_rough_fit_chi_square", &x_rough_fit_chi_square, &b_x_rough_fit_chi_square);
  fChain->SetBranchAddress("x_rough_fit_coef0", &x_rough_fit_coef0, &b_x_rough_fit_coef0);
  fChain->SetBranchAddress("x_rough_fit_coef1", &x_rough_fit_coef1, &b_x_rough_fit_coef1);
  fChain->SetBranchAddress("x_rough_fit_coef2", &x_rough_fit_coef2, &b_x_rough_fit_coef2);
  fChain->SetBranchAddress("y_rough_fit_chi_square", &y_rough_fit_chi_square, &b_y_rough_fit_chi_square);
  fChain->SetBranchAddress("y_rough_fit_coef0", &y_rough_fit_coef0, &b_y_rough_fit_coef0);
  fChain->SetBranchAddress("y_rough_fit_coef1", &y_rough_fit_coef1, &b_y_rough_fit_coef1);
  fChain->SetBranchAddress("chi_square", &chi_square, &b_chi_square);
  fChain->SetBranchAddress("n_steps", &n_steps, &b_n_steps);
  fChain->SetBranchAddress("n_calls", &n_calls, &b_n_calls);
  fChain->SetBranchAddress("rk_charge", &rk_charge, &b_rk_charge);
  fChain->SetBranchAddress("rk_hit_init_mom_gx", &rk_hit_init_mom_gx, &b_rk_hit_init_mom_gx);
  fChain->SetBranchAddress("rk_hit_init_mom_gy", &rk_hit_init_mom_gy, &b_rk_hit_init_mom_gy);
  fChain->SetBranchAddress("rk_hit_init_mom_gz", &rk_hit_init_mom_gz, &b_rk_hit_init_mom_gz);
  fChain->SetBranchAddress("rk_hit_init_pos_gx", &rk_hit_init_pos_gx, &b_rk_hit_init_pos_gx);
  fChain->SetBranchAddress("rk_hit_init_pos_gy", &rk_hit_init_pos_gy, &b_rk_hit_init_pos_gy);
  fChain->SetBranchAddress("rk_hit_init_pos_gz", &rk_hit_init_pos_gz, &b_rk_hit_init_pos_gz);
  fChain->SetBranchAddress("rk_hit_ssd_id", &rk_hit_ssd_id, &b_rk_hit_ssd_id);
  fChain->SetBranchAddress("rk_hit_ssd_gx", &rk_hit_ssd_gx, &b_rk_hit_ssd_gx);
  fChain->SetBranchAddress("rk_hit_ssd_gy", &rk_hit_ssd_gy, &b_rk_hit_ssd_gy);
  fChain->SetBranchAddress("rk_hit_ssd_gz", &rk_hit_ssd_gz, &b_rk_hit_ssd_gz);
  fChain->SetBranchAddress("rk_hit_ssd_adc", &rk_hit_ssd_adc, &b_rk_hit_ssd_adc);
  fChain->SetBranchAddress("rk_hit_ssd_t", &rk_hit_ssd_t, &b_rk_hit_ssd_t);
  fChain->SetBranchAddress("rk_hit_gtr100_xid", &rk_hit_gtr100_xid, &b_rk_hit_gtr100_xid);
  fChain->SetBranchAddress("rk_hit_gtr100_yid", &rk_hit_gtr100_yid, &b_rk_hit_gtr100_yid);
  fChain->SetBranchAddress("rk_hit_gtr100_gx", &rk_hit_gtr100_gx, &b_rk_hit_gtr100_gx);
  fChain->SetBranchAddress("rk_hit_gtr100_gy", &rk_hit_gtr100_gy, &b_rk_hit_gtr100_gy);
  fChain->SetBranchAddress("rk_hit_gtr100_gz", &rk_hit_gtr100_gz, &b_rk_hit_gtr100_gz);
  fChain->SetBranchAddress("rk_hit_gtr100_xadc", &rk_hit_gtr100_xadc, &b_rk_hit_gtr100_xadc);
  fChain->SetBranchAddress("rk_hit_gtr100_yadc", &rk_hit_gtr100_yadc, &b_rk_hit_gtr100_yadc);
  fChain->SetBranchAddress("rk_hit_gtr100_xt", &rk_hit_gtr100_xt, &b_rk_hit_gtr100_xt);
  fChain->SetBranchAddress("rk_hit_gtr100_yt", &rk_hit_gtr100_yt, &b_rk_hit_gtr100_yt);
  fChain->SetBranchAddress("rk_hit_gtr200_xid", &rk_hit_gtr200_xid, &b_rk_hit_gtr200_xid);
  fChain->SetBranchAddress("rk_hit_gtr200_yid", &rk_hit_gtr200_yid, &b_rk_hit_gtr200_yid);
  fChain->SetBranchAddress("rk_hit_gtr200_gx", &rk_hit_gtr200_gx, &b_rk_hit_gtr200_gx);
  fChain->SetBranchAddress("rk_hit_gtr200_gy", &rk_hit_gtr200_gy, &b_rk_hit_gtr200_gy);
  fChain->SetBranchAddress("rk_hit_gtr200_gz", &rk_hit_gtr200_gz, &b_rk_hit_gtr200_gz);
  fChain->SetBranchAddress("rk_hit_gtr200_xadc", &rk_hit_gtr200_xadc, &b_rk_hit_gtr200_xadc);
  fChain->SetBranchAddress("rk_hit_gtr200_yadc", &rk_hit_gtr200_yadc, &b_rk_hit_gtr200_yadc);
  fChain->SetBranchAddress("rk_hit_gtr200_xt", &rk_hit_gtr200_xt, &b_rk_hit_gtr200_xt);
  fChain->SetBranchAddress("rk_hit_gtr300_xid", &rk_hit_gtr300_xid, &b_rk_hit_gtr300_xid);
  fChain->SetBranchAddress("rk_hit_gtr300_yid", &rk_hit_gtr300_yid, &b_rk_hit_gtr300_yid);
  fChain->SetBranchAddress("rk_hit_gtr200_yt", &rk_hit_gtr200_yt, &b_rk_hit_gtr200_yt);
  fChain->SetBranchAddress("rk_hit_gtr300_gx", &rk_hit_gtr300_gx, &b_rk_hit_gtr300_gx);
  fChain->SetBranchAddress("rk_hit_gtr300_gy", &rk_hit_gtr300_gy, &b_rk_hit_gtr300_gy);
  fChain->SetBranchAddress("rk_hit_gtr300_gz", &rk_hit_gtr300_gz, &b_rk_hit_gtr300_gz);
  fChain->SetBranchAddress("rk_hit_gtr300_xadc", &rk_hit_gtr300_xadc, &b_rk_hit_gtr300_xadc);
  fChain->SetBranchAddress("rk_hit_gtr300_yadc", &rk_hit_gtr300_yadc, &b_rk_hit_gtr300_yadc);
  fChain->SetBranchAddress("rk_hit_gtr300_xt", &rk_hit_gtr300_xt, &b_rk_hit_gtr300_xt);
  fChain->SetBranchAddress("rk_hit_gtr300_yt", &rk_hit_gtr300_yt, &b_rk_hit_gtr300_yt);
  fChain->SetBranchAddress("rk_fit_init_mom_gx", &rk_fit_init_mom_gx, &b_rk_fit_init_mom_gx);
  fChain->SetBranchAddress("rk_fit_init_mom_gy", &rk_fit_init_mom_gy, &b_rk_fit_init_mom_gy);
  fChain->SetBranchAddress("rk_fit_init_mom_gz", &rk_fit_init_mom_gz, &b_rk_fit_init_mom_gz);
  fChain->SetBranchAddress("rk_fit_init_pos_gx", &rk_fit_init_pos_gx, &b_rk_fit_init_pos_gx);
  fChain->SetBranchAddress("rk_fit_init_pos_gy", &rk_fit_init_pos_gy, &b_rk_fit_init_pos_gy);
  fChain->SetBranchAddress("rk_fit_init_pos_gz", &rk_fit_init_pos_gz, &b_rk_fit_init_pos_gz);
  fChain->SetBranchAddress("rk_fit_ssd_mid", &rk_fit_ssd_mid, &b_rk_fit_ssd_mid);
  fChain->SetBranchAddress("rk_fit_ssd_gx", &rk_fit_ssd_gx, &b_rk_fit_ssd_gx);
  fChain->SetBranchAddress("rk_fit_ssd_gy", &rk_fit_ssd_gy, &b_rk_fit_ssd_gy);
  fChain->SetBranchAddress("rk_fit_ssd_gz", &rk_fit_ssd_gz, &b_rk_fit_ssd_gz);
  fChain->SetBranchAddress("rk_fit_gtr100_mid", &rk_fit_gtr100_mid, &b_rk_fit_gtr100_mid);
  fChain->SetBranchAddress("rk_fit_gtr100_gx", &rk_fit_gtr100_gx, &b_rk_fit_gtr100_gx);
  fChain->SetBranchAddress("rk_fit_gtr100_gy", &rk_fit_gtr100_gy, &b_rk_fit_gtr100_gy);
  fChain->SetBranchAddress("rk_fit_gtr100_gz", &rk_fit_gtr100_gz, &b_rk_fit_gtr100_gz);
  fChain->SetBranchAddress("rk_fit_gtr200_mid", &rk_fit_gtr200_mid, &b_rk_fit_gtr200_mid);
  fChain->SetBranchAddress("rk_fit_gtr200_gx", &rk_fit_gtr200_gx, &b_rk_fit_gtr200_gx);
  fChain->SetBranchAddress("rk_fit_gtr200_gy", &rk_fit_gtr200_gy, &b_rk_fit_gtr200_gy);
  fChain->SetBranchAddress("rk_fit_gtr200_gz", &rk_fit_gtr200_gz, &b_rk_fit_gtr200_gz);
  fChain->SetBranchAddress("rk_fit_gtr300_mid", &rk_fit_gtr300_mid, &b_rk_fit_gtr300_mid);
  fChain->SetBranchAddress("rk_fit_gtr300_gx", &rk_fit_gtr300_gx, &b_rk_fit_gtr300_gx);
  fChain->SetBranchAddress("rk_fit_gtr300_gy", &rk_fit_gtr300_gy, &b_rk_fit_gtr300_gy);
  fChain->SetBranchAddress("rk_fit_gtr300_gz", &rk_fit_gtr300_gz, &b_rk_fit_gtr300_gz);
  fChain->SetBranchAddress("rk_fit_hbd_mid", &rk_fit_hbd_mid, &b_rk_fit_hbd_mid);
  fChain->SetBranchAddress("rk_fit_hbd_x", &rk_fit_hbd_x, &b_rk_fit_hbd_x);
  fChain->SetBranchAddress("rk_fit_hbd_y", &rk_fit_hbd_y, &b_rk_fit_hbd_y);
  fChain->SetBranchAddress("rk_fit_hbd_gx", &rk_fit_hbd_gx, &b_rk_fit_hbd_gx);
  fChain->SetBranchAddress("rk_fit_hbd_gy", &rk_fit_hbd_gy, &b_rk_fit_hbd_gy);
  fChain->SetBranchAddress("rk_fit_hbd_gz", &rk_fit_hbd_gz, &b_rk_fit_hbd_gz);
  fChain->SetBranchAddress("rk_fit_lg_c_mid", &rk_fit_lg_c_mid, &b_rk_fit_lg_c_mid);
  fChain->SetBranchAddress("rk_fit_lg_c_x", &rk_fit_lg_c_x, &b_rk_fit_lg_c_x);
  fChain->SetBranchAddress("rk_fit_lg_c_y", &rk_fit_lg_c_y, &b_rk_fit_lg_c_y);
  fChain->SetBranchAddress("rk_fit_lg_c_gx", &rk_fit_lg_c_gx, &b_rk_fit_lg_c_gx);
  fChain->SetBranchAddress("rk_fit_lg_c_gy", &rk_fit_lg_c_gy, &b_rk_fit_lg_c_gy);
  fChain->SetBranchAddress("rk_fit_lg_c_gz", &rk_fit_lg_c_gz, &b_rk_fit_lg_c_gz);
  fChain->SetBranchAddress("rk_fit_lg_b_mid", &rk_fit_lg_b_mid, &b_rk_fit_lg_b_mid);
  fChain->SetBranchAddress("rk_fit_lg_b_x", &rk_fit_lg_b_x, &b_rk_fit_lg_b_x);
  fChain->SetBranchAddress("rk_fit_lg_b_y", &rk_fit_lg_b_y, &b_rk_fit_lg_b_y);
  fChain->SetBranchAddress("rk_fit_lg_b_gx", &rk_fit_lg_b_gx, &b_rk_fit_lg_b_gx);
  fChain->SetBranchAddress("rk_fit_lg_b_gy", &rk_fit_lg_b_gy, &b_rk_fit_lg_b_gy);
  fChain->SetBranchAddress("rk_fit_lg_b_gz", &rk_fit_lg_b_gz, &b_rk_fit_lg_b_gz);
  fChain->SetBranchAddress("rk_fit_lg_a_mid", &rk_fit_lg_a_mid, &b_rk_fit_lg_a_mid);
  fChain->SetBranchAddress("rk_fit_lg_a_x", &rk_fit_lg_a_x, &b_rk_fit_lg_a_x);
  fChain->SetBranchAddress("rk_fit_lg_a_y", &rk_fit_lg_a_y, &b_rk_fit_lg_a_y);
  fChain->SetBranchAddress("rk_fit_lg_a_gx", &rk_fit_lg_a_gx, &b_rk_fit_lg_a_gx);
  fChain->SetBranchAddress("rk_fit_lg_a_gy", &rk_fit_lg_a_gy, &b_rk_fit_lg_a_gy);
  fChain->SetBranchAddress("rk_fit_lg_a_gz", &rk_fit_lg_a_gz, &b_rk_fit_lg_a_gz);
  fChain->SetBranchAddress("rk_res_init_pos_gx", &rk_res_init_pos_gx, &b_rk_res_init_pos_gx);
  fChain->SetBranchAddress("rk_res_init_pos_gy", &rk_res_init_pos_gy, &b_rk_res_init_pos_gy);
  fChain->SetBranchAddress("rk_res_init_pos_gz", &rk_res_init_pos_gz, &b_rk_res_init_pos_gz);
  fChain->SetBranchAddress("rk_res_init_mom_gx", &rk_res_init_mom_gx, &b_rk_res_init_mom_gx);
  fChain->SetBranchAddress("rk_res_init_mom_gy", &rk_res_init_mom_gy, &b_rk_res_init_mom_gy);
  fChain->SetBranchAddress("rk_res_init_mom_gz", &rk_res_init_mom_gz, &b_rk_res_init_mom_gz);
  fChain->SetBranchAddress("rk_res_ssd_x", &rk_res_ssd_x, &b_rk_res_ssd_x);
  fChain->SetBranchAddress("rk_res_gtr100_x", &rk_res_gtr100_x, &b_rk_res_gtr100_x);
  fChain->SetBranchAddress("rk_res_gtr100_y", &rk_res_gtr100_y, &b_rk_res_gtr100_y);
  fChain->SetBranchAddress("rk_res_gtr200_x", &rk_res_gtr200_x, &b_rk_res_gtr200_x);
  fChain->SetBranchAddress("rk_res_gtr200_y", &rk_res_gtr200_y, &b_rk_res_gtr200_y);
  fChain->SetBranchAddress("rk_res_gtr300_x", &rk_res_gtr300_x, &b_rk_res_gtr300_x);
  fChain->SetBranchAddress("rk_res_gtr300_y", &rk_res_gtr300_y, &b_rk_res_gtr300_y);
  fChain->SetBranchAddress("rk_proj_tgt0_gx", &rk_proj_tgt0_gx, &b_rk_proj_tgt0_gx);
  fChain->SetBranchAddress("rk_proj_tgt0_gy", &rk_proj_tgt0_gy, &b_rk_proj_tgt0_gy);
  fChain->SetBranchAddress("rk_proj_tgt0_gz", &rk_proj_tgt0_gz, &b_rk_proj_tgt0_gz);
  fChain->SetBranchAddress("rk_proj_tgt1_gx", &rk_proj_tgt1_gx, &b_rk_proj_tgt1_gx);
  fChain->SetBranchAddress("rk_proj_tgt1_gy", &rk_proj_tgt1_gy, &b_rk_proj_tgt1_gy);
  fChain->SetBranchAddress("rk_proj_tgt1_gz", &rk_proj_tgt1_gz, &b_rk_proj_tgt1_gz);
  fChain->SetBranchAddress("rk_proj_tgt2_gx", &rk_proj_tgt2_gx, &b_rk_proj_tgt2_gx);
  fChain->SetBranchAddress("rk_proj_tgt2_gy", &rk_proj_tgt2_gy, &b_rk_proj_tgt2_gy);
  fChain->SetBranchAddress("rk_proj_tgt2_gz", &rk_proj_tgt2_gz, &b_rk_proj_tgt2_gz);
  fChain->SetBranchAddress("rk_proj_tgt0_mom_gx", &rk_proj_tgt0_mom_gx, &b_rk_proj_tgt0_mom_gx);
  fChain->SetBranchAddress("rk_proj_tgt0_mom_gy", &rk_proj_tgt0_mom_gy, &b_rk_proj_tgt0_mom_gy);
  fChain->SetBranchAddress("rk_proj_tgt0_mom_gz", &rk_proj_tgt0_mom_gz, &b_rk_proj_tgt0_mom_gz);
  fChain->SetBranchAddress("rk_proj_tgt1_mom_gx", &rk_proj_tgt1_mom_gx, &b_rk_proj_tgt1_mom_gx);
  fChain->SetBranchAddress("rk_proj_tgt1_mom_gy", &rk_proj_tgt1_mom_gy, &b_rk_proj_tgt1_mom_gy);
  fChain->SetBranchAddress("rk_proj_tgt1_mom_gz", &rk_proj_tgt1_mom_gz, &b_rk_proj_tgt1_mom_gz);
  fChain->SetBranchAddress("rk_proj_tgt2_mom_gx", &rk_proj_tgt2_mom_gx, &b_rk_proj_tgt2_mom_gx);
  fChain->SetBranchAddress("rk_proj_tgt2_mom_gy", &rk_proj_tgt2_mom_gy, &b_rk_proj_tgt2_mom_gy);
  fChain->SetBranchAddress("rk_proj_tgt2_mom_gz", &rk_proj_tgt2_mom_gz, &b_rk_proj_tgt2_mom_gz);
  fChain->SetBranchAddress("rk_proj_x0_gx", &rk_proj_x0_gx, &b_rk_proj_x0_gx);
  fChain->SetBranchAddress("rk_proj_x0_gy", &rk_proj_x0_gy, &b_rk_proj_x0_gy);
  fChain->SetBranchAddress("rk_proj_x0_gz", &rk_proj_x0_gz, &b_rk_proj_x0_gz);
  fChain->SetBranchAddress("rk_proj_x0_mom_gx", &rk_proj_x0_mom_gx, &b_rk_proj_x0_mom_gx);
  fChain->SetBranchAddress("rk_proj_x0_mom_gy", &rk_proj_x0_mom_gy, &b_rk_proj_x0_mom_gy);
  fChain->SetBranchAddress("rk_proj_x0_mom_gz", &rk_proj_x0_mom_gz, &b_rk_proj_x0_mom_gz);
  fChain->SetBranchAddress("rk_proj_n_hbd", &rk_proj_n_hbd, &b_rk_proj_n_hbd);
  fChain->SetBranchAddress("rk_proj_hbd0_id", &rk_proj_hbd0_id, &b_rk_proj_hbd0_id);
  fChain->SetBranchAddress("rk_proj_hbd0_mid", &rk_proj_hbd0_mid, &b_rk_proj_hbd0_mid);
  fChain->SetBranchAddress("rk_proj_hbd0_x", &rk_proj_hbd0_x, &b_rk_proj_hbd0_x);
  fChain->SetBranchAddress("rk_proj_hbd0_y", &rk_proj_hbd0_y, &b_rk_proj_hbd0_y);
  fChain->SetBranchAddress("rk_proj_hbd0_adc", &rk_proj_hbd0_adc, &b_rk_proj_hbd0_adc);
  fChain->SetBranchAddress("rk_proj_hbd0_t", &rk_proj_hbd0_t, &b_rk_proj_hbd0_t);
  fChain->SetBranchAddress("rk_proj_hbd0_ftime", &rk_proj_hbd0_ftime, &b_rk_proj_hbd0_ftime);
  fChain->SetBranchAddress("rk_proj_hbd0_tdiff", &rk_proj_hbd0_tdiff, &b_rk_proj_hbd0_tdiff);
  fChain->SetBranchAddress("rk_proj_hbd0_size", &rk_proj_hbd0_size, &b_rk_proj_hbd0_size);
  fChain->SetBranchAddress("rk_proj_hbd0_eprob", &rk_proj_hbd0_eprob, &b_rk_proj_hbd0_eprob);
  fChain->SetBranchAddress("rk_proj_hbd0_cprob", &rk_proj_hbd0_cprob, &b_rk_proj_hbd0_cprob);
  fChain->SetBranchAddress("rk_proj_hbd1_id", &rk_proj_hbd1_id, &b_rk_proj_hbd1_id);
  fChain->SetBranchAddress("rk_proj_hbd1_mid", &rk_proj_hbd1_mid, &b_rk_proj_hbd1_mid);
  fChain->SetBranchAddress("rk_proj_hbd1_x", &rk_proj_hbd1_x, &b_rk_proj_hbd1_x);
  fChain->SetBranchAddress("rk_proj_hbd1_y", &rk_proj_hbd1_y, &b_rk_proj_hbd1_y);
  fChain->SetBranchAddress("rk_proj_hbd1_adc", &rk_proj_hbd1_adc, &b_rk_proj_hbd1_adc);
  fChain->SetBranchAddress("rk_proj_hbd1_t", &rk_proj_hbd1_t, &b_rk_proj_hbd1_t);
  fChain->SetBranchAddress("rk_proj_hbd1_ftime", &rk_proj_hbd1_ftime, &b_rk_proj_hbd1_ftime);
  fChain->SetBranchAddress("rk_proj_hbd1_tdiff", &rk_proj_hbd1_tdiff, &b_rk_proj_hbd1_tdiff);
  fChain->SetBranchAddress("rk_proj_hbd1_size", &rk_proj_hbd1_size, &b_rk_proj_hbd1_size);
  fChain->SetBranchAddress("rk_proj_hbd1_eprob", &rk_proj_hbd1_eprob, &b_rk_proj_hbd1_eprob);
  fChain->SetBranchAddress("rk_proj_hbd1_cprob", &rk_proj_hbd1_cprob, &b_rk_proj_hbd1_cprob);
  fChain->SetBranchAddress("rk_proj_hbd2_id", &rk_proj_hbd2_id, &b_rk_proj_hbd2_id);
  fChain->SetBranchAddress("rk_proj_hbd2_mid", &rk_proj_hbd2_mid, &b_rk_proj_hbd2_mid);
  fChain->SetBranchAddress("rk_proj_hbd2_x", &rk_proj_hbd2_x, &b_rk_proj_hbd2_x);
  fChain->SetBranchAddress("rk_proj_hbd2_y", &rk_proj_hbd2_y, &b_rk_proj_hbd2_y);
  fChain->SetBranchAddress("rk_proj_hbd2_adc", &rk_proj_hbd2_adc, &b_rk_proj_hbd2_adc);
  fChain->SetBranchAddress("rk_proj_hbd2_t", &rk_proj_hbd2_t, &b_rk_proj_hbd2_t);
  fChain->SetBranchAddress("rk_proj_hbd2_ftime", &rk_proj_hbd2_ftime, &b_rk_proj_hbd2_ftime);
  fChain->SetBranchAddress("rk_proj_hbd2_tdiff", &rk_proj_hbd2_tdiff, &b_rk_proj_hbd2_tdiff);
  fChain->SetBranchAddress("rk_proj_hbd2_size", &rk_proj_hbd2_size, &b_rk_proj_hbd2_size);
  fChain->SetBranchAddress("rk_proj_hbd2_eprob", &rk_proj_hbd2_eprob, &b_rk_proj_hbd2_eprob);
  fChain->SetBranchAddress("rk_proj_hbd2_cprob", &rk_proj_hbd2_cprob, &b_rk_proj_hbd2_cprob);
  fChain->SetBranchAddress("rk_proj_hbd3_id", &rk_proj_hbd3_id, &b_rk_proj_hbd3_id);
  fChain->SetBranchAddress("rk_proj_hbd3_mid", &rk_proj_hbd3_mid, &b_rk_proj_hbd3_mid);
  fChain->SetBranchAddress("rk_proj_hbd3_x", &rk_proj_hbd3_x, &b_rk_proj_hbd3_x);
  fChain->SetBranchAddress("rk_proj_hbd3_y", &rk_proj_hbd3_y, &b_rk_proj_hbd3_y);
  fChain->SetBranchAddress("rk_proj_hbd3_adc", &rk_proj_hbd3_adc, &b_rk_proj_hbd3_adc);
  fChain->SetBranchAddress("rk_proj_hbd3_t", &rk_proj_hbd3_t, &b_rk_proj_hbd3_t);
  fChain->SetBranchAddress("rk_proj_hbd3_ftime", &rk_proj_hbd3_ftime, &b_rk_proj_hbd3_ftime);
  fChain->SetBranchAddress("rk_proj_hbd3_tdiff", &rk_proj_hbd3_tdiff, &b_rk_proj_hbd3_tdiff);
  fChain->SetBranchAddress("rk_proj_hbd3_size", &rk_proj_hbd3_size, &b_rk_proj_hbd3_size);
  fChain->SetBranchAddress("rk_proj_hbd3_eprob", &rk_proj_hbd3_eprob, &b_rk_proj_hbd3_eprob);
  fChain->SetBranchAddress("rk_proj_hbd3_cprob", &rk_proj_hbd3_cprob, &b_rk_proj_hbd3_cprob);
  fChain->SetBranchAddress("rk_proj_n_lg", &rk_proj_n_lg, &b_rk_proj_n_lg);
  fChain->SetBranchAddress("rk_proj_lg0_id", &rk_proj_lg0_id, &b_rk_proj_lg0_id);
  fChain->SetBranchAddress("rk_proj_lg0_mid", &rk_proj_lg0_mid, &b_rk_proj_lg0_mid);
  fChain->SetBranchAddress("rk_proj_lg0_x", &rk_proj_lg0_x, &b_rk_proj_lg0_x);
  fChain->SetBranchAddress("rk_proj_lg0_y", &rk_proj_lg0_y, &b_rk_proj_lg0_y);
  fChain->SetBranchAddress("rk_proj_lg0_adc", &rk_proj_lg0_adc, &b_rk_proj_lg0_adc);
  fChain->SetBranchAddress("rk_proj_lg0_t", &rk_proj_lg0_t, &b_rk_proj_lg0_t);
  fChain->SetBranchAddress("rk_proj_lg0_npeaks", &rk_proj_lg0_npeaks, &b_rk_proj_lg0_npeaks);
  fChain->SetBranchAddress("rk_proj_lg0_fflag", &rk_proj_lg0_fflag, &b_rk_proj_lg0_fflag);
  fChain->SetBranchAddress("rk_proj_lg1_id", &rk_proj_lg1_id, &b_rk_proj_lg1_id);
  fChain->SetBranchAddress("rk_proj_lg1_mid", &rk_proj_lg1_mid, &b_rk_proj_lg1_mid);
  fChain->SetBranchAddress("rk_proj_lg1_x", &rk_proj_lg1_x, &b_rk_proj_lg1_x);
  fChain->SetBranchAddress("rk_proj_lg1_y", &rk_proj_lg1_y, &b_rk_proj_lg1_y);
  fChain->SetBranchAddress("rk_proj_lg1_adc", &rk_proj_lg1_adc, &b_rk_proj_lg1_adc);
  fChain->SetBranchAddress("rk_proj_lg1_t", &rk_proj_lg1_t, &b_rk_proj_lg1_t);
  fChain->SetBranchAddress("rk_proj_lg1_npeaks", &rk_proj_lg1_npeaks, &b_rk_proj_lg1_npeaks);
  fChain->SetBranchAddress("rk_proj_lg1_fflag", &rk_proj_lg1_fflag, &b_rk_proj_lg1_fflag);
  fChain->SetBranchAddress("rk_proj_lg2_id", &rk_proj_lg2_id, &b_rk_proj_lg2_id);
  fChain->SetBranchAddress("rk_proj_lg2_mid", &rk_proj_lg2_mid, &b_rk_proj_lg2_mid);
  fChain->SetBranchAddress("rk_proj_lg2_x", &rk_proj_lg2_x, &b_rk_proj_lg2_x);
  fChain->SetBranchAddress("rk_proj_lg2_y", &rk_proj_lg2_y, &b_rk_proj_lg2_y);
  fChain->SetBranchAddress("rk_proj_lg2_adc", &rk_proj_lg2_adc, &b_rk_proj_lg2_adc);
  fChain->SetBranchAddress("rk_proj_lg2_t", &rk_proj_lg2_t, &b_rk_proj_lg2_t);
  fChain->SetBranchAddress("rk_proj_lg2_npeaks", &rk_proj_lg2_npeaks, &b_rk_proj_lg2_npeaks);
  fChain->SetBranchAddress("rk_proj_lg2_fflag", &rk_proj_lg2_fflag, &b_rk_proj_lg2_fflag);
  fChain->SetBranchAddress("rk_proj_lg3_id", &rk_proj_lg3_id, &b_rk_proj_lg3_id);
  fChain->SetBranchAddress("rk_proj_lg3_mid", &rk_proj_lg3_mid, &b_rk_proj_lg3_mid);
  fChain->SetBranchAddress("rk_proj_lg3_x", &rk_proj_lg3_x, &b_rk_proj_lg3_x);
  fChain->SetBranchAddress("rk_proj_lg3_y", &rk_proj_lg3_y, &b_rk_proj_lg3_y);
  fChain->SetBranchAddress("rk_proj_lg3_adc", &rk_proj_lg3_adc, &b_rk_proj_lg3_adc);
  fChain->SetBranchAddress("rk_proj_lg3_t", &rk_proj_lg3_t, &b_rk_proj_lg3_t);
  fChain->SetBranchAddress("rk_proj_lg3_npeaks", &rk_proj_lg3_npeaks, &b_rk_proj_lg3_npeaks);
  fChain->SetBranchAddress("rk_proj_lg3_fflag", &rk_proj_lg3_fflag, &b_rk_proj_lg3_fflag);
  fChain->SetBranchAddress("rk_pair_minus_track_id", &rk_pair_minus_track_id, &b_rk_pair_minus_track_id);
  fChain->SetBranchAddress("rk_pair_minus_gtr300_mid", &rk_pair_minus_gtr300_mid, &b_rk_pair_minus_gtr300_mid);
  fChain->SetBranchAddress("rk_pair_minus_chi_square", &rk_pair_minus_chi_square, &b_rk_pair_minus_chi_square);
  fChain->SetBranchAddress("rk_pair_minus_mom_gx", &rk_pair_minus_mom_gx, &b_rk_pair_minus_mom_gx);
  fChain->SetBranchAddress("rk_pair_minus_mom_gy", &rk_pair_minus_mom_gy, &b_rk_pair_minus_mom_gy);
  fChain->SetBranchAddress("rk_pair_minus_mom_gz", &rk_pair_minus_mom_gz, &b_rk_pair_minus_mom_gz);
  fChain->SetBranchAddress("rk_pair_minus_ssd_t", &rk_pair_minus_ssd_t, &b_rk_pair_minus_ssd_t);
  fChain->SetBranchAddress("rk_pair_minus_lg0_t", &rk_pair_minus_lg0_t, &b_rk_pair_minus_lg0_t);
  fChain->SetBranchAddress("rk_pair_minus_lg1_t", &rk_pair_minus_lg1_t, &b_rk_pair_minus_lg1_t);
  fChain->SetBranchAddress("rk_pair_minus_lg2_t", &rk_pair_minus_lg2_t, &b_rk_pair_minus_lg2_t);
  fChain->SetBranchAddress("rk_pair_minus_lg3_t", &rk_pair_minus_lg3_t, &b_rk_pair_minus_lg3_t);
  fChain->SetBranchAddress("rk_pair_plus_track_id", &rk_pair_plus_track_id, &b_rk_pair_plus_track_id);
  fChain->SetBranchAddress("rk_pair_plus_gtr300_mid", &rk_pair_plus_gtr300_mid, &b_rk_pair_plus_gtr300_mid);
  fChain->SetBranchAddress("rk_pair_plus_chi_square", &rk_pair_plus_chi_square, &b_rk_pair_plus_chi_square);
  fChain->SetBranchAddress("rk_pair_plus_mom_gx", &rk_pair_plus_mom_gx, &b_rk_pair_plus_mom_gx);
  fChain->SetBranchAddress("rk_pair_plus_mom_gy", &rk_pair_plus_mom_gy, &b_rk_pair_plus_mom_gy);
  fChain->SetBranchAddress("rk_pair_plus_mom_gz", &rk_pair_plus_mom_gz, &b_rk_pair_plus_mom_gz);
  fChain->SetBranchAddress("rk_pair_plus_ssd_t", &rk_pair_plus_ssd_t, &b_rk_pair_plus_ssd_t);
  fChain->SetBranchAddress("rk_pair_plus_lg0_t", &rk_pair_plus_lg0_t, &b_rk_pair_plus_lg0_t);
  fChain->SetBranchAddress("rk_pair_plus_lg1_t", &rk_pair_plus_lg1_t, &b_rk_pair_plus_lg1_t);
  fChain->SetBranchAddress("rk_pair_plus_lg2_t", &rk_pair_plus_lg2_t, &b_rk_pair_plus_lg2_t);
  fChain->SetBranchAddress("rk_pair_plus_lg3_t", &rk_pair_plus_lg3_t, &b_rk_pair_plus_lg3_t);
  fChain->SetBranchAddress("rk_pair_distance", &rk_pair_distance, &b_rk_pair_distance);
  fChain->SetBranchAddress("rk_pair_vtx_gx", &rk_pair_vtx_gx, &b_rk_pair_vtx_gx);
  fChain->SetBranchAddress("rk_pair_vtx_gy", &rk_pair_vtx_gy, &b_rk_pair_vtx_gy);
  fChain->SetBranchAddress("rk_pair_vtx_gz", &rk_pair_vtx_gz, &b_rk_pair_vtx_gz);
  fChain->SetBranchAddress("rk_pair_is_refit", &rk_pair_is_refit, &b_rk_pair_is_refit);
  fChain->SetBranchAddress("rk_pair_is_selected", &rk_pair_is_selected, &b_rk_pair_is_selected);
  fChain->SetBranchAddress("rk_pair_chi_square_refit", &rk_pair_chi_square_refit, &b_rk_pair_chi_square_refit);
  fChain->SetBranchAddress("rk_pair_vtx_refit_gx", &rk_pair_vtx_refit_gx, &b_rk_pair_vtx_refit_gx);
  fChain->SetBranchAddress("rk_pair_vtx_refit_gy", &rk_pair_vtx_refit_gy, &b_rk_pair_vtx_refit_gy);
  fChain->SetBranchAddress("rk_pair_vtx_refit_gz", &rk_pair_vtx_refit_gz, &b_rk_pair_vtx_refit_gz);
  fChain->SetBranchAddress("rk_pair_minus_mom_refit_gx", &rk_pair_minus_mom_refit_gx, &b_rk_pair_minus_mom_refit_gx);
  fChain->SetBranchAddress("rk_pair_minus_mom_refit_gy", &rk_pair_minus_mom_refit_gy, &b_rk_pair_minus_mom_refit_gy);
  fChain->SetBranchAddress("rk_pair_minus_mom_refit_gz", &rk_pair_minus_mom_refit_gz, &b_rk_pair_minus_mom_refit_gz);
  fChain->SetBranchAddress("rk_pair_plus_mom_refit_gx", &rk_pair_plus_mom_refit_gx, &b_rk_pair_plus_mom_refit_gx);
  fChain->SetBranchAddress("rk_pair_plus_mom_refit_gy", &rk_pair_plus_mom_refit_gy, &b_rk_pair_plus_mom_refit_gy);
  fChain->SetBranchAddress("rk_pair_plus_mom_refit_gz", &rk_pair_plus_mom_refit_gz, &b_rk_pair_plus_mom_refit_gz);
  fChain->SetBranchAddress("rk_pair_minus_ssd_pos_refit_gx", &rk_pair_minus_ssd_pos_refit_gx, &b_rk_pair_minus_ssd_pos_refit_gx);
  fChain->SetBranchAddress("rk_pair_minus_ssd_pos_refit_gy", &rk_pair_minus_ssd_pos_refit_gy, &b_rk_pair_minus_ssd_pos_refit_gy);
  fChain->SetBranchAddress("rk_pair_minus_ssd_pos_refit_gz", &rk_pair_minus_ssd_pos_refit_gz, &b_rk_pair_minus_ssd_pos_refit_gz);
  fChain->SetBranchAddress("rk_pair_minus_gtr100_pos_refit_gx", &rk_pair_minus_gtr100_pos_refit_gx, &b_rk_pair_minus_gtr100_pos_refit_gx);
  fChain->SetBranchAddress("rk_pair_minus_gtr100_pos_refit_gy", &rk_pair_minus_gtr100_pos_refit_gy, &b_rk_pair_minus_gtr100_pos_refit_gy);
  fChain->SetBranchAddress("rk_pair_minus_gtr100_pos_refit_gz", &rk_pair_minus_gtr100_pos_refit_gz, &b_rk_pair_minus_gtr100_pos_refit_gz);
  fChain->SetBranchAddress("rk_pair_minus_gtr200_pos_refit_gx", &rk_pair_minus_gtr200_pos_refit_gx, &b_rk_pair_minus_gtr200_pos_refit_gx);
  fChain->SetBranchAddress("rk_pair_minus_gtr200_pos_refit_gy", &rk_pair_minus_gtr200_pos_refit_gy, &b_rk_pair_minus_gtr200_pos_refit_gy);
  fChain->SetBranchAddress("rk_pair_minus_gtr200_pos_refit_gz", &rk_pair_minus_gtr200_pos_refit_gz, &b_rk_pair_minus_gtr200_pos_refit_gz);
  fChain->SetBranchAddress("rk_pair_minus_gtr300_pos_refit_gx", &rk_pair_minus_gtr300_pos_refit_gx, &b_rk_pair_minus_gtr300_pos_refit_gx);
  fChain->SetBranchAddress("rk_pair_minus_gtr300_pos_refit_gy", &rk_pair_minus_gtr300_pos_refit_gy, &b_rk_pair_minus_gtr300_pos_refit_gy);
  fChain->SetBranchAddress("rk_pair_minus_gtr300_pos_refit_gz", &rk_pair_minus_gtr300_pos_refit_gz, &b_rk_pair_minus_gtr300_pos_refit_gz);
  fChain->SetBranchAddress("rk_pair_plus_ssd_pos_refit_gx", &rk_pair_plus_ssd_pos_refit_gx, &b_rk_pair_plus_ssd_pos_refit_gx);
  fChain->SetBranchAddress("rk_pair_plus_ssd_pos_refit_gy", &rk_pair_plus_ssd_pos_refit_gy, &b_rk_pair_plus_ssd_pos_refit_gy);
  fChain->SetBranchAddress("rk_pair_plus_ssd_pos_refit_gz", &rk_pair_plus_ssd_pos_refit_gz, &b_rk_pair_plus_ssd_pos_refit_gz);
  fChain->SetBranchAddress("rk_pair_plus_gtr100_pos_refit_gx", &rk_pair_plus_gtr100_pos_refit_gx, &b_rk_pair_plus_gtr100_pos_refit_gx);
  fChain->SetBranchAddress("rk_pair_plus_gtr100_pos_refit_gy", &rk_pair_plus_gtr100_pos_refit_gy, &b_rk_pair_plus_gtr100_pos_refit_gy);
  fChain->SetBranchAddress("rk_pair_plus_gtr100_pos_refit_gz", &rk_pair_plus_gtr100_pos_refit_gz, &b_rk_pair_plus_gtr100_pos_refit_gz);
  fChain->SetBranchAddress("rk_pair_plus_gtr200_pos_refit_gx", &rk_pair_plus_gtr200_pos_refit_gx, &b_rk_pair_plus_gtr200_pos_refit_gx);
  fChain->SetBranchAddress("rk_pair_plus_gtr200_pos_refit_gy", &rk_pair_plus_gtr200_pos_refit_gy, &b_rk_pair_plus_gtr200_pos_refit_gy);
  fChain->SetBranchAddress("rk_pair_plus_gtr200_pos_refit_gz", &rk_pair_plus_gtr200_pos_refit_gz, &b_rk_pair_plus_gtr200_pos_refit_gz);
  fChain->SetBranchAddress("rk_pair_plus_gtr300_pos_refit_gx", &rk_pair_plus_gtr300_pos_refit_gx, &b_rk_pair_plus_gtr300_pos_refit_gx);
  fChain->SetBranchAddress("rk_pair_plus_gtr300_pos_refit_gy", &rk_pair_plus_gtr300_pos_refit_gy, &b_rk_pair_plus_gtr300_pos_refit_gy);
  fChain->SetBranchAddress("rk_pair_plus_gtr300_pos_refit_gz", &rk_pair_plus_gtr300_pos_refit_gz, &b_rk_pair_plus_gtr300_pos_refit_gz);
  fChain->SetBranchAddress("rk_pair_minus_ssd_mom_refit_gx", &rk_pair_minus_ssd_mom_refit_gx, &b_rk_pair_minus_ssd_mom_refit_gx);
  fChain->SetBranchAddress("rk_pair_minus_ssd_mom_refit_gy", &rk_pair_minus_ssd_mom_refit_gy, &b_rk_pair_minus_ssd_mom_refit_gy);
  fChain->SetBranchAddress("rk_pair_minus_ssd_mom_refit_gz", &rk_pair_minus_ssd_mom_refit_gz, &b_rk_pair_minus_ssd_mom_refit_gz);
  fChain->SetBranchAddress("rk_pair_minus_gtr100_mom_refit_gx", &rk_pair_minus_gtr100_mom_refit_gx, &b_rk_pair_minus_gtr100_mom_refit_gx);
  fChain->SetBranchAddress("rk_pair_minus_gtr100_mom_refit_gy", &rk_pair_minus_gtr100_mom_refit_gy, &b_rk_pair_minus_gtr100_mom_refit_gy);
  fChain->SetBranchAddress("rk_pair_minus_gtr100_mom_refit_gz", &rk_pair_minus_gtr100_mom_refit_gz, &b_rk_pair_minus_gtr100_mom_refit_gz);
  fChain->SetBranchAddress("rk_pair_minus_gtr200_mom_refit_gx", &rk_pair_minus_gtr200_mom_refit_gx, &b_rk_pair_minus_gtr200_mom_refit_gx);
  fChain->SetBranchAddress("rk_pair_minus_gtr200_mom_refit_gy", &rk_pair_minus_gtr200_mom_refit_gy, &b_rk_pair_minus_gtr200_mom_refit_gy);
  fChain->SetBranchAddress("rk_pair_minus_gtr200_mom_refit_gz", &rk_pair_minus_gtr200_mom_refit_gz, &b_rk_pair_minus_gtr200_mom_refit_gz);
  fChain->SetBranchAddress("rk_pair_minus_gtr300_mom_refit_gx", &rk_pair_minus_gtr300_mom_refit_gx, &b_rk_pair_minus_gtr300_mom_refit_gx);
  fChain->SetBranchAddress("rk_pair_minus_gtr300_mom_refit_gy", &rk_pair_minus_gtr300_mom_refit_gy, &b_rk_pair_minus_gtr300_mom_refit_gy);
  fChain->SetBranchAddress("rk_pair_minus_gtr300_mom_refit_gz", &rk_pair_minus_gtr300_mom_refit_gz, &b_rk_pair_minus_gtr300_mom_refit_gz);
  fChain->SetBranchAddress("rk_pair_plus_ssd_mom_refit_gx", &rk_pair_plus_ssd_mom_refit_gx, &b_rk_pair_plus_ssd_mom_refit_gx);
  fChain->SetBranchAddress("rk_pair_plus_ssd_mom_refit_gy", &rk_pair_plus_ssd_mom_refit_gy, &b_rk_pair_plus_ssd_mom_refit_gy);
  fChain->SetBranchAddress("rk_pair_plus_ssd_mom_refit_gz", &rk_pair_plus_ssd_mom_refit_gz, &b_rk_pair_plus_ssd_mom_refit_gz);
  fChain->SetBranchAddress("rk_pair_plus_gtr100_mom_refit_gx", &rk_pair_plus_gtr100_mom_refit_gx, &b_rk_pair_plus_gtr100_mom_refit_gx);
  fChain->SetBranchAddress("rk_pair_plus_gtr100_mom_refit_gy", &rk_pair_plus_gtr100_mom_refit_gy, &b_rk_pair_plus_gtr100_mom_refit_gy);
  fChain->SetBranchAddress("rk_pair_plus_gtr100_mom_refit_gz", &rk_pair_plus_gtr100_mom_refit_gz, &b_rk_pair_plus_gtr100_mom_refit_gz);
  fChain->SetBranchAddress("rk_pair_plus_gtr200_mom_refit_gx", &rk_pair_plus_gtr200_mom_refit_gx, &b_rk_pair_plus_gtr200_mom_refit_gx);
  fChain->SetBranchAddress("rk_pair_plus_gtr200_mom_refit_gy", &rk_pair_plus_gtr200_mom_refit_gy, &b_rk_pair_plus_gtr200_mom_refit_gy);
  fChain->SetBranchAddress("rk_pair_plus_gtr200_mom_refit_gz", &rk_pair_plus_gtr200_mom_refit_gz, &b_rk_pair_plus_gtr200_mom_refit_gz);
  fChain->SetBranchAddress("rk_pair_plus_gtr300_mom_refit_gx", &rk_pair_plus_gtr300_mom_refit_gx, &b_rk_pair_plus_gtr300_mom_refit_gx);
  fChain->SetBranchAddress("rk_pair_plus_gtr300_mom_refit_gy", &rk_pair_plus_gtr300_mom_refit_gy, &b_rk_pair_plus_gtr300_mom_refit_gy);
  fChain->SetBranchAddress("rk_pair_plus_gtr300_mom_refit_gz", &rk_pair_plus_gtr300_mom_refit_gz, &b_rk_pair_plus_gtr300_mom_refit_gz);
  fChain->SetBranchAddress("rk_pair_minus_ssd_res_refit_x", &rk_pair_minus_ssd_res_refit_x, &b_rk_pair_minus_ssd_res_refit_x);
  fChain->SetBranchAddress("rk_pair_minus_ssd_res_refit_y", &rk_pair_minus_ssd_res_refit_y, &b_rk_pair_minus_ssd_res_refit_y);
  fChain->SetBranchAddress("rk_pair_minus_ssd_res_refit_z", &rk_pair_minus_ssd_res_refit_z, &b_rk_pair_minus_ssd_res_refit_z);
  fChain->SetBranchAddress("rk_pair_minus_gtr100_res_refit_x", &rk_pair_minus_gtr100_res_refit_x, &b_rk_pair_minus_gtr100_res_refit_x);
  fChain->SetBranchAddress("rk_pair_minus_gtr100_res_refit_y", &rk_pair_minus_gtr100_res_refit_y, &b_rk_pair_minus_gtr100_res_refit_y);
  fChain->SetBranchAddress("rk_pair_minus_gtr100_res_refit_z", &rk_pair_minus_gtr100_res_refit_z, &b_rk_pair_minus_gtr100_res_refit_z);
  fChain->SetBranchAddress("rk_pair_minus_gtr200_res_refit_x", &rk_pair_minus_gtr200_res_refit_x, &b_rk_pair_minus_gtr200_res_refit_x);
  fChain->SetBranchAddress("rk_pair_minus_gtr200_res_refit_y", &rk_pair_minus_gtr200_res_refit_y, &b_rk_pair_minus_gtr200_res_refit_y);
  fChain->SetBranchAddress("rk_pair_minus_gtr200_res_refit_z", &rk_pair_minus_gtr200_res_refit_z, &b_rk_pair_minus_gtr200_res_refit_z);
  fChain->SetBranchAddress("rk_pair_minus_gtr300_res_refit_x", &rk_pair_minus_gtr300_res_refit_x, &b_rk_pair_minus_gtr300_res_refit_x);
  fChain->SetBranchAddress("rk_pair_minus_gtr300_res_refit_y", &rk_pair_minus_gtr300_res_refit_y, &b_rk_pair_minus_gtr300_res_refit_y);
  fChain->SetBranchAddress("rk_pair_minus_gtr300_res_refit_z", &rk_pair_minus_gtr300_res_refit_z, &b_rk_pair_minus_gtr300_res_refit_z);
  fChain->SetBranchAddress("rk_pair_plus_ssd_res_refit_x", &rk_pair_plus_ssd_res_refit_x, &b_rk_pair_plus_ssd_res_refit_x);
  fChain->SetBranchAddress("rk_pair_plus_ssd_res_refit_y", &rk_pair_plus_ssd_res_refit_y, &b_rk_pair_plus_ssd_res_refit_y);
  fChain->SetBranchAddress("rk_pair_plus_ssd_res_refit_z", &rk_pair_plus_ssd_res_refit_z, &b_rk_pair_plus_ssd_res_refit_z);
  fChain->SetBranchAddress("rk_pair_plus_gtr100_res_refit_x", &rk_pair_plus_gtr100_res_refit_x, &b_rk_pair_plus_gtr100_res_refit_x);
  fChain->SetBranchAddress("rk_pair_plus_gtr100_res_refit_y", &rk_pair_plus_gtr100_res_refit_y, &b_rk_pair_plus_gtr100_res_refit_y);
  fChain->SetBranchAddress("rk_pair_plus_gtr100_res_refit_z", &rk_pair_plus_gtr100_res_refit_z, &b_rk_pair_plus_gtr100_res_refit_z);
  fChain->SetBranchAddress("rk_pair_plus_gtr200_res_refit_x", &rk_pair_plus_gtr200_res_refit_x, &b_rk_pair_plus_gtr200_res_refit_x);
  fChain->SetBranchAddress("rk_pair_plus_gtr200_res_refit_y", &rk_pair_plus_gtr200_res_refit_y, &b_rk_pair_plus_gtr200_res_refit_y);
  fChain->SetBranchAddress("rk_pair_plus_gtr200_res_refit_z", &rk_pair_plus_gtr200_res_refit_z, &b_rk_pair_plus_gtr200_res_refit_z);
  fChain->SetBranchAddress("rk_pair_plus_gtr300_res_refit_x", &rk_pair_plus_gtr300_res_refit_x, &b_rk_pair_plus_gtr300_res_refit_x);
  fChain->SetBranchAddress("rk_pair_plus_gtr300_res_refit_y", &rk_pair_plus_gtr300_res_refit_y, &b_rk_pair_plus_gtr300_res_refit_y);
  fChain->SetBranchAddress("rk_pair_plus_gtr300_res_refit_z", &rk_pair_plus_gtr300_res_refit_z, &b_rk_pair_plus_gtr300_res_refit_z);
  fChain->SetBranchAddress("rk_pair_mass_refit", &rk_pair_mass_refit, &b_rk_pair_mass_refit);
  Notify();
}

void E16ANA_TrackAnalyzerFromTree::InitOutTree() {
  out_tree->Branch("run_id", &out_run_id, "run_id/I");
  out_tree->Branch("event_id", &out_event_id, "event_id/I");
  out_tree->Branch("n_tracks", &out_n_tracks, "n_tracks/I");
  out_tree->Branch("n_pairs", &out_n_pairs, "n_pairs/I");
  out_tree->Branch("n_selected_pairs", &out_n_selected_pairs, "n_selected_pairs/I");
  out_tree->Branch("is_selected", &out_is_selected);
  out_tree->Branch("minus_track_id", &out_minus_track_id);
  out_tree->Branch("plus_track_id", &out_plus_track_id);
  out_tree->Branch("chi_square", &out_chi_square);
  out_tree->Branch("vtx_gx", &out_vtx_gx);
  out_tree->Branch("vtx_gy", &out_vtx_gy);
  out_tree->Branch("vtx_gz", &out_vtx_gz);
  out_tree->Branch("minus_mom", &out_minus_mom);
  out_tree->Branch("minus_mom_gx", &out_minus_mom_gx);
  out_tree->Branch("minus_mom_gy", &out_minus_mom_gy);
  out_tree->Branch("minus_mom_gz", &out_minus_mom_gz);
  out_tree->Branch("plus_mom", &out_plus_mom);
  out_tree->Branch("plus_mom_gx", &out_plus_mom_gx);
  out_tree->Branch("plus_mom_gy", &out_plus_mom_gy);
  out_tree->Branch("plus_mom_gz", &out_plus_mom_gz);
  out_tree->Branch("minus_ssd_mid", &out_minus_ssd_mid);
  out_tree->Branch("minus_gtr100_mid", &out_minus_gtr100_mid);
  out_tree->Branch("minus_gtr200_mid", &out_minus_gtr200_mid);
  out_tree->Branch("minus_gtr300_mid", &out_minus_gtr300_mid);
  out_tree->Branch("plus_ssd_mid", &out_plus_ssd_mid);
  out_tree->Branch("plus_gtr100_mid", &out_plus_gtr100_mid);
  out_tree->Branch("plus_gtr200_mid", &out_plus_gtr200_mid);
  out_tree->Branch("plus_gtr300_mid", &out_plus_gtr300_mid);
  out_tree->Branch("minus_proj_lg_max_adc",  &out_minus_proj_lg_max_adc);
  out_tree->Branch("minus_proj_hbd_max_adc", &out_minus_proj_hbd_max_adc);
  out_tree->Branch("plus_proj_lg_max_adc",  &out_plus_proj_lg_max_adc);
  out_tree->Branch("plus_proj_hbd_max_adc", &out_plus_proj_hbd_max_adc);
  out_tree->Branch("minus_ssd_hit_pos_gx", &out_minus_ssd_hit_pos_gx);
  out_tree->Branch("minus_ssd_hit_pos_gy", &out_minus_ssd_hit_pos_gy);
  out_tree->Branch("minus_ssd_hit_pos_gz", &out_minus_ssd_hit_pos_gz);
  out_tree->Branch("minus_gtr100_hit_pos_gx", &out_minus_gtr100_hit_pos_gx);
  out_tree->Branch("minus_gtr100_hit_pos_gy", &out_minus_gtr100_hit_pos_gy);
  out_tree->Branch("minus_gtr100_hit_pos_gz", &out_minus_gtr100_hit_pos_gz);
  out_tree->Branch("minus_gtr200_hit_pos_gx", &out_minus_gtr200_hit_pos_gx);
  out_tree->Branch("minus_gtr200_hit_pos_gy", &out_minus_gtr200_hit_pos_gy);
  out_tree->Branch("minus_gtr200_hit_pos_gz", &out_minus_gtr200_hit_pos_gz);
  out_tree->Branch("minus_gtr300_hit_pos_gx", &out_minus_gtr300_hit_pos_gx);
  out_tree->Branch("minus_gtr300_hit_pos_gy", &out_minus_gtr300_hit_pos_gy);
  out_tree->Branch("minus_gtr300_hit_pos_gz", &out_minus_gtr300_hit_pos_gz);
  out_tree->Branch("plus_ssd_hit_pos_gx", &out_plus_ssd_hit_pos_gx);
  out_tree->Branch("plus_ssd_hit_pos_gy", &out_plus_ssd_hit_pos_gy);
  out_tree->Branch("plus_ssd_hit_pos_gz", &out_plus_ssd_hit_pos_gz);
  out_tree->Branch("plus_gtr100_hit_pos_gx", &out_plus_gtr100_hit_pos_gx);
  out_tree->Branch("plus_gtr100_hit_pos_gy", &out_plus_gtr100_hit_pos_gy);
  out_tree->Branch("plus_gtr100_hit_pos_gz", &out_plus_gtr100_hit_pos_gz);
  out_tree->Branch("plus_gtr200_hit_pos_gx", &out_plus_gtr200_hit_pos_gx);
  out_tree->Branch("plus_gtr200_hit_pos_gy", &out_plus_gtr200_hit_pos_gy);
  out_tree->Branch("plus_gtr200_hit_pos_gz", &out_plus_gtr200_hit_pos_gz);
  out_tree->Branch("plus_gtr300_hit_pos_gx", &out_plus_gtr300_hit_pos_gx);
  out_tree->Branch("plus_gtr300_hit_pos_gy", &out_plus_gtr300_hit_pos_gy);
  out_tree->Branch("plus_gtr300_hit_pos_gz", &out_plus_gtr300_hit_pos_gz);
  out_tree->Branch("minus_ssd_fit_pos_x", &out_minus_ssd_fit_pos_x);
  out_tree->Branch("minus_ssd_fit_pos_y", &out_minus_ssd_fit_pos_y);
  out_tree->Branch("minus_ssd_fit_pos_z", &out_minus_ssd_fit_pos_z);
  out_tree->Branch("minus_gtr100_fit_pos_x", &out_minus_gtr100_fit_pos_x);
  out_tree->Branch("minus_gtr100_fit_pos_y", &out_minus_gtr100_fit_pos_y);
  out_tree->Branch("minus_gtr100_fit_pos_z", &out_minus_gtr100_fit_pos_z);
  out_tree->Branch("minus_gtr200_fit_pos_x", &out_minus_gtr200_fit_pos_x);
  out_tree->Branch("minus_gtr200_fit_pos_y", &out_minus_gtr200_fit_pos_y);
  out_tree->Branch("minus_gtr200_fit_pos_z", &out_minus_gtr200_fit_pos_z);
  out_tree->Branch("minus_gtr300_fit_pos_x", &out_minus_gtr300_fit_pos_x);
  out_tree->Branch("minus_gtr300_fit_pos_y", &out_minus_gtr300_fit_pos_y);
  out_tree->Branch("minus_gtr300_fit_pos_z", &out_minus_gtr300_fit_pos_z);
  out_tree->Branch("plus_ssd_fit_pos_x", &out_plus_ssd_fit_pos_x);
  out_tree->Branch("plus_ssd_fit_pos_y", &out_plus_ssd_fit_pos_y);
  out_tree->Branch("plus_ssd_fit_pos_z", &out_plus_ssd_fit_pos_z);
  out_tree->Branch("plus_gtr100_fit_pos_x", &out_plus_gtr100_fit_pos_x);
  out_tree->Branch("plus_gtr100_fit_pos_y", &out_plus_gtr100_fit_pos_y);
  out_tree->Branch("plus_gtr100_fit_pos_z", &out_plus_gtr100_fit_pos_z);
  out_tree->Branch("plus_gtr200_fit_pos_x", &out_plus_gtr200_fit_pos_x);
  out_tree->Branch("plus_gtr200_fit_pos_y", &out_plus_gtr200_fit_pos_y);
  out_tree->Branch("plus_gtr200_fit_pos_z", &out_plus_gtr200_fit_pos_z);
  out_tree->Branch("plus_gtr300_fit_pos_x", &out_plus_gtr300_fit_pos_x);
  out_tree->Branch("plus_gtr300_fit_pos_y", &out_plus_gtr300_fit_pos_y);
  out_tree->Branch("plus_gtr300_fit_pos_z", &out_plus_gtr300_fit_pos_z);
  out_tree->Branch("minus_ssd_fit_pos_gx", &out_minus_ssd_fit_pos_gx);
  out_tree->Branch("minus_ssd_fit_pos_gy", &out_minus_ssd_fit_pos_gy);
  out_tree->Branch("minus_ssd_fit_pos_gz", &out_minus_ssd_fit_pos_gz);
  out_tree->Branch("minus_gtr100_fit_pos_gx", &out_minus_gtr100_fit_pos_gx);
  out_tree->Branch("minus_gtr100_fit_pos_gy", &out_minus_gtr100_fit_pos_gy);
  out_tree->Branch("minus_gtr100_fit_pos_gz", &out_minus_gtr100_fit_pos_gz);
  out_tree->Branch("minus_gtr200_fit_pos_gx", &out_minus_gtr200_fit_pos_gx);
  out_tree->Branch("minus_gtr200_fit_pos_gy", &out_minus_gtr200_fit_pos_gy);
  out_tree->Branch("minus_gtr200_fit_pos_gz", &out_minus_gtr200_fit_pos_gz);
  out_tree->Branch("minus_gtr300_fit_pos_gx", &out_minus_gtr300_fit_pos_gx);
  out_tree->Branch("minus_gtr300_fit_pos_gy", &out_minus_gtr300_fit_pos_gy);
  out_tree->Branch("minus_gtr300_fit_pos_gz", &out_minus_gtr300_fit_pos_gz);
  out_tree->Branch("plus_ssd_fit_pos_gx", &out_plus_ssd_fit_pos_gx);
  out_tree->Branch("plus_ssd_fit_pos_gy", &out_plus_ssd_fit_pos_gy);
  out_tree->Branch("plus_ssd_fit_pos_gz", &out_plus_ssd_fit_pos_gz);
  out_tree->Branch("plus_gtr100_fit_pos_gx", &out_plus_gtr100_fit_pos_gx);
  out_tree->Branch("plus_gtr100_fit_pos_gy", &out_plus_gtr100_fit_pos_gy);
  out_tree->Branch("plus_gtr100_fit_pos_gz", &out_plus_gtr100_fit_pos_gz);
  out_tree->Branch("plus_gtr200_fit_pos_gx", &out_plus_gtr200_fit_pos_gx);
  out_tree->Branch("plus_gtr200_fit_pos_gy", &out_plus_gtr200_fit_pos_gy);
  out_tree->Branch("plus_gtr200_fit_pos_gz", &out_plus_gtr200_fit_pos_gz);
  out_tree->Branch("plus_gtr300_fit_pos_gx", &out_plus_gtr300_fit_pos_gx);
  out_tree->Branch("plus_gtr300_fit_pos_gy", &out_plus_gtr300_fit_pos_gy);
  out_tree->Branch("plus_gtr300_fit_pos_gz", &out_plus_gtr300_fit_pos_gz);
  out_tree->Branch("minus_ssd_fit_mom",     &out_minus_ssd_fit_mom);
  out_tree->Branch("minus_ssd_fit_mom_x",   &out_minus_ssd_fit_mom_x);
  out_tree->Branch("minus_ssd_fit_mom_y",   &out_minus_ssd_fit_mom_y);
  out_tree->Branch("minus_ssd_fit_mom_z",   &out_minus_ssd_fit_mom_z);
  out_tree->Branch("minus_ssd_fit_mom_tan", &out_minus_ssd_fit_mom_tan);
  out_tree->Branch("minus_ssd_fit_mom_gx",  &out_minus_ssd_fit_mom_gx);
  out_tree->Branch("minus_ssd_fit_mom_gy",  &out_minus_ssd_fit_mom_gy);
  out_tree->Branch("minus_ssd_fit_mom_gz",  &out_minus_ssd_fit_mom_gz);
  out_tree->Branch("minus_gtr100_fit_mom",     &out_minus_gtr100_fit_mom);
  out_tree->Branch("minus_gtr100_fit_mom_x",   &out_minus_gtr100_fit_mom_x);
  out_tree->Branch("minus_gtr100_fit_mom_y",   &out_minus_gtr100_fit_mom_y);
  out_tree->Branch("minus_gtr100_fit_mom_z",   &out_minus_gtr100_fit_mom_z);
  out_tree->Branch("minus_gtr100_fit_mom_tan", &out_minus_gtr100_fit_mom_tan);
  out_tree->Branch("minus_gtr100_fit_mom_gx",  &out_minus_gtr100_fit_mom_gx);
  out_tree->Branch("minus_gtr100_fit_mom_gy",  &out_minus_gtr100_fit_mom_gy);
  out_tree->Branch("minus_gtr100_fit_mom_gz",  &out_minus_gtr100_fit_mom_gz);
  out_tree->Branch("minus_gtr200_fit_mom",     &out_minus_gtr200_fit_mom);
  out_tree->Branch("minus_gtr200_fit_mom_x",   &out_minus_gtr200_fit_mom_x);
  out_tree->Branch("minus_gtr200_fit_mom_y",   &out_minus_gtr200_fit_mom_y);
  out_tree->Branch("minus_gtr200_fit_mom_z",   &out_minus_gtr200_fit_mom_z);
  out_tree->Branch("minus_gtr200_fit_mom_tan", &out_minus_gtr200_fit_mom_tan);
  out_tree->Branch("minus_gtr200_fit_mom_gx",  &out_minus_gtr200_fit_mom_gx);
  out_tree->Branch("minus_gtr200_fit_mom_gy",  &out_minus_gtr200_fit_mom_gy);
  out_tree->Branch("minus_gtr200_fit_mom_gz",  &out_minus_gtr200_fit_mom_gz);
  out_tree->Branch("minus_gtr300_fit_mom",     &out_minus_gtr300_fit_mom);
  out_tree->Branch("minus_gtr300_fit_mom_x",   &out_minus_gtr300_fit_mom_x);
  out_tree->Branch("minus_gtr300_fit_mom_y",   &out_minus_gtr300_fit_mom_y);
  out_tree->Branch("minus_gtr300_fit_mom_z",   &out_minus_gtr300_fit_mom_z);
  out_tree->Branch("minus_gtr300_fit_mom_tan", &out_minus_gtr300_fit_mom_tan);
  out_tree->Branch("minus_gtr300_fit_mom_gx",  &out_minus_gtr300_fit_mom_gx);
  out_tree->Branch("minus_gtr300_fit_mom_gy",  &out_minus_gtr300_fit_mom_gy);
  out_tree->Branch("minus_gtr300_fit_mom_gz",  &out_minus_gtr300_fit_mom_gz);
  out_tree->Branch("plus_ssd_fit_mom",     &out_plus_ssd_fit_mom);
  out_tree->Branch("plus_ssd_fit_mom_x",   &out_plus_ssd_fit_mom_x);
  out_tree->Branch("plus_ssd_fit_mom_y",   &out_plus_ssd_fit_mom_y);
  out_tree->Branch("plus_ssd_fit_mom_z",   &out_plus_ssd_fit_mom_z);
  out_tree->Branch("plus_ssd_fit_mom_tan", &out_plus_ssd_fit_mom_tan);
  out_tree->Branch("plus_ssd_fit_mom_gx",  &out_plus_ssd_fit_mom_gx);
  out_tree->Branch("plus_ssd_fit_mom_gy",  &out_plus_ssd_fit_mom_gy);
  out_tree->Branch("plus_ssd_fit_mom_gz",  &out_plus_ssd_fit_mom_gz);
  out_tree->Branch("plus_gtr100_fit_mom",     &out_plus_gtr100_fit_mom);
  out_tree->Branch("plus_gtr100_fit_mom_x",   &out_plus_gtr100_fit_mom_x);
  out_tree->Branch("plus_gtr100_fit_mom_y",   &out_plus_gtr100_fit_mom_y);
  out_tree->Branch("plus_gtr100_fit_mom_z",   &out_plus_gtr100_fit_mom_z);
  out_tree->Branch("plus_gtr100_fit_mom_tan", &out_plus_gtr100_fit_mom_tan);
  out_tree->Branch("plus_gtr100_fit_mom_gx",  &out_plus_gtr100_fit_mom_gx);
  out_tree->Branch("plus_gtr100_fit_mom_gy",  &out_plus_gtr100_fit_mom_gy);
  out_tree->Branch("plus_gtr100_fit_mom_gz",  &out_plus_gtr100_fit_mom_gz);
  out_tree->Branch("plus_gtr200_fit_mom",     &out_plus_gtr200_fit_mom);
  out_tree->Branch("plus_gtr200_fit_mom_x",   &out_plus_gtr200_fit_mom_x);
  out_tree->Branch("plus_gtr200_fit_mom_y",   &out_plus_gtr200_fit_mom_y);
  out_tree->Branch("plus_gtr200_fit_mom_z",   &out_plus_gtr200_fit_mom_z);
  out_tree->Branch("plus_gtr200_fit_mom_tan", &out_plus_gtr200_fit_mom_tan);
  out_tree->Branch("plus_gtr200_fit_mom_gx",  &out_plus_gtr200_fit_mom_gx);
  out_tree->Branch("plus_gtr200_fit_mom_gy",  &out_plus_gtr200_fit_mom_gy);
  out_tree->Branch("plus_gtr200_fit_mom_gz",  &out_plus_gtr200_fit_mom_gz);
  out_tree->Branch("plus_gtr300_fit_mom",     &out_plus_gtr300_fit_mom);
  out_tree->Branch("plus_gtr300_fit_mom_x",   &out_plus_gtr300_fit_mom_x);
  out_tree->Branch("plus_gtr300_fit_mom_y",   &out_plus_gtr300_fit_mom_y);
  out_tree->Branch("plus_gtr300_fit_mom_z",   &out_plus_gtr300_fit_mom_z);
  out_tree->Branch("plus_gtr300_fit_mom_tan", &out_plus_gtr300_fit_mom_tan);
  out_tree->Branch("plus_gtr300_fit_mom_gx",  &out_plus_gtr300_fit_mom_gx);
  out_tree->Branch("plus_gtr300_fit_mom_gy",  &out_plus_gtr300_fit_mom_gy);
  out_tree->Branch("plus_gtr300_fit_mom_gz",  &out_plus_gtr300_fit_mom_gz);
  out_tree->Branch("minus_ssd_fit_res_x", &out_minus_ssd_fit_res_x);
  out_tree->Branch("minus_ssd_fit_res_y", &out_minus_ssd_fit_res_y);
  out_tree->Branch("minus_ssd_fit_res_z", &out_minus_ssd_fit_res_z);
  out_tree->Branch("minus_gtr100_fit_res_x", &out_minus_gtr100_fit_res_x);
  out_tree->Branch("minus_gtr100_fit_res_y", &out_minus_gtr100_fit_res_y);
  out_tree->Branch("minus_gtr100_fit_res_z", &out_minus_gtr100_fit_res_z);
  out_tree->Branch("minus_gtr200_fit_res_x", &out_minus_gtr200_fit_res_x);
  out_tree->Branch("minus_gtr200_fit_res_y", &out_minus_gtr200_fit_res_y);
  out_tree->Branch("minus_gtr200_fit_res_z", &out_minus_gtr200_fit_res_z);
  out_tree->Branch("minus_gtr300_fit_res_x", &out_minus_gtr300_fit_res_x);
  out_tree->Branch("minus_gtr300_fit_res_y", &out_minus_gtr300_fit_res_y);
  out_tree->Branch("minus_gtr300_fit_res_z", &out_minus_gtr300_fit_res_z);
  out_tree->Branch("plus_ssd_fit_res_x", &out_plus_ssd_fit_res_x);
  out_tree->Branch("plus_ssd_fit_res_y", &out_plus_ssd_fit_res_y);
  out_tree->Branch("plus_ssd_fit_res_z", &out_plus_ssd_fit_res_z);
  out_tree->Branch("plus_gtr100_fit_res_x", &out_plus_gtr100_fit_res_x);
  out_tree->Branch("plus_gtr100_fit_res_y", &out_plus_gtr100_fit_res_y);
  out_tree->Branch("plus_gtr100_fit_res_z", &out_plus_gtr100_fit_res_z);
  out_tree->Branch("plus_gtr200_fit_res_x", &out_plus_gtr200_fit_res_x);
  out_tree->Branch("plus_gtr200_fit_res_y", &out_plus_gtr200_fit_res_y);
  out_tree->Branch("plus_gtr200_fit_res_z", &out_plus_gtr200_fit_res_z);
  out_tree->Branch("plus_gtr300_fit_res_x", &out_plus_gtr300_fit_res_x);
  out_tree->Branch("plus_gtr300_fit_res_y", &out_plus_gtr300_fit_res_y);
  out_tree->Branch("plus_gtr300_fit_res_z", &out_plus_gtr300_fit_res_z);
  out_tree->Branch("ee_mass", &out_ee_mass);
  out_tree->Branch("pipi_mass", &out_pipi_mass);
  out_tree->Branch("pip_mass", &out_pip_mass);
  out_tree->Branch("ks_pos_at_x0_gx", &out_ks_pos_at_x0_gx);
  out_tree->Branch("ks_pos_at_x0_gy", &out_ks_pos_at_x0_gy);
  out_tree->Branch("ks_pos_at_x0_gz", &out_ks_pos_at_x0_gz);
  out_tree->Branch("ks_mom_at_x0_gx", &out_ks_mom_at_x0_gx);
  out_tree->Branch("ks_mom_at_x0_gy", &out_ks_mom_at_x0_gy);
  out_tree->Branch("ks_mom_at_x0_gz", &out_ks_mom_at_x0_gz);
  out_tree->Branch("ks_t_at_x0",      &out_ks_t_at_x0);

  out_tree->Branch("minus_proj_hbd_id", &out_minus_proj_hbd_id);
  out_tree->Branch("minus_proj_hbd_mid", &out_minus_proj_hbd_mid);
  out_tree->Branch("minus_proj_hbd_x", &out_minus_proj_hbd_x);
  out_tree->Branch("minus_proj_hbd_y", &out_minus_proj_hbd_y);
  //  out_tree->Branch("minus_proj_hbd_gx", &out_minus_proj_hbd_gx);
  //  out_tree->Branch("minus_proj_hbd_gy", &out_minus_proj_hbd_gy);
  //  out_tree->Branch("minus_proj_hbd_gz", &out_minus_proj_hbd_gz);
  //  out_tree->Branch("minus_proj_hbd_adc", &out_minus_proj_hbd_adc);
  out_tree->Branch("minus_proj_hbd_t", &out_minus_proj_hbd_t);
  out_tree->Branch("minus_proj_hbd_ftime", &out_minus_proj_hbd_ftime);
  out_tree->Branch("minus_proj_hbd_tdiff", &out_minus_proj_hbd_tdiff);
  out_tree->Branch("minus_proj_hbd_size", &out_minus_proj_hbd_size);
  out_tree->Branch("minus_proj_hbd_eprob", &out_minus_proj_hbd_eprob);
  out_tree->Branch("minus_proj_hbd_cprob", &out_minus_proj_hbd_cprob);
  out_tree->Branch("minus_proj_lg_id", &out_minus_proj_lg_id);
  out_tree->Branch("minus_proj_lg_mid", &out_minus_proj_lg_mid);
  out_tree->Branch("minus_proj_lg_x", &out_minus_proj_lg_x);
  out_tree->Branch("minus_proj_lg_y", &out_minus_proj_lg_y);
  //  out_tree->Branch("minus_proj_lg_gx", &out_minus_proj_lg_gx);
  //  out_tree->Branch("minus_proj_lg_gy", &out_minus_proj_lg_gy);
  //  out_tree->Branch("minus_proj_lg_gz", &out_minus_proj_lg_gz);
  //  out_tree->Branch("minus_proj_lg_adc", &out_minus_proj_lg_adc);
  out_tree->Branch("minus_proj_lg_t", &out_minus_proj_lg_t);
  out_tree->Branch("minus_proj_lg_npeaks", &out_minus_proj_lg_npeaks);
  out_tree->Branch("minus_proj_lg_fflag", &out_minus_proj_lg_fflag);
  out_tree->Branch("plus_proj_hbd_id", &out_plus_proj_hbd_id);
  out_tree->Branch("plus_proj_hbd_mid", &out_plus_proj_hbd_mid);
  out_tree->Branch("plus_proj_hbd_x", &out_plus_proj_hbd_x);
  out_tree->Branch("plus_proj_hbd_y", &out_plus_proj_hbd_y);
  //  out_tree->Branch("plus_proj_hbd_gx", &out_plus_proj_hbd_gx);
  //  out_tree->Branch("plus_proj_hbd_gy", &out_plus_proj_hbd_gy);
  //  out_tree->Branch("plus_proj_hbd_gz", &out_plus_proj_hbd_gz);
  //  out_tree->Branch("plus_proj_hbd_adc", &out_plus_proj_hbd_adc);
  out_tree->Branch("plus_proj_hbd_t", &out_plus_proj_hbd_t);
  out_tree->Branch("plus_proj_hbd_ftime", &out_plus_proj_hbd_ftime);
  out_tree->Branch("plus_proj_hbd_tdiff", &out_plus_proj_hbd_tdiff);
  out_tree->Branch("plus_proj_hbd_size", &out_plus_proj_hbd_size);
  out_tree->Branch("plus_proj_hbd_eprob", &out_plus_proj_hbd_eprob);
  out_tree->Branch("plus_proj_hbd_cprob", &out_plus_proj_hbd_cprob);
  out_tree->Branch("plus_proj_lg_id", &out_plus_proj_lg_id);
  out_tree->Branch("plus_proj_lg_mid", &out_plus_proj_lg_mid);
  out_tree->Branch("plus_proj_lg_x", &out_plus_proj_lg_x);
  out_tree->Branch("plus_proj_lg_y", &out_plus_proj_lg_y);
  //  out_tree->Branch("plus_proj_lg_gx", &out_plus_proj_lg_gx);
  //  out_tree->Branch("plus_proj_lg_gy", &out_plus_proj_lg_gy);
  //  out_tree->Branch("plus_proj_lg_gz", &out_plus_proj_lg_gz);
  //  out_tree->Branch("plus_proj_lg_adc", &out_plus_proj_lg_adc);
  out_tree->Branch("plus_proj_lg_t", &out_plus_proj_lg_t);
  out_tree->Branch("plus_proj_lg_npeaks", &out_plus_proj_lg_npeaks);
  out_tree->Branch("plus_proj_lg_fflag", &out_plus_proj_lg_fflag);

  // out_tree->Branch("n_hbd_clusters", &out_n_hbd_clusters, "n_hbd_clusters/I");
  // out_tree->Branch("hbd_cluster_id", &out_hbd_cluster_id);
  // out_tree->Branch("hbd_cluster_mid", &out_hbd_cluster_mid);
  // out_tree->Branch("hbd_cluster_x", &out_hbd_cluster_x);
  // out_tree->Branch("hbd_cluster_y", &out_hbd_cluster_y);
  // out_tree->Branch("hbd_cluster_gx", &out_hbd_cluster_gx);
  // out_tree->Branch("hbd_cluster_gy", &out_hbd_cluster_gy);
  // out_tree->Branch("hbd_cluster_gz", &out_hbd_cluster_gz);
  // out_tree->Branch("hbd_cluster_adc", &out_hbd_cluster_adc);
  // out_tree->Branch("hbd_cluster_t", &out_hbd_cluster_t);
  // out_tree->Branch("hbd_cluster_ftime", &out_hbd_cluster_ftime);
  // out_tree->Branch("hbd_cluster_tdiff", &out_hbd_cluster_tdiff);
  // out_tree->Branch("hbd_cluster_size", &out_hbd_cluster_size);
  // out_tree->Branch("hbd_cluster_eprob", &out_hbd_cluster_eprob);
  // out_tree->Branch("hbd_cluster_cprob", &out_hbd_cluster_cprob);
  // out_tree->Branch("n_lg_hits", &out_n_lg_hits, "n_lg_hits/I");
  // out_tree->Branch("lg_hit_id", &out_lg_hit_id);
  // out_tree->Branch("lg_hit_mid", &out_lg_hit_mid);
  // out_tree->Branch("lg_hit_x", &out_lg_hit_x);
  // out_tree->Branch("lg_hit_y", &out_lg_hit_y);
  // out_tree->Branch("lg_hit_gx", &out_lg_hit_gx);
  // out_tree->Branch("lg_hit_gy", &out_lg_hit_gy);
  // out_tree->Branch("lg_hit_gz", &out_lg_hit_gz);
  // out_tree->Branch("lg_hit_adc", &out_lg_hit_adc);
  // out_tree->Branch("lg_hit_t", &out_lg_hit_t);
  // out_tree->Branch("lg_hit_npeaks", &out_lg_hit_npeaks);
  // out_tree->Branch("lg_hit_fflag", &out_lg_hit_fflag);
  // out_tree->Branch("n_single_tracks", &out_n_single_tracks, "n_single_tracks/I");
  // out_tree->Branch("single_track_id", &out_single_track_id);
  // out_tree->Branch("single_chi_square", &out_single_chi_square);
  // out_tree->Branch("rk_fit_hbd_mid", &out_rk_fit_hbd_mid);
  // out_tree->Branch("rk_fit_hbd_x",   &out_rk_fit_hbd_x);
  // out_tree->Branch("rk_fit_hbd_y",   &out_rk_fit_hbd_y);
  // out_tree->Branch("rk_fit_hbd_gx",  &out_rk_fit_hbd_gx);
  // out_tree->Branch("rk_fit_hbd_gy",  &out_rk_fit_hbd_gy);
  // out_tree->Branch("rk_fit_hbd_gz",  &out_rk_fit_hbd_gz);
  // out_tree->Branch("rk_fit_lg_c_mid", &out_rk_fit_lg_c_mid);
  // out_tree->Branch("rk_fit_lg_c_x",   &out_rk_fit_lg_c_x);
  // out_tree->Branch("rk_fit_lg_c_y",   &out_rk_fit_lg_c_y);
  // out_tree->Branch("rk_fit_lg_c_gx",  &out_rk_fit_lg_c_gx);
  // out_tree->Branch("rk_fit_lg_c_gy",  &out_rk_fit_lg_c_gy);
  // out_tree->Branch("rk_fit_lg_c_gz",  &out_rk_fit_lg_c_gz);
  // out_tree->Branch("rk_fit_lg_b_mid", &out_rk_fit_lg_b_mid);
  // out_tree->Branch("rk_fit_lg_b_x",   &out_rk_fit_lg_b_x);
  // out_tree->Branch("rk_fit_lg_b_y",   &out_rk_fit_lg_b_y);
  // out_tree->Branch("rk_fit_lg_b_gx",  &out_rk_fit_lg_b_gx);
  // out_tree->Branch("rk_fit_lg_b_gy",  &out_rk_fit_lg_b_gy);
  // out_tree->Branch("rk_fit_lg_b_gz",  &out_rk_fit_lg_b_gz);
  // out_tree->Branch("rk_fit_lg_a_mid", &out_rk_fit_lg_a_mid);
  // out_tree->Branch("rk_fit_lg_a_x",   &out_rk_fit_lg_a_x);
  // out_tree->Branch("rk_fit_lg_a_y",   &out_rk_fit_lg_a_y);
  // out_tree->Branch("rk_fit_lg_a_gx",  &out_rk_fit_lg_a_gx);
  // out_tree->Branch("rk_fit_lg_a_gy",  &out_rk_fit_lg_a_gy);
  // out_tree->Branch("rk_fit_lg_a_gz",  &out_rk_fit_lg_a_gz);
  // out_tree->Branch("rk_res_ssd_x", &out_rk_res_ssd_x);
  // out_tree->Branch("rk_res_gtr100_x", &out_rk_res_gtr100_x);
  // out_tree->Branch("rk_res_gtr100_y", &out_rk_res_gtr100_y);
  // out_tree->Branch("rk_res_gtr200_x", &out_rk_res_gtr200_x);
  // out_tree->Branch("rk_res_gtr200_y", &out_rk_res_gtr200_y);
  // out_tree->Branch("rk_res_gtr300_x", &out_rk_res_gtr300_x);
  // out_tree->Branch("rk_res_gtr300_y", &out_rk_res_gtr300_y);
  // out_tree->Branch("rk_proj_tgt0_gx", &out_rk_proj_tgt0_gx);
  // out_tree->Branch("rk_proj_tgt0_gy", &out_rk_proj_tgt0_gy);
  // out_tree->Branch("rk_proj_tgt0_gz", &out_rk_proj_tgt0_gz);
  // out_tree->Branch("rk_proj_tgt1_gx", &out_rk_proj_tgt1_gx);
  // out_tree->Branch("rk_proj_tgt1_gy", &out_rk_proj_tgt1_gy);
  // out_tree->Branch("rk_proj_tgt1_gz", &out_rk_proj_tgt1_gz);
  // out_tree->Branch("rk_proj_tgt2_gx", &out_rk_proj_tgt2_gx);
  // out_tree->Branch("rk_proj_tgt2_gy", &out_rk_proj_tgt2_gy);
  // out_tree->Branch("rk_proj_tgt2_gz", &out_rk_proj_tgt2_gz);
  // out_tree->Branch("rk_proj_tgt0_mom_gx", &out_rk_proj_tgt0_mom_gx);
  // out_tree->Branch("rk_proj_tgt0_mom_gy", &out_rk_proj_tgt0_mom_gy);
  // out_tree->Branch("rk_proj_tgt0_mom_gz", &out_rk_proj_tgt0_mom_gz);
  // out_tree->Branch("rk_proj_n_hbd", &out_rk_proj_n_hbd);
  // out_tree->Branch("rk_proj_hbd0_id", &out_rk_proj_hbd0_id);
  // out_tree->Branch("rk_proj_hbd0_mid", &out_rk_proj_hbd0_mid);
  // out_tree->Branch("rk_proj_hbd1_id", &out_rk_proj_hbd0_id);
  // out_tree->Branch("rk_proj_hbd1_mid", &out_rk_proj_hbd0_mid);
  // out_tree->Branch("rk_proj_hbd2_id", &out_rk_proj_hbd0_id);
  // out_tree->Branch("rk_proj_hbd2_mid", &out_rk_proj_hbd0_mid);
  // out_tree->Branch("rk_proj_hbd3_id", &out_rk_proj_hbd0_id);
  // out_tree->Branch("rk_proj_hbd3_mid", &out_rk_proj_hbd0_mid);
  // out_tree->Branch("rk_proj_n_lg", &out_rk_proj_n_lg);
  // out_tree->Branch("rk_proj_lg0_id", &out_rk_proj_lg0_id);
  // out_tree->Branch("rk_proj_lg1_id", &out_rk_proj_lg0_id);
  // out_tree->Branch("rk_proj_lg2_id", &out_rk_proj_lg0_id);
  // out_tree->Branch("rk_proj_lg3_id", &out_rk_proj_lg0_id);
}

Bool_t E16ANA_TrackAnalyzerFromTree::Notify() {
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void E16ANA_TrackAnalyzerFromTree::Show(Long64_t entry) {
// Print contents of entry.
// If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

Int_t E16ANA_TrackAnalyzerFromTree::Cut(Long64_t entry) {
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
  return 1;
}
#endif // #ifdef E16ANA_TrackAnalyzerFromTree_cxx
