//2020-09-16, uploaded by yokkaich
//2020-08-30, uploaded by yokkaich
//2019-06-26, uploaded by yokkaich
////FMfieldDump.cc 150528 by S. Yokkaichi
//    Last modified at <2020-09-16 13:00:05 >
// revised 190515 by S.Yokkaichi
//

#include <stdlib.h>
#include <iostream>
#include <CLHEP/Vector/ThreeVector.h>

#include "E16ANA_ParamManager.hh"
#include "E16ANA_ErrorMessage.hh"
#include "E16ANA_MagneticFieldMap.hh"

using namespace std;
using namespace CLHEP;

void Integral(E16ANA_MagneticFieldMap* fmf, int argc, char* argv[]){
  double x=0,y=0, z=0;
    
  if( argc == 5){
    x= atof(argv[2]);
    y= atof(argv[3]);
    z= atof(argv[4]);
  }
  else{
    E16FATAL("argc = %d: error for the flag=%d", argc, atoi(argv[1]) );
    exit(1);
  }

  int flag = 0;//bilinear
  double B[3];
  Hep3Vector vec(x,y,z);
  Hep3Vector unit = vec / vec.mag();
  cerr<<"direction vec "<<vec <<"-> unit "<<unit<<endl;

  double bdl=0;//[Tm]
  double dl = 1;//[mm]

  double rxzThr[9]={0,100,200,400,600,1200,1400,1800,10000};
  int rIndex = 0;
  bool print = false;

  for(int i=0;i<3600;i++){
    double onestep = 1.0;// mm
    Hep3Vector pos  = unit * onestep * i;
    double point[3]={ pos.x(), pos.y(), pos.z() };//mm

    fmf -> GetFieldValue_Tesla(point, B, flag);
    Hep3Vector BV(B[0],B[1],B[2]);  
    double cos= unit*BV/BV.mag();
    double sin= sqrt(1-cos*cos);
    double Bperp = BV.mag()*sin;

    double b = Bperp;
    //    double b = BV.mag();
    //        double b = BV.y();

    //    bdl += b * dl * 1e-6; //gauss*cm -> T*m : 0.0001 * 0.01
    bdl += b * dl * 1e-3; //T*mm -> T*m

    double rxz = sqrt( pos.x()*pos.x() + pos.z()*pos.z() );

    if( rxz > rxzThr[rIndex]){
      print = true;
      rIndex ++;
    }
    if( print ){
      fprintf(stderr, "Bdl(Tm)=%8.6f for %7.4f [T] in %4d th step",  bdl, b, i);
      cerr<<" for "<<BV<<" T @"<<pos<<"mm"<<endl;
      print = false;
    }
  }//i

}
void PrintBbyStep(E16ANA_MagneticFieldMap* fmf, int argc, char* argv[]){
  double x=0,y=0, z=0;
  double vx=0,vy=0, vz=0, step=10;


  if( argc == 9){
    x= atof(argv[2]);
    y= atof(argv[3]);
    z= atof(argv[4]);
    vx= atof(argv[5]);
    vy= atof(argv[6]);
    vz= atof(argv[7]);
    step = atof(argv[8]);
  }
  else{
    E16FATAL("argc = %d: error for the flag=%d", argc, atoi(argv[1]) );
    exit(1);
  }

  int flag = 0;//bilinear
  double B[3];
  Hep3Vector initPos(x, y, z);
  Hep3Vector vec(vx, vy, vz);
  Hep3Vector unit = vec / vec.mag();
  cerr<<"direction vec "<<vec <<"-> unit "<<unit<<endl;

  for(int i=0;i<20;i++){

    Hep3Vector pos  = initPos + unit * step*i;
    double point[3]={ pos.x(), pos.y(), pos.z() };//mm

   fmf -> GetFieldValue_Tesla(point, B, flag);

    double norm = sqrt(B[0]*B[0] + B[1]*B[1] + B[2]*B[2]);
    
    fprintf(stderr, 
      //      "Bx,y,z, total %8.5f %8.5f %8.5f : %8.5f at point (%6.3f %6.3f %6.3f)[mm]\n", 
      //      "Bx,y,z, total %8.3f %8.3f %8.3f : %8.3f at point (%6.1f %6.1f %6.1f)[mm]\n", 
      "Bx,y,z, total %8.5f %8.5f %8.5f : %8.5f [T] at point (%6.1f %6.1f %6.1f)[mm]\n", 
      B[0], B[1], B[2], norm,
      pos.x(),       pos.y(),       pos.z() );

  }//i

}

