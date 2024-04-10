#include "E16DSTN_PosCorrection.hh"
#include "E16ANA_StraightTrackConstant.hh"
//#include "E16ANA_StraightTrackParameter.hh"
#include "E16ANA_StraightMultiTrack.hh"
#include <map>

//using namespace E16ANA_StraightTrackParameter;
using namespace E16DSTN_StraightParameter;


void E16DSTN_PosCorrection::PosCoLoop(TTree *tree, int print_cycle, int max_event, bool vertex_xy_fix_flag, bool py_fix_flag, bool  vetex_z_fix_flag, int analysisSW) { 

	int nevent = tree->GetEntries();
	std::cout << "nevent = " << nevent << std::endl;
	for(int n=0; n < nevent; n++){
		if(max_event != -1 && n > max_event){
			std::cout  << "N event analzyed reached to max event" << std::endl;
			break;
		}
		if ( n % print_cycle == 0) {
			printf("N re-analyzed = %d \n", n);
		}	
	tree->GetEntry(n);//read tree

	good_ids.clear();
	sorted_ids.clear();
	killdup_ids.clear();

	if(analysisSW == 0){//dulication cut first 
	ResizeTmpVectors();
	ChiSqSort(sorted_ids);//output vec
	SetTracks(sorted_ids, good_ids);//in/out vec
	ClearUsedClusterIDs();
	RemoveDuplicatedHits(good_ids, killdup_ids);
	CorrectionFit(killdup_ids);
	AddRecord(killdup_ids);
	}
	else if (analysisSW == 1){//Re-Fit First
	ResizeTmpVectors();
	SetTracks(good_ids);//good tracks are choosen based on chi2, targetpos 
	CorrectionFit(good_ids);
	ChiSqSort(good_ids, sorted_ids);//in out
	ClearUsedClusterIDs();
	RemoveDuplicatedHits(sorted_ids, killdup_ids);
	AddRecord(killdup_ids);
	}
	}
}


void E16DSTN_PosCorrection::ResizeTmpVectors(){
 tmp_rk_fit_ssd_mid.resize(n_cands)  ;
 tmp_rk_fit_ssd_x.resize(n_cands);
 tmp_rk_fit_ssd_y.resize(n_cands);
 tmp_rk_fit_ssd_gx.resize(n_cands);
 tmp_rk_fit_ssd_gy.resize(n_cands);
 tmp_rk_fit_ssd_gz.resize(n_cands);
 tmp_rk_fit_ssd_mom_x.resize(n_cands);
 tmp_rk_fit_ssd_mom_y.resize(n_cands);
 tmp_rk_fit_ssd_mom_z.resize(n_cands);
 tmp_rk_fit_ssd_mom_gx.resize(n_cands);
 tmp_rk_fit_ssd_mom_gy.resize(n_cands);
 tmp_rk_fit_ssd_mom_gz.resize(n_cands);
 tmp_rk_res_ssd_x   .resize(n_cands);
 tmp_rk_fit_gtr100_mid.resize(n_cands);
 tmp_rk_fit_gtr200_mid.resize(n_cands);
 tmp_rk_fit_gtr300_mid.resize(n_cands);
 tmp_rk_fit_gtr100_x.resize(n_cands);
 tmp_rk_fit_gtr200_x.resize(n_cands);
 tmp_rk_fit_gtr300_x.resize(n_cands);
 tmp_rk_fit_gtr100_y.resize(n_cands);
 tmp_rk_fit_gtr200_y.resize(n_cands);
 tmp_rk_fit_gtr300_y.resize(n_cands);
 tmp_rk_fit_gtr100_gx.resize(n_cands);
 tmp_rk_fit_gtr200_gx.resize(n_cands);
 tmp_rk_fit_gtr300_gx.resize(n_cands);
 tmp_rk_fit_gtr100_gy.resize(n_cands);
 tmp_rk_fit_gtr200_gy.resize(n_cands);
 tmp_rk_fit_gtr300_gy.resize(n_cands);
 tmp_rk_fit_gtr100_gz.resize(n_cands);
 tmp_rk_fit_gtr200_gz.resize(n_cands);
 tmp_rk_fit_gtr300_gz.resize(n_cands);
 tmp_rk_fit_gtr100_mom_x.resize(n_cands);
 tmp_rk_fit_gtr200_mom_x.resize(n_cands);
 tmp_rk_fit_gtr300_mom_x.resize(n_cands);
 tmp_rk_fit_gtr100_mom_y.resize(n_cands);
 tmp_rk_fit_gtr200_mom_y.resize(n_cands);
 tmp_rk_fit_gtr300_mom_y.resize(n_cands);
 tmp_rk_fit_gtr100_mom_z.resize(n_cands);
 tmp_rk_fit_gtr200_mom_z.resize(n_cands);
 tmp_rk_fit_gtr300_mom_z.resize(n_cands);
 tmp_rk_fit_gtr100_mom_gx.resize(n_cands);
 tmp_rk_fit_gtr200_mom_gx.resize(n_cands);
 tmp_rk_fit_gtr300_mom_gx.resize(n_cands);
 tmp_rk_fit_gtr100_mom_gy.resize(n_cands);
 tmp_rk_fit_gtr200_mom_gy.resize(n_cands);
 tmp_rk_fit_gtr300_mom_gy.resize(n_cands);
 tmp_rk_fit_gtr100_mom_gz.resize(n_cands);
 tmp_rk_fit_gtr200_mom_gz.resize(n_cands);
 tmp_rk_fit_gtr300_mom_gz.resize(n_cands);
 tmp_rk_res_init_pos_gx.resize(n_cands);
 tmp_rk_res_init_pos_gy.resize(n_cands);
 tmp_rk_res_init_pos_gz.resize(n_cands);
 tmp_rk_res_init_mom_gx.resize(n_cands);
 tmp_rk_res_init_mom_gy.resize(n_cands);
 tmp_rk_res_init_mom_gz.resize(n_cands);
 tmp_rk_res_gtr100_x.resize(n_cands);
 tmp_rk_res_gtr100_y.resize(n_cands);
 tmp_rk_res_gtr200_x.resize(n_cands);
 tmp_rk_res_gtr200_y.resize(n_cands);
 tmp_rk_res_gtr300_x.resize(n_cands);
 tmp_rk_res_gtr300_y.resize(n_cands);
	
 tmp_rk_fit_init_pos_gx.resize(n_cands);
 tmp_rk_fit_init_pos_gy.resize(n_cands);
 tmp_rk_fit_init_pos_gz.resize(n_cands);
 tmp_rk_fit_init_mom_gx.resize(n_cands);
 tmp_rk_fit_init_mom_gy.resize(n_cands);
 tmp_rk_fit_init_mom_gz.resize(n_cands);
}

