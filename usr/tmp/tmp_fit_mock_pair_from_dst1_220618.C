//#define FROM_MOCK
//#define WO_PAIR_FIT

#define tmp_fit_mock_pair_from_dst1_220618_cxx
#include "tmp_fit_mock_pair_from_dst1_220618.h"

#include <iostream>

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "E16ANA_GeometryV2.hh"
//#include "E16ANA_MagneticFieldMap.hh"
#include "E16ANA_MultiTrack.hh"
#include "E16ANA_StepTrack.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "tmp_fit_mock_pair_220616_parameter.hh"

using namespace std;
using namespace tmp_fit_mock_pair_220616_parameter;

TVector3 tmp_fit_mock_pair_from_dst1_220618::SmearPosition(int layer_id, int module_id, const TVector3& pos) {
  auto add_pos = kTmpPostionSmear[layer_id];
//  if (layer_id % 2 == 1) {
  if (layer_id == 1) {
    add_pos += TVector3(-2. * add_pos.X(), -2. * add_pos.Y(), 0.);
  }
  return pos + add_pos;
}

int tmp_fit_mock_pair_from_dst1_220618::CalcZ0Track(int charge, const TVector3& init_pos, const TVector3& init_mom, E16ANA_MagneticFieldMap& bfield_map,
                                                    TVector3* z0_pos, TVector3* z0_mom) {
  auto hep_init_pos = Hep3Vector(init_pos.X() * 0.1, init_pos.Y() * 0.1, init_pos.Z() * 0.1);
  auto hep_init_mom = Hep3Vector(init_mom.X(), init_mom.Y(), init_mom.Z());
  auto step_track = E16ANA_StepTrack(&bfield_map, hep_init_pos, hep_init_mom, charge, kStepTrackSizeCm, kStepTrackArraySize);
  Hep3Vector cross_pos;
  Hep3Vector cross_mom;
  auto flag = step_track.CrossZconstPlane(0., cross_pos, cross_mom);
  z0_pos->SetXYZ(cross_pos.x() * 10., cross_pos.y() * 10., cross_pos.z() * 10.);
  z0_mom->SetXYZ(cross_mom.x(),       cross_mom.y(),       cross_mom.z());
  return flag;
}

double tmp_fit_mock_pair_from_dst1_220618::CalcMass(int flag, const TVector3& mom0, const TVector3& mom1) {
  constexpr double kElectronMass = 511.99894641e-6;
  constexpr double kElectronMass2 = kElectronMass * kElectronMass;
  constexpr double kPionMass = 139.57039e-3;
  constexpr double kPionMass2 = kPionMass * kPionMass;
//  constexpr double kProtonMass    = 938.272081e-3;
//  constexpr double kProtonMass2   = kProtonMass * kProtonMass;
  double mass2[2];
  if (flag == kEEMass) {
    mass2[0] = kElectronMass2;
    mass2[1] = kElectronMass2;
  } else if (flag == kPiPiMass) {
    mass2[0] = kPionMass2;
    mass2[1] = kPionMass2;
  }
  double p0 = mom0.X() * mom0.X() + mom0.Y() * mom0.Y() + mom0.Z() * mom0.Z();
  double p1 = mom1.X() * mom1.X() + mom1.Y() * mom1.Y() + mom1.Z() * mom1.Z();
  double e0 = sqrt(p0 + mass2[0]);
  double e1 = sqrt(p1 + mass2[1]);
  double p0p1 = mom0.X() * mom1.X() + mom0.Y() * mom1.Y() + mom0.Z() * mom1.Z();
  return sqrt(mass2[0] + mass2[1] + 2. * (e0 * e1 - p0p1));
}

