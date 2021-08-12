// 2015-11-02, uploaded by yokkaich
// 2015-11-02, uploaded by komatsu
// 2015-10-05, uploaded by yokkaich
// 2015-08-20, uploaded by yokkaich
// 2015-07-15, uploaded by nakai
//
// E16ANA_GTRAnalyzer2.cc
//    Last modified at <2015-10-05 15:26:06 >
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <map>
#include <algorithm>

#include "E16ANA_GTRAnalyzer2.h"
#include "E16ANA_GTRStripAnalyzer.h"

using namespace std;

E16ANA_GTRAnalyzer2::E16ANA_GTRAnalyzer2(int _n_strip_x, int _n_strip_y, int _n_fadc_chs, int _n_fadc_counts)
   : n_strip_x(_n_strip_x), n_strip_y(_n_strip_y), n_fadc_chs(_n_fadc_chs), n_fadc_counts(_n_fadc_counts)
{
   strip_num = new int[n_fadc_chs];

   for (int i = 0; i < n_fadc_chs; i++) {
      strip_num[i] = i;
   }

   strip_pitch_x = 0.35;
   strip_pitch_y = 1.40;
   gem_th_x = 200.0;
   gem_th_y = 200.0;
   drift_velocity = 0.015;
   drift_gap_center = 0.0;
   fadc_clock_period = 25.0;
   fadc_t0_correction = 0.0;
   tdc_lsb = 0.035;
   gem_t0_min = -10000.0;
   gem_t0_max = 10000.0;
   // gem_t0_min = 100.0;
   // gem_t0_max = 450.0;
   gem_tr = 75.0;
   threshold_fraction = 0.5;
   fadc_valid_count.reserve(n_fadc_counts);
   for (int i = 0; i < n_fadc_counts; i++) {
      fadc_valid_count.push_back(i);
   }
   strip_ana_x = new E16ANA_GTRStripAnalyzer(n_strip_x, n_fadc_counts);
   strip_ana_x->SetInverse(false);
   strip_ana_y = new E16ANA_GTRStripAnalyzer(n_strip_y, n_fadc_counts);
   strip_ana_y->SetInverse(true);
   strip_list.push_back(strip_ana_x);
   strip_list.push_back(strip_ana_y);

   x_start = -(double)n_strip_x / 2.0 * strip_pitch_x + strip_pitch_x * 0.5;
   y_start = -(double)n_strip_y / 2.0 * strip_pitch_y + strip_pitch_y * 0.5;

   strip_ana_x->strip_pitch = strip_pitch_x;
   strip_ana_x->gem_threshold = gem_th_x;
   strip_ana_x->gem_tdc_min = gem_t0_min;
   strip_ana_x->gem_tdc_max = gem_t0_max;
   strip_ana_x->drift_velocity = drift_velocity;
   strip_ana_x->drift_gap_center = drift_gap_center;
   strip_ana_x->fadc_clock_period = fadc_clock_period;
   strip_ana_x->position_start = x_start;
   strip_ana_x->gem_tr = gem_tr;
   strip_ana_x->threshold_fraction = threshold_fraction;

   strip_ana_y->strip_pitch = strip_pitch_y;
   strip_ana_y->gem_threshold = gem_th_y;
   strip_ana_y->gem_tdc_min = gem_t0_min;
   strip_ana_y->gem_tdc_max = gem_t0_max;
   strip_ana_y->drift_velocity = drift_velocity;
   strip_ana_y->drift_gap_center = drift_gap_center;
   strip_ana_y->fadc_clock_period = fadc_clock_period;
   strip_ana_y->position_start = y_start;
   strip_ana_y->gem_tr = gem_tr;
   strip_ana_y->threshold_fraction = threshold_fraction;
}

E16ANA_GTRAnalyzer2::~E16ANA_GTRAnalyzer2()
{
   delete[] strip_num;
   delete strip_ana_x;
   delete strip_ana_y;
}

void E16ANA_GTRAnalyzer2::Clear()
{
   // strip_ana_x->Clear();
   // strip_ana_y->Clear();
   for (int i = 0; i < (int)strip_list.size(); i++) {
      strip_list[i]->Clear();
   }
}

