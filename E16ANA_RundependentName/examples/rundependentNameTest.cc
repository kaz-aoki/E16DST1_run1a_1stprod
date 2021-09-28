//2021-09-12, uploaded by yokkaich
//rundependentNameTest.cc 210912 by S. Yokkaichi
//    Last modified at <2021-09-12 22:47:31 >
//
//
//Test of 
//  geometry/filed filename using calibDB  (RundependentName)
//and
//  geometry/field global pointer

#include <stdlib.h>
#include <iostream>
#include <CLHEP/Vector/ThreeVector.h>

#include "E16ANA_ErrorMessage.hh"
#include "E16ANA_CalibDBManager.hh"

#include "E16ANA_GeometryV2.hh"
#include "E16ANA_MagneticFieldMap.hh"
#include "E16ANA_RundependentName.hh"

using namespace std;
using namespace CLHEP;

void DumpInfo(string tag){// In the factory, tracking, etc.

  cerr<<"---- DumpInfo "<<tag<<"------------------"<<endl;

    E16ANA_MagneticFieldMap3D* fmf = (E16ANA_MagneticFieldMap3D*)E16ANA_MagneticFieldMap3D::GlobalPointer( );
    E16ANA_GeometryV2* geom = E16ANA_GeometryV2::GlobalPointer( );

//test geometry
    Hep3Vector localPos(20, 10, 0);
    int module0=16;//105
    Hep3Vector gpos0 = geom->GTR1( module0 )->GetGPos(localPos);
    cerr<<"105 "<<localPos<<"-->"<<gpos0<<endl;
    int module1=19;//104
    Hep3Vector gpos1 = geom->GTR1( module1 )->GetGPos(localPos);
    cerr<<"104 "<<localPos<<"-->"<<gpos1<<endl;

//test fieldmap
  Hep3Vector pos(0,0,1);

  double point[3]={ pos.x(), pos.y(), pos.z() };//mm
  double B[3]={0}; int flag=0;
  fmf -> GetFieldValue_Tesla(point, B, flag);

  double norm = sqrt(B[0]*B[0] + B[1]*B[1] + B[2]*B[2]);
    
  fprintf(stderr, 
      "Bx,y,z, total %8.5f %8.5f %8.5f : %8.5f [T] at point (%6.1f %6.1f %6.1f)[mm]\n", 
      B[0], B[1], B[2], norm,      pos.x(),       pos.y(),       pos.z() );

}

void RundependentInitialize(int runID){
  E16ANA_RundependentName& name = E16ANA_RundependentName::Instance();

  string geomName    = name.ReadNameWithRunID( runID, "geometry","/ccj/u/E16/database/");
  string fieldmapName= name.ReadNameWithRunID( runID, "fieldmap","/ccj/u/E16/database/");
  cerr<<"name  "<<geomName << " "<< fieldmapName <<endl;

  if (geomName != "unchanged"){
      E16ANA_GeometryV2* geom = new  E16ANA_GeometryV2( geomName );
      E16ANA_GeometryV2::SetGlobalPointer( geom );
  }
  if (fieldmapName != "unchanged"){
      E16ANA_MagneticFieldMap3D* fmf = new E16ANA_MagneticFieldMap3D( fieldmapName );
    fmf->Initialize_binary();
    E16ANA_MagneticFieldMap::SetGlobalPointer( fmf );
  }


  
}


int main(){
  
  int  runID = 29999;

  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();

  calib.SetRunID(runID);

#if 0
    //for the local test
  calib.CalibDBfileResetByLocal("/ccj/u/E16/database/calib/",
    "E16calibDB-210910.txt");
#endif

  E16ANA_RundependentName& name = E16ANA_RundependentName::Instance();

  string geomName    =name.ReadNameWithRunID( runID, "geometry", "/ccj/u/E16/database/");
  string fieldmapName=name.ReadNameWithRunID( runID, "fieldmap", "/ccj/u/E16/database/");
  cerr<<"name  "<<geomName << " "<< fieldmapName <<endl;

  if (geomName != "unchanged"){
    E16ANA_GeometryV2* geom = new  E16ANA_GeometryV2( geomName );
    E16ANA_GeometryV2::SetGlobalPointer( geom );
  }
  if (fieldmapName != "unchanged"){
      E16ANA_MagneticFieldMap3D* fmf = new E16ANA_MagneticFieldMap3D( fieldmapName );
    fmf->Initialize_binary();
    E16ANA_MagneticFieldMap::SetGlobalPointer( fmf );
  }

  DumpInfo("test 0");


  RundependentInitialize( 28888 );
  DumpInfo("test 1 same filename");

  RundependentInitialize( 28888 );
  DumpInfo("test 2 same runID");

  RundependentInitialize( 50000 );
  DumpInfo("test 3 geom/field file changed");

}









