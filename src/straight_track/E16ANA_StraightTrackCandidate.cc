#include "E16ANA_StraightTrackCandidate.hh"
#include "E16ANA_StraightTrackConstant.hh"
#include "E16ANA_StraightTrackParameter.hh"

using namespace E16ANA_StraightTrackParameter;

void E16ANA_StraightTrackCandidate::SetDefaultSigma() {
  for (int i = 0; i < E16ANA_StraightTrackConstant::kNumTrackingLayers; ++i) {
    sigma[i] = kSigmas[i];
  }
}

TVector3 E16ANA_StraightTrackCandidate::EachSigma(int n) { return kSigmas[n]; }

TVector3 E16ANA_StraightTrackCandidate::InitPosError() { return kInitPosError; }


bool E16ANA_StraightTrackCandidate::CalcRoughMomentumV2() {
  double x[2],y[2],z[2];
  x[0] = init_pos.X();
  y[0] = init_pos.Y();
  z[0] = init_pos.Z();
  auto& c = cluster_pairs[1];
  x[1] = c.GlobalPos().X();
  y[1] = c.GlobalPos().Y();
  z[1] = c.GlobalPos().Z();

  double r = sqrt(pow(x[1]-x[0],2)+pow(y[1]-y[0],2)+pow(z[1]-z[0],2));

  init_mom.SetXYZ((x[1]-x[0])/r, (y[1]-y[0])/r, (z[1]-z[0])/r);
  return true;

}

void E16ANA_StraightTrackCandidate::AddTrackHit(E16ANA_StraightMultiTrack* single_track, bool isWire) {
  for (auto& fit_result : fit_results) {
    fit_result.set_flag = 0;
  }
//  if (!CalcRoughMomentum()) {
  if (!CalcRoughMomentumV2()) {
    std::cerr << "Cannot calculate rough momentum" << std::endl;
  }
  int tid = 0; // only 1 track is fitted by the fitter
  single_track->Clear();
  if(isWire){
  		single_track->SetInitialVertex(TVector3(init_pos.X(), init_pos.Y(), init_pos.Z()), kInitPosErrorWire); 
  }
  else {
  		single_track->SetInitialVertex(TVector3(init_pos.X(), init_pos.Y(), init_pos.Z()), kInitPosError); 
//   single_track->SetInitialVertex(TVector3(init_pos.X(), 0., init_pos.Z()), TVector3(0.4, 0., 0)); // for Ks
  }
  single_track->SetInitialMomentum(tid, init_mom);
//  single_track->SetCharge(tid, charge);

//  for (int l = 0; l < E16ANA_StraightTrackConstant::kNumTrackingLayers; ++l) {
  for (int l = 0; l < E16ANA_StraightTrackConstant::kNumTrackingLayers; ++l) {
    auto& c = cluster_pairs[l];
    if (l == E16ANA_StraightTrackConstant::kSSD) {
      #ifdef NoExist_SSD
         continue;
      #endif 
		#ifndef UseSTS
      single_track->AddHit(tid, c.LayerOrder(), geometry->SSD(E16ANA_StraightTrackConstant::ModuleID2020To2013(c.ModuleID())), c.LocalPos(), sigma[l]);
		#else
      single_track->AddHit(tid, c.LayerOrder(), geometry->STS(E16ANA_StraightTrackConstant::ModuleID2020To2013(c.ModuleID())), c.LocalPos(), sigma[l]);
		#endif
    } else {
      single_track->AddHit(tid, c.LayerOrder(), geometry->GTR(E16ANA_StraightTrackConstant::ModuleID2020To2013(c.ModuleID()), c.LayerOrder() - 1), c.LocalPos(), sigma[l]);
    }
  }
}

void E16ANA_StraightTrackCandidate::UpdateFitResult(E16ANA_StraightMultiTrack* fitter) {
//diffetent with magnetic field tracking
  int tid = 0;
  int hid = 0;
  init_pos_fit = fitter->GetFitVertex();
//  std::cout << "init pos = " << init_pos_fit.x() << ", " << init_pos_fit.y() << ", " << init_pos_fit.z() << std::endl;
  init_mom_fit = fitter->GetFitMomentum(tid);
  minimize_status = fitter->GetMinimizeStatus();
  matrix_status = fitter->GetMatrixStatus();
  n_steps = fitter->GetTrackSteps(tid).size();
  n_calls = fitter->GetNumCalls();
  for (int l = 0; l < E16ANA_StraightTrackConstant::kNumTrackingLayers; ++l) {
//  for (int l = 1; l < E16ANA_StraightTrackConstant::kNumTrackingLayers; ++l) {
#ifdef NoExist_SSD
		if(l == 0){
			continue;
		}
#endif

    fit_results[l].Clear();
    std::vector<TVector3> lpos;
    std::vector<TVector3> lmom;
    std::vector<int> mid;
    fitter->GetFitLPos(tid, l, mid, lpos);
    fitter->GetFitLMom(tid, l, mid, lmom);
    TVector3 gpos;
    TVector3 gmom;
    auto mid2020 = E16ANA_StraightTrackConstant::ModuleID2013To2020(mid[hid]);
    if (l <= E16ANA_StraightTrackConstant::kSSD) {
		#ifndef UseSTS
      gpos = geometry->SSD(mid[hid])->GetGPos(lpos[hid]);
      gmom = geometry->SSD(mid[hid])->GetGMom(lmom[hid]);
		#else 
		gpos = geometry->STS(mid[hid])->GetGPos(lpos[hid]);
      gmom = geometry->STS(mid[hid])->GetGMom(lmom[hid]);
		#endif
    } else {
      gpos = geometry->GTR(mid[hid], l - 1)->GetGPos(lpos[hid]);
      gmom = geometry->GTR(mid[hid], l - 1)->GetGMom(lmom[hid]);
    }
    auto rpos = cluster_pairs[l].LocalPos() - lpos[hid];
    fit_results[l].Set(l, mid2020, lpos[hid], lmom[hid], gpos, gmom, rpos);
    if(l != E16ANA_StraightTrackConstant::kSSD) {
      auto rpost2 = cluster_pairs[l].LocalPosT() - lpos[hid];
      auto rpost  = cluster_pairs[l].LocalPos() - lpos[hid];
      fit_results[l].SetT(rpost);
      fit_results[l].SetT2(rpost2);
      auto xclst = dynamic_cast<E16DST_DST1GTRCluster*>(cluster_pairs[l].Cluster(0));
      auto yclst = dynamic_cast<E16DST_DST1GTRCluster*>(cluster_pairs[l].Cluster(1));
      TVector3 lcx(xclst->LocalX()-lpos[hid].X(),yclst->LocalX()-lpos[hid].Y(),0);
      fit_results[l].SetC(lcx);
		}
    }
	Projection(fitter);//add 230826
	return;
}