void E16ANA_GTRAnalyzer2::SetParameters(std::string filename)
{
   // NConfReader &gConf= NConfReader::GetInstance();
   // std::string filename= gConf.GetFileName("GEMPARAM:");
   std::cout << "[E16ANA_GTRAnalyzer2::SetParameters()]: filename =  " << filename << std::endl;
   std::ifstream ifs(filename.c_str());

   if (ifs.fail()) {
      std::cout << "\t ParamFile open fail" << std::endl;
      return;
   }

   std::map<std::string, double> parameter_list;

   while (ifs.good()) {
      std::string buf;
      std::getline(ifs, buf);
      if (buf[0] == '#' || buf.empty()) {
         continue;
      }
      std::istringstream is(buf);
      std::istream_iterator<std::string> issBegin(is);
      std::istream_iterator<std::string> issEnd;
      std::vector<std::string> param(issBegin, issEnd);
      if (param.empty() || param[0].empty()) {
         continue;
      }
      double parameter = atof(param[1].c_str());
      parameter_list[param[0]] = parameter;
      // double pedestal= atof(param[1].c_str());
      // double sigma= atof(param[2].c_str());
   }
   ifs.close();
   strip_pitch_x = parameter_list["PITCH_X:"];
   strip_pitch_y = parameter_list["PITCH_Y:"];
   gem_th_x = parameter_list["TH_X:"];
   gem_th_y = parameter_list["TH_Y:"];
   gem_t0_min = parameter_list["TDC_MIN:"];
   gem_t0_max = parameter_list["TDC_MAX:"];
   drift_velocity = parameter_list["DRIFT_VELOCITY:"];
   drift_gap_center = parameter_list["DRIFT_CENTER:"] * drift_velocity;
   fadc_clock_period = parameter_list["FADC_CLOCK_PERIOD:"];
   tdc_lsb = parameter_list["TDC_LSB:"];

   x_start = -(double)n_strip_x / 2.0 * strip_pitch_x + strip_pitch_x * 0.5;
   y_start = -(double)n_strip_y / 2.0 * strip_pitch_y + strip_pitch_y * 0.5;

   /*
      if(parameter_list["TDC_THRESHOLD_FRACTION"]>0.0){
         threshold_fraction= parameter_list["TDC_THRESHOLD_FRACTION:"];
      }
   */

   strip_ana_x->strip_pitch = strip_pitch_x;
   strip_ana_x->gem_threshold = gem_th_x;
   strip_ana_x->gem_tdc_min = gem_t0_min;
   strip_ana_x->gem_tdc_max = gem_t0_max;
   strip_ana_x->drift_velocity = drift_velocity;
   strip_ana_x->drift_gap_center = drift_gap_center;
   strip_ana_x->fadc_clock_period = fadc_clock_period;
   strip_ana_x->position_start = x_start;
   strip_ana_x->gem_tr = gem_tr;
   strip_ana_x->threshold_fraction = threshold_fraction;

   strip_ana_y->strip_pitch = strip_pitch_y;
   strip_ana_y->gem_threshold = gem_th_y;
   strip_ana_y->gem_tdc_min = gem_t0_min;
   strip_ana_y->gem_tdc_max = gem_t0_max;
   strip_ana_y->drift_velocity = drift_velocity;
   strip_ana_y->drift_gap_center = drift_gap_center;
   strip_ana_y->fadc_clock_period = fadc_clock_period;
   strip_ana_y->position_start = y_start;
   strip_ana_y->gem_tr = gem_tr;
   strip_ana_y->threshold_fraction = threshold_fraction;
}

void E16ANA_GTRAnalyzer2::SetThresholdX(double th)
{
   gem_th_x = th;
   strip_ana_x->gem_threshold = gem_th_x;
}

void E16ANA_GTRAnalyzer2::SetThresholdY(double th)
{
   gem_th_y = th;
   strip_ana_y->gem_threshold = gem_th_y;
}

void E16ANA_GTRAnalyzer2::SetTOTThresholdX(double th)
{
   strip_ana_x->gem_tot_threshold = th;
}

void E16ANA_GTRAnalyzer2::SetTOTThresholdY(double th)
{
   strip_ana_y->gem_tot_threshold = th;
}

void E16ANA_GTRAnalyzer2::SetBadPedestalThresholdX(double th)
{
   strip_ana_x->SetBadPedestalThreshold(th);
}

void E16ANA_GTRAnalyzer2::SetBadPedestalThresholdY(double th)
{
   strip_ana_y->SetBadPedestalThreshold(th);
}

