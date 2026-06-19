// 2015-11-02, uploaded by yokkaich
// 2015-11-02, uploaded by komatsu
// 2015-10-05, uploaded by yokkaich
// 2015-07-15, uploaded by nakai
// 2015-05-29, uploaded by yokkaich
// 2015-04-08, uploaded by nakai

#include <iostream>
#include <cmath>

#include "GTR/E16ANA_GTRStripAnalyzer.h"
//#include "E16ANA_WaveformFitter.h"
//#include "E16ANA_Waveform2dFitter.h"

E16ANA_GTRStripAnalyzer::E16ANA_GTRStripAnalyzer(int _n_strips, int _n_sampling)
   : n_strips(_n_strips), n_sampling(_n_sampling), strip_pitch(0.35), gem_threshold(4.0), gem_tot_threshold(-10000.0),
     drift_velocity(0.010), drift_gap_center(0.0), fadc_clock_period(32.0), fadc_t0_correction(0.0),
     gem_tdc_min(-10000.0), gem_tdc_max(10000.0), gem_tr(75.0), threshold_fraction(0.5), inverted(1.0),cluster_minimum_gap(1), cluster_delta_tdc(10000.0),  
     rise_time_min(-10000.0),   rise_time_max(10000.0),
     peak_time_min(-10000.0),   peak_time_max(10000.0)

{
   fadc = new double *[n_strips];
   for (int i = 0; i < n_strips; i++) {
      fadc[i] = new double[n_sampling];
   }
   
   fadc_peak.resize(n_strips);
   fadc_peak_tdc.resize(n_strips);
   fadc_peak_time.resize(n_strips);
   fadc_tdc.resize(n_strips);
   fadc_tot.resize(n_strips);
   fadc_rise.resize(n_strips);
   fadc_peak_st.resize(n_strips);
   fadc_peak_ed.resize(n_strips);
   fadc_used.resize(n_strips);
   fadc_qual.resize(n_strips);

   fadc_ped       = new double[n_strips];
   fadc_ped_sigma = new double[n_strips];
   fadc_tped      = new double[n_sampling];
   gem_analyzed_hits.reserve(510);
   for (int i = 0; i < n_strips; i++) {
      fadc_ped[i] = 0.0;
      fadc_ped_sigma[i] = 1.0;
   }
   // wf1d_fitter = new E16ANA_WaveformFitter();
   // wf2d_fitter = new E16ANA_Waveform2dFitter();
   drift_velocity = 0.008;
   ztiming        = 328;
   Clear();
}

E16ANA_GTRStripAnalyzer::~E16ANA_GTRStripAnalyzer()
{
   for (int i = 0; i < n_strips; i++) {
      delete[] fadc[i];
   }
   delete[] fadc;
   delete[] fadc_ped;
   delete[] fadc_tped;
   delete[] fadc_ped_sigma;

   fadc_peak.clear();
   fadc_peak_time.clear();
   fadc_peak_tdc.clear();
   fadc_tdc.clear();
   fadc_tot.clear();
   fadc_rise.clear();
   fadc_peak_st.clear();
   fadc_peak_ed.clear();
   fadc_used.clear();
   fadc_qual.clear();
   // delete wf1d_fitter;
   // delete wf2d_fitter;
}

void E16ANA_GTRStripAnalyzer::Clear()
{
   for (int i = 0; i < n_strips; i++) {
      for (int j = 0; j < n_sampling; j++) {
         fadc[i][j] = -100000.0;
      }
   }
}

void E16ANA_GTRStripAnalyzer::SetLFadc(int strip_id, int16_t *waveform)
{

  /*
   double local_pedestal = 0.0;
  for (int j = 0; j < 3; j++) {
    local_pedestal += waveform[j];
  }
  local_pedestal /= 3.0;

  double local_pedestal2 = 0.0;
  int iped = 0;
  for (int j = 0; j < 3; j++) {
    if(waveform[j]-local_pedestal-fadc_ped[strip_id]<80&&waveform[j]-local_pedestal-fadc_ped[strip_id]>-180){
      local_pedestal2 += waveform[j];
      iped++;
    }
  }
  if(iped>1){
    local_pedestal = local_pedestal2/iped;
  }else{
    local_pedestal = fadc_ped[strip_id];
  }
  */

  double local_pedestal = 0.0;
  for (int j = 0; j < 3; j++) {
    local_pedestal += (double)waveform[j];
  }
  local_pedestal /= 3.0;
  
   for (int j = 0; j < n_sampling; j++) {
     //fadc[strip_id][j] = waveform[j] - fadc_ped[strip_id];
     fadc[strip_id][j] = waveform[j] - local_pedestal;
     fadc_tped[j]      = 0;
   }
}


void E16ANA_GTRStripAnalyzer::SetFadc(int strip_id, int16_t *waveform)
{
  /*
  double local_pedestal = 0.0;
   for (int j = 0; j < 3; j++) {
     local_pedestal += waveform[j];
   }
   local_pedestal /= 3.0;
  */

  for (int j = 0; j < n_sampling; j++) {
    fadc[strip_id][j] = waveform[j] - fadc_ped[strip_id];
//      if(strip_id == 700 && j == 0){
//       std::cout  << "fadc   = " << fadc[strip_id][j] << std::endl;
//      }
     //fadc[strip_id][j] = waveform[j] - local_pedestal;
   }
}


bool E16ANA_GTRStripAnalyzer::IsBadStrip(int strip_id)
{

   if (fabs(fadc_ped[strip_id]) > bad_pedestal_threshold) {
     //return true;
   }
   if (fadc_ped_sigma[strip_id] > bad_pedestal_sigma_threshold) {
     // return true;
   }
   if (fadc_ped_sigma[strip_id] < 2.0) { // too small
     // return true;
   }

   return false;
}

void E16ANA_GTRStripAnalyzer::Analyze()
{

   // CalcWaveParamsPeak();
   int n_hits = HitClusteringV0();
//   std::cout << "clusterd size = " << n_hits << std::endl;
   gem_analyzed_hits.resize(n_hits);
   // gem_analyzed_hits.resize(n_hits,E16ANA_GTRAnalyzedStripHit());

   int cid,cpt,pid,ppt;
   double npt,rpt;
   cid = cpt = pid = ppt = -100;
   rpt = npt = -100;
   for (int i = 0; i < n_hits; i++) {
      gem_analyzed_hits[i].SetInvalid();
      CalcCenterOfGravity(clustered_strip_id[i], gem_analyzed_hits[i]);
      //CalcTdcHit1(clustered_strip_id[i], gem_analyzed_hits[i], i);
      //CalcTdcHit12(clustered_strip_id[i], gem_analyzed_hits[i], i);
      CalcTdcHit12V2(clustered_strip_id[i], gem_analyzed_hits[i], i, pid,ppt,cid,cpt,npt,rpt);
      pid = cid;
      ppt = cpt;
      npt = rpt;
      // CalcTdcHit2(clustered_strip_id[i], gem_analyzed_hits[i].TanTheta(), gem_analyzed_hits[i]);
   }
}



void E16ANA_GTRStripAnalyzer::Analyze2()
{
   // CalcWaveParamsPeak();
   int n_hits = HitClusteringV0();
   gem_analyzed_hits.resize(n_hits);
   // gem_analyzed_hits.resize(n_hits,E16ANA_GTRAnalyzedStripHit());
   for (int i = 0; i < n_hits; i++) {
      CalcCenterOfGravity(clustered_strip_id[i], gem_analyzed_hits[i]);
      CalcTdcHit2(clustered_strip_id[i], gem_analyzed_hits[i].TanTheta(), gem_analyzed_hits[i]);
   }
}

void E16ANA_GTRStripAnalyzer::Analyze2(int id)
{
   //  E16MESSAGE("size %d %d", clustered_strip_id.size(), gem_analyzed_hits.size());
   CalcTdcHit2(clustered_strip_id[id], gem_analyzed_hits[id].TanTheta(), gem_analyzed_hits[id]);
}

void E16ANA_GTRStripAnalyzer::AnalyzeV1()
{
   // CalcWaveParamsPeak();
  int n_hits = HitClusteringV1();
   gem_analyzed_hits.resize(n_hits);
   int cid,cpt,pid,ppt;
   double npt,rpt;
   cid = cpt = pid = ppt = -100;
   rpt = npt = -100;
   // gem_analyzed_hits.resize(n_hits,E16ANA_GTRAnalyzedStripHit());
   for (int i = 0; i < n_hits; i++) {
      gem_analyzed_hits[i].SetInvalid();
      CalcCenterOfGravity(clustered_strip_id[i], gem_analyzed_hits[i]);
      //CalcTdcHit1(clustered_strip_id[i], gem_analyzed_hits[i], i);
      //      CalcTdcHit12(clustered_strip_id[i], gem_analyzed_hits[i], i);//original
      CalcTdcHit12V2(clustered_strip_id[i], gem_analyzed_hits[i], i, pid,ppt,cid,cpt,npt,rpt);
      pid = cid;
      ppt = cpt;
      npt = rpt;
      // CalcTdcHit2(clustered_strip_id[i], gem_analyzed_hits[i].TanTheta(), gem_analyzed_hits[i]);
   }
}

int E16ANA_GTRStripAnalyzer::HitClusteringV0()
{
   return HitClusteringV0(cluster_minimum_gap, -10000.0);
   //return HitClusteringV0(2, -10000.0);
}

int E16ANA_GTRStripAnalyzer::HitClusteringV0(const int min_gap, const double cluster_threshold)
{
  /*
  CalcWaveParamsPeak();
   int signal_gap = 100;
   
   for (int i = 0; i < (int)clustered_strip_id.size(); i++) {
     clustered_strip_id[i].clear();
   }
   clustered_strip_id.clear();


   for (int i = 0; i < n_strips; i++) {
      if (fadc_peak[i] > 0.0 && fadc_peak_time[i] > 0.0) {
	if (signal_gap >= min_gap) {
	  clustered_strip_id.push_back(std::vector<int>());
			
	} else if (fadc_peak[i] < cluster_threshold) {
	  clustered_strip_id.push_back(std::vector<int>());
	}
	clustered_strip_id.back().push_back(i);
	signal_gap = 0;
      } else {
	signal_gap++;
      }
   }
   */
   return clustered_strip_id.size();
}

int E16ANA_GTRStripAnalyzer::HitClusteringV1(){
  return HitClusteringV1(cluster_minimum_gap, cluster_delta_tdc);
}

