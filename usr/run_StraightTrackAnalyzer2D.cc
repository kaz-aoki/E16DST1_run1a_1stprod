//this is test for wire track factory 
//
//
//
#include <stdlib.h>
#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TCanvas.h>
#include <regex>
//#include <boost/program_options.hpp>

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

using namespace std;
//namespace  bpo = boost::program_options;

void SetRemovedLayerInfoHit(std::vector<E16DST_DST1GTRHit> &hits, const int removed_layer, const int mid, vector<vector<double>> &fadc, vector<int> &sid, vector<double> &ph){//fill hit info 
	std::vector<float> wave_form;
	std::vector<double> d_wave_form; 
	wave_form.clear();
	d_wave_form.clear();
	fadc.clear();		
	sid.clear();
	ph.clear();
	int id = 0;
	for(int i=0; i < hits.size() ; i++){
		E16DST_DST1GTRHit &h = hits[i];
		if(h.ModuleId() != mid) continue;//module matching 
		if(h.LayerId() != removed_layer -1) continue;//layer matching 
		if(h.Type() != 0) continue;//axis matching  //0 means X strip
        wave_form = h.WaveForm();
        d_wave_form.resize(wave_form.size());//depends on n_sampling
        std::transform(wave_form.begin(), wave_form.end(), d_wave_form.begin(), [](const float &f){return static_cast<double>(f);});
		fadc.push_back(d_wave_form);
		sid.push_back(h.ChannelId());
		ph.push_back(h.PeakHeight());
		id++;
	}
}
void SetRemovedLayerInfoCluster(std::vector<E16DST_DST1GTRCluster> &clusters, const int removed_layer, const int mid, vector<double> &charge, vector<double> &cog, vector<double> timing){//fill cluster info
	charge.clear();
	cog.clear();
	timing.clear();
	for(int i=0; i < clusters.size() ; i++){
		E16DST_DST1GTRCluster &cl = clusters[i];
		if(cl.ModuleId() != mid) continue;//module matching 
		if(cl.LayerId() != (removed_layer -1)) continue;//layer matching 
		if(cl.Type() != 0) continue;//axis matching  //0 means X strip
//		std::cout << "cluster charge = " << cl.PeakSum() << std::endl;
		charge.push_back(cl.PeakSum());
		cog.push_back(cl.CogPos());
		timing.push_back(cl.Timing());
	}
}

void SetHitInfoToBranch(std::vector<E16DST_DST1GTRHit> &hits, E16DST_DST1GTRCluster* cluster, vector<vector<double>> &fadc, vector<int> &sid , 
						vector<double> &tot, vector<double> &htime, vector<double> &ph,
					vector<double> &tots, vector<double> &tote, vector<double> &peakt, vector<double> &rt){
	std::vector<float> wave_form;
	std::vector<double> d_wave_form; 
    int cl_size = cluster->HitOrders().size();
	wave_form.clear();
	d_wave_form.clear();
    sid.clear();
    tot.clear();
	htime.clear();
	ph.clear();
    fadc.clear();
	tots.clear();
	tote.clear();
	peakt.clear();
	rt.clear();
    for(const int hit_ord : cluster->HitOrders()){ 
	    E16DST_DST1GTRHit &h = hits[hit_ord];
        wave_form = h.WaveForm();
        d_wave_form.resize(wave_form.size());//depends on n_sampling
        std::transform(wave_form.begin(), wave_form.end(), d_wave_form.begin(), [](const float &f){return static_cast<double>(f);});
        fadc.push_back(d_wave_form);
        sid.push_back(h.ChannelId());
        tot.push_back(h.Tot());
        htime.push_back(h.Timing());
        ph.push_back(h.PeakHeight());
		tots.push_back(h.TotStart());
		tote.push_back(h.TotEnd());
		peakt.push_back(h.Peakt());
		rt.push_back(h.Riset());
	 }
}

int main(int argc, char* argv[]) {
  if (argc != 6) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst0] [output.dst1] [run_num] [max physics event (all: -1)] [removed_layer (-1 = all, 0, ssd, 1,2,3 = gtr)]" << endl;
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
//  string outputfile = "./dst1_test/" + run + "_sink" + sink_id +"_"+ smallest_id+".root";
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
  string outputfile = "./dst1_test/" + run + "_sink" + sink_id +"_"+ smallest_id+".root";

  const char* c_out = out_file_name.c_str();
  
  





  TFile *f = new TFile( c_out, "recreate");
 
 
//  TFile *f = new TFile("./dst1_test/output.root", "recreate");
  TTree *tree  = new TTree("tree", "tree");
  TTree *ctree = new TTree("ctree", "ctree");
  Int_t event_id;
  Int_t run_id;
  Int_t mod_id;
  Int_t axis;// 0...X, 1...Y
  Int_t hitid_ssdx;
  Int_t hitid_100x;
  Int_t hitid_200x;
  Int_t hitid_300x;
  Int_t hitid_100y;
  Int_t hitid_200y;
  Int_t hitid_300y;
  Int_t hasMatchedASDHit;
  Double_t g_xssd;
  Double_t g_zssd;
  Double_t gc_x100;
  Double_t gc_y100;
  Double_t gc_z100;
  Double_t gc_x200;
  Double_t gc_y200;
  Double_t gc_z200;
  Double_t gc_x300;
  Double_t gc_y300;
  Double_t gc_z300;
  Double_t gt_x100;
  Double_t gt_y100;
  Double_t gt_z100;
  Double_t gt_x200;
  Double_t gt_y200;
  Double_t gt_z200;
  Double_t gt_x300;
  Double_t gt_y300;
  Double_t gt_z300;
  Double_t lxssd;//local pos1
//  Double_t lx100;//local pos1
//  Double_t ly100;
//  Double_t lx200;
//  Double_t ly200;
//  Double_t lx300;
//  Double_t ly300;
  Double_t cog_x100;
  Double_t cog_x200;
  Double_t cog_x300;
  Double_t cog_y100;
  Double_t cog_y200;
  Double_t cog_y300;
  Double_t tpos_x100;
  Double_t tpos_x200;
  Double_t tpos_x300;
  Double_t clc_xssd;
  Double_t clc_x100;
  Double_t clc_x200;
  Double_t clc_x300;
  Double_t clc_y100;
  Double_t clc_y200;
  Double_t clc_y300;
  Double_t timing_xssd;
  Double_t timing_x100;
  Double_t timing_x200;
  Double_t timing_x300;
  Double_t timing_y100;
  Double_t timing_y200;
  Double_t timing_y300;
  Double_t timing2_x100;
  Double_t timing2_x200;
  Double_t timing2_x300;
  Double_t timing2_y100;
  Double_t timing2_y200;
  Double_t timing2_y300;
  Double_t timing3_x100;
  Double_t timing3_x200;
  Double_t timing3_x300;
  Double_t timing3_y100;
  Double_t timing3_y200;
  Double_t timing3_y300;
  Double_t timing4_x100;
  Double_t timing4_x200;
  Double_t timing4_x300;
  Double_t timing4_y100;
  Double_t timing4_y200;
  Double_t timing4_y300;
  Double_t timing5_x100;
  Double_t timing5_x200;
  Double_t timing5_x300;
  Double_t timing5_y100;
  Double_t timing5_y200;
  Double_t timing5_y300;
  Double_t max_riset_x100;
  Double_t max_riset_x200;
  Double_t max_riset_x300;
  Double_t max_riset_y100;
  Double_t max_riset_y200;
  Double_t max_riset_y300;
  Double_t residual_ssdx;
  Double_t residual_100x;
  Double_t residual_200x;
  Double_t residual_300x;
  Double_t residual_100y;
  Double_t residual_200y;
  Double_t residual_300y;
  Double_t fitresidual_ssdx;
  Double_t fitresidual_100x;
  Double_t fitresidual_200x;
  Double_t fitresidual_300x;
  Double_t fitresidual_100y;
  Double_t fitresidual_200y;
  Double_t fitresidual_300y;
  Double_t chi2_x;
  Double_t chi2_y;
  Double_t tgt_z;