void E16ANA_GTRAnalyzer2::SetBadPedestalSigmaThresholdX(double th)
{
   strip_ana_x->SetBadPedestalSigmaThreshold(th);
}

void E16ANA_GTRAnalyzer2::SetBadPedestalSigmaThresholdY(double th)
{
   strip_ana_y->SetBadPedestalSigmaThreshold(th);
}

void E16ANA_GTRAnalyzer2::SetTimeWindowMin(double th)
{
   for (int i = 0; i < (int)strip_list.size(); i++) {
      strip_list[i]->gem_tdc_min = th;
   }
}

void E16ANA_GTRAnalyzer2::SetTimeWindowMax(double th)
{
   for (int i = 0; i < (int)strip_list.size(); i++) {
      strip_list[i]->gem_tdc_max = th;
   }
}

void E16ANA_GTRAnalyzer2::SetPinAssign(std::string filename)
{
   // NConfReader &gConf= NConfReader::GetInstance();
   // std::string filename= gConf.GetFileName("FADCGEO:");
   std::cout << "[E16ANA_GTRAnalyzer2::SetPinAssign()]: filename = " << filename << std::endl;
   std::ifstream ifs(filename.c_str());

   if (ifs.fail()) {
      std::cout << "\t PinAssignFile open fail" << std::endl;
      return;
   }

   for (int ch = 0; ch < n_fadc_chs; ch++) {
      strip_num[ch] = -1;
   }

   while (ifs.good()) {
      std::string buf;
      std::getline(ifs, buf);
      if (buf[0] == '#' || buf.empty()) {
         continue;
      }
      std::istringstream is(buf);
      std::istream_iterator<std::string> issBegin(is);
      std::istream_iterator<std::string> issEnd;
      std::vector<std::string> param(issBegin, issEnd);
      if (param.empty() || param[0].empty()) {
         continue;
      }
      int ch = atoi(param[0].c_str());
      if (ch >= n_fadc_chs) {
         std::cout << "\t Channel exceeds the maximum of FADC channel ID." << std::endl;
         continue;
      }
      // double pedestal= atof(param[1].c_str());
      // double sigma= atof(param[2].c_str());
      if (param[1] == "x") {
         strip_num[ch] = atoi(param[2].c_str());
      } else if (param[1] == "y") {
         strip_num[ch] = atoi(param[2].c_str()) + n_strip_x;
      } else {
         strip_num[ch] = -1;
      }
   }
   /*
      for(int ch=0; ch<n_fadc_chs; ch++){
         std::cout<< "strip_num["<< ch<< "] = "<< strip_num[ch]<< std::endl;
      }
   */
   ifs.close();
}

void E16ANA_GTRAnalyzer2::SetFadcValidCount(std::string filename)
{
   // NConfReader &gConf= NConfReader::GetInstance();
   // std::string filename= gConf.GetFileName("FADCVALID:");
   // std::cout<< "[E16ANA_GTRAnalyzer2::SetFadcValidCount()] "<< filename<< std::endl;
   std::ifstream ifs(filename.c_str());

   if (ifs.fail()) {
      std::cout << "File open fail" << std::endl;
      return;
   }

   fadc_valid_count.clear();
   fadc_valid_count.reserve(n_fadc_counts);
   while (ifs.good()) {
      std::string buf;
      std::getline(ifs, buf);
      if (buf[0] == '#' || buf.empty()) {
         continue;
      }
      std::istringstream is(buf);
      std::istream_iterator<std::string> issBegin(is);
      std::istream_iterator<std::string> issEnd;
      std::vector<std::string> param(issBegin, issEnd);
      if (param.empty() || param[0].empty()) {
         continue;
      }
      for (int i = 0; i < (int)param.size(); i++) {
         fadc_valid_count.push_back(atoi(param[i].c_str()));
      }
   }
   /*
      for(int ch=0; ch<n_fadc_chs; ch++){
         std::cout<< "strip_num["<< ch<< "] = "<< strip_num[ch]<< std::endl;
      }
   */
   ifs.close();
}

