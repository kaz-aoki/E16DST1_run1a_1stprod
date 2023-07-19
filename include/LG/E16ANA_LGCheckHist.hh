#ifndef E16ANA_LGCheckHist_h
#define E16ANA_LGCheckHist_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TF1.h>

#include <stdio.h>
#include <iostream>

class E16ANA_LGCheckHist{
private :

public :
  E16ANA_LGCheckHist();
  ~E16ANA_LGCheckHist();

  static bool IsValidModuleId(int module);
  static bool IsValidBlockId(int block);
  static int  ModuleToIndex(int module);
  static int  BlockToIndex(int block);
  static int  IndexToModule(int index);
  static int  IndexToBlock(int index);
  void Fill(int module, int block, double peak, int peaktime, double timing, double baseline, double baselinerms, double integral, int nhits);
  void FillPeak(int module, int block, double peak);
  void FillPeakTime(int module, int block, int peaktime);
  void FillTiming(int module, int block, double timing);
  void FillBaseline(int module, int block, double baseline);
  void FillBaselineRms(int module, int block, double baselinerms);
  void FillIntegral(int module, int block, double integral);
  void FillNhits(int module, int block, bool nhits);
  void FillTimeCorrelation(int module, int block, int peaktime, int trgtiming);
  void DrawEach(TString& fpdf, TCanvas* c);
  void DrawEachPeak(TString& fpdf, TCanvas* c);
  void DrawEachPeakTime(TString& fpdf, TCanvas* c);
  void DrawEachTiming(TString& fpdf, TCanvas* c);
  void DrawEachBaseline(TString& fpdf, TCanvas* c);
  void DrawEachBaselineRms(TString& fpdf, TCanvas* c);
  void DrawEachIntegral(TString& fpdf, TCanvas* c);
  void DrawEachNhits(TString& fpdf, TCanvas* c);
  void DrawEachTimeCorrelation(TString& fpdf, TCanvas* c);
  void DrawEachHist(TString& fpdf, TCanvas* c, TH1F* h[8][42]);
  void Draw(TString& fpdf, TCanvas* c);
  void DrawPeak(TString& fpdf, TCanvas* c);
  void DrawPeakTime(TString& fpdf, TCanvas* c);
  void DrawTiming(TString& fpdf, TCanvas* c);
  void DrawBaseline(TString& fpdf, TCanvas* c);
  void DrawBaselineRms(TString& fpdf, TCanvas* c);
  void DrawIntegral(TString& fpdf, TCanvas* c);
  void DrawNhits(TString& fpdf, TCanvas* c);
  void DrawGraph(TString& fpdf, TCanvas* c, char* name, TH1F* h[8][42], TGraph* g[8]);
  void Draw2D(TString& fpdf, TCanvas* c);
  void Draw2DPeak(TString& fpdf, TCanvas* c);
  void Draw2DPeakTime(TString& fpdf, TCanvas* c);
  void Draw2DTiming(TString& fpdf, TCanvas* c);
  void Draw2DBaseline(TString& fpdf, TCanvas* c);
  void Draw2DBaselineRms(TString& fpdf, TCanvas* c);
  void Draw2DIntegral(TString& fpdf, TCanvas* c);
  void Draw2DNhits(TString& fpdf, TCanvas* c);
  void Draw2DHist(TString& fpdf, TCanvas* c, char* name, TH1F* h[8][42], TH2F* hh[8]);
  void MakeT0CalibFile();
  void SetWaveform(int module, int block, double waveform[200]);
  void DrawWaveform(TString& fpdf);

  TH1F* hpeak[8][42];
  TH1F* hpeaktime[8][42];
  TH1F* htiming[8][42];
  TH1F* hbaseline[8][42];
  TH1F* hbaselinerms[8][42];
  TH1F* hintegral[8][42];
  TH1F* hnhits[8][42];
  TGraph* gpeak[8];
  TGraph* gpeaktime[8];
  TGraph* gtiming[8];
  TGraph* gbaseline[8];
  TGraph* gbaselinerms[8];
  TGraph* gintegral[8];
  TGraph* gnhits[8];
  TH2F* hhpeak[8];
  TH2F* hhpeaktime[8];
  TH2F* hhtiming[8];
  TH2F* hhbaseline[8];
  TH2F* hhbaselinerms[8];
  TH2F* hhintegral[8];
  TH2F* hhnhits[8];

  TH2F* htimcor[8][42];// WF vs Trg timing

  TF1* ftiming[8][42];

  int wfcount[8][42];
  double wf[8][42][3][200];
};
#endif
