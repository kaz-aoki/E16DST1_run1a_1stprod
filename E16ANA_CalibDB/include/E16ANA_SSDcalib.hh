//2021-08-11, uploaded by yokkaich
//E16ANA_SSDcalib.hh 210808 by S. Yokkaichi
//    Last modified at <2021-08-11 19:35:12 >
//


#ifndef E16ANA_SSDcalib_HH
#define E16ANA_SSDcalib_HH

#include <string>

class E16ANA_SSDcalibTimeConstant{
private:
  double tdcTimeGain;
  double tdcOffset;
  bool ReadConstantDataCore(int runID, std::string indexfilename);
public:
  bool ReadConstantData(int runID);
  bool ReadConstantDataByLocal(int runID, std::string indexfilename);
  //read constants from file to tdcTimeGain & tdcOffset

  double TDCtimeGain(){return tdcTimeGain;}
  double TDCoffset(){return tdcOffset;}
};


class E16ANA_SSDcalibPedestal{
private:
  double pedestal[6][3][128][8];
  double sigma[6][3][128][8];
  //apvmodule[0-5], apvchip[0-2], strip[0-127], sample[0-7] ped/sigma
  static const int datasize = 6*3*128*8;
  bool ReadCalibDataCore(FILE* ifp);

public:
  bool ReadCalibData(int runID);
  bool ReadCalibDataByLocal(std::string localcalibfilename);

  bool WriteCalibData(std::string filename, 
    double**** wpedestal, double**** wsigma);

  double Pedestal(int module, int apv, int strip, int sample){
    return pedestal[module][apv][strip][sample];
  }
  double Sigma(int module, int apv, int strip, int sample){
    return sigma[module][apv][strip][sample];
  }

};





#endif// E16ANA_SSDcalib_HH

