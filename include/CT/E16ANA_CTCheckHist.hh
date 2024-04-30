#ifndef E16ANA_CTCheckHist_h
#define E16ANA_CTCheckHist_h

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

#include "E16DST_Constant.hh"

class E16ANA_CTCheckHist{
private :

  static const int NMOD = 2;
  static const int NCH  = 32;

  static constexpr int blocklist[NMOD][NCH] = {
    {43,42,41,40,53,52,51,50,
     23,22,21,20,33,32,31,30,
     3, 2, 1, 0, 13,12,11,10,
     7, 6, 5, 4, -1,-1,-1,-1},
    {55,54,45,44,
     36,35,26,25,
     15,14,5, 4, 
     3, 2, 1, 0,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
  };


public :
  E16ANA_CTCheckHist();
  ~E16ANA_CTCheckHist();

  static int  GetNMOD(){return NMOD;}
  static int  GetNCH(){return NCH;}
  static bool IsValidModuleId(int module);
  static bool IsValidBlockId(int module, int block);
  static int  ModuleToIndex(int module);
  static int  BlockToIndex(int module, int block);
  static int  IndexToModule(int index);
  static int  IndexToBlock(int index_m, int index_b);
  static bool LGwCT(int lgmodule, int lgblock);
  static int  LGToCT0Module(int lgmodule);
  static int  LGToCT0Block(int lgmodule, int lgblock);
  static int  LGToCT1Module(int lgmodule);
  static int  LGToCT1Block(int lgmodule, int lgblock);
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
  void DrawEachHist(TString& fpdf, TCanvas* c, TH1F* h[NMOD][NCH]);
  void Draw(TString& fpdf, TCanvas* c);
  void DrawPeak(TString& fpdf, TCanvas* c);
  void DrawPeakTime(TString& fpdf, TCanvas* c);
  void DrawTiming(TString& fpdf, TCanvas* c);
  void DrawBaseline(TString& fpdf, TCanvas* c);
  void DrawBaselineRms(TString& fpdf, TCanvas* c);
  void DrawIntegral(TString& fpdf, TCanvas* c);
  void DrawNhits(TString& fpdf, TCanvas* c);
  void DrawGraph(TString& fpdf, TCanvas* c, char* name, TH1F* h[NMOD][NCH], TGraph* g[NMOD]);
  void Draw2D(TString& fpdf, TCanvas* c);
  void Draw2DPeak(TString& fpdf, TCanvas* c);
  void Draw2DPeakTime(TString& fpdf, TCanvas* c);
  void Draw2DTiming(TString& fpdf, TCanvas* c);
  void Draw2DBaseline(TString& fpdf, TCanvas* c);
  void Draw2DBaselineRms(TString& fpdf, TCanvas* c);
  void Draw2DIntegral(TString& fpdf, TCanvas* c);
  void Draw2DNhits(TString& fpdf, TCanvas* c);
  void Draw2DHist(TString& fpdf, TCanvas* c, char* name, TH1F* h[NMOD][NCH], TH2F* hh[NMOD]);
  // void MakeT0CalibFile();
  void SetWaveform(int module, int block, double waveform[E16DST_Constant::NSamplesCT]);
  void DrawWaveform(TString& fpdf);

  TH1F* hpeak[NMOD][NCH];
  TH1F* hpeaktime[NMOD][NCH];
  TH1F* htiming[NMOD][NCH];
  TH1F* hbaseline[NMOD][NCH];
  TH1F* hbaselinerms[NMOD][NCH];
  TH1F* hintegral[NMOD][NCH];
  TH1F* hnhits[NMOD][NCH];
  TGraph* gpeak[NMOD];
  TGraph* gpeaktime[NMOD];
  TGraph* gtiming[NMOD];
  TGraph* gbaseline[NMOD];
  TGraph* gbaselinerms[NMOD];
  TGraph* gintegral[NMOD];
  TGraph* gnhits[NMOD];
  TH2F* hhpeak[NMOD];
  TH2F* hhpeaktime[NMOD];
  TH2F* hhtiming[NMOD];
  TH2F* hhbaseline[NMOD];
  TH2F* hhbaselinerms[NMOD];
  TH2F* hhintegral[NMOD];
  TH2F* hhnhits[NMOD];

  TH2F* htimcor[NMOD][NCH];// WF vs Trg timing

  TF1* ftiming[NMOD][NCH];

  int wfcount[NMOD][NCH];
  double wf[NMOD][NCH][3][E16DST_Constant::NSamplesCT];
};
#endif
