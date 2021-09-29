//2021-02-27, uploaded by nakai
//2020-10-27, uploaded by yokkaich
//2016-11-22, uploaded by nakai
#include <iostream>
#include <bitset>

#include <TMath.h>
#include <TRandom.h>
#include <TFile.h>
#include <TTree.h>

#include "E16ANA_Geometry.hh"
#include "E16ANA_GeometryV2.hh"

using namespace std;

// check the SSD change effect 201025 by S.Yokkaichi
//   use old lib and updated lib
//   compare the output text


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

int main(int argc, char **argv){
  E16ANA_GeometryV2* geom_v2=NULL;
//  string geomfilename="/ccj/u/E16/database/geometry/v2/geometry_200606.dat";
  string geomfilename="/e16/u/ichikawa/work/dst1/E16DST1/E16ANA_Geometry/database/v2/geometry_200606.dat";
  if( argc>1){
    geom_v2= new E16ANA_GeometryV2(argv[1]);
  }
  else{
    cerr<<"usage:"<<argv[0]<<"(geom file name)"<<endl;
    cerr<<"if no filename, use default :" << geomfilename<<endl;
    geom_v2 = new E16ANA_GeometryV2(geomfilename);
  }
   //geom_v2->SetDesignValues();
   //geom_v2->SetValuesFromV1(geom_v1);

   G4ThreeVector localPos;
   G4ThreeVector gpos_v2;
#if 0
   for(int i=100;i<111;i++){
     //100/110 is invalid
     int module = ModuleID_2020to2013_27(i);
     cerr<<"HBD "<<i<<" "<<module<<endl;
   }
#endif
#if 0
   for(int i=100;i<111;i++){
     int module = ModuleID_2020to2013_33(i);
     int layer  =0;

     //     localPos=G4ThreeVector(0,0,0);
     localPos=G4ThreeVector(50,0,0);

     gpos_v2 = geom_v2->GTR(module, layer)->GetGPos(localPos);
     cerr<<"GTR "<<i<<" "<<module<<" "<<layer<<" "<<localPos<<" "<<gpos_v2<<endl;
     gpos_v2 = geom_v2->SSD(module)->GetGPos(localPos);
     cerr<<"SSD "<<i<<" "<<module<<" "<<layer<<" "<<localPos<<" "<<gpos_v2<<endl;
   }
   geom_v2->PrintParams(std::cout);
#endif
#if 0
   for(int i=0;i<11;i++){
     
     int module = ModuleID_2020to2013_33( 105 );
     int layer  =0;
     //     localPos=G4ThreeVector(0,0,0);
     double x = 10*i;
     localPos=G4ThreeVector( x ,0,0);
     cerr<<   geom_v2<<endl;

     gpos_v2 = geom_v2->GTR(module, 1)->GetGPos(localPos);
     cerr<<"GTR "<<i<<" "<<module<<" "<<layer<<" "<<localPos<<" "<<gpos_v2<<endl;
     gpos_v2 = geom_v2->SSD(module)->GetGPos(localPos);
     cerr<<"SSD "<<i<<" "<<module<<" "<<layer<<" "<<localPos<<" "<<gpos_v2<<endl;
   }
#endif

#if 1
  if( argc<=2){
     return 1;
  }
   TFile *file = new TFile(argv[2], "recreate");
   TTree *tree = new TTree("tree", "tree");

   int module, layer, block;
   TVector3 gpos;
   TVector3 lpos;

   tree->Branch("module", &module);
   tree->Branch("layer", &layer);
   tree->Branch("block", &block);
   tree->Branch("lpos", &lpos);
   tree->Branch("gpos", &gpos);

   gRandom->SetSeed(1000);
   std::bitset<64> valid_lg_block;
   for(int i=0; i<6; i++){
      for(int j=0; j<6; j++){
         valid_lg_block.set(i*10+j);
      }
   }
   valid_lg_block.set(26);   valid_lg_block.set(36);

   int n_entries = 100000;
   for(int n=0; n<n_entries; n++){
      if(n%1000==0) std::cout << n << "/" << n_entries << std::endl;
      //layer = gRandom->Integer(7);
      layer = 6; // LG geometry test
      if(layer == 0){
         module = gRandom->Integer(33);
         lpos.SetXYZ(gRandom->Uniform(-25.,25.),gRandom->Uniform(-25.,25.),0);
         gpos = geom_v2->SSD(module)->GetGPos(lpos);
      }else if(layer <= 3){
         module = gRandom->Integer(33);
         lpos.SetXYZ(
               gRandom->Uniform(-50.*(layer),50.*(layer)),
               gRandom->Uniform(-50.*(layer),50.*(layer)),
               gRandom->Uniform(-3.0,+3.0));
         gpos = geom_v2->GTR(module, layer-1)->GetGPos(lpos);
      }else if(layer == 4){
         module = gRandom->Integer(27);
         lpos.SetXYZ(gRandom->Uniform(-300.,300.),gRandom->Uniform(-300.,300.),0);
         gpos = geom_v2->HBD(module)->GetGPos(lpos);
      }else if(layer == 5){
         module = gRandom->Integer(27);
         lpos.SetXYZ(gRandom->Uniform(-350.,350.),gRandom->Uniform(-350.,350.),0);
         gpos = geom_v2->LGVD(module)->GetGPos(lpos);
      }else if(layer == 6){
         module = gRandom->Integer(27);
         block = gRandom->Integer(56);
         while(!valid_lg_block[block]){
            block = gRandom->Integer(56);
         }
         lpos.SetXYZ(gRandom->Uniform(-50.,50.),gRandom->Uniform(-50.,50.),0);
         gpos = geom_v2->LG(module,block)->GetGPos(lpos);
      }
      tree->Fill();
   }
   file->Write();
   file->Close();

   //TVector3 gpos;
   //std::cout << "Layer = " << layer << ", Module = " << module << std::endl;
   //std::cout << "lpos        : "; lpos.Print();
   //std::cout << std::endl;

   //gpos = geom_v1->GetGPos(lpos, layer, module);
   ////std::cout << "lpos (V1) : "; lpos.Print();
   //std::cout << "gpos (V1)   : "; gpos.Print();

   //gpos = geom_v2->GetGPos(lpos, layer, module);
   ////std::cout << "lpos (V2-2) : "; lpos.Print();
   //std::cout << "gpos (V2)   : "; gpos.Print();

#endif
   std::cerr << __func__ << ", " << __FILE__ << ":" << __LINE__ << std::endl;
   delete geom_v2;
   return 0;
}


