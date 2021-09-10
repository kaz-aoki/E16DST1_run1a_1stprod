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
    for(int m=100; m<110; m++){
//        std::vector<E16DST_DST1GTRCluster> &clusters0 = gtr_clusters.ClusterPtrs(m, 0, 0)//module, layer, type
//        std::vector<E16DST_DST1GTRCluster> &clusters1 = gtr_clusters.ClusterPtrs(m, 1, 0)//module, layer, type
//        std::vector<E16DST_DST1GTRCluster> &clusters2 = gtr_clusters.ClusterPtrs(m, 2, 0)//module, layer, type
    }
    

}
