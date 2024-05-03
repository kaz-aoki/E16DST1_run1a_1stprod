#include <iostream>
#include <TFile.h>
#include <TTree.h>

#include "SingleTrackAnalyzerForRes.hh"
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

//constexpr int kAnalyzeFlag = E16ANA_TrackAnalyzerFromTreeParameter::kElectronFlag; // 0 : electron, 1 : pion (Ks)
//constexpr int kAnalyzeFlag = E16ANA_TrackAnalyzerFromTreeParameter::kPionFlag; // 0 : electron, 1 : pion (Ks)
constexpr int kAnalyzeFlag = E16ANA_TrackAnalyzerFromTreeParameter::kBothFlag; // 0 : electron, 1 : pion (Ks)
//constexpr int kAnalyzeFlag = E16ANA_TrackAnalyzerFromTreeParameter::kPionWoRefitFlag; // 0 : electron, 1 : pion (Ks)
//constexpr int kAnalyzeFlag = E16ANA_TrackAnalyzerFromTreeParameter::kPionWClusterDup; // 0 : electron, 1 : pion (Ks)
//constexpr int kAnalyzeFlag = E16ANA_TrackAnalyzerFromTreeParameter::kPionWDiffChargeYClusterDup; // 0 : electron, 1 : pion (Ks)

constexpr bool kIsEventMix = true;
//constexpr bool kIsEventMix = false;

int main(int argc, char* argv[]) {
  if (argc != 5) {
    cerr << "./bin [input.root] [output.root] [maxevent] [module of track@HBD]" << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  int maxevent = stoi(argv[3]);
  int hbd_track_module = stoi(argv[4]);
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
  //E16ANA_MultiTrack pair_fitter(bfield_map, geometry, 2);
  auto in_chain = new TChain("tree", "tree");
  in_chain->Add(in_file_name);
  //auto in_file = new TFile(in_file_name);
//  auto in_tree = dynamic_cast<TTree*>(in_file->Get("tree1"));
//  auto out_file = new TFile(out_file_name, "recreate");
  SingleTrackAnalyzerForRes *t = new SingleTrackAnalyzerForRes(in_chain);
  t->MkTreeForTrackSelection(0, maxevent, out_file_name, hbd_track_module, 0, 100000, geometry, bfield_map);//runoption, maxevent, outfile, hbdmodule, charge, max chi2, geom, bfield
  
  //E16ANA_TrackAnalyzerFromTree analyzer(in_tree, kAnalyzeFlag, kIsEventMix, geometry, bfield_map, &pair_fitter, out_file);
  //analyzer.Loop();


  delete geometry;
  delete bfield_map;
//  delete in_tree;
//  delete in_file;
 // delete out_file;
  delete in_chain;
  return 0;
}




