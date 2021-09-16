#include "E16ANA_HBDTH2Hex.hh"
#include "E16ANA_HBDConstant.hh"
#include "E16ANA_HBDGeometry.hh"

#include "E16DST_Constant.hh"

#include <iostream>
#include <cmath>

#include <TH2Poly.h>
#include <TPad.h>
#include <TGaxis.h>

E16ANA_HBDTH2Hex::E16ANA_HBDTH2Hex(const int _module_id) :
  module_id(_module_id)
{
  if( E16ANA_HBDGeometry::IsRotated(module_id) ){
    x_direction = 1;
    y_direction = -1;
  }
  else{
    x_direction = -1;
    y_direction = 1;
  }
  if(IsXAxisNormal() || IsXAxisReverse()){
    if(IsYAxisNormal() || IsYAxisReverse()){
      SetHBDHexBin();
    }
  }
}

E16ANA_HBDTH2Hex::E16ANA_HBDTH2Hex(const int _module_id, const char *name, const char *title) :
  module_id(_module_id)
{
  this->SetName(name);
  this->SetTitle(title);
  
  if( E16ANA_HBDGeometry::IsRotated(module_id) ){
    x_direction = 1;
    y_direction = -1;
  }
  else{
    x_direction = -1;
    y_direction = 1;
  }
  if(IsXAxisNormal() || IsXAxisReverse()){
    if(IsYAxisNormal() || IsYAxisReverse()){
      SetHBDHexBin();
    }
  }
}

E16ANA_HBDTH2Hex::E16ANA_HBDTH2Hex(std::string state)
{
  if(state == "rotated"){
    module_id = HBD_Module_Constant::rotated_module_ids[0];
  }else{
    module_id = HBD_Module_Constant::normal_module_ids[0];
  }
  
  if( E16ANA_HBDGeometry::IsRotated(module_id) ){
    x_direction = 1;
    y_direction = -1;
  }
  else{
    x_direction = -1;
    y_direction = 1;
  }
  if(IsXAxisNormal() || IsXAxisReverse()){
    if(IsYAxisNormal() || IsYAxisReverse()){
      SetHBDHexBin();
    }
  }
}

E16ANA_HBDTH2Hex::~E16ANA_HBDTH2Hex()
{
}

