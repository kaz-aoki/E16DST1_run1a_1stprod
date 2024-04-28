/***********************************************************************************
#
# class E16ANA_EventDisplay
# K.Aoki
# 
# event display of E16-STS. 2D only.
#
# instance of E16ANA_EventDisplay will create a TCanvas and have it inside.
#
# DrawSensor() : draw sensors themselves. 101-104,106-109 will be drawn. 2D.
#
# DrawHit(double* pos) : Draw Hit according to pos. (Global coordinate)
#
# SetMirror() / SetNoMirror() :
#   SetMirror will make x = -x.
#   Official x axis of E16 coordinate system is left in direction.
#   After doing SetMirror, the event display will look like you see the setup from above.
#
# SetHitColor() : Set the color to draw hits.
#
***********************************************************************************/


#ifndef __E16ANA_EventDisplay_h_
#define __E16ANA_EventDisplay_h_

#include <string>
class TCanvas;
class E16ANA_GeometryV2;
#include "E16DST_DST1Constant.hh"
class TString;

class E16ANA_EventDisplay{
public:
  
  E16ANA_EventDisplay(const std::string canv_name = "c1");
  void DrawSensor();
  void Clear();
  void DrawHit(double* pos);
  void DrawHit(double x, double y, double z);
  void DrawLine(double* pos1, double* pos2);
  void DrawLatex(double x, double y,TString str);
  void DrawTargets();
  void DrawWires();
  void DrawBox(double* pos1, double *pos2);
  void DrawLGBox(int module,int block);

  void DrawUpdate();
  void SetPdfName(std::string name);
  void SavePdfStart();
  void SavePdf();
  void SavePdfEnd();

  void SetMirror() { _mirror = true; }
  void SetNoMirror() { _mirror = false; }
  void SetHitColor(Color_t color) { color_hit = color; }
  void SetGeometry(E16ANA_GeometryV2* geom) { geome16 = geom;}

  int G4modGTR(int mid) {
    assert(mid >=0 && mid<=209);
    return E16DST_DST1Constant::kModuleId2020To2013[mid/100][mid%100];
  };

  int G4modHBDLG(int mid) {
    assert(mid >=0 && mid<=209);
    return E16DST_DST1Constant::kModuleId2020To2013[mid/100][(mid%100)+1];
  };

  void DrawRun(int run_id);
  void DrawEvent(int event_id);

 private:
  E16ANA_GeometryV2* geome16 {nullptr};
  TCanvas* _canv = nullptr;
  std::string _canv_name;
  std::string _pdf_name;
  bool _mirror;
  Color_t color_hit;
  
  double frame_xy[4]={-2000.,-2000.,2000.,2000.}; // frame for LG
};

#endif