void E16ANA_StraightTrackCandidate::Projection(E16ANA_StraightMultiTrack* fitter) {
	projection_flag = 0;
	fitter->Clear();
	  for (int l = E16ANA_TrackConstant::kHBD; l < E16ANA_TrackConstant::kNumDetectorLayers; ++l) {
     fit_results[l].Clear();
   }
   if (chisq >= 1.0e10) {
     return;
   }
   int tid = 0;
   TVector3 lpos(0., 0., 0.);
   TVector3 lsigma(0., 0., 0.);
   auto module_id = cluster_pairs[E16ANA_TrackConstant::kNumTrackingLayers - 1].ModuleID();
   int lid = 0; // only 1 layer in 1 RK
   int hid = 0; // oonly 1 hit in 1 RK
   std::vector<int> mids;
   std::vector<TVector3> lposs;
   std::vector<TVector3> lmoms;
   for (int l = E16ANA_TrackConstant::kHBD; l < E16ANA_TrackConstant::kNumDetectorLayers; ++l) {
     auto& result = fit_results[l];
     result.Clear();
     int nstps;
 //    double r;
     for (int mid = module_id - 2; mid <= module_id + 2; ++mid) {
       if (mid == 105 || mid < E16ANA_TrackConstant::kModuleIDs.front() || mid > E16ANA_TrackConstant::kModuleIDs.back()) {
         continue;
       }
       auto mid2013 = E16ANA_TrackConstant::ModuleID2020To2013_27(mid);
       fitter->Clear();
       if (l == E16ANA_TrackConstant::kHBD) {
         auto tmp_geom = geometry->HBD(mid2013);
         fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
 #ifndef TRACK_EFF_CHECK
       } else {
         auto tmp_geom = geometry->LG(mid2013, kTypicalLGBlocks[l - E16ANA_TrackConstant::kLG]);
         fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
       }
 #else
       } else if (l < kLGVD) {
         auto tmp_geom = geometry->LG(mid2013, kTypicalLGBlocks[l - E16ANA_TrackConstant::kLG]);
         fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
       } else {
         auto tmp_geom = geometry->LGVD(mid2013);
         fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
       }
 #endif
       fitter->SetMaxSteps(kProjectionMaxSteps);
       fitter->RungeKuttaTracking(tid, init_pos_fit, init_mom_fit, charge);
       fitter->GetFitLPos(tid, lid, mids, lposs);
       fitter->GetFitLMom(tid, lid, mids, lmoms);
       auto lpos = lposs[hid];
       auto lmom = lmoms[hid];
       if (fabs(lpos.X()) >= fabs(E16DST_DST1Constant::kInvalidValue)) {
         continue;
       }
       TVector3 gpos;
       TVector3 gmom;
       if (l == E16ANA_TrackConstant::kHBD) {
         gpos = geometry->HBD(mid2013)->GetGPos(lpos);
         gmom = geometry->HBD(mid2013)->GetGMom(lmom);
 #ifndef TRACK_EFF_CHECK
       } else {
         gpos = geometry->LG(mid2013, kTypicalLGBlocks[l - E16ANA_TrackConstant::kLG0])->GetGPos(lpos);
         gmom = geometry->LG(mid2013, kTypicalLGBlocks[l - E16ANA_TrackConstant::kLG0])->GetGMom(lmom);
       }
 #else
       } else if (l < kLGVD) {
         gpos = geometry->LG(mid2013, kTypicalLGBlocks[l - E16ANA_TrackConstant::kLG0])->GetGPos(lpos);
         gmom = geometry->LG(mid2013, kTypicalLGBlocks[l - E16ANA_TrackConstant::kLG0])->GetGMom(lmom);
       } else {
         gpos = geometry->LGVD(mid2013)->GetGPos(lpos);
         gmom = geometry->LGVD(mid2013)->GetGMom(lmom);
       }
 #endif
       auto nstps_tmp = fitter->GetTrackSteps(tid).size();
       if (result.set_flag == 0) {
         if (l == E16ANA_TrackConstant::kHBD) {
           result.Set(l, mid, lpos, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
 #ifndef TRACK_EFF_CHECK
         } else {
           auto lpos_lgvd = geometry->LGVD(mid2013)->GetLPos(gpos);
           result.Set(l, mid, lpos_lgvd, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
         }
 #else
         } else if (l < kLGVD) {
           auto lpos_lgvd = geometry->LGVD(mid2013)->GetLPos(gpos);
           result.Set(l, mid, lpos_lgvd, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
         } else {
           result.Set(l, mid, lpos, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
         }
 #endif
         nstps = nstps_tmp;
 //        r = gpos.Mag();
       } else if (nstps_tmp < nstps) {
 //      } else if (gpos.Mag() < r) {
         if (l == E16ANA_TrackConstant::kHBD) {
           result.Set(l, mid, lpos, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
 #ifndef TRACK_EFF_CHECK
         } else {
           auto lpos_lgvd = geometry->LGVD(mid2013)->GetLPos(gpos);
           result.Set(l, mid, lpos_lgvd, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
         }
 #else
         } else if (l < kLGVD) {
           auto lpos_lgvd = geometry->LGVD(mid2013)->GetLPos(gpos);
           result.Set(l, mid, lpos_lgvd, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
         } else {
           result.Set(l, mid, lpos, lmom, gpos, gmom, E16DST_DST1Constant::kInvalidVector);
         }
 #endif
         nstps = nstps_tmp;
 //        r = gpos.Mag();
       }
     }
     if (result.set_flag == 1) {
       projection_flag += pow(2, l - E16ANA_TrackConstant::kHBD);
     }
   }
}


double E16ANA_StraightTrackCandidate::Fit(E16ANA_StraightMultiTrack* fitter, bool vertex_xy_fix_flag, bool py_fix_flag, bool vertex_z_fix_flag, bool  isWire) {
  fitter->Clear();
  this->AddTrackHit(fitter, isWire);
  fitter->SetRungeKuttaStepSize(kTrackingStepSize);
  fitter->SetMaxSteps(kTrackingMaxSteps);
  chisq = fitter->Fit(vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag, kMinuitStrategy, kMinuitMaxFunctionCalls);
  UpdateFitResult(fitter);
  return chisq;
}

void E16ANA_StraightTrackCandidate::PrintParam() {
//  std::cout << "Sigma : ("  << kSigma(0) << ", " << kSigma(1) << ", " << kSigma(2) << ")" << std::endl;
  for (int i = 0; i < E16ANA_StraightTrackConstant::kNumTrackingLayers; ++i) {
    std::cout << "  " << E16ANA_StraightTrackConstant::kDetectorName[i] << " : ("  << kSigmas[i](0) << ", " << kSigmas[i](1) << ", " << kSigmas[i](2) << ")" << std::endl;
  }
  std::cout << "Initial Position Error : (" << kInitPosError(0) << ", " << kInitPosError(1) << ", " << kInitPosError(2) << ")" << std::endl;
  std::cout << "Runge Kutta Tracking Max Steps : " << kTrackingMaxSteps << std::endl;
  std::cout << "Runge Kutta Projection Max Steps : " << kProjectionMaxSteps << std::endl;
}



bool E16ANA_StraightTrackCandidates::IsXTrackCandidate(OneAxisClusterSet* cluster_set, int in_mid){
  auto& pos_set = cluster_set->global_poss;
  int mid       = in_mid -100;
//targets position 
  std::vector<TVector2> targets;
  targets.clear();
  for(int i=0; i < targets_pos.size(); i++){
    targets.push_back(TVector2(targets_pos[i].x(), targets_pos[i].z()));
  } 
//detector positions
  std::vector<TVector2> positions;
  positions.clear();
  for(int i=0; i < E16ANA_StraightTrackConstant::kNumTrackingLayers;i++){
#if NoExist_SSD
   if(i == 0) continue;
#endif
  positions.push_back(TVector2(pos_set[i].X(), pos_set[i].Z()));
  }
//rotating targets
  std::vector<TVector2> rtargets;
  rtargets.clear();
  for(int i=0; i < targets.size(); i++){
    rtargets.push_back(targets[i].Rotate(Agtr[mid]*cpi/180));
  }
//rotating detector hits
  std::vector<TVector2> rpositions;
  rpositions.clear();
  for(int i=0; i < positions.size(); i++){
    rpositions.push_back(positions[i].Rotate(Agtr[mid]*cpi/180));
  }
  int removed_layer = -1;
#ifdef NoExist_SSD
			removed_layer = 0;
#elif REMOVE_GTR100
			removed_layer = 1;
#elif  REMOVE_GTR200
			removed_layer = 2;
#elif  REMOVE_GTR300
			removed_layer = 3;
#endif 

  if(isWire){
		  if(removed_layer == -1){//with all detectors, Wire
	  	  double rlx1[]={rtargets[0].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X(),rpositions[3].X()};//wire0_x
	  	  double rlz1[]={rtargets[0].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y(),rpositions[3].Y()};//wire0_y
   	  double rlx2[]={rtargets[1].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X(),rpositions[3].X()};//wire1_x
    	  double rlz2[]={rtargets[1].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y(),rpositions[3].Y()};//wire1_y

//        std::cout << "t : " << rtargets[0].X() << " " << rtargets[0].Y() << std::endl;
//        std::cout << "0 : " << rpositions[0].X() << " " << rpositions[0].Y() << std::endl;
//        std::cout << "1 : " << rpositions[1].X() << " " << rpositions[1].Y() << std::endl;
//        std::cout << "2 : " << rpositions[2].X() << " " << rpositions[2].Y() << std::endl;
//        std::cout << "3 : " << rpositions[3].X() << " " << rpositions[3].Y() << std::endl;


	     double err[]={kWireXSigma[0],kWireXSigma[1],kWireXSigma[2],kWireXSigma[3],kWireXSigma[4]};//with all
	     double ra1,rb1;
	     fline(5,rlz1,rlx1,err,ra1,rb1);
	     double ra2,rb2;
	     fline(5,rlz2,rlx2,err,ra2,rb2);
	     double chi1,chi2;
	     chi1 = chi2 = 0;
	     for(int i=0;i<5;i++){
           chi1 += pow((rlx1[i]-(rb1*rlz1[i]+ra1))/err[i],2);
           chi2 += pow((rlx2[i]-(rb2*rlz2[i]+ra2))/err[i],2);
        }
      double ras[2]     = {ra1, ra2}; //[2] is number of targets
      double rbs[2]     = {rb1, rb2}; 
      double chi_cand[2] = {chi1, chi2};
      auto   min_t = std::min_element(std::begin(chi_cand), std::end(chi_cand));
      int	 min_i = std::distance(std::begin(chi_cand), min_t);

//      std::cout << "chi1 = "  << chi1 << std::endl;
//      std::cout << "chi2 = "  << chi2 << std::endl;

      if (chi_cand[min_i] < kRoughFitChiSquareThreshold[0]) {
//        cluster_set->charge = -1;
//        if(chi2<chi1)  cluster_set->charge = 1;
          cluster_set->chi_square = chi_cand[min_i];
    	    cluster_set->target_id  = min_i;
    	    cluster_set->coefs[0]   = ras[min_i]; 
    	    cluster_set->coefs[1]   = rbs[min_i]; 
          return true;
      }
      return false;
     }
     else {//Without One layer, Wire
  	    double rlx1[]={rtargets[0].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X()};//wire0_x
	    double rlz1[]={rtargets[0].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y()};//wire0_y
    	 double rlx2[]={rtargets[1].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X()};//wire1_x
  	    double rlz2[]={rtargets[1].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y()};//wire1_y
       std::vector<double> sigmas;
       sigmas.clear();
       for(int i=0; i < E16ANA_StraightTrackConstant::kNumTrackingLayers+1; i++){
         if(i != -1 && i-1 == removed_layer) continue;
         sigmas.push_back(kWireXSigma[i]);
       }
       double err[]={sigmas[0], sigmas[1],sigmas[2], sigmas[3]};//without one layer
       double ra1,rb1;
       fline(4,rlz1,rlx1,err,ra1,rb1);
       double ra2,rb2;
       fline(4,rlz2,rlx2,err,ra2,rb2);
       double chi1,chi2;
       chi1 = chi2 = 0;
       for(int i=0;i<4;i++){
        chi1 += pow((rlx1[i]-(rb1*rlz1[i]+ra1))/err[i],2);
        chi2 += pow((rlx2[i]-(rb2*rlz2[i]+ra2))/err[i],2);
      }
      double ras[n_targets]     = {ra1, ra2}; //[2] is number of targets
      double rbs[n_targets]     = {rb1, rb2}; 
      double chi_cand[2] = {chi1, chi2};
      auto   min_t = std::min_element(std::begin(chi_cand), std::end(chi_cand));
      int	 min_i = std::distance(std::begin(chi_cand), min_t);
	   
      if (chi_cand[min_i] < kRoughFitChiSquareThreshold[0]) {
//        cluster_set->charge = -1;
//        if(chi2<chi1)  cluster_set->charge = 1;
          cluster_set->chi_square = chi_cand[min_i];
    	    cluster_set->target_id  = min_i;
    	    cluster_set->coefs[0]   = ras[min_i]; 
    	    cluster_set->coefs[1]   = rbs[min_i]; 
          return true;
      }
      return false;
      }
  }
  else {// three targets case 
		  if(removed_layer == -1) {//all layers and three targets 
		    double rlx1[]={rtargets[0].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X(), rpositions[3].X()};
	  	    double rlz1[]={rtargets[0].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y(), rpositions[3].Y()};
	  	    double rlx2[]={rtargets[1].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X(), rpositions[3].X()};
    		 double rlz2[]={rtargets[1].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y(), rpositions[3].Y()};
	   	 double rlx3[]={rtargets[2].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X(), rpositions[3].X()};
    	    double rlz3[]={rtargets[2].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y(), rpositions[3].Y()};
          double err[]={kXSigmaIncTgt[0],kXSigmaIncTgt[1], kXSigmaIncTgt[2],kXSigmaIncTgt[3],kXSigmaIncTgt[4]};//with SSD
	       double ra1,rb1;
	       fline(5,rlz1,rlx1,err,ra1,rb1);
	       double ra2,rb2;
	       fline(5,rlz2,rlx2,err,ra2,rb2);
	       double ra3,rb3;
	       fline(5,rlz3,rlx3,err,ra3,rb3);
	       double chi1,chi2, chi3;
	       chi1 = chi2 = chi3 = 0;
	       for(int i=0;i<5;i++){
	         chi1 += pow((rlx1[i]-(rb1*rlz1[i]+ra1))/err[i],2);
	         chi2 += pow((rlx2[i]-(rb2*rlz2[i]+ra2))/err[i],2);
	         chi3 += pow((rlx3[i]-(rb3*rlz3[i]+ra3))/err[i],2);
	       }
	       double ras[3]     = {ra1, ra2, ra3}; // 3 is the number of targets
	       double rbs[3]     = {rb1, rb2, rb3}; 
	       double chi_cand[3] = {chi1, chi2, chi3};
	       auto  min_t = std::min_element(std::begin(chi_cand), std::end(chi_cand));
	       int   min_i = std::distance(std::begin(chi_cand), min_t);
          if (chi_cand[min_i] < kRoughFitChiSquareThreshold[0]) {
            cluster_set->chi_square = chi_cand[min_i];
         	cluster_set->target_id  = min_i;
    	      cluster_set->coefs[0]   = ras[min_i]; 
    	      cluster_set->coefs[1]   = rbs[min_i]; 
            return true;
          }
        return false;
        }
        else {//three targets and without one layer
   		  double rlx1[]={rtargets[0].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X()};
       	  double rlz1[]={rtargets[0].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y()};
       	  double rlx2[]={rtargets[1].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X()};
     	     double rlz2[]={rtargets[1].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y()};
       	  double rlx3[]={rtargets[2].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X()};
       	  double rlz3[]={rtargets[2].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y()};
           std::vector<double> sigmas;
           sigmas.clear();
           for(int i=0; i < E16ANA_StraightTrackConstant::kNumTrackingLayers+1; i++){
             if(i != -1 && i-1 == removed_layer) continue;
             sigmas.push_back(kXSigmaIncTgt[i]);
           }
           double err[]={sigmas[0], sigmas[1],sigmas[2], sigmas[3]};//without one layer
           double ra1,rb1;
           fline(4,rlz1,rlx1,err,ra1,rb1);
           double ra2,rb2;
           fline(4,rlz2,rlx2,err,ra2,rb2);
           double ra3,rb3;
           fline(4,rlz3,rlx3,err,ra3,rb3);
           double chi1,chi2, chi3;
           chi1 = chi2 = chi3 = 0;
           for(int j=0; j< 4; j++){
             chi1 += pow((rlx1[j]-(rb1*rlz1[j]+ra1))/err[j],2);
             chi2 += pow((rlx2[j]-(rb2*rlz2[j]+ra2))/err[j],2);
             chi3 += pow((rlx3[j]-(rb3*rlz3[j]+ra3))/err[j],2);
           }
   
           double ras[3]     = {ra1, ra2, ra3};//3 is number of targets
           double rbs[3]     = {rb1, rb2, rb3}; 
           double chi_cand[3] = {chi1, chi2, chi3};
           auto   min_t = std::min_element(std::begin(chi_cand), std::end(chi_cand));
           int		min_i = std::distance(std::begin(chi_cand), min_t);
           if (chi_cand[min_i] < kRoughFitChiSquareThreshold[0]) {
               cluster_set->chi_square = chi_cand[min_i];
             	cluster_set->target_id  = min_i;
            	cluster_set->coefs[0]   = ras[min_i]; 
   	         cluster_set->coefs[1]   = rbs[min_i]; 
               return true;
             }
           return false;
        }	
  } // three targets case

}



//bool E16ANA_StraightTrackCandidates::IsXTrackCandidate(OneAxisClusterSet* cluster_set, int in_mid) {
//  auto& pos_set = cluster_set->global_poss;
//  int mid       = in_mid -100;
//  TVector2 trod1(-0.8, -19);
//  TVector2 trod2(-0.8, 0);
//  TVector2 trod3(-0.8, 19);
//  TVector2 ggt1(pos_set[1].X(),pos_set[1].Z());
//  TVector2 ggt2(pos_set[2].X(),pos_set[2].Z());
//  TVector2 ggt3(pos_set[3].X(),pos_set[3].Z());
//
//  TVector2  rod1 = trod1.Rotate(Agtr[mid]*cpi/180);
//  TVector2  rod2 = trod2.Rotate(Agtr[mid]*cpi/180);
//  TVector2  rod3 = trod3.Rotate(Agtr[mid]*cpi/180);
////  TVector2  lssd = gssd.Rotate(Agtr[mid]*cpi/180);
//  TVector2  lgt1 = ggt1.Rotate(Agtr[mid]*cpi/180);
//  TVector2  lgt2 = ggt2.Rotate(Agtr[mid]*cpi/180);
//  TVector2  lgt3 = ggt3.Rotate(Agtr[mid]*cpi/180);
//
////  double rlx1[]={rod1.X(),lssd.X(),lgt1.X(),lgt2.X(),lgt3.X()};
////  double rlz1[]={rod1.Y(),lssd.Y(),lgt1.Y(),lgt2.Y(),lgt3.Y()};
////  double rlx2[]={rod2.X(),lssd.X(),lgt1.X(),lgt2.X(),lgt3.X()};
////  double rlz2[]={rod2.Y(),lssd.Y(),lgt1.Y(),lgt2.Y(),lgt3.Y()};
//  double rlx1[]={rod1.X(),lgt1.X(),lgt2.X(),lgt3.X()};
//  double rlz1[]={rod1.Y(),lgt1.Y(),lgt2.Y(),lgt3.Y()};
//  double rlx2[]={rod2.X(),lgt1.X(),lgt2.X(),lgt3.X()};
//  double rlz2[]={rod2.Y(),lgt1.Y(),lgt2.Y(),lgt3.Y()};
//  double rlx3[]={rod3.X(),lgt1.X(),lgt2.X(),lgt3.X()};
//  double rlz3[]={rod3.Y(),lgt1.Y(),lgt2.Y(),lgt3.Y()};
//  //double err[]={0.4,0.1,0.3,0.3,0.3};
//  //double err[]={0.6,0.1,0.3,1.5,1.0};
//  //double err[]={0.6,0.1,0.2,999999,0.4};
////  double err[]={0.3,0.1,0.3,0.3,0.8};
////  double err[]={0.3,0.3,0.3,0.8};
////  double err[]={kXSigmaIncTgt[0],kXSigmaIncTgt[1],kXSigmaIncTgt[2],kXSigmaIncTgt[3]};
//    double err[]={kXSigmaIncTgt[0],kXSigmaIncTgt[2],kXSigmaIncTgt[3],kXSigmaIncTgt[4]};//wo SSD
//
//
////  std::cout << "lgt1x = "  << lgt1.X() << ", " << lgt1.Y() << ", " << std::endl;
//
//
//
//  double ra1,rb1;
//  fline(4,rlz1,rlx1,err,ra1,rb1);
//  double ra2,rb2;
//  fline(4,rlz2,rlx2,err,ra2,rb2);
//  double ra3,rb3;
//  fline(4,rlz3,rlx3,err,ra3,rb3);
//
//  double chi1,chi2, chi3;
//  chi1 = chi2 = chi3 = 0;
////  for(int i=0;i<5;i++){
//  for(int i=0;i<4;i++){
////    std::cout << " " << ra1 << ", " << rb1 << ", " << rlz1[i]<<", "  << rlx1[i] << std::endl;
//    chi1 += pow((rlx1[i]-(rb1*rlz1[i]+ra1))/err[i],2);
//    chi2 += pow((rlx2[i]-(rb2*rlz2[i]+ra2))/err[i],2);
//    chi3 += pow((rlx3[i]-(rb3*rlz3[i]+ra3))/err[i],2);
//  }
//
////        std::cout <<"chi2_1 = " <<  chi1 << std::endl;
////        std::cout <<"chi2_2 = " <<  chi2 << std::endl;
////        std::cout <<"chi2_3 = " <<  chi3 << std::endl;
//  double ras[E16ANA_StraightTrackConstant::kNumTargets]     = {ra1, ra2, ra3}; 
//  double rbs[E16ANA_StraightTrackConstant::kNumTargets]     = {rb1, rb2, rb3}; 
//  double chi_cand[E16ANA_StraightTrackConstant::kNumTargets] = {chi1, chi2, chi3};
//  auto   min_t = std::min_element(std::begin(chi_cand), std::end(chi_cand));
//  int		min_i = std::distance(std::begin(chi_cand), min_t);
//
//  if (chi_cand[min_i] < kRoughFitChiSquareThreshold[0]) {
////    cluster_set->charge = 1;
////    if(chi2<chi1)  cluster_set->charge = -1;
//    cluster_set->chi_square = chi_cand[min_i];
//	 cluster_set->target_id  = min_i;
//	 cluster_set->coefs[0]   = ras[min_i]; 
//	 cluster_set->coefs[1]   = rbs[min_i]; 
//    return true;
//  }
//  return false;
//}

//bool E16ANA_StraightTrackCandidates::IsYTrackCandidate(OneAxisClusterSet* cluster_set) {
//  auto& pos_set = cluster_set->global_poss;
////targets position 
//  int n_tgt = targets_pos.size(); 
//  std::vector<double> tgt_y;
//  std::vector<double> tgt_r;
//  tgt_y.resize(n_tgt);
//  tgt_r.resize(n_tgt);
//  for(int i=0; i < n_tgt; i++){
//     tgt_y[i] = targets_pos[i].y();
//     tgt_r[i] = targets_pos[i].x() * targets_pos[i].x() + targets_pos[i].z() * targets_pos[i].z();
//  }
//
//#ifdef REMOVE_GTR100
//  std::array<double, kNumGTRLayers> gtr_y({0, pos_set[2].Y(), pos_set[3].Y()});
//  std::array<double, kNumGTRLayers> gtr_r({0,
//                                           sqrt(pos_set[2].X() * pos_set[2].X() + pos_set[2].Z() * pos_set[2].Z()),
//                                           sqrt(pos_set[3].X() * pos_set[3].X() + pos_set[3].Z() * pos_set[3].Z())});
//#elif REMOVE_GTR200
//  std::array<double, kNumGTRLayers> gtr_y({pos_set[1].Y(), 0, pos_set[3].Y()});
//  std::array<double, kNumGTRLayers> gtr_r({sqrt(pos_set[1].X() * pos_set[1].X() + pos_set[1].Z() * pos_set[1].Z()),
//                                           0,
//                                           sqrt(pos_set[3].X() * pos_set[3].X() + pos_set[3].Z() * pos_set[3].Z())});
//#elif REMOVE_GTR300
//  std::array<double, kNumGTRLayers> gtr_y({pos_set[1].Y(), pos_set[2].Y(), 0});
//  std::array<double, kNumGTRLayers> gtr_r({sqrt(pos_set[1].X() * pos_set[1].X() + pos_set[1].Z() * pos_set[1].Z()),
//                                           sqrt(pos_set[2].X() * pos_set[2].X() + pos_set[2].Z() * pos_set[2].Z()),
//                                           0 });
//#else
//  std::array<double, kNumGTRLayers> gtr_y({pos_set[1].Y(), pos_set[2].Y(), pos_set[3].Y()});
//  std::array<double, kNumGTRLayers> gtr_r({sqrt(pos_set[1].X() * pos_set[1].X() + pos_set[1].Z() * pos_set[1].Z()),
//                                           sqrt(pos_set[2].X() * pos_set[2].X() + pos_set[2].Z() * pos_set[2].Z()),
//                                           sqrt(pos_set[3].X() * pos_set[3].X() + pos_set[3].Z() * pos_set[3].Z())});
//
//#endif
//
//
//  if (fabs(kGTRSizeCoef[0] * gtr_y[0] - kGTRSizeCoef[1] * gtr_y[1]) > kGTRYDiffThreshold ||
//      fabs(kGTRSizeCoef[0] * gtr_y[0] - kGTRSizeCoef[2] * gtr_y[2]) > kGTRYDiffThreshold ||
//      fabs(kGTRSizeCoef[1] * gtr_y[1] - kGTRSizeCoef[2] * gtr_y[2]) > kGTRYDiffThreshold) {
////cout << "y subtract bad" << endl;
//#ifdef TRACK_EFF_CHECK
//    for (int i = 0; i < 2; ++i) {
//      if (is_sim_ycluster[i][0] && is_sim_ycluster[i][1] && is_sim_ycluster[i][2]) {
//        y_reject_point[i] += Pow2(kRejYSubtract);
//      }
//    }
//#endif
//    return false;
//  }
//
//  double r2 [n_tgt]={ 0.};
//  double r  [n_tgt]={ 0.};
//  double c  [n_tgt]={ 0.};
//  double ry [n_tgt]={ 0.};
//  double y  [n_tgt]={ 0.};
//
//  
//  for (int tgt = 0; tgt < n_tgt; ++tgt) {
//    r2[tgt] += kWeightInit[1] * tgt_r[tgt] * tgt_r[tgt];
//    r [tgt] += kWeightInit[1] * tgt_r[tgt];
//    c [tgt] += kWeightInit[1];
//    ry[tgt] += kWeightInit[1] * tgt_r[tgt] * tgt_y[tgt];
//    y [tgt] += kWeightInit[1] * tgt_y[tgt];
//	 
//    for (int i = 0; i < kNumGTRLayers; ++i) {
//      r2[tgt] += kYWeight[i] * gtr_r[i] * gtr_r[i];
//      r [tgt] += kYWeight[i] * gtr_r[i];
//      c [tgt] += kYWeight[i];
//      ry[tgt] += kYWeight[i] * gtr_r[i] * gtr_y[i];
//      y [tgt] += kYWeight[i] * gtr_y[i];
//    }
//  }
//  
//  
//  std::vector<std::vector<double>> coef;
//  coef.resize(n_tgt);	
//  for(int tgt=0; tgt < n_tgt; tgt++){
//	 coef[tgt].resize(kNumRoughFitDegree[1]);
//    coef[tgt] = {(r2[tgt] * y[tgt]  - r[tgt] * ry[tgt]) / (c[tgt] * r2[tgt] - r[tgt] * r[tgt]),
//                  (c[tgt]  * ry[tgt] - r[tgt] * y[tgt])  / (c[tgt] * r2[tgt] - r[tgt] * r[tgt])};
//  }
//
//  double chi2_cand[n_tgt] = {0.};
//
//  
//  for (int tgt = 0; tgt < n_tgt; ++tgt) {
//    std::array<double, kNumGTRLayers + 1> fit_y;
//    for (int i = 0; i < kNumGTRLayers; ++i) {
//      fit_y[i] = coef[tgt][0] + coef[tgt][1] * gtr_r[i];//a + bx 
//      chi2_cand[tgt] += kYWeight[i] * (fit_y[i] - gtr_y[i]) * (fit_y[i] - gtr_y[i]);
//    }
//    fit_y[kNumGTRLayers + 1] = coef[tgt][0] + coef[tgt][1] * tgt_r[tgt];//a + bx 
//    chi2_cand[tgt] += kWeightInit[1] * (fit_y[kNumGTRLayers + 1] - tgt_y[tgt]) * (fit_y[kNumGTRLayers + 1] - tgt_y[tgt]);
//  }
//
//  double min_chi2 = 999999;
//  int min_tgt_id = 99999;
//  for(int i=0; i < n_tgt; i++){
//    if(chi2_cand[i] < min_chi2) {
//      min_chi2 = chi2_cand[i];
//		min_tgt_id = i;
//	 }
//  }
//  
//
//  if (min_chi2 < kRoughFitChiSquareThreshold[1] && fabs(coef[min_tgt_id][0]) < kRoughYFitCoefficientThreshold[0]) {
//    cluster_set->xy = coef[min_tgt_id][0];
//    cluster_set->chi_square = min_chi2;
//    for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
//      cluster_set->coefs[i] = coef[min_tgt_id][i];
//    }
//    return true;
//  }
//#ifdef TRACK_EFF_CHECK
//  for (int i = 0; i < 2; ++i) {
//    if (is_sim_ycluster[i][0] && is_sim_ycluster[i][1] && is_sim_ycluster[i][2]) {
//      if (min_chi2 < kRoughFitChiSquareThreshold[1]) {
//        y_reject_point[i] += Pow2(kRejYChi2);
//      }
//      if (fabs(coef[min_tgt_id][0]) < kRoughYFitCoefficientThreshold[0]) {
//        y_reject_point[i] += Pow2(kRejYCoef0);
//      }
//    }
//  }
//#endif
////cout << "y chi2 bad" << endl;
//  return false;
//
////  double r2 = 0.;
////  double r  = 0.;
////  double c  = 0.;
////  double ry = 0.;
////  double y  = 0.;
////  for (int i = 0; i < kNumGTRLayers; ++i) {
////    r2 += kYWeight[i] * gtr_r[i] * gtr_r[i];
////    r  += kYWeight[i] * gtr_r[i];
////    c  += kYWeight[i];
////    ry += kYWeight[i] * gtr_r[i] * gtr_y[i];
////    y  += kYWeight[i] * gtr_y[i];
////  }
////
////
////
////
////  
////  std::array<double, kNumRoughFitDegree[1]> coef({(r2 * y  - r * ry) / (c * r2 - r * r),
////                                                  (c  * ry - r * y)  / (c * r2 - r * r)});
////  double chi2_cand = 0.;
////  std::array<double, kNumGTRLayers> fit_y;
////  for (int i = 0; i < kNumGTRLayers; ++i) {
////    fit_y[i] = coef[0] + coef[1] * gtr_r[i];//a + bx 
////    chi2_cand += kYWeight[i] * (fit_y[i] - gtr_y[i]) * (fit_y[i] - gtr_y[i]);
////  }
////
////
////  if (chi2_cand < kRoughFitChiSquareThreshold[1] && fabs(coef[0]) < kRoughYFitCoefficientThreshold[0]) {
////    cluster_set->xy = coef[0];
////    cluster_set->chi_square = chi2_cand;
////    for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
////      cluster_set->coefs[i] = coef[i];
////    }
////    return true;
////  }
////#ifdef TRACK_EFF_CHECK
////  for (int i = 0; i < 2; ++i) {
////    if (is_sim_ycluster[i][0] && is_sim_ycluster[i][1] && is_sim_ycluster[i][2]) {
////      if (chi2_cand < kRoughFitChiSquareThreshold[1]) {
////        y_reject_point[i] += Pow2(kRejYChi2);
////      }
////      if (fabs(coef[0]) < kRoughYFitCoefficientThreshold[0]) {
////        y_reject_point[i] += Pow2(kRejYCoef0);
////      }
////    }
////  }
////#endif
//////cout << "y chi2 bad" << endl;
////  return false;
//}
//

bool E16ANA_StraightTrackCandidates::IsYTrackCandidate(OneAxisClusterSet* cluster_set) {
  auto& pos_set = cluster_set->global_poss;
  if(isWire){//wire case
	 for(int tgt=0; tgt < targets_pos.size(); tgt++){
    std::array<double, kNumGTRLayers> gtr_y({pos_set[1].Y(), pos_set[2].Y(), pos_set[3].Y()});
    std::array<double, kNumGTRLayers> gtr_r({sqrt(pow(pos_set[1].X() - targets_pos[tgt].x(),2) +pow(pos_set[1].Z() - targets_pos[tgt].z(),2)),
    sqrt(pow(pos_set[2].X() - targets_pos[tgt].x(),2) +pow(pos_set[2].Z() - targets_pos[tgt].z(),2)),
  	 sqrt(pow(pos_set[3].X() - targets_pos[tgt].x(),2) +pow(pos_set[3].Z() - targets_pos[tgt].z(),2))});
    double r2 = 0.;
    double r  = 0.;
    double c  = 0.;
    double ry = 0.;
    double y  = 0.;

//targets
    r2 += kYTargetWeight* 0.0 * 0.0;
    r  += kYTargetWeight*0.0 ;
    c  += kYTargetWeight;
    ry += kYTargetWeight* 0.0 * 0.0;
    y  += kYTargetWeight* 0.0 ;
//gtr layers
    for (int i = 0; i < kNumGTRLayers; ++i) {
      r2 += kYWeight[i] * gtr_r[i] * gtr_r[i];
      r  += kYWeight[i] * gtr_r[i];
      c  += kYWeight[i];
      ry += kYWeight[i] * gtr_r[i] * gtr_y[i];
      y  += kYWeight[i] * gtr_y[i];
    }
    std::array<double, kNumRoughFitDegree[1]> coef({(r2 * y  - r * ry) / (c * r2 - r * r),
                                                    (c  * ry - r * y)  / (c * r2 - r * r)});
    double chi2_cand = 0.;
    std::array<double, kNumGTRLayers> fit_y;

    for (int i = 0; i < kNumGTRLayers; ++i) {
      fit_y[i] = coef[0] + coef[1] * gtr_r[i];
      chi2_cand += kYWeight[i] * (fit_y[i] - gtr_y[i]) * (fit_y[i] - gtr_y[i]);
    }
      fit_y[kNumGTRLayers + 1] = coef[0] + coef[1] * 0.0;// targets
      chi2_cand += kYTargetWeight * (fit_y[kNumGTRLayers + 1] - 0.0 ) * (fit_y[kNumGTRLayers + 1] - 0.0);//targets
    if (chi2_cand < kRoughFitChiSquareThreshold[1] && fabs(coef[0]) < kRoughYFitCoefficientThreshold[0]) {
      cluster_set->xy = coef[0];
      cluster_set->chi_square = chi2_cand;
      for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
        cluster_set->coefs[i] = coef[i];
      }
      return true;
		}
    }//wire target loop
    return false;
  }
  
  else{
// ---- three targets case --- //
//
// targets position 
  int n_tgt = targets_pos.size(); 
  std::vector<double> tgt_y;
  std::vector<double> tgt_r;
  tgt_y.resize(n_tgt);
  tgt_r.resize(n_tgt);
  for(int i=0; i < n_tgt; i++){
     tgt_y[i] = targets_pos[i].y();
     tgt_r[i] = targets_pos[i].x() * targets_pos[i].x() + targets_pos[i].z() * targets_pos[i].z();
  }
// detector positions
  std::array<double, kNumGTRLayers> gtr_y({pos_set[1].Y(), pos_set[2].Y(), pos_set[3].Y()});
  std::array<double, kNumGTRLayers> gtr_r({sqrt(pos_set[1].X() * pos_set[1].X() + pos_set[1].Z() * pos_set[1].Z()),
                                           sqrt(pos_set[2].X() * pos_set[2].X() + pos_set[2].Z() * pos_set[2].Z()),
                                           sqrt(pos_set[3].X() * pos_set[3].X() + pos_set[3].Z() * pos_set[3].Z())});

  if (fabs(kGTRSizeCoef[0] * gtr_y[0] - kGTRSizeCoef[1] * gtr_y[1]) > kGTRYDiffThreshold ||
      fabs(kGTRSizeCoef[0] * gtr_y[0] - kGTRSizeCoef[2] * gtr_y[2]) > kGTRYDiffThreshold ||
      fabs(kGTRSizeCoef[1] * gtr_y[1] - kGTRSizeCoef[2] * gtr_y[2]) > kGTRYDiffThreshold) {
//cout << "y subtract bad" << endl;
#ifdef TRACK_EFF_CHECK
    for (int i = 0; i < 2; ++i) {
      if (is_sim_ycluster[i][0] && is_sim_ycluster[i][1] && is_sim_ycluster[i][2]) {
        y_reject_point[i] += Pow2(kRejYSubtract);
      }
    }
#endif
    return false;
  }

  double r2 [n_tgt]={ 0.};
  double r  [n_tgt]={ 0.};
  double c  [n_tgt]={ 0.};
  double ry [n_tgt]={ 0.};
  double y  [n_tgt]={ 0.};

  
  for (int tgt = 0; tgt < n_tgt; ++tgt) {
    r2[tgt] += kWeightInit[1] * tgt_r[tgt] * tgt_r[tgt];
    r [tgt] += kWeightInit[1] * tgt_r[tgt];
    c [tgt] += kWeightInit[1];
    ry[tgt] += kWeightInit[1] * tgt_r[tgt] * tgt_y[tgt];
    y [tgt] += kWeightInit[1] * tgt_y[tgt];
	 
    for (int i = 0; i < kNumGTRLayers; ++i) {
      r2[tgt] += kYWeight[i] * gtr_r[i] * gtr_r[i];
      r [tgt] += kYWeight[i] * gtr_r[i];
      c [tgt] += kYWeight[i];
      ry[tgt] += kYWeight[i] * gtr_r[i] * gtr_y[i];
      y [tgt] += kYWeight[i] * gtr_y[i];
    }
  }
  std::vector<std::vector<double>> coef;
  coef.resize(n_tgt);	
  for(int tgt=0; tgt < n_tgt; tgt++){
	 coef[tgt].resize(kNumRoughFitDegree[1]);
    coef[tgt] = {(r2[tgt] * y[tgt]  - r[tgt] * ry[tgt]) / (c[tgt] * r2[tgt] - r[tgt] * r[tgt]),
                  (c[tgt]  * ry[tgt] - r[tgt] * y[tgt])  / (c[tgt] * r2[tgt] - r[tgt] * r[tgt])};
  }

  double chi2_cand[n_tgt] = {0.};
  
  for (int tgt = 0; tgt < n_tgt; ++tgt) {
    std::array<double, kNumGTRLayers + 1> fit_y;
    for (int i = 0; i < kNumGTRLayers; ++i) {
      fit_y[i] = coef[tgt][0] + coef[tgt][1] * gtr_r[i];//a + bx 
      chi2_cand[tgt] += kYWeight[i] * (fit_y[i] - gtr_y[i]) * (fit_y[i] - gtr_y[i]);
    }
    fit_y[kNumGTRLayers + 1] = coef[tgt][0] + coef[tgt][1] * tgt_r[tgt];//a + bx 
    chi2_cand[tgt] += kWeightInit[1] * (fit_y[kNumGTRLayers + 1] - tgt_y[tgt]) * (fit_y[kNumGTRLayers + 1] - tgt_y[tgt]);
  }

  double min_chi2 = 999999;
  int min_tgt_id = 99999;
  for(int i=0; i < n_tgt; i++){
    if(chi2_cand[i] < min_chi2) {
      min_chi2 = chi2_cand[i];
		min_tgt_id = i;
	 }
  }

  if (min_chi2 < kRoughFitChiSquareThreshold[1] && fabs(coef[min_tgt_id][0]) < kRoughYFitCoefficientThreshold[0]) {
    cluster_set->xy = coef[min_tgt_id][0];
    cluster_set->chi_square = min_chi2;
    for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
      cluster_set->coefs[i] = coef[min_tgt_id][i];
    }
    return true;
  }
#ifdef TRACK_EFF_CHECK
  for (int i = 0; i < 2; ++i) {
    if (is_sim_ycluster[i][0] && is_sim_ycluster[i][1] && is_sim_ycluster[i][2]) {
      if (min_chi2 < kRoughFitChiSquareThreshold[1]) {
        y_reject_point[i] += Pow2(kRejYChi2);
      }
      if (fabs(coef[min_tgt_id][0]) < kRoughYFitCoefficientThreshold[0]) {
        y_reject_point[i] += Pow2(kRejYCoef0);
      }
    }
  }
#endif
//cout << "y chi2 bad" << endl;
  return false;

//  double r2 = 0.;
//  double r  = 0.;
//  double c  = 0.;
//  double ry = 0.;
//  double y  = 0.;
//  for (int i = 0; i < kNumGTRLayers; ++i) {
//    r2 += kYWeight[i] * gtr_r[i] * gtr_r[i];
//    r  += kYWeight[i] * gtr_r[i];
//    c  += kYWeight[i];
//    ry += kYWeight[i] * gtr_r[i] * gtr_y[i];
//    y  += kYWeight[i] * gtr_y[i];
//  }
//
//
//
//
//  
//  std::array<double, kNumRoughFitDegree[1]> coef({(r2 * y  - r * ry) / (c * r2 - r * r),
//                                                  (c  * ry - r * y)  / (c * r2 - r * r)});
//  double chi2_cand = 0.;
//  std::array<double, kNumGTRLayers> fit_y;
//  for (int i = 0; i < kNumGTRLayers; ++i) {
//    fit_y[i] = coef[0] + coef[1] * gtr_r[i];//a + bx 
//    chi2_cand += kYWeight[i] * (fit_y[i] - gtr_y[i]) * (fit_y[i] - gtr_y[i]);
//  }
//
//
//  if (chi2_cand < kRoughFitChiSquareThreshold[1] && fabs(coef[0]) < kRoughYFitCoefficientThreshold[0]) {
//    cluster_set->xy = coef[0];
//    cluster_set->chi_square = chi2_cand;
//    for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
//      cluster_set->coefs[i] = coef[i];
//    }
//    return true;
//  }
//#ifdef TRACK_EFF_CHECK
//  for (int i = 0; i < 2; ++i) {
//    if (is_sim_ycluster[i][0] && is_sim_ycluster[i][1] && is_sim_ycluster[i][2]) {
//      if (chi2_cand < kRoughFitChiSquareThreshold[1]) {
//        y_reject_point[i] += Pow2(kRejYChi2);
//      }
//      if (fabs(coef[0]) < kRoughYFitCoefficientThreshold[0]) {
//        y_reject_point[i] += Pow2(kRejYCoef0);
//      }
//    }
//  }
//#endif
////cout << "y chi2 bad" << endl;
//  return false;
}//three targets case





}

double E16ANA_StraightTrackCandidates::GTRTimeDiffThreshold(int n) { return kGTRTimeDiffThreshold[n]; }
double E16ANA_StraightTrackCandidates::XSigma(int n) { return kXSigmaIncTgt[n]; }
double E16ANA_StraightTrackCandidates::XWeight(int n) { return kXWeight[n]; }
double E16ANA_StraightTrackCandidates::YSigma(int n) { return kYSigma[n]; }
double E16ANA_StraightTrackCandidates::YWeight(int n) { return kYWeight[n]; }
int E16ANA_StraightTrackCandidates::MinHitsInXCluster() { return kMinHitsInXCluster; }
double E16ANA_StraightTrackCandidates::GTRYDiffThreshold() { return kGTRYDiffThreshold; }
double E16ANA_StraightTrackCandidates::GTRPeakSumThresholdX(int n) { return kGTRPeakSumThresholdX[n]; }
double E16ANA_StraightTrackCandidates::GTRPeakSumThresholdY(int n) { return kGTRPeakSumThresholdY[n]; }
double E16ANA_StraightTrackCandidates::RoughFitChiSquareThreshold(int n) { return kRoughFitChiSquareThreshold[n]; }
double E16ANA_StraightTrackCandidates::RoughXFitCoefficientThreshold(int n) { return kRoughXFitCoefficientThreshold[n]; }
double E16ANA_StraightTrackCandidates::RoughYFitCoefficientThreshold(int n) { return kRoughYFitCoefficientThreshold[n]; }

void E16ANA_StraightTrackCandidates::SearchTrackCandidatesWoSSD() {
  track_candidates.clear();
  track_candidates.reserve(kNumReserveTracks[2]); // tmp
  auto& gtr = record->GTR();
//E16MESSAGE("number of GTR clusters: %d", gtr.NumClusters());
E16INFO("number of GTR clusters: %d", gtr.NumClusters());
//  if(gtr.NumClusters() > 5000) return;
  std::array<std::vector<OneAxisClusterSet>, 2> cluster_sets;
  cluster_sets[0].reserve(kNumReserveTracks[0]);
  cluster_sets[1].reserve(kNumReserveTracks[1]);
  auto cluster_set = new OneAxisClusterSet();

    for (const auto& gtr100_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
		auto is_l = IsLModule(gtr100_module_id);
      auto& gtr100x_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsX);
      for (const auto& gtr200_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
//        if (is_l != IsLModule(gtr200_module_id)) {
      if (abs(gtr200_module_id - gtr100_module_id) > 1) {
          continue;
        }
        auto& gtr200x_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsX);
        for (const auto& gtr300_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
       //   if (is_l != IsLModule(gtr300_module_id)) {
	      if (abs(gtr300_module_id - gtr100_module_id) > 1) {
            continue;
          }
          auto& gtr300x_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsX);

            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
              if (gtr100x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR100 - 1]) {
                continue;
              }
              if (gtr100x_cluster->NumHits() < kMinHitsInXCluster) {
                continue;
              }
//              #ifndef EFFICIANCY_EVAL
//                if(gtr100x_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif


              cluster_set->gtr_clusters[0] = gtr100x_cluster;
              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100x_cluster->GlobalPosT(*geometry);
	      TVector3 testg = gtr100x_cluster->GlobalPos(*geometry);
//			std::cout << "peaksum1 = " << gtr100x_cluster->PeakSum() << std::endl;
//std::cout << "local  pos = " << gtr100x_cluster->TdcPos() << std::endl;
// std::cout << "global pos = " << cluster_set->global_poss[1].X() << std::endl;

//	      printf("x:%f,%f    y:%f,%f     z:%f,%f \n",cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100].X(),testg.X(),
	      //     cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100].Y(),testg.Y(),
	      //     cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100].Z(),testg.Z());

              for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
                if (gtr200x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR200 - 1]) {
                  continue;
                }
                if (gtr200x_cluster->NumHits() < kMinHitsInXCluster) {
                  continue;
                }
