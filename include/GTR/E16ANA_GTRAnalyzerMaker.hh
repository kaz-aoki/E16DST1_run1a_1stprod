#ifndef E16ANA_GTRAnalyzerMaker_hh
#define E16ANA_GTRAnalyzerMaker_hh


#include "E16ANA_GTRAnalyzer2.h"
#include "E16ANA_GTRStripAnalyzer.h"
#include "E16ANA_GTRPedestal.h"
#include "OnlineGTRUtility.h"
#include "E16DST_DST1.hh"

class E16ANA_GTRAnalyzerMaker {
public:
    enum { n_layers = 3 };
    E16ANA_GTRAnalyzerMaker();
    ~E16ANA_GTRAnalyzerMaker();
   bool Exists(uint16_t module_id, uint16_t layer_id);
   void Clear();
   void SetThresholdX(double th);
   void SetThresholdY(double th);
   void SetTOTThresholdX(double th);
   void SetTOTThresholdY(double th);
   void Set(void (E16ANA_GTRAnalyzer2::*f)(double), double th);
   OnlineGTR::HashMap<E16ANA_GTRAnalyzer2 *> analyzer_map;
   E16ANA_GTRAnalyzer2 *Chamber(uint16_t module_id, uint16_t layer_id){
      return analyzer_map[OnlineGTR::IDs(module_id, layer_id).value64];
   }
private:
};



#endif //E16ANAGTRAnalyzerMaker_hh
