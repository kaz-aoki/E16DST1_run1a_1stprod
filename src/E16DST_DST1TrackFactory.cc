#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "TVector3.h"
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_MagneticFieldMap.hh"
#include "E16ANA_TrackCandidate.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DefaultFilePath.hh"

//const std::array<double, kNumGTRLayers> kLorentzCor({2.65, -1.24, -0.26});

int E16DST_DST1TrackFactory(E16ANA_GeometryV2& geometry, E16ANA_MagneticFieldMap& bfield_map, E16DST_DST1PhysicsRecord* record) {
  const std::array<std::array<E16ANA_DetectorGeometry*, E16ANA_TrackConstant::kNumModules>, E16ANA_TrackConstant::kNumRemainingLayers> tmp_geoms = {{
      {const_cast<E16ANA_DetectorGeometry*>(geometry.HBD(E16ANA_TrackConstant::kModuleIDs[0])),
       const_cast<E16ANA_DetectorGeometry*>(geometry.HBD(E16ANA_TrackConstant::kModuleIDs[1])),
       const_cast<E16ANA_DetectorGeometry*>(geometry.HBD(E16ANA_TrackConstant::kModuleIDs[2])),
       const_cast<E16ANA_DetectorGeometry*>(geometry.HBD(E16ANA_TrackConstant::kModuleIDs[3])),
       const_cast<E16ANA_DetectorGeometry*>(geometry.HBD(E16ANA_TrackConstant::kModuleIDs[4])),
       const_cast<E16ANA_DetectorGeometry*>(geometry.HBD(E16ANA_TrackConstant::kModuleIDs[5])),
       const_cast<E16ANA_DetectorGeometry*>(geometry.HBD(E16ANA_TrackConstant::kModuleIDs[6])),
       const_cast<E16ANA_DetectorGeometry*>(geometry.HBD(E16ANA_TrackConstant::kModuleIDs[7]))},
      {const_cast<E16ANA_DetectorGeometry*>(geometry.LGVD(E16ANA_TrackConstant::kModuleIDs[0])),
       const_cast<E16ANA_DetectorGeometry*>(geometry.LGVD(E16ANA_TrackConstant::kModuleIDs[1])),
       const_cast<E16ANA_DetectorGeometry*>(geometry.LGVD(E16ANA_TrackConstant::kModuleIDs[2])),
       const_cast<E16ANA_DetectorGeometry*>(geometry.LGVD(E16ANA_TrackConstant::kModuleIDs[3])),
       const_cast<E16ANA_DetectorGeometry*>(geometry.LGVD(E16ANA_TrackConstant::kModuleIDs[4])),
       const_cast<E16ANA_DetectorGeometry*>(geometry.LGVD(E16ANA_TrackConstant::kModuleIDs[5])),
       const_cast<E16ANA_DetectorGeometry*>(geometry.LGVD(E16ANA_TrackConstant::kModuleIDs[6])),
       const_cast<E16ANA_DetectorGeometry*>(geometry.LGVD(E16ANA_TrackConstant::kModuleIDs[7]))}}};
  auto track_candidates = new E16ANA_TrackCandidates(&geometry, &bfield_map, tmp_geoms, record);
  track_candidates->SelectTracks();
  track_candidates->Print();
  return 0;
}
