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

#include "E16ANA_TrackAnalyzerFromTreeV2.hh"
#include "E16ANA_TrackAnalyzerFromTreeParameterV2.hh"

using namespace std;

constexpr int kAnalyzeFlag = E16ANA_TrackAnalyzerFromTreeParameter::kElectronFlag; // 0 : electron, 1 : pion (Ks)
//constexpr int kAnalyzeFlag = E16ANA_TrackAnalyzerFromTreeParameter::kPionFlag; // 0 : electron, 1 : pion (Ks)
//constexpr int kAnalyzeFlag = E16ANA_TrackAnalyzerFromTreeParameter::kBothFlag; // 0 : electron, 1 : pion (Ks)
//constexpr int kAnalyzeFlag = E16ANA_TrackAnalyzerFromTreeParameter::kPionWoRefitFlag; // 0 : electron, 1 : pion (Ks)
//constexpr int kAnalyzeFlag = E16ANA_TrackAnalyzerFromTreeParameter::kPionWClusterDup; // 0 : electron, 1 : pion (Ks)
//constexpr int kAnalyzeFlag = E16ANA_TrackAnalyzerFromTreeParameter::kPionWDiffChargeYClusterDup; // 0 : electron, 1 : pion (Ks)

//constexpr bool kIsEventMix = true;
constexpr bool kIsEventMix = false;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "./bin [input.root] [output.root]" << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  
  FILE* fp = fopen(in_file_name, "r");
  if (!fp) {
    cerr << "could not open file : " << in_file_name << endl;
    return -1;
  }
  fclose(fp);

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  E16ANA_GeometryV2::SetGlobalPointer(geometry);
  auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
  bfield_map->Initialize_binary();
  E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
  E16ANA_MultiTrack pair_fitter(bfield_map, geometry, 2);

  auto in_file = new TFile(in_file_name);
  auto in_tree = dynamic_cast<TTree*>(in_file->Get("tree"));
  auto out_file = new TFile(out_file_name, "recreate");
  E16ANA_TrackAnalyzerFromTree analyzer(in_tree, kAnalyzeFlag, kIsEventMix, geometry, bfield_map, &pair_fitter, out_file);
  analyzer.Loop();

  delete geometry;
  delete bfield_map;
  delete in_tree;
  delete in_file;
  delete out_file;
  return 0;
}
