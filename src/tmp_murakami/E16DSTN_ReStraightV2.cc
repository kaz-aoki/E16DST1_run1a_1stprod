#define E16DSTN_ReStraightV2_cxx
#include "E16DSTN_ReStraightV2.hh"
#include "E16ANA_StraightTrackParameter.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


using namespace E16ANA_StraightTrackParameter;
using namespace E16ANA_StraightTrackConstant;


void E16DSTN_ReStraightV2::ChiSqSort( std::vector<int> &sorted_ids){
	int n_chisq  = chi_square->size();
	int n_tracks = n_cands;
	if(n_tracks != n_cands) {
		std::cerr << "It is a bug ! : Unexpected behavior was detected." << std::endl;
		exit(1);
	} 
	std::multimap<double, int> chi2_trkid_map;
	chi2_trkid_map.clear();
 for(int i=0; i < n_tracks; i++){
 	chi2_trkid_map.insert(std::make_pair(chi_square->at(i), i));
 }
	for(const auto &el : chi2_trkid_map){
		sorted_ids.push_back(el.second);
	}
}

void E16DSTN_ReStraightV2::SelectTracks(std::vector<int> &sorted_ids, std::vector<int> &selected_ids){
	for(int i=0; i < n_cands; i++){
//		if(IsRealTrack(i)){
			if(IsGoodTrack(i)){
				selected_ids.emplace_back(i);
			}
//		}
	}
}

bool E16DSTN_ReStraightV2::IsGoodTrack(const int id){
	return true;
}

bool E16DSTN_ReStraightV2::IsRealTrack(const int id){
	bool flag = true;
   double adcs_x[3] = {rk_hit_gtr100_xadc->at(id), rk_hit_gtr200_xadc->at(id), rk_hit_gtr300_xadc->at(id)};
   double adcs_y[3] = {rk_hit_gtr100_yadc->at(id), rk_hit_gtr200_yadc->at(id), rk_hit_gtr300_yadc->at(id)};
	for(int i=0; i < 3; i++){
		if(adcs_x[i] == 99999) {
			flag = false;
		}
		if(adcs_y[i] == 99999) {
			flag = false;
		}
	}
	return flag;
}


void E16DSTN_ReStraightV2::DuplicationClusterCut(std::vector<int> &selected_ids, std::vector<int> &killdup_ids){
	int n_selected_ids = selected_ids.size();

#ifdef REMOVE_NOLAYER // all layer exist
	for(int i=0; i < n_selected_ids ; i++){
			std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips> cids = {
			rk_hit_sts_id->at(i),
			rk_hit_gtr100_xid->at(i), rk_hit_gtr100_yid->at(i),
			rk_hit_gtr200_xid->at(i), rk_hit_gtr200_yid->at(i),
			rk_hit_gtr300_xid->at(i), rk_hit_gtr300_yid->at(i)};
 			std::cout << "ids (" << rk_hit_sts_id->at(i)   
			 << ", " << rk_hit_gtr100_xid->at(i) 
			 << ", " << rk_hit_gtr200_xid->at(i) 
			 << ", " << rk_hit_gtr300_xid->at(i) 
			 << ", " << rk_hit_gtr100_yid->at(i) 
			 << ", " << rk_hit_gtr200_yid->at(i) 
			 << ", " << rk_hit_gtr300_yid->at(i) << std::endl;
         if(HasUsedCluster(cids, used_cluster_ids)){
//			std::cout << "duplicated !" << std::endl;
			continue;			
			} else {
//				std::cout << "NOT duplicated !" << std::endl;
				for (int j=0; j  <  E16ANA_StraightTrackConstant::kNumTrackingStrips;j++){
					used_cluster_ids[j].emplace_back(cids[j]);
				}
			killdup_ids.emplace_back(i);
			}
    }
#else//
	#ifdef No_Exist_SSD
	 for(int i=0; i < n_selected_ids ; i++){
			std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips -1 > cids = {
			rk_hit_gtr100_xid->at(i), rk_hit_gtr100_yid->at(i),
			rk_hit_gtr200_xid->at(i), rk_hit_gtr200_yid->at(i),
			rk_hit_gtr300_xid->at(i), rk_hit_gtr300_yid->at(i)};
         if(HasUsedCluster(cids, used_cluster_ids)){
				continue;			
			} else {
				for (int j=0; j  <  E16ANA_StraightTrackConstant::kNumTrackingStrips-1;j++){
					used_cluster_ids[j].emplace_back(cids[j]);
				}
			killdup_ids.emplace_back(i);
			}
    }
    #elif REMOVE_GTR100
    for(int i=0; i < n_selected_ids ; i++){
			std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips -2 > cids = {
			rk_hit_sts_id->at(i),
			rk_hit_gtr200_xid->at(i), rk_hit_gtr200_yid->at(i),
			rk_hit_gtr300_xid->at(i), rk_hit_gtr300_yid->at(i)};
         if(HasUsedCluster(cids, used_cluster_ids)){
				continue;			
			} else {
				for (int j=0; j  <  E16ANA_StraightTrackConstant::kNumTrackingStrips-2;j++){
					used_cluster_ids[j].emplace_back(cids[j]);
				}
			killdup_ids.emplace_back(i);
			}
    }
    #elif REMOVE_GTR200
    for(int i=0; i < n_selected_ids ; i++){
			std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips -2 > cids = {
			rk_hit_sts_id->at(i),
			rk_hit_gtr100_xid->at(i), rk_hit_gtr100_yid->at(i),
			rk_hit_gtr300_xid->at(i), rk_hit_gtr300_yid->at(i)};
// 			std::cout << "ids (" << rk_hit_sts_id->at(i)   
//			 << ", " << rk_hit_gtr100_xid->at(i) 
//			 << ", " << rk_hit_gtr300_xid->at(i) 
//			 << ", " << rk_hit_gtr100_yid->at(i) 
//			 << ", " << rk_hit_gtr300_yid->at(i) << std::endl;
         if(HasUsedCluster(cids, used_cluster_ids)){
				continue;			
			} else {
				for (int j=0; j  <  E16ANA_StraightTrackConstant::kNumTrackingStrips-2;j++){
					used_cluster_ids[j].emplace_back(cids[j]);
				}
			killdup_ids.emplace_back(i);
			}
    }
     #elif REMOVE_GTR300
    for(int i=0; i < n_selected_ids ; i++){
			std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips -2 > cids = {
			rk_hit_sts_id->at(i),
			rk_hit_gtr100_xid->at(i), rk_hit_gtr100_yid->at(i),
			rk_hit_gtr200_xid->at(i), rk_hit_gtr200_yid->at(i)};
         if(HasUsedCluster(cids, used_cluster_ids)){
				continue;			
			} else {
				for (int j=0; j  <  E16ANA_StraightTrackConstant::kNumTrackingStrips-2;j++){
					used_cluster_ids[j].emplace_back(cids[j]);
				}
			killdup_ids.emplace_back(i);
			}
    }
#endif // 
#endif //
}



void E16DSTN_ReStraightV2::Loop(TTree* tree, int print_cycle, int max_event, bool vertex_xy_fix_flag, bool py_fix_flag, bool vetex_z_fix_flag ,int  anaSW)
{
   if (fChain == 0) return;
   Long64_t nevent = fChain->GetEntries();
   std::cout << "nevent = " << nevent << std::endl;
   Long64_t nbytes = 0, nb = 0;
   for(int n=0; n < nevent ; n++){
		if(max_event != -1 &&  n > max_event){
			std::cout << "N event analyzed readched to max event " << std::endl;
		   break;	
      }
      if( n% print_cycle == 0 ){
         printf( "N analyzed = %d \n ", n);
      }
      tree->GetEntry(n);
      std::vector<int> out_ids;
      std::vector<int> sorted_ids;
      std::vector<int> selected_ids;
      std::vector<int> killdup_ids;
      out_ids.clear();
		sorted_ids.clear();
		selected_ids.clear();
		killdup_ids.clear();
//      std::cout << "n_cands = " << n_cands << std::endl;
		ChiSqSort(sorted_ids);
		SelectTracks(sorted_ids, selected_ids);
//	   std::cout << "n of selected tracks = " << selected_ids.size() << std::endl;
		ClearUsedClusterIDs();
		DuplicationClusterCut(selected_ids, killdup_ids);
//	   std::cout << "n of duplication cut tracks = " << killdup_ids.size() << std::endl;
		AnalyzeTrackPairs(killdup_ids);
	 	AddRecord(tree,  killdup_ids);
   }
}

//void SearchLGAssociationHit(std::vector<int> &in_ids){
////rough selection
//	projected_lg_hits.clear();
//	for(int i=0; i < in_ids.size(); i++){
//		int tid = in_ids[i];
//		double mplgy = rk_fit_lg_b_gy->at(tid);
//		double plgx  = rk_fit_lg_b_x->at(tid);
//		if(fabs(mplgy) > 260){
//			plgx = rk_fit_lg_c_x->at(tid);
//		}
//		if(fabs(mplgy) < 150){
//			plgx = rk_fit_lg_a_x->at(tid);
//		}
//		double lg_near = -9999;
//		double mind =9999;
//		int nlg = 0;
//		PeojectedLGHits plg;
//		for(int k=0; k < n_lg_hits;k++){
//			if(lgf_hit_mid->at(k) == rk_fit_lg_b_mid->at(tid)){
//				if(lg_hit_adc->at(k) < 10) continue;
////				if(fabs(lg_hit_x->at(k) - 310) < 1 && fabs(lg_hit_y->at(k) + 315) < 1) continue; 
//				double dx = lg_hit_x->at(k) - plgx;
//				double dy = lg_hit_gy->at(k) - mplgy;
//				plg.res_x = dx;
//				plg.res_y = dy;
//				projected_lg_hits.emplace_back(plg);
//			}
//		}
//	}
//}


bool E16DSTN_ReStraightV2::IsSameTarget(const int tid0, const int tid1){
	return true;	
}

bool E16DSTN_ReStraightV2::IsLRTrack(const int tid0, const int tid1){
	bool flag = false;
#ifndef REMOVE_GTR100
	int mid0 = rk_fit_gtr100_mid->at(tid0);
	int mid1 = rk_fit_gtr100_mid->at(tid1);
#else
	int mid0 = rk_fit_gtr200_mid->at(tid0);
	int mid1 = rk_fit_gtr200_mid->at(tid1);
#endif
	if(mid0 < 105) {//L
		if(mid1 > 105 && mid1 < 200){
			flag = true;
		}
	}
	if(mid0 > 105 && mid0 < 200) {
		if(mid1 < 105 ){
			flag = true;
		}
	}
	return flag;
}


double E16DSTN_ReStraightV2::SearchVertex(TrackPair *track_pair){
	int tid0 = track_pair->tid0;
	int tid1 = track_pair->tid1;
	Hep3Vector init_pos0 (rk_fit_init_pos_gx->at(tid0) * 0.1, rk_fit_init_pos_gy->at(tid0) * 0.1, rk_fit_init_pos_gz->at(tid0) * 0.1);
	Hep3Vector init_mom0 (rk_fit_init_mom_gx->at(tid0) , rk_fit_init_mom_gy->at(tid0) , rk_fit_init_mom_gz->at(tid0) );
	Hep3Vector init_pos1 (rk_fit_init_pos_gx->at(tid1) * 0.1, rk_fit_init_pos_gy->at(tid1) * 0.1, rk_fit_init_pos_gz->at(tid1) * 0.1);
	Hep3Vector init_mom1 (rk_fit_init_mom_gx->at(tid1) , rk_fit_init_mom_gy->at(tid1) , rk_fit_init_mom_gz->at(tid1) );
//	std::cout << "init pos  = " << init_pos0.x() << ", " << init_pos0.y() << " ," << init_pos0.z() << std::endl;
//	std::cout << "init pos  = " << init_pos1.x() << ", " << init_pos1.y() << " ," << init_pos1.z() << std::endl;
	E16ANA_StraightStepTrack step_track0(init_pos0, init_mom0, -1,  0.1, 1000);
	E16ANA_StraightStepTrack step_track1(init_pos1, init_mom1,  1,  0.1, 1000);
	double distance;
	Hep3Vector cross_point;
	Hep3Vector mom0;
	Hep3Vector mom1;
	auto flag = step_track0.Cross(step_track1, &distance, &cross_point, &mom0, &mom1);
	track_pair->vtx = {cross_point.x() * 10, cross_point.y() * 10, cross_point.z() *10.};
//	std::cout << "vertex  = " << track_pair->vtx.x() << ", " << track_pair->vtx.y() << " ," << track_pair->vtx.z() << std::endl;
	track_pair->distance = distance *10.;
	track_pair->mom_minus = {mom0.x(), mom0.y(), mom0.z()};
	track_pair->mom_plus  = {mom1.x(), mom1.y(), mom1.z()};
	return distance * 10;
}

void E16DSTN_ReStraightV2::AnalyzeTrackPairs(std::vector<int> &in_ids){
	track_pairs.clear();
	TrackPair track_pair;
	track_pair.Clear();
	int n_cands = in_ids.size();
	for(int i = 0; i < n_cands -1 ; i++){
		int tid0 = in_ids[i]; //track id 0
		for(int j = i + 1; j < n_cands; j++){
			int tid1 = in_ids[j];//track id 1
//			std::cout << "tid 0 1 = "  << tid0 << ", " << tid1 << std::endl;
//			if(IsSameTarget(tid0, tid1)){
				if(IsLRTrack(tid0, tid1)){
//					if(rk_fit_gtr100_mid->at(tid0) == rk_fit_gtr100_mid->at(tid1)) continue;
					track_pair.tid0 = tid0;
					track_pair.tid1 = tid1;
					SearchVertex(&track_pair);	
//					PairTracking(&track_pair);
					track_pairs.emplace_back(track_pair);
				}
//			}	
		}
	}
	SelectTrackPairs();
	return;
}

void E16DSTN_ReStraightV2::PairTracking(TrackPair *track_pair){
	AddTracks(track_pair);
	pair_fitter->SetRungeKuttaStepSize(kPairTrackingStepSize);
	pair_fitter->SetMaxSteps(kPairTrackingMaxSteps);
	track_pair->chi_square_refit = pair_fitter->Fit(vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag, kPairMinuitStrategy, kPairMinuitMaxFunctionCalls);
	UpdateFitResult(track_pair);
}

void E16DSTN_ReStraightV2::UpdateFitResult(TrackPair *track_pair){
	track_pair->vtx_refit = pair_fitter->GetFitVertex();
	track_pair->mom_minus_refit = pair_fitter->GetFitMomentum(0);
	track_pair->mom_plus_refit  = pair_fitter->GetFitMomentum(1);
	for (int track_index = 0; track_index < 2; ++track_index) {
	   for (int layer_index = 0; layer_index < E16ANA_TrackConstant::kNumTrackingLayers; ++layer_index) {
	      #ifdef NoExist_SSD
	      if(layer_index == 0 ) continue;
	      #endif
	      std::vector<int> mid;
	      std::vector<TVector3> lpos;
	      std::vector<TVector3> lmom;
	      std::vector<TVector3> lres;
	      pair_fitter->GetFitLPos(track_index, layer_index, mid, lpos);
	      pair_fitter->GetFitLMom(track_index, layer_index, mid, lmom);
	      pair_fitter->GetFitResidual(track_index, layer_index, mid, lres);
	      int hid = 0;//hit ID
	      if (layer_index == E16ANA_TrackConstant::kSSD) {
	         if(track_index == 0){
	            track_pair->track_minus_pos_refit[layer_index] = geometry->SSD(mid[hid])->GetGPos(lpos[hid]);
	            track_pair->track_minus_mom_refit[layer_index] = geometry->SSD(mid[hid])->GetGMom(lmom[hid]);
	            track_pair->track_minus_res_refit[layer_index] = lres[hid];
	         } else {
	            track_pair->track_plus_pos_refit[layer_index] = geometry->SSD(mid[hid])->GetGPos(lpos[hid]);
	            track_pair->track_plus_mom_refit[layer_index] = geometry->SSD(mid[hid])->GetGMom(lmom[hid]);
	            track_pair->track_plus_res_refit[layer_index] = lres[hid];
	         }
	      } else {
	         if(track_index == 0){
	         track_pair->track_minus_pos_refit[layer_index] = geometry->GTR(mid[hid], layer_index - 1)->GetGPos(lpos[hid]);
	         track_pair->track_minus_mom_refit[layer_index] = geometry->GTR(mid[hid], layer_index - 1)->GetGMom(lmom[hid]);
	         track_pair->track_minus_res_refit[layer_index] = lres[hid];
	         } else {
	         track_pair->track_plus_pos_refit[layer_index] = geometry->GTR(mid[hid], layer_index - 1)->GetGPos(lpos[hid]);
	         track_pair->track_plus_mom_refit[layer_index] = geometry->GTR(mid[hid], layer_index - 1) ->GetGMom(lmom[hid]);
	         track_pair->track_plus_res_refit[layer_index] = lres[hid];
	         }
	      }
	   }
	}
	track_pair->is_refit = true;
	return;
}

