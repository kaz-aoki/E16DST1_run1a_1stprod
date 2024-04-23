#ifndef E16DSTN_POSCORRECTION_HH 
#define E16DSTN_POSCORRECTION_HH

#include <TROOT.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TVector3.h>
#include <TTree.h>
#include <TFile.h>
#include <TBranch.h>
#include <vector>
#include <array>
#include <iostream>
#include "E16ANA_StraightTrackConstant.hh"
#include "E16ANA_StraightMultiTrack.hh"
#include "E16DST_DST1Constant.hh"

class E16DSTN_PosCorrection {
public : 
	TTree *fChain;
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           run_id;
   Int_t           event_id;
   Int_t           spill_id;
   ULong64_t       timestamp_in_spill;
   Int_t           trigger_fine_time;
   Int_t           n_fill;
   Int_t           n_ssd_hits;
   std::vector<int>     *ssd_hit_id;
   std::vector<int>     *ssd_hit_mid;
   std::vector<int>     *ssd_hit_cid;
   std::vector<double>  *ssd_hit_x;
   std::vector<double>  *ssd_hit_gx;
   std::vector<double>  *ssd_hit_gz;
   std::vector<double>  *ssd_hit_t;
   std::vector<float>   *ssd_hit_adc;
   Int_t           n_gtr100x_hits;
   std::vector<int>     *gtr100x_hit_id;
   std::vector<int>     *gtr100x_hit_mid;
   std::vector<int>     *gtr100x_hit_cid;
   std::vector<double>  *gtr100x_hit_x;
   std::vector<double>  *gtr100x_hit_tx;
   std::vector<double>  *gtr100x_hit_gx;
   std::vector<double>  *gtr100x_hit_gz;
   std::vector<double>  *gtr100x_hit_t;
   std::vector<float>   *gtr100x_hit_adc;
   Int_t           n_gtr200x_hits;
   std::vector<int>     *gtr200x_hit_id;
   std::vector<int>     *gtr200x_hit_mid;
   std::vector<int>     *gtr200x_hit_cid;
   std::vector<double>  *gtr200x_hit_x;
   std::vector<double>  *gtr200x_hit_tx;
   std::vector<double>  *gtr200x_hit_gx;
   std::vector<double>  *gtr200x_hit_gz;
   std::vector<double>  *gtr200x_hit_t;
   std::vector<float>   *gtr200x_hit_adc;
   Int_t           n_gtr300x_hits;
   std::vector<int>     *gtr300x_hit_id;
   std::vector<int>     *gtr300x_hit_mid;
   std::vector<int>     *gtr300x_hit_cid;
   std::vector<double>  *gtr300x_hit_x;
   std::vector<double>  *gtr300x_hit_tx;
   std::vector<double>  *gtr300x_hit_gx;
   std::vector<double>  *gtr300x_hit_gz;
   std::vector<double>  *gtr300x_hit_t;
   std::vector<float>   *gtr300x_hit_adc;
   Int_t           n_gtr100y_hits;
   std::vector<int>     *gtr100y_hit_id;
   std::vector<int>     *gtr100y_hit_mid;
   std::vector<int>     *gtr100y_hit_cid;
   std::vector<double>  *gtr100y_hit_y;
   std::vector<double>  *gtr100y_hit_ty;
   std::vector<double>  *gtr100y_hit_t;
   std::vector<float>   *gtr100y_hit_adc;
   Int_t           n_gtr100yb_hits;
   std::vector<int>     *gtr100yb_hit_id;
   std::vector<int>     *gtr100yb_hit_mid;
   std::vector<int>     *gtr100yb_hit_cid;
   std::vector<double>  *gtr100yb_hit_y;
   std::vector<double>  *gtr100yb_hit_ty;
   std::vector<double>  *gtr100yb_hit_t;
   std::vector<float>   *gtr100yb_hit_adc;
   Int_t           n_gtr200y_hits;
   std::vector<int>     *gtr200y_hit_id;
   std::vector<int>     *gtr200y_hit_mid;
   std::vector<int>     *gtr200y_hit_cid;
   std::vector<double>  *gtr200y_hit_y;
   std::vector<double>  *gtr200y_hit_ty;
   std::vector<double>  *gtr200y_hit_t;
   std::vector<float>   *gtr200y_hit_adc;
   Int_t           n_gtr300y_hits;
   std::vector<int>     *gtr300y_hit_id;
   std::vector<int>     *gtr300y_hit_mid;
   std::vector<int>     *gtr300y_hit_cid;
   std::vector<double>  *gtr300y_hit_y;
   std::vector<double>  *gtr300y_hit_ty;
   std::vector<double>  *gtr300y_hit_t;
   std::vector<float>   *gtr300y_hit_adc;
   Int_t           n_hbd_hits;
   std::vector<int>     *hbd_hit_id;
   std::vector<int>     *hbd_hit_mid;
   std::vector<int>     *hbd_hit_cid;
   std::vector<double>  *hbd_hit_x;
   std::vector<double>  *hbd_hit_y;
   std::vector<double>  *hbd_hit_gx;
   std::vector<double>  *hbd_hit_gy;
   std::vector<double>  *hbd_hit_gz;
   std::vector<double>  *hbd_hit_t;
   std::vector<float>   *hbd_hit_adc;
   Int_t           n_ssd_clusters;
   std::vector<int>     *ssd_cluster_id;
   std::vector<int>     *ssd_cluster_mid;
   std::vector<double>  *ssd_cluster_x;
   std::vector<double>  *ssd_cluster_gx;
   std::vector<double>  *ssd_cluster_gz;
   std::vector<float>   *ssd_cluster_adc;
   std::vector<double>  *ssd_cluster_t;
   std::vector<int>     *ssd_cluster_size;
   std::vector<double>  *ssd_cluster_fit_x;
   std::vector<double>  *ssd_cluster_fit_t;
   std::vector<double>  *ssd_cluster_fit_adc;
   std::vector<double>  *ssd_cluster_fit_chi2;
   Int_t           n_gtr100x_clusters;
   std::vector<int>     *gtr100x_cluster_id;
   std::vector<int>     *gtr100x_cluster_mid;
   std::vector<double>  *gtr100x_cluster_x;
   std::vector<double>  *gtr100x_cluster_gx;
   std::vector<double>  *gtr100x_cluster_gz;
   std::vector<float>   *gtr100x_cluster_adc;
   std::vector<double>  *gtr100x_cluster_t;
   std::vector<double>  *gtr100x_cluster_t2;
   std::vector<double>  *gtr100x_cluster_tx;
   std::vector<double>  *gtr100x_cluster_the;
   std::vector<double>  *gtr100x_cluster_gtx;
   std::vector<int>     *gtr100x_cluster_nc;
   std::vector<int>     *gtr100x_cluster_size;
   Int_t           n_gtr200x_clusters;
   std::vector<int>     *gtr200x_cluster_id;
   std::vector<int>     *gtr200x_cluster_mid;
   std::vector<double>  *gtr200x_cluster_x;
   std::vector<double>  *gtr200x_cluster_gx;
   std::vector<double>  *gtr200x_cluster_gz;
   std::vector<float>   *gtr200x_cluster_adc;
   std::vector<double>  *gtr200x_cluster_t;
   std::vector<double>  *gtr200x_cluster_t2;
   std::vector<double>  *gtr200x_cluster_tx;
   std::vector<double>  *gtr200x_cluster_the;
   std::vector<int>     *gtr200x_cluster_nc;
   std::vector<double>  *gtr200x_cluster_gtx;
   std::vector<int>     *gtr200x_cluster_size;
   Int_t           n_gtr300x_clusters;
   std::vector<int>     *gtr300x_cluster_id;
   std::vector<int>     *gtr300x_cluster_mid;
   std::vector<double>  *gtr300x_cluster_x;
   std::vector<double>  *gtr300x_cluster_gx;
   std::vector<double>  *gtr300x_cluster_gz;
   std::vector<float>   *gtr300x_cluster_adc;
   std::vector<double>  *gtr300x_cluster_t;
   std::vector<double>  *gtr300x_cluster_t2;
   std::vector<double>  *gtr300x_cluster_tx;
   std::vector<double>  *gtr300x_cluster_the;
   std::vector<int>     *gtr300x_cluster_nc;
   std::vector<double>  *gtr300x_cluster_gtx;
   std::vector<int>     *gtr300x_cluster_size;
   Int_t           n_gtr100y_clusters;
   std::vector<int>     *gtr100y_cluster_id;
   std::vector<int>     *gtr100y_cluster_mid;
   std::vector<double>  *gtr100y_cluster_y;
   std::vector<float>   *gtr100y_cluster_adc;
   std::vector<double>  *gtr100y_cluster_t;
   std::vector<double>  *gtr100y_cluster_t2;
   std::vector<double>  *gtr100y_cluster_ty;
   std::vector<double>  *gtr100y_cluster_the;
   std::vector<int>     *gtr100y_cluster_nc;
   std::vector<int>     *gtr100y_cluster_size;
   Int_t           n_gtr100yb_clusters;
   std::vector<int>     *gtr100yb_cluster_id;
   std::vector<int>     *gtr100yb_cluster_mid;
   std::vector<double>  *gtr100yb_cluster_y;
   std::vector<float>   *gtr100yb_cluster_adc;
   std::vector<double>  *gtr100yb_cluster_t;
   std::vector<double>  *gtr100yb_cluster_t2;
   std::vector<double>  *gtr100yb_cluster_ty;
   std::vector<double>  *gtr100yb_cluster_the;
   std::vector<int>     *gtr100yb_cluster_nc;
   std::vector<int>     *gtr100yb_cluster_size;
   Int_t           n_gtr200y_clusters;
   std::vector<int>     *gtr200y_cluster_id;
   std::vector<int>     *gtr200y_cluster_mid;
   std::vector<double>  *gtr200y_cluster_y;
   std::vector<float>   *gtr200y_cluster_adc;
   std::vector<double>  *gtr200y_cluster_t;
   std::vector<double>  *gtr200y_cluster_t2;
   std::vector<double>  *gtr200y_cluster_ty;
   std::vector<double>  *gtr200y_cluster_the;
   std::vector<int>     *gtr200y_cluster_nc;
   std::vector<int>     *gtr200y_cluster_size;
   Int_t           n_gtr300y_clusters;
   std::vector<int>     *gtr300y_cluster_id;
   std::vector<int>     *gtr300y_cluster_mid;
   std::vector<double>  *gtr300y_cluster_y;
   std::vector<float>   *gtr300y_cluster_adc;
   std::vector<double>  *gtr300y_cluster_t;
   std::vector<double>  *gtr300y_cluster_t2;
   std::vector<double>  *gtr300y_cluster_ty;
   std::vector<double>  *gtr300y_cluster_the;
   std::vector<int>     *gtr300y_cluster_nc;
   std::vector<int>     *gtr300y_cluster_size;
   Int_t           n_hbd_clusters;
   std::vector<int>     *hbd_cluster_id;
   std::vector<int>     *hbd_cluster_mid;
   std::vector<double>  *hbd_cluster_x;
   std::vector<double>  *hbd_cluster_y;
   std::vector<double>  *hbd_cluster_gx;
   std::vector<double>  *hbd_cluster_gy;
   std::vector<double>  *hbd_cluster_gz;
   std::vector<float>   *hbd_cluster_adc;
   std::vector<int>     *hbd_cluster_max_cid;
   std::vector<double>  *hbd_cluster_t;
   std::vector<float>   *hbd_cluster_ftime;
   std::vector<float>   *hbd_cluster_tdiff;
   std::vector<int>     *hbd_cluster_size;
   std::vector<float>   *hbd_cluster_eprob;
   std::vector<float>   *hbd_cluster_cprob;
   Int_t           n_hbd_clusters_wotime;
   std::vector<int>     *hbd_cluster_wotime_id;
   std::vector<int>     *hbd_cluster_wotime_mid;
   std::vector<double>  *hbd_cluster_wotime_x;
   std::vector<double>  *hbd_cluster_wotime_y;
   std::vector<double>  *hbd_cluster_wotime_gx;
   std::vector<double>  *hbd_cluster_wotime_gy;
   std::vector<double>  *hbd_cluster_wotime_gz;
   std::vector<float>   *hbd_cluster_wotime_adc;
   std::vector<int>     *hbd_cluster_wotime_max_cid;
   std::vector<double>  *hbd_cluster_wotime_t;
   std::vector<float>   *hbd_cluster_wotime_ftime;
   std::vector<float>   *hbd_cluster_wotime_tdiff;
   std::vector<int>     *hbd_cluster_wotime_size;
   std::vector<float>   *hbd_cluster_wotime_eprob;
   std::vector<float>   *hbd_cluster_wotime_cprob;
   Int_t           n_lg_hits;
   std::vector<int>     *lg_hit_id;
   std::vector<int>     *lg_hit_mid;
   std::vector<int>     *lg_hit_cid;
   std::vector<double>  *lg_hit_x;
   std::vector<double>  *lg_hit_y;
   std::vector<double>  *lg_hit_z;
   std::vector<double>  *lg_hit_gx;
   std::vector<double>  *lg_hit_gy;
   std::vector<double>  *lg_hit_gz;
   std::vector<float>   *lg_hit_adc;
   std::vector<float>   *lg_hit_t;
   std::vector<float>   *lg_hit_wofit_adc;
   std::vector<float>   *lg_hit_wofit_t;
   std::vector<int>     *lg_hit_npeaks;
   std::vector<int>     *lg_hit_fflag;
   Int_t           n_lg_clusters;
   std::vector<int>     *lg_cluster_id;
   std::vector<int>     *lg_cluster_mid;
   std::vector<int>     *lg_cluster_max_cid;
   std::vector<int>     *lg_cluster_max_adc;
   std::vector<double>  *lg_cluster_x;
   std::vector<double>  *lg_cluster_y;
   std::vector<double>  *lg_cluster_z;
   std::vector<double>  *lg_cluster_gx;
   std::vector<double>  *lg_cluster_gy;
   std::vector<double>  *lg_cluster_gz;
   std::vector<float>   *lg_cluster_adc;
   std::vector<float>   *lg_cluster_t;
   std::vector<float>   *lg_cluster_tdiff;
   std::vector<int>     *lg_cluster_size;
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
   std::vector<double>  *trg_lg_hit_z;
   std::vector<double>  *trg_lg_hit_gx;
   std::vector<double>  *trg_lg_hit_gy;
   std::vector<double>  *trg_lg_hit_gz;
   std::vector<float>   *trg_lg_hit_t;
   Int_t           n_trg_tracks;
   std::vector<int>     *trg_track_n_gtr_hits;
   std::vector<std::vector<double> > *trg_track_gtr_id;
   std::vector<std::vector<double> > *trg_track_gtr_mid;
   std::vector<std::vector<double> > *trg_track_gtr_cid;
   std::vector<std::vector<double> > *trg_track_gtr_x;
   std::vector<std::vector<double> > *trg_track_gtr_y;
   std::vector<std::vector<double> > *trg_track_gtr_t;
   std::vector<std::vector<double> > *trg_track_gtr_is_t_match;
   std::vector<int>     *trg_track_n_hbd_hits;
   std::vector<std::vector<double> > *trg_track_hbd_id;
   std::vector<std::vector<double> > *trg_track_hbd_mid;
   std::vector<std::vector<double> > *trg_track_hbd_cid;
   std::vector<std::vector<double> > *trg_track_hbd_x;
   std::vector<std::vector<double> > *trg_track_hbd_y;
   std::vector<std::vector<double> > *trg_track_hbd_t;
   std::vector<std::vector<double> > *trg_track_hbd_is_t_match;
   std::vector<int>     *trg_track_lg_id;
   std::vector<int>     *trg_track_lg_mid;
   std::vector<int>     *trg_track_lg_cid;
   std::vector<double>  *trg_track_lg_x;
   std::vector<double>  *trg_track_lg_y;
   std::vector<float>   *trg_track_lg_t;
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
   std::vector<double>  *x_rough_fit_dist0;
   std::vector<double>  *x_rough_fit_dist1;
   std::vector<double>  *x_rough_fit_coef0;
   std::vector<double>  *x_rough_fit_coef1;
   std::vector<double>  *x_rough_fit_coef2;
   std::vector<int>     *rough_fit_n_hbds;
   std::vector<std::vector<double> > *rough_fit_hbd_ids;
   std::vector<std::vector<double> > *rough_fit_hbd_ress;
   std::vector<std::vector<double> > *rough_fit_hbd_y_oks;
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
   std::vector<double>  *rk_hit_ssd_x;
   std::vector<double>  *rk_hit_ssd_gx;
   std::vector<double>  *rk_hit_ssd_gy;
   std::vector<double>  *rk_hit_ssd_gz;
   std::vector<float>   *rk_hit_ssd_adc;
   std::vector<float>   *rk_hit_ssd_t;
   std::vector<double>  *rk_hit_ssd_chi2;
   std::vector<int>     *rk_hit_gtr100_xid;
   std::vector<int>     *rk_hit_gtr100_yid;
   std::vector<double>  *rk_hit_gtr100_gx;
   std::vector<double>  *rk_hit_gtr100_gy;
   std::vector<double>  *rk_hit_gtr100_gz;
   std::vector<float>   *rk_hit_gtr100_xadc;
   std::vector<float>   *rk_hit_gtr100_yadc;
   std::vector<float>   *rk_hit_gtr100_xt;
   std::vector<float>   *rk_hit_gtr100_yt;
   std::vector<float>   *rk_hit_gtr100_xt2;
   std::vector<float>   *rk_hit_gtr100_yt2;
   std::vector<double>  *rk_hit_gtr100_tx2;
   std::vector<double>  *rk_hit_gtr100_ty;
   std::vector<double>  *rk_hit_gtr100_gtx;
   std::vector<double>  *rk_hit_gtr100_gty;
   std::vector<double>  *rk_hit_gtr100_gtz;
   std::vector<double>  *rk_hit_gtr100_gtx2;
   std::vector<double>  *rk_hit_gtr100_gty2;
   std::vector<double>  *rk_hit_gtr100_gtz2;
   std::vector<int>     *rk_hit_gtr100_nc;
   std::vector<double>  *rk_hit_gtr100_the;
   std::vector<double>  *rk_hit_gtr100_the2;
   std::vector<int>     *rk_hit_gtr200_xid;
   std::vector<int>     *rk_hit_gtr200_yid;
   std::vector<double>  *rk_hit_gtr200_gx;
   std::vector<double>  *rk_hit_gtr200_gy;
   std::vector<double>  *rk_hit_gtr200_gz;
   std::vector<float>   *rk_hit_gtr200_xadc;
   std::vector<float>   *rk_hit_gtr200_yadc;
   std::vector<float>   *rk_hit_gtr200_xt;
   std::vector<float>   *rk_hit_gtr200_yt;
   std::vector<float>   *rk_hit_gtr200_xt2;
   std::vector<float>   *rk_hit_gtr200_yt2;
   std::vector<double>  *rk_hit_gtr200_tx2;
   std::vector<double>  *rk_hit_gtr200_ty;
   std::vector<double>  *rk_hit_gtr200_gtx;
   std::vector<double>  *rk_hit_gtr200_gty;
   std::vector<double>  *rk_hit_gtr200_gtz;
   std::vector<double>  *rk_hit_gtr200_gtx2;
   std::vector<double>  *rk_hit_gtr200_gty2;
   std::vector<double>  *rk_hit_gtr200_gtz2;
   std::vector<int>     *rk_hit_gtr200_nc;
   std::vector<double>  *rk_hit_gtr200_the;
   std::vector<double>  *rk_hit_gtr200_the2;
   std::vector<int>     *rk_hit_gtr300_xid;
   std::vector<int>     *rk_hit_gtr300_yid;
   std::vector<double>  *rk_hit_gtr300_gx;
   std::vector<double>  *rk_hit_gtr300_gy;
   std::vector<double>  *rk_hit_gtr300_gz;
   std::vector<float>   *rk_hit_gtr300_xadc;
   std::vector<float>   *rk_hit_gtr300_yadc;
   std::vector<float>   *rk_hit_gtr300_xt;
   std::vector<float>   *rk_hit_gtr300_yt;
   std::vector<float>   *rk_hit_gtr300_xt2;
   std::vector<float>   *rk_hit_gtr300_yt2;
   std::vector<double>  *rk_hit_gtr300_tx2;
   std::vector<double>  *rk_hit_gtr300_ty;
   std::vector<double>  *rk_hit_gtr300_gtx;
   std::vector<double>  *rk_hit_gtr300_gty;
   std::vector<double>  *rk_hit_gtr300_gtz;
   std::vector<double>  *rk_hit_gtr300_gtx2;
   std::vector<double>  *rk_hit_gtr300_gty2;
   std::vector<double>  *rk_hit_gtr300_gtz2;
   std::vector<int>     *rk_hit_gtr300_nc;
   std::vector<double>  *rk_hit_gtr300_the;
   std::vector<double>  *rk_hit_gtr300_the2;
   std::vector<double>  *rk_fit_init_mom_gx;
   std::vector<double>  *rk_fit_init_mom_gy;
   std::vector<double>  *rk_fit_init_mom_gz;
   std::vector<double>  *rk_fit_init_pos_gx;
   std::vector<double>  *rk_fit_init_pos_gy;
   std::vector<double>  *rk_fit_init_pos_gz;
   std::vector<int>     *rk_fit_ssd_mid;
   std::vector<double>  *rk_fit_ssd_x;
   std::vector<double>  *rk_fit_ssd_y;
   std::vector<double>  *rk_fit_ssd_gx;
   std::vector<double>  *rk_fit_ssd_gy;
   std::vector<double>  *rk_fit_ssd_gz;
   std::vector<double>  *rk_fit_ssd_mom_x;
   std::vector<double>  *rk_fit_ssd_mom_y;
   std::vector<double>  *rk_fit_ssd_mom_z;
   std::vector<double>  *rk_fit_ssd_mom_gx;
   std::vector<double>  *rk_fit_ssd_mom_gy;
   std::vector<double>  *rk_fit_ssd_mom_gz;
   std::vector<int>     *rk_fit_gtr100_mid;
   std::vector<double>  *rk_fit_gtr100_x;
   std::vector<double>  *rk_fit_gtr100_y;
   std::vector<double>  *rk_fit_gtr100_gx;
   std::vector<double>  *rk_fit_gtr100_gy;
   std::vector<double>  *rk_fit_gtr100_gz;
   std::vector<double>  *rk_fit_gtr100_mom_x;
   std::vector<double>  *rk_fit_gtr100_mom_y;
   std::vector<double>  *rk_fit_gtr100_mom_z;
   std::vector<double>  *rk_fit_gtr100_mom_gx;
   std::vector<double>  *rk_fit_gtr100_mom_gy;
   std::vector<double>  *rk_fit_gtr100_mom_gz;
   std::vector<int>     *rk_fit_gtr200_mid;
   std::vector<double>  *rk_fit_gtr200_x;
   std::vector<double>  *rk_fit_gtr200_y;
   std::vector<double>  *rk_fit_gtr200_gx;
   std::vector<double>  *rk_fit_gtr200_gy;
   std::vector<double>  *rk_fit_gtr200_gz;
   std::vector<double>  *rk_fit_gtr200_mom_x;
   std::vector<double>  *rk_fit_gtr200_mom_y;
   std::vector<double>  *rk_fit_gtr200_mom_z;
   std::vector<double>  *rk_fit_gtr200_mom_gx;
   std::vector<double>  *rk_fit_gtr200_mom_gy;
   std::vector<double>  *rk_fit_gtr200_mom_gz;
   std::vector<int>     *rk_fit_gtr300_mid;
   std::vector<double>  *rk_fit_gtr300_x;
   std::vector<double>  *rk_fit_gtr300_y;
   std::vector<double>  *rk_fit_gtr300_gx;
   std::vector<double>  *rk_fit_gtr300_gy;
   std::vector<double>  *rk_fit_gtr300_gz;
   std::vector<double>  *rk_fit_gtr300_mom_x;
   std::vector<double>  *rk_fit_gtr300_mom_y;
   std::vector<double>  *rk_fit_gtr300_mom_z;
   std::vector<double>  *rk_fit_gtr300_mom_gx;
   std::vector<double>  *rk_fit_gtr300_mom_gy;
   std::vector<double>  *rk_fit_gtr300_mom_gz;
   std::vector<int>     *rk_fit_hbd_mid;
   std::vector<double>  *rk_fit_hbd_x;
   std::vector<double>  *rk_fit_hbd_y;
   std::vector<double>  *rk_fit_hbd_gx;
   std::vector<double>  *rk_fit_hbd_gy;
   std::vector<double>  *rk_fit_hbd_gz;
   std::vector<double>  *rk_fit_hbd_mom_x;
   std::vector<double>  *rk_fit_hbd_mom_y;
   std::vector<double>  *rk_fit_hbd_mom_z;
   std::vector<double>  *rk_fit_hbd_mom_gx;
   std::vector<double>  *rk_fit_hbd_mom_gy;
   std::vector<double>  *rk_fit_hbd_mom_gz;
   std::vector<int>     *rk_fit_lg_c_mid;
   std::vector<double>  *rk_fit_lg_c_x;
   std::vector<double>  *rk_fit_lg_c_y;
   std::vector<double>  *rk_fit_lg_c_gx;
   std::vector<double>  *rk_fit_lg_c_gy;
   std::vector<double>  *rk_fit_lg_c_gz;
   std::vector<double>  *rk_fit_lg_c_mom_x;
   std::vector<double>  *rk_fit_lg_c_mom_y;
   std::vector<double>  *rk_fit_lg_c_mom_z;
   std::vector<double>  *rk_fit_lg_c_mom_gx;
   std::vector<double>  *rk_fit_lg_c_mom_gy;
   std::vector<double>  *rk_fit_lg_c_mom_gz;
   std::vector<int>     *rk_fit_lg_b_mid;
   std::vector<double>  *rk_fit_lg_b_x;
   std::vector<double>  *rk_fit_lg_b_y;
   std::vector<double>  *rk_fit_lg_b_gx;
   std::vector<double>  *rk_fit_lg_b_gy;
   std::vector<double>  *rk_fit_lg_b_gz;
   std::vector<double>  *rk_fit_lg_b_mom_x;
   std::vector<double>  *rk_fit_lg_b_mom_y;
   std::vector<double>  *rk_fit_lg_b_mom_z;
   std::vector<double>  *rk_fit_lg_b_mom_gx;
   std::vector<double>  *rk_fit_lg_b_mom_gy;
   std::vector<double>  *rk_fit_lg_b_mom_gz;
   std::vector<int>     *rk_fit_lg_a_mid;
   std::vector<double>  *rk_fit_lg_a_x;
   std::vector<double>  *rk_fit_lg_a_y;
   std::vector<double>  *rk_fit_lg_a_gx;
   std::vector<double>  *rk_fit_lg_a_gy;
   std::vector<double>  *rk_fit_lg_a_gz;
   std::vector<double>  *rk_fit_lg_a_mom_x;
   std::vector<double>  *rk_fit_lg_a_mom_y;
   std::vector<double>  *rk_fit_lg_a_mom_z;
   std::vector<double>  *rk_fit_lg_a_mom_gx;
   std::vector<double>  *rk_fit_lg_a_mom_gy;
   std::vector<double>  *rk_fit_lg_a_mom_gz;
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
   std::vector<double>  *rk_res_gtr100_tx;
   std::vector<double>  *rk_res_gtr100_ty;
   std::vector<double>  *rk_res_gtr200_tx;
   std::vector<double>  *rk_res_gtr200_ty;
   std::vector<double>  *rk_res_gtr300_tx;
   std::vector<double>  *rk_res_gtr300_ty;
   std::vector<double>  *rk_res_gtr100_tx2;
   std::vector<double>  *rk_res_gtr200_tx2;
   std::vector<double>  *rk_res_gtr300_tx2;
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
   std::vector<bool>    *rk_proj_is_search;
   std::vector<int>     *rk_proj_n_hbd;
   std::vector<std::vector<double> > *rk_proj_hbd_id;
   std::vector<std::vector<double> > *rk_proj_hbd_mid;
   std::vector<std::vector<double> > *rk_proj_hbd_x;
   std::vector<std::vector<double> > *rk_proj_hbd_y;
   std::vector<std::vector<double> > *rk_proj_hbd_adc;
   std::vector<std::vector<double> > *rk_proj_hbd_t;
   std::vector<std::vector<double> > *rk_proj_hbd_ftime;
   std::vector<std::vector<double> > *rk_proj_hbd_tdiff;
   std::vector<std::vector<double> > *rk_proj_hbd_size;
   std::vector<std::vector<double> > *rk_proj_hbd_eprob;
   std::vector<std::vector<double> > *rk_proj_hbd_cprob;
   std::vector<int>     *rk_proj_n_lg;
   std::vector<std::vector<double> > *rk_proj_lg_id;
   std::vector<std::vector<double> > *rk_proj_lg_mid;
   std::vector<std::vector<double> > *rk_proj_lg_cid;
   std::vector<std::vector<double> > *rk_proj_lg_x;
   std::vector<std::vector<double> > *rk_proj_lg_y;
   std::vector<std::vector<double> > *rk_proj_lg_adc;
   std::vector<std::vector<double> > *rk_proj_lg_t;
   std::vector<std::vector<double> > *rk_proj_lg_npeaks;
   std::vector<std::vector<double> > *rk_proj_lg_fflag;
   std::vector<int>     *rk_pair_minus_track_id;
   std::vector<int>     *rk_pair_minus_gtr300_mid;
   std::vector<double>  *rk_pair_minus_chi_square;
   std::vector<double>  *rk_pair_minus_mom_gx;
   std::vector<double>  *rk_pair_minus_mom_gy;
   std::vector<double>  *rk_pair_minus_mom_gz;
   std::vector<double>  *rk_pair_minus_ssd_t;
   std::vector<std::vector<double> > *rk_pair_minus_lg_t;
   std::vector<int>     *rk_pair_plus_track_id;
   std::vector<int>     *rk_pair_plus_gtr300_mid;
   std::vector<double>  *rk_pair_plus_chi_square;
   std::vector<double>  *rk_pair_plus_mom_gx;
   std::vector<double>  *rk_pair_plus_mom_gy;
   std::vector<double>  *rk_pair_plus_mom_gz;
   std::vector<double>  *rk_pair_plus_ssd_t;
   std::vector<std::vector<double> > *rk_pair_plus_lg_t;
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

