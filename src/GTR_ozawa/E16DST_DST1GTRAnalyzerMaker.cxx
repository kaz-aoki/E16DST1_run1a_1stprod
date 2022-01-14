//#include "GTR/E16ANA_GTRAnalyzer2.h"
//#include "GTR/E16ANA_GTRAnalyzerMaker.hh"
#include "E16ANA_GTRAnalyzer2.h"
#include "E16ANA_GTRAnalyzerMaker.hh"

E16ANA_GTRAnalyzerMaker::E16ANA_GTRAnalyzerMaker()
{
    for (int module_id = 100; module_id <= 110; module_id++){
        analyzer_map[OnlineGTR::IDs(module_id, 0).value64] = new E16ANA_GTR100Analyzer();
        analyzer_map[OnlineGTR::IDs(module_id, 1).value64] = new E16ANA_GTR200Analyzer();
        analyzer_map[OnlineGTR::IDs(module_id, 2).value64] = new E16ANA_GTR300Analyzer();
    }
}

E16ANA_GTRAnalyzerMaker::~E16ANA_GTRAnalyzerMaker()
{
   for (auto &a : analyzer_map) {
      delete a.second;
   }
}

void E16ANA_GTRAnalyzerMaker::Clear()
{
   for (auto &a : analyzer_map) {
      a.second->Clear();
   }
}

void E16ANA_GTRAnalyzerMaker::SetThresholdX(double th)
{
   for (auto &a : analyzer_map) {
      a.second->SetThresholdX(th);
   }
}

void E16ANA_GTRAnalyzerMaker::SetThresholdY(double th)
{
   for (auto &a : analyzer_map) {
      a.second->SetThresholdY(th);
   }
}

void E16ANA_GTRAnalyzerMaker::SetTOTThresholdX(double th)
{
   for (auto &a : analyzer_map) {
      a.second->SetTOTThresholdX(th);
   }
}

void E16ANA_GTRAnalyzerMaker::SetTOTThresholdY(double th)
{
   for (auto &a : analyzer_map) {
      a.second->SetTOTThresholdY(th);
   }
}

void E16ANA_GTRAnalyzerMaker::Set(void (E16ANA_GTRAnalyzer2::*f)(double), double th)
{
   for (auto &a : analyzer_map) {
      (a.second->*f)(th);
   }
}

void E16ANA_GTRAnalyzerMaker::SetInteger(void (E16ANA_GTRAnalyzer2::*f)(int), int th)
{
   for (auto &a : analyzer_map) {
      (a.second->*f)(th);
   }
}