//  Double_t tgtpos_y;
  Double_t fit_a_x;
  Double_t fit_b_x;
  Double_t fit_a_y;
  Double_t fit_b_y;
  Double_t distance_x;
//  Double_t distance_y;	
  Double_t distance_fromtgt_y;	
  Double_t distance_fromupwire_y;	
  Double_t distance_fromdownwire_y;	
  Double_t fit_g100x;
  Double_t fit_g100y;
  Double_t fit_g100z;
  Double_t fit_g200x;
  Double_t fit_g200y;
  Double_t fit_g200z;
  Double_t fit_g300x;
  Double_t fit_g300y;
  Double_t fit_g300z;

  Int_t x_trk_used_times;
  Int_t trkid_x;
  Int_t trkid_y;
  Int_t cluster_size_ssd;
  Int_t cluster_size_g100x;
  Int_t cluster_size_g200x;
  Int_t cluster_size_g300x;
  Int_t cluster_size_g100y;
  Int_t cluster_size_g200y;
  Int_t cluster_size_g300y;
  Int_t asd_hit;
  Int_t lg_hit;
  TVector3 lg_cross_pos;
  Int_t lg_module_id;
  Int_t lg_channel_id;
  Double_t timediff_in_cluster_100x;
  Double_t timediff_in_cluster_200x;
  Double_t timediff_in_cluster_300x;
  vector<Double_t> timings_100x;
  vector<Double_t> timings_200x;
  vector<Double_t> timings_300x;
  vector<Double_t> positions_100x;
  vector<Double_t> positions_200x;
  vector<Double_t> positions_300x;

  vector<Double_t> asd_hits;
  vector<vector<Double_t>> fadc_100x;
  vector<vector<Double_t>> fadc_200x;
  vector<vector<Double_t>> fadc_300x;
  vector<vector<Double_t>> fadc_100y;
  vector<vector<Double_t>> fadc_200y;
  vector<vector<Double_t>> fadc_300y;
  vector<Double_t> htime_100x;//hit timing for each strip
  vector<Double_t> htime_200x;
  vector<Double_t> htime_300x;
  vector<Double_t> htime_100y;
  vector<Double_t> htime_200y;
  vector<Double_t> htime_300y;
  vector<Double_t> hpt_100x;//hit peak time
  vector<Double_t> hpt_200x;//hit peak time
  vector<Double_t> hpt_300x;//hit peak time
  vector<Double_t> hpt_100y;//hit peak time
  vector<Double_t> hpt_200y;//hit peak time
  vector<Double_t> hpt_300y;//hit peak time
  vector<Double_t> htot_100x;
  vector<Double_t> htot_200x;
  vector<Double_t> htot_300x;
  vector<Double_t> htot_100y;
  vector<Double_t> htot_200y;
  vector<Double_t> htot_300y;
  vector<Double_t> hrt_100x;
  vector<Double_t> hrt_200x;
  vector<Double_t> hrt_300x;
  vector<Double_t> hrt_100y;
  vector<Double_t> hrt_200y;
  vector<Double_t> hrt_300y;
  vector<Double_t> htots_100x;//tot start
  vector<Double_t> htots_200x;//tot start
  vector<Double_t> htots_300x;//tot start
  vector<Double_t> htots_100y;//tot start
  vector<Double_t> htots_200y;//tot start
  vector<Double_t> htots_300y;//tot start
  vector<Double_t> htote_100x;//tot end 
  vector<Double_t> htote_200x;//tot end 
  vector<Double_t> htote_300x;//tot end 
  vector<Double_t> htote_100y;//tot end 
  vector<Double_t> htote_200y;//tot end 
  vector<Double_t> htote_300y;//tot end 
  vector<Double_t> ph_100x;//peak height
  vector<Double_t> ph_200x;
  vector<Double_t> ph_300x;
  vector<Double_t> ph_100y;
  vector<Double_t> ph_200y;
  vector<Double_t> ph_300y;
  vector<Int_t> sid_100x;
  vector<Int_t> sid_200x;
  vector<Int_t> sid_300x;
  vector<Int_t> sid_100y;
  vector<Int_t> sid_200y;
  vector<Int_t> sid_300y;

// for removed layer ## hit  
  vector<vector<Double_t>> fadc_rlx;
  vector<Double_t> hph_rlx;//hit peak height 
  vector<Int_t>    hsid_rlx;//hit strip id

//for removed layer ## cluster
  vector<Double_t> clc_rlx; //cluster charge
  vector<Double_t> clcog_rlx;//cluster cog
  vector<Double_t> clt_rlx; //cluster timing
 

//
  Double_t cp_x;
  Double_t cp_z;
  Double_t cp_dis;
  Double_t cp_chi2_1;
  Double_t cp_chi2_2;
  Double_t cp_mod1;
  Double_t cp_mod2;
  ctree->Branch("cp_x",     &cp_x,   "cp_x/D");
  ctree->Branch("cp_z",     &cp_z,   "cp_z/D");
  ctree->Branch("cp_dis",   &cp_dis, "cp_dis/D");
  ctree->Branch("cp_chi2_1",&cp_chi2_1, "cp_chi2_1/D"   );
  ctree->Branch("cp_chi2_2",&cp_chi2_2, "cp_chi2_2/D"   );
  ctree->Branch("cp_mod1",&cp_mod1, "cp_mod1/D"   );
  ctree->Branch("cp_mod2",&cp_mod2, "cp_mod2/D"   );




  //	std::vector<TVector3> two_points_on_track;
  tree->Branch("run_id", &run_id, "run_id/I");
  tree->Branch("event_id", &event_id, "event_id/I");
  tree->Branch("mod_id", &mod_id, "mod_id/I");
  tree->Branch("axis", &axis, "axis/I");
  tree->Branch("hitid_ssdx", &hitid_ssdx, "hitid_ssdx/I");
  tree->Branch("hitid_100x", &hitid_100x, "hitid_100x/I");
  tree->Branch("hitid_200x", &hitid_200x, "hitid_200x/I");
  tree->Branch("hitid_300x", &hitid_300x, "hitid_300x/I");
  tree->Branch("hitid_100y", &hitid_100y, "hitid_100y/I");
  tree->Branch("hitid_200y", &hitid_200y, "hitid_200y/I");
  tree->Branch("hitid_300y", &hitid_300y, "hitid_300y/I");
  tree->Branch("g_xssd", &g_xssd, "g_xssd/D");
  tree->Branch("g_zssd", &g_zssd, "g_zssd/D");
  tree->Branch("gc_x100", &gc_x100, "gc_x100/D");
  tree->Branch("gc_y100", &gc_y100, "gc_y100/D");
  tree->Branch("gc_z100", &gc_z100, "gc_z100/D");
  tree->Branch("gc_x200", &gc_x200, "gc_x200/D");
  tree->Branch("gc_y200", &gc_y200, "gc_y200/D");
  tree->Branch("gc_z200", &gc_z200, "gc_z200/D");
  tree->Branch("gc_x300", &gc_x300, "gc_x300/D");
  tree->Branch("gc_y300", &gc_y300, "gc_y300/D");
  tree->Branch("gc_z300", &gc_z300, "gc_z300/D");
  tree->Branch("gt_x100", &gt_x100, "gt_x100/D");
  tree->Branch("gt_y100", &gt_y100, "gt_y100/D");
  tree->Branch("gt_z100", &gt_z100, "gt_z100/D");
  tree->Branch("gt_x200", &gt_x200, "gt_x200/D");
  tree->Branch("gt_y200", &gt_y200, "gt_y200/D");
  tree->Branch("gt_z200", &gt_z200, "gt_z200/D");
  tree->Branch("gt_x300", &gt_x300, "gt_x300/D");
  tree->Branch("gt_y300", &gt_y300, "gt_y300/D");
  tree->Branch("gt_z300", &gt_z300, "gt_z300/D");
  tree->Branch("lxssd", &lxssd, "lxssd/D");
