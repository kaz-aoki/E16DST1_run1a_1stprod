#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
//#include <boost/program_options.hpp>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_Constant.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16DST_DST1DefaultFilePath.hh"

#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"

#include "E16ANA_WaveformFitter.hh"
#include "E16ANA_HBDCalibration.hh"
#include "E16ANA_HBDCut.hh"
#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_HBDChannelManager.hh"
#include "E16ANA_HBDConstant.hh"
#include "E16ANA_HBDClusterAnalysis.hh"

#include "E16ANA_GTRcalib.hh"
#include "GTR/GTRCheckHist.hh"
#include "E16ANA_TargetInfo.hh"

#include "E16ANA_RundependentName.hh"
#include "straight_track/StraightTrackAnalyzerV0.h"
#include "E16ANA_GeometryV2.hh"

using namespace std;
//namespace  bpo = boost::program_options;

int c_mid(int mid){
  int c=-1;
  if(mid==101||mid==102||mid==103||mid==104){
    c=mid-101;
  }
  if(mid==106||mid==107||mid==108||mid==109){
    c=mid-102;
  }
  return c;
}

int m_cid(int cid){
  int m=-1;
  if(cid==0||cid==1||cid==2||cid==3){
    m=cid+101;
  }
  if(cid==4||cid==5||cid==6||cid==7){
    m=cid+102;
  }
  return m;
}

double rtod(double rad){
  return rad*180./TMath::Pi();
}

