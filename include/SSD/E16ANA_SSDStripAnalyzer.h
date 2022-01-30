// 2015-11-02, uploaded by yokkaich
// 2015-11-02, uploaded by komatsu
// 2015-10-05, uploaded by yokkaich
// 2015-08-20, uploaded by yokkaich
// 2015-07-15, uploaded by nakai
// 2015-05-29, uploaded by yokkaich
// 2015-04-08, uploaded by nakai
#ifndef E16ANA_SSDStripAnalyzer_hh
#define E16ANA_SSDStripAnalyzer_hh 1

#include <iostream>

#include "E16ANA_SSDAnalyzer.h"
//#include "E16ANA_WaveformFitter.h"
//#include "E16ANA_Waveform2dFitter.h"
//#include "/ccj/u/E16/include/root-v5.34.02/TGraph.h"
#include <TF1.h>
#include <TGraph.h>
#include <vector>


class E16ANA_SSDSingleStripHit{
 public:
  void SetFitValues(int id, double peak, double t0, double t05, double scale, double risetime){
    stripID = id;
    fitPeakT = peak; fitT0 = t0; fitT05 = t05; fitScale = scale; fitRisetime = risetime; }

  int StripID(){return stripID;}
  double FitPeakT(){return fitPeakT;}
  double FitT0(){return fitT0;}
  double FitT05(){return fitT05;}
  double FitScale(){return fitScale;}
  double FitRisetime(){return fitRisetime;}
 private:

  int stripID;
  double fitPeakT;
  double fitT0;
  double fitT05; // 1/2 rise time
  double fitScale;
  double fitRisetime;
};

class E16ANA_SSDAnalyzedStripHit {
  //cluster
public:
   enum {
      n_sampling = 8,
      is_x = 0,
      is_y = 1,
      is_yb = 2,
   };

private:
   int ssd_max_strip;    // strip id
   double ssd_max_value; // peak ADC value
   int ssd_num_hit;
   double ssd_cluster_charge;    // sum of ADC values in a cluster
   double ssd_center_of_gravity; // mm
   double ssd_tdc_hit;           // mm
   double ssd_hit_pos;           // mm
   double tan_incident_angle;    // radian
   double timing;                // ns

   double timing_fit;             // ns
   double ssd_cluster_charge_fit;  // sum of Fit Scale in a cluster    


   int layerID;                  // 0-2
   int moduleID;                 // 0-32

   int id;   // array intex in Analyzer
   int type; // x,y,yb=0,1,2

   double summed_waveform[n_sampling];
   std::vector<double> strip_charge;
   std::vector<double> strip_timing;
   std::vector<int> strip_id;
   std::vector<double> strip_pos;
   std::vector<double> strip_tot;

   std::vector<double> strip_fit_scale;
   std::vector<double> strip_fit_t0;
   std::vector<double> strip_fit_rise_time;

public:
   E16ANA_SSDAnalyzedStripHit() {
      SetInvalid();
   };
   ~E16ANA_SSDAnalyzedStripHit() {};

   int ID() {
      return id;
   };
   void SetID(int i) {
      id = i;
   };

   void SetMaxStrip(int _ssd_max_strip) {
      ssd_max_strip = _ssd_max_strip;
   };
   void SetMaxValue(double _ssd_max_value) {
      ssd_max_value = _ssd_max_value;
   };
   void SetNumHit(int _ssd_num_hit) {
      ssd_num_hit = _ssd_num_hit;
   };
   void SetClusterCharge(double _ssd_cluster_charge) {
      ssd_cluster_charge = _ssd_cluster_charge;
   };
   void SetCogHit(double _ssd_center_of_gravity) {
      ssd_center_of_gravity = _ssd_center_of_gravity;
   };
   void SetTdcHit(double _ssd_tdc_hit) {
      ssd_tdc_hit = _ssd_tdc_hit;
   };
   void SetTanTheta(double _tan_incident_angle) {
      tan_incident_angle = _tan_incident_angle;
   };
   void SetModuleID(int _module_id){
     moduleID = _module_id;
   };

   void SetTimingFit(double _timing_fit){
     timing_fit = _timing_fit;
   };
   void SetClusterChargeFit(double _ssd_cluster_charge_fit) {
      ssd_cluster_charge_fit = _ssd_cluster_charge_fit;
   };

   
   void SetInvalid() {
      ssd_max_strip = kInvalidValue;
      ssd_max_value = kInvalidValue;
      ssd_num_hit = kInvalidValue;
      ssd_cluster_charge = kInvalidValue;
      ssd_center_of_gravity = kInvalidValue;
      ssd_tdc_hit = kInvalidValue;
      ssd_hit_pos = kInvalidValue;
      tan_incident_angle = kInvalidValue;
      // x_or_y = kInvalidValue;
      timing = kInvalidValue;
      layerID = kInvalidValue;
      moduleID = kInvalidValue;
      id = kInvalidValue;
      type = kInvalidValue;

      timing_fit = kInvalidValue;
      ssd_cluster_charge_fit =  kInvalidValue;

      strip_id.clear();
      strip_pos.clear();
      strip_tot.clear();
      strip_charge.clear();
      strip_timing.clear();
      strip_fit_scale.clear();
      strip_fit_t0.clear();
      strip_fit_rise_time.clear();

   };
   void AddWaveForm(double *wf) {
      for (int i = 0; i < n_sampling; i++) {
         summed_waveform[i] += wf[i];
      }
   };
   void ClearWaveForm() {
      for (int i = 0; i < n_sampling; i++) {
         summed_waveform[i] = 0.0;
      }
   }
   void SetTiming(double t) { timing = t; }


