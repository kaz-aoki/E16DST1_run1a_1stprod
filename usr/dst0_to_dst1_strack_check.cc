#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
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

  int ssd_nh;
  int ssd_nc;
  int ssd_m[CMAX];
  int ssd_cs[CMAX];
  float ssd_tdc[CMAX];
  float ssd_adc[CMAX];
  float ssd_lx[CMAX];
  //  float ssd_res[CMAX*2];
  int gtr_nh, gtr_nc;
  int g100_nh;
  int g100_nc;
  int g100_m[CMAX];
  int g100_cs[CMAX];
  float g100_tdc[CMAX];
  float g100_adc[CMAX];
  float g100_lx[CMAX];
  float g100_ly[CMAX];
  int g200_nh;
  int g200_nc;
  int g200_m[CMAX];
  int g200_cs[CMAX];
  float g200_tdc[CMAX];
  float g200_adc[CMAX];
  float g200_lx[CMAX];
  float g200_ly[CMAX];
  int g300_nh;
  int g300_nc;
  int g300_m[CMAX];
  int g300_cs[CMAX];
  float g300_tdc[CMAX];
  float g300_adc[CMAX];
  float g300_lx[CMAX];
  float g300_ly[CMAX];
  int hbd_nh;
  int hbd_nc;
  int hbd_m[CMAX];
  int hbd_cs[CMAX];
  float hbd_tdc[CMAX];
  float hbd_adc[CMAX];
  float hbd_lx[CMAX];
  float hbd_ly[CMAX];
  int lg_nh;
  int lg_nc;
  int lg_m[HMAX];
  int lg_cs[HMAX];
  float lg_tdc[HMAX];
  float lg_adc[HMAX];
  float lg_lx[HMAX];
  float lg_ly[HMAX];
  //  float lg_res[CMAX*2];

  /*
  tree->Branch("Event",&event,"Event/I");
  tree->Branch("ssd_nh",&ssd_nh,"ssd_nh/I");
  tree->Branch("ssd_nc",&ssd_nc,"ssd_nc/I");
  tree->Branch("ssd_m",ssd_m,"ssd_m[ssd_nc]/I");
  tree->Branch("ssd_cs",ssd_cs,"ssd_cs[ssd_nc]/I");
  tree->Branch("ssd_tdc",ssd_tdc,"ssd_tdc[ssd_nc]/F");
  tree->Branch("ssd_adc",ssd_adc,"ssd_adc[ssd_nc]/F");
  tree->Branch("ssd_lx",ssd_lx,"ssd_lx[ssd_nc]/F");
  tree->Branch("gtr_nh",&gtr_nh,"gtr_nh/I");
  tree->Branch("gtr_nc",&gtr_nc,"gtr_nc/I");
  tree->Branch("g100_nh",&g100_nh,"g100_nh/I");
  tree->Branch("g100_nc",&g100_nc,"g100_nc/I");
  tree->Branch("g100_m",g100_m,"g100_m[g100_nc]/I");
  tree->Branch("g100_cs",g100_cs,"g100_cs[g100_nc]/I");
  tree->Branch("g100_tdc",g100_tdc,"g100_tdc[g100_nc]/F");
  tree->Branch("g100_adc",g100_adc,"g100_adc[g100_nc]/F");
  tree->Branch("g100_lx",g100_lx,"g100_lx[g100_nc]/F");
  tree->Branch("g100_ly",g100_ly,"g100_ly[g100_nc]/F");
  tree->Branch("g200_nh",&g200_nh,"g200_nh/I");
  tree->Branch("g200_nc",&g200_nc,"g200_nc/I");
  tree->Branch("g200_m",g200_m,"g200_m[g200_nc]/I");
  tree->Branch("g200_cs",g200_cs,"g200_cs[g200_nc]/I");
  tree->Branch("g200_tdc",g200_tdc,"g200_tdc[g200_nc]/F");
  tree->Branch("g200_adc",g200_adc,"g200_adc[g200_nc]/F");
  tree->Branch("g200_lx",g200_lx,"g200_lx[g200_nc]/F");
  tree->Branch("g200_ly",g200_ly,"g200_ly[g200_nc]/F");
  tree->Branch("g300_nh",&g300_nh,"g300_nh/I");
  tree->Branch("g300_nc",&g300_nc,"g300_nc/I");
  tree->Branch("g300_m",g300_m,"g300_m[g300_nc]/I");
  tree->Branch("g300_cs",g300_cs,"g300_cs[g300_nc]/I");
  tree->Branch("g300_tdc",g300_tdc,"g300_tdc[g300_nc]/F");
  tree->Branch("g300_adc",g300_adc,"g300_adc[g300_nc]/F");
  tree->Branch("g300_lx",g300_lx,"g300_lx[g300_nc]/F");
  tree->Branch("g300_ly",g300_ly,"g300_ly[g300_nc]/F");
  tree->Branch("hbd_nh",&hbd_nh,"hbd_nh/I");
  tree->Branch("hbd_nc",&hbd_nc,"hbd_nc/I");
  tree->Branch("hbd_m",hbd_m,"hbd_m[hbd_nc]/I");
  tree->Branch("hbd_cs",hbd_cs,"hbd_cs[hbd_nc]/I");
  tree->Branch("hbd_tdc",hbd_tdc,"hbd_tdc[hbd_nc]/F");
  tree->Branch("hbd_adc",hbd_adc,"hbd_adc[hbd_nc]/F");
  tree->Branch("hbd_lx",hbd_lx,"hbd_lx[hbd_nc]/F");
  tree->Branch("hbd_ly",hbd_ly,"hbd_ly[hbd_nc]/F");
  tree->Branch("lg_nh",&lg_nh,"lg_nh/I");
  tree->Branch("lg_nc",&lg_nc,"lg_nc/I");
  tree->Branch("lg_m",lg_m,"lg_m[lg_nh]/I");
  tree->Branch("lg_cs",lg_cs,"lg_cs[lg_nh]/I");
  tree->Branch("lg_tdc",lg_tdc,"lg_tdc[lg_nh]/F");
  tree->Branch("lg_adc",lg_adc,"lg_adc[lg_nh]/F");
  tree->Branch("lg_lx",lg_lx,"lg_lx[lg_nh]/F");
  tree->Branch("lg_ly",lg_ly,"lg_ly[lg_nh]/F");
  */
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

      std::vector<E16DST_DST1StraightTrack2D> st_tracks;
