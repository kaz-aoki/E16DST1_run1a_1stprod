#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
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

  // TH1F *hnh[7];
  // TH1F *hph[7][56];
  // TH1F *hpt[7][56];
  // TH1F *htm[7][56];
  // TH1F *hbl[7][56];
  // TH1F *hbr[7][56];
  // TH1F *hit[7][56];
  // TH1F *ht0[7][56];
  // TH1F *hed[7][56];
  // TH1F *hnp[7][56];
  // TH1F *hff[7][56];
  // TH1F *hfp[7][56];
  // TH1F *hfx[7][56];
  // TH1F *hft[7][56];
  // TH1F *hfw[7][56];
  // TH1F *hfc[7][56];
  // TH1F *hctd = new TH1F("hctd","hclusterTimeDiff",400,0,40);
  // TH1F *hcmp = new TH1F("hcmp","hclusterMaxPeak",1100,-100,1000);
  // TH1F *hctm = new TH1F("hctm","hclusterTiming",200,0,200);
  // TH1F *hcps = new TH1F("hcps","hclusterPeakSum",1100,-100,1000);
  // TH1F *hcgx = new TH1F("hcgx","hclusterGlobalX",4000,-2000,2000);
  // TH1F *hcgy = new TH1F("hcgy","hclusterGlobalY",4000,-2000,2000);
  // TH1F *hcgz = new TH1F("hcgz","hclusterGlobalZ",4000,-2000,2000);
  // TH2F *hcgyx = new TH2F("hcgyx","hclusterGlobalYX",4000,-2000,2000,4000,-2000,2000);
  // TH2F *hcgzx = new TH2F("hcgzx","hclusterGlobalZX",4000,-2000,2000,4000,-2000,2000);
  // for(int i=0;i<7;i++){
  //   hnh[i] = new TH1F(Form("hnh%d",i),Form("NHit%d",i),300,0,300);
  //   for(int j=0;j<56;j++){
  //     hph[i][j] = new TH1F(Form("hph%d%d",i,j),Form("PeakHeight%d%d",i,j),1100,-100,1000);
  //     hpt[i][j] = new TH1F(Form("hpt%d%d",i,j),Form("PeakTime%d%d",i,j),200,0,200);
  //     htm[i][j] = new TH1F(Form("htm%d%d",i,j),Form("Timing%d%d",i,j),200,0,200);
  //     hbl[i][j] = new TH1F(Form("hbl%d%d",i,j),Form("Baseline%d%d",i,j),200,-100,100);
  //     hbr[i][j] = new TH1F(Form("hbr%d%d",i,j),Form("BaselineRms%d%d",i,j),200,-100,100);
  //     hit[i][j] = new TH1F(Form("hit%d%d",i,j),Form("Integral%d%d",i,j),1100,-100,1000);
  //     ht0[i][j] = new TH1F(Form("ht0%d%d",i,j),Form("CalibTiming%d%d",i,j),1000,0,200);
  //     hed[i][j] = new TH1F(Form("hed%d%d",i,j),Form("EnergyDeposit%d%d",i,j),1100,-1,10);
  //     hnp[i][j] = new TH1F(Form("hnp%d%d",i,j),Form("Npeaks%d%d",i,j),5,0,5);
  //     hff[i][j] = new TH1F(Form("hff%d%d",i,j),Form("FitFlag%d%d",i,j),5,0,5);
  //     hfp[i][j] = new TH1F(Form("hfp%d%d",i,j),Form("FitPeak%d%d",i,j),1100,-100,1000);
  //     hfx[i][j] = new TH1F(Form("hfx%d%d",i,j),Form("FitPeakTime%d%d",i,j),200,0,200);
  //     hft[i][j] = new TH1F(Form("hft%d%d",i,j),Form("FitTiming%d%d",i,j),200,0,200);
  //     hfw[i][j] = new TH1F(Form("hfw%d%d",i,j),Form("FitWidth%d%d",i,j),200,0,2);
  //     hfc[i][j] = new TH1F(Form("hfc%d%d",i,j),Form("FitChi2%d%d",i,j),200,0,50);
  //   }
  // }
  uint16_t module, block;
  int run, event, n_trg_lg_hits, sr, sl;
  vector<float>  sradc;
  vector<float>  srtdc;
  vector<int>     srnpeaks;
  vector<int>     srfitflag;
  vector<float>  sladc;
  vector<float>  sltdc;
  vector<int>     slnpeaks;
  vector<int>     slfitflag;
  vector<int>     trg_lg_hit_id;
  vector<int>     trg_lg_hit_mid;
  vector<int>     trg_lg_hit_cid;
  vector<float>     trg_lg_hit_t;

  tree->Branch("Run",&run,"Run/I");
  tree->Branch("Event",&event,"Event/I");

  tree->Branch("SR",&sr,"SR/I");
  tree->Branch("SL",&sl,"SL/I");
  tree->Branch("SRadc",&sradc);
  tree->Branch("SRtdc",&srtdc);
  tree->Branch("SRnpeaks",&srnpeaks);
  tree->Branch("SRfitflag",&srfitflag);
  tree->Branch("SLadc",&sladc);
  tree->Branch("SLtdc",&sltdc);
  tree->Branch("SLnpeaks",&slnpeaks);
  tree->Branch("SLfitflag",&slfitflag);

  tree->Branch("n_trg_lg_hits",&n_trg_lg_hits,"n_trg_lg_hits/I");
  tree->Branch("trg_lg_hit_id",&trg_lg_hit_id);
  tree->Branch("trg_lg_hit_mid",&trg_lg_hit_mid);
  tree->Branch("trg_lg_hit_cid",&trg_lg_hit_cid);
  tree->Branch("trg_lg_hit_t",&trg_lg_hit_t);

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  // auto trigger_param = new E16ANA_TriggerCalibParam();
  // trigger_param->ReadConstantData(calib.CurrentRunID());
  E16ANA_TriggerCalibParam trigger_param;
  trigger_param.ReadConstantData(calib.CurrentRunID());
  E16ANA_GTRcalibPedestal gtrped;
  gtrped.ReadCalibData( calib.CurrentRunID() );
  E16ANA_LGBasic lgbasic;
  lgbasic.SetMap();
  lgbasic.SetCalibMap();//it is necessary to use energy deposit and calibrated timing.

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  
  // auto record = new E16DST_DST1PhysicsRecord();
  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }
  E16DST_DST1PhysicsRecord record;

