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

//int E16DST_DST1TrackFactory(E16ANA_GeometryV2& geometry, E16ANA_MagneticFieldMap& bfield_map, E16ANA_MultiTrack* fitter, E16DST_DST1PhysicsRecord* record) {
int E16DST_DST1TrackFactory(E16ANA_GeometryV2& geometry, E16ANA_MagneticFieldMap& bfield_map, E16ANA_MultiTrack* fitter, E16DST_DST1PhysicsRecord* record, CheckFile* check_file) {
  E16ANA_TrackCandidates track_candidates(&geometry, &bfield_map, fitter, record);
  static int n_calls;
  static int n_cands;
  track_candidates.Analyze();

//  track_candidates.Print();
  track_candidates.PrintSelected();
  
  for (int i = 0; i < 3; ++i) {
//    for (auto& cand : track_candidates.TrackCandidates(i)) {
//      check_file->AddEntry(n_calls, cand);
//    }
    for (auto& cand : track_candidates.SelectedTrackCandidates(i)) {
      check_file->AddEntry(n_calls, *cand);
    }
  }
  ++n_calls;
  n_cands += track_candidates.NumTrackCandidates();
  std::cout << "Total Number of Track Candidates: " << n_cands << std::endl;
  return 0;
}
