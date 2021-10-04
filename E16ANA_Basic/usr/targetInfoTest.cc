//2021-09-12, uploaded by yokkaich
//targetInfoTest.cc 210910 by S. Yokkaichi
//    Last modified at <2021-09-10 22:34:24 >

#include <iostream>
#include <fstream>
#include <string>
#include "E16ANA_ErrorMessage.hh"

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_TargetInfo.hh"
#include "E16ANA_SSDcalib.hh"

using namespace std;

int main(int argc, char **argv){
  E16INFO("start");

  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();

  int runID = 39999;
  calib.SetRunID(runID);








#if 1

  E16ANA_TargetInfoManager& targets=  E16ANA_TargetInfoManager::Instance();
  targets.ReadInfoWithRunID(runID);
  targets.Print();
  targets.ReadInfoWithRunID(30395);
  targets.Print();
  targets.ReadInfoWithRunID(30395);// test of runID-cache
  targets.Print();
  targets.ReadInfoWithRunID(30394);
                      //test of calibfilename-cache//not implemented yet
  targets.Print();
  targets.ReadInfoWithRunID(39999);
  double x1,x2,x3,z1,z2,z3;
  if( targets.IsWire() ){
    x1=targets.Info(0).Position().x();
    z1=targets.Info(0).Position().z();
    x2=targets.Info(1).Position().x();
    z2=targets.Info(1).Position().z();
    cerr<<"target z "<<z1<<" "<<z2<<endl;
  }
  else{
    cerr<<"position of T3 "<<targets.Info(2).Position()<<endl;
  }

#endif


  return 0;
}

