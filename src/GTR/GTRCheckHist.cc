#include "GTR/GTRCheckHist.hh"
#include "TH1D.h"

GTRCheckHist::GTRCheckHist(){
  for(int l=0;l<3;l++){
    h_cl_ncluster_modall_x[l] = new TH1D(Form("cl_ncluster_modall_x_%d", l), Form("cl_ncluster_modall_x_%d", l),100, -0.5 ,99.5);
    h_cl_ncluster_modall_y[l] = new TH1D(Form("cl_ncluster_modall_y_%d", l), Form("cl_ncluster_modall_y_%d", l),100, -0.5 ,99.5);
    h_cl_ncluster_modall_yb[l] = new TH1D(Form("cl_ncluster_modall_yb_%d", l), Form("cl_ncluster_modall_yb_%d", l),100, -0.5, 99.5);
  }
    for(int m=100; m < 110; m++){
        for(int l=0; l<3; l++){
            h_hit_ph_x[m-100][l] = new TH1D(Form("hit_ph_x%d_%d",m, l), Form("hit_ph_x%d_%d",m, l),100, 0, 3000);
            h_hit_ph_y[m-100][l] = new TH1D(Form("hit_ph_y%d_%d",m, l), Form("hit_ph_y%d_%d",m, l),100, 0, 3000);
            h_hit_timing_x[m-100][l] = new TH1D(Form("hit_timing_x%d_%d",m, l), Form("hit_timing_x%d_%d",m, l),100, -50, 800);
            h_cl_ncluster_x[m-100][l] = new TH1D(Form("cl_ncluster_x%d_%d",m, l), Form("cl_ncluster_x%d_%d",m, l),30, -0.5 ,29.5);
            h_cl_ncluster_y[m-100][l] = new TH1D(Form("cl_ncluster_y%d_%d",m, l), Form("cl_ncluster_y%d_%d",m, l),30, -0.5,29.5);
            h_cl_ncluster_yb[m-100][l] = new TH1D(Form("cl_ncluster_yb%d_%d",m, l), Form("cl_ncluster_yb%d_%d",m, l),30, -0.5, 29.5);
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
            
            h_cl_max_peak_x[m-100][l] = new TH1D(Form("cl_max_peak_x%d_%d",m, l), Form("cl_max_peak_x%d_%d",m, l),100, 0,1800);
            h_cl_max_peak_y[m-100][l] = new TH1D(Form("cl_max_peak_y%d_%d",m, l), Form("cl_max_peak_y%d_%d",m, l),100, 0,1800);
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

				h_hit_map[m-100][l] = new TH2D(Form("h_hit_map%d_%d", m, l), Form("h_hit_map%d_%d", m, l), 288 * (l + 1 ) / 4 , (-288 * (l + 1))/ 2.0 * 0.35, (288 * (l +1)) / 2.0 * 0.35, 72 * (l + 1) / 4, -288 * (l +1 ) / 2.0 * 0.35, 288 * (l +1 ) /2.0* 0.35);
				h_hit_multiplicity_x[m-100][l] = new TH1D(Form("h_hit_multiplicity_x_%d_%d", m, l), Form("h_hit_multiplicity_x%d_%d", m, l), 100 , -0.5, 99.5);
				h_cluster_multiplicity_x[m-100][l] = new TH1D(Form("h_cluster_multiplicity_x_%d_%d", m, l), Form("h_cluster_multiplicity_x%d_%d", m, l), 100 , -0.5, 99.5);
				h_cluster_multiplicity_y[m-100][l] = new TH1D(Form("h_cluster_multiplicity_x_%d_%d", m, l), Form("h_cluster_multiplicity_y%d_%d", m, l), 100 , -0.5, 99.5);

				for(int k=0; k < 12; k++){
				h_cluster_multiplicity_xdependence[m-100][l][k] = new TH1D(Form("h_cluster_multiplicity_xdependence_%d_%d_%d", m, l, k), Form("h_cluster_multiplicity_xdependence%d_%d_%d", m, l, k), 12 , -0.5, 11.5);
				h_cluster_multiplicity_ydependence[m-100][l][k] = new TH1D(Form("h_cluster_multiplicity_ydependence_%d_%d_%d", m, l, k), Form("h_cluster_multiplicity_ydependence%d_%d_%d", m, l, k), 12 , -0.5, 11.5);
			}
 			
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
			   delete h_hit_ph_x[m-100][l]; 
			   delete h_hit_ph_y[m-100][l]; 
			   delete h_hit_timing_x[m-100][l]; 
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
            delete h_cl_timing_x[m-100][l];
            delete h_cl_timing_y[m-100][l];
            delete h_cl_timing_yb[m-100][l];
            delete h_hit_map[m-100][l];
			   delete h_hit_multiplicity_x[m-100][l];
//			   delete h_hit_multiplicity_y[m-100][l];
        }
    }
}

