#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TGraph2D.h>
#include <TStyle.h>
// #include <boost/program_options.hpp>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"
#include "E16ANA_LGConstant.hh"
#include "E16ANA_LGDeadChannel.hh"
#include "E16ANA_LGClustering.hh"
#include "E16DST_Constant.hh"

using namespace std;
// namespace  bpo = boost::program_options;

double CalcAngzx(int module){
  const double PI = acos(-1.);
  if(module==106){
    return PI/6.;
  }
  else if(module==107){
    return PI/3.;
  }
  else if(module==108){
    return PI/2.;
  }
  else if(module==109){
    return PI*2./3.;
  }
  else if(module==104){
    return -PI/6.;
  }
  else if(module==103){
    return -PI/3.;
  }
  else if(module==102){
    return -PI/2.;
  }
  else if(module==101){
    return -PI*2./3.;
  }
  else{
    std::cout<<"invalid mid"<<std::endl;
    return -10000.;
  }
}
double CalcAngyz(int block){
  const double PI = acos(-1.);
  int blky = block/10;
  if(blky==0){
    return -PI*14./180.;
  }
  else if(blky==1){
    return -PI*9.6/180.;
  }
  else if(blky==2){
    return -PI*4.9/180.;
  }
  else if(blky==3){
    return PI*4.9/180.;
  }
  else if(blky==4){
    return PI*9.6/180.;
  }
  else if(blky==5){
    return PI*14./180.;
  }
  else{
    std::cout<<"invalid cid"<<std::endl;
    return -10000.;
  }
}

int main(int argc, char* argv[]) {
  if (argc != 5) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst0] [output.dst1] [run ID] [max physics event (all: -1)] " << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  auto run_id        = stoi(argv[3]);
  auto max_event     = stoi(argv[4]);

  TString fout = Form("%s",out_file_name);
  TGraph2D* gabs = new TGraph2D(304);
  TGraph2D* gthe = new TGraph2D(304);
  int mod[8] = {109,108,107,106,104,103,102,101};
  TH2F* habs[8];
  TH2F* hthe[8];
  for(int i=0;i<8;i++){
    habs[i] = new TH2F(Form("habs%d",i),Form("mag_abs_%d",mod[i]),7,0,7,6,0,6);
    hthe[i] = new TH2F(Form("hthe%d",i),Form("mag_theta_%d",mod[i]),7,0,7,6,0,6);
  }

  int module, block;

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  // E16ANA_TriggerCalibParam trigger_param;
  // trigger_param.ReadConstantData(calib.CurrentRunID());
  // bool TrigIsAWmax = trigger_param.IsMaximumWidth();
  // int TrigAWmax = trigger_param.MaximumWidth();
  // int TrigAWmin = trigger_param.MinimumWidth();
  // int TrigTW = trigger_param.TimeWidth();
  // if(!TrigIsAWmax){TrigAWmax=10000;}
  // bool TrigIsAWmax = false;
  // int TrigAWmax = -10000;
  // int TrigAWmin = -10000;
  // int TrigTW = -10000;

  E16ANA_LGBasic lgbasic;
  E16ANA_LGDeadChannel lgdead;
  lgbasic.SetMap();
  lgbasic.SetCalibMap();//it is necessary to use energy deposit and calibrated timing.
  lgbasic.SetTemplate();
  lgdead.ReadDeadChannelData();

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  E16ANA_GeometryV2::SetGlobalPointer(geometry);
  auto bfield_map = new E16ANA_MagneticFieldMap3D(static_cast<std::string>(MagneticFieldMapFile));
  bfield_map->Initialize_binary();
  E16ANA_MagneticFieldMap::SetGlobalPointer(bfield_map);
  
  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }
  E16DST_DST1PhysicsRecord record;

  // std::ofstream tableout("./table.txt");

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
      // auto& ssd_hits0         = event0->SSD();
      // auto& gtr_hits0         = event0->GTR();
      // auto& hbd_hits0         = event0->HBD();
      auto& lg_hits0          = event0->LG();
      // auto& trigger_gtr_hits0 = event0->TriggerGTR();
      // auto& trigger_hbd_hits0 = event0->TriggerHBD();
      // auto& trigger_lg_hits0  = event0->TriggerLG();
      auto event_id = event0->EventID();

      E16DST_DST1LGFactory(lg_hits0, &record.LG(), 0, geometry); // w/ fit
      record.LG().AddHitAndClusterIds();
      record.LG().UpdatePtrs();
      // E16DST_DST1TriggerFactory(trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record.Trigger());
      // record.Trigger().AddHitAndClusterIDs();
      // record.Trigger().UpdatePtrs();