//      E16DST_DST1WireTrackFactory2D(event0, &record->SSD(), &record->GTR(), st_tracks, gtrped, geom);


      int ntracks = st_tracks.size();
      //std::cout<<"N_STRAIGHT_TRACK: "<<ntracks<<std::endl;
      int no = 0;
      int index[5] = {-1000,-1000,-1000,-1000,-1000};
      float ssdr[5] = {1000,1000,1000,1000,1000};
      float chi2_before;
      for(int i=0;i<ntracks;i++){
	//E16DST_DST1StraightTrack2D& st_track = st_tracks[i];
	auto& st_track = st_tracks[i];
	float chi2_temp = st_track.Chi2();
	float ssdr_temp = st_track.SSDResidualExSelf();
	if(i!=0&&fabs(chi2_temp-chi2_before)>0.01){
	  no++;
	  index[no] = i;
	  ssdr[no] = fabs(ssdr_temp);
	}
	if(fabs(ssdr_temp)<ssdr[no]){
	  index[no] = i;
	  ssdr[no] = fabs(ssdr_temp);
	}
	chi2_before = chi2_temp;
      }


      double crosslgx[2];
      double crossssdx[2];
      //if(ntracks!=0){
      if(ntracks!=0&&index[0]>=0&&index[0]<ntracks&&index[1]>=0&&index[1]<ntracks){
      int module[2] = {st_tracks[index[0]].ModuleID(), st_tracks[index[1]].ModuleID()};
      float chi2[2] = {st_tracks[index[0]].Chi2(), st_tracks[index[1]].Chi2()};
      float tgtz[2] = {st_tracks[index[0]].TgtZ(), st_tracks[index[1]].TgtZ()};
      float dist[2] = {st_tracks[index[0]].Distance(), st_tracks[index[1]].Distance()};
      float ssdres[2] = {st_tracks[index[0]].SSDResidualExSelf(), st_tracks[index[1]].SSDResidualExSelf()};
      TVector2 pt100[2] = {st_tracks[index[0]].PtOnTrackGTR100(), st_tracks[index[1]].PtOnTrackGTR100()};
      TVector2 pt300[2] = {st_tracks[index[0]].PtOnTrackGTR300(), st_tracks[index[1]].PtOnTrackGTR300()};
      TVector2 pt3000[2] = {st_tracks[index[0]].PtOnTrack3000mm(), st_tracks[index[1]].PtOnTrack3000mm()};
      //std::cout<<"Check:::: "<<st_tracks[index[0]].ModuleID()<<" "<<st_tracks[index[1]].ModuleID()<<std::endl;

      Int_t mid;
      TVector3 gpos0;
      TVector3 gpos1;
      TVector3 cpos;
      double lz;
      bool iscrossed;

      mid = ModuleID_2020to2013_27(module[0]);
      gpos0 = {st_tracks[index[0]].PtOnTrackGTR100().X(), 0, st_tracks[index[0]].PtOnTrackGTR100().Y()};
      gpos1 = {st_tracks[index[0]].PtOnTrack3000mm().X(), 0, st_tracks[index[0]].PtOnTrack3000mm().Y()};
      iscrossed = geom->LGVD(mid)->IsCrossed(gpos0, gpos1, cpos, lz);
      crosslgx[0] = cpos.X();

      mid = ModuleID_2020to2013_27(module[1]);
      gpos0 = {st_tracks[index[1]].PtOnTrackGTR100().X(), 0, st_tracks[index[1]].PtOnTrackGTR100().Y()};
      gpos1 = {st_tracks[index[1]].PtOnTrack3000mm().X(), 0, st_tracks[index[1]].PtOnTrack3000mm().Y()};
      iscrossed = geom->LGVD(mid)->IsCrossed(gpos0, gpos1, cpos, lz);
      crosslgx[1] = cpos.X();

      //std::cout<<crosslgx[0]<<" "<<crosslgx[1]<<std::endl;

      for(int i=0;i<2;i++){
	mid = ModuleID_2020to2013_33(module[i]);
	//std::cout<<"mid: "<<module[i]<<std::endl;
	TVector3 origin;
	TRotation rotation;
	origin =  geom->SSD(mid)->GetGPos(TVector3(0.,0.,0.));
	rotation = geom->SSD(mid)->GetRotation();
	TVector3 normal;
	normal.SetXYZ(0.,0.,1.);
	normal = rotation*normal;
	double p1[3] = {st_tracks[index[i]].PtOnTrackGTR100().X(), 0, st_tracks[index[i]].PtOnTrackGTR100().Y()};
	double p2[3] = {st_tracks[index[i]].PtOnTrack3000mm().X(), 0, st_tracks[index[i]].PtOnTrack3000mm().Y()};
	double p0[3] = {origin.X(), origin.Y(), origin.Z()};
	double pn[3] = {normal.X(), normal.Y(), normal.Z()};
	double t = (pn[0]*(p0[0]-p1[0]) + pn[2]*(p0[2]-p1[2])) / (pn[0]*(p2[0]-p1[0]) + pn[2]*(p2[2]-p1[2]));
	double x = (p2[0]-p1[0])*t + p1[0];
	double z = (p2[2]-p1[2])*t + p1[2];
	//std::cout<<"mycalc: "<<x<<" "<<z<<std::endl;
	TVector3 gcp = {x,0,z};
	TVector3 lcp = geom->SSD(mid)->GetLPos(gcp);
	//std::cout<<lcp.X()<<" "<<lcp.Y()<<" "<<lcp.Z()<<std::endl;
	crossssdx[i] = lcp.X();
	hres[c_mid(module[i])]->Fill(st_tracks[index[i]].SSDResidualExSelf());
	htgz[c_mid(module[i])]->Fill(st_tracks[index[i]].TgtZ());
	hch2[c_mid(module[i])]->Fill(st_tracks[index[i]].Chi2());
      }

      //std::cout<<crossssdx[0]<<" "<<crossssdx[1]<<std::endl;

      }//ntracks



