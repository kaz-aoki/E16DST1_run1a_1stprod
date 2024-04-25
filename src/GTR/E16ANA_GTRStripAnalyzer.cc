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
     gem_tdc_min(-10000.0), gem_tdc_max(10000.0), gem_tr(75.0), threshold_fraction(0.5), inverted(1.0),cluster_minimum_gap(2), cluster_delta_tdc(10000.0),  
     rise_time_min(-10000.0),   rise_time_max(10000.0),
     peak_time_min(-10000.0),   peak_time_max(10000.0)

{
   fadc = new double *[n_strips];
   for (int i = 0; i < n_strips; i++) {
      fadc[i] = new double[n_sampling];
   }
   fadc_peak = new double[n_strips];
   fadc_peak_time = new double[n_strips];
   fadc_peak_tdc  = new double[n_strips];
   fadc_tdc = new double[n_strips];
   fadc_tot = new double[n_strips];
   fadc_ped = new double[n_strips];
   fadc_ped_sigma = new double[n_strips];
   fadc_peak_st = new double[n_strips];//tot start time
   fadc_peak_ed = new double[n_strips];//tot end time
   fadc_rise = new double[n_strips];//peak time - tot start
   gem_analyzed_hits.reserve(20);
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
   delete[] fadc_peak;
   delete[] fadc_peak_time;
   delete[] fadc_peak_tdc;
   delete[] fadc_tdc;
   delete[] fadc_tot;
   delete[] fadc_ped;
   delete[] fadc_ped_sigma;
   delete[] fadc_rise;
   delete[] fadc_peak_st;
   delete[] fadc_peak_ed;
   
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

void E16ANA_GTRStripAnalyzer::SetFadc(int strip_id, int16_t *waveform)
{

  /*
  double local_pedestal = 0.0;
   for (int j = 0; j < 5; j++) {
     local_pedestal += waveform[j];
   }
   local_pedestal /= 5.0;
  */

   for (int j = 0; j < n_sampling; j++) {
     fadc[strip_id][j] = waveform[j] - fadc_ped[strip_id];
//	if(strip_id == 700 && j == 0){
//	 std::cout  << "fadc   = " << fadc[strip_id][j] << std::endl; 
//	}
     //fadc[strip_id][j] = waveform[j] - local_pedestal;
      if( strip_id== 100 ){
//        std::cout << "wave form j0 = " << waveform[j] << ", ped = "  <<fadc_ped[strip_id] << ", sigma = "<< fadc_ped_sigma[strip_id] <<  std::endl;
      }
   }
}

bool E16ANA_GTRStripAnalyzer::IsBadStrip(int strip_id)
{
   if (fabs(fadc_ped[strip_id]) > bad_pedestal_threshold) {
      return true;
   }
   if (fadc_ped_sigma[strip_id] > bad_pedestal_sigma_threshold) {
      return true;
   }
   if (fadc_ped_sigma[strip_id] < 2.0) { // too small
      return true;
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
   for (int i = 0; i < n_hits; i++) {
      gem_analyzed_hits[i].SetInvalid();
      CalcCenterOfGravity(clustered_strip_id[i], gem_analyzed_hits[i]);
      //CalcTdcHit1(clustered_strip_id[i], gem_analyzed_hits[i], i);
      //CalcTdcHit12(clustered_strip_id[i], gem_analyzed_hits[i], i);
      CalcTdcHit12V2(clustered_strip_id[i], gem_analyzed_hits[i], i);
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
   // gem_analyzed_hits.resize(n_hits,E16ANA_GTRAnalyzedStripHit());
   for (int i = 0; i < n_hits; i++) {
      gem_analyzed_hits[i].SetInvalid();
      CalcCenterOfGravity(clustered_strip_id[i], gem_analyzed_hits[i]);
      //CalcTdcHit1(clustered_strip_id[i], gem_analyzed_hits[i], i);
//      CalcTdcHit12(clustered_strip_id[i], gem_analyzed_hits[i], i);//original
      CalcTdcHit12V2(clustered_strip_id[i], gem_analyzed_hits[i], i);//morino ver
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
   CalcWaveParamsPeak();
   // const int min_gap = 2;
   int signal_gap = 100;

   for (int i = 0; i < (int)clustered_strip_id.size(); i++) {
      clustered_strip_id[i].clear();
   }
   clustered_strip_id.clear();

   // double pre_tdc = fadc_tdc[0];

   for (int i = 0; i < n_strips; i++) {
      // gem_threshold = 4.0 * fadc_ped_sigma[i]; // 4sigma
//      std::cout << "i  = " << i << ", peak = " << fadc_peak[i] << std::endl;
      if (fadc_peak[i] > 0.0 && fadc_peak_time[i] > 0.0) {
         // double delta_tdc = fadc_tdc[i]-pre_tdc;
         // pre_tdc = fadc_tdc[i];
         // if(signal_gap>=min_gap || fabs(delta_tdc)>100.0){ // V1
         if (signal_gap >= min_gap) { // V0
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
   return clustered_strip_id.size();
}

int E16ANA_GTRStripAnalyzer::HitClusteringV1(){
  return HitClusteringV1(cluster_minimum_gap, cluster_delta_tdc);
  //return HitClusteringV1(2, 150);
}

int E16ANA_GTRStripAnalyzer::HitClusteringV1(const int min_gap, const double delta_tdc_threshold)
{
   CalcWaveParamsPeak();
   // const int min_gap = 2;
   int signal_gap = 100;
   // const double delta_tdc_threshold = 150.0;

   for (int i = 0; i < (int)clustered_strip_id.size(); i++) {
      clustered_strip_id[i].clear();
   }
   clustered_strip_id.clear();

   double pre_tdc = fadc_tdc[0];

   for (int i = 0; i < n_strips; i++) {
      // gem_threshold = 4.0 * fadc_ped_sigma[i]; // 4sigma
      if (fadc_peak[i] > 0.0 && fadc_peak_time[i] > 0.0) {
         double delta_tdc = fadc_tdc[i] - pre_tdc;
//		 std::cout << "fadc tdc " << fadc_tdc[i] << std::endl;
         pre_tdc = fadc_tdc[i];
         if (signal_gap >= min_gap || fabs(delta_tdc) > delta_tdc_threshold) { // V1
            // if(signal_gap>=min_gap){ // V0
            clustered_strip_id.push_back(std::vector<int>());
         }
         clustered_strip_id.back().push_back(i);
         signal_gap = 0;
      } else {
         signal_gap++;
      }
   }
   return clustered_strip_id.size();
}

void E16ANA_GTRStripAnalyzer::CalcWaveParamsPeak()
{
   for (int i = 0; i < n_strips; i++) {
      fadc_peak[i] = -255.0;
      fadc_peak_time[i] = -1000.0;
      fadc_tdc[i] = -1000.0;
	  fadc_peak_st[i] = -1000.0;
	  fadc_peak_ed[i] = -1000.0;
	  
   }

   for (int i = 0; i < n_strips; i++) {
      // for(int i=left_strip_x; i<right_strip_x; i++){
      if (fadc[i][0] < -255.0) {
         continue;
      }
      if (IsBadStrip(i)) {
         continue;
      }
      // gem_threshold = 4.0 * fadc_ped_sigma[i]; // 4sigma
      this->CalcWaveParamsPeak(i, 10000.0);
      // this->CalcWaveParamsPeak(i, gem_tdc_max+gem_tr+50.0);
      // if(fadc_tdc[i]>gem_tdc_max){
      //   this->CalcWaveParamsPeak(i, gem_tdc_max-gem_tr);
      //}
   }
}

void E16ANA_GTRStripAnalyzer::CalcWaveParamsPeak(int ch, double t_cutoff)
{
   int peak_count;
   double tot_start = 1000.0;
   double tot_end = 0.0;
   if (ch < n_strips) {
      fadc_peak[ch] = -255.0;
      fadc_tdc[ch] = -1000.0;
      fadc_tot[ch] = -1000.0;
      fadc_peak_time[ch] = -1000.0;
      fadc_peak_tdc[ch]  = -1000.0;
	  fadc_peak_st[ch]   = -1000;
	  fadc_peak_ed[ch]   = -1000;
	  fadc_rise[ch]   = -1000;
	  
      peak_count = -1;
      for (int j = 0; j < n_sampling; j++) {
         // for(int l=0; l<(int)fadc_valid_count.size(); l++){
         // int j= fadc_valid_count[l];
         double tdc_j = j * fadc_clock_period + fadc_t0_correction;
//		 std::cout << "j, fadc_period, t0" << j << ", " << fadc_clock_period << ", " << fadc_t0_correction << std::endl;
         if (tdc_j > t_cutoff)
            break;
         // if(tdc_j<t_cutoff) continue;

         if (fadc_peak[ch] < fadc[ch][j]) {
            fadc_peak[ch] = fadc[ch][j];
	    fadc_peak_time[ch] = j * fadc_clock_period + fadc_t0_correction;
	    fadc_peak_tdc[ch] = j ;
            peak_count = j;
         }
      }
//	  std::cout << "ch = " << ch << ", peak   = " << fadc_peak[ch] << std::endl; 
      if (fadc_peak[ch] < gem_threshold ||  fadc_peak[ch] > 4000) {
         fadc_peak[ch] = -255.0;
         peak_count = -1;
      } else {
//        std::cout << "Peak detection, peak_value = " << fadc_peak[ch] << ", peak_count = " << peak_count <<   std::endl;
      }

      if (peak_count > -1) {
         for (int j = peak_count; j > -1; j--) {
            if (fadc[ch][j] < fadc_peak[ch] * threshold_fraction) {
               // double tdc_j = j;
               double w_j0 = fadc_peak[ch] * threshold_fraction - fadc[ch][j];
               double w_j1 = -fadc_peak[ch] * threshold_fraction + fadc[ch][j + 1];
               double tdc_j = (j * w_j1 + (j + 1.0) * w_j0) / (w_j0 + w_j1);
               // std::cout << "tdc_j = " << tdc_j << std::endl;
               fadc_tdc[ch] = tdc_j * fadc_clock_period + fadc_t0_correction;
               tot_start = fadc_tdc[ch];
       //        fadc_peak_time[ch] = peak_count * fadc_clock_period + fadc_t0_correction;
               break;
            }
         }
         for (int j = peak_count; j < n_sampling; j++) {
            if (fadc[ch][j] < fadc_peak[ch] * threshold_fraction) {
               // double tdc_j = j;
               double w_j0 = fadc_peak[ch] * threshold_fraction - fadc[ch][j - 1];
               double w_j1 = -fadc_peak[ch] * threshold_fraction + fadc[ch][j];
               double tdc_j = (j * w_j1 + (j + 1.0) * w_j0) / (w_j0 + w_j1);
               tot_end = tdc_j * fadc_clock_period + fadc_t0_correction;
               break;
            }
         }
		 fadc_peak_st[ch] = tot_start;
		 fadc_peak_ed[ch] = tot_end;
         fadc_tot[ch] = tot_end - tot_start;
		 fadc_rise[ch] = fadc_peak_time[ch] - tot_start;
	 //std::cout << fadc_tot[ch] << ", " << tot_start << ", " << tot_end << 
	 //  std::endl;
// 230207 changed for a test, originally Morino Update was used
//         if (fadc_tot[ch] < gem_tot_threshold ) { // Original
         //if (fadc_tot[ch] < gem_tot_threshold && fadc_tot[ch] > 0 ) {
//	 if (tot_end - fadc_peak_time[ch] < gem_tot_threshold 	 && fadc_tot[ch] > 0 ) { // Morino Updates
//	 if (tot_end - fadc_peak_time[ch] < gem_tot_threshold 	 && fadc_tot[ch] > gem_tot_threshold ) { // murakami
	 if (fadc_tot[ch] < gem_tot_threshold ) { // murakami
	 //if (fabs(fadc_tot[ch]) < gem_tot_threshold) { // Morino
            fadc_peak[ch] = -255.0;
            fadc_tdc[ch] = -1000.0;
            fadc_peak_time[ch] = -1000.0;
	    fadc_peak_tdc[ch]  = -1000.0;
            peak_count = -1;
//			std::cout << "tot cut " << std::endl;
         }
      } else {//peakcount == -1
         fadc_tdc[ch] = -1000.0;
         fadc_peak_time[ch] = -1000.0;
//		std::cout << "peak count is -1 " << std::endl;
      }
//230207 comment out for a test
//      if (fadc_tdc[ch] > gem_tdc_max || fadc_tdc[ch] < gem_tdc_min ||
//	  fadc_peak_time[ch] > peak_time_max || 
//	  fadc_peak_time[ch] < peak_time_min ||
//	  (fadc_peak_time[ch] - fadc_tdc[ch]) > rise_time_max ||
//	  (fadc_peak_time[ch] - fadc_tdc[ch]) < rise_time_min 
//	  ) {
//         fadc_tdc[ch] = -1000.0;
//         fadc_peak_time[ch] = -1000.0;
//	 fadc_peak_tdc[ch]  = -1000.0;
//      }
//	std::cout << "fadc_tdc :" << fadc_tdc[ch] << std::endl;

      if (fadc_tdc[ch] > gem_tdc_max || fadc_tdc[ch] < gem_tdc_min) {
         fadc_tdc[ch] = -1000.0;
         fadc_peak_time[ch] = -1000.0;
      }
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

   if ((int)strip_ids.size() == 0) {
      hit.SetInvalid();
      return;
   }

   for (int i = 0; i < (int)strip_ids.size(); i++) {
      int id = strip_ids[i];
      if (fadc_peak[id] > temp_max_value) {
         temp_max_strip = id;
         temp_max_value = fadc_peak[id];
	      temp_tot       = fadc_tot[id];
         temp_rise      = fadc_rise[id];
      }
      temp_num_hit++;
      temp_cc += fadc_peak[id];
      // temp_cog += fadc_peak[id]*id;
      temp_cog += fadc_peak[id] * GetPosition(id);
//      hit.PushBackStrip(id, GetPosition(id), fadc_peak[id], fadc_tdc[id], fadc_tot[id], fadc[id]);//original
      hit.PushBackStrip(id, GetPosition(id), fadc_peak[id], fadc_tdc[id], fadc_tot[id],  fadc_peak_time[id], fadc_peak_st[id], fadc_peak_ed[id], fadc_rise[id], fadc[id]);
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
}

void E16ANA_GTRStripAnalyzer::SetArraysForTdcMethods(const std::vector<int> &strip_ids, std::vector<double> &x_array,
                                                     std::vector<double> &time_array, std::vector<double> &peak_array)
{
   //   std::cerr<<std::endl<<"fadctime/peak ";
   for (int i = 0; i < (int)strip_ids.size(); i++) {
      // if(gem_peak_x[i]>gem_th_x && gem_t0_x[i]<800){
      // if(gem_peak_x[i]>gem_th_x && gem_t0_x[i]>0.0 && gem_t0_x[i]<gem_t0_max){
      int id = strip_ids[i];
      // if (fadc_peak[id] > gem_threshold && fadc_tdc[id] > 0.0) {
      // if (fadc_tdc[id] > 0.0) {
      // x_array.push_back(((double)id*strip_pitch+position_start)*inverted);
      x_array.push_back(GetPosition(id));
      time_array.push_back(fadc_tdc[id] * drift_velocity);
      peak_array.push_back(fadc_peak[id]);
      // std::cerr<<id<<" "<<fadc_tdc[id]<<" "<<fadc_peak_time[id]<<" "<<drift_velocity<<" ";
      //}
   }
}

void E16ANA_GTRStripAnalyzer::SetArraysForTdcMethods2(const std::vector<int> &strip_ids, std::vector<double> &x_array,
						      std::vector<double> &time_array, std::vector<double> &peak_array)
{

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


}

void E16ANA_GTRStripAnalyzer::SetArraysForTdcMethods4(const std::vector<int> &strip_ids, std::vector<double> &x_array,
                                                      std::vector<double> &x_array2,std::vector<double> &time_array,
                                                      std::vector<double> &time_array2)
{

  for (int i = 0; i < (int)strip_ids.size(); i++) {
    int id = strip_ids[i];
    int it = fadc_peak_tdc[id];
    int imax    = 1;
    for (int j = 0; j < (int)strip_ids.size(); j++) {
      if(i==j)    continue;
      if(imax<0)  continue;
      int id2     = strip_ids[j];
      double tq   = fadc[id2][it];
      if(tq>fadc[id][it]) imax = -1;
    }
    if(imax<0)  continue;

    double sumq = 0;
    double sumx = 0;
    double sumt = 0;

    for (int j = 0; j < (int)strip_ids.size(); j++) {
      int id2   = strip_ids[j];
      double tq = fadc[id2][it];
      if(tq<0) tq = 0;
      sumq += tq;
      sumx += tq * GetPosition(id2);
      sumt += tq * fadc_tdc[id2];;
    }

    if(sumq>0){
      double lx = sumx/sumq;
      double lt = sumt/sumq;
      x_array.push_back(GetPosition(id));
      time_array.push_back(fadc_tdc[id]);
      x_array2.push_back(lx);
      time_array2.push_back(lt);
    }
  }
}

void E16ANA_GTRStripAnalyzer::SetArraysForTdcMethods3(const std::vector<int> &strip_ids, std::vector<double> &x_array,
                                                      std::vector<double> &time_array, std::vector<double> &peak_array,
                                                      std::vector<double> &xcent,std::vector<double> &xtime,
                                                      std::vector<double> &adc1,std::vector<double> &adc2,
                                                      std::vector<double> &adc3,std::vector<double> &adc4,
                                                      std::vector<double> &adc5, double &tdc4){

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
  double sadc[n_sampling];
  int    peakc = -1;
  double peakq = -9999;
  for (int i = 0; i < n_sampling; i++) {
    double maxq = -99999;
    int    mid  = -10;
    sadc[i] = 0;
    for (int j = 0; j < (int)strip_ids.size(); j++) {
      int id  = strip_ids[j];
      double tq = fadc[id][i];
      sadc[i] += tq;
      if(tq>maxq) {
        maxq = tq;
        mid  = id;
      }
    }
    if(sadc[i]>peakq){
      peakq = sadc[i];
      peakc = i;
    }
    if(maxq>100){
      double lt = i * fadc_clock_period + fadc_t0_correction;
      double lq = 0;
      double rq = 0;
      if(mid>0)           lq = fadc[mid-1][i];
      if(mid<n_strips-1)  rq = fadc[mid+1][i];
      if(lq<0) lq=0;
      if(rq<0) rq=0;
      double llq = 0;
      double rrq = 0;
      if(mid>1)           llq = fadc[mid-2][i];
      if(mid<n_strips-2)  rrq = fadc[mid+2][i];
      if(llq<0) llq=0;
      if(rrq<0) rrq=0;

      xcent.push_back(GetPosition(mid));
      xtime.push_back(lt);
      adc1.push_back(llq);
      adc2.push_back(lq);
      adc3.push_back(maxq);
      adc4.push_back(rq);
      adc5.push_back(rrq);
    }
  }

  tdc4 = -100;
  if(peakc>-1){
    for (int j = peakc; j > -1; j--) {
      if (sadc[j] < peakq * threshold_fraction) {
        // double tdc_j = j;
        double w_j0 =  peakq * threshold_fraction - sadc[j];
        double w_j1 = -peakq * threshold_fraction + sadc[j+1];
        double tdc_j = (j * w_j1 + (j + 1.0) * w_j0) / (w_j0 + w_j1);
        tdc4 = tdc_j * fadc_clock_period + fadc_t0_correction;
        break;
      }
    }
  }

}




void E16ANA_GTRStripAnalyzer::CalcTdcHit1(const std::vector<int> &strip_ids, E16ANA_GTRAnalyzedStripHit &hit, int hitID)
{
   std::vector<double> x_array;
   std::vector<double> time_array;
   std::vector<double> peak_array;

   // int temp_max_strip = -1;
   // double temp_max_value = -255.0;
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
      //      std::cerr<<time_array[i]<<" ";
      // hit.PushBackStrip(x_array[i], peak_array[i], time_array[i]);
   }

   double dtdx = (x_array.size() * D - C * E) / (x_array.size() * B - E * E);
   double t0 = (B * C - D * E) / (x_array.size() * B - E * E);
   temp_tan_theta = 1.0 / dtdx;
   temp_tdc_hit = (drift_gap_center - t0) / dtdx;

   // hit.SetMaxStrip(temp_max_strip);
   // hit.SetMaxValue(temp_max_value);
   hit.SetNumHit(temp_num_hit);
   hit.SetClusterCharge(temp_cc);
   hit.SetTdcHit(temp_tdc_hit);
   hit.SetTanTheta(temp_tan_theta);

   hit.SetID(hitID);

   double meantime = C / drift_velocity / x_array.size(); // cluster mean
   hit.SetTiming(meantime);
   //   std::cerr<<"t0/mean "<<t0<<" "<<meantime<<std::endl;
   //   t0 is bad
}

void E16ANA_GTRStripAnalyzer::CalcTdcHit12(const std::vector<int> &strip_ids, E16ANA_GTRAnalyzedStripHit &hit, int hitID)
{// updated to morino-ana 
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


}

void E16ANA_GTRStripAnalyzer::CalcTdcHit12V2(const std::vector<int> &strip_ids, E16ANA_GTRAnalyzedStripHit &hit, int hitID)
{// updated to morino-ana 
  std::vector<double> x_array, x_array2, x_array3, x_array4;
  std::vector<double> time_array, time_array2, time_array3, time_array4;
  std::vector<double> peak_array,peak_array2;
  std::vector<double> xcent;
  std::vector<double> xtime;
  std::vector<double> adc1, adc2, adc3, adc4, adc5;
  int temp_num_hit = 0;
  double temp_cc = 0.0;
  double temp_tdc_hit = 0.0;
  double temp_tan_theta = 0.0;
  double time4;

  if ((int)strip_ids.size() == 0) {
    hit.SetInvalid();
    return;
  }
  //SetArraysForTdcMethods2(strip_ids, x_array, time_array, peak_array);
  SetArraysForTdcMethods(strip_ids, x_array2, time_array2, peak_array2);
  SetArraysForTdcMethods3(strip_ids, x_array, time_array, peak_array, xcent, xtime, adc1, adc2, adc3,adc4, adc5, time4);
  SetArraysForTdcMethods4(strip_ids, x_array3, x_array4, time_array3, time_array4);
  temp_num_hit = x_array.size();
  temp_cc = 0.0;
  double wt=0, t=0, sx=0, sy=0, st2=0, ss = 0, sxoss = 0;
  double sx2=0, sxy=0;
  double ftdc = 9999;
  int nn =0;
  double time3=0;
  double sumq = 0;//peak sum
  for(int i = 0; i < x_array.size(); i++){
	sumq += peak_array[i];
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
  time3 = time3/sumq;
  hit.SetTdcHit(temp_mhit);
  hit.SetTanTheta(b/drift_velocity);
  hit.SetTiming2(ftdc);
  hit.SetTiming(sx/x_array.size());
  hit.SetTiming3(time3);
  hit.SetTiming4(time4);
  for(int i=0; i < xcent.size(); i++){
    hit.SetCTiming(xtime[i]);
    hit.SetCPos(xcent[i]);
    hit.SetCAdc1(adc1[i]);
    hit.SetCAdc2(adc2[i]);
    hit.SetCAdc3(adc3[i]);
    hit.SetCAdc4(adc4[i]);
    hit.SetCAdc5(adc5[i]);
  }

  for(int i = 0; i < x_array.size(); i++){
    hit.SetCTiming2(time_array[i]);
    hit.SetCPos2(x_array[i]);
  }
  for(int i = 0; i < x_array2.size(); i++){
    hit.SetCTiming3(time_array2[i]);
    hit.SetCPos3(x_array2[i]);
  }
  for(int i = 0; i < x_array3.size(); i++){
    hit.SetCTiming4(time_array3[i]);
    hit.SetCPos4(x_array3[i]);
	hit.SetCTiming5(time_array4[i]);
	hit.SetCPos5(x_array4[i]);
  }

}





void E16ANA_GTRStripAnalyzer::CalcTdcHit2(const std::vector<int> &strip_ids, double tan_theta,
                                          E16ANA_GTRAnalyzedStripHit &hit)
{
   std::vector<double> x_array;
   std::vector<double> time_array;
   std::vector<double> peak_array;

   // int temp_max_strip = -1;
   // double temp_max_value = -255.0;
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

   // hit.SetMaxStrip(temp_max_strip);
   // hit.SetMaxValue(temp_max_value);
   hit.SetNumHit(temp_num_hit);
   hit.SetClusterCharge(temp_cc);
   hit.SetTdcHit(temp_tdc_hit);
   hit.SetTanTheta(tan_theta);

   hit.SetTiming(0);
   // std::cerr<<"t02 "<<std::endl;
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
