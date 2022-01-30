// 2015-11-02, uploaded by yokkaich
// 2015-11-02, uploaded by komatsu
// 2015-10-05, uploaded by yokkaich
// 2015-07-15, uploaded by nakai
// 2015-05-29, uploaded by yokkaich
// 2015-04-08, uploaded by nakai

#include <iostream>
#include <cmath>
//#include "/ccj/u/E16/include/root-v5.34.02/TF1.h"
//#include "/ccj/u/E16/include/root-v5.34.02/TGraph.h"
#include <TF1.h>
#include <TH1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>

#include "E16ANA_SSDStripAnalyzer.h"
//#include "E16ANA_WaveformFitter.h"
//#include "E16ANA_Waveform2dFitter.h"

using namespace std;

E16ANA_SSDStripAnalyzer::E16ANA_SSDStripAnalyzer(int _n_strips, int _n_sampling)
   : n_strips(_n_strips), n_sampling(_n_sampling), strip_pitch(0.08), ssd_threshold(4.0), ssd_tot_threshold(-10000.0),
//     drift_velocity(0.010), drift_gap_center(0.0), 
     fadc_clock_period(25.0), fadc_t0_correction(0.0),
     //fadc_clock_period(8.0), fadc_t0_correction(0.0),
     ssd_tdc_min(-10000.0), ssd_tdc_max(10000.0), ssd_tr(75.0), threshold_fraction(0.5), inverted(1.0) {
   fadc = new double *[n_strips];
   fadc_noPedestal = new double *[n_strips];
   for (int i = 0; i < n_strips; i++) {
      fadc[i] = new double[n_sampling];
      fadc_noPedestal[i] = new double[n_sampling];
   }
   param = new double *[n_strips];
   for (int i = 0; i < n_strips; i++) {
      param[i] = new double[n_sampling];
   }
   fadc_peak = new double[n_strips];
   fadc_peak_time = new double[n_strips];
   fadc_tdc = new double[n_strips];
   fadc_tot = new double[n_strips];
   fadc_ped = new double*[n_strips];

   fadc_fit_scale = new double[n_strips];
   fadc_fit_t0 = new double[n_strips];
   fadc_fit_rise_time = new double[n_strips];

   for (int i = 0; i < n_strips; i++) {
      fadc_ped[i] = new double[n_sampling];
   }
   sample_time = new double[n_sampling];
   adc_strip = new double[n_sampling];
   ssd_analyzed_hits.reserve(20);
   // for (int i = 0; i < n_strips; i++) {
   //   for (int j = 0; j < n_sampling; j++) {
   //     fadc_ped[i][j] = 0.0;
   //   }
   // }
   //   graph_fit = new TGraph;
   // wf1d_fitter = new E16ANA_WaveformFitter();
   // wf2d_fitter = new E16ANA_Waveform2dFitter();
   Clear();
}

E16ANA_SSDStripAnalyzer::~E16ANA_SSDStripAnalyzer() {
   for (int i = 0; i < n_strips; i++) {
     delete[] fadc[i];
     delete[] fadc_noPedestal[i];
     delete[] fadc_ped[i];
   }
   for (int i = 0; i < n_strips; i++) {
     delete[] param[i];
   }
   delete[] fadc;
   delete[] fadc_noPedestal;
   delete[] fadc_peak;
   delete[] fadc_peak_time;
   delete[] fadc_tdc;
   delete[] fadc_tot;
   delete[] fadc_ped;
   delete[] sample_time;
   delete[] adc_strip;

   delete[] fadc_fit_scale;
   delete[] fadc_fit_t0;
   delete[] fadc_fit_rise_time;

   //   delete graph_fit;
   // delete wf1d_fitter;
   // delete wf2d_fitter;
}

void E16ANA_SSDStripAnalyzer::Clear() {
   for (int i = 0; i < n_strips; i++) {
      for (int j = 0; j < n_sampling; j++) {
         fadc[i][j] = -100000.0;
         fadc_noPedestal[i][j] = -100000.0;
      }
   }
}

void E16ANA_SSDStripAnalyzer::SetFadc(int strip_id, int16_t *waveform) {
   for (int j = 0; j < n_sampling; j++) {
      fadc[strip_id][j] = waveform[j] - fadc_ped[strip_id][j];
      fadc_noPedestal[strip_id][j] = waveform[j];
   }
   //cout << "fadc[strip_id][0]=" << fadc[strip_id][0] << endl;
   //cout << "waveform[0]=" << waveform[0] << endl;
   //cout << "fadc_ped["<<strip_id<<"][0]=" << fadc_ped[strip_id][0] << endl;
}

