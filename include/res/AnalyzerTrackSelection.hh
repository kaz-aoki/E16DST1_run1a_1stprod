//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Feb  3 22:10:48 2022 by ROOT version 6.18/04
// from TTree tree/tree
// found on file: out/root03a/trackselection_chisq30_unlinklg.root
//////////////////////////////////////////////////////////

#ifndef AnalyzerTrackSelection_h
#define AnalyzerTrackSelection_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>

#include <stdio.h>
#include <iostream>
using namespace std;

// Header file for the classes stored in the TTree if any.
#include "SingleTrackAnalyzerForRes.hh"
#include "vector"
#include "vector"
#include "vector"
#include "vector"

class AnalyzerTrackSelection {
private :
   //HBD residual region for selecting tracks
   // double track_select_sigma = 2.;
   // double hbd_voriginx[4]={0.};
   // double hbd_voriginy[4]={0.};
   // double hbd_vsigmax[4]={25.,25.,25.,25.};
   // double hbd_vsigmay[4]={25.,25.,25.,25.};

public :
   struct hitset{
     int mid;
     double lx;
     double ly;
     double adc;
     double tdc;
     bool operator<(const hitset& another){
       return tdc < another.tdc;
     }
   };

   struct trackset{
     int track_id;
     double chisq;
     double ssd;
     double gtr100x;
     double gtr100y;
     double gtr200x;
     double gtr200y;
     double gtr300x;
     double gtr300y;

     bool operator==(const trackset& another){
       if( ssd == another.ssd
	 || gtr100x == another.gtr100x
	 || gtr100y == another.gtr100y
	 || gtr200x == another.gtr200x
	 || gtr200y == another.gtr200y
	 || gtr300x == another.gtr300x
	 || gtr300y == another.gtr300y) return true;
       return false;
     }
   };

   struct lgcls{
     std::vector<int> cids;
     std::vector<double> resxs;
     std::vector<double> resys;
     std::vector<double> adcs;
     std::vector<double> tdcs;
     double adcsum;
     double timediff;
     double cogx;
     double cogy;
     int maxadcch;
   };

