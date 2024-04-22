#include "E16DSTN_ReadStraightTree.hh"
#include "E16DSTN_StraightParameter.hh"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include <array>



using namespace std;
using namespace E16DSTN_StraightParameter;

void E16DSTN_ReadStraightTree::ClearUsedClusterIDs() {
	for(auto& ids : used_cluster_ids){
		ids.clear();
	}
	return;
}

bool E16DSTN_ReadStraightTree::HasUsedCluster(const array<int, kNumTrackingDetectors> &cids){
  for (int i = 0; i < kNumTrackingDetectors; ++i) {
     for (const auto& used_id : used_cluster_ids[i]) {
       if (cids[i] == used_id) {
         return true;
       }
     }
   }
   return false;
}

bool E16DSTN_ReadStraightTree::IsComingFromTarget(int n){
	if(isWire){
		if(fabs(rk_fit_init_pos_gy->at(n)) < 5){
			return true;
		}
		else {
			return false;
		}
	}//wire 
	else{
		std::cerr << "not developed yet" << std::endl; 
	}
	return false;
}


bool E16DSTN_ReadStraightTree::IsGoodTrack(int n){
//	if (kUsePosAtTargetCut && !NearestRadius(n) > kMaxRadiusAtTarget){
//		return false;	
			if(IsComingFromTarget(n)){
					if (kUseClusterDuplicationCut == kSSDAndGTRDuplicationCut){
						std::array<int, kNumTrackingDetectors> cids = {
#ifndef NoExist_SSD
						rk_hit_ssd_id->at(n),
						rk_hit_gtr100_xid->at(n), rk_hit_gtr100_yid->at(n), 
						rk_hit_gtr200_xid->at(n), rk_hit_gtr200_yid->at(n),
						rk_hit_gtr300_xid->at(n), rk_hit_gtr300_yid->at(n)};
#else
						rk_hit_gtr100_xid->at(n), rk_hit_gtr100_yid->at(n), 
						rk_hit_gtr200_xid->at(n), rk_hit_gtr200_yid->at(n),
						rk_hit_gtr300_xid->at(n), rk_hit_gtr300_yid->at(n)};
#endif
						if(HasUsedCluster(cids)) {
							return false;
						}
#ifndef NoExist_SSD
						for (int i =0; i < kNumTrackingDetectors;i++){
#else
						for (int i =0; i < kNumTrackingDetectors-1;i++){
#endif
							used_cluster_ids[i].emplace_back(cids[i]);
						}

					}
			}
			return true;
}

void E16DSTN_ReadStraightTree::SetTracks(){
	selected_ids.clear();
	for (int i=0; i < n_cands; i++){
      std::cout << "i = " << i << std::endl;
		if(kUseChi2Cut && chi_square->at(i) > kMaxChi2){
			break;
		}
		if (IsGoodTrack(i)){
			selected_ids.emplace_back(i);
		}
	}
	return;
}

void E16DSTN_ReadStraightTree::Loop(TTree* tree, int print_cycle, int max_event){
	int nevent = tree->GetEntries();

	for(int n=0; n < nevent; n++){
	if( max_event != -1 && n > max_event){
			std::cout << "N Event Analyzed reached to max event " << std::endl;
			break;
		}
		if (n % print_cycle == 0) {
			printf(" N Analyzed = %d \n", n);
		} 

	tree->GetEntry(n);
// NOT necessary, dst1 tracks are already sorted by chi2
//	std::multimap<double, int> chi2_map;
//	chi2_map.clear();
//	std::vector<int> sorted_trkid;
//	sorted_trkid.clear();
//	std::vector<int> nodup_id;
//	nodup_id.clear();
//	if(chi_square->size() != track_id->size()){
//		std::cout << "size is different !" << std::endl;
//	}
//	for(int i=0; i<n_cands; i++){
//     	chi2_map.insert({chi_square->at(i), track_id->at(i)});
//   }	
//   for (const auto& pair : chi2_map) {
//   	sorted_trkid.push_back(pair.second);
//	}

	ClearUsedClusterIDs();
	SetTracks();
////		RKFittingWoOneLayer(nodup_id, 2);//removed layer 2 = GTR200
//	if(removed_layer !=-1 ){
//		ChooseSmallestResidual(nodup_id, selected_id);//if There is removed_layer
//	}
		AddRecord();
	} 
}

//void E16DSTN_ReadStraightTree::AfterKillDupLoop(TTree* tree, int print_cycle, int max_event,bool vertex_xy_fix_flag, bool py_fix_flag, bool vetex_z_fix_flag, bool isWire, int removed_layer){
//
//	int nevent = tree->GetEntries();
//	for(int n=0; n < nevent; n++){
//	if( max_event != -1 && n > max_event){
//			std::cout << "N Event Analyzed reached to max event " << std::endl;
//			break;
//		}
//		if (n % print_cycle == 0) {
//			printf(" N Re-Analyzed = %d \n", n);
//		} 
//	nodup_tracks.clear();
//	tree->GetEntry(n);
//	Re-FittingPrepare();
//	Re-RKFitting();
//	Re-AddRecord();
//	} 
//}





void E16DSTN_ReadStraightTree::ChooseSmallestResidual(std::vector<int> &nudup_ids, std::vector<int> &selected_id){
//	std::multimap<double, int> res_map;
//	res_map.clear();
//	std::vector<int> sorted_id;//will be sorted with residual
//	sorted_id.clear();
//	for(const int tid : selected_ids){
//     	if(removed_layer == 1) res_map.insert({rk_res_gtr100_x->at(tid), tid});
//     	if(removed_layer == 2) res_map.insert({rk_res_gtr200_x->at(tid), tid});
//     	if(removed_layer == 3) res_map.insert({rk_res_gtr300_x->at(tid), tid});
//   }	
//   for (const auto& pair : res_map) {
//   	sorted_id.push_back(pair.second);
//	}
//	int max  =  20000;
//	if(removed_layer == 2) {
//		bool x1_table[max] = {};
//		std::fill(x1_table, x1_table + max, 0);
//		for(const int tid : sorted_id){
//			int x1id = rk_hit_gtr200_xid->at(tid);//gtr200 remove
//			if(x1_table[x1id] == 0){
//				x1_table[x1id] = 1; 
//				selected_id.push_back(tid);
//			}
//			else {
//				// nothing to do
//			}	
//		}
//	}
}




