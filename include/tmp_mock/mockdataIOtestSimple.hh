//mockdataIOtestSimple.cc 220426 by S. Yokkaichi
//    Last modified at <2022-04-26 22:07:35 >
//
//mockdataIOtest.cc 220426 by S. Yokkaichi
//    Last modified at <2022-04-26 21:12:07 >
//from
//g4trajectoryDump.cc 220422 by S. Yokkaichi
//    Last modified at <2022-04-26 18:55:50 >

#ifndef MOCKDATAIOTESTSIMPLE_HH
#define MOCKDATAIOTESTSIMPLE_HH

#include <ctime>
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include <HepPDT/ParticleData.hh>

#include <TFile.h>
#include <TPostScript.h>
#include <TPDF.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TText.h>
#include <TStyle.h>

#include <TH1.h>
#include <TH2.h>
#include <TTree.h>
#include <TMath.h>
#include <TVector3.h>

#include "E16ANA_Constant.hh"

#include "E16ANA_ParamManager.hh"
#include "E16ANA_G4OutputData.hh"
#include "E16ANA_ErrorMessage.hh"


using namespace std;
#include <CLHEP/Vector/ThreeVector.h>
#include <CLHEP/Vector/LorentzVector.h>
using namespace CLHEP;

class E16ANA_G4ANATrajectory;

inline int ModuleID_2013to2020_33(int id )
{
   const int moduleID_2013to2020_33[33] = {
     10, 110, 210, 9, 109, 209, 8, 108, 208, 7, 107, 207, 6, 106, 206, 
     5, 105, 205,
     4,  104, 204, 3, 103, 203, 2, 102, 202, 1, 101, 201, 0, 100, 200 };
   return  moduleID_2013to2020_33[ id ];
}
inline int ModuleID_2020to2013_33(int id ){//GTR,SSD
   const int module_id_kawama33[3][11] = {
     {30, 27, 24, 21, 18, 15, 12, 9, 6, 3, 0},
     {31, 28, 25, 22, 19, 16, 13, 10, 7, 4, 1},
     {32, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2}};
   return module_id_kawama33[ id / 100][id % 100];
}
inline int ModuleID_2013to2020_27( int id ){// //LG,HBD
   const int moduleID_2013to2020_27[27] = {
   9, 109, 209, 8, 108, 208, 7, 107, 207,  6, 106, 206, 
   5, 105, 205, 
   4, 104, 204, 3, 103, 203, 2, 102, 202,  1, 101, 201};
   return  moduleID_2013to2020_27[ id ];
}
inline int ModuleID_2020to2013_27(int id ){//LG,HBD
   const int module_id_kawama27[3][9] = {
     {24, 21, 18, 15, 12, 9, 6, 3, 0 },
     {25, 22, 19, 16, 13, 10, 7, 4, 1},
     {26, 23, 20, 17, 14, 11, 8, 5, 2}};

   int id2=(id %100) -1;

   return module_id_kawama27[ id / 100][ id2 ];
}



//===============================================================
class E16ANA_MockHit{
private:
  short pID;         //particle ID in PDG code
  short charge;      //+1 or -1
  short moduleID;    
  short temp;
  double p;          //momentum value
  double x,y,z;      //local cooridnate in the detector
  double gx,gy,gz;   //global cooridnate
  double px,py,pz;   //momentum at hit point
  double gpx,gpy,gpz;   //momentum at hit point:global
  double t;          //timing

public:
  E16ANA_MockHit(){
    Clear();
  }
  enum{ErrorValue = -9999};

  void SetPID  (int pid, int icharge, int imod){
    pID = pid; charge=icharge; moduleID=imod; temp=ErrorValue; };

  void SetXYZ (double ix, double iy, double iz){    x=ix; y=iy; z=iz; }
  void SetXYZ(TVector3& v){    x=v.X();y=v.Y();z=v.Z(); }
  void SetGXYZ(double ix, double iy, double iz){    gx=ix; gy=iy; gz=iz;}
  void SetGXYZ(TVector3& gv){    gx=gv.X();gy=gv.Y();gz=gv.Z(); }

  void SetP   (double ix, double iy, double iz){    px=ix; py=iy; pz=iz; 
    p=sqrt(ix*ix + iy*iy + iz*iz);}
  void SetP   (TVector3& v){    px=v.X(); py=v.Y(); pz=v.Z(); p=v.Mag() ;}
  void SetP   (TVector3 v){    px=v.X(); py=v.Y(); pz=v.Z(); p=v.Mag() ;}

  void SetGP  (double ix, double iy, double iz){   gpx=ix;gpy=iy;gpz=iz; 
    p=sqrt(ix*ix + iy*iy + iz*iz);}
  void SetGP  (TVector3& gv){    gpx=gv.X(); gpy=gv.Y(); gpz=gv.Z(); p=gv.Mag();}
  void SetGP  (TVector3 gv){    gpx=gv.X(); gpy=gv.Y(); gpz=gv.Z(); p=gv.Mag();}