   std::vector<double>  *rk_hit_gtr100_cogx;
   std::vector<double>  *rk_hit_gtr200_cogx;
   std::vector<double>  *rk_hit_gtr300_cogx;
   std::vector<double>  *rk_hit_gtr100_cogy;
   std::vector<double>  *rk_hit_gtr200_cogy;
   std::vector<double>  *rk_hit_gtr300_cogy;
	
   std::vector<float>   *rk_hit_gtr100_xt4;
   std::vector<float>   *rk_hit_gtr200_xt4;
   std::vector<float>   *rk_hit_gtr300_xt4;
   std::vector<float>   *rk_hit_gtr100_yt4;
   std::vector<float>   *rk_hit_gtr200_yt4;
   std::vector<float>   *rk_hit_gtr300_yt4;


   // List of branches
   //
   //

   TBranch  *b_rk_hit_gtr100_xt4;
   TBranch    *b_rk_hit_gtr200_xt4;
   TBranch    *b_rk_hit_gtr300_xt4;
   TBranch    *b_rk_hit_gtr100_yt4;
   TBranch    *b_rk_hit_gtr200_yt4;
   TBranch    *b_rk_hit_gtr300_yt4;
   TBranch        *b_run_id;   //!
   TBranch        *b_event_id;   //!
   TBranch        *b_spill_id;   //!
   TBranch        *b_timestamp_in_spill;   //!
   TBranch        *b_trigger_fine_time;   //!
   TBranch        *b_n_fill;   //!
   TBranch        *b_n_ssd_hits;   //!
   TBranch        *b_ssd_hit_id;   //!
   TBranch        *b_ssd_hit_mid;   //!
   TBranch        *b_ssd_hit_cid;   //!
   TBranch        *b_ssd_hit_x;   //!
   TBranch        *b_ssd_hit_gx;   //!
   TBranch        *b_ssd_hit_gz;   //!
   TBranch        *b_ssd_hit_t;   //!
   TBranch        *b_ssd_hit_adc;   //!
   TBranch        *b_n_gtr100x_hits;   //!
   TBranch        *b_gtr100x_hit_id;   //!
   TBranch        *b_gtr100x_hit_mid;   //!
   TBranch        *b_gtr100x_hit_cid;   //!
   TBranch        *b_gtr100x_hit_x;   //!
   TBranch        *b_gtr100x_hit_tx;   //!
   TBranch        *b_gtr100x_hit_gx;   //!
   TBranch        *b_gtr100x_hit_gz;   //!
   TBranch        *b_gtr100x_hit_t;   //!
   TBranch        *b_gtr100x_hit_adc;   //!
   TBranch        *b_n_gtr200x_hits;   //!
   TBranch        *b_gtr200x_hit_id;   //!
   TBranch        *b_gtr200x_hit_mid;   //!
   TBranch        *b_gtr200x_hit_cid;   //!
   TBranch        *b_gtr200x_hit_x;   //!
   TBranch        *b_gtr200x_hit_tx;   //!
   TBranch        *b_gtr200x_hit_gx;   //!
   TBranch        *b_gtr200x_hit_gz;   //!
   TBranch        *b_gtr200x_hit_t;   //!
   TBranch        *b_gtr200x_hit_adc;   //!
   TBranch        *b_n_gtr300x_hits;   //!
   TBranch        *b_gtr300x_hit_id;   //!
   TBranch        *b_gtr300x_hit_mid;   //!
   TBranch        *b_gtr300x_hit_cid;   //!
   TBranch        *b_gtr300x_hit_x;   //!
   TBranch        *b_gtr300x_hit_tx;   //!
   TBranch        *b_gtr300x_hit_gx;   //!
   TBranch        *b_gtr300x_hit_gz;   //!
   TBranch        *b_gtr300x_hit_t;   //!
   TBranch        *b_gtr300x_hit_adc;   //!
   TBranch        *b_n_gtr100y_hits;   //!
   TBranch        *b_gtr100y_hit_id;   //!
   TBranch        *b_gtr100y_hit_mid;   //!
   TBranch        *b_gtr100y_hit_cid;   //!
   TBranch        *b_gtr100y_hit_y;   //!
   TBranch        *b_gtr100y_hit_ty;   //!
   TBranch        *b_gtr100y_hit_t;   //!
   TBranch        *b_gtr100y_hit_adc;   //!
   TBranch        *b_n_gtr100yb_hits;   //!
   TBranch        *b_gtr100yb_hit_id;   //!
   TBranch        *b_gtr100yb_hit_mid;   //!
   TBranch        *b_gtr100yb_hit_cid;   //!
   TBranch        *b_gtr100yb_hit_y;   //!
   TBranch        *b_gtr100yb_hit_ty;   //!
   TBranch        *b_gtr100yb_hit_t;   //!
   TBranch        *b_gtr100yb_hit_adc;   //!
   TBranch        *b_n_gtr200y_hits;   //!
   TBranch        *b_gtr200y_hit_id;   //!
   TBranch        *b_gtr200y_hit_mid;   //!
   TBranch        *b_gtr200y_hit_cid;   //!
   TBranch        *b_gtr200y_hit_y;   //!
   TBranch        *b_gtr200y_hit_ty;   //!
   TBranch        *b_gtr200y_hit_t;   //!
   TBranch        *b_gtr200y_hit_adc;   //!
   TBranch        *b_n_gtr300y_hits;   //!
   TBranch        *b_gtr300y_hit_id;   //!
   TBranch        *b_gtr300y_hit_mid;   //!
   TBranch        *b_gtr300y_hit_cid;   //!
   TBranch        *b_gtr300y_hit_y;   //!
   TBranch        *b_gtr300y_hit_ty;   //!
   TBranch        *b_gtr300y_hit_t;   //!
   TBranch        *b_gtr300y_hit_adc;   //!
   TBranch        *b_n_hbd_hits;   //!
   TBranch        *b_hbd_hit_id;   //!
   TBranch        *b_hbd_hit_mid;   //!
   TBranch        *b_hbd_hit_cid;   //!
   TBranch        *b_hbd_hit_x;   //!
   TBranch        *b_hbd_hit_y;   //!
   TBranch        *b_hbd_hit_gx;   //!
   TBranch        *b_hbd_hit_gy;   //!
   TBranch        *b_hbd_hit_gz;   //!
   TBranch        *b_hbd_hit_t;   //!
   TBranch        *b_hbd_hit_adc;   //!
   TBranch        *b_n_ssd_clusters;   //!
   TBranch        *b_ssd_cluster_id;   //!
   TBranch        *b_ssd_cluster_mid;   //!
   TBranch        *b_ssd_cluster_x;   //!
   TBranch        *b_ssd_cluster_gx;   //!
   TBranch        *b_ssd_cluster_gz;   //!
   TBranch        *b_ssd_cluster_adc;   //!
   TBranch        *b_ssd_cluster_t;   //!
   TBranch        *b_ssd_cluster_size;   //!
   TBranch        *b_ssd_cluster_fit_x;   //!
   TBranch        *b_ssd_cluster_fit_t;   //!
   TBranch        *b_ssd_cluster_fit_adc;   //!
   TBranch        *b_ssd_cluster_fit_chi2;   //!
   TBranch        *b_n_gtr100x_clusters;   //!
   TBranch        *b_gtr100x_cluster_id;   //!
   TBranch        *b_gtr100x_cluster_mid;   //!
   TBranch        *b_gtr100x_cluster_x;   //!
   TBranch        *b_gtr100x_cluster_gx;   //!
   TBranch        *b_gtr100x_cluster_gz;   //!
   TBranch        *b_gtr100x_cluster_adc;   //!
   TBranch        *b_gtr100x_cluster_t;   //!
   TBranch        *b_gtr100x_cluster_t2;   //!
   TBranch        *b_gtr100x_cluster_tx;   //!
   TBranch        *b_gtr100x_cluster_the;   //!
   TBranch        *b_gtr100x_cluster_gtx;   //!
   TBranch        *b_gtr100x_cluster_nc;   //!
   TBranch        *b_gtr100x_cluster_size;   //!
   TBranch        *b_n_gtr200x_clusters;   //!
   TBranch        *b_gtr200x_cluster_id;   //!
   TBranch        *b_gtr200x_cluster_mid;   //!
   TBranch        *b_gtr200x_cluster_x;   //!
   TBranch        *b_gtr200x_cluster_gx;   //!
   TBranch        *b_gtr200x_cluster_gz;   //!
   TBranch        *b_gtr200x_cluster_adc;   //!
   TBranch        *b_gtr200x_cluster_t;   //!
   TBranch        *b_gtr200x_cluster_t2;   //!
   TBranch        *b_gtr200x_cluster_tx;   //!
   TBranch        *b_gtr200x_cluster_the;   //!
   TBranch        *b_gtr200x_cluster_nc;   //!
   TBranch        *b_gtr200x_cluster_gtx;   //!
   TBranch        *b_gtr200x_cluster_size;   //!
   TBranch        *b_n_gtr300x_clusters;   //!
   TBranch        *b_gtr300x_cluster_id;   //!
   TBranch        *b_gtr300x_cluster_mid;   //!
   TBranch        *b_gtr300x_cluster_x;   //!
   TBranch        *b_gtr300x_cluster_gx;   //!
   TBranch        *b_gtr300x_cluster_gz;   //!
   TBranch        *b_gtr300x_cluster_adc;   //!
   TBranch        *b_gtr300x_cluster_t;   //!
   TBranch        *b_gtr300x_cluster_t2;   //!
   TBranch        *b_gtr300x_cluster_tx;   //!
   TBranch        *b_gtr300x_cluster_the;   //!
   TBranch        *b_gtr300x_cluster_nc;   //!
   TBranch        *b_gtr300x_cluster_gtx;   //!
   TBranch        *b_gtr300x_cluster_size;   //!
   TBranch        *b_n_gtr100y_clusters;   //!
   TBranch        *b_gtr100y_cluster_id;   //!
   TBranch        *b_gtr100y_cluster_mid;   //!
   TBranch        *b_gtr100y_cluster_y;   //!
   TBranch        *b_gtr100y_cluster_adc;   //!
   TBranch        *b_gtr100y_cluster_t;   //!
   TBranch        *b_gtr100y_cluster_t2;   //!
   TBranch        *b_gtr100y_cluster_ty;   //!
   TBranch        *b_gtr100y_cluster_the;   //!
   TBranch        *b_gtr100y_cluster_nc;   //!
   TBranch        *b_gtr100y_cluster_size;   //!
   TBranch        *b_n_gtr100yb_clusters;   //!
   TBranch        *b_gtr100yb_cluster_id;   //!
   TBranch        *b_gtr100yb_cluster_mid;   //!
   TBranch        *b_gtr100yb_cluster_y;   //!
   TBranch        *b_gtr100yb_cluster_adc;   //!
   TBranch        *b_gtr100yb_cluster_t;   //!
   TBranch        *b_gtr100yb_cluster_t2;   //!
   TBranch        *b_gtr100yb_cluster_ty;   //!
   TBranch        *b_gtr100yb_cluster_the;   //!
   TBranch        *b_gtr100yb_cluster_nc;   //!
   TBranch        *b_gtr100yb_cluster_size;   //!
   TBranch        *b_n_gtr200y_clusters;   //!
   TBranch        *b_gtr200y_cluster_id;   //!
   TBranch        *b_gtr200y_cluster_mid;   //!
   TBranch        *b_gtr200y_cluster_y;   //!
   TBranch        *b_gtr200y_cluster_adc;   //!
   TBranch        *b_gtr200y_cluster_t;   //!
   TBranch        *b_gtr200y_cluster_t2;   //!
   TBranch        *b_gtr200y_cluster_ty;   //!
   TBranch        *b_gtr200y_cluster_the;   //!
   TBranch        *b_gtr200y_cluster_nc;   //!
   TBranch        *b_gtr200y_cluster_size;   //!
   TBranch        *b_n_gtr300y_clusters;   //!
   TBranch        *b_gtr300y_cluster_id;   //!
   TBranch        *b_gtr300y_cluster_mid;   //!
   TBranch        *b_gtr300y_cluster_y;   //!
   TBranch        *b_gtr300y_cluster_adc;   //!
   TBranch        *b_gtr300y_cluster_t;   //!
   TBranch        *b_gtr300y_cluster_t2;   //!
   TBranch        *b_gtr300y_cluster_ty;   //!
   TBranch        *b_gtr300y_cluster_the;   //!
   TBranch        *b_gtr300y_cluster_nc;   //!
   TBranch        *b_gtr300y_cluster_size;   //!
   TBranch        *b_n_hbd_clusters;   //!
   TBranch        *b_hbd_cluster_id;   //!
   TBranch        *b_hbd_cluster_mid;   //!
   TBranch        *b_hbd_cluster_x;   //!
   TBranch        *b_hbd_cluster_y;   //!
   TBranch        *b_hbd_cluster_gx;   //!
   TBranch        *b_hbd_cluster_gy;   //!
   TBranch        *b_hbd_cluster_gz;   //!
   TBranch        *b_hbd_cluster_adc;   //!
   TBranch        *b_hbd_cluster_max_cid;   //!
   TBranch        *b_hbd_cluster_t;   //!
   TBranch        *b_hbd_cluster_ftime;   //!
   TBranch        *b_hbd_cluster_tdiff;   //!
   TBranch        *b_hbd_cluster_size;   //!
   TBranch        *b_hbd_cluster_eprob;   //!
   TBranch        *b_hbd_cluster_cprob;   //!
   TBranch        *b_n_hbd_clusters_wotime;   //!
   TBranch        *b_hbd_cluster_wotime_id;   //!
   TBranch        *b_hbd_cluster_wotime_mid;   //!
   TBranch        *b_hbd_cluster_wotime_x;   //!
   TBranch        *b_hbd_cluster_wotime_y;   //!
   TBranch        *b_hbd_cluster_wotime_gx;   //!
   TBranch        *b_hbd_cluster_wotime_gy;   //!
   TBranch        *b_hbd_cluster_wotime_gz;   //!
   TBranch        *b_hbd_cluster_wotime_adc;   //!
   TBranch        *b_hbd_cluster_wotime_max_cid;   //!
   TBranch        *b_hbd_cluster_wotime_t;   //!
   TBranch        *b_hbd_cluster_wotime_ftime;   //!
   TBranch        *b_hbd_cluster_wotime_tdiff;   //!
   TBranch        *b_hbd_cluster_wotime_size;   //!
   TBranch        *b_hbd_cluster_wotime_eprob;   //!
   TBranch        *b_hbd_cluster_wotime_cprob;   //!
   TBranch        *b_n_lg_hits;   //!
   TBranch        *b_lg_hit_id;   //!
   TBranch        *b_lg_hit_mid;   //!
   TBranch        *b_lg_hit_cid;   //!
   TBranch        *b_lg_hit_x;   //!
   TBranch        *b_lg_hit_y;   //!
   TBranch        *b_lg_hit_z;   //!
   TBranch        *b_lg_hit_gx;   //!
   TBranch        *b_lg_hit_gy;   //!
   TBranch        *b_lg_hit_gz;   //!
   TBranch        *b_lg_hit_adc;   //!
   TBranch        *b_lg_hit_t;   //!
   TBranch        *b_lg_hit_wofit_adc;   //!
   TBranch        *b_lg_hit_wofit_t;   //!
   TBranch        *b_lg_hit_npeaks;   //!
   TBranch        *b_lg_hit_fflag;   //!
   TBranch        *b_n_lg_clusters;   //!
   TBranch        *b_lg_cluster_id;   //!
   TBranch        *b_lg_cluster_mid;   //!
   TBranch        *b_lg_cluster_max_cid;   //!
   TBranch        *b_lg_cluster_max_adc;   //!
   TBranch        *b_lg_cluster_x;   //!
   TBranch        *b_lg_cluster_y;   //!
   TBranch        *b_lg_cluster_z;   //!
   TBranch        *b_lg_cluster_gx;   //!
   TBranch        *b_lg_cluster_gy;   //!
   TBranch        *b_lg_cluster_gz;   //!
   TBranch        *b_lg_cluster_adc;   //!
   TBranch        *b_lg_cluster_t;   //!
   TBranch        *b_lg_cluster_tdiff;   //!
   TBranch        *b_lg_cluster_size;   //!
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
   TBranch        *b_trg_lg_hit_z;   //!
   TBranch        *b_trg_lg_hit_gx;   //!
   TBranch        *b_trg_lg_hit_gy;   //!
   TBranch        *b_trg_lg_hit_gz;   //!
   TBranch        *b_trg_lg_hit_t;   //!
   TBranch        *b_n_trg_tracks;   //!
   TBranch        *b_trg_track_n_gtr_hits;   //!
   TBranch        *b_trg_track_gtr_id;   //!
   TBranch        *b_trg_track_gtr_mid;   //!
   TBranch        *b_trg_track_gtr_cid;   //!
   TBranch        *b_trg_track_gtr_x;   //!
   TBranch        *b_trg_track_gtr_y;   //!
   TBranch        *b_trg_track_gtr_t;   //!
   TBranch        *b_trg_track_gtr_is_t_match;   //!
   TBranch        *b_trg_track_n_hbd_hits;   //!
   TBranch        *b_trg_track_hbd_id;   //!
   TBranch        *b_trg_track_hbd_mid;   //!
   TBranch        *b_trg_track_hbd_cid;   //!
   TBranch        *b_trg_track_hbd_x;   //!
   TBranch        *b_trg_track_hbd_y;   //!
   TBranch        *b_trg_track_hbd_t;   //!
   TBranch        *b_trg_track_hbd_is_t_match;   //!
   TBranch        *b_trg_track_lg_id;   //!
   TBranch        *b_trg_track_lg_mid;   //!
   TBranch        *b_trg_track_lg_cid;   //!
   TBranch        *b_trg_track_lg_x;   //!
   TBranch        *b_trg_track_lg_y;   //!
   TBranch        *b_trg_track_lg_t;   //!
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
   TBranch        *b_x_rough_fit_dist0;   //!
   TBranch        *b_x_rough_fit_dist1;   //!
   TBranch        *b_x_rough_fit_coef0;   //!
   TBranch        *b_x_rough_fit_coef1;   //!
   TBranch        *b_x_rough_fit_coef2;   //!
   TBranch        *b_rough_fit_n_hbds;   //!
   TBranch        *b_rough_fit_hbd_ids;   //!
   TBranch        *b_rough_fit_hbd_ress;   //!
   TBranch        *b_rough_fit_hbd_y_oks;   //!
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
   TBranch        *b_rk_hit_ssd_x;   //!
   TBranch        *b_rk_hit_ssd_gx;   //!
   TBranch        *b_rk_hit_ssd_gy;   //!
   TBranch        *b_rk_hit_ssd_gz;   //!
   TBranch        *b_rk_hit_ssd_adc;   //!
   TBranch        *b_rk_hit_ssd_t;   //!
   TBranch        *b_rk_hit_ssd_chi2;   //!
   TBranch        *b_rk_hit_gtr100_xid;   //!
   TBranch        *b_rk_hit_gtr100_yid;   //!
   TBranch        *b_rk_hit_gtr100_gx;   //!
   TBranch        *b_rk_hit_gtr100_gy;   //!
   TBranch        *b_rk_hit_gtr100_gz;   //!
   TBranch        *b_rk_hit_gtr100_xadc;   //!
   TBranch        *b_rk_hit_gtr100_yadc;   //!
   TBranch        *b_rk_hit_gtr100_xt;   //!
   TBranch        *b_rk_hit_gtr100_yt;   //!
   TBranch        *b_rk_hit_gtr100_xt2;   //!
   TBranch        *b_rk_hit_gtr100_yt2;   //!
   TBranch        *b_rk_hit_gtr100_tx2;   //!
   TBranch        *b_rk_hit_gtr100_ty;   //!
   TBranch        *b_rk_hit_gtr100_gtx;   //!
   TBranch        *b_rk_hit_gtr100_gty;   //!
   TBranch        *b_rk_hit_gtr100_gtz;   //!
   TBranch        *b_rk_hit_gtr100_gtx2;   //!
   TBranch        *b_rk_hit_gtr100_gty2;   //!
   TBranch        *b_rk_hit_gtr100_gtz2;   //!
   TBranch        *b_rk_hit_gtr100_nc;   //!
   TBranch        *b_rk_hit_gtr100_the;   //!
   TBranch        *b_rk_hit_gtr100_the2;   //!
   TBranch        *b_rk_hit_gtr200_xid;   //!
   TBranch        *b_rk_hit_gtr200_yid;   //!
   TBranch        *b_rk_hit_gtr200_gx;   //!
   TBranch        *b_rk_hit_gtr200_gy;   //!
   TBranch        *b_rk_hit_gtr200_gz;   //!
   TBranch        *b_rk_hit_gtr200_xadc;   //!
   TBranch        *b_rk_hit_gtr200_yadc;   //!
   TBranch        *b_rk_hit_gtr200_xt;   //!
   TBranch        *b_rk_hit_gtr200_yt;   //!
   TBranch        *b_rk_hit_gtr200_xt2;   //!
   TBranch        *b_rk_hit_gtr200_yt2;   //!
   TBranch        *b_rk_hit_gtr200_tx2;   //!
   TBranch        *b_rk_hit_gtr200_ty;   //!
   TBranch        *b_rk_hit_gtr200_gtx;   //!
   TBranch        *b_rk_hit_gtr200_gty;   //!
   TBranch        *b_rk_hit_gtr200_gtz;   //!
   TBranch        *b_rk_hit_gtr200_gtx2;   //!
   TBranch        *b_rk_hit_gtr200_gty2;   //!
   TBranch        *b_rk_hit_gtr200_gtz2;   //!
   TBranch        *b_rk_hit_gtr200_nc;   //!
   TBranch        *b_rk_hit_gtr200_the;   //!
   TBranch        *b_rk_hit_gtr200_the2;   //!
   TBranch        *b_rk_hit_gtr300_xid;   //!
   TBranch        *b_rk_hit_gtr300_yid;   //!
   TBranch        *b_rk_hit_gtr300_gx;   //!
   TBranch        *b_rk_hit_gtr300_gy;   //!
   TBranch        *b_rk_hit_gtr300_gz;   //!
   TBranch        *b_rk_hit_gtr300_xadc;   //!
   TBranch        *b_rk_hit_gtr300_yadc;   //!
   TBranch        *b_rk_hit_gtr300_xt;   //!
   TBranch        *b_rk_hit_gtr300_yt;   //!
   TBranch        *b_rk_hit_gtr300_xt2;   //!
   TBranch        *b_rk_hit_gtr300_yt2;   //!
   TBranch        *b_rk_hit_gtr300_tx2;   //!
   TBranch        *b_rk_hit_gtr300_ty;   //!
   TBranch        *b_rk_hit_gtr300_gtx;   //!
   TBranch        *b_rk_hit_gtr300_gty;   //!
   TBranch        *b_rk_hit_gtr300_gtz;   //!
   TBranch        *b_rk_hit_gtr300_gtx2;   //!
   TBranch        *b_rk_hit_gtr300_gty2;   //!
   TBranch        *b_rk_hit_gtr300_gtz2;   //!
   TBranch        *b_rk_hit_gtr300_nc;   //!
   TBranch        *b_rk_hit_gtr300_the;   //!
   TBranch        *b_rk_hit_gtr300_the2;   //!
   TBranch        *b_rk_fit_init_mom_gx;   //!
   TBranch        *b_rk_fit_init_mom_gy;   //!
   TBranch        *b_rk_fit_init_mom_gz;   //!
   TBranch        *b_rk_fit_init_pos_gx;   //!
   TBranch        *b_rk_fit_init_pos_gy;   //!
   TBranch        *b_rk_fit_init_pos_gz;   //!
   TBranch        *b_rk_fit_ssd_mid;   //!
   TBranch        *b_rk_fit_ssd_x;   //!
   TBranch        *b_rk_fit_ssd_y;   //!
   TBranch        *b_rk_fit_ssd_gx;   //!
   TBranch        *b_rk_fit_ssd_gy;   //!
   TBranch        *b_rk_fit_ssd_gz;   //!
   TBranch        *b_rk_fit_ssd_mom_x;   //!
   TBranch        *b_rk_fit_ssd_mom_y;   //!
   TBranch        *b_rk_fit_ssd_mom_z;   //!
   TBranch        *b_rk_fit_ssd_mom_gx;   //!
   TBranch        *b_rk_fit_ssd_mom_gy;   //!
   TBranch        *b_rk_fit_ssd_mom_gz;   //!
   TBranch        *b_rk_fit_gtr100_mid;   //!
   TBranch        *b_rk_fit_gtr100_x;   //!
   TBranch        *b_rk_fit_gtr100_y;   //!
   TBranch        *b_rk_fit_gtr100_gx;   //!
   TBranch        *b_rk_fit_gtr100_gy;   //!
   TBranch        *b_rk_fit_gtr100_gz;   //!
   TBranch        *b_rk_fit_gtr100_mom_x;   //!
   TBranch        *b_rk_fit_gtr100_mom_y;   //!
   TBranch        *b_rk_fit_gtr100_mom_z;   //!
   TBranch        *b_rk_fit_gtr100_mom_gx;   //!
   TBranch        *b_rk_fit_gtr100_mom_gy;   //!
   TBranch        *b_rk_fit_gtr100_mom_gz;   //!
   TBranch        *b_rk_fit_gtr200_mid;   //!
   TBranch        *b_rk_fit_gtr200_x;   //!
   TBranch        *b_rk_fit_gtr200_y;   //!
   TBranch        *b_rk_fit_gtr200_gx;   //!
   TBranch        *b_rk_fit_gtr200_gy;   //!
   TBranch        *b_rk_fit_gtr200_gz;   //!
   TBranch        *b_rk_fit_gtr200_mom_x;   //!
   TBranch        *b_rk_fit_gtr200_mom_y;   //!
   TBranch        *b_rk_fit_gtr200_mom_z;   //!
   TBranch        *b_rk_fit_gtr200_mom_gx;   //!
   TBranch        *b_rk_fit_gtr200_mom_gy;   //!
   TBranch        *b_rk_fit_gtr200_mom_gz;   //!
   TBranch        *b_rk_fit_gtr300_mid;   //!
   TBranch        *b_rk_fit_gtr300_x;   //!
   TBranch        *b_rk_fit_gtr300_y;   //!
   TBranch        *b_rk_fit_gtr300_gx;   //!
   TBranch        *b_rk_fit_gtr300_gy;   //!
   TBranch        *b_rk_fit_gtr300_gz;   //!
   TBranch        *b_rk_fit_gtr300_mom_x;   //!
   TBranch        *b_rk_fit_gtr300_mom_y;   //!
   TBranch        *b_rk_fit_gtr300_mom_z;   //!
   TBranch        *b_rk_fit_gtr300_mom_gx;   //!
   TBranch        *b_rk_fit_gtr300_mom_gy;   //!
   TBranch        *b_rk_fit_gtr300_mom_gz;   //!
   TBranch        *b_rk_fit_hbd_mid;   //!
   TBranch        *b_rk_fit_hbd_x;   //!
   TBranch        *b_rk_fit_hbd_y;   //!
   TBranch        *b_rk_fit_hbd_gx;   //!
   TBranch        *b_rk_fit_hbd_gy;   //!
   TBranch        *b_rk_fit_hbd_gz;   //!
   TBranch        *b_rk_fit_hbd_mom_x;   //!
   TBranch        *b_rk_fit_hbd_mom_y;   //!
   TBranch        *b_rk_fit_hbd_mom_z;   //!
   TBranch        *b_rk_fit_hbd_mom_gx;   //!
   TBranch        *b_rk_fit_hbd_mom_gy;   //!
   TBranch        *b_rk_fit_hbd_mom_gz;   //!
   TBranch        *b_rk_fit_lg_c_mid;   //!
   TBranch        *b_rk_fit_lg_c_x;   //!
   TBranch        *b_rk_fit_lg_c_y;   //!
   TBranch        *b_rk_fit_lg_c_gx;   //!
   TBranch        *b_rk_fit_lg_c_gy;   //!
   TBranch        *b_rk_fit_lg_c_gz;   //!
   TBranch        *b_rk_fit_lg_c_mom_x;   //!
   TBranch        *b_rk_fit_lg_c_mom_y;   //!
   TBranch        *b_rk_fit_lg_c_mom_z;   //!
   TBranch        *b_rk_fit_lg_c_mom_gx;   //!
   TBranch        *b_rk_fit_lg_c_mom_gy;   //!
   TBranch        *b_rk_fit_lg_c_mom_gz;   //!
   TBranch        *b_rk_fit_lg_b_mid;   //!
   TBranch        *b_rk_fit_lg_b_x;   //!
   TBranch        *b_rk_fit_lg_b_y;   //!
   TBranch        *b_rk_fit_lg_b_gx;   //!
   TBranch        *b_rk_fit_lg_b_gy;   //!
   TBranch        *b_rk_fit_lg_b_gz;   //!
   TBranch        *b_rk_fit_lg_b_mom_x;   //!
   TBranch        *b_rk_fit_lg_b_mom_y;   //!
   TBranch        *b_rk_fit_lg_b_mom_z;   //!
   TBranch        *b_rk_fit_lg_b_mom_gx;   //!
   TBranch        *b_rk_fit_lg_b_mom_gy;   //!
   TBranch        *b_rk_fit_lg_b_mom_gz;   //!
   TBranch        *b_rk_fit_lg_a_mid;   //!
   TBranch        *b_rk_fit_lg_a_x;   //!
   TBranch        *b_rk_fit_lg_a_y;   //!
   TBranch        *b_rk_fit_lg_a_gx;   //!
   TBranch        *b_rk_fit_lg_a_gy;   //!
   TBranch        *b_rk_fit_lg_a_gz;   //!
   TBranch        *b_rk_fit_lg_a_mom_x;   //!
   TBranch        *b_rk_fit_lg_a_mom_y;   //!
   TBranch        *b_rk_fit_lg_a_mom_z;   //!
   TBranch        *b_rk_fit_lg_a_mom_gx;   //!
   TBranch        *b_rk_fit_lg_a_mom_gy;   //!
   TBranch        *b_rk_fit_lg_a_mom_gz;   //!
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
   TBranch        *b_rk_res_gtr100_tx;   //!
   TBranch        *b_rk_res_gtr100_ty;   //!
   TBranch        *b_rk_res_gtr200_tx;   //!
   TBranch        *b_rk_res_gtr200_ty;   //!
   TBranch        *b_rk_res_gtr300_tx;   //!
   TBranch        *b_rk_res_gtr300_ty;   //!
   TBranch        *b_rk_res_gtr100_tx2;   //!
   TBranch        *b_rk_res_gtr200_tx2;   //!
   TBranch        *b_rk_res_gtr300_tx2;   //!
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
   TBranch        *b_rk_proj_is_search;   //!
   TBranch        *b_rk_proj_n_hbd;   //!
   TBranch        *b_rk_proj_hbd_id;   //!
   TBranch        *b_rk_proj_hbd_mid;   //!
   TBranch        *b_rk_proj_hbd_x;   //!
   TBranch        *b_rk_proj_hbd_y;   //!
   TBranch        *b_rk_proj_hbd_adc;   //!
   TBranch        *b_rk_proj_hbd_t;   //!
   TBranch        *b_rk_proj_hbd_ftime;   //!
   TBranch        *b_rk_proj_hbd_tdiff;   //!
   TBranch        *b_rk_proj_hbd_size;   //!
   TBranch        *b_rk_proj_hbd_eprob;   //!
   TBranch        *b_rk_proj_hbd_cprob;   //!
   TBranch        *b_rk_proj_n_lg;   //!
   TBranch        *b_rk_proj_lg_id;   //!
   TBranch        *b_rk_proj_lg_mid;   //!
   TBranch        *b_rk_proj_lg_cid;   //!
   TBranch        *b_rk_proj_lg_x;   //!
   TBranch        *b_rk_proj_lg_y;   //!
   TBranch        *b_rk_proj_lg_adc;   //!
   TBranch        *b_rk_proj_lg_t;   //!
   TBranch        *b_rk_proj_lg_npeaks;   //!
   TBranch        *b_rk_proj_lg_fflag;   //!
   TBranch        *b_rk_pair_minus_track_id;   //!
   TBranch        *b_rk_pair_minus_gtr300_mid;   //!
   TBranch        *b_rk_pair_minus_chi_square;   //!
   TBranch        *b_rk_pair_minus_mom_gx;   //!
   TBranch        *b_rk_pair_minus_mom_gy;   //!
   TBranch        *b_rk_pair_minus_mom_gz;   //!
   TBranch        *b_rk_pair_minus_ssd_t;   //!
   TBranch        *b_rk_pair_minus_lg_t;   //!
   TBranch        *b_rk_pair_plus_track_id;   //!
   TBranch        *b_rk_pair_plus_gtr300_mid;   //!
   TBranch        *b_rk_pair_plus_chi_square;   //!
   TBranch        *b_rk_pair_plus_mom_gx;   //!
   TBranch        *b_rk_pair_plus_mom_gy;   //!
   TBranch        *b_rk_pair_plus_mom_gz;   //!
   TBranch        *b_rk_pair_plus_ssd_t;   //!
   TBranch        *b_rk_pair_plus_lg_t;   //!
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
   TBranch        *b_rk_hit_gtr100_cogx;
   TBranch        *b_rk_hit_gtr200_cogx;
   TBranch        *b_rk_hit_gtr300_cogx;
   TBranch        *b_rk_hit_gtr100_cogy;
   TBranch        *b_rk_hit_gtr200_cogy;
   TBranch        *b_rk_hit_gtr300_cogy;
	
 