void E16DSTN_PosCorrection::ChiSqSort( std::vector<int> &outids){
	int n_chisq = chi_square->size();
	int n_tracks = n_cands;
	if(n_chisq != n_cands ){
		std::cout << "it is bug ! " << std::endl;
		exit(1);
	}
	std::multimap<double,int> chi2_trkid_map;
	std::multimap<double,std::array<FitResult, E16ANA_StraightTrackConstant::kNumDetectorLayers>> chi2_fitres_map;
	for(int i=0; i < n_tracks;i++){
		chi2_trkid_map.insert(std::make_pair(chi_square->at(i), i));
	}
	for(const auto &el : chi2_trkid_map){
		outids.push_back(el.second);
	}
}

void E16DSTN_PosCorrection::ChiSqSort( std::vector<int> &inids, std::vector<int> &outids){
	int n_chisq = chisq.size();
	int n_tracks = inids.size();
	if(n_chisq != n_tracks ){
		std::cout << "it is bug ! " << std::endl;
		exit(1);
	}
	std::multimap<double,int> chi2_trkid_map;
	std::multimap<double,std::array<FitResult, E16ANA_StraightTrackConstant::kNumDetectorLayers>> chi2_fitres_map;
	for(int i=0; i < n_tracks;i++){
		chi2_trkid_map.insert(std::make_pair(chisq[i], inids[i]));
	}
	for(const auto &el : chi2_trkid_map){
		outids.push_back(el.second);
	}
}


void E16DSTN_PosCorrection::RemoveDuplicatedHits(std::vector<int> &in_ids, std::vector<int> &out_ids){
	
	for(int i=0; i < in_ids.size() ; i++){
		int tid = in_ids[i];
		if(removed_layer ==-1){
			std::array<int, kNumTrackingDetectors> cids = {
			rk_hit_ssd_id->at(tid),
			rk_hit_gtr100_xid->at(tid), rk_hit_gtr100_yid->at(tid),
			rk_hit_gtr200_xid->at(tid), rk_hit_gtr200_yid->at(tid),
			rk_hit_gtr300_xid->at(tid), rk_hit_gtr300_yid->at(tid)};
			if(HasUsedCluster(cids)){
				continue;			
			} else {
				for (int j=0; j  <  kNumTrackingDetectors;j++){
					used_cluster_ids[j].emplace_back(cids[j]);
				}
			out_ids.emplace_back(tid);
			}
		}
		else {
			std::cerr << "not developed yet" << std::endl;
		}
	}
}


