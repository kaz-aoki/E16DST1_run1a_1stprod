#ifndef E16ANA_LGClustering_h
#define E16ANA_LGClustering_h

#include "E16DST_DST0.hh"
#include "E16DST_Constant.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1Constant.hh"
#include "E16ANA_LGConstant.hh"
#include "E16ANA_LGBasic.hh"
#include <set>
#include <TGraph.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1.h>


class E16ANA_LGClustering
{

public:

  struct lghit{
    int hid;
    int mid;
    int cid;
    float peak;
    float timing;
    float integral;
    double lx;
    double ly;

    bool operator<(const lghit& another){
      if( mid != another.mid ){ return mid<another.mid; }
      if( cid != another.cid ){ return cid<another.cid; }
      return timing < another.timing;
    }

  };

  struct lgcluster{
    std::vector<int16_t> hids;
    int mid;
    float peaksum;
    float fasttiming;
    float timediff;
    float intsum;
    int maxcid;
    float maxpeak;
    double lx;
    double ly;
  };

  E16ANA_LGClustering();
    ~E16ANA_LGClustering(){}

  void SetHitData(int hid, int mid, int cid, float peak, float timing, float integral, double lx, double ly);
  void Clustering();
  void CalcTimeRegion(std::vector<lghit>& hits, double& tim_max, double& tim_min);
  int CalcHitsToCluster(std::vector<lghit>& hits, lgcluster& cluster);
  int LGClusterSize(){ return lgclusters.size(); }
  lgcluster& LGClusterIth(int n){ return lgclusters.at(n); }

protected:

private:

  const double time_diff_threshold = 10;
  std::vector<lghit> lghits;
  std::vector<lgcluster> lgclusters;

};

#endif //E16ANA_LGClustering_h
