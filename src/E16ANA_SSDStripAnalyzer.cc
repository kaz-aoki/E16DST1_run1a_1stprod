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
#include <TCanvas.h>

#include "E16ANA_SSDStripAnalyzer.h"
//#include "E16ANA_WaveformFitter.h"
//#include "E16ANA_Waveform2dFitter.h"

using namespace std;

E16ANA_SSDStripAnalyzer::E16ANA_SSDStripAnalyzer(int _n_strips, int _n_sampling)
   : n_strips(_n_strips), n_sampling(_n_sampling), strip_pitch(0.08), ssd_threshold(4.0), ssd_tot_threshold(-10000.0),
//     drift_velocity(0.010), drift_gap_center(0.0), fadc_clock_period(25.0), fadc_t0_correction(0.0),
     fadc_clock_period(8.0), fadc_t0_correction(0.0),
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
   // cout << "fadc[strip_id][0]=" << fadc[strip_id][0] << endl;
   // cout << "waveform[0]=" << waveform[0] << endl;
   // cout << "fadc_ped["<<strip_id<<"][0]=" << fadc_ped[strip_id][0] << endl;
}

void E16ANA_SSDStripAnalyzer::SetPedestal(int strip_id, double *_fadc_ped) {
   for (int j = 0; j < n_sampling; j++) {
      fadc_ped[strip_id][j] = _fadc_ped[j];
   }
}

void E16ANA_SSDStripAnalyzer::Analyze() {

   // CalcWaveParamsPeak();
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
  
  HitWaveFitV11();
  HitWaveFit_noPedestal();
  // CalcWaveParamsPeak();
  int n_hits = HitClusteringV0();//number of cluster
  //std::cout << "n_hits=" << n_hits << std::endl;
  ssd_analyzed_hits.resize(n_hits);
  // ssd_analyzed_hits.resize(n_hits,E16ANA_SSDAnalyzedStripHit());
  for (int i = 0; i < n_hits; i++) {
    ssd_analyzed_hits[i].SetInvalid();
    CalcCenterOfGravity(clustered_strip_id[i], ssd_analyzed_hits[i]);
//      CalcTdcHit1(clustered_strip_id[i], ssd_analyzed_hits[i], i);
    // CalcTdcHit2(clustered_strip_id[i], ssd_analyzed_hits[i].TanTheta(), ssd_analyzed_hits[i]);
  }
}


void E16ANA_SSDStripAnalyzer::Analyze2() {
   // CalcWaveParamsPeak();
   int n_hits = HitClusteringV0();
   ssd_analyzed_hits.resize(n_hits);
   // ssd_analyzed_hits.resize(n_hits,E16ANA_SSDAnalyzedStripHit());
   for (int i = 0; i < n_hits; i++) {
      CalcCenterOfGravity(clustered_strip_id[i], ssd_analyzed_hits[i]);
//      CalcTdcHit2(clustered_strip_id[i], ssd_analyzed_hits[i].TanTheta(), ssd_analyzed_hits[i]);
   }
}


void E16ANA_SSDStripAnalyzer::Analyze2(int id) {
   //  E16MESSAGE("size %d %d", clustered_strip_id.size(), ssd_analyzed_hits.size());
 //  CalcTdcHit2(clustered_strip_id[id], ssd_analyzed_hits[id].TanTheta(), ssd_analyzed_hits[id]);
}

void E16ANA_SSDStripAnalyzer::AnalyzeV1() {
   // CalcWaveParamsPeak();
//   int n_hits = HitClusteringV1();
//   ssd_analyzed_hits.resize(n_hits);
   // ssd_analyzed_hits.resize(n_hits,E16ANA_SSDAnalyzedStripHit());
//   for (int i = 0; i < n_hits; i++) {
//      ssd_analyzed_hits[i].SetInvalid();
//      CalcCenterOfGravity(clustered_strip_id[i], ssd_analyzed_hits[i]);
 //     CalcTdcHit1(clustered_strip_id[i], ssd_analyzed_hits[i], i);
      // CalcTdcHit2(clustered_strip_id[i], ssd_analyzed_hits[i].TanTheta(), ssd_analyzed_hits[i]);
//   }
}

