#include "E16DSTN_PosCorrection.hh"
#include "E16ANA_StraightTrackConstant.hh"
#include "E16ANA_StraightTrackParameter.hh"
#include "E16ANA_StraightMultiTrack.hh"

using namespace E16ANA_StraightTrackParameter;


void E16DSTN_PosCorrection::PosCoLoop(TTree *tree, int print_cycle, int max_event, bool vertex_xy_fix_flag, bool py_fix_flag, bool  vetex_z_fix_flag, bool isWire) { 

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
	CorrectionFit();
	AddRecord();
	}
}


void E16DSTN_PosCorrection::UpdateFitResult(const int tid){
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




void E16DSTN_PosCorrection::CorrectionFit(){
	chisq.clear();
	for(int tid = 0 ; tid < n_selected; tid++){
//		std::cout  << "track id " <<tid <<  std::endl;
		fitter->Clear();
		this->AddTrackCorrectedHit(fitter, tid);
		fitter->SetRungeKuttaStepSize(15.0);
		fitter->SetMaxSteps(kTrackingMaxSteps);
		double chi2;
		chi2 = fitter->Fit(false, false, false, kMinuitStrategy, kMinuitMaxFunctionCalls);//vertex z fix
		//chi2 = fitter->Fit(false, false, true, kMinuitStrategy, kMinuitMaxFunctionCalls);//vertex z fix
//		std::cout << "chi2 = " << chi2 << std::endl;
		chisq.push_back(chi2);	
		UpdateFitResult(tid);
	}
}
void E16DSTN_PosCorrection::AddTrackCorrectedHit(E16ANA_StraightMultiTrack *fitter, const int tid){

	if (!CalcRoughMomentumV2()) {
		std::cerr << "Cannot Caluculate rough momentum " << std::endl;
	}	
	
	for (auto& fit_result : fit_results) {
		fit_result.set_flag = 0;
	}
	fitter->Clear();
	double target_z;
	if(rk_fit_init_pos_gz->at(tid) < 0){
		target_z = -40;
	}
	else{
		target_z = 40;
	}
  	fitter->SetInitialVertex(TVector3(20,rk_fit_init_pos_gy->at(tid), target_z),TVector3(kInitPosErrorWire));

//	std::cout << "init "  << rk_fit_init_pos_gy->at(tid) << std::endl;
	fitter->SetInitialMomentum(0, TVector3(rk_fit_init_mom_gx->at(tid), rk_fit_init_mom_gy->at(tid), rk_fit_init_mom_gz->at(tid)));//zero is for a single track
//	std::cout << "init mom x "  << rk_fit_init_mom_gx->at(tid) << std::endl;
//	std::cout << "init mom y "  << rk_fit_init_mom_gy->at(tid) << std::endl;
//	std::cout << "init mom z "  << rk_fit_init_mom_gz->at(tid) << std::endl;
//

	std::array<TVector3,4> Sigmas = {TVector3( 0.067, 0, 0),
												TVector3(	 0.265, 0.625, 0),
												TVector3(	 0.252, 0.542, 0),
//												TVector3(	 10, 0.542, 0),
												TVector3(	 0.265, 0.625, 0)};


   for (int l = 0; l < E16ANA_StraightTrackConstant::kNumTrackingLayers; ++l) {
   	if (l == removed_layer) continue;
		int mid[4] = {rk_fit_ssd_mid->at(tid), rk_fit_gtr100_mid->at(tid), rk_fit_gtr200_mid->at(tid), rk_fit_gtr300_mid->at(tid)};
//		std::cout << "mid " << rk_fit_ssd_mid->at(tid) << std::endl;
    	if (l == E16ANA_StraightTrackConstant::kSSD) {
		TVector3 lpos(rk_fit_ssd_x->at(tid), 0, 0 );
//		std::cout << "ssd x " << rk_hit_ssd_x->at(tid) << std::endl;
      fitter->AddHit(0, l, geom->SSD(E16ANA_StraightTrackConstant::ModuleID2020To2013(mid[l])),lpos, Sigmas[l]);//first zero is for a single track, second argv is the layzer order
    } else {
      fitter->AddHit(0, l, geom->GTR(E16ANA_StraightTrackConstant::ModuleID2020To2013(mid[l]), l - 1), CorrectedLocalPos(tid,mid[l],  l), Sigmas[l]);//first zero is for a single track
//		std::cout << "gtr x " << CorrectedLocalPos(tid, mid[l], l ).X() <<", " << CorrectedLocalPos(tid, mid[l], l).Y() <<std::endl;
    }
  }
//	fitter->PrintHits();
}

TVector3 E16DSTN_PosCorrection::CorrectedLocalPos(const int tid, const int mid, const int l){
	TVector3 cor_pos;//correcrted pos 
//	if(l == 0){
//		return TVector3(rk_hit_ssd_x->at(tid),0, 0 );
//	}
//	
//	else if(l == 1){//gtr100
////		double localx     = rk_hit_gtr100_tx2->at(tid);
////		double localy     = rk_hit_gtr100_ty->at(tid);
//		double localx     = rk_hit_gtr100_cogx->at(tid);
//		double localy     = rk_hit_gtr100_cogy->at(tid);
//		double vd     = 0.011;
//		double gap = 1.5;
//		double tan    = (double)rk_fit_gtr100_mom_gx->at(tid)/rk_fit_gtr100_mom_gz->at(tid);
//		double tcor   = 1.4*exp(-0.5*pow((fabs(localx)-45)/11,2))+1e-4*(localy*localy);
//		double cent0  = 150;
//		double tc1x   = cent0 + (gap - tcor)/vd;
//		double crx1   = localx - (tc1x - rk_hit_gtr100_xt4->at(tid)) * vd * tan;	
////		double crx1   = localx - (tc1x - rk_hit_gtr100_xt->at(tid)) * vd * tan;	
//		double cry1   = localy;
//		return TVector3(crx1, cry1, 0);
//	}
//	else if(l == 2)	{//gtr200
////		double localx     = rk_hit_gtr200_tx2->at(tid);//should be gtx?
////		double localy     = rk_hit_gtr200_ty->at(tid);
//		double localx     = rk_hit_gtr200_cogx->at(tid);
//		double localy     = rk_hit_gtr200_cogy->at(tid);
//		double vd     = 0.010;
//		double gap    = 1.5;
//		double tan    = (double)rk_fit_gtr200_mom_gx->at(tid)/rk_fit_gtr200_mom_gz->at(tid);
//		double tcor   = -0.8*exp(-0.5*pow((localx+75)/15,2))+exp(-0.5*pow((localx-55)/20, 2))+4e-4*(localy*localy)/4.0;
//		double cent0  = 150;
//		double tc2x   = cent0 + (gap - tcor)/vd;
//		double crx2   = localx - (tc2x - rk_hit_gtr200_xt4->at(tid)) * vd * tan;	
////		double crx2   = localx - (tc2x - rk_hit_gtr200_xt->at(tid)) * vd * tan;	
//		double cry2   = localy;
//		return TVector3(crx2, cry2, 0);
//	}
//	else if(l == 3){//gtr300
////		double localx     = rk_hit_gtr300_tx2->at(tid);//should be gtx?
////		double localy     = rk_hit_gtr300_ty->at(tid);
//		double localx     = rk_hit_gtr300_cogx->at(tid);//should be gtx?
//		double localy     = rk_hit_gtr300_cogy->at(tid);
//		double vd     = 0.018;
//		double gap    = 1.5;
//		double tan   = (double)rk_fit_gtr300_mom_gx->at(tid)/rk_fit_gtr300_mom_gz->at(tid);
//		double tcor   = 1.4*exp(-0.5*pow((localx+115)/14,2))+6e-4*(localy*localy)/6.0;
//		double cent0  = 150;
//		double tc3x   = cent0 + (gap - tcor)/vd;
//		double crx3   = localx - (tc3x - rk_hit_gtr300_xt4->at(tid)) * vd * tan;	
////		double crx3   = localx - (tc3x - rk_hit_gtr300_xt->at(tid)) * vd * tan;	
//		double cry3   = localy;
//		return TVector3(crx3, cry3, 0);
//	}
	

//  -------- for a test  ---------- ///
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
	return cor_pos;
}

//		double vd = 0.010;//drift velocity
//		double gap = 1.5; // drift gap [mm]
//		double projx2 = rk_fit_gtr200_x->at(tid);
//		double projy2 = rk_fit_gtr200_y->at(tid);
//		double tcor2 = -0.8*(exp(-0.5*pow((projx2+75)/15,2))+exp(-0.5*pow((projx2-55)/20,2)))+4e-4*(projy2*projy2/4);
//		double tc2 = 150+(gap-tcor2) / vd;
//		double cx2 = rk_hit_gtr100_x->at(tid)+ (tc2 - gtr)
	