int E16ANA_GTRStripAnalyzer::HitClusteringV1(const int min_gap, const double delta_tdc_threshold)
{
   CalcWaveParamsPeak();
   for (int i = 0; i < (int)clustered_strip_id.size(); i++) {
     clustered_strip_id[i].clear();
   }
   clustered_strip_id.clear();
   
   int nhit=0;
   std::vector<int> lastcls;
   lastcls.clear();
   for(int it = 0; it < 3; it++) {
     int signal_gap = 100;   
     int    pre_id  = -10;
     double pre_tdc =  0;
     for (int i = 0; i < n_strips; i++) {
       if((int)fadc_tdc.at(i).size()>0){
	 pre_tdc = fadc_tdc.at(i).at(0);
       }
     }
     for(int i = 0; i < n_strips; i++) {
       if((int)fadc_tdc.at(i).size()>0) {
	 for(int jj = 0; jj < (int)fadc_tdc.at(i).size(); jj++) {
	   if(it==0) nhit++;
	   int j=jj;
	   if(it==2) j = fadc_tdc.at(i).size() - jj - 1;
	   
	   if(fadc_used.at(i).at(j)>0) 	  continue;
	   //if(it==0) std::cout<<"id::"<<i<<", "<<j<<" pulse::"<<fadc_tdc.at(i).at(j)<<", "<< fadc_peak_ed.at(i).at(j)<<", " <<fadc_peak.at(i).at(j) <<std::endl;
	   int sid = j*1000+i;	 
	   double delta_tdc = fadc_tdc.at(i).at(j) - pre_tdc;
	   double delta_id  = i - pre_id;
	   if(delta_id==0) {
	     //if(it==0) std::cout<<"same pad " <<std::endl;
	     int csize = clustered_strip_id.back().size();
	     if(csize>1){
	       int psid2 = clustered_strip_id.back().at(csize-2);
	       int pi2   = (int)psid2%1000;
	       int pj2   = (int)(psid2/1000);
	       double pre_tdc2  = fadc_tdc.at(pi2).at(pj2) ;
	       if(fabs(fadc_tdc.at(i).at(j)-pre_tdc2)<delta_tdc_threshold){
		 int psid  = clustered_strip_id.back().at(csize-1);
		 int pi    = (int)psid%1000;
		 int pj    = (int)(psid/1000);
		 double cur_tdc = fadc_tdc.at(i).at(j) ;
		 if(fabs(pre_tdc2-cur_tdc)<fabs(pre_tdc2-fadc_tdc.at(pi).at(pj))){
		   clustered_strip_id.back().pop_back();
		   fadc_used.at(pi).at(pj) = -1;
		   fadc_used.at(i).at(j)   =  1;
		   pre_tdc = fadc_tdc.at(i).at(j);
		   pre_id  = i;
		   clustered_strip_id.back().push_back(sid);
		   signal_gap = 0;
		   if(it==2) lastcls.push_back(psid);
		   //std::cout<<"re-find close hit1" <<std::endl;
		   continue;
		 }
	       }
	     }
	     if(it==2) lastcls.push_back(sid);
	     continue;
	   }
	   
	   if(signal_gap<min_gap && (fabs(delta_tdc)>delta_tdc_threshold) && (j<(int)(fadc_tdc.at(i).size()-1)) ) {
	     //if(it==0) std::cout<<"search other hit " <<std::endl;
	     if(it==2) lastcls.push_back(sid);
	     continue;
	   }
	   if (signal_gap >= min_gap){
	     if(pre_id>-1&&it<2){
	       if(clustered_strip_id.back().size()==1) clustered_strip_id.pop_back();
	     }
	     clustered_strip_id.push_back(std::vector<int>());
	     //if(it==0) std::cout<<"find isolate hit " <<std::endl;
	   }
	   if( signal_gap<min_gap && fabs(delta_tdc) >delta_tdc_threshold ){
	     if(pre_id>-1&&it<2){
	       if(clustered_strip_id.back().size()==1) clustered_strip_id.pop_back();
	     }
	     clustered_strip_id.push_back(std::vector<int>());
	     //if(it==0) std::cout<<"find different tdc hit "<< pre_tdc<<", "<<fadc_tdc.at(i).at(j) <<std::endl;
	   }

	   int sflag = -1;
	   
	   if(clustered_strip_id.back().size()>1){
	     int id1   = clustered_strip_id.back().at(clustered_strip_id.back().size()-1);
	     int i1    = (int)id1%1000;
	     int j1    = (int)(id1/1000);
	     int id2   = clustered_strip_id.back().at(clustered_strip_id.back().size()-2);
	     int i2    = (int)id2%1000;
	     int j2    = (int)(id2/1000);

	     if( ((fadc_peak.at(i2).at(j2)-20>fadc_peak.at(i1).at(j1)) &&(fadc_peak.at(i).at(j)-20  >fadc_peak.at(i1).at(j1)))
		 ||  ((fadc_peak.at(i).at(j)-20>fadc_peak.at(i1).at(j1)) &&(fadc_peak.at(i).at(j)-20  >fadc_peak.at(i2).at(j2)))
		 ){
	       double maxadc = -1000;
	       for(int ic=0;ic<clustered_strip_id.back().size();ic++){
		 int psid  = clustered_strip_id.back().at(ic);
		 int pi    = (int)psid%1000;
		 int pj    = (int)(psid/1000);
		 if(maxadc<fadc_peak.at(pi).at(pj)) maxadc = fadc_peak.at(pi).at(pj);
	       }
	       if(0.4*maxadc>fadc_peak.at(i1).at(j1)){
		 sflag = 1;
		 clustered_strip_id.push_back(std::vector<int>());
		 //std::cout<<"split cluster " <<std::endl;
	       }


	       
	     }
	   }
	   
	   //if(delta_id>0 && delta_id<=min_gap && fabs(delta_tdc) < delta_tdc_threshold){
	   if(signal_gap<min_gap && fabs(delta_tdc) <= delta_tdc_threshold && sflag<0){
	     if(pre_id>-1){
	       int psid  = clustered_strip_id.back().back();
	       int pi    = (int)psid%1000;
	       int pj    = (int)(psid/1000);
	       int rflag = -1;
	       if(fadc_tdc.at(pi).size()>1){
		 double min_dtdc = fadc_tdc.at(i).at(j) - fadc_tdc.at(pi).at(pj);
		 for(int ii=0;ii<fadc_tdc.at(pi).size();ii++){
		   if(fadc_used.at(pi).at(ii)>0) continue;
		   if(ii==pj)                    continue;
		   double pre_tdc2  = fadc_tdc.at(pi).at(ii) ;
		   if(fabs(pre_tdc2-fadc_tdc.at(i).at(j))<=delta_tdc_threshold){
		     if(fabs(min_dtdc)>fabs(pre_tdc2-fadc_tdc.at(i).at(j))){
		       min_dtdc = pre_tdc2-fadc_tdc.at(i).at(j);
		       
		       if(clustered_strip_id.back().size()==1) {
			 clustered_strip_id.pop_back();
			 fadc_used.at(pi).at(pj) = -1;
			 if(it==2) lastcls.push_back(psid);
		       }
		       
		       
		       clustered_strip_id.push_back(std::vector<int>());
		       clustered_strip_id.back().push_back(ii*1000+pi);
		       fadc_used.at(pi).at(ii) = 1;
		       rflag = 1;
		       //std::cout<<"re-find close hit2" <<std::endl;
		     }
		   }
		 }  
	       }
	       
	       if(rflag<0){
		 fadc_used.at(pi).at(pj) = 1;
	       }
	       
	     }
	     fadc_used.at(i).at(j) = 1;
	     //std::cout<<"try::"<<it <<", find cluster::" <<i<<", "<<j<<", "<<clustered_strip_id.back().size() <<std::endl;
	   }
	   pre_tdc = fadc_tdc.at(i).at(j);
	   pre_id  = i;
	   clustered_strip_id.back().push_back(sid);
	   signal_gap = 0;
	 }
       }else {
	 signal_gap++;
       }
     }
     if(clustered_strip_id.size()>0&&it<2){
       if(clustered_strip_id.back().size()==1) clustered_strip_id.pop_back();
     }
   }

   

   //if(nhit>0) std::cout<<"remaining cls::"<< lastcls.size()<<std::endl;
   for(int i=0;i<lastcls.size();i++){
     int lid     = lastcls.at(i);
     int li      = (int)lid%1000;
     int lj      = (int)(lid/1000);
     double ltdc = fadc_tdc.at(li).at(lj);
     int iflag   = -1;

     for(int j=0;j<clustered_strip_id.size();j++){
       int i0    = (int)clustered_strip_id.at(j).front()%1000;
       int j0    = (int)(clustered_strip_id.at(j).front()/1000);
       int i1    = (int)clustered_strip_id.at(j).back()%1000;
       int j1    = (int)(clustered_strip_id.at(j).back()/1000);
       if(li==(i0-1) &&  fabs(ltdc-fadc_tdc.at(i0).at(j0)) <= delta_tdc_threshold){
	 clustered_strip_id.at(j).insert(clustered_strip_id.at(j).begin(),lid);
	 iflag = 1;
	 break;
       }
       if(li==(i1+1) &&  fabs(ltdc-fadc_tdc.at(i1).at(j1)) <= delta_tdc_threshold){
	 clustered_strip_id.at(j).push_back(lid);
	 iflag = 1;
	 break;
       }
     }

     if(iflag<0){
       clustered_strip_id.push_back(std::vector<int>());
       clustered_strip_id.back().push_back(lastcls.at(i));
     }
   }
   lastcls.clear();
   int renhit = 0;
   
   for(int i=0;i<clustered_strip_id.size();i++){
     renhit += clustered_strip_id.at(i).size();
     //for(int ii=0;ii<clustered_strip_id.at(i).size();ii++){
     //std::cout<<i<<", "<<ii<<", "<<clustered_strip_id.at(i).at(ii)<<std::endl;
     //}
   }
   //if(nhit>0)   std::cout<<"hit::"<<nhit<<",  ncls::"<<clustered_strip_id.size()<<", "<<renhit<<std::endl;
   //std::cout<<std::endl;
   return clustered_strip_id.size();
}

void E16ANA_GTRStripAnalyzer::CalcWaveParamsPeak()
{

  
  for (int i = 0; i < n_strips; i++) {
    if (fadc[i][0] < -255.0) {
      continue;
    }
    this->CalcWaveParamsPeak(i, 10000.0);
  }
  
}

