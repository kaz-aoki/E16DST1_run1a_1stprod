#define EfficiencyCalc_cxx
#include "EfficiencyCalc.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


void EfficiencyCalc::SelectTracks(){
//	std::array<std::vector<int>, track_const::kNumTrackingLayers> used_cluster_ids;
	//matched_lghit_ids.resize(n_tracks);
	//matched_lghit_ids.clear();
	for(int i = 0; i < n_cands; i++){
		//if(isTimingMatchSSDAndLg(i, matched_lghit_ids[i])){
			//SelectTrack(i, &used_cluster_ids);
		//}
	}
}

void EfficiencyCalc::CalculateResidual(){
	for(int i = 0 ; i < n_cands; i++){
		for(int k=0; k < n_gtr100x_clusters; k++){
			if(gtr100x_cluster_adc->at(k)>50e3) continue;//remove fake hit
			if(gtr100x_cluster_size->at(k) < 2) continue;
			if(rk_fit_gtr100_mid->at(i) == gtr100x_cluster_mid->at(k) && rk_charge->at(i) == 1){ 
				///double resx = sqrt(pow(gtr100x_cluster_gx->at(k) - rk_fit_gtr100_gx->at(i), 2) + pow(gtr100x_cluster_gz->at(k) - rk_fit_gtr100_gz->at(i), 2));
				double resx = gtr100x_cluster_gx->at(k) - rk_fit_gtr100_gx->at(i);
				detector_res_x[rk_fit_gtr100_mid->at(i) - 100][1][1] = resx;
			}
		}
	}
	out_tree->Fill();

}

void EfficiencyCalc::Calculate()
{

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if(jentry == maxevent) break;
	  if(jentry % 1000  == 0 ) {
		  std::cout << jentry << "/" << nentries << std::endl;
	  }
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      SelectTracks();
	  CalculateResidual();//temporally gtr100
   }
   out_tree->Write();
}
