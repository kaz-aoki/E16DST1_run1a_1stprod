#if defined(__CLING__) || defined(__ACLIC__)
#include "E16ANA_STSLocalEventDisplay.hh"
#include "E16ANA_STSGeometry.hh"
#else
#include "STS/E16ANA_STSLocalEventDisplay.hh"
#include "STS/E16ANA_STSGeometry.hh"
#endif

#include <iostream>
#include "TCanvas.h"
#include "TLine.h"
#include "TBox.h"

E16ANA_STSLocalEventDisplay::E16ANA_STSLocalEventDisplay(const std::string canv_name):_canv_name(canv_name),_mirror(false),color_hit(kRed),_pdf_name("out.pdf"){
  _canv = new TCanvas(_canv_name.c_str(),_canv_name.c_str(),800,820);
}

void E16ANA_STSLocalEventDisplay::DrawSensor(){
  auto* lgeom = E16ANA_STSGeometry::instance();

  std::vector<int> modules{101,102,103,104,106,107,108,109};
  _canv->Clear();
  _canv->DrawFrame(-40,-40,40,40);

  // Draw sensitive area.
  double dx = lgeom->halfDX_active;
  double dy = lgeom->halfDY_active;
  TBox box;
  box.DrawBox(-dx,-dy,dx,dy);
}


void E16ANA_STSLocalEventDisplay::DrawStrip(int pn, int istrip){
  auto* lgeom = E16ANA_STSGeometry::instance();
  if ( pn == 0 ) {
    // p-strip

    auto botref = lgeom->GetBotRef(istrip);  // std::pair<double,double>[O
    auto topref = lgeom->GetTopRef(istrip);
    TLine line;
    if (lgeom->IsNonZStrip(istrip)){
      // Non-Z-strip
      line.DrawLine(botref.first,botref.second,topref.first,topref.second);
    }else{
      // Zstrip
      double y = lgeom->CalcY(topref,-lgeom->halfDX_active);
      line.DrawLine(topref.first,topref.second,-lgeom->halfDX_active,y);
      y = lgeom->CalcY(botref,lgeom->halfDX_active);
      line.DrawLine(botref.first,botref.second,lgeom->halfDX_active,y);
      line.SetLineColor(kBlack);
      // use lgeom->p_phi or lgeom->p_tan_phi to calculate the end point of the strips.
      // then draw. Two lines if it is z-strip;
    }
    std::cout << "DrawStrip for p-side" << std::endl;
  }else if (pn == 1) {
    // n-strip
    TLine line;
    double x = lgeom->GetLocalX_fromN(istrip);
    double dy = lgeom->halfDY_active;
    line.DrawLine(x,-dy,x,dy);
  }
}

/*
void E16ANA_STSLocalEventDisplay::DrawStripD(int pn, double strip){
  auto* lgeom = E16ANA_STSGeometry::instance();
  if ( pn == 0 ) {
    // p-strip
    std::cout << "DrawStrip for p-side" << std::endl;
  }else if (pn == 1) {
    // n-strip
    TLine line;
    double x = lgeom->GetLocalX_fromN(strip);
    double dy = lgeom->halfDY_active;
    line.DrawLine(x,-dy,x,dy);
  }
}
*/


void E16ANA_STSLocalEventDisplay::DrawHit(double* pos){
  DrawHit(pos[0],pos[1],pos[2]);
}

void E16ANA_STSLocalEventDisplay::DrawHit(double x, double y, double z){
  if ( _mirror ) x = -x;
  TLine line;
  double size = 4;
  line.SetLineColor(color_hit);
  // xz
  line.DrawLine(x-size,z-size, x+size,z+size);
  line.DrawLine(x+size,z-size, x-size,z+size);
}

void E16ANA_STSLocalEventDisplay::DrawUpdate(){
  _canv->Draw();
  _canv->Update();
}

void E16ANA_STSLocalEventDisplay::SetPdfName(std::string name){
  _pdf_name = name;
}

void E16ANA_STSLocalEventDisplay::SavePdfStart(){
  _canv->Print((_pdf_name+"[").c_str());
}

void E16ANA_STSLocalEventDisplay::SavePdf(){
  _canv->Print((_pdf_name).c_str());
}

void E16ANA_STSLocalEventDisplay::SavePdfEnd(){
  _canv->Print((_pdf_name+"]").c_str());
}
