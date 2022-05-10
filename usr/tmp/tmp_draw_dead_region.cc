#include <iostream>
#include <TCanvas.h>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
//#include <boost/program_options.hpp>

#include "E16ANA_CalibDBManager.hh"
//#include "E16ANA_WaveformFitter.hh"
#include "E16ANA_WaveformFitterCRRC.hh"
#include "E16ANA_FieldMapCalib.hh"
#include "E16ANA_EventSelect.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_GTRChannelManager.h"
#include "E16ANA_GTRLorentzAngleCalib.hh"
#include "E16ANA_GTRStatus.h"
#include "E16ANA_HBDCalibration.hh"
#include "E16ANA_HBDCut.hh"
#include "E16ANA_HBDDeadChannel.hh"
#include "E16ANA_LGDeadChannel.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16DST_DST1DefaultFilePath.hh"

#include "E16ANA_TrackCheckFile.hh"

#include "E16ANA_GTRAnalyzerMaker.hh"

using namespace std;
//namespace  bpo = boost::program_options;

constexpr bool kIsElectronRun = true;
constexpr bool kSelectEvent   = false;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "./bin run_id output.pdf" << endl;
    return -1;
  }
  auto run_id = stoi(argv[1]);
  auto out_file_name = static_cast<TString>(argv[2]);
  gROOT->ProcessLine(".x ~/.rootlogon.C");

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  E16ANA_FieldMapCalibParam field_map_param;
  field_map_param.ReadConstantData(calib.CurrentRunID());
  E16ANA_EventSelect event_select;
  event_select.ReadConstantData(calib.CurrentRunID());
  auto& selected_event_ids = event_select.SelectedEventIDs();
  int current_ids_index = 0;
  auto n_selected_events = event_select.NumSelectedEventIDs();
  E16ANA_GTRcalibPedestal gtrped;
  gtrped.ReadCalibData( calib.CurrentRunID() );
  E16ANA_GTRLorentzAngleCalibParamManager gtr_lorentz_angle_calib_param_manager;
  gtr_lorentz_angle_calib_param_manager.ReadConstantData(calib.CurrentRunID());
  auto gtr_lorentz_angle_calib_params = gtr_lorentz_angle_calib_param_manager.GTRLorentzAngleCalibParams();
  E16ANA_HBDCalibration *hbd_calib = new E16ANA_HBDCalibration();
  hbd_calib->ReadCalibrationData(calib.CurrentRunID());
  E16ANA_HBDCut *hbd_cut = new E16ANA_HBDCut();
  hbd_cut->ReadCutData(calib.CurrentRunID());
  E16ANA_HBDCut *hbd_cut_wo_timing = new E16ANA_HBDCut();
  hbd_cut_wo_timing->ReadCutData(calib.CurrentRunID());
  hbd_cut_wo_timing->SetCut("clustering_time_window_start", -10000.);
  hbd_cut_wo_timing->SetCut("clustering_time_window_end", 10000.);
