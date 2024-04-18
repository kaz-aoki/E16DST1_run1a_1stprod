//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr 13 21:25:45 2022 by ROOT version 5.34/01
// from TTree tree/tree
// found on file: out.root
//////////////////////////////////////////////////////////

#ifndef GTRResidualCalculator_h
#define GTRResidualCalculator_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TVector.h>
#include "E16ANA_MultiTrack.hh"
#include "SingleTrackAnalyzerForRes.hh"
#include "E16ANA_TrackConstant.hh"


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

const TVector3 zero_sigma = {0, 0, 0};
//const TVector3 kTargetSigma = {3., 3., 0.};
//const TVector3 kTargetSigma = {3., 3.4, 0.};
//const TVector3 kTargetSigma = {3., 3.4, 0.};
//const TVector3 kTargetSigma = {3., 3.4, 0.};//220518
//const TVector3 kTargetSigma = {1., 1.7, 0.};//220523
//const TVector3 kTargetSigma = {3, 3, 0.};//220523
const TVector3 kTargetSigma = {3, 3, 0.};//220523
//const TVector3 kDetectorSigma[4]  = {{0.1, 0, 0}, {0.3, 1, 0}, {0.3, 1, 0},{0.3, 1, 0} };
const TVector3 kDetectorSigma[4]  = {{0.075, 0, 0}, {0.27, 1, 0}, {0.27, 1, 0},{0.27, 1, 0} };
// Fixed size dimensions of array or collections stored in the TTree if any.

class GTRResidualCalculator {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           run_id;
   Int_t           event_id;
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

   vector<double>  *l_hit_ssd_x;
   vector<double>  *l_hit_gtr100_x;
   vector<double>  *l_hit_gtr100_y;
   vector<double>  *l_hit_gtr200_x;
   vector<double>  *l_hit_gtr200_y;
   vector<double>  *l_hit_gtr300_x;
   vector<double>  *l_hit_gtr300_y;
   vector<double>  *rk_hit_ssd_gx;
   vector<double>  *rk_hit_ssd_gy;
   vector<double>  *rk_hit_ssd_gz;
   vector<double>  *rk_hit_gtr100_gx;
   vector<double>  *rk_hit_gtr100_gy;
   vector<double>  *rk_hit_gtr100_gz;
   vector<double>  *rk_hit_gtr200_gx;
   vector<double>  *rk_hit_gtr200_gy;
   vector<double>  *rk_hit_gtr200_gz;
   vector<double>  *rk_hit_gtr300_gx;
   vector<double>  *rk_hit_gtr300_gy;
   vector<double>  *rk_hit_gtr300_gz;
   vector<double>  *rk_hit_gtr100_gtx;
   vector<double>  *rk_hit_gtr100_gtx2;
   vector<double>  *rk_hit_gtr100_gty;
   vector<double>  *rk_hit_gtr100_gtz;
   vector<double>  *rk_hit_gtr100_gtz2;
   vector<double>  *rk_hit_gtr200_gtx;
   vector<double>  *rk_hit_gtr200_gtx2;
   vector<double>  *rk_hit_gtr200_gty;
   vector<double>  *rk_hit_gtr200_gtz;
   vector<double>  *rk_hit_gtr300_gtx;
   vector<double>  *rk_hit_gtr200_gtz2;
   vector<double>  *rk_hit_gtr300_gtx2;
   vector<double>  *rk_hit_gtr300_gty;
   vector<double>  *rk_hit_gtr300_gtz2;
   vector<double>  *rk_hit_gtr300_gtz;
   vector<double>  *rk_res_ssd_x;
   vector<double>  *rk_res_gtr100_x;
   vector<double>  *rk_res_gtr100_y;
   vector<double>  *rk_res_gtr200_x;
   vector<double>  *rk_res_gtr200_y;
   vector<double>  *rk_res_gtr300_x;
   vector<double>  *rk_res_gtr300_y;
   vector<double>  *rk_res_gtr100_tx2;
   vector<double>  *rk_res_gtr100_ty;
   vector<double>  *rk_res_gtr200_tx2;
   vector<double>  *rk_res_gtr200_ty;
   vector<double>  *rk_res_gtr300_tx2;
   vector<double>  *rk_res_gtr300_ty;
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
   vector<int>     *rk_hit_ssd_id;
   vector<int>     *rk_hit_gtr100_xid;
   vector<int>     *rk_hit_gtr200_xid;
   vector<int>     *rk_hit_gtr300_xid;
   vector<int>     *rk_hit_gtr100_yid;
   vector<int>     *rk_hit_gtr200_yid;
   vector<int>     *rk_hit_gtr300_yid;
   vector<int>     *rk_fit_ssd_mid;
   vector<int>     *rk_fit_gtr100_mid;
   vector<int>     *rk_fit_gtr200_mid;
   vector<int>     *rk_fit_gtr300_mid;
   vector<double>  *rk_fit_gtr100_gx;
   vector<double>  *rk_fit_gtr200_gx;
   vector<double>  *rk_fit_gtr300_gx;
   vector<double>  *rk_fit_gtr100_gy;
   vector<double>  *rk_fit_gtr200_gy;
   vector<double>  *rk_fit_gtr300_gy;
   vector<double>  *rk_fit_gtr100_gz;
   vector<double>  *rk_fit_gtr200_gz;
   vector<double>  *rk_fit_gtr300_gz;
   vector<double>  *rk_fit_ssd_gx;
   vector<double>  *rk_fit_ssd_gy;
   vector<double>  *rk_fit_ssd_gz;
   vector<double>  *rk_fit_init_pos_gx;
   vector<double>  *rk_fit_init_pos_gy;
   vector<double>  *rk_fit_init_pos_gz;

   
   
   // List of branches
   TBranch        *b_run_id;   //!
   TBranch        *b_event_id;   //!
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
   TBranch        *b_rk_hit_ssd_gx;   //!
   TBranch        *b_rk_hit_ssd_gy;   //!
   TBranch        *b_rk_hit_ssd_gz;   //!
   TBranch        *b_rk_hit_gtr100_gx;   //!
   TBranch        *b_rk_hit_gtr100_gy;   //!
   TBranch        *b_rk_hit_gtr100_gz;   //!
   TBranch        *b_rk_hit_gtr200_gx;   //!
   TBranch        *b_rk_hit_gtr200_gy;   //!
   TBranch        *b_rk_hit_gtr200_gz;   //!
   TBranch        *b_rk_hit_gtr300_gx;   //!
   TBranch        *b_rk_hit_gtr300_gy;   //!
   TBranch        *b_rk_hit_gtr300_gz;   //!
   TBranch        *b_rk_hit_gtr100_gtx;   //!
   TBranch        *b_rk_hit_gtr100_gty;   //!
   TBranch        *b_rk_hit_gtr200_gty;   //!
   TBranch        *b_rk_hit_gtr300_gty;   //!
   TBranch        *b_rk_hit_gtr100_gtz;   //!
   TBranch        *b_rk_hit_gtr200_gtx;   //!
   TBranch        *b_rk_hit_gtr200_gtz;   //!
   TBranch        *b_rk_hit_gtr300_gtx;   //!
   TBranch        *b_rk_hit_gtr300_gtz;   //!
   TBranch        *b_rk_hit_gtr100_gtx2;   //!
   TBranch        *b_rk_hit_gtr100_gtz2;   //!
   TBranch        *b_rk_hit_gtr200_gtx2;   //!
   TBranch        *b_rk_hit_gtr200_gtz2;   //!
   TBranch        *b_rk_hit_gtr300_gtx2;   //!
   TBranch        *b_rk_hit_gtr300_gtz2;   //!
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
   TBranch        *b_rk_hit_ssd_id;
   TBranch        *b_rk_hit_gtr100_xid;
   TBranch        *b_rk_hit_gtr200_xid;
   TBranch        *b_rk_hit_gtr300_xid;
   TBranch        *b_rk_hit_gtr100_yid;
   TBranch        *b_rk_hit_gtr200_yid;
   TBranch        *b_rk_hit_gtr300_yid;
   TBranch        *b_rk_res_ssd_x;
   TBranch        *b_rk_res_gtr100_x;
   TBranch        *b_rk_res_gtr100_y;
   TBranch        *b_rk_res_gtr200_x;