void E16ANA_HBDTH2Hex::SetHBDHexBin(){
  
  double x[6], y[6];
  double x_start, y_start;
  
  //--- lower panel ---//
  x_start = a;
  y_start = 0.;
  for(int j=0; j<n_pad_x/2; j++){//pad id 0--19
    y[0] = y_start;
    y[1] = y[0];
    y[2] = y[1] + std::sqrt(3.)/2.*a;
    y[3] = y[2];
    x[0] = x_start - a + 3.*a*j;
    x[1] = x[0] + 2.*a;
    x[2] = x[1] - a/2.;
    x[3] = x[2] - a;
    for(int k=0; k<4; k++) x[k] = x_direction*x[k];
    for(int k=0; k<4; k++) y[k] = y_direction*y[k];
    this->AddBin(4, x, y);
  }
  
  for(int i=0; i<n_pad_y/2; i++){//pad id 20--359
    for(int j=0; j<n_pad_x/2; j++){
      if(j != n_pad_x/2-1){
	y[0] = y_start + std::sqrt(3.)/2.*a + std::sqrt(3.)*a*i;
	y[1] = y[0] - std::sqrt(3.)/2.*a;
	y[2] = y[1];
	y[3] = y[0];
	y[4] = y[0] + std::sqrt(3.)/2.*a;
	y[5] = y[4];
	x[0] = x_start + a/2. + 3.*a*j;
	x[1] = x[0] + a/2.;
	x[2] = x[1] + a;
	x[3] = x[2] + a/2.;
	x[4] = x[2];
	x[5] = x[1];
	for(int k=0; k<6; k++) x[k] = x_direction*x[k];
	for(int k=0; k<6; k++) y[k] = y_direction*y[k];
	this->AddBin(6, x, y);
      }
      else if(j == n_pad_x/2-1){
	y[0] = y_start + std::sqrt(3.)/2.*a + std::sqrt(3.)*a*i;
	y[1] = y[0] - std::sqrt(3.)/2.*a;
	y[2] = y[1];
	y[3] = y[2] + std::sqrt(3.)*a;
	y[4] = y[3];
	x[0] = x_start + a/2. + 3.*a*j;
	x[1] = x[0] + a/2.;
	x[2] = x[1] + a/3.;
	x[3] = x[2];
	x[4] = x[3] - a/3.;
	for(int k=0; k<5; k++) x[k] = x_direction*x[k];
	for(int k=0; k<5; k++) y[k] = y_direction*y[k];
	this->AddBin(5, x, y);
      }
    }

    if( i != n_pad_y/2 - 1){
      for(int j=0; j<n_pad_x/2; j++){
	y[0] = y_start + std::sqrt(3.)*a + std::sqrt(3.)*a*i;
	y[1] = y[0] - std::sqrt(3.)/2.*a;
	y[2] = y[1];
	y[3] = y[0];
	y[4] = y[0] + std::sqrt(3.)/2.*a;
	y[5] = y[4];
	x[0] = x_start - a + 3.*a*j;
	x[1] = x[0] + a/2.;
	x[2] = x[1] + a;
	x[3] = x[2] + a/2.;
	x[4] = x[2];
	x[5] = x[1];
	for(int k=0; k<6; k++) x[k] = x_direction*x[k];
	for(int k=0; k<6; k++) y[k] = y_direction*y[k];
	this->AddBin(6, x, y);
      }
    }
  }
  
  for(int j=0; j<n_pad_x/2; j++){
    y[0] = y_start + std::sqrt(3.)*a*n_pad_y/2;
    y[1] = y[0] - std::sqrt(3.)/2.*a;
    y[2] = y[1];
    y[3] = y[0];
    x[0] = x_start - a + 3.*a*j;
    x[1] = x[0] + a/2.;
    x[2] = x[1] + a;
    x[3] = x[2] + a/2.;
    for(int k=0; k<4; k++) x[k] = x_direction*x[k];
    for(int k=0; k<4; k++) y[k] = y_direction*y[k];
    this->AddBin(4, x, y);
  }  
  //--- lower panel ---//

  //--- upper panel ---//
  y_start = std::sqrt(3.)*a*n_pad_y/2;
  for(int j=0; j<n_pad_x/2; j++){// pad id 700--719
    y[0] = y_start;
    y[1] = y[0];
    y[2] = y[1] + std::sqrt(3.)/2.*a;
    y[3] = y[2];
    x[0] = x_start - a + 3.*a*j;
    x[1] = x[0] + 2.*a;
    x[2] = x[1] - a/2.;
    x[3] = x[2] - a;
    for(int k=0; k<4; k++) x[k] = x_direction*x[k];
    for(int k=0; k<4; k++) y[k] = y_direction*y[k];
    this->AddBin(4, x, y);
  }
  
  for(int i=0; i<n_pad_y/2; i++){    
    for(int j=0; j<n_pad_x/2; j++){
      if(j != n_pad_x/2-1){
	y[0] = y_start + std::sqrt(3.)/2.*a + std::sqrt(3.)*a*i;
	y[1] = y[0] - std::sqrt(3.)/2.*a;
	y[2] = y[1];
	y[3] = y[0];
	y[4] = y[0] + std::sqrt(3.)/2.*a;
	y[5] = y[4];
	x[0] = x_start + a/2. + 3.*a*j;
	x[1] = x[0] + a/2.;
	x[2] = x[1] + a;
	x[3] = x[2] + a/2.;
	x[4] = x[2];
	x[5] = x[1];
	for(int k=0; k<6; k++) x[k] = x_direction*x[k];
	for(int k=0; k<6; k++) y[k] = y_direction*y[k];
	this->AddBin(6, x, y);
      }
      else if(j == n_pad_x/2-1){
	y[0] = y_start + std::sqrt(3.)/2.*a + std::sqrt(3.)*a*i;
	y[1] = y[0] - std::sqrt(3.)/2.*a;
	y[2] = y[1];
	y[3] = y[2] + std::sqrt(3.)*a;
	y[4] = y[3];
	x[0] = x_start + a/2. + 3.*a*j;
	x[1] = x[0] + a/2.;
	x[2] = x[1] + a/3.;
	x[3] = x[2];
	x[4] = x[3] - a/3.;
	for(int k=0; k<5; k++) x[k] = x_direction*x[k];
	for(int k=0; k<5; k++) y[k] = y_direction*y[k];
	this->AddBin(5, x, y);
      }
    }

    if( i != n_pad_y/2 - 1){
      for(int j=0; j<n_pad_x/2; j++){
	y[0] = y_start + std::sqrt(3.)*a + std::sqrt(3.)*a*i;
	y[1] = y[0] - std::sqrt(3.)/2.*a;
	y[2] = y[1];
	y[3] = y[0];
	y[4] = y[0] + std::sqrt(3.)/2.*a;
	y[5] = y[4];
	x[0] = x_start - a + 3.*a*j;
	x[1] = x[0] + a/2.;
	x[2] = x[1] + a;
	x[3] = x[2] + a/2.;
	x[4] = x[2];
	x[5] = x[1];
	for(int k=0; k<6; k++) x[k] = x_direction*x[k];
	for(int k=0; k<6; k++) y[k] = y_direction*y[k];
	this->AddBin(6, x, y);
      }
    }
  }
  
  for(int j=0; j<n_pad_x/2; j++){
    y[0] = y_start + std::sqrt(3.)*a*n_pad_y/2;
    y[1] = y[0] - std::sqrt(3.)/2.*a;
    y[2] = y[1];
    y[3] = y[0];
    x[0] = x_start - a + 3.*a*j;
    x[1] = x[0] + a/2.;
    x[2] = x[1] + a;
    x[3] = x[2] + a/2.;
    for(int k=0; k<4; k++) x[k] = x_direction*x[k];
    for(int k=0; k<4; k++) y[k] = y_direction*y[k];
    this->AddBin(4, x, y);
  }  
  //--- upper panel ---//
  
}//SetHBDHexBin()