//// Check begin
      //auto event_id = event0->EventID();
      //cout << "Event ID: " << event_id << endl;

      event = event0->EventID();

// SSD
      for(int j=0;j<8;j++){//module loop
	int mod = m_cid(j);
	auto& ssd_hits1 = record->SSD().HitPtrs(mod,0,0);
	auto& ssd_clusters1 = record->SSD().ClusterPtrs(mod,0,0);
	ssd_nh = ssd_hits1.size();
	ssd_nc = ssd_clusters1.size();
	hnh[0][j]->Fill(ssd_nh);
	hnc[0][j]->Fill(ssd_nc);
	if (ssd_clusters1.size() != 0) {
	  for(int i=0;i<ssd_nc;i++){//cluster loop
	    auto& ssdcluster = ssd_clusters1[i];
	    hcs[0][j]->Fill(ssdcluster->NumHits());
	    htd[0][j]->Fill(ssdcluster->Timing());
	    had[0][j]->Fill(ssdcluster->PeakSum());
	    hlx[0][j]->Fill(ssdcluster->CogPos());
	    if(ntracks!=0&&index[0]>=0&&index[0]<ntracks&&index[1]>=0&&index[1]<ntracks){
	      for(int k=0;k<2;k++){
		hre[0][j]->Fill(ssdcluster->CogPos() - crossssdx[k]);
	      }
	    }
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
	hnh[5][j]->Fill(lg_nh);
	hnc[5][j]->Fill(lg_nc);
	if (lg_hits1.size() != 0) {
	  for(int i=0;i<lg_nh;i++){//cluster loop
	    auto& lghit = lg_hits1[i];
	    hcs[5][j]->Fill(1);
	    htd[5][j]->Fill(lghit->FitTiming());
	    had[5][j]->Fill(lghit->FitPeak());
	    hlx[5][j]->Fill(lghit->LocalPos(*geom).X());
	    hly[5][j]->Fill(lghit->LocalPos(*geom).Y());
	    //hlx[5][j]->Fill(lghit->LocalPos(*geometry).X());
	    //hly[5][j]->Fill(lghit->LocalPos(*geometry).Y());
	    if(ntracks!=0&&index[0]>=0&&index[0]<ntracks&&index[1]>=0&&index[1]<ntracks){
	      for(int k=0;k<2;k++){
		hre[5][j]->Fill(lghit->LocalPos(*geom).X() - crosslgx[k]);
	      }
	    }
	  }//cluster loop
	}//lg cluster bool
      }//module loop


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