  double relg[4][5][6][7]={
    {//morino220531
    {//103
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    },
    {//104
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    },
    {//
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    },
    // {//106morino
    // {1.18,0.93,1.10,0.97,1.06,1.08,1},
    // {0.98,1.00,0.87,0.99,0.93,0.98,1},
    // {1.59,0.96,0.92,0.83,0.85,0.86,0.95},
    // {1.19,0.95,0.89,1.03,1.11,1.09,0.73},
    // {0.95,0.85,0.85,0.88,0.77,1.08,1},
    // {1.28,1.09,0.96,0.87,0.85,1.00,1},
    // },
    {//106
      {1,0.788,0.932,0.822,0.898,0.915,1},
      {0.831,0.847,0.737,0.839,0.788,0.831,1},
      {1.35,0.814,0.78,0.703,0.72,0.729,0.805},
      {1.01,0.805,0.754,0.873,0.941,0.924,0.619},
      {0.805,0.72,0.72,0.746,0.653,0.915,1},
      {1.08,0.924,0.814,0.737,0.72,0.847,1},
    },
    {//107
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    }
    },

    {//morino220822
    {//103
    {0.0060,0.0070,0.0110,0.0130,0.0135,0.0150,0.0090},
    {0.0090,0.0130,0.0145,0.0175,0.0170,0.0190,0.0154},
    {0.0235,0.0280,0.0275,0.0280,0.0280,0.0280,0.0280},
    {0.0235,0.0250,0.0300,0.0290,0.0280,0.0280,0.0280},
    {0.0135,0.0136,0.0170,0.0245,0.0190,0.0190,0.0144},
    {0.0060,0.0100,0.0160,0.0145,0.0140,0.0150,0.0090},
    },
    {//104
    {0.0130,0.0130,0.0110,0.0110,0.0115,0.0110,0.0090},
    {0.0230,0.0225,0.0210,0.0175,0.0185,0.0160,0.0154},
    {0.0320,0.0320,0.0300,0.0300,0.0270,0.0260,0.0310},
    {0.0322,0.0320,0.0285,0.0260,0.0250,0.0250,0.0290},
    {0.0230,0.0225,0.0210,0.0185,0.0185,0.0160,0.0146},
    {0.0135,0.0135,0.0110,0.0110,0.0115,0.0110,0.0090},
    },
    {//
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    },
    {//106
    {0.0090,0.0070,0.0065,0.0085,0.0105,0.0110,0.0090},
    {0.0195,0.0190,0.0180,0.0180,0.0225,0.0210,0.0154},
    {0.0290,0.0290,0.0290,0.0300,0.0310,0.0310,0.0310},
    {0.0265,0.0275,0.0290,0.0300,0.0310,0.0310,0.0310},
    {0.0195,0.0190,0.0190,0.0185,0.0225,0.0210,0.0154},
    {0.0110,0.0070,0.0095,0.0085,0.0105,0.0110,0.0090},
    },
    {//107
    {0.0130,0.0130,0.0130,0.0120,0.0080,0.0050,0.0090},
    {0.0155,0.0145,0.0140,0.0130,0.0140,0.0080,0.0164},
    {0.0290,0.0280,0.0280,0.0270,0.0210,0.0260,0.0250},
    {0.0280,0.0280,0.0280,0.0280,0.0210,0.0250,0.0230},
    {0.0155,0.0140,0.0145,0.0181,0.0120,0.0130,0.0115},
    {0.0110,0.0110,0.0110,0.0100,0.0055,0.0045,0.0090},
    }
    },

    {//morino220905
    {//103
    {0.0088,0.0090,0.0087,0.0103,0.0088,0.0077,0.0090},
    {0.0123,0.0150,0.0135,0.0165,0.0093,0.0090,0.0154},
    {0.0155,0.0175,0.0135,0.0175,0.0060,0.0075,0.0134},
    {0.0137,0.0174,0.0207,0.0165,0.0062,0.0076,0.0131},
    {0.0107,0.0133,0.0155,0.0143,0.0087,0.0097,0.0144},
    {0.0074,0.0078,0.0083,0.0106,0.0085,0.0081,0.0090},
    },
    {//104
    {0.0100,0.0076,0.0072,0.0074,0.0074,0.0069,0.0090},
    {0.0142,0.0123,0.0127,0.0119,0.0122,0.0112,0.0154},
    {0.0217,0.0177,0.0160,0.0146,0.0210,0.0256,0.0178},
    {0.0212,0.0185,0.0162,0.0138,0.0205,0.0243,0.0185},
    {0.0134,0.0129,0.0128,0.0114,0.0110,0.0106,0.0146},
    {0.0095,0.0077,0.0070,0.0067,0.0076,0.0076,0.0090},
    },
    {//
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    {1.,1.,1.,1.,1.,1.,1.},
    },
    {//106
    {0.0078,0.0083,0.0071,0.0069,0.0068,0.0088,0.0090},
    {0.0125,0.0125,0.0112,0.0113,0.0106,0.0133,0.0154},
    {0.0162,0.0223,0.0209,0.0202,0.0210,0.0196,0.0225},
    {0.0180,0.0200,0.0215,0.0209,0.0195,0.0196,0.0200},
    {0.0116,0.0112,0.0114,0.0117,0.0098,0.0133,0.0154},
    {0.0087,0.0076,0.0070,0.0072,0.0066,0.0080,0.0090},
    },
    {//107
    {0.0062,0.0060,0.0089,0.0080,0.0077,0.0070,0.0090},
    {0.0078,0.0062,0.0088,0.0094,0.0121,0.0113,0.0164},
    {0.0127,0.0140,0.0181,0.0193,0.0187,0.0148,0.0094},
    {0.0120,0.0088,0.0140,0.0240,0.0208,0.0174,0.0091},
    {0.0094,0.0063,0.0101,0.0134,0.0107,0.0096,0.0164},
    {0.0071,0.0067,0.0072,0.0072,0.0074,0.0075,0.0090},
    }
    },

    {//nakasuga, sim
    {//103
      {0.826598,0.851196,0.875794,0.900391,0.924989,0.949587,0.974185,},
      {0.826598,0.851196,0.875794,0.900391,0.924989,0.949587,0.974185,},
      {0.826598,0.851196,0.875794,0.900391,0.924989,0.949587,0.974185,},
      {0.826598,0.851196,0.875794,0.900391,0.924989,0.949587,0.974185,},
      {0.826598,0.851196,0.875794,0.900391,0.924989,0.949587,0.974185,},
      {0.826598,0.851196,0.875794,0.900391,0.924989,0.949587,0.974185,},
    },
    {//104
      {0.98885,1.04373,1.0986,1.15348,1.20836,1.26323,1.31811,},
      {0.98885,1.04373,1.0986,1.15348,1.20836,1.26323,1.31811,},
      {0.98885,1.04373,1.0986,1.15348,1.20836,1.26323,1.31811,},
      {0.98885,1.04373,1.0986,1.15348,1.20836,1.26323,1.31811,},
      {0.98885,1.04373,1.0986,1.15348,1.20836,1.26323,1.31811,},
      {0.98885,1.04373,1.0986,1.15348,1.20836,1.26323,1.31811,},
    },
    {//
      {1.,1.,1.,1.,1.,1.,1.},
      {1.,1.,1.,1.,1.,1.,1.},
      {1.,1.,1.,1.,1.,1.,1.},
      {1.,1.,1.,1.,1.,1.,1.},
      {1.,1.,1.,1.,1.,1.,1.},
      {1.,1.,1.,1.,1.,1.,1.},
    },
    {//106
      {1.28353,1.22499,1.16645,1.10791,1.04937,0.99083,0.932289,},
      {1.28353,1.22499,1.16645,1.10791,1.04937,0.99083,0.932289,},
      {1.28353,1.22499,1.16645,1.10791,1.04937,0.99083,0.932289,},
      {1.28353,1.22499,1.16645,1.10791,1.04937,0.99083,0.932289,},
      {1.28353,1.22499,1.16645,1.10791,1.04937,0.99083,0.932289,},
      {1.28353,1.22499,1.16645,1.10791,1.04937,0.99083,0.932289,},
    },
    {//107
      {0.947466,0.924747,0.902027,0.879308,0.856589,0.833869,0.81115,},
      {0.947466,0.924747,0.902027,0.879308,0.856589,0.833869,0.81115,},
      {0.947466,0.924747,0.902027,0.879308,0.856589,0.833869,0.81115,},
      {0.947466,0.924747,0.902027,0.879308,0.856589,0.833869,0.81115,},
      {0.947466,0.924747,0.902027,0.879308,0.856589,0.833869,0.81115,},
      {0.947466,0.924747,0.902027,0.879308,0.856589,0.833869,0.81115,},
    }
    }

  };


   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           run_id;
   Int_t           event_id;
   Int_t           spill_id;
   Int_t           n_tracks;
   vector<int>     *track_id;
   vector<double>  *chi_square;
   vector<int>     *rk_charge;
   vector<int>     *is_selected;
   vector<double>  *track_mom;
   vector<double>  *track_mom_x;
   vector<double>  *track_mom_y;
   vector<double>  *track_mom_z;
   vector<double>  *track_tgt_dist;
   vector<int>  *track_tgt_id;
   vector<double>  *track_lg_pi_eff1;
   vector<double>  *track_lg_pi_eff2;
   vector<double>  *track_angle_lx;
   vector<double>  *track_angle_ly;
   vector<double>  *track_position_block_lx;
   vector<double>  *track_position_block_ly;
   vector<double>  *track_ssd_t;
   vector<double>  *track_ssd_adc;
   vector<double>  *track_gtr100x_t;
   vector<double>  *track_gtr100x_adc;
   vector<double>  *track_gtr100y_t;
   vector<double>  *track_gtr100y_adc;
   vector<double>  *track_gtr200x_t;
   vector<double>  *track_gtr200x_adc;
   vector<double>  *track_gtr200y_t;
   vector<double>  *track_gtr200y_adc;
   vector<double>  *track_gtr300x_t;
   vector<double>  *track_gtr300x_adc;
   vector<double>  *track_gtr300y_t;
   vector<double>  *track_gtr300y_adc;
   vector<bool>    *track_w_trg_bias;
   vector<bool>    *track_w_trg_gtr;
   vector<bool>    *track_w_trg_hbd;
   vector<int>     *track_w_trg_lg;
   vector<bool>    *track_w_trg_trk;
   vector<double>  *track_select_hbd_resx;
   vector<double>  *track_select_hbd_adc;
   vector<int>     *track_select_gtr_nass;
   vector<double>  *track_select_gtr100y_res;
   vector<double>  *track_select_gtr200y_res;
   vector<double>  *track_select_gtr300y_res;
   vector<double>  *track_select_gtr_chisq;
   vector<int>     *track_hbd_mid;
   vector<double>  *track_hbd_lx;
   vector<double>  *track_hbd_ly;
   vector<double>  *track_hbd_nearx;
   vector<double>  *track_hbd_neary;
   vector<int>     *track_hbd_multiplicity;
   vector<double>  *track_hbd_dum_nearx;
   vector<double>  *track_hbd_dum_neary;
   vector<int>     *track_hbd_dum_multiplicity;
   vector<int>     *track_lg_mid;
   vector<double>  *track_lg_lx;
   vector<double>  *track_lg_ly;
   vector<int>     *track_lg_blockch;
   vector<double>  *track_lg_nearx;
   vector<double>  *track_lg_neary;
   vector<int>     *track_lg_multiplicity;
   vector<double>  *track_lg_dum_nearx;
   vector<double>  *track_lg_dum_neary;
   vector<int>     *track_lg_dum_multiplicity;
   vector<double>  *track_lg_cl_nearx;
   vector<double>  *track_lg_cl_neary;
   vector<int>     *track_lg_cl_multiplicity;
   vector<double>  *track_lg_cl_dum_nearx;
   vector<double>  *track_lg_cl_dum_neary;
   vector<int>     *track_lg_cl_dum_multiplicity;
   vector<vector<double> > *track_hbd_allhit_resx;
   vector<vector<double> > *track_hbd_allhit_resy;
   vector<vector<double> > *track_hbd_allhit_ftime;
   vector<vector<double> > *track_hbd_allhit_adc;
   vector<vector<double> > *track_hbd_allhit_size;
   vector<vector<double> > *track_hbd_allhit_eprob;
   vector<vector<double> > *track_hbd_allhit_cprob;
   vector<vector<double> > *track_hbd_allhit_dum_resx;
   vector<vector<double> > *track_hbd_allhit_dum_resy;
   vector<vector<double> > *track_hbd_allhit_dum_ftime;
   vector<vector<double> > *track_hbd_allhit_dum_adc;
   vector<vector<double> > *track_hbd_allhit_dum_size;
   vector<vector<double> > *track_hbd_allhit_dum_eprob;
   vector<vector<double> > *track_hbd_allhit_dum_cprob;
   vector<vector<double> > *track_lg_allhit_resx;
   vector<vector<double> > *track_lg_allhit_resy;
   vector<vector<double> > *track_lg_allhit_ftime;
   vector<vector<double> > *track_lg_allhit_adc;
   vector<vector<double> > *track_lg_allhit_trgt;
   vector<vector<double> > *track_lg_allhit_dum_resx;
   vector<vector<double> > *track_lg_allhit_dum_resy;
   vector<vector<double> > *track_lg_allhit_dum_ftime;
   vector<vector<double> > *track_lg_allhit_dum_adc;
   vector<vector<double> > *track_lg_cl_allhit_resx;
   vector<vector<double> > *track_lg_cl_allhit_resy;
   vector<vector<double> > *track_lg_cl_allhit_ftime;
   vector<vector<double> > *track_lg_cl_allhit_adc;
   vector<vector<double> > *track_lg_cl_allhit_maxpeak;
   vector<vector<double> > *track_lg_cl_allhit_maxcid;
   vector<vector<double> > *track_lg_cl_allhit_dum_resx;
   vector<vector<double> > *track_lg_cl_allhit_dum_resy;
   vector<vector<double> > *track_lg_cl_allhit_dum_ftime;
   vector<vector<double> > *track_lg_cl_allhit_dum_adc;
   vector<vector<double> > *track_lg_cl_allhit_dum_maxpeak;
   vector<vector<double> > *track_lg_cl_allhit_dum_maxcid;