  void SetT(double it){ t=it;}

  int PID(){return pID;}
  int Charge(){return charge;}
  int ModuleID() { return moduleID; }
  double X()  {return x;}
  double Y()  {return y;}
  double Z()   {return z;}
  double GX()  {return gx;}
  double GY()   {return gy;}
  double GZ()   {return gz;}
  Hep3Vector XV()  {return Hep3Vector(x,y,z);}
  Hep3Vector GXV()  {return Hep3Vector(gx,gy,gz);}
  Hep3Vector PV()  {return Hep3Vector(px,py,pz);}
  Hep3Vector GPV() {return Hep3Vector(gpx,gpy,gpz);}

  TVector3 XTV() {return TVector3(x,y,z);}
  TVector3 GXTV(){return TVector3(gx,gy,gz);}
  TVector3 PTV() {return TVector3(px,py,pz);}
  TVector3 GPTV() {return TVector3(gpx,gpy,gpz);}


  double AngleY(){
    double pxz = sqrt( px*px + pz*pz );
    double incidentAngley = atan2(py, pxz);
    return incidentAngley;
  }
  double AngleXZ(){
    double incidentAnglex = atan2(px, pz);
    return incidentAnglex;
  }
  double Time(){return t;}

  void Clear(){
    pID = charge = moduleID = ErrorValue; 
    p=ErrorValue;
    x  = y = z = ErrorValue;
    gx = gy =gz = ErrorValue;
    px = py =pz = ErrorValue;
    t=ErrorValue;
  }

  void Dump(std::string tag=""){
    fprintf(stderr, 
	    "E16ANA_MockHit: %s : %6.1f %6.1f %6.1f /%6.3f %6.3f %6.3f\n",
	    tag.c_str(), x, y, z, gx, gy, gz);
    fprintf(stderr, 
	    "             (p,charge,pid,moduleID,t): %6.3f %2i %4i %3i %6.3f %s\n",
      p, charge, pID, moduleID, t, 
	    HepPID::particleName(pID).c_str() );
    fprintf(stderr, 
	    "             (angle-xz,angle-y): %6.3f %6.3f\n",
      AngleXZ()*RadToDeg, AngleY()*RadToDeg );
  }

  int WriteData(FILE* fpWrite);
  int ReadData(FILE* fpRead);


};

class E16ANA_MockTrack{
private:
  short pID;         //particle ID in PDG code
  short charge;      //+1 or -1
  int temp;          //padding
  double px,py,pz,p;     //original momentum
  double x,y,z;          //original vertex (initial point)
  E16ANA_MockHit hits[8];// hits in each layer
public:
  enum{ErrorValue = -9999};
  int PID(){return pID;}
  int Charge(){return charge;}
  Hep3Vector Vertex()  {return Hep3Vector(x,y,z);}
  Hep3Vector OrigPV()  {return Hep3Vector(px,py,pz);}
  TVector3 VertexT() {return TVector3(x,y,z);}
  TVector3 OrigPTV() {return TVector3(px,py,pz);}

  E16ANA_MockHit& SSD()  {return hits[0];}    //can assign and change:
  E16ANA_MockHit& GTR1() {return hits[1];}
  E16ANA_MockHit& GTR2() {return hits[2];}
  E16ANA_MockHit& GTR3() {return hits[3];}
  E16ANA_MockHit& HBDfront(){return hits[4];}
  E16ANA_MockHit& HBDback() {return hits[5];}
  E16ANA_MockHit& LGVD()    {return hits[6];}
  E16ANA_MockHit& LG()      {return hits[7];}
  ~E16ANA_MockTrack(){}
  E16ANA_MockTrack(){ Clear();}

  void SetValue(
    int ipid, int icharge,
    double ipx, double ipy, double ipz, double ip,
    double ix, double iy, double iz
  ){
    pID=ipid; charge=icharge;
    px=ipx;  py=ipy;  pz=ipz; p=ip;
    x=ix;  y=iy;  z=iz;
  }
  void Clear(){
    pID=charge=px=py=pz=p=x=y=z=ErrorValue;
    for(int i=0;i<8;i++){ hits[i].Clear() ;}
  }

  int ReadData(FILE* fp){
    int flag = fread(&pID, sizeof(double), 8, fp);
    flag = fread(hits, sizeof(E16ANA_MockHit), 8, fp);
    return flag;
  }

  int WriteData(FILE* fp){
    E16INFO("write");
    int flag = fwrite(&pID, sizeof(double), 8, fp);
    flag = fwrite(hits, sizeof(E16ANA_MockHit), 8, fp);
    return flag;
  }