void E16DSTN_ReStraightV2::SelectTrackPairs(){
	selected_track_pairs.clear();
	std::vector<int> used_tids;
	used_tids.clear();
	std::sort(track_pairs.begin(), track_pairs.end(), [](auto& lhs, auto& rhs) {
       return lhs.chi_square_refit < rhs.chi_square_refit;
    });
    for(auto &pair : track_pairs){
       bool is_used = false;
       for(auto &used_tid : used_tids) {
          if(used_tid == pair.tid0){
             is_used = true;
             break;
          }
       }
       if(!is_used) {
          for(auto &used_tid: used_tids){
             if(used_tid = pair.tid1){
                is_used = true;
                break;
             }
          }
       }
       if (is_used){
          continue;
       }
       pair.is_selected = true;
       selected_track_pairs.emplace_back(&pair);
       used_tids.emplace_back(pair.tid0);
       used_tids.emplace_back(pair.tid1);
    }
    return;
}



void E16DSTN_ReStraightV2::AddTracks(TrackPair *track_pair){
	pair_fitter->Clear();
	pair_fitter->SetInitialVertex(track_pair->vtx, kVertexSigma);
	pair_fitter->SetInitialMomentum(0, track_pair->mom_minus);
	pair_fitter->SetInitialMomentum(1, track_pair->mom_plus);
	int tid0 = track_pair->tid0;
	int tid1 = track_pair->tid1;
	int tids[2] = {tid0, tid1};

	std::array<int, E16ANA_StraightTrackConstant::kNumTrackingLayers> mids[2];
	std::array<TVector3, E16ANA_StraightTrackConstant::kNumTrackingLayers> local_poss[2];
	mids[0] =  { rk_fit_sts_mid->at(tid0), rk_fit_gtr100_mid->at(tid0), rk_fit_gtr200_mid->at(tid0), rk_fit_gtr300_mid->at(tid0)};
	mids[1] =  { rk_fit_sts_mid->at(tid1), rk_fit_gtr100_mid->at(tid1), rk_fit_gtr200_mid->at(tid1), rk_fit_gtr300_mid->at(tid1)};
	local_poss[0] = {	TVector3(rk_hit_sts_x->at(tid0), 0, 0), 
							TVector3(rk_hit_gtr100_xt->at(tid0), rk_hit_gtr100_ty->at(tid0), 0), 
							TVector3(rk_hit_gtr200_xt->at(tid0), rk_hit_gtr200_ty->at(tid0), 0), 
							TVector3(rk_hit_gtr300_xt->at(tid0), rk_hit_gtr300_ty->at(tid0), 0)}; 
	local_poss[1] = {	TVector3(rk_hit_sts_x->at(tid1)    , 0                        , 0), 
							TVector3(rk_hit_gtr100_xt->at(tid1), rk_hit_gtr100_ty->at(tid1), 0), 
							TVector3(rk_hit_gtr200_xt->at(tid1), rk_hit_gtr200_ty->at(tid1), 0), 
							TVector3(rk_hit_gtr300_xt->at(tid1), rk_hit_gtr300_ty->at(tid1), 0)}; 	

	for(int track_index=0; track_index < 2; track_index++){
		for(int l=0; l < E16ANA_StraightTrackConstant::kNumTrackingLayers; l++){
			#ifdef NoExist_SSD
			if(l == 0) continue;
			#endif
			if(l == E16ANA_TrackConstant::kSSD){
				#ifdef UseSTS
				pair_fitter->AddHit(tids[track_index], l, geometry->STS(E16ANA_StraightTrackConstant::ModuleID2020To2013(mids[track_index][l])),      local_poss[track_index][l], kSigmas[l]);
				#else
				pair_fitter->AddHit(tids[track_index], l, geometry->SSD(E16ANA_StraightTrackConstant::ModuleID2020To2013(mids[track_index][l])),  local_poss[track_index][l], kSigmas[l]);
				#endif
			}
			else {
				pair_fitter->AddHit(tids[track_index], l, geometry->GTR(E16ANA_StraightTrackConstant::ModuleID2020To2013(mids[track_index][l]),  l-1), local_poss[track_index][l], kSigmas[l]);
			}
		}
	}
	return;
}


//void E16DSTN_ReStraightV2::Loop(TTree* tree, int print_cycle, int max_event, bool vertex_xy_fix_flag, bool py_fix_flag, bool vetex_z_fix_flag ,int  anaSW)
//{
//   if (fChain == 0) return;
//
//   Long64_t nevent = fChain->GetEntries();
//   std::cout << "nevent = " << nevent << std::endl;
//   Long64_t nbytes = 0, nb = 0;
//
//   for(int n=0; n < nevent ; n++){
//		if(max_event != -1 &&  n > max_event){
//			std::cout << "N event analyzed readched to max event " << std::endl;
//		   break;	
//      }
//      if( n% print_cycle == 0 ){
//         printf( "N analyzed = %d \n ", n);
//      }
//      tree->GetEntry(n);
//		ClearUsedClusterIDs();
//      std::vector<int> out_ids;
//      out_ids.clear();
//#ifndef NoExist_SSD
//	for(int i=0; i < n_cands ; i++){
//			std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips> cids = {
//			rk_hit_sts_id->at(i),
//			rk_hit_gtr100_xid->at(i), rk_hit_gtr100_yid->at(i),
//			rk_hit_gtr200_xid->at(i), rk_hit_gtr200_yid->at(i),
//			rk_hit_gtr300_xid->at(i), rk_hit_gtr300_yid->at(i)};
//         if(HasUsedCluster(cids)){
//				continue;			
//			} else {
//				for (int j=0; j  <  E16ANA_StraightTrackConstant::kNumTrackingStrips;j++){
//					used_cluster_ids[j].emplace_back(cids[j]);
//				}
//			out_ids.emplace_back(i);
//			}
//    }
//#else//NoExist_SSD
//    #ifdef REMOVE_100
//    for(int i=0; i < n_cands ; i++){
//			std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips -2 > cids = {
//			rk_hit_sts_id->at(i),
//			rk_hit_gtr200_xid->at(i), rk_hit_gtr200_yid->at(i),
//			rk_hit_gtr300_xid->at(i), rk_hit_gtr300_yid->at(i)};
//         if(HasUsedCluster(cids)){
//				continue;			
//			} else {
//				for (int j=0; j  <  E16ANA_StraightTrackConstant::kNumTrackingStrips-2;j++){
//					used_cluster_ids[j].emplace_back(cids[j]);
//				}
//			out_ids.emplace_back(i);
//			}
//    }
//    #elif REMOVE_200
//    for(int i=0; i < n_cands ; i++){
//			std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips -2 > cids = {
//			rk_hit_sts_id->at(i),
//			rk_hit_gtr100_xid->at(i), rk_hit_gtr100_yid->at(i),
//			rk_hit_gtr300_xid->at(i), rk_hit_gtr300_yid->at(i)};
//         if(HasUsedCluster(cids)){
//				continue;			
//			} else {
//				for (int j=0; j  <  E16ANA_StraightTrackConstant::kNumTrackingStrips-2;j++){
//					used_cluster_ids[j].emplace_back(cids[j]);
//				}
//			out_ids.emplace_back(i);
//			}
//    }
//     #elif REMOVE_300
//    for(int i=0; i < n_cands ; i++){
//			std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips -2 > cids = {
//			rk_hit_sts_id->at(i),
//			rk_hit_gtr100_xid->at(i), rk_hit_gtr100_yid->at(i),
//			rk_hit_gtr200_xid->at(i), rk_hit_gtr200_yid->at(i)};
//         if(HasUsedCluster(cids)){
//				continue;			
//			} else {
//				for (int j=0; j  <  E16ANA_StraightTrackConstant::kNumTrackingStrips-2;j++){
//					used_cluster_ids[j].emplace_back(cids[j]);
//				}
//			out_ids.emplace_back(i);
//			}
//    }
//    #else
//	 for(int i=0; i < n_cands ; i++){
//			std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips -1 > cids = {
//			rk_hit_gtr100_xid->at(i), rk_hit_gtr100_yid->at(i),
//			rk_hit_gtr200_xid->at(i), rk_hit_gtr200_yid->at(i),
//			rk_hit_gtr300_xid->at(i), rk_hit_gtr300_yid->at(i)};
//         if(HasUsedCluster(cids)){
//				continue;			
//			} else {
//				for (int j=0; j  <  E16ANA_StraightTrackConstant::kNumTrackingStrips-1;j++){
//					used_cluster_ids[j].emplace_back(cids[j]);
//				}
//			out_ids.emplace_back(i);
//			}
//    }
//#endif // REMOVE_GTRxxx
//#endif // NoExist_SSD
//	 AddRecord(out_ids);
//   }
//}
//
//

void E16DSTN_ReStraightV2::ClearUsedClusterIDs() {
	for(auto &ids : used_cluster_ids){
		ids.clear();
	}
	return;
}



//void E16DSTN_ReStraightV2::SetTracks(std::vector<int> &invec,std::vector<int> &outids){
////	good_ids.clear();
//	for(int i=0; i < invec.size(); i++){
//		int tid = invec[i];
////		if(kUseChi2Cut && chi_square->at(tid) > kMaxChi2){
////			break;
////		}
//		if(IsGoodTrack(tid)){
////			good_ids.emplace_back(i);
// 			outids.emplace_back(i);
//		}
//	}
//}

bool E16DSTN_ReStraightV2::HasUsedCluster(const array<int, kNumTrackingStrips- 2> &cids,std::array<std::vector<int>, E16ANA_StraightTrackConstant::kNumTrackingStrips-2> &used_cluster_ids ){
	for (int i = 0; i < kNumTrackingStrips-2; ++i) {
		for(const auto& used_id : used_cluster_ids[i]){
     		if(cids[i] == used_id){
       		return true;
     		}
   	}
	}
	return false;
}


bool E16DSTN_ReStraightV2::HasUsedCluster(const array<int, kNumTrackingStrips> &cids,std::array<std::vector<int>, E16ANA_StraightTrackConstant::kNumTrackingStrips> &used_cluster_ids ){//all layer tracking
	for (int i = 0; i < kNumTrackingStrips; ++i) {
		for(const auto& used_id : used_cluster_ids[i]){
	     if(cids[i] == used_id){
	       return true;
	     }
	   }
	  }
	return false;
}




