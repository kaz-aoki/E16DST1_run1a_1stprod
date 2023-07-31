#define straightRoot_cxx
#include "straightRoot.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTreeIndex.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <unordered_map>

void straightRoot::Loop(int run)
{
//   In a ROOT session, you can do:
//      root> .L straightRoot.C
//      root> straightRoot t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   std::string foutname = "./initinfo_run" + to_string(run) + ".txt";
   std::ofstream fout(foutname);
   TH2F* hh = new TH2F("hh","hh",1000,-100,100,1000,-100,100);

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if(run_id != run) continue;

      TVector3 g1(fit_g100x, fit_g100y, fit_g100z);
      TVector3 g2(fit_g200x, fit_g200y, fit_g200z);
      // TVector3 g2(fit_g300x, fit_g300y, fit_g300z);

      // line eqn.: p = g1 + t*(g2-g1) = (1-t)*g1 + t*g2
      // line eqn.: py = (1-t)*g1y + t*g2y = 0 --> t = g1y / (g1y-g2y)
      double t = g1.X()/(g1.X()-g2.X());
      // double t = g1.Y()/(g1.Y()-g2.Y());
      TVector3 initpos = g1 + t*(g2-g1);
      TVector3 initdir = g1 - initpos;
      double norm = 1./initdir.Mag();
      initdir = initdir*norm;
      // fout << run_id <<" "<< event_id <<" "<< g1.X() <<" "<< g1.Y() <<" "<< g1.Z() <<" "<< g2.X() <<" "<< g2.Y() <<" "<< g2.Z() <<" "<< t <<" "<< initpos.X() <<" "<< initpos.Y() <<" "<< initpos.Z() <<" "<< initdir.X() <<" "<< initdir.Y() <<" "<< initdir.Z() <<std::endl;
      fout << run_id <<" "<< event_id <<" "<< initpos.X() <<" "<< initpos.Y() <<" "<< initpos.Z() <<" "<< initdir.X() <<" "<< initdir.Y() <<" "<< initdir.Z() <<std::endl;
      hh->Fill(initpos.Z(),initpos.Y());
      // hh->Fill(initdir.Z(),initdir.X());
   }
}

void straightRoot::ClearEntry()
{
  ntracks = 0;
  initposs.clear();
  initdirs.clear();
  timing_100xs.clear();
  timing_100ys.clear();
  timing_200xs.clear();
  timing_200ys.clear();
  timing_300xs.clear();
  timing_300ys.clear();
  timing2_100xs.clear();
  timing2_100ys.clear();
  timing2_200xs.clear();
  timing2_200ys.clear();
  timing2_300xs.clear();
  timing2_300ys.clear();
  residual_100xs.clear();
  residual_100ys.clear();
  residual_200xs.clear();
  residual_200ys.clear();
  residual_300xs.clear();
  residual_300ys.clear();
  chi2_xs.clear();
  chi2_ys.clear();
  tgt_zs.clear();
}

void straightRoot::MakeMap(int in_run_id, int maxevent)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   for (Long64_t jentry=0; jentry<nentries; jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      Long64_t nb = fChain->GetEntry(jentry);
      if( maxevent!=-1 && jentry>maxevent ) break;
      if( in_run_id != run_id ) continue;

      std::vector<int> val = map[event_id];
      if(val.size()==0){
	std::vector<int> tmp;
	tmp.push_back(jentry);
	map[event_id] = tmp;
      }
      else{
	std::vector<int> tmp;
	for(int i=0;i<val.size();i++){
	  tmp.push_back(val.at(i));
	}
	tmp.push_back(jentry);
	map[event_id] = tmp;
      }
   }

}

void straightRoot::SetEntry(int in_event_id)
{
  ClearEntry();
  std::vector<int> jentries = map[in_event_id];
  ntracks = jentries.size();
  for( int j=0; j<jentries.size(); j++){
    int jentry = jentries.at(j);
    Long64_t nb = fChain->GetEntry(jentry);
    TVector3 g1(fit_g100x, fit_g100y, fit_g100z);
    TVector3 g2(fit_g200x, fit_g200y, fit_g200z);
    TVector3 _initpos;
    TVector3 _initdir;
    CalcInitInfo(g1,g2,_initpos,_initdir);
    initposs.push_back(_initpos);
    initdirs.push_back(_initdir);
    timing_100xs.push_back(timing_x100);
    timing_100ys.push_back(timing_y100);
    timing_200xs.push_back(timing_x200);
    timing_200ys.push_back(timing_y200);
    timing_300xs.push_back(timing_x300);
    timing_300ys.push_back(timing_y300);
    timing2_100xs.push_back(timing2_x100);
    timing2_100ys.push_back(timing2_y100);
    timing2_200xs.push_back(timing2_x200);
    timing2_200ys.push_back(timing2_y200);
    timing2_300xs.push_back(timing2_x300);
    timing2_300ys.push_back(timing2_y300);
    residual_100xs.push_back(residual_100x);
    residual_100ys.push_back(residual_100y);
    residual_200xs.push_back(residual_200x);
    residual_200ys.push_back(residual_200y);
    residual_300xs.push_back(residual_300x);
    residual_300ys.push_back(residual_300y);
    chi2_xs.push_back(chi2_x);
    chi2_ys.push_back(chi2_y);
    tgt_zs.push_back(tgt_z);
  }

}

void straightRoot::CalcInitInfo(TVector3& g1, TVector3& g2, TVector3& _initpos, TVector3& _initdir)
{
  // line eqn.: p = g1 + t*(g2-g1) = (1-t)*g1 + t*g2
  // line eqn.: py = (1-t)*g1y + t*g2y = 0 --> t = g1y / (g1y-g2y)
  double t = g1.X()/(g1.X()-g2.X());
  // double t = g1.Y()/(g1.Y()-g2.Y());
  _initpos = g1 + t*(g2-g1);
  _initdir = g1 - _initpos;
  double norm = 1./_initdir.Mag();
  _initdir = _initdir*norm;
}