void E16ANA_SSDStripAnalyzer::SetPedestal(int strip_id, double *_fadc_ped) {
   for (int j = 0; j < n_sampling; j++) {
      fadc_ped[strip_id][j] = _fadc_ped[j];
   }
}

void E16ANA_SSDStripAnalyzer::Analyze() {

    CalcWaveParamsPeak();
   int n_hits = HitClusteringV0();
   ssd_analyzed_hits.resize(n_hits);
   // ssd_analyzed_hits.resize(n_hits,E16ANA_SSDAnalyzedStripHit());
   for (int i = 0; i < n_hits; i++) {
      ssd_analyzed_hits[i].SetInvalid();
      CalcCenterOfGravity(clustered_strip_id[i], ssd_analyzed_hits[i]);
//      CalcTdcHit1(clustered_strip_id[i], ssd_analyzed_hits[i], i);
      // CalcTdcHit2(clustered_strip_id[i], ssd_analyzed_hits[i].TanTheta(), ssd_analyzed_hits[i]);
   }
}

void E16ANA_SSDStripAnalyzer::Analyze11() {

  double fit_param[n_strips][3];//3=n_param
  
   CalcWaveParamsPeak();
   HitWaveFitV11();  
  //HitWaveFit_noPedestal();

   int n_hits = HitClusteringV0();//number of cluster
  //std::cout << "n_hits=" << n_hits << std::endl;
  ssd_analyzed_hits.resize(n_hits);
  // ssd_analyzed_hits.resize(n_hits,E16ANA_SSDAnalyzedStripHit());
  for (int i = 0; i < n_hits; i++) {
    ssd_analyzed_hits[i].SetInvalid();
    CalcCenterOfGravity(clustered_strip_id[i], ssd_analyzed_hits[i]);
  }
}


//int E16ANA_SSDStripAnalyzer::HitClusteringV0() { return HitClusteringV0(2, -10000.0); }

int E16ANA_SSDStripAnalyzer::HitClusteringV0() { return HitClusteringV0(1, -10000.0); }

int E16ANA_SSDStripAnalyzer::HitClusteringV0(const int min_gap, const double cluster_threshold) {
  //CalcWaveParamsPeak();
   // const int min_gap = 2;
   int signal_gap = 100;

   for (int i = 0; i < (int)clustered_strip_id.size(); i++) {
      clustered_strip_id[i].clear();
   }
   clustered_strip_id.clear();

   //double pre_tdc = fadc_tdc[0];
   double pre_tdc = fadc_fit_t0[0];
   for (int i = 0; i < n_strips; i++) {
      if (fadc_peak[i] > ssd_threshold &&
	  fadc_peak_time[i] > 0 ) {
	//std::cout << fadc_peak_time[i] << std::endl;
	//std::cout << fadc_fit_t0[i] << std::endl;
         // double delta_tdc = fadc_tdc[i]-pre_tdc;
         // pre_tdc = fadc_tdc[i];
          double delta_tdc = fadc_fit_t0[i]-pre_tdc;
          pre_tdc = fadc_fit_t0[i];
          if(signal_gap>=min_gap || fabs(delta_tdc)>10.0){ // V1
         //if (signal_gap >= min_gap) { // V0
	    //cout << "next cluster:" << delta_tdc << endl;
            clustered_strip_id.push_back(std::vector<int>());
         } else if (fadc_peak[i] < cluster_threshold) {
	    //cout << "next cluster:" << delta_tdc << endl;
            clustered_strip_id.push_back(std::vector<int>());
         }
	  //cout << "all:" << delta_tdc << endl;
         clustered_strip_id.back().push_back(i);
         signal_gap = 0;
      } else {
         signal_gap++;
      }
   }
   return clustered_strip_id.size();
}

// int E16ANA_SSDStripAnalyzer::ClusterInfo(vector<int> &strip_ids){
  
//   for(int i=0; i<strip_ids.size; i++){
    
//   }



//   return 0;
// }


int E16ANA_SSDStripAnalyzer::HitClusteringV1(const int min_gap, const double delta_tdc_threshold) {
/*
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
      if (fadc_peak[i] > ssd_threshold) {
         double delta_tdc = fadc_tdc[i] - pre_tdc;
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
*/
}

