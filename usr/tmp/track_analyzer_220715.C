#define track_analyzer_220715_cxx
#include "track_analyzer_220715.h"

#include <iostream>

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

using namespace std;
using namespace track_analyzer_220715_parameter;

void track_analyzer_220715::MakeBranches(TTree* tree) {
  tree->Branch("run_id",                           &run_id,             "run_id/I");
  tree->Branch("event_id",                         &event_id,           "event_id/I");
  tree->Branch("n_cands",                          &n_cands,            "n_cands/I");
  tree->Branch("n_ssd_clusters",                   &n_ssd_clusters,     "n_ssd_clusters/I");
  tree->Branch("n_gtr100x_clusters",               &n_gtr100x_clusters, "n_gtr100x_clusters/I");
  tree->Branch("n_gtr100y_clusters",               &n_gtr100y_clusters, "n_gtr100y_clusters/I");
  tree->Branch("n_gtr200x_clusters",               &n_gtr200x_clusters, "n_gtr200x_clusters/I");
  tree->Branch("n_gtr200y_clusters",               &n_gtr200y_clusters, "n_gtr200y_clusters/I");
  tree->Branch("n_gtr300x_clusters",               &n_gtr300x_clusters, "n_gtr300x_clusters/I");
  tree->Branch("n_gtr300y_clusters",               &n_gtr300y_clusters, "n_gtr300y_clusters/I");
  tree->Branch("n_hbd_clusters",                   &n_hbd_clusters,     "n_hbd_clusters/I");
  tree->Branch("n_lg_hits",                        &n_lg_hits,          "n_lg_hits/I");
  tree->Branch("n_trg_gtr_hits",                   &n_trg_gtr_hits,     "n_trg_gtr_hits/I");
  tree->Branch("trg_gtr_hit_id",                   &trg_gtr_hit_id);
  tree->Branch("trg_gtr_hit_mid",                  &trg_gtr_hit_mid);
  tree->Branch("trg_gtr_hit_cid",                  &trg_gtr_hit_cid);
  tree->Branch("trg_gtr_hit_x",                    &trg_gtr_hit_x);
  tree->Branch("trg_gtr_hit_y",                    &trg_gtr_hit_y);
  tree->Branch("trg_gtr_hit_gx",                   &trg_gtr_hit_gx);
  tree->Branch("trg_gtr_hit_gy",                   &trg_gtr_hit_gy);
  tree->Branch("trg_gtr_hit_gz",                   &trg_gtr_hit_gz);
  tree->Branch("trg_gtr_hit_t",                    &trg_gtr_hit_t);
  tree->Branch("n_trg_hbd_hits",                   &n_trg_hbd_hits,     "n_trg_hbd_hits/I");
  tree->Branch("trg_hbd_hit_id",                   &trg_hbd_hit_id);
  tree->Branch("trg_hbd_hit_mid",                  &trg_hbd_hit_mid);
  tree->Branch("trg_hbd_hit_cid",                  &trg_hbd_hit_cid);
  tree->Branch("trg_hbd_hit_x",                    &trg_hbd_hit_x);
  tree->Branch("trg_hbd_hit_y",                    &trg_hbd_hit_y);
  tree->Branch("trg_hbd_hit_gx",                   &trg_hbd_hit_gx);
  tree->Branch("trg_hbd_hit_gy",                   &trg_hbd_hit_gy);
  tree->Branch("trg_hbd_hit_gz",                   &trg_hbd_hit_gz);
  tree->Branch("trg_hbd_hit_t",                    &trg_hbd_hit_t);
  tree->Branch("n_trg_lg_hits",                    &n_trg_lg_hits,      "n_trg_lg_hits/I");
  tree->Branch("trg_lg_hit_id",                    &trg_lg_hit_id);
  tree->Branch("trg_lg_hit_mid",                   &trg_lg_hit_mid);
  tree->Branch("trg_lg_hit_cid",                   &trg_lg_hit_cid);
  tree->Branch("trg_lg_hit_x",                     &trg_lg_hit_x);
  tree->Branch("trg_lg_hit_y",                     &trg_lg_hit_y);
  tree->Branch("trg_lg_hit_gx",                    &trg_lg_hit_gx);
  tree->Branch("trg_lg_hit_gy",                    &trg_lg_hit_gy);
  tree->Branch("trg_lg_hit_gz",                    &trg_lg_hit_gz);
  tree->Branch("trg_lg_hit_t",                     &trg_lg_hit_t);
  tree->Branch("n_pairs",                          &out_n_pairs,        "n_pairs/I");
  tree->Branch("pair_order",                       &out_pair_order);
  tree->Branch("plus_rough_fit_init_pos_x",        &out_plus_rough_fit_init_pos_x);
  tree->Branch("plus_rough_fit_init_pos_y",        &out_plus_rough_fit_init_pos_y);
  tree->Branch("plus_rough_fit_init_pos_z",        &out_plus_rough_fit_init_pos_z);
  tree->Branch("plus_rough_fit_init_mom_x",        &out_plus_rough_fit_init_mom_x);
  tree->Branch("plus_rough_fit_init_mom_y",        &out_plus_rough_fit_init_mom_y);
  tree->Branch("plus_rough_fit_init_mom_z",        &out_plus_rough_fit_init_mom_z);
  tree->Branch("minus_rough_fit_init_pos_x",       &out_minus_rough_fit_init_pos_x);
  tree->Branch("minus_rough_fit_init_pos_y",       &out_minus_rough_fit_init_pos_y);
  tree->Branch("minus_rough_fit_init_pos_z",       &out_minus_rough_fit_init_pos_z);
  tree->Branch("minus_rough_fit_init_mom_x",       &out_minus_rough_fit_init_mom_x);
  tree->Branch("minus_rough_fit_init_mom_y",       &out_minus_rough_fit_init_mom_y);
  tree->Branch("minus_rough_fit_init_mom_z",       &out_minus_rough_fit_init_mom_z);
  tree->Branch("plus_single_fit_init_pos_x",       &out_plus_single_fit_init_pos_x);
  tree->Branch("plus_single_fit_init_pos_y",       &out_plus_single_fit_init_pos_y);
  tree->Branch("plus_single_fit_init_pos_z",       &out_plus_single_fit_init_pos_z);
  tree->Branch("plus_single_fit_init_mom_x",       &out_plus_single_fit_init_mom_x);
  tree->Branch("plus_single_fit_init_mom_y",       &out_plus_single_fit_init_mom_y);
  tree->Branch("plus_single_fit_init_mom_z",       &out_plus_single_fit_init_mom_z);
  tree->Branch("minus_single_fit_init_pos_x",      &out_minus_single_fit_init_pos_x);
  tree->Branch("minus_single_fit_init_pos_y",      &out_minus_single_fit_init_pos_y);
  tree->Branch("minus_single_fit_init_pos_z",      &out_minus_single_fit_init_pos_z);
  tree->Branch("minus_single_fit_init_mom_x",      &out_minus_single_fit_init_mom_x);
  tree->Branch("minus_single_fit_init_mom_y",      &out_minus_single_fit_init_mom_y);
  tree->Branch("minus_single_fit_init_mom_z",      &out_minus_single_fit_init_mom_z);
  tree->Branch("plus_track_id",                    &out_plus_track_id);
  tree->Branch("plus_charge_id",                   &out_plus_charge_id);
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
  tree->Branch("minus_track_id",                   &out_minus_track_id);
  tree->Branch("minus_charge_id",                  &out_minus_charge_id);
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
  tree->Branch("plus_chi2",                        &out_plus_chi2);
  tree->Branch("minus_chi2",                       &out_minus_chi2);
  tree->Branch("flag",                             &out_flag);
  tree->Branch("distance",                         &out_distance);
  tree->Branch("plus_nearest_tgt_id",              &out_plus_nearest_tgt_id);
  tree->Branch("plus_nearest_radius",              &out_plus_nearest_radius);
  tree->Branch("minus_nearest_tgt_id",             &out_minus_nearest_tgt_id);
  tree->Branch("minus_nearest_radius",             &out_minus_nearest_radius);
  tree->Branch("dir_id",                           &out_dir_id);
  tree->Branch("vtx_x",                            &out_vtx_x);
  tree->Branch("vtx_y",                            &out_vtx_y);
  tree->Branch("vtx_z",                            &out_vtx_z);
  tree->Branch("plus_pos_x",                       &out_plus_pos_x);
  tree->Branch("plus_pos_y",                       &out_plus_pos_y);
  tree->Branch("plus_pos_z",                       &out_plus_pos_z);
  tree->Branch("minus_pos_x",                      &out_minus_pos_x);
  tree->Branch("minus_pos_y",                      &out_minus_pos_y);
  tree->Branch("minus_pos_z",                      &out_minus_pos_z);
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
  tree->Branch("simple_best_tgt_id",               &out_simple_best_tgt_id);
  tree->Branch("simple_best_tgt_r",                &out_simple_best_tgt_r);
  tree->Branch("ee_mass_at_best_tgt",              &out_ee_mass_at_best_tgt);
  tree->Branch("pipi_mass_at_best_tgt",            &out_pipi_mass_at_best_tgt);
  tree->Branch("pip_mass_at_best_tgt",             &out_pip_mass_at_best_tgt);
  tree->Branch("kk_mass_at_best_tgt",              &out_kk_mass_at_best_tgt);
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
  tree->Branch("fit_plus_x0_y",                    &out_fit_plus_x0_y);
  tree->Branch("fit_plus_x0_z",                    &out_fit_plus_x0_z);
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
  tree->Branch("fit_minus_x0_y",                   &out_fit_minus_x0_y);
  tree->Branch("fit_minus_x0_z",                   &out_fit_minus_x0_z);
  tree->Branch("fit_plus_ssd_mom_lx",              &out_fit_plus_ssd_mom_lx);
  tree->Branch("fit_plus_ssd_mom_ly",              &out_fit_plus_ssd_mom_ly);
  tree->Branch("fit_plus_ssd_mom_lz",              &out_fit_plus_ssd_mom_lz);
  tree->Branch("fit_plus_ssd_mom_gx",              &out_fit_plus_ssd_mom_gx);
  tree->Branch("fit_plus_ssd_mom_gy",              &out_fit_plus_ssd_mom_gy);
  tree->Branch("fit_plus_ssd_mom_gz",              &out_fit_plus_ssd_mom_gz);
  tree->Branch("fit_plus_gtr100_mom_lx",           &out_fit_plus_gtr100_mom_lx);
  tree->Branch("fit_plus_gtr100_mom_ly",           &out_fit_plus_gtr100_mom_ly);
  tree->Branch("fit_plus_gtr100_mom_lz",           &out_fit_plus_gtr100_mom_lz);
  tree->Branch("fit_plus_gtr100_mom_gx",           &out_fit_plus_gtr100_mom_gx);
  tree->Branch("fit_plus_gtr100_mom_gy",           &out_fit_plus_gtr100_mom_gy);
  tree->Branch("fit_plus_gtr100_mom_gz",           &out_fit_plus_gtr100_mom_gz);
  tree->Branch("fit_plus_gtr200_mom_lx",           &out_fit_plus_gtr200_mom_lx);
  tree->Branch("fit_plus_gtr200_mom_ly",           &out_fit_plus_gtr200_mom_ly);
  tree->Branch("fit_plus_gtr200_mom_lz",           &out_fit_plus_gtr200_mom_lz);
  tree->Branch("fit_plus_gtr200_mom_gx",           &out_fit_plus_gtr200_mom_gx);
  tree->Branch("fit_plus_gtr200_mom_gy",           &out_fit_plus_gtr200_mom_gy);
  tree->Branch("fit_plus_gtr200_mom_gz",           &out_fit_plus_gtr200_mom_gz);
  tree->Branch("fit_plus_gtr300_mom_lx",           &out_fit_plus_gtr300_mom_lx);
  tree->Branch("fit_plus_gtr300_mom_ly",           &out_fit_plus_gtr300_mom_ly);
  tree->Branch("fit_plus_gtr300_mom_lz",           &out_fit_plus_gtr300_mom_lz);
  tree->Branch("fit_plus_gtr300_mom_gx",           &out_fit_plus_gtr300_mom_gx);
  tree->Branch("fit_plus_gtr300_mom_gy",           &out_fit_plus_gtr300_mom_gy);
  tree->Branch("fit_plus_gtr300_mom_gz",           &out_fit_plus_gtr300_mom_gz);
  tree->Branch("fit_plus_hbd_mom_lx",              &out_fit_plus_hbd_mom_lx);
  tree->Branch("fit_plus_hbd_mom_ly",              &out_fit_plus_hbd_mom_ly);
  tree->Branch("fit_plus_hbd_mom_lz",              &out_fit_plus_hbd_mom_lz);
  tree->Branch("fit_plus_hbd_mom_gx",              &out_fit_plus_hbd_mom_gx);
  tree->Branch("fit_plus_hbd_mom_gy",              &out_fit_plus_hbd_mom_gy);
  tree->Branch("fit_plus_hbd_mom_gz",              &out_fit_plus_hbd_mom_gz);
  tree->Branch("fit_plus_lg_c_mom_lx",             &out_fit_plus_lg_c_mom_lx);
  tree->Branch("fit_plus_lg_c_mom_ly",             &out_fit_plus_lg_c_mom_ly);
  tree->Branch("fit_plus_lg_c_mom_lz",             &out_fit_plus_lg_c_mom_lz);
  tree->Branch("fit_plus_lg_c_mom_gx",             &out_fit_plus_lg_c_mom_gx);
  tree->Branch("fit_plus_lg_c_mom_gy",             &out_fit_plus_lg_c_mom_gy);
  tree->Branch("fit_plus_lg_c_mom_gz",             &out_fit_plus_lg_c_mom_gz);
  tree->Branch("fit_plus_lg_b_mom_lx",             &out_fit_plus_lg_b_mom_lx);
  tree->Branch("fit_plus_lg_b_mom_ly",             &out_fit_plus_lg_b_mom_ly);
  tree->Branch("fit_plus_lg_b_mom_lz",             &out_fit_plus_lg_b_mom_lz);
  tree->Branch("fit_plus_lg_b_mom_gx",             &out_fit_plus_lg_b_mom_gx);
  tree->Branch("fit_plus_lg_b_mom_gy",             &out_fit_plus_lg_b_mom_gy);
  tree->Branch("fit_plus_lg_b_mom_gz",             &out_fit_plus_lg_b_mom_gz);
  tree->Branch("fit_plus_lg_a_mom_lx",             &out_fit_plus_lg_a_mom_lx);
  tree->Branch("fit_plus_lg_a_mom_ly",             &out_fit_plus_lg_a_mom_ly);
  tree->Branch("fit_plus_lg_a_mom_lz",             &out_fit_plus_lg_a_mom_lz);
  tree->Branch("fit_plus_lg_a_mom_gx",             &out_fit_plus_lg_a_mom_gx);
  tree->Branch("fit_plus_lg_a_mom_gy",             &out_fit_plus_lg_a_mom_gy);
  tree->Branch("fit_plus_lg_a_mom_gz",             &out_fit_plus_lg_a_mom_gz);
  tree->Branch("fit_plus_tgt_minus_mom_x",         &out_fit_plus_tgt_minus_mom_x);
  tree->Branch("fit_plus_tgt_minus_mom_y",         &out_fit_plus_tgt_minus_mom_y);
  tree->Branch("fit_plus_tgt_minus_mom_z",         &out_fit_plus_tgt_minus_mom_z);
  tree->Branch("fit_plus_tgt_zero_mom_x",          &out_fit_plus_tgt_zero_mom_x);
  tree->Branch("fit_plus_tgt_zero_mom_y",          &out_fit_plus_tgt_zero_mom_y);
  tree->Branch("fit_plus_tgt_zero_mom_z",          &out_fit_plus_tgt_zero_mom_z);
  tree->Branch("fit_plus_tgt_plus_mom_x",          &out_fit_plus_tgt_plus_mom_x);
  tree->Branch("fit_plus_tgt_plus_mom_y",          &out_fit_plus_tgt_plus_mom_y);
  tree->Branch("fit_plus_tgt_plus_mom_z",          &out_fit_plus_tgt_plus_mom_z);
  tree->Branch("fit_minus_ssd_mom_lx",             &out_fit_minus_ssd_mom_lx);
  tree->Branch("fit_minus_ssd_mom_ly",             &out_fit_minus_ssd_mom_ly);
  tree->Branch("fit_minus_ssd_mom_lz",             &out_fit_minus_ssd_mom_lz);
  tree->Branch("fit_minus_ssd_mom_gx",             &out_fit_minus_ssd_mom_gx);
  tree->Branch("fit_minus_ssd_mom_gy",             &out_fit_minus_ssd_mom_gy);
  tree->Branch("fit_minus_ssd_mom_gz",             &out_fit_minus_ssd_mom_gz);
  tree->Branch("fit_minus_gtr100_mom_lx",          &out_fit_minus_gtr100_mom_lx);
  tree->Branch("fit_minus_gtr100_mom_ly",          &out_fit_minus_gtr100_mom_ly);
  tree->Branch("fit_minus_gtr100_mom_lz",          &out_fit_minus_gtr100_mom_lz);
  tree->Branch("fit_minus_gtr100_mom_gx",          &out_fit_minus_gtr100_mom_gx);
  tree->Branch("fit_minus_gtr100_mom_gy",          &out_fit_minus_gtr100_mom_gy);
  tree->Branch("fit_minus_gtr100_mom_gz",          &out_fit_minus_gtr100_mom_gz);
  tree->Branch("fit_minus_gtr200_mom_lx",          &out_fit_minus_gtr200_mom_lx);
  tree->Branch("fit_minus_gtr200_mom_ly",          &out_fit_minus_gtr200_mom_ly);
  tree->Branch("fit_minus_gtr200_mom_lz",          &out_fit_minus_gtr200_mom_lz);
  tree->Branch("fit_minus_gtr200_mom_gx",          &out_fit_minus_gtr200_mom_gx);
  tree->Branch("fit_minus_gtr200_mom_gy",          &out_fit_minus_gtr200_mom_gy);
  tree->Branch("fit_minus_gtr200_mom_gz",          &out_fit_minus_gtr200_mom_gz);
  tree->Branch("fit_minus_gtr300_mom_lx",          &out_fit_minus_gtr300_mom_lx);
  tree->Branch("fit_minus_gtr300_mom_ly",          &out_fit_minus_gtr300_mom_ly);
  tree->Branch("fit_minus_gtr300_mom_lz",          &out_fit_minus_gtr300_mom_lz);
  tree->Branch("fit_minus_gtr300_mom_gx",          &out_fit_minus_gtr300_mom_gx);
  tree->Branch("fit_minus_gtr300_mom_gy",          &out_fit_minus_gtr300_mom_gy);
  tree->Branch("fit_minus_gtr300_mom_gz",          &out_fit_minus_gtr300_mom_gz);
  tree->Branch("fit_minus_hbd_mom_lx",             &out_fit_minus_hbd_mom_lx);
  tree->Branch("fit_minus_hbd_mom_ly",             &out_fit_minus_hbd_mom_ly);
  tree->Branch("fit_minus_hbd_mom_lz",             &out_fit_minus_hbd_mom_lz);
  tree->Branch("fit_minus_hbd_mom_gx",             &out_fit_minus_hbd_mom_gx);
  tree->Branch("fit_minus_hbd_mom_gy",             &out_fit_minus_hbd_mom_gy);
  tree->Branch("fit_minus_hbd_mom_gz",             &out_fit_minus_hbd_mom_gz);
  tree->Branch("fit_minus_lg_c_mom_lx",            &out_fit_minus_lg_c_mom_lx);
  tree->Branch("fit_minus_lg_c_mom_ly",            &out_fit_minus_lg_c_mom_ly);
  tree->Branch("fit_minus_lg_c_mom_lz",            &out_fit_minus_lg_c_mom_lz);
  tree->Branch("fit_minus_lg_c_mom_gx",            &out_fit_minus_lg_c_mom_gx);
  tree->Branch("fit_minus_lg_c_mom_gy",            &out_fit_minus_lg_c_mom_gy);
  tree->Branch("fit_minus_lg_c_mom_gz",            &out_fit_minus_lg_c_mom_gz);
  tree->Branch("fit_minus_lg_b_mom_lx",            &out_fit_minus_lg_b_mom_lx);
  tree->Branch("fit_minus_lg_b_mom_ly",            &out_fit_minus_lg_b_mom_ly);
  tree->Branch("fit_minus_lg_b_mom_lz",            &out_fit_minus_lg_b_mom_lz);
  tree->Branch("fit_minus_lg_b_mom_gx",            &out_fit_minus_lg_b_mom_gx);
  tree->Branch("fit_minus_lg_b_mom_gy",            &out_fit_minus_lg_b_mom_gy);
  tree->Branch("fit_minus_lg_b_mom_gz",            &out_fit_minus_lg_b_mom_gz);
  tree->Branch("fit_minus_lg_a_mom_lx",            &out_fit_minus_lg_a_mom_lx);
  tree->Branch("fit_minus_lg_a_mom_ly",            &out_fit_minus_lg_a_mom_ly);
  tree->Branch("fit_minus_lg_a_mom_lz",            &out_fit_minus_lg_a_mom_lz);
  tree->Branch("fit_minus_lg_a_mom_gx",            &out_fit_minus_lg_a_mom_gx);
  tree->Branch("fit_minus_lg_a_mom_gy",            &out_fit_minus_lg_a_mom_gy);
  tree->Branch("fit_minus_lg_a_mom_gz",            &out_fit_minus_lg_a_mom_gz);
  tree->Branch("fit_minus_tgt_minus_mom_x",        &out_fit_minus_tgt_minus_mom_x);
  tree->Branch("fit_minus_tgt_minus_mom_y",        &out_fit_minus_tgt_minus_mom_y);
  tree->Branch("fit_minus_tgt_minus_mom_z",        &out_fit_minus_tgt_minus_mom_z);
  tree->Branch("fit_minus_tgt_zero_mom_x",         &out_fit_minus_tgt_zero_mom_x);
  tree->Branch("fit_minus_tgt_zero_mom_y",         &out_fit_minus_tgt_zero_mom_y);
  tree->Branch("fit_minus_tgt_zero_mom_z",         &out_fit_minus_tgt_zero_mom_z);
  tree->Branch("fit_minus_tgt_plus_mom_x",         &out_fit_minus_tgt_plus_mom_x);
  tree->Branch("fit_minus_tgt_plus_mom_y",         &out_fit_minus_tgt_plus_mom_y);
  tree->Branch("fit_minus_tgt_plus_mom_z",         &out_fit_minus_tgt_plus_mom_z);
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
  tree->Branch("fit_parent_mom",                   &out_fit_parent_mom);
  tree->Branch("fit_parent_mom_x",                 &out_fit_parent_mom_x);
  tree->Branch("fit_parent_mom_y",                 &out_fit_parent_mom_y);
  tree->Branch("fit_parent_mom_z",                 &out_fit_parent_mom_z);
  tree->Branch("fit_parent_mom_theta",             &out_fit_parent_mom_theta);
  tree->Branch("fit_parent_mom_phi",               &out_fit_parent_mom_phi);
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
  tree->Branch("fit_parent_best_tgt_r",            &out_fit_parent_best_tgt_r);
  tree->Branch("fit_parent_good_tgt_id_set",       &out_fit_parent_good_tgt_id_set);
  tree->Branch("fit_parent_good_tgt_ids",          &out_fit_parent_good_tgt_ids);
  tree->Branch("fit_parent_x0_y",                  &out_fit_parent_x0_y);
  tree->Branch("fit_parent_x0_z",                  &out_fit_parent_x0_z);
  tree->Branch("proj_plus_n_hbds",                 &out_proj_plus_n_hbds);
  tree->Branch("proj_plus_hbd_min_res",            &out_proj_plus_hbd_min_res);
  tree->Branch("proj_plus_hbd_id",                 &out_proj_plus_hbd_id);
  tree->Branch("proj_plus_hbd_lx",                 &out_proj_plus_hbd_lx);
  tree->Branch("proj_plus_hbd_ly",                 &out_proj_plus_hbd_ly);
  tree->Branch("proj_plus_hbd_resx",               &out_proj_plus_hbd_resx);
  tree->Branch("proj_plus_hbd_resy",               &out_proj_plus_hbd_resy);
  tree->Branch("proj_plus_hbd_adc",                &out_proj_plus_hbd_adc);
  tree->Branch("proj_plus_hbd_size",               &out_proj_plus_hbd_size);
  tree->Branch("proj_plus_hbd_eprob",              &out_proj_plus_hbd_eprob);
  tree->Branch("proj_minus_n_hbds",                &out_proj_minus_n_hbds);
  tree->Branch("proj_minus_hbd_min_res",           &out_proj_minus_hbd_min_res);
  tree->Branch("proj_minus_hbd_id",                &out_proj_minus_hbd_id);
  tree->Branch("proj_minus_hbd_lx",                &out_proj_minus_hbd_lx);
  tree->Branch("proj_minus_hbd_ly",                &out_proj_minus_hbd_ly);
  tree->Branch("proj_minus_hbd_resx",              &out_proj_minus_hbd_resx);
  tree->Branch("proj_minus_hbd_resy",              &out_proj_minus_hbd_resy);
  tree->Branch("proj_minus_hbd_adc",               &out_proj_minus_hbd_adc);
  tree->Branch("proj_minus_hbd_size",              &out_proj_minus_hbd_size);
  tree->Branch("proj_minus_hbd_eprob",             &out_proj_minus_hbd_eprob);
// tmp check E16ANA_StepTrack function
tree->Branch("tmp_fit_plus_x0_flag",               &out_tmp_fit_plus_x0_flag);
tree->Branch("tmp_fit_plus_x0_n_cross",            &out_tmp_fit_plus_x0_n_cross);
tree->Branch("tmp_fit_plus_x0_pos_y",              &out_tmp_fit_plus_x0_pos_y);
tree->Branch("tmp_fit_plus_x0_pos_z",              &out_tmp_fit_plus_x0_pos_z);
tree->Branch("tmp_fit_plus_x0_mom_x",              &out_tmp_fit_plus_x0_mom_x);
tree->Branch("tmp_fit_plus_x0_mom_y",              &out_tmp_fit_plus_x0_mom_y);
tree->Branch("tmp_fit_plus_x0_mom_z",              &out_tmp_fit_plus_x0_mom_z);
tree->Branch("tmp_fit_minus_x0_flag",              &out_tmp_fit_minus_x0_flag);
tree->Branch("tmp_fit_minus_x0_n_cross",           &out_tmp_fit_minus_x0_n_cross);
tree->Branch("tmp_fit_minus_x0_pos_y",             &out_tmp_fit_minus_x0_pos_y);
tree->Branch("tmp_fit_minus_x0_pos_z",             &out_tmp_fit_minus_x0_pos_z);
tree->Branch("tmp_fit_minus_x0_mom_x",             &out_tmp_fit_minus_x0_mom_x);
tree->Branch("tmp_fit_minus_x0_mom_y",             &out_tmp_fit_minus_x0_mom_y);
tree->Branch("tmp_fit_minus_x0_mom_z",             &out_tmp_fit_minus_x0_mom_z);
#ifdef TMP_SOME_Z
// tmp check vertex
tree->Branch("tmp_plus_static_flag",               &out_tmp_plus_static_flag);
tree->Branch("tmp_plus_static_pos_x",              &out_tmp_plus_static_pos_x);
tree->Branch("tmp_plus_static_pos_y",              &out_tmp_plus_static_pos_y);
tree->Branch("tmp_plus_static_pos_z",              &out_tmp_plus_static_pos_z);
tree->Branch("tmp_plus_static_mom_x",              &out_tmp_plus_static_mom_x);
tree->Branch("tmp_plus_static_mom_y",              &out_tmp_plus_static_mom_y);
tree->Branch("tmp_plus_static_mom_z",              &out_tmp_plus_static_mom_z);
tree->Branch("tmp_minus_static_flag",              &out_tmp_minus_static_flag);
tree->Branch("tmp_minus_static_pos_x",             &out_tmp_minus_static_pos_x);
tree->Branch("tmp_minus_static_pos_y",             &out_tmp_minus_static_pos_y);
tree->Branch("tmp_minus_static_pos_z",             &out_tmp_minus_static_pos_z);
tree->Branch("tmp_minus_static_mom_x",             &out_tmp_minus_static_mom_x);
tree->Branch("tmp_minus_static_mom_y",             &out_tmp_minus_static_mom_y);
tree->Branch("tmp_minus_static_mom_z",             &out_tmp_minus_static_mom_z);
tree->Branch("tmp_static_distance",                &out_tmp_static_distance);
tree->Branch("tmp_static_mom_angle",               &out_tmp_static_mom_angle);
tree->Branch("tmp_static_pipi_mass",               &out_tmp_static_pipi_mass);
tree->Branch("tmp_dynamic_chi2",                   &out_tmp_dynamic_chi2);
tree->Branch("tmp_dynamic_vtx_x",                  &out_tmp_dynamic_vtx_x);
tree->Branch("tmp_dynamic_vtx_y",                  &out_tmp_dynamic_vtx_y);
tree->Branch("tmp_dynamic_vtx_z",                  &out_tmp_dynamic_vtx_z);
tree->Branch("tmp_plus_dynamic_flag",              &out_tmp_plus_dynamic_flag);
tree->Branch("tmp_plus_dynamic_pos_x",             &out_tmp_plus_dynamic_pos_x);
tree->Branch("tmp_plus_dynamic_pos_y",             &out_tmp_plus_dynamic_pos_y);
tree->Branch("tmp_plus_dynamic_pos_z",             &out_tmp_plus_dynamic_pos_z);
tree->Branch("tmp_plus_dynamic_mom_x",             &out_tmp_plus_dynamic_mom_x);
tree->Branch("tmp_plus_dynamic_mom_y",             &out_tmp_plus_dynamic_mom_y);
tree->Branch("tmp_plus_dynamic_mom_z",             &out_tmp_plus_dynamic_mom_z);
tree->Branch("tmp_minus_dynamic_flag",             &out_tmp_minus_dynamic_flag);
tree->Branch("tmp_minus_dynamic_pos_x",            &out_tmp_minus_dynamic_pos_x);
tree->Branch("tmp_minus_dynamic_pos_y",            &out_tmp_minus_dynamic_pos_y);
tree->Branch("tmp_minus_dynamic_pos_z",            &out_tmp_minus_dynamic_pos_z);
tree->Branch("tmp_minus_dynamic_mom_x",            &out_tmp_minus_dynamic_mom_x);
tree->Branch("tmp_minus_dynamic_mom_y",            &out_tmp_minus_dynamic_mom_y);
tree->Branch("tmp_minus_dynamic_mom_z",            &out_tmp_minus_dynamic_mom_z);
tree->Branch("tmp_dynamic_distance",               &out_tmp_dynamic_distance);
tree->Branch("tmp_dynamic_mom_angle",              &out_tmp_dynamic_mom_angle);
tree->Branch("tmp_dynamic_pipi_mass",              &out_tmp_dynamic_pipi_mass);
#endif // TMP_SOME_Z
#ifdef TMP_ZX_NEAREST
tree->Branch("tmp_zx_flag",        &out_tmp_zx_flag);
tree->Branch("tmp_zx_distance",    &out_tmp_zx_distance);
tree->Branch("tmp_zx_vtx_x",       &out_tmp_zx_vtx_x);
tree->Branch("tmp_zx_vtx_y",       &out_tmp_zx_vtx_y);
tree->Branch("tmp_zx_vtx_z",       &out_tmp_zx_vtx_z);
tree->Branch("tmp_zx_plus_pos_x",  &out_tmp_zx_plus_pos_x);
tree->Branch("tmp_zx_plus_pos_y",  &out_tmp_zx_plus_pos_y);
tree->Branch("tmp_zx_plus_pos_z",  &out_tmp_zx_plus_pos_z);
tree->Branch("tmp_zx_minus_pos_x", &out_tmp_zx_minus_pos_x);
tree->Branch("tmp_zx_minus_pos_y", &out_tmp_zx_minus_pos_y);
tree->Branch("tmp_zx_minus_pos_z", &out_tmp_zx_minus_pos_z);
tree->Branch("tmp_zx_plus_mom_x",  &out_tmp_zx_plus_mom_x);
tree->Branch("tmp_zx_plus_mom_y",  &out_tmp_zx_plus_mom_y);
tree->Branch("tmp_zx_plus_mom_z",  &out_tmp_zx_plus_mom_z);
tree->Branch("tmp_zx_minus_mom_x", &out_tmp_zx_minus_mom_x);
tree->Branch("tmp_zx_minus_mom_y", &out_tmp_zx_minus_mom_y);
tree->Branch("tmp_zx_minus_mom_z", &out_tmp_zx_minus_mom_z);
tree->Branch("tmp_zx_pipi_mass",   &out_tmp_zx_pipi_mass);
#endif // TMP_ZX_NEAREST
  return;
}