void E16ANA_GTRAnalyzer2::SetFadc(int ch, int16_t *_fadc)
{
   if (strip_num[ch] < n_strip_x && strip_num[ch] > -1) {
      strip_ana_x->SetFadc(strip_num[ch], _fadc);
   } else if (strip_num[ch] >= n_strip_x && strip_num[ch] < n_strip_x + n_strip_y) {
      strip_ana_y->SetFadc(strip_num[ch] - n_strip_x, _fadc);
   }
}

void E16ANA_GTRAnalyzer2::SetPedestal(int ch, double _fadc_ped)
{
   if (strip_num[ch] < n_strip_x && strip_num[ch] > -1) {
      strip_ana_x->SetPedestal(strip_num[ch], _fadc_ped);
   } else if (strip_num[ch] >= n_strip_x && strip_num[ch] < n_strip_x + n_strip_y) {
      strip_ana_y->SetPedestal(strip_num[ch] - n_strip_x, _fadc_ped);
   }
}

void E16ANA_GTRAnalyzer2::SetPedestalSigma(int ch, double _fadc_ped_sigma)
{
   if (strip_num[ch] < n_strip_x && strip_num[ch] > -1) {
      strip_ana_x->SetPedestalSigma(strip_num[ch], _fadc_ped_sigma);
   } else if (strip_num[ch] >= n_strip_x && strip_num[ch] < n_strip_x + n_strip_y) {
      strip_ana_y->SetPedestalSigma(strip_num[ch] - n_strip_x, _fadc_ped_sigma);
   }
}

void E16ANA_GTRAnalyzer2::SetFadcX(int strip_id, int16_t *_fadc)
{
   strip_ana_x->SetFadc(strip_id, _fadc);
}

void E16ANA_GTRAnalyzer2::SetFadcY(int strip_id, int16_t *_fadc)
{
   strip_ana_y->SetFadc(strip_id, _fadc);
}

void E16ANA_GTRAnalyzer2::Analyze()
{
   // strip_ana_x->Analyze();
   // strip_ana_y->Analyze();
   for (int i = 0; i < (int)strip_list.size(); i++) {
      strip_list[i]->Analyze();
   }
}
void E16ANA_GTRAnalyzer2::Analyze2X(int hitid)
{
   strip_ana_x->Analyze2(hitid);
}
void E16ANA_GTRAnalyzer2::Analyze2Y(int hitid)
{
   strip_ana_y->Analyze2(hitid);
}

void E16ANA_GTRAnalyzer2::AnalyzeV1()
{
   for (int i = 0; i < (int)strip_list.size(); i++) {
      strip_list[i]->AnalyzeV1();
   }
}
/*
void E16ANA_GTRAnalyzer2::AnalyzeV2(){
   for(int i=0; i<(int)strip_list.size(); i++){
      strip_list[i]->AnalyzeV2();
   }
}
void E16ANA_GTRAnalyzer2::AnalyzeV2X(int hitid){
   strip_ana_x->AnalyzeV2(hitid);
}
void E16ANA_GTRAnalyzer2::AnalyzeV2Y(int hitid){
   strip_ana_y->AnalyzeV2(hitid);
}

void E16ANA_GTRAnalyzer2::AnalyzeV3(){
   for(int i=0; i<(int)strip_list.size(); i++){
      strip_list[i]->AnalyzeV3();
   }
}
void E16ANA_GTRAnalyzer2::AnalyzeV3X(int hitid){
   strip_ana_x->AnalyzeV3(hitid);
}
void E16ANA_GTRAnalyzer2::AnalyzeV3Y(int hitid){
   strip_ana_y->AnalyzeV3(hitid);
}
*/
/* ---- E16ANA_GTR100Analyzer ---- */

// E16ANA_GTR100Analyzer::E16ANA_GTR100Analyzer(int _n_fadc_chs = 432, int _n_fadc_counts = 30) :
E16ANA_GTR100Analyzer::E16ANA_GTR100Analyzer(int _n_fadc_chs, int _n_fadc_counts)
   : E16ANA_GTRAnalyzer2(288, 72, _n_fadc_chs, _n_fadc_counts)
{
   x_start = -(double)n_strip_x / 2.0 * strip_pitch_x + strip_pitch_x * 0.5;
   y_start = -(double)n_strip_y / 2.0 * strip_pitch_y + strip_pitch_y * 0.5;

   strip_ana_yb = new E16ANA_GTRStripAnalyzer(n_strip_y, n_fadc_counts);
   strip_ana_yb->SetInverse(false);
   strip_list.push_back(strip_ana_yb);
   strip_ana_yb->strip_pitch = strip_pitch_y;
   strip_ana_yb->gem_threshold = gem_th_y;
   strip_ana_yb->gem_tdc_min = gem_t0_min;
   strip_ana_yb->gem_tdc_max = gem_t0_max;
   strip_ana_yb->drift_velocity = drift_velocity;
   strip_ana_yb->drift_gap_center = drift_gap_center;
   strip_ana_yb->fadc_clock_period = fadc_clock_period;
   strip_ana_yb->position_start = y_start;
   strip_ana_yb->gem_tr = gem_tr;
   strip_ana_yb->threshold_fraction = threshold_fraction;
}

