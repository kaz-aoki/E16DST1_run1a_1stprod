#include "GTR/E16ANA_STRAnalyzer.h"

E16ANA_STRAnalyzer::E16ANA_STRAnalyzer(){
}
E16ANA_STRAnalyzer::~E16ANA_STRAnalyzer(){
}

E16ANA_STRAnalyzerOfWire::E16ANA_STRAnalyzerOfWire(){
}
E16ANA_STRAnalyzerOfWire::~E16ANA_STRAnalyzerOfWire(){
}


void E16ANA_STRAnalyzer::TrackCandidateSearchXZ_OneModule(E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> &ssd_detector, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> &gtr_detector){
    int n_gtr_layers = E16DST_DST1Constant::n_gtr_layers;
    std::vector<TVector2> v_fit_samples;
	std::vector<double> sigma_x = {0.2,0.2,0.2};
	for(int m=100; m<110; m++){
        std::vector<E16DST_DST1GTRCluster*> &clusters0 = gtr_detector.ClusterPtrs(m, 0, 0);//module, layer, type
        std::vector<E16DST_DST1GTRCluster*> &clusters1 = gtr_detector.ClusterPtrs(m, 1, 0);//module, layer, type
        std::vector<E16DST_DST1GTRCluster*> &clusters2 = gtr_detector.ClusterPtrs(m, 2, 0);//module, layer, type
		for(int i=0; i < cluster0.size(); i++){
			for(int j=0; j < cluster1.size(); j++){
				for(int k=0; k < cluster2.size(); k++){
					std::vector<E16DST_DST1GTRCluster*> cls;
					cls.clear();
					cls.push_back(cluster0[i]);
					cls.push_back(cluster1[j]);
					cls.push_back(cluster2[k]);
					rot_pos.clear();
					v_fit_samples.clear();
					for(int l=0; l < n_gtr_layers; l++){
						rot_pos.push_back(TVector3(TVector3(cls[l].ClobalPos(geom).rotateY(-phi))));
						v_fit_samples.push_back(TVector2(tor_pos[l].X(), rot_pos[l].z()));
					}	
					std::vector<long double> &&v_results1 = LeastSquareMethod(v_fit_samples, sigma_x);
					std::shared_ptr<E16ANA_XZTrackCandidate> trk = std::make_shared<E16ANA_XZTrackCandidate<();
	
			    	v_results1.clear();
				}
			}	
	
		}    
	
	cluster0.clear();
	cluster1.clear();
	cluster2.clear();
    }

}



