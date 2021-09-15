//#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1.hh"
#include "GTR/E16ANA_GTRAnalyzerMaker.hh"
#include "GTR/OnlineGTRUtility.h"
//#include "E16ANA_GTRPedestal.h"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"


int E16DST_DST1GTRFactoryDST1Detector(E16DST_DST0Detector<E16DST_DST0GTRHit>& dst0_hits, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster>* gtr1) {
    auto& dst1_hits     = gtr1->Hits();
    auto& dst1_clusters = gtr1->Clusters();
    
    static bool isFirst = true;
    static E16ANA_GTRAnalyzerMaker *gtr_analyzers;
    if(isFirst){
        gtr_analyzers = new E16ANA_GTRAnalyzerMaker();
//        E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
//        E16ANA_GTRcalibPedestal gtrped;
//n        gtrped.ReadCalibData( calib.CurrentRunID());
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetThresholdX, 150.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetThresholdY, 300.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetTOTThresholdX, 75.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetTOTThresholdY, 75.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetBadPedestalThresholdX, 150.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetBadPedestalThresholdY, 150.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetBadPedestalSigmaThresholdX, 80.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetBadPedestalSigmaThresholdY, 150.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetTimeWindowMin, 0.0);
        gtr_analyzers->Set(&E16ANA_GTRAnalyzer2::SetTimeWindowMax, 1000.0);
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
        a.second->AnalyzeV0();
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
            t_hit_indexs[0].clear();
            t_hit_indexs[1].clear();
            t_hit_indexs[2].clear();
            for(int t=0; t < v_anahits.size(); t++){//t == 0, 1, 2 means X, Y, Yb respectively, namely, type
                for(int i =0; i<v_anahits[t].get().size();i++){
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
                    cl.SetHitOrders(t_hit_indexs[t]);
                    cl.SetType(t);
//                  cl.SetMaxPeakCh();
//                  clSetMaxPeakHeight();
                    cl.SetTiming(anahit.Timing());
                    cl.SetPeakSum(anahit.Timing());
                    cl.SetCogPos(anahit.CogHit());
                    cl.SetTdcPos(anahit.TdcHit());
                    cl.SetTanTheta(anahit.TanTheta());
                    cl_id++;
                }       
            }
            
        }
    }
//    std::cout << "h id , h_size = " <<  h_id << " . "  <<dst1_hits_size  << std::endl;
//    std::cout << "cl id " << cl_id << ", " << dst1_clusters_size <<  std::endl;


//            int order_x = 0;
//            std::vector<E16ANA_GTRAnalyzedStripHit> &hitsx = gtr_analyzers->Chamber(mid,lid)->GetStripX()->GetAnalyzedHits();
            
//            std::vector<int> hit_orders_x;
//            for(int i=0; i<hitsx.size(); i++){
//--cluster fill --//
//                E16ANA_GTRAnalyzedStripHit &anahit = hitsx[i];
//                E16DST_DST1GTRCluster &cl = dst1_clusters->Hit(cl_id);
//                cl.SetInvalid();
//                cl.SetModuleId(mid);
//                cl.SetLayerId(lid);
//                cl.SetType(0);//means x strip
////                cl.SetHitOrders(hit_orders_x);
////              cl.SetMaxPeakCh();
////              clSetMaxPeakHeight();
//                cl.SetTiming(anahit.Timing());
//                cl.SetPeakSum(anahit.Timing());
//                cl.SetCogPos(anahit.CogHit());
//                cl.SetTdcPos(anahit.TdcHit());
//                cl.SetTanTheta(anahit.TanTheta());
//                for(int j=0; j<anahit.NumHit(); j++){
////--hit fill --//
//                    E16DST_DST1GTRHit &h = dst1_hits->Hit(h_id);
//                    h.SetInvalid();
//                    h.SetIds(mid, anahit.StripID(j));
//                    h.SetLayerId(lid);
//                    h.SetTiming(anahit.StripTiming(j));
//                    h.SetPeakHeight(anahit.StripCharge(j));
//                    h.SetTot(anahit.StripTimeOverThreshold(j));
//                    h.SetType(0);//means x strip
////                    hit_orders_x.push_back(order_x);
////                    order_x++;
//                    h_id++;
//                }
//                cl_id++;
//            }
//        hitsx.clear();
//        }
//    }


