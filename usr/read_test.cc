#include <fstream>
#include <iostream>
#include <string>

#include "E16DST_DST1.hh"

using namespace std;

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
  auto ssd             = new E16DST_DST1Detector<E16DST_DST1SSDHit, E16DST_DST1SSDCluster>;
  while (!in_file->eof()) {
    record_header->Read(in_file);
    if (in_file->eof()) {
      break;
    }
    auto record_type    = record_header->Type();
    cout << "record type: " << record_type << endl;

    if (record_type == E16DST_DST1Constant::kDetector) {
      
      detector_header->Read(in_file);
      if (detector_header->Check()) {
        cout << "right magic" << endl;
      }
      auto detector_version = detector_header->detector_version;
      auto detector_id      = detector_header->detector_id;
      cout << "detector version: " << detector_version << ", detector ID: " << detector_id << endl;
      if (detector_version == 0) {
        if (detector_id == E16DST_DST1Constant::kSSD) {
          ssd->Read(in_file);
        }
      } else {
        cerr << "invalid detector version: " << detector_version << endl;
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