   TBranch        *b_rk_res_gtr200_y;
   TBranch        *b_rk_res_gtr300_x;
   TBranch        *b_rk_res_gtr300_y;
   TBranch        *b_rk_res_gtr100_tx2;
   TBranch        *b_rk_res_gtr100_ty;
   TBranch        *b_rk_res_gtr200_tx2;
   TBranch        *b_rk_res_gtr200_ty;
   TBranch        *b_rk_res_gtr300_tx2;
   TBranch        *b_rk_res_gtr300_ty;
   TBranch        *b_rk_fit_gtr100_gx;
   TBranch        *b_rk_fit_gtr100_gy;
   TBranch        *b_rk_fit_gtr100_gz;
   TBranch        *b_rk_fit_gtr200_gx;
   TBranch        *b_rk_fit_gtr200_gy;
   TBranch        *b_rk_fit_gtr200_gz;
   TBranch        *b_rk_fit_gtr300_gx;
   TBranch        *b_rk_fit_gtr300_gy;
   TBranch        *b_rk_fit_gtr300_gz;
   TBranch        *b_rk_fit_ssd_gx;
   TBranch        *b_rk_fit_ssd_gy;
   TBranch        *b_rk_fit_ssd_gz;
   TBranch        *b_rk_fit_init_pos_gx;
   TBranch        *b_rk_fit_init_pos_gy;
   TBranch        *b_rk_fit_init_pos_gz;

//for out tree
   TTree *out_tree;
   TFile *out_file;

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
   double pre_chi_square;
   double post_chi_square;
   double post_3l_chi_square[4];
   double post_detector_lx[out_n_layer];
   double post_detector_ly[out_n_layer];
   double post_detector_res_x[out_n_layer];//detector resolution fit with 4 layers
   double post_detector_res_y[out_n_layer];
   double post_detector_res_z[out_n_layer];
   double post_3l_detector_res_x[out_n_layer][out_n_layer];//detector resolution fit with 3 layer
   double post_3l_detector_res_y[out_n_layer][out_n_layer];
   double post_wo_tgt_detector_res_x[out_n_layer];
   double post_wo_tgt_detector_res_y[out_n_layer];
   double post_wo_tgt_chi_square;
   double post_wo_tgt_fit_tgtpj_x;//tgt
   double post_wo_tgt_fit_tgtpj_y;//tgt
   double post_wo_tgt_fit_tgtpj_z;//tgt
   double lg_t;
   double ssd_t;
   double pre_detector_res_x[out_n_layer];
   double pre_detector_res_y[out_n_layer];
   double pre_detector_res_z[out_n_layer];
   double post_fit_tgtpj_x;//tgt
   double post_fit_tgtpj_y;//tgt
   double post_fit_tgtpj_z;//tgt

   double chi2_tgtpos[20][20];
 

   TH1D *h_chi2_tgtpos[20][20];
   // Set branch addresses and branch pointers
   //if (!tree) return;
   E16ANA_MultiTrack *fitter;
   GTRResidualCalculator(char* out_file_name, TChain *chain, E16ANA_MultiTrack *_fitter, int maxevent);
   GTRResidualCalculator(TTree *tree, E16ANA_MultiTrack *_fitter, int maxevent);
   virtual ~GTRResidualCalculator();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   //virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   std::vector<int> selected_track_indexs;
   void Calculate();
   bool isTimingMatchSSDAndLG(int track_id, vector<int> &lg_hit_id);
   void CheckUsedClusters(int track_index, std::array<std::vector<int>, track_const::kNumTrackingLayers>* used_cluster_ids);
   void RKAnalyze(E16ANA_MultiTrack *fitter);
   void RKAnalyzeForTgtCalib(E16ANA_MultiTrack *fitter);
   void SelectTrack(int track_index, std::array<std::vector<int>,track_const::kNumTrackingLayers> *used_cluster_ids);
   void SelectTracks();
   TFile* GetOutFile(){return out_file;}
private:
   int maxevent;
   vector<vector<int>> matched_lghit_ids;
};

#endif


GTRResidualCalculator::GTRResidualCalculator(char* out_file_name, TChain *chain, E16ANA_MultiTrack *_fitter, int _maxevent)
 : fChain(0) , fitter(_fitter), maxevent(_maxevent)
{
//   out_file = new TFile("./dst1ana_out/outgtr_test.root", "recreate");
   out_file = new TFile(out_file_name, "recreate" );
   out_tree = new TTree("tree", "tree");
   out_tree->Branch("module_id", &module_id, "module_id[6]/I");
   out_tree->Branch("trk_charge", &trk_charge, "trk_charge/I");
   out_tree->Branch("pre_chi_square", &pre_chi_square, "pre_chi_square/D");
   out_tree->Branch("post_chi_square", &post_chi_square, "post_chi_square/D");
   out_tree->Branch("post_3l_chi_square", &post_3l_chi_square, "post_3l_chi_square[4]/D");
   out_tree->Branch("post_detector_lx", &post_detector_lx, "post_detector_lx[6]/D");
   out_tree->Branch("post_detector_res_x", &post_detector_res_x, "post_detector_res_x[6]/D");
   out_tree->Branch("post_3l_detector_res_x", &post_3l_detector_res_x, "post_3l_detector_res_x[6][6]/D");
   out_tree->Branch("post_detector_ly", &post_detector_ly, "post_detector_ly[6]/D");
   out_tree->Branch("post_detector_res_y", &post_detector_res_y, "post_detector_res_y[6]/D");
   out_tree->Branch("post_detector_res_z", &post_detector_res_z, "post_detector_res_z[6]/D");
   out_tree->Branch("post_3l_detector_res_y", &post_3l_detector_res_y, "post_3l_detector_res_y[6][6]/D");
   out_tree->Branch("pre_detector_res_x", &pre_detector_res_x, "pre_detector_res_x[6]/D");
   out_tree->Branch("pre_detector_res_y", &pre_detector_res_y, "pre_detector_res_y[6]/D");
   out_tree->Branch("pre_detector_res_z", &pre_detector_res_z, "pre_detector_res_z[6]/D");
   out_tree->Branch("post_wo_tgt_detector_res_x", &post_wo_tgt_detector_res_x, "post_wo_tgt_detector_res_x[6]/D");
   out_tree->Branch("post_wo_tgt_detector_res_y", &post_wo_tgt_detector_res_y, "post_wo_tgt_detector_res_y[6]/D");
   out_tree->Branch("post_wo_tgt_fit_tgtpj_x", &post_wo_tgt_fit_tgtpj_x, "post_wo_tgt_fit_tgtpj_x/D");
   out_tree->Branch("post_wo_tgt_fit_tgtpj_y", &post_wo_tgt_fit_tgtpj_y, "post_wo_tgt_fit_tgtpj_y/D");
   out_tree->Branch("post_wo_tgt_fit_tgtpj_z", &post_wo_tgt_fit_tgtpj_z, "post_wo_tgt_fit_tgtpj_z/D");
   out_tree->Branch("post_fit_tgtpj_x", &post_fit_tgtpj_x, "post_fit_tgtpj_x/D");
   out_tree->Branch("post_fit_tgtpj_y", &post_fit_tgtpj_y, "post_fit_tgtpj_y/D");
   out_tree->Branch("post_fit_tgtpj_z", &post_fit_tgtpj_z, "post_fit_tgtpj_z/D");
   out_tree->Branch("lg_t", &lg_t, "lg_t/D");
   out_tree->Branch("ssd_t", &ssd_t, "ssd_t/D");
   out_tree->Branch("chi2_tgtpos", &chi2_tgtpos, "chi2_tgtpos[20][20]/D");
   Init(dynamic_cast<TTree*>(chain));
    for(int i = 0; i < 20; i++){
    for(int j = 0; j < 20; j++){
	h_chi2_tgtpos[i][j] = new TH1D(Form("h_chi2_tgtpos_%d_%d", i, j), Form("h_chi2_tgtpos_%d_%d", i, j), 400,0, 100);
	}
	}
}
GTRResidualCalculator::GTRResidualCalculator(TTree *tree, E16ANA_MultiTrack *_fitter, int _maxevent)
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

