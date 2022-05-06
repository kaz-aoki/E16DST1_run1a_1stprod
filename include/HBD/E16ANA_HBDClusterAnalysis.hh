#ifndef E16ANA_HBDClusterAnalysis_h
#define E16ANA_HBDClusterAnalysis_h

#include "E16ANA_HBDConstant.hh"
#include "E16ANA_HBDChannelManager.hh"

#include <vector>
#include <iostream>

/*
  1, clustering is perfomed module by module. So the cluster which has hits across multiple modules
  does not reconstructed into a single cluster.
  (the number of these clusters may be negligibly small, because the physical distance between
  modules along the pad planes is longer than the typical blob size.)

  2, if there is pile-up events in a pad (multiple hits in a pad), the hit with the largest adc is added to the sadc and spe of a cluster.
  But all pile-up hits are added to vector id, adc, and tdc of a cluster in order to
  do re-clustering after some analysis.
 */

class E16ANA_HBDClusterAnalysis{
  
 public:
  struct hbd_cluster{
    int module_id;
    int cid;             // cluster id in a module
    double sadc;         // sum of adc of a cluster member pad
    double spe;          // sum of photoelectrons of a cluster member pad
    double time_diff;    // timing difference between the fastest and latest pad tdc
    double fastest_tdc;
    double average_time;
    int max_adc_id; // max adc pad id
    double max_adc;
    int max_pe_id;
    double max_pe;
    double lpos_w_adc[3];// local position with adc weight
    double lpos_w_pe[3]; // local position with pe weight
    int size;            // number of pads
    std::vector<int> id; // pad id belong to a cluster
    std::vector<double> adc;
    std::vector<double> pe;
    std::vector<double> tdc;
    std::vector<int16_t> dst_id; // dst hit id belong to a cluster
    std::vector<int> pileup_id;
    std::vector<double> pileup_adc;
    std::vector<double> pileup_pe;
    std::vector<double> pileup_tdc;
    std::vector<int> pileup_dst_id;
    void Show(){ std::cerr<<module_id<<" "<<cid<<" "<<sadc<<" "<<spe<<" "<<time_diff<<" "<<size<<std::endl; };
  };
  
  E16ANA_HBDClusterAnalysis(const int module_id);
  E16ANA_HBDClusterAnalysis();
  ~E16ANA_HBDClusterAnalysis();
  void Clear();
  void SetModuleID(const int _module_id){ module_id = _module_id; };
  int GetModuleID(){return module_id;};
  void SetData(const int module_id, const int pad_id, const double _adc, const double _pe, const double _tdc);
  void SetData(const int module_id, const int pad_id, const double _adc, const double _pe, const double _tdc, const int dst_id);
  bool DoClustering();
  bool SubClustering(const int pad_id, hbd_cluster &cluster, int &n_call);
  void ShowClusters();
  std::vector<hbd_cluster> GetClusters(){return clusters;};
  std::vector<hbd_cluster> *GetClustersPointer(){return &clusters;};
  static hbd_cluster GetMaxADCCluster(std::vector<hbd_cluster> &_clusters);
  static hbd_cluster GetMaxSizeCluster(std::vector<hbd_cluster> &_clusters);
 
private:
  void CalcTimeDiff(hbd_cluster &cluster);
  void CalcLocalPositionWADCWeight(hbd_cluster &cluster);
  void CalcLocalPositionWPEWeight(hbd_cluster &cluster);
  void CalcMaxADCPadID(hbd_cluster &cluster);
  void CalcMaxPEPadID(hbd_cluster &cluster);
  void CalcMaxADC(hbd_cluster &cluster);
  void CalcMaxPE(hbd_cluster &cluster);
  void CalcAverageTime(hbd_cluster &cluster);
  
  enum {
    n_pads = HBD_Module_Constant::n_pads
  };

  int module_id;
  std::vector<int> hit_padid;// hit pad id
  std::vector<int> hit_dstid[n_pads];//number of hits in a pad is sometimes 2 or more due to pile-up
  std::vector<double> adc[n_pads];
  std::vector<double> pe[n_pads];
  std::vector<double> tdc[n_pads];
  std::vector<hbd_cluster> clusters;
};
#endif // E16ANA_HBDClusterAnalysis_h
