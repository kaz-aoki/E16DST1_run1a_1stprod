#ifndef E16ANA_LGWaveform_h
#define E16ANA_LGWaveform_h

#include "E16DST_DST0.hh"
#include "E16DST_Constant.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1Constant.hh"
#include "E16ANA_LGConstant.hh"
#include "E16ANA_LGBasic.hh"
#include <set>
#include <TGraph.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1.h>


class E16ANA_LGWaveform : E16ANA_LGBasic
{

public:

  E16ANA_LGWaveform();
    ~E16ANA_LGWaveform(){}

  //conventional method
  void SimpleMethod(double* _wf);
  void SetWaveform(double* _wf){
    for(int i=0;i<E16DST_Constant::NSamplesLG;i++){
      wf[i] = _wf[i];
    }
  }
  void CalcPeak();//and peakx
  void CalcTiming();
  void CalcBaseline();//and baselinerms
  void CalcIntegral();//and falltime
  double GetPeak(){return peak;}
  int GetPeakx(){return peakx;}
  double GetTiming(){return timing;}
  double GetBaseline(){return baseline;}
  double GetBaselineRms(){return baselinerms;}
  double GetIntegral(){return integral;}
  int GetFalltime(){return falltime;}
  bool GetSpikeFlag(){return spikeflag;}

  // void MethodForTrack(double* _wf, double t0);
  int GetHitFlag(){return hitflag;}

  //fitting method
  void FitMethod(int someorall, double* _wf, double t0);// 0: only requied wf are fitted (default), 1: all wf are fitted
  void SetT0(double _t0){t0 = _t0;}
  void CalcWaveforms();
  //void CalcPeaks();
  void PeakSearch();
  void Fit();
  void AllFit();
  bool BaselineCorrect();
  void CalcOffset();
  int PeakSearchFull(double* pxs, double* ps);
  int PeakSearchShort(double* pxs, double* ps);
  int FitTmpl1(double* pxs, double* ps);
  int FitTmpl2(double* pxs, double* ps);
  int FitTmpl3(double* pxs, double* ps);
  int Fit(double* pxs, double* ps);
  void DrawWf();
  int GetNpsFull(){return nps_full;}
  int GetNpsShort(){return nps_short;}
  int GetNpsFit(){return nps_fit;}
  int GetNpeaks(){return npeaks;}
  int GetFitOK(){return fitOK;}
  double* GetPeaks(){return peaks;}
  double* GetPeakxs(){return peakxs;}
  double* GetWidths(){return widths;}
  double* GetTimings(){return timings;}
  double* GetChi2s(){return chi2s;}

//  void SetTemplate();
  static double Template1(double* x, double* par);
  static double Template2(double* x, double* par);
  static double Template3(double* x, double* par);

  //other
  double celltons(double _cell){return _cell/E16ANA_LGConstant::kTimeScale;}
  double nstocell(double _ns){return _ns*E16ANA_LGConstant::kTimeScale;}
  static void RemoveSpike(double* dat); // for waveform w/o wftype-correction

  //old method
  void Peak(double* dat, double* peak, int* peakx, double* timing);
  void Baseline(double* dat, int peakx, double* baseline, double* baselinerms);
  void Integral(double* dat, int peakx, double baseline, double* integral, int* falltime);
  int PeakSearch(double* dat, double t0, double* mwf, double* peakxs, double* peakys);


protected:

private:

  double wf[E16DST_Constant::NSamplesLG];
  double t0;
  double peak;
  int peakx;
  double timing;
  double baseline;
  double baselinerms;
  double integral;
  int falltime;
  bool spikeflag;

  int hitflag;

  double dwf[E16DST_Constant::NSamplesLG]; //diff
  double mwf[E16DST_Constant::NSamplesLG]; //modified waveform (remove spike noise)
  double offset;
  int pxmin;
  int pxmax;
  int nps_full; //Npeaks: peak_search in full range of waveform
  double ps_full[30];//peaks
  double pxs_full[30];//peakxs
  int nps_short; //Npeaks: peak_search in short range of waveform (around trigger timing)
  double ps_short[30];
  double pxs_short[30];
  int nps_fit; //Npeaks: fit result
  double ps_fit[30];
  double pxs_fit[30];
  int npeaks;// final value
  int fitOK;// 0: not performed fitting, 1: fit OK, 2: fit failed
  double peaks[30];
  double peakxs[30];
  double widths[30];
  double timings[30];
  double chi2s[30];


  TH1F* hwf;
//  static TGraph* gtmpl;

  //for check
  static int n_call;
  static int n_fit0;
  static int n_fit1[3];
  static int n_fit2[3];
  static int n_fit3[3];
  static int n_fit4;

TString outfit0 = "tmpltest/outfit0.pdf";
TString outfit1suc = "tmpltest/outfit1suc.pdf";
TString outfit1fail = "tmpltest/outfit1fail.pdf";
TString outfit2suc = "tmpltest/outfit2suc.pdf";
TString outfit2fail = "tmpltest/outfit2fail.pdf";
TString outfit3suc = "tmpltest/outfit3suc.pdf";
TString outfit3fail = "tmpltest/outfit3fail.pdf";
TCanvas *c0[100];
TCanvas *c1s[100];
TCanvas *c1f[100];
TCanvas *c2s[50];
TCanvas *c2f[30];
TCanvas *c3s[100];
TCanvas *c3f[100];



};

#endif //E16ANA_LGWaveform_h
