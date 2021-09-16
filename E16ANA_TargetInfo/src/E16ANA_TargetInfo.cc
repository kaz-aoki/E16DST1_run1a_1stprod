//2021-09-12, uploaded by yokkaich
//E16ANA_TargetInfo.cc 210619 by S. Yokkaichi
//    Last modified at <2021-09-10 18:34:13 >


#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

#include "E16ANA_ErrorMessage.hh" 
#include "E16ANA_CalibDBManager.hh" 
#include "E16ANA_TargetInfo.hh" 


void E16ANA_TargetInfo::Print(){
  cerr<<"E16Target "<<name<<" "<<massNumber<<" ";
  cerr<<"position "<<position;
  cerr<<"sigma    "<<sigma<<endl;
}

//--------------------------------------------
void E16ANA_TargetInfoManager::Print(){
  E16WARNING("");
  cerr<<"runID  "<<runID<< " pattern "<<patternID <<" nTarget "<<nTarget<<endl;

  for (int i=0;i<nTarget;i++){
    cerr<<i<<" ";
    targets[i].Print();
  }

}


E16ANA_TargetInfoManager::E16ANA_TargetInfoManager(){
  E16INFO("DB Initialized");
#if 0
  string DefaultPATH="/ccj/u/E16/database/calib/";
  string DefaultCalibDBname="E16calibDB.txt";
  CalibDBfileSet(DefaultPATH, DefaultCalibDBname);
#endif

}

E16ANA_TargetInfoManager& E16ANA_TargetInfoManager::Instance() {
    static E16ANA_TargetInfoManager singleton;
    return singleton;
}



bool E16ANA_TargetInfoManager::ReadInfoWithRunID(int irunID){
  if ( runID == irunID ){
    E16INFO("runID is same: file is not read");
    return true;
  }
  else{
    runID = irunID;
  }
  return ReadInfo( );

}

bool E16ANA_TargetInfoManager::ReadInfo(){
  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();

  ifstream* ifsp = calib.CalibStreamOpenText("Target-position", runID);
  return ReadInfoCore( ifsp );

}

bool E16ANA_TargetInfoManager::ReadInfoByLocal(int runID, string localfilename ){
  
  ifstream ifs(localfilename, ios_base::in);

  if( ! ifs ){
    E16FATAL("local info file open error: %s", localfilename.c_str());
    return false;
  }

  return ReadInfoCore( &ifs );
   
}
bool E16ANA_TargetInfoManager::ReadTargetInfo( std::ifstream& ifs){
  string line;
  int count = 0;
  double x=0,y=0,z=0;double sx=0,sy=0,sz=0;  int mass=0; string name("temp");

  while( getline(ifs, line) ){
    if( line[0]== '#'  || line.empty() ){
      continue;
    }

    stringstream s;
    s<<line;

    s>> x>>y>>z>> sx>>sy>>sz>> mass >>name;

    targets[count]=E16ANA_TargetInfo(x,y,z, sx,sy,sz, mass,name);
    count ++;

    if( count == nTarget){
      return true;
    }
  }//while

  E16FATAL("target number in file is inconsistent:  count %d nTarget %d",
    count, nTarget);

  return false;
}


bool E16ANA_TargetInfoManager::ReadInfoCore( std::ifstream* ifsp){

  if( ifsp == NULL ){
    return false;
  }
  bool flag=true;

  ifstream& ifs = *ifsp;

  string line;

  while( getline(ifs, line) ){
    if( line[0]== '#'  || line.empty() ){
      continue;
    }
    stringstream s;
    s<<line;

    s>>patternID>>nTarget;

    if( nTarget > 5 || nTarget<2){
      E16FATAL("only supported 1<nTarget<6 while nTarget=%i",nTarget);
      flag=false;
      break;
    }
    if( patternID <1 || patternID > 3){
      E16FATAL("only supported 0<patternID<4 while ID=%i",patternID);
      flag=false;
      break;
    }
    flag=ReadTargetInfo(ifs);
    break;
  }//while
  
  ifs.close();
  delete ifsp;

  return flag;

}

