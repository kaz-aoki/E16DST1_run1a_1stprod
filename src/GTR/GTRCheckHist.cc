#include "GTR/GTRCheckHist.hh"
#include "TH1D.h"

GTRCheckHist::GTRCheckHist(){
  for(int l=0;l<3;l++){
    h_cl_ncluster_modall_x[l] = new TH1D(Form("cl_ncluster_modall_x_%d", l), Form("cl_ncluster_modall_x_%d", l),1000, -0.5 ,999.5);
    h_cl_ncluster_modall_y[l] = new TH1D(Form("cl_ncluster_modall_y_%d", l), Form("cl_ncluster_modall_y_%d", l),1000, -0.5,999.5);
    h_cl_ncluster_modall_yb[l] = new TH1D(Form("cl_ncluster_modall_yb_%d", l), Form("cl_ncluster_modall_yb_%d", l),1000, -0.5, 999.5);
  }
    for(int m=100; m < 110; m++){
        for(int l=0; l<3; l++){
            h_cl_ncluster_x[m-100][l] = new TH1D(Form("cl_ncluster_x%d_%d",m, l), Form("cl_ncluster_x%d_%d",m, l),200, -0.5 ,199.5);
            h_cl_ncluster_y[m-100][l] = new TH1D(Form("cl_ncluster_y%d_%d",m, l), Form("cl_ncluster_y%d_%d",m, l),200, -0.5,199.5);
            h_cl_ncluster_yb[m-100][l] = new TH1D(Form("cl_ncluster_yb%d_%d",m, l), Form("cl_ncluster_yb%d_%d",m, l),200, -0.5, 199.5);
            h_cl_numhits_x[m-100][l] = new TH1D(Form("cl_numhits_x%d_%d",m, l), Form("cl_numhits_x%d_%d",m, l),30, -0.5 ,29.5);
            h_cl_numhits_y[m-100][l] = new TH1D(Form("cl_numhits_y%d_%d",m, l), Form("cl_numhits_y%d_%d",m, l),30, -0.5,29.5);
            h_cl_numhits_yb[m-100][l] = new TH1D(Form("cl_numhits_yb%d_%d",m, l), Form("cl_numhits_yb%d_%d",m, l),30, -0.5, 29.5);
            h_cl_charge_x[m-100][l] = new TH1D(Form("cl_charge_x%d_%d",m, l), Form("cl_charge_x%d_%d",m, l),100, 0,3000);
            h_cl_charge_y[m-100][l] = new TH1D(Form("cl_charge_y%d_%d",m, l), Form("cl_charge_y%d_%d",m, l),100, 0,3000);
            h_cl_charge_yb[m-100][l] = new TH1D(Form("cl_charge_yb%d_%d",m, l), Form("cl_charge_yb%d_%d",m, l),100, 0,3000);
            h_cl_local_x[m-100][l] = new TH1D(Form("cl_local_x%d_%d",m, l), Form("cl_local_x%d_%d",m, l),100, -50*(l+1), 50*(l+1));
            h_cl_local_y[m-100][l] = new TH1D(Form("cl_local_y%d_%d",m, l), Form("cl_local_y%d_%d",m, l),100, -50*(l+1), 50*(l+1));
            h_cl_local_yb[m-100][l] = new TH1D(Form("cl_local_y%d_%d",m, l), Form("cl_local_y%d_%d",m, l),100, -50*(l+1), 50*(l+1));
            h_cl_timing_x[m-100][l] = new TH1D(Form("cl_timing_x%d_%d",m, l), Form("cl_timing_x%d_%d",m, l),100, -50, 800);
            h_cl_timing_y[m-100][l] = new TH1D(Form("cl_timing_y%d_%d",m, l), Form("cl_timing_y%d_%d",m, l),100, -50, 800);
            h_cl_timing_yb[m-100][l] = new TH1D(Form("cl_timing_yb%d_%d",m, l), Form("cl_timing_yb%d_%d",m, l),100,0, 800);
            
            h_cl_max_peak_x[m-100][l] = new TH1D(Form("cl_max_peak_x%d_%d",m, l), Form("cl_max_peak_x%d_%d",m, l),100, 0,3000);
            h_cl_max_peak_y[m-100][l] = new TH1D(Form("cl_max_peak_y%d_%d",m, l), Form("cl_max_peak_y%d_%d",m, l),100, 0,3000);
            h_cl_max_peak_yb[m-100][l] = new TH1D(Form("cl_max_peak_yb%d_%d",m, l), Form("cl_max_peak_yb%d_%d",m, l),100, 0,3000);
            h_cl_max_peak_ch_x[m-100][l] = new TH1D(Form("cl_max_peak_ch_x%d_%d",m, l), Form("cl_max_peak_ch_x%d_%d",m, l),1000, 0,1000);
            h_cl_max_peak_ch_y[m-100][l] = new TH1D(Form("cl_max_peak_ch_y%d_%d",m, l), Form("cl_max_peak_ch_y%d_%d",m, l),1000, 0,1000);
            h_cl_max_peak_ch_yb[m-100][l] = new TH1D(Form("cl_max_peak_ch_yb%d_%d",m, l), Form("cl_max_peak_ch_yb%d_%d",m, l),1000, 0,1000);
            h_cl_tdcpos_x[m-100][l] = new TH1D(Form("cl_tdcpos_x%d_%d",m, l), Form("cl_tdcpos_x%d_%d",m, l),100, -50*(l+1), 50*(l+1));
            h_cl_tdcpos_y[m-100][l] = new TH1D(Form("cl_tdcpos_y%d_%d",m, l), Form("cl_tdcpos_y%d_%d",m, l),100, -50*(l+1), 50*(l+1));
            h_cl_tdcpos_yb[m-100][l] = new TH1D(Form("cl_tdcpos_yb%d_%d",m, l), Form("cl_tdcpos_yb%d_%d",m, l),100, -50*(l+1), 50*(l+1));
            h_cl_tan_x[m-100][l] = new TH1D(Form("cl_tan_x%d_%d",m, l), Form("cl_tan_x%d_%d",m, l),20, -4, 4);
            h_cl_tan_y[m-100][l] = new TH1D(Form("cl_tan_y%d_%d",m, l), Form("cl_tan_x%d_%d",m, l),20, -4, 4);
            h_cl_tan_yb[m-100][l] = new TH1D(Form("cl_tan_yb%d_%d",m, l), Form("cl_tan_x%d_%d",m, l),20, -4, 4);
 			
        }
//-------straight_track -----------//
		h_tgt_z[m-100] = new TH1D(Form("h_tgt_z_m%d", m), Form("h_tgt_z_m%d", m), 400, -50, 50);          
    }
}
GTRCheckHist::~GTRCheckHist(){
    
  for(int l=0; l<3; l++){
    delete h_cl_ncluster_modall_x[l];
    delete h_cl_ncluster_modall_y[l];
    delete h_cl_ncluster_modall_yb[l];
  }
for(int m=100; m < 110; m++){
        for(int l=0; l<3; l++){
            delete h_cl_ncluster_x[m-100][l];
            delete h_cl_ncluster_y[m-100][l];
            delete h_cl_ncluster_yb[m-100][l];
            delete h_cl_numhits_x[m-100][l];
            delete h_cl_numhits_y[m-100][l];
            delete h_cl_numhits_yb[m-100][l];
            delete h_cl_charge_x[m-100][l];
            delete h_cl_charge_y[m-100][l];
            delete h_cl_charge_yb[m-100][l];
            delete h_cl_local_x[m-100][l];
            delete h_cl_local_y[m-100][l];
            delete h_cl_local_yb[m-100][l];
        }
    }
}

