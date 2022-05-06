#ifndef E16ANA_MAKEDUMMYDST1_HH
#define E16ANA_MAKEDUMMYDST1_HH

#include <array>
#include <fstream>

#include "TString.h"
#include "E16ANA_GTRStatus.h"
#include "E16ANA_HBDDeadChannel.hh"
#include "E16ANA_LGDeadChannel.hh"
#include "E16ANA_MakeDummyDST1Parameter.hh"
#include "E16DST_DST1.hh"
#include "mockdataIOtestSimple.hh"

class E16ANA_MakeDummyDST1 {
 public:
  E16ANA_MakeDummyDST1(E16ANA_GTR100GEMDeadArea* _gtr100_dead_area, E16ANA_GTR200GEMDeadArea* _gtr200_dead_area, E16ANA_GTR300GEMDeadArea* _gtr300_dead_area,
                       E16ANA_HBDDeadChannel* _hbd_dead_ch, E16ANA_LGDeadChannel* _lg_dead_ch)
      : gtr100_dead_area(_gtr100_dead_area), gtr200_dead_area(_gtr200_dead_area), gtr300_dead_area(_gtr300_dead_area), hbd_dead_ch(_hbd_dead_ch), lg_dead_ch(_lg_dead_ch) {}
  ~E16ANA_MakeDummyDST1() {}
  bool IsSSDDeadRegion(int mid, const TVector3& pos);
  bool IsGTRDeadRegion(int lid, int mid, const TVector3& pos);
  bool IsHBDDeadRegion(int mid, const TVector3& pos);
  bool IsLGDeadRegion(int mid, const TVector3& pos);
  bool IsDeadRegion(E16ANA_MockTrack& track);
  bool IsAType(int module_id);
  std::array<double, 2> DistributeTiming(int detector_id, double t);
  int GTRClusterSize(int type, E16ANA_MockHit& hit);
  void MergeMockToRealData(E16ANA_MockTrack& track, E16DST_DST1PhysicsRecord* record);
 private:
  E16ANA_GTR100GEMDeadArea* gtr100_dead_area;
  E16ANA_GTR200GEMDeadArea* gtr200_dead_area;
  E16ANA_GTR300GEMDeadArea* gtr300_dead_area;
  E16ANA_HBDDeadChannel*    hbd_dead_ch;
  E16ANA_LGDeadChannel*     lg_dead_ch;
};

#endif //E16ANA_MAKEDUMMYDST1_HH