	E16DSTN_PosCorrection(TTree *tree=0, const char* out_file = 0, E16ANA_GeometryV2 *_geom=nullptr, E16ANA_StraightMultiTrack *_fitter=nullptr);
	virtual ~E16DSTN_PosCorrection();
//	virtual Int_t Cut(Long64_t entry);
	virtual Int_t GetEntry(Long64_t entry);
	virtual Long64_t LoadTree(Long64_t entry);
	virtual void Init(TTree *tree, const char *out_file);
	bool CalcRoughMomentumV2();
	virtual Bool_t Notify();
	virtual void Show(Long64_t enery = -1);
	void   AddRecord(std::vector<int> &ids);
	TFile *FileOut() {return fout;}
	void SetRemovedLayer(int i) {removed_layer = i;}
	
	
   void PosCoLoop(TTree *tree, int print_cycle, int max_event, bool vertex_xy_fix_flag, bool py_fix_flag,bool  vetex_z_fix_flag, int analysisSW);
	void UpdateFitResult(E16ANA_StraightMultiTrack *fitter, const int tid);
	bool HasUsedCluster(const std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips> &cids);
	bool HasUsedCluster(const std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips-1 > &cids);
	void SetIsWire(bool i) {
	isWire = i;}
	void ResizeTmpVectors();
	void ChiSqSort(std::vector<int> &ids, std::vector<int> &outids);
	void ChiSqSort(std::vector<int> &outids);
	void ClearUsedClusterIDs();
	void SetTracks(std::vector<int> &ids);
	void SetTracks(std::vector<int> &ids, std::vector<int> &out);
	bool IsGoodTrack(int i);
	bool IsComingFromTarget(int i);
	TVector3 CorrectedLocalPos(const int tid, const int mid,  const int l);
	void AddTrackCorrectedHit(E16ANA_StraightMultiTrack *fitter,const int tid);
	void CorrectionFit(std::vector<int> &ids);	
	void SetGeom(E16ANA_GeometryV2 *_geom){geom = _geom;}
	void SetFitter(E16ANA_StraightMultiTrack *_fitter){fitter = _fitter;}
	void RemoveDuplicatedHits(std::vector<int> &ids, std::vector<int> &oids);

