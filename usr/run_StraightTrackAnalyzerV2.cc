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
//#include "E16ANA_LGStraightProj.hh"
//#include "straightRoot.hh"
#include "E16DST_Constant.hh"

#include "E16ANA_StraightMultiTrack.hh"
#include "E16ANA_StraightTrackCandidate.hh"
#include "E16ANA_StraightTrackCheckFile.hh"

using namespace std;

int main(int argc, char* argv[]){
   if (argc != 7) {
      cerr << "Invalid argc: " << argc << endl;
      cerr << "./bin [input_gtr.dst0] [output.dst1] [run_num] [physics event start] [physics event end(all:-1)] [removed_layer (-1=all, 0=ssd,1-2-3=gtr)]" << endl;
      return 1;
    }
     auto dst0 = new E16DST_DST0();
    if (!dst0->Open(argv[1], E16DST_DST0::ReadMode)) {
      std::cout << "failed to open file : " << argv[1]  <<std::endl;
      exit(1);
  //    return 1;
    }

    string in_file_name = argv[1];
    auto out_file_name = argv[2];
    auto c_outfile     = argv[2];
    auto run_id        = stoi(argv[3]);
    auto event_start   = stoi(argv[4]);
    auto event_end     = stoi(argv[5]);
    auto removed_layer = stoi(argv[6]);
	 int  print_cycle   = 10000;
//for lg dst0
  //    return 1;
 
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
//    std::cout << "run_num: " << run_num << std::endl;
//    std::cout << "sink_id: " << sink_id << std::endl;
//    std::cout << "smallest_id: " << smallest_id << std::endl;
//    string rem    = argv[5];
//    string run = "g4run" + run_num + "exGTR" + rem;
    TFile *f = new TFile( c_outfile, "recreate");
	 TTree *tree = new TTree("tree", "tree");
	
    auto& calib = E16ANA_CalibDBManager::Instance();
    calib.SetRunID(run_id);
    E16ANA_FieldMapCalibParam field_map_param;
    field_map_param.ReadConstantData(calib.CurrentRunID());
    E16ANA_GTRcalibPedestal gtrped;
    gtrped.ReadCalibData( calib.CurrentRunID() );
    E16ANA_GTRLorentzAngleCalibParamManager gtr_lorentz_angle_calib_param_manager;
    gtr_lorentz_angle_calib_param_manager.ReadConstantData(calib.CurrentRunID());
    auto gtr_lorentz_angle_calib_params = gtr_lorentz_angle_calib_param_manager.GTRLorentzAngleCalibParams();
  
    E16ANA_TriggerCalibParam trigger_param;
    trigger_param.ReadConstantData(calib.CurrentRunID());

//targets info
	 E16ANA_TargetInfoManager &targets = E16ANA_TargetInfoManager::Instance();
	 targets.ReadInfoWithRunID(calib.CurrentRunID());
	 targets.Print();
	 std::vector<TVector3> targets_pos;
	 targets_pos.clear();
    if(targets.NoT() == 3 ){
            targets_pos.push_back(TVector3( targets.Info(0).Position().x(),targets.Info(0).Position().y(),  targets.Info(0).Position().z()));
            targets_pos.push_back(TVector3( targets.Info(1).Position().x(),targets.Info(1).Position().y(),  targets.Info(1).Position().z()));
            targets_pos.push_back(TVector3( targets.Info(2).Position().x(),targets.Info(2).Position().y(),  targets.Info(2).Position().z()));
     }
     else if (targets.IsWire()){
         targets_pos.push_back(TVector3  (targets.Info(0).Position().x(), targets.Info(0).Position().y(), targets.Info(0).Position().z()));
         targets_pos.push_back(TVector3  (targets.Info(1).Position().x(), targets.Info(1).Position().y(), targets.Info(1).Position().z()));
     }
    else {
      return -1;
    }
  
    auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
    cout<< static_cast<std::string>(GeometryFile)<<endl;
    E16ANA_GeometryV2::SetGlobalPointer(geometry);
  
    //E16ANA_WaveformFitterCRRC *wf1d_fitter = new E16ANA_WaveformFitterCRRC();
    E16ANA_StraightMultiTrack fitter(geometry, 1);
    E16ANA_StraightTrackCheckFile check_file(c_outfile, run_id);
  
//    auto record = new E16DST_DST1PhysicsRecord();
    E16DST_DST1PhysicsRecord record;
    int fflag = 0;
    int n_event = 0;
    int n_physics_event = 0;
    while (dst0->ReadAnEvent()) {
 		
      auto event_type = dst0->EventType();
      if (event_type != E16DST_DST0EventType::Physics) {
      	std::cout << "Event ID = " << dst0->Event()->EventID() << " is not Physics Event, Event Type = " << event_type << std::endl;
			continue;
		}
		if (n_physics_event < event_start) {
			++n_event;
			++n_physics_event;
			continue;
		}
		if(event_end != -1 && n_physics_event > event_end){
			break;
		}
      if (n_event % print_cycle == 0) {
        cout << "Number of event: " << n_event << endl;
      }
		record.Clear();
        //printf("hello0 \n");
		auto  event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
		auto  event_id = event0->EventID();
//		std::cout << "Event id  = " << event_id << std::endl;
		auto& ssd_hits0         = event0->SSD();
		auto& gtr_hits0         = event0->GTR();
//		auto& lg_hits0          = event0->LG();
//		auto& trigger_gtr_hits0 = event0->TriggerGTR();
//		auto& trigger_hbd_hits0 = event0->TriggerHBD();
//		auto& trigger_lg_hits0  = event0->TriggerLG();
		
//For Run0d
			auto& lg_hits0 = event0->LG(); 
			auto& trigger_gtr_hits0 = event0->TriggerGTR();
			auto& trigger_hbd_hits0 = event0->TriggerHBD();
			auto& trigger_lg_hits0  = event0->TriggerLG();
			//E16DST_DST1LGFactory(lg_hits0, &record.LG(), 2, geometry); // w/fit
			E16DST_DST1LGFactory(lg_hits0, &record.LG(), 1, geometry); // w/fit
			record.LG().AddHitAndClusterIds();
			record.LG().UpdatePtrs();

			
			E16DST_DST1TriggerFactory(trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record.Trigger());
			record.Trigger().AddHitAndClusterIDs();
			record.Trigger().UpdatePtrs();

		if(removed_layer != 0){
		   E16DST_DST1SSDFactory(ssd_hits0, &record.SSD());
		}
		if(removed_layer == -1 || removed_layer == 0){
		   E16DST_DST1GTRFactory(gtr_hits0, &record.GTR(), gtrped, gtr_lorentz_angle_calib_params);
		}
		else if(removed_layer == 1 || removed_layer == 2 || removed_layer == 3){
		   E16DST_DST1GTRFactory_ExOneGTR(gtr_hits0, &record.GTR(), gtrped, gtr_lorentz_angle_calib_params, removed_layer);
		 }
		else {
		   std::cerr << "invalid removed layer ! " << std::endl;
		   return -1;
		}
		record.GTR().UpdatePtrs();
		record.SSD().UpdatePtrs();
		
//	LG 
//		E16DST_DST1LGFactory(lg_hits0, &record.LG(), 2, geometry); // w/fit
//		record.LG().AddHitAndClusterIds();
//		record.LG().UpdatePtrs();


// Track
		check_file.AddRecord(*geometry, event0->EventID(), event0->SpillID(), event0->TimeStampInSpill(), event0->UT3().TriggerTime() % 8 , record);
		E16DST_DST1StraightTrackFactoryV2(*geometry, &fitter, &record, &check_file, targets_pos, removed_layer);



//		E16DST_DST1TriggerFactory(trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record.Trigger());
//		record.Trigger().AddHitAndClusterIDs();
//		record.Trigger().UpdatePtrs();
		//printf("hello2 \n");
		
// SSD & GTR
		++n_event;
		++n_physics_event;
		}
	delete geometry;
	delete dst0;
	return 0;
}
