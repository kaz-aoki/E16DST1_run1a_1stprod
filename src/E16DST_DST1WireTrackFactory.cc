#include "GTR/E16ANA_STRAnalyzer.h"

int E16DST_DST1WireTrackFactory(
        E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> &ssd_detector,
        E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> &gtr_detector,
        E16DST_DST1WireTrack *wire_tracks){
    static bool isFirst = true;
    static E16ANA_STRAnalyzer *str_analyzer;
    if(isFirst){
        str_analyzer = new E16ANA_STRAnalyzer();
    }
    str_analyzer->TrackCandidateSearchXZ_OneModule(ssd_detector, gtr_detector);

}