bool E16DSTN_PosCorrection::HasUsedCluster(const std::array<int, kNumTrackingDetectors> &cids){
  for (int i = 0; i < kNumTrackingDetectors; ++i) {
     for (const auto& used_id : used_cluster_ids[i]) {
       if (cids[i] == used_id) {
         return true;
       }
     }
   }
   return false;
}


bool E16DSTN_PosCorrection::IsComingFromTarget(int i){
	if(isWire){
		if( fabs(rk_fit_init_pos_gy->at(i)) < 5){
			double init_gz = rk_fit_init_pos_gz->at(i);
			if( kUpTargetgz - kWireZRegion < init_gz  && init_gz < kUpTargetgz + kWireZRegion){
				return true;
			}
			else if ( kDownTargetgz - kWireZRegion< init_gz && init_gz < kDownTargetgz + kWireZRegion){
				return true;		
			}else {
				return false;
			}
		}
	}
	else {
		std::cerr << "not developed yet for coming from targets " << std::endl;
		return false;	
	}
}


bool E16DSTN_PosCorrection::IsGoodTrack(int i){
	if(IsComingFromTarget(i)){
		return true;
	}
	else {
		return false;
	}
}

void E16DSTN_PosCorrection::SetTracks(std::vector<int> &outids){
//	good_ids.clear();
	for(int i=0; i < n_cands; i++){
		if(kUseChi2Cut && chi_square->at(i) > kMaxChi2){
			break;
		}
		if(IsGoodTrack(i)){
//			good_ids.emplace_back(i);
 			outids.emplace_back(i);
		}
	}
}

void E16DSTN_PosCorrection::SetTracks(std::vector<int> &invec,std::vector<int> &outids){
//	good_ids.clear();
	for(int i=0; i < invec.size(); i++){
		int tid = invec[i];
		if(kUseChi2Cut && chi_square->at(tid) > kMaxChi2){
			break;
		}
		if(IsGoodTrack(tid)){
//			good_ids.emplace_back(i);
 			outids.emplace_back(i);
		}
	}
}




void E16DSTN_PosCorrection::ClearUsedClusterIDs() {
	for(auto &ids : used_cluster_ids){
		ids.clear();
	}
	return;
}