void E16DSTN_ReadStraightTree::DrawHist(TTree* tree, int n_maxevent, int print_cycle, TString pdf_name){	
	const int n_module = 10;
	const int n_layer = 4;
	const int n_tgt = 2;
	const int n_div = 5;//divide x direction
	int htdiv[10]   = {0,  6,  6,  6,  6, 0, 8,  7,  8,  6};
	int hdzdiv[10]  = {0, 60, 60, 60, 40, 0, 40, 36, 50, 60};
	const double sideLen[4] = {58, 100, 200, 300};

	TH1D* h_chi2;
	TH1D* h_t0diff;
	TH1D* h_n_runid;
	TH1D* h_n_eventid;
	TH1D* h_n_spillid;


	TH1D* h_chi2_mod[n_module];
	TH1D* h_lg_t_mod[n_module];
	TH1D* h_tgt_proj_z_raw[n_module];
	TH1D* h_tgt_proj_z_cut[n_module];
	TH1D* h_tgt_proj_z_chi2cut[n_module];
	TH1D* h_tgt_proj_x[n_module];
	TH1D* h_tgt_proj_y[n_module];
	TH1D* h_res_x[n_tgt][n_module][n_layer];
	TH1D* h_res_y[n_tgt][n_module][n_layer];
	TH1D* h_tan_theta[n_tgt][n_module][n_layer];
	TH1D* h_fitlx[n_tgt][n_module][n_layer];

	TH2D* h_tgt_pos;
	TH2D* h_tgt_pos_mod_raw[n_module];
	TH2D* h_tgt_pos_mod_cut[n_module];
	TH2D* h_cor_dz_time[n_tgt][n_module][n_layer][n_div];
	TH2D* h_cor_dz_time_t0cor[n_tgt][n_module][n_layer][n_div];
	TH2D* h_cor_res_fitlx[n_tgt][n_module][n_layer];
	TH2D* h_cor_res_fitly[n_tgt][n_module][n_layer];
	TH2D* h_cor_res_timing[n_tgt][n_module][n_layer];
	
	TH2D* h_slopevel[n_tgt][n_module][n_layer][n_div];

	TH2D* h_trackmap[n_tgt][n_module];


	h_n_runid = new TH1D("n of events of runid","n of events of runid", 15, 30331.5, 30346.5);
	h_n_eventid = new TH1D("n of events of event id","n of events of eventid", 10000, -0.5, 9999.5);
	h_n_spillid = new TH1D("n of events of spill id","n of events of spillid", 1000, -0.5, 999.5);
	h_chi2    = new TH1D(Form("h_chi2"), Form("h_chi2"), 100, 0, 100);	
	h_t0diff    = new TH1D(Form("h_t0diff"), Form("h_t0diff"), 100, -100,100);	
	h_tgt_pos = new TH2D(Form("h_tgt_pos"), Form("h_tgt_pos"), 50, 19.8, 20.2, 200, -60, 60);
	for(int m=0; m < n_module; m++){
		for(int tg=0; tg < 2; tg++){
			h_trackmap[tg][m] = new TH2D(Form("h_track_map%d_%d", tg,  m+100), Form("h_track_map%d_%d",tg,  m+100), 25, -50, 50, 25, -50, 50);
		}
		h_chi2_mod[m] = new TH1D(Form("h_chi2_mod%d", m+100), Form("h_chi2_mod%d", m+100), 100, 0, 100);
		h_lg_t_mod[m] = new TH1D(Form("h_lg_t_mod%d", m+100), Form("h_lg_t_mod%d", m+100), 100, 50, 150);
		h_tgt_pos_mod_raw[m] = new TH2D(Form("h_tgt_pos_mod_raw_%d", m+100), Form("h_tgt_pos_mod_raw_%d", m+100), 50, 19.8, 20.2, 60, -60, 60);
		h_tgt_pos_mod_cut[m] = new TH2D(Form("h_tgt_pos_mod_cut_%d", m+100), Form("h_tgt_pos_mod_cut_%d", m+100), 50, 19.8, 20.2, 60, -60, 60);
		h_tgt_proj_z_raw[m] = new TH1D(Form("h_tgt_proj_z_raw%d", m+100), Form("h_tgt_proj_z_raw%d", m+100), 100, -60, 60);
		h_tgt_proj_z_cut[m] = new TH1D(Form("h_tgt_proj_z_cut%d", m+100), Form("h_tgt_proj_z_cut%d", m+100), 100, -60, 60);
		h_tgt_proj_z_chi2cut[m] = new TH1D(Form("h_tgt_proj_z_chi2cut%d", m+100), Form("h_tgt_proj_z_chi2cut%d", m+100), 100, -45, 45);
		h_tgt_proj_x[m] = new TH1D(Form("h_tgt_proj_x%d", m+100), Form("h_tgt_proj_x%d", m+100), 100, 19.8, 20.2);
		h_tgt_proj_y[m] = new TH1D(Form("h_tgt_proj_y%d", m+100), Form("h_tgt_proj_y%d", m+100), 100, -5,5 );
		for(int l=0; l < n_layer; l++){// -- layer 
			for(int t=0; t < n_tgt; t++){
				h_fitlx[t][m][l] = new TH1D(Form("h_fitlx_tgt%d_m%d_l%d",t, m+100, l), Form("h_fitlx_tgt%d_m%d_l%d",t, m+100, l), 100, -2, 2);
				h_res_x[t][m][l] = new TH1D(Form("h_res_x_tgt%d_m%d_l%d",t, m+100, l), Form("h_res_x_tgt%d_m%d_l%d",t, m+100, l), 100, -2, 2);
				h_res_y[t][m][l] = new TH1D(Form("h_res_y_tgt%d_m%d_l%d",t, m+100, l), Form("h_res_y_tgt%d_m%d_l%d",t, m+100, l), 100, -4, 4);
				h_cor_res_fitlx[t][m][l] = new TH2D(Form("h_cor_res_fitlx_%d_%d_%d", t,m+100, l), Form("h_cor_res_fitlx_%d_%d%_d", t,m+100, l), 20, -50*l , 50*l, 100, -2, 2);
				h_cor_res_fitly[t][m][l] = new TH2D(Form("h_cor_res_fitly_%d_%d_%d", t,m+100, l), Form("h_cor_res_fitly_%d_%d%_d", t,m+100, l), 20, -50*l , 50*l, 100, -2, 2);
				h_cor_res_timing[t][m][l] = new TH2D(Form("h_cor_res_timing_%d_%d_%d", t,m+100, l), Form("h_cor_res_timing_%d_%d%_d", t,m+100, l), 20, 0 , 600, 100, -2, 2);
			h_tan_theta[t][m][l] = new TH1D(Form("h_tan_theta_t%d_m%d_l%d", t, m+100, l), Form("h_tan_theta%d_%d_%d", t,m+100, l), 100, -0.5, 0.5);
			for(int div = 0 ; div < n_div; div++){
			h_cor_dz_time[t][m][l][div]        = new TH2D(Form("h_cor_dz_time_%d_%d%d%d",t,  m+100, l, div)      , Form("h_cor_dz_time_%d%d%d%d",t,  m+100, l, div)      , htdiv[m], 0, 600, hdzdiv[m], -8, 8);
			h_cor_dz_time_t0cor[t][m][l][div] = new TH2D(Form("h_cor_dz_time_t0cor_%d%d_%d%d", t, m+100, l,div), Form("h_cor_dz_time_t0cor_%d%d%d%d",t, m+100, l,div), htdiv[m], 0, 600, hdzdiv[m], -8, 8);
			h_slopevel[t][m][l][div] = new TH2D(Form("h_slopevel_%d%d_%d%d", t, m+100, l,div), Form("h_slopevel_%d%d%d%d",t, m+100, l,div),  25, -100, 100, 60, -2, 2);
		}
			}
		}
	}
	int nevent = tree->GetEntries();
   int fixl;
#ifdef REMOVE_100
	 fixl   = 1; //gtr200
#endif
#ifdef REMOVE_200
	 fixl   = 2; //gtr200
#endif
#ifdef REMOVE_300
	 fixl   = 3; //gtr200
#endif

								//    00, 01, 02, 03, 04, 05,    06
	double chi2_th[n_module] = {30, 30,30, 30, 30,   0,   30, 30, 30, 30};//mod100-109
	double res_min[n_module] = {0, -4, -4, -4, -4,   0,   -4, -4, -4, -4};//mod100-109
	double res_max[n_module] = {0,  4,  4,  4,  4,   0,    4,  4,  4,  4};//mod100-109
	double timing_cut = 120;
	double tgty_cut = 3.0;

std::array<int, 4> mids;
std::array<double, 4> resx;
std::array<double, 4> resy;
std::array<double, 4> fitlxs;
std::array<double, 4> fitlys;
std::array<double, 4> tans;//tan thetas
std::array<double, 4> xt4s;//xt4

	for(int n=0; n < nevent; n++){
		if(n > n_maxevent) break;
		if (n % print_cycle == 0) {
			printf(" N Analyzed = %d \n", n);
		} 
		tree->GetEntry(n);
		h_n_runid->Fill(run_id);
		h_n_eventid->Fill(event_id);
		h_n_spillid->Fill(spill_id);


		int n_tracks = chi_square->size();//note that n tracks are judged with chi2 vec
		for(int i=0; i < n_tracks; i++){
			std::cout << "i2 = " << i << std::endl;
//			if(rk_fit_gtr100_mid->at(i) < 105 || rk_fit_gtr100_mid->at(i) > 107) continue;
			double chi2  = chi_square->at(i);
			std::cout << "chi2 = " << chi2 << std::endl;
			int    mid   = rk_fit_gtr200_mid->at(i);

#ifndef NoExist_SSD
			double ssd_t = rk_hit_ssd_t->at(i);
#endif
			std::cout << "mid  = " << mid << std::endl;

			mids = {	
						
#ifndef NoExist_SSD
rk_fit_ssd_mid->at(i),
#else 
0,
#endif
						rk_fit_gtr100_mid->at(i),						
						rk_fit_gtr200_mid->at(i),
						rk_fit_gtr300_mid->at(i)};


			resx = { 
						
#ifndef NoExist_SSD
rk_res_ssd_x->at(i),
#else 
0,
#endif
	
						rk_res_gtr100_x->at(i),
						rk_res_gtr200_x->at(i),
						rk_res_gtr300_x->at(i)};
			resy = { 0,
						rk_res_gtr100_y->at(i),
						rk_res_gtr200_y->at(i),
						rk_res_gtr300_y->at(i)};
			fitlxs   = { 						
#ifndef NoExist_SSD
rk_fit_ssd_x  ->at(i),
#else 
0,
#endif
			   		 rk_fit_gtr100_x->at(i),
						 rk_fit_gtr200_x->at(i),
						 rk_fit_gtr300_x->at(i)};
			fitlys   = { 0,
			   		 rk_fit_gtr100_y->at(i),
						 rk_fit_gtr200_y->at(i),
						 rk_fit_gtr300_y->at(i)};
			tans = { 
#ifndef NoExist_SSD

rk_fit_ssd_mom_x->at(i)/rk_fit_ssd_mom_z->at(i),
#else 
0,
#endif
						rk_fit_gtr100_mom_x->at(i)/rk_fit_gtr100_mom_z->at(i),
						rk_fit_gtr200_mom_x->at(i)/rk_fit_gtr200_mom_z->at(i),
						rk_fit_gtr300_mom_x->at(i)/rk_fit_gtr300_mom_z->at(i)};
         std::cout << "xt4  " << rk_hit_gtr100_xt4->at(i) << std::endl;
			xt4s = { 0, 
						rk_hit_gtr100_xt4->at(i),
						rk_hit_gtr200_xt4->at(i),
						rk_hit_gtr300_xt4->at(i)};
			
			double tgt_x = rk_fit_init_pos_gx->at(i);
			double tgt_y = rk_fit_init_pos_gy->at(i);
			double tgt_z = rk_fit_init_pos_gz->at(i);
			double tdiff100 = rk_hit_gtr100_xt->at(i) - rk_hit_gtr100_yt->at(i);
			double tdiff200 = rk_hit_gtr200_xt->at(i) - rk_hit_gtr200_yt->at(i);
			double tdiff300 = rk_hit_gtr300_xt->at(i) - rk_hit_gtr300_yt->at(i);
			h_chi2->Fill(chi2);
			h_chi2_mod[mid-100]->Fill(chi2);
			h_tgt_pos_mod_raw[mid-100]->Fill(rk_fit_init_pos_gx->at(i), rk_fit_init_pos_gz->at(i));
			h_tgt_pos->Fill(rk_fit_init_pos_gx->at(i), rk_fit_init_pos_gz->at(i));
			h_tgt_proj_z_raw[mid-100]->Fill(rk_fit_init_pos_gz->at(i));
			bool lg_flag = true;//run0c wire
			double smallest_lgt = 1000;
//			for(int j=0; j < rk_proj_lg_t->size(); j++) {
//				for( auto lgt : rk_proj_lg_t->at(j)){
//					h_lg_t_mod[mid-100]->Fill(lgt);
//					if(lgt > 0 ){ 
//					lg_flag = true;
//					if(smallest_lgt > lgt) smallest_lgt = lgt;
//					}
//				}
//			}

			double t0diff = smallest_lgt - 88;//run0d
//			double t0diff =  ssd_t;
			
// --- cut conditions --- //
			
			if(chi2 > chi2_th[mid-100]) continue; //chi2_cut
			h_tgt_proj_z_chi2cut[mid-100]->Fill(rk_fit_init_pos_gz->at(i));
			if(fabs(tgt_y + 1) > tgty_cut) continue;
//			if(xt4s[l] < timing_cut) continue;
//			if(resx < res_min[mid-100]) continue;
//			if(resx > res_max[mid-100]) continue;
			if(lg_flag) {
				int tgtid;
				if(tgt_z < 0) tgtid = 0;//up
				if(tgt_z > 0) tgtid = 1;//down
				for(int l=0; l < 4; l++){
					
					int ith_div = (fitlxs[l] + sideLen[l]/2 ) / (sideLen[l]/ n_div);	
					
					h_fitlx[tgtid][mids[l]-100][l]->Fill(fitlxs[l]);
					h_res_x[tgtid][mids[l]-100][l]->Fill(resx[l]);
					h_res_y[tgtid][mids[l]-100][l]->Fill(resy[l]);
					h_cor_res_fitlx[tgtid][mids[l]-100][l]->Fill(fitlxs[l], resx[l]);	
					h_cor_res_fitly[tgtid][mids[l]-100][l]->Fill(fitlys[l], resx[l]);	
					h_cor_res_timing[tgtid][mids[l]-100][l]->Fill(xt4s[l], resx[l]);	//timing
					h_tan_theta[tgtid][mids[l]-100][l]     ->Fill(tans[l]);
					h_cor_dz_time[tgtid][mids[l]-100][l][ith_div]   ->Fill(xt4s[l], resx[l]/tans[l]);	
					h_cor_dz_time_t0cor[tgtid][mid-100][l][ith_div] ->Fill(xt4s[l] - t0diff, resx[l]/tans[l]);//plus or minus?
					h_slopevel[tgtid][mid-100][l][ith_div]->Fill((xt4s[l] - 250) * tans[l], resx[l] );
				}
				h_tgt_proj_x[mid-100]->Fill(rk_fit_init_pos_gx->at(i));
				h_tgt_proj_y[mid-100]->Fill(rk_fit_init_pos_gy->at(i));
				h_trackmap[tgtid][mid-100]->Fill(fitlxs[1], fitlys[1]);
	//			if(fabs(rk_fit_init_pos_gx->at(i) + 1) > 4 ) continue;
	//			if(fabs(tgt_y+ 1.5) >1.5 ) continue;
	//			if(fabs(tdiff100-5) > 30) continue;
	//			if(fabs(tdiff200-5) > 30) continue;
	//			if(fabs(tdiff300-5) > 30) continue;
	//			if(fabs(tan) > 0.08){
	
				h_tgt_pos_mod_cut[mid-100]->Fill(rk_fit_init_pos_gx->at(i), rk_fit_init_pos_gz->at(i));
				h_tgt_proj_z_cut[mid-100]->Fill(rk_fit_init_pos_gz->at(i));
	//			std::cout << "t0fiff " << t0diff << std::endl;
				h_t0diff->Fill(t0diff);
//			}
		}
		}
	}

	TCanvas *c0 = new TCanvas();
	c0->SaveAs(pdf_name + "[", "pdf");
	gStyle->SetOptStat(1111111);
	gStyle->SetOptFit(0111);

	TCanvas *c00 = new TCanvas();
	c00->Divide(2,2);
	c00->cd(1);
	h_n_runid->Draw();
	c00->cd(2);
	h_n_eventid->Draw();
	c00->cd(3);
	h_n_spillid->Draw();
	c00->SaveAs(pdf_name, "pdf");

//module 106 focus
	int fixm = 106;
	TCanvas *c1 = new TCanvas();
	c1->Divide(4,2);
	for(int l=0; l < 4; l++){
		c1->cd(l+1);
		h_res_x[0][6][l]->Draw();
		c1->cd(5+l);
		h_res_x[1][6][l]->Draw();
	}
	c1->SaveAs(pdf_name, "pdf");

	TCanvas *c200 = new TCanvas();
	c200->Divide(4,2);
	for(int l=0; l < 4; l++){
		c200->cd(l+1);
		h_fitlx[0][6][l]->Draw();
		c200->cd(5+l);
		h_fitlx[1][6][l]->Draw();
	}
	c200->SaveAs(pdf_name, "pdf");




   TCanvas *c100 = new TCanvas();
	c100->Divide(2,1);      
   c100->cd(1); h_tgt_proj_z_raw[6]->Draw("colz"); c100->SaveAs(pdf_name, "pdf");
	

	 TCanvas *c310[2][10];
    TGraphErrors *gr[2][10];
    TGraphErrors *gr_mean[2][10];
    TH1D *h1[10];
    TF1 *f1[10];
	 int hmid = 106;
    c310[0][hmid-100] = new TCanvas();
    c310[1][hmid-100] = new TCanvas();
    c310[0][hmid-100]->Divide(5,5);
    c310[1][hmid-100]->Divide(5,5);
	 for(int t=0; t < 2; t++){
    int n = h_cor_res_fitlx[t][hmid-100][fixl]->GetNbinsX();
    double xmin = -2;
    double xmax =  2;
    std::cout << "nbins = " << n << std::endl;
    gr[t][hmid-100] = new TGraphErrors(n);
    gr_mean[t][hmid-100] = new TGraphErrors(n);
     for (int i = 1; i <= n; i++) {
       c310[t][hmid-100]->cd(i);
        h1[hmid-100] = h_cor_res_fitlx[t][hmid-100][fixl]->ProjectionY(Form("_py%d%d", hmid, i), i, i     );
 //    f1[hmid-100] = new TF1(Form("f1%d%d",hmid, i), "gaus");
//       f1[hmid-100] = new TF1(Form("f%d", hmid), "gaus(0) + [3]+[4]*x+[5]*x*x+[6]*x*x*x",      xmin, xmax);
       f1[hmid-100] = new TF1(Form("f%d", hmid), "gaus(0)",      xmin, xmax);
//       f1[hmid-100]->SetParameter(0, 500);   // constant
       f1[hmid-100]->SetParameter(1, 0);     // mean
//       f1[hmid-100]->SetParLimits(1, -2, 2); // mean
//       f1[hmid-100]->SetParameter(2, 0.3);
//       f1[hmid-100]->SetParLimits(2, 0.1, 1);
//       f1[hmid-100]->SetParameter(3, 0);
//       f1[hmid-100]->SetParameter(4, -1);
        h1[hmid-100]->Fit(f1[hmid-100], "", "", xmin, xmax);
	     double mean = f1[hmid-100]->GetParameter(1);
	     double mean_err = f1[hmid-100]->GetParError(1);
       double sigma = f1[hmid-100]->GetParameter(2);
        double sigma_err = f1[hmid-100]->GetParError(2);
       std::cout << "sigma = " << sigma << std::endl;
        gr[t][hmid-100]->SetPoint(i-1, -100 + 200/n * i + 200/n/2, sigma);
        gr[t][hmid-100]->SetPointError(i-1, 0, sigma_err);
        gr_mean[t][hmid-100]->SetPoint(i-1, -100+ 200/n * i + 200/n/2, mean);
        gr_mean[t][hmid-100]->SetPointError(i-1, 0, mean_err);
       h1[hmid-100]->Draw();
    }
          c310[t][hmid-100]->cd(24);
			
          gr[t][hmid-100]->Draw("AP");
          c310[t][hmid-100]->cd(25);
				gr_mean[t][hmid-100]->SetMaximum(1.0);
				gr_mean[t][hmid-100]->SetMinimum(-1.0);
				gr_mean[t][hmid-100]->SetLineStyle(0);
          gr_mean[t][hmid-100]->Draw("AP");
          c310[t][hmid-100]->SaveAs(pdf_name, "pdf");
		}//target loop


	 TCanvas *c311[2][10];
    TGraphErrors *gry[2][10];
    TGraphErrors *gry_mean[2][10];
    TH1D *h1y[10];
    TF1 *f1y[10];
    c311[0][hmid-100] = new TCanvas();
    c311[1][hmid-100] = new TCanvas();
    c311[0][hmid-100]->Divide(5,5);
    c311[1][hmid-100]->Divide(5,5);
	 for(int t=0; t < 2; t++){
    int n = h_cor_res_fitly[t][hmid-100][fixl]->GetNbinsX();
    double xmin = -2;
    double xmax =  2;
    std::cout << "nbins = " << n << std::endl;
    gry[t][hmid-100] = new TGraphErrors(n);
    gry_mean[t][hmid-100] = new TGraphErrors(n);
     for (int i = 1; i <= n; i++) {
       c311[t][hmid-100]->cd(i);
        h1y[hmid-100] = h_cor_res_fitly[t][hmid-100][fixl]->ProjectionY(Form("_pjy%d%d", hmid, i), i, i     );
     f1y[hmid-100] = new TF1(Form("f1y%d%d",hmid, i), "gaus");
//       f1y[hmid-100] = new TF1(Form("f%d", hmid), "gaus(0) + [3]+[4]*x+[5]*x*x+[6]*x*x*x",      xmin, xmax);
       f1y[hmid-100]->SetParameter(0, 500);   // constant
       f1y[hmid-100]->SetParameter(1, 0);     // mean
       f1y[hmid-100]->SetParLimits(1, -2, 2); // mean
       f1y[hmid-100]->SetParameter(2, 0.3);
       f1y[hmid-100]->SetParLimits(2, 0.1, 1);
       f1y[hmid-100]->SetParameter(3, 0);
       f1y[hmid-100]->SetParameter(4, -1);
        h1y[hmid-100]->Fit(f1y[hmid-100], "", "", xmin, xmax);
	     double mean = f1y[hmid-100]->GetParameter(1);
	     double mean_err = f1y[hmid-100]->GetParError(1);
       double sigma = f1y[hmid-100]->GetParameter(2);
        double sigma_err = f1y[hmid-100]->GetParError(2);
       std::cout << "sigma = " << sigma << std::endl;
        gry[t][hmid-100]->SetPoint(i-1, -100 + 200/n * i + 200/n/2, sigma);
        gry[t][hmid-100]->SetPointError(i-1, 0, sigma_err);
        gry_mean[t][hmid-100]->SetPoint(i-1, -100+ 200/n * i + 200/n/2, mean);
        gry_mean[t][hmid-100]->SetPointError(i-1, 0, mean_err);
       h1y[hmid-100]->Draw();
    }
          c311[t][hmid-100]->cd(24);
			
          gry[t][hmid-100]->Draw("AP");
          c311[t][hmid-100]->cd(25);
				gry_mean[t][hmid-100]->SetMaximum(1.0);
				gry_mean[t][hmid-100]->SetMinimum(-1.0);
				gry_mean[t][hmid-100]->SetLineStyle(0);
          gry_mean[t][hmid-100]->Draw("AP");
          c311[t][hmid-100]->SaveAs(pdf_name, "pdf");
		}//target loop


	TCanvas *c333 = new TCanvas();
	h_cor_res_timing[0][6][2]->Draw();
	c333->SaveAs(pdf_name, "pdf");

	 TCanvas *c31t[2][10];
    TGraphErrors *grt[2][10];
    TGraphErrors *grt_mean[2][10];
    TH1D *h1t[10];
    TF1 *f1t[10];
    c31t[0][hmid-100] = new TCanvas();
    c31t[1][hmid-100] = new TCanvas();
    c31t[0][hmid-100]->Divide(5,5);
    c31t[1][hmid-100]->Divide(5,5);
	 for(int t=0; t < 2; t++){
    int n = h_cor_res_timing[t][hmid-100][fixl]->GetNbinsX();
    double xmin = -2;
    double xmax =  2;
    std::cout << "nbins = " << n << std::endl;
    grt[t][hmid-100] = new TGraphErrors(n);
    grt_mean[t][hmid-100] = new TGraphErrors(n);
     for (int i = 1; i <= n; i++) {
       c31t[t][hmid-100]->cd(i);
        h1t[hmid-100] = h_cor_res_timing[t][hmid-100][fixl]->ProjectionY(Form("_pjt%d%d", hmid, i), i, i     );
     f1t[hmid-100] = new TF1(Form("f1t%d%d",hmid, i), "gaus");
//       f1t[hmid-100] = new TF1(Form("f%d", hmid), "gaus(0) + [3]+[4]*x+[5]*x*x+[6]*x*x*x",      xmin, xmax);
       f1t[hmid-100]->SetParameter(0, 500);   // constant
       f1t[hmid-100]->SetParameter(1, 0);     // mean
       f1t[hmid-100]->SetParLimits(1, -2, 2); // mean
       f1t[hmid-100]->SetParameter(2, 0.3);
       f1t[hmid-100]->SetParLimits(2, 0.1, 1);
       f1t[hmid-100]->SetParameter(3, 0);
       f1t[hmid-100]->SetParameter(4, -1);
        h1t[hmid-100]->Fit(f1t[hmid-100], "", "", xmin, xmax);
	     double mean = f1t[hmid-100]->GetParameter(1);
	     double mean_err = f1t[hmid-100]->GetParError(1);
       double sigma = f1t[hmid-100]->GetParameter(2);
        double sigma_err = f1t[hmid-100]->GetParError(2);
       std::cout << "sigma = " << sigma << std::endl;
        grt[t][hmid-100]->SetPoint(i-1,   600/n * i + 600/n/2, sigma);
        grt[t][hmid-100]->SetPointError(i-1, 0, sigma_err);
        grt_mean[t][hmid-100]->SetPoint(i-1, 600/n * i + 600/n/2, mean);
        grt_mean[t][hmid-100]->SetPointError(i-1, 0, mean_err);
       h1t[hmid-100]->Draw();
    }
          c31t[t][hmid-100]->cd(24);
			
          grt[t][hmid-100]->Draw("AP");
          c31t[t][hmid-100]->cd(25);
				grt_mean[t][hmid-100]->SetMaximum(1.0);
				grt_mean[t][hmid-100]->SetMinimum(-1.0);
			 grt_mean[t][hmid-100]->SetLineStyle(0);
          grt_mean[t][hmid-100]->Draw("AP");
          c31t[t][hmid-100]->SaveAs(pdf_name, "pdf");
		}//target loop


//

	double msize = 0.4;
	TCanvas *c312 = new TCanvas();
	c312->Divide(2,2);
	c312->cd(1);
	gr[0][6]->SetTitle("residual vs local x  ");
	gr[0][6]->GetYaxis()->SetTitle("residual sigma [mm]");
	gr[0][6]->GetXaxis()->SetRangeUser(-100, 100);
	gr[0][6]->GetXaxis()->SetTitle("local x [mm]");
	gr[0][6]->SetMarkerStyle(20);
	gr[1][6]->SetMarkerStyle(21);
	gr[0][6]->SetMarkerSize(msize);
	gr[1][6]->SetMarkerSize(msize);
	gr[1][6]->SetMarkerColor(kRed);
	gr[0][6]->Draw("AP");
	gr[1][6]->SetLineColor(kRed);
	gr[1][6]->Draw("P SAME");

	c312->cd(2);
	gry[0][6]->SetTitle("residual vs localy ");
	gry[0][6]->GetYaxis()->SetTitle("residual sigma [mm]");
	gry[0][6]->GetXaxis()->SetRangeUser(-100, 100);
	gry[0][6]->GetXaxis()->SetTitle("local y [mm]");
	gry[0][6]->SetMarkerStyle(20);
	gry[1][6]->SetMarkerStyle(21);
	gry[0][6]->SetMarkerSize(msize);
	gry[1][6]->SetMarkerSize(msize);
	gry[1][6]->SetMarkerColor(kRed);
	gry[0][6]->Draw("AP");
	gry[1][6]->SetLineColor(kRed);
	gry[1][6]->Draw("P SAME");

   c312->cd(3);
	grt[0][6]->SetTitle("residual vs timing ");
	grt[0][6]->GetYaxis()->SetTitle("residual sigma [mm]");
	grt[0][6]->GetXaxis()->SetRangeUser(0, 600);
	grt[0][6]->GetXaxis()->SetTitle("timing x [ns]");
	grt[0][6]->SetMarkerStyle(20);
	grt[1][6]->SetMarkerStyle(21);
	grt[0][6]->SetMarkerSize(msize);
	grt[1][6]->SetMarkerSize(msize);
	grt[1][6]->SetMarkerColor(kRed);
	grt[0][6]->Draw("AP");
	grt[1][6]->SetLineColor(kRed);
	grt[1][6]->Draw("P SAME");
	c312->SaveAs(pdf_name, "pdf");

	TCanvas *c313 = new TCanvas();
	c313->Divide(2,2);
	c313->cd(1);
	gr_mean[0][6]->SetTitle("residual vs local x mean ");
	gr_mean[0][6]->GetYaxis()->SetTitle("residual mean [mm]");
	gr_mean[0][6]->GetXaxis()->SetRangeUser(-100, 100);
	gr_mean[0][6]->GetXaxis()->SetTitle("local x [mm]");
	gr_mean[0][6]->SetMarkerStyle(20);
	gr_mean[1][6]->SetMarkerStyle(21);
	gr_mean[1][6]->SetMarkerColor(kRed);
	gr_mean[0][6]->SetMarkerSize(msize);
	gr_mean[1][6]->SetMarkerSize(msize);
	gr_mean[0][6]->Draw("AP");
	gr_mean[1][6]->SetLineColor(kRed);
	gr_mean[1][6]->Draw("P SAME");
	c313->cd(2);
	gry_mean[0][6]->SetTitle("residual vs localy mean ");
	gry_mean[0][6]->GetYaxis()->SetTitle("residual mean [mm]");
	gry_mean[0][6]->GetXaxis()->SetRangeUser(-100, 100);
	gry_mean[0][6]->GetXaxis()->SetTitle("local y [mm]");
	gry_mean[0][6]->SetMarkerStyle(20);
	gry_mean[1][6]->SetMarkerStyle(21);
	gry_mean[1][6]->SetMarkerColor(kRed);
	gry_mean[0][6]->SetMarkerSize(msize);
	gry_mean[1][6]->SetMarkerSize(msize);
	gry_mean[0][6]->Draw("AP");
	gry_mean[1][6]->SetLineColor(kRed);
	gry_mean[1][6]->Draw("P SAME");
	c313->cd(3);
	grt_mean[0][6]->SetTitle("residual mean vs timing ");
	grt_mean[0][6]->GetYaxis()->SetTitle("residual mean [mm]");
	grt_mean[0][6]->GetXaxis()->SetRangeUser(0, 600);
	grt_mean[0][6]->GetXaxis()->SetTitle("timing x [ns]");
	grt_mean[0][6]->SetMarkerStyle(20);
	grt_mean[1][6]->SetMarkerStyle(21);
	grt_mean[1][6]->SetMarkerColor(kRed);
	grt_mean[0][6]->SetMarkerSize(msize);
	grt_mean[1][6]->SetMarkerSize(msize);
	grt_mean[0][6]->Draw("AP");
	grt_mean[1][6]->SetLineColor(kRed);
	grt_mean[1][6]->Draw("P SAME");


	c313->SaveAs(pdf_name, "pdf");


	




	TCanvas *c01 = new TCanvas();
	h_chi2->Draw();
	c01->SaveAs(pdf_name, "pdf");


	TCanvas *c02 = new TCanvas();
	c02->Divide(4,2);
	for(int i =1; i < 9; i++){
      c02->cd(i);
      if(i < 5) {
         h_chi2_mod[i]->Draw("colz");
      }
      else {
         h_chi2_mod[i+1]->Draw("colz");
      }
   }
   c02->SaveAs(pdf_name, "pdf");

	TCanvas *clgt = new TCanvas();
	clgt->Divide(4,2);
	for(int i =1; i < 9; i++){
      clgt->cd(i);
      if(i < 5) {
         h_lg_t_mod[i]->Draw("colz");
      }
      else {
         h_lg_t_mod[i+1]->Draw("colz");
      }
   }
   clgt->SaveAs(pdf_name, "pdf");




	TCanvas *chit = new TCanvas();
	chit->Divide(8,2);
	for(int i =1; i < 9; i++){
      chit->cd(i);
      if(i < 5) {
         h_trackmap[0][i]->Draw("colz");
			chit->cd(i+8);
			h_trackmap[1][i]->Draw("colz");
      }
      else {
         h_trackmap[0][i+1]->Draw("colz");
			chit->cd(i+8);
         h_trackmap[1][i+1]->Draw("colz");
      }
   }
   chit->SaveAs(pdf_name, "pdf");

	


	TCanvas *c03 = new TCanvas();
	h_tgt_pos->Draw("colz");
	c03->SaveAs(pdf_name, "pdf");



	TCanvas *c03a = new TCanvas();
	c03a->Divide(4,2);
	for(int i =1; i < 9; i++){
      c03a->cd(i);
      if(i < 5) {
         h_tgt_pos_mod_raw[i]->Draw("colz");
      }
      else {
         h_tgt_pos_mod_raw[i+1]->Draw("colz");
      }
   }
   c03a->SaveAs(pdf_name, "pdf");

	TCanvas *c03b = new TCanvas();
	c03b->Divide(4,2);
	for(int i =1; i < 9; i++){
      c03b->cd(i);
      if(i < 5) {
         h_tgt_pos_mod_cut[i]->Draw("colz");
      }
      else {
         h_tgt_pos_mod_cut[i+1]->Draw("colz");
      }
   }
   c03b->SaveAs(pdf_name, "pdf");



	TCanvas *c04 = new TCanvas();
	c04->Divide(4,2);
	for(int i =1; i < 9; i++){
      c04->cd(i);
      if(i < 5) {
         h_tgt_proj_z_raw[i]->Draw("colz");
      }
      else {
         h_tgt_proj_z_raw[i+1]->Draw("colz");
      }
   }
   c04->SaveAs(pdf_name, "pdf");

	TCanvas *c04c = new TCanvas();
	c04c->Divide(4,2);
	for(int i =1; i < 9; i++){
      c04c->cd(i);
      if(i < 5) {
         h_tgt_proj_z_chi2cut[i]->Draw("colz");
      }
      else {
         h_tgt_proj_z_chi2cut[i+1]->Draw("colz");
      }
   }
   c04c->SaveAs(pdf_name, "pdf");


	TCanvas *c04a = new TCanvas();
	c04a->Divide(4,2);
	for(int i =1; i < 9; i++){
      c04a->cd(i);
      if(i < 5) {
         h_tgt_proj_z_cut[i]->Draw("colz");
      }
      else {
         h_tgt_proj_z_cut[i+1]->Draw("colz");
      }
   }
   c04a->SaveAs(pdf_name, "pdf");



	TCanvas *c04x = new TCanvas();
	c04x->Divide(4,2);
	for(int i =1; i < 9; i++){
      c04x->cd(i);
      if(i < 5) {
         h_tgt_proj_x[i]->Draw("colz");
      }
      else {
         h_tgt_proj_x[i+1]->Draw("colz");
      }
   }
   c04x->SaveAs(pdf_name, "pdf");

	TCanvas *c04y = new TCanvas();
	c04y->Divide(4,2);
	for(int i =1; i < 9; i++){
      c04y->cd(i);
      if(i < 5) {
         h_tgt_proj_y[i]->Draw("colz");
      }
      else {
         h_tgt_proj_y[i+1]->Draw("colz");
      }
   }
   c04y->SaveAs(pdf_name, "pdf");

//	TCanvas *c1 = new TCanvas();
//	c1->Divide(4,2);
//	for(int i =1; i < 9; i++){
//      c1->cd(i);
//      if(i < 5) {
//         h_res_x[i][fixl]->Draw("colz");
//      }
//      else {
//         h_res_x[i+1][fixl]->Draw("colz");
//      }
//   }
//   c1->SaveAs(pdf_name, "pdf");
//
//	TCanvas *c2 = new TCanvas();
//	c2->Divide(4,2);
//	for(int i =1; i < 9; i++){
//      c2->cd(i);
//      if(i < 5) {
//         h_res_y[i][fixl]->Draw("colz");
//      }
//      else {
//         h_res_y[i+1][fixl]->Draw("colz");
//      }
//   }
//   c2->SaveAs(pdf_name, "pdf");
//
//	TCanvas *c3 = new TCanvas();
//	c3->Divide(4,2);
//	for(int i =1; i < 9; i++){
//      c3->cd(i);
//      if(i < 5) {
//         h_tan_theta[t][i][fixl]->Draw("colz");
//      }
//      else {
//         h_tan_theta[i+1][fixl]->Draw("colz");
//      }
//   }
//   c3->SaveAs(pdf_name, "pdf");




//
//	TCanvas *c31[10];
//    TGraphErrors *gr[10];
//    TGraphErrors *gr_mean[10];
//    TH1D *h1[10];
//    TF1 *f1[10];
//    for(int hmid=101; hmid < 110; hmid++){
//       if(hmid == 105)continue;
//             c31[hmid-100] = new TCanvas();
//             c31[hmid-100]->Divide(4,3);
//             int n = h_cor_res_fitlx[0][hmid-100][fixl]->GetNbinsX();
//             double xmin = -2;
//             double xmax =  2;
//             std::cout << "nibs = " << n << std::endl;
//             gr[hmid-100] = new TGraphErrors(n);
//             gr_mean[hmid-100] = new TGraphErrors(n);
//              for (int i = 1; i <= n; i++) {
//                c31[hmid-100]->cd(i);
//                 h1[hmid-100] = h_cor_res_fitlx[0][hmid-100][fixl]->ProjectionY(Form("_py%d%d", hmid, i), i, i     );
// //             f1[hmid-100] = new TF1(Form("f1%d%d",hmid, i), "gaus");
//                f1[hmid-100] = new TF1(Form("f%d", hmid), "gaus(0) + [3]+[4]*x+[5]*x*x+[6]*x*x*x",      xmin, xmax);
//                f1[hmid-100]->SetParameter(0, 500);   // constant
//                f1[hmid-100]->SetParameter(1, 0);     // mean
//                f1[hmid-100]->SetParLimits(1, -2, 2); // mean
//                f1[hmid-100]->SetParameter(2, 0.3);
//                f1[hmid-100]->SetParLimits(2, 0.1, 1);
//                f1[hmid-100]->SetParameter(3, 0);
//                f1[hmid-100]->SetParameter(4, -1);
//                 h1[hmid-100]->Fit(f1[hmid-100], "", "", xmin, xmax);
//					  double mean = f1[hmid-100]->GetParameter(1);
//					  double mean_err = f1[hmid-100]->GetParError(1);
//                double sigma = f1[hmid-100]->GetParameter(2);
//                 double sigma_err = f1[hmid-100]->GetParError(2);
//                std::cout << "sigma = " << sigma << std::endl;
//                 gr[hmid-100]->SetPoint(i-1, i, sigma);
//                 gr[hmid-100]->SetPointError(i-1, 0, sigma_err);
//                 gr_mean[hmid-100]->SetPoint(i-1, i, mean);
//                 gr_mean[hmid-100]->SetPointError(i-1, 0, mean_err);
//                h1[hmid-100]->Draw();
//             }
//          c31[hmid-100]->cd(11);
//          gr[hmid-100]->Draw();
//          c31[hmid-100]->cd(12);
//				gr_mean[hmid-100]->SetMaximum(0.2);
//				gr_mean[hmid-100]->SetMinimum(-0.2);
//				gr_mean[hmid-100]->SetLineStyle(0);
//				
//          gr_mean[hmid-100]->Draw();
//          c31[hmid-100]->SaveAs(pdf_name, "pdf");
//    }
//

//   TCanvas *c6 = new TCanvas();
//   c6->Divide(4,2);
//   for(int i =1; i < 9; i++){
//      c6->cd(i);
//      if(i < 5) {
//         h_cor_dz_time[i][fixl]->Draw("colz");
//      }
//      else {
//         h_cor_dz_time[i+1][fixl]->Draw("colz");
//      }
//   }
//   c6->SaveAs(pdf_name, "pdf");
//
//    TCanvas *c16[2][10];
//    TGraphErrors *gr16[2][10];
//    TH1D *h16[2][10];
//    TF1  *f16[2][10];
//    TF1  *fla[2][10];
//    double xmin[10]  = {0, -7, -7, -7,     -6, 0, -6.5, -5.5, -7, -7};//mod100-109
//    double xmax[10]  = {0, 10, 10, 10,    5.5, 0,    2,  4.0,  8,  8};
//	 double flmin[10] = {0, 120, 120, 120, 120, 0, 120, 100, 180, 180};
//	 double flmax[10] = {0, 450, 450, 450, 450, 0, 530, 450, 550, 450};
//	 for(int t=0; t < 2; t++){
//    for(int hmid=101; hmid < 110; hmid++){
//       if(hmid != 106)continue;
//       c16[t][hmid-100] = new TCanvas();
//       int n = h_cor_dz_time[t][hmid-100][fixl]->GetNbinsX();
//       c16[t][hmid-100]->Divide(5,5);
//       std::cout << "nbins dz = " << n << std::endl;
//       gr16[t][hmid-100] = new TGraphErrors(n);
//		 gr16[t][hmid-100]->SetMaximum( 8.0);
//		 gr16[t][hmid-100]->SetMinimum(-8.0);
//        for (int i = 1; i <= n; i++) {
//          c16[t][hmid-100]->cd(i);
//          fla[t][hmid-100] = new TF1(Form("fla%d", hmid), "pol1", flmin[hmid-100], flmax[hmid-100]);
//          h16[t][hmid-100] = h_cor_dz_time[t][hmid-100][fixl]->ProjectionY(Form("_py%d%d", hmid, i), i, i);
//          //f16[hmid-100] = new TF1(Form("f16%d%d",hmid, i), "landau");
// //       f16[hmid-100] = new TF1("fitFunction", "gaus(0) + [3]*exp(-[4]*(x-[5])  )", xmin, xmax);
// //       f16[hmid-100] = new TF1("fitFunction", "gaus(0)+[3]+[4]*x+[5]*x*x+[6]*x*x*x", xmin,xmax);
//          //f16[hmid-100]->SetParNames("Constant", "Mean", "Sigma", "Slope", "X0");
////          f16[hmid-100] = new TF1("fitFunction", "gaus(0)+[3]+[4]*x+[5]*x*x", xmin[hmid-100],xmax[hmid-100]);
//          f16[t][hmid-100] = new TF1("fitFunction", "gaus(0)+[3]*x", xmin[hmid-100],xmax[hmid-100]);
// //       f16[hmid-100] = new TF1("fitFunction", "[0]*exp(-0.5*((x-[1])/[2])**2) + [3]*TMath::Erfc([4]*(x-[5]))", xmin, xmax);
// //       f16[hmid-100]->SetParNames("Constant", "Mean", "Sigma", "TailHeight", "TailSlope","TailX0");
//          f16[t][hmid-100]->SetParameter(0, 20); // constant
//          f16[t][hmid-100]->SetParameter(1, 0);     // mean
//          f16[t][hmid-100]->SetParameter(2, 10);    // sigma
//          f16[t][hmid-100]->SetParLimits(2, 1, 10);
//          f16[t][hmid-100]->SetParameter(3, 0);    
////          f16[hmid-100]->SetParLimits(3, -0.8, 0);
////          f16[hmid-100]->SetParameter(4, -1);    
////          f16[hmid-100]->SetParameter(4, -0.5);  
//           h16[t][hmid-100]->Fit(f16[t][hmid-100], "", "", xmin[hmid-100], xmax[hmid-100]);
//
//           double chi2 = f16[t][hmid-100]->GetChisquare();
//          double mean =  f16[t][hmid-100]->GetParameter(1);
//           double sigma_err = f16[t][hmid-100]->GetParError(2);
//          std::cout << "mod, fit chi2  = " << hmid  << ", "  << chi2 << std::endl;
//          if(chi2 < 5) continue;
//          if(sigma_err > 10) continue;
//           gr16[t][hmid-100]->SetPoint(i-1, i*(600/n), mean);
//           gr16[t][hmid-100]->SetPointError(i-1, 0, sigma_err);
//           gr16[t][hmid-100]->Fit(fla[t][hmid-100], "R");
//           h16[t][hmid-100]->Draw();
//       }
//          c16[t][hmid-100]->cd(6);
//          c16[t][hmid-100]->SaveAs(pdf_name, "pdf");
//		}
//    }
////
////
//    TCanvas *c17[2];
//	for(int t=0; t < 2; t++){
//	 c17[t]= new TCanvas();
//    c17[t]->Divide(4,2);
//    for(int hmid=101; hmid < 110; hmid++){
//       if(hmid!=106) continue;
//       if(hmid < 105) {c17[t]->cd(hmid-100);}
//		 else {c17[t]->cd(hmid-101);}
//       gr16[t][hmid-100]->SetTitle(Form("residual/tan_theta tgt%d  mod%d : timing ;  timing; residual/tan_theta", t, hmid) );
//       gr16[t][hmid-100]->Draw("AP");
//    }
//   c17[t]->SaveAs(pdf_name, "pdf");
//	}
//

//
//  TCanvas *c6b = new TCanvas();
//  c6b->Divide(2,2);
//  for(int tgt=0; tgt<2; tgt++){
//  for(int i =1; i < 9; i++){
//	  
//     c6b->cd(i);
//     if(i < 5) {
//        h_cor_dz_time_t0cor[tgt][i][fixl]->Draw("colz");
//     }
//     else {
//        h_cor_dz_time_t0cor[tgt][i+1][fixl]->Draw("colz");
//     }
//  }
//	}
//  c6b->SaveAs(pdf_name, "pdf");
//
//

   TCanvas *c16b[2][10][n_div];
   TGraphErrors *gr16b[2][10][n_div];
   TH1D *h16b[2][10][n_div];
   TF1 *f16b[2][10][n_div];
   TF1 *flab[2][10][n_div];
#ifdef CALIB
   double xminb[10]  = {0, -4, -7, -7,     -6, 0, -2, -5.5, -4, -4};//mod100-109
   double xmaxb[10]  = {0,  4, 10, 10,    5.5, 0,  2,  4.0,  5,  5};
#else 
   double xminb[10]  = {0, -4, -7, -7,     -6, 0, -4, -5.5, -4, -4};//mod100-109
   double xmaxb[10]  = {0,  4, 10, 10,    5.5, 0,   4,  4.0,  5,  5};
#endif
   double flminb[10] = {0, 120, 120, 120, 120, 0, 200, 120, 100, 180};
   double flmaxb[10] = {0, 450, 450, 450, 450, 0, 550, 450, 320, 450};
	for(int t=0; t < 2; t++){
		int hmid = 106;
		for(int d=0 ; d < n_div; d++){
      c16b[t][hmid-100][d] = new TCanvas();
      int n = h_cor_dz_time_t0cor[t][hmid-100][fixl][d]->GetNbinsX();
      c16b[t][hmid-100][d]->Divide(5,5);
      std::cout << "nbins dz = " << n << std::endl;
      gr16b[t][hmid-100][d] = new TGraphErrors(n);
   	gr16b[t][hmid-100][d]->SetMaximum( 8.0);
	   gr16b[t][hmid-100][d]->SetMinimum(-8.0);
       for (int i = 1; i <= n; i++) {
         c16b[t][hmid-100][d]->cd(i);
         flab[t][hmid-100][d] = new TF1(Form("fla%d%d", t, d), "pol1", flminb[hmid-100], flmaxb[hmid-100]);
         h16b[t][hmid-100][d] = h_cor_dz_time_t0cor[t][hmid-100][fixl][d]->ProjectionY(Form("_py%d%d%d", hmid, i), i, i);
//         f16b[t][hmid-100][d] = new TF1("fitFunction", "gaus(0)+[3]+[4]*x+[5]*x*x", xminb[hmid-100],xmaxb[hmid-100]);
//         f16b[t][hmid-100][d] = new TF1(Form("fitFunction%d%d", t, d), "gaus(0)+[3]*x*x", xminb[hmid-100],xmaxb[hmid-100]);
         f16b[t][hmid-100][d] = new TF1("fitFunction", "gaus(0)+[3]*x", xminb[hmid-100],xmaxb[hmid-100]);
//       f16b[hmid-100] = new TF1("fitFunction", "[0]*exp(-0.5*((x-[1])/[2])**2) + [3]*TMath::Erfc([4]*(x-[5]))", xmin, xmax);
//       f16b[hmid-100]->SetParNames("Constant", "Mean", "Sigma", "TailHeight", "TailSlope","TailX0");
         f16b[t][hmid-100][d]->SetParameter(0, 20); // constant
         f16b[t][hmid-100][d]->SetParameter(1, 0);     // mean
         f16b[t][hmid-100][d]->SetParameter(2, 3);    // sigma
//         f16b[t][hmid-100][d]->SetParameter(3, 0);    
//         f16b[t][hmid-100][d]->SetParameter(4, -1);    
//         f16b[t][hmid-100][d]->SetParameter(4, -0.5);  
         h16b[t][hmid-100][d]->Fit(f16b[t][hmid-100][d], "", "", xminb[hmid-100], xmaxb[hmid-100]);

          double chi2 = f16b[t][hmid-100][d]->GetChisquare();
         double mean = f16b[t][hmid-100][d]->GetParameter(1);
          double sigma_err = f16b[t][hmid-100][d]->GetParError(2);
         std::cout << "mod, fit chi2  = " << hmid  << ", "  << chi2 << std::endl;
         if(chi2 < 5) continue;
         if(sigma_err > 10) continue;
          gr16b[t][hmid-100][d]->SetPoint(i-1, i*(600/n), mean);
          gr16b[t][hmid-100][d]->SetPointError(i-1, 0, sigma_err);
          gr16b[t][hmid-100][d]->Fit(flab[t][hmid-100][d], "R");
          h16b[t][hmid-100][d]->Draw();
      }
         c16b[t][hmid-100][d]->cd(6);
         c16b[t][hmid-100][d]->SaveAs(pdf_name, "pdf");
   	}
	}


	TCanvas *c0d = new TCanvas();
	h_t0diff->Draw();
	c0d->SaveAs(pdf_name, "pdf");

    TCanvas *c17b[2];
		for(int t=0; t < 2; t++){
		 	c17b[t] = new TCanvas();
   	 	c17b[t]->Divide(5,4);
			for(int d=0; d < n_div; d++){
				c17b[t]->cd(d+1);
		      gr16b[t][6][d]->SetTitle(Form("residual/tan_theta tgt%d mod 106 : timing_lg ;  timing_lg; residual/tan_theta", t) );
	   	   gr16b[t][6][d]->Draw("AP");
				
			}
	 	c17b[t]->SaveAs(pdf_name, "pdf");
	  }


    TCanvas *c18[2];
	 TGraphErrors *tg18[2];
		for(int t=0; t < 2; t++){
			c18[t] = new TCanvas();
			tg18[t] = new TGraphErrors(n_div);
			for(int d=0; d < n_div; d++){
				double tilt = flab[t][6][d]->GetParameter(1);
				tg18[t]->SetPoint(d, d, tilt);
			}
//			tg18[t]->SetMarkerSize(msize);
			tg18[t]->Draw("AP");
	 c18[t]->SaveAs(pdf_name, "pdf");
	  }


    TCanvas *c19[2];
		for(int t=0; t < 2; t++){
			c19[t] = new TCanvas();
			c19[t]->Divide(4,5);
			for(int d=0; d < n_div; d++){
				c19[t]->cd(d+1);
				h_slopevel[t][6][fixl][d]->Draw("colz");
			}
	 	c19[t]->SaveAs(pdf_name, "pdf");
	  }




		



		c0->SaveAs(pdf_name + "]", "pdf");
}



