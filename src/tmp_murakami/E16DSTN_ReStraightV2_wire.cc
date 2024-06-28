#define E16DSTN_ReStraightV2_wire_cxx
#include "E16DSTN_ReStraightV2.hh"
//#include "E16ANA_StraightTrackParameter.hh"
#include "E16DSTN_ReStraightParameter.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>


//using namespace E16ANA_StraightTrackParameter;
using namespace E16ANA_StraightTrackConstant;
using namespace E16DSTN_ReStraightParameter;



void E16DSTN_ReStraightV2::DrawHistWire(TTree* tree, int n_start, int n_end, int print_cycle, const int residual_layer,  TString pdf_name){	
	int nevent = tree->GetEntries();
	std::cout << "Total N events in the tree : " << nevent << std::endl;
	int cnt_lgres_fore[10] = {0};
	int cnt_lgres_bg[10]   = {0};
//conditions 
	double chi_sq_th  = 200;
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
			if(chi2 > chi_sq_th) continue;
			FillVectors(i);//

// ----- LG Asssociation --------- // 
				bool assoc_fore = false;
				bool assoc_bg = false;
				double plgx  = rk_fit_lg_b_x->at(i);
				double mplgy = rk_fit_lg_b_gy->at(i);
				if(fabs(mplgy) > 260){
					plgx = rk_fit_lg_c_x->at(i);
				}
				if(fabs(mplgy) < 150){
					plgx = rk_fit_lg_a_x->at(i);
				}
	// --- fore event --- //
				for(int k=0; k < n_lg_hits;k++){
					if(lg_hit_mid->at(k) == rk_fit_lg_b_mid->at(i)){
						int lg_mid = lg_hit_mid->at(k);
						if(lg_hit_adc->at(k) < 10) continue;
			//			if(fabs(lg_hit_x->at(k) - 310) < 1 && fabs(lg_hit_y->at(k) + 315) < 1) continue; 
						double dx     = lg_hit_x->at(k) - plgx;
						double dy     = lg_hit_gy->at(k) - mplgy;
						h_res_lg_x[lg_mid-100]->Fill(dx);
						h_res_lg_y[lg_mid-100]->Fill(dy);
						h_res_lg_2d[lg_mid-100]->Fill(dx,dy);
						if(fabs(dx) < 80 & fabs(dy) < 80 ){//association
							assoc_fore = true;
						}
					}
				}
	// ----- previous event ---- // 
				for(int k=0; k < pre_n_lg_hits;k++){
					if(pre_lg_hit_mid[k] == rk_fit_lg_b_mid->at(i)){
						int lg_mid = pre_lg_hit_mid[k];
						if(pre_lg_hit_adc[k] < 10) continue;
			//			if(fabs(pre_lg_hit_x[k] - 310) < 1 && fabs(pre_lg_hit_gy[k] + 315) < 1) continue; 
							double pre_dx = pre_lg_hit_x[k]  - plgx;
							double pre_dy = pre_lg_hit_gy[k] - mplgy;
							h_bak_res_lg_x[lg_mid-100]->Fill(pre_dx);
							h_bak_res_lg_y[lg_mid-100]->Fill(pre_dy);
							h_bak_res_lg_2d[lg_mid-100]->Fill(pre_dx, pre_dy);
						if(fabs(pre_dx) < 80 & fabs(pre_dy) < 80 ){//association
							assoc_bg = true;
						}
					}
				}
			//
				if(assoc_fore){
					cnt_lgres_fore[rk_fit_lg_b_mid->at(i)-100]++;
				}
				if(assoc_bg){
					cnt_lgres_bg[rk_fit_lg_b_mid->at(i) -100]++;
				}
// -- LG association finished ---- /// 

//			pre_mplgy[rk_fit_lg_b_mid->at(i)-100] = mplgy;
//			pre_plgx[rk_fit_lg_b_mid->at(i)-100] = plgx;
//			h_cluster_timing_chi2[m-100][l]->Fill(xt4s[l]);
////		h_cluster_timing_chi2_xdependence[m-100][l][nth_div]->Fill(xt4s[l]);
////		h_cluster_timing_chi2_ydependence[m-100][l][nth_divy]->Fill(xt4s[l]);
////		h_cluster_adc_xdependence[m-100][l][nth_div]->Fill(xadcs[l]);
////		h_cluster_adc_ydependence[m-100][l][nth_divy]->Fill(yadcs[l]);

// Fill Histos Basic
				double init_gx = rk_fit_init_pos_gx->at(i);
				double init_gy = rk_fit_init_pos_gy->at(i);
				double init_gz = rk_fit_init_pos_gz->at(i);
				h_init_pos->Fill(init_gx, init_gz);
				h_init_posz_mod[mids[1]-100]->Fill(init_gz);//mod decided by gtr100

// which wire
				int which_t;
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
				
			
// Fill Histos detectors
			for(int lid = 0; lid < n_layers; lid++){
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
				h_cor_res_fitlx_wire[which_t][mids[lid]-100][lid]->Fill(fitlxs[lid], resx[lid]);	
				h_cor_res_fitly_wire[which_t][mids[lid]-100][lid]->Fill(fitlys[lid], resy[lid]);	
				h_cor_resx_tan_wire[which_t][mids[lid]-100][lid] ->Fill(tans[lid], resx[lid]);
				}
			FillPulseInfos(i);
		}//track loop
	}
   fout->Write();


	const int g_mod = 6; // geometry calibration module 

	TCanvas *c0 = new TCanvas();
	c0->SaveAs(pdf_name + "[", "pdf");
	gStyle->SetOptStat(1111111);
	gStyle->SetOptFit(0111);

	TCanvas *c03 = new TCanvas();
	h_init_pos->Draw("colz");
	c03->SaveAs(pdf_name, "pdf");
	
	TCanvas *c04 = new TCanvas();
	h_init_posz_mod[g_mod]->Draw();
	c04->SaveAs(pdf_name, "pdf");


	TCanvas *c02 = new TCanvas();
   h_chi2_mod[g_mod]->Draw();
   c02->SaveAs(pdf_name, "pdf");


  TCanvas *c1[10];
  for(int m =1; m < 9; m++){ 
	 if(m != g_mod) continue;
    c1[m]= new TCanvas(); 
    c1[m]->Divide(4,4);
	for(int t=0; t < n_wires; t++){
      for(int l=0; l < n_layers; l++){
     		c1[m]->cd(1+l + t*4);
     if(m < 5) {
        h_res_x_wire[t][m][l]->Fit("gaus", "", "", -0.5, 0.5);
        h_res_x_wire[t][m][l]->Draw("colz");
     }
	 }
	}
    c1[m]->SaveAs(pdf_name, "pdf");
  }

  TCanvas *cresy[10];
  for(int m =1; m < 9; m++){ 
	 if(m != g_mod) continue;
    cresy[m]= new TCanvas(); 
    cresy[m]->Divide(2,2);
    for(int l=0; l < n_layers; l++){
     cresy[m]->cd(1+l);
     if(m < 5) {
        h_res_y[m][l]->Fit("gaus", "", "", -0.5, 0.5);
        h_res_y[m][l]->Draw("colz");

     }
     else {
        h_res_y[m+1][l]->Fit("gaus", "", "", -0.5, 0.5);
        h_res_y[m+1][l]->Draw("colz");
     }
	 }
    cresy[m]->SaveAs(pdf_name, "pdf");
  }



	TCanvas *c20[n_modules];
	for(int m=0; m < n_modules; m++){
		c20[m] = new TCanvas();
		c20[m]->Divide(4,4);
		for(int t=0; t < n_wires;t++){
			for(int l=0; l < n_layers;l++){
			c20[m]->cd(l+1 * t*4);
			h_cor_res_fitlx_wire[t][m][l]->Draw("colz");
			}
		}
		c20[m]->SaveAs(pdf_name, "pdf");
}




   TCanvas *c31[n_wires][n_modules][n_layers];
   TGraphErrors *gr[n_wires][n_modules][n_layers];
   TGraphErrors *gr_mean[n_wires][n_modules][n_layers];
   TH1D *h1[n_wires][n_modules][n_layers];
   TF1 *f1[n_wires][n_modules][n_layers];
   for(int hmid=101; hmid < 110; hmid++){
      if(hmid != g_mod + 100)continue;
		for(int t=0; t < n_wires; t++){	
				for(int l=0; l < n_layers;l++){
            c31[t][hmid-100][l] = new TCanvas();
            c31[t][hmid-100][l]->Divide(5,5);
            int n = h_cor_res_fitlx_wire[t][hmid-100][l]->GetNbinsX();
            double xmin = -1;
            double xmax =  1;
            std::cout << "nibs = " << n << std::endl;
            gr[t][hmid-100][l] = new TGraphErrors(n);
            gr[t][hmid-100][l]->SetTitle(Form("X Residual Sigma m%d l%d; local x [mm]; sigma", hmid, l ));
            gr_mean[t][hmid-100][l] = new TGraphErrors(n);
            gr_mean[t][hmid-100][l]->SetTitle(Form("X Residual Mean m%d l%d; local x [mm]; mean", hmid, l ));
             for (int i = 1; i <= n; i++) {
               c31[t][hmid-100][l]->cd(i);
               h1[t][hmid-100][l] = h_cor_res_fitlx_wire[t][hmid-100][l]->ProjectionY(Form("x_py__tgt%d_m%d_l%d_%d",t,  hmid, l, i), i, i     );
					if(h1[t][hmid-100][l]->GetEntries() == 0 ) continue;
//             f1[hmid-100] = new TF1(Form("f1%d%d",hmid, i), "gaus");
               f1[t][hmid-100][l] = new TF1(Form("f%d%d", hmid, l), "gaus(0) + [3]+[4]*x+[5]*x*x+[6]*x*x*x",      xmin, xmax);
               f1[t][hmid-100][l]->SetParameter(0, 500);   // constant
               f1[t][hmid-100][l]->SetParameter(1, 0);     // mean
               f1[t][hmid-100][l]->SetParLimits(1, -2, 2); // mean
               f1[t][hmid-100][l]->SetParameter(2, 0.3);
               f1[t][hmid-100][l]->SetParLimits(2, 0.1, 1);
               f1[t][hmid-100][l]->SetParameter(3, 0);
               f1[t][hmid-100][l]->SetParameter(4, -1);
               h1[t][hmid-100][l]->Fit(f1[t][hmid-100][l], "", "", xmin, xmax);
 				   double mean      = f1[t][hmid-100][l]->GetParameter(1);
 				   double mean_err  = f1[t][hmid-100][l]->GetParError(1);
               double sigma     = f1[t][hmid-100][l]->GetParameter(2);
               double sigma_err = f1[t][hmid-100][l]->GetParError(2);
               std::cout << "sigma = " << sigma << std::endl;
               gr[t][hmid-100][l]->SetPoint(i-1, i, sigma);
               gr[t][hmid-100][l]->SetPointError(i-1, 0, sigma_err);
					double lx = (-50*l) + i * (double)(l*100)/n;
					if(l ==0){
               	gr_mean[t][hmid-100][l]->SetPoint(i-1, i, mean);
					}
					else {
               	gr_mean[t][hmid-100][l]->SetPoint(i-1, lx, mean);
					}
               gr_mean[t][hmid-100][l]->SetPointError(i-1, 0, mean_err);
               h1[t][hmid-100][l]->Draw();
            }
         c31[t][hmid-100][l]->cd(23);
         gr[t][hmid-100][l]->SetMaximum(0.5);
         gr[t][hmid-100][l]->SetMinimum(-0.5);
         gr[t][hmid-100][l]->Draw("ap");
         c31[t][hmid-100][l]->cd(24);
 			gr_mean[t][hmid-100][l]->SetMaximum(1.0);
 			gr_mean[t][hmid-100][l]->SetMinimum(-1.0);
 			gr_mean[t][hmid-100][l]->SetLineStyle(0);
         gr_mean[t][hmid-100][l]->Draw("ap");
         c31[t][hmid-100][l]->SaveAs(pdf_name, "pdf");
			}
   	}
	}



   TCanvas *c31y[n_wires][n_modules][n_modules];
   TGraphErrors *gr_y[n_wires][n_modules][n_modules];
   TGraphErrors *gr_y_mean[n_wires][n_modules][n_modules];
   TH1D *h1y[n_wires][n_modules][n_modules];
   TF1 *f1y[n_wires][n_modules][n_modules];
   for(int hmid=101; hmid < 110; hmid++){
      if(hmid != g_mod + 100)continue;
		for(int t=0; t < n_wires; t++){
				for(int l=0; l < n_layers;l++){
            c31y[t][hmid-100][l] = new TCanvas();
            c31y[t][hmid-100][l]->Divide(5,5);
            int n = h_cor_res_fitly_wire[t][hmid-100][l]->GetNbinsX();
            double xmin = -1;
            double xmax =  1;
            std::cout << "nibs = " << n << std::endl;
            gr_y[t][hmid-100][l] = new TGraphErrors(n);
            gr_y[t][hmid-100][l]->SetTitle(Form("Y Residual Sigma m%d l%d; local y [mm]; sigma", hmid, l ));
            gr_y_mean[t][hmid-100][l] = new TGraphErrors(n);
            gr_y_mean[t][hmid-100][l]->SetTitle(Form("Y Residual Mean m%d l%d; local y [mm]; mean", hmid, l ));
             for (int i = 1; i <= n; i++) {
               c31y[t][hmid-100][l]->cd(i);
               h1y[t][hmid-100][l] = h_cor_res_fitly_wire[t][hmid-100][l]->ProjectionY(Form("y_py_tgt%d_m%d_l%d_%d", t, hmid, l, i), i, i     );
					if(h1y[t][hmid-100][l]->GetEntries() == 0 ) continue;
//             f1y[hmid-100] = new TF1(Form("f1y%d%d",hmid, i), "gaus");
               f1y[t][hmid-100][l] = new TF1(Form("f%d%d", hmid, l), "gaus(0) + [3]+[4]*x+[5]*x*x+[6]*x*x*x",      xmin, xmax);
               f1y[t][hmid-100][l]->SetParameter(0, 500);   // constant
               f1y[t][hmid-100][l]->SetParameter(1, 0);     // mean
               f1y[t][hmid-100][l]->SetParLimits(1, -2, 2); // mean
               f1y[t][hmid-100][l]->SetParameter(2, 0.3);
               f1y[t][hmid-100][l]->SetParLimits(2, 0.1, 1);
               f1y[t][hmid-100][l]->SetParameter(3, 0);
               f1y[t][hmid-100][l]->SetParameter(4, -1);
               h1y[t][hmid-100][l]->Fit(f1y[t][hmid-100][l], "", "", xmin, xmax);
 				   double mean      = f1y[t][hmid-100][l]->GetParameter(1);
 				   double mean_err  = f1y[t][hmid-100][l]->GetParError(1);
               double sigma     = f1y[t][hmid-100][l]->GetParameter(2);
               double sigma_err = f1y[t][hmid-100][l]->GetParError(2);
               std::cout << "sigma = " << sigma << std::endl;
               gr_y[t][hmid-100][l]->SetPoint(i-1, i, sigma);
               gr_y[t][hmid-100][l]->SetPointError(i-1, 0, sigma_err);
					double ly = (-50*l) + i * (double)(l*100)/n;
					if(l == 0){
               gr_y_mean[t][hmid-100][l]->SetPoint(i-1, i, mean);
					}else {
               gr_y_mean[t][hmid-100][l]->SetPoint(i-1, ly, mean);
					}
               gr_y_mean[t][hmid-100][l]->SetPointError(i-1, 0, mean_err);
               h1y[t][hmid-100][l]->Draw();
            }
         c31y[t][hmid-100][l]->cd(23);
         gr_y[t][hmid-100][l]->SetMaximum(0.5);
         gr_y[t][hmid-100][l]->SetMinimum(-0.5);
         gr_y[t][hmid-100][l]->Draw("ap");
         c31y[t][hmid-100][l]->cd(24);
 			gr_y_mean[t][hmid-100][l]->SetMaximum(1.0);
 			gr_y_mean[t][hmid-100][l]->SetMinimum(-1.0);
 			gr_y_mean[t][hmid-100][l]->SetLineStyle(0);
         gr_y_mean[t][hmid-100][l]->Draw("ap");
         c31y[t][hmid-100][l]->SaveAs(pdf_name, "pdf");
			}
		}
   }


	TCanvas *c31a[n_modules];
	for(int m =1; m < 9; m++){
		if(m!=g_mod) continue;
	   c31a[m]= new TCanvas();
		c31a[m]->Divide(4,4);
		for(int t=0; t < 4; t++){
		for(int l=0; l < 4; l++){
   		c31a[m]->cd(l+1 + t*4);
			gr[t][m][l]->Draw("ap");
      }
		}
   c31a[m]->SaveAs(pdf_name, "pdf");
	}


	TCanvas *c31a2[n_modules];
	TGraphErrors *tg_xmean;
	TLegend *legend = new TLegend(0.8, 0.68, 0.99, 0.78);
	for(int m =1; m < 9; m++){
		if(m!=g_mod) continue;
	   c31a2[m]= new TCanvas();
		c31a2[m]->Divide(2,2);
		for(int l=0; l < 4; l++){
			for(int t=0; t < n_wires; t++){
   		c31a2[m]->cd(l+1);
			if(t==0){
				gr_mean[t][m][l]->SetMarkerStyle(t + 20);
				gr_mean[t][m][l]->Draw("AP");
			}
			else {
				gr_mean[t][m][l]->SetMarkerStyle(t + 20);
				gr_mean[t][m][l]->SetMarkerColor(t + 1);
				gr_mean[t][m][l]->SetLineColor(t + 1);
				gr_mean[t][m][l]->Draw("P SAME");
			}
		legend->AddEntry( gr_mean[0][m][l], "up, minus", "p");
		legend->AddEntry( gr_mean[1][m][l], "down, minus", "p");
		legend->AddEntry( gr_mean[2][m][l], "down, plus", "p");
		legend->AddEntry( gr_mean[3][m][l], "up, plus", "p");
		legend->Draw();
			
      }
		
	}
   c31a2[m]->SaveAs(pdf_name, "pdf");
	}



	TCanvas *c31ya[n_modules];
	for(int m =1; m < 9; m++){
		if(m!=g_mod) continue;
	   c31ya[m]= new TCanvas();
		c31ya[m]->Divide(4,4);
		for(int t=0; t < 4; t++){
		for(int l=0; l < 4; l++){
   		c31ya[m]->cd(l+1 + t*4);
			gr_y[t][m][l]->Draw("ap");
      }
		}
   c31ya[m]->SaveAs(pdf_name, "pdf");
	}


	TCanvas *c31ya2[n_modules];
	TLegend *legend_y = new TLegend(0.8, 0.68, 0.99, 0.78);
	for(int m =1; m < 9; m++){
		if(m!=g_mod) continue;
	   c31ya2[m]= new TCanvas();
		c31ya2[m]->Divide(2,2);
		for(int l=0; l < 4; l++){
   		c31ya2[m]->cd(l+1);
			for(int t=0; t < n_wires; t++){
				if(t==0){
					gr_y_mean[t][m][l]->SetMarkerStyle(t + 20);
					gr_y_mean[t][m][l]->Draw("ap");
				}
				else  {
					gr_y_mean[t][m][l]->SetMarkerStyle(20 + t);
					gr_y_mean[t][m][l]->SetMarkerColor(t + 1);//red, green, blue
					gr_y_mean[t][m][l]->SetLineColor(t + 1);//red, green, blue
					gr_y_mean[t][m][l]->Draw("p same");
				}
			}
		legend_y->AddEntry( gr_mean[0][m][l], "up, minus", "p");
		legend_y->AddEntry( gr_mean[1][m][l], "down, minus", "p");
		legend_y->AddEntry( gr_mean[2][m][l], "down, plus", "p");
		legend_y->AddEntry( gr_mean[3][m][l], "up, plus", "p");
      }
   c31ya2[m]->SaveAs(pdf_name, "pdf");
	}


	TCanvas *ctheta[n_modules];
	for(int m=0; m < n_modules;m++){
		if(m!=g_mod) continue;
		ctheta[m] = new TCanvas();	
		ctheta[m]->Divide(2,2);	
		for(int l=0; l < n_layers; l++){
			ctheta[m]->cd(l+1);
			h_tan_theta[g_mod][l]->Draw();
		}
		ctheta[m]->SaveAs(pdf_name, "pdf");
	}

	TCanvas *ccortheta[n_modules];
	for(int t=0; t < n_wires; t++){
	for(int m=0; m < n_modules;m++){
		if(m != g_mod) continue;
		ccortheta[m] = new TCanvas();	
		for(int l=0; l < n_layers; l++){
			h_cor_resx_tan_wire[t][g_mod][l]->Draw("colz");
		}
		ccortheta[m]->SaveAs(pdf_name, "pdf");
	}
	}


   TCanvas *crtan[n_wires][n_modules][n_layers];
   TGraphErrors *res_sigma_tan[n_wires][n_modules][n_layers];
   TGraphErrors *res_mean_tan_mean[n_wires][n_modules][n_layers];
   TH1D *h1_restan[n_wires][n_modules][n_layers];
   TF1 *f1_restan[n_wires][n_modules][n_layers];
   for(int hmid=101; hmid < 110; hmid++){
      if(hmid != g_mod + 100)continue;
		for(int t=0; t < n_wires; t++){	
				for(int l=0; l < n_layers;l++){
            crtan[t][hmid-100][l] = new TCanvas();
            crtan[t][hmid-100][l]->Divide(5,5);
            int n = h_cor_resx_tan_wire[t][hmid-100][l]->GetNbinsX();
            double xmin = -1;
            double xmax =  1;
            std::cout << "nibs = " << n << std::endl;
            res_sigma_tan[t][hmid-100][l] = new TGraphErrors(n);
            res_sigma_tan[t][hmid-100][l]->SetTitle(Form("X Residual Sigma vs TanTheta m%d l%d; tan_theta ; sigma", hmid, l ));
            res_mean_tan_mean[t][hmid-100][l] = new TGraphErrors(n);
            res_mean_tan_mean[t][hmid-100][l]->SetTitle(Form("X Residual Mean vs TanTheta m%d l%d; tan_theta; mean", hmid, l ));
             for (int i = 1; i <= n; i++) {
               crtan[t][hmid-100][l]->cd(i);
               h1_restan[t][hmid-100][l] = h_cor_resx_tan_wire[t][hmid-100][l]->ProjectionY(Form("x_py__tgt%d_m%d_l%d_%d",t,  hmid, l, i), i, i     );
					if(h1_restan[t][hmid-100][l]->GetEntries() == 0 ) continue;
//             f1_restan[hmid-100] = new TF1(Form("f1_restan%d%d",hmid, i), "gaus");
               f1_restan[t][hmid-100][l] = new TF1(Form("f%d%d", hmid, l), "gaus(0) + [3]+[4]*x+[5]*x*x+[6]*x*x*x",      xmin, xmax);
               f1_restan[t][hmid-100][l]->SetParameter(0, 500);   // constant
               f1_restan[t][hmid-100][l]->SetParameter(1, 0);     // mean
               f1_restan[t][hmid-100][l]->SetParLimits(1, -2, 2); // mean
               f1_restan[t][hmid-100][l]->SetParameter(2, 0.3);
               f1_restan[t][hmid-100][l]->SetParLimits(2, 0.1, 1);
               f1_restan[t][hmid-100][l]->SetParameter(3, 0);
               f1_restan[t][hmid-100][l]->SetParameter(4, -1);
               h1_restan[t][hmid-100][l]->Fit(f1_restan[t][hmid-100][l], "", "", xmin, xmax);
 				   double mean      = f1_restan[t][hmid-100][l]->GetParameter(1);
 				   double mean_err  = f1_restan[t][hmid-100][l]->GetParError(1);
               double sigma     = f1_restan[t][hmid-100][l]->GetParameter(2);
               double sigma_err = f1_restan[t][hmid-100][l]->GetParError(2);
               res_sigma_tan[t][hmid-100][l]->SetPoint(i-1, i, sigma);
               res_sigma_tan[t][hmid-100][l]->SetPointError(i-1, 0, sigma_err);
					double tan = (double)(kHistoTanMax - kHistoTanMin)/n * i + kHistoTanMin;
               	res_mean_tan_mean[t][hmid-100][l]->SetPoint(i-1, tan, mean);
               res_mean_tan_mean[t][hmid-100][l]->SetPointError(i-1, 0, mean_err);
               h1_restan[t][hmid-100][l]->Draw();
            }
         crtan[t][hmid-100][l]->cd(23);
         res_sigma_tan[t][hmid-100][l]->SetMaximum(0.5);
         res_sigma_tan[t][hmid-100][l]->SetMinimum(-0.5);
         res_sigma_tan[t][hmid-100][l]->Draw("ap");
         crtan[t][hmid-100][l]->cd(24);
 			res_mean_tan_mean[t][hmid-100][l]->SetMaximum(1.0);
 			res_mean_tan_mean[t][hmid-100][l]->SetMinimum(-1.0);
 			res_mean_tan_mean[t][hmid-100][l]->SetLineStyle(0);
         res_mean_tan_mean[t][hmid-100][l]->Draw("ap");
         crtan[t][hmid-100][l]->SaveAs(pdf_name, "pdf");
			}
   	}
	}


	TCanvas *c35[n_modules];
	TGraphErrors *tg_tanm;
	TLegend *leg = new TLegend(0.8, 0.68, 0.99, 0.78);
	for(int m =1; m < 9; m++){
		if(m!=g_mod) continue;
	   c35[m]= new TCanvas();
		c35[m]->Divide(2,2);
		for(int l=0; l < 4; l++){
			for(int t=0; t < n_wires; t++){
   		c35[m]->cd(l+1);
			if(t==0){
				res_mean_tan_mean[t][m][l]->SetMarkerStyle(t + 20);
				res_mean_tan_mean[t][m][l]->Draw("AP");
			}
			else {
				res_mean_tan_mean[t][m][l]->SetMarkerStyle(t + 20);
				res_mean_tan_mean[t][m][l]->SetMarkerColor(t + 1);
				res_mean_tan_mean[t][m][l]->SetLineColor(t + 1);
				res_mean_tan_mean[t][m][l]->Draw("P SAME");
			}
      }
		leg->AddEntry( res_mean_tan_mean[0][m][l], "up, minus", "p");
		leg->AddEntry( res_mean_tan_mean[1][m][l], "down, minus", "p");
		leg->AddEntry( res_mean_tan_mean[2][m][l], "down, plus", "p");
		leg->AddEntry( res_mean_tan_mean[3][m][l], "up, plus", "p");
	}
   c35[m]->SaveAs(pdf_name, "pdf");
	}