   // List of branches
   TBranch        *b_run_id;   //!
   TBranch        *b_event_id;   //!
   TBranch        *b_spill_id;   //!
   TBranch        *b_n_tracks;   //!
   TBranch        *b_track_id;   //!
   TBranch        *b_chi_square;   //!
   TBranch        *b_rk_charge;   //!
   TBranch        *b_is_selected;   //!
   TBranch        *b_track_mom;   //!
   TBranch        *b_track_mom_x;   //!
   TBranch        *b_track_mom_y;   //!
   TBranch        *b_track_mom_z;   //!
   TBranch        *b_track_tgt_dist;   //!
   TBranch        *b_track_tgt_id;   //!
   TBranch        *b_track_lg_pi_eff1;   //!
   TBranch        *b_track_lg_pi_eff2;   //!
   TBranch        *b_track_angle_lx;   //!
   TBranch        *b_track_angle_ly;   //!
   TBranch        *b_track_position_block_lx;   //!
   TBranch        *b_track_position_block_ly;   //!
   TBranch        *b_track_ssd_t;   //!
   TBranch        *b_track_ssd_adc;   //!
   TBranch        *b_track_gtr100x_t;   //!
   TBranch        *b_track_gtr100x_adc;   //!
   TBranch        *b_track_gtr100y_t;   //!
   TBranch        *b_track_gtr100y_adc;   //!
   TBranch        *b_track_gtr200x_t;   //!
   TBranch        *b_track_gtr200x_adc;   //!
   TBranch        *b_track_gtr200y_t;   //!
   TBranch        *b_track_gtr200y_adc;   //!
   TBranch        *b_track_gtr300x_t;   //!
   TBranch        *b_track_gtr300x_adc;   //!
   TBranch        *b_track_gtr300y_t;   //!
   TBranch        *b_track_gtr300y_adc;   //!
   TBranch        *b_track_w_trg_bias;   //!
   TBranch        *b_track_w_trg_gtr;   //!
   TBranch        *b_track_w_trg_hbd;   //!
   TBranch        *b_track_w_trg_lg;   //!
   TBranch        *b_track_w_trg_trk;   //!
   TBranch        *b_track_select_hbd_resx;   //!
   TBranch        *b_track_select_hbd_adc;   //!
   TBranch        *b_track_select_gtr_nass;   //!
   TBranch        *b_track_select_gtr100y_res;   //!
   TBranch        *b_track_select_gtr200y_res;   //!
   TBranch        *b_track_select_gtr300y_res;   //!
   TBranch        *b_track_select_gtr_chisq;   //!
   TBranch        *b_track_hbd_mid;   //!
   TBranch        *b_track_hbd_lx;   //!
   TBranch        *b_track_hbd_ly;   //!
   TBranch        *b_track_hbd_nearx;   //!
   TBranch        *b_track_hbd_neary;   //!
   TBranch        *b_track_hbd_multiplicity;   //!
   TBranch        *b_track_hbd_dum_nearx;   //!
   TBranch        *b_track_hbd_dum_neary;   //!
   TBranch        *b_track_hbd_dum_multiplicity;   //!
   TBranch        *b_track_lg_mid;   //!
   TBranch        *b_track_lg_lx;   //!
   TBranch        *b_track_lg_ly;   //!
   TBranch        *b_track_lg_blockch;   //!
   TBranch        *b_track_lg_nearx;   //!
   TBranch        *b_track_lg_neary;   //!
   TBranch        *b_track_lg_multiplicity;   //!
   TBranch        *b_track_lg_dum_nearx;   //!
   TBranch        *b_track_lg_dum_neary;   //!
   TBranch        *b_track_lg_dum_multiplicity;   //!
   TBranch        *b_track_lg_cl_nearx;   //!
   TBranch        *b_track_lg_cl_neary;   //!
   TBranch        *b_track_lg_cl_multiplicity;   //!
   TBranch        *b_track_lg_cl_dum_nearx;   //!
   TBranch        *b_track_lg_cl_dum_neary;   //!
   TBranch        *b_track_lg_cl_dum_multiplicity;   //!
   TBranch        *b_track_hbd_allhit_resx;   //!
   TBranch        *b_track_hbd_allhit_resy;   //!
   TBranch        *b_track_hbd_allhit_ftime;   //!
   TBranch        *b_track_hbd_allhit_adc;   //!
   TBranch        *b_track_hbd_allhit_size;   //!
   TBranch        *b_track_hbd_allhit_eprob;   //!
   TBranch        *b_track_hbd_allhit_cprob;   //!
   TBranch        *b_track_hbd_allhit_dum_resx;   //!
   TBranch        *b_track_hbd_allhit_dum_resy;   //!
   TBranch        *b_track_hbd_allhit_dum_ftime;   //!
   TBranch        *b_track_hbd_allhit_dum_adc;   //!
   TBranch        *b_track_hbd_allhit_dum_size;   //!
   TBranch        *b_track_hbd_allhit_dum_eprob;   //!
   TBranch        *b_track_hbd_allhit_dum_cprob;   //!
   TBranch        *b_track_lg_allhit_resx;   //!
   TBranch        *b_track_lg_allhit_resy;   //!
   TBranch        *b_track_lg_allhit_ftime;   //!
   TBranch        *b_track_lg_allhit_adc;   //!
   TBranch        *b_track_lg_allhit_trgt;   //!
   TBranch        *b_track_lg_allhit_dum_resx;   //!
   TBranch        *b_track_lg_allhit_dum_resy;   //!
   TBranch        *b_track_lg_allhit_dum_ftime;   //!
   TBranch        *b_track_lg_allhit_dum_adc;   //!
   TBranch        *b_track_lg_cl_allhit_resx;   //!
   TBranch        *b_track_lg_cl_allhit_resy;   //!
   TBranch        *b_track_lg_cl_allhit_ftime;   //!
   TBranch        *b_track_lg_cl_allhit_adc;   //!
   TBranch        *b_track_lg_cl_allhit_maxpeak;   //!
   TBranch        *b_track_lg_cl_allhit_maxcid;   //!
   TBranch        *b_track_lg_cl_allhit_dum_resx;   //!
   TBranch        *b_track_lg_cl_allhit_dum_resy;   //!
   TBranch        *b_track_lg_cl_allhit_dum_ftime;   //!
   TBranch        *b_track_lg_cl_allhit_dum_adc;   //!
   TBranch        *b_track_lg_cl_allhit_dum_maxpeak;   //!
   TBranch        *b_track_lg_cl_allhit_dum_maxcid;   //!

