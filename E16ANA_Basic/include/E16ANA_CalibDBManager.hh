//2021-08-11, uploaded by yokkaich
//E16ANA_CalibDBManager.hh 210619 by S. Yokkaichi
//    Last modified at <2021-08-11 20:32:15 >
//

#if 0
CalibDBManager memo
----------------------------------------------
- singleton
    for global-ness
    unity is not so required

- file hierarchy
1) calibDB file : top of the file-hierarchy
  key-value set
  key (detector+function) - index file name
  -  use default file
   reset (reopen):  CalibDBfileResetByLocal()

   symbolic link 
    E16CalibDB.txt -> E16CalibDB-yymmdd.txt

2) index file 
     runnumber to calibration filename
   format:
     DET-XXX       filename1
    e.g. SSD-pedestal  SSD-pedestal.txt

2a) index file for simple constant
     runnumber to simple calibration constants
   format:
     DET-XXX     const1 const2 ....
     e.g. SSD-time    timegain timeoffset

3) calibration data file
     format should be decided by each Detector
     binary file is recommended for large numbers of channel.


- directory/filename  convention
  - calibDB file
   calib/E16calibDB.txt
  - index file
   calib/index/index-key-uploadDate.txt
     key: detector-subcategory
  - calibration data file
   calib/(detector)/(sub)/yymmdd/key-runID-yymmdd.txt
   calib/SSD/pedestal/210619/SSD-pedstal-run9999-210619.dat

- filename convention in the index file
   subdirectory name (under calib/) should be included as
   SSD/pedestal/210619/SSD-pedstal-run9999-210619.dat
       
- filename convention for extention
     *.txt: text
     *.dat: binary

- full-path completion
     topdir (CalibPATH) /e16/u/nakasuga/E16/DST1/E16DST1/E16ANA_CalibDB/calib_database/
   should be changed when other site as KEKCC/Hokusai

----------------------------------------------
#endif

#ifndef E16ANA_CalibDBManager_h
#define E16ANA_CalibDBManager_h 

#include <stdio.h>

#include <string>
#include <iostream>
#include <fstream>
#include <map>

class E16ANA_CalibDBManager{

public:
  static E16ANA_CalibDBManager& Instance();
  static E16ANA_CalibDBManager& Instance(std::string& path, std::string& file_name);
private:
  const std::string DefaultPATH;
  const std::string DefaultCalibDBname;
  std::string CalibPATH;
  std::string IndexPATH;
  std::string CalibDBname;

  E16ANA_CalibDBManager( const E16ANA_CalibDBManager& );
  E16ANA_CalibDBManager( );

  static E16ANA_CalibDBManager singleton;

  bool CalibDBFileRead(std::string filename);

  std::map<std::string, std::string>  calibDB;
  // map of keyword & indexfilename
  bool CalibDBfileSet(std::string newpath, std::string newfilename);
  int currentRunID;

  std::string SearchIndexFileForCalibFileName(std::string indexfilename, int runID);

  FILE*     CalibFileOpen(std::string key, int runID, bool binaryflag);
  FILE*     CalibFileOpen(std::string filename,  bool binaryflag);
  std::ifstream*     CalibStreamOpen(std::string key, int runID, bool binaryflag);
  std::ifstream*     CalibStreamOpen(std::string filename,  bool binaryflag);

public:
  int CurrentRunID(){ return currentRunID; }//default is 0, set in constructor
  void SetRunID(int runID); //should be set around run-header, or beginning of program
  bool CalibDBfileResetByLocal(std::string newpath, std::string newfilename);
  bool CalibDBfileResetDefault();

  //enum{NOCalibFile=1, NOindexFile=2, NOrunID=3, NOCalibFile=4};

  //user of this class can use indexfile to follow
  //the simple run-dependent constant.
  //below three are the tool for that, as shown in the SSDcalib.hh/cc
  //
  std::string SearchForIndexFileName(std::string key);
  std::map<std::string,std::string> ReadFileWithStringKey( std::ifstream& ifs) ;
  std::map<int,std::string> ReadFileWithNumberKey( std::ifstream& ifs) ;

  //user of this class can use FILE* by CalibFileOpenXX below, 
  //or get filename by CalibFileName()  and open by themselves
  //in the 'Detector'calib.cc/hh as SSDcalib.cc/hh
  //
  std::string CalibFileName(std::string key, int runID);

  FILE*     CalibFileOpenText(std::string key, int runID);
  FILE*     CalibFileOpenBinary(std::string key, int runID);
  FILE*     CalibFileOpenText(std::string key);
  FILE*     CalibFileOpenBinary(std::string key);
  //to develop the calibfile by local environment
  FILE*     CalibFileOpenTextByLocalName(std::string localfilename);
  FILE*     CalibFileOpenBinaryByLocalName(std::string localfilename);

  std::ifstream*     CalibStreamOpenText(std::string key, int runID);
  std::ifstream*     CalibStreamOpenBinary(std::string key, int runID);
  std::ifstream*     CalibStreamOpenText(std::string key);
  std::ifstream*     CalibStreamOpenBinary(std::string key);
  //to develop the calibfile by local environment
  std::ifstream*     CalibStreamOpenTextByLocalName(std::string localfilename);
  std::ifstream*     CalibStreamOpenBinaryByLocalName(std::string localfilename);


};


#endif// E16ANA_CalibDBManager_h