void GTRCheckHist::Fill(E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> *gtr1){
	std::vector<E16DST_DST1GTRCluster> &clusters = gtr1->Clusters();
	
	int nclusterx[10][3] = {0};	
	int nclustery[10][3] = {0};	
	int nclusteryb[10][3] = {0};	
	int nclusterx_modall[3] = {0};	
	int nclustery_modall[3] = {0};	
	int nclusteryb_modall[3] = {0};	

    for(int i=0; i < clusters.size(); i++){
        E16DST_DST1GTRCluster &cl = clusters[i];
        if(cl.Type() == 0){
//        std::cout << "cluster id :: " << i << std::endl;
//        std::cout << "module id :: " << cl.ModuleId() << std::endl;
//        std::cout << "layer id :: " << cl.LayerId() << std::endl;
//        std::cout << "cluster charge :: " << cl.PeakSum() << std::endl;
	  nclusterx[cl.ModuleId()-100][cl.LayerId()]++;
	  nclusterx_modall[cl.LayerId()]++;
            h_cl_numhits_x[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.NumHits());
            h_cl_charge_x[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.PeakSum());
            h_cl_local_x[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.LocalX());
            h_cl_timing_x[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.Timing());
            h_cl_max_peak_x[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.MaxPeakHeight());
            h_cl_max_peak_ch_x[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.MaxPeakCh());
            h_cl_tdcpos_x[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.TdcPos());
            h_cl_tan_x[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.TanTheta());
		}
        else if(cl.Type() == 1){
	  nclustery[cl.ModuleId()-100][cl.LayerId()]++;
	  nclustery_modall[cl.LayerId()]++;
            h_cl_numhits_y[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.NumHits());
            h_cl_charge_y[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.PeakSum());
            h_cl_local_y[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.LocalX());
            h_cl_timing_y[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.Timing());
            h_cl_max_peak_y[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.MaxPeakHeight());
            h_cl_max_peak_ch_y[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.MaxPeakCh());
            h_cl_tdcpos_y[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.TdcPos());
            h_cl_tan_y[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.TanTheta());
        }
        else if(cl.Type() == 2){
	  nclusteryb[cl.ModuleId()-100][cl.LayerId()]++;
	  nclusteryb_modall[cl.LayerId()]++;
            h_cl_numhits_yb[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.NumHits());
            h_cl_charge_yb[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.PeakSum());
            h_cl_local_yb[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.LocalX());
            h_cl_timing_yb[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.Timing());
            h_cl_max_peak_yb[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.MaxPeakHeight());
            h_cl_max_peak_ch_yb[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.MaxPeakCh());
            h_cl_tdcpos_yb[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.TdcPos());
            h_cl_tan_yb[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.TanTheta());
        }

    }//n cluster loop

    for(int i=0;i<10;i++){
      for(int j=0;j<3;j++){
	h_cl_ncluster_x[i][j]->Fill(nclusterx[i][j]);
	h_cl_ncluster_y[i][j]->Fill(nclustery[i][j]);
	h_cl_ncluster_yb[i][j]->Fill(nclusteryb[i][j]);
      }
    }
    for(int i=0;i<3;i++){
      h_cl_ncluster_modall_x[i]->Fill(nclusterx_modall[i]);
      h_cl_ncluster_modall_y[i]->Fill(nclustery_modall[i]);
      h_cl_ncluster_modall_yb[i]->Fill(nclusteryb_modall[i]);
    }

}

void GTRCheckHist::Fill(std::vector<std::shared_ptr<E16DST_DST1StraightTrack3D>> st_tracks){
	for(int i=0; i<st_tracks.size();i++){	
		auto trk = st_tracks[i];
		h_tgt_z[trk->ModuleID()- 100]->Fill(trk->TgtPosZ());
	}	
}