void E16ANA_STRAnalyzer::TrackCandidateSearchYR_OneModule( E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> &gtr_detector){	int n_gtr_layers = E16DST_DST1Constant::n_gtr_layers;
//void StraightTrackAnalyzerV0::YRStraightAnalyze(std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_yhits0, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_yhits0b, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_yhits1, std::vector<E16ANA_GTRAnalyzedStripHit> &gtr_yhits2, int mid, E16ANA_GeometryV2 *geom_v2){
//    int kawama_module = ModuleID_2020to2013_33(mid);
//    double phi = GetGTRModulePhi(geom_v2, mid);
//	std::vector<double> sigma_y = {0.3, 0.3, 0.3};	
//	std::vector<TVector2> v_fit_samples; 
//	std::vector<G4ThreeVector> l_hitpos;
//	std::vector<G4ThreeVector> g_hitpos;
//	std::vector<G4ThreeVector> rot_pos;
//    G4ThreeVector pos_100 = ((geom_v2->GTR(kawama_module, 0)->GetGPos(G4ThreeVector(0,0,0))));
//	double r100_2 = pos_100.x()*pos_100.x() + pos_100.y()*pos_100.y() + pos_100.z()*pos_100.z();
//	double r100  = sqrt(r100_2);
//    G4ThreeVector pos_300 = ((geom_v2->GTR(kawama_module, 2)->GetGPos(G4ThreeVector(0,0,0))));
//	double r300_2 = pos_300.x()*pos_300.x() + pos_300.y()*pos_300.y() + pos_300.z()*pos_300.z();
//	double r300  = sqrt(r300_2);
//    double r3000 = r300 * 10;
//	for(int i = 0; i<(int)gtr_yhits0.size(); i++){
//		for(int j = 0; j<(int)gtr_yhits1.size(); j++){
//			for(int k = 0; k<(int)gtr_yhits2.size(); k++){
//                std::vector<std::reference_wrapper<E16ANA_GTRAnalyzedStripHit>> hits;
//                hits.clear();
//                hits.push_back(gtr_yhits0[i]);
//                hits.push_back(gtr_yhits1[j]);
//                hits.push_back(gtr_yhits2[k]);
//                l_hitpos.clear();
//                g_hitpos.clear();
//                rot_pos.clear();
//                v_fit_samples.clear();
//                for(int l = 0; l <3; l++){
//                    l_hitpos.push_back(G4ThreeVector(0, hits[l].get().CogHit(), 0));
//                    g_hitpos.push_back(G4ThreeVector(geom_v2->GTR(kawama_module, l)->GetGPos(l_hitpos[l])));
//                    rot_pos.push_back(G4ThreeVector(g_hitpos[l].rotateY(phi)));
//                    v_fit_samples.push_back(TVector2(rot_pos[l].x(), rot_pos[l].y()));
//                }
//  //              std::cout << "v fir sample = " << v_fit_samples[2].Y() << std::endl;
//				std::vector<long double> &&v_results = LeastSquareMethod(v_fit_samples, sigma_y );//return chi2, a,b (a+bx)
////                std::cout << "v result" << v_results[1] << std::endl;
//				if(v_results[0] < th_chi2_y){
//                    std::shared_ptr<E16ANA_YTrackCandidate> trk = std::make_shared<E16ANA_YTrackCandidate>();
////    				trk->SetInvalid();
//					trk->SetModuleID(mid);
////					y_trk_cand[index].SetChi2(v_results[0]);
//                    trk->SetChi2(v_results[0]);
//					trk->SetTgtPos(v_results[1]);
////                    std::cout << "v_results = " << v_results[1] << std::endl;
//					double a = v_results[1];
//					double b = v_results[2];
//					double zpos_x_at100 = b*(r100) + a;
//    				double zpos_x_at300 = b*r300 + a;
//                    double zpos_x_at3000 = b*r3000 + a;
////					std::cout << "z pos , r" << zpos_x_at300 << "  : " << r300 << std::endl;
////					std::cout << "local y" << hy2.CogHit() << "  : " << r300 << std::endl;
//				    TVector2 ref_pt0(r100, zpos_x_at100);
//				    TVector2 ref_pt1(r300, zpos_x_at300);
//				    TVector2 ref_pt2(r3000, zpos_x_at3000);
//				    trk->SetPt0OnTrack(ref_pt0);
//				    trk->SetPt1OnTrack(ref_pt1);
//				    trk->SetPt2OnTrack(ref_pt2);
////                    trk.SetXIntercept(-v_results[1]/v_results[2]);
////					std::cout << "tgt  = " << v_results[1] << std::endl;
////					std::cout << "hy2 bef = " << &hy2 << std::endl;
//					trk->SetYHit100(&hits[0].get());
//					trk->SetYHit200(&hits[1].get());
//					trk->SetYHit300(&hits[2].get());
//                    trk->SetID100Hit(i);
//                    trk->SetID200Hit(j);
//                    trk->SetID300Hit(k);
//                    y_trk_cands.push_back(trk);
//  			//	std::cout << "target height " << v_results[1] << std::endl;
////					trk->SetResidual100(v_results2[3]);
////					trk->SetResidual200(v_results2[4]);
////					trk->SetResidual300(v_results2[5]);
//						//	std::cout << xz_trk_cand[index].Chi2() << std::endl;		
//				}
//				v_results.clear();
//                //std::cout << "v_results after clear= " << v_results[1] << std::endl;
//			}
//        }
//    }
//	for(int i = 0; i<(int)gtr_yhits0b.size(); i++){
//		for(int j = 0; j<(int)gtr_yhits1.size(); j++){
//            for(int k =0; k<(int)gtr_yhits2.size(); k++){
//                std::vector<std::reference_wrapper<E16ANA_GTRAnalyzedStripHit>> hits;
//                hits.clear();
//                hits.push_back(gtr_yhits0b[i]);
//                hits.push_back(gtr_yhits1[j]);
//                hits.push_back(gtr_yhits2[k]);
//                l_hitpos.clear();
//                g_hitpos.clear();
//                rot_pos.clear();
//                v_fit_samples.clear();
//                for(int l = 0; l <3; l++){
//                    l_hitpos.push_back(G4ThreeVector(0, hits[l].get().CogHit(), 0));
//                    g_hitpos.push_back(G4ThreeVector(geom_v2->GTR(kawama_module, l)->GetGPos(l_hitpos[l]))); //                    rot_pos.push_back(G4ThreeVector(g_hitpos[l].rotateY(phi)));
//                    v_fit_samples.push_back(TVector2(rot_pos[l].x(), rot_pos[l].y()));
//                }
//				std::vector<long double> &&v_results = LeastSquareMethod(v_fit_samples, sigma_y );//return chi2, a,b (a+bx)
//            //    std::cout << "v result" << v_results[1] << std::endl;
//				if(v_results[0] < th_chi2_y){
//                    std::shared_ptr<E16ANA_YTrackCandidate> trk = std::make_shared<E16ANA_YTrackCandidate>();
//    				trk->SetInvalid();
//					trk->SetModuleID(mid);
////					y_trk_cand[index].SetChi2(v_results[0]);
//                    trk->SetChi2(v_results[0]);
//					trk->SetTgtPos(v_results[1]);
//					double a = v_results[1];
//					double b = v_results[2];
//					double zpos_x_at100 = b*(r100) + a;
//    				double zpos_x_at300 = b*r300 + a;
//                    double zpos_x_at3000 = b*r3000 + a;
////					std::cout << "z pos , r" << zpos_x_at300 << "  : " << r300 << std::endl;
////					std::cout << "local y" << hy2.CogHit() << "  : " << r300 << std::endl;
//				    TVector2 ref_pt0(r100, zpos_x_at100);
//				    TVector2 ref_pt1(r300, zpos_x_at300);
//				    TVector2 ref_pt2(r3000, zpos_x_at3000);
//				    trk->SetPt0OnTrack(ref_pt0);
//				    trk->SetPt1OnTrack(ref_pt1);
//				    trk->SetPt2OnTrack(ref_pt2);
////                    trk.SetXIntercept(-v_results[1]/v_results[2]);
////					std::cout << "tgt  = " << v_results[1] << std::endl;
////					std::cout << "hy2 bef = " << &hy2 << std::endl;
//					trk->SetYHit100(&hits[0].get());
//					trk->SetYHit200(&hits[1].get());
//					trk->SetYHit300(&hits[2].get());
//                    trk->SetID100Hit(i);
//                    trk->SetID200Hit(j);
//                    trk->SetID300Hit(k);
//                    y_trk_cands.push_back(trk);
//
//                }
//				v_results.clear();
//            }
//		}
//	}
/*
	bool i_table[yhits0.size()] = {};
	bool j_table[yhits1.size()] = {};
	bool k_table[yhits2.size()] = {};
	//bool l_tab[ssd_hits.size()] = {};
	std::fill_n(i_table, yhits0.size(), 0);
	std::fill_n(j_table, yhits1.size(), 0);
	std::fill_n(k_table, yhits2.size(), 0);
	//std::fill_n(l_tab, ssd_hits.size(), 0);
    //sort by chi2, and if the hits are overlaped, the track is erased 
    std::sort(y_trk_cand.begin(), y_trk_cand.end(), E16ANA_YTrackCandidate::CompareTrackFunctor());
	std::vector<E16ANA_YTrackCandidate>::const_iterator iter = y_trk_cand.begin();
    while(iter != y_trk_cand.end()){
		if(i_table[(*iter).ID100Hit()] == 0 && j_table[(*iter).ID200Hit()] == 0 && k_table[(*iter).ID300Hit()] == 0 ){
            i_table[(*iter).ID100Hit()] = 1;
			j_table[(*iter).ID200Hit()] = 1; 
			k_table[(*iter).ID300Hit()] = 1; 
            ++iter;
        }
        else{
            iter = y_trk_cand.erase(iter);
 //           std::cout << "a duplicated track Y is erased !" << std::endl;
        }
    }
*/
}