void track_analyzer_220715::MakeEMBranches(TTree* tree) {
  tree->Branch("plus_run_id",                      &em_plus_run_id);
  tree->Branch("plus_event_id",                    &em_plus_event_id);
  tree->Branch("plus_n_cands",                     &em_plus_n_cands);
//  tree->Branch("plus_n_pairs",                     &em_plus_n_pairs);
  tree->Branch("plus_track_id",                    &em_plus_track_id);
//  tree->Branch("hit_plus_ssd_id",                  &out_hit_plus_ssd_id);
//  tree->Branch("hit_plus_ssd_lx",                  &out_hit_plus_ssd_lx);
//  tree->Branch("hit_plus_ssd_t",                   &out_hit_plus_ssd_t);
//  tree->Branch("hit_plus_ssd_adc",                 &out_hit_plus_ssd_adc);
//  tree->Branch("hit_plus_ssd_size",                &out_hit_plus_ssd_size);
//  tree->Branch("hit_plus_gtr100_xid",              &out_hit_plus_gtr100_xid);
//  tree->Branch("hit_plus_gtr100_yid",              &out_hit_plus_gtr100_yid);
//  tree->Branch("hit_plus_gtr100_lx",               &out_hit_plus_gtr100_lx);
//  tree->Branch("hit_plus_gtr100_ly",               &out_hit_plus_gtr100_ly);
//  tree->Branch("hit_plus_gtr100_xt",               &out_hit_plus_gtr100_xt);
//  tree->Branch("hit_plus_gtr100_yt",               &out_hit_plus_gtr100_yt);
//  tree->Branch("hit_plus_gtr100_xadc",             &out_hit_plus_gtr100_xadc);
//  tree->Branch("hit_plus_gtr100_yadc",             &out_hit_plus_gtr100_yadc);
//  tree->Branch("hit_plus_gtr100_xsize",            &out_hit_plus_gtr100_xsize);
//  tree->Branch("hit_plus_gtr100_ysize",            &out_hit_plus_gtr100_ysize);
//  tree->Branch("hit_plus_gtr200_xid",              &out_hit_plus_gtr200_xid);
//  tree->Branch("hit_plus_gtr200_yid",              &out_hit_plus_gtr200_yid);
//  tree->Branch("hit_plus_gtr200_lx",               &out_hit_plus_gtr200_lx);
//  tree->Branch("hit_plus_gtr200_ly",               &out_hit_plus_gtr200_ly);
//  tree->Branch("hit_plus_gtr200_xt",               &out_hit_plus_gtr200_xt);
//  tree->Branch("hit_plus_gtr200_yt",               &out_hit_plus_gtr200_yt);
//  tree->Branch("hit_plus_gtr200_xadc",             &out_hit_plus_gtr200_xadc);
//  tree->Branch("hit_plus_gtr200_yadc",             &out_hit_plus_gtr200_yadc);
//  tree->Branch("hit_plus_gtr200_xsize",            &out_hit_plus_gtr200_xsize);
//  tree->Branch("hit_plus_gtr200_ysize",            &out_hit_plus_gtr200_ysize);
//  tree->Branch("hit_plus_gtr300_xid",              &out_hit_plus_gtr300_xid);
//  tree->Branch("hit_plus_gtr300_yid",              &out_hit_plus_gtr300_yid);
//  tree->Branch("hit_plus_gtr300_lx",               &out_hit_plus_gtr300_lx);
//  tree->Branch("hit_plus_gtr300_ly",               &out_hit_plus_gtr300_ly);
//  tree->Branch("hit_plus_gtr300_xt",               &out_hit_plus_gtr300_xt);
//  tree->Branch("hit_plus_gtr300_yt",               &out_hit_plus_gtr300_yt);
//  tree->Branch("hit_plus_gtr300_xadc",             &out_hit_plus_gtr300_xadc);
//  tree->Branch("hit_plus_gtr300_yadc",             &out_hit_plus_gtr300_yadc);
//  tree->Branch("hit_plus_gtr300_xsize",            &out_hit_plus_gtr300_xsize);
//  tree->Branch("hit_plus_gtr300_ysize",            &out_hit_plus_gtr300_ysize);
  tree->Branch("minus_run_id",                     &em_minus_run_id);
  tree->Branch("minus_event_id",                   &em_minus_event_id);
  tree->Branch("minus_n_cands",                    &em_minus_n_cands);
//  tree->Branch("minus_n_pairs",                    &em_minus_n_pairs);
  tree->Branch("minus_track_id",                   &em_minus_track_id);
//  tree->Branch("hit_minus_ssd_id",                 &out_hit_minus_ssd_id);
//  tree->Branch("hit_minus_ssd_lx",                 &out_hit_minus_ssd_lx);
//  tree->Branch("hit_minus_ssd_t",                  &out_hit_minus_ssd_t);
//  tree->Branch("hit_minus_ssd_adc",                &out_hit_minus_ssd_adc);
//  tree->Branch("hit_minus_ssd_size",               &out_hit_minus_ssd_size);
//  tree->Branch("hit_minus_gtr100_xid",             &out_hit_minus_gtr100_xid);
//  tree->Branch("hit_minus_gtr100_yid",             &out_hit_minus_gtr100_yid);
//  tree->Branch("hit_minus_gtr100_lx",              &out_hit_minus_gtr100_lx);
//  tree->Branch("hit_minus_gtr100_ly",              &out_hit_minus_gtr100_ly);
//  tree->Branch("hit_minus_gtr100_xt",              &out_hit_minus_gtr100_xt);
//  tree->Branch("hit_minus_gtr100_yt",              &out_hit_minus_gtr100_yt);
//  tree->Branch("hit_minus_gtr100_xadc",            &out_hit_minus_gtr100_xadc);
//  tree->Branch("hit_minus_gtr100_yadc",            &out_hit_minus_gtr100_yadc);
//  tree->Branch("hit_minus_gtr100_xsize",           &out_hit_minus_gtr100_xsize);
//  tree->Branch("hit_minus_gtr100_ysize",           &out_hit_minus_gtr100_ysize);
//  tree->Branch("hit_minus_gtr200_xid",             &out_hit_minus_gtr200_xid);
//  tree->Branch("hit_minus_gtr200_yid",             &out_hit_minus_gtr200_yid);
//  tree->Branch("hit_minus_gtr200_lx",              &out_hit_minus_gtr200_lx);
//  tree->Branch("hit_minus_gtr200_ly",              &out_hit_minus_gtr200_ly);
//  tree->Branch("hit_minus_gtr200_xt",              &out_hit_minus_gtr200_xt);
//  tree->Branch("hit_minus_gtr200_yt",              &out_hit_minus_gtr200_yt);
//  tree->Branch("hit_minus_gtr200_xadc",            &out_hit_minus_gtr200_xadc);
//  tree->Branch("hit_minus_gtr200_yadc",            &out_hit_minus_gtr200_yadc);
//  tree->Branch("hit_minus_gtr200_xsize",           &out_hit_minus_gtr200_xsize);
//  tree->Branch("hit_minus_gtr200_ysize",           &out_hit_minus_gtr200_ysize);
//  tree->Branch("hit_minus_gtr300_xid",             &out_hit_minus_gtr300_xid);
//  tree->Branch("hit_minus_gtr300_yid",             &out_hit_minus_gtr300_yid);
//  tree->Branch("hit_minus_gtr300_lx",              &out_hit_minus_gtr300_lx);
//  tree->Branch("hit_minus_gtr300_ly",              &out_hit_minus_gtr300_ly);
//  tree->Branch("hit_minus_gtr300_xt",              &out_hit_minus_gtr300_xt);
//  tree->Branch("hit_minus_gtr300_yt",              &out_hit_minus_gtr300_yt);
//  tree->Branch("hit_minus_gtr300_xadc",            &out_hit_minus_gtr300_xadc);
//  tree->Branch("hit_minus_gtr300_yadc",            &out_hit_minus_gtr300_yadc);
//  tree->Branch("hit_minus_gtr300_xsize",           &out_hit_minus_gtr300_xsize);
//  tree->Branch("hit_minus_gtr300_ysize",           &out_hit_minus_gtr300_ysize);
  tree->Branch("n_pairs",                          &em_n_pairs);
  tree->Branch("chi2",                             &em_chi2);
  tree->Branch("plus_chi2",                        &em_plus_chi2);
  tree->Branch("minus_chi2",                       &em_minus_chi2);
  tree->Branch("flag",                             &em_flag);
  tree->Branch("distance",                         &em_distance);
  tree->Branch("dir_id",                           &em_dir_id);
  tree->Branch("vtx_x",                            &em_vtx_x);
  tree->Branch("vtx_y",                            &em_vtx_y);
  tree->Branch("vtx_z",                            &em_vtx_z);
  tree->Branch("plus_mom",                         &em_plus_mom);
  tree->Branch("plus_mom_x",                       &em_plus_mom_x);
  tree->Branch("plus_mom_y",                       &em_plus_mom_y);
  tree->Branch("plus_mom_z",                       &em_plus_mom_z);
  tree->Branch("plus_mom_theta",                   &em_plus_mom_theta);
  tree->Branch("plus_mom_phi",                     &em_plus_mom_phi);
  tree->Branch("minus_mom",                        &em_minus_mom);
  tree->Branch("minus_mom_x",                      &em_minus_mom_x);
  tree->Branch("minus_mom_y",                      &em_minus_mom_y);
  tree->Branch("minus_mom_z",                      &em_minus_mom_z);
  tree->Branch("minus_mom_theta",                  &em_minus_mom_theta);
  tree->Branch("minus_mom_phi",                    &em_minus_mom_phi);
  tree->Branch("mom_angle",                        &em_mom_angle);
  tree->Branch("ee_mass",                          &em_ee_mass);
  tree->Branch("pipi_mass",                        &em_pipi_mass);
  tree->Branch("pip_mass",                         &em_pip_mass);
  tree->Branch("kk_mass",                          &em_kk_mass);
  tree->Branch("simple_best_tgt_id",               &em_simple_best_tgt_id);
  tree->Branch("simple_best_tgt_r",                &em_simple_best_tgt_r);
  tree->Branch("ee_mass_at_best_tgt",              &em_ee_mass_at_best_tgt);
  tree->Branch("pipi_mass_at_best_tgt",            &em_pipi_mass_at_best_tgt);
  tree->Branch("pip_mass_at_best_tgt",             &em_pip_mass_at_best_tgt);
  tree->Branch("kk_mass_at_best_tgt",              &em_kk_mass_at_best_tgt);
  tree->Branch("plus_ssd_mid",                     &em_plus_ssd_mid);
  tree->Branch("plus_gtr100_mid",                  &em_plus_gtr100_mid);
  tree->Branch("plus_gtr200_mid",                  &em_plus_gtr200_mid);
  tree->Branch("plus_gtr300_mid",                  &em_plus_gtr300_mid);
  tree->Branch("plus_hbd_mid",                     &em_plus_hbd_mid);
  tree->Branch("plus_lg_c_mid",                    &em_plus_lg_c_mid);
  tree->Branch("plus_lg_b_mid",                    &em_plus_lg_b_mid);
  tree->Branch("plus_lg_a_mid",                    &em_plus_lg_a_mid);
  tree->Branch("minus_ssd_mid",                    &em_minus_ssd_mid);
  tree->Branch("minus_gtr100_mid",                 &em_minus_gtr100_mid);
  tree->Branch("minus_gtr200_mid",                 &em_minus_gtr200_mid);
  tree->Branch("minus_gtr300_mid",                 &em_minus_gtr300_mid);
  tree->Branch("minus_hbd_mid",                    &em_minus_hbd_mid);
  tree->Branch("minus_lg_c_mid",                   &em_minus_lg_c_mid);
  tree->Branch("minus_lg_b_mid",                   &em_minus_lg_b_mid);
  tree->Branch("minus_lg_a_mid",                   &em_minus_lg_a_mid);
  tree->Branch("fit_plus_ssd_lx",                  &em_fit_plus_ssd_lx);
  tree->Branch("fit_plus_ssd_ly",                  &em_fit_plus_ssd_ly);
  tree->Branch("fit_plus_gtr100_lx",               &em_fit_plus_gtr100_lx);
  tree->Branch("fit_plus_gtr100_ly",               &em_fit_plus_gtr100_ly);
  tree->Branch("fit_plus_gtr200_lx",               &em_fit_plus_gtr200_lx);
  tree->Branch("fit_plus_gtr200_ly",               &em_fit_plus_gtr200_ly);
  tree->Branch("fit_plus_gtr300_lx",               &em_fit_plus_gtr300_lx);
  tree->Branch("fit_plus_gtr300_ly",               &em_fit_plus_gtr300_ly);
  tree->Branch("fit_plus_hbd_lx",                  &em_fit_plus_hbd_lx);
  tree->Branch("fit_plus_hbd_ly",                  &em_fit_plus_hbd_ly);
  tree->Branch("fit_plus_lg_c_lx",                 &em_fit_plus_lg_c_lx);
  tree->Branch("fit_plus_lg_c_ly",                 &em_fit_plus_lg_c_ly);
  tree->Branch("fit_plus_lg_b_lx",                 &em_fit_plus_lg_b_lx);
  tree->Branch("fit_plus_lg_b_ly",                 &em_fit_plus_lg_b_ly);
  tree->Branch("fit_plus_lg_a_lx",                 &em_fit_plus_lg_a_lx);
  tree->Branch("fit_plus_lg_a_ly",                 &em_fit_plus_lg_a_ly);
  tree->Branch("fit_plus_tgt_minus_x",             &em_fit_plus_tgt_minus_x);
  tree->Branch("fit_plus_tgt_minus_y",             &em_fit_plus_tgt_minus_y);
  tree->Branch("fit_plus_tgt_zero_x",              &em_fit_plus_tgt_zero_x);
  tree->Branch("fit_plus_tgt_zero_y",              &em_fit_plus_tgt_zero_y);
  tree->Branch("fit_plus_tgt_plus_x",              &em_fit_plus_tgt_plus_x);
  tree->Branch("fit_plus_tgt_plus_y",              &em_fit_plus_tgt_plus_y);
  tree->Branch("fit_plus_x0_y",                    &em_fit_plus_x0_y);
  tree->Branch("fit_plus_x0_z",                    &em_fit_plus_x0_z);
  tree->Branch("fit_minus_ssd_lx",                 &em_fit_minus_ssd_lx);
  tree->Branch("fit_minus_ssd_ly",                 &em_fit_minus_ssd_ly);
  tree->Branch("fit_minus_gtr100_lx",              &em_fit_minus_gtr100_lx);
  tree->Branch("fit_minus_gtr100_ly",              &em_fit_minus_gtr100_ly);
  tree->Branch("fit_minus_gtr200_lx",              &em_fit_minus_gtr200_lx);
  tree->Branch("fit_minus_gtr200_ly",              &em_fit_minus_gtr200_ly);
  tree->Branch("fit_minus_gtr300_lx",              &em_fit_minus_gtr300_lx);
  tree->Branch("fit_minus_gtr300_ly",              &em_fit_minus_gtr300_ly);
  tree->Branch("fit_minus_hbd_lx",                 &em_fit_minus_hbd_lx);
  tree->Branch("fit_minus_hbd_ly",                 &em_fit_minus_hbd_ly);
  tree->Branch("fit_minus_lg_c_lx",                &em_fit_minus_lg_c_lx);
  tree->Branch("fit_minus_lg_c_ly",                &em_fit_minus_lg_c_ly);
  tree->Branch("fit_minus_lg_b_lx",                &em_fit_minus_lg_b_lx);
  tree->Branch("fit_minus_lg_b_ly",                &em_fit_minus_lg_b_ly);
  tree->Branch("fit_minus_lg_a_lx",                &em_fit_minus_lg_a_lx);
  tree->Branch("fit_minus_lg_a_ly",                &em_fit_minus_lg_a_ly);
  tree->Branch("fit_minus_tgt_minus_x",            &em_fit_minus_tgt_minus_x);
  tree->Branch("fit_minus_tgt_minus_y",            &em_fit_minus_tgt_minus_y);
  tree->Branch("fit_minus_tgt_zero_x",             &em_fit_minus_tgt_zero_x);
  tree->Branch("fit_minus_tgt_zero_y",             &em_fit_minus_tgt_zero_y);
  tree->Branch("fit_minus_tgt_plus_x",             &em_fit_minus_tgt_plus_x);
  tree->Branch("fit_minus_tgt_plus_y",             &em_fit_minus_tgt_plus_y);
  tree->Branch("fit_minus_x0_y",                   &em_fit_minus_x0_y);
  tree->Branch("fit_minus_x0_z",                   &em_fit_minus_x0_z);
  tree->Branch("fit_plus_ssd_mom_lx",              &em_fit_plus_ssd_mom_lx);
  tree->Branch("fit_plus_ssd_mom_ly",              &em_fit_plus_ssd_mom_ly);
  tree->Branch("fit_plus_ssd_mom_lz",              &em_fit_plus_ssd_mom_lz);
  tree->Branch("fit_plus_ssd_mom_gx",              &em_fit_plus_ssd_mom_gx);
  tree->Branch("fit_plus_ssd_mom_gy",              &em_fit_plus_ssd_mom_gy);
  tree->Branch("fit_plus_ssd_mom_gz",              &em_fit_plus_ssd_mom_gz);
  tree->Branch("fit_plus_gtr100_mom_lx",           &em_fit_plus_gtr100_mom_lx);
  tree->Branch("fit_plus_gtr100_mom_ly",           &em_fit_plus_gtr100_mom_ly);
  tree->Branch("fit_plus_gtr100_mom_lz",           &em_fit_plus_gtr100_mom_lz);
  tree->Branch("fit_plus_gtr100_mom_gx",           &em_fit_plus_gtr100_mom_gx);
  tree->Branch("fit_plus_gtr100_mom_gy",           &em_fit_plus_gtr100_mom_gy);
  tree->Branch("fit_plus_gtr100_mom_gz",           &em_fit_plus_gtr100_mom_gz);
  tree->Branch("fit_plus_gtr200_mom_lx",           &em_fit_plus_gtr200_mom_lx);
  tree->Branch("fit_plus_gtr200_mom_ly",           &em_fit_plus_gtr200_mom_ly);
  tree->Branch("fit_plus_gtr200_mom_lz",           &em_fit_plus_gtr200_mom_lz);
  tree->Branch("fit_plus_gtr200_mom_gx",           &em_fit_plus_gtr200_mom_gx);
  tree->Branch("fit_plus_gtr200_mom_gy",           &em_fit_plus_gtr200_mom_gy);
  tree->Branch("fit_plus_gtr200_mom_gz",           &em_fit_plus_gtr200_mom_gz);
  tree->Branch("fit_plus_gtr300_mom_lx",           &em_fit_plus_gtr300_mom_lx);
  tree->Branch("fit_plus_gtr300_mom_ly",           &em_fit_plus_gtr300_mom_ly);
  tree->Branch("fit_plus_gtr300_mom_lz",           &em_fit_plus_gtr300_mom_lz);
  tree->Branch("fit_plus_gtr300_mom_gx",           &em_fit_plus_gtr300_mom_gx);
  tree->Branch("fit_plus_gtr300_mom_gy",           &em_fit_plus_gtr300_mom_gy);
  tree->Branch("fit_plus_gtr300_mom_gz",           &em_fit_plus_gtr300_mom_gz);
  tree->Branch("fit_plus_hbd_mom_lx",              &em_fit_plus_hbd_mom_lx);
  tree->Branch("fit_plus_hbd_mom_ly",              &em_fit_plus_hbd_mom_ly);
  tree->Branch("fit_plus_hbd_mom_lz",              &em_fit_plus_hbd_mom_lz);
  tree->Branch("fit_plus_hbd_mom_gx",              &em_fit_plus_hbd_mom_gx);
  tree->Branch("fit_plus_hbd_mom_gy",              &em_fit_plus_hbd_mom_gy);
  tree->Branch("fit_plus_hbd_mom_gz",              &em_fit_plus_hbd_mom_gz);
  tree->Branch("fit_plus_lg_c_mom_lx",             &em_fit_plus_lg_c_mom_lx);
  tree->Branch("fit_plus_lg_c_mom_ly",             &em_fit_plus_lg_c_mom_ly);
  tree->Branch("fit_plus_lg_c_mom_lz",             &em_fit_plus_lg_c_mom_lz);
  tree->Branch("fit_plus_lg_c_mom_gx",             &em_fit_plus_lg_c_mom_gx);
  tree->Branch("fit_plus_lg_c_mom_gy",             &em_fit_plus_lg_c_mom_gy);
  tree->Branch("fit_plus_lg_c_mom_gz",             &em_fit_plus_lg_c_mom_gz);
  tree->Branch("fit_plus_lg_b_mom_lx",             &em_fit_plus_lg_b_mom_lx);
  tree->Branch("fit_plus_lg_b_mom_ly",             &em_fit_plus_lg_b_mom_ly);
  tree->Branch("fit_plus_lg_b_mom_lz",             &em_fit_plus_lg_b_mom_lz);
  tree->Branch("fit_plus_lg_b_mom_gx",             &em_fit_plus_lg_b_mom_gx);
  tree->Branch("fit_plus_lg_b_mom_gy",             &em_fit_plus_lg_b_mom_gy);
  tree->Branch("fit_plus_lg_b_mom_gz",             &em_fit_plus_lg_b_mom_gz);
  tree->Branch("fit_plus_lg_a_mom_lx",             &em_fit_plus_lg_a_mom_lx);
  tree->Branch("fit_plus_lg_a_mom_ly",             &em_fit_plus_lg_a_mom_ly);
  tree->Branch("fit_plus_lg_a_mom_lz",             &em_fit_plus_lg_a_mom_lz);
  tree->Branch("fit_plus_lg_a_mom_gx",             &em_fit_plus_lg_a_mom_gx);
  tree->Branch("fit_plus_lg_a_mom_gy",             &em_fit_plus_lg_a_mom_gy);
  tree->Branch("fit_plus_lg_a_mom_gz",             &em_fit_plus_lg_a_mom_gz);
  tree->Branch("fit_plus_tgt_minus_mom_x",         &em_fit_plus_tgt_minus_mom_x);
  tree->Branch("fit_plus_tgt_minus_mom_y",         &em_fit_plus_tgt_minus_mom_y);
  tree->Branch("fit_plus_tgt_minus_mom_z",         &em_fit_plus_tgt_minus_mom_z);
  tree->Branch("fit_plus_tgt_zero_mom_x",          &em_fit_plus_tgt_zero_mom_x);
  tree->Branch("fit_plus_tgt_zero_mom_y",          &em_fit_plus_tgt_zero_mom_y);
  tree->Branch("fit_plus_tgt_zero_mom_z",          &em_fit_plus_tgt_zero_mom_z);
  tree->Branch("fit_plus_tgt_plus_mom_x",          &em_fit_plus_tgt_plus_mom_x);
  tree->Branch("fit_plus_tgt_plus_mom_y",          &em_fit_plus_tgt_plus_mom_y);
  tree->Branch("fit_plus_tgt_plus_mom_z",          &em_fit_plus_tgt_plus_mom_z);
  tree->Branch("fit_minus_ssd_mom_lx",             &em_fit_minus_ssd_mom_lx);
  tree->Branch("fit_minus_ssd_mom_ly",             &em_fit_minus_ssd_mom_ly);
  tree->Branch("fit_minus_ssd_mom_lz",             &em_fit_minus_ssd_mom_lz);
  tree->Branch("fit_minus_ssd_mom_gx",             &em_fit_minus_ssd_mom_gx);
  tree->Branch("fit_minus_ssd_mom_gy",             &em_fit_minus_ssd_mom_gy);
  tree->Branch("fit_minus_ssd_mom_gz",             &em_fit_minus_ssd_mom_gz);
  tree->Branch("fit_minus_gtr100_mom_lx",          &em_fit_minus_gtr100_mom_lx);
  tree->Branch("fit_minus_gtr100_mom_ly",          &em_fit_minus_gtr100_mom_ly);
  tree->Branch("fit_minus_gtr100_mom_lz",          &em_fit_minus_gtr100_mom_lz);
  tree->Branch("fit_minus_gtr100_mom_gx",          &em_fit_minus_gtr100_mom_gx);
  tree->Branch("fit_minus_gtr100_mom_gy",          &em_fit_minus_gtr100_mom_gy);
  tree->Branch("fit_minus_gtr100_mom_gz",          &em_fit_minus_gtr100_mom_gz);
  tree->Branch("fit_minus_gtr200_mom_lx",          &em_fit_minus_gtr200_mom_lx);
  tree->Branch("fit_minus_gtr200_mom_ly",          &em_fit_minus_gtr200_mom_ly);
  tree->Branch("fit_minus_gtr200_mom_lz",          &em_fit_minus_gtr200_mom_lz);
  tree->Branch("fit_minus_gtr200_mom_gx",          &em_fit_minus_gtr200_mom_gx);
  tree->Branch("fit_minus_gtr200_mom_gy",          &em_fit_minus_gtr200_mom_gy);
  tree->Branch("fit_minus_gtr200_mom_gz",          &em_fit_minus_gtr200_mom_gz);
  tree->Branch("fit_minus_gtr300_mom_lx",          &em_fit_minus_gtr300_mom_lx);
  tree->Branch("fit_minus_gtr300_mom_ly",          &em_fit_minus_gtr300_mom_ly);
  tree->Branch("fit_minus_gtr300_mom_lz",          &em_fit_minus_gtr300_mom_lz);
  tree->Branch("fit_minus_gtr300_mom_gx",          &em_fit_minus_gtr300_mom_gx);
  tree->Branch("fit_minus_gtr300_mom_gy",          &em_fit_minus_gtr300_mom_gy);
  tree->Branch("fit_minus_gtr300_mom_gz",          &em_fit_minus_gtr300_mom_gz);
  tree->Branch("fit_minus_hbd_mom_lx",             &em_fit_minus_hbd_mom_lx);
  tree->Branch("fit_minus_hbd_mom_ly",             &em_fit_minus_hbd_mom_ly);
  tree->Branch("fit_minus_hbd_mom_lz",             &em_fit_minus_hbd_mom_lz);
  tree->Branch("fit_minus_hbd_mom_gx",             &em_fit_minus_hbd_mom_gx);
  tree->Branch("fit_minus_hbd_mom_gy",             &em_fit_minus_hbd_mom_gy);
  tree->Branch("fit_minus_hbd_mom_gz",             &em_fit_minus_hbd_mom_gz);
  tree->Branch("fit_minus_lg_c_mom_lx",            &em_fit_minus_lg_c_mom_lx);
  tree->Branch("fit_minus_lg_c_mom_ly",            &em_fit_minus_lg_c_mom_ly);
  tree->Branch("fit_minus_lg_c_mom_lz",            &em_fit_minus_lg_c_mom_lz);
  tree->Branch("fit_minus_lg_c_mom_gx",            &em_fit_minus_lg_c_mom_gx);
  tree->Branch("fit_minus_lg_c_mom_gy",            &em_fit_minus_lg_c_mom_gy);
  tree->Branch("fit_minus_lg_c_mom_gz",            &em_fit_minus_lg_c_mom_gz);
  tree->Branch("fit_minus_lg_b_mom_lx",            &em_fit_minus_lg_b_mom_lx);
  tree->Branch("fit_minus_lg_b_mom_ly",            &em_fit_minus_lg_b_mom_ly);
  tree->Branch("fit_minus_lg_b_mom_lz",            &em_fit_minus_lg_b_mom_lz);
  tree->Branch("fit_minus_lg_b_mom_gx",            &em_fit_minus_lg_b_mom_gx);
  tree->Branch("fit_minus_lg_b_mom_gy",            &em_fit_minus_lg_b_mom_gy);
  tree->Branch("fit_minus_lg_b_mom_gz",            &em_fit_minus_lg_b_mom_gz);
  tree->Branch("fit_minus_lg_a_mom_lx",            &em_fit_minus_lg_a_mom_lx);
  tree->Branch("fit_minus_lg_a_mom_ly",            &em_fit_minus_lg_a_mom_ly);
  tree->Branch("fit_minus_lg_a_mom_lz",            &em_fit_minus_lg_a_mom_lz);
  tree->Branch("fit_minus_lg_a_mom_gx",            &em_fit_minus_lg_a_mom_gx);
  tree->Branch("fit_minus_lg_a_mom_gy",            &em_fit_minus_lg_a_mom_gy);
  tree->Branch("fit_minus_lg_a_mom_gz",            &em_fit_minus_lg_a_mom_gz);
  tree->Branch("fit_minus_tgt_minus_mom_x",        &em_fit_minus_tgt_minus_mom_x);
  tree->Branch("fit_minus_tgt_minus_mom_y",        &em_fit_minus_tgt_minus_mom_y);
  tree->Branch("fit_minus_tgt_minus_mom_z",        &em_fit_minus_tgt_minus_mom_z);
  tree->Branch("fit_minus_tgt_zero_mom_x",         &em_fit_minus_tgt_zero_mom_x);
  tree->Branch("fit_minus_tgt_zero_mom_y",         &em_fit_minus_tgt_zero_mom_y);
  tree->Branch("fit_minus_tgt_zero_mom_z",         &em_fit_minus_tgt_zero_mom_z);
  tree->Branch("fit_minus_tgt_plus_mom_x",         &em_fit_minus_tgt_plus_mom_x);
  tree->Branch("fit_minus_tgt_plus_mom_y",         &em_fit_minus_tgt_plus_mom_y);
  tree->Branch("fit_minus_tgt_plus_mom_z",         &em_fit_minus_tgt_plus_mom_z);
//  tree->Branch("res_plus_ssd_lx",                  &out_res_plus_ssd_lx);
////  tree->Branch("res_plus_ssd_ly",                  &out_res_plus_ssd_ly);
//  tree->Branch("res_plus_gtr100_lx",               &out_res_plus_gtr100_lx);
//  tree->Branch("res_plus_gtr100_ly",               &out_res_plus_gtr100_ly);
//  tree->Branch("res_plus_gtr200_lx",               &out_res_plus_gtr200_lx);
//  tree->Branch("res_plus_gtr200_ly",               &out_res_plus_gtr200_ly);
//  tree->Branch("res_plus_gtr300_lx",               &out_res_plus_gtr300_lx);
//  tree->Branch("res_plus_gtr300_ly",               &out_res_plus_gtr300_ly);
//  tree->Branch("res_minus_ssd_lx",                 &out_res_minus_ssd_lx);
////  tree->Branch("res_minus_ssd_ly",                 &out_res_minus_ssd_ly);
//  tree->Branch("res_minus_gtr100_lx",              &out_res_minus_gtr100_lx);
//  tree->Branch("res_minus_gtr100_ly",              &out_res_minus_gtr100_ly);
//  tree->Branch("res_minus_gtr200_lx",              &out_res_minus_gtr200_lx);
//  tree->Branch("res_minus_gtr200_ly",              &out_res_minus_gtr200_ly);
//  tree->Branch("res_minus_gtr300_lx",              &out_res_minus_gtr300_lx);
//  tree->Branch("res_minus_gtr300_ly",              &out_res_minus_gtr300_ly);
  tree->Branch("fit_parent_mom",                   &em_fit_parent_mom);
  tree->Branch("fit_parent_mom_x",                 &em_fit_parent_mom_x);
  tree->Branch("fit_parent_mom_y",                 &em_fit_parent_mom_y);
  tree->Branch("fit_parent_mom_z",                 &em_fit_parent_mom_z);
  tree->Branch("fit_parent_mom_theta",             &em_fit_parent_mom_theta);
  tree->Branch("fit_parent_mom_phi",               &em_fit_parent_mom_phi);
  tree->Branch("fit_parent_tgt_minus_x",           &em_fit_parent_tgt_minus_x);
  tree->Branch("fit_parent_tgt_minus_y",           &em_fit_parent_tgt_minus_y);
  tree->Branch("fit_parent_tgt_minus_flight_path", &em_fit_parent_tgt_minus_flight_path);
  tree->Branch("fit_parent_tgt_zero_x",            &em_fit_parent_tgt_zero_x);
  tree->Branch("fit_parent_tgt_zero_y",            &em_fit_parent_tgt_zero_y);
  tree->Branch("fit_parent_tgt_zero_flight_path",  &em_fit_parent_tgt_zero_flight_path);
  tree->Branch("fit_parent_tgt_plus_x",            &em_fit_parent_tgt_plus_x);
  tree->Branch("fit_parent_tgt_plus_y",            &em_fit_parent_tgt_plus_y);
  tree->Branch("fit_parent_tgt_plus_flight_path",  &em_fit_parent_tgt_plus_flight_path);
  tree->Branch("fit_parent_best_tgt_id",           &em_fit_parent_best_tgt_id);
  tree->Branch("fit_parent_best_tgt_r",            &em_fit_parent_best_tgt_r);
  tree->Branch("fit_parent_good_tgt_id_set",       &em_fit_parent_good_tgt_id_set);
  tree->Branch("fit_parent_good_tgt_ids",          &em_fit_parent_good_tgt_ids);
  tree->Branch("fit_parent_x0_y",                  &em_fit_parent_x0_y);
  tree->Branch("fit_parent_x0_z",                  &em_fit_parent_x0_z);
//  tree->Branch("proj_plus_n_hbds",                 &out_proj_plus_n_hbds);
//  tree->Branch("proj_plus_hbd_id",                 &out_proj_plus_hbd_id);
//  tree->Branch("proj_plus_hbd_lx",                 &out_proj_plus_hbd_lx);
//  tree->Branch("proj_plus_hbd_ly",                 &out_proj_plus_hbd_ly);
//  tree->Branch("proj_plus_hbd_resx",               &out_proj_plus_hbd_resx);
//  tree->Branch("proj_plus_hbd_resy",               &out_proj_plus_hbd_resy);
//  tree->Branch("proj_plus_hbd_adc",                &out_proj_plus_hbd_adc);
//  tree->Branch("proj_plus_hbd_size",               &out_proj_plus_hbd_size);
//  tree->Branch("proj_plus_hbd_eprob",              &out_proj_plus_hbd_eprob);
//  tree->Branch("proj_minus_n_hbds",                &out_proj_minus_n_hbds);
//  tree->Branch("proj_minus_hbd_id",                &out_proj_minus_hbd_id);
//  tree->Branch("proj_minus_hbd_lx",                &out_proj_minus_hbd_lx);
//  tree->Branch("proj_minus_hbd_ly",                &out_proj_minus_hbd_ly);
//  tree->Branch("proj_minus_hbd_resx",              &out_proj_minus_hbd_resx);
//  tree->Branch("proj_minus_hbd_resy",              &out_proj_minus_hbd_resy);
//  tree->Branch("proj_minus_hbd_adc",               &out_proj_minus_hbd_adc);
//  tree->Branch("proj_minus_hbd_size",              &out_proj_minus_hbd_size);
//  tree->Branch("proj_minus_hbd_eprob",             &out_proj_minus_hbd_eprob);
  return;
}

