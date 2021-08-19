//---based on E16ANA_GTRPedestal, written by T. Murakami 20210818 ----
#ifndef E16ANA_GTRcalib_hh
#define E16ANA_GTRcalib_hh

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

#endif // E16ANA_GTRcalib_hh