void tmp_fit_mock_pair_from_dst1_220618::Loop(int vtx_z_flag, int mass_flag, double vtx_z_coef, int max_events, const TString& out_name) {
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
//  auto geometry = new E16ANA_GeometryV2("/ccj/u/E16/database/geometry/v2/geometry_Run0b_210226_design.dat"); // for geometry effect estimation
  E16ANA_GeometryV2::SetGlobalPointer(geometry);
  auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
//  auto bfield_map = new E16ANA_MagneticFieldMap3D("/ccj/u/E16/database/fieldmap/Bmap_201207010_mod.binary"); // for magnetic field estimation
  bfield_map->Initialize_binary();
  E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
  E16ANA_MultiTrack fitter(bfield_map, geometry, 2);
  E16ANA_MultiTrack sfitter(bfield_map, geometry, 1);

  auto out_file = TFile(out_name, "recreate");
  auto out_tree = TTree("tree", "tree");
  // common
  int      plus_ssd_mid;
  int      plus_gtr100_mid;
  int      plus_gtr200_mid;
  int      plus_gtr300_mid;
  TVector3 plus_ssd_lpos;
  TVector3 plus_gtr100_lpos;
  TVector3 plus_gtr200_lpos;
  TVector3 plus_gtr300_lpos;
  int      minus_ssd_mid;
  int      minus_gtr100_mid;
  int      minus_gtr200_mid;
  int      minus_gtr300_mid;
  TVector3 minus_ssd_lpos;
  TVector3 minus_gtr100_lpos;
  TVector3 minus_gtr200_lpos;
  TVector3 minus_gtr300_lpos;
  // mock
  TVector3 mock_parent_vtx;
  TVector3 mock_parent_mom;
  TVector3 mock_vtx;
  TVector3 mock_plus_init_mom;
  TVector3 mock_plus_ssd_lpos;
  TVector3 mock_plus_gtr100_lpos;
  TVector3 mock_plus_gtr200_lpos;
  TVector3 mock_plus_gtr300_lpos;
  TVector3 mock_plus_ssd_lmom;
  TVector3 mock_plus_gtr100_lmom;
  TVector3 mock_plus_gtr200_lmom;
  TVector3 mock_plus_gtr300_lmom;
TVector3 mock_plus_ssd_gpos;
TVector3 mock_plus_ssd_gmom;
TVector3 mock_plus_z0_pos;
TVector3 mock_plus_z0_mom;
  TVector3 mock_minus_init_mom;
  TVector3 mock_minus_ssd_lpos;
  TVector3 mock_minus_gtr100_lpos;
  TVector3 mock_minus_gtr200_lpos;
  TVector3 mock_minus_gtr300_lpos;
  TVector3 mock_minus_ssd_lmom;
  TVector3 mock_minus_gtr100_lmom;
  TVector3 mock_minus_gtr200_lmom;
  TVector3 mock_minus_gtr300_lmom;
TVector3 mock_minus_ssd_gpos;
TVector3 mock_minus_ssd_gmom;
TVector3 mock_minus_z0_pos;
TVector3 mock_minus_z0_mom;
  double mock_mass;
  // rough fit
  TVector3 rough_fit_plus_init_pos;
  TVector3 rough_fit_plus_init_mom;
  TVector3 rough_fit_minus_init_pos;
  TVector3 rough_fit_minus_init_mom;
  // pre fit
  double   pre_fit_plus_chi2;
  int      pre_fit_plus_n_calls;
  TVector3 pre_fit_plus_init_mom;
  TVector3 pre_fit_plus_init_pos;
  TVector3 pre_fit_plus_ssd_lpos;
  TVector3 pre_fit_plus_gtr100_lpos;
  TVector3 pre_fit_plus_gtr200_lpos;
  TVector3 pre_fit_plus_gtr300_lpos;
  TVector3 pre_fit_plus_tgt0_pos;
  TVector3 pre_fit_plus_tgt0_mom;
  TVector3 pre_fit_plus_tgt1_pos;
  TVector3 pre_fit_plus_tgt1_mom;
  TVector3 pre_fit_plus_tgt2_pos;
  TVector3 pre_fit_plus_tgt2_mom;
//TVector3 pre_fit_plus_z0_pos;
//TVector3 pre_fit_plus_z0_mom;
  double   pre_fit_minus_chi2;
  int      pre_fit_minus_n_calls;
  TVector3 pre_fit_minus_init_mom;
  TVector3 pre_fit_minus_init_pos;
  TVector3 pre_fit_minus_ssd_lpos;
  TVector3 pre_fit_minus_gtr100_lpos;
  TVector3 pre_fit_minus_gtr200_lpos;
  TVector3 pre_fit_minus_gtr300_lpos;
  TVector3 pre_fit_minus_tgt0_pos;
  TVector3 pre_fit_minus_tgt0_mom;
  TVector3 pre_fit_minus_tgt1_pos;
  TVector3 pre_fit_minus_tgt1_mom;
  TVector3 pre_fit_minus_tgt2_pos;
  TVector3 pre_fit_minus_tgt2_mom;
//TVector3 pre_fit_minus_z0_pos;
//TVector3 pre_fit_minus_z0_mom;
  TVector3 pre_fit_vtx;
  TVector3 pre_fit_plus_vtx_mom;
  TVector3 pre_fit_minus_vtx_mom;
  double   pre_fit_distance;
  int      pre_fit_flag;
  double   pre_fit_mass;
  // single fit
  double   fit_plus_chi2;
  TVector3 fit_plus_init_mom;
  TVector3 fit_plus_init_pos;
  TVector3 fit_plus_ssd_lpos;
  TVector3 fit_plus_gtr100_lpos;
  TVector3 fit_plus_gtr200_lpos;
  TVector3 fit_plus_gtr300_lpos;
TVector3 fit_plus_z0_pos;
TVector3 fit_plus_z0_mom;
  double   fit_minus_chi2;
  TVector3 fit_minus_init_mom;
  TVector3 fit_minus_init_pos;
  TVector3 fit_minus_ssd_lpos;
  TVector3 fit_minus_gtr100_lpos;
  TVector3 fit_minus_gtr200_lpos;
  TVector3 fit_minus_gtr300_lpos;
TVector3 fit_minus_z0_pos;
TVector3 fit_minus_z0_mom;
  TVector3 fit_vtx;
  TVector3 fit_plus_vtx_mom;
  TVector3 fit_minus_vtx_mom;
  double   fit_distance;
  int      fit_flag;
  double   fit_mass;
  // pair fit
//  double   pair_fit_vtx_z_coef;
  double   pair_fit_chi2;
  TVector3 pair_fit_vtx;
  TVector3 pair_fit_plus_init_mom;
  TVector3 pair_fit_plus_ssd_lpos;
  TVector3 pair_fit_plus_gtr100_lpos;
  TVector3 pair_fit_plus_gtr200_lpos;
  TVector3 pair_fit_plus_gtr300_lpos;
  TVector3 pair_fit_minus_init_mom;
  TVector3 pair_fit_minus_ssd_lpos;
  TVector3 pair_fit_minus_gtr100_lpos;
  TVector3 pair_fit_minus_gtr200_lpos;
  TVector3 pair_fit_minus_gtr300_lpos;
  double   pair_fit_mass;
//  // w/o fit
//  int      wo_fit_flag;
//  double   wo_fit_distance;
//  TVector3 wo_fit_vtx;
//  TVector3 wo_fit_plus_init_mom;
//  TVector3 wo_fit_minus_init_mom;
//  double   wo_fit_mass;
  
  // common
  out_tree.Branch("run_id",                    &run_id,          "run_id/I");
  out_tree.Branch("event_id",                  &event_id,        "event_id/I");
  out_tree.Branch("plus_ssd_mid",              &plus_ssd_mid,    "plus_ssd_mid/I");
  out_tree.Branch("plus_gtr100_mid",           &plus_gtr100_mid, "plus_gtr100_mid/I");
  out_tree.Branch("plus_gtr200_mid",           &plus_gtr200_mid, "plus_gtr200_mid/I");
  out_tree.Branch("plus_gtr300_mid",           &plus_gtr300_mid, "plus_gtr300_mid/I");
  out_tree.Branch("plus_ssd_lpos",             &plus_ssd_lpos);
  out_tree.Branch("plus_gtr100_lpos",          &plus_gtr100_lpos);
  out_tree.Branch("plus_gtr200_lpos",          &plus_gtr200_lpos);
  out_tree.Branch("plus_gtr300_lpos",          &plus_gtr300_lpos);
  out_tree.Branch("minus_ssd_mid",             &minus_ssd_mid,    "minus_ssd_mid/I");
  out_tree.Branch("minus_gtr100_mid",          &minus_gtr100_mid, "minus_gtr100_mid/I");
  out_tree.Branch("minus_gtr200_mid",          &minus_gtr200_mid, "minus_gtr200_mid/I");
  out_tree.Branch("minus_gtr300_mid",          &minus_gtr300_mid, "minus_gtr300_mid/I");
  out_tree.Branch("minus_ssd_lpos",            &minus_ssd_lpos);
  out_tree.Branch("minus_gtr100_lpos",         &minus_gtr100_lpos);
  out_tree.Branch("minus_gtr200_lpos",         &minus_gtr200_lpos);
  out_tree.Branch("minus_gtr300_lpos",         &minus_gtr300_lpos);
  // mock
  out_tree.Branch("mock_parent_vtx",        &mock_parent_vtx);
  out_tree.Branch("mock_parent_mom",        &mock_parent_mom);
  out_tree.Branch("mock_vtx",               &mock_vtx);
  out_tree.Branch("mock_plus_init_mom",     &mock_plus_init_mom);
  out_tree.Branch("mock_plus_ssd_lpos",     &mock_plus_ssd_lpos);
  out_tree.Branch("mock_plus_gtr100_lpos",  &mock_plus_gtr100_lpos);
  out_tree.Branch("mock_plus_gtr200_lpos",  &mock_plus_gtr200_lpos);
  out_tree.Branch("mock_plus_gtr300_lpos",  &mock_plus_gtr300_lpos);
  out_tree.Branch("mock_plus_ssd_lmom",     &mock_plus_ssd_lmom);
  out_tree.Branch("mock_plus_gtr100_lmom",  &mock_plus_gtr100_lmom);
  out_tree.Branch("mock_plus_gtr200_lmom",  &mock_plus_gtr200_lmom);
  out_tree.Branch("mock_plus_gtr300_lmom",  &mock_plus_gtr300_lmom);
out_tree.Branch("mock_plus_ssd_gpos",  &mock_plus_ssd_gpos);
out_tree.Branch("mock_plus_ssd_gmom",  &mock_plus_ssd_gmom);
out_tree.Branch("mock_plus_z0_pos",           &mock_plus_z0_pos);
out_tree.Branch("mock_plus_z0_mom",           &mock_plus_z0_mom);
  out_tree.Branch("mock_minus_init_mom",    &mock_minus_init_mom);
  out_tree.Branch("mock_minus_ssd_lpos",    &mock_minus_ssd_lpos);
  out_tree.Branch("mock_minus_gtr100_lpos", &mock_minus_gtr100_lpos);
  out_tree.Branch("mock_minus_gtr200_lpos", &mock_minus_gtr200_lpos);
  out_tree.Branch("mock_minus_gtr300_lpos", &mock_minus_gtr300_lpos);
  out_tree.Branch("mock_minus_ssd_lmom",    &mock_minus_ssd_lmom);
  out_tree.Branch("mock_minus_gtr100_lmom", &mock_minus_gtr100_lmom);
  out_tree.Branch("mock_minus_gtr200_lmom", &mock_minus_gtr200_lmom);
  out_tree.Branch("mock_minus_gtr300_lmom", &mock_minus_gtr300_lmom);
out_tree.Branch("mock_minus_ssd_gpos",  &mock_minus_ssd_gpos);
out_tree.Branch("mock_minus_ssd_gmom",  &mock_minus_ssd_gmom);
out_tree.Branch("mock_minus_z0_pos",          &mock_minus_z0_pos);
out_tree.Branch("mock_minus_z0_mom",          &mock_minus_z0_mom);
  out_tree.Branch("mock_mass",              &mock_mass, "mock_mass/D");
  // rough fit
  out_tree.Branch("rough_fit_plus_init_pos",  &rough_fit_plus_init_pos);
  out_tree.Branch("rough_fit_plus_init_mom",  &rough_fit_plus_init_mom);
  out_tree.Branch("rough_fit_minus_init_pos", &rough_fit_minus_init_pos);
  out_tree.Branch("rough_fit_minus_init_mom", &rough_fit_minus_init_mom);
  // pre fit
  out_tree.Branch("pre_fit_plus_chi2",         &pre_fit_plus_chi2, "pre_fit_plus_chi2/D");
  out_tree.Branch("pre_fit_plus_n_calls",      &pre_fit_plus_n_calls, "pre_fit_plus_n_calls/I");
  out_tree.Branch("pre_fit_plus_init_mom",     &pre_fit_plus_init_mom);
  out_tree.Branch("pre_fit_plus_init_pos",     &pre_fit_plus_init_pos);
  out_tree.Branch("pre_fit_plus_ssd_lpos",     &pre_fit_plus_ssd_lpos);
  out_tree.Branch("pre_fit_plus_gtr100_lpos",  &pre_fit_plus_gtr100_lpos);
  out_tree.Branch("pre_fit_plus_gtr200_lpos",  &pre_fit_plus_gtr200_lpos);
  out_tree.Branch("pre_fit_plus_gtr300_lpos",  &pre_fit_plus_gtr300_lpos);
  out_tree.Branch("pre_fit_plus_tgt0_pos",     &pre_fit_plus_tgt0_pos);
  out_tree.Branch("pre_fit_plus_tgt0_mom",     &pre_fit_plus_tgt0_mom);
  out_tree.Branch("pre_fit_plus_tgt1_pos",     &pre_fit_plus_tgt1_pos);
  out_tree.Branch("pre_fit_plus_tgt1_mom",     &pre_fit_plus_tgt1_mom);
  out_tree.Branch("pre_fit_plus_tgt2_pos",     &pre_fit_plus_tgt2_pos);
  out_tree.Branch("pre_fit_plus_tgt2_mom",     &pre_fit_plus_tgt2_mom);
  out_tree.Branch("pre_fit_minus_chi2",        &pre_fit_minus_chi2, "pre_fit_minus_chi2/D");
  out_tree.Branch("pre_fit_minus_n_calls",     &pre_fit_minus_n_calls, "pre_fit_minus_n_calls/I");
  out_tree.Branch("pre_fit_minus_init_mom",    &pre_fit_minus_init_mom);
  out_tree.Branch("pre_fit_minus_init_pos",    &pre_fit_minus_init_pos);
  out_tree.Branch("pre_fit_minus_ssd_lpos",    &pre_fit_minus_ssd_lpos);
  out_tree.Branch("pre_fit_minus_gtr100_lpos", &pre_fit_minus_gtr100_lpos);
  out_tree.Branch("pre_fit_minus_gtr200_lpos", &pre_fit_minus_gtr200_lpos);
  out_tree.Branch("pre_fit_minus_gtr300_lpos", &pre_fit_minus_gtr300_lpos);
  out_tree.Branch("pre_fit_minus_tgt0_pos",    &pre_fit_minus_tgt0_pos);
  out_tree.Branch("pre_fit_minus_tgt0_mom",    &pre_fit_minus_tgt0_mom);
  out_tree.Branch("pre_fit_minus_tgt1_pos",    &pre_fit_minus_tgt1_pos);
  out_tree.Branch("pre_fit_minus_tgt1_mom",    &pre_fit_minus_tgt1_mom);
  out_tree.Branch("pre_fit_minus_tgt2_pos",    &pre_fit_minus_tgt2_pos);
  out_tree.Branch("pre_fit_minus_tgt2_mom",    &pre_fit_minus_tgt2_mom);
  out_tree.Branch("pre_fit_vtx",               &pre_fit_vtx);
  out_tree.Branch("pre_fit_plus_vtx_mom",      &pre_fit_plus_vtx_mom);
  out_tree.Branch("pre_fit_minus_vtx_mom",     &pre_fit_minus_vtx_mom);
  out_tree.Branch("pre_fit_distance",          &pre_fit_distance, "pre_fit_distance/D");
  out_tree.Branch("pre_fit_flag",              &pre_fit_flag,     "pre_fit_flag/I");
  out_tree.Branch("pre_fit_mass",              &pre_fit_mass,     "pre_fit_mass/D");
  // single fit
  out_tree.Branch("fit_plus_chi2",             &fit_plus_chi2, "fit_plus_chi2/D");
  out_tree.Branch("fit_plus_init_mom",         &fit_plus_init_mom);
  out_tree.Branch("fit_plus_init_pos",         &fit_plus_init_pos);
  out_tree.Branch("fit_plus_ssd_lpos",         &fit_plus_ssd_lpos);
  out_tree.Branch("fit_plus_gtr100_lpos",      &fit_plus_gtr100_lpos);
  out_tree.Branch("fit_plus_gtr200_lpos",      &fit_plus_gtr200_lpos);
  out_tree.Branch("fit_plus_gtr300_lpos",      &fit_plus_gtr300_lpos);
out_tree.Branch("fit_plus_z0_pos",      &fit_plus_z0_pos);
out_tree.Branch("fit_plus_z0_mom",      &fit_plus_z0_mom);
  out_tree.Branch("fit_minus_chi2",            &fit_minus_chi2, "fit_minus_chi2/D");
  out_tree.Branch("fit_minus_init_mom",        &fit_minus_init_mom);
  out_tree.Branch("fit_minus_init_pos",        &fit_minus_init_pos);
  out_tree.Branch("fit_minus_ssd_lpos",        &fit_minus_ssd_lpos);
  out_tree.Branch("fit_minus_gtr100_lpos",     &fit_minus_gtr100_lpos);
  out_tree.Branch("fit_minus_gtr200_lpos",     &fit_minus_gtr200_lpos);
  out_tree.Branch("fit_minus_gtr300_lpos",     &fit_minus_gtr300_lpos);
out_tree.Branch("fit_minus_z0_pos",      &fit_minus_z0_pos);
out_tree.Branch("fit_minus_z0_mom",      &fit_minus_z0_mom);
  out_tree.Branch("fit_vtx",                   &fit_vtx);
  out_tree.Branch("fit_plus_vtx_mom",          &fit_plus_vtx_mom);
  out_tree.Branch("fit_minus_vtx_mom",         &fit_minus_vtx_mom);
  out_tree.Branch("fit_distance",              &fit_distance, "fit_distance/D");
  out_tree.Branch("fit_flag",                  &fit_flag,     "fit_flag/I");
  out_tree.Branch("fit_mass",                  &fit_mass,     "fit_mass/D");
  // pair fit
  out_tree.Branch("pair_fit_vtx_z_coef",        &vtx_z_coef,          "pair_fit_vtx_z_coef/D");
  out_tree.Branch("pair_fit_chi2",              &pair_fit_chi2,       "pair_fit_chi2/D");
  out_tree.Branch("pair_fit_vtx",               &pair_fit_vtx);
  out_tree.Branch("pair_fit_plus_init_mom",     &pair_fit_plus_init_mom);
  out_tree.Branch("pair_fit_plus_ssd_lpos",     &pair_fit_plus_ssd_lpos);
  out_tree.Branch("pair_fit_plus_gtr100_lpos",  &pair_fit_plus_gtr100_lpos);
  out_tree.Branch("pair_fit_plus_gtr200_lpos",  &pair_fit_plus_gtr200_lpos);
  out_tree.Branch("pair_fit_plus_gtr300_lpos",  &pair_fit_plus_gtr300_lpos);
  out_tree.Branch("pair_fit_minus_init_mom",    &pair_fit_minus_init_mom);
  out_tree.Branch("pair_fit_minus_ssd_lpos",    &pair_fit_minus_ssd_lpos);
  out_tree.Branch("pair_fit_minus_gtr100_lpos", &pair_fit_minus_gtr100_lpos);
  out_tree.Branch("pair_fit_minus_gtr200_lpos", &pair_fit_minus_gtr200_lpos);
  out_tree.Branch("pair_fit_minus_gtr300_lpos", &pair_fit_minus_gtr300_lpos);
  out_tree.Branch("pair_fit_mass",              &pair_fit_mass, "pair_fit_mass/D");

  if (max_events == -1) {
    max_events = nentries;
  }
  for (Long64_t jentry = 0; jentry < max_events; ++jentry) {
    if (jentry % 10 == 0) {
      cout << jentry << " / " << nentries << endl;
    }
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
//    if (Cut(ientry) < 0) continue;
    if (!sim_track_detected->at(0) || !sim_track_detected->at(1)) {
      continue;
    }
    array<array<int, 4>, 2> mids;
    // hit
    array<bool, 2> is_sim_filled;
    is_sim_filled.fill(false);
    for (int i = 0; i < n_cands; ++i) {
      if (!is_sim_track->at(i)) {
        continue;
      }
      if (rk_charge->at(i) == 1) {
        is_sim_filled[0] = true;
        plus_ssd_mid     = rk_fit_ssd_mid->at(i);
        plus_gtr100_mid  = rk_fit_gtr100_mid->at(i);
        plus_gtr200_mid  = rk_fit_gtr200_mid->at(i);
        plus_gtr300_mid  = rk_fit_gtr300_mid->at(i);
        mids[0][0] = ModuleID2020To2013(plus_ssd_mid);
        mids[0][1] = ModuleID2020To2013(plus_gtr100_mid);
        mids[0][2] = ModuleID2020To2013(plus_gtr200_mid);
        mids[0][3] = ModuleID2020To2013(plus_gtr300_mid);
        plus_ssd_lpos    = geometry->SSD(mids[0][0])->GetLPos(TVector3(rk_hit_ssd_gx->at(i),         rk_hit_ssd_gy->at(i),     rk_hit_ssd_gz->at(i)));
        plus_gtr100_lpos = geometry->GTR(mids[0][1], 0)->GetLPos(TVector3(rk_hit_gtr100_gtx2->at(i), rk_hit_gtr100_gty2->at(i), rk_hit_gtr100_gtz2->at(i)));
        plus_gtr200_lpos = geometry->GTR(mids[0][2], 1)->GetLPos(TVector3(rk_hit_gtr200_gtx2->at(i), rk_hit_gtr200_gty2->at(i), rk_hit_gtr200_gtz2->at(i)));
        plus_gtr300_lpos = geometry->GTR(mids[0][3], 2)->GetLPos(TVector3(rk_hit_gtr300_gtx2->at(i), rk_hit_gtr300_gty2->at(i), rk_hit_gtr300_gtz2->at(i)));
        pre_fit_plus_chi2        = chi_square->at(i);
        pre_fit_plus_n_calls     = n_calls->at(i);
        pre_fit_plus_init_mom    = TVector3(rk_fit_init_mom_gx->at(i), rk_fit_init_mom_gy->at(i), rk_fit_init_mom_gz->at(i));
        rough_fit_plus_init_pos  = TVector3(rk_hit_init_pos_gx->at(i), rk_hit_init_pos_gy->at(i), rk_hit_init_pos_gz->at(i));
        rough_fit_plus_init_mom  = TVector3(rk_hit_init_mom_gx->at(i), rk_hit_init_mom_gy->at(i), rk_hit_init_mom_gz->at(i));
        pre_fit_plus_init_pos    = TVector3(rk_fit_init_pos_gx->at(i), rk_fit_init_pos_gy->at(i), rk_fit_init_pos_gz->at(i));
        pre_fit_plus_ssd_lpos    = TVector3(rk_fit_ssd_x->at(i),    rk_fit_ssd_y->at(i),    0.);
        pre_fit_plus_gtr100_lpos = TVector3(rk_fit_gtr100_x->at(i), rk_fit_gtr100_y->at(i), 0.);
        pre_fit_plus_gtr200_lpos = TVector3(rk_fit_gtr200_x->at(i), rk_fit_gtr200_y->at(i), 0.);
        pre_fit_plus_gtr300_lpos = TVector3(rk_fit_gtr300_x->at(i), rk_fit_gtr300_y->at(i), 0.);
        pre_fit_plus_tgt0_pos    = TVector3(rk_proj_tgt0_gx->at(i),     rk_proj_tgt0_gy->at(i),     rk_proj_tgt0_gz->at(i));
        pre_fit_plus_tgt0_mom    = TVector3(rk_proj_tgt0_mom_gx->at(i), rk_proj_tgt0_mom_gy->at(i), rk_proj_tgt0_mom_gz->at(i));
        pre_fit_plus_tgt1_pos    = TVector3(rk_proj_tgt1_gx->at(i),     rk_proj_tgt1_gy->at(i),     rk_proj_tgt1_gz->at(i));
        pre_fit_plus_tgt1_mom    = TVector3(rk_proj_tgt1_mom_gx->at(i), rk_proj_tgt1_mom_gy->at(i), rk_proj_tgt1_mom_gz->at(i));
        pre_fit_plus_tgt2_pos    = TVector3(rk_proj_tgt2_gx->at(i),     rk_proj_tgt2_gy->at(i),     rk_proj_tgt2_gz->at(i));
        pre_fit_plus_tgt2_mom    = TVector3(rk_proj_tgt2_mom_gx->at(i), rk_proj_tgt2_mom_gy->at(i), rk_proj_tgt2_mom_gz->at(i));
      } else {
        is_sim_filled[1] = true;
        minus_ssd_mid     = rk_fit_ssd_mid->at(i);
        minus_gtr100_mid  = rk_fit_gtr100_mid->at(i);
        minus_gtr200_mid  = rk_fit_gtr200_mid->at(i);
        minus_gtr300_mid  = rk_fit_gtr300_mid->at(i);
        mids[1][0] = ModuleID2020To2013(minus_ssd_mid);
        mids[1][1] = ModuleID2020To2013(minus_gtr100_mid);
        mids[1][2] = ModuleID2020To2013(minus_gtr200_mid);
        mids[1][3] = ModuleID2020To2013(minus_gtr300_mid);
        minus_ssd_lpos    = geometry->SSD(mids[1][0])->GetLPos(TVector3(rk_hit_ssd_gx->at(i),         rk_hit_ssd_gy->at(i),     rk_hit_ssd_gz->at(i)));
        minus_gtr100_lpos = geometry->GTR(mids[1][1], 0)->GetLPos(TVector3(rk_hit_gtr100_gtx2->at(i), rk_hit_gtr100_gty2->at(i), rk_hit_gtr100_gtz2->at(i)));
        minus_gtr200_lpos = geometry->GTR(mids[1][2], 1)->GetLPos(TVector3(rk_hit_gtr200_gtx2->at(i), rk_hit_gtr200_gty2->at(i), rk_hit_gtr200_gtz2->at(i)));
        minus_gtr300_lpos = geometry->GTR(mids[1][3], 2)->GetLPos(TVector3(rk_hit_gtr300_gtx2->at(i), rk_hit_gtr300_gty2->at(i), rk_hit_gtr300_gtz2->at(i)));
        pre_fit_minus_chi2        = chi_square->at(i);
        pre_fit_minus_n_calls     = n_calls->at(i);
        pre_fit_minus_init_mom    = TVector3(rk_fit_init_mom_gx->at(i), rk_fit_init_mom_gy->at(i), rk_fit_init_mom_gz->at(i));
        rough_fit_minus_init_pos  = TVector3(rk_hit_init_pos_gx->at(i), rk_hit_init_pos_gy->at(i), rk_hit_init_pos_gz->at(i));
        rough_fit_minus_init_mom  = TVector3(rk_hit_init_mom_gx->at(i), rk_hit_init_mom_gy->at(i), rk_hit_init_mom_gz->at(i));
        pre_fit_minus_init_pos    = TVector3(rk_fit_init_pos_gx->at(i), rk_fit_init_pos_gy->at(i), rk_fit_init_pos_gz->at(i));
        pre_fit_minus_ssd_lpos    = TVector3(rk_fit_ssd_x->at(i),    rk_fit_ssd_y->at(i),    0.);
        pre_fit_minus_gtr100_lpos = TVector3(rk_fit_gtr100_x->at(i), rk_fit_gtr100_y->at(i), 0.);
        pre_fit_minus_gtr200_lpos = TVector3(rk_fit_gtr200_x->at(i), rk_fit_gtr200_y->at(i), 0.);
        pre_fit_minus_gtr300_lpos = TVector3(rk_fit_gtr300_x->at(i), rk_fit_gtr300_y->at(i), 0.);
        pre_fit_minus_tgt0_pos    = TVector3(rk_proj_tgt0_gx->at(i),     rk_proj_tgt0_gy->at(i),     rk_proj_tgt0_gz->at(i));
        pre_fit_minus_tgt0_mom    = TVector3(rk_proj_tgt0_mom_gx->at(i), rk_proj_tgt0_mom_gy->at(i), rk_proj_tgt0_mom_gz->at(i));
        pre_fit_minus_tgt1_pos    = TVector3(rk_proj_tgt1_gx->at(i),     rk_proj_tgt1_gy->at(i),     rk_proj_tgt1_gz->at(i));
        pre_fit_minus_tgt1_mom    = TVector3(rk_proj_tgt1_mom_gx->at(i), rk_proj_tgt1_mom_gy->at(i), rk_proj_tgt1_mom_gz->at(i));
        pre_fit_minus_tgt2_pos    = TVector3(rk_proj_tgt2_gx->at(i),     rk_proj_tgt2_gy->at(i),     rk_proj_tgt2_gz->at(i));
        pre_fit_minus_tgt2_mom    = TVector3(rk_proj_tgt2_mom_gx->at(i), rk_proj_tgt2_mom_gy->at(i), rk_proj_tgt2_mom_gz->at(i));
      }
      auto pre_fit_hep_plus_init_pos  = Hep3Vector(pre_fit_plus_init_pos.X()  * 0.1, pre_fit_plus_init_pos.Y()  * 0.1, pre_fit_plus_init_pos.Z()  * 0.1);
      auto pre_fit_hep_minus_init_pos = Hep3Vector(pre_fit_minus_init_pos.X() * 0.1, pre_fit_minus_init_pos.Y() * 0.1, pre_fit_minus_init_pos.Z() * 0.1);
      auto pre_fit_hep_plus_init_mom  = Hep3Vector(pre_fit_plus_init_mom.X(),        pre_fit_plus_init_mom.Y(),        pre_fit_plus_init_mom.Z());
      auto pre_fit_hep_minus_init_mom = Hep3Vector(pre_fit_minus_init_mom.X(),       pre_fit_minus_init_mom.Y(),       pre_fit_minus_init_mom.Z());
      auto pre_fit_plus_step_track    = E16ANA_StepTrack(bfield_map, pre_fit_hep_plus_init_pos,  pre_fit_hep_plus_init_mom,
                                                         1.,  kStepTrackSizeCm, kStepTrackArraySize);
      auto pre_fit_minus_step_track   = E16ANA_StepTrack(bfield_map, pre_fit_hep_minus_init_pos, pre_fit_hep_minus_init_mom,
                                                         -1., kStepTrackSizeCm, kStepTrackArraySize);
      auto pre_fit_distance_cm        = double();
      auto pre_fit_hep_vtx            = Hep3Vector();
      auto pre_fit_hep_plus_vtx_mom   = Hep3Vector();
      auto pre_fit_hep_minus_vtx_mom  = Hep3Vector();
      pre_fit_flag = pre_fit_plus_step_track.Cross(pre_fit_minus_step_track,
                                                   &pre_fit_distance_cm, &pre_fit_hep_vtx, &pre_fit_hep_plus_vtx_mom, &pre_fit_hep_minus_vtx_mom);
      pre_fit_distance = pre_fit_distance_cm * 10.;
      pre_fit_vtx.SetXYZ(pre_fit_hep_vtx.x() * 10., pre_fit_hep_vtx.y() * 10., pre_fit_hep_vtx.z() * 10.);
      pre_fit_plus_vtx_mom.SetXYZ(pre_fit_hep_plus_vtx_mom.x(),   pre_fit_hep_plus_vtx_mom.y(),  pre_fit_hep_plus_vtx_mom.z());
      pre_fit_minus_vtx_mom.SetXYZ(pre_fit_hep_minus_vtx_mom.x(), pre_fit_hep_minus_vtx_mom.y(), pre_fit_hep_minus_vtx_mom.z());
      if (is_sim_filled[0] && is_sim_filled[1]) {
        break;
      }
    }
    pre_fit_mass = CalcMass(mass_flag, pre_fit_plus_vtx_mom,   pre_fit_minus_vtx_mom);
    // mock
    auto mock_id = mock_n_tracks - 2;
    mock_parent_vtx        = TVector3(mock_init_pos_x->at(mock_id - 1),    mock_init_pos_y->at(mock_id - 1),    mock_init_pos_z->at(mock_id - 1));
    mock_parent_mom        = TVector3(mock_init_mom_x->at(mock_id - 1),    mock_init_mom_y->at(mock_id - 1),    mock_init_mom_z->at(mock_id - 1));
    mock_vtx               = TVector3(mock_init_pos_x->at(mock_id),        mock_init_pos_y->at(mock_id),        mock_init_pos_z->at(mock_id));
    mock_plus_init_mom     = TVector3(mock_init_mom_x->at(mock_id),        mock_init_mom_y->at(mock_id),        mock_init_mom_z->at(mock_id));
    mock_plus_ssd_lpos     = TVector3(mock_ssd_lpos_x->at(mock_id),        mock_ssd_lpos_y->at(mock_id),        mock_ssd_lpos_z->at(mock_id));
    mock_plus_gtr100_lpos  = TVector3(mock_gtr100_lpos_x->at(mock_id),     mock_gtr100_lpos_y->at(mock_id),     mock_gtr100_lpos_z->at(mock_id));
    mock_plus_gtr200_lpos  = TVector3(mock_gtr200_lpos_x->at(mock_id),     mock_gtr200_lpos_y->at(mock_id),     mock_gtr200_lpos_z->at(mock_id));
    mock_plus_gtr300_lpos  = TVector3(mock_gtr300_lpos_x->at(mock_id),     mock_gtr300_lpos_y->at(mock_id),     mock_gtr300_lpos_z->at(mock_id));
    mock_plus_ssd_lmom     = TVector3(mock_ssd_lmom_x->at(mock_id),        mock_ssd_lmom_y->at(mock_id),        mock_ssd_lmom_z->at(mock_id));
    mock_plus_gtr100_lmom  = TVector3(mock_gtr100_lmom_x->at(mock_id),     mock_gtr100_lmom_y->at(mock_id),     mock_gtr100_lmom_z->at(mock_id));
    mock_plus_gtr200_lmom  = TVector3(mock_gtr200_lmom_x->at(mock_id),     mock_gtr200_lmom_y->at(mock_id),     mock_gtr200_lmom_z->at(mock_id));
    mock_plus_gtr300_lmom  = TVector3(mock_gtr300_lmom_x->at(mock_id),     mock_gtr300_lmom_y->at(mock_id),     mock_gtr300_lmom_z->at(mock_id));
mock_plus_ssd_gpos     = TVector3(mock_ssd_gpos_x->at(mock_id),        mock_ssd_gpos_y->at(mock_id),        mock_ssd_gpos_z->at(mock_id));
mock_plus_ssd_gmom     = TVector3(mock_ssd_gmom_x->at(mock_id),        mock_ssd_gmom_y->at(mock_id),        mock_ssd_gmom_z->at(mock_id));
    mock_minus_init_mom    = TVector3(mock_init_mom_x->at(mock_id + 1),    mock_init_mom_y->at(mock_id + 1),    mock_init_mom_z->at(mock_id + 1));
    mock_minus_ssd_lpos    = TVector3(mock_ssd_lpos_x->at(mock_id + 1),    mock_ssd_lpos_y->at(mock_id + 1),    mock_ssd_lpos_z->at(mock_id + 1));
    mock_minus_gtr100_lpos = TVector3(mock_gtr100_lpos_x->at(mock_id + 1), mock_gtr100_lpos_y->at(mock_id + 1), mock_gtr100_lpos_z->at(mock_id + 1));
    mock_minus_gtr200_lpos = TVector3(mock_gtr200_lpos_x->at(mock_id + 1), mock_gtr200_lpos_y->at(mock_id + 1), mock_gtr200_lpos_z->at(mock_id + 1));
    mock_minus_gtr300_lpos = TVector3(mock_gtr300_lpos_x->at(mock_id + 1), mock_gtr300_lpos_y->at(mock_id + 1), mock_gtr300_lpos_z->at(mock_id + 1));
    mock_minus_ssd_lmom    = TVector3(mock_ssd_lmom_x->at(mock_id + 1),    mock_ssd_lmom_y->at(mock_id + 1),    mock_ssd_lmom_z->at(mock_id + 1));
    mock_minus_gtr100_lmom = TVector3(mock_gtr100_lmom_x->at(mock_id + 1), mock_gtr100_lmom_y->at(mock_id + 1), mock_gtr100_lmom_z->at(mock_id + 1));
    mock_minus_gtr200_lmom = TVector3(mock_gtr200_lmom_x->at(mock_id + 1), mock_gtr200_lmom_y->at(mock_id + 1), mock_gtr200_lmom_z->at(mock_id + 1));
    mock_minus_gtr300_lmom = TVector3(mock_gtr300_lmom_x->at(mock_id + 1), mock_gtr300_lmom_y->at(mock_id + 1), mock_gtr300_lmom_z->at(mock_id + 1));
mock_minus_ssd_gpos     = TVector3(mock_ssd_gpos_x->at(mock_id + 1),        mock_ssd_gpos_y->at(mock_id + 1),        mock_ssd_gpos_z->at(mock_id + 1));
mock_minus_ssd_gmom     = TVector3(mock_ssd_gmom_x->at(mock_id + 1),        mock_ssd_gmom_y->at(mock_id + 1),        mock_ssd_gmom_z->at(mock_id + 1));
    CalcZ0Track(1,  mock_vtx, mock_plus_init_mom,  *bfield_map, &mock_plus_z0_pos,  &mock_plus_z0_mom);
    CalcZ0Track(-1, mock_vtx, mock_minus_init_mom, *bfield_map, &mock_minus_z0_pos, &mock_minus_z0_mom);
    mock_mass = CalcMass(mass_flag, mock_plus_init_mom,     mock_minus_init_mom);
    // single fit
    for (int t = 0; t < 2; ++t) {
      sfitter.Clear();
      if (t == 0) {
        sfitter.SetCharge(0, 1.);
//        sfitter.SetInitialVertex(rough_fit_plus_init_pos, kVertexSigma);
//        sfitter.SetInitialMomentum(0, rough_fit_plus_init_mom);
        sfitter.SetInitialVertex(mock_plus_ssd_gpos, kVertexSigma);
        sfitter.SetInitialMomentum(0, mock_plus_ssd_gmom);
//        sfitter.SetInitialVertex(mock_vtx, kVertexSigma);
//        sfitter.SetInitialMomentum(0, mock_plus_init_mom);
      } else {
        sfitter.SetCharge(0, -1.);
//        sfitter.SetInitialVertex(rough_fit_minus_init_pos, kVertexSigma);
//        sfitter.SetInitialMomentum(0, rough_fit_minus_init_mom);
        sfitter.SetInitialVertex(mock_minus_ssd_gpos, kVertexSigma);
        sfitter.SetInitialMomentum(0, mock_minus_ssd_gmom);
//        sfitter.SetInitialVertex(mock_vtx, kVertexSigma);
//        sfitter.SetInitialMomentum(0, mock_minus_init_mom);
      }
      if (t == 0) {
        sfitter.AddHit(0, 0, geometry->SSD(mids[0][0]),    plus_ssd_lpos,    kSSDSigma);
        sfitter.AddHit(0, 1, geometry->GTR(mids[0][1], 0), plus_gtr100_lpos, kGTR100Sigma);
        sfitter.AddHit(0, 2, geometry->GTR(mids[0][2], 1), plus_gtr200_lpos, kGTR200Sigma);
        sfitter.AddHit(0, 3, geometry->GTR(mids[0][3], 2), plus_gtr300_lpos, kGTR300Sigma);
      } else {
        sfitter.AddHit(0, 0, geometry->SSD(mids[1][0]),    minus_ssd_lpos,    kSSDSigma);
        sfitter.AddHit(0, 1, geometry->GTR(mids[1][1], 0), minus_gtr100_lpos, kGTR100Sigma);
        sfitter.AddHit(0, 2, geometry->GTR(mids[1][2], 1), minus_gtr200_lpos, kGTR200Sigma);
        sfitter.AddHit(0, 3, geometry->GTR(mids[1][3], 2), minus_gtr300_lpos, kGTR300Sigma);
      }
//      if (t == 0) {
//        sfitter.AddHit(0, 0, geometry->SSD(mids[0][0]),    SmearPosition(0, mids[0][0], plus_ssd_lpos),    kSSDSigma);
//        sfitter.AddHit(0, 1, geometry->GTR(mids[0][1], 0), SmearPosition(1, mids[0][1], plus_gtr100_lpos), kGTR100Sigma);
//        sfitter.AddHit(0, 2, geometry->GTR(mids[0][2], 1), SmearPosition(2, mids[0][2], plus_gtr200_lpos), kGTR200Sigma);
//        sfitter.AddHit(0, 3, geometry->GTR(mids[0][3], 2), SmearPosition(3, mids[0][3], plus_gtr300_lpos), kGTR300Sigma);
//      } else {
//        sfitter.AddHit(0, 0, geometry->SSD(mids[1][0]),    SmearPosition(0, mids[1][0], minus_ssd_lpos),    kSSDSigma);
//        sfitter.AddHit(0, 1, geometry->GTR(mids[1][1], 0), SmearPosition(1, mids[1][1], minus_gtr100_lpos), kGTR100Sigma);
//        sfitter.AddHit(0, 2, geometry->GTR(mids[1][2], 1), SmearPosition(2, mids[1][2], minus_gtr200_lpos), kGTR200Sigma);
//        sfitter.AddHit(0, 3, geometry->GTR(mids[1][3], 2), SmearPosition(3, mids[1][3], minus_gtr300_lpos), kGTR300Sigma);
//      }
      sfitter.SetRungeKuttaStepSize(kStepSize);
      sfitter.SetMaxSteps(kMaxSteps);
      auto tmp_chi2     = sfitter.Fit(kFixVtxXY, kFixPy, kFixVtxZ[vtx_z_flag], kStrategy, kMaxFuncCalls,
                                      kVtxXRange[0], kVtxXRange[1], kVtxYRange[0], kVtxYRange[1], kVtxZRange[0], kVtxZRange[1]);
      auto tmp_mom      = sfitter.GetFitMomentum(0);
      auto tmp_init_pos = sfitter.GetFitVertex();
      array<TVector3, 4> tmp_lposs;
      for (int l = 0; l < 4; ++l) {
        vector<int> tmp_mid;
        vector<TVector3> tmp_lpos;
        sfitter.GetFitLPos(0, l, tmp_mid, tmp_lpos);
        tmp_lposs[l] = tmp_lpos[0];
      }
      if (t == 0) {
        fit_plus_chi2        = tmp_chi2;
        fit_plus_init_mom    = tmp_mom;
        fit_plus_init_pos    = tmp_init_pos;
        fit_plus_ssd_lpos    = tmp_lposs[0];
        fit_plus_gtr100_lpos = tmp_lposs[1];
        fit_plus_gtr200_lpos = tmp_lposs[2];
        fit_plus_gtr300_lpos = tmp_lposs[3];
      } else {
        fit_minus_chi2        = tmp_chi2;
        fit_minus_init_mom    = tmp_mom;
        fit_minus_init_pos    = tmp_init_pos;
        fit_minus_ssd_lpos    = tmp_lposs[0];
        fit_minus_gtr100_lpos = tmp_lposs[1];
        fit_minus_gtr200_lpos = tmp_lposs[2];
        fit_minus_gtr300_lpos = tmp_lposs[3];
      }
    }
    auto fit_hep_plus_init_pos  = Hep3Vector(fit_plus_init_pos.X()  * 0.1, fit_plus_init_pos.Y()  * 0.1, fit_plus_init_pos.Z()  * 0.1);
    auto fit_hep_minus_init_pos = Hep3Vector(fit_minus_init_pos.X() * 0.1, fit_minus_init_pos.Y() * 0.1, fit_minus_init_pos.Z() * 0.1);
    auto fit_hep_plus_init_mom  = Hep3Vector(fit_plus_init_mom.X(),        fit_plus_init_mom.Y(),        fit_plus_init_mom.Z());
    auto fit_hep_minus_init_mom = Hep3Vector(fit_minus_init_mom.X(),       fit_minus_init_mom.Y(),       fit_minus_init_mom.Z());
    auto fit_plus_step_track    = E16ANA_StepTrack(bfield_map, fit_hep_plus_init_pos,  fit_hep_plus_init_mom,   1., kStepTrackSizeCm, kStepTrackArraySize);
    auto fit_minus_step_track   = E16ANA_StepTrack(bfield_map, fit_hep_minus_init_pos, fit_hep_minus_init_mom, -1., kStepTrackSizeCm, kStepTrackArraySize);
    auto fit_distance_cm        = double();
    auto fit_hep_vtx            = Hep3Vector();
    auto fit_hep_plus_vtx_mom   = Hep3Vector();
    auto fit_hep_minus_vtx_mom  = Hep3Vector();
    fit_flag = fit_plus_step_track.Cross(fit_minus_step_track, &fit_distance_cm, &fit_hep_vtx, &fit_hep_plus_vtx_mom, &fit_hep_minus_vtx_mom);
    fit_distance = fit_distance_cm * 10.;
    fit_vtx.SetXYZ(fit_hep_vtx.x() * 10., fit_hep_vtx.y() * 10., fit_hep_vtx.z() * 10.);
    fit_plus_vtx_mom.SetXYZ(fit_hep_plus_vtx_mom.x(),   fit_hep_plus_vtx_mom.y(),  fit_hep_plus_vtx_mom.z());
    fit_minus_vtx_mom.SetXYZ(fit_hep_minus_vtx_mom.x(), fit_hep_minus_vtx_mom.y(), fit_hep_minus_vtx_mom.z());
    CalcZ0Track(1,  fit_plus_init_pos,  fit_plus_init_mom,   *bfield_map, &fit_plus_z0_pos,   &fit_plus_z0_mom);
    CalcZ0Track(-1, fit_minus_init_pos, fit_minus_init_mom,  *bfield_map, &fit_minus_z0_pos,  &fit_minus_z0_mom);
    fit_mass = CalcMass(mass_flag, fit_plus_vtx_mom,       fit_minus_vtx_mom);
#ifndef WO_PAIR_FIT
    // pair fit
    fitter.Clear();
    if (vtx_z_coef == 0.) {
      fitter.SetInitialVertex(kInitVertex[vtx_z_flag], kVertexSigma);
    } else {
      fitter.SetInitialVertex(TVector3(0., 0., mock_vtx.Z() * vtx_z_coef), kVertexSigma);
    }
    fitter.SetCharge(0, 1.);
#ifndef FROM_MOCK
    fitter.SetInitialMomentum(0, pre_fit_plus_init_mom);
//    fitter.SetInitialMomentum(0, mock_plus_init_mom);
    fitter.AddHit(0, 0, geometry->SSD(mids[0][0]),    SmearPosition(0, mids[0][0], plus_ssd_lpos),    kSSDSigma);
    fitter.AddHit(0, 1, geometry->GTR(mids[0][1], 0), SmearPosition(1, mids[0][1], plus_gtr100_lpos), kGTR100Sigma);
    fitter.AddHit(0, 2, geometry->GTR(mids[0][2], 1), SmearPosition(2, mids[0][2], plus_gtr200_lpos), kGTR200Sigma);
    fitter.AddHit(0, 3, geometry->GTR(mids[0][3], 2), SmearPosition(3, mids[0][3], plus_gtr300_lpos), kGTR300Sigma);
//#else
//    fitter.SetInitialMomentum(0, mock_plus_init_mom);
////    fitter.AddHit(0, 0, geometry->SSD(mids[0][0]),    mock_plus_ssd_lpos,    kSSDSigma);
////    fitter.AddHit(0, 1, geometry->GTR(mids[0][1], 0), mock_plus_gtr100_lpos, kGTR100Sigma);
////    fitter.AddHit(0, 2, geometry->GTR(mids[0][2], 1), mock_plus_gtr200_lpos, kGTR200Sigma);
////    fitter.AddHit(0, 3, geometry->GTR(mids[0][3], 2), mock_plus_gtr300_lpos, kGTR300Sigma);
//    fitter.AddHit(0, 0, geometry->SSD(mids[0][0]),    mock_plus_ssd_lpos,    kSSDSigma);
//    fitter.AddHit(0, 1, geometry->GTR(mids[0][1], 0), mock_plus_gtr100_lpos, kGTR100Sigma);
//    fitter.AddHit(0, 2, geometry->GTR(mids[0][2], 1), mock_plus_gtr200_lpos, kGTR200Sigma);
//    fitter.AddHit(0, 3, geometry->GTR(mids[0][3], 2), mock_plus_gtr300_lpos, kGTR300Sigma);
#endif
    fitter.SetCharge(1, -1.);
#ifndef FROM_MOCK
    fitter.SetInitialMomentum(1, pre_fit_minus_init_mom);
//    fitter.SetInitialMomentum(1, mock_minus_init_mom);
//    fitter.AddHit(1, 0, geometry->SSD(mids[1][0]),    minus_ssd_lpos,    kSSDSigma);
//    fitter.AddHit(1, 1, geometry->GTR(mids[1][1], 0), minus_gtr100_lpos, kGTR100Sigma);
//    fitter.AddHit(1, 2, geometry->GTR(mids[1][2], 1), minus_gtr200_lpos, kGTR200Sigma);
//    fitter.AddHit(1, 3, geometry->GTR(mids[1][3], 2), minus_gtr300_lpos, kGTR300Sigma);
    fitter.AddHit(1, 0, geometry->SSD(mids[1][0]),    SmearPosition(0, mids[1][0], minus_ssd_lpos),    kSSDSigma);
    fitter.AddHit(1, 1, geometry->GTR(mids[1][1], 0), SmearPosition(1, mids[1][1], minus_gtr100_lpos), kGTR100Sigma);
    fitter.AddHit(1, 2, geometry->GTR(mids[1][2], 1), SmearPosition(2, mids[1][2], minus_gtr200_lpos), kGTR200Sigma);
    fitter.AddHit(1, 3, geometry->GTR(mids[1][3], 2), SmearPosition(3, mids[1][3], minus_gtr300_lpos), kGTR300Sigma);
//#else
//    fitter.SetInitialMomentum(1, mock_minus_init_mom);
//    fitter.AddHit(1, 0, geometry->SSD(mids[1][0]),    mock_minus_ssd_lpos,    kSSDSigma);
//    fitter.AddHit(1, 1, geometry->GTR(mids[1][1], 0), mock_minus_gtr100_lpos, kGTR100Sigma);
//    fitter.AddHit(1, 2, geometry->GTR(mids[1][2], 1), mock_minus_gtr200_lpos, kGTR200Sigma);
//    fitter.AddHit(1, 3, geometry->GTR(mids[1][3], 2), mock_minus_gtr300_lpos, kGTR300Sigma);
#endif
    fitter.SetRungeKuttaStepSize(kStepSize);
    fitter.SetMaxSteps(kMaxSteps);
    if (vtx_z_coef == 0.) {
      pair_fit_chi2           = fitter.Fit(kFixVtxXY, kFixPy, kFixVtxZ[vtx_z_flag], kStrategy, kMaxFuncCalls,
                                           kVtxXRange[0], kVtxXRange[1], kVtxYRange[0], kVtxYRange[1], kVtxZRange[0], kVtxZRange[1]);
    } else {
      pair_fit_chi2           = fitter.Fit(kFixVtxXY, kFixPy, true, kStrategy, kMaxFuncCalls,
                                           kVtxXRange[0], kVtxXRange[1], kVtxYRange[0], kVtxYRange[1], kVtxZRange[0], kVtxZRange[1]);
    }
    pair_fit_vtx            = fitter.GetFitVertex();
    pair_fit_plus_init_mom  = fitter.GetFitMomentum(0);
    pair_fit_minus_init_mom = fitter.GetFitMomentum(1);
    for (int t = 0; t < 2; ++t) {
      for (int l = 0; l < 4; ++l) {
        vector<int>      mids;
        vector<TVector3> lposs;
        fitter.GetFitLPos(t, l, mids, lposs);
        if (t == 0) {
          if (l == 0) {
            pair_fit_plus_ssd_lpos = lposs[0];
          } else if (l == 1) {
            pair_fit_plus_gtr100_lpos = lposs[0];
          } else if (l == 2) {
            pair_fit_plus_gtr200_lpos = lposs[0];
          } else {
            pair_fit_plus_gtr300_lpos = lposs[0];
          }
        } else {
          if (l == 0) {
            pair_fit_minus_ssd_lpos = lposs[0];
          } else if (l == 1) {
            pair_fit_minus_gtr100_lpos = lposs[0];
          } else if (l == 2) {
            pair_fit_minus_gtr200_lpos = lposs[0];
          } else {
            pair_fit_minus_gtr300_lpos = lposs[0];
          }
        }
      }
    }
    pair_fit_mass = CalcMass(mass_flag, pair_fit_plus_init_mom, pair_fit_minus_init_mom);
#endif // WO_PAIR_FIT
    out_tree.Fill();
  }
  out_file.Write();
}