void E16ANA_GTRStripAnalyzer::CalcWaveParamsPeak(int ch, double t_cutoff)
{

  int npeak = 0;
  int peak_count[3];
  int qual[3];
  double tot_start[3];
  double tot_end[3];
  double peakadc[3];
  double peaktime[3];

  for(int i=0;i<3;i++){
    peak_count[i] =  -1;
    tot_start[i]  =   1000;
    tot_end[i]    =  -1000;
    peakadc[i]    =  -1000;
    peaktime[i]   =  -1000;
  }
  
  if (ch > (n_strips-1)) return;
  double tempfadc[15];  
  int      peakc = -1;
  double tempmax = -100;
  for (int j = 1; j < n_sampling-1; j++) {
    tempfadc[j] = fadc[ch][j];
    if (tempmax < fadc[ch][j]) {
      tempmax = fadc[ch][j];
      peakc = j;
    }
  }

  int      peakc2 = -1;
  double tempmax2 = -100;
  for (int j = 1; j < n_sampling-1; j++) {
    if(j==peakc) continue;
    if (tempmax2 < fadc[ch][j]) {
      tempmax2 = fadc[ch][j];
      peakc2 = j;
    }
  }

  //remove noise
  /*
  if(tempmax*threshold_fraction*0.75>fadc[ch][peakc-1]){
    if(tempmax*threshold_fraction*0.75>fadc[ch][peakc+1]){
      if(tempmax2*threshold_fraction*0.75>fadc[ch][peakc2-1]){
	if(tempmax2*threshold_fraction*0.75>fadc[ch][peakc2+1]){
	  for (int j = 0; j < n_sampling; j++) {
	    fadc[ch][j] = fadc[ch][j] - fadc_tped[j]; 
	  }
	}
      }
    }
  }
  */
  /*
  if(tempmax>gem_threshold){
    if(tempmax*threshold_fraction/2>fadc[ch][peakc-1]){
      if(tempmax*threshold_fraction/2>fadc[ch][peakc+1]){
	if(tempmax2*threshold_fraction/2>fadc[ch][peakc2-1]){
	  if(tempmax2*threshold_fraction/2>fadc[ch][peakc2+1]){
	    for (int j = 0; j < n_sampling; j++) {
	      fadc[ch][j] = fadc[ch][j] - fadc_tped[j]; 
	    }
	  }
	}
      }
    }
  }else{
    for (int j = 0; j < n_sampling; j++) {
      fadc_tped[j] = fadc[ch][j];
    }
  }
  */
    
  //remove spike
  /*
  int      peakc3 = -1;
  double tempmax3 = -100;
  for (int j = 0; j < n_sampling; j++) {
    if (tempmax3 < fadc[ch][j]) {
      tempmax3 = fadc[ch][j];
      peakc3 = j;
    }
  }
  if(0<peakc3&&peakc3<n_sampling-1&&tempmax3>gem_threshold){
    if(tempmax3*threshold_fraction/2>fadc[ch][peakc-1]){
      if(tempmax3*threshold_fraction/2>fadc[ch][peakc+1]){
	fadc[ch][peakc] = fadc[ch][peakc-1];
      }
    }
  }
  */
  
  for (int j = 3; j < n_sampling; j++) {
    //if(npeak>2)                      continue;
    if(npeak>1)                      continue;
    if(fadc[ch][j]<gem_threshold)    continue;
    if(fadc[ch][j-1]>fadc[ch][j])    continue;
    if(fadc[ch][j-2]>fadc[ch][j])    continue;
    if(j<(n_sampling-2)){
      if(fadc[ch][j+2]>fadc[ch][j])  continue;
    }
    if(j<(n_sampling-1)){
      if(fadc[ch][j+1]>fadc[ch][j])  continue;
    }
    
    peak_count[npeak] = j;
    peakadc[npeak]    = fadc[ch][j];
    peaktime[npeak]   = j * fadc_clock_period + fadc_t0_correction;
    int nflag1 = -1;
    int nflag2 = -1;
    int st = -1;
    
    if(npeak>0){
      double minadc = 10000;
      int    mint   = 0;
      for (int j =  peak_count[npeak-1]; j<peak_count[npeak];j++) {
	if(fadc[ch][j]<minadc) {
	  minadc = fadc[ch][j];
	}
      }
      if (minadc < peakadc[npeak]*threshold_fraction) {
	st = peak_count[npeak-1];
      }else{
	double dadc      = (peakadc[npeak] - fadc[ch][mint])/(peak_count[npeak]-mint);
	double dtbin     = peakadc[npeak]*threshold_fraction/dadc;
	double tdc_j     = peak_count[npeak] - dtbin;
	tot_start[npeak] = tdc_j * fadc_clock_period + fadc_t0_correction;
      }
    }
    
    if(npeak==0 || (st>-1&&npeak>0) ){
      double temp_start = -10;
      for (int jj = peak_count[npeak]; jj > st; jj--) {
	if (fadc[ch][jj] < peakadc[npeak] * threshold_fraction) {
	  double w_j0      =  peakadc[npeak] * threshold_fraction - fadc[ch][jj];
	  double w_j1      = -peakadc[npeak] * threshold_fraction + fadc[ch][jj+1];
	  double tdc_j     = (jj * w_j1 + (jj + 1.0) * w_j0) / (w_j0 + w_j1);
	  tot_start[npeak] = tdc_j * fadc_clock_period + fadc_t0_correction;
	  if(jj==0)    break;
	  if(nflag1>0) break;
	  if( (fadc[ch][jj-1]>peakadc[npeak]*threshold_fraction)&&(jj==(peak_count[npeak]-1))){
	    nflag1     = 1;
	    temp_start = tot_start[npeak];
	  }else{
	    break;
	  }
	}
      }
      if(nflag1>0&&temp_start>0) tot_start[npeak] = (tot_start[npeak]+temp_start)/2;
    }  
    
    /*
    if(npeak==0 || (npeak>0 && fadc[ch][peak_count[npeak]-3]<peakadc[npeak]*threshold_fraction)){
      for (int jj = peak_count[npeak]; jj > -1; jj--) {
	if (fadc[ch][jj] < peakadc[npeak] * threshold_fraction) {
	  double w_j0      =  peakadc[npeak] * threshold_fraction - fadc[ch][jj];
	  double w_j1      = -peakadc[npeak] * threshold_fraction + fadc[ch][jj+1];
	  double tdc_j     = (jj * w_j1 + (jj + 1.0) * w_j0) / (w_j0 + w_j1);
	  tot_start[npeak] = tdc_j * fadc_clock_period + fadc_t0_correction;
	  if(jj==0)    break;
	  if(nflag1>0) break;
	  if( (fadc[ch][jj-1]>peakadc[npeak]*threshold_fraction)&&(jj==(peak_count[npeak]-1))){
	    nflag1 = 1;
	  }else{
	    break;
	  }
	}
      }
    }else{
      double dadc   = peakadc[npeak] - fadc[ch][peak_count[npeak]-1];
      double dtbin  = peakadc[npeak]*threshold_fraction/dadc;
      double tdc_j  = peak_count[npeak] - dtbin;
      tot_start[npeak] = tdc_j * fadc_clock_period + fadc_t0_correction;
    }
    */

    
    if(j==(n_sampling-1)) tot_end[npeak] = -1000;
    if(j==(n_sampling-2)) {
      double dadc   = peakadc[npeak] - fadc[ch][peak_count[npeak]+1];
      double dtbin  = peakadc[npeak]*threshold_fraction/dadc;
      double tdc_j  = peak_count[npeak] + dtbin +1;
      tot_end[npeak] = tdc_j * fadc_clock_period + fadc_t0_correction;
      //std::cout<<"end case1::"<<tot_end[npeak]<<std::endl;
    }
    if(j==(n_sampling-3)){
      if(fadc[ch][peak_count[npeak]+2]<peakadc[npeak]*threshold_fraction){
	for (int jj = peak_count[npeak]; jj < n_sampling; jj++) {
	  if (fadc[ch][jj] < peakadc[npeak] * threshold_fraction) {
	    double w_j0 =  peakadc[npeak] * threshold_fraction - fadc[ch][jj-1];
	    double w_j1 = -peakadc[npeak] * threshold_fraction + fadc[ch][jj];
	    double tdc_j = (jj * w_j1 + (jj + 1.0) * w_j0) / (w_j0 + w_j1);
	    tot_end[npeak] = tdc_j * fadc_clock_period + fadc_t0_correction;
	    //std::cout<<"end case2::"<<tot_end[npeak]<<std::endl;
	    break;
	  }
	}
      }else{
	double dadc   = peakadc[npeak] - fadc[ch][peak_count[npeak]+2];
	double dtbin  = 2*(peakadc[npeak]*threshold_fraction/dadc);
	double tdc_j  = peak_count[npeak] + dtbin +1;
	tot_end[npeak] = tdc_j * fadc_clock_period + fadc_t0_correction;
	//std::cout<<"end case3::"<<tot_end[npeak]<<std::endl;
      }
    }
    
    if(j<(n_sampling-3)){
      if(fadc[ch][peak_count[npeak]+2]<fadc[ch][peak_count[npeak]+3]
	 && fadc[ch][peak_count[npeak]+3]>peakadc[npeak]*threshold_fraction) {
	double dadc   = peakadc[npeak] - fadc[ch][peak_count[npeak]+2];
	double dtbin  = 2*(peakadc[npeak]*threshold_fraction/dadc);
	double tdc_j  = peak_count[npeak] + dtbin +1;
	tot_end[npeak] = tdc_j * fadc_clock_period + fadc_t0_correction;
	//std::cout<<"end case4::"<<tot_end[npeak]<<std::endl;
      }else{
	if(fadc[ch][peak_count[npeak]+3]<peakadc[npeak]*threshold_fraction){
	  for (int jj = peak_count[npeak]; jj < n_sampling; jj++) {
	    if (fadc[ch][jj] < peakadc[npeak] * threshold_fraction) {
	      double w_j0 =  peakadc[npeak] * threshold_fraction - fadc[ch][jj-1];
	      double w_j1 = -peakadc[npeak] * threshold_fraction + fadc[ch][jj];
	      double tdc_j = (jj * w_j1 + (jj + 1.0) * w_j0) / (w_j0 + w_j1);
	      tot_end[npeak] = tdc_j * fadc_clock_period + fadc_t0_correction;
	      if(jj==(n_sampling-1))    break;
	      if(nflag2>0)              break;
	      if( (fadc[ch][jj+1]>peakadc[npeak]*threshold_fraction)&&(jj==(peak_count[npeak]+1))){
		nflag2 = 1;
	      }else{
		break;
	      }
	    }
	  }
	}else if(j==(n_sampling-4)){
	  double dadc   = peakadc[npeak] - fadc[ch][peak_count[npeak]+3];
	  double dtbin  = 3*(peakadc[npeak]*threshold_fraction/dadc);
	  double tdc_j  = peak_count[npeak] + dtbin  + 1;
	  tot_end[npeak] = tdc_j * fadc_clock_period + fadc_t0_correction;
	  //std::cout<<"end case6::"<<tot_end[npeak]<<std::endl;
	}else{
	  double minadc = 99999;
	  int    minit  = -1;
	  for (int jj = peak_count[npeak]; jj < n_sampling; jj++) {
	    if(fadc[ch][jj]<minadc){
	      minadc = fadc[ch][jj];
	      minit  = jj;
	    }
	  }
	  if(minadc<peakadc[npeak]*threshold_fraction){
	    for (int jj = peak_count[npeak]; jj < n_sampling; jj++) {
	      if (fadc[ch][jj] < peakadc[npeak] * threshold_fraction) {
		double w_j0 =  peakadc[npeak] * threshold_fraction - fadc[ch][jj-1];
		double w_j1 = -peakadc[npeak] * threshold_fraction + fadc[ch][jj];
		double tdc_j = (jj * w_j1 + (jj + 1.0) * w_j0) / (w_j0 + w_j1);
		tot_end[npeak] = tdc_j * fadc_clock_period + fadc_t0_correction;
		//std::cout<<"end case7::"<<tot_end[npeak]<<std::endl;
		if(jj==(n_sampling-1))    break;
		if(nflag2>0)              break;
		if( (fadc[ch][jj+1]>peakadc[npeak]*threshold_fraction)&&(jj==(peak_count[npeak]+1))){
		  nflag2 = 1;
		}else{
		  break;
		}
	      }
	    }
	  }else{
	    double dadc   = peakadc[npeak] - fadc[ch][minit];
	    double dtbin  = (minit-npeak)*(peakadc[npeak]*threshold_fraction/dadc);
	    double tdc_j  = peak_count[npeak] + dtbin +1;
	    tot_end[npeak] = tdc_j * fadc_clock_period + fadc_t0_correction;
	    //std::cout<<"end case8::"<<tot_end[npeak]<<std::endl;
	  }
	}
      }
    }
  
    int wcut = 1;
    double temptot = tot_end[npeak]   - tot_start[npeak];
    double temprt  = peaktime[npeak]  - tot_start[npeak];


    /*
    std::cout<<"ch::"<<ch<<", "<<GetPosition(ch)<<", "<< peakadc[npeak]<<", "<<tot_start[npeak]<<", "<<tot_end[npeak] <<std::endl;
    if(ch==50){
      for(int ii=0;ii<15;ii++){
	std::cout<<fadc[ch][ii]<<std::endl;
      }
    }
    */
    if(tot_end[npeak]<0 && temprt<(rise_time_min+50)){
      wcut = -1;
    }
    if(temptot<gem_tot_threshold){
      //std::cout<<"ch::"<<ch<<", tot cut"<<std::endl;
      wcut = -1;
    }
    if(nflag1>0 && nflag2>0&&peakadc[npeak]<2*gem_threshold ){
      //std::cout<<"ch::"<<ch<<", noise cut"<<std::endl;
      wcut = -1;
    }
    if(temprt<rise_time_min&&peakadc[npeak]<2*gem_threshold){
      //std::cout<<"ch::"<<ch<<", RT cut"<<std::endl;
      wcut = -1;
    }
    if(tot_end[npeak]-peaktime[npeak]<18&&tot_end[npeak]>0){
      //std::cout<<"ch::"<<ch<<", ET cut"<<std::endl;
      wcut = -1;
    }
    if(tot_start[npeak]>gem_tdc_max||tot_start[npeak]<gem_tdc_min){
      //std::cout<<"ch::"<<ch<<", TDC MAX cut"<<std::endl;
      wcut = -1;
    }
    if(tot_end[npeak]>1 && tot_end[npeak]<peak_time_max){
      //std::cout<<"ch::"<<ch<<", TDC END cut"<<std::endl;
      wcut = -1;
    }
    if(npeak>0){
      //if(fabs(tot_start[npeak] - tot_start[npeak-1])<cluster_delta_tdc && ){
      if(fabs(peaktime[npeak] - peaktime[npeak-1])<cluster_delta_tdc){
	//std::cout<<"ch::"<<ch<<", too close cut"<<std::endl;
	wcut = -1;
      }
    }
    if(peakadc[npeak]>3.5*gem_threshold) {
      //std::cout<<"ch::"<<ch<<", OK"<<std::endl;
      wcut = 1;
    }
    qual[npeak] = -1-(nflag1+nflag2)/2;
    if(wcut>0) npeak++;
  }
  
  if(npeak==0){
    for (int j = 0; j < n_sampling; j++) {
      fadc_tped[j] = tempfadc[j];
    }
  }

  fadc_peak[ch].resize(npeak);
  fadc_peak_tdc[ch].resize(npeak);
  fadc_peak_time[ch].resize(npeak);
  fadc_tdc[ch].resize(npeak);
  fadc_tot[ch].resize(npeak);
  fadc_rise[ch].resize(npeak);
  fadc_peak_st[ch].resize(npeak);
  fadc_peak_ed[ch].resize(npeak);
  fadc_used[ch].resize(npeak);
  fadc_qual[ch].resize(npeak);
  
  for(int i=0;i<npeak;i++){
    fadc_peak[ch][i]      = peakadc[i];
    fadc_peak_time[ch][i] = peaktime[i];
    fadc_peak_tdc[ch][i]  = peak_count[i];
    fadc_tdc[ch][i]       = tot_start[i];
    fadc_tot[ch][i]       = tot_end[i]   - tot_start[i];
    fadc_rise[ch][i]      = peaktime[i]  - tot_start[i];
    fadc_peak_st[ch][i]   = tot_start[i];
    fadc_peak_ed[ch][i]   = tot_end[i];
    fadc_used[ch][i]      = -1;
    fadc_qual[ch][i]      = qual[i];
  }
}

