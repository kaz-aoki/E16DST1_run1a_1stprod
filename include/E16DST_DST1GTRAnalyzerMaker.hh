#ifndef E16DST_DST1GTRAnalyzerMaker_h
#define E16DST_DST1GTRAnalyzerMaker_h


#include "E16ANA_GTRAnalyzer2.h"
#include "E16ANA_GTRStripAnalyzer.h"
#include "E16ANA_GTRPedestal.h"
#include "OnlineGTRUtility.h"
#include "E16DST_DST1.hh"

class E16DST_DST1GTRAnalyzerMaker {
public:
    enum { n_layers = 3 };
    E16DST_DST1GTRAnalyzerMaker();
    ~E16DST_DST1GTRAnalyzerMaker();
   bool Exists(uint16_t module_id, uint16_t layer_id);
   void Analyze(E16DST_DST0Detector<E16DST_DST0GTRHit> &hits0);
   void SetPedestal(E16ANA_GTRPedestal *pedestal);
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



#endif //E16DST_DST1GTRAnalyzerMaker_h
