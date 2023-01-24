#ifndef E16ANA_MAKEDUMMYDST1_HH
#define E16ANA_MAKEDUMMYDST1_HH

#include <array>
#include <fstream>

#include "TString.h"
#include "E16ANA_GTRAnalyzerMaker.hh"
#include "E16ANA_GTRStatus.h"
#include "E16ANA_HBDDeadChannel.hh"
#include "E16ANA_LGDeadChannel.hh"
#include "E16ANA_MakeDummyDST1Parameter.hh"
#include "E16ANA_MockTrackOutputData.hh"
#include "E16DST_DST1.hh"
//#include "mockdataIOtestSimple.hh"

class E16ANA_MakeDummyDST1 {
 public:
  E16ANA_MakeDummyDST1(int _smear_flag,
                       E16ANA_GTRAnalyzerMaker* _gtr_analyzers, E16ANA_GTRStatus* _gtr_stat, E16ANA_GTRASDDeadChannel* _gtr_asd_dead_ch,
                       E16ANA_HBDDeadChannel* _hbd_dead_ch, E16ANA_LGDeadChannel* _lg_dead_ch)
      : smear_flag(_smear_flag), gtr_analyzers(_gtr_analyzers), gtr_stat(_gtr_stat), gtr_asd_dead_ch(_gtr_asd_dead_ch),
        hbd_dead_ch(_hbd_dead_ch), lg_dead_ch(_lg_dead_ch) {}
//  E16ANA_MakeDummyDST1(int run_id);
  ~E16ANA_MakeDummyDST1() {}
  int GTRYToASDCh(double y);
  bool IsGTRASDDeadRegion(int mid, const TVector3& pos);
  int HBDPosToASDCh(const TVector3& pos);
  bool IsHBDASDDeadRegion(int mid, const TVector3& pos);
  bool IsLGDiscriDeadRegion(int mid, const TVector3& pos);
  bool IsDiscriDeadRegion(E16ANA_MockTrack& track);
  bool IsSSDDeadRegion(int mid, const TVector3& pos);
  bool IsGTRDeadRegion(int lid, int mid, const TVector3& pos);
  bool IsHBDDeadRegion(int mid, const TVector3& pos);
  bool IsLGDeadRegion(int mid, const TVector3& pos);
  bool IsDeadRegion(E16ANA_MockTrack& track);
  bool IsAType(int module_id);
  std::array<double, 2> DistributeTiming(int detector_id, double t);
  int GTRClusterSize(int type, E16ANA_MockHit& hit);
  bool IsOverlap(int detector_id, const double x[], const int size[], const float t[]);
  void MergeMockToRealData(int cluster_id_offset, E16ANA_MockTrack& track, E16DST_DST1PhysicsRecord* record);
 private:
  struct MergedValues {
    double x;
    float  t;
    int    size;
  };
  int                       smear_flag;
  E16ANA_GTRAnalyzerMaker*  gtr_analyzers;
  E16ANA_GTRStatus*         gtr_stat;
  E16ANA_GTRASDDeadChannel* gtr_asd_dead_ch;
  E16ANA_HBDDeadChannel*    hbd_dead_ch;
  E16ANA_LGDeadChannel*     lg_dead_ch;
};

#endif //E16ANA_MAKEDUMMYDST1_HH
