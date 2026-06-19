#include "E16ANA_GTRLorentzCorrection.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_FieldMapCalib.hh"

#include <TMath.h>

TVector3 E16ANA_GTRLorentzCorrection::CorrectLocalPos(const TVector3 &lpos, double hit_time, const TVector3 &lmom, double corr[]){
   double tan_theta_x = lmom.X()/lmom.Z();
   //double tan_theta_y = lmom.Y()/lmom.Z();
   double lx = lpos.X();
   double ly = lpos.Y();
   double lconst_rough = fLorentzConstRoughFunc(lx, ly);
   double t0 = fT0Func(lx+lconst_rough, ly);
   double vd_z = fVDriftZFunc(lx+lconst_rough, ly);
   double vd_x = fVDriftXFunc(lx+lconst_rough, ly);
   double lconst = fLorentzConstFunc(lx+lconst_rough, ly);
   double fgeom  = fFGeom(lx+lconst_rough, ly);
   double corrected_lx = lx + (t0-hit_time)*vd_z*tan_theta_x + lconst_rough + lconst - (t0-hit_time)*vd_x   - fgeom;
   corr[0] = lconst;
   corr[1] = -fgeom;
   corr[2] = t0;
   corr[3] = (t0-hit_time)*vd_z*tan_theta_x;
   corr[4] = - (t0-hit_time)*vd_x;

   //   printf("lconst_rough::%f \n",lconst_rough);
   //                   readout        incident angle            //lorentz constant      //lorentz time depend  //geometry correnction
   //if(fabs(t0-165)>0.0001&&fabs(lconst)>0.001){
   //printf("%f %f %f %f %f %f \n",lx+lconst_rough,ly,t0,lconst,corrected_lx-lx,corrected_lx);
   //}
   
//	std::cout << "(lx, ly)     = " << lx + lconst_rough << ", " << ly << std::endl;
//	std::cout << "t0           = " << t0 << std::endl;
//	std::cout << "lconst_fine  = " << lconst << std::endl;
//	std::cout << "correct lx   = " << corrected_lx << std::endl;
//	std::cout << "dtx          = " << (t0-hit_time)*vd_z*tan_theta_x << std::endl;
//	std::cout << "dax          = " << - (t0-hit_time)*vd_x << std::endl;

   return TVector3(corrected_lx, ly, lpos.Z());
}

void E16ANA_GTRLorentzCorrection::PrintParams(const TVector3 &lpos){
   double lx = lpos.X();
   double ly = lpos.Y();
   double lconst_rough = fLorentzConstRoughFunc(lx, ly);
   double t0 = fT0Func(lx+lconst_rough, ly);
   double vd_z = fVDriftZFunc(lx+lconst_rough, ly);
   double vd_x = fVDriftXFunc(lx+lconst_rough, ly);
   double lconst = fLorentzConstFunc(lx+lconst_rough, ly);
   std::cout << "\tlpos = (" << lx << ", " << ly << ")"
             << ", t0 = " << t0
             << ", vd_z = " << vd_z
             << ", vd_x = " << vd_x
             << ", lconst_rough = " << lconst_rough
             << ", lconst = " << lconst
             << ", lconst_sum = " << lconst_rough + lconst << std::endl;
}