//  E16ANA_GTRPedestal *gtr_pedestal = new E16ANA_GTRPedestal();
//  gtr_pedestal->Read(argv[5]);
//  auto dst1 = new E16DST_DST1();
//  auto dst1 = new E16DST_DST0();
//  if (!dst1->Open(out_file_name, E16DST_DST0::WriteMode)) {
//    std::cerr << "Cannot open output file: " << out_file_name << std::endl;
//    return -1;
//   }

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
      auto& trigger_gtr_hits0 = event0->TriggerGTR();
      auto& trigger_hbd_hits0 = event0->TriggerHBD();
      auto& trigger_lg_hits0  = event0->TriggerLG();
      auto event_id = event0->EventID();

      E16DST_DST1LGFactory(lg_hits0, &record.LG(), 1, geometry); // w/ fit
      record.LG().AddHitAndClusterIds();
      record.LG().UpdatePtrs();
      E16DST_DST1TriggerFactory(trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record.Trigger());
      record.Trigger().AddHitAndClusterIDs();
      record.Trigger().UpdatePtrs();
//      E16DST_DST0Detector<E16DST_DST1LGHit> lg_hits1;
//      E16DST_DST0Detector<E16DST_DST1LGCluster> lg_clusters1;
//      auto& lg_hits1 = record->LG().Hits();
//      auto& lg_clusters1 = record->LG().Clusters();
//      E16DST_DST1SSDFactory(ssd_hits0, &event1->SSDHits(), &event1->SSDClusters());
//      std::cout << "GTR factory returns :: " << E16DST_DST1GTRHitAndClusterFactory(gtr_hits0, &event1->GTRHits(), &event1->GTRClusters(), gtrped) << std::endl;
//      E16DST_DST1GTRFactoryDST1Detector(gtr_hits0, &event1->GTR());
//      E16DST_DST1HBDFactory(hbd_hits0, &event1->HBDHits(), &event1->HBDClusters());
//      E16DST_DST1LGHitAndClusterFactory(lg_hits0,   lg_hits1,  lg_clusters1);
//      E16DST_DST1LGFactory(lg_hits0, &record->LG(), 1, geometry);
//      E16DST_DST1LGFactoryDST1Detector(lg_hits0, &event1->LG());
//      E16DST_DST1TriggerFactory(*trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &event1->Trigger());
//      event1->GTR().SetValidFlag(1);
//      event1->LG().SetValidFlag(1);
//      event1->Trigger().SetValidFlag(1);


