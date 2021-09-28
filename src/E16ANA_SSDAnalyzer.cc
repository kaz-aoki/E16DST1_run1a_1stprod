// 2015-11-02, uploaded by yokkaich
// 2015-11-02, uploaded by komatsu
// 2015-10-05, uploaded by yokkaich
// 2015-08-20, uploaded by yokkaich
// 2015-07-15, uploaded by nakai
//
// E16ANA_SSDAnalyzer.cc
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

#include "E16ANA_SSDAnalyzer.h"
#include "E16ANA_SSDStripAnalyzer.h"


//E16ANA_SSDAnalyzer::E16ANA_SSDAnalyzer(int _n_strip_x, int _n_strip_y, int _n_fadc_chs, int _n_fadc_counts)
E16ANA_SSDAnalyzer::E16ANA_SSDAnalyzer(int _n_strip_x, int _n_fadc_chs, int _n_fadc_counts)
//   : n_strip_x(_n_strip_x), n_strip_y(_n_strip_y), n_fadc_chs(_n_fadc_chs), n_fadc_counts(_n_fadc_counts) {
   : n_strip_x(_n_strip_x), n_fadc_chs(_n_fadc_chs), n_fadc_counts(_n_fadc_counts) {
   strip_num = new int[n_fadc_chs];

   for (int i = 0; i < n_fadc_chs; i++) {
      strip_num[i] = i;
   }

   strip_pitch_x = 0.08;
//   strip_pitch_y = 1.40;
//   ssd_th_x = 200.0;
   ssd_th_x = 0.0;
//   ssd_th_y = 200.0;
//   drift_velocity = 0.015;
//   drift_gap_center = 0.0;
   fadc_clock_period = 8.0;
   fadc_t0_correction = 0.0;
   tdc_lsb = 0.035;
   ssd_t0_min = -10000.0;
   ssd_t0_max = 10000.0;
   ssd_tr = 75.0;
   threshold_fraction = 0.5;
   fadc_valid_count.reserve(n_fadc_counts);
   for (int i = 0; i < n_fadc_counts; i++) {
      fadc_valid_count.push_back(i);
   }
   strip_ana_x = new E16ANA_SSDStripAnalyzer(n_fadc_chs, n_fadc_counts);
   strip_ana_x->SetInverse(false);
//   strip_ana_y = new E16ANA_SSDStripAnalyzer(n_strip_y, n_fadc_counts);
//   strip_ana_y->SetInverse(true);
   strip_list.push_back(strip_ana_x);
//   strip_list.push_back(strip_ana_y);

   x_start = -(double)n_strip_x / 2.0 * strip_pitch_x + strip_pitch_x * 0.5;
//   y_start = -(double)n_strip_y / 2.0 * strip_pitch_y + strip_pitch_y * 0.5;

   strip_ana_x->strip_pitch = strip_pitch_x;
   strip_ana_x->ssd_threshold = ssd_th_x;
   strip_ana_x->ssd_tdc_min = ssd_t0_min;
   strip_ana_x->ssd_tdc_max = ssd_t0_max;
//   strip_ana_x->drift_velocity = drift_velocity;
//   strip_ana_x->drift_gap_center = drift_gap_center;
   strip_ana_x->fadc_clock_period = fadc_clock_period;
   strip_ana_x->position_start = x_start;
   strip_ana_x->ssd_tr = ssd_tr;
   strip_ana_x->threshold_fraction = threshold_fraction;

/*
   strip_ana_y->strip_pitch = strip_pitch_y;
   strip_ana_y->ssd_threshold = ssd_th_y;
   strip_ana_y->ssd_tdc_min = ssd_t0_min;
   strip_ana_y->ssd_tdc_max = ssd_t0_max;
//   strip_ana_y->drift_velocity = drift_velocity;
//   strip_ana_y->drift_gap_center = drift_gap_center;
   strip_ana_y->fadc_clock_period = fadc_clock_period;
   strip_ana_y->position_start = y_start;
   strip_ana_y->ssd_tr = ssd_tr;
   strip_ana_y->threshold_fraction = threshold_fraction;
*/
}

E16ANA_SSDAnalyzer::~E16ANA_SSDAnalyzer() {
   delete[] strip_num;
   delete strip_ana_x;
//   delete strip_ana_y;
}

void E16ANA_SSDAnalyzer::Clear() {
  strip_ana_x->Clear();
   // strip_ana_y->Clear();

   // for (int i = 0; i < (int)strip_list.size(); i++) {
   //    strip_list[i]->Clear();
   // }

}

