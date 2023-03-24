#ifndef E16ANA_LGGainCalibwoTrack_h
#define E16ANA_LGGainCalibwoTrack_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <stdio.h>
#include <iostream>
using namespace std;
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_TrackAnalyzerFromTree.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_HBDDeadChannel.hh"
#include "E16ANA_EIDSingleTrackAnalyzer.hh"

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
#include "vector"
#include "vector"

class E16ANA_LGGainCalibwoTrack : public E16ANA_EIDSingleTrackAnalyzer {
private :

  double search_d[5] = {1.25, 2.5, 5., 7.5, 15.};
  double search_1GeV[5][2] = { {20,10}, {30,10}, {40,10}, {40,10}, {15,15} };

public :

  struct nearcls{
    double adc;
    double t;
    double lx;
    double ly;
    double dist;

    void nearclsInit(){
      adc = -10000.;
      t = -10000.;
      lx = -10000.;
      ly = -10000.;
      dist = 10000.;
    }
    void nearclsSet(double tadc, double tt, double tlx, double tly, double tdist){
      adc = tadc;
      t = tt;
      lx = tlx;
      ly = tly;
      dist = tdist;
    }
  };

  E16ANA_LGGainCalibwoTrack(TTree *tree=0);
  virtual ~E16ANA_LGGainCalibwoTrack();
  virtual void     MakeTree(int runoption, int maxevent, char* out_file_name);
  virtual void     SideHit(int cidside, int ilg, double& outadc, double& outt);
  virtual void     LeftSideHit(int ilg, double& outadc, double& outt);
  virtual void     RightSideHit(int ilg, double& outadc, double& outt);
  virtual void     CalcCrossPoint(E16ANA_GeometryV2* geometry, int mid, int cid, int otherlid, int& othermid, TVector3& lcross);
  virtual void     OtherClsLoop(int lid, int xory, int othermid, double lcross, int& nassocs, nearcls& nc, std::vector<double>& outadc, std::vector<double>& outt, std::vector<double>& outlp);
  // virtual void     OtherClsLoopforGTR300(int lid, int xory, int othermid, double lcross, int& nassocs, nearcls& nc, std::vector<double>& outadc, std::vector<double>& outt, std::vector<double>& outlp);
  virtual void     MomentumEachBlock(char* out_pdf_file, char* out_root_file, int maxevent);

};

#endif

#ifdef E16ANA_LGGainCalibwoTrack_cxx
E16ANA_LGGainCalibwoTrack::E16ANA_LGGainCalibwoTrack(TTree* tree) : E16ANA_EIDSingleTrackAnalyzer(tree)
{
}

E16ANA_LGGainCalibwoTrack::~E16ANA_LGGainCalibwoTrack()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

void E16ANA_LGGainCalibwoTrack::SideHit(int cidside, int ith, double& outadc, double& outt)
{
  std::vector<double> adccand(0);
  std::vector<double> tcand(0);
  int mid = lg_hit_mid->at(ith);
  int cid = lg_hit_cid->at(ith);
  for(int ilg=0;ilg<n_lg_hits;ilg++){
    if(ilg==ith) continue;
    if(lg_hit_mid->at(ilg)!=mid) continue;
    if(lg_hit_cid->at(ilg)==cid+cidside){
      adccand.push_back(lg_hit_adc->at(ilg));
      tcand.push_back(lg_hit_t->at(ilg));
    }
  }
  double tdiff_min = 10000.;
  for(int i=0;i<adccand.size();i++){
    double tdiff = fabs( lg_hit_t->at(ith)-tcand.at(i) );
    if(tdiff<tdiff_min){
      outadc = adccand.at(i);
      outt = tcand.at(i);
      tdiff_min = tdiff;
    }
  }
}
void E16ANA_LGGainCalibwoTrack::LeftSideHit(int ith, double& outadc, double& outt)
{
  SideHit(1,ith,outadc,outt);
}
void E16ANA_LGGainCalibwoTrack::RightSideHit(int ith, double& outadc, double& outt)
{
  SideHit(-1,ith,outadc,outt);
}