//           #ifndef EFFICIANCY_EVAL
//                if(gtr200x_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif


                cluster_set->gtr_clusters[1] = gtr200x_cluster;
                cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR200] = gtr200x_cluster->GlobalPosT(*geometry);
                for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
                  if (gtr300x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR300 - 1]) {
                    continue;
                  }
                  if (gtr300x_cluster->NumHits() < kMinHitsInXCluster) {
                    continue;
                  }
//           #ifndef EFFICIANCY_EVAL
//                if(gtr300x_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif





                  cluster_set->gtr_clusters[2] = gtr300x_cluster;
                  cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR300] = gtr300x_cluster->GlobalPosT(*geometry);
		  				bool is_cand = false;
                  double chi2 = 5;
//			std::cout << "peaksum2 = " << gtr200x_cluster->PeakSum() << std::endl;
//			std::cout << "peaksum3 = " << gtr300x_cluster->PeakSum() << std::endl;
                  if (IsXTrackCandidate(cluster_set,gtr100_module_id)) {
//std::cout << "id 100 = " << cluster_set->gtr_clusters[0]->ClusterId() << std::endl;
//std::cout << "id 200 = " << cluster_set->gtr_clusters[1]->ClusterId() << std::endl;
//std::cout << "id 300 = " << cluster_set->gtr_clusters[2]->ClusterId() << std::endl;
                    cluster_sets[0].emplace_back(*cluster_set);
                  }
                }
              }
            }
        }
      }
    }

