#include <stdio.h>
#include <iostream>
#include <fstream>
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
#include "E16ANA_LGProjection.hh"
#include "E16ANA_Massw2Gamma.hh"
#include "E16ANA_GammaAnalyzer.hh"
#include "E16DST_Constant.hh"
#include "E16ANA_TriggerConstant.hh"
#include "E16DST_TriggerChannelMap.hh"
#include "E16ANA_TriggerCoincidenceMap.hh"

using namespace std;
// namespace  bpo = boost::program_options;

struct particleset{
  int pid;
  double mass;
  double px;
  double py;
  double pz;
  double p;
  int charge;
  bool lcross;
  int lmid;
  int lcid;
  bool hcross;
  int hmid;
  int hcid;
  bool gcross;
  int gmid;
  int gcid;
  bool ssd;
  bool g100;
  bool g200;
};

bool TriggerLogicIsOK(E16DST_TriggerChannelMap* channel_map, E16ANA_TriggerCoincidenceMap* coincidence_maps, particleset& ptmp){

  if( ptmp.charge==0 ){
    return false;
  }

  auto& coincidence_map = coincidence_maps->CoincidenceMap(ptmp.lmid, ptmp.lcid, true);
  bool GTR = false;
  for (int channel = 0; channel < coincidence_map.gtr_map.size(); ++channel) {
    if (!coincidence_map.gtr_map[channel]) continue;
    auto ids = channel_map->GetDetectorIDs(32 * (coincidence_map.gtr_start_module + int{channel / E16DST_Constant::NTriggerChannelsGTR}) + channel % E16DST_Constant::NTriggerChannelsGTR);
    if( ptmp.gmid==ids.moduleID && ptmp.gcid==ids.channelID ){
      GTR = true;
      break;
    }
  }
  if( !GTR ){
    return false;
  }
  bool HBD = false;
  for (int channel = 0; channel < coincidence_map.hbd_map.size(); ++channel) {
    if (!coincidence_map.hbd_map[channel]) continue;
    auto ids = channel_map->GetDetectorIDs(256 + 64 * coincidence_map.hbd_start_module + 32 * int{channel / (E16DST_Constant::NTriggerChannelsHBD / 2)} + channel % (E16DST_Constant::NTriggerChannelsHBD / 2));
    if( ptmp.hmid==ids.moduleID && ptmp.hcid==ids.channelID ){
      HBD = true;
      break;
    }
  }
  if( !HBD ){
    return false;
  }
  else{
    return true;
  }
}

bool IsTrgPair(int mid1, int cid1, int mid2, int cid2){
  int d1x = (mid1-100)*7+cid1%10;
  int d1y = cid1/10;
  int d2x = (mid2-100)*7+cid2%10;
  int d2y = cid2/10;
  int dist = (d2x-d1x)*(d2x-d1x)+(d2y-d1y)*(d2y-d1y);
  if( dist>1 && dist<64 ){
    return true;
  }
  else{
    return false;
  }
}

