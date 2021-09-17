#ifndef E16ANA_LGWaveform_h
#define E16ANA_LGWaveform_h

#include <vector>
#include "E16DST_DST0.hh"
#include "E16DST_Constant.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1Constant.hh"
#include "E16ANA_LGConstant.hh"
#include <unordered_map>
#include <iostream>
#include <set>
#include <TGraph.h>
using namespace std;



class E16ANA_LGWaveform
{

public:

E16ANA_LGWaveform(){};
~E16ANA_LGWaveform(){};

void Peak(double* dat, double* peak, int* peakx, double* timing);
void Baseline(double* dat, int peakx, double* baseline, double* baselinerms);
void Integral(double* dat, int peakx, double baseline, double* integral, int* falltime);
int PeakSearch(double* dat, double t0, double* mwf, double* peakxs, double* peakys);

void SetTemplate();
double Template1(double* x, double* par);
double Template2(double* x, double* par);
double Template3(double* x, double* par);
int Fit(double* dat, double* mwf, int npeaks, double* peakxs, double* peakys);

protected:

private:

  //double wf[E16DST_Constant::NSamplesLG];
TGraph* gtmpl;

};



#endif //E16ANA_LGWaveform_h
