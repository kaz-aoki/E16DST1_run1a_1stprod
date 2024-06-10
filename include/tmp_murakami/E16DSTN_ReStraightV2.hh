//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr 24 04:44:40 2024 by ROOT version 5.34/01
// from TTree tree/tree
// found on file: /work24/E16/Run0e/srs/dst1/240423_out_run_050376_sink0_000.dst1
//////////////////////////////////////////////////////////

#ifndef E16DSTN_ReStraightV2_hh
#define E16DSTN_ReStraightV2_hh

#include <TROOT.h>
#include <TChain.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>
#include <vector>
#include <vector>
#include <vector>
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_StraightMultiTrack.hh"
#include "E16DST_Constant.hh"
#include "E16ANA_StraightTrackConstant.hh"
#include "E16ANA_StraightTrackParameter.hh"
#include <TGraphErrors.h> 
#include <TF1.h> 
#include "E16ANA_StraightStepTrack.hh"
#include "E16DST_DST1Constant.hh" 

using namespace std;



// Fixed size dimensions of array or collections stored in the TTree if any.

class E16DSTN_ReStraightV2 {

public :
	struct TrackPair {
		int tid0;//track id //minus
		int tid1;//track id //plus
		TVector3 vtx;
		double distance;
		TVector3 mom_minus;
		TVector3 mom_plus;
		bool is_refit;
		bool is_selected;
		double chi_square_refit;
		TVector3 vtx_refit;
		TVector3 mom_minus_refit;
		TVector3 mom_plus_refit;
      std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> track_minus_pos_refit;
      std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> track_plus_pos_refit;
      std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> track_minus_mom_refit;
      std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> track_plus_mom_refit;
      std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> track_minus_res_refit;
      std::array<TVector3, E16ANA_TrackConstant::kNumTrackingLayers> track_plus_res_refit;
	   TrackPair& operator = (const TrackPair& rhs) {
	     Copy(rhs);
	     return (*this);
	   }
	   void Copy(const TrackPair& rhs) {
	     this->tid0= rhs.tid0;
	     this->tid1= rhs.tid1;
	     this->vtx = rhs.vtx;
	     this->distance = rhs.distance;
	     this->mom_minus = rhs.mom_minus;
	     this->mom_plus = rhs.mom_plus;
	     this->is_refit = rhs.is_refit;
	     this->is_selected = rhs.is_selected;
	     this->chi_square_refit = rhs.chi_square_refit;
	     this->vtx_refit = rhs.vtx_refit;
	     this->mom_minus_refit = rhs.mom_minus_refit;
	     this->mom_plus_refit = rhs.mom_plus_refit;
	     this->track_minus_pos_refit = rhs.track_minus_pos_refit;
	     this->track_plus_pos_refit = rhs.track_plus_pos_refit;
	     this->track_minus_mom_refit = rhs.track_minus_mom_refit;
	     this->track_plus_mom_refit = rhs.track_plus_mom_refit;
	     this->track_minus_res_refit = rhs.track_minus_res_refit;
		  this->track_plus_res_refit = rhs.track_plus_res_refit;
        return;
     }
     void Clear() {
       tid0 = E16DST_DST1Constant::kInvalidValue;
       tid1 = E16DST_DST1Constant::kInvalidValue;
       vtx = E16DST_DST1Constant::kInvalidVector;
       distance = E16DST_DST1Constant::kInvalidValue;
       mom_minus = E16DST_DST1Constant::kInvalidVector;
       mom_plus = E16DST_DST1Constant::kInvalidVector;
       is_refit = false;
       is_selected = false;
       vtx_refit = E16DST_DST1Constant::kInvalidVector;
 //      distance_refit = E16DST_DST1Constant::kInvalidValue;
       mom_minus_refit = E16DST_DST1Constant::kInvalidVector;
       mom_plus_refit = E16DST_DST1Constant::kInvalidVector;
       track_minus_pos_refit.fill(E16DST_DST1Constant::kInvalidVector);
       track_plus_pos_refit.fill(E16DST_DST1Constant::kInvalidVector);
       track_minus_mom_refit.fill(E16DST_DST1Constant::kInvalidVector);
       track_plus_mom_refit.fill(E16DST_DST1Constant::kInvalidVector);
       track_minus_res_refit.fill(E16DST_DST1Constant::kInvalidVector);
       track_plus_res_refit.fill(E16DST_DST1Constant::kInvalidVector);
     }
   };


private:
   E16ANA_StraightMultiTrack *pair_fitter;
#ifdef REMOVE_NOLAYER
   std::array<std::vector<int>, E16ANA_StraightTrackConstant::kNumTrackingStrips> used_cluster_ids;
#else
	#ifndef NoExist_SSD
   std::array<std::vector<int>, E16ANA_StraightTrackConstant::kNumTrackingStrips-2> used_cluster_ids;
	#else
   std::array<std::vector<int>, E16ANA_StraightTrackConstant::kNumTrackingStrips-1> used_cluster_ids;
	#endif
#endif
   E16ANA_GeometryV2 *geometry ;
   bool isWire;
   int n_targets;
	bool vertex_xy_fix_flag;
	bool py_fix_flag;
	bool vertex_z_fix_flag;
   std::vector<TVector3> targets_pos; 
   std::vector<TrackPair> track_pairs;
   std::vector<TrackPair*> selected_track_pairs;

	static constexpr int kPairMinuitStrategy = 2;
	static constexpr int kPairMinuitMaxFunctionCalls = 1e4;
	static inline const TVector3 kVertexSigma = {0, 0, 0};	
   static const int n_modules = 10;
	static const int n_layers  = 4;
	static const int n_div = 8;
// -- arrays for branch info -- // 
	std::array<int, 4> mids;
	std::array<int, 4> mids_tid0;
	std::array<int, 4> mids_tid1;
	std::array<double, 4> resx;
	std::array<double, 4> pre_resx;
	std::array<double, 4> resx_tid0;
	std::array<double, 4> resx_tid1;
	std::array<double, 4> resy;
	std::array<double, 4> resy_tid0;
	std::array<double, 4> resy_tid1;
	std::array<double, 4> fitlxs;
	std::array<double, 4> fitlys;
	std::array<double, 4> tans;//tan thetas
	std::array<double, 4> xt4s;//xt4
	std::array<double, 4> xadcs;//
	std::array<double, 4> yadcs;//
	std::array<int, 4> xcids;//
	std::array<double, 4> xtotend;//




//Histograms
   TH1D* h_chi2;
   TH1D* h_t0diff;
   TH1D* h_n_runid;
   TH1D* h_n_eventid;
   TH1D* h_n_spillid;
   TH1D* h_chi2_mod[n_modules];
   TH1D* h_lg_t_mod[n_modules];
   TH1D* h_tgt_proj_z_raw[n_modules];
   TH1D* h_tgt_proj_z_cut[n_modules];
   TH1D* h_tgt_proj_z_chi2cut[n_modules];
   TH1D* h_tgt_proj_x[n_modules];
   TH1D* h_tgt_proj_y[n_modules];
   TH1D* h_res_x[n_modules][n_layers];
   TH1D* h_pre_res_x[n_modules][n_layers];
   TH1D* h_res_y[n_modules][n_layers];
   TH1D* h_res_vtx_trk_x[n_modules][n_layers];
   TH1D* h_res_vtx_trk_y[n_modules][n_layers];
   TH1D* h_tan_theta[n_modules][n_layers];
//   TH1D* h_fitlx[n_tgt][n_modules][n_layers];
   TH1D* h_cluster_timing_raw[n_modules][n_layers];
   TH1D* h_cluster_timing_chi2[n_modules][n_layers];
   TH1D* h_cluster_timing_chi2_xdependence[n_modules][n_layers][n_div];
   TH1D* h_cluster_timing_chi2_ydependence[n_modules][n_layers][n_div];
	TH1D* h_tot_end_fr[n_modules][n_layers];	
	TH1D* h_tot_end_bg[n_modules][n_layers];	
	TH1D* h_cluster_adc_xdependence[n_modules][n_layers][n_div];
	TH1D* h_cluster_adc_ydependence[n_modules][n_layers][n_div];
	TH2D* h_init_pos;
	TH2D* h_tgt_pos_mod_raw[n_modules];
	TH2D* h_tgt_pos_mod_cut[n_modules];
	TH2D* h_cor_dz_time[n_modules][n_layers];
	TH2D* h_cor_dz_time_t0cor[n_modules][n_layers];
	TH2D* h_cor_res_fitlx[n_modules][n_layers];
	TH2D* h_cor_res_fitly[n_modules][n_layers];
	TH2D* h_cor_res_timing[n_modules][n_layers];
	TH2D* h_slopevel[n_modules][n_layers][n_div];
	TH1D* h_res_lg_x[n_modules];
	TH1D* h_res_lg_y[n_modules];
   
   TH2D* h_res_lg_2d[n_modules];

	TH1D* h_res_vtx_trk_lg_x[n_modules];
	TH1D* h_res_vtx_trk_lg_y[n_modules];
	TH1D* h_bak_res_lg_x[n_modules];
	TH1D* h_bak_res_lg_y[n_modules];

   TH2D* h_bak_res_lg_2d[n_modules];
	

	TH1D* h_bak_res_vtx_trk_lg_x[n_modules];
	TH1D* h_bak_res_vtx_trk_lg_y[n_modules];

//removed residual

//pair
	TH1D* h_vtx_gx;
	TH1D* h_vtx_gy;
	TH1D* h_vtx_gz;
	TH2D* h_vtx_gx_gz;	
	TH2D* h_vtx_gx_gy;	


public:

   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           run_id;
   Int_t           event_id;
   Int_t           spill_id;
   ULong64_t       timestamp_in_spill;
   Int_t           trigger_fine_time;
   Int_t           n_fill;
   Int_t           n_sts_hits;
   vector<int>     *sts_hit_id;
   vector<int>     *sts_hit_mid;
   vector<int>     *sts_hit_cid;
   vector<double>  *sts_hit_x;
   vector<double>  *sts_hit_gx;
   vector<double>  *sts_hit_gz;
   vector<double>  *sts_hit_t;
   vector<float>   *sts_hit_adc;
   Int_t           n_gtr100x_hits;
   vector<int>     *gtr100x_hit_id;
   vector<int>     *gtr100x_hit_mid;
   vector<int>     *gtr100x_hit_cid;
   vector<double>  *gtr100x_hit_x;
   vector<double>  *gtr100x_hit_tx;
   vector<double>  *gtr100x_hit_gx;
   vector<double>  *gtr100x_hit_gz;
   vector<double>  *gtr100x_hit_t;
   vector<float>   *gtr100x_hit_adc;
   Int_t           n_gtr200x_hits;
   vector<int>     *gtr200x_hit_id;
   vector<int>     *gtr200x_hit_mid;
   vector<int>     *gtr200x_hit_cid;
   vector<double>  *gtr200x_hit_x;
   vector<double>  *gtr200x_hit_tx;
   vector<double>  *gtr200x_hit_gx;
   vector<double>  *gtr200x_hit_gz;
   vector<double>  *gtr200x_hit_t;
   vector<float>   *gtr200x_hit_adc;
   Int_t           n_gtr300x_hits;
   vector<int>     *gtr300x_hit_id;
   vector<int>     *gtr300x_hit_mid;
   vector<int>     *gtr300x_hit_cid;
   vector<double>  *gtr300x_hit_x;
   vector<double>  *gtr300x_hit_tx;
   vector<double>  *gtr300x_hit_gx;
   vector<double>  *gtr300x_hit_gz;
   vector<double>  *gtr300x_hit_t;
   vector<float>   *gtr300x_hit_adc;
   Int_t           n_gtr100y_hits;
   vector<int>     *gtr100y_hit_id;
   vector<int>     *gtr100y_hit_mid;
   vector<int>     *gtr100y_hit_cid;
   vector<double>  *gtr100y_hit_y;
   vector<double>  *gtr100y_hit_ty;
   vector<double>  *gtr100y_hit_t;
   vector<float>   *gtr100y_hit_adc;
   Int_t           n_gtr100yb_hits;
   vector<int>     *gtr100yb_hit_id;
   vector<int>     *gtr100yb_hit_mid;
   vector<int>     *gtr100yb_hit_cid;
   vector<double>  *gtr100yb_hit_y;
   vector<double>  *gtr100yb_hit_ty;
   vector<double>  *gtr100yb_hit_t;
   vector<float>   *gtr100yb_hit_adc;
   Int_t           n_gtr200y_hits;
   vector<int>     *gtr200y_hit_id;
   vector<int>     *gtr200y_hit_mid;
   vector<int>     *gtr200y_hit_cid;
   vector<double>  *gtr200y_hit_y;
   vector<double>  *gtr200y_hit_ty;
   vector<double>  *gtr200y_hit_t;
   vector<float>   *gtr200y_hit_adc;
   Int_t           n_gtr300y_hits;
   vector<int>     *gtr300y_hit_id;
   vector<int>     *gtr300y_hit_mid;
   vector<int>     *gtr300y_hit_cid;
   vector<double>  *gtr300y_hit_y;
   vector<double>  *gtr300y_hit_ty;
   vector<double>  *gtr300y_hit_t;
   vector<float>   *gtr300y_hit_adc;

   Int_t           pre_n_gtrx_clusters = 0;
   vector<int>     pre_gtrx_cluster_id;
   vector<int>     pre_gtrx_cluster_mid;
   vector<int>     pre_gtrx_cluster_cid;
   vector<double>  pre_gtrx_cluster_x;
   vector<double>  pre_gtrx_cluster_ty;
   vector<double>  pre_gtrx_cluster_t;
   vector<float>   pre_gtrx_cluster_adc;
   Int_t           pre_n_gtry_clusters = 0;
   vector<int>     pre_gtry_cluster_id;
   vector<int>     pre_gtry_cluster_mid;
   vector<int>     pre_gtry_cluster_cid;
   vector<double>  pre_gtry_cluster_y;
   vector<double>  pre_gtry_cluster_ty;
   vector<double>  pre_gtry_cluster_t;
   vector<float>   pre_gtry_cluster_adc;


   Int_t           n_hbd_hits;
   vector<int>     *hbd_hit_id;
   vector<int>     *hbd_hit_mid;
   vector<int>     *hbd_hit_cid;
   vector<double>  *hbd_hit_x;
   vector<double>  *hbd_hit_y;
   vector<double>  *hbd_hit_gx;
   vector<double>  *hbd_hit_gy;
   vector<double>  *hbd_hit_gz;
   vector<double>  *hbd_hit_t;
   vector<float>   *hbd_hit_adc;
   Int_t           n_sts_clusters;
   vector<int>     *sts_cluster_id;
   vector<int>     *sts_cluster_mid;
   vector<double>  *sts_cluster_x;
   vector<double>  *sts_cluster_gx;
   vector<double>  *sts_cluster_gz;
   vector<float>   *sts_cluster_adc;
   vector<double>  *sts_cluster_t;
   vector<int>     *sts_cluster_size;
   vector<double>  *sts_cluster_fit_x;
   vector<double>  *sts_cluster_fit_t;
   vector<double>  *sts_cluster_fit_adc;
   vector<double>  *sts_cluster_fit_chi2;
   Int_t           n_gtr100x_clusters;
   vector<int>     *gtr100x_cluster_id;
   vector<vector<double>>     *gtr100x_cluster_consist_hit_id;
   vector<int>     *gtr100x_cluster_mid;
   vector<double>  *gtr100x_cluster_x;
   vector<double>  *gtr100x_cluster_gx;
   vector<double>  *gtr100x_cluster_gz;
   vector<float>   *gtr100x_cluster_adc;
   vector<double>  *gtr100x_cluster_t;
   vector<double>  *gtr100x_cluster_t2;
   vector<double>  *gtr100x_cluster_tx;
   vector<double>  *gtr100x_cluster_the;
   vector<double>  *gtr100x_cluster_gtx;
   vector<int>     *gtr100x_cluster_nc;
   vector<int>     *gtr100x_cluster_size;
   vector<double>  *gtr100x_cluster_last_tot_end;
   vector<double>  *gtr200x_cluster_last_tot_end;
   vector<double>  *gtr300x_cluster_last_tot_end;
   Int_t           n_gtr200x_clusters;
   vector<int>     *gtr200x_cluster_id;
   vector<vector<double>>     *gtr200x_cluster_consist_hit_id;
   vector<int>     *gtr200x_cluster_mid;
   vector<double>  *gtr200x_cluster_x;
   vector<double>  *gtr200x_cluster_gx;
   vector<double>  *gtr200x_cluster_gz;
   vector<float>   *gtr200x_cluster_adc;
   vector<double>  *gtr200x_cluster_t;
   vector<double>  *gtr200x_cluster_t2;
   vector<double>  *gtr200x_cluster_tx;
   vector<double>  *gtr200x_cluster_the;
   vector<int>     *gtr200x_cluster_nc;
   vector<double>  *gtr200x_cluster_gtx;
   vector<int>     *gtr200x_cluster_size;
   Int_t           n_gtr300x_clusters;
   vector<int>     *gtr300x_cluster_id;
   vector<vector<double>>     *gtr300x_cluster_consist_hit_id;
   vector<int>     *gtr300x_cluster_mid;
   vector<double>  *gtr300x_cluster_x;
   vector<double>  *gtr300x_cluster_gx;
   vector<double>  *gtr300x_cluster_gz;
   vector<float>   *gtr300x_cluster_adc;
   vector<double>  *gtr300x_cluster_t;
   vector<double>  *gtr300x_cluster_t2;
   vector<double>  *gtr300x_cluster_tx;
   vector<double>  *gtr300x_cluster_the;
   vector<int>     *gtr300x_cluster_nc;
   vector<double>  *gtr300x_cluster_gtx;
   vector<int>     *gtr300x_cluster_size;
   Int_t           n_gtr100y_clusters;
   vector<int>     *gtr100y_cluster_id;
   vector<vector<double>>     *gtr100y_cluster_consist_hit_id;
   vector<int>     *gtr100y_cluster_mid;
   vector<double>  *gtr100y_cluster_y;
   vector<float>   *gtr100y_cluster_adc;
   vector<double>  *gtr100y_cluster_t;
   vector<double>  *gtr100y_cluster_t2;
   vector<double>  *gtr100y_cluster_ty;
   vector<double>  *gtr100y_cluster_the;
   vector<int>     *gtr100y_cluster_nc;
   vector<int>     *gtr100y_cluster_size;
   Int_t           n_gtr100yb_clusters;
   vector<int>     *gtr100yb_cluster_id;
   vector<vector<double>>     *gtr100yb_cluster_consist_hit_id;
   vector<int>     *gtr100yb_cluster_mid;
   vector<double>  *gtr100yb_cluster_y;
   vector<float>   *gtr100yb_cluster_adc;
   vector<double>  *gtr100yb_cluster_t;
   vector<double>  *gtr100yb_cluster_t2;
   vector<double>  *gtr100yb_cluster_ty;
   vector<double>  *gtr100yb_cluster_the;
   vector<int>     *gtr100yb_cluster_nc;
   vector<int>     *gtr100yb_cluster_size;
   Int_t           n_gtr200y_clusters;
   vector<int>     *gtr200y_cluster_id;
   vector<vector<double>>     *gtr200y_cluster_consist_hit_id;
   vector<int>     *gtr200y_cluster_mid;
   vector<double>  *gtr200y_cluster_y;
   vector<float>   *gtr200y_cluster_adc;
   vector<double>  *gtr200y_cluster_t;
   vector<double>  *gtr200y_cluster_t2;
   vector<double>  *gtr200y_cluster_ty;
   vector<double>  *gtr200y_cluster_the;
   vector<int>     *gtr200y_cluster_nc;
   vector<int>     *gtr200y_cluster_size;
   Int_t           n_gtr300y_clusters;
   vector<int>     *gtr300y_cluster_id;
   vector<vector<double>>     *gtr300y_cluster_consist_hit_id;
   vector<int>     *gtr300y_cluster_mid;
   vector<double>  *gtr300y_cluster_y;
   vector<float>   *gtr300y_cluster_adc;
   vector<double>  *gtr300y_cluster_t;
   vector<double>  *gtr300y_cluster_t2;
   vector<double>  *gtr300y_cluster_ty;
   vector<double>  *gtr300y_cluster_the;
   vector<int>     *gtr300y_cluster_nc;
   vector<int>     *gtr300y_cluster_size;
   Int_t           n_hbd_clusters;
   vector<int>     *hbd_cluster_id;
   vector<int>     *hbd_cluster_mid;
   vector<double>  *hbd_cluster_x;
   vector<double>  *hbd_cluster_y;
   vector<double>  *hbd_cluster_gx;
   vector<double>  *hbd_cluster_gy;
   vector<double>  *hbd_cluster_gz;
   vector<float>   *hbd_cluster_adc;
   vector<int>     *hbd_cluster_max_cid;
   vector<double>  *hbd_cluster_t;
   vector<float>   *hbd_cluster_ftime;
   vector<float>   *hbd_cluster_tdiff;
   vector<int>     *hbd_cluster_size;
   vector<float>   *hbd_cluster_eprob;
   vector<float>   *hbd_cluster_cprob;
   Int_t           n_hbd_clusters_wotime;
   vector<int>     *hbd_cluster_wotime_id;
   vector<int>     *hbd_cluster_wotime_mid;
   vector<double>  *hbd_cluster_wotime_x;
   vector<double>  *hbd_cluster_wotime_y;
   vector<double>  *hbd_cluster_wotime_gx;
   vector<double>  *hbd_cluster_wotime_gy;
   vector<double>  *hbd_cluster_wotime_gz;
   vector<float>   *hbd_cluster_wotime_adc;
   vector<int>     *hbd_cluster_wotime_max_cid;
   vector<double>  *hbd_cluster_wotime_t;
   vector<float>   *hbd_cluster_wotime_ftime;
   vector<float>   *hbd_cluster_wotime_tdiff;
   vector<int>     *hbd_cluster_wotime_size;
   vector<float>   *hbd_cluster_wotime_eprob;
   vector<float>   *hbd_cluster_wotime_cprob;
   Int_t           n_lg_hits;
   vector<int>     *lg_hit_id;
   vector<int>     *lg_hit_mid;
   vector<int>     *lg_hit_cid;
   vector<double>  *lg_hit_x;
   vector<double>  *lg_hit_y;
   vector<double>  *lg_hit_z;
   vector<double>  *lg_hit_gx;
   vector<double>  *lg_hit_gy;
   vector<double>  *lg_hit_gz;
   vector<float>   *lg_hit_adc;
   vector<float>   *lg_hit_t;
   vector<float>   *lg_hit_wofit_adc;
   vector<float>   *lg_hit_wofit_t;
   vector<int>     *lg_hit_npeaks;
   vector<int>     *lg_hit_fflag;
   Int_t           pre_n_lg_hits = 0;
   vector<int>     pre_lg_hit_id;
   vector<int>     pre_lg_hit_mid;
   vector<int>     pre_lg_hit_cid;
   vector<double>  pre_lg_hit_x;
   vector<double>  pre_lg_hit_y;
   vector<double>  pre_lg_hit_z;
   vector<double>  pre_lg_hit_gx;
   vector<double>  pre_lg_hit_gy;
   vector<double>  pre_lg_hit_gz;
   vector<float>   pre_lg_hit_adc;
   vector<float>   pre_lg_hit_t;
   vector<float>   pre_lg_hit_wofit_adc;
   vector<float>   pre_lg_hit_wofit_t;
   vector<int>     pre_lg_hit_npeaks;
   vector<int>     pre_lg_hit_fflag;

   Int_t           n_lg_clusters;
   vector<int>     *lg_cluster_id;
   vector<int>     *lg_cluster_mid;
   vector<int>     *lg_cluster_max_cid;
   vector<int>     *lg_cluster_max_adc;
   vector<double>  *lg_cluster_x;
   vector<double>  *lg_cluster_y;
   vector<double>  *lg_cluster_z;
   vector<double>  *lg_cluster_gx;
   vector<double>  *lg_cluster_gy;
   vector<double>  *lg_cluster_gz;
   vector<float>   *lg_cluster_adc;
   vector<float>   *lg_cluster_t;
   vector<float>   *lg_cluster_tdiff;
   vector<int>     *lg_cluster_size;
   Int_t           n_trg_gtr_hits;
   vector<int>     *trg_gtr_hit_id;
   vector<int>     *trg_gtr_hit_mid;
   vector<int>     *trg_gtr_hit_cid;
   vector<double>  *trg_gtr_hit_x;
   vector<double>  *trg_gtr_hit_y;
   vector<double>  *trg_gtr_hit_gx;
   vector<double>  *trg_gtr_hit_gy;
   vector<double>  *trg_gtr_hit_gz;
   vector<float>   *trg_gtr_hit_t;
   Int_t           n_trg_hbd_hits;
   vector<int>     *trg_hbd_hit_id;
   vector<int>     *trg_hbd_hit_mid;
   vector<int>     *trg_hbd_hit_cid;
   vector<double>  *trg_hbd_hit_x;
   vector<double>  *trg_hbd_hit_y;
   vector<double>  *trg_hbd_hit_gx;
   vector<double>  *trg_hbd_hit_gy;
   vector<double>  *trg_hbd_hit_gz;
   vector<float>   *trg_hbd_hit_t;
   Int_t           n_trg_lg_hits;
   vector<int>     *trg_lg_hit_id;
   vector<int>     *trg_lg_hit_mid;
   vector<int>     *trg_lg_hit_cid;
   vector<double>  *trg_lg_hit_x;
   vector<double>  *trg_lg_hit_y;
   vector<double>  *trg_lg_hit_z;
   vector<double>  *trg_lg_hit_gx;
   vector<double>  *trg_lg_hit_gy;
   vector<double>  *trg_lg_hit_gz;
   vector<float>   *trg_lg_hit_t;
   Int_t           n_trg_tracks;
   vector<int>     *trg_track_n_gtr_hits;
   vector<vector<double> > *trg_track_gtr_id;
   vector<vector<double> > *trg_track_gtr_mid;
   vector<vector<double> > *trg_track_gtr_cid;
   vector<vector<double> > *trg_track_gtr_x;
   vector<vector<double> > *trg_track_gtr_y;
   vector<vector<double> > *trg_track_gtr_t;
   vector<vector<double> > *trg_track_gtr_is_t_match;
   vector<int>     *trg_track_n_hbd_hits;
   vector<vector<double> > *trg_track_hbd_id;
   vector<vector<double> > *trg_track_hbd_mid;
   vector<vector<double> > *trg_track_hbd_cid;
   vector<vector<double> > *trg_track_hbd_x;
   vector<vector<double> > *trg_track_hbd_y;
   vector<vector<double> > *trg_track_hbd_t;
   vector<vector<double> > *trg_track_hbd_is_t_match;
   vector<int>     *trg_track_lg_id;
   vector<int>     *trg_track_lg_mid;
   vector<int>     *trg_track_lg_cid;
   vector<double>  *trg_track_lg_x;
   vector<double>  *trg_track_lg_y;
   vector<float>   *trg_track_lg_t;
   Int_t           n_x_cands;
   Int_t           n_y_cands;
   Int_t           n_cands;
   Int_t           n_selected;
   Int_t           n_pairs;
   Int_t           n_refit_pairs;

   Int_t           n_alive_tracks;