// ---  Y AXIS PART begins --- ///  
  for (const auto& gtr300_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
    if (gtr300_module_id == 105) {
      continue;
    }
    auto is_l = IsLModule(gtr300_module_id);
    auto& gtr300y_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsY);
    for (const auto& gtr200_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
//      if (is_l != IsLModule(gtr200_module_id)) {
      if (abs(gtr300_module_id - gtr200_module_id) > 1) {
        continue;
      }
      auto& gtr200y_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsY);
      for (const auto& gtr100_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
//        if (is_l != IsLModule(gtr100_module_id)) {
      if (abs(gtr300_module_id - gtr100_module_id) > 1) {
          continue;
        }
        auto& gtr100y_cluster_ptrs  = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsY);
        auto& gtr100yb_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsYb);
        for (const auto& gtr300y_cluster : gtr300y_cluster_ptrs) {
          if (gtr300y_cluster->PeakSum() < kGTRPeakSumThresholdY[E16ANA_StraightTrackConstant::kGTR300-1]) {
            continue;
          }
//           #ifndef EFFICIANCY_EVAL
//                if(gtr300y_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif
//

          cluster_set->gtr_clusters[2] = gtr300y_cluster;
          cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR300] = gtr300y_cluster->GlobalPosT(*geometry);
          for (const auto& gtr200y_cluster : gtr200y_cluster_ptrs) {
            if (gtr200y_cluster->PeakSum() < kGTRPeakSumThresholdY[E16ANA_StraightTrackConstant::kGTR200-1]) {
              continue;
            }
//           #ifndef EFFICIANCY_EVAL
//                if(gtr200y_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif


            cluster_set->gtr_clusters[1] = gtr200y_cluster;
            cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR200] = gtr200y_cluster->GlobalPosT(*geometry);
            for (const auto& gtr100y_cluster : gtr100y_cluster_ptrs) {
              if (gtr100y_cluster->PeakSum() < kGTRPeakSumThresholdY[E16ANA_StraightTrackConstant::kGTR100-1]) {
                continue;
              }
//           #ifndef EFFICIANCY_EVAL
//                if(gtr100y_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif
//

              cluster_set->gtr_clusters[0] = gtr100y_cluster;
              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100y_cluster->GlobalPosT(*geometry);
              if (IsYTrackCandidate(cluster_set)) {
                cluster_sets[1].emplace_back(*cluster_set);
              }
            }
            for (const auto& gtr100yb_cluster : gtr100yb_cluster_ptrs) {
              if (gtr100yb_cluster->PeakSum() < kGTRPeakSumThresholdY[E16ANA_StraightTrackConstant::kGTR100-1]) {
                continue;
              }
//           #ifndef EFFICIANCY_EVAL
//                if(gtr100yb_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif
              cluster_set->gtr_clusters[0] = gtr100yb_cluster;
              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100yb_cluster->GlobalPosT(*geometry);
// std::cout << "yb " << gtr100yb_cluster->PeakSum() << std::endl;
              if (IsYTrackCandidate(cluster_set)) {
                cluster_sets[1].emplace_back(*cluster_set);
              }
            }
          }
        }
      }
    }
  }
  delete cluster_set;
  n_x_cands = cluster_sets[0].size();
  n_y_cands = cluster_sets[1].size();
