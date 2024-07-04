//E16ANA_STSDeadChannel.cc 240626 by R.Yamada
//    Last modified at <2024-06-26 20:33:31 >
//

#include "E16ANA_ErrorMessage.hh"
#include "E16ANA_STSDeadChannel.hh"
#include "E16ANA_CalibDBManager.hh"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

E16ANA_STSDeadChannel::E16ANA_STSDeadChannel() {
    Init();
}

E16ANA_STSDeadChannel::~E16ANA_STSDeadChannel() {}

bool E16ANA_STSDeadChannel::ReadConstantDataCore(int _run_id, std::string _index_file_name) {
    run_id = _run_id;
    auto& calib = E16ANA_CalibDBManager::Instance();

    Init();

    std::ifstream fin(_index_file_name);
    if (!fin) {
        std::cerr << __func__ << " invalid dead channel filename: " << _index_file_name << std::endl;
        return false;
    }

    std::string buf_line;
    while (std::getline(fin, buf_line)) {
        if (buf_line.empty() || buf_line[0] == '#') continue; // Skip comment or empty line

        std::stringstream ss(buf_line);
        uint16_t module_id, pol_id, ch_id;
        int ch_status;
        ss >> module_id >> pol_id >> ch_id >> ch_status;

        int k_module_id = ConvertModuleID(module_id);
        if (k_module_id != -1) {
            status[k_module_id][pol_id][ch_id] = ch_status;
        }
    }
    return true;
}

bool E16ANA_STSDeadChannel::ReadConstantData(int run_id) {
    auto& calib = E16ANA_CalibDBManager::Instance();
    auto index_file_name = calib.SearchForIndexFileName("STS-deadch");
    return ReadConstantDataCore(run_id, index_file_name);
}

bool E16ANA_STSDeadChannel::ReadConstantDataByLocal(int run_id, std::string index_file_name) {
    return ReadConstantDataCore(run_id, index_file_name);
}

bool E16ANA_STSDeadChannel::IsOK(const uint16_t module_id, const uint16_t pol_id, const uint16_t ch_id) const {
    int k_module_id = ConvertModuleID(module_id);
    return status[k_module_id][pol_id][ch_id] == 0;
}

bool E16ANA_STSDeadChannel::IsDead(const uint16_t module_id, const uint16_t pol_id, const uint16_t ch_id) const {
    int k_module_id = ConvertModuleID(module_id);
    return status[k_module_id][pol_id][ch_id] == 1;
}

bool E16ANA_STSDeadChannel::IsNoisy(const uint16_t module_id, const uint16_t pol_id, const uint16_t ch_id) const {
    int k_module_id = ConvertModuleID(module_id);
    return status[k_module_id][pol_id][ch_id] == 2;
}

bool E16ANA_STSDeadChannel::IsHot(const uint16_t module_id, const uint16_t pol_id, const uint16_t ch_id) const {
    int k_module_id = ConvertModuleID(module_id);
    return status[k_module_id][pol_id][ch_id] == 3;
}

int E16ANA_STSDeadChannel::ConvertModuleID(uint16_t module_id) const {
    std::vector<uint16_t> k_module_ids = {101, 102, 103, 104, 106, 107, 108, 109, 206, 207};

    for (int i = 0; i < k_module_ids.size(); ++i) {
        if (k_module_ids[i] == module_id) {
            return i;
        }
    }
    std::cerr << "Invalid module_id: " << module_id << std::endl;
    return -1;
}

void E16ANA_STSDeadChannel::Init() {
    for (uint16_t i = 0; i < n_modules; ++i) {
        for (uint16_t j = 0; j < 2; ++j) {
            for (uint16_t k = 0; k < n_channels; ++k) {
                status[i][j][k] = 0; // Set default status to 0
            }
        }
    }
}
