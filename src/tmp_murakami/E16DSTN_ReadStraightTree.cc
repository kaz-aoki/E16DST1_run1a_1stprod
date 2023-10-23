
#include "E16DSTN_ReadStraightTree.hh"
#include "E16DSTN_StraightParameter.hh"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"

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
				if(removed_layer ==-1){
					if (kUseClusterDuplicationCut == kSSDAndGTRDuplicationCut){
						std::array<int, kNumTrackingDetectors> cids = {
						rk_hit_ssd_id->at(n),
						rk_hit_gtr100_xid->at(n), rk_hit_gtr100_yid->at(n), 
						rk_hit_gtr200_xid->at(n), rk_hit_gtr200_yid->at(n),
						rk_hit_gtr300_xid->at(n), rk_hit_gtr300_yid->at(n)};
						if(HasUsedCluster(cids)) {
							return false;
						}
						for (int i =0; i < kNumTrackingDetectors;i++){
							used_cluster_ids[i].emplace_back(cids[i]);
						}
					}
				}
				else {
					std::cout <<  "not developed yet " << std::endl;
				}
			}
			return true;
}

void E16DSTN_ReadStraightTree::SetTracks(){
	selected_ids.clear();
	for (int i=0; i < n_cands; i++){
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
	if(removed_layer !=-1 ){
//		ChooseSmallestResidual(nodup_id, selected_id);//if There is removed_layer
	}
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
	std::multimap<double, int> res_map;
	res_map.clear();
	std::vector<int> sorted_id;//will be sorted with residual
	sorted_id.clear();
	for(const int tid : selected_ids){
     	if(removed_layer == 1) res_map.insert({rk_res_gtr100_x->at(tid), tid});
     	if(removed_layer == 2) res_map.insert({rk_res_gtr200_x->at(tid), tid});
     	if(removed_layer == 3) res_map.insert({rk_res_gtr300_x->at(tid), tid});
   }	
   for (const auto& pair : res_map) {
   	sorted_id.push_back(pair.second);
	}
	int max  =  20000;
	if(removed_layer == 2) {
		bool x1_table[max] = {};
		std::fill(x1_table, x1_table + max, 0);
		for(const int tid : sorted_id){
			int x1id = rk_hit_gtr200_xid->at(tid);//gtr200 remove
			if(x1_table[x1id] == 0){
				x1_table[x1id] = 1; 
				selected_id.push_back(tid);
			}
			else {
				// nothing to do
			}	
		}
	}
}




void E16DSTN_ReadStraightTree::DrawHist(TTree* tree, int n_maxevent, int print_cycle, TString pdf_name){	
	const int n_module = 10;
	const int n_layer = 4;

	TH1D* h_chi2;
	TH1D* h_t0diff;
	TH1D* h_n_runid;
	TH1D* h_n_eventid;
	TH1D* h_n_spillid;

//	TH1D* rk_fit_init_mom_gx0




	TH1D* h_chi2_mod[n_module];
	TH1D* h_lg_t_mod[n_module];
	TH1D* h_tgt_proj_z_raw[n_module];
	TH1D* h_tgt_proj_z_cut[n_module];
	TH1D* h_tgt_proj_z_chi2cut[n_module];
	TH1D* h_tgt_proj_x[n_module];
	TH1D* h_tgt_proj_y[n_module];
	TH1D* h_res_x[n_module][n_layer];
	TH1D* h_res_y[n_module][n_layer];
	TH1D* h_tan_theta[n_module][n_layer];

	TH2D* h_tgt_pos;
	TH2D* h_tgt_pos_mod_raw[n_module];
	TH2D* h_tgt_pos_mod_cut[n_module];
	TH2D* h_cor_dz_time[n_module][n_layer];
	TH2D* h_cor_dz_time_lg[n_module][n_layer];
	TH2D* h_cor_res_lx[n_module][n_layer];
	
	int htdiv[10]   = {0,  6,  6,  6,  6, 0, 6,  7,  8,  6};
	int hdzdiv[10]  = {0, 60, 60, 60, 40, 0, 40, 36, 50, 60};

	h_n_runid = new TH1D("n of events of runid","n of events of runid", 15, 30331.5, 30346.5);
	h_n_eventid = new TH1D("n of events of event id","n of events of eventid", 10000, -0.5, 9999.5);
	h_n_spillid = new TH1D("n of events of spill id","n of events of spillid", 1000, -0.5, 999.5);
	h_chi2    = new TH1D(Form("h_chi2"), Form("h_chi2"), 100, 0, 200);	
	h_t0diff    = new TH1D(Form("h_t0diff"), Form("h_t0diff"), 100, -50,50);	
	h_tgt_pos = new TH2D(Form("h_tgt_pos"), Form("h_tgt_pos"), 50, 19.8, 20.2, 200, -60, 60);
	for(int m=0; m < n_module; m++){
		h_chi2_mod[m] = new TH1D(Form("h_chi2_mod%d", m+100), Form("h_chi2_mod%d", m+100), 100, 0, 200);
		h_lg_t_mod[m] = new TH1D(Form("h_lg_t_mod%d", m+100), Form("h_lg_t_mod%d", m+100), 100, 50, 150);
		h_tgt_pos_mod_raw[m] = new TH2D(Form("h_tgt_pos_mod_raw_%d", m+100), Form("h_tgt_pos_mod_raw_%d", m+100), 50, 19.8, 20.2, 60, -60, 60);
		h_tgt_pos_mod_cut[m] = new TH2D(Form("h_tgt_pos_mod_cut_%d", m+100), Form("h_tgt_pos_mod_cut_%d", m+100), 50, 19.8, 20.2, 60, -60, 60);
		h_tgt_proj_z_raw[m] = new TH1D(Form("h_tgt_proj_z_raw%d", m+100), Form("h_tgt_proj_z_raw%d", m+100), 100, -60, 60);
		h_tgt_proj_z_cut[m] = new TH1D(Form("h_tgt_proj_z_cut%d", m+100), Form("h_tgt_proj_z_cut%d", m+100), 100, -60, 60);
		h_tgt_proj_z_chi2cut[m] = new TH1D(Form("h_tgt_proj_z_chi2cut%d", m+100), Form("h_tgt_proj_z_chi2cut%d", m+100), 100, -45, 45);
		h_tgt_proj_x[m] = new TH1D(Form("h_tgt_proj_x%d", m+100), Form("h_tgt_proj_x%d", m+100), 100, 19.8, 20.2);
		h_tgt_proj_y[m] = new TH1D(Form("h_tgt_proj_y%d", m+100), Form("h_tgt_proj_y%d", m+100), 100, -5,5 );
		for(int l=0; l < n_layer; l++){// -- layer 
			h_res_x[m][l] = new TH1D(Form("h_res_x_m%d_l%d", m+100, l), Form("h_res_x_m%d_l%d", m+100, l), 100, -2, 2);
			h_res_y[m][l] = new TH1D(Form("h_res_y_m%d_l%d", m+100, l), Form("h_res_y_m%d_l%d", m+100, l), 100, -4, 4);
			h_tan_theta[m][l] = new TH1D(Form("h_tan_theta_%d_%d", m+100, l), Form("h_tan_theta%d_%d", m+100, l), 100, -0.5, 0.5);
			
			h_cor_dz_time[m][l] = new TH2D(Form("h_cor_dz_time_%d_%d", m+100, l), Form("h_cor_dz_time_%d%_d", m+100, l), htdiv[m], 0, 600, hdzdiv[m], -8, 8);
			h_cor_dz_time_lg[m][l] = new TH2D(Form("h_cor_dz_time_lg_%d_%d", m+100, l), Form("h_cor_dz_time_lg_%d%_d", m+100, l), htdiv[m], 0, 600, hdzdiv[m], -8, 8);
			h_cor_res_lx[m][l] = new TH2D(Form("h_cor_res_lx_%d_%d", m+100, l), Form("h_cor_res_lx_%d%_d", m+100, l), 10, -50*l , 50*l, 100, -2, 2);
		}
	}
	int nevent = tree->GetEntries();
	int fixl   = 2; //gtr200
								//    00, 01, 02, 03, 04, 05,    06
	double chi2_th[n_module] = {15, 15,15, 15, 15,   0,   15, 15, 15, 15};//mod100-109
	double res_min[n_module] = {0, -4, -4, -4, -4,   0,   -4, -4, -4, -4};//mod100-109
	double res_max[n_module] = {0,  4,  4,  4,  4,   0,    4,  4,  4,  4};//mod100-109




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
			if(rk_fit_gtr100_mid->at(i) < 105 || rk_fit_gtr100_mid->at(i) > 107) continue;
			double chi2  = chi_square->at(i);
			int    mid   = rk_fit_gtr200_mid->at(i);
			double resx  = rk_res_gtr200_x->at(i);
			double resy  = rk_res_gtr200_y->at(i);
			double lx    = rk_fit_gtr200_x->at(i);
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
			double t0diff = smallest_lgt - 88;
			if(chi2 > chi2_th[mid-100]) continue; //chi2_cut
//			if(fabs(tgt_z)  > 30) continue;
			h_tgt_proj_z_chi2cut[mid-100]->Fill(rk_fit_init_pos_gz->at(i));
//			if(resx < res_min[mid-100]) continue;
//			if(resx > res_max[mid-100]) continue;
			if(lg_flag) {
				h_res_x[mid-100][fixl]->Fill(resx);
				h_res_y[mid-100][fixl]->Fill(resy);
				h_tgt_proj_x[mid-100]->Fill(rk_fit_init_pos_gx->at(i));
				h_tgt_proj_y[mid-100]->Fill(rk_fit_init_pos_gy->at(i));
				double tan  = rk_fit_gtr200_mom_x->at(i)/rk_fit_gtr200_mom_z->at(i);// tan_theta 
				h_tan_theta[mid-100][fixl]->Fill(tan);
				h_cor_res_lx[mid-100][fixl]->Fill(lx, resx);	
	//			if(fabs(rk_fit_init_pos_gx->at(i) + 1) > 4 ) continue;
	//			if(fabs(tgt_y+ 1.5) >1.5 ) continue;
	//			if(fabs(tdiff100-5) > 30) continue;
	//			if(fabs(tdiff200-5) > 30) continue;
	//			if(fabs(tdiff300-5) > 30) continue;
	//			if(fabs(tan) > 0.08){
	
				h_tgt_pos_mod_cut[mid-100]->Fill(rk_fit_init_pos_gx->at(i), rk_fit_init_pos_gz->at(i));
				h_tgt_proj_z_cut[mid-100]->Fill(rk_fit_init_pos_gz->at(i));
				h_cor_dz_time[mid-100][fixl]->Fill(rk_hit_gtr200_xt->at(i), resx/tan);	
	//			std::cout << "t0fiff " << t0diff << std::endl;
				h_t0diff->Fill(t0diff);
				h_cor_dz_time_lg[mid-100][fixl]->Fill(rk_hit_gtr200_xt->at(i) - t0diff, resx/tan);//plus or minus?
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





	TCanvas *c1 = new TCanvas();
	c1->Divide(4,2);
	for(int i =1; i < 9; i++){
      c1->cd(i);
      if(i < 5) {
         h_res_x[i][fixl]->Draw("colz");
      }
      else {
         h_res_x[i+1][fixl]->Draw("colz");
      }
   }
   c1->SaveAs(pdf_name, "pdf");

	TCanvas *c2 = new TCanvas();
	c2->Divide(4,2);
	for(int i =1; i < 9; i++){
      c2->cd(i);
      if(i < 5) {
         h_res_y[i][fixl]->Draw("colz");
      }
      else {
         h_res_y[i+1][fixl]->Draw("colz");
      }
   }
   c2->SaveAs(pdf_name, "pdf");

	TCanvas *c3 = new TCanvas();
	c3->Divide(4,2);
	for(int i =1; i < 9; i++){
      c3->cd(i);
      if(i < 5) {
         h_tan_theta[i][fixl]->Draw("colz");
      }
      else {
         h_tan_theta[i+1][fixl]->Draw("colz");
      }
   }
   c3->SaveAs(pdf_name, "pdf");





	TCanvas *c31[10];
    TGraphErrors *gr[10];
    TGraphErrors *gr_mean[10];
    TH1D *h1[10];
    TF1 *f1[10];
    for(int hmid=101; hmid < 110; hmid++){
       if(hmid == 105)continue;
             c31[hmid-100] = new TCanvas();
             c31[hmid-100]->Divide(4,3);
             int n = h_cor_res_lx[hmid-100][fixl]->GetNbinsX();
             double xmin = -2;
             double xmax =  2;
             std::cout << "nibs = " << n << std::endl;
             gr[hmid-100] = new TGraphErrors(n);
             gr_mean[hmid-100] = new TGraphErrors(n);
              for (int i = 1; i <= n; i++) {
                c31[hmid-100]->cd(i);
                 h1[hmid-100] = h_cor_res_lx[hmid-100][fixl]->ProjectionY(Form("_py%d%d", hmid, i), i, i     );
 //             f1[hmid-100] = new TF1(Form("f1%d%d",hmid, i), "gaus");
                f1[hmid-100] = new TF1(Form("f%d", hmid), "gaus(0) + [3]+[4]*x+[5]*x*x+[6]*x*x*x",      xmin, xmax);
                f1[hmid-100]->SetParameter(0, 500);   // constant
                f1[hmid-100]->SetParameter(1, 0);     // mean
                f1[hmid-100]->SetParLimits(1, -2, 2); // mean
                f1[hmid-100]->SetParameter(2, 0.3);
                f1[hmid-100]->SetParLimits(2, 0.1, 1);
                f1[hmid-100]->SetParameter(3, 0);
                f1[hmid-100]->SetParameter(4, -1);
                 h1[hmid-100]->Fit(f1[hmid-100], "", "", xmin, xmax);
					  double mean = f1[hmid-100]->GetParameter(1);
					  double mean_err = f1[hmid-100]->GetParError(1);
                double sigma = f1[hmid-100]->GetParameter(2);
                 double sigma_err = f1[hmid-100]->GetParError(2);
                std::cout << "sigma = " << sigma << std::endl;
                 gr[hmid-100]->SetPoint(i-1, i, sigma);
                 gr[hmid-100]->SetPointError(i-1, 0, sigma_err);
                 gr_mean[hmid-100]->SetPoint(i-1, i, mean);
                 gr_mean[hmid-100]->SetPointError(i-1, 0, mean_err);
                h1[hmid-100]->Draw();
             }
          c31[hmid-100]->cd(11);
          gr[hmid-100]->Draw();
          c31[hmid-100]->cd(12);
				gr_mean[hmid-100]->SetMaximum(0.2);
				gr_mean[hmid-100]->SetMinimum(-0.2);
				gr_mean[hmid-100]->SetLineStyle(0);
				
          gr_mean[hmid-100]->Draw();
          c31[hmid-100]->SaveAs(pdf_name, "pdf");
    }


   TCanvas *c6 = new TCanvas();
   c6->Divide(4,2);
   for(int i =1; i < 9; i++){
      c6->cd(i);
      if(i < 5) {
         h_cor_dz_time[i][fixl]->Draw("colz");
      }
      else {
         h_cor_dz_time[i+1][fixl]->Draw("colz");
      }
   }
   c6->SaveAs(pdf_name, "pdf");
    TCanvas *c16[10];
    TGraphErrors *gr16[10];
    TH1D *h16[10];
    TF1 *f16[10];
    TF1 *fla[10];
    double xmin[10]  = {0, -7, -7, -7,     -6, 0, -6.5, -5.5, -7, -7};//mod100-109
    double xmax[10]  = {0, 10, 10, 10,    5.5, 0,    2,  4.0,  8,  8};
	 double flmin[10] = {0, 120, 120, 120, 120, 0, 120, 100, 180, 180};
	 double flmax[10] = {0, 450, 450, 450, 450, 0, 530, 450, 550, 450};
    for(int hmid=101; hmid < 110; hmid++){
       if(hmid == 105)continue;
       c16[hmid-100] = new TCanvas();
       int n = h_cor_dz_time[hmid-100][fixl]->GetNbinsX();
       c16[hmid-100]->Divide(2,6);
       std::cout << "nbins dz = " << n << std::endl;
       gr16[hmid-100] = new TGraphErrors(n);
		 gr16[hmid-100]->SetMaximum( 8.0);
		 gr16[hmid-100]->SetMinimum(-8.0);
        for (int i = 1; i <= n; i++) {
          c16[hmid-100]->cd(i);
          fla[hmid-100] = new TF1(Form("fla%d", hmid), "pol1", flmin[hmid-100], flmax[hmid-100]);
          h16[hmid-100] = h_cor_dz_time[hmid-100][fixl]->ProjectionY(Form("_py%d%d", hmid, i), i, i);
          //f16[hmid-100] = new TF1(Form("f16%d%d",hmid, i), "landau");
 //       f16[hmid-100] = new TF1("fitFunction", "gaus(0) + [3]*exp(-[4]*(x-[5])  )", xmin, xmax);
 //       f16[hmid-100] = new TF1("fitFunction", "gaus(0)+[3]+[4]*x+[5]*x*x+[6]*x*x*x", xmin,xmax);
          //f16[hmid-100]->SetParNames("Constant", "Mean", "Sigma", "Slope", "X0");
//          f16[hmid-100] = new TF1("fitFunction", "gaus(0)+[3]+[4]*x+[5]*x*x", xmin[hmid-100],xmax[hmid-100]);
          f16[hmid-100] = new TF1("fitFunction", "gaus(0)+[3]*x", xmin[hmid-100],xmax[hmid-100]);
 //       f16[hmid-100] = new TF1("fitFunction", "[0]*exp(-0.5*((x-[1])/[2])**2) + [3]*TMath::Erfc([4]*(x-[5]))", xmin, xmax);
 //       f16[hmid-100]->SetParNames("Constant", "Mean", "Sigma", "TailHeight", "TailSlope","TailX0");
          f16[hmid-100]->SetParameter(0, 20); // constant
          f16[hmid-100]->SetParameter(1, 0);     // mean
          f16[hmid-100]->SetParameter(2, 10);    // sigma
          f16[hmid-100]->SetParLimits(2, 1, 10);
          f16[hmid-100]->SetParameter(3, 0);    
//          f16[hmid-100]->SetParLimits(3, -0.8, 0);
//          f16[hmid-100]->SetParameter(4, -1);    
//          f16[hmid-100]->SetParameter(4, -0.5);  
           h16[hmid-100]->Fit(f16[hmid-100], "", "", xmin[hmid-100], xmax[hmid-100]);

           double chi2 = f16[hmid-100]->GetChisquare();
          double mean = f16[hmid-100]->GetParameter(1);
           double sigma_err = f16[hmid-100]->GetParError(2);
          std::cout << "mod, fit chi2  = " << hmid  << ", "  << chi2 << std::endl;
          if(chi2 < 5) continue;
          if(sigma_err > 10) continue;
           gr16[hmid-100]->SetPoint(i-1, i*(600/n), mean);
           gr16[hmid-100]->SetPointError(i-1, 0, sigma_err);
           gr16[hmid-100]->Fit(fla[hmid-100], "R");
           h16[hmid-100]->Draw();
       }
          c16[hmid-100]->cd(6);
          c16[hmid-100]->SaveAs(pdf_name, "pdf");
    }


    TCanvas *c17 = new TCanvas();
    c17->Divide(4,2);
    for(int hmid=101; hmid < 110; hmid++){
       if(hmid==105) continue;
       if(hmid < 105) {c17->cd(hmid-100);}
		 else {c17->cd(hmid-101);}
       gr16[hmid-100]->SetTitle(Form("residual/tan_theta mod%d : timing ;  timing; residual/tan_theta", hmid) );
       gr16[hmid-100]->Draw("AP");
    }
   c17->SaveAs(pdf_name, "pdf");




   TCanvas *c6b = new TCanvas();
   c6b->Divide(4,2);
   for(int i =1; i < 9; i++){
      c6b->cd(i);
      if(i < 5) {
         h_cor_dz_time_lg[i][fixl]->Draw("colz");
      }
      else {
         h_cor_dz_time_lg[i+1][fixl]->Draw("colz");
      }
   }
   c6b->SaveAs(pdf_name, "pdf");



    TCanvas *c16b[10];
    TGraphErrors *gr16b[10];
    TH1D *h16b[10];
    TF1 *f16b[10];
    TF1 *flab[10];
    double xminb[10]  = {0, -4, -7, -7,     -6, 0, -6.5, -5.5, -4, -4};//mod100-109
    double xmaxb[10]  = {0,  4, 10, 10,    5.5, 0,    2,  4.0,  5,  5};
	 double flminb[10] = {0, 120, 120, 120, 120, 0, 120, 120, 100, 180};
	 double flmaxb[10] = {0, 450, 450, 450, 450, 0, 450, 450, 320, 450};
    for(int hmid=101; hmid < 110; hmid++){
       if(hmid == 105)continue;
       c16b[hmid-100] = new TCanvas();
       int n = h_cor_dz_time_lg[hmid-100][fixl]->GetNbinsX();
       c16b[hmid-100]->Divide(2,6);
       std::cout << "nbins dz = " << n << std::endl;
       gr16b[hmid-100] = new TGraphErrors(n);
		 gr16b[hmid-100]->SetMaximum( 8.0);
		 gr16b[hmid-100]->SetMinimum(-8.0);
        for (int i = 1; i <= n; i++) {
          c16b[hmid-100]->cd(i);
          flab[hmid-100] = new TF1(Form("fla%d", hmid), "pol1", flminb[hmid-100], flmaxb[hmid-100]);
          h16b[hmid-100] = h_cor_dz_time_lg[hmid-100][fixl]->ProjectionY(Form("_py%d%d", hmid, i), i, i);
          //f16[hmid-100] = new TF1(Form("f16%d%d",hmid, i), "landau");
 //       f16[hmid-100] = new TF1("fitFunction", "gaus(0) + [3]*exp(-[4]*(x-[5])  )", xmin, xmax);
 //       f16[hmid-100] = new TF1("fitFunction", "gaus(0)+[3]+[4]*x+[5]*x*x+[6]*x*x*x", xmin,xmax);
          //f16[hmid-100]->SetParNames("Constant", "Mean", "Sigma", "Slope", "X0");
//          f16[hmid-100] = new TF1("fitFunction", "gaus(0)+[3]+[4]*x+[5]*x*x", xmin[hmid-100],xmax[hmid-100]);
//          f16b[hmid-100] = new TF1("fitFunction", "gaus(0)+[3]*x*x", xminb[hmid-100],xmaxb[hmid-100]);
          f16b[hmid-100] = new TF1("fitFunction", "gaus(0)+[3]*x", xminb[hmid-100],xmaxb[hmid-100]);
 //       f16b[hmid-100] = new TF1("fitFunction", "[0]*exp(-0.5*((x-[1])/[2])**2) + [3]*TMath::Erfc([4]*(x-[5]))", xmin, xmax);
 //       f16b[hmid-100]->SetParNames("Constant", "Mean", "Sigma", "TailHeight", "TailSlope","TailX0");
          f16b[hmid-100]->SetParameter(0, 20); // constant
          f16b[hmid-100]->SetParameter(1, 0);     // mean
          f16b[hmid-100]->SetParameter(2, 10);    // sigma
          f16b[hmid-100]->SetParameter(3, 0);    
          f16b[hmid-100]->SetParLimits(2, 1, 10); // 
//          f16b[hmid-100]->SetParLimits(3, -0.8, 0); // 
//          f16[hmid-100]->SetParameter(4, -1);    
//          f16[hmid-100]->SetParameter(4, -0.5);  
           h16b[hmid-100]->Fit(f16b[hmid-100], "", "", xminb[hmid-100], xmaxb[hmid-100]);

           double chi2 = f16b[hmid-100]->GetChisquare();
          double mean = f16b[hmid-100]->GetParameter(1);
           double sigma_err = f16b[hmid-100]->GetParError(2);
          std::cout << "mod, fit chi2  = " << hmid  << ", "  << chi2 << std::endl;
          if(chi2 < 5) continue;
          if(sigma_err > 10) continue;
           gr16b[hmid-100]->SetPoint(i-1, i*(600/n), mean);
           gr16b[hmid-100]->SetPointError(i-1, 0, sigma_err);
           gr16b[hmid-100]->Fit(flab[hmid-100], "R");
           h16b[hmid-100]->Draw();
       }
          c16b[hmid-100]->cd(6);
          c16b[hmid-100]->SaveAs(pdf_name, "pdf");
    }


	TCanvas *c0d = new TCanvas();
	h_t0diff->Draw();
	c0d->SaveAs(pdf_name, "pdf");





    TCanvas *c17b = new TCanvas();
    c17b->Divide(4,2);
    for(int hmid=101; hmid < 110; hmid++){
       if(hmid==105) continue;
       if(hmid < 105) {c17b->cd(hmid-100);}
		 else {c17b->cd(hmid-101);}
       gr16b[hmid-100]->SetTitle(Form("residual/tan_theta mod%d : timing_lg ;  timing_lg; residual/tan_theta", hmid) );
       gr16b[hmid-100]->Draw("AP");
    }
   c17b->SaveAs(pdf_name, "pdf");


	c0->SaveAs(pdf_name + "]", "pdf");
}