//E16MESSAGE("number of x candidates: %d", n_x_cands);
//E16MESSAGE("number of y candidates: %d", n_y_cands);
E16INFO("number of x candidates: %d", n_x_cands);
E16INFO("number of y candidates: %d", n_y_cands);

  if(n_x_cands > 500) return;
  if(n_y_cands > 500) return;
  
  int count = 0;
  int county = 0;
  for (const auto& x_cand : cluster_sets[0]) {
		count++;
//    auto& ssdx = *x_cand.ssd_cluster;
    auto& gtrx = x_cand.gtr_clusters;
    std::array<int, kNumGTRLayers> x_module_ids = {gtrx[0]->ModuleId(), gtrx[1]->ModuleId(), gtrx[2]->ModuleId()};
    std::array<float, kNumGTRLayers> x_timings = {gtrx[0]->Timing4(), gtrx[1]->Timing4(), gtrx[2]->Timing4()};
    std::array<float, kNumGTRLayers> x_peak_sums = {gtrx[0]->PeakSum(), gtrx[1]->PeakSum(), gtrx[2]->PeakSum()};
    for (const auto& y_cand : cluster_sets[1]) {
     county++;
      auto& gtry = y_cand.gtr_clusters;
      bool is_same_module = true;
      /*
      if ((gtry[0]->IsY() && gtrx[0]->LocalPosT().X() <= 0) || (gtry[0]->IsYb() && gtrx[0]->LocalPosT().X() >= 0)) {
        continue;
      }
      */
      for (int i = 0; i < kNumGTRLayers; ++i) {
// std::cout << "module " << x_module_ids[i] << ", " << gtry[i]->ModuleId() << std::endl;
//std::cout << "timing " << x_timings[i] << ", " << gtry[i]->Timing4() << std::endl;



        if (x_module_ids[i] != gtry[i]->ModuleId() || fabs(x_timings[i] - gtry[i]->Timing4()) > kGTRTimeDiffThreshold[i] ) { // ozawa v8
          is_same_module = false;
          break;
        }
      }
      if (!is_same_module) {
        continue;
      }
//		std::cout << "matched " << count << ", " << county <<  std::endl;
      for (int i = 0; i < kNumGTRLayers; ++i) {
//		std::cout << "timineg"  << x_timings[i] <<", " << gtry[i]->Timing4() << std::endl;
}
      track_candidates.emplace_back(E16ANA_StraightTrackCandidate(geometry));
      auto& tmp_cand = track_candidates.back();
      tmp_cand.SetTrackID(track_candidates.size() - 1);
		if(isWire){
        tmp_cand.SetInitX(targets_pos[x_cand.target_id].x());
        tmp_cand.SetInitY(targets_pos[x_cand.target_id].y());
        tmp_cand.SetInitZ(targets_pos[x_cand.target_id].z());
      }
      else {
			tmp_cand.SetInitX(targets_pos[x_cand.target_id].x());
			tmp_cand.SetInitY(targets_pos[x_cand.target_id].y());
			tmp_cand.SetInitZ(targets_pos[x_cand.target_id].z());
      }
//		std::cout << "xy = " << x_cand.xy << ", y_xy = " << y_cand.xy << std::endl;
//		tmp_cand.SetInitX(x_cand.xy);
//      if(x_cand.charge<0) tmp_cand.SetInitZ(-40);
      tmp_cand.SetDefaultSigma();
      tmp_cand.SetXChiSquare(x_cand.chi_square);
      tmp_cand.SetYChiSquare(y_cand.chi_square);
      for (int i = 0; i < kNumRoughFitDegree[0]; ++i) {
        tmp_cand.SetXCoef(i, x_cand.coefs[i]);
      }
      for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
        tmp_cand.SetYCoef(i, y_cand.coefs[i]);
      }
      auto& cluster_pairs = tmp_cand.ClusterPairs();
//      cluster_pairs[0].Set(geometry, 0, ssdx.ModuleId(), x_cand.global_poss[0], &ssdx);//for ssd
      for (int i = 0; i < kNumGTRLayers; ++i) {
        cluster_pairs[1 + i].Set(geometry, 1 + i, gtrx[i]->ModuleId(), x_cand.global_poss[1 + i], y_cand.global_poss[1 + i], gtrx[i], gtry[i]);

	  int nhit = gtrx[i]->NumCls();
	  for(int j=0;j<nhit;j++){
	    cluster_pairs[1+i].SetCAdc1((double)gtrx[i]->CAdc1(j));
	    cluster_pairs[1+i].SetCPos((double)gtrx[i]->CPos(j));
	    cluster_pairs[1+i].SetCAdc2((double)gtrx[i]->CAdc2(j));
	    cluster_pairs[1+i].SetCAdc3((double)gtrx[i]->CAdc3(j));
	    cluster_pairs[1+i].SetCAdc4((double)gtrx[i]->CAdc4(j));
	    cluster_pairs[1+i].SetCTiming((double)gtrx[i]->CTiming(j));
	    cluster_pairs[1+i].SetCAdc5((double)gtrx[i]->CAdc5(j));
	  }

	  int nhit2 = gtrx[i]->NumCls2();
	  for(int j=0;j<nhit2;j++){
	    cluster_pairs[1+i].SetCTiming2((double)gtrx[i]->CTiming2(j));
	    cluster_pairs[1+i].SetCPos2((double)gtrx[i]->CPos2(j));
	  }
	  int nhit3 = gtrx[i]->NumCls3();
	  for(int j=0;j<nhit3;j++){
	    cluster_pairs[1+i].SetCTiming3((double)gtrx[i]->CTiming3(j));
	    cluster_pairs[1+i].SetCPos3((double)gtrx[i]->CPos3(j));
	  }

	  int nhit4 = gtrx[i]->NumCls4();
	  for(int j=0;j<nhit4;j++){
	    cluster_pairs[1+i].SetCTiming4((double)gtrx[i]->CTiming4(j));
	    cluster_pairs[1+i].SetCPos4((double)gtrx[i]->CPos4(j));
	    cluster_pairs[1+i].SetCTiming5((double)gtrx[i]->CTiming5(j));
	    cluster_pairs[1+i].SetCPos5((double)gtrx[i]->CPos5(j));
	  }
      }
}
    }
}



void E16ANA_StraightTrackCandidates::SearchTrackCandidates() {
  track_candidates.clear();
  track_candidates.reserve(kNumReserveTracks[2]); // tmp
  auto& ssd = record->SSD();
  auto& gtr = record->GTR();
//E16MESSAGE("number of SSD clusters: %d", ssd.NumClusters());
//E16MESSAGE("number of GTR clusters: %d", gtr.NumClusters());
E16INFO("number of SSD clusters: %d", ssd.NumClusters());
E16INFO("number of GTR clusters: %d", gtr.NumClusters());
// if(ssd.NumClusters()>30) return;
  std::array<std::vector<OneAxisClusterSet>, 2> cluster_sets;
  cluster_sets[0].reserve(kNumReserveTracks[0]);
  cluster_sets[1].reserve(kNumReserveTracks[1]);
  auto cluster_set = new OneAxisClusterSet();

  for (const auto& ssd_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
    if (ssd_module_id == 105) {
      continue;
    }
    auto is_l = IsLModule(ssd_module_id);
    auto& ssd_cluster_ptrs = ssd.ClusterPtrs(ssd_module_id, 0, 0);
    for (const auto& gtr100_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
      if (abs(gtr100_module_id - ssd_module_id) > 1) {
  //    if (is_l != IsLModule(gtr100_module_id)) {
        continue;
      }
      auto& gtr100x_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsX);
      for (const auto& gtr200_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
        if (abs(gtr200_module_id - ssd_module_id) > 1) {
//        if (is_l != IsLModule(gtr200_module_id)) {
          continue;
        }
        auto& gtr200x_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsX);
        for (const auto& gtr300_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
          if (abs(gtr300_module_id - ssd_module_id) > 1) {
//          if (is_l != IsLModule(gtr300_module_id)) {
            continue;
          }
          auto& gtr300x_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsX);


          for (const auto& ssd_cluster : ssd_cluster_ptrs) {
            cluster_set->ssd_cluster = ssd_cluster;
            cluster_set->global_poss[E16ANA_StraightTrackConstant::kSSD] = ssd_cluster->GlobalPos(*geometry);
            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
              if (gtr100x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR100 - 1]) {
                continue;
              }
              if (gtr100x_cluster->NumHits() < kMinHitsInXCluster) {
                continue;
              }
//              #ifndef EFFICIANCY_EVAL
//                if(gtr100x_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif

              cluster_set->gtr_clusters[0] = gtr100x_cluster;
              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100x_cluster->GlobalPosT(*geometry);
	      TVector3 testg = gtr100x_cluster->GlobalPos(*geometry);

	      //printf("x:%f,%f    y:%f,%f     z:%f,%f \n",cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100].X(),testg.X(),
	      //     cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100].Y(),testg.Y(),
	      //     cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100].Z(),testg.Z());

              for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
                if (gtr200x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR200 - 1]) {
                  continue;
                }
                if (gtr200x_cluster->NumHits() < kMinHitsInXCluster) {
                  continue;
                }
//              #ifndef EFFICIANCY_EVAL
//                if(gtr200x_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif
                cluster_set->gtr_clusters[1] = gtr200x_cluster;
                cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR200] = gtr200x_cluster->GlobalPosT(*geometry);
                for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
                  if (gtr300x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR300 - 1]) {
                    continue;
                  }
                  if (gtr300x_cluster->NumHits() < kMinHitsInXCluster) {
                    continue;
                  }
//                  #ifndef EFFICIANCY_EVAL
//                  if(gtr300x_cluster->PeakSum() > kGTRFakeADC ){
//                    continue;
//                  }
//                  #endif
                  cluster_set->gtr_clusters[2] = gtr300x_cluster;
                  cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR300] = gtr300x_cluster->GlobalPosT(*geometry);
//                  bool is_cand = false;
		  bool is_cand = false;
                  double chi2 = 5;
                  if (IsXTrackCandidate(cluster_set,ssd_module_id)) {
                    cluster_sets[0].emplace_back(*cluster_set);
                  }

                }
              }
            }
          }
        }
      }
    }
  }