int E16ANA_SSDStripAnalyzer::HitClusteringV0() { return HitClusteringV0(2, -10000.0); }

int E16ANA_SSDStripAnalyzer::HitClusteringV0(const int min_gap, const double cluster_threshold) {
   CalcWaveParamsPeak();
   // const int min_gap = 2;
   int signal_gap = 100;

   for (int i = 0; i < (int)clustered_strip_id.size(); i++) {
      clustered_strip_id[i].clear();
   }
   clustered_strip_id.clear();

   // double pre_tdc = fadc_tdc[0];
   for (int i = 0; i < n_strips; i++) {
      if (fadc_peak[i] > ssd_threshold) {
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
  CalcPeak();
  ssd_single_hits.resize(0);
  int n_fit=0;

  int c=0;
  for(int strip=0; strip<n_strips; strip++){//n_strips=128
    if(fadc_peak[strip]>ssd_threshold){
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
      temp.SetFitValues(t0+rise_time, t0, -1, scale, rise_time);
      ssd_single_hits.push_back(temp);

      delete fit_func;
      delete graph_wave;

    }
  }
  return 0;
}

double E16ANA_SSDStripAnalyzer::HitWaveFit_noPedestal() {
  CalcPeak();
  ssd_single_hits.resize(0);
  int n_fit=0;

  int c=0;
  for(int strip=0; strip<n_strips; strip++){//n_strips=128
    if(fadc_peak[strip]>ssd_threshold){
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

      delete fit_func;
      delete graph_wave;

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
   if (ch < n_strips) {
      fadc_peak[ch] = -255.0;
      fadc_tdc[ch] = -1000.0;
      fadc_tot[ch] = -1000.0;
      peak_count = -1;
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
 //         std::cout << "Peak detection, peak_value = " << fadc_peak[ch] << ", peak_count = " << peak_count <<
//          std::endl;
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
	       //               fadc_peak_time[ch] = peak_count * fadc_clock_period + fadc_t0_correction;
               fadc_peak_time[ch] = peak_count * CLOCKWIDTH + fadc_t0_correction;
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
      if (fadc_tdc[ch] > ssd_tdc_max || fadc_tdc[ch] < ssd_tdc_min) {
         fadc_tdc[ch] = -1000.0;
         fadc_peak_time[ch] = -1003.0;
      }
   }
}

void E16ANA_SSDStripAnalyzer::CalcCenterOfGravity(const std::vector<int> &strip_ids, E16ANA_SSDAnalyzedStripHit &hit) {
   int temp_max_strip = -1;
   double temp_max_value = -255.0;
   int temp_num_hit = 0;
   double temp_cc = 0.0;
   double temp_cog = 0.0;

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
//      cout << "id=" << id << endl;
//      cout << "pos=" << GetPosition(id) << endl;
      hit.PushBackStrip(id, GetPosition(id), fadc_peak[id], fadc_tdc[id], fadc_tot[id]);
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

/*

void E16ANA_SSDStripAnalyzer::SetArraysForTdcMethods(const std::vector<int> &strip_ids, std::vector<double> &x_array,
                                                     std::vector<double> &time_array, std::vector<double> &peak_array) {
   //   std::cerr<<std::endl<<"fadctime/peak ";
   for (int i = 0; i < (int)strip_ids.size(); i++) {
      // if(ssd_peak_x[i]>ssd_th_x && ssd_t0_x[i]<800){
      // if(ssd_peak_x[i]>ssd_th_x && ssd_t0_x[i]>0.0 && ssd_t0_x[i]<ssd_t0_max){
      int id = strip_ids[i];
      if (fadc_peak[id] > ssd_threshold && fadc_tdc[id] > 0.0) {
         // x_array.push_back(((double)id*strip_pitch+position_start)*inverted);
         x_array.push_back(GetPosition(id));
         time_array.push_back(fadc_tdc[id] * drift_velocity);
         peak_array.push_back(fadc_peak[id]);
         // std::cerr<<id<<" "<<fadc_tdc[id]<<" "<<fadc_peak_time[id]<<" "<<drift_velocity<<" ";
      }
   }
}
void
E16ANA_SSDStripAnalyzer::CalcTdcHit1(const std::vector<int> &strip_ids, E16ANA_SSDAnalyzedStripHit &hit, int hitID) {
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
   //hit.SetID(hitID);
	//hit.SetModuleID(moduleID);
	

   double meantime = C / drift_velocity / x_array.size(); // cluster mean
   hit.SetTiming(meantime);
   //   std::cerr<<"t0/mean "<<t0<<" "<<meantime<<std::endl;
   //   t0 is bad
}
void E16ANA_SSDStripAnalyzer::CalcTdcHit2(const std::vector<int> &strip_ids, double tan_theta,
                                          E16ANA_SSDAnalyzedStripHit &hit) {
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

*/
/*----------------- Analyze version 2 -----------------*/
/*
void E16ANA_SSDStripAnalyzer::AnalyzeV2(){
   int n_hits = HitClusteringV2();
   std::cout << "E16ANA_SSDStripAnalyzer::AnalyzeV2 : multiplicity = " << n_hits << std::endl;
   ssd_analyzed_hits.resize(n_hits);
   for(int i=0; i<n_hits; i++){
      std::cout << "cid = " << i << ", n_signal = " << clustered_x[i].size() << std::endl;
      CalcTdcHit3(false, clustered_x[i], clustered_z[i], clustered_peak[i], ssd_analyzed_hits[i], i);
   }
}

void E16ANA_SSDStripAnalyzer::CalcWaveParamsFit(std::vector<fit_params_t> &fit_pars_array){
   fit_pars_array.clear();
   for(int i=0; i<n_strips; i++){
   //for(int i=left_strip_x; i<right_strip_x; i++){
      if(fadc[i][0]<-255.0) continue;
      fit_pars_array.push_back(fit_params_t(i,5));
      this->CalcWaveParamsFit(i, fit_pars_array.back());
   }
}

void E16ANA_SSDStripAnalyzer::CalcWaveParamsFit(int ch, fit_params_t &fit_pars){
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

int E16ANA_SSDStripAnalyzer::HitClusteringV2(const int min_gap, const double delta_tdc_threshold){
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

void E16ANA_SSDStripAnalyzer::AnalyzeV2(int id){
   CalcTdcHit3(true, clustered_x[id], clustered_z[id], clustered_peak[id], ssd_analyzed_hits[id], id);
}
*/
/*----------------- Analyze version 2 -----------------*/

/*----------------- Analyze version 3 -----------------*/
/*
void E16ANA_SSDStripAnalyzer::AnalyzeV3(){
   clustered_x.clear();
   clustered_z.clear();
   clustered_peak.clear();
   int n_hits = HitClusteringV3(clustered_x, clustered_z, clustered_peak);
   //std::cout << "E16ANA_SSDStripAnalyzer::AnalyzeV3 : multiplicity = " << n_hits << std::endl;
   ssd_analyzed_hits.resize(n_hits);
   for(int i=0; i<n_hits; i++){
      CalcTdcHit3(false, clustered_x[i], clustered_z[i], clustered_peak[i], ssd_analyzed_hits[i], i);
   }
}

//void E16ANA_SSDStripAnalyzer::CalcClusterParams(
//      std::vector<double> &v1_pos,
//      std::vector<double> &v1_time,
//      std::vector<double> &v1_peak
//      ){
void E16ANA_SSDStripAnalyzer::CalcClusterParams(std::vector<cluster_param_t> &v1){
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

int E16ANA_SSDStripAnalyzer::HitClusteringV3(
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

void E16ANA_SSDStripAnalyzer::CalcTdcHit3(
      bool fix_flag,
      const std::vector<double> &x,
      const std::vector<double> &z,
      const std::vector<double> &peak,
      E16ANA_SSDAnalyzedStripHit &hit, int hitID){

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

void E16ANA_SSDStripAnalyzer::AnalyzeV3(int id){
   CalcTdcHit3(true, clustered_x[id], clustered_z[id], clustered_peak[id], ssd_analyzed_hits[id], id);
}
*/
/*----------------- Analyze version 3 -----------------*/