#if 0
//
// comparison v1 & v2  by W.Nakai
//
int main(int argc, char **argv){
   //E16ANA_GeometryV1 *geom_v1 = new E16ANA_GeometryV1("/ccj/u/E16/database/geometry/geometry_150810.dat");
   E16ANA_GeometryV1 *geom_v1 = new E16ANA_GeometryV1(argv[1]);
   E16ANA_GeometryV2 *geom_v2 = new E16ANA_GeometryV2(argv[2]);
   //geom_v2->SetDesignValues();
   //geom_v2->SetValuesFromV1(geom_v1);

   TFile *file = new TFile(argv[3], "recreate");
   TTree *tree = new TTree("tree", "tree");

   int module, layer;
   TVector3 lpos;
   TVector3 gpos_v1;
   TVector3 gpos_v2;

   tree->Branch("module", &module);
   tree->Branch("layer", &layer);
   tree->Branch("lpos", &lpos);
   tree->Branch("gpos_v1", &gpos_v1);
   tree->Branch("gpos_v2", &gpos_v2);

   gRandom->SetSeed(1000);

   int n_entries = 100000;
   for(int n=0; n<n_entries; n++){
      if(n%1000==0) std::cout << n << "/" << n_entries << std::endl;
      layer = gRandom->Integer(6);
      if(layer < 3){
         module = gRandom->Integer(33);
         lpos.SetXYZ(
               gRandom->Uniform(-50.*(layer+1),50.*(layer+1)),
               gRandom->Uniform(-50.*(layer+1),50.*(layer+1)),
               gRandom->Uniform(-3.0,+3.0));
         gpos_v1 = geom_v1->GetGPos(lpos*0.1, layer, module);
         gpos_v1 = gpos_v1*10.0;
         gpos_v2 = geom_v2->GTR(module, layer)->GetGPos(lpos);
      }else if(layer == 3){
         module = gRandom->Integer(27);
         lpos.SetXYZ(gRandom->Uniform(-300.,300.),gRandom->Uniform(-300.,300.),0);
         gpos_v2 = geom_v2->HBD(module)->GetGPos(lpos);
      }else if(layer == 4){
         module = gRandom->Integer(27);
         lpos.SetXYZ(gRandom->Uniform(-350.,350.),gRandom->Uniform(-350.,350.),0);
         gpos_v2 = geom_v2->LGVD(module)->GetGPos(lpos);
      }else{
         //module = gRandom->Integer(9);
         module = gRandom->Integer(33);
         lpos.SetXYZ(gRandom->Uniform(-25.,25.),gRandom->Uniform(-25.,25.),0);
         gpos_v2 = geom_v2->SSD(module)->GetGPos(lpos);
      }
      tree->Fill();
   }
   file->Write();
   file->Close();

   //TVector3 gpos;
   //std::cout << "Layer = " << layer << ", Module = " << module << std::endl;
   //std::cout << "lpos        : "; lpos.Print();
   //std::cout << std::endl;

   //gpos = geom_v1->GetGPos(lpos, layer, module);
   ////std::cout << "lpos (V1) : "; lpos.Print();
   //std::cout << "gpos (V1)   : "; gpos.Print();

   //gpos = geom_v2->GetGPos(lpos, layer, module);
   ////std::cout << "lpos (V2-2) : "; lpos.Print();
   //std::cout << "gpos (V2)   : "; gpos.Print();

   std::cerr << __func__ << ", " << __FILE__ << ":" << __LINE__ << std::endl;
   delete geom_v1;
   delete geom_v2;

   return 0;
}

#endif