//// Check begin
//// LG

//dst0hit
      for (int n_hit = 0; n_hit < lg_hits0.NumberOfHits(); ++n_hit) {
	auto hit0 = lg_hits0.Hit(n_hit);
	module = hit0.ModuleID();
	block = hit0.BlockID();

	TVector3 tlpos(0.,0.,0.);
	if(block>=0&&block<10){
	  tlpos.SetY(-143.1);
	  tlpos.SetZ(32.0);
	}
	else if(block>=10&&block<20){
	  tlpos.SetY(-135.0);
	  tlpos.SetZ(43.9);
	}
	else if(block>=20&&block<30){
	  tlpos.SetY(-142.3);
	  tlpos.SetZ(53.5);
	}
	else if(block>=30&&block<40){
	  tlpos.SetY(142.3);
	  tlpos.SetZ(53.5);
	}
	else if(block>=40&&block<50){
	  tlpos.SetY(135.0);
	  tlpos.SetZ(43.9);
	}
	else if(block>=50&&block<60){
	  tlpos.SetY(143.1);
	  tlpos.SetZ(32.0);
	}
	int valmod = E16DST_DST1Constant::kModuleId2020To2013[module/100][module%100+1];
	TVector3 tgpos = geometry->LG(valmod,block)->GetGPos(tlpos);
	std::cout<<module<<" "<<block<<" "<<tgpos.X()<<" "<<tgpos.Y()<<" "<<tgpos.Z()<<std::endl;

	double B[3];
	double point[3] = { tgpos.X()/10., tgpos.Y()/10., tgpos.Z()/10. };// mm -> cm
	bfield_map->GetFieldValue(point, B, 0);
	std::cout<<module<<" "<<block<<" "<<B[0]<<" "<<B[1]<<" "<<B[2]<<std::endl;

	TVector3 mag;
	mag.SetXYZ(B[0],B[1],B[2]);
	double angzx = CalcAngzx(module);
	double angyz = CalcAngyz(block);

	double abs = mag.Mag() * 0.0001;//Tesla
	TVector3 nx(1,0,0);
	TVector3 ny(0,1,0);
	TVector3 nz(0,0,1);
	nx.Rotate(angzx,ny);
	ny.Rotate(angzx,ny);
	nz.Rotate(angzx,ny);
	nx.Rotate(angyz,nx);
	ny.Rotate(angyz,nx);
	nz.Rotate(angyz,nx);
	double theta = mag.Angle(-ny);
	double theta_deg = theta*180./acos(-1);
	std::cout<<module<<" "<<block<<" "<< abs <<" "<< theta <<" "<< theta_deg <<std::endl;

	gabs->SetPoint(n_hit,(double)module,(double)block,abs);
	gthe->SetPoint(n_hit,(double)module,(double)block,theta_deg);

	for(int j=0;j<8;j++){
	  if(module==mod[j]){
	    int x = block%10 + 1;
	    int y = block/10 + 1;
	    habs[j]->SetBinContent(x,y,abs);
	    hthe[j]->SetBinContent(x,y,theta_deg);
	  }
	}

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

  gStyle->SetOptStat(0000);
  gStyle->SetPaintTextFormat("2.2f");
  TCanvas* c = new TCanvas("c","c",1400,500);
  c->Divide(2,1);
  c->cd(1);
  gabs->SetMarkerStyle(20);
  gabs->Draw("pcol");
  c->cd(2);
  gthe->SetMarkerStyle(20);
  gthe->Draw("pcol");

  TCanvas* cm = new TCanvas("cm","cm",1000,1000);
  cm->Divide(4,4);
  for(int i=0;i<8;i++){
    cm->cd(i+1+4*(i/4));
    habs[i]->GetZaxis()->SetRangeUser(0,0.3);
    habs[i]->SetMarkerSize(2);
    habs[i]->Draw("colz text");
    cm->cd(i+1+4*(i/4)+4);
    hthe[i]->GetZaxis()->SetRangeUser(0,70);
    hthe[i]->SetMarkerSize(2);
    hthe[i]->Draw("colz text");
  }

  c->SaveAs(fout+"[","pdf");
  c->SaveAs(fout,"pdf");
  cm->SaveAs(fout,"pdf");
  cm->SaveAs(fout+"]","pdf");

  delete geometry;
  delete dst0;
//  dst1->Close();
  return 0;
}
