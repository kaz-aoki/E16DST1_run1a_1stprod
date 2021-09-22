// 2015-11-02, uploaded by yokkaich
// 2015-11-02, uploaded by komatsu
// 2015-10-05, uploaded by yokkaich
// 2015-08-20, uploaded by yokkaich
// 2015-07-15, uploaded by nakai
#ifndef E16ANA_SSDAnalyzer_hh
#define E16ANA_SSDAnalyzer_hh 1

#include <vector>

#include <TVector3.h>

class E16ANA_SSDStripAnalyzer;

// example
// E16ANA_SSD100Analyzer( 360, 24); for SSD100
// E16ANA_SSD200Analyzer( 720, 24); for SSD200
// E16ANA_SSD300Analyzer(1080, 24); for SSD300
//
// Arguments are num_of_fadcs, and num_of_samplings respectively.
// When using this for ordinary simulation, use default arguments.
// If not, set num_of_fadcs correct value (for example 384) and use SetPinAssign method.

class E16ANA_SSDAnalyzer {
public:
//   E16ANA_SSDAnalyzer(int _n_strip_x, int _n_strip_y, int _n_fadc_chs, int _n_fadc_counts);
   E16ANA_SSDAnalyzer(int _n_strip_x=128, int _n_fadc_chs=768, int _n_fadc_counts=8);
   virtual ~E16ANA_SSDAnalyzer();
   virtual void SetParameters(std::string filename);
   virtual void SetPinAssign(std::string filename);
   virtual int GetNumberOfStrips(){return n_strip_x + n_strip_y;};
   void SetFadcValidCount(std::string filename);

   void Analyze();
   void Analyze11();

   void Analyze2X(int hitid); // use CalcTdc2 for a hit
   void Analyze2Y(int hitid); // use CalcTdc2 for a hit
//   virtual void Analyze2Y(int hitid, int type) = 0;

   void AnalyzeV0() {
      Analyze();
   };
   void AnalyzeV11() {
      Analyze11();
   };
   void AnalyzeV0X(int hitid) {
      Analyze2X(hitid);
   };
   void AnalyzeV0Y(int hitid) {
      Analyze2Y(hitid);
   };

   void AnalyzeV1();
   void AnalyzeV1X(int hitid) {
      Analyze2X(hitid);
   };
   void AnalyzeV1Y(int hitid) {
      Analyze2Y(hitid);
   };
   /*
      void AnalyzeV2();
      void AnalyzeV2X(int hitid);//use CalcTdc2 for a hit
      void AnalyzeV2Y(int hitid);//use CalcTdc2 for a hit

      void AnalyzeV3();
      void AnalyzeV3X(int hitid);//use CalcTdc2 for a hit
      void AnalyzeV3Y(int hitid);//use CalcTdc2 for a hit
   */
   void Clear();
   virtual void SetFadc(int ch, int16_t *_fadc); // use this
   virtual void SetPedestal(int ch, double *_fadc_ped); // use this
   virtual void SetTDC(int _tdc);
   virtual int GetTDC(){return TDC;};
   virtual void SetOffset(double _offset);
   virtual void SetTimegain(double _timegain);
   void SetFadcX(int strip_id, int16_t *_fadc);  // use this
   void SetFadcY(int strip_id, int16_t *_fadc);  // use this

   void SetFadcT0CorrectionParameter(int _fadc_t0) {
      fadc_t0_correction = _fadc_t0 * tdc_lsb;
   };

   E16ANA_SSDStripAnalyzer *GetStripX() {
      return strip_ana_x;
   };
   E16ANA_SSDStripAnalyzer *GetStripY() {
      return strip_ana_y;
   };
#if 0
  virtual E16ANA_SSDStripAnalyzer* GetStripYa()=0;
  virtual E16ANA_SSDStripAnalyzer* GetStripYb()=0;
  virtual void  SetStripDataYa()=0;
  virtual void  SetStripDataYb()=0;
#endif

protected:
   int n_strip_x;
   int n_strip_y;
   int n_fadc_counts;
   int n_fadc_chs;
   int *strip_num; // Use to convert fadc_ch to strip_num (shared by X and Y)
   // int y_strip_num[32];

