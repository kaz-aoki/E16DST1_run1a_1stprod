//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr 13 21:25:45 2022 by ROOT version 5.34/01
// from TTree tree/tree
// found on file: out.root
//////////////////////////////////////////////////////////

#ifndef LayerEfficiencyCalculator_h
#define LayerEfficiencyCalculator_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TVector.h>
#include "E16ANA_MultiTrack.hh"
// #include "SingleTrackAnalyzerForRes.hh"
#include "E16ANA_EIDSingleTrackAnalyzer.hh"
#include "E16ANA_TrackConstant.hh"
#include "E16ANA_GTRChannelManager.h"
#include "E16ANA_GTRStatus.h"
#include "E16ANA_GTRAnalyzerMaker.hh"
#include <TString.h>
// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>
#include <vector>
using namespace std;
namespace track_const = E16ANA_TrackConstant;
constexpr double kStepSize = 1;
constexpr int kMaxSteps = 400;
constexpr int kMinuitStrategy = 2;
constexpr int kMaxFunctionCalls = 1.0e4;
const int out_n_layer = 6;//including hbd,lg
const double xm_hitrange[3]     = {-2, -3, -4};// hit within -1 * yrange ~ yrange is regarded as a true hit
const double xp_hitrange[3]     = { 3, 2, 4};// hit within -1 * yrange ~ yrange is regarded as a true hit
const double x_clusterrange[3] = {2.75, 2.75, 3.5};// hit within -1 * yrange ~ yrange is regarded as a true hit
const double ym_hitrange[3]     = {-3, -5, -3};// hit within -1 * yrange ~ yrange is regarded as a true hit
const double yp_hitrange[3]     = { 4,  5,  3};// hit within -1 * yrange ~ yrange is regarded as a true hit
const double y_clusterrange[3] = {5, 5, 5};// hit within -1 * yrange ~ yrange is regarded as a true hit

const TVector3 zero_sigma = {0, 0, 0};
const TVector3 kTargetSigma = {3., 3., 0.};
//const TVector3 kTargetSigma = {1., 1., 0.};
const TVector3 kDetectorSigma[4]  = {{0.1, 0, 0}, {0.3, 1, 0}, {0.3, 1, 0},{0.3, 1, 0} };
// Fixed size dimensions of array or collections stored in the TTree if any.

class LayerEfficiencyCalculator {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   //added here 
   vector<double>  ass_hbd_resx;
   vector<double>  ass_hbd_resy;
   vector<int>     ass_hbd_cluster_id;
   vector<double>  mix_ass_hbd_resx;
   vector<double>  mix_ass_hbd_resy;
   vector<int>     mix_ass_hbd_cluster_id;
   vector<double>  ass_lg_resx;
   vector<double>  ass_lg_resy;
   vector<int>     ass_lg_hit_id;

   // Declaration of leaf types
   Int_t           run_id;
   Int_t           event_id;
   Int_t           n_cands;
   Int_t           spill_id;
   Int_t           n_tracks;
   vector<int>     *track_id;
   vector<double>  *chi_square;
   vector<int>     *rk_charge;
   vector<int>     *is_selected;
   vector<double>  *track_mom;
   vector<double>  *track_mom_x;
   vector<double>  *track_mom_y;
   vector<double>  *track_mom_z;
   vector<double>  *track_tgt_dist;
   vector<double>  *track_lg_pi_eff1;
   vector<double>  *track_lg_pi_eff2;
   vector<double>  *track_angle_lx;
   vector<double>  *track_angle_ly;
   vector<double>  *track_position_block_lx;
   vector<double>  *track_position_block_ly;
   vector<double>  *track_ssd_t;
   vector<double>  *track_ssd_adc;
   vector<double>  *track_gtr100x_t;
   vector<double>  *track_gtr100x_adc;
   vector<double>  *track_gtr100y_t;
   vector<double>  *track_gtr100y_adc;
   vector<double>  *track_gtr200x_t;
   vector<double>  *track_gtr200x_adc;
   vector<double>  *track_gtr200y_t;
   vector<double>  *track_gtr200y_adc;
   vector<double>  *track_gtr300x_t;
   vector<double>  *track_gtr300x_adc;
   vector<double>  *track_gtr300y_t;
   vector<double>  *track_gtr300y_adc;
   vector<int>     *track_hbd_mid;
   vector<double>  *track_hbd_lx;
   vector<double>  *track_hbd_ly;
   vector<double>  *track_hbd_nearx;
   vector<double>  *track_hbd_neary;
   vector<int>     *track_hbd_multiplicity;
   vector<double>  *track_hbd_dum_nearx;
   vector<double>  *track_hbd_dum_neary;
   vector<int>     *track_hbd_dum_multiplicity;
   vector<int>     *track_lg_mid;
   vector<double>  *track_lg_lx;
   vector<double>  *track_lg_ly;
   vector<double>  *track_lg_nearx;
   vector<double>  *track_lg_neary;
   vector<int>     *track_lg_multiplicity;
   vector<double>  *track_lg_dum_nearx;
   vector<double>  *track_lg_dum_neary;
   vector<int>     *track_lg_dum_multiplicity;
   vector<double>  *track_lg_cl_nearx;
   vector<double>  *track_lg_cl_neary;
   vector<int>     *track_lg_cl_multiplicity;
   vector<double>  *track_lg_cl_dum_nearx;
   vector<double>  *track_lg_cl_dum_neary;
   vector<int>     *track_lg_cl_dum_multiplicity;
   vector<vector<double> > *track_hbd_allhit_resx;
   vector<vector<double> > *track_hbd_allhit_resy;
   vector<vector<double> > *track_hbd_allhit_ftime;
   vector<vector<double> > *track_hbd_allhit_adc;
   vector<vector<double> > *track_hbd_allhit_size;
   vector<vector<double> > *track_hbd_allhit_eprob;
   vector<vector<double> > *track_hbd_allhit_cprob;
   vector<vector<double> > *track_hbd_allhit_dum_resx;
   vector<vector<double> > *track_hbd_allhit_dum_resy;
   vector<vector<double> > *track_hbd_allhit_dum_ftime;
   vector<vector<double> > *track_hbd_allhit_dum_adc;
   vector<vector<double> > *track_hbd_allhit_dum_size;
   vector<vector<double> > *track_hbd_allhit_dum_eprob;
   vector<vector<double> > *track_hbd_allhit_dum_cprob;
   vector<vector<double> > *track_lg_allhit_resx;//dst1 hit (bettet to use)
   vector<vector<double> > *track_lg_allhit_resy;
   vector<vector<double> > *track_lg_allhit_ftime;
   vector<vector<double> > *track_lg_allhit_adc;
   vector<vector<double> > *track_lg_allhit_dum_resx;
   vector<vector<double> > *track_lg_allhit_dum_resy;
   vector<vector<double> > *track_lg_allhit_dum_ftime;
   vector<vector<double> > *track_lg_allhit_dum_adc;
   vector<vector<double> > *track_lg_cl_allhit_resx;//dst1 cluster
   vector<vector<double> > *track_lg_cl_allhit_resy;
   vector<vector<double> > *track_lg_cl_allhit_ftime;
   vector<vector<double> > *track_lg_cl_allhit_adc;
   vector<vector<double> > *track_lg_cl_allhit_maxpeak;
   vector<vector<double> > *track_lg_cl_allhit_maxcid;
   vector<vector<double> > *track_lg_cl_allhit_dum_resx;
   vector<vector<double> > *track_lg_cl_allhit_dum_resy;
   vector<vector<double> > *track_lg_cl_allhit_dum_ftime;
   vector<vector<double> > *track_lg_cl_allhit_dum_adc;
   vector<vector<double> > *track_lg_cl_allhit_dum_maxpeak;
   vector<vector<double> > *track_lg_cl_allhit_dum_maxcid;
   
   vector<int> *trg_track_lg_id;
   vector<int> *trg_track_lg_mid;
   vector<int> *trg_track_lg_cid;
   vector<double> *trg_track_lg_x; 
   vector<double> *trg_track_lg_y; 
   vector<double> *trg_track_lg_t; 

   vector<double>  *l_hit_ssd_x;
   vector<double>  *l_hit_gtr100_x;
   vector<double>  *l_hit_gtr100_y;
   vector<double>  *l_hit_gtr200_x;
   vector<double>  *l_hit_gtr200_y;
   vector<double>  *l_hit_gtr300_x;
   vector<double>  *l_hit_gtr300_y;
//   vector<double>  *rk_hit_ssd_gx;
//   vector<double>  *rk_hit_ssd_gy;
//   vector<double>  *rk_hit_ssd_gz;
//   vector<double>  *rk_hit_gtr100_gx;
//   vector<double>  *rk_hit_gtr100_gy;
//   vector<double>  *rk_hit_gtr100_gz;
//   vector<double>  *rk_hit_gtr200_gx;
//   vector<double>  *rk_hit_gtr200_gy;
//   vector<double>  *rk_hit_gtr200_gz;
//   vector<double>  *rk_hit_gtr300_gx;
//   vector<double>  *rk_hit_gtr300_gy;
//   vector<double>  *rk_hit_gtr300_gz;
//   vector<double>  *rk_hit_gtr100_gtx;
//   vector<double>  *rk_hit_gtr100_gtx2;
//   vector<double>  *rk_hit_gtr100_gty;
//   vector<double>  *rk_hit_gtr100_gtz;
//   vector<double>  *rk_hit_gtr100_gtz2;
//   vector<double>  *rk_hit_gtr200_gtx;
//   vector<double>  *rk_hit_gtr200_gtx2;
//   vector<double>  *rk_hit_gtr200_gty;
//   vector<double>  *rk_hit_gtr200_gtz;
//   vector<double>  *rk_hit_gtr300_gtx;
//   vector<double>  *rk_hit_gtr200_gtz2;
//   vector<double>  *rk_hit_gtr300_gtx2;
//   vector<double>  *rk_hit_gtr300_gty;
//   vector<double>  *rk_hit_gtr300_gtz2;
//   vector<double>  *rk_hit_gtr300_gtz;
   vector<double>  *rk_res_ssd_x;
   vector<double>  *rk_res_gtr100_x;
   vector<double>  *rk_res_gtr100_y;
   vector<double>  *rk_res_gtr200_x;
   vector<double>  *rk_res_gtr200_y;
   vector<double>  *rk_res_gtr300_x;
   vector<double>  *rk_res_gtr300_y;
   vector<int>     *track_ssd_cluster_id;
   vector<int>     *track_ssd_cluster_mid;
   vector<int>     *track_gtr100x_cluster_id;
   vector<int>     *track_gtr200x_cluster_id;
   vector<int>     *track_gtr300x_cluster_id;
   vector<int>     *track_gtr100y_cluster_id;
   vector<int>     *track_gtr200y_cluster_id;
   vector<int>     *track_gtr300y_cluster_id;
   vector<int>     *track_gtr100yb_cluster_id;
   vector<int>     *track_gtr100_cluster_mid;
   vector<int>     *track_gtr200_cluster_mid;
   vector<int>     *track_gtr300_cluster_mid;
   vector<int>     *track_lg_hit_mid;
   vector<double>  *track_lg_t;
   vector<int>     *track_hbd_hit_mid;
//   vector<int>     *rk_hit_ssd_id;
//   vector<int>     *rk_hit_gtr100_xid;
//   vector<int>     *rk_hit_gtr200_xid;
//   vector<int>     *rk_hit_gtr300_xid;
//   vector<int>     *rk_hit_gtr100_yid;
//   vector<int>     *rk_hit_gtr200_yid;
//   vector<int>     *rk_hit_gtr300_yid;
vector<double>  *rk_hit_init_mom_gx;
   vector<double>  *rk_hit_init_mom_gy;
   vector<double>  *rk_hit_init_mom_gz;
   vector<double>  *rk_hit_init_pos_gx;
   vector<double>  *rk_hit_init_pos_gy;
   vector<double>  *rk_hit_init_pos_gz;
   vector<int>     *rk_hit_ssd_id;
   vector<double>  *rk_hit_ssd_gx;
   vector<double>  *rk_hit_ssd_gy;
   vector<double>  *rk_hit_ssd_gz;
   vector<float>   *rk_hit_ssd_adc;
   vector<float>   *rk_hit_ssd_t;
   vector<int>     *rk_hit_gtr100_xid;
   vector<int>     *rk_hit_gtr100_yid;
   vector<double>  *rk_hit_gtr100_gx;
   vector<double>  *rk_hit_gtr100_gy;
   vector<double>  *rk_hit_gtr100_gz;
   vector<double>  *rk_hit_gtr100_gtz;
   vector<double>  *rk_hit_gtr100_gtz2;
   vector<double>  *rk_hit_gtr200_gtz;
   vector<double>  *rk_hit_gtr200_gtz2;
   vector<double>  *rk_hit_gtr300_gtz;
   vector<double>  *rk_hit_gtr300_gtz2;
   vector<double>  *rk_hit_gtr100_gtx;
   vector<double>  *rk_hit_gtr100_gty;
   vector<double>  *rk_hit_gtr200_gty;
   vector<double>  *rk_hit_gtr300_gty;
   vector<double>  *rk_hit_gtr100_gtx2;
   vector<double>  *rk_hit_gtr200_gtx;
   vector<double>  *rk_hit_gtr200_gtx2;
   vector<double>  *rk_hit_gtr300_gtx;
   vector<double>  *rk_hit_gtr300_gtx2;
   vector<float>   *rk_hit_gtr100_xadc;
   vector<float>   *rk_hit_gtr100_yadc;
   vector<float>   *rk_hit_gtr100_xt;
   vector<float>   *rk_hit_gtr100_yt;
   vector<int>     *rk_hit_gtr200_xid;
   vector<int>     *rk_hit_gtr200_yid;
   vector<double>  *rk_hit_gtr200_gx;
   vector<double>  *rk_hit_gtr200_gy;
   vector<double>  *rk_hit_gtr200_gz;
   vector<float>   *rk_hit_gtr200_xadc;
   vector<float>   *rk_hit_gtr200_yadc;
   vector<float>   *rk_hit_gtr200_xt;
   vector<int>     *rk_hit_gtr300_xid;
   vector<int>     *rk_hit_gtr300_yid;
   vector<float>   *rk_hit_gtr200_yt;
   vector<double>  *rk_hit_gtr300_gx;
   vector<double>  *rk_hit_gtr300_gy;
   vector<double>  *rk_hit_gtr300_gz;
   vector<float>   *rk_hit_gtr300_xadc;
   vector<float>   *rk_hit_gtr300_yadc;
   vector<float>   *rk_hit_gtr300_xt;
   vector<float>   *rk_hit_gtr300_yt;
   

   vector<int>     *rk_fit_ssd_mid;
   vector<int>     *rk_fit_gtr100_mid;
   vector<int>     *rk_fit_gtr200_mid;
   vector<int>     *rk_fit_gtr300_mid;
   vector<double>  *rk_fit_gtr100_gx;
   vector<double>  *rk_fit_gtr100_gy;
   vector<double>  *rk_fit_gtr100_gz;
   vector<double>  *rk_fit_gtr200_gx;
   vector<double>  *rk_fit_gtr200_gy;
   vector<double>  *rk_fit_gtr200_gz;
   vector<double>  *rk_fit_gtr300_gx;
   vector<double>  *rk_fit_gtr300_gy;
   vector<double>  *rk_fit_gtr300_gz;
   vector<int>     *rk_fit_hbd_mid;
   vector<double>  *rk_fit_hbd_x;
   vector<double>  *rk_fit_hbd_y;
   vector<double>  *rk_fit_hbd_gx;
   vector<double>  *rk_fit_hbd_gy;
   vector<double>  *rk_fit_hbd_gz;
   vector<int>     *rk_fit_lg_c_mid;
   vector<double>  *rk_fit_lg_c_x;
   vector<double>  *rk_fit_lg_c_y;
   vector<double>  *rk_fit_lg_c_gx;
   vector<double>  *rk_fit_lg_c_gy;
   vector<double>  *rk_fit_lg_c_gz;
   vector<int>     *rk_fit_lg_b_mid;
   vector<double>  *rk_fit_lg_b_x;
   vector<double>  *rk_fit_lg_b_y;
   vector<double>  *rk_fit_lg_b_gx;
   vector<double>  *rk_fit_lg_b_gy;
   vector<double>  *rk_fit_lg_b_gz;
   vector<int>     *rk_fit_lg_a_mid;
   vector<double>  *rk_fit_lg_a_x;
   vector<double>  *rk_fit_lg_a_y;
   vector<double>  *rk_fit_lg_a_gx;
   vector<double>  *rk_fit_lg_a_gy;
   vector<double>  *rk_fit_lg_a_gz;

   Int_t           n_gtr100x_hits;
   vector<int>     *gtr100x_hit_id;   
   vector<int>     *gtr100x_hit_mid;   
   vector<int>     *gtr100x_hit_cid;   
   vector<double>  *gtr100x_hit_x;   
   vector<double>  *gtr100x_hit_tx;   
   vector<double>  *gtr100x_hit_gx;   
   vector<double>  *gtr100x_hit_gz;   
   vector<double>  *gtr100x_hit_t;   
   vector<float>  *gtr100x_hit_adc;   
   Int_t           n_gtr200x_hits;
   vector<int>     *gtr200x_hit_id;   
   vector<int>     *gtr200x_hit_mid;   
   vector<int>     *gtr200x_hit_cid;   
   vector<double>  *gtr200x_hit_x;   
   vector<double>  *gtr200x_hit_tx;   
   vector<double>  *gtr200x_hit_gx;   
   vector<double>  *gtr200x_hit_gz;   
   vector<double>  *gtr200x_hit_t;   
   vector<float>  *gtr200x_hit_adc;   
   Int_t           n_gtr300x_hits;
   vector<int>     *gtr300x_hit_id;   
   vector<int>     *gtr300x_hit_mid;   
   vector<int>     *gtr300x_hit_cid;   
   vector<double>  *gtr300x_hit_x;   
   vector<double>  *gtr300x_hit_tx;   
   vector<double>  *gtr300x_hit_gx;   
   vector<double>  *gtr300x_hit_gz;   
   vector<double>  *gtr300x_hit_t;   
   vector<float>  *gtr300x_hit_adc;   

   Int_t           n_gtr100y_hits;
   vector<int>     *gtr100y_hit_id;   
   vector<int>     *gtr100y_hit_mid;   
   vector<int>     *gtr100y_hit_cid;   
   vector<double>  *gtr100y_hit_y;   
   vector<double>  *gtr100y_hit_ty;   
   vector<double>  *gtr100y_hit_t;   
   vector<float>  *gtr100y_hit_adc;   
   Int_t           n_gtr100yb_hits;
   vector<int>     *gtr100yb_hit_id;   
   vector<int>     *gtr100yb_hit_mid;   
   vector<int>     *gtr100yb_hit_cid;   
   vector<double>  *gtr100yb_hit_y;   
   vector<double>  *gtr100yb_hit_ty;   
   vector<double>  *gtr100yb_hit_t;   
   vector<float>  *gtr100yb_hit_adc;   
 
   Int_t           n_gtr200y_hits;
   vector<int>     *gtr200y_hit_id;   
   vector<int>     *gtr200y_hit_mid;   
   vector<int>     *gtr200y_hit_cid;   
   vector<double>  *gtr200y_hit_y;   
   vector<double>  *gtr200y_hit_ty;   
   vector<double>  *gtr200y_hit_t;   
   vector<float>  *gtr200y_hit_adc;   
   Int_t           n_gtr300y_hits;
   vector<int>     *gtr300y_hit_id;   
   vector<int>     *gtr300y_hit_mid;   
   vector<int>     *gtr300y_hit_cid;   
   vector<double>  *gtr300y_hit_y;   
   vector<double>  *gtr300y_hit_ty;   
   vector<double>  *gtr300y_hit_t;   
   vector<float>  *gtr300y_hit_adc;   








   vector<int>         *ssd_cluster_size;
   vector<int>         *gtr100x_cluster_size;
   vector<int>         *gtr200x_cluster_size;
   vector<int>         *gtr300x_cluster_size;
   vector<int>         *gtr100y_cluster_size;
   vector<int>         *gtr100yb_cluster_size;
   vector<int>         *gtr200y_cluster_size;
   vector<int>         *gtr300y_cluster_size;
   Int_t         n_ssd_clusters;
   vector<int>     *ssd_cluster_id;
   vector<int>     *ssd_cluster_mid;
   vector<double>  *ssd_cluster_x;
   vector<double>  *ssd_cluster_gx;
   vector<double>  *ssd_cluster_gz;
   vector<float>   *ssd_cluster_adc;
   vector<double>  *ssd_cluster_t;
   Int_t           n_gtr100x_clusters;
   vector<int>     *gtr100x_cluster_id;
   vector<int>     *gtr100x_cluster_mid;
   vector<double>  *gtr100x_cluster_x;
   vector<double>  *gtr100x_cluster_gx;
   vector<double>  *gtr100x_cluster_gz;
   vector<float>   *gtr100x_cluster_adc;
   vector<double>  *gtr100x_cluster_t;
   vector<double>  *gtr100x_cluster_t2;
   Int_t           n_gtr200x_clusters;
   vector<int>     *gtr200x_cluster_id;
   vector<int>     *gtr200x_cluster_mid;
   vector<double>  *gtr200x_cluster_x;
   vector<double>  *gtr200x_cluster_gx;
   vector<double>  *gtr200x_cluster_gz;
   vector<float>   *gtr200x_cluster_adc;
   vector<double>  *gtr200x_cluster_t;
   vector<double>  *gtr200x_cluster_t2;
   Int_t           n_gtr300x_clusters;
   vector<int>     *gtr300x_cluster_id;
   vector<int>     *gtr300x_cluster_mid;
   vector<double>  *gtr300x_cluster_x;
   vector<double>  *gtr300x_cluster_gx;
   vector<double>  *gtr300x_cluster_gz;
   vector<float>   *gtr300x_cluster_adc;
   vector<double>  *gtr300x_cluster_t;
   vector<double>  *gtr300x_cluster_t2;
   Int_t           n_gtr100y_clusters;
   vector<int>     *gtr100y_cluster_id;
   vector<int>     *gtr100y_cluster_mid;
   vector<double>  *gtr100y_cluster_y;
   vector<float>   *gtr100y_cluster_adc;
   vector<double>  *gtr100y_cluster_t;
   vector<double>  *gtr100y_cluster_t2;
   Int_t           n_gtr100yb_clusters;
   vector<int>     *gtr100yb_cluster_id;
   vector<int>     *gtr100yb_cluster_mid;
   vector<double>  *gtr100yb_cluster_y;
   vector<float>   *gtr100yb_cluster_adc;
   vector<double>  *gtr100yb_cluster_t;
   vector<double>  *gtr100yb_cluster_t2;
   Int_t           n_gtr200y_clusters;
   vector<int>     *gtr200y_cluster_id;
   vector<int>     *gtr200y_cluster_mid;
   vector<double>  *gtr200y_cluster_y;
   vector<float>   *gtr200y_cluster_adc;
   vector<double>  *gtr200y_cluster_t;
   vector<double>  *gtr200y_cluster_t2;
   Int_t           n_gtr300y_clusters;
   vector<int>     *gtr300y_cluster_id;
   vector<int>     *gtr300y_cluster_mid;
   vector<double>  *gtr300y_cluster_y;
   vector<float>   *gtr300y_cluster_adc;
   vector<double>  *gtr300y_cluster_t;
   vector<double>  *gtr300y_cluster_t2;

   Int_t           n_hbd_clusters;
   vector<int>     *hbd_cluster_id;
   vector<int>     *hbd_cluster_mid;
   vector<double>  *hbd_cluster_x;
   vector<double>  *hbd_cluster_y;
   vector<double>  *hbd_cluster_gx;
   vector<double>  *hbd_cluster_gy;
   vector<double>  *hbd_cluster_gz;
   vector<float>   *hbd_cluster_adc;
   vector<double>  *hbd_cluster_t;
   vector<float>   *hbd_cluster_ftime;
   vector<float>   *hbd_cluster_tdiff;
   vector<int>     *hbd_cluster_size;
   vector<float>   *hbd_cluster_eprob;
   vector<float>   *hbd_cluster_cprob;
   Int_t           n_lg_hits;
   vector<int>     *lg_hit_id;
   vector<int>     *lg_hit_mid;
   vector<int>     *lg_hit_cid;
   vector<double>  *lg_hit_x;
   vector<double>  *lg_hit_y;
   vector<double>  *lg_hit_gx;
   vector<double>  *lg_hit_gy;
   vector<double>  *lg_hit_gz;
   vector<float>   *lg_hit_adc;
   vector<float>   *lg_hit_t;
   vector<int>     *lg_hit_npeaks;
   vector<int>     *lg_hit_fflag;

