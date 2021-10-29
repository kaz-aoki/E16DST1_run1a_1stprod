//based on E16ANA_GTRPedestal, written by T. Murakami, 210818
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_ErrorMessage.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include <TF1.h>

E16ANA_GTRcalibPedestal::E16ANA_GTRcalibPedestal() {}

E16ANA_GTRcalibPedestal::~E16ANA_GTRcalibPedestal() {}

bool E16ANA_GTRcalibPedestal::ReadCalibData(int runID){
    E16ANA_CalibDBManager& calib = E16ANA_CalibDBManager::Instance();
//    FILE *ifp = calib.CalibFileOpenBinary("GTR-pedestal", runID);
    std::ifstream *ifs = calib.CalibStreamOpenBinary("GTR-pedestal", runID);
    if (ifs != NULL){
        return ReadCalibDataCore(ifs);
    }
    else {
        E16FATAL("file open error");
    return false;
    }
}

bool E16ANA_GTRcalibPedestal::ReadCalibDataCore(std::ifstream *ifs){
//   std::ifstream *ifs;
//   *ifs = *fname;
//   ifs.open(fname);
   bool flag = true;
   if (ifs->fail()) {
      std::cerr << "E16ANA_GTRcalibPedestal::Read : failed to read file: " << ifs << std::endl;
      flag = false ;
      std::exit(1);
   }
   while (!ifs->eof()) {
      std::string buf;
      std::getline(*ifs, buf);
      if (buf[0] == '#' || buf.empty()) {
         continue;
      }
      std::istringstream iss(buf);
      IDs id(0);
      double pedestal, sigma;
      iss >> id.module_id >> id.layer_id >> id.strip_id >> pedestal >> sigma;
      pedestal_map[id.value64].SetValues(pedestal, sigma);
   }
   ifs->close();
   return flag;
}

void E16ANA_GTRcalibPedestal::Read(std::string fname)
{
   std::ifstream ifs;
   ifs.open(fname);
   if (ifs.fail()) {
      std::cerr << "E16ANA_GTRcalibPedestal::Read : failed to read file: " << fname << std::endl;
      std::exit(1);
   }
   while (!ifs.eof()) {
      std::string buf;
      std::getline(ifs, buf);
      if (buf[0] == '#' || buf.empty()) {
         continue;
      }
      std::istringstream iss(buf);
      IDs id(0);
      double pedestal, sigma;
      iss >> id.module_id >> id.layer_id >> id.strip_id >> pedestal >> sigma;
      pedestal_map[id.value64].SetValues(pedestal, sigma);
   }
   ifs.close();
}

void E16ANA_GTRcalibPedestal::Write(std::string fname)
{
   std::ofstream ofs;
   ofs.open(fname);
   if (ofs.fail()) {
      std::cerr << "E16ANA_GTRcalibPedestal::Write : failed to open file: " << fname << std::endl;
      std::exit(1);
   }
   std::map<uint64_t, Pedestal> sorted_map(pedestal_map.begin(), pedestal_map.end());
   for (auto &p : sorted_map) {
      IDs id(p.first);
      ofs << id.module_id << " " << id.layer_id << " " << id.strip_id << " " << p.second.Value() << " "
          << p.second.Sigma() << std::endl;
   }
   ofs.close();
}

E16ANA_GTRcalibPedestal::Pedestal::Pedestal() : value(0.0), sigma(1.0), is_set(true), h_adc(nullptr) {}

E16ANA_GTRcalibPedestal::Pedestal::~Pedestal()
{
   if (h_adc != nullptr) {
      delete h_adc;
   }
}

void E16ANA_GTRcalibPedestal::Pedestal::AddADCValue(double adc)
{
   if (h_adc == nullptr) {
      static int n = 0;
      h_adc = new TH1D(Form("h_gtr_pedestal_adc%d", n), Form("h_gtr_pedestal_adc%d", n), 2001, -1000.5, 1000.5);
      n++;
   }
   h_adc->Fill(adc);
   is_set = false;
}

void E16ANA_GTRcalibPedestal::Pedestal::CalcPedestal()
{
   if (h_adc == nullptr) {
      return;
   }

   int n_fit = 3;
   double n_sigma = 2.0;
   double mean = h_adc->GetMean();
   double rms = h_adc->GetRMS();
   double min = -1000, max = 1000;
   TF1 *f = new TF1("f_ped_fit", "gaus", min, max);
   for (int i = 0; i < n_fit; i++) {
      f->SetParameter(1, mean);
      f->SetParameter(2, rms);
      h_adc->Fit(f, "QN", "QN", min, max);
      mean = f->GetParameter(1);
      rms = f->GetParameter(2);
      min = mean - rms * n_sigma;
      max = mean + rms * n_sigma;
   }
   value = mean;
   sigma = rms;
   is_set = true;
   delete f;
   return;
}

bool E16ANA_GTRcalibParams::ReadCalibDataCore(std::ifstream *ifs){
   bool flag = true;
   if (ifs->fail()) {
      std::cerr << "E16ANA_GTRcalibParams::Read : failed to read file: " << ifs << std::endl;
      flag = false ;
      std::exit(1);
   }
   while (!ifs->eof()) {
      std::string buf;
      std::getline(*ifs, buf);
      if (buf[0] == '#' || buf.empty()) {
         continue;
      }
      std::istringstream iss(buf);
      IDs id(0);
	  int cluster_min_gap;
      double tx, ty, totx, toty, pedx, pedy, sigx, sigy, wmin, wmax,cluster_delta_tdc,risetime_min,risetime_max,peaktime_min,	peaktime_max, tdcmin, tdcmax, dv, cd, cd2;
      iss >> id.module_id >> id.layer_id  >> tx >> ty >> totx >> toty >>  pedx >>  pedy >>  sigx>>  sigy >> wmin >> wmax >> cluster_min_gap >> cluster_delta_tdc >> risetime_min >> risetime_max >> peaktime_min >> peaktime_max >> tdcmin >> tdcmax >> dv >> cd >> cd2;
      chamber_params_map[id.value32].SetValues(tx, ty, totx, toty, pedx, pedy, sigx, sigy, wmin, wmax,cluster_min_gap,cluster_delta_tdc,risetime_min,risetime_max,peaktime_min,	peaktime_max, tdcmin, tdcmax, dv, cd, cd2);
   }
   ifs->close();
   return flag;


}

bool E16ANA_GTRcalibParams::ReadCalibData(int runID){
	E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();
	std::ifstream *ifs = calib.CalibStreamOpenBinary("GTR-params", runID);	
	if (ifs != NULL){
		return ReadCalibDataCore(ifs);
	}
	else{
		E16FATAL("file open error");
		return false;
	}
}
