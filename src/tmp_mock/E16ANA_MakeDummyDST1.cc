#ifdef TRACK_EFF_CHECK

//#define WO_LAYER_EFF
//#define GEOM_VER0

#include "E16ANA_MakeDummyDST1.hh"

#include <random>

using namespace std;
using namespace E16ANA_MakeDummyDST1Parameter;

bool E16ANA_MakeDummyDST1::IsSSDDeadRegion(int mid, const TVector3& pos) {
  if (mid == kSSDDeadModuleID && pos.X() > kSSDDeadX[0] && pos.X() < kSSDDeadX[1]) {
    return true;
  }
  return false;
}

bool E16ANA_MakeDummyDST1::IsGTRDeadRegion(int lid, int mid, const TVector3& pos) {
  if (lid == kGTR100) {
//    if (gtr100_dead_area->IsXOK(mid, pos.X()) && gtr100_dead_area->IsYOK(mid, pos.Y())) {
    if (gtr100_dead_area->IsXOK(mid, pos.X())) {
      return false;
    }
  } else if (kGTR200) {
    if (gtr200_dead_area->IsXOK(mid, pos.X()) && gtr200_dead_area->IsYOK(mid, pos.Y())) {
      return false;
    }
  } else if (kGTR300) {
    if (gtr300_dead_area->IsXOK(mid, pos.X()) && gtr300_dead_area->IsYOK(mid, pos.Y())) {
      return false;
    }
  }
  return true;
}

bool E16ANA_MakeDummyDST1::IsHBDDeadRegion(int mid, const TVector3& pos) {
//  if (mid == 103) {
//    if (pos.X() > 0 && pos.Y() < 0) {
//      return true;
//    }
//  } else if (mid == 104) {
//    if (pos.X() < 0 && pos.Y() > 0) {
//      return true;
//    }
//  } else if (mid == 106) {
//    if (pos.X() < 0 && pos.Y() < 0) {
//      return true;
//    }
//  } else if (mid == 107) {
//    if (pos.X() > 0 || pos.Y() > 0) {
//      return true;
//    }
//  } else {
//    return true;
//  }
//  return false;
  double cog[2] = {pos.X(), pos.Y()};
  auto status = hbd_dead_ch->StatusWLocalCoordinate(mid, cog);
  if (status == 0) {
    return false;
  }
  return true;
}

bool E16ANA_MakeDummyDST1::IsDeadRegion(E16ANA_MockTrack& track) {
  const auto& ssd_mid    = track.SSD().ModuleID();
  const auto& gtr100_mid = track.GTR1().ModuleID();
  const auto& gtr200_mid = track.GTR2().ModuleID();
  const auto& gtr300_mid = track.GTR3().ModuleID();
  const auto& hbd_mid    = track.HBDback().ModuleID();
  const auto& lg_mid     = track.LGVD().ModuleID();
  const auto& ssd_pos    = track.SSD().XTV();
  const auto& gtr100_pos = track.GTR1().XTV();
  const auto& gtr200_pos = track.GTR2().XTV();
  const auto& gtr300_pos = track.GTR3().XTV();
  const auto& hbd_pos    = track.HBDback().XTV();
  const auto& lg_pos     = track.LGVD().XTV();
  
  if (IsSSDDeadRegion(ssd_mid, ssd_pos)) {
cout << "SSD dead" << endl;
    return true;
  }
  if (IsGTRDeadRegion(kGTR100, gtr100_mid, gtr100_pos)) {
cout << "GTR100 dead" << endl;
    return true;
  }
  if (IsGTRDeadRegion(kGTR200, gtr200_mid, gtr200_pos)) {
cout << "GTR200 dead" << endl;
    return true;
  }
  if (IsGTRDeadRegion(kGTR300, gtr300_mid, gtr300_pos)) {
cout << "GTR300 dead" << endl;
    return true;
  }
  if (IsHBDDeadRegion(hbd_mid, hbd_pos)) {
cout << "HBD dead" << endl;
    return true;
  }
//  if (IsLGDeadRegion(lg_mid, lg_pos)) {
//    return true;
//  }
  return false;
}