int E16ANA_SSDStripAnalyzer::getMinSampleNum(std::vector<double>& v_waveform){
  int minSample = -100;
  double minValue = 99999;
  for(int sample=0; sample<v_waveform.size(); sample++){
    if(minValue > v_waveform.at(sample)){
      minValue = v_waveform.at(sample);
      minSample = sample;
    }
  }//for sample
  return minSample;

};

int E16ANA_SSDStripAnalyzer::getMaxSampleNum(std::vector<double>& v_waveform){
  int maxSample = -100;
  double maxValue = -99999;
  for(int sample=0; sample<n_sampling; sample++){
    if(v_waveform.at(sample) > maxValue){
      maxSample = sample;
      maxValue = v_waveform.at(sample);
    }//if
  }//for sample
  return maxSample;
};


double E16ANA_SSDStripAnalyzer::getMin(std::vector<double> v_waveform){
  double min = 99999;
  for(int sample=0; sample<v_waveform.size(); sample++){
    if(min > v_waveform.at(sample)){
      min = v_waveform.at(sample);
    }
  }
  return min;
};

double E16ANA_SSDStripAnalyzer::getMax(std::vector<double> v_waveform){
  double max = -99999;
  for(int sample=0; sample<v_waveform.size(); sample++){
    if(max < v_waveform.at(sample)){
      max = v_waveform.at(sample);
    }
  }
  return max;
};

int E16ANA_SSDStripAnalyzer::classifyWaveType(std::vector<double> v_waveform, int minSampleNum, int maxSampleNum, double minAdcValue){
  int TYPE;
  for(int sample=0; sample<v_waveform.size(); sample++){
    v_waveform.at(sample) -= minAdcValue;
  }//for sample

  if(maxSampleNum == 4){
    if(maxSampleNum == minSampleNum + 3){
      TYPE = 41;
      if(v_waveform.at(minSampleNum+1)
  	> (v_waveform.at(minSampleNum)+v_waveform.at(minSampleNum+2))/2.0)
  	{
  	  TYPE = 411;
  	}
    }
    else if(maxSampleNum == minSampleNum + 2){
      if(v_waveform.at(maxSampleNum-2)<10){
  	TYPE = 421;
      }
      else{
  	TYPE = 42;
      }
    }
    else if(maxSampleNum == minSampleNum + 1){
      TYPE = 43;
    }
    else{
      TYPE = 41;
    }
  }//if maxSampleNum == 4
  else if(maxSampleNum == 3){
    if(maxSampleNum == minSampleNum + 2){
      TYPE = 32;
    }
    else if(maxSampleNum == minSampleNum + 3){
      if(v_waveform.at(minSampleNum)<15){
  	TYPE = 331;
      }
      else{
  	TYPE = 33;
      }
    }
    else{
      TYPE = 31;
    }
  }
  else if(maxSampleNum == 5){
    if(maxSampleNum == minSampleNum + 2){
      TYPE = 511;
    }
    else{
      TYPE = 51;
    }
  }
  else{
    TYPE = 41;
  }

  return TYPE;
};