void E16ANA_GTRStripAnalyzer::CalcCenterOfGravity(const std::vector<int> &strip_ids, E16ANA_GTRAnalyzedStripHit &hit)
{
   int temp_max_strip = -1;
   double temp_max_value = -255.0;
   int temp_num_hit = 0;
   double temp_cc = 0.0;
   double temp_cog = 0.0;
   double temp_tot = -10;
   double temp_rise = -10;
   int temp_qual = 0;
   if ((int)strip_ids.size() == 0) {
      hit.SetInvalid();
      return;
   }
   
   int tempid = -1;
   for (int i = 0; i < (int)strip_ids.size(); i++) {
     int sid = strip_ids.at(i);
     int pi   = (int)sid%1000;
     int pj   = (int)(sid/1000);
     if (fadc_peak.at(pi).at(pj) > temp_max_value) {
       tempid = pi;
       temp_max_value = fadc_peak.at(pi).at(pj);
     }
   }
   
   temp_max_value = -255.0;

   for (int i = 0; i < (int)strip_ids.size(); i++) {
     int sid = strip_ids.at(i);
     int pi   = (int)sid%1000;
     int pj   = (int)(sid/1000);

     if( (tempid-2) <=pi && pi<=(tempid+2)){
       if (fadc_peak.at(pi).at(pj) > temp_max_value) {
         temp_max_strip = pi;
         temp_max_value = fadc_peak.at(pi).at(pj);
	 temp_tot       = fadc_tot.at(pi).at(pj);
         temp_rise      = fadc_rise.at(pi).at(pj);
	 temp_qual      = fadc_qual.at(pi).at(pj);
       }
       temp_cc += fadc_peak.at(pi).at(pj);
       temp_cog += fadc_peak.at(pi).at(pj) * GetPosition(pi);
     }
     temp_num_hit++;

     // temp_cog += fadc_peak[id]*id;
     // hit.PushBackStrip(id, GetPosition(id), fadc_peak[id], fadc_tdc[id], fadc_tot[id], fadc[id]);//original
     hit.PushBackStrip(pi, GetPosition(pi), fadc_peak.at(pi).at(pj), fadc_tdc.at(pi).at(pj), fadc_tot.at(pi).at(pj),  fadc_peak_time.at(pi).at(pj), fadc_peak_st.at(pi).at(pj), fadc_peak_ed.at(pi).at(pj), fadc_rise.at(pi).at(pj), fadc[pi]);
   }
   temp_cog /= temp_cc;

   // temp_cog *= strip_pitch;
   // temp_cog += position_start;
   // temp_cog *= inverted;

   
   hit.SetMaxStrip(temp_max_strip);
   hit.SetMaxValue(temp_max_value);
   hit.SetNumHit(temp_num_hit);
   hit.SetClusterCharge(temp_cc);
   hit.SetCogHit(temp_cog);
   hit.SetQual(temp_qual);
}

void E16ANA_GTRStripAnalyzer::SetArraysForTdcMethods(const std::vector<int> &strip_ids, std::vector<double> &x_array,
                                                     std::vector<double> &time_array, std::vector<double> &peak_array)
{
  for (int i = 0; i < (int)strip_ids.size(); i++) {
    int sid  = strip_ids.at(i);
    int pi   = (int)sid%1000;
    int pj   = (int)(sid/1000);
    
    x_array.push_back(GetPosition(pi));
    time_array.push_back(fadc_tdc.at(pi).at(pj) * drift_velocity);
    peak_array.push_back(fadc_peak.at(pi).at(pj));
  }
}

void E16ANA_GTRStripAnalyzer::SetArraysForTdcMethods2(const std::vector<int> &strip_ids, std::vector<double> &x_array,
						      std::vector<double> &time_array, std::vector<double> &peak_array)
{
  /*
  for (int i = 0; i < (int)strip_ids.size(); i++) {
    int id = strip_ids[i];
    int it = fadc_peak_tdc[id];
    double sumq = 0;
    double sumx = 0;
    for (int j = 0; j < (int)strip_ids.size(); j++) {
      int id2 = strip_ids[j];
      double tq = fadc[id2][it];
      if(tq<0) tq = 0;
      sumq += tq;
      sumx += tq * GetPosition(id2);
    }
    if(sumq>0){
      double lx = sumx/sumq;
      x_array.push_back(lx);
      time_array.push_back(fadc_tdc[id]);
      peak_array.push_back(fadc_peak[id]);
    }
  }
  */

}

void E16ANA_GTRStripAnalyzer::SetArraysForTdcMethods4(const std::vector<int> &strip_ids, std::vector<double> &x_array,
                                                      std::vector<double> &x_array2,std::vector<double> &time_array,
                                                      std::vector<double> &time_array2)
{

  for (int i = 0; i < (int)strip_ids.size(); i++) {
    int sid  = strip_ids.at(i);
    int pi   = (int)sid%1000;
    int pj   = (int)(sid/1000);

    int it     = (int)(fadc_peak_tdc.at(pi).at(pj));
    int imax   = 1;
    
    for (int j = 0; j < (int)strip_ids.size(); j++) {
      if(i==j)    continue;
      if(imax<0)  continue;
      int   id2  = (int)strip_ids.at(j)%1000;
      double tq  = fadc[id2][it];
      if(tq>fadc[pi][it]) imax = -1;
    }
    if(imax<0)  continue;
    
    double sumq = 0;
    double sumx = 0;
    double sumt = 0;

    for (int j = 0; j < (int)strip_ids.size(); j++) {
      int sid2  = strip_ids.at(j);
      int id2   = (int)sid2%1000;
      int pj2   = (int)(sid2/1000);
      double tq = fadc[id2][it];
      if(tq<0) tq = 0;
      sumq += tq;
      sumx += tq * GetPosition(id2);
      sumt += tq * fadc_tdc.at(id2).at(pj2);
    }

    if(sumq>0){
      double lx = sumx/sumq;
      double lt = sumt/sumq;
      x_array.push_back(GetPosition(pi));
      time_array.push_back(fadc_tdc.at(pi).at(pj));
      x_array2.push_back(lx);
      time_array2.push_back(lt);
    }
  }
}