int main(int argc, char* argv[]) {
  if (argc != 5) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.txt] [output.root] [output.pdf] [max event]" << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  auto out_pdf_name = argv[3];
  auto maxevent = stoi(argv[4]);

  std::ifstream fin(in_file_name);
  TFile* fout = new TFile(out_file_name,"recreate");

  // auto *analyzer = new E16ANA_GammaAnalyzer();

  static auto* channel_map      = new E16DST_TriggerChannelMap(static_cast<std::string>(TriggerChannelMapFiles[0]), static_cast<std::string>(TriggerChannelMapFiles[1]), static_cast<std::string>(TriggerChannelMapFiles[2]));
  static auto* coincidence_maps = new E16ANA_TriggerCoincidenceMap(CoincidenceMapFiles, TriggerChannelMapFiles);

  E16ANA_LGProjection proj;
  TVector3 initvtx(0., 0., -20.);
  // TVector3 initvtx( 25., 0., -40.);//left up
  // TVector3 initvtx( 25., 0.,  40.);//left down
  // TVector3 initvtx(-25., 0., -40.);//right up
  // TVector3 initvtx(-25., 0.,  40.);//right down

  std::vector<particleset> parts(0);

  TTree* tree = new TTree("tree","tree");
  int out_event_id;
  int out_n_tracks;
  std::vector<int> out_track_id;
  std::vector<int> out_track_pid;
  std::vector<double> out_track_mass;
  std::vector<double> out_track_px;
  std::vector<double> out_track_py;
  std::vector<double> out_track_pz;
  std::vector<double> out_track_p;
  std::vector<int> out_track_charge;
  std::vector<bool> out_track_lcross;
  std::vector<int> out_track_lmid;
  std::vector<int> out_track_lcid;
  std::vector<bool> out_track_hcross;
  std::vector<int> out_track_hmid;
  std::vector<int> out_track_hcid;
  std::vector<bool> out_track_gcross;
  std::vector<int> out_track_gmid;
  std::vector<int> out_track_gcid;
  std::vector<bool> out_track_trglogic_single;
  std::vector<bool> out_track_trglogic_pair;
  std::vector<bool> out_track_ssd;
  std::vector<bool> out_track_g100;
  std::vector<bool> out_track_g200;
  tree->Branch("event_id",&out_event_id,"event_id/I");
  tree->Branch("n_tracks",&out_n_tracks,"n_tracks/I");
  tree->Branch("track_id", &out_track_id);
  tree->Branch("track_pid", &out_track_pid);
  tree->Branch("track_mass", &out_track_mass);
  tree->Branch("track_px", &out_track_px);
  tree->Branch("track_py", &out_track_py);
  tree->Branch("track_pz", &out_track_pz);
  tree->Branch("track_p", &out_track_p);
  tree->Branch("track_charge", &out_track_charge);
  tree->Branch("track_lcross", &out_track_lcross);
  tree->Branch("track_lmid", &out_track_lmid);
  tree->Branch("track_lcid", &out_track_lcid);
  tree->Branch("track_hcross", &out_track_hcross);
  tree->Branch("track_hmid", &out_track_hmid);
  tree->Branch("track_hcid", &out_track_hcid);
  tree->Branch("track_gcross", &out_track_gcross);
  tree->Branch("track_gmid", &out_track_gmid);
  tree->Branch("track_gcid", &out_track_gcid);
  tree->Branch("track_trglogic_single", &out_track_trglogic_single);
  tree->Branch("track_trglogic_pair", &out_track_trglogic_pair);
  tree->Branch("track_ssd", &out_track_ssd);
  tree->Branch("track_g100", &out_track_g100);
  tree->Branch("track_g200", &out_track_g200);

  TH1F* hhits[11];
  TH1F* hhitswc[11];
  TH1F* hpairs[11];
  TH1F* hpairid[11];
  for(int i=0;i<11;i++){
    hhits[i] = new TH1F(Form("hhits%d",i),Form("multiplicity_%d",i+100),10,0,10);
    hhitswc[i] = new TH1F(Form("hhitswc%d",i),Form("multiplicity_w/TrgLogic_%d",i+100),10,0,10);
    hpairs[i] = new TH1F(Form("hpairs%d",i),Form("n_pair_w/TrgLogic_%d",i+100),10,0,10);
    hpairid[i] = new TH1F(Form("hpairid%d",i),Form("pair_id_w/TrgLogic_%d",i+100),55,-10,45);
  }
  TH1F* hnmod1 = new TH1F("hnmod1","hnmod1",10,0,10);
  TH1F* hnmod2 = new TH1F("hnmod2","hnmod2",10,0,10);

  int n_particle = 0;
  int n_pip = 0;
  int n_pim = 0;
  int n_pi0 = 0;
  int eventid_current = 0;
  int eventid_before = 0;
  int n_event = 0;

  while (!fin.eof()) {
    if (n_particle % 1000 == 0) {
      cout << "Number of particle: " << n_particle << endl;
    }
    if (maxevent!=-1 && n_event>=maxevent) {
      break;
    }

    int eventid, pid;
    double impactp, mass, px, py, pz;
    std::string name;
    fin >> eventid >> impactp >> pid >> mass >> name >> px >> py >> pz;
    int charge = pid/fabs(pid);
    if(pid==111){charge = 0;}
    eventid_current = eventid;
    if(pid==211){n_pip++;}
    if(pid==-211){n_pim++;}
    if(pid==111){n_pi0++;}

    if( eventid_current != eventid_before ){
      //Fill
      int nhits[11] = {0};
      int nhitswc[11] = {0};
      int npairs[11] = {0};
      int nmod1 = 0;
      int nmod2 = 0;
      out_track_trglogic_single.resize( parts.size(), false );
      out_track_trglogic_pair.resize( parts.size(), false );
      for(int ip=0; ip<parts.size(); ip++){
	nhits[ parts.at(ip).gmid-100 ]++;
	out_track_id.push_back(ip);
	out_track_pid.push_back(parts.at(ip).pid);
	out_track_mass.push_back(parts.at(ip).mass);
	out_track_px.push_back(parts.at(ip).px);
	out_track_py.push_back(parts.at(ip).py);
	out_track_pz.push_back(parts.at(ip).pz);
	out_track_p.push_back(parts.at(ip).p);
	out_track_charge.push_back(parts.at(ip).charge);
	out_track_lcross.push_back(parts.at(ip).lcross);
	out_track_lmid.push_back(parts.at(ip).lmid);
	out_track_lcid.push_back(parts.at(ip).lcid);
	out_track_hcross.push_back(parts.at(ip).hcross);
	out_track_hmid.push_back(parts.at(ip).hmid);
	out_track_hcid.push_back(parts.at(ip).hcid);
	out_track_gcross.push_back(parts.at(ip).gcross);
	out_track_gmid.push_back(parts.at(ip).gmid);
	out_track_gcid.push_back(parts.at(ip).gcid);
	out_track_ssd.push_back(parts.at(ip).ssd);
	out_track_g100.push_back(parts.at(ip).g100);
	out_track_g200.push_back(parts.at(ip).g200);
	if( !TriggerLogicIsOK( channel_map, coincidence_maps, parts.at(ip) ) ) continue;
	nhitswc[ parts.at(ip).gmid-100 ]++;
	out_track_trglogic_single[ip] = true;
	for(int jp=ip+1; jp<parts.size(); jp++){
	  if( parts.at(jp).gmid != parts.at(ip).gmid ) continue;
	  if( !TriggerLogicIsOK( channel_map, coincidence_maps, parts.at(jp)) ) continue;
	  if( !IsTrgPair( parts.at(ip).lmid, parts.at(ip).lcid, parts.at(jp).lmid, parts.at(jp).lcid ) ) continue;
	  npairs[ parts.at(ip).gmid-100 ]++;
	  int pairid = int(parts.at(ip).pid/100) + int(parts.at(jp).pid/100);
	  if(pairid==0){pairid = fabs( int(parts.at(ip).pid/100) );}
	  hpairid[ parts.at(ip).gmid-100 ]->Fill(pairid);
	  out_track_trglogic_pair[ip] = true;
	  out_track_trglogic_pair[jp] = true;
	}
      }
      for(int im=0; im<11; im++){
	hhits[im]->Fill(nhits[im]);
	hhitswc[im]->Fill(nhitswc[im]);
	if(nhits[im]>0){nmod1++;}
	if(nhits[im]>1){nmod2++;}
	hpairs[im]->Fill(npairs[im]);
      }
      hnmod1->Fill(nmod1);
      hnmod2->Fill(nmod2);

      out_event_id = eventid_before;
      out_n_tracks = parts.size();
      tree->Fill();
      //Clear
      parts.clear();
      out_track_id.clear();
      out_track_pid.clear();
      out_track_mass.clear();
      out_track_px.clear();
      out_track_py.clear();
      out_track_pz.clear();
      out_track_p.clear();
      out_track_charge.clear();
      out_track_lcross.clear();
      out_track_lmid.clear();
      out_track_lcid.clear();
      out_track_hcross.clear();
      out_track_hmid.clear();
      out_track_hcid.clear();
      out_track_gcross.clear();
      out_track_gmid.clear();
      out_track_gcid.clear();
      out_track_trglogic_single.clear();
      out_track_trglogic_pair.clear();
      out_track_ssd.clear();
      out_track_g100.clear();
      out_track_g200.clear();
      // std::cout<<"*************"<<std::endl;//event head
    }

    particleset ptmp;
    ptmp.pid = pid;
    ptmp.mass = mass;
    ptmp.px = px;
    ptmp.py = py;
    ptmp.pz = pz;
    ptmp.charge = charge;
    TVector3 initmom(px,py,pz);
    ptmp.p = initmom.Mag();
    if( charge!=0 ){
      proj.SetInitInfo( initvtx, initmom, charge );
      ptmp.lcross = proj.CalcCrossInfo();
    }
    else{
      proj.SetInitInfo( initvtx, initmom );
      ptmp.lcross = proj.CalcCrossInfoStraight();
    }
    ptmp.lmid = proj.Module();
    ptmp.lcid = proj.Block();
    ptmp.hcross = proj.TrgHBD();
    ptmp.hmid = proj.TrgHBDMid();
    ptmp.hcid = proj.TrgHBDCid();
    ptmp.gcross = proj.TrgGTR();
    ptmp.gmid = proj.TrgGTRMid();
    ptmp.gcid = proj.TrgGTRCid();
    ptmp.ssd = proj.OfflineSSD();
    ptmp.g100 = proj.OfflineGTR100();
    ptmp.g200 = proj.OfflineGTR200();
    if( ptmp.charge==0 || (ptmp.lcross && ptmp.hcross && ptmp.gcross) ){
      parts.push_back( ptmp );
    }

    if( eventid_current != eventid_before ){
      eventid_before = eventid_current;
      n_event++;
    }

    ++n_particle;
  }

  std::cout<<n_event<<" "<<n_particle<<std::endl;
  std::cout<<n_pip<<" "<<n_pim<<" "<<n_pi0<<" "<<n_pip+n_pim+n_pi0<<std::endl;

  TString fsout = Form("%s",out_pdf_name);
  TCanvas* c = new TCanvas("c","c",1000,700);
  c->SaveAs(fsout+"[","pdf");
  c->Clear();
  c->Divide(4,4);
  for(int i=0;i<11;i++){
    c->cd(i+1);
    hhits[i]->SetMarkerSize(2.5);
    hhits[i]->Draw("hist text45");
  }
  c->cd(13);
  hnmod1->SetMarkerSize(2.5);
  hnmod1->Draw("hist text45");
  c->cd(14);
  hnmod2->SetMarkerSize(2.5);
  hnmod2->Draw("hist text45");
  c->SaveAs(fsout,"pdf");
  c->Clear();
  c->Divide(4,4);
  for(int i=0;i<11;i++){
    c->cd(i+1);
    hhitswc[i]->SetMarkerSize(2.5);
    hhitswc[i]->Draw("hist text45");
  }
  c->SaveAs(fsout,"pdf");
  c->Clear();
  c->Divide(4,4);
  for(int i=0;i<11;i++){
    c->cd(i+1);
    hpairs[i]->SetMarkerSize(2.5);
    hpairs[i]->Draw("hist text45");
  }
  c->SaveAs(fsout,"pdf");
  c->Clear();
  c->Divide(4,4);
  for(int i=0;i<11;i++){
    c->cd(i+1);
    hpairid[i]->SetMarkerSize(2.5);
    hpairid[i]->Draw("hist text45");
  }
  c->SaveAs(fsout,"pdf");
  c->SaveAs(fsout+"]","pdf");

  fout->Write();
  fout->Close();

  return 0;
}