   vector<int>     *track_id;
   vector<bool>    *has_e_hbd_cluster;
   vector<bool>    *has_e_lg_hit;
   vector<bool>    *is_large_residual;
   vector<bool>    *is_near_target;
   vector<bool>    *is_cluster_used;
   vector<bool>    *is_selected;
   vector<double>  *x_rough_fit_chi_square;
   vector<double>  *x_rough_fit_coef0;
   vector<double>  *x_rough_fit_coef1;
   vector<double>  *x_rough_fit_coef2;
   vector<int>     *rough_fit_n_hbds;
   vector<vector<double> > *rough_fit_hbd_ids;
   vector<vector<double> > *rough_fit_hbd_ress;
   vector<vector<double> > *rough_fit_hbd_y_oks;
   vector<double>  *y_rough_fit_chi_square;
   vector<double>  *y_rough_fit_coef0;
   vector<double>  *y_rough_fit_coef1;
   vector<double>  *chi_square;
   vector<int>     *n_steps;
   vector<int>     *n_calls;
   vector<int>     *rk_charge;
   vector<double>  *rk_hit_init_mom_gx;
   vector<double>  *rk_hit_init_mom_gy;
   vector<double>  *rk_hit_init_mom_gz;
   vector<double>  *rk_hit_init_pos_gx;
   vector<double>  *rk_hit_init_pos_gy;
   vector<double>  *rk_hit_init_pos_gz;
   vector<int>     *rk_hit_sts_id;
   vector<double>  *rk_hit_sts_x;
   vector<double>  *rk_hit_sts_gx;
   vector<double>  *rk_hit_sts_gy;
   vector<double>  *rk_hit_sts_gz;
   vector<float>   *rk_hit_sts_adc;
   vector<float>   *rk_hit_sts_t;
   vector<double>  *rk_hit_sts_chi2;
   vector<int>     *rk_hit_gtr100_xid;
   vector<int>     *rk_hit_gtr100_yid;
   vector<double>  *rk_hit_gtr100_gx;
   vector<double>  *rk_hit_gtr100_gy;
   vector<double>  *rk_hit_gtr100_gyt;
   vector<double>  *rk_hit_gtr100_gz;
   vector<float>   *rk_hit_gtr100_xadc;
   vector<float>   *rk_hit_gtr100_yadc;
   vector<float>   *rk_hit_gtr100_xt;
   vector<float>   *rk_hit_gtr100_yt;
   vector<float>   *rk_hit_gtr100_xt2;
   vector<float>   *rk_hit_gtr100_xt3;
   vector<float>   *rk_hit_gtr100_xt4;
   vector<float>   *rk_hit_gtr100_yt2;
   vector<float>   *rk_hit_gtr100_yt3;
   vector<float>   *rk_hit_gtr100_yt4;
   vector<double>  *rk_hit_gtr100_tx2;
   vector<double>  *rk_hit_gtr100_cogx;
   vector<double>  *rk_hit_gtr200_cogx;
   vector<double>  *rk_hit_gtr300_cogx;
   vector<double>  *rk_hit_gtr100_cogy;
   vector<double>  *rk_hit_gtr200_cogy;
   vector<double>  *rk_hit_gtr300_cogy;
   vector<double>  *rk_hit_gtr100_ty;
   vector<double>  *rk_hit_gtr100_gtx;
   vector<double>  *rk_hit_gtr100_gty;
   vector<double>  *rk_hit_gtr100_gtz;
   vector<double>  *rk_hit_gtr100_gtx2;
   vector<double>  *rk_hit_gtr100_gty2;
   vector<double>  *rk_hit_gtr100_gtz2;
   vector<int>     *rk_hit_gtr100_nc;
   vector<double>  *rk_hit_gtr100_the;
   vector<double>  *rk_hit_gtr100_the2;
   vector<int>     *rk_hit_gtr200_xid;
   vector<int>     *rk_hit_gtr200_yid;
   vector<double>  *rk_hit_gtr200_gx;
   vector<double>  *rk_hit_gtr200_gy;
   vector<double>  *rk_hit_gtr200_gz;
   vector<float>   *rk_hit_gtr200_xadc;
   vector<float>   *rk_hit_gtr200_yadc;
   vector<float>   *rk_hit_gtr200_xt;
   vector<float>   *rk_hit_gtr200_yt;
   vector<float>   *rk_hit_gtr200_xt2;
   vector<float>   *rk_hit_gtr200_xt3;
   vector<float>   *rk_hit_gtr200_xt4;
   vector<float>   *rk_hit_gtr200_yt2;
   vector<float>   *rk_hit_gtr200_yt3;
   vector<float>   *rk_hit_gtr200_yt4;
   vector<double>  *rk_hit_gtr200_tx2;
   vector<double>  *rk_hit_gtr200_ty;
   vector<double>  *rk_hit_gtr200_gtx;
   vector<double>  *rk_hit_gtr200_gty;
   vector<double>  *rk_hit_gtr200_gtz;
   vector<double>  *rk_hit_gtr200_gtx2;
   vector<double>  *rk_hit_gtr200_gty2;
   vector<double>  *rk_hit_gtr200_gtz2;
   vector<int>     *rk_hit_gtr200_nc;
   vector<double>  *rk_hit_gtr200_the;
   vector<double>  *rk_hit_gtr200_the2;
   vector<int>     *rk_hit_gtr300_xid;
   vector<int>     *rk_hit_gtr300_yid;
   vector<double>  *rk_hit_gtr300_gx;
   vector<double>  *rk_hit_gtr300_gy;
   vector<double>  *rk_hit_gtr300_gz;
   vector<float>   *rk_hit_gtr300_xadc;
   vector<float>   *rk_hit_gtr300_yadc;
   vector<float>   *rk_hit_gtr300_xt;
   vector<float>   *rk_hit_gtr300_yt;
   vector<float>   *rk_hit_gtr300_xt2;
   vector<float>   *rk_hit_gtr300_xt3;
   vector<float>   *rk_hit_gtr300_xt4;
   vector<float>   *rk_hit_gtr300_yt2;
   vector<float>   *rk_hit_gtr300_yt3;
   vector<float>   *rk_hit_gtr300_yt4;
   vector<double>  *rk_hit_gtr300_tx2;
   vector<double>  *rk_hit_gtr300_ty;
   vector<double>  *rk_hit_gtr300_gtx;
   vector<double>  *rk_hit_gtr300_gty;
   vector<double>  *rk_hit_gtr300_gtz;
   vector<double>  *rk_hit_gtr300_gtx2;
   vector<double>  *rk_hit_gtr300_gty2;
   vector<double>  *rk_hit_gtr300_gtz2;
   vector<int>     *rk_hit_gtr300_nc;
   vector<double>  *rk_hit_gtr300_the;
   vector<double>  *rk_hit_gtr300_the2;
   vector<double>  *rk_fit_init_mom_gx;
   vector<double>  *rk_fit_init_mom_gy;
   vector<double>  *rk_fit_init_mom_gz;
   vector<double>  *rk_fit_init_pos_gx;
   vector<double>  *rk_fit_init_pos_gy;
   vector<double>  *rk_fit_init_pos_gz;
   vector<int>     *rk_fit_sts_mid;
   vector<double>  *rk_fit_sts_x;
   vector<double>  *rk_fit_sts_y;
   vector<double>  *rk_fit_sts_gx;
   vector<double>  *rk_fit_sts_gy;
   vector<double>  *rk_fit_sts_gz;
   vector<double>  *rk_fit_sts_mom_x;
   vector<double>  *rk_fit_sts_mom_y;
   vector<double>  *rk_fit_sts_mom_z;
   vector<double>  *rk_fit_sts_mom_gx;
   vector<double>  *rk_fit_sts_mom_gy;
   vector<double>  *rk_fit_sts_mom_gz;
   vector<int>     *rk_fit_gtr100_mid;
   vector<double>  *rk_fit_gtr100_x;
   vector<double>  *rk_fit_gtr100_y;
   vector<double>  *rk_fit_gtr100_gx;
   vector<double>  *rk_fit_gtr100_gy;
   vector<double>  *rk_fit_gtr100_gz;
   vector<double>  *rk_fit_gtr100_mom_x;
   vector<double>  *rk_fit_gtr100_mom_y;
   vector<double>  *rk_fit_gtr100_mom_z;
   vector<double>  *rk_fit_gtr100_mom_gx;
   vector<double>  *rk_fit_gtr100_mom_gy;
   vector<double>  *rk_fit_gtr100_mom_gz;
   vector<int>     *rk_fit_gtr200_mid;
   vector<double>  *rk_fit_gtr200_x;
   vector<double>  *rk_fit_gtr200_y;
   vector<double>  *rk_fit_gtr200_gx;
   vector<double>  *rk_fit_gtr200_gy;
   vector<double>  *rk_fit_gtr200_gz;
   vector<double>  *rk_fit_gtr200_mom_x;
   vector<double>  *rk_fit_gtr200_mom_y;
   vector<double>  *rk_fit_gtr200_mom_z;
   vector<double>  *rk_fit_gtr200_mom_gx;
   vector<double>  *rk_fit_gtr200_mom_gy;
   vector<double>  *rk_fit_gtr200_mom_gz;
   vector<int>     *rk_fit_gtr300_mid;
   vector<double>  *rk_fit_gtr300_x;
   vector<double>  *rk_fit_gtr300_y;
   vector<double>  *rk_fit_gtr300_gx;
   vector<double>  *rk_fit_gtr300_gy;
   vector<double>  *rk_fit_gtr300_gz;
   vector<double>  *rk_fit_gtr300_mom_x;
   vector<double>  *rk_fit_gtr300_mom_y;
   vector<double>  *rk_fit_gtr300_mom_z;
   vector<double>  *rk_fit_gtr300_mom_gx;
   vector<double>  *rk_fit_gtr300_mom_gy;
   vector<double>  *rk_fit_gtr300_mom_gz;
   vector<int>     *rk_fit_hbd_mid;
   vector<double>  *rk_fit_hbd_x;
   vector<double>  *rk_fit_hbd_y;
   vector<double>  *rk_fit_hbd_gx;
   vector<double>  *rk_fit_hbd_gy;
   vector<double>  *rk_fit_hbd_gz;
   vector<double>  *rk_fit_hbd_mom_x;
   vector<double>  *rk_fit_hbd_mom_y;
   vector<double>  *rk_fit_hbd_mom_z;
   vector<double>  *rk_fit_hbd_mom_gx;
   vector<double>  *rk_fit_hbd_mom_gy;
   vector<double>  *rk_fit_hbd_mom_gz;
   vector<int>     *rk_fit_lg_c_mid;
   vector<double>  *rk_fit_lg_c_x;
   vector<double>  *rk_fit_lg_c_y;
   vector<double>  *rk_fit_lg_c_gx;
   vector<double>  *rk_fit_lg_c_gy;
   vector<double>  *rk_fit_lg_c_gz;
   vector<double>  *rk_fit_lg_c_mom_x;
   vector<double>  *rk_fit_lg_c_mom_y;
   vector<double>  *rk_fit_lg_c_mom_z;
   vector<double>  *rk_fit_lg_c_mom_gx;
   vector<double>  *rk_fit_lg_c_mom_gy;
   vector<double>  *rk_fit_lg_c_mom_gz;
   vector<int>     *rk_fit_lg_b_mid;
   vector<double>  *rk_fit_lg_b_x;
   vector<double>  *rk_fit_lg_b_y;
   vector<double>  *rk_fit_lg_b_gx;
   vector<double>  *rk_fit_lg_b_gy;
   vector<double>  *rk_fit_lg_b_gz;
   vector<double>  *rk_fit_lg_b_mom_x;
   vector<double>  *rk_fit_lg_b_mom_y;
   vector<double>  *rk_fit_lg_b_mom_z;
   vector<double>  *rk_fit_lg_b_mom_gx;
   vector<double>  *rk_fit_lg_b_mom_gy;
   vector<double>  *rk_fit_lg_b_mom_gz;
   vector<int>     *rk_fit_lg_a_mid;
   vector<double>  *rk_fit_lg_a_x;
   vector<double>  *rk_fit_lg_a_y;
   vector<double>  *rk_fit_lg_a_gx;
   vector<double>  *rk_fit_lg_a_gy;
   vector<double>  *rk_fit_lg_a_gz;
   vector<double>  *rk_fit_lg_a_mom_x;
   vector<double>  *rk_fit_lg_a_mom_y;
   vector<double>  *rk_fit_lg_a_mom_z;
   vector<double>  *rk_fit_lg_a_mom_gx;
   vector<double>  *rk_fit_lg_a_mom_gy;
   vector<double>  *rk_fit_lg_a_mom_gz;
   vector<double>  *rk_res_init_pos_gx;
   vector<double>  *rk_res_init_pos_gy;
   vector<double>  *rk_res_init_pos_gz;
   vector<double>  *rk_res_init_mom_gx;
   vector<double>  *rk_res_init_mom_gy;
   vector<double>  *rk_res_init_mom_gz;
   vector<double>  *rk_res_sts_x;
   vector<double>  *rk_res_gtr100_x;
   vector<double>  *rk_res_gtr100_y;
   vector<double>  *rk_res_gtr200_x;
   vector<double>  *rk_res_gtr200_y;
   vector<double>  *rk_res_gtr300_x;
   vector<double>  *rk_res_gtr300_y;
   vector<double>  *rk_res_gtr100_tx;
   vector<double>  *rk_res_gtr100_ty;
   vector<double>  *rk_res_gtr200_tx;
   vector<double>  *rk_res_gtr200_ty;
   vector<double>  *rk_res_gtr300_tx;
   vector<double>  *rk_res_gtr300_ty;
   vector<double>  *rk_res_gtr100_tx2;
   vector<double>  *rk_res_gtr200_tx2;
   vector<double>  *rk_res_gtr300_tx2;
   vector<double>  *rk_proj_tgt0_gx;
   vector<double>  *rk_proj_tgt0_gy;
   vector<double>  *rk_proj_tgt0_gz;
   vector<double>  *rk_proj_tgt1_gx;
   vector<double>  *rk_proj_tgt1_gy;
   vector<double>  *rk_proj_tgt1_gz;
   vector<double>  *rk_proj_tgt2_gx;
   vector<double>  *rk_proj_tgt2_gy;
   vector<double>  *rk_proj_tgt2_gz;
   vector<double>  *rk_proj_tgt0_mom_gx;
   vector<double>  *rk_proj_tgt0_mom_gy;
   vector<double>  *rk_proj_tgt0_mom_gz;
   vector<double>  *rk_proj_tgt1_mom_gx;
   vector<double>  *rk_proj_tgt1_mom_gy;
   vector<double>  *rk_proj_tgt1_mom_gz;
   vector<double>  *rk_proj_tgt2_mom_gx;
   vector<double>  *rk_proj_tgt2_mom_gy;
   vector<double>  *rk_proj_tgt2_mom_gz;
   vector<double>  *rk_proj_x0_gx;
   vector<double>  *rk_proj_x0_gy;
   vector<double>  *rk_proj_x0_gz;
   vector<double>  *rk_proj_x0_mom_gx;
   vector<double>  *rk_proj_x0_mom_gy;
   vector<double>  *rk_proj_x0_mom_gz;
   vector<bool>    *rk_proj_is_search;
   vector<int>     *rk_proj_n_hbd;
   vector<vector<double> > *rk_proj_hbd_id;
   vector<vector<double> > *rk_proj_hbd_mid;
   vector<vector<double> > *rk_proj_hbd_x;
   vector<vector<double> > *rk_proj_hbd_y;
   vector<vector<double> > *rk_proj_hbd_adc;
   vector<vector<double> > *rk_proj_hbd_t;
   vector<vector<double> > *rk_proj_hbd_ftime;
   vector<vector<double> > *rk_proj_hbd_tdiff;
   vector<vector<double> > *rk_proj_hbd_size;
   vector<vector<double> > *rk_proj_hbd_eprob;
   vector<vector<double> > *rk_proj_hbd_cprob;
   vector<int>     *rk_proj_n_lg;
   vector<vector<double> > *rk_proj_lg_id;
   vector<vector<double> > *rk_proj_lg_mid;
   vector<vector<double> > *rk_proj_lg_cid;
   vector<vector<double> > *rk_proj_lg_x;
   vector<vector<double> > *rk_proj_lg_y;
   vector<vector<double> > *rk_proj_lg_adc;
   vector<vector<double> > *rk_proj_lg_t;
   vector<vector<double> > *rk_proj_lg_npeaks;
   vector<vector<double> > *rk_proj_lg_fflag;
   vector<int>     *rk_pair_minus_track_id;
   vector<int>     *rk_pair_minus_gtr300_mid;
   vector<double>  *rk_pair_minus_chi_square;
   vector<double>  *rk_pair_minus_mom_gx;
   vector<double>  *rk_pair_minus_mom_gy;
   vector<double>  *rk_pair_minus_mom_gz;
   vector<double>  *rk_pair_minus_sts_t;
   vector<vector<double> > *rk_pair_minus_lg_t;
   vector<int>     *rk_pair_plus_track_id;
   vector<int>     *rk_pair_plus_gtr300_mid;
   vector<double>  *rk_pair_plus_chi_square;
   vector<double>  *rk_pair_plus_mom_gx;
   vector<double>  *rk_pair_plus_mom_gy;
   vector<double>  *rk_pair_plus_mom_gz;
   vector<double>  *rk_pair_plus_sts_t;
   vector<vector<double> > *rk_pair_plus_lg_t;
   vector<double>  *rk_pair_distance;
   vector<double>  *rk_pair_vtx_gx;
   vector<double>  *rk_pair_vtx_gy;
   vector<double>  *rk_pair_vtx_gz;
   vector<bool>    *rk_pair_is_refit;
   vector<bool>    *rk_pair_is_selected;
   vector<double>  *rk_pair_chi_square_refit;
   vector<double>  *rk_pair_vtx_refit_gx;
   vector<double>  *rk_pair_vtx_refit_gy;
   vector<double>  *rk_pair_vtx_refit_gz;
   vector<double>  *rk_pair_minus_mom_refit_gx;
   vector<double>  *rk_pair_minus_mom_refit_gy;
   vector<double>  *rk_pair_minus_mom_refit_gz;
   vector<double>  *rk_pair_plus_mom_refit_gx;
   vector<double>  *rk_pair_plus_mom_refit_gy;
   vector<double>  *rk_pair_plus_mom_refit_gz;
   vector<double>  *rk_pair_minus_sts_pos_refit_gx;
   vector<double>  *rk_pair_minus_sts_pos_refit_gy;
   vector<double>  *rk_pair_minus_sts_pos_refit_gz;
   vector<double>  *rk_pair_minus_gtr100_pos_refit_gx;
   vector<double>  *rk_pair_minus_gtr100_pos_refit_gy;
   vector<double>  *rk_pair_minus_gtr100_pos_refit_gz;
   vector<double>  *rk_pair_minus_gtr200_pos_refit_gx;
   vector<double>  *rk_pair_minus_gtr200_pos_refit_gy;
   vector<double>  *rk_pair_minus_gtr200_pos_refit_gz;
   vector<double>  *rk_pair_minus_gtr300_pos_refit_gx;
   vector<double>  *rk_pair_minus_gtr300_pos_refit_gy;
   vector<double>  *rk_pair_minus_gtr300_pos_refit_gz;
   vector<double>  *rk_pair_plus_sts_pos_refit_gx;
   vector<double>  *rk_pair_plus_sts_pos_refit_gy;
   vector<double>  *rk_pair_plus_sts_pos_refit_gz;
   vector<double>  *rk_pair_plus_gtr100_pos_refit_gx;
   vector<double>  *rk_pair_plus_gtr100_pos_refit_gy;
   vector<double>  *rk_pair_plus_gtr100_pos_refit_gz;
   vector<double>  *rk_pair_plus_gtr200_pos_refit_gx;
   vector<double>  *rk_pair_plus_gtr200_pos_refit_gy;
   vector<double>  *rk_pair_plus_gtr200_pos_refit_gz;
   vector<double>  *rk_pair_plus_gtr300_pos_refit_gx;
   vector<double>  *rk_pair_plus_gtr300_pos_refit_gy;
   vector<double>  *rk_pair_plus_gtr300_pos_refit_gz;
   vector<double>  *rk_pair_minus_sts_mom_refit_gx;
   vector<double>  *rk_pair_minus_sts_mom_refit_gy;
   vector<double>  *rk_pair_minus_sts_mom_refit_gz;
   vector<double>  *rk_pair_minus_gtr100_mom_refit_gx;
   vector<double>  *rk_pair_minus_gtr100_mom_refit_gy;
   vector<double>  *rk_pair_minus_gtr100_mom_refit_gz;
   vector<double>  *rk_pair_minus_gtr200_mom_refit_gx;
   vector<double>  *rk_pair_minus_gtr200_mom_refit_gy;
   vector<double>  *rk_pair_minus_gtr200_mom_refit_gz;
   vector<double>  *rk_pair_minus_gtr300_mom_refit_gx;
   vector<double>  *rk_pair_minus_gtr300_mom_refit_gy;
   vector<double>  *rk_pair_minus_gtr300_mom_refit_gz;
   vector<double>  *rk_pair_plus_sts_mom_refit_gx;
   vector<double>  *rk_pair_plus_sts_mom_refit_gy;
   vector<double>  *rk_pair_plus_sts_mom_refit_gz;
   vector<double>  *rk_pair_plus_gtr100_mom_refit_gx;
   vector<double>  *rk_pair_plus_gtr100_mom_refit_gy;
   vector<double>  *rk_pair_plus_gtr100_mom_refit_gz;
   vector<double>  *rk_pair_plus_gtr200_mom_refit_gx;
   vector<double>  *rk_pair_plus_gtr200_mom_refit_gy;
   vector<double>  *rk_pair_plus_gtr200_mom_refit_gz;
   vector<double>  *rk_pair_plus_gtr300_mom_refit_gx;
   vector<double>  *rk_pair_plus_gtr300_mom_refit_gy;
   vector<double>  *rk_pair_plus_gtr300_mom_refit_gz;
   vector<double>  *rk_pair_minus_sts_res_refit_x;
   vector<double>  *rk_pair_minus_sts_res_refit_y;
   vector<double>  *rk_pair_minus_sts_res_refit_z;
   vector<double>  *rk_pair_minus_gtr100_res_refit_x;
   vector<double>  *rk_pair_minus_gtr100_res_refit_y;
   vector<double>  *rk_pair_minus_gtr100_res_refit_z;
   vector<double>  *rk_pair_minus_gtr200_res_refit_x;
   vector<double>  *rk_pair_minus_gtr200_res_refit_y;
   vector<double>  *rk_pair_minus_gtr200_res_refit_z;
   vector<double>  *rk_pair_minus_gtr300_res_refit_x;
   vector<double>  *rk_pair_minus_gtr300_res_refit_y;
   vector<double>  *rk_pair_minus_gtr300_res_refit_z;
   vector<double>  *rk_pair_plus_sts_res_refit_x;
   vector<double>  *rk_pair_plus_sts_res_refit_y;
   vector<double>  *rk_pair_plus_sts_res_refit_z;
   vector<double>  *rk_pair_plus_gtr100_res_refit_x;
   vector<double>  *rk_pair_plus_gtr100_res_refit_y;
   vector<double>  *rk_pair_plus_gtr100_res_refit_z;
   vector<double>  *rk_pair_plus_gtr200_res_refit_x;
   vector<double>  *rk_pair_plus_gtr200_res_refit_y;
   vector<double>  *rk_pair_plus_gtr200_res_refit_z;
   vector<double>  *rk_pair_plus_gtr300_res_refit_x;
   vector<double>  *rk_pair_plus_gtr300_res_refit_y;
   vector<double>  *rk_pair_plus_gtr300_res_refit_z;
   vector<double>  *rk_pair_mass_refit;