   AnalyzerTrackSelection(TTree *tree=0);
   virtual ~AnalyzerTrackSelection();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    SelectGoodTrack(Long64_t entry, std::vector<int>& goodtracks, double* hbd_voriginx, double* hbd_voriginy, double* hbd_vsigmax, double* hbd_vsigmay);
   virtual Int_t    CutOfTrack(Long64_t entry, int itrack, std::vector<int>& goodtracks);
   virtual Int_t    CutOfTrack(Long64_t entry, int itrack, int runoption );
   virtual Int_t    CutOfTrack(Long64_t entry, int itrack );
   virtual Int_t    IsGoodTrack(Long64_t entry, int itrack, std::vector<trackset> &tracksets);
   virtual Int_t    IsGoodTrackWHBD(Long64_t entry, int itrack, std::vector<trackset> &tracksets, double hbdadc);
   virtual Int_t    RunPurpose(int run_id);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual double   CalcADCNearHit(int condition, std::vector<hitset>& lgnear, double ssdt, lgcls& lgcluster);
   // virtual double   CalcMaxADCNearHit(std::vector<hitset>& lgnear, double ssdt);
   // virtual double   CalcSumADCNearHit(std::vector<hitset>& lgnear, double ssdt);
   virtual void     Loop();
   virtual void     DrawForResidualHBD(int runtype, int maxevent, char* out_file_name);
   virtual void     DrawForTrackSelection(int runtype, int maxevent, char* out_file_name);
   virtual void     DrawForLGEfficiency(int runtype, int maxevent, char* out_file_name, char* out_root_name, double hbdthr, int hbdclthr);
   virtual void     DrawForLGRejection(int runtype, int maxevent, char* out_file_name, char* out_root_name, int hbdoptype);
   virtual void     GainCalib(int runtype, int maxevent, char* out_file_name, char* out_root_name);
   // virtual void     MkMixingHist(int runoption, int maxevent);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef AnalyzerTrackSelection_cxx
AnalyzerTrackSelection::AnalyzerTrackSelection(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("out/root03a/trackselection_chisq30_unlinklg.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("out/root03a/trackselection_chisq30_unlinklg.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

AnalyzerTrackSelection::~AnalyzerTrackSelection()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t AnalyzerTrackSelection::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t AnalyzerTrackSelection::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void AnalyzerTrackSelection::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   track_id = 0;
   chi_square = 0;
   rk_charge = 0;
   is_selected = 0;
   track_mom = 0;
   track_mom_x = 0;
   track_mom_y = 0;
   track_mom_z = 0;
   track_tgt_dist = 0;
   track_tgt_id = 0;
   track_lg_pi_eff1 = 0;
   track_lg_pi_eff2 = 0;
   track_angle_lx = 0;
   track_angle_ly = 0;
   track_position_block_lx = 0;
   track_position_block_ly = 0;
   track_ssd_t = 0;
   track_ssd_adc = 0;
   track_gtr100x_t = 0;
   track_gtr100x_adc = 0;
   track_gtr100y_t = 0;
   track_gtr100y_adc = 0;
   track_gtr200x_t = 0;
   track_gtr200x_adc = 0;
   track_gtr200y_t = 0;
   track_gtr200y_adc = 0;
   track_gtr300x_t = 0;
   track_gtr300x_adc = 0;
   track_gtr300y_t = 0;
   track_gtr300y_adc = 0;
   track_w_trg_bias = 0;
   track_w_trg_gtr = 0;
   track_w_trg_hbd = 0;
   track_w_trg_lg = 0;
   track_w_trg_trk = 0;
   track_select_hbd_resx = 0;
   track_select_hbd_adc = 0;
   track_select_gtr_nass = 0;
   track_select_gtr100y_res = 0;
   track_select_gtr200y_res = 0;
   track_select_gtr300y_res = 0;
   track_select_gtr_chisq = 0;
   track_hbd_mid = 0;
   track_hbd_lx = 0;
   track_hbd_ly = 0;
   track_hbd_nearx = 0;
   track_hbd_neary = 0;
   track_hbd_multiplicity = 0;
   track_hbd_dum_nearx = 0;
   track_hbd_dum_neary = 0;
   track_hbd_dum_multiplicity = 0;
   track_lg_mid = 0;
   track_lg_lx = 0;
   track_lg_ly = 0;
   track_lg_blockch = 0;
   track_lg_nearx = 0;
   track_lg_neary = 0;
   track_lg_multiplicity = 0;
   track_lg_dum_nearx = 0;
   track_lg_dum_neary = 0;
   track_lg_dum_multiplicity = 0;
   track_lg_cl_nearx = 0;
   track_lg_cl_neary = 0;
   track_lg_cl_multiplicity = 0;
   track_lg_cl_dum_nearx = 0;
   track_lg_cl_dum_neary = 0;
   track_lg_cl_dum_multiplicity = 0;
   track_hbd_allhit_resx = 0;
   track_hbd_allhit_resy = 0;
   track_hbd_allhit_ftime = 0;
   track_hbd_allhit_adc = 0;
   track_hbd_allhit_size = 0;
   track_hbd_allhit_eprob = 0;
   track_hbd_allhit_cprob = 0;
   track_hbd_allhit_dum_resx = 0;
   track_hbd_allhit_dum_resy = 0;
   track_hbd_allhit_dum_ftime = 0;
   track_hbd_allhit_dum_adc = 0;
   track_hbd_allhit_dum_size = 0;
   track_hbd_allhit_dum_eprob = 0;
   track_hbd_allhit_dum_cprob = 0;
   track_lg_allhit_resx = 0;
   track_lg_allhit_resy = 0;
   track_lg_allhit_ftime = 0;
   track_lg_allhit_adc = 0;
   track_lg_allhit_trgt = 0;
   track_lg_allhit_dum_resx = 0;
   track_lg_allhit_dum_resy = 0;
   track_lg_allhit_dum_ftime = 0;
   track_lg_allhit_dum_adc = 0;
   track_lg_cl_allhit_resx = 0;
   track_lg_cl_allhit_resy = 0;
   track_lg_cl_allhit_ftime = 0;
   track_lg_cl_allhit_adc = 0;
   track_lg_cl_allhit_maxpeak = 0;
   track_lg_cl_allhit_maxcid = 0;
   track_lg_cl_allhit_dum_resx = 0;
   track_lg_cl_allhit_dum_resy = 0;
   track_lg_cl_allhit_dum_ftime = 0;
   track_lg_cl_allhit_dum_adc = 0;
   track_lg_cl_allhit_dum_maxpeak = 0;
   track_lg_cl_allhit_dum_maxcid = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run_id", &run_id, &b_run_id);
   fChain->SetBranchAddress("event_id", &event_id, &b_event_id);
   fChain->SetBranchAddress("spill_id", &spill_id, &b_spill_id);
   fChain->SetBranchAddress("n_tracks", &n_tracks, &b_n_tracks);
   fChain->SetBranchAddress("track_id", &track_id, &b_track_id);
   fChain->SetBranchAddress("chi_square", &chi_square, &b_chi_square);
   fChain->SetBranchAddress("rk_charge", &rk_charge, &b_rk_charge);
   fChain->SetBranchAddress("is_selected", &is_selected, &b_is_selected);
   fChain->SetBranchAddress("track_mom", &track_mom, &b_track_mom);
   fChain->SetBranchAddress("track_mom_x", &track_mom_x, &b_track_mom_x);
   fChain->SetBranchAddress("track_mom_y", &track_mom_y, &b_track_mom_y);
   fChain->SetBranchAddress("track_mom_z", &track_mom_z, &b_track_mom_z);
   fChain->SetBranchAddress("track_tgt_dist", &track_tgt_dist, &b_track_tgt_dist);
   fChain->SetBranchAddress("track_tgt_id", &track_tgt_id, &b_track_tgt_id);
   fChain->SetBranchAddress("track_lg_pi_eff1", &track_lg_pi_eff1, &b_track_lg_pi_eff1);
   fChain->SetBranchAddress("track_lg_pi_eff2", &track_lg_pi_eff2, &b_track_lg_pi_eff2);
   fChain->SetBranchAddress("track_angle_lx", &track_angle_lx, &b_track_angle_lx);
   fChain->SetBranchAddress("track_angle_ly", &track_angle_ly, &b_track_angle_ly);
   fChain->SetBranchAddress("track_position_block_lx", &track_position_block_lx, &b_track_position_block_lx);
   fChain->SetBranchAddress("track_position_block_ly", &track_position_block_ly, &b_track_position_block_ly);
   fChain->SetBranchAddress("track_ssd_t", &track_ssd_t, &b_track_ssd_t);
   fChain->SetBranchAddress("track_ssd_adc", &track_ssd_adc, &b_track_ssd_adc);
   fChain->SetBranchAddress("track_gtr100x_t", &track_gtr100x_t, &b_track_gtr100x_t);
   fChain->SetBranchAddress("track_gtr100x_adc", &track_gtr100x_adc, &b_track_gtr100x_adc);
   fChain->SetBranchAddress("track_gtr100y_t", &track_gtr100y_t, &b_track_gtr100y_t);
   fChain->SetBranchAddress("track_gtr100y_adc", &track_gtr100y_adc, &b_track_gtr100y_adc);
   fChain->SetBranchAddress("track_gtr200x_t", &track_gtr200x_t, &b_track_gtr200x_t);
   fChain->SetBranchAddress("track_gtr200x_adc", &track_gtr200x_adc, &b_track_gtr200x_adc);
   fChain->SetBranchAddress("track_gtr200y_t", &track_gtr200y_t, &b_track_gtr200y_t);
   fChain->SetBranchAddress("track_gtr200y_adc", &track_gtr200y_adc, &b_track_gtr200y_adc);
   fChain->SetBranchAddress("track_gtr300x_t", &track_gtr300x_t, &b_track_gtr300x_t);
   fChain->SetBranchAddress("track_gtr300x_adc", &track_gtr300x_adc, &b_track_gtr300x_adc);
   fChain->SetBranchAddress("track_gtr300y_t", &track_gtr300y_t, &b_track_gtr300y_t);
   fChain->SetBranchAddress("track_gtr300y_adc", &track_gtr300y_adc, &b_track_gtr300y_adc);
   fChain->SetBranchAddress("track_w_trg_bias", &track_w_trg_bias, &b_track_w_trg_bias);
   fChain->SetBranchAddress("track_w_trg_gtr", &track_w_trg_gtr, &b_track_w_trg_gtr);
   fChain->SetBranchAddress("track_w_trg_hbd", &track_w_trg_hbd, &b_track_w_trg_hbd);
   fChain->SetBranchAddress("track_w_trg_lg", &track_w_trg_lg, &b_track_w_trg_lg);
   fChain->SetBranchAddress("track_w_trg_trk", &track_w_trg_trk, &b_track_w_trg_trk);
   fChain->SetBranchAddress("track_select_hbd_resx", &track_select_hbd_resx, &b_track_select_hbd_resx);
   fChain->SetBranchAddress("track_select_hbd_adc", &track_select_hbd_adc, &b_track_select_hbd_adc);
   fChain->SetBranchAddress("track_select_gtr_nass", &track_select_gtr_nass, &b_track_select_gtr_nass);
   fChain->SetBranchAddress("track_select_gtr100y_res", &track_select_gtr100y_res, &b_track_select_gtr100y_res);
   fChain->SetBranchAddress("track_select_gtr200y_res", &track_select_gtr200y_res, &b_track_select_gtr200y_res);
   fChain->SetBranchAddress("track_select_gtr300y_res", &track_select_gtr300y_res, &b_track_select_gtr300y_res);
   fChain->SetBranchAddress("track_select_gtr_chisq", &track_select_gtr_chisq, &b_track_select_gtr_chisq);
   fChain->SetBranchAddress("track_hbd_mid", &track_hbd_mid, &b_track_hbd_mid);
   fChain->SetBranchAddress("track_hbd_lx", &track_hbd_lx, &b_track_hbd_lx);
   fChain->SetBranchAddress("track_hbd_ly", &track_hbd_ly, &b_track_hbd_ly);
   fChain->SetBranchAddress("track_hbd_nearx", &track_hbd_nearx, &b_track_hbd_nearx);
   fChain->SetBranchAddress("track_hbd_neary", &track_hbd_neary, &b_track_hbd_neary);
   fChain->SetBranchAddress("track_hbd_multiplicity", &track_hbd_multiplicity, &b_track_hbd_multiplicity);
   fChain->SetBranchAddress("track_hbd_dum_nearx", &track_hbd_dum_nearx, &b_track_hbd_dum_nearx);
   fChain->SetBranchAddress("track_hbd_dum_neary", &track_hbd_dum_neary, &b_track_hbd_dum_neary);
   fChain->SetBranchAddress("track_hbd_dum_multiplicity", &track_hbd_dum_multiplicity, &b_track_hbd_dum_multiplicity);
   fChain->SetBranchAddress("track_lg_mid", &track_lg_mid, &b_track_lg_mid);
   fChain->SetBranchAddress("track_lg_lx", &track_lg_lx, &b_track_lg_lx);
   fChain->SetBranchAddress("track_lg_ly", &track_lg_ly, &b_track_lg_ly);
   fChain->SetBranchAddress("track_lg_blockch", &track_lg_blockch, &b_track_lg_blockch);
   fChain->SetBranchAddress("track_lg_nearx", &track_lg_nearx, &b_track_lg_nearx);
   fChain->SetBranchAddress("track_lg_neary", &track_lg_neary, &b_track_lg_neary);
   fChain->SetBranchAddress("track_lg_multiplicity", &track_lg_multiplicity, &b_track_lg_multiplicity);
   fChain->SetBranchAddress("track_lg_dum_nearx", &track_lg_dum_nearx, &b_track_lg_dum_nearx);
   fChain->SetBranchAddress("track_lg_dum_neary", &track_lg_dum_neary, &b_track_lg_dum_neary);
   fChain->SetBranchAddress("track_lg_dum_multiplicity", &track_lg_dum_multiplicity, &b_track_lg_dum_multiplicity);
   fChain->SetBranchAddress("track_lg_cl_nearx", &track_lg_cl_nearx, &b_track_lg_cl_nearx);
   fChain->SetBranchAddress("track_lg_cl_neary", &track_lg_cl_neary, &b_track_lg_cl_neary);
   fChain->SetBranchAddress("track_lg_cl_multiplicity", &track_lg_cl_multiplicity, &b_track_lg_cl_multiplicity);
   fChain->SetBranchAddress("track_lg_cl_dum_nearx", &track_lg_cl_dum_nearx, &b_track_lg_cl_dum_nearx);
   fChain->SetBranchAddress("track_lg_cl_dum_neary", &track_lg_cl_dum_neary, &b_track_lg_cl_dum_neary);
   fChain->SetBranchAddress("track_lg_cl_dum_multiplicity", &track_lg_cl_dum_multiplicity, &b_track_lg_cl_dum_multiplicity);
   fChain->SetBranchAddress("track_hbd_allhit_resx", &track_hbd_allhit_resx, &b_track_hbd_allhit_resx);
   fChain->SetBranchAddress("track_hbd_allhit_resy", &track_hbd_allhit_resy, &b_track_hbd_allhit_resy);
   fChain->SetBranchAddress("track_hbd_allhit_ftime", &track_hbd_allhit_ftime, &b_track_hbd_allhit_ftime);
   fChain->SetBranchAddress("track_hbd_allhit_adc", &track_hbd_allhit_adc, &b_track_hbd_allhit_adc);
   fChain->SetBranchAddress("track_lg_allhit_trgt", &track_lg_allhit_trgt, &b_track_lg_allhit_trgt);
   fChain->SetBranchAddress("track_hbd_allhit_size", &track_hbd_allhit_size, &b_track_hbd_allhit_size);
   fChain->SetBranchAddress("track_hbd_allhit_eprob", &track_hbd_allhit_eprob, &b_track_hbd_allhit_eprob);
   fChain->SetBranchAddress("track_hbd_allhit_cprob", &track_hbd_allhit_cprob, &b_track_hbd_allhit_cprob);
   fChain->SetBranchAddress("track_hbd_allhit_dum_resx", &track_hbd_allhit_dum_resx, &b_track_hbd_allhit_dum_resx);
   fChain->SetBranchAddress("track_hbd_allhit_dum_resy", &track_hbd_allhit_dum_resy, &b_track_hbd_allhit_dum_resy);
   fChain->SetBranchAddress("track_hbd_allhit_dum_ftime", &track_hbd_allhit_dum_ftime, &b_track_hbd_allhit_dum_ftime);
   fChain->SetBranchAddress("track_hbd_allhit_dum_adc", &track_hbd_allhit_dum_adc, &b_track_hbd_allhit_dum_adc);
   fChain->SetBranchAddress("track_hbd_allhit_dum_size", &track_hbd_allhit_dum_size, &b_track_hbd_allhit_dum_size);
   fChain->SetBranchAddress("track_hbd_allhit_dum_eprob", &track_hbd_allhit_dum_eprob, &b_track_hbd_allhit_dum_eprob);
   fChain->SetBranchAddress("track_hbd_allhit_dum_cprob", &track_hbd_allhit_dum_cprob, &b_track_hbd_allhit_dum_cprob);
   fChain->SetBranchAddress("track_lg_allhit_resx", &track_lg_allhit_resx, &b_track_lg_allhit_resx);
   fChain->SetBranchAddress("track_lg_allhit_resy", &track_lg_allhit_resy, &b_track_lg_allhit_resy);
   fChain->SetBranchAddress("track_lg_allhit_ftime", &track_lg_allhit_ftime, &b_track_lg_allhit_ftime);
   fChain->SetBranchAddress("track_lg_allhit_adc", &track_lg_allhit_adc, &b_track_lg_allhit_adc);
   fChain->SetBranchAddress("track_lg_allhit_dum_resx", &track_lg_allhit_dum_resx, &b_track_lg_allhit_dum_resx);
   fChain->SetBranchAddress("track_lg_allhit_dum_resy", &track_lg_allhit_dum_resy, &b_track_lg_allhit_dum_resy);
   fChain->SetBranchAddress("track_lg_allhit_dum_ftime", &track_lg_allhit_dum_ftime, &b_track_lg_allhit_dum_ftime);
   fChain->SetBranchAddress("track_lg_allhit_dum_adc", &track_lg_allhit_dum_adc, &b_track_lg_allhit_dum_adc);
   fChain->SetBranchAddress("track_lg_cl_allhit_resx", &track_lg_cl_allhit_resx, &b_track_lg_cl_allhit_resx);
   fChain->SetBranchAddress("track_lg_cl_allhit_resy", &track_lg_cl_allhit_resy, &b_track_lg_cl_allhit_resy);
   fChain->SetBranchAddress("track_lg_cl_allhit_ftime", &track_lg_cl_allhit_ftime, &b_track_lg_cl_allhit_ftime);
   fChain->SetBranchAddress("track_lg_cl_allhit_adc", &track_lg_cl_allhit_adc, &b_track_lg_cl_allhit_adc);
   fChain->SetBranchAddress("track_lg_cl_allhit_maxpeak", &track_lg_cl_allhit_maxpeak, &b_track_lg_cl_allhit_maxpeak);
   fChain->SetBranchAddress("track_lg_cl_allhit_maxcid", &track_lg_cl_allhit_maxcid, &b_track_lg_cl_allhit_maxcid);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_resx", &track_lg_cl_allhit_dum_resx, &b_track_lg_cl_allhit_dum_resx);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_resy", &track_lg_cl_allhit_dum_resy, &b_track_lg_cl_allhit_dum_resy);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_ftime", &track_lg_cl_allhit_dum_ftime, &b_track_lg_cl_allhit_dum_ftime);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_adc", &track_lg_cl_allhit_dum_adc, &b_track_lg_cl_allhit_dum_adc);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_maxpeak", &track_lg_cl_allhit_dum_maxpeak, &b_track_lg_cl_allhit_dum_maxpeak);
   fChain->SetBranchAddress("track_lg_cl_allhit_dum_maxcid", &track_lg_cl_allhit_dum_maxcid, &b_track_lg_cl_allhit_dum_maxcid);
   Notify();
}

