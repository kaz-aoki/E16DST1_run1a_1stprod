#ifndef E16ANA_GTRTemplatePulseCalib_hh
#define E16ANA_GTRTemplatePulseCalib_hh

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <TFile.h>
#include <TH1D.h>

class E16ANA_GTRTemplatePulseCalib {
private:
   static constexpr int n_xbin = 3;
   static constexpr int n_anglebin= 5;
   static constexpr double tan_whole_range = 2.0;// (-1.0 < tan_theta < 1.0)
   static constexpr double xstrip_pitch = 0.350;//mm 
   static constexpr int n_modules = 10;
   static constexpr int n_layers = 3;//gtr
public:
   static constexpr int n_gtr_samples = 15;//run0e
   struct GTRTemplatePulse{
      int delta_strip;//i_th strip from neareset strips to sim_hit
      std::array<double, n_gtr_samples> waveform;
      double peak_sumx;
      double peak_sumy;
      double cluster_timing;
   };
   E16ANA_GTRTemplatePulseCalib(bool _enableNormalize) : enableNormalize(_enableNormalize) {}
   ~E16ANA_GTRTemplatePulseCalib(){};
//   E16ANA_GTRTemplatePulseCalib(int xbin=1, int anglebin=1) : n_xbin(xbin), n_anglebin(anglebin) {}
//   ~E16ANA_GTRTemplatePulseCalib(){};
 
   void Read(std::string fname);
   void Write(std::string fname);
   
   bool ReadCalibData(int run_id);
   bool ReadCalibDataCore(std::vector<std::ifstream*>& ifs_list, std::array<std::array<std::unordered_map<std::string, std::unordered_map<int, std::vector<GTRTemplatePulse>>>, n_layers>, n_modules>& template_fadc_map);
   int GetGTRNSamples(){return n_gtr_samples;}
   //const std::vector<GTRTemplatePulse> GetRandomTemplatePulses(int16_t layer_id, int16_t x_bin, int16_t angle_bin, bool isX);
   const std::array<std::vector<GTRTemplatePulse>, 2>  GetRandomTemplatePulses(int run_id, int event_id, int track_id, int16_t module_id, int16_t layer_id, int16_t x_bin, int16_t angle_bin);
   static std::string MakeKey(int16_t x_bin, int16_t angle_bin);
   int CalculateXBin(double dx);
   int CalculateAngleBin(double a);
//   double TanWholeRange(return tan_whole_range);
//   double XStripPitch(return xstrip_pitch); 
   int NAngleBin(){return n_anglebin;}; 
//   int NXBin(return n_xbin);  
private:
   bool enableNormalize; 
   constexpr static double base_adc_value = 2000.0;//this value is no reason
   bool ReadCalibDataCore(TFile* f);
   bool ReadCalibDataCore(std::ifstream* ifs,   std::array<std::array<std::unordered_map<std::string, std::unordered_map<int, std::vector<GTRTemplatePulse>>>, n_layers>, n_modules> &template_fadc_map);

   bool ParseCalibLine(const std::string& line, std::array<std::array<std::unordered_map<std::string, std::unordered_map<int, std::vector<GTRTemplatePulse>>>, n_layers>, n_modules> &template_fadc_map);
   //   Key : (x_bin, angle_bin) -> to string
   // Value : holds a map with set_id as a key
   //         where each setid contains vector of GTRTemplatePulse
   std::array<std::array<std::unordered_map<std::string, std::unordered_map<int, std::vector<GTRTemplatePulse>>>, n_layers>, n_modules> template_fadc_map_x;
   std::array<std::array<std::unordered_map<std::string, std::unordered_map<int, std::vector<GTRTemplatePulse>>>, n_layers>, n_modules> template_fadc_map_y;

   TH1D* h_gtr_template_peaksum_x_l0;
   TH1D* h_gtr_template_peaksum_x_l1;
   TH1D* h_gtr_template_peaksum_x_l2;
   TH1D* h_gtr_template_peaksum_y_l0;
   TH1D* h_gtr_template_peaksum_y_l1;
   TH1D* h_gtr_template_peaksum_y_l2;
};

#endif //E16ANA_GTRTemplatePulseCalib_hh
