//#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1.hh"
#include "E16ANA_GTRAnalyzerMaker.hh"
#include "OnlineGTRUtility.h"
//#include "E16ANA_GTRPedestal.h"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_StraightTrackNameSpace.hh"

using namespace E16ANA_StraightTrackNameSpace;

int E16DST_DST1GTRFactory(E16DST_DST0Detector<E16DST_DST0GTRHit>& dst0_hits, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster>* gtr1, E16ANA_GTRcalibPedestal &gtrped,
                          const std::array<double, 3>& lonrentz_angle_calib_params) {
    auto& dst1_hits = gtr1->Hits();
    auto& dst1_clusters = gtr1->Clusters();
    static bool isFirst = true;
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
        int lid = hit.LayerID();
        int sid = hit.StripID();
        gtr_analyzers->analyzer_map[OnlineGTR::IDs(mid, lid).value64]->SetFadc(sid, hit.Waveform());
    }
    for(auto &a : gtr_analyzers->analyzer_map){
//        a.second->AnalyzeV0();
        a.second->AnalyzeV1();
    }
       
	
    

// calculation of hit and cluster size 
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
                v_anahits.push_back(hitsyb);
            }
            for(int t=0; t < v_anahits.size(); t++){//t == 0, 1, 2 means X, Y, Yb respectively
                dst1_clusters_size += v_anahits[t].get().size();
                for(int i =0; i<v_anahits[t].get().size();i++){
                    dst1_hits_size += v_anahits[t].get()[i].NumHit();        
                }
            }
        }
    }
    dst1_hits.resize(dst1_hits_size);
    dst1_clusters.resize(dst1_clusters_size);

//
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
						h.SetPeakt(anahit.StripPeakt(j));
						h.SetTotEnd(anahit.StripTotEd(j));
						h.SetTotStart(anahit.StripTotSt(j));
						std::vector<float> fadc;
            //            std::cout << "strip charge = " << anahit.StripCharge(j) << std::endl;
						for(int k=0; k < anahit.StripFadc(j).size(); k++){//24 sampling
							fadc.push_back((anahit.StripFadc(j))[k]);
			//				std::cout << "stdipID, anahit fadc = "  << anahit.StripID(j) <<", " <<   anahit.StripFadc(j)[k] << std::endl;
                        }
						h.SetWaveForm(fadc);
						fadc.clear();
                        //t_hit_indexs[t].push_back(indexs[t]);
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
					cl.SetMaxRiset(anahit.MaxRiset());
					cl.SetMaxTot(anahit.MaxTot());
					cl.SetTiming3(anahit.Timing3());
					cl.SetTiming4(anahit.Timing4());
				    int nhit = anahit.NumCls();
				    for(int i=0;i<nhit;i++){
        	        	cl.SetCTiming(anahit.CTiming(i));
                    	cl.SetCPos(anahit.CPos(i));
						cl.SetCAdc1(anahit.CAdc1(i));
						cl.SetCAdc2(anahit.CAdc2(i));
						cl.SetCAdc3(anahit.CAdc3(i));
						cl.SetCAdc4(anahit.CAdc4(i));
						cl.SetCAdc5(anahit.CAdc5(i));
		    		}
					int nhit2 = anahit.NumCls2();
				    for(int i=0;i<nhit;i++){
        	        	cl.SetCTiming2(anahit.CTiming2(i));
						cl.SetCPos2(anahit.CPos2(i));
					}
					int nhit3 = anahit.NumCls3();
				    for(int i=0;i<nhit;i++){
        	        	cl.SetCTiming3(anahit.CTiming3(i));
						cl.SetCPos3(anahit.CPos3(i));
					}
					int nhit4 = anahit.NumCls4();
				    for(int i=0;i<nhit;i++){
        	        	cl.SetCTiming4(anahit.CTiming4(i));
						cl.SetCPos4(anahit.CPos4(i));
        	        	cl.SetCTiming5(anahit.CTiming5(i));
						cl.SetCPos5(anahit.CPos5(i));
					}
		    //printf("%d th, %d , mid:%d, lay:%d, nhit:%d, nhit2:%d,cog:%f, tdc:%f, theta:%f, time1:%f, time2:%f \n",i,t,mid,lid,
		    //	   anahit.NumHit(),nhit,anahit.CogHit(),anahit.TdcHit(),anahit.TanTheta(),anahit.Timing(),anahit.Timing2());

                    cl_id++;
                }       
            }   
        }
    }
    return sizeof(E16DST_DST1GTRHit) * dst1_hits_size + sizeof(E16DST_DST1GTRCluster) * dst1_clusters_size;
}
