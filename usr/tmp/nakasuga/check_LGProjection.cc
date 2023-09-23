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

bool IsTrgPair(int id1, int id2){
  int mid1 = id1/100;
  int mid2 = id2/100;
  int cid1 = id1-mid1*100;
  int cid2 = id2-mid2*100;
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

  std::vector<int> hits[11];
  for(int i=0;i<11;i++){
    hits[i].clear();
  }
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
    eventid_current = eventid;
    if(pid==211){n_pip++;}
    if(pid==-211){n_pim++;}
    if(pid==111){n_pi0++;}

    if( eventid_current != eventid_before ){
      //Fill
      int nmod1 = 0;
      int nmod2 = 0;
      int npairall = 0;
      for(int i=0;i<11;i++){
	hhits[i]->Fill(hits[i].size());
	if(hits[i].size()>0){nmod1++;}
	if(hits[i].size()>1){nmod2++;}
	int npair = 0;
	if(hits[i].size()>1){
	  for(int ip=0;ip<hits[i].size();ip++){
	    for(int jp=ip+1;jp<hits[i].size();jp++){
	      int id1 = hits[i].at(ip);
	      int id2 = hits[i].at(jp);
	      if( IsTrgPair(id1, id2) ){
		npair++;
	      }
	    }
	  }
	}
	hpairs[i]->Fill(npair);
	npairall+=npair;
      }
      hnmod1->Fill(nmod1);
      hnmod2->Fill(nmod2);
      //Clear
      for(int i=0;i<11;i++){ hits[i].clear(); }
      // std::cout<<"*************"<<std::endl;//event head
    }

    if( fabs(pid)==211 ){
      TVector3 initmom(px,py,pz);
      proj.SetInitInfo(initvtx, initmom, pid/fabs(pid) );
      bool is_crossed = proj.CalcCrossInfo();
      int gmid = proj.GTRModule();
      if( is_crossed && gmid>=100 && gmid<=110 ){
	// std::cout<<eventid<<" "<<name<<" "<<proj.Module()<<" "<<proj.Block()<<" "<<gmid<<std::endl;
	hits[gmid-100].push_back( proj.Module()*100+proj.Block() );
      }
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