std::vector<long double> StraightTrackAnalyzerV0::LeastSquareMethod(std::vector<TVector2> &tv_v_pos, std::vector<double> sigma_x){
	int v_size = tv_v_pos.size();
	int v_sig_size = sigma_x.size();
	if(v_size != sigma_x.size()){
			std::cout << " sizes of vectors btw positions and sigmas are different  " << std::endl;
			std::cout << "size of pos vec = " << v_size << std::endl;
			std::cout << "size of sigma vec = " << v_sig_size << std::endl;}
	double wt=0, t=0, sx=0, sy=0, st2=0, ss = 0, sxoss = 0;
	double a=0, b=0, siga=0, sigb=0, chi2=0;//a+bx
	for(int i = 0; i < v_size; i++){
		wt = 1.0 / sqr(sigma_x[i]);
		ss += wt;
		sx += tv_v_pos[i].X() * wt ;
		sy += tv_v_pos[i].Y() * wt ;
	}
	sxoss = sx/ss;
	for(int i=0; i < v_size; i++ ){
		t = (tv_v_pos[i].X() -sxoss)/sigma_x[i];
		st2 += t*t;
		b += t*tv_v_pos[i].Y()/sigma_x[i]; 
	}
	b /= st2;
	a = (sy-sx*b)/ss;
	siga = sqrt((1.0 + sx*sx/(ss*st2)/ss));
	sigb = sqrt(1.0/st2);
	chi2 = 0.0;
	for(int i=0; i < v_size; i++){
		chi2 += sqr((tv_v_pos[i].Y()- a-(b*tv_v_pos[i].X()))/sigma_x[i]);
//		q = Gammq(0.5 * (n_sample-2), 0.5* (chi2));
	}
	std::vector<long double> lst_sq_results;
	lst_sq_results.clear();
	lst_sq_results.push_back(chi2);
    //std::cout << "chi2  = " << chi2 << std::endl;
	lst_sq_results.push_back(a);
	lst_sq_results.push_back(b);
//	std::vector<double> residual;
	for(int i = 0; i<v_size; i++){
		lst_sq_results.push_back(tv_v_pos[i].Y()- a-(b*tv_v_pos[i].X()));
	}
	/*
	double residue[3] = {0, 0, 0};
	if(chi2 < th_chi2){
		for(int i = 0; i < 3; i++){
			residue[i] = tv_v_pos[i].Y()- a-(b*tv_v_pos[i].X());
		}
		h_residue[0]->Fill(residue[0]);
		h_residue[1]->Fill(residue[1]);
		h_residue[2]->Fill(residue[2]);
/		if(b == 0){
		std::cout << "b is 0 ? " << b << std::endl;}
		h_fitted_a[0]->Fill(a);
		h_fitted_b[0]->Fill(b);
	}
*/
	return lst_sq_results;
}