void E16ANA_SSDAnalyzer::SetParameters(std::string filename) {
   // NConfReader &gConf= NConfReader::GetInstance();
   // std::string filename= gConf.GetFileName("GEMPARAM:");
   std::cout << "[E16ANA_SSDAnalyzer::SetParameters()]: filename =  " << filename << std::endl;
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
   ssd_th_x = parameter_list["TH_X:"];
   ssd_th_y = parameter_list["TH_Y:"];
   ssd_t0_min = parameter_list["TDC_MIN:"];
   ssd_t0_max = parameter_list["TDC_MAX:"];
//   drift_velocity = parameter_list["DRIFT_VELOCITY:"];
//   drift_gap_center = parameter_list["DRIFT_CENTER:"] * drift_velocity;
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
   strip_ana_x->ssd_threshold = ssd_th_x;
   strip_ana_x->ssd_tdc_min = ssd_t0_min;
   strip_ana_x->ssd_tdc_max = ssd_t0_max;
//   strip_ana_x->drift_velocity = drift_velocity;
//   strip_ana_x->drift_gap_center = drift_gap_center;
   strip_ana_x->fadc_clock_period = fadc_clock_period;
   strip_ana_x->position_start = x_start;
   strip_ana_x->ssd_tr = ssd_tr;
   strip_ana_x->threshold_fraction = threshold_fraction;

   strip_ana_y->strip_pitch = strip_pitch_y;
   strip_ana_y->ssd_threshold = ssd_th_y;
   strip_ana_y->ssd_tdc_min = ssd_t0_min;
   strip_ana_y->ssd_tdc_max = ssd_t0_max;
//   strip_ana_y->drift_velocity = drift_velocity;
//   strip_ana_y->drift_gap_center = drift_gap_center;
   strip_ana_y->fadc_clock_period = fadc_clock_period;
   strip_ana_y->position_start = y_start;
   strip_ana_y->ssd_tr = ssd_tr;
   strip_ana_y->threshold_fraction = threshold_fraction;
}

void E16ANA_SSDAnalyzer::SetPinAssign(std::string filename) {
   // NConfReader &gConf= NConfReader::GetInstance();
   // std::string filename= gConf.GetFileName("FADCGEO:");
   std::cout << "[E16ANA_SSDAnalyzer::SetPinAssign()]: filename = " << filename << std::endl;
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

void E16ANA_SSDAnalyzer::SetFadcValidCount(std::string filename) {
   // NConfReader &gConf= NConfReader::GetInstance();
   // std::string filename= gConf.GetFileName("FADCVALID:");
   // std::cout<< "[E16ANA_SSDAnalyzer::SetFadcValidCount()] "<< filename<< std::endl;
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

void E16ANA_SSDAnalyzer::SetFadc(int ch, int16_t *_fadc) {
   if (strip_num[ch] < n_fadc_chs && strip_num[ch] > -1) {
      strip_ana_x->SetFadc(strip_num[ch], _fadc);
   } 
//	else if (strip_num[ch] >= n_strip_x && strip_num[ch] < n_strip_x + n_strip_y) {
//      strip_ana_y->SetFadc(strip_num[ch] - n_strip_x, _fadc);
//   }
}

void E16ANA_SSDAnalyzer::SetTDC(int _tdc) {
     strip_ana_x->SetTDC(_tdc);
}

void E16ANA_SSDAnalyzer::SetTimegain(double _timegain) {
     strip_ana_x->SetTimegain(_timegain);
}

void E16ANA_SSDAnalyzer::SetOffset(double _offset) {
     strip_ana_x->SetOffset(_offset);
}

void E16ANA_SSDAnalyzer::SetPedestal(int ch, double *_fadc_ped) {
   if (strip_num[ch] < n_fadc_chs && strip_num[ch] > -1) {
      strip_ana_x->SetPedestal(strip_num[ch], _fadc_ped);
   } 
//	else if (strip_num[ch] >= n_strip_x && strip_num[ch] < n_strip_x + n_strip_y) {
//      strip_ana_y->SetPedestal(strip_num[ch] - n_strip_x, _fadc_ped);
//   }
}

void E16ANA_SSDAnalyzer::SetFadcX(int strip_id, int16_t *_fadc) { strip_ana_x->SetFadc(strip_id, _fadc); }

//void E16ANA_SSDAnalyzer::SetFadcY(int strip_id, int16_t *_fadc) { strip_ana_y->SetFadc(strip_id, _fadc); }

void E16ANA_SSDAnalyzer::Analyze() {
   // strip_ana_x->Analyze();
   // strip_ana_y->Analyze();
   for (int i = 0; i < (int)strip_list.size(); i++) { //always 1, because ATLAS SSD has X only
   	strip_list[i]->Analyze();
   }
}

void E16ANA_SSDAnalyzer::Analyze11() {
   for (int i = 0; i < (int)strip_list.size(); i++) { //always 1, because ATLAS SSD has X only
   	strip_list[i]->Analyze11();
   }
}
