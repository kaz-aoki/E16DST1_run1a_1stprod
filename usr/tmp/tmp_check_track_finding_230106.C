#define tmp_check_track_finding_230106_cxx
#include "tmp_check_track_finding_230106.h"

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TRandom.h>

#include "E16ANA_GeometryV2.hh"

using namespace std;

int tmp_check_track_finding_230106::ModuleID2020To2013(int module_id) {
const std::array<std::array<int, 11>, 3> kModuleId2020To2013 = {{{30, 27, 24, 21, 18, 15, 12, 9,  6, 3, 0},
                                                                 {31, 28, 25, 22, 19, 16, 13, 10, 7, 4, 1},
                                                                 {32, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2}}};
  return kModuleId2020To2013[module_id / 100][module_id % 100];
}

double tmp_check_track_finding_230106::SmearPosition(double pos, int layer_id, int axis_id, double smear_coef)  {
  return gRandom->Gaus(pos, smear_coef * kSmearSigma[layer_id][axis_id]);
}

int tmp_check_track_finding_230106::ModuleSetType(const vector<int>& mids) {
  int t = 0;
  if (mids[0] % 2 == 1) {
    t += 1;
  }
  if (mids[1] % 2 == 0) {
    t += 2;
  }
  if (mids[2] % 2 == 0) {
    t += 1;
  }
  if (mids[3] % 2 == 1) {
    t += 1;
  }
  return t;
}

void tmp_check_track_finding_230106::IsCurveCorrelation(const array<TVector3, 4>& pos_set, double* dist0, double* dist1) {
  for (int i = 0; i < 2; ++i) {
    double coef1 = (pos_set[2 + i].X() - pos_set[i].X()) / (pos_set[2 + i].Z() - pos_set[i].Z());
    double coef0 = pos_set[i].X() - coef1 * pos_set[i].Z();
    double dist  = fabs(coef1 * pos_set[1 + i].Z() + coef0 - pos_set[1 + i].X()) / sqrt(coef1 * coef1 + 1.);
    if (i == 0) {
      *dist0 = dist;
    } else {
      *dist1 = dist;
    }
  }
  return;
}

TVector3 tmp_check_track_finding_230106::Lotate(double rot_cos, double rot_sin, const TVector3& offset_pos, const TVector3& pos) {
  auto z =       rot_cos * (pos.Z() - offset_pos.Z()) + rot_sin * (pos.X() - offset_pos.X());
  auto x = -1. * rot_sin * (pos.Z() - offset_pos.Z()) + rot_cos * (pos.X() - offset_pos.X());
  return TVector3(x, 0, z);
}

void tmp_check_track_finding_230106::CalcLotatedPos(const array<TVector3, 4>& pos, double rot_cos, double rot_sin, array<TVector3, 4>* lotated_pos) {
  (*lotated_pos)[0] = TVector3(0., 0., 0.);
  for (int i = 1; i < 4; ++i) {
    (*lotated_pos)[i] = Lotate(rot_cos, rot_sin, pos[0], pos[i]);
  }
  return;
}

void tmp_check_track_finding_230106::AddMatrixElement(double w, const TVector3& lotated_pos, array<double, 5>* mz, array<double, 3>* mzx) {
  auto z = lotated_pos.Z();
  auto x = lotated_pos.X();
  (*mz)[0]  += w;
  (*mz)[1]  += w * z;
  (*mz)[2]  += w * z * z;
  (*mz)[3]  += w * z * z * z;
  (*mz)[4]  += w * z * z * z * z;
  (*mzx)[0] += w * x * z * z;
  (*mzx)[1] += w * x * z;
  (*mzx)[2] += w * x;
  return;
}

void tmp_check_track_finding_230106::CalcInverseMatrix(const array<double, 5>& mz, array<array<double, 3>, 3>* matrix) {
  double m11 = mz[4];
  double m12 = mz[3];
  double m13 = mz[2];
  double m21 = mz[3];
  double m22 = mz[2];
  double m23 = mz[1];
  double m31 = mz[2];
  double m32 = mz[1];
  double m33 = mz[0];
  double det = m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32 -
               m13 * m22 * m31 - m12 * m21 * m33 - m11 * m23 * m32;
  (*matrix)[0][0] =       (m22 * m33 - m23 * m32) / det;
  (*matrix)[0][1] = -1. * (m12 * m33 - m13 * m32) / det;
  (*matrix)[0][2] =       (m12 * m23 - m13 * m22) / det;
  (*matrix)[1][0] = -1. * (m21 * m33 - m23 * m31) / det;
  (*matrix)[1][1] =       (m11 * m33 - m13 * m31) / det;
  (*matrix)[1][2] = -1. * (m11 * m23 - m13 * m21) / det;
  (*matrix)[2][0] =       (m21 * m32 - m22 * m31) / det;
  (*matrix)[2][1] = -1. * (m11 * m32 - m12 * m31) / det;
  (*matrix)[2][2] =       (m11 * m22 - m12 * m21) / det;
  return;
}

