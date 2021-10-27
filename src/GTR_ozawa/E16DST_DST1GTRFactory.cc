//#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1.hh"
//#include "GTR/E16ANA_GTRAnalyzerMaker.hh"
//#include "GTR/OnlineGTRUtility.h"
#include "E16ANA_GTRAnalyzerMaker.hh"
#include "OnlineGTRUtility.h"
//#include "E16ANA_GTRPedestal.h"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"


int E16DST_DST1GTRFactory(E16DST_DST0Detector<E16DST_DST0GTRHit>& dst0_hits, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster>* gtr1, E16ANA_GTRcalibPedestal &gtrped) {
    auto& dst1_hits = gtr1->Hits();
    auto& dst1_clusters = gtr1->Clusters();
    static bool isFirst = true;
    static E16ANA_GTRAnalyzerMaker *gtr_analyzers;
    if(isFirst){
        gtr_analyzers = new E16ANA_GTRAnalyzerMaker();

#undef FIELD_OFF_ANA
#ifdef  FIELD_OFF_ANA
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetThresholdX, 150.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetThresholdY, 300.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetTOTThresholdX, 75.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetTOTThresholdY, 75.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetTimeWindowMin, 0.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetTimeWindowMax, 1000.0);

        gtr_analyzers->SetInteger(&E16ANA_GTRAnalyzer2::SetClusterMinimumGap, 
				  2);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetClusterDeltaTdc, 10000.);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetRiseTimeMin, -10000.);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetRiseTimeMax, 10000.);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetPeakTimeMin, -10000.);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetPeakTimeMax, 10000.);

#else

        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetThresholdX, 50.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetThresholdY, 50.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetTOTThresholdX, -1000.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetTOTThresholdY, -1000.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetTimeWindowMin, 50.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetTimeWindowMax, 1000.0);

        gtr_analyzers->SetInteger(&E16ANA_GTRAnalyzer2::SetClusterMinimumGap, 
				  1);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetClusterDeltaTdc, 150.);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetRiseTimeMin, 25.);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetRiseTimeMax, 125.);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetPeakTimeMin, -10000.);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetPeakTimeMax, 520.);


#endif


        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetBadPedestalThresholdX, 
			   150.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetBadPedestalThresholdY, 
			   150.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetBadPedestalSigmaThresholdX, 
			   80.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetBadPedestalSigmaThresholdY, 
			   150.0);


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
      //a.second->AnalyzeV0();
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
    int cl_id = 0;// cluster id 
    int h_id = 0;// hit id
    for(int mid=100; mid < 110 ; mid++){
        for(int lid=0; lid< 3 ; lid++){
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
            std::array<int16_t, 3> indexs = {0,0,0};
//            t_hit_indexs[0].clear();
//            t_hit_indexs[1].clear();
//            t_hit_indexs[2].clear();
            for(int t=0; t < v_anahits.size(); t++){//t == 0, 1, 2 means X, Y, Yb respectively, namely, type
                for(int i =0; i<v_anahits[t].get().size();i++){
                    t_hit_indexs[0].clear();
                    t_hit_indexs[1].clear();
                    t_hit_indexs[2].clear();
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
                        t_hit_indexs[t].push_back(indexs[t]);
                        h_id++;
                        indexs[t]++;
                    }
                    E16DST_DST1GTRCluster &cl = dst1_clusters[cl_id];
                    cl.SetInvalid();
                    cl.SetModuleId(mid);
                    cl.SetLayerId(lid);
                    //std::cout << "t, t_hit_indexs[t] = " << t_hit_indexs[t].size() << std::endl;
                    //std::cout << "hit size = " << cl.NumHits() << std::endl;
                    cl.SetHitOrders(t_hit_indexs[t]);
                    //std::cout << "hit size after = " << cl.NumHits() << std::endl;
                    cl.SetType(t);
                    cl.SetMaxPeakCh(anahit.MaxStripId());
                    cl.SetMaxPeakHeight(anahit.MaxValue());
                    cl.SetTiming(anahit.Timing());
                    cl.SetPeakSum(anahit.ClusterCharge());//cluster charge
                    cl.SetCogPos(anahit.CogHit());
                    if(isnan(anahit.TdcHit())){
		      //std::cout << "TDC hit pos is nan" << std::endl;
                    }
                    else{
                        cl.SetTdcPos(anahit.TdcHit());
                    }
                    cl.SetTanTheta(anahit.TanTheta());
                    cl_id++;
                }       
            }   
        }
    }
    return sizeof(E16DST_DST1GTRHit) * dst1_hits_size + sizeof(E16DST_DST1GTRCluster) * dst1_clusters_size;
}
