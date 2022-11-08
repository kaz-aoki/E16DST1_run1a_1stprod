//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul 15 13:58:32 2022 by ROOT version 6.18/04
// from TTree tree/tree
// found on file: /work22/ichikawa/lsf_file/22070700-v2/root/run030717_0_000_ev0-999.root
//////////////////////////////////////////////////////////

#ifndef track_analyzer_220715_h
#define track_analyzer_220715_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"

#include "E16ANA_GeometryV2.hh"
#include "E16ANA_MagneticFieldMap.hh"
#include "E16ANA_MultiTrack.hh"
#include "E16ANA_StepTrack.hh"
#include "track_analyzer_220715_parameter.hh"

class track_analyzer_220715 {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

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

   // List of branches
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

   track_analyzer_220715(TTree *tree = 0, E16ANA_GeometryV2* _geometry = nullptr, E16ANA_MagneticFieldMap* _bfield_map = nullptr,
                         E16ANA_MultiTrack* _fitter = nullptr, E16ANA_MultiTrack* _proj_fitter = nullptr);
   virtual ~track_analyzer_220715();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(const TString& out_name);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
 private:
  struct EntryInfo {
    int entry_index;
    std::vector<int> track_indexs;
  };
  void MakeBranches(TTree* tree);
  void MakeEMBranches(TTree* tree);
  void ClearUsedClusterIDs();
  void SetHBDs();
  double NearestRadius(int n);
  bool HasAssociatedHBD(int mid, const TVector3& track_pos, double* min_res, std::vector<int>* _associated_hbd_indexs);
  bool HasAssociatedHBD(int n);
  bool HasUsedCluster(const std::array<int, track_analyzer_220715_parameter::kNumTrackingDetectors>& cids);
  bool IsGoodTrack(int n);
  void SetTracks();
  bool IsGoodPair(int n, int m);
  void SetPairs();
  void ClearAndResizeBranches();
  double CalcMass(int flag, const TVector3& pmom, const TVector3& mmom);
  void FillTVector3(int n, const TVector3& tvec, std::vector<double>* x, std::vector<double>* y, std::vector<double>* z);
  void FillTVector3(int n, const TVector3& tvec, std::vector<double>* x, std::vector<double>* y);
  void FillBranchesFromPairFit(int n, double chi2);
  int ModuleID2013(int m);
  int ChargeID(int c);
  void PairFit(int n);
  void FillBranchesFromStepTrack(int n, int flag, double dist_cm, const Hep3Vector& hep_vtx, const Hep3Vector& hep_plus_mom, const Hep3Vector& hep_minus_mom);
  void NearestPoint(int n);
  int DirID(int mid0, int mid1);
  int ModuleID2013_27(int m);
  void ProjectionHBDAndLG(int n);
  void ProjectionTargets(int n);
//  int BestTargetID(int n);
//  void ParentInfo(int n);
  int BestTargetID(double vtx_z, const std::array<TVector3, track_analyzer_220715_parameter::kNumTgts>& tgt_poss,
                   std::array<double, track_analyzer_220715_parameter::kNumTgts>* flight_paths,
                   double* best_tgt_r, int* good_tgt_id_set, std::vector<double>* good_tgt_ids);
  TVector3 Xo0Pos(const TVector3& pos, const TVector3& mom);
  void ParentInfo(const TVector3& vtx, const std::array<TVector3, 2>& moms, TVector3* parent_mom,
                  std::array<TVector3, track_analyzer_220715_parameter::kNumTgts>* tgt_poss,
                  std::array<double, track_analyzer_220715_parameter::kNumTgts>* flight_paths,
                  int* best_tgt_id, double* best_tgt_r, int* good_tgt_id_set, std::vector<double>* good_tgt_ids, TVector3* x0_pos);
  void ParentInfo(int n);
  void AssociatedHBD(int n);
  int SimpleBestTargetID(int n, double* r);
  void SimpleAnalysis(int n);
  void TmpProjectionX0(int n);
  void FillCommonBranches();
  void Analyze();
  void FillEntryInfo(int entry_index, track_analyzer_220715::EntryInfo* plus_entry, track_analyzer_220715::EntryInfo* minus_entry);
  void ClearEMBranches();
  void PairFitEM(int plus_entry_index, int plus_track_index, int minus_entry_index, int minus_track_index);
  void NearestPointEM(int plus_entry_index, int plus_track_index, int minus_entry_index, int minus_track_index);
  void DirIDsEM();
  void ParentInfoEM();
  void EventMixing(const track_analyzer_220715::EntryInfo& plus_entry, const track_analyzer_220715::EntryInfo& minus_entry);
  int SimpleBestTargetIDEM(int n, double* r);
  void SimpleAnalysisEM();
  void UpdatePastEntries(const track_analyzer_220715::EntryInfo& plus_entry, const track_analyzer_220715::EntryInfo& minus_entry);
  void AnalyzeEM(int entry_index);
  // Analyze class
  E16ANA_GeometryV2*       geometry;
  E16ANA_MagneticFieldMap* bfield_map;
  E16ANA_MultiTrack*       fitter;
  E16ANA_MultiTrack*       proj_fitter;
  //
  std::array<std::vector<int>, track_analyzer_220715_parameter::kNumModules> hbd_indexs;
//  std::array<std::array<std::vector<int>, track_analyzer_220715_parameter::kNumLGTypes>, track_analyzer_220715_parameter::kNumModules> lg_indexs;
  std::vector<int> good_track_indexs;
  std::vector<std::array<int, 2>> good_pair_indexs;
  std::vector<std::vector<int>> associated_hbd_indexs;
  std::vector<int>    nearest_tgt_ids;
  std::vector<double> nearest_radius;
  std::array<std::vector<int>, track_analyzer_220715_parameter::kNumTrackingDetectors> used_cluster_ids;
  std::vector<EntryInfo> past_plus_entries;
  std::vector<EntryInfo> past_minus_entries;
  // Tree branch
  int out_n_pairs;
// single fit info. chi2, ...
  std::vector<double> out_plus_rough_fit_init_pos_x;
  std::vector<double> out_plus_rough_fit_init_pos_y;
  std::vector<double> out_plus_rough_fit_init_pos_z;
  std::vector<double> out_plus_rough_fit_init_mom_x;
  std::vector<double> out_plus_rough_fit_init_mom_y;
  std::vector<double> out_plus_rough_fit_init_mom_z;
  std::vector<double> out_minus_rough_fit_init_pos_x;
  std::vector<double> out_minus_rough_fit_init_pos_y;
  std::vector<double> out_minus_rough_fit_init_pos_z;
  std::vector<double> out_minus_rough_fit_init_mom_x;
  std::vector<double> out_minus_rough_fit_init_mom_y;
  std::vector<double> out_minus_rough_fit_init_mom_z;
  std::vector<double> out_plus_single_fit_init_pos_x;
  std::vector<double> out_plus_single_fit_init_pos_y;
  std::vector<double> out_plus_single_fit_init_pos_z;
  std::vector<double> out_plus_single_fit_init_mom_x;
  std::vector<double> out_plus_single_fit_init_mom_y;
  std::vector<double> out_plus_single_fit_init_mom_z;
  std::vector<double> out_minus_single_fit_init_pos_x;
  std::vector<double> out_minus_single_fit_init_pos_y;
  std::vector<double> out_minus_single_fit_init_pos_z;
  std::vector<double> out_minus_single_fit_init_mom_x;
  std::vector<double> out_minus_single_fit_init_mom_y;
  std::vector<double> out_minus_single_fit_init_mom_z;
  // Hit
  std::vector<int>    out_plus_track_id;
  std::vector<int>    out_plus_charge_id;
  std::vector<int>    out_hit_plus_ssd_id;
  std::vector<double> out_hit_plus_ssd_lx;
  std::vector<double> out_hit_plus_ssd_t;
  std::vector<double> out_hit_plus_ssd_adc;
  std::vector<int>    out_hit_plus_ssd_size;
  std::vector<int>    out_hit_plus_gtr100_xid;
  std::vector<int>    out_hit_plus_gtr100_yid;
  std::vector<double> out_hit_plus_gtr100_lx;
  std::vector<double> out_hit_plus_gtr100_ly;
  std::vector<double> out_hit_plus_gtr100_xt;
  std::vector<double> out_hit_plus_gtr100_yt;
  std::vector<double> out_hit_plus_gtr100_xadc;
  std::vector<double> out_hit_plus_gtr100_yadc;
  std::vector<int>    out_hit_plus_gtr100_xsize;
  std::vector<int>    out_hit_plus_gtr100_ysize;
  std::vector<int>    out_hit_plus_gtr200_xid;
  std::vector<int>    out_hit_plus_gtr200_yid;
  std::vector<double> out_hit_plus_gtr200_lx;
  std::vector<double> out_hit_plus_gtr200_ly;
  std::vector<double> out_hit_plus_gtr200_xt;
  std::vector<double> out_hit_plus_gtr200_yt;
  std::vector<double> out_hit_plus_gtr200_xadc;
  std::vector<double> out_hit_plus_gtr200_yadc;
  std::vector<int>    out_hit_plus_gtr200_xsize;
  std::vector<int>    out_hit_plus_gtr200_ysize;
  std::vector<int>    out_hit_plus_gtr300_xid;
  std::vector<int>    out_hit_plus_gtr300_yid;
  std::vector<double> out_hit_plus_gtr300_lx;
  std::vector<double> out_hit_plus_gtr300_ly;
  std::vector<double> out_hit_plus_gtr300_xt;
  std::vector<double> out_hit_plus_gtr300_yt;
  std::vector<double> out_hit_plus_gtr300_xadc;
  std::vector<double> out_hit_plus_gtr300_yadc;
  std::vector<int>    out_hit_plus_gtr300_xsize;
  std::vector<int>    out_hit_plus_gtr300_ysize;
  std::vector<int>    out_minus_track_id;
  std::vector<int>    out_minus_charge_id;
  std::vector<int>    out_hit_minus_ssd_id;
  std::vector<double> out_hit_minus_ssd_lx;
  std::vector<double> out_hit_minus_ssd_t;
  std::vector<double> out_hit_minus_ssd_adc;
  std::vector<int>    out_hit_minus_ssd_size;
  std::vector<int>    out_hit_minus_gtr100_xid;
  std::vector<int>    out_hit_minus_gtr100_yid;
  std::vector<double> out_hit_minus_gtr100_lx;
  std::vector<double> out_hit_minus_gtr100_ly;
  std::vector<double> out_hit_minus_gtr100_xt;
  std::vector<double> out_hit_minus_gtr100_yt;
  std::vector<double> out_hit_minus_gtr100_xadc;
  std::vector<double> out_hit_minus_gtr100_yadc;
  std::vector<int>    out_hit_minus_gtr100_xsize;
  std::vector<int>    out_hit_minus_gtr100_ysize;
  std::vector<int>    out_hit_minus_gtr200_xid;
  std::vector<int>    out_hit_minus_gtr200_yid;
  std::vector<double> out_hit_minus_gtr200_lx;
  std::vector<double> out_hit_minus_gtr200_ly;
  std::vector<double> out_hit_minus_gtr200_xt;
  std::vector<double> out_hit_minus_gtr200_yt;
  std::vector<double> out_hit_minus_gtr200_xadc;
  std::vector<double> out_hit_minus_gtr200_yadc;
  std::vector<int>    out_hit_minus_gtr200_xsize;
  std::vector<int>    out_hit_minus_gtr200_ysize;
  std::vector<int>    out_hit_minus_gtr300_xid;
  std::vector<int>    out_hit_minus_gtr300_yid;
  std::vector<double> out_hit_minus_gtr300_lx;
  std::vector<double> out_hit_minus_gtr300_ly;
  std::vector<double> out_hit_minus_gtr300_xt;
  std::vector<double> out_hit_minus_gtr300_yt;
  std::vector<double> out_hit_minus_gtr300_xadc;
  std::vector<double> out_hit_minus_gtr300_yadc;
  std::vector<int>    out_hit_minus_gtr300_xsize;
  std::vector<int>    out_hit_minus_gtr300_ysize;
  // Fit
  std::vector<double> out_chi2;
  std::vector<double> out_plus_chi2;
  std::vector<double> out_minus_chi2;
  std::vector<int>    out_flag;
  std::vector<double> out_distance;
  std::vector<int>    out_plus_nearest_tgt_id; // must be update for pair fit
  std::vector<double> out_plus_nearest_radius; // must be update for pair fit
  std::vector<int>    out_minus_nearest_tgt_id; // must be update for pair fit
  std::vector<double> out_minus_nearest_radius; // must be update for pair fit
  std::vector<int>    out_dir_id;
  std::vector<double> out_vtx_x;
  std::vector<double> out_vtx_y;
  std::vector<double> out_vtx_z;
  std::vector<double> out_plus_mom;
  std::vector<double> out_plus_mom_x;
  std::vector<double> out_plus_mom_y;
  std::vector<double> out_plus_mom_z;
  std::vector<double> out_plus_mom_theta;
  std::vector<double> out_plus_mom_phi;
  std::vector<double> out_minus_mom;
  std::vector<double> out_minus_mom_x;
  std::vector<double> out_minus_mom_y;
  std::vector<double> out_minus_mom_z;
  std::vector<double> out_minus_mom_theta;
  std::vector<double> out_minus_mom_phi;
  std::vector<double> out_mom_angle;
  std::vector<double> out_ee_mass;
  std::vector<double> out_pipi_mass;
  std::vector<double> out_pip_mass;
  std::vector<double> out_kk_mass;
  std::vector<int>    out_simple_best_tgt_id;
  std::vector<double> out_simple_best_tgt_r;
  std::vector<double> out_ee_mass_at_best_tgt;
  std::vector<double> out_pipi_mass_at_best_tgt;
  std::vector<double> out_pip_mass_at_best_tgt;
  std::vector<double> out_kk_mass_at_best_tgt;
  std::vector<int>    out_plus_ssd_mid;
  std::vector<int>    out_plus_gtr100_mid;
  std::vector<int>    out_plus_gtr200_mid;
  std::vector<int>    out_plus_gtr300_mid;
  std::vector<int>    out_plus_hbd_mid;
  std::vector<int>    out_plus_lg_c_mid;
  std::vector<int>    out_plus_lg_b_mid;
  std::vector<int>    out_plus_lg_a_mid;
  std::vector<int>    out_minus_ssd_mid;
  std::vector<int>    out_minus_gtr100_mid;
  std::vector<int>    out_minus_gtr200_mid;
  std::vector<int>    out_minus_gtr300_mid;
  std::vector<int>    out_minus_hbd_mid;
  std::vector<int>    out_minus_lg_c_mid;
  std::vector<int>    out_minus_lg_b_mid;
  std::vector<int>    out_minus_lg_a_mid;
  std::vector<double> out_fit_plus_ssd_lx;
  std::vector<double> out_fit_plus_ssd_ly;
  std::vector<double> out_fit_plus_gtr100_lx;
  std::vector<double> out_fit_plus_gtr100_ly;
  std::vector<double> out_fit_plus_gtr200_lx;
  std::vector<double> out_fit_plus_gtr200_ly;
  std::vector<double> out_fit_plus_gtr300_lx;
  std::vector<double> out_fit_plus_gtr300_ly;
  std::vector<double> out_fit_plus_hbd_lx;
  std::vector<double> out_fit_plus_hbd_ly;
  std::vector<double> out_fit_plus_lg_c_lx;
  std::vector<double> out_fit_plus_lg_c_ly;
  std::vector<double> out_fit_plus_lg_b_lx;
  std::vector<double> out_fit_plus_lg_b_ly;
  std::vector<double> out_fit_plus_lg_a_lx;
  std::vector<double> out_fit_plus_lg_a_ly;
  std::vector<double> out_fit_plus_tgt_minus_x;
  std::vector<double> out_fit_plus_tgt_minus_y;
  std::vector<double> out_fit_plus_tgt_zero_x;
  std::vector<double> out_fit_plus_tgt_zero_y;
  std::vector<double> out_fit_plus_tgt_plus_x;
  std::vector<double> out_fit_plus_tgt_plus_y;
  std::vector<double> out_fit_plus_x0_y;
  std::vector<double> out_fit_plus_x0_z;
  std::vector<double> out_fit_minus_ssd_lx;
  std::vector<double> out_fit_minus_ssd_ly;
  std::vector<double> out_fit_minus_gtr100_lx;
  std::vector<double> out_fit_minus_gtr100_ly;
  std::vector<double> out_fit_minus_gtr200_lx;
  std::vector<double> out_fit_minus_gtr200_ly;
  std::vector<double> out_fit_minus_gtr300_lx;
  std::vector<double> out_fit_minus_gtr300_ly;
  std::vector<double> out_fit_minus_hbd_lx;
  std::vector<double> out_fit_minus_hbd_ly;
  std::vector<double> out_fit_minus_lg_c_lx;
  std::vector<double> out_fit_minus_lg_c_ly;
  std::vector<double> out_fit_minus_lg_b_lx;
  std::vector<double> out_fit_minus_lg_b_ly;
  std::vector<double> out_fit_minus_lg_a_lx;
  std::vector<double> out_fit_minus_lg_a_ly;
  std::vector<double> out_fit_minus_tgt_minus_x;
  std::vector<double> out_fit_minus_tgt_minus_y;
  std::vector<double> out_fit_minus_tgt_zero_x;
  std::vector<double> out_fit_minus_tgt_zero_y;
  std::vector<double> out_fit_minus_tgt_plus_x;
  std::vector<double> out_fit_minus_tgt_plus_y;
  std::vector<double> out_fit_minus_x0_y;
  std::vector<double> out_fit_minus_x0_z;
  std::vector<double> out_fit_plus_ssd_mom_lx;
  std::vector<double> out_fit_plus_ssd_mom_ly;
  std::vector<double> out_fit_plus_ssd_mom_lz;
  std::vector<double> out_fit_plus_ssd_mom_gx;
  std::vector<double> out_fit_plus_ssd_mom_gy;
  std::vector<double> out_fit_plus_ssd_mom_gz;
  std::vector<double> out_fit_plus_gtr100_mom_lx;
  std::vector<double> out_fit_plus_gtr100_mom_ly;
  std::vector<double> out_fit_plus_gtr100_mom_lz;
  std::vector<double> out_fit_plus_gtr100_mom_gx;
  std::vector<double> out_fit_plus_gtr100_mom_gy;
  std::vector<double> out_fit_plus_gtr100_mom_gz;
  std::vector<double> out_fit_plus_gtr200_mom_lx;
  std::vector<double> out_fit_plus_gtr200_mom_ly;
  std::vector<double> out_fit_plus_gtr200_mom_lz;
  std::vector<double> out_fit_plus_gtr200_mom_gx;
  std::vector<double> out_fit_plus_gtr200_mom_gy;
  std::vector<double> out_fit_plus_gtr200_mom_gz;
  std::vector<double> out_fit_plus_gtr300_mom_lx;
  std::vector<double> out_fit_plus_gtr300_mom_ly;
  std::vector<double> out_fit_plus_gtr300_mom_lz;
  std::vector<double> out_fit_plus_gtr300_mom_gx;
  std::vector<double> out_fit_plus_gtr300_mom_gy;
  std::vector<double> out_fit_plus_gtr300_mom_gz;
  std::vector<double> out_fit_plus_hbd_mom_lx;
  std::vector<double> out_fit_plus_hbd_mom_ly;
  std::vector<double> out_fit_plus_hbd_mom_lz;
  std::vector<double> out_fit_plus_hbd_mom_gx;
  std::vector<double> out_fit_plus_hbd_mom_gy;
  std::vector<double> out_fit_plus_hbd_mom_gz;
  std::vector<double> out_fit_plus_lg_c_mom_lx;
  std::vector<double> out_fit_plus_lg_c_mom_ly;
  std::vector<double> out_fit_plus_lg_c_mom_lz;
  std::vector<double> out_fit_plus_lg_c_mom_gx;
  std::vector<double> out_fit_plus_lg_c_mom_gy;
  std::vector<double> out_fit_plus_lg_c_mom_gz;
  std::vector<double> out_fit_plus_lg_b_mom_lx;
  std::vector<double> out_fit_plus_lg_b_mom_ly;
  std::vector<double> out_fit_plus_lg_b_mom_lz;
  std::vector<double> out_fit_plus_lg_b_mom_gx;
  std::vector<double> out_fit_plus_lg_b_mom_gy;
  std::vector<double> out_fit_plus_lg_b_mom_gz;
  std::vector<double> out_fit_plus_lg_a_mom_lx;
  std::vector<double> out_fit_plus_lg_a_mom_ly;
  std::vector<double> out_fit_plus_lg_a_mom_lz;
  std::vector<double> out_fit_plus_lg_a_mom_gx;
  std::vector<double> out_fit_plus_lg_a_mom_gy;
  std::vector<double> out_fit_plus_lg_a_mom_gz;
  std::vector<double> out_fit_plus_tgt_minus_mom_x;
  std::vector<double> out_fit_plus_tgt_minus_mom_y;
  std::vector<double> out_fit_plus_tgt_minus_mom_z;
  std::vector<double> out_fit_plus_tgt_zero_mom_x;
  std::vector<double> out_fit_plus_tgt_zero_mom_y;
  std::vector<double> out_fit_plus_tgt_zero_mom_z;
  std::vector<double> out_fit_plus_tgt_plus_mom_x;
  std::vector<double> out_fit_plus_tgt_plus_mom_y;
  std::vector<double> out_fit_plus_tgt_plus_mom_z;
  std::vector<double> out_fit_minus_ssd_mom_lx;
  std::vector<double> out_fit_minus_ssd_mom_ly;
  std::vector<double> out_fit_minus_ssd_mom_lz;
  std::vector<double> out_fit_minus_ssd_mom_gx;
  std::vector<double> out_fit_minus_ssd_mom_gy;
  std::vector<double> out_fit_minus_ssd_mom_gz;
  std::vector<double> out_fit_minus_gtr100_mom_lx;
  std::vector<double> out_fit_minus_gtr100_mom_ly;
  std::vector<double> out_fit_minus_gtr100_mom_lz;
  std::vector<double> out_fit_minus_gtr100_mom_gx;
  std::vector<double> out_fit_minus_gtr100_mom_gy;
  std::vector<double> out_fit_minus_gtr100_mom_gz;
  std::vector<double> out_fit_minus_gtr200_mom_lx;
  std::vector<double> out_fit_minus_gtr200_mom_ly;
  std::vector<double> out_fit_minus_gtr200_mom_lz;
  std::vector<double> out_fit_minus_gtr200_mom_gx;
  std::vector<double> out_fit_minus_gtr200_mom_gy;
  std::vector<double> out_fit_minus_gtr200_mom_gz;
  std::vector<double> out_fit_minus_gtr300_mom_lx;
  std::vector<double> out_fit_minus_gtr300_mom_ly;
  std::vector<double> out_fit_minus_gtr300_mom_lz;
  std::vector<double> out_fit_minus_gtr300_mom_gx;
  std::vector<double> out_fit_minus_gtr300_mom_gy;
  std::vector<double> out_fit_minus_gtr300_mom_gz;
  std::vector<double> out_fit_minus_hbd_mom_lx;
  std::vector<double> out_fit_minus_hbd_mom_ly;
  std::vector<double> out_fit_minus_hbd_mom_lz;
  std::vector<double> out_fit_minus_hbd_mom_gx;
  std::vector<double> out_fit_minus_hbd_mom_gy;
  std::vector<double> out_fit_minus_hbd_mom_gz;
  std::vector<double> out_fit_minus_lg_c_mom_lx;
  std::vector<double> out_fit_minus_lg_c_mom_ly;
  std::vector<double> out_fit_minus_lg_c_mom_lz;
  std::vector<double> out_fit_minus_lg_c_mom_gx;
  std::vector<double> out_fit_minus_lg_c_mom_gy;
  std::vector<double> out_fit_minus_lg_c_mom_gz;
  std::vector<double> out_fit_minus_lg_b_mom_lx;
  std::vector<double> out_fit_minus_lg_b_mom_ly;
  std::vector<double> out_fit_minus_lg_b_mom_lz;
  std::vector<double> out_fit_minus_lg_b_mom_gx;
  std::vector<double> out_fit_minus_lg_b_mom_gy;
  std::vector<double> out_fit_minus_lg_b_mom_gz;
  std::vector<double> out_fit_minus_lg_a_mom_lx;
  std::vector<double> out_fit_minus_lg_a_mom_ly;
  std::vector<double> out_fit_minus_lg_a_mom_lz;
  std::vector<double> out_fit_minus_lg_a_mom_gx;
  std::vector<double> out_fit_minus_lg_a_mom_gy;
  std::vector<double> out_fit_minus_lg_a_mom_gz;
  std::vector<double> out_fit_minus_tgt_minus_mom_x;
  std::vector<double> out_fit_minus_tgt_minus_mom_y;
  std::vector<double> out_fit_minus_tgt_minus_mom_z;
  std::vector<double> out_fit_minus_tgt_zero_mom_x;
  std::vector<double> out_fit_minus_tgt_zero_mom_y;
  std::vector<double> out_fit_minus_tgt_zero_mom_z;
  std::vector<double> out_fit_minus_tgt_plus_mom_x;
  std::vector<double> out_fit_minus_tgt_plus_mom_y;
  std::vector<double> out_fit_minus_tgt_plus_mom_z;
// gpos...
  std::vector<double> out_res_plus_ssd_lx;
//  std::vector<double> out_res_plus_ssd_ly;
  std::vector<double> out_res_plus_gtr100_lx;
  std::vector<double> out_res_plus_gtr100_ly;
  std::vector<double> out_res_plus_gtr200_lx;
  std::vector<double> out_res_plus_gtr200_ly;
  std::vector<double> out_res_plus_gtr300_lx;
  std::vector<double> out_res_plus_gtr300_ly;
  std::vector<double> out_res_minus_ssd_lx;
//  std::vector<double> out_res_minus_ssd_ly;
  std::vector<double> out_res_minus_gtr100_lx;
  std::vector<double> out_res_minus_gtr100_ly;
  std::vector<double> out_res_minus_gtr200_lx;
  std::vector<double> out_res_minus_gtr200_ly;
  std::vector<double> out_res_minus_gtr300_lx;
  std::vector<double> out_res_minus_gtr300_ly;
  std::vector<double>              out_fit_parent_mom;
  std::vector<double>              out_fit_parent_mom_x;
  std::vector<double>              out_fit_parent_mom_y;
  std::vector<double>              out_fit_parent_mom_z;
  std::vector<double>              out_fit_parent_mom_theta;
  std::vector<double>              out_fit_parent_mom_phi;
  std::vector<double>              out_fit_parent_tgt_minus_x;
  std::vector<double>              out_fit_parent_tgt_minus_y;
  std::vector<double>              out_fit_parent_tgt_minus_flight_path;
  std::vector<double>              out_fit_parent_tgt_zero_x;
  std::vector<double>              out_fit_parent_tgt_zero_y;
  std::vector<double>              out_fit_parent_tgt_zero_flight_path;
  std::vector<double>              out_fit_parent_tgt_plus_x;
  std::vector<double>              out_fit_parent_tgt_plus_y;
  std::vector<double>              out_fit_parent_tgt_plus_flight_path;
  std::vector<int>                 out_fit_parent_best_tgt_id;
  std::vector<double>              out_fit_parent_best_tgt_r;
  std::vector<int>                 out_fit_parent_good_tgt_id_set;
  std::vector<std::vector<double>> out_fit_parent_good_tgt_ids;
  std::vector<double>              out_fit_parent_x0_y;
  std::vector<double>              out_fit_parent_x0_z;
  // HBD Projection
  std::vector<double>              out_proj_plus_n_hbds;
  std::vector<double>              out_proj_plus_hbd_min_res;
  std::vector<std::vector<double>> out_proj_plus_hbd_id;
  std::vector<std::vector<double>> out_proj_plus_hbd_lx;
  std::vector<std::vector<double>> out_proj_plus_hbd_ly;
  std::vector<std::vector<double>> out_proj_plus_hbd_resx;
  std::vector<std::vector<double>> out_proj_plus_hbd_resy;
  std::vector<std::vector<double>> out_proj_plus_hbd_adc;
  std::vector<std::vector<double>> out_proj_plus_hbd_size;
  std::vector<std::vector<double>> out_proj_plus_hbd_eprob;
  std::vector<double>              out_proj_minus_n_hbds;
  std::vector<double>              out_proj_minus_hbd_min_res;
  std::vector<std::vector<double>> out_proj_minus_hbd_id;
  std::vector<std::vector<double>> out_proj_minus_hbd_lx;
  std::vector<std::vector<double>> out_proj_minus_hbd_ly;
  std::vector<std::vector<double>> out_proj_minus_hbd_resx;
  std::vector<std::vector<double>> out_proj_minus_hbd_resy;
  std::vector<std::vector<double>> out_proj_minus_hbd_adc;
  std::vector<std::vector<double>> out_proj_minus_hbd_size;
  std::vector<std::vector<double>> out_proj_minus_hbd_eprob;
  // LG Projection
std::vector<int>                 out_tmp_fit_plus_x0_flag;
std::vector<std::vector<double>> out_tmp_fit_plus_x0_pos_y;
std::vector<std::vector<double>> out_tmp_fit_plus_x0_pos_z;
std::vector<std::vector<double>> out_tmp_fit_plus_x0_mom_x;
std::vector<std::vector<double>> out_tmp_fit_plus_x0_mom_y;
std::vector<std::vector<double>> out_tmp_fit_plus_x0_mom_z;
std::vector<int>                 out_tmp_fit_minus_x0_flag;
std::vector<std::vector<double>> out_tmp_fit_minus_x0_pos_y;
std::vector<std::vector<double>> out_tmp_fit_minus_x0_pos_z;
std::vector<std::vector<double>> out_tmp_fit_minus_x0_mom_x;
std::vector<std::vector<double>> out_tmp_fit_minus_x0_mom_y;
std::vector<std::vector<double>> out_tmp_fit_minus_x0_mom_z;
  // Event Mixing 
  std::vector<int> em_plus_run_id;
  std::vector<int> em_plus_event_id;
  std::vector<int> em_plus_n_cands;
//  std::vector<int> em_plus_n_pairs;
  std::vector<int> em_plus_track_id;
  std::vector<int> em_minus_run_id;
  std::vector<int> em_minus_event_id;
  std::vector<int> em_minus_n_cands;
//  std::vector<int> em_minus_n_pairs;
  std::vector<int> em_minus_track_id;
//// single fit info. chi2, ...
//  // Hit
//  std::vector<int>    out_plus_track_id;
//  std::vector<int>    out_hit_plus_ssd_id;
//  std::vector<double> out_hit_plus_ssd_lx;
//  std::vector<double> out_hit_plus_ssd_t;
//  std::vector<double> out_hit_plus_ssd_adc;
//  std::vector<int>    out_hit_plus_ssd_size;
//  std::vector<int>    out_hit_plus_gtr100_xid;
//  std::vector<int>    out_hit_plus_gtr100_yid;
//  std::vector<double> out_hit_plus_gtr100_lx;
//  std::vector<double> out_hit_plus_gtr100_ly;
//  std::vector<double> out_hit_plus_gtr100_xt;
//  std::vector<double> out_hit_plus_gtr100_yt;
//  std::vector<double> out_hit_plus_gtr100_xadc;
//  std::vector<double> out_hit_plus_gtr100_yadc;
//  std::vector<int>    out_hit_plus_gtr100_xsize;
//  std::vector<int>    out_hit_plus_gtr100_ysize;
//  std::vector<int>    out_hit_plus_gtr200_xid;
//  std::vector<int>    out_hit_plus_gtr200_yid;
//  std::vector<double> out_hit_plus_gtr200_lx;
//  std::vector<double> out_hit_plus_gtr200_ly;
//  std::vector<double> out_hit_plus_gtr200_xt;
//  std::vector<double> out_hit_plus_gtr200_yt;
//  std::vector<double> out_hit_plus_gtr200_xadc;
//  std::vector<double> out_hit_plus_gtr200_yadc;
//  std::vector<int>    out_hit_plus_gtr200_xsize;
//  std::vector<int>    out_hit_plus_gtr200_ysize;
//  std::vector<int>    out_hit_plus_gtr300_xid;
//  std::vector<int>    out_hit_plus_gtr300_yid;
//  std::vector<double> out_hit_plus_gtr300_lx;
//  std::vector<double> out_hit_plus_gtr300_ly;
//  std::vector<double> out_hit_plus_gtr300_xt;
//  std::vector<double> out_hit_plus_gtr300_yt;
//  std::vector<double> out_hit_plus_gtr300_xadc;
//  std::vector<double> out_hit_plus_gtr300_yadc;
//  std::vector<int>    out_hit_plus_gtr300_xsize;
//  std::vector<int>    out_hit_plus_gtr300_ysize;
//  std::vector<int>    out_minus_track_id;
//  std::vector<int>    out_hit_minus_ssd_id;
//  std::vector<double> out_hit_minus_ssd_lx;
//  std::vector<double> out_hit_minus_ssd_t;
//  std::vector<double> out_hit_minus_ssd_adc;
//  std::vector<int>    out_hit_minus_ssd_size;
//  std::vector<int>    out_hit_minus_gtr100_xid;
//  std::vector<int>    out_hit_minus_gtr100_yid;
//  std::vector<double> out_hit_minus_gtr100_lx;
//  std::vector<double> out_hit_minus_gtr100_ly;
//  std::vector<double> out_hit_minus_gtr100_xt;
//  std::vector<double> out_hit_minus_gtr100_yt;
//  std::vector<double> out_hit_minus_gtr100_xadc;
//  std::vector<double> out_hit_minus_gtr100_yadc;
//  std::vector<int>    out_hit_minus_gtr100_xsize;
//  std::vector<int>    out_hit_minus_gtr100_ysize;
//  std::vector<int>    out_hit_minus_gtr200_xid;
//  std::vector<int>    out_hit_minus_gtr200_yid;
//  std::vector<double> out_hit_minus_gtr200_lx;
//  std::vector<double> out_hit_minus_gtr200_ly;
//  std::vector<double> out_hit_minus_gtr200_xt;
//  std::vector<double> out_hit_minus_gtr200_yt;
//  std::vector<double> out_hit_minus_gtr200_xadc;
//  std::vector<double> out_hit_minus_gtr200_yadc;
//  std::vector<int>    out_hit_minus_gtr200_xsize;
//  std::vector<int>    out_hit_minus_gtr200_ysize;
//  std::vector<int>    out_hit_minus_gtr300_xid;
//  std::vector<int>    out_hit_minus_gtr300_yid;
//  std::vector<double> out_hit_minus_gtr300_lx;
//  std::vector<double> out_hit_minus_gtr300_ly;
//  std::vector<double> out_hit_minus_gtr300_xt;
//  std::vector<double> out_hit_minus_gtr300_yt;
//  std::vector<double> out_hit_minus_gtr300_xadc;
//  std::vector<double> out_hit_minus_gtr300_yadc;
//  std::vector<int>    out_hit_minus_gtr300_xsize;
//  std::vector<int>    out_hit_minus_gtr300_ysize;
  // Fit
  std::vector<double> em_chi2;
  std::vector<double> em_plus_chi2;
  std::vector<double> em_minus_chi2;
  std::vector<int>    em_flag;
  std::vector<double> em_distance;
  std::vector<int>    em_dir_id;
  std::vector<double> em_vtx_x;
  std::vector<double> em_vtx_y;
  std::vector<double> em_vtx_z;
  std::vector<double> em_plus_mom;
  std::vector<double> em_plus_mom_x;
  std::vector<double> em_plus_mom_y;
  std::vector<double> em_plus_mom_z;
  std::vector<double> em_plus_mom_theta;
  std::vector<double> em_plus_mom_phi;
  std::vector<double> em_minus_mom;
  std::vector<double> em_minus_mom_x;
  std::vector<double> em_minus_mom_y;
  std::vector<double> em_minus_mom_z;
  std::vector<double> em_minus_mom_theta;
  std::vector<double> em_minus_mom_phi;
  std::vector<double> em_mom_angle;
  std::vector<double> em_ee_mass;
  std::vector<double> em_pipi_mass;
  std::vector<double> em_pip_mass;
  std::vector<double> em_kk_mass;
  std::vector<int>    em_simple_best_tgt_id;
  std::vector<double> em_simple_best_tgt_r;
  std::vector<double> em_ee_mass_at_best_tgt;
  std::vector<double> em_pipi_mass_at_best_tgt;
  std::vector<double> em_pip_mass_at_best_tgt;
  std::vector<double> em_kk_mass_at_best_tgt;
  std::vector<int>    em_plus_ssd_mid;
  std::vector<int>    em_plus_gtr100_mid;
  std::vector<int>    em_plus_gtr200_mid;
  std::vector<int>    em_plus_gtr300_mid;
  std::vector<int>    em_plus_hbd_mid;
  std::vector<int>    em_plus_lg_c_mid;
  std::vector<int>    em_plus_lg_b_mid;
  std::vector<int>    em_plus_lg_a_mid;
  std::vector<int>    em_minus_ssd_mid;
  std::vector<int>    em_minus_gtr100_mid;
  std::vector<int>    em_minus_gtr200_mid;
  std::vector<int>    em_minus_gtr300_mid;
  std::vector<int>    em_minus_hbd_mid;
  std::vector<int>    em_minus_lg_c_mid;
  std::vector<int>    em_minus_lg_b_mid;
  std::vector<int>    em_minus_lg_a_mid;
//  std::vector<double> out_fit_plus_ssd_lx;
//  std::vector<double> out_fit_plus_ssd_ly;
//  std::vector<double> out_fit_plus_gtr100_lx;
//  std::vector<double> out_fit_plus_gtr100_ly;
//  std::vector<double> out_fit_plus_gtr200_lx;
//  std::vector<double> out_fit_plus_gtr200_ly;
//  std::vector<double> out_fit_plus_gtr300_lx;
//  std::vector<double> out_fit_plus_gtr300_ly;
//  std::vector<double> out_fit_plus_hbd_lx;
//  std::vector<double> out_fit_plus_hbd_ly;
//  std::vector<double> out_fit_plus_lg_c_lx;
//  std::vector<double> out_fit_plus_lg_c_ly;
//  std::vector<double> out_fit_plus_lg_b_lx;
//  std::vector<double> out_fit_plus_lg_b_ly;
//  std::vector<double> out_fit_plus_lg_a_lx;
//  std::vector<double> out_fit_plus_lg_a_ly;
  std::vector<double> em_fit_plus_tgt_minus_x;
  std::vector<double> em_fit_plus_tgt_minus_y;
  std::vector<double> em_fit_plus_tgt_zero_x;
  std::vector<double> em_fit_plus_tgt_zero_y;
  std::vector<double> em_fit_plus_tgt_plus_x;
  std::vector<double> em_fit_plus_tgt_plus_y;
  std::vector<double> em_fit_plus_x0_y;
  std::vector<double> em_fit_plus_x0_z;
//  std::vector<double> out_fit_minus_ssd_lx;
//  std::vector<double> out_fit_minus_ssd_ly;
//  std::vector<double> out_fit_minus_gtr100_lx;
//  std::vector<double> out_fit_minus_gtr100_ly;
//  std::vector<double> out_fit_minus_gtr200_lx;
//  std::vector<double> out_fit_minus_gtr200_ly;
//  std::vector<double> out_fit_minus_gtr300_lx;
//  std::vector<double> out_fit_minus_gtr300_ly;
//  std::vector<double> out_fit_minus_hbd_lx;
//  std::vector<double> out_fit_minus_hbd_ly;
//  std::vector<double> out_fit_minus_lg_c_lx;
//  std::vector<double> out_fit_minus_lg_c_ly;
//  std::vector<double> out_fit_minus_lg_b_lx;
//  std::vector<double> out_fit_minus_lg_b_ly;
//  std::vector<double> out_fit_minus_lg_a_lx;
//  std::vector<double> out_fit_minus_lg_a_ly;
  std::vector<double> em_fit_minus_tgt_minus_x;
  std::vector<double> em_fit_minus_tgt_minus_y;
  std::vector<double> em_fit_minus_tgt_zero_x;
  std::vector<double> em_fit_minus_tgt_zero_y;
  std::vector<double> em_fit_minus_tgt_plus_x;
  std::vector<double> em_fit_minus_tgt_plus_y;
  std::vector<double> em_fit_minus_x0_y;
  std::vector<double> em_fit_minus_x0_z;
  std::vector<double> em_fit_plus_ssd_mom_lx;
  std::vector<double> em_fit_plus_ssd_mom_ly;
  std::vector<double> em_fit_plus_ssd_mom_lz;
  std::vector<double> em_fit_plus_ssd_mom_gx;
  std::vector<double> em_fit_plus_ssd_mom_gy;
  std::vector<double> em_fit_plus_ssd_mom_gz;
  std::vector<double> em_fit_plus_gtr100_mom_lx;
  std::vector<double> em_fit_plus_gtr100_mom_ly;
  std::vector<double> em_fit_plus_gtr100_mom_lz;
  std::vector<double> em_fit_plus_gtr100_mom_gx;
  std::vector<double> em_fit_plus_gtr100_mom_gy;
  std::vector<double> em_fit_plus_gtr100_mom_gz;
  std::vector<double> em_fit_plus_gtr200_mom_lx;
  std::vector<double> em_fit_plus_gtr200_mom_ly;
  std::vector<double> em_fit_plus_gtr200_mom_lz;
  std::vector<double> em_fit_plus_gtr200_mom_gx;
  std::vector<double> em_fit_plus_gtr200_mom_gy;
  std::vector<double> em_fit_plus_gtr200_mom_gz;
  std::vector<double> em_fit_plus_gtr300_mom_lx;
  std::vector<double> em_fit_plus_gtr300_mom_ly;
  std::vector<double> em_fit_plus_gtr300_mom_lz;
  std::vector<double> em_fit_plus_gtr300_mom_gx;
  std::vector<double> em_fit_plus_gtr300_mom_gy;
  std::vector<double> em_fit_plus_gtr300_mom_gz;
  std::vector<double> em_fit_plus_hbd_mom_lx;
  std::vector<double> em_fit_plus_hbd_mom_ly;
  std::vector<double> em_fit_plus_hbd_mom_lz;
  std::vector<double> em_fit_plus_hbd_mom_gx;
  std::vector<double> em_fit_plus_hbd_mom_gy;
  std::vector<double> em_fit_plus_hbd_mom_gz;
  std::vector<double> em_fit_plus_lg_c_mom_lx;
  std::vector<double> em_fit_plus_lg_c_mom_ly;
  std::vector<double> em_fit_plus_lg_c_mom_lz;
  std::vector<double> em_fit_plus_lg_c_mom_gx;
  std::vector<double> em_fit_plus_lg_c_mom_gy;
  std::vector<double> em_fit_plus_lg_c_mom_gz;
  std::vector<double> em_fit_plus_lg_b_mom_lx;
  std::vector<double> em_fit_plus_lg_b_mom_ly;
  std::vector<double> em_fit_plus_lg_b_mom_lz;
  std::vector<double> em_fit_plus_lg_b_mom_gx;
  std::vector<double> em_fit_plus_lg_b_mom_gy;
  std::vector<double> em_fit_plus_lg_b_mom_gz;
  std::vector<double> em_fit_plus_lg_a_mom_lx;
  std::vector<double> em_fit_plus_lg_a_mom_ly;
  std::vector<double> em_fit_plus_lg_a_mom_lz;
  std::vector<double> em_fit_plus_lg_a_mom_gx;
  std::vector<double> em_fit_plus_lg_a_mom_gy;
  std::vector<double> em_fit_plus_lg_a_mom_gz;
  std::vector<double> em_fit_plus_tgt_minus_mom_x;
  std::vector<double> em_fit_plus_tgt_minus_mom_y;
  std::vector<double> em_fit_plus_tgt_minus_mom_z;
  std::vector<double> em_fit_plus_tgt_zero_mom_x;
  std::vector<double> em_fit_plus_tgt_zero_mom_y;
  std::vector<double> em_fit_plus_tgt_zero_mom_z;
  std::vector<double> em_fit_plus_tgt_plus_mom_x;
  std::vector<double> em_fit_plus_tgt_plus_mom_y;
  std::vector<double> em_fit_plus_tgt_plus_mom_z;
  std::vector<double> em_fit_minus_ssd_mom_lx;
  std::vector<double> em_fit_minus_ssd_mom_ly;
  std::vector<double> em_fit_minus_ssd_mom_lz;
  std::vector<double> em_fit_minus_ssd_mom_gx;
  std::vector<double> em_fit_minus_ssd_mom_gy;
  std::vector<double> em_fit_minus_ssd_mom_gz;
  std::vector<double> em_fit_minus_gtr100_mom_lx;
  std::vector<double> em_fit_minus_gtr100_mom_ly;
  std::vector<double> em_fit_minus_gtr100_mom_lz;
  std::vector<double> em_fit_minus_gtr100_mom_gx;
  std::vector<double> em_fit_minus_gtr100_mom_gy;
  std::vector<double> em_fit_minus_gtr100_mom_gz;
  std::vector<double> em_fit_minus_gtr200_mom_lx;
  std::vector<double> em_fit_minus_gtr200_mom_ly;
  std::vector<double> em_fit_minus_gtr200_mom_lz;
  std::vector<double> em_fit_minus_gtr200_mom_gx;
  std::vector<double> em_fit_minus_gtr200_mom_gy;
  std::vector<double> em_fit_minus_gtr200_mom_gz;
  std::vector<double> em_fit_minus_gtr300_mom_lx;
  std::vector<double> em_fit_minus_gtr300_mom_ly;
  std::vector<double> em_fit_minus_gtr300_mom_lz;
  std::vector<double> em_fit_minus_gtr300_mom_gx;
  std::vector<double> em_fit_minus_gtr300_mom_gy;
  std::vector<double> em_fit_minus_gtr300_mom_gz;
  std::vector<double> em_fit_minus_hbd_mom_lx;
  std::vector<double> em_fit_minus_hbd_mom_ly;
  std::vector<double> em_fit_minus_hbd_mom_lz;
  std::vector<double> em_fit_minus_hbd_mom_gx;
  std::vector<double> em_fit_minus_hbd_mom_gy;
  std::vector<double> em_fit_minus_hbd_mom_gz;
  std::vector<double> em_fit_minus_lg_c_mom_lx;
  std::vector<double> em_fit_minus_lg_c_mom_ly;
  std::vector<double> em_fit_minus_lg_c_mom_lz;
  std::vector<double> em_fit_minus_lg_c_mom_gx;
  std::vector<double> em_fit_minus_lg_c_mom_gy;
  std::vector<double> em_fit_minus_lg_c_mom_gz;
  std::vector<double> em_fit_minus_lg_b_mom_lx;
  std::vector<double> em_fit_minus_lg_b_mom_ly;
  std::vector<double> em_fit_minus_lg_b_mom_lz;
  std::vector<double> em_fit_minus_lg_b_mom_gx;
  std::vector<double> em_fit_minus_lg_b_mom_gy;
  std::vector<double> em_fit_minus_lg_b_mom_gz;
  std::vector<double> em_fit_minus_lg_a_mom_lx;
  std::vector<double> em_fit_minus_lg_a_mom_ly;
  std::vector<double> em_fit_minus_lg_a_mom_lz;
  std::vector<double> em_fit_minus_lg_a_mom_gx;
  std::vector<double> em_fit_minus_lg_a_mom_gy;
  std::vector<double> em_fit_minus_lg_a_mom_gz;
  std::vector<double> em_fit_minus_tgt_minus_mom_x;
  std::vector<double> em_fit_minus_tgt_minus_mom_y;
  std::vector<double> em_fit_minus_tgt_minus_mom_z;
  std::vector<double> em_fit_minus_tgt_zero_mom_x;
  std::vector<double> em_fit_minus_tgt_zero_mom_y;
  std::vector<double> em_fit_minus_tgt_zero_mom_z;
  std::vector<double> em_fit_minus_tgt_plus_mom_x;
  std::vector<double> em_fit_minus_tgt_plus_mom_y;
  std::vector<double> em_fit_minus_tgt_plus_mom_z;
//// gpos...
//  std::vector<double> out_res_plus_ssd_lx;
////  std::vector<double> out_res_plus_ssd_ly;
//  std::vector<double> out_res_plus_gtr100_lx;
//  std::vector<double> out_res_plus_gtr100_ly;
//  std::vector<double> out_res_plus_gtr200_lx;
//  std::vector<double> out_res_plus_gtr200_ly;
//  std::vector<double> out_res_plus_gtr300_lx;
//  std::vector<double> out_res_plus_gtr300_ly;
//  std::vector<double> out_res_minus_ssd_lx;
////  std::vector<double> out_res_minus_ssd_ly;
//  std::vector<double> out_res_minus_gtr100_lx;
//  std::vector<double> out_res_minus_gtr100_ly;
//  std::vector<double> out_res_minus_gtr200_lx;
//  std::vector<double> out_res_minus_gtr200_ly;
//  std::vector<double> out_res_minus_gtr300_lx;
//  std::vector<double> out_res_minus_gtr300_ly;
  std::vector<double>              em_fit_parent_mom;
  std::vector<double>              em_fit_parent_mom_x;
  std::vector<double>              em_fit_parent_mom_y;
  std::vector<double>              em_fit_parent_mom_z;
  std::vector<double>              em_fit_parent_mom_theta;
  std::vector<double>              em_fit_parent_mom_phi;
  std::vector<double>              em_fit_parent_tgt_minus_x;
  std::vector<double>              em_fit_parent_tgt_minus_y;
  std::vector<double>              em_fit_parent_tgt_minus_flight_path;
  std::vector<double>              em_fit_parent_tgt_zero_x;
  std::vector<double>              em_fit_parent_tgt_zero_y;
  std::vector<double>              em_fit_parent_tgt_zero_flight_path;
  std::vector<double>              em_fit_parent_tgt_plus_x;
  std::vector<double>              em_fit_parent_tgt_plus_y;
  std::vector<double>              em_fit_parent_tgt_plus_flight_path;
  std::vector<int>                 em_fit_parent_best_tgt_id;
  std::vector<double>              em_fit_parent_best_tgt_r;
  std::vector<int>                 em_fit_parent_good_tgt_id_set;
  std::vector<std::vector<double>> em_fit_parent_good_tgt_ids;
  std::vector<double>              em_fit_parent_x0_y;
  std::vector<double>              em_fit_parent_x0_z;
//  // Projected HBD
//  std::vector<double>              out_proj_plus_n_hbds;
//  std::vector<std::vector<double>> out_proj_plus_hbd_id;
//  std::vector<std::vector<double>> out_proj_plus_hbd_lx;
//  std::vector<std::vector<double>> out_proj_plus_hbd_ly;
//  std::vector<std::vector<double>> out_proj_plus_hbd_resx;
//  std::vector<std::vector<double>> out_proj_plus_hbd_resy;
//  std::vector<std::vector<double>> out_proj_plus_hbd_adc;
//  std::vector<std::vector<double>> out_proj_plus_hbd_size;
//  std::vector<std::vector<double>> out_proj_plus_hbd_eprob;
//  std::vector<double>              out_proj_minus_n_hbds;
//  std::vector<std::vector<double>> out_proj_minus_hbd_id;
//  std::vector<std::vector<double>> out_proj_minus_hbd_lx;
//  std::vector<std::vector<double>> out_proj_minus_hbd_ly;
//  std::vector<std::vector<double>> out_proj_minus_hbd_resx;
//  std::vector<std::vector<double>> out_proj_minus_hbd_resy;
//  std::vector<std::vector<double>> out_proj_minus_hbd_adc;
//  std::vector<std::vector<double>> out_proj_minus_hbd_size;
//  std::vector<std::vector<double>> out_proj_minus_hbd_eprob;
//  // Projected LG
};

