//E16ANA_STSTDCCalibration.cc  260516 K. Aoki
//

#include "E16ANA_ErrorMessage.hh"
#include "E16ANA_STSTDCCalibration.hh"
#include "E16ANA_CalibDBManager.hh"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include <tuple>
#include <stdexcept>

E16ANA_STSTDCCalibration::E16ANA_STSTDCCalibration() {
    Init();
}

E16ANA_STSTDCCalibration::~E16ANA_STSTDCCalibration() {}

bool sts_tdc_table::Load(const std::string& filename){
  std::ifstream fin(filename);
  
  if (!fin) {
    std::cerr << "Cannot open " << filename << std::endl;
    return false;
  }
  
  std::string line;
  
  while (std::getline(fin, line)) {
    if (line.empty()) continue;
    if (line[0] == '#') continue;
    
    std::istringstream iss(line);
    
    int run_begin;
    int run_end;
    
    int mod;
    int pn;

    double peak;
    double mean;
    double sigma;
    
    if (!(iss >> run_begin
	  >> run_end
	  >> mod
	  >> pn
	  >> peak
	  >> mean
	  >> sigma)) {
      continue;
    }
    
    Key key = std::make_tuple(mod, pn);
    
    table_[key].push_back(
			  Entry{
			    run_begin,
			    run_end,
			    mean,
			    sigma
			  }
			  );
  }
  return true;
}

bool sts_tdc_table::Get(int run, int mod, int pn, double& mean, double& sigma) const{
  Key key = std::make_tuple(mod, pn);
  auto it = table_.find(key);
  if (it == table_.end()) {
    return false;
  }
  bool found = false;
  
  int best_width = std::numeric_limits<int>::max();
  for (const auto& e : it->second) {

    if (run < e.run_begin) continue;
    if (run > e.run_end  ) continue;
    
    int width = e.run_end - e.run_begin;
    
    // exact match / narrower range has priority
    if (width < best_width) {
      best_width = width;
      
      mean  = e.mean;
      sigma = e.sigma;
      found = true;
    }
  }
  return found;
}

sts_tdc_table::tdc_calib sts_tdc_table::At(int run, int mod, int pn) const{
  double mean;
  double sigma;
  
  if (!Get(run, mod, pn, mean, sigma)) {
    throw std::runtime_error("TDC calibration not found");
  }
  
  return tdc_calib{mean, sigma};
}

void sts_tdc_table::DEBUG(int run){
  std::cout << "### STSTDC DEBUG OUT" << std::endl;
  for (const auto& kv : table_) {
    int mod = std::get<0>(kv.first);
    int pn  = std::get<1>(kv.first);
    double mean, sigma;
    Get(run,mod,pn,mean,sigma);
    std::cout << mod << " " << pn << "\t" << mean << "\t" << sigma << std::endl;
    /*
    std::stringstream ss;
    int best_width = std::numeric_limits<int>::max();
    bool found = false;
    for (const auto& e : kv.second) {
      if (run < e.run_begin ||
	  run > e.run_end) {
	continue;
      }
      int width = e.run_end-e.run_begin;
      if ( best_width > width ) {
	best_width=width;
	ss.clear();
	ss
	<< "run=" << run
	<< " mod=" << mod
	<< " pn="  << pn
	<< " range=[" << e.run_begin
	<< "," << e.run_end << "]"
	<< " mean="  << e.mean
	<< " sigma=" << e.sigma
	<< std::endl;
      }
    }
    if (found) {
      std::cout << ss.str();
    }
    */
  }
}


bool E16ANA_STSTDCCalibration::ReadConstantDataCore(int _run_id, std::string _index_file_name) {
    run_id = _run_id;
    Init();
    return tdc_table.Load(_index_file_name);
}

bool E16ANA_STSTDCCalibration::ReadConstantData(int run_id) {
  auto& calib = E16ANA_CalibDBManager::Instance();
  std::cout << "E16ANA_STSTDCCalibration::ReadConstantData  run_id = " << run_id << std::endl;
  auto index_file_name = calib.CalibFileName("STS-tdccalib", run_id);
  std::cout << "E16ANA_STSTDCCalibration index_file " << index_file_name << std::endl;
  return ReadConstantDataCore(run_id, index_file_name);
}

bool E16ANA_STSTDCCalibration::Get(int mod,int pn, double &mean, double &sigma) const{
  return tdc_table.Get(run_id,mod,pn,mean,sigma);
}

void E16ANA_STSTDCCalibration::Init() {
  // Erase the calib data
  tdc_table.Clear();
}