   double x_start;
   double y_start;
   double strip_pitch_x;
   double strip_pitch_y;
   double ssd_th_x;
   double ssd_th_y;
//   double drift_velocity;
//   double drift_gap_center;
   double fadc_clock_period;
   double fadc_t0_correction;
   double tdc_lsb;//least square bit in the case of V775, 35ps
   double ssd_t0_min;
   double ssd_t0_max;
   double ssd_tr;//rise time
   double threshold_fraction;
   int TDC;
   double V775_OFFSET;
   double V775_TIMEGAIN;

   // int n_valid_counts;
   std::vector<int> fadc_valid_count;

   E16ANA_SSDStripAnalyzer *strip_ana_x;
   E16ANA_SSDStripAnalyzer *strip_ana_y;
   std::vector<E16ANA_SSDStripAnalyzer *> strip_list;
};
/*
class E16ANA_SSD100Analyzer;

class E16ANA_SSD200Analyzer;
class E16ANA_SSD300Analyzer;

class E16ANA_SSD100Analyzer : public E16ANA_SSDAnalyzer {
private:
   E16ANA_SSDStripAnalyzer *strip_ana_yb;

public:
   E16ANA_SSD100Analyzer(int _n_fadc_chs = 432, int _n_fadc_counts = 24);
   ~E16ANA_SSD100Analyzer();

   // 100 chamber has separated Y strip
   // Ya:   0 <(local) x< 50 [mm]
   // Yb: -50 <(local) x< 0  [mm]

   E16ANA_SSDStripAnalyzer *GetStripYa() {
      return strip_ana_y;
   };
   E16ANA_SSDStripAnalyzer *GetStripYb() {
      return strip_ana_yb;
   };

   void AnalyzeYb();
   void Analyze2Ya(int hitid); // using CalcTdc2 for a hit
   void Analyze2Yb(int hitid); // using CalcTdc2 for a hit
   void Analyze2Y(int hitid, int type); // a(is_y) or b(is_yb):

   void SetFadc(int ch, int16_t *_fadc); // use this
   void SetPedestal(int ch, double _fadc_ped); // use this
   void SetFadcYa(int strip_id, int16_t *_fadc);
   void SetFadcYb(int strip_id, int16_t *_fadc);

   void SetParameters(std::string filename);
   void SetPinAssign(std::string filename);
   int GetNumberOfStrips(){return n_strip_x + n_strip_y + n_strip_y;};
};

class E16ANA_SSD200Analyzer : public E16ANA_SSDAnalyzer {
public:
   E16ANA_SSD200Analyzer(int _n_fadc_chs = 720, int _n_fadc_counts = 24)
      : E16ANA_SSDAnalyzer(576, 144, _n_fadc_chs, _n_fadc_counts) {};

   void Analyze2Y(int hitid, int type) {
      //    std::cerr<<"200 2Y type "<<type<<std::endl;
      E16ANA_SSDAnalyzer::Analyze2Y(hitid);
   }
};
*/

class E16ANA_ATLASSSDAnalyzer;
class E16ANA_ATLASSSDAnalyzer : public E16ANA_SSDAnalyzer {
public:
   E16ANA_ATLASSSDAnalyzer(int _n_fadc_chs = 768, int _n_fadc_counts = 8)
      : E16ANA_SSDAnalyzer(768, _n_fadc_chs, _n_fadc_counts) {};
//   void Analyze2Y(int hitid, int type) {
//       std::cerr<<"300 2Y type "<<type<<std::endl;
//     E16ANA_SSDAnalyzer::Analyze2Y(hitid);
//   }
};



#endif // E16ANA_SSDAnalyzer_hh