void E16ANA_GTRStripAnalyzer::SetArraysForTdcMethods30(const std::vector<int> &strip_ids,
						       std::vector<double> &xcent,std::vector<double> &xtime,
						       std::vector<double> &adc1,std::vector<double> &adc2,
						       std::vector<double> &adc3,std::vector<double> &adc4,
						       std::vector<double> &adc5, int &tpeak, int &idpeak){

  double mpeak = -999;
  int mid2 = -10;
  for (int i = 0; i < (int)strip_ids.size(); i++) {
    int id   = strip_ids.at(i);
    int pi   = (int)id%1000;
    int pj   = (int)(id/1000);
    
    double adc = fadc_peak.at(pi).at(pj);
    if(adc>mpeak){
      mpeak = adc;
      mid2  = pi;
      tpeak = (int)(fadc_peak_tdc.at(pi).at(pj));
    }
  }
  
  idpeak = mid2;
  for (int i = 0; i < n_sampling; i++) {
    double lt = i * fadc_clock_period + fadc_t0_correction;
    double lq = 0;
    double rq = 0;
    if(mid2>0)           lq = fadc[mid2-1][i];
    if(mid2<n_strips-1)  rq = fadc[mid2+1][i];
    double mq  =  fadc[mid2][i];
    double llq = 0;
    double rrq = 0;
    if(mid2>1)           llq = fadc[mid2-2][i];
    if(mid2<n_strips-2)  rrq = fadc[mid2+2][i];
    xcent.push_back(GetPosition(mid2));
    xtime.push_back(lt);
    adc1.push_back(llq);
    adc2.push_back(lq);
    adc3.push_back(mq);
    adc4.push_back(rq);
    adc5.push_back(rrq);
  }

}

void E16ANA_GTRStripAnalyzer::SetArraysForTdcMethods3(const std::vector<int> &strip_ids, std::vector<double> &x_array,
                                                      std::vector<double> &time_array, std::vector<double> &peak_array,
						      double &tdc4, double &tdc5,  std::vector<double> &cadc,
						      double &ced, double &ctot, double &crt,double &cpeak){
  double temppeak= 0;
  double tempsumq= 0;
  double tempmax = -100;
  int    tempid  = 0;
  double ftime   = 99999;
  for (int i = 0; i < (int)strip_ids.size(); i++) {
    int sid  = strip_ids.at(i);
    int pi   = (int)sid%1000;
    int pj   = (int)(sid/1000);
    if(fadc_peak_tdc.at(pi).size()>0){
      if(fadc_tdc.at(pi).at(pj)<ftime){
	ftime = fadc_tdc.at(pi).at(pj);
      }
      
      if(tempmax<fadc_peak.at(pi).at(pj)){
	tempmax = fadc_peak.at(pi).at(pj);
	tempid  = pi;
      }
    }
  }
  
  tdc5 = ftime;
  
  for (int i = 0; i < (int)strip_ids.size(); i++) {
    int sid  = strip_ids.at(i);
    int pi   = (int)sid%1000;
    int pj   = (int)(sid/1000);
    int it    = fadc_peak_tdc.at((int)strip_ids.at(0)%1000).at(0);
    if(pi<tempid-2)  continue;
    if(pi>tempid+2)  continue;
    if(fadc_peak_tdc.at(pi).size()>0){
      it        = fadc_peak_tdc.at(pi).at(pj);
      temppeak += it*fadc_peak.at(pi).at(pj);
      tempsumq += fadc_peak.at(pi).at(pj);
    }
    //std::cout<<strip_ids.size() <<", "<<id<<", "<<it <<std::endl;
    double sumq = 0;
    double sumx = 0;
    for (int j = 0; j < (int)strip_ids.size(); j++) {
      int id2   = (int)strip_ids.at(j)%1000;
      if(id2<tempid-2)  continue;
      if(id2>tempid+2)  continue;
      double tq = fadc[id2][it];
      if(tq<0) tq = 0;
      sumq += tq;
      sumx += tq * GetPosition(id2);
    }
    if(sumq>0){
      double lx = sumx/sumq;
      if(fadc_peak_tdc.at(pi).size()>0){
	x_array.push_back(lx);
	time_array.push_back(fadc_tdc.at(pi).at(pj));
	peak_array.push_back(fadc_peak.at(pi).at(pj));
      }
    }
  }
  temppeak = int(temppeak/tempsumq);
    
  
  double sadc[n_sampling];
  int    peakc   = -1;
  double peakq   = -9999;
  int secondpeak = -1;
  for (int i = 0; i < n_sampling; i++) {
    double maxq = -99999;
    int    mid  = -10;
    sadc[i] = 0;
    for (int j = 0; j < (int)strip_ids.size(); j++) {
      int id    = (int)strip_ids.at(j)%1000;
      if(id<tempid-2)  continue;
      if(id>tempid+2)  continue;
      if((int)strip_ids.at(j)/1000>0) secondpeak = 1;
      double tq = fadc[id][i];
      if(id!=tempid && (int)strip_ids.at(j)/1000>0) tq=0;
      if(tq<0) tq=0;
      //std::cout<<i<<"  strip::"<<id<<", "<<j<<", "<<fadc[id][i]<<", "<<tq<<std::endl;
      sadc[i]  += tq;
      if(tq>maxq) {
        maxq = tq;
        mid  = id;
      }
    }
    cadc.push_back(sadc[i]);
    if(temppeak-2<=i && i<= temppeak+2 && 2<i){
      if(sadc[i]>peakq){
	peakq = sadc[i];
	peakc = i;
      }
    }
  }
  cpeak = 0;
  for (int j = 0; j < (int)strip_ids.size(); j++) {
    int id    = (int)strip_ids.at(j)%1000;
    if(id<tempid-2)  continue;
    if(id>tempid+2)  continue;
    cpeak += fadc[id][peakc];
  }

  
  int fpeak      = 0;
  if(secondpeak>0){
    //for (int j = peakc-1; j>2;j--) {
    //if(sadc[j]>sadc[j-1]+20&&sadc[j]>sadc[j-2]+20&&sadc[j]>sadc[j+1]+20 ) {
    for (int j = 2; j<peakc;j++) {
      if(sadc[j]>sadc[j-1]&&sadc[j]>sadc[j-2]&&sadc[j]>sadc[j+1] && sadc[j]>peakq*threshold_fraction ) {
	fpeak = j;
      }
    }
  }
  
  
  
  tdc4 = -100;
  ced  =  1000;
  if(peakc>-1&&peakc<n_sampling-1){
    double minadc = 10000;
    int    mint   = 0;
    //for (int j = 0; j<peakc;j++) {
    for (int j = fpeak; j<peakc;j++) {
      if(sadc[j]<minadc) {
	minadc = sadc[j];
	mint   = j;
      }
    }
    if(minadc<peakq * threshold_fraction){
      double ftdc = -1000;
      for (int j = peakc; j > -1; j--) {
	if (sadc[j] < peakq * threshold_fraction) {
	  // double tdc_j = j;
	  double w_j0 =  peakq * threshold_fraction - sadc[j];
	  double w_j1 = -peakq * threshold_fraction + sadc[j+1];
	  double tdc_j = (j * w_j1 + (j + 1.0) * w_j0) / (w_j0 + w_j1);
	  tdc4 = tdc_j * fadc_clock_period + fadc_t0_correction;
	  if(j==0)   break;
	  if(ftdc>0) break;
	  if( (sadc[j-1]> peakq*threshold_fraction)&&(j==(peakc-1))){
	    ftdc = tdc4;
	  }else{
	    break;
	  }
	}
      }
      if(ftdc>0) tdc4 = (tdc4+ftdc)/2;
    }else{
      double dadc   = (peakq - sadc[mint])/(peakc-mint);
      double dtbin  = peakq*threshold_fraction/dadc;
      double tdc_j  = peakc - dtbin;
      tdc4          = tdc_j * fadc_clock_period + fadc_t0_correction;
    }
    
    double minadc2 = 10000;
    int   mint2   = 14;
    for (int j = peakc; j<n_sampling;j++) {
      if(sadc[j]<minadc2) {
	minadc2 = sadc[j];
	mint2   = j;
      }
    }

    if(minadc2<peakq * threshold_fraction){
      double fed = -1000;
      for (int j = peakc; j < n_sampling; j++) {
	if (sadc[j] < peakq * threshold_fraction) {
	  // double tdc_j = j;
	  double w_j0  = peakq * threshold_fraction - sadc[j - 1];
	  double w_j1  = -peakq * threshold_fraction + sadc[j];
	  double tdc_j = (j * w_j1 + (j + 1.0) * w_j0) / (w_j0 + w_j1);
	  ced          = tdc_j * fadc_clock_period + fadc_t0_correction;
	  if(j==(n_sampling-1))  break;
	  if(fed>0)              break;
	  if( (sadc[j+1]>peakq*threshold_fraction)&&(j==(peakc+1))){
	    fed= ced;
	  }else{
	    break;
	  }
	}
      }
      if(fed>0) fed = (ced+fed)/2;
    }else{
      double dadc   = (peakq - sadc[mint2])/(mint2-peakc);
      double dtbin  = peakq*threshold_fraction/dadc;
      double tdc_j  = peakc + dtbin + 1;
      ced = tdc_j * fadc_clock_period + fadc_t0_correction;
    }
  }

  ctot = ced - tdc4;
  crt  = peakc*fadc_clock_period+fadc_t0_correction - tdc4;
  
  int    peakc2 = -1;
  double peakq2 = 145;
  //tdc5 = -1000;
  
  for (int j = 2; j < n_sampling-2; j++) {
    if(j==peakc) continue;
    if(sadc[j]>sadc[j-1] && sadc[j]>sadc[j-2]){
      if(sadc[j]>sadc[j+1] && sadc[j]>sadc[j+2]){
	if(sadc[j]>peakq2) {
	  peakq2  = sadc[j];
	  peakc2  = j;
	}
      }
    }
  }

  /*
  if(peakc2>-1){
    for (int j = peakc2; j > -1; j--) {
      if (sadc[j] < peakq2 * threshold_fraction) {
        // double tdc_j = j;
        double w_j0 =  peakq2 * threshold_fraction - sadc[j];
        double w_j1 = -peakq2 * threshold_fraction + sadc[j+1];
        double tdc_j = (j * w_j1 + (j + 1.0) * w_j0) / (w_j0 + w_j1);
        tdc5 = tdc_j * fadc_clock_period + fadc_t0_correction;
        break;
      }
    }
  }
  */

}




