#define E16DSTN_ReStraightV2_wire_cxx
#include "E16DSTN_ReStraightV2.hh"
//#include "E16ANA_StraightTrackParameter.hh"
#include "E16DSTN_ReStraightParameter.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <sstream>
#include <fstream>


//using namespace E16ANA_StraightTrackParameter;
using namespace E16ANA_StraightTrackConstant;
using namespace E16DSTN_ReStraightParameter;
using namespace std;


void E16DSTN_ReStraightV2::SetGeomTemp(int target_mid){
	geom_temp.clear();
	auto gp = static_cast<const E16ANA_PlanarSTSGeometry*>(geometry->STS(E16ANA_StraightTrackConstant::ModuleID2020To2013(target_mid)));
	geom_temp.push_back(new E16ANA_PlanarSTSGeometry(*gp));
	for(int l = 1; l < 4; l++){
	auto gp = static_cast<const E16ANA_PlanarGeometry*>(geometry->GTR(E16ANA_StraightTrackConstant::ModuleID2020To2013(target_mid), l-1));
	geom_temp.push_back(new E16ANA_PlanarGeometry(*gp));	
	}
	for(int l = 1; l < 4; l++){
		if(l == 1){
		geom_temp[l]->LocalTranslate(TVector3(gmove_pattern0.dx, gmove_pattern0.dy ,gmove_pattern0.dz));
		geom_temp[l]->LocalRotate(gmove_pattern0.radx, gmove_pattern0.rady ,gmove_pattern0.radz);
		}
		else if(l == 2){
		geom_temp[l]->LocalTranslate(TVector3(gmove_pattern1.dx, gmove_pattern1.dy ,gmove_pattern1.dz));
		geom_temp[l]->LocalRotate(gmove_pattern1.radx, gmove_pattern1.rady ,gmove_pattern1.radz);
		}
		else if(l == 3){
		geom_temp[l]->LocalTranslate(TVector3(gmove_pattern2.dx, gmove_pattern2.dy ,gmove_pattern2.dz));
		geom_temp[l]->LocalRotate(gmove_pattern2.radx, gmove_pattern2.rady ,gmove_pattern2.radz);
		}
	}
}

void E16DSTN_ReStraightV2::SetGeomMovePattern(const std::string& file, int pid){
	std::ifstream infile(file);
	std::string line;
	while(std::getline(infile, line)) {
		if(line.empty() || line[0] == '#' ){
			continue;
		}	
		std::istringstream iss(line);
		GeomMovePattern p;
		if (iss >> p.pattern_id >> p.gtrsize >> p.dx >> p.dy >> p.dz >> p.radx >> p.rady >> p.radz){
			if(p.pattern_id == pid && p.gtrsize == 0){
				std::cout << "gtrsize " << p.gtrsize <<", " << p.dx << std::endl;
				gmove_pattern0.pattern_id = p.pattern_id;
				gmove_pattern0.gtrsize     = p.gtrsize;
				gmove_pattern0.dx     = p.dx;
				gmove_pattern0.dy     = p.dy;
				gmove_pattern0.dz     = p.dz;
				gmove_pattern0.radx   = p.radx;
				gmove_pattern0.rady   = p.rady;
				gmove_pattern0.radz   = p.radz;
				std::cerr << "Pattern was successfully found " << std::endl;
			}
			if(p.pattern_id == pid && p.gtrsize == 1){
				std::cout << "gtrsize " << p.gtrsize <<", " << p.dx << std::endl;
				gmove_pattern1.pattern_id = p.pattern_id;
				gmove_pattern1.gtrsize     = p.gtrsize;
				gmove_pattern1.dx     = p.dx;
				gmove_pattern1.dy     = p.dy;
				gmove_pattern1.dz     = p.dz;
				gmove_pattern1.radx   = p.radx;
				gmove_pattern1.rady   = p.rady;
				gmove_pattern1.radz   = p.radz;
				std::cerr << "Pattern was successfully found " << std::endl;
			}
			if(p.pattern_id == pid && p.gtrsize == 2){
				std::cout << "gtrsize " << p.gtrsize <<", " << p.dx << std::endl;
				gmove_pattern2.pattern_id = p.pattern_id;
				gmove_pattern2.gtrsize     = p.gtrsize;
				gmove_pattern2.dx     = p.dx;
				gmove_pattern2.dy     = p.dy;
				gmove_pattern2.dz     = p.dz;
				gmove_pattern2.radx   = p.radx;
				gmove_pattern2.rady   = p.rady;
				gmove_pattern2.radz   = p.radz;
				std::cerr << "Pattern was successfully found " << std::endl;
				return; 
			}
		}
	}
	std::cerr << "Pattern not found " << std::endl;
	exit(0);
}