	struct FitResult {
 		int set_flag;
		int layer_order;
      int module_id;
      TVector3 local_pos;
      TVector3 local_mom;
      TVector3 global_pos;
      TVector3 global_mom;
  //    TVector3 local_sigma;
      TVector3 residual_pos;
      TVector3 residual_post;
      TVector3 residual_post2;
      void Clear() {
        set_flag = 0;
        layer_order = E16DST_DST1Constant::kInvalidValue;
        module_id = E16DST_DST1Constant::kInvalidValue;
        local_pos = E16DST_DST1Constant::kInvalidVector;
        local_mom = E16DST_DST1Constant::kInvalidVector;
        global_pos = E16DST_DST1Constant::kInvalidVector;
        global_mom = E16DST_DST1Constant::kInvalidVector;
        residual_pos = E16DST_DST1Constant::kInvalidVector;
        residual_post = E16DST_DST1Constant::kInvalidVector;
        residual_post2 = E16DST_DST1Constant::kInvalidVector;
      }
      void Set(int _layer_order, int _module_id, TVector3 _local_pos, TVector3  _local_mom, TVector3 _global_pos, TVector3 _global_mom, TVector3 _residual_pos) {
        set_flag = 1;
        layer_order = _layer_order;
        module_id = _module_id;
        local_pos = _local_pos;
        local_mom = _local_mom;
        global_pos = _global_pos;
        global_mom = _global_mom;
        residual_pos = _residual_pos;
      }
      void SetT(TVector3 _residual_pos) { residual_post  = _residual_pos;}
      void SetT2(TVector3 _residual_pos){ residual_post2 = _residual_pos;}
      void SetC(TVector3 _residual_pos) { residual_pos   = _residual_pos;}
	};
	
	TFile *fout;   //= new TFile (out_file, "recreate");
	TTree *outtree;// = new TTree("outtree", "outtree");

   Int_t           out_run_id;
   Int_t           out_event_id;
   Int_t           out_spill_id;
   ULong64_t       out_timestamp_in_spill;
   Int_t           out_trigger_fine_time;
   Int_t           out_n_fill;
   Int_t           out_n_ssd_hits;
   std::vector<int>     out_ssd_hit_id;
   std::vector<int>     out_ssd_hit_mid;
   std::vector<int>     out_ssd_hit_cid;
   std::vector<double>  out_ssd_hit_x;
   std::vector<double>  out_ssd_hit_gx;
   std::vector<double>  out_ssd_hit_gz;
   std::vector<double>  out_ssd_hit_t;
   std::vector<float>   out_ssd_hit_adc;
   Int_t           out_n_gtr100x_hits;
   std::vector<int>     out_gtr100x_hit_id;
   std::vector<int>     out_gtr100x_hit_mid;
   std::vector<int>     out_gtr100x_hit_cid;
   std::vector<double>  out_gtr100x_hit_x;
   std::vector<double>  out_gtr100x_hit_tx;
   std::vector<double>  out_gtr100x_hit_gx;
   std::vector<double>  out_gtr100x_hit_gz;
   std::vector<double>  out_gtr100x_hit_t;
   std::vector<float>   out_gtr100x_hit_adc;
   Int_t           out_n_gtr200x_hits;
   std::vector<int>     out_gtr200x_hit_id;
   std::vector<int>     out_gtr200x_hit_mid;
   std::vector<int>     out_gtr200x_hit_cid;
   std::vector<double>  out_gtr200x_hit_x;
   std::vector<double>  out_gtr200x_hit_tx;
   std::vector<double>  out_gtr200x_hit_gx;
   std::vector<double>  out_gtr200x_hit_gz;
   std::vector<double>  out_gtr200x_hit_t;
   std::vector<float>   out_gtr200x_hit_adc;
   Int_t           out_n_gtr300x_hits;
   std::vector<int>     out_gtr300x_hit_id;
   std::vector<int>     out_gtr300x_hit_mid;
   std::vector<int>     out_gtr300x_hit_cid;
   std::vector<double>  out_gtr300x_hit_x;
   std::vector<double>  out_gtr300x_hit_tx;
   std::vector<double>  out_gtr300x_hit_gx;
   std::vector<double>  out_gtr300x_hit_gz;
   std::vector<double>  out_gtr300x_hit_t;
   std::vector<float>   out_gtr300x_hit_adc;
   Int_t           out_n_gtr100y_hits;
   std::vector<int>     out_gtr100y_hit_id;
   std::vector<int>     out_gtr100y_hit_mid;
   std::vector<int>     out_gtr100y_hit_cid;
   std::vector<double>  out_gtr100y_hit_y;
   std::vector<double>  out_gtr100y_hit_ty;
   std::vector<double>  out_gtr100y_hit_t;
   std::vector<float>   out_gtr100y_hit_adc;
   Int_t           out_n_gtr100yb_hits;
   std::vector<int>     out_gtr100yb_hit_id;
   std::vector<int>     out_gtr100yb_hit_mid;
   std::vector<int>     out_gtr100yb_hit_cid;
   std::vector<double>  out_gtr100yb_hit_y;
   std::vector<double>  out_gtr100yb_hit_ty;
   std::vector<double>  out_gtr100yb_hit_t;
   std::vector<float>   out_gtr100yb_hit_adc;
   Int_t                out_n_gtr200y_hits;
   std::vector<int>     out_gtr200y_hit_id;
   std::vector<int>     out_gtr200y_hit_mid;
   std::vector<int>     out_gtr200y_hit_cid;
   std::vector<double>  out_gtr200y_hit_y;
   std::vector<double>  out_gtr200y_hit_ty;
   std::vector<double>  out_gtr200y_hit_t;
   std::vector<float>   out_gtr200y_hit_adc;