void E16ANA_STRAnalyzerOfWire::Make2DCrossPoint(std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> &xz_trk_cands, E16ANA_GeometryV2 *geom_v2){
    //make cross_points 
    //remove cross points made from two tracks of same module
    //leave points made from LR Tracks
	int index = 0;
//    cross_points.resize(xz_trk_cands.size()* xz_trk_cands.size());
//        std::cout << "xz track size = "<< xz_trk_cands.size() << std::endl;
    std::vector<std::pair<int, int>> p;
    p.clear();
	if(xz_trk_cands.size() != 0){
		std::cout << "size of tracks before making crosspoints = " << xz_trk_cands.size() << std::endl;
    }
	for(int i=0; i<xz_trk_cands.size();i++){
        if(xz_trk_cands.size() < 2) continue;
        std::shared_ptr<E16ANA_XZTrackCandidate> track1 = xz_trk_cands[i];
            for(int j=i; j<xz_trk_cands.size(); j++){
                if(i == j) continue;
                std::shared_ptr<E16ANA_XZTrackCandidate> track2 = xz_trk_cands[j];
				std::cout << "trk z 1 = " << track1->TgtZ() << std::endl;
				std::cout << "trk z 2 = " << track2->TgtZ() << std::endl;
//                if(track1->ModuleID() == track2->ModuleID() ) continue;
//                if( signbit(track1->ModuleID() -105) == signbit(track2->ModuleID()-105 ) ) continue;
                if(fabs(track1->TgtZ() - track2->TgtZ()) <10.0 && fabs(track1->TgtZ() - track2->TgtZ()) != 0.0){
                    std::vector<double> && result_calc_cross = CalcCrossPoint2D(track1, track2);//X, Z, min_distance from target
    				if(result_calc_cross[2] < 10 && isnan(result_calc_cross[0]) == 0){
                    //std::cout << result_calc_cross[0] << std::endl;
//	    			if(fabs(track1.TgtZ()) < 10 && fabs(track2.TgtZ()) < 10 ){
                        bool isFirst = true;
                        std::pair<int, int> temp(track1->TrackID(), track2->TrackID());
                        for(int k = 0; k < p.size() ; k++){
                            if(p[k] == temp){
                                isFirst  = false;
                            }
                        }
                        if(isFirst){
                            p.push_back(temp);
                            std::shared_ptr<E16ANA_XZCrossPoint> cp = std::make_shared<E16ANA_XZCrossPoint>();
    	                    cp->SetTrack1ID(i);
	                        cp->SetTrack2ID(j);
	                        cp->SetCoordinateX(result_calc_cross[0]);
        	                cp->SetCoordinateZ(result_calc_cross[1]);
        	                cp->SetDistance(result_calc_cross[2]);
				    	    cp->SetTgtZ1(track1->TgtZ());
    		    			cp->SetTgtZ2(track2->TgtZ());
	        				cp->SetXZTrack1(track1);
	    	    			cp->SetXZTrack2(track2);
                            cross_points.push_back(cp);
    			    		index++;
                            }
                    }
                result_calc_cross.clear();
                }
            }
    }
// ----------------------- NOT allowed using duplicated tracks ----------------------------//
#if 1
    if(cross_points.size() != 0){
        std::cout << "n of cross points before  duplication cut  " << cross_points.size() << std::endl;
    }
    if(cross_points.size() > 0 && cross_points.size() < 5){
   	    bool i_table[xz_trk_cands.size()] = {};
        for(int l=0;l<xz_trk_cands.size(); l++){
   	        i_table[l] = 0;
        }
        std::sort(cross_points.begin(), cross_points.end(), E16ANA_XZCrossPoint::CompareCrossFunctor());
       	std::vector<std::shared_ptr<E16ANA_XZCrossPoint>>::const_iterator iter = cross_points.begin();
        std::vector<std::shared_ptr<E16ANA_XZCrossPoint>> tmp;
        tmp.reserve(index);
        while(iter != cross_points.end()){
   		if(i_table[(*iter)->Track1ID()] == 0 && i_table[(*iter)->Track2ID()] ==0
               && (*iter)->Distance() < 10.0){
               i_table[(*iter)->Track1ID()] = 1;
               i_table[(*iter)->Track2ID()] = 1;
               tmp.push_back((*iter));
               ++iter; 
           }
           else {
               ++iter;   
           }
        }
        cross_points = std::move(tmp);
        std::cout << "n of cross points after duplication cut  " << cross_points.size() << std::endl;
    }
#endif
}

