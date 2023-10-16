#define E16DSTN_AfterTrackAna_cxx
#include "E16DSTN_AfterTrackAna.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

void E16DSTN_AfterTrackAna::DrawHist(TTree* tree, int print_cycle, int event_start, int event_end, TString pdf_name)
{
	int n_module = 10;
	TH1D* h_eemass_atbest;
   TH1D* h_chi2; 
   TH1D* h_distance; 

	TH1D *h_hbd_minres[2][n_module] ;
	TH1D *h_hbd_res_x[2][n_module];
	TH1D *h_hbd_res_y[2][n_module];
	TH1D *h_hbd_eprob[2][n_module];//e probability
	
	h_eemass_atbest = new TH1D("h_eemass_atbest", "h_eemass_atbest",100,  0.2, 2.0);
   h_chi2          = new TH1D("h_chi2", "h_chi2", 100, 0, 100);
   h_distance          = new TH1D("h_distance", "h_distance", 100, 0, 100);
  	for(int mid=0; mid < n_module;mid++){
		for(int c=0; c < 2; c++){//charge
		 h_hbd_minres[c][mid] = new TH1D(Form("h_hbd_minres_m%d_%d", mid,c), Form("h_hbd_minres_m%d_%d", mid, c), 100, -100, 100);
		 h_hbd_res_x[c][mid] = new TH1D(Form("h_hbd_res_x_m%d_%d", mid,c), Form("h_hbd_res_x_m%d_%d", mid, c), 100, -1, 1);
		 h_hbd_res_y[c][mid] = new TH1D(Form("h_hbd_res_y_m%d_%d", mid,c), Form("h_hbd_res_y_m%d_%d", mid, c), 100, -1, 1);
		 h_hbd_eprob[c][mid] = new TH1D(Form("h_hbd_eprob_m%d_%d", mid,c), Form("h_hbd_eprob_m%d_%d", mid, c), 100, 0, 1.1);
		}
	}
	int nevent = tree->GetEntries();
	for(int n=0; n < nevent; n++){
		if(n < event_start) continue;
		if(n > event_end ) break;
		if( n%print_cycle ==0 ){
			printf("N Analyzed = %d \n", n);
		}
		tree->GetEntry(n);
		for(int i=0; i < chi2->size(); i++){
			double p_chi2        = plus_chi2->at(i);
			double m_chi2        = minus_chi2->at(i);
			int    p_hbd_mid    = plus_hbd_mid->at(i);
			int    m_hbd_mid    = plus_hbd_mid->at(i);
//			double iphbd_min_res = proj_plus_hbd_min_res->at(i);
//			double imhbd_min_res = proj_minus_hbd_min_res->at(i);
//			double iphbd_res_x  = proj_plus_hbd_resx->at(i);
//			double imhbd_res_x  = proj_minus_hbd_resy->at(i);
//			double iphbd_res_y  = proj_plus_hbd_resx->at(i);
//			double imhbd_res_y  = proj_minus_hbd_resy->at(i);
			double idistance    = distance->at(i);
// proj_plus_n_hbds->at(i) == 1
			double p_eprob     = (*proj_plus_hbd_eprob)[i][0];
			double p_hbd_res   = proj_plus_hbd_min_res->at(i);
 			double m_eprob     = (*proj_minus_hbd_eprob)[i][0];
			double m_hbd_res   = proj_minus_hbd_min_res->at(i);
         double p_hbd_adc    = (*proj_plus_hbd_adc)[i][0];
         double m_hbd_adc    = (*proj_minus_hbd_adc)[i][0];
			
//				h_chi2[0]                   ->Fill(ichi2);
				h_distance               ->Fill(idistance);
    			h_hbd_minres[0][p_hbd_mid-100]->Fill(p_hbd_res);
    			h_hbd_minres[1][m_hbd_mid-100]->Fill(m_hbd_res);
				h_hbd_eprob[0][p_hbd_mid-100]->Fill(p_eprob);
				h_hbd_eprob[1][m_hbd_mid-100]->Fill(m_eprob);
//				h_hbd_minres[1][m_hbd_mid]->Fill(imhbd_min_res);
//				h_hbd_res_x[0][p_hbd_mid]->Fill(iphbd_res_x);
//				h_hbd_res_x[1][m_hbd_mid]->Fill(imhbd_res_y);
//				h_hbd_res_y[0][p_hbd_mid]->Fill(iphbd_res_x);
//				h_hbd_res_y[1][m_hbd_mid]->Fill(imhbd_res_y);
			if(p_chi2 > 5	 | m_chi2 > 5) continue;
			if(p_hbd_adc  < 11	 | m_hbd_adc < 11) continue;
				h_eemass_atbest->Fill(ee_mass_at_best_tgt->at(i));
		}
	} 
	TCanvas *c0 = new TCanvas();
   c0->SaveAs(pdf_name + "[", "pdf");
   gStyle->SetOptStat(1111111);
   gStyle->SetOptFit(0111);

   TCanvas *c01 = new TCanvas();
   h_eemass_atbest->Draw();
   c01->SaveAs(pdf_name, "pdf");

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
