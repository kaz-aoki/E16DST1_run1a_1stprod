#define E16DSTN_ReStraightV2_cxx
#include "E16DSTN_ReStraightV2.hh"
//#include "E16ANA_StraightTrackParameter.hh"
#include "E16DSTN_ReStraightParameter.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


//using namespace E16ANA_StraightTrackParameter;
using namespace E16ANA_StraightTrackConstant;
using namespace E16DSTN_ReStraightParameter;

void E16DSTN_ReStraightV2::ChiSqSort( std::vector<int> &sorted_ids){
	int n_chisq  = chi_square->size();
	int n_tracks = n_cands;
	if(n_tracks != n_chisq) {
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
			killdup_ids.emplace_back(i);
			}
    }
#else//
	#ifdef NoExist_SSD
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



void E16DSTN_ReStraightV2::Loop(TTree* tree, int print_cycle, int event_start, int event_end, bool vertex_xy_fix_flag, bool py_fix_flag, bool vetex_z_fix_flag )
{
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


void E16DSTN_ReStraightV2::ReTracking(TTree* tree, int print_cycle, int event_start, int event_end, bool vertex_xy_fix_flag, bool py_fix_flag, bool vertex_z_fix_flag){
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
		for(int itk=0; itk < n_alive_tracks; itk++){//ith track
			double chi2 = chi_square->at(itk);
			int mid_sts = rk_fit_sts_mid->at(itk);
			int mid_gtr100 = rk_fit_gtr100_mid->at(itk);
			int mid_gtr200 = rk_fit_gtr200_mid->at(itk);
			int mid_gtr300 = rk_fit_gtr300_mid->at(itk);
			if(mid_sts != 106) continue;
			if(mid_gtr100 != 106) continue;
			if(mid_gtr200 != 106) continue;
			if(mid_gtr300 != 106) continue;
			if(chi2 < E16DSTN_ReStraightParameter::kchi2_threshold){
				Fit(itk, fitter, vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag);
				alive_ids.push_back(itk);	
			}
   	}
		AnalyzeTrackPairs(alive_ids);
	 	AddRecord(tree, alive_ids);
	}
}

double E16DSTN_ReStraightV2::Fit(int itk, E16ANA_StraightMultiTrack* fitter, bool vertex_xy_fix_flag,  bool py_fix_flag, bool vertex_z_fix_flag){
	fitter->Clear();
	this->AddTrackHit(itk, fitter);
	fitter->SetRungeKuttaStepSize(5.0);
	fitter->SetMaxSteps(80);
	double chisq = fitter->Fit(vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag, 0, 1.0e3);
	UpdateFitResult(itk, fitter);
	return chisq;
}

void E16DSTN_ReStraightV2::UpdateFitResult(int itk, E16ANA_StraightMultiTrack *fitter){
	int tid = 0;
	for(int l=0; l < 4; l++){
		std::vector<TVector3> lpos;
      std::vector<TVector3> lmom;
      std::vector<int> mid;
      fitter->GetFitLPos(0, l, mid, lpos);
      fitter->GetFitLMom(0, l, mid, lmom);
      TVector3 gpos;
      TVector3 gmom;
      auto mid2020 = E16ANA_StraightTrackConstant::ModuleID2013To2020(mid[0]);
      if (l <= E16ANA_StraightTrackConstant::kSSD) {
        gpos = geometry->STS(mid[tid])->GetGPos(lpos[tid]);
        gmom = geometry->STS(mid[tid])->GetGMom(lmom[tid]);
      } else {
        gpos = geometry->GTR(mid[tid], l - 1)->GetGPos(lpos[tid]);
        gmom = geometry->GTR(mid[tid], l - 1)->GetGMom(lmom[tid]);
      }
      auto res_pos  = CorrectedLocalPos( tid,mid[tid] ,l ) - lpos[tid];
//    std::cout  << "layer, rpos Mag  "  << l << ", " << rpos.Mag() << std::endl;
//    std::cout  << "lpos  "  << lpos[tid].X() << ", " << lpos[tid].Y() << ", " << lpos[tid].Z() << std::endl;
//    std::cout  << "cpos  "
//    << CorrectedLocalPos(tid, mid[tid], l).X() << ", "
//    << CorrectedLocalPos(tid, mid[tid], l).Y() << ", "
//    << CorrectedLocalPos(tid, mid[tid], l).Z() << std::endl;
      fit_results[l].Set(l, mid2020, lpos[tid], lmom[tid], gpos, gmom, res_pos);
    }

//initial 
	rk_fit_init_pos_gx->at(itk) = fitter->GetFitVertex().x();
	rk_fit_init_pos_gy->at(itk) = fitter->GetFitVertex().y();
	rk_fit_init_pos_gz->at(itk) = fitter->GetFitVertex().z();
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

   rk_res_gtr100_x->at(itk)= fit_results[1].residual_pos.X();
   rk_res_gtr100_y->at(itk)= fit_results[1].residual_pos.Y();
   rk_res_gtr200_x->at(itk)= fit_results[2].residual_pos.X();
   rk_res_gtr200_y->at(itk)= fit_results[2].residual_pos.Y();
   rk_res_gtr300_x->at(itk)= fit_results[3].residual_pos.X();
   rk_res_gtr300_y->at(itk)= fit_results[3].residual_pos.Y();

}