//  std::string hbd_waveform_template = calib.CalibFileName("HBD-waveform-template", 0);
  E16ANA_LGBasic lgbasic;
  lgbasic.SetMap();
  lgbasic.SetCalibMap();
  E16ANA_TriggerCalibParam trigger_param;
  trigger_param.ReadConstantData(calib.CurrentRunID());

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  E16ANA_GeometryV2::SetGlobalPointer(geometry);
  auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
  bfield_map->Initialize_binary();
  E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
  
  E16ANA_WaveformFitterCRRC *wf1d_fitter = new E16ANA_WaveformFitterCRRC();
  E16ANA_MultiTrack fitter(bfield_map, geometry, 1);
  E16ANA_MultiTrack pair_fitter(bfield_map, geometry, 2);

  E16ANA_GTRcalibParams gtr_params;
  gtr_params.ReadCalibData(run_id);
  auto gtr_analyzers = new E16ANA_GTRAnalyzerMaker(gtr_params);
  for(int mid = 100; mid <= 110; ++mid) {
    for(int lid = 0; lid < 3; ++lid) {
      auto gtr_analyzer2 = gtr_analyzers->Chamber(mid, lid);
      int n_strips = gtr_analyzer2->GetNumberOfStrips();
      for(int strip_id = 0; strip_id < n_strips; ++strip_id) {
        double ped = gtrped.GetPedestal(mid, lid, strip_id).Value();
        double sigma = gtrped.GetPedestal(mid, lid, strip_id).Sigma();
        gtr_analyzer2->SetPedestal(strip_id, ped);
        gtr_analyzer2->SetPedestalSigma(strip_id, sigma);
      }
    }
  }
  auto gtr_stat = E16ANA_GTRStatus(run_id);
  
  auto hbd_dead_ch = E16ANA_HBDDeadChannel();
  hbd_dead_ch.ReadDeadChannelData(run_id);
  auto lg_dead_ch = E16ANA_LGDeadChannel();
  lg_dead_ch.ReadDeadChannelData();
  
  array<array<TH2I*, 9>, 4> h_gem;
  array<array<TH2I*, 9>, 4> h_apv;
  array<array<TH2I*, 9>, 4> h_dead;
  double range[6] = {50., 100., 150., 300., 400.};
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 9; ++j) {
      int mid = 101 + j;
      TString name0 = Form("h_gem_%d_%d", i, j);
      TString name1 = Form("h_apv_%d_%d", i, j);
      TString name2 = Form("h_dead_%d_%d", i, j);
      h_gem[i][j] = new TH2I(name0, name0, 200, -1. * range[i], range[i], 200, -1. * range[i], range[i]);
      h_apv[i][j] = new TH2I(name1, name1, 200, -1. * range[i], range[i], 200, -1. * range[i], range[i]);
      h_dead[i][j]     = new TH2I(name2, name2, 200, -1. * range[i], range[i], 200, -1. * range[i], range[i]);
    }
  }
  auto gtr100_stat = gtr_stat.GEMDeadArea100();
  auto gtr200_stat = gtr_stat.GEMDeadArea200();
  auto gtr300_stat = gtr_stat.GEMDeadArea300();
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 9; ++j) {
      auto mid = 101 + j;
      for (int k = 0; k < 200; ++k) {
        double x = k * range[i] / 100 - range[i];
        int apv_x_ch;
        bool is_apv_x_dead;
        if (i < 3) {
          apv_x_ch = E16ANA_GTRChannelManager::ConvLocalXToAPVch(i, x);
          is_apv_x_dead = gtr_analyzers->Chamber(mid, i)->GetStripX()->IsBadStrip(apv_x_ch);
        }
        for (int l = 0; l < 200; ++l) {
          double y = l * range[i] / 100 - range[i];
          int apv_y_ch;
          bool is_apv_y_dead;
          if (i < 3) {
            apv_y_ch = E16ANA_GTRChannelManager::ConvLocalYToAPVch(i, y);
            is_apv_y_dead = gtr_analyzers->Chamber(mid, i)->GetStripY()->IsBadStrip(apv_y_ch);
          }
          if (i == 0) {
            if (gtr100_stat->IsXOK(mid, x) && gtr100_stat->IsYOK(mid, y)) {
              h_gem[i][j]->Fill(x, y, 1);
            } else {
              h_gem[i][j]->Fill(x, y, -1);
            }
            if (!is_apv_x_dead && !is_apv_y_dead) {
              h_apv[i][j]->Fill(x, y, 1);
            } else {
              h_apv[i][j]->Fill(x, y, -1);
            }
            if (gtr100_stat->IsXOK(mid, x) && gtr100_stat->IsYOK(mid, y) && !is_apv_x_dead && !is_apv_y_dead) {
              h_dead[i][j]->Fill(x, y, 1);
            } else {
              h_dead[i][j]->Fill(x, y, -1);
            }
          } else if (i == 1) {
            if (gtr200_stat->IsXOK(mid, x) && gtr200_stat->IsYOK(mid, y)) {
              h_gem[i][j]->Fill(x, y, 1);
            } else {
              h_gem[i][j]->Fill(x, y, -1);
            }
            if (!is_apv_x_dead && !is_apv_y_dead) {
              h_apv[i][j]->Fill(x, y, 1);
            } else {
              h_apv[i][j]->Fill(x, y, -1);
            }
            if (gtr200_stat->IsXOK(mid, x) && gtr200_stat->IsYOK(mid, y) && !is_apv_x_dead && !is_apv_y_dead) {
              h_dead[i][j]->Fill(x, y, 1);
            } else {
              h_dead[i][j]->Fill(x, y, -1);
            }
          } else if (i == 2) {
            if (gtr300_stat->IsXOK(mid, x) && gtr300_stat->IsYOK(mid, y)) {
              h_gem[i][j]->Fill(x, y, 1);
            } else {
              h_gem[i][j]->Fill(x, y, -1);
            }
            if (!is_apv_x_dead && !is_apv_y_dead) {
              h_apv[i][j]->Fill(x, y, 1);
            } else {
              h_apv[i][j]->Fill(x, y, -1);
            }
            if (gtr300_stat->IsXOK(mid, x) && gtr300_stat->IsYOK(mid, y) && !is_apv_x_dead && !is_apv_y_dead) {
              h_dead[i][j]->Fill(x, y, 1);
            } else {
              h_dead[i][j]->Fill(x, y, -1);
            }
          } else if (i == 3) {
            double cog[2] = {x, y};
            h_dead[i][j]->Fill(x, y, hbd_dead_ch.StatusWLocalCoordinate(mid, cog));
          }
        }
      }
    }
  }
  auto out_canvas = new TCanvas();
  out_canvas->Print(out_file_name + "[");
  for (int i = 0; i < 4; ++i) {
    out_canvas->Clear();
    out_canvas->Divide(3, 3);
    for (int j = 0; j < 9; ++j) {
      out_canvas->cd(1 + j);
      h_gem[i][j]->Draw("colz");
    }
    out_canvas->Print(out_file_name);
  }
  for (int i = 0; i < 4; ++i) {
    out_canvas->Clear();
    out_canvas->Divide(3, 3);
    for (int j = 0; j < 9; ++j) {
      out_canvas->cd(1 + j);
      h_apv[i][j]->Draw("colz");
    }
    out_canvas->Print(out_file_name);
  }
  for (int i = 0; i < 4; ++i) {
    out_canvas->Clear();
    out_canvas->Divide(3, 3);
    for (int j = 0; j < 9; ++j) {
      out_canvas->cd(1 + j);
      h_dead[i][j]->Draw("colz");
    }
    out_canvas->Print(out_file_name);
  }
  out_canvas->Print(out_file_name + "]");
  return 0;
}