void E16ANA_LGGainCalibwoTrack::CalcCrossPoint(E16ANA_GeometryV2* geometry, int lgmid, int lgcid, int otherlid, int& othermid, TVector3& lcross)
{
  auto mid2013e = E16ANA_TrackConstant::ModuleID2020To2013_27(lgmid);//HBD, LG
  auto mid2013t = E16ANA_TrackConstant::ModuleID2020To2013(lgmid);//SSD, GTR
  bool is_crossed = false;

  TVector3 o(0., 0., 0.);
  TVector3 g0(0., 0., 0.);
  TVector3 g1(0., 0., 0.);//LG block position
  g1 = geometry->LG(mid2013e, lgcid)->GetGPos(o);
  double detector_region[2] = {0.,0.};// x, y (half width)

  if( otherlid==4 ){
    auto hbd_geom = geometry->HBD(mid2013e);
    is_crossed = hbd_geom->IsCrossed(g0,g1,lcross);
    othermid = lgmid;
  }
  else if( otherlid>=0 && otherlid<=3 ){
    const E16ANA_DetectorGeometry* trk_geom;
    if(otherlid==0){
      trk_geom = geometry->SSD(mid2013t);
      detector_region[0] = 30.;
      detector_region[1] = 30.;
    }
    else{
      trk_geom = geometry->GTR(mid2013t,otherlid-1);
      detector_region[0] = (double)otherlid*50;
      detector_region[1] = (double)otherlid*50;
    }
    is_crossed = trk_geom->IsCrossed(g0,g1,lcross);
    // if( is_crossed ){
    if( is_crossed && fabs(lcross.X())<detector_region[0] && fabs(lcross.Y())<detector_region[1] ){
      othermid = lgmid;
    }
    else{
      if(lgmid>105){ //L
	mid2013t = E16ANA_TrackConstant::ModuleID2020To2013(lgmid+1);
	if(otherlid==0){
	  trk_geom = geometry->SSD(mid2013t);
	}
	else{
	  trk_geom = geometry->GTR(mid2013t,otherlid-1);
	}
	is_crossed = trk_geom->IsCrossed(g0,g1,lcross);
	othermid = lgmid+1;
      }
      else{ //R
	mid2013t = E16ANA_TrackConstant::ModuleID2020To2013(lgmid-1);
	if(otherlid==0){
	  trk_geom = geometry->SSD(mid2013t);
	}
	else{
	  trk_geom = geometry->GTR(mid2013t,otherlid-1);
	}
	is_crossed = trk_geom->IsCrossed(g0,g1,lcross);
	othermid = lgmid-1;
      }
    }
  }
  else{
    std::cout<<"invalid layer id"<<std::endl;
  }

  if(!is_crossed){
    std::cout<<"LG "<<lgmid<<"-"<<lgcid<<std::endl;
    std::cout<<"Layer"<<otherlid<<" is not crossed."<<std::endl;
  }

}

void E16ANA_LGGainCalibwoTrack::OtherClsLoop(int lid, int xory, int othermid, double lcross, int& nassocs, nearcls& nc, std::vector<double>& outadc, std::vector<double>& outt, std::vector<double>& outlp)
{
  int nclusters;
  std::vector<int>* mid;
  std::vector<float>* adc;
  std::vector<double>* t;
  std::vector<double>* lp;
  double adcthr;
  if(lid==0){
    nclusters = n_ssd_clusters;
    mid = ssd_cluster_mid;
    adc = ssd_cluster_adc;
    t = ssd_cluster_t;
    lp = ssd_cluster_x;
    adcthr = 0.;
  }
  else if(lid==1){
    if(xory==0){
      nclusters = n_gtr100x_clusters;
      mid = gtr100x_cluster_mid;
      adc = gtr100x_cluster_adc;
      t = gtr100x_cluster_t;
      lp = gtr100x_cluster_x;
      adcthr = 100.;
    }
    else{
      nclusters = n_gtr100y_clusters;
      mid = gtr100y_cluster_mid;
      adc = gtr100y_cluster_adc;
      t = gtr100y_cluster_t;
      lp = gtr100y_cluster_y;
      adcthr = 50.;
    }
  }
  else if(lid==2){
    if(xory==0){
      nclusters = n_gtr200x_clusters;
      mid = gtr200x_cluster_mid;
      adc = gtr200x_cluster_adc;
      t = gtr200x_cluster_t;
      lp = gtr200x_cluster_x;
      adcthr = 100.;
    }
    else{
      nclusters = n_gtr200y_clusters;
      mid = gtr200y_cluster_mid;
      adc = gtr200y_cluster_adc;
      t = gtr200y_cluster_t;
      lp = gtr200y_cluster_y;
      adcthr = 50.;
    }
  }
  else if(lid==3){
    if(xory==0){
      nclusters = n_gtr300x_clusters;
      mid = gtr300x_cluster_mid;
      adc = gtr300x_cluster_adc;
      t = gtr300x_cluster_t;
      lp = gtr300x_cluster_x;
      adcthr = 100.;
    }
    else{
      nclusters = n_gtr300y_clusters;
      mid = gtr300y_cluster_mid;
      adc = gtr300y_cluster_adc;
      t = gtr300y_cluster_t;
      lp = gtr300y_cluster_y;
      adcthr = 50.;
    }
  }
  else{
    std::cout<<"invalid layer id"<<std::endl;
    nassocs = 0;
    nc.nearclsInit();
    return;
  }
  // double search_d_tmp = search_d[lid];
  double search_d_tmp = search_1GeV[lid][xory];

  nc.nearclsInit();
  nassocs = 0;
  for(int io=0;io<nclusters;io++){
    if(mid->at(io)!=othermid) continue;
    if(adc->at(io)<adcthr) continue;
    double dist = fabs(lp->at(io) - lcross);
    if(dist<search_d_tmp){
      outadc.push_back(adc->at(io));
      outt.push_back(t->at(io));
      outlp.push_back(lp->at(io));
      nassocs++;
    }
    if(dist<nc.dist){
      if(xory==0){
	nc.nearclsSet(adc->at(io), t->at(io), lp->at(io), -10000., dist);
      }
      else{
	nc.nearclsSet(adc->at(io), t->at(io), -10000., lp->at(io), dist);
      }
    }
  }

}
// void E16ANA_LGGainCalibwoTrack::OtherClsLoopforGTR300(int lid, int xory, int othermid, double lcross, int& nassocs, nearcls& nc, std::vector<double>& outadc, std::vector<double>& outt, std::vector<double>& outlp)
// {
//   int nclusters;
//   std::vector<int>* mid;
//   std::vector<float>* adc;
//   std::vector<double>* t;
//   std::vector<double>* lp;
//   double adcthr;
//   double search_d_tmp;
//   if(xory==0){
//     nclusters = n_gtr300x_clusters;
//     mid = gtr300x_cluster_mid;
//     adc = gtr300x_cluster_adc;
//     t = gtr300x_cluster_t;
//     lp = gtr300x_cluster_x;
//     adcthr = 100.;
//     search_d_tmp = 40.;//230320
//   }
//   else{
//     nclusters = n_gtr300y_clusters;
//     mid = gtr300y_cluster_mid;
//     adc = gtr300y_cluster_adc;
//     t = gtr300y_cluster_t;
//     lp = gtr300y_cluster_y;
//     adcthr = 50.;
//     search_d_tmp = 10.;//230320
//   }

