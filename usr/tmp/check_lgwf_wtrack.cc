#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TGraph.h>
#include <TLine.h>
#include <TLegend.h>
//#include <boost/program_options.hpp>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"

using namespace std;
//namespace  bpo = boost::program_options;

int main(int argc, char* argv[]) {
  if (argc != 5) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst0] [run ID] [module ID] [max event]" << endl;
    return -1;
  }
  auto in_file_name = argv[1];
  auto run_id        = stoi(argv[2]);
  auto module_id     = stoi(argv[3]);
  auto max_event     = stoi(argv[4]);
  std::string s_run_id = argv[2];
  std::string s_module_id = argv[3];
  std::string infilename = "/ccj/u/nakasuga/work/dst1ana/track/wf" + s_module_id + ".txt";
  std::ifstream fin(infilename);

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  auto trigger_param = new E16ANA_TriggerCalibParam();
  trigger_param->ReadConstantData(calib.CurrentRunID());
  E16ANA_GTRcalibPedestal gtrped;
  gtrped.ReadCalibData( calib.CurrentRunID() );
  E16ANA_LGBasic lgbasic;
  lgbasic.SetMap();
  lgbasic.SetCalibMap();//it is necessary to use energy deposit and calibrated timing.

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  
  auto record = new E16DST_DST1PhysicsRecord();

  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }

  int trun, tevent, tmod, tblock, tcharge, tncan, tcan;
  std::vector<int> tvcan(0);
  double tposx, tposy, tangx, tangy, tmom, tssdt;
  bool read = true;
  while(read&&!fin.eof()){
    tvcan.clear();
    fin >> trun >> tevent >> tmod >> tblock >> tposx >> tposy >> tangx >> tangy >> tmom >> tssdt >> tcharge >> tncan;
    for(int it=0;it<tncan;it++){
      fin >> tcan;
      tvcan.push_back(tcan);
    }
    if(trun==run_id){
      read = false;
    }
  }
  std::cout << trun <<" "<< tevent <<" "<< tmod <<" "<< tblock <<" "<< tposx <<" "<< tposy <<" "<< tangx <<" "<< tangy <<" "<< tmom <<" "<< tssdt <<" "<< tcharge <<" "<< tncan << std::endl;


  if(!read){//track exist

  std::vector<TGraph*> gwf[9];
  TString outfile = "run" + s_run_id + "mod" + s_module_id + ".pdf";
  TCanvas* c = new TCanvas("c","c",700,500);
  c->SaveAs(outfile+"[","pdf");

  //event loop
  int n_event = 0;
  int n_physics_event = 0;
  while (dst0->ReadAnEvent()) {
    if (max_event != -1 && n_physics_event >= max_event) {
      break;
    }
    if (n_event % 1000 == 0) {
      cout << "Number of event: " << n_event << endl;
    }
    auto event_type = dst0->EventType();

    if (event_type == E16DST_DST0EventType::Physics) {
      auto event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());

      if(event0->EventID()!=tevent) continue;

      std::cout<<event0->EventID()<<std::endl;

      auto& lg_hits0          = event0->LG();
      auto& trigger_gtr_hits0 = event0->TriggerGTR();
      auto& trigger_hbd_hits0 = event0->TriggerHBD();
      auto& trigger_lg_hits0  = event0->TriggerLG();
      E16DST_DST1LGFactory(lg_hits0, &record->LG(), 1, geometry);
      E16DST_DST1TriggerFactory(*trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record->Trigger());

//// Check begin
//// LG
      int block[9];
      block[0] = tblock + 11;
      block[1] = tblock + 10;
      block[2] = tblock + 9;
      block[3] = tblock + 1;
      block[4] = tblock;
      block[5] = tblock - 1;
      block[6] = tblock - 9;
      block[7] = tblock - 10;
      block[8] = tblock - 11;
      double iteration[200];
      double waveform[9][200];
      for(int j=0;j<200;j++){
	iteration[j] = j;
	for(int i=0;i<9;i++){
	  waveform[i][j] = {-10000.};
	}
      }

      for (int n_hit = 0; n_hit < lg_hits0.NumberOfHits(); ++n_hit) {//dst0hit loop
	auto hit0 = lg_hits0.Hit(n_hit);
	auto spec = lgbasic.GetSpec(hit0.ModuleID(),hit0.BlockID());
	double wftype = spec->WF_TYPE;//relative gain of DRS4module
	double t0 = lgbasic.GetT0(hit0.ModuleID(),hit0.BlockID());
	// int status = lgdead.Status(hit0.ModuleID(),hit0.BlockID());
	// if( status!=0 ){
	//   continue;
	// }
	if(hit0.ModuleID()==tmod&&hit0.BlockID()==block[0]){
	  for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
	    waveform[0][cell] = wftype*(double)(hit0.Waveform()[cell]);
	  }
	}
	else if(hit0.ModuleID()==tmod&&hit0.BlockID()==block[1]){
	  for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
	    waveform[1][cell] = wftype*(double)(hit0.Waveform()[cell]);
	  }
	}
	else if(hit0.ModuleID()==tmod&&hit0.BlockID()==block[2]){
	  for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
	    waveform[2][cell] = wftype*(double)(hit0.Waveform()[cell]);
	  }
	}
	else if(hit0.ModuleID()==tmod&&hit0.BlockID()==block[3]){
	  for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
	    waveform[3][cell] = wftype*(double)(hit0.Waveform()[cell]);
	  }
	}
	else if(hit0.ModuleID()==tmod&&hit0.BlockID()==block[4]){
	  for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
	    waveform[4][cell] = wftype*(double)(hit0.Waveform()[cell]);
	  }
	}
	else if(hit0.ModuleID()==tmod&&hit0.BlockID()==block[5]){
	  for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
	    waveform[5][cell] = wftype*(double)(hit0.Waveform()[cell]);
	  }
	}
	else if(hit0.ModuleID()==tmod&&hit0.BlockID()==block[6]){
	  for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
	    waveform[6][cell] = wftype*(double)(hit0.Waveform()[cell]);
	  }
	}
	else if(hit0.ModuleID()==tmod&&hit0.BlockID()==block[7]){
	  for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
	    waveform[7][cell] = wftype*(double)(hit0.Waveform()[cell]);
	  }
	}
	else if(hit0.ModuleID()==tmod&&hit0.BlockID()==block[8]){
	  for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
	    waveform[8][cell] = wftype*(double)(hit0.Waveform()[cell]);
	  }
	}

      }//dst0hit loop

      c->Clear();
      c->Divide(3,3);
      for(int ic=0;ic<9;ic++){
	c->cd(ic+1)->SetGrid();
	bool in_cluster = false;
	for(int it=0;it<tncan;it++){
	  if(tvcan.at(it)==block[ic]){
	    in_cluster = true;
	    break;
	  }
	}
	TGraph* gtmp = new TGraph(200,iteration,waveform[ic]);
	gtmp->SetTitle(Form("run%06d mod%d blk%d",run_id,tmod,block[ic]));
	gtmp->GetXaxis()->SetLimits(0,200);
	gtmp->SetMaximum(150.);
	gtmp->SetMinimum(0.);
	if(in_cluster){
	  gtmp->SetLineColor(2);
	  gtmp->SetMarkerColor(2);
	}
	gwf[ic].push_back(gtmp);
	gwf[ic].at(gwf[ic].size()-1)->Draw("AL");
	TLine *l = new TLine(tssdt,0,tssdt,150);
	l->SetLineColor(4);
	l->Draw("sames");
	TLine *l2 = new TLine(tssdt-21.,0,tssdt-21.,150);
	l2->SetLineColor(4);
	l2->Draw("sames");
	TLine *l3 = new TLine(tssdt+21.,0,tssdt+21.,150);
	l3->SetLineColor(4);
	l3->Draw("sames");
      }
      TLegend* leg = new TLegend(0.7,0.7,0.9,0.9);
      leg->AddEntry((TObject*)0,Form("ly: %1.1f",tposy),"");
      leg->AddEntry((TObject*)0,Form("p: %1.2f",tmom),"");
      leg->AddEntry((TObject*)0,Form("c: %d",tcharge),"");
      leg->Draw();
      c->SaveAs(outfile, "pdf");

      tvcan.clear();
      fin >> trun >> tevent >> tmod >> tblock >> tposx >> tposy >> tangx >> tangy >> tmom >> tssdt >> tcharge >> tncan;
      for(int it=0;it<tncan;it++){
	fin >> tcan;
	tvcan.push_back(tcan);
      }

    } else if (event_type == E16DST_DST0EventType::Scaler) {
      auto event0 = dynamic_cast<E16DST_DST0ScalerEvent*>(dst0->Event());
//      dst1->WriteAnEvent(event0);
    } else if (event_type == E16DST_DST0EventType::SpillStart) {
      auto event0 = dynamic_cast<E16DST_DST0SpillStartEvent*>(dst0->Event());
//      dst1->WriteAnEvent(event0);
    } else if (event_type == E16DST_DST0EventType::SpillEnd) {
      auto event0 = dynamic_cast<E16DST_DST0SpillEndEvent*>(dst0->Event());
//      dst1->WriteAnEvent(event0);
    } else {
      std::cerr << "Invalid Event Type: " << event_type << std::endl;
      return -1;
    }
    ++n_event;
    ++n_physics_event;
  }

  c->SaveAs(outfile+"]","pdf");

  }//track exist

  delete geometry;
  delete dst0;
//  dst1->Close();
  return 0;
}
