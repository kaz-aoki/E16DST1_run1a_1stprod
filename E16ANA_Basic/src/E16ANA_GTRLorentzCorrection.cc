#include "E16ANA_GTRLorentzCorrection.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_FieldMapCalib.hh"

TVector3 E16ANA_GTRLorentzCorrection::CorrectLocalPos(const TVector3 &lpos, double hit_time, const TVector3 &lmom){
   double tan_theta_x = lmom.X()/lmom.Z();
   //double tan_theta_y = lmom.Y()/lmom.Z();
   double lx = lpos.X();
   double ly = lpos.Y();
   double t0 = fT0Func(lx, ly);
   double vd_z = fVDriftZFunc(lx, ly);
   double vd_x = fVDriftXFunc(lx, ly);
   double lconst = fLorentzConstFunc(lx, ly);
   double corrected_lx = lx + (t0-hit_time)*vd_z*tan_theta_x + lconst + (t0-hit_time)*vd_x;
   std::cout << "\tlpos = (" << lx << ", " << ly << ")"
             << ", t0 = " << t0
             << ", vd_z = " << vd_z
             << ", vd_x = " << vd_x
             << ", lconst = " << lconst << std::endl;
   return TVector3(corrected_lx, ly, lpos.Z());
}

namespace E16ANA_GTRLorentzParamFunc {
// Implement functions here.
double const_func(double *val, double *pars){
   return pars[0];
}

double t0_func_103_100_200_300(double *val, double *pars){
   double xx = val[0];
   double yy = val[1];
   double sx = pars[0];
   double sy = pars[1];
   double rho = pars[2];
   double mx = pars[3];
   double my = pars[4];
   double amp = pars[5];
   double ped = pars[6];
   double det = 1.0 - rho*rho;
   double f = (xx-mx)*(xx-mx)/2.0/sx/sx + (yy-my)*(yy-my)/2.0/sy/sy - (xx-mx)*(yy-my)*rho/sx/sy;
   return exp(-f/det) * amp + ped;
}

double t0_func_104_100(double *val, double *pars){
   double xx = val[0];
   double yy = val[1];
   double sx = pars[0];
   double sy = pars[1];
   double rho = pars[2];
   double mx = pars[3];
   double my = pars[4];
   double amp = pars[5];
   double ped = pars[6];
   double det = 1.0 - rho*rho;
   double f = (xx-mx)*(xx-mx)/2.0/sx/sx + (yy-my)*(yy-my)/2.0/sy/sy - (xx-mx)*(yy-my)*rho/sx/sy;
   return exp(-f/det) * amp + ped;
}

double t0_func_104_200(double *val, double *pars){
   double xx = val[0];
   double yy = val[1];
   double sx = pars[0];
   double sy = pars[1];
   double rho = pars[2];
   double mx = pars[3];
   double my = pars[4];
   double amp = pars[5];
   double ped = pars[6];
   double det = 1.0 - rho*rho;
   double f = (xx-mx)*(xx-mx)/2.0/sx/sx + (yy-my)*(yy-my)/2.0/sy/sy - (xx-mx)*(yy-my)*rho/sx/sy;

   double sx2 = 15.0;
   double mx2 = -100.0;
   double sy2 = pars[7];
   double my2 = pars[8];
   double amp2 = pars[9];
   double f2 = (xx-mx2)*(xx-mx2)/2.0/sx2/sx2 + (yy-my2)*(yy-my2)/2.0/sy2/sy2;
   //double f2 = (yy-my2)*(yy-my2)/2.0/sy2/sy2;
   //double step = 1.0/(1.0+exp((xx-mx2)/sx2));

   //return exp(-f/det)*amp + ped + exp(-f2)*step*amp2;
   return exp(-f/det)*amp + ped + exp(-f2)*amp2;
}

double lconst_func_104_100(double *val, double *pars){
   return 3.0;
}

} // namespace E16ANA_GTRLorentzParamFunc