//  tree->Branch("lx100", &lx100, "lx100/D");
//  tree->Branch("ly100", &ly100, "ly100/D");
//  tree->Branch("lx200", &lx200, "lx200/D");
//  tree->Branch("ly200", &ly200, "ly200/D");
//  tree->Branch("lx300", &lx300, "lx300/D");
//  tree->Branch("ly300", &ly300, "ly300/D");
  tree->Branch("cog_x100", &cog_x100, "cog_x100/D");
  tree->Branch("cog_x200", &cog_x200, "cog_x200/D");
  tree->Branch("cog_x300", &cog_x300, "cog_x300/D");
  tree->Branch("cog_y100", &cog_y100, "cog_y100/D");
  tree->Branch("cog_y200", &cog_y200, "cog_y200/D");
  tree->Branch("cog_y300", &cog_y300, "cog_y300/D");
  tree->Branch("tpos_x100", &tpos_x100, "tpos_x100/D");
  tree->Branch("tpos_x200", &tpos_x200, "tpos_x200/D");
  tree->Branch("tpos_x300", &tpos_x300, "tpos_x300/D");
 // tree->Branch("tpos_y100", &tpos_y100, "tpos_y100/D");
 // tree->Branch("tpos_y200", &tpos_y200, "tpos_y200/D");
 // tree->Branch("tpos_y300", &tpos_y300, "tpos_y300/D");
  tree->Branch("clc_xssd", &clc_xssd, "clc_xssd/D");
  tree->Branch("clc_x100", &clc_x100, "clc_x100/D");
  tree->Branch("clc_x200", &clc_x200, "clc_x200/D");
  tree->Branch("clc_x300", &clc_x300, "clc_x300/D");
  tree->Branch("clc_y100", &clc_y100, "clc_y100/D");
  tree->Branch("clc_y200", &clc_y200, "clc_y200/D");
  tree->Branch("clc_y300", &clc_y300, "clc_y300/D");
  tree->Branch("timing_xssd", &timing_xssd, "timing_xssd/D");
  tree->Branch("timing_x100", &timing_x100, "timing_x100/D");
  tree->Branch("timing_x200", &timing_x200, "timing_x200/D");
  tree->Branch("timing_x300", &timing_x300, "timing_x300/D");
  tree->Branch("timing_y100", &timing_y100, "timing_y100/D");
  tree->Branch("timing_y200", &timing_y200, "timing_y200/D");
  tree->Branch("timing_y300", &timing_y300, "timing_y300/D");
  tree->Branch("timing2_x100", &timing2_x100, "timing2_x100/D");
  tree->Branch("timing2_x200", &timing2_x200, "timing2_x200/D");
  tree->Branch("timing2_x300", &timing2_x300, "timing2_x300/D");
  tree->Branch("timing2_y100", &timing2_y100, "timing2_y100/D");
  tree->Branch("timing2_y200", &timing2_y200, "timing2_y200/D");
  tree->Branch("timing2_y300", &timing2_y300, "timing2_y300/D");
  tree->Branch("timing3_x100", &timing3_x100, "timing3_x100/D");
  tree->Branch("timing3_x200", &timing3_x200, "timing3_x200/D");
  tree->Branch("timing3_x300", &timing3_x300, "timing3_x300/D");
  tree->Branch("timing3_y100", &timing3_y100, "timing3_y100/D");
  tree->Branch("timing3_y200", &timing3_y200, "timing3_y200/D");
  tree->Branch("timing3_y300", &timing3_y300, "timing3_y300/D");
  tree->Branch("timing4_x100", &timing4_x100, "timing4_x100/D");
  tree->Branch("timing4_x200", &timing4_x200, "timing4_x200/D");
  tree->Branch("timing4_x300", &timing4_x300, "timing4_x300/D");
  tree->Branch("timing4_y100", &timing4_y100, "timing4_y100/D");
  tree->Branch("timing4_y200", &timing4_y200, "timing4_y200/D");
  tree->Branch("timing4_y300", &timing4_y300, "timing4_y300/D");
  tree->Branch("timing5_x100", &timing5_x100, "timing5_x100/D");
  tree->Branch("timing5_x200", &timing5_x200, "timing5_x200/D");
  tree->Branch("timing5_x300", &timing5_x300, "timing5_x300/D");
  tree->Branch("timing5_y100", &timing5_y100, "timing5_y100/D");
  tree->Branch("timing5_y200", &timing5_y200, "timing5_y200/D");
  tree->Branch("timing5_y300", &timing5_y300, "timing5_y300/D");
  tree->Branch("max_riset_x100", &max_riset_x100, "max_riset_x100/D");
  tree->Branch("max_riset_x200", &max_riset_x200, "max_riset_x200/D");
  tree->Branch("max_riset_x300", &max_riset_x300, "max_riset_x300/D");
  tree->Branch("max_riset_y100", &max_riset_y100, "max_riset_y100/D");
  tree->Branch("max_riset_y200", &max_riset_y200, "max_riset_y200/D");
  tree->Branch("max_riset_y300", &max_riset_y300, "max_riset_y300/D");
  tree->Branch("residual_100x", &residual_100x, "residual_100x/D");
  tree->Branch("residual_200x", &residual_200x, "residual_200x/D");
  tree->Branch("residual_300x", &residual_300x, "residual_300x/D");
  tree->Branch("residual_100y", &residual_100y, "residual_100y/D");
  tree->Branch("residual_200y", &residual_200y, "residual_200y/D");
  tree->Branch("residual_300y", &residual_300y, "residual_300y/D");
  tree->Branch("residual_ssdx", &residual_ssdx, "residual_ssdx/D");
  tree->Branch("fitresidual_100x", &fitresidual_100x, "fitresidual_100x/D");
  tree->Branch("fitresidual_200x", &fitresidual_200x, "fitresidual_200x/D");
  tree->Branch("fitresidual_300x", &fitresidual_300x, "fitresidual_300x/D");
  tree->Branch("fitresidual_100y", &fitresidual_100y, "fitresidual_100y/D");
  tree->Branch("fitresidual_200y", &fitresidual_200y, "fitresidual_200y/D");
  tree->Branch("fitresidual_300y", &fitresidual_300y, "fitresidual_300y/D");
  tree->Branch("fitresidual_ssdx", &fitresidual_ssdx, "fitresidual_ssdx/D");
 


  tree->Branch("chi2_x", &chi2_x, "chi2_x/D");
  tree->Branch("chi2_y", &chi2_y, "chi2_y/D");
  tree->Branch("tgt_z", &tgt_z, "tgt_z/D");
//  tree->Branch("tgtpos_y", &tgtpos_y, "tgtpos_y/D");
  tree->Branch("fit_a_x", &fit_a_x, "fit_a_x/D");
  tree->Branch("fit_b_x", &fit_b_x, "fit_b_x/D");
  tree->Branch("fit_a_y", &fit_a_y, "fit_a_y/D");
  tree->Branch("fit_b_y", &fit_b_y, "fit_b_y/D");
  tree->Branch("distance_x", &distance_x, "distance_x/D");
