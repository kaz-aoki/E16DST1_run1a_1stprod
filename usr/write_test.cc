#include <fstream>
#include <iostream>
#include <string>

#include "E16DST_DST1.hh"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "./bin [output.dat]" << endl;
    return -1;
  }
  auto out_file_name = static_cast<string>(argv[1]);

  auto out_file = new fstream(out_file_name, ios_base::out | ios_base::binary);

  auto record_header = new E16DST_DST1RecordHeader();
  record_header->SetType(E16DST_DST1Constant::kDetector);
  cout << record_header->Type() << endl;
  record_header->Write(out_file);
  delete record_header;

  auto detector_header = new E16DST_DST1DetectorHeader();
  detector_header->Write(out_file);
  delete detector_header;

  out_file->close();
  delete out_file;
  return 0;
}