   // List of branches
   TBranch        *b_run_id;   //!
   TBranch        *b_event_id;   //!
   TBranch        *b_n_cands;   //!
   TBranch        *b_spill_id;   //!
   TBranch        *b_n_tracks;   //!
   TBranch        *b_track_id;   //!
   TBranch        *b_chi_square;   //!
   TBranch        *b_rk_charge;   //!
   TBranch        *b_is_selected;   //!
   TBranch        *b_track_mom;   //!
   TBranch        *b_track_mom_x;   //!
   TBranch        *b_track_mom_y;   //!
   TBranch        *b_track_mom_z;   //!
   TBranch        *b_track_tgt_dist;   //!
   TBranch        *b_track_lg_pi_eff1;   //!
   TBranch        *b_track_lg_pi_eff2;   //!
   TBranch        *b_track_angle_lx;   //!
   TBranch        *b_track_angle_ly;   //!
   TBranch        *b_track_position_block_lx;   //!
   TBranch        *b_track_position_block_ly;   //!
   TBranch        *b_track_ssd_t;   //!
   TBranch        *b_track_ssd_adc;   //!
   TBranch        *b_track_gtr100x_t;   //!
   TBranch        *b_track_gtr100x_adc;   //!
   TBranch        *b_track_gtr100y_t;   //!
   TBranch        *b_track_gtr100y_adc;   //!
   TBranch        *b_track_gtr200x_t;   //!
   TBranch        *b_track_gtr200x_adc;   //!
   TBranch        *b_track_gtr200y_t;   //!
   TBranch        *b_track_gtr200y_adc;   //!
   TBranch        *b_track_gtr300x_t;   //!
   TBranch        *b_track_gtr300x_adc;   //!
   TBranch        *b_track_gtr300y_t;   //!
   TBranch        *b_track_gtr300y_adc;   //!
   TBranch        *b_track_hbd_mid;   //!
   TBranch        *b_track_hbd_lx;   //!
   TBranch        *b_track_hbd_ly;   //!
   TBranch        *b_track_hbd_nearx;   //!
   TBranch        *b_track_hbd_neary;   //!
   TBranch        *b_track_hbd_multiplicity;   //!
   TBranch        *b_track_hbd_dum_nearx;   //!
   TBranch        *b_track_hbd_dum_neary;   //!
   TBranch        *b_track_hbd_dum_multiplicity;   //!
   TBranch        *b_track_lg_t;
   TBranch        *b_track_lg_mid;   //!
   TBranch        *b_track_lg_lx;   //!
   TBranch        *b_track_lg_ly;   //!
   TBranch        *b_track_lg_nearx;   //!
   TBranch        *b_track_lg_neary;   //!
   TBranch        *b_track_lg_multiplicity;   //!
   TBranch        *b_track_lg_dum_nearx;   //!
   TBranch        *b_track_lg_dum_neary;   //!
   TBranch        *b_track_lg_dum_multiplicity;   //!
   TBranch        *b_track_lg_cl_nearx;   //!
   TBranch        *b_track_lg_cl_neary;   //!
   TBranch        *b_track_lg_cl_multiplicity;   //!
   TBranch        *b_track_lg_cl_dum_nearx;   //!
   TBranch        *b_track_lg_cl_dum_neary;   //!
   TBranch        *b_track_lg_cl_dum_multiplicity;   //!
   TBranch        *b_track_hbd_allhit_resx;   //!
   TBranch        *b_track_hbd_allhit_resy;   //!
   TBranch        *b_track_hbd_allhit_ftime;   //!
   TBranch        *b_track_hbd_allhit_adc;   //!
   TBranch        *b_track_hbd_allhit_size;   //!
   TBranch        *b_track_hbd_allhit_eprob;   //!
   TBranch        *b_track_hbd_allhit_cprob;   //!
   TBranch        *b_track_hbd_allhit_dum_resx;   //!
   TBranch        *b_track_hbd_allhit_dum_resy;   //!
   TBranch        *b_track_hbd_allhit_dum_ftime;   //!
   TBranch        *b_track_hbd_allhit_dum_adc;   //!
   TBranch        *b_track_hbd_allhit_dum_size;   //!
   TBranch        *b_track_hbd_allhit_dum_eprob;   //!
   TBranch        *b_track_hbd_allhit_dum_cprob;   //!
   TBranch        *b_track_lg_allhit_resx;   //!
   TBranch        *b_track_lg_allhit_resy;   //!
   TBranch        *b_track_lg_allhit_ftime;   //!
   TBranch        *b_track_lg_allhit_adc;   //!
   TBranch        *b_track_lg_allhit_dum_resx;   //!
   TBranch        *b_track_lg_allhit_dum_resy;   //!
   TBranch        *b_track_lg_allhit_dum_ftime;   //!
   TBranch        *b_track_lg_allhit_dum_adc;   //!
   TBranch        *b_track_lg_cl_allhit_resx;   //!
   TBranch        *b_track_lg_cl_allhit_resy;   //!
   TBranch        *b_track_lg_cl_allhit_ftime;   //!
   TBranch        *b_track_lg_cl_allhit_adc;   //!
   TBranch        *b_track_lg_cl_allhit_maxpeak;   //!
   TBranch        *b_track_lg_cl_allhit_maxcid;   //!
   TBranch        *b_track_lg_cl_allhit_dum_resx;   //!
   TBranch        *b_track_lg_cl_allhit_dum_resy;   //!
   TBranch        *b_track_lg_cl_allhit_dum_ftime;   //!
   TBranch        *b_track_lg_cl_allhit_dum_adc;   //!
   TBranch        *b_track_lg_cl_allhit_dum_maxpeak;   //!
   TBranch        *b_track_lg_cl_allhit_dum_maxcid;   //!

   TBranch        *b_trg_track_lg_id;
   TBranch        *b_trg_track_lg_mid;
   TBranch        *b_trg_track_lg_cid;
   TBranch        *b_trg_track_lg_x; 
   TBranch        *b_trg_track_lg_y; 
   TBranch        *b_trg_track_lg_t; 



//   TBranch        *b_rk_hit_ssd_gx;   //!
//
//
//   TBranch        *b_rk_hit_ssd_gy;   //!
//   TBranch        *b_rk_hit_ssd_gz;   //!
//   TBranch        *b_rk_hit_gtr100_gx;   //!
//   TBranch        *b_rk_hit_gtr100_gy;   //!
//   TBranch        *b_rk_hit_gtr100_gz;   //!
//   TBranch        *b_rk_hit_gtr200_gx;   //!
//   TBranch        *b_rk_hit_gtr200_gy;   //!
//   TBranch        *b_rk_hit_gtr200_gz;   //!
//   TBranch        *b_rk_hit_gtr300_gx;   //!
//   TBranch        *b_rk_hit_gtr300_gy;   //!
//   TBranch        *b_rk_hit_gtr300_gz;   //!
//   TBranch        *b_rk_hit_gtr100_gtx;   //!
//   TBranch        *b_rk_hit_gtr100_gty;   //!
//   TBranch        *b_rk_hit_gtr200_gty;   //!
//   TBranch        *b_rk_hit_gtr300_gty;   //!
//   TBranch        *b_rk_hit_gtr100_gtz;   //!
//   TBranch        *b_rk_hit_gtr200_gtx;   //!
//   TBranch        *b_rk_hit_gtr200_gtz;   //!
//   TBranch        *b_rk_hit_gtr300_gtx;   //!
//   TBranch        *b_rk_hit_gtr300_gtz;   //!
//   TBranch        *b_rk_hit_gtr100_gtx2;   //!
//   TBranch        *b_rk_hit_gtr100_gtz2;   //!
//   TBranch        *b_rk_hit_gtr200_gtx2;   //!
//   TBranch        *b_rk_hit_gtr200_gtz2;   //!
//   TBranch        *b_rk_hit_gtr300_gtx2;   //!
//   TBranch        *b_rk_hit_gtr300_gtz2;   //!
   TBranch        *b_track_ssd_cluster_id;   //!
   TBranch        *b_track_ssd_cluster_mid;   //!
   TBranch        *b_track_gtr100x_cluster_id;   //!
   TBranch        *b_track_gtr200x_cluster_id;   //!
   TBranch        *b_track_gtr300x_cluster_id;   //!
   TBranch        *b_track_gtr100y_cluster_id;   //!
   TBranch        *b_track_gtr200y_cluster_id;   //!
   TBranch        *b_track_gtr300y_cluster_id;   //!
   TBranch        *b_track_gtr100yb_cluster_id;   //!
   TBranch        *b_track_gtr100_cluster_mid;   //!
   TBranch        *b_track_gtr200_cluster_mid;   //!
   TBranch        *b_track_gtr300_cluster_mid;   //!
   

   TBranch        *b_l_hit_ssd_x;
   TBranch        *b_l_hit_gtr100_x;
   TBranch        *b_l_hit_gtr100_y;
   TBranch        *b_l_hit_gtr200_x;
   TBranch        *b_l_hit_gtr200_y;
   TBranch        *b_l_hit_gtr300_x;
   TBranch        *b_l_hit_gtr300_y;
//   TBranch        *b_rk_hit_ssd_id;
//   TBranch        *b_rk_hit_gtr100_xid;
//   TBranch        *b_rk_hit_gtr200_xid;
//   TBranch        *b_rk_hit_gtr300_xid;
//   TBranch        *b_rk_hit_gtr100_yid;
//   TBranch        *b_rk_hit_gtr200_yid;
//   TBranch        *b_rk_hit_gtr300_yid;
   TBranch        *b_rk_res_ssd_x;
   TBranch        *b_rk_res_gtr100_x;
   TBranch        *b_rk_res_gtr100_y;
   TBranch        *b_rk_res_gtr200_x;
   TBranch        *b_rk_res_gtr200_y;
   TBranch        *b_rk_res_gtr300_x;
   TBranch        *b_rk_res_gtr300_y;
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
   TBranch        *b_rk_hit_gtr100_gtx;   //!
   TBranch        *b_rk_hit_gtr100_gtx2;   //!
   TBranch        *b_rk_hit_gtr100_gty;   //!
   TBranch        *b_rk_hit_gtr100_gtz;   //!
   TBranch        *b_rk_hit_gtr100_gtz2;   //!
   TBranch        *b_rk_hit_gtr200_gtz;   //!
   TBranch        *b_rk_hit_gtr200_gtz2;   //!
   TBranch        *b_rk_hit_gtr300_gtz;   //!
   TBranch        *b_rk_hit_gtr300_gtz2;   //!
   TBranch        *b_rk_hit_gtr200_gty;   //!
   TBranch        *b_rk_hit_gtr300_gty;   //!
   TBranch        *b_rk_hit_gtr200_gtx;   //!
   TBranch        *b_rk_hit_gtr200_gtx2;   //!
   TBranch        *b_rk_hit_gtr300_gtx;   //!
   TBranch        *b_rk_hit_gtr300_gtx2;   //!
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
  

  TBranch    *b_rk_fit_ssd_mid;
  TBranch    *b_rk_fit_gtr100_mid;
  TBranch    *b_rk_fit_gtr200_mid;
  TBranch    *b_rk_fit_gtr300_mid;
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
   TBranch        *b_rk_fit_lg_a_gz;   




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
   TBranch        *b_lg_hit_cid;   //!
   TBranch        *b_lg_hit_x;   //!
   TBranch        *b_lg_hit_y;   //!
   TBranch        *b_lg_hit_gx;   //!
   TBranch        *b_lg_hit_gy;   //!
   TBranch        *b_lg_hit_gz;   //!
   TBranch        *b_lg_hit_adc;   //!
   TBranch        *b_lg_hit_t;   //!
   TBranch        *b_lg_hit_npeaks;   //!
   TBranch        *b_lg_hit_fflag;   //!
 

//220512 add
//
//
   TBranch        *b_rk_fit_gtr100_gx;   //!
   TBranch        *b_rk_fit_gtr100_gy;   //!
   TBranch        *b_rk_fit_gtr100_gz;   //!
   TBranch        *b_rk_fit_gtr200_gx;   //!
   TBranch        *b_rk_fit_gtr200_gy;   //!
   TBranch        *b_rk_fit_gtr200_gz;   //!
   TBranch        *b_rk_fit_gtr300_gx;   //!
   TBranch        *b_rk_fit_gtr300_gy;   //!
   TBranch        *b_rk_fit_gtr300_gz;   //!
 
   TBranch  *b_n_gtr100x_hits;
   TBranch  *b_n_gtr200x_hits;
   TBranch  *b_n_gtr300x_hits;
   TBranch  *b_n_gtr100y_hits;
   TBranch  *b_n_gtr100yb_hits;
   TBranch  *b_n_gtr200y_hits;
   TBranch  *b_n_gtr300y_hits;
   TBranch  *b_gtr100x_hit_id;   
   TBranch  *b_gtr100x_hit_mid;   
   TBranch  *b_gtr100x_hit_cid;   
   TBranch  *b_gtr100x_hit_x;   
   TBranch  *b_gtr100x_hit_tx;   
   TBranch  *b_gtr100x_hit_gx;   
   TBranch  *b_gtr100x_hit_gz;   
   TBranch  *b_gtr100x_hit_t;   
   TBranch  *b_gtr100x_hit_adc;   
   TBranch  *b_gtr200x_hit_id;   
   TBranch  *b_gtr200x_hit_mid;   
   TBranch  *b_gtr200x_hit_cid;   
   TBranch  *b_gtr200x_hit_x;   
   TBranch  *b_gtr200x_hit_tx;   
   TBranch  *b_gtr200x_hit_gx;   
   TBranch  *b_gtr200x_hit_gz;   
   TBranch  *b_gtr200x_hit_t;   
   TBranch  *b_gtr200x_hit_adc;   
   TBranch  *b_gtr300x_hit_id;   
   TBranch  *b_gtr300x_hit_mid;   
   TBranch  *b_gtr300x_hit_cid;   
   TBranch  *b_gtr300x_hit_x;   
   TBranch  *b_gtr300x_hit_tx;   
   TBranch  *b_gtr300x_hit_gx;   
   TBranch  *b_gtr300x_hit_gz;   
   TBranch  *b_gtr300x_hit_t;   
   TBranch  *b_gtr300x_hit_adc;   

   TBranch  *b_gtr100y_hit_id;   
   TBranch  *b_gtr100y_hit_mid;   
   TBranch  *b_gtr100y_hit_cid;   
   TBranch  *b_gtr100y_hit_y;   
   TBranch  *b_gtr100y_hit_ty;   
   TBranch  *b_gtr100y_hit_t;   
   TBranch  *b_gtr100y_hit_adc;   
   TBranch  *b_gtr100yb_hit_id;   
   TBranch  *b_gtr100yb_hit_mid;   
   TBranch  *b_gtr100yb_hit_cid;   
   TBranch  *b_gtr100yb_hit_y;   
   TBranch  *b_gtr100yb_hit_ty;   
   TBranch  *b_gtr100yb_hit_t;   
   TBranch  *b_gtr100yb_hit_adc;   
 
   TBranch  *b_gtr200y_hit_id;   
   TBranch  *b_gtr200y_hit_mid;   
   TBranch  *b_gtr200y_hit_cid;   
   TBranch  *b_gtr200y_hit_y;   
   TBranch  *b_gtr200y_hit_ty;   
   TBranch  *b_gtr200y_hit_t;   
   TBranch  *b_gtr200y_hit_adc;   
   TBranch  *b_gtr300y_hit_id;   
   TBranch  *b_gtr300y_hit_mid;   
   TBranch  *b_gtr300y_hit_cid;   
   TBranch  *b_gtr300y_hit_y;   
   TBranch  *b_gtr300y_hit_ty;   
   TBranch  *b_gtr300y_hit_t;   
   TBranch  *b_gtr300y_hit_adc;   








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
   TBranch        *b_gtr100x_cluster_t2;   //!
   TBranch        *b_n_gtr200x_clusters;   //!
   TBranch        *b_gtr200x_cluster_id;   //!
   TBranch        *b_gtr200x_cluster_mid;   //!
   TBranch        *b_gtr200x_cluster_x;   //!
   TBranch        *b_gtr200x_cluster_gx;   //!
   TBranch        *b_gtr200x_cluster_gz;   //!
   TBranch        *b_gtr200x_cluster_adc;   //!
   TBranch        *b_gtr200x_cluster_t;   //!
   TBranch        *b_gtr200x_cluster_t2;   //!
   TBranch        *b_n_gtr300x_clusters;   //!
   TBranch        *b_gtr300x_cluster_id;   //!
   TBranch        *b_gtr300x_cluster_mid;   //!
   TBranch        *b_gtr300x_cluster_x;   //!
   TBranch        *b_gtr300x_cluster_gx;   //!
   TBranch        *b_gtr300x_cluster_gz;   //!
   TBranch        *b_gtr300x_cluster_adc;   //!
   TBranch        *b_gtr300x_cluster_t;   //!
   TBranch        *b_gtr300x_cluster_t2;   //!
   TBranch        *b_n_gtr100y_clusters;   //!
   TBranch        *b_gtr100y_cluster_id;   //!
   TBranch        *b_gtr100y_cluster_mid;   //!
   TBranch        *b_gtr100y_cluster_y;   //!
   TBranch        *b_gtr100y_cluster_adc;   //!
   TBranch        *b_gtr100y_cluster_t;   //!
   TBranch        *b_gtr100y_cluster_t2;   //!
   TBranch        *b_n_gtr100yb_clusters;   //!
   TBranch        *b_gtr100yb_cluster_id;   //!
   TBranch        *b_gtr100yb_cluster_mid;   //!
   TBranch        *b_gtr100yb_cluster_y;   //!
   TBranch        *b_gtr100yb_cluster_adc;   //!
   TBranch        *b_gtr100yb_cluster_t;   //!
   TBranch        *b_gtr100yb_cluster_t2;   //!
   TBranch        *b_n_gtr200y_clusters;   //!
   TBranch        *b_gtr200y_cluster_id;   //!
   TBranch        *b_gtr200y_cluster_mid;   //!
   TBranch        *b_gtr200y_cluster_y;   //!
   TBranch        *b_gtr200y_cluster_adc;   //!
   TBranch        *b_gtr200y_cluster_t;   //!
   TBranch        *b_gtr200y_cluster_t2;   //!
   TBranch        *b_n_gtr300y_clusters;   //!
   TBranch        *b_gtr300y_cluster_id;   //!
   TBranch        *b_gtr300y_cluster_mid;   //!
   TBranch        *b_gtr300y_cluster_y;   //!
   TBranch        *b_gtr300y_cluster_adc;   //!
   TBranch        *b_gtr300y_cluster_t;   //!  
   TBranch        *b_gtr300y_cluster_t2;   //!

TBranch    *b_ssd_cluster_size ;
TBranch       *b_gtr100x_cluster_size; 
TBranch       *b_gtr200x_cluster_size; 
TBranch       *b_gtr300x_cluster_size; 
TBranch       *b_gtr100y_cluster_size; //
TBranch       *b_gtr100yb_cluster_size;
TBranch       *b_gtr200y_cluster_size;
TBranch       *b_gtr300y_cluster_size; 


   TFile *out_file;
   TTree *out_tree;
   double trk_mom;
   double trk_mom_x;
   double trk_mom_y;
   double trk_mom_z;
   double trk_tgt_dist;
   double detector_adc_x[out_n_layer];
   double detector_t_x[out_n_layer];
   double detector_adc_y[out_n_layer];
   double detector_t_y[out_n_layer];

   int module_id[out_n_layer];
   int trk_charge;
   int n_cluster_inrange;
   int dum_n_cluster_inrange;
   double pre_chi_square;
   double post_chi_square;
   double post_3l_chi_square[4];
   double post_detector_lx[out_n_layer];
   double post_detector_ly[out_n_layer];

   //double post_detector_res_x[out_n_layer];//detector resolution fit with 4 layers
   double post_detector_res_x[out_n_layer];//detector resolution fit with 4 layers
   double post_detector_res_y[out_n_layer];
   double post_3l_detector_res_x[out_n_layer][out_n_layer];//detector resolution fit with 3 layer
   double post_3l_detector_res_y[out_n_layer][out_n_layer];
   double post_wo_tgt_detector_res_x[out_n_layer];
   double post_wo_tgt_detector_res_y[out_n_layer];
   double post_wo_tgt_chi_square;
   double post_wo_tgt_fit_tgtpj_x;//tgt
   double post_wo_tgt_fit_tgtpj_y;//tgt
   double post_wo_tgt_fit_tgtpj_z;//tgt
//   double lg_t;
//   double ssd_t;
   double pre_detector_res_x[out_n_layer];
   double pre_detector_res_y[out_n_layer];
   double post_fit_tgtpj_x;//tgt
   double post_fit_tgtpj_y;//tgt
   double post_fit_tgtpj_z;//tgt

   double dum_rk_fit_gtr_gx[10][2];//dummy
   double dum_rk_fit_gtr_gy[10][2];
   double dum_rk_fit_gtr_gz[10][2];
   double dum_rk_fit_gtr_y[10][2];
   double dum2_rk_fit_gtr_gx[10][2];//dummy
   double dum2_rk_fit_gtr_gy[10][2];
   double dum2_rk_fit_gtr_gz[10][2];
   double dum_rk_fit_lg_c_x[10];
   double dum_rk_fit_lg_b_x[10];
   double dum_rk_fit_lg_a_x[10];
   int    memoryk;
   // Set branch addresses and branch pointers
   //if (!tree) return;
   E16ANA_MultiTrack *fitter;
   LayerEfficiencyCalculator(char* out_file_name, TChain *chain, E16ANA_MultiTrack *_fitter, int maxevent, int rm_size);
   LayerEfficiencyCalculator(TTree *tree, E16ANA_MultiTrack *_fitter, int maxevent);
   virtual ~LayerEfficiencyCalculator();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   //virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   std::vector<int> selected_track_indexes;
   void Calculate();
//   bool IsTimingMatchSSDAndLG(int track_id, vector<int> &lg_hit_id);
   bool CheckUsedClusters(int track_index, std::array<std::vector<int>, 6>* used_cluster_ids);
   bool CheckUsedClustersForMix(int track_index, std::array<std::vector<int>, 6>* used_cluster_ids);
   bool IsGoodHBDAssociation(int track_index, std::vector<double> &v, std::vector<double> &vv);
   bool IsGoodLGAssociation(int track_index);
   bool IsTriggerdTrack(int tid);
   int  LGLocalToCh(double lx, double ly);
   bool IsHittedOnSurvivalArea(E16ANA_GTRStatus *gtr_status, E16ANA_GTRAnalyzerMaker *gtr_analyzers, int track_index);
//   void RKAnalyze(E16ANA_MultiTrack *fitter);
   void CalculateResiduals(int &cnt);
   void CalculateResidualsUsingHits(int &cnt);
   void CalculateResidualsUsingRawHits(int &cnt);
   void CalculateResidualsX(int tid, int &ncluster, int &dum_ncluster, bool IsBeforeY);
   void CalculateResidualsXUsingHits(int tid, int &ncluster, int &dum_ncluster, bool IsBeforeY);
   void CalculateResidualsXUsingRawHits(int tid, int &ncluster, int &dum_ncluster);
   bool AssociationGTRY(int tid, int &ncluster, int &dum_ncluster);
   bool AssociationGTRYUsingHit(int tid, int &ncluster, int &dum_ncluster);
   void SelectTrack(E16ANA_GTRStatus *gtr_status, E16ANA_GTRAnalyzerMaker *gtr_analyzers, int track_index, std::array<std::vector<int>,6> *used_cluster_ids, int &cnt);
   double  SelectTracks(E16ANA_GTRStatus *gtr_status, E16ANA_GTRAnalyzerMaker *gtr_analyzers);
   void Clear();
   double  EvalTrueTrackRatioByLGX(E16ANA_GTRStatus *gtr_status, E16ANA_GTRAnalyzerMaker *gtr_analyzers, int &cnt);
   void EvaluateBGOfLGHits(int mid);
   
	
   void AssociateHBDCluster(int track_id, std::vector<double> &v, std::vector<double> &vv, std::vector<int> &i);
   void AssociateLGHit(int track_id);
   TFile* GetOutFile(){return out_file;}
private:
   int maxevent;
   int rm_size;
   vector<vector<int>> matched_lghit_ids;
   TH1D *h_fit_profile[10];
   TH1D *h_y_hit_adc[10];


   TH1D *h_n_cluster_inrange[10];
   TH1D *h_n_cluster_inrange_y[10];
   TH1D *h_n_cluster_inrange_wo_Y[10];
   TH1D *h_dum_n_cluster_inrange_wo_Y[10];
   TH1D *h_all_cut_n_cluster_inrange[10];
   TH1D *h_dum_n_cluster_inrange[10];
   TH1D *h_dum_n_cluster_inrange_y[10];
   TH1D *h_hbd_res_x[10];
   TH1D *h_hbd_res_y[10];
   TH1D *h_lg_res_x[10];
   TH1D *h_lg_res_y[10];
   TH1D *h_gtr_res_all_x[10];
   TH1D *h_gtr_res_all_x_wo_Y[10];
   TH1D *h_dum_gtr_res_all_x_wo_Y[10];
   TH1D *h_gtr_res_min_x[10];
   TH1D *h_gtr_res_min_y[10];
   TH1D *h_dum_gtr_res_min_x[10];
   TH1D *h_dum_gtr_res_all_x[10];
   TH1D *h_gtr_res_all_y[10];
   TH1D *h_dum_gtr_res_all_y[10];
   TH1D *h_n_lg_hits_inrange[10];
   TH1D *h_n_lg_dum_hits_inrange[10];
   TH1D *h_mix_dum_lg_res_x[10][10];
   TH1D *h_mix_true_lg_res_x[10][10];
   TH1D *h_mix_all_dum_lg_res_x[10][10];
   TH1D *h_mix_all_true_lg_res_x[10][10];
   TH2D *h_rk_hit_plane[10];
   TH2D *h_hit_fit[10];
   TH1D *h_timingx_dis[10];
   TH1D *h_timingx2_dis[10];
   TH1D *h_timingy_dis[10];
   TH1D *h_timingy2_dis[10];
   TH2D *h_timing_corr_xy[10];
   TH2D *h_timing2_corr_xy[10];
   TH1D *h_timing_diff[10];
   TH1D *h_timing2_diff[10];
   
};

#endif