GTRResidualCalculator::~GTRResidualCalculator()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}
Int_t GTRResidualCalculator::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t GTRResidualCalculator::LoadTree(Long64_t entry)
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

void GTRResidualCalculator::Init(TTree *tree)
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
   rk_hit_ssd_gx = 0;
   rk_hit_ssd_gy = 0;
   rk_hit_ssd_gz = 0;
   rk_hit_gtr100_gx = 0;
   rk_hit_gtr100_gy = 0;
   rk_hit_gtr100_gz = 0;
   rk_hit_gtr200_gx = 0;
   rk_hit_gtr200_gy = 0;
   rk_hit_gtr200_gz = 0;
   rk_hit_gtr300_gx = 0;
   rk_hit_gtr300_gy = 0;
   rk_hit_gtr300_gz = 0;
   rk_hit_gtr100_gtx = 0;
   rk_hit_gtr100_gtx2 = 0;
   rk_hit_gtr200_gtx = 0;
   rk_hit_gtr200_gtx2 = 0;
   rk_hit_gtr300_gtx = 0;
   rk_hit_gtr300_gtx2 = 0;
   rk_hit_gtr100_gtz = 0;
   rk_hit_gtr100_gtz2 = 0;
   rk_hit_gtr200_gtz = 0;
   rk_hit_gtr200_gtz2 = 0;
   rk_hit_gtr300_gtz = 0;
   rk_hit_gtr300_gtz2 = 0;
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
   rk_res_gtr100_tx2 = 0;
   rk_res_gtr100_ty = 0;
   rk_res_gtr200_tx2 = 0;
   rk_res_gtr200_ty = 0;
   rk_res_gtr300_tx2 = 0;
   rk_res_gtr300_ty = 0;
   rk_fit_ssd_gx = 0;
   rk_fit_ssd_gy = 0;
   rk_fit_ssd_gz = 0;
   rk_fit_gtr100_gx = 0;
   rk_fit_gtr100_gy = 0;
   rk_fit_gtr100_gz = 0;
   rk_fit_gtr200_gx = 0;
   rk_fit_gtr200_gy = 0;
   rk_fit_gtr200_gz = 0;
   rk_fit_gtr300_gx = 0;
   rk_fit_gtr300_gy = 0;
   rk_fit_gtr300_gz = 0;
   rk_fit_init_pos_gx = 0;
   rk_fit_init_pos_gy = 0;
   rk_fit_init_pos_gz = 0;

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run_id", &run_id, &b_run_id);
   fChain->SetBranchAddress("event_id", &event_id, &b_event_id);
   fChain->SetBranchAddress("spill_id", &spill_id, &b_spill_id);
   fChain->SetBranchAddress("n_tracks", &n_tracks, &b_n_tracks);
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
   fChain->SetBranchAddress("rk_hit_ssd_gx", &rk_hit_ssd_gx, &b_rk_hit_ssd_gx);
   fChain->SetBranchAddress("rk_hit_ssd_gy", &rk_hit_ssd_gy, &b_rk_hit_ssd_gy);
   fChain->SetBranchAddress("rk_hit_ssd_gz", &rk_hit_ssd_gz, &b_rk_hit_ssd_gz);
   fChain->SetBranchAddress("rk_hit_gtr100_gx", &rk_hit_gtr100_gx, &b_rk_hit_gtr100_gx);
   fChain->SetBranchAddress("rk_hit_gtr100_gy", &rk_hit_gtr100_gy, &b_rk_hit_gtr100_gy);
   fChain->SetBranchAddress("rk_hit_gtr100_gz", &rk_hit_gtr100_gz, &b_rk_hit_gtr100_gz);
   fChain->SetBranchAddress("rk_hit_gtr200_gx", &rk_hit_gtr200_gx, &b_rk_hit_gtr200_gx);
   fChain->SetBranchAddress("rk_hit_gtr200_gy", &rk_hit_gtr200_gy, &b_rk_hit_gtr200_gy);
   fChain->SetBranchAddress("rk_hit_gtr200_gz", &rk_hit_gtr200_gz, &b_rk_hit_gtr200_gz);
   fChain->SetBranchAddress("rk_hit_gtr300_gx", &rk_hit_gtr300_gx, &b_rk_hit_gtr300_gx);
   fChain->SetBranchAddress("rk_hit_gtr300_gy", &rk_hit_gtr300_gy, &b_rk_hit_gtr300_gy);
   fChain->SetBranchAddress("rk_hit_gtr300_gz", &rk_hit_gtr300_gz, &b_rk_hit_gtr300_gz);
   fChain->SetBranchAddress("rk_hit_gtr100_gtx", &rk_hit_gtr100_gtx, &b_rk_hit_gtr100_gtx);
   fChain->SetBranchAddress("rk_hit_gtr100_gty", &rk_hit_gtr100_gty, &b_rk_hit_gtr100_gty);
   fChain->SetBranchAddress("rk_hit_gtr200_gty", &rk_hit_gtr200_gty, &b_rk_hit_gtr200_gty);
   fChain->SetBranchAddress("rk_hit_gtr300_gty", &rk_hit_gtr300_gty, &b_rk_hit_gtr300_gty);
   fChain->SetBranchAddress("rk_hit_gtr100_gtx2", &rk_hit_gtr100_gtx2, &b_rk_hit_gtr100_gtx2);
   fChain->SetBranchAddress("rk_hit_gtr100_gtz2", &rk_hit_gtr100_gtz2, &b_rk_hit_gtr100_gtz2);
   fChain->SetBranchAddress("rk_hit_gtr200_gtz2", &rk_hit_gtr200_gtz2, &b_rk_hit_gtr200_gtz2);
   fChain->SetBranchAddress("rk_hit_gtr300_gtz2", &rk_hit_gtr300_gtz2, &b_rk_hit_gtr300_gtz2);
   fChain->SetBranchAddress("rk_hit_gtr200_gtx", &rk_hit_gtr200_gtx, &b_rk_hit_gtr200_gtx);
   fChain->SetBranchAddress("rk_hit_gtr200_gtx2", &rk_hit_gtr200_gtx2, &b_rk_hit_gtr200_gtx2);
   fChain->SetBranchAddress("rk_hit_gtr300_gtx", &rk_hit_gtr300_gtx, &b_rk_hit_gtr300_gtx);
   fChain->SetBranchAddress("rk_hit_gtr300_gtx2", &rk_hit_gtr300_gtx2, &b_rk_hit_gtr300_gtx2);
   fChain->SetBranchAddress("rk_res_ssd_x", &rk_res_ssd_x, &b_rk_res_ssd_x);
   fChain->SetBranchAddress("rk_res_gtr100_x", &rk_res_gtr100_x, &b_rk_res_gtr100_x);
   fChain->SetBranchAddress("rk_res_gtr200_x", &rk_res_gtr200_x, &b_rk_res_gtr200_x);
   fChain->SetBranchAddress("rk_res_gtr300_x", &rk_res_gtr300_x, &b_rk_res_gtr300_x);
   fChain->SetBranchAddress("rk_res_gtr100_y", &rk_res_gtr100_y, &b_rk_res_gtr100_y);
   fChain->SetBranchAddress("rk_res_gtr200_y", &rk_res_gtr200_y, &b_rk_res_gtr200_y);
   fChain->SetBranchAddress("rk_res_gtr300_y", &rk_res_gtr300_y, &b_rk_res_gtr300_y);
   fChain->SetBranchAddress("rk_res_gtr100_tx2", &rk_res_gtr100_tx2, &b_rk_res_gtr100_tx2);
   fChain->SetBranchAddress("rk_res_gtr200_tx2", &rk_res_gtr200_tx2, &b_rk_res_gtr200_tx2);
   fChain->SetBranchAddress("rk_res_gtr300_tx2", &rk_res_gtr300_tx2, &b_rk_res_gtr300_tx2);
   fChain->SetBranchAddress("rk_res_gtr100_ty", &rk_res_gtr100_ty, &b_rk_res_gtr100_ty);
   fChain->SetBranchAddress("rk_res_gtr200_ty", &rk_res_gtr200_ty, &b_rk_res_gtr200_ty);
   fChain->SetBranchAddress("rk_res_gtr300_ty", &rk_res_gtr300_ty, &b_rk_res_gtr300_ty);
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
   fChain->SetBranchAddress("rk_fit_ssd_gx", &rk_fit_ssd_gx, &b_rk_fit_ssd_gx);
   fChain->SetBranchAddress("rk_fit_ssd_gy", &rk_fit_ssd_gy, &b_rk_fit_ssd_gy);
   fChain->SetBranchAddress("rk_fit_ssd_gz", &rk_fit_ssd_gz, &b_rk_fit_ssd_gz);
   fChain->SetBranchAddress("rk_fit_gtr100_gx", &rk_fit_gtr100_gx, &b_rk_fit_gtr100_gx);
   fChain->SetBranchAddress("rk_fit_gtr100_gy", &rk_fit_gtr100_gy, &b_rk_fit_gtr100_gy);
   fChain->SetBranchAddress("rk_fit_gtr100_gz", &rk_fit_gtr100_gz, &b_rk_fit_gtr100_gz);
   fChain->SetBranchAddress("rk_fit_gtr200_gx", &rk_fit_gtr200_gx, &b_rk_fit_gtr200_gx);
   fChain->SetBranchAddress("rk_fit_gtr200_gy", &rk_fit_gtr200_gy, &b_rk_fit_gtr200_gy);
   fChain->SetBranchAddress("rk_fit_gtr200_gz", &rk_fit_gtr200_gz, &b_rk_fit_gtr200_gz);
   fChain->SetBranchAddress("rk_fit_gtr300_gx", &rk_fit_gtr300_gx, &b_rk_fit_gtr300_gx);
   fChain->SetBranchAddress("rk_fit_gtr300_gy", &rk_fit_gtr300_gy, &b_rk_fit_gtr300_gy);
   fChain->SetBranchAddress("rk_fit_gtr300_gz", &rk_fit_gtr300_gz, &b_rk_fit_gtr300_gz);
   fChain->SetBranchAddress("rk_fit_init_pos_gx", &rk_fit_init_pos_gx, &b_rk_fit_init_pos_gx);
   fChain->SetBranchAddress("rk_fit_init_pos_gy", &rk_fit_init_pos_gy, &b_rk_fit_init_pos_gy);
   fChain->SetBranchAddress("rk_fit_init_pos_gz", &rk_fit_init_pos_gz, &b_rk_fit_init_pos_gz);
   Notify();
}

