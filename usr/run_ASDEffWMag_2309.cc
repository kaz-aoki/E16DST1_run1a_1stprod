#include <stdlib.h>
#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TCanvas.h>
#include <regex>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_WaveformFitterCRRC.hh"
#include "E16ANA_FieldMapCalib.hh"
#include "E16ANA_EventSelect.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_GTRLorentzAngleCalib.hh"
#include "E16ANA_GTRStatus.h"
#include "E16ANA_HBDCalibration.hh"
#include "E16ANA_HBDCut.hh"
#include "E16ANA_HBDDeadChannel.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "GTR/GTRCheckHist.hh"
#include "E16ANA_TargetInfo.hh"
#include "E16ANA_RundependentName.hh"
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

constexpr bool kIsElectronRun = false;
constexpr bool kSelectEvent   = false;


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
    std::cout << "run_num: " << run_num << std::endl;
    std::cout << "sink_id: " << sink_id << std::endl;
    std::cout << "smallest_id: " << smallest_id << std::endl;
    string rem    = argv[5];
    string run = "g4run" + run_num + "exGTR" + rem;
    string outputfile = "./dst1_test/" + run + "_sink" + sink_id +"_"+ smallest_id+".root     ";
//    char* c_outfile = out_file_name.c_str();
    TFile *f = new TFile( c_outfile, "recreate");
	 TTree *tree = new TTree("tree", "tree");
	
    auto& calib = E16ANA_CalibDBManager::Instance();
    calib.SetRunID(run_id);
    E16ANA_FieldMapCalibParam field_map_param;
    field_map_param.ReadConstantData(calib.CurrentRunID());

	 E16ANA_EventSelect event_select;
	 event_select.ReadConstantData(calib.CurrentRunID());
	 auto& selected_event_ids = event_select.SelectedEventIDs();
    int current_ids_index = 0;
	 auto n_selected_events = event_select.NumSelectedEventIDs();
//GTR
    E16ANA_GTRcalibPedestal gtrped;
    gtrped.ReadCalibData( calib.CurrentRunID() );
    E16ANA_GTRLorentzAngleCalibParamManager gtr_lorentz_angle_calib_param_manager;
    gtr_lorentz_angle_calib_param_manager.ReadConstantData(calib.CurrentRunID());
    auto gtr_lorentz_angle_calib_params = gtr_lorentz_angle_calib_param_manager.GTRLorentzAngleCalibParams();
//HBD
    E16ANA_HBDCalibration *hbd_calib = new E16ANA_HBDCalibration();
    hbd_calib->ReadCalibrationData(calib.CurrentRunID());
    E16ANA_HBDCut *hbd_cut = new E16ANA_HBDCut();
    hbd_cut->ReadCutData(calib.CurrentRunID());
    E16ANA_HBDCut *hbd_cut_wo_timing = new E16ANA_HBDCut();
    hbd_cut_wo_timing->ReadCutData(calib.CurrentRunID());
    hbd_cut_wo_timing->SetCut("clustering_time_window_start", -10000.);
    hbd_cut_wo_timing->SetCut("clustering_time_window_end", 10000.);
 //  std::string hbd_waveform_template = calib.CalibFileName("HBD-waveform-template", 0);
//LG
	 E16ANA_LGBasic lgbasic;
	 lgbasic.SetMap();
	 lgbasic.SetCalibMap();
//Trigger
    E16ANA_TriggerCalibParam trigger_param;
    trigger_param.ReadConstantData(calib.CurrentRunID());

//Targets
	 E16ANA_TargetInfoManager &targets = E16ANA_TargetInfoManager::Instance();
	 targets.ReadInfoWithRunID(calib.CurrentRunID());
	 targets.Print();
//Geom and BFiled  
    auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
    cout<< static_cast<std::string>(GeometryFile)<<endl;
    E16ANA_GeometryV2::SetGlobalPointer(geometry);
    auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
    bfield_map->Initialize_binary();
	 E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
  
    E16ANA_WaveformFitterCRRC *wf1d_fitter = new E16ANA_WaveformFitterCRRC();
    E16ANA_MultiTrack fitter(bfield_map, geometry, 1);
    E16ANA_MultiTrack pair_fitter(bfield_map, geometry, 2);

    E16ANA_TrackCheckFile check_file(c_outfile, run_id);
  
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
      if (n_event % 1000 == 0) {
        cout << "Number of event: " << n_event << endl;
      }
        //printf("hello0 \n");
		auto  event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
		auto  event_id = event0->EventID();
		auto& ssd_hits0         = event0->SSD();
		auto& gtr_hits0         = event0->GTR();
      auto& hbd_hits0         = event0->HBD();
		auto& lg_hits0          = event0->LG();
		auto& trigger_gtr_hits0 = event0->TriggerGTR();
		auto& trigger_hbd_hits0 = event0->TriggerHBD();
		auto& trigger_lg_hits0  = event0->TriggerLG();
	   if (kSelectEvent) {
			bool is_selected_event = false;
			while (true) {
				auto current_id = selected_event_ids[current_ids_index];
				if (event_id < current_id) {
					break;
				} else if (event_id == current_id) {
					is_selected_event = true;
					++current_ids_index;
					break;
				} else if (event_id > current_id ) {
					if(current_ids_index == n_selected_events - 1){
						break;
					} else {
						++current_ids_index;
						continue;
					}
				}
			}
			if (!is_selected_event) {
				++n_event;
				++n_physics_event;
				continue;
			}
		}
		
			

		if(removed_layer != 0){
		   E16DST_DST1SSDFactory(ssd_hits0, &record.SSD());
			record.SSD().AddHitAndClusterIds();
		}
		if(removed_layer == -1 || removed_layer == 0){

		   E16DST_DST1GTRFactory(gtr_hits0, &record.GTR(), gtrped, gtr_lorentz_angle_calib_params);
			record.GTR().AddHitAndClusterIds();
		}
		else if(removed_layer == 1 || removed_layer == 2 || removed_layer == 3){
		   E16DST_DST1GTRFactory_ExOneGTR(gtr_hits0, &record.GTR(), gtrped, gtr_lorentz_angle_calib_params, removed_layer);
			record.GTR().AddHitAndClusterIds();
		 }
		else {
		   std::cerr << "invalid removed layer ! " << std::endl;
		   return -1;
		}

		E16DST_DST1HBDFactory(hbd_hits0, hbd_calib, hbd_cut, wf1d_fitter, &record.HBD());
		record.HBD().AddHitAndClusterIds();
		//E16DST_DST1LGFactory(lg_hits0, &record.LG(), 2, geometry); // w/fit
		E16DST_DST1LGFactory(lg_hits0, &record.LG(), 1, geometry); // w/fit
		record.LG().AddHitAndClusterIds();
		E16DST_DST1TriggerFactory(trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record.Trigger());
		record.Trigger().AddHitAndClusterIDs();
		record.LG().UpdatePtrs();
		record.GTR().UpdatePtrs();
		record.SSD().UpdatePtrs();
		record.LG().UpdatePtrs();
		record.Trigger().UpdatePtrs();
// Track
		check_file.AddRecord(*geometry, event0->EventID(), event0->SpillID(), event0->TimeStampInSpill(), event0->UT3().TriggerTime() % 8 , record, lgbasic);
		E16DST_DST1TrackFactory(*geometry, *bfield_map, &fitter, &pair_fitter,kIsElectronRun,  &record, &check_file);
		record.Tracks().Print();

		++n_event;
		++n_physics_event;
		}
	delete geometry;
	delete dst0;
	return 0;
}
