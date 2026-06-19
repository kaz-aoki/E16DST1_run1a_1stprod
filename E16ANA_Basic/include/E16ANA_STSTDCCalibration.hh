//E16ANA_STSADCCalibration.hh 260516 K. Aoki
//

#ifndef E16ANA_STSTDCCALIBRATION_HH
#define E16ANA_STSTDCCALIBRATION_HH

#include <string>
#include <vector>
#include <cstdint>

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <tuple>
#include <limits>
#include <stdexcept>

class sts_tdc_table
{
public:
    struct tdc_calib {
        double mean;
        double sigma;
    };

    struct Entry {
        int run_begin;
        int run_end;

        double mean;
        double sigma;
    };

public:
  void Clear(){
    table_.clear();
  }
  void DEBUG(int run);
  
  bool Load(const std::string& filename);
  bool Get(int run, int mod, int pn, double& mean, double& sigma) const;
  tdc_calib At(int run, int mod, int pn) const;
private:
    // key = (mod, pn)
    using Key = std::tuple<int,int>;
    std::map<Key, std::vector<Entry>> table_;

};

class E16ANA_STSTDCCalibration {
public:
    E16ANA_STSTDCCalibration();
    ~E16ANA_STSTDCCalibration();

  bool ReadConstantData(int run_id);
  bool Get(int mod, int pn, double&mean, double& sigma) const;
  void DEBUG(){
    tdc_table.DEBUG(run_id);
  }
private:
  bool ReadConstantDataCore(int _run_id, std::string _index_file_name);
  void Init();
  
  sts_tdc_table tdc_table;
  int run_id;
};


#endif // E16ANA_STSTDCCALIBRATION_HH
