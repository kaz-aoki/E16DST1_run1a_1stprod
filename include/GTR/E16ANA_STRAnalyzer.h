#ifndef E16ANA_STRAnalyzer_h
#define E16ANA_STRAnalyzer_h 1

#include "E16ANA_GTRAnalyzer2.h"
#include "E16ANA_GTRStripAnalyzer.h"
#include "E16DST_DST1.hh"
//#include "GTR/E16ANA_GTRAnalyzerMaker.hh"
//#include "GTR/OnlineGTRUtility.h"
//#include "E16ANA_GTRPedestal.h"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"







class E16ANA_STRAnalyzer {
public:
    E16ANA_STRAnalyzer();
    ~E16ANA_STRAnalyzer();
    void TrackCandidateSearchXZ_OneModule(
            E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> &ssd_detector,
            E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> &gtr_detector
            );

};

class E16ANA_STRAnalyzerOfWire : public E16ANA_STRAnalyzer {
public:
    E16ANA_STRAnalyzerOfWire();
    ~E16ANA_STRAnalyzerOfWire();

};



#endif 