LayerEfficiencyCalculator::LayerEfficiencyCalculator(char* out_file_name, TChain *chain, E16ANA_MultiTrack *_fitter, int _maxevent, int _rm_size)
 : fChain(0) , fitter(_fitter), maxevent(_maxevent),rm_size(_rm_size)  
{
//   out_file = new TFile("./dst1ana_out/outgtr_test.root", "recreate");
   out_file = new TFile(out_file_name, "recreate" );
   out_tree = new TTree("tree", "tree");
   out_tree->Branch("module_id", &module_id, "module_id[6]/I");
   out_tree->Branch("trk_charge", &trk_charge, "trk_charge/I");
   out_tree->Branch("n_cluster_inrange", &n_cluster_inrange, "n_cluster_inrange/I");
//   out_tree->Branch("all_cut_n_cluster_inrange", &all_cut_n_cluster_inrange, "all_cut_n_cluster_inrange/I");
   out_tree->Branch("dum_n_cluster_inrange", &dum_n_cluster_inrange, "dum_n_cluster_inrange/I");
   out_tree->Branch("pre_chi_square", &pre_chi_square, "pre_chi_square/D");
   out_tree->Branch("post_chi_square", &post_chi_square, "post_chi_square/D");
   out_tree->Branch("post_3l_chi_square", &post_3l_chi_square, "post_3l_chi_square[4]/D");
   out_tree->Branch("post_detector_lx", &post_detector_lx, "post_detector_lx[6]/D");
   out_tree->Branch("post_detector_res_x", &post_detector_res_x, "post_detector_res_x[6]/D");
   out_tree->Branch("post_3l_detector_res_x", &post_3l_detector_res_x, "post_3l_detector_res_x[6][6]/D");
   out_tree->Branch("post_detector_ly", &post_detector_ly, "post_detector_ly[6]/D");
   out_tree->Branch("post_detector_res_y", &post_detector_res_y, "post_detector_res_y[6]/D");
   out_tree->Branch("post_3l_detector_res_y", &post_3l_detector_res_y, "post_3l_detector_res_y[6][6]/D");
   out_tree->Branch("pre_detector_res_x", &pre_detector_res_x, "pre_detector_res_x[6]/D");
   out_tree->Branch("pre_detector_res_y", &pre_detector_res_y, "pre_detector_res_y[6]/D");
   out_tree->Branch("post_wo_tgt_detector_res_x", &post_wo_tgt_detector_res_x, "post_wo_tgt_detector_res_x[6]/D");
   out_tree->Branch("post_wo_tgt_detector_res_y", &post_wo_tgt_detector_res_y, "post_wo_tgt_detector_res_y[6]/D");
   out_tree->Branch("post_wo_tgt_fit_tgtpj_x", &post_wo_tgt_fit_tgtpj_x, "post_wo_tgt_fit_tgtpj_x/D");
   out_tree->Branch("post_wo_tgt_fit_tgtpj_y", &post_wo_tgt_fit_tgtpj_y, "post_wo_tgt_fit_tgtpj_y/D");
   out_tree->Branch("post_wo_tgt_fit_tgtpj_z", &post_wo_tgt_fit_tgtpj_z, "post_wo_tgt_fit_tgtpj_z/D");
   out_tree->Branch("post_fit_tgtpj_x", &post_fit_tgtpj_x, "post_fit_tgtpj_x/D");
   out_tree->Branch("post_fit_tgtpj_y", &post_fit_tgtpj_y, "post_fit_tgtpj_y/D");
   out_tree->Branch("post_fit_tgtpj_z", &post_fit_tgtpj_z, "post_fit_tgtpj_z/D");
//   out_tree->Branch("lg_t", &lg_t, "lg_t/D");
//   out_tree->Branch("ssd_t", &ssd_t, "ssd_t/D");

   for(int m = 100; m < 110; m++){
		h_fit_profile[m-100] = new TH1D(Form("h_fit_profile_%d", m),Form("h_fit_profile_%d", m ), 200, -50, 50);
		h_y_hit_adc[m-100] = new TH1D(Form("h_y_hit_adc_%d", m),Form("h_y_hit_adc_%d", m ), 500, 0, 2500);
		h_n_cluster_inrange[m-100]      = new TH1D(Form("h_n_cluster_inrange_%d", m),Form("h_n_cluster_inrange_%d", m ), 20, -0.5, 19.5);
		h_n_cluster_inrange_y[m-100]    = new TH1D(Form("h_n_cluster_inrange_y_%d", m),Form("h_n_cluster_inrange_y_%d", m ), 20, -0.5, 19.5);
		h_n_cluster_inrange_wo_Y[m-100] = new TH1D(Form("h_n_cluster_inrange_wo_Y_%d", m),Form("h_n_cluster_inrange_wo_Y%d", m ), 20, -0.5, 19.5);
		h_dum_n_cluster_inrange_wo_Y[m-100] = new TH1D(Form("h_dum_n_cluster_inrange_wo_Y_%d", m),Form("h_dum_n_cluster_inrange_wo_Y%d", m ), 20, -0.5, 19.5);
		h_all_cut_n_cluster_inrange[m-100] = new TH1D(Form("h_all_cut_n_cluster_inrange_%d", m),Form("h_all_cut_n_cluster_inrange_%d", m ), 20, -0.5, 19.5);
		h_timingx_dis[m-100] = new TH1D(Form("h_timingx_dis_x_%d", m),Form("h_htimingx_dis_x_%d", m ), 100, 0, 600);
		h_timingx2_dis[m-100] = new TH1D(Form("h_timingx2_dis_x_%d", m),Form("h_htimingx2_dis_x_%d", m ), 100, 0, 600);
		h_timingy_dis[m-100] = new TH1D(Form("h_timingy_dis_x_%d", m),Form("h_htimingy_dis_x_%d", m ), 100, 0, 600);
		h_timingy2_dis[m-100] = new TH1D(Form("h_timingy2_dis_x_%d", m),Form("h_htimingy2_dis_x_%d", m ), 100, 0, 600);
		h_timing_corr_xy[m-100] = new TH2D(Form("h_timing_corr_xy_%d", m),Form("h_htiming_corr_xy_%d", m ), 50, 0, 600, 50, 0, 600);
		h_timing2_corr_xy[m-100] = new TH2D(Form("h_timing2_corr_xy_%d", m),Form("h_htiming2_corr_xy_%d", m ), 50, 0, 600, 50, 0, 600);
		h_timing_diff[m-100] = new TH1D(Form("h_timing_diff_%d", m),Form("h_htiming_diff_%d", m ), 100, -500, 500);
		h_timing2_diff[m-100] = new TH1D(Form("h_timing2_diff_%d", m),Form("h_htiming2_diff_%d", m ), 100, -500, 500);
    
		h_dum_n_cluster_inrange[m-100] = new TH1D(Form("h_dum_n_cluster_inrange_%d", m),Form("h_dum_n_cluster_inrange_%d", m ), 20, -0.5, 19.5);
		h_dum_n_cluster_inrange_y[m-100] = new TH1D(Form("h_dum_n_cluster_inrange_y_%d", m),Form("h_dum_n_cluster_inrange_y_%d", m ), 20, -0.5, 19.5);
		h_hbd_res_x[m-100] = new TH1D(Form("h_hbd_res_x_%d", m),Form("h_hbd_res_x_%d", m ), 400, -200, 200);
		h_hbd_res_y[m-100] = new TH1D(Form("h_hbd_res_y_%d", m),Form("h_hbd_res_y_%d", m ), 400, -200, 200);
		h_lg_res_x[m-100] = new TH1D(Form("h_lg_res_x_%d", m),Form("h_lg_res_x_%d", m ), 400, -400, 400);
		h_lg_res_y[m-100] = new TH1D(Form("h_lg_res_y_%d", m),Form("h_lg_res_y_%d", m ), 400, -400, 400);
		h_gtr_res_all_x[m-100]            = new TH1D(Form("h_gtr_res_all_x_%d", m),    Form("h_gtr_res_all_x_%d", m ),                  100, -20, 20);
		h_gtr_res_all_x_wo_Y[m-100]       = new TH1D(Form("h_gtr_res_all_x_wo_Y_%d", m),    Form("h_gtr_res_all_x_wo_Y%d", m ),         100, -20, 20);
		h_dum_gtr_res_all_x_wo_Y[m-100]   = new TH1D(Form("h_dum_gtr_res_all_x_wo_Y_%d", m),    Form("h_dum_gtr_res_all_x_wo_Y%d", m ), 100, -20, 20);
		h_gtr_res_min_x[m-100]            = new TH1D(Form("h_gtr_res_min_x_%d", m),    Form("h_gtr_res_min_x_%d", m ),                  100, -20, 20);
		h_gtr_res_min_y[m-100]            = new TH1D(Form("h_gtr_res_min_y_%d", m),    Form("h_gtr_res_min_y_%d", m ),                  100, -20, 20);
		h_dum_gtr_res_min_x[m-100]        = new TH1D(Form("h_dum_gtr_res_min_x_%d", m),    Form("h_dum_gtr_res_min_x_%d", m ),          100, -20, 20);
		h_dum_gtr_res_all_x[m-100]        = new TH1D(Form("h_dum_gtr_res_all_x_%d", m),Form("h_dum_gtr_res_all_x_%d", m ),              100, -20, 20);
		h_gtr_res_all_y[m-100]            = new TH1D(Form("h_gtr_res_all_y_%d", m),    Form("h_gtr_res_all_y_%d", m ),                  100, -20, 20);
		h_dum_gtr_res_all_y[m-100]        = new TH1D(Form("h_dum_gtr_res_all_y_%d", m),Form("h_dum_gtr_res_all_y_%d", m ),              100, -20, 20);
		h_n_lg_hits_inrange[m-100]        = new TH1D(Form("h_n_lg_hits_inrange_%d", m),Form("h_n_lg_hits_inrange__%d", m ), 10, -0.5, 9.5);
		h_n_lg_dum_hits_inrange[m-100] = new TH1D(Form("h_n_lg_dum_hits_inrange_%d", m),Form("h_n_lg_dum_hits_inrange__%d", m ), 10, -0.5, 9.5);
		h_rk_hit_plane[m-100]  = new TH2D(Form("h_rk_hit_plane_%d", m), Form("h_rk_hit_plane_%d", m ), 1500, 100, 300, 800, 100, 300);
//		h_hit_fit[m-100]  = new TH2D(Form("h_hit_fit_%d", m), Form("h_hit_fit_%d", m ), 100, -150, 150, 100, -150, 150);
	h_hit_fit[m-100]  = new TH2D(Form("h_hit_fit_%d", m), Form("h_hit_fit_%d", m ), 100, 0, 400, 100, -150, 150);
   for(int gtrm = 100; gtrm < 110; gtrm++){
		h_mix_true_lg_res_x[gtrm-100][m-100] =     new TH1D(Form("h_mix_true_lg_res_x_gtr%d_%d",gtrm,  m),     Form("h_mix_true_lg_res_x_gtr%d_%d", gtrm, m ), 200, -800, 800);
		h_mix_dum_lg_res_x[gtrm-100][m-100]  =     new TH1D(Form("h_mix_dum_lg_res_x_gtr%d_%d", gtrm,  m),     Form("h_mix_dum_lg_res_x_gtr%d_%d", gtrm, m ),  200, -800, 800);
		h_mix_all_true_lg_res_x[gtrm-100][m-100] = new TH1D(Form("h_mix_all_true_lg_res_x_gtr%d_%d", gtrm,  m),Form("h_mix_all_true_lg_res_x_gtr%d_%d", gtrm, m ), 200, -800, 800);
		h_mix_all_dum_lg_res_x[gtrm-100][m-100]  = new TH1D(Form("h_mix_all_dum_lg_res_x_gtr%d_%d", gtrm, m),  Form("h_mix_all_dum_lg_res_x_gtr%d_%d",gtrm,  m ),  200, -800, 800);
	}

		}
   Init(dynamic_cast<TTree*>(chain));
}
LayerEfficiencyCalculator::LayerEfficiencyCalculator(TTree *tree, E16ANA_MultiTrack *_fitter, int _maxevent)
{
//// if parameter tree is not specified (or zero), connect the file
//// used to generate this class and read the Tree.
//   if (tree == 0) {
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("out.root");
//      if (!f || !f->IsOpen()) {
//         f = new TFile("out.root");
//      }
//      f->GetObject("tree",tree);
//   }
   Init(tree);
}

LayerEfficiencyCalculator::~LayerEfficiencyCalculator()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}
Int_t LayerEfficiencyCalculator::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t LayerEfficiencyCalculator::LoadTree(Long64_t entry)
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

void LayerEfficiencyCalculator::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   track_id = 0;
   chi_square = 0;
   rk_charge = 0;
   is_selected = 0;
   track_mom = 0;
   track_mom_x = 0;
   track_mom_y = 0;
   track_mom_z = 0;
   track_tgt_dist = 0;
   track_lg_pi_eff1 = 0;
   track_lg_pi_eff2 = 0;
   track_angle_lx = 0;
   track_angle_ly = 0;
   track_position_block_lx = 0;
   track_position_block_ly = 0;
   track_ssd_t = 0;
   track_ssd_adc = 0;
   track_gtr100x_t = 0;
   track_gtr100x_adc = 0;
   track_gtr100y_t = 0;
   track_gtr100y_adc = 0;
   track_gtr200x_t = 0;
   track_gtr200x_adc = 0;
   track_gtr200y_t = 0;
   track_gtr200y_adc = 0;
   track_gtr300x_t = 0;
   track_gtr300x_adc = 0;
   track_gtr300y_t = 0;
   track_gtr300y_adc = 0;
   track_hbd_mid = 0;
   track_hbd_lx = 0;
   track_hbd_ly = 0;
   track_hbd_nearx = 0;
   track_hbd_neary = 0;
   track_hbd_multiplicity = 0;
   track_hbd_dum_nearx = 0;
   track_hbd_dum_neary = 0;
   track_hbd_dum_multiplicity = 0;
   track_lg_mid = 0;
   track_lg_lx = 0;
   track_lg_ly = 0;
   track_lg_nearx = 0;
   track_lg_neary = 0;
   track_lg_multiplicity = 0;
   track_lg_dum_nearx = 0;
   track_lg_dum_neary = 0;
   track_lg_dum_multiplicity = 0;
   track_lg_cl_nearx = 0;
   track_lg_cl_neary = 0;
   track_lg_cl_multiplicity = 0;
   track_lg_cl_dum_nearx = 0;
   track_lg_cl_dum_neary = 0;
   track_lg_cl_dum_multiplicity = 0;
   track_hbd_allhit_resx = 0;
   track_hbd_allhit_resy = 0;
   track_hbd_allhit_ftime = 0;
   track_hbd_allhit_adc = 0;
   track_hbd_allhit_size = 0;
   track_hbd_allhit_eprob = 0;
   track_hbd_allhit_cprob = 0;
   track_hbd_allhit_dum_resx = 0;
   track_hbd_allhit_dum_resy = 0;
   track_hbd_allhit_dum_ftime = 0;
   track_hbd_allhit_dum_adc = 0;
   track_hbd_allhit_dum_size = 0;
   track_hbd_allhit_dum_eprob = 0;
   track_hbd_allhit_dum_cprob = 0;
   track_lg_allhit_resx = 0;
   track_lg_allhit_resy = 0;
   track_lg_allhit_ftime = 0;
   track_lg_allhit_adc = 0;
   track_lg_allhit_dum_resx = 0;
   track_lg_allhit_dum_resy = 0;
   track_lg_allhit_dum_ftime = 0;
   track_lg_allhit_dum_adc = 0;
   track_lg_cl_allhit_resx = 0;
   track_lg_cl_allhit_resy = 0;
   track_lg_cl_allhit_ftime = 0;
   track_lg_cl_allhit_adc = 0;
   track_lg_cl_allhit_maxpeak = 0;
   track_lg_cl_allhit_maxcid = 0;
   track_lg_cl_allhit_dum_resx = 0;
   track_lg_cl_allhit_dum_resy = 0;
   track_lg_cl_allhit_dum_ftime = 0;
   track_lg_cl_allhit_dum_adc = 0;
   track_lg_cl_allhit_dum_maxpeak = 0;
   track_lg_cl_allhit_dum_maxcid = 0;
   track_lg_t = 0;

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
   rk_hit_gtr100_gtz = 0;
   rk_hit_gtr100_gtz2 = 0;
   rk_hit_gtr200_gtz = 0;
   rk_hit_gtr200_gtz2 = 0;
   rk_hit_gtr300_gtz = 0;
   rk_hit_gtr300_gtz2 = 0;
   rk_hit_gtr100_gtx = 0;
   rk_hit_gtr100_gty = 0;
   rk_hit_gtr200_gty = 0;
   rk_hit_gtr300_gty = 0;
   rk_hit_gtr100_gtx2 = 0;
   rk_hit_gtr200_gtx = 0;
   rk_hit_gtr200_gtx2 = 0;
   rk_hit_gtr300_gtx = 0;
   rk_hit_gtr300_gtx2 = 0;
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


//   rk_hit_ssd_gx = 0;
//   rk_hit_ssd_gy = 0;
//   rk_hit_ssd_gz = 0;
//   rk_hit_gtr100_gx = 0;
//   rk_hit_gtr100_gy = 0;
//   rk_hit_gtr100_gz = 0;
//   rk_hit_gtr200_gx = 0;
//   rk_hit_gtr200_gy = 0;
//   rk_hit_gtr200_gz = 0;
//   rk_hit_gtr300_gx = 0;
//   rk_hit_gtr300_gy = 0;
//   rk_hit_gtr300_gz = 0;
//   rk_hit_gtr100_gtx = 0;
//   rk_hit_gtr100_gtx2 = 0;
//   rk_hit_gtr200_gtx = 0;
//   rk_hit_gtr200_gtx2 = 0;
//   rk_hit_gtr300_gtx = 0;
//   rk_hit_gtr300_gtx2 = 0;
//   rk_hit_gtr100_gtz = 0;
//   rk_hit_gtr100_gtz2 = 0;
//   rk_hit_gtr200_gtz = 0;
//   rk_hit_gtr200_gtz2 = 0;
//   rk_hit_gtr300_gtz = 0;
//   rk_hit_gtr300_gtz2 = 0;
//
//

   trg_track_lg_id  =0;
   trg_track_lg_mid =0;
   trg_track_lg_cid =0;
   trg_track_lg_x   =0; 
   trg_track_lg_y   =0; 
   trg_track_lg_t   =0; 




//
//

   track_ssd_cluster_id = 0;
   track_ssd_cluster_mid = 0;
   track_gtr100x_cluster_id = 0;
   track_gtr200x_cluster_id = 0;
   track_gtr300x_cluster_id = 0;
   track_gtr100y_cluster_id = 0;
   track_gtr200y_cluster_id = 0;
   track_gtr300y_cluster_id = 0;
   track_gtr100yb_cluster_id = 0;
   track_gtr100_cluster_mid = 0;
   track_gtr200_cluster_mid = 0;
   track_gtr300_cluster_mid = 0;
   rk_res_ssd_x = 0;
   rk_res_gtr100_x = 0;
   rk_res_gtr100_y = 0;
   rk_res_gtr200_x = 0;
   rk_res_gtr200_y = 0;
   rk_res_gtr300_x = 0;
   rk_res_gtr300_y = 0;

   gtr100x_hit_id = 0;   
   gtr100x_hit_mid = 0;   
   gtr100x_hit_cid = 0;   
   gtr100x_hit_x = 0;   
   gtr100x_hit_tx = 0;   
   gtr100x_hit_gx = 0;   
   gtr100x_hit_gz = 0;   
   gtr100x_hit_t   =0;   
   gtr100x_hit_adc=0;   
   gtr200x_hit_id = 0;   
   gtr200x_hit_mid = 0;   
   gtr200x_hit_cid = 0;   
   gtr200x_hit_x   = 0 ;   
   gtr200x_hit_tx =0;   
   gtr200x_hit_gx = 0;   
   gtr200x_hit_gz = 0;   
   gtr200x_hit_t = 0;   
   gtr200x_hit_adc = 0;   
   gtr300x_hit_id = 0;   
   gtr300x_hit_mid = 0;   
   gtr300x_hit_cid=0;   
   gtr300x_hit_x-0;   
   gtr300x_hit_tx=0;   
   gtr300x_hit_gx=0;   
   gtr300x_hit_gz=0;   
   gtr300x_hit_t=0;   
   gtr300x_hit_adc=0;   

   gtr100y_hit_id = 0;   
   gtr100y_hit_mid = 0;   
   gtr100y_hit_cid = 0 ;   
   gtr100y_hit_y = 0;   
   gtr100y_hit_ty = 0;   
   gtr100y_hit_t = 0;   
   gtr100y_hit_adc = 0;   
   gtr100yb_hit_id   = 0;   
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
   gtr300y_hit_cid = 0 ;   
   gtr300y_hit_y = 0;   
   gtr300y_hit_ty = 0;   
   gtr300y_hit_t = 0;   
   gtr300y_hit_adc = 0;   










   
    ssd_cluster_size = 0;
    gtr100x_cluster_size = 0 ;
    gtr200x_cluster_size = 0;
    gtr300x_cluster_size = 0;
    gtr100y_cluster_size = 0;
    gtr100yb_cluster_size = 0;
    gtr200y_cluster_size = 0;
    gtr300y_cluster_size =  0;
     ssd_cluster_id       =0;     
     ssd_cluster_mid      =0;     
     ssd_cluster_x        =0;     
     ssd_cluster_gx       =0;    
     ssd_cluster_gz       =0;      
     ssd_cluster_adc      =0;       
     ssd_cluster_t        =0;    
     gtr100x_cluster_id   =0;              
     gtr100x_cluster_mid  =0;             
     gtr100x_cluster_x    =0;               
     gtr100x_cluster_gx   =0;                
     gtr100x_cluster_gz   =0;                   
     gtr100x_cluster_adc  =0;                     
     gtr100x_cluster_t    =0;                     
     gtr100x_cluster_t2    =0;                     
     gtr200x_cluster_id   =0;                      
     gtr200x_cluster_mid  =0;                           
     gtr200x_cluster_x    =0;                      
     gtr200x_cluster_gx   =0;                         
     gtr200x_cluster_gz   =0;                      
     gtr200x_cluster_adc  =0;                
     gtr200x_cluster_t    =0;         
     gtr200x_cluster_t2    =0;         
     gtr300x_cluster_id   =0;        
     gtr300x_cluster_mid  =0;         
     gtr300x_cluster_x    =0;           
     gtr300x_cluster_gx   =0;            
     gtr300x_cluster_gz   =0;           
     gtr300x_cluster_adc  =0;               
     gtr300x_cluster_t    =0;           
     gtr300x_cluster_t2    =0;           
     gtr100y_cluster_id   =0;           
     gtr100y_cluster_mid  =0;          
     gtr100y_cluster_y    =0;          
     gtr100y_cluster_adc  =0;         
     gtr100y_cluster_t    =0;          
     gtr100y_cluster_t2    =0;          
     gtr100yb_cluster_id  =0;         
     gtr100yb_cluster_mid =0;           
     gtr100yb_cluster_y   =0;        
     gtr100yb_cluster_adc =0;          
     gtr100yb_cluster_t   =0;            
     gtr100yb_cluster_t2   =0;            
     gtr200y_cluster_id   = 0 ;
     gtr200y_cluster_mid  =0;          
     gtr200y_cluster_y    =0;        
     gtr200y_cluster_adc  =0;         
     gtr200y_cluster_t    =0;         
     gtr200y_cluster_t2    =0;         
     gtr300y_cluster_id   =0;          
     gtr300y_cluster_mid  =0;          
     gtr300y_cluster_y    =0;       
     gtr300y_cluster_adc  =0;         
     gtr300y_cluster_t    =0;        
     gtr300y_cluster_t2    =0;        
  rk_fit_gtr100_gx = 0;   //!
  rk_fit_gtr100_gy = 0;   //!
  rk_fit_gtr100_gz = 0;   //!
  rk_fit_gtr200_gx = 0;   //!
  rk_fit_gtr200_gy = 0;   //!
  rk_fit_gtr200_gz = 0;   //!
  rk_fit_gtr300_gx = 0;   //!
  rk_fit_gtr300_gy = 0;   //!
  rk_fit_gtr300_gz = 0;   //!
 

  rk_fit_ssd_mid    = 0;
  rk_fit_gtr100_mid  = 0;
  rk_fit_gtr200_mid  = 0;
  rk_fit_gtr300_mid  = 0;
  
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
   lg_hit_cid = 0;
   lg_hit_x = 0;
   lg_hit_y = 0;
   lg_hit_gx = 0;
   lg_hit_gy = 0;
   lg_hit_gz = 0;
   lg_hit_adc = 0;
   lg_hit_t = 0;
   lg_hit_npeaks = 0;
   lg_hit_fflag = 0;


   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run_id", &run_id, &b_run_id);
   fChain->SetBranchAddress("event_id", &event_id, &b_event_id);
   fChain->SetBranchAddress("n_cands", &n_cands, &b_n_cands);
   fChain->SetBranchAddress("spill_id", &spill_id, &b_spill_id);
