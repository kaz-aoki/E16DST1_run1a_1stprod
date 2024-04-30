#include <iostream>
#include "TCanvas.h"
#include "STS/E16ANA_EventDisplay.hh"
#include "STS/E16ANA_STSGeometry.hh"
#include "STS/E16ANA_STSGlobalGeometry.hh"
#include "TLine.h"
#include "TVector3.h"
#include "E16ANA_GeometryV2.hh"
#include "TLatex.h"

E16ANA_EventDisplay::E16ANA_EventDisplay(const std::string canv_name):_canv_name(canv_name),_mirror(false),color_hit(kRed),_pdf_name("out.pdf"){
  _canv = new TCanvas(_canv_name.c_str(),_canv_name.c_str(),800,820);
}

void E16ANA_EventDisplay::DrawSensor(){
  auto* lgeom = E16ANA_STSGeometry::instance();
  auto* ggeom = E16ANA_STSGlobalGeometry::instance();

  std::vector<int> modules{101,102,103,104,106,107,108,109};
  _canv->Clear();
  //_canv->DrawFrame(-200,-200,200,200); // STS
  //_canv->DrawFrame(-800,-800,800,800); // GTR
  _canv->DrawFrame(frame_xy[0],frame_xy[1],frame_xy[2],frame_xy[3]);
  TLine line;
  // STS
  for (auto mod : modules ) {
    double local1[3] = {-30,0,0};
    double local2[3] = {30,0,0};
    double global1[3] = {0,0,0};
    double global2[3] = {0,0,0};
    ggeom->Local2Global(mod,local1,global1);
    ggeom->Local2Global(mod,local2,global2);

    if (_mirror) line.DrawLine(-global1[0],global1[2],-global2[0],global2[2]);
    else line.DrawLine(global1[0],global1[2],global2[0],global2[2]);
  }
  //GTR
  for (auto mod: modules ) {
    std::vector<double> gtrsize{100,200,300};
    for( int i = 0;i<3;i++){
      TVector3 lpos1(-gtrsize[i]/2.,0.,0.);
      TVector3 lpos2(gtrsize[i]/2.,0,0);
      TVector3 gpos1 = geome16->GTR(G4modGTR(mod),i)->GetGPos(lpos1);
      TVector3 gpos2 = geome16->GTR(G4modGTR(mod),i)->GetGPos(lpos2);
      if (_mirror )    line.DrawLine(-gpos1.X(),gpos1.Z(),-gpos2.X(),gpos2.Z());
      else line.DrawLine(gpos1.X(),gpos1.Z(),gpos2.X(),gpos2.Z());
    }
  }
  // HBD
  for (auto mod: modules ) {
    TVector3 lpos1(-600/2.,0.,0.);
    TVector3 lpos2(600/2.,0,0);
    TVector3 gpos1 = geome16->HBD(G4modHBDLG(mod))->GetGPos(lpos1);
    TVector3 gpos2 = geome16->HBD(G4modHBDLG(mod))->GetGPos(lpos2);
    if (_mirror )    line.DrawLine(-gpos1.X(),gpos1.Z(),-gpos2.X(),gpos2.Z());
    else line.DrawLine(gpos1.X(),gpos1.Z(),gpos2.X(),gpos2.Z());
  }
  // LG
  for (auto mod: modules ) {
    TVector3 lpos(0.,0.,0.);
    TVector3 gpos1 = geome16->LG(G4modHBDLG(mod),20)->GetGPos(lpos);
    TVector3 gpos2 = geome16->LG(G4modHBDLG(mod),26)->GetGPos(lpos);
    if (_mirror) line.DrawLine(-gpos1.X(),gpos1.Z(),-gpos2.X(),gpos2.Z());
    else line.DrawLine(gpos1.X(),gpos1.Z(),gpos2.X(),gpos2.Z());
  }
}


void E16ANA_EventDisplay::DrawHit(const TVector3& pos){
  DrawHit(pos.X(),pos.Y(),pos.Z());
}

void E16ANA_EventDisplay::DrawHit(double* pos){
  DrawHit(pos[0],pos[1],pos[2]);
}

void E16ANA_EventDisplay::DrawHit(double x, double y, double z){
  if ( _mirror ) x = -x;
  TLine line;
  double size = 4;
  line.SetLineColor(color_hit);
  // xz
  line.DrawLine(x-size,z-size, x+size,z+size);
  line.DrawLine(x+size,z-size, x-size,z+size);
}

