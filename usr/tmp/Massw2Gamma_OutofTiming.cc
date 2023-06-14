#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
#include <TRandom.h>
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
#include "E16ANA_LGCheckHist.hh"
#include "E16ANA_Massw2Gamma.hh"
#include "E16DST_Constant.hh"

using namespace std;
// namespace  bpo = boost::program_options;

#define TRG_ON

void DrawTH1FCanvas(TCanvas* c, TString& fout, TH1F* h1, TH1F* h2, TH1F *h3, TH1F *h4){
  c->Clear();
  c->Divide(2,2);
  c->cd(1);
  h1->Draw();
  c->cd(2);
  h2->Draw();
  c->cd(3);
  h3->Draw();
  c->cd(4);
  h4->Draw();
  c->SaveAs(fout,"pdf");
}

int main(int argc, char* argv[]) {
  if (argc != 6) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst0] [output.root] [output.pdf] [run ID] [max physics event (all: -1)] " << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  auto out_pdf_name = argv[3];
  auto run_id        = stoi(argv[4]);
  auto max_event     = stoi(argv[5]);

  gRandom->SetSeed( time(NULL) );

  TFile* fout = new TFile(out_file_name,"recreate");

  TH1F* hp[4][2];
  TH1F* hpx[4][2];
  TH1F* hpy[4][2];
  TH1F* hpz[4][2];
  TH1F* hpt[4][2];
  TH1F* hpp[4][2];
  TH1F* hps[4];
  TH1F* hpsx[4];
  TH1F* hpsy[4];
  TH1F* hpsz[4];
  TH1F* hdist[4];
  TH2F* hpzpx[4];
  TH1F* hm[4];
  TH1F* hpm[4][2];
  TH1F* hpxm[4][2];
  TH1F* hpym[4][2];
  TH1F* hpzm[4][2];
  TH1F* hptm[4][2];
  TH1F* hppm[4][2];
  TH1F* hpsm[4];
  TH1F* hpsxm[4];
  TH1F* hpsym[4];
  TH1F* hpszm[4];
  TH1F* hdistm[4];
  TH2F* hpzpxm[4];
  TH1F* hmm[4];
  int decaypos[4] = {-260,-20,0,+20};
  for(int i=0;i<4;i++){
    for(int j=0;j<2;j++){
      hp[i][j] = new TH1F(Form("hp%d%d",i,j),Form("mom%d_%d",j+1,decaypos[i]),100,0,2.5);
      hpx[i][j] = new TH1F(Form("hpx%d%d",i,j),Form("mom%dx_%d",j+1,decaypos[i]),100,-2.5,2.5);
      hpy[i][j] = new TH1F(Form("hpy%d%d",i,j),Form("mom%dy_%d",j+1,decaypos[i]),100,-2.5,2.5);
      hpz[i][j] = new TH1F(Form("hpz%d%d",i,j),Form("mom%dz_%d",j+1,decaypos[i]),100,-2.5,2.5);
      hpt[i][j] = new TH1F(Form("hpt%d%d",i,j),Form("mom%dtheta_%d",j+1,decaypos[i]),100,-2.5,2.5);
      hpp[i][j] = new TH1F(Form("hpp%d%d",i,j),Form("mom%dphi_%d",j+1,decaypos[i]),100,-2.5,2.5);
      hpm[i][j] = new TH1F(Form("hpm%d%d",i,j),Form("mix_mom%d_%d",j+1,decaypos[i]),100,0,2.5);
      hpxm[i][j] = new TH1F(Form("hpxm%d%d",i,j),Form("mix_mom%dx_%d",j+1,decaypos[i]),100,-2.5,2.5);
      hpym[i][j] = new TH1F(Form("hpym%d%d",i,j),Form("mix_mom%dy_%d",j+1,decaypos[i]),100,-2.5,2.5);
      hpzm[i][j] = new TH1F(Form("hpzm%d%d",i,j),Form("mix_mom%dz_%d",j+1,decaypos[i]),100,-2.5,2.5);
      hptm[i][j] = new TH1F(Form("hptm%d%d",i,j),Form("mix_mom%dtheta_%d",j+1,decaypos[i]),100,-2.5,2.5);
      hppm[i][j] = new TH1F(Form("hppm%d%d",i,j),Form("mix_mom%dphi_%d",j+1,decaypos[i]),100,-2.5,2.5);
    }
    hps[i] = new TH1F(Form("hps%d",i),Form("momsum_%d",decaypos[i]),100,0,2.5);
    hpsx[i] = new TH1F(Form("hpsx%d",i),Form("momsum_x_%d",decaypos[i]),100,-2.5,2.5);
    hpsy[i] = new TH1F(Form("hpsy%d",i),Form("momsum_y_%d",decaypos[i]),100,-2.5,2.5);
    hpsz[i] = new TH1F(Form("hpsz%d",i),Form("momsum_z_%d",decaypos[i]),100,-2.5,2.5);
    hdist[i] = new TH1F(Form("hdist%d",i),Form("2gamma_distance@LG_%d",decaypos[i]),100,0,5000);
    hpzpx[i] = new TH2F(Form("hpzpx%d",i),Form("mom_zvsx_%d",decaypos[i]),100,-2.5,2.5,100,-2.5,2.5);
    hm[i] = new TH1F(Form("hm%d",i),Form("IM_%d",decaypos[i]),100,0,1.5);
    hpsm[i] = new TH1F(Form("hpsm%d",i),Form("mix_momsum_%d",decaypos[i]),100,0,2.5);
    hpsxm[i] = new TH1F(Form("hpsxm%d",i),Form("mix_momsum_x_%d",decaypos[i]),100,-2.5,2.5);
    hpsym[i] = new TH1F(Form("hpsym%d",i),Form("mix_momsum_y_%d",decaypos[i]),100,-2.5,2.5);
    hpszm[i] = new TH1F(Form("hpszm%d",i),Form("mix_momsum_z_%d",decaypos[i]),100,-2.5,2.5);
    hdistm[i] = new TH1F(Form("hdistm%d",i),Form("mix_2gamma_distance@LG_%d",decaypos[i]),100,0,5000);
    hpzpxm[i] = new TH2F(Form("hpzpxm%d",i),Form("mix_mom_zvsx_%d",decaypos[i]),100,-2.5,2.5,100,-2.5,2.5);
    hmm[i] = new TH1F(Form("hmm%d",i),Form("mix_IM_%d",decaypos[i]),100,0,1.5);
  }

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
#ifdef TRG_ON
  E16ANA_TriggerCalibParam trigger_param;
  trigger_param.ReadConstantData(calib.CurrentRunID());
  bool TrigIsAWmax = trigger_param.IsMaximumWidth();
  int TrigAWmax = trigger_param.MaximumWidth();
  int TrigAWmin = trigger_param.MinimumWidth();
  int TrigTW = trigger_param.TimeWidth();
  if(!TrigIsAWmax){TrigAWmax=10000;}
  std::cout<<TrigIsAWmax<<" "<<TrigAWmax<<" "<<TrigAWmin<<" "<<TrigTW<<std::endl;