void E16DSTN_ReStraightV2::AddTrackHit(int itk, E16ANA_StraightMultiTrack* single_track){
	single_track->Clear();
	int tid = 0; // only 1 track is fit
	if(isWire){
		single_track->SetInitialVertex(TVector3(rk_fit_init_pos_gx->at(itk), rk_fit_init_pos_gy->at(itk), rk_fit_init_pos_gz->at(itk)), kInitPosErrorWire );
	}
	else {
		single_track->SetInitialVertex(TVector3(rk_fit_init_pos_gx->at(itk), rk_fit_init_pos_gy->at(itk), rk_fit_init_pos_gz->at(itk)), kInitPosError);//maybe not good
	}


	single_track->SetInitialMomentum(tid, TVector3(rk_fit_init_mom_gx->at(itk), rk_fit_init_mom_gy->at(itk), rk_fit_init_mom_gz->at(itk)));
	
	int rk_mids[4] = {rk_fit_sts_mid->at(itk), rk_fit_gtr100_mid->at(itk), rk_fit_gtr200_mid->at(itk), rk_fit_gtr300_mid->at(itk)};
	for(int l=0; l < 4; ++l){
		if(l == E16ANA_StraightTrackConstant::kSSD){
			single_track->AddHit(tid, l, geometry->STS(E16ANA_StraightTrackConstant::ModuleID2020To2013(rk_mids[l])), CorrectedLocalPos(itk, rk_mids[l], l), kSigmas[l]);
		}
		else {
			single_track->AddHit(tid, l, geometry->GTR(E16ANA_StraightTrackConstant::ModuleID2020To2013(rk_mids[l]), l-1), CorrectedLocalPos(itk, rk_mids[l], l), kSigmas[l]);
		}
	}
}

