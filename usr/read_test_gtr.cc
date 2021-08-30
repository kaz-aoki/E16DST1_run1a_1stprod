#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DefaultFilePath.hh"

using namespace std;
using namespace E16DST_DST1Constant;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst1] [max physics event (all: -1)] " << endl;
    return -1;
  }
  auto in_file_name = argv[1];
  auto max_event     = stoi(argv[2]);

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  
  auto in_file = new fstream(in_file_name, ios_base::in | ios_base::binary);
  if (!in_file) {
    cerr << "file can not open" << endl;
    return -1;
  }

  auto record_header = new E16DST_DST1RecordHeader();
//  auto physics_record = new E16DST_DST1PhysicsRecord();
  while (!in_file->eof()) {
    record_header->Read(in_file);
    cout << "run number: " << record_header->RunNumber() << endl;
    if (in_file->eof()) {
      break;
    }
//    physics_record->Clear();
    auto record_type = record_header->Type();
    if (record_type == kPhysics) {
      auto physics_record = new E16DST_DST1PhysicsRecord();
      int tmp = physics_record->Read(in_file);
      auto& gtr = physics_record->GTR();
//      cout << "read size: " << tmp << endl;
//      cout << "number of GTR hits     : " << gtr.NumHits() << endl;
//      cout << "number of GTR clusterss: " << gtr.NumClusters() << endl;
//      auto num_clusters = gtr.NumClusters();
////      auto num_clusters = gtr.NumHits();
//      if (num_clusters != 0) {
//        auto cluster = gtr.Cluster(num_clusters - 1);
////        auto hit = gtr.Hit(num_clusters - 1);
////        gtr.Cluster(num_clusters - 1).Print();
//        cluster.Print();
////        hit.Print();
//      }
//      delete physics_record;
    }
  }
  delete record_header;
//  delete physics_record;

  in_file->close();
  delete in_file;



  delete geometry;
  return 0;
}
