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

  const int SMAX = 100;
  const int LMAX = 50;

  int ntr;
  int ssd_nhs;
  int ssd_ncs;
  int hbd_nhs;
  int hbd_ncs;
  int lg_nhs;
  int lg_ncs;
  //  int x_track_flag;

  int trkindex;
  int module;
  float chi2x;
  float chi2y;
  float tgtz;
  float tgty;
  float distzx;
  float distyr;
  float res0;
  float res1;
  float res2;
  float res3;
  float res1y;
  float res2y;
  float res3y;
  float gtr100x, gtr100y, gtr100z;
  float gtr200x, gtr200y, gtr200z;
  float gtr300x, gtr300y, gtr300z;

  bool ssdeff;
  double ssdcpt;
  double ssdres;
  int ssdcs;
  double ssdadc;
  double ssdtdc;
  double ssdhitres[SMAX];
  int ssdhitcs[SMAX];
  double ssdhitadc[SMAX];
  double ssdhittdc[SMAX];
  double ssdhitgx[SMAX];
  double ssdhitgy[SMAX];
  double ssdhitgz[SMAX];

  bool hbdeff;
  double hbdcptx;
  double hbdcpty;
  double hbdresx;
  double hbdresy;
  double hbdresxdam;
  double hbdresydam;
  int hbdcs;
  double hbdadc;
  double hbdtdc;
  double hbdhitresx[SMAX];
  double hbdhitresy[SMAX];
  int hbdhitcs[SMAX];
  double hbdhitadc[SMAX];
  double hbdhittdc[SMAX];
  double hbdhitgx[SMAX];
  double hbdhitgy[SMAX];
  double hbdhitgz[SMAX];

  bool lgeff;
  double angle;
  int modulelg;
  int block;
  int lgmod;
  int lgblk;
  double lgcptx;
  double lgcpty;
  double lgresx;
  double lgresy;
  double lgresxdam;
  double lgresydam;
  int lgcs;
  double lgadc;
  double lgtdc;
  double lggx;
  double lggy;
  double lggz;
  double lghitresx[LMAX];
  double lghitresy[LMAX];
  int lghitcs[LMAX];
  double lghitadc[LMAX];
  double lghittdc[LMAX];
  double lghitgx[LMAX];
  double lghitgy[LMAX];
  double lghitgz[LMAX];


  tree->Branch("ntr",&ntr,"ntr/I");
  tree->Branch("ssd_nhs",&ssd_nhs,"ssd_nhs/I");
  tree->Branch("ssd_ncs",&ssd_ncs,"ssd_ncs/I");
  tree->Branch("hbd_nhs",&hbd_nhs,"hbd_nhs/I");
  tree->Branch("hbd_ncs",&hbd_ncs,"hbd_ncs/I");
  tree->Branch("lg_nhs",&lg_nhs,"lg_nhs/I");
  tree->Branch("lg_ncs",&lg_ncs,"lg_ncs/I");
  //  tree->Branch("x_track_flag",&x_track_flag,"x_track_flag/I");

  tree->Branch("trkindex",&trkindex,"trkindex/I");
  tree->Branch("module",&module,"module/I");
  tree->Branch("chi2x",&chi2x,"chi2x/F");
  tree->Branch("chi2y",&chi2y,"chi2y/F");
  tree->Branch("tgtz",&tgtz,"tgtz/F");
  tree->Branch("tgty",&tgty,"tgty/F");
  tree->Branch("distzx",&distzx,"distzx/F");
  tree->Branch("distyr",&distyr,"distyr/F");
  tree->Branch("res0",&res0,"res0/F");
  tree->Branch("res1",&res1,"res1/F");
  tree->Branch("res2",&res2,"res2/F");
  tree->Branch("res3",&res3,"res3/F");
  tree->Branch("res1y",&res1y,"res1y/F");
  tree->Branch("res2y",&res2y,"res2y/F");
  tree->Branch("res3y",&res3y,"res3y/F");
  tree->Branch("gtr100x",&gtr100x,"gtr100x/F");
  tree->Branch("gtr100y",&gtr100y,"gtr100y/F");
  tree->Branch("gtr100z",&gtr100z,"gtr100z/F");
  tree->Branch("gtr200x",&gtr200x,"gtr200x/F");
  tree->Branch("gtr200y",&gtr200y,"gtr200y/F");
  tree->Branch("gtr200z",&gtr200z,"gtr200z/F");
  tree->Branch("gtr300x",&gtr300x,"gtr300x/F");
  tree->Branch("gtr300y",&gtr300y,"gtr300y/F");
  tree->Branch("gtr300z",&gtr300z,"gtr300z/F");

  tree->Branch("ssdeff",&ssdeff,"ssdeff/O");
  tree->Branch("ssdcpt",&ssdcpt,"ssdcpt/D");
  tree->Branch("ssdres",&ssdres,"ssdres/D");
  tree->Branch("ssdcs",&ssdcs,"ssdcs/I");
  tree->Branch("ssdadc",&ssdadc,"ssdadc/D");
  tree->Branch("ssdtdc",&ssdtdc,"ssdtdc/D");
  tree->Branch("ssdhitres",ssdhitres,"ssdhitres[ssd_ncs]/D");
  tree->Branch("ssdhitcs",ssdhitcs,"ssdhitcs[ssd_ncs]/I");
  tree->Branch("ssdhitadc",ssdhitadc,"ssdhitadc[ssd_ncs]/D");
  tree->Branch("ssdhittdc",ssdhittdc,"ssdhittdc[ssd_ncs]/D");
  tree->Branch("ssdhitgx",ssdhitgx,"ssdhitgx[ssd_ncs]/D");
  tree->Branch("ssdhitgy",ssdhitgy,"ssdhitgy[ssd_ncs]/D");
  tree->Branch("ssdhitgz",ssdhitgz,"ssdhitgz[ssd_ncs]/D");

  tree->Branch("hbdeff",&hbdeff,"hbdeff/O");
  tree->Branch("hbdcptx",&hbdcptx,"hbdcptx/D");
  tree->Branch("hbdcpty",&hbdcpty,"hbdcpty/D");
  tree->Branch("hbdresx",&hbdresx,"hbdresx/D");
  tree->Branch("hbdresy",&hbdresy,"hbdresy/D");
  tree->Branch("hbdresxdam",&hbdresxdam,"hbdresxdam/D");
  tree->Branch("hbdresydam",&hbdresydam,"hbdresydam/D");
  tree->Branch("hbdcs",&hbdcs,"hbdcs/I");
  tree->Branch("hbdadc",&hbdadc,"hbdadc/D");
  tree->Branch("hbdtdc",&hbdtdc,"hbdtdc/D");
  tree->Branch("hbdhitresx",hbdhitresx,"hbdhitresx[hbd_ncs]/D");
  tree->Branch("hbdhitresy",hbdhitresy,"hbdhitresy[hbd_ncs]/D");
  tree->Branch("hbdhitcs",hbdhitcs,"hbdhitcs[hbd_ncs]/I");
  tree->Branch("hbdhitadc",hbdhitadc,"hbdhitadc[hbd_ncs]/D");
  tree->Branch("hbdhittdc",hbdhittdc,"hbdhittdc[hbd_ncs]/D");
  tree->Branch("hbdhitgx",hbdhitgx,"hbdhitgx[hbd_ncs]/D");
  tree->Branch("hbdhitgy",hbdhitgy,"hbdhitgy[hbd_ncs]/D");
  tree->Branch("hbdhitgz",hbdhitgz,"hbdhitgz[hbd_ncs]/D");

  tree->Branch("lgeff",&lgeff,"lgeff/O");
  tree->Branch("angle",&angle,"angle/D");
  tree->Branch("modulelg",&modulelg,"modulelg/I");
  tree->Branch("block",&block,"block/I");
  tree->Branch("lgcptx",&lgcptx,"lgcptx/D");
  tree->Branch("lgcpty",&lgcpty,"lgcpty/D");
  tree->Branch("lgresx",&lgresx,"lgresx/D");
  tree->Branch("lgresy",&lgresy,"lgresy/D");
  tree->Branch("lgresxdam",&lgresxdam,"lgresxdam/D");
  tree->Branch("lgresydam",&lgresydam,"lgresydam/D");
  tree->Branch("lgadc",&lgadc,"lgadc/D");
  tree->Branch("lgtdc",&lgtdc,"lgtdc/D");
  tree->Branch("lgmod",&lgmod,"lgmod/I");
  tree->Branch("lgblk",&lgblk,"lgblk/I");
  tree->Branch("lggx",&lggx,"lggx/D");
  tree->Branch("lggy",&lggy,"lggy/D");
  tree->Branch("lggz",&lggz,"lggz/D");
  tree->Branch("lghitresx",lghitresx,"lghitresx[lg_nhs]/D");
  tree->Branch("lghitresy",lghitresy,"lghitresy[lg_nhs]/D");
  tree->Branch("lghitadc",lghitadc,"lghitadc[lg_nhs]/D");
  tree->Branch("lghittdc",lghittdc,"lghittdc[lg_nhs]/D");
  tree->Branch("lghitgx",lghitgx,"lghitgx[lg_nhs]/D");
  tree->Branch("lghitgy",lghitgy,"lghitgy[lg_nhs]/D");
  tree->Branch("lghitgz",lghitgz,"lghitgz[lg_nhs]/D");

  //TH2F* ssdxz = new TH2F("ssdxz","ssdxz",2000,-1000,1000,2000,-1000,1000);
  //TH2F* ssdzy = new TH2F("ssdzy","ssdzy",2000,-1000,1000,2000,-1000,1000);

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
  double hbdcptx_temp=0;
  double hbdcpty_temp=0;
  double lgcptx_temp=0;
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

      std::vector<std::shared_ptr<E16DST_DST1StraightTrack3D>> st_tracks;
      E16DST_DST1WireTrackFactory3D(event0, &record->SSD(), &record->GTR(), st_tracks, gtrped, geom);
      record->SSD().UpdatePtrs();


      //analysis
      int ntracks = st_tracks.size();
      ntr = ntracks;
      for(int i=0;i<ntracks;i++){
	ssd_nhs=-10000;
	ssd_ncs=-10000;
	hbd_nhs=-10000;
	hbd_ncs=-10000;
	lg_nhs=-10000;
	lg_ncs=-10000;
	//x_track_flag = -1;
	//if(i==x_track_id){x_track_flag=1;}
	trkindex=-10000;
	module=-10000;
	chi2x=-10000;
	chi2y=-10000;
	tgtz=-10000;
	tgty=-10000;
	distzx=-10000;
	distyr=-10000;
	res0=-10000;
	res1=-10000;
	res2=-10000;
	res3=-10000;
	res1y=-10000;
	res2y=-10000;
	res3y=-10000;
	gtr100x=-10000;
	gtr100y=-10000;
	gtr100z=-10000;
	gtr200x=-10000;
	gtr200y=-10000;
	gtr200z=-10000;
	gtr300x=-10000;
	gtr300y=-10000;
	gtr300z=-10000;
	ssdeff=false;
	ssdcpt=-10000;
	ssdres=-10000;
	ssdcs=-10000;
	ssdadc=-10000;
	ssdtdc=-10000;
	hbdeff=false;
	hbdcptx=-10000;
	hbdcpty=-10000;
	hbdresx=-10000;
	hbdresy=-10000;
	hbdresxdam=-10000;
	hbdcs=-10000;
	hbdadc=-10000;
	hbdtdc=-10000;
	angle=-10000;
	modulelg=-10000;
	block=-10000;
	lgeff=false;
	lgcptx=-10000;
	lgcpty=-10000;
	lgresx=-10000;
	lgresy=-10000;
	lgresxdam=-10000;
	lgresydam=-10000;
	lgadc=-10000;
	lgtdc=-10000;
	lggx = -10000;
	lggy = -10000;
	lggz = -10000;
	lgmod = -10000;
	lgblk = -10000;

	for(int k=0;k<SMAX;k++){
	  ssdhitres[k]=-10000;
	  ssdhitcs[k]=-10000;
	  ssdhitadc[k]=-10000;
	  ssdhittdc[k]=-10000;
	  ssdhitgx[k]=-10000;
	  ssdhitgy[k]=-10000;
	  ssdhitgz[k]=-10000;
	  hbdhitresx[k]=-10000;
	  hbdhitresy[k]=-10000;
	  hbdhitcs[k]=-10000;
	  hbdhitadc[k]=-10000;
	  hbdhittdc[k]=-10000;
	  hbdhitgx[k]=-10000;
	  hbdhitgy[k]=-10000;
	  hbdhitgz[k]=-10000;
	}
	for(int k=0;k<LMAX;k++){
	  lghitresx[k]=-10000;
	  lghitresy[k]=-10000;
	  lghitadc[k]=-10000;
	  lghittdc[k]=-10000;
	  lghitgx[k]=-10000;
	  lghitgy[k]=-10000;
	  lghitgz[k]=-10000;
	}

	trkindex = i;
	auto& st_track = st_tracks[i];
	module = st_track->ModuleID();
	chi2x = st_track->Chi2X();
	chi2y = st_track->Chi2Y();
	tgtz = st_track->TgtPosZ();
	tgty = st_track->TgtPosY();
	distzx = st_track->DistanceFromTgtXZ();
	distyr = st_track->DistanceFromTgtYR();
	res0 = st_track->ResidualSSD();
	res1 = st_track->FitResidual100X();
	res2 = st_track->FitResidual200X();
	res3 = st_track->FitResidual300X();
	res1y = st_track->FitResidual100Y();
	res2y = st_track->FitResidual200Y();
	res3y = st_track->FitResidual300Y();

	//extrapolation
	//std::cout<<"TRACK MODULE "<<module<<std::endl;
	TVector3 g100 = st_track->FitPtOnGTR100();
	TVector3 g200 = st_track->FitPtOnGTR200();
	TVector3 g300 = st_track->FitPtOnGTR300();
	gtr100x = g100.X();
	gtr100y = g100.Y();
	gtr100z = g100.Z();
	gtr200x = g200.X();
	gtr200y = g200.Y();
	gtr200z = g200.Z();
	gtr300x = g300.X();
	gtr300y = g300.Y();
	gtr300z = g300.Z();
	TVector3 p1 = 5*(g300-g100)+g100;//for LG
	TVector3 p2 = (-1)*(g300-g100)+g100;// for SSD

	//Cross point at SSD plane
	int mid0 = ModuleID_2020to2013_33(module);
	TVector3 l100 = geom->GTR1(mid0)->GetLPos(g100);
	TVector3 l200 = geom->GTR2(mid0)->GetLPos(g200);
	TVector3 l300 = geom->GTR3(mid0)->GetLPos(g300);
	//std::cout<<"GTR100Local  "<<l100.X()<<" "<<l100.Y()<<" "<<l100.Z()<<std::endl;
	//std::cout<<"GTR200Local  "<<l200.X()<<" "<<l200.Y()<<" "<<l200.Z()<<std::endl;
	//std::cout<<"GTR300Local  "<<l300.X()<<" "<<l300.Y()<<" "<<l300.Z()<<std::endl;
	TVector3 clpos0;
	double lz;
	bool iscrossedssd = geom->SSD(mid0)->IsCrossed(p1, p2, clpos0, lz);
	if(iscrossedssd){
	  ssdcpt = clpos0.X();
	}
	else{
	  std::cout<<"ERROR::: SSD extrapolation is failed"<<std::endl;
	  ssdcpt = -10000;
	}

	//residual at SSD plane
	auto& ssd_hits1 = record->SSD().HitPtrs(module,0,0);
	auto& ssd_clusters1 = record->SSD().ClusterPtrs(module,0,0);
	ssd_nhs = ssd_hits1.size();
	ssd_ncs = ssd_clusters1.size();
	if (ssd_clusters1.size() != 0) {
	  int nearindex = -10000;
	  double nearres = 10000;
	  for(int ncs=0;ncs<ssd_ncs;ncs++){
	    auto& ssdcluster = ssd_clusters1[ncs];
	    //std::cout<<"SSD COGPOS: "<<ssdcluster->CogPos()<<", CROSS PT: "<<ssdcpt<<std::endl;
	    double res = ssdcluster->CogPos() - ssdcpt;
	    ssdhitres[ncs] = res;
	    ssdhitcs[ncs] = ssdcluster->NumHits();
	    ssdhitadc[ncs] = ssdcluster->PeakSum();
	    ssdhittdc[ncs] = ssdcluster->Timing();
	    ssdhitgx[ncs] = ssdcluster->GlobalPos(*geom).X();
	    ssdhitgy[ncs] = ssdcluster->GlobalPos(*geom).Y();
	    ssdhitgz[ncs] = ssdcluster->GlobalPos(*geom).Z();
	    if(fabs(res)<fabs(nearres)){
	      nearindex = ncs;
	      nearres = res;
	    }
	  }
	  if(nearindex>=0){
	    ssdres = nearres;
	    ssdcs = ssdhitcs[nearindex];
	    ssdadc = ssdhitadc[nearindex];
	    ssdtdc = ssdhittdc[nearindex];
	    if(fabs(nearres)<5){
	      ssdeff = true;
	    }
	  }
	}

	//Cross point at HBD plane
	int mid4 = ModuleID_2020to2013_27(module);
	TVector3 clpos4;
	bool iscrossedhbd = geom->HBD(mid4)->IsCrossed(p1, p2, clpos0, lz);
	if(iscrossedhbd){
	  hbdcptx = clpos0.X();
	  hbdcpty = clpos0.Y();
	}
	else{
	  std::cout<<"ERROR::: HBD extrapolation is failed"<<std::endl;
	  hbdcptx = -10000;
	}

	//residual at HBD plane
	auto& hbd_hits1 = record->HBD().HitPtrs(module,0,0);
	auto& hbd_clusters1 = record->HBD().ClusterPtrs(module,0,0);
	hbd_nhs = hbd_hits1.size();
	hbd_ncs = hbd_clusters1.size();
	if (hbd_clusters1.size() != 0) {
	  int nearindex = -10000;
	  double nearresx = 10000;
	  double nearresy = 10000;
	  double nearresxdam = 10000;
	  double nearresydam = 10000;
	  for(int ncs=0;ncs<hbd_ncs;ncs++){
	    auto& hbdcluster = hbd_clusters1[ncs];
	    //std::cout<<"HBD COGPOS: "<<hbdcluster->LocalPos().X()<<", CROSS PT: "<<hbdcptx<<std::endl;
	    double resx = hbdcluster->LocalPos().X() - hbdcptx;
	    double resy = hbdcluster->LocalPos().Y() - hbdcpty;
	    double resxdam = hbdcluster->LocalPos().X() - hbdcptx_temp;
	    double resydam = hbdcluster->LocalPos().Y() - hbdcpty_temp;
	    //hbdcptx_temp = (-1)*hbdcptx;
	    //hbdcpty_temp = (-1)*hbdcpty;
	    hbdhitresx[ncs] = resx;
	    hbdhitresy[ncs] = resy;
	    hbdhitcs[ncs] = hbdcluster->ClusterSize();
	    hbdhitadc[ncs] = hbdcluster->PeakSum();
	    hbdhittdc[ncs] = hbdcluster->Timing();
	    hbdhitgx[ncs] = hbdcluster->GlobalPos(*geom).X();
	    hbdhitgy[ncs] = hbdcluster->GlobalPos(*geom).Y();
	    hbdhitgz[ncs] = hbdcluster->GlobalPos(*geom).Z();
	    double res = sqrt(resx*resx+resy*resy);
	    if( fabs(res) < fabs(sqrt(nearresx*nearresx+nearresy*nearresy)) ){
	      nearindex = ncs;
	      nearresx = resx;
	      nearresy = resy;
	    }
	    double resdam = sqrt(resxdam*resxdam+resydam*resydam);
	    if( fabs(res) < fabs(sqrt(nearresxdam*nearresxdam+nearresydam*nearresydam)) ){
	      nearresxdam = resxdam;
	      nearresydam = resydam;
	    }
	  }
	  if(nearindex>=0){
	    hbdresx = nearresx;
	    hbdresy = nearresy;
	    hbdresxdam = nearresxdam;
	    hbdresydam = nearresydam;
	    hbdcs = hbdhitcs[nearindex];
	    hbdadc = hbdhitadc[nearindex];
	    hbdtdc = hbdhittdc[nearindex];
	    if(sqrt(nearresx*nearresx+nearresy*nearresy)<10){
	      hbdeff = true;
	    }
	  }
	}

	//Cross point at LG plane
	double ea = atan2(g300.Y(), g300.Mag());
	angle = rtod(ea);
	//int block;
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
	  lgcptx = -30000;
	  lgcpty = -30000;
	  continue;
	}

	int mid[3] = {ModuleID_2020to2013_27(module-1), ModuleID_2020to2013_27(module), ModuleID_2020to2013_27(module+1)};
	TVector3 clpostemp[3];
	TVector3 cgpos[3];
	cgpos[0].SetXYZ(10000,10000,10000);
	cgpos[1].SetXYZ(10000,10000,10000);
	cgpos[2].SetXYZ(10000,10000,10000);
	TVector3 clpos[3];
	bool isclg1 = geom->LG(mid[1],block)->IsCrossed(p1, p2, clpostemp[1], lz);
	//std::cout<<"LG CROSS LOCALT POS: "<<clpostemp[1].X()<<" "<<clpostemp[1].Y()<<" "<<clpostemp[1].Z()<<std::endl;
	cgpos[1] = geom->LG(mid[1],block)->GetGPos(clpostemp[1]);
	//std::cout<<"LG CROSS GLOBAL POS: "<<cgpos[1].X()<<" "<<cgpos[1].Y()<<" "<<cgpos[1].Z()<<std::endl;
	clpos[1] = geom->LGVD(mid[1])->GetLPos(cgpos[1]);
	//std::cout<<"LG CROSS LOCAL  POS: "<<clpos[1].X()<<" "<<clpos[1].Y()<<" "<<clpos[1].Z()<<std::endl;
	int index = 1;
	bool isclg0 = geom->LG(mid[0],block)->IsCrossed(p1, p2, clpostemp[0], lz);
	cgpos[0] = geom->LG(mid[0],block)->GetGPos(clpostemp[0]);
	clpos[0] = geom->LGVD(mid[0])->GetLPos(cgpos[0]);
	if(isclg0&&cgpos[0].Mag()<cgpos[index].Mag()){index = 0;}
	bool isclg2 = geom->LG(mid[2],block)->IsCrossed(p1, p2, clpostemp[2], lz);
	cgpos[2] = geom->LG(mid[2],block)->GetGPos(clpostemp[2]);
	clpos[2] = geom->LGVD(mid[2])->GetLPos(cgpos[2]);
	if(isclg2&&cgpos[2].Mag()<cgpos[index].Mag()){index = 2;}

	if(isclg0||isclg1||isclg2){
	  lgcptx = clpos[index].X();
	  lgcpty = clpos[index].Y();
	  //std::cout<<"LG LOCAL: "<<clpos[index].X()<<" "<<clpos[index].Y()<<" "<<clpos[index].Z()<<std::endl;
	  //std::cout<<"LGGlobal: "<<cgpos[index].X()<<" "<<cgpos[index].Y()<<" "<<cgpos[index].Z()<<" "<<cgpos[index].Mag()<<std::endl;
	}
	else{
	  std::cout<<"ERROR::: LG extrapolation is failed"<<std::endl;
	  lgcptx = -20000;
	  lgcpty = -20000;
	}

	//residual at LG plane
	modulelg = ModuleID_2013to2020_27(mid[index]);
	std::cout<<"compare mod: "<<module<<" "<<modulelg<<" "<<block<<std::endl;
	auto& lg_hits1 = record->LG().HitPtrs(modulelg,0,0);
	auto& lg_clusters1 = record->LG().ClusterPtrs(modulelg,0,0);
	lg_nhs = lg_hits1.size();
	lg_ncs = lg_clusters1.size();
	//std::cout<<lg_nhs<<" "<<lg_ncs<<std::endl;
	if (lg_hits1.size() != 0) {
	  int nearindex = -10000;
	  double nearresx = 10000;
	  double nearresy = 10000;
	  double nearresxdam = 10000;
	  for(int nhs=0;nhs<lg_nhs;nhs++){//cluster loop
	    auto& lghit = lg_hits1[nhs];
	    double resx = lghit->LocalPos(*geom).X() - lgcptx;
	    double resy = lghit->LocalPos(*geom).Y() - lgcpty;
	    double resxdam = lghit->LocalPos(*geom).X() - lgcptx_temp;
	    //lgcptx_temp = lgcptx;
	    //std::cout<<"LGCheck:"<<lghit->ModuleId()<<" "<<lghit->ChannelId()<<" "<<lghit->LocalPos(*geom).X()<<" "<<lghit->LocalPos(*geom).Y()<<std::endl;
	    lghitresx[nhs] = resx;
	    lghitresy[nhs] = resy;
	    lghitadc[nhs] = lghit->FitPeak();
	    lghittdc[nhs] = lghit->GetCalibTiming(lgbasic, lghit->FitTiming());
	    lghitgx[nhs] = lghit->GlobalPos(*geom).X();
	    lghitgy[nhs] = lghit->GlobalPos(*geom).Y();
	    lghitgz[nhs] = lghit->GlobalPos(*geom).Z();

	    int lglocaly = lghit->ChannelId()/10;
	    if(lglocaly*10==block){
	      //std::cout<<"LG COGPOS: "<<lghit->LocalPos(*geom).X()<<", CROSS PT: "<<lgcptx<<std::endl;
	      if(fabs(resx)<fabs(nearresx)){
		nearindex = nhs;
		nearresx = resx;
		nearresy = resy;
	      }
	      if(fabs(resxdam)<fabs(nearresxdam)){
		nearresxdam = resxdam;
	      }
	      if(fabs(nearresx)<65){
		lgeff = true;
	      }
	    }
	  }//cluster loop
	  if(nearindex>=0){
	    lgresx = nearresx;
	    lgresy = nearresy;
	    lgresxdam = nearresxdam;
	    lgadc = lghitadc[nearindex];
	    lgtdc = lghittdc[nearindex];
	    lggx = lghitgx[nearindex];
	    lggy = lghitgy[nearindex];
	    lggz = lghitgz[nearindex];
	    lgmod = lg_hits1[nearindex]->ModuleId();
	    lgblk = lg_hits1[nearindex]->ChannelId();
	  }
	}//lg cluster bool

	//std::cout<<lgcptx<<" "<<lgcpty<<std::endl;
	std::cout<<"******************************"<<std::endl;


      tree->Fill();


      }//ntracks

      hbdcptx_temp = hbdcptx;
      hbdcpty_temp = hbdcpty;
      lgcptx_temp = lgcptx;


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
