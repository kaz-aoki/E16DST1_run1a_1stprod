//#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1.hh"
#include "E16ANA_GTRAnalyzerMaker.hh"
#include "OnlineGTRUtility.h"
//#include "E16ANA_GTRPedestal.h"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_StraightTrackNameSpace.hh"

////double E16ANA_GTRLocalX(double lorentz_angle_calib_param, int layer_id, int type, int channel_id) {
//  double strip_pitch;
//  double position_start;
//  int n_strip_x = E16DST_DST1Constant::nstrips_x[layer_id]; 
//  int n_strip_y = E16DST_DST1Constant::nstrips_y[layer_id]; 
//  double inverted;
//  if (type == E16DST_DST1Constant::kIsX) {
//    strip_pitch = E16DST_DST1Constant::gtr_strip_pitch_x;
//	  position_start = -(double)n_strip_x / 2.0 * strip_pitch + strip_pitch * 0.5 + lorentz_angle_calib_param;
//    inverted = +1.0;
//  } else if (type == E16DST_DST1Constant::kIsY) {
//    strip_pitch = E16DST_DST1Constant::gtr_strip_pitch_y;
//    position_start = -(double)n_strip_y / 2.0 * strip_pitch + strip_pitch * 0.5;
//    inverted = -1.0;
//  } else if (type == E16DST_DST1Constant::kIsYb) {
//    strip_pitch = E16DST_DST1Constant::gtr_strip_pitch_y;
//    position_start = -(double)n_strip_y / 2.0 * strip_pitch + strip_pitch * 0.5;
//    inverted = +1.0;
//  }
//  return (channel_id * strip_pitch + position_start) * inverted;
//}