void E16DSTN_ReStraightV2::DrawHistWire(TTree* tree, int n_start, int n_end, int print_cycle, const int residual_layer,  TString pdf_name){	
	int nevent = tree->GetEntries();
	std::cout << "Total N events in the tree : " << nevent << std::endl;
	int cnt_lgres_fore[10] = {0};
	int cnt_lgres_bg[10]   = {0};
//conditions 
	double chi_sq_th  = 2000;
//initialize Histos
	InitHistos();
//Analysis part
	for(int n=0; n < nevent; n++){
		if(n > n_end) break;
		if (n % print_cycle == 0) {
			printf(" N Analyzed = %d \n", n);
		}
		if(n < n_start) continue;
		tree->GetEntry(n);
		int n_tracks = chi_square->size();//note that n tracks are judged with chi2 vec
      for(int i=0; i < n_tracks;i++){// track loop
	      double chi2 = chi_square->at(i);
			h_chi2->Fill(chi2);
			h_chi2_mod[rk_fit_gtr100_mid->at(i)-100]->Fill(chi2);
			if(chi2 > chi_sq_th) continue;
			if(fabs(rk_fit_gtr100_x->at(i)) > 50) continue;
			if(fabs(rk_fit_gtr200_x->at(i)) > 100) continue;
			if(fabs(rk_fit_gtr300_x->at(i)) > 150) continue;
			if(fabs(rk_fit_gtr100_y->at(i)) > 50) continue;
			if(fabs(rk_fit_gtr200_y->at(i)) > 100) continue;
			if(fabs(rk_fit_gtr300_y->at(i)) > 150) continue;

			FillVectors(i);//

// Fill Histos Basic
				double init_gx = rk_fit_init_pos_gx->at(i);
				double init_gy = rk_fit_init_pos_gy->at(i);
				double init_gz = rk_fit_init_pos_gz->at(i);
				h_init_pos->Fill(init_gx, init_gz);
				h_init_posz_mod[mids[1]-100]->Fill(init_gz);//mod decided by gtr100

// which wire
				
				int which_t = -1;
					  if(init_gx > 0 && init_gz < 0){
					which_t = 3;	
				}
				else if(init_gx > 0 && init_gz > 0){
					which_t = 2;
				}
				else if(init_gx < 0 && init_gz > 0){
					which_t = 1;
				}
				else if(init_gx < 0 && init_gz < 0){
					which_t = 0;
				}
				
				if(which_t == -1) {
					continue;
				}
				
				double tcent =  rk_hit_sts_t->at(i);
			
// Fill Histos detectors
			for(int lid = 0; lid < n_layers; lid++){
				if(lid == 0) continue;


				h_hitmap[mids[lid]-100][lid]           ->Fill( fitlxs[lid], fitlys[lid]);
				h_hitmap_x[mids[lid]-100][lid]         ->Fill( fitlxs[lid]);
				h_hitmap_y[mids[lid]-100][lid]         ->Fill( fitlys[lid]);
				h_cluster_t_diff[mids[lid]-100][lid]   ->Fill( xt4s[lid] - yts[lid]);
				h_cluster_t_diff_2d[mids[lid]-100][lid]->Fill( xt4s[lid] ,  yts[lid]);
				h_cluster_timing_x[mids[lid]-100][lid]->Fill(xt4s[lid]);
				h_cluster_timing_y[mids[lid]-100][lid]->Fill(yts[lid]);
				h_pre_res_x[mids[lid]-100][lid]->Fill(pre_resx[lid]);
//									h_cor_res_timing[mids[l]-100][l]->Fill(xt4s[l], resx[l]);	//timing
				h_tan_theta[mids[lid]-100][lid]     ->Fill(tans[lid]);
				h_cor_dz_time[mids[lid]-100][lid]   ->Fill(xt4s[lid], resx[lid]/tans[lid]);	
////									h_cor_dz_time_t0cor[mid-100][l] ->Fill(xt4s[l] - t0diff, resx[l]/tans[l]);//plus or minus?
////										h_slopevel[mid-100][l][ith_div]->Fill((xt4s[l] - 250) * tans[l], resx[l] ); 
				h_tot_end_fr[mids[lid]-100][lid]->Fill(xtotend[lid]);
				h_res_x_wire[which_t][mids[lid]-100][lid]->Fill(resx[lid]);
				h_res_y_wire[which_t][mids[lid]-100][lid]->Fill(resy[lid]);

				h_cor_resx_fitlx_wire[which_t][mids[lid]-100][lid]->Fill(fitlxs[lid], resx[lid]);	
				h_cor_resx_fitly_wire[which_t][mids[lid]-100][lid]->Fill(fitlys[lid], resx[lid]);	
				h_cor_resx_tan_wire[which_t][mids[lid]-100][lid]  ->Fill(tans[lid], resx[lid]);
				
				if(fabs(fitlys[lid])  < 40) {//center part Y direction
					h_cor_resx_fitlx_center_wire[which_t][mids[lid]-100][lid]->Fill(fitlxs[lid], resx[lid]);	
					h_cor_resx_tan_center_wire[which_t][mids[lid]-100][lid]  ->Fill(tans[lid], resx[lid]);
				}
				else if(fitlys[lid]  >  70) {//edge part Y direction
					h_cor_resx_fitlx_edge_top_wire[which_t][mids[lid]-100][lid]->Fill(fitlxs[lid], resx[lid]);	
					h_cor_resx_tan_edge_top_wire[which_t][mids[lid]-100][lid]  ->Fill(tans[lid], resx[lid]);
				}
				else if(fitlys[lid]  <  -70) {//edge part Y direction
					h_cor_resx_fitlx_edge_bot_wire[which_t][mids[lid]-100][lid]->Fill(fitlxs[lid], resx[lid]);	
					h_cor_resx_tan_edge_bot_wire[which_t][mids[lid]-100][lid]  ->Fill(tans[lid], resx[lid]);
				}
	
				if(fabs(fitlxs[lid])  < 40) {//center part X direction
					h_cor_resx_fitly_center_wire[which_t][mids[lid]-100][lid]->Fill(fitlys[lid], resx[lid]);	
				}
				else if(fitlxs[lid]   > 70 ) {//edge part X direction
					h_cor_resx_fitly_edge_top_wire[which_t][mids[lid]-100][lid]->Fill(fitlys[lid], resx[lid]);	
				}
				else if(fitlxs[lid]   < -70 ) {//edge part X direction
					h_cor_resx_fitly_edge_bot_wire[which_t][mids[lid]-100][lid]->Fill(fitlys[lid], resx[lid]);	
				}


				int area , area16, area25;
				double length = (double)100*lid/3;
				double length25 = (double)100*lid/5;
				double length16 = (double)100*lid/4;
				area = floor((fitlxs[lid] + lid*50)/length) +  floor((fitlys[lid] + lid * 50)/length ) * 3;
				area16 = floor((fitlxs[lid] + lid*50)/length16) +  floor((fitlys[lid] + lid * 50)/length16 ) * 4;
				area25 = floor((fitlxs[lid] + lid*50)/length25) +  floor((fitlys[lid] + lid * 50)/length25 ) * 5;
//				h_cluster_timing_x_area[mids[lid]-100][lid][area25]->Fill(xt4s[lid]);
				h_cluster_timing_x_area[mids[lid]-100][lid][area16]->Fill(xt4s[lid]);

				h_resx_div[which_t][mids[lid]-100][lid][area]->Fill(resx[lid]);	
				
				h_resx_dz_wire_x[which_t][mids[lid]-100][lid][area16]->Fill((xt4s[lid] - tcent), (double)resx[lid]/tans[lid]);
//				if(xt4s[lid] - tcent < 0){
//					cout << "timing " << xt4s[lid] - tcent << " length = " << length <<  std::endl;
//				}
				h_resx_dz_wire_x[4][mids[lid]-100][lid][area16]->Fill((xt4s[lid] - tcent) , (double)resx[lid]/tans[lid]);
	
				
				if(lid == 1){
					double t0 = ft0_gtr100->Eval(fitlxs[lid], fitlys[lid]);
					double xt = xt4s[lid] - rk_hit_sts_t->at(i);
					double dt = xt - t0;
					double dtx = (0.015 * dt) * tans[lid];
					h_dtx_tan->Fill(dtx, tans[lid]);
				}

				
				h_cor_resy_fitly_wire[which_t][mids[lid]-100][lid]->Fill(fitlys[lid], resy[lid]);	

//				std::cout << " fitlx  = " << fitlxs[lid] << std::endl;
//				std::cout << " fitly  = " << fitlys[lid] << std::endl;
//				std::cout << h_res_x_wire[which_t][mids[lid]-100][lid]->GetName() << std::endl;
//				std::cout << " xt4  = " << xt4s[lid] << std::endl;
//				std::cout << " tan  = " << tans[lid] << std::endl;
//				std::cout << " dz   = " << (xt4s[lid] - tcent) * tans[lid] << std::endl;

				//which div
//				int i_div   = (fitlxs[lid] + lid * 50)/ (lid * 50 / n_div);
//				int i_div_y = (fitlys[lid] + lid * 50)/ (lid * 50 / n_div);
//				
//				h_resx_dz_wire_xdiv[mids[lid]-100][lid][i_div]  ->Fill((xt4s[lid] - tcent) , (double)resx[lid]/tans[lid]);
//				h_resx_dz_wire_ydiv[mids[lid]-100][lid][i_div_y]->Fill((xt4s[lid] - tcent) , (double)resx[lid]/tans[lid]);
				
				}
			FillPulseInfos(i);
		}//track loop
	}
}