void E16ANA_GTRStripAnalyzer::CalcTdcHit1(const std::vector<int> &strip_ids, E16ANA_GTRAnalyzedStripHit &hit, int hitID)
{
  /*
   std::vector<double> x_array;
   std::vector<double> time_array;
   std::vector<double> peak_array;

   int temp_num_hit = 0;
   double temp_cc = 0.0;
   double temp_tdc_hit = 0.0;
   double temp_tan_theta = 0.0;

   if ((int)strip_ids.size() == 0) {
      hit.SetInvalid();
      return;
   }

   SetArraysForTdcMethods(strip_ids, x_array, time_array, peak_array);

   temp_num_hit = x_array.size();
   temp_cc = 0.0;

   double B = 0.0;
   double C = 0.0;
   double D = 0.0;
   double E = 0.0;

   for (int i = 0; i < (int)x_array.size(); i++) {
      B += x_array[i] * x_array[i];
      C += time_array[i];
      D += x_array[i] * time_array[i];
      E += x_array[i];
      temp_cc += peak_array[i];
   }

   double dtdx = (x_array.size() * D - C * E) / (x_array.size() * B - E * E);
   double t0 = (B * C - D * E) / (x_array.size() * B - E * E);
   temp_tan_theta = 1.0 / dtdx;
   temp_tdc_hit = (drift_gap_center - t0) / dtdx;

   hit.SetNumHit(temp_num_hit);
   hit.SetClusterCharge(temp_cc);
   hit.SetTdcHit(temp_tdc_hit);
   hit.SetTanTheta(temp_tan_theta);

   hit.SetID(hitID);

   double meantime = C / drift_velocity / x_array.size(); // cluster mean
   hit.SetTiming(meantime);
  */
}

void E16ANA_GTRStripAnalyzer::CalcTdcHit12(const std::vector<int> &strip_ids, E16ANA_GTRAnalyzedStripHit &hit, int hitID)
{
  /*
  std::vector<double> x_array;
  std::vector<double> time_array;
  std::vector<double> peak_array;

  int temp_num_hit = 0;
  double temp_cc = 0.0;
  double temp_tdc_hit = 0.0;
  double temp_tan_theta = 0.0;

  if ((int)strip_ids.size() == 0) {
    hit.SetInvalid();
    return;
  }
  SetArraysForTdcMethods2(strip_ids, x_array, time_array, peak_array);
  temp_num_hit = x_array.size();
  temp_cc = 0.0;
  double wt=0, t=0, sx=0, sy=0, st2=0, ss = 0, sxoss = 0;
  double sx2=0, sxy=0;
  double ftdc = 9999;
  int nn =0;
  for(int i = 0; i < x_array.size(); i++){
    ss  ++;
    sx  += time_array[i] ;
    sy  += x_array[i] ;
    sx2 += time_array[i] *time_array[i] ;
    sxy += x_array[i] * time_array[i] ;
    if(time_array[i]<ftdc){
      ftdc = time_array[i];
    }
    int flag = 1;
    for(int j = 0; j < i; j++){
      if(fabs(x_array[i]-x_array[j])<0.005) flag=-1;
    }
    if(flag>0) nn++;
  }
  double a = sy/x_array.size();
  double b = 0;
  if(nn>1&&sx*sx!=ss*sx2){
    a = (sx*sxy-sx2*sy)/(sx*sx-ss*sx2);       //seppen
    b = (sx*sy-ss*sxy)/(sx*sx-ss*sx2); //katamuki
  }
  double temp_mhit = a+b*ztiming;
  //double temp_mhit = a+b*200;

  hit.SetTdcHit(temp_mhit);
  hit.SetTanTheta(b/drift_velocity);
  hit.SetTiming2(ftdc);
  hit.SetTiming(sx/x_array.size());


  for(int i = 0; i < x_array.size(); i++){
    hit.SetCTiming(time_array[i]);
    hit.SetCPos(x_array[i]);
  }
  */

}



void E16ANA_GTRStripAnalyzer::FindSecPeak(std::vector<double> &adc,int tpeak, double &charge, double &t, double &tot , double &pt, double &st, double &ed, double &rizet){

  int    peakc  = -1;
  double qmax   =  0;
  charge = t = tot = pt = st = ed = rizet = -1000;
  for(int i=tpeak-4;i<=tpeak+4;i++){
    if(i>-1&&i<n_sampling){
      if(adc[i]>qmax){
	qmax  = adc[i];
	peakc = tpeak;
      }
    }
  }
  
  if(peakc<tpeak-2 || peakc>tpeak+2)  return;
  if(qmax<(gem_threshold-15))         return;
  pt =  peakc*fadc_clock_period + fadc_t0_correction;
  
  if(peakc>-1){
    for (int j = peakc; j > -1; j--) {
      if (adc[j] < qmax * threshold_fraction) {
        double w_j0 =  qmax * threshold_fraction - adc[j];
        double w_j1 = -qmax * threshold_fraction + adc[j+1];
        double tdc_j = (j * w_j1 + (j + 1.0) * w_j0) / (w_j0 + w_j1);
        st = tdc_j * fadc_clock_period + fadc_t0_correction;
	t  = tdc_j * fadc_clock_period + fadc_t0_correction;
        break;
      }
    }
    
    for (int j = peakc; j < n_sampling; j++) {
      if (adc[j] < qmax * threshold_fraction) {
	double w_j0  =  qmax * threshold_fraction - adc[j-1];
	double w_j1  = -qmax * threshold_fraction + adc[j];
	double tdc_j = (j * w_j1 + (j + 1.0) * w_j0) / (w_j0 + w_j1);
	ed           = tdc_j * fadc_clock_period + fadc_t0_correction;
	break;
      }
    }
  }
  
  if(st>0 && pt-st<17) return;
  if(ed>0 && ed-pt<17) return;
  tot = ed-st;
  if(tot<(gem_tot_threshold-10)&&st>0&&ed>0) return;
  if(st<0&&ed<0) return;
  rizet = pt-st;
  charge = qmax;

  return;
}