Bool_t AnalyzerTrackSelection::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void AnalyzerTrackSelection::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t AnalyzerTrackSelection::Cut(Long64_t entry)
{
  std::vector<int> goodtracks(1);
  double hbd_voriginx[4]={0.};
  double hbd_voriginy[4]={0.};
  double hbd_vsigmax[4]={25.,25.,25.,25.};
  double hbd_vsigmay[4]={25.,25.,25.,25.};
  return SelectGoodTrack(entry,goodtracks,hbd_voriginx,hbd_voriginy,hbd_vsigmax,hbd_vsigmay);
}
Int_t AnalyzerTrackSelection::SelectGoodTrack(Long64_t entry, std::vector<int>& goodtracks, double* hbd_voriginx, double* hbd_voriginy, double* hbd_vsigmax, double* hbd_vsigmay)
{
  if(goodtracks.size()==1){return 1;}
  else{

  struct set{
    int track_id;
    double chisq;
    double ssd;
    double gtr100x;
    double gtr100y;
    double gtr200x;
    double gtr200y;
    double gtr300x;
    double gtr300y;

    bool operator==(const set& another){
      if( ssd == another.ssd
    	|| gtr100x == another.gtr100x
    	|| gtr100y == another.gtr100y
    	|| gtr200x == another.gtr200x
    	|| gtr200y == another.gtr200y
    	|| gtr300x == another.gtr300x
    	|| gtr300y == another.gtr300y) return true;
      return false;
    }
  };

  std::vector<set> tracks(0);
  // std::cout<<n_tracks<<std::endl;
  //tracks are already sorted by chi_square in DST1
  for(int i=0;i<n_tracks;i++){ //track loop
    // if(CutOfTrack(entry,i)<0) continue;
    int trk_mid = track_hbd_mid->at(i);
    double rxt = track_hbd_nearx->at(i)-hbd_voriginx[(trk_mid-103+2)%5];
    double ryt = track_hbd_neary->at(i)-hbd_voriginy[(trk_mid-103+2)%5];
    if(track_hbd_mid->at(i)!=track_lg_mid->at(i)) continue;
    if( fabs(rxt)>hbd_vsigmax[(trk_mid-103+2)%5] || fabs(ryt)>hbd_vsigmay[(trk_mid-103+2)%5] ) continue;
    if(chi_square->at(i)>30.) continue;
    set settmp;
    settmp.track_id = track_id->at(i);
    settmp.chisq = chi_square->at(i);
    settmp.ssd = track_ssd_t->at(i);
    settmp.gtr100x = track_gtr100x_t->at(i);
    settmp.gtr100y = track_gtr100y_t->at(i);
    settmp.gtr200x = track_gtr200x_t->at(i);
    settmp.gtr200y = track_gtr200y_t->at(i);
    settmp.gtr300x = track_gtr300x_t->at(i);
    settmp.gtr300y = track_gtr300y_t->at(i);
    // std::cout<<settmp.chisq<<" "<<settmp.ssd<<" "<<settmp.gtr100x<<" "<<settmp.gtr100y<<" "<<settmp.gtr200x<<" "<<settmp.gtr200y<<" "<<settmp.gtr300x<<" "<<settmp.gtr300y<<std::endl;

    if(tracks.size()==0){
      tracks.push_back(settmp);
      goodtracks.push_back(settmp.track_id);
    }
    else{
      bool isgood = false;
      for(int j=0;j<tracks.size();j++){
	if(settmp==tracks.at(j)){
	  break;
	}
	if(j==tracks.size()-1){isgood=true;}
      }
      if(isgood==true){
	tracks.push_back(settmp);
	goodtracks.push_back(settmp.track_id);
      }
    }
  }//track loop

  // std::cout<<"************"<<tracks.size()<<" "<<goodtracks.size()<<std::endl;
  if(goodtracks.size()==0){return -1;}

  return 1;
  }
}
Int_t AnalyzerTrackSelection::CutOfTrack(Long64_t entry, int itrack, std::vector<int> &goodtracks)
{
  for(int i=0;i<goodtracks.size();i++){
    if(track_id->at(itrack)==goodtracks.at(i)){return 1;}
  }
  return -1;
}
Int_t AnalyzerTrackSelection::CutOfTrack(Long64_t entry, int itrack, int runoption)
{
  // int trk_mid = track_hbd_mid->at(itrack);
  // double rxt = track_hbd_nearx->at(itrack)-hbd_voriginx[(trk_mid-103+2)%5];
  // double ryt = track_hbd_neary->at(itrack)-hbd_voriginy[(trk_mid-103+2)%5];
  if(track_hbd_mid->at(itrack)!=track_lg_mid->at(itrack)) {return -1;}
  // if( fabs(rxt)>hbd_vsigmax[(trk_mid-103+2)%5] || fabs(ryt)>hbd_vsigmay[(trk_mid-103+2)%5] ) {return -1;}
  if(runoption==1&&chi_square->at(itrack)>20.) {return -1;}
  if(runoption==3&&chi_square->at(itrack)>10.) {return -1;}
  if(runoption==0&&chi_square->at(itrack)>10.) {return -1;}
  // if(track_w_trg_hbd->at(itrack)&&track_w_trg_gtr->at(itrack)&&track_w_trg_lg->at(itrack)>-1000) {return -1;}
  // if(fabs(track_position_block_lx->at(itrack))>30) {return -1;}
  // if(fabs(track_position_block_ly->at(itrack))>30) {return -1;}
  // if(track_ssd_t->at(itrack)<40.||track_ssd_t->at(itrack)>55.) {return -1;}
  // if (track_mom->at(itrack) > 3.) {return -1;}
  // if (track_mom->at(itrack) < 1.6) {return -1;}
  // if (track_mom->at(itrack) > 0.8) {return -1;}
  // if (track_mom->at(itrack) < 0.4) {return -1;}
  // if (rk_charge->at(itrack) != -1) {return -1;}
  // if (rk_charge->at(itrack)==1) {return -1;}
  // if (track_lg_mid->at(itrack)==104&&track_lg_lx->at(itrack)>280.&&track_lg_lx->at(itrack)<330.&&track_lg_ly->at(itrack)>-330.&&track_lg_ly->at(itrack)<-270.) {return -1;}
  if (track_tgt_dist->at(itrack)>20) {return -1;}
  // if (track_tgt_id->at(itrack)==0) {return -1;}
  // if (track_tgt_id->at(itrack)==2) {return -1;}

  // if ( track_ssd_t->at(itrack)<40 || track_ssd_t->at(itrack)>55 ) {return -1;}
  // if(run_id>20980) {return -1;}
  // if(chi_square->at(itrack)>5.) {return -1;}
  // if(is_selected->at(itrack)==0) {return -1;}
  // if(track_w_trg_bias->at(itrack)>-1000) {return -1;}
  // if(track_w_trg_bias->at(itrack)) {return -1;}
  else{
    return 1;
  }
}
Int_t AnalyzerTrackSelection::CutOfTrack(Long64_t entry, int itrack)
{
  int runoption = 1;
  return CutOfTrack(entry,itrack,runoption);

}
Int_t AnalyzerTrackSelection::IsGoodTrack(Long64_t entry, int itrack, std::vector<trackset> &tracksets)
{
  //tracks are already sorted by chi_square in DST1
  trackset settmp;
  settmp.track_id = track_id->at(itrack);
  settmp.chisq = chi_square->at(itrack);
  settmp.ssd = track_ssd_t->at(itrack);
  settmp.gtr100x = track_gtr100x_t->at(itrack);
  settmp.gtr100y = track_gtr100y_t->at(itrack);
  settmp.gtr200x = track_gtr200x_t->at(itrack);
  settmp.gtr200y = track_gtr200y_t->at(itrack);
  settmp.gtr300x = track_gtr300x_t->at(itrack);
  settmp.gtr300y = track_gtr300y_t->at(itrack);
  // std::cout<<settmp.chisq<<" "<<settmp.ssd<<" "<<settmp.gtr100x<<" "<<settmp.gtr100y<<" "<<settmp.gtr200x<<" "<<settmp.gtr200y<<" "<<settmp.gtr300x<<" "<<settmp.gtr300y<<std::endl;

  if(tracksets.size()==0){
    tracksets.push_back(settmp);
    return 1;
  }
  else{
    bool isgood = false;
    for(int j=0;j<tracksets.size();j++){
      if(settmp==tracksets.at(j)){
	return -1;
      }
      if(j==tracksets.size()-1){isgood=true;}
    }
    if(isgood==true){
      tracksets.push_back(settmp);
      return 1;
    }
    else{
      return -2;
    }
  }
}
Int_t AnalyzerTrackSelection::IsGoodTrackWHBD(Long64_t entry, int itrack, std::vector<trackset> &tracksets, double hbdadc)
{
  //tracks are already sorted by chi_square in DST1
  trackset settmp;
  settmp.track_id = track_id->at(itrack);
  settmp.chisq = chi_square->at(itrack);
  settmp.ssd = hbdadc;//HBD
  settmp.gtr100x = itrack;
  settmp.gtr100y = itrack;
  settmp.gtr200x = itrack;
  settmp.gtr200y = itrack;
  settmp.gtr300x = itrack;
  settmp.gtr300y = itrack;
  // std::cout<<settmp.chisq<<" "<<settmp.ssd<<" "<<settmp.gtr100x<<" "<<settmp.gtr100y<<" "<<settmp.gtr200x<<" "<<settmp.gtr200y<<" "<<settmp.gtr300x<<" "<<settmp.gtr300y<<std::endl;

  if(tracksets.size()==0){
    tracksets.push_back(settmp);
    return 1;
  }
  else{
    bool isgood = false;
    for(int j=0;j<tracksets.size();j++){
      if(settmp==tracksets.at(j)){
	return -1;
      }
      if(j==tracksets.size()-1){isgood=true;}
    }
    if(isgood==true){
      tracksets.push_back(settmp);
      return 1;
    }
    else{
      return -2;
    }
  }
}
// Int_t AnalyzerTrackSelection::Cut(Long64_t entry, std::vector<int>& goodtracks)
// {
//   if(goodtracks.size()==1){return 1;}
//   else{