//   nc.nearclsInit();
//   nassocs = 0;
//   for(int io=0;io<nclusters;io++){
//     if(mid->at(io)!=othermid) continue;
//     if(adc->at(io)<adcthr) continue;
//     double dist = fabs(lp->at(io) - lcross);
//     if(dist<search_d_tmp){
//       outadc.push_back(adc->at(io));
//       outt.push_back(t->at(io));
//       outlp.push_back(lp->at(io));
//       nassocs++;
//     }
//     if(dist<nc.dist){
//       if(xory==0){
// 	nc.nearclsSet(adc->at(io), t->at(io), lp->at(io), -10000., dist);
//       }
//       else{
// 	nc.nearclsSet(adc->at(io), t->at(io), -10000., lp->at(io), dist);
//       }
//     }
//   }

// }
// void E16ANA_LGGainCalibwoTrack::SetGTRAllCls(int lid, int xory, std::vector<double>& outv)
// {
//   int nclusters;
//   std::vector<int>* mid;
//   std::vector<float>* adc;
//   std::vector<double>* lp;
//   double adcthr;

//   if(lid==0){
//     if(xory==0){
//       nclusters = n_gtr100x_clusters;
//       mid = gtr100x_cluster_mid;
//       adc = gtr100x_cluster_adc;
//       lp  = gtr100x_cluster_x;
//       adcthr = 100.;
//     }
//     else{
//       nclusters = n_gtr100y_clusters;
//       mid = gtr100y_cluster_mid;
//       adc = gtr100y_cluster_adc;
//       lp  = gtr100y_cluster_y;
//       adcthr = 50.;
//     }
//   }
//   else if(lid==1){
//     if(xory==0){
//       nclusters = n_gtr200x_clusters;
//       mid = gtr200x_cluster_mid;
//       adc = gtr200x_cluster_adc;
//       lp  = gtr200x_cluster_x;
//       adcthr = 100.;
//     }
//     else{
//       nclusters = n_gtr200y_clusters;
//       mid = gtr200y_cluster_mid;
//       adc = gtr200y_cluster_adc;
//       lp  = gtr200y_cluster_y;
//       adcthr = 50.;
//     }
//   }
//   else if(lid==2){
//     if(xory==0){
//       nclusters = n_gtr300x_clusters;
//       mid = gtr300x_cluster_mid;
//       adc = gtr300x_cluster_adc;
//       lp  = gtr300x_cluster_x;
//       adcthr = 100.;
//     }
//     else{
//       nclusters = n_gtr300y_clusters;
//       mid = gtr300y_cluster_mid;
//       adc = gtr300y_cluster_adc;
//       lp  = gtr300y_cluster_y;
//       adcthr = 50.;
//     }
//   }

//   for(int igtr=0;igtr<nclusters;igtr++){
//     if( adc->at(igtr)<adcthr ) continue;
//     int midgtr = mid->at(igtr)-101;
//     outv[midgtr].push_back( lp->at(igtr) );
//   }

// }
#endif // #ifdef E16ANA_LGGainCalibwoTrack_cxx