   // List of branches
   TBranch        *b_run_id;   //!
   TBranch        *b_event_id;   //!
   TBranch        *b_spill_id;   //!
   TBranch        *b_timestamp_in_spill;   //!
   TBranch        *b_trigger_fine_time;   //!
   TBranch        *b_n_fill;   //!
   TBranch        *b_n_sts_hits;   //!
   TBranch        *b_sts_hit_id;   //!
   TBranch        *b_sts_hit_mid;   //!
   TBranch        *b_sts_hit_cid;   //!
   TBranch        *b_sts_hit_x;   //!
   TBranch        *b_sts_hit_gx;   //!
   TBranch        *b_sts_hit_gz;   //!
   TBranch        *b_sts_hit_t;   //!
   TBranch        *b_sts_hit_adc;   //!
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
   TBranch        *b_n_sts_clusters;   //!
   TBranch        *b_sts_cluster_id;   //!
   TBranch        *b_sts_cluster_mid;   //!
   TBranch        *b_sts_cluster_x;   //!
   TBranch        *b_sts_cluster_gx;   //!
   TBranch        *b_sts_cluster_gz;   //!
   TBranch        *b_sts_cluster_adc;   //!
   TBranch        *b_sts_cluster_t;   //!
   TBranch        *b_sts_cluster_size;   //!
   TBranch        *b_sts_cluster_fit_x;   //!
   TBranch        *b_sts_cluster_fit_t;   //!
   TBranch        *b_sts_cluster_fit_adc;   //!
   TBranch        *b_sts_cluster_fit_chi2;   //!
   TBranch        *b_n_gtr100x_clusters;   //!
   TBranch        *b_gtr100x_cluster_id;   //!
   TBranch        *b_gtr100x_cluster_consist_hit_id;   //!
   TBranch        *b_gtr200x_cluster_consist_hit_id;   //!
   TBranch        *b_gtr300x_cluster_consist_hit_id;   //!
   TBranch        *b_gtr100y_cluster_consist_hit_id;   //!
   TBranch        *b_gtr100yb_cluster_consist_hit_id;   //!
   TBranch        *b_gtr200y_cluster_consist_hit_id;   //!
   TBranch        *b_gtr300y_cluster_consist_hit_id;   //!
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
   TBranch        *b_gtr100x_cluster_last_tot_end;   //!
   TBranch        *b_gtr200x_cluster_last_tot_end;   //!
   TBranch        *b_gtr300x_cluster_last_tot_end;   //!
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
//   TBranch        *b_pre_n_lg_hits;   //!
//   TBranch        *b_pre_lg_hit_id;   //!
//   TBranch        *b_pre_lg_hit_mid;   //!
//   TBranch        *b_pre_lg_hit_cid;   //!
//   TBranch        *b_pre_lg_hit_x;   //!
//   TBranch        *b_pre_lg_hit_y;   //!
//   TBranch        *b_pre_lg_hit_z;   //!
//   TBranch        *b_pre_lg_hit_gx;   //!
//   TBranch        *b_pre_lg_hit_gy;   //!
//   TBranch        *b_pre_lg_hit_gz;   //!
//   TBranch        *b_pre_lg_hit_adc;   //!
//   TBranch        *b_pre_lg_hit_t;   //!
//   TBranch        *b_pre_lg_hit_wofit_adc;   //!
//   TBranch        *b_pre_lg_hit_wofit_t;   //!
//   TBranch        *b_pre_lg_hit_npeaks;   //!
//   TBranch        *b_pre_lg_hit_fflag;   //!
// 
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
   TBranch        *b_rk_hit_sts_id;   //!
   TBranch        *b_rk_hit_sts_x;   //!
   TBranch        *b_rk_hit_sts_gx;   //!
   TBranch        *b_rk_hit_sts_gy;   //!
   TBranch        *b_rk_hit_sts_gz;   //!
   TBranch        *b_rk_hit_sts_adc;   //!
   TBranch        *b_rk_hit_sts_t;   //!
   TBranch        *b_rk_hit_sts_chi2;   //!
   TBranch        *b_rk_hit_gtr100_xid;   //!
   TBranch        *b_rk_hit_gtr100_yid;   //!
   TBranch        *b_rk_hit_gtr100_gx;   //!
   TBranch        *b_rk_hit_gtr100_gy;   //!
   TBranch        *b_rk_hit_gtr100_gyt;   //!
   TBranch        *b_rk_hit_gtr100_gz;   //!
   TBranch        *b_rk_hit_gtr100_xadc;   //!
   TBranch        *b_rk_hit_gtr100_yadc;   //!
   TBranch        *b_rk_hit_gtr100_xt;   //!
   TBranch        *b_rk_hit_gtr100_yt;   //!
   TBranch        *b_rk_hit_gtr100_xt2;   //!
   TBranch        *b_rk_hit_gtr100_xt3;   //!
   TBranch        *b_rk_hit_gtr100_xt4;   //!
   TBranch        *b_rk_hit_gtr100_yt2;   //!
   TBranch        *b_rk_hit_gtr100_yt3;   //!
   TBranch        *b_rk_hit_gtr100_yt4;   //!
   TBranch        *b_rk_hit_gtr100_tx2;   //!
   TBranch        *b_rk_hit_gtr100_cogx;   //!
   TBranch        *b_rk_hit_gtr200_cogx;   //!
   TBranch        *b_rk_hit_gtr300_cogx;   //!
   TBranch        *b_rk_hit_gtr100_cogy;   //!
   TBranch        *b_rk_hit_gtr200_cogy;   //!
   TBranch        *b_rk_hit_gtr300_cogy;   //!
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
   TBranch        *b_rk_hit_gtr200_xt3;   //!
   TBranch        *b_rk_hit_gtr200_xt4;   //!
   TBranch        *b_rk_hit_gtr200_yt2;   //!
   TBranch        *b_rk_hit_gtr200_yt3;   //!
   TBranch        *b_rk_hit_gtr200_yt4;   //!
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
   TBranch        *b_rk_hit_gtr300_xt3;   //!
   TBranch        *b_rk_hit_gtr300_xt4;   //!
   TBranch        *b_rk_hit_gtr300_yt2;   //!
   TBranch        *b_rk_hit_gtr300_yt3;   //!
   TBranch        *b_rk_hit_gtr300_yt4;   //!
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
   TBranch        *b_rk_fit_sts_mid;   //!
   TBranch        *b_rk_fit_sts_x;   //!
   TBranch        *b_rk_fit_sts_y;   //!
   TBranch        *b_rk_fit_sts_gx;   //!
   TBranch        *b_rk_fit_sts_gy;   //!
   TBranch        *b_rk_fit_sts_gz;   //!
   TBranch        *b_rk_fit_sts_mom_x;   //!
   TBranch        *b_rk_fit_sts_mom_y;   //!
   TBranch        *b_rk_fit_sts_mom_z;   //!
   TBranch        *b_rk_fit_sts_mom_gx;   //!
   TBranch        *b_rk_fit_sts_mom_gy;   //!
   TBranch        *b_rk_fit_sts_mom_gz;   //!
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
   TBranch        *b_rk_res_sts_x;   //!
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
   TBranch        *b_rk_pair_minus_sts_t;   //!
   TBranch        *b_rk_pair_minus_lg_t;   //!
   TBranch        *b_rk_pair_plus_track_id;   //!
   TBranch        *b_rk_pair_plus_gtr300_mid;   //!
   TBranch        *b_rk_pair_plus_chi_square;   //!
   TBranch        *b_rk_pair_plus_mom_gx;   //!
   TBranch        *b_rk_pair_plus_mom_gy;   //!
   TBranch        *b_rk_pair_plus_mom_gz;   //!
   TBranch        *b_rk_pair_plus_sts_t;   //!
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
   TBranch        *b_rk_pair_minus_sts_pos_refit_gx;   //!
   TBranch        *b_rk_pair_minus_sts_pos_refit_gy;   //!
   TBranch        *b_rk_pair_minus_sts_pos_refit_gz;   //!
   TBranch        *b_rk_pair_minus_gtr100_pos_refit_gx;   //!
   TBranch        *b_rk_pair_minus_gtr100_pos_refit_gy;   //!
   TBranch        *b_rk_pair_minus_gtr100_pos_refit_gz;   //!
   TBranch        *b_rk_pair_minus_gtr200_pos_refit_gx;   //!
   TBranch        *b_rk_pair_minus_gtr200_pos_refit_gy;   //!
   TBranch        *b_rk_pair_minus_gtr200_pos_refit_gz;   //!
   TBranch        *b_rk_pair_minus_gtr300_pos_refit_gx;   //!
   TBranch        *b_rk_pair_minus_gtr300_pos_refit_gy;   //!
   TBranch        *b_rk_pair_minus_gtr300_pos_refit_gz;   //!
   TBranch        *b_rk_pair_plus_sts_pos_refit_gx;   //!
   TBranch        *b_rk_pair_plus_sts_pos_refit_gy;   //!
   TBranch        *b_rk_pair_plus_sts_pos_refit_gz;   //!
   TBranch        *b_rk_pair_plus_gtr100_pos_refit_gx;   //!
   TBranch        *b_rk_pair_plus_gtr100_pos_refit_gy;   //!
   TBranch        *b_rk_pair_plus_gtr100_pos_refit_gz;   //!
   TBranch        *b_rk_pair_plus_gtr200_pos_refit_gx;   //!
   TBranch        *b_rk_pair_plus_gtr200_pos_refit_gy;   //!
   TBranch        *b_rk_pair_plus_gtr200_pos_refit_gz;   //!
   TBranch        *b_rk_pair_plus_gtr300_pos_refit_gx;   //!
   TBranch        *b_rk_pair_plus_gtr300_pos_refit_gy;   //!
   TBranch        *b_rk_pair_plus_gtr300_pos_refit_gz;   //!
   TBranch        *b_rk_pair_minus_sts_mom_refit_gx;   //!
   TBranch        *b_rk_pair_minus_sts_mom_refit_gy;   //!
   TBranch        *b_rk_pair_minus_sts_mom_refit_gz;   //!
   TBranch        *b_rk_pair_minus_gtr100_mom_refit_gx;   //!
   TBranch        *b_rk_pair_minus_gtr100_mom_refit_gy;   //!
   TBranch        *b_rk_pair_minus_gtr100_mom_refit_gz;   //!
   TBranch        *b_rk_pair_minus_gtr200_mom_refit_gx;   //!
   TBranch        *b_rk_pair_minus_gtr200_mom_refit_gy;   //!
   TBranch        *b_rk_pair_minus_gtr200_mom_refit_gz;   //!
   TBranch        *b_rk_pair_minus_gtr300_mom_refit_gx;   //!
   TBranch        *b_rk_pair_minus_gtr300_mom_refit_gy;   //!
   TBranch        *b_rk_pair_minus_gtr300_mom_refit_gz;   //!
   TBranch        *b_rk_pair_plus_sts_mom_refit_gx;   //!
   TBranch        *b_rk_pair_plus_sts_mom_refit_gy;   //!
   TBranch        *b_rk_pair_plus_sts_mom_refit_gz;   //!
   TBranch        *b_rk_pair_plus_gtr100_mom_refit_gx;   //!
   TBranch        *b_rk_pair_plus_gtr100_mom_refit_gy;   //!
   TBranch        *b_rk_pair_plus_gtr100_mom_refit_gz;   //!
   TBranch        *b_rk_pair_plus_gtr200_mom_refit_gx;   //!
   TBranch        *b_rk_pair_plus_gtr200_mom_refit_gy;   //!
   TBranch        *b_rk_pair_plus_gtr200_mom_refit_gz;   //!
   TBranch        *b_rk_pair_plus_gtr300_mom_refit_gx;   //!
   TBranch        *b_rk_pair_plus_gtr300_mom_refit_gy;   //!
   TBranch        *b_rk_pair_plus_gtr300_mom_refit_gz;   //!
   TBranch        *b_rk_pair_minus_sts_res_refit_x;   //!
   TBranch        *b_rk_pair_minus_sts_res_refit_y;   //!
   TBranch        *b_rk_pair_minus_sts_res_refit_z;   //!
   TBranch        *b_rk_pair_minus_gtr100_res_refit_x;   //!
   TBranch        *b_rk_pair_minus_gtr100_res_refit_y;   //!
   TBranch        *b_rk_pair_minus_gtr100_res_refit_z;   //!
   TBranch        *b_rk_pair_minus_gtr200_res_refit_x;   //!
   TBranch        *b_rk_pair_minus_gtr200_res_refit_y;   //!
   TBranch        *b_rk_pair_minus_gtr200_res_refit_z;   //!
   TBranch        *b_rk_pair_minus_gtr300_res_refit_x;   //!
   TBranch        *b_rk_pair_minus_gtr300_res_refit_y;   //!
   TBranch        *b_rk_pair_minus_gtr300_res_refit_z;   //!
   TBranch        *b_rk_pair_plus_sts_res_refit_x;   //!
   TBranch        *b_rk_pair_plus_sts_res_refit_y;   //!
   TBranch        *b_rk_pair_plus_sts_res_refit_z;   //!
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


	
	TFile *fout;   //= new TFile (out_file, "recreate");
	TTree *outtree;// = new TTree("outtree", "outtree");

//   Int_t           out_run_id;
//   Int_t           out_event_id;
//   Int_t           out_spill_id;
//   ULong64_t       out_timestamp_in_spill;
//   Int_t           out_trigger_fine_time;
//   Int_t           out_n_fill;
//   Int_t           out_n_sts_hits;
//   std::vector<int>     out_sts_hit_id;
//   std::vector<int>     out_sts_hit_mid;
//   std::vector<int>     out_sts_hit_cid;
//   std::vector<double>  out_sts_hit_x;
//   std::vector<double>  out_sts_hit_gx;
//   std::vector<double>  out_sts_hit_gz;
//   std::vector<double>  out_sts_hit_t;
//   std::vector<float>   out_sts_hit_adc;
//   Int_t           out_n_gtr100x_hits;
//   std::vector<int>     out_gtr100x_hit_id;
//   std::vector<int>     out_gtr100x_hit_mid;
//   std::vector<int>     out_gtr100x_hit_cid;
//   std::vector<double>  out_gtr100x_hit_x;
//   std::vector<double>  out_gtr100x_hit_tx;
//   std::vector<double>  out_gtr100x_hit_gx;
//   std::vector<double>  out_gtr100x_hit_gz;
//   std::vector<std::vector<double>>  out_gtr100x_hit_t;
//   std::vector<float>   out_gtr100x_hit_adc;
//   Int_t           out_n_gtr200x_hits;
//   std::vector<int>     out_gtr200x_hit_id;
//   std::vector<int>     out_gtr200x_hit_mid;
//   std::vector<int>     out_gtr200x_hit_cid;
//   std::vector<double>  out_gtr200x_hit_x;
//   std::vector<double>  out_gtr200x_hit_tx;
//   std::vector<double>  out_gtr200x_hit_gx;
//   std::vector<double>  out_gtr200x_hit_gz;
//   std::vector<double>  out_gtr200x_hit_t;
//   std::vector<float>   out_gtr200x_hit_adc;
//   Int_t           out_n_gtr300x_hits;
//   std::vector<int>     out_gtr300x_hit_id;
//   std::vector<int>     out_gtr300x_hit_mid;
//   std::vector<int>     out_gtr300x_hit_cid;
//   std::vector<double>  out_gtr300x_hit_x;
//   std::vector<double>  out_gtr300x_hit_tx;
//   std::vector<double>  out_gtr300x_hit_gx;
//   std::vector<double>  out_gtr300x_hit_gz;
//   std::vector<double>  out_gtr300x_hit_t;
//   std::vector<float>   out_gtr300x_hit_adc;
//   Int_t           out_n_gtr100y_hits;
//   std::vector<int>     out_gtr100y_hit_id;
//   std::vector<int>     out_gtr100y_hit_mid;
//   std::vector<int>     out_gtr100y_hit_cid;
//   std::vector<double>  out_gtr100y_hit_y;
//   std::vector<double>  out_gtr100y_hit_ty;
//   std::vector<double>  out_gtr100y_hit_t;
//   std::vector<float>   out_gtr100y_hit_adc;
//   Int_t           out_n_gtr100yb_hits;
//   std::vector<int>     out_gtr100yb_hit_id;
//   std::vector<int>     out_gtr100yb_hit_mid;
//   std::vector<int>     out_gtr100yb_hit_cid;
//   std::vector<double>  out_gtr100yb_hit_y;
//   std::vector<double>  out_gtr100yb_hit_ty;
//   std::vector<double>  out_gtr100yb_hit_t;
//   std::vector<float>   out_gtr100yb_hit_adc;
//   Int_t                out_n_gtr200y_hits;
//   std::vector<int>     out_gtr200y_hit_id;
//   std::vector<int>     out_gtr200y_hit_mid;
//   std::vector<int>     out_gtr200y_hit_cid;
//   std::vector<double>  out_gtr200y_hit_y;
//   std::vector<double>  out_gtr200y_hit_ty;
//   std::vector<double>  out_gtr200y_hit_t;
//   std::vector<float>   out_gtr200y_hit_adc;
//
//   Int_t                out_n_gtr300y_hits;
//   std::vector<int>     out_gtr300y_hit_id;
//   std::vector<int>     out_gtr300y_hit_mid;
//   std::vector<int>     out_gtr300y_hit_cid;
//   std::vector<double>  out_gtr300y_hit_y;
//   std::vector<double>  out_gtr300y_hit_ty;
//   std::vector<double>  out_gtr300y_hit_t;
//   std::vector<float>   out_gtr300y_hit_adc;
//   Int_t                out_n_hbd_hits;
//   std::vector<int>     out_hbd_hit_id;
//   std::vector<int>     out_hbd_hit_mid;
//   std::vector<int>     out_hbd_hit_cid;
//   std::vector<double>  out_hbd_hit_x;
//   std::vector<double>  out_hbd_hit_y;
//   std::vector<double>  out_hbd_hit_gx;
//   std::vector<double>  out_hbd_hit_gy;
//   std::vector<double>  out_hbd_hit_gz;
//   std::vector<double>  out_hbd_hit_t;
//   std::vector<float>   out_hbd_hit_adc;
//   Int_t                out_n_sts_clusters;
//   std::vector<int>     out_sts_cluster_id;
//   std::vector<int>     out_sts_cluster_mid;
//   std::vector<double>  out_sts_cluster_x;
//   std::vector<double>  out_sts_cluster_gx;
//   std::vector<double>  out_sts_cluster_gz;
//   std::vector<float>   out_sts_cluster_adc;
//   std::vector<double>  out_sts_cluster_t;
//   std::vector<int>     out_sts_cluster_size;
//   std::vector<double>  out_sts_cluster_fit_x;
//   std::vector<double>  out_sts_cluster_fit_t;
//   std::vector<double>  out_sts_cluster_fit_adc;
//   std::vector<double>  out_sts_cluster_fit_chi2;
//   Int_t                out_n_gtr100x_clusters;
//   std::vector<int>     out_gtr100x_cluster_id;
////   std::vector<std::vector<int>>     out_gtr100x_cluster_consist_hit_id;
//   std::vector<int>     out_gtr100x_cluster_mid;
//   std::vector<double>  out_gtr100x_cluster_x;
//   std::vector<double>  out_gtr100x_cluster_gx;
//   std::vector<double>  out_gtr100x_cluster_gz;
//   std::vector<float>   out_gtr100x_cluster_adc;
//   std::vector<double>  out_gtr100x_cluster_t;
//   std::vector<double>  out_gtr100x_cluster_t2;
//   std::vector<double>  out_gtr100x_cluster_tx;
//   std::vector<double>  out_gtr100x_cluster_the;
//   std::vector<double>  out_gtr100x_cluster_gtx;
//   std::vector<int>     out_gtr100x_cluster_nc;
//   std::vector<int>     out_gtr100x_cluster_size;
//   Int_t                out_n_gtr200x_clusters;
//   std::vector<int>     out_gtr200x_cluster_id;
//   std::vector<int>     out_gtr200x_cluster_mid;
//   std::vector<double>  out_gtr200x_cluster_x;
//   std::vector<double>  out_gtr200x_cluster_gx;
//   std::vector<double>  out_gtr200x_cluster_gz;
//   std::vector<float>   out_gtr200x_cluster_adc;
//   std::vector<double>  out_gtr200x_cluster_t;
//   std::vector<double>  out_gtr200x_cluster_t2;
//   std::vector<double>  out_gtr200x_cluster_tx;
//   std::vector<double>  out_gtr200x_cluster_the;
//   std::vector<int>     out_gtr200x_cluster_nc;
//   std::vector<double>  out_gtr200x_cluster_gtx;
//   std::vector<int>     out_gtr200x_cluster_size;
//   Int_t                out_n_gtr300x_clusters;
//   std::vector<int>     out_gtr300x_cluster_id;
//   std::vector<int>     out_gtr300x_cluster_mid;
//   std::vector<double>  out_gtr300x_cluster_x;
//   std::vector<double>  out_gtr300x_cluster_gx;
//   std::vector<double>  out_gtr300x_cluster_gz;
//   std::vector<float>   out_gtr300x_cluster_adc;
//   std::vector<double>  out_gtr300x_cluster_t;
//   std::vector<double>  out_gtr300x_cluster_t2;
//   std::vector<double>  out_gtr300x_cluster_tx;
//   std::vector<double>  out_gtr300x_cluster_the;
//   std::vector<int>     out_gtr300x_cluster_nc;
//   std::vector<double>  out_gtr300x_cluster_gtx;
//   std::vector<int>     out_gtr300x_cluster_size;
//   Int_t                out_n_gtr100y_clusters;
//   std::vector<int>     out_gtr100y_cluster_id;
//   std::vector<int>     out_gtr100y_cluster_mid;
//   std::vector<double>  out_gtr100y_cluster_y;
//   std::vector<float>   out_gtr100y_cluster_adc;
//   std::vector<double>  out_gtr100y_cluster_t;
//   std::vector<double>  out_gtr100y_cluster_t2;
//   std::vector<double>  out_gtr100y_cluster_ty;
//   std::vector<double>  out_gtr100y_cluster_the;
//   std::vector<int>     out_gtr100y_cluster_nc;
//   std::vector<int>     out_gtr100y_cluster_size;
//   Int_t                out_n_gtr100yb_clusters;
//   std::vector<int>     out_gtr100yb_cluster_id;
//   std::vector<int>     out_gtr100yb_cluster_mid;
//   std::vector<double>  out_gtr100yb_cluster_y;
//   std::vector<float>   out_gtr100yb_cluster_adc;
//   std::vector<double>  out_gtr100yb_cluster_t;
//   std::vector<double>  out_gtr100yb_cluster_t2;
//   std::vector<double>  out_gtr100yb_cluster_ty;
//   std::vector<double>  out_gtr100yb_cluster_the;
//   std::vector<int>     out_gtr100yb_cluster_nc;
//   std::vector<int>     out_gtr100yb_cluster_size;
//   Int_t                out_n_gtr200y_clusters;
//   std::vector<int>     out_gtr200y_cluster_id;
//   std::vector<int>     out_gtr200y_cluster_mid;
//   std::vector<double>  out_gtr200y_cluster_y;
//   std::vector<float>   out_gtr200y_cluster_adc;
//   std::vector<double>  out_gtr200y_cluster_t;
//   std::vector<double>  out_gtr200y_cluster_t2;
//   std::vector<double>  out_gtr200y_cluster_ty;
//   std::vector<double>  out_gtr200y_cluster_the;
//   std::vector<int>     out_gtr200y_cluster_nc;
//   std::vector<int>     out_gtr200y_cluster_size;
//   Int_t                out_n_gtr300y_clusters;
//   std::vector<int>     out_gtr300y_cluster_id;
//   std::vector<int>     out_gtr300y_cluster_mid;
//   std::vector<double>  out_gtr300y_cluster_y;
//   std::vector<float>   out_gtr300y_cluster_adc;
//   std::vector<double>  out_gtr300y_cluster_t;
//   std::vector<double>  out_gtr300y_cluster_t2;
//   std::vector<double>  out_gtr300y_cluster_ty;
//   std::vector<double>  out_gtr300y_cluster_the;
//   std::vector<int>     out_gtr300y_cluster_nc;
//   std::vector<int>     out_gtr300y_cluster_size;
//   Int_t                out_n_hbd_clusters;
//   std::vector<int>     out_hbd_cluster_id;
//   std::vector<int>     out_hbd_cluster_mid;
//   std::vector<double>  out_hbd_cluster_x;
//   std::vector<double>  out_hbd_cluster_y;
//   std::vector<double>  out_hbd_cluster_gx;
//   std::vector<double>  out_hbd_cluster_gy;
//   std::vector<double>  out_hbd_cluster_gz;
//   std::vector<float>   out_hbd_cluster_adc;
//   std::vector<int>     out_hbd_cluster_max_cid;
//   std::vector<double>  out_hbd_cluster_t;
//   std::vector<float>   out_hbd_cluster_ftime;
//   std::vector<float>   out_hbd_cluster_tdiff;
//   std::vector<int>     out_hbd_cluster_size;
//   std::vector<float>   out_hbd_cluster_eprob;
//   std::vector<float>   out_hbd_cluster_cprob;
//   Int_t                out_n_hbd_clusters_wotime;
//   std::vector<int>     out_hbd_cluster_wotime_id;
//   std::vector<int>     out_hbd_cluster_wotime_mid;
//   std::vector<double>  out_hbd_cluster_wotime_x;
//   std::vector<double>  out_hbd_cluster_wotime_y;
//   std::vector<double>  out_hbd_cluster_wotime_gx;
//   std::vector<double>  out_hbd_cluster_wotime_gy;
//   std::vector<double>  out_hbd_cluster_wotime_gz;
//   std::vector<float>   out_hbd_cluster_wotime_adc;
//   std::vector<int>     out_hbd_cluster_wotime_max_cid;
//   std::vector<double>  out_hbd_cluster_wotime_t;
//   std::vector<float>   out_hbd_cluster_wotime_ftime;
//   std::vector<float>   out_hbd_cluster_wotime_tdiff;
//   std::vector<int>     out_hbd_cluster_wotime_size;
//   std::vector<float>   out_hbd_cluster_wotime_eprob;
//   std::vector<float>   out_hbd_cluster_wotime_cprob;
//   Int_t                out_n_lg_hits;
//   std::vector<int>     out_lg_hit_id;
//   std::vector<int>     out_lg_hit_mid;
//   std::vector<int>     out_lg_hit_cid;
//   std::vector<double>  out_lg_hit_x;
//   std::vector<double>  out_lg_hit_y;
//   std::vector<double>  out_lg_hit_z;
//   std::vector<double>  out_lg_hit_gx;
//   std::vector<double>  out_lg_hit_gy;
//   std::vector<double>  out_lg_hit_gz;
//   std::vector<float>   out_lg_hit_adc;
//   std::vector<float>   out_lg_hit_t;
//   std::vector<float>   out_lg_hit_wofit_adc;
//   std::vector<float>   out_lg_hit_wofit_t;
//   std::vector<int>     out_lg_hit_npeaks;
//   std::vector<int>     out_lg_hit_fflag;
//   Int_t                out_n_lg_clusters;
//   std::vector<int>     out_lg_cluster_id;
//   std::vector<int>     out_lg_cluster_mid;
//   std::vector<int>     out_lg_cluster_max_cid;
//   std::vector<int>     out_lg_cluster_max_adc;
//   std::vector<double>  out_lg_cluster_x;
//   std::vector<double>  out_lg_cluster_y;
//   std::vector<double>  out_lg_cluster_z;
//   std::vector<double>  out_lg_cluster_gx;
//   std::vector<double>  out_lg_cluster_gy;
//   std::vector<double>  out_lg_cluster_gz;
//   std::vector<float>   out_lg_cluster_adc;
//   std::vector<float>   out_lg_cluster_t;
//   std::vector<float>   out_lg_cluster_tdiff;
//   std::vector<int>     out_lg_cluster_size;
//   Int_t                out_n_trg_gtr_hits;
//   std::vector<int>     out_trg_gtr_hit_id;
//   std::vector<int>     out_trg_gtr_hit_mid;
//   std::vector<int>     out_trg_gtr_hit_cid;
//   std::vector<double>  out_trg_gtr_hit_x;
//   std::vector<double>  out_trg_gtr_hit_y;
//   std::vector<double>  out_trg_gtr_hit_gx;
//   std::vector<double>  out_trg_gtr_hit_gy;
//   std::vector<double>  out_trg_gtr_hit_gz;
//   std::vector<float>   out_trg_gtr_hit_t;
//   Int_t                out_n_trg_hbd_hits;
//   std::vector<int>     out_trg_hbd_hit_id;
//   std::vector<int>     out_trg_hbd_hit_mid;
//   std::vector<int>     out_trg_hbd_hit_cid;
//   std::vector<double>  out_trg_hbd_hit_x;
//   std::vector<double>  out_trg_hbd_hit_y;
//   std::vector<double>  out_trg_hbd_hit_gx;
//   std::vector<double>  out_trg_hbd_hit_gy;
//   std::vector<double>  out_trg_hbd_hit_gz;
//   std::vector<float>   out_trg_hbd_hit_t;
//   Int_t                out_n_trg_lg_hits;
//   std::vector<int>     out_trg_lg_hit_id;
//   std::vector<int>     out_trg_lg_hit_mid;
//   std::vector<int>     out_trg_lg_hit_cid;
//   std::vector<double>  out_trg_lg_hit_x;
//   std::vector<double>  out_trg_lg_hit_y;
//   std::vector<double>  out_trg_lg_hit_z;
//   std::vector<double>  out_trg_lg_hit_gx;
//   std::vector<double>  out_trg_lg_hit_gy;
//   std::vector<double>  out_trg_lg_hit_gz;
//   std::vector<float>   out_trg_lg_hit_t;
//   Int_t                out_n_trg_tracks;
//   std::vector<int>     out_trg_track_n_gtr_hits;
//   std::vector<std::vector<double> > out_trg_track_gtr_id;
//   std::vector<std::vector<double> > out_trg_track_gtr_mid;
//   std::vector<std::vector<double> > out_trg_track_gtr_cid;
//   std::vector<std::vector<double> > out_trg_track_gtr_x;
//   std::vector<std::vector<double> > out_trg_track_gtr_y;
//   std::vector<std::vector<double> > out_trg_track_gtr_t;
//   std::vector<std::vector<double> > out_trg_track_gtr_is_t_match;
//   std::vector<int>                  out_trg_track_n_hbd_hits;
//   std::vector<std::vector<double> > out_trg_track_hbd_id;
//   std::vector<std::vector<double> > out_trg_track_hbd_mid;
//   std::vector<std::vector<double> > out_trg_track_hbd_cid;
//   std::vector<std::vector<double> > out_trg_track_hbd_x;
//   std::vector<std::vector<double> > out_trg_track_hbd_y;
//   std::vector<std::vector<double> > out_trg_track_hbd_t;
//   std::vector<std::vector<double> > out_trg_track_hbd_is_t_match;
//   std::vector<int>     out_trg_track_lg_id;
//   std::vector<int>     out_trg_track_lg_mid;
//   std::vector<int>     out_trg_track_lg_cid;
//   std::vector<double>  out_trg_track_lg_x;
//   std::vector<double>  out_trg_track_lg_y;
//   std::vector<float>   out_trg_track_lg_t;
   Int_t                out_n_x_cands;
   Int_t                out_n_y_cands;
   Int_t                out_n_cands;
   Int_t                out_n_selected;
   Int_t                out_n_pairs;
   Int_t                out_n_refit_pairs;

//	Int_t out_n_alive_tracks;

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
   std::vector<int>     out_rk_hit_sts_id;
   std::vector<double>  out_rk_hit_sts_x;
   std::vector<double>  out_rk_hit_sts_gx;
   std::vector<double>  out_rk_hit_sts_gy;
   std::vector<double>  out_rk_hit_sts_gz;
   std::vector<float>   out_rk_hit_sts_adc;
   std::vector<float>   out_rk_hit_sts_t;
   std::vector<double>  out_rk_hit_sts_chi2;
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
   std::vector<int>     out_rk_fit_sts_mid;
   std::vector<double>  out_rk_fit_sts_x;
   std::vector<double>  out_rk_fit_sts_y;
   std::vector<double>  out_rk_fit_sts_gx;
   std::vector<double>  out_rk_fit_sts_gy;
   std::vector<double>  out_rk_fit_sts_gz;
   std::vector<double>  out_rk_fit_sts_mom_x;
   std::vector<double>  out_rk_fit_sts_mom_y;
   std::vector<double>  out_rk_fit_sts_mom_z;
   std::vector<double>  out_rk_fit_sts_mom_gx;
   std::vector<double>  out_rk_fit_sts_mom_gy;
   std::vector<double>  out_rk_fit_sts_mom_gz;
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
   std::vector<double>  out_rk_res_sts_x;
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
   std::vector<double>               out_rk_pair_minus_sts_t;
   std::vector<std::vector<double> > out_rk_pair_minus_lg_t;
   std::vector<int>                  out_rk_pair_plus_track_id;
   std::vector<int>                  out_rk_pair_plus_gtr300_mid;
   std::vector<double>               out_rk_pair_plus_chi_square;
   std::vector<double>               out_rk_pair_plus_mom_gx;
   std::vector<double>               out_rk_pair_plus_mom_gy;
   std::vector<double>               out_rk_pair_plus_mom_gz;
   std::vector<double>               out_rk_pair_plus_sts_t;
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
   std::vector<double> out_rk_pair_minus_sts_pos_refit_gx;
   std::vector<double> out_rk_pair_minus_sts_pos_refit_gy;
   std::vector<double> out_rk_pair_minus_sts_pos_refit_gz;
   std::vector<double> out_rk_pair_minus_gtr100_pos_refit_gx;
   std::vector<double> out_rk_pair_minus_gtr100_pos_refit_gy;
   std::vector<double> out_rk_pair_minus_gtr100_pos_refit_gz;
   std::vector<double> out_rk_pair_minus_gtr200_pos_refit_gx;
   std::vector<double> out_rk_pair_minus_gtr200_pos_refit_gy;
   std::vector<double> out_rk_pair_minus_gtr200_pos_refit_gz;
   std::vector<double> out_rk_pair_minus_gtr300_pos_refit_gx;
   std::vector<double> out_rk_pair_minus_gtr300_pos_refit_gy;
   std::vector<double> out_rk_pair_minus_gtr300_pos_refit_gz;
   std::vector<double> out_rk_pair_plus_sts_pos_refit_gx;
   std::vector<double> out_rk_pair_plus_sts_pos_refit_gy;
   std::vector<double> out_rk_pair_plus_sts_pos_refit_gz;
   std::vector<double> out_rk_pair_plus_gtr100_pos_refit_gx;
   std::vector<double> out_rk_pair_plus_gtr100_pos_refit_gy;
   std::vector<double> out_rk_pair_plus_gtr100_pos_refit_gz;
   std::vector<double> out_rk_pair_plus_gtr200_pos_refit_gx;
   std::vector<double> out_rk_pair_plus_gtr200_pos_refit_gy;
   std::vector<double> out_rk_pair_plus_gtr200_pos_refit_gz;
   std::vector<double> out_rk_pair_plus_gtr300_pos_refit_gx;
   std::vector<double> out_rk_pair_plus_gtr300_pos_refit_gy;
   std::vector<double> out_rk_pair_plus_gtr300_pos_refit_gz;
   std::vector<double> out_rk_pair_minus_sts_mom_refit_gx;
   std::vector<double> out_rk_pair_minus_sts_mom_refit_gy;
   std::vector<double> out_rk_pair_minus_sts_mom_refit_gz;
   std::vector<double> out_rk_pair_minus_gtr100_mom_refit_gx;
   std::vector<double> out_rk_pair_minus_gtr100_mom_refit_gy;
   std::vector<double> out_rk_pair_minus_gtr100_mom_refit_gz;
   std::vector<double> out_rk_pair_minus_gtr200_mom_refit_gx;
   std::vector<double> out_rk_pair_minus_gtr200_mom_refit_gy;
   std::vector<double> out_rk_pair_minus_gtr200_mom_refit_gz;
   std::vector<double> out_rk_pair_minus_gtr300_mom_refit_gx;
   std::vector<double> out_rk_pair_minus_gtr300_mom_refit_gy;
   std::vector<double> out_rk_pair_minus_gtr300_mom_refit_gz;
   std::vector<double> out_rk_pair_plus_sts_mom_refit_gx;
   std::vector<double> out_rk_pair_plus_sts_mom_refit_gy;
   std::vector<double> out_rk_pair_plus_sts_mom_refit_gz;
   std::vector<double> out_rk_pair_plus_gtr100_mom_refit_gx;
   std::vector<double> out_rk_pair_plus_gtr100_mom_refit_gy;
   std::vector<double> out_rk_pair_plus_gtr100_mom_refit_gz;
   std::vector<double> out_rk_pair_plus_gtr200_mom_refit_gx;
   std::vector<double> out_rk_pair_plus_gtr200_mom_refit_gy;
   std::vector<double> out_rk_pair_plus_gtr200_mom_refit_gz;
   std::vector<double> out_rk_pair_plus_gtr300_mom_refit_gx;
   std::vector<double> out_rk_pair_plus_gtr300_mom_refit_gy;
   std::vector<double> out_rk_pair_plus_gtr300_mom_refit_gz;
   std::vector<double> out_rk_pair_minus_sts_res_refit_x;
   std::vector<double> out_rk_pair_minus_sts_res_refit_y;
   std::vector<double> out_rk_pair_minus_sts_res_refit_z;
   std::vector<double> out_rk_pair_minus_gtr100_res_refit_x;
   std::vector<double> out_rk_pair_minus_gtr100_res_refit_y;
   std::vector<double> out_rk_pair_minus_gtr100_res_refit_z;
   std::vector<double> out_rk_pair_minus_gtr200_res_refit_x;
   std::vector<double> out_rk_pair_minus_gtr200_res_refit_y;
   std::vector<double> out_rk_pair_minus_gtr200_res_refit_z;
   std::vector<double> out_rk_pair_minus_gtr300_res_refit_x;
   std::vector<double> out_rk_pair_minus_gtr300_res_refit_y;
   std::vector<double> out_rk_pair_minus_gtr300_res_refit_z;
   std::vector<double> out_rk_pair_plus_sts_res_refit_x;
   std::vector<double> out_rk_pair_plus_sts_res_refit_y;
   std::vector<double> out_rk_pair_plus_sts_res_refit_z;
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

//   std::vector<std::vector<double>> out_re_lg_res_x;//restraight lg residual
//   std::vector<std::vector<double>> out_re_lg_res_y;//restraight lg residual

   std::vector<double>     out_gtr100x_cluster_last_tot_end;
   std::vector<double>     out_gtr200x_cluster_last_tot_end;
   std::vector<double>     out_gtr300x_cluster_last_tot_end;

	std::vector<std::vector<double>>	out_gtr100x_cluster_consist_hit_id;
	std::vector<std::vector<double>>	out_gtr200x_cluster_consist_hit_id;
	std::vector<std::vector<double>>	out_gtr300x_cluster_consist_hit_id;
	std::vector<std::vector<double>>	out_gtr100y_cluster_consist_hit_id;
	std::vector<std::vector<double>>	out_gtr100yb_cluster_consist_hit_id;
	std::vector<std::vector<double>>	out_gtr200y_cluster_consist_hit_id;
	std::vector<std::vector<double>>	out_gtr300y_cluster_consist_hit_id;


   E16DSTN_ReStraightV2(TTree *tree, const char *out_file, E16ANA_GeometryV2 *_geom, E16ANA_StraightMultiTrack *_pair_fitter, std::vector<TVector3> &tgt_pos);
   virtual ~E16DSTN_ReStraightV2();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree, const char *out_file);
   virtual void     Loop(TTree* tree, int print, int max, bool xy, bool py, bool z, int SW);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
 
	TFile *FileOut() {return fout;}
   bool HasUsedCluster(const std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips>& cids, std::array<std::vector<int>, E16ANA_StraightTrackConstant::kNumTrackingStrips> &used_cluster_ids);
   bool HasUsedCluster(const std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips - 2>& cids, std::array<std::vector<int>, E16ANA_StraightTrackConstant::kNumTrackingStrips-2> &used_cluster_ids);
   void ClearUsedClusterIDs();
   void AddRecord(TTree* intree, std::vector<int> &alive_ids);
	void ChiSqSort(std::vector<int> &ids);
	void SelectTracks(std::vector<int> &ids, std::vector<int> &outids);
	void DuplicationClusterCut(std::vector<int> &ids, std::vector<int> &outids);

	bool IsGoodTrack(const int id);
	bool IsRealTrack(const int id);
	bool IsSameTarget(const int tid0, const int tid1);
	bool IsLRTrack(const int tid0, const int tid1);
   void AnalyzeTrackPairs(std::vector<int> &in_ids);
	void PairTracking(TrackPair *track_pair);
	void AddTracks(TrackPair *track_pair);
	void UpdateFitResult(TrackPair *track_pair);
	double SearchVertex(TrackPair *track_pair);
	void SelectTrackPairs();

   void DrawHist( TTree* tree, int n_maxevent, int print_cycle, const int residual_layer,  TString pdf_name);
	void FillPulseInfos();
	void InitHistos();
	void FillVectors(int i);
	void CalculateRemovedGTRMinResidual();
//	void CalculateLGAllHitsResidual(int i, double &dx, double &dy, double &pre_dx, double &pre_dy);
};

#endif

#ifdef E16DSTN_ReStraightV2_cxx

E16DSTN_ReStraightV2::E16DSTN_ReStraightV2(TTree *tree, const char *out_file, E16ANA_GeometryV2 *_geom, E16ANA_StraightMultiTrack *_pair_fitter, std::vector<TVector3> & _tgt_pos) : fChain(0), geometry(_geom), pair_fitter(_pair_fitter), vertex_xy_fix_flag(false), py_fix_flag(false), vertex_z_fix_flag(E16ANA_StraightTrackParameter::kVtxZFixFlag)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/work24/E16/Run0e/srs/dst1/240423_out_run_050376_sink0_000.dst1");
//      if (!f || !f->IsOpen()) {
//         f = new TFile("/work24/E16/Run0e/srs/dst1/240423_out_run_050376_sink0_000.dst1");
//      }
//      f->GetObject("tree",tree);
   }
   Init(tree, out_file);
   n_targets = _tgt_pos.size();
   if(n_targets = 2) {isWire = true;}
	else if (n_targets == 3) {isWire = false;}
   else {std::cerr << "strange number of targerts" << std::endl; std::exit(0);}
   targets_pos.resize(_tgt_pos.size());
   for(int i=0; i < _tgt_pos.size(); i++){
     targets_pos[i] = _tgt_pos[i];
   }
}

E16DSTN_ReStraightV2::~E16DSTN_ReStraightV2()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t E16DSTN_ReStraightV2::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t E16DSTN_ReStraightV2::LoadTree(Long64_t entry)
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

