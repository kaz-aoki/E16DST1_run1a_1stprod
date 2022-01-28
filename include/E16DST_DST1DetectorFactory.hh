#ifndef E16DST_DST1FACTORY_HH
#define E16DST_DST1FACTORY_HH

#include "E16ANA_WaveformFitter.hh"
#include "E16ANA_HBDCalibration.hh"
#include "E16ANA_HBDChannelManager.hh"
#include "E16ANA_HBDConstant.hh"
#include "E16ANA_HBDClusterAnalysis.hh"
#include "E16ANA_HBDCut.hh"
#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_TrackCandidate.hh"

#include "E16ANA_TrackCheckFile.hh"

int E16DST_DST1SSDFactory(E16DST_DST0Detector<E16DST_DST0SSDHit>& hits0, E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster>* ssd1);
int E16DST_DST1GTRFactory(E16DST_DST0Detector<E16DST_DST0GTRHit>& hits0, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster>* gtr1, E16ANA_GTRcalibPedestal& gtrped,
                          const std::array<double, 3>& lorentz_angle_calib_params);
int E16DST_DST1HBDFactory(E16DST_DST0Detector<E16DST_DST0HBDHit>& hits0, E16ANA_HBDCalibration* hbd_calib,
                          E16ANA_HBDCut* hbd_cut, E16ANA_WaveformFitter* wf1d_fitter,
                          E16DST_DST1Detector<E16DST_DST1HBDHit, E16DST_DST1HBDCluster>* hbd1);
int E16DST_DST1LGFactory(E16DST_DST0Detector<E16DST_DST0LGHit>& hits0, E16DST_DST1Detector<E16DST_DST1LGHit, E16DST_DST1LGCluster>* lg1, int fit_option, E16ANA_GeometryV2* geometry ); // 0: w/o fit, 1: w/ fit
int E16DST_DST1TriggerFactory(E16ANA_TriggerCalibParam& trigger_param, E16DST_DST0Detector<E16DST_DST0TriggerHit>& gtr_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& hbd_hits, E16DST_DST0Detector<E16DST_DST0TriggerHit>& lg_hits, E16DST_DST0UT3& ut3, E16DST_DST1Trigger* trigger);
int E16DST_DST1WireTrackFactory3D(E16DST_DST0PhysicsEvent *event0, E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster> *ssd1, E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> *gtr1,std::vector<std::shared_ptr<E16DST_DST1StraightTrack3D>> &st_tracks,  E16ANA_GTRcalibPedestal& gtrped);
int E16DST_DST1TrackFactory(E16ANA_GeometryV2& geometry, E16ANA_MagneticFieldMap& bfield_map, E16ANA_MultiTrack* fitter, E16ANA_MultiTrack* pair_fitter, bool is_electron_run, E16DST_DST1PhysicsRecord* record, E16ANA_TrackCheckFile* check_file);

#endif // E16DST_DST1FACTORY_HH