Int_t E16ANA_HBDTH2Hex::Fill(Double_t x, Double_t y, Double_t weight)
{//x, y should be local coordinate
  double v[2] = {x, y};
  E16ANA_HBDGeometry::LocalToBoardCoordinate(module_id, v);
  
  if( IsXAxisNormal() || IsXAxisReverse() ){
    if( IsYAxisNormal() || IsYAxisReverse() ){
      return this->TH2Poly::Fill(x_direction*v[0], y_direction*v[1], weight);
    }
  }
  
  return 0;
}

int E16ANA_HBDTH2Hex::Fill(const int pad_id, const double weight)
{
  double cog[2];
  E16ANA_HBDGeometry::GetPadLocalCOG(module_id, pad_id, cog);
  this->Fill(cog[0], cog[1], weight);
  return 0;
}

int E16ANA_HBDTH2Hex::FindBin(const double x, const double y)
{//x, y should be local coordinate
  int pad = -1;
  double v[2] = {x, y};
  E16ANA_HBDGeometry::LocalToBoardCoordinate(module_id, v);
  
  if( IsXAxisNormal() || IsXAxisReverse() ){
    if( IsYAxisNormal() || IsYAxisReverse() ){
      pad = this->TH2Poly::FindBin(x_direction*v[0], y_direction*v[1]) - 1;
      //TH2Poly returns bin number which starts with 1, thus pad ID can get by bin number -1 
    }
  }
  
  if( pad < 0 || pad > E16DST_Constant::NPadsHBD-1 ){
    pad = -1;
  }
  
  return pad; 
}

void E16ANA_HBDTH2Hex::DrawWLocalCoordinate(char *option)
{
  this->Draw(option);

  this->GetXaxis()->SetLabelOffset(999);
  this->GetXaxis()->SetTickLength(0);
  gPad->Update();
  TGaxis *newxaxis = new TGaxis(gPad->GetUxmax(),
                                gPad->GetUymin(),
                                gPad->GetUxmin(),
                                gPad->GetUymin(),
                                -(gPad->GetUxmax()-gPad->GetUxmin())/2.,
				(gPad->GetUxmax()-gPad->GetUxmin())/2.,
				510, "-");
  newxaxis->SetLabelOffset(-0.03);
  newxaxis->SetTitle("local X [mm]");
  newxaxis->Draw();
  
  this->GetYaxis()->SetLabelOffset(999);
  this->GetYaxis()->SetTickLength(0);
  gPad->Update();
  TGaxis *newyaxis = new TGaxis(gPad->GetUxmin(),
                                gPad->GetUymin(),
                                gPad->GetUxmin()-0.001,
                                gPad->GetUymax(),
                                -(gPad->GetUymax()-gPad->GetUymin())/2.,
				(gPad->GetUymax()-gPad->GetUymin())/2.,
                                510, "+");
  newyaxis->SetLabelOffset(0.07);
  newyaxis->SetTitle("local Y [mm]");
  newyaxis->Draw();
}