void PrintB(E16ANA_MagneticFieldMap* fmf, int argc, char* argv[]){
  double x=0,y=0, z=0;

  if( argc == 5){
    x= atof(argv[2]);
    y= atof(argv[3]);
    z= atof(argv[4]);
  }
  else{
    E16FATAL("argc = %d: error for the flag=%d", argc, atoi(argv[1]) );
    exit(1);
  }

    double point[3]={ x*0.1, y*0.1, z*0.1 };//mm->cm
    double B[3];
    int flag = 0;//bilinear
    fmf -> GetFieldValue(point, B, flag);

    double norm = sqrt(B[0]*B[0] + B[1]*B[1] + B[2]*B[2]);
    cerr<<"Bx,y,z, total =("<<B[0]*0.0001<<", "<<B[1]*0.0001<<", "<<B[2]*0.0001<<"[T]: "<<norm<< " [gauss]) at ";
    cerr<<"("<<x<<","<<y<<","<<z<<")[mm]"<<endl;
    
}
int main(int argc, char* argv[]){

  int flag=0;   double x=0,y=0,z=0;
  
  if (argc==1){
    cout << "Usage: ./FMfieldDump     0 x,y,z (coordinate, mm)"<<endl;
    cout << "Usage: ./FMfieldDump     1 x,y,z (direction from the center for integral)"<<endl;
    cout << "Usage: ./FMfieldDump     2 x,y,z[mm], vx,vy,vz,step[mm] (initial position, direction, plot by the step)"<<endl;
    cout << "Usage: ./FMfieldDump     3 (for your customization)"<<endl;
    return 1;
  }
  else{
    flag=atoi(argv[1]);
  }


  E16INFO("initialize...");

#if 0
  char* E16calibfilename = "./E16CalibFiles-local.cfg";
  E16ANA_ParamManager* paramMgr= new E16ANA_ParamManager( E16calibfilename );

  char* filename = paramMgr->GetMapFileName();
  E16INFO("field map filename in paramfile:%s",filename);
#endif

#if 0
  //map conversion text->binary
  E16ANA_MagneticFieldMap *fmf= new E16ANA_MagneticFieldMap3D("tempdata.txt");
  fmf -> Initialize();

  E16ANA_MagneticFieldMap3D* fmf2=   (E16ANA_MagneticFieldMap3D*) fmf;
  fmf2 -> MapConvert("tempdata.bin");
  fmf -> Initialize_binary("tempdata.bin");
#endif


  //  E16ANA_MagneticFieldMap* fmf= new E16ANA_MagneticFieldMap3D("/ccj/u/E16/database/fieldmap/Bmap_201207010_mod.binary");

  E16ANA_MagneticFieldMap* fmf= new E16ANA_MagneticFieldMap3D("/ccj/u/E16/database/fieldmap/Bmap-SKS-block-far-191218-2450A.binary");

  fmf -> Initialize_binary();

  //  Hep3Vector shiftV(0.0, 0.0, 0.0);
  //  int ncall =fmf->Initialize_shift(shiftV);

   E16INFO("----map initialize end----------");

  if( flag == 0 ){
    PrintB(fmf, argc, argv);
  }
  else if (flag == 1){
    Integral(fmf, argc, argv);
  }
  else if (flag == 2){
    PrintBbyStep(fmf, argc, argv);
  }
  else if (flag == 3){
    cerr<<"convert..."<<endl;
    
  }

  return 0;
}
