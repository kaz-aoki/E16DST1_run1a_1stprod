#include "E16ANA_LGOnlineAnalyzer.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>

#include <TH1.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "TROOT.h"

//ichikawa function
#include <array>
#include <vector>
#include "E16ANA_StepTrack.hh"
#include "E16DST_DST1.hh"

void ProjectionHBDAndLG(E16ANA_GeometryV2* geometry, E16ANA_MultiTrack* pair_fitter, const TVector3& vertex, const TVector3& mom, double charge, int mid[], TVector3 out_lposs[], TVector3 out_gposs[], TVector3 out_lmoms[], TVector3 out_gmoms[]) {
  const int n_layers = E16ANA_TrackConstant::kNumDetectorLayers - E16ANA_TrackConstant::kHBD;
  const int tid = 0;
  const TVector3 lpos(0., 0., 0.);
  const TVector3 lsigma(0., 0., 0.);
  const int lid = 0; // only 1 layer in 1 RK
  const int hid = 0; // only 1 hit in 1 RK
  const int max_steps = 2000;
  const int tmp_lg_block_id[3] = {0, 10, 20};
  const TVector3 error_vector = {-10000., -10000., -10000.};

  std::vector<int> mids;
  std::vector<TVector3> lposs;
  std::vector<TVector3> lmoms;
  for (int l = 0; l < n_layers; ++l) {
    if (mid[l] < 0) {
      out_lposs[l] = error_vector;
      out_gposs[l] = error_vector;
      out_lmoms[l] = error_vector;
      out_gmoms[l] = error_vector;
      continue;
    }
    auto mid2013 = E16ANA_TrackConstant::ModuleID2020To2013_27(mid[l]);
    pair_fitter->Clear();
    if (l == 0) { // HBD
      auto tmp_geom = geometry->HBD(mid2013);
      pair_fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
    } else {
      auto tmp_geom = geometry->LG(mid2013, tmp_lg_block_id[l - 1]);
      pair_fitter->AddHit(tid, lid, tmp_geom, lpos, lsigma);
    }
    pair_fitter->SetMaxSteps(max_steps);
    pair_fitter->RungeKuttaTracking(tid, vertex, mom, charge);
    pair_fitter->GetFitLPos(tid, lid, mids, lposs);
    pair_fitter->GetFitLMom(tid, lid, mids, lmoms);
    out_lmoms[l] = lmoms[hid];
    if (l == 0) {
      out_lposs[l] = lposs[hid];
      out_gposs[l] = geometry->HBD(mid2013)->GetGPos(lposs[hid]);
      out_gmoms[l] = geometry->HBD(mid2013)->GetGMom(lmoms[hid]);
    } else {
      out_gposs[l] = geometry->LG(mid2013, tmp_lg_block_id[l - 1])->GetGPos(lposs[hid]);
      out_lposs[l] = geometry->LGVD(mid2013)->GetLPos(out_gposs[l]);
      out_gmoms[l] = geometry->LG(mid2013, tmp_lg_block_id[l - 1])->GetGMom(lmoms[hid]);
    }
  }
  return;
}
//ichikawa function

int main(int argc, char* argv[]) {

   if ( argc!=1 ) {
     std::cerr << "./bin" << std::endl;
     return -1;
   }
   // auto run_id = stoi(argv[1]);
   // auto infile = argv[2];
   // auto in_chain = new TChain("tree", "tree");
   // in_chain->Add(Form("%s",infile));
   // E16ANA_LGOnlineAnalyzer* t = new E16ANA_LGOnlineAnalyzer(in_chain);
   // t->MakePDF(run_id, outfile, maxevent);
   // delete in_chain;

   auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
   E16ANA_GeometryV2::SetGlobalPointer(geometry);
   auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
   bfield_map->Initialize_binary();
   E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
   E16ANA_MultiTrack pair_fitter(bfield_map, geometry, 2);

   TVector3 vertex(0., 0., -80.);
   TVector3 mom(3.69189, 0., 14.9927);
   double charge = 1.;
   int mid[4]={106,106,106,106};
   TVector3 out_lposs[4];
   TVector3 out_gposs[4];
   TVector3 out_lmoms[4];
   TVector3 out_gmoms[4];

   ProjectionHBDAndLG(geometry, &pair_fitter, vertex, mom,charge,mid,out_lposs,out_gposs,out_lmoms,out_gmoms);

   std::cout<<out_lposs[0].X()<<" "<<out_lposs[0].Y()<<" "<<out_lposs[0].Z()<<std::endl;
   std::cout<<out_lmoms[0].X()<<" "<<out_lmoms[0].Y()<<" "<<out_lmoms[0].Z()<<" "<<out_lmoms[0].Mag()<<std::endl;
   std::cout<<out_lposs[1].X()<<" "<<out_lposs[1].Y()<<" "<<out_lposs[1].Z()<<std::endl;
   std::cout<<out_lmoms[1].X()<<" "<<out_lmoms[1].Y()<<" "<<out_lmoms[1].Z()<<" "<<out_lmoms[1].Mag()<<std::endl;

   return 0;

}