//// Check begin
//// LG

      run = run_id;
      event = event0->EventID();
      sr = 0;
      sl = 0;
      sradc.clear();
      srtdc.clear();
      srnpeaks.clear();
      srfitflag.clear();
      sladc.clear();
      sltdc.clear();
      slnpeaks.clear();
      slfitflag.clear();
      trg_lg_hit_id.clear();
      trg_lg_hit_mid.clear();
      trg_lg_hit_cid.clear();
      trg_lg_hit_t.clear();

      int nall_trg_lg_hits = record.Trigger().NumLGHits();
      int nacc = 0;
      for(int itrg=0;itrg<nall_trg_lg_hits;itrg++){
	auto& hit = record.Trigger().LGHit(itrg);
	if(hit.Timing()>300||hit.Timing()<-900) continue;
	trg_lg_hit_id.push_back(itrg);
	trg_lg_hit_mid.push_back(hit.ModuleId());
	trg_lg_hit_cid.push_back(hit.ChannelId());
	trg_lg_hit_t.push_back(hit.Timing());
	nacc++;
      }
      n_trg_lg_hits = nacc;

      int srflag = event0->UT3().NIMFlag(1);
      int slflag = event0->UT3().NIMFlag(0);
      if(srflag!=0||slflag!=0){
      sr = srflag;
      sl = slflag;

      auto& lg_hits1 = record.LG().Hits();
      int n_lghits = lg_hits1.size();
      if (lg_hits1.size() != 0) {// exist hit
	for(int i=0;i<n_lghits;i++){//hit loop
	  auto& lghit = lg_hits1[i];
	  module = lghit.ModuleId();
	  block = lghit.ChannelId();
	  if( module==104&&block==5 ){
	    sradc.push_back(lghit.FitPeak());
	    srtdc.push_back(lghit.FitTiming());
	    srnpeaks.push_back(lghit.Npeaks());
	    srfitflag.push_back(lghit.FitFlag());
	  }
	  if( module==106&&block==0 ){
	    sladc.push_back(lghit.FitPeak());
	    sltdc.push_back(lghit.FitTiming());
	    slnpeaks.push_back(lghit.Npeaks());
	    slfitflag.push_back(lghit.FitFlag());
	  }

	  // if(fitflag<2){
	  // if(npeak==0){
	  // hph[module-102][block]->Fill(lghit.PeakHeight());
	  // hpt[module-102][block]->Fill(lghit.PeakTime());
	  // htm[module-102][block]->Fill(lghit.Timing());
	  // hbl[module-102][block]->Fill(lghit.Baseline());
	  // hbr[module-102][block]->Fill(lghit.BaselineRms());
	  // hit[module-102][block]->Fill(lghit.Integral());
	  // ht0[module-102][block]->Fill(lghit.GetCalibTiming(lgbasic));
	  // hed[module-102][block]->Fill(lghit.GetEnergyDeposit(lgbasic));
	  // hnp[module-102][block]->Fill(lghit.Npeaks());
	  // hff[module-102][block]->Fill(lghit.FitFlag());
	  // }
	  // hfp[module-102][block]->Fill(lghit.FitPeak());
	  // hfx[module-102][block]->Fill(lghit.FitPeakTime());
	  // hft[module-102][block]->Fill(lghit.FitTiming());
	  // //hft[module-102][block]->Fill(lghit.GetCalibTiming(lgbasic, lghit.FitTiming()));
	  // hfw[module-102][block]->Fill(lghit.FitWidth());
	  // hfc[module-102][block]->Fill(lghit.FitChi2());
	  // }

	  // nhit[module-102]++;
	  // nhit[105-102]++;

	}//hit loop

	// for(int nmod=0;nmod<7;nmod++){
	//   hnh[nmod]->Fill(nhit[nmod]);
	// }

      }// exist hit

      tree->Fill();
      }

      // auto& lg_clusters1 = record->LG().Clusters();
      // int n_lgclusters = lg_clusters1.size();
      // if (lg_clusters1.size() != 0) {// exist cluster
      // 	for(int icl=0;icl<n_lgclusters;icl++){//cluster loop
      // 	  auto& lgcluster = lg_clusters1[icl];
      // 	  if(lgcluster.HitOrders().size()>1){
      // 	    hctd->Fill(lgcluster.TimeDifference());
      // 	    hcmp->Fill(lgcluster.MaxPeakHeight());
      // 	    hctm->Fill(lgcluster.Timing());
      // 	    hcps->Fill(lgcluster.PeakSum());
      // 	    hcgx->Fill(lgcluster.GlobalPos(*geometry).X());
      // 	    hcgy->Fill(lgcluster.GlobalPos(*geometry).Y());
      // 	    hcgz->Fill(lgcluster.GlobalPos(*geometry).Z());
      // 	    hcgyx->Fill(lgcluster.GlobalPos(*geometry).X(),lgcluster.GlobalPos(*geometry).Y());
      // 	    hcgzx->Fill(lgcluster.GlobalPos(*geometry).X(),lgcluster.GlobalPos(*geometry).Z());
      // 	  }
      // 	}//cluster loop
      // }// exist cluster


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

  delete geometry;
  delete dst0;
//  dst1->Close();
  return 0;
}
