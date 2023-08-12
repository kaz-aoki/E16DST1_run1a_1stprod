#include <stdlib.h>
#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TCanvas.h>
#include <regex>
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "GTR/GTRCheckHist.hh"
#include "E16ANA_TargetInfo.hh"
#include "E16ANA_RundependentName.hh"
#include "straight_track/StraightTrackAnalyzerV0.h"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16ANA_GTRStatus.h"
#include "E16ANA_GTRChannelManager.h"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"
#include "E16ANA_LGConstant.hh"
#include "E16ANA_LGDeadChannel.hh"
#include "E16ANA_LGClustering.hh"
#include "E16ANA_LGStraightProj.hh"
#include "straightRoot.hh"
#include "E16DST_Constant.hh"
using namespace std;

int main(int argc, char* argv[]){
   if (argc != 6) {
      cerr << "Invalid argc: " << argc << endl;
      cerr << "./bin [input.dst0] [output.dst1] [run_num] [max physics event (all: -1)] [     removed_layer (-1 = all, 0, ssd, 1,2,3 = gtr)]" << endl;
      return 1;
    }
     auto dst0 = new E16DST_DST0();
    if (!dst0->Open(argv[1], E16DST_DST0::ReadMode)) {
      std::cout << "failed to open file : " << argv[1]  <<std::endl;
      exit(1);
  //    return 1;
    }
    string in_file_name = argv[1];
    string out_file_name = argv[2];
    auto in_run_id        = stoi(argv[3]);
    auto max_event     = stoi(argv[4]);
    auto removed_layer = stoi(argv[5]);
 
  //run0c
  //  int sink_id_pos = in_file_name.length() - 10;
  //  string sink_id = in_file_name.substr(sink_id_pos, 1);
  //  std::cout << "sink id = " << sink_id << std::endl;
  //  int smallest_id_pos = in_file_name.length()-8;
  //  string smallest_id = in_file_name.substr(smallest_id_pos, 3);
  //  std::cout << "smallest  id = " << smallest_id << std::endl;
  //  string runnum = argv[3];
  //  string rem    = argv[5];
  //  string run = "g4run0" + runnum + "exGTR" + rem;
  //  string outputfile = "./dst1_test/" + run + "_sink" + sink_id +"_"+ smallest_id+".ro     ot";
  //  const char* c_out = outputfile.c_str();
 
  //run0d
    std::regex re_run("run(\\d+)");
    std::regex re_sink("sink(\\d+)");
    std::regex re_dst("_(\\d+).dst0");
    std::smatch match_run;
    std::smatch match_sink;
    std::smatch match_dst;
    std::string run_num;
    std::string sink_id;
    std::string smallest_id;
    if(std::regex_search(in_file_name, match_run, re_run)){
        run_num = match_run.str(1);
    }
    if (std::regex_search(in_file_name, match_sink, re_sink)) {
        sink_id = match_sink.str(1);
    }
    if (std::regex_search(in_file_name, match_dst, re_dst)) {
        smallest_id = match_dst.str(1);
    }
    std::cout << "run_num: " << run_num << std::endl;
    std::cout << "sink_id: " << sink_id << std::endl;
    std::cout << "smallest_id: " << smallest_id << std::endl;
    string rem    = argv[5];
    string run = "g4run" + run_num + "exGTR" + rem;
    string outputfile = "./dst1_test/" + run + "_sink" + sink_id +"_"+ smallest_id+".root     ";
    const char* c_out = out_file_name.c_str();
    TFile *f = new TFile( c_out, "recreate");
	TTree *tree = new TTree("tree", "tree");
	



}