//void E16DSTN_ReadStraightTree::HistFit(TCanvas *c, ){
//   TCanvas *c16b[2][10];
//   TGraphErrors *gr16b[2][10];
//   TH1D *h16b[2][10];
//   TF1 *f16b[2][10];
//   TF1 *flab[2][10];
//   double xminb[10]  = {0, -4, -7, -7,     -6, 0, -4, -5.5, -4, -4};//mod100-109
//   double xmaxb[10]  = {0,  4, 10, 10,    5.5, 0,   4,  4.0,  5,  5};
//   double flminb[10] = {0, 120, 120, 120, 120, 0, 120, 120, 100, 180};
//   double flmaxb[10] = {0, 450, 450, 450, 450, 0, 450, 450, 320, 450};
//	for(int t=0; t < 2; t++){
//   for(int hmid=101; hmid < 110; hmid++){
//      if(hmid != 106)continue;
//		for(int d=0 ; d < n_div; d++){
//      c16b[t][hmid-100] = new TCanvas();
//      int n = h_cor_dz_time_t0cor[t][hmid-100][fixl]->GetNbinsX();
//      c16b[t][hmid-100]->Divide(5,5);
//      std::cout << "nbins dz = " << n << std::endl;
//      gr16b[t][hmid-100] = new TGraphErrors(n);
//	 gr16b[t][hmid-100]->SetMaximum( 8.0);
//	 gr16b[t][hmid-100]->SetMinimum(-8.0);
//       for (int i = 1; i <= n; i++) {
//         c16b[t][hmid-100]->cd(i);
//         flab[t][hmid-100] = new TF1(Form("fla%d", hmid), "pol1", flminb[hmid-100], flmaxb[hmid-100]);
//         h16b[t][hmid-100] = h_cor_dz_time_t0cor[t][hmid-100][fixl]->ProjectionY(Form("_py%d%d", hmid, i), i, i);
//         f16b[t][hmid-100] = new TF1("fitFunction", "gaus(0)+[3]+[4]*x+[5]*x*x", xmin[hmid-100],xmax[hmid-100]);
//         f16b[t][hmid-100] = new TF1("fitFunction", "gaus(0)+[3]*x*x", xminb[hmid-100],xmaxb[hmid-100]);
//         f16b[t][hmid-100] = new TF1("fitFunction", "gaus(0)+[3]*x", xminb[hmid-100],xmaxb[hmid-100]);
////       f16b[hmid-100] = new TF1("fitFunction", "[0]*exp(-0.5*((x-[1])/[2])**2) + [3]*TMath::Erfc([4]*(x-[5]))", xmin, xmax);
////       f16b[hmid-100]->SetParNames("Constant", "Mean", "Sigma", "TailHeight", "TailSlope","TailX0");
//         f16b[t][hmid-100]->SetParameter(0, 20); // constant
//         f16b[t][hmid-100]->SetParameter(1, 0);     // mean
//         f16b[t][hmid-100]->SetParameter(2, 1);    // sigma
//         f16b[t][hmid-100]->SetParameter(3, 0);    
//          f16[t][hmid-100]->SetParameter(4, -1);    
//          f16[t][hmid-100]->SetParameter(4, -0.5);  
//          h16b[t][hmid-100]->Fit(f16b[t][hmid-100], "", "", xminb[hmid-100], xmaxb[hmid-100]);
//
//          double chi2 = f16b[t][hmid-100]->GetChisquare();
//         double mean = f16b[t][hmid-100]->GetParameter(1);
//          double sigma_err = f16b[t][hmid-100]->GetParError(2);
//         std::cout << "mod, fit chi2  = " << hmid  << ", "  << chi2 << std::endl;
//         if(chi2 < 5) continue;
//         if(sigma_err > 10) continue;
//          gr16b[t][hmid-100]->SetPoint(i-1, i*(600/n), mean);
//          gr16b[t][hmid-100]->SetPointError(i-1, 0, sigma_err);
//          gr16b[t][hmid-100]->Fit(flab[t][hmid-100], "R");
//          h16b[t][hmid-100]->Draw();
//      }
//         c16b[t][hmid-100]->cd(6);
//         c16b[t][hmid-100]->SaveAs(pdf_name, "pdf");
//   	}
//		}
//	}
//
//
//}
