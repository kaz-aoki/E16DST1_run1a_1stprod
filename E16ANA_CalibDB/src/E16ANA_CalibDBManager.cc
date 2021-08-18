//2021-08-11, uploaded by yokkaich
//E16ANA_CalibDBManager.cc 210619 by S. Yokkaichi
//    Last modified at <2021-08-11 20:31:08 >


#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

#include "E16ANA_ErrorMessage.hh" 
#include "E16ANA_CalibDBManager.hh" 
#include "E16DST_DST1DefaultFilePath.hh"

E16ANA_CalibDBManager::E16ANA_CalibDBManager():
  //  DefaultPATH("/e16/u/nakasuga/E16/DST1/E16DST1/E16ANA_CalibDB/calib_database/"), 
  DefaultPATH(static_cast<std::string>(CalibFilePath) + "/"), 
  DefaultCalibDBname("E16calibDB.txt")
{
  E16INFO("DB Initialized");
   currentRunID = 0;
  CalibDBfileSet(DefaultPATH, DefaultCalibDBname);
}
void E16ANA_CalibDBManager::SetRunID(int runID){
    currentRunID = runID; 
    E16INFO("runID= %d",runID);
}
bool E16ANA_CalibDBManager::CalibDBfileResetDefault(){
  E16INFO("DB reset default");
  return CalibDBfileSet(DefaultPATH, DefaultCalibDBname);
}

bool E16ANA_CalibDBManager::CalibDBfileSet(
  string newpath, string newfilename){

  CalibPATH  = newpath;
  CalibDBname= newfilename;
  IndexPATH  = CalibPATH + "/index/";

  string calibDBfullpathname=CalibPATH+CalibDBname;
  E16INFO("DB set by %s", calibDBfullpathname.c_str() );
  return CalibDBFileRead( calibDBfullpathname );

}

bool E16ANA_CalibDBManager::CalibDBfileResetByLocal(
  string newpath, string newfilename){
  E16INFO("DB ResetByLocal");
  return CalibDBfileSet(newpath, newfilename);
}

E16ANA_CalibDBManager& E16ANA_CalibDBManager::Instance() {
    static E16ANA_CalibDBManager singleton;

    //initialized, if not yet
    return singleton;
}

string E16ANA_CalibDBManager::SearchForIndexFileName(string key){
  string indexfilename=calibDB[key];
  if( indexfilename == ""){
    E16FATAL("no key: %s",key.c_str() );
    return "NO-KEY";//no PATH added
  }
  indexfilename=IndexPATH + indexfilename;
  return indexfilename;
}


string E16ANA_CalibDBManager::SearchIndexFileForCalibFileName(string indexfilename, int runID){

  ifstream ifs(indexfilename, ios_base::in);
  if( ! ifs ){
    E16FATAL("indexfile open error: %s", indexfilename.c_str());
    return string("Error-IndexOpen");
  }

  map<int, string> map = ReadFileWithNumberKey( ifs );

  // key is sorted in "map"
  auto item1=map.lower_bound(runID);

  stringstream s;
  string filename, comment;
  s << (string)item1->second;
  s>>filename;
  s>>comment;

  ifs.close();
  return string(CalibPATH + filename);

}

string E16ANA_CalibDBManager::CalibFileName(string key, int runID){
  string indexfilename = SearchForIndexFileName(key);
  string calibfilename("");
  if( indexfilename != "" ){
    calibfilename = SearchIndexFileForCalibFileName(indexfilename, runID);
  }
  return calibfilename;
}

bool E16ANA_CalibDBManager::CalibDBFileRead(string calibDBname){
  ifstream ifs(calibDBname, ios_base::in);
  if( ! ifs ){
    E16FATAL("no such file name for Calib DB: %s", calibDBname.c_str() );
    return false;
  }
  calibDB = ReadFileWithStringKey( ifs ) ;
  ifs.close();
  return true;
}