//  tree->Branch("distance_y", &distance_y, "distance_y/D");
  tree->Branch("distance_fromtgt_y", &distance_fromtgt_y, "distance_fromtgt_y/D");
  tree->Branch("distance_fromupwire_y", &distance_fromupwire_y, "distance_fromupwire_y/D");
  tree->Branch("distance_fromdownwire_y", &distance_fromdownwire_y, "distance_fromdownwire_y/D");
  tree->Branch("fit_g100x", &fit_g100x, "fit_g100x/D");
  tree->Branch("fit_g100y", &fit_g100y, "fit_g100y/D");
  tree->Branch("fit_g100z", &fit_g100z, "fit_g100z/D");
  tree->Branch("fit_g200x", &fit_g200x, "fit_g200x/D");
  tree->Branch("fit_g200y", &fit_g200y, "fit_g200y/D");
  tree->Branch("fit_g200z", &fit_g200z, "fit_g200z/D");
  tree->Branch("fit_g300x", &fit_g300x, "fit_g300x/D");
  tree->Branch("fit_g300y", &fit_g300y, "fit_g300y/D");
  tree->Branch("fit_g300z", &fit_g300z, "fit_g300z/D");


  tree->Branch("hasMatchedASDHit", &hasMatchedASDHit, "hasMatchedASDHit/I");
  tree->Branch("x_trk_used_times", &x_trk_used_times, "x_trk_used_times/I");
  tree->Branch("trkid_x", &trkid_x, "trkid_x/I");
  tree->Branch("trkid_y", &trkid_y, "trkid_y/I");
  tree->Branch("hitid_ssdx", &hitid_ssdx, "hitid_ssdx/I");
  tree->Branch("hitid_100x", &hitid_100x, "hitid_100x/I");
  tree->Branch("hitid_200x", &hitid_200x, "hitid_200x/I");
  tree->Branch("hitid_300x", &hitid_300x, "hitid_300x/I");
  tree->Branch("hitid_100y", &hitid_100y, "hitid_100y/I");
  tree->Branch("hitid_200y", &hitid_200y, "hitid_200y/I");
  tree->Branch("hitid_300y", &hitid_300y, "hitid_300y/I");
  tree->Branch("cluster_size_ssd", &cluster_size_ssd, "cluster_size_ssd/I");
  tree->Branch("cluster_size_g100x", &cluster_size_g100x, "cluster_size_g100x/I");
  tree->Branch("cluster_size_g200x", &cluster_size_g200x, "cluster_size_g200x/I");
  tree->Branch("cluster_size_g300x", &cluster_size_g300x, "cluster_size_g300x/I");
  tree->Branch("cluster_size_g100y", &cluster_size_g100y, "cluster_size_g100y/I");
  tree->Branch("cluster_size_g200y", &cluster_size_g200y, "cluster_size_g200y/I");
  tree->Branch("cluster_size_g300y", &cluster_size_g300y, "cluster_size_g300y/I");
  tree->Branch("asd_hit",&asd_hit, "asd_hit/I" );
  tree->Branch("lg_hit",&lg_hit, "lg_hit/I" );
  tree->Branch("lg_cross_pos", &lg_cross_pos);
  tree->Branch("lg_module_id", &lg_module_id, "lg_module_id/I");
  tree->Branch("lg_channel_id", &lg_channel_id,"lg_channel_id/I" );

  tree->Branch("timediff_in_cluster_100x", &timediff_in_cluster_100x, "timediff_in_cluster_100x/D"); 
  tree->Branch("timediff_in_cluster_200x", &timediff_in_cluster_200x, "timediff_in_cluster_200x/D"); 
  tree->Branch("timediff_in_cluster_300x", &timediff_in_cluster_300x, "timediff_in_cluster_300x/D"); 
  tree->Branch("timings_100x"  , &timings_100x );
  tree->Branch("timings_200x"  , &timings_200x );
  tree->Branch("timings_300x"  , &timings_300x );
  tree->Branch("positions_100x", &positions_100x );
  tree->Branch("positions_200x", &positions_200x );
  tree->Branch("positions_300x", &positions_300x );

  tree->Branch("asd_hits", &asd_hits);
  
  tree->Branch("fadc_100x", &fadc_100x);
  tree->Branch("fadc_200x", &fadc_200x);
  tree->Branch("fadc_300x", &fadc_300x);
  tree->Branch("fadc_100y", &fadc_100y);
  tree->Branch("fadc_200y", &fadc_200y);
  tree->Branch("fadc_300y", &fadc_300y);
  tree->Branch("sid_100x", &sid_100x);
  tree->Branch("sid_200x", &sid_200x);
  tree->Branch("sid_300x", &sid_300x);
  tree->Branch("sid_100y", &sid_100y);
  tree->Branch("sid_200y", &sid_200y);
  tree->Branch("sid_300y", &sid_300y);
  tree->Branch("htot_100x", &htot_100x);
  tree->Branch("htot_200x", &htot_200x);
  tree->Branch("htot_300x", &htot_300x);
  tree->Branch("htot_100y", &htot_100y);
  tree->Branch("htot_200y", &htot_200y);
  tree->Branch("hrt_100x", &hrt_100x);
  tree->Branch("hrt_200x", &hrt_200x);
  tree->Branch("hrt_300x", &hrt_300x);
  tree->Branch("hrt_100y", &hrt_100y);
  tree->Branch("hrt_200y", &hrt_200y);
  tree->Branch("hrt_300y", &hrt_300y);
  tree->Branch("hrt_300y", &hrt_300y);
  tree->Branch("htime_100x", &htime_100x);
  tree->Branch("htime_200x", &htime_200x);
  tree->Branch("htime_300x", &htime_300x);
  tree->Branch("htime_100y", &htime_100y);
  tree->Branch("htime_200y", &htime_200y);
  tree->Branch("htime_300y", &htime_300y);
  tree->Branch("hpt_100x", &hpt_100x);
  tree->Branch("hpt_200x", &hpt_200x);
  tree->Branch("hpt_300x", &hpt_300x);
  tree->Branch("hpt_100y", &hpt_100y);
  tree->Branch("hpt_200y", &hpt_200y);
  tree->Branch("hpt_300y", &hpt_300y);
  tree->Branch("htots_100x", &htots_100x);
  tree->Branch("htots_200x", &htots_200x);
  tree->Branch("htots_300x", &htots_300x);
  tree->Branch("htots_100y", &htots_100y);
  tree->Branch("htots_200y", &htots_200y);
  tree->Branch("htots_300y", &htots_300y);
  tree->Branch("htote_100x", &htote_100x);
  tree->Branch("htote_200x", &htote_200x);
  tree->Branch("htote_300x", &htote_300x);
  tree->Branch("htote_100y", &htote_100y);
  tree->Branch("htote_200y", &htote_200y);
  tree->Branch("htote_300y", &htote_300y);
  
  tree->Branch("hph_100x", &ph_100x);
  tree->Branch("hph_200x", &ph_200x);
  tree->Branch("hph_300x", &ph_300x);
  tree->Branch("hph_100y", &ph_100y);
  tree->Branch("hph_200y", &ph_200y);
  tree->Branch("hph_300y", &ph_300y);
  tree->Branch("htot_100x", &htot_100x);
  tree->Branch("htot_200x", &htot_200x);
  tree->Branch("htot_300x", &htot_300x);
  tree->Branch("htot_100y", &htot_100y);
  tree->Branch("htot_200y", &htot_200y);
  tree->Branch("htot_300y", &htot_300y);
  tree->Branch("hrt_100x",  &hrt_100x);
  tree->Branch("hrt_200x",  &hrt_200x);
  tree->Branch("hrt_300x",  &hrt_300x);
  tree->Branch("hrt_100y",  &hrt_100y);
  tree->Branch("hrt_200y",  &hrt_200y);
  tree->Branch("hrt_300y",  &hrt_300y);

  tree->Branch("hsid_rlx" , &hsid_rlx);
  tree->Branch("hph_rlx"  , &hph_rlx);
  tree->Branch("fadc_rlx" , &fadc_rlx);
  tree->Branch("clc_rlx"  , &clc_rlx);//cluster charge
  tree->Branch("clcog_rlx", &clcog_rlx);//cluster cog
  tree->Branch("clt_rlx"  , &clt_rlx); //cluster timing

  //auto in_file_name  = argv[1];
    auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(in_run_id);
//  E16ANA_RundependentName& name = E16ANA_RundependentName::Instance();
//  string geomName = name.ReadNameWithRunID(run_id, "geometry", "/ccj/u/E16/database/");
//  E16ANA_GeometryV2* geom = new E16ANA_GeometryV2(geomName);
//  E16ANA_GeometryV2::SetGlobalPointer(geom);