// ---  Y AXIS PART begins --- ///  
  for (const auto& gtr300_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
    if (gtr300_module_id == 105) {
      continue;
    }
    auto is_l = IsLModule(gtr300_module_id);
    auto& gtr300y_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsY);
    for (const auto& gtr200_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
      if (abs(gtr200_module_id - gtr300_module_id) > 1) {
//      if (is_l != IsLModule(gtr200_module_id)) {
        continue;
      }
      auto& gtr200y_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsY);
      for (const auto& gtr100_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
        if (abs(gtr100_module_id - gtr300_module_id) > 1) {
//        if (is_l != IsLModule(gtr100_module_id)) {
          continue;
        }
        auto& gtr100y_cluster_ptrs  = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsY);
        auto& gtr100yb_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsYb);
        for (const auto& gtr300y_cluster : gtr300y_cluster_ptrs) {
          if (gtr300y_cluster->PeakSum() < kGTRPeakSumThresholdY[E16ANA_StraightTrackConstant::kGTR300 - 1]) {
            continue;
          }

//           #ifndef EFFICIANCY_EVAL
//                if(gtr300y_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif
          cluster_set->gtr_clusters[2] = gtr300y_cluster;
          cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR300] = gtr300y_cluster->GlobalPosT(*geometry);
          for (const auto& gtr200y_cluster : gtr200y_cluster_ptrs) {
            if (gtr200y_cluster->PeakSum() < kGTRPeakSumThresholdY[E16ANA_StraightTrackConstant::kGTR200 - 1]) {
              continue;
            }

//           #ifndef EFFICIANCY_EVAL
//                if(gtr200y_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif
            cluster_set->gtr_clusters[1] = gtr200y_cluster;
            cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR200] = gtr200y_cluster->GlobalPosT(*geometry);
            for (const auto& gtr100y_cluster : gtr100y_cluster_ptrs) {
              if (gtr100y_cluster->PeakSum() < kGTRPeakSumThresholdY[E16ANA_StraightTrackConstant::kGTR100 - 1]) {
	      //if (gtr100y_cluster->PeakSum() < 10000) {
                continue;
              }

//           #ifndef EFFICIANCY_EVAL
//                if(gtr100y_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif
              cluster_set->gtr_clusters[0] = gtr100y_cluster;
              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100y_cluster->GlobalPosT(*geometry);
              if (IsYTrackCandidate(cluster_set)) {
                cluster_sets[1].emplace_back(*cluster_set);
              }
            }
            for (const auto& gtr100yb_cluster : gtr100yb_cluster_ptrs) {
              if (gtr100yb_cluster->PeakSum() < kGTRPeakSumThresholdY[E16ANA_StraightTrackConstant::kGTR100 - 1]) {
	      //if (gtr100yb_cluster->PeakSum() < 10000) {
                continue;
              }

//           #ifndef EFFICIANCY_EVAL
//                if(gtr100yb_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif
              cluster_set->gtr_clusters[0] = gtr100yb_cluster;
              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100yb_cluster->GlobalPosT(*geometry);
              if (IsYTrackCandidate(cluster_set)) {
                cluster_sets[1].emplace_back(*cluster_set);
              }
            }
          }
        }
      }
    }
  }
  delete cluster_set;
  n_x_cands = cluster_sets[0].size();
  n_y_cands = cluster_sets[1].size();
E16MESSAGE("number of x candidates: %d", n_x_cands);
E16MESSAGE("number of y candidates: %d", n_y_cands);
  
  for (const auto& x_cand : cluster_sets[0]) {
    auto& ssdx = *x_cand.ssd_cluster;
    auto& gtrx = x_cand.gtr_clusters;
    std::array<int, kNumGTRLayers> x_module_ids = {gtrx[0]->ModuleId(), gtrx[1]->ModuleId(), gtrx[2]->ModuleId()};
    std::array<float, kNumGTRLayers> x_timings = {gtrx[0]->Timing4(), gtrx[1]->Timing4(), gtrx[2]->Timing4()};
    std::array<float, kNumGTRLayers> x_peak_sums = {gtrx[0]->PeakSum(), gtrx[1]->PeakSum(), gtrx[2]->PeakSum()};
    for (const auto& y_cand : cluster_sets[1]) {
      auto& gtry = y_cand.gtr_clusters;
      bool is_same_module = true;
      /*
      if ((gtry[0]->IsY() && gtrx[0]->LocalPosT().X() <= 0) || (gtry[0]->IsYb() && gtrx[0]->LocalPosT().X() >= 0)) {
        continue;
      }
      */
      for (int i = 0; i < kNumGTRLayers; ++i) {
        if (x_module_ids[i] != gtry[i]->ModuleId() || fabs(x_timings[i] - gtry[i]->Timing4()) > kGTRTimeDiffThreshold[i] ) { // ozawa v8
          is_same_module = false;
          break;
        }
      }
      if (!is_same_module) {
        continue;
      }
      track_candidates.emplace_back(E16ANA_StraightTrackCandidate(geometry));
      auto& tmp_cand = track_candidates.back();
      tmp_cand.SetTrackID(track_candidates.size() - 1);
//      tmp_cand.SetCharge(x_cand.charge);

		if(isWire){
        tmp_cand.SetInitX(targets_pos[x_cand.target_id].x());
        tmp_cand.SetInitY(targets_pos[x_cand.target_id].y());
        tmp_cand.SetInitZ(targets_pos[x_cand.target_id].z());
      }
      else {
			tmp_cand.SetInitX(targets_pos[x_cand.target_id].x());
			tmp_cand.SetInitY(targets_pos[x_cand.target_id].y());
			tmp_cand.SetInitZ(targets_pos[x_cand.target_id].z());
      }

      tmp_cand.SetDefaultSigma();
      tmp_cand.SetXChiSquare(x_cand.chi_square);
      tmp_cand.SetYChiSquare(y_cand.chi_square);
      for (int i = 0; i < kNumRoughFitDegree[0]; ++i) {
        tmp_cand.SetXCoef(i, x_cand.coefs[i]);
      }
      for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
        tmp_cand.SetYCoef(i, y_cand.coefs[i]);
      }
      auto& cluster_pairs = tmp_cand.ClusterPairs();
      cluster_pairs[0].Set(geometry, 0, ssdx.ModuleId(), x_cand.global_poss[0], &ssdx);//x only for ssd
      for (int i = 0; i < kNumGTRLayers; ++i) {
        cluster_pairs[1 + i].Set(geometry, 1 + i, gtrx[i]->ModuleId(), x_cand.global_poss[1 + i], y_cand.global_poss[1 + i], gtrx[i], gtry[i]);

	  int nhit = gtrx[i]->NumCls();
	  for(int j=0;j<nhit;j++){
	    cluster_pairs[1+i].SetCAdc1((double)gtrx[i]->CAdc1(j));
	    cluster_pairs[1+i].SetCPos((double)gtrx[i]->CPos(j));
	    cluster_pairs[1+i].SetCAdc2((double)gtrx[i]->CAdc2(j));
	    cluster_pairs[1+i].SetCAdc3((double)gtrx[i]->CAdc3(j));
	    cluster_pairs[1+i].SetCAdc4((double)gtrx[i]->CAdc4(j));
	    cluster_pairs[1+i].SetCTiming((double)gtrx[i]->CTiming(j));
	    cluster_pairs[1+i].SetCAdc5((double)gtrx[i]->CAdc5(j));
	  }

	  int nhit2 = gtrx[i]->NumCls2();
	  for(int j=0;j<nhit2;j++){
	    cluster_pairs[1+i].SetCTiming2((double)gtrx[i]->CTiming2(j));
	    cluster_pairs[1+i].SetCPos2((double)gtrx[i]->CPos2(j));
	  }
	  int nhit3 = gtrx[i]->NumCls3();
	  for(int j=0;j<nhit3;j++){
	    cluster_pairs[1+i].SetCTiming3((double)gtrx[i]->CTiming3(j));
	    cluster_pairs[1+i].SetCPos3((double)gtrx[i]->CPos3(j));
	  }

	  int nhit4 = gtrx[i]->NumCls4();
	  for(int j=0;j<nhit4;j++){
	    cluster_pairs[1+i].SetCTiming4((double)gtrx[i]->CTiming4(j));
	    cluster_pairs[1+i].SetCPos4((double)gtrx[i]->CPos4(j));
	    cluster_pairs[1+i].SetCTiming5((double)gtrx[i]->CTiming5(j));
	    cluster_pairs[1+i].SetCPos5((double)gtrx[i]->CPos5(j));
	  }

      }
    }
  }
}





void E16ANA_StraightTrackCandidates::SearchTrackCandidatesUsingSTS() {
  track_candidates.clear();
  track_candidates.reserve(kNumReserveTracks[2]); // tmp
  auto& sts = record->STS();
  auto& gtr = record->GTR();
//E16MESSAGE("number of STS clusters: %d", sts.NumClusters());
//E16MESSAGE("number of GTR clusters: %d", gtr.NumClusters());
E16INFO("number of STS clusters: %d", sts.NumClusters());
E16INFO("number of GTR clusters: %d", gtr.NumClusters());
  if(sts.NumClusters()>100) return;
  std::array<std::vector<OneAxisClusterSet>, 2> cluster_sets;
  cluster_sets[0].reserve(kNumReserveTracks[0]);
  cluster_sets[1].reserve(kNumReserveTracks[1]);
  auto cluster_set = new OneAxisClusterSet();

  for (const auto& sts_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
    if (sts_module_id == 105) {
      continue;
    }
    auto is_l = IsLModule(sts_module_id);
    auto& sts_cluster_ptrs = sts.ClusterPtrs(sts_module_id, 0, 0);
    for (const auto& gtr100_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
      if (abs(gtr100_module_id - sts_module_id) > 1) {
//        if (is_l != IsLModule(gtr100_module_id)) {
        continue;
      }
      auto& gtr100x_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsX);
      for (const auto& gtr200_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
        if (abs(gtr200_module_id - sts_module_id) > 1) {
//        if (is_l != IsLModule(gtr200_module_id)) {
          continue;
        }
        auto& gtr200x_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsX);
        for (const auto& gtr300_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
          if (abs(gtr300_module_id - sts_module_id) > 1) {
//          if (is_l != IsLModule(gtr300_module_id)) {
            continue;
          }
          auto& gtr300x_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsX);


          for (const auto& sts_cluster : sts_cluster_ptrs) {
            cluster_set->sts_cluster = sts_cluster;
            cluster_set->global_poss[E16ANA_StraightTrackConstant::kSSD] = sts_cluster->GlobalPos(*geometry);
            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
              if (gtr100x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR100 - 1]) {
                continue;
              }
              if (gtr100x_cluster->NumHits() < kMinHitsInXCluster) {
                continue;
              }
//              #ifndef EFFICIANCY_EVAL
//                if(gtr100x_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif

              cluster_set->gtr_clusters[0] = gtr100x_cluster;
              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100x_cluster->GlobalPosT(*geometry);
	      TVector3 testg = gtr100x_cluster->GlobalPos(*geometry);

	      //printf("x:%f,%f    y:%f,%f     z:%f,%f \n",cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100].X(),testg.X(),
	      //     cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100].Y(),testg.Y(),
	      //     cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100].Z(),testg.Z());

              for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
                if (gtr200x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR200 - 1]) {
                  continue;
                }
                if (gtr200x_cluster->NumHits() < kMinHitsInXCluster) {
                  continue;
                }
//              #ifndef EFFICIANCY_EVAL
//                if(gtr200x_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif
                cluster_set->gtr_clusters[1] = gtr200x_cluster;
                cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR200] = gtr200x_cluster->GlobalPosT(*geometry);
                for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
                  if (gtr300x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR300 - 1]) {
                    continue;
                  }
                  if (gtr300x_cluster->NumHits() < kMinHitsInXCluster) {
                    continue;
                  }
//                  #ifndef EFFICIANCY_EVAL
//                  if(gtr300x_cluster->PeakSum() > kGTRFakeADC ){
//                    continue;
//                  }
//                  #endif
                  cluster_set->gtr_clusters[2] = gtr300x_cluster;
                  cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR300] = gtr300x_cluster->GlobalPosT(*geometry);
//                  bool is_cand = false;
		  bool is_cand = false;
                  double chi2 = 5;
                  if (IsXTrackCandidate(cluster_set,sts_module_id)) {
                    cluster_sets[0].emplace_back(*cluster_set);
                  }

                }
              }
            }
          }
        }
      }
    }
  }

// ---  Y AXIS PART begins --- ///  
  for (const auto& gtr300_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
    if (gtr300_module_id == 105) {
      continue;
    }
    auto is_l = IsLModule(gtr300_module_id);
    auto& gtr300y_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsY);
    for (const auto& gtr200_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
      if (abs(gtr200_module_id - gtr300_module_id) > 1) {
//      if (is_l != IsLModule(gtr200_module_id)) {
        continue;
      }
      auto& gtr200y_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsY);
      for (const auto& gtr100_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
        if (abs(gtr100_module_id - gtr300_module_id) > 1) {
//        if (is_l != IsLModule(gtr100_module_id)) {
          continue;
        }
        auto& gtr100y_cluster_ptrs  = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsY);
        auto& gtr100yb_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsYb);
        for (const auto& gtr300y_cluster : gtr300y_cluster_ptrs) {
          if (gtr300y_cluster->PeakSum() < kGTRPeakSumThresholdY[E16ANA_StraightTrackConstant::kGTR300 - 1]) {
            continue;
          }

//           #ifndef EFFICIANCY_EVAL
//                if(gtr300y_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif
          cluster_set->gtr_clusters[2] = gtr300y_cluster;
          cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR300] = gtr300y_cluster->GlobalPosT(*geometry);
          for (const auto& gtr200y_cluster : gtr200y_cluster_ptrs) {
            if (gtr200y_cluster->PeakSum() < kGTRPeakSumThresholdY[E16ANA_StraightTrackConstant::kGTR200 - 1]) {
              continue;
            }

//           #ifndef EFFICIANCY_EVAL
//                if(gtr200y_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif
            cluster_set->gtr_clusters[1] = gtr200y_cluster;
            cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR200] = gtr200y_cluster->GlobalPosT(*geometry);
            for (const auto& gtr100y_cluster : gtr100y_cluster_ptrs) {
              if (gtr100y_cluster->PeakSum() < kGTRPeakSumThresholdY[E16ANA_StraightTrackConstant::kGTR100 - 1]) {
	      //if (gtr100y_cluster->PeakSum() < 10000) {
                continue;
              }

//           #ifndef EFFICIANCY_EVAL
//                if(gtr100y_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif
              cluster_set->gtr_clusters[0] = gtr100y_cluster;
              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100y_cluster->GlobalPosT(*geometry);
              if (IsYTrackCandidate(cluster_set)) {
                cluster_sets[1].emplace_back(*cluster_set);
              }
            }
            for (const auto& gtr100yb_cluster : gtr100yb_cluster_ptrs) {
              if (gtr100yb_cluster->PeakSum() < kGTRPeakSumThresholdY[E16ANA_StraightTrackConstant::kGTR100 - 1]) {
	      //if (gtr100yb_cluster->PeakSum() < 10000) {
                continue;
              }

//           #ifndef EFFICIANCY_EVAL
//                if(gtr100yb_cluster->PeakSum() > kGTRFakeADC ){
//                  continue;
//                }
//              #endif
              cluster_set->gtr_clusters[0] = gtr100yb_cluster;
              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100yb_cluster->GlobalPosT(*geometry);
              if (IsYTrackCandidate(cluster_set)) {
                cluster_sets[1].emplace_back(*cluster_set);
              }
            }
          }
        }
      }
    }
  }
  delete cluster_set;
  n_x_cands = cluster_sets[0].size();
  n_y_cands = cluster_sets[1].size();
