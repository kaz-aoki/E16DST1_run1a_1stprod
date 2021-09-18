#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "TVector3.h"
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_MagneticFieldMap.hh"
#include "E16ANA_MultiTrack.hh"
#include "E16ANA_TrackCandidate.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DefaultFilePath.hh"

//const std::array<double, kNumGTRLayers> kLorentzCor({2.65, -1.24, -0.26});

//int E16DST_DST1TrackFactory(E16ANA_GeometryV2& geometry, E16ANA_MagneticFieldMap& bfield_map, E16ANA_MultiTrack* fitter, E16DST_DST1PhysicsRecord* record) {
int E16DST_DST1TrackFactory(E16ANA_GeometryV2& geometry, E16ANA_MagneticFieldMap& bfield_map, E16ANA_MultiTrack* fitter, E16DST_DST1PhysicsRecord* record, CheckFile* check_file) {
  E16ANA_TrackCandidates track_candidates(&geometry, &bfield_map, fitter, record);
  static int n_calls;
//  auto check_file = new CheckFile();
  track_candidates.SelectTracks();
  track_candidates.Print();
  
  for (int i = 0; i < 3; ++i) {
    for (auto& cand : track_candidates.TrackCandidates(i)) {
      check_file->AddEntry(n_calls, cand);
    }
  }
  ++n_calls;
  return 0;
}