void tmp_check_track_finding_230106::CalcCoefficients(const array<double, 3>& mzx, const array<array<double, 3>, 3>& matrix, array<double, 3>* coef) {
  for (int i = 0; i < 3; ++i) {
    (*coef)[2 - i] = matrix[i][0] * mzx[0] + matrix[i][1] * mzx[1] + matrix[i][2] * mzx[2];
  }
  return;
}

void tmp_check_track_finding_230106::CalcQuadCurve(const array<TVector3, 4>& lotated_pos, array<double, 5>* mz, array<double, 3>* mzx, array<double, 3>* coef) {
  mz->fill(0.);
  mzx->fill(0.);
  for (int i = 0; i < 4; ++i) {
    AddMatrixElement(kXWeight[i], lotated_pos[i], mz, mzx);
  }
  array<array<double, 3>, 3> matrix;
  CalcInverseMatrix(*mz, &matrix);
  CalcCoefficients(*mzx, matrix, coef);
  return;
}

void tmp_check_track_finding_230106::IsXTrackCandidate(const array<TVector3, 4>& pos_set, array<double, 3>* coefs, double* chi2, double* init_pos_x) {
  std::array<TVector3, 4> lotated_pos;
  auto rot_phi = std::atan2(pos_set[1].X() - pos_set[0].X(), pos_set[1].Z() - pos_set[0].Z());
  auto rot_cos = std::cos(rot_phi);
  auto rot_sin = std::sin(rot_phi);
  CalcLotatedPos(pos_set, rot_cos, rot_sin, &lotated_pos);

  array<double, 5> mz;
  array<double, 3> mzx;
//  array<double, 3> coef;
  CalcQuadCurve(lotated_pos, &mz, &mzx, coefs);

////  CalcTargetZ();
//  double grad = -1. * (rot_sin / rot_cos);
//  double BB_fit = coef[1] - grad;
//  double det_tgt_fit = BB_fit * BB_fit - 4 * coef[2] * coef[0];
//  double tgt_z_cand = E16DST_DST1Constant::kInvalidValue;
//  if (det_tgt_fit > 0) {
//    double fit_tgt1  = (-1. * BB_fit + sqrt(det_tgt_fit)) / (2. * coef[2]);
//    double fit_tgt2  = (-1. * BB_fit - sqrt(det_tgt_fit)) / (2. * coef[2]);
//    double tgt_z_prime_cand = fabs(fit_tgt1) < fabs(fit_tgt2) ? fit_tgt1 : fit_tgt2; 
//    tgt_z_cand = rot_cos * tgt_z_prime_cand - rot_sin * grad * tgt_z_prime_cand;
//  }
//
////  CalcTargetX();
//  double tgt_x_cand;
//  grad = rot_cos / rot_sin;
//  double BBtgt = coef[1] - grad;
////  double CCtgt = coef[0] + tgt_z / rot_sin;
//  double CCtgt = coef[0];
//  det_tgt_fit = BBtgt * BBtgt - 4 * coef[2] * CCtgt;
//  double z0_cand = 0.;
//  double x0 = E16DST_DST1Constant::kInvalidValue;
//  if (det_tgt_fit > 0) {
//    double fit_tgt1 = (-1. * BBtgt + sqrt(det_tgt_fit)) / (2. * coef[2]);
//    double fit_tgt2 = (-1. * BBtgt - sqrt(det_tgt_fit)) / (2. * coef[2]);
//    z0_cand = fabs(fit_tgt1) < fabs(fit_tgt2) ? fit_tgt1 : fit_tgt2; 
//    x0 = rot_sin * z0_cand + rot_cos * grad * z0_cand;
//  }
//  tgt_x_cand = x0;

//  CalcChiSquare();
  *chi2 = 0.;
  for (int i = 0; i < 4; ++i) {
    double fit_posx = (*coefs)[2] * lotated_pos[i].Z() * lotated_pos[i].Z() + (*coefs)[1] * lotated_pos[i].Z() + (*coefs)[0];
    *chi2 += kXWeight[i] * (fit_posx - lotated_pos[i].X()) * (fit_posx - lotated_pos[i].X());
  }

// CalcInitPosX(); // no need
  array<double, 2> z0_coefs = {1. / rot_sin, rot_cos / rot_sin};
  array<double, 3> cross_coefs = {(*coefs)[0] - z0_coefs[0], (*coefs)[1] - z0_coefs[1], (*coefs)[2]};
  double d = cross_coefs[1] * cross_coefs[1] - 4. * cross_coefs[2] * cross_coefs[0];
  if (d < 0) {
    *init_pos_x = 0.;
  } else {
    TVector3 cross_pos;
    cross_pos.SetZ((-1. * cross_coefs[1] - sqrt(d)) / (2. * cross_coefs[2]));
    cross_pos.SetX(cross_pos.Z() * z0_coefs[1] + z0_coefs[0]);
    auto lotate_pos = Lotate(rot_cos, -1. * rot_sin, -1. * pos_set[0], cross_pos);
    *init_pos_x = lotate_pos.X();
  }

//  vector<int> hbd_indexs;
//  vector<int> hbd_ids;
//  vector<double> hbd_ress;
//  if (chi2_cand < prev_chi2 && chi2_cand < kRoughFitChiSquareThreshold[0] &&
//      fabs(coef[0]) < kRoughXFitCoefficientThreshold[0] && fabs(coef[2]) < kRoughXFitCoefficientThreshold[2] &&
//      (!kReqHBDAssociation || HasXAssociatedHBD(tgt_id, *cluster_set, coef, &hbd_indexs, &hbd_ids, &hbd_ress))) {
//    cluster_set->charge = coef[2] > 0 ? 1 : -1;
//    cluster_set->target_id = tgt_id;
//    cluster_set->xy = tgt_x_cand;
//    cluster_set->chi_square = chi2_cand;
//    cluster_set->hbd_indexs.clear();
//    cluster_set->hbd_ids.clear();
//    cluster_set->hbd_ress.clear();
//    for (int i = 0; i < kNumRoughFitDegree[0]; ++i) {
//      cluster_set->coefs[i] = coef[i];
//    }
//    copy(hbd_indexs.begin(),  hbd_indexs.end(),  back_inserter(cluster_set->hbd_indexs));
//    copy(hbd_ids.begin(),     hbd_ids.end(),     back_inserter(cluster_set->hbd_ids));
//    copy(hbd_ress.begin(),    hbd_ress.end(),    back_inserter(cluster_set->hbd_ress));
//    return true;
//  }
//#ifdef TRACK_EFF_CHECK
//  for (int i = 0; i < 2; ++i) {
//    if (is_sim_xcluster[i][0] && is_sim_xcluster[i][1] && is_sim_xcluster[i][2] && is_sim_xcluster[i][3]) {
//      if (chi2_cand >= kRoughFitChiSquareThreshold[0]) {
//        x_fit_reject_point[i] += Pow2(kRejTgt0XChi2 + tgt_id);
//      }
//      if (fabs(coef[0]) >= kRoughXFitCoefficientThreshold[0]) {
//        x_fit_reject_point[i] += Pow2(kRejTgt0XCoef0 + tgt_id);
//      }
//      if (fabs(coef[2]) >= kRoughXFitCoefficientThreshold[2]) {
//        x_fit_reject_point[i] += Pow2(kRejTgt0XCoef2 + tgt_id);
//      }
//    }
//  }
//#endif // TRACK_EFF_CHECK
////cout << "x fit bad. chi2: " << chi2_cand << ", coef0: " << coef[0] << ", coef2: " << coef[2] << endl;
//  return false;
  return;
}

