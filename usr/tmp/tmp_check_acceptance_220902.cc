#include <iostream>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_WaveformFitterCRRC.hh"
#include "E16ANA_FieldMapCalib.hh"
#include "E16ANA_EventSelect.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_GTRLorentzAngleCalib.hh"
#include "E16ANA_GTRStatus.h"
#include "E16ANA_HBDCalibration.hh"
#include "E16ANA_HBDCut.hh"
#include "E16ANA_HBDDeadChannel.hh"
#include "E16ANA_LGDeadChannel.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16DST_DST1DefaultFilePath.hh"

#include "E16ANA_TrackCheckFile.hh"

#include "E16ANA_GTRAnalyzerMaker.hh"
#include "E16ANA_MakeDummyDST1.hh"
#include "E16ANA_MockTrackOutputData.hh"

using namespace std;

int main(int argc, char* argv[]) {
#ifdef TRACK_EFF_CHECK
  if (argc != 3) {
    cerr << "./bin run_ID input.mock" << endl;
    return -1;
  }
  auto run_id = stoi(argv[1]);
  auto mock_data_name = argv[2];

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  E16ANA_GTRcalibPedestal gtrped;
  gtrped.ReadCalibData( calib.CurrentRunID() );
//  E16ANA_GTRLorentzAngleCalibParamManager gtr_lorentz_angle_calib_param_manager;
//  gtr_lorentz_angle_calib_param_manager.ReadConstantData(calib.CurrentRunID());
//  auto gtr_lorentz_angle_calib_params = gtr_lorentz_angle_calib_param_manager.GTRLorentzAngleCalibParams();
//  E16ANA_HBDCalibration *hbd_calib = new E16ANA_HBDCalibration();
//  hbd_calib->ReadCalibrationData(calib.CurrentRunID());
//  E16ANA_HBDCut *hbd_cut = new E16ANA_HBDCut();
//  hbd_cut->ReadCutData(calib.CurrentRunID());
//  E16ANA_LGBasic lgbasic;
//  lgbasic.SetMap();
//  lgbasic.SetCalibMap();

//  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
//  E16ANA_GeometryV2::SetGlobalPointer(geometry);
//  auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
//  bfield_map->Initialize_binary();
//  E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
  
  auto mock_data = E16ANA_MockTrackOutputData();
  if (mock_data.OpenReadFile(mock_data_name) != E16ANA_MockTrackOutputData::OK) {
    cerr << "cannot open mock data file" << endl;
    return -1;
  }
  
  E16ANA_GTRcalibParams gtr_params;
  gtr_params.ReadCalibData(run_id);
  auto gtr_analyzers = new E16ANA_GTRAnalyzerMaker(gtr_params);
  for(int mid = 100; mid <= 110; ++mid) {
    for(int lid = 0; lid < 3; ++lid) {
      auto gtr_analyzer2 = gtr_analyzers->Chamber(mid, lid);
      int n_strips = gtr_analyzer2->GetNumberOfStrips();
      for(int strip_id = 0; strip_id < n_strips; ++strip_id) {
        double ped = gtrped.GetPedestal(mid, lid, strip_id).Value();
        double sigma = gtrped.GetPedestal(mid, lid, strip_id).Sigma();
        gtr_analyzer2->SetPedestal(strip_id, ped);
        gtr_analyzer2->SetPedestalSigma(strip_id, sigma);
      }
    }
  }
  auto gtr_stat = E16ANA_GTRStatus(run_id);
  auto hbd_dead_ch = E16ANA_HBDDeadChannel();
  hbd_dead_ch.ReadDeadChannelData(run_id);
  auto lg_dead_ch = E16ANA_LGDeadChannel();
  lg_dead_ch.ReadDeadChannelData();
  auto data_merger = E16ANA_MakeDummyDST1(0, gtr_analyzers, gtr_stat.ASDDeadChannel(), gtr_stat.GEMDeadArea100(), gtr_stat.GEMDeadArea200(), gtr_stat.GEMDeadArea300(),
                                          &hbd_dead_ch, &lg_dead_ch);
  
  array<array<double, 4>, 2> n_events; // 0: all, 1: waveform dead, 2: waveform alive, discri. dead 3: alive
  for (auto& ev : n_events) {
    for (auto& ev0 : ev) {
      ev0 = 0.;
    }
  }

  while (mock_data.ReadATrack() == E16ANA_MockTrackOutputData::OK) {
    int lr_id;
    if (mock_data.Track().GTR3().ModuleID() > 105) {
      lr_id = 0;
    } else {
      lr_id = 1;
    }
    ++n_events[lr_id][0];
    auto& track = mock_data.Track();
    if (data_merger.IsDeadRegion(track)) {
      ++n_events[lr_id][1];
      continue;
    } else if (data_merger.IsDiscriDeadRegion(track)) {
      ++n_events[lr_id][2];
      continue;
    } else {
      ++n_events[lr_id][3];
    }
  }
  cout << "GTR300 left  module waveform dead                  : " << n_events[0][1] << " / " << n_events[0][0] << ", " << n_events[0][1] / n_events[0][0] << endl;
  cout << "GTR300 left  module waveform alive and discri. dead: " << n_events[0][2] << " / " << n_events[0][0] << ", " << n_events[0][2] / n_events[0][0] << endl;
  cout << "GTR300 left  module alive                          : " << n_events[0][3] << " / " << n_events[0][0] << ", " << n_events[0][3] / n_events[0][0] << endl;
  cout << "GTR300 right module waveform dead                  : " << n_events[1][1] << " / " << n_events[1][0] << ", " << n_events[1][1] / n_events[1][0] << endl;
  cout << "GTR300 right module waveform alive and discri. dead: " << n_events[1][2] << " / " << n_events[1][0] << ", " << n_events[1][2] / n_events[1][0] << endl;
  cout << "GTR300 right module alive                          : " << n_events[1][3] << " / " << n_events[1][0] << ", " << n_events[1][3] / n_events[1][0] << endl;
#endif // TRACK_EFF_CHECK
  return 0;
}
