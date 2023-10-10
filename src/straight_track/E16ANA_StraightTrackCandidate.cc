#include "E16ANA_StraightTrackCandidate.hh"
#include "E16ANA_StraightTrackConstant.hh"

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

void E16ANA_StraightTrackCandidate::AddTrackHit(E16ANA_StraightMultiTrack* single_track, bool isWire, int removed_layer) {
  for (auto& fit_result : fit_results) {
    fit_result.set_flag = 0;
  }
//  if (!CalcRoughMomentum()) {
  if (!CalcRoughMomentumV2()) {
    std::cerr << "Cannot calculate rough momentum" << std::endl;
  }
  int tid = 0; // only 1 track is fitted by the fitter
  single_track->Clear();
  if(isWire){//wire
      single_track->SetInitialVertex(TVector3(init_pos.X(), init_pos.Y(), init_pos.Z()), kInitPosErrorWire); 
  }
  else{//target
    if(removed_layer ==0){//without ssd, gtr100 is init pos
      single_track->SetInitialVertex(TVector3(init_pos.X(), init_pos.Y(), init_pos.Z()), kInitPosError100); 
    }
    else {//SSD is init pos 
      single_track->SetInitialVertex(TVector3(init_pos.X(), init_pos.Y(), init_pos.Z()), kInitPosErrorSSD); 
    }
    
  }
//  single_track->SetInitialVertex(TVector3(init_pos.X(), 0., init_pos.Z()), TVector3(0.4, 0., 0)); // for Ks
  single_track->SetInitialMomentum(tid, init_mom);
//  single_track->SetCharge(tid, charge);
  for (int l = 0; l < E16ANA_StraightTrackConstant::kNumTrackingLayers; ++l) {
    if (l == removed_layer) continue;
    auto& c = cluster_pairs[l];
    if (l == E16ANA_StraightTrackConstant::kSSD) {
      single_track->AddHit(tid, c.LayerOrder(), geometry->SSD(E16ANA_StraightTrackConstant::ModuleID2020To2013(c.ModuleID())), c.LocalPos(), sigma[l]);
    } else {
      single_track->AddHit(tid, c.LayerOrder(), geometry->GTR(E16ANA_StraightTrackConstant::ModuleID2020To2013(c.ModuleID()), c.LayerOrder() - 1), c.LocalPos(), sigma[l]);
    }
  }
}

