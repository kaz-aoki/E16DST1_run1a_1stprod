#include <iostream>
#include <TFile.h>
#include <TTree.h>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_WaveformFitter.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_HBDCalibration.hh"
#include "E16ANA_HBDCut.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16DST_DST1DefaultFilePath.hh"

#include "E16ANA_TrackAnalyzerFromTree.hh"
#include "E16ANA_TrackAnalyzerFromTreeParameterV2.hh"

using namespace std;

//const TString kFileNameHeader = "/ccj/w/data03a/E16/user/ichikawa/lsf_file/21102900-v2/root/";
const TString kFileNameHeader = "/ccj/w/data03z/E16/ichikawa/lsf_file/22013102-v1/root/";

const int kAnalyzeFlag = E16ANA_TrackAnalyzerFromTreeParameter::kElectronFlag; // 0 : electron, 1 : pion (Ks)
//const int kAnalyzeFlag = E16ANA_TrackAnalyzerFromTreeParameter::kPionFlag; // 0 : electron, 1 : pion (Ks)
//const int kAnalyzeFlag = E16ANA_TrackAnalyzerFromTreeParameter::kBothFlag; // 0 : electron, 1 : pion (Ks)

int main(int argc, char* argv[]) {
  if (argc != 4) {
    cerr << "./bin [output.root] [begin run ID] [end run ID]" << endl;
    return -1;
  }
  auto out_file_name = argv[1];
  auto begin_run_id = stoi(argv[2]);
  auto end_run_id = stoi(argv[3]);
  
  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  E16ANA_GeometryV2::SetGlobalPointer(geometry);
  auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
  bfield_map->Initialize_binary();
  E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
  E16ANA_MultiTrack pair_fitter(bfield_map, geometry, 2);

  auto in_chain = new TChain("tree", "tree");
  for (int i = begin_run_id; i <= end_run_id; ++i) {
    in_chain->Add(kFileNameHeader + Form("run%06d*", i));
  }

  auto out_file = new TFile(out_file_name, "recreate");
  E16ANA_TrackAnalyzerFromTree analyzer(in_chain, kAnalyzeFlag, geometry, bfield_map, &pair_fitter, out_file);
  analyzer.Loop();
  
  delete out_file;
  delete geometry;
  delete bfield_map;
  delete in_chain;
  return 0;
}
