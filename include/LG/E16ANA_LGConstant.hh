#ifndef E16ANA_LGCONSTANT_HH
#define E16ANA_LGCONSTANT_HH

#include <array>
#include <TGraph.h>

namespace E16ANA_LGConstant {

const double             kTimeScale               = 960. / 1000.;

const int kHitThreshold = 5;//[mV]
const int kHitTimingStart = 50;//[ns]
const int kHitTimingEnd = 150;//[ns]

const int kPeakSearchStart = 5;//[cell]
const int kPeakSearchEnd = 160;//[cell]
const int kTimingSearchRegion = 20;//[cell] before peaktime
const int kBaselineStart = -60;//[cell] +peaktime
const int kBaselineEnd = -10;//[cell] +peaktime
const int kIntegralStart = -10;//[cell] +peaktime
const int kIntegralEnd = 50;//[cell] +peaktime

  //const int kTPeakSearchRegion = 190;
  //const int kTPeakSearchStart = 5;
  //const int kTPeakSearchEnd = 195;


  /*
void SetTemplate(){

  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();
  FILE* fp_wf = calib.CalibFileOpenBinary("LG-WFtemplate", calib.CurrentRunID() );
  if ( fp_wf==NULL ) {
    std::cout<<"[Error] wf template file is not found !"<<std::endl;
    exit(1);
  }

  double xt, yt;
  std::vector<double> x;
  std::vector<double> y;
  while( feof(fp_wf)==0 ){
    fscanf(fp_wf, "%lf %lf", &xt, &yt );
    x.push_back(xt);
    y.push_back(yt);
  }

  gtmpl = new TGraph(110,&x[0],&y[0]);

  fclose(fp_wf);
}

double Template1(double* x, double* par){

  return (gtmpl->Eval((x[0]-par[0])*par[1]))*par[2]/140.+par[3];

}

TGraph* gtmpl;
  */

}; // namespace E16ANA_LGConstant

#endif