//int SetRange(int minmax, int waveType, double* sample_time, double maxSampleNum){
void SetRange(int waveType, double* sample_time, int maxSampleNum,
  double& fit_range_min  , double& fit_range_max){
  //  int fit_range_min;
  //  int fit_range_max;

  switch(waveType){
  case 41:
    //cout << waveType << endl;
    fit_range_min
      = sample_time[(int)maxSampleNum-2];
    fit_range_max
      = sample_time[(int)maxSampleNum+3];
    break;
  case 411:
    //cout << waveType << endl;
    fit_range_min
      = sample_time[(int)maxSampleNum-1];
    fit_range_max
      = sample_time[(int)maxSampleNum+3];
    break;
  case 42:
    //cout << waveType << endl;
    fit_range_min
      = sample_time[(int)maxSampleNum-2];
    fit_range_max
      = sample_time[(int)maxSampleNum+3];
    break;
  case 421:
    //cout << waveType << endl;
    fit_range_min
      = sample_time[(int)maxSampleNum-1];
    fit_range_max
      = sample_time[(int)maxSampleNum+3];
    break;
  case 43:
    //cout << waveType << endl;
    fit_range_min
      = sample_time[(int)maxSampleNum];
    fit_range_max
      = sample_time[(int)maxSampleNum+3];
    break;
  case 31:
    //cout << waveType << endl;
    fit_range_min
      = sample_time[(int)maxSampleNum-2];
    fit_range_max
      = sample_time[(int)maxSampleNum+3];
    break;
  case 32:
    fit_range_min
      = sample_time[(int)maxSampleNum-1];
    fit_range_max
      = sample_time[(int)maxSampleNum+4];
    break;
  case 33:
    fit_range_min
      = sample_time[(int)maxSampleNum-2];
    fit_range_max
      = sample_time[(int)maxSampleNum+4];
    break;
  case 331:
    fit_range_min
      = sample_time[(int)maxSampleNum-1];
    fit_range_max
      = sample_time[(int)maxSampleNum+4];
    break;
  case 51:
    fit_range_min
      = sample_time[(int)maxSampleNum-2];
    fit_range_max
      = sample_time[(int)maxSampleNum+2];
    break;
  case 511:
    fit_range_min
      = sample_time[(int)maxSampleNum-1];
    fit_range_max
      = sample_time[(int)maxSampleNum+2];
    break;
  case 61:
    fit_range_min
      = sample_time[(int)maxSampleNum-2];
    fit_range_max
      = sample_time[(int)maxSampleNum+1];
    break;
  case 21:
    fit_range_min
      = sample_time[(int)maxSampleNum-1];
    fit_range_max
      = sample_time[(int)maxSampleNum+3];
    break;
  case 11:
    fit_range_min
      = sample_time[(int)maxSampleNum];
    fit_range_max
      = sample_time[(int)maxSampleNum+3];
    break;
  case 71:
    fit_range_min
      = sample_time[(int)maxSampleNum-2];
    fit_range_max
      = sample_time[(int)maxSampleNum];
    break;
  }
  return;
}

int Convex(double fadc[8]){
  int convex = 2;//monotonic increase(tantyou zouka)
  if(fadc[0]>fadc[1]){
    convex = -2;//monotonic decrease(tantyou gensyou)
    return convex;
  }
  else{
    for(int i=0; i<7; i++){
      if(fadc[i]>fadc[i+1]){
	convex = 1;//convex upward(ue ni totsu)
      }
      if(convex==1){
	if(fadc[i]<fadc[i+1]){
	  convex = -1;//two extremum
	return convex;
	}
      }
    }
  }
  return convex;
}

