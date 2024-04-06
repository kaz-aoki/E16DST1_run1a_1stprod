//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Oct 13 00:07:02 2023 by ROOT version 5.34/01
// from TTree tree/tree
// found on file: root/out-run030737_sink0_000-event-0-999.root
//////////////////////////////////////////////////////////

#ifndef E16DSTN_AfterTrackAna_hh
#define E16DSTN_AfterTrackAna_hh

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>
#include <vector>
#include <vector>
#include <TH1D.h>
#include <TH2D.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class E16DSTN_AfterTrackAna {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           run_id;
   Int_t           event_id;
   Int_t           n_cands;
   Int_t           n_ssd_clusters;
   Int_t           n_gtr100x_clusters;
   Int_t           n_gtr100y_clusters;
   Int_t           n_gtr200x_clusters;
   Int_t           n_gtr200y_clusters;
   Int_t           n_gtr300x_clusters;
   Int_t           n_gtr300y_clusters;
   Int_t           n_hbd_clusters;
   Int_t           n_lg_hits;
   Int_t           n_trg_gtr_hits;
   std::vector<int>     *trg_gtr_hit_id;
   std::vector<int>     *trg_gtr_hit_mid;
   std::vector<int>     *trg_gtr_hit_cid;
   std::vector<double>  *trg_gtr_hit_x;
   std::vector<double>  *trg_gtr_hit_y;
   std::vector<double>  *trg_gtr_hit_gx;
   std::vector<double>  *trg_gtr_hit_gy;
   std::vector<double>  *trg_gtr_hit_gz;
   std::vector<float>   *trg_gtr_hit_t;
   Int_t           n_trg_hbd_hits;
   std::vector<int>     *trg_hbd_hit_id;
   std::vector<int>     *trg_hbd_hit_mid;
   std::vector<int>     *trg_hbd_hit_cid;
   std::vector<double>  *trg_hbd_hit_x;
   std::vector<double>  *trg_hbd_hit_y;
   std::vector<double>  *trg_hbd_hit_gx;
   std::vector<double>  *trg_hbd_hit_gy;
   std::vector<double>  *trg_hbd_hit_gz;
   std::vector<float>   *trg_hbd_hit_t;
   Int_t           n_trg_lg_hits;
   std::vector<int>     *trg_lg_hit_id;
   std::vector<int>     *trg_lg_hit_mid;
   std::vector<int>     *trg_lg_hit_cid;
   std::vector<double>  *trg_lg_hit_x;
   std::vector<double>  *trg_lg_hit_y;
   std::vector<double>  *trg_lg_hit_gx;
   std::vector<double>  *trg_lg_hit_gy;
   std::vector<double>  *trg_lg_hit_gz;
   std::vector<float>   *trg_lg_hit_t;
   Int_t           n_tracks;
   Int_t           n_pairs;
   std::vector<int>     *pair_order;
   std::vector<double>  *plus_rough_fit_init_pos_x;
   std::vector<double>  *plus_rough_fit_init_pos_y;
   std::vector<double>  *plus_rough_fit_init_pos_z;
   std::vector<double>  *plus_rough_fit_init_mom_x;
   std::vector<double>  *plus_rough_fit_init_mom_y;
   std::vector<double>  *plus_rough_fit_init_mom_z;
   std::vector<double>  *minus_rough_fit_init_pos_x;
   std::vector<double>  *minus_rough_fit_init_pos_y;
   std::vector<double>  *minus_rough_fit_init_pos_z;
   std::vector<double>  *minus_rough_fit_init_mom_x;
   std::vector<double>  *minus_rough_fit_init_mom_y;
   std::vector<double>  *minus_rough_fit_init_mom_z;
   std::vector<double>  *plus_single_fit_init_pos_x;
   std::vector<double>  *plus_single_fit_init_pos_y;
   std::vector<double>  *plus_single_fit_init_pos_z;
   std::vector<double>  *plus_single_fit_init_mom_x;
   std::vector<double>  *plus_single_fit_init_mom_y;
   std::vector<double>  *plus_single_fit_init_mom_z;
   std::vector<double>  *minus_single_fit_init_pos_x;
   std::vector<double>  *minus_single_fit_init_pos_y;
   std::vector<double>  *minus_single_fit_init_pos_z;
   std::vector<double>  *minus_single_fit_init_mom_x;
   std::vector<double>  *minus_single_fit_init_mom_y;
   std::vector<double>  *minus_single_fit_init_mom_z;
   std::vector<int>     *plus_track_id;
   std::vector<int>     *plus_charge_id;
   std::vector<int>     *hit_plus_ssd_id;
   std::vector<double>  *hit_plus_ssd_lx;
   std::vector<double>  *hit_plus_ssd_t;
   std::vector<double>  *hit_plus_ssd_adc;
   std::vector<int>     *hit_plus_ssd_size;
   std::vector<int>     *hit_plus_gtr100_xid;
   std::vector<int>     *hit_plus_gtr100_yid;
   std::vector<double>  *hit_plus_gtr100_lx;
   std::vector<double>  *hit_plus_gtr100_ly;
   std::vector<double>  *hit_plus_gtr100_xt;
   std::vector<double>  *hit_plus_gtr100_yt;
   std::vector<double>  *hit_plus_gtr100_xadc;
   std::vector<double>  *hit_plus_gtr100_yadc;
   std::vector<int>     *hit_plus_gtr100_xsize;
   std::vector<int>     *hit_plus_gtr100_ysize;
   std::vector<int>     *hit_plus_gtr200_xid;
   std::vector<int>     *hit_plus_gtr200_yid;
   std::vector<double>  *hit_plus_gtr200_lx;
   std::vector<double>  *hit_plus_gtr200_ly;
   std::vector<double>  *hit_plus_gtr200_xt;
   std::vector<double>  *hit_plus_gtr200_yt;
   std::vector<double>  *hit_plus_gtr200_xadc;
   std::vector<double>  *hit_plus_gtr200_yadc;
   std::vector<int>     *hit_plus_gtr200_xsize;
   std::vector<int>     *hit_plus_gtr200_ysize;
   std::vector<int>     *hit_plus_gtr300_xid;
   std::vector<int>     *hit_plus_gtr300_yid;
   std::vector<double>  *hit_plus_gtr300_lx;
   std::vector<double>  *hit_plus_gtr300_ly;
   std::vector<double>  *hit_plus_gtr300_xt;
   std::vector<double>  *hit_plus_gtr300_yt;
   std::vector<double>  *hit_plus_gtr300_xadc;
   std::vector<double>  *hit_plus_gtr300_yadc;
   std::vector<int>     *hit_plus_gtr300_xsize;
   std::vector<int>     *hit_plus_gtr300_ysize;
   std::vector<int>     *minus_track_id;
   std::vector<int>     *minus_charge_id;
   std::vector<int>     *hit_minus_ssd_id;
   std::vector<double>  *hit_minus_ssd_lx;
   std::vector<double>  *hit_minus_ssd_t;
   std::vector<double>  *hit_minus_ssd_adc;
   std::vector<int>     *hit_minus_ssd_size;
   std::vector<int>     *hit_minus_gtr100_xid;
   std::vector<int>     *hit_minus_gtr100_yid;
   std::vector<double>  *hit_minus_gtr100_lx;
   std::vector<double>  *hit_minus_gtr100_ly;
   std::vector<double>  *hit_minus_gtr100_xt;
   std::vector<double>  *hit_minus_gtr100_yt;
   std::vector<double>  *hit_minus_gtr100_xadc;
   std::vector<double>  *hit_minus_gtr100_yadc;
   std::vector<int>     *hit_minus_gtr100_xsize;
   std::vector<int>     *hit_minus_gtr100_ysize;
   std::vector<int>     *hit_minus_gtr200_xid;
   std::vector<int>     *hit_minus_gtr200_yid;
   std::vector<double>  *hit_minus_gtr200_lx;
   std::vector<double>  *hit_minus_gtr200_ly;
   std::vector<double>  *hit_minus_gtr200_xt;
   std::vector<double>  *hit_minus_gtr200_yt;
   std::vector<double>  *hit_minus_gtr200_xadc;
   std::vector<double>  *hit_minus_gtr200_yadc;
   std::vector<int>     *hit_minus_gtr200_xsize;
   std::vector<int>     *hit_minus_gtr200_ysize;
   std::vector<int>     *hit_minus_gtr300_xid;
   std::vector<int>     *hit_minus_gtr300_yid;
   std::vector<double>  *hit_minus_gtr300_lx;
   std::vector<double>  *hit_minus_gtr300_ly;
   std::vector<double>  *hit_minus_gtr300_xt;
   std::vector<double>  *hit_minus_gtr300_yt;
   std::vector<double>  *hit_minus_gtr300_xadc;
   std::vector<double>  *hit_minus_gtr300_yadc;
   std::vector<int>     *hit_minus_gtr300_xsize;
   std::vector<int>     *hit_minus_gtr300_ysize;
   std::vector<double>  *chi2;
   std::vector<double>  *plus_chi2;
   std::vector<double>  *minus_chi2;
   std::vector<int>     *flag;
   std::vector<double>  *distance;
   std::vector<int>     *plus_nearest_tgt_id;
   std::vector<double>  *plus_nearest_radius;
   std::vector<int>     *minus_nearest_tgt_id;
   std::vector<double>  *minus_nearest_radius;
   std::vector<int>     *dir_id;
   std::vector<double>  *vtx_x;
   std::vector<double>  *vtx_y;
   std::vector<double>  *vtx_z;
   std::vector<double>  *plus_pos_x;
   std::vector<double>  *plus_pos_y;
   std::vector<double>  *plus_pos_z;
   std::vector<double>  *minus_pos_x;
   std::vector<double>  *minus_pos_y;
   std::vector<double>  *minus_pos_z;
   std::vector<double>  *plus_mom;
   std::vector<double>  *plus_mom_x;
   std::vector<double>  *plus_mom_y;
   std::vector<double>  *plus_mom_z;
   std::vector<double>  *plus_mom_theta;
   std::vector<double>  *plus_mom_phi;
   std::vector<double>  *minus_mom;
   std::vector<double>  *minus_mom_x;
   std::vector<double>  *minus_mom_y;
   std::vector<double>  *minus_mom_z;
   std::vector<double>  *minus_mom_theta;
   std::vector<double>  *minus_mom_phi;
   std::vector<double>  *mom_angle;
   std::vector<double>  *ee_mass;
   std::vector<double>  *pipi_mass;
   std::vector<double>  *pip_mass;
   std::vector<double>  *kk_mass;
   std::vector<int>     *simple_best_tgt_id;
   std::vector<double>  *simple_best_tgt_r;
   std::vector<double>  *ee_mass_at_best_tgt;
   std::vector<double>  *pipi_mass_at_best_tgt;
   std::vector<double>  *pip_mass_at_best_tgt;
   std::vector<double>  *kk_mass_at_best_tgt;
   std::vector<int>     *plus_ssd_mid;
   std::vector<int>     *plus_gtr100_mid;
   std::vector<int>     *plus_gtr200_mid;
   std::vector<int>     *plus_gtr300_mid;
   std::vector<int>     *plus_hbd_mid;
   std::vector<int>     *plus_lg_c_mid;
   std::vector<int>     *plus_lg_b_mid;
   std::vector<int>     *plus_lg_a_mid;
   std::vector<int>     *minus_ssd_mid;
   std::vector<int>     *minus_gtr100_mid;
   std::vector<int>     *minus_gtr200_mid;
   std::vector<int>     *minus_gtr300_mid;
   std::vector<int>     *minus_hbd_mid;
   std::vector<int>     *minus_lg_c_mid;
   std::vector<int>     *minus_lg_b_mid;
   std::vector<int>     *minus_lg_a_mid;
   std::vector<double>  *fit_plus_ssd_lx;
   std::vector<double>  *fit_plus_ssd_ly;
   std::vector<double>  *fit_plus_gtr100_lx;
   std::vector<double>  *fit_plus_gtr100_ly;
   std::vector<double>  *fit_plus_gtr200_lx;
   std::vector<double>  *fit_plus_gtr200_ly;
   std::vector<double>  *fit_plus_gtr300_lx;
   std::vector<double>  *fit_plus_gtr300_ly;
   std::vector<double>  *fit_plus_hbd_lx;
   std::vector<double>  *fit_plus_hbd_ly;
   std::vector<double>  *fit_plus_lg_c_lx;
   std::vector<double>  *fit_plus_lg_c_ly;
   std::vector<double>  *fit_plus_lg_b_lx;
   std::vector<double>  *fit_plus_lg_b_ly;
   std::vector<double>  *fit_plus_lg_a_lx;
   std::vector<double>  *fit_plus_lg_a_ly;
   std::vector<double>  *fit_plus_tgt_minus_x;
   std::vector<double>  *fit_plus_tgt_minus_y;
   std::vector<double>  *fit_plus_tgt_zero_x;
   std::vector<double>  *fit_plus_tgt_zero_y;
   std::vector<double>  *fit_plus_tgt_plus_x;
   std::vector<double>  *fit_plus_tgt_plus_y;
   std::vector<double>  *fit_plus_x0_y;
   std::vector<double>  *fit_plus_x0_z;
   std::vector<double>  *fit_minus_ssd_lx;
   std::vector<double>  *fit_minus_ssd_ly;
   std::vector<double>  *fit_minus_gtr100_lx;
   std::vector<double>  *fit_minus_gtr100_ly;
   std::vector<double>  *fit_minus_gtr200_lx;
   std::vector<double>  *fit_minus_gtr200_ly;
   std::vector<double>  *fit_minus_gtr300_lx;
   std::vector<double>  *fit_minus_gtr300_ly;
   std::vector<double>  *fit_minus_hbd_lx;
   std::vector<double>  *fit_minus_hbd_ly;
   std::vector<double>  *fit_minus_lg_c_lx;
   std::vector<double>  *fit_minus_lg_c_ly;
   std::vector<double>  *fit_minus_lg_b_lx;
   std::vector<double>  *fit_minus_lg_b_ly;
   std::vector<double>  *fit_minus_lg_a_lx;
   std::vector<double>  *fit_minus_lg_a_ly;
   std::vector<double>  *fit_minus_tgt_minus_x;
   std::vector<double>  *fit_minus_tgt_minus_y;
   std::vector<double>  *fit_minus_tgt_zero_x;
   std::vector<double>  *fit_minus_tgt_zero_y;
   std::vector<double>  *fit_minus_tgt_plus_x;
   std::vector<double>  *fit_minus_tgt_plus_y;
   std::vector<double>  *fit_minus_x0_y;
   std::vector<double>  *fit_minus_x0_z;
   std::vector<double>  *fit_plus_ssd_mom_lx;
   std::vector<double>  *fit_plus_ssd_mom_ly;
   std::vector<double>  *fit_plus_ssd_mom_lz;
   std::vector<double>  *fit_plus_ssd_mom_gx;
   std::vector<double>  *fit_plus_ssd_mom_gy;
   std::vector<double>  *fit_plus_ssd_mom_gz;
   std::vector<double>  *fit_plus_gtr100_mom_lx;
   std::vector<double>  *fit_plus_gtr100_mom_ly;
   std::vector<double>  *fit_plus_gtr100_mom_lz;
   std::vector<double>  *fit_plus_gtr100_mom_gx;
   std::vector<double>  *fit_plus_gtr100_mom_gy;
   std::vector<double>  *fit_plus_gtr100_mom_gz;
   std::vector<double>  *fit_plus_gtr200_mom_lx;
   std::vector<double>  *fit_plus_gtr200_mom_ly;
   std::vector<double>  *fit_plus_gtr200_mom_lz;
   std::vector<double>  *fit_plus_gtr200_mom_gx;
   std::vector<double>  *fit_plus_gtr200_mom_gy;
   std::vector<double>  *fit_plus_gtr200_mom_gz;
   std::vector<double>  *fit_plus_gtr300_mom_lx;
   std::vector<double>  *fit_plus_gtr300_mom_ly;
   std::vector<double>  *fit_plus_gtr300_mom_lz;
   std::vector<double>  *fit_plus_gtr300_mom_gx;
   std::vector<double>  *fit_plus_gtr300_mom_gy;
   std::vector<double>  *fit_plus_gtr300_mom_gz;
   std::vector<double>  *fit_plus_hbd_mom_lx;
   std::vector<double>  *fit_plus_hbd_mom_ly;
   std::vector<double>  *fit_plus_hbd_mom_lz;
   std::vector<double>  *fit_plus_hbd_mom_gx;
   std::vector<double>  *fit_plus_hbd_mom_gy;
   std::vector<double>  *fit_plus_hbd_mom_gz;
   std::vector<double>  *fit_plus_lg_c_mom_lx;
   std::vector<double>  *fit_plus_lg_c_mom_ly;
   std::vector<double>  *fit_plus_lg_c_mom_lz;
   std::vector<double>  *fit_plus_lg_c_mom_gx;
   std::vector<double>  *fit_plus_lg_c_mom_gy;
   std::vector<double>  *fit_plus_lg_c_mom_gz;
   std::vector<double>  *fit_plus_lg_b_mom_lx;
   std::vector<double>  *fit_plus_lg_b_mom_ly;
   std::vector<double>  *fit_plus_lg_b_mom_lz;
   std::vector<double>  *fit_plus_lg_b_mom_gx;
   std::vector<double>  *fit_plus_lg_b_mom_gy;
   std::vector<double>  *fit_plus_lg_b_mom_gz;
   std::vector<double>  *fit_plus_lg_a_mom_lx;
   std::vector<double>  *fit_plus_lg_a_mom_ly;
   std::vector<double>  *fit_plus_lg_a_mom_lz;
   std::vector<double>  *fit_plus_lg_a_mom_gx;
   std::vector<double>  *fit_plus_lg_a_mom_gy;
   std::vector<double>  *fit_plus_lg_a_mom_gz;
   std::vector<double>  *fit_plus_tgt_minus_mom_x;
   std::vector<double>  *fit_plus_tgt_minus_mom_y;
   std::vector<double>  *fit_plus_tgt_minus_mom_z;
   std::vector<double>  *fit_plus_tgt_zero_mom_x;
   std::vector<double>  *fit_plus_tgt_zero_mom_y;
   std::vector<double>  *fit_plus_tgt_zero_mom_z;
   std::vector<double>  *fit_plus_tgt_plus_mom_x;
   std::vector<double>  *fit_plus_tgt_plus_mom_y;
   std::vector<double>  *fit_plus_tgt_plus_mom_z;
   std::vector<double>  *fit_minus_ssd_mom_lx;
   std::vector<double>  *fit_minus_ssd_mom_ly;
   std::vector<double>  *fit_minus_ssd_mom_lz;
   std::vector<double>  *fit_minus_ssd_mom_gx;
   std::vector<double>  *fit_minus_ssd_mom_gy;
   std::vector<double>  *fit_minus_ssd_mom_gz;
   std::vector<double>  *fit_minus_gtr100_mom_lx;
   std::vector<double>  *fit_minus_gtr100_mom_ly;
   std::vector<double>  *fit_minus_gtr100_mom_lz;
   std::vector<double>  *fit_minus_gtr100_mom_gx;
   std::vector<double>  *fit_minus_gtr100_mom_gy;
   std::vector<double>  *fit_minus_gtr100_mom_gz;
   std::vector<double>  *fit_minus_gtr200_mom_lx;
   std::vector<double>  *fit_minus_gtr200_mom_ly;
   std::vector<double>  *fit_minus_gtr200_mom_lz;
   std::vector<double>  *fit_minus_gtr200_mom_gx;
   std::vector<double>  *fit_minus_gtr200_mom_gy;
   std::vector<double>  *fit_minus_gtr200_mom_gz;
   std::vector<double>  *fit_minus_gtr300_mom_lx;
   std::vector<double>  *fit_minus_gtr300_mom_ly;
   std::vector<double>  *fit_minus_gtr300_mom_lz;
   std::vector<double>  *fit_minus_gtr300_mom_gx;
   std::vector<double>  *fit_minus_gtr300_mom_gy;
   std::vector<double>  *fit_minus_gtr300_mom_gz;
   std::vector<double>  *fit_minus_hbd_mom_lx;
   std::vector<double>  *fit_minus_hbd_mom_ly;
   std::vector<double>  *fit_minus_hbd_mom_lz;
   std::vector<double>  *fit_minus_hbd_mom_gx;
   std::vector<double>  *fit_minus_hbd_mom_gy;
   std::vector<double>  *fit_minus_hbd_mom_gz;
   std::vector<double>  *fit_minus_lg_c_mom_lx;
   std::vector<double>  *fit_minus_lg_c_mom_ly;
   std::vector<double>  *fit_minus_lg_c_mom_lz;
   std::vector<double>  *fit_minus_lg_c_mom_gx;
   std::vector<double>  *fit_minus_lg_c_mom_gy;
   std::vector<double>  *fit_minus_lg_c_mom_gz;
   std::vector<double>  *fit_minus_lg_b_mom_lx;
   std::vector<double>  *fit_minus_lg_b_mom_ly;
   std::vector<double>  *fit_minus_lg_b_mom_lz;
   std::vector<double>  *fit_minus_lg_b_mom_gx;
   std::vector<double>  *fit_minus_lg_b_mom_gy;
   std::vector<double>  *fit_minus_lg_b_mom_gz;
   std::vector<double>  *fit_minus_lg_a_mom_lx;
   std::vector<double>  *fit_minus_lg_a_mom_ly;
   std::vector<double>  *fit_minus_lg_a_mom_lz;
   std::vector<double>  *fit_minus_lg_a_mom_gx;
   std::vector<double>  *fit_minus_lg_a_mom_gy;
   std::vector<double>  *fit_minus_lg_a_mom_gz;
   std::vector<double>  *fit_minus_tgt_minus_mom_x;
   std::vector<double>  *fit_minus_tgt_minus_mom_y;
   std::vector<double>  *fit_minus_tgt_minus_mom_z;
   std::vector<double>  *fit_minus_tgt_zero_mom_x;
   std::vector<double>  *fit_minus_tgt_zero_mom_y;
   std::vector<double>  *fit_minus_tgt_zero_mom_z;
   std::vector<double>  *fit_minus_tgt_plus_mom_x;
   std::vector<double>  *fit_minus_tgt_plus_mom_y;
   std::vector<double>  *fit_minus_tgt_plus_mom_z;
   std::vector<double>  *res_plus_ssd_lx;
   std::vector<double>  *res_plus_gtr100_lx;
   std::vector<double>  *res_plus_gtr100_ly;
   std::vector<double>  *res_plus_gtr200_lx;
   std::vector<double>  *res_plus_gtr200_ly;
   std::vector<double>  *res_plus_gtr300_lx;
   std::vector<double>  *res_plus_gtr300_ly;
   std::vector<double>  *res_minus_ssd_lx;
   std::vector<double>  *res_minus_gtr100_lx;
   std::vector<double>  *res_minus_gtr100_ly;
   std::vector<double>  *res_minus_gtr200_lx;
   std::vector<double>  *res_minus_gtr200_ly;
   std::vector<double>  *res_minus_gtr300_lx;
   std::vector<double>  *res_minus_gtr300_ly;
   std::vector<double>  *fit_parent_mom;
   std::vector<double>  *fit_parent_mom_x;
   std::vector<double>  *fit_parent_mom_y;
   std::vector<double>  *fit_parent_mom_z;
   std::vector<double>  *fit_parent_mom_theta;
   std::vector<double>  *fit_parent_mom_phi;
   std::vector<double>  *fit_parent_tgt_minus_x;
   std::vector<double>  *fit_parent_tgt_minus_y;
   std::vector<double>  *fit_parent_tgt_minus_flight_path;
   std::vector<double>  *fit_parent_tgt_zero_x;
   std::vector<double>  *fit_parent_tgt_zero_y;
   std::vector<double>  *fit_parent_tgt_zero_flight_path;
   std::vector<double>  *fit_parent_tgt_plus_x;
   std::vector<double>  *fit_parent_tgt_plus_y;
   std::vector<double>  *fit_parent_tgt_plus_flight_path;
   std::vector<int>     *fit_parent_best_tgt_id;
   std::vector<double>  *fit_parent_best_tgt_r;
   std::vector<int>     *fit_parent_good_tgt_id_set;
   std::vector<std::vector<double> > *fit_parent_good_tgt_ids;
   std::vector<double>  *fit_parent_x0_y;
   std::vector<double>  *fit_parent_x0_z;
   std::vector<double>  *proj_plus_n_hbds;
   std::vector<double>  *proj_plus_hbd_min_res;
   std::vector<std::vector<double> > *proj_plus_hbd_id;
   std::vector<std::vector<double> > *proj_plus_hbd_lx;
   std::vector<std::vector<double> > *proj_plus_hbd_ly;
   std::vector<std::vector<double> > *proj_plus_hbd_resx;
   std::vector<std::vector<double> > *proj_plus_hbd_resy;
   std::vector<std::vector<double> > *proj_plus_hbd_adc;
   std::vector<std::vector<double> > *proj_plus_hbd_size;
   std::vector<std::vector<double> > *proj_plus_hbd_eprob;



   std::vector<double>  *proj_minus_n_hbds;
   std::vector<double>  *proj_minus_hbd_min_res;
   std::vector<std::vector<double> > *proj_minus_hbd_id;
   std::vector<std::vector<double> > *proj_minus_hbd_lx;
   std::vector<std::vector<double> > *proj_minus_hbd_ly;
   std::vector<std::vector<double> > *proj_minus_hbd_resx;
   std::vector<std::vector<double> > *proj_minus_hbd_resy;
   std::vector<std::vector<double> > *proj_minus_hbd_adc;
   std::vector<std::vector<double> > *proj_minus_hbd_size;
   std::vector<std::vector<double> > *proj_minus_hbd_eprob;

   std::vector<std::vector<double>> *proj_plus_n_lgs;
   std::vector<std::vector<double>> *proj_plus_lg_id;
   std::vector<std::vector<double>> *proj_plus_lg_lx;
   std::vector<std::vector<double>> *proj_plus_lg_ly;
   std::vector<std::vector<double>> *proj_plus_lg_resx;
   std::vector<std::vector<double>> *proj_plus_lg_resy;
   std::vector<std::vector<double>> *proj_plus_lg_adc;

   std::vector<std::vector<double>> *proj_minus_n_lgs;
   std::vector<std::vector<double>> *proj_minus_lg_id;
   std::vector<std::vector<double>> *proj_minus_lg_lx;
   std::vector<std::vector<double>> *proj_minus_lg_ly;
   std::vector<std::vector<double>> *proj_minus_lg_resx;
   std::vector<std::vector<double>> *proj_minus_lg_resy;
   std::vector<std::vector<double>> *proj_minus_lg_adc;




   std::vector<int>     *tmp_fit_plus_x0_flag;
   std::vector<int>     *tmp_fit_plus_x0_n_cross;
   std::vector<std::vector<double> > *tmp_fit_plus_x0_pos_y;
   std::vector<std::vector<double> > *tmp_fit_plus_x0_pos_z;
   std::vector<std::vector<double> > *tmp_fit_plus_x0_mom_x;
   std::vector<std::vector<double> > *tmp_fit_plus_x0_mom_y;
   std::vector<std::vector<double> > *tmp_fit_plus_x0_mom_z;
   std::vector<int>     *tmp_fit_minus_x0_flag;
   std::vector<int>     *tmp_fit_minus_x0_n_cross;
   std::vector<std::vector<double> > *tmp_fit_minus_x0_pos_y;
   std::vector<std::vector<double> > *tmp_fit_minus_x0_pos_z;
   std::vector<std::vector<double> > *tmp_fit_minus_x0_mom_x;
   std::vector<std::vector<double> > *tmp_fit_minus_x0_mom_y;
   std::vector<std::vector<double> > *tmp_fit_minus_x0_mom_z;

   // List of branches
   TBranch        *b_run_id;   //!
   TBranch        *b_event_id;   //!
   TBranch        *b_n_cands;   //!
   TBranch        *b_n_ssd_clusters;   //!
   TBranch        *b_n_gtr100x_clusters;   //!
   TBranch        *b_n_gtr100y_clusters;   //!
   TBranch        *b_n_gtr200x_clusters;   //!
   TBranch        *b_n_gtr200y_clusters;   //!
   TBranch        *b_n_gtr300x_clusters;   //!
   TBranch        *b_n_gtr300y_clusters;   //!
   TBranch        *b_n_hbd_clusters;   //!
   TBranch        *b_n_lg_hits;   //!
   TBranch        *b_n_trg_gtr_hits;   //!
   TBranch        *b_trg_gtr_hit_id;   //!
   TBranch        *b_trg_gtr_hit_mid;   //!
   TBranch        *b_trg_gtr_hit_cid;   //!
   TBranch        *b_trg_gtr_hit_x;   //!
   TBranch        *b_trg_gtr_hit_y;   //!
   TBranch        *b_trg_gtr_hit_gx;   //!
   TBranch        *b_trg_gtr_hit_gy;   //!
   TBranch        *b_trg_gtr_hit_gz;   //!
   TBranch        *b_trg_gtr_hit_t;   //!
   TBranch        *b_n_trg_hbd_hits;   //!
   TBranch        *b_trg_hbd_hit_id;   //!
   TBranch        *b_trg_hbd_hit_mid;   //!
   TBranch        *b_trg_hbd_hit_cid;   //!
   TBranch        *b_trg_hbd_hit_x;   //!
   TBranch        *b_trg_hbd_hit_y;   //!
   TBranch        *b_trg_hbd_hit_gx;   //!
   TBranch        *b_trg_hbd_hit_gy;   //!
   TBranch        *b_trg_hbd_hit_gz;   //!
   TBranch        *b_trg_hbd_hit_t;   //!
   TBranch        *b_n_trg_lg_hits;   //!
   TBranch        *b_trg_lg_hit_id;   //!
   TBranch        *b_trg_lg_hit_mid;   //!
   TBranch        *b_trg_lg_hit_cid;   //!
   TBranch        *b_trg_lg_hit_x;   //!
   TBranch        *b_trg_lg_hit_y;   //!
   TBranch        *b_trg_lg_hit_gx;   //!
   TBranch        *b_trg_lg_hit_gy;   //!
   TBranch        *b_trg_lg_hit_gz;   //!
   TBranch        *b_trg_lg_hit_t;   //!
   TBranch        *b_n_tracks;   //!
   TBranch        *b_n_pairs;   //!
   TBranch        *b_pair_order;   //!
   TBranch        *b_plus_rough_fit_init_pos_x;   //!
   TBranch        *b_plus_rough_fit_init_pos_y;   //!
   TBranch        *b_plus_rough_fit_init_pos_z;   //!
   TBranch        *b_plus_rough_fit_init_mom_x;   //!
   TBranch        *b_plus_rough_fit_init_mom_y;   //!
   TBranch        *b_plus_rough_fit_init_mom_z;   //!
   TBranch        *b_minus_rough_fit_init_pos_x;   //!
   TBranch        *b_minus_rough_fit_init_pos_y;   //!
   TBranch        *b_minus_rough_fit_init_pos_z;   //!
   TBranch        *b_minus_rough_fit_init_mom_x;   //!
   TBranch        *b_minus_rough_fit_init_mom_y;   //!
   TBranch        *b_minus_rough_fit_init_mom_z;   //!
   TBranch        *b_plus_single_fit_init_pos_x;   //!
   TBranch        *b_plus_single_fit_init_pos_y;   //!
   TBranch        *b_plus_single_fit_init_pos_z;   //!
   TBranch        *b_plus_single_fit_init_mom_x;   //!
   TBranch        *b_plus_single_fit_init_mom_y;   //!
   TBranch        *b_plus_single_fit_init_mom_z;   //!
   TBranch        *b_minus_single_fit_init_pos_x;   //!
   TBranch        *b_minus_single_fit_init_pos_y;   //!
   TBranch        *b_minus_single_fit_init_pos_z;   //!
   TBranch        *b_minus_single_fit_init_mom_x;   //!
   TBranch        *b_minus_single_fit_init_mom_y;   //!
   TBranch        *b_minus_single_fit_init_mom_z;   //!
   TBranch        *b_plus_track_id;   //!
   TBranch        *b_plus_charge_id;   //!
   TBranch        *b_hit_plus_ssd_id;   //!
   TBranch        *b_hit_plus_ssd_lx;   //!
   TBranch        *b_hit_plus_ssd_t;   //!
   TBranch        *b_hit_plus_ssd_adc;   //!
   TBranch        *b_hit_plus_ssd_size;   //!
   TBranch        *b_hit_plus_gtr100_xid;   //!
   TBranch        *b_hit_plus_gtr100_yid;   //!
   TBranch        *b_hit_plus_gtr100_lx;   //!
   TBranch        *b_hit_plus_gtr100_ly;   //!
   TBranch        *b_hit_plus_gtr100_xt;   //!
   TBranch        *b_hit_plus_gtr100_yt;   //!
   TBranch        *b_hit_plus_gtr100_xadc;   //!
   TBranch        *b_hit_plus_gtr100_yadc;   //!
   TBranch        *b_hit_plus_gtr100_xsize;   //!
   TBranch        *b_hit_plus_gtr100_ysize;   //!
   TBranch        *b_hit_plus_gtr200_xid;   //!
   TBranch        *b_hit_plus_gtr200_yid;   //!
   TBranch        *b_hit_plus_gtr200_lx;   //!
   TBranch        *b_hit_plus_gtr200_ly;   //!
   TBranch        *b_hit_plus_gtr200_xt;   //!
   TBranch        *b_hit_plus_gtr200_yt;   //!
   TBranch        *b_hit_plus_gtr200_xadc;   //!
   TBranch        *b_hit_plus_gtr200_yadc;   //!
   TBranch        *b_hit_plus_gtr200_xsize;   //!
   TBranch        *b_hit_plus_gtr200_ysize;   //!
   TBranch        *b_hit_plus_gtr300_xid;   //!
   TBranch        *b_hit_plus_gtr300_yid;   //!
   TBranch        *b_hit_plus_gtr300_lx;   //!
   TBranch        *b_hit_plus_gtr300_ly;   //!
   TBranch        *b_hit_plus_gtr300_xt;   //!
   TBranch        *b_hit_plus_gtr300_yt;   //!
   TBranch        *b_hit_plus_gtr300_xadc;   //!
   TBranch        *b_hit_plus_gtr300_yadc;   //!
   TBranch        *b_hit_plus_gtr300_xsize;   //!
   TBranch        *b_hit_plus_gtr300_ysize;   //!
   TBranch        *b_minus_track_id;   //!
   TBranch        *b_minus_charge_id;   //!
   TBranch        *b_hit_minus_ssd_id;   //!
   TBranch        *b_hit_minus_ssd_lx;   //!
   TBranch        *b_hit_minus_ssd_t;   //!
   TBranch        *b_hit_minus_ssd_adc;   //!
   TBranch        *b_hit_minus_ssd_size;   //!
   TBranch        *b_hit_minus_gtr100_xid;   //!
   TBranch        *b_hit_minus_gtr100_yid;   //!
   TBranch        *b_hit_minus_gtr100_lx;   //!
   TBranch        *b_hit_minus_gtr100_ly;   //!
   TBranch        *b_hit_minus_gtr100_xt;   //!
   TBranch        *b_hit_minus_gtr100_yt;   //!
   TBranch        *b_hit_minus_gtr100_xadc;   //!
   TBranch        *b_hit_minus_gtr100_yadc;   //!
   TBranch        *b_hit_minus_gtr100_xsize;   //!
   TBranch        *b_hit_minus_gtr100_ysize;   //!
   TBranch        *b_hit_minus_gtr200_xid;   //!
   TBranch        *b_hit_minus_gtr200_yid;   //!
   TBranch        *b_hit_minus_gtr200_lx;   //!
   TBranch        *b_hit_minus_gtr200_ly;   //!
   TBranch        *b_hit_minus_gtr200_xt;   //!
   TBranch        *b_hit_minus_gtr200_yt;   //!
   TBranch        *b_hit_minus_gtr200_xadc;   //!
   TBranch        *b_hit_minus_gtr200_yadc;   //!
   TBranch        *b_hit_minus_gtr200_xsize;   //!
   TBranch        *b_hit_minus_gtr200_ysize;   //!
   TBranch        *b_hit_minus_gtr300_xid;   //!
   TBranch        *b_hit_minus_gtr300_yid;   //!
   TBranch        *b_hit_minus_gtr300_lx;   //!
   TBranch        *b_hit_minus_gtr300_ly;   //!
   TBranch        *b_hit_minus_gtr300_xt;   //!
   TBranch        *b_hit_minus_gtr300_yt;   //!
   TBranch        *b_hit_minus_gtr300_xadc;   //!
   TBranch        *b_hit_minus_gtr300_yadc;   //!
   TBranch        *b_hit_minus_gtr300_xsize;   //!
   TBranch        *b_hit_minus_gtr300_ysize;   //!
   TBranch        *b_chi2;   //!
   TBranch        *b_plus_chi2;   //!
   TBranch        *b_minus_chi2;   //!
   TBranch        *b_flag;   //!
   TBranch        *b_distance;   //!
   TBranch        *b_plus_nearest_tgt_id;   //!
   TBranch        *b_plus_nearest_radius;   //!
   TBranch        *b_minus_nearest_tgt_id;   //!
   TBranch        *b_minus_nearest_radius;   //!
   TBranch        *b_dir_id;   //!
   TBranch        *b_vtx_x;   //!
   TBranch        *b_vtx_y;   //!
   TBranch        *b_vtx_z;   //!
   TBranch        *b_plus_pos_x;   //!
   TBranch        *b_plus_pos_y;   //!
   TBranch        *b_plus_pos_z;   //!
   TBranch        *b_minus_pos_x;   //!
   TBranch        *b_minus_pos_y;   //!
   TBranch        *b_minus_pos_z;   //!
   TBranch        *b_plus_mom;   //!
   TBranch        *b_plus_mom_x;   //!
   TBranch        *b_plus_mom_y;   //!
   TBranch        *b_plus_mom_z;   //!
   TBranch        *b_plus_mom_theta;   //!
   TBranch        *b_plus_mom_phi;   //!
   TBranch        *b_minus_mom;   //!
   TBranch        *b_minus_mom_x;   //!
   TBranch        *b_minus_mom_y;   //!
   TBranch        *b_minus_mom_z;   //!
   TBranch        *b_minus_mom_theta;   //!
   TBranch        *b_minus_mom_phi;   //!
   TBranch        *b_mom_angle;   //!
   TBranch        *b_ee_mass;   //!
   TBranch        *b_pipi_mass;   //!
   TBranch        *b_pip_mass;   //!
   TBranch        *b_kk_mass;   //!
   TBranch        *b_simple_best_tgt_id;   //!
   TBranch        *b_simple_best_tgt_r;   //!
   TBranch        *b_ee_mass_at_best_tgt;   //!
   TBranch        *b_pipi_mass_at_best_tgt;   //!
   TBranch        *b_pip_mass_at_best_tgt;   //!
   TBranch        *b_kk_mass_at_best_tgt;   //!
   TBranch        *b_plus_ssd_mid;   //!
   TBranch        *b_plus_gtr100_mid;   //!
   TBranch        *b_plus_gtr200_mid;   //!
   TBranch        *b_plus_gtr300_mid;   //!
   TBranch        *b_plus_hbd_mid;   //!
   TBranch        *b_plus_lg_c_mid;   //!
   TBranch        *b_plus_lg_b_mid;   //!
   TBranch        *b_plus_lg_a_mid;   //!
   TBranch        *b_minus_ssd_mid;   //!
   TBranch        *b_minus_gtr100_mid;   //!
   TBranch        *b_minus_gtr200_mid;   //!
   TBranch        *b_minus_gtr300_mid;   //!
   TBranch        *b_minus_hbd_mid;   //!
   TBranch        *b_minus_lg_c_mid;   //!
   TBranch        *b_minus_lg_b_mid;   //!
   TBranch        *b_minus_lg_a_mid;   //!
   TBranch        *b_fit_plus_ssd_lx;   //!
   TBranch        *b_fit_plus_ssd_ly;   //!
   TBranch        *b_fit_plus_gtr100_lx;   //!
   TBranch        *b_fit_plus_gtr100_ly;   //!
   TBranch        *b_fit_plus_gtr200_lx;   //!
   TBranch        *b_fit_plus_gtr200_ly;   //!
   TBranch        *b_fit_plus_gtr300_lx;   //!
   TBranch        *b_fit_plus_gtr300_ly;   //!
   TBranch        *b_fit_plus_hbd_lx;   //!
   TBranch        *b_fit_plus_hbd_ly;   //!
   TBranch        *b_fit_plus_lg_c_lx;   //!
   TBranch        *b_fit_plus_lg_c_ly;   //!
   TBranch        *b_fit_plus_lg_b_lx;   //!
   TBranch        *b_fit_plus_lg_b_ly;   //!
   TBranch        *b_fit_plus_lg_a_lx;   //!
   TBranch        *b_fit_plus_lg_a_ly;   //!
   TBranch        *b_fit_plus_tgt_minus_x;   //!
   TBranch        *b_fit_plus_tgt_minus_y;   //!
   TBranch        *b_fit_plus_tgt_zero_x;   //!
   TBranch        *b_fit_plus_tgt_zero_y;   //!
   TBranch        *b_fit_plus_tgt_plus_x;   //!
   TBranch        *b_fit_plus_tgt_plus_y;   //!
   TBranch        *b_fit_plus_x0_y;   //!
   TBranch        *b_fit_plus_x0_z;   //!
   TBranch        *b_fit_minus_ssd_lx;   //!
   TBranch        *b_fit_minus_ssd_ly;   //!
   TBranch        *b_fit_minus_gtr100_lx;   //!
   TBranch        *b_fit_minus_gtr100_ly;   //!
   TBranch        *b_fit_minus_gtr200_lx;   //!
   TBranch        *b_fit_minus_gtr200_ly;   //!
   TBranch        *b_fit_minus_gtr300_lx;   //!
   TBranch        *b_fit_minus_gtr300_ly;   //!
   TBranch        *b_fit_minus_hbd_lx;   //!
   TBranch        *b_fit_minus_hbd_ly;   //!
   TBranch        *b_fit_minus_lg_c_lx;   //!
   TBranch        *b_fit_minus_lg_c_ly;   //!
   TBranch        *b_fit_minus_lg_b_lx;   //!
   TBranch        *b_fit_minus_lg_b_ly;   //!
   TBranch        *b_fit_minus_lg_a_lx;   //!
   TBranch        *b_fit_minus_lg_a_ly;   //!
   TBranch        *b_fit_minus_tgt_minus_x;   //!
   TBranch        *b_fit_minus_tgt_minus_y;   //!
   TBranch        *b_fit_minus_tgt_zero_x;   //!
   TBranch        *b_fit_minus_tgt_zero_y;   //!
   TBranch        *b_fit_minus_tgt_plus_x;   //!
   TBranch        *b_fit_minus_tgt_plus_y;   //!
   TBranch        *b_fit_minus_x0_y;   //!
   TBranch        *b_fit_minus_x0_z;   //!
   TBranch        *b_fit_plus_ssd_mom_lx;   //!
   TBranch        *b_fit_plus_ssd_mom_ly;   //!
   TBranch        *b_fit_plus_ssd_mom_lz;   //!
   TBranch        *b_fit_plus_ssd_mom_gx;   //!
   TBranch        *b_fit_plus_ssd_mom_gy;   //!
   TBranch        *b_fit_plus_ssd_mom_gz;   //!
   TBranch        *b_fit_plus_gtr100_mom_lx;   //!
   TBranch        *b_fit_plus_gtr100_mom_ly;   //!
   TBranch        *b_fit_plus_gtr100_mom_lz;   //!
   TBranch        *b_fit_plus_gtr100_mom_gx;   //!
   TBranch        *b_fit_plus_gtr100_mom_gy;   //!
   TBranch        *b_fit_plus_gtr100_mom_gz;   //!
   TBranch        *b_fit_plus_gtr200_mom_lx;   //!
   TBranch        *b_fit_plus_gtr200_mom_ly;   //!
   TBranch        *b_fit_plus_gtr200_mom_lz;   //!
   TBranch        *b_fit_plus_gtr200_mom_gx;   //!
   TBranch        *b_fit_plus_gtr200_mom_gy;   //!
   TBranch        *b_fit_plus_gtr200_mom_gz;   //!
   TBranch        *b_fit_plus_gtr300_mom_lx;   //!
   TBranch        *b_fit_plus_gtr300_mom_ly;   //!
   TBranch        *b_fit_plus_gtr300_mom_lz;   //!
   TBranch        *b_fit_plus_gtr300_mom_gx;   //!
   TBranch        *b_fit_plus_gtr300_mom_gy;   //!
   TBranch        *b_fit_plus_gtr300_mom_gz;   //!
   TBranch        *b_fit_plus_hbd_mom_lx;   //!
   TBranch        *b_fit_plus_hbd_mom_ly;   //!
   TBranch        *b_fit_plus_hbd_mom_lz;   //!
   TBranch        *b_fit_plus_hbd_mom_gx;   //!
   TBranch        *b_fit_plus_hbd_mom_gy;   //!
   TBranch        *b_fit_plus_hbd_mom_gz;   //!
   TBranch        *b_fit_plus_lg_c_mom_lx;   //!
   TBranch        *b_fit_plus_lg_c_mom_ly;   //!
   TBranch        *b_fit_plus_lg_c_mom_lz;   //!
   TBranch        *b_fit_plus_lg_c_mom_gx;   //!
   TBranch        *b_fit_plus_lg_c_mom_gy;   //!
   TBranch        *b_fit_plus_lg_c_mom_gz;   //!
   TBranch        *b_fit_plus_lg_b_mom_lx;   //!
   TBranch        *b_fit_plus_lg_b_mom_ly;   //!
   TBranch        *b_fit_plus_lg_b_mom_lz;   //!
   TBranch        *b_fit_plus_lg_b_mom_gx;   //!
   TBranch        *b_fit_plus_lg_b_mom_gy;   //!
   TBranch        *b_fit_plus_lg_b_mom_gz;   //!
   TBranch        *b_fit_plus_lg_a_mom_lx;   //!
   TBranch        *b_fit_plus_lg_a_mom_ly;   //!
   TBranch        *b_fit_plus_lg_a_mom_lz;   //!
   TBranch        *b_fit_plus_lg_a_mom_gx;   //!
   TBranch        *b_fit_plus_lg_a_mom_gy;   //!
   TBranch        *b_fit_plus_lg_a_mom_gz;   //!
   TBranch        *b_fit_plus_tgt_minus_mom_x;   //!
   TBranch        *b_fit_plus_tgt_minus_mom_y;   //!
   TBranch        *b_fit_plus_tgt_minus_mom_z;   //!
   TBranch        *b_fit_plus_tgt_zero_mom_x;   //!
   TBranch        *b_fit_plus_tgt_zero_mom_y;   //!
   TBranch        *b_fit_plus_tgt_zero_mom_z;   //!
   TBranch        *b_fit_plus_tgt_plus_mom_x;   //!
   TBranch        *b_fit_plus_tgt_plus_mom_y;   //!
   TBranch        *b_fit_plus_tgt_plus_mom_z;   //!
   TBranch        *b_fit_minus_ssd_mom_lx;   //!
   TBranch        *b_fit_minus_ssd_mom_ly;   //!
   TBranch        *b_fit_minus_ssd_mom_lz;   //!
   TBranch        *b_fit_minus_ssd_mom_gx;   //!
   TBranch        *b_fit_minus_ssd_mom_gy;   //!
   TBranch        *b_fit_minus_ssd_mom_gz;   //!
   TBranch        *b_fit_minus_gtr100_mom_lx;   //!
   TBranch        *b_fit_minus_gtr100_mom_ly;   //!
   TBranch        *b_fit_minus_gtr100_mom_lz;   //!
   TBranch        *b_fit_minus_gtr100_mom_gx;   //!
   TBranch        *b_fit_minus_gtr100_mom_gy;   //!
   TBranch        *b_fit_minus_gtr100_mom_gz;   //!
   TBranch        *b_fit_minus_gtr200_mom_lx;   //!
   TBranch        *b_fit_minus_gtr200_mom_ly;   //!
   TBranch        *b_fit_minus_gtr200_mom_lz;   //!
   TBranch        *b_fit_minus_gtr200_mom_gx;   //!
   TBranch        *b_fit_minus_gtr200_mom_gy;   //!
   TBranch        *b_fit_minus_gtr200_mom_gz;   //!
   TBranch        *b_fit_minus_gtr300_mom_lx;   //!
   TBranch        *b_fit_minus_gtr300_mom_ly;   //!
   TBranch        *b_fit_minus_gtr300_mom_lz;   //!
   TBranch        *b_fit_minus_gtr300_mom_gx;   //!
   TBranch        *b_fit_minus_gtr300_mom_gy;   //!
   TBranch        *b_fit_minus_gtr300_mom_gz;   //!
   TBranch        *b_fit_minus_hbd_mom_lx;   //!
   TBranch        *b_fit_minus_hbd_mom_ly;   //!
   TBranch        *b_fit_minus_hbd_mom_lz;   //!
   TBranch        *b_fit_minus_hbd_mom_gx;   //!
   TBranch        *b_fit_minus_hbd_mom_gy;   //!
   TBranch        *b_fit_minus_hbd_mom_gz;   //!
   TBranch        *b_fit_minus_lg_c_mom_lx;   //!
   TBranch        *b_fit_minus_lg_c_mom_ly;   //!
   TBranch        *b_fit_minus_lg_c_mom_lz;   //!
   TBranch        *b_fit_minus_lg_c_mom_gx;   //!
   TBranch        *b_fit_minus_lg_c_mom_gy;   //!
   TBranch        *b_fit_minus_lg_c_mom_gz;   //!
   TBranch        *b_fit_minus_lg_b_mom_lx;   //!
   TBranch        *b_fit_minus_lg_b_mom_ly;   //!
   TBranch        *b_fit_minus_lg_b_mom_lz;   //!
   TBranch        *b_fit_minus_lg_b_mom_gx;   //!
   TBranch        *b_fit_minus_lg_b_mom_gy;   //!
   TBranch        *b_fit_minus_lg_b_mom_gz;   //!
   TBranch        *b_fit_minus_lg_a_mom_lx;   //!
   TBranch        *b_fit_minus_lg_a_mom_ly;   //!
   TBranch        *b_fit_minus_lg_a_mom_lz;   //!
   TBranch        *b_fit_minus_lg_a_mom_gx;   //!
   TBranch        *b_fit_minus_lg_a_mom_gy;   //!
   TBranch        *b_fit_minus_lg_a_mom_gz;   //!
   TBranch        *b_fit_minus_tgt_minus_mom_x;   //!
   TBranch        *b_fit_minus_tgt_minus_mom_y;   //!
   TBranch        *b_fit_minus_tgt_minus_mom_z;   //!
   TBranch        *b_fit_minus_tgt_zero_mom_x;   //!
   TBranch        *b_fit_minus_tgt_zero_mom_y;   //!
   TBranch        *b_fit_minus_tgt_zero_mom_z;   //!
   TBranch        *b_fit_minus_tgt_plus_mom_x;   //!
   TBranch        *b_fit_minus_tgt_plus_mom_y;   //!
   TBranch        *b_fit_minus_tgt_plus_mom_z;   //!
   TBranch        *b_res_plus_ssd_lx;   //!
   TBranch        *b_res_plus_gtr100_lx;   //!
   TBranch        *b_res_plus_gtr100_ly;   //!
   TBranch        *b_res_plus_gtr200_lx;   //!
   TBranch        *b_res_plus_gtr200_ly;   //!
   TBranch        *b_res_plus_gtr300_lx;   //!
   TBranch        *b_res_plus_gtr300_ly;   //!
   TBranch        *b_res_minus_ssd_lx;   //!
   TBranch        *b_res_minus_gtr100_lx;   //!
   TBranch        *b_res_minus_gtr100_ly;   //!
   TBranch        *b_res_minus_gtr200_lx;   //!
   TBranch        *b_res_minus_gtr200_ly;   //!
   TBranch        *b_res_minus_gtr300_lx;   //!
   TBranch        *b_res_minus_gtr300_ly;   //!
   TBranch        *b_fit_parent_mom;   //!
   TBranch        *b_fit_parent_mom_x;   //!
   TBranch        *b_fit_parent_mom_y;   //!
   TBranch        *b_fit_parent_mom_z;   //!
   TBranch        *b_fit_parent_mom_theta;   //!
   TBranch        *b_fit_parent_mom_phi;   //!
   TBranch        *b_fit_parent_tgt_minus_x;   //!
   TBranch        *b_fit_parent_tgt_minus_y;   //!
   TBranch        *b_fit_parent_tgt_minus_flight_path;   //!
   TBranch        *b_fit_parent_tgt_zero_x;   //!
   TBranch        *b_fit_parent_tgt_zero_y;   //!
   TBranch        *b_fit_parent_tgt_zero_flight_path;   //!
   TBranch        *b_fit_parent_tgt_plus_x;   //!
   TBranch        *b_fit_parent_tgt_plus_y;   //!
   TBranch        *b_fit_parent_tgt_plus_flight_path;   //!
   TBranch        *b_fit_parent_best_tgt_id;   //!
   TBranch        *b_fit_parent_best_tgt_r;   //!
   TBranch        *b_fit_parent_good_tgt_id_set;   //!
   TBranch        *b_fit_parent_good_tgt_ids;   //!
   TBranch        *b_fit_parent_x0_y;   //!
   TBranch        *b_fit_parent_x0_z;   //!
   TBranch        *b_proj_plus_n_hbds;   //!
   TBranch        *b_proj_plus_hbd_min_res;   //!
   TBranch        *b_proj_plus_hbd_id;   //!
   TBranch        *b_proj_plus_hbd_lx;   //!
   TBranch        *b_proj_plus_hbd_ly;   //!
   TBranch        *b_proj_plus_hbd_resx;   //!
   TBranch        *b_proj_plus_hbd_resy;   //!
   TBranch        *b_proj_plus_hbd_adc;   //!
   TBranch        *b_proj_plus_hbd_size;   //!
   TBranch        *b_proj_plus_hbd_eprob;   //!
   TBranch        *b_proj_minus_n_hbds;   //!
   TBranch        *b_proj_minus_hbd_min_res;   //!
   TBranch        *b_proj_minus_hbd_id;   //!
   TBranch        *b_proj_minus_hbd_lx;   //!
   TBranch        *b_proj_minus_hbd_ly;   //!
   TBranch        *b_proj_minus_hbd_resx;   //!
   TBranch        *b_proj_minus_hbd_resy;   //!
   TBranch        *b_proj_minus_hbd_adc;   //!
   TBranch        *b_proj_minus_hbd_size;   //!
   TBranch        *b_proj_minus_hbd_eprob;   //


   TBranch *b_proj_plus_n_lgs;
   TBranch *b_proj_plus_lg_id;
   TBranch *b_proj_plus_lg_lx;
   TBranch *b_proj_plus_lg_ly;
   TBranch *b_proj_plus_lg_resx;
   TBranch *b_proj_plus_lg_resy;
   TBranch *b_proj_plus_lg_adc;
   TBranch *b_proj_minus_n_lgs;
   TBranch *b_proj_minus_lg_id;
   TBranch *b_proj_minus_lg_lx;
   TBranch *b_proj_minus_lg_ly;
   TBranch *b_proj_minus_lg_resx;
   TBranch *b_proj_minus_lg_resy;
   TBranch *b_proj_minus_lg_adc;





   TBranch        *b_tmp_fit_plus_x0_flag;   //!
   TBranch        *b_tmp_fit_plus_x0_n_cross;   //!
   TBranch        *b_tmp_fit_plus_x0_pos_y;   //!
   TBranch        *b_tmp_fit_plus_x0_pos_z;   //!
   TBranch        *b_tmp_fit_plus_x0_mom_x;   //!
   TBranch        *b_tmp_fit_plus_x0_mom_y;   //!
   TBranch        *b_tmp_fit_plus_x0_mom_z;   //!
   TBranch        *b_tmp_fit_minus_x0_flag;   //!
   TBranch        *b_tmp_fit_minus_x0_n_cross;   //!
   TBranch        *b_tmp_fit_minus_x0_pos_y;   //!
   TBranch        *b_tmp_fit_minus_x0_pos_z;   //!
   TBranch        *b_tmp_fit_minus_x0_mom_x;   //!
   TBranch        *b_tmp_fit_minus_x0_mom_y;   //!
   TBranch        *b_tmp_fit_minus_x0_mom_z;   //!

   E16DSTN_AfterTrackAna(TTree *tree=0, const char *outfile=0);
   virtual ~E16DSTN_AfterTrackAna();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree, const char *outfile);
