#include <iostream>
#include "TCanvas.h"
#include "STS/E16ANA_STSEventDisplay.hh"
#include "STS/E16ANA_STSGeometry.hh"
#include "E16ANA_STSGlobalGeometry.hh"
#include "TLine.h"

E16ANA_STSEventDisplay::E16ANA_STSEventDisplay(const std::string canv_name):_canv_name(canv_name),_mirror(false),color_hit(kRed),_pdf_name("out.pdf"){
  _canv = new TCanvas(_canv_name.c_str(),_canv_name.c_str(),800,820);
}

void E16ANA_STSEventDisplay::DrawSensor(){
  auto* lgeom = E16ANA_STSGeometry::instance();
  auto* ggeom = E16ANA_STSGlobalGeometry::instance();

  std::vector<int> modules{101,102,103,104,106,107,108,109};
  _canv->Clear();
  _canv->DrawFrame(-200,-200,200,200);
  TLine line;

  for (auto& mod : modules ) {
    double local1[3] = {-30,0,0};
    double local2[3] = {30,0,0};
    double global1[3] = {0,0,0};
    double global2[3] = {0,0,0};
    ggeom->Local2Global(mod,local1,global1);
    ggeom->Local2Global(mod,local2,global2);
    
    //std::cout << global1[0] << "," << global1[2] << std::endl;
    //std::cout << global2[0] << "," << global2[2] << std::endl;
    line.DrawLine(global1[0],global1[2],global2[0],global2[2]);
  }
}

void E16ANA_STSEventDisplay::DrawHit(double* pos){
  DrawHit(pos[0],pos[1],pos[2]);
}

void E16ANA_STSEventDisplay::DrawHit(double x, double y, double z){
  if ( _mirror ) x = -x;
  TLine line;
  double size = 4;
  line.SetLineColor(color_hit);
  // xz
  line.DrawLine(x-size,z-size, x+size,z+size);
  line.DrawLine(x+size,z-size, x-size,z+size);
}

void E16ANA_STSEventDisplay::DrawUpdate(){
  _canv->Draw();
  _canv->Update();
}

void E16ANA_STSEventDisplay::SetPdfName(std::string name){
  _pdf_name = name;
}

void E16ANA_STSEventDisplay::SavePdfStart(){
  _canv->Print((_pdf_name+"[").c_str());
}

void E16ANA_STSEventDisplay::SavePdf(){
  _canv->Print((_pdf_name).c_str());
}

void E16ANA_STSEventDisplay::SavePdfEnd(){
  _canv->Print((_pdf_name+"]").c_str());
}
