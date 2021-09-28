#include "E16ANA_SSDAnalyzer.h"
#include "E16DST_DST1SSDAnalyzerMaker.hh"

E16DST_DST1SSDAnalyzerMaker::E16DST_DST1SSDAnalyzerMaker(){
  for(int moduleID=101; moduleID<110; moduleID++){
    analyzer_map[OnlineGTR::IDs(moduleID,0).value64] = new E16ANA_SSDAnalyzer();
  }
}
