//2020-09-16, uploaded by yokkaich
//2020-08-30, uploaded by yokkaich
//2016-05-02, uploaded by nakai
//2016-04-01, uploaded by nakai
//2015-11-02, uploaded by yokkaich
//2015-11-02, uploaded by komatsu
//2015-08-20, uploaded by yokkaich
//2015-07-15, uploaded by nakai
//2015-03-27, uploaded by yokkaich
//2015-01-05, modified by yokkaich
//2015-01-05, modified by yokkaich
//2014-08-27, modified by kawama
//2014-05-07, modified by kawama
//2014-04-30, modified by kawama
//2014-04-24, modified by kawama
//2013-11-14, modified by kawama
//2013-05-13, modified by kawama
/*
//E16ANA_ParamManager.cc 150104 by S. Yokkaichi
//    Last modified at <>
//

   */


#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;

#include "E16ANA_ErrorMessage.hh" 
#include "E16ANA_ParamManager.hh" 

ofstream LogFile;
namespace{
   const int SizeOfBuffer = 144;
}

#if 0


map<string,string> ReadFileWithKey( ifstream& ifs) {
  map<string,string> map1;

  if (!ifs){
    cerr<<""<<endl;
    return map1;
  }

  string tmp;
  int count = 0;
  while( getline(ifs, tmp) ){
    count ++;
    if( tmp[0]== '#'  || tmp.empty() ){
      continue;
    }
    stringstream s;
    s<<tmp;
    string key, item;
    s>>key;
    s>>item;
    map1[key]=item;

  }//while

#if 0
  for( auto item =  map1.begin() ; item !=map1.end() ; item ++){
    cerr<<"map "<<item->first<<" "<<item->second <<endl;
  }
#endif

  return map1;

}
void ChannelMapInit(string*  names){

#if 0
  string dir="./channel_map/Trigger/";
  string trg_gtr_file=dir+"trgGtr.txt";
  string trg_hbd_file=dir+"trgHbd.txt";
  string trg_lgc_file=dir+"trgLgc.txt";
#endif
  string trg_gtr_file;
  string trg_hbd_file;
  string trg_lgc_file;

  ifstream mapconfigfile;
  string configfilename;

  mapconfigfile.open(localconfigfilename);

  if( ! mapconfigfile ){ // read customized local file
      mapconfigfile.open(defaultconfigfilename);
      configfilename = defaultconfigfilename;
  }
  else{
      configfilename = localconfigfilename;
  }
  if( ! mapconfigfile ){
    cerr<<"cannot open any config file"<<endl;
    cerr<<"    local:"<<localconfigfilename<<endl;
    cerr<<"  defailt:"<<defaultconfigfilename<<endl;
    cerr<<"exit"<<endl;exit(1);
  }

  map<string, string> filelist = ReadFileWithKey( mapconfigfile );
  if( filelist.count("GTR")+  filelist.count("HBD")+  filelist.count("LGC") != 3 ){
    cerr<<"exit: mapconfigfile error: number of items "<<filelist.size()<<" items:"<<configfilename <<endl;
    cerr<<"  GTR "<<filelist["GTR"]<<endl;
    cerr<<"  HBD "<<filelist["HBD"]<<endl;
    cerr<<"  LGC "<<filelist["LGC"]<<endl;
    exit(1);
  }

  trg_gtr_file = filelist["GTR"];
  trg_hbd_file = filelist["HBD"];
  trg_lgc_file = filelist["LGC"];


|

#endif





/////////////////////////////////////////
E16ANA_ParamManager *E16ANA_ParamManager::thisPointer=0;
/////////////////////////////////////////

//////////////////////////////////////////////////////
   E16ANA_ParamManager::E16ANA_ParamManager( const char *parFileName )
: fileName(parFileName)
   //////////////////////////////////////////////////////
{
   ReadParam();
   LogFile.open(LogFileName);
   LogFile << "Field Map : "<<MapFileName <<endl;
   LogFile << "Geometry Map : "<<GeomFileName <<endl;

   thisPointer = this;
}






/////////////////////////////
bool E16ANA_ParamManager::ReadParam()
   ////////////////////////////
{
   // define initial value
   strcpy( ROOTFileName, "root/test.root" );
   strcpy( InputDataName, "" );
   GenerationID = 0;
   // ID = 0 : pi-e uniform
   // ID = 1 : from file
   // ID = 2 : Beam 
   ParticleID = 1;
   // ID = 0 : geantino
   // ID = 1 : Electron 
   ipFlag=0;
   evStart=0;
   //ipFlag==0 : bylinear interpolation
   //ipFlag==1 : (pseudo-)bycubic interpolation
   rseed = 1;

   //CutValue = 0.001;
   //Edet = 0.2;
   //ThetaLimit = 3.14;

   FILE *fp = fopen( fileName, "r" );
   if( !fp ){
     E16WARNING("file open error:%s",fileName);
      cerr << "E16ANA_ParamManager: file open fail \"" << fileName << "\"" 
         << endl;
      exit( -1 );
   }

   char str[SizeOfBuffer];
   char str1[SizeOfBuffer];
   int id;

   while( fgets( str, SizeOfBuffer, fp ) ){
     if( str[0] == '#' ) {continue;} //for the comment line

      if( sscanf( str, "Field Map: %s %d", str1, &ipFlag )==2 ){
         strcpy( MapFileName, str1 );
      }
      else if( sscanf( str, "Geometry Data: %s", str1 )==1 ){
         strcpy( GeomFileName, str1 );
      }
      else if( sscanf( str, "GTR100 Analyzer Parameters: %s %d", str1, &id )==2 ){
         if(id<maxGTRId) strcpy(GTR100AnalysisParamFileName[id], str1);
      }
      else if( sscanf( str, "GTR200 Analyzer Parameters: %s %d", str1, &id )==2 ){
         if(id<maxGTRId) strcpy(GTR200AnalysisParamFileName[id], str1);
      }
      else if( sscanf( str, "GTR300 Analyzer Parameters: %s %d", str1, &id )==2 ){
         if(id<maxGTRId) strcpy(GTR300AnalysisParamFileName[id], str1);
      }
      else if( sscanf( str, "GTR100 Response Parameters: %s %d", str1, &id )==2 ){
         if(id<maxGTRId) strcpy(GTR100ResponseParamFileName[id], str1);
      }
      else if( sscanf( str, "GTR200 Response Parameters: %s %d", str1, &id )==2 ){
         if(id<maxGTRId) strcpy(GTR200ResponseParamFileName[id], str1);
      }
      else if( sscanf( str, "GTR300 Response Parameters: %s %d", str1, &id )==2 ){
         if(id<maxGTRId) strcpy(GTR300ResponseParamFileName[id], str1);
      }
   }

   return true;
}
