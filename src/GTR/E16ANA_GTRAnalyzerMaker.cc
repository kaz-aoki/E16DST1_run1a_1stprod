#include "GTR/E16ANA_GTRAnalyzer2.h"
#include "GTR/E16ANA_GTRAnalyzerMaker.hh"

E16ANA_GTRAnalyzerMaker::E16ANA_GTRAnalyzerMaker(E16ANA_GTRcalibParams &gtr_params){
    for (int module_id = 100; module_id <= 110; module_id++){
        analyzer_map[OnlineGTR::IDs(module_id, 0).value64] = new E16ANA_GTR100Analyzer();
        analyzer_map[OnlineGTR::IDs(module_id, 1).value64] = new E16ANA_GTR200Analyzer();
        analyzer_map[OnlineGTR::IDs(module_id, 2).value64] = new E16ANA_GTR300Analyzer();
    }
    for (int module_id = 100; module_id <= 110; module_id++){
		for(int layer_id=0; layer_id<3; layer_id++){
			Chamber(module_id, layer_id)->SetThresholdX(gtr_params.GetParams(module_id, layer_id).ThresholdX());
			Chamber(module_id, layer_id)->SetThresholdY(gtr_params.GetParams(module_id, layer_id).ThresholdY());
			Chamber(module_id, layer_id)->SetTOTThresholdX(gtr_params.GetParams(module_id, layer_id).TOTThresholdX());
			Chamber(module_id, layer_id)->SetTOTThresholdY(gtr_params.GetParams(module_id, layer_id).TOTThresholdY());
			Chamber(module_id, layer_id)->SetBadPedestalThresholdX(gtr_params.GetParams(module_id, layer_id).BadPedestalThresholdX());
			Chamber(module_id, layer_id)->SetBadPedestalThresholdY(gtr_params.GetParams(module_id, layer_id).BadPedestalThresholdY());
			Chamber(module_id, layer_id)->SetBadPedestalSigmaThresholdX(gtr_params.GetParams(module_id, layer_id).BadPedestalSigmaThresholdX());
			Chamber(module_id, layer_id)->SetBadPedestalSigmaThresholdY(gtr_params.GetParams(module_id, layer_id).BadPedestalSigmaThresholdY());
			Chamber(module_id, layer_id)->SetTimeWindowMin(gtr_params.GetParams(module_id, layer_id).TimeWindowMin());
			Chamber(module_id, layer_id)->SetTimeWindowMax(gtr_params.GetParams(module_id, layer_id).TimeWindowMax());
			Chamber(module_id, layer_id)->SetClusterMinimumGap(gtr_params.GetParams(module_id, layer_id).ClusterMinGap());
			Chamber(module_id, layer_id)->SetClusterDeltaTdc(gtr_params.GetParams(module_id, layer_id).ClusterDeltaTDC());
			Chamber(module_id, layer_id)->SetRiseTimeMin(gtr_params.GetParams(module_id, layer_id).RiseTimeMin());
			Chamber(module_id, layer_id)->SetRiseTimeMax(gtr_params.GetParams(module_id, layer_id).RiseTimeMax());
//			Chamber(module_id, layer_id)->SetTdcMin(gtr_params.GetParams(module_id, layer_id).TdcMin());
//			Chamber(module_id, layer_id)->SetTdcMax(gtr_params.GetParams(module_id, layer_id).TdcMax());
			Chamber(module_id, layer_id)->SetDriftVelocity(gtr_params.GetParams(module_id, layer_id).DriftVelocity());
			Chamber(module_id, layer_id)->SetCenterOfDriftGap(gtr_params.GetParams(module_id, layer_id).CenterOfDriftGap());
			Chamber(module_id,layer_id)->SetPeakTimeMin(gtr_params.GetParams(module_id,layer_id).PeakTimeMin());
			Chamber(module_id,layer_id)->SetPeakTimeMax(gtr_params.GetParams(module_id,layer_id).PeakTimeMax());
		}
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