E16ANA_GTR100Analyzer::~E16ANA_GTR100Analyzer()
{
   delete strip_ana_yb;
}

void E16ANA_GTR100Analyzer::SetParameters(std::string filename)
{
   E16ANA_GTRAnalyzer2::SetParameters(filename);
   strip_ana_yb->strip_pitch = strip_pitch_y;
   strip_ana_yb->gem_threshold = gem_th_y;
   strip_ana_yb->gem_tdc_min = gem_t0_min;
   strip_ana_yb->gem_tdc_max = gem_t0_max;
   strip_ana_yb->drift_velocity = drift_velocity;
   strip_ana_yb->drift_gap_center = drift_gap_center;
   strip_ana_yb->fadc_clock_period = fadc_clock_period;
   strip_ana_yb->position_start = y_start;
   strip_ana_yb->gem_tr = gem_tr;
   strip_ana_yb->threshold_fraction = threshold_fraction;
}

void E16ANA_GTR100Analyzer::SetThresholdY(double th)
{
   E16ANA_GTRAnalyzer2::SetThresholdY(th);
   strip_ana_yb->gem_threshold = gem_th_y;
}

void E16ANA_GTR100Analyzer::SetTOTThresholdY(double th)
{
   E16ANA_GTRAnalyzer2::SetTOTThresholdY(th);
   strip_ana_yb->gem_tot_threshold = th;
}

void E16ANA_GTR100Analyzer::SetBadPedestalThresholdY(double th)
{
   E16ANA_GTRAnalyzer2::SetBadPedestalThresholdY(th);
   strip_ana_yb->SetBadPedestalThreshold(th);
}

void E16ANA_GTR100Analyzer::SetBadPedestalSigmaThresholdY(double th)
{
   E16ANA_GTRAnalyzer2::SetBadPedestalSigmaThresholdY(th);
   strip_ana_yb->SetBadPedestalSigmaThreshold(th);
}

void E16ANA_GTR100Analyzer::SetFadcYa(int strip_id, int16_t *_fadc)
{
   strip_ana_y->SetFadc(strip_id, _fadc);
}

void E16ANA_GTR100Analyzer::SetFadcYb(int strip_id, int16_t *_fadc)
{
   strip_ana_yb->SetFadc(strip_id, _fadc);
}
void E16ANA_GTR100Analyzer::AnalyzeYb()
{
   strip_ana_yb->Analyze();
}

void E16ANA_GTR100Analyzer::Analyze2Ya(int hitid)
{
   strip_ana_y->Analyze2(hitid);
}
void E16ANA_GTR100Analyzer::Analyze2Yb(int hitid)
{
   strip_ana_yb->Analyze2(hitid);
}
void E16ANA_GTR100Analyzer::Analyze2Y(int hitid, int type)
{
   //  cerr<<"100 2Y type "<<type<<endl;
   if (type == E16ANA_GTRAnalyzedStripHit::is_y) {
      strip_ana_y->Analyze2(hitid);
   } else if (type == E16ANA_GTRAnalyzedStripHit::is_yb) {
      strip_ana_yb->Analyze2(hitid);
   } else {
   }
}

void E16ANA_GTR100Analyzer::SetFadc(int ch, int16_t *_fadc)
{
   if (strip_num[ch] < n_strip_x && strip_num[ch] > -1) {
      strip_ana_x->SetFadc(strip_num[ch], _fadc);
   } else if (strip_num[ch] >= n_strip_x && strip_num[ch] < n_strip_x + n_strip_y) {
      strip_ana_y->SetFadc(strip_num[ch] - n_strip_x, _fadc);
   } else if (strip_num[ch] >= n_strip_x + n_strip_y && strip_num[ch] < n_strip_x + n_strip_y + n_strip_y) {
      strip_ana_yb->SetFadc(strip_num[ch] - n_strip_x - n_strip_y, _fadc);
   }
}