void E16DSTN_ReStraightV2::Init(TTree *tree, const char* out_file)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).


	fout    = new TFile (out_file, "recreate");
	outtree = new TTree("tree", "tree");


   // Set object pointer
   sts_hit_id = 0;
   sts_hit_mid = 0;
   sts_hit_cid = 0;
   sts_hit_x = 0;
   sts_hit_gx = 0;
   sts_hit_gz = 0;
   sts_hit_t = 0;
   sts_hit_adc = 0;
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
   sts_cluster_id = 0;
   sts_cluster_mid = 0;
   sts_cluster_x = 0;
   sts_cluster_gx = 0;
   sts_cluster_gz = 0;
   sts_cluster_adc = 0;
   sts_cluster_t = 0;
   sts_cluster_size = 0;
   sts_cluster_fit_x = 0;
   sts_cluster_fit_t = 0;
   sts_cluster_fit_adc = 0;
   sts_cluster_fit_chi2 = 0;
   gtr100x_cluster_id = 0;
   gtr100x_cluster_consist_hit_id = 0;
   gtr200x_cluster_consist_hit_id = 0;
   gtr300x_cluster_consist_hit_id = 0;
   gtr100y_cluster_consist_hit_id = 0;
   gtr100yb_cluster_consist_hit_id = 0;
   gtr200y_cluster_consist_hit_id = 0;
   gtr300y_cluster_consist_hit_id = 0;
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
   gtr100x_cluster_last_tot_end = 0;
   gtr200x_cluster_last_tot_end = 0;
   gtr300x_cluster_last_tot_end = 0;
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
//   pre_lg_hit_id = 0;
//   pre_lg_hit_mid = 0;
//   pre_lg_hit_cid = 0;
//   pre_lg_hit_x = 0;
//   pre_lg_hit_y = 0;
//   pre_lg_hit_z = 0;
//   pre_lg_hit_gx = 0;
//   pre_lg_hit_gy = 0;
//   pre_lg_hit_gz = 0;
//   pre_lg_hit_adc = 0;
//   pre_lg_hit_t = 0;
//   pre_lg_hit_wofit_adc = 0;
//   pre_lg_hit_wofit_t = 0;
//   pre_lg_hit_npeaks = 0;
//   pre_lg_hit_fflag = 0;

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
   rk_hit_sts_id = 0;
   rk_hit_sts_x = 0;
   rk_hit_sts_gx = 0;
   rk_hit_sts_gy = 0;
   rk_hit_sts_gz = 0;
   rk_hit_sts_adc = 0;
   rk_hit_sts_t = 0;
   rk_hit_sts_chi2 = 0;
   rk_hit_gtr100_xid = 0;
   rk_hit_gtr100_yid = 0;
   rk_hit_gtr100_gx = 0;
   rk_hit_gtr100_gy = 0;
   rk_hit_gtr100_gyt = 0;
   rk_hit_gtr100_gz = 0;
   rk_hit_gtr100_xadc = 0;
   rk_hit_gtr100_yadc = 0;
   rk_hit_gtr100_xt = 0;
   rk_hit_gtr100_yt = 0;
   rk_hit_gtr100_xt2 = 0;
   rk_hit_gtr100_xt3 = 0;
   rk_hit_gtr100_xt4 = 0;
   rk_hit_gtr100_yt2 = 0;
   rk_hit_gtr100_yt3 = 0;
   rk_hit_gtr100_yt4 = 0;
   rk_hit_gtr100_tx2 = 0;
   rk_hit_gtr100_cogx = 0;
   rk_hit_gtr200_cogx = 0;
   rk_hit_gtr300_cogx = 0;
   rk_hit_gtr100_cogy = 0;
   rk_hit_gtr200_cogy = 0;
   rk_hit_gtr300_cogy = 0;
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
   rk_hit_gtr200_xt3 = 0;
   rk_hit_gtr200_xt4 = 0;
   rk_hit_gtr200_yt2 = 0;
   rk_hit_gtr200_yt3 = 0;
   rk_hit_gtr200_yt4 = 0;
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
   rk_hit_gtr300_xt3 = 0;
   rk_hit_gtr300_xt4 = 0;
   rk_hit_gtr300_yt2 = 0;
   rk_hit_gtr300_yt3 = 0;
   rk_hit_gtr300_yt4 = 0;
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
   rk_fit_sts_mid = 0;
   rk_fit_sts_x = 0;
   rk_fit_sts_y = 0;
   rk_fit_sts_gx = 0;
   rk_fit_sts_gy = 0;
   rk_fit_sts_gz = 0;
   rk_fit_sts_mom_x = 0;
   rk_fit_sts_mom_y = 0;
   rk_fit_sts_mom_z = 0;
   rk_fit_sts_mom_gx = 0;
   rk_fit_sts_mom_gy = 0;
   rk_fit_sts_mom_gz = 0;
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
   rk_res_sts_x = 0;
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
   rk_pair_minus_sts_t = 0;
   rk_pair_minus_lg_t = 0;
   rk_pair_plus_track_id = 0;
   rk_pair_plus_gtr300_mid = 0;
   rk_pair_plus_chi_square = 0;
   rk_pair_plus_mom_gx = 0;
   rk_pair_plus_mom_gy = 0;
   rk_pair_plus_mom_gz = 0;
   rk_pair_plus_sts_t = 0;
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
   rk_pair_minus_sts_pos_refit_gx = 0;
   rk_pair_minus_sts_pos_refit_gy = 0;
   rk_pair_minus_sts_pos_refit_gz = 0;
   rk_pair_minus_gtr100_pos_refit_gx = 0;
   rk_pair_minus_gtr100_pos_refit_gy = 0;
   rk_pair_minus_gtr100_pos_refit_gz = 0;
   rk_pair_minus_gtr200_pos_refit_gx = 0;
   rk_pair_minus_gtr200_pos_refit_gy = 0;
   rk_pair_minus_gtr200_pos_refit_gz = 0;
   rk_pair_minus_gtr300_pos_refit_gx = 0;
   rk_pair_minus_gtr300_pos_refit_gy = 0;
   rk_pair_minus_gtr300_pos_refit_gz = 0;
   rk_pair_plus_sts_pos_refit_gx = 0;
   rk_pair_plus_sts_pos_refit_gy = 0;
   rk_pair_plus_sts_pos_refit_gz = 0;
   rk_pair_plus_gtr100_pos_refit_gx = 0;
   rk_pair_plus_gtr100_pos_refit_gy = 0;
   rk_pair_plus_gtr100_pos_refit_gz = 0;
   rk_pair_plus_gtr200_pos_refit_gx = 0;
   rk_pair_plus_gtr200_pos_refit_gy = 0;
   rk_pair_plus_gtr200_pos_refit_gz = 0;
   rk_pair_plus_gtr300_pos_refit_gx = 0;
   rk_pair_plus_gtr300_pos_refit_gy = 0;
   rk_pair_plus_gtr300_pos_refit_gz = 0;
   rk_pair_minus_sts_mom_refit_gx = 0;
   rk_pair_minus_sts_mom_refit_gy = 0;
   rk_pair_minus_sts_mom_refit_gz = 0;
   rk_pair_minus_gtr100_mom_refit_gx = 0;
   rk_pair_minus_gtr100_mom_refit_gy = 0;
   rk_pair_minus_gtr100_mom_refit_gz = 0;
   rk_pair_minus_gtr200_mom_refit_gx = 0;
   rk_pair_minus_gtr200_mom_refit_gy = 0;
   rk_pair_minus_gtr200_mom_refit_gz = 0;
   rk_pair_minus_gtr300_mom_refit_gx = 0;
   rk_pair_minus_gtr300_mom_refit_gy = 0;
   rk_pair_minus_gtr300_mom_refit_gz = 0;
   rk_pair_plus_sts_mom_refit_gx = 0;
   rk_pair_plus_sts_mom_refit_gy = 0;
   rk_pair_plus_sts_mom_refit_gz = 0;
   rk_pair_plus_gtr100_mom_refit_gx = 0;
   rk_pair_plus_gtr100_mom_refit_gy = 0;
   rk_pair_plus_gtr100_mom_refit_gz = 0;
   rk_pair_plus_gtr200_mom_refit_gx = 0;
   rk_pair_plus_gtr200_mom_refit_gy = 0;
   rk_pair_plus_gtr200_mom_refit_gz = 0;
   rk_pair_plus_gtr300_mom_refit_gx = 0;
   rk_pair_plus_gtr300_mom_refit_gy = 0;
   rk_pair_plus_gtr300_mom_refit_gz = 0;
   rk_pair_minus_sts_res_refit_x = 0;
   rk_pair_minus_sts_res_refit_y = 0;
   rk_pair_minus_sts_res_refit_z = 0;
   rk_pair_minus_gtr100_res_refit_x = 0;
   rk_pair_minus_gtr100_res_refit_y = 0;
   rk_pair_minus_gtr100_res_refit_z = 0;
   rk_pair_minus_gtr200_res_refit_x = 0;
   rk_pair_minus_gtr200_res_refit_y = 0;
   rk_pair_minus_gtr200_res_refit_z = 0;
   rk_pair_minus_gtr300_res_refit_x = 0;
   rk_pair_minus_gtr300_res_refit_y = 0;
   rk_pair_minus_gtr300_res_refit_z = 0;
   rk_pair_plus_sts_res_refit_x = 0;
   rk_pair_plus_sts_res_refit_y = 0;
   rk_pair_plus_sts_res_refit_z = 0;
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
   fChain->SetBranchAddress("n_sts_hits", &n_sts_hits, &b_n_sts_hits);
   fChain->SetBranchAddress("sts_hit_id", &sts_hit_id, &b_sts_hit_id);
   fChain->SetBranchAddress("sts_hit_mid", &sts_hit_mid, &b_sts_hit_mid);
   fChain->SetBranchAddress("sts_hit_cid", &sts_hit_cid, &b_sts_hit_cid);
   fChain->SetBranchAddress("sts_hit_x", &sts_hit_x, &b_sts_hit_x);
   fChain->SetBranchAddress("sts_hit_gx", &sts_hit_gx, &b_sts_hit_gx);
   fChain->SetBranchAddress("sts_hit_gz", &sts_hit_gz, &b_sts_hit_gz);
   fChain->SetBranchAddress("sts_hit_t", &sts_hit_t, &b_sts_hit_t);
   fChain->SetBranchAddress("sts_hit_adc", &sts_hit_adc, &b_sts_hit_adc);
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
   fChain->SetBranchAddress("n_sts_clusters", &n_sts_clusters, &b_n_sts_clusters);
   fChain->SetBranchAddress("sts_cluster_id", &sts_cluster_id, &b_sts_cluster_id);
   fChain->SetBranchAddress("sts_cluster_mid", &sts_cluster_mid, &b_sts_cluster_mid);
   fChain->SetBranchAddress("sts_cluster_x", &sts_cluster_x, &b_sts_cluster_x);
   fChain->SetBranchAddress("sts_cluster_gx", &sts_cluster_gx, &b_sts_cluster_gx);
   fChain->SetBranchAddress("sts_cluster_gz", &sts_cluster_gz, &b_sts_cluster_gz);
   fChain->SetBranchAddress("sts_cluster_adc", &sts_cluster_adc, &b_sts_cluster_adc);
   fChain->SetBranchAddress("sts_cluster_t", &sts_cluster_t, &b_sts_cluster_t);
   fChain->SetBranchAddress("sts_cluster_size", &sts_cluster_size, &b_sts_cluster_size);
   fChain->SetBranchAddress("sts_cluster_fit_x", &sts_cluster_fit_x, &b_sts_cluster_fit_x);
   fChain->SetBranchAddress("sts_cluster_fit_t", &sts_cluster_fit_t, &b_sts_cluster_fit_t);
   fChain->SetBranchAddress("sts_cluster_fit_adc", &sts_cluster_fit_adc, &b_sts_cluster_fit_adc);
   fChain->SetBranchAddress("sts_cluster_fit_chi2", &sts_cluster_fit_chi2, &b_sts_cluster_fit_chi2);
   fChain->SetBranchAddress("n_gtr100x_clusters", &n_gtr100x_clusters, &b_n_gtr100x_clusters);
   fChain->SetBranchAddress("gtr100x_cluster_id", &gtr100x_cluster_id, &b_gtr100x_cluster_id);
   fChain->SetBranchAddress("gtr100x_cluster_consist_hit_id", &gtr100x_cluster_consist_hit_id, &b_gtr100x_cluster_consist_hit_id);
   fChain->SetBranchAddress("gtr200x_cluster_consist_hit_id", &gtr200x_cluster_consist_hit_id, &b_gtr200x_cluster_consist_hit_id);
   fChain->SetBranchAddress("gtr300x_cluster_consist_hit_id", &gtr300x_cluster_consist_hit_id, &b_gtr300x_cluster_consist_hit_id);
   fChain->SetBranchAddress("gtr100y_cluster_consist_hit_id", &gtr100y_cluster_consist_hit_id, &b_gtr100y_cluster_consist_hit_id);
   fChain->SetBranchAddress("gtr100yb_cluster_consist_hit_id", &gtr100yb_cluster_consist_hit_id, &b_gtr100yb_cluster_consist_hit_id);
   fChain->SetBranchAddress("gtr200y_cluster_consist_hit_id", &gtr200y_cluster_consist_hit_id, &b_gtr200y_cluster_consist_hit_id);
   fChain->SetBranchAddress("gtr300y_cluster_consist_hit_id", &gtr300y_cluster_consist_hit_id, &b_gtr300y_cluster_consist_hit_id);
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
   fChain->SetBranchAddress("gtr100x_cluster_last_tot_end", &gtr100x_cluster_last_tot_end, &b_gtr100x_cluster_last_tot_end);
   fChain->SetBranchAddress("gtr200x_cluster_last_tot_end", &gtr200x_cluster_last_tot_end, &b_gtr200x_cluster_last_tot_end);
   fChain->SetBranchAddress("gtr300x_cluster_last_tot_end", &gtr300x_cluster_last_tot_end, &b_gtr300x_cluster_last_tot_end);
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
   fChain->SetBranchAddress("lg_hit_t"  , &lg_hit_t  , &b_lg_hit_t);
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
   fChain->SetBranchAddress("rk_hit_sts_id", &rk_hit_sts_id, &b_rk_hit_sts_id);
   fChain->SetBranchAddress("rk_hit_sts_x", &rk_hit_sts_x, &b_rk_hit_sts_x);
   fChain->SetBranchAddress("rk_hit_sts_gx", &rk_hit_sts_gx, &b_rk_hit_sts_gx);
   fChain->SetBranchAddress("rk_hit_sts_gy", &rk_hit_sts_gy, &b_rk_hit_sts_gy);
   fChain->SetBranchAddress("rk_hit_sts_gz", &rk_hit_sts_gz, &b_rk_hit_sts_gz);
   fChain->SetBranchAddress("rk_hit_sts_adc", &rk_hit_sts_adc, &b_rk_hit_sts_adc);
   fChain->SetBranchAddress("rk_hit_sts_t", &rk_hit_sts_t, &b_rk_hit_sts_t);
   fChain->SetBranchAddress("rk_hit_sts_chi2", &rk_hit_sts_chi2, &b_rk_hit_sts_chi2);
   fChain->SetBranchAddress("rk_hit_gtr100_xid", &rk_hit_gtr100_xid, &b_rk_hit_gtr100_xid);
   fChain->SetBranchAddress("rk_hit_gtr100_yid", &rk_hit_gtr100_yid, &b_rk_hit_gtr100_yid);
   fChain->SetBranchAddress("rk_hit_gtr100_gx", &rk_hit_gtr100_gx, &b_rk_hit_gtr100_gx);
   fChain->SetBranchAddress("rk_hit_gtr100_gy", &rk_hit_gtr100_gy, &b_rk_hit_gtr100_gy);
   fChain->SetBranchAddress("rk_hit_gtr100_gyt", &rk_hit_gtr100_gyt, &b_rk_hit_gtr100_gyt);
   fChain->SetBranchAddress("rk_hit_gtr100_gz", &rk_hit_gtr100_gz, &b_rk_hit_gtr100_gz);
   fChain->SetBranchAddress("rk_hit_gtr100_xadc", &rk_hit_gtr100_xadc, &b_rk_hit_gtr100_xadc);
   fChain->SetBranchAddress("rk_hit_gtr100_yadc", &rk_hit_gtr100_yadc, &b_rk_hit_gtr100_yadc);
   fChain->SetBranchAddress("rk_hit_gtr100_xt", &rk_hit_gtr100_xt, &b_rk_hit_gtr100_xt);
   fChain->SetBranchAddress("rk_hit_gtr100_yt", &rk_hit_gtr100_yt, &b_rk_hit_gtr100_yt);
   fChain->SetBranchAddress("rk_hit_gtr100_xt2", &rk_hit_gtr100_xt2, &b_rk_hit_gtr100_xt2);
   fChain->SetBranchAddress("rk_hit_gtr100_xt3", &rk_hit_gtr100_xt3, &b_rk_hit_gtr100_xt3);
   fChain->SetBranchAddress("rk_hit_gtr100_xt4", &rk_hit_gtr100_xt4, &b_rk_hit_gtr100_xt4);
   fChain->SetBranchAddress("rk_hit_gtr100_yt2", &rk_hit_gtr100_yt2, &b_rk_hit_gtr100_yt2);
   fChain->SetBranchAddress("rk_hit_gtr100_yt3", &rk_hit_gtr100_yt3, &b_rk_hit_gtr100_yt3);
   fChain->SetBranchAddress("rk_hit_gtr100_yt4", &rk_hit_gtr100_yt4, &b_rk_hit_gtr100_yt4);
   fChain->SetBranchAddress("rk_hit_gtr100_tx2", &rk_hit_gtr100_tx2, &b_rk_hit_gtr100_tx2);
   fChain->SetBranchAddress("rk_hit_gtr100_cogx", &rk_hit_gtr100_cogx, &b_rk_hit_gtr100_cogx);
   fChain->SetBranchAddress("rk_hit_gtr200_cogx", &rk_hit_gtr200_cogx, &b_rk_hit_gtr200_cogx);
   fChain->SetBranchAddress("rk_hit_gtr300_cogx", &rk_hit_gtr300_cogx, &b_rk_hit_gtr300_cogx);
   fChain->SetBranchAddress("rk_hit_gtr100_cogy", &rk_hit_gtr100_cogy, &b_rk_hit_gtr100_cogy);
   fChain->SetBranchAddress("rk_hit_gtr200_cogy", &rk_hit_gtr200_cogy, &b_rk_hit_gtr200_cogy);
   fChain->SetBranchAddress("rk_hit_gtr300_cogy", &rk_hit_gtr300_cogy, &b_rk_hit_gtr300_cogy);
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
   fChain->SetBranchAddress("rk_hit_gtr200_xt3", &rk_hit_gtr200_xt3, &b_rk_hit_gtr200_xt3);
   fChain->SetBranchAddress("rk_hit_gtr200_xt4", &rk_hit_gtr200_xt4, &b_rk_hit_gtr200_xt4);
   fChain->SetBranchAddress("rk_hit_gtr200_yt2", &rk_hit_gtr200_yt2, &b_rk_hit_gtr200_yt2);
   fChain->SetBranchAddress("rk_hit_gtr200_yt3", &rk_hit_gtr200_yt3, &b_rk_hit_gtr200_yt3);
   fChain->SetBranchAddress("rk_hit_gtr200_yt4", &rk_hit_gtr200_yt4, &b_rk_hit_gtr200_yt4);
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
   fChain->SetBranchAddress("rk_hit_gtr300_xt3", &rk_hit_gtr300_xt3, &b_rk_hit_gtr300_xt3);
   fChain->SetBranchAddress("rk_hit_gtr300_xt4", &rk_hit_gtr300_xt4, &b_rk_hit_gtr300_xt4);
   fChain->SetBranchAddress("rk_hit_gtr300_yt2", &rk_hit_gtr300_yt2, &b_rk_hit_gtr300_yt2);
   fChain->SetBranchAddress("rk_hit_gtr300_yt3", &rk_hit_gtr300_yt3, &b_rk_hit_gtr300_yt3);
   fChain->SetBranchAddress("rk_hit_gtr300_yt4", &rk_hit_gtr300_yt4, &b_rk_hit_gtr300_yt4);
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
   fChain->SetBranchAddress("rk_fit_sts_mid", &rk_fit_sts_mid, &b_rk_fit_sts_mid);
   fChain->SetBranchAddress("rk_fit_sts_x", &rk_fit_sts_x, &b_rk_fit_sts_x);
   fChain->SetBranchAddress("rk_fit_sts_y", &rk_fit_sts_y, &b_rk_fit_sts_y);
   fChain->SetBranchAddress("rk_fit_sts_gx", &rk_fit_sts_gx, &b_rk_fit_sts_gx);
   fChain->SetBranchAddress("rk_fit_sts_gy", &rk_fit_sts_gy, &b_rk_fit_sts_gy);
   fChain->SetBranchAddress("rk_fit_sts_gz", &rk_fit_sts_gz, &b_rk_fit_sts_gz);
   fChain->SetBranchAddress("rk_fit_sts_mom_x", &rk_fit_sts_mom_x, &b_rk_fit_sts_mom_x);
   fChain->SetBranchAddress("rk_fit_sts_mom_y", &rk_fit_sts_mom_y, &b_rk_fit_sts_mom_y);
   fChain->SetBranchAddress("rk_fit_sts_mom_z", &rk_fit_sts_mom_z, &b_rk_fit_sts_mom_z);
   fChain->SetBranchAddress("rk_fit_sts_mom_gx", &rk_fit_sts_mom_gx, &b_rk_fit_sts_mom_gx);
   fChain->SetBranchAddress("rk_fit_sts_mom_gy", &rk_fit_sts_mom_gy, &b_rk_fit_sts_mom_gy);
   fChain->SetBranchAddress("rk_fit_sts_mom_gz", &rk_fit_sts_mom_gz, &b_rk_fit_sts_mom_gz);
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
   fChain->SetBranchAddress("rk_res_sts_x", &rk_res_sts_x, &b_rk_res_sts_x);
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
   fChain->SetBranchAddress("rk_pair_minus_sts_t", &rk_pair_minus_sts_t, &b_rk_pair_minus_sts_t);
   fChain->SetBranchAddress("rk_pair_minus_lg_t", &rk_pair_minus_lg_t, &b_rk_pair_minus_lg_t);
   fChain->SetBranchAddress("rk_pair_plus_track_id", &rk_pair_plus_track_id, &b_rk_pair_plus_track_id);
   fChain->SetBranchAddress("rk_pair_plus_gtr300_mid", &rk_pair_plus_gtr300_mid, &b_rk_pair_plus_gtr300_mid);
   fChain->SetBranchAddress("rk_pair_plus_chi_square", &rk_pair_plus_chi_square, &b_rk_pair_plus_chi_square);
   fChain->SetBranchAddress("rk_pair_plus_mom_gx", &rk_pair_plus_mom_gx, &b_rk_pair_plus_mom_gx);
   fChain->SetBranchAddress("rk_pair_plus_mom_gy", &rk_pair_plus_mom_gy, &b_rk_pair_plus_mom_gy);
   fChain->SetBranchAddress("rk_pair_plus_mom_gz", &rk_pair_plus_mom_gz, &b_rk_pair_plus_mom_gz);
   fChain->SetBranchAddress("rk_pair_plus_sts_t", &rk_pair_plus_sts_t, &b_rk_pair_plus_sts_t);
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
   fChain->SetBranchAddress("rk_pair_minus_sts_pos_refit_gx", &rk_pair_minus_sts_pos_refit_gx, &b_rk_pair_minus_sts_pos_refit_gx);
   fChain->SetBranchAddress("rk_pair_minus_sts_pos_refit_gy", &rk_pair_minus_sts_pos_refit_gy, &b_rk_pair_minus_sts_pos_refit_gy);
   fChain->SetBranchAddress("rk_pair_minus_sts_pos_refit_gz", &rk_pair_minus_sts_pos_refit_gz, &b_rk_pair_minus_sts_pos_refit_gz);
   fChain->SetBranchAddress("rk_pair_minus_gtr100_pos_refit_gx", &rk_pair_minus_gtr100_pos_refit_gx, &b_rk_pair_minus_gtr100_pos_refit_gx);
   fChain->SetBranchAddress("rk_pair_minus_gtr100_pos_refit_gy", &rk_pair_minus_gtr100_pos_refit_gy, &b_rk_pair_minus_gtr100_pos_refit_gy);
   fChain->SetBranchAddress("rk_pair_minus_gtr100_pos_refit_gz", &rk_pair_minus_gtr100_pos_refit_gz, &b_rk_pair_minus_gtr100_pos_refit_gz);
   fChain->SetBranchAddress("rk_pair_minus_gtr200_pos_refit_gx", &rk_pair_minus_gtr200_pos_refit_gx, &b_rk_pair_minus_gtr200_pos_refit_gx);
   fChain->SetBranchAddress("rk_pair_minus_gtr200_pos_refit_gy", &rk_pair_minus_gtr200_pos_refit_gy, &b_rk_pair_minus_gtr200_pos_refit_gy);
   fChain->SetBranchAddress("rk_pair_minus_gtr200_pos_refit_gz", &rk_pair_minus_gtr200_pos_refit_gz, &b_rk_pair_minus_gtr200_pos_refit_gz);
   fChain->SetBranchAddress("rk_pair_minus_gtr300_pos_refit_gx", &rk_pair_minus_gtr300_pos_refit_gx, &b_rk_pair_minus_gtr300_pos_refit_gx);
   fChain->SetBranchAddress("rk_pair_minus_gtr300_pos_refit_gy", &rk_pair_minus_gtr300_pos_refit_gy, &b_rk_pair_minus_gtr300_pos_refit_gy);
   fChain->SetBranchAddress("rk_pair_minus_gtr300_pos_refit_gz", &rk_pair_minus_gtr300_pos_refit_gz, &b_rk_pair_minus_gtr300_pos_refit_gz);
   fChain->SetBranchAddress("rk_pair_plus_sts_pos_refit_gx", &rk_pair_plus_sts_pos_refit_gx, &b_rk_pair_plus_sts_pos_refit_gx);
   fChain->SetBranchAddress("rk_pair_plus_sts_pos_refit_gy", &rk_pair_plus_sts_pos_refit_gy, &b_rk_pair_plus_sts_pos_refit_gy);
   fChain->SetBranchAddress("rk_pair_plus_sts_pos_refit_gz", &rk_pair_plus_sts_pos_refit_gz, &b_rk_pair_plus_sts_pos_refit_gz);
   fChain->SetBranchAddress("rk_pair_plus_gtr100_pos_refit_gx", &rk_pair_plus_gtr100_pos_refit_gx, &b_rk_pair_plus_gtr100_pos_refit_gx);
   fChain->SetBranchAddress("rk_pair_plus_gtr100_pos_refit_gy", &rk_pair_plus_gtr100_pos_refit_gy, &b_rk_pair_plus_gtr100_pos_refit_gy);
   fChain->SetBranchAddress("rk_pair_plus_gtr100_pos_refit_gz", &rk_pair_plus_gtr100_pos_refit_gz, &b_rk_pair_plus_gtr100_pos_refit_gz);
   fChain->SetBranchAddress("rk_pair_plus_gtr200_pos_refit_gx", &rk_pair_plus_gtr200_pos_refit_gx, &b_rk_pair_plus_gtr200_pos_refit_gx);
   fChain->SetBranchAddress("rk_pair_plus_gtr200_pos_refit_gy", &rk_pair_plus_gtr200_pos_refit_gy, &b_rk_pair_plus_gtr200_pos_refit_gy);
   fChain->SetBranchAddress("rk_pair_plus_gtr200_pos_refit_gz", &rk_pair_plus_gtr200_pos_refit_gz, &b_rk_pair_plus_gtr200_pos_refit_gz);
   fChain->SetBranchAddress("rk_pair_plus_gtr300_pos_refit_gx", &rk_pair_plus_gtr300_pos_refit_gx, &b_rk_pair_plus_gtr300_pos_refit_gx);
   fChain->SetBranchAddress("rk_pair_plus_gtr300_pos_refit_gy", &rk_pair_plus_gtr300_pos_refit_gy, &b_rk_pair_plus_gtr300_pos_refit_gy);
   fChain->SetBranchAddress("rk_pair_plus_gtr300_pos_refit_gz", &rk_pair_plus_gtr300_pos_refit_gz, &b_rk_pair_plus_gtr300_pos_refit_gz);
   fChain->SetBranchAddress("rk_pair_minus_sts_mom_refit_gx", &rk_pair_minus_sts_mom_refit_gx, &b_rk_pair_minus_sts_mom_refit_gx);
   fChain->SetBranchAddress("rk_pair_minus_sts_mom_refit_gy", &rk_pair_minus_sts_mom_refit_gy, &b_rk_pair_minus_sts_mom_refit_gy);
   fChain->SetBranchAddress("rk_pair_minus_sts_mom_refit_gz", &rk_pair_minus_sts_mom_refit_gz, &b_rk_pair_minus_sts_mom_refit_gz);
   fChain->SetBranchAddress("rk_pair_minus_gtr100_mom_refit_gx", &rk_pair_minus_gtr100_mom_refit_gx, &b_rk_pair_minus_gtr100_mom_refit_gx);
   fChain->SetBranchAddress("rk_pair_minus_gtr100_mom_refit_gy", &rk_pair_minus_gtr100_mom_refit_gy, &b_rk_pair_minus_gtr100_mom_refit_gy);
   fChain->SetBranchAddress("rk_pair_minus_gtr100_mom_refit_gz", &rk_pair_minus_gtr100_mom_refit_gz, &b_rk_pair_minus_gtr100_mom_refit_gz);
   fChain->SetBranchAddress("rk_pair_minus_gtr200_mom_refit_gx", &rk_pair_minus_gtr200_mom_refit_gx, &b_rk_pair_minus_gtr200_mom_refit_gx);
   fChain->SetBranchAddress("rk_pair_minus_gtr200_mom_refit_gy", &rk_pair_minus_gtr200_mom_refit_gy, &b_rk_pair_minus_gtr200_mom_refit_gy);
   fChain->SetBranchAddress("rk_pair_minus_gtr200_mom_refit_gz", &rk_pair_minus_gtr200_mom_refit_gz, &b_rk_pair_minus_gtr200_mom_refit_gz);
   fChain->SetBranchAddress("rk_pair_minus_gtr300_mom_refit_gx", &rk_pair_minus_gtr300_mom_refit_gx, &b_rk_pair_minus_gtr300_mom_refit_gx);
   fChain->SetBranchAddress("rk_pair_minus_gtr300_mom_refit_gy", &rk_pair_minus_gtr300_mom_refit_gy, &b_rk_pair_minus_gtr300_mom_refit_gy);
   fChain->SetBranchAddress("rk_pair_minus_gtr300_mom_refit_gz", &rk_pair_minus_gtr300_mom_refit_gz, &b_rk_pair_minus_gtr300_mom_refit_gz);
   fChain->SetBranchAddress("rk_pair_plus_sts_mom_refit_gx", &rk_pair_plus_sts_mom_refit_gx, &b_rk_pair_plus_sts_mom_refit_gx);
   fChain->SetBranchAddress("rk_pair_plus_sts_mom_refit_gy", &rk_pair_plus_sts_mom_refit_gy, &b_rk_pair_plus_sts_mom_refit_gy);
   fChain->SetBranchAddress("rk_pair_plus_sts_mom_refit_gz", &rk_pair_plus_sts_mom_refit_gz, &b_rk_pair_plus_sts_mom_refit_gz);
   fChain->SetBranchAddress("rk_pair_plus_gtr100_mom_refit_gx", &rk_pair_plus_gtr100_mom_refit_gx, &b_rk_pair_plus_gtr100_mom_refit_gx);
   fChain->SetBranchAddress("rk_pair_plus_gtr100_mom_refit_gy", &rk_pair_plus_gtr100_mom_refit_gy, &b_rk_pair_plus_gtr100_mom_refit_gy);
   fChain->SetBranchAddress("rk_pair_plus_gtr100_mom_refit_gz", &rk_pair_plus_gtr100_mom_refit_gz, &b_rk_pair_plus_gtr100_mom_refit_gz);
   fChain->SetBranchAddress("rk_pair_plus_gtr200_mom_refit_gx", &rk_pair_plus_gtr200_mom_refit_gx, &b_rk_pair_plus_gtr200_mom_refit_gx);
   fChain->SetBranchAddress("rk_pair_plus_gtr200_mom_refit_gy", &rk_pair_plus_gtr200_mom_refit_gy, &b_rk_pair_plus_gtr200_mom_refit_gy);
   fChain->SetBranchAddress("rk_pair_plus_gtr200_mom_refit_gz", &rk_pair_plus_gtr200_mom_refit_gz, &b_rk_pair_plus_gtr200_mom_refit_gz);
   fChain->SetBranchAddress("rk_pair_plus_gtr300_mom_refit_gx", &rk_pair_plus_gtr300_mom_refit_gx, &b_rk_pair_plus_gtr300_mom_refit_gx);
   fChain->SetBranchAddress("rk_pair_plus_gtr300_mom_refit_gy", &rk_pair_plus_gtr300_mom_refit_gy, &b_rk_pair_plus_gtr300_mom_refit_gy);
   fChain->SetBranchAddress("rk_pair_plus_gtr300_mom_refit_gz", &rk_pair_plus_gtr300_mom_refit_gz, &b_rk_pair_plus_gtr300_mom_refit_gz);
   fChain->SetBranchAddress("rk_pair_minus_sts_res_refit_x", &rk_pair_minus_sts_res_refit_x, &b_rk_pair_minus_sts_res_refit_x);
   fChain->SetBranchAddress("rk_pair_minus_sts_res_refit_y", &rk_pair_minus_sts_res_refit_y, &b_rk_pair_minus_sts_res_refit_y);
   fChain->SetBranchAddress("rk_pair_minus_sts_res_refit_z", &rk_pair_minus_sts_res_refit_z, &b_rk_pair_minus_sts_res_refit_z);
   fChain->SetBranchAddress("rk_pair_minus_gtr100_res_refit_x", &rk_pair_minus_gtr100_res_refit_x, &b_rk_pair_minus_gtr100_res_refit_x);
   fChain->SetBranchAddress("rk_pair_minus_gtr100_res_refit_y", &rk_pair_minus_gtr100_res_refit_y, &b_rk_pair_minus_gtr100_res_refit_y);
   fChain->SetBranchAddress("rk_pair_minus_gtr100_res_refit_z", &rk_pair_minus_gtr100_res_refit_z, &b_rk_pair_minus_gtr100_res_refit_z);
   fChain->SetBranchAddress("rk_pair_minus_gtr200_res_refit_x", &rk_pair_minus_gtr200_res_refit_x, &b_rk_pair_minus_gtr200_res_refit_x);
   fChain->SetBranchAddress("rk_pair_minus_gtr200_res_refit_y", &rk_pair_minus_gtr200_res_refit_y, &b_rk_pair_minus_gtr200_res_refit_y);
   fChain->SetBranchAddress("rk_pair_minus_gtr200_res_refit_z", &rk_pair_minus_gtr200_res_refit_z, &b_rk_pair_minus_gtr200_res_refit_z);
   fChain->SetBranchAddress("rk_pair_minus_gtr300_res_refit_x", &rk_pair_minus_gtr300_res_refit_x, &b_rk_pair_minus_gtr300_res_refit_x);
   fChain->SetBranchAddress("rk_pair_minus_gtr300_res_refit_y", &rk_pair_minus_gtr300_res_refit_y, &b_rk_pair_minus_gtr300_res_refit_y);
   fChain->SetBranchAddress("rk_pair_minus_gtr300_res_refit_z", &rk_pair_minus_gtr300_res_refit_z, &b_rk_pair_minus_gtr300_res_refit_z);
   fChain->SetBranchAddress("rk_pair_plus_sts_res_refit_x", &rk_pair_plus_sts_res_refit_x, &b_rk_pair_plus_sts_res_refit_x);
   fChain->SetBranchAddress("rk_pair_plus_sts_res_refit_y", &rk_pair_plus_sts_res_refit_y, &b_rk_pair_plus_sts_res_refit_y);
   fChain->SetBranchAddress("rk_pair_plus_sts_res_refit_z", &rk_pair_plus_sts_res_refit_z, &b_rk_pair_plus_sts_res_refit_z);
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

   outtree->Branch("run_id",            &run_id  , "run_id/I"             );
   outtree->Branch("event_id",          &event_id, "event_id/I"         );
   outtree->Branch("spill_id",          &spill_id, "spill_id/I"          );
   outtree->Branch("timestamp_in_spill",&timestamp_in_spill);
   outtree->Branch("trigger_fine_time", &trigger_fine_time);
   outtree->Branch("n_fill",            &n_fill           );
   outtree->Branch("n_sts_hits",        &n_sts_hits  );
   outtree->Branch("sts_hit_id",        &sts_hit_id  );
   outtree->Branch("sts_hit_mid",       &sts_hit_mid );
   outtree->Branch("sts_hit_cid",       &sts_hit_cid );
   outtree->Branch("sts_hit_x",         &sts_hit_x  );
   outtree->Branch("sts_hit_gx",        &sts_hit_gx );
   outtree->Branch("sts_hit_gz",        &sts_hit_gz );
   outtree->Branch("sts_hit_t",         &sts_hit_t  );
   outtree->Branch("sts_hit_adc",       &sts_hit_adc );
   outtree->Branch("n_gtr100x_hits",    &n_gtr100x_hits);
   outtree->Branch("gtr100x_hit_id",    &gtr100x_hit_id);
   outtree->Branch("gtr100x_hit_mid",   &gtr100x_hit_mid);
   outtree->Branch("gtr100x_hit_cid",   &gtr100x_hit_cid);
   outtree->Branch("gtr100x_hit_x",               &gtr100x_hit_x);
   outtree->Branch("gtr100x_hit_tx",              &gtr100x_hit_tx);
   outtree->Branch("gtr100x_hit_gx",              &gtr100x_hit_gx);
   outtree->Branch("gtr100x_hit_gz",              &gtr100x_hit_gz);
   outtree->Branch("gtr100x_hit_t",               &gtr100x_hit_t);
   outtree->Branch("gtr100x_hit_adc",             &gtr100x_hit_adc);
   outtree->Branch("n_gtr200x_hits",              &n_gtr200x_hits );
   outtree->Branch("gtr200x_hit_id",              &gtr200x_hit_id );
   outtree->Branch("gtr200x_hit_mid",             &gtr200x_hit_mid);
   outtree->Branch("gtr200x_hit_cid",             &gtr200x_hit_cid);
   outtree->Branch("gtr200x_hit_x",               &gtr200x_hit_x );
   outtree->Branch("gtr200x_hit_tx",              &gtr200x_hit_tx);
   outtree->Branch("gtr200x_hit_gx",              &gtr200x_hit_gx);
   outtree->Branch("gtr200x_hit_gz",              &gtr200x_hit_gz);
   outtree->Branch("gtr200x_hit_t",               &gtr200x_hit_t );
   outtree->Branch("gtr200x_hit_adc",             &gtr200x_hit_adc);
   outtree->Branch("n_gtr300x_hits",              &n_gtr300x_hits);
   outtree->Branch("gtr300x_hit_id",              &gtr300x_hit_id);
   outtree->Branch("gtr300x_hit_mid",             &gtr300x_hit_mid);
   outtree->Branch("gtr300x_hit_cid",             &gtr300x_hit_cid);
   outtree->Branch("gtr300x_hit_x",               &gtr300x_hit_x );
   outtree->Branch("gtr300x_hit_tx",              &gtr300x_hit_tx);
   outtree->Branch("gtr300x_hit_gx",              &gtr300x_hit_gx);
   outtree->Branch("gtr300x_hit_gz",              &gtr300x_hit_gz);
   outtree->Branch("gtr300x_hit_t",               &gtr300x_hit_t );
   outtree->Branch("gtr300x_hit_adc",             &gtr300x_hit_adc);
   outtree->Branch("n_gtr100y_hits",              &n_gtr100y_hits);
   outtree->Branch("gtr100y_hit_id",              &gtr100y_hit_id);
   outtree->Branch("gtr100y_hit_mid",             &gtr100y_hit_mid);
   outtree->Branch("gtr100y_hit_cid",             &gtr100y_hit_cid);
   outtree->Branch("gtr100y_hit_y",               &gtr100y_hit_y );
   outtree->Branch("gtr100y_hit_ty",              &gtr100y_hit_ty);
   outtree->Branch("gtr100y_hit_t",               &gtr100y_hit_t );
   outtree->Branch("gtr100y_hit_adc",             &gtr100y_hit_adc);
   outtree->Branch("n_gtr100yb_hits",             &n_gtr100yb_hits);
   outtree->Branch("gtr100yb_hit_id",             &gtr100yb_hit_id);
   outtree->Branch("gtr100yb_hit_mid",            &gtr100yb_hit_mid);
   outtree->Branch("gtr100yb_hit_cid",            &gtr100yb_hit_cid);
   outtree->Branch("gtr100yb_hit_y",              &gtr100yb_hit_y);
   outtree->Branch("gtr100yb_hit_ty",             &gtr100yb_hit_ty );
   outtree->Branch("gtr100yb_hit_t",              &gtr100yb_hit_t);
   outtree->Branch("gtr100yb_hit_adc",            &gtr100yb_hit_adc);
   outtree->Branch("n_gtr200y_hits",              &n_gtr200y_hits);
   outtree->Branch("gtr200y_hit_id",              &gtr200y_hit_id);
   outtree->Branch("gtr200y_hit_mid",             &gtr200y_hit_mid);
   outtree->Branch("gtr200y_hit_cid",             &gtr200y_hit_cid);
   outtree->Branch("gtr200y_hit_y",               &gtr200y_hit_y);
   outtree->Branch("gtr200y_hit_ty",              &gtr200y_hit_ty);
   outtree->Branch("gtr200y_hit_t",               &gtr200y_hit_t);
   outtree->Branch("gtr200y_hit_adc",             &gtr200y_hit_adc);
   outtree->Branch("n_gtr300y_hits",              &n_gtr300y_hits);
   outtree->Branch("gtr300y_hit_id",              &gtr300y_hit_id);
   outtree->Branch("gtr300y_hit_mid",             &gtr300y_hit_mid);
   outtree->Branch("gtr300y_hit_cid",             &gtr300y_hit_cid);
   outtree->Branch("gtr300y_hit_y",               &gtr300y_hit_y);
   outtree->Branch("gtr300y_hit_ty",              &gtr300y_hit_ty);
   outtree->Branch("gtr300y_hit_t",               &gtr300y_hit_t);
   outtree->Branch("gtr300y_hit_adc",             &gtr300y_hit_adc);
   outtree->Branch("n_hbd_hits",                  &n_hbd_hits      );
   outtree->Branch("hbd_hit_id",                  &hbd_hit_id  );
   outtree->Branch("hbd_hit_mid",                 &hbd_hit_mid );
   outtree->Branch("hbd_hit_cid",                 &hbd_hit_cid );
   outtree->Branch("hbd_hit_x",                   &hbd_hit_x);
   outtree->Branch("hbd_hit_y",                   &hbd_hit_y);
   outtree->Branch("hbd_hit_gx",                  &hbd_hit_gx);
   outtree->Branch("hbd_hit_gy",                  &hbd_hit_gy);
   outtree->Branch("hbd_hit_gz",                  &hbd_hit_gz);
   outtree->Branch("hbd_hit_t",                   &hbd_hit_t );
   outtree->Branch("hbd_hit_adc",                 &hbd_hit_adc);
   outtree->Branch("n_sts_clusters",              &n_sts_clusters);
   outtree->Branch("sts_cluster_id",              &sts_cluster_id);
   outtree->Branch("sts_cluster_mid",             &sts_cluster_mid);
   outtree->Branch("sts_cluster_x",               &sts_cluster_x);
   outtree->Branch("sts_cluster_gx",              &sts_cluster_gx);
   outtree->Branch("sts_cluster_gz",              &sts_cluster_gz);
   outtree->Branch("sts_cluster_adc",             &sts_cluster_adc);
   outtree->Branch("sts_cluster_t",               &sts_cluster_t );
   outtree->Branch("sts_cluster_size",            &sts_cluster_size);
   outtree->Branch("sts_cluster_fit_x",           &sts_cluster_fit_x);
   outtree->Branch("sts_cluster_fit_t",           &sts_cluster_fit_t);
   outtree->Branch("sts_cluster_fit_adc",         &sts_cluster_fit_adc);
   outtree->Branch("sts_cluster_fit_chi2",        &sts_cluster_fit_chi2);
   outtree->Branch("n_gtr100x_clusters",          &n_gtr100x_clusters );
   outtree->Branch("gtr100x_cluster_id",          &gtr100x_cluster_id );
   outtree->Branch("gtr100x_cluster_mid",         &gtr100x_cluster_mid);
   outtree->Branch("gtr100x_cluster_x",           &gtr100x_cluster_x );
   outtree->Branch("gtr100x_cluster_gx",          &gtr100x_cluster_gx);
   outtree->Branch("gtr100x_cluster_gz",          &gtr100x_cluster_gz);
   outtree->Branch("gtr100x_cluster_adc",         &gtr100x_cluster_adc);
   outtree->Branch("gtr100x_cluster_t",           &gtr100x_cluster_t );
   outtree->Branch("gtr100x_cluster_t2",          &gtr100x_cluster_t2);
   outtree->Branch("gtr100x_cluster_tx",          &gtr100x_cluster_tx);
   outtree->Branch("gtr100x_cluster_the",         &gtr100x_cluster_the);
   outtree->Branch("gtr100x_cluster_gtx",         &gtr100x_cluster_gtx);
   outtree->Branch("gtr100x_cluster_nc",          &gtr100x_cluster_nc);
   outtree->Branch("gtr100x_cluster_size",        &gtr100x_cluster_size);
   outtree->Branch("n_gtr200x_clusters",          &n_gtr200x_clusters );
   outtree->Branch("gtr200x_cluster_id",          &gtr200x_cluster_id );
   outtree->Branch("gtr200x_cluster_mid",         &gtr200x_cluster_mid);
   outtree->Branch("gtr200x_cluster_x",           &gtr200x_cluster_x );
   outtree->Branch("gtr200x_cluster_gx",          &gtr200x_cluster_gx);
   outtree->Branch("gtr200x_cluster_gz",          &gtr200x_cluster_gz);
   outtree->Branch("gtr200x_cluster_adc",         &gtr200x_cluster_adc);
   outtree->Branch("gtr200x_cluster_t",           &gtr200x_cluster_t );
   outtree->Branch("gtr200x_cluster_t2",          &gtr200x_cluster_t2);
   outtree->Branch("gtr200x_cluster_tx",          &gtr200x_cluster_tx);
   outtree->Branch("gtr200x_cluster_the",         &gtr200x_cluster_the);
   outtree->Branch("gtr200x_cluster_nc",          &gtr200x_cluster_nc);
   outtree->Branch("gtr200x_cluster_gtx",         &gtr200x_cluster_gtx);
   outtree->Branch("gtr200x_cluster_size",        &gtr200x_cluster_size);
   outtree->Branch("n_gtr300x_clusters",          &n_gtr300x_clusters );
   outtree->Branch("gtr300x_cluster_id",          &gtr300x_cluster_id );
   outtree->Branch("gtr300x_cluster_mid",         &gtr300x_cluster_mid);
   outtree->Branch("gtr300x_cluster_x",           &gtr300x_cluster_x );
   outtree->Branch("gtr300x_cluster_gx",          &gtr300x_cluster_gx);
   outtree->Branch("gtr300x_cluster_gz",          &gtr300x_cluster_gz );
   outtree->Branch("gtr300x_cluster_adc",         &gtr300x_cluster_adc);
   outtree->Branch("gtr300x_cluster_t",           &gtr300x_cluster_t );
   outtree->Branch("gtr300x_cluster_t2",          &gtr300x_cluster_t2);
   outtree->Branch("gtr300x_cluster_tx",          &gtr300x_cluster_tx);
   outtree->Branch("gtr300x_cluster_the",         &gtr300x_cluster_the);
   outtree->Branch("gtr300x_cluster_nc",          &gtr300x_cluster_nc);
   outtree->Branch("gtr300x_cluster_gtx",         &gtr300x_cluster_gtx );
   outtree->Branch("gtr300x_cluster_size",        &gtr300x_cluster_size);
   outtree->Branch("n_gtr100y_clusters",          &n_gtr100y_clusters);
   outtree->Branch("gtr100y_cluster_id",          &gtr100y_cluster_id);
   outtree->Branch("gtr100y_cluster_mid",         &gtr100y_cluster_mid );
   outtree->Branch("gtr100y_cluster_y",           &gtr100y_cluster_y   );
   outtree->Branch("gtr100y_cluster_adc",         &gtr100y_cluster_adc);
   outtree->Branch("gtr100y_cluster_t",           &gtr100y_cluster_t );
   outtree->Branch("gtr100y_cluster_t2",          &gtr100y_cluster_t2);
   outtree->Branch("gtr100y_cluster_ty",          &gtr100y_cluster_ty);
   outtree->Branch("gtr100y_cluster_the",         &gtr100y_cluster_the);
   outtree->Branch("gtr100y_cluster_nc",          &gtr100y_cluster_nc);
   outtree->Branch("gtr100y_cluster_size",        &gtr100y_cluster_size);
   outtree->Branch("n_gtr100yb_clusters",         &n_gtr100yb_clusters);
   outtree->Branch("gtr100yb_cluster_id",         &gtr100yb_cluster_id );
   outtree->Branch("gtr100yb_cluster_mid",        &gtr100yb_cluster_mid);
   outtree->Branch("gtr100yb_cluster_y",          &gtr100yb_cluster_y );
   outtree->Branch("gtr100yb_cluster_adc",        &gtr100yb_cluster_adc);
   outtree->Branch("gtr100yb_cluster_t",          &gtr100yb_cluster_t );
   outtree->Branch("gtr100yb_cluster_t2",         &gtr100yb_cluster_t2);
   outtree->Branch("gtr100yb_cluster_ty",         &gtr100yb_cluster_ty);
   outtree->Branch("gtr100yb_cluster_the",        &gtr100yb_cluster_the);
   outtree->Branch("gtr100yb_cluster_nc",         &gtr100yb_cluster_nc);
   outtree->Branch("gtr100yb_cluster_size",     &gtr100yb_cluster_size);
   outtree->Branch("n_gtr200y_clusters",        &n_gtr200y_clusters);
   outtree->Branch("gtr200y_cluster_id",        &gtr200y_cluster_id);
   outtree->Branch("gtr200y_cluster_mid",       &gtr200y_cluster_mid);
   outtree->Branch("gtr200y_cluster_y",         &gtr200y_cluster_y);
   outtree->Branch("gtr200y_cluster_adc",       &gtr200y_cluster_adc);
   outtree->Branch("gtr200y_cluster_t",         &gtr200y_cluster_t);
   outtree->Branch("gtr200y_cluster_t2",        &gtr200y_cluster_t2);
   outtree->Branch("gtr200y_cluster_ty",        &gtr200y_cluster_ty);
   outtree->Branch("gtr200y_cluster_the",       &gtr200y_cluster_the);
   outtree->Branch("gtr200y_cluster_nc",        &gtr200y_cluster_nc);
   outtree->Branch("gtr200y_cluster_size",      &gtr200y_cluster_size);
   outtree->Branch("n_gtr300y_clusters",        &n_gtr300y_clusters);
   outtree->Branch("gtr300y_cluster_id",        &gtr300y_cluster_id);
   outtree->Branch("gtr300y_cluster_mid",       &gtr300y_cluster_mid);
   outtree->Branch("gtr300y_cluster_y",         &gtr300y_cluster_y);
   outtree->Branch("gtr300y_cluster_adc",       &gtr300y_cluster_adc);
   outtree->Branch("gtr300y_cluster_t",         &gtr300y_cluster_t);
   outtree->Branch("gtr300y_cluster_t2",        &gtr300y_cluster_t2);
   outtree->Branch("gtr300y_cluster_ty",        &gtr300y_cluster_ty);
   outtree->Branch("gtr300y_cluster_the",       &gtr300y_cluster_the);
   outtree->Branch("gtr300y_cluster_nc",        &gtr300y_cluster_nc);
   outtree->Branch("gtr300y_cluster_size",      &gtr300y_cluster_size);
   outtree->Branch("n_hbd_clusters",            &n_hbd_clusters);
   outtree->Branch("hbd_cluster_id",            &hbd_cluster_id);
   outtree->Branch("hbd_cluster_mid",           &hbd_cluster_mid);
   outtree->Branch("hbd_cluster_x",             &hbd_cluster_x);
   outtree->Branch("hbd_cluster_y",             &hbd_cluster_y);
   outtree->Branch("hbd_cluster_gx",            &hbd_cluster_gx);
   outtree->Branch("hbd_cluster_gy",            &hbd_cluster_gy);
   outtree->Branch("hbd_cluster_gz",            &hbd_cluster_gz);
   outtree->Branch("hbd_cluster_adc",           &hbd_cluster_adc);
   outtree->Branch("hbd_cluster_max_cid",       &hbd_cluster_max_cid);
   outtree->Branch("hbd_cluster_t",             &hbd_cluster_t);
   outtree->Branch("hbd_cluster_ftime",         &hbd_cluster_ftime);
   outtree->Branch("hbd_cluster_tdiff",         &hbd_cluster_tdiff);
   outtree->Branch("hbd_cluster_size",          &hbd_cluster_size);
   outtree->Branch("hbd_cluster_eprob",         &hbd_cluster_eprob);
   outtree->Branch("hbd_cluster_cprob",         &hbd_cluster_cprob);
   outtree->Branch("n_hbd_clusters_wotime",     &n_hbd_clusters_wotime);
   outtree->Branch("hbd_cluster_wotime_id",     &hbd_cluster_wotime_id);
   outtree->Branch("hbd_cluster_wotime_mid",    &hbd_cluster_wotime_mid);
   outtree->Branch("hbd_cluster_wotime_x",      &hbd_cluster_wotime_x);
   outtree->Branch("hbd_cluster_wotime_y",      &hbd_cluster_wotime_y);
   outtree->Branch("hbd_cluster_wotime_gx",     &hbd_cluster_wotime_gx);
   outtree->Branch("hbd_cluster_wotime_gy",     &hbd_cluster_wotime_gy);
   outtree->Branch("hbd_cluster_wotime_gz",     &hbd_cluster_wotime_gz);
   outtree->Branch("hbd_cluster_wotime_adc",    &hbd_cluster_wotime_adc);
   outtree->Branch("hbd_cluster_wotime_max_cid",&hbd_cluster_wotime_max_cid);
   outtree->Branch("hbd_cluster_wotime_t",    &hbd_cluster_wotime_t);
   outtree->Branch("hbd_cluster_wotime_ftime",&hbd_cluster_wotime_ftime);
   outtree->Branch("hbd_cluster_wotime_tdiff",&hbd_cluster_wotime_tdiff);
   outtree->Branch("hbd_cluster_wotime_size", &hbd_cluster_wotime_size );
   outtree->Branch("hbd_cluster_wotime_eprob",&hbd_cluster_wotime_eprob);
   outtree->Branch("hbd_cluster_wotime_cprob",&hbd_cluster_wotime_cprob);
   outtree->Branch("n_lg_hits",               &n_lg_hits);
   outtree->Branch("lg_hit_id",               &lg_hit_id);
   outtree->Branch("lg_hit_mid",              &lg_hit_mid);
   outtree->Branch("lg_hit_cid",              &lg_hit_cid);
   outtree->Branch("lg_hit_x",                &lg_hit_x );
   outtree->Branch("lg_hit_y",                &lg_hit_y );
   outtree->Branch("lg_hit_z",                &lg_hit_z );
   outtree->Branch("lg_hit_gx"  ,             &lg_hit_gx);
   outtree->Branch("lg_hit_gy"  ,             &lg_hit_gy);
   outtree->Branch("lg_hit_gz"  ,             &lg_hit_gz);
   outtree->Branch("lg_hit_adc",             &lg_hit_adc);
   outtree->Branch("lg_hit_t",                &lg_hit_t );
   outtree->Branch("lg_hit_wofit_adc",        &lg_hit_wofit_adc);
   outtree->Branch("lg_hit_wofit_t",          &lg_hit_wofit_t);
   outtree->Branch("lg_hit_npeaks",           &lg_hit_npeaks);
   outtree->Branch("lg_hit_fflag",            &lg_hit_fflag);
   outtree->Branch("pre_n_lg_hits",               &pre_n_lg_hits);
