#ifndef E16ANA_GTR_LORENTZ_CORRECTION_HH
#define E16ANA_GTR_LORENTZ_CORRECTION_HH

#include <unordered_map>
#include <array>
#include <functional>
#include <TVector3.h>

class E16ANA_GTRLorentzCorrection {
public:
   E16ANA_GTRLorentzCorrection() = default;
   ~E16ANA_GTRLorentzCorrection() = default;
   TVector3 CorrectLocalPos(const TVector3 &lpos, double hit_time, const TVector3 &lmom);
   /*
   corrected_lx = lx + (t0-hit_time)*vd_z*tan_theta_x
                     + lorentz_const
                     + (t0-hit_time)*vd_x
   t0, vd_z : independent on mag field
   lorentz_const, vd_x : sign depends on the mag field
   */
   void PrintParams(const TVector3 &lpos);
   void SetMagFieldSign(double sign){
      fVDriftXFunc.fSign = sign;
      fLorentzConstRoughFunc.fSign = sign;
      fLorentzConstFunc.fSign = sign;
   };
   void SetT0Func(std::function<double(double*, double*)> func, std::initializer_list<double> params = {});
   void SetVDriftZFunc(std::function<double(double*, double*)> func, std::initializer_list<double> params = {});
   void SetVDriftXFunc(std::function<double(double*, double*)> func, std::initializer_list<double> params = {});
   void SetLorentzConstRoughFunc(std::function<double(double*, double*)> func, std::initializer_list<double> params = {});
   void SetLorentzConstFunc(std::function<double(double*, double*)> func, std::initializer_list<double> params = {});

   void SetT0Func(std::function<double(double*, double*)> func, std::vector<double> &params);
   void SetVDriftZFunc(std::function<double(double*, double*)> func, std::vector<double> &params);
   void SetVDriftXFunc(std::function<double(double*, double*)> func, std::vector<double> &params);
   void SetLorentzConstRoughFunc(std::function<double(double*, double*)> func, std::vector<double> &params);
   void SetLorentzConstFunc(std::function<double(double*, double*)> func, std::vector<double> &params);

private:
   class Func2D {
   public:
      Func2D() = default;
      ~Func2D() = default;
      double operator()(double lx, double ly){
         if (fFunc) {
            std::vector<double> val = {lx, ly};
            return fFunc(&val[0], &fParams[0]) * fSign;
         }
         return 0.0;
      };
      std::function<double(double*, double*)> fFunc;
      std::vector<double> fParams;
      double fSign{1.0};
   };
   Func2D fT0Func;
   Func2D fVDriftZFunc;
   Func2D fVDriftXFunc;
   Func2D fLorentzConstRoughFunc;
   Func2D fLorentzConstFunc;

};

class E16ANA_GTRLorentzCorrectionManager {
public:
   static E16ANA_GTRLorentzCorrectionManager& Instance();
   TVector3 CorrectLocalPos(int module_id, int layer_id, const TVector3 &lpos, double hit_time, const TVector3 &lmom);
   void PrintParams(int module_id, int layer_id, const TVector3 &lpos);

private:
   E16ANA_GTRLorentzCorrectionManager();
   ~E16ANA_GTRLorentzCorrectionManager() = default;

   static E16ANA_GTRLorentzCorrectionManager *fInstance;
   std::unordered_map<int, std::array<E16ANA_GTRLorentzCorrection, 3>> fLorentzCorrections;

};

#endif // E16ANA_GTR_LORENTZ_CORRECTION_HH