   Int_t                out_n_gtr300y_hits;
   std::vector<int>     out_gtr300y_hit_id;
   std::vector<int>     out_gtr300y_hit_mid;
   std::vector<int>     out_gtr300y_hit_cid;
   std::vector<double>  out_gtr300y_hit_y;
   std::vector<double>  out_gtr300y_hit_ty;
   std::vector<double>  out_gtr300y_hit_t;
   std::vector<float>   out_gtr300y_hit_adc;
   Int_t                out_n_hbd_hits;
   std::vector<int>     out_hbd_hit_id;
   std::vector<int>     out_hbd_hit_mid;
   std::vector<int>     out_hbd_hit_cid;
   std::vector<double>  out_hbd_hit_x;
   std::vector<double>  out_hbd_hit_y;
   std::vector<double>  out_hbd_hit_gx;
   std::vector<double>  out_hbd_hit_gy;
   std::vector<double>  out_hbd_hit_gz;
   std::vector<double>  out_hbd_hit_t;
   std::vector<float>   out_hbd_hit_adc;
   Int_t                out_n_ssd_clusters;
   std::vector<int>     out_ssd_cluster_id;
   std::vector<int>     out_ssd_cluster_mid;
   std::vector<double>  out_ssd_cluster_x;
   std::vector<double>  out_ssd_cluster_gx;
   std::vector<double>  out_ssd_cluster_gz;
   std::vector<float>   out_ssd_cluster_adc;
   std::vector<double>  out_ssd_cluster_t;
   std::vector<int>     out_ssd_cluster_size;
   std::vector<double>  out_ssd_cluster_fit_x;
   std::vector<double>  out_ssd_cluster_fit_t;
   std::vector<double>  out_ssd_cluster_fit_adc;
   std::vector<double>  out_ssd_cluster_fit_chi2;
   Int_t                out_n_gtr100x_clusters;
   std::vector<int>     out_gtr100x_cluster_id;
   std::vector<int>     out_gtr100x_cluster_mid;
   std::vector<double>  out_gtr100x_cluster_x;
   std::vector<double>  out_gtr100x_cluster_gx;
   std::vector<double>  out_gtr100x_cluster_gz;
   std::vector<float>   out_gtr100x_cluster_adc;
   std::vector<double>  out_gtr100x_cluster_t;
   std::vector<double>  out_gtr100x_cluster_t2;
   std::vector<double>  out_gtr100x_cluster_tx;
   std::vector<double>  out_gtr100x_cluster_the;
   std::vector<double>  out_gtr100x_cluster_gtx;
   std::vector<int>     out_gtr100x_cluster_nc;
   std::vector<int>     out_gtr100x_cluster_size;
   Int_t                out_n_gtr200x_clusters;
   std::vector<int>     out_gtr200x_cluster_id;
   std::vector<int>     out_gtr200x_cluster_mid;
   std::vector<double>  out_gtr200x_cluster_x;
   std::vector<double>  out_gtr200x_cluster_gx;
   std::vector<double>  out_gtr200x_cluster_gz;
   std::vector<float>   out_gtr200x_cluster_adc;
   std::vector<double>  out_gtr200x_cluster_t;
   std::vector<double>  out_gtr200x_cluster_t2;
   std::vector<double>  out_gtr200x_cluster_tx;
   std::vector<double>  out_gtr200x_cluster_the;
   std::vector<int>     out_gtr200x_cluster_nc;
   std::vector<double>  out_gtr200x_cluster_gtx;
   std::vector<int>     out_gtr200x_cluster_size;
   Int_t                out_n_gtr300x_clusters;
   std::vector<int>     out_gtr300x_cluster_id;
   std::vector<int>     out_gtr300x_cluster_mid;
   std::vector<double>  out_gtr300x_cluster_x;
   std::vector<double>  out_gtr300x_cluster_gx;
   std::vector<double>  out_gtr300x_cluster_gz;
   std::vector<float>   out_gtr300x_cluster_adc;
   std::vector<double>  out_gtr300x_cluster_t;
   std::vector<double>  out_gtr300x_cluster_t2;
   std::vector<double>  out_gtr300x_cluster_tx;
   std::vector<double>  out_gtr300x_cluster_the;
   std::vector<int>     out_gtr300x_cluster_nc;
   std::vector<double>  out_gtr300x_cluster_gtx;
   std::vector<int>     out_gtr300x_cluster_size;
   Int_t                out_n_gtr100y_clusters;
   std::vector<int>     out_gtr100y_cluster_id;
   std::vector<int>     out_gtr100y_cluster_mid;
   std::vector<double>  out_gtr100y_cluster_y;
   std::vector<float>   out_gtr100y_cluster_adc;
   std::vector<double>  out_gtr100y_cluster_t;
   std::vector<double>  out_gtr100y_cluster_t2;
   std::vector<double>  out_gtr100y_cluster_ty;
   std::vector<double>  out_gtr100y_cluster_the;
   std::vector<int>     out_gtr100y_cluster_nc;
   std::vector<int>     out_gtr100y_cluster_size;
   Int_t                out_n_gtr100yb_clusters;
   std::vector<int>     out_gtr100yb_cluster_id;
   std::vector<int>     out_gtr100yb_cluster_mid;
   std::vector<double>  out_gtr100yb_cluster_y;
   std::vector<float>   out_gtr100yb_cluster_adc;
   std::vector<double>  out_gtr100yb_cluster_t;
   std::vector<double>  out_gtr100yb_cluster_t2;
   std::vector<double>  out_gtr100yb_cluster_ty;
   std::vector<double>  out_gtr100yb_cluster_the;
   std::vector<int>     out_gtr100yb_cluster_nc;
   std::vector<int>     out_gtr100yb_cluster_size;
   Int_t                out_n_gtr200y_clusters;
   std::vector<int>     out_gtr200y_cluster_id;
   std::vector<int>     out_gtr200y_cluster_mid;
   std::vector<double>  out_gtr200y_cluster_y;
   std::vector<float>   out_gtr200y_cluster_adc;
   std::vector<double>  out_gtr200y_cluster_t;
   std::vector<double>  out_gtr200y_cluster_t2;
   std::vector<double>  out_gtr200y_cluster_ty;
   std::vector<double>  out_gtr200y_cluster_the;
   std::vector<int>     out_gtr200y_cluster_nc;
   std::vector<int>     out_gtr200y_cluster_size;
   Int_t                out_n_gtr300y_clusters;
   std::vector<int>     out_gtr300y_cluster_id;
   std::vector<int>     out_gtr300y_cluster_mid;
   std::vector<double>  out_gtr300y_cluster_y;
   std::vector<float>   out_gtr300y_cluster_adc;
   std::vector<double>  out_gtr300y_cluster_t;
   std::vector<double>  out_gtr300y_cluster_t2;
   std::vector<double>  out_gtr300y_cluster_ty;
   std::vector<double>  out_gtr300y_cluster_the;
   std::vector<int>     out_gtr300y_cluster_nc;
   std::vector<int>     out_gtr300y_cluster_size;
   Int_t                out_n_hbd_clusters;
   std::vector<int>     out_hbd_cluster_id;
   std::vector<int>     out_hbd_cluster_mid;
   std::vector<double>  out_hbd_cluster_x;
   std::vector<double>  out_hbd_cluster_y;
   std::vector<double>  out_hbd_cluster_gx;
   std::vector<double>  out_hbd_cluster_gy;
   std::vector<double>  out_hbd_cluster_gz;
   std::vector<float>   out_hbd_cluster_adc;
   std::vector<int>     out_hbd_cluster_max_cid;
   std::vector<double>  out_hbd_cluster_t;
   std::vector<float>   out_hbd_cluster_ftime;
   std::vector<float>   out_hbd_cluster_tdiff;
   std::vector<int>     out_hbd_cluster_size;
   std::vector<float>   out_hbd_cluster_eprob;
   std::vector<float>   out_hbd_cluster_cprob;
   Int_t                out_n_hbd_clusters_wotime;
   std::vector<int>     out_hbd_cluster_wotime_id;
   std::vector<int>     out_hbd_cluster_wotime_mid;
   std::vector<double>  out_hbd_cluster_wotime_x;
   std::vector<double>  out_hbd_cluster_wotime_y;
   std::vector<double>  out_hbd_cluster_wotime_gx;
   std::vector<double>  out_hbd_cluster_wotime_gy;
   std::vector<double>  out_hbd_cluster_wotime_gz;
   std::vector<float>   out_hbd_cluster_wotime_adc;
   std::vector<int>     out_hbd_cluster_wotime_max_cid;
   std::vector<double>  out_hbd_cluster_wotime_t;
   std::vector<float>   out_hbd_cluster_wotime_ftime;
   std::vector<float>   out_hbd_cluster_wotime_tdiff;
   std::vector<int>     out_hbd_cluster_wotime_size;
   std::vector<float>   out_hbd_cluster_wotime_eprob;
   std::vector<float>   out_hbd_cluster_wotime_cprob;
   Int_t                out_n_lg_hits;
   std::vector<int>     out_lg_hit_id;
   std::vector<int>     out_lg_hit_mid;
   std::vector<int>     out_lg_hit_cid;
   std::vector<double>  out_lg_hit_x;
   std::vector<double>  out_lg_hit_y;
   std::vector<double>  out_lg_hit_z;
   std::vector<double>  out_lg_hit_gx;
   std::vector<double>  out_lg_hit_gy;
   std::vector<double>  out_lg_hit_gz;
   std::vector<float>   out_lg_hit_adc;
   std::vector<float>   out_lg_hit_t;
   std::vector<float>   out_lg_hit_wofit_adc;
   std::vector<float>   out_lg_hit_wofit_t;
   std::vector<int>     out_lg_hit_npeaks;
   std::vector<int>     out_lg_hit_fflag;
   Int_t                out_n_lg_clusters;
   std::vector<int>     out_lg_cluster_id;
   std::vector<int>     out_lg_cluster_mid;
   std::vector<int>     out_lg_cluster_max_cid;
   std::vector<int>     out_lg_cluster_max_adc;
   std::vector<double>  out_lg_cluster_x;
   std::vector<double>  out_lg_cluster_y;
   std::vector<double>  out_lg_cluster_z;
   std::vector<double>  out_lg_cluster_gx;
   std::vector<double>  out_lg_cluster_gy;
   std::vector<double>  out_lg_cluster_gz;
   std::vector<float>   out_lg_cluster_adc;
   std::vector<float>   out_lg_cluster_t;
   std::vector<float>   out_lg_cluster_tdiff;
   std::vector<int>     out_lg_cluster_size;
   Int_t                out_n_trg_gtr_hits;
   std::vector<int>     out_trg_gtr_hit_id;
   std::vector<int>     out_trg_gtr_hit_mid;
   std::vector<int>     out_trg_gtr_hit_cid;
   std::vector<double>  out_trg_gtr_hit_x;
   std::vector<double>  out_trg_gtr_hit_y;
   std::vector<double>  out_trg_gtr_hit_gx;
   std::vector<double>  out_trg_gtr_hit_gy;
   std::vector<double>  out_trg_gtr_hit_gz;
   std::vector<float>   out_trg_gtr_hit_t;
   Int_t                out_n_trg_hbd_hits;
   std::vector<int>     out_trg_hbd_hit_id;
   std::vector<int>     out_trg_hbd_hit_mid;
   std::vector<int>     out_trg_hbd_hit_cid;
   std::vector<double>  out_trg_hbd_hit_x;
   std::vector<double>  out_trg_hbd_hit_y;
   std::vector<double>  out_trg_hbd_hit_gx;
   std::vector<double>  out_trg_hbd_hit_gy;
   std::vector<double>  out_trg_hbd_hit_gz;
   std::vector<float>   out_trg_hbd_hit_t;
   Int_t                out_n_trg_lg_hits;
   std::vector<int>     out_trg_lg_hit_id;
   std::vector<int>     out_trg_lg_hit_mid;
   std::vector<int>     out_trg_lg_hit_cid;
   std::vector<double>  out_trg_lg_hit_x;
   std::vector<double>  out_trg_lg_hit_y;
   std::vector<double>  out_trg_lg_hit_z;
   std::vector<double>  out_trg_lg_hit_gx;
   std::vector<double>  out_trg_lg_hit_gy;
   std::vector<double>  out_trg_lg_hit_gz;
   std::vector<float>   out_trg_lg_hit_t;
   Int_t                out_n_trg_tracks;
   std::vector<int>     out_trg_track_n_gtr_hits;
   std::vector<std::vector<double> > out_trg_track_gtr_id;
   std::vector<std::vector<double> > out_trg_track_gtr_mid;
   std::vector<std::vector<double> > out_trg_track_gtr_cid;
   std::vector<std::vector<double> > out_trg_track_gtr_x;
   std::vector<std::vector<double> > out_trg_track_gtr_y;
   std::vector<std::vector<double> > out_trg_track_gtr_t;
   std::vector<std::vector<double> > out_trg_track_gtr_is_t_match;
   std::vector<int>                  out_trg_track_n_hbd_hits;
   std::vector<std::vector<double> > out_trg_track_hbd_id;
   std::vector<std::vector<double> > out_trg_track_hbd_mid;
   std::vector<std::vector<double> > out_trg_track_hbd_cid;
   std::vector<std::vector<double> > out_trg_track_hbd_x;
   std::vector<std::vector<double> > out_trg_track_hbd_y;
   std::vector<std::vector<double> > out_trg_track_hbd_t;
   std::vector<std::vector<double> > out_trg_track_hbd_is_t_match;
   std::vector<int>     out_trg_track_lg_id;
   std::vector<int>     out_trg_track_lg_mid;
   std::vector<int>     out_trg_track_lg_cid;
   std::vector<double>  out_trg_track_lg_x;
   std::vector<double>  out_trg_track_lg_y;
   std::vector<float>   out_trg_track_lg_t;
   Int_t                out_n_x_cands;
   Int_t                out_n_y_cands;
   Int_t                out_n_cands;
   Int_t                out_n_selected;
   Int_t                out_n_pairs;
   Int_t                out_n_refit_pairs;
   std::vector<int>     out_track_id;
   std::vector<bool>    out_has_e_hbd_cluster;
   std::vector<bool>    out_has_e_lg_hit;
   std::vector<bool>    out_is_large_residual;
   std::vector<bool>    out_is_near_target;
   std::vector<bool>    out_is_cluster_used;
   std::vector<bool>    out_is_selected;
   std::vector<double>  out_x_rough_fit_chi_square;
   std::vector<double>  out_x_rough_fit_dist0;
   std::vector<double>  out_x_rough_fit_dist1;
   std::vector<double>  out_x_rough_fit_coef0;
   std::vector<double>  out_x_rough_fit_coef1;
   std::vector<double>  out_x_rough_fit_coef2;
   std::vector<int>     out_rough_fit_n_hbds;
   std::vector<std::vector<double> > out_rough_fit_hbd_ids;
   std::vector<std::vector<double> > out_rough_fit_hbd_ress;
   std::vector<std::vector<double> > out_rough_fit_hbd_y_oks;
   std::vector<double>  out_y_rough_fit_chi_square;
   std::vector<double>  out_y_rough_fit_coef0;
   std::vector<double>  out_y_rough_fit_coef1;
   std::vector<double>  out_chi_square;
   std::vector<int>     out_n_steps;
   std::vector<int>     out_n_calls;
   std::vector<int>     out_rk_charge;
   std::vector<double>  out_rk_hit_init_mom_gx;
   std::vector<double>  out_rk_hit_init_mom_gy;
   std::vector<double>  out_rk_hit_init_mom_gz;
   std::vector<double>  out_rk_hit_init_pos_gx;
   std::vector<double>  out_rk_hit_init_pos_gy;
   std::vector<double>  out_rk_hit_init_pos_gz;
   std::vector<int>     out_rk_hit_ssd_id;
   std::vector<double>  out_rk_hit_ssd_x;
   std::vector<double>  out_rk_hit_ssd_gx;
   std::vector<double>  out_rk_hit_ssd_gy;
   std::vector<double>  out_rk_hit_ssd_gz;
   std::vector<float>   out_rk_hit_ssd_adc;
   std::vector<float>   out_rk_hit_ssd_t;
   std::vector<double>  out_rk_hit_ssd_chi2;
   std::vector<int>     out_rk_hit_gtr100_xid;
   std::vector<int>     out_rk_hit_gtr100_yid;
   std::vector<double>  out_rk_hit_gtr100_gx;
   std::vector<double>  out_rk_hit_gtr100_gy;
   std::vector<double>  out_rk_hit_gtr100_gz;
   std::vector<float>   out_rk_hit_gtr100_xadc;
   std::vector<float>   out_rk_hit_gtr100_yadc;
   std::vector<float>   out_rk_hit_gtr100_xt;
   std::vector<float>   out_rk_hit_gtr100_yt;
   std::vector<float>   out_rk_hit_gtr100_xt2;
   std::vector<float>   out_rk_hit_gtr100_yt2;
   std::vector<double>  out_rk_hit_gtr100_tx2;
   std::vector<double>  out_rk_hit_gtr100_ty;
   std::vector<double>  out_rk_hit_gtr100_gtx;
   std::vector<double>  out_rk_hit_gtr100_gty;
   std::vector<double>  out_rk_hit_gtr100_gtz;
   std::vector<double>  out_rk_hit_gtr100_gtx2;
   std::vector<double>  out_rk_hit_gtr100_gty2;
   std::vector<double>  out_rk_hit_gtr100_gtz2;
   std::vector<int>     out_rk_hit_gtr100_nc;
   std::vector<double>  out_rk_hit_gtr100_the;
   std::vector<double>  out_rk_hit_gtr100_the2;
   std::vector<int>     out_rk_hit_gtr200_xid;
   std::vector<int>     out_rk_hit_gtr200_yid;
   std::vector<double>  out_rk_hit_gtr200_gx;
   std::vector<double>  out_rk_hit_gtr200_gy;
   std::vector<double>  out_rk_hit_gtr200_gz;
   std::vector<float>   out_rk_hit_gtr200_xadc;
   std::vector<float>   out_rk_hit_gtr200_yadc;
   std::vector<float>   out_rk_hit_gtr200_xt;
   std::vector<float>   out_rk_hit_gtr200_yt;
   std::vector<float>   out_rk_hit_gtr200_xt2;
   std::vector<float>   out_rk_hit_gtr200_yt2;
   std::vector<double>  out_rk_hit_gtr200_tx2;
   std::vector<double>  out_rk_hit_gtr200_ty;
   std::vector<double>  out_rk_hit_gtr200_gtx;
   std::vector<double>  out_rk_hit_gtr200_gty;
   std::vector<double>  out_rk_hit_gtr200_gtz;
   std::vector<double>  out_rk_hit_gtr200_gtx2;
   std::vector<double>  out_rk_hit_gtr200_gty2;
   std::vector<double>  out_rk_hit_gtr200_gtz2;
   std::vector<int>     out_rk_hit_gtr200_nc;
   std::vector<double>  out_rk_hit_gtr200_the;
   std::vector<double>  out_rk_hit_gtr200_the2;
   std::vector<int>     out_rk_hit_gtr300_xid;
   std::vector<int>     out_rk_hit_gtr300_yid;
   std::vector<double>  out_rk_hit_gtr300_gx;
   std::vector<double>  out_rk_hit_gtr300_gy;
   std::vector<double>  out_rk_hit_gtr300_gz;
   std::vector<float>   out_rk_hit_gtr300_xadc;
   std::vector<float>   out_rk_hit_gtr300_yadc;
   std::vector<float>   out_rk_hit_gtr300_xt;
   std::vector<float>   out_rk_hit_gtr300_yt;
   std::vector<float>   out_rk_hit_gtr300_xt2;
   std::vector<float>   out_rk_hit_gtr300_yt2;
   std::vector<double>  out_rk_hit_gtr300_tx2;
   std::vector<double>  out_rk_hit_gtr300_ty;
   std::vector<double>  out_rk_hit_gtr300_gtx;
   std::vector<double>  out_rk_hit_gtr300_gty;
   std::vector<double>  out_rk_hit_gtr300_gtz;
   std::vector<double>  out_rk_hit_gtr300_gtx2;
   std::vector<double>  out_rk_hit_gtr300_gty2;
   std::vector<double>  out_rk_hit_gtr300_gtz2;
   std::vector<int>     out_rk_hit_gtr300_nc;
   std::vector<double>  out_rk_hit_gtr300_the;
   std::vector<double>  out_rk_hit_gtr300_the2;
   std::vector<double>  out_rk_fit_init_mom_gx;
   std::vector<double>  out_rk_fit_init_mom_gy;
   std::vector<double>  out_rk_fit_init_mom_gz;
   std::vector<double>  out_rk_fit_init_pos_gx;
   std::vector<double>  out_rk_fit_init_pos_gy;
   std::vector<double>  out_rk_fit_init_pos_gz;
   std::vector<int>     out_rk_fit_ssd_mid;
   std::vector<double>  out_rk_fit_ssd_x;
   std::vector<double>  out_rk_fit_ssd_y;
   std::vector<double>  out_rk_fit_ssd_gx;
   std::vector<double>  out_rk_fit_ssd_gy;
   std::vector<double>  out_rk_fit_ssd_gz;
   std::vector<double>  out_rk_fit_ssd_mom_x;
   std::vector<double>  out_rk_fit_ssd_mom_y;
   std::vector<double>  out_rk_fit_ssd_mom_z;
   std::vector<double>  out_rk_fit_ssd_mom_gx;
   std::vector<double>  out_rk_fit_ssd_mom_gy;
   std::vector<double>  out_rk_fit_ssd_mom_gz;
   std::vector<int>     out_rk_fit_gtr100_mid;
   std::vector<double>  out_rk_fit_gtr100_x;
   std::vector<double>  out_rk_fit_gtr100_y;
   std::vector<double>  out_rk_fit_gtr100_gx;
   std::vector<double>  out_rk_fit_gtr100_gy;
   std::vector<double>  out_rk_fit_gtr100_gz;
   std::vector<double>  out_rk_fit_gtr100_mom_x;
   std::vector<double>  out_rk_fit_gtr100_mom_y;
   std::vector<double>  out_rk_fit_gtr100_mom_z;
   std::vector<double>  out_rk_fit_gtr100_mom_gx;
   std::vector<double>  out_rk_fit_gtr100_mom_gy;
   std::vector<double>  out_rk_fit_gtr100_mom_gz;
   std::vector<int>     out_rk_fit_gtr200_mid;
   std::vector<double>  out_rk_fit_gtr200_x;
   std::vector<double>  out_rk_fit_gtr200_y;
   std::vector<double>  out_rk_fit_gtr200_gx;
   std::vector<double>  out_rk_fit_gtr200_gy;
   std::vector<double>  out_rk_fit_gtr200_gz;
   std::vector<double>  out_rk_fit_gtr200_mom_x;
   std::vector<double>  out_rk_fit_gtr200_mom_y;
   std::vector<double>  out_rk_fit_gtr200_mom_z;
   std::vector<double>  out_rk_fit_gtr200_mom_gx;
   std::vector<double>  out_rk_fit_gtr200_mom_gy;
   std::vector<double>  out_rk_fit_gtr200_mom_gz;
   std::vector<int>     out_rk_fit_gtr300_mid;
   std::vector<double>  out_rk_fit_gtr300_x;
   std::vector<double>  out_rk_fit_gtr300_y;
   std::vector<double>  out_rk_fit_gtr300_gx;
   std::vector<double>  out_rk_fit_gtr300_gy;
   std::vector<double>  out_rk_fit_gtr300_gz;
   std::vector<double>  out_rk_fit_gtr300_mom_x;
   std::vector<double>  out_rk_fit_gtr300_mom_y;
   std::vector<double>  out_rk_fit_gtr300_mom_z;
   std::vector<double>  out_rk_fit_gtr300_mom_gx;
   std::vector<double>  out_rk_fit_gtr300_mom_gy;
   std::vector<double>  out_rk_fit_gtr300_mom_gz;
   std::vector<int>     out_rk_fit_hbd_mid;
   std::vector<double>  out_rk_fit_hbd_x;
   std::vector<double>  out_rk_fit_hbd_y;
   std::vector<double>  out_rk_fit_hbd_gx;
   std::vector<double>  out_rk_fit_hbd_gy;
   std::vector<double>  out_rk_fit_hbd_gz;
   std::vector<double>  out_rk_fit_hbd_mom_x;
   std::vector<double>  out_rk_fit_hbd_mom_y;
   std::vector<double>  out_rk_fit_hbd_mom_z;
   std::vector<double>  out_rk_fit_hbd_mom_gx;
   std::vector<double>  out_rk_fit_hbd_mom_gy;
   std::vector<double>  out_rk_fit_hbd_mom_gz;
   std::vector<int>     out_rk_fit_lg_c_mid;
   std::vector<double>  out_rk_fit_lg_c_x;
   std::vector<double>  out_rk_fit_lg_c_y;
   std::vector<double>  out_rk_fit_lg_c_gx;
   std::vector<double>  out_rk_fit_lg_c_gy;
   std::vector<double>  out_rk_fit_lg_c_gz;
   std::vector<double>  out_rk_fit_lg_c_mom_x;
   std::vector<double>  out_rk_fit_lg_c_mom_y;
   std::vector<double>  out_rk_fit_lg_c_mom_z;
   std::vector<double>  out_rk_fit_lg_c_mom_gx;
   std::vector<double>  out_rk_fit_lg_c_mom_gy;
   std::vector<double>  out_rk_fit_lg_c_mom_gz;
   std::vector<int>     out_rk_fit_lg_b_mid;
   std::vector<double>  out_rk_fit_lg_b_x;
   std::vector<double>  out_rk_fit_lg_b_y;
   std::vector<double>  out_rk_fit_lg_b_gx;
   std::vector<double>  out_rk_fit_lg_b_gy;
   std::vector<double>  out_rk_fit_lg_b_gz;
   std::vector<double>  out_rk_fit_lg_b_mom_x;
   std::vector<double>  out_rk_fit_lg_b_mom_y;
   std::vector<double>  out_rk_fit_lg_b_mom_z;
   std::vector<double>  out_rk_fit_lg_b_mom_gx;
   std::vector<double>  out_rk_fit_lg_b_mom_gy;
   std::vector<double>  out_rk_fit_lg_b_mom_gz;
   std::vector<int>     out_rk_fit_lg_a_mid;
   std::vector<double>  out_rk_fit_lg_a_x;
   std::vector<double>  out_rk_fit_lg_a_y;
   std::vector<double>  out_rk_fit_lg_a_gx;
   std::vector<double>  out_rk_fit_lg_a_gy;
   std::vector<double>  out_rk_fit_lg_a_gz;
   std::vector<double>  out_rk_fit_lg_a_mom_x;
   std::vector<double>  out_rk_fit_lg_a_mom_y;
   std::vector<double>  out_rk_fit_lg_a_mom_z;
   std::vector<double>  out_rk_fit_lg_a_mom_gx;
   std::vector<double>  out_rk_fit_lg_a_mom_gy;
   std::vector<double>  out_rk_fit_lg_a_mom_gz;
   std::vector<double>  out_rk_res_init_pos_gx;
   std::vector<double>  out_rk_res_init_pos_gy;
   std::vector<double>  out_rk_res_init_pos_gz;
   std::vector<double>  out_rk_res_init_mom_gx;
   std::vector<double>  out_rk_res_init_mom_gy;
   std::vector<double>  out_rk_res_init_mom_gz;
   std::vector<double>  out_rk_res_ssd_x;
   std::vector<double>  out_rk_res_gtr100_x;
   std::vector<double>  out_rk_res_gtr100_y;
   std::vector<double>  out_rk_res_gtr200_x;
   std::vector<double>  out_rk_res_gtr200_y;
   std::vector<double>  out_rk_res_gtr300_x;
   std::vector<double>  out_rk_res_gtr300_y;
   std::vector<double>  out_rk_res_gtr100_tx;
   std::vector<double>  out_rk_res_gtr100_ty;
   std::vector<double>  out_rk_res_gtr200_tx;
   std::vector<double>  out_rk_res_gtr200_ty;
   std::vector<double>  out_rk_res_gtr300_tx;
   std::vector<double>  out_rk_res_gtr300_ty;
   std::vector<double>  out_rk_res_gtr100_tx2;
   std::vector<double>  out_rk_res_gtr200_tx2;
   std::vector<double>  out_rk_res_gtr300_tx2;
   std::vector<double>  out_rk_proj_tgt0_gx;
   std::vector<double>  out_rk_proj_tgt0_gy;
   std::vector<double>  out_rk_proj_tgt0_gz;
   std::vector<double>  out_rk_proj_tgt1_gx;
   std::vector<double>  out_rk_proj_tgt1_gy;
   std::vector<double>  out_rk_proj_tgt1_gz;
   std::vector<double>  out_rk_proj_tgt2_gx;
   std::vector<double>  out_rk_proj_tgt2_gy;
   std::vector<double>  out_rk_proj_tgt2_gz;
   std::vector<double>  out_rk_proj_tgt0_mom_gx;
   std::vector<double>  out_rk_proj_tgt0_mom_gy;
   std::vector<double>  out_rk_proj_tgt0_mom_gz;
   std::vector<double>  out_rk_proj_tgt1_mom_gx;
   std::vector<double>  out_rk_proj_tgt1_mom_gy;
   std::vector<double>  out_rk_proj_tgt1_mom_gz;
   std::vector<double>  out_rk_proj_tgt2_mom_gx;
   std::vector<double>  out_rk_proj_tgt2_mom_gy;
   std::vector<double>  out_rk_proj_tgt2_mom_gz;
   std::vector<double>  out_rk_proj_x0_gx;
   std::vector<double>  out_rk_proj_x0_gy;
   std::vector<double>  out_rk_proj_x0_gz;
   std::vector<double>  out_rk_proj_x0_mom_gx;
   std::vector<double>  out_rk_proj_x0_mom_gy;
   std::vector<double>  out_rk_proj_x0_mom_gz;
   std::vector<bool>    out_rk_proj_is_search;
   std::vector<int>     out_rk_proj_n_hbd;
   std::vector<std::vector<double> > out_rk_proj_hbd_id;
   std::vector<std::vector<double> > out_rk_proj_hbd_mid;
   std::vector<std::vector<double> > out_rk_proj_hbd_x;
   std::vector<std::vector<double> > out_rk_proj_hbd_y;
   std::vector<std::vector<double> > out_rk_proj_hbd_adc;
   std::vector<std::vector<double> > out_rk_proj_hbd_t;
   std::vector<std::vector<double> > out_rk_proj_hbd_ftime;
   std::vector<std::vector<double> > out_rk_proj_hbd_tdiff;
   std::vector<std::vector<double> > out_rk_proj_hbd_size;
   std::vector<std::vector<double> > out_rk_proj_hbd_eprob;
   std::vector<std::vector<double> > out_rk_proj_hbd_cprob;
   std::vector<int>                  out_rk_proj_n_lg;
   std::vector<std::vector<double> > out_rk_proj_lg_id;
   std::vector<std::vector<double> > out_rk_proj_lg_mid;
   std::vector<std::vector<double> > out_rk_proj_lg_cid;
   std::vector<std::vector<double> > out_rk_proj_lg_x;
   std::vector<std::vector<double> > out_rk_proj_lg_y;
   std::vector<std::vector<double> > out_rk_proj_lg_adc;
   std::vector<std::vector<double> > out_rk_proj_lg_t;
   std::vector<std::vector<double> > out_rk_proj_lg_npeaks;
   std::vector<std::vector<double> > out_rk_proj_lg_fflag;
   std::vector<int>                  out_rk_pair_minus_track_id;
   std::vector<int>                  out_rk_pair_minus_gtr300_mid;
   std::vector<double>               out_rk_pair_minus_chi_square;
   std::vector<double>               out_rk_pair_minus_mom_gx;
   std::vector<double>               out_rk_pair_minus_mom_gy;
   std::vector<double>               out_rk_pair_minus_mom_gz;
   std::vector<double>               out_rk_pair_minus_ssd_t;
   std::vector<std::vector<double> > out_rk_pair_minus_lg_t;
   std::vector<int>                  out_rk_pair_plus_track_id;
   std::vector<int>                  out_rk_pair_plus_gtr300_mid;
   std::vector<double>               out_rk_pair_plus_chi_square;
   std::vector<double>               out_rk_pair_plus_mom_gx;
   std::vector<double>               out_rk_pair_plus_mom_gy;
   std::vector<double>               out_rk_pair_plus_mom_gz;
   std::vector<double>               out_rk_pair_plus_ssd_t;
   std::vector<std::vector<double> > out_rk_pair_plus_lg_t;
   std::vector<double> out_rk_pair_distance;
   std::vector<double> out_rk_pair_vtx_gx;
   std::vector<double> out_rk_pair_vtx_gy;
   std::vector<double> out_rk_pair_vtx_gz;
   std::vector<bool>   out_rk_pair_is_refit;
   std::vector<bool>   out_rk_pair_is_selected;
   std::vector<double> out_rk_pair_chi_square_refit;
   std::vector<double> out_rk_pair_vtx_refit_gx;
   std::vector<double> out_rk_pair_vtx_refit_gy;
   std::vector<double> out_rk_pair_vtx_refit_gz;
   std::vector<double> out_rk_pair_minus_mom_refit_gx;
   std::vector<double> out_rk_pair_minus_mom_refit_gy;
   std::vector<double> out_rk_pair_minus_mom_refit_gz;
   std::vector<double> out_rk_pair_plus_mom_refit_gx;
   std::vector<double> out_rk_pair_plus_mom_refit_gy;
   std::vector<double> out_rk_pair_plus_mom_refit_gz;
   std::vector<double> out_rk_pair_minus_ssd_pos_refit_gx;
   std::vector<double> out_rk_pair_minus_ssd_pos_refit_gy;
   std::vector<double> out_rk_pair_minus_ssd_pos_refit_gz;
   std::vector<double> out_rk_pair_minus_gtr100_pos_refit_gx;
   std::vector<double> out_rk_pair_minus_gtr100_pos_refit_gy;
   std::vector<double> out_rk_pair_minus_gtr100_pos_refit_gz;
   std::vector<double> out_rk_pair_minus_gtr200_pos_refit_gx;
   std::vector<double> out_rk_pair_minus_gtr200_pos_refit_gy;
   std::vector<double> out_rk_pair_minus_gtr200_pos_refit_gz;
   std::vector<double> out_rk_pair_minus_gtr300_pos_refit_gx;
   std::vector<double> out_rk_pair_minus_gtr300_pos_refit_gy;
   std::vector<double> out_rk_pair_minus_gtr300_pos_refit_gz;
   std::vector<double> out_rk_pair_plus_ssd_pos_refit_gx;
   std::vector<double> out_rk_pair_plus_ssd_pos_refit_gy;
   std::vector<double> out_rk_pair_plus_ssd_pos_refit_gz;
   std::vector<double> out_rk_pair_plus_gtr100_pos_refit_gx;
   std::vector<double> out_rk_pair_plus_gtr100_pos_refit_gy;
   std::vector<double> out_rk_pair_plus_gtr100_pos_refit_gz;
   std::vector<double> out_rk_pair_plus_gtr200_pos_refit_gx;
   std::vector<double> out_rk_pair_plus_gtr200_pos_refit_gy;
   std::vector<double> out_rk_pair_plus_gtr200_pos_refit_gz;
   std::vector<double> out_rk_pair_plus_gtr300_pos_refit_gx;
   std::vector<double> out_rk_pair_plus_gtr300_pos_refit_gy;
   std::vector<double> out_rk_pair_plus_gtr300_pos_refit_gz;
   std::vector<double> out_rk_pair_minus_ssd_mom_refit_gx;
   std::vector<double> out_rk_pair_minus_ssd_mom_refit_gy;
   std::vector<double> out_rk_pair_minus_ssd_mom_refit_gz;
   std::vector<double> out_rk_pair_minus_gtr100_mom_refit_gx;
   std::vector<double> out_rk_pair_minus_gtr100_mom_refit_gy;
   std::vector<double> out_rk_pair_minus_gtr100_mom_refit_gz;
   std::vector<double> out_rk_pair_minus_gtr200_mom_refit_gx;
   std::vector<double> out_rk_pair_minus_gtr200_mom_refit_gy;
   std::vector<double> out_rk_pair_minus_gtr200_mom_refit_gz;
   std::vector<double> out_rk_pair_minus_gtr300_mom_refit_gx;
   std::vector<double> out_rk_pair_minus_gtr300_mom_refit_gy;
   std::vector<double> out_rk_pair_minus_gtr300_mom_refit_gz;
   std::vector<double> out_rk_pair_plus_ssd_mom_refit_gx;
   std::vector<double> out_rk_pair_plus_ssd_mom_refit_gy;
   std::vector<double> out_rk_pair_plus_ssd_mom_refit_gz;
   std::vector<double> out_rk_pair_plus_gtr100_mom_refit_gx;
   std::vector<double> out_rk_pair_plus_gtr100_mom_refit_gy;
   std::vector<double> out_rk_pair_plus_gtr100_mom_refit_gz;
   std::vector<double> out_rk_pair_plus_gtr200_mom_refit_gx;
   std::vector<double> out_rk_pair_plus_gtr200_mom_refit_gy;
   std::vector<double> out_rk_pair_plus_gtr200_mom_refit_gz;
   std::vector<double> out_rk_pair_plus_gtr300_mom_refit_gx;
   std::vector<double> out_rk_pair_plus_gtr300_mom_refit_gy;
   std::vector<double> out_rk_pair_plus_gtr300_mom_refit_gz;
   std::vector<double> out_rk_pair_minus_ssd_res_refit_x;
   std::vector<double> out_rk_pair_minus_ssd_res_refit_y;
   std::vector<double> out_rk_pair_minus_ssd_res_refit_z;
   std::vector<double> out_rk_pair_minus_gtr100_res_refit_x;
   std::vector<double> out_rk_pair_minus_gtr100_res_refit_y;
   std::vector<double> out_rk_pair_minus_gtr100_res_refit_z;
   std::vector<double> out_rk_pair_minus_gtr200_res_refit_x;
   std::vector<double> out_rk_pair_minus_gtr200_res_refit_y;
   std::vector<double> out_rk_pair_minus_gtr200_res_refit_z;
   std::vector<double> out_rk_pair_minus_gtr300_res_refit_x;
   std::vector<double> out_rk_pair_minus_gtr300_res_refit_y;
   std::vector<double> out_rk_pair_minus_gtr300_res_refit_z;
   std::vector<double> out_rk_pair_plus_ssd_res_refit_x;
   std::vector<double> out_rk_pair_plus_ssd_res_refit_y;
   std::vector<double> out_rk_pair_plus_ssd_res_refit_z;
   std::vector<double> out_rk_pair_plus_gtr100_res_refit_x;
   std::vector<double> out_rk_pair_plus_gtr100_res_refit_y;
   std::vector<double> out_rk_pair_plus_gtr100_res_refit_z;
   std::vector<double> out_rk_pair_plus_gtr200_res_refit_x;
   std::vector<double> out_rk_pair_plus_gtr200_res_refit_y;
   std::vector<double> out_rk_pair_plus_gtr200_res_refit_z;
   std::vector<double> out_rk_pair_plus_gtr300_res_refit_x;
   std::vector<double> out_rk_pair_plus_gtr300_res_refit_y;
   std::vector<double> out_rk_pair_plus_gtr300_res_refit_z;
   std::vector<double> out_rk_pair_mass_refit;