void E16DSTN_PosCorrection::UpdateFitResult(E16ANA_StraightMultiTrack *fitter,  const int tid){
	int hid = 0;
	init_pos_fit = fitter->GetFitVertex();
	init_mom_fit = fitter->GetFitMomentum(0);


	for(int l=0; l < E16ANA_StraightTrackConstant::kNumTrackingLayers; ++l){
		fit_results[l].Clear();
		std::vector<TVector3> lpos;
    	std::vector<TVector3> lmom;
      std::vector<int> mid;
      fitter->GetFitLPos(0, l, mid, lpos);
      fitter->GetFitLMom(0, l, mid, lmom);
      TVector3 gpos;
      TVector3 gmom;
		if(l == removed_layer) {
			mid[l] = mid[l-1];//tmp
		}
      auto mid2020 = E16ANA_StraightTrackConstant::ModuleID2013To2020(mid[0]);
      if (l <= E16ANA_StraightTrackConstant::kSSD) {
        gpos = geom->SSD(mid[hid])->GetGPos(lpos[hid]);
        gmom = geom->SSD(mid[hid])->GetGMom(lmom[hid]);
      } else {
        gpos = geom->GTR(mid[hid], l - 1)->GetGPos(lpos[hid]);
        gmom = geom->GTR(mid[hid], l - 1)->GetGMom(lmom[hid]);
      }
//      auto rpos = cluster_pairs[l].LocalPos() - lpos[hid];
		auto rpos  = CorrectedLocalPos(tid,mid[hid] ,l ) - lpos[hid];
		
//		std::cout  << "layer, rpos Mag  "  << l << ", " << rpos.Mag() << std::endl;
//		std::cout  << "lpos  "  << lpos[hid].X() << ", " << lpos[hid].Y() << ", " << lpos[hid].Z() << std::endl;
//		std::cout  << "cpos  "   
//		<< CorrectedLocalPos(tid, mid[hid], l).X() << ", " 
//		<< CorrectedLocalPos(tid, mid[hid], l).Y() << ", " 
//		<< CorrectedLocalPos(tid, mid[hid], l).Z() << std::endl;
      	fit_results[l].Set(l, mid2020, lpos[hid], lmom[hid], gpos, gmom, rpos);
		if(l != removed_layer){
		}
      if(l != E16ANA_StraightTrackConstant::kSSD) {
		}
	}


		tmp_rk_fit_init_mom_gx[tid]   = init_mom_fit.x();
		tmp_rk_fit_init_mom_gy[tid]   = init_mom_fit.y();
		tmp_rk_fit_init_mom_gz[tid]   = init_mom_fit.z();
		tmp_rk_fit_init_pos_gx[tid]   = init_pos_fit.x();
		tmp_rk_fit_init_pos_gy[tid]   = init_pos_fit.y();
		tmp_rk_fit_init_pos_gz[tid]   = init_pos_fit.z();
      tmp_rk_fit_ssd_mid[tid]       = fit_results[0].module_id;
      tmp_rk_fit_ssd_x[tid]         = fit_results[0].local_pos.X();
      tmp_rk_fit_ssd_y[tid]         = fit_results[0].local_pos.Y();
      tmp_rk_fit_ssd_gx[tid]        = fit_results[0].global_pos.X();
      tmp_rk_fit_ssd_gy[tid]        = fit_results[0].global_pos.Y();
      tmp_rk_fit_ssd_gz[tid]        = fit_results[0].global_pos.Z();
      tmp_rk_fit_ssd_mom_x[tid]     = fit_results[0].local_mom.X();
      tmp_rk_fit_ssd_mom_y[tid]     = fit_results[0].local_mom.Y();
      tmp_rk_fit_ssd_mom_z[tid]     = fit_results[0].local_mom.Z();
      tmp_rk_fit_ssd_mom_gx[tid]    = fit_results[0].global_mom.X();
      tmp_rk_fit_ssd_mom_gy[tid]    = fit_results[0].global_mom.Y();
      tmp_rk_fit_ssd_mom_gz[tid]    = fit_results[0].global_mom.Z();
      tmp_rk_res_ssd_x[tid]         = fit_results[0].residual_pos.X();

      tmp_rk_fit_gtr100_mid[tid]    = fit_results[1].module_id;
      tmp_rk_fit_gtr200_mid[tid]    = fit_results[2].module_id;
      tmp_rk_fit_gtr300_mid[tid]    = fit_results[3].module_id;
      tmp_rk_fit_gtr100_x[tid]      = fit_results[1].local_pos.X();
      tmp_rk_fit_gtr200_x[tid]      = fit_results[2].local_pos.X();
      tmp_rk_fit_gtr300_x[tid]      = fit_results[3].local_pos.X();
      tmp_rk_fit_gtr100_y[tid]      = fit_results[1].local_pos.Y();
      tmp_rk_fit_gtr200_y[tid]      = fit_results[2].local_pos.Y();
      tmp_rk_fit_gtr300_y[tid]      = fit_results[3].local_pos.Y();
      tmp_rk_fit_gtr100_gx[tid]     = fit_results[1].global_pos.X();
      tmp_rk_fit_gtr200_gx[tid]     = fit_results[2].global_pos.X();
      tmp_rk_fit_gtr300_gx[tid]     = fit_results[3].global_pos.X();
      tmp_rk_fit_gtr100_gy[tid]     = fit_results[1].global_pos.Y();
      tmp_rk_fit_gtr200_gy[tid]     = fit_results[2].global_pos.Y();
      tmp_rk_fit_gtr300_gy[tid]     = fit_results[3].global_pos.Y();
      tmp_rk_fit_gtr100_gz[tid]     = fit_results[1].global_pos.Z();
      tmp_rk_fit_gtr200_gz[tid]     = fit_results[2].global_pos.Z();
      tmp_rk_fit_gtr300_gz[tid]     = fit_results[3].global_pos.Z();
      tmp_rk_fit_gtr100_mom_x[tid]  = fit_results[1].local_mom.X();
      tmp_rk_fit_gtr200_mom_x[tid]  = fit_results[2].local_mom.X();
      tmp_rk_fit_gtr300_mom_x[tid]  = fit_results[3].local_mom.X();
      tmp_rk_fit_gtr100_mom_y[tid]  = fit_results[1].local_mom.Y();
      tmp_rk_fit_gtr200_mom_y[tid]  = fit_results[2].local_mom.Y();
      tmp_rk_fit_gtr300_mom_y[tid]  = fit_results[3].local_mom.Y();
      tmp_rk_fit_gtr100_mom_z[tid]  = fit_results[1].local_mom.Z();
      tmp_rk_fit_gtr200_mom_z[tid]  = fit_results[2].local_mom.Z();
      tmp_rk_fit_gtr300_mom_z[tid]  = fit_results[3].local_mom.Z();
      tmp_rk_fit_gtr100_mom_gx[tid] = fit_results[1].global_mom.X();
      tmp_rk_fit_gtr200_mom_gx[tid] = fit_results[2].global_mom.X();
      tmp_rk_fit_gtr300_mom_gx[tid] = fit_results[3].global_mom.X();
      tmp_rk_fit_gtr100_mom_gy[tid] = fit_results[1].global_mom.Y();
      tmp_rk_fit_gtr200_mom_gy[tid] = fit_results[2].global_mom.Y();
      tmp_rk_fit_gtr300_mom_gy[tid] = fit_results[3].global_mom.Y();
      tmp_rk_fit_gtr100_mom_gz[tid] = fit_results[1].global_mom.Z();
      tmp_rk_fit_gtr200_mom_gz[tid] = fit_results[2].global_mom.Z();
      tmp_rk_fit_gtr300_mom_gz[tid] = fit_results[3].global_mom.Z();
      tmp_rk_res_init_pos_gx[tid]   =0;
      tmp_rk_res_init_pos_gy[tid]   =0;
      tmp_rk_res_init_pos_gz[tid]   =0;
      tmp_rk_res_init_mom_gx[tid]   =0;
      tmp_rk_res_init_mom_gy[tid]   =0;
      tmp_rk_res_init_mom_gz[tid]   =0;
      tmp_rk_res_gtr100_x[tid]      = fit_results[1].residual_pos.X();
      tmp_rk_res_gtr100_y[tid]      = fit_results[1].residual_pos.Y();
      tmp_rk_res_gtr200_x[tid]      = fit_results[2].residual_pos.X();
      tmp_rk_res_gtr200_y[tid]      = fit_results[2].residual_pos.Y();
      tmp_rk_res_gtr300_x[tid]      = fit_results[3].residual_pos.X();
      tmp_rk_res_gtr300_y[tid]      = fit_results[3].residual_pos.Y();




	
}




 bool E16DSTN_PosCorrection::CalcRoughMomentumV2() {
//   double x[2],y[2],z[2];
//   x[0] = init_pos.X();
//   y[0] = init_pos.Y();
//   z[0] = init_pos.Z();
//   auto& c = cluster_pairs[1];
//   x[1] = c.GlobalPos().X();
//   y[1] = c.GlobalPos().Y();
//   z[1] = c.GlobalPos().Z();
//
//   double r = sqrt(pow(x[1]-x[0],2)+pow(y[1]-y[0],2)+pow(z[1]-z[0],2));
//
//   init_mom.SetXYZ((x[1]-x[0])/r, (y[1]-y[0])/r, (z[1]-z[0])/r);
   return true;

 }




