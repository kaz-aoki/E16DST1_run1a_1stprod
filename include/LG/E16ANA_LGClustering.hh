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
    double lz;

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
    double lz;
  };

  E16ANA_LGClustering();
    ~E16ANA_LGClustering(){}

  void SetHitData(int hid, int mid, int cid, float peak, float timing, float integral, double lx, double ly, double lz);
  void Clustering();
  void ClusteringXY();
  void CalcTimeRegion(std::vector<lghit>& hits, double& tim_max, double& tim_min);
  void CalcLocalXRegion(std::vector<lghit>& hits, double& lx_max, double& lx_min);
  void CalcLocalYRegion(std::vector<lghit>& hits, double& ly_max, double& ly_min);
  int CalcHitsToCluster(std::vector<lghit>& hits, lgcluster& cluster);
  int LGClusterSize(){ return lgclusters.size(); }
  lgcluster& LGClusterIth(int n){ return lgclusters.at(n); }

protected:

private:

  const double time_diff_threshold = 4;
  const double lx_threshold = 126;
  const double ly_threshold = 168;
  std::vector<lghit> lghits;
  std::vector<lgcluster> lgclusters;

};

#endif //E16ANA_LGClustering_h
