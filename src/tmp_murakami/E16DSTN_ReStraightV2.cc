#define E16DSTN_ReStraightV2_cxx
#include "E16DSTN_ReStraightV2.hh"
#include "E16ANA_StraightTrackParameter.hh"
#include "E16DSTN_ReStraightParameter.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TRotation.h>
#include <TMatrixD.h>


//using namespace E16ANA_StraightTrackParameter;
using namespace E16ANA_StraightTrackConstant;
using namespace E16DSTN_ReStraightParameter;

void E16DSTN_ReStraightV2::ChiSqSort( std::vector<int> &in_ids, std::vector<int> &sorted_ids){
	int n_tracks = in_ids.size();
	std::multimap<double, int> chi2_trkid_map;
	chi2_trkid_map.clear();
	for(int i=0; i < n_tracks; i++){
		int id = in_ids[i];//track_id
 		chi2_trkid_map.insert(std::make_pair(chi_square->at(id), id));
	}
	for(const auto &el : chi2_trkid_map){
		sorted_ids.push_back(el.second);
	}
}

void E16DSTN_ReStraightV2::SelectTracks(std::vector<int> &sorted_ids, std::vector<int> &selected_ids){
	for(int i=0; i < n_cands; i++){
//		if(IsRealTrack(i)){
//			if(IsGoodTrack(i)){
				selected_ids.emplace_back(i);
//			}
//		}
	}
}

bool E16DSTN_ReStraightV2::IsGoodTrack(const int id){
	//LG matching
	bool flag = false;
	for(int i=0 ; i < rk_proj_n_lg->at(id); i++){
		double lg_t = rk_proj_lg_t->at(id)[i];
		if(lg_t >  0){
			flag = true;
		}
	}
	return flag;
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

//void E16DSTN_ReStraightV2::DuplicationClusterCut(std::vector<int> &selected_ids, std::vector<int> &killdup_ids){
//	int n_selected_ids = selected_ids.size();
//	for(int i=0; i < n_selected_ids ; i++){
////		std::cout << "i " << i << std::endl;
////		std::cout << "sts id  = " << rk_hit_sts_id->at(i);
//			std::array<int, 3> cids = {
//			rk_hit_sts_id->at(i), 
//			rk_hit_gtr100_xid->at(i), rk_hit_gtr100_yid->at(i)};
////			rk_hit_gtr200_xid->at(i), rk_hit_gtr200_yid->at(i),
////			rk_hit_gtr300_xid->at(i), rk_hit_gtr300_yid->at(i)};
//// 			std::cout << "ids (" << rk_hit_sts_id->at(i)   
////			 << ", " << rk_hit_gtr100_xid->at(i) 
////			 << ", " << rk_hit_gtr200_xid->at(i) 
////			 << ", " << rk_hit_gtr300_xid->at(i) 
////			 << ", " << rk_hit_gtr100_yid->at(i) 
////			 << ", " << rk_hit_gtr200_yid->at(i) 
////			 << ", " << rk_hit_gtr300_yid->at(i) << std::endl;
//         if(HasUsedCluster(cids, used_cluster_ids)){
////			std::cout << "duplicated !" << std::endl;
//			continue;			
//			} else {
////				std::cout << "NOT duplicated !" << std::endl;
//				for (int j=0; j  <  3;j++){
//					used_cluster_ids[j].emplace_back(cids[j]);
//				}
//			killdup_ids.emplace_back(i);
//			}
//    }
//}

#ifndef WIRE_STS_TRACK
void E16DSTN_ReStraightV2::DuplicationClusterCut(std::vector<int> &selected_ids, std::vector<int> &killdup_ids){
	int n_selected_ids = selected_ids.size();
#ifdef REMOVE_NOLAYER // all layer exist
	for(int i=0; i < n_selected_ids ; i++){
			int tid = selected_ids[i];
			std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips> cids = {
			rk_hit_sts_id->at(tid),
			rk_hit_gtr100_xid->at(tid), rk_hit_gtr100_yid->at(tid),
			rk_hit_gtr200_xid->at(tid), rk_hit_gtr200_yid->at(tid),
			rk_hit_gtr300_xid->at(tid), rk_hit_gtr300_yid->at(tid)};
// 			std::cout << "ids (" << rk_hit_sts_id->at(i)   
//			 << ", " << rk_hit_gtr100_xid->at(i) 
//			 << ", " << rk_hit_gtr200_xid->at(i) 
//			 << ", " << rk_hit_gtr300_xid->at(i) 
//			 << ", " << rk_hit_gtr100_yid->at(i) 
//			 << ", " << rk_hit_gtr200_yid->at(i) 
//			 << ", " << rk_hit_gtr300_yid->at(i) << std::endl;
         if(HasUsedCluster(cids, used_cluster_ids)){
//			std::cout << "duplicated !" << std::endl;
			continue;			
			} else {
//				std::cout << "NOT duplicated !" << std::endl;
				for (int j=0; j  <  E16ANA_StraightTrackConstant::kNumTrackingStrips;j++){
					used_cluster_ids[j].emplace_back(cids[j]);
				}
			killdup_ids.emplace_back(tid);
			}
    }

#else//
	#ifdef NoExist_SSD
	 for(int i=0; i < n_selected_ids ; i++){
			int tid = selected_ids[i];
			std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips -1 > cids = {
			rk_hit_gtr100_xid->at(tid), rk_hit_gtr100_yid->at(tid),
			rk_hit_gtr200_xid->at(tid), rk_hit_gtr200_yid->at(tid),
			rk_hit_gtr300_xid->at(tid), rk_hit_gtr300_yid->at(tid)};
         if(HasUsedCluster(cids, used_cluster_ids)){
				continue;			
			} else {
				for (int j=0; j  <  E16ANA_StraightTrackConstant::kNumTrackingStrips-1;j++){
					used_cluster_ids[j].emplace_back(cids[j]);
				}
			killdup_ids.emplace_back(tid);
			}
    }
    #elif REMOVE_GTR100
    for(int i=0; i < n_selected_ids ; i++){
			int tid = selected_ids[i];
			std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips -2 > cids = {
			rk_hit_sts_id->at(tid),
			rk_hit_gtr200_xid->at(tid), rk_hit_gtr200_yid->at(tid),
			rk_hit_gtr300_xid->at(tid), rk_hit_gtr300_yid->at(tid)};
         if(HasUsedCluster(cids, used_cluster_ids)){
				continue;			
			} else {
				for (int j=0; j  <  E16ANA_StraightTrackConstant::kNumTrackingStrips-2;j++){
					used_cluster_ids[j].emplace_back(cids[j]);
				}
			killdup_ids.emplace_back(tid);
			}
    }
    #elif REMOVE_GTR200
    for(int i=0; i < n_selected_ids ; i++){
			int tid = selected_ids[i];
			std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips -2 > cids = {
			rk_hit_sts_id->at(tid),
			rk_hit_gtr100_xid->at(tid), rk_hit_gtr100_yid->at(tid),
			rk_hit_gtr300_xid->at(tid), rk_hit_gtr300_yid->at(tid)};
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
			killdup_ids.emplace_back(tid);
			}
    }
     #elif REMOVE_GTR300
    for(int i=0; i < n_selected_ids ; i++){
			int tid = selected_ids[i];
			std::array<int, E16ANA_StraightTrackConstant::kNumTrackingStrips -2 > cids = {
			rk_hit_sts_id->at(tid),
			rk_hit_gtr100_xid->at(tid), rk_hit_gtr100_yid->at(tid),
			rk_hit_gtr200_xid->at(tid), rk_hit_gtr200_yid->at(tid)};
         if(HasUsedCluster(cids, used_cluster_ids)){
				continue;			
			} else {
				for (int j=0; j  <  E16ANA_StraightTrackConstant::kNumTrackingStrips-2;j++){
					used_cluster_ids[j].emplace_back(cids[j]);
				}
			killdup_ids.emplace_back(tid);
			}
    }
#endif // 
#endif //
}
#endif