double E16ANA_SSDStripAnalyzer::HitWaveFitV11() {
  //CalcPeak();
  ssd_single_hits.resize(0);
  int n_fit=0;

  int c=0;
  for(int strip=0; strip<n_strips; strip++){//n_strips=128

    fadc_fit_scale[strip] = -1000;
    fadc_fit_t0[strip] = -1000;
    fadc_fit_rise_time[strip] = -1000;

    if(fadc_peak[strip]>ssd_threshold && 
       fadc_peak_time[strip] > 0){
      if(c==0){
	//	cout << "fadc["<<strip<<"][0]=" << fadc[strip][0] <<endl; 
	c++;
      }
      //      cout << "Convex=" << Convex(fadc[strip]) << endl;
      n_fit++;
      //      cout << "n_fit=" << n_fit << endl;
      //TH1D *histo_wave = new TH1D("histo_wave","histo_wave",200,0,200);
      std::vector<double> v_adc_strip;
      std::vector<double> v_adc_strip_mod;
      for(int sample=0; sample<n_sampling; sample++){
	sample_time[sample] = sample*CLOCKWIDTH + (TDC-V775_OFFSET)*V775_TIMEGAIN;
	adc_strip[sample] = fadc[strip][sample];//-minAdcValue;
	//histo_wave->Fill(sample_time[sample],adc_strip[sample]);
	v_adc_strip.push_back(adc_strip[sample]);
	//cout << "adc_strip["<<sample<<"]=" << adc_strip[sample] << endl;
	//cout << "sample_time["<<sample<<"]=" << sample_time[sample] << endl;

      }
      double minAdcValue = getMin(v_adc_strip);
      for(int sample=0; sample<n_sampling; sample++){
	adc_strip[sample] -= minAdcValue;
	//cout << "adc_strip["<<sample<<"]=" << adc_strip[sample] << endl;
      }
      int minSampleNum = getMinSampleNum(v_adc_strip);
      int maxSampleNum = getMaxSampleNum(v_adc_strip);

      int waveType = classifyWaveType(v_adc_strip,minSampleNum,maxSampleNum,minAdcValue);

      //cout << "max Sample Num:" << maxSampleNum << 
      //	" Type: " << waveType<< endl;

      double fit_range_min = 0;
      double fit_range_max = 200;
      SetRange(waveType,sample_time,maxSampleNum, fit_range_min,fit_range_max);
      //cout << "fit range min " << fit_range_min << ", fit range max " << fit_range_max << endl;

      TF1 *fit_func = new TF1("fitfunc","[1]*(x-[2])/[0]*exp(-(x-[2])/[0])",fit_range_min-0.001,fit_range_max+0.001);

      double t_error[8] = {8.0/sqrt(12.), 8.0/sqrt(12.), 8.0/sqrt(12.),
			   8.0/sqrt(12.), 8.0/sqrt(12.),8.0/sqrt(12.),
			   8.0/sqrt(12.), 8.0/sqrt(12.)};
      double adc_error[8] = {4.0, 4.0, 4.0, 4.0,4.0, 4.0, 4.0, 4.0 };

      //TGraph *graph_wave = new TGraph(8,sample_time,adc_strip);
      TGraphErrors *graph_wave = new TGraphErrors(8,sample_time,adc_strip,
						  t_error, adc_error);
      // fit_func->SetParameter(0,37*3.5);//fix later
      // fit_func->SetParameter(1,fadc_peak[strip]*2.718);
      // fit_func->SetParameter(2,fadc_peak_time[strip]-140);
      //double p0 = 40;
      double p0 = 45;
      //double p1 = getMax(v_adc_strip)*2.718;
      double p1 = (getMax(v_adc_strip)-minAdcValue)*2.718;
      //double p2 = fadc_peak_time[strip]-40.;

      //double p2 = fadc_peak_time[strip]-40.;
      double p2;
      if(maxSampleNum > 0 && maxSampleNum < 7){
	double temp_csum = adc_strip[maxSampleNum -1 ] +
	  adc_strip[maxSampleNum] +
	  adc_strip[maxSampleNum +1] ;

	double temp_cog = 
	  adc_strip[maxSampleNum -1 ] * sample_time[maxSampleNum - 1 ] +
	  adc_strip[maxSampleNum]  * sample_time[maxSampleNum] +
	  adc_strip[maxSampleNum +1] * sample_time[maxSampleNum + 1 ]  ;

	//p2 = temp_cog/temp_csum - 140.0;
	p2 = temp_cog/temp_csum - p0;

      }else{
	p2 = fadc_peak_time[strip] - p0;
      }


      //cout << "p0,p1,p2=" << p0 << "," << p1 << "," << p2 <<endl;

      fit_func->SetParameter(0,p0);
      fit_func->SetParameter(1,p1);
      fit_func->SetParameter(2,p2);
      //if(fadc[strip][0]<fadc[strip][7] && Convex(fadc[strip])==1){
      if(fadc[strip][0]<fadc[strip][7] && Convex(fadc[strip])==1){
	//cout << "p0,p1,p2=" << p0 << "," << p1 << "," << p2 <<endl;
	// graph_wave->Fit(fit_func,""); cout << endl << endl;
	//graph_wave->Fit(fit_func,"qn");
	graph_wave->Fit(fit_func,"OQMEX0","",
			fit_range_min-0.001, fit_range_max+0.001);

      }
      double rise_time = fit_func->GetParameter(0);
      double scale = fit_func->GetParameter(1);
      double t0 = fit_func->GetParameter(2);


      if(rise_time!=40){

	//cout << "With Pedestal: p0,p1,p2=" << rise_time << "," << scale << "," << t0 <<endl;

	vector<double> plot;
	plot.resize(19);
	for(int i=0; i<8; i++){
	  plot.at(i)=adc_strip[i];
	  plot.at(i+8)=sample_time[i];
	}
	for(int i=0; i<3; i++){
	  plot.at(i+16)=fit_func->GetParameter(i);
	}
	ssd_plots.push_back(plot);
      }
      if(rise_time==40){
	rise_time=-1000;
	scale=-1000;
	t0=-1000;
      }
      E16ANA_SSDSingleStripHit temp;
      temp.SetFitValues(strip, t0+rise_time, t0, -1, scale, rise_time);
      ssd_single_hits.push_back(temp);

      //cout << "With Pedestal: p0,p1,p2=" << rise_time << "," << scale << "," << t0 <<endl;

      fadc_fit_scale[strip] = scale;
      fadc_fit_t0[strip] = t0;
      fadc_fit_rise_time[strip] = rise_time;

      delete fit_func; // ichikawa
      delete graph_wave; // ichikawa

    }
  }
  return 0;
}