void E16DSTN_PosCorrection::CorrectionFit(std::vector<int> &inids){
	chisq.clear();
//	int n_goodtracks = good_ids.size();
	int n_goodtracks = inids.size();
	for(int i = 0 ; i < n_goodtracks; i++){
//		int tid = good_ids[i];
		int tid = inids[i];
//		std::cout  << "track id " <<tid <<  std::endl;
		fitter->Clear();
		this->AddTrackCorrectedHit(fitter, tid);
		fitter->SetRungeKuttaStepSize(15.0);
		fitter->SetMaxSteps(kTrackingMaxSteps);
		double chi2;
		chi2 = fitter->Fit(false, false, false, kMinuitStrategy, kMinuitMaxFunctionCalls);//vertex z not fix
		//chi2 = fitter->Fit(false, false, true, kMinuitStrategy, kMinuitMaxFunctionCalls);//vertex z fix
//		std::cout << "chi2 = " << chi2 << std::endl;
		chisq.push_back(chi2);	
		UpdateFitResult(fitter, tid);
	}
}

void E16DSTN_PosCorrection::AddTrackCorrectedHit(E16ANA_StraightMultiTrack *fitter, const int tid){

	if (!CalcRoughMomentumV2()) {
		std::cerr << "Cannot Caluculate rough momentum " << std::endl;
	}	
	
//	for (auto& fit_result : fit_results) {
//		fit_result.set_flag = 0;
//	}
	fitter->Clear();
	double target_z, target_x;
	if(rk_fit_init_pos_gz->at(tid) < 0){
		target_z = kUpTargetgz;
		target_x = kUpTargetgx;
	}
	else{
		target_z = kDownTargetgz;
		target_x = kDownTargetgx;
	}
  	fitter->SetInitialVertex(TVector3(target_x,rk_fit_init_pos_gy->at(tid), target_z),TVector3(kInitPosErrorWire));

//	std::cout << "init "  << rk_fit_init_pos_gy->at(tid) << std::endl;
	fitter->SetInitialMomentum(0, TVector3(rk_fit_init_mom_gx->at(tid), rk_fit_init_mom_gy->at(tid), rk_fit_init_mom_gz->at(tid)));//zero is for a single track
//	std::cout << "init mom x "  << rk_fit_init_mom_gx->at(tid) << std::endl;
//	std::cout << "init mom y "  << rk_fit_init_mom_gy->at(tid) << std::endl;
//	std::cout << "init mom z "  << rk_fit_init_mom_gz->at(tid) << std::endl;
//

   for (int l = 0; l < E16ANA_StraightTrackConstant::kNumTrackingLayers; ++l) {
   	if (l == removed_layer) continue;
		int mid[4] = {rk_fit_ssd_mid->at(tid), rk_fit_gtr100_mid->at(tid), rk_fit_gtr200_mid->at(tid), rk_fit_gtr300_mid->at(tid)};
//		std::cout << "mid " << rk_fit_ssd_mid->at(tid) << std::endl;
    	if (l == E16ANA_StraightTrackConstant::kSSD) {
		TVector3 lpos(rk_fit_ssd_x->at(tid), 0, 0 );
//		std::cout << "ssd x " << rk_hit_ssd_x->at(tid) << std::endl;
      fitter->AddHit(0, l, geom->SSD(E16ANA_StraightTrackConstant::ModuleID2020To2013(mid[l])),lpos, kSigmas[l]);//first zero is for a single track, second argv is the layzer order
    } else {
      fitter->AddHit(0, l, geom->GTR(E16ANA_StraightTrackConstant::ModuleID2020To2013(mid[l]), l - 1), CorrectedLocalPos(tid,mid[l],  l), kSigmas[l]);//first zero is for a single track
//		std::cout << "gtr x " << CorrectedLocalPos(tid, mid[l], l ).X() <<", " << CorrectedLocalPos(tid, mid[l], l).Y() <<std::endl;
    }
  }
//	fitter->PrintHits();
}

