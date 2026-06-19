//E16ANA_STSGlobalGeometryCalib.cc 251231 by K.Aoki
//    Last modified at <2025-12-31 10:56:30 >
//

#include "E16ANA_ErrorMessage.hh"
#include "E16ANA_STSGlobalGeometry_v2.hh"
#include "E16ANA_STSGlobalGeometryCalib.hh"
#include "E16ANA_CalibDBManager.hh"
#include "exprtk.hpp"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>

E16ANA_STSGlobalGeometryCalib::E16ANA_STSGlobalGeometryCalib() {
    Init();
}

E16ANA_STSGlobalGeometryCalib::~E16ANA_STSGlobalGeometryCalib() {}

bool E16ANA_STSGlobalGeometryCalib::ReadConstantDataCore(int _run_id, std::string _index_file_name) {
  run_id = _run_id;
  auto& calib = E16ANA_CalibDBManager::Instance();

  Init();

  ////// Read the file
  std::ifstream fin(_index_file_name);
  if (!fin) {
    std::cerr << __func__ << " invalid STS GlobalGeometry calibration filename: " << _index_file_name << std::endl;
    return false;
  }
  std::vector<std::vector<std::string>> data;
  std::string line;
  
  while (std::getline(fin, line)) {
    if ( line.empty() ) continue;
    if ( line[0] == '#' ) continue;
    // std::cout << "DEBUG :" << line << std::endl;
    std::stringstream ss(line);
    std::string cell;
    std::vector<std::string> row;
    
    while (std::getline(ss, cell, ',')) {
      row.push_back(cell);
    }
    data.push_back(row);
  }

  // analyze calib data

  auto is_valid_module = [](int mod) {
    if ( mod == 105 ) return false;
    if ( mod >=1 && mod <= 9 ) return true;
    if ( mod >=101 && mod <= 109 ) return true;
    if ( mod >=201 && mod <= 209 ) return true;
    return false;
  };
  // mod, radius, angle, dy, bSpin
  for( auto x: data ){
    if ( x.size() == 0 ) continue;
    if (x.size() < 5 ) {
      std::cout << "Invalid calib format." << std::endl;
      continue;
    }
    
    // DEBUG output
    //for( int i = 0;i<5;i++) std::cout << x[i] << " " << std::endl;
    //std::cout << std::endl;
    
    try {
      int mod = std::stoi(x[0]);
      if ( ! is_valid_module(mod) ) {
	throw std::invalid_argument("Illegal module number");
      }

      auto evaluate_expression = [](std::string str)->double{
	typedef exprtk::expression<double> expression_t;
	typedef exprtk::parser<double> parser_t;

	expression_t expression;
	parser_t parser;

	if ( !parser.compile(str, expression)) {
	  throw std::invalid_argument("Illegal expression");
	}
	return expression.value();
      };

      double radius = evaluate_expression(x[1]);
      double angle = evaluate_expression(x[2]);
      double dy = evaluate_expression(x[3]);

      //double radius = std::stod(x[1]);
      //double angle = std::stod(x[2]);
      //double dy = std::stod(x[3]);
      
      bool bSpin = true;
      if ( x[4].find("true") != std::string::npos ){
	bSpin = true;
      }else if ( x[4].find("false") != std::string::npos) {
	bSpin = false;
      }else{
	throw std::invalid_argument("bSpin must be true or false");
      }
      E16ANA_STSGlobalSensorGeom sg;
      sg.mod = mod;
      sg.radius = radius;
      sg.angle = angle;
      sg.dy = dy;
      sg.bSpin = bSpin;
      map_sg[mod] = sg;
    }catch  (const std::exception& e){
      std::cout << e.what() << std::endl;
    }
  }
  
  //  DEBUG output
  std::cout << "Evaluated values " << std::endl;
  for( auto x : map_sg ) {
    std::cout << x.second.mod << ": "
	      << x.second.radius << ","
	      << x.second.angle << ", "
	      << x.second.dy << ","
	      << x.second.bSpin
	      << std::endl;
  }
  return true;
}

bool E16ANA_STSGlobalGeometryCalib::ReadConstantData(int run_id) {
  auto& calib = E16ANA_CalibDBManager::Instance();
  std::cout << "E16ANA_STSGlobalGeometryCalib::ReadConstantData  run_id = " << run_id << std::endl;
  auto index_file_name = calib.CalibFileName("STS-ggeomcalib", run_id);
  std::cout << "E16ANA_STSGlobalGeometryCalib index_file " << index_file_name << std::endl;
  auto ret =  ReadConstantDataCore(run_id, index_file_name);
  E16ANA_STSGlobalGeometry_v2* ggeom = dynamic_cast<E16ANA_STSGlobalGeometry_v2*>(E16ANA_STSGlobalGeometry_v2::instance());
  ggeom->set_calib(*this);
  return ret;
}

bool E16ANA_STSGlobalGeometryCalib::ReadConstantDataByLocal(int run_id, std::string index_file_name) {
  return ReadConstantDataCore(run_id, index_file_name);
}

void E16ANA_STSGlobalGeometryCalib::Init() {
  map_sg.clear();
}
