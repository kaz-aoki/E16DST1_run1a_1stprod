#include <iostream>

#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_MagneticFieldMap.hh"
#include "E16ANA_MultiTrack.hh"
#include "E16ANA_TrackConstant.hh"

using namespace std;
using namespace E16ANA_TrackConstant;

const TVector3 kVertexSigma = {3., 3., 0.};
const TVector3 kDetectorSigma[4] = {{0.1, 0., 0.}, {0.3, 1., 0.}, {0.3, 1., 0.}, {0.3, 1., 0.}};
constexpr double kStepSize = 1.;
constexpr int    kMaxSteps= 400;
constexpr bool   kVertexXyFixFlag = false;
constexpr bool   kPyFixFlag = false;
constexpr bool   kVertexZFixFlag = true;
constexpr int    kMinuitStrategy = 2;
constexpr int    kMaxFunctionCalls = 1.0e4;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "./bin input.root output.root" << endl;
    return -1;
  }
  auto in_file_name  = static_cast<TString>(argv[1]);
  auto out_file_name = static_cast<TString>(argv[2]);

  auto in_file = new TFile(in_file_name);
  auto in_tree = dynamic_cast<TTree*>(in_file->Get("tree"));
  int run_id;
  int event_id;
  int n_pairs;
  vector<int>*    minus_track_id     = nullptr;
  vector<int>*    plus_track_id      = nullptr;
  vector<int>*    minus_ssd_mid      = nullptr;
  vector<int>*    minus_gtr100_mid   = nullptr;
  vector<int>*    minus_gtr200_mid   = nullptr;
  vector<int>*    minus_gtr300_mid   = nullptr;
  vector<int>*    plus_ssd_mid       = nullptr;
  vector<int>*    plus_gtr100_mid    = nullptr;
  vector<int>*    plus_gtr200_mid    = nullptr;
  vector<int>*    plus_gtr300_mid    = nullptr;
  vector<double>* chi_square         = nullptr;
  vector<double>* vtx_gx             = nullptr;
  vector<double>* vtx_gy             = nullptr;
  vector<double>* vtx_gz             = nullptr;
  vector<double>* minus_mom_gx       = nullptr;
  vector<double>* minus_mom_gy       = nullptr;
  vector<double>* minus_mom_gz       = nullptr;
  vector<double>* plus_mom_gx        = nullptr;
  vector<double>* plus_mom_gy        = nullptr;
  vector<double>* plus_mom_gz        = nullptr;
  vector<double>* minus_ssd_hit_x    = nullptr;
  vector<double>* minus_ssd_hit_y    = nullptr;
//  vector<double>* minus_ssd_hit_z    = nullptr;
  vector<double>* minus_gtr100_hit_x = nullptr;
  vector<double>* minus_gtr100_hit_y = nullptr;
//  vector<double>* minus_gtr100_hit_z = nullptr;
  vector<double>* minus_gtr200_hit_x = nullptr;
  vector<double>* minus_gtr200_hit_y = nullptr;
//  vector<double>* minus_gtr200_hit_z = nullptr;
  vector<double>* minus_gtr300_hit_x = nullptr;
  vector<double>* minus_gtr300_hit_y = nullptr;
//  vector<double>* minus_gtr300_hit_z = nullptr;
  vector<double>* plus_ssd_hit_x     = nullptr;
  vector<double>* plus_ssd_hit_y     = nullptr;
//  vector<double>* plus_ssd_hit_z     = nullptr;
  vector<double>* plus_gtr100_hit_x  = nullptr;
  vector<double>* plus_gtr100_hit_y  = nullptr;
//  vector<double>* plus_gtr100_hit_z  = nullptr;
  vector<double>* plus_gtr200_hit_x  = nullptr;
  vector<double>* plus_gtr200_hit_y  = nullptr;
//  vector<double>* plus_gtr200_hit_z  = nullptr;
  vector<double>* plus_gtr300_hit_x  = nullptr;
  vector<double>* plus_gtr300_hit_y  = nullptr;
//  vector<double>* plus_gtr300_hit_z  = nullptr;
  vector<double>* minus_ssd_res_x    = nullptr;
  vector<double>* minus_ssd_res_y    = nullptr;
//  vector<double>* minus_ssd_res_z    = nullptr;
  vector<double>* minus_gtr100_res_x = nullptr;
  vector<double>* minus_gtr100_res_y = nullptr;