//   struct set{
//     int track_id;
//     double chisq;
//     int pos_id;
//     double tim;

//     bool operator<(const set& another){
//       if( pos_id != another.pos_id ){ return pos_id<another.pos_id; }
//       if( tim != another.tim ){ return tim<another.tim; }
//       return chisq < another.chisq;
//     }

//   };
//   std::vector<set> tracks(0);
//   // std::cout<<n_tracks<<std::endl;
//   for(int i=0;i<n_tracks;i++){
//     if(chi_square->at(i)>30.) continue;
//     if(fabs(track_position_block_lx->at(i))>30) continue;
//     if(fabs(track_position_block_ly->at(i))>30) continue;
//     set settmp;
//     settmp.track_id = track_id->at(i);
//     settmp.chisq = chi_square->at(i);
//     int mid = track_lg_mid->at(i);
//     int blockchx = (track_lg_lx->at(i))-(track_position_block_lx->at(i));
//     int blockchy = (track_lg_ly->at(i)/fabs(track_lg_ly->at(i)))*(fabs(track_lg_ly->at(i))+track_position_block_ly->at(i));
//     int cid = SingleTrackAnalyzerForRes::LocaltoCh(blockchx,blockchy);
//     settmp.pos_id = mid*100+cid;
//     settmp.tim = track_ssd_t->at(i);
//     // std::cout<<settmp.pos_id<<" "<<settmp.tim<<" "<<settmp.chisq<<std::endl;
//     tracks.push_back(settmp);
//   }