void GTRCheckHist::Fill(E16DST_DST1PhysicsRecord *record){
   auto& gtr = record->GTR();
	std::vector<E16DST_DST1GTRHit>     &hits     = gtr.Hits();
	std::vector<E16DST_DST1GTRCluster> &clusters = gtr.Clusters();
//	std::cout << " clusters size  = "  << clusters.size() << std::endl;
	
	int nclusterx[10][3] = {0};	
	int nclustery[10][3] = {0};	
	int nclusteryb[10][3] = {0};	
	int nclusterx_modall[3] = {0};	
	int nclustery_modall[3] = {0};	
	int nclusteryb_modall[3] = {0};	


   int sum_nhits_x[10][3] = {};
   int sum_ncluster_x[10][3] = {};
   int sum_ncluster_y[10][3] = {};
   int sum_ncluster_xdependence[10][3][12] = {};
   int sum_ncluster_ydependence[10][3][12] = {};

	for(int i=0; i < hits.size(); i++){
		E16DST_DST1GTRHit &h = hits[i];
      sum_nhits_x[h.ModuleId()-100][h.LayerId()]++;//to count multiplicty
		if(h.Type() == 0){
			h_hit_timing_x[h.ModuleId() -100 ][h.LayerId()]->Fill(h.Timing());
			h_hit_ph_x[h.ModuleId() -100 ][h.LayerId()]->Fill(h.PeakHeight());
		}
		else if (h.Type() == 1){
			h_hit_ph_y[h.ModuleId() -100 ][h.LayerId()]->Fill(h.PeakHeight());
		}
		else if (h.Type() == 2){
			h_hit_ph_y[h.ModuleId() -100 ][h.LayerId()]->Fill(h.PeakHeight());
		}
	}
   
   for(int m=0;m < 10; m++){
      for(int l=0; l < 3; l++){
//   		h_hit_multiplicity_x[m][l] ->Fill(sum_nhits_x[m][l]);
		}
	}

    for(int i=0; i < clusters.size(); i++){
        E16DST_DST1GTRCluster &cl = clusters[i];
        
        

        if(cl.Type() == 0){//x axis
// for multiplicity calculation 
		  		double lx = cl.LocalX();
	 		   double offset = 50 * (cl.LayerId()+1);
        		int nth_xdiv = (lx + offset) /( ((cl.LayerId()+1) * 100) / n_xdiv) ;
        		sum_ncluster_xdependence[cl.ModuleId()-100][cl.LayerId()][nth_xdiv]++;//to count multiplicty
// --- 
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
            sum_ncluster_x[cl.ModuleId()-100][cl.LayerId()]++;//to count multiplicty
			
		}
        else if(cl.Type() == 1){ // yaxis
// -- 
				double ly = cl.LocalX();
				double offset = 50 * (cl.LayerId() + 1);
				int nth_ydiv = (ly + offset) / (((cl.LayerId() + 1) * 100) / n_ydiv);
        		sum_ncluster_ydependence[cl.ModuleId()-100][cl.LayerId()][nth_ydiv]++;//to count multiplicty


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
            sum_ncluster_y[cl.ModuleId()-100][cl.LayerId()]++;//to count multiplicty
        }
        else if(cl.Type() == 2){
				double ly = cl.LocalX();
				double offset = 50 * (cl.LayerId() + 1);
				int nth_ydiv = (ly + offset) / (((cl.LayerId() + 1) * 100) / n_ydiv);
        		sum_ncluster_ydependence[cl.ModuleId()-100][cl.LayerId()][nth_ydiv]++;//to count multiplicty
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
            sum_ncluster_y[cl.ModuleId()-100][cl.LayerId()]++;//to count multiplicty
        }
    }//n cluster loop


    double gtr_timing_window = 40;

    for(const auto& gtr100_module_id : E16ANA_TrackConstant::kModuleIDs){
    	auto& gtr100x_cluster_ptrs  = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsX);
	   auto& gtr100y_cluster_ptrs  = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsY);
	   auto& gtr100yb_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsYb);
      for(const auto& gtr100x_cluster:gtr100x_cluster_ptrs){
		   double lx = gtr100x_cluster->LocalX();
			double tx = gtr100x_cluster->Timing();
      	for(const auto& gtr100y_cluster:gtr100y_cluster_ptrs){
				if(lx < 0){
					double ty = gtr100y_cluster->Timing();
					if(fabs(tx - ty ) < gtr_timing_window){
						h_hit_map[gtr100_module_id-100][0]->Fill(gtr100x_cluster->LocalX(), gtr100y_cluster->LocalX());
         		}
				}
      	}
	      for(const auto& gtr100yb_cluster:gtr100yb_cluster_ptrs){
				if(lx > 0){
					double ty = gtr100yb_cluster->Timing();
					if(fabs(tx - ty ) < gtr_timing_window){
						h_hit_map[gtr100_module_id-100][0]->Fill(gtr100x_cluster->LocalX(), gtr100yb_cluster->LocalX());
         		}
				}
      	}

      }
   }
    for(const auto& gtr200_module_id : E16ANA_TrackConstant::kModuleIDs){
    	auto& gtr200x_cluster_ptrs  = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsX);
	   auto& gtr200y_cluster_ptrs  = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsY);
      for(const auto& gtr200x_cluster:gtr200x_cluster_ptrs){
		   double lx = gtr200x_cluster->LocalX();
			double tx = gtr200x_cluster->Timing();
      	for(const auto& gtr200y_cluster:gtr200y_cluster_ptrs){
					double ty = gtr200y_cluster->Timing();
					if(fabs(tx - ty ) < gtr_timing_window){
						h_hit_map[gtr200_module_id-100][1]->Fill(gtr200x_cluster->LocalX(), gtr200y_cluster->LocalX());
				}
      	}
      }
   }

   for(const auto& gtr300_module_id : E16ANA_TrackConstant::kModuleIDs){
    	auto& gtr300x_cluster_ptrs  = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsX);
	   auto& gtr300y_cluster_ptrs  = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsY);
      for(const auto& gtr300x_cluster:gtr300x_cluster_ptrs){
		   double lx = gtr300x_cluster->LocalX();
			double tx = gtr300x_cluster->Timing();
      	for(const auto& gtr300y_cluster:gtr300y_cluster_ptrs){
					double ty = gtr300y_cluster->Timing();
					if(fabs(tx - ty ) < gtr_timing_window){
						h_hit_map[gtr300_module_id-100][2]->Fill(gtr300x_cluster->LocalX(), gtr300y_cluster->LocalX());
				}
      	}
      }
   }




    for(int i=0;i<10;i++){
      for(int j=0;j<3;j++){
         h_cluster_multiplicity_x[i][j]->Fill(sum_ncluster_x[i][j]);
			h_cl_ncluster_x[i][j]->Fill(nclusterx[i][j]);
			h_cl_ncluster_y[i][j]->Fill(nclustery[i][j]);
			h_cl_ncluster_yb[i][j]->Fill(nclusteryb[i][j]);
         for(int nx=0 ; nx < n_xdiv; nx++){
				h_cluster_multiplicity_xdependence[i][j][nx]->Fill(sum_ncluster_xdependence[i][j][nx]);
				h_cluster_multiplicity_ydependence[i][j][nx]->Fill(sum_ncluster_ydependence[i][j][nx]);
        	}
        }
    }
    for(int i=0;i<3;i++){
      h_cl_ncluster_modall_x[i]->Fill(nclusterx_modall[i]);
      h_cl_ncluster_modall_y[i]->Fill(nclustery_modall[i]);
      h_cl_ncluster_modall_yb[i]->Fill(nclusteryb_modall[i]);
    }
	clusters.clear();
	hits.clear();

}

void GTRCheckHist::Fill(std::vector<std::shared_ptr<E16DST_DST1StraightTrack3D>> st_tracks){
	for(int i=0; i<st_tracks.size();i++){	
		auto trk = st_tracks[i];
		h_tgt_z[trk->ModuleID()- 100]->Fill(trk->TgtPosZ());
	}	
}
