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

#include "track_analyzer_220715.h";

using namespace std;

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
  E16ANA_MultiTrack fitter(bfield_map, geometry, 2);
  E16ANA_MultiTrack proj_fitter(bfield_map, geometry, 1);

  auto in_file = new TFile(in_file_name);
  auto in_tree = dynamic_cast<TTree*>(in_file->Get("tree"));
  auto analyzer = track_analyzer_220715(in_tree, geometry, bfield_map, &fitter, &proj_fitter);
  analyzer.Loop(out_file_name);

  delete geometry;
  delete bfield_map;
  delete in_tree;
  delete in_file;
  return 0;
}
