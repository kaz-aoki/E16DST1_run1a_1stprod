#ifndef GTRCheckHist_hh
#define GTRCheckHist_hh

#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1Constant.hh"
#include <TH1D.h>


class GTRCheckHist{
public:
    GTRCheckHist();
    ~GTRCheckHist();

    //void Fill(E16DST_DST0Detector<E16DST_DST1GTRHit> *hits, E16DST_DST0Detector<E16DST_DST1GTRCluster> *clusters);
    void Fill(E16DST_DST1Detector<E16DST_DST1GTRHit, E16DST_DST1GTRCluster> *gtr1);
    void Fill(std::vector<std::shared_ptr<E16DST_DST1StraightTrack3D>> st_tracks);
    TH1D *h_cl_ncluster_x[10][3];
    TH1D *h_cl_ncluster_y[10][3];
    TH1D *h_cl_ncluster_yb[10][3];
    TH1D *h_cl_numhits_x[10][3];
    TH1D *h_cl_numhits_y[10][3];
    TH1D *h_cl_numhits_yb[10][3];
    TH1D *h_cl_charge_x[10][3];
    TH1D *h_cl_charge_y[10][3];
    TH1D *h_cl_charge_yb[10][3];
    TH1D *h_cl_local_x[10][3];
    TH1D *h_cl_local_y[10][3];
    TH1D *h_cl_local_yb[10][3];
    TH1D *h_cl_timing_x[10][3];
    TH1D *h_cl_timing_y[10][3];
    TH1D *h_cl_timing_yb[10][3];
    TH1D *h_cl_max_peak_x[10][3];
    TH1D *h_cl_max_peak_y[10][3];
    TH1D *h_cl_max_peak_yb[10][3];
    TH1D *h_cl_max_peak_ch_x[10][3];
    TH1D *h_cl_max_peak_ch_y[10][3];
    TH1D *h_cl_max_peak_ch_yb[10][3];
    TH1D *h_cl_tdcpos_x[10][3];
    TH1D *h_cl_tdcpos_y[10][3];
    TH1D *h_cl_tdcpos_yb[10][3];
    TH1D *h_cl_tan_x[10][3];
    TH1D *h_cl_tan_y[10][3];
    TH1D *h_cl_tan_yb[10][3];

	TH1D *h_tgt_z[10];


private:

    

};

#endif
