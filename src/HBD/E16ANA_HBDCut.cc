#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_HBDCut.hh"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

E16ANA_HBDCut::E16ANA_HBDCut()
{
}

E16ANA_HBDCut::~E16ANA_HBDCut()
{
}

bool E16ANA_HBDCut::ReadCutData(const int runID){
  E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
  
  std::string hbd_cut_file = calib.CalibFileName("HBD-cut", runID);
  
  this->ReadFile(hbd_cut_file.c_str());
}

bool E16ANA_HBDCut::ReadFile(const char *filename){
  std::ifstream fin(filename);
  
  if( fin ){
    std::string buf_line;
    for(;;){
      if(fin.eof()) break;
      std::getline(fin, buf_line);

      if(buf_line[0] == '#' || buf_line[0] == '\0') continue;

      std::stringstream ss(buf_line);
      std::string keyword;
      double value;
      ss>>keyword>>value;
      if(keyword.compare("n_sigma_wf_dst1") == 0 ) n_sigma_wf_dst1 = value;
      if(keyword.compare("n_waves_dst1") == 0 ) n_waves_dst1 = (int) value;
      if(keyword.compare("th_csize_dst1") == 0 ) th_csize_dst1 = (int) value;
      if(keyword.compare("th_ccharge_dst1") == 0 ) th_ccharge_dst1 = value;
      if(keyword.compare("n_sigma_cadc") == 0 ) n_sigma_cadc = value;
    }
    return true;
  }
  else{
    std::cerr<<__func__<<" invalid cut filename"<<std::endl;
    return false;
  }
}