E16INFO("number of x candidates: %d", n_x_cands);
E16INFO("number of y candidates: %d", n_y_cands);
  
if(n_x_cands > 500) return;
if(n_y_cands > 500) return;
  for (const auto& x_cand : cluster_sets[0]) {
    auto& stsx = *x_cand.sts_cluster;
    auto& gtrx = x_cand.gtr_clusters;
    std::array<int, kNumGTRLayers> x_module_ids = {gtrx[0]->ModuleId(), gtrx[1]->ModuleId(), gtrx[2]->ModuleId()};
    std::array<float, kNumGTRLayers> x_timings = {gtrx[0]->Timing4(), gtrx[1]->Timing4(), gtrx[2]->Timing4()};
    std::array<float, kNumGTRLayers> x_peak_sums = {gtrx[0]->PeakSum(), gtrx[1]->PeakSum(), gtrx[2]->PeakSum()};
    for (const auto& y_cand : cluster_sets[1]) {
      auto& gtry = y_cand.gtr_clusters;
      bool is_same_module = true;
      /*
      if ((gtry[0]->IsY() && gtrx[0]->LocalPosT().X() <= 0) || (gtry[0]->IsYb() && gtrx[0]->LocalPosT().X() >= 0)) {
        continue;
      }
      */
      for (int i = 0; i < kNumGTRLayers; ++i) {
        if (x_module_ids[i] != gtry[i]->ModuleId() || fabs(x_timings[i] - gtry[i]->Timing4()) > kGTRTimeDiffThreshold[i] ) { // ozawa v8
          is_same_module = false;
          break;
        }
      }
      if (!is_same_module) {
        continue;
      }
      track_candidates.emplace_back(E16ANA_StraightTrackCandidate(geometry));
      auto& tmp_cand = track_candidates.back();
      tmp_cand.SetTrackID(track_candidates.size() - 1);
//      tmp_cand.SetCharge(x_cand.charge);

		if(isWire){
        tmp_cand.SetInitX(targets_pos[x_cand.target_id].x());
        tmp_cand.SetInitY(targets_pos[x_cand.target_id].y());
        tmp_cand.SetInitZ(targets_pos[x_cand.target_id].z());
      }
      else {
			tmp_cand.SetInitX(targets_pos[x_cand.target_id].x());
			tmp_cand.SetInitY(targets_pos[x_cand.target_id].y());
			tmp_cand.SetInitZ(targets_pos[x_cand.target_id].z());
      }

      tmp_cand.SetDefaultSigma();
      tmp_cand.SetXChiSquare(x_cand.chi_square);
      tmp_cand.SetYChiSquare(y_cand.chi_square);
      for (int i = 0; i < kNumRoughFitDegree[0]; ++i) {
        tmp_cand.SetXCoef(i, x_cand.coefs[i]);
      }
      for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
        tmp_cand.SetYCoef(i, y_cand.coefs[i]);
      }
      auto& cluster_pairs = tmp_cand.ClusterPairs();
      cluster_pairs[0].Set(geometry, 0, stsx.ModuleId(), x_cand.global_poss[0], &stsx);//x only for ssd
      for (int i = 0; i < kNumGTRLayers; ++i) {
        cluster_pairs[1 + i].Set(geometry, 1 + i, gtrx[i]->ModuleId(), x_cand.global_poss[1 + i], y_cand.global_poss[1 + i], gtrx[i], gtry[i]);

	  int nhit = gtrx[i]->NumCls();
	  for(int j=0;j<nhit;j++){
	    cluster_pairs[1+i].SetCAdc1((double)gtrx[i]->CAdc1(j));
	    cluster_pairs[1+i].SetCPos((double)gtrx[i]->CPos(j));
	    cluster_pairs[1+i].SetCAdc2((double)gtrx[i]->CAdc2(j));
	    cluster_pairs[1+i].SetCAdc3((double)gtrx[i]->CAdc3(j));
	    cluster_pairs[1+i].SetCAdc4((double)gtrx[i]->CAdc4(j));
	    cluster_pairs[1+i].SetCTiming((double)gtrx[i]->CTiming(j));
	    cluster_pairs[1+i].SetCAdc5((double)gtrx[i]->CAdc5(j));
	  }

	  int nhit2 = gtrx[i]->NumCls2();
	  for(int j=0;j<nhit2;j++){
	    cluster_pairs[1+i].SetCTiming2((double)gtrx[i]->CTiming2(j));
	    cluster_pairs[1+i].SetCPos2((double)gtrx[i]->CPos2(j));
	  }
	  int nhit3 = gtrx[i]->NumCls3();
	  for(int j=0;j<nhit3;j++){
	    cluster_pairs[1+i].SetCTiming3((double)gtrx[i]->CTiming3(j));
	    cluster_pairs[1+i].SetCPos3((double)gtrx[i]->CPos3(j));
	  }

	  int nhit4 = gtrx[i]->NumCls4();
	  for(int j=0;j<nhit4;j++){
	    cluster_pairs[1+i].SetCTiming4((double)gtrx[i]->CTiming4(j));
	    cluster_pairs[1+i].SetCPos4((double)gtrx[i]->CPos4(j));
	    cluster_pairs[1+i].SetCTiming5((double)gtrx[i]->CTiming5(j));
	    cluster_pairs[1+i].SetCPos5((double)gtrx[i]->CPos5(j));
	  }
      }
    }
  }
}

void E16ANA_StraightTrackCandidates::Fit() {
  int i=0;
	for (auto& cand : track_candidates) {
   cand.Fit(fitter, vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag, isWire);
	i++;
  }
}



//void E16ANA_StraightTrackCandidates::AddTracksToRecord() {
//  auto& tracks = record->Tracks().Tracks();
//  tracks.resize(selected_track_candidates.size());
//  for (int track_index = 0; track_index < selected_track_candidates.size(); ++track_index) {
//    auto& cand = track_candidates[track_index];
//    auto& track = tracks[track_index];
//    for (int i = 0; i < E16ANA_StraightTrackConstant::kNumTargets; ++i) {
//      track.SetInitialPosAtTargetPlane(i, cand.PosAtTarget(i));
//      track.SetInitialMomAtTargetPlane(i, cand.MomAtTarget(i));
//    }
//    for (int i = 0; i < E16ANA_StraightTrackConstant::kNumDetectorLayers; ++i) {
//      auto& lpos = cand.LocalFitResult(i).local_pos;
//      auto& lmom = cand.LocalFitResult(i).local_mom;
//      track.SetHitPos(i, lpos);
//      track.SetHitMom(i, lmom);
//    }
////    for (int i = 0; i < E16ANA_StraightTrackConstant::kNumTrackingLayers; ++i) {
//    for (int i = 1; i < E16ANA_StraightTrackConstant::kNumTrackingLayers; ++i) {
//      for (int j = 0; j < 2; ++j) {
//        if (i == E16ANA_StraightTrackConstant::kSSD) {
//          if (j == 0) {
//            track.SetOriginalClusterPtr(2 * i + j, cand.ClusterPair(i).Cluster(j));
//          } else {
//            continue;
//          }
//        }
//        track.SetOriginalClusterPtr(2 * i + j - 1, cand.ClusterPair(i).Cluster(j));
//      }
//    }
//  }
//  return;
//}