double tmp_check_track_finding_230106::CalcHBDDistance0(const array<TVector3, 4>& pos_set, const TVector3& hbd_pos) {
  double coef_a = (pos_set[3].X() - pos_set[2].X()) / (pos_set[3].Z() - pos_set[2].Z());
  double coef_b = -1. * coef_a * pos_set[2].Z() + pos_set[2].X();
  return fabs(coef_a * hbd_pos.Z() + coef_b - hbd_pos.X()) / sqrt(coef_a * coef_a + 1.);
}

double tmp_check_track_finding_230106::CalcHBDDistance1(const array<TVector3, 4>& pos_set, const TVector3& hbd_pos, const array<double, 3>& coefs) {
  auto rot_phi = std::atan2(pos_set[1].X() - pos_set[0].X(), pos_set[1].Z() - pos_set[0].Z());
  auto rot_cos = std::cos(rot_phi);
  auto rot_sin = std::sin(rot_phi);
  auto lotate_gtr300 = Lotate(rot_cos, rot_sin, pos_set[0], pos_set[3]);
  auto lotate_hbd    = Lotate(rot_cos, rot_sin, pos_set[0], hbd_pos);
  array<double, 2> tan_coefs;
  tan_coefs[1] = 2. * coefs[2] * lotate_gtr300.Z() + coefs[1];
  tan_coefs[0] = lotate_gtr300.X() - tan_coefs[1] * lotate_gtr300.Z();
  return fabs(tan_coefs[1] * lotate_hbd.Z() + tan_coefs[0] - lotate_hbd.X()) / sqrt(tan_coefs[1] * tan_coefs[1] + 1.);
}