//----------push back 
//    for(int mid=100; mid < 110 ; mid++){
//        for(int lid=0; lid< 3 ; lid++){
//            int order_x = 0;
//            std::vector<E16ANA_GTRAnalyzedStripHit> &hits0 = gtr_analyzers->Chamber(mid, lid)->GetStripX()->GetAnalyzedHits();
//            std::vector<int> hit_orders_x;
//            for(int i = 0 ; i < hits0.size(); i++){
//                E16ANA_GTRAnalyzedStripHit &h = hits0[i];
//                for(int j=0; j < h.NumHit(); j++){
//                    auto dst1_h = new E16DST_DST1GTRHit();
//                    dst1_h->SetInvalid();
//                    dst1_h->SetIds(mid, h.StripID(j));
//                    dst1_h->SetLayerId(lid);
//                    dst1_h->SetTiming(h.StripTiming(j));
//                    dst1_h->SetPeakHeight(h.StripCharge(j));
//                    dst1_h->SetTot(h.StripTimeOverThreshold(j));
//                    dst1_h->SetType(0);//means x strip
//                    hit_orders_x.push_back(order_x);
//                    dst1_hits->PushBack(*dst1_h);
//                    order_x++;
//                    delete dst1_h;
//                }
//                auto dst1_cl = new E16DST_DST1GTRCluster();
//                dst1_cl->SetInvalid();
//                dst1_cl->SetModuleId(mid);
//                dst1_cl->SetLayerId(lid);
//                dst1_cl->SetType(0);//means x strip
//                dst1_cl->SetHitOrders(hit_orders_x);
////                dst1_cl->SetMaxPeakCh();
////                dst1_cl->SetMaxPeakHeight();
//                dst1_cl->SetTiming(h.Timing());
//                dst1_cl->SetPeakSum(h.Timing());
//                dst1_cl->SetCogPos(h.CogHit());
//                dst1_cl->SetTdcPos(h.TdcHit());
//                dst1_cl->SetTanTheta(h.TanTheta());
//                dst1_clusters->PushBack(*dst1_cl);
//                delete dst1_cl;
//            }
//            hits0.clear();
//            int order_y = 0;
//            std::vector<E16ANA_GTRAnalyzedStripHit> &hits1 = gtr_analyzers->Chamber(mid, lid)->GetStripY()->GetAnalyzedHits(); 
//            std::vector<int> hit_orders_y;
//            for(int i = 0 ; i < hits1.size(); i++){
//                E16ANA_GTRAnalyzedStripHit &h = hits1[i];
//                for(int j=0; j < h.NumHit(); j++){
//                    auto dst1_h = new E16DST_DST1GTRHit();
//                    dst1_h->SetInvalid();
//                    dst1_h->SetIds(mid, h.StripID(j));
//                    dst1_h->SetLayerId(lid);
//                    dst1_h->SetType(1);//means y strip
//                    dst1_h->SetTiming(h.StripTiming(j));
//                    dst1_h->SetPeakHeight(h.StripCharge(j));
//                    dst1_h->SetTot(h.StripTimeOverThreshold(j));
//                    hit_orders_y.push_back(order_y);
//                    dst1_hits->PushBack(*dst1_h);
//                    order_y++;
//                    delete dst1_h;
//                }
//                auto dst1_cl = new E16DST_DST1GTRCluster();
//                dst1_cl->SetInvalid();
//                dst1_cl->SetModuleId(mid);
//                dst1_cl->SetLayerId(lid);
//                dst1_cl->SetType(1);//means y strip
////                dst1_cl->SetMaxPeakCh();
////                dst1_cl->SetMaxPeakHeight();
//                dst1_cl->SetTiming(h.Timing());
//                dst1_cl->SetPeakSum(h.Timing());
//                dst1_cl->SetCogPos(h.CogHit());
//                dst1_cl->SetTdcPos(h.TdcHit());
//                dst1_cl->SetTanTheta(h.TanTheta());
//                dst1_cl->SetHitOrders(hit_orders_y);
//                dst1_clusters->PushBack(*dst1_cl);
//                delete dst1_cl;
//            }
//            hits1.clear();
//            if(lid != 0)continue;
//            int order_yb = 0;
//            std::vector<E16ANA_GTRAnalyzedStripHit> &hits2 = static_cast<E16ANA_GTR100Analyzer *>(gtr_analyzers->Chamber(mid, 0))->GetStripYb()->GetAnalyzedHits();
//            std::vector<int> hit_orders_yb;
//            for(int i = 0 ; i < hits2.size(); i++){
//                E16ANA_GTRAnalyzedStripHit &h = hits2[i];
//                for(int j=0; j < h.NumHit(); j++){
//                    auto dst1_h = new E16DST_DST1GTRHit();
//                    dst1_h->SetInvalid();
//                    dst1_h->SetIds(mid, h.StripID(j));
//                    dst1_h->SetLayerId(lid);
//                    dst1_h->SetType(2);//means yb strip
//                    dst1_h->SetTiming(h.StripTiming(j));
//                    dst1_h->SetPeakHeight(h.StripCharge(j));
//                    dst1_h->SetTot(h.StripTimeOverThreshold(j));
//                    hit_orders_yb.push_back(order_yb);
//                    dst1_hits->PushBack(*dst1_h);
//                    order_yb++;
//                    delete dst1_h;
//                }
//                auto dst1_cl = new E16DST_DST1GTRCluster();
//                dst1_cl->SetInvalid();
//                dst1_cl->SetModuleId(mid);
//                dst1_cl->SetLayerId(lid);
//                dst1_cl->SetType(2);//means yb strip
////                dst1_cl->SetMaxPeakCh();
////                dst1_cl->SetMaxPeakHeight();
//                dst1_cl->SetTiming(h.Timing());
//                dst1_cl->SetPeakSum(h.Timing());
//                dst1_cl->SetCogPos(h.CogHit());
//                dst1_cl->SetTdcPos(h.TdcHit());
//                dst1_cl->SetTanTheta(h.TanTheta());
//                dst1_cl->SetHitOrders(hit_orders_yb);
//                dst1_clusters->PushBack(*dst1_cl);
//                delete dst1_cl;
//            }
//            hits2.clear();
//        }
//    }
//    return 0;  
    return sizeof(E16DST_DST1GTRHit) * dst1_hits_size + sizeof(E16DST_DST1GTRCluster) * dst1_clusters_size;
}
