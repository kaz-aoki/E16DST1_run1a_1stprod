#ifndef E16ANA_GammaAnalyzer_h
#define E16ANA_GammaAnalyzer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TF1.h>

#include <stdio.h>
#include <iostream>

class E16ANA_GammaAnalyzer{

public :

  struct hitset{
    int id;
    int mid;
    int cid;
    double x;
    double y;
    double z;
    double gx;
    double gy;
    double gz;
    float adc;
    float t;
    int fflag;
    float width;
  };

  E16ANA_GammaAnalyzer();
  ~E16ANA_GammaAnalyzer();
  double PhtoEnergy(){return mvtoe;};
  int ModuleToIndex(int module);
  int IndexToModule(int index);
  void ClearHits();
  void ClearHit0();
  void ClearHit1();
  void ClearHit(hitset& hit);
  void SetHit0(int _id, int _mid, int _cid, double _x, double _y, double _z, double _gx, double _gy, double _gz, float _adc, float _t, int _fflag, float _width);
  void SetHit0(hitset& hit);
  void SetHit1(int _id, int _mid, int _cid, double _x, double _y, double _z, double _gx, double _gy, double _gz, float _adc, float _t, int _fflag, float _width);
  void SetHit1(hitset& hit);
  void SetHit(hitset& hit, int _id, int _mid, int _cid, double _x, double _y, double _z, double _gx, double _gy, double _gz, float _adc, float _t, int _fflag, float _width);
  void SetHit(hitset& hit_unset, hitset& hit_set);
  bool Hit0isInvalid();
  bool Hit1isInvalid();
  bool HitisInvalid(hitset& hit);
  bool HitsareInvalid();
  bool HitsareInvalid(hitset& _hit0, hitset& _hit1);
  bool IsNeighborBlock(hitset& _hit0, hitset& _hit1);
  void FillForeHist();
  void FillMixHist();
  void FillHist(int ifm, hitset& _hit0, hitset& _hit1);
  void FillHit0();
  void FillHit1();
  void FillHit(int type, hitset hit);
  void ClearMixEvent();
  void ClearMixAll();
  void PushBackMixHit(hitset& hit);
  void PushBackMixEvent();
  void DrawTH1FCanvas(TCanvas* c, TString& fout, TH1F* h1, TH1F* h2, TH1F *h3, TH1F *h4);
  void DrawSameTH1FCanvas(TCanvas* c, TString& fout, TH1F* h1, TH1F* h2, double scale);
  double CalcMixScale(TH1F* h1, TH1F* h2);
  void Draw(TString& fout, TCanvas* c);
  void SetRootFile(char* fin_name);
  void DeleteRootFile();
  void SetHists();
  void ClearBranch();
  void SetBranchIds(int _run_id, int _event_id, int _spill_id);
  void FillTree();

private :

  int decaypos[4] = {-260,-20,0,+20};
  double e_etog = 1.17;
  double mvtoe = 0.005*e_etog;
  int mixevent = 10;

  hitset hit0;
  hitset hit1;
  std::vector<std::vector<hitset>> allmixhits[9];
  std::vector<hitset> eventmixhits[9];
  std::vector<std::vector<hitset>> allMixhits;
  std::vector<hitset> eventMixhits;

  TH1F* hp[2][4][2];
  TH1F* hpx[2][4][2];
  TH1F* hpy[2][4][2];
  TH1F* hpz[2][4][2];
  TH1F* hpt[2][4][2];
  TH1F* hpp[2][4][2];
  TH1F* hps[2][4];
  TH1F* hpsx[2][4];
  TH1F* hpsy[2][4];
  TH1F* hpsz[2][4];
  TH1F* hdist[2][4];
  TH2F* hpzpx[2][4];
  TH1F* hm[2][4];

  TH1F* hmid[2];
  TH1F* hcid[2];
  TH1F* hx[2];
  TH1F* hy[2];
  TH1F* hz[2];
  TH1F* hgx[2];
  TH1F* hgy[2];
  TH1F* hgz[2];
  TH1F* hadc[2];
  TH1F* ht[2];
  TH1F* hfflag[2];
  TH1F* hwidth[2];

  TTree* tree;
  int run_id;
  int event_id;
  int spill_id;
  double brp[2][2];
  double brpx[2][2];
  double brpy[2][2];
  double brpz[2][2];
  double brpt[2][2];
  double brpp[2][2];
  double brps[2];
  double brpsx[2];
  double brpsy[2];
  double brpsz[2];
  double brdist[2];
  double brm[2];
  int brmid[2];
  int brcid[2];
  double brx[2];
  double bry[2];
  double brz[2];
  double brgx[2];
  double brgy[2];
  double brgz[2];
  double bradc[2];
  double brt[2];
  int brfflag[2];
  double brwidth[2];

  TFile* fin;

};
#endif