int E16DST_DST1GTRFactory_ExOneGTR(E16DST_DST0Detector<E16DST_DST0GTRHit>& dst0_hits, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster>* gtr1, E16ANA_GTRcalibPedestal &gtrped,
                          const std::array<double, 3>& lonrentz_angle_calib_params, const int removed_layer) {
    auto& dst1_hits = gtr1->Hits();
    auto& dst1_clusters = gtr1->Clusters();
    static bool isFirst = true;
	int n_fake_cl_x = 20 * removed_layer;
	int n_fake_cl_y = 10 * removed_layer;
	static E16ANA_GTRAnalyzerMaker *gtr_analyzers;
    if(isFirst){
		E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();
		E16ANA_GTRcalibParams gtr_params;
		gtr_params.ReadCalibData(calib.CurrentRunID());
    	gtr_analyzers = new E16ANA_GTRAnalyzerMaker(gtr_params);	
        for(int mid=100; mid<= 110; mid++){
            for(int lid = 0; lid < 3 ; lid ++){
                E16ANA_GTRAnalyzer2 *analyzer = gtr_analyzers->Chamber(mid, lid);
                int n_strips = analyzer->GetNumberOfStrips();
                for(int strip_id = 0; strip_id < n_strips; strip_id++){
                    double ped = gtrped.GetPedestal(mid, lid, strip_id).Value();
                    double sigma = gtrped.GetPedestal(mid, lid, strip_id).Sigma();
                    analyzer->SetPedestal(strip_id, ped);
                    analyzer->SetPedestalSigma(strip_id, sigma);
                }
            }     
        }
        isFirst = false;
        std::cout << "GTR Analyzer parameters are set :: should be called ONLY ONCE " << std::endl;
    }
    int noh = dst0_hits.NumberOfHits();
    for (auto &a : gtr_analyzers->analyzer_map){
        a.second->Clear();
    }    
    for(int i =0; i < noh ; i++){
        E16DST_DST0GTRHit &hit = dst0_hits.Hit(i);
        int mid = hit.ModuleID();
//		if(mid ! = 107) continue;
		  if(mid > 200) continue;
        int lid = hit.LayerID();
        int sid = hit.StripID();
        gtr_analyzers->analyzer_map[OnlineGTR::IDs(mid, lid).value64]->SetFadc(sid, hit.Waveform());
    }
    for(auto &a : gtr_analyzers->analyzer_map){
//        a.second->AnalyzeV0();
        a.second->AnalyzeV1();
    }

    int dst1_clusters_size = 0;
    int dst1_hits_size = 0;
    for(int mid=100; mid<110; mid++){
        for(int lid=0; lid<3; lid++){
            std::vector<E16ANA_GTRAnalyzedStripHit> &hitsx = gtr_analyzers->Chamber(mid,lid)->GetStripX()->GetAnalyzedHits();
            std::vector<E16ANA_GTRAnalyzedStripHit> &hitsy = gtr_analyzers->Chamber(mid,lid)->GetStripY()->GetAnalyzedHits();
            std::vector<std::reference_wrapper<std::vector<E16ANA_GTRAnalyzedStripHit>>> v_anahits;
            v_anahits.clear();
            v_anahits.push_back(hitsx);
            v_anahits.push_back(hitsy);
            if(lid == 0){
                std::vector<E16ANA_GTRAnalyzedStripHit> &hitsyb = static_cast<E16ANA_GTR100Analyzer *>(gtr_analyzers->Chamber(mid, 0))->GetStripYb()->GetAnalyzedHits();
                v_anahits.push_back(hitsyb); }
            for(int t=0; t < v_anahits.size(); t++){//t == 0, 1, 2 means X, Y, Yb respectively
                dst1_clusters_size += v_anahits[t].get().size();
                for(int i =0; i<v_anahits[t].get().size();i++){
                    dst1_hits_size += v_anahits[t].get()[i].NumHit();        
                }
            }
        }
    }
    dst1_hits.resize(dst1_hits_size);
    //dst1_clusters.resize(dst1_clusters_size);
    if(removed_layer == 1){
    	dst1_clusters.resize(dst1_clusters_size+(n_fake_cl_x + n_fake_cl_y * 2)*6);
	}
	else {
    	dst1_clusters.resize(dst1_clusters_size+(n_fake_cl_x + n_fake_cl_y)*6);
	}
    //dst1_clusters.resize(dst1_clusters_size+61);
    int cl_id = 0;// cluster id 
    int h_id = 0;// hit id
    for(int mid=100; mid < 110 ; mid++){
        for(int lid=0; lid< 3 ; lid++){
            auto lorentz_angle_calib_param = lonrentz_angle_calib_params[lid];
            std::vector<E16ANA_GTRAnalyzedStripHit> &hitsx = gtr_analyzers->Chamber(mid,lid)->GetStripX()->GetAnalyzedHits();
            std::vector<E16ANA_GTRAnalyzedStripHit> &hitsy = gtr_analyzers->Chamber(mid,lid)->GetStripY()->GetAnalyzedHits();
            std::vector<std::reference_wrapper<std::vector<E16ANA_GTRAnalyzedStripHit>>> v_anahits;
            v_anahits.clear();
            v_anahits.push_back(hitsx);
            v_anahits.push_back(hitsy);
            if(lid == 0){
                std::vector<E16ANA_GTRAnalyzedStripHit> &hitsyb = static_cast<E16ANA_GTR100Analyzer *>(gtr_analyzers->Chamber(mid, 0))->GetStripYb()->GetAnalyzedHits();
                v_anahits.push_back(hitsyb);
            }
            std::array<std::vector<int16_t>, 3>  t_hit_indexs;
			std::vector<int16_t> hit_orders;
            std::array<int16_t, 3> indexs = {0,0,0};
//            t_hit_indexs[0].clear();
//            t_hit_indexs[1].clear();
//            t_hit_indexs[2].clear();
            for(int t=0; t < v_anahits.size(); t++){//t == 0, 1, 2 means X, Y, Yb respectively, namely, type
                for(int i =0; i<v_anahits[t].get().size();i++){
                    t_hit_indexs[0].clear();
                    t_hit_indexs[1].clear();
                    t_hit_indexs[2].clear();
					hit_orders.clear();
                    E16ANA_GTRAnalyzedStripHit &anahit = v_anahits[t].get()[i];
                    for(int j=0; j<anahit.NumHit(); j++){
                        E16DST_DST1GTRHit &h = dst1_hits[h_id];
                        h.SetInvalid();
                        h.SetIds(mid, anahit.StripID(j));
                        h.SetLayerId(lid);
                        h.SetTiming(anahit.StripTiming(j));
                        h.SetPeakHeight(anahit.StripCharge(j));
                        h.SetTot(anahit.StripTimeOverThreshold(j));
                        h.SetType(t);
                        h.SetLocalX(E16ANA_StraightTrackNameSpace::E16ANA_GTRLocalX(lorentz_angle_calib_param, lid, t, anahit.StripID(j)));
						std::vector<float> fadc;
            //            std::cout << "strip charge = " << anahit.StripCharge(j) << std::endl;
						for(int k=0; k < anahit.StripFadc(j).size(); k++){//24 sampling
							fadc.push_back((anahit.StripFadc(j))[k]);
			//				std::cout << "stdipID, anahit fadc = "  << anahit.StripID(j) <<", " <<   anahit.StripFadc(j)[k] << std::endl;
                        }
						h.SetWaveForm(fadc);
						fadc.clear();

//			h.SetRiset(anahit.Riset());
//			h.SetMtot(anahit.Mtot());
                        //t_hit_indexs[t].push_back(indexs[t]);
//			h.SetPeakt(anahit.StripPeakt(j));
  //                      h.SetEd(anahit.StripEd(j));
    //                    h.SetSt(anahit.StripSt(j));
                        hit_orders.push_back(h_id);
                        h_id++;
                        indexs[t]++;
                    }
                    E16DST_DST1GTRCluster &cl = dst1_clusters[cl_id];
                    cl.SetInvalid();
                    cl.SetModuleId(mid);
                    cl.SetLayerId(lid);
                    //std::cout << "t, t_hit_indexs[t] = " << t_hit_indexs[t].size() << std::endl;
                    //std::cout << "hit size = " << cl.NumHits() << std::endl;
                    //cl.SetHitOrders(t_hit_indexs[t]);
                    cl.SetHitOrders(hit_orders);
		    //std::cout << "hit size after = " << cl.NumHits() << std::endl;
                    cl.SetType(t);
                    cl.SetMaxPeakCh(anahit.MaxStripId());
                    cl.SetMaxPeakHeight(anahit.MaxValue());
                    cl.SetTiming(anahit.Timing());
                    cl.SetPeakSum(anahit.ClusterCharge());//cluster charge
                    //std::cout << "cluster charge = " << anahit.ClusterCharge() << std::endl;//cluster charge
                    cl.SetCogPos(anahit.CogHit());
//					std::cout << "cl cog = " << anahit.CogHit() << std::endl;
		    /*
                    if(isnan(anahit.TdcHit())){
                    }
                    else{
                        cl.SetTdcPos(anahit.TdcHit());
                    }
		    */
		    
		    cl.SetTiming2(anahit.Timing2());
                    cl.SetTanTheta(anahit.TanTheta());
		    cl.SetTdcPos(anahit.TdcHit());
                    cl.SetTdcPos2(anahit.TdcHit2());
                    cl.SetTanTheta2(anahit.TanTheta2());
	//	    cl.SetRiset(anahit.Riset());
      //              cl.SetMtot(anahit.Mtot());

		    int nhit = anahit.NumCls();
		    for(int i=0;i<nhit;i++){
        //              cl.SetCTiming(anahit.CTiming(i));
          //            cl.SetCPos(anahit.CPos(i));
		    }
		    //printf("%d th, %d , mid:%d, lay:%d, nhit:%d, nhit2:%d,cog:%f, tdc:%f, theta:%f, time1:%f, time2:%f \n",i,t,mid,lid,
		    //	   anahit.NumHit(),nhit,anahit.CogHit(),anahit.TdcHit(),anahit.TanTheta(),anahit.Timing(),anahit.Timing2());

                    cl_id++;
                }       
            }   
        }
    }


    std::vector<int16_t> thit_orders;    
    thit_orders.clear();
    thit_orders.push_back(0);thit_orders.push_back(1);thit_orders.push_back(2);
    for(int mid=102; mid < 109 ; mid++){
		if(mid == 105) continue;
    	for(int k=0; k < n_fake_cl_x ; k++){
			E16DST_DST1GTRCluster &cl = dst1_clusters[cl_id];
			double lx = -1 * (48*removed_layer) +5*k;
			cl.SetInvalid();
			cl.SetModuleId(mid);
			cl.SetLayerId(removed_layer - 1);
			cl.SetHitOrders(thit_orders);
			cl.SetType(0);
			cl.SetMaxPeakCh(1);
			cl.SetMaxPeakHeight(99999);
			cl.SetTiming(820);
			cl.SetPeakSum(99999);//cluster charge
			cl.SetCogPos(lx);
			cl.SetTiming2(820);
			cl.SetTanTheta(0);
			cl.SetTdcPos(lx);
			cl.SetTdcPos2(lx);
			cl.SetTanTheta2(0);
			cl_id++;
      	}

	    for(int k=0; k < n_fake_cl_y ; k++){
			E16DST_DST1GTRCluster &cl = dst1_clusters[cl_id];
			double lx =  -1 * (48 * removed_layer) +10*k;
			cl.SetInvalid();
			cl.SetModuleId(mid);
			cl.SetLayerId(removed_layer - 1);
			cl.SetHitOrders(thit_orders);
			cl.SetType(1);
			cl.SetMaxPeakCh(1);
			cl.SetMaxPeakHeight(99999);
			cl.SetTiming(820);
			cl.SetPeakSum(99999);//cluster charge
			cl.SetCogPos(lx);
			cl.SetTiming2(820);
			cl.SetTanTheta(0);
			cl.SetTdcPos(lx);
			cl.SetTdcPos2(lx);
			cl.SetTanTheta2(0);
			cl_id++;
	      }

// for Yb
		if(removed_layer ==1){
  		for(int k=0; k < n_fake_cl_y ; k++){
			E16DST_DST1GTRCluster &cl = dst1_clusters[cl_id];
			double lx =  -1 * (48 * removed_layer) +10*k;
			cl.SetInvalid();
			cl.SetModuleId(mid);
			cl.SetLayerId(removed_layer - 1);
			cl.SetHitOrders(thit_orders);
			cl.SetType(2);
			cl.SetMaxPeakCh(1);
			cl.SetMaxPeakHeight(99999);
			cl.SetTiming(820);
			cl.SetPeakSum(99999);//cluster charge
			cl.SetCogPos(lx);
			cl.SetTiming2(820);
			cl.SetTanTheta(0);
			cl.SetTdcPos(lx);
			cl.SetTdcPos2(lx);
			cl.SetTanTheta2(0);
			cl_id++;
	     }
		}
    }
    
    return sizeof(E16DST_DST1GTRHit) * dst1_hits_size + sizeof(E16DST_DST1GTRCluster) * (dst1_clusters_size+(n_fake_cl_x + n_fake_cl_y)*6);
    //return sizeof(E16DST_DST1GTRHit) * dst1_hits_size + sizeof(E16DST_DST1GTRCluster) * (dst1_clusters_size);
}
