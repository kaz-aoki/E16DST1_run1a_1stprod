//2021-08-11, uploaded by yokkaich
//calibSample.cc 210709 by S. Yokkaichi
//    Last modified at <2021-08-11 19:36:11 >
//

#include <iostream>
#include <fstream>
#include <string>

#include "E16ANA_ErrorMessage.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_SSDcalib.hh"

using namespace std;

//===========================================
void  SSD_CalibUsageSample(){
  E16MESSAGE("start");
  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();

  E16ANA_SSDcalibTimeConstant ssdtime;
  ssdtime.ReadConstantData( calib.CurrentRunID() );
  
  cerr<<"runID,tgain,toff="<<calib.CurrentRunID() <<" ";
  cerr<< ssdtime.TDCtimeGain() <<" "<<ssdtime.TDCoffset() <<endl;

  ssdtime.ReadConstantDataByLocal(99999, "localSSDtimeConst.txt"  );
  cerr<<"runID,tgain,toff="<<99999 <<" ";
  cerr<< ssdtime.TDCtimeGain() <<" "<<ssdtime.TDCoffset() <<endl;

  E16ANA_SSDcalibPedestal ssdped;
  //apvmodule[0-5], apvchip[0-2], strip[0-127], sample[0-7] ped/sigma

  double ped[6][3][128][8]={0};
  double sigma[6][3][128][8]={0};

    ped  [2][0][10][1]= 300.1;
    sigma[2][1][10][0]=  35.1;

  ssdped.WriteCalibData("localSSDpedestal.dat", 
    (double****)ped, (double****)sigma);

  ssdped.ReadCalibDataByLocal("localSSDpedestal.dat");
  for(int i=0;i<3;i++){
    cerr<< ssdped.Pedestal(2, i, 10, 0)<<" ";
    cerr<< ssdped.Sigma   (2, i, 10, 0)<<" ";
    cerr<< ssdped.Pedestal(2, i, 10, 1)<<" ";
    cerr<< ssdped.Sigma   (2, i, 10, 1)<<endl;
  }
  ssdped.ReadCalibData( 888888 );
  for(int i=0;i<3;i++){
    cerr<< ssdped.Pedestal(2, i, 10, 0)<<" ";
    cerr<< ssdped.Sigma   (2, i, 10, 0)<<" ";
    cerr<< ssdped.Pedestal(2, i, 10, 1)<<" ";
    cerr<< ssdped.Sigma   (2, i, 10, 1)<<endl;
  }

  //---------------------------------------------
  calib.CalibDBfileResetByLocal("./calib/","tempcalibDB.txt");

  bool flag1=ssdtime.ReadConstantData( calib.CurrentRunID() );
  if( !flag1 ){
    E16FATAL("ssd time read error");
    //    exit(1);
  }
  
  cerr<<"runID,tgain,toff="<<calib.CurrentRunID() <<" ";
  cerr<< ssdtime.TDCtimeGain() <<" "<<ssdtime.TDCoffset() <<endl;

  bool flag=ssdped.ReadCalibData( calib.CurrentRunID() );
  if( !flag ){
    E16FATAL("ssd calib read error");
    //    exit(1);
  }
  for(int i=0;i<3;i++){
    cerr<< ssdped.Pedestal(2, i, 10, 0)<<" ";
    cerr<< ssdped.Sigma   (2, i, 10, 0)<<" ";
    cerr<< ssdped.Pedestal(2, i, 10, 1)<<" ";
    cerr<< ssdped.Sigma   (2, i, 10, 1)<<endl;
  }

  //---------------------------------------------
  calib.CalibDBfileResetDefault();

  bool flag2=ssdped.ReadCalibData( calib.CurrentRunID() );
  if( !flag2 ){
    E16FATAL("ssd calib read error");
  }
  for(int i=0;i<3;i++){
    cerr<< ssdped.Pedestal(2, i, 10, 0)<<" ";
    cerr<< ssdped.Sigma   (2, i, 10, 0)<<" ";
    cerr<< ssdped.Pedestal(2, i, 10, 1)<<" ";
    cerr<< ssdped.Sigma   (2, i, 10, 1)<<endl;
  }


}


void  SSD_DST1Factory( E16ANA_SSDcalibTimeConstant& ssdtime,
  E16ANA_SSDcalibPedestal& ssdped){

  E16MESSAGE("start DST1Factory");

  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();

  cerr<<"runID,tgain,toff="<< calib.CurrentRunID()  <<" ";
  cerr<< ssdtime.TDCtimeGain() <<" "<<ssdtime.TDCoffset() <<endl;

  cerr<<"pedestal/sigma sample"<<endl;
  for(int i=0;i<3;i++){
    cerr<< ssdped.Pedestal(2, i, 10, 0)<<" ";
    cerr<< ssdped.Sigma   (2, i, 10, 0)<<" ";
    cerr<< ssdped.Pedestal(2, i, 10, 1)<<" ";
    cerr<< ssdped.Sigma   (2, i, 10, 1)<<endl;
  }

}

//===================================================
int main(int argc, char **argv){
  if( argc !=2 ){
    cerr<<"calibSample runID"<<endl;
    exit(1);
  }
  int runID = atoi(argv[1]);

  E16MESSAGE("start %s %d", argv[0], runID);

#if 0
  //logfile only record the INFO/FATAL message, for the production run
  char infoLogfilename[32];
  sprintf(infoLogfilename,"e16info-run%06d.log", runID);
  E16Message_SetLogFilename(infoLogfilename);
#endif

  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();

  //sample of run-by-run initialization
  calib.SetRunID(runID);
  E16ANA_SSDcalibTimeConstant ssdtime;
  ssdtime.ReadConstantData( calib.CurrentRunID() );
  E16ANA_SSDcalibPedestal ssdped;
  ssdped.ReadCalibData( calib.CurrentRunID() );


  //sample of event-by-event usage of initialized calibration data
  SSD_DST1Factory(ssdtime, ssdped);

  //sample of CalibDBManager usage
  //make a pedestal file, using localfile, etc.
  SSD_CalibUsageSample();

  return 0;

}