//   fChain->SetBranchAddress("n_tracks", &n_tracks, &b_n_tracks);
   fChain->SetBranchAddress("track_id", &track_id, &b_track_id);
   fChain->SetBranchAddress("chi_square", &chi_square, &b_chi_square);
   fChain->SetBranchAddress("rk_charge", &rk_charge, &b_rk_charge);
   fChain->SetBranchAddress("is_selected", &is_selected, &b_is_selected);
   fChain->SetBranchAddress("track_mom", &track_mom, &b_track_mom);
   fChain->SetBranchAddress("track_mom_x", &track_mom_x, &b_track_mom_x);
   fChain->SetBranchAddress("track_mom_y", &track_mom_y, &b_track_mom_y);
   fChain->SetBranchAddress("track_mom_z", &track_mom_z, &b_track_mom_z);
   fChain->SetBranchAddress("track_tgt_dist", &track_tgt_dist, &b_track_tgt_dist);
   fChain->SetBranchAddress("track_lg_pi_eff1", &track_lg_pi_eff1, &b_track_lg_pi_eff1);
   fChain->SetBranchAddress("track_lg_pi_eff2", &track_lg_pi_eff2, &b_track_lg_pi_eff2);
   fChain->SetBranchAddress("track_angle_lx", &track_angle_lx, &b_track_angle_lx);
   fChain->SetBranchAddress("track_angle_ly", &track_angle_ly, &b_track_angle_ly);
   fChain->SetBranchAddress("track_position_block_lx", &track_position_block_lx, &b_track_position_block_lx);
   fChain->SetBranchAddress("track_position_block_ly", &track_position_block_ly, &b_track_position_block_ly);
   fChain->SetBranchAddress("track_ssd_t", &track_ssd_t, &b_track_ssd_t);
   fChain->SetBranchAddress("track_ssd_adc", &track_ssd_adc, &b_track_ssd_adc);
   fChain->SetBranchAddress("track_gtr100x_t", &track_gtr100x_t, &b_track_gtr100x_t);
   fChain->SetBranchAddress("track_gtr100x_adc", &track_gtr100x_adc, &b_track_gtr100x_adc);
   fChain->SetBranchAddress("track_gtr100y_t", &track_gtr100y_t, &b_track_gtr100y_t);
   fChain->SetBranchAddress("track_gtr100y_adc", &track_gtr100y_adc, &b_track_gtr100y_adc);
   fChain->SetBranchAddress("track_gtr200x_t", &track_gtr200x_t, &b_track_gtr200x_t);
   fChain->SetBranchAddress("track_gtr200x_adc", &track_gtr200x_adc, &b_track_gtr200x_adc);
   fChain->SetBranchAddress("track_gtr200y_t", &track_gtr200y_t, &b_track_gtr200y_t);
   fChain->SetBranchAddress("track_gtr200y_adc", &track_gtr200y_adc, &b_track_gtr200y_adc);
   fChain->SetBranchAddress("track_gtr300x_t", &track_gtr300x_t, &b_track_gtr300x_t);
   fChain->SetBranchAddress("track_gtr300x_adc", &track_gtr300x_adc, &b_track_gtr300x_adc);
   fChain->SetBranchAddress("track_gtr300y_t", &track_gtr300y_t, &b_track_gtr300y_t);
   fChain->SetBranchAddress("track_gtr300y_adc", &track_gtr300y_adc, &b_track_gtr300y_adc);
   fChain->SetBranchAddress("track_hbd_mid", &track_hbd_mid, &b_track_hbd_mid);
   fChain->SetBranchAddress("track_hbd_lx", &track_hbd_lx, &b_track_hbd_lx);
   fChain->SetBranchAddress("track_hbd_ly", &track_hbd_ly, &b_track_hbd_ly);
   fChain->SetBranchAddress("track_hbd_nearx", &track_hbd_nearx, &b_track_hbd_nearx);
   fChain->SetBranchAddress("track_hbd_neary", &track_hbd_neary, &b_track_hbd_neary);
   fChain->SetBranchAddress("track_hbd_multiplicity", &track_hbd_multiplicity, &b_track_hbd_multiplicity);
   fChain->SetBranchAddress("track_hbd_dum_nearx", &track_hbd_dum_nearx, &b_track_hbd_dum_nearx);
   fChain->SetBranchAddress("track_hbd_dum_neary", &track_hbd_dum_neary, &b_track_hbd_dum_neary);
   fChain->SetBranchAddress("track_hbd_dum_multiplicity", &track_hbd_dum_multiplicity, &b_track_hbd_dum_multiplicity);
   fChain->SetBranchAddress("track_lg_mid", &track_lg_mid, &b_track_lg_mid);
   fChain->SetBranchAddress("track_lg_t", &track_lg_t, &b_track_lg_t);
   fChain->SetBranchAddress("track_lg_lx", &track_lg_lx, &b_track_lg_lx);
   fChain->SetBranchAddress("track_lg_ly", &track_lg_ly, &b_track_lg_ly);
   fChain->SetBranchAddress("track_lg_nearx", &track_lg_nearx, &b_track_lg_nearx);
   fChain->SetBranchAddress("track_lg_neary", &track_lg_neary, &b_track_lg_neary);
   fChain->SetBranchAddress("track_lg_multiplicity", &track_lg_multiplicity, &b_track_lg_multiplicity);
   fChain->SetBranchAddress("track_lg_dum_nearx", &track_lg_dum_nearx, &b_track_lg_dum_nearx);
   fChain->SetBranchAddress("track_lg_dum_neary", &track_lg_dum_neary, &b_track_lg_dum_neary);
   fChain->SetBranchAddress("track_lg_dum_multiplicity", &track_lg_dum_multiplicity, &b_track_lg_dum_multiplicity);
   fChain->SetBranchAddress("track_lg_cl_nearx", &track_lg_cl_nearx, &b_track_lg_cl_nearx);
   fChain->SetBranchAddress("track_lg_cl_neary", &track_lg_cl_neary, &b_track_lg_cl_neary);
   fChain->SetBranchAddress("track_lg_cl_multiplicity", &track_lg_cl_multiplicity, &b_track_lg_cl_multiplicity);
   fChain->SetBranchAddress("track_lg_cl_dum_nearx", &track_lg_cl_dum_nearx, &b_track_lg_cl_dum_nearx);
   fChain->SetBranchAddress("track_lg_cl_dum_neary", &track_lg_cl_dum_neary, &b_track_lg_cl_dum_neary);
   fChain->SetBranchAddress("track_lg_cl_dum_multiplicity", &track_lg_cl_dum_multiplicity, &b_track_lg_cl_dum_multiplicity);
   fChain->SetBranchAddress("track_hbd_allhit_resx", &track_hbd_allhit_resx, &b_track_hbd_allhit_resx);
   fChain->SetBranchAddress("track_hbd_allhit_resy", &track_hbd_allhit_resy, &b_track_hbd_allhit_resy);
   fChain->SetBranchAddress("track_hbd_allhit_ftime", &track_hbd_allhit_ftime, &b_track_hbd_allhit_ftime);
   fChain->SetBranchAddress("track_hbd_allhit_adc", &track_hbd_allhit_adc, &b_track_hbd_allhit_adc);
   fChain->SetBranchAddress("track_hbd_allhit_size", &track_hbd_allhit_size, &b_track_hbd_allhit_size);
   fChain->SetBranchAddress("track_hbd_allhit_eprob", &track_hbd_allhit_eprob, &b_track_hbd_allhit_eprob);
   fChain->SetBranchAddress("track_hbd_allhit_cprob", &track_hbd_allhit_cprob, &b_track_hbd_allhit_cprob);
   fChain->SetBranchAddress("track_hbd_allhit_dum_resx", &track_hbd_allhit_dum_resx, &b_track_hbd_allhit_dum_resx);
   fChain->SetBranchAddress("track_hbd_allhit_dum_resy", &track_hbd_allhit_dum_resy, &b_track_hbd_allhit_dum_resy);
   fChain->SetBranchAddress("track_hbd_allhit_dum_ftime", &track_hbd_allhit_dum_ftime, &b_track_hbd_allhit_dum_ftime);
   fChain->SetBranchAddress("track_hbd_allhit_dum_adc", &track_hbd_allhit_dum_adc, &b_track_hbd_allhit_dum_adc);
   fChain->SetBranchAddress("track_hbd_allhit_dum_size", &track_hbd_allhit_dum_size, &b_track_hbd_allhit_dum_size);
   fChain->SetBranchAddress("track_hbd_allhit_dum_eprob", &track_hbd_allhit_dum_eprob, &b_track_hbd_allhit_dum_eprob);
   fChain->SetBranchAddress("track_hbd_allhit_dum_cprob", &track_hbd_allhit_dum_cprob, &b_track_hbd_allhit_dum_cprob);
   fChain->SetBranchAddress("track_lg_allhit_resx", &track_lg_allhit_resx, &b_track_lg_allhit_resx);
   fChain->SetBranchAddress("track_lg_allhit_resy", &track_lg_allhit_resy, &b_track_lg_allhit_resy);
   fChain->SetBranchAddress("track_lg_allhit_ftime", &track_lg_allhit_ftime, &b_track_lg_allhit_ftime);
   fChain->SetBranchAddress("track_lg_allhit_adc", &track_lg_allhit_adc, &b_track_lg_allhit_adc);
   fChain->SetBranchAddress("track_lg_allhit_dum_resx", &track_lg_allhit_dum_resx, &b_track_lg_allhit_dum_resx);
   fChain->SetBranchAddress("track_lg_allhit_dum_resy", &track_lg_allhit_dum_resy, &b_track_lg_allhit_dum_resy);
   fChain->SetBranchAddress("track_lg_allhit_dum_ftime", &track_lg_allhit_dum_ftime, &b_track_lg_allhit_dum_ftime);
   fChain->SetBranchAddress("track_lg_allhit_dum_adc", &track_lg_allhit_dum_adc, &b_track_lg_allhit_dum_adc);
   fChain->SetBranchAddress("track_lg_cl_allhit_resx", &track_lg_cl_allhit_resx, &b_track_lg_cl_allhit_resx);
   fChain->SetBranchAddress("track_lg_cl_allhit_resy", &track_lg_cl_allhit_resy, &b_track_lg_cl_allhit_resy);
   fChain->SetBranchAddress("track_lg_cl_allhit_ftime", &track_lg_cl_allhit_ftime, &b_track_lg_cl_allhit_ftime);
   fChain->SetBranchAddress("track_lg_cl_allhit_adc", &track_lg_cl_allhit_adc, &b_track_lg_cl_allhit_adc);
   fChain->SetBranchAddress("track_lg_cl_allhit_maxpeak", &track_lg_cl_allhit_maxpeak, &b_track_lg_cl_allhit_maxpeak);
   fChain->SetBranchAddress("track_lg_cl_allhit_maxcid", &track_lg_cl_allhit_maxcid, &b_track_lg_cl_allhit_maxcid);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_resx", &track_lg_cl_allhit_dum_resx, &b_track_lg_cl_allhit_dum_resx);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_resy", &track_lg_cl_allhit_dum_resy, &b_track_lg_cl_allhit_dum_resy);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_ftime", &track_lg_cl_allhit_dum_ftime, &b_track_lg_cl_allhit_dum_ftime);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_adc", &track_lg_cl_allhit_dum_adc, &b_track_lg_cl_allhit_dum_adc);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_maxpeak", &track_lg_cl_allhit_dum_maxpeak, &b_track_lg_cl_allhit_dum_maxpeak);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_maxcid", &track_lg_cl_allhit_dum_maxcid, &b_track_lg_cl_allhit_dum_maxcid);
   fChain->SetBranchAddress("trg_track_lg_id",  &trg_track_lg_id , &b_trg_track_lg_id ) ;
   fChain->SetBranchAddress("trg_track_lg_mid", &trg_track_lg_mid, &b_trg_track_lg_mid) ;
   fChain->SetBranchAddress("trg_track_lg_cid", &trg_track_lg_cid, &b_trg_track_lg_cid) ;
   fChain->SetBranchAddress("trg_track_lg_x",   &trg_track_lg_x  , &b_trg_track_lg_x  ) ; 
   fChain->SetBranchAddress("trg_track_lg_y",   &trg_track_lg_y  , &b_trg_track_lg_y  ) ; 
   fChain->SetBranchAddress("trg_track_lg_t",   &trg_track_lg_t  , &b_trg_track_lg_t  ) ; 






//   fChain->SetBranchAddress("rk_hit_ssd_gx", &rk_hit_ssd_gx, &b_rk_hit_ssd_gx);
//   fChain->SetBranchAddress("rk_hit_ssd_gy", &rk_hit_ssd_gy, &b_rk_hit_ssd_gy);
//   fChain->SetBranchAddress("rk_hit_ssd_gz", &rk_hit_ssd_gz, &b_rk_hit_ssd_gz);
//   fChain->SetBranchAddress("rk_hit_gtr100_gx", &rk_hit_gtr100_gx, &b_rk_hit_gtr100_gx);
//   fChain->SetBranchAddress("rk_hit_gtr100_gy", &rk_hit_gtr100_gy, &b_rk_hit_gtr100_gy);
//   fChain->SetBranchAddress("rk_hit_gtr100_gz", &rk_hit_gtr100_gz, &b_rk_hit_gtr100_gz);
//   fChain->SetBranchAddress("rk_hit_gtr200_gx", &rk_hit_gtr200_gx, &b_rk_hit_gtr200_gx);
//   fChain->SetBranchAddress("rk_hit_gtr200_gy", &rk_hit_gtr200_gy, &b_rk_hit_gtr200_gy);
//   fChain->SetBranchAddress("rk_hit_gtr200_gz", &rk_hit_gtr200_gz, &b_rk_hit_gtr200_gz);
//   fChain->SetBranchAddress("rk_hit_gtr300_gx", &rk_hit_gtr300_gx, &b_rk_hit_gtr300_gx);
//   fChain->SetBranchAddress("rk_hit_gtr300_gy", &rk_hit_gtr300_gy, &b_rk_hit_gtr300_gy);
//   fChain->SetBranchAddress("rk_hit_gtr300_gz", &rk_hit_gtr300_gz, &b_rk_hit_gtr300_gz);
//   fChain->SetBranchAddress("rk_hit_gtr100_gtx", &rk_hit_gtr100_gtx, &b_rk_hit_gtr100_gtx);
//   fChain->SetBranchAddress("rk_hit_gtr100_gty", &rk_hit_gtr100_gty, &b_rk_hit_gtr100_gty);
//   fChain->SetBranchAddress("rk_hit_gtr200_gty", &rk_hit_gtr200_gty, &b_rk_hit_gtr200_gty);
//   fChain->SetBranchAddress("rk_hit_gtr300_gty", &rk_hit_gtr300_gty, &b_rk_hit_gtr300_gty);
//   fChain->SetBranchAddress("rk_hit_gtr100_gtx2", &rk_hit_gtr100_gtx2, &b_rk_hit_gtr100_gtx2);
//   fChain->SetBranchAddress("rk_hit_gtr100_gtz2", &rk_hit_gtr100_gtz2, &b_rk_hit_gtr100_gtz2);
//   fChain->SetBranchAddress("rk_hit_gtr200_gtz2", &rk_hit_gtr200_gtz2, &b_rk_hit_gtr200_gtz2);
//   fChain->SetBranchAddress("rk_hit_gtr300_gtz2", &rk_hit_gtr300_gtz2, &b_rk_hit_gtr300_gtz2);
//   fChain->SetBranchAddress("rk_hit_gtr200_gtx", &rk_hit_gtr200_gtx, &b_rk_hit_gtr200_gtx);
//   fChain->SetBranchAddress("rk_hit_gtr200_gtx2", &rk_hit_gtr200_gtx2, &b_rk_hit_gtr200_gtx2);
//   fChain->SetBranchAddress("rk_hit_gtr300_gtx", &rk_hit_gtr300_gtx, &b_rk_hit_gtr300_gtx);
//   fChain->SetBranchAddress("rk_hit_gtr300_gtx2", &rk_hit_gtr300_gtx2, &b_rk_hit_gtr300_gtx2);
//
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
   fChain->SetBranchAddress("rk_hit_gtr100_gtz", &rk_hit_gtr100_gtz, &b_rk_hit_gtr100_gtz);
   fChain->SetBranchAddress("rk_hit_gtr100_gtz2", &rk_hit_gtr100_gtz2, &b_rk_hit_gtr100_gtz2);
   fChain->SetBranchAddress("rk_hit_gtr200_gtz", &rk_hit_gtr200_gtz, &b_rk_hit_gtr200_gtz);
   fChain->SetBranchAddress("rk_hit_gtr200_gtz2", &rk_hit_gtr200_gtz2, &b_rk_hit_gtr200_gtz2);
   fChain->SetBranchAddress("rk_hit_gtr300_gtz", &rk_hit_gtr300_gtz, &b_rk_hit_gtr300_gtz);
   fChain->SetBranchAddress("rk_hit_gtr300_gtz2", &rk_hit_gtr300_gtz2, &b_rk_hit_gtr300_gtz2);
   fChain->SetBranchAddress("rk_hit_gtr100_gtx", &rk_hit_gtr100_gtx, &b_rk_hit_gtr100_gtx);
   fChain->SetBranchAddress("rk_hit_gtr100_gty", &rk_hit_gtr100_gty, &b_rk_hit_gtr100_gty);
   fChain->SetBranchAddress("rk_hit_gtr200_gty", &rk_hit_gtr200_gty, &b_rk_hit_gtr200_gty);
   fChain->SetBranchAddress("rk_hit_gtr300_gty", &rk_hit_gtr300_gty, &b_rk_hit_gtr300_gty);
   fChain->SetBranchAddress("rk_hit_gtr100_gtx2", &rk_hit_gtr100_gtx2, &b_rk_hit_gtr100_gtx2);
   fChain->SetBranchAddress("rk_hit_gtr200_gtx", &rk_hit_gtr200_gtx, &b_rk_hit_gtr200_gtx);
   fChain->SetBranchAddress("rk_hit_gtr200_gtx2", &rk_hit_gtr200_gtx2, &b_rk_hit_gtr200_gtx2);
   fChain->SetBranchAddress("rk_hit_gtr300_gtx", &rk_hit_gtr300_gtx, &b_rk_hit_gtr300_gtx);
   fChain->SetBranchAddress("rk_hit_gtr300_gtx2", &rk_hit_gtr300_gtx2, &b_rk_hit_gtr300_gtx2);
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
 

   fChain->SetBranchAddress("rk_res_ssd_x", &rk_res_ssd_x, &b_rk_res_ssd_x);
   fChain->SetBranchAddress("rk_res_gtr100_x", &rk_res_gtr100_x, &b_rk_res_gtr100_x);
   fChain->SetBranchAddress("rk_res_gtr200_x", &rk_res_gtr200_x, &b_rk_res_gtr200_x);
   fChain->SetBranchAddress("rk_res_gtr300_x", &rk_res_gtr300_x, &b_rk_res_gtr300_x);
   fChain->SetBranchAddress("rk_res_gtr100_y", &rk_res_gtr100_y, &b_rk_res_gtr100_y);
   fChain->SetBranchAddress("rk_res_gtr200_y", &rk_res_gtr200_y, &b_rk_res_gtr200_y);
   fChain->SetBranchAddress("rk_res_gtr300_y", &rk_res_gtr300_y, &b_rk_res_gtr300_y);
   fChain->SetBranchAddress("track_ssd_cluster_id", &track_ssd_cluster_id, &b_track_ssd_cluster_id);
   fChain->SetBranchAddress("track_ssd_cluster_mid", &track_ssd_cluster_mid, &b_track_ssd_cluster_mid);
   fChain->SetBranchAddress("track_gtr100x_cluster_id", &track_gtr100x_cluster_id, &b_track_gtr100x_cluster_id);
   fChain->SetBranchAddress("track_gtr200x_cluster_id", &track_gtr200x_cluster_id, &b_track_gtr200x_cluster_id);
   fChain->SetBranchAddress("track_gtr300x_cluster_id", &track_gtr300x_cluster_id, &b_track_gtr300x_cluster_id);
   fChain->SetBranchAddress("track_gtr100y_cluster_id", &track_gtr100y_cluster_id, &b_track_gtr100y_cluster_id);
   fChain->SetBranchAddress("track_gtr200y_cluster_id", &track_gtr200y_cluster_id, &b_track_gtr200y_cluster_id);
   fChain->SetBranchAddress("track_gtr300y_cluster_id", &track_gtr300y_cluster_id, &b_track_gtr300y_cluster_id);
   fChain->SetBranchAddress("track_gtr100yb_cluster_id", &track_gtr100yb_cluster_id, &b_track_gtr100yb_cluster_id);
   fChain->SetBranchAddress("track_gtr100_cluster_mid", &track_gtr100_cluster_mid, &b_track_gtr100_cluster_mid);
   fChain->SetBranchAddress("track_gtr200_cluster_mid", &track_gtr200_cluster_mid, &b_track_gtr200_cluster_mid);
   fChain->SetBranchAddress("track_gtr300_cluster_mid", &track_gtr300_cluster_mid, &b_track_gtr300_cluster_mid);

   fChain->SetBranchAddress("ssd_cluster_size"     , &ssd_cluster_size    , &b_ssd_cluster_size    ) ;
   fChain->SetBranchAddress("gtr100x_cluster_size" , &gtr100x_cluster_size , &b_gtr100x_cluster_size) ;
   fChain->SetBranchAddress("gtr200x_cluster_size" , &gtr200x_cluster_size , &b_gtr200x_cluster_size);
   fChain->SetBranchAddress("gtr300x_cluster_size" , &gtr300x_cluster_size , &b_gtr300x_cluster_size);
   fChain->SetBranchAddress("gtr100y_cluster_size" , &gtr100y_cluster_size , &b_gtr100y_cluster_size);
   fChain->SetBranchAddress("gtr100yb_cluster_size", &gtr100yb_cluster_size , &b_gtr100yb_cluster_size);
   fChain->SetBranchAddress("gtr200y_cluster_size" , &gtr200y_cluster_size , &b_gtr200y_cluster_size);
   fChain->SetBranchAddress("gtr300y_cluster_size" , &gtr300y_cluster_size , &b_gtr300y_cluster_size);


 
   fChain->SetBranchAddress("n_gtr100x_hits", &n_gtr100x_hits  , &b_n_gtr100x_hits);
   fChain->SetBranchAddress("n_gtr200x_hits", &n_gtr200x_hits  , &b_n_gtr200x_hits);
   fChain->SetBranchAddress("n_gtr300x_hits", &n_gtr300x_hits  , &b_n_gtr300x_hits);
   fChain->SetBranchAddress("n_gtr100y_hits", &n_gtr100y_hits  , &b_n_gtr100y_hits);
   fChain->SetBranchAddress("n_gtr100yb_hits", &n_gtr100yb_hits,   &b_n_gtr100yb_hits);
   fChain->SetBranchAddress("n_gtr200y_hits", &n_gtr200y_hits  , &b_n_gtr200y_hits);
   fChain->SetBranchAddress("n_gtr300y_hits", &n_gtr300y_hits  , &b_n_gtr300y_hits);

   fChain->SetBranchAddress("gtr100x_hit_id",   &gtr100x_hit_id ,   &b_gtr100x_hit_id); 
   fChain->SetBranchAddress("gtr100x_hit_mid",  &gtr100x_hit_mid,   &b_gtr100x_hit_mid); 
   fChain->SetBranchAddress("gtr100x_hit_cid",  &gtr100x_hit_cid,   &b_gtr100x_hit_cid); 
   fChain->SetBranchAddress("gtr100x_hit_x",    &gtr100x_hit_x,     &b_gtr100x_hit_x);   
   fChain->SetBranchAddress("gtr100x_hit_tx",   &gtr100x_hit_tx,    &b_gtr100x_hit_tx);   
   fChain->SetBranchAddress("gtr100x_hit_gx",   &gtr100x_hit_gx,    &b_gtr100x_hit_gx);   
   fChain->SetBranchAddress("gtr100x_hit_gz",   &gtr100x_hit_gz,    &b_gtr100x_hit_gz);   
   fChain->SetBranchAddress("gtr100x_hit_t",    &gtr100x_hit_t,    &b_gtr100x_hit_t);   
   fChain->SetBranchAddress("gtr100x_hit_adc" ,   &gtr100x_hit_adc,    &b_gtr100x_hit_adc);   

   fChain->SetBranchAddress("gtr200x_hit_id",   &gtr200x_hit_id ,   &b_gtr200x_hit_id); 
   fChain->SetBranchAddress("gtr200x_hit_mid",  &gtr200x_hit_mid,   &b_gtr200x_hit_mid); 
   fChain->SetBranchAddress("gtr200x_hit_cid",  &gtr200x_hit_cid,   &b_gtr200x_hit_cid); 
   fChain->SetBranchAddress("gtr200x_hit_x",    &gtr200x_hit_x,     &b_gtr200x_hit_x);   
   fChain->SetBranchAddress("gtr200x_hit_tx",   &gtr200x_hit_tx,    &b_gtr200x_hit_tx);   
   fChain->SetBranchAddress("gtr200x_hit_gx",   &gtr200x_hit_gx,    &b_gtr200x_hit_gx);   
   fChain->SetBranchAddress("gtr200x_hit_gz",   &gtr200x_hit_gz,    &b_gtr200x_hit_gz);   
   fChain->SetBranchAddress("gtr200x_hit_t",    &gtr200x_hit_t,     &b_gtr200x_hit_t);   
   fChain->SetBranchAddress("gtr200x_hit_adc",  &gtr200x_hit_adc,   &b_gtr200x_hit_adc);   

   fChain->SetBranchAddress("gtr300x_hit_id",   &gtr300x_hit_id ,   &b_gtr300x_hit_id); 
   fChain->SetBranchAddress("gtr300x_hit_mid",  &gtr300x_hit_mid,   &b_gtr300x_hit_mid); 
   fChain->SetBranchAddress("gtr300x_hit_cid",  &gtr300x_hit_cid,   &b_gtr300x_hit_cid); 
   fChain->SetBranchAddress("gtr300x_hit_x",    &gtr300x_hit_x,     &b_gtr300x_hit_x);   
   fChain->SetBranchAddress("gtr300x_hit_tx",   &gtr300x_hit_tx,    &b_gtr300x_hit_tx);   
   fChain->SetBranchAddress("gtr300x_hit_gx",   &gtr300x_hit_gx,    &b_gtr300x_hit_gx);   
   fChain->SetBranchAddress("gtr300x_hit_gz",   &gtr300x_hit_gz,    &b_gtr300x_hit_gz);   
   fChain->SetBranchAddress("gtr300x_hit_t",    &gtr300x_hit_t,     &b_gtr300x_hit_t);   
   fChain->SetBranchAddress("gtr300x_hit_adc"  , &gtr300x_hit_adc,   &b_gtr300x_hit_adc);   


   fChain->SetBranchAddress("gtr100y_hit_id",   &gtr100y_hit_id ,   &b_gtr100y_hit_id); 
   fChain->SetBranchAddress("gtr100y_hit_mid",  &gtr100y_hit_mid,   &b_gtr100y_hit_mid); 
   fChain->SetBranchAddress("gtr100y_hit_cid",  &gtr100y_hit_cid,   &b_gtr100y_hit_cid); 
   fChain->SetBranchAddress("gtr100y_hit_y",    &gtr100y_hit_y,     &b_gtr100y_hit_y);   
   fChain->SetBranchAddress("gtr100y_hit_ty",   &gtr100y_hit_ty,    &b_gtr100y_hit_ty);   
   fChain->SetBranchAddress("gtr100y_hit_t",    &gtr100y_hit_t,     &b_gtr100y_hit_t);   
   fChain->SetBranchAddress("gtr100y_hit_adc",  &gtr100y_hit_adc,   &b_gtr100y_hit_adc);   

   fChain->SetBranchAddress("gtr100yb_hit_id",   &gtr100yb_hit_id ,   &b_gtr100yb_hit_id); 
   fChain->SetBranchAddress("gtr100yb_hit_mid",  &gtr100yb_hit_mid,   &b_gtr100yb_hit_mid); 
   fChain->SetBranchAddress("gtr100yb_hit_cid",  &gtr100yb_hit_cid,   &b_gtr100yb_hit_cid); 
   fChain->SetBranchAddress("gtr100yb_hit_y",    &gtr100yb_hit_y,     &b_gtr100yb_hit_y);   
   fChain->SetBranchAddress("gtr100yb_hit_ty",   &gtr100yb_hit_ty,    &b_gtr100yb_hit_ty);   
   fChain->SetBranchAddress("gtr100yb_hit_t",    &gtr100yb_hit_t,     &b_gtr100yb_hit_t);   
   fChain->SetBranchAddress("gtr100yb_hit_adc" ,  &gtr100yb_hit_adc,   &b_gtr100yb_hit_adc);   


   fChain->SetBranchAddress("gtr200y_hit_id",   &gtr200y_hit_id ,   &b_gtr200y_hit_id); 
   fChain->SetBranchAddress("gtr200y_hit_mid",  &gtr200y_hit_mid,   &b_gtr200y_hit_mid); 
   fChain->SetBranchAddress("gtr200y_hit_cid",  &gtr200y_hit_cid,   &b_gtr200y_hit_cid); 
   fChain->SetBranchAddress("gtr200y_hit_y",    &gtr200y_hit_y,     &b_gtr200y_hit_y);   
   fChain->SetBranchAddress("gtr200y_hit_ty",   &gtr200y_hit_ty,    &b_gtr200y_hit_ty);   
   fChain->SetBranchAddress("gtr200y_hit_t",    &gtr200y_hit_t,     &b_gtr200y_hit_t);   
   fChain->SetBranchAddress("gtr200y_hit_adc",    &gtr200y_hit_adc,   &b_gtr200y_hit_adc);   

   fChain->SetBranchAddress("gtr300y_hit_id",   &gtr300y_hit_id ,   &b_gtr300y_hit_id); 
   fChain->SetBranchAddress("gtr300y_hit_mid",  &gtr300y_hit_mid,   &b_gtr300y_hit_mid); 
   fChain->SetBranchAddress("gtr300y_hit_cid",  &gtr300y_hit_cid,   &b_gtr300y_hit_cid); 
   fChain->SetBranchAddress("gtr300y_hit_y",    &gtr300y_hit_y,     &b_gtr300y_hit_y);   
   fChain->SetBranchAddress("gtr300y_hit_ty",   &gtr300y_hit_ty,    &b_gtr300y_hit_ty);   
   fChain->SetBranchAddress("gtr300y_hit_t",    &gtr300y_hit_t,     &b_gtr300y_hit_t);   
   fChain->SetBranchAddress("gtr300y_hit_adc",  &gtr300y_hit_adc,   &b_gtr300y_hit_adc);   






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
   fChain->SetBranchAddress("gtr100x_cluster_t2", &gtr100x_cluster_t2, &b_gtr100x_cluster_t2);
   fChain->SetBranchAddress("n_gtr200x_clusters", &n_gtr200x_clusters, &b_n_gtr200x_clusters);
   fChain->SetBranchAddress("gtr200x_cluster_id", &gtr200x_cluster_id, &b_gtr200x_cluster_id);
   fChain->SetBranchAddress("gtr200x_cluster_mid", &gtr200x_cluster_mid, &b_gtr200x_cluster_mid);
   fChain->SetBranchAddress("gtr200x_cluster_x", &gtr200x_cluster_x, &b_gtr200x_cluster_x);
   fChain->SetBranchAddress("gtr200x_cluster_gx", &gtr200x_cluster_gx, &b_gtr200x_cluster_gx);
   fChain->SetBranchAddress("gtr200x_cluster_gz", &gtr200x_cluster_gz, &b_gtr200x_cluster_gz);
   fChain->SetBranchAddress("gtr200x_cluster_adc", &gtr200x_cluster_adc, &b_gtr200x_cluster_adc);
   fChain->SetBranchAddress("gtr200x_cluster_t", &gtr200x_cluster_t, &b_gtr200x_cluster_t);
   fChain->SetBranchAddress("gtr200x_cluster_t2", &gtr200x_cluster_t2, &b_gtr200x_cluster_t2);
   fChain->SetBranchAddress("n_gtr300x_clusters", &n_gtr300x_clusters, &b_n_gtr300x_clusters);
   fChain->SetBranchAddress("gtr300x_cluster_id", &gtr300x_cluster_id, &b_gtr300x_cluster_id);
   fChain->SetBranchAddress("gtr300x_cluster_mid", &gtr300x_cluster_mid, &b_gtr300x_cluster_mid);
   fChain->SetBranchAddress("gtr300x_cluster_x", &gtr300x_cluster_x, &b_gtr300x_cluster_x);
   fChain->SetBranchAddress("gtr300x_cluster_gx", &gtr300x_cluster_gx, &b_gtr300x_cluster_gx);
   fChain->SetBranchAddress("gtr300x_cluster_gz", &gtr300x_cluster_gz, &b_gtr300x_cluster_gz);
   fChain->SetBranchAddress("gtr300x_cluster_adc", &gtr300x_cluster_adc, &b_gtr300x_cluster_adc);
   fChain->SetBranchAddress("gtr300x_cluster_t", &gtr300x_cluster_t, &b_gtr300x_cluster_t);
   fChain->SetBranchAddress("gtr300x_cluster_t2", &gtr300x_cluster_t2, &b_gtr300x_cluster_t2);
   fChain->SetBranchAddress("n_gtr100y_clusters", &n_gtr100y_clusters, &b_n_gtr100y_clusters);
   fChain->SetBranchAddress("gtr100y_cluster_id", &gtr100y_cluster_id, &b_gtr100y_cluster_id);
   fChain->SetBranchAddress("gtr100y_cluster_mid", &gtr100y_cluster_mid, &b_gtr100y_cluster_mid);
   fChain->SetBranchAddress("gtr100y_cluster_y", &gtr100y_cluster_y, &b_gtr100y_cluster_y);
   fChain->SetBranchAddress("gtr100y_cluster_adc", &gtr100y_cluster_adc, &b_gtr100y_cluster_adc);
   fChain->SetBranchAddress("gtr100y_cluster_t", &gtr100y_cluster_t, &b_gtr100y_cluster_t);
   fChain->SetBranchAddress("gtr100y_cluster_t2", &gtr100y_cluster_t2, &b_gtr100y_cluster_t2);
   fChain->SetBranchAddress("n_gtr100yb_clusters", &n_gtr100yb_clusters, &b_n_gtr100yb_clusters);
   fChain->SetBranchAddress("gtr100yb_cluster_id", &gtr100yb_cluster_id, &b_gtr100yb_cluster_id);
   fChain->SetBranchAddress("gtr100yb_cluster_mid", &gtr100yb_cluster_mid, &b_gtr100yb_cluster_mid);
   fChain->SetBranchAddress("gtr100yb_cluster_y", &gtr100yb_cluster_y, &b_gtr100yb_cluster_y);
   fChain->SetBranchAddress("gtr100yb_cluster_adc", &gtr100yb_cluster_adc, &b_gtr100yb_cluster_adc);
   fChain->SetBranchAddress("gtr100yb_cluster_t", &gtr100yb_cluster_t, &b_gtr100yb_cluster_t);
   fChain->SetBranchAddress("gtr100yb_cluster_t2", &gtr100yb_cluster_t2, &b_gtr100yb_cluster_t2);
   fChain->SetBranchAddress("n_gtr200y_clusters", &n_gtr200y_clusters, &b_n_gtr200y_clusters);
   fChain->SetBranchAddress("gtr200y_cluster_id", &gtr200y_cluster_id, &b_gtr200y_cluster_id);
   fChain->SetBranchAddress("gtr200y_cluster_mid", &gtr200y_cluster_mid, &b_gtr200y_cluster_mid);
   fChain->SetBranchAddress("gtr200y_cluster_y", &gtr200y_cluster_y, &b_gtr200y_cluster_y);
   fChain->SetBranchAddress("gtr200y_cluster_adc", &gtr200y_cluster_adc, &b_gtr200y_cluster_adc);
   fChain->SetBranchAddress("gtr200y_cluster_t", &gtr200y_cluster_t, &b_gtr200y_cluster_t);
   fChain->SetBranchAddress("gtr200y_cluster_t2", &gtr200y_cluster_t2, &b_gtr200y_cluster_t2);
   fChain->SetBranchAddress("n_gtr300y_clusters", &n_gtr300y_clusters, &b_n_gtr300y_clusters);
   fChain->SetBranchAddress("gtr300y_cluster_id", &gtr300y_cluster_id, &b_gtr300y_cluster_id);
   fChain->SetBranchAddress("gtr300y_cluster_mid", &gtr300y_cluster_mid, &b_gtr300y_cluster_mid);
   fChain->SetBranchAddress("gtr300y_cluster_y", &gtr300y_cluster_y, &b_gtr300y_cluster_y);
   fChain->SetBranchAddress("gtr300y_cluster_adc", &gtr300y_cluster_adc, &b_gtr300y_cluster_adc);
   fChain->SetBranchAddress("gtr300y_cluster_t", &gtr300y_cluster_t, &b_gtr300y_cluster_t);
   fChain->SetBranchAddress("gtr300y_cluster_t2", &gtr300y_cluster_t2, &b_gtr300y_cluster_t2);

   fChain->SetBranchAddress("rk_fit_gtr100_gx", &rk_fit_gtr100_gx , &b_rk_fit_gtr100_gx );
   fChain->SetBranchAddress("rk_fit_gtr100_gy", &rk_fit_gtr100_gy , &b_rk_fit_gtr100_gy );
   fChain->SetBranchAddress("rk_fit_gtr100_gz", &rk_fit_gtr100_gz , &b_rk_fit_gtr100_gz );
   fChain->SetBranchAddress("rk_fit_gtr200_gx", &rk_fit_gtr200_gx , &b_rk_fit_gtr200_gx );
   fChain->SetBranchAddress("rk_fit_gtr200_gy", &rk_fit_gtr200_gy , &b_rk_fit_gtr200_gy );
   fChain->SetBranchAddress("rk_fit_gtr200_gz", &rk_fit_gtr200_gz , &b_rk_fit_gtr200_gz );
   fChain->SetBranchAddress("rk_fit_gtr300_gx", &rk_fit_gtr300_gx , &b_rk_fit_gtr300_gx );
   fChain->SetBranchAddress("rk_fit_gtr300_gy", &rk_fit_gtr300_gy , &b_rk_fit_gtr300_gy );
   fChain->SetBranchAddress("rk_fit_gtr300_gz", &rk_fit_gtr300_gz , &b_rk_fit_gtr300_gz );

   fChain->SetBranchAddress("rk_fit_ssd_mid",    &rk_fit_ssd_mid   , &b_rk_fit_ssd_mid   );   
   fChain->SetBranchAddress("rk_fit_gtr100_mid", &rk_fit_gtr100_mid, &b_rk_fit_gtr100_mid);
   fChain->SetBranchAddress("rk_fit_gtr200_mid", &rk_fit_gtr200_mid, &b_rk_fit_gtr200_mid);
   fChain->SetBranchAddress("rk_fit_gtr300_mid", &rk_fit_gtr300_mid, &b_rk_fit_gtr300_mid);

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
   fChain->SetBranchAddress("lg_hit_cid", &lg_hit_cid, &b_lg_hit_cid);
   fChain->SetBranchAddress("lg_hit_x", &lg_hit_x, &b_lg_hit_x);
   fChain->SetBranchAddress("lg_hit_y", &lg_hit_y, &b_lg_hit_y);
   fChain->SetBranchAddress("lg_hit_gx", &lg_hit_gx, &b_lg_hit_gx);
   fChain->SetBranchAddress("lg_hit_gy", &lg_hit_gy, &b_lg_hit_gy);
   fChain->SetBranchAddress("lg_hit_gz", &lg_hit_gz, &b_lg_hit_gz);
   fChain->SetBranchAddress("lg_hit_adc", &lg_hit_adc, &b_lg_hit_adc);
   fChain->SetBranchAddress("lg_hit_t", &lg_hit_t, &b_lg_hit_t);
   fChain->SetBranchAddress("lg_hit_npeaks", &lg_hit_npeaks, &b_lg_hit_npeaks);
   fChain->SetBranchAddress("lg_hit_fflag", &lg_hit_fflag, &b_lg_hit_fflag);


   Notify();
}