void E16ANA_GTRStripAnalyzer::CalcTdcHit12V2(std::vector<int> &strip_ids, E16ANA_GTRAnalyzedStripHit &hit, int hitID,int pid,int ppt,int &cid, int &cpt, double npt, double &prpt)
{// updated to morino-ana 
  std::vector<double> x_array, x_array2, x_array3, x_array4;
  std::vector<double> time_array, time_array2, time_array3, time_array4;
  std::vector<double> peak_array,peak_array2;
  std::vector<double> xcent;
  std::vector<double> xtime;
  std::vector<double> adc1, adc2, adc3, adc4, adc5;
  std::vector<double> cadc;
  int temp_num_hit = 0;
  double temp_cc = 0.0;
  double temp_tdc_hit = 0.0;
  double temp_tan_theta = 0.0;
  double time4, time5;

  if ((int)strip_ids.size() == 0) {
    hit.SetInvalid();
    return;
  }
  int sid1 =  (int)strip_ids.size();
  //SetArraysForTdcMethods2(strip_ids, x_array, time_array, peak_array);
  
  SetArraysForTdcMethods(strip_ids, x_array2, time_array2, peak_array2);
  SetArraysForTdcMethods4(strip_ids, x_array3, x_array4, time_array3, time_array4);

  int tpeak,idpeak;
  SetArraysForTdcMethods30(strip_ids, xcent,xtime, adc1, adc2, adc3,adc4, adc5, tpeak,idpeak);
  cid   = idpeak;
  cpt   = tpeak;
  prpt   = -100;
  int fdump = -1;
  
  if(pid==cid && cpt==ppt){
    hit.SetNumHit(1);
    hit.SetClusterCharge(0);
    fdump = 1;
    //std::cout<<"same clus::"<<sid1<<std::endl;
  }
  
  double lqmax,ltime,ltot,lpt,lst,led,lrt;
  double rqmax,rtime,rtot,rpt,rst,red,rrt;
  double llqmax,lltime,lltot,llpt,llst,lled,llrt;
  double rrqmax,rrtime,rrtot,rrpt,rrst,rred,rrrt;
  double qmax = adc3[tpeak];
  
  FindSecPeak(adc1,tpeak, llqmax, lltime, lltot, llpt, llst, lled, llrt);
  FindSecPeak(adc2,tpeak, lqmax,  ltime,   ltot,  lpt,  lst,  led, lrt);
  FindSecPeak(adc4,tpeak, rqmax,  rtime,   rtot,  rpt,  rst,  red, rrt);
  FindSecPeak(adc5,tpeak, rrqmax, rrtime, rrtot, rrpt, rrst, rred, rrrt);

  
  int fll,fl,fr,frr;
  fll = fl = fr = frr = -1;
  for (int i = 0; i < (int)strip_ids.size(); i++) {
    if(int(strip_ids[i]%1000)==idpeak-2) fll = 1; 
    if(int(strip_ids[i]%1000)==idpeak-1) fl  = 1;
    if(int(strip_ids[i]%1000)==idpeak+1) fr  = 1;
    if(int(strip_ids[i]%1000)==idpeak+2) frr = 1;
  }
  
  if(rqmax>(gem_threshold-10)) prpt = rpt;
  double ptime =  ppt*fadc_clock_period + fadc_t0_correction;
  int fadd = 1;
  
  if(pid==(idpeak-1) && fabs(ptime-lpt)<10){
    fadd = -1;
    //std::cout<<"previous clus1::"<<", "<<sid1<<", "<< ptime-lpt<<", "<<fl <<std::endl;
  }

  if(pid==(idpeak-2) && fabs(prpt-lpt)<10){
    //if(pid==(idpeak-2) ){
    fadd = -1;
    //std::cout<<"previous clus2::"<<", "<<sid1<<", "<< prpt-lpt<<", "<<fl  <<std::endl;
  }
  
  int fmod = -1;
  double sumq = qmax;
  double sumx = qmax*GetPosition(idpeak);

  if(fl<0 && lqmax>(gem_threshold-15) &&fadd>0 && lqmax< qmax){
    fmod  = 1;
    sumq += lqmax;
    sumx += lqmax*GetPosition(idpeak-1);
    strip_ids.push_back(idpeak-1);
    //std::cout<<"add-1::"<<idpeak-1<<", "<<lqmax<<", "<<ltime<<", "<<ltot<<", "<<lpt<<", "<<lst<<", "<<led<<std::endl;
    hit.PushBackStrip2(idpeak-1, GetPosition(idpeak-1), lqmax,  ltime,   ltot,  lpt,  lst,  led, lrt);
    /*
    if(fll<0 && llqmax>50){
      sumq += llqmax;
      sumx += llqmax*GetPosition(idpeak-2);
      strip_ids.push_back(idpeak-2);
      hit.PushBackStrip2(idpeak-2, GetPosition(idpeak-2), llqmax,  lltime,   lltot,  llpt,  llst,  lled, llrt);
    }
    */
  }
  
  if(fr<0 && rqmax>(gem_threshold-15) &&fadd>0 && rqmax<qmax){
    fmod  = 1;
    sumq += rqmax;
    sumx += rqmax*GetPosition(idpeak+1);
    strip_ids.push_back(idpeak+1);
    //std::cout<<"add+1::"<<idpeak+1<<", "<<rqmax<<", "<<rtime<<", "<<rtot<<", "<<rpt<<", "<<rst<<", "<<led<<std::endl;
    hit.PushBackStrip2(idpeak+1, GetPosition(idpeak+1), rqmax,  rtime,   rtot,  rpt,  rst,  red, rrt);
    /*
    if(frr<0 && rrqmax>50){
      sumq += rrqmax;
      sumx += rrqmax*GetPosition(idpeak+2);
      strip_ids.push_back(idpeak+2);
      hit.PushBackStrip2(idpeak+2, GetPosition(idpeak+2), rrqmax,  rrtime,   rrtot,  rrpt,  rrst,  rred, rrrt);
    }
    */
  }
  
  //if(fmod>0&&sid1==1){
  if(fmod>0){
    hit.SetNumHit(strip_ids.size());
      double sumq,sumx;
    sumq=sumx=0;
    for (int i = 0; i < (int)strip_ids.size(); i++) {
      sumx += (double)hit.StripPos(i)*hit.StripCharge(i);
      sumq += (double)hit.StripCharge(i);
    }
    double recog = sumx/sumq;
    hit.SetClusterCharge(sumq);
    hit.SetCogHit(recog);
  }


  
  int sid2 =  (int)strip_ids.size();
  double ced,crt,ctot,cpeak;
  SetArraysForTdcMethods3(strip_ids, x_array, time_array, peak_array, time4, time5,cadc,ced,ctot,crt,cpeak);
  
  temp_num_hit = x_array.size();
  temp_cc = 0.0;
  double wt=0, t=0, sx=0, sy=0, st2=0, ss = 0, sxoss = 0;
  double sx2=0, sxy=0;
  double ftdc = 9999;
  int nn =0;
  double time3=0;
  double sumq2 = 0;//peak sum
  for(int i = 0; i < x_array.size(); i++){
	sumq2 += peak_array[i];
	time3 += peak_array[i] * time_array[i];
    ss  ++;
    sx  += time_array[i] ;
    sy  += x_array[i] ;
    sx2 += time_array[i] *time_array[i] ;
    sxy += x_array[i] * time_array[i] ;
    if(time_array[i]<ftdc){
      ftdc = time_array[i];
    }
    int flag = 1;
    for(int j = 0; j < i; j++){
      if(fabs(x_array[i]-x_array[j])<0.005) flag=-1;
    }
    if(flag>0) nn++;
  }
  double a = sy/x_array.size();
  double b = 0;
  if(nn>1&&sx*sx!=ss*sx2){
    a = (sx*sxy-sx2*sy)/(sx*sx-ss*sx2);       //seppen
    b = (sx*sy-ss*sxy)/(sx*sx-ss*sx2); //katamuki
  }
  double temp_mhit = a+b*ztiming;
  //double temp_mhit = a+b*200;
  time3 = time3/sumq2;
  hit.SetTdcHit(temp_mhit);
  hit.SetTanTheta(b/drift_velocity);
  hit.SetTiming2(ftdc);
  hit.SetTiming(sx/x_array.size());
  hit.SetTiming3(time5);
  hit.SetTiming4(time4);
  
  hit.SetTiming5(time5);
  hit.SetCtot(ctot);
  hit.SetCed(ced);
  hit.SetCrt(crt);
  hit.SetCpeak(cpeak);
  
  for(int i=0; i < xcent.size(); i++){
    hit.SetCTiming(xtime[i]);
    hit.SetCPos(xcent[i]);
    hit.SetCAdc1(adc1[i]);
    hit.SetCAdc2(adc2[i]);
    hit.SetCAdc3(adc3[i]);
    hit.SetCAdc4(adc4[i]);
    hit.SetCAdc5(adc5[i]);
    hit.SetCAdc(cadc[i]);
  }

  for(int i = 0; i < x_array.size(); i++){
    hit.SetCTiming2(time_array[i]);
    hit.SetCPos2(x_array[i]);
  }
  for(int i = 0; i < x_array2.size(); i++){
    hit.SetCTiming3(time_array2[i]);
    hit.SetCPos3(x_array2[i]);
  }
  //std::cout<<"size::"<<x_array3.size()<<", "<<time_array3.size()<<", "<<x_array4.size()<<", "<<time_array4.size()<<std::endl;
  for(int i = 0; i < x_array3.size(); i++){
    hit.SetCTiming4(time_array3[i]);
    hit.SetCPos4(x_array3[i]);
    hit.SetCTiming5(time_array4[i]);
    hit.SetCPos5(x_array4[i]);
  }
  
  //std::cout<< "size::"<<sid1<< ", "<<sid2<<", "<<idpeak<<", "<<strip_ids[sid2-1]<<", "<<hit.CogHit() <<", "<< qmax<<", "<<hit.ClusterCharge()<<", "<<hit.Timing4() <<", "<<hit.Ctot() <<", " <<n_strips <<std::endl;
  /*for(int i=0;i<hit.NumHit();i++){
    std::cout<< "info::"<<hit.StripID(i)<<", "<<hit.StripCharge(i) <<", "<<hit.StripTotSt(i)<<", "<<hit.StripTotEd(i)<<", "<<hit.StripTimeOverThreshold(i)<<", "<<hit.StripRiseTiming(i)<<", "<< hit.StripPos(i)<<std::endl;
  }
  */
}





void E16ANA_GTRStripAnalyzer::CalcTdcHit2(const std::vector<int> &strip_ids, double tan_theta,
                                          E16ANA_GTRAnalyzedStripHit &hit)
{
  /*
   std::vector<double> x_array;
   std::vector<double> time_array;
   std::vector<double> peak_array;

   int temp_num_hit = 0;
   double temp_cc = 0.0;
   double temp_tdc_hit = 0.0;

   if ((int)strip_ids.size() == 0) {
      hit.SetInvalid();
      return;
   }

   SetArraysForTdcMethods(strip_ids, x_array, time_array, peak_array);

   temp_num_hit = x_array.size();
   temp_cc = 0.0;

   double A = 0.0;
   for (int i = 0; i < (int)x_array.size(); i++) {
      A += x_array[i] - tan_theta * time_array[i];
      temp_cc += peak_array[i];
   }
   double tdc_x0 = A / x_array.size();
   temp_tdc_hit = tan_theta * drift_gap_center + tdc_x0;

   hit.SetNumHit(temp_num_hit);
   hit.SetClusterCharge(temp_cc);
   hit.SetTdcHit(temp_tdc_hit);
   hit.SetTanTheta(tan_theta);
   hit.SetTiming(0);
   */
}

/*----------------- Analyze version 2 -----------------*/
/*
void E16ANA_GTRStripAnalyzer::AnalyzeV2(){
   int n_hits = HitClusteringV2();
   std::cout << "E16ANA_GTRStripAnalyzer::AnalyzeV2 : multiplicity = " << n_hits << std::endl;
   gem_analyzed_hits.resize(n_hits);
   for(int i=0; i<n_hits; i++){
      std::cout << "cid = " << i << ", n_signal = " << clustered_x[i].size() << std::endl;
      CalcTdcHit3(false, clustered_x[i], clustered_z[i], clustered_peak[i], gem_analyzed_hits[i], i);
   }
}

void E16ANA_GTRStripAnalyzer::CalcWaveParamsFit(std::vector<fit_params_t> &fit_pars_array){
   fit_pars_array.clear();
   for(int i=0; i<n_strips; i++){
   //for(int i=left_strip_x; i<right_strip_x; i++){
      if(fadc[i][0]<-255.0) continue;
      fit_pars_array.push_back(fit_params_t(i,5));
      this->CalcWaveParamsFit(i, fit_pars_array.back());
   }
}

void E16ANA_GTRStripAnalyzer::CalcWaveParamsFit(int ch, fit_params_t &fit_pars){
   wf1d_fitter->SetWaveform(fadc[ch], n_sampling);
   wf1d_fitter->SetNumWaveforms(3);
   wf1d_fitter->Fit();
   const double merge_time = 50.0;
   double time = wf1d_fitter->GetWaveformTime(0);
   double peak = wf1d_fitter->GetWaveformPeak(0);
   double pre_time = time;
   for(int i=1; i<wf1d_fitter->GetNumWaveforms(); i++){
      double temp_time = wf1d_fitter->GetWaveformTime(i);
      double temp_peak = wf1d_fitter->GetWaveformPeak(i);
      if(temp_time > (pre_time+merge_time)){
         time /= peak;
         if(peak>10.0 && time>20.0 && time<700.0){
            //std::cout << "StripID = " << ch << ", Time = " << time << ", Peak = " << peak << std::endl;
            fit_pars.times.push_back(time);
            fit_pars.peaks.push_back(peak);
         }
         time = 0.0;
         peak = 0.0;
         pre_time = temp_time;
      }
      peak += temp_peak;
      time += temp_peak*temp_time; // cog merge
   }
   if(peak>10.0 && time>20.0 && time<700.0){
      time /= peak;
      //std::cout << "StripID = " << ch << ", Time = " << time << ", Peak = " << peak << std::endl;
      fit_pars.times.push_back(time+fadc_t0_correction);
      fit_pars.peaks.push_back(peak);
   }
}

int E16ANA_GTRStripAnalyzer::HitClusteringV2(const int min_gap, const double delta_tdc_threshold){
   std::vector<fit_params_t> fit_pars;
   CalcWaveParamsFit(fit_pars);
   clustered_x.clear();
   clustered_z.clear();
   clustered_peak.clear();

   std::vector<fit_params_t>::iterator it = fit_pars.begin();

   double pre_tdc = -10000.0;
   int pre_strip_id = -100;
   while(!fit_pars.empty()){
      if(it == fit_pars.end()){
         pre_tdc = -10000.0;
         pre_strip_id = -100;
         it = fit_pars.begin();
      }
      int signal_gap = (*it).strip_id-pre_strip_id;
      int min_j = -1;
      double min_delta_tdc = 1000000.0;
      for(int j=0; j<(int)(*it).peaks.size(); j++){
         if(fabs((*it).times[j]-pre_tdc)<min_delta_tdc){
            min_j = j;
            min_delta_tdc = fabs((*it).times[j]-pre_tdc);
         }
      }
      //std::cout << "min_j = " << min_j << ", delta_tdc = " << min_delta_tdc << std::endl;
      if(min_j < 0){
         it = fit_pars.erase(it);
         continue;
      }
      double delta_tdc = min_delta_tdc;
      if(signal_gap>min_gap){
         clustered_x.push_back(std::vector<double>());
         clustered_z.push_back(std::vector<double>());
         clustered_peak.push_back(std::vector<double>());
         //pre_tdc = (*it).times[min_j];
         //pre_strip_id = (*it).strip_id;
         //clustered_x.back().push_back(GetPosition(pre_strip_id));
         //clustered_z.back().push_back(pre_tdc*drift_velocity-drift_gap_center);
         //clustered_peak.back().push_back((*it).peaks[min_j]);
         //(*it).times.erase((*it).times.begin()+min_j);
         //(*it).peaks.erase((*it).peaks.begin()+min_j);
      }
      //if(signal_gap<=min_gap && fabs(delta_tdc)<delta_tdc_threshold){ // V1
      if(signal_gap>min_gap || fabs(delta_tdc)<delta_tdc_threshold){
         pre_tdc = (*it).times[min_j];
         pre_strip_id = (*it).strip_id;
         std::cout << "cid = " << clustered_x.size()-1 << ", t = " << pre_tdc
            << ", sid = " << pre_strip_id
            << ", peak = " << (*it).peaks[min_j] << std::endl;
         clustered_x.back().push_back(GetPosition(pre_strip_id));
         clustered_z.back().push_back(pre_tdc*drift_velocity-drift_gap_center);
         clustered_peak.back().push_back((*it).peaks[min_j]);
         (*it).times.erase((*it).times.begin()+min_j);
         (*it).peaks.erase((*it).peaks.begin()+min_j);
      }
      it++;
   }
   return clustered_x.size();
}

void E16ANA_GTRStripAnalyzer::AnalyzeV2(int id){
   CalcTdcHit3(true, clustered_x[id], clustered_z[id], clustered_peak[id], gem_analyzed_hits[id], id);
}
*/
/*----------------- Analyze version 2 -----------------*/