  void Dump(){
    cerr<<"E16ANA_MockTrack "<<pID <<" "<<charge<<" "<<p<<" ";
    cerr<<Hep3Vector(px,py,pz)<<" "<<Hep3Vector(x,y,z)<<endl;
    hits[0].Dump("  ssd");
    hits[1].Dump("  gtr1");
    hits[2].Dump("  gtr2");
    hits[3].Dump("  gtr3");
    hits[4].Dump("  hbdf");
    hits[5].Dump("  hbdb");
    hits[6].Dump("  LGVD");
    hits[7].Dump("  LG  ");
      cerr<<"----------------"<<endl;
  }

};

class E16ANA_MockTrackOutputData{
  //modified from E16ANA_G4OutputData 
private:
  FILE* fpRead;
  FILE* fpWrite;
  E16ANA_MockTrack  track;            //handle for current track in the data file

public:
  E16ANA_MockTrackOutputData(){
    fpRead=NULL;    fpWrite=NULL;
  }
  ~E16ANA_MockTrackOutputData();

  enum{OK=0, OpenERROR,ReadERROR};
  int OpenReadFile(const char* filename);
  int OpenWriteFile(const char* filename);
  int CloseReadFile();
  int CloseWriteFile();

  E16ANA_MockTrack& Track(){ return track;}
  
  int WriteATrack(){
    return track.WriteData(fpWrite);
  }
  int ReadATrack(){
    int flag=track.ReadData(fpRead);
    if( flag != 8) {
      E16FATAL("READ ERROR");
      track.Clear();
      return ReadERROR;
    }
    else{
      return OK;
    }
  }

};
  
//E16ANA_MockTrackOutputData::~E16ANA_MockTrackOutputData(){
//  if( fpRead != NULL){    fclose(fpRead);     }
//  if( fpWrite != NULL){      fclose(fpWrite); }
//}
//  
//
//int E16ANA_MockTrackOutputData::CloseReadFile(){
//  fclose(fpRead); fpRead=NULL;
//  return 0;
//}
//int E16ANA_MockTrackOutputData::CloseWriteFile(){
//  fclose(fpWrite); fpWrite=NULL;
//  return 0;
//}
//
//int E16ANA_MockTrackOutputData::OpenReadFile(const char* filename){
//  if( fpRead != NULL ){
//    E16FATAL("file is already opened for reading: %s",filename);
//    return OpenERROR;
//  }
//
//  fpRead = fopen(filename, "r");
//
//  if ( fpRead==NULL ){
//    E16FATAL("file open error for reading: %s",filename);
//    return OpenERROR;
//  }
//  return OK;
//}
//
//int E16ANA_MockTrackOutputData::OpenWriteFile(const char* filename){
//  if( fpWrite != NULL ){
//    E16FATAL("file is already opened for writing: %s",filename);
//    return OpenERROR;
//  }
//
//  fpWrite = fopen(filename, "w");
//
//  if ( fpWrite==NULL ){
//    E16FATAL("file open error for writing: %s",filename);
//    return OpenERROR;
//  }
//  return OK;
//}


////======================================================
//void ReadAndDumpData(int nEvent,
//  E16ANA_MockTrackOutputData& mockdata){
//
//  for(int i=0; i<nEvent; i++) {
//
//    int flag = mockdata.ReadATrack();
//    if(flag == mockdata.ReadERROR){
//      E16FATAL("possibly nEvent/nTrack over the file size");
//      return;
//    }
//    E16INFO("readATrack %d",flag);
//    mockdata.Track().Dump();
//  }
//
//}
////-------------------------------------------
//int main(int argc, char* argv[]){
//
//  //E16ANA_ParamManager *paramMgr;
//   char* filename1; char* filename2; 
//   char* outfilenamebase;
//   char outfilename0[128]; 
//
//   char outfilename1[128];
//   char outfilename2[128];   char outfilename3[128];
//   char outfilename4[128];   char outfilename5[128];
//   char outfilename6[128];
//   char overfilename0[128];
//
//   char outfilenameG4out[128];
//   char outfilenameMockout[128];
//   int nEvent = 0;
//
//   if (argc!=3){
//      cerr << "Usage: ./mockdataIOtestSimple inputmockdatafile nevent"<<endl;
//      return 1;
//   }
//   else{
//     filename1=argv[1];
//     nEvent = atoi(argv[2]);
//   }
//
//   stringstream argStr;
//   for(int i=0;i<argc;i++){
//     argStr <<argv[i]<<" ";
//   }
//
//   E16ANA_MockTrackOutputData mockdata1;
//   int flag3 = mockdata1.OpenReadFile(filename1);
//   if( flag3 != mockdata1.OK ){     exit(1);   }
//
//
//   ReadAndDumpData(nEvent, mockdata1);
//
//   mockdata1.CloseReadFile();
//   //   mockdata1.CloseWriteFile();
//
//
//   return 0;
//}

#endif // MOCKDATAIOTESTSIMPLE_HH