void E16ANA_StraightTrackCandidates::AddTracksToRecord() {
  auto& tracks = record->Tracks().Tracks();
  tracks.resize(track_candidates.size());
  for (int track_index = 0; track_index < track_candidates.size(); ++track_index) {
    auto& cand = track_candidates[track_index];
    auto& track = tracks[track_index];
    for (int i = 0; i < E16ANA_StraightTrackConstant::kNumTargets; ++i) {
      track.SetInitialPosAtTargetPlane(i, cand.PosAtTarget(i));
      track.SetInitialMomAtTargetPlane(i, cand.MomAtTarget(i));
    }
    for (int i = 0; i < E16ANA_StraightTrackConstant::kNumDetectorLayers; ++i) {
      auto& lpos = cand.LocalFitResult(i).local_pos;
      auto& lmom = cand.LocalFitResult(i).local_mom;
      track.SetHitPos(i, lpos);
      track.SetHitMom(i, lmom);
    }
#ifndef NoExist_SSD
    for (int i = 0; i < E16ANA_StraightTrackConstant::kNumTrackingLayers; ++i) {
#else 
    for (int i = 1; i < E16ANA_StraightTrackConstant::kNumTrackingLayers; ++i) {
#endif
      for (int j = 0; j < 2; ++j) {
        if (i == E16ANA_StraightTrackConstant::kSSD) {
          if (j == 0) {
            track.SetOriginalClusterPtr(2 * i + j, cand.ClusterPair(i).Cluster(j));
          } else {
            continue;
          }
        }
        track.SetOriginalClusterPtr(2 * i + j - 1, cand.ClusterPair(i).Cluster(j));
      }
    }
		track.SetLGHitPtrs(cand.ProjectedLGHits());
		track.SetLGClusterPtrs(cand.ProjectedLGClusters());
  }
  return;
}


void E16ANA_StraightTrackCandidates::SearchLGHits() {
	auto &lg = record->LG();
	for( auto& cand : track_candidates) {
		if(cand.ChiSquare() >= 1.1e10){
			cand.SetIsSearchAssociatedHits(false);
			continue;
		}
		if (cand.ChiSquare() >= kMaxChi2ForSearchAssociatedHits){
			cand.SetIsSearchAssociatedHits(false);
			continue;
		}
		cand.SetIsSearchAssociatedHits(true);
		auto& fit_results  = cand.LocalFitResults();
		for( int l = E16ANA_StraightTrackConstant::kHBD; l < E16ANA_TrackConstant::kNumDetectorLayers; ++l){
			auto &fit_pos = fit_results[l].global_pos;
		   int  fit_module_id = fit_results[l].module_id;
			if(l == E16ANA_StraightTrackConstant::kHBD){
				//HBD space 
			}
			else {//LG
				auto &hits = lg.HitPtrs(fit_module_id, 0, 0 );
				auto &clusters = lg.ClusterPtrs(fit_module_id, 0, 0);
				for(auto &hit :  hits){
					int lgh = hit->ChannelId() /10;
   	      if (l == E16ANA_TrackConstant::kLG0) {
      	   	if (lgh != 0 && lgh != 5) {
         	      continue;
            }
  	 	     } else if (l == E16ANA_TrackConstant::kLG1) {
      	   	if (lgh != 1 && lgh != 4) {
         	      continue;
            	}
 	        } else {
   	         if (lgh != 2 && lgh != 3) {
      	      	continue;
         	   }
 	        }
			TVector3 lg = hit->GlobalPos(*geometry);
//			std::cout << "lg  hit = (" << lg.x() << ", " << lg.y() << ", " << lg.z() << std::endl;
//			std::cout << "fit hit = (" << fit_pos.x() << ", " << fit_pos.y() << ", " << fit_pos.z() << std::endl;
//			std::cout << "residual = " << (hit->GlobalPos(*geometry)  - fit_pos).Mag() << std::endl;
				if((hit->GlobalPos(*geometry) - fit_pos).Mag() < kLGProjectionThreshold){
					cand.ProjectedLGHits().emplace_back(hit);
//					cand.SetLGResidualMag((hit->GlobalPos(*geometry) - fit_pos).Mag());
				}
			}
//		for(auto &cluster : clusters){//seems no meaning because analysis is based on hits info
//			TVector3 lg = cluster->GlobalPos(*geometry);
////			std::cout << "lg  hit = (" << lg.x() << ", " << lg.y() << ", " << lg.z() << std::endl;
////			std::cout << "fit hit = (" << fit_pos.x() << ", " << fit_pos.y() << ", " << fit_pos.z() << std::endl;
////			std::cout << "residual = " << (cluster->GlobalPos(*geometry)  - fit_pos).Mag() << std::endl;
//			if((cluster->GlobalPos(*geometry) - fit_pos).Mag() < kLGProjectionThreshold){
//				cand.ProjectedLGClusters().emplace_back(cluster);
//			}
//		}
		}
		}
	}
	return;
}


void E16ANA_StraightTrackCandidates::ProjectionTarget() {
	Hep3Vector cross_pos;
	Hep3Vector cross_mom;
	for(auto & cand : track_candidates){
		auto& pos = cand.PosAtTargets();
		auto& mom = cand.MomAtTargets();
	   if (cand.ChiSquare() > 1.0e9) {
			for(int i=0; i < targets_pos.size() ; i++){
				pos[i] = E16DST_DST1Constant::kInvalidVector;
				mom[i] = E16DST_DST1Constant::kInvalidVector;
			}
			continue;
		}
	   auto t_init_pos = cand.FitInitPos();
   	auto t_init_mom = cand.FitInitMom();
	   Hep3Vector init_pos(t_init_pos(0) * 0.1, t_init_pos(1) * 0.1, t_init_pos(2) * 0.1);
		Hep3Vector init_mom(t_init_mom(0),       t_init_mom(1),       t_init_mom(2));
		E16ANA_StraightStepTrack step_track(init_pos, init_mom, cand.Charge(), kStepTrackStepSizeCm, kStepTrackArraySize);
		for (int i = 0; i < targets_pos.size() ; ++i) {
			if (step_track.CrossZconstPlane(E16ANA_TrackConstant::kTargetZ[i] * 0.1, cross_pos, cross_mom) == -1) {
				pos[i] = E16DST_DST1Constant::kInvalidVector;
				mom[i] = E16DST_DST1Constant::kInvalidVector;
			 } else {
				pos[i].SetXYZ(cross_pos.x() * 10., cross_pos.y() * 10., cross_pos.z() * 10.);
				mom[i].SetXYZ(cross_mom.x() , cross_mom.y() , cross_mom.z());
			}
		}
 	}
	return;
}


double  E16ANA_StraightTrackCandidates::SearchVertex(TrackPair *track_pair) {
	auto& cand0 = track_pair->cand_minus;
	auto& cand1 = track_pair->cand_plus;
   auto t_init_pos0 = cand0->FitInitPos();
	auto t_init_mom0 = cand0->FitInitMom();
   auto t_init_pos1 = cand1->FitInitPos();
	auto t_init_mom1 = cand1->FitInitMom();
   Hep3Vector init_pos0 (t_init_pos0(0) * 0.1, t_init_pos0(1) * 0.1, t_init_pos0(2) * 0.1);
   Hep3Vector init_mom0 (t_init_mom0(0)      , t_init_mom0(1)      , t_init_mom0(2));
   Hep3Vector init_pos1 (t_init_pos1(0) * 0.1, t_init_pos1(1) * 0.1, t_init_pos1(2) * 0.1);
   Hep3Vector init_mom1 (t_init_mom1(0)      , t_init_mom1(1)      , t_init_mom1(2));
   E16ANA_StraightStepTrack step_track0( init_pos0, init_mom0, -1, kStepTrackStepSizeCm, kStepTrackArraySize);
   E16ANA_StraightStepTrack step_track1( init_pos1, init_mom1,  1, kStepTrackStepSizeCm, kStepTrackArraySize);
   double distance;
	Hep3Vector cross_point;
	Hep3Vector mom0;
	Hep3Vector mom1;
	auto flag = step_track0.Cross(step_track1, &distance, &cross_point, &mom0, &mom1);
	track_pair->vtx = {cross_point.x() * 10., cross_point.y() * 10., cross_point.z() * 10.};
   track_pair->distance = distance * 10.;
   track_pair->mom_minus = {mom0.x(), mom0.y(), mom0.z()};
   track_pair->mom_plus  = {mom1.x(), mom1.y(), mom1.z()};
   return distance * 10;
}


void E16ANA_StraightTrackCandidates::AddTracks(TrackPair *track_pair, double tgt_z){
	pair_fitter->Clear();
	std::array<E16ANA_StraightTrackCandidate*, 2> cands = {track_pair->cand_minus, track_pair->cand_plus};
	pair_fitter->SetInitialVertex(TVector3(0., 0., tgt_z), kVertexSigma);
	pair_fitter->SetInitialMomentum(0, track_pair->mom_minus);
	pair_fitter->SetInitialMomentum(1, track_pair->mom_plus);
	for (int track_index = 0; track_index < cands.size(); ++track_index) {
		for (int layer_index = 0; layer_index < E16ANA_TrackConstant::kNumTrackingLayers; ++layer_index) {
			#ifdef NoExist_SSD
			if(layer_index == 0) continue;
			#endif
			auto& cluster_pair = cands[track_index]->ClusterPair(layer_index);
			auto module_id  = cluster_pair.ModuleID();
 			auto local_pos  = cluster_pair.LocalPos(); 
 			auto local_posT = cluster_pair.LocalPosT(); 
 			if (layer_index == E16ANA_TrackConstant::kSSD) {
				pair_fitter->AddHit(track_index, layer_index, geometry->SSD(E16ANA_TrackConstant::ModuleID2020To2013(module_id)), local_pos, kSigmas[layer_index]);
		   } else {
			pair_fitter->AddHit(track_index, layer_index, geometry->GTR(E16ANA_TrackConstant::ModuleID2020To2013(module_id), layer_index - 1), local_posT, kSigmas[layer_index]);
			}
		}
	}
	return;
}


void E16ANA_StraightTrackCandidates::PairTracking(TrackPair *track_pair, double tgt_z) {
	AddTracks(track_pair, tgt_z);
	pair_fitter->SetRungeKuttaStepSize(kPairTrackingStepSize);
	pair_fitter->SetMaxSteps(kPairTrackingMaxSteps);
	track_pair->chi_square_refit = pair_fitter->Fit(vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag, kPairMinuitStrategy, kPairMinuitMaxFunctionCalls);
   UpdateFitResult(track_pair);
	return;
}

void E16ANA_StraightTrackCandidates::UpdateFitResult(TrackPair* track_pair) {
	track_pair->vtx_refit = pair_fitter->GetFitVertex();
	track_pair->mom_minus_refit = pair_fitter->GetFitMomentum(0);
	track_pair->mom_plus_refit = pair_fitter->GetFitMomentum(1);
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



void E16ANA_StraightTrackCandidates::AnalyzeTrackPairs() {
	track_pairs.clear();
	TrackPair track_pair;
	int n_cands = track_candidates.size();
	for(int cand_index0 = 0; cand_index0 < n_cands; ++cand_index0){
		auto cand0  = track_candidates[cand_index0];
      auto tgt_z0 = cand0.InitPos().X();
 		for(int cand_index1 = cand_index0; cand_index1 < n_cands; ++cand_index1){
			auto cand1 = track_candidates[cand_index1];
   	   auto tgt_z1 = cand1.InitPos().X();
			if(tgt_z0 != tgt_z1){
				continue;
			}
			track_pair.Clear();
			track_pair.cand_minus = &cand0;
			track_pair.cand_plus  = &cand1;
			SearchVertex(&track_pair);
	      PairTracking(&track_pair, tgt_z0);	
   	   track_pairs.emplace_back(track_pair);
		}
	}
	SelectTrackPairs();
	return;
}

void E16ANA_StraightTrackCandidates::SelectTracks() {
	std::array<std::vector<E16DST_DST1Cluster*>, E16ANA_StraightTrackConstant::kNumTrackingLayers> used_clusters;
	for( auto& clsts : used_clusters){
		clsts.clear();
	}
	std::sort(track_candidates.begin(), track_candidates.end(), [](auto& lhs, auto& rhs){
		return lhs.ChiSquare() < rhs.ChiSquare();
	});
	for( auto &cand : track_candidates) {
		cand.SetIsSelected(false);
		if( cand.ChiSquare() > 1.0e9) {
			break;
		}
		if (cand.MinimizeStatus() == 0) {
			continue;
		}
//		if (cand.ProjectedHBDClusters().size() == 0){
//			continue;
//		}
		if(cand.ProjectedLGHits().size() == 0) {
			continue;
		}
		bool is_large_residual = false;
		for(int i=0; i < targets_pos.size(); i++){
			auto &res = cand.LocalFitResult(i).residual_pos;
			#ifdef NoExist_SSD
			if(i == 0 ) continue;
			#endif
			if(fabs(res.X()) > kResidualThresholdX[i]) {
				is_large_residual = true;
				break;
			}
			if ( i!= E16DST_DST1Constant::kSSD && fabs(res.Y()) > kResidualThresholdY[i]){
				is_large_residual = true;
				break;
			}
		}	
		cand.SetIsLargeResidual(is_large_residual);
		if (is_large_residual) {
			continue;
		}
		bool is_near_target = false;
		for(auto& pos : cand.PosAtTargets()) {
			double mag2 = pos.X() * pos.X() + pos.Y() * pos.Y();
			if( mag2 < kNearTargetThreshold){
				is_near_target = true;
				break;
			}
		}
		cand.SetIsNearTarget(is_near_target);
		if(!is_near_target){
			continue;
		}
		bool is_used = false;
		for( int l=0; l < E16ANA_StraightTrackConstant::kNumTrackingLayers; l++){
			int n_types = 2;
			if(l == E16DST_DST1Constant::kSSD){
				n_types = 1;
			}
			for (int type = 0; type < n_types; type++){
				auto cluster = cand.ClusterPair(l).Cluster(type);
				for( const auto &clst : used_clusters[l]) {
					if (cluster == clst) {
						is_used = true;
						break;
					}
				}
				if(is_used) {
					break;
				}
				used_clusters[l].emplace_back(cluster);
			}
			if(is_used) {
				break;
			}
		}
		cand.SetIsClusterUsed(is_used);
		if(is_used) {
			continue;
		}	
		cand.SetIsSelected(true);
		selected_track_candidates.emplace_back(&cand);
	}
	return;
}

void E16ANA_StraightTrackCandidates::SelectTrackPairs(){
	selected_track_pairs.clear();
	std::vector<E16ANA_StraightTrackCandidate*> used_minus_cands;
	std::vector<E16ANA_StraightTrackCandidate*> used_plus_cands;
	std::sort(track_pairs.begin(), track_pairs.end(), [](auto& lhs, auto& rhs) {
		return lhs.chi_square_refit < rhs.chi_square_refit;
	});
	for(auto &pair : track_pairs){
		bool is_used = false;
		for(auto &used_cand : used_minus_cands) {
			if(used_cand == pair.cand_minus){
				is_used = true;
				break;
			}
		}
		if(!is_used) {
			for(auto &used_cand : used_plus_cands){
				if(used_cand = pair.cand_plus){
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
		used_minus_cands.emplace_back(pair.cand_minus);
		used_plus_cands.emplace_back(pair.cand_plus);
	}
	return;
}

void E16ANA_StraightTrackCandidates::Analyze() {
  track_candidates.clear();
  selected_track_candidates.clear();
#ifdef NoExist_SSD
  SearchTrackCandidatesWoSSD();
#else 
  #ifdef UseSTS
  SearchTrackCandidatesUsingSTS();
  #else 
  SearchTrackCandidates();
  #endif
#endif
  E16INFO("number of track candidate: %d", track_candidates.size());
  Fit();
//  ProjectionTarget();
  SearchLGHits();//230826 add
//  SelectTracks();
  if(kExecutePairFit){
    AnalyzeTrackPairs();
  }
  AddTracksToRecord();
  return;
}

void E16ANA_StraightTrackCandidates::PrintParam() {
  std::cout << "GTR Time Difference Threshold :" << std::endl;
  std::cout << "  GTR100 : " << kGTRTimeDiffThreshold[0] << ", GTR200 : " << kGTRTimeDiffThreshold[1] << ", GTR300 : " << kGTRTimeDiffThreshold[2] << std::endl;
  std::cout << "Sigma at X Rough Fit :" << std::endl;
  std::cout << "  Target : " << kXSigmaIncTgt[0] << ", SSD : " << kXSigmaIncTgt[1] << ", GTR100 : " << kXSigmaIncTgt[2] << ", GTR200 : " << kXSigmaIncTgt[3] << ", GTR300 : " << kXSigmaIncTgt[4] << std::endl;
  std::cout << "Sigma at Y Rough Fit :" << std::endl;
  std::cout << "  GTR100 : " << kYSigma[0] << ", GTR200 : " << kYSigma[2] << ", GTR300 : " << kYSigma[2] << std::endl;
  std::cout << "Minimum Hits in X Cluster : " << kMinHitsInXCluster << std::endl;
  std::cout << "GTR Position Difference Threshold between Layers at Y Candidate Search : " << kGTRYDiffThreshold << std::endl;
  std::cout << "GTR X ADC Peak Sum Threshold :" << std::endl;
  std::cout << "  GTR100 : " << kGTRPeakSumThresholdX[0] << ", GTR200 : " << kGTRPeakSumThresholdX[1] << ", GTR300 : " << kGTRPeakSumThresholdX[2] << std::endl;
  std::cout << "GTR Y ADC Peak Sum Threshold : " << kGTRPeakSumThresholdY[0] << ", " << kGTRPeakSumThresholdY[1] << ", " << kGTRPeakSumThresholdY[2] << std::endl;
  std::cout << "Rough Fit Chi Square Threshold :" << std::endl;
  std::cout << "  X : " << kRoughFitChiSquareThreshold[0] << ", Y : " << kRoughFitChiSquareThreshold[1] << std::endl;
  std::cout << "X Rough Fit Coefficient Threshold : " 
            << kRoughXFitCoefficientThreshold[0] << ", " << kRoughXFitCoefficientThreshold[1] << kRoughXFitCoefficientThreshold[2] << std::endl;
  std::cout << "Y Rough Fit Coefficient Threshold : " << kRoughYFitCoefficientThreshold[0] << ", " << kRoughYFitCoefficientThreshold[1] << std::endl;
  std::cout << "HBD Projection Threshold : " << kHBDProjectionThreshold << std::endl;
  std::cout << "LG  Projection Threshold : " << kLGProjectionThreshold << std::endl;
  std::cout << "Near Target Threshold : " << kNearTargetThreshold << std::endl;
  std::cout << "E16ANA_StraightStepTrack Step Size [cm] : " << kStepTrackStepSizeCm << std::endl;
  std::cout << "E16ANA_StraightStepTrack Array Size : " << kStepTrackArraySize << std::endl;
}