   std::vector<double>      out_rk_hit_gtr100_cogx;
   std::vector<double>      out_rk_hit_gtr200_cogx;
   std::vector<double>      out_rk_hit_gtr300_cogx;
   std::vector<double>      out_rk_hit_gtr100_cogy;
   std::vector<double>      out_rk_hit_gtr200_cogy;
   std::vector<double>      out_rk_hit_gtr300_cogy;


   std::vector<float>   out_rk_hit_gtr100_xt4;
   std::vector<float>   out_rk_hit_gtr200_xt4;
   std::vector<float>   out_rk_hit_gtr300_xt4;
   std::vector<float>   out_rk_hit_gtr100_yt4;
   std::vector<float>   out_rk_hit_gtr200_yt4;
   std::vector<float>   out_rk_hit_gtr300_yt4;

   std::vector<double> tmp_rk_fit_ssd_mid  ; 


 	  std::vector<double>tmp_rk_fit_ssd_x  ;
 	  std::vector<double>tmp_rk_fit_ssd_y;
 	  std::vector<double> tmp_rk_fit_ssd_gx;
 	  std::vector<double> tmp_rk_fit_ssd_gy;
 	  std::vector<double> tmp_rk_fit_ssd_gz;
 	  std::vector<double>   tmp_rk_fit_ssd_mom_x;
 	  std::vector<double>   tmp_rk_fit_ssd_mom_y;
 	  std::vector<double>   tmp_rk_fit_ssd_mom_z;
 	  std::vector<double>    tmp_rk_fit_ssd_mom_gx;
 	  std::vector<double>    tmp_rk_fit_ssd_mom_gy;
 	  std::vector<double>    tmp_rk_fit_ssd_mom_gz;





   std::vector<double> tmp_rk_fit_gtr100_mid; 
   std::vector<double> tmp_rk_fit_gtr200_mid; 
	std::vector<double> tmp_rk_fit_gtr300_mid;
   std::vector<double> tmp_rk_fit_gtr100_x;
   std::vector<double> tmp_rk_fit_gtr200_x;
   std::vector<double> tmp_rk_fit_gtr300_x;
   std::vector<double> tmp_rk_fit_gtr100_y;
   std::vector<double> tmp_rk_fit_gtr200_y;
   std::vector<double> tmp_rk_fit_gtr300_y;
   std::vector<double> tmp_rk_fit_gtr100_gx;
   std::vector<double> tmp_rk_fit_gtr200_gx;
   std::vector<double> tmp_rk_fit_gtr300_gx;
   std::vector<double> tmp_rk_fit_gtr100_gy;
   std::vector<double> tmp_rk_fit_gtr200_gy;
   std::vector<double> tmp_rk_fit_gtr300_gy;
   std::vector<double> tmp_rk_fit_gtr100_gz;
   std::vector<double> tmp_rk_fit_gtr200_gz;
   std::vector<double> tmp_rk_fit_gtr300_gz;
   std::vector<double> tmp_rk_fit_gtr100_mom_x;
   std::vector<double> tmp_rk_fit_gtr200_mom_x;
   std::vector<double> tmp_rk_fit_gtr300_mom_x;
   std::vector<double> tmp_rk_fit_gtr100_mom_y;
   std::vector<double> tmp_rk_fit_gtr200_mom_y;
   std::vector<double> tmp_rk_fit_gtr300_mom_y;
   std::vector<double> tmp_rk_fit_gtr100_mom_z;
   std::vector<double> tmp_rk_fit_gtr200_mom_z;
   std::vector<double> tmp_rk_fit_gtr300_mom_z;
   std::vector<double> tmp_rk_fit_gtr100_mom_gx;
   std::vector<double> tmp_rk_fit_gtr200_mom_gx;
   std::vector<double> tmp_rk_fit_gtr300_mom_gx;
   std::vector<double> tmp_rk_fit_gtr100_mom_gy;
   std::vector<double> tmp_rk_fit_gtr200_mom_gy;
   std::vector<double> tmp_rk_fit_gtr300_mom_gy;
   std::vector<double> tmp_rk_fit_gtr100_mom_gz;
   std::vector<double> tmp_rk_fit_gtr200_mom_gz;
   std::vector<double> tmp_rk_fit_gtr300_mom_gz;
   std::vector<double> tmp_rk_res_init_pos_gx; 
   std::vector<double> tmp_rk_res_init_pos_gy; 
   std::vector<double> tmp_rk_res_init_pos_gz; 
   std::vector<double> tmp_rk_res_init_mom_gx; 
   std::vector<double> tmp_rk_res_init_mom_gy; 
   std::vector<double> tmp_rk_res_init_mom_gz; 
   std::vector<double> tmp_rk_res_ssd_x   ; 
   std::vector<double> tmp_rk_res_gtr100_x; 
   std::vector<double> tmp_rk_res_gtr100_y; 
   std::vector<double> tmp_rk_res_gtr200_x; 
   std::vector<double> tmp_rk_res_gtr200_y; 
   std::vector<double> tmp_rk_res_gtr300_x; 
   std::vector<double> tmp_rk_res_gtr300_y; 

	std::vector<double> tmp_rk_fit_init_mom_gx;
	std::vector<double> tmp_rk_fit_init_mom_gy;
	std::vector<double> tmp_rk_fit_init_mom_gz;
	std::vector<double> tmp_rk_fit_init_pos_gx;
	std::vector<double> tmp_rk_fit_init_pos_gy;
	std::vector<double> tmp_rk_fit_init_pos_gz;
//      out_rk_res_gtr100_tx[i]     = fit_results[1].residual_pos.X(); 





private:
	E16ANA_StraightMultiTrack *fitter;
	std::array<std::vector<int>, E16ANA_StraightTrackConstant::kNumTrackingStrips> used_cluster_ids;
//	std::vector<int> killdup_ids;
	std::vector<int> good_ids;
	std::vector<int> sorted_ids;
	std::vector<int> killdup_ids;
	std::array<TVector3, E16ANA_StraightTrackConstant::kNumTrackingStrips> det_sigmas;//detectors sigmas
	std::array<FitResult, E16ANA_StraightTrackConstant::kNumTrackingStrips> fit_results;
	int removed_layer;
	TVector3 init_pos_fit;
	TVector3 init_mom_fit;
	TVector3 init_pos_sigma;
	E16ANA_GeometryV2 *geom;
	std::vector<double> chisq;
	bool isWire;
	
};

#endif//E16DSTN_PosCorrection_hh

#ifdef E16DSTN_PosCorrection_cxx
	

void E16DSTN_PosCorrection::Init(TTree *tree, const char* out_file){
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).


//  -- for output -- //

	fout    = new TFile (out_file, "recreate");
	outtree = new TTree("tree", "tree");