//  E16ANA_ParamManager *paramMgr;
//  E16ANA_GTRAnalyzerManager *gtr_manager;
//  const char *file = "/ccj/u/mtomoki/E16CalibFiles-local.cfg";
//  paramMgr = new E16ANA_ParamManager(file);
//  gtr_manager = new E16ANA_GTRAnalyzerManager(paramMgr);


  auto trigger_param = new E16ANA_TriggerCalibParam();
  trigger_param->ReadConstantData(calib.CurrentRunID());
  E16ANA_GTRcalibPedestal gtrped;
  gtrped.ReadCalibData( calib.CurrentRunID() );
  E16ANA_TargetInfoManager& targets = E16ANA_TargetInfoManager::Instance();
  targets.ReadInfoWithRunID( calib.CurrentRunID());
  targets.Print();
  E16ANA_GTRLorentzAngleCalibParamManager gtr_lorentz_angle_calib_param_manager;
  gtr_lorentz_angle_calib_param_manager.ReadConstantData(calib.CurrentRunID());
  auto gtr_lorentz_angle_calib_params = gtr_lorentz_angle_calib_param_manager.GTRLorentzAngleCalibParams();
  auto record = new E16DST_DST1PhysicsRecord();
  auto geom = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  auto *gtrhist = new GTRCheckHist();
  auto gtr_status = new E16ANA_GTRStatus(calib.CurrentRunID());
  //auto asd_dead = gtr_status->ASDDeadChannel();
//  gtr_status->ASDDeadChannel()->ReadDeadChannelData( calib.CurrentRunID());
  for (int m=101; m< 110; m++){
	for(int ch=0; ch < 24; ch++){
// 		std::cout << "GEM Status : module = " << m << ", ch = " << ch << ", gtr_dead " <<  gtr_status->GEMDeadArea300()->IsYOK(m, ch) << std::endl;
	}
  }
//  std::cout << "Is X GEM OK  == " << gtr_status->GEMDeadArea300()->IsXOK(106, 13.2) << std::endl;//GEM  
  int apvch = E16ANA_GTRChannelManager::ConvLocalXToAPVch(0, 12);//(gtr_size, local_pos[mm])