   void SetLayerAndModuleIDandType(int id1, int id2, int itype) {
      layerID = id1;
      moduleID = id2;
      type = itype;
   }

   bool IsX() { return type == is_x; }
   bool IsY() { return type == is_y; }
   bool IsYb() { return type == is_yb; }
   int Type() { return type; }

   //   void PushBackStrip(int id, double pos, double charge, double t, double tot = 0.0) {
   void PushBackStrip(int id, double pos, double charge, double t, 
		      double tot ,
		      double fit_scale, double fit_t0, double fit_rise_t
		      ) {
      strip_id.push_back(id);
      strip_pos.push_back(pos);
      strip_charge.push_back(charge);
      strip_timing.push_back(t);
      strip_tot.push_back(tot);
      strip_fit_scale.push_back(fit_scale);
      strip_fit_t0.push_back(fit_t0);
      strip_fit_rise_time.push_back(fit_rise_t);

   };

   int MaxStripId() {
      return ssd_max_strip;
   };
   double MaxValue() {
      return ssd_max_value;
   };
   int NumHit() {
      return ssd_num_hit;
   };
   double ClusterCharge() {
      return ssd_cluster_charge;
   };
   double CogHit() {
      return ssd_center_of_gravity;
   };
   double TdcHit() {
      return ssd_tdc_hit;
   };
   double TanTheta() {
      return tan_incident_angle;
   };
   double Timing() { return timing; }

   double TimingFit(){ return timing_fit;  };
   double ClusterChargeFit() { return ssd_cluster_charge_fit ;  };



   int ModuleID() { return moduleID; }
   int LayerID() { return layerID; }
   int StripID(int i) {
      return strip_id[i];
   };
   double StripPos(int i) {
      return strip_pos[i];
   };
   double StripCharge(int i) {
      return strip_charge[i];
   };
   double StripTiming(int i) {
      return strip_timing[i];
   };
   double StripTimeOverThreshold(int i) {
      return strip_tot[i];
   };

   double StripFitScale(int i) {
      return strip_fit_scale[i];
   };
   double StripFitT0(int i) {
      return strip_fit_t0[i];
   };
   double StripFitRiseTime(int i) {
      return strip_fit_rise_time[i];
   };


   enum {
      kInvalidValue = -1000000,
   };

   void Print() {
      std::cout << "E16ANA_SSDStripAnalyzer : "
                << "Num hit strips = " << ssd_num_hit << ", Cluster charge = " << ssd_cluster_charge
                << ", Cog hit pos = " << ssd_center_of_gravity << " [mm], Tdc hit pos = " << ssd_tdc_hit << " [mm]"
                << std::endl;
   };
};



class E16ANA_SSDStripAnalyzer {
   // friend void E16ANA_SSDAnalyzer::SetParameters(std::string filename);
   // friend void E16ANA_SSD100Analyzer::SetParameters(std::string filename);
   friend class E16ANA_SSDAnalyzer;
   friend class E16ANA_SSD100Analyzer;

public:
   E16ANA_SSDStripAnalyzer(int _n_fadc_chs, int _n_sampling);
   virtual ~E16ANA_SSDStripAnalyzer();
   virtual void Clear();
   virtual void SetFadc(int strip_id, int16_t *waveform);
   virtual void SetPedestal(double _fadc_ped[]){memcpy(fadc_ped, _fadc_ped, sizeof(double)*n_strips);};
   virtual void SetPedestal(int strip_id, double *_fadc_ped);//{fadc_ped[strip_id] = _fadc_ped[];};
   virtual void SetTDC(int _tdc){TDC=_tdc;};
   virtual int GetTDC(){return TDC;};
   virtual void SetOffset(double _offset){V775_OFFSET=_offset;};
   virtual void SetTimegain(double _timegain){V775_TIMEGAIN=_timegain;};
   virtual void Analyze();
   virtual void Analyze11();

   void SetInverse(bool flag) {
      if (flag) {
         inverted = -1.0;
      } else {
         inverted = +1.0;
      }
   };

   std::vector<E16ANA_SSDAnalyzedStripHit> &GetAnalyzedHits() {
      return ssd_analyzed_hits;
   };

   std::vector<E16ANA_SSDSingleStripHit> &GetSingleStripHits() {
      return ssd_single_hits;
   };

   std::vector<std::vector<double>> &GetParams(){
     return ssd_params;
   }

   std::vector<std::vector<double>> &GetPlots(){
     return ssd_plots;
   }