/*----------------- Analyze version 3 -----------------*/
/*
void E16ANA_GTRStripAnalyzer::AnalyzeV3(){
   clustered_x.clear();
   clustered_z.clear();
   clustered_peak.clear();
   int n_hits = HitClusteringV3(clustered_x, clustered_z, clustered_peak);
   //std::cout << "E16ANA_GTRStripAnalyzer::AnalyzeV3 : multiplicity = " << n_hits << std::endl;
   gem_analyzed_hits.resize(n_hits);
   for(int i=0; i<n_hits; i++){
      CalcTdcHit3(false, clustered_x[i], clustered_z[i], clustered_peak[i], gem_analyzed_hits[i], i);
   }
}

//void E16ANA_GTRStripAnalyzer::CalcClusterParams(
//      std::vector<double> &v1_pos,
//      std::vector<double> &v1_time,
//      std::vector<double> &v1_peak
//      ){
void E16ANA_GTRStripAnalyzer::CalcClusterParams(std::vector<cluster_param_t> &v1){
   HitClusteringV0(1, 30.0); // Pre clustering
   //E16ANA_Waveform2dFitter *wf_fitter = new E16ANA_Waveform2dFitter();
   for(int i=0; i<(int)clustered_strip_id.size(); i++){
      std::vector<int> &strips = clustered_strip_id[i];
      wf2d_fitter->Clear();
      //wf2d_fitter->SetNumClusters(ceil((double)strips.size()/2.5));
      wf2d_fitter->SetNumClusters(ceil((double)strips.size()/1.5));
      for(int j=0; j<(int)strips.size(); j++){
         double pos = GetPosition(strips[j]);
         wf2d_fitter->AddWaveform(pos, fadc[strips[j]], n_sampling);
      }
      wf2d_fitter->Fit();
      for(int n=0; n<wf2d_fitter->GetNumClusters(); n++){
         //v1_pos.push_back(wf2d_fitter->GetClusterPos(n));
         //v1_time.push_back(wf2d_fitter->GetClusterTime(n)+fadc_t0_correction);
         //v1_peak.push_back(wf2d_fitter->GetClusterPeak(n));
         v1.push_back(cluster_param_t(
                  wf2d_fitter->GetClusterPos(n),
                  wf2d_fitter->GetClusterTime(n)+fadc_t0_correction,
                  wf2d_fitter->GetClusterPeak(n)
                  ));
      }
   }
   //delete wf_fitter;
}

int E16ANA_GTRStripAnalyzer::HitClusteringV3(
      std::vector<std::vector<double> > &v2_x,
      std::vector<std::vector<double> > &v2_z,
      std::vector<std::vector<double> > &v2_peak
      ){
   const double cluster_peak_threshold = 10.0;
   const double cluster_min_distance = 2.0; // mm
   //const double cluster_min_distance = 1.0; // mm
   //const double cluster_min_distance = 0.5; // mm

   //std::vector<double> v1_pos; // sorted by pos
   //std::vector<double> v1_time; // sorted by pos
   //std::vector<double> v1_peak; // sorted by pos
   //CalcClusterParams(v1_pos, v1_time, v1_peak);
   std::vector<cluster_param_t> v1; // sorted by pos
   CalcClusterParams(v1);

   if((int)v1.size() == 0){
      return 0;
   }

   double pre_x = -10000.0;
   double pre_z = -10000.0;
   double dist = 10000.0;
   double min_distance = 1000.0;
   std::vector<cluster_param_t>::iterator it = v1.begin();
   while(it != v1.end()){
      //std::cout << "v1.size() = " << v1.size() << std::endl;
      if((*it).peak < cluster_peak_threshold){
         it = v1.erase(it);
         continue;
      }
      if(min_distance > cluster_min_distance){
         it = v1.begin();
         v2_x.push_back(std::vector<double>());
         v2_z.push_back(std::vector<double>());
         v2_peak.push_back(std::vector<double>());
      }
      pre_x = (*it).pos;
      pre_z = ((*it).time)*drift_velocity-drift_gap_center;
      v2_x.back().push_back(pre_x);
      v2_z.back().push_back(pre_z);
      v2_peak.back().push_back((*it).peak);
      it = v1.erase(it);

      min_distance = 1000.0;
      //std::vector<cluster_param_t>::iterator min_it;
      std::vector<cluster_param_t>::iterator it_temp = v1.begin();
      while(it_temp != v1.end()){
         double cur_x = (*it_temp).pos;
         double cur_z = ((*it_temp).time)*drift_velocity-drift_gap_center;
         dist = sqrt((pre_x-cur_x)*(pre_x-cur_x)+(pre_z-cur_z)*(pre_z-cur_z));
         if((cur_x-pre_x) > cluster_min_distance) break;
         if(dist < min_distance){
            //min_it = it_temp;
            it = it_temp;
            min_distance = dist;
         }
         it_temp++;
      }
      //std::cout << "distance = " << min_distance << " [mm]" << std::endl;
   }
   // fiducial cut
   double fiducial_min = -2.0;
   double fiducial_max =  2.0;
   std::vector<std::vector<double> >::iterator it_z = v2_z.begin();
   std::vector<std::vector<double> >::iterator it_x = v2_x.begin();
   std::vector<std::vector<double> >::iterator it_peak = v2_peak.begin();
   while(it_z != v2_z.end()){
      double min_z =  1000.0;
      double max_z = -1000.0;
      for(int i=0; i<(int)it_z->size(); i++){
         if(min_z > it_z->at(i)) min_z = it_z->at(i);
         if(max_z < it_z->at(i)) max_z = it_z->at(i);
      }
      if(min_z < fiducial_min || max_z > fiducial_max){
         it_z = v2_z.erase(it_z);
         it_x = v2_x.erase(it_x);
         it_peak = v2_peak.erase(it_peak);
      }else{
         it_z++;
         it_x++;
         it_peak++;
      }
   }
   return v2_x.size();
}

void E16ANA_GTRStripAnalyzer::CalcTdcHit3(
      bool fix_flag,
      const std::vector<double> &x,
      const std::vector<double> &z,
      const std::vector<double> &peak,
      E16ANA_GTRAnalyzedStripHit &hit, int hitID){

   //int temp_max_strip = -1;
   //double temp_max_value = -255.0;
   int temp_num_hit = 0;
   double temp_cc = 0.0;
   double temp_tdc_hit = 0.0;
   double temp_tan_theta = 0.0;

   if((int)x.size()==0){
      hit.SetInvalid();
      return;
   }

   temp_num_hit = x.size();
   temp_cc = 0.0;

   //if(fabs(hit.TanTheta()) > 2.0){
   if(!fix_flag){
      double B= 0.0;
      double C= 0.0;
      double D= 0.0;
      double E= 0.0;

      for(int i=0; i<(int)x.size(); i++){
         B+= x[i]*x[i];
         C+= z[i];
         D+= x[i]*z[i];
         E+= x[i];
         temp_cc += peak[i];
         //std::cout << "(x, z, p) = (" << x[i] << ", " << z[i] << ", " << peak[i] << ")" << std::endl;
         hit.PushBackStrip(x[i], peak[i], z[i]);
      }
      //std::cout << std::endl;

      if((int)x.size() > 1){
         double dzdx = (x.size()*D-C*E)/(x.size()*B-E*E);
         double z0 = (B*C-D*E)/(x.size()*B-E*E);
         temp_tan_theta= 1.0/dzdx;
         //temp_tdc_hit= (drift_gap_center-z0)/dzdx;
         temp_tdc_hit= -z0/dzdx;
      }else if((int)x.size() == 1){
         temp_tan_theta = 0.0;
         temp_tdc_hit = E;
      }
   }else{
      double A= 0.0;
      for(int i=0; i<(int)x.size(); i++){
         A += x[i]-hit.TanTheta()*z[i];
         temp_cc += peak[i];
      }
      double tdc_x0 = A/x.size();
      //temp_tdc_hit = hit.TanTheta()*drift_gap_center+tdc_x0;
      temp_tdc_hit = tdc_x0;
   }

   double temp_cog = 0.0;
   for(int i=0; i<(int)x.size(); i++){
      //temp_cog += x[i]/(double)x.size();
      temp_cog += x[i]*peak[i]/temp_cc;
   }

   hit.SetCogHit(temp_cog);
   hit.SetNumHit(temp_num_hit);
   hit.SetClusterCharge(temp_cc);
   hit.SetTdcHit(temp_tdc_hit);
   hit.SetTanTheta(temp_tan_theta);
   hit.SetID(hitID);

}

void E16ANA_GTRStripAnalyzer::AnalyzeV3(int id){
   CalcTdcHit3(true, clustered_x[id], clustered_z[id], clustered_peak[id], gem_analyzed_hits[id], id);
}
*/
/*----------------- Analyze version 3 -----------------*/