void E16ANA_StraightTrackCandidate::UpdateFitResult(E16ANA_StraightMultiTrack* fitter, int removed_layer) {
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
//  int l_st = 0;//all layer
//  if(removed_layer == 0 ) l_st = 1;//without ssd
  for (int l = 0; l < E16ANA_StraightTrackConstant::kNumTrackingLayers; ++l) {
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
      gpos = geometry->SSD(mid[hid])->GetGPos(lpos[hid]);
      gmom = geometry->SSD(mid[hid])->GetGMom(lmom[hid]);
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


double E16ANA_StraightTrackCandidate::Fit(E16ANA_StraightMultiTrack* fitter, bool vertex_xy_fix_flag, bool py_fix_flag, bool vertex_z_fix_flag,bool isWire, int removed_layer) {
  fitter->Clear();
  this->AddTrackHit(fitter, isWire,  removed_layer);
  fitter->SetRungeKuttaStepSize(15.0);
  fitter->SetMaxSteps(kTrackingMaxSteps);
  chisq = fitter->Fit(vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag, kMinuitStrategy, kMinuitMaxFunctionCalls);
  UpdateFitResult(fitter,removed_layer);
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

bool E16ANA_StraightTrackCandidates::IsXTrackCandidate(OneAxisClusterSet* cluster_set, int in_mid) {
  auto& pos_set = cluster_set->global_poss;
  int mid       = in_mid -100;
  std::vector<TVector2> targets; targets.clear(); for(int i=0; i < targets_pos.size();i++){ targets.push_back(TVector2(targets_pos[i].x(), targets_pos[i].z()));
  }
//  if(isWire){
//     targets.push_back(TVector2(20, 40));//minus wire
//     targets.push_back(TVector2(20, -40));//do not exchange the turn of p/m
//  }
//  else {
//     targets.push_back(TVector2(0, -20));
//     targets.push_back(TVector2(0, 0));
//     targets.push_back(TVector2(0, 20)); 
//  }
//detector pos
  std::vector<TVector2> positions;
  positions.clear();
  for(int i=0; i <E16ANA_StraightTrackConstant::kNumTrackingLayers;i++){
      if(i == removed_layer) continue;
      positions.push_back(TVector2(pos_set[i].X(), pos_set[i].Z()));//
  } 
//Rotating targets
  std::vector<TVector2> rtargets;
  rtargets.clear();
  for(int i=0; i < targets.size(); i++){
     rtargets.push_back(targets[i].Rotate(Agtr[mid]*cpi/180));
  }
//Rotating Detector Hits
  std::vector<TVector2> rpositions;
  rpositions.clear();
  for(int i=0; i < positions.size(); i++){
    rpositions.push_back(positions[i].Rotate(Agtr[mid]*cpi/180)); 
  }

  if(isWire){
     if(removed_layer == -1){//with all detectors, Wire
  	  double rlx1[]={rtargets[0].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X(),rpositions[3].X()};//wire0_x
	    double rlz1[]={rtargets[0].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y(),rpositions[3].Y()};//wire0_y
   	  double rlx2[]={rtargets[1].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X(),rpositions[3].X()};//wire1_x
  	  double rlz2[]={rtargets[1].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y(),rpositions[3].Y()};//wire1_y
//      double err[]={kXSigma[0],kXSigma[1],kXSigma[2],kXSigma[3],kXSigma[4]};//with all
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
       for(int i=1; i < 5; i++){//i==0 is corresponding to wire
         if(i - 1 == removed_layer) continue;
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
      int		 min_i = std::distance(std::begin(chi_cand), min_t);
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
  }//Wire Case
  else {//Three Targets Case
    if(removed_layer == -1){//All layers and three targets
      double rlx1[]={rtargets[0].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X(), rpositions[3].X()};
  	  double rlz1[]={rtargets[0].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y(), rpositions[3].Y()};
  	  double rlx2[]={rtargets[1].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X(), rpositions[3].X()};
    	double rlz2[]={rtargets[1].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y(), rpositions[3].Y()};
  	  double rlx3[]={rtargets[2].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X(), rpositions[3].X()};
    	double rlz3[]={rtargets[2].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y(), rpositions[3].Y()};
      double err[]={kXSigma[0],kXSigma[1], kXSigma[2],kXSigma[3],kXSigma[4]};//with SSD
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
//       cluster_set->charge = -1;
//        if(chi2<chi1)  cluster_set->charge = 1;
          cluster_set->chi_square = chi_cand[min_i];
       	  cluster_set->target_id  = min_i;
    	    cluster_set->coefs[0]   = ras[min_i]; 
    	    cluster_set->coefs[1]   = rbs[min_i]; 
          return true;
        }
        return false;
      }//three targets and All layers
      else {//Three Targets and without one layer
  	    double rlx1[]={rtargets[0].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X()};
    	  double rlz1[]={rtargets[0].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y()};
    	  double rlx2[]={rtargets[1].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X()};
  	    double rlz2[]={rtargets[1].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y()};
    	  double rlx3[]={rtargets[2].X(),rpositions[0].X(),rpositions[1].X(),rpositions[2].X()};
    	  double rlz3[]={rtargets[2].Y(),rpositions[0].Y(),rpositions[1].Y(),rpositions[2].Y()};
        std::vector<double> sigmas;
        sigmas.clear();
        for(int i=0; i < E16ANA_StraightTrackConstant::kNumTrackingLayers; i++){
          if(i == removed_layer) continue;
          sigmas.push_back(kXSigma[i]);
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
//          cluster_set->charge = -1;
//          if(chi2<chi1)  cluster_set->charge = 1;
            cluster_set->chi_square = chi_cand[min_i];
          	cluster_set->target_id  = min_i;
         	  cluster_set->coefs[0]   = ras[min_i]; 
	          cluster_set->coefs[1]   = rbs[min_i]; 
            return true;
          }
        return false;
        }
    }
}



////bool E16ANA_StraightTrackCandidates::IsXTrackCandidate(OneAxisClusterSet* cluster_set, int in_mid) {
//  auto& pos_set = cluster_set->global_poss;
//  int mid       = in_mid -100;
//  TVector2 trod1(0, -20);
//  TVector2 trod2(0, 0);
//  TVector2 trod3(0, 20);
//  TVector2 ggt1(pos_set[1].X(),pos_set[1].Z());
//  TVector2 ggt2(pos_set[2].X(),pos_set[2].Z());
//  TVector2 ggt3(pos_set[3].X(),pos_set[3].Z());
//
//  TVector2  rod1 = trod1.Rotate(Agtr[mid]*cpi/180);
//  TVector2  rod2 = trod2.Rotate(Agtr[mid]*cpi/180);
//  TVector2  rod3 = trod3.Rotate(Agtr[mid]*cpi/180);
//  TVector2  lgt1 = ggt1.Rotate(Agtr[mid]*cpi/180);
//  TVector2  lgt2 = ggt2.Rotate(Agtr[mid]*cpi/180);
//  TVector2  lgt3 = ggt3.Rotate(Agtr[mid]*cpi/180);
//  if(removed_layer != 0){//with SSD
//     TVector2  lssd = gssd.Rotate(Agtr[mid]*cpi/180);
//   double rlx1[]={rod1.X(),lgt1.X(),lgt2.X(),lgt3.X()};
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
////  double err[]={kXSigma[0],kXSigma[1],kXSigma[2],kXSigma[3]};
//  double err[]={kXSigma[0],kXSigma[2],kXSigma[3],kXSigma[4]};//wo SSD
//
////  std::cout << "lgt1x = "  << lgt1.X() << ", " << lgt1.Y() << ", " << std::endl;
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
//    chi1 += pow((rlx1[i]-(rb1*rlz1[i]+ra1))/err[i],2);
//    chi2 += pow((rlx2[i]-(rb2*rlz2[i]+ra2))/err[i],2);
//    chi3 += pow((rlx3[i]-(rb3*rlz3[i]+ra3))/err[i],2);
//  }
//
//  double ras[E16ANA_StraightTrackConstant::kNumTargets]     = {ra1, ra2, ra3}; 
//  double rbs[E16ANA_StraightTrackConstant::kNumTargets]     = {rb1, rb2, rb3}; 
//  double chi_cand[E16ANA_StraightTrackConstant::kNumTargets] = {chi1, chi2, chi3};
//  auto   min_t = std::min_element(std::begin(chi_cand), std::end(chi_cand));
//  int		min_i = std::distance(std::begin(chi_cand), min_t);
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
//  }//with SSD
//}
//  else {
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
////  double err[]={kXSigma[0],kXSigma[1],kXSigma[2],kXSigma[3]};
//  double err[]={kXSigma[0],kXSigma[2],kXSigma[3],kXSigma[4]};//wo SSD
//
////  std::cout << "lgt1x = "  << lgt1.X() << ", " << lgt1.Y() << ", " << std::endl;
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
//    chi1 += pow((rlx1[i]-(rb1*rlz1[i]+ra1))/err[i],2);
//    chi2 += pow((rlx2[i]-(rb2*rlz2[i]+ra2))/err[i],2);
//    chi3 += pow((rlx3[i]-(rb3*rlz3[i]+ra3))/err[i],2);
//  }
//
//  double ras[E16ANA_StraightTrackConstant::kNumTargets]     = {ra1, ra2, ra3}; 
//  double rbs[E16ANA_StraightTrackConstant::kNumTargets]     = {rb1, rb2, rb3}; 
//  double chi_cand[E16ANA_StraightTrackConstant::kNumTargets] = {chi1, chi2, chi3};
//  auto   min_t = std::min_element(std::begin(chi_cand), std::end(chi_cand));
//  int		min_i = std::distance(std::begin(chi_cand), min_t);
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
//  }
//}
//
//

bool E16ANA_StraightTrackCandidates::IsYTrackCandidate(OneAxisClusterSet* cluster_set) {
  auto& pos_set = cluster_set->global_poss;
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

  double r2 = 0.;
  double r  = 0.;
  double c  = 0.;
  double ry = 0.;
  double y  = 0.;
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
    fit_y[i] = coef[0] + coef[1] * gtr_r[i];//a + bx 
    chi2_cand += kYWeight[i] * (fit_y[i] - gtr_y[i]) * (fit_y[i] - gtr_y[i]);
  }
  if (chi2_cand < kRoughFitChiSquareThreshold[1] && fabs(coef[0]) < kRoughYFitCoefficientThreshold[0]) {
    cluster_set->xy = coef[0];
    cluster_set->chi_square = chi2_cand;
    for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
      cluster_set->coefs[i] = coef[i];
    }
    return true;
  }
#ifdef TRACK_EFF_CHECK
  for (int i = 0; i < 2; ++i) {
    if (is_sim_ycluster[i][0] && is_sim_ycluster[i][1] && is_sim_ycluster[i][2]) {
      if (chi2_cand < kRoughFitChiSquareThreshold[1]) {
        y_reject_point[i] += Pow2(kRejYChi2);
      }
      if (fabs(coef[0]) < kRoughYFitCoefficientThreshold[0]) {
        y_reject_point[i] += Pow2(kRejYCoef0);
      }
    }
  }
#endif
//cout << "y chi2 bad" << endl;
  return false;
}


//bool E16ANA_StraightTrackCandidates::IsYTrackCandidate(OneAxisClusterSet* cluster_set) {
//  auto& pos_set = cluster_set->global_poss;
//  std::array<double, kNumGTRLayers> gtr_y({pos_set[1].Y(), pos_set[2].Y(), pos_set[3].Y()});
//  std::array<double, kNumGTRLayers> gtr_r({sqrt(pow(pos_set[1].X()-20,2) +pow(pos_set[1].Z()+40,2)),
//	sqrt(pow(pos_set[2].X()-20,2) +pow(pos_set[2].Z()+40,2)),
//	sqrt(pow(pos_set[3].X()-20,2) +pow(pos_set[3].Z()+40,2))});
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
//  std::array<double, kNumRoughFitDegree[1]> coef({(r2 * y  - r * ry) / (c * r2 - r * r),
//                                                  (c  * ry - r * y)  / (c * r2 - r * r)});
//  double chi2_cand = 0.;
//  std::array<double, kNumGTRLayers> fit_y;
//  for (int i = 0; i < kNumGTRLayers; ++i) {
//    fit_y[i] = coef[0] + coef[1] * gtr_r[i];
//    chi2_cand += kYWeight[i] * (fit_y[i] - gtr_y[i]) * (fit_y[i] - gtr_y[i]);
//  }
//  if (chi2_cand < kRoughFitChiSquareThreshold[1] && fabs(coef[0]) < kRoughYFitCoefficientThreshold[0]) {
//    cluster_set->xy = coef[0];
//    cluster_set->chi_square = chi2_cand;
//    for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
//      cluster_set->coefs[i] = coef[i];
//    }
//    return true;
//  }else{
//    std::array<double, kNumGTRLayers> gtr_r2({sqrt(pow(pos_set[1].X()-20,2) +pow(pos_set[1].Z()-40,2)),
//	  sqrt(pow(pos_set[2].X()-20,2) +pow(pos_set[2].Z()-40,2)),
//	  sqrt(pow(pos_set[3].X()-20,2) +pow(pos_set[3].Z()-40,2))});
//      
//    double dr2 = 0.;
//    double dr  = 0.;
//    double dc  = 0.;
//    double dry = 0.;
//    double dy  = 0.;
//    for (int i = 0; i < kNumGTRLayers; ++i) {
//      dr2 += kYWeight[i] * gtr_r2[i] * gtr_r2[i];
//      dr  += kYWeight[i] * gtr_r2[i];
//      dc  += kYWeight[i];
//      dry += kYWeight[i] * gtr_r2[i] * gtr_y[i];
//      dy  += kYWeight[i] * gtr_y[i];
//    }
//    std::array<double, kNumRoughFitDegree[1]> dcoef({(dr2 * dy  - dr * dry) / (dc * dr2 - dr * dr),
//	  (dc  * dry - dr * dy)  / (dc * dr2 - dr * dr)});
//    double dchi2_cand = 0.;
//    std::array<double, kNumGTRLayers> dfit_y;
//
//    for (int i = 0; i < kNumGTRLayers; ++i) {
//      dfit_y[i] = dcoef[0] + dcoef[1] * gtr_r2[i];
//      dchi2_cand += kYWeight[i] * (dfit_y[i] - gtr_y[i]) * (dfit_y[i] - gtr_y[i]);
//    }
//    if (dchi2_cand < kRoughFitChiSquareThreshold[1] && fabs(dcoef[0]) < kRoughYFitCoefficientThreshold[0]) {
//      cluster_set->xy = dcoef[0];
//      cluster_set->chi_square = dchi2_cand;
//      for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
//	cluster_set->coefs[i] = dcoef[i];
//      }
//      return true;
//    }
//  }
//  return false;
//}

double E16ANA_StraightTrackCandidates::GTRTimeDiffThreshold(int n) { return kGTRTimeDiffThreshold[n]; }
double E16ANA_StraightTrackCandidates::XSigma(int n) { return kXSigma[n]; }
double E16ANA_StraightTrackCandidates::XWeight(int n) { return kXWeight[n]; }
double E16ANA_StraightTrackCandidates::YSigma(int n) { return kYSigma[n]; }
double E16ANA_StraightTrackCandidates::YWeight(int n) { return kYWeight[n]; }
int E16ANA_StraightTrackCandidates::MinHitsInXCluster() { return kMinHitsInXCluster; }
double E16ANA_StraightTrackCandidates::GTRYDiffThreshold() { return kGTRYDiffThreshold; }
double E16ANA_StraightTrackCandidates::GTRPeakSumThresholdX(int n) { return kGTRPeakSumThresholdX[n]; }
double E16ANA_StraightTrackCandidates::GTRPeakSumThresholdY() { return kGTRPeakSumThresholdY; }
double E16ANA_StraightTrackCandidates::RoughFitChiSquareThreshold(int n) { return kRoughFitChiSquareThreshold[n]; }
double E16ANA_StraightTrackCandidates::RoughXFitCoefficientThreshold(int n) { return kRoughXFitCoefficientThreshold[n]; }
double E16ANA_StraightTrackCandidates::RoughYFitCoefficientThreshold(int n) { return kRoughYFitCoefficientThreshold[n]; }

//void E16ANA_StraightTrackCandidates::SearchTrackCandidatesWoSSD() {
//  track_candidates.clear();
//  track_candidates.reserve(kNumReserveTracks[2]); // tmp
//  auto& gtr = record->GTR();
////E16INFO("number of GTR clusters: %d", gtr.NumClusters());
////  if(gtr.NumClusters() > 5000) return;
//  std::array<std::vector<OneAxisClusterSet>, 2> cluster_sets;
//  cluster_sets[0].reserve(kNumReserveTracks[0]);
//  cluster_sets[1].reserve(kNumReserveTracks[1]);
//  auto cluster_set = new OneAxisClusterSet();
//
//    for (const auto& gtr100_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
//		auto is_l = IsLModule(gtr100_module_id);
//      auto& gtr100x_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsX);
//      for (const auto& gtr200_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
////        if (is_l != IsLModule(gtr200_module_id)) {
//      if (abs(gtr200_module_id - gtr100_module_id) > 1) {
//          continue;
//        }
//        auto& gtr200x_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsX);
//        for (const auto& gtr300_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
//       //   if (is_l != IsLModule(gtr300_module_id)) {
//	      if (abs(gtr300_module_id - gtr100_module_id) > 1) {
//            continue;
//          }
//          auto& gtr300x_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsX);
//
//            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
//              if (gtr100x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR100 - 1]) {
//                continue;
//              }
//              if (gtr100x_cluster->NumHits() < kMinHitsInXCluster) {
//                continue;
//              }
//              cluster_set->gtr_clusters[0] = gtr100x_cluster;
//              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100x_cluster->GlobalPosT(*geometry);
//	      TVector3 testg = gtr100x_cluster->GlobalPos(*geometry);
//
//	      //printf("x:%f,%f    y:%f,%f     z:%f,%f \n",cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100].X(),testg.X(),
//	      //     cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100].Y(),testg.Y(),
//	      //     cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100].Z(),testg.Z());
//
//              for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
//                if (gtr200x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR200 - 1]) {
//                  continue;
//                }
//                if (gtr200x_cluster->NumHits() < kMinHitsInXCluster) {
//                  continue;
//                }
//                cluster_set->gtr_clusters[1] = gtr200x_cluster;
//                cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR200] = gtr200x_cluster->GlobalPosT(*geometry);
//                for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
//                  if (gtr300x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR300 - 1]) {
//                    continue;
//                  }
//                  if (gtr300x_cluster->NumHits() < kMinHitsInXCluster) {
//                    continue;
//                  }
//                  cluster_set->gtr_clusters[2] = gtr300x_cluster;
//                  cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR300] = gtr300x_cluster->GlobalPosT(*geometry);
//		  				bool is_cand = false;
//                  double chi2 = 5;
//                  if (IsXTrackCandidate(cluster_set,gtr100_module_id)) {
//                    cluster_sets[0].emplace_back(*cluster_set);
//                  }
//                }
//              }
//            }
//        }
//      }
//    }
//
//// ---  Y AXIS PART begins --- ///  
//  for (const auto& gtr300_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
//    if (gtr300_module_id == 105) {
//      continue;
//    }
//    auto is_l = IsLModule(gtr300_module_id);
//    auto& gtr300y_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsY);
//    for (const auto& gtr200_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
////      if (is_l != IsLModule(gtr200_module_id)) {
//      if (abs(gtr300_module_id - gtr200_module_id) > 1) {
//        continue;
//      }
//      auto& gtr200y_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsY);
//      for (const auto& gtr100_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
////        if (is_l != IsLModule(gtr100_module_id)) {
//      if (abs(gtr300_module_id - gtr100_module_id) > 1) {
//          continue;
//        }
//        auto& gtr100y_cluster_ptrs  = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsY);
//        auto& gtr100yb_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsYb);
//        for (const auto& gtr300y_cluster : gtr300y_cluster_ptrs) {
//          if (gtr300y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
//            continue;
//          }
//          cluster_set->gtr_clusters[2] = gtr300y_cluster;
//          cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR300] = gtr300y_cluster->GlobalPosT(*geometry);
//          for (const auto& gtr200y_cluster : gtr200y_cluster_ptrs) {
//            if (gtr200y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
//              continue;
//            }
//            cluster_set->gtr_clusters[1] = gtr200y_cluster;
//            cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR200] = gtr200y_cluster->GlobalPosT(*geometry);
//            for (const auto& gtr100y_cluster : gtr100y_cluster_ptrs) {
//              if (gtr100y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
//                continue;
//              }
//              cluster_set->gtr_clusters[0] = gtr100y_cluster;
//              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100y_cluster->GlobalPosT(*geometry);
//              if (IsYTrackCandidate(cluster_set)) {
//                cluster_sets[1].emplace_back(*cluster_set);
//              }
//            }
//            for (const auto& gtr100yb_cluster : gtr100yb_cluster_ptrs) {
//              if (gtr100yb_cluster->PeakSum() < kGTRPeakSumThresholdY) {
//                continue;
//              }
//              cluster_set->gtr_clusters[0] = gtr100yb_cluster;
//              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100yb_cluster->GlobalPosT(*geometry);
//              if (IsYTrackCandidate(cluster_set)) {
//                cluster_sets[1].emplace_back(*cluster_set);
//              }
//            }
//          }
//        }
//      }
//    }
//  }
//  delete cluster_set;
//  n_x_cands = cluster_sets[0].size();
//  n_y_cands = cluster_sets[1].size();
////E16INFO("number of x candidates: %d", n_x_cands);
////E16INFO("number of y candidates: %d", n_y_cands);
//  
//  for (const auto& x_cand : cluster_sets[0]) {
////    auto& ssdx = *x_cand.ssd_cluster;
//    auto& gtrx = x_cand.gtr_clusters;
//    std::array<int, kNumGTRLayers> x_module_ids = {gtrx[0]->ModuleId(), gtrx[1]->ModuleId(), gtrx[2]->ModuleId()};
//    std::array<float, kNumGTRLayers> x_timings = {gtrx[0]->Timing4(), gtrx[1]->Timing4(), gtrx[2]->Timing4()};
//    std::array<float, kNumGTRLayers> x_peak_sums = {gtrx[0]->PeakSum(), gtrx[1]->PeakSum(), gtrx[2]->PeakSum()};
//    for (const auto& y_cand : cluster_sets[1]) {
//      auto& gtry = y_cand.gtr_clusters;
//      bool is_same_module = true;
//      /*
//      if ((gtry[0]->IsY() && gtrx[0]->LocalPosT().X() <= 0) || (gtry[0]->IsYb() && gtrx[0]->LocalPosT().X() >= 0)) {
//        continue;
//      }
//      */
//      for (int i = 0; i < kNumGTRLayers; ++i) {
//        if (x_module_ids[i] != gtry[i]->ModuleId() || fabs(x_timings[i] - gtry[i]->Timing4()) > kGTRTimeDiffThreshold[i] ) { // ozawa v8
//          is_same_module = false;
//          break;
//        }
//      }
//      if (!is_same_module) {
//        continue;
//      }
//
//      track_candidates.emplace_back(E16ANA_StraightTrackCandidate(geometry));
//      auto& tmp_cand = track_candidates.back();
//      tmp_cand.SetTrackID(track_candidates.size() - 1);
//      tmp_cand.SetCharge(x_cand.charge);
//      tmp_cand.SetInitX(0);
////      //tmp_cand.SetInitX(-20);
//      tmp_cand.SetInitY(0);
//		tmp_cand.SetInitZ(E16ANA_StraightTrackConstant::kTargetZ[x_cand.target_id]);
////		std::cout << "xy = " << x_cand.xy << ", y_xy = " << y_cand.xy << std::endl;
////		tmp_cand.SetInitX(x_cand.xy);
////      if(x_cand.charge<0) tmp_cand.SetInitZ(-40);
//      tmp_cand.SetDefaultSigma();
//      tmp_cand.SetXChiSquare(x_cand.chi_square);
//      tmp_cand.SetYChiSquare(y_cand.chi_square);
//      for (int i = 0; i < kNumRoughFitDegree[0]; ++i) {
//        tmp_cand.SetXCoef(i, x_cand.coefs[i]);
//      }
//      for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
//        tmp_cand.SetYCoef(i, y_cand.coefs[i]);
//      }
//      auto& cluster_pairs = tmp_cand.ClusterPairs();
////      cluster_pairs[0].Set(geometry, 0, ssdx.ModuleId(), x_cand.global_poss[0], &ssdx);
//      for (int i = 0; i < kNumGTRLayers; ++i) {
//        cluster_pairs[1 + i].Set(geometry, 1 + i, gtrx[i]->ModuleId(), x_cand.global_poss[1 + i], y_cand.global_poss[1 + i], gtrx[i], gtry[i]);
//
//	  int nhit = gtrx[i]->NumCls();
//	  for(int j=0;j<nhit;j++){
//	    cluster_pairs[1+i].SetCAdc1((double)gtrx[i]->CAdc1(j));
//	    cluster_pairs[1+i].SetCPos((double)gtrx[i]->CPos(j));
//	    cluster_pairs[1+i].SetCAdc2((double)gtrx[i]->CAdc2(j));
//	    cluster_pairs[1+i].SetCAdc3((double)gtrx[i]->CAdc3(j));
//	    cluster_pairs[1+i].SetCAdc4((double)gtrx[i]->CAdc4(j));
//	    cluster_pairs[1+i].SetCTiming((double)gtrx[i]->CTiming(j));
//	    cluster_pairs[1+i].SetCAdc5((double)gtrx[i]->CAdc5(j));
//	  }
//
//	  int nhit2 = gtrx[i]->NumCls2();
//	  for(int j=0;j<nhit2;j++){
//	    cluster_pairs[1+i].SetCTiming2((double)gtrx[i]->CTiming2(j));
//	    cluster_pairs[1+i].SetCPos2((double)gtrx[i]->CPos2(j));
//	  }
//	  int nhit3 = gtrx[i]->NumCls3();
//	  for(int j=0;j<nhit3;j++){
//	    cluster_pairs[1+i].SetCTiming3((double)gtrx[i]->CTiming3(j));
//	    cluster_pairs[1+i].SetCPos3((double)gtrx[i]->CPos3(j));
//	  }
//
//	  int nhit4 = gtrx[i]->NumCls4();
//	  for(int j=0;j<nhit4;j++){
//	    cluster_pairs[1+i].SetCTiming4((double)gtrx[i]->CTiming4(j));
//	    cluster_pairs[1+i].SetCPos4((double)gtrx[i]->CPos4(j));
//	    cluster_pairs[1+i].SetCTiming5((double)gtrx[i]->CTiming5(j));
//	    cluster_pairs[1+i].SetCPos5((double)gtrx[i]->CPos5(j));
//	  }
//      }
//    }
//  }
//}



void E16ANA_StraightTrackCandidates::SearchTrackCandidates() {
  track_candidates.clear();
  track_candidates.reserve(kNumReserveTracks[2]); // tmp
  auto& ssd = record->SSD();
  auto& gtr = record->GTR();
//E16INFO("number of SSD clusters: %d", ssd.NumClusters());
//E16INFO("number of GTR clusters: %d", gtr.NumClusters());
 if(removed_layer !=0 && ssd.NumClusters()> kMaxSSDClusterN) return;
  std::array<std::vector<OneAxisClusterSet>, 2> cluster_sets;
  cluster_sets[0].reserve(kNumReserveTracks[0]);
  cluster_sets[1].reserve(kNumReserveTracks[1]);
  auto cluster_set = new OneAxisClusterSet();

  for (const auto& ssd_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
    if (ssd_module_id == 105) continue;
    auto is_l = IsLModule(ssd_module_id);
    auto& ssd_cluster_ptrs = ssd.ClusterPtrs(ssd_module_id, 0, 0);
    for (const auto& gtr100_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
    if (abs(gtr100_module_id - ssd_module_id) > 1) continue;
        auto& gtr100x_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsX);
      for (const auto& gtr200_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
        if (abs(gtr200_module_id - ssd_module_id) > 1) continue;
          auto& gtr200x_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsX);
        for (const auto& gtr300_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
          if (abs(gtr300_module_id - ssd_module_id) > 1) continue;
            auto& gtr300x_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsX);
          if(removed_layer ==0 ){//without SSD
            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
              if (gtr100x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR100 - 1]) continue;
              if (gtr100x_cluster->NumHits() < kMinHitsInXCluster) continue;
              cluster_set->gtr_clusters[0] = gtr100x_cluster;
              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100x_cluster->GlobalPosT(*geometry);
      	     TVector3 testg = gtr100x_cluster->GlobalPos(*geometry);	      
              for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
                if (gtr200x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR200 - 1]) continue;
                if (gtr200x_cluster->NumHits() < kMinHitsInXCluster) continue;
                cluster_set->gtr_clusters[1] = gtr200x_cluster;
                cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR200] = gtr200x_cluster->GlobalPosT(*geometry);
                for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
                  if (gtr300x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR300 - 1])   continue;
                  if (gtr300x_cluster->NumHits() < kMinHitsInXCluster)   continue;
                  cluster_set->gtr_clusters[2] = gtr300x_cluster;
                  cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR300] = gtr300x_cluster->GlobalPosT(*geometry);