Bool_t LayerEfficiencyCalculator::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void LayerEfficiencyCalculator::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t LayerEfficiencyCalculator::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}



//#include "LayerEfficiencyCalculator.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


bool LayerEfficiencyCalculator::CheckUsedClusters(int track_index, 
	std::array<std::vector<int>, 6> * used_cluster_ids){
	int ids[8] = {rk_hit_ssd_id->at(track_index), 
				  rk_hit_gtr100_xid->at(track_index), rk_hit_gtr100_yid->at(track_index),
				  rk_hit_gtr200_xid->at(track_index), rk_hit_gtr200_yid->at(track_index),
				  rk_hit_gtr300_xid->at(track_index), rk_hit_gtr300_yid->at(track_index),
				  ass_hbd_cluster_id.at(track_index)};
	if(ids[7] < 0) {
//		std::cout << " HBD is not associated " << std::endl;
		return false;
		}
	for (const auto &id : used_cluster_ids->at(0)){
		if(id == ids[0]){
			return false;
		}
	}
    if(rm_size != 0){
	for (const auto &id : used_cluster_ids->at(1)){
		if(id == ids[1] || id == ids[2]){
			return false;
		}
	}
    }
    if(rm_size != 1){
	for (const auto &id : used_cluster_ids->at(2)){
		if(id == ids[3] || id == ids[4]){
			return false;
		}
	}
    }
    if(rm_size != 2){
	for (const auto &id : used_cluster_ids->at(3)){
		if(id == ids[5] || id == ids[6]){
			return false;
		}
	}
    }
	for (const auto &id : used_cluster_ids->at(4)){
		if(id == ids[7] ){
//		    std::cout << " HBD is duplicated! " << std::endl;
			return false ;
		}
	}
	used_cluster_ids->at(0).emplace_back(ids[0]);
	used_cluster_ids->at(1).emplace_back(ids[1]);
	used_cluster_ids->at(1).emplace_back(ids[2]);
	used_cluster_ids->at(2).emplace_back(ids[3]);
	used_cluster_ids->at(2).emplace_back(ids[4]);
	used_cluster_ids->at(3).emplace_back(ids[5]);
	used_cluster_ids->at(3).emplace_back(ids[6]);
	used_cluster_ids->at(4).emplace_back(ids[7]);
	//selected_track_indexes.emplace_back(track_index);
    h_hbd_res_x[rk_fit_hbd_mid->at(track_index) -100]->Fill(ass_hbd_resx.at(track_index));
    h_hbd_res_y[rk_fit_hbd_mid->at(track_index) -100]->Fill(ass_hbd_resy.at(track_index));
    h_lg_res_x[rk_fit_hbd_mid->at(track_index) -100]->Fill(ass_lg_resx.at(track_index));
    h_lg_res_y[rk_fit_hbd_mid->at(track_index) -100]->Fill(ass_lg_resy.at(track_index));
	return true;
}

bool LayerEfficiencyCalculator::CheckUsedClustersForMix(int track_index, 
	std::array<std::vector<int>, 6> * used_cluster_ids){
	int ids[8] = {rk_hit_ssd_id->at(track_index), 
				  rk_hit_gtr100_xid->at(track_index), rk_hit_gtr100_yid->at(track_index),
				  rk_hit_gtr200_xid->at(track_index), rk_hit_gtr200_yid->at(track_index),
				  rk_hit_gtr300_xid->at(track_index), rk_hit_gtr300_yid->at(track_index),
				  mix_ass_hbd_cluster_id.at(track_index)};
	if(ids[7] < 0) {
//		std::cout << " HBD is not associated " << std::endl;
		return false;
		}
	for (const auto &id : used_cluster_ids->at(0)){
		if(id == ids[0]){
			return false;
		}
	}
    if(rm_size != 0){
	for (const auto &id : used_cluster_ids->at(1)){
		if(id == ids[1] || id == ids[2]){
			return false;
		}
	}
    }
    if(rm_size != 1){
	for (const auto &id : used_cluster_ids->at(2)){
		if(id == ids[3] || id == ids[4]){
			return false;
		}
	}
    }
    if(rm_size != 2){
	for (const auto &id : used_cluster_ids->at(3)){
		if(id == ids[5] || id == ids[6]){
			return false;
		}
	}
    }
	for (const auto &id : used_cluster_ids->at(4)){
		if(id == ids[7] ){
//		    std::cout << " HBD is duplicated! " << std::endl;
			return false ;
		}
    }
	used_cluster_ids->at(0).emplace_back(ids[0]);
	used_cluster_ids->at(1).emplace_back(ids[1]);
	used_cluster_ids->at(1).emplace_back(ids[2]);
	used_cluster_ids->at(2).emplace_back(ids[3]);
	used_cluster_ids->at(2).emplace_back(ids[4]);
	used_cluster_ids->at(3).emplace_back(ids[5]);
	used_cluster_ids->at(3).emplace_back(ids[6]);
	used_cluster_ids->at(4).emplace_back(ids[7]);
	//selected_track_indexes.emplace_back(track_index);
   return true;
}
void LayerEfficiencyCalculator::SelectTrack(E16ANA_GTRStatus *gtr_status, E16ANA_GTRAnalyzerMaker *gtr_analyzers,  int track_index, std::array<std::vector<int>, 6> *used_cluster_ids, int &cnt){
	if(CheckUsedClusters(track_index, used_cluster_ids)){
		if(IsGoodHBDAssociation(track_index, ass_hbd_resx, ass_hbd_resy)){
			if(IsHittedOnSurvivalArea(gtr_status, gtr_analyzers, track_index)){
//				if(IsTriggerdTrack(track_index)){
					if(IsGoodLGAssociation(track_index)){//this cut shouuld be the last 
			    		cnt++;
						//std::cout << "selected tid  = " << track_index << std::endl;
						selected_track_indexes.emplace_back(track_index);
//					}
				}
			}
		}
	}
}




bool LayerEfficiencyCalculator::IsGoodLGAssociation(int track_index){
	double resx = ass_lg_resx.at(track_index);
	double resy = ass_lg_resy.at(track_index);
	//std::cout << "lg residual = " << resx << std::endl;
	bool flag = false;
	if(fabs(resx) < 100 && fabs(resy) < 100) {
//		std::cout << "resx      = " << resx << ", " << resy<< std::endl;	    
		flag = true;
	}
	return flag;
}


bool LayerEfficiencyCalculator::IsGoodHBDAssociation(int track_index, std::vector<double> &v_ass_hbd_resx, std::vector<double> &v_ass_hbd_resy){
	double resx = v_ass_hbd_resx.at(track_index);
	double resy = v_ass_hbd_resy.at(track_index);
	//std::cout << "hbd residual = " << resx << std::endl;
	bool flag = false;
	if(-20 < resx && resx < 0 && fabs(resy) < 15) {
		flag = true;
	}
	return flag;
}

double LayerEfficiencyCalculator::SelectTracks(E16ANA_GTRStatus *gtr_status, E16ANA_GTRAnalyzerMaker *gtr_analyzers){
	std::array<std::vector<int> , 6> used_cluster_ids;
    for(int l = 0; l < 6; l++){
		used_cluster_ids.at(l).clear();	
	}
    int cnt;
//	matched_lghit_ids.resize(n_tracks);
//1	matched_lghit_ids.clear();
//	std::array<std::vector<int> , 10> used_hbd_cluster_mid_and_ids> ;
//    used_hbd_cluster_mid_ids.clear();
	for(int tid = 0; tid < track_id->size(); tid++){	

		h_fit_profile[rk_fit_gtr100_mid->at(tid) - 100] ->Fill(rk_fit_gtr100_gy->at(tid));
		AssociateHBDCluster(tid, ass_hbd_resx, ass_hbd_resy, ass_hbd_cluster_id );	
		AssociateLGHit(tid);
    	SelectTrack(gtr_status, gtr_analyzers, tid,  &used_cluster_ids, cnt);	
	}
 //   if(cnt != 0 )  std::cout << "cnt1 =  " << cnt << std::endl;
    return cnt;
}

bool LayerEfficiencyCalculator::IsHittedOnSurvivalArea(E16ANA_GTRStatus *gtr_status, E16ANA_GTRAnalyzerMaker *gtr_analyzers, int track_id){
    bool flag = true;
    int mid[3] = { rk_fit_gtr100_mid->at(track_id), 
     rk_fit_gtr200_mid->at(track_id), 
     rk_fit_gtr300_mid->at(track_id)};
    
    TVector3 gpos[3] = {TVector3(rk_fit_gtr100_gx->at(track_id), rk_fit_gtr100_gy->at(track_id), rk_fit_gtr100_gz->at(track_id)), 
                        TVector3(rk_fit_gtr200_gx->at(track_id), rk_fit_gtr200_gy->at(track_id), rk_fit_gtr200_gz->at(track_id)), 
                        TVector3(rk_fit_gtr300_gx->at(track_id), rk_fit_gtr300_gy->at(track_id), rk_fit_gtr300_gz->at(track_id))}; 
    E16ANA_GeometryV2 *geom = E16ANA_GeometryV2::GlobalPointer();
    TVector3 lpos = geom->GTR(track_const::ModuleID2020To2013(mid[rm_size]), rm_size)->GetLPos(gpos[rm_size]);
	int apv_ch_x = E16ANA_GTRChannelManager::ConvLocalXToAPVch( rm_size,lpos.X());
	int apv_ch_y = E16ANA_GTRChannelManager::ConvLocalYToAPVch( rm_size, lpos.X(), lpos.Y());
	if(gtr_analyzers->Chamber(mid[rm_size], rm_size)->GetStripX()->IsBadStrip(apv_ch_x)){
		flag = false;
	}
	if(gtr_analyzers->Chamber(mid[rm_size], rm_size)->GetStripY()->IsBadStrip(apv_ch_y)){
		flag = false;
	}
  	else if(rm_size == 0 &&  lpos.X()  < 0){
		 if(static_cast<E16ANA_GTR100Analyzer *> (gtr_analyzers->Chamber(mid[rm_size], rm_size))->GetStripYb()->IsBadStrip(apv_ch_y)){
			flag = false;	
		}
	}
    if(rm_size == 0 && gtr_status->GEMDeadArea100()->IsXOK(mid[rm_size], lpos.X()) == true){
	}
    else if(rm_size == 1 && gtr_status->GEMDeadArea200()->IsXOK(mid[rm_size], lpos.X()) == true 
			&& gtr_status->GEMDeadArea200()->IsYOK(mid[rm_size], lpos.Y()) == true){
	}
    else if(rm_size == 2 && gtr_status->GEMDeadArea300()->IsXOK(mid[rm_size], lpos.X()) == true
		&& gtr_status->GEMDeadArea300()->IsYOK(mid[rm_size], lpos.Y()) == true
		){
	}

	else {
	flag = false;}

	if(rk_fit_gtr100_gy->at(track_id) < 20 && 10  < rk_fit_gtr100_gy->at(track_id))
	std::cout << "flag " << flag << std::endl;
    return flag;
	
}

	




void LayerEfficiencyCalculator::AssociateLGHit(int track_id){	
	double resx = 10000;
    double resy = 10000;
	double resx2 = 10000;
    double resy2 = 10000;
    int    min_cluster_id = -1;
	double min_resx = 10000;
	double min_resx2 = 10000;
	double min_resy2 = 10000;
	double min_resy = 10000;
	double ssdt = rk_hit_ssd_t->at(track_id);
	int n_lg_hits_inrange[10] = {0,0,0,0,0,0,0,0,0,0};
	for(int i = 0; i < n_lg_hits; i++){
    int mid = 0;
		bool flag = false;
		if(lg_hit_mid->at(i) == rk_fit_lg_c_mid->at(track_id)){
			flag = true;
			mid  = lg_hit_mid->at(i);
		}
		else if(lg_hit_mid->at(i) == rk_fit_lg_b_mid->at(track_id)){
			flag = true;
			mid  = lg_hit_mid->at(i);
		}
		else if(lg_hit_mid->at(i) == rk_fit_lg_a_mid->at(track_id)){
			flag = true;
			mid  = lg_hit_mid->at(i);
		}
		if(flag){
		if( fabs(lg_hit_t->at(i) - ssdt - 51) < 11 ){// ssd & lg timing match
			int ch = lg_hit_cid->at(i);
			if( ch < 10 || 49 < ch ){
				resx = lg_hit_x->at(i) - rk_fit_lg_c_x->at(track_id);
				resy = lg_hit_y->at(i) - rk_fit_lg_c_y->at(track_id);
			}
			else if( ch/10 ==  1 ||  ch/10 == 4 ){
				resx = lg_hit_x->at(i) - rk_fit_lg_b_x->at(track_id);
				resy = lg_hit_y->at(i) - rk_fit_lg_b_y->at(track_id);
			}
			else if( ch/10 == 2 || ch/10 == 3 ){
				resx = lg_hit_x->at(i) - rk_fit_lg_a_x->at(track_id);
				resy = lg_hit_y->at(i) - rk_fit_lg_a_y->at(track_id);
			}
			if( resx * resx + resy * resy < min_resx*min_resx + min_resy * min_resy){
				min_resx = resx;
				min_resy = resy;
				min_cluster_id = lg_hit_id->at(i);
			}
			}
		}
	}
	ass_lg_resx.push_back(min_resx);
	ass_lg_resy.push_back(min_resy);
	ass_lg_hit_id.push_back(min_cluster_id);
}


void LayerEfficiencyCalculator::AssociateHBDCluster(int track_id, std::vector<double> &v_ass_hbd_resx, std::vector<double> &v_ass_hbd_resy, std::vector<int> &v_ass_hbd_cluster_id){
	double resx = 10000;
    double resy = 10000;
    int    min_cluster_id = -1;
	double min_resx = 10000;
	double min_resy = 10000;
	for(int ihbd = 0; ihbd < n_hbd_clusters; ihbd++){
		if(hbd_cluster_mid->at(ihbd) == rk_fit_hbd_mid->at(track_id)){
			resx = hbd_cluster_x->at(ihbd) - rk_fit_hbd_x->at(track_id);
			resy = hbd_cluster_y->at(ihbd) - rk_fit_hbd_y->at(track_id);
			if( resx * resx + resy * resy < min_resx*min_resy + min_resy * min_resy){
				min_resx = resx;
				min_resy = resy;
				min_cluster_id = hbd_cluster_id->at(ihbd);
			}
		}
	}
	v_ass_hbd_resx.push_back(min_resx);
	v_ass_hbd_resy.push_back(min_resy);
	v_ass_hbd_cluster_id.push_back(min_cluster_id);
}


int LayerEfficiencyCalculator::LGLocalToCh(double lx, double ly){
	int y_ch = (ly + 400)/130;
	int x_ch = (lx + 500)/120-1;
	return y_ch * 10 + x_ch;
}

bool LayerEfficiencyCalculator::IsTriggerdTrack(int tid){//
    int rk_fit_lg_mid[3] = {rk_fit_lg_c_mid->at(tid), rk_fit_lg_b_mid->at(tid), rk_fit_lg_a_mid->at(tid)};
    int rk_fit_lg_x[3] = {rk_fit_lg_c_x->at(tid), rk_fit_lg_b_x->at(tid), rk_fit_lg_a_x->at(tid)};
    int rk_fit_lg_y[3] = {rk_fit_lg_c_y->at(tid), rk_fit_lg_b_y->at(tid), rk_fit_lg_a_y->at(tid)};
    bool isFound = false;
//	std::cout << "trg trl lg mid size = " << trg_track_lg_mid->size() << std::endl;
	for(int p = 0; p < 3; p++){//plane a, b, or c 
		for(int i=0; i < trg_track_lg_mid->size(); i++){
//			std::cout << "trg trl lg cid size = " << trg_track_lg_cid->size() << std::endl;
//			std::cout << "trg trl lg cid size = " << trg_track_lg_x->size() << std::endl;
			int tt_lg_mid = trg_track_lg_mid->at(i);//triggerd track
			int tt_lg_cid = trg_track_lg_cid->at(i);//triggerd track
//			double tt_lg_t = trg_track_lg_t->at(i);
			int rk_lg_ch = LGLocalToCh(rk_fit_lg_x[p], rk_fit_lg_y[p]);
	
			if(rk_fit_lg_mid[p] == tt_lg_mid && rk_lg_ch == tt_lg_cid){
				isFound = true;
				std::cout <<  "found " << std::endl;
//				std::cout << "rk_fit_lg_t  = " << lg_t->at(tid) << std::endl;
//				std::cout << "trg trklg t  = " << trg_track_lg_t->at(i) << std::endl;
			}
		}
	}
	return isFound;
}


