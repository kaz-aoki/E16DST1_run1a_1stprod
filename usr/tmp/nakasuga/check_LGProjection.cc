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

using namespace std;
// namespace  bpo = boost::program_options;

struct particleset{
  int pid;
  double mass;
  double px;
  double py;
  double pz;
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
};

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
  // TFile* fout = new TFile(out_file_name,"recreate");

  // auto *analyzer = new E16ANA_GammaAnalyzer();

  E16ANA_LGProjection proj;
  TVector3 initvtx(0., 0., 0.);
  // TVector3 initvtx( 25., 0., -40.);//left up
  // TVector3 initvtx( 25., 0.,  40.);//left down
  // TVector3 initvtx(-25., 0., -40.);//right up
  // TVector3 initvtx(-25., 0.,  40.);//right down

  std::vector<particleset> parts(0);

  TH1F* hhits[11];
  TH1F* hpairs[11];
  for(int i=0;i<11;i++){
    hhits[i] = new TH1F(Form("hhits%d",i),Form("multiplicity_%d",i+100),10,0,10);
    hpairs[i] = new TH1F(Form("hpairs%d",i),Form("n_pair_%d",i+100),10,0,10);
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
      int npairs[11] = {0};
      int nmod1 = 0;
      int nmod2 = 0;
      for(int ip=0; ip<parts.size(); ip++){
	nhits[ parts.at(ip).gmid-100 ]++;
	for(int jp=ip+1; jp<parts.size(); jp++){
	  if( parts.at(jp).gmid != parts.at(ip).gmid ) continue;
	  if( IsTrgPair( parts.at(ip).lmid, parts.at(ip).lcid, parts.at(jp).lmid, parts.at(jp).lcid ) ){
	    npairs[ parts.at(ip).gmid-100 ]++;
	  }
	}
      }
      for(int im=0; im<11; im++){
	hhits[im]->Fill(nhits[im]);
	if(nhits[im]>0){nmod1++;}
	if(nhits[im]>1){nmod2++;}
	hpairs[im]->Fill(npairs[im]);
      }
      hnmod1->Fill(nmod1);
      hnmod2->Fill(nmod2);
      //Clear
      parts.clear();
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
    if( charge!=0 ){
      proj.SetInitInfo( initvtx, initmom, charge );
      ptmp.lcross = proj.CalcCrossInfo();
    }
    // else{
    //   proj.SetInitInfoStraight( initvtx, initmom );
    //   ptmp.lcross = proj.CalcCrossInfoStraight();
    // }
    ptmp.lmid = proj.Module();
    ptmp.lcid = proj.Block();
    ptmp.hcross = proj.TrgHBD();
    ptmp.hmid = proj.TrgHBDMid();
    ptmp.hcid = proj.TrgHBDCid();
    ptmp.gcross = proj.TrgGTR();
    ptmp.gmid = proj.TrgGTRMid();
    ptmp.gcid = proj.TrgGTRCid();
    if( ptmp.charge!=0 && ptmp.lcross && ptmp.gcross ){
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
    hpairs[i]->SetMarkerSize(2.5);
    hpairs[i]->Draw("hist text45");
  }
  c->SaveAs(fsout,"pdf");
  c->SaveAs(fsout+"]","pdf");

  // fout->Write();
  // fout->Close();

  return 0;
}