void E16DSTN_ReStraightV2::Loop(TTree* tree, int print_cycle, int event_start, int event_end, bool vertex_xy_fix_flag, bool py_fix_flag, bool vetex_z_fix_flag )
{
//   if (fChain == 0) return;
//   Long64_t nevent = fChain->GetEntries();
//   std::cout << "nevent = " << nevent << std::endl;
//   Long64_t nbytes = 0, nb = 0;
//   for(int n=0; n < nevent ; n++){
//		if(n < event_start) continue;
//		if(n > event_end){
//			std::cout << "N event analyzed readched to event_end that you decide" << std::endl;
//		   break;	
//      }
//      if( n% print_cycle == 0 ){
//         printf( "N analyzed = %d \n ", n);
//      }
//      tree->GetEntry(n);
//      std::vector<int> out_ids;
//      std::vector<int> sorted_ids;
//      std::vector<int> selected_ids;
//      std::vector<int> killdup_ids;
//      out_ids.clear();
//		sorted_ids.clear();
//		selected_ids.clear();
//		killdup_ids.clear();
////      std::cout << "n_cands = " << n_cands << std::endl;
// 	ChiSqSort(sorted_ids);
// 	SelectTracks(sorted_ids, selected_ids);
////	   std::cout << "n of selected tracks = " << selected_ids.size() << std::endl;
// 	ClearUsedClusterIDs();
// 	DuplicationClusterCut(selected_ids, killdup_ids);
////	   std::cout << "n of duplication cut tracks = " << killdup_ids.size() << std::endl;
////		AnalyzeTrackPairs(killdup_ids);
//	 	AddRecord(tree,  killdup_ids);
//   }
}

#ifdef WIRE_STS_TRACK
void E16DSTN_ReStraightV2::DuplicationClusterCutForWire(std::vector<int> &in_ids, std::vector<int> &out_ids){
	int n_in_ids = in_ids.size();
	for(int i=0; i < n_in_ids ; i++){
			int tid = in_ids[i];
			std::array<int, n_kill_strips> cids = {
			rk_hit_sts_id->at(tid),
		rk_hit_gtr100_xid->at(tid)
//		rk_hit_gtr100_yid->at(tid),
//		rk_hit_gtr200_xid->at(tid)
//		rk_hit_gtr200_yid->at(tid),
//	rk_hit_gtr300_xid->at(tid)
//		rk_hit_gtr300_yid->at(tid)
			};
	
			if(HasUsedClusterForWire(cids, used_cid_sets)){//combination match
			continue;			
			} else {
				used_cid_sets.emplace_back(cids);
				out_ids.emplace_back(tid);
			}
    }
}
#endif



void E16DSTN_ReStraightV2::ReTrackingAndDuplicationCut(TTree* tree, int print_cycle, int event_start, int event_end, bool vertex_xy_fix_flag, bool py_fix_flag, bool vertex_z_fix_flag, int target_mid){
   if (fChain == 0) return;
   Long64_t nevent = fChain->GetEntries();
   std::cout << "nevent = " << nevent << std::endl;
   Long64_t nbytes = 0, nb = 0;
   for(int n=0; n < nevent ; n++){
		if(n < event_start) continue;
		if(n > event_end){
			std::cout << "N event analyzed readched to event_end that you decide" << std::endl;
		   break;	
      }
      if( n% print_cycle == 0 ){
         printf( "N analyzed = %d \n ", n);
      }
      tree->GetEntry(n);
		std::vector<int> alive_ids;
		alive_ids.clear();

		std::vector<int> fit_ids;
		fit_ids.clear();

		std::vector<int> sorted_ids;
		sorted_ids.clear();
		std::vector<int> killdup_ids;
		killdup_ids.clear();
		
		std::vector<int> in_ids;
		in_ids.clear();
		
//for GTR100
//		for(int i = 0; i < n_cands; i++){
//			in_ids.push_back(i);
//		}
//		ClearUsedClusterIDs();
//		ChiSqSort(in_ids, sorted_ids);
//		DuplicationClusterCutForWire(sorted_ids, killdup_ids);
//
//		for(int i=0; i < killdup_ids.size(); i++){
//			int itk = killdup_ids[i];//i th track
//		---- for GTR100
		for(int i=0; i < n_cands; i++){
			int itk =  i; //track id
//module matching 
			int mid_sts = rk_fit_sts_mid->at(itk);
			int mid_gtr100 = rk_fit_gtr100_mid->at(itk);
			int mid_gtr200 = rk_fit_gtr200_mid->at(itk);
			int mid_gtr300 = rk_fit_gtr300_mid->at(itk);
			if(mid_sts    != target_mid) continue;
			if(mid_gtr100 != target_mid) continue;
			if(mid_gtr200 != target_mid) continue;
//			if(mid_gtr300 != target_mid) continue;
//timing correlation cut
			double tdiff100 = rk_hit_gtr100_xt4->at(itk) - rk_hit_gtr100_yt->at(itk);	
			double tdiff200 = rk_hit_gtr200_xt4->at(itk) - rk_hit_gtr200_yt->at(itk);	
			double tdiff300 = rk_hit_gtr300_xt4->at(itk) - rk_hit_gtr300_yt->at(itk);	
			if(fabs(tdiff100-5.0) >  20) continue; 
			if(fabs(tdiff200-9.0) >  25) continue; 
			if(fabs(tdiff300-5.0) >  25) continue; 

			double chi2 = chi_square->at(itk);
			if(chi2 < E16DSTN_ReStraightParameter::kchi2_threshold){
				Fit(itk, fitter, vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag);
				fit_ids.push_back(itk);	
			}
   	}
		ClearUsedClusterIDs();
		ChiSqSort(fit_ids, sorted_ids);
#ifdef WIRE_STS_TRACK
		DuplicationClusterCutForWire(sorted_ids, alive_ids);
#else
		DuplicationClusterCut(sorted_ids, alive_ids);
#endif
		AnalyzeTrackPairs(alive_ids);
	 	AddRecord(tree, alive_ids);
      if( n% print_cycle == 0 ){
      }
	}
}

double E16DSTN_ReStraightV2::Fit(int itk, E16ANA_StraightMultiTrack* fitter, bool vertex_xy_fix_flag,  bool py_fix_flag, bool vertex_z_fix_flag){
	fitter->Clear();
	this->AddTrackHit(itk, fitter);
	fitter->SetRungeKuttaStepSize(5.0);
	fitter->SetMaxSteps(80);
	double chisq = fitter->Fit(vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag, 0, 1.0e3);
	UpdateFitResult(itk, fitter, chisq);
	return chisq;
}