double tmp_check_track_finding_230106::CalcHBDDistance2(const array<TVector3, 4>& pos_set, const TVector3& hbd_pos, const array<double, 3>& coefs) {
  auto rot_phi = std::atan2(pos_set[1].X() - pos_set[0].X(), pos_set[1].Z() - pos_set[0].Z());
  auto rot_cos = std::cos(rot_phi);
  auto rot_sin = std::sin(rot_phi);
  auto lotate_gtr300 = Lotate(rot_cos, rot_sin, pos_set[0], pos_set[3]);
  auto lotate_hbd    = Lotate(rot_cos, rot_sin, pos_set[0], hbd_pos);
  return fabs(coefs[2] * lotate_hbd.Z() * lotate_hbd.Z() + coefs[1] * lotate_hbd.Z() + coefs[0] - lotate_hbd.X());
}

double tmp_check_track_finding_230106::CalcHBDDistance3(const array<TVector3, 4>& pos_set, const TVector3& hbd_pos, const array<double, 3>& coefs) {
  auto rot_phi = std::atan2(pos_set[1].X() - pos_set[0].X(), pos_set[1].Z() - pos_set[0].Z());
  auto rot_cos = std::cos(rot_phi);
  auto rot_sin = std::sin(rot_phi);
  auto lotate_gtr300 = Lotate(rot_cos, rot_sin, pos_set[0], pos_set[3]);
  auto lotate_hbd    = Lotate(rot_cos, rot_sin, pos_set[0], hbd_pos);
  double z = lotate_hbd.Z();
  double x = coefs[2] * z * z + coefs[1] * z + coefs[0];
  array<double, 2> tan_coefs;
  tan_coefs[1] = 2. * coefs[2] * z + coefs[1];
  tan_coefs[0] = x - tan_coefs[1] * z;
  return fabs(tan_coefs[1] * lotate_hbd.Z() + tan_coefs[0] - lotate_hbd.X()) / sqrt(tan_coefs[1] * tan_coefs[1] + 1.);
}

void tmp_check_track_finding_230106::IsYTrackCandidate(int ssd_mid, const array<TVector3, 4>& pos_set,
                                                       array<double, 2>* coefs, double* chi2, double* init_pos_y, double* ssd_pos_y) {
  std::array<double, 3> gtr_y({pos_set[1].Y(), pos_set[2].Y(), pos_set[3].Y()});
  std::array<double, 3> gtr_r({sqrt(pos_set[1].X() * pos_set[1].X() + pos_set[1].Z() * pos_set[1].Z()),
                               sqrt(pos_set[2].X() * pos_set[2].X() + pos_set[2].Z() * pos_set[2].Z()),
                               sqrt(pos_set[3].X() * pos_set[3].X() + pos_set[3].Z() * pos_set[3].Z())});
  double r2 = 0.;
  double r  = 0.;
  double c  = 0.;
  double ry = 0.;
  double y  = 0.;
  for (int i = 0; i < 3; ++i) {
    r2 += kYWeight[i] * gtr_r[i] * gtr_r[i];
    r  += kYWeight[i] * gtr_r[i];
    c  += kYWeight[i];
    ry += kYWeight[i] * gtr_r[i] * gtr_y[i];
    y  += kYWeight[i] * gtr_y[i];
  }
  (*coefs)[0] = (r2 * y  - r * ry) / (c * r2 - r * r);
  (*coefs)[1] = (c  * ry - r * y)  / (c * r2 - r * r);
  *chi2 = 0.;
  std::array<double, 3> fit_y;
  for (int i = 0; i < 3; ++i) {
    fit_y[i] = (*coefs)[0] + (*coefs)[1] * gtr_r[i];
    *chi2 += kYWeight[i] * (fit_y[i] - gtr_y[i]) * (fit_y[i] - gtr_y[i]);
  }
  *init_pos_y = (*coefs)[0];
  if (ssd_mid % 2 == 1) {
    *ssd_pos_y  = (*coefs)[0] + (*coefs)[1] * kSSDRoughRadius[0];
  } else {
    *ssd_pos_y  = (*coefs)[0] + (*coefs)[1] * kSSDRoughRadius[1];
  }
//  if (chi2_cand < kRoughFitChiSquareThreshold[1] && fabs(coef[0]) < kRoughYFitCoefficientThreshold[0]) {
//    cluster_set->xy = coef[0];
//    cluster_set->chi_square = chi2_cand;
//    for (int i = 0; i < kNumRoughFitDegree[1]; ++i) {
//      cluster_set->coefs[i] = coef[i];
//    }
//    return true;
//  }
//#ifdef TRACK_EFF_CHECK
//  for (int i = 0; i < 2; ++i) {
//    if (is_sim_ycluster[i][0] && is_sim_ycluster[i][1] && is_sim_ycluster[i][2]) {
//      if (chi2_cand < kRoughFitChiSquareThreshold[1]) {
//        y_reject_point[i] += Pow2(kRejYChi2);
//      }
//      if (fabs(coef[0]) < kRoughYFitCoefficientThreshold[0]) {
//        y_reject_point[i] += Pow2(kRejYCoef0);
//      }
//    }
//  }
//#endif
////cout << "y chi2 bad" << endl;
//  return false;
  return;
}