void StraightTrackAnalyzerOfWireV1::SearchSSDHit(std::vector<std::shared_ptr<E16ANA_XZCrossPoint>> &cps, std::vector<std::reference_wrapper<std::vector<E16ANA_SSDAnalyzedStripHit>>> &v_shits, E16ANA_GeometryV2 *geom_v2){
    std::vector<G4ThreeVector> l_hitpos;
    std::vector<G4ThreeVector> g_hitpos;
    std::vector<G4ThreeVector> rot_pos;
    std::vector<TVector2> v_fit_samples;
    std::vector<G4ThreeVector> l_ssd_hitpos;
    std::vector<G4ThreeVector> g_ssd_hitpos;
    std::vector<G4ThreeVector> rot_ssd_pos;
    std::vector<double> sigma_x = {0.1, 0.1, 0.1};//gtr0,1, 2 
    std::vector<double> sigma_x2 = {0.2, 0.2, 0.2, 0.1};//gtr0,1, 2 ssd
    int index = 0;
    for(int i=0; i<cps.size(); i++){
        std::shared_ptr<E16ANA_XZTrackCandidate> t1 = cps[i]->GetXZTrackCandidate1();
        std::shared_ptr<E16ANA_XZTrackCandidate> t2 = cps[i]->GetXZTrackCandidate2();
        std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> ts;
        ts.clear();
        ts.push_back(t1);
        ts.push_back(t2);
        for(int t=0; t<ts.size(); t++){
        std::vector<E16ANA_SSDAnalyzedStripHit> &v_shit = v_shits[ts[t]->ModuleID()-100];
        l_hitpos.clear();
        g_hitpos.clear();
        rot_pos.clear();
        v_fit_samples.clear();
        int kawama_module = ModuleID_2020to2013_33(ts[t]->ModuleID());
        double phi = GetGTRModulePhi(geom_v2, ts[t]->ModuleID());
        l_hitpos.push_back(G4ThreeVector(ts[t]->GetXHit100()->CogHit(), 0, 0));
        l_hitpos.push_back(G4ThreeVector(ts[t]->GetXHit200()->CogHit(), 0, 0));
        l_hitpos.push_back(G4ThreeVector(ts[t]->GetXHit300()->CogHit(), 0, 0));
        for(int l=0; l<l_hitpos.size(); l++){
            g_hitpos.push_back(G4ThreeVector(geom_v2->GTR(kawama_module, l)->GetGPos(l_hitpos[l])));
            rot_pos.push_back(G4ThreeVector(g_hitpos[l].rotateY(phi)));
            v_fit_samples.push_back(TVector2(rot_pos[l].x(), rot_pos[l].z()));
        }
        for(int j = 0; j<v_shit.size() ; j++){
            E16ANA_SSDAnalyzedStripHit &h = v_shit[j];
            l_ssd_hitpos.clear();
            g_ssd_hitpos.clear();
            rot_ssd_pos.clear();
            l_ssd_hitpos.push_back(G4ThreeVector(h.CogHit(), 0, 0));
            g_ssd_hitpos.push_back(G4ThreeVector(geom_v2->SSD(kawama_module, 0)->GetGPos(l_ssd_hitpos[0])));
            rot_ssd_pos.push_back(G4ThreeVector(g_ssd_hitpos[0].rotateY(phi)));
            TVector2 rot_ssd = TVector2(rot_ssd_pos[0].x(), rot_ssd_pos[0].z());
            std::vector<long double> &&v_results2 = LeastSquareMethod(v_fit_samples, sigma_x);
//            v_fit_samples.push_back(TVector2(rot_ssd_pos[0].x(), rot_ssd_pos[0].z()));
//            std::vector<long double> &&v_results2 = LeastSquareMethod(v_fit_samples, sigma_x2);
//            v_fit_samples.pop_back();
            if(v_results2[0] < 50){
                std::shared_ptr<E16ANA_XZTrackCandidate> trk = std::make_shared<E16ANA_XZTrackCandidate>();
                trk->SetID100Hit(ts[t]->ID100Hit());
	           	trk->SetID200Hit(ts[t]->ID200Hit());
                trk->SetID300Hit(ts[t]->ID300Hit());
				trk->SetIDSSDHit(j);
        	    trk->SetModuleID(ts[t]->ModuleID());
		        trk->SetChi2(v_results2[0]);
		        trk->SetTgtZ(ReconstructTgtPosBeforeVertex(v_results2[1], v_results2[2], phi, kawama_module, geom_v2, trk));
                trk->SetResidualSSD((rot_ssd.Y() - (v_results2[1] + v_results2[2]*rot_ssd.X())));
//                trk->SetResidual100(v_results2[3]);
//	        	trk->SetResidual200(v_results2[4]);
//               trk->SetResidual300(v_results2[5]);
//	            trk->SetResidualSSD(v_results2[6]);
    	        trk->SetXHit100(ts[t]->GetXHit100());
	        	trk->SetXHit200(ts[t]->GetXHit200());
    	        trk->SetXHit300(ts[t]->GetXHit300());
    	        trk->SetXHitSSD(&h);
                trk->SetTrackID(index);
                xz_trks_evesel.push_back(trk);
                index++;
            }
            v_results2.clear();
        }
        }
    }
////    xz_trks_evesel.shrink_to_fit();
}


