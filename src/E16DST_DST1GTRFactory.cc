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
        //for(int mid=100; mid<= 110; mid++){
	  for(int mid=103; mid<= 107; mid++){
	  //if(mid==104) continue;
            for(int lid = 0; lid < 3 ; lid ++){
	      //if(mid==106&&lid==0) continue;
	      //if(mid==106&&lid==1) continue;
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
        std::cout << "GTR Factory :: GTR Analyzer parameters are set :: should be called ONLY ONCE " << std::endl;
    }
    int noh = dst0_hits.NumberOfHits();
    for (auto &a : gtr_analyzers->analyzer_map){
        a.second->Clear();
    }    
    for(int i =0; i < noh ; i++){
        E16DST_DST0GTRHit &hit = dst0_hits.Hit(i);
        int mid = hit.ModuleID();
	if(mid > 200) continue;
	if(mid<103)   continue;
	//if(mid==104)  continue;
	if(mid>107)   continue;
	int lid = hit.LayerID();
	int sid = hit.StripID();
	//if(mid==106&&lid==0) continue;
	//if(mid==106&&lid==1) continue;
			gtr_analyzers->analyzer_map[OnlineGTR::IDs(mid, lid).value64]->SetFadc(sid, hit.Waveform());
    	}
//	}
    for(auto &a : gtr_analyzers->analyzer_map){
//        a.second->AnalyzeV0();
       a.second->AnalyzeV1();
    }

	
    

// calculation of hit and cluster size 
    int dst1_clusters_size = 0;
    int dst1_hits_size = 0;
    //for(int mid=100; mid<110; mid++){
    for(int mid=103; mid<=107; mid++){
      //if(mid==104) continue;
        for(int lid=0; lid<3; lid++){
	  //if(mid==106&&lid==0) continue;
	  //if(mid==106&&lid==1) continue;
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
    dst1_clusters.resize(dst1_clusters_size+11);
    //dst1_clusters.resize(dst1_clusters_size);

//
    int cl_id = 0;// cluster id 
    int h_id = 0;// hit id
    //for(int mid=100; mid < 110 ; mid++){
    for(int mid=103; mid<=107; mid++){
      //if(mid==104) continue;
      for(int lid=0; lid< 3 ; lid++){
	//if(mid==106&&lid==0) continue;
	//if(mid==106&&lid==1) continue;
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
			 		     double last_totend = -1000;
			 			  double max_tot  = -1000;//241022
			 			  double min_tot  = 1000;//241022
			 			  double min_rt   = 1000;//241022
			 			  double max_rt   = -1000;//241022
			 			  double last_st  = -1000;//241022
						  double min_adc = 99990;//241022
                    E16ANA_GTRAnalyzedStripHit &anahit = v_anahits[t].get()[i];
                    for(int j=0; j<anahit.NumHit(); j++){
		      				E16DST_DST1GTRHit &h = dst1_hits[h_id];
		      				h.SetInvalid();
                        h.SetIds(mid, anahit.StripID(j));
                        h.SetLayerId(lid);
                        h.SetModId(mid);
                        h.SetTiming(anahit.StripTiming(j));
                        h.SetPeakHeight(anahit.StripCharge(j));
                        h.SetTot(anahit.StripTimeOverThreshold(j));
								h.SetRiset(anahit.StripRiseTiming(j));
								h.SetType(t);
                        h.SetLocalX(E16ANA_StraightTrackNameSpace::E16ANA_GTRLocalX(lorentz_angle_calib_param, lid, t, anahit.StripID(j)));
								h.SetPeakt(anahit.StripPeakt(j));
								h.SetTotEnd(anahit.StripTotEd(j));
								if(min_adc > anahit.StripCharge(j)){
									min_adc = anahit.StripCharge(j);
								}
								if(last_totend < anahit.StripTotEd(j)){
								  last_totend = anahit.StripTotEd(j);
								}
								if(last_st < anahit.StripTotSt(j)){
									last_st = anahit.StripTotSt(j);	
								}
								if(max_tot < anahit.StripTimeOverThreshold(j)){
									max_tot = anahit.StripTimeOverThreshold(j);
								}
								if(min_tot > anahit.StripTimeOverThreshold(j)){
									min_tot = anahit.StripTimeOverThreshold(j);
								}
								if(max_rt < anahit.StripRiseTiming(j)){
									max_rt = anahit.StripRiseTiming(j);
								}
								if(min_rt > anahit.StripRiseTiming(j)){
									min_rt = anahit.StripRiseTiming(j);
								}
								
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
                    cl.SetModId(mid);
		     			  cl.SetClusterId(cl_id);
                    cl.SetHitOrders(hit_orders);
                    cl.SetType(t);
						  cl.SetClusterSize(anahit.NumHit());
                    cl.SetMaxPeakCh(anahit.MaxStripId());
                    cl.SetMaxPeakHeight(anahit.MaxValue());
                    cl.SetTiming(anahit.Timing());
                    cl.SetPeakSum(anahit.ClusterCharge());//cluster charge
                    cl.SetCogPos(anahit.CogHit());
		    			  cl.SetTiming2(anahit.Timing2());
                    cl.SetTanTheta(anahit.TanTheta());
						  cl.SetTdcPos(anahit.TdcHit());
						  cl.SetTdcPos2(anahit.TdcHit2());
						  cl.SetTanTheta2(anahit.TanTheta2());
						  cl.SetMinAdc(min_adc);
//						  cl.SetMaxRiset(anahit.MaxRiset());//241022
						  cl.SetMaxRiset(max_rt);//241022
						  cl.SetMinRiset(min_rt);
//						  cl.SetMaxTot(anahit.MaxTot());//241022
						  cl.SetMaxTot(max_tot);//241022
						  cl.SetMinTot(min_tot);
						  cl.SetTiming3(anahit.Timing3());
						  cl.SetTiming4(anahit.Timing4());
						  cl.SetLastTotStart(last_st);
						  cl.SetLastTotEnd(last_totend);//240426
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


    std::vector<int16_t> thit_orders;
    thit_orders.clear();
    thit_orders.push_back(0);thit_orders.push_back(1);thit_orders.push_back(2);
    
    for(int mid=107; mid<=107; mid++){
        for(int lid=2; lid< 3 ; lid++){
	  
	  E16DST_DST1GTRCluster &cl = dst1_clusters[cl_id];
	  cl.SetInvalid();
	  cl.SetModuleId(mid);
	  cl.SetLayerId(lid);
	  cl.SetModId(mid);
	  cl.SetClusterId(cl_id);
	  cl.SetHitOrders(thit_orders);
	  cl.SetType(0);
	  cl.SetMaxPeakCh(1);
	  cl.SetMaxPeakHeight(99999);
	  cl.SetTiming(300);
	  cl.SetPeakSum(99999);//cluster charge
	  cl.SetCogPos(0);
	  cl.SetTiming2(300);
	  cl.SetTanTheta(0);
	  cl.SetTdcPos(0);
	  cl.SetTdcPos2(0);
	  cl.SetTanTheta2(0);
	  cl.SetMaxRiset(0);
	  cl.SetMaxTot(9999);//shold be over the totmax threshold  
	  cl.SetTiming3(300);
	  cl.SetTiming4(300);
	  cl.SetLastTotEnd(0);//240426
	  for(int i=0;i<1;i++){
	    cl.SetCTiming(300);
	    cl.SetCPos(0);
	    cl.SetCAdc1(0);
	    cl.SetCAdc2(0);
	    cl.SetCAdc3(0);
	    cl.SetCAdc4(0);
	    cl.SetCAdc5(0);
	  }
	  for(int i=0;i<1;i++){
	    cl.SetCTiming2(0);
	    cl.SetCPos2(0);
	  }
	  for(int i=0;i<1;i++){
	    cl.SetCTiming3(0);
	    cl.SetCPos3(0);
	  }
	  for(int i=0;i<1;i++){
	    cl.SetCTiming4(0);
	    cl.SetCPos4(0);
	    cl.SetCTiming5(0);
	    cl.SetCPos5(0);
	  }
	  cl_id++;




	  E16DST_DST1GTRCluster &cly = dst1_clusters[cl_id];
	  cly.SetInvalid();
	  cly.SetModuleId(mid);
	  cly.SetLayerId(lid);
	  cly.SetModId(mid);
	  cly.SetClusterId(cl_id);
	  cly.SetHitOrders(thit_orders);
	  cly.SetType(1);
	  cly.SetMaxPeakCh(1);
	  cly.SetMaxPeakHeight(99999);
	  cly.SetTiming(300);
	  cly.SetPeakSum(99999);//clyuster charge
	  cly.SetCogPos(0);
	  cly.SetTiming2(300);
	  cly.SetTanTheta(0);
	  cly.SetTdcPos(0);
	  cly.SetTdcPos2(0);
	  cly.SetTanTheta2(0);
	  cly.SetMaxRiset(0);
	  cly.SetMaxTot(9999);
	  cly.SetTiming3(300);
	  cly.SetTiming4(300);
	  cly.SetLastTotEnd(0);//240426
	  for(int i=0;i<1;i++){
	    cly.SetCTiming(300);
	    cly.SetCPos(0);
	    cly.SetCAdc1(0);
	    cly.SetCAdc2(0);
	    cly.SetCAdc3(0);
	    cly.SetCAdc4(0);
	    cly.SetCAdc5(0);
	  }
	  for(int i=0;i<1;i++){
	    cly.SetCTiming2(0);
	    cly.SetCPos2(0);
	  }
	  for(int i=0;i<1;i++){
	    cly.SetCTiming3(0);
	    cly.SetCPos3(0);
	  }
	  for(int i=0;i<1;i++){
	    cly.SetCTiming4(0);
	    cly.SetCPos4(0);
	    cly.SetCTiming5(0);
	    cly.SetCPos5(0);
	  }
	  cl_id++;
	}       
    }
    
    for(int mid=103; mid<=106; mid++){
      if(mid==105) continue;
	for(int lid=0; lid< 3 ; lid++){
	  E16DST_DST1GTRCluster &cly = dst1_clusters[cl_id];
	  cly.SetInvalid();
	  cly.SetModuleId(mid);
	  cly.SetLayerId(lid);
	  cly.SetModId(mid);
	  cly.SetClusterId(cl_id);
	  cly.SetHitOrders(thit_orders);
	  cly.SetType(1);
	  cly.SetMaxPeakCh(1);
	  cly.SetMaxPeakHeight(99999);
	  cly.SetTiming(300);
	  cly.SetPeakSum(99999);//clyuster charge
	  cly.SetCogPos(0);
	  cly.SetTiming2(300);
	  cly.SetTanTheta(0);
	  cly.SetTdcPos(0);
	  cly.SetTdcPos2(0);
	  cly.SetTanTheta2(0);
	  cly.SetMaxRiset(0);
	  cly.SetMaxTot(0);
	  cly.SetTiming3(300);
	  cly.SetTiming4(300);
	  cly.SetLastTotEnd(0);
	  for(int i=0;i<1;i++){
	    cly.SetCTiming(300);
	    cly.SetCPos(0);
	    cly.SetCAdc1(0);
	    cly.SetCAdc2(0);
	    cly.SetCAdc3(0);
	    cly.SetCAdc4(0);
	    cly.SetCAdc5(0);
	  }
	  for(int i=0;i<1;i++){
	    cly.SetCTiming2(0);
	    cly.SetCPos2(0);
	  }
	  for(int i=0;i<1;i++){
	    cly.SetCTiming3(0);
	    cly.SetCPos3(0);
	  }
	  for(int i=0;i<1;i++){
	    cly.SetCTiming4(0);
	    cly.SetCPos4(0);
	    cly.SetCTiming5(0);
	    cly.SetCPos5(0);
	  }
	  cl_id++;
	}
    }
    

    
    
    //return sizeof(E16DST_DST1GTRHit) * dst1_hits_size + sizeof(E16DST_DST1GTRCluster) * (dst1_clusters_size+2);
    return sizeof(E16DST_DST1GTRHit) * dst1_hits_size + sizeof(E16DST_DST1GTRCluster) * (dst1_clusters_size+11);
    //return sizeof(E16DST_DST1GTRHit) * dst1_hits_size + sizeof(E16DST_DST1GTRCluster) * (dst1_clusters_size);
}
