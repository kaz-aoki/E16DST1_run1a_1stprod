/***********************************************************************************
#
# class E16ANA_STSLocalEventDisplay
# K.Aoki
# 
# event display of E16-STS. 2D only.
# Sensor strip view
#
# instance of E16ANA_STSLocalEventDisplay will create a TCanvas and have it inside.
#
#
# DrawSensor() : draw sensor sensitive area.
# DrawStrip(int pn, int istrip): Draw a strip
# DrawStripD(int pn, double strip)
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

#ifndef __E16ANA_STSLocalEventDisplay_h_
#define __E16ANA_STSLocalEventDisplay_h_

#include <string>
#include "TCanvas.h"

class E16ANA_STSLocalEventDisplay{
public:
  
  E16ANA_STSLocalEventDisplay(const std::string canv_name = "c1");
  void DrawSensor();
  void DrawStrip(int pn, int istrip);
  
  
  void DrawHit(double* pos);
  void DrawHit(double x, double y, double z);
  void DrawUpdate();
  void SetPdfName(std::string name);
  void SavePdfStart();
  void SavePdf();
  void SavePdfEnd();
  void SetMirror() { _mirror = true; }
  void SetNoMirror() { _mirror = false; }
  void SetHitColor(Color_t color) { color_hit = color; }
  void SetLineColor(Color_t color) { color_line = color;}
  
 private:
  TCanvas* _canv = nullptr;
  std::string _canv_name;
  std::string _pdf_name;
  bool _mirror;
  Color_t color_hit;
  Color_t color_line;
};

#endif