//   outtree->Branch("pre_lg_hit_id",               &pre_lg_hit_id);
//   outtree->Branch("pre_lg_hit_mid",              &pre_lg_hit_mid);
//   outtree->Branch("pre_lg_hit_cid",              &pre_lg_hit_cid);
//   outtree->Branch("pre_lg_hit_x",                &pre_lg_hit_x );
//   outtree->Branch("pre_lg_hit_y",                &pre_lg_hit_y );
//   outtree->Branch("pre_lg_hit_z",                &pre_lg_hit_z );
//   outtree->Branch("pre_lg_hit_gx"  ,             &pre_lg_hit_gx);
//   outtree->Branch("pre_lg_hit_gy"  ,             &pre_lg_hit_gy);
//   outtree->Branch("pre_lg_hit_gz"  ,             &pre_lg_hit_gz);
//   outtree->Branch("pre_lg_hit_adc",              &pre_lg_hit_adc);
//   outtree->Branch("pre_lg_hit_t",                &pre_lg_hit_t );
//   outtree->Branch("pre_lg_hit_wofit_adc",        &pre_lg_hit_wofit_adc);
//   outtree->Branch("pre_lg_hit_wofit_t",          &pre_lg_hit_wofit_t);
//   outtree->Branch("pre_lg_hit_npeaks",           &pre_lg_hit_npeaks);
//   outtree->Branch("pre_lg_hit_fflag",            &pre_lg_hit_fflag);

   outtree->Branch("n_lg_clusters",           &n_lg_clusters);
   outtree->Branch("lg_cluster_id",           &lg_cluster_id);
   outtree->Branch("lg_cluster_mid",          &lg_cluster_mid);
   outtree->Branch("lg_cluster_max_cid",      &lg_cluster_max_cid);
   outtree->Branch("lg_cluster_max_adc",      &lg_cluster_max_adc);
   outtree->Branch("lg_cluster_x",            &lg_cluster_x);
   outtree->Branch("lg_cluster_y",            &lg_cluster_y);
   outtree->Branch("lg_cluster_z",            &lg_cluster_z);
   outtree->Branch("lg_cluster_gx",           &lg_cluster_gx);
   outtree->Branch("lg_cluster_gy",           &lg_cluster_gy);
   outtree->Branch("lg_cluster_gz",           &lg_cluster_gz);
   outtree->Branch("lg_cluster_adc"    ,      &lg_cluster_adc);
   outtree->Branch("lg_cluster_t",            &lg_cluster_t  );
   outtree->Branch("lg_cluster_tdiff",        &lg_cluster_tdiff);
   outtree->Branch("lg_cluster_size",         &lg_cluster_size);
   outtree->Branch("n_trg_gtr_hits",          &n_trg_gtr_hits);
   outtree->Branch("trg_gtr_hit_id",          &trg_gtr_hit_id);
   outtree->Branch("trg_gtr_hit_mid",         &trg_gtr_hit_mid);
   outtree->Branch("trg_gtr_hit_cid",         &trg_gtr_hit_cid);
   outtree->Branch("trg_gtr_hit_x",           &trg_gtr_hit_x);
   outtree->Branch("trg_gtr_hit_y",           &trg_gtr_hit_y);
   outtree->Branch("trg_gtr_hit_gx",          &trg_gtr_hit_gx);
   outtree->Branch("trg_gtr_hit_gy",          &trg_gtr_hit_gy);
   outtree->Branch("trg_gtr_hit_gz",          &trg_gtr_hit_gz);
   outtree->Branch("trg_gtr_hit_t",           &trg_gtr_hit_t);
   outtree->Branch("n_trg_hbd_hits",          &n_trg_hbd_hits);
   outtree->Branch("trg_hbd_hit_id",          &trg_hbd_hit_id);
   outtree->Branch("trg_hbd_hit_mid",         &trg_hbd_hit_mid);
   outtree->Branch("trg_hbd_hit_cid",         &trg_hbd_hit_cid);
   outtree->Branch("trg_hbd_hit_x",           &trg_hbd_hit_x);
   outtree->Branch("trg_hbd_hit_y",           &trg_hbd_hit_y);
   outtree->Branch("trg_hbd_hit_gx",          &trg_hbd_hit_gx);
   outtree->Branch("trg_hbd_hit_gy",          &trg_hbd_hit_gy);
   outtree->Branch("trg_hbd_hit_gz",          &trg_hbd_hit_gz);
   outtree->Branch("trg_hbd_hit_t",           &trg_hbd_hit_t);
   outtree->Branch("n_trg_lg_hits",           &n_trg_lg_hits);
   outtree->Branch("trg_lg_hit_id",           &trg_lg_hit_id);
   outtree->Branch("trg_lg_hit_mid",          &trg_lg_hit_mid);
   outtree->Branch("trg_lg_hit_cid",          &trg_lg_hit_cid);
   outtree->Branch("trg_lg_hit_x",            &trg_lg_hit_x); 
   outtree->Branch("trg_lg_hit_y",            &trg_lg_hit_y); 
   outtree->Branch("trg_lg_hit_z",            &trg_lg_hit_z); 
   outtree->Branch("trg_lg_hit_gx",           &trg_lg_hit_gx);
   outtree->Branch("trg_lg_hit_gy",           &trg_lg_hit_gy);
   outtree->Branch("trg_lg_hit_gz",           &trg_lg_hit_gz);
   outtree->Branch("trg_lg_hit_t",            &trg_lg_hit_t);
   outtree->Branch("n_trg_tracks",            &n_trg_tracks); 
   outtree->Branch("trg_track_n_gtr_hits",    &trg_track_n_gtr_hits);
   outtree->Branch("trg_track_gtr_id",        &trg_track_gtr_id);
   outtree->Branch("trg_track_gtr_mid",       &trg_track_gtr_mid);
   outtree->Branch("trg_track_gtr_cid",       &trg_track_gtr_cid);
   outtree->Branch("trg_track_gtr_x",         &trg_track_gtr_x);
   outtree->Branch("trg_track_gtr_y",         &trg_track_gtr_y);
   outtree->Branch("trg_track_gtr_t",         &trg_track_gtr_t);
   outtree->Branch("trg_track_gtr_is_t_match",&trg_track_gtr_is_t_match);
   outtree->Branch("trg_track_n_hbd_hits",    &trg_track_n_hbd_hits);
   outtree->Branch("trg_track_hbd_id",        &trg_track_hbd_id);
   outtree->Branch("trg_track_hbd_mid",       &trg_track_hbd_mid);
   outtree->Branch("trg_track_hbd_cid",       &trg_track_hbd_cid);
   outtree->Branch("trg_track_hbd_x",         &trg_track_hbd_x);
   outtree->Branch("trg_track_hbd_y",         &trg_track_hbd_y);
   outtree->Branch("trg_track_hbd_t",         &trg_track_hbd_t);
   outtree->Branch("trg_track_hbd_is_t_match",&trg_track_hbd_is_t_match);
   outtree->Branch("trg_track_lg_id",        &trg_track_lg_id);
   outtree->Branch("trg_track_lg_mid",       &trg_track_lg_mid);
   outtree->Branch("trg_track_lg_cid",       &trg_track_lg_cid);
   outtree->Branch("trg_track_lg_x",         &trg_track_lg_x);
   outtree->Branch("trg_track_lg_y",         &trg_track_lg_y);
   outtree->Branch("trg_track_lg_t",         &trg_track_lg_t);
   outtree->Branch("n_x_cands",              &n_x_cands);
   outtree->Branch("n_y_cands",              &n_y_cands);
   outtree->Branch("n_cands",                &n_cands);
   outtree->Branch("n_selected",             &n_selected);
   outtree->Branch("n_pairs",                &n_pairs);
   outtree->Branch("n_refit_pairs",          &n_refit_pairs);

