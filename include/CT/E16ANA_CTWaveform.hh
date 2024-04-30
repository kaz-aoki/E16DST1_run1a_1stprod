#ifndef E16ANA_CTWaveform_h
#define E16ANA_CTWaveform_h

// #include "E16DST_DST0.hh"
#include "E16DST_Constant.hh"
// #include "E16ANA_CalibDBManager.hh"
// #include "E16DST_DST1Constant.hh"
#include "E16ANA_CTConstant.hh"
// #include "E16ANA_CTBasic.hh"
#include <set>

class E16ANA_CTWaveform //: E16ANA_CTBasic
{

public:

  E16ANA_CTWaveform();
    ~E16ANA_CTWaveform(){}

  //conventional method
  void SimpleMethod(double* _wf);
  void SetWaveform(double* _wf){
    for(int i=0;i<E16DST_Constant::NSamplesCT;i++){
      wf[i] = _wf[i];
    }
  }
  void CalcPeak();//and peakx
  void CalcTiming();
  void CalcBaseline();//and baselinerms
  void CalcIntegral();
  double GetPeak(){return peak;}
  int GetPeakx(){return peakx;}
  double GetTiming(){return timing;}
  double GetBaseline(){return baseline;}
  double GetBaselineRms(){return baselinerms;}
  double GetIntegral(){return integral;}

  //other
  double celltons(double _cell){return _cell/E16ANA_CTConstant::kTimeScale;}
  double nstocell(double _ns){return _ns*E16ANA_CTConstant::kTimeScale;}
  bool InvalidCell(int _cell){
    if(_cell<0||_cell>E16DST_Constant::NSamplesCT){
      return true;
    }
    else{
      return false;
    }
  }

protected:

private:

  double wf[E16DST_Constant::NSamplesCT];
  double peak;
  int peakx;
  double timing;
  double baseline;
  double baselinerms;
  double integral;

};

#endif //E16ANA_CTWaveform_h