double E16ANA_SSDStripAnalyzer::HitWaveFit_noPedestal() {
  //CalcPeak();
  ssd_single_hits.resize(0);
  int n_fit=0;

  int c=0;
  for(int strip=0; strip<n_strips; strip++){//n_strips=128
    if(fadc_peak[strip]>ssd_threshold &&
       fadc_peak_time[strip] > 0){
      if(c==0){
	//	cout << "fadc["<<strip<<"][0]=" << fadc[strip][0] <<endl; 
	c++;
      }
      //      cout << "Convex=" << Convex(fadc[strip]) << endl;
      n_fit++;
      //      cout << "n_fit=" << n_fit << endl;
      //TH1D *histo_wave = new TH1D("histo_wave","histo_wave",200,0,200);
      std::vector<double> v_adc_strip;
      std::vector<double> v_adc_strip_mod;
      for(int sample=0; sample<n_sampling; sample++){
	sample_time[sample] = sample*CLOCKWIDTH;
	adc_strip[sample] = fadc_noPedestal[strip][sample];//-minAdcValue;
	//histo_wave->Fill(sample_time[sample],adc_strip[sample]);
	v_adc_strip.push_back(adc_strip[sample]);
	//	cout << "adc_strip["<<sample<<"]=" << adc_strip[sample] << endl;
      }
      double minAdcValue = getMin(v_adc_strip);
      for(int sample=0; sample<n_sampling; sample++){
	adc_strip[sample] -= minAdcValue;
      }
      double minSampleNum = getMinSampleNum(v_adc_strip);
      double maxSampleNum = getMaxSampleNum(v_adc_strip);
      int waveType = classifyWaveType(v_adc_strip,minSampleNum,maxSampleNum,minAdcValue);
      double fit_range_min = 0;
      double fit_range_max = 200;
      //      SetRange(waveType,sample_time,maxSampleNum, fit_range_min,fit_range_max);
      TF1 *fit_func = new TF1("fitfunc","[1]*(x-[2])/[0]*exp(-(x-[2])/[0])",fit_range_min,fit_range_max);
      TGraph *graph_wave = new TGraph(8,sample_time,adc_strip);
      // fit_func->SetParameter(0,37*3.5);//fix later
      // fit_func->SetParameter(1,fadc_peak[strip]*2.718);
      // fit_func->SetParameter(2,fadc_peak_time[strip]-140);
      double p0 = 40;
      //double p1 = getMax(v_adc_strip)*2.718;
      double p1 = (getMax(v_adc_strip)-minAdcValue)*2.718;
      double p2 = fadc_peak_time[strip]-40;
      fit_func->SetParameter(0,p0);
      fit_func->SetParameter(1,p1);
      fit_func->SetParameter(2,p2);
      if(fadc[strip][0]<fadc[strip][7] && Convex(fadc[strip])==1){
	// cout << "p0,p1,p2=" << p0 << "," << p1 << "," << p2 <<endl;
	// graph_wave->Fit(fit_func,""); cout << endl << endl;
	graph_wave->Fit(fit_func,"qn");
      }
      double rise_time = fit_func->GetParameter(0);
      double scale = fit_func->GetParameter(1);
      double t0 = fit_func->GetParameter(2);
      if(rise_time!=40){

	//cout << "No Pedestal: p0,p1,p2=" << rise_time << "," << scale << "," << t0 <<endl;

	vector<double> params;
	params.resize(3);
	for(int i=0; i<3; i++){
	  params.at(i) = fit_func->GetParameter(i);
	}
	ssd_params.push_back(params);

	vector<double> plot0;
	plot0.resize(19);
	for(int i=0; i<8; i++){
	  plot0.at(i)=adc_strip[i];
	  plot0.at(i+8)=sample_time[i];
	}
	for(int i=0; i<3; i++){
	  plot0.at(i+16)=fit_func->GetParameter(i);
	}
	ssd_plots0.push_back(plot0);
      }
      if(rise_time==40){
	rise_time=-1000;
	scale=-1000;
	t0=-1000;
      }

delete fit_func; // ichikawa
delete graph_wave; // ichikawa

    }
  }
  return 0;
}

