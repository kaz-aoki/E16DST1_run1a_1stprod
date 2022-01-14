#ifndef E16ANA_GTRcalib_h
#define E16ANA_GTRcalib_h

//---based on E16ANA_GTRPedestal, written by T. Murakami 20210818 ----
#include <cmath>
#include <string>
#include <unordered_map>

#include <TH1D.h>

class E16ANA_GTRcalibPedestal {
public:
   union IDs {
      uint64_t value64;
      struct {
         uint32_t strip_id;
         uint16_t layer_id;
         uint16_t module_id;
      };
      IDs(uint16_t _module_id, uint16_t _layer_id, uint32_t _strip_id)
         : strip_id(_strip_id), layer_id(_layer_id), module_id(_module_id){};
      IDs(uint64_t id) : value64(id){};
      ~IDs(){};
#if 0
      bool operator < (const IDs &rhs) const {
         return this->value64 < rhs.value64;
      };
#endif
   };

   class Pedestal {
   public:
      Pedestal();
      ~Pedestal();
      void AddADCValue(double adc);
      void CalcPedestal();
      double Value()
      {
         if (!is_set) {
            CalcPedestal();
         }
         return value;
      };
      double Sigma()
      {
         if (!is_set) {
            CalcPedestal();
         }
         return sigma;
      };
      void SetValues(double v, double s)
      { // file read mode
         is_set = true;
         value = v;
         sigma = s;
      };

   private:
      double value;
      double sigma;
      bool is_set;
      TH1D *h_adc;
   };

   E16ANA_GTRcalibPedestal();
   ~E16ANA_GTRcalibPedestal();
   void Read(std::string fname);
   void Write(std::string fname);
   void AddADCValue(IDs id, double adc) { pedestal_map[id.value64].AddADCValue(adc); };
   Pedestal &GetPedestal(IDs id) { return pedestal_map[id.value64]; };
   Pedestal &GetPedestal(uint16_t module_id, uint16_t layer_id, uint32_t strip_id)
   {
      return GetPedestal(IDs(module_id, layer_id, strip_id));
   };

   bool ReadCalibData(int run_id);
//   bool ReadCalibDataCore(FILE *file);
   bool ReadCalibDataCore(std::ifstream *fname);


private:
   std::unordered_map<uint64_t, Pedestal> pedestal_map;
};

class E16ANA_GTRcalibParams{
public:
	E16ANA_GTRcalibParams(){};
	~E16ANA_GTRcalibParams(){};
	
	FILE* CallParamFile(int runID);

public:
   union IDs {
      uint32_t value32;
      struct {
         uint16_t layer_id;
         uint16_t module_id;
      };
      IDs(uint16_t _module_id, uint16_t _layer_id)
         : layer_id(_layer_id), module_id(_module_id){};
      IDs(uint32_t id) : value32(id){};
      ~IDs(){};
#if 0
      bool operator < (const IDs &rhs) const {
         return this->value64 < rhs.value64;
      };
#endif
   };

   class Params {
   public:
      Params(){};
      ~Params(){};
//      void AddADCValue(double adc);
//      void CalcPedestal();
//      double Value()
//      {
//         if (!is_set) {
//            CalcPedestal();
//         }
//         return value;
//      };
//      double Sigma()
//      {
//         if (!is_set) {
//            CalcPedestal();
//         }
//         return sigma;
//      };
      void SetValues(double tx, double ty, double totx, double toty, double pedx, double pedy, double sigx, double sigy, double wmin, double wmax, int gap, double tdc, double rmin, double rmax, double pmin, double pmax, double dv, double cd, double cd2)
      { // file read mode
    	 th_x = tx;
	     th_y = ty;
		 th_totx = totx;
		 th_toty = toty;
		 th_badped_x = pedx;
		 th_badped_y = pedy;
		 th_badped_sigma_x = sigx;
		 th_badped_sigma_y = sigy;
		 twindow_min = wmin;
	 	 twindow_max= wmax;
         cluster_min_gap = gap;
    	 cluster_delta_tdc = tdc;
	  	 risetime_min = rmin;
	  	 risetime_max = rmax;
	 	 peaktime_min = pmin;	
    	 peaktime_max = pmax;
//	     tdc_min  = tdmin;
//	 	 tdc_max  = tdmax;
	  	 drift_velocity = dv;
	  	 center_of_drift_gap = cd;
	  	 center_of_drift_gap2 = cd2;
         is_set = true;
      };
	  double ThresholdX(){return th_x;}
	  double ThresholdY(){return th_y;}
	  double TOTThresholdX(){return th_totx;}
	  double TOTThresholdY(){return th_toty;}
	  double BadPedestalThresholdX(){return th_badped_x;}
	  double BadPedestalThresholdY(){return th_badped_y;}
	  double BadPedestalSigmaThresholdX(){return th_badped_sigma_x;}
	  double BadPedestalSigmaThresholdY(){return th_badped_sigma_y;}
	  double TimeWindowMin(){return twindow_min;}
	  double TimeWindowMax(){return twindow_max;}
      int    ClusterMinGap(){return cluster_min_gap;}
	  double ClusterDeltaTDC(){return cluster_delta_tdc;}
	  double RiseTimeMin(){return risetime_min;}
	  double RiseTimeMax(){return risetime_max;}
	  double PeakTimeMin(){return peaktime_min;}
	  double PeakTimeMax(){return peaktime_max;}
//	  double TdcMin(){return tdc_min;}
//	  double TdcMax(){return tdc_max;}
	  double DriftVelocity(){return drift_velocity;}
	  double CenterOfDriftGap(){return center_of_drift_gap;}
	  double CenterOfDriftGap2(){return center_of_drift_gap2;}
   private:
      double th_x;
      double th_y;
	  double th_totx;
	  double th_toty;
	  double th_badped_x;
	  double th_badped_y;
	  double th_badped_sigma_x;
	  double th_badped_sigma_y;
	  double twindow_min;
	  double twindow_max;
      int    cluster_min_gap;
	  double cluster_delta_tdc;
	  double risetime_min;
	  double risetime_max;
	  double peaktime_min;	
      double peaktime_max;
//	  double tdc_min;
//	  double tdc_max;
	  double drift_velocity;
	  double center_of_drift_gap;
	  double center_of_drift_gap2;
      bool is_set;
   };

   void Read(std::string fname);
   void Write(std::string fname);
//   void AddADCValue(IDs id, double adc) { pedestal_map[id.value64].AddADCValue(adc); };
   Params &GetParams(IDs id) { return chamber_params_map[id.value32]; };
   Params &GetParams(uint16_t module_id, uint16_t layer_id)
   {
      return GetParams(IDs(module_id, layer_id));
   };

   bool ReadCalibData(int run_id);
//   bool ReadCalibDataCore(FILE *file);
   bool ReadCalibDataCore(std::ifstream *fname);


private:
   std::unordered_map<uint32_t, Params> chamber_params_map;
};





#endif // E16ANA_GTRcalib_h