void E16ANA_GTR100Analyzer::SetPedestal(int ch, double _fadc_ped)
{
   if (strip_num[ch] < n_strip_x && strip_num[ch] > -1) {
      strip_ana_x->SetPedestal(strip_num[ch], _fadc_ped);
   } else if (strip_num[ch] >= n_strip_x && strip_num[ch] < n_strip_x + n_strip_y) {
      strip_ana_y->SetPedestal(strip_num[ch] - n_strip_x, _fadc_ped);
   } else if (strip_num[ch] >= n_strip_x + n_strip_y && strip_num[ch] < n_strip_x + n_strip_y + n_strip_y) {
      strip_ana_yb->SetPedestal(strip_num[ch] - n_strip_x - n_strip_y, _fadc_ped);
   }
}

void E16ANA_GTR100Analyzer::SetPedestalSigma(int ch, double _fadc_ped_sigma)
{
   if (strip_num[ch] < n_strip_x && strip_num[ch] > -1) {
      strip_ana_x->SetPedestalSigma(strip_num[ch], _fadc_ped_sigma);
   } else if (strip_num[ch] >= n_strip_x && strip_num[ch] < n_strip_x + n_strip_y) {
      strip_ana_y->SetPedestalSigma(strip_num[ch] - n_strip_x, _fadc_ped_sigma);
   } else if (strip_num[ch] >= n_strip_x + n_strip_y && strip_num[ch] < n_strip_x + n_strip_y + n_strip_y) {
      strip_ana_yb->SetPedestalSigma(strip_num[ch] - n_strip_x - n_strip_y, _fadc_ped_sigma);
   }
}

void E16ANA_GTR100Analyzer::SetPinAssign(std::string filename)
{
   // NConfReader &gConf= NConfReader::GetInstance();
   // std::string filename= gConf.GetFileName("FADCGEO:");
   std::cout << "[E16ANA_GTRAnalyzer2::SetPinAssign()]: filename = " << filename << std::endl;
   std::ifstream ifs(filename.c_str());

   if (ifs.fail()) {
      std::cout << "\t PinAssignFile open fail" << std::endl;
      return;
   }

   for (int ch = 0; ch < n_fadc_chs; ch++) {
      strip_num[ch] = -1;
   }

   while (ifs.good()) {
      std::string buf;
      std::getline(ifs, buf);
      if (buf[0] == '#' || buf.empty()) {
         continue;
      }
      std::istringstream is(buf);
      std::istream_iterator<std::string> issBegin(is);
      std::istream_iterator<std::string> issEnd;
      std::vector<std::string> param(issBegin, issEnd);
      if (param.empty() || param[0].empty()) {
         continue;
      }
      int ch = atoi(param[0].c_str());
      if (ch >= n_fadc_chs) {
         std::cout << "\t Channel exceeds the maximum of FADC channel ID." << std::endl;
         continue;
      }
      // double pedestal= atof(param[1].c_str());
      // double sigma= atof(param[2].c_str());
      if (param[1] == "x") {
         strip_num[ch] = atoi(param[2].c_str());
      } else if (param[1] == "y" || param[1] == "ya") {
         strip_num[ch] = atoi(param[2].c_str()) + n_strip_x;
      } else if (param[1] == "yb") {
         strip_num[ch] = atoi(param[2].c_str()) + n_strip_x + n_strip_y;
      } else {
         strip_num[ch] = -1;
      }
   }
   ifs.close();
}

//------------------------------------------

void E16ANA_GTRAnalyzedHit::SetXstripHit(E16ANA_GTRAnalyzedStripHit *xhit, TVector3 &gX)
{
   xstriphit = xhit;
   gPosition = gX;
   layerID = xhit->LayerID();
   moduleID = xhit->ModuleID();
}

void E16ANA_GTRAnalyzedHit::SetYstripHit(E16ANA_GTRAnalyzedStripHit *yhit, TVector3 &gY)
{
   ystriphit = yhit;
   gPosition = gY;
   layerID = yhit->LayerID();
   moduleID = yhit->ModuleID();
}
