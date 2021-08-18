//#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1GTRAnalyzerMaker.hh"
#include "OnlineGTRUtility.h"
//#include "E16ANA_GTRPedestal.h"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"


int E16DST_DST1GTRHitAndClusterFactory(E16DST_DST0Detector<E16DST_DST0GTRHit>& dst0_hits, E16DST_DST0Detector<E16DST_DST1GTRHit> *dst1_hits, E16DST_DST0Detector<E16DST_DST1GTRCluster> * dst1_clusters) {
    static bool isFirst = true;
    static E16DST_DST1GTRAnalyzerMaker *gtr_analyzers;
    if(isFirst){
        gtr_analyzers = new E16DST_DST1GTRAnalyzerMaker();
        E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
        E16ANA_GTRcalibPedestal gtrped;
        gtrped.ReadCalibData( calib.CurrentRunID());
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
    for(int mid=100; mid < 110 ; mid++){
        for(int lid=0; lid< 3 ; lid++){
            int order_x = 0;
            std::vector<E16ANA_GTRAnalyzedStripHit> &hits0 = gtr_analyzers->Chamber(mid, lid)->GetStripX()->GetAnalyzedHits();
            std::vector<int> hit_orders_x;
            for(int i = 0 ; i < hits0.size(); i++){
                E16ANA_GTRAnalyzedStripHit &h = hits0[i];
                for(int j=0; j < h.NumHit(); j++){
                    auto dst1_h = new E16DST_DST1GTRHit();
                    dst1_h->SetInvalid();
                    dst1_h->SetIds(mid, h.StripID(j));
                    dst1_h->SetTiming(h.StripTiming(j));
                    dst1_h->SetPeakHeight(h.StripCharge(j));
                    dst1_h->SetTot(h.StripTimeOverThreshold(j));
                    hit_orders_x.push_back(order_x);
                    dst1_hits->
                        PushBack(*dst1_h);
                    order_x++;
                }
                auto dst1_cl = new E16DST_DST1GTRCluster();
                dst1_cl->SetInvalid();
                dst1_cl->SetModuleId(mid);
                dst1_cl->SetHitOrders(hit_orders_x);
//                dst1_cl->SetMaxPeakCh();
//                dst1_cl->SetMaxPeakHeight();
                dst1_cl->SetTiming(h.Timing());
                dst1_cl->SetPeakSum(h.Timing());
                dst1_cl->SetCogPos(h.CogHit());
                dst1_cl->SetTdcPos(h.TdcHit());
                dst1_cl->SetTanTheta(h.TanTheta());
                dst1_clusters->PushBack(*dst1_cl);
            }
            int order_y = 0;
            std::vector<E16ANA_GTRAnalyzedStripHit> &hits1 = gtr_analyzers->Chamber(mid, lid)->GetStripY()->GetAnalyzedHits(); 
            std::vector<int> hit_orders_y;
            for(int i = 0 ; i < hits1.size(); i++){
                E16ANA_GTRAnalyzedStripHit &h = hits1[i];
                for(int j=0; j < h.NumHit(); j++){
                    auto dst1_h = new E16DST_DST1GTRHit();
                    dst1_h->SetInvalid();
                    dst1_h->SetIds(mid, h.StripID(j));
                    dst1_h->SetTiming(h.StripTiming(j));
                    dst1_h->SetPeakHeight(h.StripCharge(j));
                    dst1_h->SetTot(h.StripTimeOverThreshold(j));
                    hit_orders_y.push_back(order_y);
                    dst1_hits->PushBack(*dst1_h);
                    order_y++;
                }
                auto dst1_cl = new E16DST_DST1GTRCluster();
                dst1_cl->SetInvalid();
                dst1_cl->SetModuleId(mid);
//                dst1_cl->SetMaxPeakCh();
//                dst1_cl->SetMaxPeakHeight();
                dst1_cl->SetTiming(h.Timing());
                dst1_cl->SetPeakSum(h.Timing());
                dst1_cl->SetCogPos(h.CogHit());
                dst1_cl->SetTdcPos(h.TdcHit());
                dst1_cl->SetTanTheta(h.TanTheta());
                dst1_cl->SetHitOrders(hit_orders_y);
                dst1_clusters->PushBack(*dst1_cl);
            }
            
            if(lid != 0)continue;
            int order_yb = 0;
            std::vector<E16ANA_GTRAnalyzedStripHit> &hits2 = gtr_analyzers->Chamber(mid, lid)->GetStripY()->GetAnalyzedHits();
            std::vector<int> hit_orders_yb;
            for(int i = 0 ; i < hits2.size(); i++){
                E16ANA_GTRAnalyzedStripHit &h = hits2[i];
                for(int j=0; j < h.NumHit(); j++){
                    auto dst1_h = new E16DST_DST1GTRHit();
                    dst1_h->SetInvalid();
                    dst1_h->SetIds(mid, h.StripID(j));
                    dst1_h->SetTiming(h.StripTiming(j));
                    dst1_h->SetPeakHeight(h.StripCharge(j));
                    dst1_h->SetTot(h.StripTimeOverThreshold(j));
                    hit_orders_yb.push_back(order_yb);
                    dst1_hits->PushBack(*dst1_h);
                    order_yb++;
                }
                auto dst1_cl = new E16DST_DST1GTRCluster();
                dst1_cl->SetInvalid();
                dst1_cl->SetModuleId(mid);
//                dst1_cl->SetMaxPeakCh();
//                dst1_cl->SetMaxPeakHeight();
                dst1_cl->SetTiming(h.Timing());
                dst1_cl->SetPeakSum(h.Timing());
                dst1_cl->SetCogPos(h.CogHit());
                dst1_cl->SetTdcPos(h.TdcHit());
                dst1_cl->SetTanTheta(h.TanTheta());
                dst1_cl->SetHitOrders(hit_orders_yb);
                dst1_clusters->PushBack(*dst1_cl);
            }
        }
    }
    return 0;  

}