void E16ANA_EventDisplay::DrawUpdate(){
  _canv->Draw();
  _canv->Update();
}

void E16ANA_EventDisplay::SetPdfName(std::string name){
  _pdf_name = name;
}

void E16ANA_EventDisplay::SavePdfStart(){
  _canv->Print((_pdf_name+"[").c_str());
}

void E16ANA_EventDisplay::SavePdf(){
  _canv->Print((_pdf_name).c_str());
}

void E16ANA_EventDisplay::SavePdfEnd(){
  _canv->Print((_pdf_name+"]").c_str());
}

void E16ANA_EventDisplay::DrawLine(double *pos1,double *pos2){
  double pos1_x = pos1[0];
  double pos2_x = pos2[0];
  if ( _mirror ) {
    pos1_x = -pos1_x;
    pos2_x = -pos2_x;
  }
  TLine line;
  line.SetLineColor(color_line);
  line.DrawLine(pos1_x,pos1[2],pos2_x,pos2[2]);
  line.DrawLine(pos1_x,pos1[2],pos2_x,pos2[2]);
}

void E16ANA_EventDisplay::Clear(){
  _canv->Clear();
}

void E16ANA_EventDisplay::DrawLatex(double x, double y, TString str){
  TLatex latex;
  latex.DrawLatex(x,y,str);
}

void E16ANA_EventDisplay::DrawTargets(){
  TLine line;
  SetLineColor(kBlue);
  line.DrawLine(-10.,  0., 10.,  0.);
  line.DrawLine(-10., 20., 10., 20.);
  line.DrawLine(-10.,-20., 10.,-20.);
}

void E16ANA_EventDisplay::DrawWires(){
  double wires[4][3] = {
    { 20., 0.,  40.},
    { 20., 0., -40.},
    {-20., 0., -40.},
    {-20., 0.,  40.}
  };
  for(int i = 0;i<4;i++) DrawHit(wires[i]);
}

void E16ANA_EventDisplay::DrawRun(int run_id){
  TLatex latex;
  TString str;
  str.Form("Run %d",run_id);
  latex.DrawLatexNDC(0.1,0.9,str);
}

void E16ANA_EventDisplay::DrawEvent(int event_id){
  TLatex latex;
  TString str;
  str.Form("Event %d",event_id);
  latex.DrawLatexNDC(0.1,0.85,str);
}


void E16ANA_EventDisplay::DrawBox(double *pos1,double *pos2){
  double pos1_x = pos1[0];
  double pos2_x = pos2[0];
  if ( _mirror ) {
    pos1_x = -pos1_x;
    pos2_x = -pos2_x;
  }
  double pos1_y = pos1[2];
  double pos2_y = pos2[2];
  
  TLine line;
  SetLineColor(kRed);
  line.DrawLine(pos1_x,pos1_y,pos1_x,pos2_y);
  line.DrawLine(pos1_x,pos2_y,pos2_x,pos2_y);
  line.DrawLine(pos2_x,pos2_y,pos2_x,pos1_y);
  line.DrawLine(pos2_x,pos1_y,pos1_x,pos1_y);
}

void E16ANA_EventDisplay::DrawLGHitBox(int module,int block){
  auto lg = geome16->LG(G4modHBDLG(module),block);
  constexpr double lg_width = 122.;
  constexpr double lg_depth = 135.;
  TVector3 local1(-lg_width/2.,0.,0);
  TVector3 local2(+lg_width/2.,0.,0);
  TVector3 local3(+lg_width/2.,0.,lg_depth);
  TVector3 local4(-lg_width/2.,0.,lg_depth);

  TVector3 gpos1 = lg->GetGPos(local1);
  TVector3 gpos2 = lg->GetGPos(local2);
  TVector3 gpos3 = lg->GetGPos(local3);
  TVector3 gpos4 = lg->GetGPos(local4);
  
  double global1[3] = { gpos1.X(), gpos1.Y(), gpos1.Z() };
  double global2[3] = { gpos2.X(), gpos2.Y(), gpos2.Z() };
  double global3[3] = { gpos3.X(), gpos3.Y(), gpos3.Z() };
  double global4[3] = { gpos4.X(), gpos4.Y(), gpos4.Z() };
  SetLineColor(color_hit);
  DrawLine(global1,global2);
  DrawLine(global2,global3);
  DrawLine(global3,global4);
  DrawLine(global4,global1);
}