//	TCanvas *c_vtx = new TCanvas();
//		c_vtx->Divide(3,2);
//		c_vtx->cd(1);
//		h_vtx_gx->Fit("gaus", "", "", -2, 3);
//		h_vtx_gx->Draw();
//		c_vtx->cd(2);
//		h_vtx_gy->Fit("gaus", "", "", -3, 1);
//		h_vtx_gy->Draw();
//		c_vtx->cd(3);
//		h_vtx_gz->Draw();
//		c_vtx->cd(4);
//		h_vtx_gx_gz->Draw("colz");
//		c_vtx->cd(5);
//		h_vtx_gx_gy->Draw("colz");
//   c_vtx->SaveAs(pdf_name, "pdf");
//
////
////
////  TCanvas *c_res_v[10];
////  for(int m =1; m < 9; m++){ 
////    c_res_v[m]= new TCanvas(); 
////    c_res_v[m]->Divide(2,2);
////    for(int l=0; l < n_layer; l++){
////     c_res_v[m]->cd(1+l);
////     if(m < 5) {
////        h_res_vtx_trk_x[m][l]->Fit("gaus", "", "", -0.5, 0.2);
////        h_res_vtx_trk_x[m][l]->Draw("colz");
////     }
////     else {
////        h_res_vtx_trk_x[m+1][l]->Fit("gaus", "", "", -0.5, 0.2);
////        h_res_vtx_trk_x[m+1][l]->Draw("colz");
////     
////	 }
////    c_res_v[m]->SaveAs(pdf_name, "pdf");
////  }
//
////
//
//
//	TCanvas *chm[n_modules];
//	for(int m =1; m < 9; m++){
//		if(m == 5) continue;
//	   chm[m]= new TCanvas();
//		chm[m]->Divide(4,3);
//		for(int l=0; l < 4; l++){
//   		chm[m]->cd(l+1);
//			h_hitmap[m][l]->Draw("colz");
//   		chm[m]->cd(l+5);
//			h_hitmap_x[m][l]->Draw();
//   		chm[m]->cd(l+9);
//			h_hitmap_y[m][l]->Draw();
//   	}
//   	chm[m]->SaveAs(pdf_name, "pdf");
//	}
//
//		
//
//	TCanvas *chtd[n_modules];
//	for(int m =1; m < 9; m++){
//		if(m == 5) continue;
//	   chtd[m]= new TCanvas();
//		chtd[m]->Divide(4,2);
//		for(int l=0; l < 4; l++){
//   		chtd[m]->cd(l+1);
//      	h_cluster_t_diff[m][l]->Draw();
//   		chtd[m]->cd(l+5);
//      	h_cluster_t_diff_2d[m][l]->Draw("colz");
//   	}
//   	chtd[m]->SaveAs(pdf_name, "pdf");
//	}
//
//
//
//
//	TCanvas *c2[n_modules];
//	for(int m =1; m < 9; m++){
//	   c2[m]= new TCanvas();
//		c2[m]->Divide(4,2);
//		for(int l=0; l < 4; l++){
//   		c2[m]->cd(l+1);
//	      if(m < 5) {
//      	   h_cluster_timing_x[m][l]->Draw("colz");
//   			c2[m]->cd(l+5);
//      	   h_cluster_timing_y[m][l]->Draw("colz");
//   	   }
// 	     else {
//         	h_cluster_timing_x[m][l]->Draw("colz");
//   			c2[m]->cd(l+5);
//         	h_cluster_timing_y[m][l]->Draw("colz");
//      	}
//   	}
//   c2[m]->SaveAs(pdf_name, "pdf");
//	}
//
//
//	TCanvas *cht[n_modules];
//	for(int m =1; m < 9; m++){
//		if(m == 5) continue;
//	   cht[m]= new TCanvas();
//		cht[m]->Divide(2,2);
//		for(int l=0; l < 4; l++){
//   		cht[m]->cd(l+1);
//      	h_hit_timing_x[m][l]->Draw();
//   	}
//   cht[m]->SaveAs(pdf_name, "pdf");
//	}
//
//	TCanvas *c03 = new TCanvas();
//	h_init_pos->Draw("colz");
//	c03->SaveAs(pdf_name, "pdf");
//	
//	TCanvas *c04 = new TCanvas();
//	c04->Divide(4,2);
//	for(int i=1; i < 9; i++){
//		c04->cd(i);
//		if(i < 5) {
//			h_init_posz_mod[i]->Draw();
//		}
//			h_init_posz_mod[i+1]->Draw();
//	}
//	c04->SaveAs(pdf_name, "pdf");
//
//	TCanvas *c22[n_modules];
//	for(int m =1; m < 9; m++){
//	   c22[m]= new TCanvas();
//		c22[m]->Divide(2,2);
//		for(int l=0; l < 4; l++){
//   		c22[m]->cd(l+1);
//	      if(m < 5) {
//      	   h_tot_end_fr[m][l]->Draw();
//      	   h_tot_end_bg[m][l]->Scale(h_tot_end_fr[m][l]->GetEntries() / h_tot_end_bg[m][l]->GetEntries());
//      	   std::cout << "scale " << h_tot_end_fr[m][l]->GetEntries() / h_tot_end_bg[m][l]->GetEntries() << std::endl;
//      	   h_tot_end_bg[m][l]->SetLineColor(kRed);
//      	   h_tot_end_bg[m][l]->Draw("same");
//   	   }
// 	     else {
//         	h_tot_end_fr[m][l]->Draw();
//      	   h_tot_end_bg[m][l]->Scale(h_tot_end_fr[m][l]->GetEntries() / h_tot_end_bg[m][l]->GetEntries());
//      	   h_tot_end_bg[m][l]->SetLineColor(kRed);
//         	h_tot_end_bg[m][l]->Draw("same");
//      	}
//   	}
//   c22[m]->SaveAs(pdf_name, "pdf");
//	}
//
//
////	TCanvas *c23[n_modules];
////	for(int m =1; m < 9; m++){
////	   c23[m]= new TCanvas();
////		c23[m]->Divide(2,2);
////		for(int l=0; l < 4; l++){
////   		c23[m]->cd(l+1);
////	      if(m < 5) {
////      	   h_tot_end_bg[m][l]->SetLineColor(kRed);
////      	   h_tot_end_bg[m][l]->Draw("same");
////   	   }
//// 	     else {
////      	   h_tot_end_bg[m][l]->SetLineColor(kRed);
////         	h_tot_end_bg[m][l]->Draw("same");
////      	}
////   	}
////   c23[m]->SaveAs(pdf_name, "pdf");
////	}
//
//
//
//	TCanvas *clgt = new TCanvas();
//	clgt->Divide(4,2);
//	for(int i =1; i < 9; i++){
//      clgt->cd(i);
//      if(i < 5) {
//         h_lg_t_mod[i]->Draw("colz");
//      }
//      else {
//         h_lg_t_mod[i+1]->Draw("colz");
//      }
//   }
//   clgt->SaveAs(pdf_name, "pdf");
//
//
//
//	TCanvas *c01 = new TCanvas();
//	h_chi2->Draw();
//	c01->SaveAs(pdf_name, "pdf");
//
//
//	TCanvas *c02 = new TCanvas();
//	c02->Divide(4,2);
//	for(int i =1; i < 9; i++){
//      c02->cd(i);
//      if(i < 5) {
//         h_chi2_mod[i]->Draw("colz");
//      }
//      else {
//         h_chi2_mod[i+1]->Draw("colz");
//      }
//   }
//   c02->SaveAs(pdf_name, "pdf");
//
//  TCanvas *c1[10];
//  for(int m =1; m < 9; m++){ 
//	 if(m==5) continue;
//    c1[m]= new TCanvas(); 
//    c1[m]->Divide(4,4);
//	for(int t=0; t < n_wires; t++){
//      for(int l=0; l < n_layers; l++){
//     		c1[m]->cd(1+l + t*4);
//     if(m < 5) {
//        h_res_x_wire[t][m][l]->Fit("gaus", "", "", -0.5, 0.5);
//        h_res_x_wire[t][m][l]->Draw("colz");
////		  h_pre_res_x[m][l]->SetLineColor(kRed);
////		  h_pre_res_x[m][l]->Draw("same");
//
//     }
//	 }
//	}
//    c1[m]->SaveAs(pdf_name, "pdf");
//  }
//
//  TCanvas *cresy[10];
//  for(int m =1; m < 9; m++){ 
//    cresy[m]= new TCanvas(); 
//    cresy[m]->Divide(2,2);
//    for(int l=0; l < n_layers; l++){
//     cresy[m]->cd(1+l);
//     if(m < 5) {
//        h_res_y[m][l]->Fit("gaus", "", "", -0.5, 0.5);
//        h_res_y[m][l]->Draw("colz");
////		  h_pre_res_y[m][l]->SetLineColor(kRed);
////		  h_pre_res_y[m][l]->Draw("same");
//
//     }
//     else {
//        h_res_y[m+1][l]->Fit("gaus", "", "", -0.5, 0.5);
//        h_res_y[m+1][l]->Draw("colz");
////		  h_pre_res_y[m+1][l]->SetLineColor(kRed);
////		  h_pre_res_y[m+1][l]->Draw("same");
//     }
//	 }
//    cresy[m]->SaveAs(pdf_name, "pdf");
//  }
//
//
//
//
//   TCanvas *c31[n_wires][n_modules][n_layers];
//   TGraphErrors *gr[n_wires][n_modules][n_layers];
//   TGraphErrors *gr_mean[n_wires][n_modules][n_layers];
//   TH1D *h1[n_wires][n_modules][n_layers];
//   TF1 *f1[n_wires][n_modules][n_layers];
//   for(int hmid=101; hmid < 110; hmid++){
//      if(hmid == 105)continue;
//		for(int t=0; t < n_wires; t++){	
//				for(int l=0; l < n_layers;l++){
//            c31[t][hmid-100][l] = new TCanvas();
//            c31[t][hmid-100][l]->Divide(5,5);
//            int n = h_cor_res_fitlx_wire[t][hmid-100][l]->GetNbinsX();
//            double xmin = -1;
//            double xmax =  1;
//            std::cout << "nibs = " << n << std::endl;
//            gr[t][hmid-100][l] = new TGraphErrors(n);
//            gr[t][hmid-100][l]->SetTitle(Form("X Residual Sigma m%d l%d; local x; sigma", hmid, l ));
//            gr_mean[t][hmid-100][l] = new TGraphErrors(n);
//            gr_mean[t][hmid-100][l]->SetTitle(Form("X Residual Mean m%d l%d; local x; mean", hmid, l ));
//             for (int i = 1; i <= n; i++) {
//               c31[t][hmid-100][l]->cd(i);
//               h1[t][hmid-100][l] = h_cor_res_fitlx_wire[t][hmid-100][l]->ProjectionY(Form("x_py_tgt%d_m%d_l%d_%d", t, hmid, l, i), i, i     );
////             f1[hmid-100] = new TF1(Form("f1%d%d",hmid, i), "gaus");
//               f1[t][hmid-100][l] = new TF1(Form("f%d%d", hmid, l), "gaus(0) + [3]+[4]*x+[5]*x*x+[6]*x*x*x",      xmin, xmax);
//               f1[t][hmid-100][l]->SetParameter(0, 500);   // constant
//               f1[t][hmid-100][l]->SetParameter(1, 0);     // mean
//               f1[t][hmid-100][l]->SetParLimits(1, -2, 2); // mean
//               f1[t][hmid-100][l]->SetParameter(2, 0.3);
//               f1[t][hmid-100][l]->SetParLimits(2, 0.1, 1);
//               f1[t][hmid-100][l]->SetParameter(3, 0);
//               f1[t][hmid-100][l]->SetParameter(4, -1);
//               h1[t][hmid-100][l]->Fit(f1[t][hmid-100][l], "", "", xmin, xmax);
// 				   double mean      = f1[t][hmid-100][l]->GetParameter(1);
// 				   double mean_err  = f1[t][hmid-100][l]->GetParError(1);
//               double sigma     = f1[t][hmid-100][l]->GetParameter(2);
//               double sigma_err = f1[t][hmid-100][l]->GetParError(2);
//               std::cout << "sigma = " << sigma << std::endl;
//               gr[t][hmid-100][l]->SetPoint(i-1, i, sigma);
//               gr[t][hmid-100][l]->SetPointError(i-1, 0, sigma_err);
//               gr_mean[t][hmid-100][l]->SetPoint(i-1, i, mean);
//               gr_mean[t][hmid-100][l]->SetPointError(i-1, 0, mean_err);
//               h1[t][hmid-100][l]->Draw();
//            }
//         c31[t][hmid-100][l]->cd(23);
//         gr[t][hmid-100][l]->SetMaximum(0.5);
//         gr[t][hmid-100][l]->SetMinimum(-0.5);
//         gr[t][hmid-100][l]->Draw("ap");
//         c31[t][hmid-100][l]->cd(24);
// 			gr_mean[t][hmid-100][l]->SetMaximum(1.0);
// 			gr_mean[t][hmid-100][l]->SetMinimum(-1.0);
// 			gr_mean[t][hmid-100][l]->SetLineStyle(0);
//         gr_mean[t][hmid-100][l]->Draw("ap");
//         c31[t][hmid-100][l]->SaveAs(pdf_name, "pdf");
//			}
//   	}
//	}
//
//
//
//   TCanvas *c31y[n_wires][n_modules][n_modules];
//   TGraphErrors *gr_y[n_wires][n_modules][n_modules];
//   TGraphErrors *gr_y_mean[n_wires][n_modules][n_modules];
//   TH1D *h1y[n_wires][n_modules][n_modules];
//   TF1 *f1y[n_wires][n_modules][n_modules];
//   for(int hmid=101; hmid < 110; hmid++){
//      if(hmid == 105)continue;
//		for(int t=0; t < n_wires; t++){
//				for(int l=0; l < n_layers;l++){
//            c31y[t][hmid-100][l] = new TCanvas();
//            c31y[t][hmid-100][l]->Divide(5,5);
//            int n = h_cor_res_fitly_wire[t][hmid-100][l]->GetNbinsX();
//            double xmin = -1;
//            double xmax =  1;
//            std::cout << "nibs = " << n << std::endl;
//            gr_y[t][hmid-100][l] = new TGraphErrors(n);
//            gr_y[t][hmid-100][l]->SetTitle(Form("Y Residual Sigma m%d l%d; local y; sigma", hmid, l ));
//            gr_y_mean[t][hmid-100][l] = new TGraphErrors(n);
//            gr_y_mean[t][hmid-100][l]->SetTitle(Form("Y Residual Mean m%d l%d; local y; mean", hmid, l ));
//             for (int i = 1; i <= n; i++) {
//               c31y[t][hmid-100][l]->cd(i);
//               h1y[t][hmid-100][l] = h_cor_res_fitly_wire[t][hmid-100][l]->ProjectionY(Form("y_py_tgt%d_m%d_l%d_%d",t,  hmid, l, i), i, i     );
////             f1y[hmid-100] = new TF1(Form("f1y%d%d",hmid, i), "gaus");
//               f1y[t][hmid-100][l] = new TF1(Form("f%d%d", hmid, l), "gaus(0) + [3]+[4]*x+[5]*x*x+[6]*x*x*x",      xmin, xmax);
//               f1y[t][hmid-100][l]->SetParameter(0, 500);   // constant
//               f1y[t][hmid-100][l]->SetParameter(1, 0);     // mean
//               f1y[t][hmid-100][l]->SetParLimits(1, -2, 2); // mean
//               f1y[t][hmid-100][l]->SetParameter(2, 0.3);
//               f1y[t][hmid-100][l]->SetParLimits(2, 0.1, 1);
//               f1y[t][hmid-100][l]->SetParameter(3, 0);
//               f1y[t][hmid-100][l]->SetParameter(4, -1);
//               h1y[t][hmid-100][l]->Fit(f1y[t][hmid-100][l], "", "", xmin, xmax);
// 				   double mean      = f1y[t][hmid-100][l]->GetParameter(1);
// 				   double mean_err  = f1y[t][hmid-100][l]->GetParError(1);
//               double sigma     = f1y[t][hmid-100][l]->GetParameter(2);
//               double sigma_err = f1y[t][hmid-100][l]->GetParError(2);
//               std::cout << "sigma = " << sigma << std::endl;
//               gr_y[t][hmid-100][l]->SetPoint(i-1, i, sigma);
//               gr_y[t][hmid-100][l]->SetPointError(i-1, 0, sigma_err);
//               gr_y_mean[t][hmid-100][l]->SetPoint(i-1, i, mean);
//               gr_y_mean[t][hmid-100][l]->SetPointError(i-1, 0, mean_err);
//               h1y[t][hmid-100][l]->Draw();
//            }
//         c31y[t][hmid-100][l]->cd(23);
//         gr_y[t][hmid-100][l]->SetMaximum(0.5);
//         gr_y[t][hmid-100][l]->SetMinimum(-0.5);
//         gr_y[t][hmid-100][l]->Draw("ap");
//         c31y[t][hmid-100][l]->cd(24);
// 			gr_y_mean[t][hmid-100][l]->SetMaximum(1.0);
// 			gr_y_mean[t][hmid-100][l]->SetMinimum(-1.0);
// 			gr_y_mean[t][hmid-100][l]->SetLineStyle(0);
//         gr_y_mean[t][hmid-100][l]->Draw("ap");
//         c31y[t][hmid-100][l]->SaveAs(pdf_name, "pdf");
//			}
//		}
//   }
//
//
//	TCanvas *c31a[n_modules];
//	for(int m =1; m < 9; m++){
//		if(m==5) continue;
//	   c31a[m]= new TCanvas();
//		c31a[m]->Divide(4,4);
//		for(int t=0; t < 4; t++){
//		for(int l=0; l < 4; l++){
//   		c31a[m]->cd(l+1 + t*4);
//			gr[t][m][l]->Draw("ap");
//      }
//		}
//   c31a[m]->SaveAs(pdf_name, "pdf");
//	}
//
//
//	TCanvas *c31a2[n_modules];
//	for(int m =1; m < 9; m++){
//		if(m==5) continue;
//	   c31a2[m]= new TCanvas();
//		c31a2[m]->Divide(2,2);
//		for(int l=0; l < 4; l++){
//			for(int t=0; t < n_wires; t++){
//   		c31a2[m]->cd(l+1);
//			if(t==0){
//				gr_mean[t][m][l]->Draw("ap");
//			}
//			else {
//				gr_mean[t][m][l]->SetMarkerColor(t);
//				gr_mean[t][m][l]->Draw("ap, same");
//			}
//      }
//	}
//   c31a2[m]->SaveAs(pdf_name, "pdf");
//	}
//
//
//
//	TCanvas *c31ya[n_modules];
//	for(int m =1; m < 9; m++){
//		if(m==5) continue;
//	   c31ya[m]= new TCanvas();
//		c31ya[m]->Divide(4,4);
//		for(int t=0; t < 4; t++){
//		for(int l=0; l < 4; l++){
//   		c31ya[m]->cd(l+1 + t*4);
//			gr_y[t][m][l]->Draw("ap");
//      }
//		}
//   c31ya[m]->SaveAs(pdf_name, "pdf");
//	}
//
//
//	TCanvas *c31ya2[n_modules];
//	for(int m =1; m < 9; m++){
//		if(m==5) continue;
//	   c31ya2[m]= new TCanvas();
//		c31ya2[m]->Divide(2,2);
//	
//		for(int l=0; l < 4; l++){
//   		c31ya2[m]->cd(l+1);
//			for(int t=0; t < n_wires; t++){
//				if(t==0){
//				gr_y_mean[t][m][l]->Draw("ap");
//				}
//				else  {
//				gr_y_mean[t][m][l]->SetMarkerColor(t);
//				gr_y_mean[t][m][l]->Draw("ap, same");
//				}
//			}
//      }
//   c31ya2[m]->SaveAs(pdf_name, "pdf");
//	}
//
//
//
//	TCanvas *c18;
//	c18 = new TCanvas();
//	c18->Divide(4,2);
//	for(int mid=101; mid < 110; mid++){
//		if(mid == 105) continue;
//		if(mid < 105){
//		c18->cd(mid-100);
//		h_res_lg_x[mid-100]->Draw();
//		h_bak_res_lg_x[mid-100]->SetLineColor(kRed);
//		h_bak_res_lg_x[mid-100]->Draw("sames");
//		}
//	   else if(mid > 105){
//			c18->cd(mid-101);
//			h_res_lg_x[mid-100]->Draw();
//			h_bak_res_lg_x[mid-100]->SetLineColor(kRed);
//			h_bak_res_lg_x[mid-100]->Draw("sames");
//			
//		}
//   }
//	c18->SaveAs(pdf_name, "pdf");
//
//   TCanvas *c19;
//	c19 = new TCanvas();
//	c19->Divide(4,2);
//	for(int mid=101; mid < 110; mid++){
//		if(mid == 105) continue;
//		if(mid < 105){
//		c19->cd(mid-100);
//		h_res_lg_y[mid-100]->Draw();
//		h_bak_res_lg_y[mid-100]->SetLineColor(kRed);
//		h_bak_res_lg_y[mid-100]->Draw("sames");
//		}
//	   else if(mid > 105){
//			c19->cd(mid-101);
//			h_res_lg_y[mid-100]->Draw();
//			h_bak_res_lg_y[mid-100]->SetLineColor(kRed);
//			h_bak_res_lg_y[mid-100]->Draw("sames");
//			
//		}
//   }
//	c19->SaveAs(pdf_name, "pdf");
//
//   TCanvas *c20;
//	c20 = new TCanvas();
//	c20->Divide(4,2);
//	for(int mid=101; mid < 110; mid++){
//		if(mid == 105) continue;
//		if(mid < 105){
//		c20->cd(mid-100);
//		h_res_lg_2d[mid-100]->Draw("colz");
////		h_bak_res_lg_2d[mid-100]->SetLineColor(kRed);
////		h_bak_res_lg_2d[mid-100]->Draw("same");
//		}
//	   else if(mid > 105){
//			c20->cd(mid-101);
//			h_res_lg_2d[mid-100]->Draw("colz");
////			h_bak_res_lg_2d[mid-100]->SetLineColor(kRed);
////			h_bak_res_lg_2d[mid-100]->Draw("same");
//			
//		}
//   }
//	c20->SaveAs(pdf_name, "pdf");
//
//
//   TCanvas *c20_bg;
//	c20_bg = new TCanvas();
//	c20_bg->Divide(4,2);
//	for(int mid=101; mid < 110; mid++){
//		if(mid == 105) continue;
//		if(mid < 105){
//		c20_bg->cd(mid-100);
//		h_bak_res_lg_2d[mid-100]->Draw("colz");
////		h_bak_res_lg_2d[mid-100]->SetLineColor(kRed);
////		h_bak_res_lg_2d[mid-100]->Draw("same");
//		}
//	   else if(mid > 105){
//			c20_bg->cd(mid-101);
//			h_bak_res_lg_2d[mid-100]->Draw("colz");
////			h_bak_res_lg_2d[mid-100]->SetLineColor(kRed);
////			h_bak_res_lg_2d[mid-100]->Draw("same");
//		}
//   }
//	c20_bg->SaveAs(pdf_name, "pdf");
//
//// TCanvas *c6b = new TCanvas();
//// c6b->Divide(2,2);
//// for(int tgt=0; tgt<2; tgt++){
//// for(int i =1; i < 9; i++){
////   
////    c6b->cd(i);
////    if(i < 5) {
////       h_cor_dz_time_t0cor[i][residual_layer]->Draw("colz");
////    }
////    else {
////       h_cor_dz_time_t0cor[i+1][residual_layer]->Draw("colz");
////    }
//// }
//// }
//// c6b->SaveAs(pdf_name, "pdf");
////
////
////
////TCanvas *c16b[2][10][n_div];
////TGraphErrors *gr16b[2][10][n_div];
////TH1D *h16b[2][10][n_div];
////TF1 *f16b[2][10][n_div];
////TF1 *flab[2][10][n_div];
////double xminb[10]  = {0, -4, -7, -7,     -6, 0, -4, -5.5, -4, -4};//mod100-109
////double xmaxb[10]  = {0,  4, 10, 10,    5.5, 0,   4,  4.0,  5,  5};
////double flminb[10] = {0, 120, 120, 120, 120, 0, 200, 120, 100, 180};
////double flmaxb[10] = {0, 450, 450, 450, 450, 0, 550, 450, 320, 450};
////for(int t=0; t < 2; t++){
//// int hmid = 106;
//// for(int d=0 ; d < n_div; d++){
////   c16b[t][hmid-100][d] = new TCanvas();
////   int n = h_cor_dz_time_t0cor[hmid-100][residual_layer][d]->GetNbinsX();
////   c16b[t][hmid-100][d]->Divide(5,5);
////   std::cout << "nbins dz = " << n << std::endl;
////   gr16b[t][hmid-100][d] = new TGraphErrors(n);
////	gr16b[t][hmid-100][d]->SetMaximum( 8.0);
//// gr16b[t][hmid-100][d]->SetMinimum(-8.0);
////    for (int i = 1; i <= n; i++) {
////      c16b[t][hmid-100][d]->cd(i);
////      flab[t][hmid-100][d] = new TF1(Form("fla%d%d", t, d), "pol1", flminb[hmid-100], flmaxb[hmid-100]);
////      h16b[t][hmid-100][d] = h_cor_dz_time_t0cor[t][hmid-100][residual_layer][d]->ProjectionY(Form("_py%d%d%d", hmid, i), i, i);
////        f16b[t][hmid-100][d] = new TF1("fitFunction", "gaus(0)+[3]+[4]*x+[5]*x*x", xminb[hmid-100],xmaxb[hmid-100]);
////        f16b[t][hmid-100][d] = new TF1(Form("fitFunction%d%d", t, d), "gaus(0)+[3]*x*x", xminb[hmid-100],xmaxb[hmid-100]);
////      f16b[t][hmid-100][d] = new TF1("fitFunction", "gaus(0)+[3]*x", xminb[hmid-100],xmaxb[hmid-100]);
////      f16b[hmid-100] = new TF1("fitFunction", "[0]*exp(-0.5*((x-[1])/[2])**2) + [3]*TMath::Erfc([4]*(x-[5]))", xmin, xmax);
////      f16b[hmid-100]->SetParNames("Constant", "Mean", "Sigma", "TailHeight", "TailSlope","TailX0");
////      f16b[t][hmid-100][d]->SetParameter(0, 20); // constant
////      f16b[t][hmid-100][d]->SetParameter(1, 0);     // mean
////      f16b[t][hmid-100][d]->SetParameter(2, 3);    // sigma
////        f16b[t][hmid-100][d]->SetParameter(3, 0);    
////        f16b[t][hmid-100][d]->SetParameter(4, -1);    
////        f16b[t][hmid-100][d]->SetParameter(4, -0.5);  
////      h16b[t][hmid-100][d]->Fit(f16b[t][hmid-100][d], "", "", xminb[hmid-100], xmaxb[hmid-100]);
////
////       double chi2 = f16b[t][hmid-100][d]->GetChisquare();
////      double mean = f16b[t][hmid-100][d]->GetParameter(1);
////       double sigma_err = f16b[t][hmid-100][d]->GetParError(2);
////      std::cout << "mod, fit chi2  = " << hmid  << ", "  << chi2 << std::endl;
////      if(chi2 < 5) continue;
////      if(sigma_err > 10) continue;
////       gr16b[t][hmid-100][d]->SetPoint(i-1, i*(600/n), mean);
////       gr16b[t][hmid-100][d]->SetPointError(i-1, 0, sigma_err);
////       gr16b[t][hmid-100][d]->Fit(flab[t][hmid-100][d], "R");
////       h16b[t][hmid-100][d]->Draw();
////   }
////      c16b[t][hmid-100][d]->cd(6);
////      c16b[t][hmid-100][d]->SaveAs(pdf_name, "pdf");
////	}
////
//
////
////TCanvas *c0d = new TCanvas();
////t0diff->Draw();
////d->SaveAs(pdf_name, "pdf");
//
//// TCanvas *c17b[2];
////  	c17b[t] = new TCanvas();
////	 	c17b[t]->Divide(5,4);
//// 	for(int d=0; d < n_div; d++){
//// 		c17b[t]->cd(d+1);
////       gr16b[t][6][d]->SetTitle(Form("residual/tan_theta tgt%d mod 106 : timing_lg ;  timing_lg; residual/tan_theta", t) );
//// 	   gr16b[t][6][d]->Draw("AP");
//// 		
//// 	}
////   c17b[t]->SaveAs(pdf_name, "pdf");
//////}
//////
////
//// TCanvas *c18[2];
////GraphErrors *tg18[2];
//// for(int t=0; t < 2; t++){
//// 	c18[t] = new TCanvas();
//// 	tg18[t] = new TGraphErrors(n_div);
//// 	for(int d=0; d < n_div; d++){
//// 		double tilt = flab[t][6][d]->GetParameter(1);
//// 		tg18[t]->SetPoint(d, d, tilt);
//// 	}
//// 		tg18[t]->SetMarkerSize(msize);
//// 	tg18[t]->Draw("AP");
////18[t]->SaveAs(pdf_name, "pdf");
////}
////
//
//// TCanvas *c19[2];
//// for(int t=0; t < 2; t++){
//// 	c19[t] = new TCanvas();
//// 	c19[t]->Divide(4,5);
//// 	for(int d=0; d < n_div; d++){
//// 		c19[t]->cd(d+1);
//// 		h_slopevel[t][6][residual_layer][d]->Draw("colz");
//// 	}
//// c19[t]->SaveAs(pdf_name, "pdf");
////}
////
////
//

	for(int m=0; m < 10; m++){
	std::cout << "m = " << m+100 << ",fore lg residual = " << cnt_lgres_fore[m] << ", bg lg residual = " << cnt_lgres_bg[m] << std::endl;
	}
	c0->SaveAs(pdf_name + "]", "pdf");
}