TVector3 tmp_check_track_finding_230106::CalcRoughMomentum(double xcoef2, double ycoef1, const array<TVector3, 4>& pos_set) {
//  constexpr double kBy = 1.3; 
  constexpr double kBy = 1.13;
  double cogz = 0.;
  double cogx = 0.;
  for (int i = 0; i < 4; ++i) {
    cogz += pos_set[i].Z();
    cogx += pos_set[i].X();
  }
  cogz /= 4;
  cogx /= 4;
  double t30 = 0.;
  double t20 = 0.;
  double t12 = 0.;
  double t11 = 0.;
  double t03 = 0.;
  double t02 = 0.;
  double t21 = 0.;
  for (int i = 0; i < 4; ++i) {
    double z = pos_set[i].Z() - cogz;
    double x = pos_set[i].X() - cogx;
    double zz = z * z;
    double xx = x * x;
    t30 += zz * z;
    t20 += zz;
    t12 += z * xx;
    t11 += z * x;
    t03 += xx * x;
    t02 += xx;
    t21 += zz * x;
  }
  double c = 0.5 / (t20 * t02 - t11 * t11);
  double cz = c * (t02 * (t30 + t12) - t11 * (t03 + t21));
  double cx = c * (t20 * (t03 + t21) - t11 * (t30 + t12));
  double r = sqrt(cz * cz + cx * cx + 0.25 * (t20 + t02));
  double mom = 0.3 * (r  * 0.001) * kBy;
  double sin = (pos_set[0].X() - (cx + cogx)) / r;
  double cos = (pos_set[0].Z() - (cz + cogz)) / r;
  constexpr double kXMomOffset = 0.015;
  if (xcoef2 > 0.) {
    if (cos > 0.) {
      return TVector3(cos * mom - kXMomOffset, ycoef1 * mom, -1. * sin * mom);
    } else {
      return TVector3(cos * mom + kXMomOffset, ycoef1 * mom, -1. * sin * mom);
    }
  } else {
    if (cos < 0.) {
      return TVector3(-1. * cos * mom - kXMomOffset, ycoef1 * mom, sin * mom);
    } else {
      return TVector3(-1. * cos * mom + kXMomOffset, ycoef1 * mom, sin * mom);
    }
  }
}

void tmp_check_track_finding_230106::SearchThreshold(double efficiency, TH1F& hist, array<double, 2>* thresholds) {
  auto n_fills = hist.Integral();
  auto n_bins  = hist.GetNbinsX();
  if (double{hist.Integral(1, n_bins)} / n_fills < efficiency) {
    thresholds->fill(100000.);
    return;
  }
  auto bin_width = hist.GetXaxis()->GetBinWidth(1);
  auto max_n = hist.GetMaximumBin();
  int min_bin_id = max_n;
  int max_bin_id = max_n;
  while (true) {
    if (min_bin_id < 1 || max_bin_id > n_bins) {
      break;
    }
    auto n = hist.Integral(min_bin_id, max_bin_id);
    if (double{n} / n_fills > efficiency) {
      break;
    }
    auto min_n = hist.Integral(min_bin_id - 1, min_bin_id - 1);
    auto max_n = hist.Integral(max_bin_id + 1, max_bin_id + 1);
    if (min_n > max_n) {
      --min_bin_id;
    } else {
      ++max_bin_id;
    }
  }
  thresholds->at(0) = (min_bin_id - 1) * bin_width;
  thresholds->at(1) = max_bin_id * bin_width;
  return;
}