map<string,string> E16ANA_CalibDBManager::ReadFileWithStringKey( ifstream& ifs) {
  map<string,string> map1;

  if (!ifs){
    E16FATAL("ifs invalid");
    return map1;
  }

  string line;
  int count = 0;
  while( getline(ifs, line) ){
    count ++;
    if( line[0]== '#'  || line.empty() ){
      continue;
    }
    stringstream s;
    s<<line;

    //read from the line first and second columns(string) and discard others
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

map<int,string> E16ANA_CalibDBManager::ReadFileWithNumberKey( ifstream& ifs) {
  map<int,string> map1;

  if (!ifs){
    E16FATAL("ifs invalid");
    return map1;
  }

  string line;
  int count = 0;
  while( getline(ifs, line) ){
    count ++;
    if( line[0]== '#'  || line.empty() ){
      continue;
    }
    stringstream s;
    s<<line;

    //divide the line to first column(number) and others(string w/ " ")
    int number;
    string item;
    s>>number;
    getline( s, item );

    map1[number]=item; 

  }//while


  return map1;
}



//-----------------------------------------------------
FILE* E16ANA_CalibDBManager::CalibFileOpenText(string key, int runID){
  return CalibFileOpen(key, runID, false);
}
FILE* E16ANA_CalibDBManager::CalibFileOpenBinary(string key, int runID){
  return CalibFileOpen(key, runID, true);
}



FILE* E16ANA_CalibDBManager::CalibFileOpenTextByLocalName(string filename){
  return CalibFileOpen( filename, false);
}
FILE* E16ANA_CalibDBManager::CalibFileOpenBinaryByLocalName(string filename){
  return CalibFileOpen( filename, true);
}

FILE* E16ANA_CalibDBManager::CalibFileOpen(string key, int runID, bool binaryflag){
  string filename= CalibFileName(key, runID);
  return CalibFileOpen( filename, binaryflag);
}

FILE* E16ANA_CalibDBManager::CalibFileOpen(string filename, bool binaryflag){
  string option="r";
  if( binaryflag ) {option="rb";}

  if( filename != string("Error-IndexOpen") ){
    FILE* fp = fopen( filename.c_str(), option.c_str()  );
    if( fp != NULL ){
      E16INFO("calib file open: %s", filename.c_str() );
      return fp;
    }
    else{
      E16FATAL("file open error: %s", filename.c_str() );
      return NULL;
    }
  }
  else{//"Error-IndexOpen"
    E16FATAL("calib DB search error: %s", filename.c_str() );
    return NULL;
  }
    
}

//---------------------

ifstream* E16ANA_CalibDBManager::CalibStreamOpenText(string key, int runID){
  return CalibStreamOpen(key, runID, false);
}
ifstream* E16ANA_CalibDBManager::CalibStreamOpenBinary(string key, int runID){
  return CalibStreamOpen(key, runID, true);
}


ifstream* E16ANA_CalibDBManager::CalibStreamOpenTextByLocalName(string filename){
  return CalibStreamOpen( filename, false);
}
ifstream* E16ANA_CalibDBManager::CalibStreamOpenBinaryByLocalName(string filename){
  return CalibStreamOpen( filename, true);
}

ifstream* E16ANA_CalibDBManager::CalibStreamOpen(string key, int runID, bool binaryflag){
  string filename= CalibFileName(key, runID);
  return CalibStreamOpen( filename, binaryflag);
}

ifstream* E16ANA_CalibDBManager::CalibStreamOpen(string filename, bool binaryflag){

  ifstream* ifsp=new ifstream;
  ifstream& ifs = *ifsp;
  
  if( filename != string("Error-Index") ){
    if( binaryflag )
      ifs.open( filename.c_str(), ios::in | ios::binary  );
    else{
      ifs.open( filename.c_str(), ios::in );
    }
    if( ifs  ){
      E16INFO("calib file open: %s", filename.c_str() );
      return ifsp;
    }
    else{
      E16FATAL("file open error: %s", filename.c_str() );
      return NULL;
    }
  }
  else{//"Error-IndexOpen"
    E16FATAL("calib DB search error: %s", filename.c_str() );
    return NULL;
  }

}

