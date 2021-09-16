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
	
	std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> trks;
	std::vector<std::shared_ptr<E16ANA_XZTrackCandidate>> t = str_analyzer->GetXZTrackCandidates();
	for(int i=0; i < t.size(); i++){
		if((fabs(t[i]->TgtZ() - 40 ) < 20 ) || (fabs(t[i]->TgtZ() +40) < 20)){
			trks.push_back(t[i]);
		}
	}
	str_analyzer->Make2DCrossPoint(trks, geom);
	trks.clear();
//	str_analyzer->SeachSSDHit(str_analyzer->GetCrossPoints(), str_analyzer->ssd_detector.Clusters(),geom);
//	int n_trks = str_analyzer->GetXZTracksEveSel().size();
	
}