void E16ANA_SSDStripAnalyzer::CalcPeak() {
  for (int i = 0; i < n_strips; i++) {
    fadc_peak[i] = -255.0;
    fadc_peak_time[i] = -1000.0;
    fadc_tdc[i] = -1000.0;
  }
  for (int i = 0; i < n_strips; i++) {
    if (fadc[i][0] < -255.0)
      continue;
    this->CalcPeak(i, 10000.0);
  }
}

void E16ANA_SSDStripAnalyzer::CalcPeak(int ch, double t_cutoff) {
   int peak_count;
   double tot_start = 1000.0;
   double tot_end = 0.0;
   fadc_peak[ch] = -255.0;
   fadc_tdc[ch] = -1000.0;
   fadc_tot[ch] = -1000.0;
   peak_count = -1;
   for (int j = 0; j < n_sampling; j++) {
     if (fadc_peak[ch] < fadc[ch][j]) {
       fadc_peak[ch] = fadc[ch][j];
       peak_count = j;
     }
   }
   if(peak_count>-1){
     fadc_peak_time[ch] = peak_count*CLOCKWIDTH + (TDC-V775_OFFSET)*V775_TIMEGAIN;
   }


   if (fadc_peak[ch] < ssd_threshold) {
     fadc_peak[ch] = -255.0;
     fadc_peak_time[ch] = -1001.0;
     peak_count = -1;
   } 
}


void E16ANA_SSDStripAnalyzer::CalcWaveParamsPeak() {

  for (int i = 0; i < n_strips; i++) {
    fadc_peak[i] = -255.0;
    fadc_peak_time[i] = -2000.0;
    fadc_tdc[i] = -1000.0;
  }

   for (int i = 0; i < n_strips; i++) {

      // for(int i=left_strip_x; i<right_strip_x; i++){
     //     cout << "fadc[" << i << "][0]=" << fadc[i][0] << endl;  
     if (fadc[i][0] < -255.0)
       continue;

     this->CalcWaveParamsPeak(i, 10000.0);

     //std::cout << "strip ID:" << i << ", fadc_peak:" << fadc_peak[i] << endl;

     //     cout << "calculated!" << endl;
     // this->CalcWaveParamsPeak(i, ssd_tdc_max+ssd_tr+50.0);
     // if(fadc_tdc[i]>ssd_tdc_max){
     //   this->CalcWaveParamsPeak(i, ssd_tdc_max-ssd_tr);
     //}
   }
}