#ifdef GEOM_VER0
bool E16ANA_MakeDummyDST1::IsAType(int module_id) {
  if (module_id % 2 == 1) {
    return true;
  }
  return false;
}
#endif // GEOM_VER0

array<double, 2> E16ANA_MakeDummyDST1::DistributeTiming(int detector_id, double t) {
#ifndef WO_LAYER_EFF
  double mean;
  double sigma;
  if (detector_id == kSSD) {
    mean  = kSSDTimeMean;
    sigma = kSSDTimeSigma;
  } else if (detector_id == kGTR) {
    mean  = kGTRTimeMean;
    sigma = kGTRTimeSigma;
  }
  random_device seed_gen;
  default_random_engine engine(seed_gen());
  normal_distribution<> dist(mean, sigma);
  auto time = dist(engine);
  if (detector_id == kSSD) {
    return {time, 0.};
  }
  normal_distribution<> xy_dist(time, kGTRXYTimeSigma);
  return {xy_dist(engine), xy_dist(engine)};
#else
  return {0., 0.};
#endif
}

int E16ANA_MakeDummyDST1::GTRClusterSize(int type, E16ANA_MockHit& hit) {
#ifndef WO_LAYER_EFF
  auto mom = hit.PTV();
  double length = kGTRDriftSigma;
  if (type == kGTRx) {
    length += fabs(kGTRDriftLength * mom.X() / mom.Z());
  } else {
    length += fabs(kGTRDriftLength * mom.Y() / mom.Z());
  }
  return int{length / kGTRStripPitch[type]} + 1;
#else
  return 2;
#endif
}

