#ifndef E16ANA_LGWaveform_h
#define E16ANA_LGWaveform_h

#include "E16DST_DST0.hh"
#include "E16DST_Constant.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1Constant.hh"
#include "E16ANA_LGConstant.hh"
#include <set>
#include <TGraph.h>
#include <TH1.h>


class E16ANA_LGWaveform
{

public:

  /*
  E16ANA_LGWaveform()
    : peak(E16DST_DST1Constant::kInvalidValue),
      peakx(E16DST_DST1Constant::kInvalidValue),
      timing(E16DST_DST1Constant::kInvalidValue),
      baseline(E16DST_DST1Constant::kInvalidValue),
      baselinerms(E16DST_DST1Constant::kInvalidValue),
      integral(E16DST_DST1Constant::kInvalidValue),
      falltime(E16DST_DST1Constant::kInvalidValue),
      offset(E16DST_DST1Constant::kInvalidValue),
      nps_full(E16DST_DST1Constant::kInvalidValue),
      nps_short(E16DST_DST1Constant::kInvalidValue),
      nps_fit(E16DST_DST1Constant::kInvalidValue) {

    for(int i=0;i<E16DST_Constant::NSamplesLG;i++){
      wf[i] = E16DST_DST1Constant::kInvalidValue;
      dwf[i] = E16DST_DST1Constant::kInvalidValue;
      mwf[i] = E16DST_DST1Constant::kInvalidValue;
      hwf = new TH1F("hwf","hwf",200,0.5,200.5);
    }
    for(int i=0;i<30;i++){
      ps_full[i] = E16DST_DST1Constant::kInvalidValue;
      pxs_full[i] = E16DST_DST1Constant::kInvalidValue;
      ps_short[i] = E16DST_DST1Constant::kInvalidValue;
      pxs_short[i] = E16DST_DST1Constant::kInvalidValue;
      ps_fit[i] = E16DST_DST1Constant::kInvalidValue;
      pxs_fit[i] = E16DST_DST1Constant::kInvalidValue;
    }
  }
  */
  E16ANA_LGWaveform();
    ~E16ANA_LGWaveform(){}
  //~E16ANA_LGWaveform(){delete hwf;}


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

  //fitting method
  void FitMethod(double* _wf, double t0);
  void SetT0(double _t0){t0 = _t0;}
  void CalcWaveforms();
  void CalcPeaks();
  void CalcOffset();
  int PeakSearchFull(double* pxs, double* ps);
  int PeakSearchShort(double* pxs, double* ps);
  int Fit(double* pxs, double* ps);
  int GetNpeaks(){return nps_fit;}
  double* GetPeaks(){return ps_fit;}
  double* GetPeakxs(){return pxs_fit;}

  void SetTemplate();
  static double Template1(double* x, double* par);
  static double Template2(double* x, double* par);
  static double Template3(double* x, double* par);

  //other
  double celltons(double _cell){return _cell/E16ANA_LGConstant::kTimeScale;}
  double nstocell(double _ns){return _ns*E16ANA_LGConstant::kTimeScale;}


  //old method
  void Peak(double* dat, double* peak, int* peakx, double* timing);
  void Baseline(double* dat, int peakx, double* baseline, double* baselinerms);
  void Integral(double* dat, int peakx, double baseline, double* integral, int* falltime);
  int PeakSearch(double* dat, double t0, double* mwf, double* peakxs, double* peakys);
  int Fit(double* dat, double* mwf, int npeaks, double* peakxs, double* peakys);


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

  TH1F* hwf;
  static TGraph* gtmpl;

};

#endif //E16ANA_LGWaveform_h