TVector3 E16DSTN_ReStraightV2::CorrectedLocalPos(const int itk, const int mid, const int lid){
	if(lid == 0){//ssd
		 return TVector3(rk_hit_sts_x->at(itk), 0, 0);//sts
	}
	else if(lid == 1){//gtr100
		double lx = rk_hit_gtr100_cogx->at(itk);	//cog
		double ly = rk_hit_gtr100_cogy->at(itk);	//cog
		return TVector3(lx, ly, 0);
	}
	else if(lid == 2){//gtr100
		double lx = rk_hit_gtr200_cogx->at(itk);	//cog
		double ly = rk_hit_gtr200_cogy->at(itk);	//cog
		return TVector3(lx, ly, 0);
	}
	else if(lid == 3){//gtr100
		double lx = rk_hit_gtr300_cogx->at(itk);	//cog
		double ly = rk_hit_gtr300_cogy->at(itk);	//cog
		return TVector3(lx, ly, 0);
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
	pair_fitter->SetRungeKuttaStepSize(15);
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


void E16DSTN_ReStraightV2::ClearUsedClusterIDs() {
	for(auto &ids : used_cluster_ids){
		ids.clear();
	}
	return;
}


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


void E16DSTN_ReStraightV2::InitHistos(){	
//basic 
	h_n_runid = new TH1D("n of events of runid","n of events of runid", 15, 30331.5, 30346.5);
	h_n_eventid = new TH1D("n of events of event id","n of events of eventid", 10000, -0.5, 9999.5);
	h_n_spillid = new TH1D("n of events of spill id","n of events of spillid", 1000, -0.5, 999.5);
	h_chi2    = new TH1D(Form("h_chi2"), Form("h_chi2"), 100, 0, 100);	
	h_t0diff    = new TH1D(Form("h_t0diff"), Form("h_t0diff"), 100, -100,100);	
	h_init_pos = new TH2D(Form("h_init_pos"), Form("h_init_pos"), 50, -30, 30, 50, -60, 60);

	for(int m=0; m < n_modules; m++){
		for(int tg=0; tg < 2; tg++){
//			h_trackmap[tg][m] = new TH2D(Form("h_track_map%d_%d", tg,  m+100), Form("h_track_map%d_%d",tg,  m+100), 25, -50, 50, 25, -50, 50);
		}
		h_chi2_mod[m] = new TH1D(Form("h_chi2_mod%d", m+100), Form("h_chi2_mod%d", m+100), 100, 0, 100);
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
				h_hitmap[m][l] = new TH2D (Form("h_hit_map_%d_%d", m+100, l), Form("h_hit_map_%d_%d", m+100, l), 50,  -50*l , 50 * l, 50, -50 * l , 50*l ) ;
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

	for(int t=0; t < n_wires; t++){// see .hh for definitions
		for(int m=0; m <n_modules;m++){
			for(int l=0; l < n_layers; l++){
				h_res_x_wire[t][m][l] = new TH1D(Form("h_res_x_wire%d_mod%d_n%d", t, m+100, l), Form("h_res_x_wire%d_mod%d_n%d", t, m+100, l), 100, -2.5, 2.5);
				h_res_y_wire[t][m][l] = new TH1D(Form("h_res_y_wire%d_mod%d_n%d", t, m+100, l), Form("h_res_y_wire%d_mod%d_n%d", t, m+100, l), 100, -2.5, 2.5);
			
				if(l == 0 ){
				h_cor_res_fitlx_wire[t][m][l]  = new TH2D(Form("h_cor_res_fitlx_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_res_fitlx_wire%d_m%d_l%d",t,  m+100, l), 20, -30 , 30, 50, -1.5, 1.5);
				}
				else {
				h_cor_res_fitlx_wire[t][m][l]  = new TH2D(Form("h_cor_res_fitlx_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_res_fitlx_wire%d_m%d_l%d",t,  m+100, l), 20, -50*l , 50*l, 50, -2.5, 2.5);

				}
				h_cor_res_fitly_wire[t][m][l]  = new TH2D(Form("h_cor_res_fitly_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_res_fitly_wire%d_m%d_l%d",t,  m+100, l), 20, -50*l , 50*l, 50, -2.5, 2.5);
				h_cor_resx_tan_wire[t][m][l]  = new TH2D(Form("h_cor_resx_tan_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resx_tan_wire%d_m%d_l%d",t,  m+100, l),  20, kHistoTanMin, kHistoTanMax, 50, -2.5, 2.5);
				h_cor_resy_tan_wire[t][m][l]  = new TH2D(Form("h_cor_resy_tan_wire%d_m%d_l%d",t,  m+100, l), Form("h_cor_resy_tan_wire%d_m%d_l%d",t,  m+100, l),  20, kHistoTanMin, kHistoTanMax, 50, -2.5, 2.5);
			}
		}
	}


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
         xtotend = {-100,gtr100x_cluster_last_tot_end->at(i), gtr200x_cluster_last_tot_end->at(i), gtr300x_cluster_last_tot_end->at(i) };
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
		int mid_track = mids[l];//mid in track
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
	for(int l=1; l < n_layers; l++){
		for(int i=0; i < n_hits_x[l]; i++){
			int hid = hits_ids_x[l]->at(i);	
			int mid_track = mids[l];
//			std::cout << "m " << hit_mids_x[l]->at(i) << ", layer " << l << ", hid = "  << hid << std::endl; 
//			if(mid_track != hit_mids_x[l]->at(i) )	continue;
			for(int j=0; j< consist_ids[l]->size(); j++){
				int consist_id = consist_ids[l]->at(j);
//				std::cout << "consist id  = " << consist_id << std::endl;
				if(consist_id == hid){
					h_hit_timing_x[hit_mids_x[l]->at(i) - 100][l]->Fill(hit_timings_x[l]->at(i));
				}
			}
		}
	}
}

void E16DSTN_ReStraightV2::DrawHist(TTree* tree, int n_start, int n_end, int print_cycle, const int residual_layer,  TString pdf_name){	
	int nevent = tree->GetEntries();
	std::cout << "Total N events in the tree : " << nevent << std::endl;
	double mplgy;
	double plgx;
	double pre_mplgy[10] = {9999, 9999, 9999, 9999 ,9999, 9999, 9999, 9999, 9999, 9999};
	double pre_plgx[10] = {9999, 9999, 9999, 9999 ,9999, 9999, 9999, 9999, 9999, 9999};
//	std::vector<double> pre_clusters_x;
//	std::vector<float>  pre_clusters_xadc;
//	std::vector<int>    pre_clusters_mids;
//	int	pre_n_lg_hits;
//	std::vector<int>		pre_lg_hit_mid;
//   std::vector<float>		pre_lg_hit_adc ;
//   std::vector<double>		pre_lg_hit_x ;
//   std::vector<double>		pre_lg_hit_gy;
	int cnt_lgres_fore[10] = {0};
	int cnt_lgres_bg[10]   = {0};

	double chi_sq_th  = 200;

	InitHistos();
	for(int n=0; n < nevent; n++){
		if(n > n_end) break;
		if (n % print_cycle == 0) {
			printf(" N Analyzed = %d \n", n);
		}
		if(n < n_start) continue;
		tree->GetEntry(n);
//
//
//// ------- analysis for pair ------- //
			for(int i=0; i < n_pairs; i++){
				if(rk_pair_plus_chi_square->at(i) < chi_sq_th && rk_pair_minus_chi_square->at(i) < chi_sq_th){
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
//					if( tid0 == track_id->at(j) || tid1 == track_id->at(j)){
//						mids= {	rk_fit_sts_mid->at(j),
//									rk_fit_gtr100_mid->at(j),						
//									rk_fit_gtr200_mid->at(j),
//									rk_fit_gtr300_mid->at(j)};
//						resx = { rk_res_sts_x->at(j),
//									rk_res_gtr100_x->at(j),
//									rk_res_gtr200_x->at(j),
//									rk_res_gtr300_x->at(j)};
//						resy = { 0,
//									rk_res_gtr100_y->at(j),
//									rk_res_gtr200_y->at(j),
//									rk_res_gtr300_y->at(j)};
//						for(int l=1; l < 4; l++){//layer loop
//							h_res_vtx_trk_x[mids[l]-100][l]->Fill(resx[l]);
//							h_res_vtx_trk_y[mids[l]-100][l]->Fill(resy[l]);
//						}
// //1--- residual LG -- //
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
//						}
					}
				}	
			}//analysis for pairs

/// ------- analysis for 1 track ---- // 
		int n_tracks = chi_square->size();//note that n tracks are judged with chi2 vec
      for(int i=0; i < n_tracks;i++){// track loop
	      double chi2 = chi_square->at(i);
			h_chi2->Fill(chi2);
			if(chi2 > chi_sq_th) continue;
			FillVectors(i);//
			#ifndef REMOVE_NOLAYER
			CalculateRemovedGTRMinResidual();
			#endif
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

// Fill Histos 
				h_init_pos->Fill(rk_fit_init_pos_gx->at(i), rk_fit_init_pos_gz->at(i));
			
// Fill Histos GTR
			for(int lid = 0; lid < n_layers; lid++){
				#ifdef NoExist_SSD
				if(lid == 0 ) continue;
				#endif
				h_hitmap[mids[lid]-100][lid]->Fill( fitlxs[lid], fitlys[lid]);
				h_hitmap_x[mids[lid]-100][lid]->Fill( fitlxs[lid]);
				h_hitmap_y[mids[lid]-100][lid]->Fill( fitlys[lid]);
				h_cluster_t_diff[mids[lid]-100][lid]->Fill( xt4s[lid] - yts[lid]);
				h_cluster_t_diff_2d[mids[lid]-100][lid]->Fill( xt4s[lid] ,  yts[lid]);
				h_res_x[mids[lid]-100][lid]->Fill(resx[lid]);
				h_res_y[mids[lid]-100][lid]->Fill(resy[lid]);
				h_cluster_timing_x[mids[lid]-100][lid]->Fill(xt4s[lid]);
				h_cluster_timing_y[mids[lid]-100][lid]->Fill(yts[lid]);
				h_pre_res_x[mids[lid]-100][lid]->Fill(pre_resx[lid]);
				h_cor_res_fitlx[mids[lid]-100][lid]->Fill(fitlxs[lid], resx[lid]);	
				h_cor_res_fitly[mids[lid]-100][lid]->Fill(fitlys[lid], resx[lid]);	
//									h_cor_res_timing[mids[l]-100][l]->Fill(xt4s[l], resx[l]);	//timing
//									h_tan_theta[mids[l]-100][l]     ->Fill(tans[l]);
//									h_cor_dz_time[mids[l]-100][l]   ->Fill(xt4s[l], resx[l]/tans[l]);	
////									h_cor_dz_time_t0cor[mid-100][l] ->Fill(xt4s[l] - t0diff, resx[l]/tans[l]);//plus or minus?
////										h_slopevel[mid-100][l][ith_div]->Fill((xt4s[l] - 250) * tans[l], resx[l] ); 
				h_tot_end_fr[mids[lid]-100][lid]->Fill(xtotend[lid]);
				}
			FillPulseInfos(i);
		}//track loop
//
//
#ifndef REMOVE_NOLAYER
#ifdef REMOVE_GTR100
	pre_n_gtrx_clusters    = n_gtr100x_clusters;
   pre_gtrx_cluster_x.resize(pre_n_gtrx_clusters); 
   pre_gtrx_cluster_adc.resize(pre_n_gtrx_clusters); 
   pre_gtrx_cluster_mid.resize(pre_n_gtrx_clusters); 
	for(int k=0; k < pre_n_gtrx_clusters;k++){
		pre_gtrx_cluster_x[k]    = gtr100x_cluster_x->at(k);
		pre_gtrx_cluster_adc[k] = gtr100x_cluster_adc->at(k);
		pre_gtrx_cluster_mid[k] = gtr100x_cluster_mid->at(k);
	}
#elif REMOVE_GTR200
	pre_n_gtrx_clusters    = n_gtr200x_clusters;
   pre_gtrx_cluster_x.resize(pre_n_gtrx_clusters); 
   pre_gtrx_cluster_adc.resize(pre_n_gtrx_clusters); 
   pre_gtrx_cluster_mid.resize(pre_n_gtrx_clusters); 
	for(int k=0; k < pre_n_gtrx_clusters;k++){
		pre_gtrx_cluster_x[k]    = gtr200x_cluster_x->at(k);
		pre_gtrx_cluster_adc[k] = gtr200x_cluster_adc->at(k);
		pre_gtrx_cluster_mid[k] = gtr200x_cluster_mid->at(k);
	}

#elif REMOVE_GTR300
	pre_n_gtrx_clusters    = n_gtr300x_clusters;
   pre_gtrx_cluster_x.resize(pre_n_gtrx_clusters); 
   pre_gtrx_cluster_adc.resize(pre_n_gtrx_clusters); 
   pre_gtrx_cluster_mid.resize(pre_n_gtrx_clusters); 
	for(int k=0; k < pre_n_gtrx_clusters;k++){
		pre_gtrx_cluster_x[k]    = gtr300x_cluster_x->at(k);
		pre_gtrx_cluster_adc[k] = gtr300x_cluster_adc->at(k);
		pre_gtrx_cluster_mid[k] = gtr300x_cluster_mid->at(k);
	}
	#endif
#endif 

// --- Filled lg previous event --- // 
		pre_n_lg_hits = n_lg_hits;
		pre_lg_hit_mid.resize(n_lg_hits);
		pre_lg_hit_adc.resize(n_lg_hits);
		pre_lg_hit_x .resize(n_lg_hits);
		pre_lg_hit_gy.resize(n_lg_hits);
		for(int k=0; k < n_lg_hits; k++){
			pre_lg_hit_mid[k] = lg_hit_mid->at(k);
			pre_lg_hit_adc[k] = lg_hit_adc->at(k);
			pre_lg_hit_x[k]  =  lg_hit_x->at(k);
			pre_lg_hit_gy[k] =  lg_hit_gy->at(k);
		}

	}// event loop

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

//
//
//  TCanvas *c_res_v[10];
//  for(int m =1; m < 9; m++){ 
//    c_res_v[m]= new TCanvas(); 
//    c_res_v[m]->Divide(2,2);
//    for(int l=0; l < n_layer; l++){
//     c_res_v[m]->cd(1+l);
//     if(m < 5) {
//        h_res_vtx_trk_x[m][l]->Fit("gaus", "", "", -0.5, 0.2);
//        h_res_vtx_trk_x[m][l]->Draw("colz");
//     }
//     else {
//        h_res_vtx_trk_x[m+1][l]->Fit("gaus", "", "", -0.5, 0.2);
//        h_res_vtx_trk_x[m+1][l]->Draw("colz");
//     
//	 }
//    c_res_v[m]->SaveAs(pdf_name, "pdf");
//  }

//


	TCanvas *chm[n_modules];
	for(int m =1; m < 9; m++){
		if(m == 5) continue;
	   chm[m]= new TCanvas();
		chm[m]->Divide(4,3);
		for(int l=0; l < 4; l++){
   		chm[m]->cd(l+1);
			h_hitmap[m][l]->Draw("colz");
   		chm[m]->cd(l+5);
			h_hitmap_x[m][l]->Draw();
   		chm[m]->cd(l+9);
			h_hitmap_y[m][l]->Draw();
   	}
   	chm[m]->SaveAs(pdf_name, "pdf");
	}

		

	TCanvas *chtd[n_modules];
	for(int m =1; m < 9; m++){
		if(m == 5) continue;
	   chtd[m]= new TCanvas();
		chtd[m]->Divide(4,2);
		for(int l=0; l < 4; l++){
   		chtd[m]->cd(l+1);
      	h_cluster_t_diff[m][l]->Draw();
   		chtd[m]->cd(l+5);
      	h_cluster_t_diff_2d[m][l]->Draw("colz");
   	}
   	chtd[m]->SaveAs(pdf_name, "pdf");
	}




	TCanvas *c2[n_modules];
	for(int m =1; m < 9; m++){
	   c2[m]= new TCanvas();
		c2[m]->Divide(4,2);
		for(int l=0; l < 4; l++){
   		c2[m]->cd(l+1);
	      if(m < 5) {
      	   h_cluster_timing_x[m][l]->Draw("colz");
   			c2[m]->cd(l+5);
      	   h_cluster_timing_y[m][l]->Draw("colz");
   	   }
 	     else {
         	h_cluster_timing_x[m][l]->Draw("colz");
   			c2[m]->cd(l+5);
         	h_cluster_timing_y[m][l]->Draw("colz");
      	}
   	}
   c2[m]->SaveAs(pdf_name, "pdf");
	}


	TCanvas *cht[n_modules];
	for(int m =1; m < 9; m++){
		if(m == 5) continue;
	   cht[m]= new TCanvas();
		cht[m]->Divide(2,2);
		for(int l=0; l < 4; l++){
   		cht[m]->cd(l+1);
      	h_hit_timing_x[m][l]->Draw();
   	}
   cht[m]->SaveAs(pdf_name, "pdf");
	}




TCanvas *c03 = new TCanvas();
h_init_pos->Draw("colz");
c03->SaveAs(pdf_name, "pdf");


	TCanvas *c22[n_modules];
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


	TCanvas *c23[n_modules];
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
         h_init_posz_mod[i]->Draw("colz");
      }
      else {
         h_init_posz_mod[i+1]->Draw("colz");
      }
   }
   c04->SaveAs(pdf_name, "pdf");



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

  TCanvas *c1[10];
  for(int m =1; m < 9; m++){ 
    c1[m]= new TCanvas(); 
    c1[m]->Divide(2,2);
    for(int l=0; l < n_layers; l++){
     c1[m]->cd(1+l);
     if(m < 5) {
        h_res_x[m][l]->Fit("gaus", "", "", -0.5, 0.5);
        h_res_x[m][l]->Draw("colz");
		  h_pre_res_x[m][l]->SetLineColor(kRed);
		  h_pre_res_x[m][l]->Draw("same");

     }
     else {
        h_res_x[m+1][l]->Fit("gaus", "", "", -0.5, 0.5);
        h_res_x[m+1][l]->Draw("colz");
		  h_pre_res_x[m+1][l]->SetLineColor(kRed);
		  h_pre_res_x[m+1][l]->Draw("same");
     }
	 }
    c1[m]->SaveAs(pdf_name, "pdf");
  }

  TCanvas *cresy[10];
  for(int m =1; m < 9; m++){ 
    cresy[m]= new TCanvas(); 
    cresy[m]->Divide(2,2);
    for(int l=0; l < n_layers; l++){
     cresy[m]->cd(1+l);
     if(m < 5) {
        h_res_y[m][l]->Fit("gaus", "", "", -0.5, 0.5);
        h_res_y[m][l]->Draw("colz");
//		  h_pre_res_y[m][l]->SetLineColor(kRed);
//		  h_pre_res_y[m][l]->Draw("same");

     }
     else {
        h_res_y[m+1][l]->Fit("gaus", "", "", -0.5, 0.5);
        h_res_y[m+1][l]->Draw("colz");
//		  h_pre_res_y[m+1][l]->SetLineColor(kRed);
//		  h_pre_res_y[m+1][l]->Draw("same");
     }
	 }
    cresy[m]->SaveAs(pdf_name, "pdf");
  }




   TCanvas *c31[10][4];
   TGraphErrors *gr[10][4];
   TGraphErrors *gr_mean[10][4];
   TH1D *h1[10][4];
   TF1 *f1[10][4];
   for(int hmid=101; hmid < 110; hmid++){
      if(hmid == 105)continue;
				for(int l=0; l < n_layers;l++){
            c31[hmid-100][l] = new TCanvas();
            c31[hmid-100][l]->Divide(5,5);
            int n = h_cor_res_fitlx[hmid-100][l]->GetNbinsX();
            double xmin = -1;
            double xmax =  1;
            std::cout << "nibs = " << n << std::endl;
            gr[hmid-100][l] = new TGraphErrors(n);
            gr[hmid-100][l]->SetTitle(Form("X Residual Sigma m%d l%d; local x; sigma", hmid, l ));
            gr_mean[hmid-100][l] = new TGraphErrors(n);
            gr_mean[hmid-100][l]->SetTitle(Form("X Residual Mean m%d l%d; local x; mean", hmid, l ));
             for (int i = 1; i <= n; i++) {
               c31[hmid-100][l]->cd(i);
               h1[hmid-100][l] = h_cor_res_fitlx[hmid-100][l]->ProjectionY(Form("x_py_m%d_l%d_%d", hmid, l, i), i, i     );
//             f1[hmid-100] = new TF1(Form("f1%d%d",hmid, i), "gaus");
               f1[hmid-100][l] = new TF1(Form("f%d%d", hmid, l), "gaus(0) + [3]+[4]*x+[5]*x*x+[6]*x*x*x",      xmin, xmax);
               f1[hmid-100][l]->SetParameter(0, 500);   // constant
               f1[hmid-100][l]->SetParameter(1, 0);     // mean
               f1[hmid-100][l]->SetParLimits(1, -2, 2); // mean
               f1[hmid-100][l]->SetParameter(2, 0.3);
               f1[hmid-100][l]->SetParLimits(2, 0.1, 1);
               f1[hmid-100][l]->SetParameter(3, 0);
               f1[hmid-100][l]->SetParameter(4, -1);
               h1[hmid-100][l]->Fit(f1[hmid-100][l], "", "", xmin, xmax);
 				   double mean      = f1[hmid-100][l]->GetParameter(1);
 				   double mean_err  = f1[hmid-100][l]->GetParError(1);
               double sigma     = f1[hmid-100][l]->GetParameter(2);
               double sigma_err = f1[hmid-100][l]->GetParError(2);
               std::cout << "sigma = " << sigma << std::endl;
               gr[hmid-100][l]->SetPoint(i-1, i, sigma);
               gr[hmid-100][l]->SetPointError(i-1, 0, sigma_err);
               gr_mean[hmid-100][l]->SetPoint(i-1, i, mean);
               gr_mean[hmid-100][l]->SetPointError(i-1, 0, mean_err);
               h1[hmid-100][l]->Draw();
            }
         c31[hmid-100][l]->cd(23);
         gr[hmid-100][l]->SetMaximum(0.5);
         gr[hmid-100][l]->SetMinimum(-0.5);
         gr[hmid-100][l]->Draw("ap");
         c31[hmid-100][l]->cd(24);
 			gr_mean[hmid-100][l]->SetMaximum(1.0);
 			gr_mean[hmid-100][l]->SetMinimum(-1.0);
 			gr_mean[hmid-100][l]->SetLineStyle(0);
         gr_mean[hmid-100][l]->Draw("ap");
         c31[hmid-100][l]->SaveAs(pdf_name, "pdf");
		}
   }



	TCanvas *c31a[n_modules];
	for(int m =1; m < 9; m++){
		if(m==5) continue;
	   c31a[m]= new TCanvas();
		c31a[m]->Divide(4,2);
		for(int l=0; l < 4; l++){
   		c31a[m]->cd(l+1);
			gr[m][l]->Draw("ap");
   		c31a[m]->cd(l+5);
			gr_mean[m][l]->Draw("ap");
      }
   c31a[m]->SaveAs(pdf_name, "pdf");
	}


   TCanvas *c31y[10][4];
   TGraphErrors *gr_y[10][4];
   TGraphErrors *gr_y_mean[10][4];
   TH1D *h1y[10][4];
   TF1 *f1y[10][4];
   for(int hmid=101; hmid < 110; hmid++){
      if(hmid == 105)continue;
				for(int l=0; l < n_layers;l++){
            c31y[hmid-100][l] = new TCanvas();
            c31y[hmid-100][l]->Divide(5,5);
            int n = h_cor_res_fitly[hmid-100][l]->GetNbinsX();
            double xmin = -1;
            double xmax =  1;
            std::cout << "nibs = " << n << std::endl;
            gr_y[hmid-100][l] = new TGraphErrors(n);
            gr_y[hmid-100][l]->SetTitle(Form("Y Residual Sigma m%d l%d; local y; sigma", hmid, l ));
            gr_y_mean[hmid-100][l] = new TGraphErrors(n);
            gr_y_mean[hmid-100][l]->SetTitle(Form("Y Residual Mean m%d l%d; local y; mean", hmid, l ));
             for (int i = 1; i <= n; i++) {
               c31y[hmid-100][l]->cd(i);
               h1y[hmid-100][l] = h_cor_res_fitly[hmid-100][l]->ProjectionY(Form("y_py_m%d_l%d_%d", hmid, l, i), i, i     );
//             f1y[hmid-100] = new TF1(Form("f1y%d%d",hmid, i), "gaus");
               f1y[hmid-100][l] = new TF1(Form("f%d%d", hmid, l), "gaus(0) + [3]+[4]*x+[5]*x*x+[6]*x*x*x",      xmin, xmax);
               f1y[hmid-100][l]->SetParameter(0, 500);   // constant
               f1y[hmid-100][l]->SetParameter(1, 0);     // mean
               f1y[hmid-100][l]->SetParLimits(1, -2, 2); // mean
               f1y[hmid-100][l]->SetParameter(2, 0.3);
               f1y[hmid-100][l]->SetParLimits(2, 0.1, 1);
               f1y[hmid-100][l]->SetParameter(3, 0);
               f1y[hmid-100][l]->SetParameter(4, -1);
               h1y[hmid-100][l]->Fit(f1y[hmid-100][l], "", "", xmin, xmax);
 				   double mean      = f1y[hmid-100][l]->GetParameter(1);
 				   double mean_err  = f1y[hmid-100][l]->GetParError(1);
               double sigma     = f1y[hmid-100][l]->GetParameter(2);
               double sigma_err = f1y[hmid-100][l]->GetParError(2);
               std::cout << "sigma = " << sigma << std::endl;
               gr_y[hmid-100][l]->SetPoint(i-1, i, sigma);
               gr_y[hmid-100][l]->SetPointError(i-1, 0, sigma_err);
               gr_y_mean[hmid-100][l]->SetPoint(i-1, i, mean);
               gr_y_mean[hmid-100][l]->SetPointError(i-1, 0, mean_err);
               h1y[hmid-100][l]->Draw();
            }
         c31y[hmid-100][l]->cd(23);
         gr_y[hmid-100][l]->SetMaximum(0.5);
         gr_y[hmid-100][l]->SetMinimum(-0.5);
         gr_y[hmid-100][l]->Draw("ap");
         c31y[hmid-100][l]->cd(24);
 			gr_y_mean[hmid-100][l]->SetMaximum(1.0);
 			gr_y_mean[hmid-100][l]->SetMinimum(-1.0);
 			gr_y_mean[hmid-100][l]->SetLineStyle(0);
         gr_y_mean[hmid-100][l]->Draw("ap");
         c31y[hmid-100][l]->SaveAs(pdf_name, "pdf");
		}
   }


	TCanvas *c31b[n_modules];
	for(int m =1; m < 9; m++){
		if(m==5) continue;
	   c31b[m]= new TCanvas();
		c31b[m]->Divide(4,2);
		for(int l=0; l < 4; l++){
   		c31b[m]->cd(l+1);
			gr_y[m][l]->Draw("ap");
   		c31b[m]->cd(l+5);
			gr_y_mean[m][l]->Draw("ap");
      }
   c31b[m]->SaveAs(pdf_name, "pdf");
	}





	TCanvas *c18;
	c18 = new TCanvas();
	c18->Divide(4,2);
	for(int mid=101; mid < 110; mid++){
		if(mid == 105) continue;
		if(mid < 105){
		c18->cd(mid-100);
		h_res_lg_x[mid-100]->Draw();
		h_bak_res_lg_x[mid-100]->SetLineColor(kRed);
		h_bak_res_lg_x[mid-100]->Draw("sames");
		}
	   else if(mid > 105){
			c18->cd(mid-101);
			h_res_lg_x[mid-100]->Draw();
			h_bak_res_lg_x[mid-100]->SetLineColor(kRed);
			h_bak_res_lg_x[mid-100]->Draw("sames");
			
		}
   }
	c18->SaveAs(pdf_name, "pdf");

   TCanvas *c19;
	c19 = new TCanvas();
	c19->Divide(4,2);
	for(int mid=101; mid < 110; mid++){
		if(mid == 105) continue;
		if(mid < 105){
		c19->cd(mid-100);
		h_res_lg_y[mid-100]->Draw();
		h_bak_res_lg_y[mid-100]->SetLineColor(kRed);
		h_bak_res_lg_y[mid-100]->Draw("sames");
		}
	   else if(mid > 105){
			c19->cd(mid-101);
			h_res_lg_y[mid-100]->Draw();
			h_bak_res_lg_y[mid-100]->SetLineColor(kRed);
			h_bak_res_lg_y[mid-100]->Draw("sames");
			
		}
   }
	c19->SaveAs(pdf_name, "pdf");

   TCanvas *c20;
	c20 = new TCanvas();
	c20->Divide(4,2);
	for(int mid=101; mid < 110; mid++){
		if(mid == 105) continue;
		if(mid < 105){
		c20->cd(mid-100);
		h_res_lg_2d[mid-100]->Draw("colz");
//		h_bak_res_lg_2d[mid-100]->SetLineColor(kRed);
//		h_bak_res_lg_2d[mid-100]->Draw("same");
		}
	   else if(mid > 105){
			c20->cd(mid-101);
			h_res_lg_2d[mid-100]->Draw("colz");
//			h_bak_res_lg_2d[mid-100]->SetLineColor(kRed);
//			h_bak_res_lg_2d[mid-100]->Draw("same");
			
		}
   }
	c20->SaveAs(pdf_name, "pdf");


   TCanvas *c20_bg;
	c20_bg = new TCanvas();
	c20_bg->Divide(4,2);
	for(int mid=101; mid < 110; mid++){
		if(mid == 105) continue;
		if(mid < 105){
		c20_bg->cd(mid-100);
		h_bak_res_lg_2d[mid-100]->Draw("colz");
//		h_bak_res_lg_2d[mid-100]->SetLineColor(kRed);
//		h_bak_res_lg_2d[mid-100]->Draw("same");
		}
	   else if(mid > 105){
			c20_bg->cd(mid-101);
			h_bak_res_lg_2d[mid-100]->Draw("colz");
//			h_bak_res_lg_2d[mid-100]->SetLineColor(kRed);
//			h_bak_res_lg_2d[mid-100]->Draw("same");
		}
   }
	c20_bg->SaveAs(pdf_name, "pdf");

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
//
//
//
//TCanvas *c16b[2][10][n_div];
//TGraphErrors *gr16b[2][10][n_div];
//TH1D *h16b[2][10][n_div];
//TF1 *f16b[2][10][n_div];
//TF1 *flab[2][10][n_div];
//double xminb[10]  = {0, -4, -7, -7,     -6, 0, -4, -5.5, -4, -4};//mod100-109
//double xmaxb[10]  = {0,  4, 10, 10,    5.5, 0,   4,  4.0,  5,  5};
//double flminb[10] = {0, 120, 120, 120, 120, 0, 200, 120, 100, 180};
//double flmaxb[10] = {0, 450, 450, 450, 450, 0, 550, 450, 320, 450};
//for(int t=0; t < 2; t++){
// int hmid = 106;
// for(int d=0 ; d < n_div; d++){
//   c16b[t][hmid-100][d] = new TCanvas();
//   int n = h_cor_dz_time_t0cor[hmid-100][residual_layer][d]->GetNbinsX();
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
//TCanvas *c0d = new TCanvas();
//t0diff->Draw();
//d->SaveAs(pdf_name, "pdf");

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
//
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


	for(int m=0; m < 10; m++){
	std::cout << "m = " << m+100 << ",fore lg residual = " << cnt_lgres_fore[m] << ", bg lg residual = " << cnt_lgres_bg[m] << std::endl;
	}
	c0->SaveAs(pdf_name + "]", "pdf");
}