double tmp_check_track_finding_230106::SearchThreshold(bool is_symmetry, double efficiency, TH1F& hist) {
  auto n_fills = hist.Integral();
  auto n_bins  = hist.GetNbinsX();
  if (double{hist.Integral(1, n_bins)} / n_fills < efficiency) {
    return 100000.;
  }
//  double min;
//  hist.GetXaxis()->GetLowEdge(&min);
  auto bin_width = hist.GetXaxis()->GetBinWidth(1);
  int bin_id = 1;
  if (is_symmetry) {
    n_bins /= 2;
  }
  for (; bin_id < n_bins; ++bin_id) {
    int n;
    if (is_symmetry) {
      n = hist.Integral(n_bins + 1 - bin_id, n_bins + bin_id);
    } else {
      n = hist.Integral(1, bin_id);
    }
    double ratio = double{n} / n_fills;
    if (ratio > efficiency) {
      break;
    }
  }
  return bin_id * bin_width;
}

void tmp_check_track_finding_230106::Loop(double smear_coef, const TString& out_name) {
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntries();
  Long64_t nbytes = 0, nb = 0;
  
  auto geometry = new E16ANA_GeometryV2(kGeometryFile);
  E16ANA_GeometryV2::SetGlobalPointer(geometry);
  auto file = TFile(out_name, "recreate");
  auto tree = TTree("tree", "tree");
  int charge_id;
  vector<int> mids;
  int module_set_type;
  double mock_ssd_pos_y;
  TVector3 mock_ssd_mom;
  double dist0;
  double dist1;
  double xcoef0;
  double xcoef1;
  double xcoef2;
  double xchi2;
  double hbd_dist0;
  double hbd_dist1;
  double hbd_dist2;
  double hbd_dist3;
  double ycoef0;
  double ycoef1;
  double ychi2;
//  TVector3 init_pos;
  double ssd_pos_y;
  TVector3 init_mom; // @SSD
  tree.Branch("charge_id",       &charge_id,       "charge_id/I");
  tree.Branch("mids",            &mids);
  tree.Branch("module_set_type", &module_set_type, "module_set_type/I");
  tree.Branch("mock_ssd_pos_y",  &mock_ssd_pos_y,  "mock_ssd_pos_y/D");
  tree.Branch("mock_ssd_mom",    &mock_ssd_mom);
  tree.Branch("dist0",           &dist0,           "dist0/D");
  tree.Branch("dist1",           &dist1,           "dist1/D");
  tree.Branch("xcoef0",          &xcoef0,          "xcoef0/D");
  tree.Branch("xcoef1",          &xcoef1,          "xcoef1/D");
  tree.Branch("xcoef2",          &xcoef2,          "xcoef2/D");
  tree.Branch("xchi2",           &xchi2,           "xchi2/D");
  tree.Branch("hbd_dist0",       &hbd_dist0,       "hbd_dist0/D");
  tree.Branch("hbd_dist1",       &hbd_dist1,       "hbd_dist1/D");
  tree.Branch("hbd_dist2",       &hbd_dist2,       "hbd_dist2/D");
  tree.Branch("hbd_dist3",       &hbd_dist3,       "hbd_dist3/D");
  tree.Branch("ycoef0",          &ycoef0,          "ycoef0/D");
  tree.Branch("ycoef1",          &ycoef1,          "ycoef1/D");
  tree.Branch("ychi2",           &ychi2,           "ychi2/D");
//  tree.Branch("init_pos",        &init_pos);
  tree.Branch("ssd_pos_y",       &ssd_pos_y,       "ssd_pos_y/D");
  tree.Branch("init_mom",        &init_mom);
  array<TH1F, 6> h_xdist_ratio;
  array<TH1F, 3> h_xcoef;
  array<TH1F, 2> h_ycoef;
  array<TH1F, 2> h_chi2;
  for (int i = 0; i < 6; ++i) {
    auto foot = TString(Form("_%d", i));
    h_xdist_ratio[i] = TH1F("h_xdist_ratio" + foot, "h_xdist_ratio" + foot, kNumXDistHistBins, kXDistHistRange[0], kXDistHistRange[1]);
    if (i < 3) {
      h_xcoef[i] = TH1F("h_xcoef" + foot, "h_xcoef" + foot, kNumXCoefHistBins[i], kXCoefHistRange[i][0], kXCoefHistRange[i][1]);
    }
    if (i < 2) {
      h_ycoef[i] = TH1F("h_ycoef" + foot, "h_ycoef" + foot, kNumYCoefHistBins[i], kYCoefHistRange[i][0], kYCoefHistRange[i][1]);
      h_chi2[i]  = TH1F("h_chi2"  + foot, "h_chi2"  + foot, kNumChiHistBins[i],   kChiHistRange[i][0],   kChiHistRange[i][1]);
    }
  }
  for (Long64_t jentry = 0; jentry < nentries; ++jentry) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);
    nbytes += nb;
    if (jentry % 1000 == 0) {
      cout << jentry << " / " << nentries << endl;
    }
    for (int i = 0; i < mock_n_tracks; ++i) {
      if (mock_pid->at(i) == 310) {
        continue;
      }
      if (mock_pid->at(i) > 0) {
        charge_id = 0;
      } else {
        charge_id = 1;
      }
      mids.resize(4);
      mids[0] = mock_ssd_mid->at(i);
      mids[1] = mock_gtr100_mid->at(i);
      mids[2] = mock_gtr200_mid->at(i);
      mids[3] = mock_gtr300_mid->at(i);
      module_set_type = ModuleSetType(mids);
      mock_ssd_pos_y = mock_ssd_gpos_y->at(i);
      mock_ssd_mom = TVector3(mock_ssd_gmom_x->at(i), mock_ssd_gmom_y->at(i), mock_ssd_gmom_z->at(i));
      array<TVector3, 4> xpos_set;
//      xpos_set[0] = geometry->SSD(ModuleID2020To2013(mids[0]))->GetGPos(TVector3(mock_ssd_lpos_x->at(i), 0., 0.));
//      xpos_set[1] = geometry->GTR(ModuleID2020To2013(mids[1]), 0)->GetGPos(TVector3(mock_gtr100_lpos_x->at(i), 0., 0.));
//      xpos_set[2] = geometry->GTR(ModuleID2020To2013(mids[2]), 1)->GetGPos(TVector3(mock_gtr200_lpos_x->at(i), 0., 0.));
//      xpos_set[3] = geometry->GTR(ModuleID2020To2013(mids[3]), 2)->GetGPos(TVector3(mock_gtr300_lpos_x->at(i), 0., 0.));
      xpos_set[0] = geometry->SSD(ModuleID2020To2013(mids[0]))->GetGPos(TVector3(SmearPosition(mock_ssd_lpos_x->at(i), 0, 0, smear_coef), 0., 0.));
      xpos_set[1] = geometry->GTR(ModuleID2020To2013(mids[1]), 0)->GetGPos(TVector3(SmearPosition(mock_gtr100_lpos_x->at(i), 1, 0, smear_coef), 0., 0.));
      xpos_set[2] = geometry->GTR(ModuleID2020To2013(mids[2]), 1)->GetGPos(TVector3(SmearPosition(mock_gtr200_lpos_x->at(i), 2, 0, smear_coef), 0., 0.));
      xpos_set[3] = geometry->GTR(ModuleID2020To2013(mids[3]), 2)->GetGPos(TVector3(SmearPosition(mock_gtr300_lpos_x->at(i), 3, 0, smear_coef), 0., 0.));
      IsCurveCorrelation(xpos_set, &dist0, &dist1);
      array<double, 3> xcoefs;
      double ipos_x;
      IsXTrackCandidate(xpos_set, &xcoefs, &xchi2, &ipos_x);
      xcoef0 = xcoefs[0];
      xcoef1 = xcoefs[1];
      xcoef2 = xcoefs[2];
//      init_pos.SetX(ipos_x);

      auto hbd_pos = TVector3(mock_hbd_gpos_x->at(i), mock_hbd_gpos_y->at(i), mock_hbd_gpos_z->at(i));
      hbd_dist0 = CalcHBDDistance0(xpos_set, hbd_pos);
      hbd_dist1 = CalcHBDDistance1(xpos_set, hbd_pos, xcoefs);
      hbd_dist2 = CalcHBDDistance2(xpos_set, hbd_pos, xcoefs);
      hbd_dist3 = CalcHBDDistance3(xpos_set, hbd_pos, xcoefs);
      
      array<TVector3, 4> ypos_set;
      ypos_set[0] = TVector3(0., 0., 0.);
      ypos_set[1] = geometry->GTR(ModuleID2020To2013(mids[1]), 0)->GetGPos(TVector3(0., SmearPosition(mock_gtr100_lpos_y->at(i), 1, 1, smear_coef), 0.));
      ypos_set[2] = geometry->GTR(ModuleID2020To2013(mids[2]), 1)->GetGPos(TVector3(0., SmearPosition(mock_gtr200_lpos_y->at(i), 2, 1, smear_coef), 0.));
      ypos_set[3] = geometry->GTR(ModuleID2020To2013(mids[3]), 2)->GetGPos(TVector3(0., SmearPosition(mock_gtr300_lpos_y->at(i), 3, 1, smear_coef), 0.));
      array<double, 2> ycoefs;
      double ipos_y;
      IsYTrackCandidate(mids[0], ypos_set, &ycoefs, &ychi2, &ipos_y, &ssd_pos_y);
      ycoef0 = ycoefs[0];
      ycoef1 = ycoefs[1];
//      init_pos.SetY(ipos_y);
      
      init_mom = CalcRoughMomentum(xcoefs[2], ycoefs[1], xpos_set);
      
      tree.Fill();
      h_xdist_ratio[module_set_type].Fill(dist0 / dist1);
      for (int i = 0; i < 3; ++i) {
        h_xcoef[i].Fill(xcoefs[i]);
      }
      for (int i = 0; i < 2; ++i) {
        h_ycoef[i].Fill(ycoefs[i]);
      }
      h_chi2[0].Fill(xchi2);
      h_chi2[1].Fill(ychi2);
    }
  }
  auto canvas = TCanvas("c_xdist_ratio", "c_xdist_ratio");
  canvas.Divide(3, 2);
  constexpr double kEfficiency = 0.93;
  array<array<TLine, 2>, 6> l_xdist;
  for (int i = 0; i < 6; ++i) {
    canvas.cd(1 + i);
    h_xdist_ratio[i].Draw();
    array<double, 2> thresholds;
    SearchThreshold(kEfficiency, h_xdist_ratio[i], &thresholds);
    for (int j = 0; j < 2; ++j) {
//      l_xdist[i][j] = TLine(kXCurveCorrWindow[i][j], 0., kXCurveCorrWindow[i][j], 1000000.);
      l_xdist[i][j] = TLine(thresholds[j], 0., thresholds[j], 1000000.);
      l_xdist[i][j].SetLineColor(kRed);
      l_xdist[i][j].Draw();
    }
  }
  canvas.Write();
  
  auto canvas1 = TCanvas("c_find_param", "c_find_param");
  canvas1.Divide(3, 3);
  array<TLine, 2> l_chi;
  array<array<TLine, 2>, 3> l_xcoef;
  array<TLine, 2> l_ycoef;
  for (int i = 0; i < 2; ++i) {
    canvas1.cd(1 + i);
    h_chi2[i].Draw();
//    l_chi[i] = TLine(kRoughFitChiSquareThreshold[i], 0., kRoughFitChiSquareThreshold[i], 1000000.);
    auto threshold = SearchThreshold(false, kEfficiency, h_chi2[i]);
    l_chi[i] = TLine(threshold, 0., threshold, 1000000.);
    l_chi[i].SetLineColor(kRed);
    l_chi[i].Draw();
  }
  for (int i = 0; i < 3; ++i) {
    canvas1.cd(4 + i);
    h_xcoef[i].Draw();
//    l_xcoef[i][0] = TLine(-1. * kRoughXFitCoefficientThreshold[i], 0., -1. * kRoughXFitCoefficientThreshold[i], 1000000.);
//    l_xcoef[i][1] = TLine(kRoughXFitCoefficientThreshold[i], 0., kRoughXFitCoefficientThreshold[i], 1000000.);
    auto threshold = SearchThreshold(true, kEfficiency, h_xcoef[i]);
    l_xcoef[i][0] = TLine(-1. * threshold, 0., -1. * threshold, 1000000.);
    l_xcoef[i][1] = TLine(threshold, 0., threshold, 1000000.);
    for (int j = 0; j < 2; ++j) {
      l_xcoef[i][j].SetLineColor(kRed);
      l_xcoef[i][j].Draw();
    }
  }
  for (int i = 0; i < 2; ++i) {
    canvas1.cd(7 + i);
    h_ycoef[i].Draw();
    if (i == 0) {
//      l_ycoef[0] = TLine(-1. * kRoughYFitCoefficientThreshold[i], 0., -1. * kRoughYFitCoefficientThreshold[i], 1000000.);
//      l_ycoef[1] = TLine(kRoughYFitCoefficientThreshold[i], 0., kRoughYFitCoefficientThreshold[i], 1000000.);
      auto threshold = SearchThreshold(true, kEfficiency, h_ycoef[i]);
      l_ycoef[0] = TLine(-1. * threshold, 0., -1. * threshold, 1000000.);
      l_ycoef[1] = TLine(threshold, 0., threshold, 1000000.);
      for (int j = 0; j < 2; ++j) {
        l_ycoef[j].SetLineColor(kRed);
        l_ycoef[j].Draw();
      }
    }
  }
  canvas1.Write();
  file.Write();
}
