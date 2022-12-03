//2022-05-06, uploaded by yokkaich
//mockdataIOtestSimple.cc 220426 by S. Yokkaichi
//    Last modified at <2022-05-06 04:54:07 >
//
//mockdataIOtest.cc 220426 by S. Yokkaichi
//    Last modified at <2022-04-26 21:12:07 >
//from
//g4trajectoryDump.cc 220422 by S. Yokkaichi
//    Last modified at <2022-04-26 18:55:50 >

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

#include "E16ANA_MockTrackOutputData.hh"

using namespace std;
#include <CLHEP/Vector/ThreeVector.h>
#include <CLHEP/Vector/LorentzVector.h>
using namespace CLHEP;


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

//======================================================
void ReadAndDumpData(int nEvent,  E16ANA_MockTrackOutputData& mockdata){

  for(int i=0; i<nEvent; i++) {
    int flag = mockdata.ReadATrack();
    E16WARNING("readATrack %d",flag);

    if(flag == mockdata.ReadERROR){
      E16FATAL("possibly nEvent/nTrack over the file size");
      return;
    }

    std::cout << "track: " << i << std::endl;
    mockdata.Track().Dump();
    
  }//i

}
void ReadAndDivideData(int nEvent,
  E16ANA_MockTrackOutputData& mockdata, int divEvent, char* outfilenamebase){

  int nfile=0;
  int j=0;

  for(int i=0; i<nEvent; i++,j++) {
    if( j==divEvent ){
      j=0;
      nfile++;
      int flag3 = mockdata.CloseWriteFile();
      //      cerr<<"close"<<endl;
    }
    //    cerr<<"i,j,nfile "<<i<<" "<<j<<" "<<nfile<<endl;    

    if( j==0 ){
      char filename[128];
      sprintf(filename, "%s.%03d.mockout", outfilenamebase, nfile);
      E16INFO("opne divide save file %s",filename);

      int flag3 = mockdata.OpenWriteFile(filename);
      if( flag3 != mockdata.OK ){     exit(1);   }
    }

    int flag = mockdata.ReadATrack();
    E16WARNING("readATrack %d",flag);

    if(flag == mockdata.ReadERROR){
      E16FATAL("possibly nEvent/nTrack over the file size");
      return;
    }

    //    mockdata.Track().Dump();
    mockdata.WriteATrack();



    
  }//i

}
//-------------------------------------------
int main(int argc, char* argv[]){

  //E16ANA_ParamManager *paramMgr;
   char* filename1; char* filename2; 

   char* outfilenamebase;

   int nEvent = 0;
   int divEvent = 0;

   if (argc<3 || argc > 5 || argc==4){
      cerr << "Usage: ./mockdataIOtestSimple inputmockdatafile nevent (divide-nevent outfilenamebase)"<<endl;
      return 1;
   }
   else if ( argc == 3) {
     filename1=argv[1];
     nEvent = atoi(argv[2]);
     divEvent = nEvent;
     outfilenamebase="";
   }
   else if ( argc == 5) {
     filename1=argv[1];
     nEvent = atoi(argv[2]);
     divEvent = atoi(argv[3]);
     outfilenamebase=argv[4];
   }

   cerr<<" "<<nEvent<<" "<<divEvent<<" "<<outfilenamebase<<endl;

   stringstream argStr;
   for(int i=0;i<argc;i++){
     argStr <<argv[i]<<" ";
   }

   E16ANA_MockTrackOutputData mockdata1;
   int flag3 = mockdata1.OpenReadFile(filename1);
   if( flag3 != mockdata1.OK ){     exit(1);   }

   if( argc == 3){
     ReadAndDumpData(nEvent, mockdata1);
   }
   else if ( argc == 5){
     ReadAndDivideData(nEvent, mockdata1, divEvent, outfilenamebase);
   }

   mockdata1.CloseReadFile();
   //   mockdata1.CloseWriteFile();


   return 0;
}