void E16ANA_MakeDummyDST1::MergeMockToRealData(E16ANA_MockTrack& track, E16DST_DST1PhysicsRecord* record) {
  auto num_tracks = record->SSD().NumClusters();
  auto ssd     = E16DST_DST1SSDCluster();
  auto gtr100x = E16DST_DST1GTRCluster();
  auto gtr100y = E16DST_DST1GTRCluster();
  auto gtr200x = E16DST_DST1GTRCluster();
  auto gtr200y = E16DST_DST1GTRCluster();
  auto gtr300x = E16DST_DST1GTRCluster();
  auto gtr300y = E16DST_DST1GTRCluster();
  auto hbd     = E16DST_DST1HBDCluster();
  auto lg      = E16DST_DST1LGHit();
  auto& mock_ssd    = track.SSD();
  auto& mock_gtr100 = track.GTR1();
  auto& mock_gtr200 = track.GTR2();
  auto& mock_gtr300 = track.GTR3();
  auto& mock_hbd    = track.HBDback();
  auto& mock_lg     = track.LGVD();
  auto ssd_t    = DistributeTiming(kSSD, mock_ssd.Time());
  auto gtr100_t = DistributeTiming(kGTR, mock_gtr100.Time());
  auto gtr200_t = DistributeTiming(kGTR, mock_gtr200.Time());
  auto gtr300_t = DistributeTiming(kGTR, mock_gtr300.Time());
  
  ssd.SetClusterId(kMockClusterID);
  ssd.SetModuleId(mock_ssd.ModuleID());
#ifndef GEOM_VER0
  ssd.SetCogPos(mock_ssd.Xsmear(kSSDXSigma));
#else
  if (IsAType(mock_ssd.ModuleID())) {
    ssd.SetCogPos(-1. * mock_ssd.X());
  } else {
    ssd.SetCogPos(mock_ssd.X());
  }
#endif
  ssd.SetTimingFit(ssd_t[0]);
  
  gtr100x.SetClusterId(kMockClusterID + kGTR100x);
  gtr100x.SetLayerId(0);
  gtr100x.SetType(0);
  gtr100x.SetModuleId(mock_gtr100.ModuleID());
#ifndef GEOM_VER0
  gtr100x.SetTdcPos(mock_gtr100.Xsmear(kGTRXYSigma[0][0]) - E16DST_DST1Constant::kGTRLorentzAngle[0]);
#else // GEOM_VER0
  if (IsAType(mock_gtr100.ModuleID())) {
    gtr100x.SetTdcPos(mock_gtr100.X() - E16DST_DST1Constant::kGTRLorentzAngle[0]);
  } else {
    gtr100x.SetTdcPos(-1. * mock_gtr100.X() - E16DST_DST1Constant::kGTRLorentzAngle[0]);
  }
#endif // GEOM_VER0
  gtr100x.SetTiming(gtr100_t[0]);
  gtr100x.SetPeakSum(kGTRADC);
  gtr100x.SetNumHits(GTRClusterSize(kGTRx, mock_gtr100));

  gtr100y.SetClusterId(kMockClusterID + kGTR100y);
  gtr100y.SetLayerId(0);
  if (gtr100x.LocalXT() >= 0) {
    gtr100y.SetType(1);
  } else {
    gtr100y.SetType(2);
  }
  gtr100y.SetModuleId(mock_gtr100.ModuleID());
#ifndef GEOM_VER0
  gtr100y.SetTdcPos(mock_gtr100.Ysmear(kGTRXYSigma[0][1])); // xt?, xt2?
#else
  gtr100y.SetTdcPos(-1. * mock_gtr100.Y()); // xt?, xt2?
#endif
  gtr100y.SetTiming(gtr100_t[1]);
  gtr100y.SetPeakSum(kGTRADC);
  gtr100y.SetNumHits(GTRClusterSize(kGTRy, mock_gtr100));
  
  gtr200x.SetClusterId(kMockClusterID + kGTR200x);
  gtr200x.SetLayerId(1);
  gtr200x.SetType(0);
  gtr200x.SetModuleId(mock_gtr200.ModuleID());
#ifndef GEOM_VER0
  gtr200x.SetTdcPos(mock_gtr200.Xsmear(kGTRXYSigma[1][0]) - E16DST_DST1Constant::kGTRLorentzAngle[1]);
#else
  if (IsAType(mock_gtr200.ModuleID())) {
    gtr200x.SetTdcPos(-1. * mock_gtr200.X() - E16DST_DST1Constant::kGTRLorentzAngle[1]);
  } else {
    gtr200x.SetTdcPos(mock_gtr200.X() - E16DST_DST1Constant::kGTRLorentzAngle[1]);
  }
#endif
  gtr200x.SetTiming(gtr200_t[0]);
  gtr200x.SetPeakSum(kGTRADC);
  gtr200x.SetNumHits(GTRClusterSize(kGTRx, mock_gtr200));
  
  gtr200y.SetClusterId(kMockClusterID + kGTR200y);
  gtr200y.SetLayerId(1);
  gtr200y.SetType(1);
  gtr200y.SetModuleId(mock_gtr200.ModuleID());
  gtr200y.SetTdcPos(mock_gtr200.Ysmear(kGTRXYSigma[1][1]));
  gtr200y.SetTiming(gtr200_t[1]);
  gtr200y.SetPeakSum(kGTRADC);
  gtr200y.SetNumHits(GTRClusterSize(kGTRy, mock_gtr200));
  
  gtr300x.SetClusterId(kMockClusterID + kGTR300x);
  gtr300x.SetLayerId(2);
  gtr300x.SetType(0);
  gtr300x.SetModuleId(mock_gtr300.ModuleID());
#ifndef GEOM_VER0
  gtr300x.SetTdcPos(mock_gtr300.Xsmear(kGTRXYSigma[2][0]) - E16DST_DST1Constant::kGTRLorentzAngle[2]);
#else
  if (IsAType(mock_gtr300.ModuleID())) {
    gtr300x.SetTdcPos(-1. * mock_gtr300.X() - E16DST_DST1Constant::kGTRLorentzAngle[2]);
  } else {
    gtr300x.SetTdcPos(mock_gtr300.X() - E16DST_DST1Constant::kGTRLorentzAngle[2]);
  }
#endif
  gtr300x.SetTiming(gtr300_t[0]);
  gtr300x.SetPeakSum(kGTRADC);
  gtr300x.SetNumHits(GTRClusterSize(kGTRx, mock_gtr300));
  
  gtr300y.SetClusterId(kMockClusterID + kGTR300y);
  gtr300y.SetLayerId(2);
  gtr300y.SetType(1);
  gtr300y.SetModuleId(mock_gtr300.ModuleID());
  gtr300y.SetTdcPos(mock_gtr300.Ysmear(kGTRXYSigma[2][1]));
  gtr300y.SetTiming(gtr300_t[1]);
  gtr300y.SetPeakSum(kGTRADC);
  gtr300y.SetNumHits(GTRClusterSize(kGTRy, mock_gtr300));
  
  hbd.SetClusterId(kMockClusterID);
  hbd.SetModuleId(mock_hbd.ModuleID());
  hbd.SetPeakSum(kHBDPE);
  hbd.SetTiming(kHBDTime);
  hbd.SetNumHits(kHBDSize);
  hbd.SetFastestTiming(kHBDFTime);
  hbd.SetClusterSize(kHBDSize);
  hbd.SetLocalPos(mock_hbd.XTV());
  hbd.SetEProb(kHBDEProb);
  
  lg.SetHitId(kMockClusterID);
  lg.SetIds(mock_lg.ModuleID(), -9999.);
  lg.SetLocalPos(mock_lg.XTV());
  lg.SetFitPeak(kLGADC);
  lg.SetFitTiming(kLGTime);
  lg.SetFitFlag(0);
  
  record->SSD().PushBackCluster(ssd);
  record->GTR().PushBackCluster(gtr100x);
  record->GTR().PushBackCluster(gtr100y);
  record->GTR().PushBackCluster(gtr200x);
  record->GTR().PushBackCluster(gtr200y);
  record->GTR().PushBackCluster(gtr300x);
  record->GTR().PushBackCluster(gtr300y);
  record->HBD().PushBackCluster(hbd);
  record->LG().PushBackHit(lg);
#ifdef SIM_DST1_GEOM_CHECK
cout << "mock pos" << endl;
cout << "module " << mock_ssd.ModuleID() << " " << mock_gtr100.ModuleID() << " " << mock_gtr200.ModuleID() << " " << mock_gtr300.ModuleID() << endl;
cout << "SSD " << mock_ssd.X()    << " " << mock_ssd.Y()    << " " << mock_ssd.Z()    << endl;
cout << "100 " << mock_gtr100.X() << " " << mock_gtr100.Y() << " " << mock_gtr100.Z() << endl;
cout << "200 " << mock_gtr200.X() << " " << mock_gtr200.Y() << " " << mock_gtr200.Z() << endl;
cout << "300 " << mock_gtr300.X() << " " << mock_gtr300.Y() << " " << mock_gtr300.Z() << endl;
cout << "DST1 pos" << endl;
cout << "SSD " << ssd.LocalPos().X()                                        << endl;
cout << "100 " << gtr100x.LocalPosT().X() << " " << gtr100y.LocalPosT().Y() << endl;
cout << "200 " << gtr200x.LocalPosT().X() << " " << gtr200y.LocalPosT().Y() << endl;
cout << "300 " << gtr300x.LocalPosT().X() << " " << gtr300y.LocalPosT().Y() << endl;
cout << "mock global pos" << endl;
cout << "SSD " << mock_ssd.GX()    << " " << mock_ssd.GY()    << " " << mock_ssd.GZ()    << endl;
cout << "100 " << mock_gtr100.GX() << " " << mock_gtr100.GY() << " " << mock_gtr100.GZ() << endl;
cout << "200 " << mock_gtr200.GX() << " " << mock_gtr200.GY() << " " << mock_gtr200.GZ() << endl;
cout << "300 " << mock_gtr300.GX() << " " << mock_gtr300.GY() << " " << mock_gtr300.GZ() << endl;
#endif //SIM_DST1_GEOM_CHECK
  return;
}

#endif // TRACK_EFF_CHECK