namespace E16ANA_GTRLorentzParamFunc {
// Implement functions here.
double const_func(double *val, double *pars){
   return pars[0];
}


double lconst_func_103_100(double *val, double *par){
  double x    = val[0];
  double y    = -1*val[1];
  double dl   = (-0.13+0.0029*x+0.00012*x*x-1.5e-6*x*x*x-4.2e-8*x*x*x*x)+y*(0.0023+6.4e-6*x-1.4e-6*x*x)+y*y*(8.4e-5-3.6e-7*x-4.2e-8*x*x);

  //double dl2  = 0.4*(TMath::Gaus(y,-25,15)-TMath::Gaus(y,35,12))*TMath::Gaus(x,-40,15)+(0.3*TMath::Gaus(y,-25,15)-0.2*TMath::Gaus(y,30,12))*TMath::Gaus(x,35,15);
  
  //return -1.6*dl - dl2;

  double dl2  = (5.7e-3+3.8e-3*y-3.0e-5*y*y-2.4e-6*y*y*y+2.4e-8*y*y*y*y)+x*(-1.7e-4+5.5e-6*y-1.6e-7*y*y)+x*x*(-3.2e-6-2.6e-6*y+8e-9*y*y+1.5e-9*y*y*y-6.8e-12*y*y*y*y);

  double dl3  = 0.2*(1-1/(exp(0.2*(x-40))+1))*TMath::Gaus(y,-32,10)+0.15*(1-1/(exp(0.2*(x-41))+1))*TMath::Gaus(y,15,12);
  
  return -1.6*dl - 1.6*dl2 - dl3;
}

double lconst_func_103_200(double *val, double *par){
  double x    = -1*val[0];
  double y    = val[1];
  double dl   = 0.6*(1-1/(exp(0.12*(abs(x-20)-60))+1));
  //double dl2  =(0.018-0.0062*y+3.1e-5*y*y+1e-6*y*y*y-5.6e-9*y*y*y*y)+x*(0.00093+1.9e-5*y)+x*x*(-4.9e-6+8.1e-7*y+1.5e-9*y*y-8.6e-11*y*y*y-1.9e-13*y*y*y*y);
  double dl2 = (3.9e-2-1.8e-4*y+4.4e-5*y*y+1.7e-8*y*y*y-5.8e-9*y*y*y*y)+x*(9.2e-4+2.9e-5*y-4.4e-8*y*y-2.6e-9*y*y*y)
    + x*x*(1.0e-5+2.8e-7*y-2.8e-10*y*y-2.3e-11*y*y*y);
  double dl3 = (-1.2e-1+5.4e-3*y+9.6e-6*y*y-2.9e-6*y*y*y+4.8e-11*y*y*y*y+2.9e-10*y*y*y*y*y)
    +x*(8.8e-4+3.4e-6*y-3.8e-8*y*y)+x*x*(1.8e-5+7.0e-8*y-1.4e-9*y*y);
  
  return dl + 1.35*dl2 + dl3;
  //return dl + dl2;
}

double lconst_func_103_300(double *val, double *par){
  double x    = -1*val[0];
  double y    = val[1];
  return 0;
}

double t0_func_103_300(double *val, double *pars){
  return 165;
}

double t0_func_103_100(double *val, double *pars){
  double x   = val[0];
  double y   = -1*val[1];

  double p0 = -13.8   + 0.0074*x  +  0.02*x*x    -0.00023*x*x*x -2.1e-5*x*x*x*x;
  double p1 = 0.0057  - 0.00031*x - 0.00023*x*x;
  double p2 = -0.0054 + 0.00013*x - 3.8e-7*x*x;
  if(p0<-70) p0 = -70;
  double dt  = p0 + p1*y + p2*y*y;
    
  //return 155 - 0.8*dt;
   return 176 - 0.8*dt;
}

double t0_func_103_200(double *val, double *pars){
  double x   = -1*val[0];
  double y   =    val[1];
  double dt  = (-5.6+4.8e-1*y-6.0e-3*y*y-7.5e-5*y*y*y+1.3e-6*y*y*y*y)+ x*(3.3e-2-4.4e-3*y+3.3e-5*y*y)
    + x*x*(-1.3e-2-2.7e-4*y-2.1e-6*y*y+3.6e-8*y*y*y+1.6e-10*y*y*y*y);
  if(dt> 120) dt =  120;
  if(dt<-120) dt = -120;
  /*
  double dt  = (-1.3-0.28*x-0.012*x*x+5.8e-5*x*x*x)+y*(-0.038-0.0063*x-2.6e-5*x*x)+y*y*(0.00047+3.8e-5*x-3.7e-7*x*x);
  
  if(dt> 100) dt =  100;
  if(dt<-100) dt = -100;
  return 175 + dt;
  */
  //return 175 + 0.8*dt;
  return 196 + 0.8*dt;
}
  
double t0_func_103_100_200_300(double *val, double *pars){
   double xx = val[0];
   double yy = val[1];
   double sx = pars[0];
   return 180;
}

static inline double pol2(double x, double c0, double c1, double c2){
  return c0 + c1*x + c2*x*x;
}

  

double t0_func_104_100(double *val, double *pars){
  (void)pars;

  const double x = -1.0 * val[0] /100.0;
  const double y = -1.0 * val[1] /100.0;

  double ret =
                -12.397
    + (-64.9342 ) * x
    + ( 309.453  ) * x * x
    + (-3915.02  ) * x * x * x
    + (-27895.6  ) * x * x * x * x
    + ( 25088.8  ) * x * x * x * x * x
    + ( 136865   ) * x * x * x * x * x * x

    + (-40.2492  ) * y
    + (-87.4823  ) * x * y
    + ( 16.2177  ) * x * x * y
    + ( 2507.65  ) * x * x * x * y
    + (-5092.01  ) * x * x * x * x * y
    + (-12199.5  ) * x * x * x * x * x * y

    + ( 167.268  ) * y * y
    + (-381.252  ) * x * y * y
    + ( 719.819  ) * x * x * y * y
    + (-8410.98  ) * x * x * x * y * y
    + (-22272.2  ) * x * x * x * x * y * y

    + ( 553.382  ) * y * y * y
    + ( 332.799  ) * x * y * y * y
    + ( 985.234  ) * x * x * y * y * y
    + ( 1945     ) * x * x * x * y * y * y

    + (-563.474  ) * y * y * y * y
    + ( 6835.73  ) * x * y * y * y * y
    + ( 32239.9  ) * x * x * y * y * y * y

    + (-2232.7   ) * y * y * y * y * y
    + (-4928.07  ) * x * y * y * y * y * y

    + (-3210.01  ) * y * y * y * y * y * y;
  ret*=0.2;
  if(ret>50)ret=50;
  if(ret<-50)ret=-50;
  double cor = 
	        4.57057
    + ( 28.8439  ) * x
    + ( 789.359  ) * x * x
    + ( 2172.73  ) * x * x * x
    + (-3389.67  ) * x * x * x * x
    + (-44034.1  ) * x * x * x * x * x
    + (-14054.4  ) * x * x * x * x * x * x
    + ( 193720   ) * x * x * x * x * x * x * x
    + ( 128111   ) * x * x * x * x * x * x * x * x

    + ( 15.6619  ) * y
    + ( 394.308  ) * x * y
    + (-339.253  ) * x * x * y
    + (-4664.48  ) * x * x * x * y
    + ( 7264.73  ) * x * x * x * x * y
    + ( 53194.1  ) * x * x * x * x * x * y
    + (-8250.04  ) * x * x * x * x * x * x * y
    + (-145185  ) * x * x * x * x * x * x * x * y

    + (-189.342  ) * y * y
    + (-474.184  ) * x * y * y
    + (-312.004  ) * x * x * y * y
    + ( 11025.7  ) * x * x * x * y * y
    + ( 37339.2  ) * x * x * x * x * y * y
    + (-18179.8  ) * x * x * x * x * x * y * y
    + (-309888  ) * x * x * x * x * x * x * y * y

    + (-1219.91  ) * y * y * y
    + (-4995.36  ) * x * y * y * y
    + ( 3923.63  ) * x * x * y * y * y
    + ( 2605.51  ) * x * x * x * y * y * y
    + (-26237.5  ) * x * x * x * x * y * y * y
    + (-26785.7  ) * x * x * x * x * x * y * y * y

    + ( 3020.97  ) * y * y * y * y
    + (-4622.64  ) * x * y * y * y * y
    + (-253.685  ) * x * x * y * y * y * y
    + (-18631.8  ) * x * x * x * y * y * y * y
    + ( 251273  ) * x * x * x * x * y * y * y * y

    + ( 9758.77  ) * y * y * y * y * y
    + ( 27330.6  ) * x * y * y * y * y * y
    + (-17484.9  ) * x * x * y * y * y * y * y
    + ( 8295.55  ) * x * x * x * y * y * y * y * y

    + (-35737.7  ) * y * y * y * y * y * y
    + ( 17793.2  ) * x * y * y * y * y * y * y
    + (-109410  ) * x * x * y * y * y * y * y * y

    + (-21641.9  ) * y * y * y * y * y * y * y
    + (-45108.2  ) * x * y * y * y * y * y * y * y

    + ( 105865  ) * y * y * y * y * y * y * y * y;
  if(cor>100)cor=100;
  if(cor<-100)cor=-100;
  //return 195 + ret + cor;
  return 228 + ret + cor;
}
double t0_func_104_200(double *val, double *pars){
   const double x = -1*val[0]/100.0;
   const double y = val[1]/100.0;

   double ret =
    + (-14.9757 ) * x
    + (-33.9399 ) * x * x
    + ( 70.7641  ) * x * x * x
    + ( 35.0905  ) * x * x * x * x
    + ( 270.802  ) * x * x * x * x * x
    + (-223.131  ) * x * x * x * x * x * x

    + (-21.0501 ) * y
    + (-30.4706 ) * x * y
    + ( 21.8793  ) * x * x * y
    + (-27.8682 ) * x * x * x * y
    + (-12.1692 ) * x * x * x * x * y
    + ( 158.247  ) * x * x * x * x * x * y

    + (-57.3837 ) * y * y
    + (-78.293  ) * x * y * y
    + (-104.018 ) * x * x * y * y
    + (-176.987 ) * x * x * x * y * y
    + ( 66.3612  ) * x * x * x * x * y * y

    + ( 58.9714  ) * y * y * y
    + ( 142.96   ) * x * y * y * y
    + (-155.981 ) * x * x * y * y * y
    + (-136.6   ) * x * x * x * y * y * y

    + ( 162.349  ) * y * y * y * y
    + ( 136.91   ) * x * y * y * y * y
    + ( 155.62   ) * x * x * y * y * y * y

    + (-18.4197 ) * y * y * y * y * y
    + (-112.226 ) * x * y * y * y * y * y

    + (-66.4606 ) * y * y * y * y * y * y;
   ret*=0.4;
   if(ret>50)ret=50;
   if(ret<-50)ret=-50;
   double cor =
                 -1.4909
    + ( 1.21824 ) * x
    + ( 6.26246 ) * x * x
    + (-325.833 ) * x * x * x
    + ( 621.77  ) * x * x * x * x
    + ( 458.706 ) * x * x * x * x * x
    + (-1006.79 ) * x * x * x * x * x * x

    + ( 11.3783 ) * y
    + ( 52.271  ) * x * y
    + ( 3.94803 ) * x * x * y
    + (-175.117 ) * x * x * x * y
    + ( 120.821 ) * x * x * x * x * y
    + ( 166.842 ) * x * x * x * x * x * y

    + (-12.4554 ) * y * y
    + (-42.5329 ) * x * y * y
    + (-18.4704 ) * x * x * y * y
    + (-57.2491 ) * x * x * x * y * y
    + (-43.8098 ) * x * x * x * x * y * y

    + (-59.2744 ) * y * y * y
    + (-147.924 ) * x * y * y * y
    + (-66.8537 ) * x * x * y * y * y
    + ( 117.992 ) * x * x * x * y * y * y

    + ( 68.6134 ) * y * y * y * y
    + ( 94.4413 ) * x * y * y * y * y
    + (-75.1733 ) * x * x * y * y * y * y

    + ( 62.3284 ) * y * y * y * y * y
    + ( 111.32  ) * x * y * y * y * y * y

    + (-34.8908 ) * y * y * y * y * y * y;
   if(cor>30)cor=30;
   if(cor<-30)cor=-30;
   double adj =
      -5.20261
    + ( 12.5539  ) * x
    + (-10.7177  ) * x * x
    + (-272.398  ) * x * x * x
    + ( 829.405  ) * x * x * x * x
    + ( 357.08   ) * x * x * x * x * x
    + (-1980.29  ) * x * x * x * x * x * x
    + (-23.9623  ) * x * x * x * x * x * x * x
    + ( 1012.32  ) * x * x * x * x * x * x * x * x

    + (-4.14501  ) * y
    + (-7.04455  ) * x * y
    + ( 99.258   ) * x * x * y
    + (-42.2819  ) * x * x * x * y
    + ( 44.7394  ) * x * x * x * x * y
    + ( 93.2611  ) * x * x * x * x * x * y
    + (-27.4544  ) * x * x * x * x * x * x * y
    + (-8.01186  ) * x * x * x * x * x * x * x * y

    + ( 14.965   ) * y * y
    + (-87.5983  ) * x * y * y
    + ( 38.7636  ) * x * x * y * y
    + ( 384.42   ) * x * x * x * y * y
    + ( 116.438  ) * x * x * x * x * y * y
    + (-210.628  ) * x * x * x * x * x * y * y
    + ( 418.403  ) * x * x * x * x * x * x * y * y

    + (-32.3358  ) * y * y * y
    + ( 52.9715  ) * x * y * y * y
    + (-314.719  ) * x * x * y * y * y
    + (-22.3304  ) * x * x * x * y * y * y
    + (-95.9525  ) * x * x * x * x * y * y * y
    + (-252.365  ) * x * x * x * x * x * y * y * y

    + (-67.0235  ) * y * y * y * y
    + ( 93.6322  ) * x * y * y * y * y
    + (-275.63   ) * x * x * y * y * y * y
    + (-309.606  ) * x * x * x * y * y * y * y
    + (-568.965  ) * x * x * x * x * y * y * y * y

    + ( 85.9107  ) * y * y * y * y * y
    + (-109.237  ) * x * y * y * y * y * y
    + ( 246.674  ) * x * x * y * y * y * y * y
    + ( 187.787  ) * x * x * x * y * y * y * y * y

    + ( 155.176  ) * y * y * y * y * y * y
    + (-1.90917  ) * x * y * y * y * y * y * y
    + ( 294.821  ) * x * x * y * y * y * y * y * y

    + (-50.9537  ) * y * y * y * y * y * y * y
    + ( 33.8391  ) * x * y * y * y * y * y * y * y

    + (-89.338   ) * y * y * y * y * y * y * y * y;
   adj *= 0.6;
   if(adj>50)adj=50;
   if(adj<-30)adj=-30;

   ret*=0.4;
   cor*=0.4;
   adj*=0.4;
   double adj2 = 
	         -5.50765
    + (-8.23019 ) * x
    + ( 26.5367  ) * x * x
    + (-275.538  ) * x * x * x
    + ( 694.546  ) * x * x * x * x
    + ( 620.138  ) * x * x * x * x * x
    + (-1669.81  ) * x * x * x * x * x * x
    + (-256.027  ) * x * x * x * x * x * x * x
    + ( 897.805  ) * x * x * x * x * x * x * x * x

    + ( 5.51578  ) * y
    + ( 46.5146  ) * x * y
    + ( 9.86666  ) * x * x * y
    + (-186.671  ) * x * x * x * y
    + ( 70.5034  ) * x * x * x * x * y
    + ( 274.31   ) * x * x * x * x * x * y
    + (-418.261  ) * x * x * x * x * x * x * y
    + (-452.579  ) * x * x * x * x * x * x * x * y

    + ( 3.5642   ) * y * y
    + (-25.4634  ) * x * y * y
    + (-112.692  ) * x * x * y * y
    + ( 154.599  ) * x * x * x * y * y
    + (-194.885  ) * x * x * x * x * y * y
    + (-255.28   ) * x * x * x * x * x * y * y
    + (-30.566   ) * x * x * x * x * x * x * y * y

    + ( 13.2991  ) * y * y * y
    + (-108.162  ) * x * y * y * y
    + (-135.27   ) * x * x * y * y * y
    + ( 41.362   ) * x * x * x * y * y * y
    + ( 533.395  ) * x * x * x * x * y * y * y
    + ( 429.889  ) * x * x * x * x * x * y * y * y

    + (-26.4398  ) * y * y * y * y
    + ( 68.2104  ) * x * y * y * y * y
    + ( 148.341  ) * x * x * y * y * y * y
    + (-11.347   ) * x * x * x * y * y * y * y
    + ( 244.657  ) * x * x * x * x * y * y * y * y

    + (-86.6318  ) * y * y * y * y * y
    + ( 78.0664  ) * x * y * y * y * y * y
    + (-26.3317  ) * x * x * y * y * y * y * y
    + (-99.8988  ) * x * x * x * y * y * y * y * y

    + ( 133.564  ) * y * y * y * y * y * y
    + (-36.9036  ) * x * y * y * y * y * y * y
    + (-172.963  ) * x * x * y * y * y * y * y * y

    + ( 60.089   ) * y * y * y * y * y * y * y
    + (-8.78192  ) * x * y * y * y * y * y * y * y

    + (-76.077   ) * y * y * y * y * y * y * y * y;
   adj2 *= 0.6;
      double adj3 =
                    -3.02195
    + ( 28.3302  ) * x
    + (-45.7677  ) * x * x
    + (-241.03   ) * x * x * x
    + ( 199.446  ) * x * x * x * x
    + (-222.429  ) * x * x * x * x * x
    + ( 150.792  ) * x * x * x * x * x * x
    + ( 931.396  ) * x * x * x * x * x * x * x
    + (-523.653  ) * x * x * x * x * x * x * x * x

    + (-0.667509 ) * y
    + (-19.1559  ) * x * y
    + ( 16.8039  ) * x * x * y
    + ( 276.954  ) * x * x * x * y
    + (-542.376  ) * x * x * x * x * y
    + (-265.077  ) * x * x * x * x * x * y
    + ( 1009.23  ) * x * x * x * x * x * x * y
    + (-237.244  ) * x * x * x * x * x * x * x * y

    + (-79.7352  ) * y * y
    + ( 24.1116  ) * x * y * y
    + ( 49.0796  ) * x * x * y * y
    + ( 295.606  ) * x * x * x * y * y
    + ( 1440.68  ) * x * x * x * x * y * y
    + (-534.058  ) * x * x * x * x * x * y * y
    + (-170.936  ) * x * x * x * x * x * x * y * y

    + (-28.0809  ) * y * y * y
    + (-116.587  ) * x * y * y * y
    + ( 215.965  ) * x * x * y * y * y
    + ( 152.452  ) * x * x * x * y * y * y
    + (-336.117  ) * x * x * x * x * y * y * y
    + ( 689.608  ) * x * x * x * x * x * y * y * y

    + ( 380.978  ) * y * y * y * y
    + (-115.058  ) * x * y * y * y * y
    + (-1245.79  ) * x * x * y * y * y * y
    + (-72.4818  ) * x * x * x * y * y * y * y
    + (-1204.98  ) * x * x * x * x * y * y * y * y

    + ( 90.8567  ) * y * y * y * y * y
    + ( 233.762  ) * x * y * y * y * y * y
    + (-28.4124  ) * x * x * y * y * y * y * y
    + (-648.373  ) * x * x * x * y * y * y * y * y

    + (-583.813  ) * y * y * y * y * y * y
    + ( 164.296  ) * x * y * y * y * y * y * y
    + ( 1314.08  ) * x * x * y * y * y * y * y * y

    + (-80.326   ) * y * y * y * y * y * y * y
    + (-126.776  ) * x * y * y * y * y * y * y * y

    + ( 324.001  ) * y * y * y * y * y * y * y * y;
if(adj3>30)adj3 =  30;
if(adj3<-30)adj3 =  -30;
//return 235 + ret + cor + adj + adj2 + adj3;
 return 268 + ret + cor + adj + adj2 + adj3;
}


double t0_func_104_300(double *val, double *pars){
  double x  = -1.0*val[0]/100;
  double y  = 1.0*val[1]/100;
    double ret =
                -25.8697
    + (-130.707 ) * x
    + (-298.056 ) * x * x
    + ( 1167.23  ) * x * x * x
    + ( 3.44367  ) * x * x * x * x
    + (-1782.39  ) * x * x * x * x * x
    + ( 635.976  ) * x * x * x * x * x * x
    + ( 665.267  ) * x * x * x * x * x * x * x
    + (-306.655  ) * x * x * x * x * x * x * x * x

    + ( 34.5488  ) * y
    + (-31.4657  ) * x * y
    + (-6.88693  ) * x * x * y
    + ( 233.22   ) * x * x * x * y
    + (-432.781  ) * x * x * x * x * y
    + (-192.675  ) * x * x * x * x * x * y
    + ( 202.279  ) * x * x * x * x * x * x * y
    + ( 93.6405  ) * x * x * x * x * x * x * x * y

    + ( 111.084  ) * y * y
    + (-68.4378  ) * x * y * y
    + (-398.236  ) * x * x * y * y
    + (-300.718  ) * x * x * x * y * y
    + (-601.769  ) * x * x * x * x * y * y
    + ( 130.513  ) * x * x * x * x * x * y * y
    + ( 526.325  ) * x * x * x * x * x * x * y * y

    + (-102.851  ) * y * y * y
    + (-110.954  ) * x * y * y * y
    + ( 412.396  ) * x * x * y * y * y
    + ( 47.041   ) * x * x * x * y * y * y
    + (-24.5125  ) * x * x * x * x * y * y * y
    + ( 51.5936  ) * x * x * x * x * x * y * y * y

    + ( 31.5709  ) * y * y * y * y
    + ( 223.463  ) * x * y * y * y * y
    + ( 727.651  ) * x * x * y * y * y * y
    + ( 183.114  ) * x * x * x * y * y * y * y
    + (-371.054  ) * x * x * x * x * y * y * y * y

    + ( 24.4687  ) * y * y * y * y * y
    + ( 51.0319  ) * x * y * y * y * y * y
    + (-95.4566  ) * x * x * y * y * y * y * y
    + (-118.809  ) * x * x * x * y * y * y * y * y

    + (-159.686  ) * y * y * y * y * y * y
    + (-127.225  ) * x * y * y * y * y * y * y
    + (-28.0622  ) * x * x * y * y * y * y * y * y

    + ( 12.3168  ) * y * y * y * y * y * y * y
    + ( 13.1683  ) * x * y * y * y * y * y * y * y

    + ( 39.9501  ) * y * y * y * y * y * y * y * y;
  ret *= 0.2;
  if(ret>100)ret=100;
  if(ret<-100)ret=-100;

    double cor =
                1.27514
    + (-56.8258 ) * x
    + (-163.897 ) * x * x
    + ( 404.559 ) * x * x * x
    + ( 89.0827 ) * x * x * x * x
    + (-709.423 ) * x * x * x * x * x
    + ( 355.251 ) * x * x * x * x * x * x
    + ( 298.76  ) * x * x * x * x * x * x * x
    + (-208.889 ) * x * x * x * x * x * x * x * x

    + ( 7.64113 ) * y
    + ( 14.5797 ) * x * y
    + ( 1.60504 ) * x * x * y
    + (-38.2819 ) * x * x * x * y
    + (-18.1223 ) * x * x * x * x * y
    + (-25.7647 ) * x * x * x * x * x * y
    + (-4.80343 ) * x * x * x * x * x * x * y
    + ( 36.6126 ) * x * x * x * x * x * x * x * y

    + ( 15.0026 ) * y * y
    + (-7.26867 ) * x * y * y
    + (-165.022 ) * x * x * y * y
    + ( 77.1072 ) * x * x * x * y * y
    + (-386.658 ) * x * x * x * x * y * y
    + (-92.342  ) * x * x * x * x * x * y * y
    + ( 377.771 ) * x * x * x * x * x * x * y * y

    + (-2.48716 ) * y * y * y
    + (-107.379 ) * x * y * y * y
    + ( 16.5129 ) * x * x * y * y * y
    + ( 152.467 ) * x * x * x * y * y * y
    + (-16.4071 ) * x * x * x * x * y * y * y
    + (-48.0817 ) * x * x * x * x * x * y * y * y

    + ( 103.892 ) * y * y * y * y
    + ( 7.351   ) * x * y * y * y * y
    + ( 304.224 ) * x * x * y * y * y * y
    + ( 42.2278 ) * x * x * x * y * y * y * y
    + (-291.057 ) * x * x * x * x * y * y * y * y

    + (-7.12832 ) * y * y * y * y * y
    + ( 79.1403 ) * x * y * y * y * y * y
    + ( 27.5228 ) * x * x * y * y * y * y * y
    + (-29.8594 ) * x * x * x * y * y * y * y * y

    + (-166.328 ) * y * y * y * y * y * y
    + (-9.408   ) * x * y * y * y * y * y * y
    + ( 34.4116 ) * x * x * y * y * y * y * y * y

    + (-0.386555) * y * y * y * y * y * y * y
    + (-16.3847 ) * x * y * y * y * y * y * y * y

    + ( 47.4326 ) * y * y * y * y * y * y * y * y;
  cor *= 0.6;
  if(cor>100)cor=100;
  if(cor<-50)cor=-50;
    double adj =
                1.93331
    + (-34.1813 ) * x
    + (-70.0434 ) * x * x
    + ( 275.074 ) * x * x * x
    + (-106.53  ) * x * x * x * x
    + (-391.829 ) * x * x * x * x * x
    + ( 467.812 ) * x * x * x * x * x * x
    + ( 137.954 ) * x * x * x * x * x * x * x
    + (-258.802 ) * x * x * x * x * x * x * x * x

    + (-13.1471 ) * y
    + (-45.4978 ) * x * y
    + ( 121.156 ) * x * x * y
    + ( 187.326 ) * x * x * x * y
    + (-76.556  ) * x * x * x * x * y
    + (-134.308 ) * x * x * x * x * x * y
    + (-15.2703 ) * x * x * x * x * x * x * y
    + ( 42.5634 ) * x * x * x * x * x * x * x * y

    + (-8.07728 ) * y * y
    + ( 21.7218 ) * x * y * y
    + (-134.142 ) * x * x * y * y
    + ( 97.3256 ) * x * x * x * y * y
    + (-266.565 ) * x * x * x * x * y * y
    + (-149.638 ) * x * x * x * x * x * y * y
    + ( 478.031 ) * x * x * x * x * x * x * y * y

    + ( 54.4212 ) * y * y * y
    + ( 74.1004 ) * x * y * y * y
    + (-283.581 ) * x * x * y * y * y
    + (-338.928 ) * x * x * x * y * y * y
    + ( 53.0443 ) * x * x * x * x * y * y * y
    + ( 194.432 ) * x * x * x * x * x * y * y * y

    + ( 96.1389 ) * y * y * y * y
    + (-51.8842 ) * x * y * y * y * y
    + ( 217.42  ) * x * x * y * y * y * y
    + ( 74.3597 ) * x * x * x * y * y * y * y
    + (-393.846 ) * x * x * x * x * y * y * y * y

    + (-28.6567 ) * y * y * y * y * y
    + (-26.5255 ) * x * y * y * y * y * y
    + ( 195.955 ) * x * x * y * y * y * y * y
    + ( 54.7174 ) * x * x * x * y * y * y * y * y

    + (-109.363 ) * y * y * y * y * y * y
    + (-2.62831 ) * x * y * y * y * y * y * y
    + ( 98.4118 ) * x * x * y * y * y * y * y * y

    + (-13.4266 ) * y * y * y * y * y * y * y
    + ( 11.5993 ) * x * y * y * y * y * y * y * y

    + ( 16.0572 ) * y * y * y * y * y * y * y * y;
  if(adj>50)adj=50;
  if(adj<-50)adj=-50;

  //return 205 + ret + cor + adj;
   return 238 + ret + cor + adj;
}

double lconst_func_104_100(double *val, double *pars){
  double x  = -1 * val[0] / 100.0;//rotate
  double y  = -1 * val[1] / 100.0;//rotate

  double ret =
      -0.09445659
    + (-0.02612418) * x
    + ( 3.73611780) * x * x
    + (-3.09953790) * x * x * x
    + (-99.23598500) * x * x * x * x
    + (-75.46225500) * x * x * x * x * x
    + ( 815.77995000) * x * x * x * x * x * x
    + ( 535.25920000) * x * x * x * x * x * x * x
    + (-1847.80315000) * x * x * x * x * x * x * x * x

    + ( 0.21272378) * y
    + ( 1.08951850) * x * y
    + (-5.62523065) * x * x * y
    + ( 0.36676450) * x * x * x * y
    + ( 101.28568240) * x * x * x * x * y
    + ( 50.29375550) * x * x * x * x * x * y
    + (-283.09120000) * x * x * x * x * x * x * y
    + (-461.19640000) * x * x * x * x * x * x * x * y

    + (-2.56180680) * y * y
    + (-2.50161200) * x * y * y
    + ( 15.17487000) * x * x * y * y
    + ( 57.31109000) * x * x * x * y * y
    + ( 22.50744500) * x * x * x * x * y * y
    + (-200.59075000) * x * x * x * x * x * y * y
    + (-698.16850000) * x * x * x * x * x * x * y * y

    + (-4.49848865) * y * y * y
    + (-29.35830900) * x * y * y * y
    + ( 5.33782594) * x * x * y * y * y
    + ( 28.23044550) * x * x * x * y * y * y
    + (-129.13301500) * x * x * x * x * y * y * y
    + ( 664.32420000) * x * x * x * x * x * y * y * y

    + ( 31.62931800) * y * y * y * y
    + (-13.97724400) * x * y * y * y * y
    + (-152.88656000) * x * x * y * y * y * y
    + (-45.82865000) * x * x * x * y * y * y * y
    + ( 769.33340000) * x * x * x * x * y * y * y * y

    + ( 41.36161500) * y * y * y * y * y
    + ( 158.09460500) * x * y * y * y * y * y
    + (-69.54926500) * x * x * y * y * y * y * y
    + (-542.04470000) * x * x * x * y * y * y * y * y

    + (-135.71284000) * y * y * y * y * y * y
    + ( 63.91420500) * x * y * y * y * y * y * y
    + ( 14.03350000) * x * x * y * y * y * y * y * y

    + (-137.97904500) * y * y * y * y * y * y * y
    + (-167.03325000) * x * y * y * y * y * y * y * y

    + ( 307.16340000) * y * y * y * y * y * y * y * y;

  return ret;
}

double lconst_func_104_200(double *val, double *pars){
  (void)pars;

  const double x = -1.0 * val[0] / 100.0;
  const double y = val[1] / 100.0;

  double ret =
    + ( 0.532315   ) * x
    + (-0.102337   ) * x * x
    + (-0.861868   ) * x * x * x
    + ( 0.856681   ) * x * x * x * x
    + (-0.236822   ) * x * x * x * x * x
    + ( 0.135461   ) * x * x * x * x * x * x

    + (-0.434424   ) * y
    + (-1.40652    ) * x * y
    + ( 0.747149   ) * x * x * y
    + ( 0.931457   ) * x * x * x * y
    + (-0.671457   ) * x * x * x * x * y
    + (-0.119259   ) * x * x * x * x * x * y

    + (-0.48569    ) * y * y
    + (-0.555923   ) * x * y * y
    + (-0.39578    ) * x * x * y * y
    + ( 2.07792    ) * x * x * x * y * y
    + (-0.000783101) * x * x * x * x * y * y

    + (-1.01866    ) * y * y * y
    + ( 2.18183    ) * x * y * y * y
    + ( 0.0915502  ) * x * x * y * y * y
    + (-2.06614    ) * x * x * x * y * y * y

    + ( 2.28577    ) * y * y * y * y
    + (-0.598879   ) * x * y * y * y * y
    + (-0.391953   ) * x * x * y * y * y * y

    + ( 1.16486    ) * y * y * y * y * y
    + (-0.283102   ) * x * y * y * y * y * y

    + (-0.760918   ) * y * y * y * y * y * y;

  ret *= 0.7;
  if(ret > 3) ret = 3;
  if(ret < -3) ret = -3;

    double cor =
                0.150286940
    + (-0.648625280) * x
    + (-0.211648650) * x * x
    + ( 4.368550850) * x * x * x
    + (-8.657235500) * x * x * x * x
    + (-4.439690000) * x * x * x * x * x
    + ( 28.938293500) * x * x * x * x * x * x
    + (-3.493945500) * x * x * x * x * x * x * x
    + (-28.272109000) * x * x * x * x * x * x * x * x

    + ( 0.039421500) * y
    + (-0.502021250) * x * y
    + ( 0.733695700) * x * x * y
    + (-0.371716250) * x * x * x * y
    + (-0.595373250) * x * x * x * x * y
    + ( 2.893671700) * x * x * x * x * x * y
    + (-2.498962000) * x * x * x * x * x * x * y
    + ( 0.504311100) * x * x * x * x * x * x * x * y

    + ( 0.637064800) * y * y
    + (-0.020182310) * x * y * y
    + ( 3.156727350) * x * x * y * y
    + (-6.919934950) * x * x * x * y * y
    + (-13.052805000) * x * x * x * x * y * y
    + ( 7.981539000) * x * x * x * x * x * y * y
    + ( 26.556118500) * x * x * x * x * x * x * y * y

    + ( 0.411559750) * y * y * y
    + ( 4.385430130) * x * y * y * y
    + (-3.114838500) * x * x * y * y * y
    + (-1.908476900) * x * x * x * y * y * y
    + ( 4.089755000) * x * x * x * x * y * y * y
    + (-2.090488950) * x * x * x * x * x * y * y * y

    + (-3.268927845) * y * y * y * y
    + ( 3.538502350) * x * y * y * y * y
    + (-6.742967100) * x * x * y * y * y * y
    + ( 1.585137950) * x * x * x * y * y * y * y
    + (-11.797770000) * x * x * x * x * y * y * y * y

    + (-1.629478400) * y * y * y * y * y
    + (-7.999329000) * x * y * y * y * y * y
    + ( 3.153487450) * x * x * y * y * y * y * y
    + ( 2.992617900) * x * x * x * y * y * y * y * y

    + ( 5.957183150) * y * y * y * y * y * y
    + (-4.486720000) * x * y * y * y * y * y * y
    + ( 17.537423000) * x * x * y * y * y * y * y * y

    + ( 2.393309000) * y * y * y * y * y * y * y
    + ( 3.698176000) * x * y * y * y * y * y * y * y

    + (-6.613174550) * y * y * y * y * y * y * y * y;


  return ret + cor;
}

double lconst_func_104_300(double *val, double *pars){
  double x  = -1 * val[0] / 100;
  double y  =      val[1] / 100;

    double ret =
                0.644001020
    + ( 0.029547350) * x
    + ( 0.675001600) * x * x
    + (-3.043262000) * x * x * x
    + ( 1.055040600) * x * x * x * x
    + ( 4.591052000) * x * x * x * x * x
    + (-3.946200500) * x * x * x * x * x * x
    + (-1.487058500) * x * x * x * x * x * x * x
    + ( 1.751933000) * x * x * x * x * x * x * x * x

    + (-0.140758950) * y
    + (-0.643911900) * x * y
    + (-0.268487150) * x * x * y
    + (-0.389973500) * x * x * x * y
    + ( 1.174018620) * x * x * x * x * y
    + ( 0.641566000) * x * x * x * x * x * y
    + (-0.806637400) * x * x * x * x * x * x * y
    + (-0.171836900) * x * x * x * x * x * x * x * y

    + (-0.219168300) * y * y
    + ( 0.249476400) * x * y * y
    + ( 0.404806750) * x * x * y * y
    + (-0.364354410) * x * x * x * y * y
    + ( 2.528116500) * x * x * x * x * y * y
    + (-0.343090500) * x * x * x * x * x * y * y
    + (-1.225104100) * x * x * x * x * x * x * y * y

    + (-0.502080500) * y * y * y
    + ( 1.254017500) * x * y * y * y
    + (-0.695474050) * x * x * y * y * y
    + (-0.153479800) * x * x * x * y * y * y
    + ( 0.227182461) * x * x * x * x * y * y * y
    + ( 0.018960600) * x * x * x * x * x * y * y * y

    + ( 1.376339340) * y * y * y * y
    + (-0.115331100) * x * y * y * y * y
    + (-2.957505000) * x * x * y * y * y * y
    + ( 0.117937105) * x * x * x * y * y * y * y
    + ( 0.328873700) * x * x * x * x * y * y * y * y

    + ( 0.881711000) * y * y * y * y * y
    + (-0.677735000) * x * y * y * y * y * y
    + ( 0.435555800) * x * x * y * y * y * y * y
    + ( 0.182958700) * x * x * x * y * y * y * y * y

    + (-1.802981500) * y * y * y * y * y * y
    + (-0.035390200) * x * y * y * y * y * y * y
    + ( 1.621039100) * x * x * y * y * y * y * y * y

    + (-0.232329200) * y * y * y * y * y * y * y
    + (-0.077314620) * x * y * y * y * y * y * y * y

    + ( 0.405219600) * y * y * y * y * y * y * y * y;

  return ret;
}
  
double t0_func_106_100(double *val, double *pars){
  double x     = -1*val[0];
  double y     = -1*val[1];
  double ret = (29+9.6e-2*y-1.8e-2*y*y)+x*(0.34+1.5e-3*y-8.9e-4*y*y-4.3e-7*y*y*y+4e-7*y*y*y*y)+x*x*(3.9e-2-1.1e-4*y+2.8e-6*y*y);
  //double ret2 = 70/(exp(0.4*(-x+45))+1)/(exp(0.2*(y-15))+1)+150*TMath::Gaus(y,-5,20)/(exp(0.4*(x+43))+1);
  double ret2 =  50*TMath::Gaus(y,5,12)/(exp(0.4*(x+43))+1);
  if(ret>80)  ret =  80;
  if(ret<-80) ret = -80;
  
  //return 185 + 0.6*ret + ret2;
  //return 215 + 0.8*ret ;
  return 202 + 0.6*ret + ret2;
}



double t0_func_106_200(double *val, double *params){
  Double_t x = val[0];
  Double_t y = val[1];

  double ret = (-49+0.22*y+6.2e-3*y*y-3.9e-5*y*y*y-8.4e-7*y*y*y*y)+x*(-0.19-6.6e-4*y+4.2e-5*y*y)+x*x*(-1.4e-2+6.6e-6*y+4.9e-7*y*y);
  if(ret>110)  ret =  110;
  if(ret<-110) ret = -110;
  
  //return 210 - 0.75*ret;
  //return 240 - 0.75*ret;
  return 227 - 0.75*ret;
}


double t0_func_106_300(double *val, double *pars){
  Double_t x = val[0];
  Double_t y = val[1];
  if(x>70) x= 70;
  double ret = (19+0.23*y+4.4e-3*y*y-8.2e-6*y*y*y-3.2e-7*y*y*y*y)+x*(-0.11-7e-4*y+2.8e-5*y*y)+x*x*(-0.021-3.8e-5*y+1.4e-6*y*y);
  if(ret>30)   ret =   30;
  if(ret<-120) ret = -120;
  //return 220 - 0.7*ret - TMath::Gaus(y,15,45)*(90/(exp(0.1*(-x-95))+1)-50);
  // return 250;
   return 237 - 0.7*ret - TMath::Gaus(y,15,45)*(90/(exp(0.1*(-x-95))+1)-50);
}

double lconst_func_106_100(double *val, double *pars){
  double x     = -1*val[0];
  double y     = -1*val[1];
  
  double dl    = (-0.024-2e-3*x+1.2e-4*x*x+7.1e-7*x*x*x)+y*(1.7e-4+4.2e-5*x-1.7e-6*x*x-1.7e-8*x*x*x+8.8e-10*x*x*x*x)+y*y*(1.3e-4+4.8e-7*x-8.7e-8*x*x);
  double dl2   = 0.3*(1-1.4*TMath::Gaus(fabs(y),35,8))*(1/(exp(0.2*(x+40))+1)) + 0.25*(1-1.4*TMath::Gaus(fabs(y),35,8)-1.2*TMath::Gaus(y,2,6))/(exp(0.25*(-x+42.5))+1);

  double dl3   = 0;
  if(fabs(y)<45&&fabs(x)<40) {
    dl3 = 0.08*TMath::Gaus(fabs(y),35,5)+x*x*(-3.5e-5-1.5e-6*y-6.5e-7*y*y+8.7e-10*y*y*y+3.2e-10*y*y*y*y)
      +pow(x,4)*(1.9e-8+9.9e-10*y+3.2e-10*y*y-6e-13*y*y*y-1.6e-13*y*y*y*y);
  }
  
  return dl + 1.25*dl2 + 1.1*dl3;
}




double lconst_func_106_200(double  *val, double *pars){
  Double_t x = val[0];
  Double_t y = val[1];

  double dl    = (6.7e-3-8.5e-4*x+1.7e-5*x*x+3.7e-7*x*x*x)+y*(8.5e-5-9.0e-6*x-1.1e-8*x*x+1.6e-9*x*x*x)+y*y*(-1.3e-5+1.5e-7*x+5.5e-10*x*x-6.4e-11*x*x*x)-0.3*(1/(exp(0.2*(x+90))+1));
  double dl2   = (0.079+3e-4*x+3.8e-5*x*x)+y*(8.1e-5-3.2e-6*x-2e-8*x*x+9.1e-10*x*x*x)+y*y*(8.6e-6+4.3e-8*x-2.7e-9*x*x-1.4e-11*x*x*x);
  return -1*(dl+1.5*dl2);
  //return -1*dl;
}

double lconst_func_106_300(double *val, double *pars){
  Double_t x = val[0];
  Double_t y = val[1];

  double dl  = 0.3*TMath::Gaus(y,-10,30)*TMath::Gaus(x,-y-20,25)+(0.088+8.7e-5*y-7e-6*y*y+6.4e-8*y*y*y+0.22*TMath::Gaus(y,-115,18))
    +x*(7.6e-5+1.3e-6*y+9.1e-8*y*y-2.3e-10*y*y*y-6.2e-12*y*y*y*y)+x*x*(-1.5e-5+3.1e-8*y+2.6e-9*y*y-3.9e-12*y*y*y-1.5e-13*y*y*y*y);
    
  return -1.1*dl;
}

double t0_func_107_100_200_300(double *val, double *pars){
  double xx   = val[0];
  double yy   = val[1];
  return 180;
  
}

double t0_func_107_100(double *val, double *pars){
  double x   = val[0];
  double y   = -1*val[1];
  double dt  =(-98+0.23*y+0.048*y*y)+x*(-2.2+0.011*y+0.00075*y*y-7.5e-6*y*y*y)+x*x*(-0.029-0.00057*y-0.00013*y*y+2.4e-7*y*y*y+4.4e-8*y*y*y*y);
  if(dt> 90) dt =  90;
  if(dt<-90) dt = -90;

  //double dt2  = 33/(exp(0.2*(x+28))+1)+25/(exp(0.2*(-x+35))+1);
  double dt2  = 30/(exp(0.2*(x+30))+1)+30/(exp(0.2*(-x+30))+1);

  double p1 = -7.6+1.5*x+0.017*x*x-0.0019*x*x*x-1.8e-5*x*x*x*x;
  double p2 = 0.087+0.0029*x-3.4e-5*x*x-1.3e-5*x*x*x;
  double p3 = 0.0066-0.00032*x+1.8e-5*x*x+4.9e-7*x*x*x;
  
  double dt3 = p1 + p2*y + p3*y*y;
  if(dt3>100)  dt3 =  100;
  if(dt3<-100) dt3 = -100;
  /*
  double p21 = 12-1.7*x+0.027*x*x+0.0015*x*x*x-2.8e-5*x*x*x*x;
  double p22 = -0.032-0.0013*x-0.00012*x*x;
  double p23 = -0.0055+0.00047*x-1.1e-5*x*x-7.7e-7*x*x*x;
  if(p21<-25) p21 = -25;
  double dt4 = p21 + p22*y + p23*y*y;
  */
  
  //return 150-0.8*dt - dt2 - 0.8*dt3;
  //return 150-0.8*dt ;
  return 167-0.8*dt - dt2 - 0.8*dt3;
}

double t0_func_107_200(double *val, double *pars){
  double x   = -1*val[0];
  double y   =    val[1];
  double dt  = (26+0.81*x+0.0039*x*x)+y*(0.068+0.0014*x-6.2e-5*x*x+4.2e-8*x*x*x+3.5e-9*x*x*x*x)
    +y*y*(-0.0021+5.8e-6*x+2.4e-7*x*x-5.8e-9*x*x*x);
  if(dt> 100) dt =  100;
  if(dt<-100) dt = -100;

  double dt2  = 30/(exp(0.1*(x+70))+1)+30/(exp(0.1*(-x+70))+1);

  double p1 = -7.5-0.16*x-0.012*x*x+3.9e-5*x*x*x+1.7e-6*x*x*x*x;
  if(x<-50) p1 = -25;
  double p2 = 0.031+0.00039*x-1.5e-5*x*x;
  double p3 = -0.0025+1.9e-5*x+1.4e-7*x*x-5.8e-9*x*x*x;
  if(x>70) p3 = -0.0025;
  
  double dt3 = p1 + p2*y + p3*y*y;
  
  //return 170+0.8*dt-dt2 + 0.8*dt3;
   return 187+0.8*dt-dt2 + 0.8*dt3;
}

double t0_func_107_300(double *val, double *pars){
  double x   = -1*val[0];
  double y   =    val[1];

  double dt  =(84+0.12*y-0.0004*y*y-4.8e-6*y*y*y-1.7e-7*y*y*y*y)+x*(0.52+0.00087*y-7.4e-6*y*y)+x*x*(-0.0084-1.5e-5*y+1.6e-7*y*y);
  if(dt> 100) dt =  100;
  if(dt<-100) dt = -100;
  
  //return 160+0.8*dt;
  return 177+0.8*dt;
}

  
double lconst_func_107_100(double *val, double *par){
  double x   = val[0];
  double y   = -1*val[1];
  double dl = (-0.5+0.0047*x+0.00053*x*x-4.6e-6*x*x*x-2.1e-7*x*x*x*x)+y*(0.0008-4.4e-5*x-6.2e-7*x*x)+y*y*(0.00018-3e-6*x-2.1e-7*x*x+2.1e-9*x*x*x+9.7e-11*x*x*x*x);
  //printf("%f %f %f \n",x,y,dl);


  //double dl2 = (-0.029+0.0015*x+0.00014*x*x-1.9e-6*x*x*x-6.6e-8*x*x*x*x)+y*(0.0003-2.5e-5*x-1.4e-7*x*x)+y*y*(2.3e-5-1e-6*x-4.2e-8*x*x+8.3e-10*x*x*x+2.7e-11*x*x*x*x);

  //double dl2  = -0.2*(1/(exp(0.18*(x+25))+1)+1/(exp(0.18*(-x+35))+1))*TMath::Gaus(y,0,20);
  double dl2  = -0.2*(1.7/(exp(0.2*(x+40))+1)+1/(exp(0.18*(-x+35))+1))*TMath::Gaus(y,0,20);

  double dl3  = (-0.0081-0.00098*y-5.3e-5*y*y+7.1e-7*y*y*y+2.3e-8*y*y*y*y)+x*(-0.00013-1.8e-5*y+8.1e-8*y*y+5.6e-9*y*y*y)+x*x*(5.1e-5+9.3e-7*y+2.1e-8*y*y-6e-10*y*y*y-1.7e-11*y*y*y*y);

  double dl4  = -0.2*(0.7/(exp(0.3*(x+45))+1)+0.5/(exp(0.25*(-x+42))+1));
  
  double dl5  = (-0.026+0.0027*x+3.6e-5*x*x-2.2e-6*x*x*x)+y*(0.00024+4.4e-5*x-6.4e-7*x*x-4.5e-8*x*x*x)+y*y*(2.1e-5-1.1e-6*x-8.4e-8*x*x+9.6e-10*x*x*x+3.9e-11*x*x*x*x);
  
  //return -0.7*dl - dl2 - 0.7*dl3;
  return -0.7*dl - dl2 - 0.9*dl3 - dl4 - 0.65*dl5;
  
}

double lconst_func_107_200(double *val, double *par){
  double x    = -1*val[0];
  double y    = val[1];

  //double dl = (-0.36-0.0013*x+6.2e-6*x*x-1e-7*x*x*x+5.8e-9*x*x*x*x)+y*(-0.00056-2.4e-6*x+8.1e-8*x*x)+y*y*(5.8e-5-1.1e-7*x+3.5e-9*x*x+1e-11*x*x*x-1.3e-12*x*x*x*x);

  double dl  =(0.42-0.0011*y-7e-5*y*y+2.3e-7*y*y*y+6.3e-9*y*y*y*y)+x*(0.00038+4.4e-6*y)+x*x*(-2.3e-5+1.1e-7*y+1e-8*y*y-2.7e-11*y*y*y-1.1e-12*y*y*y*y);

  //double dl2  = 0.6*(1/(exp(0.1*(x+50))+1)+1/(exp(0.1*(-x+70))+1))*TMath::Gaus(y,0,40);
  double dl2  = 0.4*(1/(exp(0.1*(x+70))+1)+1.3/(exp(0.1*(-x+70))+1))*TMath::Gaus(y,0,40);
  double dl3  = (-0.041+0.00053*y-1.5e-6*y*y-1e-7*y*y*y+1.5e-9*y*y*y*y)+x*(0.00073+1.1e-5*y-1.1e-7*y*y-1.3e-9*y*y*y)+x*x*(-4.6e-6+5.2e-8*y-2.6e-10*y*y);
  double dl4  =  0.2*(0.7/(exp(0.18*(x+90))+1)+0.5/(exp(0.13*(-x+84))+1));
  double dl5  = (0.076-0.0013*x-6.7e-6*x*x+2.9e-7*x*x*x)+y*(-7.9e-6+1.8e-6*x+6e-8*x*x)+y*y*(-7.8e-6+8.2e-8*x+2.1e-9*x*x-2.8e-11*x*x*x-3.2e-13*x*x*x*x);
  
  return 1.2*dl + dl2 + 0.9*dl3 + dl4 + 1.3*dl5;
  //return 0;
}

double lconst_func_107_300(double *val, double *par){
  double x    = -1*val[0];
  double y    = val[1];
  double dl   = (0.51+1.8e-5*x+2.6e-5*x*x+1.9e-7*x*x*x-1.9e-9*x*x*x*x)+y*(0.0017-2.1e-6*x-2.7e-8*x*x+3.1e-10*x*x*x)+y*y*(-5.4e-5+8.7e-8*x+1e-9*x*x-1.1e-11*x*x*x);
  
  //double dl2  = 0.8*(1/(exp(0.08*(x+85))+1)+1/(exp(0.09*(-x+110))+1))*TMath::Gaus(y,0,70);
  double dl2  = 0.55*(1/(exp(0.08*(x+105))+1)+1.2/(exp(0.09*(-x+110))+1))*TMath::Gaus(y,0,70);

  double dl3  =(-0.042-0.00022*y+1.7e-5*y*y+1.3e-8*y*y*y-9.3e-10*y*y*y*y)+x*(-0.0002-1.6e-6*y+1.7e-7*y*y+3.6e-10*y*y*y-9.9e-12*y*y*y*y)+x*x*(4.9e-6+1.4e-8*y-2.4e-9*y*y-5.2e-14*y*y*y+1.2e-13*y*y*y*y);
  
  double dl4  = 0.2*(0.7/(exp(0.15*(x+135))+1)+0.5/(exp(0.09*(-x+130))+1));

  double dl5  = (0.0085-0.00044*y+2.2e-6*y*y+2.9e-8*y*y*y)+x*(0.00068+2.6e-6*y-1.4e-8*y*y)+x*x*(-1.2e-6+2.2e-8*y-1.2e-9*y*y-7.7e-13*y*y*y+5.9e-14*y*y*y*y);
  
  //return 0.7*dl;
  return 1.6*dl + dl2 + dl3 + dl4 + 1.3*dl5;
}

  

  
double fgeom_func_103_100(double *val, double *par){
  double x     = val[0];
  double y     = -1*val[1];
  double dx    = (0.0005-0.00062*x+1.2e-5*x*x+1.7e-7*x*x*x)+y*(-0.00012+1.3e-5*x+3e-7*x*x-5.4e-9*x*x*x)
    +y*y*(2.7e-6+1.6e-6*x-1.4e-8*x*x-7.7e-10*x*x*x+1.1e-12*x*x*x*x);  

  double dx2   = (-0.012+0.0003*y+1.1e-5*y*y)+x*(-0.00053-4.3e-7*y+1.7e-7*y*y)+x*x*(-8.8e-6 - 3e-7*y);
  
  return dx + 0.85*dx2;
}

double fgeom_func_103_200(double *val, double *par){
  double x     = -1*val[0];
  double y     = val[1];
  double p1 = 0.021   - 0.0001*x*x + 5.3e-8*pow(x,4)  - 5.2e-12*pow(x,6);
  double p3 = -2.1e-6 + 1.5e-8*x*x - 9e-12*pow(x,4)   + 9.3e-16*pow(x,6);
  if(p1<-0.15) p1 = -0.15;
  if(p3>4e-5)  p3 = 4e-5;
  
  double dx     = p1 + y*(-0.00012+2.7e-6*x) + y*y*p3;
  double dx2    = (-0.0063+0.0017*x)+y*(0.00041+4e-6*x+3e-8*x*x)+y*y*(-5e-6-2.4e-7*x-2.1e-10*x*x+5.1e-11*x*x*x);
  double dx3    = (6.1e-3+4.3e-4*y-1.9e-6*y*y)+x*(1.7e-3-1.5e-6*y-5.0e-8*y*y+1.4e-9*y*y*y);
  double dx4    = x*(1.1e-3-3.8e-6*y+7.2e-7*y*y+1.7e-9*y*y*y-9.7e-11*y*y*y*y);
  
  return -1*dx -dx2 - dx3 - 1.3*dx4;
}

double fgeom_func_103_300(double *val, double *par){
  double x     = -1*val[0];
  double y     = val[1];
  return 0;
}

enum {
  pAret=0, pKret=1,
  pR1_0=2, pR1_1=3, pR1_2=4,     // (-37.8 +0.14*y -0.0020*y^2)
  pR2_0=5, pR2_1=6, pR2_2=7,     // (-36   -0.011*y -0.00157*y^2)
              // cor
  pAcor=8,  pKcor=9,
  pC1_0=10, pC1_1=11, pC1_2=12,  // (-42 +0.068*y -0.004*y^2)
  pC2_0=13, pC2_1=14, pC2_2=15,   // (-42 -0.12*y +0.0004*y^2)