void track_analyzer_220715::ClearUsedClusterIDs() {
  for (auto& ids : used_cluster_ids) {
    ids.clear();
  }
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
      E16INFO("Invalid HBD cluster module ID: %d (Run ID: %d, Event ID: %d)", mid, run_id, event_id);
      continue;
    }
    hbd_indexs[mid - 101].emplace_back(i);
  }
  return;
}

//void track_analyzer_220715::SetLGs() {
//  for (auto& lg : lg_indexs) {
//    for (auto& lg0 : lg) {
//      lg0.clear();
//    }
//  }
//  for (int i = 0; i < n_lg_hits; ++i) {
//    auto adc = lg_hit_adc->at(i);
//    auto t   = lg_hit_t->at(i);
//    if (adc < kMinLGADC || t < kMinLGTime || t > kMaxLGTime) {
//      continue;
//    }
//    auto mid   = lg_hit_mid->at(i);
//    auto cid10 = lg_hit_cid->at(i) / 10;
//    int type;
//    if (cid10 == 0 || cid10 == 5) {
//      type = kLGTypeC;
//    } else if (cid10 == 1 || cid10 == 4) {
//      type = kLGTypeB;
//    } else {
//      type = kLGTypeA;
//    }
//    if (mid < 101 || mid > 109) {
//      E16INFO("Invalid LG hit module ID: %d (Run ID: %d, Event ID: %d)", mid, run_id, event_id);
//      continue;
//    }
//    lg_indexs[mid - 101][type].emplace_back(i);
//  }
//  return;
//}

double track_analyzer_220715::NearestRadius(int n) {
  array<TVector3, kNumTgts> tgt_poss = {TVector3(rk_proj_tgt0_gx->at(n), rk_proj_tgt0_gy->at(n), rk_proj_tgt0_gz->at(n)),
                                        TVector3(rk_proj_tgt1_gx->at(n), rk_proj_tgt1_gy->at(n), rk_proj_tgt1_gz->at(n)),
                                        TVector3(rk_proj_tgt2_gx->at(n), rk_proj_tgt2_gy->at(n), rk_proj_tgt2_gz->at(n))};
  int tgt_id = 0;
  double r2 = 10000.;
  for (int i = 0; i < kNumTgts; ++i) {
    auto tmp_r2 = tgt_poss[i].Perp2();
    if (r2 > tmp_r2) {
      tgt_id = i;
      r2 = tmp_r2;
    }
  }
  auto r = sqrt(r2);
  nearest_tgt_ids[n] = tgt_id;
  nearest_radius[n]  = r;
  return r;
}