TVector3 E16DSTN_PosCorrection::CorrectedLocalPos(const int tid, const int mid, const int l){
	TVector3 cor_pos;//correcrted pos 
#ifdef CALIB

	if(l == 0){
		return TVector3(rk_hit_ssd_x->at(tid),0, 0 );
	}
	
	else if(l == 1){//gtr100
//		double localx     = rk_hit_gtr100_tx2->at(tid);
//		double localy     = rk_hit_gtr100_ty->at(tid);
		double localx     = rk_hit_gtr100_cogx->at(tid);
		double localy     = rk_hit_gtr100_cogy->at(tid);
		double vd     = 0.011;
		double gap = 1.5;
//		double tan    = (double)rk_fit_gtr100_mom_gx->at(tid)/rk_fit_gtr100_mom_gz->at(tid);
		double tan    = (double)rk_fit_gtr100_mom_x->at(tid)/rk_fit_gtr100_mom_z->at(tid);
		double tcor   = 1.4*exp(-0.5*pow((fabs(localx)-45)/11,2))+1e-4*(localy*localy);
		double cent0  = 150;
		double tc1x   = cent0 + (gap - tcor)/vd;
		double crx1   = localx - (tc1x - rk_hit_gtr100_xt4->at(tid)) * vd * tan;	
//		double crx1   = localx - (tc1x - rk_hit_gtr100_xt->at(tid)) * vd * tan;	
		double cry1   = localy;
		return TVector3(crx1, cry1, 0);
	}
	else if(l == 2)	{//gtr200
//		double localx     = rk_hit_gtr200_tx2->at(tid);//should be gtx?
//		double localy     = rk_hit_gtr200_ty->at(tid);
//		double localx     = rk_hit_gtr200_cogx->at(tid);
		double localy     = rk_hit_gtr200_cogy->at(tid);
		double projx  = rk_fit_gtr200_x->at(tid);
		double projy  = rk_fit_gtr200_y->at(tid);
		double vd     = 0.010;
		double gap    = 1.5;
//		double tan    = (double)rk_fit_gtr200_mom_gx->at(tid)/rk_fit_gtr200_mom_gz->at(tid);
		double tan    = (double)rk_fit_gtr200_mom_x->at(tid)/rk_fit_gtr200_mom_z->at(tid);
//		double tcor   = -0.8*exp(-0.5*pow((localx+75)/15,2))+exp(-0.5*pow((localx-55)/20, 2))+4e-4*(localy*localy)/4.0;
		double tcor   = -0.8*exp(-0.5*pow((projx+75)/15,2))+exp(-0.5*pow((projx-55)/20, 2))+4e-4*(projy*projy)/4.0;
		double cent0  = 150;
		double tc2x   = cent0 + (gap - tcor)/vd;
		double crx2   = projx - (tc2x - rk_hit_gtr200_xt4->at(tid)) * vd * tan;	
//		double crx2   = localx - (tc2x - rk_hit_gtr200_xt4->at(tid)) * vd * tan;	
//		double crx2   = localx - (tc2x - rk_hit_gtr200_xt->at(tid)) * vd * tan;	
		double cry2   = localy;
		return TVector3(crx2, cry2, 0);
	}
	else if(l == 3){//gtr300
//		double localx     = rk_hit_gtr300_tx2->at(tid);//should be gtx?
//		double localy     = rk_hit_gtr300_ty->at(tid);
		double localx     = rk_hit_gtr300_cogx->at(tid);//should be gtx?
		double localy     = rk_hit_gtr300_cogy->at(tid);
		double vd     = 0.018;
		double gap    = 1.5;
//		double tan   = (double)rk_fit_gtr300_mom_gx->at(tid)/rk_fit_gtr300_mom_gz->at(tid);
		double tan   = (double)rk_fit_gtr300_mom_x->at(tid)/rk_fit_gtr300_mom_z->at(tid);
		double tcor   = 1.4*exp(-0.5*pow((localx+115)/14,2))+6e-4*(localy*localy)/6.0;
		double cent0  = 150;
		double tc3x   = cent0 + (gap - tcor)/vd;
		double crx3   = localx - (tc3x - rk_hit_gtr300_xt4->at(tid)) * vd * tan;	
//		double crx3   = localx - (tc3x - rk_hit_gtr300_xt->at(tid)) * vd * tan;	
		double cry3   = localy;
		return TVector3(crx3, cry3, 0);
	}
#endif
#ifdef COG_INFO
	

//  -------- COG  ---------- ///
	if(l == 0) {
		cor_pos = TVector3(rk_hit_ssd_x->at(tid), 0 , 0);
	}
	else if(l == 1) {
		cor_pos = TVector3(rk_hit_gtr100_cogx->at(tid), rk_hit_gtr100_cogy->at(tid) , 0);
	}
	else if(l == 2) {
		cor_pos = TVector3(rk_hit_gtr200_cogx->at(tid), rk_hit_gtr200_cogy->at(tid) , 0);
	}
	else if(l == 3) {
		cor_pos = TVector3(rk_hit_gtr300_cogx->at(tid), rk_hit_gtr300_cogy->at(tid) , 0);
	}
#endif 
#ifdef TDC_INFO


// ---------- TDC ----------- //
	if(l == 0) {
		cor_pos = TVector3(rk_hit_ssd_x->at(tid), 0 , 0);
	}
	else if(l == 1) {
		cor_pos = TVector3(rk_hit_gtr100_tx2->at(tid), rk_hit_gtr100_cogy->at(tid) , 0);
	}
	else if(l == 2) {
		cor_pos = TVector3(rk_hit_gtr200_tx2->at(tid), rk_hit_gtr200_cogy->at(tid) , 0);
	}
	else if(l == 3) {
		cor_pos = TVector3(rk_hit_gtr300_tx2->at(tid), rk_hit_gtr300_cogy->at(tid) , 0);
	}
#endif 

#ifdef DRIFT_V
// -----   Drift velocity ----- // 
	if(l == 0) {
		cor_pos = TVector3(rk_hit_ssd_x->at(tid), 0 , 0);
	}


	if(l == 0){
		return TVector3(rk_hit_ssd_x->at(tid),0, 0 );
	}
	
	else if(l == 1){//gtr100
//		double localx     = rk_hit_gtr100_tx2->at(tid);
//		double localy     = rk_hit_gtr100_ty->at(tid);
		double localx     = rk_hit_gtr100_cogx->at(tid);
		double localy     = rk_hit_gtr100_cogy->at(tid);
		double vd     = 0.011;
		double gap = 1.5;
//		double tan    = (double)rk_fit_gtr100_mom_gx->at(tid)/rk_fit_gtr100_mom_gz->at(tid);
		double tan    = (double)rk_fit_gtr100_mom_x->at(tid)/rk_fit_gtr100_mom_z->at(tid);
		double tcor   = 1.4*exp(-0.5*pow((fabs(localx)-45)/11,2))+1e-4*(localy*localy);
		double cent0  = 150;
		double tc1x   = cent0 + (gap - tcor)/vd;
		double crx1   = localx - (tc1x - rk_hit_gtr100_xt4->at(tid)) * vd * tan;	
//		double crx1   = localx - (tc1x - rk_hit_gtr100_xt->at(tid)) * vd * tan;	
		double cry1   = localy;
		return TVector3(crx1, cry1, 0);
	}
	else if(l == 2)	{//gtr200
		#ifdef CHECK_200
		cor_pos = TVector3(rk_hit_gtr200_cogx->at(tid), rk_hit_gtr200_cogy->at(tid) , 0);
		#else
//		double localx     = rk_hit_gtr200_tx2->at(tid);//should be gtx?
//		double localy     = rk_hit_gtr200_ty->at(tid);
//		double localx     = rk_hit_gtr200_cogx->at(tid);
		double localy     = rk_hit_gtr200_cogy->at(tid);
		double projx  = rk_fit_gtr200_x->at(tid);
		double projy  = rk_fit_gtr200_y->at(tid);
		double vd     = 0.010;
		double gap    = 1.5;
//		double tan    = (double)rk_fit_gtr200_mom_gx->at(tid)/rk_fit_gtr200_mom_gz->at(tid);
		double tan    = (double)rk_fit_gtr200_mom_x->at(tid)/rk_fit_gtr200_mom_z->at(tid);
//		double tcor   = -0.8*exp(-0.5*pow((localx+75)/15,2))+exp(-0.5*pow((localx-55)/20, 2))+4e-4*(localy*localy)/4.0;
		double tcor   = -0.8*exp(-0.5*pow((projx+75)/15,2))+exp(-0.5*pow((projx-55)/20, 2))+4e-4*(projy*projy)/4.0;
		double cent0  = 150;
		double tc2x   = cent0 + (gap - tcor)/vd;
		double crx2   = projx - (tc2x - rk_hit_gtr200_xt4->at(tid)) * vd * tan;	
//		double crx2   = localx - (tc2x - rk_hit_gtr200_xt4->at(tid)) * vd * tan;	
//		double crx2   = localx - (tc2x - rk_hit_gtr200_xt->at(tid)) * vd * tan;	
		double cry2   = localy;
		return TVector3(crx2, cry2, 0);
		#endif
	}
	else if(l == 3){//gtr300
//		double localx     = rk_hit_gtr300_tx2->at(tid);//should be gtx?
//		double localy     = rk_hit_gtr300_ty->at(tid);
		double localx     = rk_hit_gtr300_cogx->at(tid);//should be gtx?
		double localy     = rk_hit_gtr300_cogy->at(tid);
		double vd     = 0.018;
		double gap    = 1.5;
//		double tan   = (double)rk_fit_gtr300_mom_gx->at(tid)/rk_fit_gtr300_mom_gz->at(tid);
		double tan   = (double)rk_fit_gtr300_mom_x->at(tid)/rk_fit_gtr300_mom_z->at(tid);
		double tcor   = 1.4*exp(-0.5*pow((localx+115)/14,2))+6e-4*(localy*localy)/6.0;
		double cent0  = 150;
		double tc3x   = cent0 + (gap - tcor)/vd;
		double crx3   = localx - (tc3x - rk_hit_gtr300_xt4->at(tid)) * vd * tan;	
//		double crx3   = localx - (tc3x - rk_hit_gtr300_xt->at(tid)) * vd * tan;	
		double cry3   = localy;
		return TVector3(crx3, cry3, 0);
	}



#endif


	return cor_pos;
}

//		double vd = 0.010;//drift velocity
//		double gap = 1.5; // drift gap [mm]
//		double projx2 = rk_fit_gtr200_x->at(tid);
//		double projy2 = rk_fit_gtr200_y->at(tid);
//		double tcor2 = -0.8*(exp(-0.5*pow((projx2+75)/15,2))+exp(-0.5*pow((projx2-55)/20,2)))+4e-4*(projy2*projy2/4);
//		double tc2 = 150+(gap-tcor2) / vd;
//		double cx2 = rk_hit_gtr100_x->at(tid)+ (tc2 - gtr)
	