double dtor(double deg){
  return deg*TMath::Pi()/180.;
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
//  bpo::variables_map vm;
//  string in_file_name;
//  string out_file_name;
//  int run_num;


  TFile *fout = new TFile(out_file_name,"recreate");
  TTree *tree = new TTree("tree","tree");

  int event;

  const int HMAX = 1000;
  const int CMAX = 1000;
  const int TMAX = 1000;

  int ntr;
  int module[TMAX];
  float chi2x[TMAX];
  float chi2y[TMAX];
  float tgtz[TMAX];
  float tgty[TMAX];
  float distzx[TMAX];
  float distyr[TMAX];
  float res0[TMAX];
  float res1[TMAX];
  float res2[TMAX];
  float res3[TMAX];
  float res1y[TMAX];
  float res2y[TMAX];
  float res3y[TMAX];

  int ssd_nhs[TMAX];
  int ssd_ncs[TMAX];
  int lg_nhs[TMAX];
  int lg_ncs[TMAX];
  double ssdclx[TMAX];
  double lgclx[TMAX];
  double lgcly[TMAX];

  tree->Branch("ntr",&ntr,"ntr/I");
  tree->Branch("module",module,"module[ntr]/I");
  tree->Branch("chi2x",chi2x,"chi2x[ntr]/F");
  tree->Branch("chi2y",chi2y,"chi2y[ntr]/F");
  tree->Branch("tgtz",tgtz,"tgtz[ntr]/F");
  tree->Branch("tgty",tgty,"tgty[ntr]/F");
  tree->Branch("distzx",distzx,"distzx[ntr]/F");
  tree->Branch("distyr",distyr,"distyr[ntr]/F");
  tree->Branch("res0",res0,"res0[ntr]/F");
  tree->Branch("res1",res1,"res1[ntr]/F");
  tree->Branch("res2",res2,"res2[ntr]/F");
  tree->Branch("res3",res3,"res3[ntr]/F");
  tree->Branch("res1y",res1y,"res1y[ntr]/F");
  tree->Branch("res2y",res2y,"res2y[ntr]/F");
  tree->Branch("res3y",res3y,"res3y[ntr]/F");

  tree->Branch("ssd_nhs",ssd_nhs,"ssd_nhs[ntr]/I");
  tree->Branch("ssd_ncs",ssd_ncs,"ssd_ncs[ntr]/I");
  tree->Branch("lg_nhs",lg_nhs,"lg_nhs[ntr]/I");
  tree->Branch("lg_ncs",lg_ncs,"lg_ncs[ntr]/I");
  tree->Branch("ssdclx",ssdclx,"ssdclx[ntr]/D");
  tree->Branch("lgclx",lgclx,"lgclx[ntr]/D");
  tree->Branch("lgcly",lgcly,"lgcly[ntr]/D");

  TH1F *hssdrx = new TH1F("hssdrx","SSDResidualLx",800,-400,400);
  TH1F *hlgrx = new TH1F("hlgrx","LGResidualLx",800,-400,400);
  TH1F *hlgry = new TH1F("hlgry","LGResidualLy",800,-400,400);
  TH1F *hssdrxn = new TH1F("hssdrxn","SSDResidualLx1Hit",800,-400,400);
  TH1F *hlgrxn = new TH1F("hlgrxn","LGResidualLx1Hit",800,-400,400);
  TH1F *hlgryn = new TH1F("hlgryn","LGResidualLy1Hit",800,-400,400);


  /*
  const char par[8][12] = {"Nhits", "Nclusters", "ClusterSize", "Tdc", "Adc", "Lx", "Ly", "Residual"};
  const char det[6][10] = {"SSD", "GTR100", "GTR200", "GTR300", "HBD", "LG"};
  const char mod[8][5] = {"101", "102", "103", "104", "106", "107", "108", "109"};

  TH1F* hnh[6][8];
  TH1F* hnc[6][8];
  TH1F* hcs[6][8];
  TH1F* htd[6][8];
  TH1F* had[6][8];
  TH1F* hlx[6][8];
  TH1F* hly[6][8];
  TH1F* hre[6][8];

  TH1F* hres[8];
  TH1F* htgz[8];
  TH1F* hch2[8];

  for(int i=0;i<6;i++){//det loop
    for(int j=0;j<8;j++){// mod loop
      hnh[i][j] = new TH1F(Form("hnh%d%d",i,j),Form("%s%s%s",par[0],det[i],mod[j]),1000,0,1000);
      hnc[i][j] = new TH1F(Form("hnc%d%d",i,j),Form("%s%s%s",par[1],det[i],mod[j]),300,0,300);
      hcs[i][j] = new TH1F(Form("hcs%d%d",i,j),Form("%s%s%s",par[2],det[i],mod[j]),50,0,50);
      htd[i][j] = new TH1F(Form("htd%d%d",i,j),Form("%s%s%s",par[3],det[i],mod[j]),600,0,600);
      hlx[i][j] = new TH1F(Form("hlx%d%d",i,j),Form("%s%s%s",par[5],det[i],mod[j]),800,-400,400);
      hly[i][j] = new TH1F(Form("hly%d%d",i,j),Form("%s%s%s",par[6],det[i],mod[j]),800,-400,400);
      hre[i][j] = new TH1F(Form("hre%d%d",i,j),Form("%s%s%s",par[7],det[i],mod[j]),8000,-400,400);
    }
  }
  for(int j=0;j<8;j++){// mod loop
    had[0][j] = new TH1F(Form("had%d%d",0,j),Form("%s%s%s",par[4],det[0],mod[j]),100,0,10000);//ssd
    had[1][j] = new TH1F(Form("had%d%d",1,j),Form("%s%s%s",par[4],det[1],mod[j]),100,0,50000);//gtr100
    had[2][j] = new TH1F(Form("had%d%d",2,j),Form("%s%s%s",par[4],det[2],mod[j]),100,0,50000);//gtr200
    had[3][j] = new TH1F(Form("had%d%d",3,j),Form("%s%s%s",par[4],det[3],mod[j]),100,0,50000);//gtr300
    had[4][j] = new TH1F(Form("had%d%d",4,j),Form("%s%s%s",par[4],det[4],mod[j]),1000,0,0.01);//hbd
    had[5][j] = new TH1F(Form("had%d%d",5,j),Form("%s%s%s",par[4],det[5],mod[j]),1000,0,1000);//lg
    hres[j] = new TH1F(Form("hres%d%d",0,j),Form("%s%s%s","Residual","Track",mod[j]),1000,-100,100);//track
    htgz[j] = new TH1F(Form("htgz%d%d",0,j),Form("%s%s%s","TargetZ","Track",mod[j]),1000,-100,100);//track
    hch2[j] = new TH1F(Form("hch2%d%d",0,j),Form("%s%s%s","Chi2","Track",mod[j]),1000,0,100);//track
  }
  */


  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);

  //  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  E16ANA_RundependentName& name = E16ANA_RundependentName::Instance();
  string geomName = name.ReadNameWithRunID(run_id, "geometry", "/ccj/u/E16/database/");
  E16ANA_GeometryV2* geom = new E16ANA_GeometryV2(geomName);
  E16ANA_GeometryV2::SetGlobalPointer(geom);

  auto trigger_param = new E16ANA_TriggerCalibParam();
  trigger_param->ReadConstantData(calib.CurrentRunID());
  E16ANA_GTRcalibPedestal gtrped;
  gtrped.ReadCalibData( calib.CurrentRunID() );
  E16ANA_LGBasic lgbasic;
  lgbasic.SetCalibMap();//it is necessary to use energy deposit and calibrated timing.
  E16ANA_TargetInfoManager& targets = E16ANA_TargetInfoManager::Instance();
  targets.ReadInfoWithRunID( calib.CurrentRunID());
  targets.Print();

  //HBD initialize
  E16ANA_HBDCalibration *hbd_calib = new E16ANA_HBDCalibration();
  hbd_calib->ReadCalibrationData(calib.CurrentRunID());
  E16ANA_HBDCut *hbd_cut = new E16ANA_HBDCut();
  hbd_cut->ReadCutData(calib.CurrentRunID());
  std::string hbd_waveform_template = calib.CalibFileName("HBD-waveform-template", 0);
  E16ANA_WaveformFitter *wf1d_fitter = new E16ANA_WaveformFitter(hbd_waveform_template);


  auto record = new E16DST_DST1PhysicsRecord();

  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }

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
////////    dst1->SetEventType(event_type);
    if (event_type == E16DST_DST0EventType::Physics) {
      auto event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
      auto& ssd_hits0         = event0->SSD();
      auto& gtr_hits0         = event0->GTR();
      auto& hbd_hits0         = event0->HBD();
      auto& lg_hits0          = event0->LG();
      auto& trigger_gtr_hits0 = event0->TriggerGTR();
      auto& trigger_hbd_hits0 = event0->TriggerHBD();
      auto& trigger_lg_hits0  = event0->TriggerLG();

      E16DST_DST1SSDFactory(ssd_hits0, &record->SSD());
      E16DST_DST1GTRFactory(gtr_hits0, &record->GTR(), gtrped);
      E16DST_DST1HBDFactory(hbd_hits0, hbd_calib, hbd_cut, wf1d_fitter, &record->HBD());
      E16DST_DST1LGFactory(lg_hits0, &record->LG(), 1);
//      E16DST_DST1TriggerFactory(*trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &event1->Trigger());

      record->SSD().UpdatePtrs();
      record->GTR().UpdatePtrs();
      record->HBD().UpdatePtrs();
      record->LG().UpdatePtrs();

      //std::vector<E16DST_DST1StraightTrack2D> st_tracks;
      //E16DST_DST1WireTrackFactory2D(event0, &record->SSD(), &record->GTR(), st_tracks, gtrped, geom);

      std::vector<std::shared_ptr<E16DST_DST1StraightTrack3D>> st_tracks;
      E16DST_DST1WireTrackFactory3D(event0, &record->SSD(), &record->GTR(), st_tracks, gtrped, geom);
      record->SSD().UpdatePtrs();

      int ntracks = st_tracks.size();
      ntr = ntracks;
      for(int i=0;i<ntracks;i++){
	auto& st_track = st_tracks[i];
	module[i] = st_track->ModuleID();
	chi2x[i] = st_track->Chi2X();
	chi2y[i] = st_track->Chi2Y();
	tgtz[i] = st_track->TgtPosZ();
	tgty[i] = st_track->TgtPosY();
	distzx[i] = st_track->DistanceFromTgtXZ();
	distyr[i] = st_track->DistanceFromTgtYR();
	res0[i] = st_track->ResidualSSD();
	res1[i] = st_track->FitResidual100X();
	res2[i] = st_track->FitResidual200X();
	res3[i] = st_track->FitResidual300X();
	res1y[i] = st_track->FitResidual100Y();
	res2y[i] = st_track->FitResidual200Y();
	res3y[i] = st_track->FitResidual300Y();

	//extrapolation
	std::cout<<"TRACK MODULE "<<module[i]<<std::endl;
	TVector3 g100 = st_track->FitPtOnGTR100();
	TVector3 g200 = st_track->FitPtOnGTR200();
	TVector3 g300 = st_track->FitPtOnGTR300();
	std::cout<<"GTR100Output "<<g100.X()<<" "<<g100.Y()<<" "<<g100.Z()<<std::endl;
	std::cout<<"GTR200Output "<<g200.X()<<" "<<g200.Y()<<" "<<g200.Z()<<std::endl;
	std::cout<<"GTR300Output "<<g300.X()<<" "<<g300.Y()<<" "<<g300.Z()<<std::endl;
	TVector3 p1 = 5*(g300-g100)+g100;//for LG
	TVector3 p2 = (-1)*(g300-g100)+g100;// for SSD

	//Cross point at SSD plane
	int mid0 = ModuleID_2020to2013_33(module[i]);
	std::cout<<"GTR100Local "<<geom->GTR1(mid0)->GetLPos(g100).X()<<" "<<geom->GTR1(mid0)->GetLPos(g100).Y()<<std::endl;
	std::cout<<"GTR300Local "<<geom->GTR3(mid0)->GetLPos(g300).X()<<" "<<geom->GTR3(mid0)->GetLPos(g300).Y()<<std::endl;
	TVector3 clpos0;
	double lz;
	bool iscrossedssd = geom->SSD(mid0)->IsCrossed(p1, p2, clpos0, lz);
	if(iscrossedssd){
	  std::cout<<clpos0.X()<<" "<<clpos0.Z()<<std::endl;
	  ssdclx[i] = clpos0.X();
	}
	else{
	  std::cout<<"ERROR::: SSD extrapolation is failed"<<std::endl;
	  ssdclx[i] = -10000;
	}

	//residual at SSD plane
	auto& ssd_hits1 = record->SSD().HitPtrs(module[i],0,0);
	auto& ssd_clusters1 = record->SSD().ClusterPtrs(module[i],0,0);
	ssd_nhs[i] = ssd_hits1.size();
	ssd_ncs[i] = ssd_clusters1.size();
	if (ssd_clusters1.size() != 0) {
	  for(int ncs=0;ncs<ssd_ncs[i];ncs++){
	    auto& ssdcluster = ssd_clusters1[ncs];
	    std::cout<<"SSD COGPOS: "<<ssdcluster->CogPos()<<", CROSS PT: "<<ssdclx[i]<<std::endl;
	    hssdrx->Fill(ssdcluster->CogPos() - ssdclx[i]);
	    if(abs(ssdcluster->CogPos()-ssdclx[i])){

	    }
	  }
	}


	//Cross point at LG plane
	double ea = atan2(g300.Y(), g300.Mag());
	int block;
	if(ea<=dtor(15)&&ea>dtor(10)){
	  block = 50;
	}
	else if(ea<=dtor(10)&&ea>dtor(5)){
	  block = 40;
	}
	else if(ea<=dtor(5)&&ea>dtor(0)){
	  block = 30;
	}
	else if(ea<=dtor(0)&&ea>dtor(-5)){
	  block = 20;
	}
	else if(ea<=dtor(-5)&&ea>dtor(-10)){
	  block = 10;
	}
	else if(ea<=dtor(-10)&&ea>dtor(-15)){
	  block = 0;
	}
	else{
	  std::cout<<"ERROR::: out of acceptance****************"<<std::endl;
	  lgclx[i] = -10000;
	  lgcly[i] = -10000;
	  continue;
	}

	int mid[3] = {ModuleID_2020to2013_27(module[i]-1), ModuleID_2020to2013_27(module[i]), ModuleID_2020to2013_27(module[i]+1)};
	TVector3 clpos[3];
	TVector3 cgpos[3];
	cgpos[0].SetXYZ(10000,10000,10000);
	cgpos[1].SetXYZ(10000,10000,10000);
	cgpos[2].SetXYZ(10000,10000,10000);
	bool isclg1 = geom->LG(mid[1],block)->IsCrossed(p1, p2, clpos[1], lz);
	cgpos[1] = geom->LG(mid[1],block)->GetGPos(clpos[1]);
	int index = 1;
	bool isclg0 = geom->LG(mid[0],block)->IsCrossed(p1, p2, clpos[0], lz);
	cgpos[0] = geom->LG(mid[0],block)->GetGPos(clpos[0]);
	if(cgpos[0].Mag()<cgpos[index].Mag()){index = 0;}
	bool isclg2 = geom->LG(mid[2],block)->IsCrossed(p1, p2, clpos[2], lz);
	cgpos[2] = geom->LG(mid[2],block)->GetGPos(clpos[2]);
	if(cgpos[2].Mag()<cgpos[index].Mag()){index = 2;}

	if(isclg0||isclg1||isclg2){
	  lgclx[i] = clpos[index].X();
	  lgcly[i] = clpos[index].Y();
	  //std::cout<<"LGGlobal: "<<cgpos[index].X()<<" "<<cgpos[index].Y()<<" "<<cgpos[index].Z()<<" "<<cgpos[index].Mag()<<std::endl;
	}
	else{
	  std::cout<<"ERROR::: LG extrapolation is failed"<<std::endl;
	  lgclx[i] = -10000;
	  lgcly[i] = -10000;
	}

	int modulelg = ModuleID_2013to2020_27(mid[index]);
	std::cout<<"compare mod: "<<module[i]<<" "<<modulelg<<" "<<block<<std::endl;
	auto& lg_hits1 = record->LG().HitPtrs(modulelg,0,0);
	auto& lg_clusters1 = record->LG().ClusterPtrs(modulelg,0,0);
	lg_nhs[i] = lg_hits1.size();
	lg_ncs[i] = lg_clusters1.size();
	std::cout<<lg_nhs[i]<<" "<<lg_ncs[i]<<std::endl;
	if (lg_hits1.size() != 0) {
	  for(int nhs=0;nhs<lg_nhs[i];nhs++){//cluster loop
	    auto& lghit = lg_hits1[nhs];
	    std::cout<<"LG COGPOS: "<<lghit->LocalPos(*geom).X()<<", CROSS PT: "<<lgclx[i]<<std::endl;
	    hlgrx->Fill(lghit->LocalPos(*geom).X() - lgclx[i]);
	    hlgry->Fill(lghit->LocalPos(*geom).Y() - lgcly[i]);
	  }//cluster loop
	}//lg cluster bool

	std::cout<<"******************************"<<std::endl;

      }//ntracks

      tree->Fill();


//// Check begin
      //auto event_id = event0->EventID();
      //cout << "Event ID: " << event_id << endl;

      event = event0->EventID();

      /*
// SSD
      for(int j=0;j<8;j++){//module loop
	int mod = m_cid(j);
	auto& ssd_hits1 = record->SSD().HitPtrs(mod,0,0);
	auto& ssd_clusters1 = record->SSD().ClusterPtrs(mod,0,0);
	ssd_nh = ssd_hits1.size();
	ssd_nc = ssd_clusters1.size();
	//hnh[0][j]->Fill(ssd_nh);
	//hnc[0][j]->Fill(ssd_nc);
	if (ssd_clusters1.size() != 0) {
	  for(int i=0;i<ssd_nc;i++){//cluster loop
	    auto& ssdcluster = ssd_clusters1[i];
	    //hcs[0][j]->Fill(ssdcluster->NumHits());
	    //htd[0][j]->Fill(ssdcluster->Timing());
	    //had[0][j]->Fill(ssdcluster->PeakSum());
	    //hlx[0][j]->Fill(ssdcluster->CogPos());
	  }//cluster loop
	}//ssd cluster bool
      }//module loop

// GTR

      for(int j=0;j<8;j++){//module loop
	int mod = m_cid(j);
	for(int k=0;k<3;k++){//layer loop
	  for(int l=0;l<3;l++){//type loop
	    auto& gtr_hits1 = record->GTR().HitPtrs(mod,k,l);
	    auto& gtr_clusters1 = record->GTR().ClusterPtrs(mod,k,l);
	    gtr_nh = gtr_hits1.size();
	    gtr_nc = gtr_clusters1.size();
	    hnh[k+1][j]->Fill(gtr_nh);
	    hnc[k+1][j]->Fill(gtr_nc);
	    if (gtr_clusters1.size() != 0) {
	      for(int i=0;i<gtr_nc;i++){//cluster loop
		auto& gtrcluster = gtr_clusters1[i];
		hcs[k+1][j]->Fill(gtrcluster->NumHits());
		htd[k+1][j]->Fill(gtrcluster->Timing());
		had[k+1][j]->Fill(gtrcluster->PeakSum());
		if(l==0){hlx[k+1][j]->Fill(gtrcluster->CogPos());}
		else{hly[k+1][j]->Fill(gtrcluster->CogPos());}
	      }//cluster loop
	    }//gtr cluster bool
	  }//type loop
	}//layer loop
      }//module loop

// HBD

      for(int j=0;j<8;j++){//module loop
	int mod = m_cid(j);
	auto& hbd_hits1 = record->HBD().HitPtrs(mod,0,0);;
	auto& hbd_clusters1 = record->HBD().ClusterPtrs(mod,0,0);
	hbd_nh = hbd_hits1.size();
	hbd_nc = hbd_clusters1.size();
	hnh[4][j]->Fill(hbd_nh);
	hnc[4][j]->Fill(hbd_nc);
	if (hbd_clusters1.size() != 0) {
	  for(int i=0;i<hbd_nc;i++){//cluster loop
	    auto& hbdcluster = hbd_clusters1[i];
	    hcs[4][j]->Fill(hbdcluster->ClusterSize());
	    htd[4][j]->Fill(hbdcluster->Timing());
	    had[4][j]->Fill(hbdcluster->PeakSum());
	    hlx[4][j]->Fill(hbdcluster->LocalPos().X());
	    hly[4][j]->Fill(hbdcluster->LocalPos().Y());
	  }//cluster loop
	}//hbd cluster bool
      }//module loop

// LG

      for(int j=0;j<8;j++){//module loop
	int mod = m_cid(j);
	auto& lg_hits1 = record->LG().HitPtrs(mod,0,0);;
	auto& lg_clusters1 = record->LG().ClusterPtrs(mod,0,0);
	lg_nh = lg_hits1.size();
	lg_nc = lg_clusters1.size();
	//hnh[5][j]->Fill(lg_nh);
	//hnc[5][j]->Fill(lg_nc);
	if (lg_hits1.size() != 0) {
	  for(int i=0;i<lg_nh;i++){//cluster loop
	    auto& lghit = lg_hits1[i];
	    //hcs[5][j]->Fill(1);
	    //htd[5][j]->Fill(lghit->FitTiming());
	    //had[5][j]->Fill(lghit->FitPeak());
	    //hlx[5][j]->Fill(lghit->LocalPos(*geom).X());
	    //hly[5][j]->Fill(lghit->LocalPos(*geom).Y());
	  }//cluster loop
	}//lg cluster bool
      }//module loop
      */

      //tree->Fill();

//// trigger
//      event1->Trigger().Print(*geometry);
//
//// Check end

//      dst1->WriteAnEvent();
//      delete event0;
//      delete record;

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

  fout->Write();
  fout->Close();

  //  delete geometry;
  delete geom;
  delete dst0;
//  dst1->Close();
  return 0;
}