void E16DSTN_ReStraightV2::DrawHist(TTree* tree, int n_maxevent, int print_cycle, const int residual_layer,  TString pdf_name){	

   const int n_module = 10;
   const int n_layer = 4;
   const int n_tgt = 3; 
   const int n_div = 8;

	int nevent = tree->GetEntries();

   std::cout << "nevent : " << nevent << std::endl;
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
	TH1D* h_res_x[n_module][n_layer];
	TH1D* h_res_y[n_module][n_layer];
	TH1D* h_res_vtx_trk_x[n_module][n_layer];
	TH1D* h_res_vtx_trk_y[n_module][n_layer];
	TH1D* h_tan_theta[n_module][n_layer];
	TH1D* h_fitlx[n_tgt][n_module][n_layer];
   
   TH1D* h_cluster_timing_raw[n_module][n_layer];
   TH1D* h_cluster_timing_chi2[n_module][n_layer];
   TH1D* h_cluster_timing_chi2_xdependence[n_module][n_layer][n_div];
   TH1D* h_cluster_timing_chi2_ydependence[n_module][n_layer][n_div];
   
	TH1D* h_tot_end_fr[n_module][n_layer];	
	TH1D* h_tot_end_bg[n_module][n_layer];	



	TH1D* h_cluster_adc_xdependence[n_module][n_layer][n_div];
	TH1D* h_cluster_adc_ydependence[n_module][n_layer][n_div];
	TH2D* h_init_pos;
	TH2D* h_tgt_pos_mod_raw[n_module];
	TH2D* h_tgt_pos_mod_cut[n_module];
	TH2D* h_cor_dz_time[n_module][n_layer];
	TH2D* h_cor_dz_time_t0cor[n_module][n_layer];
	TH2D* h_cor_res_fitlx[n_module][n_layer];
	TH2D* h_cor_res_fitly[n_module][n_layer];
	TH2D* h_cor_res_timing[n_module][n_layer];
	
	TH2D* h_slopevel[n_module][n_layer][n_div];
	TH1D* h_res_lg_x[n_module];
	TH1D* h_res_lg_y[n_module];
	TH1D* h_res_vtx_trk_lg_x[n_module];
	TH1D* h_res_vtx_trk_lg_y[n_module];
	TH1D* h_bak_res_lg_x[n_module];
	TH1D* h_bak_res_lg_y[n_module];
	TH1D* h_bak_res_vtx_trk_lg_x[n_module];
	TH1D* h_bak_res_vtx_trk_lg_y[n_module];

//pair
	TH1D* h_vtx_gx;
	TH1D* h_vtx_gy;
	TH1D* h_vtx_gz;
	TH2D* h_vtx_gx_gz;	
	TH2D* h_vtx_gx_gy;	
   h_vtx_gx = new TH1D("h_vtx_gx", "h_vtx_gx", 80, -20, 20);
   h_vtx_gy = new TH1D("h_vtx_gy", "h_vtx_gy", 80, -20, 20);
   h_vtx_gz = new TH1D("h_vtx_gz", "h_vtx_gz", 80, -50, 50);
  	h_vtx_gx_gz = new TH2D("h_vtx_gx_gz", "h_vtx_gx_gz", 80, -20, 20, 80, -40, 40); 
  	h_vtx_gx_gy = new TH2D("h_vtx_gx_gy", "h_vtx_gx_gy", 80, -20, 20, 80, -20, 20); 



	h_n_runid = new TH1D("n of events of runid","n of events of runid", 15, 30331.5, 30346.5);
	h_n_eventid = new TH1D("n of events of event id","n of events of eventid", 10000, -0.5, 9999.5);
	h_n_spillid = new TH1D("n of events of spill id","n of events of spillid", 1000, -0.5, 999.5);
	h_chi2    = new TH1D(Form("h_chi2"), Form("h_chi2"), 100, 0, 100);	
	h_t0diff    = new TH1D(Form("h_t0diff"), Form("h_t0diff"), 100, -100,100);	
	h_init_pos = new TH2D(Form("h_init_pos"), Form("h_init_pos"), 50, -30, 30, 50, -60, 60);

	for(int m=0; m < n_module; m++){
		for(int tg=0; tg < 2; tg++){
//			h_trackmap[tg][m] = new TH2D(Form("h_track_map%d_%d", tg,  m+100), Form("h_track_map%d_%d",tg,  m+100), 25, -50, 50, 25, -50, 50);
		}
		h_chi2_mod[m] = new TH1D(Form("h_chi2_mod%d", m+100), Form("h_chi2_mod%d", m+100), 100, 0, 100);
		h_lg_t_mod[m] = new TH1D(Form("h_lg_t_mod%d", m+100), Form("h_lg_t_mod%d", m+100), 100, 50, 150);
		h_tgt_pos_mod_raw[m] = new TH2D(Form("h_tgt_pos_mod_raw_%d", m+100), Form("h_tgt_pos_mod_raw_%d", m+100), 50, 19.8, 20.2, 60, -60, 60);
		h_tgt_pos_mod_cut[m] = new TH2D(Form("h_tgt_pos_mod_cut_%d", m+100), Form("h_tgt_pos_mod_cut_%d", m+100), 50, 19.8, 20.2, 60, -60, 60);
		h_tgt_proj_z_raw[m] = new TH1D(Form("h_tgt_proj_z_raw%d", m+100), Form("h_tgt_proj_z_raw%d", m+100), 100, -60, 60);
		h_tgt_proj_z_cut[m] = new TH1D(Form("h_tgt_proj_z_cut%d", m+100), Form("h_tgt_proj_z_cut%d", m+100), 100, -60, 60);
		h_tgt_proj_z_chi2cut[m] = new TH1D(Form("h_tgt_proj_z_chi2cut%d", m+100), Form("h_tgt_proj_z_chi2cut%d", m+100), 100, -80, 80);
		h_tgt_proj_x[m] = new TH1D(Form("h_tgt_proj_x%d", m+100), Form("h_tgt_proj_x%d", m+100), 100, 19.8, 20.2);
		h_tgt_proj_y[m] = new TH1D(Form("h_tgt_proj_y%d", m+100), Form("h_tgt_proj_y%d", m+100), 100, -5,5 );

		h_res_lg_x[m]  = new TH1D(Form("h_res_lg_x_%d", m+100), Form("h_res_lg_x_%d", m+100), 50, -400, 400 );
		h_res_lg_y[m]  = new TH1D(Form("h_res_lg_y_%d", m+100), Form("h_res_lg_y_%d", m+100), 50, -400, 400 );
		h_res_vtx_trk_lg_x[m]  = new TH1D(Form("h_res_vtx_trk_lg_x_%d", m+100), Form("h_res_vtx_trk_lg_x_%d", m+100), 50, -400, 400 );
		h_res_vtx_trk_lg_y[m]  = new TH1D(Form("h_res_vtx_trk_lg_y_%d", m+100), Form("h_res_vtx_trk_lg_y_%d", m+100), 50, -400, 400 );
		h_bak_res_vtx_trk_lg_x[m]  = new TH1D(Form("h_bak_res_vtx_trk_lg_x_%d", m+100), Form("h_bak_res_vtx_trk_lg_x_%d", m+100), 50, -400, 400 );
		h_bak_res_vtx_trk_lg_y[m]  = new TH1D(Form("h_bak_res_vtx_trk_lg_y_%d", m+100), Form("h_bak_res_vtx_trk_lg_y_%d", m+100), 50, -400, 400 );

		h_bak_res_lg_x[m]  = new TH1D(Form("h_bak_res_lg_x_%d", m+100), Form("h_bak_res_lg_x_%d", m+100), 50, -400, 400 );
		h_bak_res_lg_y[m]  = new TH1D(Form("h_bak_res_lg_y_%d", m+100), Form("h_bak_res_lg_y_%d", m+100), 50, -400, 400 );

		for(int l=0; l < n_layer; l++){// -- layer 
				h_cluster_timing_raw[m][l] = new TH1D (Form("h_cluster_timing_raw%d_%d", m+100, l), Form("h_cluster_timing_raw%d_%d", m+100, l), 100, 0 ,600 ) ;
				h_cluster_timing_chi2[m][l] = new TH1D (Form("h_cluster_timing_chi2%d_%d", m+100, l), Form("h_cluster_timing_chi2%d_%d", m+100, l), 100, 0 ,600 ) ;
				h_tot_end_fr[m][l] = new TH1D (Form("h_tot_end_fr%d_%d", m+100, l), Form("h_tot_end_fr%d_%d", m+100, l), 50, -10 ,1000 ) ;
				h_tot_end_bg[m][l] = new TH1D (Form("h_tot_end_bg%d_%d", m+100, l), Form("h_tot_end_bg%d_%d", m+100, l), 50, -10 ,1000 ) ;
//				h_slopevel[m][l][div] = new TH2D(Form("h_slopevel_%d_%d%d", m+100, l,div), Form("h_slopevel_%d%d%d", m+100, l,div),  25, -100, 100, 60, -2, 2);
				h_res_x[m][l] = new TH1D(Form("h_res_x__m%d_l%d", m+100, l), Form("h_res_x__m%d_l%d", m+100, l), 100, -2, 2);
				h_res_y[m][l] = new TH1D(Form("h_res_y__m%d_l%d", m+100, l), Form("h_res_y__m%d_l%d", m+100, l), 100, -4, 4);

				h_res_vtx_trk_x[m][l] = new TH1D(Form("h_res_vtx_trk_x_m%d_l%d", m+100, l), Form("h_res_vtx_trk_x_m%d_l%d", m+100, l), 100, -2, 2);
				h_res_vtx_trk_y[m][l] = new TH1D(Form("h_res_vtx_trk_y_m%d_l%d", m+100, l), Form("h_res_vtx_trk_y_m%d_l%d", m+100, l), 100, -4, 4);
				h_cor_res_fitlx[m][l]  = new TH2D(Form("h_cor_res_fitlx__%d_%d", m+100, l), Form("h_cor_res_fitlx_%d_%d", m+100, l), 40, -50*l , 50*l, 100, -2.5, 2.5);
				h_cor_res_fitly[m][l]  = new TH2D(Form("h_cor_res_fitly__%d_%d", m+100, l), Form("h_cor_res_fitly_%d_%d", m+100, l), 20, -50*l , 50*l, 100, -2, 2);
				h_cor_res_timing[m][l] = new TH2D(Form("h_cor_res_timing__%d_%d", m+100, l), Form("h_cor_res_timing_%d_%d", m+100, l), 20, 0 , 600, 100, -2, 2);
				h_tan_theta[m][l] = new TH1D(Form("h_tan_theta_m%d_l%d",  m+100, l), Form("h_tan_theta_%d_%d", m+100, l), 20,  -0.5, 0.5);
				h_cor_dz_time[m][l]        = new TH2D(Form("h_cor_dz_time_%d%d", m+100, l)      , Form("h_cor_dz_time_%d%d",  m+100, l)     , 20, 0, 600, 60,  -6, 6);
				h_cor_dz_time_t0cor[m][l]= new TH2D(Form("h_cor_dz_time_t0cor_%d_%d",  m+100, l), Form("h_cor_dz_time_t0cor_%d%d", m+100, l), 20, 0, 600, 7, -8, 8);
					for(int div = 0; div < n_div; div++){
						h_cluster_timing_chi2_xdependence[m][l][div] = new TH1D(Form("h_cluster_timing_chi2_xdependence%d_%d_%d", m+100, l, div), Form("h_cluster_timing_chi2_xdependence%d_%d_%d", m+100, l, div), 20, 0 ,600 ) ;
						h_cluster_timing_chi2_ydependence[m][l][div] = new TH1D(Form("h_cluster_timing_chi2_ydependence%d_%d_%d", m+100, l, div), Form("h_cluster_timing_chi2_ydependence%d_%d_%d", m+100, l, div), 20, 0 ,600 ) ;
						h_cluster_adc_xdependence[m][l][div] = new TH1D(Form("h_cluster_adc_xdependence%d_%d_%d", m+100, l, div), Form("h_cluster_adc_xdependence%d_%d_%d", m+100, l, div), 20, 0 ,5000 ) ;
						h_cluster_adc_ydependence[m][l][div] = new TH1D(Form("h_cluster_adc_ydependence%d_%d_%d", m+100, l, div), Form("h_cluster_adc_ydependence%d_%d_%d", m+100, l, div), 20, 0 ,5000 ) ;
						}
				for(int t=0; t < n_tgt; t++){
					h_fitlx[t][m][l] = new TH1D(Form("h_fitlx_tgt%d_m%d_l%d",t, m+100, l), Form("h_fitlx_tgt%d_m%d_l%d",t, m+100, l), 100, -2, 2);
				}
			}
		}	



std::array<int, 4> mids;
std::array<int, 4> mids_tid0;
std::array<int, 4> mids_tid1;
std::array<double, 4> resx;
std::array<double, 4> resx_tid0;
std::array<double, 4> resx_tid1;
std::array<double, 4> resy;
std::array<double, 4> resy_tid0;
std::array<double, 4> resy_tid1;
std::array<double, 4> fitlxs;
std::array<double, 4> fitlys;
std::array<double, 4> tans;//tan thetas
std::array<double, 4> xt4s;//xt4
std::array<double, 4> xadcs;//xt4
std::array<double, 4> yadcs;//xt4
std::array<double, 4> xcids;//xt4
std::array<double, 4> xtotend;//xt4


	double mplgy;
	double plgx;
	double pre_mplgy[10] = {9999, 9999, 9999, 9999 ,9999, 9999, 9999, 9999, 9999, 9999};
	double pre_plgx[10] = {9999, 9999, 9999, 9999 ,9999, 9999, 9999, 9999, 9999, 9999};



	for(int n=0; n < nevent; n++){
		if(n > n_maxevent) break;
			if (n % print_cycle == 0) {
				printf(" N Analyzed = %d \n", n);
			} 
			tree->GetEntry(n);
			h_n_runid->Fill(run_id);
			h_n_eventid->Fill(event_id);
			h_n_spillid->Fill(spill_id);

// ------- analysis for pair ------- //
			for(int i=0; i < n_pairs; i++){
				if(rk_pair_plus_chi_square->at(i) < 20 && rk_pair_minus_chi_square->at(i) < 20){
					int tid0 = rk_pair_minus_track_id->at(i);
					int tid1 = rk_pair_plus_track_id->at(i);
					int n_tracks = chi_square->size();
					for(int j=0; j < n_tracks; j++){
					   TVector3 vtx_gpos = TVector3(rk_pair_vtx_gx->at(i), rk_pair_vtx_gy->at(i), rk_pair_vtx_gz->at(i));
						h_vtx_gx->Fill(vtx_gpos.x());
						h_vtx_gy->Fill(vtx_gpos.y());
						h_vtx_gz->Fill(vtx_gpos.z());
						h_vtx_gx_gz->Fill(vtx_gpos.x(), vtx_gpos.z());
						h_vtx_gx_gy->Fill(vtx_gpos.x(), vtx_gpos.y());
					if( tid0 == track_id->at(j) || tid1 == track_id->at(j)){
						mids= {	rk_fit_sts_mid->at(j),
									rk_fit_gtr100_mid->at(j),						
									rk_fit_gtr200_mid->at(j),
									rk_fit_gtr300_mid->at(j)};
						resx = { rk_res_sts_x->at(j),
									rk_res_gtr100_x->at(j),
									rk_res_gtr200_x->at(j),
									rk_res_gtr300_x->at(j)};
						resy = { 0,
									rk_res_gtr100_y->at(j),
									rk_res_gtr200_y->at(j),
									rk_res_gtr300_y->at(j)};
						for(int l=1; l < 4; l++){//layer loop
							h_res_vtx_trk_x[mids[l]-100][l]->Fill(resx[l]);
							h_res_vtx_trk_y[mids[l]-100][l]->Fill(resy[l]);
						}
// --- residual LG -- //
//										 mplgy = rk_fit_lg_b_gy->at(i);
//										 plgx  = rk_fit_lg_b_x->at(i);
//										if(fabs(mplgy) > 260){
//											plgx = rk_fit_lg_c_x->at(i);
//										}
//										if(fabs(mplgy) < 150){
//											plgx = rk_fit_lg_a_x->at(i);
//										}
//										double lg_near = -9999;
//										double mind =9999;
//										int nlg = 0;
//										for(int k=0; k < n_lg_hits;k++){
//											if(lg_hit_mid->at(k) == rk_fit_lg_b_mid->at(i)){
//												int lg_mid = lg_hit_mid->at(k);
//												if(lg_hit_adc->at(k) < 10) continue;
//								//				if(fabs(lg_hit_x->at(k) - 310) < 1 && fabs(lg_hit_y->at(k) + 315) < 1) continue; 
//												double dx     = lg_hit_x->at(k) - plgx;
//												double dy     = lg_hit_gy->at(k) - mplgy;
//												double pre_dx = lg_hit_x->at(k)  - pre_plgx[lg_mid-100];
//												double pre_dy = lg_hit_gy->at(k) - pre_mplgy[lg_mid-100];
//
////												std::cout << "dx = " << dx << ", " << pre_dx << std::endl;
////												std::cout << "dy = " << dy << ", " << pre_dy << std::endl;
//												
//												h_res_vtx_trk_lg_x[lg_mid-100]->Fill(dx);
//												h_res_vtx_trk_lg_y[lg_mid-100]->Fill(dx);
//												h_bak_res_vtx_trk_lg_x[lg_mid-100]->Fill(pre_dx);
//												h_bak_res_vtx_trk_lg_y[lg_mid-100]->Fill(pre_dx);
//											}
//										}




						}
					}
				}	
			}//analysis for pairs


// ------- analysis for 1 track ---- // 
			int n_tracks = chi_square->size();//note that n tracks are judged with chi2 vec
         for(int i=0; i < n_tracks;i++){
         	double chi2 = chi_square->at(i);
				mids = {	rk_fit_sts_mid->at(i),
					rk_fit_gtr100_mid->at(i),						
					rk_fit_gtr200_mid->at(i),
					rk_fit_gtr300_mid->at(i)};
				resx = { rk_res_sts_x->at(i),
							rk_res_gtr100_x->at(i),
							rk_res_gtr200_x->at(i),
							rk_res_gtr300_x->at(i)};
				resy = { 0,
							rk_res_gtr100_y->at(i),
							rk_res_gtr200_y->at(i),
							rk_res_gtr300_y->at(i)};
				fitlxs   = { rk_fit_sts_x  ->at(i),
				   		 rk_fit_gtr100_x->at(i),
							 rk_fit_gtr200_x->at(i),
							 rk_fit_gtr300_x->at(i)};
				fitlys   = { 0,
				   		 rk_fit_gtr100_y->at(i),
							 rk_fit_gtr200_y->at(i),
							 rk_fit_gtr300_y->at(i)};
				tans = { rk_fit_sts_mom_x->at(i)/rk_fit_sts_mom_z->at(i),
							rk_fit_gtr100_mom_x->at(i)/rk_fit_gtr100_mom_z->at(i),
							rk_fit_gtr200_mom_x->at(i)/rk_fit_gtr200_mom_z->at(i),
							rk_fit_gtr300_mom_x->at(i)/rk_fit_gtr300_mom_z->at(i)};
				xt4s = { 0, 
							rk_hit_gtr100_xt4->at(i),
							rk_hit_gtr200_xt4->at(i),
      					rk_hit_gtr300_xt4->at(i)};
				xadcs = {rk_hit_sts_adc->at(i), rk_hit_gtr100_xadc->at(i), rk_hit_gtr200_xadc->at(i), rk_hit_gtr300_xadc->at(i)};
				yadcs = {0, rk_hit_gtr100_yadc->at(i), rk_hit_gtr200_yadc->at(i), rk_hit_gtr300_yadc->at(i)};


				xcids = {-100, rk_hit_gtr100_xid->at(i), rk_hit_gtr200_xid->at(i), rk_hit_gtr300_xid->at(i)};
            xtotend = {-100,gtr100x_cluster_last_tot_end->at(i), gtr200x_cluster_last_tot_end->at(i), gtr300x_cluster_last_tot_end->at(i) };
				

	double tgt_x = rk_fit_init_pos_gx->at(i);
	double tgt_y = rk_fit_init_pos_gy->at(i);
	double tgt_z = rk_fit_init_pos_gz->at(i);
	double tdiff100 = rk_hit_gtr100_xt->at(i) - rk_hit_gtr100_yt->at(i);
	double tdiff200 = rk_hit_gtr200_xt->at(i) - rk_hit_gtr200_yt->at(i);
	double tdiff300 = rk_hit_gtr300_xt->at(i) - rk_hit_gtr300_yt->at(i);
	int mid = mids[1];//mid is decided by gtr100
   bool lg_flag = true;

//	std::cout << "fitlx " << fitlxs[1] << std::endl;


//	double smallest_lgt = 1000;
//	for(int j=0; j < rk_proj_lg_t->size(); j++) {
//		for( auto lgt : rk_proj_lg_t->at(j)){
//			h_lg_t_mod[mid-100]->Fill(lgt);
//			if(lgt > 0  && lgt< 90){ 
//				lg_flag = true;
//			if(smallest_lgt > lgt) smallest_lgt = lgt;
//			}
//		}
//	}
//	double t0diff = smallest_lgt - 88;//run0d


	for(int l=0; l < 4; l++){
	}

	double tgt_range_center[10] = {0, -60, -60, -60, -60, 0, -60, -60, -60, -60};		

		if (lg_flag){
		h_chi2->Fill(chi2);
		h_chi2_mod[mid-100]->Fill(chi2);
		h_tgt_pos_mod_raw[mid-100]->Fill(rk_fit_init_pos_gx->at(i), rk_fit_init_pos_gz->at(i));
		h_init_pos->Fill(rk_fit_init_pos_gx->at(i), rk_fit_init_pos_gz->at(i));
		h_tgt_proj_z_raw[mid-100]->Fill(rk_fit_init_pos_gz->at(i));



			for(int m=100; m < 110; m++){
					if(mid ==m){//module id matching (with track)
						for(int l=0; l < 4; l++){
#ifdef NoExist_SSD
							if(l==0) continue;
#endif
							double lx = fitlxs[l];
							double ly = fitlys[l];
							double offset = 50 * (l );
//								std::cout << "lx  = " << lx << std::endl; 
							int nth_div =  (lx + offset) / ((l*100)/n_div);
							int nth_divy = (ly + offset) / ((l*100)/n_div);
//								std::cout << "nth div = " << nth_div << std::endl;
								h_cluster_timing_raw[m-100][l]->Fill(xt4s[l]);
								if(chi2 <  20){
										h_tgt_proj_z_chi2cut[m-100]->Fill(rk_fit_init_pos_gz->at(i));

//---  LG residual
										 mplgy = rk_fit_lg_b_gy->at(i);
										 plgx  = rk_fit_lg_b_x->at(i);
										if(fabs(mplgy) > 260){
											plgx = rk_fit_lg_c_x->at(i);
										}
										if(fabs(mplgy) < 150){
											plgx = rk_fit_lg_a_x->at(i);
										}
										double lg_near = -9999;
										double mind =9999;
										int nlg = 0;
										for(int k=0; k < n_lg_hits;k++){
											if(lg_hit_mid->at(k) == rk_fit_lg_b_mid->at(i)){
												int lg_mid = lg_hit_mid->at(k);
												if(lg_hit_adc->at(k) < 10) continue;
								//				if(fabs(lg_hit_x->at(k) - 310) < 1 && fabs(lg_hit_y->at(k) + 315) < 1) continue; 
												double dx     = lg_hit_x->at(k) - plgx;
												double dy     = lg_hit_gy->at(k) - mplgy;
												double pre_dx = lg_hit_x->at(k)  - pre_plgx[lg_mid-100];
												double pre_dy = lg_hit_gy->at(k) - pre_mplgy[lg_mid-100];
//												std::cout << "dx = " << dx << ", " << pre_dx << std::endl;
//												std::cout << "dy = " << dy << ", " << pre_dy << std::endl;
												h_res_lg_x[lg_mid-100]->Fill(dx);
												h_res_lg_y[lg_mid-100]->Fill(dx);
												h_bak_res_lg_x[lg_mid-100]->Fill(pre_dx);
												h_bak_res_lg_y[lg_mid-100]->Fill(pre_dx);
											}
										}
//								


									h_res_x[mids[l]-100][l]->Fill(resx[l]);
									h_res_y[mids[l]-100][l]->Fill(resy[l]);
									h_cluster_timing_chi2[m-100][l]->Fill(xt4s[l]);
//									h_cluster_timing_chi2_xdependence[m-100][l][nth_div]->Fill(xt4s[l]);
//									h_cluster_timing_chi2_ydependence[m-100][l][nth_divy]->Fill(xt4s[l]);
//									h_cluster_adc_xdependence[m-100][l][nth_div]->Fill(xadcs[l]);
//									h_cluster_adc_ydependence[m-100][l][nth_divy]->Fill(yadcs[l]);
									h_cor_res_fitlx[mids[l]-100][l]->Fill(fitlxs[l], resx[l]);	
									h_cor_res_fitly[mids[l]-100][l]->Fill(fitlys[l], resx[l]);	
									h_cor_res_timing[mids[l]-100][l]->Fill(xt4s[l], resx[l]);	//timing
									h_tan_theta[mids[l]-100][l]     ->Fill(tans[l]);
									h_cor_dz_time[mids[l]-100][l]   ->Fill(xt4s[l], resx[l]/tans[l]);	
//									h_cor_dz_time_t0cor[mid-100][l] ->Fill(xt4s[l] - t0diff, resx[l]/tans[l]);//plus or minus?
//										h_slopevel[mid-100][l][ith_div]->Fill((xt4s[l] - 250) * tans[l], resx[l] ); 


									if(m == 102){
									if(-25 < rk_fit_init_pos_gz->at(i) && rk_fit_init_pos_gz->at(i) < 30){
										h_tot_end_fr[m-100][l]->Fill(xtotend[l]);
									} else {
										h_tot_end_bg[m-100][l]->Fill(xtotend[l]);
									}
									}
									else if(m == 103){
									if(-20 < rk_fit_init_pos_gz->at(i) && rk_fit_init_pos_gz->at(i) < 30){
										h_tot_end_fr[m-100][l]->Fill(xtotend[l]);
									} else {
										h_tot_end_bg[m-100][l]->Fill(xtotend[l]);
									}
									}


									else if(m == 104){
									if(-30 < rk_fit_init_pos_gz->at(i) && rk_fit_init_pos_gz->at(i) < 20){
										h_tot_end_fr[m-100][l]->Fill(xtotend[l]);
									} else {
										h_tot_end_bg[m-100][l]->Fill(xtotend[l]);
									}
									}

									else if(m == 106){
									if(-15 < rk_fit_init_pos_gz->at(i) && rk_fit_init_pos_gz->at(i) < 32){
										h_tot_end_fr[m-100][l]->Fill(xtotend[l]);
									} else {
										h_tot_end_bg[m-100][l]->Fill(xtotend[l]);
									}
									}
									else if(m == 107){
									if(-30 < rk_fit_init_pos_gz->at(i) && rk_fit_init_pos_gz->at(i) < 20){
										h_tot_end_fr[m-100][l]->Fill(xtotend[l]);
									} else {
										h_tot_end_bg[m-100][l]->Fill(xtotend[l]);
									}
									}
									else {
									if(-30 < rk_fit_init_pos_gz->at(i) && rk_fit_init_pos_gz->at(i) < 30){
										h_tot_end_fr[m-100][l]->Fill(xtotend[l]);
									} else {
										h_tot_end_bg[m-100][l]->Fill(xtotend[l]);
									}
									}

		         			}

						}
					}
				}
				}
												pre_mplgy[rk_fit_lg_b_mid->at(i)-100] = mplgy;
												pre_plgx[rk_fit_lg_b_mid->at(i)-100] = plgx;
			}

	}
   
   fout->Write();

	TCanvas *c0 = new TCanvas();
	c0->SaveAs(pdf_name + "[", "pdf");
	gStyle->SetOptStat(1111111);
	gStyle->SetOptFit(0111);

	TCanvas *c_vtx = new TCanvas();
		c_vtx->Divide(3,2);
		c_vtx->cd(1);
		h_vtx_gx->Fit("gaus", "", "", -2, 3);
		h_vtx_gx->Draw();
		c_vtx->cd(2);
		h_vtx_gy->Fit("gaus", "", "", -3, 1);
		h_vtx_gy->Draw();
		c_vtx->cd(3);
		h_vtx_gz->Draw();
		c_vtx->cd(4);
		h_vtx_gx_gz->Draw("colz");
		c_vtx->cd(5);
		h_vtx_gx_gy->Draw("colz");
   c_vtx->SaveAs(pdf_name, "pdf");


  TCanvas *c_res_v[10];
  for(int m =1; m < 9; m++){ 
    c_res_v[m]= new TCanvas(); 
    c_res_v[m]->Divide(2,2);
    for(int l=0; l < n_layer; l++){
     c_res_v[m]->cd(1+l);
     if(m < 5) {
        h_res_vtx_trk_x[m][l]->Fit("gaus", "", "", -0.5, 0.2);
        h_res_vtx_trk_x[m][l]->Draw("colz");
     }
     else {
        h_res_vtx_trk_x[m+1][l]->Fit("gaus", "", "", -0.5, 0.2);
        h_res_vtx_trk_x[m+1][l]->Draw("colz");
     }
	 }
    c_res_v[m]->SaveAs(pdf_name, "pdf");
  }


	TCanvas *cv_lgres;
	cv_lgres = new TCanvas();
	cv_lgres->Divide(4,2);
	for(int mid=101; mid < 110; mid++){
		if(mid == 105) continue;
		if(mid < 105){
		cv_lgres->cd(mid-100);
		h_res_vtx_trk_lg_x[mid-100]->Draw();
		h_bak_res_vtx_trk_lg_x[mid-100]->SetLineColor(kRed);
		h_bak_res_vtx_trk_lg_x[mid-100]->Draw("same");
		}
	   else if(mid > 105){
			cv_lgres->cd(mid-101);
			h_res_vtx_trk_lg_x[mid-100]->Draw();
			h_bak_res_vtx_trk_lg_x[mid-100]->SetLineColor(kRed);
			h_bak_res_vtx_trk_lg_x[mid-100]->Draw("same");
			
		}
   }
	cv_lgres->SaveAs(pdf_name, "pdf");




	TCanvas *c2[n_module];
	for(int m =1; m < 9; m++){
	   c2[m]= new TCanvas();
		c2[m]->Divide(2,2);
		for(int l=0; l < 4; l++){
   		c2[m]->cd(l+1);
	      if(m < 5) {
      	   h_cluster_timing_raw[m][l]->Draw("colz");
   	   }
 	     else {
         	h_cluster_timing_raw[m][l]->Draw("colz");
      	}
   	}
   c2[m]->SaveAs(pdf_name, "pdf");
	}


	TCanvas *c2_chi[n_module];
	for(int m =1; m < 9; m++){
	   c2_chi[m]= new TCanvas();
		c2_chi[m]->Divide(2,2);
		for(int l=0; l < 4; l++){
   		c2_chi[m]->cd(l+1);
	      if(m < 5) {
      	   h_cluster_timing_chi2[m][l]->Draw();
   	   }
 	     else {
         	h_cluster_timing_chi2[m][l]->Draw();
      	}
   	}
   c2_chi[m]->SaveAs(pdf_name, "pdf");
	}

TCanvas *c03 = new TCanvas();
h_init_pos->Draw("colz");
c03->SaveAs(pdf_name, "pdf");


	TCanvas *c22[n_module];
	for(int m =1; m < 9; m++){
	   c22[m]= new TCanvas();
		c22[m]->Divide(2,2);
		for(int l=0; l < 4; l++){
   		c22[m]->cd(l+1);
	      if(m < 5) {
      	   h_tot_end_fr[m][l]->Draw();
      	   h_tot_end_bg[m][l]->Scale(h_tot_end_fr[m][l]->GetEntries() / h_tot_end_bg[m][l]->GetEntries());
      	   std::cout << "scale " << h_tot_end_fr[m][l]->GetEntries() / h_tot_end_bg[m][l]->GetEntries() << std::endl;
      	   h_tot_end_bg[m][l]->SetLineColor(kRed);
      	   h_tot_end_bg[m][l]->Draw("same");
   	   }
 	     else {
         	h_tot_end_fr[m][l]->Draw();
      	   h_tot_end_bg[m][l]->Scale(h_tot_end_fr[m][l]->GetEntries() / h_tot_end_bg[m][l]->GetEntries());
      	   h_tot_end_bg[m][l]->SetLineColor(kRed);
         	h_tot_end_bg[m][l]->Draw("same");
      	}
   	}
   c22[m]->SaveAs(pdf_name, "pdf");
	}


	TCanvas *c23[n_module];
	for(int m =1; m < 9; m++){
	   c23[m]= new TCanvas();
		c23[m]->Divide(2,2);
		for(int l=0; l < 4; l++){
   		c23[m]->cd(l+1);
	      if(m < 5) {
      	   h_tot_end_bg[m][l]->SetLineColor(kRed);
      	   h_tot_end_bg[m][l]->Draw("same");
   	   }
 	     else {
      	   h_tot_end_bg[m][l]->SetLineColor(kRed);
         	h_tot_end_bg[m][l]->Draw("same");
      	}
   	}
   c23[m]->SaveAs(pdf_name, "pdf");
	}




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



	TCanvas *c3[n_module];
   for(int m=0; m < n_module;m++){
		c3[m] = new TCanvas();
		c3[m]->Divide(n_div,3 );
		for(int l=1; l<4; l++){
			for(int div=0; div < n_div; div++){
			   c3[m]->cd(div + 1 + n_div * (l-1) );
				h_cluster_timing_chi2_xdependence[m][l][div]->Draw();
			}
		}
	c3[m]->SaveAs(pdf_name, "pdf");
	}

	TCanvas *c4[n_module];
   for(int m=0; m < n_module;m++){
		c4[m] = new TCanvas();
		c4[m]->Divide(n_div, 3);
		for(int l=1; l<4; l++){
			for(int div=0; div < n_div; div++){
			   c4[m]->cd(div + 1 + n_div * (l-1) );
				h_cluster_timing_chi2_ydependence[m][l][div]->Draw();
			}
		}
	c4[m]->SaveAs(pdf_name, "pdf");
	}


	TCanvas *c5[n_module];
   for(int m=0; m < n_module;m++){
		c5[m] = new TCanvas();
		c5[m]->Divide(n_div, 3);
		for(int l=1; l<4; l++){
			for(int div=0; div < n_div; div++){
			   c5[m]->cd(div + 1 + n_div * (l-1) );
				h_cluster_adc_xdependence[m][l][div]->Draw();
			}
		}
	c5[m]->SaveAs(pdf_name, "pdf");
	}

	TCanvas *c6[n_module];
   for(int m=0; m < n_module;m++){
		c6[m] = new TCanvas();
		c6[m]->Divide(n_div, 3);
		for(int l=1; l<4; l++){
			for(int div=0; div < n_div; div++){
			   c6[m]->cd(div + 1 + n_div * (l-1) );
				h_cluster_adc_ydependence[m][l][div]->Draw();
			}
		}
	c6[m]->SaveAs(pdf_name, "pdf"); }



  TCanvas *c1[10];
  for(int m =1; m < 9; m++){ 
    c1[m]= new TCanvas(); 
    c1[m]->Divide(2,2);
    for(int l=0; l < n_layer; l++){
     c1[m]->cd(1+l);
     if(m < 5) {
        h_res_x[m][l]->Fit("gaus", "", "", -0.5, 0.2);
        h_res_x[m][l]->Draw("colz");
     }
     else {
        h_res_x[m+1][l]->Fit("gaus", "", "", -0.5, 0.2);
        h_res_x[m+1][l]->Draw("colz");
     }
	 }
    c1[m]->SaveAs(pdf_name, "pdf");
  }

 TCanvas *c2y = new TCanvas();
 c2y->Divide(4,2);
 for(int i =1; i < 9; i++){
     c2y->cd(i);
     if(i < 5) {
        h_res_y[i][residual_layer]->Draw("colz");
     }
     else {
        h_res_y[i+1][residual_layer]->Draw("colz");
     }
  }
  c2y->SaveAs(pdf_name, "pdf");

 TCanvas *c3t = new TCanvas();
 c3t->Divide(4,2);
 for(int i =1; i < 9; i++){
     c3t->cd(i);
     if(i < 5) {
        h_tan_theta[i][residual_layer]->Draw("colz");
     }
     else {
        h_tan_theta[i+1][residual_layer]->Draw("colz");
     }
  }
  c3t->SaveAs(pdf_name, "pdf");





 TCanvas *c31[10];
   TGraphErrors *gr[10];
   TGraphErrors *gr_mean[10];
   TH1D *h1[10];
   TF1 *f1[10];
   for(int hmid=101; hmid < 110; hmid++){
      if(hmid == 105)continue;
            c31[hmid-100] = new TCanvas();
            c31[hmid-100]->Divide(4,3);
            int n = h_cor_res_fitlx[hmid-100][residual_layer]->GetNbinsX();
            double xmin = -2;
            double xmax =  2;
            std::cout << "nibs = " << n << std::endl;
            gr[hmid-100] = new TGraphErrors(n);
            gr_mean[hmid-100] = new TGraphErrors(n);
             for (int i = 1; i <= n; i++) {
               c31[hmid-100]->cd(i);
                h1[hmid-100] = h_cor_res_fitlx[hmid-100][residual_layer]->ProjectionY(Form("_py%d%d", hmid, i), i, i     );
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


  TCanvas *c61 = new TCanvas();
  c61->Divide(4,2);
  for(int i =1; i < 9; i++){
     c61->cd(i);
     if(i < 5) {
        h_cor_dz_time[i][residual_layer]->Draw("colz");
     }
     else {
        h_cor_dz_time[i+1][residual_layer]->Draw("colz");
     }
  }
  c61->SaveAs(pdf_name, "pdf");


   TCanvas *c16[10];
   TGraphErrors *gr16[10];
   TH1D *h16[10];
   TF1  *f16[10];
   TF1  *fla[10];
   double xmin[10]  = {0, -4.5, -5.5, -5.5,     -5.5, 0, -3.5,  -3.5, -4.5, -4.5};//mod100-109
   double xmax[10]  = {0, 4.5, 3.5, 3.5,      3.5, 0,  3.5 ,  3.0,  8,  8};
   double flmin[10] = {0, 120, 120, 120, 120,   0,   120, 100, 180, 180};
   double flmax[10] = {0, 450, 450, 450, 500, 0, 500, 450, 550, 450};
   for(int hmid=101; hmid < 110; hmid++){
      c16[hmid-100] = new TCanvas();
      int n = h_cor_dz_time[hmid-100][residual_layer]->GetNbinsX();
      c16[hmid-100]->Divide(5,5);
      std::cout << "nbins dz = " << n << std::endl;
      gr16[hmid-100] = new TGraphErrors(n);
    	gr16[hmid-100]->SetMaximum( 8.0);
 	   gr16[hmid-100]->SetMinimum(-8.0);
       for (int i = 1; i <= n; i++) {
         c16[hmid-100]->cd(i);
         fla[hmid-100] = new TF1(Form("fla%d", hmid), "pol1", flmin[hmid-100], flmax[hmid-100]);
         h16[hmid-100] = h_cor_dz_time[hmid-100][residual_layer]->ProjectionY(Form("_py%d%d", hmid, i), i, i);
         //f16[hmid-100] = new TF1(Form("f16%d%d",hmid, i), "landau");
//       f16[hmid-100] = new TF1("fitFunction", "gaus(0) + [3]*exp(-[4]*(x-[5])  )", xmin, xmax);
//       f16[hmid-100] = new TF1("fitFunction", "gaus(0)+[3]+[4]*x+[5]*x*x+[6]*x*x*x", xmin,xmax);
         //f16[hmid-100]->SetParNames("Constant", "Mean", "Sigma", "Slope", "X0");
          f16[hmid-100] = new TF1("fitFunction", "gaus(0)+[3]+[4]*x+[5]*x*x", xmin[hmid-100],xmax[hmid-100]);
         f16[hmid-100] = new TF1("fitFunction", "gaus(0)+[3]*x", xmin[hmid-100],xmax[hmid-100]);
//       f16[hmid-100] = new TF1("fitFunction", "[0]*exp(-0.5*((x-[1])/[2])**2) + [3]*TMath::Erfc([4]*(x-[5]))", xmin, xmax);
//       f16[hmid-100]->SetParNames("Constant", "Mean", "Sigma", "TailHeight", "TailSlope","TailX0");
         f16[hmid-100]->SetParameter(0, 20); // constant
         f16[hmid-100]->SetParameter(1, 0);     // mean
         f16[hmid-100]->SetParameter(2, 10);    // sigma
         f16[hmid-100]->SetParLimits(2, 1, 10);
         f16[hmid-100]->SetParameter(3, 0);    
         f16[hmid-100]->SetParLimits(3, -0.8, 0);
         f16[hmid-100]->SetParameter(4, -1);    
         f16[hmid-100]->SetParameter(4, -0.5);  
         h16[hmid-100]->Fit(f16[hmid-100], "", "", xmin[hmid-100], xmax[hmid-100]);

          double chi2 = f16[hmid-100]->GetChisquare();
         double mean =  f16[hmid-100]->GetParameter(1);
          double sigma_err = f16[hmid-100]->GetParError(2);
         std::cout << "mod, fit chi2  = " << hmid  << ", "  << chi2 << std::endl;
         if(chi2 < 5) continue;
         if(sigma_err > 10) continue;
          gr16[hmid-100]->SetPoint(i-1, i*(600/n), mean);
          gr16[hmid-100]->SetPointError(i-1, 0, sigma_err);
          gr16[hmid-100]->Fit(fla[hmid-100], "R");
          h16[hmid-100]->Draw();
      }
         c16[hmid-100]->SaveAs(pdf_name, "pdf");
   }


   TCanvas *c17;
  c17= new TCanvas();
   c17->Divide(4,2);
   for(int hmid=101; hmid < 110; hmid++){
		if(hmid == 105) continue;
      if(hmid < 105) {
		c17->cd(hmid-100);
      gr16[hmid-100]->SetTitle(Form("residual/tan_theta mod%d : timing ;  timing; residual/tan_theta",  hmid) );
      gr16[hmid-100]->Draw("AP");
	 }
 	 else {c17->cd(hmid-101);}
      gr16[hmid-100]->SetTitle(Form("residual/tan_theta mod%d : timing ;  timing; residual/tan_theta",  hmid) );
      gr16[hmid-100]->Draw("AP");
   }
  c17->SaveAs(pdf_name, "pdf");


	TCanvas *c18;
	c18 = new TCanvas();
	c18->Divide(4,2);
	for(int mid=101; mid < 110; mid++){
		if(mid == 105) continue;
		if(mid < 105){
		c18->cd(mid-100);
		h_res_lg_x[mid-100]->Draw();
		h_bak_res_lg_x[mid-100]->SetLineColor(kRed);
		h_bak_res_lg_x[mid-100]->Draw("same");
		}
	   else if(mid > 105){
			c18->cd(mid-101);
			h_res_lg_x[mid-100]->Draw();
			h_bak_res_lg_x[mid-100]->SetLineColor(kRed);
			h_bak_res_lg_x[mid-100]->Draw("same");
			
		}
   }
	c18->SaveAs(pdf_name, "pdf");

// TCanvas *c6b = new TCanvas();
// c6b->Divide(2,2);
// for(int tgt=0; tgt<2; tgt++){
// for(int i =1; i < 9; i++){
//   
//    c6b->cd(i);
//    if(i < 5) {
//       h_cor_dz_time_t0cor[i][residual_layer]->Draw("colz");
//    }
//    else {
//       h_cor_dz_time_t0cor[i+1][residual_layer]->Draw("colz");
//    }
// }
// }
// c6b->SaveAs(pdf_name, "pdf");



//TCanvas *c16b[2][10][n_div];
//TGraphErrors *gr16b[2][10][n_div];
//TH1D *h16b[2][10][n_div];
//TF1 *f16b[2][10][n_div];
//TF1 *flab[2][10][n_div];
//def CALIB
//double xminb[10]  = {0, -4, -7, -7,     -6, 0, -2, -5.5, -4, -4};//mod100-109
//double xmaxb[10]  = {0,  4, 10, 10,    5.5, 0,  2,  4.0,  5,  5};
//se 
//double xminb[10]  = {0, -4, -7, -7,     -6, 0, -4, -5.5, -4, -4};//mod100-109
//double xmaxb[10]  = {0,  4, 10, 10,    5.5, 0,   4,  4.0,  5,  5};
//dif
//double flminb[10] = {0, 120, 120, 120, 120, 0, 200, 120, 100, 180};
//double flmaxb[10] = {0, 450, 450, 450, 450, 0, 550, 450, 320, 450};
//r(int t=0; t < 2; t++){
// int hmid = 106;
// for(int d=0 ; d < n_div; d++){
//   c16b[t][hmid-100][d] = new TCanvas();
//   int n = h_cor_dz_time_t0cor[t][hmid-100][residual_layer][d]->GetNbinsX();
//   c16b[t][hmid-100][d]->Divide(5,5);
//   std::cout << "nbins dz = " << n << std::endl;
//   gr16b[t][hmid-100][d] = new TGraphErrors(n);
//	gr16b[t][hmid-100][d]->SetMaximum( 8.0);
// gr16b[t][hmid-100][d]->SetMinimum(-8.0);
//    for (int i = 1; i <= n; i++) {
//      c16b[t][hmid-100][d]->cd(i);
//      flab[t][hmid-100][d] = new TF1(Form("fla%d%d", t, d), "pol1", flminb[hmid-100], flmaxb[hmid-100]);
//      h16b[t][hmid-100][d] = h_cor_dz_time_t0cor[t][hmid-100][residual_layer][d]->ProjectionY(Form("_py%d%d%d", hmid, i), i, i);
//        f16b[t][hmid-100][d] = new TF1("fitFunction", "gaus(0)+[3]+[4]*x+[5]*x*x", xminb[hmid-100],xmaxb[hmid-100]);
//        f16b[t][hmid-100][d] = new TF1(Form("fitFunction%d%d", t, d), "gaus(0)+[3]*x*x", xminb[hmid-100],xmaxb[hmid-100]);
//      f16b[t][hmid-100][d] = new TF1("fitFunction", "gaus(0)+[3]*x", xminb[hmid-100],xmaxb[hmid-100]);
//      f16b[hmid-100] = new TF1("fitFunction", "[0]*exp(-0.5*((x-[1])/[2])**2) + [3]*TMath::Erfc([4]*(x-[5]))", xmin, xmax);
//      f16b[hmid-100]->SetParNames("Constant", "Mean", "Sigma", "TailHeight", "TailSlope","TailX0");
//      f16b[t][hmid-100][d]->SetParameter(0, 20); // constant
//      f16b[t][hmid-100][d]->SetParameter(1, 0);     // mean
//      f16b[t][hmid-100][d]->SetParameter(2, 3);    // sigma
//        f16b[t][hmid-100][d]->SetParameter(3, 0);    
//        f16b[t][hmid-100][d]->SetParameter(4, -1);    
//        f16b[t][hmid-100][d]->SetParameter(4, -0.5);  
//      h16b[t][hmid-100][d]->Fit(f16b[t][hmid-100][d], "", "", xminb[hmid-100], xmaxb[hmid-100]);
//
//       double chi2 = f16b[t][hmid-100][d]->GetChisquare();
//      double mean = f16b[t][hmid-100][d]->GetParameter(1);
//       double sigma_err = f16b[t][hmid-100][d]->GetParError(2);
//      std::cout << "mod, fit chi2  = " << hmid  << ", "  << chi2 << std::endl;
//      if(chi2 < 5) continue;
//      if(sigma_err > 10) continue;
//       gr16b[t][hmid-100][d]->SetPoint(i-1, i*(600/n), mean);
//       gr16b[t][hmid-100][d]->SetPointError(i-1, 0, sigma_err);
//       gr16b[t][hmid-100][d]->Fit(flab[t][hmid-100][d], "R");
//       h16b[t][hmid-100][d]->Draw();
//   }
//      c16b[t][hmid-100][d]->cd(6);
//      c16b[t][hmid-100][d]->SaveAs(pdf_name, "pdf");
//	}
//
//
////
////TCanvas *c0d = new TCanvas();
////t0diff->Draw();
////d->SaveAs(pdf_name, "pdf");
//
// TCanvas *c17b[2];
//  	c17b[t] = new TCanvas();
//	 	c17b[t]->Divide(5,4);
// 	for(int d=0; d < n_div; d++){
// 		c17b[t]->cd(d+1);
//       gr16b[t][6][d]->SetTitle(Form("residual/tan_theta tgt%d mod 106 : timing_lg ;  timing_lg; residual/tan_theta", t) );
// 	   gr16b[t][6][d]->Draw("AP");
// 		
// 	}
//   c17b[t]->SaveAs(pdf_name, "pdf");
////}
////
////
// TCanvas *c18[2];
//GraphErrors *tg18[2];
// for(int t=0; t < 2; t++){
// 	c18[t] = new TCanvas();
// 	tg18[t] = new TGraphErrors(n_div);
// 	for(int d=0; d < n_div; d++){
// 		double tilt = flab[t][6][d]->GetParameter(1);
// 		tg18[t]->SetPoint(d, d, tilt);
// 	}
// 		tg18[t]->SetMarkerSize(msize);
// 	tg18[t]->Draw("AP");
//18[t]->SaveAs(pdf_name, "pdf");
//}
//
//
// TCanvas *c19[2];
// for(int t=0; t < 2; t++){
// 	c19[t] = new TCanvas();
// 	c19[t]->Divide(4,5);
// 	for(int d=0; d < n_div; d++){
// 		c19[t]->cd(d+1);
// 		h_slopevel[t][6][residual_layer][d]->Draw("colz");
// 	}
// c19[t]->SaveAs(pdf_name, "pdf");
//}
//
//


	c0->SaveAs(pdf_name + "]", "pdf");

}

	//TH1D* h_chi2;
//	TH1D* h_t0diff;
//	TH1D* h_n_runid;
//	TH1D* h_n_eventid;
//	TH1D* h_n_spillid;
//
//
//	TH1D* h_chi2_mod[n_module];
//	TH1D* h_lg_t_mod[n_module];
//	TH1D* h_tgt_proj_z_raw[n_module];
//	TH1D* h_tgt_proj_z_cut[n_module];
//	TH1D* h_tgt_proj_z_chi2cut[n_module];
//	TH1D* h_tgt_proj_x[n_module];
//	TH1D* h_tgt_proj_y[n_module];
//	TH1D* h_res_x[n_tgt][n_module][n_layer];
//	TH1D* h_res_y[n_tgt][n_module][n_layer];
//	TH1D* h_tan_theta[n_tgt][n_module][n_layer];
//	TH1D* h_fitlx[n_tgt][n_module][n_layer];
//
//	TH2D* h_tgt_pos;
//	TH2D* h_tgt_pos_mod_raw[n_module];
////	TH2D* h_tgt_pos_mod_cut[n_module];
//	TH2D* h_cor_dz_time[n_module][n_layer][n_div];
//	TH2D* h_cor_dz_time_t0cor[n_module][n_layer][n_div];
//	TH2D* h_cor_res_fitlx[n_tgt][n_module][n_layer];
//	TH2D* h_cor_res_fitly[n_tgt][n_module][n_layer];
//	TH2D* h_cor_res_timing[n_tgt][n_module][n_layer];
//	
//	TH2D* h_slopevel[n_tgt][n_module][n_layer][n_div];
//
//	TH2D* h_trackmap[n_tgt][n_module];
//
//
//	h_n_runid = new TH1D("n of events of runid","n of events of runid", 15, 30331.5, 30346.5);
//	h_n_eventid = new TH1D("n of events of event id","n of events of eventid", 10000, -0.5, 9999.5);
//	h_n_spillid = new TH1D("n of events of spill id","n of events of spillid", 1000, -0.5, 999.5);
//	h_chi2    = new TH1D(Form("h_chi2"), Form("h_chi2"), 100, 0, 100);	
//	h_t0diff    = new TH1D(Form("h_t0diff"), Form("h_t0diff"), 100, -100,100);	
//	h_tgt_pos = new TH2D(Form("h_tgt_pos"), Form("h_tgt_pos"), 50, 19.8, 20.2, 200, -60, 60);
//	for(int m=0; m < n_module; m++){
//		for(int tg=0; tg < 2; tg++){
//			h_trackmap[tg][m] = new TH2D(Form("h_track_map%d_%d", tg,  m+100), Form("h_track_map%d_%d",tg,  m+100), 25, -50, 50, 25, -50, 50);
//		}
//		h_chi2_mod[m] = new TH1D(Form("h_chi2_mod%d", m+100), Form("h_chi2_mod%d", m+100), 100, 0, 100);
//		h_lg_t_mod[m] = new TH1D(Form("h_lg_t_mod%d", m+100), Form("h_lg_t_mod%d", m+100), 100, 50, 150);
//		h_tgt_pos_mod_raw[m] = new TH2D(Form("h_tgt_pos_mod_raw_%d", m+100), Form("h_tgt_pos_mod_raw_%d", m+100), 50, 19.8, 20.2, 60, -60, 60);
//		h_tgt_pos_mod_cut[m] = new TH2D(Form("h_tgt_pos_mod_cut_%d", m+100), Form("h_tgt_pos_mod_cut_%d", m+100), 50, 19.8, 20.2, 60, -60, 60);
//		h_tgt_proj_z_raw[m] = new TH1D(Form("h_tgt_proj_z_raw%d", m+100), Form("h_tgt_proj_z_raw%d", m+100), 100, -60, 60);
//		h_tgt_proj_z_cut[m] = new TH1D(Form("h_tgt_proj_z_cut%d", m+100), Form("h_tgt_proj_z_cut%d", m+100), 100, -60, 60);
//		h_tgt_proj_z_chi2cut[m] = new TH1D(Form("h_tgt_proj_z_chi2cut%d", m+100), Form("h_tgt_proj_z_chi2cut%d", m+100), 100, -45, 45);
//		h_tgt_proj_x[m] = new TH1D(Form("h_tgt_proj_x%d", m+100), Form("h_tgt_proj_x%d", m+100), 100, 19.8, 20.2);
//		h_tgt_proj_y[m] = new TH1D(Form("h_tgt_proj_y%d", m+100), Form("h_tgt_proj_y%d", m+100), 100, -5,5 );
//		for(int l=0; l < n_layer; l++){// -- layer 
//			for(int t=0; t < n_tgt; t++){
//				h_fitlx[t][m][l] = new TH1D(Form("h_fitlx_tgt%d_m%d_l%d",t, m+100, l), Form("h_fitlx_tgt%d_m%d_l%d",t, m+100, l), 100, -2, 2);
//				h_res_x[t][m][l] = new TH1D(Form("h_res_x_tgt%d_m%d_l%d",t, m+100, l), Form("h_res_x_tgt%d_m%d_l%d",t, m+100, l), 100, -2, 2);
//				h_res_y[t][m][l] = new TH1D(Form("h_res_y_tgt%d_m%d_l%d",t, m+100, l), Form("h_res_y_tgt%d_m%d_l%d",t, m+100, l), 100, -4, 4);
//				h_cor_res_fitlx[t][m][l] = new TH2D(Form("h_cor_res_fitlx_%d_%d_%d", t,m+100, l), Form("h_cor_res_fitlx_%d_%d%_d", t,m+100, l), 20, -50*l , 50*l, 100, -2, 2);
//				h_cor_res_fitly[t][m][l] = new TH2D(Form("h_cor_res_fitly_%d_%d_%d", t,m+100, l), Form("h_cor_res_fitly_%d_%d%_d", t,m+100, l), 20, -50*l , 50*l, 100, -2, 2);
//				h_cor_res_timing[t][m][l] = new TH2D(Form("h_cor_res_timing_%d_%d_%d", t,m+100, l), Form("h_cor_res_timing_%d_%d%_d", t,m+100, l), 20, 0 , 600, 100, -2, 2);
//			h_tan_theta[t][m][l] = new TH1D(Form("h_tan_theta_t%d_m%d_l%d", t, m+100, l), Form("h_tan_theta%d_%d_%d", t,m+100, l), 100, -0.5, 0.5);
//			for(int div = 0 ; div < n_div; div++){
//			h_cor_dz_time[t][m][l][div]        = new TH2D(Form("h_cor_dz_time_%d_%d%d%d",t,  m+100, l, div)      , Form("h_cor_dz_time_%d%d%d%d",t,  m+100, l, div)      , htdiv[m], 0, 600, hdzdiv[m], -8, 8);
//			h_cor_dz_time_t0cor[t][m][l][div] = new TH2D(Form("h_cor_dz_time_t0cor_%d%d_%d%d", t, m+100, l,div), Form("h_cor_dz_time_t0cor_%d%d%d%d",t, m+100, l,div), htdiv[m], 0, 600, hdzdiv[m], -8, 8);
//			h_slopevel[t][m][l][div] = new TH2D(Form("h_slopevel_%d%d_%d%d", t, m+100, l,div), Form("h_slopevel_%d%d%d%d",t, m+100, l,div),  25, -100, 100, 60, -2, 2);
//		}
//			}
//		}
//	}
//	int nevent = tree->GetEntries();
//#ifdef CHECK_100
//	int fixl   = 1; //gtr200
//#endif
//#ifdef CHECK_200
//	int fixl   = 2; //gtr200
//#endif
//#ifdef CHECK_300
//	int fixl   = 3; //gtr200
//#endif
//
//
//								//    00, 01, 02, 03, 04, 05,    06
//	double chi2_th[n_module] = {30, 30,30, 30, 30,   0,   30, 30, 30, 30};//mod100-109
//	double res_min[n_module] = {0, -4, -4, -4, -4,   0,   -4, -4, -4, -4};//mod100-109
//	double res_max[n_module] = {0,  4,  4,  4,  4,   0,    4,  4,  4,  4};//mod100-109
//	double timing_cut = 120;
//	double tgty_cut = 3.0;
//
//std::array<int, 4> mids;
//std::array<double, 4> resx;
//std::array<double, 4> resy;
//std::array<double, 4> fitlxs;
//std::array<double, 4> fitlys;
//std::array<double, 4> tans;//tan thetas
//std::array<double, 4> xt4s;//xt4
//
//	for(int n=0; n < nevent; n++){
//		if(n > n_maxevent) break;
//		if (n % print_cycle == 0) {
//			printf(" N Analyzed = %d \n", n);
//		} 
//		tree->GetEntry(n);
//		h_n_runid->Fill(run_id);
//		h_n_eventid->Fill(event_id);
//		h_n_spillid->Fill(spill_id);
//
//
//		int n_tracks = chi_square->size();//note that n tracks are judged with chi2 vec
//		for(int i=0; i < n_tracks; i++){
////			if(rk_fit_gtr100_mid->at(i) < 105 || rk_fit_gtr100_mid->at(i) > 107) continue;
//			double chi2  = chi_square->at(i);
//			int    mid   = rk_fit_gtr200_mid->at(i);
//			double sts_t = rk_hit_sts_t->at(i);
//			mids = {	rk_fit_sts_mid->at(i),
//						rk_fit_gtr100_mid->at(i),						
//						rk_fit_gtr200_mid->at(i),
//						rk_fit_gtr300_mid->at(i)};
//			resx = { rk_res_sts_x->at(i),
//						rk_res_gtr100_x->at(i),
//						rk_res_gtr200_x->at(i),
//						rk_res_gtr300_x->at(i)};
//			resy = { 0,
//						rk_res_gtr100_y->at(i),
//						rk_res_gtr200_y->at(i),
//						rk_res_gtr300_y->at(i)};
//			fitlxs   = { rk_fit_sts_x  ->at(i),
//			   		 rk_fit_gtr100_x->at(i),
//						 rk_fit_gtr200_x->at(i),
//						 rk_fit_gtr300_x->at(i)};
//			fitlys   = { 0,
//			   		 rk_fit_gtr100_y->at(i),
//						 rk_fit_gtr200_y->at(i),
//						 rk_fit_gtr300_y->at(i)};
//			tans = { rk_fit_sts_mom_x->at(i)/rk_fit_sts_mom_z->at(i),
//						rk_fit_gtr100_mom_x->at(i)/rk_fit_gtr100_mom_z->at(i),
//						rk_fit_gtr200_mom_x->at(i)/rk_fit_gtr200_mom_z->at(i),
//						rk_fit_gtr300_mom_x->at(i)/rk_fit_gtr300_mom_z->at(i)};
//			xt4s = { 0, 
//						rk_hit_gtr100_xt4->at(i),
//						rk_hit_gtr200_xt4->at(i),
//						rk_hit_gtr300_xt4->at(i)};
//			
//			double tgt_x = rk_fit_init_pos_gx->at(i);
//			double tgt_y = rk_fit_init_pos_gy->at(i);
//			double tgt_z = rk_fit_init_pos_gz->at(i);
//			double tdiff100 = rk_hit_gtr100_xt->at(i) - rk_hit_gtr100_yt->at(i);
//			double tdiff200 = rk_hit_gtr200_xt->at(i) - rk_hit_gtr200_yt->at(i);
//			double tdiff300 = rk_hit_gtr300_xt->at(i) - rk_hit_gtr300_yt->at(i);
//			h_chi2->Fill(chi2);
//			h_chi2_mod[mid-100]->Fill(chi2);
//			h_tgt_pos_mod_raw[mid-100]->Fill(rk_fit_init_pos_gx->at(i), rk_fit_init_pos_gz->at(i));
//			h_tgt_pos->Fill(rk_fit_init_pos_gx->at(i), rk_fit_init_pos_gz->at(i));
//			h_tgt_proj_z_raw[mid-100]->Fill(rk_fit_init_pos_gz->at(i));
//			bool lg_flag = true;//run0c wire
//			double smallest_lgt = 1000;
////			for(int j=0; j < rk_proj_lg_t->size(); j++) {
////				for( auto lgt : rk_proj_lg_t->at(j)){
////					h_lg_t_mod[mid-100]->Fill(lgt);
////					if(lgt > 0 ){ 
////					lg_flag = true;
////					if(smallest_lgt > lgt) smallest_lgt = lgt;
////					}
////				}
////			}
////			double t0diff = smallest_lgt - 88;//run0d
//			double t0diff =  sts_t;
//			
//// --- cut conditions --- //
//			if(chi2 > chi2_th[mid-100]) continue; //chi2_cut
//			h_tgt_proj_z_chi2cut[mid-100]->Fill(rk_fit_init_pos_gz->at(i));
//			if(fabs(tgt_y + 1) > tgty_cut) continue;
////			if(xt4s[l] < timing_cut) continue;
////			if(resx < res_min[mid-100]) continue;
////			if(resx > res_max[mid-100]) continue;
//			if(lg_flag) {
//				int tgtid;
//				if(tgt_z < 0) tgtid = 0;//up
//				if(tgt_z > 0) tgtid = 1;//down
//				for(int l=0; l < 4; l++){
//					
//					int ith_div = (fitlxs[l] + sideLen[l]/2 ) / (sideLen[l]/ n_div);	
//					
//					h_fitlx[tgtid][mids[l]-100][l]->Fill(fitlxs[l]);
//					h_res_x[tgtid][mids[l]-100][l]->Fill(resx[l]);
//					h_res_y[tgtid][mids[l]-100][l]->Fill(resy[l]);
//					h_cor_res_fitlx[tgtid][mids[l]-100][l]->Fill(fitlxs[l], resx[l]);	
//					h_cor_res_fitly[tgtid][mids[l]-100][l]->Fill(fitlys[l], resx[l]);	
//					h_cor_res_timing[tgtid][mids[l]-100][l]->Fill(xt4s[l], resx[l]);	//timing
//					h_tan_theta[tgtid][mids[l]-100][l]     ->Fill(tans[l]);
//					h_cor_dz_time[tgtid][mids[l]-100][l][ith_div]   ->Fill(xt4s[l], resx[l]/tans[l]);	
//					h_cor_dz_time_t0cor[tgtid][mid-100][l][ith_div] ->Fill(xt4s[l] - t0diff, resx[l]/tans[l]);//plus or minus?
//					h_slopevel[tgtid][mid-100][l][ith_div]->Fill((xt4s[l] - 250) * tans[l], resx[l] );
//				}
//				h_tgt_proj_x[mid-100]->Fill(rk_fit_init_pos_gx->at(i));
//				h_tgt_proj_y[mid-100]->Fill(rk_fit_init_pos_gy->at(i));
//				h_trackmap[tgtid][mid-100]->Fill(fitlxs[1], fitlys[1]);
//	//			if(fabs(rk_fit_init_pos_gx->at(i) + 1) > 4 ) continue;
//	//			if(fabs(tgt_y+ 1.5) >1.5 ) continue;
//	//			if(fabs(tdiff100-5) > 30) continue;
//	//			if(fabs(tdiff200-5) > 30) continue;
//	//			if(fabs(tdiff300-5) > 30) continue;
//	//			if(fabs(tan) > 0.08){
//	
//				h_tgt_pos_mod_cut[mid-100]->Fill(rk_fit_init_pos_gx->at(i), rk_fit_init_pos_gz->at(i));
//				h_tgt_proj_z_cut[mid-100]->Fill(rk_fit_init_pos_gz->at(i));
//	//			std::cout << "t0fiff " << t0diff << std::endl;
//				h_t0diff->Fill(t0diff);
////			}
//		}
//		}
//	}
//
//	TCanvas *c0 = new TCanvas();
//	c0->SaveAs(pdf_name + "[", "pdf");
//	gStyle->SetOptStat(1111111);
//	gStyle->SetOptFit(0111);
//
//	TCanvas *c00 = new TCanvas();
//	c00->Divide(2,2);
//	c00->cd(1);
//	h_n_runid->Draw();
//	c00->cd(2);
//	h_n_eventid->Draw();
//	c00->cd(3);
//	h_n_spillid->Draw();
//	c00->SaveAs(pdf_name, "pdf");
//
////module 106 focus
//	int fixm = 106;
//	TCanvas *c1 = new TCanvas();
//	c1->Divide(4,2);
//	for(int l=0; l < 4; l++){
//		c1->cd(l+1);
//		h_res_x[0][6][l]->Draw();
//		c1->cd(5+l);
//		h_res_x[1][6][l]->Draw();
//	}
//	c1->SaveAs(pdf_name, "pdf");
//
//	TCanvas *c200 = new TCanvas();
//	c200->Divide(4,2);
//	for(int l=0; l < 4; l++){
//		c200->cd(l+1);
//		h_fitlx[0][6][l]->Draw();
//		c200->cd(5+l);
//		h_fitlx[1][6][l]->Draw();
//	}
//	c200->SaveAs(pdf_name, "pdf");
//
//
//
//
//   TCanvas *c100 = new TCanvas();
//	c100->Divide(2,1);      
//   c100->cd(1); h_tgt_proj_z_raw[6]->Draw("colz"); c100->SaveAs(pdf_name, "pdf");
//	
//
//	 TCanvas *c310[2][10];
//    TGraphErrors *gr[2][10];
//    TGraphErrors *gr_mean[2][10];
//    TH1D *h1[10];
//    TF1 *f1[10];
//	 int hmid = 106;
//    c310[0][hmid-100] = new TCanvas();
//    c310[1][hmid-100] = new TCanvas();
//    c310[0][hmid-100]->Divide(5,5);
//    c310[1][hmid-100]->Divide(5,5);
//	 for(int t=0; t < 2; t++){
//    int n = h_cor_res_fitlx[t][hmid-100][fixl]->GetNbinsX();
//    double xmin = -2;
//    double xmax =  2;
//    std::cout << "nbins = " << n << std::endl;
//    gr[t][hmid-100] = new TGraphErrors(n);
//    gr_mean[t][hmid-100] = new TGraphErrors(n);
//     for (int i = 1; i <= n; i++) {
//       c310[t][hmid-100]->cd(i);
//        h1[hmid-100] = h_cor_res_fitlx[t][hmid-100][fixl]->ProjectionY(Form("_py%d%d", hmid, i), i, i     );
// //    f1[hmid-100] = new TF1(Form("f1%d%d",hmid, i), "gaus");
////       f1[hmid-100] = new TF1(Form("f%d", hmid), "gaus(0) + [3]+[4]*x+[5]*x*x+[6]*x*x*x",      xmin, xmax);
//       f1[hmid-100] = new TF1(Form("f%d", hmid), "gaus(0)",      xmin, xmax);
////       f1[hmid-100]->SetParameter(0, 500);   // constant
//       f1[hmid-100]->SetParameter(1, 0);     // mean
////       f1[hmid-100]->SetParLimits(1, -2, 2); // mean
////       f1[hmid-100]->SetParameter(2, 0.3);
////       f1[hmid-100]->SetParLimits(2, 0.1, 1);
////       f1[hmid-100]->SetParameter(3, 0);
////       f1[hmid-100]->SetParameter(4, -1);
//        h1[hmid-100]->Fit(f1[hmid-100], "", "", xmin, xmax);
//	     double mean = f1[hmid-100]->GetParameter(1);
//	     double mean_err = f1[hmid-100]->GetParError(1);
//       double sigma = f1[hmid-100]->GetParameter(2);
//        double sigma_err = f1[hmid-100]->GetParError(2);
//       std::cout << "sigma = " << sigma << std::endl;
//        gr[t][hmid-100]->SetPoint(i-1, -100 + 200/n * i + 200/n/2, sigma);
//        gr[t][hmid-100]->SetPointError(i-1, 0, sigma_err);
//        gr_mean[t][hmid-100]->SetPoint(i-1, -100+ 200/n * i + 200/n/2, mean);
//        gr_mean[t][hmid-100]->SetPointError(i-1, 0, mean_err);
//       h1[hmid-100]->Draw();
//    }
//          c310[t][hmid-100]->cd(24);
//			
//          gr[t][hmid-100]->Draw("AP");
//          c310[t][hmid-100]->cd(25);
//				gr_mean[t][hmid-100]->SetMaximum(1.0);
//				gr_mean[t][hmid-100]->SetMinimum(-1.0);
//				gr_mean[t][hmid-100]->SetLineStyle(0);
//          gr_mean[t][hmid-100]->Draw("AP");
//          c310[t][hmid-100]->SaveAs(pdf_name, "pdf");
//		}//target loop
//
//
//	 TCanvas *c311[2][10];
//    TGraphErrors *gry[2][10];
//    TGraphErrors *gry_mean[2][10];
//    TH1D *h1y[10];
//    TF1 *f1y[10];
//    c311[0][hmid-100] = new TCanvas();
//    c311[1][hmid-100] = new TCanvas();
//    c311[0][hmid-100]->Divide(5,5);
//    c311[1][hmid-100]->Divide(5,5);
//	 for(int t=0; t < 2; t++){
//    int n = h_cor_res_fitly[t][hmid-100][fixl]->GetNbinsX();
//    double xmin = -2;
//    double xmax =  2;
//    std::cout << "nbins = " << n << std::endl;
//    gry[t][hmid-100] = new TGraphErrors(n);
//    gry_mean[t][hmid-100] = new TGraphErrors(n);
//     for (int i = 1; i <= n; i++) {
//       c311[t][hmid-100]->cd(i);
//        h1y[hmid-100] = h_cor_res_fitly[t][hmid-100][fixl]->ProjectionY(Form("_pjy%d%d", hmid, i), i, i     );
//     f1y[hmid-100] = new TF1(Form("f1y%d%d",hmid, i), "gaus");
////       f1y[hmid-100] = new TF1(Form("f%d", hmid), "gaus(0) + [3]+[4]*x+[5]*x*x+[6]*x*x*x",      xmin, xmax);
//       f1y[hmid-100]->SetParameter(0, 500);   // constant
//       f1y[hmid-100]->SetParameter(1, 0);     // mean
//       f1y[hmid-100]->SetParLimits(1, -2, 2); // mean
//       f1y[hmid-100]->SetParameter(2, 0.3);
//       f1y[hmid-100]->SetParLimits(2, 0.1, 1);
//       f1y[hmid-100]->SetParameter(3, 0);
//       f1y[hmid-100]->SetParameter(4, -1);
//        h1y[hmid-100]->Fit(f1y[hmid-100], "", "", xmin, xmax);
//	     double mean = f1y[hmid-100]->GetParameter(1);
//	     double mean_err = f1y[hmid-100]->GetParError(1);
//       double sigma = f1y[hmid-100]->GetParameter(2);
//        double sigma_err = f1y[hmid-100]->GetParError(2);
//       std::cout << "sigma = " << sigma << std::endl;
//        gry[t][hmid-100]->SetPoint(i-1, -100 + 200/n * i + 200/n/2, sigma);
//        gry[t][hmid-100]->SetPointError(i-1, 0, sigma_err);
//        gry_mean[t][hmid-100]->SetPoint(i-1, -100+ 200/n * i + 200/n/2, mean);
//        gry_mean[t][hmid-100]->SetPointError(i-1, 0, mean_err);
//       h1y[hmid-100]->Draw();
//    }
//          c311[t][hmid-100]->cd(24);
//			
//          gry[t][hmid-100]->Draw("AP");
//          c311[t][hmid-100]->cd(25);
//				gry_mean[t][hmid-100]->SetMaximum(1.0);
//				gry_mean[t][hmid-100]->SetMinimum(-1.0);
//				gry_mean[t][hmid-100]->SetLineStyle(0);
//          gry_mean[t][hmid-100]->Draw("AP");
//          c311[t][hmid-100]->SaveAs(pdf_name, "pdf");
//		}//target loop
//
//
//	TCanvas *c333 = new TCanvas();
//	h_cor_res_timing[0][6][2]->Draw();
//	c333->SaveAs(pdf_name, "pdf");
//
//	 TCanvas *c31t[2][10];
//    TGraphErrors *grt[2][10];
//    TGraphErrors *grt_mean[2][10];
//    TH1D *h1t[10];
//    TF1 *f1t[10];
//    c31t[0][hmid-100] = new TCanvas();
//    c31t[1][hmid-100] = new TCanvas();
//    c31t[0][hmid-100]->Divide(5,5);
//    c31t[1][hmid-100]->Divide(5,5);
//	 for(int t=0; t < 2; t++){
//    int n = h_cor_res_timing[t][hmid-100][fixl]->GetNbinsX();
//    double xmin = -2;
//    double xmax =  2;
//    std::cout << "nbins = " << n << std::endl;
//    grt[t][hmid-100] = new TGraphErrors(n);
//    grt_mean[t][hmid-100] = new TGraphErrors(n);
//     for (int i = 1; i <= n; i++) {
//       c31t[t][hmid-100]->cd(i);
//        h1t[hmid-100] = h_cor_res_timing[t][hmid-100][fixl]->ProjectionY(Form("_pjt%d%d", hmid, i), i, i     );
//     f1t[hmid-100] = new TF1(Form("f1t%d%d",hmid, i), "gaus");
////       f1t[hmid-100] = new TF1(Form("f%d", hmid), "gaus(0) + [3]+[4]*x+[5]*x*x+[6]*x*x*x",      xmin, xmax);
//       f1t[hmid-100]->SetParameter(0, 500);   // constant
//       f1t[hmid-100]->SetParameter(1, 0);     // mean
//       f1t[hmid-100]->SetParLimits(1, -2, 2); // mean
//       f1t[hmid-100]->SetParameter(2, 0.3);
//       f1t[hmid-100]->SetParLimits(2, 0.1, 1);
//       f1t[hmid-100]->SetParameter(3, 0);
//       f1t[hmid-100]->SetParameter(4, -1);
//        h1t[hmid-100]->Fit(f1t[hmid-100], "", "", xmin, xmax);
//	     double mean = f1t[hmid-100]->GetParameter(1);
//	     double mean_err = f1t[hmid-100]->GetParError(1);
//       double sigma = f1t[hmid-100]->GetParameter(2);
//        double sigma_err = f1t[hmid-100]->GetParError(2);
//       std::cout << "sigma = " << sigma << std::endl;
//        grt[t][hmid-100]->SetPoint(i-1,   600/n * i + 600/n/2, sigma);
//        grt[t][hmid-100]->SetPointError(i-1, 0, sigma_err);
//        grt_mean[t][hmid-100]->SetPoint(i-1, 600/n * i + 600/n/2, mean);
//        grt_mean[t][hmid-100]->SetPointError(i-1, 0, mean_err);
//       h1t[hmid-100]->Draw();
//    }
//          c31t[t][hmid-100]->cd(24);
//			
//          grt[t][hmid-100]->Draw("AP");
//          c31t[t][hmid-100]->cd(25);
//				grt_mean[t][hmid-100]->SetMaximum(1.0);
//				grt_mean[t][hmid-100]->SetMinimum(-1.0);
//			 grt_mean[t][hmid-100]->SetLineStyle(0);
//          grt_mean[t][hmid-100]->Draw("AP");
//          c31t[t][hmid-100]->SaveAs(pdf_name, "pdf");
//		}//target loop
//
//
////
//
//	double msize = 0.4;
//	TCanvas *c312 = new TCanvas();
//	c312->Divide(2,2);
//	c312->cd(1);
//	gr[0][6]->SetTitle("residual vs local x  ");
//	gr[0][6]->GetYaxis()->SetTitle("residual sigma [mm]");
//	gr[0][6]->GetXaxis()->SetRangeUser(-100, 100);
//	gr[0][6]->GetXaxis()->SetTitle("local x [mm]");
//	gr[0][6]->SetMarkerStyle(20);
//	gr[1][6]->SetMarkerStyle(21);
//	gr[0][6]->SetMarkerSize(msize);
//	gr[1][6]->SetMarkerSize(msize);
//	gr[1][6]->SetMarkerColor(kRed);
//	gr[0][6]->Draw("AP");
//	gr[1][6]->SetLineColor(kRed);
//	gr[1][6]->Draw("P SAME");
//
//	c312->cd(2);
//	gry[0][6]->SetTitle("residual vs localy ");
//	gry[0][6]->GetYaxis()->SetTitle("residual sigma [mm]");
//	gry[0][6]->GetXaxis()->SetRangeUser(-100, 100);
//	gry[0][6]->GetXaxis()->SetTitle("local y [mm]");
//	gry[0][6]->SetMarkerStyle(20);
//	gry[1][6]->SetMarkerStyle(21);
//	gry[0][6]->SetMarkerSize(msize);
//	gry[1][6]->SetMarkerSize(msize);
//	gry[1][6]->SetMarkerColor(kRed);
//	gry[0][6]->Draw("AP");
//	gry[1][6]->SetLineColor(kRed);
//	gry[1][6]->Draw("P SAME");
//
//   c312->cd(3);
//	grt[0][6]->SetTitle("residual vs timing ");
//	grt[0][6]->GetYaxis()->SetTitle("residual sigma [mm]");
//	grt[0][6]->GetXaxis()->SetRangeUser(0, 600);
//	grt[0][6]->GetXaxis()->SetTitle("timing x [ns]");
//	grt[0][6]->SetMarkerStyle(20);
//	grt[1][6]->SetMarkerStyle(21);
//	grt[0][6]->SetMarkerSize(msize);
//	grt[1][6]->SetMarkerSize(msize);
//	grt[1][6]->SetMarkerColor(kRed);
//	grt[0][6]->Draw("AP");
//	grt[1][6]->SetLineColor(kRed);
//	grt[1][6]->Draw("P SAME");
//	c312->SaveAs(pdf_name, "pdf");
//
//	TCanvas *c313 = new TCanvas();
//	c313->Divide(2,2);
//	c313->cd(1);
//	gr_mean[0][6]->SetTitle("residual vs local x mean ");
//	gr_mean[0][6]->GetYaxis()->SetTitle("residual mean [mm]");
//	gr_mean[0][6]->GetXaxis()->SetRangeUser(-100, 100);
//	gr_mean[0][6]->GetXaxis()->SetTitle("local x [mm]");
//	gr_mean[0][6]->SetMarkerStyle(20);
//	gr_mean[1][6]->SetMarkerStyle(21);
//	gr_mean[1][6]->SetMarkerColor(kRed);
//	gr_mean[0][6]->SetMarkerSize(msize);
//	gr_mean[1][6]->SetMarkerSize(msize);
//	gr_mean[0][6]->Draw("AP");
//	gr_mean[1][6]->SetLineColor(kRed);
//	gr_mean[1][6]->Draw("P SAME");
//	c313->cd(2);
//	gry_mean[0][6]->SetTitle("residual vs localy mean ");
//	gry_mean[0][6]->GetYaxis()->SetTitle("residual mean [mm]");
//	gry_mean[0][6]->GetXaxis()->SetRangeUser(-100, 100);
//	gry_mean[0][6]->GetXaxis()->SetTitle("local y [mm]");
//	gry_mean[0][6]->SetMarkerStyle(20);
//	gry_mean[1][6]->SetMarkerStyle(21);
//	gry_mean[1][6]->SetMarkerColor(kRed);
//	gry_mean[0][6]->SetMarkerSize(msize);
//	gry_mean[1][6]->SetMarkerSize(msize);
//	gry_mean[0][6]->Draw("AP");
//	gry_mean[1][6]->SetLineColor(kRed);
//	gry_mean[1][6]->Draw("P SAME");
//	c313->cd(3);
//	grt_mean[0][6]->SetTitle("residual mean vs timing ");
//	grt_mean[0][6]->GetYaxis()->SetTitle("residual mean [mm]");
//	grt_mean[0][6]->GetXaxis()->SetRangeUser(0, 600);
//	grt_mean[0][6]->GetXaxis()->SetTitle("timing x [ns]");
//	grt_mean[0][6]->SetMarkerStyle(20);
//	grt_mean[1][6]->SetMarkerStyle(21);
//	grt_mean[1][6]->SetMarkerColor(kRed);
//	grt_mean[0][6]->SetMarkerSize(msize);
//	grt_mean[1][6]->SetMarkerSize(msize);
//	grt_mean[0][6]->Draw("AP");
//	grt_mean[1][6]->SetLineColor(kRed);
//	grt_mean[1][6]->Draw("P SAME");
//
//
//	c313->SaveAs(pdf_name, "pdf");
//
//
//	
//
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
//
//	TCanvas *chit = new TCanvas();
//	chit->Divide(8,2);
//	for(int i =1; i < 9; i++){
//      chit->cd(i);
//      if(i < 5) {
//         h_trackmap[0][i]->Draw("colz");
//			chit->cd(i+8);
//			h_trackmap[1][i]->Draw("colz");
//      }
//      else {
//         h_trackmap[0][i+1]->Draw("colz");
//			chit->cd(i+8);
//         h_trackmap[1][i+1]->Draw("colz");
//      }
//   }
//   chit->SaveAs(pdf_name, "pdf");
//
//	
//
//
//
//
//	TCanvas *c03a = new TCanvas();
//	c03a->Divide(4,2);
//	for(int i =1; i < 9; i++){
//      c03a->cd(i);
//      if(i < 5) {
//         h_tgt_pos_mod_raw[i]->Draw("colz");
//      }
//      else {
//         h_tgt_pos_mod_raw[i+1]->Draw("colz");
//      }
//   }
//   c03a->SaveAs(pdf_name, "pdf");
//
//	TCanvas *c03b = new TCanvas();
//	c03b->Divide(4,2);
//	for(int i =1; i < 9; i++){
//      c03b->cd(i);
//      if(i < 5) {
//         h_tgt_pos_mod_cut[i]->Draw("colz");
//      }
//      else {
//         h_tgt_pos_mod_cut[i+1]->Draw("colz");
//      }
//   }
//   c03b->SaveAs(pdf_name, "pdf");
//
//
//
//	TCanvas *c04 = new TCanvas();
//	c04->Divide(4,2);
//	for(int i =1; i < 9; i++){
//      c04->cd(i);
//      if(i < 5) {
//         h_tgt_proj_z_raw[i]->Draw("colz");
//      }
//      else {
//         h_tgt_proj_z_raw[i+1]->Draw("colz");
//      }
//   }
//   c04->SaveAs(pdf_name, "pdf");
//
//	TCanvas *c04c = new TCanvas();
//	c04c->Divide(4,2);
//	for(int i =1; i < 9; i++){
//      c04c->cd(i);
//      if(i < 5) {
//         h_tgt_proj_z_chi2cut[i]->Draw("colz");
//      }
//      else {
//         h_tgt_proj_z_chi2cut[i+1]->Draw("colz");
//      }
//   }
//   c04c->SaveAs(pdf_name, "pdf");
//
//
//	TCanvas *c04a = new TCanvas();
//	c04a->Divide(4,2);
//	for(int i =1; i < 9; i++){
//      c04a->cd(i);
//      if(i < 5) {
//         h_tgt_proj_z_cut[i]->Draw("colz");
//      }
//      else {
//         h_tgt_proj_z_cut[i+1]->Draw("colz");
//      }
//   }
//   c04a->SaveAs(pdf_name, "pdf");
//
//
//
//	TCanvas *c04x = new TCanvas();
//	c04x->Divide(4,2);
//	for(int i =1; i < 9; i++){
//      c04x->cd(i);
//      if(i < 5) {
//         h_tgt_proj_x[i]->Draw("colz");
//      }
//      else {
//         h_tgt_proj_x[i+1]->Draw("colz");
//      }
//   }
//   c04x->SaveAs(pdf_name, "pdf");
//
//	TCanvas *c04y = new TCanvas();
//	c04y->Divide(4,2);
//	for(int i =1; i < 9; i++){
//      c04y->cd(i);
//      if(i < 5) {
//         h_tgt_proj_y[i]->Draw("colz");
//      }
//      else {
//         h_tgt_proj_y[i+1]->Draw("colz");
//      }
//   }
//   c04y->SaveAs(pdf_name, "pdf");
//
////	TCanvas *c1 = new TCanvas();
////	c1->Divide(4,2);
////	for(int i =1; i < 9; i++){
////      c1->cd(i);
////      if(i < 5) {
////         h_res_x[i][fixl]->Draw("colz");
////      }
////      else {
////         h_res_x[i+1][fixl]->Draw("colz");
////      }
////   }
////   c1->SaveAs(pdf_name, "pdf");
////
////	TCanvas *c2 = new TCanvas();
////	c2->Divide(4,2);
////	for(int i =1; i < 9; i++){
////      c2->cd(i);
////      if(i < 5) {
////         h_res_y[i][fixl]->Draw("colz");
////      }
////      else {
////         h_res_y[i+1][fixl]->Draw("colz");
////      }
////   }
////   c2->SaveAs(pdf_name, "pdf");
////
////	TCanvas *c3 = new TCanvas();
////	c3->Divide(4,2);
////	for(int i =1; i < 9; i++){
////      c3->cd(i);
////      if(i < 5) {
////         h_tan_theta[t][i][fixl]->Draw("colz");
////      }
////      else {
////         h_tan_theta[i+1][fixl]->Draw("colz");
////      }
////   }
////   c3->SaveAs(pdf_name, "pdf");
//
//
//
//
////
////	TCanvas *c31[10];
////    TGraphErrors *gr[10];
////    TGraphErrors *gr_mean[10];
////    TH1D *h1[10];
////    TF1 *f1[10];
////    for(int hmid=101; hmid < 110; hmid++){
////       if(hmid == 105)continue;
////             c31[hmid-100] = new TCanvas();
////             c31[hmid-100]->Divide(4,3);
////             int n = h_cor_res_fitlx[0][hmid-100][fixl]->GetNbinsX();
////             double xmin = -2;
////             double xmax =  2;
////             std::cout << "nibs = " << n << std::endl;
////             gr[hmid-100] = new TGraphErrors(n);
////             gr_mean[hmid-100] = new TGraphErrors(n);
////              for (int i = 1; i <= n; i++) {
////                c31[hmid-100]->cd(i);
////                 h1[hmid-100] = h_cor_res_fitlx[0][hmid-100][fixl]->ProjectionY(Form("_py%d%d", hmid, i), i, i     );
//// //             f1[hmid-100] = new TF1(Form("f1%d%d",hmid, i), "gaus");
////                f1[hmid-100] = new TF1(Form("f%d", hmid), "gaus(0) + [3]+[4]*x+[5]*x*x+[6]*x*x*x",      xmin, xmax);
////                f1[hmid-100]->SetParameter(0, 500);   // constant
////                f1[hmid-100]->SetParameter(1, 0);     // mean
////                f1[hmid-100]->SetParLimits(1, -2, 2); // mean
////                f1[hmid-100]->SetParameter(2, 0.3);
////                f1[hmid-100]->SetParLimits(2, 0.1, 1);
////                f1[hmid-100]->SetParameter(3, 0);
////                f1[hmid-100]->SetParameter(4, -1);
////                 h1[hmid-100]->Fit(f1[hmid-100], "", "", xmin, xmax);
////					  double mean = f1[hmid-100]->GetParameter(1);
////					  double mean_err = f1[hmid-100]->GetParError(1);
////                double sigma = f1[hmid-100]->GetParameter(2);
////                 double sigma_err = f1[hmid-100]->GetParError(2);
////                std::cout << "sigma = " << sigma << std::endl;
////                 gr[hmid-100]->SetPoint(i-1, i, sigma);
////                 gr[hmid-100]->SetPointError(i-1, 0, sigma_err);
////                 gr_mean[hmid-100]->SetPoint(i-1, i, mean);
////                 gr_mean[hmid-100]->SetPointError(i-1, 0, mean_err);
////                h1[hmid-100]->Draw();
////             }
////          c31[hmid-100]->cd(11);
////          gr[hmid-100]->Draw();
////          c31[hmid-100]->cd(12);
////				gr_mean[hmid-100]->SetMaximum(0.2);
////				gr_mean[hmid-100]->SetMinimum(-0.2);
////				gr_mean[hmid-100]->SetLineStyle(0);
////				
////          gr_mean[hmid-100]->Draw();
////          c31[hmid-100]->SaveAs(pdf_name, "pdf");
////    }
////
//
////   TCanvas *c6 = new TCanvas();
////   c6->Divide(4,2);
////   for(int i =1; i < 9; i++){
////      c6->cd(i);
////      if(i < 5) {
////         h_cor_dz_time[i][fixl]->Draw("colz");
////      }
////      else {
////         h_cor_dz_time[i+1][fixl]->Draw("colz");
////      }
////   }
////   c6->SaveAs(pdf_name, "pdf");
////
////    TCanvas *c16[2][10];
////    TGraphErrors *gr16[2][10];
////    TH1D *h16[2][10];
////    TF1  *f16[2][10];
////    TF1  *fla[2][10];
////    double xmin[10]  = {0, -7, -7, -7,     -6, 0, -6.5, -5.5, -7, -7};//mod100-109
////    double xmax[10]  = {0, 10, 10, 10,    5.5, 0,    2,  4.0,  8,  8};
////	 double flmin[10] = {0, 120, 120, 120, 120, 0, 120, 100, 180, 180};
////	 double flmax[10] = {0, 450, 450, 450, 450, 0, 530, 450, 550, 450};
////	 for(int t=0; t < 2; t++){
////    for(int hmid=101; hmid < 110; hmid++){
////       if(hmid != 106)continue;
////       c16[t][hmid-100] = new TCanvas();
////       int n = h_cor_dz_time[t][hmid-100][fixl]->GetNbinsX();
////       c16[t][hmid-100]->Divide(5,5);
////       std::cout << "nbins dz = " << n << std::endl;
////       gr16[t][hmid-100] = new TGraphErrors(n);
////		 gr16[t][hmid-100]->SetMaximum( 8.0);
////		 gr16[t][hmid-100]->SetMinimum(-8.0);
////        for (int i = 1; i <= n; i++) {
////          c16[t][hmid-100]->cd(i);
////          fla[t][hmid-100] = new TF1(Form("fla%d", hmid), "pol1", flmin[hmid-100], flmax[hmid-100]);
////          h16[t][hmid-100] = h_cor_dz_time[t][hmid-100][fixl]->ProjectionY(Form("_py%d%d", hmid, i), i, i);
////          //f16[hmid-100] = new TF1(Form("f16%d%d",hmid, i), "landau");
//// //       f16[hmid-100] = new TF1("fitFunction", "gaus(0) + [3]*exp(-[4]*(x-[5])  )", xmin, xmax);
//// //       f16[hmid-100] = new TF1("fitFunction", "gaus(0)+[3]+[4]*x+[5]*x*x+[6]*x*x*x", xmin,xmax);
////          //f16[hmid-100]->SetParNames("Constant", "Mean", "Sigma", "Slope", "X0");
//////          f16[hmid-100] = new TF1("fitFunction", "gaus(0)+[3]+[4]*x+[5]*x*x", xmin[hmid-100],xmax[hmid-100]);
////          f16[t][hmid-100] = new TF1("fitFunction", "gaus(0)+[3]*x", xmin[hmid-100],xmax[hmid-100]);
//// //       f16[hmid-100] = new TF1("fitFunction", "[0]*exp(-0.5*((x-[1])/[2])**2) + [3]*TMath::Erfc([4]*(x-[5]))", xmin, xmax);
//// //       f16[hmid-100]->SetParNames("Constant", "Mean", "Sigma", "TailHeight", "TailSlope","TailX0");
////          f16[t][hmid-100]->SetParameter(0, 20); // constant
////          f16[t][hmid-100]->SetParameter(1, 0);     // mean
////          f16[t][hmid-100]->SetParameter(2, 10);    // sigma
////          f16[t][hmid-100]->SetParLimits(2, 1, 10);
////          f16[t][hmid-100]->SetParameter(3, 0);    
//////          f16[hmid-100]->SetParLimits(3, -0.8, 0);
//////          f16[hmid-100]->SetParameter(4, -1);    
//////          f16[hmid-100]->SetParameter(4, -0.5);  
////           h16[t][hmid-100]->Fit(f16[t][hmid-100], "", "", xmin[hmid-100], xmax[hmid-100]);
////
////           double chi2 = f16[t][hmid-100]->GetChisquare();
////          double mean =  f16[t][hmid-100]->GetParameter(1);
////           double sigma_err = f16[t][hmid-100]->GetParError(2);
////          std::cout << "mod, fit chi2  = " << hmid  << ", "  << chi2 << std::endl;
////          if(chi2 < 5) continue;
////          if(sigma_err > 10) continue;
////           gr16[t][hmid-100]->SetPoint(i-1, i*(600/n), mean);
////           gr16[t][hmid-100]->SetPointError(i-1, 0, sigma_err);
////           gr16[t][hmid-100]->Fit(fla[t][hmid-100], "R");
////           h16[t][hmid-100]->Draw();
////       }
////          c16[t][hmid-100]->cd(6);
////          c16[t][hmid-100]->SaveAs(pdf_name, "pdf");
////		}
////    }
//////
//////
////    TCanvas *c17[2];
////	for(int t=0; t < 2; t++){
////	 c17[t]= new TCanvas();
////    c17[t]->Divide(4,2);
////    for(int hmid=101; hmid < 110; hmid++){
////       if(hmid!=106) continue;
////       if(hmid < 105) {c17[t]->cd(hmid-100);}
////		 else {c17[t]->cd(hmid-101);}
////       gr16[t][hmid-100]->SetTitle(Form("residual/tan_theta tgt%d  mod%d : timing ;  timing; residual/tan_theta", t, hmid) );
////       gr16[t][hmid-100]->Draw("AP");
////    }
////   c17[t]->SaveAs(pdf_name, "pdf");
////	}
////
//
////
////  TCanvas *c6b = new TCanvas();
////  c6b->Divide(2,2);
////  for(int tgt=0; tgt<2; tgt++){
////  for(int i =1; i < 9; i++){
////	  
////     c6b->cd(i);
////     if(i < 5) {
////        h_cor_dz_time_t0cor[tgt][i][fixl]->Draw("colz");
////     }
////     else {
////        h_cor_dz_time_t0cor[tgt][i+1][fixl]->Draw("colz");
////     }
////  }
////	}
////  c6b->SaveAs(pdf_name, "pdf");
////
////
//
//   TCanvas *c16b[2][10][n_div];
//   TGraphErrors *gr16b[2][10][n_div];
//   TH1D *h16b[2][10][n_div];
//   TF1 *f16b[2][10][n_div];
//   TF1 *flab[2][10][n_div];
//#ifdef CALIB
//   double xminb[10]  = {0, -4, -7, -7,     -6, 0, -2, -5.5, -4, -4};//mod100-109
//   double xmaxb[10]  = {0,  4, 10, 10,    5.5, 0,  2,  4.0,  5,  5};
//#else 
//   double xminb[10]  = {0, -4, -7, -7,     -6, 0, -4, -5.5, -4, -4};//mod100-109
//   double xmaxb[10]  = {0,  4, 10, 10,    5.5, 0,   4,  4.0,  5,  5};
//#endif
//   double flminb[10] = {0, 120, 120, 120, 120, 0, 200, 120, 100, 180};
//   double flmaxb[10] = {0, 450, 450, 450, 450, 0, 550, 450, 320, 450};
//	for(int t=0; t < 2; t++){
//		int hmid = 106;
//		for(int d=0 ; d < n_div; d++){
//      c16b[t][hmid-100][d] = new TCanvas();
//      int n = h_cor_dz_time_t0cor[t][hmid-100][fixl][d]->GetNbinsX();
//      c16b[t][hmid-100][d]->Divide(5,5);
//      std::cout << "nbins dz = " << n << std::endl;
//      gr16b[t][hmid-100][d] = new TGraphErrors(n);
//   	gr16b[t][hmid-100][d]->SetMaximum( 8.0);
//	   gr16b[t][hmid-100][d]->SetMinimum(-8.0);
//       for (int i = 1; i <= n; i++) {
//         c16b[t][hmid-100][d]->cd(i);
//         flab[t][hmid-100][d] = new TF1(Form("fla%d%d", t, d), "pol1", flminb[hmid-100], flmaxb[hmid-100]);
//         h16b[t][hmid-100][d] = h_cor_dz_time_t0cor[t][hmid-100][fixl][d]->ProjectionY(Form("_py%d%d%d", hmid, i), i, i);
////         f16b[t][hmid-100][d] = new TF1("fitFunction", "gaus(0)+[3]+[4]*x+[5]*x*x", xminb[hmid-100],xmaxb[hmid-100]);
////         f16b[t][hmid-100][d] = new TF1(Form("fitFunction%d%d", t, d), "gaus(0)+[3]*x*x", xminb[hmid-100],xmaxb[hmid-100]);
//         f16b[t][hmid-100][d] = new TF1("fitFunction", "gaus(0)+[3]*x", xminb[hmid-100],xmaxb[hmid-100]);
////       f16b[hmid-100] = new TF1("fitFunction", "[0]*exp(-0.5*((x-[1])/[2])**2) + [3]*TMath::Erfc([4]*(x-[5]))", xmin, xmax);
////       f16b[hmid-100]->SetParNames("Constant", "Mean", "Sigma", "TailHeight", "TailSlope","TailX0");
//         f16b[t][hmid-100][d]->SetParameter(0, 20); // constant
//         f16b[t][hmid-100][d]->SetParameter(1, 0);     // mean
//         f16b[t][hmid-100][d]->SetParameter(2, 3);    // sigma
////         f16b[t][hmid-100][d]->SetParameter(3, 0);    
////         f16b[t][hmid-100][d]->SetParameter(4, -1);    
////         f16b[t][hmid-100][d]->SetParameter(4, -0.5);  
//         h16b[t][hmid-100][d]->Fit(f16b[t][hmid-100][d], "", "", xminb[hmid-100], xmaxb[hmid-100]);
//
//          double chi2 = f16b[t][hmid-100][d]->GetChisquare();
//         double mean = f16b[t][hmid-100][d]->GetParameter(1);
//          double sigma_err = f16b[t][hmid-100][d]->GetParError(2);
//         std::cout << "mod, fit chi2  = " << hmid  << ", "  << chi2 << std::endl;
//         if(chi2 < 5) continue;
//         if(sigma_err > 10) continue;
//          gr16b[t][hmid-100][d]->SetPoint(i-1, i*(600/n), mean);
//          gr16b[t][hmid-100][d]->SetPointError(i-1, 0, sigma_err);
//          gr16b[t][hmid-100][d]->Fit(flab[t][hmid-100][d], "R");
//          h16b[t][hmid-100][d]->Draw();
//      }
//         c16b[t][hmid-100][d]->cd(6);
//         c16b[t][hmid-100][d]->SaveAs(pdf_name, "pdf");
//   	}
//	}
//
//
//	TCanvas *c0d = new TCanvas();
//	h_t0diff->Draw();
//	c0d->SaveAs(pdf_name, "pdf");
//
//    TCanvas *c17b[2];
//		for(int t=0; t < 2; t++){
//		 	c17b[t] = new TCanvas();
//   	 	c17b[t]->Divide(5,4);
//			for(int d=0; d < n_div; d++){
//				c17b[t]->cd(d+1);
//		      gr16b[t][6][d]->SetTitle(Form("residual/tan_theta tgt%d mod 106 : timing_lg ;  timing_lg; residual/tan_theta", t) );
//	   	   gr16b[t][6][d]->Draw("AP");
//				
//			}
//	 	c17b[t]->SaveAs(pdf_name, "pdf");
//	  }
//
//
//    TCanvas *c18[2];
//	 TGraphErrors *tg18[2];
//		for(int t=0; t < 2; t++){
//			c18[t] = new TCanvas();
//			tg18[t] = new TGraphErrors(n_div);
//			for(int d=0; d < n_div; d++){
//				double tilt = flab[t][6][d]->GetParameter(1);
//				tg18[t]->SetPoint(d, d, tilt);
//			}
////			tg18[t]->SetMarkerSize(msize);
//			tg18[t]->Draw("AP");
//	 c18[t]->SaveAs(pdf_name, "pdf");
//	  }
//
//
//    TCanvas *c19[2];
//		for(int t=0; t < 2; t++){
//			c19[t] = new TCanvas();
//			c19[t]->Divide(4,5);
//			for(int d=0; d < n_div; d++){
//				c19[t]->cd(d+1);
//				h_slopevel[t][6][fixl][d]->Draw("colz");
//			}
//	 	c19[t]->SaveAs(pdf_name, "pdf");
//	  }
//
//
//		
//
//
//
//		c0->SaveAs(pdf_name + "]", "pdf");
//}
//
//
//
//void E16DSTN_ReadStraightTree::HistFit(TCanvas *c, ){
//   TCanvas *c16b[2][10];
//   TGraphErrors *gr16b[2][10];

