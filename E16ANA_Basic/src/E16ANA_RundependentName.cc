//2021-09-12, uploaded by yokkaich
//E16ANA_RundependentName.cc 210912 by S. Yokkaichi
//    Last modified at <2021-09-12 22:18:26 >
//

#include "E16ANA_ErrorMessage.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_RundependentName.hh"

#include <sstream>
 
using namespace std;

E16ANA_RundependentName& E16ANA_RundependentName::Instance() {
    static E16ANA_RundependentName singleton;
    return singleton;
}

E16ANA_RundependentName::E16ANA_RundependentName() {
  UNCHENGED=string("unchanged");
  runidCache["geometry"]=0;
  runidCache["fieldmap"]=0;
  nameCache["geometry"]="not initialized";
  nameCache["fieldmap"]="not initialized";
}

string E16ANA_RundependentName::SearchIndexFileForName(string indexfilename, int runID){
  //modified from  E16ANA_CalibDBManager::SearchIndexFileForCalibFileName()

  ifstream ifs(indexfilename, ios_base::in);
  if( ! ifs ){
    E16FATAL("indexfile open error: %s", indexfilename.c_str());
    return string("Error-IndexOpen");
  }

  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();
  map<int, string> map = calib.ReadFileWithNumberKey( ifs );

  // key is sorted in "map"
  auto item1=map.lower_bound(runID);

  stringstream s;
  string name, comment;
  s << (string)item1->second;
  s>>name;
  s>>comment;

  ifs.close();
  return string(name);

}

string E16ANA_RundependentName::ReadNameWithRunID(int irunID, string key, string path){
  if ( runidCache[ key ] == irunID ){
    E16INFO("runID %d is same for the key %s: file is not read:", 
      irunID, key.c_str() );
    return UNCHENGED;
  }
  else{
    runidCache[ key ] == irunID ;
  }

  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();

  string  indexfilename = calib.SearchForIndexFileName(key);
  string name = SearchIndexFileForName( indexfilename, irunID );

  if( name == nameCache[key] ){
    return UNCHENGED;
  }
  else{
    nameCache[key]=name;
    name = path + name;
    return name;
  }

}