  pAadj=16,  pKadj=17,
  pA1_0=18, pA1_1=19, pA1_2=20,  // (-42 +0.068*y -0.004*y^2)
  pA2_0=21, pA2_1=22, pA2_2=23,   // (-42 -0.12*y +0.0004*y^2)
  kFitParams = 24
};


double fgeom_func_104_100(double *val, double *par){
  (void)par;

  double x = -1.0 * val[0];
  double y = -1.0 * val[1];

  const double r1 = pol2(y, -35.0792,   0.0745138,  -0.00348433);
  const double r2 = pol2(y, -29.3026,   0.0918407,  -0.00287127);
  const double c1 = pol2(y, -43.6219,  -0.652202,    0.0056185);
  const double c2 = pol2(y,  -2.45045,  0.349437,    0.0172475);
  const double a1 = pol2(y, -168.364,  -22.2275,   -10.986);
  const double a2 = pol2(y, -38.3529,    0.25344,    0.00272879);

  const double ret =
      -0.148408 / (std::exp( 0.298879  * ( x + r1 )) + 1.0)
      +0.148408 / (std::exp( 0.298879  * (-x + r2 )) + 1.0)

      -(-0.0426818) / (std::exp( -0.100796 * ( x + c1 )) + 1.0)
      +(-0.0426818) / (std::exp( -0.100796 * (-x + c2 )) + 1.0)

      -(-0.19812) / (std::exp( 0.0622834 * ( x + a1 )) + 1.0)
      +(-0.19812) / (std::exp( 0.0622834 * (-x + a2 )) + 1.0);
  x *= 0.01;
  y *= 0.01;
  double cor = 
	        0.0183496
    + ( 0.0329031 ) * x
    + (-0.757413  ) * x * x
    + ( 1.28533   ) * x * x * x
    + ( 4.51473   ) * x * x * x * x
    + ( 0.29563   ) * x * x * x * x * x
    + ( 0.359947  ) * x * x * x * x * x * x
    + ( 0.455686  ) * x * x * x * x * x * x * x
    + ( 0.946227  ) * x * x * x * x * x * x * x * x

    + (-0.0137577 ) * y
    + ( 0.395162  ) * x * y
    + ( 0.393023  ) * x * x * y
    + ( 0.904718  ) * x * x * x * y
    + (-0.658885  ) * x * x * x * x * y
    + (-0.719746  ) * x * x * x * x * x * y
    + (-1.15512   ) * x * x * x * x * x * x * y
    + (-2.00734   ) * x * x * x * x * x * x * x * y

    + ( 0.00363761) * y * y
    + (-0.265926  ) * x * y * y
    + ( 1.24697   ) * x * x * y * y
    + ( 0.665822  ) * x * x * x * y * y
    + ( 0.129849  ) * x * x * x * x * y * y
    + ( 0.76213   ) * x * x * x * x * x * y * y
    + ( 0.778908  ) * x * x * x * x * x * x * y * y

    + (-0.259112  ) * y * y * y
    + (-3.15876   ) * x * y * y * y
    + ( 0.155104  ) * x * x * y * y * y
    + (-0.00645987) * x * x * x * y * y * y
    + ( 0.00245138) * x * x * x * x * y * y * y
    + (-0.812865  ) * x * x * x * x * x * y * y * y

    + (-0.0785379 ) * y * y * y * y
    + ( 0.193579  ) * x * y * y * y * y
    + ( 0.212447  ) * x * x * y * y * y * y
    + ( 0.798664  ) * x * x * x * y * y * y * y
    + ( 0.636614  ) * x * x * x * x * y * y * y * y

    + ( 0.26379   ) * y * y * y * y * y
    + ( 0.406444  ) * x * y * y * y * y * y
    + ( 0.629065  ) * x * x * y * y * y * y * y
    + ( 0.731755  ) * x * x * x * y * y * y * y * y

    + ( 0.0452633 ) * y * y * y * y * y * y
    + ( 0.341342  ) * x * y * y * y * y * y * y
    + ( 0.689892  ) * x * x * y * y * y * y * y * y

    + ( 0.272168  ) * y * y * y * y * y * y * y
    + ( 1.0157    ) * x * y * y * y * y * y * y * y

    + ( 0.131301  ) * y * y * y * y * y * y * y * y;

  return -1*(ret + cor);
}

double fgeom_func_104_200(double *val, double *par){
  (void)par;

  double x = val[0];
  double y = val[1];

  const double r1 = pol2(y, -605.734,  -7.99062,    -0.0344249);
  const double r2 = pol2(y,   24.4541, -0.101427,    0.00287194);
  const double c1 = pol2(y,  -87.979,   0.00712266, -0.000779164);
  const double c2 = pol2(y,  -93.5324, -0.0224839,  -0.000872752);
  const double a1 = pol2(y, -139.616,  -0.126433,    0.000475876);
  const double a2 = pol2(y,   37.8754, -0.194184,    0.00406813);

  double ret =
      -3.75302 / (std::exp(0.0313836 * ( x + r1 )) + 1.0)
      +3.75302 / (std::exp(0.0313836 * (-x + r2 )) + 1.0)

      -0.89707 / (std::exp(0.463375 * ( x + c1 )) + 1.0)
      +0.89707 / (std::exp(0.463375 * (-x + c2 )) + 1.0)

      -3.84465 / (std::exp(-0.0229804 * ( x + a1 )) + 1.0)
      +3.84465 / (std::exp(-0.0229804 * (-x + a2 )) + 1.0);
  ret *= 0.4;

  x *= -0.01;
  y *= 0.01;
    double cor =
                 0.0391052100
    + ( 0.1440952000) * x
    + (-0.2991353000) * x * x
    + (-0.4189355000) * x * x * x
    + ( 0.9989265000) * x * x * x * x
    + (-0.1183644350) * x * x * x * x * x
    + ( 0.0154025200) * x * x * x * x * x * x
    + (-0.0353857490) * x * x * x * x * x * x * x
    + ( 0.0110431958) * x * x * x * x * x * x * x * x

    + ( 0.0456246850) * y
    + (-0.1501056000) * x * y
    + ( 0.0294776400) * x * x * y
    + (-0.0638608800) * x * x * x * y
    + (-0.0766931400) * x * x * x * x * y
    + ( 0.0144272667) * x * x * x * x * x * y
    + (-0.0246381819) * x * x * x * x * x * x * y
    + ( 0.0077189358) * x * x * x * x * x * x * x * y

    + (-0.1358218200) * y * y
    + ( 0.3209875700) * x * y * y
    + (-0.4221036600) * x * x * y * y
    + ( 0.2398223100) * x * x * x * y * y
    + (-0.0272354030) * x * x * x * x * y * y
    + ( 0.0261148400) * x * x * x * x * x * y * y
    + (-0.0032947541) * x * x * x * x * x * x * y * y

    + (-0.1025078300) * y * y * y
    + ( 0.1826118600) * x * y * y * y
    + (-0.0007628500) * x * x * y * y * y
    + (-0.0086263600) * x * x * x * y * y * y
    + (-0.0180948410) * x * x * x * x * y * y * y
    + (-0.0072422470) * x * x * x * x * x * y * y * y

    + ( 0.1697055000) * y * y * y * y
    + (-0.0946648100) * x * y * y * y * y
    + ( 0.0391559160) * x * x * y * y * y * y
    + ( 0.0211168550) * x * x * x * y * y * y * y
    + (-0.0006106680) * x * x * x * x * y * y * y * y

    + ( 0.0194356630) * y * y * y * y * y
    + (-0.0124796700) * x * y * y * y * y * y
    + (-0.0016698095) * x * x * y * y * y * y * y
    + (-0.0111877900) * x * x * x * y * y * y * y * y

    + ( 0.0016853638) * y * y * y * y * y * y
    + (-0.0219130580) * x * y * y * y * y * y * y
    + ( 0.0190453260) * x * x * y * y * y * y * y * y

    + ( 0.0046997222) * y * y * y * y * y * y * y
    + (-0.0069276571) * x * y * y * y * y * y * y * y

    + ( 0.0005866089) * y * y * y * y * y * y * y * y;

  double adj =
                 0.0160647000
    + ( 0.0124551000) * x
    + (-0.1664290000) * x * x
    + (-0.0494863000) * x * x * x
    + ( 0.2750140000) * x * x * x * x
    + (-0.0474675000) * x * x * x * x * x
    + (-0.0009702070) * x * x * x * x * x * x
    + (-0.0061384700) * x * x * x * x * x * x * x
    + (-0.0015328700) * x * x * x * x * x * x * x * x

    + ( 0.0000987393) * y
    + (-0.0305843000) * x * y
    + (-0.0012404000) * x * x * y
    + (-0.0261178000) * x * x * x * y
    + (-0.0315900000) * x * x * x * x * y
    + ( 0.0062255600) * x * x * x * x * x * y
    + (-0.0072415800) * x * x * x * x * x * x * y
    + ( 0.0027064300) * x * x * x * x * x * x * x * y

    + (-0.0342752000) * y * y
    + ( 0.0702823000) * x * y * y
    + (-0.0098104500) * x * x * y * y
    + ( 0.0943280000) * x * x * x * y * y
    + (-0.0061030400) * x * x * x * x * y * y
    + ( 0.0045523200) * x * x * x * x * x * y * y
    + (-0.0007502050) * x * x * x * x * x * x * y * y

    + (-0.0049405200) * y * y * y
    + ( 0.0350057000) * x * y * y * y
    + (-0.0224254000) * x * x * y * y * y
    + (-0.0096085200) * x * x * x * y * y * y
    + (-0.0080939000) * x * x * x * x * y * y * y
    + (-0.0030655800) * x * x * x * x * x * y * y * y

    + ( 0.0414122000) * y * y * y * y
    + (-0.0383751000) * x * y * y * y * y
    + ( 0.0141774000) * x * x * y * y * y * y
    + ( 0.0045174300) * x * x * x * y * y * y * y
    + ( 0.0011156300) * x * x * x * x * y * y * y * y

    + ( 0.0036148100) * y * y * y * y * y
    + (-0.0024935900) * x * y * y * y * y * y
    + (-0.0024057900) * x * x * y * y * y * y * y
    + (-0.0042099200) * x * x * x * y * y * y * y * y

    + (-0.0008036930) * y * y * y * y * y * y
    + (-0.0060506100) * x * y * y * y * y * y * y
    + ( 0.0044454700) * x * x * y * y * y * y * y * y

    + ( 0.0006544210) * y * y * y * y * y * y * y
    + (-0.0010055600) * x * y * y * y * y * y * y * y

    + (-0.0004010710) * y * y * y * y * y * y * y * y;

  if(adj < 0) adj = 0;

  ret = ret - cor - adj;

  if(ret >  0.8) ret =  0.8;
  if(ret < -0.8) ret = -0.8;

  return ret;
}
double fgeom_func_104_300(double *val, double *par){
  (void)par;

  double x = val[0];
  double y = val[1];

  const double r1 = pol2(y, -748.272,  -3.28836,   -0.0603974);
  const double r2 = pol2(y,    0.992615, 0.135836,   0.00272455);
  const double c1 = pol2(y,  157.273,  -0.0861787, -0.00175463);
  const double c2 = pol2(y, -162.007,  -0.345751,  -0.00571543);
  const double a1 = pol2(y, -109.314,  -0.168394,   0.00574952);
  const double a2 = pol2(y,  -70.1685,  0.0825645,  0.0125166);

  const double ret =
      -2.08536 / (std::exp(0.0144872 * ( x + r1 )) + 1.0)
      +2.08536 / (std::exp(0.0144872 * (-x + r2 )) + 1.0)

      -0.958562 / (std::exp(0.0667726 * ( x + c1 )) + 1.0)
      +0.958562 / (std::exp(0.0667726 * (-x + c2 )) + 1.0)

      -1.62786 / (std::exp(-0.00689364 * ( x + a1 )) + 1.0)
      +1.62786 / (std::exp(-0.00689364 * (-x + a2 )) + 1.0);

  x *= -0.01;
  y *= 0.01;
  double cor = 
	        -0.0147806
    + (-0.145032   ) * x
    + ( 0.562605   ) * x * x
    + ( 0.0240177  ) * x * x * x
    + (-0.60788    ) * x * x * x * x
    + ( 0.0399832  ) * x * x * x * x * x
    + (-0.000458616) * x * x * x * x * x * x
    + ( 0.00530027 ) * x * x * x * x * x * x * x
    + ( 0.000298625) * x * x * x * x * x * x * x * x

    + (-0.0118364  ) * y
    + (-0.0799444  ) * x * y
    + (-0.0396674  ) * x * x * y
    + (-0.106001   ) * x * x * x * y
    + ( 0.0144717  ) * x * x * x * x * y
    + (-0.00510821 ) * x * x * x * x * x * y
    + ( 0.00204139 ) * x * x * x * x * x * x * y
    + (-0.00161385 ) * x * x * x * x * x * x * x * y

    + (-0.0140859  ) * y * y
    + ( 0.0259769  ) * x * y * y
    + ( 0.162029   ) * x * x * y * y
    + (-0.0371115  ) * x * x * x * y * y
    + ( 0.00655686 ) * x * x * x * x * y * y
    + ( 0.000473094) * x * x * x * x * x * y * y
    + ( 0.00159391 ) * x * x * x * x * x * x * y * y

    + ( 0.017436   ) * y * y * y
    + ( 0.120109   ) * x * y * y * y
    + (-0.00478461 ) * x * x * y * y * y
    + (-0.000728098) * x * x * x * y * y * y
    + ( 0.00129666 ) * x * x * x * x * y * y * y
    + (-0.00182791 ) * x * x * x * x * x * y * y * y

    + (-0.0175008  ) * y * y * y * y
    + ( 0.00954216 ) * x * y * y * y * y
    + (-0.00278716 ) * x * x * y * y * y * y
    + (-0.00296289 ) * x * x * x * y * y * y * y
    + ( 0.00163066 ) * x * x * x * x * y * y * y * y

    + (-0.00287483 ) * y * y * y * y * y
    + ( 0.00349812 ) * x * y * y * y * y * y
    + (-0.00180186 ) * x * x * y * y * y * y * y
    + ( 0.000832493) * x * x * x * y * y * y * y * y

    + (-0.000667345) * y * y * y * y * y * y
    + ( 0.00168931 ) * x * y * y * y * y * y * y
    + (-0.00126533 ) * x * x * y * y * y * y * y * y

    + (-0.000336842) * y * y * y * y * y * y * y
    + ( 0.00104497 ) * x * y * y * y * y * y * y * y

    + (-0.000217144) * y * y * y * y * y * y * y * y;
  cor *= -1;

  return ret + cor;
}


double fgeom_func_106_100(double *val, double *par){
  double x   = -1*val[0];
  double y   = -1*val[1];

  double ret = (-0.34+1e-3*y+8.7e-5*y*y)*(1/(exp(0.18*(x-40))+1)-1/(exp(0.18*(-x-40))+1))-0.05-0.2/(exp(0.3*(x+43))+1)*TMath::Gaus(y,10,15);
  
  return -1.1*ret;
}

  
double fgeom_func_106_200(double *val, double *par){
  double x   = val[0];
  double y   = val[1];

  double ret = (-0.06-0.3e-3*x+4.5e-6*x*x+3.5e-7*x*x*x)+y*(1.9e-5-5.8e-7*x+5.7e-8*x*x)+y*y*(1.1e-6+5.1e-7*x-2e-9*x*x-7.2e-11*x*x*x)+(-0.03+0.0008*x-1e-5*x*x)/(exp(0.35*(-fabs(y)+85))+1);

  double ret2 = (-9.1e-3-9.8e-4*x-2.6e-6*x*x-1.4e-7*x*x*x-0.3/(exp(0.2*(x+90))+1)+0.72/(exp(0.25*(-x+90))+1))
    + y*(-2.3e-5-2.4e-6*x+4.6e-8*x*x) + y*y*(2.4e-6+3.1e-7*x-3.6e-10*x*x+4e-5/(exp(0.25*(x+90))+1)-7e-5/(exp(0.25*(-x+90))+1));

  
  return ret + 1.4*ret2;
}

double fgeom_func_106_300(double *val, double *par){
  double x   = val[0];
  double y   = val[1];
  double ret = (-0.011+6.2e-5*y+7.7e-6*y*y+1.3e-9*y*y*y-5.6e-10*y*y*y*y)+x*(1.1e-3+1.4e-6*y-5.2e-8*y*y)+x*x*(8.6e-6-7.5e-9*y-1.6e-9*y*y-8.1e-13*y*y*y+8.8e-14*y*y*y*y);
  
  return ret;

}

double fgeom_func_107_100(double *val, double *par){
  double x     = val[0];
  double y     = -1*val[1];
  double dx    = (-0.007-0.00013*y-4.7e-6*y*y)+x*(0.0013-2.3e-6*y-2.8e-6*y*y)+x*x*(2.4e-5-2.4e-8*y+6.5e-9*y*y)+x*x*x*(-8.4e-8-2.9e-9*y+1.4e-9*y*y);
  double dx2   = (-0.57-0.0071*y+0.00014*y*y+2.6e-6*y*y*y)/(exp(0.25*(-x+43))+1);
  return dx + 0.9*dx2;
  
  
}

double fgeom_func_107_200(double *val, double *par){
  double x     = -1*val[0];
  double y     = val[1];
  double dx    = (-0.037-0.0002*y+1.1e-6*y*y)+x*(0.00076+2.5e-6*y-3.6e-7*y*y)+x*x*(4.6e-6+4.9e-8*y-1.5e-10*y*y)+x*x*x*(-9.6e-8-6.6e-10*y+4.9e-11*y*y);
  //double dx2   = (0.065-0.00046*y+9.6e-6*y*y+1e-7*y*y*y)+x*(0.00092-1.2e-6*y-4.9e-7*y*y+1e-10*y*y*y+4e-11*y*y*y*y)+x*x*(-4e-6-1.2e-8*y-1.5e-9*y*y);
  double dx2   = -0.45/(exp(0.1*(-x+90))+1);
  return -1*(dx+dx2);
  
}

double fgeom_func_107_300(double *val, double *par){
  double x     = -1*val[0];
  double y     = val[1];
  double dx    = (-0.0049-0.00014*y)+x*(-1.1e-5+1.5e-8*y-1.3e-8*y*y)+x*x*(7.8e-7-6.4e-8*y+1.8e-10*y*y+8.4e-12*y*y*y)-1.1e-8*x*x*x;
  double dx2   = (-0.046-0.0051*x-9.6e-7*x*x+3.1e-7*x*x*x)+y*(-0.00065+2.5e-6*x)+y*y*(-8.9e-7+2.2e-7*x+3.2e-10*x*x-8.4e-12*x*x*x);
  
  double dx3   = (-0.048-0.0021*x+3.2e-6*x*x+8.1e-8*x*x*x)+y*(-0.00021+2.2e-6*x-1.4e-8*x*x)+y*y*(2.5e-6+5.4e-8*x-7.7e-11*x*x);
  return -1*(dx+dx2+dx3);  
}


  
  
//double lconst_func_107_300(double *val, double *par){
//  double lc    = par[0];
//  
//  return lc;
//}

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
   double default_fgeom[3] = {0,0,0};
   for (int module_id=1; module_id<10; module_id++) {
      for (int layer_id=0; layer_id<3; layer_id++) {
         fLorentzCorrections[module_id][layer_id].SetMagFieldSign(sign);
         fLorentzCorrections[module_id][layer_id].SetT0Func(const_func, {default_t0[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetVDriftZFunc(const_func, {default_vd_z[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetVDriftXFunc(const_func, {default_vd_x[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetLorentzConstFunc(const_func, {default_lconst[layer_id]});
	 fLorentzCorrections[module_id][layer_id].SetFGeom(const_func, {default_fgeom[layer_id]});
      }
   }
   for (int module_id=101; module_id<110; module_id++) {
      for (int layer_id=0; layer_id<3; layer_id++) {
         fLorentzCorrections[module_id][layer_id].SetMagFieldSign(sign);
         fLorentzCorrections[module_id][layer_id].SetT0Func(const_func, {default_t0[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetVDriftZFunc(const_func, {default_vd_z[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetVDriftXFunc(const_func, {default_vd_x[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetLorentzConstFunc(const_func, {default_lconst[layer_id]});
	 fLorentzCorrections[module_id][layer_id].SetFGeom(const_func, {default_fgeom[layer_id]});
      }
   }
   for (int module_id=201; module_id<210; module_id++) {
      for (int layer_id=0; layer_id<3; layer_id++) {
         fLorentzCorrections[module_id][layer_id].SetMagFieldSign(sign);
         fLorentzCorrections[module_id][layer_id].SetT0Func(const_func, {default_t0[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetVDriftZFunc(const_func, {default_vd_z[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetVDriftXFunc(const_func, {default_vd_x[layer_id]});
         fLorentzCorrections[module_id][layer_id].SetLorentzConstFunc(const_func, {default_lconst[layer_id]});
	 fLorentzCorrections[module_id][layer_id].SetFGeom(const_func, {default_fgeom[layer_id]});
      }
   }

   // Set functions and parameters here.
   // fLorentzCorrections[module_id][layer_id]
   // and Set T0, VDriftZ, VDriftX, LorentzConst functions.

   // LorentzConstant rough values
   fLorentzCorrections[103][0].SetLorentzConstRoughFunc(const_func, {+3.45});
   fLorentzCorrections[103][1].SetLorentzConstRoughFunc(const_func, {-2.2});
   fLorentzCorrections[103][2].SetLorentzConstRoughFunc(const_func, {-1.2});

   fLorentzCorrections[104][0].SetLorentzConstRoughFunc(const_func, {+3.733});//20260329_1
   fLorentzCorrections[104][1].SetLorentzConstRoughFunc(const_func, {-3.097});
   fLorentzCorrections[104][2].SetLorentzConstRoughFunc(const_func, {-2.060});
   fLorentzCorrections[106][0].SetLorentzConstRoughFunc(const_func, {+4.209});
   fLorentzCorrections[106][1].SetLorentzConstRoughFunc(const_func, {-3.264});
   fLorentzCorrections[106][2].SetLorentzConstRoughFunc(const_func, {-2.112});
   //v1
   /*
   fLorentzCorrections[107][0].SetLorentzConstRoughFunc(const_func, {+3.361});
   fLorentzCorrections[107][1].SetLorentzConstRoughFunc(const_func, {-2.404});
   fLorentzCorrections[107][2].SetLorentzConstRoughFunc(const_func, {-1.705});
   */
   fLorentzCorrections[107][0].SetLorentzConstRoughFunc(const_func, {+3.361});
   fLorentzCorrections[107][1].SetLorentzConstRoughFunc(const_func, {-3.00});
   fLorentzCorrections[107][2].SetLorentzConstRoughFunc(const_func, {-1.055});
   //GTR-Module103
   fLorentzCorrections[103][0].SetT0Func(t0_func_103_100, {});
   fLorentzCorrections[103][1].SetT0Func(t0_func_103_200, {});
   fLorentzCorrections[103][2].SetT0Func(t0_func_103_300, {});
   /*
   fLorentzCorrections[103][2].SetT0Func(t0_func_103_100_200_300, {
       210,
       //117.737,
         167.237,
         -0.105471,
         8.01617,
         -11.0619,
         158.059,
         99.538
         });
   */
   //fLorentzCorrections[103][0].SetVDriftZFunc(const_func, {0.0078});
   fLorentzCorrections[103][0].SetVDriftZFunc(const_func, {0.015});
   fLorentzCorrections[103][1].SetVDriftZFunc(const_func, {0.015});
   fLorentzCorrections[103][2].SetVDriftZFunc(const_func, {0.018});

   fLorentzCorrections[103][0].SetLorentzConstFunc(lconst_func_103_100,{});
   fLorentzCorrections[103][1].SetLorentzConstFunc(lconst_func_103_200,{});
   fLorentzCorrections[103][2].SetLorentzConstFunc(lconst_func_103_300,{});

   fLorentzCorrections[103][0].SetVDriftXFunc(const_func, {0.0089});
   fLorentzCorrections[103][1].SetVDriftXFunc(const_func, {-0.0052});
   fLorentzCorrections[103][2].SetVDriftXFunc(const_func, {-0.0035});
   fLorentzCorrections[103][0].SetFGeom(fgeom_func_103_100, {0});
   fLorentzCorrections[103][1].SetFGeom(fgeom_func_103_200, {0});
   fLorentzCorrections[103][2].SetFGeom(fgeom_func_103_300, {0});   
   
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
   fLorentzCorrections[104][2].SetT0Func(t0_func_104_300, {0});   

   fLorentzCorrections[104][0].SetFGeom(fgeom_func_104_100, {0});
   fLorentzCorrections[104][1].SetFGeom(fgeom_func_104_200, {0});
   fLorentzCorrections[104][2].SetFGeom(fgeom_func_104_300, {0});   
   
   fLorentzCorrections[104][0].SetVDriftZFunc(const_func, {0.01725});
   //fLorentzCorrections[104][1].SetVDriftZFunc(const_func, {0.015});
   fLorentzCorrections[104][1].SetVDriftZFunc(const_func, {0.0165});
   //fLorentzCorrections[104][2].SetVDriftZFunc(const_func, {0.020});
   fLorentzCorrections[104][2].SetVDriftZFunc(const_func, {0.016});
   
   //fLorentzCorrections[104][0].SetVDriftXFunc(const_func, {0.0062}); //vdrift * tan(25deg)
   fLorentzCorrections[104][0].SetVDriftXFunc(const_func, {0.0076}); 
   //fLorentzCorrections[104][1].SetVDriftXFunc(const_func, {-0.0057});//vdrift * tan(18deg)
   fLorentzCorrections[104][1].SetVDriftXFunc(const_func, {-0.00627});//vdrift * tan(18deg)
   //fLorentzCorrections[104][2].SetVDriftXFunc(const_func, {-0.006});//vdrfit  * tan(13+?)deg
   fLorentzCorrections[104][2].SetVDriftXFunc(const_func, {-0.0042});//vdrfit  * tan(13+?)deg
   
   //Lorentz function
   fLorentzCorrections[104][0].SetLorentzConstFunc(lconst_func_104_100);
   fLorentzCorrections[104][1].SetLorentzConstFunc(lconst_func_104_200);
   fLorentzCorrections[104][2].SetLorentzConstFunc(lconst_func_104_300);

   //GTR-Module106
   
   fLorentzCorrections[106][0].SetT0Func(t0_func_106_100, {
       200, 300, -40, -130, 35, -55, 25,70, 10, 0.50
     });
   fLorentzCorrections[106][1].SetT0Func(t0_func_106_200, {
       0.2, 220, 290, -85, -40, 50, 70
     });
   fLorentzCorrections[106][2].SetT0Func(t0_func_106_300, {
       300
     });
   
   
   //VdriftZ
   fLorentzCorrections[106][0].SetVDriftZFunc(const_func, {0.0135});
   fLorentzCorrections[106][1].SetVDriftZFunc(const_func, {0.018});
   fLorentzCorrections[106][2].SetVDriftZFunc(const_func, {0.020});
   //VdriftX
   fLorentzCorrections[106][0].SetVDriftXFunc(const_func, {0.0065});
   fLorentzCorrections[106][1].SetVDriftXFunc(const_func, {-0.008});
   fLorentzCorrections[106][2].SetVDriftXFunc(const_func, {-0.0035});
   //Lorentz function
   fLorentzCorrections[106][0].SetLorentzConstFunc(lconst_func_106_100);
   fLorentzCorrections[106][1].SetLorentzConstFunc(lconst_func_106_200);
   fLorentzCorrections[106][2].SetLorentzConstFunc(lconst_func_106_300);

   fLorentzCorrections[106][0].SetFGeom(fgeom_func_106_100, {0});
   fLorentzCorrections[106][1].SetFGeom(fgeom_func_106_200, {0});
   fLorentzCorrections[106][2].SetFGeom(fgeom_func_106_300, {0});
   
   fLorentzCorrections[106][0].SetLorentzConstFunc(lconst_func_106_100,{
       0.33,-45,-0.41,-42
     });

   fLorentzCorrections[106][1].SetLorentzConstFunc(lconst_func_106_200,{
       0.026,-0.00106,1.51e-5,3.51e-7,
       -0.00123,-3.54e-5,6.28e-7,6.23e-9,-1.36e-10
     });
   fLorentzCorrections[106][2].SetLorentzConstFunc(lconst_func_106_300,{
       0.4,0.15,-50,
       -1,
       0.6,0.12,-30
     });
   
   //GTR-Module107

   fLorentzCorrections[107][0].SetT0Func(t0_func_107_100, {});
   fLorentzCorrections[107][1].SetT0Func(t0_func_107_200, {});
   fLorentzCorrections[107][2].SetT0Func(t0_func_107_300, {});

   fLorentzCorrections[107][0].SetVDriftZFunc(const_func, {0.014});
   fLorentzCorrections[107][1].SetVDriftZFunc(const_func, {0.014});
   fLorentzCorrections[107][2].SetVDriftZFunc(const_func, {0.018});
   
   fLorentzCorrections[107][0].SetLorentzConstFunc(lconst_func_107_100,{});
   fLorentzCorrections[107][1].SetLorentzConstFunc(lconst_func_107_200,{});
   fLorentzCorrections[107][2].SetLorentzConstFunc(lconst_func_107_300,{});

   fLorentzCorrections[107][0].SetFGeom(fgeom_func_107_100, {0});
   fLorentzCorrections[107][1].SetFGeom(fgeom_func_107_200, {0});
   fLorentzCorrections[107][2].SetFGeom(fgeom_func_107_300, {0});

   fLorentzCorrections[107][0].SetVDriftXFunc(const_func, {0.0076});
   fLorentzCorrections[107][1].SetVDriftXFunc(const_func, {-0.0066});
   fLorentzCorrections[107][2].SetVDriftXFunc(const_func, {-0.0035});
}

E16ANA_GTRLorentzCorrectionManager* E16ANA_GTRLorentzCorrectionManager::fInstance = nullptr;

E16ANA_GTRLorentzCorrectionManager& E16ANA_GTRLorentzCorrectionManager::Instance(){
   if (fInstance == nullptr) {
      fInstance = new E16ANA_GTRLorentzCorrectionManager();
   }
   return *fInstance;
}

TVector3 E16ANA_GTRLorentzCorrectionManager::CorrectLocalPos(int module_id, int layer_id, const TVector3 &lpos, double hit_time, const TVector3 &lmom,double corr[]){
  return fLorentzCorrections[module_id][layer_id].CorrectLocalPos(lpos, hit_time, lmom,corr);
}

void E16ANA_GTRLorentzCorrectionManager::PrintParams(int module_id, int layer_id, const TVector3 &lpos){
   return fLorentzCorrections[module_id][layer_id].PrintParams(lpos);
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

void E16ANA_GTRLorentzCorrection::SetFGeom(std::function<double(double*, double*)> func, std::initializer_list<double> params){
   std::vector<double> p;
   for (auto &e : params) {
      p.push_back(e);
   }
   SetFGeom(func, p);
}

void E16ANA_GTRLorentzCorrection::SetFGeom(std::function<double(double*, double*)> func, std::vector<double> &params){
   fFGeom.fFunc = func;
   fFGeom.fParams = params;
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

void E16ANA_GTRLorentzCorrection::SetLorentzConstRoughFunc(std::function<double(double*, double*)> func, std::initializer_list<double> params){
   std::vector<double> p;
   for (auto &e : params) {
      p.push_back(e);
   }
   SetLorentzConstRoughFunc(func, p);
}
void E16ANA_GTRLorentzCorrection::SetLorentzConstRoughFunc(std::function<double(double*, double*)> func, std::vector<double> &params){
   fLorentzConstRoughFunc.fFunc = func;
   fLorentzConstRoughFunc.fParams = params;
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