//  vector<double>* minus_gtr100_res_z = nullptr;
  vector<double>* minus_gtr200_res_x = nullptr;
  vector<double>* minus_gtr200_res_y = nullptr;
//  vector<double>* minus_gtr200_res_z = nullptr;
  vector<double>* minus_gtr300_res_x = nullptr;
  vector<double>* minus_gtr300_res_y = nullptr;
//  vector<double>* minus_gtr300_res_z = nullptr;
  vector<double>* plus_ssd_res_x     = nullptr;
  vector<double>* plus_ssd_res_y     = nullptr;
//  vector<double>* plus_ssd_res_z     = nullptr;
  vector<double>* plus_gtr100_res_x  = nullptr;
  vector<double>* plus_gtr100_res_y  = nullptr;
//  vector<double>* plus_gtr100_res_z  = nullptr;
  vector<double>* plus_gtr200_res_x  = nullptr;
  vector<double>* plus_gtr200_res_y  = nullptr;
//  vector<double>* plus_gtr200_res_z  = nullptr;
  vector<double>* plus_gtr300_res_x  = nullptr;
  vector<double>* plus_gtr300_res_y  = nullptr;
//  vector<double>* plus_gtr300_res_z  = nullptr;
  in_tree->SetBranchAddress("run_id",   &run_id);
  in_tree->SetBranchAddress("event_id", &event_id);
  in_tree->SetBranchAddress("n_pairs", &n_pairs);
  in_tree->SetBranchAddress("minus_track_id", &minus_track_id);
  in_tree->SetBranchAddress("plus_track_id", &plus_track_id);
  in_tree->SetBranchAddress("minus_ssd_mid", &minus_ssd_mid);
  in_tree->SetBranchAddress("minus_gtr100_mid", &minus_gtr100_mid);
  in_tree->SetBranchAddress("minus_gtr200_mid", &minus_gtr200_mid);
  in_tree->SetBranchAddress("minus_gtr300_mid", &minus_gtr300_mid);
  in_tree->SetBranchAddress("plus_ssd_mid", &plus_ssd_mid);
  in_tree->SetBranchAddress("plus_gtr100_mid", &plus_gtr100_mid);
  in_tree->SetBranchAddress("plus_gtr200_mid", &plus_gtr200_mid);
  in_tree->SetBranchAddress("plus_gtr300_mid", &plus_gtr300_mid);
  in_tree->SetBranchAddress("chi_square", &chi_square);
  in_tree->SetBranchAddress("vtx_gx", &vtx_gx);
  in_tree->SetBranchAddress("vtx_gy", &vtx_gy);
  in_tree->SetBranchAddress("vtx_gz", &vtx_gz);
  in_tree->SetBranchAddress("minus_mom_gx", &minus_mom_gx);
  in_tree->SetBranchAddress("minus_mom_gy", &minus_mom_gy);
  in_tree->SetBranchAddress("minus_mom_gz", &minus_mom_gz);
  in_tree->SetBranchAddress("plus_mom_gx", &plus_mom_gx);
  in_tree->SetBranchAddress("plus_mom_gy", &plus_mom_gy);
  in_tree->SetBranchAddress("plus_mom_gz", &plus_mom_gz);
  in_tree->SetBranchAddress("minus_ssd_hit_x", &minus_ssd_hit_x);
  in_tree->SetBranchAddress("minus_ssd_hit_y", &minus_ssd_hit_y);
  in_tree->SetBranchAddress("minus_gtr100_hit_x", &minus_gtr100_hit_x);
  in_tree->SetBranchAddress("minus_gtr100_hit_y", &minus_gtr100_hit_y);
  in_tree->SetBranchAddress("minus_gtr200_hit_x", &minus_gtr200_hit_x);
  in_tree->SetBranchAddress("minus_gtr200_hit_y", &minus_gtr200_hit_y);
  in_tree->SetBranchAddress("minus_gtr300_hit_x", &minus_gtr300_hit_x);
  in_tree->SetBranchAddress("minus_gtr300_hit_y", &minus_gtr300_hit_y);
  in_tree->SetBranchAddress("plus_ssd_hit_x", &plus_ssd_hit_x);
  in_tree->SetBranchAddress("plus_ssd_hit_y", &plus_ssd_hit_y);
  in_tree->SetBranchAddress("plus_gtr100_hit_x", &plus_gtr100_hit_x);
  in_tree->SetBranchAddress("plus_gtr100_hit_y", &plus_gtr100_hit_y);
  in_tree->SetBranchAddress("plus_gtr200_hit_x", &plus_gtr200_hit_x);
  in_tree->SetBranchAddress("plus_gtr200_hit_y", &plus_gtr200_hit_y);
  in_tree->SetBranchAddress("plus_gtr300_hit_x", &plus_gtr300_hit_x);
  in_tree->SetBranchAddress("plus_gtr300_hit_y", &plus_gtr300_hit_y);
  in_tree->SetBranchAddress("minus_ssd_res_x", &minus_ssd_res_x);
  in_tree->SetBranchAddress("minus_ssd_res_y", &minus_ssd_res_y);
  in_tree->SetBranchAddress("minus_gtr100_res_x", &minus_gtr100_res_x);
  in_tree->SetBranchAddress("minus_gtr100_res_y", &minus_gtr100_res_y);
  in_tree->SetBranchAddress("minus_gtr200_res_x", &minus_gtr200_res_x);
  in_tree->SetBranchAddress("minus_gtr200_res_y", &minus_gtr200_res_y);
  in_tree->SetBranchAddress("minus_gtr300_res_x", &minus_gtr300_res_x);
  in_tree->SetBranchAddress("minus_gtr300_res_y", &minus_gtr300_res_y);
  in_tree->SetBranchAddress("plus_ssd_res_x", &plus_ssd_res_x);
  in_tree->SetBranchAddress("plus_ssd_res_y", &plus_ssd_res_y);
  in_tree->SetBranchAddress("plus_gtr100_res_x", &plus_gtr100_res_x);
  in_tree->SetBranchAddress("plus_gtr100_res_y", &plus_gtr100_res_y);
  in_tree->SetBranchAddress("plus_gtr200_res_x", &plus_gtr200_res_x);
  in_tree->SetBranchAddress("plus_gtr200_res_y", &plus_gtr200_res_y);
  in_tree->SetBranchAddress("plus_gtr300_res_x", &plus_gtr300_res_x);
  in_tree->SetBranchAddress("plus_gtr300_res_y", &plus_gtr300_res_y);
  auto out_file = new TFile(out_file_name, "recreate");
  auto out_tree = new TTree("tree", "tree");
  int    out_minus_track_id;
  int    out_plus_track_id;
  int    removed_charge;
  int    removed_layer;
  int    module_id[2][4];
  double pre_chi_square;
  double pre_vtx_gx;
  double pre_vtx_gy;
  double pre_vtx_gz;
  double pre_detector_x[2][4];
  double pre_detector_y[2][4];
  double pre_detector_res_x[2][4];
  double pre_detector_res_y[2][4];
  double post_chi_square;
  double post_vtx_gx;
  double post_vtx_gy;
  double post_vtx_gz;
  double post_detector_x[2][4];
  double post_detector_y[2][4];
  double post_detector_res_x[2][4];
  double post_detector_res_y[2][4];
  out_tree->Branch("run_id", &run_id, "run_id/I");
  out_tree->Branch("event_id", &event_id, "event_id/I");
  out_tree->Branch("minus_track_id", &out_minus_track_id, "minus_track_id/I");
  out_tree->Branch("plus_track_id", &out_plus_track_id, "plus_track_id/I");
  out_tree->Branch("removed_charge", &removed_charge, "removed_charge/I");
  out_tree->Branch("removed_layer", &removed_layer, "removed_layer/I");
  out_tree->Branch("module_id", &module_id, "module_id[2][4]/I");
  out_tree->Branch("pre_chi_square", &pre_chi_square, "pre_chi_square/D");
  out_tree->Branch("pre_vtx_gx", &pre_vtx_gx, "pre_vtx_gx/D");
  out_tree->Branch("pre_vtx_gy", &pre_vtx_gy, "pre_vtx_gy/D");
  out_tree->Branch("pre_vtx_gz", &pre_vtx_gz, "pre_vtx_gz/D");
  out_tree->Branch("pre_detector_x", &pre_detector_x, "pre_detector_x[2][4]/D");
  out_tree->Branch("pre_detector_y", &pre_detector_y, "pre_detector_x[2][4]/D");
  out_tree->Branch("pre_detector_res_x", &pre_detector_res_x, "pre_detector_res_x[2][4]/D");
  out_tree->Branch("pre_detector_res_y", &pre_detector_res_y, "pre_detector_res_y[2][4]/D");
  out_tree->Branch("post_chi_square", &post_chi_square, "post_chi_square/D");
  out_tree->Branch("post_vtx_gx", &post_vtx_gx, "post_vtx_gx/D");
  out_tree->Branch("post_vtx_gy", &post_vtx_gy, "post_vtx_gy/D");
  out_tree->Branch("post_vtx_gz", &post_vtx_gz, "post_vtx_gz/D");
  out_tree->Branch("post_detector_x", &post_detector_x, "post_detector_x[2][4]/D");
  out_tree->Branch("post_detector_y", &post_detector_y, "post_detector_x[2][4]/D");
  out_tree->Branch("post_detector_res_x", &post_detector_res_x, "post_detector_res_x[2][4]/D");
  out_tree->Branch("post_detector_res_y", &post_detector_res_y, "post_detector_res_y[2][4]/D");

  auto geometry = new E16ANA_GeometryV2("/ccj/u/E16/database/geometry/v2/geometry_Run0c_211006b_ymorino_220122.dat");
  E16ANA_GeometryV2::SetGlobalPointer(geometry);
  auto bfield_map = new E16ANA_MagneticFieldMap3D("/ccj/u/E16/database/fieldmap/Bmap-SKS-block-far-191218-2450A-rev1.binary");
  bfield_map->Initialize_binary();
  E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
  E16ANA_MultiTrack fitter(bfield_map, geometry, 2);
  
  auto n_entries = in_tree->GetEntries();
  vector<int> minus_track_ids;
  vector<int> plus_track_ids;
  for (int entry_i = 0; entry_i < n_entries; ++entry_i) {
    if (entry_i % 100 == 0) {
      cout << entry_i << " / " << n_entries << endl;
    }
    in_tree->GetEntry(entry_i);
    minus_track_ids.clear();
    plus_track_ids.clear();
    for (int pair_i = 0; pair_i < n_pairs; ++pair_i) {
      bool minus_is_used = false;
      bool plus_is_used = false;
      for (const auto& id : minus_track_ids) {
        if (id == minus_track_id->at(pair_i)) {
          minus_is_used = true;
          break;
        }
      }
      for (const auto& id : plus_track_ids) {
        if (id == plus_track_id->at(pair_i)) {
          plus_is_used = true;
          break;
        }
      }
      if (minus_is_used || plus_is_used) {
        continue;
      }
      auto zero_sigma = TVector3(0., 0., 0.);
      auto init_pos = TVector3(vtx_gx->at(pair_i), vtx_gy->at(pair_i), vtx_gz->at(pair_i));
      double charges[2] = {-1., 1.};
      TVector3 moms[2] = {TVector3(minus_mom_gx->at(pair_i), minus_mom_gy->at(pair_i), minus_mom_gz->at(pair_i)),
                          TVector3(plus_mom_gx->at(pair_i),  plus_mom_gy->at(pair_i),  plus_mom_gz->at(pair_i))};
      int mids[2][4] = {{minus_ssd_mid->at(pair_i), minus_gtr100_mid->at(pair_i), minus_gtr200_mid->at(pair_i), minus_gtr300_mid->at(pair_i)},
                        {plus_ssd_mid->at(pair_i),  plus_gtr100_mid->at(pair_i),  plus_gtr200_mid->at(pair_i),  plus_gtr300_mid->at(pair_i)}};
      TVector3 lposs[2][4] = {{TVector3(minus_ssd_hit_x->at(pair_i),    minus_ssd_hit_y->at(pair_i),    0.),
                               TVector3(minus_gtr100_hit_x->at(pair_i), minus_gtr100_hit_y->at(pair_i), 0.),
                               TVector3(minus_gtr200_hit_x->at(pair_i), minus_gtr200_hit_y->at(pair_i), 0.),
                               TVector3(minus_gtr300_hit_x->at(pair_i), minus_gtr300_hit_y->at(pair_i), 0.)},
                              {TVector3(plus_ssd_hit_x->at(pair_i),     plus_ssd_hit_y->at(pair_i),     0.),
                               TVector3(plus_gtr100_hit_x->at(pair_i),  plus_gtr100_hit_y->at(pair_i),  0.),
                               TVector3(plus_gtr200_hit_x->at(pair_i),  plus_gtr200_hit_y->at(pair_i),  0.),
                               TVector3(plus_gtr300_hit_x->at(pair_i),  plus_gtr300_hit_y->at(pair_i),  0.)}};
      TVector3 ress[2][4] = {{TVector3(minus_ssd_res_x->at(pair_i),    minus_ssd_res_y->at(pair_i),    0.),
                              TVector3(minus_gtr100_res_x->at(pair_i), minus_gtr100_res_y->at(pair_i), 0.),
                              TVector3(minus_gtr200_res_x->at(pair_i), minus_gtr200_res_y->at(pair_i), 0.),
                              TVector3(minus_gtr300_res_x->at(pair_i), minus_gtr300_res_y->at(pair_i), 0.)},
                             {TVector3(plus_ssd_res_x->at(pair_i),     plus_ssd_res_y->at(pair_i),     0.),
                              TVector3(plus_gtr100_res_x->at(pair_i),  plus_gtr100_res_y->at(pair_i),  0.),
                              TVector3(plus_gtr200_res_x->at(pair_i),  plus_gtr200_res_y->at(pair_i),  0.),
                              TVector3(plus_gtr300_res_x->at(pair_i),  plus_gtr300_res_y->at(pair_i),  0.)}};
      for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
          module_id[i][j]          = mids[i][j];
          pre_detector_x[i][j]     = lposs[i][j].X();
          pre_detector_y[i][j]     = lposs[i][j].Y();
          pre_detector_res_x[i][j] = ress[i][j].X();
          pre_detector_res_y[i][j] = ress[i][j].Y();
        }
      }
      pre_chi_square = chi_square->at(pair_i);
      
      for (int charge_i = 0; charge_i < 2; ++charge_i) {
        if (charge_i == 0) {
          removed_charge = -1;
        } else {
          removed_charge = 1;
        }
        for (int layer_i = 0; layer_i < 4; ++layer_i) {
          removed_layer = layer_i;
          fitter.Clear();
          fitter.SetInitialVertex(TVector3(0., 0., vtx_gz->at(pair_i)), kVertexSigma);
          for (int i = 0; i < 2; ++i) {
            fitter.SetCharge(i, charges[i]);
            fitter.SetInitialMomentum(i, moms[i]);
            for (int l = 0; l < 4; ++l) {
              auto mid2013 = ModuleID2020To2013(mids[i][l]);
              if (l == 0) {
                if (charge_i == i && layer_i == l) {
                  fitter.AddHit(i, l, geometry->SSD(mid2013), lposs[i][l], zero_sigma);
                } else {
                  fitter.AddHit(i, l, geometry->SSD(mid2013), lposs[i][l], kDetectorSigma[l]);
                }
              } else {
                if (charge_i == i && layer_i == l) {
                  fitter.AddHit(i, l, geometry->GTR(mid2013, l - 1), lposs[i][l], zero_sigma);
                } else {
                  fitter.AddHit(i, l, geometry->GTR(mid2013, l - 1), lposs[i][l], kDetectorSigma[l]);
                }
              }
            }
          }
          fitter.SetRungeKuttaStepSize(kStepSize);
          fitter.SetMaxSteps(kMaxSteps);
          post_chi_square = fitter.Fit(kVertexXyFixFlag, kPyFixFlag, kVertexZFixFlag, kMinuitStrategy, kMaxFunctionCalls);
cout << post_chi_square << endl;
          auto tmp_vtx = fitter.GetFitVertex();
          post_vtx_gx = tmp_vtx.X();
          post_vtx_gy = tmp_vtx.Y();
          post_vtx_gz = tmp_vtx.Z();
          for (int i = 0; i < 2; ++i) {
            for (int l = 0; l < 4; ++l) {
              const int hid = 0;
              std::vector<int>      tmp_mid;
              std::vector<TVector3> tmp_lpos;
              std::vector<TVector3> tmp_lres;
              fitter.GetFitLPos(i,     l, tmp_mid, tmp_lpos);
              fitter.GetFitResidual(i, l, tmp_mid, tmp_lres);
              post_detector_x[i][l]     = tmp_lpos[hid].X();
              post_detector_y[i][l]     = tmp_lpos[hid].Y();
              post_detector_res_x[i][l] = tmp_lres[hid].X();
              post_detector_res_y[i][l] = tmp_lres[hid].Y();
            }
          }
          out_tree->Fill();
        }
      }
    }
  }
  out_file->Write();
  
  delete in_tree;
  delete in_file;
  return 0;
}