//   sort(tracks.begin(),tracks.end());

//   int tmp_pos_id=10000;
//   for(int i=0;i<tracks.size();i++){
//     // std::cout<<tracks.at(i).pos_id<<" "<<tracks.at(i).tim<<" "<<tracks.at(i).chisq<<std::endl;
//     if(tracks.at(i).pos_id!=tmp_pos_id){
//       goodtracks.push_back(tracks.at(i).track_id);
//       tmp_pos_id = tracks.at(i).pos_id;
//     }
//   }

//   return 1;
//   }
// }

// Int_t AnalyzerTrackSelection::CutOfTrack(Long64_t entry, int itrack, int runoption)
// {
//   double momxz = sqrt(track_mom_x->at(itrack)*track_mom_x->at(itrack)+track_mom_z->at(itrack)*track_mom_z->at(itrack));//220212
//   if (track_hbd_mid->at(itrack)!=track_lg_mid->at(itrack)) {return -2;}
//   // else if (momxz<1.0) {return -1;}//220212
//   else if (chi_square->at(itrack)>30.) {return -1;}
//   // else if (fabs(track_angle_lx->at(itrack))>0.2) {return -1;}//220222
//   else if (fabs(track_position_block_lx->at(itrack))>30) {return -1;}//220222
//   else if (fabs(track_position_block_ly->at(itrack))>30) {return -1;}//220222
//   // else if ( runoption==0 && (track_ssd_t->at(itrack)<40||track_ssd_t->at(itrack)>55) ) {return -1;}//220213
//   // else if ( runoption==3 && (track_ssd_t->at(itrack)<41||track_ssd_t->at(itrack)>56) ) {return -1;}//220213
//   // else if ( runoption==1 && (track_ssd_t->at(itrack)<38||track_ssd_t->at(itrack)>54) ) {return -1;}//220213
//   // else if ( is_selected->at(itrack)==0 ) {return -1;}
//   // else if ( track_lg_multiplicity->at(itrack)>4 ) {return -1;}//220306
//   // else if ( track_hbd_multiplicity->at(itrack)>5 ) {return -1;}//220306
//   // else if ( track_tgt_dist->at(itrack)>5 ) {return -1;}
//   // else if((track_gtr100x_t->at(itrack)-track_ssd_t->at(itrack))<10) {return -1;}
//   // else if((track_gtr100x_t->at(itrack)-track_ssd_t->at(itrack))>250) {return -1;}
//   // else if((track_gtr100y_t->at(itrack)-track_ssd_t->at(itrack))<10) {return -1;}
//   // else if((track_gtr100y_t->at(itrack)-track_ssd_t->at(itrack))>250) {return -1;}
//   // else if((track_gtr200x_t->at(itrack)-track_ssd_t->at(itrack))<10) {return -1;}
//   // else if((track_gtr200x_t->at(itrack)-track_ssd_t->at(itrack))>250) {return -1;}
//   // else if((track_gtr200y_t->at(itrack)-track_ssd_t->at(itrack))<10) {return -1;}
//   // else if((track_gtr200y_t->at(itrack)-track_ssd_t->at(itrack))>250) {return -1;}
//   // else if((track_gtr300x_t->at(itrack)-track_ssd_t->at(itrack))<10) {return -1;}
//   // else if((track_gtr300x_t->at(itrack)-track_ssd_t->at(itrack))>250) {return -1;}
//   // else if((track_gtr300y_t->at(itrack)-track_ssd_t->at(itrack))<10) {return -1;}
//   // else if((track_gtr300y_t->at(itrack)-track_ssd_t->at(itrack))>250) {return -1;}
//   // else if(track_gtr100y_adc->at(itrack)/track_gtr100x_adc->at(itrack)<0.25) {return -1;}
//   // else if(track_gtr100y_adc->at(itrack)/track_gtr100x_adc->at(itrack)>1.5) {return -1;}
//   // else if(track_gtr200y_adc->at(itrack)/track_gtr200x_adc->at(itrack)<0.25) {return -1;}
//   // else if(track_gtr200y_adc->at(itrack)/track_gtr200x_adc->at(itrack)>1.5) {return -1;}
//   // else if(track_gtr300y_adc->at(itrack)/track_gtr300x_adc->at(itrack)<0.25) {return -1;}
//   // else if(track_gtr300y_adc->at(itrack)/track_gtr300x_adc->at(itrack)>1.5) {return -1;}
//   // else if(  runoption==1 && (track_gtr100x_t->at(itrack)-track_gtr100y_t->at(itrack))<-20)  {return -1;}
//   // else if(  runoption==1 && (track_gtr100x_t->at(itrack)-track_gtr100y_t->at(itrack))>30)  {return -1;}
//   // else if(  runoption==1 && (track_gtr200x_t->at(itrack)-track_gtr200y_t->at(itrack))<-30)  {return -1;}
//   // else if(  runoption==1 && (track_gtr200x_t->at(itrack)-track_gtr200y_t->at(itrack))>30)  {return -1;}
//   // else if(  runoption==1 && (track_gtr300x_t->at(itrack)-track_gtr300y_t->at(itrack))<-30)  {return -1;}
//   // else if(  runoption==1 && (track_gtr300x_t->at(itrack)-track_gtr300y_t->at(itrack))>30)  {return -1;}
//   else{
//     return 1;
//   }
// }
// Int_t AnalyzerTrackSelection::CutOfTrack(Long64_t entry, int itrack)
// {
//   int runoption = 0;
//   return CutOfTrack(entry,itrack,runoption);
// }
Int_t AnalyzerTrackSelection::RunPurpose(int run_id)
{
  if( run_id==20908 || run_id==20909 || run_id==20914 || run_id==20921 || run_id==20924 || run_id==20927 )
    {//IM3, 5e9
      return 50;
    }
  else if( run_id==20928 || run_id==20930 || (run_id>=20932&&run_id<=20939) || run_id==20947 )
    {//106, 5e9
      return 56;
    }
  else if( run_id==20912 || run_id==20913 || (run_id>=20941&&run_id<=20946) || run_id==20915 || run_id==20916 || run_id==20929 )
    {//107, 5e9
      return 57;
    }
  else if( run_id==20987 || run_id==20989 )
    {//IM3, 1e9
      return 10;
    }
  else if( (run_id>=20996&&run_id<=20998) || (run_id>=21000&&run_id<=21010) )
    {//104,106,108, 1e9
      return 15;
    }
  else if( run_id==20990 || run_id==20991 || run_id==20994 || run_id==20995 || run_id==20999 )
    {//106, 1e9
      return 16;
    }
  else if( run_id==20992 || run_id==20993 )
    {//107, 1e9
      return 17;
    }
  else{
    std::cout<<"This RunNumber is not categorized"<<std::endl;
    return -1;
  }
}
#endif // #ifdef AnalyzerTrackSelection_cxx