//  std::cout << "apv ch convorotor returns   == " << E16ANA_GTRChannelManager::ConvLocalXToAPVch(0, 12) << std::endl;//
  
  
  int n_event = 0;
  int n_physics_event = 0;
  int print_cycle = 100;
  while (dst0->ReadAnEvent()) {
    if (max_event != -1 && n_event >= max_event) {
      break;
    }
    if (n_event % print_cycle == 0) {
		std::cout  << "infile = " << in_file_name <<std::endl;
      cout << "Number of event: " << n_event << endl;
    }
    if (dst0->EventType() != E16DST_DST0EventType::Physics){
        std::cout << "Event ID = " << dst0->Event()->EventID() << " is not Physics Event, Event Type =" << dst0->Event()->EventType() << std::endl;
        continue;
    }
//
//
    auto event_type = dst0->EventType();
    E16DST_DST0PhysicsEvent *event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
    auto& gtr_hits0 = event0->GTR();
	if(removed_layer != 0){
    	auto& ssd_hits0 = event0->SSD();
    	E16DST_DST1SSDFactory(ssd_hits0, &record->SSD());
	}
	if(removed_layer == -1 || removed_layer == 0){
    	E16DST_DST1GTRFactory(gtr_hits0, &record->GTR(), gtrped, gtr_lorentz_angle_calib_params);
	}
	else if(removed_layer == 1 || removed_layer == 2 || removed_layer == 3){
    	E16DST_DST1GTRFactory_ExOneGTR(gtr_hits0, &record->GTR(), gtrped, gtr_lorentz_angle_calib_params, removed_layer);
    }
	else {
		std::cerr << "invalid removed layer ! " << std::endl;
		return -1;
	}
	
	record->GTR().UpdatePtrs();
    record->SSD().UpdatePtrs();

//---test --- //	
//	for(int mid=100; mid<110; mid++){
//		for(int l=0; l<2; l++){
//		std::vector<E16DST_DST1GTRCluster*> &cls  = record->GTR().ClusterPtrs(mid, l, 0);
//			for(int i =0; i<cls.size(); i++){
//				for(int j=0; j< cls[i]->HitOrders().size() ; j++){
//					std::cout << "id = " << cls[i]->HitOrders()[j] << std::endl;
//				}
//			}
//		}
//	}
	int noh_trg = event0->TriggerGTR().NumberOfHits();
	int hit_tile = -1000;
	
	std::vector<std::shared_ptr<E16DST_DST1StraightTrack2D>> stx_tracks;
	std::vector<std::shared_ptr<E16DST_DST1StraightTrack2D>> sty_tracks;
	std::vector<std::shared_ptr<E16DST1_DST1CrossByStraight>> cross;
	if(targets.IsWire()){
//		E16DST_DST1WireTrackFactory3D(event0, &record->SSD(), &record->GTR(), st_tracks, gtrped, removed_layer);
	}
	else if(targets.NoT() == 3){
		E16DST_DST1StraightTrackFactory2D(event0, &record->SSD(), &record->GTR(), stx_tracks, sty_tracks,cross,  gtrped, removed_layer);
	}

	for(int i=0; i < stx_tracks.size(); i++){
		std::shared_ptr<E16DST_DST1StraightTrack2D> t = stx_tracks[i];
        run_id     = in_run_id;
		event_id   = t->EventID();
		//	std::cout << "event_id "  << event_id << std::endl;
		mod_id     = t->ModuleID();	
		axis       = t->Axis();
		trkid_x    = t->TrackID();
//		trkid_y    = t->YTrackID();
//		hitid_ssdx = t->SSDXHitID();
		hitid_100x = t->ID100Hit();
		hitid_200x = t->ID200Hit();
		hitid_300x = t->ID300Hit();
//		hitid_100y = t->GTR100XHitID();
//		hitid_200y = t->GTR200XHitID();
//		hitid_300y = t->GTR300XHitID();
//		if(t->SSDCluster() != nullptr){
//			cluster_size_ssd   = t->SSDCluster()->NumHits();
//			lxssd    = t->SSDCluster()->CogPos();
//			g_xssd   = t->SSDCluster()->GlobalPos(*geom).X();
//			g_zssd   = t->SSDCluster()->GlobalPos(*geom).Z();
//			clc_xssd = t->SSDCluster()->PeakSum();
//			timing_xssd = t->SSDCluster()->Timing();
//			residual_ssdx = t->ResidualSSD();
//		}
		cluster_size_g100x = t->GTR100Cluster()->NumHits();
		cluster_size_g200x = t->GTR200Cluster()->NumHits();
		cluster_size_g300x = t->GTR300Cluster()->NumHits();
//		cluster_size_g100y = t->GTR100YCluster()->NumHits();
//		cluster_size_g200y = t->GTR200YCluster()->NumHits();
//		cluster_size_g300y = t->GTR300YCluster()->NumHits();
		cog_x100    = t->GTR100Cluster()->CogPos();
		cog_x200    = t->GTR200Cluster()->CogPos();
		cog_x300    = t->GTR300Cluster()->CogPos();
		tpos_x100   = t->GTR100Cluster()->TdcPos();
//		std::cout << "tpos " << tpos_x100 << std::endl;
		tpos_x200   = t->GTR200Cluster()->TdcPos();
		tpos_x300   = t->GTR300Cluster()->TdcPos();
//		ly100    = t->GTR100YCluster()->CogPos();//local y
//		ly200    = t->GTR200YCluster()->CogPos();//local y
//		ly300    = t->GTR300YCluster()->CogPos();//local y
		gc_x100   = t->GTR100Cluster()->GlobalPos(*geom).X();
		gc_x200   = t->GTR200Cluster()->GlobalPos(*geom).X();
		gc_x300   = t->GTR300Cluster()->GlobalPos(*geom).X();
//		gc_y100   = t->GTR100YCluster()->GlobalPos(*geom).Y();
//		gc_y200   = t->GTR200YCluster()->GlobalPos(*geom).Y();
//		gc_y300   = t->GTR300YCluster()->GlobalPos(*geom).Y();
		gc_z100   = t->GTR100Cluster()->GlobalPos(*geom).Z();
		gc_z200   = t->GTR200Cluster()->GlobalPos(*geom).Z();
		gc_z300   = t->GTR300Cluster()->GlobalPos(*geom).Z();
		gt_x100   = t->GTR100Cluster()->GlobalPosT(*geom).X();
		gt_x200   = t->GTR200Cluster()->GlobalPosT(*geom).X();
		gt_x300   = t->GTR300Cluster()->GlobalPosT(*geom).X();
//		gt_y100   = t->GTR100YCluster()->GlobalPosT(*geom).Y();
//		gt_y200   = t->GTR200YCluster()->GlobalPosT(*geom).Y();
//		gt_y300   = t->GTR300YCluster()->GlobalPosT(*geom).Y();
		gt_z100   = t->GTR100Cluster()->GlobalPosT(*geom).Z();
		gt_z200   = t->GTR200Cluster()->GlobalPosT(*geom).Z();
		gt_z300   = t->GTR300Cluster()->GlobalPosT(*geom).Z();
//		std::cout << "cog z 100 " << gc_z100 << std::endl;
		clc_x100 = t->GTR100Cluster()->PeakSum();
		clc_x200 = t->GTR200Cluster()->PeakSum();
		clc_x300 = t->GTR300Cluster()->PeakSum();
//		clc_y100 = t->GTR100YCluster()->PeakSum();
//		clc_y200 = t->GTR200YCluster()->PeakSum();
//		clc_y300 = t->GTR300YCluster()->PeakSum();
		timing_x100 = t->GTR100Cluster()->Timing();
		timing_x200 = t->GTR200Cluster()->Timing();
		timing_x300 = t->GTR300Cluster()->Timing();
//		timing_y100 = t->GTR100YCluster()->Timing();
//		timing_y200 = t->GTR200YCluster()->Timing();
//		timing_y300 = t->GTR300YCluster()->Timing();
		timing2_x100 = t->GTR100Cluster()->Timing2();
		timing2_x200 = t->GTR200Cluster()->Timing2();
		timing2_x300 = t->GTR300Cluster()->Timing2();
//		timing2_y100 = t->GTR100YCluster()->Timing2();
//		timing2_y200 = t->GTR200YCluster()->Timing2();
//		timing2_y300 = t->GTR300YCluster()->Timing2();
		timing3_x100 = t->GTR100Cluster()->Timing3();
		timing3_x200 = t->GTR200Cluster()->Timing3();
		timing3_x300 = t->GTR300Cluster()->Timing3();
//		timing3_y100 = t->GTR100YCluster()->Timing3();
//		timing3_y200 = t->GTR200YCluster()->Timing3();
//		timing3_y300 = t->GTR300YCluster()->Timing3();
		timing4_x100 = t->GTR100Cluster()->Timing4();
		timing4_x200 = t->GTR200Cluster()->Timing4();
		timing4_x300 = t->GTR300Cluster()->Timing4();
//		timing4_y100 = t->GTR100YCluster()->Timing4();
//		timing4_y200 = t->GTR200YCluster()->Timing4();
//		timing4_y300 = t->GTR300YCluster()->Timing4();
//		timing5_x100 = t->GTR100XCluster()->Timing5();
//		timing5_x200 = t->GTR200XCluster()->Timing5();
//		timing5_x300 = t->GTR300XCluster()->Timing5();
//		timing5_y100 = t->GTR100YCluster()->Timing5();
//		timing5_y200 = t->GTR200YCluster()->Timing5();
//		timing5_y300 = t->GTR300YCluster()->Timing5();
		max_riset_x100 = t->GTR100Cluster()->MaxRiset();
		max_riset_x200 = t->GTR200Cluster()->MaxRiset();
		max_riset_x300 = t->GTR300Cluster()->MaxRiset();
		chi2_x = t->Chi2();
//		chi2_y = t->Chi2Y();
		tgt_z  = t->TgtZ();
//		std::cout << "tgt = " << tgt_z <<  std::endl;
//		tgtpos_y = t->TgtPosY();
	    fit_a_x = t->FitA();
	    fit_b_x = t->FitB();
//	    fit_a_y = t->FitAY();
//	    fit_b_y = t->FitBY();
//		if(targets.IsWire()){
//			distance_x = t->DistanceFromTgtXZ();
////			distance_y = t->DistanceFromTgtYR();
//			distance_fromupwire_y   = t->DistanceFromUpWireYR();
//			distance_fromdownwire_y = t->DistanceFromDownWireYR();
//		}
//		distance_fromtgt_y = -1000;
//        distance_fromtgt_y  = t->DistanceYTrackAndTgt();
//		residual_100x = t->Residual100X();
//		residual_200x = t->Residual200X();
//		residual_300x = t->Residual300X();
//		residual_100y = t->Residual100Y();
//		residual_200y =	t->Residual200Y();
//		residual_300y = t->Residual300Y();
//		fitresidual_ssdx = t->FitResidualSSD();
//		fitresidual_100x = t->FitResidual100X();
//		fitresidual_200x = t->FitResidual200X();
//		fitresidual_300x = t->FitResidual300X();
//		fitresidual_100y = t->FitResidual100Y();
//		fitresidual_200y = t->FitResidual200Y();
//		fitresidual_300y = t->FitResidual300Y();
//		fit_g100x = t->FitPtOnGTR100().X();
//		fit_g100y = t->FitPtOnGTR100().Y();
//		fit_g100z = t->FitPtOnGTR100().Z();
//		fit_g200x = t->FitPtOnGTR200().X();
//		fit_g200y = t->FitPtOnGTR200().Y();
//		fit_g200z = t->FitPtOnGTR200().Z();
//		fit_g300x = t->FitPtOnGTR300().X();
//		fit_g300y = t->FitPtOnGTR300().Y();
//		fit_g300z = t->FitPtOnGTR300().Z();
//		x_trk_used_times = t->XZTrackUsedTimes();
		
		timings_100x.clear();
		timings_200x.clear();
		timings_300x.clear();
		positions_100x.clear();
		positions_200x.clear();
		positions_300x.clear();
        
//       fadc_100x.clear();
//       fadc_200x.clear();
//       fadc_300x.clear();
//       fadc_100y.clear();
//       fadc_200y.clear();
//       fadc_300y.clear();
//

//---------for removed layer 
//
		if(removed_layer != -1 || removed_layer != 0){
			SetRemovedLayerInfoHit(record->GTR().Hits(), removed_layer,  t->ModuleID(), fadc_rlx, hsid_rlx, hph_rlx);
			SetRemovedLayerInfoCluster(record->GTR().Clusters(), removed_layer,  t->ModuleID(), clc_rlx, clcog_rlx, clt_rlx);
		}
//
//
        SetHitInfoToBranch(record->GTR().Hits(), t->GTR100Cluster(), fadc_100x, sid_100x, htot_100x, htime_100x, ph_100x,  htots_100x, htote_100x, hpt_100x, hrt_100x);
        SetHitInfoToBranch(record->GTR().Hits(), t->GTR200Cluster(), fadc_200x, sid_200x, htot_200x, htime_200x, ph_200x,  htots_200x, htote_200x, hpt_200x, hrt_300x);
        SetHitInfoToBranch(record->GTR().Hits(), t->GTR300Cluster(), fadc_300x, sid_300x, htot_300x, htime_300x, ph_300x,  htots_300x, htote_300x, hpt_300x, hrt_200x);
//        SetHitInfoToBranch(record->GTR().Hits(), t->GTR100YCluster(), fadc_100y, sid_100y, tot_100y, htime_100y, ph_100y);
//        SetHitInfoToBranch(record->GTR().Hits(), t->GTR200YCluster(), fadc_200y, sid_200y, tot_200y, htime_200y, ph_200y);
//        SetHitInfoToBranch(record->GTR().Hits(), t->GTR300YCluster(), fadc_300y, sid_300y, tot_300y, htime_300y, ph_300y);
 

		tree->Fill();
	}//for x

	for(int i=0; i < sty_tracks.size(); i++){
		std::shared_ptr<E16DST_DST1StraightTrack2D> t = sty_tracks[i];
        run_id     = in_run_id;
		event_id   = t->EventID();
		mod_id     = t->ModuleID();	
		axis       = t->Axis();
		trkid_y    = t->TrackID();
//		hitid_ssdx = t->SSDXHitID();
		hitid_100y = t->ID100Hit();
		hitid_200y = t->ID200Hit();
		hitid_300y = t->ID300Hit();
		cluster_size_g100y = t->GTR100Cluster()->NumHits();
		cluster_size_g200y = t->GTR200Cluster()->NumHits();
		cluster_size_g300y = t->GTR300Cluster()->NumHits();
//		ly100    = t->GTR100Cluster()->CogPos();//local y
//		ly200    = t->GTR200Cluster()->CogPos();//local y
//		ly300    = t->GTR300Cluster()->CogPos();//local y
		cog_y100 = t->GTR100Cluster()->CogPos();
		cog_y200 = t->GTR200Cluster()->CogPos();
		cog_y300 = t->GTR300Cluster()->CogPos();
		gc_y100   = t->GTR100Cluster()->GlobalPos(*geom).Y();
		gc_y200   = t->GTR200Cluster()->GlobalPos(*geom).Y();
		gc_y300   = t->GTR300Cluster()->GlobalPos(*geom).Y();
		gt_y100   = t->GTR100Cluster()->GlobalPosT(*geom).Y();
		gt_y200   = t->GTR200Cluster()->GlobalPosT(*geom).Y();
		gt_y300   = t->GTR300Cluster()->GlobalPosT(*geom).Y();
//		std::cout << "cog z 100 " << gc_z100 << std::endl;
		clc_y100 = t->GTR100Cluster()->PeakSum();
		clc_y200 = t->GTR200Cluster()->PeakSum();
		clc_y300 = t->GTR300Cluster()->PeakSum();
		timing_y100 = t->GTR100Cluster()->Timing();
		timing_y200 = t->GTR200Cluster()->Timing();
		timing_y300 = t->GTR300Cluster()->Timing();
		timing2_y100 = t->GTR100Cluster()->Timing2();
		timing2_y200 = t->GTR200Cluster()->Timing2();
		timing2_y300 = t->GTR300Cluster()->Timing2();
		timing3_y100 = t->GTR100Cluster()->Timing3();
		timing3_y200 = t->GTR200Cluster()->Timing3();
		timing3_y300 = t->GTR300Cluster()->Timing3();
//		timing4_y100 = t->GTR100YCluster()->Timing4();
//		timing4_y200 = t->GTR200YCluster()->Timing4();
//		timing4_y300 = t->GTR300YCluster()->Timing4();
//		timing5_x100 = t->GTR100XCluster()->Timing5();
//		timing5_x200 = t->GTR200XCluster()->Timing5();
//		timing5_x300 = t->GTR300XCluster()->Timing5();
//		timing5_y100 = t->GTR100YCluster()->Timing5();
//		timing5_y200 = t->GTR200YCluster()->Timing5();
//		timing5_y300 = t->GTR300YCluster()->Timing5();
		max_riset_y100 = t->GTR100Cluster()->MaxRiset();
		max_riset_y200 = t->GTR200Cluster()->MaxRiset();
		max_riset_y300 = t->GTR300Cluster()->MaxRiset();
//		chi2_x = t->Chi2();
		chi2_y = t->Chi2();
//		tgt_z  = t->TgtZ();
//		tgtpos_y = t->TgtPosY();
//	    fit_a_x = t->FitA();
//	    fit_b_x = t->FitB();
	    fit_a_y = t->FitA();
	    fit_b_y = t->FitB();
//		if(targets.IsWire()){
//			distance_x = t->DistanceFromTgtXZ();
////			distance_y = t->DistanceFromTgtYR();
//			distance_fromupwire_y   = t->DistanceFromUpWireYR();
//			distance_fromdownwire_y = t->DistanceFromDownWireYR();
//		}
//		distance_fromtgt_y = -1000;
//        distance_fromtgt_y  = t->DistanceYTrackAndTgt();
//		residual_100x = t->Residual100X();
//		residual_200x = t->Residual200X();
//		residual_300x = t->Residual300X();
//		residual_100y = t->Residual100Y();
//		residual_200y =	t->Residual200Y();
//		residual_300y = t->Residual300Y();
//		fitresidual_ssdx = t->FitResidualSSD();
//		fitresidual_100x = t->FitResidual100X();
//		fitresidual_200x = t->FitResidual200X();
//		fitresidual_300x = t->FitResidual300X();
//		fitresidual_100y = t->FitResidual100Y();
//		fitresidual_200y = t->FitResidual200Y();
//		fitresidual_300y = t->FitResidual300Y();
//		fit_g100x = t->FitPtOnGTR100().X();
//		fit_g100y = t->FitPtOnGTR100().Y();
//		fit_g100z = t->FitPtOnGTR100().Z();
//		fit_g200x = t->FitPtOnGTR200().X();
//		fit_g200y = t->FitPtOnGTR200().Y();
//		fit_g200z = t->FitPtOnGTR200().Z();
//		fit_g300x = t->FitPtOnGTR300().X();
//		fit_g300y = t->FitPtOnGTR300().Y();
//		fit_g300z = t->FitPtOnGTR300().Z();
//		x_trk_used_times = t->XZTrackUsedTimes();
		
//		timings_100y.clear();
//		timings_200y.clear();
//		timings_300y.clear();
//		positions_100y.clear();
//		positions_200y.clear();
//		positions_300y.clear();
        
//       fadc_100x.clear();
//       fadc_200x.clear();
//       fadc_300x.clear();
//       fadc_100y.clear();
//       fadc_200y.clear();
//       fadc_300y.clear();
//

//---------for removed layer 
//
//		if(removed_layer != -1 || removed_layer != 0){
//			SetRemovedLayerInfoHit(record->GTR().Hits(), removed_layer,  t->ModuleID(), fadc_rlx, hsid_rlx, hph_rlx);
//			SetRemovedLayerInfoCluster(record->GTR().Clusters(), removed_layer,  t->ModuleID(), clc_rlx, clcog_rlx, clt_rlx);
//		}
//
//
   //     SetHitInfoToBranch(record->GTR().Hits(), t->GTR100Cluster(), fadc_100x, sid_100x, tot_100x, Branch(record->GTR().Hits(), t->GTR200Cluster(), fadc_200x, sid_200x, tot_200x, htime_200x, ph_200x);
   //     SetHitInfoToBranch(record->GTR().Hits(), t->GTR300Cluster(), fadc_300x, sid_300x, tot_300x, htime_300x, ph_300x);
//        SetHitInfoToBranch(record->GTR().Hits(), t->GTR100YCluster(), fadc_100y, sid_100y, tot_100y, htime_100y, ph_100y);
//        SetHitInfoToBranch(record->GTR().Hits(), t->GTR200YCluster(), fadc_200y, sid_200y, tot_200y, htime_200y, ph_200y);
//        SetHitInfoToBranch(record->GTR().Hits(), t->GTR300YCluster(), fadc_300y, sid_300y, tot_300y, htime_300y, ph_300y);
 

		tree->Fill();
	}//y fill
	
	for(int i=0 ; i < cross.size() ; i++){
		std::shared_ptr<E16DST1_DST1CrossByStraight> c = cross[i];
			cp_x    = c->X(); 
			cp_z    = c->Z(); 
			cp_dis  = c->Distance(); 
			cp_chi2_1  = c->Chi2_1(); 
			cp_chi2_2  = c->Chi2_2(); 
			cp_mod1    = c->Mod1();
			cp_mod2    = c->Mod2();
	}
	ctree->Fill();

	
//	if(st_tracks.size() != 0)std::cout << "st_tracks size =  " << st_tracks.size() << std::endl;
//	gtrhist->Fill(st_tracks);
//	gtrhist->Fill();	
    ++n_event;
    ++n_physics_event;
  }
  f->Write();

 

  TCanvas *c0 = new TCanvas("c0", "c0", 1024, 768);
  TString pdf_name;
  pdf_name.Form("gtrtest.pdf");
  c0->SaveAs(pdf_name + "[", "pdf");

  TCanvas *c1 = new TCanvas();
  c1->Divide(3,2);
  for(int m=102; m < 109 ; m++){
    if(m == 105) continue;
	c1->cd(m-101);
   	gtrhist->h_tgt_z[m-100]->Draw();
	if(m>105 ){
		c1->cd(m-102);
	    gtrhist->h_tgt_z[m-100]->Draw();
	}
  }
  c1->SaveAs(pdf_name, "pdf");