void E16DSTN_ReStraightV2::UpdateFitResult(int itk, E16ANA_StraightMultiTrack *fitter, double chisq){
	int tid = 0;
	for(int l=0; l < 4; l++){
		#ifdef NoExist_SSD
		if(l == 0 ) continue;
		#endif
		std::vector<TVector3> fit_lpos;
      std::vector<TVector3> fit_lmom;
      std::vector<int> mid;
      fitter->GetFitLPos(0, l, mid, fit_lpos);
      fitter->GetFitLMom(0, l, mid, fit_lmom);
      TVector3 gpos;
      TVector3 gmom;
      auto mid2020 = E16ANA_StraightTrackConstant::ModuleID2013To2020(mid[0]);
//      if (l <= E16ANA_StraightTrackConstant::kSSD) {
//        gpos = geometry->STS(mid[tid])->GetGPos(fit_lpos[tid]);//maybe geometry should be geom_temp
//        gmom = geometry->STS(mid[tid])->GetGMom(fit_lmom[tid]);
//      } else {
//        gpos = geometry->GTR(mid[tid], l - 1)->GetGPos(fit_lpos[tid]);
//        gmom = geometry->GTR(mid[tid], l - 1)->GetGMom(fit_lmom[tid]);
        gpos = geom_temp[l]->GetGPos(fit_lpos[tid]);
        gmom = geom_temp[l]->GetGMom(fit_lmom[tid]);
//      }
      auto res_pos  = CorrectedLocalPos( tid, mid[tid] ,l ) - fit_lpos[tid];
//    std::cout  << "layer, rpos Mag  "  << l << ", " << rpos.Mag() << std::endl;
//    std::cout  << "lpos  "  << lpos[tid].X() << ", " << lpos[tid].Y() << ", " << lpos[tid].Z() << std::endl;
//    std::cout  << "cpos  "
//    << CorrectedLocalPos(tid, mid[tid], l).X() << ", "
//    << CorrectedLocalPos(tid, mid[tid], l).Y() << ", "
//    << CorrectedLocalPos(tid, mid[tid], l).Z() << std::endl;
      fit_results[l].Set(l, mid2020, fit_lpos[tid], fit_lmom[tid], gpos, gmom, res_pos);
    }

//track
	chi_square->at(itk) = chisq;


//initial 
	rk_fit_init_pos_gx->at(itk) = fitter->GetFitVertex().x();
	rk_fit_init_pos_gy->at(itk) = fitter->GetFitVertex().y();
	rk_fit_init_pos_gz->at(itk) = fitter->GetFitVertex().z();

//	if(fabs(fitter->GetFitMomentum(0).x())  <0.001 ){
//	std::cout << "track id " << itk << std::endl;
//	std::cout << "gtr200 mom before x " << rk_fit_init_mom_gx->at(itk) << std::endl;
//	std::cout << "gtr200 mom after x " << fit_results[2].global_mom.X() << std::endl;
//	std::cout << "init mom z " << fitter->GetFitMomentum(0).z() << std::endl;
//	}

	rk_fit_init_mom_gx->at(itk) = fitter->GetFitMomentum(0).x();
	rk_fit_init_mom_gy->at(itk) = fitter->GetFitMomentum(0).y();
	rk_fit_init_mom_gz->at(itk) = fitter->GetFitMomentum(0).z();
//detector
   rk_fit_sts_mid->at(itk)= fit_results[0].module_id;
   rk_fit_sts_x->at(itk)= fit_results[0].local_pos.X();
   rk_fit_sts_y->at(itk)= fit_results[0].local_pos.Y();
   rk_fit_sts_gx->at(itk)= fit_results[0].global_pos.X();
   rk_fit_sts_gy->at(itk)= fit_results[0].global_pos.Y();
   rk_fit_sts_gz->at(itk)= fit_results[0].global_pos.Z();
   rk_fit_sts_mom_x->at(itk)= fit_results[0].local_mom.X();
   rk_fit_sts_mom_y->at(itk)= fit_results[0].local_mom.Y();
   rk_fit_sts_mom_z->at(itk)= fit_results[0].local_mom.Z();
   rk_fit_sts_mom_gx->at(itk)= fit_results[0].global_mom.X();
   rk_fit_sts_mom_gy->at(itk)= fit_results[0].global_mom.Y();
   rk_fit_sts_mom_gz->at(itk)= fit_results[0].global_mom.Z();
   rk_res_sts_x->at(itk)= fit_results[0].residual_pos.X();

   rk_fit_gtr100_mid->at(itk)= fit_results[1].module_id;
   rk_fit_gtr200_mid->at(itk)= fit_results[2].module_id;
   rk_fit_gtr300_mid->at(itk)= fit_results[3].module_id;
   rk_fit_gtr100_x->at(itk)= fit_results[1].local_pos.X();
   rk_fit_gtr200_x->at(itk)= fit_results[2].local_pos.X();
   rk_fit_gtr300_x->at(itk)= fit_results[3].local_pos.X();
   rk_fit_gtr100_y->at(itk)= fit_results[1].local_pos.Y();
   rk_fit_gtr200_y->at(itk)= fit_results[2].local_pos.Y();
   rk_fit_gtr300_y->at(itk)= fit_results[3].local_pos.Y();
   rk_fit_gtr100_gx->at(itk)= fit_results[1].global_pos.X();
   rk_fit_gtr200_gx->at(itk)= fit_results[2].global_pos.X();
   rk_fit_gtr300_gx->at(itk)= fit_results[3].global_pos.X();
   rk_fit_gtr100_gy->at(itk)= fit_results[1].global_pos.Y();
   rk_fit_gtr200_gy->at(itk)= fit_results[2].global_pos.Y();
   rk_fit_gtr300_gy->at(itk)= fit_results[3].global_pos.Y();
   rk_fit_gtr100_gz->at(itk)= fit_results[1].global_pos.Z();
   rk_fit_gtr200_gz->at(itk)= fit_results[2].global_pos.Z();
   rk_fit_gtr300_gz->at(itk)= fit_results[3].global_pos.Z();
   rk_fit_gtr100_mom_x->at(itk)= fit_results[1].local_mom.X();
   rk_fit_gtr200_mom_x->at(itk)= fit_results[2].local_mom.X();
   rk_fit_gtr300_mom_x->at(itk)= fit_results[3].local_mom.X();
   rk_fit_gtr100_mom_y->at(itk)= fit_results[1].local_mom.Y();
   rk_fit_gtr200_mom_y->at(itk)= fit_results[2].local_mom.Y();
   rk_fit_gtr300_mom_y->at(itk)= fit_results[3].local_mom.Y();
   rk_fit_gtr100_mom_z->at(itk)= fit_results[1].local_mom.Z();
   rk_fit_gtr200_mom_z->at(itk)= fit_results[2].local_mom.Z();
   rk_fit_gtr300_mom_z->at(itk)= fit_results[3].local_mom.Z();
   rk_fit_gtr100_mom_gx->at(itk)= fit_results[1].global_mom.X();
   rk_fit_gtr200_mom_gx->at(itk)= fit_results[2].global_mom.X();
   rk_fit_gtr300_mom_gx->at(itk)= fit_results[3].global_mom.X();
   rk_fit_gtr100_mom_gy->at(itk)= fit_results[1].global_mom.Y();
   rk_fit_gtr200_mom_gy->at(itk)= fit_results[2].global_mom.Y();
   rk_fit_gtr300_mom_gy->at(itk)= fit_results[3].global_mom.Y();
   rk_fit_gtr100_mom_gz->at(itk)= fit_results[1].global_mom.Z();
   rk_fit_gtr200_mom_gz->at(itk)= fit_results[2].global_mom.Z();
   rk_fit_gtr300_mom_gz->at(itk)= fit_results[3].global_mom.Z();

	
   rk_res_gtr100_x->at(itk) = fit_results[1].residual_pos.X();
   rk_res_gtr100_y->at(itk) = fit_results[1].residual_pos.Y();
   rk_res_gtr200_x->at(itk) = fit_results[2].residual_pos.X();
   rk_res_gtr200_y->at(itk) = fit_results[2].residual_pos.Y();
   rk_res_gtr300_x->at(itk) = fit_results[3].residual_pos.X();
   rk_res_gtr300_y->at(itk) = fit_results[3].residual_pos.Y();

}

