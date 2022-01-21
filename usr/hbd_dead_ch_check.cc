#include "E16DST_Constant.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_HBDCalibration.hh"
#include "E16ANA_HBDConstant.hh"
#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_HBDChannelManager.hh"
#include "E16ANA_HBDTH2Hex.hh"

#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "TCanvas.h"

int main(int argc, char **argv){

  if(argc != 2){
    std::cerr<<"usage: ./hbd_dead_ch_check [run ID]"<<std::endl;
    return 0;
  }
  int run_id = std::atoi(argv[1]);

  //------ define constants
  const int n_modules = E16DST_Constant::NModules;
  int module_ID[n_modules];
  for(int i=0; i<n_modules; i++){
    module_ID[i] = HBD_Module_Constant::module_ids[i];
  }
  //------ define constants

  //------ calibration
  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  
  E16ANA_HBDCalibration *hbd_calib = new E16ANA_HBDCalibration();
  hbd_calib->ReadCalibrationData(calib.CurrentRunID());
  //------ calibration
  
  E16ANA_HBDTH2Hex *hh[n_modules];
  for(int i=0; i<n_modules; i++){
    hh[i] = new E16ANA_HBDTH2Hex(module_ID[i], Form("hh_%d", module_ID[i]), Form("hh_%d", module_ID[i]));
    std::vector<int> ok_chs;
    hbd_calib->GetDeadChannel()->GetOKChannels(module_ID[i], ok_chs);
    for(auto ch : ok_chs){
      std::cerr<<module_ID[i]<<" "<<ch<<std::endl;

      hh[i]->Fill(ch, 1);// weight of 1, omomi ha nanndemoii
    }
  }
  
  //------ define canvas
  TCanvas *cvs[n_modules];
  for(int i=0; i<n_modules; i++){
    cvs[i] = new TCanvas(Form("cvs_%d", i), Form("cvs_%d", i), 1200, 800);
    cvs[i]->cd(1);
    hh[i]->Draw("COLZ0");
    
    if(i==0) cvs[i]->SaveAs("dead_ch_hexpad.pdf(");
    if(i!=0 && i!=n_modules-1) cvs[i]->SaveAs("dead_ch_hexpad.pdf");
    if(i==n_modules-1) cvs[i]->SaveAs("dead_ch_hexpad.pdf)");
  }
  //------ define canvas
  
  return 0;
}