bool LayerEfficiencyCalculator::AssociationGTRYUsingHit(int tid, int &tn_hits_inrange, int &dum_tn_hits_inrange){
	int rk_fit_gtr_mid[3] = {rk_fit_gtr100_mid->at(tid), rk_fit_gtr200_mid->at(tid), rk_fit_gtr300_mid->at(tid)};
    int n_gtr_hits[3] = {n_gtr100y_hits, n_gtr200y_hits, n_gtr300y_hits};
    std::vector<int>    *gtry_hit_mid[3]  =  {gtr100y_hit_mid,  gtr200y_hit_mid,  gtr300y_hit_mid};
    std::vector<float> *gtry_hit_adc[3]  =  {gtr100y_hit_adc,  gtr200y_hit_adc,  gtr300y_hit_adc};
//    std::vector<int>    *gtry_hit_size[3] =  {gtr100y_hit_size, gtr200y_hit_size, gtr300y_hit_size};
    std::vector<double> *rk_fit_gtr_gx[3] =  {rk_fit_gtr100_gx,   rk_fit_gtr200_gx,   rk_fit_gtr300_gx};
    std::vector<double> *rk_fit_gtr_gy[3] =  {rk_fit_gtr100_gy,   rk_fit_gtr200_gy,   rk_fit_gtr300_gy};
    std::vector<double> *rk_fit_gtr_gz[3] =  {rk_fit_gtr100_gz,   rk_fit_gtr200_gz,   rk_fit_gtr300_gz};
    std::vector<double> *gtry_hit_y[3]    =  {gtr100y_hit_y, gtr200y_hit_y, gtr300y_hit_y};
    std::vector<double> *gtry_hit_t[3]    =  {gtr100y_hit_t, gtr200y_hit_t, gtr300y_hit_t};
 //   std::vector<double> *gtry_hit_t2[3]   =  {gtr100y_hit_t2, gtr200y_hit_t2, gtr300y_hit_t2};
    int mid = rk_fit_gtr_mid[rm_size] - 100;
	int c = rk_charge->at(tid);
	if(c == -1) c = 0; //charge minus
    double min_resy = 10000;
	for(int k = 0; k < n_gtr_hits[rm_size]; k++){
//		std::cout << " k / nhits = " << k << " /  " << n_gtr_hits[rm_size]  << std::endl;
//		std::cout << "mid = " << gtry_hit_mid[rm_size]->at(k) << std::endl;
//		std::cout << gtry_hit_adc[rm_size]->size() << std::endl;
//		std::cout <<" adc     = " <<  gtry_hit_adc[rm_size]->at(k) << std::endl;
//		std::cout <<" y       = " <<  gtry_hit_y[rm_size]->at(k) << std::endl;
//		std::cout <<" t       = " <<  gtry_hit_t[rm_size]->at(k) << std::endl;
		if(rk_fit_gtr_mid[rm_size] != gtry_hit_mid[rm_size]->at(k) ) continue; //module match
		if(gtry_hit_adc[rm_size]->at(k)>50e3) continue;//remove fake hit (maybe no meaning here)
//5		std::cout << "gtry hit adc = " << gtry_hit_adc[rm_size]->at(k) << std::endl;
		h_y_hit_adc[mid]->Fill(gtry_hit_adc[rm_size]->at(k));
//		if(gtry_hit_adc[rm_size]->at(k)<50) continue;
		double resy, dum_resy;
		if(rm_size == 0 ){//gtr 100
       	     resy     = gtry_hit_y[rm_size]->at(k) + rk_fit_gtr_gy[rm_size]->at(tid);
             dum_resy = gtry_hit_y[rm_size]->at(k) + dum_rk_fit_gtr_y[mid][c];
		}
		else {//gtr200, 300
    	     resy     = gtry_hit_y[rm_size]->at(k) - rk_fit_gtr_gy[rm_size]->at(tid);
             dum_resy = gtry_hit_y[rm_size]->at(k) - dum_rk_fit_gtr_y[mid][c];
		}
		if(ym_hitrange[rm_size] < resy  && resy < yp_hitrange[rm_size]) tn_hits_inrange++;
		if(ym_hitrange[rm_size] <  dum_resy &&  dum_resy < yp_hitrange[rm_size]) dum_tn_hits_inrange++;
		h_gtr_res_all_y[mid] ->Fill(resy);
        h_dum_gtr_res_all_y[mid ]->Fill(dum_resy);
	    if(min_resy > resy) {
			min_resy = resy;
			memoryk = k ;
		}
        h_hit_fit[mid]->Fill(gtry_hit_y[rm_size]->at(k), rk_fit_gtr_gy[rm_size]->at(tid));
//	h_fit_profile[mid]->Fill(rk_fit_gtr_gy[rm_size]->at(tid));
  	}
// -- yb 
  if(rm_size == 0){
   	for(int k = 0; k < n_gtr100yb_hits; k++){
		if(rk_fit_gtr100_mid->at(tid) != gtr100yb_hit_mid->at(k) ) continue; //module match
		if(gtr100yb_hit_adc->at(k)>50e3) continue;//remove fake hit
    	double resy =     gtr100yb_hit_y->at(k) + rk_fit_gtr100_gy->at(tid);
        double dum_resy = gtr100yb_hit_y->at(k) + dum_rk_fit_gtr_y[mid][c];
		if(ym_hitrange[rm_size] < resy  && resy < yp_hitrange[rm_size]) tn_hits_inrange++;
		if(ym_hitrange[rm_size] <  dum_resy &&  dum_resy < yp_hitrange[rm_size]) dum_tn_hits_inrange++;
		//if(fabs(resy) < y_hitrange[rm_size]) tn_hits_inrange++;
		//if(fabs(dum_resy) < y_hitrange[rm_size]) dum_tn_hits_inrange++;
		h_gtr_res_all_y[mid] ->Fill(resy);
        h_dum_gtr_res_all_y[mid]->Fill(dum_resy);
	    if(min_resy > resy) min_resy = resy;
	}
	}
	dum_rk_fit_gtr_y[mid][c] = rk_fit_gtr_gy[rm_size]->at(tid);
    h_gtr_res_min_y[mid]->Fill(min_resy);
	if(tn_hits_inrange > 0){
		
		return true;
	}
	else { return false;}
}




bool LayerEfficiencyCalculator::AssociationGTRY(int tid, int &tn_cluster_inrange, int &dum_tn_cluster_inrange){
	int rk_fit_gtr_mid[3] = {rk_fit_gtr100_mid->at(tid), rk_fit_gtr200_mid->at(tid), rk_fit_gtr300_mid->at(tid)};
    int n_gtr_clusters[3] = {n_gtr100y_clusters, n_gtr200y_clusters, n_gtr300y_clusters};
    std::vector<int> *gtry_cluster_mid[3]    =  {gtr100y_cluster_mid, gtr200y_cluster_mid, gtr300y_cluster_mid};
    std::vector<float> *gtry_cluster_adc[3] =  {gtr100y_cluster_adc, gtr200y_cluster_adc, gtr300y_cluster_adc};
    std::vector<int> *gtry_cluster_size[3] =  {gtr100y_cluster_size, gtr200y_cluster_size, gtr300y_cluster_size};
    std::vector<double> *rk_fit_gtr_gx[3] =    {rk_fit_gtr100_gx,   rk_fit_gtr200_gx,   rk_fit_gtr300_gx};
    std::vector<double> *rk_fit_gtr_gy[3] =    {rk_fit_gtr100_gy,   rk_fit_gtr200_gy,   rk_fit_gtr300_gy};
    std::vector<double> *rk_fit_gtr_gz[3] =    {rk_fit_gtr100_gz,   rk_fit_gtr200_gz,   rk_fit_gtr300_gz};
    std::vector<double> *gtry_cluster_y[3] =  {gtr100y_cluster_y, gtr200y_cluster_y, gtr300y_cluster_y};
    std::vector<double> *gtry_cluster_t[3] =   {gtr100y_cluster_t, gtr200y_cluster_t, gtr300y_cluster_t};
    std::vector<double> *gtry_cluster_t2[3] =  {gtr100y_cluster_t2, gtr200y_cluster_t2, gtr300y_cluster_t2};
    int mid = rk_fit_gtr_mid[rm_size] - 100;
	int c = rk_charge->at(tid);
	if(c == -1) c = 0; //charge minus
    double min_resy = 10000;
	std::cout << "tid " << tid << std::endl;
	for(int k = 0; k < n_gtr_clusters[rm_size]; k++){
		if(rk_fit_gtr_mid[rm_size] != gtry_cluster_mid[rm_size]->at(k) ) continue; //module match
		if(gtry_cluster_adc[rm_size]->at(k)>50e3) continue;//remove fake hit
		double resy, dum_resy;
		if(rm_size == 0 ){//gtr 100
       	     resy     = gtry_cluster_y[rm_size]->at(k) + rk_fit_gtr_gy[rm_size]->at(tid);
             dum_resy = gtry_cluster_y[rm_size]->at(k) + dum_rk_fit_gtr_y[mid][c];
		}
		else {//gtr200, 300
    	     resy     = gtry_cluster_y[rm_size]->at(k) - rk_fit_gtr_gy[rm_size]->at(tid);
             dum_resy = gtry_cluster_y[rm_size]->at(k) - dum_rk_fit_gtr_y[mid][c];
		}
		if(fabs(resy) < y_clusterrange[rm_size]) tn_cluster_inrange++;
//		std::cout << "residual y = " << resy << std::endl;  
		if(fabs(dum_resy) < y_clusterrange[rm_size]) dum_tn_cluster_inrange++;
		h_gtr_res_all_y[mid] ->Fill(resy);
        h_dum_gtr_res_all_y[mid ]->Fill(dum_resy);
	    if(min_resy > resy) {
			min_resy = resy;
			memoryk = k ;
		}
//        h_hit_fit[mid]->Fill(gtry_cluster_y[rm_size]->at(k), rk_fit_gtr_gy[rm_size]->at(tid));
//	h_fit_profile[mid]->Fill(rk_fit_gtr_gy[rm_size]->at(tid));
		}
// -- yb 
	if(rm_size == 0){
   	for(int k = 0; k < n_gtr100yb_clusters; k++){
		if(rk_fit_gtr100_mid->at(tid) != gtr100yb_cluster_mid->at(k) ) continue; //module match
		if(gtr100yb_cluster_adc->at(k)>50e3) continue;//remove fake hit
    	double resy =     gtr100yb_cluster_y->at(k) + rk_fit_gtr100_gy->at(tid);
        double dum_resy = gtr100yb_cluster_y->at(k) + dum_rk_fit_gtr_y[mid][c];
//		std::cout << "residual yb = " << resy << std::endl;  
		if(fabs(resy) < y_clusterrange[rm_size]) tn_cluster_inrange++;
		if(fabs(dum_resy) < y_clusterrange[rm_size]) dum_tn_cluster_inrange++;
		h_gtr_res_all_y[mid] ->Fill(resy);
        h_dum_gtr_res_all_y[mid]->Fill(dum_resy);
	    if(min_resy > resy) min_resy = resy;
		if(fabs(resy) < y_clusterrange[rm_size]){ 
//			h_timingy_dis[mid]->Fill(gtr100yb_cluster_t->at(k));
//			h_timingy2_dis[mid]->Fill(gtr100yb_cluster_t2->at(k));
		}
 //       h_hit_fit[mid]->Fill(gtr100yb_cluster_y->at(k), rk_fit_gtr_gy[rm_size]->at(tid));
	}
	}
	dum_rk_fit_gtr_y[mid][c] = rk_fit_gtr_gy[rm_size]->at(tid);
    h_gtr_res_min_y[mid]->Fill(min_resy);
	if(tn_cluster_inrange > 0){
   //     h_hit_fit[mid]->Fill(rk_fit_gtr_gx[rm_size]->at(tid), rk_fit_gtr_gy[rm_size]->at(tid));
		return true;
	}
	else { return false;}

//	for(int k = 0; k < n_gtr_clusters[rm_size]; k++){
//		if(rk_fit_gtr_mid[rm_size] != gtry_cluster_mid[rm_size]->at(k) ) continue; //module match
//		if(gtry_cluster_adc[rm_size]->at(k)>50e3) continue;//remove fake hit
//    	double resy     = gtry_cluster_y[rm_size]->at(k) + rk_fit_gtr_gy[rm_size]->at(tid);
//        double dum_resy = gtry_cluster_y[rm_size]->at(k) + dum_rk_fit_gtr_y[mid][c];
//		if(fabs(resy) < y_clusterrange[rm_size]) tn_cluster_inrange++;
//		if(fabs(dum_resy) < y_clusterrange[rm_size]) dum_tn_cluster_inrange++;
//		h_gtr_res_all_y[mid] ->Fill(resy);
//        h_dum_gtr_res_all_y[mid ]->Fill(dum_resy);
//	    if(min_resy > resy) min_resy = resy;
//        h_hit_fit[mid]->Fill(gtry_cluster_y[rm_size]->at(k), rk_fit_gtr_gy[rm_size]->at(tid));
////	h_fit_profile[mid]->Fill(rk_fit_gtr_gy[rm_size]->at(tid));
//		}
//
//// -- yb 
//   	for(int k = 0; k < n_gtr100yb_clusters; k++){
//		if(rk_fit_gtr100_mid->at(tid) != gtr100yb_cluster_mid->at(k) ) continue; //module match
//		if(gtr100yb_cluster_adc->at(k)>50e3) continue;//remove fake hit
//    	double resy =     gtr100yb_cluster_y->at(k) - rk_fit_gtr100_gy->at(tid);
//        double dum_resy = gtr100yb_cluster_y->at(k) - dum_rk_fit_gtr_y[mid][c];
//		if(fabs(resy) < y_clusterrange[rm_size]) tn_cluster_inrange++;
//		if(fabs(dum_resy) < y_clusterrange[rm_size]) dum_tn_cluster_inrange++;
//		h_gtr_res_all_y[mid] ->Fill(resy);
//        h_dum_gtr_res_all_y[mid]->Fill(dum_resy);
//	    if(min_resy > resy) min_resy = resy;
//  //      h_hit_fit[mid]->Fill(gtr100yb_cluster_y->at(k), rk_fit_gtr_gy[rm_size]->at(tid));
//	}
//	dum_rk_fit_gtr_y[mid][c] = rk_fit_gtr_gy[rm_size]->at(tid);
//    h_gtr_res_min_y[mid]->Fill(min_resy);
//	if(tn_cluster_inrange > 0){
//		return true;
//	}
//	else { return false;}
}



void LayerEfficiencyCalculator::CalculateResidualsXUsingHits(int tid, int &tn_hits_inrange, int &dum_tn_hits_inrange , bool IsBeforeY){
	int c = rk_charge->at(tid);
	double min_resx = 10000;
	double min_dum_resx = 10000;
    int n_gtr_hits[3] = {n_gtr100x_hits, n_gtr200x_hits, n_gtr300x_hits};
	int rk_fit_gtr_mid[3] = {rk_fit_gtr100_mid->at(tid), rk_fit_gtr200_mid->at(tid), rk_fit_gtr300_mid->at(tid)};
    int mid = rk_fit_gtr_mid[rm_size];
    std::vector<int> *gtrx_hit_mid[3]    =  {gtr100x_hit_mid, gtr200x_hit_mid, gtr300x_hit_mid};
    std::vector<float> *gtrx_hit_adc[3] =  {gtr100x_hit_adc, gtr200x_hit_adc, gtr300x_hit_adc};
//    std::vector<int> *gtrx_hit_size[3] =  {gtr100x_hit_size, gtr200x_hit_size, gtr300x_hit_size};
    std::vector<double> *rk_fit_gtr_gx[3] =    {rk_fit_gtr100_gx,   rk_fit_gtr200_gx,   rk_fit_gtr300_gx};
    std::vector<double> *rk_fit_gtr_gy[3] =    {rk_fit_gtr100_gy,   rk_fit_gtr200_gy,   rk_fit_gtr300_gy};
    std::vector<double> *rk_fit_gtr_gz[3] =    {rk_fit_gtr100_gz,   rk_fit_gtr200_gz,   rk_fit_gtr300_gz};
    std::vector<double> *gtrx_hit_gx[3] =  {gtr100x_hit_gx, gtr200x_hit_gx, gtr300x_hit_gx};
    std::vector<double> *gtrx_hit_gz[3] =  {gtr100x_hit_gz, gtr200x_hit_gz, gtr300x_hit_gz};
    std::vector<double> *gtrx_hit_t[3] =  {gtr100x_hit_t, gtr200x_hit_t, gtr300x_hit_t};
 //   std::vector<double> *gtrx_hit_t2[3] =  {gtr100x_hit_t2, gtr200x_hit_t2, gtr300x_hit_t2};
    std::vector<double> *gtry_hit_t[3] =   {gtr100y_hit_t, gtr200y_hit_t, gtr300y_hit_t};
//    std::vector<double> *gtry_hit_t2[3] =  {gtr100y_hit_t2, gtr200y_hit_t2, gtr300y_hit_t2};
    int memoryxk;
	if(c == -1) c = 0; //charge minus
		for(int k = 0; k < n_gtr_hits[rm_size];k++){
			if(rk_fit_gtr_mid[rm_size] != gtrx_hit_mid[rm_size]->at(k) ) continue; //module match
//			std::cout << "gtrx_hit_adc" << gtrx_hit_adc[rm_size]->at(k) << std::endl;
//			if(gtrx_hit_adc[rm_size]->at(k)>50e3) continue;//remove fake hit
//			if(gtrx_hit_size[rm_size]->at(k) < 2) continue;
            //if(chi_square->at(tid) > 10) continue;
            double resx, dum_resx;
			if(IsBeforeY){
				resx = sqrt(pow(gtrx_hit_gx[rm_size]->at(k) - rk_fit_gtr_gx[rm_size]->at(tid), 2) 
					 + pow(gtrx_hit_gz[rm_size]->at(k) - rk_fit_gtr_gz[rm_size]->at(tid), 2));
				dum_resx = sqrt(pow(gtrx_hit_gx[rm_size]->at(k) - dum_rk_fit_gtr_gx[mid-100][c], 2) 
							 + pow(gtrx_hit_gz[rm_size]->at(k) - dum_rk_fit_gtr_gz[mid-100][c], 2));
			if(gtrx_hit_gx[rm_size]->at(k) - rk_fit_gtr_gx[rm_size]->at(tid) < 0) {resx = -1 * resx;}
			if(gtrx_hit_gx[rm_size]->at(k) - dum_rk_fit_gtr_gx[mid-100][c] < 0)   {dum_resx = -1 * dum_resx;}
			}
	    	else {
				resx = sqrt(pow(gtrx_hit_gx[rm_size]->at(k) - rk_fit_gtr_gx[rm_size]->at(tid), 2) 
					 + pow(gtrx_hit_gz[rm_size]->at(k) - rk_fit_gtr_gz[rm_size]->at(tid), 2));
				dum_resx = sqrt(pow(gtrx_hit_gx[rm_size]->at(k) - dum2_rk_fit_gtr_gx[mid-100][c], 2) 
							 + pow(gtrx_hit_gz[rm_size]->at(k) - dum2_rk_fit_gtr_gz[mid-100][c], 2));
			if(gtrx_hit_gx[rm_size]->at(k) - rk_fit_gtr_gx[rm_size]->at(tid) < 0) {resx = -1 * resx;}
			if(gtrx_hit_gx[rm_size]->at(k) - dum2_rk_fit_gtr_gx[mid-100][c] < 0)   {dum_resx = -1 * dum_resx;}
			}

//			std::cout << "res x using hit  : " << resx << std::endl;
			if( xm_hitrange[rm_size] < resx && resx < xp_hitrange[rm_size] ) tn_hits_inrange++;
			if( xm_hitrange[rm_size] < dum_resx && dum_resx < xp_hitrange[rm_size]) dum_tn_hits_inrange++;
			if(fabs(resx) < fabs(min_resx)) {
				min_resx = resx;
				min_dum_resx = dum_resx;
				memoryxk = k;
			}
			if(IsBeforeY){
				h_gtr_res_all_x_wo_Y[mid- 100]->Fill(resx);
				h_dum_gtr_res_all_x_wo_Y[mid- 100]->Fill(dum_resx);
			}
			else {
				h_gtr_res_all_x[mid- 100]->Fill(resx);
				h_dum_gtr_res_all_x[mid - 100]->Fill(dum_resx);
	
			}
//            h_rk_hit_plane[mid-100]->Fill(rk_fit_gtr100_gx->at(tid), rk_fit_gtr100_gz->at(tid));
		}
	if(IsBeforeY){
//    h_gtr_res_min_x[mid-100]->Fill(min_resx); 
//    h_dum_gtr_res_min_x[mid-100]->Fill(min_dum_resx); 
	dum_rk_fit_gtr_gx[mid-100][c] = rk_fit_gtr_gx[rm_size]->at(tid);
	dum_rk_fit_gtr_gy[mid-100][c] = rk_fit_gtr_gy[rm_size]->at(tid);
	dum_rk_fit_gtr_gz[mid-100][c] = rk_fit_gtr_gz[rm_size]->at(tid);
	}
	else {
	    h_gtr_res_min_x[mid-100]->Fill(min_resx); 
    	h_dum_gtr_res_min_x[mid-100]->Fill(min_dum_resx); 
	dum2_rk_fit_gtr_gx[mid-100][c] = rk_fit_gtr_gx[rm_size]->at(tid);
	dum2_rk_fit_gtr_gy[mid-100][c] = rk_fit_gtr_gy[rm_size]->at(tid);
	dum2_rk_fit_gtr_gz[mid-100][c] = rk_fit_gtr_gz[rm_size]->at(tid);
//				if(rm_size == 1){
//				h_timingx_dis[mid-100]->Fill(gtrx_hit_t[rm_size]->at(memoryxk));
//				h_timingx2_dis[mid-100]->Fill(gtrx_hit_t2[rm_size]->at(memoryxk));
//				h_timingy_dis[mid-100]->Fill(gtry_hit_t[rm_size]->at(memoryk));
//				h_timingy2_dis[mid-100]->Fill(gtry_hit_t2[rm_size]->at(memoryk));
//				h_timing_corr_xy[mid-100] ->Fill(gtrx_hit_t[rm_size]->at(memoryxk), gtry_hit_t[rm_size]->at(memoryk));
//				h_timing2_corr_xy[mid-100]->Fill(gtrx_hit_t2[rm_size]->at(memoryxk), gtry_hit_t2[rm_size]->at(memoryk));
//				h_timing_diff[mid-100] ->Fill(gtrx_hit_t[rm_size]->at(memoryxk) - gtry_hit_t[rm_size]->at(memoryk));
//				h_timing2_diff[mid-100] ->Fill(gtrx_hit_t2[rm_size]->at(memoryxk) - gtry_hit_t2[rm_size]->at(memoryk));
//				}

	}
}


void LayerEfficiencyCalculator::CalculateResidualsX(int tid, int &tn_cluster_inrange, int &dum_tn_cluster_inrange , bool IsBeforeY){
	int c = rk_charge->at(tid);
	double min_resx = 10000;
	double min_dum_resx = 10000;
    int n_gtr_clusters[3] = {n_gtr100x_clusters, n_gtr200x_clusters, n_gtr300x_clusters};
	int rk_fit_gtr_mid[3] = {rk_fit_gtr100_mid->at(tid), rk_fit_gtr200_mid->at(tid), rk_fit_gtr300_mid->at(tid)};
    int mid = rk_fit_gtr_mid[rm_size];
    std::vector<int> *gtrx_cluster_mid[3]    =  {gtr100x_cluster_mid, gtr200x_cluster_mid, gtr300x_cluster_mid};
    std::vector<float> *gtrx_cluster_adc[3] =  {gtr100x_cluster_adc, gtr200x_cluster_adc, gtr300x_cluster_adc};
    std::vector<int> *gtrx_cluster_size[3] =  {gtr100x_cluster_size, gtr200x_cluster_size, gtr300x_cluster_size};
    std::vector<double> *rk_fit_gtr_gx[3] =    {rk_fit_gtr100_gx,   rk_fit_gtr200_gx,   rk_fit_gtr300_gx};
    std::vector<double> *rk_fit_gtr_gy[3] =    {rk_fit_gtr100_gy,   rk_fit_gtr200_gy,   rk_fit_gtr300_gy};
    std::vector<double> *rk_fit_gtr_gz[3] =    {rk_fit_gtr100_gz,   rk_fit_gtr200_gz,   rk_fit_gtr300_gz};
    std::vector<double> *gtrx_cluster_gx[3] =  {gtr100x_cluster_gx, gtr200x_cluster_gx, gtr300x_cluster_gx};
    std::vector<double> *gtrx_cluster_gz[3] =  {gtr100x_cluster_gz, gtr200x_cluster_gz, gtr300x_cluster_gz};
    std::vector<double> *gtrx_cluster_t[3] =  {gtr100x_cluster_t, gtr200x_cluster_t, gtr300x_cluster_t};
    std::vector<double> *gtrx_cluster_t2[3] =  {gtr100x_cluster_t2, gtr200x_cluster_t2, gtr300x_cluster_t2};
    std::vector<double> *gtry_cluster_t[3] =   {gtr100y_cluster_t, gtr200y_cluster_t, gtr300y_cluster_t};
    std::vector<double> *gtry_cluster_t2[3] =  {gtr100y_cluster_t2, gtr200y_cluster_t2, gtr300y_cluster_t2};
    int memoryxk;
	if(c == -1) c = 0; //charge minus
		for(int k = 0; k < n_gtr_clusters[rm_size];k++){
			if(rk_fit_gtr_mid[rm_size] != gtrx_cluster_mid[rm_size]->at(k) ) continue; //module match
			if(gtrx_cluster_adc[rm_size]->at(k)>50e3) continue;//remove fake hit
			if(gtrx_cluster_size[rm_size]->at(k) < 2) continue;
            //if(chi_square->at(tid) > 10) continue;
            double resx, dum_resx;
			if(IsBeforeY){
				resx = sqrt(pow(gtrx_cluster_gx[rm_size]->at(k) - rk_fit_gtr_gx[rm_size]->at(tid), 2) 
					 + pow(gtrx_cluster_gz[rm_size]->at(k) - rk_fit_gtr_gz[rm_size]->at(tid), 2));
				dum_resx = sqrt(pow(gtrx_cluster_gx[rm_size]->at(k) - dum_rk_fit_gtr_gx[mid-100][c], 2) 
							 + pow(gtrx_cluster_gz[rm_size]->at(k) - dum_rk_fit_gtr_gz[mid-100][c], 2));
			if(gtrx_cluster_gx[rm_size]->at(k) - rk_fit_gtr_gx[rm_size]->at(tid) < 0) {resx = -1 * resx;}
			if(gtrx_cluster_gx[rm_size]->at(k) - dum_rk_fit_gtr_gx[mid-100][c] < 0)   {dum_resx = -1 * dum_resx;}
			}
	    	else {
				resx = sqrt(pow(gtrx_cluster_gx[rm_size]->at(k) - rk_fit_gtr_gx[rm_size]->at(tid), 2) 
					 + pow(gtrx_cluster_gz[rm_size]->at(k) - rk_fit_gtr_gz[rm_size]->at(tid), 2));
				dum_resx = sqrt(pow(gtrx_cluster_gx[rm_size]->at(k) - dum2_rk_fit_gtr_gx[mid-100][c], 2) 
							 + pow(gtrx_cluster_gz[rm_size]->at(k) - dum2_rk_fit_gtr_gz[mid-100][c], 2));
			if(gtrx_cluster_gx[rm_size]->at(k) - rk_fit_gtr_gx[rm_size]->at(tid) < 0) {resx = -1 * resx;}
			if(gtrx_cluster_gx[rm_size]->at(k) - dum2_rk_fit_gtr_gx[mid-100][c] < 0)   {dum_resx = -1 * dum_resx;}
			}

			if(fabs(resx) < x_clusterrange[rm_size]) tn_cluster_inrange++;
			if(fabs(dum_resx) < x_clusterrange[rm_size]) dum_tn_cluster_inrange++;
//			std::cout << "res x using cls  : " << resx << std::endl;
			if(fabs(resx) < fabs(min_resx)) {
				min_resx = resx;
				min_dum_resx = dum_resx;
				memoryxk = k;
			}
			if(IsBeforeY){
				h_gtr_res_all_x_wo_Y[mid- 100]->Fill(resx);
				h_dum_gtr_res_all_x_wo_Y[mid- 100]->Fill(dum_resx);
			}
			else {
				h_gtr_res_all_x[mid- 100]->Fill(resx);
				h_dum_gtr_res_all_x[mid - 100]->Fill(dum_resx);
	
			}
//            h_rk_hit_plane[mid-100]->Fill(rk_fit_gtr100_gx->at(tid), rk_fit_gtr100_gz->at(tid));
		}
	if(IsBeforeY){
//    h_gtr_res_min_x[mid-100]->Fill(min_resx); 
//    h_dum_gtr_res_min_x[mid-100]->Fill(min_dum_resx); 
	dum_rk_fit_gtr_gx[mid-100][c] = rk_fit_gtr_gx[rm_size]->at(tid);
	dum_rk_fit_gtr_gy[mid-100][c] = rk_fit_gtr_gy[rm_size]->at(tid);
	dum_rk_fit_gtr_gz[mid-100][c] = rk_fit_gtr_gz[rm_size]->at(tid);
	}
	else {
	    h_gtr_res_min_x[mid-100]->Fill(min_resx); 
    	h_dum_gtr_res_min_x[mid-100]->Fill(min_dum_resx); 
	dum2_rk_fit_gtr_gx[mid-100][c] = rk_fit_gtr_gx[rm_size]->at(tid);
	dum2_rk_fit_gtr_gy[mid-100][c] = rk_fit_gtr_gy[rm_size]->at(tid);
	dum2_rk_fit_gtr_gz[mid-100][c] = rk_fit_gtr_gz[rm_size]->at(tid);
				if(rm_size == 1){
				h_timingx_dis[mid-100]->Fill(gtrx_cluster_t[rm_size]->at(memoryxk));
				h_timingx2_dis[mid-100]->Fill(gtrx_cluster_t2[rm_size]->at(memoryxk));
				h_timingy_dis[mid-100]->Fill(gtry_cluster_t[rm_size]->at(memoryk));
				h_timingy2_dis[mid-100]->Fill(gtry_cluster_t2[rm_size]->at(memoryk));
				h_timing_corr_xy[mid-100] ->Fill(gtrx_cluster_t[rm_size]->at(memoryxk), gtry_cluster_t[rm_size]->at(memoryk));
				h_timing2_corr_xy[mid-100]->Fill(gtrx_cluster_t2[rm_size]->at(memoryxk), gtry_cluster_t2[rm_size]->at(memoryk));
				h_timing_diff[mid-100] ->Fill(gtrx_cluster_t[rm_size]->at(memoryxk) - gtry_cluster_t[rm_size]->at(memoryk));
				h_timing2_diff[mid-100] ->Fill(gtrx_cluster_t2[rm_size]->at(memoryxk) - gtry_cluster_t2[rm_size]->at(memoryk));
				}

	}
}