E16ANA_GTRLorentzCorrectionManager::E16ANA_GTRLorentzCorrectionManager(){
   E16ANA_FieldMapCalibParam field_map_param;
   auto &calib = E16ANA_CalibDBManager::Instance();
   field_map_param.ReadConstantData(calib.CurrentRunID());
   double fm_current = field_map_param.FMCurrent();
   std::cout << "E16ANA_GTRLorentzCorrectionManager: FMCurrent = " << field_map_param.FMCurrent() << std::endl;
   double sign = +1.0; // this value will be multiplied by vd_x, lorentz_const
   if (fabs(fm_current) < 10) { // < 10 Ampere, thus zero field run
      sign = 0.0;
   } else if (fm_current < -10.0) { // negative field run
      sign = -1.0;
   }

   using namespace E16ANA_GTRLorentzParamFunc;
   double default_t0[3] = {180.0, 180.0, 180.0};
   double default_vd_z[3] = {0.010, 0.010, 0.010};
   double default_vd_x[3] = {0.35 * 0.91 * 0.010, -0.75 * 0.94 * 0.010, -0.14 * 0.010};
   double default_lconst[3] = {3.18 * 0.91, -2.4 * 0.94, -1.15};
   for (int module_id=1; module_id<10; module_id++) {
      for (int layer_id=0; layer_id<3; layer_id++) {
         fLorentzCorrections[module_id][layer_id].SetMagFieldSign(sign);
         fLorentzCorrections[module_id][layer_id].SetT0Func(const_func, {default_t0[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetVDriftZFunc(const_func, {default_vd_z[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetVDriftXFunc(const_func, {default_vd_x[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetLorentzConstFunc(const_func, {default_lconst[layer_id]});
      }
   }
   for (int module_id=101; module_id<110; module_id++) {
      for (int layer_id=0; layer_id<3; layer_id++) {
         fLorentzCorrections[module_id][layer_id].SetMagFieldSign(sign);
         fLorentzCorrections[module_id][layer_id].SetT0Func(const_func, {default_t0[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetVDriftZFunc(const_func, {default_vd_z[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetVDriftXFunc(const_func, {default_vd_x[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetLorentzConstFunc(const_func, {default_lconst[layer_id]});
      }
   }
   for (int module_id=201; module_id<210; module_id++) {
      for (int layer_id=0; layer_id<3; layer_id++) {
         fLorentzCorrections[module_id][layer_id].SetMagFieldSign(sign);
         fLorentzCorrections[module_id][layer_id].SetT0Func(const_func, {default_t0[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetVDriftZFunc(const_func, {default_vd_z[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetVDriftXFunc(const_func, {default_vd_x[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetLorentzConstFunc(const_func, {default_lconst[layer_id]});
      }
   }

   // Set functions and parameters here.
   // fLorentzCorrections[module_id][layer_id]
   // and Set T0, VDriftZ, VDriftX, LorentzConst functions.
   //GTR-Module103
   fLorentzCorrections[103][0].SetT0Func(t0_func_103_100_200_300, {
         94.0687,
         590.154,
         -0.985214,
         233.857,
         -1503.67,
         870.409,
         134.171
         });
   fLorentzCorrections[103][1].SetT0Func(t0_func_103_100_200_300, {
         52.1901,
         50.5459,
         -0.221594,
         -0.198514,
         2.20718,
         125.667,
         137.904
         });
   fLorentzCorrections[103][2].SetT0Func(t0_func_103_100_200_300, {
         117.737,
         167.237,
         -0.105471,
         8.01617,
         -11.0619,
         158.059,
         99.538
         });
   fLorentzCorrections[103][0].SetVDriftZFunc(const_func, {0.0078});
   fLorentzCorrections[103][1].SetVDriftZFunc(const_func, {0.010});
   fLorentzCorrections[103][2].SetVDriftZFunc(const_func, {0.0184});

   //GTR-Module104
   fLorentzCorrections[104][0].SetT0Func(t0_func_104_100, {
         54.8305,
         91.8214,
         -0.859271,
         -27.3381,
         49.0041,
         94.8484,
         97.6324
         });
   fLorentzCorrections[104][1].SetT0Func(t0_func_104_200, {
         927.533,
         203.666,
         -0.845532,
         1184.03,
         -218.078,
         385.489,
         63.2379,
         45.5075,
         -0.281632,
         205.572
         });
   fLorentzCorrections[104][2].SetT0Func(const_func, {184.981});

   fLorentzCorrections[104][0].SetVDriftZFunc(const_func, {0.0105});
   fLorentzCorrections[104][1].SetVDriftZFunc(const_func, {0.010});
   fLorentzCorrections[104][2].SetVDriftZFunc(const_func, {0.010});

   fLorentzCorrections[104][0].SetLorentzConstFunc(lconst_func_104_100);
   fLorentzCorrections[104][1].SetLorentzConstFunc(lconst_func_104_100);
   fLorentzCorrections[104][2].SetLorentzConstFunc(lconst_func_104_100);
   //GTR-Module106
   //GTR-Module107
}

E16ANA_GTRLorentzCorrectionManager* E16ANA_GTRLorentzCorrectionManager::fInstance = nullptr;

E16ANA_GTRLorentzCorrectionManager& E16ANA_GTRLorentzCorrectionManager::Instance(){
   if (fInstance == nullptr) {
      fInstance = new E16ANA_GTRLorentzCorrectionManager();
   }
   return *fInstance;
}

TVector3 E16ANA_GTRLorentzCorrectionManager::CorrectLocalPos(int module_id, int layer_id, const TVector3 &lpos, double hit_time, const TVector3 &lmom){
   return fLorentzCorrections[module_id][layer_id].CorrectLocalPos(lpos, hit_time, lmom);
}

void E16ANA_GTRLorentzCorrection::SetT0Func(std::function<double(double*, double*)> func, std::initializer_list<double> params){
   std::vector<double> p;
   for (auto &e : params) {
      p.push_back(e);
   }
   SetT0Func(func, p);
}
void E16ANA_GTRLorentzCorrection::SetT0Func(std::function<double(double*, double*)> func, std::vector<double> &params){
   fT0Func.fFunc = func;
   fT0Func.fParams = params;
}

void E16ANA_GTRLorentzCorrection::SetVDriftZFunc(std::function<double(double*, double*)> func, std::initializer_list<double> params){
   std::vector<double> p;
   for (auto &e : params) {
      p.push_back(e);
   }
   SetVDriftZFunc(func, p);
}
void E16ANA_GTRLorentzCorrection::SetVDriftZFunc(std::function<double(double*, double*)> func, std::vector<double> &params){
   fVDriftZFunc.fFunc = func;
   fVDriftZFunc.fParams = params;
}

void E16ANA_GTRLorentzCorrection::SetVDriftXFunc(std::function<double(double*, double*)> func, std::initializer_list<double> params){
   std::vector<double> p;
   for (auto &e : params) {
      p.push_back(e);
   }
   SetVDriftXFunc(func, p);
}
void E16ANA_GTRLorentzCorrection::SetVDriftXFunc(std::function<double(double*, double*)> func, std::vector<double> &params){
   fVDriftXFunc.fFunc = func;
   fVDriftXFunc.fParams = params;
}

void E16ANA_GTRLorentzCorrection::SetLorentzConstFunc(std::function<double(double*, double*)> func, std::initializer_list<double> params){
   std::vector<double> p;
   for (auto &e : params) {
      p.push_back(e);
   }
   SetLorentzConstFunc(func, p);
}
void E16ANA_GTRLorentzCorrection::SetLorentzConstFunc(std::function<double(double*, double*)> func, std::vector<double> &params){
   fLorentzConstFunc.fFunc = func;
   fLorentzConstFunc.fParams = params;
}