//   virtual void     Loop();
   void     DrawHist(TTree* tree, int p, int s, int e, TString pdf);
	bool IsSameArm(int mm , int pm );
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef E16DSTN_AfterTrackAna_cxx
E16DSTN_AfterTrackAna::E16DSTN_AfterTrackAna(TTree *tree, const char *outfile) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("RootFileCannotbeFound");
      if (!f || !f->IsOpen()) {
//         f = new TFile("root/out-run030737_sink0_000-event-0-999.root");
      }
      f->GetObject("tree",tree);
   }
   Init(tree, outfile);
}

E16DSTN_AfterTrackAna::~E16DSTN_AfterTrackAna()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t E16DSTN_AfterTrackAna::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t E16DSTN_AfterTrackAna::LoadTree(Long64_t entry)
{
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

void E16DSTN_AfterTrackAna::Init(TTree *tree, const char* outfile)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   trg_gtr_hit_id = 0;
   trg_gtr_hit_mid = 0;
   trg_gtr_hit_cid = 0;
   trg_gtr_hit_x = 0;
   trg_gtr_hit_y = 0;
   trg_gtr_hit_gx = 0;
   trg_gtr_hit_gy = 0;
   trg_gtr_hit_gz = 0;
   trg_gtr_hit_t = 0;
   trg_hbd_hit_id = 0;
   trg_hbd_hit_mid = 0;
   trg_hbd_hit_cid = 0;
   trg_hbd_hit_x = 0;
   trg_hbd_hit_y = 0;
   trg_hbd_hit_gx = 0;
   trg_hbd_hit_gy = 0;
   trg_hbd_hit_gz = 0;
   trg_hbd_hit_t = 0;
   trg_lg_hit_id = 0;
   trg_lg_hit_mid = 0;
   trg_lg_hit_cid = 0;
   trg_lg_hit_x = 0;
   trg_lg_hit_y = 0;
   trg_lg_hit_gx = 0;
   trg_lg_hit_gy = 0;
   trg_lg_hit_gz = 0;
   trg_lg_hit_t = 0;
   pair_order = 0;
   plus_rough_fit_init_pos_x = 0;
   plus_rough_fit_init_pos_y = 0;
   plus_rough_fit_init_pos_z = 0;
   plus_rough_fit_init_mom_x = 0;
   plus_rough_fit_init_mom_y = 0;
   plus_rough_fit_init_mom_z = 0;
   minus_rough_fit_init_pos_x = 0;
   minus_rough_fit_init_pos_y = 0;
   minus_rough_fit_init_pos_z = 0;
   minus_rough_fit_init_mom_x = 0;
   minus_rough_fit_init_mom_y = 0;
   minus_rough_fit_init_mom_z = 0;
   plus_single_fit_init_pos_x = 0;
   plus_single_fit_init_pos_y = 0;
   plus_single_fit_init_pos_z = 0;
   plus_single_fit_init_mom_x = 0;
   plus_single_fit_init_mom_y = 0;
   plus_single_fit_init_mom_z = 0;
   minus_single_fit_init_pos_x = 0;
   minus_single_fit_init_pos_y = 0;
   minus_single_fit_init_pos_z = 0;
   minus_single_fit_init_mom_x = 0;
   minus_single_fit_init_mom_y = 0;
   minus_single_fit_init_mom_z = 0;
   plus_track_id = 0;
   plus_charge_id = 0;
   hit_plus_ssd_id = 0;
   hit_plus_ssd_lx = 0;
   hit_plus_ssd_t = 0;
   hit_plus_ssd_adc = 0;
   hit_plus_ssd_size = 0;
   hit_plus_gtr100_xid = 0;
   hit_plus_gtr100_yid = 0;
   hit_plus_gtr100_lx = 0;
   hit_plus_gtr100_ly = 0;
   hit_plus_gtr100_xt = 0;
   hit_plus_gtr100_yt = 0;
   hit_plus_gtr100_xadc = 0;
   hit_plus_gtr100_yadc = 0;
   hit_plus_gtr100_xsize = 0;
   hit_plus_gtr100_ysize = 0;
   hit_plus_gtr200_xid = 0;
   hit_plus_gtr200_yid = 0;
   hit_plus_gtr200_lx = 0;
   hit_plus_gtr200_ly = 0;
   hit_plus_gtr200_xt = 0;
   hit_plus_gtr200_yt = 0;
   hit_plus_gtr200_xadc = 0;
   hit_plus_gtr200_yadc = 0;
   hit_plus_gtr200_xsize = 0;
   hit_plus_gtr200_ysize = 0;
   hit_plus_gtr300_xid = 0;
   hit_plus_gtr300_yid = 0;
   hit_plus_gtr300_lx = 0;
   hit_plus_gtr300_ly = 0;
   hit_plus_gtr300_xt = 0;
   hit_plus_gtr300_yt = 0;
   hit_plus_gtr300_xadc = 0;
   hit_plus_gtr300_yadc = 0;
   hit_plus_gtr300_xsize = 0;
   hit_plus_gtr300_ysize = 0;
   minus_track_id = 0;
   minus_charge_id = 0;
   hit_minus_ssd_id = 0;
   hit_minus_ssd_lx = 0;
   hit_minus_ssd_t = 0;
   hit_minus_ssd_adc = 0;
   hit_minus_ssd_size = 0;
   hit_minus_gtr100_xid = 0;
   hit_minus_gtr100_yid = 0;
   hit_minus_gtr100_lx = 0;
   hit_minus_gtr100_ly = 0;
   hit_minus_gtr100_xt = 0;
   hit_minus_gtr100_yt = 0;
   hit_minus_gtr100_xadc = 0;
   hit_minus_gtr100_yadc = 0;
   hit_minus_gtr100_xsize = 0;
   hit_minus_gtr100_ysize = 0;
   hit_minus_gtr200_xid = 0;
   hit_minus_gtr200_yid = 0;
   hit_minus_gtr200_lx = 0;
   hit_minus_gtr200_ly = 0;
   hit_minus_gtr200_xt = 0;
   hit_minus_gtr200_yt = 0;
   hit_minus_gtr200_xadc = 0;
   hit_minus_gtr200_yadc = 0;
   hit_minus_gtr200_xsize = 0;
   hit_minus_gtr200_ysize = 0;
   hit_minus_gtr300_xid = 0;
   hit_minus_gtr300_yid = 0;
   hit_minus_gtr300_lx = 0;
   hit_minus_gtr300_ly = 0;
   hit_minus_gtr300_xt = 0;
   hit_minus_gtr300_yt = 0;
   hit_minus_gtr300_xadc = 0;
   hit_minus_gtr300_yadc = 0;
   hit_minus_gtr300_xsize = 0;
   hit_minus_gtr300_ysize = 0;
   chi2 = 0;
   plus_chi2 = 0;
   minus_chi2 = 0;
   flag = 0;
   distance = 0;
   plus_nearest_tgt_id = 0;
   plus_nearest_radius = 0;
   minus_nearest_tgt_id = 0;
   minus_nearest_radius = 0;
   dir_id = 0;
   vtx_x = 0;
   vtx_y = 0;
   vtx_z = 0;
   plus_pos_x = 0;
   plus_pos_y = 0;
   plus_pos_z = 0;
   minus_pos_x = 0;
   minus_pos_y = 0;
   minus_pos_z = 0;
   plus_mom = 0;
   plus_mom_x = 0;
   plus_mom_y = 0;
   plus_mom_z = 0;
   plus_mom_theta = 0;
   plus_mom_phi = 0;
   minus_mom = 0;
   minus_mom_x = 0;
   minus_mom_y = 0;
   minus_mom_z = 0;
   minus_mom_theta = 0;
   minus_mom_phi = 0;
   mom_angle = 0;
   ee_mass = 0;
   pipi_mass = 0;
   pip_mass = 0;
   kk_mass = 0;
   simple_best_tgt_id = 0;
   simple_best_tgt_r = 0;
   ee_mass_at_best_tgt = 0;
   pipi_mass_at_best_tgt = 0;
   pip_mass_at_best_tgt = 0;
   kk_mass_at_best_tgt = 0;
   plus_ssd_mid = 0;
   plus_gtr100_mid = 0;
   plus_gtr200_mid = 0;
   plus_gtr300_mid = 0;
   plus_hbd_mid = 0;
   plus_lg_c_mid = 0;
   plus_lg_b_mid = 0;
   plus_lg_a_mid = 0;
   minus_ssd_mid = 0;
   minus_gtr100_mid = 0;
   minus_gtr200_mid = 0;
   minus_gtr300_mid = 0;
   minus_hbd_mid = 0;
   minus_lg_c_mid = 0;
   minus_lg_b_mid = 0;
   minus_lg_a_mid = 0;
   fit_plus_ssd_lx = 0;
   fit_plus_ssd_ly = 0;
   fit_plus_gtr100_lx = 0;
   fit_plus_gtr100_ly = 0;
   fit_plus_gtr200_lx = 0;
   fit_plus_gtr200_ly = 0;
   fit_plus_gtr300_lx = 0;
   fit_plus_gtr300_ly = 0;
   fit_plus_hbd_lx = 0;
   fit_plus_hbd_ly = 0;
   fit_plus_lg_c_lx = 0;
   fit_plus_lg_c_ly = 0;
   fit_plus_lg_b_lx = 0;
   fit_plus_lg_b_ly = 0;
   fit_plus_lg_a_lx = 0;
   fit_plus_lg_a_ly = 0;
   fit_plus_tgt_minus_x = 0;
   fit_plus_tgt_minus_y = 0;
   fit_plus_tgt_zero_x = 0;
   fit_plus_tgt_zero_y = 0;
   fit_plus_tgt_plus_x = 0;
   fit_plus_tgt_plus_y = 0;
   fit_plus_x0_y = 0;
   fit_plus_x0_z = 0;
   fit_minus_ssd_lx = 0;
   fit_minus_ssd_ly = 0;
   fit_minus_gtr100_lx = 0;
   fit_minus_gtr100_ly = 0;
   fit_minus_gtr200_lx = 0;
   fit_minus_gtr200_ly = 0;
   fit_minus_gtr300_lx = 0;
   fit_minus_gtr300_ly = 0;
   fit_minus_hbd_lx = 0;
   fit_minus_hbd_ly = 0;
   fit_minus_lg_c_lx = 0;
   fit_minus_lg_c_ly = 0;
   fit_minus_lg_b_lx = 0;
   fit_minus_lg_b_ly = 0;
   fit_minus_lg_a_lx = 0;
   fit_minus_lg_a_ly = 0;
   fit_minus_tgt_minus_x = 0;
   fit_minus_tgt_minus_y = 0;
   fit_minus_tgt_zero_x = 0;
   fit_minus_tgt_zero_y = 0;
   fit_minus_tgt_plus_x = 0;
   fit_minus_tgt_plus_y = 0;
   fit_minus_x0_y = 0;
   fit_minus_x0_z = 0;
   fit_plus_ssd_mom_lx = 0;
   fit_plus_ssd_mom_ly = 0;
   fit_plus_ssd_mom_lz = 0;
   fit_plus_ssd_mom_gx = 0;
   fit_plus_ssd_mom_gy = 0;
   fit_plus_ssd_mom_gz = 0;
   fit_plus_gtr100_mom_lx = 0;
   fit_plus_gtr100_mom_ly = 0;
   fit_plus_gtr100_mom_lz = 0;
   fit_plus_gtr100_mom_gx = 0;
   fit_plus_gtr100_mom_gy = 0;
   fit_plus_gtr100_mom_gz = 0;
   fit_plus_gtr200_mom_lx = 0;
   fit_plus_gtr200_mom_ly = 0;
   fit_plus_gtr200_mom_lz = 0;
   fit_plus_gtr200_mom_gx = 0;
   fit_plus_gtr200_mom_gy = 0;
   fit_plus_gtr200_mom_gz = 0;
   fit_plus_gtr300_mom_lx = 0;
   fit_plus_gtr300_mom_ly = 0;
   fit_plus_gtr300_mom_lz = 0;
   fit_plus_gtr300_mom_gx = 0;
   fit_plus_gtr300_mom_gy = 0;
   fit_plus_gtr300_mom_gz = 0;
   fit_plus_hbd_mom_lx = 0;
   fit_plus_hbd_mom_ly = 0;
   fit_plus_hbd_mom_lz = 0;
   fit_plus_hbd_mom_gx = 0;
   fit_plus_hbd_mom_gy = 0;
   fit_plus_hbd_mom_gz = 0;
   fit_plus_lg_c_mom_lx = 0;
   fit_plus_lg_c_mom_ly = 0;
   fit_plus_lg_c_mom_lz = 0;
   fit_plus_lg_c_mom_gx = 0;
   fit_plus_lg_c_mom_gy = 0;
   fit_plus_lg_c_mom_gz = 0;
   fit_plus_lg_b_mom_lx = 0;
   fit_plus_lg_b_mom_ly = 0;
   fit_plus_lg_b_mom_lz = 0;
   fit_plus_lg_b_mom_gx = 0;
   fit_plus_lg_b_mom_gy = 0;
   fit_plus_lg_b_mom_gz = 0;
   fit_plus_lg_a_mom_lx = 0;
   fit_plus_lg_a_mom_ly = 0;
   fit_plus_lg_a_mom_lz = 0;
   fit_plus_lg_a_mom_gx = 0;
   fit_plus_lg_a_mom_gy = 0;
   fit_plus_lg_a_mom_gz = 0;
   fit_plus_tgt_minus_mom_x = 0;
   fit_plus_tgt_minus_mom_y = 0;
   fit_plus_tgt_minus_mom_z = 0;
   fit_plus_tgt_zero_mom_x = 0;
   fit_plus_tgt_zero_mom_y = 0;
   fit_plus_tgt_zero_mom_z = 0;
   fit_plus_tgt_plus_mom_x = 0;
   fit_plus_tgt_plus_mom_y = 0;
   fit_plus_tgt_plus_mom_z = 0;
   fit_minus_ssd_mom_lx = 0;
   fit_minus_ssd_mom_ly = 0;
   fit_minus_ssd_mom_lz = 0;
   fit_minus_ssd_mom_gx = 0;
   fit_minus_ssd_mom_gy = 0;
   fit_minus_ssd_mom_gz = 0;
   fit_minus_gtr100_mom_lx = 0;
   fit_minus_gtr100_mom_ly = 0;
   fit_minus_gtr100_mom_lz = 0;
   fit_minus_gtr100_mom_gx = 0;
   fit_minus_gtr100_mom_gy = 0;
   fit_minus_gtr100_mom_gz = 0;
   fit_minus_gtr200_mom_lx = 0;
   fit_minus_gtr200_mom_ly = 0;
   fit_minus_gtr200_mom_lz = 0;
   fit_minus_gtr200_mom_gx = 0;
   fit_minus_gtr200_mom_gy = 0;
   fit_minus_gtr200_mom_gz = 0;
   fit_minus_gtr300_mom_lx = 0;
   fit_minus_gtr300_mom_ly = 0;
   fit_minus_gtr300_mom_lz = 0;
   fit_minus_gtr300_mom_gx = 0;
   fit_minus_gtr300_mom_gy = 0;
   fit_minus_gtr300_mom_gz = 0;
   fit_minus_hbd_mom_lx = 0;
   fit_minus_hbd_mom_ly = 0;
   fit_minus_hbd_mom_lz = 0;
   fit_minus_hbd_mom_gx = 0;
   fit_minus_hbd_mom_gy = 0;
   fit_minus_hbd_mom_gz = 0;
   fit_minus_lg_c_mom_lx = 0;
   fit_minus_lg_c_mom_ly = 0;
   fit_minus_lg_c_mom_lz = 0;
   fit_minus_lg_c_mom_gx = 0;
   fit_minus_lg_c_mom_gy = 0;
   fit_minus_lg_c_mom_gz = 0;
   fit_minus_lg_b_mom_lx = 0;
   fit_minus_lg_b_mom_ly = 0;
   fit_minus_lg_b_mom_lz = 0;
   fit_minus_lg_b_mom_gx = 0;
   fit_minus_lg_b_mom_gy = 0;
   fit_minus_lg_b_mom_gz = 0;
   fit_minus_lg_a_mom_lx = 0;
   fit_minus_lg_a_mom_ly = 0;
   fit_minus_lg_a_mom_lz = 0;
   fit_minus_lg_a_mom_gx = 0;
   fit_minus_lg_a_mom_gy = 0;
   fit_minus_lg_a_mom_gz = 0;
   fit_minus_tgt_minus_mom_x = 0;
   fit_minus_tgt_minus_mom_y = 0;
   fit_minus_tgt_minus_mom_z = 0;
   fit_minus_tgt_zero_mom_x = 0;
   fit_minus_tgt_zero_mom_y = 0;
   fit_minus_tgt_zero_mom_z = 0;
   fit_minus_tgt_plus_mom_x = 0;
   fit_minus_tgt_plus_mom_y = 0;
   fit_minus_tgt_plus_mom_z = 0;
   res_plus_ssd_lx = 0;
   res_plus_gtr100_lx = 0;
   res_plus_gtr100_ly = 0;
   res_plus_gtr200_lx = 0;
   res_plus_gtr200_ly = 0;
   res_plus_gtr300_lx = 0;
   res_plus_gtr300_ly = 0;
   res_minus_ssd_lx = 0;
   res_minus_gtr100_lx = 0;
   res_minus_gtr100_ly = 0;
   res_minus_gtr200_lx = 0;
   res_minus_gtr200_ly = 0;
   res_minus_gtr300_lx = 0;
   res_minus_gtr300_ly = 0;
   fit_parent_mom = 0;
   fit_parent_mom_x = 0;
   fit_parent_mom_y = 0;
   fit_parent_mom_z = 0;
   fit_parent_mom_theta = 0;
   fit_parent_mom_phi = 0;
   fit_parent_tgt_minus_x = 0;
   fit_parent_tgt_minus_y = 0;
   fit_parent_tgt_minus_flight_path = 0;
   fit_parent_tgt_zero_x = 0;
   fit_parent_tgt_zero_y = 0;
   fit_parent_tgt_zero_flight_path = 0;
   fit_parent_tgt_plus_x = 0;
   fit_parent_tgt_plus_y = 0;
   fit_parent_tgt_plus_flight_path = 0;
   fit_parent_best_tgt_id = 0;
   fit_parent_best_tgt_r = 0;
   fit_parent_good_tgt_id_set = 0;
   fit_parent_good_tgt_ids = 0;
   fit_parent_x0_y = 0;
   fit_parent_x0_z = 0;
   proj_plus_n_hbds = 0;
   proj_plus_hbd_min_res = 0;
   proj_plus_hbd_id = 0;
   proj_plus_hbd_lx = 0;
   proj_plus_hbd_ly = 0;
   proj_plus_hbd_resx = 0;
   proj_plus_hbd_resy = 0;
   proj_plus_hbd_adc = 0;
   proj_plus_hbd_size = 0;
   proj_plus_hbd_eprob = 0;


   proj_plus_n_lgs = 0;
   proj_plus_lg_id = 0;
   proj_plus_lg_lx = 0;
   proj_plus_lg_ly = 0;
   proj_plus_lg_resx = 0;
   proj_plus_lg_resy = 0;
   proj_plus_lg_adc = 0;
   proj_minus_n_lgs = 0;
   proj_minus_lg_id = 0;
   proj_minus_lg_lx = 0;
   proj_minus_lg_ly = 0;
   proj_minus_lg_resx =0;
   proj_minus_lg_resy=0;
   proj_minus_lg_adc = 0;




   proj_minus_n_hbds = 0;
   proj_minus_hbd_min_res = 0;
   proj_minus_hbd_id = 0;
   proj_minus_hbd_lx = 0;
   proj_minus_hbd_ly = 0;
   proj_minus_hbd_resx = 0;
   proj_minus_hbd_resy = 0;
   proj_minus_hbd_adc = 0;
   proj_minus_hbd_size = 0;
   proj_minus_hbd_eprob = 0;
   tmp_fit_plus_x0_flag = 0;
   tmp_fit_plus_x0_n_cross = 0;
   tmp_fit_plus_x0_pos_y = 0;
   tmp_fit_plus_x0_pos_z = 0;
   tmp_fit_plus_x0_mom_x = 0;
   tmp_fit_plus_x0_mom_y = 0;
   tmp_fit_plus_x0_mom_z = 0;
   tmp_fit_minus_x0_flag = 0;
   tmp_fit_minus_x0_n_cross = 0;
   tmp_fit_minus_x0_pos_y = 0;
   tmp_fit_minus_x0_pos_z = 0;
   tmp_fit_minus_x0_mom_x = 0;
   tmp_fit_minus_x0_mom_y = 0;
   tmp_fit_minus_x0_mom_z = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run_id", &run_id, &b_run_id);
   fChain->SetBranchAddress("event_id", &event_id, &b_event_id);
   fChain->SetBranchAddress("n_cands", &n_cands, &b_n_cands);
   fChain->SetBranchAddress("n_ssd_clusters", &n_ssd_clusters, &b_n_ssd_clusters);
   fChain->SetBranchAddress("n_gtr100x_clusters", &n_gtr100x_clusters, &b_n_gtr100x_clusters);
   fChain->SetBranchAddress("n_gtr100y_clusters", &n_gtr100y_clusters, &b_n_gtr100y_clusters);
   fChain->SetBranchAddress("n_gtr200x_clusters", &n_gtr200x_clusters, &b_n_gtr200x_clusters);
   fChain->SetBranchAddress("n_gtr200y_clusters", &n_gtr200y_clusters, &b_n_gtr200y_clusters);
   fChain->SetBranchAddress("n_gtr300x_clusters", &n_gtr300x_clusters, &b_n_gtr300x_clusters);
   fChain->SetBranchAddress("n_gtr300y_clusters", &n_gtr300y_clusters, &b_n_gtr300y_clusters);
   fChain->SetBranchAddress("n_hbd_clusters", &n_hbd_clusters, &b_n_hbd_clusters);
   fChain->SetBranchAddress("n_lg_hits", &n_lg_hits, &b_n_lg_hits);
   fChain->SetBranchAddress("n_trg_gtr_hits", &n_trg_gtr_hits, &b_n_trg_gtr_hits);
   fChain->SetBranchAddress("trg_gtr_hit_id", &trg_gtr_hit_id, &b_trg_gtr_hit_id);
   fChain->SetBranchAddress("trg_gtr_hit_mid", &trg_gtr_hit_mid, &b_trg_gtr_hit_mid);
   fChain->SetBranchAddress("trg_gtr_hit_cid", &trg_gtr_hit_cid, &b_trg_gtr_hit_cid);
   fChain->SetBranchAddress("trg_gtr_hit_x", &trg_gtr_hit_x, &b_trg_gtr_hit_x);
   fChain->SetBranchAddress("trg_gtr_hit_y", &trg_gtr_hit_y, &b_trg_gtr_hit_y);
   fChain->SetBranchAddress("trg_gtr_hit_gx", &trg_gtr_hit_gx, &b_trg_gtr_hit_gx);
   fChain->SetBranchAddress("trg_gtr_hit_gy", &trg_gtr_hit_gy, &b_trg_gtr_hit_gy);
   fChain->SetBranchAddress("trg_gtr_hit_gz", &trg_gtr_hit_gz, &b_trg_gtr_hit_gz);
   fChain->SetBranchAddress("trg_gtr_hit_t", &trg_gtr_hit_t, &b_trg_gtr_hit_t);
   fChain->SetBranchAddress("n_trg_hbd_hits", &n_trg_hbd_hits, &b_n_trg_hbd_hits);
   fChain->SetBranchAddress("trg_hbd_hit_id", &trg_hbd_hit_id, &b_trg_hbd_hit_id);
   fChain->SetBranchAddress("trg_hbd_hit_mid", &trg_hbd_hit_mid, &b_trg_hbd_hit_mid);
   fChain->SetBranchAddress("trg_hbd_hit_cid", &trg_hbd_hit_cid, &b_trg_hbd_hit_cid);
   fChain->SetBranchAddress("trg_hbd_hit_x", &trg_hbd_hit_x, &b_trg_hbd_hit_x);
   fChain->SetBranchAddress("trg_hbd_hit_y", &trg_hbd_hit_y, &b_trg_hbd_hit_y);
   fChain->SetBranchAddress("trg_hbd_hit_gx", &trg_hbd_hit_gx, &b_trg_hbd_hit_gx);
   fChain->SetBranchAddress("trg_hbd_hit_gy", &trg_hbd_hit_gy, &b_trg_hbd_hit_gy);
   fChain->SetBranchAddress("trg_hbd_hit_gz", &trg_hbd_hit_gz, &b_trg_hbd_hit_gz);
   fChain->SetBranchAddress("trg_hbd_hit_t", &trg_hbd_hit_t, &b_trg_hbd_hit_t);
   fChain->SetBranchAddress("n_trg_lg_hits", &n_trg_lg_hits, &b_n_trg_lg_hits);
   fChain->SetBranchAddress("trg_lg_hit_id", &trg_lg_hit_id, &b_trg_lg_hit_id);
   fChain->SetBranchAddress("trg_lg_hit_mid", &trg_lg_hit_mid, &b_trg_lg_hit_mid);
   fChain->SetBranchAddress("trg_lg_hit_cid", &trg_lg_hit_cid, &b_trg_lg_hit_cid);
   fChain->SetBranchAddress("trg_lg_hit_x", &trg_lg_hit_x, &b_trg_lg_hit_x);
   fChain->SetBranchAddress("trg_lg_hit_y", &trg_lg_hit_y, &b_trg_lg_hit_y);
   fChain->SetBranchAddress("trg_lg_hit_gx", &trg_lg_hit_gx, &b_trg_lg_hit_gx);
   fChain->SetBranchAddress("trg_lg_hit_gy", &trg_lg_hit_gy, &b_trg_lg_hit_gy);
   fChain->SetBranchAddress("trg_lg_hit_gz", &trg_lg_hit_gz, &b_trg_lg_hit_gz);
   fChain->SetBranchAddress("trg_lg_hit_t", &trg_lg_hit_t, &b_trg_lg_hit_t);
   fChain->SetBranchAddress("n_tracks", &n_tracks, &b_n_tracks);
   fChain->SetBranchAddress("n_pairs", &n_pairs, &b_n_pairs);
   fChain->SetBranchAddress("pair_order", &pair_order, &b_pair_order);
   fChain->SetBranchAddress("plus_rough_fit_init_pos_x", &plus_rough_fit_init_pos_x, &b_plus_rough_fit_init_pos_x);
   fChain->SetBranchAddress("plus_rough_fit_init_pos_y", &plus_rough_fit_init_pos_y, &b_plus_rough_fit_init_pos_y);
   fChain->SetBranchAddress("plus_rough_fit_init_pos_z", &plus_rough_fit_init_pos_z, &b_plus_rough_fit_init_pos_z);
   fChain->SetBranchAddress("plus_rough_fit_init_mom_x", &plus_rough_fit_init_mom_x, &b_plus_rough_fit_init_mom_x);
   fChain->SetBranchAddress("plus_rough_fit_init_mom_y", &plus_rough_fit_init_mom_y, &b_plus_rough_fit_init_mom_y);
   fChain->SetBranchAddress("plus_rough_fit_init_mom_z", &plus_rough_fit_init_mom_z, &b_plus_rough_fit_init_mom_z);
   fChain->SetBranchAddress("minus_rough_fit_init_pos_x", &minus_rough_fit_init_pos_x, &b_minus_rough_fit_init_pos_x);
   fChain->SetBranchAddress("minus_rough_fit_init_pos_y", &minus_rough_fit_init_pos_y, &b_minus_rough_fit_init_pos_y);
   fChain->SetBranchAddress("minus_rough_fit_init_pos_z", &minus_rough_fit_init_pos_z, &b_minus_rough_fit_init_pos_z);
   fChain->SetBranchAddress("minus_rough_fit_init_mom_x", &minus_rough_fit_init_mom_x, &b_minus_rough_fit_init_mom_x);
   fChain->SetBranchAddress("minus_rough_fit_init_mom_y", &minus_rough_fit_init_mom_y, &b_minus_rough_fit_init_mom_y);
   fChain->SetBranchAddress("minus_rough_fit_init_mom_z", &minus_rough_fit_init_mom_z, &b_minus_rough_fit_init_mom_z);
   fChain->SetBranchAddress("plus_single_fit_init_pos_x", &plus_single_fit_init_pos_x, &b_plus_single_fit_init_pos_x);
   fChain->SetBranchAddress("plus_single_fit_init_pos_y", &plus_single_fit_init_pos_y, &b_plus_single_fit_init_pos_y);
   fChain->SetBranchAddress("plus_single_fit_init_pos_z", &plus_single_fit_init_pos_z, &b_plus_single_fit_init_pos_z);
   fChain->SetBranchAddress("plus_single_fit_init_mom_x", &plus_single_fit_init_mom_x, &b_plus_single_fit_init_mom_x);
   fChain->SetBranchAddress("plus_single_fit_init_mom_y", &plus_single_fit_init_mom_y, &b_plus_single_fit_init_mom_y);
   fChain->SetBranchAddress("plus_single_fit_init_mom_z", &plus_single_fit_init_mom_z, &b_plus_single_fit_init_mom_z);
   fChain->SetBranchAddress("minus_single_fit_init_pos_x", &minus_single_fit_init_pos_x, &b_minus_single_fit_init_pos_x);
   fChain->SetBranchAddress("minus_single_fit_init_pos_y", &minus_single_fit_init_pos_y, &b_minus_single_fit_init_pos_y);
   fChain->SetBranchAddress("minus_single_fit_init_pos_z", &minus_single_fit_init_pos_z, &b_minus_single_fit_init_pos_z);
   fChain->SetBranchAddress("minus_single_fit_init_mom_x", &minus_single_fit_init_mom_x, &b_minus_single_fit_init_mom_x);
   fChain->SetBranchAddress("minus_single_fit_init_mom_y", &minus_single_fit_init_mom_y, &b_minus_single_fit_init_mom_y);
   fChain->SetBranchAddress("minus_single_fit_init_mom_z", &minus_single_fit_init_mom_z, &b_minus_single_fit_init_mom_z);
   fChain->SetBranchAddress("plus_track_id", &plus_track_id, &b_plus_track_id);
   fChain->SetBranchAddress("plus_charge_id", &plus_charge_id, &b_plus_charge_id);
   fChain->SetBranchAddress("hit_plus_ssd_id", &hit_plus_ssd_id, &b_hit_plus_ssd_id);
   fChain->SetBranchAddress("hit_plus_ssd_lx", &hit_plus_ssd_lx, &b_hit_plus_ssd_lx);
   fChain->SetBranchAddress("hit_plus_ssd_t", &hit_plus_ssd_t, &b_hit_plus_ssd_t);
   fChain->SetBranchAddress("hit_plus_ssd_adc", &hit_plus_ssd_adc, &b_hit_plus_ssd_adc);
   fChain->SetBranchAddress("hit_plus_ssd_size", &hit_plus_ssd_size, &b_hit_plus_ssd_size);
   fChain->SetBranchAddress("hit_plus_gtr100_xid", &hit_plus_gtr100_xid, &b_hit_plus_gtr100_xid);
   fChain->SetBranchAddress("hit_plus_gtr100_yid", &hit_plus_gtr100_yid, &b_hit_plus_gtr100_yid);
   fChain->SetBranchAddress("hit_plus_gtr100_lx", &hit_plus_gtr100_lx, &b_hit_plus_gtr100_lx);
   fChain->SetBranchAddress("hit_plus_gtr100_ly", &hit_plus_gtr100_ly, &b_hit_plus_gtr100_ly);
   fChain->SetBranchAddress("hit_plus_gtr100_xt", &hit_plus_gtr100_xt, &b_hit_plus_gtr100_xt);
   fChain->SetBranchAddress("hit_plus_gtr100_yt", &hit_plus_gtr100_yt, &b_hit_plus_gtr100_yt);
   fChain->SetBranchAddress("hit_plus_gtr100_xadc", &hit_plus_gtr100_xadc, &b_hit_plus_gtr100_xadc);
   fChain->SetBranchAddress("hit_plus_gtr100_yadc", &hit_plus_gtr100_yadc, &b_hit_plus_gtr100_yadc);
   fChain->SetBranchAddress("hit_plus_gtr100_xsize", &hit_plus_gtr100_xsize, &b_hit_plus_gtr100_xsize);
   fChain->SetBranchAddress("hit_plus_gtr100_ysize", &hit_plus_gtr100_ysize, &b_hit_plus_gtr100_ysize);
   fChain->SetBranchAddress("hit_plus_gtr200_xid", &hit_plus_gtr200_xid, &b_hit_plus_gtr200_xid);
   fChain->SetBranchAddress("hit_plus_gtr200_yid", &hit_plus_gtr200_yid, &b_hit_plus_gtr200_yid);
   fChain->SetBranchAddress("hit_plus_gtr200_lx", &hit_plus_gtr200_lx, &b_hit_plus_gtr200_lx);
   fChain->SetBranchAddress("hit_plus_gtr200_ly", &hit_plus_gtr200_ly, &b_hit_plus_gtr200_ly);
   fChain->SetBranchAddress("hit_plus_gtr200_xt", &hit_plus_gtr200_xt, &b_hit_plus_gtr200_xt);
   fChain->SetBranchAddress("hit_plus_gtr200_yt", &hit_plus_gtr200_yt, &b_hit_plus_gtr200_yt);
   fChain->SetBranchAddress("hit_plus_gtr200_xadc", &hit_plus_gtr200_xadc, &b_hit_plus_gtr200_xadc);
   fChain->SetBranchAddress("hit_plus_gtr200_yadc", &hit_plus_gtr200_yadc, &b_hit_plus_gtr200_yadc);
   fChain->SetBranchAddress("hit_plus_gtr200_xsize", &hit_plus_gtr200_xsize, &b_hit_plus_gtr200_xsize);
   fChain->SetBranchAddress("hit_plus_gtr200_ysize", &hit_plus_gtr200_ysize, &b_hit_plus_gtr200_ysize);
   fChain->SetBranchAddress("hit_plus_gtr300_xid", &hit_plus_gtr300_xid, &b_hit_plus_gtr300_xid);
   fChain->SetBranchAddress("hit_plus_gtr300_yid", &hit_plus_gtr300_yid, &b_hit_plus_gtr300_yid);
   fChain->SetBranchAddress("hit_plus_gtr300_lx", &hit_plus_gtr300_lx, &b_hit_plus_gtr300_lx);
   fChain->SetBranchAddress("hit_plus_gtr300_ly", &hit_plus_gtr300_ly, &b_hit_plus_gtr300_ly);
   fChain->SetBranchAddress("hit_plus_gtr300_xt", &hit_plus_gtr300_xt, &b_hit_plus_gtr300_xt);
   fChain->SetBranchAddress("hit_plus_gtr300_yt", &hit_plus_gtr300_yt, &b_hit_plus_gtr300_yt);
   fChain->SetBranchAddress("hit_plus_gtr300_xadc", &hit_plus_gtr300_xadc, &b_hit_plus_gtr300_xadc);
   fChain->SetBranchAddress("hit_plus_gtr300_yadc", &hit_plus_gtr300_yadc, &b_hit_plus_gtr300_yadc);
   fChain->SetBranchAddress("hit_plus_gtr300_xsize", &hit_plus_gtr300_xsize, &b_hit_plus_gtr300_xsize);
   fChain->SetBranchAddress("hit_plus_gtr300_ysize", &hit_plus_gtr300_ysize, &b_hit_plus_gtr300_ysize);
   fChain->SetBranchAddress("minus_track_id", &minus_track_id, &b_minus_track_id);
   fChain->SetBranchAddress("minus_charge_id", &minus_charge_id, &b_minus_charge_id);
   fChain->SetBranchAddress("hit_minus_ssd_id", &hit_minus_ssd_id, &b_hit_minus_ssd_id);
   fChain->SetBranchAddress("hit_minus_ssd_lx", &hit_minus_ssd_lx, &b_hit_minus_ssd_lx);
   fChain->SetBranchAddress("hit_minus_ssd_t", &hit_minus_ssd_t, &b_hit_minus_ssd_t);
   fChain->SetBranchAddress("hit_minus_ssd_adc", &hit_minus_ssd_adc, &b_hit_minus_ssd_adc);
   fChain->SetBranchAddress("hit_minus_ssd_size", &hit_minus_ssd_size, &b_hit_minus_ssd_size);
   fChain->SetBranchAddress("hit_minus_gtr100_xid", &hit_minus_gtr100_xid, &b_hit_minus_gtr100_xid);
   fChain->SetBranchAddress("hit_minus_gtr100_yid", &hit_minus_gtr100_yid, &b_hit_minus_gtr100_yid);
   fChain->SetBranchAddress("hit_minus_gtr100_lx", &hit_minus_gtr100_lx, &b_hit_minus_gtr100_lx);
   fChain->SetBranchAddress("hit_minus_gtr100_ly", &hit_minus_gtr100_ly, &b_hit_minus_gtr100_ly);
   fChain->SetBranchAddress("hit_minus_gtr100_xt", &hit_minus_gtr100_xt, &b_hit_minus_gtr100_xt);
   fChain->SetBranchAddress("hit_minus_gtr100_yt", &hit_minus_gtr100_yt, &b_hit_minus_gtr100_yt);
   fChain->SetBranchAddress("hit_minus_gtr100_xadc", &hit_minus_gtr100_xadc, &b_hit_minus_gtr100_xadc);
   fChain->SetBranchAddress("hit_minus_gtr100_yadc", &hit_minus_gtr100_yadc, &b_hit_minus_gtr100_yadc);
   fChain->SetBranchAddress("hit_minus_gtr100_xsize", &hit_minus_gtr100_xsize, &b_hit_minus_gtr100_xsize);
   fChain->SetBranchAddress("hit_minus_gtr100_ysize", &hit_minus_gtr100_ysize, &b_hit_minus_gtr100_ysize);
   fChain->SetBranchAddress("hit_minus_gtr200_xid", &hit_minus_gtr200_xid, &b_hit_minus_gtr200_xid);
   fChain->SetBranchAddress("hit_minus_gtr200_yid", &hit_minus_gtr200_yid, &b_hit_minus_gtr200_yid);
   fChain->SetBranchAddress("hit_minus_gtr200_lx", &hit_minus_gtr200_lx, &b_hit_minus_gtr200_lx);
   fChain->SetBranchAddress("hit_minus_gtr200_ly", &hit_minus_gtr200_ly, &b_hit_minus_gtr200_ly);
   fChain->SetBranchAddress("hit_minus_gtr200_xt", &hit_minus_gtr200_xt, &b_hit_minus_gtr200_xt);
   fChain->SetBranchAddress("hit_minus_gtr200_yt", &hit_minus_gtr200_yt, &b_hit_minus_gtr200_yt);
   fChain->SetBranchAddress("hit_minus_gtr200_xadc", &hit_minus_gtr200_xadc, &b_hit_minus_gtr200_xadc);
   fChain->SetBranchAddress("hit_minus_gtr200_yadc", &hit_minus_gtr200_yadc, &b_hit_minus_gtr200_yadc);
   fChain->SetBranchAddress("hit_minus_gtr200_xsize", &hit_minus_gtr200_xsize, &b_hit_minus_gtr200_xsize);
   fChain->SetBranchAddress("hit_minus_gtr200_ysize", &hit_minus_gtr200_ysize, &b_hit_minus_gtr200_ysize);
   fChain->SetBranchAddress("hit_minus_gtr300_xid", &hit_minus_gtr300_xid, &b_hit_minus_gtr300_xid);
   fChain->SetBranchAddress("hit_minus_gtr300_yid", &hit_minus_gtr300_yid, &b_hit_minus_gtr300_yid);
   fChain->SetBranchAddress("hit_minus_gtr300_lx", &hit_minus_gtr300_lx, &b_hit_minus_gtr300_lx);
   fChain->SetBranchAddress("hit_minus_gtr300_ly", &hit_minus_gtr300_ly, &b_hit_minus_gtr300_ly);
   fChain->SetBranchAddress("hit_minus_gtr300_xt", &hit_minus_gtr300_xt, &b_hit_minus_gtr300_xt);
   fChain->SetBranchAddress("hit_minus_gtr300_yt", &hit_minus_gtr300_yt, &b_hit_minus_gtr300_yt);
   fChain->SetBranchAddress("hit_minus_gtr300_xadc", &hit_minus_gtr300_xadc, &b_hit_minus_gtr300_xadc);
   fChain->SetBranchAddress("hit_minus_gtr300_yadc", &hit_minus_gtr300_yadc, &b_hit_minus_gtr300_yadc);
   fChain->SetBranchAddress("hit_minus_gtr300_xsize", &hit_minus_gtr300_xsize, &b_hit_minus_gtr300_xsize);
   fChain->SetBranchAddress("hit_minus_gtr300_ysize", &hit_minus_gtr300_ysize, &b_hit_minus_gtr300_ysize);
   fChain->SetBranchAddress("chi2", &chi2, &b_chi2);
   fChain->SetBranchAddress("plus_chi2", &plus_chi2, &b_plus_chi2);
   fChain->SetBranchAddress("minus_chi2", &minus_chi2, &b_minus_chi2);
   fChain->SetBranchAddress("flag", &flag, &b_flag);
   fChain->SetBranchAddress("distance", &distance, &b_distance);
   fChain->SetBranchAddress("plus_nearest_tgt_id", &plus_nearest_tgt_id, &b_plus_nearest_tgt_id);
   fChain->SetBranchAddress("plus_nearest_radius", &plus_nearest_radius, &b_plus_nearest_radius);
   fChain->SetBranchAddress("minus_nearest_tgt_id", &minus_nearest_tgt_id, &b_minus_nearest_tgt_id);
   fChain->SetBranchAddress("minus_nearest_radius", &minus_nearest_radius, &b_minus_nearest_radius);
   fChain->SetBranchAddress("dir_id", &dir_id, &b_dir_id);
   fChain->SetBranchAddress("vtx_x", &vtx_x, &b_vtx_x);
   fChain->SetBranchAddress("vtx_y", &vtx_y, &b_vtx_y);
   fChain->SetBranchAddress("vtx_z", &vtx_z, &b_vtx_z);
   fChain->SetBranchAddress("plus_pos_x", &plus_pos_x, &b_plus_pos_x);
   fChain->SetBranchAddress("plus_pos_y", &plus_pos_y, &b_plus_pos_y);
   fChain->SetBranchAddress("plus_pos_z", &plus_pos_z, &b_plus_pos_z);
   fChain->SetBranchAddress("minus_pos_x", &minus_pos_x, &b_minus_pos_x);
   fChain->SetBranchAddress("minus_pos_y", &minus_pos_y, &b_minus_pos_y);
   fChain->SetBranchAddress("minus_pos_z", &minus_pos_z, &b_minus_pos_z);
   fChain->SetBranchAddress("plus_mom", &plus_mom, &b_plus_mom);
   fChain->SetBranchAddress("plus_mom_x", &plus_mom_x, &b_plus_mom_x);
   fChain->SetBranchAddress("plus_mom_y", &plus_mom_y, &b_plus_mom_y);
   fChain->SetBranchAddress("plus_mom_z", &plus_mom_z, &b_plus_mom_z);
   fChain->SetBranchAddress("plus_mom_theta", &plus_mom_theta, &b_plus_mom_theta);
   fChain->SetBranchAddress("plus_mom_phi", &plus_mom_phi, &b_plus_mom_phi);
   fChain->SetBranchAddress("minus_mom", &minus_mom, &b_minus_mom);
   fChain->SetBranchAddress("minus_mom_x", &minus_mom_x, &b_minus_mom_x);
   fChain->SetBranchAddress("minus_mom_y", &minus_mom_y, &b_minus_mom_y);
   fChain->SetBranchAddress("minus_mom_z", &minus_mom_z, &b_minus_mom_z);
   fChain->SetBranchAddress("minus_mom_theta", &minus_mom_theta, &b_minus_mom_theta);
   fChain->SetBranchAddress("minus_mom_phi", &minus_mom_phi, &b_minus_mom_phi);
   fChain->SetBranchAddress("mom_angle", &mom_angle, &b_mom_angle);
   fChain->SetBranchAddress("ee_mass", &ee_mass, &b_ee_mass);
   fChain->SetBranchAddress("pipi_mass", &pipi_mass, &b_pipi_mass);
   fChain->SetBranchAddress("pip_mass", &pip_mass, &b_pip_mass);
   fChain->SetBranchAddress("kk_mass", &kk_mass, &b_kk_mass);
   fChain->SetBranchAddress("simple_best_tgt_id", &simple_best_tgt_id, &b_simple_best_tgt_id);
   fChain->SetBranchAddress("simple_best_tgt_r", &simple_best_tgt_r, &b_simple_best_tgt_r);
   fChain->SetBranchAddress("ee_mass_at_best_tgt", &ee_mass_at_best_tgt, &b_ee_mass_at_best_tgt);
   fChain->SetBranchAddress("pipi_mass_at_best_tgt", &pipi_mass_at_best_tgt, &b_pipi_mass_at_best_tgt);
   fChain->SetBranchAddress("pip_mass_at_best_tgt", &pip_mass_at_best_tgt, &b_pip_mass_at_best_tgt);
   fChain->SetBranchAddress("kk_mass_at_best_tgt", &kk_mass_at_best_tgt, &b_kk_mass_at_best_tgt);
   fChain->SetBranchAddress("plus_ssd_mid", &plus_ssd_mid, &b_plus_ssd_mid);
   fChain->SetBranchAddress("plus_gtr100_mid", &plus_gtr100_mid, &b_plus_gtr100_mid);
   fChain->SetBranchAddress("plus_gtr200_mid", &plus_gtr200_mid, &b_plus_gtr200_mid);
   fChain->SetBranchAddress("plus_gtr300_mid", &plus_gtr300_mid, &b_plus_gtr300_mid);
   fChain->SetBranchAddress("plus_hbd_mid", &plus_hbd_mid, &b_plus_hbd_mid);
   fChain->SetBranchAddress("plus_lg_c_mid", &plus_lg_c_mid, &b_plus_lg_c_mid);
   fChain->SetBranchAddress("plus_lg_b_mid", &plus_lg_b_mid, &b_plus_lg_b_mid);
   fChain->SetBranchAddress("plus_lg_a_mid", &plus_lg_a_mid, &b_plus_lg_a_mid);
   fChain->SetBranchAddress("minus_ssd_mid", &minus_ssd_mid, &b_minus_ssd_mid);
   fChain->SetBranchAddress("minus_gtr100_mid", &minus_gtr100_mid, &b_minus_gtr100_mid);
   fChain->SetBranchAddress("minus_gtr200_mid", &minus_gtr200_mid, &b_minus_gtr200_mid);
   fChain->SetBranchAddress("minus_gtr300_mid", &minus_gtr300_mid, &b_minus_gtr300_mid);
   fChain->SetBranchAddress("minus_hbd_mid", &minus_hbd_mid, &b_minus_hbd_mid);
   fChain->SetBranchAddress("minus_lg_c_mid", &minus_lg_c_mid, &b_minus_lg_c_mid);
   fChain->SetBranchAddress("minus_lg_b_mid", &minus_lg_b_mid, &b_minus_lg_b_mid);
   fChain->SetBranchAddress("minus_lg_a_mid", &minus_lg_a_mid, &b_minus_lg_a_mid);
   fChain->SetBranchAddress("fit_plus_ssd_lx", &fit_plus_ssd_lx, &b_fit_plus_ssd_lx);
   fChain->SetBranchAddress("fit_plus_ssd_ly", &fit_plus_ssd_ly, &b_fit_plus_ssd_ly);
   fChain->SetBranchAddress("fit_plus_gtr100_lx", &fit_plus_gtr100_lx, &b_fit_plus_gtr100_lx);
   fChain->SetBranchAddress("fit_plus_gtr100_ly", &fit_plus_gtr100_ly, &b_fit_plus_gtr100_ly);
   fChain->SetBranchAddress("fit_plus_gtr200_lx", &fit_plus_gtr200_lx, &b_fit_plus_gtr200_lx);
   fChain->SetBranchAddress("fit_plus_gtr200_ly", &fit_plus_gtr200_ly, &b_fit_plus_gtr200_ly);
   fChain->SetBranchAddress("fit_plus_gtr300_lx", &fit_plus_gtr300_lx, &b_fit_plus_gtr300_lx);
   fChain->SetBranchAddress("fit_plus_gtr300_ly", &fit_plus_gtr300_ly, &b_fit_plus_gtr300_ly);
   fChain->SetBranchAddress("fit_plus_hbd_lx", &fit_plus_hbd_lx, &b_fit_plus_hbd_lx);
   fChain->SetBranchAddress("fit_plus_hbd_ly", &fit_plus_hbd_ly, &b_fit_plus_hbd_ly);
   fChain->SetBranchAddress("fit_plus_lg_c_lx", &fit_plus_lg_c_lx, &b_fit_plus_lg_c_lx);
   fChain->SetBranchAddress("fit_plus_lg_c_ly", &fit_plus_lg_c_ly, &b_fit_plus_lg_c_ly);
   fChain->SetBranchAddress("fit_plus_lg_b_lx", &fit_plus_lg_b_lx, &b_fit_plus_lg_b_lx);
   fChain->SetBranchAddress("fit_plus_lg_b_ly", &fit_plus_lg_b_ly, &b_fit_plus_lg_b_ly);
   fChain->SetBranchAddress("fit_plus_lg_a_lx", &fit_plus_lg_a_lx, &b_fit_plus_lg_a_lx);
   fChain->SetBranchAddress("fit_plus_lg_a_ly", &fit_plus_lg_a_ly, &b_fit_plus_lg_a_ly);
   fChain->SetBranchAddress("fit_plus_tgt_minus_x", &fit_plus_tgt_minus_x, &b_fit_plus_tgt_minus_x);
   fChain->SetBranchAddress("fit_plus_tgt_minus_y", &fit_plus_tgt_minus_y, &b_fit_plus_tgt_minus_y);
   fChain->SetBranchAddress("fit_plus_tgt_zero_x", &fit_plus_tgt_zero_x, &b_fit_plus_tgt_zero_x);
   fChain->SetBranchAddress("fit_plus_tgt_zero_y", &fit_plus_tgt_zero_y, &b_fit_plus_tgt_zero_y);
   fChain->SetBranchAddress("fit_plus_tgt_plus_x", &fit_plus_tgt_plus_x, &b_fit_plus_tgt_plus_x);
   fChain->SetBranchAddress("fit_plus_tgt_plus_y", &fit_plus_tgt_plus_y, &b_fit_plus_tgt_plus_y);
   fChain->SetBranchAddress("fit_plus_x0_y", &fit_plus_x0_y, &b_fit_plus_x0_y);
   fChain->SetBranchAddress("fit_plus_x0_z", &fit_plus_x0_z, &b_fit_plus_x0_z);
   fChain->SetBranchAddress("fit_minus_ssd_lx", &fit_minus_ssd_lx, &b_fit_minus_ssd_lx);
   fChain->SetBranchAddress("fit_minus_ssd_ly", &fit_minus_ssd_ly, &b_fit_minus_ssd_ly);
   fChain->SetBranchAddress("fit_minus_gtr100_lx", &fit_minus_gtr100_lx, &b_fit_minus_gtr100_lx);
   fChain->SetBranchAddress("fit_minus_gtr100_ly", &fit_minus_gtr100_ly, &b_fit_minus_gtr100_ly);
   fChain->SetBranchAddress("fit_minus_gtr200_lx", &fit_minus_gtr200_lx, &b_fit_minus_gtr200_lx);
   fChain->SetBranchAddress("fit_minus_gtr200_ly", &fit_minus_gtr200_ly, &b_fit_minus_gtr200_ly);
   fChain->SetBranchAddress("fit_minus_gtr300_lx", &fit_minus_gtr300_lx, &b_fit_minus_gtr300_lx);
   fChain->SetBranchAddress("fit_minus_gtr300_ly", &fit_minus_gtr300_ly, &b_fit_minus_gtr300_ly);
   fChain->SetBranchAddress("fit_minus_hbd_lx", &fit_minus_hbd_lx, &b_fit_minus_hbd_lx);
   fChain->SetBranchAddress("fit_minus_hbd_ly", &fit_minus_hbd_ly, &b_fit_minus_hbd_ly);
   fChain->SetBranchAddress("fit_minus_lg_c_lx", &fit_minus_lg_c_lx, &b_fit_minus_lg_c_lx);
   fChain->SetBranchAddress("fit_minus_lg_c_ly", &fit_minus_lg_c_ly, &b_fit_minus_lg_c_ly);
   fChain->SetBranchAddress("fit_minus_lg_b_lx", &fit_minus_lg_b_lx, &b_fit_minus_lg_b_lx);
   fChain->SetBranchAddress("fit_minus_lg_b_ly", &fit_minus_lg_b_ly, &b_fit_minus_lg_b_ly);
   fChain->SetBranchAddress("fit_minus_lg_a_lx", &fit_minus_lg_a_lx, &b_fit_minus_lg_a_lx);
   fChain->SetBranchAddress("fit_minus_lg_a_ly", &fit_minus_lg_a_ly, &b_fit_minus_lg_a_ly);
   fChain->SetBranchAddress("fit_minus_tgt_minus_x", &fit_minus_tgt_minus_x, &b_fit_minus_tgt_minus_x);
   fChain->SetBranchAddress("fit_minus_tgt_minus_y", &fit_minus_tgt_minus_y, &b_fit_minus_tgt_minus_y);
   fChain->SetBranchAddress("fit_minus_tgt_zero_x", &fit_minus_tgt_zero_x, &b_fit_minus_tgt_zero_x);
   fChain->SetBranchAddress("fit_minus_tgt_zero_y", &fit_minus_tgt_zero_y, &b_fit_minus_tgt_zero_y);
   fChain->SetBranchAddress("fit_minus_tgt_plus_x", &fit_minus_tgt_plus_x, &b_fit_minus_tgt_plus_x);
   fChain->SetBranchAddress("fit_minus_tgt_plus_y", &fit_minus_tgt_plus_y, &b_fit_minus_tgt_plus_y);
   fChain->SetBranchAddress("fit_minus_x0_y", &fit_minus_x0_y, &b_fit_minus_x0_y);
   fChain->SetBranchAddress("fit_minus_x0_z", &fit_minus_x0_z, &b_fit_minus_x0_z);
   fChain->SetBranchAddress("fit_plus_ssd_mom_lx", &fit_plus_ssd_mom_lx, &b_fit_plus_ssd_mom_lx);
   fChain->SetBranchAddress("fit_plus_ssd_mom_ly", &fit_plus_ssd_mom_ly, &b_fit_plus_ssd_mom_ly);
   fChain->SetBranchAddress("fit_plus_ssd_mom_lz", &fit_plus_ssd_mom_lz, &b_fit_plus_ssd_mom_lz);
   fChain->SetBranchAddress("fit_plus_ssd_mom_gx", &fit_plus_ssd_mom_gx, &b_fit_plus_ssd_mom_gx);
   fChain->SetBranchAddress("fit_plus_ssd_mom_gy", &fit_plus_ssd_mom_gy, &b_fit_plus_ssd_mom_gy);
   fChain->SetBranchAddress("fit_plus_ssd_mom_gz", &fit_plus_ssd_mom_gz, &b_fit_plus_ssd_mom_gz);
   fChain->SetBranchAddress("fit_plus_gtr100_mom_lx", &fit_plus_gtr100_mom_lx, &b_fit_plus_gtr100_mom_lx);
   fChain->SetBranchAddress("fit_plus_gtr100_mom_ly", &fit_plus_gtr100_mom_ly, &b_fit_plus_gtr100_mom_ly);
   fChain->SetBranchAddress("fit_plus_gtr100_mom_lz", &fit_plus_gtr100_mom_lz, &b_fit_plus_gtr100_mom_lz);
   fChain->SetBranchAddress("fit_plus_gtr100_mom_gx", &fit_plus_gtr100_mom_gx, &b_fit_plus_gtr100_mom_gx);
   fChain->SetBranchAddress("fit_plus_gtr100_mom_gy", &fit_plus_gtr100_mom_gy, &b_fit_plus_gtr100_mom_gy);
   fChain->SetBranchAddress("fit_plus_gtr100_mom_gz", &fit_plus_gtr100_mom_gz, &b_fit_plus_gtr100_mom_gz);
   fChain->SetBranchAddress("fit_plus_gtr200_mom_lx", &fit_plus_gtr200_mom_lx, &b_fit_plus_gtr200_mom_lx);
   fChain->SetBranchAddress("fit_plus_gtr200_mom_ly", &fit_plus_gtr200_mom_ly, &b_fit_plus_gtr200_mom_ly);
   fChain->SetBranchAddress("fit_plus_gtr200_mom_lz", &fit_plus_gtr200_mom_lz, &b_fit_plus_gtr200_mom_lz);
   fChain->SetBranchAddress("fit_plus_gtr200_mom_gx", &fit_plus_gtr200_mom_gx, &b_fit_plus_gtr200_mom_gx);
   fChain->SetBranchAddress("fit_plus_gtr200_mom_gy", &fit_plus_gtr200_mom_gy, &b_fit_plus_gtr200_mom_gy);
   fChain->SetBranchAddress("fit_plus_gtr200_mom_gz", &fit_plus_gtr200_mom_gz, &b_fit_plus_gtr200_mom_gz);
   fChain->SetBranchAddress("fit_plus_gtr300_mom_lx", &fit_plus_gtr300_mom_lx, &b_fit_plus_gtr300_mom_lx);
   fChain->SetBranchAddress("fit_plus_gtr300_mom_ly", &fit_plus_gtr300_mom_ly, &b_fit_plus_gtr300_mom_ly);
   fChain->SetBranchAddress("fit_plus_gtr300_mom_lz", &fit_plus_gtr300_mom_lz, &b_fit_plus_gtr300_mom_lz);
   fChain->SetBranchAddress("fit_plus_gtr300_mom_gx", &fit_plus_gtr300_mom_gx, &b_fit_plus_gtr300_mom_gx);
   fChain->SetBranchAddress("fit_plus_gtr300_mom_gy", &fit_plus_gtr300_mom_gy, &b_fit_plus_gtr300_mom_gy);
   fChain->SetBranchAddress("fit_plus_gtr300_mom_gz", &fit_plus_gtr300_mom_gz, &b_fit_plus_gtr300_mom_gz);
   fChain->SetBranchAddress("fit_plus_hbd_mom_lx", &fit_plus_hbd_mom_lx, &b_fit_plus_hbd_mom_lx);
   fChain->SetBranchAddress("fit_plus_hbd_mom_ly", &fit_plus_hbd_mom_ly, &b_fit_plus_hbd_mom_ly);
   fChain->SetBranchAddress("fit_plus_hbd_mom_lz", &fit_plus_hbd_mom_lz, &b_fit_plus_hbd_mom_lz);
   fChain->SetBranchAddress("fit_plus_hbd_mom_gx", &fit_plus_hbd_mom_gx, &b_fit_plus_hbd_mom_gx);
   fChain->SetBranchAddress("fit_plus_hbd_mom_gy", &fit_plus_hbd_mom_gy, &b_fit_plus_hbd_mom_gy);
   fChain->SetBranchAddress("fit_plus_hbd_mom_gz", &fit_plus_hbd_mom_gz, &b_fit_plus_hbd_mom_gz);
   fChain->SetBranchAddress("fit_plus_lg_c_mom_lx", &fit_plus_lg_c_mom_lx, &b_fit_plus_lg_c_mom_lx);
   fChain->SetBranchAddress("fit_plus_lg_c_mom_ly", &fit_plus_lg_c_mom_ly, &b_fit_plus_lg_c_mom_ly);
   fChain->SetBranchAddress("fit_plus_lg_c_mom_lz", &fit_plus_lg_c_mom_lz, &b_fit_plus_lg_c_mom_lz);
   fChain->SetBranchAddress("fit_plus_lg_c_mom_gx", &fit_plus_lg_c_mom_gx, &b_fit_plus_lg_c_mom_gx);
   fChain->SetBranchAddress("fit_plus_lg_c_mom_gy", &fit_plus_lg_c_mom_gy, &b_fit_plus_lg_c_mom_gy);
   fChain->SetBranchAddress("fit_plus_lg_c_mom_gz", &fit_plus_lg_c_mom_gz, &b_fit_plus_lg_c_mom_gz);
   fChain->SetBranchAddress("fit_plus_lg_b_mom_lx", &fit_plus_lg_b_mom_lx, &b_fit_plus_lg_b_mom_lx);
   fChain->SetBranchAddress("fit_plus_lg_b_mom_ly", &fit_plus_lg_b_mom_ly, &b_fit_plus_lg_b_mom_ly);
   fChain->SetBranchAddress("fit_plus_lg_b_mom_lz", &fit_plus_lg_b_mom_lz, &b_fit_plus_lg_b_mom_lz);
   fChain->SetBranchAddress("fit_plus_lg_b_mom_gx", &fit_plus_lg_b_mom_gx, &b_fit_plus_lg_b_mom_gx);
   fChain->SetBranchAddress("fit_plus_lg_b_mom_gy", &fit_plus_lg_b_mom_gy, &b_fit_plus_lg_b_mom_gy);
   fChain->SetBranchAddress("fit_plus_lg_b_mom_gz", &fit_plus_lg_b_mom_gz, &b_fit_plus_lg_b_mom_gz);
   fChain->SetBranchAddress("fit_plus_lg_a_mom_lx", &fit_plus_lg_a_mom_lx, &b_fit_plus_lg_a_mom_lx);
   fChain->SetBranchAddress("fit_plus_lg_a_mom_ly", &fit_plus_lg_a_mom_ly, &b_fit_plus_lg_a_mom_ly);
   fChain->SetBranchAddress("fit_plus_lg_a_mom_lz", &fit_plus_lg_a_mom_lz, &b_fit_plus_lg_a_mom_lz);
   fChain->SetBranchAddress("fit_plus_lg_a_mom_gx", &fit_plus_lg_a_mom_gx, &b_fit_plus_lg_a_mom_gx);
   fChain->SetBranchAddress("fit_plus_lg_a_mom_gy", &fit_plus_lg_a_mom_gy, &b_fit_plus_lg_a_mom_gy);
   fChain->SetBranchAddress("fit_plus_lg_a_mom_gz", &fit_plus_lg_a_mom_gz, &b_fit_plus_lg_a_mom_gz);
   fChain->SetBranchAddress("fit_plus_tgt_minus_mom_x", &fit_plus_tgt_minus_mom_x, &b_fit_plus_tgt_minus_mom_x);
   fChain->SetBranchAddress("fit_plus_tgt_minus_mom_y", &fit_plus_tgt_minus_mom_y, &b_fit_plus_tgt_minus_mom_y);
   fChain->SetBranchAddress("fit_plus_tgt_minus_mom_z", &fit_plus_tgt_minus_mom_z, &b_fit_plus_tgt_minus_mom_z);
   fChain->SetBranchAddress("fit_plus_tgt_zero_mom_x", &fit_plus_tgt_zero_mom_x, &b_fit_plus_tgt_zero_mom_x);
   fChain->SetBranchAddress("fit_plus_tgt_zero_mom_y", &fit_plus_tgt_zero_mom_y, &b_fit_plus_tgt_zero_mom_y);
   fChain->SetBranchAddress("fit_plus_tgt_zero_mom_z", &fit_plus_tgt_zero_mom_z, &b_fit_plus_tgt_zero_mom_z);
   fChain->SetBranchAddress("fit_plus_tgt_plus_mom_x", &fit_plus_tgt_plus_mom_x, &b_fit_plus_tgt_plus_mom_x);
   fChain->SetBranchAddress("fit_plus_tgt_plus_mom_y", &fit_plus_tgt_plus_mom_y, &b_fit_plus_tgt_plus_mom_y);
   fChain->SetBranchAddress("fit_plus_tgt_plus_mom_z", &fit_plus_tgt_plus_mom_z, &b_fit_plus_tgt_plus_mom_z);
   fChain->SetBranchAddress("fit_minus_ssd_mom_lx", &fit_minus_ssd_mom_lx, &b_fit_minus_ssd_mom_lx);
   fChain->SetBranchAddress("fit_minus_ssd_mom_ly", &fit_minus_ssd_mom_ly, &b_fit_minus_ssd_mom_ly);
   fChain->SetBranchAddress("fit_minus_ssd_mom_lz", &fit_minus_ssd_mom_lz, &b_fit_minus_ssd_mom_lz);
   fChain->SetBranchAddress("fit_minus_ssd_mom_gx", &fit_minus_ssd_mom_gx, &b_fit_minus_ssd_mom_gx);
   fChain->SetBranchAddress("fit_minus_ssd_mom_gy", &fit_minus_ssd_mom_gy, &b_fit_minus_ssd_mom_gy);
   fChain->SetBranchAddress("fit_minus_ssd_mom_gz", &fit_minus_ssd_mom_gz, &b_fit_minus_ssd_mom_gz);
   fChain->SetBranchAddress("fit_minus_gtr100_mom_lx", &fit_minus_gtr100_mom_lx, &b_fit_minus_gtr100_mom_lx);
   fChain->SetBranchAddress("fit_minus_gtr100_mom_ly", &fit_minus_gtr100_mom_ly, &b_fit_minus_gtr100_mom_ly);
   fChain->SetBranchAddress("fit_minus_gtr100_mom_lz", &fit_minus_gtr100_mom_lz, &b_fit_minus_gtr100_mom_lz);
   fChain->SetBranchAddress("fit_minus_gtr100_mom_gx", &fit_minus_gtr100_mom_gx, &b_fit_minus_gtr100_mom_gx);
   fChain->SetBranchAddress("fit_minus_gtr100_mom_gy", &fit_minus_gtr100_mom_gy, &b_fit_minus_gtr100_mom_gy);
   fChain->SetBranchAddress("fit_minus_gtr100_mom_gz", &fit_minus_gtr100_mom_gz, &b_fit_minus_gtr100_mom_gz);
   fChain->SetBranchAddress("fit_minus_gtr200_mom_lx", &fit_minus_gtr200_mom_lx, &b_fit_minus_gtr200_mom_lx);
   fChain->SetBranchAddress("fit_minus_gtr200_mom_ly", &fit_minus_gtr200_mom_ly, &b_fit_minus_gtr200_mom_ly);
   fChain->SetBranchAddress("fit_minus_gtr200_mom_lz", &fit_minus_gtr200_mom_lz, &b_fit_minus_gtr200_mom_lz);
   fChain->SetBranchAddress("fit_minus_gtr200_mom_gx", &fit_minus_gtr200_mom_gx, &b_fit_minus_gtr200_mom_gx);
   fChain->SetBranchAddress("fit_minus_gtr200_mom_gy", &fit_minus_gtr200_mom_gy, &b_fit_minus_gtr200_mom_gy);
   fChain->SetBranchAddress("fit_minus_gtr200_mom_gz", &fit_minus_gtr200_mom_gz, &b_fit_minus_gtr200_mom_gz);
   fChain->SetBranchAddress("fit_minus_gtr300_mom_lx", &fit_minus_gtr300_mom_lx, &b_fit_minus_gtr300_mom_lx);
   fChain->SetBranchAddress("fit_minus_gtr300_mom_ly", &fit_minus_gtr300_mom_ly, &b_fit_minus_gtr300_mom_ly);
   fChain->SetBranchAddress("fit_minus_gtr300_mom_lz", &fit_minus_gtr300_mom_lz, &b_fit_minus_gtr300_mom_lz);
   fChain->SetBranchAddress("fit_minus_gtr300_mom_gx", &fit_minus_gtr300_mom_gx, &b_fit_minus_gtr300_mom_gx);
   fChain->SetBranchAddress("fit_minus_gtr300_mom_gy", &fit_minus_gtr300_mom_gy, &b_fit_minus_gtr300_mom_gy);
   fChain->SetBranchAddress("fit_minus_gtr300_mom_gz", &fit_minus_gtr300_mom_gz, &b_fit_minus_gtr300_mom_gz);
   fChain->SetBranchAddress("fit_minus_hbd_mom_lx", &fit_minus_hbd_mom_lx, &b_fit_minus_hbd_mom_lx);
   fChain->SetBranchAddress("fit_minus_hbd_mom_ly", &fit_minus_hbd_mom_ly, &b_fit_minus_hbd_mom_ly);
   fChain->SetBranchAddress("fit_minus_hbd_mom_lz", &fit_minus_hbd_mom_lz, &b_fit_minus_hbd_mom_lz);
   fChain->SetBranchAddress("fit_minus_hbd_mom_gx", &fit_minus_hbd_mom_gx, &b_fit_minus_hbd_mom_gx);
   fChain->SetBranchAddress("fit_minus_hbd_mom_gy", &fit_minus_hbd_mom_gy, &b_fit_minus_hbd_mom_gy);
   fChain->SetBranchAddress("fit_minus_hbd_mom_gz", &fit_minus_hbd_mom_gz, &b_fit_minus_hbd_mom_gz);
   fChain->SetBranchAddress("fit_minus_lg_c_mom_lx", &fit_minus_lg_c_mom_lx, &b_fit_minus_lg_c_mom_lx);
   fChain->SetBranchAddress("fit_minus_lg_c_mom_ly", &fit_minus_lg_c_mom_ly, &b_fit_minus_lg_c_mom_ly);
   fChain->SetBranchAddress("fit_minus_lg_c_mom_lz", &fit_minus_lg_c_mom_lz, &b_fit_minus_lg_c_mom_lz);
   fChain->SetBranchAddress("fit_minus_lg_c_mom_gx", &fit_minus_lg_c_mom_gx, &b_fit_minus_lg_c_mom_gx);
   fChain->SetBranchAddress("fit_minus_lg_c_mom_gy", &fit_minus_lg_c_mom_gy, &b_fit_minus_lg_c_mom_gy);
   fChain->SetBranchAddress("fit_minus_lg_c_mom_gz", &fit_minus_lg_c_mom_gz, &b_fit_minus_lg_c_mom_gz);
   fChain->SetBranchAddress("fit_minus_lg_b_mom_lx", &fit_minus_lg_b_mom_lx, &b_fit_minus_lg_b_mom_lx);
   fChain->SetBranchAddress("fit_minus_lg_b_mom_ly", &fit_minus_lg_b_mom_ly, &b_fit_minus_lg_b_mom_ly);
   fChain->SetBranchAddress("fit_minus_lg_b_mom_lz", &fit_minus_lg_b_mom_lz, &b_fit_minus_lg_b_mom_lz);
   fChain->SetBranchAddress("fit_minus_lg_b_mom_gx", &fit_minus_lg_b_mom_gx, &b_fit_minus_lg_b_mom_gx);
   fChain->SetBranchAddress("fit_minus_lg_b_mom_gy", &fit_minus_lg_b_mom_gy, &b_fit_minus_lg_b_mom_gy);
   fChain->SetBranchAddress("fit_minus_lg_b_mom_gz", &fit_minus_lg_b_mom_gz, &b_fit_minus_lg_b_mom_gz);
   fChain->SetBranchAddress("fit_minus_lg_a_mom_lx", &fit_minus_lg_a_mom_lx, &b_fit_minus_lg_a_mom_lx);
   fChain->SetBranchAddress("fit_minus_lg_a_mom_ly", &fit_minus_lg_a_mom_ly, &b_fit_minus_lg_a_mom_ly);
   fChain->SetBranchAddress("fit_minus_lg_a_mom_lz", &fit_minus_lg_a_mom_lz, &b_fit_minus_lg_a_mom_lz);
   fChain->SetBranchAddress("fit_minus_lg_a_mom_gx", &fit_minus_lg_a_mom_gx, &b_fit_minus_lg_a_mom_gx);
   fChain->SetBranchAddress("fit_minus_lg_a_mom_gy", &fit_minus_lg_a_mom_gy, &b_fit_minus_lg_a_mom_gy);
   fChain->SetBranchAddress("fit_minus_lg_a_mom_gz", &fit_minus_lg_a_mom_gz, &b_fit_minus_lg_a_mom_gz);
   fChain->SetBranchAddress("fit_minus_tgt_minus_mom_x", &fit_minus_tgt_minus_mom_x, &b_fit_minus_tgt_minus_mom_x);
   fChain->SetBranchAddress("fit_minus_tgt_minus_mom_y", &fit_minus_tgt_minus_mom_y, &b_fit_minus_tgt_minus_mom_y);
   fChain->SetBranchAddress("fit_minus_tgt_minus_mom_z", &fit_minus_tgt_minus_mom_z, &b_fit_minus_tgt_minus_mom_z);
   fChain->SetBranchAddress("fit_minus_tgt_zero_mom_x", &fit_minus_tgt_zero_mom_x, &b_fit_minus_tgt_zero_mom_x);
   fChain->SetBranchAddress("fit_minus_tgt_zero_mom_y", &fit_minus_tgt_zero_mom_y, &b_fit_minus_tgt_zero_mom_y);
   fChain->SetBranchAddress("fit_minus_tgt_zero_mom_z", &fit_minus_tgt_zero_mom_z, &b_fit_minus_tgt_zero_mom_z);
   fChain->SetBranchAddress("fit_minus_tgt_plus_mom_x", &fit_minus_tgt_plus_mom_x, &b_fit_minus_tgt_plus_mom_x);
   fChain->SetBranchAddress("fit_minus_tgt_plus_mom_y", &fit_minus_tgt_plus_mom_y, &b_fit_minus_tgt_plus_mom_y);
   fChain->SetBranchAddress("fit_minus_tgt_plus_mom_z", &fit_minus_tgt_plus_mom_z, &b_fit_minus_tgt_plus_mom_z);
   fChain->SetBranchAddress("res_plus_ssd_lx", &res_plus_ssd_lx, &b_res_plus_ssd_lx);
   fChain->SetBranchAddress("res_plus_gtr100_lx", &res_plus_gtr100_lx, &b_res_plus_gtr100_lx);
   fChain->SetBranchAddress("res_plus_gtr100_ly", &res_plus_gtr100_ly, &b_res_plus_gtr100_ly);
   fChain->SetBranchAddress("res_plus_gtr200_lx", &res_plus_gtr200_lx, &b_res_plus_gtr200_lx);
   fChain->SetBranchAddress("res_plus_gtr200_ly", &res_plus_gtr200_ly, &b_res_plus_gtr200_ly);
   fChain->SetBranchAddress("res_plus_gtr300_lx", &res_plus_gtr300_lx, &b_res_plus_gtr300_lx);
   fChain->SetBranchAddress("res_plus_gtr300_ly", &res_plus_gtr300_ly, &b_res_plus_gtr300_ly);
   fChain->SetBranchAddress("res_minus_ssd_lx", &res_minus_ssd_lx, &b_res_minus_ssd_lx);
   fChain->SetBranchAddress("res_minus_gtr100_lx", &res_minus_gtr100_lx, &b_res_minus_gtr100_lx);
   fChain->SetBranchAddress("res_minus_gtr100_ly", &res_minus_gtr100_ly, &b_res_minus_gtr100_ly);
   fChain->SetBranchAddress("res_minus_gtr200_lx", &res_minus_gtr200_lx, &b_res_minus_gtr200_lx);
   fChain->SetBranchAddress("res_minus_gtr200_ly", &res_minus_gtr200_ly, &b_res_minus_gtr200_ly);
   fChain->SetBranchAddress("res_minus_gtr300_lx", &res_minus_gtr300_lx, &b_res_minus_gtr300_lx);
   fChain->SetBranchAddress("res_minus_gtr300_ly", &res_minus_gtr300_ly, &b_res_minus_gtr300_ly);
   fChain->SetBranchAddress("fit_parent_mom", &fit_parent_mom, &b_fit_parent_mom);
   fChain->SetBranchAddress("fit_parent_mom_x", &fit_parent_mom_x, &b_fit_parent_mom_x);
   fChain->SetBranchAddress("fit_parent_mom_y", &fit_parent_mom_y, &b_fit_parent_mom_y);
   fChain->SetBranchAddress("fit_parent_mom_z", &fit_parent_mom_z, &b_fit_parent_mom_z);
   fChain->SetBranchAddress("fit_parent_mom_theta", &fit_parent_mom_theta, &b_fit_parent_mom_theta);
   fChain->SetBranchAddress("fit_parent_mom_phi", &fit_parent_mom_phi, &b_fit_parent_mom_phi);
   fChain->SetBranchAddress("fit_parent_tgt_minus_x", &fit_parent_tgt_minus_x, &b_fit_parent_tgt_minus_x);
   fChain->SetBranchAddress("fit_parent_tgt_minus_y", &fit_parent_tgt_minus_y, &b_fit_parent_tgt_minus_y);
   fChain->SetBranchAddress("fit_parent_tgt_minus_flight_path", &fit_parent_tgt_minus_flight_path, &b_fit_parent_tgt_minus_flight_path);
   fChain->SetBranchAddress("fit_parent_tgt_zero_x", &fit_parent_tgt_zero_x, &b_fit_parent_tgt_zero_x);
   fChain->SetBranchAddress("fit_parent_tgt_zero_y", &fit_parent_tgt_zero_y, &b_fit_parent_tgt_zero_y);
   fChain->SetBranchAddress("fit_parent_tgt_zero_flight_path", &fit_parent_tgt_zero_flight_path, &b_fit_parent_tgt_zero_flight_path);
   fChain->SetBranchAddress("fit_parent_tgt_plus_x", &fit_parent_tgt_plus_x, &b_fit_parent_tgt_plus_x);
   fChain->SetBranchAddress("fit_parent_tgt_plus_y", &fit_parent_tgt_plus_y, &b_fit_parent_tgt_plus_y);
   fChain->SetBranchAddress("fit_parent_tgt_plus_flight_path", &fit_parent_tgt_plus_flight_path, &b_fit_parent_tgt_plus_flight_path);
   fChain->SetBranchAddress("fit_parent_best_tgt_id", &fit_parent_best_tgt_id, &b_fit_parent_best_tgt_id);
   fChain->SetBranchAddress("fit_parent_best_tgt_r", &fit_parent_best_tgt_r, &b_fit_parent_best_tgt_r);
   fChain->SetBranchAddress("fit_parent_good_tgt_id_set", &fit_parent_good_tgt_id_set, &b_fit_parent_good_tgt_id_set);
   fChain->SetBranchAddress("fit_parent_good_tgt_ids", &fit_parent_good_tgt_ids, &b_fit_parent_good_tgt_ids);
   fChain->SetBranchAddress("fit_parent_x0_y", &fit_parent_x0_y, &b_fit_parent_x0_y);
   fChain->SetBranchAddress("fit_parent_x0_z", &fit_parent_x0_z, &b_fit_parent_x0_z);
   fChain->SetBranchAddress("proj_plus_n_hbds", &proj_plus_n_hbds, &b_proj_plus_n_hbds);
   fChain->SetBranchAddress("proj_plus_hbd_min_res", &proj_plus_hbd_min_res, &b_proj_plus_hbd_min_res);
   fChain->SetBranchAddress("proj_plus_hbd_id", &proj_plus_hbd_id, &b_proj_plus_hbd_id);
   fChain->SetBranchAddress("proj_plus_hbd_lx", &proj_plus_hbd_lx, &b_proj_plus_hbd_lx);
   fChain->SetBranchAddress("proj_plus_hbd_ly", &proj_plus_hbd_ly, &b_proj_plus_hbd_ly);
   fChain->SetBranchAddress("proj_plus_hbd_resx", &proj_plus_hbd_resx, &b_proj_plus_hbd_resx);
   fChain->SetBranchAddress("proj_plus_hbd_resy", &proj_plus_hbd_resy, &b_proj_plus_hbd_resy);
   fChain->SetBranchAddress("proj_plus_hbd_adc", &proj_plus_hbd_adc, &b_proj_plus_hbd_adc);
   fChain->SetBranchAddress("proj_plus_hbd_size", &proj_plus_hbd_size, &b_proj_plus_hbd_size);
   fChain->SetBranchAddress("proj_plus_hbd_eprob", &proj_plus_hbd_eprob, &b_proj_plus_hbd_eprob);
   fChain->SetBranchAddress("proj_minus_n_hbds", &proj_minus_n_hbds, &b_proj_minus_n_hbds);
   fChain->SetBranchAddress("proj_minus_hbd_min_res", &proj_minus_hbd_min_res, &b_proj_minus_hbd_min_res);
   fChain->SetBranchAddress("proj_minus_hbd_id", &proj_minus_hbd_id, &b_proj_minus_hbd_id);
   fChain->SetBranchAddress("proj_minus_hbd_lx", &proj_minus_hbd_lx, &b_proj_minus_hbd_lx);
   fChain->SetBranchAddress("proj_minus_hbd_ly", &proj_minus_hbd_ly, &b_proj_minus_hbd_ly);
   fChain->SetBranchAddress("proj_minus_hbd_resx", &proj_minus_hbd_resx, &b_proj_minus_hbd_resx);
   fChain->SetBranchAddress("proj_minus_hbd_resy", &proj_minus_hbd_resy, &b_proj_minus_hbd_resy);
   fChain->SetBranchAddress("proj_minus_hbd_adc", &proj_minus_hbd_adc, &b_proj_minus_hbd_adc);
   fChain->SetBranchAddress("proj_minus_hbd_size", &proj_minus_hbd_size, &b_proj_minus_hbd_size);
   fChain->SetBranchAddress("proj_minus_hbd_eprob", &proj_minus_hbd_eprob, &b_proj_minus_hbd_eprob);

   fChain->SetBranchAddress("proj_plus_n_lgs", &proj_plus_n_lgs, &b_proj_plus_n_lgs);
   fChain->SetBranchAddress("proj_plus_lg_id", &proj_plus_lg_id, &b_proj_plus_lg_id);
   fChain->SetBranchAddress("proj_plus_lg_lx", &proj_plus_lg_lx, &b_proj_plus_lg_lx);
   fChain->SetBranchAddress("proj_plus_lg_ly", &proj_plus_lg_ly, &b_proj_plus_lg_ly);
   fChain->SetBranchAddress("proj_plus_lg_resx", &proj_plus_lg_resx, &b_proj_plus_lg_resx);
   fChain->SetBranchAddress("proj_plus_lg_resy", &proj_plus_lg_resy, &b_proj_plus_lg_resy);
   fChain->SetBranchAddress("proj_plus_lg_adc", &proj_plus_lg_adc, &b_proj_plus_lg_adc);

   fChain->SetBranchAddress("proj_minus_n_lgs", &proj_minus_n_lgs, &b_proj_minus_n_lgs);
   fChain->SetBranchAddress("proj_minus_lg_id", &proj_minus_lg_id, &b_proj_minus_lg_id);
   fChain->SetBranchAddress("proj_minus_lg_lx", &proj_minus_lg_lx, &b_proj_minus_lg_lx);
   fChain->SetBranchAddress("proj_minus_lg_ly", &proj_minus_lg_ly, &b_proj_minus_lg_ly);
   fChain->SetBranchAddress("proj_minus_lg_resx", &proj_minus_lg_resx, &b_proj_minus_lg_resx);
   fChain->SetBranchAddress("proj_minus_lg_resy", &proj_minus_lg_resy, &b_proj_minus_lg_resy);
   fChain->SetBranchAddress("proj_minus_lg_adc", &proj_minus_lg_adc, &b_proj_minus_lg_adc);

   fChain->SetBranchAddress("tmp_fit_plus_x0_flag", &tmp_fit_plus_x0_flag, &b_tmp_fit_plus_x0_flag);
   fChain->SetBranchAddress("tmp_fit_plus_x0_n_cross", &tmp_fit_plus_x0_n_cross, &b_tmp_fit_plus_x0_n_cross);
   fChain->SetBranchAddress("tmp_fit_plus_x0_pos_y", &tmp_fit_plus_x0_pos_y, &b_tmp_fit_plus_x0_pos_y);
   fChain->SetBranchAddress("tmp_fit_plus_x0_pos_z", &tmp_fit_plus_x0_pos_z, &b_tmp_fit_plus_x0_pos_z);
   fChain->SetBranchAddress("tmp_fit_plus_x0_mom_x", &tmp_fit_plus_x0_mom_x, &b_tmp_fit_plus_x0_mom_x);
   fChain->SetBranchAddress("tmp_fit_plus_x0_mom_y", &tmp_fit_plus_x0_mom_y, &b_tmp_fit_plus_x0_mom_y);
   fChain->SetBranchAddress("tmp_fit_plus_x0_mom_z", &tmp_fit_plus_x0_mom_z, &b_tmp_fit_plus_x0_mom_z);
   fChain->SetBranchAddress("tmp_fit_minus_x0_flag", &tmp_fit_minus_x0_flag, &b_tmp_fit_minus_x0_flag);
   fChain->SetBranchAddress("tmp_fit_minus_x0_n_cross", &tmp_fit_minus_x0_n_cross, &b_tmp_fit_minus_x0_n_cross);
   fChain->SetBranchAddress("tmp_fit_minus_x0_pos_y", &tmp_fit_minus_x0_pos_y, &b_tmp_fit_minus_x0_pos_y);
   fChain->SetBranchAddress("tmp_fit_minus_x0_pos_z", &tmp_fit_minus_x0_pos_z, &b_tmp_fit_minus_x0_pos_z);
   fChain->SetBranchAddress("tmp_fit_minus_x0_mom_x", &tmp_fit_minus_x0_mom_x, &b_tmp_fit_minus_x0_mom_x);
   fChain->SetBranchAddress("tmp_fit_minus_x0_mom_y", &tmp_fit_minus_x0_mom_y, &b_tmp_fit_minus_x0_mom_y);
   fChain->SetBranchAddress("tmp_fit_minus_x0_mom_z", &tmp_fit_minus_x0_mom_z, &b_tmp_fit_minus_x0_mom_z);
   Notify();
}

Bool_t E16DSTN_AfterTrackAna::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void E16DSTN_AfterTrackAna::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t E16DSTN_AfterTrackAna::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef E16DSTN_AfterTrackAna_cxx
