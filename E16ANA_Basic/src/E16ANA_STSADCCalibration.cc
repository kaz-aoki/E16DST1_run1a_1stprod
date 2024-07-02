//E16ANA_STSADCCalibration.cc 240627 by R.Yamada
//    Last modified at <2024-06-27 20:33:31 >
//

#include "E16ANA_ErrorMessage.hh"
#include "E16ANA_STSADCCalibration.hh"
#include "E16ANA_CalibDBManager.hh"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>

E16ANA_STSADCCalibration::E16ANA_STSADCCalibration()
{
    Init();
}

E16ANA_STSADCCalibration::~E16ANA_STSADCCalibration()
{
}

bool E16ANA_STSADCCalibration::ReadFile(const char *filename){
    Init();

    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << __func__ << " invalid dead channel filename: " << filename << std::endl;
        return false;
    }

    std::string buf_line;
    while (std::getline(fin, buf_line)) {
        if (buf_line.empty() || buf_line[0] == '#') continue; //skip comment or empty line

        std::stringstream ss(buf_line);
        uint16_t module_id, pol_id, ch_id, adc_id;
        float corr_fc;
        ss >> module_id >> pol_id >> ch_id >> adc_id >> corr_fc;

        int k_module_id = ConvertModuleID(module_id);
        if (k_module_id != -1) {
            status[k_module_id][pol_id][ch_id][adc_id] = std::round(corr_fc * 100.0f) / 100.0f;
        }
    }
    return true;
}

//============================================================
bool E16ANA_STSADCCalibration::ReadADCCalibData(const int runID){
    E16ANA_CalibDBManager &calib = E16ANA_CalibDBManager::Instance();
    std::string sts_adc_calibration_file = calib.CalibFileName("STS-adccalib", runID);
    this->ReadFile(sts_adc_calibration_file.c_str());
    return true;
}

//============================================================

float E16ANA_STSADCCalibration::GetCorrespondingCharge(uint16_t module_id, uint16_t pol_id, uint16_t ch_id, uint16_t adc_id) const {
    int k_module_id = ConvertModuleID(module_id);
    if (k_module_id != -1) {
        return status[k_module_id][pol_id][ch_id][adc_id];
    } else {
        return -10000.0f; // or some other error value
    }
}

//==============================================================
int E16ANA_STSADCCalibration::ConvertModuleID(uint16_t module_id) const {
    std::vector<uint16_t> k_module_ids = {101, 102, 103, 104, 106, 107, 108, 109, 206, 207};//using mod

    for (int i = 0; i < k_module_ids.size(); ++i) {
        if (k_module_ids[i] == module_id) {
            return i;
        }
    }
    std::cerr << "Invalid module_id: " << module_id << std::endl;
    return -1;
}

//===============================================================
void E16ANA_STSADCCalibration::Init(){
    for (uint16_t i = 0; i < n_modules; ++i) {
        for (uint16_t j = 0; j < 2; ++j) {
            for (uint16_t k = 0; k < n_channels; ++k) {
                for (uint16_t l = 0; l < n_adc_channels; ++l) {
                    status[i][j][k][l] = -10000.;// Set default status to -10000
                }
            }
        }
    }
}