//void E16DSTN_ReStraightV2::DrawHistWire(TTree* tree, int n_start, int n_end, int print_cycle, const int residual_layer,  TString pdf_name){	
//	int nevent = tree->GetEntries();
//	std::cout << "Total N events in the tree : " << nevent << std::endl;
//	int cnt_lgres_fore[10] = {0};
//	int cnt_lgres_bg[10]   = {0};
////conditions 
//	double chi_sq_th  = 200;
////initialize Histos
//	InitHistos();
////Analysis part
//	for(int n=0; n < nevent; n++){
//		if(n > n_end) break;
//		if (n % print_cycle == 0) {
//			printf(" N Analyzed = %d \n", n);
//		}
//		if(n < n_start) continue;
//		tree->GetEntry(n);
//		int n_tracks = chi_square->size();//note that n tracks are judged with chi2 vec
//      for(int i=0; i < n_tracks;i++){// track loop
//	      double chi2 = chi_square->at(i);
//			h_chi2->Fill(chi2);
//			if(chi2 > chi_sq_th) continue;
//			FillVectors(i);//
//
//// ----- LG Asssociation --------- // 
//				bool assoc_fore = false;
//				bool assoc_bg = false;
//				double plgx  = rk_fit_lg_b_x->at(i);
//				double mplgy = rk_fit_lg_b_gy->at(i);
//				if(fabs(mplgy) > 260){
//					plgx = rk_fit_lg_c_x->at(i);
//				}
//				if(fabs(mplgy) < 150){
//					plgx = rk_fit_lg_a_x->at(i);
//				}
//	// --- fore event --- //
//				for(int k=0; k < n_lg_hits;k++){
//					if(lg_hit_mid->at(k) == rk_fit_lg_b_mid->at(i)){
//						int lg_mid = lg_hit_mid->at(k);
//						if(lg_hit_adc->at(k) < 10) continue;
//			//			if(fabs(lg_hit_x->at(k) - 310) < 1 && fabs(lg_hit_y->at(k) + 315) < 1) continue; 
//						double dx     = lg_hit_x->at(k) - plgx;
//						double dy     = lg_hit_gy->at(k) - mplgy;
//						h_res_lg_x[lg_mid-100]->Fill(dx);
//						h_res_lg_y[lg_mid-100]->Fill(dy);
//						h_res_lg_2d[lg_mid-100]->Fill(dx,dy);
//						if(fabs(dx) < 80 & fabs(dy) < 80 ){//association
//							assoc_fore = true;
//						}
//					}
//				}
//	// ----- previous event ---- // 
//				for(int k=0; k < pre_n_lg_hits;k++){
//					if(pre_lg_hit_mid[k] == rk_fit_lg_b_mid->at(i)){
//						int lg_mid = pre_lg_hit_mid[k];
//						if(pre_lg_hit_adc[k] < 10) continue;
//			//			if(fabs(pre_lg_hit_x[k] - 310) < 1 && fabs(pre_lg_hit_gy[k] + 315) < 1) continue; 
//							double pre_dx = pre_lg_hit_x[k]  - plgx;
//							double pre_dy = pre_lg_hit_gy[k] - mplgy;
//							h_bak_res_lg_x[lg_mid-100]->Fill(pre_dx);
//							h_bak_res_lg_y[lg_mid-100]->Fill(pre_dy);
//							h_bak_res_lg_2d[lg_mid-100]->Fill(pre_dx, pre_dy);
//						if(fabs(pre_dx) < 80 & fabs(pre_dy) < 80 ){//association
//							assoc_bg = true;
//						}
//					}
//				}
//			//
//				if(assoc_fore){
//					cnt_lgres_fore[rk_fit_lg_b_mid->at(i)-100]++;
//				}
//				if(assoc_bg){
//					cnt_lgres_bg[rk_fit_lg_b_mid->at(i) -100]++;
//				}
//// -- LG association finished ---- /// 
//
////			pre_mplgy[rk_fit_lg_b_mid->at(i)-100] = mplgy;
////			pre_plgx[rk_fit_lg_b_mid->at(i)-100] = plgx;
////			h_cluster_timing_chi2[m-100][l]->Fill(xt4s[l]);
//////		h_cluster_timing_chi2_xdependence[m-100][l][nth_div]->Fill(xt4s[l]);
//////		h_cluster_timing_chi2_ydependence[m-100][l][nth_divy]->Fill(xt4s[l]);
//////		h_cluster_adc_xdependence[m-100][l][nth_div]->Fill(xadcs[l]);
//////		h_cluster_adc_ydependence[m-100][l][nth_divy]->Fill(yadcs[l]);
//
//// Fill Histos Basic
//				h_init_pos->Fill(rk_fit_init_pos_gx->at(i), rk_fit_init_pos_gz->at(i));
//			
//// Fill Histos detectors
//			for(int lid = 0; lid < n_layers; lid++){
//				h_hitmap[mids[lid]-100][lid]->Fill( fitlxs[lid], fitlys[lid]);
//				h_hitmap_x[mids[lid]-100][lid]->Fill( fitlxs[lid]);
//				h_hitmap_y[mids[lid]-100][lid]->Fill( fitlys[lid]);
//				h_cluster_t_diff[mids[lid]-100][lid]->Fill( xt4s[lid] - yts[lid]);
//				h_cluster_t_diff_2d[mids[lid]-100][lid]->Fill( xt4s[lid] ,  yts[lid]);
//				h_res_x[mids[lid]-100][lid]->Fill(resx[lid]);
//				h_res_y[mids[lid]-100][lid]->Fill(resy[lid]);
//				h_cluster_timing_x[mids[lid]-100][lid]->Fill(xt4s[lid]);
//				h_cluster_timing_y[mids[lid]-100][lid]->Fill(yts[lid]);
//				h_pre_res_x[mids[lid]-100][lid]->Fill(pre_resx[lid]);
//				h_cor_res_fitlx[mids[lid]-100][lid]->Fill(fitlxs[lid], resx[lid]);	
//				h_cor_res_fitly[mids[lid]-100][lid]->Fill(fitlys[lid], resx[lid]);	
////									h_cor_res_timing[mids[l]-100][l]->Fill(xt4s[l], resx[l]);	//timing
////									h_tan_theta[mids[l]-100][l]     ->Fill(tans[l]);
////									h_cor_dz_time[mids[l]-100][l]   ->Fill(xt4s[l], resx[l]/tans[l]);	
//////									h_cor_dz_time_t0cor[mid-100][l] ->Fill(xt4s[l] - t0diff, resx[l]/tans[l]);//plus or minus?
//////										h_slopevel[mid-100][l][ith_div]->Fill((xt4s[l] - 250) * tans[l], resx[l] ); 
//				h_tot_end_fr[mids[lid]-100][lid]->Fill(xtotend[lid]);
//				}
//			FillPulseInfos(i);
//		}//track loop
//	}
//}
