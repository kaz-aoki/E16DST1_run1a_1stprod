//2021-08-11, uploaded by yokkaich
//E16ANA_SSDcalib.cc 210808 by S. Yokkaichi
//    Last modified at <2021-08-11 20:33:31 >
//

#include <sstream>
#include <stdio.h>

#include "E16ANA_ErrorMessage.hh"
#include "E16ANA_SSDcalib.hh"
#include "E16ANA_CalibDBManager.hh"

using namespace std;

//============================================================
bool E16ANA_SSDcalibTimeConstant::ReadConstantData(int runID){
  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();

  string  indexfilename = calib.SearchForIndexFileName("SSD-time");
  //  string  indexfilename = calib.SearchForIndexFileName("SSD-bad");//test
  return ReadConstantDataCore(runID, indexfilename);
}

bool E16ANA_SSDcalibTimeConstant::ReadConstantDataByLocal(int runID, string indexfilename ){

  return ReadConstantDataCore(runID, indexfilename);
   
}
bool E16ANA_SSDcalibTimeConstant::ReadConstantDataCore(int runID, string indexfilename){
  //  modified from CalibDBManager::SearchIndexfileForCalibFileName()

  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();
  bool flag=true;
#if 0
  ifstream ifs (indexfilename, ios_base::in);
  if( ! ifs  ) {
    E16FATAL("file open error: %s", indexfilename.c_str() );
    return false;
  }
  E16INFO("constant file open: %s %d", indexfilename.c_str(), runID );
#else
  ifstream* ifsp = calib.CalibStreamOpenTextByLocalName( indexfilename );
#endif
  if( ifsp == NULL ){
    return false;
  }
  ifstream& ifs = *ifsp;

  map<int,string> map1= calib.ReadFileWithNumberKey( ifs );

  // key is sorted in "map"
  auto item1 = map1.lower_bound(runID);

  stringstream s;
  s << (string)item1->second;
  s>>tdcTimeGain;
  s>>tdcOffset;
  
  ifs.close();
  delete ifsp;

  return flag;

}




//============================================================
bool E16ANA_SSDcalibPedestal::ReadCalibDataByLocal(string filename){
  FILE* ifp = fopen( filename.c_str(), "rb"  );
  if( ifp != NULL){
    E16INFO("local file open: %s",filename.c_str() );
    return ReadCalibDataCore( ifp );
  }
  else{
    E16FATAL("file open error: %s", filename.c_str() );
    return false;
  }
}

bool E16ANA_SSDcalibPedestal::ReadCalibData(int runID){
  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();
  FILE* ifp= calib.CalibFileOpenBinary("SSD-pedestal", runID);
  if( ifp != NULL){
    return ReadCalibDataCore( ifp );
  }
  else{
    E16FATAL("file open error");
    return false;
   }
}


bool E16ANA_SSDcalibPedestal::ReadCalibDataCore(FILE* ifp){
    //ifp is already checked

//apvmodule[0-5], apvchip[0-2], strip[0-127], sample[0-7] ped/sigma
//const int datasize = 6*3*128*8;
//  cerr<<"size of pedestal "<<sizeof(pedestal)<<endl;
  bool flag=true;
  int flag1=fread(pedestal,  sizeof(double), datasize, ifp);
  int flag2=fread(sigma,     sizeof(double), datasize, ifp);
  if( flag1 != datasize || flag2 != datasize){
    E16FATAL("fread error: size=%8d, ped=%8d, sigma=%8d",
      datasize, flag1, flag2);
    flag=false;
  }

  fclose(ifp);
  return flag;
}

bool E16ANA_SSDcalibPedestal::WriteCalibData(string filename, 
  double*** wpedestal, double*** wsigma){

  FILE* ofp = fopen(filename.c_str(), "wb");
  bool flag=true;

  if( ofp == NULL){
    E16FATAL("output file open error: %s", filename.c_str() );
    return false;
  }
  else{
    E16INFO("local output file open: %s",filename.c_str() );
    int flag1=fwrite(wpedestal,  sizeof(double), datasize, ofp);
    int flag2=fwrite(wsigma,     sizeof(double), datasize, ofp);
    if( flag1 != datasize || flag2 != datasize){
      E16FATAL("fwrite error: size=%8d, ped=%8d, sigma=%8d",
	datasize, flag1, flag2);
      flag=false;
    }
  }

  fclose(ofp);
  return flag;
}