   std::vector<std::vector<double>> &GetPlots0(){
     return ssd_plots0;
   }

protected:
   const double CLOCKWIDTH = 25.0; //ns 
   //APVDAQ worked with 40MHz-CLK, namely, not 41.66MHz
   //210707 Arimizu

   const double V775_CLOCKWIDTH = 0.035; //ns
   //caen V775 worked with 35ps-CLK
   //210707 Arimizu

   // Analysis parameters
//   double drift_velocity;
//   double drift_gap_center;
   double strip_pitch;
   double fadc_clock_period;
   double fadc_t0_correction;
   double ssd_tdc_min;
   double ssd_tdc_max;
   double ssd_tr;
   double ssd_threshold;
   double ssd_tot_threshold;
   double threshold_fraction;
   double position_start;

   double inverted; // If strip order is the opposite direction to the local coordinate, ...

   int TDC;
   double V775_OFFSET;
   double V775_TIMEGAIN;
   double **fadc;
   double **fadc_noPedestal;
   double **fadc_ped;
   double *fadc_peak;
   double *fadc_peak_time;
   double *fadc_tdc;
   double *fadc_tot;

   double *fadc_fit_scale;
   double *fadc_fit_t0;
   double *fadc_fit_rise_time;


   double *sample_time;
   double *adc_strip;
   double **param;

   TGraph *graph_fit;

   int n_strips;
   int n_sampling;

   std::vector<int> fadc_valid_count;
   std::vector<std::vector<int>> clustered_strip_id;
   std::vector<E16ANA_SSDAnalyzedStripHit> ssd_analyzed_hits;
   std::vector<E16ANA_SSDSingleStripHit> ssd_single_hits;
   std::vector<std::vector<double>> ssd_params;
   std::vector<std::vector<double>> ssd_plots;
   std::vector<std::vector<double>> ssd_plots0;

   // E16ANA_WaveformFitter *wf1d_fitter;
   // E16ANA_Waveform2dFitter *wf2d_fitter;

   struct fit_params_t {
      int strip_id;
      std::vector<double> times;
      std::vector<double> peaks;
      fit_params_t(int _id, int size) {
         strip_id = _id;
         times.reserve(size);
         peaks.reserve(size);
      };
   };

   struct cluster_param_t {
      double pos;
      double time;
      double peak;
      cluster_param_t(double _pos, double _time, double _peak) {
         pos = _pos;
         time = _time;
         peak = _peak;
      };
   };

   double GetPosition(int strip_id) {
      return (strip_id * strip_pitch + position_start) * inverted;
   };

   void CalcWaveParamsPeak();
   void CalcWaveParamsPeak(int ch, double t_cutoff);
   void CalcPeak();
   void CalcPeak(int ch, double t_cutoff);
   void CalcWaveParamsFit(std::vector<fit_params_t> &fit_pars_array);
   void CalcWaveParamsFit(int ch, fit_params_t &fit_pars);
   // void CalcClusterParams(
   //      std::vector<double> &v1_pos, // 1D-array
   //      std::vector<double> &v1_time,
   //      std::vector<double> &v1_peak
   //      );
   void CalcClusterParams(std::vector<cluster_param_t> &v1);
   double HitWaveFitV11();
   double HitWaveFit_noPedestal();
   int classifyWaveType(std::vector<double>,int,int,double);
   int getMinSampleNum(std::vector<double>&);
   int getMaxSampleNum(std::vector<double>&);
   double getMin(std::vector<double>);
   double getMax(std::vector<double>);
   virtual int HitClusteringV0();
   virtual int HitClusteringV0(const int min_gap, const double cluster_threshold);
   virtual int HitClusteringV1(const int min_gap = 2, const double delta_tdc_threshold = 150.0);
   /*
      virtual int HitClusteringV2(const int min_gap = 2, const double delta_tdc_threshold = 150.0);
      virtual int HitClusteringV3(
            std::vector<std::vector<double> > &v2_x, // 2D-array
            std::vector<std::vector<double> > &v2_z,
            std::vector<std::vector<double> > &v2_peak
            );
   */
   std::vector<std::vector<double>> clustered_x;
   std::vector<std::vector<double>> clustered_z;
   std::vector<std::vector<double>> clustered_peak;

   void CalcCenterOfGravity(const std::vector<int> &strip_ids, E16ANA_SSDAnalyzedStripHit &hit);
   void CalcTdcHit1(const std::vector<int> &strip_ids, E16ANA_SSDAnalyzedStripHit &hit, int hitID);
   void
   CalcTdcHit2(const std::vector<int> &strip_ids, double tan_theta, E16ANA_SSDAnalyzedStripHit &hit); // fixed method
   void SetArraysForTdcMethods(const std::vector<int> &strip_ids, std::vector<double> &x_array,
                               std::vector<double> &time_array, std::vector<double> &peak_array);
   // void CalcTdcHit3(bool fix_flag, const std::vector<double> &x, const std::vector<double> &z, const
   // std::vector<double> &peak, E16ANA_SSDAnalyzedStripHit &hit, int hitID);
};

#endif // E16ANA_SSDStripAnalyzer_hh