//	outtree->Branch("n_alive_tracks", &out_n_alive_tracks);

   outtree->Branch("track_id",               &out_track_id);
   outtree->Branch("has_e_hbd_cluster",      &out_has_e_hbd_cluster);
   outtree->Branch("has_e_lg_hit",           &out_has_e_lg_hit);
   outtree->Branch("is_large_residual",      &out_is_large_residual);
   outtree->Branch("is_near_target",         &out_is_near_target);
   outtree->Branch("is_cluster_used",        &out_is_cluster_used);
   outtree->Branch("is_selected",            &out_is_selected);
   outtree->Branch("x_rough_fit_chi_square", &out_x_rough_fit_chi_square);
   outtree->Branch("x_rough_fit_dist0",      &out_x_rough_fit_dist0);
   outtree->Branch("x_rough_fit_dist1",      &out_x_rough_fit_dist1);
   outtree->Branch("x_rough_fit_coef0",      &out_x_rough_fit_coef0);
   outtree->Branch("x_rough_fit_coef1",      &out_x_rough_fit_coef1);
   outtree->Branch("x_rough_fit_coef2",      &out_x_rough_fit_coef2);
   outtree->Branch("rough_fit_n_hbds",       &out_rough_fit_n_hbds);
   outtree->Branch("rough_fit_hbd_ids",      &out_rough_fit_hbd_ids);
   outtree->Branch("rough_fit_hbd_ress",     &out_rough_fit_hbd_ress);
   outtree->Branch("rough_fit_hbd_y_oks",    &out_rough_fit_hbd_y_oks);
   outtree->Branch("y_rough_fit_chi_square", &out_y_rough_fit_chi_square);
   outtree->Branch("y_rough_fit_coef0",  	   &out_y_rough_fit_coef0);
   outtree->Branch("y_rough_fit_coef1",      &out_y_rough_fit_coef1);
   outtree->Branch("chi_square",          &out_chi_square);
   outtree->Branch("n_steps",             &out_n_steps);
   outtree->Branch("n_calls",             &out_n_calls);
   outtree->Branch("rk_charge",           &out_rk_charge);
   outtree->Branch("rk_hit_init_mom_gx",  &out_rk_hit_init_mom_gx);
   outtree->Branch("rk_hit_init_mom_gy",  &out_rk_hit_init_mom_gy);
   outtree->Branch("rk_hit_init_mom_gz",  &out_rk_hit_init_mom_gz);
   outtree->Branch("rk_hit_init_pos_gx",  &out_rk_hit_init_pos_gx);
   outtree->Branch("rk_hit_init_pos_gy",  &out_rk_hit_init_pos_gy);
   outtree->Branch("rk_hit_init_pos_gz",  &out_rk_hit_init_pos_gz);
   outtree->Branch("rk_hit_sts_id",       &out_rk_hit_sts_id);
   outtree->Branch("rk_hit_sts_x",        &out_rk_hit_sts_x);
   outtree->Branch("rk_hit_sts_gx",       &out_rk_hit_sts_gx);
   outtree->Branch("rk_hit_sts_gy",       &out_rk_hit_sts_gy);
   outtree->Branch("rk_hit_sts_gz",       &out_rk_hit_sts_gz);
   outtree->Branch("rk_hit_sts_adc"     , &out_rk_hit_sts_adc);
   outtree->Branch("rk_hit_sts_t",        &out_rk_hit_sts_t);
   outtree->Branch("rk_hit_sts_chi2",     &out_rk_hit_sts_chi2);
   outtree->Branch("rk_hit_gtr100_xid",   &out_rk_hit_gtr100_xid);
   outtree->Branch("rk_hit_gtr100_yid",   &out_rk_hit_gtr100_yid);
   outtree->Branch("rk_hit_gtr100_gx",    &out_rk_hit_gtr100_gx);
   outtree->Branch("rk_hit_gtr100_gy",    &out_rk_hit_gtr100_gy);
   outtree->Branch("rk_hit_gtr100_gz",    &out_rk_hit_gtr100_gz);
   outtree->Branch("rk_hit_gtr100_xadc",  &out_rk_hit_gtr100_xadc);
   outtree->Branch("rk_hit_gtr100_yadc",  &out_rk_hit_gtr100_yadc);
   outtree->Branch("rk_hit_gtr100_xt",    &out_rk_hit_gtr100_xt);
   outtree->Branch("rk_hit_gtr100_yt",    &out_rk_hit_gtr100_yt);
   outtree->Branch("rk_hit_gtr100_xt2",   &out_rk_hit_gtr100_xt2);
   outtree->Branch("rk_hit_gtr100_yt2",   &out_rk_hit_gtr100_yt2);
   outtree->Branch("rk_hit_gtr100_tx2",   &out_rk_hit_gtr100_tx2);
   outtree->Branch("rk_hit_gtr100_ty",    &out_rk_hit_gtr100_ty);
   outtree->Branch("rk_hit_gtr100_gtx",   &out_rk_hit_gtr100_gtx);
   outtree->Branch("rk_hit_gtr100_gty",   &out_rk_hit_gtr100_gty);
   outtree->Branch("rk_hit_gtr100_gtz",   &out_rk_hit_gtr100_gtz);
   outtree->Branch("rk_hit_gtr100_gtx2",  &out_rk_hit_gtr100_gtx2);
   outtree->Branch("rk_hit_gtr100_gty2",  &out_rk_hit_gtr100_gty2);
   outtree->Branch("rk_hit_gtr100_gtz2",  &out_rk_hit_gtr100_gtz2);
   outtree->Branch("rk_hit_gtr100_nc",    &out_rk_hit_gtr100_nc);
   outtree->Branch("rk_hit_gtr100_the",   &out_rk_hit_gtr100_the);
   outtree->Branch("rk_hit_gtr100_the2",  &out_rk_hit_gtr100_the2);
   outtree->Branch("rk_hit_gtr200_xid",   &out_rk_hit_gtr200_xid);
   outtree->Branch("rk_hit_gtr200_yid",   &out_rk_hit_gtr200_yid);
   outtree->Branch("rk_hit_gtr200_gx",    &out_rk_hit_gtr200_gx);
   outtree->Branch("rk_hit_gtr200_gy",    &out_rk_hit_gtr200_gy);
   outtree->Branch("rk_hit_gtr200_gz",    &out_rk_hit_gtr200_gz);
   outtree->Branch("rk_hit_gtr200_xadc",  &out_rk_hit_gtr200_xadc);
   outtree->Branch("rk_hit_gtr200_yadc",  &out_rk_hit_gtr200_yadc);
   outtree->Branch("rk_hit_gtr200_xt",    &out_rk_hit_gtr200_xt);
   outtree->Branch("rk_hit_gtr200_yt",    &out_rk_hit_gtr200_yt);
   outtree->Branch("rk_hit_gtr200_xt2",   &out_rk_hit_gtr200_xt2);
   outtree->Branch("rk_hit_gtr200_yt2",   &out_rk_hit_gtr200_yt2);
   outtree->Branch("rk_hit_gtr200_tx2",   &out_rk_hit_gtr200_tx2);
   outtree->Branch("rk_hit_gtr200_ty",    &out_rk_hit_gtr200_ty );
   outtree->Branch("rk_hit_gtr200_gtx",   &out_rk_hit_gtr200_gtx);
   outtree->Branch("rk_hit_gtr200_gty",   &out_rk_hit_gtr200_gty);
   outtree->Branch("rk_hit_gtr200_gtz",   &out_rk_hit_gtr200_gtz);
   outtree->Branch("rk_hit_gtr200_gtx2",  &out_rk_hit_gtr200_gtx2);
   outtree->Branch("rk_hit_gtr200_gty2",  &out_rk_hit_gtr200_gty2);
   outtree->Branch("rk_hit_gtr200_gtz2",  &out_rk_hit_gtr200_gtz2);
   outtree->Branch("rk_hit_gtr200_nc",    &out_rk_hit_gtr200_nc );
   outtree->Branch("rk_hit_gtr200_the",   &out_rk_hit_gtr200_the);
   outtree->Branch("rk_hit_gtr200_the2",  &out_rk_hit_gtr200_the2);
   outtree->Branch("rk_hit_gtr300_xid",   &out_rk_hit_gtr300_xid);
   outtree->Branch("rk_hit_gtr300_yid",   &out_rk_hit_gtr300_yid);
   outtree->Branch("rk_hit_gtr300_gx",    &out_rk_hit_gtr300_gx );
   outtree->Branch("rk_hit_gtr300_gy",    &out_rk_hit_gtr300_gy );
   outtree->Branch("rk_hit_gtr300_gz",    &out_rk_hit_gtr300_gz );
   outtree->Branch("rk_hit_gtr300_xadc",  &out_rk_hit_gtr300_xadc);
   outtree->Branch("rk_hit_gtr300_yadc",  &out_rk_hit_gtr300_yadc);
   outtree->Branch("rk_hit_gtr300_xt",    &out_rk_hit_gtr300_xt);
   outtree->Branch("rk_hit_gtr300_yt",    &out_rk_hit_gtr300_yt);
   outtree->Branch("rk_hit_gtr300_xt2",   &out_rk_hit_gtr300_xt2);
   outtree->Branch("rk_hit_gtr300_yt2",   &out_rk_hit_gtr300_yt2);
   outtree->Branch("rk_hit_gtr300_tx2",   &out_rk_hit_gtr300_tx2);
   outtree->Branch("rk_hit_gtr300_ty",    &out_rk_hit_gtr300_ty);
   outtree->Branch("rk_hit_gtr300_gtx",   &out_rk_hit_gtr300_gtx);
   outtree->Branch("rk_hit_gtr300_gty",   &out_rk_hit_gtr300_gty);
   outtree->Branch("rk_hit_gtr300_gtz",   &out_rk_hit_gtr300_gtz);
   outtree->Branch("rk_hit_gtr300_gtx2",  &out_rk_hit_gtr300_gtx2);
   outtree->Branch("rk_hit_gtr300_gty2",  &out_rk_hit_gtr300_gty2);
   outtree->Branch("rk_hit_gtr300_gtz2",  &out_rk_hit_gtr300_gtz2);
   outtree->Branch("rk_hit_gtr300_nc",    &out_rk_hit_gtr300_nc);
   outtree->Branch("rk_hit_gtr300_the",   &out_rk_hit_gtr300_the);
   outtree->Branch("rk_hit_gtr300_the2",  &out_rk_hit_gtr300_the2);
   outtree->Branch("rk_fit_init_mom_gx",  &out_rk_fit_init_mom_gx);
   outtree->Branch("rk_fit_init_mom_gy",  &out_rk_fit_init_mom_gy);
   outtree->Branch("rk_fit_init_mom_gz",  &out_rk_fit_init_mom_gz);
   outtree->Branch("rk_fit_init_pos_gx",  &out_rk_fit_init_pos_gx);
   outtree->Branch("rk_fit_init_pos_gy",  &out_rk_fit_init_pos_gy);
   outtree->Branch("rk_fit_init_pos_gz",  &out_rk_fit_init_pos_gz);
   outtree->Branch("rk_fit_sts_mid",      &out_rk_fit_sts_mid);
   outtree->Branch("rk_fit_sts_x",        &out_rk_fit_sts_x);
   outtree->Branch("rk_fit_sts_y",        &out_rk_fit_sts_y);
   outtree->Branch("rk_fit_sts_gx",       &out_rk_fit_sts_gx);
   outtree->Branch("rk_fit_sts_gy",       &out_rk_fit_sts_gy);
   outtree->Branch("rk_fit_sts_gz",       &out_rk_fit_sts_gz);
   outtree->Branch("rk_fit_sts_mom_x",    &out_rk_fit_sts_mom_x);
   outtree->Branch("rk_fit_sts_mom_y",    &out_rk_fit_sts_mom_y);
   outtree->Branch("rk_fit_sts_mom_z",    &out_rk_fit_sts_mom_z);
   outtree->Branch("rk_fit_sts_mom_gx",   &out_rk_fit_sts_mom_gx);
   outtree->Branch("rk_fit_sts_mom_gy",   &out_rk_fit_sts_mom_gy);
   outtree->Branch("rk_fit_sts_mom_gz",   &out_rk_fit_sts_mom_gz);
   outtree->Branch("rk_fit_gtr100_mid",   &out_rk_fit_gtr100_mid);
   outtree->Branch("rk_fit_gtr100_x",     &out_rk_fit_gtr100_x);
   outtree->Branch("rk_fit_gtr100_y",     &out_rk_fit_gtr100_y);
   outtree->Branch("rk_fit_gtr100_gx",    &out_rk_fit_gtr100_gx);
   outtree->Branch("rk_fit_gtr100_gy",    &out_rk_fit_gtr100_gy);
   outtree->Branch("rk_fit_gtr100_gz",    &out_rk_fit_gtr100_gz);
   outtree->Branch("rk_fit_gtr100_mom_x", &out_rk_fit_gtr100_mom_x);
   outtree->Branch("rk_fit_gtr100_mom_y", &out_rk_fit_gtr100_mom_y);
   outtree->Branch("rk_fit_gtr100_mom_z", &out_rk_fit_gtr100_mom_z);
   outtree->Branch("rk_fit_gtr100_mom_gx",&out_rk_fit_gtr100_mom_gx);
   outtree->Branch("rk_fit_gtr100_mom_gy",&out_rk_fit_gtr100_mom_gy);
   outtree->Branch("rk_fit_gtr100_mom_gz",&out_rk_fit_gtr100_mom_gz);
   outtree->Branch("rk_fit_gtr200_mid",   &out_rk_fit_gtr200_mid);
   outtree->Branch("rk_fit_gtr200_x",     &out_rk_fit_gtr200_x);
   outtree->Branch("rk_fit_gtr200_y",     &out_rk_fit_gtr200_y);
   outtree->Branch("rk_fit_gtr200_gx",    &out_rk_fit_gtr200_gx);
   outtree->Branch("rk_fit_gtr200_gy",    &out_rk_fit_gtr200_gy);
   outtree->Branch("rk_fit_gtr200_gz",    &out_rk_fit_gtr200_gz);
   outtree->Branch("rk_fit_gtr200_mom_x", &out_rk_fit_gtr200_mom_x);
   outtree->Branch("rk_fit_gtr200_mom_y", &out_rk_fit_gtr200_mom_y);
   outtree->Branch("rk_fit_gtr200_mom_z", &out_rk_fit_gtr200_mom_z);
   outtree->Branch("rk_fit_gtr200_mom_gx",&out_rk_fit_gtr200_mom_gx);
   outtree->Branch("rk_fit_gtr200_mom_gy",&out_rk_fit_gtr200_mom_gy);
   outtree->Branch("rk_fit_gtr200_mom_gz",&out_rk_fit_gtr200_mom_gz);
   outtree->Branch("rk_fit_gtr300_mid",   &out_rk_fit_gtr300_mid);
   outtree->Branch("rk_fit_gtr300_x",     &out_rk_fit_gtr300_x);
   outtree->Branch("rk_fit_gtr300_y",     &out_rk_fit_gtr300_y);
   outtree->Branch("rk_fit_gtr300_gx",    &out_rk_fit_gtr300_gx);
   outtree->Branch("rk_fit_gtr300_gy",    &out_rk_fit_gtr300_gy);
   outtree->Branch("rk_fit_gtr300_gz",    &out_rk_fit_gtr300_gz);
   outtree->Branch("rk_fit_gtr300_mom_x", &out_rk_fit_gtr300_mom_x);
   outtree->Branch("rk_fit_gtr300_mom_y", &out_rk_fit_gtr300_mom_y);
   outtree->Branch("rk_fit_gtr300_mom_z", &out_rk_fit_gtr300_mom_z);
   outtree->Branch("rk_fit_gtr300_mom_gx",&out_rk_fit_gtr300_mom_gx);
   outtree->Branch("rk_fit_gtr300_mom_gy",&out_rk_fit_gtr300_mom_gy);
   outtree->Branch("rk_fit_gtr300_mom_gz",&out_rk_fit_gtr300_mom_gz);
   outtree->Branch("rk_fit_hbd_mid",      &out_rk_fit_hbd_mid);
   outtree->Branch("rk_fit_hbd_x",        &out_rk_fit_hbd_x);
   outtree->Branch("rk_fit_hbd_y",        &out_rk_fit_hbd_y);
   outtree->Branch("rk_fit_hbd_gx",       &out_rk_fit_hbd_gx);
   outtree->Branch("rk_fit_hbd_gy",       &out_rk_fit_hbd_gy);
   outtree->Branch("rk_fit_hbd_gz",       &out_rk_fit_hbd_gz);
   outtree->Branch("rk_fit_hbd_mom_x",    &out_rk_fit_hbd_mom_x);
   outtree->Branch("rk_fit_hbd_mom_y",    &out_rk_fit_hbd_mom_y);
   outtree->Branch("rk_fit_hbd_mom_z",    &out_rk_fit_hbd_mom_z);
   outtree->Branch("rk_fit_hbd_mom_gx",   &out_rk_fit_hbd_mom_gx);
   outtree->Branch("rk_fit_hbd_mom_gy",   &out_rk_fit_hbd_mom_gy);
   outtree->Branch("rk_fit_hbd_mom_gz",   &out_rk_fit_hbd_mom_gz);
   outtree->Branch("rk_fit_lg_c_mid",     &out_rk_fit_lg_c_mid );
   outtree->Branch("rk_fit_lg_c_x",       &out_rk_fit_lg_c_x);
   outtree->Branch("rk_fit_lg_c_y",       &out_rk_fit_lg_c_y);
   outtree->Branch("rk_fit_lg_c_gx",      &out_rk_fit_lg_c_gx);
   outtree->Branch("rk_fit_lg_c_gy",      &out_rk_fit_lg_c_gy);
   outtree->Branch("rk_fit_lg_c_gz",      &out_rk_fit_lg_c_gz);
   outtree->Branch("rk_fit_lg_c_mom_x",   &out_rk_fit_lg_c_mom_x);
   outtree->Branch("rk_fit_lg_c_mom_y",   &out_rk_fit_lg_c_mom_y);
   outtree->Branch("rk_fit_lg_c_mom_z",   &out_rk_fit_lg_c_mom_z);
   outtree->Branch("rk_fit_lg_c_mom_gx",  &out_rk_fit_lg_c_mom_gx);
   outtree->Branch("rk_fit_lg_c_mom_gy",  &out_rk_fit_lg_c_mom_gy);
   outtree->Branch("rk_fit_lg_c_mom_gz",  &out_rk_fit_lg_c_mom_gz);
   outtree->Branch("rk_fit_lg_b_mid",     &out_rk_fit_lg_b_mid);
   outtree->Branch("rk_fit_lg_b_x",       &out_rk_fit_lg_b_x);
   outtree->Branch("rk_fit_lg_b_y",       &out_rk_fit_lg_b_y);
   outtree->Branch("rk_fit_lg_b_gx",      &out_rk_fit_lg_b_gx);
   outtree->Branch("rk_fit_lg_b_gy",      &out_rk_fit_lg_b_gy);
   outtree->Branch("rk_fit_lg_b_gz",      &out_rk_fit_lg_b_gz);
   outtree->Branch("rk_fit_lg_b_mom_x",   &out_rk_fit_lg_b_mom_x);
   outtree->Branch("rk_fit_lg_b_mom_y",   &out_rk_fit_lg_b_mom_y);
   outtree->Branch("rk_fit_lg_b_mom_z",   &out_rk_fit_lg_b_mom_z);
   outtree->Branch("rk_fit_lg_b_mom_gx",  &out_rk_fit_lg_b_mom_gx);
   outtree->Branch("rk_fit_lg_b_mom_gy",  &out_rk_fit_lg_b_mom_gy);
   outtree->Branch("rk_fit_lg_b_mom_gz",  &out_rk_fit_lg_b_mom_gz);
   outtree->Branch("rk_fit_lg_a_mid",     &out_rk_fit_lg_a_mid);
   outtree->Branch("rk_fit_lg_a_x",       &out_rk_fit_lg_a_x);
   outtree->Branch("rk_fit_lg_a_y",       &out_rk_fit_lg_a_y);
   outtree->Branch("rk_fit_lg_a_gx",      &out_rk_fit_lg_a_gx);
   outtree->Branch("rk_fit_lg_a_gy",      &out_rk_fit_lg_a_gy);
   outtree->Branch("rk_fit_lg_a_gz",      &out_rk_fit_lg_a_gz);
   outtree->Branch("rk_fit_lg_a_mom_x",   &out_rk_fit_lg_a_mom_x);
   outtree->Branch("rk_fit_lg_a_mom_y",   &out_rk_fit_lg_a_mom_y);
   outtree->Branch("rk_fit_lg_a_mom_z",   &out_rk_fit_lg_a_mom_z);
   outtree->Branch("rk_fit_lg_a_mom_gx",  &out_rk_fit_lg_a_mom_gx);
   outtree->Branch("rk_fit_lg_a_mom_gy",  &out_rk_fit_lg_a_mom_gy);
   outtree->Branch("rk_fit_lg_a_mom_gz",  &out_rk_fit_lg_a_mom_gz);
   outtree->Branch("rk_res_init_pos_gx",  &out_rk_res_init_pos_gx);
   outtree->Branch("rk_res_init_pos_gy",  &out_rk_res_init_pos_gy);
   outtree->Branch("rk_res_init_pos_gz",  &out_rk_res_init_pos_gz);
   outtree->Branch("rk_res_init_mom_gx",  &out_rk_res_init_mom_gx);
   outtree->Branch("rk_res_init_mom_gy",  &out_rk_res_init_mom_gy);
   outtree->Branch("rk_res_init_mom_gz",  &out_rk_res_init_mom_gz);
   outtree->Branch("rk_res_sts_x",        &out_rk_res_sts_x      );
   outtree->Branch("rk_res_gtr100_x",     &out_rk_res_gtr100_x);
   outtree->Branch("rk_res_gtr100_y",     &out_rk_res_gtr100_y);
   outtree->Branch("rk_res_gtr200_x",     &out_rk_res_gtr200_x);
   outtree->Branch("rk_res_gtr200_y",     &out_rk_res_gtr200_y);
   outtree->Branch("rk_res_gtr300_x",     &out_rk_res_gtr300_x);
   outtree->Branch("rk_res_gtr300_y",     &out_rk_res_gtr300_y);
   outtree->Branch("rk_res_gtr100_tx",    &out_rk_res_gtr100_tx);
   outtree->Branch("rk_res_gtr100_ty",    &out_rk_res_gtr100_ty);
   outtree->Branch("rk_res_gtr200_tx",    &out_rk_res_gtr200_tx);
   outtree->Branch("rk_res_gtr200_ty",    &out_rk_res_gtr200_ty);
   outtree->Branch("rk_res_gtr300_tx",    &out_rk_res_gtr300_tx);
   outtree->Branch("rk_res_gtr300_ty",    &out_rk_res_gtr300_ty);
   outtree->Branch("rk_res_gtr100_tx2",   &out_rk_res_gtr100_tx2);
   outtree->Branch("rk_res_gtr200_tx2",   &out_rk_res_gtr200_tx2);
   outtree->Branch("rk_res_gtr300_tx2",   &out_rk_res_gtr300_tx2);
   outtree->Branch("rk_proj_tgt0_gx",     &out_rk_proj_tgt0_gx);
   outtree->Branch("rk_proj_tgt0_gy",     &out_rk_proj_tgt0_gy);
   outtree->Branch("rk_proj_tgt0_gz",     &out_rk_proj_tgt0_gz);
   outtree->Branch("rk_proj_tgt1_gx",     &out_rk_proj_tgt1_gx);
   outtree->Branch("rk_proj_tgt1_gy",     &out_rk_proj_tgt1_gy);
   outtree->Branch("rk_proj_tgt1_gz",     &out_rk_proj_tgt1_gz);
   outtree->Branch("rk_proj_tgt2_gx",     &out_rk_proj_tgt2_gx);
   outtree->Branch("rk_proj_tgt2_gy",     &out_rk_proj_tgt2_gy);
   outtree->Branch("rk_proj_tgt2_gz",     &out_rk_proj_tgt2_gz);
   outtree->Branch("rk_proj_tgt0_mom_gx", &out_rk_proj_tgt0_mom_gx);
   outtree->Branch("rk_proj_tgt0_mom_gy", &out_rk_proj_tgt0_mom_gy);
   outtree->Branch("rk_proj_tgt0_mom_gz", &out_rk_proj_tgt0_mom_gz);
   outtree->Branch("rk_proj_tgt1_mom_gx", &out_rk_proj_tgt1_mom_gx);
   outtree->Branch("rk_proj_tgt1_mom_gy", &out_rk_proj_tgt1_mom_gy);
   outtree->Branch("rk_proj_tgt1_mom_gz", &out_rk_proj_tgt1_mom_gz);
   outtree->Branch("rk_proj_tgt2_mom_gx", &out_rk_proj_tgt2_mom_gx);
   outtree->Branch("rk_proj_tgt2_mom_gy", &out_rk_proj_tgt2_mom_gy);
   outtree->Branch("rk_proj_tgt2_mom_gz", &out_rk_proj_tgt2_mom_gz);
   outtree->Branch("rk_proj_x0_gx",       &out_rk_proj_x0_gx);
   outtree->Branch("rk_proj_x0_gy",       &out_rk_proj_x0_gy);
   outtree->Branch("rk_proj_x0_gz",       &out_rk_proj_x0_gz);
   outtree->Branch("rk_proj_x0_mom_gx",   &out_rk_proj_x0_mom_gx);
   outtree->Branch("rk_proj_x0_mom_gy",   &out_rk_proj_x0_mom_gy);
   outtree->Branch("rk_proj_x0_mom_gz",   &out_rk_proj_x0_mom_gz);
   outtree->Branch("rk_proj_is_search",   &out_rk_proj_is_search);
   outtree->Branch("rk_proj_n_hbd",       &out_rk_proj_n_hbd);
   outtree->Branch("rk_proj_hbd_id",      &out_rk_proj_hbd_id);
   outtree->Branch("rk_proj_hbd_mid",     &out_rk_proj_hbd_mid);
   outtree->Branch("rk_proj_hbd_x",       &out_rk_proj_hbd_x);
   outtree->Branch("rk_proj_hbd_y",       &out_rk_proj_hbd_y);
   outtree->Branch("rk_proj_hbd_adc",     &out_rk_proj_hbd_adc);
   outtree->Branch("rk_proj_hbd_t",       &out_rk_proj_hbd_t);
   outtree->Branch("rk_proj_hbd_ftime",   &out_rk_proj_hbd_ftime);
   outtree->Branch("rk_proj_hbd_tdiff",   &out_rk_proj_hbd_tdiff);
   outtree->Branch("rk_proj_hbd_size",    &out_rk_proj_hbd_size);
   outtree->Branch("rk_proj_hbd_eprob",   &out_rk_proj_hbd_eprob);
   outtree->Branch("rk_proj_hbd_cprob",   &out_rk_proj_hbd_cprob);
   outtree->Branch("rk_proj_n_lg",        &out_rk_proj_n_lg);
   outtree->Branch("rk_proj_lg_id",       &out_rk_proj_lg_id);
   outtree->Branch("rk_proj_lg_mid",      &out_rk_proj_lg_mid);
   outtree->Branch("rk_proj_lg_cid",      &out_rk_proj_lg_cid);
   outtree->Branch("rk_proj_lg_x",        &out_rk_proj_lg_x);
   outtree->Branch("rk_proj_lg_y",        &out_rk_proj_lg_y );
   outtree->Branch("rk_proj_lg_adc",      &out_rk_proj_lg_adc);
   outtree->Branch("rk_proj_lg_t",        &out_rk_proj_lg_t);
   outtree->Branch("rk_proj_lg_npeaks",                &out_rk_proj_lg_npeaks);
   outtree->Branch("rk_proj_lg_fflag",                 &out_rk_proj_lg_fflag);
   outtree->Branch("rk_pair_minus_track_id",           &out_rk_pair_minus_track_id);
   outtree->Branch("rk_pair_minus_gtr300_mid",         &out_rk_pair_minus_gtr300_mid);
   outtree->Branch("rk_pair_minus_chi_square",         &out_rk_pair_minus_chi_square);
   outtree->Branch("rk_pair_minus_mom_gx",             &out_rk_pair_minus_mom_gx);
   outtree->Branch("rk_pair_minus_mom_gy",             &out_rk_pair_minus_mom_gy);
   outtree->Branch("rk_pair_minus_mom_gz",             &out_rk_pair_minus_mom_gz);
   outtree->Branch("rk_pair_minus_sts_t",              &out_rk_pair_minus_sts_t);
   outtree->Branch("rk_pair_minus_lg_t",               &out_rk_pair_minus_lg_t);
   outtree->Branch("rk_pair_plus_track_id",            &out_rk_pair_plus_track_id);
   outtree->Branch("rk_pair_plus_gtr300_mid",          &out_rk_pair_plus_gtr300_mid);
   outtree->Branch("rk_pair_plus_chi_square",          &out_rk_pair_plus_chi_square);
   outtree->Branch("rk_pair_plus_mom_gx",              &out_rk_pair_plus_mom_gx);
   outtree->Branch("rk_pair_plus_mom_gy",              &out_rk_pair_plus_mom_gy);
   outtree->Branch("rk_pair_plus_mom_gz",              &out_rk_pair_plus_mom_gz);
   outtree->Branch("rk_pair_plus_sts_t",               &out_rk_pair_plus_sts_t );
   outtree->Branch("rk_pair_plus_lg_t",                &out_rk_pair_plus_lg_t  );
   outtree->Branch("rk_pair_distance",                 &out_rk_pair_distance   );
   outtree->Branch("rk_pair_vtx_gx",                   &out_rk_pair_vtx_gx);
   outtree->Branch("rk_pair_vtx_gy", 	                &out_rk_pair_vtx_gy);
   outtree->Branch("rk_pair_vtx_gz", 	                &out_rk_pair_vtx_gz);
   outtree->Branch("rk_pair_is_refit",                 &out_rk_pair_is_refit  );
   outtree->Branch("rk_pair_is_selected",              &out_rk_pair_is_selected);
   outtree->Branch("rk_pair_chi_square_refit",         &out_rk_pair_chi_square_refit);
   outtree->Branch("rk_pair_vtx_refit_gx",             &out_rk_pair_vtx_refit_gx);
   outtree->Branch("rk_pair_vtx_refit_gy",             &out_rk_pair_vtx_refit_gy);
   outtree->Branch("rk_pair_vtx_refit_gz",             &out_rk_pair_vtx_refit_gz);
   outtree->Branch("rk_pair_minus_mom_refit_gx",       &out_rk_pair_minus_mom_refit_gx);
   outtree->Branch("rk_pair_minus_mom_refit_gy",       &out_rk_pair_minus_mom_refit_gy);
   outtree->Branch("rk_pair_minus_mom_refit_gz",       &out_rk_pair_minus_mom_refit_gz);
   outtree->Branch("rk_pair_plus_mom_refit_gx",        &out_rk_pair_plus_mom_refit_gx);
   outtree->Branch("rk_pair_plus_mom_refit_gy",        &out_rk_pair_plus_mom_refit_gy);
   outtree->Branch("rk_pair_plus_mom_refit_gz",        &out_rk_pair_plus_mom_refit_gz);
   outtree->Branch("rk_pair_minus_sts_pos_refit_gx",   &out_rk_pair_minus_sts_pos_refit_gx);
   outtree->Branch("rk_pair_minus_sts_pos_refit_gy",   &out_rk_pair_minus_sts_pos_refit_gy);
   outtree->Branch("rk_pair_minus_sts_pos_refit_gz",   &out_rk_pair_minus_sts_pos_refit_gz);
   outtree->Branch("rk_pair_minus_gtr100_pos_refit_gx",&out_rk_pair_minus_gtr100_pos_refit_gx);
   outtree->Branch("rk_pair_minus_gtr100_pos_refit_gy",&out_rk_pair_minus_gtr100_pos_refit_gy);
   outtree->Branch("rk_pair_minus_gtr100_pos_refit_gz",&out_rk_pair_minus_gtr100_pos_refit_gz);
   outtree->Branch("rk_pair_minus_gtr200_pos_refit_gx",&out_rk_pair_minus_gtr200_pos_refit_gx);
   outtree->Branch("rk_pair_minus_gtr200_pos_refit_gy",&out_rk_pair_minus_gtr200_pos_refit_gy);
   outtree->Branch("rk_pair_minus_gtr200_pos_refit_gz",&out_rk_pair_minus_gtr200_pos_refit_gz);
   outtree->Branch("rk_pair_minus_gtr300_pos_refit_gx",&out_rk_pair_minus_gtr300_pos_refit_gx);
   outtree->Branch("rk_pair_minus_gtr300_pos_refit_gy",&out_rk_pair_minus_gtr300_pos_refit_gy);
   outtree->Branch("rk_pair_minus_gtr300_pos_refit_gz",&out_rk_pair_minus_gtr300_pos_refit_gz);
   outtree->Branch("rk_pair_plus_sts_pos_refit_gx",    &out_rk_pair_plus_sts_pos_refit_gx   );
   outtree->Branch("rk_pair_plus_sts_pos_refit_gy",    &out_rk_pair_plus_sts_pos_refit_gy   );
   outtree->Branch("rk_pair_plus_sts_pos_refit_gz",    &out_rk_pair_plus_sts_pos_refit_gz   );
   outtree->Branch("rk_pair_plus_gtr100_pos_refit_gx", &out_rk_pair_plus_gtr100_pos_refit_gx);
   outtree->Branch("rk_pair_plus_gtr100_pos_refit_gy", &out_rk_pair_plus_gtr100_pos_refit_gy);
   outtree->Branch("rk_pair_plus_gtr100_pos_refit_gz", &out_rk_pair_plus_gtr100_pos_refit_gz);
   outtree->Branch("rk_pair_plus_gtr200_pos_refit_gx", &out_rk_pair_plus_gtr200_pos_refit_gx);
   outtree->Branch("rk_pair_plus_gtr200_pos_refit_gy", &out_rk_pair_plus_gtr200_pos_refit_gy);
   outtree->Branch("rk_pair_plus_gtr200_pos_refit_gz", &out_rk_pair_plus_gtr200_pos_refit_gz);
   outtree->Branch("rk_pair_plus_gtr300_pos_refit_gx", &out_rk_pair_plus_gtr300_pos_refit_gx);
   outtree->Branch("rk_pair_plus_gtr300_pos_refit_gy", &out_rk_pair_plus_gtr300_pos_refit_gy);
   outtree->Branch("rk_pair_plus_gtr300_pos_refit_gz", &out_rk_pair_plus_gtr300_pos_refit_gz);
   outtree->Branch("rk_pair_minus_sts_mom_refit_gx",   &out_rk_pair_minus_sts_mom_refit_gx);
   outtree->Branch("rk_pair_minus_sts_mom_refit_gy",   &out_rk_pair_minus_sts_mom_refit_gy);
   outtree->Branch("rk_pair_minus_sts_mom_refit_gz",   &out_rk_pair_minus_sts_mom_refit_gz);
   outtree->Branch("rk_pair_minus_gtr100_mom_refit_gx",&out_rk_pair_minus_gtr100_mom_refit_gx);
   outtree->Branch("rk_pair_minus_gtr100_mom_refit_gy",&out_rk_pair_minus_gtr100_mom_refit_gy);
   outtree->Branch("rk_pair_minus_gtr100_mom_refit_gz",&out_rk_pair_minus_gtr100_mom_refit_gz);
   outtree->Branch("rk_pair_minus_gtr200_mom_refit_gx",&out_rk_pair_minus_gtr200_mom_refit_gx);
   outtree->Branch("rk_pair_minus_gtr200_mom_refit_gy",&out_rk_pair_minus_gtr200_mom_refit_gy);
   outtree->Branch("rk_pair_minus_gtr200_mom_refit_gz",&out_rk_pair_minus_gtr200_mom_refit_gz);
   outtree->Branch("rk_pair_minus_gtr300_mom_refit_gx",&out_rk_pair_minus_gtr300_mom_refit_gx);
   outtree->Branch("rk_pair_minus_gtr300_mom_refit_gy",&out_rk_pair_minus_gtr300_mom_refit_gy);
   outtree->Branch("rk_pair_minus_gtr300_mom_refit_gz",&out_rk_pair_minus_gtr300_mom_refit_gz);
   outtree->Branch("rk_pair_plus_sts_mom_refit_gx",    &out_rk_pair_plus_sts_mom_refit_gx);
   outtree->Branch("rk_pair_plus_sts_mom_refit_gy",    &out_rk_pair_plus_sts_mom_refit_gy);
   outtree->Branch("rk_pair_plus_sts_mom_refit_gz",    &out_rk_pair_plus_sts_mom_refit_gz);
   outtree->Branch("rk_pair_plus_gtr100_mom_refit_gx", &out_rk_pair_plus_gtr100_mom_refit_gx);
   outtree->Branch("rk_pair_plus_gtr100_mom_refit_gy", &out_rk_pair_plus_gtr100_mom_refit_gy);
   outtree->Branch("rk_pair_plus_gtr100_mom_refit_gz", &out_rk_pair_plus_gtr100_mom_refit_gz);
   outtree->Branch("rk_pair_plus_gtr200_mom_refit_gx", &out_rk_pair_plus_gtr200_mom_refit_gx);
   outtree->Branch("rk_pair_plus_gtr200_mom_refit_gy", &out_rk_pair_plus_gtr200_mom_refit_gy);
   outtree->Branch("rk_pair_plus_gtr200_mom_refit_gz", &out_rk_pair_plus_gtr200_mom_refit_gz);
   outtree->Branch("rk_pair_plus_gtr300_mom_refit_gx", &out_rk_pair_plus_gtr300_mom_refit_gx);
   outtree->Branch("rk_pair_plus_gtr300_mom_refit_gy", &out_rk_pair_plus_gtr300_mom_refit_gy);
   outtree->Branch("rk_pair_plus_gtr300_mom_refit_gz", &out_rk_pair_plus_gtr300_mom_refit_gz);
   outtree->Branch("rk_pair_minus_sts_res_refit_x",    &out_rk_pair_minus_sts_res_refit_x);
   outtree->Branch("rk_pair_minus_sts_res_refit_y",    &out_rk_pair_minus_sts_res_refit_y);
   outtree->Branch("rk_pair_minus_sts_res_refit_z",    &out_rk_pair_minus_sts_res_refit_z);
   outtree->Branch("rk_pair_minus_gtr100_res_refit_x", &out_rk_pair_minus_gtr100_res_refit_x);
   outtree->Branch("rk_pair_minus_gtr100_res_refit_y", &out_rk_pair_minus_gtr100_res_refit_y);
   outtree->Branch("rk_pair_minus_gtr100_res_refit_z", &out_rk_pair_minus_gtr100_res_refit_z);
   outtree->Branch("rk_pair_minus_gtr200_res_refit_x", &out_rk_pair_minus_gtr200_res_refit_x);
   outtree->Branch("rk_pair_minus_gtr200_res_refit_y", &out_rk_pair_minus_gtr200_res_refit_y);
   outtree->Branch("rk_pair_minus_gtr200_res_refit_z", &out_rk_pair_minus_gtr200_res_refit_z);
   outtree->Branch("rk_pair_minus_gtr300_res_refit_x", &out_rk_pair_minus_gtr300_res_refit_x);
   outtree->Branch("rk_pair_minus_gtr300_res_refit_y", &out_rk_pair_minus_gtr300_res_refit_y);
   outtree->Branch("rk_pair_minus_gtr300_res_refit_z", &out_rk_pair_minus_gtr300_res_refit_z);
   outtree->Branch("rk_pair_plus_sts_res_refit_x",     &out_rk_pair_plus_sts_res_refit_x)   ;
   outtree->Branch("rk_pair_plus_sts_res_refit_y",     &out_rk_pair_plus_sts_res_refit_y)   ;
   outtree->Branch("rk_pair_plus_sts_res_refit_z",     &out_rk_pair_plus_sts_res_refit_z)   ;
   outtree->Branch("rk_pair_plus_gtr100_res_refit_x",  &out_rk_pair_plus_gtr100_res_refit_x);
   outtree->Branch("rk_pair_plus_gtr100_res_refit_y",  &out_rk_pair_plus_gtr100_res_refit_y);
   outtree->Branch("rk_pair_plus_gtr100_res_refit_z",  &out_rk_pair_plus_gtr100_res_refit_z);
   outtree->Branch("rk_pair_plus_gtr200_res_refit_x",  &out_rk_pair_plus_gtr200_res_refit_x);
   outtree->Branch("rk_pair_plus_gtr200_res_refit_y",  &out_rk_pair_plus_gtr200_res_refit_y);
   outtree->Branch("rk_pair_plus_gtr200_res_refit_z",  &out_rk_pair_plus_gtr200_res_refit_z);
   outtree->Branch("rk_pair_plus_gtr300_res_refit_x",  &out_rk_pair_plus_gtr300_res_refit_x);
   outtree->Branch("rk_pair_plus_gtr300_res_refit_y",  &out_rk_pair_plus_gtr300_res_refit_y);
   outtree->Branch("rk_pair_plus_gtr300_res_refit_z",  &out_rk_pair_plus_gtr300_res_refit_z);
   outtree->Branch("rk_pair_mass_refit",               &out_rk_pair_mass_refit);


   outtree->Branch("rk_hit_gtr100_cogx" , &out_rk_hit_gtr100_cogx) ;
   outtree->Branch("rk_hit_gtr200_cogx" , &out_rk_hit_gtr200_cogx) ;
   outtree->Branch("rk_hit_gtr300_cogx" , &out_rk_hit_gtr300_cogx) ;
   outtree->Branch("rk_hit_gtr100_cogy" , &out_rk_hit_gtr100_cogy) ;
   outtree->Branch("rk_hit_gtr200_cogy" , &out_rk_hit_gtr200_cogy) ;
   outtree->Branch("rk_hit_gtr300_cogy" , &out_rk_hit_gtr300_cogy) ;

   outtree->Branch("rk_hit_gtr100_xt4", &out_rk_hit_gtr100_xt4);
   outtree->Branch("rk_hit_gtr200_xt4", &out_rk_hit_gtr200_xt4);
   outtree->Branch("rk_hit_gtr300_xt4", &out_rk_hit_gtr300_xt4);
   outtree->Branch("rk_hit_gtr100_yt4", &out_rk_hit_gtr100_yt4);
   outtree->Branch("rk_hit_gtr200_yt4", &out_rk_hit_gtr200_yt4);
   outtree->Branch("rk_hit_gtr300_yt4", &out_rk_hit_gtr300_yt4);

   outtree->Branch("gtr100x_cluster_last_tot_end",        &out_gtr100x_cluster_last_tot_end);
   outtree->Branch("gtr200x_cluster_last_tot_end",        &out_gtr200x_cluster_last_tot_end);
   outtree->Branch("gtr300x_cluster_last_tot_end",        &out_gtr300x_cluster_last_tot_end);
   outtree->Branch("gtr100x_cluster_consist_hit_id", &out_gtr100x_cluster_consist_hit_id);
   outtree->Branch("gtr200x_cluster_consist_hit_id", &out_gtr200x_cluster_consist_hit_id);
   outtree->Branch("gtr300x_cluster_consist_hit_id", &out_gtr300x_cluster_consist_hit_id);
   outtree->Branch("gtr100y_cluster_consist_hit_id", &out_gtr100y_cluster_consist_hit_id);
   outtree->Branch("gtr100yb_cluster_consist_hit_id", &out_gtr100yb_cluster_consist_hit_id);
   outtree->Branch("gtr200y_cluster_consist_hit_id", &out_gtr200y_cluster_consist_hit_id);
   outtree->Branch("gtr300y_cluster_consist_hit_id", &out_gtr300y_cluster_consist_hit_id);
