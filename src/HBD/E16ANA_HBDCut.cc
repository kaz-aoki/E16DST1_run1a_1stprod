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

  return true;
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
      if(keyword.compare("tdc_range_upper") == 0) tdc_range_upper = value;
      if(keyword.compare("tdc_range_lower") == 0) tdc_range_lower = value;
      if(keyword.compare("th_wf_chi2") == 0) th_wf_chi2 = value;
      if(keyword.compare("th_csize_dst1") == 0 ) th_csize_dst1 = (int) value;
      if(keyword.compare("th_ccharge_dst1") == 0 ) th_ccharge_dst1 = value;
      if(keyword.compare("n_sigma_cadc") == 0 ) n_sigma_cadc = value;
      if(keyword.compare("clustering_time_window_start") == 0) clustering_time_window[0]= value;
      if(keyword.compare("clustering_time_window_end") == 0) clustering_time_window[1] = value;
    }
    return true;
  }
  else{
    std::cerr<<__func__<<" invalid cut filename"<<std::endl;
    return false;
  }
}

void E16ANA_HBDCut::SetCut(const char *cut_keyword, const double value){
  
  std::string keyword = cut_keyword;
  
  if(keyword.compare("n_sigma_wf_dst1") == 0 ) n_sigma_wf_dst1 = value;
  if(keyword.compare("n_waves_dst1") == 0 ) n_waves_dst1 = (int) value;
  if(keyword.compare("tdc_range_upper") == 0) tdc_range_upper = value;
  if(keyword.compare("tdc_range_lower") == 0) tdc_range_lower = value;
  if(keyword.compare("th_wf_chi2") == 0) th_wf_chi2 = value;
  if(keyword.compare("th_csize_dst1") == 0 ) th_csize_dst1 = (int) value;
  if(keyword.compare("th_ccharge_dst1") == 0 ) th_ccharge_dst1 = value;
  if(keyword.compare("n_sigma_cadc") == 0 ) n_sigma_cadc = value;
  if(keyword.compare("clustering_time_window_start") == 0) clustering_time_window[0] = value;
  if(keyword.compare("clustering_time_window_end") == 0) clustering_time_window[1] = value;
}

double E16ANA_HBDCut::GetCut(const char *cut_keyword){
  
  std::string keyword = cut_keyword;
  
  if(keyword.compare("n_sigma_wf_dst1") == 0 ) return n_sigma_wf_dst1;
  if(keyword.compare("n_waves_dst1") == 0 ) return (double) n_waves_dst1;
  if(keyword.compare("tdc_range_upper") == 0) return tdc_range_upper;
  if(keyword.compare("tdc_range_lower") == 0) return tdc_range_lower;
  if(keyword.compare("th_wf_chi2") == 0) return th_wf_chi2;
  if(keyword.compare("th_csize_dst1") == 0 ) return (double) th_csize_dst1;
  if(keyword.compare("th_ccharge_dst1") == 0 ) return th_ccharge_dst1;
  if(keyword.compare("n_sigma_cadc") == 0 ) return n_sigma_cadc;
  if(keyword.compare("clustering_time_window_start") == 0) return clustering_time_window[0];
  if(keyword.compare("clustering_time_window_end") == 0) return clustering_time_window[1];
  
  return 0;
}