#else
  bool TrigIsAWmax = false;
  int TrigAWmax = -10000;
  int TrigAWmin = -10000;
  int TrigTW = -10000;
#endif

  // E16ANA_GTRcalibPedestal gtrped;
  // gtrped.ReadCalibData( calib.CurrentRunID() );
  E16ANA_LGBasic lgbasic;
  E16ANA_LGDeadChannel lgdead;
  lgbasic.SetMap();
  lgbasic.SetCalibMap();//it is necessary to use energy deposit and calibrated timing.
  lgbasic.SetTemplate();
  lgdead.ReadDeadChannelData();

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  E16ANA_GeometryV2::SetGlobalPointer(geometry);
  
  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }
  E16DST_DST1PhysicsRecord record;

  // E16ANA_GTRPedestal *gtr_pedestal = new E16ANA_GTRPedestal();
  // gtr_pedestal->Read(argv[5]);
  // auto dst1 = new E16DST_DST1();
  // auto dst1 = new E16DST_DST0();
  // if (!dst1->Open(out_file_name, E16DST_DST0::WriteMode)) {
  //   std::cerr << "Cannot open output file: " << out_file_name << std::endl;
  //   return -1;
  // }

  double mvtoe = 0.005;
  int mixevent = 100;
  std::vector<std::vector<E16ANA_Massw2Gamma::hitset>> mixhits[9];

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
      // std::cout<<event0->LG().NumberOfHits()<<" "<<event0->TriggerLG().NumberOfHits()<<std::endl;
      auto event_id = event0->EventID();

      E16DST_DST1LGFactory(lg_hits0, &record.LG(), 2, geometry); // w/ fit
      record.LG().AddHitAndClusterIds();
      record.LG().UpdatePtrs();
