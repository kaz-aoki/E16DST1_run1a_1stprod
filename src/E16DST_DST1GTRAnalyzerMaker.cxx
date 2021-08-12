#include "E16ANA_GTRAnalyzer2.h"
#include "E16DST_DST1GTRAnalyzerMaker.hh"

E16DST_DST1GTRAnalyzerMaker::E16DST_DST1GTRAnalyzerMaker()
{
    for (int module_id = 100; module_id <= 110; module_id++){
        analyzer_map[OnlineGTR::IDs(module_id, 0).value64] = new E16ANA_GTR100Analyzer();
        analyzer_map[OnlineGTR::IDs(module_id, 1).value64] = new E16ANA_GTR200Analyzer();
        analyzer_map[OnlineGTR::IDs(module_id, 2).value64] = new E16ANA_GTR300Analyzer();
    }
}


E16DST_DST1GTRAnalyzerMaker::~E16DST_DST1GTRAnalyzerMaker()
{
   for (auto &a : analyzer_map) {
      delete a.second;
   }
}

void E16DST_DST1GTRAnalyzerMaker::Clear()
{
   for (auto &a : analyzer_map) {
      a.second->Clear();
   }
}

void E16DST_DST1GTRAnalyzerMaker::SetThresholdX(double th)
{
   for (auto &a : analyzer_map) {
      a.second->SetThresholdX(th);
   }
}

void E16DST_DST1GTRAnalyzerMaker::SetThresholdY(double th)
{
   for (auto &a : analyzer_map) {
      a.second->SetThresholdY(th);
   }
}

void E16DST_DST1GTRAnalyzerMaker::SetTOTThresholdX(double th)
{
   for (auto &a : analyzer_map) {
      a.second->SetTOTThresholdX(th);
   }
}

void E16DST_DST1GTRAnalyzerMaker::SetTOTThresholdY(double th)
{
   for (auto &a : analyzer_map) {
      a.second->SetTOTThresholdY(th);
   }
}

void E16DST_DST1GTRAnalyzerMaker::Set(void (E16ANA_GTRAnalyzer2::*f)(double), double th)
{
   for (auto &a : analyzer_map) {
      (a.second->*f)(th);
   }
}