//   outtree->Branch("re_lg_res_x", &out_re_lg_res_x);
//   outtree->Branch("re_lg_res_y", &out_re_lg_res_y);



}

Bool_t E16DSTN_ReStraightV2::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void E16DSTN_ReStraightV2::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t E16DSTN_ReStraightV2::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}



void E16DSTN_ReStraightV2::AddRecord(TTree *intree,  std::vector<int> &alive_ids){
//	out_event_id = event_id;
//	out_spill_id = spill_id;
//	out_timestamp_in_spill = timestamp_in_spill;
//	out_trigger_fine_time  = trigger_fine_time;





//	int n_tracks = rk_hit_init_pos_gz->size() ;	
	int n_tracks = alive_ids.size();	
//	out_n_alive_tracks = n_tracks;

    	out_track_id.resize(n_tracks);
  	   out_has_e_hbd_cluster.resize(n_tracks);
  	   out_has_e_lg_hit.resize(n_tracks);
  	   out_is_large_residual.resize(n_tracks);   
  	   out_is_near_target.resize(n_tracks);
  	   out_is_cluster_used.resize(n_tracks); 
  	   out_is_selected.resize(n_tracks);
  	   out_x_rough_fit_chi_square.resize(n_tracks); 
  	   out_x_rough_fit_dist0.resize(n_tracks);
  	   out_x_rough_fit_dist1.resize(n_tracks);
  	   out_x_rough_fit_coef0.resize(n_tracks);
  	   out_x_rough_fit_coef1.resize(n_tracks);
  	   out_x_rough_fit_coef2.resize(n_tracks);   
  	   out_rough_fit_n_hbds.resize(n_tracks);
  	   out_rough_fit_hbd_ids.resize(n_tracks);   
  	   out_rough_fit_hbd_ress.resize(n_tracks); 
  	   out_rough_fit_hbd_y_oks.resize(n_tracks);  
  	   out_y_rough_fit_chi_square.resize(n_tracks);  
  	   out_y_rough_fit_coef0.resize(n_tracks);
  	   out_y_rough_fit_coef1.resize(n_tracks);

	 out_gtr100x_cluster_last_tot_end.resize(n_tracks);
	 out_gtr200x_cluster_last_tot_end.resize(n_tracks);
	 out_gtr300x_cluster_last_tot_end.resize(n_tracks);


    out_gtr100x_cluster_consist_hit_id.resize(n_tracks);
    out_gtr200x_cluster_consist_hit_id.resize(n_tracks);
    out_gtr300x_cluster_consist_hit_id.resize(n_tracks);
    out_gtr100y_cluster_consist_hit_id.resize(n_tracks);
    out_gtr100yb_cluster_consist_hit_id.resize(n_tracks);
    out_gtr200y_cluster_consist_hit_id.resize(n_tracks);
    out_gtr300y_cluster_consist_hit_id.resize(n_tracks);

	 out_rk_charge.resize(n_tracks);
    out_rk_hit_init_mom_gx.resize(n_tracks);
    out_rk_hit_init_mom_gy.resize(n_tracks);
    out_rk_hit_init_mom_gz.resize(n_tracks);
    out_rk_hit_init_pos_gx.resize(n_tracks);
    out_rk_hit_init_pos_gy.resize(n_tracks);
    out_rk_hit_init_pos_gz.resize(n_tracks);
    out_rk_hit_sts_id.resize(n_tracks);
    out_rk_hit_sts_x.resize(n_tracks);
    out_rk_hit_sts_gx.resize(n_tracks);
    out_rk_hit_sts_gy.resize(n_tracks);
    out_rk_hit_sts_gz.resize(n_tracks);
    out_rk_hit_sts_adc.resize(n_tracks);
    out_rk_hit_sts_t.resize(n_tracks);
    out_rk_hit_sts_chi2.resize(n_tracks);
    out_rk_hit_gtr100_xid.resize(n_tracks);
    out_rk_hit_gtr100_yid.resize(n_tracks);
    out_rk_hit_gtr100_gx.resize(n_tracks);
    out_rk_hit_gtr100_gy.resize(n_tracks);
    out_rk_hit_gtr100_gz.resize(n_tracks);
    out_rk_hit_gtr100_xadc.resize(n_tracks);
    out_rk_hit_gtr100_yadc.resize(n_tracks);
    out_rk_hit_gtr100_xt.resize(n_tracks);
    out_rk_hit_gtr100_yt.resize(n_tracks);
    out_rk_hit_gtr200_xid.resize(n_tracks);
    out_rk_hit_gtr200_yid.resize(n_tracks);
    out_rk_hit_gtr200_gx.resize(n_tracks);
    out_rk_hit_gtr200_gy.resize(n_tracks);
    out_rk_hit_gtr200_gz.resize(n_tracks);
    out_rk_hit_gtr200_xadc.resize(n_tracks);
    out_rk_hit_gtr200_yadc.resize(n_tracks);
    out_rk_hit_gtr200_xt.resize(n_tracks);
    out_rk_hit_gtr200_yt.resize(n_tracks);
    out_rk_hit_gtr300_xid.resize(n_tracks);
    out_rk_hit_gtr300_yid.resize(n_tracks);
    out_rk_hit_gtr300_gx.resize(n_tracks);
    out_rk_hit_gtr300_gy.resize(n_tracks);
    out_rk_hit_gtr300_gz.resize(n_tracks);
    out_rk_hit_gtr300_xadc.resize(n_tracks);
    out_rk_hit_gtr300_yadc.resize(n_tracks);
    out_rk_hit_gtr300_xt.resize(n_tracks);
    out_rk_hit_gtr300_yt.resize(n_tracks);
    out_rk_hit_gtr100_xt2.resize(n_tracks);
    out_rk_hit_gtr100_yt2.resize(n_tracks);
    out_rk_hit_gtr100_tx2.resize(n_tracks);
    out_rk_hit_gtr100_ty.resize(n_tracks);
    out_rk_hit_gtr100_gtx.resize(n_tracks);
    out_rk_hit_gtr100_gty.resize(n_tracks);
    out_rk_hit_gtr100_gtz.resize(n_tracks);
    out_rk_hit_gtr100_gtx2.resize(n_tracks);
    out_rk_hit_gtr100_gty2.resize(n_tracks);
    out_rk_hit_gtr100_gtz2.resize(n_tracks);
    out_rk_hit_gtr100_nc.resize(n_tracks);
    out_rk_hit_gtr100_the.resize(n_tracks);
    out_rk_hit_gtr100_the2.resize(n_tracks);
    out_rk_hit_gtr200_xt2.resize(n_tracks);
    out_rk_hit_gtr200_yt2.resize(n_tracks);
    out_rk_hit_gtr200_tx2.resize(n_tracks);
    out_rk_hit_gtr200_ty.resize(n_tracks);
    out_rk_hit_gtr200_gtx.resize(n_tracks);
    out_rk_hit_gtr200_gty.resize(n_tracks);
    out_rk_hit_gtr200_gtz.resize(n_tracks);
    out_rk_hit_gtr200_gtx2.resize(n_tracks);
    out_rk_hit_gtr200_gty2.resize(n_tracks);
    out_rk_hit_gtr200_gtz2.resize(n_tracks);
    out_rk_hit_gtr200_nc.resize(n_tracks);
    out_rk_hit_gtr200_the.resize(n_tracks);
    out_rk_hit_gtr200_the2.resize(n_tracks);
    out_rk_hit_gtr300_xt2.resize(n_tracks);
    out_rk_hit_gtr300_yt2.resize(n_tracks);
    out_rk_hit_gtr300_tx2.resize(n_tracks);
    out_rk_hit_gtr300_ty.resize(n_tracks);
    out_rk_hit_gtr300_gtx.resize(n_tracks);
    out_rk_hit_gtr300_gty.resize(n_tracks);
    out_rk_hit_gtr300_gtz.resize(n_tracks);
    out_rk_hit_gtr300_gtx2.resize(n_tracks);
    out_rk_hit_gtr300_gty2.resize(n_tracks);
    out_rk_hit_gtr300_gtz2.resize(n_tracks);
    out_rk_hit_gtr300_nc.resize(n_tracks);
    out_rk_hit_gtr300_the.resize(n_tracks);
    out_rk_hit_gtr300_the2.resize(n_tracks);
    out_rk_fit_init_mom_gx.resize(n_tracks);
    out_rk_fit_init_mom_gy.resize(n_tracks);
    out_rk_fit_init_mom_gz.resize(n_tracks);
    out_rk_fit_init_pos_gx.resize(n_tracks);
    out_rk_fit_init_pos_gy.resize(n_tracks);
    out_rk_fit_init_pos_gz.resize(n_tracks);
    out_rk_fit_sts_mid.resize(n_tracks);
    out_rk_fit_sts_x.resize(n_tracks);
    out_rk_fit_sts_y.resize(n_tracks);
    out_rk_fit_sts_gx.resize(n_tracks);
    out_rk_fit_sts_gy.resize(n_tracks);
    out_rk_fit_sts_gz.resize(n_tracks);
    out_rk_fit_sts_mom_x.resize(n_tracks);
    out_rk_fit_sts_mom_y.resize(n_tracks);
    out_rk_fit_sts_mom_z.resize(n_tracks);
    out_rk_fit_sts_mom_gx.resize(n_tracks);
    out_rk_fit_sts_mom_gy.resize(n_tracks);
    out_rk_fit_sts_mom_gz.resize(n_tracks);
    out_rk_fit_gtr100_mid.resize(n_tracks);
    out_rk_fit_gtr100_x.resize(n_tracks);
    out_rk_fit_gtr100_y.resize(n_tracks);
    out_rk_fit_gtr100_gx.resize(n_tracks);
    out_rk_fit_gtr100_gy.resize(n_tracks);
    out_rk_fit_gtr100_gz.resize(n_tracks);
    out_rk_fit_gtr100_mom_x.resize(n_tracks);
    out_rk_fit_gtr100_mom_y.resize(n_tracks);
    out_rk_fit_gtr100_mom_z.resize(n_tracks);
    out_rk_fit_gtr100_mom_gx.resize(n_tracks);
    out_rk_fit_gtr100_mom_gy.resize(n_tracks);
    out_rk_fit_gtr100_mom_gz.resize(n_tracks);
    out_rk_fit_gtr200_mid.resize(n_tracks);
    out_rk_fit_gtr200_x.resize(n_tracks);
    out_rk_fit_gtr200_y.resize(n_tracks);
    out_rk_fit_gtr200_gx.resize(n_tracks);
    out_rk_fit_gtr200_gy.resize(n_tracks);
    out_rk_fit_gtr200_gz.resize(n_tracks);
    out_rk_fit_gtr200_mom_x.resize(n_tracks);
    out_rk_fit_gtr200_mom_y.resize(n_tracks);
    out_rk_fit_gtr200_mom_z.resize(n_tracks);
    out_rk_fit_gtr200_mom_gx.resize(n_tracks);
    out_rk_fit_gtr200_mom_gy.resize(n_tracks);
    out_rk_fit_gtr200_mom_gz.resize(n_tracks);
    out_rk_fit_gtr300_mid.resize(n_tracks);
    out_rk_fit_gtr300_x.resize(n_tracks);
    out_rk_fit_gtr300_y.resize(n_tracks);
    out_rk_fit_gtr300_gx.resize(n_tracks);
    out_rk_fit_gtr300_gy.resize(n_tracks);
    out_rk_fit_gtr300_gz.resize(n_tracks);
    out_rk_fit_gtr300_mom_x.resize(n_tracks);
    out_rk_fit_gtr300_mom_y.resize(n_tracks);
    out_rk_fit_gtr300_mom_z.resize(n_tracks);
    out_rk_fit_gtr300_mom_gx.resize(n_tracks);
    out_rk_fit_gtr300_mom_gy.resize(n_tracks);
    out_rk_fit_gtr300_mom_gz.resize(n_tracks);
    out_rk_fit_hbd_mid.resize(n_tracks);
    out_rk_fit_hbd_x.resize(n_tracks);
    out_rk_fit_hbd_y.resize(n_tracks);
    out_rk_fit_hbd_gx.resize(n_tracks);
    out_rk_fit_hbd_gy.resize(n_tracks);
    out_rk_fit_hbd_gz.resize(n_tracks);
    out_rk_fit_hbd_mom_x.resize(n_tracks);
    out_rk_fit_hbd_mom_y.resize(n_tracks);
    out_rk_fit_hbd_mom_z.resize(n_tracks);
    out_rk_fit_hbd_mom_gx.resize(n_tracks);
    out_rk_fit_hbd_mom_gy.resize(n_tracks);
    out_rk_fit_hbd_mom_gz.resize(n_tracks);
    out_rk_fit_lg_c_mid.resize(n_tracks);
    out_rk_fit_lg_c_x.resize(n_tracks);
    out_rk_fit_lg_c_y.resize(n_tracks);
    out_rk_fit_lg_c_gx.resize(n_tracks);
    out_rk_fit_lg_c_gy.resize(n_tracks);
    out_rk_fit_lg_c_gz.resize(n_tracks);
    out_rk_fit_lg_c_mom_x.resize(n_tracks);
    out_rk_fit_lg_c_mom_y.resize(n_tracks);
    out_rk_fit_lg_c_mom_z.resize(n_tracks);
    out_rk_fit_lg_c_mom_gx.resize(n_tracks);
    out_rk_fit_lg_c_mom_gy.resize(n_tracks);
    out_rk_fit_lg_c_mom_gz.resize(n_tracks);
    out_rk_fit_lg_b_mid.resize(n_tracks);
    out_rk_fit_lg_b_x.resize(n_tracks);
    out_rk_fit_lg_b_y.resize(n_tracks);
    out_rk_fit_lg_b_gx.resize(n_tracks);
    out_rk_fit_lg_b_gy.resize(n_tracks);
    out_rk_fit_lg_b_gz.resize(n_tracks);
    out_rk_fit_lg_b_mom_x.resize(n_tracks);
    out_rk_fit_lg_b_mom_y.resize(n_tracks);
    out_rk_fit_lg_b_mom_z.resize(n_tracks);
    out_rk_fit_lg_b_mom_gx.resize(n_tracks);
    out_rk_fit_lg_b_mom_gy.resize(n_tracks);
    out_rk_fit_lg_b_mom_gz.resize(n_tracks);
    out_rk_fit_lg_a_mid.resize(n_tracks);
    out_rk_fit_lg_a_x.resize(n_tracks);
    out_rk_fit_lg_a_y.resize(n_tracks);
    out_rk_fit_lg_a_gx.resize(n_tracks);
    out_rk_fit_lg_a_gy.resize(n_tracks);
    out_rk_fit_lg_a_gz.resize(n_tracks);
    out_rk_fit_lg_a_mom_x.resize(n_tracks);
    out_rk_fit_lg_a_mom_y.resize(n_tracks);
    out_rk_fit_lg_a_mom_z.resize(n_tracks);
    out_rk_fit_lg_a_mom_gx.resize(n_tracks);
    out_rk_fit_lg_a_mom_gy.resize(n_tracks);
    out_rk_fit_lg_a_mom_gz.resize(n_tracks);
#ifdef TRACK_EFF_CHECK
    rk_fit_lgvd_mid.resize(n_tracks);
    rk_fit_lgvd_x.resize(n_tracks);
    rk_fit_lgvd_y.resize(n_tracks);
    rk_fit_lgvd_gx.resize(n_tracks);
    rk_fit_lgvd_gy.resize(n_tracks);
    rk_fit_lgvd_gz.resize(n_tracks);
    rk_fit_lgvd_mom_x.resize(n_tracks);
    rk_fit_lgvd_mom_y.resize(n_tracks);
    rk_fit_lgvd_mom_z.resize(n_tracks);
    rk_fit_lgvd_mom_gx.resize(n_tracks);
    rk_fit_lgvd_mom_gy.resize(n_tracks);
    rk_fit_lgvd_mom_gz.resize(n_tracks);
#endif
    out_rk_res_init_pos_gx.resize(n_tracks);
    out_rk_res_init_pos_gy.resize(n_tracks);
    out_rk_res_init_pos_gz.resize(n_tracks);
    out_rk_res_init_mom_gx.resize(n_tracks);
    out_rk_res_init_mom_gy.resize(n_tracks);
    out_rk_res_init_mom_gz.resize(n_tracks);
    out_rk_res_sts_x.resize(n_tracks);
    out_rk_res_gtr100_x.resize(n_tracks);
    out_rk_res_gtr100_y.resize(n_tracks);
    out_rk_res_gtr200_x.resize(n_tracks);
    out_rk_res_gtr200_y.resize(n_tracks);
    out_rk_res_gtr300_x.resize(n_tracks);
    out_rk_res_gtr300_y.resize(n_tracks);
    out_rk_res_gtr100_tx.resize(n_tracks);
    out_rk_res_gtr100_ty.resize(n_tracks);
    out_rk_res_gtr200_tx.resize(n_tracks);
    out_rk_res_gtr200_ty.resize(n_tracks);
    out_rk_res_gtr300_tx.resize(n_tracks);
    out_rk_res_gtr300_ty.resize(n_tracks);
    out_rk_res_gtr100_tx2.resize(n_tracks);
    out_rk_res_gtr200_tx2.resize(n_tracks);
    out_rk_res_gtr300_tx2.resize(n_tracks);
    out_rk_proj_lg_id.resize(n_tracks);
    out_rk_proj_lg_mid.resize(n_tracks);
    out_rk_proj_lg_cid.resize(n_tracks);
    out_rk_proj_lg_x.resize(n_tracks);
    out_rk_proj_lg_y.resize(n_tracks);
    out_rk_proj_lg_adc.resize(n_tracks);
    out_rk_proj_lg_t.resize(n_tracks);
    out_rk_proj_lg_npeaks.resize(n_tracks);
    out_rk_proj_lg_fflag.resize(n_tracks);
	 out_chi_square.resize(n_tracks);
	


   out_rk_hit_gtr100_cogx.resize(n_tracks) ;
   out_rk_hit_gtr200_cogx.resize(n_tracks) ;
   out_rk_hit_gtr300_cogx.resize(n_tracks) ;
   out_rk_hit_gtr100_cogy.resize(n_tracks) ;
   out_rk_hit_gtr200_cogy.resize(n_tracks) ;
	
   out_rk_hit_gtr100_xt4.resize(n_tracks);
   out_rk_hit_gtr200_xt4.resize(n_tracks);
   out_rk_hit_gtr300_xt4.resize(n_tracks);
   out_rk_hit_gtr100_yt4.resize(n_tracks);
   out_rk_hit_gtr200_yt4.resize(n_tracks);
   out_rk_hit_gtr300_yt4.resize(n_tracks);

  
		out_rk_hit_gtr100_tx2.resize(n_tracks);
		out_rk_hit_gtr200_tx2.resize(n_tracks);
		out_rk_hit_gtr300_tx2.resize(n_tracks);
		out_rk_hit_gtr100_gtx.resize(n_tracks);
		out_rk_hit_gtr200_gtx.resize(n_tracks);
		out_rk_hit_gtr300_gtx.resize(n_tracks);
		out_rk_hit_gtr100_gty.resize(n_tracks);
		out_rk_hit_gtr200_gty.resize(n_tracks);
		out_rk_hit_gtr300_gty.resize(n_tracks);
		out_rk_hit_gtr100_gtz.resize(n_tracks);
		out_rk_hit_gtr200_gtz.resize(n_tracks);
		out_rk_hit_gtr300_gtz.resize(n_tracks);
		out_rk_hit_gtr100_gtx2.resize(n_tracks);
		out_rk_hit_gtr200_gtx2.resize(n_tracks);
		out_rk_hit_gtr300_gtx2.resize(n_tracks);
		out_rk_hit_gtr100_gty2.resize(n_tracks);
		out_rk_hit_gtr200_gty2.resize(n_tracks);
		out_rk_hit_gtr300_gty2.resize(n_tracks);
		out_rk_hit_gtr100_gtz2.resize(n_tracks);
		out_rk_hit_gtr200_gtz2.resize(n_tracks);
		out_rk_hit_gtr300_gtz2.resize(n_tracks);
	

		n_pairs = track_pairs.size();
		out_rk_pair_minus_track_id.resize(n_pairs);
		out_rk_pair_minus_gtr300_mid.resize(n_pairs);
		out_rk_pair_minus_chi_square.resize(n_pairs);
		out_rk_pair_minus_mom_gx.resize(n_pairs);
		out_rk_pair_minus_mom_gy.resize(n_pairs);
		out_rk_pair_minus_mom_gz.resize(n_pairs);
		out_rk_pair_minus_sts_t.resize(n_pairs);
		out_rk_pair_minus_lg_t.clear();
		out_rk_pair_minus_lg_t.resize(n_pairs);
		out_rk_pair_plus_track_id.resize(n_pairs);
		out_rk_pair_plus_gtr300_mid.resize(n_pairs);
		out_rk_pair_plus_chi_square.resize(n_pairs);
		out_rk_pair_plus_mom_gx.resize(n_pairs);
		out_rk_pair_plus_mom_gy.resize(n_pairs);
		out_rk_pair_plus_mom_gz.resize(n_pairs);
		out_rk_pair_plus_sts_t.resize(n_pairs);
		out_rk_pair_plus_lg_t.clear();
		out_rk_pair_plus_lg_t.resize(n_pairs);
		out_rk_pair_distance.resize(n_pairs);
		out_rk_pair_vtx_gx.resize(n_pairs);
		out_rk_pair_vtx_gy.resize(n_pairs);
		out_rk_pair_vtx_gz.resize(n_pairs);
		out_rk_pair_is_refit.resize(n_pairs);
		out_rk_pair_is_selected.resize(n_pairs);
		out_rk_pair_chi_square_refit.resize(n_pairs);
		out_rk_pair_vtx_refit_gx.resize(n_pairs);
		out_rk_pair_vtx_refit_gy.resize(n_pairs);
		out_rk_pair_vtx_refit_gz.resize(n_pairs);
		out_rk_pair_minus_mom_refit_gx.resize(n_pairs);
		out_rk_pair_minus_mom_refit_gy.resize(n_pairs);
		out_rk_pair_minus_mom_refit_gz.resize(n_pairs);
		out_rk_pair_plus_mom_refit_gx.resize(n_pairs);
		out_rk_pair_plus_mom_refit_gy.resize(n_pairs);
		out_rk_pair_plus_mom_refit_gz.resize(n_pairs);
		out_rk_pair_minus_sts_pos_refit_gx.resize(n_pairs);
		out_rk_pair_minus_sts_pos_refit_gy.resize(n_pairs);
		out_rk_pair_minus_sts_pos_refit_gz.resize(n_pairs);
		out_rk_pair_minus_gtr100_pos_refit_gx.resize(n_pairs);
		out_rk_pair_minus_gtr100_pos_refit_gy.resize(n_pairs);
		out_rk_pair_minus_gtr100_pos_refit_gz.resize(n_pairs);
		out_rk_pair_minus_gtr200_pos_refit_gx.resize(n_pairs);
		out_rk_pair_minus_gtr200_pos_refit_gy.resize(n_pairs);
		out_rk_pair_minus_gtr200_pos_refit_gz.resize(n_pairs);
		out_rk_pair_minus_gtr300_pos_refit_gx.resize(n_pairs);
		out_rk_pair_minus_gtr300_pos_refit_gy.resize(n_pairs);
		out_rk_pair_minus_gtr300_pos_refit_gz.resize(n_pairs);
		out_rk_pair_plus_sts_pos_refit_gx.resize(n_pairs);
		out_rk_pair_plus_sts_pos_refit_gy.resize(n_pairs);
		out_rk_pair_plus_sts_pos_refit_gz.resize(n_pairs);
		out_rk_pair_plus_gtr100_pos_refit_gx.resize(n_pairs);
		out_rk_pair_plus_gtr100_pos_refit_gy.resize(n_pairs);
		out_rk_pair_plus_gtr100_pos_refit_gz.resize(n_pairs);
		out_rk_pair_plus_gtr200_pos_refit_gx.resize(n_pairs);
		out_rk_pair_plus_gtr200_pos_refit_gy.resize(n_pairs);
		out_rk_pair_plus_gtr200_pos_refit_gz.resize(n_pairs);
		out_rk_pair_plus_gtr300_pos_refit_gx.resize(n_pairs);
		out_rk_pair_plus_gtr300_pos_refit_gy.resize(n_pairs);
		out_rk_pair_plus_gtr300_pos_refit_gz.resize(n_pairs);
		out_rk_pair_minus_sts_mom_refit_gx.resize(n_pairs);
		out_rk_pair_minus_sts_mom_refit_gy.resize(n_pairs);
		out_rk_pair_minus_sts_mom_refit_gz.resize(n_pairs);
		out_rk_pair_minus_gtr100_mom_refit_gx.resize(n_pairs);
		out_rk_pair_minus_gtr100_mom_refit_gy.resize(n_pairs);
		out_rk_pair_minus_gtr100_mom_refit_gz.resize(n_pairs);
		out_rk_pair_minus_gtr200_mom_refit_gx.resize(n_pairs);
		out_rk_pair_minus_gtr200_mom_refit_gy.resize(n_pairs);
		out_rk_pair_minus_gtr200_mom_refit_gz.resize(n_pairs);
		out_rk_pair_minus_gtr300_mom_refit_gx.resize(n_pairs);
		out_rk_pair_minus_gtr300_mom_refit_gy.resize(n_pairs);
		out_rk_pair_minus_gtr300_mom_refit_gz.resize(n_pairs);
		out_rk_pair_plus_sts_mom_refit_gx.resize(n_pairs);
		out_rk_pair_plus_sts_mom_refit_gy.resize(n_pairs);
		out_rk_pair_plus_sts_mom_refit_gz.resize(n_pairs);
		out_rk_pair_plus_gtr100_mom_refit_gx.resize(n_pairs);
		out_rk_pair_plus_gtr100_mom_refit_gy.resize(n_pairs);
		out_rk_pair_plus_gtr100_mom_refit_gz.resize(n_pairs);
		out_rk_pair_plus_gtr200_mom_refit_gx.resize(n_pairs);
		out_rk_pair_plus_gtr200_mom_refit_gy.resize(n_pairs);
		out_rk_pair_plus_gtr200_mom_refit_gz.resize(n_pairs);
		out_rk_pair_plus_gtr300_mom_refit_gx.resize(n_pairs);
		out_rk_pair_plus_gtr300_mom_refit_gy.resize(n_pairs);
		out_rk_pair_plus_gtr300_mom_refit_gz.resize(n_pairs);
		out_rk_pair_minus_sts_res_refit_x.resize(n_pairs);
		out_rk_pair_minus_sts_res_refit_y.resize(n_pairs);
		out_rk_pair_minus_sts_res_refit_z.resize(n_pairs);
		out_rk_pair_minus_gtr100_res_refit_x.resize(n_pairs);
		out_rk_pair_minus_gtr100_res_refit_y.resize(n_pairs);
		out_rk_pair_minus_gtr100_res_refit_z.resize(n_pairs);
		out_rk_pair_minus_gtr200_res_refit_x.resize(n_pairs);
		out_rk_pair_minus_gtr200_res_refit_y.resize(n_pairs);
		out_rk_pair_minus_gtr200_res_refit_z.resize(n_pairs);
		out_rk_pair_minus_gtr300_res_refit_x.resize(n_pairs);
		out_rk_pair_minus_gtr300_res_refit_y.resize(n_pairs);
		out_rk_pair_minus_gtr300_res_refit_z.resize(n_pairs);
		out_rk_pair_plus_sts_res_refit_x.resize(n_pairs);
		out_rk_pair_plus_sts_res_refit_y.resize(n_pairs);
		out_rk_pair_plus_sts_res_refit_z.resize(n_pairs);
		out_rk_pair_plus_gtr100_res_refit_x.resize(n_pairs);
		out_rk_pair_plus_gtr100_res_refit_y.resize(n_pairs);
		out_rk_pair_plus_gtr100_res_refit_z.resize(n_pairs);
		out_rk_pair_plus_gtr200_res_refit_x.resize(n_pairs);
		out_rk_pair_plus_gtr200_res_refit_y.resize(n_pairs);
		out_rk_pair_plus_gtr200_res_refit_z.resize(n_pairs);
		out_rk_pair_plus_gtr300_res_refit_x.resize(n_pairs);
		out_rk_pair_plus_gtr300_res_refit_y.resize(n_pairs);
		out_rk_pair_plus_gtr300_res_refit_z.resize(n_pairs);
		


//		out_re_lg_res_x.resize(n_tracks);
//		out_re_lg_res_y.resize(n_tracks);

//  out_n_cands = n_selected;
	for(int i = 0 ; i < n_tracks ; i++){		
		int tid = alive_ids[i];
		out_track_id[i] = tid;
	   out_has_e_hbd_cluster[i]=     	   has_e_hbd_cluster->at(tid);
	   out_has_e_lg_hit[i]=          	   has_e_lg_hit->at(tid);
	   out_is_large_residual[i]=     	   is_large_residual->at(tid);   
	   out_is_near_target[i]=  is_near_target->at(tid);
	   out_is_cluster_used[i]=     is_cluster_used->at(tid); 
	   out_is_selected[i]=     is_selected->at(tid);
	   out_x_rough_fit_chi_square[i]= 	   x_rough_fit_chi_square->at(tid); 
//	   out_x_rough_fit_dist0[i]=     x_rough_fit_dist0->at(tid);
//	   out_x_rough_fit_dist1[i]=     x_rough_fit_dist1->at(tid);
	   out_x_rough_fit_coef0[i]=     x_rough_fit_coef0->at(tid);
	   out_x_rough_fit_coef1[i]=     x_rough_fit_coef1->at(tid);
	   out_x_rough_fit_coef2[i]=     x_rough_fit_coef2->at(tid);   
	   out_rough_fit_n_hbds[i]=     rough_fit_n_hbds->at(tid);
	   out_rough_fit_hbd_ids[i]=    rough_fit_hbd_ids->at(tid);   
	   out_rough_fit_hbd_ress[i]=   rough_fit_hbd_ress->at(tid); 
	   out_rough_fit_hbd_y_oks[i]=  rough_fit_hbd_y_oks->at(tid);  
	   out_y_rough_fit_chi_square[i]=     y_rough_fit_chi_square->at(tid);  
	   out_y_rough_fit_coef0[i]=     y_rough_fit_coef0->at(tid);
	   out_y_rough_fit_coef1[i]=	   y_rough_fit_coef1->at(tid);


			out_gtr100x_cluster_consist_hit_id[i].clear();
			out_gtr200x_cluster_consist_hit_id[i].clear();
			out_gtr300x_cluster_consist_hit_id[i].clear();
			out_gtr100y_cluster_consist_hit_id[i].clear();
			out_gtr100yb_cluster_consist_hit_id[i].clear();
			out_gtr200y_cluster_consist_hit_id[i].clear();
			out_gtr300y_cluster_consist_hit_id[i].clear();

		int cid_100 = rk_hit_gtr100_xid->at(tid);//cluster id which is used in a track
		std::cout << "n clusters " << n_gtr100x_clusters << std::endl;
		for(int j=0; j < n_gtr100x_clusters; j++){
			int cid = gtr100x_cluster_id->at(j);//cluster id from all cluster
			if(cid_100 == cid){ //if both are matched
   	      out_gtr100x_cluster_last_tot_end[i] = gtr100x_cluster_last_tot_end->at(j);//tot_end is filled
				std::cout << "J " << j << std::endl;
				std::cout << "cons size " << gtr100x_cluster_consist_hit_id->size() << std::endl;
				std::cout << "tot  size " << gtr100x_cluster_last_tot_end->size() << std::endl;
				
				int cl_size = gtr100x_cluster_consist_hit_id->at(j).size();
				std::cout << "clsize" << cl_size << std::endl;
				for(int k=0; k < cl_size; k++){
				out_gtr100x_cluster_consist_hit_id[i].push_back(gtr100x_cluster_consist_hit_id->at(j)[k]);
				}
			}
		}

		int cid_200 = rk_hit_gtr200_xid->at(tid);//cluster id which is used in a track
		for(int j=0; j < n_gtr200x_clusters; j++){
			int cid = gtr200x_cluster_id->at(j);//cluster id from all cluster
//			std::cout << "cid = " << cid << std::endl;
//			std::cout << "cid200 = " << cid_200 << std::endl;
//			std::cout << "j  = " << j  << std::endl;
			if(cid_200 == cid){ //if both are matchej
//				std::cout << "size " << gtr200x_cluster_last_tot_end->size() << std::endl;
///				std::cout << "out_gtr size = i ,  " << i << ", " << out_gtr200x_cluster_last_tot_end.size() << std::endl;
            out_gtr200x_cluster_last_tot_end[i] = gtr200x_cluster_last_tot_end->at(j);//tot_end is filled
//				std::cout<< "hello " << std::endl;
			}
		}	
   	int cid_300 = rk_hit_gtr300_xid->at(tid);//cluster id which is used in a track
		for(int j=0; j < n_gtr300x_clusters; j++){
			int cid = gtr300x_cluster_id->at(j);//cluster id from all cluster
			if(cid_300 == cid){ //if both are matched
            out_gtr300x_cluster_last_tot_end[i] = gtr300x_cluster_last_tot_end->at(j);//tot_end is filled
			}
		}




		

	//	std::cout << "mom = " << rk_fit_init_mom_gz->at(tid) << std::endl;
		out_chi_square[i]       = chi_square->at(tid);
#ifndef NoExist_SSD
		out_rk_hit_sts_id[i]    = rk_hit_sts_id->at(tid) ;
		out_rk_hit_sts_gx[i]    = rk_hit_sts_gx->at(tid) ;
		out_rk_hit_sts_gy[i]    = rk_hit_sts_gy->at(tid) ;
		out_rk_hit_sts_gz[i]    = rk_hit_sts_gz->at(tid) ;
		out_rk_hit_sts_adc[i]   = rk_hit_sts_adc->at(tid) ;
		out_rk_hit_sts_t[i]     = rk_hit_sts_t->at(tid);
		out_rk_hit_sts_x[i]     = rk_hit_sts_x->at(tid);
		out_rk_hit_sts_chi2[i]  = rk_hit_sts_chi2->at(tid);
#endif

		out_rk_hit_gtr100_xid[i]    = rk_hit_gtr100_xid->at(tid) ;
		out_rk_hit_gtr200_xid[i]    = rk_hit_gtr200_xid->at(tid) ;
		out_rk_hit_gtr300_xid[i]    = rk_hit_gtr300_xid->at(tid) ;
	   out_rk_hit_gtr100_yid[i]    = rk_hit_gtr100_yid->at(tid) ;
	   out_rk_hit_gtr200_yid[i]    = rk_hit_gtr200_yid->at(tid) ;
	   out_rk_hit_gtr300_yid[i]    = rk_hit_gtr300_yid->at(tid) ;
		out_rk_hit_gtr100_gx[i]     = rk_hit_gtr100_gx->at(tid) ;
		out_rk_hit_gtr200_gx[i]     = rk_hit_gtr200_gx->at(tid) ;
		out_rk_hit_gtr300_gx[i]     = rk_hit_gtr300_gx->at(tid) ;
		out_rk_hit_gtr100_gy[i]     = rk_hit_gtr100_gy->at(tid) ;
		out_rk_hit_gtr200_gy[i]     = rk_hit_gtr200_gy->at(tid) ;
		out_rk_hit_gtr300_gy[i]     = rk_hit_gtr300_gy->at(tid) ;
		out_rk_hit_gtr100_gz[i]     = rk_hit_gtr100_gz->at(tid) ;
		out_rk_hit_gtr200_gz[i]     = rk_hit_gtr200_gz->at(tid) ;
		out_rk_hit_gtr300_gz[i]     = rk_hit_gtr300_gz->at(tid) ;
		out_rk_hit_gtr100_xadc[i]   = rk_hit_gtr100_xadc->at(tid) ;
		out_rk_hit_gtr200_xadc[i]   = rk_hit_gtr200_xadc->at(tid) ;
		out_rk_hit_gtr300_xadc[i]   = rk_hit_gtr300_xadc->at(tid) ;
		out_rk_hit_gtr100_yadc[i]   = rk_hit_gtr100_yadc->at(tid);
		out_rk_hit_gtr200_yadc[i]   = rk_hit_gtr200_yadc->at(tid);
		out_rk_hit_gtr300_yadc[i]   = rk_hit_gtr300_yadc->at(tid);
		out_rk_hit_gtr100_xt[i]     = rk_hit_gtr100_xt->at(tid);
		out_rk_hit_gtr200_xt[i]     = rk_hit_gtr200_xt->at(tid);
		out_rk_hit_gtr300_xt[i]     = rk_hit_gtr300_xt->at(tid);
		out_rk_hit_gtr100_yt[i]     = rk_hit_gtr100_yt->at(tid) ;
		out_rk_hit_gtr200_yt[i]     = rk_hit_gtr200_yt->at(tid) ;
		out_rk_hit_gtr300_yt[i]     = rk_hit_gtr300_yt->at(tid) ;
	   
		out_rk_hit_gtr100_tx2[i]    = rk_hit_gtr100_tx2->at(tid);
		out_rk_hit_gtr200_tx2[i]    = rk_hit_gtr200_tx2->at(tid);
		out_rk_hit_gtr300_tx2[i]    = rk_hit_gtr300_tx2->at(tid);
		out_rk_hit_gtr100_gtx[i]    = rk_hit_gtr100_gtx->at(tid);
		out_rk_hit_gtr200_gtx[i]    = rk_hit_gtr200_gtx->at(tid);
		out_rk_hit_gtr300_gtx[i]    = rk_hit_gtr300_gtx->at(tid);
		out_rk_hit_gtr100_gty[i]    = rk_hit_gtr100_gty->at(tid);
		out_rk_hit_gtr200_gty[i]    = rk_hit_gtr200_gty->at(tid);
		out_rk_hit_gtr300_gty[i]    = rk_hit_gtr300_gty->at(tid);
		out_rk_hit_gtr100_gtz[i]    = rk_hit_gtr100_gtz->at(tid);
		out_rk_hit_gtr200_gtz[i]    = rk_hit_gtr200_gtz->at(tid);
		out_rk_hit_gtr300_gtz[i]    = rk_hit_gtr300_gtz->at(tid);
		out_rk_hit_gtr100_gtx2[i]    = rk_hit_gtr100_gtx2->at(tid);
		out_rk_hit_gtr200_gtx2[i]    = rk_hit_gtr200_gtx2->at(tid);
		out_rk_hit_gtr300_gtx2[i]    = rk_hit_gtr300_gtx2->at(tid);
		out_rk_hit_gtr100_gty2[i]    = rk_hit_gtr100_gty2->at(tid);
		out_rk_hit_gtr200_gty2[i]    = rk_hit_gtr200_gty2->at(tid);
		out_rk_hit_gtr300_gty2[i]    = rk_hit_gtr300_gty2->at(tid);
		out_rk_hit_gtr100_gtz2[i]    = rk_hit_gtr100_gtz2->at(tid);
		out_rk_hit_gtr200_gtz2[i]    = rk_hit_gtr200_gtz2->at(tid);
		out_rk_hit_gtr300_gtz2[i]    = rk_hit_gtr300_gtz2->at(tid);
	

// -- fit res are 


#ifndef NoExist_SSD
      out_rk_fit_sts_mid[i]       = rk_fit_sts_mid->at(tid);
 	   out_rk_fit_sts_x[i]         = rk_fit_sts_x->at(tid)  ;
 	   out_rk_fit_sts_y[i] =   rk_fit_sts_y         ->at(tid);
 	   out_rk_fit_sts_gx[i] =   rk_fit_sts_gx       ->at(tid);
 	   out_rk_fit_sts_gy[i] =   rk_fit_sts_gy       ->at(tid);
 	   out_rk_fit_sts_gz[i] =   rk_fit_sts_gz       ->at(tid);
 	   out_rk_fit_sts_mom_x[i] =   rk_fit_sts_mom_x ->at(tid);
 	   out_rk_fit_sts_mom_y[i] =   rk_fit_sts_mom_y ->at(tid);
 	   out_rk_fit_sts_mom_z[i] =   rk_fit_sts_mom_z ->at(tid);
 	   out_rk_fit_sts_mom_gx[i] =  rk_fit_sts_mom_gx->at(tid);
 	   out_rk_fit_sts_mom_gy[i] =  rk_fit_sts_mom_gy->at(tid);
 	   out_rk_fit_sts_mom_gz[i] =  rk_fit_sts_mom_gz->at(tid);
#endif

      out_rk_fit_init_mom_gx[i]   = rk_fit_init_mom_gx->at(tid);
      out_rk_fit_init_mom_gy[i]   = rk_fit_init_mom_gy->at(tid);
      out_rk_fit_init_mom_gz[i]   = rk_fit_init_mom_gz->at(tid);
      out_rk_fit_init_pos_gx[i]   = rk_fit_init_pos_gx->at(tid);
      out_rk_fit_init_pos_gy[i]   = rk_fit_init_pos_gy->at(tid);
      out_rk_fit_init_pos_gz[i]   = rk_fit_init_pos_gz->at(tid);
      out_rk_fit_gtr100_mid[i]    = rk_fit_gtr100_mid->at(tid);  
      out_rk_fit_gtr200_mid[i]    = rk_fit_gtr200_mid->at(tid);  
		out_rk_fit_gtr300_mid[i]    = rk_fit_gtr300_mid->at(tid);  
      out_rk_fit_gtr100_x[i]      = rk_fit_gtr100_x->at(tid);  
      out_rk_fit_gtr200_x[i]      = rk_fit_gtr200_x->at(tid);  
      out_rk_fit_gtr300_x[i]      = rk_fit_gtr300_x->at(tid);  
      out_rk_fit_gtr100_y[i]      = rk_fit_gtr100_y->at(tid);  
      out_rk_fit_gtr200_y[i]      = rk_fit_gtr200_y->at(tid);  
      out_rk_fit_gtr300_y[i]      = rk_fit_gtr300_y->at(tid);  
      out_rk_fit_gtr100_gx[i]     = rk_fit_gtr100_gx->at(tid);  
      out_rk_fit_gtr200_gx[i]     = rk_fit_gtr200_gx->at(tid);  
      out_rk_fit_gtr300_gx[i]     = rk_fit_gtr300_gx->at(tid);  
      out_rk_fit_gtr100_gy[i]     = rk_fit_gtr100_gy->at(tid);  
      out_rk_fit_gtr200_gy[i]     = rk_fit_gtr200_gy->at(tid);  
      out_rk_fit_gtr300_gy[i]     = rk_fit_gtr300_gy->at(tid);  
      out_rk_fit_gtr100_gz[i]     = rk_fit_gtr100_gz->at(tid);  
      out_rk_fit_gtr200_gz[i]     = rk_fit_gtr200_gz->at(tid);  
      out_rk_fit_gtr300_gz[i]     = rk_fit_gtr300_gz->at(tid);  
      out_rk_fit_gtr100_mom_x[i]  = rk_fit_gtr100_mom_x->at(tid);
      out_rk_fit_gtr200_mom_x[i]  = rk_fit_gtr200_mom_x->at(tid);
      out_rk_fit_gtr300_mom_x[i]  = rk_fit_gtr300_mom_x->at(tid);
      out_rk_fit_gtr100_mom_y[i]  = rk_fit_gtr100_mom_y->at(tid);
      out_rk_fit_gtr200_mom_y[i]  = rk_fit_gtr200_mom_y->at(tid);
      out_rk_fit_gtr300_mom_y[i]  = rk_fit_gtr300_mom_y->at(tid);
      out_rk_fit_gtr100_mom_z[i]  = rk_fit_gtr100_mom_z->at(tid);
      out_rk_fit_gtr200_mom_z[i]  = rk_fit_gtr200_mom_z->at(tid);
      out_rk_fit_gtr300_mom_z[i]  = rk_fit_gtr300_mom_z->at(tid);
      out_rk_fit_gtr100_mom_gx[i] = rk_fit_gtr100_mom_gx->at(tid);
      out_rk_fit_gtr200_mom_gx[i] = rk_fit_gtr200_mom_gx->at(tid);
      out_rk_fit_gtr300_mom_gx[i] = rk_fit_gtr300_mom_gx->at(tid);
      out_rk_fit_gtr100_mom_gy[i] = rk_fit_gtr100_mom_gy->at(tid);
      out_rk_fit_gtr200_mom_gy[i] = rk_fit_gtr200_mom_gy->at(tid);
      out_rk_fit_gtr300_mom_gy[i] = rk_fit_gtr300_mom_gy->at(tid);
      out_rk_fit_gtr100_mom_gz[i] = rk_fit_gtr100_mom_gz->at(tid);
      out_rk_fit_gtr200_mom_gz[i] = rk_fit_gtr200_mom_gz->at(tid);
      out_rk_fit_gtr300_mom_gz[i] = rk_fit_gtr300_mom_gz->at(tid);
      out_rk_res_init_pos_gx[i]   = rk_res_init_pos_gx->at(tid); 
      out_rk_res_init_pos_gy[i]   = rk_res_init_pos_gy->at(tid); 
      out_rk_res_init_pos_gz[i]   = rk_res_init_pos_gz->at(tid); 
      out_rk_res_init_mom_gx[i]   = rk_res_init_mom_gx->at(tid); 
      out_rk_res_init_mom_gy[i]   = rk_res_init_mom_gy->at(tid); 
      out_rk_res_init_mom_gz[i]   = rk_res_init_mom_gz->at(tid); 
#ifndef NoExist_SSD
      out_rk_res_sts_x[i]         = rk_res_sts_x->at(tid);        
#endif
      out_rk_res_gtr100_x[i]      = rk_res_gtr100_x->at(tid);
      out_rk_res_gtr100_y[i]      = rk_res_gtr100_y->at(tid);
      out_rk_res_gtr200_x[i]      = rk_res_gtr200_x->at(tid);
      out_rk_res_gtr200_y[i]      = rk_res_gtr200_y->at(tid);
      out_rk_res_gtr300_x[i]      = rk_res_gtr300_x->at(tid);
      out_rk_res_gtr300_y[i]      = rk_res_gtr300_y->at(tid);
//      out_rk_res_gtr100_tx[i]     = fit_results[1].residual_pos.X(); 
//      out_rk_res_gtr100_ty[i]     = fit_results[1].residual_pos.X(); 
//      out_rk_res_gtr200_tx[i]     = fit_results[2].residual_pos.X(); 
//      out_rk_res_gtr200_ty[i]     = fit_results[2].residual_pos.X(); 
//      out_rk_res_gtr300_tx[i]     = fit_results[3].residual_pos.X(); 
//      out_rk_res_gtr300_ty[i]     = fit_results[3].residual_pos.X(); 
//      out_rk_res_gtr100_tx2[i]    = fit_results[1].residual_pos.X(); 
//      out_rk_res_gtr200_tx2[i]    = fit_results[2].residual_pos.X(); 
//      out_rk_res_gtr300_tx2[i]    = fit_results[3].residual_pos.X(); 
		
    out_rk_fit_lg_c_mid[i]  = rk_fit_lg_c_mid->at(tid);
    out_rk_fit_lg_c_x[i] =  rk_fit_lg_c_x->at(tid);
    out_rk_fit_lg_c_y[i] =  rk_fit_lg_c_y->at(tid);
    out_rk_fit_lg_c_gx[i] = rk_fit_lg_c_gx->at(tid);
    out_rk_fit_lg_c_gy[i] = rk_fit_lg_c_gy->at(tid);
    out_rk_fit_lg_c_gz[i] = rk_fit_lg_c_gz->at(tid);
    out_rk_fit_lg_c_mom_x[i] = rk_fit_lg_c_mom_x->at(tid);
    out_rk_fit_lg_c_mom_y[i] = rk_fit_lg_c_mom_y->at(tid);
    out_rk_fit_lg_c_mom_z[i] = rk_fit_lg_c_mom_z->at(tid);
    out_rk_fit_lg_c_mom_gx[i] =rk_fit_lg_c_mom_gx->at(tid);
    out_rk_fit_lg_c_mom_gy[i] =rk_fit_lg_c_mom_gy->at(tid);
    out_rk_fit_lg_c_mom_gz[i] =rk_fit_lg_c_mom_gz->at(tid);
    out_rk_fit_lg_b_mid[i] =   rk_fit_lg_b_mid->at(tid);
    out_rk_fit_lg_b_x[i] =      rk_fit_lg_b_x->at(tid);
    out_rk_fit_lg_b_y[i] =      rk_fit_lg_b_y->at(tid);
    out_rk_fit_lg_b_gx[i] =     rk_fit_lg_b_gx->at(tid);
    out_rk_fit_lg_b_gy[i] =     rk_fit_lg_b_gy->at(tid);
    out_rk_fit_lg_b_gz[i] =     rk_fit_lg_b_gz->at(tid);
    out_rk_fit_lg_b_mom_x[i] =  rk_fit_lg_b_mom_x->at(tid);
    out_rk_fit_lg_b_mom_y[i] =  rk_fit_lg_b_mom_y->at(tid);
    out_rk_fit_lg_b_mom_z[i] =  rk_fit_lg_b_mom_z->at(tid);
    out_rk_fit_lg_b_mom_gx[i] = rk_fit_lg_b_mom_gx->at(tid);
    out_rk_fit_lg_b_mom_gy[i] = rk_fit_lg_b_mom_gy->at(tid);
    out_rk_fit_lg_b_mom_gz[i] = rk_fit_lg_b_mom_gz->at(tid);
    out_rk_fit_lg_a_mid[i] =    rk_fit_lg_a_mid->at(tid);
    out_rk_fit_lg_a_x[i] =      rk_fit_lg_a_x->at(tid);
    out_rk_fit_lg_a_y[i] =      rk_fit_lg_a_y->at(tid);
    out_rk_fit_lg_a_gx[i] =     rk_fit_lg_a_gx->at(tid);
    out_rk_fit_lg_a_gy[i] =     rk_fit_lg_a_gy->at(tid);
    out_rk_fit_lg_a_gz[i] =     rk_fit_lg_a_gz->at(tid);
    out_rk_fit_lg_a_mom_x[i] =  rk_fit_lg_a_mom_x->at(tid);
    out_rk_fit_lg_a_mom_y[i] =  rk_fit_lg_a_mom_y->at(tid);
    out_rk_fit_lg_a_mom_z[i] =  rk_fit_lg_a_mom_z->at(tid);
    out_rk_fit_lg_a_mom_gx[i] = rk_fit_lg_a_mom_gx->at(tid);
    out_rk_fit_lg_a_mom_gy[i] = rk_fit_lg_a_mom_gy->at(tid);
    out_rk_fit_lg_a_mom_gz[i] = rk_fit_lg_a_mom_gz->at(tid);





     	out_rk_proj_lg_id[i]     = rk_proj_lg_id->at(tid);
		out_rk_proj_lg_mid[i]    = rk_proj_lg_mid->at(tid);
		out_rk_proj_lg_cid[i]    = rk_proj_lg_cid->at(tid);
	   out_rk_proj_lg_x[i]      = rk_proj_lg_x->at(tid);
		out_rk_proj_lg_y[i]      = rk_proj_lg_y->at(tid);
		out_rk_proj_lg_adc[i]    = rk_proj_lg_adc->at(tid);
		out_rk_proj_lg_t[i]      = rk_proj_lg_t->at(tid);
		out_rk_proj_lg_npeaks[i] = rk_proj_lg_npeaks->at(tid);
		out_rk_proj_lg_fflag[i]  = rk_proj_lg_fflag->at(tid);

   out_rk_hit_gtr100_cogx[i] = rk_hit_gtr100_cogx->at(tid);
   out_rk_hit_gtr200_cogx[i] = rk_hit_gtr200_cogx->at(tid);
   out_rk_hit_gtr300_cogx[i] = rk_hit_gtr300_cogx->at(tid);
   out_rk_hit_gtr100_cogy[i] = rk_hit_gtr100_cogy->at(tid);
   out_rk_hit_gtr200_cogy[i] = rk_hit_gtr200_cogy->at(tid);
   out_rk_hit_gtr200_cogy[i] = rk_hit_gtr200_cogy->at(tid);
	
   out_rk_hit_gtr100_xt4[i] = rk_hit_gtr100_xt4->at(tid);
   out_rk_hit_gtr200_xt4[i] = rk_hit_gtr200_xt4->at(tid);
   out_rk_hit_gtr300_xt4[i] = rk_hit_gtr300_xt4->at(tid);
   //out_rk_hit_gtr100_yt4[i] = rk_hit_gtr100_yt4->at(i);
   //out_rk_hit_gtr200_yt4[i] = rk_hit_gtr200_yt4->at(i);
   //out_rk_hit_gtr300_yt4[i] = rk_hit_gtr300_yt4->at(i);
   //
   //
 

	for(int i=0; i < n_pairs; i++){
		auto& pair = track_pairs[i];
		out_rk_pair_distance[i] = pair.distance;
		out_rk_pair_minus_track_id[i] = pair.tid0;
		out_rk_pair_plus_track_id[i]  = pair.tid1;
      out_rk_pair_minus_chi_square[i] = chi_square->at(pair.tid0);	
      out_rk_pair_plus_chi_square[i] = chi_square->at(pair.tid1);	

		auto& pair_vtx = pair.vtx;
		out_rk_pair_vtx_gx[i] = pair_vtx.X();
		out_rk_pair_vtx_gy[i] = pair_vtx.Y();
		out_rk_pair_vtx_gz[i] = pair_vtx.Z();
	
       out_rk_pair_is_refit[i] = pair.is_refit;
       out_rk_pair_is_selected[i] = pair.is_selected;
       out_rk_pair_chi_square_refit[i] = pair.chi_square_refit;
       auto& pair_vtx_refit = pair.vtx_refit;
       out_rk_pair_vtx_refit_gx[i] = pair_vtx_refit.X();
       out_rk_pair_vtx_refit_gy[i] = pair_vtx_refit.Y();
       out_rk_pair_vtx_refit_gz[i] = pair_vtx_refit.Z();
       auto& mmom_refit = pair.mom_minus_refit;
       out_rk_pair_minus_mom_refit_gx[i] = mmom_refit.X();
       out_rk_pair_minus_mom_refit_gy[i] = mmom_refit.Y();
       out_rk_pair_minus_mom_refit_gz[i] = mmom_refit.Z();
       auto& pmom_refit = pair.mom_plus_refit;
       out_rk_pair_plus_mom_refit_gx[i] = pmom_refit.X();
       out_rk_pair_plus_mom_refit_gy[i] = pmom_refit.Y();
       out_rk_pair_plus_mom_refit_gz[i] = pmom_refit.Z();
       auto& mposs_refit = pair.track_minus_pos_refit;
       auto& pposs_refit = pair.track_plus_pos_refit;
       auto& mmoms_refit = pair.track_minus_mom_refit;
       auto& pmoms_refit = pair.track_plus_mom_refit;
       auto& mress_refit = pair.track_minus_res_refit;
       auto& press_refit = pair.track_plus_res_refit;
#ifndef NoExist_SSD
       out_rk_pair_minus_sts_pos_refit_gx[i] = mposs_refit[0].X();
       out_rk_pair_minus_sts_pos_refit_gy[i] = mposs_refit[0].Y();
       out_rk_pair_minus_sts_pos_refit_gz[i] = mposs_refit[0].Z();
       out_rk_pair_plus_sts_pos_refit_gx[i] = pposs_refit[0].X();
       out_rk_pair_plus_sts_pos_refit_gy[i] = pposs_refit[0].Y();
       out_rk_pair_plus_sts_pos_refit_gz[i] = pposs_refit[0].Z();
       out_rk_pair_minus_sts_mom_refit_gx[i] = mmoms_refit[0].X();
       out_rk_pair_minus_sts_mom_refit_gy[i] = mmoms_refit[0].Y();
       out_rk_pair_minus_sts_mom_refit_gz[i] = mmoms_refit[0].Z();
       out_rk_pair_plus_sts_mom_refit_gx[i] = pmoms_refit[0].X();
       out_rk_pair_plus_sts_mom_refit_gy[i] = pmoms_refit[0].Y();
       out_rk_pair_plus_sts_mom_refit_gz[i] = pmoms_refit[0].Z();
       out_rk_pair_minus_sts_res_refit_x[i] = mress_refit[0].X();
       out_rk_pair_minus_sts_res_refit_y[i] = mress_refit[0].Y();
       out_rk_pair_minus_sts_res_refit_z[i] = mress_refit[0].Z();
       out_rk_pair_plus_sts_res_refit_x[i] = press_refit[0].X();
       out_rk_pair_plus_sts_res_refit_y[i] = press_refit[0].Y();
       out_rk_pair_plus_sts_res_refit_z[i] = press_refit[0].Z();
#endif
       out_rk_pair_minus_gtr100_pos_refit_gx[i] = mposs_refit[1].X();
       out_rk_pair_minus_gtr100_pos_refit_gy[i] = mposs_refit[1].Y();
       out_rk_pair_minus_gtr100_pos_refit_gz[i] = mposs_refit[1].Z();
       out_rk_pair_minus_gtr200_pos_refit_gx[i] = mposs_refit[2].X();
       out_rk_pair_minus_gtr200_pos_refit_gy[i] = mposs_refit[2].Y();
       out_rk_pair_minus_gtr200_pos_refit_gz[i] = mposs_refit[2].Z();
       out_rk_pair_minus_gtr300_pos_refit_gx[i] = mposs_refit[3].X();
       out_rk_pair_minus_gtr300_pos_refit_gy[i] = mposs_refit[3].Y();
       out_rk_pair_minus_gtr300_pos_refit_gz[i] = mposs_refit[3].Z();
       out_rk_pair_plus_gtr100_pos_refit_gx[i] = pposs_refit[1].X();
       out_rk_pair_plus_gtr100_pos_refit_gy[i] = pposs_refit[1].Y();
       out_rk_pair_plus_gtr100_pos_refit_gz[i] = pposs_refit[1].Z();
       out_rk_pair_plus_gtr200_pos_refit_gx[i] = pposs_refit[2].X();
       out_rk_pair_plus_gtr200_pos_refit_gy[i] = pposs_refit[2].Y();
       out_rk_pair_plus_gtr200_pos_refit_gz[i] = pposs_refit[2].Z();
       out_rk_pair_plus_gtr300_pos_refit_gx[i] = pposs_refit[3].X();
       out_rk_pair_plus_gtr300_pos_refit_gy[i] = pposs_refit[3].Y();
       out_rk_pair_plus_gtr300_pos_refit_gz[i] = pposs_refit[3].Z();
       out_rk_pair_minus_gtr100_mom_refit_gx[i] = mmoms_refit[1].X();
       out_rk_pair_minus_gtr100_mom_refit_gy[i] = mmoms_refit[1].Y();
       out_rk_pair_minus_gtr100_mom_refit_gz[i] = mmoms_refit[1].Z();
       out_rk_pair_minus_gtr200_mom_refit_gx[i] = mmoms_refit[2].X();
       out_rk_pair_minus_gtr200_mom_refit_gy[i] = mmoms_refit[2].Y();
       out_rk_pair_minus_gtr200_mom_refit_gz[i] = mmoms_refit[2].Z();
       out_rk_pair_minus_gtr300_mom_refit_gx[i] = mmoms_refit[3].X();
       out_rk_pair_minus_gtr300_mom_refit_gy[i] = mmoms_refit[3].Y();
       out_rk_pair_minus_gtr300_mom_refit_gz[i] = mmoms_refit[3].Z();
       out_rk_pair_plus_gtr100_mom_refit_gx[i] = pmoms_refit[1].X();
       out_rk_pair_plus_gtr100_mom_refit_gy[i] = pmoms_refit[1].Y();
       out_rk_pair_plus_gtr100_mom_refit_gz[i] = pmoms_refit[1].Z();
       out_rk_pair_plus_gtr200_mom_refit_gx[i] = pmoms_refit[2].X();
       out_rk_pair_plus_gtr200_mom_refit_gy[i] = pmoms_refit[2].Y();
       out_rk_pair_plus_gtr200_mom_refit_gz[i] = pmoms_refit[2].Z();
       out_rk_pair_plus_gtr300_mom_refit_gx[i] = pmoms_refit[3].X();
       out_rk_pair_plus_gtr300_mom_refit_gy[i] = pmoms_refit[3].Y();
       out_rk_pair_plus_gtr300_mom_refit_gz[i] = pmoms_refit[3].Z();
       out_rk_pair_minus_gtr100_res_refit_x[i] = mress_refit[1].X();
       out_rk_pair_minus_gtr100_res_refit_y[i] = mress_refit[1].Y();
       out_rk_pair_minus_gtr100_res_refit_z[i] = mress_refit[1].Z();
       out_rk_pair_minus_gtr200_res_refit_x[i] = mress_refit[2].X();
       out_rk_pair_minus_gtr200_res_refit_y[i] = mress_refit[2].Y();
       out_rk_pair_minus_gtr200_res_refit_z[i] = mress_refit[2].Z();
       out_rk_pair_minus_gtr300_res_refit_x[i] = mress_refit[3].X();
       out_rk_pair_minus_gtr300_res_refit_y[i] = mress_refit[3].Y();
       out_rk_pair_minus_gtr300_res_refit_z[i] = mress_refit[3].Z();
       out_rk_pair_plus_gtr100_res_refit_x[i] = press_refit[1].X();
       out_rk_pair_plus_gtr100_res_refit_y[i] = press_refit[1].Y();
       out_rk_pair_plus_gtr100_res_refit_z[i] = press_refit[1].Z();
       out_rk_pair_plus_gtr200_res_refit_x[i] = press_refit[2].X();
       out_rk_pair_plus_gtr200_res_refit_y[i] = press_refit[2].Y();
       out_rk_pair_plus_gtr200_res_refit_z[i] = press_refit[2].Z();
       out_rk_pair_plus_gtr300_res_refit_x[i] = press_refit[3].X();
       out_rk_pair_plus_gtr300_res_refit_y[i] = press_refit[3].Y();
       out_rk_pair_plus_gtr300_res_refit_z[i] = press_refit[3].Z();
		}
	}
	outtree->Fill();	
}//AddReco













#endif // #ifdef E16DSTN_ReStraightV2_cxx

