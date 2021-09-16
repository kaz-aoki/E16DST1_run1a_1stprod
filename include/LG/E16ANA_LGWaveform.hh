#ifndef E16ANA_LGWaveform_h
#define E16ANA_LGWaveform_h

#include <vector>
#include "E16DST_DST0.hh"
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
int PeakSearch(double* dat, double t0, double* peakxs, double* peakys);

protected:

private:

  //  TGraph* gtmpl;

};



#endif //E16ANA_LGWaveform_h
