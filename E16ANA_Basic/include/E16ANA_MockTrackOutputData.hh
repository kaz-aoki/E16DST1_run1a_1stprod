//2022-05-06, uploaded by yokkaich
//E16ANA_MockTrackOutputData.hh 220504 by S. Yokkaichi
//    Last modified at <2022-05-06 07:00:37 >

#ifndef E16ANA_MockTrackOutputData_HH
#define E16ANA_MockTrackOutputData_HH

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>

#include <CLHEP/Vector/ThreeVector.h>
#include <HepPID/ParticleName.hh>
#include <TVector3.h>
#include <TRandom.h>

using namespace CLHEP;

#include "E16ANA_ErrorMessage.hh"
#include "E16ANA_Constant.hh"

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
  void SetXYZ(TVector3 v){    x=v.X();y=v.Y();z=v.Z(); }
  void SetGXYZ(double ix, double iy, double iz){    gx=ix; gy=iy; gz=iz;}
  void SetGXYZ(TVector3& gv){    gx=gv.X();gy=gv.Y();gz=gv.Z(); }
  void SetGXYZ(TVector3 gv){    gx=gv.X();gy=gv.Y();gz=gv.Z(); }

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
	

  double Xsmear(double sigma_mm)  { return gRandom->Gaus(x, sigma_mm); }
  double Ysmear(double sigma_mm)  { return gRandom->Gaus(y, sigma_mm); }
  Hep3Vector XVsmear(double sigma_Xmm, double sigma_Ymm)    { 
    return 
      Hep3Vector (  gRandom->Gaus(x, sigma_Xmm),
      gRandom->Gaus(y, sigma_Ymm),   z ); 
  }
  TVector3 XTVsmear(double sigma_Xmm, double sigma_Ymm)    { 
    return 
      TVector3 (  gRandom->Gaus(x, sigma_Xmm),
      gRandom->Gaus(y, sigma_Ymm),   z ); 
  }

  Hep3Vector XV_HBDcorrected(double sigma_Xmm=0.0, double sigma_Ymm=0.0)  {
    double zdiff = 0 - Z();
    double scale = zdiff/pz;
    Hep3Vector cX= XV() + PV()*scale;
    //    std::cerr<<" HBD correct "<<X() <<" "<<PV()<<" "<<correctedX<<std::endl;
    return   Hep3Vector(  
      gRandom->Gaus(cX.x(), sigma_Xmm),
      gRandom->Gaus(cX.y(), sigma_Ymm),   cX.z()  ); 
  }
  TVector3 XTV_HBDcorrected(double sigma_Xmm=0.0, double sigma_Ymm=0.0)  {
    double zdiff = 0 - Z();
    double scale = zdiff/pz;
    Hep3Vector cX= XV() + PV()*scale;
    //    std::cerr<<" HBD correct "<<X() <<" "<<PV()<<" "<<correctedX<<std::endl;

    return   TVector3(  
      gRandom->Gaus(cX.x(), sigma_Xmm),
      gRandom->Gaus(cX.y(), sigma_Ymm),   cX.z()  ); 
  }



  bool IsTypeA(){
    if(  (moduleID%100) %2 == 1 ){return true;}//101,103,105,107,...
    else {return false;}
  }
  double AngleY(){
    double pxz = sqrt( px*px + pz*pz );
    double incidentAngley = atan2(py, pxz);
    return incidentAngley;
  }
  double AngleXZ(){
    double incidentAnglex = atan2(px, pz);
    return incidentAnglex;
  }

  double AngleXZ_Tracker(){
    double pxtemp = IsTypeA() ? -px : px ;
    double incidentAnglex = atan2(pxtemp, pz);
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
    //    E16INFO("write");
    int flag = fwrite(&pID, sizeof(double), 8, fp);
    flag = fwrite(hits, sizeof(E16ANA_MockHit), 8, fp);
    return flag;
  }

  void Dump(){
    std::cerr<<"E16ANA_MockTrack "<<pID <<" "<<charge<<" "<<p<<" ";
    std::cerr<<Hep3Vector(px,py,pz)<<" "<<Hep3Vector(x,y,z)<<std::endl;
    hits[0].Dump("  ssd");
    hits[1].Dump("  gtr1");
    hits[2].Dump("  gtr2");
    hits[3].Dump("  gtr3");
    hits[4].Dump("  hbdf");
    hits[5].Dump("  hbdb");
    hits[6].Dump("  LGVD");
    hits[7].Dump("  LG  ");
    std::cerr<<"----------------"<<std::endl;
    std::cerr<<" SSD   "<<hits[0].Xsmear(0.1)<<std::endl;
    std::cerr<<" GTR1  "<<hits[1].Xsmear(0.3)<<std::endl;
    std::cerr<<" GTR2  "<<hits[2].Ysmear(0.5)<<std::endl;
    std::cerr<<" GTR3  "<<hits[3].XVsmear(0.3,0.5)<<std::endl;
    std::cerr<<" HBDbc  "<<hits[5].XV_HBDcorrected()<<std::endl;
    std::cerr<<" HBDbcsmear "<<hits[5].XV_HBDcorrected(10.0, 10.0)<<std::endl;
    std::cerr<<"----------------"<<std::endl;
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
  

#endif // E16ANA_MockTrackOutputData_HH