bool track_analyzer_220715::HasAssociatedHBD(int mid, const TVector3& track_pos, double* min_res, vector<int>* _associated_hbd_indexs) {
  *min_res = 10000.;
  bool has_hbd = false;
  _associated_hbd_indexs->clear();
  for (const auto& i : hbd_indexs[mid - 101]) {
    auto cluster_pos = TVector3(hbd_cluster_x->at(i), hbd_cluster_y->at(i), 0.);
    auto res = cluster_pos - track_pos;
    auto r = res.Mag();
    if (r < *min_res) {
      *min_res = r;
    }
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
  double dummy;
  return HasAssociatedHBD(mid, track_lpos, &dummy, &associated_hbd_indexs[n]);
}

//bool track_analyzer_220715::HasAssociatedLG(array<int, kNumLGTypes> mids, const array<TVector3, kNumLGTypes>& track_poss,
//                                            double* min_res, vector<int>* _associated_lg_indexs) {
//  *min_res = 10000.;
//  bool has_lg = false;
//  _associated_lg_indexs->clear();
//  for (int t = 0; t < kNumLGTypes; ++t) {
//    auto y = track_poss[t].Y();
//    if (y < kMinLGY[t] || y > kMaxLGY[t]) {
//      continue;
//    }
//    for (const auto& i : lg_indexs[mids[t] - 101][t]) {
//      auto hit_pos = TVector3(lg_hit_x->at(i), lg_hit_y->at(i), 0.);
//      auto res = hit_pos - track_poss[t];
//      auto r = res.Mag();
//      if (r < *min_res) {
//        *min_res = r;
//      }
//      if (fabs(res.X()) > kMaxLGXResidual) {
//        continue;
//      }
//      if (fabs(res.Y()) > kMaxLGYResidual) {
//        continue;
//      }
//      has_lg = true;
//      _associated_lg_indexs->emplace_back(i);
//    }
//  }
//  return has_lg;
//}

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
  if (kUsePosAtTargetCut && !NearestRadius(n) > kMaxRadiusAtTarget) {
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
  nearest_tgt_ids.clear();
  nearest_radius.clear();
  associated_hbd_indexs.resize(n_cands);
  nearest_tgt_ids.resize(n_cands);
  nearest_radius.resize(n_cands);
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
      if (!kForgiveSameCharge && charge0 == charge1) {
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
  out_pair_order.clear();
  out_plus_rough_fit_init_pos_x.clear();
  out_plus_rough_fit_init_pos_y.clear();
  out_plus_rough_fit_init_pos_z.clear();
  out_plus_rough_fit_init_mom_x.clear();
  out_plus_rough_fit_init_mom_y.clear();
  out_plus_rough_fit_init_mom_z.clear();
  out_minus_rough_fit_init_pos_x.clear();
  out_minus_rough_fit_init_pos_y.clear();
  out_minus_rough_fit_init_pos_z.clear();
  out_minus_rough_fit_init_mom_x.clear();
  out_minus_rough_fit_init_mom_y.clear();
  out_minus_rough_fit_init_mom_z.clear();
  out_plus_single_fit_init_pos_x.clear();
  out_plus_single_fit_init_pos_y.clear();
  out_plus_single_fit_init_pos_z.clear();
  out_plus_single_fit_init_mom_x.clear();
  out_plus_single_fit_init_mom_y.clear();
  out_plus_single_fit_init_mom_z.clear();
  out_minus_single_fit_init_pos_x.clear();
  out_minus_single_fit_init_pos_y.clear();
  out_minus_single_fit_init_pos_z.clear();
  out_minus_single_fit_init_mom_x.clear();
  out_minus_single_fit_init_mom_y.clear();
  out_minus_single_fit_init_mom_z.clear();
  out_plus_track_id.clear();
  out_plus_charge_id.clear();
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
  out_minus_charge_id.clear();
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
  out_plus_chi2.clear();
  out_minus_chi2.clear();
  out_flag.clear();
  out_distance.clear();
  out_plus_nearest_tgt_id.clear();
  out_plus_nearest_radius.clear();
  out_minus_nearest_tgt_id.clear();
  out_minus_nearest_radius.clear();
  out_dir_id.clear();
  out_vtx_x.clear();
  out_vtx_y.clear();
  out_vtx_z.clear();
  out_plus_pos_x.clear();
  out_plus_pos_y.clear();
  out_plus_pos_z.clear();
  out_minus_pos_x.clear();
  out_minus_pos_y.clear();
  out_minus_pos_z.clear();
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
  out_simple_best_tgt_id.clear();
  out_simple_best_tgt_r.clear();
  out_ee_mass_at_best_tgt.clear();
  out_pipi_mass_at_best_tgt.clear();
  out_pip_mass_at_best_tgt.clear();
  out_kk_mass_at_best_tgt.clear();
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
  out_fit_plus_x0_y.clear();
  out_fit_plus_x0_z.clear();
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
  out_fit_minus_x0_y.clear();
  out_fit_minus_x0_z.clear();
  out_fit_plus_ssd_mom_lx.clear();
  out_fit_plus_ssd_mom_ly.clear();
  out_fit_plus_ssd_mom_lz.clear();
  out_fit_plus_ssd_mom_gx.clear();
  out_fit_plus_ssd_mom_gy.clear();
  out_fit_plus_ssd_mom_gz.clear();
  out_fit_plus_gtr100_mom_lx.clear();
  out_fit_plus_gtr100_mom_ly.clear();
  out_fit_plus_gtr100_mom_lz.clear();
  out_fit_plus_gtr100_mom_gx.clear();
  out_fit_plus_gtr100_mom_gy.clear();
  out_fit_plus_gtr100_mom_gz.clear();
  out_fit_plus_gtr200_mom_lx.clear();
  out_fit_plus_gtr200_mom_ly.clear();
  out_fit_plus_gtr200_mom_lz.clear();
  out_fit_plus_gtr200_mom_gx.clear();
  out_fit_plus_gtr200_mom_gy.clear();
  out_fit_plus_gtr200_mom_gz.clear();
  out_fit_plus_gtr300_mom_lx.clear();
  out_fit_plus_gtr300_mom_ly.clear();
  out_fit_plus_gtr300_mom_lz.clear();
  out_fit_plus_gtr300_mom_gx.clear();
  out_fit_plus_gtr300_mom_gy.clear();
  out_fit_plus_gtr300_mom_gz.clear();
  out_fit_plus_hbd_mom_lx.clear();
  out_fit_plus_hbd_mom_ly.clear();
  out_fit_plus_hbd_mom_lz.clear();
  out_fit_plus_hbd_mom_gx.clear();
  out_fit_plus_hbd_mom_gy.clear();
  out_fit_plus_hbd_mom_gz.clear();
  out_fit_plus_lg_c_mom_lx.clear();
  out_fit_plus_lg_c_mom_ly.clear();
  out_fit_plus_lg_c_mom_lz.clear();
  out_fit_plus_lg_c_mom_gx.clear();
  out_fit_plus_lg_c_mom_gy.clear();
  out_fit_plus_lg_c_mom_gz.clear();
  out_fit_plus_lg_b_mom_lx.clear();
  out_fit_plus_lg_b_mom_ly.clear();
  out_fit_plus_lg_b_mom_lz.clear();
  out_fit_plus_lg_b_mom_gx.clear();
  out_fit_plus_lg_b_mom_gy.clear();
  out_fit_plus_lg_b_mom_gz.clear();
  out_fit_plus_lg_a_mom_lx.clear();
  out_fit_plus_lg_a_mom_ly.clear();
  out_fit_plus_lg_a_mom_lz.clear();
  out_fit_plus_lg_a_mom_gx.clear();
  out_fit_plus_lg_a_mom_gy.clear();
  out_fit_plus_lg_a_mom_gz.clear();
  out_fit_plus_tgt_minus_mom_x.clear();
  out_fit_plus_tgt_minus_mom_y.clear();
  out_fit_plus_tgt_minus_mom_z.clear();
  out_fit_plus_tgt_zero_mom_x.clear();
  out_fit_plus_tgt_zero_mom_y.clear();
  out_fit_plus_tgt_zero_mom_z.clear();
  out_fit_plus_tgt_plus_mom_x.clear();
  out_fit_plus_tgt_plus_mom_y.clear();
  out_fit_plus_tgt_plus_mom_z.clear();
  out_fit_minus_ssd_mom_lx.clear();
  out_fit_minus_ssd_mom_ly.clear();
  out_fit_minus_ssd_mom_lz.clear();
  out_fit_minus_ssd_mom_gx.clear();
  out_fit_minus_ssd_mom_gy.clear();
  out_fit_minus_ssd_mom_gz.clear();
  out_fit_minus_gtr100_mom_lx.clear();
  out_fit_minus_gtr100_mom_ly.clear();
  out_fit_minus_gtr100_mom_lz.clear();
  out_fit_minus_gtr100_mom_gx.clear();
  out_fit_minus_gtr100_mom_gy.clear();
  out_fit_minus_gtr100_mom_gz.clear();
  out_fit_minus_gtr200_mom_lx.clear();
  out_fit_minus_gtr200_mom_ly.clear();
  out_fit_minus_gtr200_mom_lz.clear();
  out_fit_minus_gtr200_mom_gx.clear();
  out_fit_minus_gtr200_mom_gy.clear();
  out_fit_minus_gtr200_mom_gz.clear();
  out_fit_minus_gtr300_mom_lx.clear();
  out_fit_minus_gtr300_mom_ly.clear();
  out_fit_minus_gtr300_mom_lz.clear();
  out_fit_minus_gtr300_mom_gx.clear();
  out_fit_minus_gtr300_mom_gy.clear();
  out_fit_minus_gtr300_mom_gz.clear();
  out_fit_minus_hbd_mom_lx.clear();
  out_fit_minus_hbd_mom_ly.clear();
  out_fit_minus_hbd_mom_lz.clear();
  out_fit_minus_hbd_mom_gx.clear();
  out_fit_minus_hbd_mom_gy.clear();
  out_fit_minus_hbd_mom_gz.clear();
  out_fit_minus_lg_c_mom_lx.clear();
  out_fit_minus_lg_c_mom_ly.clear();
  out_fit_minus_lg_c_mom_lz.clear();
  out_fit_minus_lg_c_mom_gx.clear();
  out_fit_minus_lg_c_mom_gy.clear();
  out_fit_minus_lg_c_mom_gz.clear();
  out_fit_minus_lg_b_mom_lx.clear();
  out_fit_minus_lg_b_mom_ly.clear();
  out_fit_minus_lg_b_mom_lz.clear();
  out_fit_minus_lg_b_mom_gx.clear();
  out_fit_minus_lg_b_mom_gy.clear();
  out_fit_minus_lg_b_mom_gz.clear();
  out_fit_minus_lg_a_mom_lx.clear();
  out_fit_minus_lg_a_mom_ly.clear();
  out_fit_minus_lg_a_mom_lz.clear();
  out_fit_minus_lg_a_mom_gx.clear();
  out_fit_minus_lg_a_mom_gy.clear();
  out_fit_minus_lg_a_mom_gz.clear();
  out_fit_minus_tgt_minus_mom_x.clear();
  out_fit_minus_tgt_minus_mom_y.clear();
  out_fit_minus_tgt_minus_mom_z.clear();
  out_fit_minus_tgt_zero_mom_x.clear();
  out_fit_minus_tgt_zero_mom_y.clear();
  out_fit_minus_tgt_zero_mom_z.clear();
  out_fit_minus_tgt_plus_mom_x.clear();
  out_fit_minus_tgt_plus_mom_y.clear();
  out_fit_minus_tgt_plus_mom_z.clear();
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
  out_fit_parent_mom.clear();
  out_fit_parent_mom_x.clear();
  out_fit_parent_mom_y.clear();
  out_fit_parent_mom_z.clear();
  out_fit_parent_mom_theta.clear();
  out_fit_parent_mom_phi.clear();
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
  out_fit_parent_best_tgt_r.clear();
  out_fit_parent_good_tgt_id_set.clear();
  out_fit_parent_good_tgt_ids.clear();
  out_fit_parent_x0_y.clear();
  out_fit_parent_x0_z.clear();
  out_proj_plus_n_hbds.clear();
  out_proj_plus_hbd_min_res.clear();
  out_proj_plus_hbd_id.clear();
  out_proj_plus_hbd_lx.clear();
  out_proj_plus_hbd_ly.clear();
  out_proj_plus_hbd_resx.clear();
  out_proj_plus_hbd_resy.clear();
  out_proj_plus_hbd_adc.clear();
  out_proj_plus_hbd_size.clear();
  out_proj_plus_hbd_eprob.clear();
  out_proj_minus_n_hbds.clear();
  out_proj_minus_hbd_min_res.clear();
  out_proj_minus_hbd_id.clear();
  out_proj_minus_hbd_lx.clear();
  out_proj_minus_hbd_ly.clear();
  out_proj_minus_hbd_resx.clear();
  out_proj_minus_hbd_resy.clear();
  out_proj_minus_hbd_adc.clear();
  out_proj_minus_hbd_size.clear();
  out_proj_minus_hbd_eprob.clear();
out_tmp_fit_plus_x0_flag.clear();
out_tmp_fit_plus_x0_n_cross.clear();
out_tmp_fit_plus_x0_pos_y.clear();
out_tmp_fit_plus_x0_pos_z.clear();
out_tmp_fit_plus_x0_mom_x.clear();
out_tmp_fit_plus_x0_mom_y.clear();
out_tmp_fit_plus_x0_mom_z.clear();
out_tmp_fit_minus_x0_flag.clear();
out_tmp_fit_minus_x0_n_cross.clear();
out_tmp_fit_minus_x0_pos_y.clear();
out_tmp_fit_minus_x0_pos_z.clear();
out_tmp_fit_minus_x0_mom_x.clear();
out_tmp_fit_minus_x0_mom_y.clear();
out_tmp_fit_minus_x0_mom_z.clear();
#ifdef TMP_SOME_Z
out_tmp_plus_static_flag.clear();
out_tmp_plus_static_pos_x.clear();
out_tmp_plus_static_pos_y.clear();
out_tmp_plus_static_pos_z.clear();
out_tmp_plus_static_mom_x.clear();
out_tmp_plus_static_mom_y.clear();
out_tmp_plus_static_mom_z.clear();
out_tmp_minus_static_flag.clear();
out_tmp_minus_static_pos_x.clear();
out_tmp_minus_static_pos_y.clear();
out_tmp_minus_static_pos_z.clear();
out_tmp_minus_static_mom_x.clear();
out_tmp_minus_static_mom_y.clear();
out_tmp_minus_static_mom_z.clear();
out_tmp_static_distance.clear();
out_tmp_static_mom_angle.clear();
out_tmp_static_pipi_mass.clear();
out_tmp_dynamic_chi2.clear();
out_tmp_dynamic_vtx_x.clear();
out_tmp_dynamic_vtx_y.clear();
out_tmp_dynamic_vtx_z.clear();
out_tmp_plus_dynamic_flag.clear();
out_tmp_plus_dynamic_pos_x.clear();
out_tmp_plus_dynamic_pos_y.clear();
out_tmp_plus_dynamic_pos_z.clear();
out_tmp_plus_dynamic_mom_x.clear();
out_tmp_plus_dynamic_mom_y.clear();
out_tmp_plus_dynamic_mom_z.clear();
out_tmp_minus_dynamic_flag.clear();
out_tmp_minus_dynamic_pos_x.clear();
out_tmp_minus_dynamic_pos_y.clear();
out_tmp_minus_dynamic_pos_z.clear();
out_tmp_minus_dynamic_mom_x.clear();
out_tmp_minus_dynamic_mom_y.clear();
out_tmp_minus_dynamic_mom_z.clear();
out_tmp_dynamic_distance.clear();
out_tmp_dynamic_mom_angle.clear();
out_tmp_dynamic_pipi_mass.clear();
#endif // TMP_SOME_Z
#ifdef TMP_ZX_NEAREST
out_tmp_zx_flag.clear();
out_tmp_zx_distance.clear();
out_tmp_zx_vtx_x.clear();
out_tmp_zx_vtx_y.clear();
out_tmp_zx_vtx_z.clear();
out_tmp_zx_plus_pos_x.clear();
out_tmp_zx_plus_pos_y.clear();
out_tmp_zx_plus_pos_z.clear();
out_tmp_zx_minus_pos_x.clear();
out_tmp_zx_minus_pos_y.clear();
out_tmp_zx_minus_pos_z.clear();
out_tmp_zx_plus_mom_x.clear();
out_tmp_zx_plus_mom_y.clear();
out_tmp_zx_plus_mom_z.clear();
out_tmp_zx_minus_mom_x.clear();
out_tmp_zx_minus_mom_y.clear();
out_tmp_zx_minus_mom_z.clear();
out_tmp_zx_pipi_mass.clear();
#endif // TMP_ZX_NEAREST
  out_pair_order.resize(out_n_pairs);
  out_plus_rough_fit_init_pos_x.resize(out_n_pairs);
  out_plus_rough_fit_init_pos_y.resize(out_n_pairs);
  out_plus_rough_fit_init_pos_z.resize(out_n_pairs);
  out_plus_rough_fit_init_mom_x.resize(out_n_pairs);
  out_plus_rough_fit_init_mom_y.resize(out_n_pairs);
  out_plus_rough_fit_init_mom_z.resize(out_n_pairs);
  out_minus_rough_fit_init_pos_x.resize(out_n_pairs);
  out_minus_rough_fit_init_pos_y.resize(out_n_pairs);
  out_minus_rough_fit_init_pos_z.resize(out_n_pairs);
  out_minus_rough_fit_init_mom_x.resize(out_n_pairs);
  out_minus_rough_fit_init_mom_y.resize(out_n_pairs);
  out_minus_rough_fit_init_mom_z.resize(out_n_pairs);
  out_plus_single_fit_init_pos_x.resize(out_n_pairs);
  out_plus_single_fit_init_pos_y.resize(out_n_pairs);
  out_plus_single_fit_init_pos_z.resize(out_n_pairs);
  out_plus_single_fit_init_mom_x.resize(out_n_pairs);
  out_plus_single_fit_init_mom_y.resize(out_n_pairs);
  out_plus_single_fit_init_mom_z.resize(out_n_pairs);
  out_minus_single_fit_init_pos_x.resize(out_n_pairs);
  out_minus_single_fit_init_pos_y.resize(out_n_pairs);
  out_minus_single_fit_init_pos_z.resize(out_n_pairs);
  out_minus_single_fit_init_mom_x.resize(out_n_pairs);
  out_minus_single_fit_init_mom_y.resize(out_n_pairs);
  out_minus_single_fit_init_mom_z.resize(out_n_pairs);
  out_plus_track_id.resize(out_n_pairs);
  out_plus_charge_id.resize(out_n_pairs);
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
  out_minus_charge_id.resize(out_n_pairs);
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
  out_plus_chi2.resize(out_n_pairs);
  out_minus_chi2.resize(out_n_pairs);
  out_flag.resize(out_n_pairs);
  out_distance.resize(out_n_pairs);
  out_plus_nearest_tgt_id.resize(out_n_pairs);
  out_plus_nearest_radius.resize(out_n_pairs);
  out_minus_nearest_tgt_id.resize(out_n_pairs);
  out_minus_nearest_radius.resize(out_n_pairs);
  out_dir_id.resize(out_n_pairs);
  out_vtx_x.resize(out_n_pairs);
  out_vtx_y.resize(out_n_pairs);
  out_vtx_z.resize(out_n_pairs);
  out_plus_pos_x.resize(out_n_pairs);
  out_plus_pos_y.resize(out_n_pairs);
  out_plus_pos_z.resize(out_n_pairs);
  out_minus_pos_x.resize(out_n_pairs);
  out_minus_pos_y.resize(out_n_pairs);
  out_minus_pos_z.resize(out_n_pairs);
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
  out_simple_best_tgt_id.resize(out_n_pairs);
  out_simple_best_tgt_r.resize(out_n_pairs);
  out_ee_mass_at_best_tgt.resize(out_n_pairs);
  out_pipi_mass_at_best_tgt.resize(out_n_pairs);
  out_pip_mass_at_best_tgt.resize(out_n_pairs);
  out_kk_mass_at_best_tgt.resize(out_n_pairs);
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
  out_fit_plus_x0_y.resize(out_n_pairs);
  out_fit_plus_x0_z.resize(out_n_pairs);
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
  out_fit_minus_x0_y.resize(out_n_pairs);
  out_fit_minus_x0_z.resize(out_n_pairs);
  out_fit_plus_ssd_mom_lx.resize(out_n_pairs);
  out_fit_plus_ssd_mom_ly.resize(out_n_pairs);
  out_fit_plus_ssd_mom_lz.resize(out_n_pairs);
  out_fit_plus_ssd_mom_gx.resize(out_n_pairs);
  out_fit_plus_ssd_mom_gy.resize(out_n_pairs);
  out_fit_plus_ssd_mom_gz.resize(out_n_pairs);
  out_fit_plus_gtr100_mom_lx.resize(out_n_pairs);
  out_fit_plus_gtr100_mom_ly.resize(out_n_pairs);
  out_fit_plus_gtr100_mom_lz.resize(out_n_pairs);
  out_fit_plus_gtr100_mom_gx.resize(out_n_pairs);
  out_fit_plus_gtr100_mom_gy.resize(out_n_pairs);
  out_fit_plus_gtr100_mom_gz.resize(out_n_pairs);
  out_fit_plus_gtr200_mom_lx.resize(out_n_pairs);
  out_fit_plus_gtr200_mom_ly.resize(out_n_pairs);
  out_fit_plus_gtr200_mom_lz.resize(out_n_pairs);
  out_fit_plus_gtr200_mom_gx.resize(out_n_pairs);
  out_fit_plus_gtr200_mom_gy.resize(out_n_pairs);
  out_fit_plus_gtr200_mom_gz.resize(out_n_pairs);
  out_fit_plus_gtr300_mom_lx.resize(out_n_pairs);
  out_fit_plus_gtr300_mom_ly.resize(out_n_pairs);
  out_fit_plus_gtr300_mom_lz.resize(out_n_pairs);
  out_fit_plus_gtr300_mom_gx.resize(out_n_pairs);
  out_fit_plus_gtr300_mom_gy.resize(out_n_pairs);
  out_fit_plus_gtr300_mom_gz.resize(out_n_pairs);
  out_fit_plus_hbd_mom_lx.resize(out_n_pairs);
  out_fit_plus_hbd_mom_ly.resize(out_n_pairs);
  out_fit_plus_hbd_mom_lz.resize(out_n_pairs);
  out_fit_plus_hbd_mom_gx.resize(out_n_pairs);
  out_fit_plus_hbd_mom_gy.resize(out_n_pairs);
  out_fit_plus_hbd_mom_gz.resize(out_n_pairs);
  out_fit_plus_lg_c_mom_lx.resize(out_n_pairs);
  out_fit_plus_lg_c_mom_ly.resize(out_n_pairs);
  out_fit_plus_lg_c_mom_lz.resize(out_n_pairs);
  out_fit_plus_lg_c_mom_gx.resize(out_n_pairs);
  out_fit_plus_lg_c_mom_gy.resize(out_n_pairs);
  out_fit_plus_lg_c_mom_gz.resize(out_n_pairs);
  out_fit_plus_lg_b_mom_lx.resize(out_n_pairs);
  out_fit_plus_lg_b_mom_ly.resize(out_n_pairs);
  out_fit_plus_lg_b_mom_lz.resize(out_n_pairs);
  out_fit_plus_lg_b_mom_gx.resize(out_n_pairs);
  out_fit_plus_lg_b_mom_gy.resize(out_n_pairs);
  out_fit_plus_lg_b_mom_gz.resize(out_n_pairs);
  out_fit_plus_lg_a_mom_lx.resize(out_n_pairs);
  out_fit_plus_lg_a_mom_ly.resize(out_n_pairs);
  out_fit_plus_lg_a_mom_lz.resize(out_n_pairs);
  out_fit_plus_lg_a_mom_gx.resize(out_n_pairs);
  out_fit_plus_lg_a_mom_gy.resize(out_n_pairs);
  out_fit_plus_lg_a_mom_gz.resize(out_n_pairs);
  out_fit_plus_tgt_minus_mom_x.resize(out_n_pairs);
  out_fit_plus_tgt_minus_mom_y.resize(out_n_pairs);
  out_fit_plus_tgt_minus_mom_z.resize(out_n_pairs);
  out_fit_plus_tgt_zero_mom_x.resize(out_n_pairs);
  out_fit_plus_tgt_zero_mom_y.resize(out_n_pairs);
  out_fit_plus_tgt_zero_mom_z.resize(out_n_pairs);
  out_fit_plus_tgt_plus_mom_x.resize(out_n_pairs);
  out_fit_plus_tgt_plus_mom_y.resize(out_n_pairs);
  out_fit_plus_tgt_plus_mom_z.resize(out_n_pairs);
  out_fit_minus_ssd_mom_lx.resize(out_n_pairs);
  out_fit_minus_ssd_mom_ly.resize(out_n_pairs);
  out_fit_minus_ssd_mom_lz.resize(out_n_pairs);
  out_fit_minus_ssd_mom_gx.resize(out_n_pairs);
  out_fit_minus_ssd_mom_gy.resize(out_n_pairs);
  out_fit_minus_ssd_mom_gz.resize(out_n_pairs);
  out_fit_minus_gtr100_mom_lx.resize(out_n_pairs);
  out_fit_minus_gtr100_mom_ly.resize(out_n_pairs);
  out_fit_minus_gtr100_mom_lz.resize(out_n_pairs);
  out_fit_minus_gtr100_mom_gx.resize(out_n_pairs);
  out_fit_minus_gtr100_mom_gy.resize(out_n_pairs);
  out_fit_minus_gtr100_mom_gz.resize(out_n_pairs);
  out_fit_minus_gtr200_mom_lx.resize(out_n_pairs);
  out_fit_minus_gtr200_mom_ly.resize(out_n_pairs);
  out_fit_minus_gtr200_mom_lz.resize(out_n_pairs);
  out_fit_minus_gtr200_mom_gx.resize(out_n_pairs);
  out_fit_minus_gtr200_mom_gy.resize(out_n_pairs);
  out_fit_minus_gtr200_mom_gz.resize(out_n_pairs);
  out_fit_minus_gtr300_mom_lx.resize(out_n_pairs);
  out_fit_minus_gtr300_mom_ly.resize(out_n_pairs);
  out_fit_minus_gtr300_mom_lz.resize(out_n_pairs);
  out_fit_minus_gtr300_mom_gx.resize(out_n_pairs);
  out_fit_minus_gtr300_mom_gy.resize(out_n_pairs);
  out_fit_minus_gtr300_mom_gz.resize(out_n_pairs);
  out_fit_minus_hbd_mom_lx.resize(out_n_pairs);
  out_fit_minus_hbd_mom_ly.resize(out_n_pairs);
  out_fit_minus_hbd_mom_lz.resize(out_n_pairs);
  out_fit_minus_hbd_mom_gx.resize(out_n_pairs);
  out_fit_minus_hbd_mom_gy.resize(out_n_pairs);
  out_fit_minus_hbd_mom_gz.resize(out_n_pairs);
  out_fit_minus_lg_c_mom_lx.resize(out_n_pairs);
  out_fit_minus_lg_c_mom_ly.resize(out_n_pairs);
  out_fit_minus_lg_c_mom_lz.resize(out_n_pairs);
  out_fit_minus_lg_c_mom_gx.resize(out_n_pairs);
  out_fit_minus_lg_c_mom_gy.resize(out_n_pairs);
  out_fit_minus_lg_c_mom_gz.resize(out_n_pairs);
  out_fit_minus_lg_b_mom_lx.resize(out_n_pairs);
  out_fit_minus_lg_b_mom_ly.resize(out_n_pairs);
  out_fit_minus_lg_b_mom_lz.resize(out_n_pairs);
  out_fit_minus_lg_b_mom_gx.resize(out_n_pairs);
  out_fit_minus_lg_b_mom_gy.resize(out_n_pairs);
  out_fit_minus_lg_b_mom_gz.resize(out_n_pairs);
  out_fit_minus_lg_a_mom_lx.resize(out_n_pairs);
  out_fit_minus_lg_a_mom_ly.resize(out_n_pairs);
  out_fit_minus_lg_a_mom_lz.resize(out_n_pairs);
  out_fit_minus_lg_a_mom_gx.resize(out_n_pairs);
  out_fit_minus_lg_a_mom_gy.resize(out_n_pairs);
  out_fit_minus_lg_a_mom_gz.resize(out_n_pairs);
  out_fit_minus_tgt_minus_mom_x.resize(out_n_pairs);
  out_fit_minus_tgt_minus_mom_y.resize(out_n_pairs);
  out_fit_minus_tgt_minus_mom_z.resize(out_n_pairs);
  out_fit_minus_tgt_zero_mom_x.resize(out_n_pairs);
  out_fit_minus_tgt_zero_mom_y.resize(out_n_pairs);
  out_fit_minus_tgt_zero_mom_z.resize(out_n_pairs);
  out_fit_minus_tgt_plus_mom_x.resize(out_n_pairs);
  out_fit_minus_tgt_plus_mom_y.resize(out_n_pairs);
  out_fit_minus_tgt_plus_mom_z.resize(out_n_pairs);
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
  out_fit_parent_mom.resize(out_n_pairs);
  out_fit_parent_mom_x.resize(out_n_pairs);
  out_fit_parent_mom_y.resize(out_n_pairs);
  out_fit_parent_mom_z.resize(out_n_pairs);
  out_fit_parent_mom_theta.resize(out_n_pairs);
  out_fit_parent_mom_phi.resize(out_n_pairs);
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
  out_fit_parent_best_tgt_r.resize(out_n_pairs);
  out_fit_parent_good_tgt_id_set.resize(out_n_pairs);
  out_fit_parent_good_tgt_ids.resize(out_n_pairs);
  out_fit_parent_x0_y.resize(out_n_pairs);
  out_fit_parent_x0_z.resize(out_n_pairs);
  out_proj_plus_n_hbds.resize(out_n_pairs);
  out_proj_plus_hbd_min_res.resize(out_n_pairs);
  out_proj_plus_hbd_id.resize(out_n_pairs);
  out_proj_plus_hbd_lx.resize(out_n_pairs);
  out_proj_plus_hbd_ly.resize(out_n_pairs);
  out_proj_plus_hbd_resx.resize(out_n_pairs);
  out_proj_plus_hbd_resy.resize(out_n_pairs);
  out_proj_plus_hbd_adc.resize(out_n_pairs);
  out_proj_plus_hbd_size.resize(out_n_pairs);
  out_proj_plus_hbd_eprob.resize(out_n_pairs);
  out_proj_minus_n_hbds.resize(out_n_pairs);
  out_proj_minus_hbd_min_res.resize(out_n_pairs);
  out_proj_minus_hbd_id.resize(out_n_pairs);
  out_proj_minus_hbd_lx.resize(out_n_pairs);
  out_proj_minus_hbd_ly.resize(out_n_pairs);
  out_proj_minus_hbd_resx.resize(out_n_pairs);
  out_proj_minus_hbd_resy.resize(out_n_pairs);
  out_proj_minus_hbd_adc.resize(out_n_pairs);
  out_proj_minus_hbd_size.resize(out_n_pairs);
  out_proj_minus_hbd_eprob.resize(out_n_pairs);
out_tmp_fit_plus_x0_flag.resize(out_n_pairs);
out_tmp_fit_plus_x0_n_cross.resize(out_n_pairs);
out_tmp_fit_plus_x0_pos_y.resize(out_n_pairs);
out_tmp_fit_plus_x0_pos_z.resize(out_n_pairs);
out_tmp_fit_plus_x0_mom_x.resize(out_n_pairs);
out_tmp_fit_plus_x0_mom_y.resize(out_n_pairs);
out_tmp_fit_plus_x0_mom_z.resize(out_n_pairs);
out_tmp_fit_minus_x0_flag.resize(out_n_pairs);
out_tmp_fit_minus_x0_n_cross.resize(out_n_pairs);
out_tmp_fit_minus_x0_pos_y.resize(out_n_pairs);
out_tmp_fit_minus_x0_pos_z.resize(out_n_pairs);
out_tmp_fit_minus_x0_mom_x.resize(out_n_pairs);
out_tmp_fit_minus_x0_mom_y.resize(out_n_pairs);
out_tmp_fit_minus_x0_mom_z.resize(out_n_pairs);
#ifdef TMP_SOME_Z
out_tmp_plus_static_flag.resize(out_n_pairs);
out_tmp_plus_static_pos_x.resize(out_n_pairs);
out_tmp_plus_static_pos_y.resize(out_n_pairs);
out_tmp_plus_static_pos_z.resize(out_n_pairs);
out_tmp_plus_static_mom_x.resize(out_n_pairs);
out_tmp_plus_static_mom_y.resize(out_n_pairs);
out_tmp_plus_static_mom_z.resize(out_n_pairs);
out_tmp_minus_static_flag.resize(out_n_pairs);
out_tmp_minus_static_pos_x.resize(out_n_pairs);
out_tmp_minus_static_pos_y.resize(out_n_pairs);
out_tmp_minus_static_pos_z.resize(out_n_pairs);
out_tmp_minus_static_mom_x.resize(out_n_pairs);
out_tmp_minus_static_mom_y.resize(out_n_pairs);
out_tmp_minus_static_mom_z.resize(out_n_pairs);
out_tmp_static_distance.resize(out_n_pairs);
out_tmp_static_mom_angle.resize(out_n_pairs);
out_tmp_static_pipi_mass.resize(out_n_pairs);
out_tmp_dynamic_chi2.resize(out_n_pairs);
out_tmp_dynamic_vtx_x.resize(out_n_pairs);
out_tmp_dynamic_vtx_y.resize(out_n_pairs);
out_tmp_dynamic_vtx_z.resize(out_n_pairs);
out_tmp_plus_dynamic_flag.resize(out_n_pairs);
out_tmp_plus_dynamic_pos_x.resize(out_n_pairs);
out_tmp_plus_dynamic_pos_y.resize(out_n_pairs);
out_tmp_plus_dynamic_pos_z.resize(out_n_pairs);
out_tmp_plus_dynamic_mom_x.resize(out_n_pairs);
out_tmp_plus_dynamic_mom_y.resize(out_n_pairs);
out_tmp_plus_dynamic_mom_z.resize(out_n_pairs);
out_tmp_minus_dynamic_flag.resize(out_n_pairs);
out_tmp_minus_dynamic_pos_x.resize(out_n_pairs);
out_tmp_minus_dynamic_pos_y.resize(out_n_pairs);
out_tmp_minus_dynamic_pos_z.resize(out_n_pairs);
out_tmp_minus_dynamic_mom_x.resize(out_n_pairs);
out_tmp_minus_dynamic_mom_y.resize(out_n_pairs);
out_tmp_minus_dynamic_mom_z.resize(out_n_pairs);
out_tmp_dynamic_distance.resize(out_n_pairs);
out_tmp_dynamic_mom_angle.resize(out_n_pairs);
out_tmp_dynamic_pipi_mass.resize(out_n_pairs);
#endif // TMP_SOME_Z
#ifdef TMP_ZX_NEAREST
out_tmp_zx_flag.resize(out_n_pairs);
out_tmp_zx_distance.resize(out_n_pairs);
out_tmp_zx_vtx_x.resize(out_n_pairs);
out_tmp_zx_vtx_y.resize(out_n_pairs);
out_tmp_zx_vtx_z.resize(out_n_pairs);
out_tmp_zx_plus_pos_x.resize(out_n_pairs);
out_tmp_zx_plus_pos_y.resize(out_n_pairs);
out_tmp_zx_plus_pos_z.resize(out_n_pairs);
out_tmp_zx_minus_pos_x.resize(out_n_pairs);
out_tmp_zx_minus_pos_y.resize(out_n_pairs);
out_tmp_zx_minus_pos_z.resize(out_n_pairs);
out_tmp_zx_plus_mom_x.resize(out_n_pairs);
out_tmp_zx_plus_mom_y.resize(out_n_pairs);
out_tmp_zx_plus_mom_z.resize(out_n_pairs);
out_tmp_zx_minus_mom_x.resize(out_n_pairs);
out_tmp_zx_minus_mom_y.resize(out_n_pairs);
out_tmp_zx_minus_mom_z.resize(out_n_pairs);
out_tmp_zx_pipi_mass.resize(out_n_pairs);
#endif // TMP_ZX_NEAREST
  return;
}

//void track_analyzer_220715::ClearEMBranches() {
//  em_plus_run_id.clear();
//  em_plus_event_id.clear();
//  em_plus_n_cands.clear();
////  std::vector<int> em_plus_n_pairs;
//  em_plus_track_id.clear();
//  em_minus_run_id.clear();
//  em_minus_event_id.clear();
//  em_minus_n_cands.clear();
////  std::vector<int> em_minus_n_pairs;
//  em_minus_track_id.clear();
////// single fit info. chi2, ...
////  // Hit
////  std::vector<int>    out_plus_track_id;
////  std::vector<int>    out_hit_plus_ssd_id;
////  std::vector<double> out_hit_plus_ssd_lx;
////  std::vector<double> out_hit_plus_ssd_t;
////  std::vector<double> out_hit_plus_ssd_adc;
////  std::vector<int>    out_hit_plus_ssd_size;
////  std::vector<int>    out_hit_plus_gtr100_xid;
////  std::vector<int>    out_hit_plus_gtr100_yid;
////  std::vector<double> out_hit_plus_gtr100_lx;
////  std::vector<double> out_hit_plus_gtr100_ly;
////  std::vector<double> out_hit_plus_gtr100_xt;
////  std::vector<double> out_hit_plus_gtr100_yt;
////  std::vector<double> out_hit_plus_gtr100_xadc;
////  std::vector<double> out_hit_plus_gtr100_yadc;
////  std::vector<int>    out_hit_plus_gtr100_xsize;
////  std::vector<int>    out_hit_plus_gtr100_ysize;
////  std::vector<int>    out_hit_plus_gtr200_xid;
////  std::vector<int>    out_hit_plus_gtr200_yid;
////  std::vector<double> out_hit_plus_gtr200_lx;
////  std::vector<double> out_hit_plus_gtr200_ly;
////  std::vector<double> out_hit_plus_gtr200_xt;
////  std::vector<double> out_hit_plus_gtr200_yt;
////  std::vector<double> out_hit_plus_gtr200_xadc;
////  std::vector<double> out_hit_plus_gtr200_yadc;
////  std::vector<int>    out_hit_plus_gtr200_xsize;
////  std::vector<int>    out_hit_plus_gtr200_ysize;
////  std::vector<int>    out_hit_plus_gtr300_xid;
////  std::vector<int>    out_hit_plus_gtr300_yid;
////  std::vector<double> out_hit_plus_gtr300_lx;
////  std::vector<double> out_hit_plus_gtr300_ly;
////  std::vector<double> out_hit_plus_gtr300_xt;
////  std::vector<double> out_hit_plus_gtr300_yt;
////  std::vector<double> out_hit_plus_gtr300_xadc;
////  std::vector<double> out_hit_plus_gtr300_yadc;
////  std::vector<int>    out_hit_plus_gtr300_xsize;
////  std::vector<int>    out_hit_plus_gtr300_ysize;
////  std::vector<int>    out_minus_track_id;
////  std::vector<int>    out_hit_minus_ssd_id;
////  std::vector<double> out_hit_minus_ssd_lx;
////  std::vector<double> out_hit_minus_ssd_t;
////  std::vector<double> out_hit_minus_ssd_adc;
////  std::vector<int>    out_hit_minus_ssd_size;
////  std::vector<int>    out_hit_minus_gtr100_xid;
////  std::vector<int>    out_hit_minus_gtr100_yid;
////  std::vector<double> out_hit_minus_gtr100_lx;
////  std::vector<double> out_hit_minus_gtr100_ly;
////  std::vector<double> out_hit_minus_gtr100_xt;
////  std::vector<double> out_hit_minus_gtr100_yt;
////  std::vector<double> out_hit_minus_gtr100_xadc;
////  std::vector<double> out_hit_minus_gtr100_yadc;
////  std::vector<int>    out_hit_minus_gtr100_xsize;
////  std::vector<int>    out_hit_minus_gtr100_ysize;
////  std::vector<int>    out_hit_minus_gtr200_xid;
////  std::vector<int>    out_hit_minus_gtr200_yid;
////  std::vector<double> out_hit_minus_gtr200_lx;
////  std::vector<double> out_hit_minus_gtr200_ly;
////  std::vector<double> out_hit_minus_gtr200_xt;
////  std::vector<double> out_hit_minus_gtr200_yt;
////  std::vector<double> out_hit_minus_gtr200_xadc;
////  std::vector<double> out_hit_minus_gtr200_yadc;
////  std::vector<int>    out_hit_minus_gtr200_xsize;
////  std::vector<int>    out_hit_minus_gtr200_ysize;
////  std::vector<int>    out_hit_minus_gtr300_xid;
////  std::vector<int>    out_hit_minus_gtr300_yid;
////  std::vector<double> out_hit_minus_gtr300_lx;
////  std::vector<double> out_hit_minus_gtr300_ly;
////  std::vector<double> out_hit_minus_gtr300_xt;
////  std::vector<double> out_hit_minus_gtr300_yt;
////  std::vector<double> out_hit_minus_gtr300_xadc;
////  std::vector<double> out_hit_minus_gtr300_yadc;
////  std::vector<int>    out_hit_minus_gtr300_xsize;
////  std::vector<int>    out_hit_minus_gtr300_ysize;
//  // Fit
//  em_chi2.clear();
//  em_plus_chi2.clear();
//  em_minus_chi2.clear();
//  em_flag.clear();
//  em_distance.clear();
//  em_dir_id.clear();
//  em_vtx_x.clear();
//  em_vtx_y.clear();
//  em_vtx_z.clear();
//  em_plus_mom.clear();
//  em_plus_mom_x.clear();
//  em_plus_mom_y.clear();
//  em_plus_mom_z.clear();
//  em_plus_mom_theta.clear();
//  em_plus_mom_phi.clear();
//  em_minus_mom.clear();
//  em_minus_mom_x.clear();
//  em_minus_mom_y.clear();
//  em_minus_mom_z.clear();
//  em_minus_mom_theta.clear();
//  em_minus_mom_phi.clear();
//  em_mom_angle.clear();
//  em_ee_mass.clear();
//  em_pipi_mass.clear();
//  em_pip_mass.clear();
//  em_kk_mass.clear();
//  em_simple_best_tgt_id.clear();
//  em_simple_best_tgt_r.clear();
//  em_ee_mass_at_best_tgt.clear();
//  em_pipi_mass_at_best_tgt.clear();
//  em_pip_mass_at_best_tgt.clear();
//  em_kk_mass_at_best_tgt.clear();
//  em_plus_ssd_mid.clear();
//  em_plus_gtr100_mid.clear();
//  em_plus_gtr200_mid.clear();
//  em_plus_gtr300_mid.clear();
//  em_plus_hbd_mid.clear();
//  em_plus_lg_c_mid.clear();
//  em_plus_lg_b_mid.clear();
//  em_plus_lg_a_mid.clear();
//  em_minus_ssd_mid.clear();
//  em_minus_gtr100_mid.clear();
//  em_minus_gtr200_mid.clear();
//  em_minus_gtr300_mid.clear();
//  em_minus_hbd_mid.clear();
//  em_minus_lg_c_mid.clear();
//  em_minus_lg_b_mid.clear();
//  em_minus_lg_a_mid.clear();
////  std::vector<double> out_fit_plus_ssd_lx;
////  std::vector<double> out_fit_plus_ssd_ly;
////  std::vector<double> out_fit_plus_gtr100_lx;
////  std::vector<double> out_fit_plus_gtr100_ly;
////  std::vector<double> out_fit_plus_gtr200_lx;
////  std::vector<double> out_fit_plus_gtr200_ly;
////  std::vector<double> out_fit_plus_gtr300_lx;
////  std::vector<double> out_fit_plus_gtr300_ly;
////  std::vector<double> out_fit_plus_hbd_lx;
////  std::vector<double> out_fit_plus_hbd_ly;
////  std::vector<double> out_fit_plus_lg_c_lx;
////  std::vector<double> out_fit_plus_lg_c_ly;
////  std::vector<double> out_fit_plus_lg_b_lx;
////  std::vector<double> out_fit_plus_lg_b_ly;
////  std::vector<double> out_fit_plus_lg_a_lx;
////  std::vector<double> out_fit_plus_lg_a_ly;
//  em_fit_plus_tgt_minus_x.clear();
//  em_fit_plus_tgt_minus_y.clear();
//  em_fit_plus_tgt_zero_x.clear();
//  em_fit_plus_tgt_zero_y.clear();
//  em_fit_plus_tgt_plus_x.clear();
//  em_fit_plus_tgt_plus_y.clear();
////  std::vector<double> out_fit_minus_ssd_lx;
////  std::vector<double> out_fit_minus_ssd_ly;
////  std::vector<double> out_fit_minus_gtr100_lx;
////  std::vector<double> out_fit_minus_gtr100_ly;
////  std::vector<double> out_fit_minus_gtr200_lx;
////  std::vector<double> out_fit_minus_gtr200_ly;
////  std::vector<double> out_fit_minus_gtr300_lx;
////  std::vector<double> out_fit_minus_gtr300_ly;
////  std::vector<double> out_fit_minus_hbd_lx;
////  std::vector<double> out_fit_minus_hbd_ly;
////  std::vector<double> out_fit_minus_lg_c_lx;
////  std::vector<double> out_fit_minus_lg_c_ly;
////  std::vector<double> out_fit_minus_lg_b_lx;
////  std::vector<double> out_fit_minus_lg_b_ly;
////  std::vector<double> out_fit_minus_lg_a_lx;
////  std::vector<double> out_fit_minus_lg_a_ly;
//  em_fit_minus_tgt_minus_x.clear();
//  em_fit_minus_tgt_minus_y.clear();
//  em_fit_minus_tgt_zero_x.clear();
//  em_fit_minus_tgt_zero_y.clear();
//  em_fit_minus_tgt_plus_x.clear();
//  em_fit_minus_tgt_plus_y.clear();
//  em_fit_plus_ssd_mom_lx.clear();
//  em_fit_plus_ssd_mom_ly.clear();
//  em_fit_plus_ssd_mom_lz.clear();
//  em_fit_plus_ssd_mom_gx.clear();
//  em_fit_plus_ssd_mom_gy.clear();
//  em_fit_plus_ssd_mom_gz.clear();
//  em_fit_plus_gtr100_mom_lx.clear();
//  em_fit_plus_gtr100_mom_ly.clear();
//  em_fit_plus_gtr100_mom_lz.clear();
//  em_fit_plus_gtr100_mom_gx.clear();
//  em_fit_plus_gtr100_mom_gy.clear();
//  em_fit_plus_gtr100_mom_gz.clear();
//  em_fit_plus_gtr200_mom_lx.clear();
//  em_fit_plus_gtr200_mom_ly.clear();
//  em_fit_plus_gtr200_mom_lz.clear();
//  em_fit_plus_gtr200_mom_gx.clear();
//  em_fit_plus_gtr200_mom_gy.clear();
//  em_fit_plus_gtr200_mom_gz.clear();
//  em_fit_plus_gtr300_mom_lx.clear();
//  em_fit_plus_gtr300_mom_ly.clear();
//  em_fit_plus_gtr300_mom_lz.clear();
//  em_fit_plus_gtr300_mom_gx.clear();
//  em_fit_plus_gtr300_mom_gy.clear();
//  em_fit_plus_gtr300_mom_gz.clear();
//  em_fit_plus_hbd_mom_lx.clear();
//  em_fit_plus_hbd_mom_ly.clear();
//  em_fit_plus_hbd_mom_lz.clear();
//  em_fit_plus_hbd_mom_gx.clear();
//  em_fit_plus_hbd_mom_gy.clear();
//  em_fit_plus_hbd_mom_gz.clear();
//  em_fit_plus_lg_c_mom_lx.clear();
//  em_fit_plus_lg_c_mom_ly.clear();
//  em_fit_plus_lg_c_mom_lz.clear();
//  em_fit_plus_lg_c_mom_gx.clear();
//  em_fit_plus_lg_c_mom_gy.clear();
//  em_fit_plus_lg_c_mom_gz.clear();
//  em_fit_plus_lg_b_mom_lx.clear();
//  em_fit_plus_lg_b_mom_ly.clear();
//  em_fit_plus_lg_b_mom_lz.clear();
//  em_fit_plus_lg_b_mom_gx.clear();
//  em_fit_plus_lg_b_mom_gy.clear();
//  em_fit_plus_lg_b_mom_gz.clear();
//  em_fit_plus_lg_a_mom_lx.clear();
//  em_fit_plus_lg_a_mom_ly.clear();
//  em_fit_plus_lg_a_mom_lz.clear();
//  em_fit_plus_lg_a_mom_gx.clear();
//  em_fit_plus_lg_a_mom_gy.clear();
//  em_fit_plus_lg_a_mom_gz.clear();
//  em_fit_plus_tgt_minus_mom_x.clear();
//  em_fit_plus_tgt_minus_mom_y.clear();
//  em_fit_plus_tgt_minus_mom_z.clear();
//  em_fit_plus_tgt_zero_mom_x.clear();
//  em_fit_plus_tgt_zero_mom_y.clear();
//  em_fit_plus_tgt_zero_mom_z.clear();
//  em_fit_plus_tgt_plus_mom_x.clear();
//  em_fit_plus_tgt_plus_mom_y.clear();
//  em_fit_plus_tgt_plus_mom_z.clear();
//  em_fit_minus_ssd_mom_lx.clear();
//  em_fit_minus_ssd_mom_ly.clear();
//  em_fit_minus_ssd_mom_lz.clear();
//  em_fit_minus_ssd_mom_gx.clear();
//  em_fit_minus_ssd_mom_gy.clear();
//  em_fit_minus_ssd_mom_gz.clear();
//  em_fit_minus_gtr100_mom_lx.clear();
//  em_fit_minus_gtr100_mom_ly.clear();
//  em_fit_minus_gtr100_mom_lz.clear();
//  em_fit_minus_gtr100_mom_gx.clear();
//  em_fit_minus_gtr100_mom_gy.clear();
//  em_fit_minus_gtr100_mom_gz.clear();
//  em_fit_minus_gtr200_mom_lx.clear();
//  em_fit_minus_gtr200_mom_ly.clear();
//  em_fit_minus_gtr200_mom_lz.clear();
//  em_fit_minus_gtr200_mom_gx.clear();
//  em_fit_minus_gtr200_mom_gy.clear();
//  em_fit_minus_gtr200_mom_gz.clear();
//  em_fit_minus_gtr300_mom_lx.clear();
//  em_fit_minus_gtr300_mom_ly.clear();
//  em_fit_minus_gtr300_mom_lz.clear();
//  em_fit_minus_gtr300_mom_gx.clear();
//  em_fit_minus_gtr300_mom_gy.clear();
//  em_fit_minus_gtr300_mom_gz.clear();
//  em_fit_minus_hbd_mom_lx.clear();
//  em_fit_minus_hbd_mom_ly.clear();
//  em_fit_minus_hbd_mom_lz.clear();
//  em_fit_minus_hbd_mom_gx.clear();
//  em_fit_minus_hbd_mom_gy.clear();
//  em_fit_minus_hbd_mom_gz.clear();
//  em_fit_minus_lg_c_mom_lx.clear();
//  em_fit_minus_lg_c_mom_ly.clear();
//  em_fit_minus_lg_c_mom_lz.clear();
//  em_fit_minus_lg_c_mom_gx.clear();
//  em_fit_minus_lg_c_mom_gy.clear();
//  em_fit_minus_lg_c_mom_gz.clear();
//  em_fit_minus_lg_b_mom_lx.clear();
//  em_fit_minus_lg_b_mom_ly.clear();
//  em_fit_minus_lg_b_mom_lz.clear();
//  em_fit_minus_lg_b_mom_gx.clear();
//  em_fit_minus_lg_b_mom_gy.clear();
//  em_fit_minus_lg_b_mom_gz.clear();
//  em_fit_minus_lg_a_mom_lx.clear();
//  em_fit_minus_lg_a_mom_ly.clear();
//  em_fit_minus_lg_a_mom_lz.clear();
//  em_fit_minus_lg_a_mom_gx.clear();
//  em_fit_minus_lg_a_mom_gy.clear();
//  em_fit_minus_lg_a_mom_gz.clear();
//  em_fit_minus_tgt_minus_mom_x.clear();
//  em_fit_minus_tgt_minus_mom_y.clear();
//  em_fit_minus_tgt_minus_mom_z.clear();
//  em_fit_minus_tgt_zero_mom_x.clear();
//  em_fit_minus_tgt_zero_mom_y.clear();
//  em_fit_minus_tgt_zero_mom_z.clear();
//  em_fit_minus_tgt_plus_mom_x.clear();
//  em_fit_minus_tgt_plus_mom_y.clear();
//  em_fit_minus_tgt_plus_mom_z.clear();
////// gpos...
////  std::vector<double> out_res_plus_ssd_lx;
//////  std::vector<double> out_res_plus_ssd_ly;
////  std::vector<double> out_res_plus_gtr100_lx;
////  std::vector<double> out_res_plus_gtr100_ly;
////  std::vector<double> out_res_plus_gtr200_lx;
////  std::vector<double> out_res_plus_gtr200_ly;
////  std::vector<double> out_res_plus_gtr300_lx;
////  std::vector<double> out_res_plus_gtr300_ly;
////  std::vector<double> out_res_minus_ssd_lx;
//////  std::vector<double> out_res_minus_ssd_ly;
////  std::vector<double> out_res_minus_gtr100_lx;
////  std::vector<double> out_res_minus_gtr100_ly;
////  std::vector<double> out_res_minus_gtr200_lx;
////  std::vector<double> out_res_minus_gtr200_ly;
////  std::vector<double> out_res_minus_gtr300_lx;
////  std::vector<double> out_res_minus_gtr300_ly;
//  em_fit_parent_mom_x.clear();
//  em_fit_parent_mom_y.clear();
//  em_fit_parent_mom_z.clear();
//  em_fit_parent_tgt_minus_x.clear();
//  em_fit_parent_tgt_minus_y.clear();
//  em_fit_parent_tgt_minus_flight_path.clear();
//  em_fit_parent_tgt_zero_x.clear();
//  em_fit_parent_tgt_zero_y.clear();
//  em_fit_parent_tgt_zero_flight_path.clear();
//  em_fit_parent_tgt_plus_x.clear();
//  em_fit_parent_tgt_plus_y.clear();
//  em_fit_parent_tgt_plus_flight_path.clear();
//  em_fit_parent_best_tgt_id.clear();
//  em_fit_parent_best_tgt_r.clear();
//  em_fit_parent_good_tgt_id_set.clear();
//  em_fit_parent_good_tgt_ids.clear();
//  em_fit_parent_x0_y.clear();
//  em_fit_parent_x0_z.clear();
////  // Projected HBD
////  std::vector<double>              out_proj_plus_n_hbds;
////  std::vector<std::vector<double>> out_proj_plus_hbd_id;
////  std::vector<std::vector<double>> out_proj_plus_hbd_lx;
////  std::vector<std::vector<double>> out_proj_plus_hbd_ly;
////  std::vector<std::vector<double>> out_proj_plus_hbd_resx;
////  std::vector<std::vector<double>> out_proj_plus_hbd_resy;
////  std::vector<std::vector<double>> out_proj_plus_hbd_adc;
////  std::vector<std::vector<double>> out_proj_plus_hbd_size;
////  std::vector<std::vector<double>> out_proj_plus_hbd_eprob;
////  std::vector<double>              out_proj_minus_n_hbds;
////  std::vector<std::vector<double>> out_proj_minus_hbd_id;
////  std::vector<std::vector<double>> out_proj_minus_hbd_lx;
////  std::vector<std::vector<double>> out_proj_minus_hbd_ly;
////  std::vector<std::vector<double>> out_proj_minus_hbd_resx;
////  std::vector<std::vector<double>> out_proj_minus_hbd_resy;
////  std::vector<std::vector<double>> out_proj_minus_hbd_adc;
////  std::vector<std::vector<double>> out_proj_minus_hbd_size;
////  std::vector<std::vector<double>> out_proj_minus_hbd_eprob;
////  // Projected LG
//  return;
//}

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
  array<array<TVector3, 4>, 2> lmoms;
  array<array<TVector3, 4>, 2> gposs;
  array<array<TVector3, 4>, 2> gmoms;
  for (int t = 0; t < 2; ++t) {
    moms[t] = fitter->GetFitMomentum(t);
    for (int l = 0; l < 4; ++l) {
      vector<int>      tmp_mids;
      vector<TVector3> tmp_lposs;
      vector<TVector3> tmp_lmoms;
      fitter->GetFitLPos(t, l, tmp_mids, tmp_lposs);
      auto mid = tmp_mids[0];
      lposs[t][l] = tmp_lposs[0];
      fitter->GetFitLMom(t, l, tmp_mids, tmp_lmoms);
      lmoms[t][l] = tmp_lmoms[0];
      if (l == 0) {
        gposs[t][l] = geometry->SSD(mid)->GetGPos(lposs[t][l]);
        gmoms[t][l] = geometry->SSD(mid)->GetGMom(lmoms[t][l]);
      } else {
        gposs[t][l] = geometry->GTR(mid, l - 1)->GetGPos(lposs[t][l]);
        gmoms[t][l] = geometry->GTR(mid, l - 1)->GetGMom(lposs[t][l]);
      }
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
  FillTVector3(n, lmoms[0][0], &out_fit_plus_ssd_mom_lx,     &out_fit_plus_ssd_mom_ly,     &out_fit_plus_ssd_mom_lz);
  FillTVector3(n, lmoms[0][1], &out_fit_plus_gtr100_mom_lx,  &out_fit_plus_gtr100_mom_ly,  &out_fit_plus_gtr100_mom_lz);
  FillTVector3(n, lmoms[0][2], &out_fit_plus_gtr200_mom_lx,  &out_fit_plus_gtr200_mom_ly,  &out_fit_plus_gtr200_mom_lz);
  FillTVector3(n, lmoms[0][3], &out_fit_plus_gtr300_mom_lx,  &out_fit_plus_gtr300_mom_ly,  &out_fit_plus_gtr300_mom_lz);
  FillTVector3(n, lmoms[1][0], &out_fit_minus_ssd_mom_lx,    &out_fit_minus_ssd_mom_ly,    &out_fit_minus_ssd_mom_lz);
  FillTVector3(n, lmoms[1][1], &out_fit_minus_gtr100_mom_lx, &out_fit_minus_gtr100_mom_ly, &out_fit_minus_gtr100_mom_lz);
  FillTVector3(n, lmoms[1][2], &out_fit_minus_gtr200_mom_lx, &out_fit_minus_gtr200_mom_ly, &out_fit_minus_gtr200_mom_lz);
  FillTVector3(n, lmoms[1][3], &out_fit_minus_gtr300_mom_lx, &out_fit_minus_gtr300_mom_ly, &out_fit_minus_gtr300_mom_lz);
  FillTVector3(n, gmoms[0][0], &out_fit_plus_ssd_mom_gx,     &out_fit_plus_ssd_mom_gy,     &out_fit_plus_ssd_mom_gz);
  FillTVector3(n, gmoms[0][1], &out_fit_plus_gtr100_mom_gx,  &out_fit_plus_gtr100_mom_gy,  &out_fit_plus_gtr100_mom_gz);
  FillTVector3(n, gmoms[0][2], &out_fit_plus_gtr200_mom_gx,  &out_fit_plus_gtr200_mom_gy,  &out_fit_plus_gtr200_mom_gz);
  FillTVector3(n, gmoms[0][3], &out_fit_plus_gtr300_mom_gx,  &out_fit_plus_gtr300_mom_gy,  &out_fit_plus_gtr300_mom_gz);
  FillTVector3(n, gmoms[1][0], &out_fit_minus_ssd_mom_gx,    &out_fit_minus_ssd_mom_gy,    &out_fit_minus_ssd_mom_gz);
  FillTVector3(n, gmoms[1][1], &out_fit_minus_gtr100_mom_gx, &out_fit_minus_gtr100_mom_gy, &out_fit_minus_gtr100_mom_gz);
  FillTVector3(n, gmoms[1][2], &out_fit_minus_gtr200_mom_gx, &out_fit_minus_gtr200_mom_gy, &out_fit_minus_gtr200_mom_gz);
  FillTVector3(n, gmoms[1][3], &out_fit_minus_gtr300_mom_gx, &out_fit_minus_gtr300_mom_gy, &out_fit_minus_gtr300_mom_gz);
  return;
}

int track_analyzer_220715::ModuleID2013(int m) {
  return kModuleID2013[1][m - 100];
}

int track_analyzer_220715::ChargeID(int c) {
  if (c == 1) {
    return kChargePlus;
  } else {
    return kChargeMinus;
  }
}

void track_analyzer_220715::PairFit(int n) {
  fitter->Clear();
  fitter->SetInitialVertex(kInitVertex, kVertexSigma);
  for (int tid = 0; tid < 2; ++tid) {
    auto i = good_pair_indexs[n][tid];
    if (!kForgiveSameCharge) {
      if (tid == 0) {
        fitter->SetCharge(tid, 1.);
      } else {
        fitter->SetCharge(tid, -1.);
      }
    } else {
      fitter->SetCharge(tid, ChargeID(rk_charge->at(i)));
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

void track_analyzer_220715::FillBranchesFromStepTrack(int n, int flag, double dist_cm, const Hep3Vector& hep_vtx,
                                                      const Hep3Vector& hep_plus_pos, const Hep3Vector& hep_minus_pos,
                                                      const Hep3Vector& hep_plus_mom, const Hep3Vector& hep_minus_mom) {
  auto ptid = good_pair_indexs[n][0];
  auto mtid = good_pair_indexs[n][1];
  out_plus_chi2[n]            = chi_square->at(ptid);
  out_minus_chi2[n]           = chi_square->at(mtid);
  out_flag[n]                 = flag;
  out_distance[n]             = dist_cm           * 10.;
  out_plus_nearest_tgt_id[n]  = nearest_tgt_ids[ptid];
  out_plus_nearest_radius[n]  = nearest_radius[ptid];
  out_minus_nearest_tgt_id[n] = nearest_tgt_ids[mtid];
  out_minus_nearest_radius[n] = nearest_radius[mtid];
  out_vtx_x[n]                = hep_vtx.x()       * 10.;
  out_vtx_y[n]                = hep_vtx.y()       * 10.;
  out_vtx_z[n]                = hep_vtx.z()       * 10.;
  auto ppos = TVector3(hep_plus_pos.x()  * 10., hep_plus_pos.y()  * 10., hep_plus_pos.z()  * 10.);
  auto mpos = TVector3(hep_minus_pos.x() * 10., hep_minus_pos.y() * 10., hep_minus_pos.z() * 10.);
  out_plus_pos_x[n]  = ppos.X();
  out_plus_pos_y[n]  = ppos.Y();
  out_plus_pos_z[n]  = ppos.Z();
  out_minus_pos_x[n] = mpos.X();
  out_minus_pos_y[n] = mpos.Y();
  out_minus_pos_z[n] = mpos.Z();
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

  out_fit_plus_ssd_lx[n]    = rk_fit_ssd_x->at(ptid);
  out_fit_plus_ssd_ly[n]    = rk_fit_ssd_y->at(ptid);
  out_fit_plus_gtr100_lx[n] = rk_fit_gtr100_x->at(ptid);
  out_fit_plus_gtr100_ly[n] = rk_fit_gtr100_y->at(ptid);
  out_fit_plus_gtr200_lx[n] = rk_fit_gtr200_x->at(ptid);
  out_fit_plus_gtr200_ly[n] = rk_fit_gtr200_y->at(ptid);
  out_fit_plus_gtr300_lx[n] = rk_fit_gtr300_x->at(ptid);
  out_fit_plus_gtr300_ly[n] = rk_fit_gtr300_y->at(ptid);
  out_fit_plus_hbd_lx[n]    = rk_fit_hbd_x->at(ptid);
  out_fit_plus_hbd_ly[n]    = rk_fit_hbd_y->at(ptid);
  out_fit_plus_lg_c_lx[n]   = rk_fit_lg_c_x->at(ptid);
  out_fit_plus_lg_c_ly[n]   = rk_fit_lg_c_y->at(ptid);
  out_fit_plus_lg_b_lx[n]   = rk_fit_lg_b_x->at(ptid);
  out_fit_plus_lg_b_ly[n]   = rk_fit_lg_b_y->at(ptid);
  out_fit_plus_lg_a_lx[n]   = rk_fit_lg_a_x->at(ptid);
  out_fit_plus_lg_a_ly[n]   = rk_fit_lg_a_y->at(ptid);
  out_fit_minus_ssd_lx[n]    = rk_fit_ssd_x->at(mtid);
  out_fit_minus_ssd_ly[n]    = rk_fit_ssd_y->at(mtid);
  out_fit_minus_gtr100_lx[n] = rk_fit_gtr100_x->at(mtid);
  out_fit_minus_gtr100_ly[n] = rk_fit_gtr100_y->at(mtid);
  out_fit_minus_gtr200_lx[n] = rk_fit_gtr200_x->at(mtid);
  out_fit_minus_gtr200_ly[n] = rk_fit_gtr200_y->at(mtid);
  out_fit_minus_gtr300_lx[n] = rk_fit_gtr300_x->at(mtid);
  out_fit_minus_gtr300_ly[n] = rk_fit_gtr300_y->at(mtid);
  out_fit_minus_hbd_lx[n]    = rk_fit_hbd_x->at(mtid);
  out_fit_minus_hbd_ly[n]    = rk_fit_hbd_y->at(mtid);
  out_fit_minus_lg_c_lx[n]   = rk_fit_lg_c_x->at(mtid);
  out_fit_minus_lg_c_ly[n]   = rk_fit_lg_c_y->at(mtid);
  out_fit_minus_lg_b_lx[n]   = rk_fit_lg_b_x->at(mtid);
  out_fit_minus_lg_b_ly[n]   = rk_fit_lg_b_y->at(mtid);
  out_fit_minus_lg_a_lx[n]   = rk_fit_lg_a_x->at(mtid);
  out_fit_minus_lg_a_ly[n]   = rk_fit_lg_a_y->at(mtid);
  
//  FillTVector3(n, lmoms[0][0], &out_fit_plus_ssd_mom_lx,     &out_fit_plus_ssd_mom_ly,     &out_fit_plus_ssd_mom_lz);
//  FillTVector3(n, lmoms[0][1], &out_fit_plus_gtr100_mom_lx,  &out_fit_plus_gtr100_mom_ly,  &out_fit_plus_gtr100_mom_lz);
//  FillTVector3(n, lmoms[0][2], &out_fit_plus_gtr200_mom_lx,  &out_fit_plus_gtr200_mom_ly,  &out_fit_plus_gtr200_mom_lz);
//  FillTVector3(n, lmoms[0][3], &out_fit_plus_gtr300_mom_lx,  &out_fit_plus_gtr300_mom_ly,  &out_fit_plus_gtr300_mom_lz);
//  FillTVector3(n, lmoms[1][0], &out_fit_minus_ssd_mom_lx,    &out_fit_minus_ssd_mom_ly,    &out_fit_minus_ssd_mom_lz);
//  FillTVector3(n, lmoms[1][1], &out_fit_minus_gtr100_mom_lx, &out_fit_minus_gtr100_mom_ly, &out_fit_minus_gtr100_mom_lz);
//  FillTVector3(n, lmoms[1][2], &out_fit_minus_gtr200_mom_lx, &out_fit_minus_gtr200_mom_ly, &out_fit_minus_gtr200_mom_lz);
//  FillTVector3(n, lmoms[1][3], &out_fit_minus_gtr300_mom_lx, &out_fit_minus_gtr300_mom_ly, &out_fit_minus_gtr300_mom_lz);
//  FillTVector3(n, gmoms[0][0], &out_fit_plus_ssd_mom_gx,     &out_fit_plus_ssd_mom_gy,     &out_fit_plus_ssd_mom_gz);
//  FillTVector3(n, gmoms[0][1], &out_fit_plus_gtr100_mom_gx,  &out_fit_plus_gtr100_mom_gy,  &out_fit_plus_gtr100_mom_gz);
//  FillTVector3(n, gmoms[0][2], &out_fit_plus_gtr200_mom_gx,  &out_fit_plus_gtr200_mom_gy,  &out_fit_plus_gtr200_mom_gz);
//  FillTVector3(n, gmoms[0][3], &out_fit_plus_gtr300_mom_gx,  &out_fit_plus_gtr300_mom_gy,  &out_fit_plus_gtr300_mom_gz);
//  FillTVector3(n, gmoms[1][0], &out_fit_minus_ssd_mom_gx,    &out_fit_minus_ssd_mom_gy,    &out_fit_minus_ssd_mom_gz);
//  FillTVector3(n, gmoms[1][1], &out_fit_minus_gtr100_mom_gx, &out_fit_minus_gtr100_mom_gy, &out_fit_minus_gtr100_mom_gz);
//  FillTVector3(n, gmoms[1][2], &out_fit_minus_gtr200_mom_gx, &out_fit_minus_gtr200_mom_gy, &out_fit_minus_gtr200_mom_gz);
//  FillTVector3(n, gmoms[1][3], &out_fit_minus_gtr300_mom_gx, &out_fit_minus_gtr300_mom_gy, &out_fit_minus_gtr300_mom_gz);
  return;
}

void track_analyzer_220715::NearestPoint(int n) {
  array<E16ANA_StepTrack*, 2> tracks;
  for (int t = 0; t < 2; ++t) {
    auto i = good_pair_indexs[n][t];
    auto pos = Hep3Vector(rk_fit_init_pos_gx->at(i) * 0.1, rk_fit_init_pos_gy->at(i) * 0.1, rk_fit_init_pos_gz->at(i) * 0.1);
    auto mom = Hep3Vector(rk_fit_init_mom_gx->at(i), rk_fit_init_mom_gy->at(i), rk_fit_init_mom_gz->at(i));
    double charge;
    if (!kForgiveSameCharge) {
      if (t == 0) {
        charge = 1.;
      } else {
        charge = -1.;
      }
    } else {
      if (ChargeID(rk_charge->at(i)) == kChargePlus) {
        charge = 1.;
      } else {
        charge = -1.;
      }
    }
    tracks[t] = new E16ANA_StepTrack(bfield_map, pos, mom, charge, kStepTrackSizeCm, kStepTrackArraySize);
  }
  auto dist_cm       = double();
  auto hep_vtx       = Hep3Vector();
  auto hep_plus_pos  = Hep3Vector();
  auto hep_minus_pos = Hep3Vector();
  auto hep_plus_mom  = Hep3Vector();
  auto hep_minus_mom = Hep3Vector();
  auto flag = tracks[0]->Cross(*tracks[1], &dist_cm, &hep_vtx, &hep_plus_pos, &hep_minus_pos, &hep_plus_mom, &hep_minus_mom);
  FillBranchesFromStepTrack(n, flag, dist_cm, hep_vtx, hep_plus_pos, hep_minus_pos, hep_plus_mom, hep_minus_mom);
#ifdef TMP_ZX_NEAREST
  flag = tracks[0]->CrossXZ(*tracks[1], &dist_cm, &hep_vtx, &hep_plus_pos, &hep_minus_pos, &hep_plus_mom, &hep_minus_mom);
  out_tmp_zx_flag[n] = flag;
  if (flag == -1) {
    out_tmp_zx_distance[n]    = kErrorNum;
    out_tmp_zx_vtx_x[n]       = kErrorNum;
    out_tmp_zx_vtx_y[n]       = kErrorNum;
    out_tmp_zx_vtx_z[n]       = kErrorNum;
    out_tmp_zx_plus_pos_x[n]  = kErrorNum;
    out_tmp_zx_plus_pos_y[n]  = kErrorNum;
    out_tmp_zx_plus_pos_z[n]  = kErrorNum;
    out_tmp_zx_minus_pos_x[n] = kErrorNum;
    out_tmp_zx_minus_pos_y[n] = kErrorNum;
    out_tmp_zx_minus_pos_z[n] = kErrorNum;
    out_tmp_zx_plus_mom_x[n]  = kErrorNum;
    out_tmp_zx_plus_mom_y[n]  = kErrorNum;
    out_tmp_zx_plus_mom_z[n]  = kErrorNum;
    out_tmp_zx_minus_mom_x[n] = kErrorNum;
    out_tmp_zx_minus_mom_y[n] = kErrorNum;
    out_tmp_zx_minus_mom_z[n] = kErrorNum;
    out_tmp_zx_pipi_mass[n]   = kErrorNum;
  } else {
    out_tmp_zx_distance[n] = dist_cm * 10.;
    out_tmp_zx_vtx_x[n] = hep_vtx.x() * 10.;
    out_tmp_zx_vtx_y[n] = hep_vtx.y() * 10.;
    out_tmp_zx_vtx_z[n] = hep_vtx.z() * 10.;
    auto ppos = TVector3(hep_plus_pos.x()  * 10., hep_plus_pos.y()  * 10., hep_plus_pos.z()  * 10.);
    auto mpos = TVector3(hep_minus_pos.x() * 10., hep_minus_pos.y() * 10., hep_minus_pos.z() * 10.);
    out_tmp_zx_plus_pos_x[n]  = ppos.X();
    out_tmp_zx_plus_pos_y[n]  = ppos.Y();
    out_tmp_zx_plus_pos_z[n]  = ppos.Z();
    out_tmp_zx_minus_pos_x[n] = mpos.X();
    out_tmp_zx_minus_pos_y[n] = mpos.Y();
    out_tmp_zx_minus_pos_z[n] = mpos.Z();
    auto pmom = TVector3(hep_plus_mom.x(),  hep_plus_mom.y(),  hep_plus_mom.z());
    auto mmom = TVector3(hep_minus_mom.x(), hep_minus_mom.y(), hep_minus_mom.z());
//    out_tmp_zx_plus_mom[n]        = pmom.Mag();
    out_tmp_zx_plus_mom_x[n]      = pmom.X();
    out_tmp_zx_plus_mom_y[n]      = pmom.Y();
    out_tmp_zx_plus_mom_z[n]      = pmom.Z();
//    out_tmp_zx_plus_mom_theta[n]  = pmom.Theta();
//    out_tmp_zx_plus_mom_phi[n]    = pmom.Phi();
//    out_tmp_zx_minus_mom[n]       = mmom.Mag();
    out_tmp_zx_minus_mom_x[n]     = mmom.X();
    out_tmp_zx_minus_mom_y[n]     = mmom.Y();
    out_tmp_zx_minus_mom_z[n]     = mmom.Z();
//    out_tmp_zx_minus_mom_theta[n] = mmom.Theta();
//    out_tmp_zx_minus_mom_phi[n]   = mmom.Phi();
//    out_tmp_zx_mom_angle[n]       = pmom.Angle(mmom);
//    out_tmp_zx_ee_mass[n]         = CalcMass(kEE,   pmom, mmom);
    out_tmp_zx_pipi_mass[n]       = CalcMass(kPiPi, pmom, mmom);
//    out_tmp_zx_pip_mass[n]        = CalcMass(kPiP,  pmom, mmom);
//    out_tmp_zx_kk_mass[n]         = CalcMass(kKK,   pmom, mmom);
  }
#endif // TMP_ZX_NEAREST
  for (auto& track : tracks) {
    delete track;
  }
  return;
}

int track_analyzer_220715::DirID(int mid0, int mid1) {
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
    if (kForgiveSameCharge) {
      if (ChargeID(rk_charge->at(i)) == kChargePlus) {
        charge = 1.;
      } else {
        charge = -1.;
      }
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
              out_plus_hbd_mid[n]        = m;
              out_fit_plus_hbd_lx[n]     = lpos.X();
              out_fit_plus_hbd_ly[n]     = lpos.Y();
              out_fit_plus_hbd_mom_lx[n] = lmom.X();
              out_fit_plus_hbd_mom_ly[n] = lmom.Y();
              out_fit_plus_hbd_mom_lz[n] = lmom.Z();
              out_fit_plus_hbd_mom_gx[n] = gmom.X();
              out_fit_plus_hbd_mom_gy[n] = gmom.Y();
              out_fit_plus_hbd_mom_gz[n] = gmom.Z();
            } else {
              out_minus_hbd_mid[n]        = m;
              out_fit_minus_hbd_lx[n]     = lpos.X();
              out_fit_minus_hbd_ly[n]     = lpos.Y();
              out_fit_minus_hbd_mom_lx[n] = lmom.X();
              out_fit_minus_hbd_mom_ly[n] = lmom.Y();
              out_fit_minus_hbd_mom_lz[n] = lmom.Z();
              out_fit_minus_hbd_mom_gx[n] = gmom.X();
              out_fit_minus_hbd_mom_gy[n] = gmom.Y();
              out_fit_minus_hbd_mom_gz[n] = gmom.Z();
            }
          } else {
            auto lpos_lgvd = geometry->LGVD(mid2013)->GetLPos(gpos);
            if (l == 1) {
              if (t == 0) {
                out_plus_lg_c_mid[n]        = m;
                out_fit_plus_lg_c_lx[n]     = lpos_lgvd.X();
                out_fit_plus_lg_c_ly[n]     = lpos_lgvd.Y();
                out_fit_plus_lg_c_mom_lx[n] = lmom.X();
                out_fit_plus_lg_c_mom_ly[n] = lmom.Y();
                out_fit_plus_lg_c_mom_lz[n] = lmom.Z();
                out_fit_plus_lg_c_mom_gx[n] = gmom.X();
                out_fit_plus_lg_c_mom_gy[n] = gmom.Y();
                out_fit_plus_lg_c_mom_gz[n] = gmom.Z();
              } else {
                out_minus_lg_c_mid[n]        = m;
                out_fit_minus_lg_c_lx[n]     = lpos_lgvd.X();
                out_fit_minus_lg_c_ly[n]     = lpos_lgvd.Y();
                out_fit_minus_lg_c_mom_lx[n] = lmom.X();
                out_fit_minus_lg_c_mom_ly[n] = lmom.Y();
                out_fit_minus_lg_c_mom_lz[n] = lmom.Z();
                out_fit_minus_lg_c_mom_gx[n] = gmom.X();
                out_fit_minus_lg_c_mom_gy[n] = gmom.Y();
                out_fit_minus_lg_c_mom_gz[n] = gmom.Z();
              }
            } else if (l == 2) {
              if (t == 0) {
                out_plus_lg_b_mid[n]    = m;
                out_fit_plus_lg_b_lx[n] = lpos_lgvd.X();
                out_fit_plus_lg_b_ly[n] = lpos_lgvd.Y();
                out_fit_plus_lg_b_mom_lx[n] = lmom.X();
                out_fit_plus_lg_b_mom_ly[n] = lmom.Y();
                out_fit_plus_lg_b_mom_lz[n] = lmom.Z();
                out_fit_plus_lg_b_mom_gx[n] = gmom.X();
                out_fit_plus_lg_b_mom_gy[n] = gmom.Y();
                out_fit_plus_lg_b_mom_gz[n] = gmom.Z();
              } else {
                out_minus_lg_b_mid[n]    = m;
                out_fit_minus_lg_b_lx[n] = lpos_lgvd.X();
                out_fit_minus_lg_b_ly[n] = lpos_lgvd.Y();
                out_fit_minus_lg_b_mom_lx[n] = lmom.X();
                out_fit_minus_lg_b_mom_ly[n] = lmom.Y();
                out_fit_minus_lg_b_mom_lz[n] = lmom.Z();
                out_fit_minus_lg_b_mom_gx[n] = gmom.X();
                out_fit_minus_lg_b_mom_gy[n] = gmom.Y();
                out_fit_minus_lg_b_mom_gz[n] = gmom.Z();
              }
            } else {
              if (t == 0) {
                out_plus_lg_a_mid[n]    = m;
                out_fit_plus_lg_a_lx[n] = lpos_lgvd.X();
                out_fit_plus_lg_a_ly[n] = lpos_lgvd.Y();
                out_fit_plus_lg_a_mom_lx[n] = lmom.X();
                out_fit_plus_lg_a_mom_ly[n] = lmom.Y();
                out_fit_plus_lg_a_mom_lz[n] = lmom.Z();
                out_fit_plus_lg_a_mom_gx[n] = gmom.X();
                out_fit_plus_lg_a_mom_gy[n] = gmom.Y();
                out_fit_plus_lg_a_mom_gz[n] = gmom.Z();
              } else {
                out_minus_lg_a_mid[n]    = m;
                out_fit_minus_lg_a_lx[n] = lpos_lgvd.X();
                out_fit_minus_lg_a_ly[n] = lpos_lgvd.Y();
                out_fit_minus_lg_a_mom_lx[n] = lmom.X();
                out_fit_minus_lg_a_mom_ly[n] = lmom.Y();
                out_fit_minus_lg_a_mom_lz[n] = lmom.Z();
                out_fit_minus_lg_a_mom_gx[n] = gmom.X();
                out_fit_minus_lg_a_mom_gy[n] = gmom.Y();
                out_fit_minus_lg_a_mom_gz[n] = gmom.Z();
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

void track_analyzer_220715::ProjectionTargets(int n) {
  for (int t = 0; t < kNumCharges; ++t) {
    auto i = good_pair_indexs[n][t];
    auto init_pos = Hep3Vector(out_vtx_x[n] * 0.1, out_vtx_y[n] * 0.1, out_vtx_z[n] * 0.1);
    Hep3Vector init_mom;
    double charge;
    if (t == kChargePlus) {
      init_mom.set(out_plus_mom_x[n],  out_plus_mom_y[n],  out_plus_mom_z[n]);
      charge = 1.;
    } else {
      init_mom.set(out_minus_mom_x[n], out_minus_mom_y[n], out_minus_mom_z[n]);
      charge = -1.;
    }
    if (kForgiveSameCharge) {
      if (ChargeID(rk_charge->at(i)) == kChargePlus) {
        charge = 1.;
      } else {
        charge = -1.;
      }
    }
    E16ANA_StepTrack step_track(bfield_map, init_pos, init_mom, charge, kStepTrackSizeCm, kStepTrackArraySize);
    Hep3Vector cross_pos;
    Hep3Vector cross_mom;
    for (int i = 0; i < kNumTgts; ++i) {
      if (step_track.CrossZconstPlane(kTargetZ[i] * 0.1, cross_pos, cross_mom) == -1) {
        if (t == kChargePlus) {
          if (i == kTgtMinus) {
            out_fit_plus_tgt_minus_x[n] = kErrorNum;
            out_fit_plus_tgt_minus_y[n] = kErrorNum;
            out_fit_plus_tgt_minus_mom_x[n] = kErrorNum;
            out_fit_plus_tgt_minus_mom_y[n] = kErrorNum;
            out_fit_plus_tgt_minus_mom_z[n] = kErrorNum;
          } else if (i == kTgtZero) {
            out_fit_plus_tgt_zero_x[n] = kErrorNum;
            out_fit_plus_tgt_zero_y[n] = kErrorNum;
            out_fit_plus_tgt_zero_mom_x[n] = kErrorNum;
            out_fit_plus_tgt_zero_mom_y[n] = kErrorNum;
            out_fit_plus_tgt_zero_mom_z[n] = kErrorNum;
          } else if (i == kTgtPlus) {
            out_fit_plus_tgt_plus_x[n] = kErrorNum;
            out_fit_plus_tgt_plus_y[n] = kErrorNum;
            out_fit_plus_tgt_plus_mom_x[n] = kErrorNum;
            out_fit_plus_tgt_plus_mom_y[n] = kErrorNum;
            out_fit_plus_tgt_plus_mom_z[n] = kErrorNum;
          }
        } else {
          if (i == kTgtMinus) {
            out_fit_minus_tgt_minus_x[n] = kErrorNum;
            out_fit_minus_tgt_minus_y[n] = kErrorNum;
            out_fit_minus_tgt_minus_mom_x[n] = kErrorNum;
            out_fit_minus_tgt_minus_mom_y[n] = kErrorNum;
            out_fit_minus_tgt_minus_mom_z[n] = kErrorNum;
          } else if (i == kTgtZero) {
            out_fit_minus_tgt_zero_x[n] = kErrorNum;
            out_fit_minus_tgt_zero_y[n] = kErrorNum;
            out_fit_minus_tgt_zero_mom_x[n] = kErrorNum;
            out_fit_minus_tgt_zero_mom_y[n] = kErrorNum;
            out_fit_minus_tgt_zero_mom_z[n] = kErrorNum;
          } else if (i == kTgtPlus) {
            out_fit_minus_tgt_plus_x[n] = kErrorNum;
            out_fit_minus_tgt_plus_y[n] = kErrorNum;
            out_fit_minus_tgt_plus_mom_x[n] = kErrorNum;
            out_fit_minus_tgt_plus_mom_y[n] = kErrorNum;
            out_fit_minus_tgt_plus_mom_z[n] = kErrorNum;
          }
        }
      } else {
        if (t == kChargePlus) {
          if (i == kTgtMinus) {
            out_fit_plus_tgt_minus_x[n] = cross_pos.x() * 10.;
            out_fit_plus_tgt_minus_y[n] = cross_pos.y() * 10.;
            out_fit_plus_tgt_minus_mom_x[n] = cross_mom.x();
            out_fit_plus_tgt_minus_mom_y[n] = cross_mom.y();
            out_fit_plus_tgt_minus_mom_z[n] = cross_mom.z();
          } else if (i == kTgtZero) {
            out_fit_plus_tgt_zero_x[n] = cross_pos.x() * 10.;
            out_fit_plus_tgt_zero_y[n] = cross_pos.y() * 10.;
            out_fit_plus_tgt_zero_mom_x[n] = cross_mom.x();
            out_fit_plus_tgt_zero_mom_y[n] = cross_mom.y();
            out_fit_plus_tgt_zero_mom_z[n] = cross_mom.z();
          } else if (i == kTgtPlus) {
            out_fit_plus_tgt_plus_x[n] = cross_pos.x() * 10.;
            out_fit_plus_tgt_plus_y[n] = cross_pos.y() * 10.;
            out_fit_plus_tgt_plus_mom_x[n] = cross_mom.x();
            out_fit_plus_tgt_plus_mom_y[n] = cross_mom.y();
            out_fit_plus_tgt_plus_mom_z[n] = cross_mom.z();
          }
        } else if (t == kChargeMinus) {
          if (i == kTgtMinus) {
            out_fit_minus_tgt_minus_x[n] = cross_pos.x() * 10.;
            out_fit_minus_tgt_minus_y[n] = cross_pos.y() * 10.;
            out_fit_minus_tgt_minus_mom_x[n] = cross_mom.x();
            out_fit_minus_tgt_minus_mom_y[n] = cross_mom.y();
            out_fit_minus_tgt_minus_mom_z[n] = cross_mom.z();
          } else if (i == kTgtZero) {
            out_fit_minus_tgt_zero_x[n] = cross_pos.x() * 10.;
            out_fit_minus_tgt_zero_y[n] = cross_pos.y() * 10.;
            out_fit_minus_tgt_zero_mom_x[n] = cross_mom.x();
            out_fit_minus_tgt_zero_mom_y[n] = cross_mom.y();
            out_fit_minus_tgt_zero_mom_z[n] = cross_mom.z();
          } else if (i == kTgtPlus) {
            out_fit_minus_tgt_plus_x[n] = cross_pos.x() * 10.;
            out_fit_minus_tgt_plus_y[n] = cross_pos.y() * 10.;
            out_fit_minus_tgt_plus_mom_x[n] = cross_mom.x();
            out_fit_minus_tgt_plus_mom_y[n] = cross_mom.y();
            out_fit_minus_tgt_plus_mom_z[n] = cross_mom.z();
          }
        }
      }
    }
  }
  return;
}

//int track_analyzer_220715::BestTargetID(int n) {
//  out_fit_parent_good_tgt_id_set[n] = 0;
//  array<TVector3, kNumTgts> tgt_poss;
//  tgt_poss[0].SetXYZ(out_fit_parent_tgt_minus_x[n], out_fit_parent_tgt_minus_y[n], 0.);
//  tgt_poss[1].SetXYZ(out_fit_parent_tgt_zero_x[n],  out_fit_parent_tgt_zero_y[n],  0.);
//  tgt_poss[2].SetXYZ(out_fit_parent_tgt_plus_x[n],  out_fit_parent_tgt_plus_y[n],  0.);
////  array<double, kNumTgts> r = {pow(out_fit_parent_tgt_minus_x[n] * out_fit_parent_tgt_minus_x[n] + out_fit_parent_tgt_minus_y[n] * out_fit_parent_tgt_minus_y[n], 0.5),
////                               pow(out_fit_parent_tgt_zero_x[n]  * out_fit_parent_tgt_zero_x[n]  + out_fit_parent_tgt_zero_y[n]  * out_fit_parent_tgt_zero_y[n], 0.5),
////                               pow(out_fit_parent_tgt_plus_x[n]  * out_fit_parent_tgt_plus_x[n]  + out_fit_parent_tgt_plus_y[n]  * out_fit_parent_tgt_plus_y[n], 0.5)};
//  int best_id = 0;
//  double best_r = 10000.;
//  for (int i = 0; i < kNumTgts; ++i) {
//    if (out_vtx_z[n] < kTargetZ[i] - kMaxDiffTgtAndVtx) {
//      continue;
//    }
//    auto r = tgt_poss[i].Perp();
//    if (i == 0) {
//      out_fit_parent_tgt_minus_flight_path[n] = r;
//    } else if (i == 1) {
//      out_fit_parent_tgt_zero_flight_path[n]  = r;
//    } else if (i == 2) {
//      out_fit_parent_tgt_plus_flight_path[n]  = r;
//    }
//    if (r < best_r) {
//      best_id = i;
//      best_r  = r;
//    }
//    if (fabs(tgt_poss[i].X()) < kMaxGoodTgtXDiff && fabs(tgt_poss[i].Y()) < kMaxGoodTgtYDiff) {
//      out_fit_parent_good_tgt_ids[n].emplace_back(i);
//      out_fit_parent_good_tgt_id_set[n] += pow(2, i);
//    }
//  }
//  return best_id;
//}

//void track_analyzer_220715::ParentInfo(int n) {
//  out_fit_parent_mom_x[n]       = out_plus_mom_x[n] + out_minus_mom_x[n];
//  out_fit_parent_mom_y[n]       = out_plus_mom_y[n] + out_minus_mom_y[n];
//  out_fit_parent_mom_z[n]       = out_plus_mom_z[n] + out_minus_mom_z[n];
//  out_fit_parent_tgt_minus_x[n] = out_vtx_x[n] + out_fit_parent_mom_x[n] * (kTargetZ[0] - out_vtx_z[n]) / out_fit_parent_mom_z[n];
//  out_fit_parent_tgt_minus_y[n] = out_vtx_y[n] + out_fit_parent_mom_y[n] * (kTargetZ[0] - out_vtx_z[n]) / out_fit_parent_mom_z[n];
//  out_fit_parent_tgt_zero_x[n]  = out_vtx_x[n] + out_fit_parent_mom_x[n] * (kTargetZ[1] - out_vtx_z[n]) / out_fit_parent_mom_z[n];
//  out_fit_parent_tgt_zero_y[n]  = out_vtx_y[n] + out_fit_parent_mom_y[n] * (kTargetZ[1] - out_vtx_z[n]) / out_fit_parent_mom_z[n];
//  out_fit_parent_tgt_plus_x[n]  = out_vtx_x[n] + out_fit_parent_mom_x[n] * (kTargetZ[2] - out_vtx_z[n]) / out_fit_parent_mom_z[n];
//  out_fit_parent_tgt_plus_y[n]  = out_vtx_y[n] + out_fit_parent_mom_y[n] * (kTargetZ[2] - out_vtx_z[n]) / out_fit_parent_mom_z[n];
//  out_fit_parent_best_tgt_id[n] = BestTargetID(n);
//  return;
//}

int track_analyzer_220715::BestTargetID(double vtx_z, const array<TVector3, kNumTgts>& tgt_poss,
                                        array<double, kNumTgts>* flight_paths, double* best_tgt_r, int* good_tgt_id_set, vector<double>* good_tgt_ids) {
  *good_tgt_id_set = 0;
  int best_id = -1;
  *best_tgt_r = 10000.;
  for (int i = 0; i < kNumTgts; ++i) {
    if (vtx_z < kTargetZ[i] - kMaxDiffTgtAndVtx) {
      continue;
    }
    auto r = tgt_poss[i].Perp();
    flight_paths->at(i) = r;
    if (r < *best_tgt_r) {
      best_id = i;
      *best_tgt_r  = r;
    }
    if (fabs(tgt_poss[i].X()) < kMaxGoodTgtXDiff && fabs(tgt_poss[i].Y()) < kMaxGoodTgtYDiff) {
      *good_tgt_id_set += pow(2, i);
      good_tgt_ids->emplace_back(i);
    }
  }
  return best_id;
}

TVector3 X0Projection(const TVector3& pos, const TVector3& mom) {
  double y = pos.Y() - mom.Y() / mom.X() * pos.X();
  double z = pos.Z() - mom.Z() / mom.X() * pos.X();
  return TVector3(0., y, z);
}

void track_analyzer_220715::ParentInfo(const TVector3& vtx, const array<TVector3, 2>& moms, TVector3* parent_mom, array<TVector3, kNumTgts>* tgt_poss,
                                       array<double, kNumTgts>* flight_paths, int* best_tgt_id, double* best_tgt_r,
                                       int* good_tgt_id_set, vector<double>* good_tgt_ids, TVector3* x0_pos) {
  *parent_mom = moms[0] + moms[1];
  for (int i = 0; i < kNumTgts; ++i) {
    tgt_poss->at(i).SetX(vtx.X() + parent_mom->X() * (kTargetZ[i] - vtx.Z()) / parent_mom->Z());
    tgt_poss->at(i).SetY(vtx.Y() + parent_mom->Y() * (kTargetZ[i] - vtx.Z()) / parent_mom->Z());
    tgt_poss->at(i).SetZ(0.);
  }
  *best_tgt_id = BestTargetID(vtx.Z(), *tgt_poss, flight_paths, best_tgt_r, good_tgt_id_set, good_tgt_ids);
  *x0_pos = X0Projection(vtx, *parent_mom);
  return;
}

void track_analyzer_220715::ParentInfo(int n) {
  auto vtx = TVector3(out_vtx_x[n], out_vtx_y[n], out_vtx_z[n]);
  array<TVector3, 2> moms;
  moms[0] = TVector3(out_plus_mom_x[n],  out_plus_mom_y[n],  out_plus_mom_z[n]);
  moms[1] = TVector3(out_minus_mom_x[n], out_minus_mom_y[n], out_minus_mom_z[n]);
  
  TVector3 parent_mom;
  array<TVector3, kNumTgts> tgt_poss;
  array<double,   kNumTgts> flight_paths;
  TVector3 x0_pos;
  ParentInfo(vtx, moms, &parent_mom, &tgt_poss, &flight_paths, &out_fit_parent_best_tgt_id[n], &out_fit_parent_best_tgt_r[n],
             &out_fit_parent_good_tgt_id_set[n], &out_fit_parent_good_tgt_ids[n], &x0_pos);
  out_fit_parent_mom[n]       = parent_mom.Mag();
  out_fit_parent_mom_x[n]     = parent_mom.X();
  out_fit_parent_mom_y[n]     = parent_mom.Y();
  out_fit_parent_mom_z[n]     = parent_mom.Z();
  out_fit_parent_mom_theta[n] = parent_mom.Theta();
  out_fit_parent_mom_phi[n]   = parent_mom.Phi();
  out_fit_parent_tgt_minus_x[n] = tgt_poss[0].X();
  out_fit_parent_tgt_minus_y[n] = tgt_poss[0].Y();
  out_fit_parent_tgt_zero_x[n]  = tgt_poss[1].X();
  out_fit_parent_tgt_zero_y[n]  = tgt_poss[1].Y();
  out_fit_parent_tgt_plus_x[n]  = tgt_poss[2].X();
  out_fit_parent_tgt_plus_y[n]  = tgt_poss[2].Y();
  out_fit_parent_tgt_minus_flight_path[n] = flight_paths[0];
  out_fit_parent_tgt_zero_flight_path[n]  = flight_paths[1];
  out_fit_parent_tgt_plus_flight_path[n]  = flight_paths[2];
  out_fit_parent_x0_y[n] = x0_pos.Y();
  out_fit_parent_x0_z[n] = x0_pos.Z();
  return;
}

void track_analyzer_220715::AssociatedHBD(int n) {
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
    double tmp_min_res;
    HasAssociatedHBD(mid, track_pos, &tmp_min_res, &tmp_hbd_indexs);
    auto n_hbds = tmp_hbd_indexs.size();
    if (t == 0) {
      out_proj_plus_n_hbds[n] = n_hbds;
      out_proj_plus_hbd_min_res[n] = tmp_min_res;
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
      out_proj_minus_hbd_min_res[n] = tmp_min_res;
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

//void track_analyzer_220715::AssociatedLG(int n) {
//  for (int t = 0; t < 2; ++t) {
//    auto i = good_pair_indexs[n][t];
//    array<int, 3>      mids;
//    array<TVector3, 3> track_poss;
//    if (t == 0) {
//      mids[0] = out_plus_lg_c_mid[n];
//      mids[1] = out_plus_lg_b_mid[n];
//      mids[2] = out_plus_lg_a_mid[n];
//      track_poss[0].SetXYZ(out_fit_plus_lg_c_lx[n], out_fit_plus_lg_c_ly[n], 0.);
//      track_poss[1].SetXYZ(out_fit_plus_lg_b_lx[n], out_fit_plus_lg_b_ly[n], 0.);
//      track_poss[2].SetXYZ(out_fit_plus_lg_a_lx[n], out_fit_plus_lg_a_ly[n], 0.);
//    } else {
//      mids[0] = out_minus_lg_c_mid[n];
//      mids[1] = out_minus_lg_b_mid[n];
//      mids[2] = out_minus_lg_a_mid[n];
//      track_poss[0].SetXYZ(out_fit_minus_lg_c_lx[n], out_fit_minus_lg_c_ly[n], 0.);
//      track_poss[1].SetXYZ(out_fit_minus_lg_b_lx[n], out_fit_minus_lg_b_ly[n], 0.);
//      track_poss[2].SetXYZ(out_fit_minus_lg_a_lx[n], out_fit_minus_lg_a_ly[n], 0.);
//    }
//    vector<int> tmp_hbd_indexs;
//    double tmp_min_res;
//    HasAssociatedLG(mids, track_poss, &tmp_min_res, &tmp_hbd_indexs);
//    auto n_hbds = tmp_hbd_indexs.size();
//    if (t == 0) {
//      out_proj_plus_n_hbds[n] = n_hbds;
//      out_proj_plus_hbd_min_res[n] = tmp_min_res;
//      out_proj_plus_hbd_id[n].resize(n_hbds);
//      out_proj_plus_hbd_lx[n].resize(n_hbds);
//      out_proj_plus_hbd_ly[n].resize(n_hbds);
//      out_proj_plus_hbd_resx[n].resize(n_hbds);
//      out_proj_plus_hbd_resy[n].resize(n_hbds);
//      out_proj_plus_hbd_adc[n].resize(n_hbds);
//      out_proj_plus_hbd_size[n].resize(n_hbds);
//      out_proj_plus_hbd_eprob[n].resize(n_hbds);
//      for (int j = 0; j < n_hbds; ++j) {
//        auto index = tmp_hbd_indexs[j];
//        out_proj_plus_hbd_id[n][j]    = hbd_cluster_id->at(index);
//        out_proj_plus_hbd_lx[n][j]    = hbd_cluster_x->at(index);
//        out_proj_plus_hbd_ly[n][j]    = hbd_cluster_y->at(index);
//        out_proj_plus_hbd_resx[n][j]  = hbd_cluster_x->at(index) - track_pos.X();
//        out_proj_plus_hbd_resy[n][j]  = hbd_cluster_y->at(index) - track_pos.Y();
//        out_proj_plus_hbd_adc[n][j]   = hbd_cluster_adc->at(index);
//        out_proj_plus_hbd_size[n][j]  = hbd_cluster_size->at(index);
//        out_proj_plus_hbd_eprob[n][j] = hbd_cluster_eprob->at(index);
//      }
//    } else {
//      out_proj_minus_n_hbds[n] = n_hbds;
//      out_proj_minus_hbd_min_res[n] = tmp_min_res;
//      out_proj_minus_hbd_id[n].resize(n_hbds);
//      out_proj_minus_hbd_lx[n].resize(n_hbds);
//      out_proj_minus_hbd_ly[n].resize(n_hbds);
//      out_proj_minus_hbd_resx[n].resize(n_hbds);
//      out_proj_minus_hbd_resy[n].resize(n_hbds);
//      out_proj_minus_hbd_adc[n].resize(n_hbds);
//      out_proj_minus_hbd_size[n].resize(n_hbds);
//      out_proj_minus_hbd_eprob[n].resize(n_hbds);
//      for (int j = 0; j < n_hbds; ++j) {
//        auto index = tmp_hbd_indexs[j];
//        out_proj_minus_hbd_id[n][j]    = hbd_cluster_id->at(index);
//        out_proj_minus_hbd_lx[n][j]    = hbd_cluster_x->at(index);
//        out_proj_minus_hbd_ly[n][j]    = hbd_cluster_y->at(index);
//        out_proj_minus_hbd_resx[n][j]  = hbd_cluster_x->at(index) - track_pos.X();
//        out_proj_minus_hbd_resy[n][j]  = hbd_cluster_y->at(index) - track_pos.Y();
//        out_proj_minus_hbd_adc[n][j]   = hbd_cluster_adc->at(index);
//        out_proj_minus_hbd_size[n][j]  = hbd_cluster_size->at(index);
//        out_proj_minus_hbd_eprob[n][j] = hbd_cluster_eprob->at(index);
//      }
//    }
//  }
//  return;
//}

int track_analyzer_220715::SimpleBestTargetID(int n, double* r) {
  int tid = -1;
  *r = 10000.;
  auto plus_pos  = TVector3(out_fit_plus_tgt_minus_x[n],  out_fit_plus_tgt_minus_y[n],  0.);
  auto minus_pos = TVector3(out_fit_minus_tgt_minus_x[n], out_fit_minus_tgt_minus_y[n], 0.);
  auto dist = (plus_pos - minus_pos).Mag();
  if (dist < *r) {
    tid = kTgtMinus;
    *r  = dist;
  }
  plus_pos  = TVector3(out_fit_plus_tgt_zero_x[n],  out_fit_plus_tgt_zero_y[n],  0.);
  minus_pos = TVector3(out_fit_minus_tgt_zero_x[n], out_fit_minus_tgt_zero_y[n], 0.);
  dist = (plus_pos - minus_pos).Mag();
  if (dist < *r) {
    tid = kTgtZero;
    *r  = dist;
  }
  plus_pos  = TVector3(out_fit_plus_tgt_plus_x[n],  out_fit_plus_tgt_plus_y[n],  0.);
  minus_pos = TVector3(out_fit_minus_tgt_plus_x[n], out_fit_minus_tgt_plus_y[n], 0.);
  dist = (plus_pos - minus_pos).Mag();
  if (dist < *r) {
    tid = kTgtPlus;
    *r  = dist;
  }
  return tid;
}

void track_analyzer_220715::SimpleAnalysis(int n) {
  auto best_tid = SimpleBestTargetID(n, &out_simple_best_tgt_r[n]);
  out_simple_best_tgt_id[n] = best_tid;
  TVector3 pmom;
  TVector3 mmom;
  if (best_tid == kTgtMinus) {
    pmom = TVector3(out_fit_plus_tgt_minus_mom_x[n],  out_fit_plus_tgt_minus_mom_y[n],  out_fit_plus_tgt_minus_mom_z[n]);
    mmom = TVector3(out_fit_minus_tgt_minus_mom_x[n], out_fit_minus_tgt_minus_mom_y[n], out_fit_minus_tgt_minus_mom_z[n]);
  } else if (best_tid == kTgtZero) {
    pmom = TVector3(out_fit_plus_tgt_zero_mom_x[n],  out_fit_plus_tgt_zero_mom_y[n],  out_fit_plus_tgt_zero_mom_z[n]);
    mmom = TVector3(out_fit_minus_tgt_zero_mom_x[n], out_fit_minus_tgt_zero_mom_y[n], out_fit_minus_tgt_zero_mom_z[n]);
  } else if (best_tid == kTgtPlus) {
    pmom = TVector3(out_fit_plus_tgt_plus_mom_x[n],  out_fit_plus_tgt_plus_mom_y[n],  out_fit_plus_tgt_plus_mom_z[n]);
    mmom = TVector3(out_fit_minus_tgt_plus_mom_x[n], out_fit_minus_tgt_plus_mom_y[n], out_fit_minus_tgt_plus_mom_z[n]);
  }
  out_ee_mass_at_best_tgt[n]   = CalcMass(kEE,   pmom, mmom);
  out_pipi_mass_at_best_tgt[n] = CalcMass(kPiPi, pmom, mmom);
  out_pip_mass_at_best_tgt[n]  = CalcMass(kPiP,  pmom, mmom);
  out_kk_mass_at_best_tgt[n]   = CalcMass(kKK,   pmom, mmom);
  return;
}

void track_analyzer_220715::AddPairOrders() {
  vector<pair<double, int>> tmp_params(out_n_pairs);
  if (kAnalyzeFlag == kAnalyzePairFit) {
    for (int i = 0; i < out_n_pairs; ++i) {
      tmp_params[i] = make_pair(out_chi2[i], i);
    }
  } else if (kAnalyzeFlag == kAnalyzeNearestPoint) {
    for (int i = 0; i < out_n_pairs; ++i) {
      tmp_params[i] = make_pair(out_distance[i], i);
    }
  }
  sort(tmp_params.begin(), tmp_params.end());
  for (int i = 0; i < out_n_pairs; ++i) {
    out_pair_order[i] = tmp_params[i].second;
  }
  return;
}

void track_analyzer_220715::TmpProjectionX0(int n) {
  vector<Hep3Vector> cross_pos;
  vector<Hep3Vector> cross_mom;
  for (int c = 0; c < kNumCharges; ++c) {
    Hep3Vector init_pos;
    Hep3Vector init_mom;
    int        charge;
    if (c == kChargePlus) {
      init_pos.set(out_plus_single_fit_init_pos_x[n] * 0.1, out_plus_single_fit_init_pos_y[n] * 0.1, out_plus_single_fit_init_pos_z[n] * 0.1);
      init_mom.set(out_plus_single_fit_init_mom_x[n],       out_plus_single_fit_init_mom_y[n],       out_plus_single_fit_init_mom_z[n]);
      charge = 1;
    } else {
      init_pos.set(out_minus_single_fit_init_pos_x[n] * 0.1, out_minus_single_fit_init_pos_y[n] * 0.1, out_minus_single_fit_init_pos_z[n] * 0.1);
      init_mom.set(out_minus_single_fit_init_mom_x[n],       out_minus_single_fit_init_mom_y[n],       out_minus_single_fit_init_mom_z[n]);
      charge = -1;
    }
    E16ANA_StepTrack step_track(bfield_map, init_pos, init_mom, charge, kStepTrackSizeCm, kStepTrackArraySize);
    auto flag = step_track.CrossXconstPlane(0., &cross_pos, &cross_mom);
    auto n_points = cross_pos.size();
    if (c == kChargePlus) {
      out_tmp_fit_plus_x0_flag[n]    = flag;
      out_tmp_fit_plus_x0_n_cross[n] = n_points;
      out_tmp_fit_plus_x0_pos_y[n].resize(n_points);
      out_tmp_fit_plus_x0_pos_z[n].resize(n_points);
      out_tmp_fit_plus_x0_mom_x[n].resize(n_points);
      out_tmp_fit_plus_x0_mom_y[n].resize(n_points);
      out_tmp_fit_plus_x0_mom_z[n].resize(n_points);
      for (int i = 0; i < n_points; ++i) {
        out_tmp_fit_plus_x0_pos_y[n][i] = cross_pos[i].y() * 10.;
        out_tmp_fit_plus_x0_pos_z[n][i] = cross_pos[i].z() * 10.;
        out_tmp_fit_plus_x0_mom_z[n][i] = cross_mom[i].x();
        out_tmp_fit_plus_x0_mom_y[n][i] = cross_mom[i].y();
        out_tmp_fit_plus_x0_mom_z[n][i] = cross_mom[i].z();
      }
    } else {
      out_tmp_fit_minus_x0_flag[n]    = flag;
      out_tmp_fit_minus_x0_n_cross[n] = n_points;
      out_tmp_fit_plus_x0_pos_y[n].resize(n_points);
      out_tmp_fit_minus_x0_pos_y[n].resize(n_points);
      out_tmp_fit_minus_x0_pos_z[n].resize(n_points);
      out_tmp_fit_minus_x0_mom_x[n].resize(n_points);
      out_tmp_fit_minus_x0_mom_y[n].resize(n_points);
      out_tmp_fit_minus_x0_mom_z[n].resize(n_points);
      for (int i = 0; i < n_points; ++i) {
        out_tmp_fit_minus_x0_pos_y[n][i] = cross_pos[i].y() * 10.;
        out_tmp_fit_minus_x0_pos_z[n][i] = cross_pos[i].z() * 10.;
        out_tmp_fit_minus_x0_mom_z[n][i] = cross_mom[i].x();
        out_tmp_fit_minus_x0_mom_y[n][i] = cross_mom[i].y();
        out_tmp_fit_minus_x0_mom_z[n][i] = cross_mom[i].z();
      }
    }
  }
  return;
}

#ifdef TMP_SOME_Z
void track_analyzer_220715::TmpProjectionSomeZ(int n) {
  if (kForgiveSameCharge) {
    cerr << "TmpProjectionSomeZ() don't take care of same charge pair" << endl;
    return;
  }
  out_tmp_plus_static_flag[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_plus_static_pos_x[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_plus_static_pos_y[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_plus_static_pos_z[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_plus_static_mom_x[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_plus_static_mom_y[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_plus_static_mom_z[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_minus_static_flag[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_minus_static_pos_x[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_minus_static_pos_y[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_minus_static_pos_z[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_minus_static_mom_x[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_minus_static_mom_y[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_minus_static_mom_z[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_static_distance[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_static_mom_angle[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_static_pipi_mass[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_dynamic_chi2[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_dynamic_vtx_x[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_dynamic_vtx_y[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_dynamic_vtx_z[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_plus_dynamic_flag[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_plus_dynamic_pos_x[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_plus_dynamic_pos_y[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_plus_dynamic_pos_z[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_plus_dynamic_mom_x[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_plus_dynamic_mom_y[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_plus_dynamic_mom_z[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_minus_dynamic_flag[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_minus_dynamic_pos_x[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_minus_dynamic_pos_y[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_minus_dynamic_pos_z[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_minus_dynamic_mom_x[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_minus_dynamic_mom_y[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_minus_dynamic_mom_z[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_dynamic_distance[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_dynamic_mom_angle[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  out_tmp_dynamic_pipi_mass[n].assign(2 * kTmpNumProjectionZHalf, kErrorNum);
  
  array<array<array<TVector3, 2>, 2 * kTmpNumProjectionZHalf>, kTmpNumZMethods> poss;
  array<array<array<TVector3, 2>, 2 * kTmpNumProjectionZHalf>, kTmpNumZMethods> moms;
  if (kAnalyzeFlag == kAnalyzePairFit) {
    auto z0 = out_vtx_z[n];
    for (int zid = 0; zid < 2 * kTmpNumProjectionZHalf; ++zid) {
      fitter->Clear();
      double z = kTmpProjectionZWidth * (zid - kTmpNumProjectionZHalf);
      if (zid >= kTmpNumProjectionZHalf) {
        z = kTmpProjectionZWidth * (zid - kTmpNumProjectionZHalf + 1);
      }
      z += z0;
      fitter->SetInitialVertex(TVector3(0., 0., z), kVertexSigma);
      for (int c = 0; c < 2; ++c) {
        if (c == kChargePlus) {
          fitter->SetCharge(c, 1.);
          fitter->SetInitialMomentum(c, TVector3(out_plus_mom_x[n], out_plus_mom_y[n], out_plus_mom_z[n]));
          fitter->AddHit(c, 0, geometry->SSD(ModuleID2013(out_plus_ssd_mid[n])), TVector3(out_hit_plus_ssd_lx[n], 0., 0.), kSSDSigma);
          fitter->AddHit(c, 1, geometry->GTR(ModuleID2013(out_plus_gtr100_mid[n]), 0), TVector3(out_hit_plus_gtr100_lx[n], out_hit_plus_gtr100_ly[n], 0.),
                         kGTR100Sigma);
          fitter->AddHit(c, 2, geometry->GTR(ModuleID2013(out_plus_gtr200_mid[n]), 1), TVector3(out_hit_plus_gtr200_lx[n], out_hit_plus_gtr200_ly[n], 0.),
                         kGTR200Sigma);
          fitter->AddHit(c, 3, geometry->GTR(ModuleID2013(out_plus_gtr300_mid[n]), 2), TVector3(out_hit_plus_gtr300_lx[n], out_hit_plus_gtr300_ly[n], 0.),
                         kGTR300Sigma);
        } else {
          fitter->SetCharge(c, -1.);
          fitter->SetInitialMomentum(c, TVector3(out_minus_mom_x[n], out_minus_mom_y[n], out_minus_mom_z[n]));
          fitter->AddHit(c, 0, geometry->SSD(ModuleID2013(out_minus_ssd_mid[n])), TVector3(out_hit_minus_ssd_lx[n], 0., 0.), kSSDSigma);
          fitter->AddHit(c, 1, geometry->GTR(ModuleID2013(out_minus_gtr100_mid[n]), 0), TVector3(out_hit_minus_gtr100_lx[n], out_hit_minus_gtr100_ly[n], 0.),
                         kGTR100Sigma);
          fitter->AddHit(c, 2, geometry->GTR(ModuleID2013(out_minus_gtr200_mid[n]), 1), TVector3(out_hit_minus_gtr200_lx[n], out_hit_minus_gtr200_ly[n], 0.),
                         kGTR200Sigma);
          fitter->AddHit(c, 3, geometry->GTR(ModuleID2013(out_minus_gtr300_mid[n]), 2), TVector3(out_hit_minus_gtr300_lx[n], out_hit_minus_gtr300_ly[n], 0.),
                         kGTR300Sigma);
        }
      }
      fitter->SetRungeKuttaStepSize(kStepSize);
      fitter->SetMaxSteps(kMaxSteps);
      bool fix_vtx_z = true;
      double vtx_z_range[2] = {-10000., 10000.};
      auto chi2 = fitter->Fit(kFixVtxXY, kFixPy, fix_vtx_z, kStrategy, kMaxFuncCalls,
                              kVtxXRange[0], kVtxXRange[1], kVtxYRange[0], kVtxYRange[1], vtx_z_range[0], vtx_z_range[1]);
      auto vtx = fitter->GetFitVertex();
      array<TVector3, 2> moms;
//      array<array<TVector3, 4>, 2> lposs;
//      array<array<TVector3, 4>, 2> lmoms;
//      array<array<TVector3, 4>, 2> gposs;
//      array<array<TVector3, 4>, 2> gmoms;
      for (int t = 0; t < 2; ++t) {
        moms[t] = fitter->GetFitMomentum(t);
//        for (int l = 0; l < 4; ++l) {
//          vector<int>      tmp_mids;
//          vector<TVector3> tmp_lposs;
//          vector<TVector3> tmp_lmoms;
//          fitter->GetFitLPos(t, l, tmp_mids, tmp_lposs);
//          auto mid = tmp_mids[0];
//          lposs[t][l] = tmp_lposs[0];
//          fitter->GetFitLMom(t, l, tmp_mids, tmp_lmoms);
//          lmoms[t][l] = tmp_lmoms[0];
//          if (l == 0) {
//            gposs[t][l] = geometry->SSD(mid)->GetGPos(lposs[t][l]);
//            gmoms[t][l] = geometry->SSD(mid)->GetGMom(lmoms[t][l]);
//          } else {
//            gposs[t][l] = geometry->GTR(mid, l - 1)->GetGPos(lposs[t][l]);
//            gmoms[t][l] = geometry->GTR(mid, l - 1)->GetGMom(lposs[t][l]);
//          }
//        }
      }
      out_tmp_dynamic_chi2[n][zid]        = chi2;
      out_tmp_dynamic_vtx_x[n][zid]       = vtx.X();
      out_tmp_dynamic_vtx_y[n][zid]       = vtx.Y();
      out_tmp_dynamic_vtx_z[n][zid]       = vtx.Z();
      out_tmp_plus_dynamic_mom_x[n][zid]  = moms[0].X();
      out_tmp_plus_dynamic_mom_y[n][zid]  = moms[0].Y();
      out_tmp_plus_dynamic_mom_z[n][zid]  = moms[0].Z();
      out_tmp_minus_dynamic_mom_x[n][zid] = moms[1].X();
      out_tmp_minus_dynamic_mom_y[n][zid] = moms[1].Y();
      out_tmp_minus_dynamic_mom_z[n][zid] = moms[1].Z();
      out_tmp_dynamic_pipi_mass[n][zid]   = CalcMass(kPiPi, moms[0], moms[1]);
    }
  } else if (kAnalyzeFlag == kAnalyzeNearestPoint) {
    for (int c = 0; c < kNumCharges; ++c) {
      Hep3Vector init_pos;
      Hep3Vector init_mom;
      if (kAnalyzeFlag == kAnalyzePairFit) {
        init_pos.set(out_vtx_x[n] * 0.1, out_vtx_y[n] * 0.1, out_vtx_z[n] * 0.1);
        if (c == kChargePlus) {
          init_mom.set(out_plus_mom_x[n], out_plus_mom_y[n], out_plus_mom_z[n]);
        } else {
          init_mom.set(out_minus_mom_x[n], out_minus_mom_y[n], out_minus_mom_z[n]);
        }
      } else if (kAnalyzeFlag == kAnalyzeNearestPoint) {
        if (c == kChargePlus) {
          init_pos.set(out_plus_single_fit_init_pos_x[n] * 0.1, out_plus_single_fit_init_pos_y[n] * 0.1, out_plus_single_fit_init_pos_z[n] * 0.1);
          init_mom.set(out_plus_single_fit_init_mom_x[n],       out_plus_single_fit_init_mom_y[n],       out_plus_single_fit_init_mom_z[n]);
        } else {
          init_pos.set(out_minus_single_fit_init_pos_x[n] * 0.1, out_minus_single_fit_init_pos_y[n] * 0.1, out_minus_single_fit_init_pos_z[n] * 0.1);
          init_mom.set(out_minus_single_fit_init_mom_x[n],       out_minus_single_fit_init_mom_y[n],       out_minus_single_fit_init_mom_z[n]);
        }
      } else {
        cerr << "unimplemented function: TmpProjectionSomeZ()" << endl;
        return;
      }
      
      double charge = 1.;
      if (c == kChargeMinus) {
        charge = -1.;
      }
//      if (kForgiveSameCharge) {
//        if (ChargeID(rk_charge->at(i)) == kChargePlus) {
//          charge = 1.;
//        } else {
//          charge = -1.;
//        }
//      }
      E16ANA_StepTrack step_track(bfield_map, init_pos, init_mom, charge, kStepTrackSizeCm, kStepTrackArraySize);
      Hep3Vector cross_pos;
      Hep3Vector cross_mom;
      auto z0 = out_vtx_z[n];
      for (int m = 0; m < kTmpNumZMethods; ++m) { // method. 0 : static z, 1 : dynamic z
        for (int zid = 0; zid < 2 * kTmpNumProjectionZHalf; ++zid) {
          double z = kTmpProjectionZWidth * (zid - kTmpNumProjectionZHalf);
          if (zid >= kTmpNumProjectionZHalf) {
            z = kTmpProjectionZWidth * (zid - kTmpNumProjectionZHalf + 1);
          }
          if (m == kTmpZDynamic) {
            z += z0;
          }
          auto flag = step_track.CrossZconstPlane(z * 0.1, cross_pos, cross_mom);
          auto pos = TVector3(cross_pos.x() * 10., cross_pos.y() * 10., cross_pos.z() * 10.);
          auto mom = TVector3(cross_mom.x(),       cross_mom.y(),       cross_mom.z());
          poss[m][zid][c] = pos;
          moms[m][zid][c] = mom;
          if (c == kChargePlus) {
            if (m == kTmpZStatic) {
              out_tmp_plus_static_flag[n][zid] = flag;
              if (flag != -1) {
                out_tmp_plus_static_pos_x[n][zid] = pos.X();
                out_tmp_plus_static_pos_y[n][zid] = pos.Y();
                out_tmp_plus_static_pos_z[n][zid] = pos.Z();
                out_tmp_plus_static_mom_x[n][zid] = mom.X();
                out_tmp_plus_static_mom_y[n][zid] = mom.Y();
                out_tmp_plus_static_mom_z[n][zid] = mom.Z();
              }
            } else {
              out_tmp_plus_dynamic_flag[n][zid] = flag;
              if (flag != -1) {
                out_tmp_plus_dynamic_pos_x[n][zid] = pos.X();
                out_tmp_plus_dynamic_pos_y[n][zid] = pos.Y();
                out_tmp_plus_dynamic_pos_z[n][zid] = pos.Z();
                out_tmp_plus_dynamic_mom_x[n][zid] = mom.X();
                out_tmp_plus_dynamic_mom_y[n][zid] = mom.Y();
                out_tmp_plus_dynamic_mom_z[n][zid] = mom.Z();
              }
            }
          } else {
            if (m == kTmpZStatic) {
              out_tmp_minus_static_flag[n][zid] = flag;
              if (flag != -1) {
                out_tmp_minus_static_pos_x[n][zid] = pos.X();
                out_tmp_minus_static_pos_y[n][zid] = pos.Y();
                out_tmp_minus_static_pos_z[n][zid] = pos.Z();
                out_tmp_minus_static_mom_x[n][zid] = mom.X();
                out_tmp_minus_static_mom_y[n][zid] = mom.Y();
                out_tmp_minus_static_mom_z[n][zid] = mom.Z();
              }
            } else {
              out_tmp_minus_dynamic_flag[n][zid] = flag;
              if (flag != -1) {
                out_tmp_minus_dynamic_pos_x[n][zid] = pos.X();
                out_tmp_minus_dynamic_pos_y[n][zid] = pos.Y();
                out_tmp_minus_dynamic_pos_z[n][zid] = pos.Z();
                out_tmp_minus_dynamic_mom_x[n][zid] = mom.X();
                out_tmp_minus_dynamic_mom_y[n][zid] = mom.Y();
                out_tmp_minus_dynamic_mom_z[n][zid] = mom.Z();
              }
            }
          }
        }
      }
      for (int z = 0; z < 2 * kTmpNumProjectionZHalf; ++z) {
        out_tmp_static_distance[n][z]   = (poss[kTmpZStatic][z][kChargePlus] - poss[kTmpZStatic][z][kChargeMinus]).Mag();
        out_tmp_static_mom_angle[n][z]  = moms[kTmpZStatic][z][kChargePlus].Angle(moms[kTmpZStatic][z][kChargeMinus]);
        out_tmp_static_pipi_mass[n][z]  = CalcMass(kPiPi, moms[kTmpZStatic][z][kChargePlus], moms[kTmpZStatic][z][kChargeMinus]);
        out_tmp_dynamic_distance[n][z]  = (poss[kTmpZDynamic][z][kChargePlus] - poss[kTmpZDynamic][z][kChargeMinus]).Mag();
        out_tmp_dynamic_mom_angle[n][z] = moms[kTmpZDynamic][z][kChargePlus].Angle(moms[kTmpZDynamic][z][kChargeMinus]);
        out_tmp_dynamic_pipi_mass[n][z] = CalcMass(kPiPi, moms[kTmpZDynamic][z][kChargePlus], moms[kTmpZDynamic][z][kChargeMinus]);
      }
    }
  }
  return;
}
#endif // TMP_SOME_Z

void track_analyzer_220715::FillCommonBranches() {
  for (int i = 0; i < out_n_pairs; ++i) {
    auto i0 = good_pair_indexs[i][0];
    auto i1 = good_pair_indexs[i][1];
    out_plus_rough_fit_init_pos_x[i]   = rk_hit_init_pos_gx->at(i0);
    out_plus_rough_fit_init_pos_y[i]   = rk_hit_init_pos_gy->at(i0);
    out_plus_rough_fit_init_pos_z[i]   = rk_hit_init_pos_gz->at(i0);
    out_plus_rough_fit_init_mom_x[i]   = rk_hit_init_mom_gx->at(i0);
    out_plus_rough_fit_init_mom_y[i]   = rk_hit_init_mom_gy->at(i0);
    out_plus_rough_fit_init_mom_z[i]   = rk_hit_init_mom_gz->at(i0);
    out_plus_single_fit_init_pos_x[i]  = rk_fit_init_pos_gx->at(i0);
    out_plus_single_fit_init_pos_y[i]  = rk_fit_init_pos_gy->at(i0);
    out_plus_single_fit_init_pos_z[i]  = rk_fit_init_pos_gz->at(i0);
    out_plus_single_fit_init_mom_x[i]  = rk_fit_init_mom_gx->at(i0);
    out_plus_single_fit_init_mom_y[i]  = rk_fit_init_mom_gy->at(i0);
    out_plus_single_fit_init_mom_z[i]  = rk_fit_init_mom_gz->at(i0);
    out_plus_track_id[i]               = track_id->at(i0);
    out_plus_charge_id[i]              = ChargeID(rk_charge->at(i0));
    out_hit_plus_ssd_id[i]             = rk_hit_ssd_id->at(i0);
    out_hit_plus_ssd_lx[i]             = rk_hit_ssd_x->at(i0);
    out_hit_plus_ssd_t[i]              = rk_hit_ssd_t->at(i0);
    out_hit_plus_ssd_adc[i]            = rk_hit_ssd_adc->at(i0);
//    out_hit_plus_ssd_size[i]      = rk_hit_ssd_
    out_hit_plus_gtr100_xid[i]         = rk_hit_gtr100_xid->at(i0);
    out_hit_plus_gtr100_yid[i]         = rk_hit_gtr100_yid->at(i0);
    out_hit_plus_gtr100_lx[i]          = rk_hit_gtr100_tx2->at(i0);
    out_hit_plus_gtr100_ly[i]          = rk_hit_gtr100_ty->at(i0);
    out_hit_plus_gtr100_xt[i]          = rk_hit_gtr100_xt2->at(i0);
    out_hit_plus_gtr100_yt[i]          = rk_hit_gtr100_yt2->at(i0);
    out_hit_plus_gtr100_xadc[i]        = rk_hit_gtr100_xadc->at(i0);
    out_hit_plus_gtr100_yadc[i]        = rk_hit_gtr100_yadc->at(i0);
//    out_hit_plus_gtr100_xsize[i]       = rk_hit_gtr100_
    out_hit_plus_gtr200_xid[i]         = rk_hit_gtr200_xid->at(i0);
    out_hit_plus_gtr200_yid[i]         = rk_hit_gtr200_yid->at(i0);
    out_hit_plus_gtr200_lx[i]          = rk_hit_gtr200_tx2->at(i0);
    out_hit_plus_gtr200_ly[i]          = rk_hit_gtr200_ty->at(i0);
    out_hit_plus_gtr200_xt[i]          = rk_hit_gtr200_xt2->at(i0);
    out_hit_plus_gtr200_yt[i]          = rk_hit_gtr200_yt2->at(i0);
    out_hit_plus_gtr200_xadc[i]        = rk_hit_gtr200_xadc->at(i0);
    out_hit_plus_gtr200_yadc[i]        = rk_hit_gtr200_yadc->at(i0);
    out_hit_plus_gtr300_xid[i]         = rk_hit_gtr300_xid->at(i0);
    out_hit_plus_gtr300_yid[i]         = rk_hit_gtr300_yid->at(i0);
    out_hit_plus_gtr300_lx[i]          = rk_hit_gtr300_tx2->at(i0);
    out_hit_plus_gtr300_ly[i]          = rk_hit_gtr300_ty->at(i0);
    out_hit_plus_gtr300_xt[i]          = rk_hit_gtr300_xt2->at(i0);
    out_hit_plus_gtr300_yt[i]          = rk_hit_gtr300_yt2->at(i0);
    out_hit_plus_gtr300_xadc[i]        = rk_hit_gtr300_xadc->at(i0);
    out_hit_plus_gtr300_yadc[i]        = rk_hit_gtr300_yadc->at(i0);
    out_minus_rough_fit_init_pos_x[i]  = rk_hit_init_pos_gx->at(i1);
    out_minus_rough_fit_init_pos_y[i]  = rk_hit_init_pos_gy->at(i1);
    out_minus_rough_fit_init_pos_z[i]  = rk_hit_init_pos_gz->at(i1);
    out_minus_rough_fit_init_mom_x[i]  = rk_hit_init_mom_gx->at(i1);
    out_minus_rough_fit_init_mom_y[i]  = rk_hit_init_mom_gy->at(i1);
    out_minus_rough_fit_init_mom_z[i]  = rk_hit_init_mom_gz->at(i1);
    out_minus_single_fit_init_pos_x[i] = rk_fit_init_pos_gx->at(i1);
    out_minus_single_fit_init_pos_y[i] = rk_fit_init_pos_gy->at(i1);
    out_minus_single_fit_init_pos_z[i] = rk_fit_init_pos_gz->at(i1);
    out_minus_single_fit_init_mom_x[i] = rk_fit_init_mom_gx->at(i1);
    out_minus_single_fit_init_mom_y[i] = rk_fit_init_mom_gy->at(i1);
    out_minus_single_fit_init_mom_z[i] = rk_fit_init_mom_gz->at(i1);
    out_minus_track_id[i]              = track_id->at(i1);
    out_minus_charge_id[i]             = ChargeID(rk_charge->at(i1));
    out_hit_minus_ssd_id[i]            = rk_hit_ssd_id->at(i1);
    out_hit_minus_ssd_lx[i]            = rk_hit_ssd_x->at(i1);
    out_hit_minus_ssd_t[i]             = rk_hit_ssd_t->at(i1);
    out_hit_minus_ssd_adc[i]           = rk_hit_ssd_adc->at(i1);
//    out_hit_minus_ssd_size[i] =      rk_hit_ssd_
    out_hit_minus_gtr100_xid[i]        = rk_hit_gtr100_xid->at(i1);
    out_hit_minus_gtr100_yid[i]        = rk_hit_gtr100_yid->at(i1);
    out_hit_minus_gtr100_lx[i]         = rk_hit_gtr100_tx2->at(i1);
    out_hit_minus_gtr100_ly[i]         = rk_hit_gtr100_ty->at(i1);
    out_hit_minus_gtr100_xt[i]         = rk_hit_gtr100_xt2->at(i1);
    out_hit_minus_gtr100_yt[i]         = rk_hit_gtr100_yt2->at(i1);
    out_hit_minus_gtr100_xadc[i]       = rk_hit_gtr100_xadc->at(i1);
    out_hit_minus_gtr100_yadc[i]       = rk_hit_gtr100_yadc->at(i1);
//    out_hit_minus_gtr100_xsize[i]  = rk_hit_gtr100_
    out_hit_minus_gtr200_xid[i]        = rk_hit_gtr200_xid->at(i1);
    out_hit_minus_gtr200_yid[i]        = rk_hit_gtr200_yid->at(i1);
    out_hit_minus_gtr200_lx[i]         = rk_hit_gtr200_tx2->at(i1);
    out_hit_minus_gtr200_ly[i]         = rk_hit_gtr200_ty->at(i1);
    out_hit_minus_gtr200_xt[i]         = rk_hit_gtr200_xt2->at(i1);
    out_hit_minus_gtr200_yt[i]         = rk_hit_gtr200_yt2->at(i1);
    out_hit_minus_gtr200_xadc[i]       = rk_hit_gtr200_xadc->at(i1);
    out_hit_minus_gtr200_yadc[i]       = rk_hit_gtr200_yadc->at(i1);
    out_hit_minus_gtr300_xid[i]        = rk_hit_gtr300_xid->at(i1);
    out_hit_minus_gtr300_yid[i]        = rk_hit_gtr300_yid->at(i1);
    out_hit_minus_gtr300_lx[i]         = rk_hit_gtr300_tx2->at(i1);
    out_hit_minus_gtr300_ly[i]         = rk_hit_gtr300_ty->at(i1);
    out_hit_minus_gtr300_xt[i]         = rk_hit_gtr300_xt2->at(i1);
    out_hit_minus_gtr300_yt[i]         = rk_hit_gtr300_yt2->at(i1);
    out_hit_minus_gtr300_xadc[i]       = rk_hit_gtr300_xadc->at(i1);
    out_hit_minus_gtr300_yadc[i]       = rk_hit_gtr300_yadc->at(i1);
    out_dir_id[i]                      = DirID(rk_fit_gtr300_mid->at(i0), rk_fit_gtr300_mid->at(i1));
    out_plus_ssd_mid[i]                = rk_fit_ssd_mid->at(i0);
    out_plus_gtr100_mid[i]             = rk_fit_gtr100_mid->at(i0);
    out_plus_gtr200_mid[i]             = rk_fit_gtr200_mid->at(i0);
    out_plus_gtr300_mid[i]             = rk_fit_gtr300_mid->at(i0);
    out_minus_ssd_mid[i]               = rk_fit_ssd_mid->at(i1);
    out_minus_gtr100_mid[i]            = rk_fit_gtr100_mid->at(i1);
    out_minus_gtr200_mid[i]            = rk_fit_gtr200_mid->at(i1);
    out_minus_gtr300_mid[i]            = rk_fit_gtr300_mid->at(i1);
    if (kAnalyzeFlag == kAnalyzePairFit) {
      ProjectionHBDAndLG(i);
      ProjectionTargets(i);
    } else if (kAnalyzeFlag == kAnalyzeNearestPoint) {
      out_plus_hbd_mid[i]              = rk_fit_hbd_mid->at(i0);
      out_plus_lg_c_mid[i]             = rk_fit_lg_c_mid->at(i0);
      out_plus_lg_b_mid[i]             = rk_fit_lg_b_mid->at(i0);
      out_plus_lg_a_mid[i]             = rk_fit_lg_a_mid->at(i0);
      out_minus_hbd_mid[i]             = rk_fit_hbd_mid->at(i1);
      out_minus_lg_c_mid[i]            = rk_fit_lg_c_mid->at(i1);
      out_minus_lg_b_mid[i]            = rk_fit_lg_b_mid->at(i1);
      out_minus_lg_a_mid[i]            = rk_fit_lg_a_mid->at(i1);
      out_fit_plus_hbd_lx[i]           = rk_fit_hbd_x->at(i0);
      out_fit_plus_hbd_ly[i]           = rk_fit_hbd_y->at(i0);
      out_fit_plus_lg_c_lx[i]          = rk_fit_lg_c_x->at(i0);
      out_fit_plus_lg_c_ly[i]          = rk_fit_lg_c_y->at(i0);
      out_fit_plus_lg_b_lx[i]          = rk_fit_lg_b_x->at(i0);
      out_fit_plus_lg_b_ly[i]          = rk_fit_lg_b_y->at(i0);
      out_fit_plus_lg_a_lx[i]          = rk_fit_lg_a_x->at(i0);
      out_fit_plus_lg_a_ly[i]          = rk_fit_lg_a_y->at(i0);
      out_fit_plus_tgt_minus_x[i]      = rk_proj_tgt0_gx->at(i0);
      out_fit_plus_tgt_minus_y[i]      = rk_proj_tgt0_gy->at(i0);
      out_fit_plus_tgt_zero_x[i]       = rk_proj_tgt1_gx->at(i0);
      out_fit_plus_tgt_zero_y[i]       = rk_proj_tgt1_gy->at(i0);
      out_fit_plus_tgt_plus_x[i]       = rk_proj_tgt2_gx->at(i0);
      out_fit_plus_tgt_plus_y[i]       = rk_proj_tgt2_gy->at(i0);
      out_fit_plus_x0_y[i]             = rk_proj_x0_gy->at(i0);
      out_fit_plus_x0_z[i]             = rk_proj_x0_gz->at(i0);
      out_fit_minus_hbd_lx[i]          = rk_fit_hbd_x->at(i1);
      out_fit_minus_hbd_ly[i]          = rk_fit_hbd_y->at(i1);
      out_fit_minus_lg_c_lx[i]         = rk_fit_lg_c_x->at(i1);
      out_fit_minus_lg_c_ly[i]         = rk_fit_lg_c_y->at(i1);
      out_fit_minus_lg_b_lx[i]         = rk_fit_lg_b_x->at(i1);
      out_fit_minus_lg_b_ly[i]         = rk_fit_lg_b_y->at(i1);
      out_fit_minus_lg_a_lx[i]         = rk_fit_lg_a_x->at(i1);
      out_fit_minus_lg_a_ly[i]         = rk_fit_lg_a_y->at(i1);
      out_fit_minus_tgt_minus_x[i]     = rk_proj_tgt0_gx->at(i1);
      out_fit_minus_tgt_minus_y[i]     = rk_proj_tgt0_gy->at(i1);
      out_fit_minus_tgt_zero_x[i]      = rk_proj_tgt1_gx->at(i1);
      out_fit_minus_tgt_zero_y[i]      = rk_proj_tgt1_gy->at(i1);
      out_fit_minus_tgt_plus_x[i]      = rk_proj_tgt2_gx->at(i1);
      out_fit_minus_tgt_plus_y[i]      = rk_proj_tgt2_gy->at(i1);
      out_fit_minus_x0_y[i]            = rk_proj_x0_gy->at(i1);
      out_fit_minus_x0_z[i]            = rk_proj_x0_gz->at(i1);
      out_fit_plus_ssd_mom_lx[i]       = rk_fit_ssd_mom_x->at(i0);
      out_fit_plus_ssd_mom_ly[i]       = rk_fit_ssd_mom_y->at(i0);
      out_fit_plus_ssd_mom_lz[i]       = rk_fit_ssd_mom_z->at(i0);
      out_fit_plus_ssd_mom_gx[i]       = rk_fit_ssd_mom_gx->at(i0);
      out_fit_plus_ssd_mom_gy[i]       = rk_fit_ssd_mom_gy->at(i0);
      out_fit_plus_ssd_mom_gz[i]       = rk_fit_ssd_mom_gz->at(i0);
      out_fit_plus_gtr100_mom_lx[i]    = rk_fit_gtr100_mom_x->at(i0);
      out_fit_plus_gtr100_mom_ly[i]    = rk_fit_gtr100_mom_y->at(i0);
      out_fit_plus_gtr100_mom_lz[i]    = rk_fit_gtr100_mom_z->at(i0);
      out_fit_plus_gtr100_mom_gx[i]    = rk_fit_gtr100_mom_gx->at(i0);
      out_fit_plus_gtr100_mom_gy[i]    = rk_fit_gtr100_mom_gy->at(i0);
      out_fit_plus_gtr100_mom_gz[i]    = rk_fit_gtr100_mom_gz->at(i0);
      out_fit_plus_gtr200_mom_lx[i]    = rk_fit_gtr200_mom_x->at(i0);
      out_fit_plus_gtr200_mom_ly[i]    = rk_fit_gtr200_mom_y->at(i0);
      out_fit_plus_gtr200_mom_lz[i]    = rk_fit_gtr200_mom_z->at(i0);
      out_fit_plus_gtr200_mom_gx[i]    = rk_fit_gtr200_mom_gx->at(i0);
      out_fit_plus_gtr200_mom_gy[i]    = rk_fit_gtr200_mom_gy->at(i0);
      out_fit_plus_gtr200_mom_gz[i]    = rk_fit_gtr200_mom_gz->at(i0);
      out_fit_plus_gtr300_mom_lx[i]    = rk_fit_gtr300_mom_x->at(i0);
      out_fit_plus_gtr300_mom_ly[i]    = rk_fit_gtr300_mom_y->at(i0);
      out_fit_plus_gtr300_mom_lz[i]    = rk_fit_gtr300_mom_z->at(i0);
      out_fit_plus_gtr300_mom_gx[i]    = rk_fit_gtr300_mom_gx->at(i0);
      out_fit_plus_gtr300_mom_gy[i]    = rk_fit_gtr300_mom_gy->at(i0);
      out_fit_plus_gtr300_mom_gz[i]    = rk_fit_gtr300_mom_gz->at(i0);
      out_fit_plus_hbd_mom_lx[i]       = rk_fit_hbd_mom_x->at(i0);
      out_fit_plus_hbd_mom_ly[i]       = rk_fit_hbd_mom_y->at(i0);
      out_fit_plus_hbd_mom_lz[i]       = rk_fit_hbd_mom_z->at(i0);
      out_fit_plus_hbd_mom_gx[i]       = rk_fit_hbd_mom_gx->at(i0);
      out_fit_plus_hbd_mom_gy[i]       = rk_fit_hbd_mom_gy->at(i0);
      out_fit_plus_hbd_mom_gz[i]       = rk_fit_hbd_mom_gz->at(i0);
      out_fit_plus_lg_c_mom_lx[i]      = rk_fit_lg_c_mom_x->at(i0);
      out_fit_plus_lg_c_mom_ly[i]      = rk_fit_lg_c_mom_y->at(i0);
      out_fit_plus_lg_c_mom_lz[i]      = rk_fit_lg_c_mom_z->at(i0);
      out_fit_plus_lg_c_mom_gx[i]      = rk_fit_lg_c_mom_gx->at(i0);
      out_fit_plus_lg_c_mom_gy[i]      = rk_fit_lg_c_mom_gy->at(i0);
      out_fit_plus_lg_c_mom_gz[i]      = rk_fit_lg_c_mom_gz->at(i0);
      out_fit_plus_lg_b_mom_lx[i]      = rk_fit_lg_b_mom_x->at(i0);
      out_fit_plus_lg_b_mom_ly[i]      = rk_fit_lg_b_mom_y->at(i0);
      out_fit_plus_lg_b_mom_lz[i]      = rk_fit_lg_b_mom_z->at(i0);
      out_fit_plus_lg_b_mom_gx[i]      = rk_fit_lg_b_mom_gx->at(i0);
      out_fit_plus_lg_b_mom_gy[i]      = rk_fit_lg_b_mom_gy->at(i0);
      out_fit_plus_lg_b_mom_gz[i]      = rk_fit_lg_b_mom_gz->at(i0);
      out_fit_plus_lg_a_mom_lx[i]      = rk_fit_lg_a_mom_x->at(i0);
      out_fit_plus_lg_a_mom_ly[i]      = rk_fit_lg_a_mom_y->at(i0);
      out_fit_plus_lg_a_mom_lz[i]      = rk_fit_lg_a_mom_z->at(i0);
      out_fit_plus_lg_a_mom_gx[i]      = rk_fit_lg_a_mom_gx->at(i0);
      out_fit_plus_lg_a_mom_gy[i]      = rk_fit_lg_a_mom_gy->at(i0);
      out_fit_plus_lg_a_mom_gz[i]      = rk_fit_lg_a_mom_gz->at(i0);
      out_fit_plus_tgt_minus_mom_x[i]  = rk_proj_tgt0_mom_gx->at(i0);
      out_fit_plus_tgt_minus_mom_y[i]  = rk_proj_tgt0_mom_gy->at(i0);
      out_fit_plus_tgt_minus_mom_z[i]  = rk_proj_tgt0_mom_gz->at(i0);
      out_fit_plus_tgt_zero_mom_x[i]   = rk_proj_tgt1_mom_gx->at(i0);
      out_fit_plus_tgt_zero_mom_y[i]   = rk_proj_tgt1_mom_gy->at(i0);
      out_fit_plus_tgt_zero_mom_z[i]   = rk_proj_tgt1_mom_gz->at(i0);
      out_fit_plus_tgt_plus_mom_x[i]   = rk_proj_tgt2_mom_gx->at(i0);
      out_fit_plus_tgt_plus_mom_y[i]   = rk_proj_tgt2_mom_gy->at(i0);
      out_fit_plus_tgt_plus_mom_z[i]   = rk_proj_tgt2_mom_gz->at(i0);
      out_fit_minus_ssd_mom_lx[i]      = rk_fit_ssd_mom_x->at(i1);
      out_fit_minus_ssd_mom_ly[i]      = rk_fit_ssd_mom_y->at(i1);
      out_fit_minus_ssd_mom_lz[i]      = rk_fit_ssd_mom_z->at(i1);
      out_fit_minus_ssd_mom_gx[i]      = rk_fit_ssd_mom_gx->at(i1);
      out_fit_minus_ssd_mom_gy[i]      = rk_fit_ssd_mom_gy->at(i1);
      out_fit_minus_ssd_mom_gz[i]      = rk_fit_ssd_mom_gz->at(i1);
      out_fit_minus_gtr100_mom_lx[i]   = rk_fit_gtr100_mom_x->at(i1);
      out_fit_minus_gtr100_mom_ly[i]   = rk_fit_gtr100_mom_y->at(i1);
      out_fit_minus_gtr100_mom_lz[i]   = rk_fit_gtr100_mom_z->at(i1);
      out_fit_minus_gtr100_mom_gx[i]   = rk_fit_gtr100_mom_gx->at(i1);
      out_fit_minus_gtr100_mom_gy[i]   = rk_fit_gtr100_mom_gy->at(i1);
      out_fit_minus_gtr100_mom_gz[i]   = rk_fit_gtr100_mom_gz->at(i1);
      out_fit_minus_gtr200_mom_lx[i]   = rk_fit_gtr200_mom_x->at(i1);
      out_fit_minus_gtr200_mom_ly[i]   = rk_fit_gtr200_mom_y->at(i1);
      out_fit_minus_gtr200_mom_lz[i]   = rk_fit_gtr200_mom_z->at(i1);
      out_fit_minus_gtr200_mom_gx[i]   = rk_fit_gtr200_mom_gx->at(i1);
      out_fit_minus_gtr200_mom_gy[i]   = rk_fit_gtr200_mom_gy->at(i1);
      out_fit_minus_gtr200_mom_gz[i]   = rk_fit_gtr200_mom_gz->at(i1);
      out_fit_minus_gtr300_mom_lx[i]   = rk_fit_gtr300_mom_x->at(i1);
      out_fit_minus_gtr300_mom_ly[i]   = rk_fit_gtr300_mom_y->at(i1);
      out_fit_minus_gtr300_mom_lz[i]   = rk_fit_gtr300_mom_z->at(i1);
      out_fit_minus_gtr300_mom_gx[i]   = rk_fit_gtr300_mom_gx->at(i1);
      out_fit_minus_gtr300_mom_gy[i]   = rk_fit_gtr300_mom_gy->at(i1);
      out_fit_minus_gtr300_mom_gz[i]   = rk_fit_gtr300_mom_gz->at(i1);
      out_fit_minus_hbd_mom_lx[i]      = rk_fit_hbd_mom_x->at(i1);
      out_fit_minus_hbd_mom_ly[i]      = rk_fit_hbd_mom_y->at(i1);
      out_fit_minus_hbd_mom_lz[i]      = rk_fit_hbd_mom_z->at(i1);
      out_fit_minus_hbd_mom_gx[i]      = rk_fit_hbd_mom_gx->at(i1);
      out_fit_minus_hbd_mom_gy[i]      = rk_fit_hbd_mom_gy->at(i1);
      out_fit_minus_hbd_mom_gz[i]      = rk_fit_hbd_mom_gz->at(i1);
      out_fit_minus_lg_c_mom_lx[i]     = rk_fit_lg_c_mom_x->at(i1);
      out_fit_minus_lg_c_mom_ly[i]     = rk_fit_lg_c_mom_y->at(i1);
      out_fit_minus_lg_c_mom_lz[i]     = rk_fit_lg_c_mom_z->at(i1);
      out_fit_minus_lg_c_mom_gx[i]     = rk_fit_lg_c_mom_gx->at(i1);
      out_fit_minus_lg_c_mom_gy[i]     = rk_fit_lg_c_mom_gy->at(i1);
      out_fit_minus_lg_c_mom_gz[i]     = rk_fit_lg_c_mom_gz->at(i1);
      out_fit_minus_lg_b_mom_lx[i]     = rk_fit_lg_b_mom_x->at(i1);
      out_fit_minus_lg_b_mom_ly[i]     = rk_fit_lg_b_mom_y->at(i1);
      out_fit_minus_lg_b_mom_lz[i]     = rk_fit_lg_b_mom_z->at(i1);
      out_fit_minus_lg_b_mom_gx[i]     = rk_fit_lg_b_mom_gx->at(i1);
      out_fit_minus_lg_b_mom_gy[i]     = rk_fit_lg_b_mom_gy->at(i1);
      out_fit_minus_lg_b_mom_gz[i]     = rk_fit_lg_b_mom_gz->at(i1);
      out_fit_minus_lg_a_mom_lx[i]     = rk_fit_lg_a_mom_x->at(i1);
      out_fit_minus_lg_a_mom_ly[i]     = rk_fit_lg_a_mom_y->at(i1);
      out_fit_minus_lg_a_mom_lz[i]     = rk_fit_lg_a_mom_z->at(i1);
      out_fit_minus_lg_a_mom_gx[i]     = rk_fit_lg_a_mom_gx->at(i1);
      out_fit_minus_lg_a_mom_gy[i]     = rk_fit_lg_a_mom_gy->at(i1);
      out_fit_minus_lg_a_mom_gz[i]     = rk_fit_lg_a_mom_gz->at(i1);
      out_fit_minus_tgt_minus_mom_x[i] = rk_proj_tgt0_mom_gx->at(i1);
      out_fit_minus_tgt_minus_mom_y[i] = rk_proj_tgt0_mom_gy->at(i1);
      out_fit_minus_tgt_minus_mom_z[i] = rk_proj_tgt0_mom_gz->at(i1);
      out_fit_minus_tgt_zero_mom_x[i]  = rk_proj_tgt1_mom_gx->at(i1);
      out_fit_minus_tgt_zero_mom_y[i]  = rk_proj_tgt1_mom_gy->at(i1);
      out_fit_minus_tgt_zero_mom_z[i]  = rk_proj_tgt1_mom_gz->at(i1);
      out_fit_minus_tgt_plus_mom_x[i]  = rk_proj_tgt2_mom_gx->at(i1);
      out_fit_minus_tgt_plus_mom_y[i]  = rk_proj_tgt2_mom_gy->at(i1);
      out_fit_minus_tgt_plus_mom_z[i]  = rk_proj_tgt2_mom_gz->at(i1);
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
      AssociatedHBD(i);
//      AssociatedLG(i);
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
    SimpleAnalysis(i);
TmpProjectionX0(i);
#ifdef TMP_SOME_Z
TmpProjectionSomeZ(i);
#endif // TMP_SOME_Z
  }
  AddPairOrders();
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

void track_analyzer_220715::FillEntryInfo(int entry_index, EntryInfo* plus_entry, EntryInfo* minus_entry) {
  plus_entry->entry_index  = entry_index;
  minus_entry->entry_index = entry_index;
  for (const auto& i : good_track_indexs) {
    if (rk_charge->at(i) == 1) {
      plus_entry->track_indexs.emplace_back(i);
    } else {
      minus_entry->track_indexs.emplace_back(i);
    }
  }
  return;
}

void track_analyzer_220715::ClearEMBranches() {
  em_plus_run_id.clear();
  em_plus_event_id.clear();
  em_plus_n_cands.clear();
//  em_plus_n_pairs.clear();
  em_plus_track_id.clear();
//  tree->Branch("hit_plus_ssd_id",                  &out_hit_plus_ssd_id);
//  tree->Branch("hit_plus_ssd_lx",                  &out_hit_plus_ssd_lx);
//  tree->Branch("hit_plus_ssd_t",                   &out_hit_plus_ssd_t);
//  tree->Branch("hit_plus_ssd_adc",                 &out_hit_plus_ssd_adc);
//  tree->Branch("hit_plus_ssd_size",                &out_hit_plus_ssd_size);
//  tree->Branch("hit_plus_gtr100_xid",              &out_hit_plus_gtr100_xid);
//  tree->Branch("hit_plus_gtr100_yid",              &out_hit_plus_gtr100_yid);
//  tree->Branch("hit_plus_gtr100_lx",               &out_hit_plus_gtr100_lx);
//  tree->Branch("hit_plus_gtr100_ly",               &out_hit_plus_gtr100_ly);
//  tree->Branch("hit_plus_gtr100_xt",               &out_hit_plus_gtr100_xt);
//  tree->Branch("hit_plus_gtr100_yt",               &out_hit_plus_gtr100_yt);
//  tree->Branch("hit_plus_gtr100_xadc",             &out_hit_plus_gtr100_xadc);
//  tree->Branch("hit_plus_gtr100_yadc",             &out_hit_plus_gtr100_yadc);
//  tree->Branch("hit_plus_gtr100_xsize",            &out_hit_plus_gtr100_xsize);
//  tree->Branch("hit_plus_gtr100_ysize",            &out_hit_plus_gtr100_ysize);
//  tree->Branch("hit_plus_gtr200_xid",              &out_hit_plus_gtr200_xid);
//  tree->Branch("hit_plus_gtr200_yid",              &out_hit_plus_gtr200_yid);
//  tree->Branch("hit_plus_gtr200_lx",               &out_hit_plus_gtr200_lx);
//  tree->Branch("hit_plus_gtr200_ly",               &out_hit_plus_gtr200_ly);
//  tree->Branch("hit_plus_gtr200_xt",               &out_hit_plus_gtr200_xt);
//  tree->Branch("hit_plus_gtr200_yt",               &out_hit_plus_gtr200_yt);
//  tree->Branch("hit_plus_gtr200_xadc",             &out_hit_plus_gtr200_xadc);
//  tree->Branch("hit_plus_gtr200_yadc",             &out_hit_plus_gtr200_yadc);
//  tree->Branch("hit_plus_gtr200_xsize",            &out_hit_plus_gtr200_xsize);
//  tree->Branch("hit_plus_gtr200_ysize",            &out_hit_plus_gtr200_ysize);
//  tree->Branch("hit_plus_gtr300_xid",              &out_hit_plus_gtr300_xid);
//  tree->Branch("hit_plus_gtr300_yid",              &out_hit_plus_gtr300_yid);
//  tree->Branch("hit_plus_gtr300_lx",               &out_hit_plus_gtr300_lx);
//  tree->Branch("hit_plus_gtr300_ly",               &out_hit_plus_gtr300_ly);
//  tree->Branch("hit_plus_gtr300_xt",               &out_hit_plus_gtr300_xt);
//  tree->Branch("hit_plus_gtr300_yt",               &out_hit_plus_gtr300_yt);
//  tree->Branch("hit_plus_gtr300_xadc",             &out_hit_plus_gtr300_xadc);
//  tree->Branch("hit_plus_gtr300_yadc",             &out_hit_plus_gtr300_yadc);
//  tree->Branch("hit_plus_gtr300_xsize",            &out_hit_plus_gtr300_xsize);
//  tree->Branch("hit_plus_gtr300_ysize",            &out_hit_plus_gtr300_ysize);
  em_minus_run_id.clear();
  em_minus_event_id.clear();
  em_minus_n_cands.clear();
//  em_minus_n_pairs.clear();
  em_minus_track_id.clear();
//  tree->Branch("hit_minus_ssd_id",                 &out_hit_minus_ssd_id);
//  tree->Branch("hit_minus_ssd_lx",                 &out_hit_minus_ssd_lx);
//  tree->Branch("hit_minus_ssd_t",                  &out_hit_minus_ssd_t);
//  tree->Branch("hit_minus_ssd_adc",                &out_hit_minus_ssd_adc);
//  tree->Branch("hit_minus_ssd_size",               &out_hit_minus_ssd_size);
//  tree->Branch("hit_minus_gtr100_xid",             &out_hit_minus_gtr100_xid);
//  tree->Branch("hit_minus_gtr100_yid",             &out_hit_minus_gtr100_yid);
//  tree->Branch("hit_minus_gtr100_lx",              &out_hit_minus_gtr100_lx);
//  tree->Branch("hit_minus_gtr100_ly",              &out_hit_minus_gtr100_ly);
//  tree->Branch("hit_minus_gtr100_xt",              &out_hit_minus_gtr100_xt);
//  tree->Branch("hit_minus_gtr100_yt",              &out_hit_minus_gtr100_yt);
//  tree->Branch("hit_minus_gtr100_xadc",            &out_hit_minus_gtr100_xadc);
//  tree->Branch("hit_minus_gtr100_yadc",            &out_hit_minus_gtr100_yadc);
//  tree->Branch("hit_minus_gtr100_xsize",           &out_hit_minus_gtr100_xsize);
//  tree->Branch("hit_minus_gtr100_ysize",           &out_hit_minus_gtr100_ysize);
//  tree->Branch("hit_minus_gtr200_xid",             &out_hit_minus_gtr200_xid);
//  tree->Branch("hit_minus_gtr200_yid",             &out_hit_minus_gtr200_yid);
//  tree->Branch("hit_minus_gtr200_lx",              &out_hit_minus_gtr200_lx);
//  tree->Branch("hit_minus_gtr200_ly",              &out_hit_minus_gtr200_ly);
//  tree->Branch("hit_minus_gtr200_xt",              &out_hit_minus_gtr200_xt);
//  tree->Branch("hit_minus_gtr200_yt",              &out_hit_minus_gtr200_yt);
//  tree->Branch("hit_minus_gtr200_xadc",            &out_hit_minus_gtr200_xadc);
//  tree->Branch("hit_minus_gtr200_yadc",            &out_hit_minus_gtr200_yadc);
//  tree->Branch("hit_minus_gtr200_xsize",           &out_hit_minus_gtr200_xsize);
//  tree->Branch("hit_minus_gtr200_ysize",           &out_hit_minus_gtr200_ysize);
//  tree->Branch("hit_minus_gtr300_xid",             &out_hit_minus_gtr300_xid);
//  tree->Branch("hit_minus_gtr300_yid",             &out_hit_minus_gtr300_yid);
//  tree->Branch("hit_minus_gtr300_lx",              &out_hit_minus_gtr300_lx);
//  tree->Branch("hit_minus_gtr300_ly",              &out_hit_minus_gtr300_ly);
//  tree->Branch("hit_minus_gtr300_xt",              &out_hit_minus_gtr300_xt);
//  tree->Branch("hit_minus_gtr300_yt",              &out_hit_minus_gtr300_yt);
//  tree->Branch("hit_minus_gtr300_xadc",            &out_hit_minus_gtr300_xadc);
//  tree->Branch("hit_minus_gtr300_yadc",            &out_hit_minus_gtr300_yadc);
//  tree->Branch("hit_minus_gtr300_xsize",           &out_hit_minus_gtr300_xsize);
//  tree->Branch("hit_minus_gtr300_ysize",           &out_hit_minus_gtr300_ysize);
  em_n_pairs.clear();
  em_chi2.clear();
  em_plus_chi2.clear();
  em_minus_chi2.clear();
  em_flag.clear();
  em_distance.clear();
  em_dir_id.clear();
  em_vtx_x.clear();
  em_vtx_y.clear();
  em_vtx_z.clear();
  em_plus_mom.clear();
  em_plus_mom_x.clear();
  em_plus_mom_y.clear();
  em_plus_mom_z.clear();
  em_plus_mom_theta.clear();
  em_plus_mom_phi.clear();
  em_minus_mom.clear();
  em_minus_mom_x.clear();
  em_minus_mom_y.clear();
  em_minus_mom_z.clear();
  em_minus_mom_theta.clear();
  em_minus_mom_phi.clear();
  em_mom_angle.clear();
  em_ee_mass.clear();
  em_pipi_mass.clear();
  em_pip_mass.clear();
  em_kk_mass.clear();
  em_simple_best_tgt_id.clear();
  em_simple_best_tgt_r.clear();
  em_ee_mass_at_best_tgt.clear();
  em_pipi_mass_at_best_tgt.clear();
  em_pip_mass_at_best_tgt.clear();
  em_kk_mass_at_best_tgt.clear();
  em_plus_ssd_mid.clear();
  em_plus_gtr100_mid.clear();
  em_plus_gtr200_mid.clear();
  em_plus_gtr300_mid.clear();
  em_plus_hbd_mid.clear();
  em_plus_lg_c_mid.clear();
  em_plus_lg_b_mid.clear();
  em_plus_lg_a_mid.clear();
  em_minus_ssd_mid.clear();
  em_minus_gtr100_mid.clear();
  em_minus_gtr200_mid.clear();
  em_minus_gtr300_mid.clear();
  em_minus_hbd_mid.clear();
  em_minus_lg_c_mid.clear();
  em_minus_lg_b_mid.clear();
  em_minus_lg_a_mid.clear();
  em_fit_plus_ssd_lx.clear();
  em_fit_plus_ssd_ly.clear();
  em_fit_plus_gtr100_lx.clear();
  em_fit_plus_gtr100_ly.clear();
  em_fit_plus_gtr200_lx.clear();
  em_fit_plus_gtr200_ly.clear();
  em_fit_plus_gtr300_lx.clear();
  em_fit_plus_gtr300_ly.clear();
  em_fit_plus_hbd_lx.clear();
  em_fit_plus_hbd_ly.clear();
  em_fit_plus_lg_c_lx.clear();
  em_fit_plus_lg_c_ly.clear();
  em_fit_plus_lg_b_lx.clear();
  em_fit_plus_lg_b_ly.clear();
  em_fit_plus_lg_a_lx.clear();
  em_fit_plus_lg_a_ly.clear();
  em_fit_minus_ssd_lx.clear();
  em_fit_minus_ssd_ly.clear();
  em_fit_minus_gtr100_lx.clear();
  em_fit_minus_gtr100_ly.clear();
  em_fit_minus_gtr200_lx.clear();
  em_fit_minus_gtr200_ly.clear();
  em_fit_minus_gtr300_lx.clear();
  em_fit_minus_gtr300_ly.clear();
  em_fit_minus_hbd_lx.clear();
  em_fit_minus_hbd_ly.clear();
  em_fit_minus_lg_c_lx.clear();
  em_fit_minus_lg_c_ly.clear();
  em_fit_minus_lg_b_lx.clear();
  em_fit_minus_lg_b_ly.clear();
  em_fit_minus_lg_a_lx.clear();
  em_fit_minus_lg_a_ly.clear();
//  tree->Branch("res_plus_ssd_lx",                  &out_res_plus_ssd_lx);
////  tree->Branch("res_plus_ssd_ly",                  &out_res_plus_ssd_ly);
//  tree->Branch("res_plus_gtr100_lx",               &out_res_plus_gtr100_lx);
//  tree->Branch("res_plus_gtr100_ly",               &out_res_plus_gtr100_ly);
//  tree->Branch("res_plus_gtr200_lx",               &out_res_plus_gtr200_lx);
//  tree->Branch("res_plus_gtr200_ly",               &out_res_plus_gtr200_ly);
//  tree->Branch("res_plus_gtr300_lx",               &out_res_plus_gtr300_lx);
//  tree->Branch("res_plus_gtr300_ly",               &out_res_plus_gtr300_ly);
//  tree->Branch("res_minus_ssd_lx",                 &out_res_minus_ssd_lx);
////  tree->Branch("res_minus_ssd_ly",                 &out_res_minus_ssd_ly);
//  tree->Branch("res_minus_gtr100_lx",              &out_res_minus_gtr100_lx);
//  tree->Branch("res_minus_gtr100_ly",              &out_res_minus_gtr100_ly);
//  tree->Branch("res_minus_gtr200_lx",              &out_res_minus_gtr200_lx);
//  tree->Branch("res_minus_gtr200_ly",              &out_res_minus_gtr200_ly);
//  tree->Branch("res_minus_gtr300_lx",              &out_res_minus_gtr300_lx);
//  tree->Branch("res_minus_gtr300_ly",              &out_res_minus_gtr300_ly);
  em_fit_plus_tgt_minus_x.clear();
  em_fit_plus_tgt_minus_y.clear();
  em_fit_plus_tgt_zero_x.clear();
  em_fit_plus_tgt_zero_y.clear();
  em_fit_plus_tgt_plus_x.clear();
  em_fit_plus_tgt_plus_y.clear();
  em_fit_plus_x0_y.clear();
  em_fit_plus_x0_z.clear();
  em_fit_minus_tgt_minus_x.clear();
  em_fit_minus_tgt_minus_y.clear();
  em_fit_minus_tgt_zero_x.clear();
  em_fit_minus_tgt_zero_y.clear();
  em_fit_minus_tgt_plus_x.clear();
  em_fit_minus_tgt_plus_y.clear();
  em_fit_minus_x0_y.clear();
  em_fit_minus_x0_z.clear();
  em_fit_plus_ssd_mom_lx.clear();
  em_fit_plus_ssd_mom_ly.clear();
  em_fit_plus_ssd_mom_lz.clear();
  em_fit_plus_ssd_mom_gx.clear();
  em_fit_plus_ssd_mom_gy.clear();
  em_fit_plus_ssd_mom_gz.clear();
  em_fit_plus_gtr100_mom_lx.clear();
  em_fit_plus_gtr100_mom_ly.clear();
  em_fit_plus_gtr100_mom_lz.clear();
  em_fit_plus_gtr100_mom_gx.clear();
  em_fit_plus_gtr100_mom_gy.clear();
  em_fit_plus_gtr100_mom_gz.clear();
  em_fit_plus_gtr200_mom_lx.clear();
  em_fit_plus_gtr200_mom_ly.clear();
  em_fit_plus_gtr200_mom_lz.clear();
  em_fit_plus_gtr200_mom_gx.clear();
  em_fit_plus_gtr200_mom_gy.clear();
  em_fit_plus_gtr200_mom_gz.clear();
  em_fit_plus_gtr300_mom_lx.clear();
  em_fit_plus_gtr300_mom_ly.clear();
  em_fit_plus_gtr300_mom_lz.clear();
  em_fit_plus_gtr300_mom_gx.clear();
  em_fit_plus_gtr300_mom_gy.clear();
  em_fit_plus_gtr300_mom_gz.clear();
  em_fit_plus_hbd_mom_lx.clear();
  em_fit_plus_hbd_mom_ly.clear();
  em_fit_plus_hbd_mom_lz.clear();
  em_fit_plus_hbd_mom_gx.clear();
  em_fit_plus_hbd_mom_gy.clear();
  em_fit_plus_hbd_mom_gz.clear();
  em_fit_plus_lg_c_mom_lx.clear();
  em_fit_plus_lg_c_mom_ly.clear();
  em_fit_plus_lg_c_mom_lz.clear();
  em_fit_plus_lg_c_mom_gx.clear();
  em_fit_plus_lg_c_mom_gy.clear();
  em_fit_plus_lg_c_mom_gz.clear();
  em_fit_plus_lg_b_mom_lx.clear();
  em_fit_plus_lg_b_mom_ly.clear();
  em_fit_plus_lg_b_mom_lz.clear();
  em_fit_plus_lg_b_mom_gx.clear();
  em_fit_plus_lg_b_mom_gy.clear();
  em_fit_plus_lg_b_mom_gz.clear();
  em_fit_plus_lg_a_mom_lx.clear();
  em_fit_plus_lg_a_mom_ly.clear();
  em_fit_plus_lg_a_mom_lz.clear();
  em_fit_plus_lg_a_mom_gx.clear();
  em_fit_plus_lg_a_mom_gy.clear();
  em_fit_plus_lg_a_mom_gz.clear();
  em_fit_plus_tgt_minus_mom_x.clear();
  em_fit_plus_tgt_minus_mom_y.clear();
  em_fit_plus_tgt_minus_mom_z.clear();
  em_fit_plus_tgt_zero_mom_x.clear();
  em_fit_plus_tgt_zero_mom_y.clear();
  em_fit_plus_tgt_zero_mom_z.clear();
  em_fit_plus_tgt_plus_mom_x.clear();
  em_fit_plus_tgt_plus_mom_y.clear();
  em_fit_plus_tgt_plus_mom_z.clear();
  em_fit_minus_ssd_mom_lx.clear();
  em_fit_minus_ssd_mom_ly.clear();
  em_fit_minus_ssd_mom_lz.clear();
  em_fit_minus_ssd_mom_gx.clear();
  em_fit_minus_ssd_mom_gy.clear();
  em_fit_minus_ssd_mom_gz.clear();
  em_fit_minus_gtr100_mom_lx.clear();
  em_fit_minus_gtr100_mom_ly.clear();
  em_fit_minus_gtr100_mom_lz.clear();
  em_fit_minus_gtr100_mom_gx.clear();
  em_fit_minus_gtr100_mom_gy.clear();
  em_fit_minus_gtr100_mom_gz.clear();
  em_fit_minus_gtr200_mom_lx.clear();
  em_fit_minus_gtr200_mom_ly.clear();
  em_fit_minus_gtr200_mom_lz.clear();
  em_fit_minus_gtr200_mom_gx.clear();
  em_fit_minus_gtr200_mom_gy.clear();
  em_fit_minus_gtr200_mom_gz.clear();
  em_fit_minus_gtr300_mom_lx.clear();
  em_fit_minus_gtr300_mom_ly.clear();
  em_fit_minus_gtr300_mom_lz.clear();
  em_fit_minus_gtr300_mom_gx.clear();
  em_fit_minus_gtr300_mom_gy.clear();
  em_fit_minus_gtr300_mom_gz.clear();
  em_fit_minus_hbd_mom_lx.clear();
  em_fit_minus_hbd_mom_ly.clear();
  em_fit_minus_hbd_mom_lz.clear();
  em_fit_minus_hbd_mom_gx.clear();
  em_fit_minus_hbd_mom_gy.clear();
  em_fit_minus_hbd_mom_gz.clear();
  em_fit_minus_lg_c_mom_lx.clear();
  em_fit_minus_lg_c_mom_ly.clear();
  em_fit_minus_lg_c_mom_lz.clear();
  em_fit_minus_lg_c_mom_gx.clear();
  em_fit_minus_lg_c_mom_gy.clear();
  em_fit_minus_lg_c_mom_gz.clear();
  em_fit_minus_lg_b_mom_lx.clear();
  em_fit_minus_lg_b_mom_ly.clear();
  em_fit_minus_lg_b_mom_lz.clear();
  em_fit_minus_lg_b_mom_gx.clear();
  em_fit_minus_lg_b_mom_gy.clear();
  em_fit_minus_lg_b_mom_gz.clear();
  em_fit_minus_lg_a_mom_lx.clear();
  em_fit_minus_lg_a_mom_ly.clear();
  em_fit_minus_lg_a_mom_lz.clear();
  em_fit_minus_lg_a_mom_gx.clear();
  em_fit_minus_lg_a_mom_gy.clear();
  em_fit_minus_lg_a_mom_gz.clear();
  em_fit_minus_tgt_minus_mom_x.clear();
  em_fit_minus_tgt_minus_mom_y.clear();
  em_fit_minus_tgt_minus_mom_z.clear();
  em_fit_minus_tgt_zero_mom_x.clear();
  em_fit_minus_tgt_zero_mom_y.clear();
  em_fit_minus_tgt_zero_mom_z.clear();
  em_fit_minus_tgt_plus_mom_x.clear();
  em_fit_minus_tgt_plus_mom_y.clear();
  em_fit_minus_tgt_plus_mom_z.clear();
  em_fit_parent_mom.clear();
  em_fit_parent_mom_x.clear();
  em_fit_parent_mom_y.clear();
  em_fit_parent_mom_z.clear();
  em_fit_parent_mom_theta.clear();
  em_fit_parent_mom_phi.clear();
  em_fit_parent_tgt_minus_x.clear();
  em_fit_parent_tgt_minus_y.clear();
  em_fit_parent_tgt_minus_flight_path.clear();
  em_fit_parent_tgt_zero_x.clear();
  em_fit_parent_tgt_zero_y.clear();
  em_fit_parent_tgt_zero_flight_path.clear();
  em_fit_parent_tgt_plus_x.clear();
  em_fit_parent_tgt_plus_y.clear();
  em_fit_parent_tgt_plus_flight_path.clear();
  em_fit_parent_best_tgt_id.clear();
  em_fit_parent_best_tgt_r.clear();
  em_fit_parent_good_tgt_id_set.clear();
  em_fit_parent_good_tgt_ids.clear();
  em_fit_parent_x0_y.clear();
  em_fit_parent_x0_z.clear();
//  tree->Branch("proj_plus_n_hbds",                 &out_proj_plus_n_hbds);
//  tree->Branch("proj_plus_hbd_id",                 &out_proj_plus_hbd_id);
//  tree->Branch("proj_plus_hbd_lx",                 &out_proj_plus_hbd_lx);
//  tree->Branch("proj_plus_hbd_ly",                 &out_proj_plus_hbd_ly);
//  tree->Branch("proj_plus_hbd_resx",               &out_proj_plus_hbd_resx);
//  tree->Branch("proj_plus_hbd_resy",               &out_proj_plus_hbd_resy);
//  tree->Branch("proj_plus_hbd_adc",                &out_proj_plus_hbd_adc);
//  tree->Branch("proj_plus_hbd_size",               &out_proj_plus_hbd_size);
//  tree->Branch("proj_plus_hbd_eprob",              &out_proj_plus_hbd_eprob);
//  tree->Branch("proj_minus_n_hbds",                &out_proj_minus_n_hbds);
//  tree->Branch("proj_minus_hbd_id",                &out_proj_minus_hbd_id);
//  tree->Branch("proj_minus_hbd_lx",                &out_proj_minus_hbd_lx);
//  tree->Branch("proj_minus_hbd_ly",                &out_proj_minus_hbd_ly);
//  tree->Branch("proj_minus_hbd_resx",              &out_proj_minus_hbd_resx);
//  tree->Branch("proj_minus_hbd_resy",              &out_proj_minus_hbd_resy);
//  tree->Branch("proj_minus_hbd_adc",               &out_proj_minus_hbd_adc);
//  tree->Branch("proj_minus_hbd_size",              &out_proj_minus_hbd_size);
//  tree->Branch("proj_minus_hbd_eprob",             &out_proj_minus_hbd_eprob);
  return;
}

void track_analyzer_220715::PairFitEM(int plus_entry_index, int plus_track_index, int minus_entry_index, int minus_track_index) {
  cerr << "### NOT IMPLEMENTED ###" << endl;
  return;
}

void track_analyzer_220715::NearestPointEM(int plus_entry_index, int plus_track_index, int minus_entry_index, int minus_track_index) {
  array<Hep3Vector,        2> init_poss;
  array<Hep3Vector,        2> init_moms;
  array<E16ANA_StepTrack*, 2> tracks;
  
  fChain->GetEntry(plus_entry_index);
  em_plus_run_id.emplace_back(run_id);
  em_plus_event_id.emplace_back(event_id);
  em_plus_n_cands.emplace_back(n_cands);
  em_plus_track_id.emplace_back(track_id->at(plus_track_index));
  em_plus_chi2.emplace_back(chi_square->at(plus_track_index));
  em_plus_ssd_mid.emplace_back(rk_fit_ssd_mid->at(plus_track_index));
  em_plus_gtr100_mid.emplace_back(rk_fit_gtr100_mid->at(plus_track_index));
  em_plus_gtr200_mid.emplace_back(rk_fit_gtr200_mid->at(plus_track_index));
  em_plus_gtr300_mid.emplace_back(rk_fit_gtr300_mid->at(plus_track_index));
  em_plus_hbd_mid.emplace_back(rk_fit_hbd_mid->at(plus_track_index));
  em_plus_lg_c_mid.emplace_back(rk_fit_lg_c_mid->at(plus_track_index));
  em_plus_lg_b_mid.emplace_back(rk_fit_lg_b_mid->at(plus_track_index));
  em_plus_lg_a_mid.emplace_back(rk_fit_lg_a_mid->at(plus_track_index));
  em_fit_plus_ssd_lx.emplace_back(rk_fit_ssd_x->at(plus_track_index));
  em_fit_plus_ssd_ly.emplace_back(rk_fit_ssd_y->at(plus_track_index));
  em_fit_plus_gtr100_lx.emplace_back(rk_fit_gtr100_x->at(plus_track_index));
  em_fit_plus_gtr100_ly.emplace_back(rk_fit_gtr100_y->at(plus_track_index));
  em_fit_plus_gtr200_lx.emplace_back(rk_fit_gtr200_x->at(plus_track_index));
  em_fit_plus_gtr200_ly.emplace_back(rk_fit_gtr200_y->at(plus_track_index));
  em_fit_plus_gtr300_lx.emplace_back(rk_fit_gtr300_x->at(plus_track_index));
  em_fit_plus_gtr300_ly.emplace_back(rk_fit_gtr300_y->at(plus_track_index));
  em_fit_plus_hbd_lx.emplace_back(rk_fit_hbd_x->at(plus_track_index));
  em_fit_plus_hbd_ly.emplace_back(rk_fit_hbd_y->at(plus_track_index));
  em_fit_plus_lg_c_lx.emplace_back(rk_fit_lg_c_x->at(plus_track_index));
  em_fit_plus_lg_c_ly.emplace_back(rk_fit_lg_c_y->at(plus_track_index));
  em_fit_plus_lg_b_lx.emplace_back(rk_fit_lg_b_x->at(plus_track_index));
  em_fit_plus_lg_b_ly.emplace_back(rk_fit_lg_b_y->at(plus_track_index));
  em_fit_plus_lg_a_lx.emplace_back(rk_fit_lg_a_x->at(plus_track_index));
  em_fit_plus_lg_a_ly.emplace_back(rk_fit_lg_a_y->at(plus_track_index));
  em_fit_plus_tgt_minus_x.emplace_back(rk_proj_tgt0_gx->at(plus_track_index));
  em_fit_plus_tgt_minus_y.emplace_back(rk_proj_tgt0_gy->at(plus_track_index));
  em_fit_plus_tgt_zero_x.emplace_back(rk_proj_tgt1_gx->at(plus_track_index));
  em_fit_plus_tgt_zero_y.emplace_back(rk_proj_tgt1_gy->at(plus_track_index));
  em_fit_plus_tgt_plus_x.emplace_back(rk_proj_tgt2_gx->at(plus_track_index));
  em_fit_plus_tgt_plus_y.emplace_back(rk_proj_tgt2_gy->at(plus_track_index));
  em_fit_plus_x0_y.emplace_back(rk_proj_x0_gy->at(plus_track_index));
  em_fit_plus_x0_z.emplace_back(rk_proj_x0_gz->at(plus_track_index));
  // momentum in detectors mus be implemented
  em_fit_plus_tgt_minus_mom_x.emplace_back(rk_proj_tgt0_mom_gx->at(plus_track_index));
  em_fit_plus_tgt_minus_mom_y.emplace_back(rk_proj_tgt0_mom_gy->at(plus_track_index));
  em_fit_plus_tgt_minus_mom_z.emplace_back(rk_proj_tgt0_mom_gz->at(plus_track_index));
  em_fit_plus_tgt_zero_mom_x.emplace_back(rk_proj_tgt1_mom_gx->at(plus_track_index));
  em_fit_plus_tgt_zero_mom_y.emplace_back(rk_proj_tgt1_mom_gy->at(plus_track_index));
  em_fit_plus_tgt_zero_mom_z.emplace_back(rk_proj_tgt1_mom_gz->at(plus_track_index));
  em_fit_plus_tgt_plus_mom_x.emplace_back(rk_proj_tgt2_mom_gx->at(plus_track_index));
  em_fit_plus_tgt_plus_mom_y.emplace_back(rk_proj_tgt2_mom_gy->at(plus_track_index));
  em_fit_plus_tgt_plus_mom_z.emplace_back(rk_proj_tgt2_mom_gz->at(plus_track_index));
  init_poss[0] = Hep3Vector(rk_fit_init_pos_gx->at(plus_track_index) * 0.1, rk_fit_init_pos_gy->at(plus_track_index) * 0.1,
                            rk_fit_init_pos_gz->at(plus_track_index) * 0.1);
  init_moms[0] = Hep3Vector(rk_fit_init_mom_gx->at(plus_track_index), rk_fit_init_mom_gy->at(plus_track_index), rk_fit_init_mom_gz->at(plus_track_index));
  tracks[0] = new E16ANA_StepTrack(bfield_map, init_poss[0], init_moms[0], 1., kStepTrackSizeCm, kStepTrackArraySize);
  
  fChain->GetEntry(minus_entry_index);
  em_minus_run_id.emplace_back(run_id);
  em_minus_event_id.emplace_back(event_id);
  em_minus_n_cands.emplace_back(n_cands);
  em_minus_track_id.emplace_back(track_id->at(minus_track_index));
  em_minus_chi2.emplace_back(chi_square->at(minus_track_index));
  em_minus_ssd_mid.emplace_back(rk_fit_ssd_mid->at(minus_track_index));
  em_minus_gtr100_mid.emplace_back(rk_fit_gtr100_mid->at(minus_track_index));
  em_minus_gtr200_mid.emplace_back(rk_fit_gtr200_mid->at(minus_track_index));
  em_minus_gtr300_mid.emplace_back(rk_fit_gtr300_mid->at(minus_track_index));
  em_minus_hbd_mid.emplace_back(rk_fit_hbd_mid->at(minus_track_index));
  em_minus_lg_c_mid.emplace_back(rk_fit_lg_c_mid->at(minus_track_index));
  em_minus_lg_b_mid.emplace_back(rk_fit_lg_b_mid->at(minus_track_index));
  em_minus_lg_a_mid.emplace_back(rk_fit_lg_a_mid->at(minus_track_index));
  em_fit_minus_ssd_lx.emplace_back(rk_fit_ssd_x->at(minus_track_index));
  em_fit_minus_ssd_ly.emplace_back(rk_fit_ssd_y->at(minus_track_index));
  em_fit_minus_gtr100_lx.emplace_back(rk_fit_gtr100_x->at(minus_track_index));
  em_fit_minus_gtr100_ly.emplace_back(rk_fit_gtr100_y->at(minus_track_index));
  em_fit_minus_gtr200_lx.emplace_back(rk_fit_gtr200_x->at(minus_track_index));
  em_fit_minus_gtr200_ly.emplace_back(rk_fit_gtr200_y->at(minus_track_index));
  em_fit_minus_gtr300_lx.emplace_back(rk_fit_gtr300_x->at(minus_track_index));
  em_fit_minus_gtr300_ly.emplace_back(rk_fit_gtr300_y->at(minus_track_index));
  em_fit_minus_hbd_lx.emplace_back(rk_fit_hbd_x->at(minus_track_index));
  em_fit_minus_hbd_ly.emplace_back(rk_fit_hbd_y->at(minus_track_index));
  em_fit_minus_lg_c_lx.emplace_back(rk_fit_lg_c_x->at(minus_track_index));
  em_fit_minus_lg_c_ly.emplace_back(rk_fit_lg_c_y->at(minus_track_index));
  em_fit_minus_lg_b_lx.emplace_back(rk_fit_lg_b_x->at(minus_track_index));
  em_fit_minus_lg_b_ly.emplace_back(rk_fit_lg_b_y->at(minus_track_index));
  em_fit_minus_lg_a_lx.emplace_back(rk_fit_lg_a_x->at(minus_track_index));
  em_fit_minus_lg_a_ly.emplace_back(rk_fit_lg_a_y->at(minus_track_index));
  em_fit_minus_tgt_minus_x.emplace_back(rk_proj_tgt0_gx->at(minus_track_index));
  em_fit_minus_tgt_minus_y.emplace_back(rk_proj_tgt0_gy->at(minus_track_index));
  em_fit_minus_tgt_zero_x.emplace_back(rk_proj_tgt1_gx->at(minus_track_index));
  em_fit_minus_tgt_zero_y.emplace_back(rk_proj_tgt1_gy->at(minus_track_index));
  em_fit_minus_tgt_plus_x.emplace_back(rk_proj_tgt2_gx->at(minus_track_index));
  em_fit_minus_tgt_plus_y.emplace_back(rk_proj_tgt2_gy->at(minus_track_index));
  em_fit_minus_x0_y.emplace_back(rk_proj_x0_gy->at(minus_track_index));
  em_fit_minus_x0_z.emplace_back(rk_proj_x0_gz->at(minus_track_index));
  em_fit_minus_tgt_minus_mom_x.emplace_back(rk_proj_tgt0_mom_gx->at(minus_track_index));
  em_fit_minus_tgt_minus_mom_y.emplace_back(rk_proj_tgt0_mom_gy->at(minus_track_index));
  em_fit_minus_tgt_minus_mom_z.emplace_back(rk_proj_tgt0_mom_gz->at(minus_track_index));
  em_fit_minus_tgt_zero_mom_x.emplace_back(rk_proj_tgt1_mom_gx->at(minus_track_index));
  em_fit_minus_tgt_zero_mom_y.emplace_back(rk_proj_tgt1_mom_gy->at(minus_track_index));
  em_fit_minus_tgt_zero_mom_z.emplace_back(rk_proj_tgt1_mom_gz->at(minus_track_index));
  em_fit_minus_tgt_plus_mom_x.emplace_back(rk_proj_tgt2_mom_gx->at(minus_track_index));
  em_fit_minus_tgt_plus_mom_y.emplace_back(rk_proj_tgt2_mom_gy->at(minus_track_index));
  em_fit_minus_tgt_plus_mom_z.emplace_back(rk_proj_tgt2_mom_gz->at(minus_track_index));
  init_poss[1] = Hep3Vector(rk_fit_init_pos_gx->at(minus_track_index) * 0.1, rk_fit_init_pos_gy->at(minus_track_index) * 0.1,
                            rk_fit_init_pos_gz->at(minus_track_index) * 0.1);
  init_moms[1] = Hep3Vector(rk_fit_init_mom_gx->at(minus_track_index), rk_fit_init_mom_gy->at(minus_track_index), rk_fit_init_mom_gz->at(minus_track_index));
  tracks[1] = new E16ANA_StepTrack(bfield_map, init_poss[1], init_moms[1], -1., kStepTrackSizeCm, kStepTrackArraySize);
  
  auto dist_cm       = double();
  auto hep_vtx       = Hep3Vector();
  auto hep_plus_mom  = Hep3Vector();
  auto hep_minus_mom = Hep3Vector();
  auto flag = tracks[0]->Cross(*tracks[1], &dist_cm, &hep_vtx, &hep_plus_mom, &hep_minus_mom);

  em_flag.emplace_back(flag);
  em_distance.emplace_back(dist_cm * 10.);
  em_vtx_x.emplace_back(hep_vtx.x() * 10.);
  em_vtx_y.emplace_back(hep_vtx.y() * 10.);
  em_vtx_z.emplace_back(hep_vtx.z() * 10.);
  auto pmom = TVector3(hep_plus_mom.x(),  hep_plus_mom.y(),  hep_plus_mom.z());
  auto mmom = TVector3(hep_minus_mom.x(), hep_minus_mom.y(), hep_minus_mom.z());
  em_plus_mom.emplace_back(pmom.Mag());
  em_plus_mom_x.emplace_back(pmom.X());
  em_plus_mom_y.emplace_back(pmom.Y());
  em_plus_mom_z.emplace_back(pmom.Z());
  em_plus_mom_theta.emplace_back(pmom.Theta());
  em_plus_mom_phi.emplace_back(pmom.Phi());
  em_minus_mom.emplace_back(mmom.Mag());
  em_minus_mom_x.emplace_back(mmom.X());
  em_minus_mom_y.emplace_back(mmom.Y());
  em_minus_mom_z.emplace_back(mmom.Z());
  em_minus_mom_theta.emplace_back(mmom.Theta());
  em_minus_mom_phi.emplace_back(mmom.Phi());
  em_mom_angle.emplace_back(pmom.Angle(mmom));
  em_ee_mass.emplace_back(CalcMass(kEE,   pmom, mmom));
  em_pipi_mass.emplace_back(CalcMass(kPiPi, pmom, mmom));
  em_pip_mass.emplace_back(CalcMass(kPiP,  pmom, mmom));
  em_kk_mass.emplace_back(CalcMass(kKK,   pmom, mmom));
  for (auto& track : tracks) {
    delete track;
  }
  return;
}

void track_analyzer_220715::DirIDsEM() {
  auto n = em_plus_run_id.size();
  em_dir_id.resize(n);
  for (int i = 0; i < n; ++i) {
    em_dir_id[i] = DirID(em_plus_gtr300_mid[i], em_minus_gtr300_mid[i]);
  }
  return;
}

void track_analyzer_220715::ParentInfoEM() {
  auto n = em_plus_run_id.size();
  em_fit_parent_mom.resize(n);
  em_fit_parent_mom_x.resize(n);
  em_fit_parent_mom_y.resize(n);
  em_fit_parent_mom_z.resize(n);
  em_fit_parent_mom_theta.resize(n);
  em_fit_parent_mom_phi.resize(n);
  em_fit_parent_tgt_minus_x.resize(n);
  em_fit_parent_tgt_minus_y.resize(n);
  em_fit_parent_tgt_minus_flight_path.resize(n);
  em_fit_parent_tgt_zero_x.resize(n);
  em_fit_parent_tgt_zero_y.resize(n);
  em_fit_parent_tgt_zero_flight_path.resize(n);
  em_fit_parent_tgt_plus_x.resize(n);
  em_fit_parent_tgt_plus_y.resize(n);
  em_fit_parent_tgt_plus_flight_path.resize(n);
  em_fit_parent_best_tgt_id.resize(n);
  em_fit_parent_best_tgt_r.resize(n);
  em_fit_parent_good_tgt_id_set.resize(n);
  em_fit_parent_good_tgt_ids.resize(n);
  em_fit_parent_x0_y.resize(n);
  em_fit_parent_x0_z.resize(n);
  for (int i = 0; i < n; ++i) {
    auto vtx = TVector3(em_vtx_x[i], em_vtx_y[i], em_vtx_z[i]);
    array<TVector3, 2> moms;
    moms[0] = TVector3(em_plus_mom_x[i],  em_plus_mom_y[i],  em_plus_mom_z[i]);
    moms[1] = TVector3(em_minus_mom_x[i], em_minus_mom_y[i], em_minus_mom_z[i]);
    TVector3 parent_mom;
    array<TVector3, kNumTgts> tgt_poss;
    array<double,   kNumTgts> flight_paths;
    TVector3 x0_pos;
    ParentInfo(vtx, moms, &parent_mom, &tgt_poss, &flight_paths, &em_fit_parent_best_tgt_id[i], &em_fit_parent_best_tgt_r[i],
               &em_fit_parent_good_tgt_id_set[i], &em_fit_parent_good_tgt_ids[i], &x0_pos);
    em_fit_parent_mom[i]       = parent_mom.Mag();
    em_fit_parent_mom_x[i]     = parent_mom.X();
    em_fit_parent_mom_y[i]     = parent_mom.Y();
    em_fit_parent_mom_z[i]     = parent_mom.Z();
    em_fit_parent_mom_theta[i] = parent_mom.Theta();
    em_fit_parent_mom_phi[i]   = parent_mom.Phi();
    em_fit_parent_tgt_minus_x[i] = tgt_poss[0].X();
    em_fit_parent_tgt_minus_y[i] = tgt_poss[0].Y();
    em_fit_parent_tgt_zero_x[i]  = tgt_poss[1].X();
    em_fit_parent_tgt_zero_y[i]  = tgt_poss[1].Y();
    em_fit_parent_tgt_plus_x[i]  = tgt_poss[2].X();
    em_fit_parent_tgt_plus_y[i]  = tgt_poss[2].Y();
    em_fit_parent_tgt_minus_flight_path[i] = flight_paths[0];
    em_fit_parent_tgt_zero_flight_path[i]  = flight_paths[1];
    em_fit_parent_tgt_plus_flight_path[i]  = flight_paths[2];
    em_fit_parent_x0_y[i] = x0_pos.Y();
    em_fit_parent_x0_z[i] = x0_pos.Z();
  }
  return;
}

int track_analyzer_220715::SimpleBestTargetIDEM(int n, double* r) {
  int tid = -1;
  *r = 10000.;
  auto plus_pos  = TVector3(em_fit_plus_tgt_minus_x[n],  em_fit_plus_tgt_minus_y[n],  0.);
  auto minus_pos = TVector3(em_fit_minus_tgt_minus_x[n], em_fit_minus_tgt_minus_y[n], 0.);
  auto dist = (plus_pos - minus_pos).Mag();
  if (dist < *r) {
    tid = kTgtMinus;
    *r  = dist;
  }
  plus_pos  = TVector3(em_fit_plus_tgt_zero_x[n],  em_fit_plus_tgt_zero_y[n],  0.);
  minus_pos = TVector3(em_fit_minus_tgt_zero_x[n], em_fit_minus_tgt_zero_y[n], 0.);
  dist = (plus_pos - minus_pos).Mag();
  if (dist < *r) {
    tid = kTgtZero;
    *r  = dist;
  }
  plus_pos  = TVector3(em_fit_plus_tgt_plus_x[n],  em_fit_plus_tgt_plus_y[n],  0.);
  minus_pos = TVector3(em_fit_minus_tgt_plus_x[n], em_fit_minus_tgt_plus_y[n], 0.);
  dist = (plus_pos - minus_pos).Mag();
  if (dist < *r) {
    tid = kTgtPlus;
    *r  = dist;
  }
  return tid;
}

void track_analyzer_220715::SimpleAnalysisEM() {
  auto n = em_plus_run_id.size();
  em_simple_best_tgt_id.resize(n);
  em_simple_best_tgt_r.resize(n);
  em_ee_mass_at_best_tgt.resize(n);
  em_pipi_mass_at_best_tgt.resize(n);
  em_pip_mass_at_best_tgt.resize(n);
  em_kk_mass_at_best_tgt.resize(n);
  for (int i = 0; i < n; ++i) {
    auto best_tid = SimpleBestTargetIDEM(i, &em_simple_best_tgt_r[i]);
    em_simple_best_tgt_id[i] = best_tid;
    TVector3 pmom;
    TVector3 mmom;
    if (best_tid == kTgtMinus) {
      pmom = TVector3(em_fit_plus_tgt_minus_mom_x[i],  em_fit_plus_tgt_minus_mom_y[i],  em_fit_plus_tgt_minus_mom_z[i]);
      mmom = TVector3(em_fit_minus_tgt_minus_mom_x[i], em_fit_minus_tgt_minus_mom_y[i], em_fit_minus_tgt_minus_mom_z[i]);
    } else if (best_tid == kTgtZero) {
      pmom = TVector3(em_fit_plus_tgt_zero_mom_x[i],  em_fit_plus_tgt_zero_mom_y[i],  em_fit_plus_tgt_zero_mom_z[i]);
      mmom = TVector3(em_fit_minus_tgt_zero_mom_x[i], em_fit_minus_tgt_zero_mom_y[i], em_fit_minus_tgt_zero_mom_z[i]);
    } else if (best_tid == kTgtPlus) {
      pmom = TVector3(em_fit_plus_tgt_plus_mom_x[i],  em_fit_plus_tgt_plus_mom_y[i],  em_fit_plus_tgt_plus_mom_z[i]);
      mmom = TVector3(em_fit_minus_tgt_plus_mom_x[i], em_fit_minus_tgt_plus_mom_y[i], em_fit_minus_tgt_plus_mom_z[i]);
    }
    em_ee_mass_at_best_tgt[i]   = CalcMass(kEE,   pmom, mmom);
    em_pipi_mass_at_best_tgt[i] = CalcMass(kPiPi, pmom, mmom);
    em_pip_mass_at_best_tgt[i]  = CalcMass(kPiP,  pmom, mmom);
    em_kk_mass_at_best_tgt[i]   = CalcMass(kKK,   pmom, mmom);
  }
  return;
}

void track_analyzer_220715::EventMixing(const EntryInfo& plus_entry, const EntryInfo& minus_entry) {
  int past_n_pairs = 0;
  for (const auto& i : plus_entry.track_indexs) {
    for (const auto& pentry : past_minus_entries) {
      for (const auto& j : pentry.track_indexs) {
        if (kAnalyzeFlag == kAnalyzePairFit) {
          PairFitEM(plus_entry.entry_index, i, pentry.entry_index, j);
        } else if (kAnalyzeFlag == kAnalyzeNearestPoint) {
          NearestPointEM(plus_entry.entry_index, i, pentry.entry_index, j);
        }
//        FillCommonBranchesEM();
      }
auto n = em_plus_run_id.size() - past_n_pairs;
for (int i = 0; i < n; ++i) {
  em_n_pairs.emplace_back(n); // need to replace to FillCommonBranchesEM()
}
past_n_pairs += n;
    }
  }
// Delete current_minus_track and past_plus_track pair to reduce process time
//  for (const auto& i : minus_entry.track_indexs) {
//    for (const auto& pentry : past_plus_entries) {
//      for (const auto& j : pentry.track_indexs) {
//        if (kAnalyzeFlag == kAnalyzePairFit) {
//          PairFitEM(pentry.entry_index, j, minus_entry.entry_index, i);
//        } else if (kAnalyzeFlag == kAnalyzeNearestPoint) {
//          NearestPointEM(pentry.entry_index, j, minus_entry.entry_index, i);
//        }
//      }
//    }
//  }
  DirIDsEM();
  ParentInfoEM();
  SimpleAnalysisEM();
  return;
}

void track_analyzer_220715::UpdatePastEntries(const EntryInfo& plus_entry, const EntryInfo& minus_entry) {
// Delete current_minus_track x past_plus_track pair to reduce process time
//  if (plus_entry.track_indexs.size() != 0) {
//    while (past_plus_entries.size() > kMaxPastEntries) {
//      past_plus_entries.erase(past_plus_entries.begin());
//    }
//    past_plus_entries.emplace_back(plus_entry);
//  }
  if (minus_entry.track_indexs.size() != 0) {
    while (past_minus_entries.size() > kMaxPastEntries) {
      past_minus_entries.erase(past_minus_entries.begin());
    }
    past_minus_entries.emplace_back(minus_entry);
  }
  return;
}

void track_analyzer_220715::AnalyzeEM(int entry_index) {
  EntryInfo plus_entry;
  EntryInfo minus_entry;
  FillEntryInfo(entry_index, &plus_entry, &minus_entry);
  ClearEMBranches();
  EventMixing(plus_entry, minus_entry);
  UpdatePastEntries(plus_entry, minus_entry);
  fChain->GetEntry(entry_index);
cerr << past_plus_entries.size() << " " << past_minus_entries.size() << endl;
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
  auto tree_em = TTree("tree_em", "tree_em");
  MakeBranches(&tree);
  if (kExecuteEventMixing) {
    MakeEMBranches(&tree_em);
  }
  for (Long64_t jentry = 0; jentry < nentries; ++jentry) {
    cout << jentry << " / " << nentries << endl;
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
//    if (Cut(ientry) < 0) continue;
    ClearUsedClusterIDs();
    SetHBDs();
//    SetLGs();
    SetTracks();
    SetPairs();
    ClearAndResizeBranches();
    if (kExecuteEventMixing) {
      ClearEMBranches();
    }
    Analyze();
    tree.Fill();
    if (kExecuteEventMixing) {
      AnalyzeEM(jentry);
      tree_em.Fill();
    }
  }
  file.Write();
}