//
//  TCanvas *c_cl_charge_x[10]; 
//  //= new TCanvas("cl charge ", 100,0,100);
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_charge_x[m-102] = new TCanvas(Form("ccx%d", m-102) , Form("ccx%d", m-102), 1024, 768);
//    c_cl_charge_x[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_charge_x[m-102]->cd(l+1);
//        gtrhist->h_cl_charge_x[m-100][l]->Draw();
//    }
//    c_cl_charge_x[m-102]->SaveAs(pdf_name, "pdf");
//  }
// 
//  TCanvas *c_cl_charge_y[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_charge_y[m-102] = new TCanvas(Form("ccy%d", m-102), Form("ccy%d", m-102), 1024, 768);
//    c_cl_charge_y[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_charge_y[m-102]->cd(l+1);
//        gtrhist->h_cl_charge_y[m-100][l]->Draw();
//    }
//    c_cl_charge_y[m-102]->SaveAs(pdf_name, "pdf");
//  }
//  
//  TCanvas *c_cl_charge_yb[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_charge_yb[m-102] = new TCanvas(Form("ccyb%d", m-102), Form("ccyb%d", m-102), 1024, 768);
//    c_cl_charge_yb[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_charge_yb[m-102]->cd(l+1);
//        gtrhist->h_cl_charge_yb[m-100][l]->Draw();
//    }
//    c_cl_charge_yb[m-102]->SaveAs(pdf_name, "pdf");
//  }
//  
//  TCanvas *c_cl_local_x[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_local_x[m-102] = new TCanvas(Form("clx%d", m-102), Form("clx%d", m-102), 1024, 768);
//    c_cl_local_x[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_local_x[m-102]->cd(l+1);
//        gtrhist->h_cl_local_x[m-100][l]->Draw();
//    }
//    c_cl_local_x[m-102]->SaveAs(pdf_name, "pdf");
//  }
//
//  TCanvas *c_cl_local_y[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_local_y[m-102] = new TCanvas(Form("cly%d", m-102), Form("cly%d", m-102), 1024, 768);
//    c_cl_local_y[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_local_y[m-102]->cd(l+1);
//        gtrhist->h_cl_local_y[m-100][l]->Draw();
//    }
//    c_cl_local_y[m-102]->SaveAs(pdf_name, "pdf");
//  }
//   TCanvas *c_cl_local_yb[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_local_yb[m-102] = new TCanvas(Form("clyb%d",m-102), Form("clyb%d", m-102), 1024, 768);
//    c_cl_local_yb[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_local_yb[m-102]->cd(l+1);
//        gtrhist->h_cl_local_yb[m-100][l]->Draw();
//    }
//    c_cl_local_yb[m-102]->SaveAs(pdf_name, "pdf");
//  }
// 
//  TCanvas *c_cl_max_peak_x[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_max_peak_x[m-102] = new TCanvas(Form("clmpx%d", m-102), Form("clmpx%d", m-102), 1024, 768);
//    c_cl_max_peak_x[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_max_peak_x[m-102]->cd(l+1);
//        gtrhist->h_cl_max_peak_x[m-100][l]->Draw();
//    }
//    c_cl_max_peak_x[m-102]->SaveAs(pdf_name, "pdf");
//  }
//  
//  TCanvas *c_cl_max_peak_y[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_max_peak_y[m-102] = new TCanvas(Form("clmpy%d",m-102), Form("clmpy%d", m-102), 1024, 768);
//    c_cl_max_peak_y[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_max_peak_y[m-102]->cd(l+1);
//        gtrhist->h_cl_max_peak_y[m-100][l]->Draw();
//    }
//    c_cl_max_peak_y[m-102]->SaveAs(pdf_name, "pdf");
//  }
//
//  TCanvas *c_cl_max_peak_yb[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_max_peak_yb[m-102] = new TCanvas(Form("clmpyb%d", m-102), Form("clmpyb%d", m-102), 1024, 768);
//    c_cl_max_peak_yb[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_max_peak_yb[m-102]->cd(l+1);
//        gtrhist->h_cl_max_peak_yb[m-100][l]->Draw();
//    }
//    c_cl_max_peak_yb[m-102]->SaveAs(pdf_name, "pdf");
//  }
//
//  TCanvas *c_cl_max_peak_ch_x[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_max_peak_ch_x[m-102] = new TCanvas(Form("clmpchx%d", m-102), Form("clmpchx%d", m-102), 1024, 768);
//    c_cl_max_peak_ch_x[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_max_peak_ch_x[m-102]->cd(l+1);
//        gtrhist->h_cl_max_peak_ch_x[m-100][l]->Draw();
//    }
//    c_cl_max_peak_x[m-102]->SaveAs(pdf_name, "pdf");
//  }
// 
//  TCanvas *c_cl_tdcpos_x[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_tdcpos_x[m-102] = new TCanvas(Form("cltdcposx%d", m-102), Form("cltdcposx%d", m-102), 1024, 768);
//    c_cl_tdcpos_x[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_tdcpos_x[m-102]->cd(l+1);
//        gtrhist->h_cl_tdcpos_x[m-100][l]->Draw();
//    }
//    c_cl_tdcpos_x[m-102]->SaveAs(pdf_name, "pdf");
//  }
// 
//  TCanvas *c_cl_tdcpos_y[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_tdcpos_y[m-102] = new TCanvas(Form("cltdcposy%d", m-102), Form("cltdcposy%d", m-102), 1024, 768);
//    c_cl_tdcpos_y[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_tdcpos_x[m-102]->cd(l+1);
//        gtrhist->h_cl_tdcpos_y[m-100][l]->Draw();
//    }
//    c_cl_tdcpos_y[m-102]->SaveAs(pdf_name, "pdf");
//  }
//   TCanvas *c_cl_tdcpos_yb[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_tdcpos_yb[m-102] = new TCanvas(Form("cltdcposyb%d", m-102), Form("cltdcposyb%d", m-102), 1024, 768);
//    c_cl_tdcpos_yb[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_tdcpos_yb[m-102]->cd(l+1);
//        gtrhist->h_cl_tdcpos_yb[m-100][l]->Draw();
//    }
//    c_cl_tdcpos_yb[m-102]->SaveAs(pdf_name, "pdf");
//  }
//
//  TCanvas *c_cl_tan_x[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_tan_x[m-102] = new TCanvas(Form("cltanx%d", m-102), Form("cltanx%d", m-102), 1024, 768);
//    c_cl_tan_x[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_tan_x[m-102]->cd(l+1);
//        gtrhist->h_cl_tan_x[m-100][l]->Draw();
//    }
//    c_cl_tan_x[m-102]->SaveAs(pdf_name, "pdf");
//  }
//   TCanvas *c_cl_tan_y[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_tan_y[m-102] = new TCanvas(Form("cltany%d", m-102), Form("cltany%d", m-102), 1024, 768);
//    c_cl_tan_y[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_tan_y[m-102]->cd(l+1);
//        gtrhist->h_cl_tan_y[m-100][l]->Draw();
//    }
//    c_cl_tan_y[m-102]->SaveAs(pdf_name, "pdf");
//  }
//    TCanvas *c_cl_tan_yb[10]; 
//  for(int m=102; m < 109 ; m++){
//    if(m == 105) continue;
//    c_cl_tan_yb[m-102] = new TCanvas(Form("cltanyb%d", m-102), Form("cltanyb%d", m-102), 1024, 768);
//    c_cl_tan_yb[m-102]->Divide(2,2);
//    for(int l=0; l < 3; l++){
//        c_cl_tan_yb[m-102]->cd(l+1);
//        gtrhist->h_cl_tan_yb[m-100][l]->Draw();
//    }
//    c_cl_tan_yb[m-102]->SaveAs(pdf_name, "pdf");
//  }
// 
//
  c0->SaveAs( pdf_name + "]", "pdf");
//

//  delete geometry;
  delete dst0;
//  dst1->Close();
  return 0;
}
