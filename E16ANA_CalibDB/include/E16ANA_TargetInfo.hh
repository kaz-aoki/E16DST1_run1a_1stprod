//E16ANA_TargetInfo.hh 210709 by S. Yokkaichi
//    Last modified at <2021-09-10 19:06:08 >
//

#if 0

- singleton
    for global and unity

#endif


#ifndef E16ANA_TARGETINFO_H
#define E16ANA_TARGETINFO_H

#include <stdio.h>

#include <string>
#include <iostream>
#include <fstream>
#include <map>

#include <CLHEP/Vector/ThreeVector.h>
using namespace CLHEP;

class E16ANA_TargetInfo{// information of a target wire/foil
private:
  Hep3Vector position;
  Hep3Vector sigma;
  int massNumber;
  std::string name;

public:
  E16ANA_TargetInfo(){
    position=Hep3Vector(0,0,0);
    sigma=Hep3Vector(0,0,0);
    massNumber=0;
    name=std::string("temp");
  }
  E16ANA_TargetInfo(double x, double y, double z, 
    double sx,double sy, double sz, int A, std::string iname){
    position=Hep3Vector(x,y,z);
    sigma=Hep3Vector(sx,sy,sz);
    massNumber=A;
    name=iname;
  }
  Hep3Vector& Position(){return position;}
  Hep3Vector& Sigma(){return sigma;}
  int MassNumber(){return massNumber;}
  std::string Name(){return name;}
  void Print();
								  
};

class E16ANA_TargetInfoManager{

public:
  static E16ANA_TargetInfoManager& Instance();

private:
  std::string CalibPATH;
  std::string IndexPATH;
  std::string CalibDBname;

  E16ANA_TargetInfoManager( const E16ANA_TargetInfoManager& );
  E16ANA_TargetInfoManager( );

  static E16ANA_TargetInfoManager singleton;

  bool CalibDBFileRead(std::string filename);
  bool IndexFile(std::string filename);

  std::map<std::string, std::string>  calibDB;
  bool CalibDBfileSet(std::string newpath, std::string newfilename);

  int runID;
  int patternID;// 1: wireR, 2:wireL 3:3-targets
                //  read from file, depending on runID
  int nTarget;  // number of target, read from the file
  E16ANA_TargetInfo targets[5];

  bool ReadInfo();
  bool ReadInfoCore(  std::ifstream* ifsp );
  bool ReadTargetInfo( std::ifstream& ifs);

public:
  bool ReadInfoWithRunID(int runid);
  bool ReadInfoByLocal(int runID, std::string localinfofilename);

  void Print();

  bool IsWire(){
    if( patternID == 1 || patternID == 2){
      return true;
    }
    else{
      return false;
    }
  }

  int CurrentRunID(){return runID;}
  int PatternID(){return patternID;}
  int NoT(){return nTarget;}
  E16ANA_TargetInfo& Info(int i){return targets[i];}

};



#endif//E16ANA_TARGETINFO_H


