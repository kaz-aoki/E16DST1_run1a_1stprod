#include <iostream>
#include "TChain.h"
#include "TFile.h"
#include "TString.h"
#include "TTree.h"

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

#include "track_analyzer_220715.h";

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3 && argc != 4) {
    cerr << "./bin input.root output.root" << endl;
    cerr << "./bin input_path (include /) output.root xxx" << endl;
    return -1;
  }
  auto in_name  = static_cast<TString>(argv[1]);
  auto out_name = static_cast<TString>(argv[2]);
  
  if (argc == 3) {
    FILE* fp = fopen(in_name, "r");
    if (!fp) {
      cerr << "could not open file : " << in_name << endl;
      return -1;
    }
    fclose(fp);
  }

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  E16ANA_GeometryV2::SetGlobalPointer(geometry);
  auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
  bfield_map->Initialize_binary();
  E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
  E16ANA_MultiTrack fitter(bfield_map, geometry, 2);
  E16ANA_MultiTrack proj_fitter(bfield_map, geometry, 1);
  
  if (argc == 3) {
    auto in_file = TFile(in_name);
    auto in_tree = dynamic_cast<TTree*>(in_file.Get("tree"));
    auto analyzer = track_analyzer_220715(in_tree, geometry, bfield_map, &fitter, &proj_fitter);
    analyzer.Loop(out_name);
    delete in_tree;
  } else {
    auto in_chain = TChain("tree");
    in_chain.Add(in_name + "*");
    auto analyzer = track_analyzer_220715(&in_chain, geometry, bfield_map, &fitter, &proj_fitter);
    analyzer.Loop(out_name);
  }

  delete geometry;
  delete bfield_map;
  return 0;
}