// -- for input -- //
   // Set object pointer
   ssd_hit_id = 0;
   ssd_hit_mid = 0;
   ssd_hit_cid = 0;
   ssd_hit_x = 0;
   ssd_hit_gx = 0;
   ssd_hit_gz = 0;
   ssd_hit_t = 0;
   ssd_hit_adc = 0;
   gtr100x_hit_id = 0;
   gtr100x_hit_mid = 0;
   gtr100x_hit_cid = 0;
   gtr100x_hit_x = 0;
   gtr100x_hit_tx = 0;
   gtr100x_hit_gx = 0;
   gtr100x_hit_gz = 0;
   gtr100x_hit_t = 0;
   gtr100x_hit_adc = 0;
   gtr200x_hit_id = 0;
   gtr200x_hit_mid = 0;
   gtr200x_hit_cid = 0;
   gtr200x_hit_x = 0;
   gtr200x_hit_tx = 0;
   gtr200x_hit_gx = 0;
   gtr200x_hit_gz = 0;
   gtr200x_hit_t = 0;
   gtr200x_hit_adc = 0;
   gtr300x_hit_id = 0;
   gtr300x_hit_mid = 0;
   gtr300x_hit_cid = 0;
   gtr300x_hit_x = 0;
   gtr300x_hit_tx = 0;
   gtr300x_hit_gx = 0;
   gtr300x_hit_gz = 0;
   gtr300x_hit_t = 0;
   gtr300x_hit_adc = 0;
   gtr100y_hit_id = 0;
   gtr100y_hit_mid = 0;
   gtr100y_hit_cid = 0;
   gtr100y_hit_y = 0;
   gtr100y_hit_ty = 0;
   gtr100y_hit_t = 0;
   gtr100y_hit_adc = 0;
   gtr100yb_hit_id = 0;
   gtr100yb_hit_mid = 0;
   gtr100yb_hit_cid = 0;
   gtr100yb_hit_y = 0;
   gtr100yb_hit_ty = 0;
   gtr100yb_hit_t = 0;
   gtr100yb_hit_adc = 0;
   gtr200y_hit_id = 0;
   gtr200y_hit_mid = 0;
   gtr200y_hit_cid = 0;
   gtr200y_hit_y = 0;
   gtr200y_hit_ty = 0;
   gtr200y_hit_t = 0;
   gtr200y_hit_adc = 0;
   gtr300y_hit_id = 0;
   gtr300y_hit_mid = 0;
   gtr300y_hit_cid = 0;
   gtr300y_hit_y = 0;
   gtr300y_hit_ty = 0;
   gtr300y_hit_t = 0;
   gtr300y_hit_adc = 0;
   hbd_hit_id = 0;
   hbd_hit_mid = 0;
   hbd_hit_cid = 0;
   hbd_hit_x = 0;
   hbd_hit_y = 0;
   hbd_hit_gx = 0;
   hbd_hit_gy = 0;
   hbd_hit_gz = 0;
   hbd_hit_t = 0;
   hbd_hit_adc = 0;
   ssd_cluster_id = 0;
   ssd_cluster_mid = 0;
   ssd_cluster_x = 0;
   ssd_cluster_gx = 0;
   ssd_cluster_gz = 0;
   ssd_cluster_adc = 0;
   ssd_cluster_t = 0;
   ssd_cluster_size = 0;
   ssd_cluster_fit_x = 0;
   ssd_cluster_fit_t = 0;
   ssd_cluster_fit_adc = 0;
   ssd_cluster_fit_chi2 = 0;
   gtr100x_cluster_id = 0;
   gtr100x_cluster_mid = 0;
   gtr100x_cluster_x = 0;
   gtr100x_cluster_gx = 0;
   gtr100x_cluster_gz = 0;
   gtr100x_cluster_adc = 0;
   gtr100x_cluster_t = 0;
   gtr100x_cluster_t2 = 0;
   gtr100x_cluster_tx = 0;
   gtr100x_cluster_the = 0;
   gtr100x_cluster_gtx = 0;
   gtr100x_cluster_nc = 0;
   gtr100x_cluster_size = 0;
   gtr200x_cluster_id = 0;
   gtr200x_cluster_mid = 0;
   gtr200x_cluster_x = 0;
   gtr200x_cluster_gx = 0;
   gtr200x_cluster_gz = 0;
   gtr200x_cluster_adc = 0;
   gtr200x_cluster_t = 0;
   gtr200x_cluster_t2 = 0;
   gtr200x_cluster_tx = 0;
   gtr200x_cluster_the = 0;
   gtr200x_cluster_nc = 0;
   gtr200x_cluster_gtx = 0;
   gtr200x_cluster_size = 0;
   gtr300x_cluster_id = 0;
   gtr300x_cluster_mid = 0;
   gtr300x_cluster_x = 0;
   gtr300x_cluster_gx = 0;
   gtr300x_cluster_gz = 0;
   gtr300x_cluster_adc = 0;
   gtr300x_cluster_t = 0;
   gtr300x_cluster_t2 = 0;
   gtr300x_cluster_tx = 0;
   gtr300x_cluster_the = 0;
   gtr300x_cluster_nc = 0;
   gtr300x_cluster_gtx = 0;
   gtr300x_cluster_size = 0;
   gtr100y_cluster_id = 0;
   gtr100y_cluster_mid = 0;
   gtr100y_cluster_y = 0;
   gtr100y_cluster_adc = 0;
   gtr100y_cluster_t = 0;
   gtr100y_cluster_t2 = 0;
   gtr100y_cluster_ty = 0;
   gtr100y_cluster_the = 0;
   gtr100y_cluster_nc = 0;
   gtr100y_cluster_size = 0;
   gtr100yb_cluster_id = 0;
   gtr100yb_cluster_mid = 0;
   gtr100yb_cluster_y = 0;
   gtr100yb_cluster_adc = 0;
   gtr100yb_cluster_t = 0;
   gtr100yb_cluster_t2 = 0;
   gtr100yb_cluster_ty = 0;
   gtr100yb_cluster_the = 0;
   gtr100yb_cluster_nc = 0;
   gtr100yb_cluster_size = 0;
   gtr200y_cluster_id = 0;
   gtr200y_cluster_mid = 0;
   gtr200y_cluster_y = 0;
   gtr200y_cluster_adc = 0;
   gtr200y_cluster_t = 0;
   gtr200y_cluster_t2 = 0;
   gtr200y_cluster_ty = 0;
   gtr200y_cluster_the = 0;
   gtr200y_cluster_nc = 0;
   gtr200y_cluster_size = 0;
   gtr300y_cluster_id = 0;
   gtr300y_cluster_mid = 0;
   gtr300y_cluster_y = 0;
   gtr300y_cluster_adc = 0;
   gtr300y_cluster_t = 0;
   gtr300y_cluster_t2 = 0;
   gtr300y_cluster_ty = 0;
   gtr300y_cluster_the = 0;
   gtr300y_cluster_nc = 0;
   gtr300y_cluster_size = 0;
   hbd_cluster_id = 0;
   hbd_cluster_mid = 0;
   hbd_cluster_x = 0;
   hbd_cluster_y = 0;
   hbd_cluster_gx = 0;
   hbd_cluster_gy = 0;
   hbd_cluster_gz = 0;
   hbd_cluster_adc = 0;
   hbd_cluster_max_cid = 0;
   hbd_cluster_t = 0;
   hbd_cluster_ftime = 0;
   hbd_cluster_tdiff = 0;
   hbd_cluster_size = 0;
   hbd_cluster_eprob = 0;
   hbd_cluster_cprob = 0;
   hbd_cluster_wotime_id = 0;
   hbd_cluster_wotime_mid = 0;
   hbd_cluster_wotime_x = 0;
   hbd_cluster_wotime_y = 0;
   hbd_cluster_wotime_gx = 0;
   hbd_cluster_wotime_gy = 0;
   hbd_cluster_wotime_gz = 0;
   hbd_cluster_wotime_adc = 0;
   hbd_cluster_wotime_max_cid = 0;
   hbd_cluster_wotime_t = 0;
   hbd_cluster_wotime_ftime = 0;
   hbd_cluster_wotime_tdiff = 0;
   hbd_cluster_wotime_size = 0;
   hbd_cluster_wotime_eprob = 0;
   hbd_cluster_wotime_cprob = 0;
   lg_hit_id = 0;
   lg_hit_mid = 0;
   lg_hit_cid = 0;
   lg_hit_x = 0;
   lg_hit_y = 0;
   lg_hit_z = 0;
   lg_hit_gx = 0;
   lg_hit_gy = 0;
   lg_hit_gz = 0;
   lg_hit_adc = 0;
   lg_hit_t = 0;
   lg_hit_wofit_adc = 0;
   lg_hit_wofit_t = 0;
   lg_hit_npeaks = 0;
   lg_hit_fflag = 0;
   lg_cluster_id = 0;
   lg_cluster_mid = 0;
   lg_cluster_max_cid = 0;
   lg_cluster_max_adc = 0;
   lg_cluster_x = 0;
   lg_cluster_y = 0;
   lg_cluster_z = 0;
   lg_cluster_gx = 0;
   lg_cluster_gy = 0;
   lg_cluster_gz = 0;
   lg_cluster_adc = 0;
   lg_cluster_t = 0;
   lg_cluster_tdiff = 0;
   lg_cluster_size = 0;
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
   trg_lg_hit_z = 0;
   trg_lg_hit_gx = 0;
   trg_lg_hit_gy = 0;
   trg_lg_hit_gz = 0;
   trg_lg_hit_t = 0;
   trg_track_n_gtr_hits = 0;
   trg_track_gtr_id = 0;
   trg_track_gtr_mid = 0;
   trg_track_gtr_cid = 0;
   trg_track_gtr_x = 0;
   trg_track_gtr_y = 0;
   trg_track_gtr_t = 0;
   trg_track_gtr_is_t_match = 0;
   trg_track_n_hbd_hits = 0;
   trg_track_hbd_id = 0;
   trg_track_hbd_mid = 0;
   trg_track_hbd_cid = 0;
   trg_track_hbd_x = 0;
   trg_track_hbd_y = 0;
   trg_track_hbd_t = 0;
   trg_track_hbd_is_t_match = 0;
   trg_track_lg_id = 0;
   trg_track_lg_mid = 0;
   trg_track_lg_cid = 0;
   trg_track_lg_x = 0;
   trg_track_lg_y = 0;
   trg_track_lg_t = 0;
   track_id = 0;
   has_e_hbd_cluster = 0;
   has_e_lg_hit = 0;
   is_large_residual = 0;
   is_near_target = 0;
   is_cluster_used = 0;
   is_selected = 0;
   x_rough_fit_chi_square = 0;
   x_rough_fit_dist0 = 0;
   x_rough_fit_dist1 = 0;
   x_rough_fit_coef0 = 0;
   x_rough_fit_coef1 = 0;
   x_rough_fit_coef2 = 0;
   rough_fit_n_hbds = 0;
   rough_fit_hbd_ids = 0;
   rough_fit_hbd_ress = 0;
   rough_fit_hbd_y_oks = 0;
   y_rough_fit_chi_square = 0;
   y_rough_fit_coef0 = 0;
   y_rough_fit_coef1 = 0;
   chi_square = 0;
   n_steps = 0;
   n_calls = 0;
   rk_charge = 0;
   rk_hit_init_mom_gx = 0;
   rk_hit_init_mom_gy = 0;
   rk_hit_init_mom_gz = 0;
   rk_hit_init_pos_gx = 0;
   rk_hit_init_pos_gy = 0;
   rk_hit_init_pos_gz = 0;
   rk_hit_ssd_id = 0;
   rk_hit_ssd_x = 0;
   rk_hit_ssd_gx = 0;
   rk_hit_ssd_gy = 0;
   rk_hit_ssd_gz = 0;
   rk_hit_ssd_adc = 0;
   rk_hit_ssd_t = 0;
   rk_hit_ssd_chi2 = 0;
   rk_hit_gtr100_xid = 0;
   rk_hit_gtr100_yid = 0;
   rk_hit_gtr100_gx = 0;
   rk_hit_gtr100_gy = 0;
   rk_hit_gtr100_gz = 0;
   rk_hit_gtr100_xadc = 0;
   rk_hit_gtr100_yadc = 0;
   rk_hit_gtr100_xt = 0;
   rk_hit_gtr100_yt = 0;
   rk_hit_gtr100_xt2 = 0;
   rk_hit_gtr100_yt2 = 0;
   rk_hit_gtr100_tx2 = 0;
   rk_hit_gtr100_ty = 0;
   rk_hit_gtr100_gtx = 0;
   rk_hit_gtr100_gty = 0;
   rk_hit_gtr100_gtz = 0;
   rk_hit_gtr100_gtx2 = 0;
   rk_hit_gtr100_gty2 = 0;
   rk_hit_gtr100_gtz2 = 0;
   rk_hit_gtr100_nc = 0;
   rk_hit_gtr100_the = 0;
   rk_hit_gtr100_the2 = 0;
   rk_hit_gtr200_xid = 0;
   rk_hit_gtr200_yid = 0;
   rk_hit_gtr200_gx = 0;
   rk_hit_gtr200_gy = 0;
   rk_hit_gtr200_gz = 0;
   rk_hit_gtr200_xadc = 0;
   rk_hit_gtr200_yadc = 0;
   rk_hit_gtr200_xt = 0;
   rk_hit_gtr200_yt = 0;
   rk_hit_gtr200_xt2 = 0;
   rk_hit_gtr200_yt2 = 0;
   rk_hit_gtr200_tx2 = 0;
   rk_hit_gtr200_ty = 0;
   rk_hit_gtr200_gtx = 0;
   rk_hit_gtr200_gty = 0;
   rk_hit_gtr200_gtz = 0;
   rk_hit_gtr200_gtx2 = 0;
   rk_hit_gtr200_gty2 = 0;
   rk_hit_gtr200_gtz2 = 0;
   rk_hit_gtr200_nc = 0;
   rk_hit_gtr200_the = 0;
   rk_hit_gtr200_the2 = 0;
   rk_hit_gtr300_xid = 0;
   rk_hit_gtr300_yid = 0;
   rk_hit_gtr300_gx = 0;
   rk_hit_gtr300_gy = 0;
   rk_hit_gtr300_gz = 0;
   rk_hit_gtr300_xadc = 0;
   rk_hit_gtr300_yadc = 0;
   rk_hit_gtr300_xt = 0;
   rk_hit_gtr300_yt = 0;
   rk_hit_gtr300_xt2 = 0;
   rk_hit_gtr300_yt2 = 0;
   rk_hit_gtr300_tx2 = 0;
   rk_hit_gtr300_ty = 0;
   rk_hit_gtr300_gtx = 0;
   rk_hit_gtr300_gty = 0;
   rk_hit_gtr300_gtz = 0;
   rk_hit_gtr300_gtx2 = 0;
   rk_hit_gtr300_gty2 = 0;
   rk_hit_gtr300_gtz2 = 0;
   rk_hit_gtr300_nc = 0;
   rk_hit_gtr300_the = 0;
   rk_hit_gtr300_the2 = 0;
   rk_fit_init_mom_gx = 0;
   rk_fit_init_mom_gy = 0;
   rk_fit_init_mom_gz = 0;
   rk_fit_init_pos_gx = 0;
   rk_fit_init_pos_gy = 0;
   rk_fit_init_pos_gz = 0;
   rk_fit_ssd_mid = 0;
   rk_fit_ssd_x = 0;
   rk_fit_ssd_y = 0;
   rk_fit_ssd_gx = 0;
   rk_fit_ssd_gy = 0;
   rk_fit_ssd_gz = 0;
   rk_fit_ssd_mom_x = 0;
   rk_fit_ssd_mom_y = 0;
   rk_fit_ssd_mom_z = 0;
   rk_fit_ssd_mom_gx = 0;
   rk_fit_ssd_mom_gy = 0;
   rk_fit_ssd_mom_gz = 0;
   rk_fit_gtr100_mid = 0;
   rk_fit_gtr100_x = 0;
   rk_fit_gtr100_y = 0;
   rk_fit_gtr100_gx = 0;
   rk_fit_gtr100_gy = 0;
   rk_fit_gtr100_gz = 0;
   rk_fit_gtr100_mom_x = 0;
   rk_fit_gtr100_mom_y = 0;
   rk_fit_gtr100_mom_z = 0;
   rk_fit_gtr100_mom_gx = 0;
   rk_fit_gtr100_mom_gy = 0;
   rk_fit_gtr100_mom_gz = 0;
   rk_fit_gtr200_mid = 0;
   rk_fit_gtr200_x = 0;
   rk_fit_gtr200_y = 0;
   rk_fit_gtr200_gx = 0;
   rk_fit_gtr200_gy = 0;
   rk_fit_gtr200_gz = 0;
   rk_fit_gtr200_mom_x = 0;
   rk_fit_gtr200_mom_y = 0;
   rk_fit_gtr200_mom_z = 0;
   rk_fit_gtr200_mom_gx = 0;
   rk_fit_gtr200_mom_gy = 0;
   rk_fit_gtr200_mom_gz = 0;
   rk_fit_gtr300_mid = 0;
   rk_fit_gtr300_x = 0;
   rk_fit_gtr300_y = 0;
   rk_fit_gtr300_gx = 0;
   rk_fit_gtr300_gy = 0;
   rk_fit_gtr300_gz = 0;
   rk_fit_gtr300_mom_x = 0;
   rk_fit_gtr300_mom_y = 0;
   rk_fit_gtr300_mom_z = 0;
   rk_fit_gtr300_mom_gx = 0;
   rk_fit_gtr300_mom_gy = 0;
   rk_fit_gtr300_mom_gz = 0;
   rk_fit_hbd_mid = 0;
   rk_fit_hbd_x = 0;
   rk_fit_hbd_y = 0;
   rk_fit_hbd_gx = 0;
   rk_fit_hbd_gy = 0;
   rk_fit_hbd_gz = 0;
   rk_fit_hbd_mom_x = 0;
   rk_fit_hbd_mom_y = 0;
   rk_fit_hbd_mom_z = 0;
   rk_fit_hbd_mom_gx = 0;
   rk_fit_hbd_mom_gy = 0;
   rk_fit_hbd_mom_gz = 0;
   rk_fit_lg_c_mid = 0;
   rk_fit_lg_c_x = 0;
   rk_fit_lg_c_y = 0;
   rk_fit_lg_c_gx = 0;
   rk_fit_lg_c_gy = 0;
   rk_fit_lg_c_gz = 0;
   rk_fit_lg_c_mom_x = 0;
   rk_fit_lg_c_mom_y = 0;
   rk_fit_lg_c_mom_z = 0;
   rk_fit_lg_c_mom_gx = 0;
   rk_fit_lg_c_mom_gy = 0;
   rk_fit_lg_c_mom_gz = 0;
   rk_fit_lg_b_mid = 0;
   rk_fit_lg_b_x = 0;
   rk_fit_lg_b_y = 0;
   rk_fit_lg_b_gx = 0;
   rk_fit_lg_b_gy = 0;
   rk_fit_lg_b_gz = 0;
   rk_fit_lg_b_mom_x = 0;
   rk_fit_lg_b_mom_y = 0;
   rk_fit_lg_b_mom_z = 0;
   rk_fit_lg_b_mom_gx = 0;
   rk_fit_lg_b_mom_gy = 0;
   rk_fit_lg_b_mom_gz = 0;
   rk_fit_lg_a_mid = 0;
   rk_fit_lg_a_x = 0;
   rk_fit_lg_a_y = 0;
   rk_fit_lg_a_gx = 0;
   rk_fit_lg_a_gy = 0;
   rk_fit_lg_a_gz = 0;
   rk_fit_lg_a_mom_x = 0;
   rk_fit_lg_a_mom_y = 0;
   rk_fit_lg_a_mom_z = 0;
   rk_fit_lg_a_mom_gx = 0;
   rk_fit_lg_a_mom_gy = 0;
   rk_fit_lg_a_mom_gz = 0;
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
   rk_res_gtr100_tx = 0;
   rk_res_gtr100_ty = 0;
   rk_res_gtr200_tx = 0;
   rk_res_gtr200_ty = 0;
   rk_res_gtr300_tx = 0;
   rk_res_gtr300_ty = 0;
   rk_res_gtr100_tx2 = 0;
   rk_res_gtr200_tx2 = 0;
   rk_res_gtr300_tx2 = 0;
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
   rk_proj_is_search = 0;
   rk_proj_n_hbd = 0;
   rk_proj_hbd_id = 0;
   rk_proj_hbd_mid = 0;
   rk_proj_hbd_x = 0;
   rk_proj_hbd_y = 0;
   rk_proj_hbd_adc = 0;
   rk_proj_hbd_t = 0;
   rk_proj_hbd_ftime = 0;
   rk_proj_hbd_tdiff = 0;
   rk_proj_hbd_size = 0;
   rk_proj_hbd_eprob = 0;
   rk_proj_hbd_cprob = 0;
   rk_proj_n_lg = 0;
   rk_proj_lg_id = 0;
   rk_proj_lg_mid = 0;
   rk_proj_lg_cid = 0;
   rk_proj_lg_x = 0;
   rk_proj_lg_y = 0;
   rk_proj_lg_adc = 0;
   rk_proj_lg_t = 0;
   rk_proj_lg_npeaks = 0;
   rk_proj_lg_fflag = 0;
   rk_pair_minus_track_id = 0;
   rk_pair_minus_gtr300_mid = 0;
   rk_pair_minus_chi_square = 0;
   rk_pair_minus_mom_gx = 0;
   rk_pair_minus_mom_gy = 0;
   rk_pair_minus_mom_gz = 0;
   rk_pair_minus_ssd_t = 0;
   rk_pair_minus_lg_t = 0;
   rk_pair_plus_track_id = 0;
   rk_pair_plus_gtr300_mid = 0;
   rk_pair_plus_chi_square = 0;
   rk_pair_plus_mom_gx = 0;
   rk_pair_plus_mom_gy = 0;
   rk_pair_plus_mom_gz = 0;
   rk_pair_plus_ssd_t = 0;
   rk_pair_plus_lg_t = 0;
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

   rk_hit_gtr100_cogx = 0 ;
   rk_hit_gtr200_cogx = 0 ;
   rk_hit_gtr300_cogx = 0 ;
   rk_hit_gtr100_cogy = 0 ;
   rk_hit_gtr200_cogy = 0 ;
   rk_hit_gtr300_cogy = 0 ;


   rk_hit_gtr100_xt4=0;
   rk_hit_gtr200_xt4=0;
   rk_hit_gtr300_xt4=0;
   rk_hit_gtr100_yt4=0;
   rk_hit_gtr200_yt4=0;
   rk_hit_gtr300_yt4=0;

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run_id", &run_id, &b_run_id);
   fChain->SetBranchAddress("event_id", &event_id, &b_event_id);
   fChain->SetBranchAddress("spill_id", &spill_id, &b_spill_id);
   fChain->SetBranchAddress("timestamp_in_spill", &timestamp_in_spill, &b_timestamp_in_spill);
   fChain->SetBranchAddress("trigger_fine_time", &trigger_fine_time, &b_trigger_fine_time);
   fChain->SetBranchAddress("n_fill", &n_fill, &b_n_fill);
   fChain->SetBranchAddress("n_ssd_hits", &n_ssd_hits, &b_n_ssd_hits);
   fChain->SetBranchAddress("ssd_hit_id", &ssd_hit_id, &b_ssd_hit_id);
   fChain->SetBranchAddress("ssd_hit_mid", &ssd_hit_mid, &b_ssd_hit_mid);
   fChain->SetBranchAddress("ssd_hit_cid", &ssd_hit_cid, &b_ssd_hit_cid);
   fChain->SetBranchAddress("ssd_hit_x", &ssd_hit_x, &b_ssd_hit_x);
   fChain->SetBranchAddress("ssd_hit_gx", &ssd_hit_gx, &b_ssd_hit_gx);
   fChain->SetBranchAddress("ssd_hit_gz", &ssd_hit_gz, &b_ssd_hit_gz);
   fChain->SetBranchAddress("ssd_hit_t", &ssd_hit_t, &b_ssd_hit_t);
   fChain->SetBranchAddress("ssd_hit_adc", &ssd_hit_adc, &b_ssd_hit_adc);
   fChain->SetBranchAddress("n_gtr100x_hits", &n_gtr100x_hits, &b_n_gtr100x_hits);
   fChain->SetBranchAddress("gtr100x_hit_id", &gtr100x_hit_id, &b_gtr100x_hit_id);
   fChain->SetBranchAddress("gtr100x_hit_mid", &gtr100x_hit_mid, &b_gtr100x_hit_mid);
   fChain->SetBranchAddress("gtr100x_hit_cid", &gtr100x_hit_cid, &b_gtr100x_hit_cid);
   fChain->SetBranchAddress("gtr100x_hit_x", &gtr100x_hit_x, &b_gtr100x_hit_x);
   fChain->SetBranchAddress("gtr100x_hit_tx", &gtr100x_hit_tx, &b_gtr100x_hit_tx);
   fChain->SetBranchAddress("gtr100x_hit_gx", &gtr100x_hit_gx, &b_gtr100x_hit_gx);
   fChain->SetBranchAddress("gtr100x_hit_gz", &gtr100x_hit_gz, &b_gtr100x_hit_gz);
   fChain->SetBranchAddress("gtr100x_hit_t", &gtr100x_hit_t, &b_gtr100x_hit_t);
   fChain->SetBranchAddress("gtr100x_hit_adc", &gtr100x_hit_adc, &b_gtr100x_hit_adc);
   fChain->SetBranchAddress("n_gtr200x_hits", &n_gtr200x_hits, &b_n_gtr200x_hits);
   fChain->SetBranchAddress("gtr200x_hit_id", &gtr200x_hit_id, &b_gtr200x_hit_id);
   fChain->SetBranchAddress("gtr200x_hit_mid", &gtr200x_hit_mid, &b_gtr200x_hit_mid);
   fChain->SetBranchAddress("gtr200x_hit_cid", &gtr200x_hit_cid, &b_gtr200x_hit_cid);
   fChain->SetBranchAddress("gtr200x_hit_x", &gtr200x_hit_x, &b_gtr200x_hit_x);
   fChain->SetBranchAddress("gtr200x_hit_tx", &gtr200x_hit_tx, &b_gtr200x_hit_tx);
   fChain->SetBranchAddress("gtr200x_hit_gx", &gtr200x_hit_gx, &b_gtr200x_hit_gx);
   fChain->SetBranchAddress("gtr200x_hit_gz", &gtr200x_hit_gz, &b_gtr200x_hit_gz);
   fChain->SetBranchAddress("gtr200x_hit_t", &gtr200x_hit_t, &b_gtr200x_hit_t);
   fChain->SetBranchAddress("gtr200x_hit_adc", &gtr200x_hit_adc, &b_gtr200x_hit_adc);
   fChain->SetBranchAddress("n_gtr300x_hits", &n_gtr300x_hits, &b_n_gtr300x_hits);
   fChain->SetBranchAddress("gtr300x_hit_id", &gtr300x_hit_id, &b_gtr300x_hit_id);
   fChain->SetBranchAddress("gtr300x_hit_mid", &gtr300x_hit_mid, &b_gtr300x_hit_mid);
   fChain->SetBranchAddress("gtr300x_hit_cid", &gtr300x_hit_cid, &b_gtr300x_hit_cid);
   fChain->SetBranchAddress("gtr300x_hit_x", &gtr300x_hit_x, &b_gtr300x_hit_x);
   fChain->SetBranchAddress("gtr300x_hit_tx", &gtr300x_hit_tx, &b_gtr300x_hit_tx);
   fChain->SetBranchAddress("gtr300x_hit_gx", &gtr300x_hit_gx, &b_gtr300x_hit_gx);
   fChain->SetBranchAddress("gtr300x_hit_gz", &gtr300x_hit_gz, &b_gtr300x_hit_gz);
   fChain->SetBranchAddress("gtr300x_hit_t", &gtr300x_hit_t, &b_gtr300x_hit_t);
   fChain->SetBranchAddress("gtr300x_hit_adc", &gtr300x_hit_adc, &b_gtr300x_hit_adc);
   fChain->SetBranchAddress("n_gtr100y_hits", &n_gtr100y_hits, &b_n_gtr100y_hits);
   fChain->SetBranchAddress("gtr100y_hit_id", &gtr100y_hit_id, &b_gtr100y_hit_id);
   fChain->SetBranchAddress("gtr100y_hit_mid", &gtr100y_hit_mid, &b_gtr100y_hit_mid);
   fChain->SetBranchAddress("gtr100y_hit_cid", &gtr100y_hit_cid, &b_gtr100y_hit_cid);
   fChain->SetBranchAddress("gtr100y_hit_y", &gtr100y_hit_y, &b_gtr100y_hit_y);
   fChain->SetBranchAddress("gtr100y_hit_ty", &gtr100y_hit_ty, &b_gtr100y_hit_ty);
   fChain->SetBranchAddress("gtr100y_hit_t", &gtr100y_hit_t, &b_gtr100y_hit_t);
   fChain->SetBranchAddress("gtr100y_hit_adc", &gtr100y_hit_adc, &b_gtr100y_hit_adc);
   fChain->SetBranchAddress("n_gtr100yb_hits", &n_gtr100yb_hits, &b_n_gtr100yb_hits);
   fChain->SetBranchAddress("gtr100yb_hit_id", &gtr100yb_hit_id, &b_gtr100yb_hit_id);
   fChain->SetBranchAddress("gtr100yb_hit_mid", &gtr100yb_hit_mid, &b_gtr100yb_hit_mid);
   fChain->SetBranchAddress("gtr100yb_hit_cid", &gtr100yb_hit_cid, &b_gtr100yb_hit_cid);
   fChain->SetBranchAddress("gtr100yb_hit_y", &gtr100yb_hit_y, &b_gtr100yb_hit_y);
   fChain->SetBranchAddress("gtr100yb_hit_ty", &gtr100yb_hit_ty, &b_gtr100yb_hit_ty);
   fChain->SetBranchAddress("gtr100yb_hit_t", &gtr100yb_hit_t, &b_gtr100yb_hit_t);
   fChain->SetBranchAddress("gtr100yb_hit_adc", &gtr100yb_hit_adc, &b_gtr100yb_hit_adc);
   fChain->SetBranchAddress("n_gtr200y_hits", &n_gtr200y_hits, &b_n_gtr200y_hits);
   fChain->SetBranchAddress("gtr200y_hit_id", &gtr200y_hit_id, &b_gtr200y_hit_id);
   fChain->SetBranchAddress("gtr200y_hit_mid", &gtr200y_hit_mid, &b_gtr200y_hit_mid);
   fChain->SetBranchAddress("gtr200y_hit_cid", &gtr200y_hit_cid, &b_gtr200y_hit_cid);
   fChain->SetBranchAddress("gtr200y_hit_y", &gtr200y_hit_y, &b_gtr200y_hit_y);
   fChain->SetBranchAddress("gtr200y_hit_ty", &gtr200y_hit_ty, &b_gtr200y_hit_ty);
   fChain->SetBranchAddress("gtr200y_hit_t", &gtr200y_hit_t, &b_gtr200y_hit_t);
   fChain->SetBranchAddress("gtr200y_hit_adc", &gtr200y_hit_adc, &b_gtr200y_hit_adc);
   fChain->SetBranchAddress("n_gtr300y_hits", &n_gtr300y_hits, &b_n_gtr300y_hits);
   fChain->SetBranchAddress("gtr300y_hit_id", &gtr300y_hit_id, &b_gtr300y_hit_id);
   fChain->SetBranchAddress("gtr300y_hit_mid", &gtr300y_hit_mid, &b_gtr300y_hit_mid);
   fChain->SetBranchAddress("gtr300y_hit_cid", &gtr300y_hit_cid, &b_gtr300y_hit_cid);
   fChain->SetBranchAddress("gtr300y_hit_y", &gtr300y_hit_y, &b_gtr300y_hit_y);
   fChain->SetBranchAddress("gtr300y_hit_ty", &gtr300y_hit_ty, &b_gtr300y_hit_ty);
   fChain->SetBranchAddress("gtr300y_hit_t", &gtr300y_hit_t, &b_gtr300y_hit_t);
   fChain->SetBranchAddress("gtr300y_hit_adc", &gtr300y_hit_adc, &b_gtr300y_hit_adc);
   fChain->SetBranchAddress("n_hbd_hits", &n_hbd_hits, &b_n_hbd_hits);
   fChain->SetBranchAddress("hbd_hit_id", &hbd_hit_id, &b_hbd_hit_id);
   fChain->SetBranchAddress("hbd_hit_mid", &hbd_hit_mid, &b_hbd_hit_mid);
   fChain->SetBranchAddress("hbd_hit_cid", &hbd_hit_cid, &b_hbd_hit_cid);
   fChain->SetBranchAddress("hbd_hit_x", &hbd_hit_x, &b_hbd_hit_x);
   fChain->SetBranchAddress("hbd_hit_y", &hbd_hit_y, &b_hbd_hit_y);
   fChain->SetBranchAddress("hbd_hit_gx", &hbd_hit_gx, &b_hbd_hit_gx);
   fChain->SetBranchAddress("hbd_hit_gy", &hbd_hit_gy, &b_hbd_hit_gy);
   fChain->SetBranchAddress("hbd_hit_gz", &hbd_hit_gz, &b_hbd_hit_gz);
   fChain->SetBranchAddress("hbd_hit_t", &hbd_hit_t, &b_hbd_hit_t);
   fChain->SetBranchAddress("hbd_hit_adc", &hbd_hit_adc, &b_hbd_hit_adc);
   fChain->SetBranchAddress("n_ssd_clusters", &n_ssd_clusters, &b_n_ssd_clusters);
   fChain->SetBranchAddress("ssd_cluster_id", &ssd_cluster_id, &b_ssd_cluster_id);
   fChain->SetBranchAddress("ssd_cluster_mid", &ssd_cluster_mid, &b_ssd_cluster_mid);
   fChain->SetBranchAddress("ssd_cluster_x", &ssd_cluster_x, &b_ssd_cluster_x);
   fChain->SetBranchAddress("ssd_cluster_gx", &ssd_cluster_gx, &b_ssd_cluster_gx);
   fChain->SetBranchAddress("ssd_cluster_gz", &ssd_cluster_gz, &b_ssd_cluster_gz);
   fChain->SetBranchAddress("ssd_cluster_adc", &ssd_cluster_adc, &b_ssd_cluster_adc);
   fChain->SetBranchAddress("ssd_cluster_t", &ssd_cluster_t, &b_ssd_cluster_t);
   fChain->SetBranchAddress("ssd_cluster_size", &ssd_cluster_size, &b_ssd_cluster_size);
   fChain->SetBranchAddress("ssd_cluster_fit_x", &ssd_cluster_fit_x, &b_ssd_cluster_fit_x);
   fChain->SetBranchAddress("ssd_cluster_fit_t", &ssd_cluster_fit_t, &b_ssd_cluster_fit_t);
   fChain->SetBranchAddress("ssd_cluster_fit_adc", &ssd_cluster_fit_adc, &b_ssd_cluster_fit_adc);
   fChain->SetBranchAddress("ssd_cluster_fit_chi2", &ssd_cluster_fit_chi2, &b_ssd_cluster_fit_chi2);
   fChain->SetBranchAddress("n_gtr100x_clusters", &n_gtr100x_clusters, &b_n_gtr100x_clusters);
   fChain->SetBranchAddress("gtr100x_cluster_id", &gtr100x_cluster_id, &b_gtr100x_cluster_id);
   fChain->SetBranchAddress("gtr100x_cluster_mid", &gtr100x_cluster_mid, &b_gtr100x_cluster_mid);
   fChain->SetBranchAddress("gtr100x_cluster_x", &gtr100x_cluster_x, &b_gtr100x_cluster_x);
   fChain->SetBranchAddress("gtr100x_cluster_gx", &gtr100x_cluster_gx, &b_gtr100x_cluster_gx);
   fChain->SetBranchAddress("gtr100x_cluster_gz", &gtr100x_cluster_gz, &b_gtr100x_cluster_gz);
   fChain->SetBranchAddress("gtr100x_cluster_adc", &gtr100x_cluster_adc, &b_gtr100x_cluster_adc);
   fChain->SetBranchAddress("gtr100x_cluster_t", &gtr100x_cluster_t, &b_gtr100x_cluster_t);
   fChain->SetBranchAddress("gtr100x_cluster_t2", &gtr100x_cluster_t2, &b_gtr100x_cluster_t2);
   fChain->SetBranchAddress("gtr100x_cluster_tx", &gtr100x_cluster_tx, &b_gtr100x_cluster_tx);
   fChain->SetBranchAddress("gtr100x_cluster_the", &gtr100x_cluster_the, &b_gtr100x_cluster_the);
   fChain->SetBranchAddress("gtr100x_cluster_gtx", &gtr100x_cluster_gtx, &b_gtr100x_cluster_gtx);
   fChain->SetBranchAddress("gtr100x_cluster_nc", &gtr100x_cluster_nc, &b_gtr100x_cluster_nc);
   fChain->SetBranchAddress("gtr100x_cluster_size", &gtr100x_cluster_size, &b_gtr100x_cluster_size);
   fChain->SetBranchAddress("n_gtr200x_clusters", &n_gtr200x_clusters, &b_n_gtr200x_clusters);
   fChain->SetBranchAddress("gtr200x_cluster_id", &gtr200x_cluster_id, &b_gtr200x_cluster_id);
   fChain->SetBranchAddress("gtr200x_cluster_mid", &gtr200x_cluster_mid, &b_gtr200x_cluster_mid);
   fChain->SetBranchAddress("gtr200x_cluster_x", &gtr200x_cluster_x, &b_gtr200x_cluster_x);
   fChain->SetBranchAddress("gtr200x_cluster_gx", &gtr200x_cluster_gx, &b_gtr200x_cluster_gx);
   fChain->SetBranchAddress("gtr200x_cluster_gz", &gtr200x_cluster_gz, &b_gtr200x_cluster_gz);
   fChain->SetBranchAddress("gtr200x_cluster_adc", &gtr200x_cluster_adc, &b_gtr200x_cluster_adc);
   fChain->SetBranchAddress("gtr200x_cluster_t", &gtr200x_cluster_t, &b_gtr200x_cluster_t);
   fChain->SetBranchAddress("gtr200x_cluster_t2", &gtr200x_cluster_t2, &b_gtr200x_cluster_t2);
   fChain->SetBranchAddress("gtr200x_cluster_tx", &gtr200x_cluster_tx, &b_gtr200x_cluster_tx);
   fChain->SetBranchAddress("gtr200x_cluster_the", &gtr200x_cluster_the, &b_gtr200x_cluster_the);
   fChain->SetBranchAddress("gtr200x_cluster_nc", &gtr200x_cluster_nc, &b_gtr200x_cluster_nc);
   fChain->SetBranchAddress("gtr200x_cluster_gtx", &gtr200x_cluster_gtx, &b_gtr200x_cluster_gtx);
   fChain->SetBranchAddress("gtr200x_cluster_size", &gtr200x_cluster_size, &b_gtr200x_cluster_size);
   fChain->SetBranchAddress("n_gtr300x_clusters", &n_gtr300x_clusters, &b_n_gtr300x_clusters);
   fChain->SetBranchAddress("gtr300x_cluster_id", &gtr300x_cluster_id, &b_gtr300x_cluster_id);
   fChain->SetBranchAddress("gtr300x_cluster_mid", &gtr300x_cluster_mid, &b_gtr300x_cluster_mid);
   fChain->SetBranchAddress("gtr300x_cluster_x", &gtr300x_cluster_x, &b_gtr300x_cluster_x);
   fChain->SetBranchAddress("gtr300x_cluster_gx", &gtr300x_cluster_gx, &b_gtr300x_cluster_gx);
   fChain->SetBranchAddress("gtr300x_cluster_gz", &gtr300x_cluster_gz, &b_gtr300x_cluster_gz);
   fChain->SetBranchAddress("gtr300x_cluster_adc", &gtr300x_cluster_adc, &b_gtr300x_cluster_adc);
   fChain->SetBranchAddress("gtr300x_cluster_t", &gtr300x_cluster_t, &b_gtr300x_cluster_t);
   fChain->SetBranchAddress("gtr300x_cluster_t2", &gtr300x_cluster_t2, &b_gtr300x_cluster_t2);
   fChain->SetBranchAddress("gtr300x_cluster_tx", &gtr300x_cluster_tx, &b_gtr300x_cluster_tx);
   fChain->SetBranchAddress("gtr300x_cluster_the", &gtr300x_cluster_the, &b_gtr300x_cluster_the);
   fChain->SetBranchAddress("gtr300x_cluster_nc", &gtr300x_cluster_nc, &b_gtr300x_cluster_nc);
   fChain->SetBranchAddress("gtr300x_cluster_gtx", &gtr300x_cluster_gtx, &b_gtr300x_cluster_gtx);
   fChain->SetBranchAddress("gtr300x_cluster_size", &gtr300x_cluster_size, &b_gtr300x_cluster_size);
   fChain->SetBranchAddress("n_gtr100y_clusters", &n_gtr100y_clusters, &b_n_gtr100y_clusters);
   fChain->SetBranchAddress("gtr100y_cluster_id", &gtr100y_cluster_id, &b_gtr100y_cluster_id);
   fChain->SetBranchAddress("gtr100y_cluster_mid", &gtr100y_cluster_mid, &b_gtr100y_cluster_mid);
   fChain->SetBranchAddress("gtr100y_cluster_y", &gtr100y_cluster_y, &b_gtr100y_cluster_y);
   fChain->SetBranchAddress("gtr100y_cluster_adc", &gtr100y_cluster_adc, &b_gtr100y_cluster_adc);
   fChain->SetBranchAddress("gtr100y_cluster_t", &gtr100y_cluster_t, &b_gtr100y_cluster_t);
   fChain->SetBranchAddress("gtr100y_cluster_t2", &gtr100y_cluster_t2, &b_gtr100y_cluster_t2);
   fChain->SetBranchAddress("gtr100y_cluster_ty", &gtr100y_cluster_ty, &b_gtr100y_cluster_ty);
   fChain->SetBranchAddress("gtr100y_cluster_the", &gtr100y_cluster_the, &b_gtr100y_cluster_the);
   fChain->SetBranchAddress("gtr100y_cluster_nc", &gtr100y_cluster_nc, &b_gtr100y_cluster_nc);
   fChain->SetBranchAddress("gtr100y_cluster_size", &gtr100y_cluster_size, &b_gtr100y_cluster_size);
   fChain->SetBranchAddress("n_gtr100yb_clusters", &n_gtr100yb_clusters, &b_n_gtr100yb_clusters);
   fChain->SetBranchAddress("gtr100yb_cluster_id", &gtr100yb_cluster_id, &b_gtr100yb_cluster_id);
   fChain->SetBranchAddress("gtr100yb_cluster_mid", &gtr100yb_cluster_mid, &b_gtr100yb_cluster_mid);
   fChain->SetBranchAddress("gtr100yb_cluster_y", &gtr100yb_cluster_y, &b_gtr100yb_cluster_y);
   fChain->SetBranchAddress("gtr100yb_cluster_adc", &gtr100yb_cluster_adc, &b_gtr100yb_cluster_adc);
   fChain->SetBranchAddress("gtr100yb_cluster_t", &gtr100yb_cluster_t, &b_gtr100yb_cluster_t);
   fChain->SetBranchAddress("gtr100yb_cluster_t2", &gtr100yb_cluster_t2, &b_gtr100yb_cluster_t2);
   fChain->SetBranchAddress("gtr100yb_cluster_ty", &gtr100yb_cluster_ty, &b_gtr100yb_cluster_ty);
   fChain->SetBranchAddress("gtr100yb_cluster_the", &gtr100yb_cluster_the, &b_gtr100yb_cluster_the);
   fChain->SetBranchAddress("gtr100yb_cluster_nc", &gtr100yb_cluster_nc, &b_gtr100yb_cluster_nc);
   fChain->SetBranchAddress("gtr100yb_cluster_size", &gtr100yb_cluster_size, &b_gtr100yb_cluster_size);
   fChain->SetBranchAddress("n_gtr200y_clusters", &n_gtr200y_clusters, &b_n_gtr200y_clusters);
   fChain->SetBranchAddress("gtr200y_cluster_id", &gtr200y_cluster_id, &b_gtr200y_cluster_id);
   fChain->SetBranchAddress("gtr200y_cluster_mid", &gtr200y_cluster_mid, &b_gtr200y_cluster_mid);
   fChain->SetBranchAddress("gtr200y_cluster_y", &gtr200y_cluster_y, &b_gtr200y_cluster_y);
   fChain->SetBranchAddress("gtr200y_cluster_adc", &gtr200y_cluster_adc, &b_gtr200y_cluster_adc);
   fChain->SetBranchAddress("gtr200y_cluster_t", &gtr200y_cluster_t, &b_gtr200y_cluster_t);
   fChain->SetBranchAddress("gtr200y_cluster_t2", &gtr200y_cluster_t2, &b_gtr200y_cluster_t2);
   fChain->SetBranchAddress("gtr200y_cluster_ty", &gtr200y_cluster_ty, &b_gtr200y_cluster_ty);
   fChain->SetBranchAddress("gtr200y_cluster_the", &gtr200y_cluster_the, &b_gtr200y_cluster_the);
   fChain->SetBranchAddress("gtr200y_cluster_nc", &gtr200y_cluster_nc, &b_gtr200y_cluster_nc);
   fChain->SetBranchAddress("gtr200y_cluster_size", &gtr200y_cluster_size, &b_gtr200y_cluster_size);
   fChain->SetBranchAddress("n_gtr300y_clusters", &n_gtr300y_clusters, &b_n_gtr300y_clusters);
   fChain->SetBranchAddress("gtr300y_cluster_id", &gtr300y_cluster_id, &b_gtr300y_cluster_id);
   fChain->SetBranchAddress("gtr300y_cluster_mid", &gtr300y_cluster_mid, &b_gtr300y_cluster_mid);
   fChain->SetBranchAddress("gtr300y_cluster_y", &gtr300y_cluster_y, &b_gtr300y_cluster_y);
   fChain->SetBranchAddress("gtr300y_cluster_adc", &gtr300y_cluster_adc, &b_gtr300y_cluster_adc);
   fChain->SetBranchAddress("gtr300y_cluster_t", &gtr300y_cluster_t, &b_gtr300y_cluster_t);
   fChain->SetBranchAddress("gtr300y_cluster_t2", &gtr300y_cluster_t2, &b_gtr300y_cluster_t2);
   fChain->SetBranchAddress("gtr300y_cluster_ty", &gtr300y_cluster_ty, &b_gtr300y_cluster_ty);
   fChain->SetBranchAddress("gtr300y_cluster_the", &gtr300y_cluster_the, &b_gtr300y_cluster_the);
   fChain->SetBranchAddress("gtr300y_cluster_nc", &gtr300y_cluster_nc, &b_gtr300y_cluster_nc);
   fChain->SetBranchAddress("gtr300y_cluster_size", &gtr300y_cluster_size, &b_gtr300y_cluster_size);
   fChain->SetBranchAddress("n_hbd_clusters", &n_hbd_clusters, &b_n_hbd_clusters);
   fChain->SetBranchAddress("hbd_cluster_id", &hbd_cluster_id, &b_hbd_cluster_id);
   fChain->SetBranchAddress("hbd_cluster_mid", &hbd_cluster_mid, &b_hbd_cluster_mid);
   fChain->SetBranchAddress("hbd_cluster_x", &hbd_cluster_x, &b_hbd_cluster_x);
   fChain->SetBranchAddress("hbd_cluster_y", &hbd_cluster_y, &b_hbd_cluster_y);
   fChain->SetBranchAddress("hbd_cluster_gx", &hbd_cluster_gx, &b_hbd_cluster_gx);
   fChain->SetBranchAddress("hbd_cluster_gy", &hbd_cluster_gy, &b_hbd_cluster_gy);
   fChain->SetBranchAddress("hbd_cluster_gz", &hbd_cluster_gz, &b_hbd_cluster_gz);
   fChain->SetBranchAddress("hbd_cluster_adc", &hbd_cluster_adc, &b_hbd_cluster_adc);
   fChain->SetBranchAddress("hbd_cluster_max_cid", &hbd_cluster_max_cid, &b_hbd_cluster_max_cid);
   fChain->SetBranchAddress("hbd_cluster_t", &hbd_cluster_t, &b_hbd_cluster_t);
   fChain->SetBranchAddress("hbd_cluster_ftime", &hbd_cluster_ftime, &b_hbd_cluster_ftime);
   fChain->SetBranchAddress("hbd_cluster_tdiff", &hbd_cluster_tdiff, &b_hbd_cluster_tdiff);
   fChain->SetBranchAddress("hbd_cluster_size", &hbd_cluster_size, &b_hbd_cluster_size);
   fChain->SetBranchAddress("hbd_cluster_eprob", &hbd_cluster_eprob, &b_hbd_cluster_eprob);
   fChain->SetBranchAddress("hbd_cluster_cprob", &hbd_cluster_cprob, &b_hbd_cluster_cprob);
   fChain->SetBranchAddress("n_hbd_clusters_wotime", &n_hbd_clusters_wotime, &b_n_hbd_clusters_wotime);
   fChain->SetBranchAddress("hbd_cluster_wotime_id", &hbd_cluster_wotime_id, &b_hbd_cluster_wotime_id);
   fChain->SetBranchAddress("hbd_cluster_wotime_mid", &hbd_cluster_wotime_mid, &b_hbd_cluster_wotime_mid);
   fChain->SetBranchAddress("hbd_cluster_wotime_x", &hbd_cluster_wotime_x, &b_hbd_cluster_wotime_x);
   fChain->SetBranchAddress("hbd_cluster_wotime_y", &hbd_cluster_wotime_y, &b_hbd_cluster_wotime_y);
   fChain->SetBranchAddress("hbd_cluster_wotime_gx", &hbd_cluster_wotime_gx, &b_hbd_cluster_wotime_gx);
   fChain->SetBranchAddress("hbd_cluster_wotime_gy", &hbd_cluster_wotime_gy, &b_hbd_cluster_wotime_gy);
   fChain->SetBranchAddress("hbd_cluster_wotime_gz", &hbd_cluster_wotime_gz, &b_hbd_cluster_wotime_gz);
   fChain->SetBranchAddress("hbd_cluster_wotime_adc", &hbd_cluster_wotime_adc, &b_hbd_cluster_wotime_adc);
   fChain->SetBranchAddress("hbd_cluster_wotime_max_cid", &hbd_cluster_wotime_max_cid, &b_hbd_cluster_wotime_max_cid);
   fChain->SetBranchAddress("hbd_cluster_wotime_t", &hbd_cluster_wotime_t, &b_hbd_cluster_wotime_t);
   fChain->SetBranchAddress("hbd_cluster_wotime_ftime", &hbd_cluster_wotime_ftime, &b_hbd_cluster_wotime_ftime);
   fChain->SetBranchAddress("hbd_cluster_wotime_tdiff", &hbd_cluster_wotime_tdiff, &b_hbd_cluster_wotime_tdiff);
   fChain->SetBranchAddress("hbd_cluster_wotime_size", &hbd_cluster_wotime_size, &b_hbd_cluster_wotime_size);
   fChain->SetBranchAddress("hbd_cluster_wotime_eprob", &hbd_cluster_wotime_eprob, &b_hbd_cluster_wotime_eprob);
   fChain->SetBranchAddress("hbd_cluster_wotime_cprob", &hbd_cluster_wotime_cprob, &b_hbd_cluster_wotime_cprob);
   fChain->SetBranchAddress("n_lg_hits", &n_lg_hits, &b_n_lg_hits);
   fChain->SetBranchAddress("lg_hit_id", &lg_hit_id, &b_lg_hit_id);
   fChain->SetBranchAddress("lg_hit_mid", &lg_hit_mid, &b_lg_hit_mid);
   fChain->SetBranchAddress("lg_hit_cid", &lg_hit_cid, &b_lg_hit_cid);
   fChain->SetBranchAddress("lg_hit_x", &lg_hit_x, &b_lg_hit_x);
   fChain->SetBranchAddress("lg_hit_y", &lg_hit_y, &b_lg_hit_y);
   fChain->SetBranchAddress("lg_hit_z", &lg_hit_z, &b_lg_hit_z);
   fChain->SetBranchAddress("lg_hit_gx", &lg_hit_gx, &b_lg_hit_gx);
   fChain->SetBranchAddress("lg_hit_gy", &lg_hit_gy, &b_lg_hit_gy);
   fChain->SetBranchAddress("lg_hit_gz", &lg_hit_gz, &b_lg_hit_gz);
   fChain->SetBranchAddress("lg_hit_adc", &lg_hit_adc, &b_lg_hit_adc);
   fChain->SetBranchAddress("lg_hit_t", &lg_hit_t, &b_lg_hit_t);
   fChain->SetBranchAddress("lg_hit_wofit_adc", &lg_hit_wofit_adc, &b_lg_hit_wofit_adc);
   fChain->SetBranchAddress("lg_hit_wofit_t", &lg_hit_wofit_t, &b_lg_hit_wofit_t);
   fChain->SetBranchAddress("lg_hit_npeaks", &lg_hit_npeaks, &b_lg_hit_npeaks);
   fChain->SetBranchAddress("lg_hit_fflag", &lg_hit_fflag, &b_lg_hit_fflag);
   fChain->SetBranchAddress("n_lg_clusters", &n_lg_clusters, &b_n_lg_clusters);
   fChain->SetBranchAddress("lg_cluster_id", &lg_cluster_id, &b_lg_cluster_id);
   fChain->SetBranchAddress("lg_cluster_mid", &lg_cluster_mid, &b_lg_cluster_mid);
   fChain->SetBranchAddress("lg_cluster_max_cid", &lg_cluster_max_cid, &b_lg_cluster_max_cid);
   fChain->SetBranchAddress("lg_cluster_max_adc", &lg_cluster_max_adc, &b_lg_cluster_max_adc);
   fChain->SetBranchAddress("lg_cluster_x", &lg_cluster_x, &b_lg_cluster_x);
   fChain->SetBranchAddress("lg_cluster_y", &lg_cluster_y, &b_lg_cluster_y);
   fChain->SetBranchAddress("lg_cluster_z", &lg_cluster_z, &b_lg_cluster_z);
   fChain->SetBranchAddress("lg_cluster_gx", &lg_cluster_gx, &b_lg_cluster_gx);
   fChain->SetBranchAddress("lg_cluster_gy", &lg_cluster_gy, &b_lg_cluster_gy);
   fChain->SetBranchAddress("lg_cluster_gz", &lg_cluster_gz, &b_lg_cluster_gz);
   fChain->SetBranchAddress("lg_cluster_adc", &lg_cluster_adc, &b_lg_cluster_adc);
   fChain->SetBranchAddress("lg_cluster_t", &lg_cluster_t, &b_lg_cluster_t);
   fChain->SetBranchAddress("lg_cluster_tdiff", &lg_cluster_tdiff, &b_lg_cluster_tdiff);
   fChain->SetBranchAddress("lg_cluster_size", &lg_cluster_size, &b_lg_cluster_size);
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








}
#endif

