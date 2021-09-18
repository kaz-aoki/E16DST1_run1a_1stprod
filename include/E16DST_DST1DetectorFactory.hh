#ifndef E16DST_DST1FACTORY_HH
#define E16DST_DST1FACTORY_HH

//#include <fstream>
//#include <iostream>
//#include <unordered_map>
//#include <vector>
//
//#include "TVector3.h"
//#include "E16ANA_GeometryV2.hh"
//#include "E16ANA_MagneticFieldMap.hh"
//#include "E16ANA_MultiTrack.hh"
//#include "E16ANA_GTRcalib.hh"
//#include "E16ANA_TriggerCalib.hh"
//#include "E16ANA_LGBasic.hh"
//#include "E16DST_Constant.hh"
//#include "E16DST_DST0.hh"
//#include "E16DST_DST1Constant.hh"
#include "E16ANA_TrackCandidate.hh"
#include "E16ANA_HBDCalibration.hh"

//int E16DST_DST1SSDFactory(E16DST_DST0Detector<E16DST_DST0SSDHit>& hits0, E16DST_DST0Detector<E16DST_DST1SSDHit>* hits1, E16DST_DST0Detector<E16DST_DST1SSDCluster>* clusters1);
////class E16DST_DST1GTRAnalyzerMaker;
//int E16DST_DST1GTRHitAndClusterFactory(E16DST_DST0Detector<E16DST_DST0GTRHit>& hits0, E16DST_DST0Detector<E16DST_DST1GTRHit>* hits1, E16DST_DST0Detector<E16DST_DST1GTRCluster>* clusters1, E16ANA_GTRcalibPedestal &gtrped);
//int E16DST_DST1HBDFactory(E16DST_DST0Detector<E16DST_DST0HBDHit>& hits0, E16DST_DST0Detector<E16DST_DST1HBDHit>* hits1, E16DST_DST0Detector<E16DST_DST1HBDCluster>* clusters1);
//int E16DST_DST1LGFactory(E16DST_DST0Detector<E16DST_DST0LGHit>& hits0,   E16DST_DST0Detector<E16DST_DST1LGHit>* hits1,  E16DST_DST0Detector<E16DST_DST1LGCluster>* clusters1);
//int E16DST_DST1TriggerFactory(E16ANA_TriggerCalibParam& trigger_param, E16DST_DST0Detector<E16DST_DST0TriggerHit>& gtr_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& hbd_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& lg_hits, E16DST_DST0UT3& ut3, E16DST_DST1Trigger* trigger);
//int E16DST_DST1WireTrackFactory(E16DST_DST1SSDCluster& ssd_clusters, E16DST_DST1GTRCluster& gtr_clusters, E16DST_DST1WireTrack* wire_tracks);
////int E16DST_DST1WireTrackFactory(E16DST_DST1PhysicsRecord* record);
//int E16DST_DST1TrackFactory(E16ANA_GeometryV2& geometry, E16ANA_MagneticFieldMap& bfield_map, E16ANA_MultiTrack* fitter, E16DST_DST1PhysicsRecord* record);
int E16DST_DST1TrackFactory(E16ANA_GeometryV2& geometry, E16ANA_MagneticFieldMap& bfield_map, E16ANA_MultiTrack* fitter, E16DST_DST1PhysicsRecord* record, CheckFile* check_file);

//int E16DST_DST1SSDFactoryDST1Detector(E16DST_DST0Detector<E16DST_DST0SSDHit>& hits0, E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster>* gtr1);
int E16DST_DST1SSDFactory_dummy(E16DST_DST0Detector<E16DST_DST0SSDHit>& hits0, E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster>* ssd);
int E16DST_DST1GTRFactoryDST1Detector(E16DST_DST0Detector<E16DST_DST0GTRHit>& hits0, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster>* gtr1, E16ANA_GTRcalibPedestal& gtrped);
int E16DST_DST1HBDFactoryDST1Detector(E16DST_DST0Detector<E16DST_DST0HBDHit>& hits0, E16ANA_HBDCalibration* hbd_calib, E16DST_DST1Detector<E16DST_DST1HBDHit, E16DST_DST1HBDCluster>* hbd1);
int E16DST_DST1LGFactoryDST1Detector(E16DST_DST0Detector<E16DST_DST0LGHit>& hits0,   E16DST_DST1Detector<E16DST_DST1LGHit,  E16DST_DST1LGCluster>*  lg1);

#endif // E16DST_DST1FACTORY_HH
