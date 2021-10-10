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

#include "E16ANA_TrackCheckFile.hh"

//int E16DST_DST1TrackFactory(E16ANA_GeometryV2& geometry, E16ANA_MagneticFieldMap& bfield_map, E16ANA_MultiTrack* fitter, E16DST_DST1PhysicsRecord* record) {
//int E16DST_DST1TrackFactory(E16ANA_GeometryV2& geometry, E16ANA_MagneticFieldMap& bfield_map, E16ANA_MultiTrack* fitter, E16DST_DST1PhysicsRecord* record, CheckFile* check_file) {
//int E16DST_DST1TrackFactory(E16ANA_GeometryV2& geometry, E16ANA_MagneticFieldMap& bfield_map, E16ANA_MultiTrack* fitter, E16DST_DST1PhysicsRecord* record, CheckFile* check_file0, CheckFile* check_file1) {
int E16DST_DST1TrackFactory(E16ANA_GeometryV2& geometry, E16ANA_MagneticFieldMap& bfield_map, E16ANA_MultiTrack* fitter, E16DST_DST1PhysicsRecord* record, E16ANA_TrackCheckFile* check_file) {
  E16ANA_TrackCandidates track_candidates(&geometry, &bfield_map, fitter, record);
  static int n_calls;
  static int n_cands;
  static bool is_fill_param;
  track_candidates.Analyze();

  track_candidates.Print(3);
  
//  for (auto& cand : track_candidates.TrackCandidates()) {
//    check_file0->AddEntry(n_calls, cand);
//  }
//  for (auto& cand : track_candidates.SelectedTrackCandidates()) {
//    check_file1->AddEntry(n_calls, *cand);
//  }
  if (!is_fill_param && track_candidates.NumTrackCandidates() != 0) {
    check_file->AddParam(track_candidates);
    is_fill_param = true;
  }
  check_file->AddEntry(n_calls, geometry, *record, track_candidates);
  ++n_calls;
  n_cands += track_candidates.NumTrackCandidates();
  std::cout << "Total Number of Track Candidates: " << n_cands << std::endl;
  return 0;
}
