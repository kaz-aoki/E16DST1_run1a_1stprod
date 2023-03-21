#include <iostream>

#include "TChain.h"
#include "TFile.h"
#include "TString.h"
#include "TTree.h"

#include "check_lorentz_effect_220918.h"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DefaultFilePath.hh"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3 && argc != 4) {
    cerr << "./bin input.root output.root" << endl;
    cerr << "./bin input_header output.root hoge" << endl;
    return -1;
  }
  auto in_name  = static_cast<TString>(argv[1]);
  auto out_name = static_cast<TString>(argv[2]);
  
  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  E16ANA_GeometryV2::SetGlobalPointer(geometry);
  auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
  bfield_map->Initialize_binary();
  E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
  E16ANA_MultiTrack fitter(bfield_map, geometry, 1);
  
  if (argc == 3) {
    auto file = TFile(in_name);
    auto tree = dynamic_cast<TTree*>(file.Get("tree"));
    auto analyzer = check_lorentz_effect_220918(tree);
    analyzer.Set(geometry, bfield_map, &fitter);
    analyzer.Loop(out_name);
  } else {
    auto chain = TChain("tree");
    chain.Add(in_name + "*");
    auto analyzer = check_lorentz_effect_220918(&chain);
    analyzer.Set(geometry, bfield_map, &fitter);
    analyzer.Loop(out_name);
  }
  return 0;
}
