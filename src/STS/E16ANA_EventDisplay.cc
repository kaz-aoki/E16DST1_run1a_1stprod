#include <iostream>
#include "TCanvas.h"
#include "STS/E16ANA_EventDisplay.hh"
#include "STS/E16ANA_STSGeometry.hh"
#include "STS/E16ANA_STSGlobalGeometry.hh"
#include "TLine.h"
#include "TVector3.h"
#include "E16ANA_GeometryV2.hh"

E16ANA_EventDisplay::E16ANA_EventDisplay(const std::string canv_name):_canv_name(canv_name),_mirror(false),color_hit(kRed),_pdf_name("out.pdf"){
  _canv = new TCanvas(_canv_name.c_str(),_canv_name.c_str(),800,820);
}

void E16ANA_EventDisplay::DrawSensor(){
  auto* lgeom = E16ANA_STSGeometry::instance();
  auto* ggeom = E16ANA_STSGlobalGeometry::instance();

  std::vector<int> modules{101,102,103,104,106,107,108,109};
  _canv->Clear();
  //_canv->DrawFrame(-200,-200,200,200);
  _canv->DrawFrame(-800,-800,800,800);
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
    line.DrawLine(global1[0],global1[2],global2[0],global2[2]);
  }
  //GTR
  for (auto mod: modules ) {
    std::vector<double> gtrsize{100,200,300};
    for( int i = 0;i<3;i++){
      TVector3 lpos1(-gtrsize[i]/2.,0.,0.);
      TVector3 lpos2(gtrsize[i]/2.,0,0);
      TVector3 gpos1 = geome16->GTR(Gmod(mod),i)->GetGPos(lpos1);
      TVector3 gpos2 = geome16->GTR(Gmod(mod),i)->GetGPos(lpos2);
      if (_mirror )    line.DrawLine(-gpos1.X(),gpos1.Z(),-gpos2.X(),gpos2.Z());
      line.DrawLine(gpos1.X(),gpos1.Z(),gpos2.X(),gpos2.Z());
    }
  }
  return;
  // HBD
  for (auto mod: modules ) {
    TVector3 lpos1(-600/2.,0.,0.);
    TVector3 lpos2(600/2.,0,0);
    TVector3 gpos1 = geome16->HBD(Gmod(mod))->GetGPos(lpos1);
    TVector3 gpos2 = geome16->HBD(Gmod(mod))->GetGPos(lpos2);
    if (_mirror )    line.DrawLine(-gpos1.X(),gpos1.Z(),-gpos2.X(),gpos2.Z());
    line.DrawLine(gpos1.X(),gpos1.Z(),gpos2.X(),gpos2.Z());
  }
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
  line.SetLineColor(kBlue);
  line.DrawLine(pos1_x,pos1[2],pos2_x,pos2[2]);
  line.DrawLine(pos1_x,pos1[2],pos2_x,pos2[2]);
}
