#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <sys/time.h>
#include <TH1.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TSpectrum.h>

#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"
#include "E16DST_DST1Constant.hh"
#include "E16ANA_LGConstant.hh"
#include "E16ANA_LGClustering.hh"

#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1DefaultFilePath.hh"

#include <algorithm>
#include <unordered_map>   

E16ANA_LGClustering::E16ANA_LGClustering()
{
  lghits.clear();
  lgclusters.clear();
}


void E16ANA_LGClustering::SetHitData(int hid, int mid, int cid, float peak, float timing, float integral, double lx, double ly){

  lghit hit;
  hit.hid = hid;
  hit.mid = mid;
  hit.cid = cid;
  hit.peak = peak;
  hit.timing = timing;
  hit.integral = integral;
  hit.lx = lx;
  hit.ly = ly;
  lghits.push_back(hit);

}

void E16ANA_LGClustering::Clustering(){

  if(lghits.size()==0){return;}

  sort(lghits.begin(),lghits.end());
  std::vector<std::vector<lghit>> sorthits;
  sorthits.push_back(std::vector<lghit>());
  int n_pre_cluster=0;
  int pre_cluster_tmp;
  for(int isort=0;isort<lghits.size();isort++){
    if( isort!=0 && lghits[isort].mid*10+(lghits[isort].cid)/10 != pre_cluster_tmp ){
      n_pre_cluster++;
      sorthits.push_back(std::vector<lghit>());
    }
    pre_cluster_tmp = lghits[isort].mid*10+(lghits[isort].cid)/10;
    sorthits[n_pre_cluster].push_back(lghits[isort]);
  }
  n_pre_cluster++;

  std::vector<lghit> hits;
  lgcluster cluster;
  double tim_max=-10000;
  double tim_min=10000;
  for(int ipre=0;ipre<n_pre_cluster;ipre++){
    while(sorthits[ipre].size()!=0){
      lghit hita = sorthits[ipre].at(0);
      sorthits[ipre].erase(sorthits[ipre].begin());
      hits.push_back(hita);
      CalcTimeRegion(hits,tim_max,tim_min);
      int ihit=0;
      int n_pre_hits = sorthits[ipre].size();
      for(int iprehit=0;iprehit<n_pre_hits;iprehit++){
	lghit hitb = sorthits[ipre].at(ihit);
	if( fabs(hitb.cid-hita.cid)==1 && hitb.timing>tim_min && hitb.timing<tim_max ){
	  hits.push_back(hitb);
	  CalcTimeRegion(hits,tim_max,tim_min);
	  sorthits[ipre].erase(sorthits[ipre].begin()+ihit);
	}
	else{
	  ihit++;
	}
      }
      CalcHitsToCluster(hits,cluster);
      lgclusters.push_back(cluster);
      hits.clear();
    }
  }

}

void E16ANA_LGClustering::CalcTimeRegion(std::vector<lghit>& hits, double& tim_max, double& tim_min){

  double hittim_max = -10000.;
  double hittim_min = 10000.;
  int n_size = hits.size();
  for(int i=0;i<n_size;i++){
    lghit hit = hits.at(i);
    if(hit.timing>hittim_max){ hittim_max = hit.timing; }
    if(hit.timing<hittim_min){ hittim_min = hit.timing; }
  }

  tim_max = hittim_min + time_diff_threshold;
  tim_min = hittim_max - time_diff_threshold;

}

int E16ANA_LGClustering::CalcHitsToCluster(std::vector<lghit>& hits, lgcluster& cluster){

  if(hits.size()==0){
    std::cout<<"invalid hits"<<std::endl;
  }
  else if(hits.size()==1){
    cluster.hids.clear();
    cluster.hids.push_back(hits.at(0).hid);
    cluster.mid = hits.at(0).mid;
    cluster.peaksum = hits.at(0).peak;
    cluster.fasttiming = hits.at(0).timing;
    cluster.timediff = 0;
    cluster.intsum = hits.at(0).integral;
    cluster.maxcid = hits.at(0).cid;
    cluster.maxpeak = hits.at(0).peak;
    cluster.lx = hits.at(0).lx;
    cluster.ly = hits.at(0).ly;
    //std::cout<<cluster.hids.size()<<" "<<cluster.mid<<" "<<cluster.peaksum<<" "<<cluster.fasttiming<<" "<<cluster.timediff<<" "<<cluster.intsum<<" "<<cluster.maxcid<<" "<<cluster.maxpeak<<" "<<cluster.lx<<" "<<cluster.ly<<"CLUSTER"<<std::endl;
  }
  else{
    cluster.hids.clear();
    cluster.mid = hits.at(0).mid;
    cluster.ly = hits.at(0).ly;
    float peaksum=0;
    float fasttiming=10000.;
    float latetiming=-10000;
    float timediff=0;
    float intsum=0;
    float maxpeak=-10000.;
    int maxcid=-10000;
    double lx;
    for(int i=0;i<hits.size();i++){
      lghit hit = hits.at(i);
      cluster.hids.push_back(hit.hid);
      peaksum += hit.peak;
      intsum += hit.integral;
      if(hit.timing<fasttiming){fasttiming = hit.timing;}
      if(hit.timing>latetiming){latetiming = hit.timing;}
      if(hit.peak>maxpeak){maxpeak = hit.peak; maxcid=hit.cid;}
      lx += hit.peak*hit.lx;
    }
    timediff = latetiming - fasttiming;
    lx = lx/peaksum;
    cluster.peaksum = peaksum;
    cluster.fasttiming = fasttiming;
    cluster.timediff = timediff;
    cluster.intsum = intsum;
    cluster.maxpeak = maxpeak;
    cluster.maxcid = maxcid;
    cluster.lx = lx;
    //std::cout<<cluster.hids.size()<<" "<<cluster.mid<<" "<<cluster.peaksum<<" "<<cluster.fasttiming<<" "<<cluster.timediff<<" "<<cluster.intsum<<" "<<cluster.maxcid<<" "<<cluster.maxpeak<<" "<<cluster.lx<<" "<<cluster.ly<<"CLUSTER"<<std::endl;
  }

  return hits.size();

}