//void LayerEfficiencyCalculator::CalculateResidualsX(int tid, int &tn_cluster_inrange, int &dum_tn_cluster_inrange){
//	int mid = rk_fit_gtr100_mid->at(tid);
//	int c = rk_charge->at(id);
//	double min_resx = 10000;
//	double min_dum_resx = 10000;
//    int n_cluster[3] = {n_gtr100x_clusters, n_gtr200x_clusters, n_gtr300x_clusters};
//	if(c == -1) c = 0; //charge minus
//		for(int k = 0; k < n_gtr100x_clusters;k++){
//			if(rk_fit_gtr100_mid->at(tid) != gtr100x_cluster_mid->at(k) ) continue; //module match
//			if(gtr100x_cluster_adc->at(k)>50e3) continue;//remove fake hit
//			if(gtr100x_cluster_size->at(k) < 2) continue;
//            //if(chi_square->at(tid) > 10) continue;
//            
//			double resx = sqrt(pow(gtr100x_cluster_gx->at(k) - rk_fit_gtr100_gx->at(tid), 2) 
//						 + pow(gtr100x_cluster_gz->at(k) - rk_fit_gtr100_gz->at(tid), 2));
//			double dum_resx = sqrt(pow(gtr100x_cluster_gx->at(k) - dum_rk_fit_gtr_gx[mid-100][c], 2) 
//							 + pow(gtr100x_cluster_gz->at(k) - dum_rk_fit_gtr_gz[mid-100][c], 2));
//			if(resx < 1.5) tn_cluster_inrange++;
//			if(dum_resx < 1.5) dum_tn_cluster_inrange++;
//			if(gtr100x_cluster_gx->at(k) - rk_fit_gtr100_gx->at(tid) < 0) resx = -1 * resx;
//			if(gtr100x_cluster_gx->at(k) - dum_rk_fit_gtr_gx[mid-100][c] < 0) dum_resx = -1 * dum_resx;
//			if(fabs(resx) < fabs(min_resx)) {
//				min_resx = resx;
//				min_dum_resx = dum_resx;
//			}
//			h_gtr_res_all_x[mid- 100]->Fill(resx);
//			h_dum_gtr_res_all_x[mid - 100]->Fill(dum_resx);
////            h_rk_hit_plane[mid-100]->Fill(rk_fit_gtr100_gx->at(tid), rk_fit_gtr100_gz->at(tid));
//		}
//    h_gtr_res_min_x[mid-100]->Fill(min_resx); 
//    h_dum_gtr_res_min_x[mid-100]->Fill(min_dum_resx); 
//	dum_rk_fit_gtr_gx[mid-100][c] = rk_fit_gtr100_gx->at(tid);
//	dum_rk_fit_gtr_gy[mid-100][c] = rk_fit_gtr100_gy->at(tid);
//	dum_rk_fit_gtr_gz[mid-100][c] = rk_fit_gtr100_gz->at(tid);
//}

void LayerEfficiencyCalculator::CalculateResiduals(int &cnt){
	for(int i = 0; i < selected_track_indexes.size() ; i++){//modified 220519
		int tid = selected_track_indexes[i];
	    int gtrmid;
	    if(rm_size == 0)gtrmid = rk_fit_gtr100_mid->at(tid);
    	else if(rm_size == 1)gtrmid = rk_fit_gtr200_mid->at(tid);
	    else if(rm_size == 2)gtrmid = rk_fit_gtr300_mid->at(tid);
		int tn_cluster_inrange_x = 0;
		int tn_cluster_inrange_x_wo_Y = 0;
		int dum_tn_cluster_inrange_x = 0;
		int dum_tn_cluster_inrange_x_wo_Y = 0;
		int tn_cluster_inrange_y = 0;
		int dum_tn_cluster_inrange_y = 0;
		int all_cut_n_cluster_inrange = 0;
		CalculateResidualsX(tid, tn_cluster_inrange_x_wo_Y, dum_tn_cluster_inrange_x_wo_Y, 1); // before Y associate
		h_n_cluster_inrange_wo_Y[gtrmid - 100]->Fill(tn_cluster_inrange_x_wo_Y);
		h_dum_n_cluster_inrange_wo_Y[gtrmid - 100]->Fill(dum_tn_cluster_inrange_x_wo_Y);
       bool y_ass = AssociationGTRY(tid, tn_cluster_inrange_y, dum_tn_cluster_inrange_y);
		h_n_cluster_inrange_y[gtrmid - 100]->Fill(tn_cluster_inrange_y);
		h_dum_n_cluster_inrange_y[gtrmid - 100]->Fill(dum_tn_cluster_inrange_y);
//           ------ before Y association
//           after Y association ------------
		if(y_ass){
			CalculateResidualsX(tid, tn_cluster_inrange_x, dum_tn_cluster_inrange_x, 0 );//after Y associate
		    cnt++;
			h_n_cluster_inrange[gtrmid - 100]->Fill(tn_cluster_inrange_x);
	 		trk_charge = rk_charge->at(tid);
		    n_cluster_inrange = tn_cluster_inrange_x;
    		module_id[rm_size] = gtrmid; 
			//post_detector_res_x[1] = min_resx;
			h_dum_n_cluster_inrange[gtrmid - 100]->Fill(dum_tn_cluster_inrange_x);
			h_all_cut_n_cluster_inrange[gtrmid - 100]->Fill(all_cut_n_cluster_inrange);
			out_tree->Fill();
		}
	}//end tid
}



void LayerEfficiencyCalculator::CalculateResidualsXUsingRawHits(int tid ,int &tn_hits_inrange, int &tn_dum_hits_inrange) {
	int rk_fit_gtr_mid[3] = {rk_fit_gtr100_mid->at(tid), rk_fit_gtr200_mid->at(tid), rk_fit_gtr300_mid->at(tid)};
    int n_gtr_yhits[3] = {n_gtr100y_hits, n_gtr200y_hits, n_gtr300y_hits};
    int n_gtr_xhits[3] = {n_gtr100x_hits, n_gtr200x_hits, n_gtr300x_hits};
    std::vector<int>    *gtry_hit_mid[3]  =  {gtr100y_hit_mid,  gtr200y_hit_mid,  gtr300y_hit_mid};
    std::vector<float> *gtry_hit_adc[3]  =  {gtr100y_hit_adc,  gtr200y_hit_adc,  gtr300y_hit_adc};
//    std::vector<int>    *gtry_hit_size[3] =  {gtr100y_hit_size, gtr200y_hit_size, gtr300y_hit_size};
    std::vector<double> *rk_fit_gtr_gx[3] =  {rk_fit_gtr100_gx,   rk_fit_gtr200_gx,   rk_fit_gtr300_gx};
    std::vector<double> *rk_fit_gtr_gy[3] =  {rk_fit_gtr100_gy,   rk_fit_gtr200_gy,   rk_fit_gtr300_gy};
    std::vector<double> *rk_fit_gtr_gz[3] =  {rk_fit_gtr100_gz,   rk_fit_gtr200_gz,   rk_fit_gtr300_gz};
    std::vector<double> *gtry_hit_y[3]    =  {gtr100y_hit_y, gtr200y_hit_y, gtr300y_hit_y};
    std::vector<double> *gtry_hit_t[3]    =  {gtr100y_hit_t, gtr200y_hit_t, gtr300y_hit_t};
	int c = rk_charge->at(tid);
	double min_resx = 10000;
	double min_dum_resx = 10000;
    int n_gtr_hits[3] = {n_gtr100x_hits, n_gtr200x_hits, n_gtr300x_hits};
    int mid = rk_fit_gtr_mid[rm_size];
    std::vector<int> *gtrx_hit_mid[3]    =  {gtr100x_hit_mid, gtr200x_hit_mid, gtr300x_hit_mid};
    std::vector<float> *gtrx_hit_adc[3] =  {gtr100x_hit_adc, gtr200x_hit_adc, gtr300x_hit_adc};
    std::vector<double> *gtrx_hit_gx[3] =  {gtr100x_hit_gx, gtr200x_hit_gx, gtr300x_hit_gx};
    std::vector<double> *gtrx_hit_gz[3] =  {gtr100x_hit_gz, gtr200x_hit_gz, gtr300x_hit_gz};
    std::vector<double> *gtrx_hit_t[3] =  {gtr100x_hit_t, gtr200x_hit_t, gtr300x_hit_t};
    int memoryxk;
	if(c == -1) c = 0; //charge minus
    double min_resy = 10000;
    double resx,dum_resx, resy, dum_resy;
	for(int k = 0; k < n_gtr_yhits[rm_size]; k++){
		if(rk_fit_gtr_mid[rm_size] != gtry_hit_mid[rm_size]->at(k) ) continue; //module match
		if(gtry_hit_adc[rm_size]->at(k)>50e3) continue;//remove fake hit (maybe no meaning here)
		if(gtry_hit_adc[rm_size]->at(k)<50) continue;//remove fake hit (maybe no meaning here)
		for(int j = 0; j < n_gtr_xhits[rm_size]; j++){
//			if(rk_fit_gtr_mid[rm_size] != gtrx_hit_mid[rm_size]->at(j) ) continue; //module match
//			if(gtrx_hit_adc[rm_size]->at(j)>50e3) continue;//remove fake hit (maybe no meaning here)
//			if(gtrx_hit_adc[rm_size]->at(j)<50) continue;//remove fake hit (maybe no meaning here)
//    	    if(fabs(gtrx_hit_t[rm_size]->at(j) - gtry_hit_t[rm_size]->at(j)) < 300){
//			if(rm_size == 0 ){//gtr 100
//    	   	     resy     = gtry_hit_y[rm_size]->at(k) + rk_fit_gtr_gy[rm_size]->at(tid);
//	             dum_resy = gtry_hit_y[rm_size]->at(k) + dum_rk_fit_gtr_y[mid][c];
//			}
//			else {//gtr200, 300
//    		     resy     = gtry_hit_y[rm_size]->at(k) - rk_fit_gtr_gy[rm_size]->at(tid);
//        	     dum_resy = gtry_hit_y[rm_size]->at(k) - dum_rk_fit_gtr_y[mid][c];
//			}
//				
//				resx = sqrt(pow(gtrx_hit_gx[rm_size]->at(j) - rk_fit_gtr_gx[rm_size]->at(tid), 2) 
//					 + pow(gtrx_hit_gz[rm_size]->at(j) - rk_fit_gtr_gz[rm_size]->at(tid), 2));
//				dum_resx = sqrt(pow(gtrx_hit_gx[rm_size]->at(j) - dum2_rk_fit_gtr_gx[mid-100][c], 2) 
//							 + pow(gtrx_hit_gz[rm_size]->at(j) - dum2_rk_fit_gtr_gz[mid-100][c], 2));
//			if(gtrx_hit_gx[rm_size]->at(j) - rk_fit_gtr_gx[rm_size]->at(tid) < 0) {resx = -1 * resx;}
//			if(gtrx_hit_gx[rm_size]->at(j) - dum2_rk_fit_gtr_gx[mid-100][c] < 0)   {dum_resx = -1 * dum_resx;}
//			}
//			if(fabs(resx) < 5 && fabs(resy) < 5){
//		//if(ym_hitrange[rm_size] < resy  && resy < yp_hitrange[rm_size]) tn_hits_inrange++;
////		if(ym_hitrange[rm_size] <  dum_resy &&  dum_resy < yp_hitrange[rm_size]) dum_tn_hits_inrange++;
//	
//				h_gtr_res_all_y[mid] ->Fill(resy);
//    		    h_dum_gtr_res_all_y[mid ]->Fill(dum_resy);
//				h_gtr_res_all_x[mid] ->Fill(resx);
//    		    h_dum_gtr_res_all_x[mid ]->Fill(dum_resx);
//			}
//

			}
		}
		

	dum_rk_fit_gtr_y[mid][c] = rk_fit_gtr_gy[rm_size]->at(tid);
    h_gtr_res_min_y[mid]->Fill(min_resy);
	if(tn_hits_inrange > 0){
		
	}
}

void LayerEfficiencyCalculator::CalculateResidualsUsingRawHits(int &cnt){
	for(int i = 0; i < selected_track_indexes.size() ; i++){//modified 220519
		int tid = selected_track_indexes[i];
	    int gtrmid;
	    if(rm_size == 0)gtrmid = rk_fit_gtr100_mid->at(tid);
    	else if(rm_size == 1)gtrmid = rk_fit_gtr200_mid->at(tid);
	    else if(rm_size == 2)gtrmid = rk_fit_gtr300_mid->at(tid);
		int tn_cluster_inrange_x = 0;
		int tn_cluster_inrange_x_wo_Y = 0;
		int dum_tn_cluster_inrange_x = 0;
		int dum_tn_cluster_inrange_x_wo_Y = 0;
		int tn_cluster_inrange_y = 0;
		int dum_tn_cluster_inrange_y = 0;
		int all_cut_n_cluster_inrange = 0;
		h_n_cluster_inrange_wo_Y[gtrmid - 100]->Fill(tn_cluster_inrange_x_wo_Y);
		h_dum_n_cluster_inrange_wo_Y[gtrmid - 100]->Fill(dum_tn_cluster_inrange_x_wo_Y);
		h_n_cluster_inrange_y[gtrmid - 100]->Fill(tn_cluster_inrange_y);
		h_dum_n_cluster_inrange_y[gtrmid - 100]->Fill(dum_tn_cluster_inrange_y);
		    CalculateResidualsXUsingRawHits(tid, tn_cluster_inrange_x, dum_tn_cluster_inrange_x); 
		    cnt++;
		h_n_cluster_inrange[gtrmid - 100]->Fill(tn_cluster_inrange_x);
		trk_charge = rk_charge->at(tid);
	    n_cluster_inrange = tn_cluster_inrange_x;
    	module_id[rm_size] = gtrmid; 
		//post_detector_res_x[1] = min_resx;
		h_dum_n_cluster_inrange[gtrmid - 100]->Fill(dum_tn_cluster_inrange_x);
		h_all_cut_n_cluster_inrange[gtrmid - 100]->Fill(all_cut_n_cluster_inrange);
		out_tree->Fill();
	}//end tid
}





void LayerEfficiencyCalculator::CalculateResidualsUsingHits(int &cnt){
	for(int i = 0; i < selected_track_indexes.size() ; i++){//modified 220519
		int tid = selected_track_indexes[i];
	    int gtrmid;
	    if(rm_size == 0)gtrmid = rk_fit_gtr100_mid->at(tid);
    	else if(rm_size == 1)gtrmid = rk_fit_gtr200_mid->at(tid);
	    else if(rm_size == 2)gtrmid = rk_fit_gtr300_mid->at(tid);
		int tn_cluster_inrange_x = 0;
		int tn_cluster_inrange_x_wo_Y = 0;
		int dum_tn_cluster_inrange_x = 0;
		int dum_tn_cluster_inrange_x_wo_Y = 0;
		int tn_cluster_inrange_y = 0;
		int dum_tn_cluster_inrange_y = 0;
		int all_cut_n_cluster_inrange = 0;
		CalculateResidualsXUsingHits(tid, tn_cluster_inrange_x_wo_Y, dum_tn_cluster_inrange_x_wo_Y, 1); // before Y associate
		h_n_cluster_inrange_wo_Y[gtrmid - 100]->Fill(tn_cluster_inrange_x_wo_Y);
		h_dum_n_cluster_inrange_wo_Y[gtrmid - 100]->Fill(dum_tn_cluster_inrange_x_wo_Y);
        bool y_ass = AssociationGTRYUsingHit(tid, tn_cluster_inrange_y, dum_tn_cluster_inrange_y);
		h_n_cluster_inrange_y[gtrmid - 100]->Fill(tn_cluster_inrange_y);
		h_dum_n_cluster_inrange_y[gtrmid - 100]->Fill(dum_tn_cluster_inrange_y);
//           ------ before Y association
//           after Y association ------------
		if(y_ass){
		    CalculateResidualsXUsingHits(tid, tn_cluster_inrange_x, dum_tn_cluster_inrange_x, 0); // after Y associate
		    cnt++;
		h_n_cluster_inrange[gtrmid - 100]->Fill(tn_cluster_inrange_x);
		trk_charge = rk_charge->at(tid);
	    n_cluster_inrange = tn_cluster_inrange_x;
    	module_id[rm_size] = gtrmid; 
		//post_detector_res_x[1] = min_resx;
		h_dum_n_cluster_inrange[gtrmid - 100]->Fill(dum_tn_cluster_inrange_x);
		h_all_cut_n_cluster_inrange[gtrmid - 100]->Fill(all_cut_n_cluster_inrange);
		out_tree->Fill();
	    }
	}//end tid
}
double  LayerEfficiencyCalculator::EvalTrueTrackRatioByLGX(  E16ANA_GTRStatus *gtr_status, E16ANA_GTRAnalyzerMaker *gtr_analyzers, int &cnt){
    std::array<std::vector<int> , 6> used_cluster_ids;
    for(int l = 0; l < 6; l++){
		used_cluster_ids.at(l).clear();	
	}
    std::vector<int> mix_selected_track_id;
    mix_selected_track_id.clear();
	for(int tid = 0; tid < track_id->size(); tid++){	
	    AssociateHBDCluster(tid, mix_ass_hbd_resx, mix_ass_hbd_resy, mix_ass_hbd_cluster_id);
		if(CheckUsedClustersForMix(tid, &used_cluster_ids)){
//			std::cout << "tid  = " << tid << std::endl;
			if(IsGoodHBDAssociation(tid, mix_ass_hbd_resx, mix_ass_hbd_resy)){
//				std::cout << "tid after hbd = " << tid << std::endl;
				if(IsHittedOnSurvivalArea(gtr_status, gtr_analyzers, tid)){
//					if(IsTriggerdTrack(tid)){
//				std::cout << "tid after dsead area = " << tid << std::endl;
					mix_selected_track_id.emplace_back(tid);		
//					}
				}
			}
		}
	}//tid finish
    
   if(mix_selected_track_id.size() != 0){
//	std::cout << "mixed track size = " << mix_selected_track_id.size() << std::endl; 
	}
	for(int t = 0; t< mix_selected_track_id.size() ; t++){
	int n_lg_hits_inrange[10] = {0,0,0,0,0,0,0,0,0,0};
	int n_lg_dum_hits_inrange[10] = {0,0,0,0,0,0,0,0,0,0};
	int tid = mix_selected_track_id[t];
    int gtrmid;
    if(rm_size == 0)gtrmid = rk_fit_gtr100_mid->at(tid);
    if(rm_size == 1)gtrmid = rk_fit_gtr200_mid->at(tid);
    if(rm_size == 2)gtrmid = rk_fit_gtr300_mid->at(tid);
	    double resx2 = 10000;
	    double min_resx2 = 10000;
	    double dum_resx2 = 10000;
	    double min_dumx = 10000;
    	double resy2 = 10000;
	    double min_resy2 = 10000;
        int min_mod = 100;
		for(int i = 0; i < n_lg_hits; i++){
		bool flag = false;
     	int mid = 0 ; 
		if(lg_hit_mid->at(i) == rk_fit_lg_c_mid->at(tid)){
			flag = true;
			mid  = lg_hit_mid->at(i);
		}
		else if(lg_hit_mid->at(i) == rk_fit_lg_b_mid->at(tid)){
			flag = true;
			mid  = lg_hit_mid->at(i);
		}
		else if(lg_hit_mid->at(i) == rk_fit_lg_a_mid->at(tid)){
			flag = true;
			mid  = lg_hit_mid->at(i);
		}
		if(flag){
			double ssdt = rk_hit_ssd_t->at(tid);
			if( fabs(lg_hit_t->at(i) - ssdt - 51) < 11 ){// ssd & lg timing match
				int ch = lg_hit_cid->at(i);
				if( ch < 10 || 49 < ch ){
						resx2 = lg_hit_x->at(i) - rk_fit_lg_c_x->at(tid);
						resy2 = lg_hit_y->at(i) - rk_fit_lg_c_y->at(tid);
      			        dum_resx2 =  lg_hit_x->at(i) - dum_rk_fit_lg_c_x[mid-100] ;
				}
				else if( ch/10 ==  1 ||  ch/10 == 4 ){
						resx2 = lg_hit_x->at(i) - rk_fit_lg_b_x->at(tid);
						resy2 = lg_hit_y->at(i) - rk_fit_lg_b_y->at(tid);
					    dum_resx2 =  lg_hit_x->at(i) - dum_rk_fit_lg_b_x[mid-100] ;
				}
				else if( ch/10 == 2 || ch/10 == 3 ){
						resx2 = lg_hit_x->at(i) - rk_fit_lg_a_x->at(tid);
						resy2 = lg_hit_y->at(i) - rk_fit_lg_a_y->at(tid);
					    dum_resx2 =  lg_hit_x->at(i) - dum_rk_fit_lg_a_x[mid-100] ;
				}
			    if( resx2 * resx2 + resy2 * resy2 < min_resx2*min_resx2 + min_resy2 * min_resy2){
    				min_resx2 = resx2;
     				min_resy2 = resy2;
                    min_dumx = dum_resx2;
					if(-50 < min_dumx && min_dumx < 0){
					std::cout << "res" << resx2 << std::endl;
					std::cout << "dum_res" << dum_resx2 << std::endl;
					}
                    min_mod  = mid;
//    				min_cluster_id = lg_hit_id->at(i);
	    		}
				if(fabs(resy2) < 100)  {
						h_mix_all_true_lg_res_x[gtrmid-100][mid-100]->Fill(resx2);//fill all hit
						h_mix_all_dum_lg_res_x [gtrmid-100][mid-100]->Fill(dum_resx2);
				   if(fabs(resx2) < 100) {  
						n_lg_hits_inrange[gtrmid-100]++;
					}
				   if(fabs(dum_resx2) < 100) {  
						n_lg_dum_hits_inrange[gtrmid-100]++;
					}
				}
			}
		}
	}//lg hit loop
	if(fabs(min_resy2) < 100)  {
//        std::cout <<"tid = " << tid << std::endl;
   if(fabs(min_resx2) < 100) {  
            cnt++;
    // std::cout << "min_resx2 = " << min_resx2 << ", " << min_resy2 << std::endl;
	}
	   	h_mix_true_lg_res_x[gtrmid-100][min_mod-100]->Fill(min_resx2);
		h_mix_dum_lg_res_x [gtrmid-100][min_mod-100]->Fill(min_dumx);

    for(int k=0; k < 10; k++){
    	h_n_lg_hits_inrange[k]->Fill(n_lg_hits_inrange[k]);
    	h_n_lg_dum_hits_inrange[k]->Fill(n_lg_dum_hits_inrange[k]);
	}

	}
	dum_rk_fit_lg_c_x[rk_fit_lg_c_mid->at(tid)-100] = rk_fit_lg_c_x->at(tid);
	dum_rk_fit_lg_b_x[rk_fit_lg_b_mid->at(tid)-100] = rk_fit_lg_b_x->at(tid);
   	dum_rk_fit_lg_a_x[rk_fit_lg_a_mid->at(tid)-100] = rk_fit_lg_a_x->at(tid);
	}
    
     //if(cnt != 0 )std::cout << "cnt2 =  " << cnt << std::endl;
    return cnt;
}


