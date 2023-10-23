#define E16DSTN_AfterTrackAna_cxx
#include "E16DSTN_AfterTrackAna.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

bool E16DSTN_AfterTrackAna::IsSameArm(int pmid, int mmid){
	if(pmid < 105 && mmid < 105) {
		return true;
	}
	else if (pmid > 105 && mmid > 105){
		return true;
	}
	else {
	return false;
	}

}

void E16DSTN_AfterTrackAna::DrawHist(TTree* tree, int print_cycle, int event_start, int event_end, TString pdf_name)
{
	int n_module = 10;
	TH1D* h_eemass_atbest;
   TH1D* h_chi2; 
   TH1D* h_chi2_pm[2]; 
   TH1D* h_distance; 
	TH2D *h_vertex_pos;

	TH1D *h_gtr_res_x[2][n_module][3];
	TH1D *h_hbd_minres[2][n_module] ;
	TH1D *h_hbd_adc[2][n_module] ;
	TH1D *h_hbd_res_x[2][n_module];
	TH1D *h_hbd_res_y[2][n_module];
	TH1D *h_hbd_eprob[2][n_module];//e probability
	
	h_eemass_atbest = new TH1D("h_eemass_atbest", "h_eemass_atbest",100,  0.2, 2.0);
	h_distance      = new TH1D("h_distance", "h_distance",100,  0, 200);
   h_chi2          = new TH1D("h_chi2", "h_chi2", 100, 0, 200);
	h_vertex_pos    = new TH2D("h_vertex_pos", "h_vertex_pos", 50, -150, 150, 50, -150, 150); 
	for(int c=0; c < 2; c++){//charge
		h_chi2_pm[c] = new TH1D(Form("chi2_pm%d", c), Form("chi2_pm%d", c), 100, 0, 100);
		
  		for(int mid=0; mid < n_module;mid++){
			h_hbd_minres[c][mid] = new TH1D(Form("h_hbd_minres_m%d_%d", mid,c), Form("h_hbd_minres_m%d_%d", mid, c), 100, -100, 100);
			h_hbd_adc[c][mid] = new TH1D(Form("h_hbd_adc_m%d_%d", mid,c), Form("h_hbd_adc_m%d_%d", mid, c), 100, -100, 100);
			h_hbd_res_x[c][mid] = new TH1D(Form("h_hbd_res_x_m%d_%d", mid,c), Form("h_hbd_res_x_m%d_%d", mid, c), 100, -1, 1);
			h_hbd_res_y[c][mid] = new TH1D(Form("h_hbd_res_y_m%d_%d", mid,c), Form("h_hbd_res_y_m%d_%d", mid, c), 100, -1, 1);
		 	h_hbd_eprob[c][mid] = new TH1D(Form("h_hbd_eprob_m%d_%d", mid,c), Form("h_hbd_eprob_m%d_%d", mid, c), 100, 0, 1.1);
			for(int lid=0; lid < 3; lid++){
				h_gtr_res_x[c][mid][lid] = new TH1D(Form("g_gtr_res_lx_c%d_m%d_l%d", c, mid, lid), Form("g_gtr_res_lx_c%d_m%d_l%d", c, mid, lid), 100, -5,5);
			}
		}
	}
	int nevent = tree->GetEntries();
	std::cout <<  "nevent = " << nevent << std::endl;
	for(int n=0; n < nevent; n++){
		if(n < event_start) continue;
		if(n > event_end ) break;
		if( n%print_cycle ==0 ){
			printf("N Analyzed = %d \n", n);
		}
		tree->GetEntry(n);
			double max_p_hbd_adc = 0;//plus
			double max_m_hbd_adc = 0;//minus
		for(int i=0; i < n_pairs; i++){
			double p_chi2        = plus_chi2->at(i);
			double m_chi2        = minus_chi2->at(i);
			int    p_hbd_mid    = plus_hbd_mid->at(i);
			int    m_hbd_mid    = plus_hbd_mid->at(i);
			int p_100_mid    = plus_gtr100_mid->at(i);
			int m_100_mid    = minus_gtr100_mid->at(i);
			int p_gtrmid[3] = {plus_gtr100_mid->at(i),plus_gtr200_mid->at(i), plus_gtr300_mid->at(i) };
			int  m_gtrmid[3] = {minus_gtr100_mid->at(i),minus_gtr200_mid->at(i), minus_gtr300_mid->at(i) };
			double p_gtrres[3] = {res_plus_gtr100_lx->at(i),res_plus_gtr200_lx->at(i), res_plus_gtr300_lx->at(i) };
			double m_gtrres[3] = {res_minus_gtr100_lx->at(i),res_minus_gtr200_lx->at(i), res_minus_gtr300_lx->at(i) };
			if(IsSameArm(p_100_mid, m_100_mid)) continue;
			
//			double iphbd_min_res = proj_plus_hbd_min_res->at(i);
//			double imhbd_min_res = proj_minus_hbd_min_res->at(i);
//			double iphbd_res_x  = proj_plus_hbd_resx->at(i);
//			double imhbd_res_x  = proj_minus_hbd_resy->at(i);
//			double iphbd_res_y  = proj_plus_hbd_resx->at(i);
//			double imhbd_res_y  = proj_minus_hbd_resy->at(i);
// proj_plus_n_hbds->at(i) == 1
			if((*proj_plus_hbd_adc)[i].size() > 0  ) {
			for(int j =0  ; j < (*proj_plus_hbd_adc)[i].size();j++){
//				if((*proj_plus_hbd_adc)[j].size() < 1) continue;
//			std::cout << "size i  " << (*proj_plus_n_hbds[i])->size() << std::endl;
//			std::cout << "eprob " << (*proj_plus_hbd_adc)[i][0] << std::endl;
//			double p_eprob     = (*proj_plus_hbd_eprob)[i][0];
//			double p_hbd_res   = proj_plus_hbd_min_res->at(i);
         if((*proj_plus_hbd_adc)[i][j]  > max_p_hbd_adc ) { 
					max_p_hbd_adc    = (*proj_plus_hbd_adc)[i][j];
				}
			}
			}
			if((*proj_minus_hbd_adc)[i].size() > 0 ) {
			for(int j =0  ; j < (*proj_minus_hbd_adc)[i].size();j++){
//				if((*proj_plus_hbd_adc)[j].size() < 1) continue;
//			std::cout << "size i  " << (*proj_plus_n_hbds[i])->size() << std::endl;
//			std::cout << "eprob " << (*proj_plus_hbd_adc)[i][0] << std::endl;
//			double p_eprob     = (*proj_plus_hbd_eprob)[i][0];
//			double p_hbd_res   = proj_plus_hbd_min_res->at(i);
// 			double m_eprob     = (*proj_minus_hbd_eprob)[i][0];
//			double m_hbd_res   = proj_minus_hbd_min_res->at(i);
         if((*proj_minus_hbd_adc)[i][j]  > max_m_hbd_adc ) { 
					max_m_hbd_adc    = (*proj_minus_hbd_adc)[i][j];
				}
				}
			}
				if( (*proj_plus_lg_adc).size() > 0 ){//lg association
				if( (*proj_minus_lg_adc).size() > 0 ){//lg association
//				h_chi2[0]                   ->Fill(ichi2);
//				h_chi2[0]                   ->Fill(ichi2);
//				h_distance               ->Fill(idistance);
//    			h_hbd_minres[0][p_hbd_mid-100]->Fill(p_hbd_res);
//    			h_hbd_minres[1][m_hbd_mid-100]->Fill(m_hbd_res);
//				h_hbd_eprob[0][p_hbd_mid-100]->Fill(p_eprob);
//				h_hbd_eprob[1][m_hbd_mid-100]->Fill(m_eprob);
//				h_hbd_minres[1][m_hbd_mid]->Fill(imhbd_min_res);
//				h_hbd_res_x[0][p_hbd_mid]->Fill(iphbd_res_x);
//				h_hbd_res_x[1][m_hbd_mid]->Fill(imhbd_res_y);
//				h_hbd_res_y[0][p_hbd_mid]->Fill(iphbd_res_x);
//				h_hbd_res_y[1][m_hbd_mid]->Fill(imhbd_res_y);
//			if(p_chi2 > 5	 || m_chi2 > 5) continue;
//			if(chi2->at(i) > 100 ) continue;
//			std::cout << "p hbd adc " << p_hbd_adc << std::endl;
//			std::cout << "m hbd adc " << m_hbd_adc << std::endl;
			if(max_p_hbd_adc  < 9 || max_m_hbd_adc < 9) continue;
					for(int lid=0; lid<3; lid++){
						h_gtr_res_x[0][(p_gtrmid[lid])-100][lid]->Fill(p_gtrres[lid]);//plus
						h_gtr_res_x[1][(m_gtrmid[lid])-100][lid]->Fill(m_gtrres[lid]);//minus
					}
					h_chi2->Fill(chi2->at(i));
					if(chi2->at(i) > 100) continue;
					h_eemass_atbest->Fill(ee_mass_at_best_tgt->at(i));
					h_vertex_pos->Fill(vtx_x->at(i), vtx_z->at(i));
					h_distance->Fill(distance->at(i));
			}
}
		}
	} //nevent
	TCanvas *c0 = new TCanvas();
   c0->SaveAs(pdf_name + "[", "pdf");
   gStyle->SetOptStat(1111111);
   gStyle->SetOptFit(0111);

   TCanvas *c01 = new TCanvas();
   h_eemass_atbest->Draw();
   c01->SaveAs(pdf_name, "pdf");



   TCanvas *c010 = new TCanvas();
   h_chi2->Draw();
   c010->SaveAs(pdf_name, "pdf");

   TCanvas *c011 = new TCanvas();
   h_vertex_pos->Draw("colz");
   c011->SaveAs(pdf_name, "pdf");


   TCanvas *c012 = new TCanvas();
   h_distance->Draw();
   c012->SaveAs(pdf_name, "pdf");

	TCanvas *c20 = new TCanvas();
	c20->Divide(6,2);
	for(int m=2; m < 9; m++){
		c20->cd(m-1);
		h_gtr_res_x[0][m][0]->Draw();
		c20->cd(m+5);
		h_gtr_res_x[1][m][0]->Draw();
		
	}
   c20->SaveAs(pdf_name, "pdf");

	TCanvas *c21 = new TCanvas();
	c21->Divide(6,2);
	for(int m=2; m < 9; m++){
		c21->cd(m-1);
		h_gtr_res_x[0][m][1]->Draw();
		c21->cd(m+5);
		h_gtr_res_x[1][m][1]->Draw();
		
	}
   c21->SaveAs(pdf_name, "pdf");


	TCanvas *c22 = new TCanvas();
	c22->Divide(6,2);
	for(int m=2; m < 9; m++){
		c22->cd(m-1);
		h_gtr_res_x[0][m][2]->Draw();
		c22->cd(m+5);
		h_gtr_res_x[1][m][2]->Draw();
		
	}
   c22->SaveAs(pdf_name, "pdf");




	TCanvas *c02 = new TCanvas();
	c02->Divide(6,2);
	for(int m=2; m < 9; m++){
		c02->cd(m-1);
		h_hbd_eprob[0][m]->Draw();
		c02->cd(m+5);
		h_hbd_eprob[1][m]->Draw();
		
	}
   c02->SaveAs(pdf_name, "pdf");

	TCanvas *c03 = new TCanvas();
	c03->Divide(6,2);
	for(int m=2; m < 9; m++){
		c03->cd(m-1);
		h_hbd_minres[0][m]->Draw();
		c03->cd(m+5);
		h_hbd_minres[1][m]->Draw();
		
	}
   c03->SaveAs(pdf_name, "pdf");


	c0->SaveAs(pdf_name + "]", "pdf");
}