#endif

#ifdef track_analyzer_220715_cxx
track_analyzer_220715::track_analyzer_220715(TTree *tree, E16ANA_GeometryV2* _geometry, E16ANA_MagneticFieldMap* _bfield_map, E16ANA_MultiTrack* _fitter,
                                             E16ANA_MultiTrack* _proj_fitter) : fChain(0), geometry(_geometry), bfield_map(_bfield_map), fitter(_fitter), proj_fitter(_proj_fitter)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/work22/ichikawa/lsf_file/22070700-v2/root/run030717_0_000_ev0-999.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/work22/ichikawa/lsf_file/22070700-v2/root/run030717_0_000_ev0-999.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

track_analyzer_220715::~track_analyzer_220715()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t track_analyzer_220715::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t track_analyzer_220715::LoadTree(Long64_t entry)
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

void track_analyzer_220715::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

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
   fChain->SetBranchAddress("trg_lg_hit_z", &trg_lg_hit_z, &b_trg_lg_hit_z);
   fChain->SetBranchAddress("trg_lg_hit_gx", &trg_lg_hit_gx, &b_trg_lg_hit_gx);
   fChain->SetBranchAddress("trg_lg_hit_gy", &trg_lg_hit_gy, &b_trg_lg_hit_gy);
   fChain->SetBranchAddress("trg_lg_hit_gz", &trg_lg_hit_gz, &b_trg_lg_hit_gz);
   fChain->SetBranchAddress("trg_lg_hit_t", &trg_lg_hit_t, &b_trg_lg_hit_t);
   fChain->SetBranchAddress("n_trg_tracks", &n_trg_tracks, &b_n_trg_tracks);
   fChain->SetBranchAddress("trg_track_n_gtr_hits", &trg_track_n_gtr_hits, &b_trg_track_n_gtr_hits);
   fChain->SetBranchAddress("trg_track_gtr_id", &trg_track_gtr_id, &b_trg_track_gtr_id);
   fChain->SetBranchAddress("trg_track_gtr_mid", &trg_track_gtr_mid, &b_trg_track_gtr_mid);
   fChain->SetBranchAddress("trg_track_gtr_cid", &trg_track_gtr_cid, &b_trg_track_gtr_cid);
   fChain->SetBranchAddress("trg_track_gtr_x", &trg_track_gtr_x, &b_trg_track_gtr_x);
   fChain->SetBranchAddress("trg_track_gtr_y", &trg_track_gtr_y, &b_trg_track_gtr_y);
   fChain->SetBranchAddress("trg_track_gtr_t", &trg_track_gtr_t, &b_trg_track_gtr_t);
   fChain->SetBranchAddress("trg_track_gtr_is_t_match", &trg_track_gtr_is_t_match, &b_trg_track_gtr_is_t_match);
   fChain->SetBranchAddress("trg_track_n_hbd_hits", &trg_track_n_hbd_hits, &b_trg_track_n_hbd_hits);
   fChain->SetBranchAddress("trg_track_hbd_id", &trg_track_hbd_id, &b_trg_track_hbd_id);
   fChain->SetBranchAddress("trg_track_hbd_mid", &trg_track_hbd_mid, &b_trg_track_hbd_mid);
   fChain->SetBranchAddress("trg_track_hbd_cid", &trg_track_hbd_cid, &b_trg_track_hbd_cid);
   fChain->SetBranchAddress("trg_track_hbd_x", &trg_track_hbd_x, &b_trg_track_hbd_x);
   fChain->SetBranchAddress("trg_track_hbd_y", &trg_track_hbd_y, &b_trg_track_hbd_y);
   fChain->SetBranchAddress("trg_track_hbd_t", &trg_track_hbd_t, &b_trg_track_hbd_t);
   fChain->SetBranchAddress("trg_track_hbd_is_t_match", &trg_track_hbd_is_t_match, &b_trg_track_hbd_is_t_match);
   fChain->SetBranchAddress("trg_track_lg_id", &trg_track_lg_id, &b_trg_track_lg_id);
   fChain->SetBranchAddress("trg_track_lg_mid", &trg_track_lg_mid, &b_trg_track_lg_mid);
   fChain->SetBranchAddress("trg_track_lg_cid", &trg_track_lg_cid, &b_trg_track_lg_cid);
   fChain->SetBranchAddress("trg_track_lg_x", &trg_track_lg_x, &b_trg_track_lg_x);
   fChain->SetBranchAddress("trg_track_lg_y", &trg_track_lg_y, &b_trg_track_lg_y);
   fChain->SetBranchAddress("trg_track_lg_t", &trg_track_lg_t, &b_trg_track_lg_t);
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
   fChain->SetBranchAddress("rough_fit_n_hbds", &rough_fit_n_hbds, &b_rough_fit_n_hbds);
   fChain->SetBranchAddress("rough_fit_hbd_ids", &rough_fit_hbd_ids, &b_rough_fit_hbd_ids);
   fChain->SetBranchAddress("rough_fit_hbd_ress", &rough_fit_hbd_ress, &b_rough_fit_hbd_ress);
   fChain->SetBranchAddress("rough_fit_hbd_y_oks", &rough_fit_hbd_y_oks, &b_rough_fit_hbd_y_oks);
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
   fChain->SetBranchAddress("rk_hit_ssd_x", &rk_hit_ssd_x, &b_rk_hit_ssd_x);
   fChain->SetBranchAddress("rk_hit_ssd_gx", &rk_hit_ssd_gx, &b_rk_hit_ssd_gx);
   fChain->SetBranchAddress("rk_hit_ssd_gy", &rk_hit_ssd_gy, &b_rk_hit_ssd_gy);
   fChain->SetBranchAddress("rk_hit_ssd_gz", &rk_hit_ssd_gz, &b_rk_hit_ssd_gz);
   fChain->SetBranchAddress("rk_hit_ssd_adc", &rk_hit_ssd_adc, &b_rk_hit_ssd_adc);
   fChain->SetBranchAddress("rk_hit_ssd_t", &rk_hit_ssd_t, &b_rk_hit_ssd_t);
   fChain->SetBranchAddress("rk_hit_ssd_chi2", &rk_hit_ssd_chi2, &b_rk_hit_ssd_chi2);
   fChain->SetBranchAddress("rk_hit_gtr100_xid", &rk_hit_gtr100_xid, &b_rk_hit_gtr100_xid);
   fChain->SetBranchAddress("rk_hit_gtr100_yid", &rk_hit_gtr100_yid, &b_rk_hit_gtr100_yid);
   fChain->SetBranchAddress("rk_hit_gtr100_gx", &rk_hit_gtr100_gx, &b_rk_hit_gtr100_gx);
   fChain->SetBranchAddress("rk_hit_gtr100_gy", &rk_hit_gtr100_gy, &b_rk_hit_gtr100_gy);
   fChain->SetBranchAddress("rk_hit_gtr100_gz", &rk_hit_gtr100_gz, &b_rk_hit_gtr100_gz);
   fChain->SetBranchAddress("rk_hit_gtr100_xadc", &rk_hit_gtr100_xadc, &b_rk_hit_gtr100_xadc);
   fChain->SetBranchAddress("rk_hit_gtr100_yadc", &rk_hit_gtr100_yadc, &b_rk_hit_gtr100_yadc);
   fChain->SetBranchAddress("rk_hit_gtr100_xt", &rk_hit_gtr100_xt, &b_rk_hit_gtr100_xt);
   fChain->SetBranchAddress("rk_hit_gtr100_yt", &rk_hit_gtr100_yt, &b_rk_hit_gtr100_yt);
   fChain->SetBranchAddress("rk_hit_gtr100_xt2", &rk_hit_gtr100_xt2, &b_rk_hit_gtr100_xt2);
   fChain->SetBranchAddress("rk_hit_gtr100_yt2", &rk_hit_gtr100_yt2, &b_rk_hit_gtr100_yt2);
   fChain->SetBranchAddress("rk_hit_gtr100_tx2", &rk_hit_gtr100_tx2, &b_rk_hit_gtr100_tx2);
   fChain->SetBranchAddress("rk_hit_gtr100_ty", &rk_hit_gtr100_ty, &b_rk_hit_gtr100_ty);
   fChain->SetBranchAddress("rk_hit_gtr100_gtx", &rk_hit_gtr100_gtx, &b_rk_hit_gtr100_gtx);
   fChain->SetBranchAddress("rk_hit_gtr100_gty", &rk_hit_gtr100_gty, &b_rk_hit_gtr100_gty);
   fChain->SetBranchAddress("rk_hit_gtr100_gtz", &rk_hit_gtr100_gtz, &b_rk_hit_gtr100_gtz);
   fChain->SetBranchAddress("rk_hit_gtr100_gtx2", &rk_hit_gtr100_gtx2, &b_rk_hit_gtr100_gtx2);
   fChain->SetBranchAddress("rk_hit_gtr100_gty2", &rk_hit_gtr100_gty2, &b_rk_hit_gtr100_gty2);
   fChain->SetBranchAddress("rk_hit_gtr100_gtz2", &rk_hit_gtr100_gtz2, &b_rk_hit_gtr100_gtz2);
   fChain->SetBranchAddress("rk_hit_gtr100_nc", &rk_hit_gtr100_nc, &b_rk_hit_gtr100_nc);
   fChain->SetBranchAddress("rk_hit_gtr100_the", &rk_hit_gtr100_the, &b_rk_hit_gtr100_the);
   fChain->SetBranchAddress("rk_hit_gtr100_the2", &rk_hit_gtr100_the2, &b_rk_hit_gtr100_the2);
   fChain->SetBranchAddress("rk_hit_gtr200_xid", &rk_hit_gtr200_xid, &b_rk_hit_gtr200_xid);
   fChain->SetBranchAddress("rk_hit_gtr200_yid", &rk_hit_gtr200_yid, &b_rk_hit_gtr200_yid);
   fChain->SetBranchAddress("rk_hit_gtr200_gx", &rk_hit_gtr200_gx, &b_rk_hit_gtr200_gx);
   fChain->SetBranchAddress("rk_hit_gtr200_gy", &rk_hit_gtr200_gy, &b_rk_hit_gtr200_gy);
   fChain->SetBranchAddress("rk_hit_gtr200_gz", &rk_hit_gtr200_gz, &b_rk_hit_gtr200_gz);
   fChain->SetBranchAddress("rk_hit_gtr200_xadc", &rk_hit_gtr200_xadc, &b_rk_hit_gtr200_xadc);
   fChain->SetBranchAddress("rk_hit_gtr200_yadc", &rk_hit_gtr200_yadc, &b_rk_hit_gtr200_yadc);
   fChain->SetBranchAddress("rk_hit_gtr200_xt", &rk_hit_gtr200_xt, &b_rk_hit_gtr200_xt);
   fChain->SetBranchAddress("rk_hit_gtr200_yt", &rk_hit_gtr200_yt, &b_rk_hit_gtr200_yt);
   fChain->SetBranchAddress("rk_hit_gtr200_xt2", &rk_hit_gtr200_xt2, &b_rk_hit_gtr200_xt2);
   fChain->SetBranchAddress("rk_hit_gtr200_yt2", &rk_hit_gtr200_yt2, &b_rk_hit_gtr200_yt2);
   fChain->SetBranchAddress("rk_hit_gtr200_tx2", &rk_hit_gtr200_tx2, &b_rk_hit_gtr200_tx2);
   fChain->SetBranchAddress("rk_hit_gtr200_ty", &rk_hit_gtr200_ty, &b_rk_hit_gtr200_ty);
   fChain->SetBranchAddress("rk_hit_gtr200_gtx", &rk_hit_gtr200_gtx, &b_rk_hit_gtr200_gtx);
   fChain->SetBranchAddress("rk_hit_gtr200_gty", &rk_hit_gtr200_gty, &b_rk_hit_gtr200_gty);
   fChain->SetBranchAddress("rk_hit_gtr200_gtz", &rk_hit_gtr200_gtz, &b_rk_hit_gtr200_gtz);
   fChain->SetBranchAddress("rk_hit_gtr200_gtx2", &rk_hit_gtr200_gtx2, &b_rk_hit_gtr200_gtx2);
   fChain->SetBranchAddress("rk_hit_gtr200_gty2", &rk_hit_gtr200_gty2, &b_rk_hit_gtr200_gty2);
   fChain->SetBranchAddress("rk_hit_gtr200_gtz2", &rk_hit_gtr200_gtz2, &b_rk_hit_gtr200_gtz2);
   fChain->SetBranchAddress("rk_hit_gtr200_nc", &rk_hit_gtr200_nc, &b_rk_hit_gtr200_nc);
   fChain->SetBranchAddress("rk_hit_gtr200_the", &rk_hit_gtr200_the, &b_rk_hit_gtr200_the);
   fChain->SetBranchAddress("rk_hit_gtr200_the2", &rk_hit_gtr200_the2, &b_rk_hit_gtr200_the2);
   fChain->SetBranchAddress("rk_hit_gtr300_xid", &rk_hit_gtr300_xid, &b_rk_hit_gtr300_xid);
   fChain->SetBranchAddress("rk_hit_gtr300_yid", &rk_hit_gtr300_yid, &b_rk_hit_gtr300_yid);
   fChain->SetBranchAddress("rk_hit_gtr300_gx", &rk_hit_gtr300_gx, &b_rk_hit_gtr300_gx);
   fChain->SetBranchAddress("rk_hit_gtr300_gy", &rk_hit_gtr300_gy, &b_rk_hit_gtr300_gy);
   fChain->SetBranchAddress("rk_hit_gtr300_gz", &rk_hit_gtr300_gz, &b_rk_hit_gtr300_gz);
   fChain->SetBranchAddress("rk_hit_gtr300_xadc", &rk_hit_gtr300_xadc, &b_rk_hit_gtr300_xadc);
   fChain->SetBranchAddress("rk_hit_gtr300_yadc", &rk_hit_gtr300_yadc, &b_rk_hit_gtr300_yadc);
   fChain->SetBranchAddress("rk_hit_gtr300_xt", &rk_hit_gtr300_xt, &b_rk_hit_gtr300_xt);
   fChain->SetBranchAddress("rk_hit_gtr300_yt", &rk_hit_gtr300_yt, &b_rk_hit_gtr300_yt);
   fChain->SetBranchAddress("rk_hit_gtr300_xt2", &rk_hit_gtr300_xt2, &b_rk_hit_gtr300_xt2);
   fChain->SetBranchAddress("rk_hit_gtr300_yt2", &rk_hit_gtr300_yt2, &b_rk_hit_gtr300_yt2);
   fChain->SetBranchAddress("rk_hit_gtr300_tx2", &rk_hit_gtr300_tx2, &b_rk_hit_gtr300_tx2);
   fChain->SetBranchAddress("rk_hit_gtr300_ty", &rk_hit_gtr300_ty, &b_rk_hit_gtr300_ty);
   fChain->SetBranchAddress("rk_hit_gtr300_gtx", &rk_hit_gtr300_gtx, &b_rk_hit_gtr300_gtx);
   fChain->SetBranchAddress("rk_hit_gtr300_gty", &rk_hit_gtr300_gty, &b_rk_hit_gtr300_gty);
   fChain->SetBranchAddress("rk_hit_gtr300_gtz", &rk_hit_gtr300_gtz, &b_rk_hit_gtr300_gtz);
   fChain->SetBranchAddress("rk_hit_gtr300_gtx2", &rk_hit_gtr300_gtx2, &b_rk_hit_gtr300_gtx2);
   fChain->SetBranchAddress("rk_hit_gtr300_gty2", &rk_hit_gtr300_gty2, &b_rk_hit_gtr300_gty2);
   fChain->SetBranchAddress("rk_hit_gtr300_gtz2", &rk_hit_gtr300_gtz2, &b_rk_hit_gtr300_gtz2);
   fChain->SetBranchAddress("rk_hit_gtr300_nc", &rk_hit_gtr300_nc, &b_rk_hit_gtr300_nc);
   fChain->SetBranchAddress("rk_hit_gtr300_the", &rk_hit_gtr300_the, &b_rk_hit_gtr300_the);
   fChain->SetBranchAddress("rk_hit_gtr300_the2", &rk_hit_gtr300_the2, &b_rk_hit_gtr300_the2);
   fChain->SetBranchAddress("rk_fit_init_mom_gx", &rk_fit_init_mom_gx, &b_rk_fit_init_mom_gx);
   fChain->SetBranchAddress("rk_fit_init_mom_gy", &rk_fit_init_mom_gy, &b_rk_fit_init_mom_gy);
   fChain->SetBranchAddress("rk_fit_init_mom_gz", &rk_fit_init_mom_gz, &b_rk_fit_init_mom_gz);
   fChain->SetBranchAddress("rk_fit_init_pos_gx", &rk_fit_init_pos_gx, &b_rk_fit_init_pos_gx);
   fChain->SetBranchAddress("rk_fit_init_pos_gy", &rk_fit_init_pos_gy, &b_rk_fit_init_pos_gy);
   fChain->SetBranchAddress("rk_fit_init_pos_gz", &rk_fit_init_pos_gz, &b_rk_fit_init_pos_gz);
   fChain->SetBranchAddress("rk_fit_ssd_mid", &rk_fit_ssd_mid, &b_rk_fit_ssd_mid);
   fChain->SetBranchAddress("rk_fit_ssd_x", &rk_fit_ssd_x, &b_rk_fit_ssd_x);
   fChain->SetBranchAddress("rk_fit_ssd_y", &rk_fit_ssd_y, &b_rk_fit_ssd_y);
   fChain->SetBranchAddress("rk_fit_ssd_gx", &rk_fit_ssd_gx, &b_rk_fit_ssd_gx);
   fChain->SetBranchAddress("rk_fit_ssd_gy", &rk_fit_ssd_gy, &b_rk_fit_ssd_gy);
   fChain->SetBranchAddress("rk_fit_ssd_gz", &rk_fit_ssd_gz, &b_rk_fit_ssd_gz);
   fChain->SetBranchAddress("rk_fit_ssd_mom_x", &rk_fit_ssd_mom_x, &b_rk_fit_ssd_mom_x);
   fChain->SetBranchAddress("rk_fit_ssd_mom_y", &rk_fit_ssd_mom_y, &b_rk_fit_ssd_mom_y);
   fChain->SetBranchAddress("rk_fit_ssd_mom_z", &rk_fit_ssd_mom_z, &b_rk_fit_ssd_mom_z);
   fChain->SetBranchAddress("rk_fit_ssd_mom_gx", &rk_fit_ssd_mom_gx, &b_rk_fit_ssd_mom_gx);
   fChain->SetBranchAddress("rk_fit_ssd_mom_gy", &rk_fit_ssd_mom_gy, &b_rk_fit_ssd_mom_gy);
   fChain->SetBranchAddress("rk_fit_ssd_mom_gz", &rk_fit_ssd_mom_gz, &b_rk_fit_ssd_mom_gz);
   fChain->SetBranchAddress("rk_fit_gtr100_mid", &rk_fit_gtr100_mid, &b_rk_fit_gtr100_mid);
   fChain->SetBranchAddress("rk_fit_gtr100_x", &rk_fit_gtr100_x, &b_rk_fit_gtr100_x);
   fChain->SetBranchAddress("rk_fit_gtr100_y", &rk_fit_gtr100_y, &b_rk_fit_gtr100_y);
   fChain->SetBranchAddress("rk_fit_gtr100_gx", &rk_fit_gtr100_gx, &b_rk_fit_gtr100_gx);
   fChain->SetBranchAddress("rk_fit_gtr100_gy", &rk_fit_gtr100_gy, &b_rk_fit_gtr100_gy);
   fChain->SetBranchAddress("rk_fit_gtr100_gz", &rk_fit_gtr100_gz, &b_rk_fit_gtr100_gz);
   fChain->SetBranchAddress("rk_fit_gtr100_mom_x", &rk_fit_gtr100_mom_x, &b_rk_fit_gtr100_mom_x);
   fChain->SetBranchAddress("rk_fit_gtr100_mom_y", &rk_fit_gtr100_mom_y, &b_rk_fit_gtr100_mom_y);
   fChain->SetBranchAddress("rk_fit_gtr100_mom_z", &rk_fit_gtr100_mom_z, &b_rk_fit_gtr100_mom_z);
   fChain->SetBranchAddress("rk_fit_gtr100_mom_gx", &rk_fit_gtr100_mom_gx, &b_rk_fit_gtr100_mom_gx);
   fChain->SetBranchAddress("rk_fit_gtr100_mom_gy", &rk_fit_gtr100_mom_gy, &b_rk_fit_gtr100_mom_gy);
   fChain->SetBranchAddress("rk_fit_gtr100_mom_gz", &rk_fit_gtr100_mom_gz, &b_rk_fit_gtr100_mom_gz);
   fChain->SetBranchAddress("rk_fit_gtr200_mid", &rk_fit_gtr200_mid, &b_rk_fit_gtr200_mid);
   fChain->SetBranchAddress("rk_fit_gtr200_x", &rk_fit_gtr200_x, &b_rk_fit_gtr200_x);
   fChain->SetBranchAddress("rk_fit_gtr200_y", &rk_fit_gtr200_y, &b_rk_fit_gtr200_y);
   fChain->SetBranchAddress("rk_fit_gtr200_gx", &rk_fit_gtr200_gx, &b_rk_fit_gtr200_gx);
   fChain->SetBranchAddress("rk_fit_gtr200_gy", &rk_fit_gtr200_gy, &b_rk_fit_gtr200_gy);
   fChain->SetBranchAddress("rk_fit_gtr200_gz", &rk_fit_gtr200_gz, &b_rk_fit_gtr200_gz);
   fChain->SetBranchAddress("rk_fit_gtr200_mom_x", &rk_fit_gtr200_mom_x, &b_rk_fit_gtr200_mom_x);
   fChain->SetBranchAddress("rk_fit_gtr200_mom_y", &rk_fit_gtr200_mom_y, &b_rk_fit_gtr200_mom_y);
   fChain->SetBranchAddress("rk_fit_gtr200_mom_z", &rk_fit_gtr200_mom_z, &b_rk_fit_gtr200_mom_z);
   fChain->SetBranchAddress("rk_fit_gtr200_mom_gx", &rk_fit_gtr200_mom_gx, &b_rk_fit_gtr200_mom_gx);
   fChain->SetBranchAddress("rk_fit_gtr200_mom_gy", &rk_fit_gtr200_mom_gy, &b_rk_fit_gtr200_mom_gy);
   fChain->SetBranchAddress("rk_fit_gtr200_mom_gz", &rk_fit_gtr200_mom_gz, &b_rk_fit_gtr200_mom_gz);
   fChain->SetBranchAddress("rk_fit_gtr300_mid", &rk_fit_gtr300_mid, &b_rk_fit_gtr300_mid);
   fChain->SetBranchAddress("rk_fit_gtr300_x", &rk_fit_gtr300_x, &b_rk_fit_gtr300_x);
   fChain->SetBranchAddress("rk_fit_gtr300_y", &rk_fit_gtr300_y, &b_rk_fit_gtr300_y);
   fChain->SetBranchAddress("rk_fit_gtr300_gx", &rk_fit_gtr300_gx, &b_rk_fit_gtr300_gx);
   fChain->SetBranchAddress("rk_fit_gtr300_gy", &rk_fit_gtr300_gy, &b_rk_fit_gtr300_gy);
   fChain->SetBranchAddress("rk_fit_gtr300_gz", &rk_fit_gtr300_gz, &b_rk_fit_gtr300_gz);
   fChain->SetBranchAddress("rk_fit_gtr300_mom_x", &rk_fit_gtr300_mom_x, &b_rk_fit_gtr300_mom_x);
   fChain->SetBranchAddress("rk_fit_gtr300_mom_y", &rk_fit_gtr300_mom_y, &b_rk_fit_gtr300_mom_y);
   fChain->SetBranchAddress("rk_fit_gtr300_mom_z", &rk_fit_gtr300_mom_z, &b_rk_fit_gtr300_mom_z);
   fChain->SetBranchAddress("rk_fit_gtr300_mom_gx", &rk_fit_gtr300_mom_gx, &b_rk_fit_gtr300_mom_gx);
   fChain->SetBranchAddress("rk_fit_gtr300_mom_gy", &rk_fit_gtr300_mom_gy, &b_rk_fit_gtr300_mom_gy);
   fChain->SetBranchAddress("rk_fit_gtr300_mom_gz", &rk_fit_gtr300_mom_gz, &b_rk_fit_gtr300_mom_gz);
   fChain->SetBranchAddress("rk_fit_hbd_mid", &rk_fit_hbd_mid, &b_rk_fit_hbd_mid);
   fChain->SetBranchAddress("rk_fit_hbd_x", &rk_fit_hbd_x, &b_rk_fit_hbd_x);
   fChain->SetBranchAddress("rk_fit_hbd_y", &rk_fit_hbd_y, &b_rk_fit_hbd_y);
   fChain->SetBranchAddress("rk_fit_hbd_gx", &rk_fit_hbd_gx, &b_rk_fit_hbd_gx);
   fChain->SetBranchAddress("rk_fit_hbd_gy", &rk_fit_hbd_gy, &b_rk_fit_hbd_gy);
   fChain->SetBranchAddress("rk_fit_hbd_gz", &rk_fit_hbd_gz, &b_rk_fit_hbd_gz);
   fChain->SetBranchAddress("rk_fit_hbd_mom_x", &rk_fit_hbd_mom_x, &b_rk_fit_hbd_mom_x);
   fChain->SetBranchAddress("rk_fit_hbd_mom_y", &rk_fit_hbd_mom_y, &b_rk_fit_hbd_mom_y);
   fChain->SetBranchAddress("rk_fit_hbd_mom_z", &rk_fit_hbd_mom_z, &b_rk_fit_hbd_mom_z);
   fChain->SetBranchAddress("rk_fit_hbd_mom_gx", &rk_fit_hbd_mom_gx, &b_rk_fit_hbd_mom_gx);
   fChain->SetBranchAddress("rk_fit_hbd_mom_gy", &rk_fit_hbd_mom_gy, &b_rk_fit_hbd_mom_gy);
   fChain->SetBranchAddress("rk_fit_hbd_mom_gz", &rk_fit_hbd_mom_gz, &b_rk_fit_hbd_mom_gz);
   fChain->SetBranchAddress("rk_fit_lg_c_mid", &rk_fit_lg_c_mid, &b_rk_fit_lg_c_mid);
   fChain->SetBranchAddress("rk_fit_lg_c_x", &rk_fit_lg_c_x, &b_rk_fit_lg_c_x);
   fChain->SetBranchAddress("rk_fit_lg_c_y", &rk_fit_lg_c_y, &b_rk_fit_lg_c_y);
   fChain->SetBranchAddress("rk_fit_lg_c_gx", &rk_fit_lg_c_gx, &b_rk_fit_lg_c_gx);
   fChain->SetBranchAddress("rk_fit_lg_c_gy", &rk_fit_lg_c_gy, &b_rk_fit_lg_c_gy);
   fChain->SetBranchAddress("rk_fit_lg_c_gz", &rk_fit_lg_c_gz, &b_rk_fit_lg_c_gz);
   fChain->SetBranchAddress("rk_fit_lg_c_mom_x", &rk_fit_lg_c_mom_x, &b_rk_fit_lg_c_mom_x);
   fChain->SetBranchAddress("rk_fit_lg_c_mom_y", &rk_fit_lg_c_mom_y, &b_rk_fit_lg_c_mom_y);
   fChain->SetBranchAddress("rk_fit_lg_c_mom_z", &rk_fit_lg_c_mom_z, &b_rk_fit_lg_c_mom_z);
   fChain->SetBranchAddress("rk_fit_lg_c_mom_gx", &rk_fit_lg_c_mom_gx, &b_rk_fit_lg_c_mom_gx);
   fChain->SetBranchAddress("rk_fit_lg_c_mom_gy", &rk_fit_lg_c_mom_gy, &b_rk_fit_lg_c_mom_gy);
   fChain->SetBranchAddress("rk_fit_lg_c_mom_gz", &rk_fit_lg_c_mom_gz, &b_rk_fit_lg_c_mom_gz);
   fChain->SetBranchAddress("rk_fit_lg_b_mid", &rk_fit_lg_b_mid, &b_rk_fit_lg_b_mid);
   fChain->SetBranchAddress("rk_fit_lg_b_x", &rk_fit_lg_b_x, &b_rk_fit_lg_b_x);
   fChain->SetBranchAddress("rk_fit_lg_b_y", &rk_fit_lg_b_y, &b_rk_fit_lg_b_y);
   fChain->SetBranchAddress("rk_fit_lg_b_gx", &rk_fit_lg_b_gx, &b_rk_fit_lg_b_gx);
   fChain->SetBranchAddress("rk_fit_lg_b_gy", &rk_fit_lg_b_gy, &b_rk_fit_lg_b_gy);
   fChain->SetBranchAddress("rk_fit_lg_b_gz", &rk_fit_lg_b_gz, &b_rk_fit_lg_b_gz);
   fChain->SetBranchAddress("rk_fit_lg_b_mom_x", &rk_fit_lg_b_mom_x, &b_rk_fit_lg_b_mom_x);
   fChain->SetBranchAddress("rk_fit_lg_b_mom_y", &rk_fit_lg_b_mom_y, &b_rk_fit_lg_b_mom_y);
   fChain->SetBranchAddress("rk_fit_lg_b_mom_z", &rk_fit_lg_b_mom_z, &b_rk_fit_lg_b_mom_z);
   fChain->SetBranchAddress("rk_fit_lg_b_mom_gx", &rk_fit_lg_b_mom_gx, &b_rk_fit_lg_b_mom_gx);
   fChain->SetBranchAddress("rk_fit_lg_b_mom_gy", &rk_fit_lg_b_mom_gy, &b_rk_fit_lg_b_mom_gy);
   fChain->SetBranchAddress("rk_fit_lg_b_mom_gz", &rk_fit_lg_b_mom_gz, &b_rk_fit_lg_b_mom_gz);
   fChain->SetBranchAddress("rk_fit_lg_a_mid", &rk_fit_lg_a_mid, &b_rk_fit_lg_a_mid);
   fChain->SetBranchAddress("rk_fit_lg_a_x", &rk_fit_lg_a_x, &b_rk_fit_lg_a_x);
   fChain->SetBranchAddress("rk_fit_lg_a_y", &rk_fit_lg_a_y, &b_rk_fit_lg_a_y);
   fChain->SetBranchAddress("rk_fit_lg_a_gx", &rk_fit_lg_a_gx, &b_rk_fit_lg_a_gx);
   fChain->SetBranchAddress("rk_fit_lg_a_gy", &rk_fit_lg_a_gy, &b_rk_fit_lg_a_gy);
   fChain->SetBranchAddress("rk_fit_lg_a_gz", &rk_fit_lg_a_gz, &b_rk_fit_lg_a_gz);
   fChain->SetBranchAddress("rk_fit_lg_a_mom_x", &rk_fit_lg_a_mom_x, &b_rk_fit_lg_a_mom_x);
   fChain->SetBranchAddress("rk_fit_lg_a_mom_y", &rk_fit_lg_a_mom_y, &b_rk_fit_lg_a_mom_y);
   fChain->SetBranchAddress("rk_fit_lg_a_mom_z", &rk_fit_lg_a_mom_z, &b_rk_fit_lg_a_mom_z);
   fChain->SetBranchAddress("rk_fit_lg_a_mom_gx", &rk_fit_lg_a_mom_gx, &b_rk_fit_lg_a_mom_gx);
   fChain->SetBranchAddress("rk_fit_lg_a_mom_gy", &rk_fit_lg_a_mom_gy, &b_rk_fit_lg_a_mom_gy);
   fChain->SetBranchAddress("rk_fit_lg_a_mom_gz", &rk_fit_lg_a_mom_gz, &b_rk_fit_lg_a_mom_gz);
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
   fChain->SetBranchAddress("rk_res_gtr100_tx", &rk_res_gtr100_tx, &b_rk_res_gtr100_tx);
   fChain->SetBranchAddress("rk_res_gtr100_ty", &rk_res_gtr100_ty, &b_rk_res_gtr100_ty);
   fChain->SetBranchAddress("rk_res_gtr200_tx", &rk_res_gtr200_tx, &b_rk_res_gtr200_tx);
   fChain->SetBranchAddress("rk_res_gtr200_ty", &rk_res_gtr200_ty, &b_rk_res_gtr200_ty);
   fChain->SetBranchAddress("rk_res_gtr300_tx", &rk_res_gtr300_tx, &b_rk_res_gtr300_tx);
   fChain->SetBranchAddress("rk_res_gtr300_ty", &rk_res_gtr300_ty, &b_rk_res_gtr300_ty);
   fChain->SetBranchAddress("rk_res_gtr100_tx2", &rk_res_gtr100_tx2, &b_rk_res_gtr100_tx2);
   fChain->SetBranchAddress("rk_res_gtr200_tx2", &rk_res_gtr200_tx2, &b_rk_res_gtr200_tx2);
   fChain->SetBranchAddress("rk_res_gtr300_tx2", &rk_res_gtr300_tx2, &b_rk_res_gtr300_tx2);
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
   fChain->SetBranchAddress("rk_proj_is_search", &rk_proj_is_search, &b_rk_proj_is_search);
   fChain->SetBranchAddress("rk_proj_n_hbd", &rk_proj_n_hbd, &b_rk_proj_n_hbd);
   fChain->SetBranchAddress("rk_proj_hbd_id", &rk_proj_hbd_id, &b_rk_proj_hbd_id);
   fChain->SetBranchAddress("rk_proj_hbd_mid", &rk_proj_hbd_mid, &b_rk_proj_hbd_mid);
   fChain->SetBranchAddress("rk_proj_hbd_x", &rk_proj_hbd_x, &b_rk_proj_hbd_x);
   fChain->SetBranchAddress("rk_proj_hbd_y", &rk_proj_hbd_y, &b_rk_proj_hbd_y);
   fChain->SetBranchAddress("rk_proj_hbd_adc", &rk_proj_hbd_adc, &b_rk_proj_hbd_adc);
   fChain->SetBranchAddress("rk_proj_hbd_t", &rk_proj_hbd_t, &b_rk_proj_hbd_t);
   fChain->SetBranchAddress("rk_proj_hbd_ftime", &rk_proj_hbd_ftime, &b_rk_proj_hbd_ftime);
   fChain->SetBranchAddress("rk_proj_hbd_tdiff", &rk_proj_hbd_tdiff, &b_rk_proj_hbd_tdiff);
   fChain->SetBranchAddress("rk_proj_hbd_size", &rk_proj_hbd_size, &b_rk_proj_hbd_size);
   fChain->SetBranchAddress("rk_proj_hbd_eprob", &rk_proj_hbd_eprob, &b_rk_proj_hbd_eprob);
   fChain->SetBranchAddress("rk_proj_hbd_cprob", &rk_proj_hbd_cprob, &b_rk_proj_hbd_cprob);
   fChain->SetBranchAddress("rk_proj_n_lg", &rk_proj_n_lg, &b_rk_proj_n_lg);
   fChain->SetBranchAddress("rk_proj_lg_id", &rk_proj_lg_id, &b_rk_proj_lg_id);
   fChain->SetBranchAddress("rk_proj_lg_mid", &rk_proj_lg_mid, &b_rk_proj_lg_mid);
   fChain->SetBranchAddress("rk_proj_lg_cid", &rk_proj_lg_cid, &b_rk_proj_lg_cid);
   fChain->SetBranchAddress("rk_proj_lg_x", &rk_proj_lg_x, &b_rk_proj_lg_x);
   fChain->SetBranchAddress("rk_proj_lg_y", &rk_proj_lg_y, &b_rk_proj_lg_y);
   fChain->SetBranchAddress("rk_proj_lg_adc", &rk_proj_lg_adc, &b_rk_proj_lg_adc);
   fChain->SetBranchAddress("rk_proj_lg_t", &rk_proj_lg_t, &b_rk_proj_lg_t);
   fChain->SetBranchAddress("rk_proj_lg_npeaks", &rk_proj_lg_npeaks, &b_rk_proj_lg_npeaks);
   fChain->SetBranchAddress("rk_proj_lg_fflag", &rk_proj_lg_fflag, &b_rk_proj_lg_fflag);
   fChain->SetBranchAddress("rk_pair_minus_track_id", &rk_pair_minus_track_id, &b_rk_pair_minus_track_id);
   fChain->SetBranchAddress("rk_pair_minus_gtr300_mid", &rk_pair_minus_gtr300_mid, &b_rk_pair_minus_gtr300_mid);
   fChain->SetBranchAddress("rk_pair_minus_chi_square", &rk_pair_minus_chi_square, &b_rk_pair_minus_chi_square);
   fChain->SetBranchAddress("rk_pair_minus_mom_gx", &rk_pair_minus_mom_gx, &b_rk_pair_minus_mom_gx);
   fChain->SetBranchAddress("rk_pair_minus_mom_gy", &rk_pair_minus_mom_gy, &b_rk_pair_minus_mom_gy);
   fChain->SetBranchAddress("rk_pair_minus_mom_gz", &rk_pair_minus_mom_gz, &b_rk_pair_minus_mom_gz);
   fChain->SetBranchAddress("rk_pair_minus_ssd_t", &rk_pair_minus_ssd_t, &b_rk_pair_minus_ssd_t);
   fChain->SetBranchAddress("rk_pair_minus_lg_t", &rk_pair_minus_lg_t, &b_rk_pair_minus_lg_t);
   fChain->SetBranchAddress("rk_pair_plus_track_id", &rk_pair_plus_track_id, &b_rk_pair_plus_track_id);
   fChain->SetBranchAddress("rk_pair_plus_gtr300_mid", &rk_pair_plus_gtr300_mid, &b_rk_pair_plus_gtr300_mid);
   fChain->SetBranchAddress("rk_pair_plus_chi_square", &rk_pair_plus_chi_square, &b_rk_pair_plus_chi_square);
   fChain->SetBranchAddress("rk_pair_plus_mom_gx", &rk_pair_plus_mom_gx, &b_rk_pair_plus_mom_gx);
   fChain->SetBranchAddress("rk_pair_plus_mom_gy", &rk_pair_plus_mom_gy, &b_rk_pair_plus_mom_gy);
   fChain->SetBranchAddress("rk_pair_plus_mom_gz", &rk_pair_plus_mom_gz, &b_rk_pair_plus_mom_gz);
   fChain->SetBranchAddress("rk_pair_plus_ssd_t", &rk_pair_plus_ssd_t, &b_rk_pair_plus_ssd_t);
   fChain->SetBranchAddress("rk_pair_plus_lg_t", &rk_pair_plus_lg_t, &b_rk_pair_plus_lg_t);
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

Bool_t track_analyzer_220715::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void track_analyzer_220715::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t track_analyzer_220715::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef track_analyzer_220715_cxx