void LayerEfficiencyCalculator::Clear(){
	ass_hbd_resx.clear();	
	ass_hbd_resy.clear();	
	ass_hbd_cluster_id.clear();
	mix_ass_hbd_resx.clear();	
	mix_ass_hbd_resy.clear();	
	mix_ass_hbd_cluster_id.clear();
	ass_lg_resx.clear();	
	ass_lg_resy.clear();	
	ass_lg_hit_id.clear();
 	selected_track_indexes.clear();
}

void LayerEfficiencyCalculator::Calculate(){
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   int n_tk = 0;
   auto& calib = E16ANA_CalibDBManager::Instance();
   calib.SetRunID(30322);
   E16ANA_GTRcalibPedestal gtrped;
   gtrped.ReadCalibData(calib.CurrentRunID());
   auto gtr_status = new E16ANA_GTRStatus(calib.CurrentRunID());
   E16ANA_GTRcalibParams gtr_params;
   gtr_params.ReadCalibData(calib.CurrentRunID());
   E16ANA_GTRAnalyzerMaker *gtr_analyzers = new E16ANA_GTRAnalyzerMaker(gtr_params);
   for(int mid = 100; mid < 110; mid++){
	  for(int lid = 0; lid < 3 ; lid++){
		 E16ANA_GTRAnalyzer2 *analyzer = gtr_analyzers->Chamber(mid, lid);
         int n_strips = analyzer->GetNumberOfStrips();
 	     for(int sid = 0; sid < n_strips; sid++){
		    double ped = gtrped.GetPedestal(mid, lid, sid).Value();
 	 		double sigma = gtrped.GetPedestal(mid, lid, sid).Sigma();
  			analyzer->SetPedestal(sid, ped);
			analyzer->SetPedestalSigma(sid, sigma); 
		  }
	  }
	}
	  int cnt1 = 0;
	  int cnt2 = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	  if(jentry%1000 == 0 ){
	  	std::cout << jentry << " / " << nentries << std::endl;
	  }
	  if(jentry == maxevent) break;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
	  if(run_id != 30322) continue;
	  n_tk += track_id->size();
	  Clear();
      for(int i = 0; i < n_cands; i++){
	   h_rk_hit_plane[rk_fit_gtr100_mid->at(i)-100]->Fill(rk_fit_gtr100_gx->at(i), rk_fit_gtr100_gz->at(i));
      }
	  double aa = SelectTracks(gtr_status, gtr_analyzers);//selected by hbd residual and delete duplicated gtr cluster
//      CalculateResiduals(cnt1);//analyze using cluster info 
//     CalculateResidualsUsingHits(cnt1);//analyze using hit info
     CalculateResidualsUsingRawHits(cnt1);//analyze using hit info
	  
	  Clear();
	  double a = EvalTrueTrackRatioByLGX(gtr_status, gtr_analyzers, cnt2);
//      if(a != aa){
//	  		std::cout << "diffetnnnt" << std::endl;
//	  }
   }
   std::cout  <<"# of tracks = " << n_tk << std::endl;
   out_tree->Write();
   std::cout << "Cnt1, 2 " << cnt1 << ", " << cnt2 << std::endl;
   int lg_mix_nbins = h_mix_all_true_lg_res_x[0][0]->GetXaxis()->GetNbins();
   int lg_mix_min = h_mix_all_true_lg_res_x[0][0]->GetXaxis()->GetXmin();
   int lg_mix_max = h_mix_all_true_lg_res_x[0][0]->GetXaxis()->GetXmax();

    int gtrmid =6;
    TH1D *hadd_mix_min_true_lg_res_x[10];
    TH1D *hadd_mix_all_dum_lg_res_x[10];
    TH1D *hadd_mix_all_true_lg_res_x[10];
	for(int m = 100; m < 110; m++){
		hadd_mix_min_true_lg_res_x[m-100]  = new TH1D(Form("hadd_mix_min_true_lg_res_x_gtr%d", m),  Form("hadd_mix_min_true_lg_res_x_gtr%d", m ),  200, -800, 800);
		hadd_mix_all_dum_lg_res_x[m-100]  = new TH1D(Form("hadd_mix_all_dum_lg_res_x_gtr%d", m),  Form("hadd_mix_all_dum_lg_res_x_gtr%d", m ),  200, -800, 800);
		hadd_mix_all_true_lg_res_x[m-100]  = new TH1D(Form("hadd_mix_all_true_lg_res_x_gtr%d", m),  Form("hadd_mix_all_true_lg_res_x_gtr%d", m ),  200, -800, 800);
    }
	for(int tm=0; tm < 10; tm++){
	for(int m = 0; m<10 ; m++){
	//    lgt_s[gtrmid] += h_mix_true_lg_res_x[gtrmid][m]->Integral(ibin_m_100, ibin_p_100);
	    hadd_mix_min_true_lg_res_x[tm]->Add(h_mix_true_lg_res_x[tm][m]);
	    hadd_mix_all_dum_lg_res_x[tm]->Add(h_mix_all_dum_lg_res_x[tm][m]);
	    hadd_mix_all_true_lg_res_x[tm]->Add(h_mix_all_true_lg_res_x[tm][m]);
	}
	}
   
	TFile *fout = new TFile("hist.root", "recreate");
   
   for(int m = 0; m < 10; m++){
	   h_n_cluster_inrange[m]->Write();
	   h_dum_n_cluster_inrange[m]->Write();
	   h_n_cluster_inrange_y[m]->Write();
	   h_dum_n_cluster_inrange_y[m]->Write();
	   h_n_cluster_inrange_wo_Y[m]->Write();
	   h_dum_n_cluster_inrange_wo_Y[m]->Write();
	   h_all_cut_n_cluster_inrange[m]->Write();
	   h_hbd_res_x[m]->Write();
	   h_hbd_res_y[m]->Write();
	   h_lg_res_x[m]->Write();
	   h_lg_res_y[m]->Write();
	   h_gtr_res_all_x[m]->Write();
	   h_gtr_res_all_x_wo_Y[m]->Write();
	   h_dum_gtr_res_all_x_wo_Y[m]->Write();
	   h_gtr_res_all_y[m]->Write();
	   h_gtr_res_min_x[m]->Write();
	   h_gtr_res_min_y[m]->Write();
	   h_dum_gtr_res_all_x[m]->Write();
	   h_n_lg_hits_inrange[m]->Write();
	   h_n_lg_dum_hits_inrange[m]->Write();
	   h_fit_profile[m]->Write();
	h_y_hit_adc[m]->Write();
	   h_rk_hit_plane[m]->Write();
	   h_hit_fit[m]->Write();
	   for(int gm = 0; gm < 10; gm++){
		   h_mix_true_lg_res_x[gm][m]->Write();
		   h_mix_dum_lg_res_x[gm][m]->Write();
		   h_mix_all_true_lg_res_x[gm][m]->Write();
		   h_mix_all_dum_lg_res_x[gm][m]->Write();
	   }
      h_timingx_dis[m]->Write();
      h_timingx2_dis[m]->Write();
      h_timingy_dis[m]->Write();
      h_timingy2_dis[m]->Write();
      h_timing_corr_xy[m]->Write();
      h_timing2_corr_xy[m]->Write();
	  h_timing_diff[m]->Write();
	  h_timing2_diff[m]->Write();

	}
   
  int m = 6;//gtr module
  double sigma[3] = {1.5, 0.4, 0.5};
  int m_20 =  h_dum_gtr_res_all_x[m]->FindBin(-10);
  int m_10 =  h_dum_gtr_res_all_x[m]->FindBin(-5);
  int p_10 =  h_dum_gtr_res_all_x[m]->FindBin(5);
  int p_20 =  h_dum_gtr_res_all_x[m]->FindBin(10);
  int range_m =  h_gtr_res_min_x[m]->FindBin(-1*sigma[rm_size]);
  int range_p =  h_gtr_res_min_x[m]->FindBin(sigma[rm_size]);
//  int s_m = h_dum_gtr_res_min_x[m]->Integral(m_20, m_10);
//  int s_p = h_dum_gtr_res_min_x[m]->Integral(p_10, p_20);
  int s_m = h_dum_gtr_res_all_x[6]->Integral(m_20, m_10);
  int s_p = h_dum_gtr_res_all_x[6]->Integral(p_10, p_20);
  double ave = (double)(s_m + s_p)*0.5/(m_10 - m_20 + 1);
  std::cout <<"integral m = " <<  s_m << std::endl; 
  std::cout <<"integral p = " <<  s_p << std::endl; 
  std::cout <<"int = " <<  p_10 << std::endl; 
  std::cout <<"int = " <<  p_20 << std::endl; 
  std::cout <<"ave  = " <<  ave << std::endl; 
//  std::cout <<"area of gtr true in range  = " <<  h_gtr_res_min_x[m]->Integral(range_m, range_p) << std::endl; 
  std::cout <<"area of gtr true in range  = " <<  h_gtr_res_all_x[6]->Integral(range_m, range_p) << std::endl; 
  std::cout <<"area of bg  = " <<  ave * (range_p - range_m +1) << std::endl; 
 
//  EvaluateBGOfLGHits(6);
//  int lg_m_400 =  h_mix_dum_lg_res_x[m]->FindBin(-400);
//  int lg_m_200 =  h_mix_dum_lg_res_x[m]->FindBin(-200);
//  int lg_p_200 =  h_mix_dum_lg_res_x[m]->FindBin(200);
//  int lg_p_400 =  h_mix_dum_lg_res_x[m]->FindBin(400);
//  int lgald_m_400 =  h_mix_all_dum_lg_res_x[m]->FindBin(-400);
//  int lgald_m_200 =  h_mix_all_dum_lg_res_x[m]->FindBin(-200);
//  int lgald_p_200 =  h_mix_all_dum_lg_res_x[m]->FindBin(200);
//  int lgald_p_400 =  h_mix_all_dum_lg_res_x[m]->FindBin(400);
//  int lgalt_m_400 =  h_mix_all_true_lg_res_x[m]->FindBin(-400);
//  int lgalt_m_200 =  h_mix_all_true_lg_res_x[m]->FindBin(-200);
//  int lgalt_p_200 =  h_mix_all_true_lg_res_x[m]->FindBin(200);
//  int lgalt_p_400 =  h_mix_all_true_lg_res_x[m]->FindBin(400);
//  int lg_s_m = h_mix_dum_lg_res_x[m]->Integral(lg_m_400, lg_m_200);
//  int lg_s_p = h_mix_dum_lg_res_x[m]->Integral(lg_p_200, lg_p_400);
//  int lgald_s_m = h_mix_all_dum_lg_res_x[m]->Integral(lgald_m_400, lgald_m_200);
//  int lgald_s_p = h_mix_all_dum_lg_res_x[m]->Integral(lgald_p_200, lgald_p_400);
//  int lgalt_s_m = h_mix_all_true_lg_res_x[m]->Integral(lgalt_m_400, lgalt_m_200);
//  int lgalt_s_p = h_mix_all_true_lg_res_x[m]->Integral(lgalt_p_200, lgalt_p_400);
//  double lg_dum_ave = (double)(lg_s_m + lg_s_p)*0.5/(lg_m_200 - lg_m_400 + 1);
//  double lg_dum_all_ave = (double)(lgald_s_m + lgald_s_p)*0.5/(lgald_m_200 - lgald_m_400 + 1);
//  double lg_true_all_ave = (double)(lgalt_s_m + lgalt_s_p)*0.5/(lgalt_m_200 - lgalt_m_400 + 1);
//  std::cout <<"lg ave of bg  = " <<  lg_dum_ave << std::endl; 
//   
//  int lgt_m_100 =  h_mix_true_lg_res_x[6]->FindBin(-100);
//  int lgt_p_100 =  h_mix_true_lg_res_x[6]->FindBin( 100);
//  int lgt_s = h_mix_true_lg_res_x[6]->Integral(lgt_m_100, lgt_p_100);
//  int lgt_s2 = h_mix_all_true_lg_res_x[6]->Integral(lgt_m_100, lgt_p_100);
//  std::cout <<"area of lg min true in range  = " <<  lgt_s << std::endl; 
//  std::cout <<"area of lg all true in range  = " <<  lgt_s2 << std::endl; 
//  std::cout <<"area of lg dum in range with directly mix  = " <<  h_mix_dum_lg_res_x[6]->Integral(lgt_m_100, lgt_p_100) << std::endl; 
//  std::cout <<"area of lg dum  in range  = " <<  lg_dum_ave*(lgt_m_100 - lgt_p_100 +1) << std::endl; 
//  std::cout <<"bg of lg all true in range  = " <<  lg_true_all_ave*(lgt_m_100 - lgt_p_100 +1) << std::endl; 
//  std::cout <<"bg of lg all dumm in range  = " <<  lg_dum_all_ave*(lgt_m_100 - lgt_p_100 +1) << std::endl; 
////  std::cout <<"distance : " << lgt_p_100 - lgt_m_100 << std::endl;

	double left_low  = -400;
	double left_high = -200;
	double right_low  = 200;
	double right_high = 400;
// ith bin is same for evvery hist
    int ibin_min_ll = h_mix_all_dum_lg_res_x[gtrmid][gtrmid]->FindBin(left_low);
    int ibin_min_lh = h_mix_all_dum_lg_res_x[gtrmid][gtrmid]->FindBin(left_high);
    int ibin_min_rl = h_mix_all_dum_lg_res_x[gtrmid][gtrmid]->FindBin(right_low);
    int ibin_min_rh = h_mix_all_dum_lg_res_x[gtrmid][gtrmid]->FindBin(right_high);
    int ibin_m_100 =  h_mix_true_lg_res_x[gtrmid][gtrmid]->FindBin(-100);//for mini
    int ibin_p_100 =  h_mix_true_lg_res_x[gtrmid][gtrmid]->FindBin( 100);//for mini
    int lgt_s[10] = {};
    int lgt_all_true[10] = {};
    int lgt_all_dum[10] = {};
    double lg_dum_all_ave[10];
    double lg_true_all_ave[10];
    
//    int min_left_area  = h_mix_dum_lg_res_x[gtrmid][m]->Integral(ibin_min_ll, ibin_min_lh);
//    int min_right_area = h_mix_dum_lg_res_x[gtrmid][m]->Integral(ibin_min_rl, ibin_min_rh);	
    
    lgt_s[gtrmid]        = hadd_mix_min_true_lg_res_x[gtrmid]->Integral(ibin_m_100, ibin_p_100);
    lgt_all_true[gtrmid] = hadd_mix_all_true_lg_res_x[gtrmid]->Integral(ibin_m_100, ibin_p_100);
    lgt_all_dum[gtrmid]  = hadd_mix_all_dum_lg_res_x[gtrmid] ->Integral(ibin_m_100, ibin_p_100);
    int all_dum_left_area   = hadd_mix_all_dum_lg_res_x[gtrmid]    ->Integral(ibin_min_ll, ibin_min_lh);
    int all_dum_right_area  = hadd_mix_all_dum_lg_res_x[gtrmid]    ->Integral(ibin_min_rl, ibin_min_rh);	
    int all_true_left_area  = hadd_mix_all_true_lg_res_x[gtrmid]   ->Integral(ibin_min_ll, ibin_min_lh);
    int all_true_right_area = hadd_mix_all_true_lg_res_x[gtrmid]   ->Integral(ibin_min_rl, ibin_min_rh);	
	lg_dum_all_ave[gtrmid]  = (double)(all_dum_left_area + all_dum_right_area)*0.5/(ibin_min_lh - ibin_min_ll +1); 
    lg_true_all_ave[gtrmid] = (double)(all_true_left_area + all_true_right_area)*0.5/(ibin_min_lh - ibin_min_ll +1); 
//  int lgt_s2 = h_mix_all_true_lg_res_x[6]->Integral(lgt_m_100, lgt_p_100);
//  std::cout <<"area of lg all true in range  = " <<  lgt_s2 << std::endl; 
//  std::cout <<"area of lg dum in range with directly mix  = " <<  h_mix_dum_lg_res_x[6]->Integral(lgt_m_100, lgt_p_100) << std::endl; 
//  std::cout <<"area of lg dum  in range  = " <<  lg_dum_ave*(lgt_m_100 - lgt_p_100 +1) << std::endl; 
//  std::cout <<"bg of lg all true in range  = " <<  lg_true_all_ave*(lgt_m_100 - lgt_p_100 +1) << std::endl; 
//  std::cout <<"bg of lg all dumm in range  = " <<  lg_dum_all_ave*(lgt_m_100 - lgt_p_100 +1) << std::endl; 

    std::cout <<"area of lg min true in range  = " <<  lgt_s[gtrmid] << std::endl; 
    std::cout <<"area of lg all true in range  = " <<  lgt_all_true[gtrmid] << std::endl; 
    std::cout <<"area of lg all dumm in range  = " <<  lgt_all_dum[gtrmid] << std::endl; 
    std::cout <<"bg of lg all true in range  = " <<  lg_true_all_ave[gtrmid]*(ibin_m_100 - ibin_p_100 +1) << std::endl; 
    std::cout <<"bg of lg all dumm in range  = " <<  lg_dum_all_ave[gtrmid] *(ibin_m_100 - ibin_p_100 +1) << std::endl; 
    double side_lg_true =  lg_true_all_ave[gtrmid]*(ibin_m_100 - ibin_p_100 +1); 
    double side_lg_dum  =  lg_dum_all_ave[gtrmid] *(ibin_m_100 - ibin_p_100 +1); 
    std::cout <<"lg bg of raitio  = " <<  (double)side_lg_true/side_lg_dum << std::endl; 
   double lgbg_ratio =  (double)side_lg_true/side_lg_dum;
    std::cout <<"lg n hit in range true + dum  = " <<  h_n_lg_hits_inrange[gtrmid]->Integral(2,10) << std::endl; 
    std::cout <<"lg n hit in range dum(scaled) = " <<  h_n_lg_dum_hits_inrange[gtrmid]->Integral(2,10) * lgbg_ratio  << std::endl; 
    
    hadd_mix_all_true_lg_res_x[gtrmid]->Write();
//    hadd_mix_all_dum_lg_res_x[gtrmid]->Scale((double)(side_lg_true/side_lg_dum));
    hadd_mix_all_dum_lg_res_x[gtrmid]->SetLineColor(kRed);;
    hadd_mix_all_dum_lg_res_x[gtrmid]->Write();



  fout->Close(); 
}

void LayerEfficiencyCalculator::EvaluateBGOfLGHits(int gtrmid ){
	double left_low  = -400;
	double left_high = -200;
	double right_low  = 200;
	double right_high = 400;
// ith bin is same for evvery hist
    int ibin_min_ll = h_mix_all_dum_lg_res_x[gtrmid][gtrmid]->FindBin(left_low);
    int ibin_min_lh = h_mix_all_dum_lg_res_x[gtrmid][gtrmid]->FindBin(left_high);
    int ibin_min_rl = h_mix_all_dum_lg_res_x[gtrmid][gtrmid]->FindBin(right_low);
    int ibin_min_rh = h_mix_all_dum_lg_res_x[gtrmid][gtrmid]->FindBin(right_high);
    int ibin_m_100 =  h_mix_true_lg_res_x[gtrmid][gtrmid]->FindBin(-100);//for mini
    int ibin_p_100 =  h_mix_true_lg_res_x[gtrmid][gtrmid]->FindBin( 100);//for mini
    int lgt_s[10] = {};
    int lgt_all_true[10] = {};
    int lgt_all_dum[10] = {};
    double lg_dum_all_ave[10];
    double lg_true_all_ave[10];
    TH1D *hadd_mix_min_true_lg_res_x[10];
    TH1D *hadd_mix_all_dum_lg_res_x[10];
    TH1D *hadd_mix_all_true_lg_res_x[10];
	for(int m = 100; m < 110; m++){
		hadd_mix_min_true_lg_res_x[m-100]  = new TH1D(Form("hadd_mix_min_true_lg_res_x_gtr%d", m),  Form("hadd_mix_min_true_lg_res_x_gtr%d", m ),  200, -800, 800);
		hadd_mix_all_dum_lg_res_x[m-100]  = new TH1D(Form("hadd_mix_all_dum_lg_res_x_gtr%d", m),  Form("hadd_mix_all_dum_lg_res_x_gtr%d", m ),  200, -800, 800);
		hadd_mix_all_true_lg_res_x[m-100]  = new TH1D(Form("hadd_mix_all_true_lg_res_x_gtr%d", m),  Form("hadd_mix_all_true_lg_res_x_gtr%d", m ),  200, -800, 800);
    }
	for(int m = 0; m<10 ; m++){
	//    lgt_s[gtrmid] += h_mix_true_lg_res_x[gtrmid][m]->Integral(ibin_m_100, ibin_p_100);
	    hadd_mix_min_true_lg_res_x[gtrmid]->Add(h_mix_true_lg_res_x[gtrmid][m]);
	    hadd_mix_all_dum_lg_res_x[gtrmid]->Add(h_mix_all_dum_lg_res_x[gtrmid][m]);
	    hadd_mix_all_true_lg_res_x[gtrmid]->Add(h_mix_all_true_lg_res_x[gtrmid][m]);
	}
//    int min_left_area  = h_mix_dum_lg_res_x[gtrmid][m]->Integral(ibin_min_ll, ibin_min_lh);
//    int min_right_area = h_mix_dum_lg_res_x[gtrmid][m]->Integral(ibin_min_rl, ibin_min_rh);	
    
    lgt_s[gtrmid]        = hadd_mix_min_true_lg_res_x[gtrmid]->Integral(ibin_m_100, ibin_p_100);
    lgt_all_true[gtrmid] = hadd_mix_all_true_lg_res_x[gtrmid]->Integral(ibin_m_100, ibin_p_100);
    lgt_all_dum[gtrmid]  = hadd_mix_all_dum_lg_res_x[gtrmid] ->Integral(ibin_m_100, ibin_p_100);
    int all_dum_left_area   = hadd_mix_all_dum_lg_res_x[gtrmid]    ->Integral(ibin_min_ll, ibin_min_lh);
    int all_dum_right_area  = hadd_mix_all_dum_lg_res_x[gtrmid]    ->Integral(ibin_min_rl, ibin_min_rh);	
    int all_true_left_area  = hadd_mix_all_true_lg_res_x[gtrmid]   ->Integral(ibin_min_ll, ibin_min_lh);
    int all_true_right_area = hadd_mix_all_true_lg_res_x[gtrmid]   ->Integral(ibin_min_rl, ibin_min_rh);	
	lg_dum_all_ave[gtrmid]  = (double)(all_dum_left_area + all_dum_right_area)*0.5/(ibin_min_lh - ibin_min_ll +1); 
    lg_true_all_ave[gtrmid] = (double)(all_true_left_area + all_true_right_area)*0.5/(ibin_min_lh - ibin_min_ll +1); 
//  int lgt_s2 = h_mix_all_true_lg_res_x[6]->Integral(lgt_m_100, lgt_p_100);
//  std::cout <<"area of lg all true in range  = " <<  lgt_s2 << std::endl; 
//  std::cout <<"area of lg dum in range with directly mix  = " <<  h_mix_dum_lg_res_x[6]->Integral(lgt_m_100, lgt_p_100) << std::endl; 
//  std::cout <<"area of lg dum  in range  = " <<  lg_dum_ave*(lgt_m_100 - lgt_p_100 +1) << std::endl; 
//  std::cout <<"bg of lg all true in range  = " <<  lg_true_all_ave*(lgt_m_100 - lgt_p_100 +1) << std::endl; 
//  std::cout <<"bg of lg all dumm in range  = " <<  lg_dum_all_ave*(lgt_m_100 - lgt_p_100 +1) << std::endl; 

    std::cout <<"area of lg min true in range  = " <<  lgt_s[gtrmid] << std::endl; 
    std::cout <<"area of lg all true in range  = " <<  lgt_all_true[gtrmid] << std::endl; 
    std::cout <<"area of lg all dumm in range  = " <<  lgt_all_dum[gtrmid] << std::endl; 
    std::cout <<"bg of lg all true in range  = " <<  lg_true_all_ave[gtrmid]*(ibin_m_100 - ibin_p_100 +1) << std::endl; 
    std::cout <<"bg of lg all dumm in range  = " <<  lg_dum_all_ave[gtrmid] *(ibin_m_100 - ibin_p_100 +1) << std::endl; 
    double side_lg_true =  lg_true_all_ave[gtrmid]*(ibin_m_100 - ibin_p_100 +1); 
    double side_lg_dum  =  lg_dum_all_ave[gtrmid] *(ibin_m_100 - ibin_p_100 +1); 
    std::cout <<"lg bg of raitio  = " <<  (double)side_lg_true/side_lg_dum << std::endl; 
   double lgbg_ratio =  (double)side_lg_true/side_lg_dum;
    std::cout <<"lg n hit in range true + dum  = " <<  h_n_lg_hits_inrange[gtrmid]->Integral(2,10) << std::endl; 
    std::cout <<"lg n hit in range dum(scaled) = " <<  h_n_lg_dum_hits_inrange[gtrmid]->Integral(2,10) * lgbg_ratio  << std::endl; 
    
    hadd_mix_all_true_lg_res_x[gtrmid]->Write();
    hadd_mix_all_dum_lg_res_x[gtrmid]->Scale((double)(side_lg_true/side_lg_dum));
    hadd_mix_all_dum_lg_res_x[gtrmid]->SetLineColor(kRed);;
    hadd_mix_all_dum_lg_res_x[gtrmid]->Write();
}


int main(int argc, char* argv[]){
	auto in_file_name = argv[1];
	auto out_file_name = argv[2];
	int maxevent = stoi(argv[3]);
    int rm_size = stoi(argv[4]);//removed gtr size
	FILE *fp = fopen(in_file_name, "r");
	if(!fp){
		cerr << "could not open file : " << in_file_name << std::endl;
		return -1;
	}
	fclose(fp);
	auto in_chain = new TChain("tree", "tree");
	in_chain->Add(in_file_name);
	auto geom = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
	E16ANA_GeometryV2::SetGlobalPointer(geom);
    auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
	bfield_map->Initialize_binary();
	E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
	E16ANA_MultiTrack fitter(bfield_map, geom, 1);
	LayerEfficiencyCalculator *t = new LayerEfficiencyCalculator(out_file_name, in_chain, &fitter, maxevent, rm_size);
	t->Calculate();
    t->GetOutFile()->Write();
	delete in_chain;
	return 0;
}
