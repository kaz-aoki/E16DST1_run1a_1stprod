#ifndef E16DST_DST1SSDAnalyzerMaker_h
#define eE16DST_DST1SSDAnalyzerMaker_h

#include "E16ANA_SSDAnalyzer.h"
#include "E16ANA_SSDStripAnalyzer.h"
#include "OnlineGTRUtility.h"
#include "E16DST_DST1.hh"

class E16DST_DST1SSDAnalyzerMaker{
public:
  E16DST_DST1SSDAnalyzerMaker();
  ~E16DST_DST1SSDAnalyzerMaker();
  void Analyze(E16DST_DST0Detector<E16DST_DST0SSDHit> &hits0);
  OnlineGTR::HashMap<E16ANA_SSDAnalyzer *> analyzer_map;
private:
};
#endif