void E16DSTN_ReStraightV2::AddTrackHit(int itk, E16ANA_StraightMultiTrack* single_track){
	single_track->Clear();
	int tid = 0; // only 1 track is fit
	if(isWire){
		if(     rk_fit_init_pos_gx->at(itk) < 0 && rk_fit_init_pos_gz->at(itk) < 0){
			single_track->SetInitialVertex(TVector3(-20 , 0, -40), kInitPosErrorWire );
		}
		else if(rk_fit_init_pos_gx->at(itk) > 0 && rk_fit_init_pos_gz->at(itk) < 0){
			single_track->SetInitialVertex(TVector3( 20 , 0, -40), kInitPosErrorWire );
		}
		else if(rk_fit_init_pos_gx->at(itk) < 0 && rk_fit_init_pos_gz->at(itk) > 0){
			single_track->SetInitialVertex(TVector3(-20 , 0, 40), kInitPosErrorWire );
		}
		else if(rk_fit_init_pos_gx->at(itk) > 0 && rk_fit_init_pos_gz->at(itk) > 0){
			single_track->SetInitialVertex(TVector3( 20 , 0, 40), kInitPosErrorWire );
		}
	}
	else {
		single_track->SetInitialVertex(TVector3(rk_hit_init_pos_gx->at(itk), rk_hit_init_pos_gy->at(itk), rk_hit_init_pos_gz->at(itk)), kInitPosError);//maybe not good
	}

	single_track->SetInitialMomentum(tid, TVector3(rk_fit_init_mom_gx->at(itk), rk_fit_init_mom_gy->at(itk), rk_fit_init_mom_gz->at(itk)));

	int rk_mids[4] = {rk_fit_sts_mid->at(itk), rk_fit_gtr100_mid->at(itk), rk_fit_gtr200_mid->at(itk), rk_fit_gtr300_mid->at(itk)};
	for(int l=0; l < 4; ++l){
		if(l == E16ANA_StraightTrackConstant::kSSD){
			#ifdef NoExist_SSD
			continue;
			#endif
			#ifndef UseSTS
			std::cerr << "ONLY STS case is defined " << std::endl;
			exit(0);
//			single_track->AddHit(tid, l, geometry->SSD(E16ANA_StraightTrackConstant::ModuleID2020To2013(rk_mids[l])), CorrectedLocalPos(itk, rk_mids[l], l), kSigmas[l]);
			#else 
//			single_track->AddHit(tid, l, geometry->STS(E16ANA_StraightTrackConstant::ModuleID2020To2013(rk_mids[l])), CorrectedLocalPos(itk, rk_mids[l], l), kSigmas[l]);
			single_track->AddHit(tid, l, geom_temp[l], CorrectedLocalPos(itk, rk_mids[l], l), kSigmas_re[l]);
			#endif
		}
		else {
//			single_track->AddHit(tid, l, geometry->GTR(E16ANA_StraightTrackConstant::ModuleID2020To2013(rk_mids[l]), l-1), CorrectedLocalPos(itk, rk_mids[l], l), kSigmas[l]);
			single_track->AddHit(tid, l, geom_temp[l], CorrectedLocalPos(itk, rk_mids[l], l), kSigmas_re[l]);
		}
	}
}

TVector3 E16DSTN_ReStraightV2::CorrectedLocalPos(const int itk, const int mid, const int lid){
	if(lid == 0){//ssd
		 return TVector3(rk_hit_sts_x->at(itk), 0, 0);//sts
	}
	else if(lid == 1){//gtr100
		double lx, ly;
		double cogx = rk_hit_gtr100_cogx->at(itk);	//cog
		double cogy = rk_hit_gtr100_cogy->at(itk);	//cog
		double t0  = ft0_gtr100->Eval(rk_hit_gtr100_cogx->at(itk), rk_hit_gtr100_cogy->at(itk));	
//		std::cout << "cog x : y " << rk_hit_gtr100_cogx->at(itk) << ", " <<  rk_hit_gtr100_cogy->at(itk) << std::endl;
		double xt  = rk_hit_gtr100_xt4->at(itk) - rk_hit_sts_t->at(itk) ;
		double dt  = xt - t0;
		double tan_theta = rk_fit_gtr100_mom_x->at(itk) /  rk_fit_gtr100_mom_z->at(itk);
		double dtx = (0.015 * dt) * tan_theta; 

//		cout << " xt = " << xt << ",  dt =  " << dt << ", tan =" << tan_theta << ", dtx = " << dtx << endl;
		lx = cogx - dtx;

//		return TVector3(lx, cogy, 0);
		return TVector3(cogx, cogy, 0);
	}
	else if(lid == 2){//gtr200
		double lx, ly, lz;
		double cogx = rk_hit_gtr200_cogx->at(itk);	//cog
		double cogy = rk_hit_gtr200_cogy->at(itk);	//cog
		lx = cogx;
		ly = cogy;
		lz = 0   ;
		double t0  = ft0_gtr200->Eval(rk_hit_gtr200_cogx->at(itk), rk_hit_gtr200_cogy->at(itk));	
		double xt  = rk_hit_gtr200_xt4->at(itk) - rk_hit_sts_t->at(itk) ;
		double dt  = xt - t0;
		double tan_theta = rk_fit_gtr200_mom_x->at(itk) /  rk_fit_gtr200_mom_z->at(itk);
		double dtx = (0.015 * dt) * tan_theta; 
//		cout << " xt = " << xt << ",  dt =  " << dt << ", tan =" << tan_theta << ", dtx = " << dtx << endl;
		lx = cogx - dtx;
		return TVector3(lx, cogy, 0);
//		return TVector3(cogx, cogy, 0);
	
	}
	else if(lid == 3){//gtr300
		double lx, ly, lz;
		double cogx = rk_hit_gtr300_cogx->at(itk);	//cog
		double cogy = rk_hit_gtr300_cogy->at(itk);	//cog
		lx = cogx;
		ly = cogy;
		lz = 0   ;
		double t0  = ft0_gtr300->Eval(rk_hit_gtr300_cogx->at(itk), rk_hit_gtr300_cogy->at(itk));	
		double xt  = rk_hit_gtr300_xt4->at(itk) - rk_hit_sts_t->at(itk) ;
		double dt  = xt - t0;
		double tan_theta = rk_fit_gtr300_mom_x->at(itk) /  rk_fit_gtr300_mom_z->at(itk);
		double dtx = (0.015 * dt) * tan_theta; 
//		cout << " xt = " << xt << ",  dt =  " << dt << ", tan =" << tan_theta << ", dtx = " << dtx << endl;
		lx = cogx - dtx;
		return TVector3(lx, cogy, 0);
//		return TVector3(cogx, cogy, 0);
	}
}

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
	pair_fitter->SetRungeKuttaStepSize(5);
	pair_fitter->SetMaxSteps(80);
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
				pair_fitter->AddHit(tids[track_index], l, geometry->STS(E16ANA_StraightTrackConstant::ModuleID2020To2013(mids[track_index][l])),      local_poss[track_index][l], kSigmas_re[l]);
				#else
				pair_fitter->AddHit(tids[track_index], l, geometry->SSD(E16ANA_StraightTrackConstant::ModuleID2020To2013(mids[track_index][l])),  local_poss[track_index][l], kSigmas_re[l]);
				#endif
			}
			else {
				pair_fitter->AddHit(tids[track_index], l, geometry->GTR(E16ANA_StraightTrackConstant::ModuleID2020To2013(mids[track_index][l]),  l-1), local_poss[track_index][l], kSigmas_re[l]);
			}
		}
	}
	return;
}


void E16DSTN_ReStraightV2::ClearUsedClusterIDs() {
#ifdef  WIRE_STS_TRACK
	used_cid_sets.clear();
	used_cid_sets.resize(0);
#else
	for(auto &ids : used_cluster_ids){
		ids.clear();
	}
#endif
	return;
}


#ifdef WIRE_STS_TRACK
bool E16DSTN_ReStraightV2::HasUsedClusterForWire(const array<int, n_kill_strips> &cids, std::vector<std::array<int, n_kill_strips>> &used_cid_sets ){
// No allow for STS duplication
// allow for STS is different,gtr is same
//	for(int i = 0; i < n_kill_strips; i++){
//		for(int j=0; j < used_cluster_ids[i].size() ; j++){// 
//			if(i == 0 ) {//sts
//     		if(cids[i] == used_cluster_ids[i][j]){     		
//			return true;
//     		}
//		} else {//gtr
//				if(cids[0] ==  used_cluster_ids[0][j] && cids[i] == used_cluster_ids[i][j]){ 
//				return true;
//				}
//			}
//		}
//	}
//	return false;

	for(int i=0; i < used_cid_sets.size(); i++){
		if(cids[0] == used_cid_sets[i][0]){
			return true;//No allow for STS duplication
		}
	}
//No allow for Same combination 
		return std::find(used_cid_sets.begin(), used_cid_sets.end(), cids) != used_cid_sets.end();
}
#endif

bool E16DSTN_ReStraightV2::HasUsedCluster(const array<int, kNumTrackingStrips- 2> &cids,std::array<std::vector<int>, E16ANA_StraightTrackConstant::kNumTrackingStrips-2> &used_cluster_ids ){
	for (int i = 0; i < kNumTrackingStrips-2; ++i) {
		for(const auto& used_id : used_cluster_ids[i]){ if(cids[i] == used_id){
       		return true;
     		}
   	}
	}
	return false;
}

