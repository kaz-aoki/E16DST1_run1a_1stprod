#ifndef __E16ANA_STSAnalyzer_hh_
#define __E16ANA_STSAnalyzer_hh_


#include "E16DST_DST1.hh"
#include <vector>
#include <numeric>

struct E16ANA_STSClusterParam {
  int adc_thresh = 0;
  int tdc_window = 60;
  int allowed_strip_jump = 0;
  
  //int timing_min = -115;
  //int timing_max = -86;
  int timing_min = -120;
  int timing_max = -70;
};

class E16ANA_STSCluster{
public:
  std::vector<E16DST_DST1STSHit> hits;
  int adc();
  double tdc();
  double cog();
  double timing();
  
  void show() {
    std::cout << "STSCluster:" << std::endl;
    for ( auto iter = hits.begin(); iter != hits.end(); iter++){
      std::cout << "mod=" << iter->ModuleId() << ", PN=" << iter->PN() << ", Strip=" << iter->StripId() <<
	", tdc=" << iter->TDC() << ", timing=" << iter->Timing() << ", adc=" << iter->ADC() << std::endl;
    }
    std::cout << "  adc_sum=" << adc() << ",  tdc=" << tdc() << ", timing=" << timing() << ", cog=" << cog() << std::endl;
  }
};


class E16ANA_STSAnalyzer{
public:
  E16ANA_STSAnalyzer() {;}
  void sort(std::vector<E16DST_DST1STSHit>& hits1);
  void clusterize(std::vector<E16DST_DST1STSHit>& hits1, std::vector<E16DST_DST1STSCluster>& clusters1);
  void fill_dst1(std::vector<E16DST_DST1STSCluster>& clusters1);
  
  void set_param(E16ANA_STSClusterParam _param) { param = _param; }
  E16ANA_STSClusterParam get_param() { return param; }
private:
  E16ANA_STSClusterParam param;
  std::vector<E16ANA_STSCluster> vec_cluster;

};

#endif
