#ifndef __E16ANA_STSAnalyzer_hh_
#define __E16ANA_STSAnalyzer_hh_


#include "E16DST_DST1.hh"

struct E16ANA_STSClusterParam {
  int adc_thresh = 0;
  int tdc_window = 10;
  int allowed_strip_jump = 0;
};

class E16ANA_STSAnalyzer{
public:
  E16ANA_STSAnalyzer() {;}
  void sort(std::vector<E16DST_DST1STSHit>& hits1);
  void clusterize(std::vector<E16DST_DST1STSHit>& hits1, std::vector<E16DST_DST1STSCluster>& clusters1);
  
  void set_param(E16ANA_STSClusterParam _param) { param = _param; }
  E16ANA_STSClusterParam get_param() { return param; }
private:
  E16ANA_STSClusterParam param;

};

#endif