#ifdef TRG_ON
      E16DST_DST1TriggerFactory(trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record.Trigger());
      record.Trigger().AddHitAndClusterIDs();
      record.Trigger().UpdatePtrs();
#endif

//// Check begin

//dst1_lg_hit

      std::vector<E16ANA_Massw2Gamma::hitset> hits[9];

      auto& lg_hits1 = record.LG().Hits();
      int n_lghits = lg_hits1.size();
      int ihit[2] = {0, 0};
      for(ihit[0]=0; ihit[0]<n_lghits; ihit[0]++){
	auto& lghit0 = lg_hits1[ihit[0]];
	if( lghit0.FitFlag()>=2 ) continue;
	if( lghit0.FitPeak()<30. ) continue;

      	E16ANA_Massw2Gamma::hitset hit[2];
	auto lpos0 = lghit0.LocalPos(*geometry);
	auto gpos0 = lghit0.GlobalPos(*geometry);
	hit[0].init(lghit0.HitId(), lghit0.ModuleId(), lghit0.ChannelId(), lpos0.X(), lpos0.Y(), lpos0.Z(), gpos0.X(), gpos0.Y(), gpos0.Z(), lghit0.FitPeak(), lghit0.FitTiming());
      	int index = hit[0].mid - 101;
      	hits[index].push_back(hit[0]);

      	for(ihit[1]=ihit[0]+1; ihit[1]<n_lghits; ihit[1]++){
	  auto& lghit1 = lg_hits1[ihit[1]];
	  if( lghit1.FitFlag()>=2 ) continue;
	  if( lghit1.FitPeak()<30. ) continue;
	  auto lpos1 = lghit1.LocalPos(*geometry);
	  auto gpos1 = lghit1.GlobalPos(*geometry);
	  hit[1].init(lghit1.HitId(), lghit1.ModuleId(), lghit1.ChannelId(), lpos1.X(), lpos1.Y(), lpos1.Z(), gpos1.X(), gpos1.Y(), gpos1.Z(), lghit1.FitPeak(), lghit1.FitTiming());

	  if( fabs( hit[0].t-hit[1].t ) > 4. ) continue;
	  if( hit[0].mid==hit[1].mid && E16ANA_EIDSingleTrackAnalyzer::IsNeighborBlock(*geometry, hit[0].cid, hit[1].cid) ) continue;

      	  //calc im
      	  double ene[2] = {hit[0].adc*mvtoe, hit[1].adc*mvtoe};
      	  double enesum = ene[0] + ene[1];
      	  TVector3 gpos[4][2];
      	  TVector3 mom[4][2];
      	  TVector3 momsum[4];
      	  double im[4];
      	  for(int idp=0;idp<4;idp++){
      	    for(int ig=0;ig<2;ig++){
      	      gpos[idp][ig].SetXYZ(hit[ig].gx, hit[ig].gy, hit[ig].gz - decaypos[idp]);
      	      mom[idp][ig].SetXYZ(gpos[idp][ig].X()/gpos[idp][ig].Mag()*ene[ig], 
      		                  gpos[idp][ig].Y()/gpos[idp][ig].Mag()*ene[ig], 
      		                  gpos[idp][ig].Z()/gpos[idp][ig].Mag()*ene[ig]);
      	      hp[idp][ig]->Fill(mom[idp][ig].Mag());
      	      hpx[idp][ig]->Fill(mom[idp][ig].X());
      	      hpy[idp][ig]->Fill(mom[idp][ig].Y());
      	      hpz[idp][ig]->Fill(mom[idp][ig].Z());
      	      hpzpx[idp]->Fill(mom[idp][ig].Z(),mom[idp][ig].X());
      	      TVector3 rot(mom[idp][ig].Z(),mom[idp][ig].X(),mom[idp][ig].Y());
      	      hpt[idp][ig]->Fill(rot.Theta());
      	      hpp[idp][ig]->Fill(rot.Phi());
      	    }
      	    momsum[idp] = mom[idp][0] + mom[idp][1];
      	    hps[idp]->Fill(momsum[idp].Mag());
      	    hpsx[idp]->Fill(momsum[idp].X());
      	    hpsy[idp]->Fill(momsum[idp].Y());
      	    hpsz[idp]->Fill(momsum[idp].Z());
      	    double angle = mom[idp][0].Angle(mom[idp][1]);
      	    hdist[idp]->Fill(angle*1500.);
      	    im[idp] = sqrt( enesum*enesum - momsum[idp].Mag2() );
      	    hm[idp]->Fill( im[idp] );
      	  }

      	  //calc mix im
      	  std::vector<E16ANA_Massw2Gamma::hitset> mixhitcands(0);
      	  int ifore = gRandom->Uniform(0.5, 1.5);
      	  int imix  = (ifore+1)%2;
      	  int mixmid = hit[imix].mid - 101;
      	  for(int imix1=0; imix1<mixhits[mixmid].size(); imix1++){
      	    for(int imix2=0; imix2<mixhits[mixmid].at(imix1).size(); imix2++){
      	      E16ANA_Massw2Gamma::hitset mixhit = mixhits[mixmid].at(imix1).at(imix2);
	      if( fabs( hit[ifore].t-mixhit.t ) > 4. ) continue;
	      if( hit[ifore].mid==mixhit.mid && E16ANA_EIDSingleTrackAnalyzer::IsNeighborBlock(*geometry, hit[ifore].cid, mixhit.cid) ) continue;
      	      mixhitcands.push_back(mixhit);
      	    }
      	  }
      	  if( mixhitcands.size()==0 ){
      	  }
      	  else{
      	    int imixhit = gRandom->Uniform(0.5, (float)mixhitcands.size()-0.5);
      	    E16ANA_Massw2Gamma::hitset mixhit;
      	    for(int imix1=0; imix1<mixhitcands.size(); imix1++){
      	      if( imix1==imixhit ){
      		mixhit = mixhitcands.at(imix1);
      	      }
      	    }
      	    double enem[2] = {hit[ifore].adc*mvtoe, mixhit.adc*mvtoe};
      	    double enesumm = enem[0] + enem[1];
      	    TVector3 gposm[4][2];
      	    TVector3 momm[4][2];
      	    TVector3 momsumm[4];
      	    double imm[4];
      	    for(int idp=0;idp<4;idp++){
      	      gposm[idp][0].SetXYZ(hit[ifore].gx, hit[ifore].gy, hit[ifore].gz - decaypos[idp]);
      	      gposm[idp][1].SetXYZ(mixhit.gx, mixhit.gy, mixhit.gz - decaypos[idp]);
      	      for(int ig=0;ig<2;ig++){
      		momm[idp][ig].SetXYZ(gposm[idp][ig].X()/gposm[idp][ig].Mag()*enem[ig], 
      		                     gposm[idp][ig].Y()/gposm[idp][ig].Mag()*enem[ig], 
      		                     gposm[idp][ig].Z()/gposm[idp][ig].Mag()*enem[ig]);
      		hpm[idp][ig]->Fill(momm[idp][ig].Mag());
      		hpxm[idp][ig]->Fill(momm[idp][ig].X());
      		hpym[idp][ig]->Fill(momm[idp][ig].Y());
      		hpzm[idp][ig]->Fill(momm[idp][ig].Z());
      		hpzpxm[idp]->Fill(momm[idp][ig].Z(),momm[idp][ig].X());
      		TVector3 rot(momm[idp][ig].Z(),momm[idp][ig].X(),momm[idp][ig].Y());
      		hptm[idp][ig]->Fill(rot.Theta());
      		hppm[idp][ig]->Fill(rot.Phi());
      	      }
      	      momsumm[idp] = momm[idp][0] + momm[idp][1];
      	      hpsm[idp]->Fill(momsumm[idp].Mag());
      	      hpsxm[idp]->Fill(momsumm[idp].X());
      	      hpsym[idp]->Fill(momsumm[idp].Y());
      	      hpszm[idp]->Fill(momsumm[idp].Z());
      	      double anglem = momm[idp][0].Angle(momm[idp][1]);
      	      hdistm[idp]->Fill(anglem*1500.);
      	      imm[idp] = sqrt( enesumm*enesumm - momsumm[idp].Mag2() );
      	      hmm[idp]->Fill( imm[idp] );
      	    }
      	  }

      	}
      }

      //fill mixhits
      for(int imod=0;imod<9;imod++){
      	mixhits[imod].push_back(hits[imod]);
      	if( mixhits[imod].size() > mixevent ){
      	  mixhits[imod].erase(mixhits[imod].begin());
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

  TCanvas* c = new TCanvas("c","c",1000,700);
  TString fsout = "./test.pdf";
  c->SaveAs(fsout+"[","pdf");
  for(int idp=0;idp<4;idp++){
    for(int ig=0;ig<2;ig++){
      DrawTH1FCanvas(c,fsout,hp[idp][ig],hpx[idp][ig],hpy[idp][ig],hpz[idp][ig]);
      DrawTH1FCanvas(c,fsout,hp[idp][ig],hp[idp][ig], hpt[idp][ig],hpp[idp][ig]);
    }
    DrawTH1FCanvas(c,fsout,hps[idp],hpsx[idp],hpsy[idp],hpsz[idp]);
    c->Clear();
    c->cd()->SetGrid();
    hpzpx[idp]->Draw("colz");
    c->SaveAs(fsout,"pdf");
    c->Clear();
    hdist[idp]->Draw();
    c->SaveAs(fsout,"pdf");
    c->Clear();
    hm[idp]->Draw();
    c->SaveAs(fsout,"pdf");
    //mix
    for(int ig=0;ig<2;ig++){
      DrawTH1FCanvas(c,fsout,hpm[idp][ig],hpxm[idp][ig],hpym[idp][ig],hpzm[idp][ig]);
      DrawTH1FCanvas(c,fsout,hpm[idp][ig],hpm[idp][ig], hptm[idp][ig],hppm[idp][ig]);
    }
    DrawTH1FCanvas(c,fsout,hpsm[idp],hpsxm[idp],hpsym[idp],hpszm[idp]);
    c->Clear();
    c->cd()->SetGrid();
    hpzpxm[idp]->Draw("colz");
    c->SaveAs(fsout,"pdf");
    c->Clear();
    hdistm[idp]->Draw();
    c->SaveAs(fsout,"pdf");
    c->Clear();
    hm[idp]->Draw();
    hmm[idp]->SetLineColor(2);
    hmm[idp]->Draw("sames");
    c->SaveAs(fsout,"pdf");
    //mix
  }
  c->SaveAs(fsout+"]","pdf");

  fout->Write();
  fout->Close();


  delete geometry;
  delete dst0;
  //  dst1->Close();
  return 0;
}