void E16ANA_SSDStripAnalyzer::CalcWaveParamsPeak(int ch, double t_cutoff) {
   int peak_count;
   double tot_start = 1000.0;
   double tot_end = 0.0;

   //std::cout << "ssd_threshold: " << ssd_threshold << std::endl;

   if (ch < n_strips) {
      fadc_peak[ch] = -255.0;
      fadc_tdc[ch] = -1000.0;
      fadc_tot[ch] = -1000.0;
      peak_count = -1;

      //std::cout << fadc_clock_period << std::endl;

      for (int j = 0; j < n_sampling; j++) {
         // for(int l=0; l<(int)fadc_valid_count.size(); l++){
         // int j= fadc_valid_count[l];
         double tdc_j = j * fadc_clock_period + fadc_t0_correction;
         if (tdc_j > t_cutoff)
            break;
         // if(tdc_j<t_cutoff) continue;

         if (fadc_peak[ch] < fadc[ch][j]) {
            fadc_peak[ch] = fadc[ch][j];
            peak_count = j;
         }
      }
      if (fadc_peak[ch] < ssd_threshold) {
         fadc_peak[ch] = -255.0;
         peak_count = -1;
      } else {
	//std::cout << "Peak detection, peak_value = " << fadc_peak[ch] << ", peak_count = " << peak_count <<
	//std::endl;
      }

      if (peak_count > -1) {
	//fadc_peak_time[ch] = peak_count * fadc_clock_period + fadc_t0_correction;
	fadc_peak_time[ch] = peak_count * fadc_clock_period + 
	  (TDC - V775_OFFSET)*V775_TIMEGAIN;
         for (int j = peak_count; j > -1; j--) {
            if (fadc[ch][j] < fadc_peak[ch] * threshold_fraction) {
               // double tdc_j = j;
               double w_j0 = fadc_peak[ch] * threshold_fraction - fadc[ch][j];
               double w_j1 = -fadc_peak[ch] * threshold_fraction + fadc[ch][j + 1];
               double tdc_j = (j * w_j1 + (j + 1.0) * w_j0) / (w_j0 + w_j1);
               // std::cout << "tdc_j = " << tdc_j << std::endl;
               //fadc_tdc[ch] = tdc_j * fadc_clock_period + fadc_t0_correction;
	       fadc_tdc[ch] = tdc_j * fadc_clock_period + 
		 (TDC - V775_OFFSET)*V775_TIMEGAIN;
               tot_start = fadc_tdc[ch];

               //fadc_peak_time[ch] = peak_count * CLOCKWIDTH + fadc_t0_correction;
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
         fadc_tot[ch] = tot_end - tot_start;
         if (fadc_tot[ch] < ssd_tot_threshold) {
            fadc_peak[ch] = -255.0;
            fadc_tdc[ch] = -1000.0;
            fadc_peak_time[ch] = -1001.0;
            peak_count = -1;
         }
      } else {
         fadc_tdc[ch] = -1000.0;
         fadc_peak_time[ch] = -1002.0;
      }

      if (fadc_peak_time[ch] > ssd_tdc_max 
	  || fadc_peak_time[ch] < ssd_tdc_min) {
      //if (fadc_tdc[ch] > ssd_tdc_max || fadc_tdc[ch] < ssd_tdc_min) {
         fadc_tdc[ch] = -1000.0;
         fadc_peak_time[ch] = -1003.0;
      }
   }


   /*
    std::cout << "fadc_tdc = " << fadc_tdc[ch] 
	      << ", fadc_peak_time = " << fadc_peak_time[ch] 
	      << std::endl;
    if(fadc_tdc[ch] < 0){
      for(int n_samp_tmp=0; n_samp_tmp < n_sampling; n_samp_tmp++ ){
	std::cout << fadc[ch][n_samp_tmp] << " ";
      }
      std::cout << std::endl;
    }
   */

}

void E16ANA_SSDStripAnalyzer::CalcCenterOfGravity(const std::vector<int> &strip_ids, E16ANA_SSDAnalyzedStripHit &hit) {
   int temp_max_strip = -1;
   double temp_max_value = -255.0;
   int temp_num_hit = 0;
   double temp_cc = 0.0;
   double temp_cog = 0.0;

   int temp_timing_hit = 0;
   double temp_timing = 0.0;

   int temp_fit_hit = 0;
   double temp_fit_charge = 0.0;
   double temp_fit_t = 0.0;

   if ((int)strip_ids.size() == 0) {
      hit.SetInvalid();
      return;
   }

   for (int i = 0; i < (int)strip_ids.size(); i++) {
      int id = strip_ids[i];
      if (fadc_peak[id] > temp_max_value) {
         temp_max_strip = id;
         temp_max_value = fadc_peak[id];
      }
      temp_num_hit++;
      temp_cc += fadc_peak[id];
      // temp_cog += fadc_peak[id]*id;
      temp_cog += fadc_peak[id] * GetPosition(id);

      if(fadc_peak_time[id]>0){
	temp_timing_hit++;
	temp_timing += fadc_peak_time[id];
      }

      if(fadc_fit_scale[id]>0){
	temp_fit_hit++;
	temp_fit_charge += fadc_fit_scale[id];
	temp_fit_t += fadc_fit_t0[id];
      }


//      cout << "id=" << id << endl;
//      cout << "pos=" << GetPosition(id) << endl;
      //hit.PushBackStrip(id, GetPosition(id), fadc_peak[id], fadc_tdc[id], fadc_tot[id]);
      hit.PushBackStrip(id, GetPosition(id), fadc_peak[id], fadc_peak_time[id],
			fadc_tot[id],
			fadc_fit_scale[id], fadc_fit_t0[id], 
			fadc_fit_rise_time[id]);
   }
   temp_cog /= temp_cc;


   if(temp_timing_hit > 0){
     temp_timing /= temp_timing_hit;
   }else{
     temp_timing = -1000;
   }

   if(temp_fit_hit > 0){
     temp_fit_t /= temp_fit_hit;
   }else{
     temp_fit_t = -1000;
   }

   // temp_cog *= strip_pitch;
   // temp_cog += position_start;
   // temp_cog *= inverted;

   hit.SetMaxStrip(temp_max_strip);
   hit.SetMaxValue(temp_max_value);
   hit.SetNumHit(temp_num_hit);
   hit.SetClusterCharge(temp_cc);
   hit.SetCogHit(temp_cog);
   hit.SetTiming(temp_timing);
   
   hit.SetTimingFit(temp_fit_t);
   hit.SetClusterChargeFit(temp_fit_charge);

}