//                  bool is_cand = false;
		              bool is_cand = false;
                  double chi2 = 5;
                  if (IsXTrackCandidate(cluster_set,gtr100_module_id)) {
                    cluster_sets[0].emplace_back(*cluster_set);
                  }
                }
              }
            }
          }//without ssd
          else if (removed_layer ==-1){//All targets
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
                  cluster_set->gtr_clusters[1] = gtr200x_cluster;
                  cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR200] = gtr200x_cluster->GlobalPosT(*geometry);
                  for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
                    if (gtr300x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR300 - 1]) {
                      continue;
                    }
                    if (gtr300x_cluster->NumHits() < kMinHitsInXCluster) {
                      continue;
                    }
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
          }//all targets, that is,  removed == -1
          else if (removed_layer == 1){//without gtr100
            for (const auto& ssd_cluster : ssd_cluster_ptrs) {
              cluster_set->ssd_cluster = ssd_cluster;
              cluster_set->global_poss[E16ANA_StraightTrackConstant::kSSD] = ssd_cluster->GlobalPos(*geometry);
                for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
                  if (gtr200x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR200 - 1]) {
                    continue;
                  }
                  if (gtr200x_cluster->NumHits() < kMinHitsInXCluster) {
                    continue;
                  }
                  cluster_set->gtr_clusters[1] = gtr200x_cluster;
                  cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR200] = gtr200x_cluster->GlobalPosT(*geometry);
                  for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
                    if (gtr300x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR300 - 1]) {
                      continue;
                    }
                    if (gtr300x_cluster->NumHits() < kMinHitsInXCluster) {
                      continue;
                    }
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
          }//without gtr100
          else if(removed_layer == 2) {
            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
              if (gtr100x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR100 - 1]) {
               continue;
              }
              if (gtr100x_cluster->NumHits() < kMinHitsInXCluster) {
                continue;
              }
              cluster_set->gtr_clusters[1] = gtr100x_cluster;
              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100x_cluster->GlobalPosT(*geometry);
              for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
                if (gtr300x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR300 - 1]) {
                  continue;
                }
                if (gtr300x_cluster->NumHits() < kMinHitsInXCluster) {
                  continue;
                }
                cluster_set->gtr_clusters[2] = gtr300x_cluster;
                cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR300] = gtr300x_cluster->GlobalPosT(*geometry);
                bool is_cand = false;
                double chi2 = 5;
                if (IsXTrackCandidate(cluster_set,ssd_module_id)) {
                  cluster_sets[0].emplace_back(*cluster_set);
                }
              }
            }               
          } //without gtr200
          else if(removed_layer == 3) {//without gtr300
            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
              if (gtr100x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR100 - 1]) {
                continue;
              }
              if (gtr100x_cluster->NumHits() < kMinHitsInXCluster) {
                continue;
              }
              cluster_set->gtr_clusters[1] = gtr100x_cluster;
              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100x_cluster->GlobalPosT(*geometry);
              for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
                if (gtr200x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR200 - 1]) {
                  continue;
                }
                if (gtr200x_cluster->NumHits() < kMinHitsInXCluster) {
                  continue;
                }
                cluster_set->gtr_clusters[2] = gtr200x_cluster;
                cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR200] = gtr200x_cluster->GlobalPosT(*geometry);
                bool is_cand = false;
                double chi2 = 5;
                if (IsXTrackCandidate(cluster_set,ssd_module_id)) {
                  cluster_sets[0].emplace_back(*cluster_set);
                }
              }   
            }
          }//without gtr300
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
//      if (abs(gtr200_module_id - gtr300_module_id) > 1) {
      if (is_l != IsLModule(gtr200_module_id)) {
        continue;
      }
      auto& gtr200y_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsY);
      for (const auto& gtr100_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
//        if (abs(gtr100_module_id - gtr300_module_id) > 1) {
        if (is_l != IsLModule(gtr100_module_id)) {
          continue;
        }
        auto& gtr100y_cluster_ptrs  = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsY);
        auto& gtr100yb_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsYb);
        for (const auto& gtr300y_cluster : gtr300y_cluster_ptrs) {
          if (gtr300y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
            continue;
          }
          cluster_set->gtr_clusters[2] = gtr300y_cluster;
          cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR300] = gtr300y_cluster->GlobalPosT(*geometry);
          for (const auto& gtr200y_cluster : gtr200y_cluster_ptrs) {
            if (gtr200y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
              continue;
            }
            cluster_set->gtr_clusters[1] = gtr200y_cluster;
            cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR200] = gtr200y_cluster->GlobalPosT(*geometry);
            for (const auto& gtr100y_cluster : gtr100y_cluster_ptrs) {
              if (gtr100y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
	      //if (gtr100y_cluster->PeakSum() < 10000) {
                continue;
              }
              cluster_set->gtr_clusters[0] = gtr100y_cluster;
              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100y_cluster->GlobalPosT(*geometry);
              if (IsYTrackCandidate(cluster_set)) {
                cluster_sets[1].emplace_back(*cluster_set);
              }
            }
            for (const auto& gtr100yb_cluster : gtr100yb_cluster_ptrs) {
              if (gtr100yb_cluster->PeakSum() < kGTRPeakSumThresholdY) {
	      //if (gtr100yb_cluster->PeakSum() < 10000) {
                continue;
              }
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
//E16INFO("number of x candidates: %d", n_x_cands);
  std::cout << "number of x candidates " << n_x_cands <<std::endl;
//E16INFO("number of y candidates: %d", n_y_cands);
  
  for (const auto& x_cand : cluster_sets[0]) {
    auto& ssdx = *x_cand.ssd_cluster;
    auto& gtrx = x_cand.gtr_clusters;
    std::array<int, kNumGTRLayers> x_module_ids = {gtrx[0]->ModuleId(), gtrx[1]->ModuleId(), gtrx[2]->ModuleId()};
//    std::array<float, kNumGTRLayers> x_timings = {gtrx[0]->Timing4(), gtrx[1]->Timing4(), gtrx[2]->Timing4()};
    std::array<float, kNumGTRLayers> x_timings = {gtrx[0]->Timing(), gtrx[1]->Timing(), gtrx[2]->Timing()};
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
        if(i+1 != removed_layer){ 
//        if (x_module_ids[i] != gtry[i]->ModuleId() || fabs(x_timings[i] - gtry[i]->Timing4()) > kGTRTimeDiffThreshold[i] ) { // Matching 
        if (x_module_ids[i] != gtry[i]->ModuleId() || fabs(x_timings[i] - gtry[i]->Timing()) > kGTRTimeDiffThreshold[i] ) { // Matching 
//			 std::cout << "module " << x_module_ids[i] << ", " << gtry[i]->ModuleId() << std::endl;
//			 std::cout << "timing " << x_timings[i] << ", " << gtry[i]->Timing4() << std::endl;
//          is_same_module = false;
//			 std::cout << "not matched " << std::endl;
          break;
          }
        }
      }
      if (!is_same_module) {
        continue;
      }
      track_candidates.emplace_back(E16ANA_StraightTrackCandidate(geometry));
      auto& tmp_cand = track_candidates.back();
      tmp_cand.SetTrackID(track_candidates.size() - 1);

      if(isWire){//If wire targets case, initial of RK is targets
        tmp_cand.SetInitX(targets_pos[tmp_cand.TargetID()].x());
        tmp_cand.SetInitY(targets_pos[tmp_cand.TargetID()].y());
        tmp_cand.SetInitZ(targets_pos[tmp_cand.TargetID()].z());
      }
      else {//three targets case, ssd or gtr100 is initial 
        if(removed_layer ==0){
          auto gtr100_gpos = gtrx[0]->GlobalPos(*geometry);
          tmp_cand.SetInitX(gtr100_gpos.X());
          tmp_cand.SetInitY(gtr100_gpos.Y());
          tmp_cand.SetInitZ(gtr100_gpos.Z());

        }
        else {
          auto ssd_gpos = ssdx.GlobalPos(*geometry);
          tmp_cand.SetInitX(ssd_gpos.X());
          tmp_cand.SetInitY(CalcRoughYPosition(ssdx.ModuleId(), y_cand.coefs));
          tmp_cand.SetInitZ(ssd_gpos.Z());
        }
        
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
      if(removed_layer != 0){//ssd
//		  std::cout << "ssd module " << ssdx.ModuleId() << std::endl;
//		  std::cout << "global pos " << &x_cand.global_poss[0] << std::endl;
//		  std::cout << "ssd address  " << &ssdx << std::endl;
        cluster_pairs[0].Set(geometry, 0, ssdx.ModuleId(), x_cand.global_poss[0], &ssdx);//x only for ssd
      }
      for (int i = 0; i < kNumGTRLayers; ++i) {//gtr
        if(i+1 !=removed_layer){
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
}




//void E16ANA_StraightTrackCandidates::SearchTrackCandidates() {
//  track_candidates.clear();
//  track_candidates.reserve(kNumReserveTracks[2]); // tmp
//  auto& ssd = record->SSD();
//  auto& gtr = record->GTR();
////E16INFO("number of SSD clusters: %d", ssd.NumClusters());
////E16INFO("number of GTR clusters: %d", gtr.NumClusters());
// if(ssd.NumClusters()>30) return;
//  std::array<std::vector<OneAxisClusterSet>, 2> cluster_sets;
//  cluster_sets[0].reserve(kNumReserveTracks[0]);
//  cluster_sets[1].reserve(kNumReserveTracks[1]);
//  auto cluster_set = new OneAxisClusterSet();
//
//  for (const auto& ssd_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
//    if (ssd_module_id == 105) {
//      continue;
//    }
//    auto is_l = IsLModule(ssd_module_id);
//    auto& ssd_cluster_ptrs = ssd.ClusterPtrs(ssd_module_id, 0, 0);
//    for (const auto& gtr100_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
////      if (abs(gtr100_module_id - ssd_module_id) > 1) {
//      if (is_l != IsLModule(gtr100_module_id)) {
//        continue;
//      }
//      auto& gtr100x_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsX);
//      for (const auto& gtr200_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
////        if (abs(gtr200_module_id - ssd_module_id) > 1) {
//        if (is_l != IsLModule(gtr200_module_id)) {
//          continue;
//        }
//        auto& gtr200x_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsX);
//        for (const auto& gtr300_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
////          if (abs(gtr300_module_id - ssd_module_id) > 1) {
//          if (is_l != IsLModule(gtr300_module_id)) {
//            continue;
//          }
//          auto& gtr300x_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsX);
//
//
//          for (const auto& ssd_cluster : ssd_cluster_ptrs) {
//            cluster_set->ssd_cluster = ssd_cluster;
//            cluster_set->global_poss[E16ANA_StraightTrackConstant::kSSD] = ssd_cluster->GlobalPos(*geometry);
//            for (const auto& gtr100x_cluster : gtr100x_cluster_ptrs) {
//              if (gtr100x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR100 - 1]) {
//                continue;
//              }
//              if (gtr100x_cluster->NumHits() < kMinHitsInXCluster) {
//                continue;
//              }
//              cluster_set->gtr_clusters[0] = gtr100x_cluster;
//              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100x_cluster->GlobalPosT(*geometry);
//	      TVector3 testg = gtr100x_cluster->GlobalPos(*geometry);
//
//	      //printf("x:%f,%f    y:%f,%f     z:%f,%f \n",cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100].X(),testg.X(),
//	      //     cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100].Y(),testg.Y(),
//	      //     cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100].Z(),testg.Z());
//
//              for (const auto& gtr200x_cluster : gtr200x_cluster_ptrs) {
//                if (gtr200x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR200 - 1]) {
//                  continue;
//                }
//                if (gtr200x_cluster->NumHits() < kMinHitsInXCluster) {
//                  continue;
//                }
//                cluster_set->gtr_clusters[1] = gtr200x_cluster;
//                cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR200] = gtr200x_cluster->GlobalPosT(*geometry);
//                for (const auto& gtr300x_cluster : gtr300x_cluster_ptrs) {
//                  if (gtr300x_cluster->PeakSum() < kGTRPeakSumThresholdX[E16ANA_StraightTrackConstant::kGTR300 - 1]) {
//                    continue;
//                  }
//                  if (gtr300x_cluster->NumHits() < kMinHitsInXCluster) {
//                    continue;
//                  }
//                  cluster_set->gtr_clusters[2] = gtr300x_cluster;
//                  cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR300] = gtr300x_cluster->GlobalPosT(*geometry);
////                  bool is_cand = false;
//		  bool is_cand = false;
//                  double chi2 = 5;
//                  if (IsXTrackCandidate(cluster_set,ssd_module_id)) {
//                    cluster_sets[0].emplace_back(*cluster_set);
//                  }
//                }
//              }
//            }
//          }
//        }
//      }
//    }
//  }
//
//// ---  Y AXIS PART begins --- ///  
//  for (const auto& gtr300_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
//    if (gtr300_module_id == 105) {
//      continue;
//    }
//    auto is_l = IsLModule(gtr300_module_id);
//    auto& gtr300y_cluster_ptrs = gtr.ClusterPtrs(gtr300_module_id, 2, E16DST_DST1Constant::kIsY);
//    for (const auto& gtr200_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
////      if (abs(gtr200_module_id - gtr300_module_id) > 1) {
//      if (is_l != IsLModule(gtr200_module_id)) {
//        continue;
//      }
//      auto& gtr200y_cluster_ptrs = gtr.ClusterPtrs(gtr200_module_id, 1, E16DST_DST1Constant::kIsY);
//      for (const auto& gtr100_module_id : E16ANA_StraightTrackConstant::kModuleIDs) {
////        if (abs(gtr100_module_id - gtr300_module_id) > 1) {
//        if (is_l != IsLModule(gtr100_module_id)) {
//          continue;
//        }
//        auto& gtr100y_cluster_ptrs  = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsY);
//        auto& gtr100yb_cluster_ptrs = gtr.ClusterPtrs(gtr100_module_id, 0, E16DST_DST1Constant::kIsYb);
//        for (const auto& gtr300y_cluster : gtr300y_cluster_ptrs) {
//          if (gtr300y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
//            continue;
//          }
//          cluster_set->gtr_clusters[2] = gtr300y_cluster;
//          cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR300] = gtr300y_cluster->GlobalPosT(*geometry);
//          for (const auto& gtr200y_cluster : gtr200y_cluster_ptrs) {
//            if (gtr200y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
//              continue;
//            }
//            cluster_set->gtr_clusters[1] = gtr200y_cluster;
//            cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR200] = gtr200y_cluster->GlobalPosT(*geometry);
//            for (const auto& gtr100y_cluster : gtr100y_cluster_ptrs) {
//              if (gtr100y_cluster->PeakSum() < kGTRPeakSumThresholdY) {
//	      //if (gtr100y_cluster->PeakSum() < 10000) {
//                continue;
//              }
//              cluster_set->gtr_clusters[0] = gtr100y_cluster;
//              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100y_cluster->GlobalPosT(*geometry);
//              if (IsYTrackCandidate(cluster_set)) {
//                cluster_sets[1].emplace_back(*cluster_set);
//              }
//            }
//            for (const auto& gtr100yb_cluster : gtr100yb_cluster_ptrs) {
//              if (gtr100yb_cluster->PeakSum() < kGTRPeakSumThresholdY) {
//	      //if (gtr100yb_cluster->PeakSum() < 10000) {
//                continue;
//              }
//              cluster_set->gtr_clusters[0] = gtr100yb_cluster;
//              cluster_set->global_poss[E16ANA_StraightTrackConstant::kGTR100] = gtr100yb_cluster->GlobalPosT(*geometry);
//              if (IsYTrackCandidate(cluster_set)) {
//                cluster_sets[1].emplace_back(*cluster_set);
//              }
//            }
//          }
//        }
//      }
//    }
//  }
//  delete cluster_set;
//  n_x_cands = cluster_sets[0].size();
//  n_y_cands = cluster_sets[1].size();
////E16INFO("number of x candidates: %d", n_x_cands);
////E16INFO("number of y candidates: %d", n_y_cands);
//  
//  for (const auto& x_cand : cluster_sets[0]) {
//    auto& ssdx = *x_cand.ssd_cluster;
//    auto& gtrx = x_cand.gtr_clusters;
//    std::array<int, kNumGTRLayers> x_module_ids = {gtrx[0]->ModuleId(), gtrx[1]->ModuleId(), gtrx[2]->ModuleId()};
//    std::array<float, kNumGTRLayers> x_timings = {gtrx[0]->Timing4(), gtrx[1]->Timing4(), gtrx[2]->Timing4()};
//    std::array<float, kNumGTRLayers> x_peak_sums = {gtrx[0]->PeakSum(), gtrx[1]->PeakSum(), gtrx[2]->PeakSum()};
//    for (const auto& y_cand : cluster_sets[1]) {
//      auto& gtry = y_cand.gtr_clusters;
//      bool is_same_module = true;
//      /*
//      if ((gtry[0]->IsY() && gtrx[0]->LocalPosT().X() <= 0) || (gtry[0]->IsYb() && gtrx[0]->LocalPosT().X() >= 0)) {
//        continue;
//      }
//      */
//      for (int i = 0; i < kNumGTRLayers; ++i) {
//        if (x_module_ids[i] != gtry[i]->ModuleId() || fabs(x_timings[i] - gtry[i]->Timing4()) > kGTRTimeDiffThreshold[i] ) { // ozawa v8
//          is_same_module = false;
//          break;
//        }
//      }
//      if (!is_same_module) {
//        continue;
//      }
//
//      track_candidates.emplace_back(E16ANA_StraightTrackCandidate(geometry));
//      auto& tmp_cand = track_candidates.back();
//      tmp_cand.SetTrackID(track_candidates.size() - 1);
//      tmp_cand.SetCharge(x_cand.charge);
//      tmp_cand.SetInitX(20);
//      //tmp_cand.SetInitX(-20);
//      tmp_cand.SetInitY(0);
//      tmp_cand.SetInitZ(40);
//      if(x_cand.charge<0) tmp_cand.SetInitZ(-40);//target selection
//      tmp_cand.SetDefaultSigma();
//      tmp_cand.SetXChiSquare(x_cand.chi_square);
//      tmp_cand.SetYChiSquare(y_cand.chi_square);
//      for (int i = 0; i < kNumRoughFitDegree[0]; ++i) {
//        tmp_cand.SetXCoef(i, x_cand.coefs[i]);
//      }
//      for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
//        tmp_cand.SetYCoef(i, y_cand.coefs[i]);
//      }
//      auto& cluster_pairs = tmp_cand.ClusterPairs();
//      cluster_pairs[0].Set(geometry, 0, ssdx.ModuleId(), x_cand.global_poss[0], &ssdx);
//      for (int i = 0; i < kNumGTRLayers; ++i) {
//        cluster_pairs[1 + i].Set(geometry, 1 + i, gtrx[i]->ModuleId(), x_cand.global_poss[1 + i], y_cand.global_poss[1 + i], gtrx[i], gtry[i]);
//
//	  int nhit = gtrx[i]->NumCls();
//	  for(int j=0;j<nhit;j++){
//	    cluster_pairs[1+i].SetCAdc1((double)gtrx[i]->CAdc1(j));
//	    cluster_pairs[1+i].SetCPos((double)gtrx[i]->CPos(j));
//	    cluster_pairs[1+i].SetCAdc2((double)gtrx[i]->CAdc2(j));
//	    cluster_pairs[1+i].SetCAdc3((double)gtrx[i]->CAdc3(j));
//	    cluster_pairs[1+i].SetCAdc4((double)gtrx[i]->CAdc4(j));
//	    cluster_pairs[1+i].SetCTiming((double)gtrx[i]->CTiming(j));
//	    cluster_pairs[1+i].SetCAdc5((double)gtrx[i]->CAdc5(j));
//	  }
//
//	  int nhit2 = gtrx[i]->NumCls2();
//	  for(int j=0;j<nhit2;j++){
//	    cluster_pairs[1+i].SetCTiming2((double)gtrx[i]->CTiming2(j));
//	    cluster_pairs[1+i].SetCPos2((double)gtrx[i]->CPos2(j));
//	  }
//	  int nhit3 = gtrx[i]->NumCls3();
//	  for(int j=0;j<nhit3;j++){
//	    cluster_pairs[1+i].SetCTiming3((double)gtrx[i]->CTiming3(j));
//	    cluster_pairs[1+i].SetCPos3((double)gtrx[i]->CPos3(j));
//	  }
//
//	  int nhit4 = gtrx[i]->NumCls4();
//	  for(int j=0;j<nhit4;j++){
//	    cluster_pairs[1+i].SetCTiming4((double)gtrx[i]->CTiming4(j));
//	    cluster_pairs[1+i].SetCPos4((double)gtrx[i]->CPos4(j));
//	    cluster_pairs[1+i].SetCTiming5((double)gtrx[i]->CTiming5(j));
//	    cluster_pairs[1+i].SetCPos5((double)gtrx[i]->CPos5(j));
//	  }
//
//      }
//    }
//  }
//}

void E16ANA_StraightTrackCandidates::Fit() {
  int i=0;
	for (auto& cand : track_candidates) {
    cand.Fit(fitter, vertex_xy_fix_flag, py_fix_flag, vertex_z_fix_flag, isWire, removed_layer);
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
//    for (int i = 0; i < E16ANA_StraightTrackConstant::kNumTargets; ++i) {
    for (int i = 0; i < n_targets; ++i) {
      track.SetInitialPosAtTargetPlane(i, cand.PosAtTarget(i));
      track.SetInitialMomAtTargetPlane(i, cand.MomAtTarget(i));
    }
    for (int i = 0; i < E16ANA_StraightTrackConstant::kNumDetectorLayers; ++i) {
      auto& lpos = cand.LocalFitResult(i).local_pos;
      auto& lmom = cand.LocalFitResult(i).local_mom;
      track.SetHitPos(i, lpos);
      track.SetHitMom(i, lmom);
    }
//    for (int i = 0; i < E16ANA_StraightTrackConstant::kNumTrackingLayers; ++i) {
    for (int i = 1; i < E16ANA_StraightTrackConstant::kNumTrackingLayers; ++i) {
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
}

void E16ANA_StraightTrackCandidates::Analyze() {
  track_candidates.clear();
  selected_track_candidates.clear();
  SearchTrackCandidates();//
//  E16INFO("number of track candidate: %d", track_candidates.size());
  Fit();
  SearchLGHits();//230826 add
  AddTracksToRecord();
  return;
}

void E16ANA_StraightTrackCandidates::PrintParam() {
  std::cout << "GTR Time Difference Threshold :" << std::endl;
  std::cout << "  GTR100 : " << kGTRTimeDiffThreshold[0] << ", GTR200 : " << kGTRTimeDiffThreshold[1] << ", GTR300 : " << kGTRTimeDiffThreshold[2] << std::endl;
  std::cout << "Sigma at X Rough Fit :" << std::endl;
  std::cout << "  Target : " << kXSigma[0] << ", SSD : " << kXSigma[1] << ", GTR100 : " << kXSigma[2] << ", GTR200 : " << kXSigma[3] << ", GTR300 : " << kXSigma[4] << std::endl;
  std::cout << "Sigma at Y Rough Fit :" << std::endl;
  std::cout << "  GTR100 : " << kYSigma[0] << ", GTR200 : " << kYSigma[2] << ", GTR300 : " << kYSigma[2] << std::endl;
  std::cout << "Minimum Hits in X Cluster : " << kMinHitsInXCluster << std::endl;
  std::cout << "GTR Position Difference Threshold between Layers at Y Candidate Search : " << kGTRYDiffThreshold << std::endl;
  std::cout << "GTR X ADC Peak Sum Threshold :" << std::endl;
  std::cout << "  GTR100 : " << kGTRPeakSumThresholdX[0] << ", GTR200 : " << kGTRPeakSumThresholdX[1] << ", GTR300 : " << kGTRPeakSumThresholdX[2] << std::endl;
  std::cout << "GTR Y ADC Peak Sum Threshold : " << kGTRPeakSumThresholdY << std::endl;
  std::cout << "Rough Fit Chi Square Threshold :" << std::endl;
  std::cout << "  X : " << kRoughFitChiSquareThreshold[0] << ", Y : " << kRoughFitChiSquareThreshold[1] << std::endl;
  std::cout << "X Rough Fit Coefficient Threshold : " 
            << kRoughXFitCoefficientThreshold[0] << ", " << kRoughXFitCoefficientThreshold[1] << kRoughXFitCoefficientThreshold[2] << std::endl;
  std::cout << "Y Rough Fit Coefficient Threshold : " << kRoughYFitCoefficientThreshold[0] << ", " << kRoughYFitCoefficientThreshold[1] << std::endl;
  std::cout << "HBD Projection Threshold : " << kHBDProjectionThreshold << std::endl;
  std::cout << "LG  Projection Threshold : " << kLGProjectionThreshold << std::endl;
  std::cout << "Near Target Threshold : " << kNearTargetThreshold << std::endl;
  std::cout << "E16ANA_StepTrack Step Size [cm] : " << kStepTrackStepSizeCm << std::endl;
  std::cout << "E16ANA_StepTrack Array Size : " << kStepTrackArraySize << std::endl;
}