Bool_t GTRResidualCalculator::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void GTRResidualCalculator::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t GTRResidualCalculator::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}



//#include "GTRResidualCalculator.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


void GTRResidualCalculator::CheckUsedClusters(int track_index, 
	std::array<std::vector<int>, track_const::kNumTrackingLayers> * used_cluster_ids){
	int ids[7] = {track_ssd_cluster_id->at(track_index), 
				  track_gtr100x_cluster_id->at(track_index), track_gtr100y_cluster_id->at(track_index),
				  track_gtr200x_cluster_id->at(track_index), track_gtr200y_cluster_id->at(track_index),
				  track_gtr300x_cluster_id->at(track_index), track_gtr300y_cluster_id->at(track_index)};
	for (const auto &id : used_cluster_ids->at(0)){
		if(id == ids[0]){
			return;
		}
	}
	for (const auto &id : used_cluster_ids->at(1)){
		if(id == ids[1] || id == ids[2]){
			return;
		}
	}
	for (const auto &id : used_cluster_ids->at(2)){
		if(id == ids[3] || id == ids[4]){
			return;
		}
	}
	for (const auto &id : used_cluster_ids->at(3)){
		if(id == ids[5] || id == ids[6]){
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

void GTRResidualCalculator::SelectTrack(int track_index, std::array<std::vector<int>, track_const::kNumTrackingLayers> *used_cluster_ids){
	CheckUsedClusters(track_index, used_cluster_ids);
}


void GTRResidualCalculator::SelectTracks(){
	std::array<std::vector<int> , track_const::kNumTrackingLayers> used_cluster_ids;
	matched_lghit_ids.resize(n_tracks);
	matched_lghit_ids.clear();
	for(int i = 0; i < n_tracks; i++){
		if(isTimingMatchSSDAndLG(i, matched_lghit_ids[i])){
    		SelectTrack(i,  &used_cluster_ids);	
		}
	}	
}

bool GTRResidualCalculator::isTimingMatchSSDAndLG(int track_id, vector<int> &matched_lghit_id){
	bool flag = false;
	matched_lghit_id.clear();
//	std::cout << "ssd timing = " << track_ssd_t->at(track_id) << std::endl;
	auto ftimes = track_lg_allhit_ftime->at(track_id);
	double st = track_ssd_t->at(track_id);
	for(int i=0; i< ftimes.size(); i++){
		double lg_t = ftimes.at(i);
		if(-11 < lg_t - st - 51 < 11){//taught by nakasuga
			flag = true;
			matched_lghit_id.push_back(i);
		}
	}
	return flag;
}

void GTRResidualCalculator::RKAnalyzeForTgtCalib(E16ANA_MultiTrack *fitter){
	double tgt_zs[3] = {-20., 0., 20.};
	E16ANA_GeometryV2 *geometry = E16ANA_GeometryV2::GlobalPointer();
	for(int i = 0; i < selected_track_indexs.size(); i++){
		int tid = selected_track_indexs[i];
		TVector3 moms = TVector3(track_mom_x->at(tid), track_mom_y->at(tid), track_mom_z->at(tid));
		int mids[6] = {track_ssd_cluster_mid->at(tid) , track_gtr100_cluster_mid->at(tid), track_gtr200_cluster_mid->at(tid), track_gtr300_cluster_mid->at(tid), track_hbd_mid->at(tid), track_lg_mid->at(tid)};
		for(int l = 0; l < 4; l++){
//			std::cout << "m id = " << mids[l] << std::endl;
		}
		TVector3 hit_gpos[track_const::kNumTrackingLayers];
		TVector3 hit_lpos[track_const::kNumTrackingLayers];
		hit_gpos[0] = TVector3(rk_hit_ssd_gx->at(tid), rk_hit_ssd_gy->at(tid), rk_hit_ssd_gz->at(tid));
		//std::cout << "global " << rk_hit_ssd_gx->at(tid) << ", " <<  rk_hit_ssd_gy->at(tid) << ", " <<  rk_hit_ssd_gz->at(tid) <<std::endl;
		//hit_gpos[0] = TVector3(- 65.66, 0, 132);
		hit_gpos[1] = TVector3(rk_hit_gtr100_gtx2->at(tid), rk_hit_gtr100_gty->at(tid), rk_hit_gtr100_gtz2->at(tid));
		hit_gpos[2] = TVector3(rk_hit_gtr200_gtx2->at(tid), rk_hit_gtr200_gty->at(tid), rk_hit_gtr200_gtz2->at(tid));
		hit_gpos[3] = TVector3(rk_hit_gtr300_gtx2->at(tid), rk_hit_gtr300_gty->at(tid), rk_hit_gtr300_gtz2->at(tid));
		for(int l = 0; l < 4; l++){
		if(l == 0 ) {
			hit_lpos[0] =  geometry->SSD(track_const::ModuleID2020To2013(mids[l]))->GetLPos(hit_gpos[0]);
			TVector3 tmp1 =  geometry->SSD(track_const::ModuleID2020To2013(mids[l] -1))->GetLPos(hit_gpos[0]);
			TVector3 tmp2 =  geometry->SSD(track_const::ModuleID2020To2013(mids[l] +1))->GetLPos(hit_gpos[0]);
//			std::cout << hit_lpos[0].X() << ", " << hit_lpos[0].Y() << ", " << hit_lpos[0].Z() << std::endl;
//			std::cout << tmp1.X() << ", " << tmp1.Y() << ", " << tmp1.Z() << std::endl;
//			std::cout << tmp2.X() << ", " << tmp2.Y() << ", " << tmp2.Z() << std::endl;
			//hit_lpos[0] = TVector3(0, 0, 0);
		}
		else if(l != 0 ) {
			hit_lpos[l] = geometry->GTR(track_const::ModuleID2020To2013(mids[l]), l- 1)->GetLPos(hit_gpos[l]);
		}
	//	std::cout << "before lpos = (" << hit_lpos[l].X() << ", " 
	//	<< hit_lpos[l].Y() << ", " 
	  //  << hit_lpos[l].Z() << ")" << std::endl;
		}
		std::cout << "pre     chi2 = " << chi_square->at(tid) << std::endl;
//		int removed_layer = -1;
		int charge = rk_charge->at(tid);
// ---- fit 4 layers ------------------------------------- //
	    std::vector<double> chi2_4layers_list;
	    chi2_4layers_list.clear();
	    double tmp_post_detector_lx[3][4];//[tgt_i][layer]
		double tmp_post_detector_ly[3][4];
	    double tmp_post_detector_res_x[3][4];//[tgt_i][layer]
		double tmp_post_detector_res_y[3][4];
		double tmp_post_detector_res_z[3][4];
		double tmp_post_fit_tgtpj_x[3];
		double tmp_post_fit_tgtpj_y[3];
		double tmp_post_fit_tgtpj_z[3];
		for(int tgt_i = 0; tgt_i < 3; tgt_i++){//identify which tgt from
			fitter->Clear();
			fitter->SetInitialVertex(TVector3(0.,0., tgt_zs[tgt_i]), kTargetSigma);
			fitter->SetCharge(0, charge);//first argument is n of track (now, single )
   //         std::cout << "moms = " << moms.X() 
	//		<< ", " << moms.Y()
	//		<< ", " << moms.Z() << std::endl;
 		 
			fitter->SetInitialMomentum(0, moms);
	    	for(int l=0; l < 4; l++){
				auto mid2013 = track_const::ModuleID2020To2013(mids[l]);
				if( l == 0) {
					fitter->AddHit(0, l, geometry->SSD(mid2013), hit_lpos[l], kDetectorSigma[l]);
				}else{ // l!=0
					fitter->AddHit(0, l, geometry->GTR(mid2013, l-1 ), hit_lpos[l], kDetectorSigma[l]);
				}
			}
			fitter->SetRungeKuttaStepSize(kStepSize);
			fitter->SetMaxSteps(kMaxSteps);
			std::vector<std::vector<int>> tmp_mid;//module id
			std::vector<std::vector<TVector3>> tmp_lpos;
			std::vector<std::vector<TVector3>> tmp_lres;
			tmp_mid.resize(3);
			tmp_lpos.resize(3);
			tmp_lres.resize(3);
			tmp_mid.clear();
			tmp_lpos.clear();
			tmp_lres.clear();
			for(int k=0; k < 3; k++){
				tmp_mid[k].clear();
				tmp_lpos[k].clear();
				tmp_lres[k].clear();
			}
			double chi2_4layers = fitter->Fit(false, false, true, kMinuitStrategy, kMaxFunctionCalls);
//			std::cout << "chi2  = " << chi2_4layers << std::endl;
			chi2_4layers_list.push_back(chi2_4layers);
			for(int l=0; l < 4; l++){
				fitter->GetFitLPos(0, l, tmp_mid[tgt_i], tmp_lpos[tgt_i]);//1st arg : trk id
				fitter->GetFitResidual(0, l, tmp_mid[tgt_i], tmp_lres[tgt_i]);
				tmp_post_detector_lx[tgt_i][l] = tmp_lpos[tgt_i][0].X();
				tmp_post_detector_ly[tgt_i][l] = tmp_lpos[tgt_i][0].Y();
				tmp_post_detector_res_x[tgt_i][l] = tmp_lres[tgt_i][0].X();
				tmp_post_detector_res_y[tgt_i][l] = tmp_lres[tgt_i][0].Y();
				tmp_post_detector_res_z[tgt_i][l] = tmp_lres[tgt_i][0].Z();
			}
            tmp_post_fit_tgtpj_x[tgt_i] = fitter->GetFitVertex().X();
            tmp_post_fit_tgtpj_y[tgt_i] = fitter->GetFitVertex().Y();
            tmp_post_fit_tgtpj_z[tgt_i] = fitter->GetFitVertex().Z();
		}//tgt_i loop
// select best tgt
		std::vector<double>::iterator iter = std::min_element(chi2_4layers_list.begin(), chi2_4layers_list.end());
		int min_id = std::distance(chi2_4layers_list.begin(), iter);
		std::cout << " min id = " << min_id << std::endl;
		std::cout << "first chi2 = " << *iter << std::endl;

// --- // 


// ---- change tgt pos 
		for(int i = 0; i< 10; i++){
		for(int j = 0; j< 10; j++){
			fitter->Clear();
            double x = -0.5 + i*0.1;
            double y = -0.5 + j*0.1;
			fitter->SetInitialVertex(TVector3(x, y, tgt_zs[min_id]), kTargetSigma);//move x
			fitter->SetCharge(0, charge);//first argument is n of track (now, single )
			fitter->SetInitialMomentum(0, moms);
	    	for(int l=0; l < 4; l++){
				auto mid2013 = track_const::ModuleID2020To2013(mids[l]);
				if( l == 0) {
					fitter->AddHit(0, l, geometry->SSD(mid2013), hit_lpos[l], kDetectorSigma[l]);
				}else{ // l!=0
					fitter->AddHit(0, l, geometry->GTR(mid2013, l-1 ), hit_lpos[l], kDetectorSigma[l]);
				}
			}
			fitter->SetRungeKuttaStepSize(kStepSize);
			fitter->SetMaxSteps(kMaxSteps);
			double chi2 = fitter->Fit(true, false, true, kMinuitStrategy, kMaxFunctionCalls);
			//std::cout << "i, chi2 =  " << i << ", " << chi2 << std::endl;
			h_chi2_tgtpos[i][j]->Fill(chi2);
            chi2_tgtpos[i][j] = chi2;
			}
		}
        out_tree->Fill();
	}
}



void GTRResidualCalculator::RKAnalyze(E16ANA_MultiTrack *fitter){
	std::cout << "Event ID  == " << event_id << std::endl;
	double tgt_zs[3] = {-20., 0., 20.};
	E16ANA_GeometryV2 *geometry = E16ANA_GeometryV2::GlobalPointer();
	for(int i = 0; i < selected_track_indexs.size(); i++){
		int tid = selected_track_indexs[i];
		TVector3 moms = TVector3(track_mom_x->at(tid), track_mom_y->at(tid), track_mom_z->at(tid));
		int mids[6] = {track_ssd_cluster_mid->at(tid) , track_gtr100_cluster_mid->at(tid), track_gtr200_cluster_mid->at(tid), track_gtr300_cluster_mid->at(tid), track_hbd_mid->at(tid), track_lg_mid->at(tid)};
		for(int l = 0; l < 4; l++){
//			std::cout << "m id = " << mids[l] << std::endl;
		}
		TVector3 hit_gpos[track_const::kNumTrackingLayers];
		TVector3 hit_lpos[track_const::kNumTrackingLayers];
		hit_gpos[0] = TVector3(rk_hit_ssd_gx->at(tid), rk_hit_ssd_gy->at(tid), rk_hit_ssd_gz->at(tid));
		//std::cout << "global " << rk_hit_ssd_gx->at(tid) << ", " <<  rk_hit_ssd_gy->at(tid) << ", " <<  rk_hit_ssd_gz->at(tid) <<std::endl;
		//hit_gpos[0] = TVector3(- 65.66, 0, 132);
		hit_gpos[1] = TVector3(rk_hit_gtr100_gtx2->at(tid), rk_hit_gtr100_gty->at(tid), rk_hit_gtr100_gtz2->at(tid));
		hit_gpos[2] = TVector3(rk_hit_gtr200_gtx2->at(tid), rk_hit_gtr200_gty->at(tid), rk_hit_gtr200_gtz2->at(tid));
		hit_gpos[3] = TVector3(rk_hit_gtr300_gtx2->at(tid), rk_hit_gtr300_gty->at(tid), rk_hit_gtr300_gtz2->at(tid));
		for(int l = 0; l < 4; l++){
		if(l == 0 ) {
			hit_lpos[0] =  geometry->SSD(track_const::ModuleID2020To2013(mids[l]))->GetLPos(hit_gpos[0]);
			TVector3 tmp1 =  geometry->SSD(track_const::ModuleID2020To2013(mids[l] -1))->GetLPos(hit_gpos[0]);
			TVector3 tmp2 =  geometry->SSD(track_const::ModuleID2020To2013(mids[l] +1))->GetLPos(hit_gpos[0]);
//			std::cout << hit_lpos[0].X() << ", " << hit_lpos[0].Y() << ", " << hit_lpos[0].Z() << std::endl;
//			std::cout << tmp1.X() << ", " << tmp1.Y() << ", " << tmp1.Z() << std::endl;
//			std::cout << tmp2.X() << ", " << tmp2.Y() << ", " << tmp2.Z() << std::endl;
			//hit_lpos[0] = TVector3(0, 0, 0);
		}
		else if(l != 0 ) {
			hit_lpos[l] = geometry->GTR(track_const::ModuleID2020To2013(mids[l]), l- 1)->GetLPos(hit_gpos[l]);
		}
	//	std::cout << "before lpos = (" << hit_lpos[l].X() << ", " 
	//	<< hit_lpos[l].Y() << ", " 
	  //  << hit_lpos[l].Z() << ")" << std::endl;
		}
		std::cout << "pre     chi2 = " << chi_square->at(tid) << std::endl;
//		int removed_layer = -1;
		int charge = rk_charge->at(tid);

// ---- fit 4 layers ------------------------------------- //
	    std::vector<double> chi2_4layers_list;
	    chi2_4layers_list.clear();
	    double tmp_post_detector_lx[3][4];//[tgt_i][layer]
		double tmp_post_detector_ly[3][4];
	    double tmp_post_detector_res_x[3][4];//[tgt_i][layer]
		double tmp_post_detector_res_y[3][4];
		double tmp_post_detector_res_z[3][4];
		double tmp_post_fit_tgtpj_x[3];
		double tmp_post_fit_tgtpj_y[3];
		double tmp_post_fit_tgtpj_z[3];
		for(int tgt_i = 0; tgt_i < 3; tgt_i++){//identify which tgt from
			fitter->Clear();
			fitter->SetInitialVertex(TVector3(0.48,0.21, tgt_zs[tgt_i]), kTargetSigma);
			fitter->SetCharge(0, charge);//first argument is n of track (now, single )
   //         std::cout << "moms = " << moms.X() 
	//		<< ", " << moms.Y()
	//		<< ", " << moms.Z() << std::endl;
 		 
			fitter->SetInitialMomentum(0, moms);
	    	for(int l=0; l < 4; l++){
				auto mid2013 = track_const::ModuleID2020To2013(mids[l]);
				if( l == 0) {
					fitter->AddHit(0, l, geometry->SSD(mid2013), hit_lpos[l], kDetectorSigma[l]);
				}else{ // l!=0
					fitter->AddHit(0, l, geometry->GTR(mid2013, l-1 ), hit_lpos[l], kDetectorSigma[l]);
				}
			}
			fitter->SetRungeKuttaStepSize(kStepSize);
			fitter->SetMaxSteps(kMaxSteps);
			std::vector<std::vector<int>> tmp_mid;//module id
			std::vector<std::vector<TVector3>> tmp_lpos;
			std::vector<std::vector<TVector3>> tmp_lres;
			tmp_mid.resize(3);
			tmp_lpos.resize(3);
			tmp_lres.resize(3);
			tmp_mid.clear();
			tmp_lpos.clear();
			tmp_lres.clear();
			for(int k=0; k < 3; k++){
				tmp_mid[k].clear();
				tmp_lpos[k].clear();
				tmp_lres[k].clear();
			}
			double chi2_4layers = fitter->Fit(false, false, true, kMinuitStrategy, kMaxFunctionCalls);
//			std::cout << "chi2  = " << chi2_4layers << std::endl;
			chi2_4layers_list.push_back(chi2_4layers);
			for(int l=0; l < 4; l++){
				fitter->GetFitLPos(0, l, tmp_mid[tgt_i], tmp_lpos[tgt_i]);//1st arg : trk id
				fitter->GetFitResidual(0, l, tmp_mid[tgt_i], tmp_lres[tgt_i]);
				tmp_post_detector_lx[tgt_i][l] = tmp_lpos[tgt_i][0].X();
				tmp_post_detector_ly[tgt_i][l] = tmp_lpos[tgt_i][0].Y();
				tmp_post_detector_res_x[tgt_i][l] = tmp_lres[tgt_i][0].X();
				tmp_post_detector_res_y[tgt_i][l] = tmp_lres[tgt_i][0].Y();
				tmp_post_detector_res_z[tgt_i][l] = tmp_lres[tgt_i][0].Z();
			}
            tmp_post_fit_tgtpj_x[tgt_i] = fitter->GetFitVertex().X();
            tmp_post_fit_tgtpj_y[tgt_i] = fitter->GetFitVertex().Y();
            tmp_post_fit_tgtpj_z[tgt_i] = fitter->GetFitVertex().Z();
		}//tgt_i loop
// select best tgt
		std::vector<double>::iterator iter = std::min_element(chi2_4layers_list.begin(), chi2_4layers_list.end());
		int min_id = std::distance(chi2_4layers_list.begin(), iter);
		std::cout << " min id = " << min_id << std::endl;

// --- // 
		post_chi_square = *iter;
       std::cout << "4 layer chi2 = " << post_chi_square << std::endl;
		for(int l=0; l < 4; l++){
			module_id[l]           = mids[l];
			post_detector_lx[l] = tmp_post_detector_lx[min_id][l];
			post_detector_ly[l] = tmp_post_detector_ly[min_id][l];
			post_detector_res_x[l] = tmp_post_detector_res_x[min_id][l];
			post_detector_res_y[l] = tmp_post_detector_res_y[min_id][l];
			post_detector_res_z[l] = tmp_post_detector_res_z[min_id][l];
//            if(l ==0 ){pre_detector_res_x[l]  = rk_res_ssd_x->at(tid);}
//            if(l ==1 ){pre_detector_res_x[l]  = rk_res_gtr100_tx2->at(tid);}
//            if(l ==2 ){pre_detector_res_x[l]  = rk_res_gtr200_tx2->at(tid);}
//            if(l ==3 ){pre_detector_res_x[l]  = rk_res_gtr300_tx2->at(tid);}
//            if(l ==1 ){pre_detector_res_y[l]  = rk_res_gtr100_ty->at(tid);}
//            if(l ==2 ){pre_detector_res_y[l]  = rk_res_gtr200_ty->at(tid);}
//            if(l ==3 ){pre_detector_res_y[l]  = rk_res_gtr300_ty->at(tid);}
//            if(l ==0 ){pre_detector_res_z[l]  = rk_res_ssd_z->at(tid);}
  //          if(l ==1 ){pre_detector_res_z[l]  = rk_res_gtr100_z->at(tid);}
  //          if(l ==2 ){pre_detector_res_z[l]  = rk_res_gtr200_z->at(tid);}
  //          if(l ==3 ){pre_detector_res_z[l]  = rk_res_gtr300_z->at(tid);}
//            std::cout << " layer " << l << std::endl;
/////			std::cout << " before lpos = (" << hit_lpos[l].X() << ", " << hit_lpos[l].Z() << std::endl;
//			std::cout << " L,pre  res, "  << pre_detector_res_x[l] << ", " << pre_detector_res_y[l] << std::endl;
//			std::cout << " L,post res, "  << post_detector_res_x[l] << ", " << post_detector_res_y[l] << std::endl;
//			std::cout << " L,lposx, " << l <<", " << post_detector_lx[l] << ", " << post_detector_ly[l] << std::endl;
       }//test
//            TVector3 rk_gpos0 = TVector3(rk_fit_ssd_gx->at(tid), 0, rk_fit_ssd_gz->at(tid));
//			TVector3 rk_lpos0 =  geometry->SSD(track_const::ModuleID2020To2013(mids[0]), 0)->GetLPos(rk_gpos0);
//            TVector3 rk_gpos1 = TVector3(rk_fit_gtr100_gx->at(tid), 0, rk_fit_gtr100_gz->at(tid));
//			TVector3 rk_lpos1 =  geometry->GTR(track_const::ModuleID2020To2013(mids[1]), 0)->GetLPos(rk_gpos1);
//            TVector3 rk_gpos2 = TVector3(rk_fit_gtr200_gx->at(tid), 0, rk_fit_gtr200_gz->at(tid));
//			TVector3 rk_lpos2 =  geometry->GTR(track_const::ModuleID2020To2013(mids[2]), 1)->GetLPos(rk_gpos2);
//            TVector3 rk_gpos3 = TVector3(rk_fit_gtr300_gx->at(tid), 0, rk_fit_gtr300_gz->at(tid));
//			TVector3 rk_lpos3 =  geometry->GTR(track_const::ModuleID2020To2013(mids[3]), 2)->GetLPos(rk_gpos3);
////            std::cout << "modules  = " << module_id[0] <<
////			 ", " << module_id[1] << 
////			 ", " << module_id[2] << 
////			 ", " << module_id[3] << std::endl;
//			std::cout << "dst1 fit x ssd, gtr123 =  " << rk_lpos0.X()  << ", "  
//			<< rk_lpos1.X() << ", "  
//			<< rk_lpos2.X() << ", "  
//			<< rk_lpos3.X() << ", "  << std::endl;
//			std::cout << "mura fit x ssd, gtr123 =  "  << post_detector_lx[0] << ", " 
//			<< post_detector_lx[1] << ", "
//			<< post_detector_lx[2] << ", "
//			<< post_detector_lx[3] << ", "
//			 << std::endl;
//			double b_clc_chi2 = 0;
//			double a_clc_chi2 = 0;
//			for(int l = 0; l < 4; l++){
//			std::cout << "layer = " <<l << std::endl;
//			double sq_b_res_x, sq_b_res_y, sq_a_res_x, sq_a_res_y;
//			if(l != 0 ) {
//			sq_b_res_x =pow((double)pre_detector_res_x[l]/0.3, 2);
//			sq_a_res_x =pow((double)post_detector_res_x[l]/0.3, 2);
//			sq_b_res_y =pow((double)pre_detector_res_y[l]/1,   2);
//			sq_a_res_y =pow((double)post_detector_res_y[l]/1,  2);
//			}
//			else {
//			sq_b_res_x = pow((double)pre_detector_res_x[l]/0.1, 2);
//			sq_a_res_x = pow((double)post_detector_res_x[l]/0.1,2);
//			sq_b_res_y = 0;
//			sq_a_res_y = 0;
//				}
//			//std::cout << "pre detc res = " << pre_detector_res_x[l] << std::endl;
//			b_clc_chi2 += sq_b_res_x; 
////			std::cout << "b clc chi2 = " << b_clc_chi2 << std::endl;
////			std::cout << " b res y " << b_res_y << std::endl;
//			b_clc_chi2 += sq_b_res_y;
////			std::cout << "b clc chi2 after y = " << b_clc_chi2 << std::endl;
//			a_clc_chi2 += sq_a_res_x;
//			a_clc_chi2 += sq_a_res_y;
//			std::cout << " pre  res xyz "  << pre_detector_res_x[l] << ", " << pre_detector_res_y[l] << std::endl;
//			std::cout << " post res xyz "  << post_detector_res_x[l] << ", " << post_detector_res_y[l] << ", " << post_detector_res_z[l] <<std::endl;
//            }
//			double btgtxy;
//			btgtxy = pow(rk_fit_init_pos_gx->at(tid)/3, 2) +  pow(rk_fit_init_pos_gy->at(tid)/3.4, 2);
//			b_clc_chi2 += btgtxy;
//			double atgtxy;
//			atgtxy = pow((double)tmp_post_fit_tgtpj_x[min_id]/3, 2) +  pow((double)tmp_post_fit_tgtpj_y[min_id]/3.4, 2);
//			a_clc_chi2 += atgtxy;
//			std::cout << "before : after chi2 " << b_clc_chi2 << " : " << a_clc_chi2 << std::endl;
//			std::cout << "pre  vetex =  "  
//			<< rk_fit_init_pos_gx->at(tid) << ", " 
//			<< rk_fit_init_pos_gy->at(tid) << ", " 
//			<< rk_fit_init_pos_gz->at(tid) << std::endl;
//			std::cout << "post vetex =  "  
//			<< tmp_post_fit_tgtpj_x[min_id] << ", " 
//			<< tmp_post_fit_tgtpj_y[min_id] << ", " 
//			<< tmp_post_fit_tgtpj_z[min_id]  
//			<< std::endl;
			trk_charge             = charge;
			pre_chi_square         = chi_square->at(tid);//rk 4 layers
		    module_id[4]           = track_hbd_mid->at(tid);
		    module_id[5]           = track_lg_mid->at(tid);
			
		    //lg_t                   = track_lg_allhit_ftime->at(tid).;
//			std::cout << "lg time :" << track_lg_t->at(tid) << std::endl;
		    ssd_t                  = track_ssd_t->at(tid);
   			pre_detector_res_x[4] = track_hbd_nearx->at(tid);
   		    pre_detector_res_x[5] = track_lg_nearx->at(tid);
   		    pre_detector_res_y[4] = track_hbd_neary->at(tid);
   		    pre_detector_res_y[5] = track_lg_neary->at(tid);
			post_fit_tgtpj_x = tmp_post_fit_tgtpj_x[min_id] ;//tgt
			post_fit_tgtpj_y = tmp_post_fit_tgtpj_y[min_id] ;//tgt
			post_fit_tgtpj_z = tmp_post_fit_tgtpj_z[min_id] ;//tgt
// -- finished four layer fit
//
// begin three layer fit including tgt, and four layer w/o tgt (removed i == 4)
	    for(int removed_layer_i = 0; removed_layer_i < 5; removed_layer_i++){
				if(removed_layer_i < 4){
				fitter->Clear();
				fitter->SetInitialVertex(TVector3(0.48,0.21, tgt_zs[min_id]), kTargetSigma);
				fitter->SetCharge(0, charge);//first argument is n of track (now, single )
				fitter->SetInitialMomentum(0, moms);
				for(int l=0; l < 4; l++){
					auto mid2013 = track_const::ModuleID2020To2013(mids[l]);
					if( l == 0) {
						if(removed_layer_i == l){
						fitter->AddHit(0, l, geometry->SSD(mid2013), hit_lpos[l], zero_sigma);//track_id == 0
						} else {
						fitter->AddHit(0, l, geometry->SSD(mid2013), hit_lpos[l], kDetectorSigma[l]);
						}	
					}else{ // l!=0
                        
						if(l == removed_layer_i){
						fitter->AddHit(0, l, geometry->GTR(mid2013, l -1), hit_lpos[l], zero_sigma);
						} else {
						fitter->AddHit(0, l, geometry->GTR(mid2013, l-1 ), hit_lpos[l], kDetectorSigma[l]);
						}
					}
				}
				fitter->SetRungeKuttaStepSize(kStepSize);
				fitter->SetMaxSteps(kMaxSteps);
				double chi2 = fitter->Fit(false, false, true, kMinuitStrategy, kMaxFunctionCalls);
    			std::vector<std::vector<int>> v_tmp_mid;//module id [tgt_i][nth track]
				std::vector<std::vector<TVector3>> v_tmp_lpos;
				std::vector<std::vector<TVector3>> v_tmp_lres;
				v_tmp_mid.resize(1);
				v_tmp_lpos.resize(1);
				v_tmp_lres.resize(1);
				v_tmp_mid.clear();
				v_tmp_lpos.clear();
				v_tmp_lres.clear();
				v_tmp_mid[0].clear();
				v_tmp_lpos[0].clear();
				v_tmp_lres[0].clear();
				//fitter->GetFitLPos(0, removed_layer_i, v_tmp_mid, v_tmp_lpos);
				//fitter->GetFitResidual(0, removed_layer_i, v_tmp_mid, v_tmp_lres);
                post_3l_chi_square[removed_layer_i] = chi2;
			//	std::cout << "chi2 :" << chi2 << std::endl;
                for(int ll = 0; ll < 4; ll++){
				fitter->GetFitLPos(0, ll, v_tmp_mid[0], v_tmp_lpos[0]);
				fitter->GetFitResidual(0, ll, v_tmp_mid[0], v_tmp_lres[0]);
			
//				std::cout << "removed l , lpos " << ll  << ", " <<  v_tmp_lpos[0][0].X() << std::endl;
//				std::cout << "removed l , res  " <<removed_layer_i << ", " <<  v_tmp_lres[0][0].X() << std::endl;
				post_3l_detector_res_x[removed_layer_i][ll] = v_tmp_lres[0][0].X();
				post_3l_detector_res_y[removed_layer_i][ll] = v_tmp_lres[0][0].Y();
                }
				} // three layer fit 
				else if(removed_layer_i == 4) {//wo tgt
					fitter->Clear();
					fitter->SetInitialVertex(TVector3(0.48,0.21, tgt_zs[min_id]), zero_sigma);
					fitter->SetCharge(0, charge);//first argument is n of track (now,single )
					fitter->SetInitialMomentum(0, moms);
			    	for(int l=0; l < 4; l++){
					auto mid2013 = track_const::ModuleID2020To2013(mids[l]);
					if( l == 0) {
						fitter->AddHit(0, l, geometry->SSD(mid2013), hit_lpos[l], kDetectorSigma[l]);
					}else{ // l!=0
						fitter->AddHit(0, l, geometry->GTR(mid2013, l-1 ), hit_lpos[l], kDetectorSigma[l]);
					}
					}
				fitter->SetRungeKuttaStepSize(kStepSize);
				fitter->SetMaxSteps(kMaxSteps);
				double chi2 = fitter->Fit(false, false, false, kMinuitStrategy, kMaxFunctionCalls);//not fixed vertex z

				std::vector<std::vector<int>> tmp_mid;//module id [tgt_i][nth track]
				std::vector<std::vector<TVector3>> tmp_lpos;
				std::vector<std::vector<TVector3>> tmp_lres;
				tmp_mid.resize(1);
				tmp_lpos.resize(1);
				tmp_lres.resize(1);
				tmp_mid.clear();
				tmp_lpos.clear();
				tmp_lres.clear();
				tmp_mid[0].clear();
				tmp_lpos[0].clear();
				tmp_lres[0].clear();

                post_wo_tgt_chi_square = chi2;
                for(int ll = 0; ll < 4; ll++){
					fitter->GetFitLPos(0, ll, tmp_mid[0], tmp_lpos[0]);
					fitter->GetFitResidual(0, ll, tmp_mid[0], tmp_lres[0]);
					post_wo_tgt_detector_res_x[ll] = tmp_lres[0][0].X();
					post_wo_tgt_detector_res_y[ll] = tmp_lres[0][0].Y();
				}
				post_wo_tgt_fit_tgtpj_x = fitter->GetFitVertex().X();//tgt
				post_wo_tgt_fit_tgtpj_y = fitter->GetFitVertex().Y();//tgt
				post_wo_tgt_fit_tgtpj_z = fitter->GetFitVertex().Z();//tgt
				//std::cout << "tgt pj (x,y,z) = " <<   post_wo_tgt_fit_tgtpj_x << ", " << post_wo_tgt_fit_tgtpj_y << ", " << post_wo_tgt_fit_tgtpj_z << std::endl;
				}// 4 layers w/o tgt
		}//removed layer i loop
        out_tree->Fill();
	}//selected track i loop
}

void GTRResidualCalculator::Calculate(){
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	  if(jentry%1 == 0 ){
	  	std::cout << jentry << " / " << nentries << std::endl;
	  }
	  if(jentry == maxevent) break;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
	  selected_track_indexs.clear();
      SelectTracks();//selected by hbd residual and delete duplicated gtr cluster
	  RKAnalyze(fitter); 
//	  RKAnalyzeForTgtCalib(fitter); 
   }
      std::vector<std::vector<double>> v_mean;
      v_mean.resize(20);
      
//      TCanvas *c0 = new TCanvas("c0", "c0", 1024, 768);
//	  TString pdf_name;
//	  pdf_name.Form("chi2_hist.pdf");
//	  c0->SaveAs(pdf_name + "[", "pdf");
//	  TCanvas *c1 = new TCanvas();
//	  c1->Divide(4,10);
      for(int i=0; i < 20; i++){
      for(int j=0; j < 20; j++){
	  	 h_chi2_tgtpos[i][j]->Write();
		 double mean = h_chi2_tgtpos[i][j]->GetMean();
		std::cout << "mmmmm " << mean  << std::endl;
	     v_mean[i].push_back(mean);
	  		}
		 }
       double min = 100000;
       int min_i = 100;
       int min_j = 100;
	   for(int i=0; i < 20;i++){
      for(int j=0; j < 20; j++){
            double tmean =  v_mean[i][j];
			std::cout << "mean, i , j " << tmean << ", " << i << ", " << j << std::endl;
			if(tmean < min){
			    min = tmean;
				min_i = i; 
				min_j = j;
			}
		}
		}
	   std::cout << "lowest mean, i, j : " << min << ", " << min_i << ", " << min_j << std::endl; 
	   


}



int main(int argc, char* argv[]){
	auto in_file_name = argv[1];
	auto out_file_name = argv[2];
	int maxevent = stoi(argv[3]);
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
	GTRResidualCalculator *t = new GTRResidualCalculator(out_file_name, in_chain, &fitter, maxevent);
	t->Calculate();
    t->GetOutFile()->Write();
	delete in_chain;
	return 0;
}