bool E16DSTN_ReStraightV2::HasUsedCluster(const array<int, kNumTrackingStrips- 1> &cids,std::array<std::vector<int>, E16ANA_StraightTrackConstant::kNumTrackingStrips-1> &used_cluster_ids ){
	for (int i = 0; i < kNumTrackingStrips-1; ++i) {
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

//bool E16DSTN_ReStraightV2::HasUsedCluster(const array<int, 3> &cids,std::array<std::vector<int>, 3> &used_cluster_ids ){//only sts
//	for (int i = 0; i < 1; ++i) {
//		for(const auto& used_id : used_cluster_ids[i]){
//	     if(cids[i] == used_id){
//	       return true;
//	     }
//	   }
//	  }
//	return false;
//}

void E16DSTN_ReStraightV2::InitHistos(){	
//basic 
	h_n_runid = new TH1D("n of events of runid","n of events of runid", 15, 30331.5, 30346.5);
	h_n_eventid = new TH1D("n of events of event id","n of events of eventid", 10000, -0.5, 9999.5);
	h_n_spillid = new TH1D("n of events of spill id","n of events of spillid", 1000, -0.5, 999.5);
	h_chi2    = new TH1D(Form("h_chi2"), Form("h_chi2"), 100, 0, 2000);	
	h_t0diff    = new TH1D(Form("h_t0diff"), Form("h_t0diff"), 100, -100,100);	
	h_init_pos = new TH2D(Form("h_init_pos"), Form("h_init_pos"), 50, -30, 30, 50, -60, 60);
	for(int m=0; m < n_modules; m++){
		for(int tg=0; tg < 2; tg++){
//			h_trackmap[tg][m] = new TH2D(Form("h_track_map%d_%d", tg,  m+100), Form("h_track_map%d_%d",tg,  m+100), 25, -50, 50, 25, -50, 50);
		}
		h_chi2_mod[m] = new TH1D(Form("h_chi2_mod%d", m+100), Form("h_chi2_mod%d", m+100), 100, 0, 2000);
		h_lg_t_mod[m] = new TH1D(Form("h_lg_t_mod%d", m+100), Form("h_lg_t_mod%d", m+100), 100, 50, 150);
		h_init_posz_mod[m] = new TH1D(Form("h_init_posz_mod%d", m+100), Form("h_init_posz_mod%d", m+100), 50, -60, 60);

		h_res_lg_x[m]  = new TH1D(Form("h_res_lg_x_%d", m+100), Form("h_res_lg_x_%d", m+100), 50, -400, 400 );
		h_res_lg_y[m]  = new TH1D(Form("h_res_lg_y_%d", m+100), Form("h_res_lg_y_%d", m+100), 50, -400, 400 );
		h_res_lg_2d[m]  = new TH2D(Form("h_res_lg_2d_%d", m+100), Form("h_res_lg_2d_%d", m+100), 50, -400, 400, 50, -400, 400 );
		h_res_vtx_trk_lg_x[m]  = new TH1D(Form("h_res_vtx_trk_lg_x_%d", m+100), Form("h_res_vtx_trk_lg_x_%d", m+100), 50, -400, 400 );
		h_res_vtx_trk_lg_y[m]  = new TH1D(Form("h_res_vtx_trk_lg_y_%d", m+100), Form("h_res_vtx_trk_lg_y_%d", m+100), 50, -400, 400 );
		h_bak_res_vtx_trk_lg_x[m]  = new TH1D(Form("h_bak_res_vtx_trk_lg_x_%d", m+100), Form("h_bak_res_vtx_trk_lg_x_%d", m+100), 50, -400, 400 );
		h_bak_res_vtx_trk_lg_y[m]  = new TH1D(Form("h_bak_res_vtx_trk_lg_y_%d", m+100), Form("h_bak_res_vtx_trk_lg_y_%d", m+100), 50, -400, 400 );

		h_bak_res_lg_x[m]  = new TH1D(Form("h_bak_res_lg_x_%d", m+100), Form("h_bak_res_lg_x_%d", m+100), 50, -400, 400 );
		h_bak_res_lg_y[m]  = new TH1D(Form("h_bak_res_lg_y_%d", m+100), Form("h_bak_res_lg_y_%d", m+100), 50, -400, 400 );
		h_bak_res_lg_2d[m]  = new TH2D(Form("h_bak_res_lg_2d_%d", m+100), Form("h_bak_res_lg_2d_%d", m+100), 50, -400, 400, 50, -400, 400 );

		for(int l=0; l < n_layers; l++){// -- layer 
				h_hitmap[m][l]   = new TH2D (Form("h_hit_map_%d_%d", m+100, l), Form("h_hit_map_%d_%d", m+100, l), 50,  -50*l , 50 * l, 50, -50 * l , 50*l ) ;
				h_hitmap_x[m][l] = new TH1D (Form("h_hit_map_x_%d_%d", m+100, l), Form("h_hit_map_x_%d_%d", m+100, l), 50,  -50*l , 50 * l ) ;
				h_hitmap_y[m][l] = new TH1D (Form("h_hit_map_y_%d_%d", m+100, l), Form("h_hit_map_y_%d_%d", m+100, l), 50,  -50*l , 50 * l ) ;
				h_hit_timing_x[m][l] = new TH1D (Form("h_hit_timing_x_%d_%d", m+100, l), Form("h_hit_timing_x_%d_%d", m+100, l), 100, 0 ,500 ) ;
				h_cluster_t_diff[m][l] = new TH1D (Form("h_cl_t_diff_xy_m%d_l%d", m+100, l), Form("h_cl_t_diff_xy_m%d_l%d", m+100, l), 50, -100, 100 );
				h_cluster_t_diff_2d[m][l] = new TH2D (Form("h_cl_t_diff_2d_m%d_l%d", m+100, l), Form("h_cl_t_diff_2d_m%d_l%d", m+100, l), 50, 0, 350, 50, 0, 350 );
				h_cluster_timing_x[m][l] = new TH1D (Form("h_cluster_timing_x%d_%d", m+100, l), Form("h_cluster_timing_x%d_%d", m+100, l), 100, 0 ,500 ) ;
				h_cluster_timing_y[m][l] = new TH1D (Form("h_cluster_timing_y%d_%d", m+100, l), Form("h_cluster_timing_y%d_%d", m+100, l), 100, 0 ,500 ) ;
				h_tot_end_fr[m][l] = new TH1D (Form("h_tot_end_fr%d_%d", m+100, l), Form("h_tot_end_fr%d_%d", m+100, l), 50, -10 ,1000 ) ;
				h_tot_end_bg[m][l] = new TH1D (Form("h_tot_end_bg%d_%d", m+100, l), Form("h_tot_end_bg%d_%d", m+100, l), 50, -10 ,1000 ) ;
//				h_slopevel[m][l][div] = new TH2D(Form("h_slopevel_%d_%d%d", m+100, l,div), Form("h_slopevel_%d%d%d", m+100, l,div),  25, -100, 100, 60, -2, 2);
				if(l == 0){
					h_res_x[m][l] = new TH1D(Form("h_res_x_m%d_l%d", m+100, l), Form("h_res_x_m%d_l%d", m+100, l), 100, -2.5, 2.5);//sts
				}
				else {
					h_res_x[m][l] = new TH1D(Form("h_res_x_m%d_l%d", m+100, l), Form("h_res_x_m%d_l%d", m+100, l), 100, -1.5, 1.5);
				}
				h_pre_res_x[m][l] = new TH1D(Form("h_pre_res_x_m%d_l%d", m+100, l), Form("h_pre_res_x_m%d_l%d", m+100, l), 100, -2, 2);
				h_res_y[m][l] = new TH1D(Form("h_res_y__m%d_l%d", m+100, l), Form("h_res_y__m%d_l%d", m+100, l), 100, -4, 4);

				h_res_vtx_trk_x[m][l] = new TH1D(Form("h_res_vtx_trk_x_m%d_l%d", m+100, l), Form("h_res_vtx_trk_x_m%d_l%d", m+100, l), 100, -2, 2);
				h_res_vtx_trk_y[m][l] = new TH1D(Form("h_res_vtx_trk_y_m%d_l%d", m+100, l), Form("h_res_vtx_trk_y_m%d_l%d", m+100, l), 100, -4, 4);
				if(l == 0 ) {
					h_cor_res_fitlx[m][l]  = new TH2D(Form("h_cor_res_fitlx_m%d_l%d", m+100, l), Form("h_cor_res_fitlx_m%d_l%d", m+100, l), 20, -30 , 30, 50, -2.5, 2.5);
				}
				else {
				h_cor_res_fitlx[m][l]  = new TH2D(Form("h_cor_res_fitlx_m%d_l%d", m+100, l), Form("h_cor_res_fitlx_m%d_l%d", m+100, l), 20, -50*l , 50*l, 50, -2.5, 2.5);
				}
				h_cor_res_fitly[m][l]  = new TH2D(Form("h_cor_res_fitly_%d_%d", m+100, l), Form("h_cor_res_fitly_%d_%d", m+100, l), 20, -50*l , 50*l, 50, -2, 2);
				h_cor_res_timing[m][l] = new TH2D(Form("h_cor_res_timing__%d_%d", m+100, l), Form("h_cor_res_timing_%d_%d", m+100, l), 20, 0 , 600, 100, -2, 2);
				h_tan_theta[m][l] = new TH1D(Form("h_tan_theta_m%d_l%d",  m+100, l), Form("h_tan_theta_%d_%d", m+100, l), 20,  kHistoTanMin, kHistoTanMax);

				h_dz[m][l] = new TH1D(Form("h_dz_m%d_l%d",  m+100, l), Form("h_dz_%d_%d", m+100, l), 50,  -6, 6);

				h_cor_dz_time[m][l]        = new TH2D(Form("h_cor_dz_time_%d%d", m+100, l)      , Form("h_cor_dz_time_%d%d",  m+100, l)     , 20, 0, 600, 60,  -6, 6);
				h_cor_dz_time_t0cor[m][l]= new TH2D(Form("h_cor_dz_time_t0cor_%d_%d",  m+100, l), Form("h_cor_dz_time_t0cor_%d%d", m+100, l), 20, 0, 600, 7, -8, 8);
					for(int div = 0; div < n_div; div++){
						h_cluster_timing_chi2_xdependence[m][l][div] = new TH1D(Form("h_cluster_timing_chi2_xdependence%d_%d_%d", m+100, l, div), Form("h_cluster_timing_chi2_xdependence%d_%d_%d", m+100, l, div), 20, 0 ,600 ) ;
						h_cluster_timing_chi2_ydependence[m][l][div] = new TH1D(Form("h_cluster_timing_chi2_ydependence%d_%d_%d", m+100, l, div), Form("h_cluster_timing_chi2_ydependence%d_%d_%d", m+100, l, div), 20, 0 ,600 ) ;
						h_cluster_adc_xdependence[m][l][div] = new TH1D(Form("h_cluster_adc_xdependence%d_%d_%d", m+100, l, div), Form("h_cluster_adc_xdependence%d_%d_%d", m+100, l, div), 20, 0 ,5000 ) ;
						h_cluster_adc_ydependence[m][l][div] = new TH1D(Form("h_cluster_adc_ydependence%d_%d_%d", m+100, l, div), Form("h_cluster_adc_ydependence%d_%d_%d", m+100, l, div), 20, 0 ,5000 ) ;
						}
	//			for(int t=0; t < n_tgt; t++){
//					h_fitlx[t][m][l] = new TH1D(Form("h_fitlx_tgt%d_m%d_l%d",t, m+100, l), Form("h_fitlx_tgt%d_m%d_l%d",t, m+100, l), 100, -2, 2);
	//			}
			}
		}	

 double n_bin_x = 50;//gtr100 calib
	double tan_limit  = 1.5;
	double resx_limit = 1.5;
	int n_xdiv = 20;//gtr100
	int n_xdiv2 = 8;//gtr100
//	double n_bin_x = 40;//gtr200 calib
//	double tan_limit  = 2.5;//gtr200
//	double resx_limit = 2.5;//gtr200
//	int n_xdiv = 14;//gtr200
//	int n_xdiv2 = 6;//gtr200
//	double n_bin_x = 30;//gtr300 calib
//	double tan_limit  = 2.5;//gtr300
//	double resx_limit = 2.5;//gtr300
//	int n_xdiv = 14;//gtr300
//	int n_xdiv2 = 6;//gtr300
	
	for(int t=0; t < n_wires; t++){// see .hh for definitions// 1 is for h_resx_dz_wire to integrate all wires
		for(int m=0; m <n_modules;m++){
			for(int l=0; l < n_layers; l++){
				h_res_x_wire[t][m][l] = new TH1D(Form("h_res_x_wire%d_m%d_l%d", t, m+100, l), Form("h_res_x_wire%d_m%d_l%d", t, m+100, l), 100, -2.5, 2.5);
				h_res_y_wire[t][m][l] = new TH1D(Form("h_res_y_wire%d_m%d_l%d", t, m+100, l), Form("h_res_y_wire%d_m%d_l%d", t, m+100, l), 100, -2.5, 2.5);
			
				if(l == 0 ){
				h_cor_resx_fitlx_wire[t][m][l]  = new TH2D(Form("h_cor_resx_fitlx_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resx_fitlx_wire%d_m%d_l%d",t,  m+100, l), n_xdiv, -30 , 30, n_bin_x, -1.5, 1.5);
				h_cor_resx_fitly_wire[t][m][l]  = new TH2D(Form("h_cor_resx_fitly_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resx_fitly_wire%d_m%d_l%d",t,  m+100, l), n_xdiv, -30 , 30, n_bin_x, -1.5, 1.5);
				}
				else {
				h_cor_resx_fitlx_wire[t][m][l]  = new TH2D(Form("h_cor_resx_fitlx_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resx_fitlx_wire%d_m%d_l%d",t,  m+100, l), n_xdiv, -50*l , 50*l, n_bin_x, -resx_limit, resx_limit);
				h_cor_resx_fitly_wire[t][m][l]  = new TH2D(Form("h_cor_resx_fitly_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resx_fitly_wire%d_m%d_l%d",t,  m+100, l), n_xdiv, -50*l , 50*l, n_bin_x, -resx_limit, resx_limit);
				h_cor_resx_fitlx_center_wire[t][m][l]  = new TH2D(Form("h_cor_resx_fitlx_center_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resx_fitlx_center_wire%d_m%d_l%d",t,  m+100, l),         n_xdiv2, -50*l , 50*l, n_bin_x, -resx_limit, resx_limit);
				h_cor_resx_fitly_center_wire[t][m][l]  = new TH2D(Form("h_cor_resx_fitly_center_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resx_fitly_center_wire%d_m%d_l%d",t,  m+100, l),         n_xdiv2, -50*l , 50*l, n_bin_x, -resx_limit, resx_limit);
				h_cor_resx_fitlx_edge_top_wire[t][m][l]    = new TH2D(Form("h_cor_resx_fitlx_edge_top_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resx_fitlx_edge_top_wire%d_m%d_l%d",t,  m+100, l), n_xdiv2, -50*l , 50*l, n_bin_x, -resx_limit, resx_limit);
				h_cor_resx_fitly_edge_top_wire[t][m][l]    = new TH2D(Form("h_cor_resx_fitly_edge_top_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resx_fitly_edge_top_wire%d_m%d_l%d",t,  m+100, l), n_xdiv2, -50*l , 50*l, n_bin_x, -resx_limit, resx_limit);
				h_cor_resx_fitlx_edge_bot_wire[t][m][l]    = new TH2D(Form("h_cor_resx_fitlx_edge_bot_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resx_fitlx_edge_bot_wire%d_m%d_l%d",t,  m+100, l), n_xdiv2, -50*l , 50*l, n_bin_x, -resx_limit, resx_limit);
				h_cor_resx_fitly_edge_bot_wire[t][m][l]    = new TH2D(Form("h_cor_resx_fitly_edge_bot_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resx_fitly_edge_bot_wire%d_m%d_l%d",t,  m+100, l), n_xdiv2, -50*l , 50*l, n_bin_x, -resx_limit, resx_limit);

				for(int i=0; i < 9; i++ ){//sensitive area is divided into nine regions.
					h_resx_div[t][m][l][i] = new TH1D(Form("h_resx_div_wire%d_m%d_l%d_div%d" , t, m+100, l, i), Form("h_resx_div_wire%d_m%d_l%d_div%d", t, m+100, l, i), 50, -2.5, 2.5); 
				}


				}
				h_cor_resy_fitly_wire[t][m][l]       = new TH2D(Form("h_cor_resy_fitly_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resy_fitly_wire%d_m%d_l%d",t,  m+100, l), 10, -50*l , 50*l, n_bin_x, -2.5, 2.5);
				h_cor_resx_tan_wire[t][m][l]           = new TH2D(Form("h_cor_resx_tan_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resx_tan_wire%d_m%d_l%d",t,  m+100, l),  n_xdiv, kHistoTanMin, kHistoTanMax, n_bin_x, -tan_limit, tan_limit);
				h_cor_resx_tan_center_wire[t][m][l]    = new TH2D(Form("h_cor_resx_tan_center_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resx_center_tan_wire%d_m%d_l%d",t,  m+100, l),  n_xdiv2, kHistoTanMin, kHistoTanMax, n_bin_x,     -tan_limit, tan_limit);
				h_cor_resx_tan_edge_top_wire[t][m][l]  = new TH2D(Form("h_cor_resx_tan_edge_top_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resx_edge_top_tan_wire%d_m%d_l%d",t,  m+100, l),  n_xdiv2, kHistoTanMin, kHistoTanMax, n_bin_x, -tan_limit, tan_limit);
				h_cor_resx_tan_edge_bot_wire[t][m][l]  = new TH2D(Form("h_cor_resx_tan_edge_bot_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resx_edge_bot_tan_wire%d_m%d_l%d",t,  m+100, l),  n_xdiv2, kHistoTanMin, kHistoTanMax, n_bin_x, -tan_limit, tan_limit);
				h_cor_resy_tan_wire[t][m][l]           = new TH2D(Form("h_cor_resy_tan_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resy_tan_wire%d_m%d_l%d",t,  m+100, l),  n_xdiv, kHistoTanMin, kHistoTanMax, n_bin_x, -2.5, 2.5);

				
			
			}
		}
	}


	for(int t=0; t < n_wires + 1; t++){// see .hh for definitions// 1 is for h_resx_dz_wire to integrate all wires
		for(int m=0; m <n_modules;m++){
			for(int l=0; l < n_layers; l++){
				for(int i=0; i < 16; i++ ){//sensitive area is divided 
					h_resx_dz_wire_x[t][m][l][i] = new TH2D(Form("h_resx_dz_wire_x_wire%d_m%d_l%d_div%d", t,  m+100, l, i), Form("h_resx_dz_wire_x_wire%d_m%d_l%d_div%d",t,  m+100, l, i), 8,  150 , 450, 25, -10, 10);
				}
			}
		}
	}



	for(int m=0; m < n_modules;m++){
		for(int l=0; l < n_layers; l++){
				if(l !=0){
				for(int i=0; i < 25; i++ ){//sensitive area is divided into 25 regions.
					h_hit_timing_x_area[m][l][i] = new TH1D (Form("h_hit_timing_x_area_m%d_l%d_div%d", m+100, l, i), Form("h_hit_timing_x_area_m%d_l%d_div%d", m+100, l, i), 100, 0 ,500 ) ;
					h_cluster_timing_x_area[m][l][i] = new TH1D (Form("h_cluster_timing_x_area_m%d_l%d_div%d", m+100, l, i), Form("h_cluster_timing_x_area_m%d_l%d_div%d", m+100, l, i), 100, 0 ,350 ) ;
					h_hit_adc_y_area[m][l][i] = new TH1D (Form("h_hit_adc_y_area_m%d_l%d_div%d", m+100, l, i), Form("h_hit_adc_y_area_m%d_l%d_div%d", m+100, l, i), 100, 0 ,500 ) ;
					for(int tgt=0; tgt < n_wires; tgt++){
					h_dt_area[tgt][m][l][i] = new TH1D (Form("h_dt_area_wire%d_m%d_l%d_div%d",tgt,  m+100, l, i), Form("h_dt_area_wire%d_m%d_l%d_div%d", tgt, m+100, l, i), 100, 0 ,350 ) ;
					}
				}
				}
//				h_resx_dz_wire_x[m][l] = new TH2D(Form("h_resx_dz_wire_x_m%d_l%d",  m+100, l), Form("h_resx_dz_wire_x_m%d_l%d", m+100, l), 80,  0 , 400, 40, -4, 4);
			for(int div=0; div < n_div; div++){
//				h_resx_dz_wire_xdiv[m][l][div] = new TH2D(Form("h_resx_dz_wire_xdiv_m%d_l%d_div%d",  m+100, l, div), Form("h_resx_dz_wire_xdiv_wire_m%d_l%d_div%d", m+100, l, div), 80, 0 , 400, 40, -4.0, 4.0);
//				h_resx_dz_wire_ydiv[m][l][div] = new TH2D(Form("h_resx_dz_wire_ydiv_m%d_l%d_div%d",  m+100, l, div), Form("h_resx_dz_wire_ydiv_wire_m%d_l%d_div%d", m+100, l, div), 80, 0 , 400, 40, -4.0, 4.0);
			}
		}
	}
	h_dtx_tan = new TH2D("h_dtx_tan", "h_dtx_tan", 50, -0.3, 0.3, 50, -1,1);


// vertex
   h_vtx_gx = new TH1D("h_vtx_gx", "h_vtx_gx", 80, -20, 20);
   h_vtx_gy = new TH1D("h_vtx_gy", "h_vtx_gy", 80, -20, 20);
   h_vtx_gz = new TH1D("h_vtx_gz", "h_vtx_gz", 80, -50, 50);
  	h_vtx_gx_gz = new TH2D("h_vtx_gx_gz", "h_vtx_gx_gz", 80, -20, 20, 80, -40, 40); 
  	h_vtx_gx_gy = new TH2D("h_vtx_gx_gy", "h_vtx_gx_gy", 80, -20, 20, 80, -20, 20); 
}


void E16DSTN_ReStraightV2::FillVectors(int i){
			mids = {	rk_fit_sts_mid->at(i),
				rk_fit_gtr100_mid->at(i),						
				rk_fit_gtr200_mid->at(i),
				rk_fit_gtr300_mid->at(i)};
			resx = { rk_res_sts_x->at(i),
						rk_res_gtr100_x->at(i),
						rk_res_gtr200_x->at(i),
						rk_res_gtr300_x->at(i)};
			pre_resx = { -999, -999, -999, -999};
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
			yts = { 0, 
						rk_hit_gtr100_yt->at(i),
						rk_hit_gtr200_yt->at(i),
     					rk_hit_gtr300_yt->at(i)};
			xadcs = {rk_hit_sts_adc->at(i), rk_hit_gtr100_xadc->at(i), rk_hit_gtr200_xadc->at(i), rk_hit_gtr300_xadc->at(i)};
			yadcs = {0, rk_hit_gtr100_yadc->at(i), rk_hit_gtr200_yadc->at(i), rk_hit_gtr300_yadc->at(i)};
			xcids = {rk_hit_sts_id->at(i), rk_hit_gtr100_xid->at(i), rk_hit_gtr200_xid->at(i), rk_hit_gtr300_xid->at(i)};
//         xtotend = {-100,gtr100x_cluster_last_tot_end->at(i), gtr200x_cluster_last_tot_end->at(i), gtr300x_cluster_last_tot_end->at(i) };
}


void E16DSTN_ReStraightV2::CalculateRemovedGTRMinResidual(){
#ifdef REMOVE_GTR100
	auto *clusters_x    = gtr100x_cluster_x;
	auto *clusters_xadc = gtr100x_cluster_adc;
	auto *clusters_xcids = gtr100x_cluster_id;
	auto *clusters_mids = gtr100x_cluster_mid	;
	int n_clusters = n_gtr100x_clusters;
	double min_resx = 9999;
   double pre_min_resx = 9999;
	for(int k=0; k < n_clusters; k++){
//		std::cout << "mid = " << clusters_mids->at(k) << "xaadc = "  << clusters_xadc->at(k) << ", " << clusters_x->at(k) << std::endl;
		if(clusters_mids->at(k) == mids[1]){
			if(clusters_xadc->at(k) < kGTRFakeADC ){
				double resx = fitlxs[1] - clusters_x->at(k);
				if(fabs(resx)  < fabs(min_resx)){
					min_resx = resx;
					xcids[1] = clusters_xcids->at(k); 
				}
			}
		}
	}
	resx[1] = min_resx;
// --- previous --- // 
   for(int k=0; k < pre_n_gtrx_clusters; k++){
		if(pre_gtrx_cluster_mid[k] == mids[1]){
			if(pre_gtrx_cluster_adc[k] < kGTRFakeADC ){
				double resx = fitlxs[1] - pre_gtrx_cluster_x[k];
				if(fabs(resx) < fabs(pre_min_resx)){
					pre_min_resx = resx;
				}
			}
		}
	}
	pre_resx[1] = pre_min_resx;

#elif  REMOVE_GTR200
	auto *clusters_x    = gtr200x_cluster_x;
	auto *clusters_xadc = gtr200x_cluster_adc;
	auto *clusters_xcids = gtr200x_cluster_id;
	auto *clusters_mids = gtr200x_cluster_mid	;
	int n_clusters = n_gtr200x_clusters;
	double min_resx = 9999;
   double pre_min_resx = 9999;
	for(int k=0; k < n_clusters; k++){
//		std::cout << "mid = " << clusters_mids->at(k) << "xaadc = "  << clusters_xadc->at(k) << ", " << clusters_x->at(k) << std::endl;
		if(clusters_mids->at(k) == mids[2]){
			if(clusters_xadc->at(k) < kGTRFakeADC ){
				double resx = fitlxs[2] - clusters_x->at(k);
				if(fabs(resx)  < fabs(min_resx)){
					min_resx = resx;
					xcids[2] = clusters_xcids->at(k); 
				}
			}
		}
	}
	resx[2] = min_resx;
// --- previous --- // 
   for(int k=0; k < pre_n_gtrx_clusters; k++){
		if(pre_gtrx_cluster_mid[k] == mids[2]){
			if(pre_gtrx_cluster_adc[k] < kGTRFakeADC ){
				double resx = fitlxs[2] - pre_gtrx_cluster_x[k];
				if(fabs(resx) < fabs(pre_min_resx)){
					pre_min_resx = resx;
				}
			}
		}
	}
	pre_resx[2] = pre_min_resx;
#elif REMOVE_GTR300
	auto *clusters_x    = gtr300x_cluster_x;
	auto *clusters_xadc = gtr300x_cluster_adc;
	auto *clusters_xcids = gtr300x_cluster_id;
	auto *clusters_mids = gtr300x_cluster_mid	;
	int n_clusters = n_gtr300x_clusters;
	double min_resx = 9999;
   double pre_min_resx = 9999;
	for(int k=0; k < n_clusters; k++){
//		std::cout << "mid = " << clusters_mids->at(k) << "xaadc = "  << clusters_xadc->at(k) << ", " << clusters_x->at(k) << std::endl;
		if(clusters_mids->at(k) == mids[3]){
			if(clusters_xadc->at(k) < kGTRFakeADC ){
				double resx = fitlxs[3] - clusters_x->at(k);
				if(fabs(resx)  < fabs(min_resx)){
					min_resx = resx;
					xcids[3] = clusters_xcids->at(k); 
				}
			}
		}
	}
	resx[3] = min_resx;
// --- previous --- // 
   for(int k=0; k < pre_n_gtrx_clusters; k++){
		if(pre_gtrx_cluster_mid[k] == mids[3]){
			if(pre_gtrx_cluster_adc[k] < kGTRFakeADC ){
				double resx = fitlxs[3] - pre_gtrx_cluster_x[k];
				if(fabs(resx) < fabs(pre_min_resx)){
					pre_min_resx = resx;
				}
			}
		}
	}
	pre_resx[3] = pre_min_resx;
#endif
}

//void E16DSTN_ReStraightV2::CalculateLGAllHitsResidual(int i){//i th track
//}
//
//
void E16DSTN_ReStraightV2::FillPulseInfos(int tid){//ith track
	std::array<int, 4> n_cls_x   = {n_sts_clusters, n_gtr100x_clusters, n_gtr200x_clusters, n_gtr300x_clusters};	
	std::array<vector<int>*, 4> cl_ids_x  = {sts_cluster_id, gtr100x_cluster_id, gtr200x_cluster_id, gtr300x_cluster_id};	
	std::array<vector<int>*, 4> cl_mids_x   = {sts_cluster_mid, gtr100x_cluster_mid, gtr200x_cluster_mid, gtr300x_cluster_mid};	
	std::array<vector<double>*, 4> consist_ids;
// searching consist cluster 
	for(int l=1; l < n_layers;l++){
		int cid_track = xcids[l];//cid in track
		int mid_track = mids[l]; //mid in track
		auto *cids = cl_ids_x[l];
		for(int i=0; i < n_cls_x[l];i++){
			if(mid_track != cl_mids_x[l]->at(i)) continue;//module match
			int cid = cids->at(i);
			if(cid == cid_track){//a cluster used in track
				if(l==1) {//gtr100
					consist_ids[l] =  &gtr100x_cluster_consist_hit_id->at(i);
				}		
				else if(l==2) {//gtr200
					consist_ids[l] =  &gtr200x_cluster_consist_hit_id->at(i);
				}		
				else if(l==3) {//gtr300
					consist_ids[l] =  &gtr300x_cluster_consist_hit_id->at(i);
				}		
			}
		}
	}
	
// searching hits 
	std::array<int, 4> n_hits_x                    = {n_sts_hits, n_gtr100x_hits, n_gtr200x_hits, n_gtr300x_hits};	
	std::array<vector<int>*, 4> hits_ids_x         = {sts_hit_id, gtr100x_hit_id, gtr200x_hit_id, gtr300x_hit_id};	
	std::array<vector<int>*, 4> hit_mids_x         = {sts_hit_mid, gtr100x_hit_mid, gtr200x_hit_mid, gtr300x_hit_mid};	
	std::array<vector<double>*, 4> hit_timings_x   = {sts_hit_t, gtr100x_hit_t,  gtr200x_hit_t, gtr300x_hit_t};	
	std::array<vector<float>*, 4> hit_adcs_y      = {sts_hit_adc, gtr100y_hit_adc,  gtr200y_hit_adc, gtr300y_hit_adc};	
//	for(int l=1; l < n_layers; l++){
//		for(int i=0; i < n_hits_x[l]; i++){
//			int hid = hits_ids_x[l]->at(i);	
//			int mid_track = mids[l];
////			std::cout << "m " << hit_mids_x[l]->at(i) << ", layer " << l << ", hid = "  << hid << std::endl; 
////			if(mid_track != hit_mids_x[l]->at(i) )	continue;
//			for(int j=0; j< consist_ids[l]->size(); j++){
//				int consist_id = consist_ids[l]->at(j);
////				std::cout << "consist id  = " << consist_id << std::endl;
//				if(consist_id == hid){
//					h_hit_timing_x[hit_mids_x[l]->at(i) - 100][l]->Fill(hit_timings_x[l]->at(i));
//					int area ;
//					double length = (double)100*l/5;
//					area = floor((fitlxs[l] + l*50)/length) +  floor((fitlys[l] + l * 50)/length ) * 5;
////					std::cout << "area " << area << std::endl;
//					h_hit_timing_x_area[hit_mids_x[l]->at(i) - 100][l][area]->Fill(hit_timings_x[l]->at(i));
//					h_hit_adc_y_area[hit_mids_x[l]->at(i) - 100][l][area]->Fill(hit_adcs_y[l]->at(i));
//				}
//			}
//		}
//	}
}

void E16DSTN_ReStraightV2::DrawHist(TTree* tree, int n_start, int n_end, int print_cycle, const int residual_layer,  TString pdf_name){	
}

