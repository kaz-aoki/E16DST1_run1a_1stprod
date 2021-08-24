#include <fstream>
#include <iostream>
#include <string>

#include "E16DST_DST1.hh"

using namespace std;
using namespace E16DST_DST1Constant;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "./bin [input.dat]" << endl;
    return -1;
  }
  auto in_file_name = static_cast<string>(argv[1]);

  auto in_file = new fstream(in_file_name, ios_base::in | ios_base::binary);
  
  if (!in_file) {
    cerr << "file can not open" << endl;
    return -1;
  }

  auto record_header   = new E16DST_DST1RecordHeader();
  auto detector_header = new E16DST_DST1DetectorHeader();
  while (!in_file->eof()) {
    record_header->Read(in_file);
    if (in_file->eof()) {
      break;
    }
    auto record_type    = record_header->Type();
    auto record_version = record_header->Version();
    cout << "record type: " << record_type << ", record version: " << record_version << endl;

    if (record_type == kDetector && record_version == 0) {
      detector_header->Read(in_file);
      auto detector_version   = detector_header->DetectorVersion();
      auto detector_id        = detector_header->DetectorId();
      auto n_const_components = detector_header->NumConstComponents();
      int  const_component_version[n_const_components];
      int  const_component_id[n_const_components];
      auto n_var_components = detector_header->NumVarComponents();
      int  var_component_version[n_var_components];
      int  var_component_id[n_var_components];
      for (int i = 0; i < n_const_components; ++i) {
        const_component_version[i] = detector_header->ConstComponentVersion(i);
        const_component_id[i]      = detector_header->ConstComponentId(i);
      }
      for (int i = 0; i < n_var_components; ++i) {
        var_component_version[i] = detector_header->VarComponentVersion(i);
        var_component_id[i]      = detector_header->VarComponentId(i);
      }
      cout << "detector version: " << detector_version << ", detector ID: " << detector_id << endl;
      if (const_component_version[0] == 0 && const_component_id[0] == kSSD && var_component_version[0] == 0 && var_component_id[0] == kSSD) {
        auto ssd = reinterpret_cast<E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster>*>(detector_header);
        ssd->Read(in_file);
//      } else if (const_component_version[0] == 0 && const_component_id[0] == kGTR && var_component_version[0] == 0 && var_component_id[0] == kGTR) {
//        auto gtr = reinterpret_cast<E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster>*>(detector_header);
//        gtr->Read(in_file);
      } else if (const_component_version[0] == 0 && const_component_id[0] == kHBD && var_component_version[0] == 0 && var_component_id[0] == kHBD) {
        auto hbd = reinterpret_cast<E16DST_DST1Detector<E16DST_DST1HBDHit, E16DST_DST1HBDCluster>*>(detector_header);
        hbd->Read(in_file);
      } else if (const_component_version[0] == 0 && const_component_id[0] == kLG && var_component_version[0] == 0 && var_component_id[0] == kLG) {
        auto lg = reinterpret_cast<E16DST_DST1Detector<E16DST_DST1LGHit, E16DST_DST1LGCluster>*>(detector_header);
        lg->Read(in_file);
      } else {
        std::cerr << "Invalid E16DST_DST1DetectorHeader value: "
                  << "const component version = "      << const_component_version
                  << ", const component ID = "         << const_component_id
                  << ", variable component version = " << var_component_version
                  << ", variable component ID = "      << var_component_id << std::endl;
        return -1;
      }
    }
  }
  delete record_header;
  delete detector_header;

  in_file->close();
  delete in_file;
  return 0;
}