#include "E16ANA_GTRLorentzCorrection.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_FieldMapCalib.hh"

#include <TMath.h>

TVector3 E16ANA_GTRLorentzCorrection::CorrectLocalPos(const TVector3 &lpos, double hit_time, const TVector3 &lmom){
   double tan_theta_x = lmom.X()/lmom.Z();
   //double tan_theta_y = lmom.Y()/lmom.Z();
   double lx = lpos.X();
   double ly = lpos.Y();
   double lconst_rough = fLorentzConstRoughFunc(lx, ly);
   double t0 = fT0Func(lx+lconst_rough, ly);
   double vd_z = fVDriftZFunc(lx+lconst_rough, ly);
   double vd_x = fVDriftXFunc(lx+lconst_rough, ly);
   double lconst = fLorentzConstFunc(lx+lconst_rough, ly);
   double corrected_lx = lx + (t0-hit_time)*vd_z*tan_theta_x + lconst_rough + lconst - (t0-hit_time)*vd_x;
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
  double xx   = val[0];
  double yy   = -1*val[1];
  
  double p0   = par[0];
  double p1   = par[1];
  double p2   = par[2];
  double p3   = par[3];
  double p4   = par[4];
  double s0   = par[5];
  double s1   = par[6];
  double g1   = par[7];
  double g2   = par[8];
  //double lc   = par[9];

  double pol  = p0+p1*yy+p2*yy*yy+p3*yy*yy*yy+p4*yy*yy*yy*yy;
  double st   = s0/(exp(0.4*(abs(yy)+s1))+1);
  double gg   = 0.43*exp(-0.5*(yy-g1)/g2*(yy-g1)/g2);

  double argx  = (xx)/30;
  double argx2 = (xx+3)/10;
  double argx3 = (xx+50)/10;

  //return -1*(-0.2*exp(-0.5*argx*argx) + pol -st*exp(-0.5*argx2*argx2) + gg*exp(-0.5*argx3*argx3)) + lc;
  return -1*(-0.2*exp(-0.5*argx*argx) + pol -st*exp(-0.5*argx2*argx2) + gg*exp(-0.5*argx3*argx3));
}

double lconst_func_103_200(double *val, double *par){
  double xx    = -1*val[0];
  double yy    = val[1];
  
  double p0   = par[0];
  double p1   = par[1];
  double p2   = par[2];
  double p3   = par[3];
  double p4   = par[4];
  double s0   = par[5];
  double s1   = par[6];
  double g1   = par[7];
  double g2   = par[8];
  //double lc   = par[9];

  double pol  = p0+p1*yy+p2*yy*yy+p3*yy*yy*yy+p4*yy*yy*yy*yy;
  double st   = s0/(exp(0.0636*(abs(yy-15)+s1))+1)-0.1;
  double gg   = 0.25*exp(-0.5*(yy-g1)/g2*(yy-g1)/g2)+0.15;

  double argx  = (xx-10)/40;
  double argx2 = (xx-100)/15;
  
  //return  -1*pol*exp(-0.5*argx*argx) + st + gg*exp(-0.5*argx2*argx2) + lc;
  return  -1*pol*exp(-0.5*argx*argx) + st + gg*exp(-0.5*argx2*argx2);
}

double lconst_func_103_300(double *val, double *par){
  double xx    = -1*val[0];
  double yy    = val[1];
  
  double p0     = par[0];
  double p1     = par[1];
  double p2     = par[2];
  double p3     = par[3];
  double p4     = par[4];
  
  double pp0    = par[5];
  double pp1    = par[6];
  double pp2    = par[7];
  double pp3    = par[8];
  
  double ppp0   = par[9];
  double ppp1   = par[10];
  double ppp2   = par[11];
  double ppp3   = par[12];
  double ppp4   = par[13];
  
  
  //double lc   = par[14];

  double pol   = p0+p1*yy+p2*yy*yy+p3*yy*yy*yy+p4*yy*yy*yy*yy;
  double pol2  = pp0+pp1*yy+pp2*yy*yy+pp3*yy*yy*yy+0.8*exp(-0.5*(yy-105)/15*(yy-105)/15);
  double pol3  = ppp0+ppp1*yy+ppp2*yy*yy+ppp3*yy*yy*yy+ppp4*yy*yy*yy*yy;
  double st   = -0.3/(exp(0.08*(abs(yy-25)-80))+1);

  double argx  = (xx-pol3)/45;
  double argx2 = (xx+95)/25;
  
  //return  pol2*exp(-0.5*argx*argx) + pol + st*gg*exp(-0.5*argx2*argx2) + lc;
  return  pol2*exp(-0.5*argx*argx) + pol + st*exp(-0.5*argx2*argx2);
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
  //double lconst = 3.173;
  double x  = -1 * val[0];//rotate
  double y  = -1 * val[1];//rotate
  double ys = y*0.01;
  double p0 = 0.48 +0.0225*ys -3.54*ys*ys -2.*ys*ys*ys +20.*ys*ys*ys*ys;
  double p1 = 0.56 -0.235*y;
  double p2 = 19.;
  double p3 = 0.036;
  double p4 =-0.00020 -0.000027*y;
  double func = p0 * exp( -0.5*((x-p1)/p2)*((x-p1)/p2) ) + p3 + p4*x;
  //return -func + lconst;
  return -func;
}

double lconst_func_104_200(double *val, double *pars){
  //double lconst = -3.007;
  double x  = val[0];
  double y  = val[1];
  double p0 =  3.7;
  double p1 =  0.05;
  double p2 = -124.;
  double p3 = -3.8;
  double p4 = 0.00114 -0.000017*x;
  double func = p0/(exp( p1*(fabs(y)+p2) )+1) + p3 + p4*y;
  //return func + lconst;
  return func;
}

double lconst_func_104_300(double *val, double *pars){
  //double lconst = -1.080;
  double x  = val[0];
  double y  = val[1];
  double ys = y*0.01;
  double p0 = -0.036 +0.19*ys -0.25*ys*ys -0.71*ys*ys*ys +0.15*ys*ys*ys*ys +0.35*ys*ys*ys*ys*ys;
  double p1 =  0.314;
  double p2 =  0.027;
  double p3 =  3.18  +0.27*ys +1.61*ys*ys +0.24*ys*ys*ys -1.46*ys*ys*ys*ys;
  double func = p0 + p1*sin( p2*x+p3 );
  //return func + lconst;
  return func;
}

double t0_func_106_100(double *val, double *pars){
   double xx      = -1 * val[0];//rotate
   double yy      = -1 * val[1];//rotate
   double A       = pars[0];
   double A2      = pars[1];
   double x0      = pars[2];
   double x1      = pars[3];
   double y0      = pars[4];
   double sigmaX  = pars[5];
   double sigmaX2 = pars[6];
   double sigmaY  = pars[7];
   
   double gauss1 = A  * exp(-0.5 * pow((yy - y0) / sigmaY, 2));
   double gauss2 = A2 * exp(-0.5 * pow((yy - y0) / sigmaY, 2));
   
   if(xx < x0){
      return gauss1 * exp(-0.5 * pow((xx-x0)/sigmaX, 2));
   }else if (xx > x1) {
      return gauss2 * exp(-0.5 * pow((xx-x1)/sigmaX2, 2));
   }else  {
      double slope = (gauss2 - gauss1)/(x1 - x0);
      return gauss1 + slope * (xx - x0);
   }
}



double t0_func_106_200(double *val, double *params){
    double xx = val[0];
    double yy = val[1];
    double a_x     = params[0];//smoothness
    double min_x   = params[1];
    double max_x   = params[2];
    double x0      = params[3];//middle
    double y0      = params[4];
    double amp_y   = params[5];
    double sigmaY = params[6];
    double gaussPart = amp_y + amp_y *  -exp(-0.5 * pow((yy - y0) / sigmaY, 2));
    Double_t logistic_x = min_x + (max_x - min_x) / (1 + exp(-a_x * (xx - x0)));
    if(xx > 0){
       logistic_x =   max_x -  (max_x - min_x) / (1 + exp(-a_x * (xx + x0)));
    }
    return logistic_x - gaussPart;
}


double t0_func_106_300(double *val, double *pars){
   double xx = val[0];
   double amp1 = pars[0];
   return amp1;
}

double lconst_func_106_100(double *val, double *pars){
   double xx = val[0];
   double yy = val[1];

   double a_l6      = 0.2932;
   double min_l6    = 0.2884;
   double max_l6    = -0.1019;
   double ol6       = 32.48;
   double inclinel6 = 0.001359;
   double logistic_l6 = max_l6 - (max_l6 - min_l6) / (1 + exp(-a_l6 * (yy + ol6)));
   if(yy > 0) {
      logistic_l6 = min_l6 + (max_l6 - min_l6) / (1 + exp(-a_l6 * (yy - ol6)));
   }

    logistic_l6 = logistic_l6 + inclinel6 * yy;

   double a_l7      = 0.07115;
   double min_l7    = -0.1011;
   double max_l7    = 0.9754;
   double ol7       = 54.84;
   double inclinel7 = -0.002979;
   double logistic_l7 = max_l7 - (max_l7 - min_l7) / (1 + exp(-a_l7 * (xx + ol7)));
   if(xx > 0) {
      logistic_l7 = min_l7 + (max_l7 - min_l7) / (1 + exp(-a_l7 * (xx - ol7)));
   }

    logistic_l7 = logistic_l7 + inclinel7 * xx;

   double a_l8      = 0.15;
   double min_l8    = -0.58;
   double max_l8    = 0.5;
   double ol8       = 33;
   double inclinel8 = 0.004;
   double logistic_l8 = max_l8 - (max_l8 - min_l8) / (1 + exp(-a_l8 * (xx + ol8)));
   if(xx > 0) {
      logistic_l8 = min_l8 + (max_l8 - min_l8) / (1 + exp(-a_l8 * (xx - ol8)));
   }

    logistic_l8 = (logistic_l8 + inclinel8 * xx ) * TMath::Gaus(yy, -35, 15);

   double a_l9      = 0.15;
   double min_l9    = -0.58;
   double max_l9    = 0.5;
   double ol9       = 33;
   double inclinel9 = 0.004;
   double logistic_l9 = max_l9 - (max_l9 - min_l9) / (1 + exp(-a_l9 * (xx + ol9)));
   if(xx > 0) {
      logistic_l9 = min_l9 + (max_l9 - min_l9) / (1 + exp(-a_l9 * (xx - ol9)));
   }

    logistic_l9 = (logistic_l9 + inclinel9 * xx ) * TMath::Gaus(yy, 35, 15);

   double a_l10      = 0.72;
   double min_l10    = -0.27;
   double max_l10    = 0.04;
   double ol10       = 33;
   double inclinel10 = 0.00;
   double logistic_l10 = max_l10 - (max_l10 - min_l10) / (1 + exp(-a_l10 * (yy + ol10)));
   if(yy > 0) {
      logistic_l10 = min_l10 + (max_l10 - min_l10) / (1 + exp(-a_l10 * (yy - ol10)));
   }

    logistic_l10 = (logistic_l10 + inclinel10 * yy ) * TMath::Gaus(xx, -50, 10);

   double logistic_l11 =  (logistic_l10) * TMath::Gaus(xx, 50, 15);




   double g1 = 0.45 * TMath::Gaus(xx, 0, 50) * TMath::Gaus(yy,-50, 30);
   double g2 =  0.45 * TMath::Gaus(xx, 0, 50) * TMath::Gaus(yy, 50, 30);
   double g3 = -0.45 * TMath::Gaus(xx, 50, 10) * TMath::Gaus(yy, 30, 10);
   double g4 = -0.40 * TMath::Gaus(xx, 50, 10) * TMath::Gaus(yy, -25, 10);


   //return -1 * (logistic_l6 + logistic_l7 + logistic_l8 + logistic_l9 + g1 + g2 + logistic_l10 + logistic_l11 + g3 + g4 ) - 4.481 ;
   //return (logistic_l6 + logistic_l7 + logistic_l8 + logistic_l9 + g1 + g2 + logistic_l10 + logistic_l11 + g3 + g4 ) + 4.481 ;
   return (logistic_l6 + logistic_l7 + logistic_l8 + logistic_l9 + g1 + g2 + logistic_l10 + logistic_l11 + g3 + g4 );
}




double lconst_func_106_200(double  *val, double *pars){
   double xx = val[0];
   double yy = val[1];
   double x_dep = 0;
   double x_dep2 = 0;
   double y_dep = 0;

      double logistic_x;
      double a_x   = 0.12;
      double min_x = -0.3;
      double max_x = 0.012;
      double x0    = -61.9;
      double incline_x = 0.00;
//min_x dependence
      min_x = min_x * TMath::Gaus(yy, 0, 40);

      logistic_x = max_x - (max_x - min_x) / (1 + exp(-a_x * (xx + x0)));
      x_dep = logistic_x + incline_x * xx;

   
   double a_y   = 0.405;
   double min_y = 0.119;
   double max_y = 1.05;
   double y0    = 92.5;
   double incline = 0.0017;
   double offset = 0;
   double logistic_y = max_y - (max_y - min_y) / (1 + exp(-a_y * (yy + y0))) + offset;
   if(yy > 0) {
      logistic_y = min_y + (max_y - min_y) / (1 + exp(-a_y * (yy - y0))) + offset;
   }
   y_dep = logistic_y + incline*yy;

   double a_x2   = 0.391;
   double min_x2 = -0.07379;
   double max_x2 = 0.358;
   double x02    = 87.9;
   double incline_x2 = 0.00088;
   double logistic_x2 = max_x2 - (max_x2 - min_x2) / (1 + exp(-a_x2 * (xx + x02)));
   if(xx > 0) {
      logistic_x2 = min_x2 + (max_x2 - min_x2) / (1 + exp(-a_x2 * (xx - x02))) ;
   }
   x_dep2 = (logistic_x2 + incline_x2 * xx ) * TMath::Gaus(yy, 70, 10);

   double y_dep2 = 0.2 * TMath::Gaus(yy, -75, 40) * TMath::Gaus(xx, 90, 10);


   double g_1 = -0.1  * TMath::Gaus(xx, -10, 30) * TMath::Gaus(yy, -60, 20);
   double g_2 =  0.08 * TMath::Gaus(xx, 60, 40) * TMath::Gaus(yy, -75, 15);
   double g_3 =  -0.1 * TMath::Gaus(xx, 100, 30) * TMath::Gaus(yy, 50, 15);
   double g_4 =  -0.2 * TMath::Gaus(xx, -10, 20) * TMath::Gaus(yy, 20, 30);
   double g_5 =  -0.1 * TMath::Gaus(xx, -50, 50) * TMath::Gaus(yy, 55, 30);
   double g_6 =  -0.2 * TMath::Gaus(xx, 100, 70) * TMath::Gaus(yy, 100, 40);

   
   double g_7 =  0.18 * TMath::Gaus(xx, -50, 50) * TMath::Gaus(yy, -90, 20);
   double g_8 = -0.18 * TMath::Gaus(xx, 50, 50) * TMath::Gaus(yy, -100, 15);
   double g_9 =  0.15 * TMath::Gaus(xx, -10, 30) * TMath::Gaus(yy, -20, 20);
   double g_10 = -0.10 * TMath::Gaus(xx, 100, 40) * TMath::Gaus(yy, -30, 30);
   double g_11 = 0.15 * TMath::Gaus(xx, 5, 40) * TMath::Gaus(yy, 50, 40);
   double g_12 = -0.1 * TMath::Gaus(xx, -40, 20) * TMath::Gaus(yy, 55, 15);
   double g_13 = -0.1 * TMath::Gaus(xx, 30, 20) * TMath::Gaus(yy, 60, 15);

   double g_15 = 0.2 * TMath::Gaus(yy, -10,25 ) * TMath::Gaus(xx, -10, 40);


   //return x_dep + y_dep + x_dep2 + y_dep2 + g_1 +g_2 + g_3 + g_4 + g_5 + g_6 + g_7 + g_8 + g_9 + g_10 + g_11 + g_12 + g_13 + g_15 + 3.134;
   //return -1 * (x_dep + y_dep + x_dep2 + y_dep2 + g_1 +g_2 + g_3 + g_4 + g_5 + g_6 + g_7 + g_8 + g_9 + g_10 + g_11 + g_12 + g_13 + g_15 + 3.134);
   return -1 * (x_dep + y_dep + x_dep2 + y_dep2 + g_1 +g_2 + g_3 + g_4 + g_5 + g_6 + g_7 + g_8 + g_9 + g_10 + g_11 + g_12 + g_13 + g_15 );
}

double lconst_func_106_300(double *val, double *pars){
   double xx = val[0];
   double yy = val[1];
   double g_1    =  0.5 *TMath::Gaus(yy, -40, 70 ) * TMath::Gaus(xx, -70, 30) ;
   double g_2    =  0.5 *TMath::Gaus(yy, -150, 100 ) * TMath::Gaus(xx, 150, 80) ;
   double g_3    = -0.4 *TMath::Gaus(xx,  50, 40 ) * TMath::Gaus(yy, 140, 15) ;
   double g_4    = -0.2 *TMath::Gaus(yy,  0, 60 ) * TMath::Gaus(xx, 105, 15) ;
   double g_5    = -0.15*TMath::Gaus(yy,  10, 40 ) * TMath::Gaus(xx, -15, 15) ;
   
   double g_12   = -0.2 *TMath::Gaus(yy,  20, 15 ) * TMath::Gaus(xx, -30, 30) ;
   double g_13   = -0.3 *TMath::Gaus(xx,  -150, 60 ) * TMath::Gaus(yy, 75, 15) ;
   double g_14   = 0.15 *TMath::Gaus(xx,  60, 20 ) * TMath::Gaus(yy, -105, 10) ;
   double g_15   = 0.15 *TMath::Gaus(xx,  10, 20 ) * TMath::Gaus(yy, -75, 10) ;

   double g_22 =  0.4*TMath::Gaus(yy, -60, 30) * TMath::Gaus(xx, -15, 30);
   double g_23 =  0.4*TMath::Gaus(yy,  60, 30) * TMath::Gaus(xx, -15, 30);

   //return g_1 + g_2 + g_3 + g_4 + g_5 + g_12 + g_13 + g_14 + g_15 + g_22 + g_23 +1.955;
   //return -1 * (g_1 + g_2 + g_3 + g_4 + g_5 + g_12 + g_13 + g_14 + g_15 + g_22 + g_23 +1.955);
   return -1 * (g_1 + g_2 + g_3 + g_4 + g_5 + g_12 + g_13 + g_14 + g_15 + g_22 + g_23 );
}

double t0_func_107_100_200_300(double *val, double *pars){
  double xx   = val[0];
  double yy   = val[1];
  double mag  = pars[0];
  double sx   = pars[1];
  double mx   = pars[2];
  double sy   = pars[3];
  double my   = pars[4];
  double ped  = pars[5];
  double argx = (xx-sx)/mx;
  double argy = (yy-sy)/my;
  return mag*exp(-0.5*argx*argx)*exp(-0.5*argy*argy)+ped;
  
}

double lconst_func_107_100(double *val, double *par){
  double xx   = val[0];
  double yy   = -1*val[1];
  double p0   = par[0];
  double p1   = par[1];
  double p2   = par[2];
  double p3   = par[3];
  double p4   = par[4];
  double s0   = par[5];
  double s1   = par[6];
  //double lc   = par[7];
    
  double pol  = p0+p1*yy+p2*yy*yy+p3*yy*yy*yy+p4*yy*yy*yy*yy;
  double st   = s0/(exp(0.3*(abs(yy-3)+s1))+1)-0.15;

  double argx = (xx)/20;
  //return -1*(st*exp(-0.5*argx*argx)+pol)+lc;
  return -1*(st*exp(-0.5*argx*argx)+pol);
}

double lconst_func_107_200(double *val, double *par){
  double xx    = -1*val[0];
  double yy    = val[1];
  double p0    = par[0];
  double p1    = par[1];
  double p2    = par[2];
  double p3    = par[3];
  double p4    = par[4];
  double s0    = par[5];
  double s1    = par[6];
  double ss0   = par[7];
  double ss1   = par[8];
  //double lc    = par[9];
  
  double pol   = p0+p1*yy+p2*yy*yy+p3*yy*yy*yy+p4*yy*yy*yy*yy;
  double st1   = s0/(exp(0.25*(-yy+s1))+1);
  double st2   = ss0/(exp(0.2*(abs(yy)+ss1))+1);
  double argx  = (xx+100)/35;
  double argx2 = (xx-70)/40;
  
  //return st2*exp(-0.5*argx*argx)+pol+st1*exp(-0.5*argx2*argx2)+lc;
  return st2*exp(-0.5*argx*argx)+pol+st1*exp(-0.5*argx2*argx2);
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

   // LorentzConstant rough values
   fLorentzCorrections[103][0].SetLorentzConstRoughFunc(const_func, {+2.891});
   fLorentzCorrections[103][1].SetLorentzConstRoughFunc(const_func, {-2.324});
   fLorentzCorrections[103][2].SetLorentzConstRoughFunc(const_func, {-1.005});

   fLorentzCorrections[104][0].SetLorentzConstRoughFunc(const_func, {+3.173});
   fLorentzCorrections[104][1].SetLorentzConstRoughFunc(const_func, {-3.007});
   fLorentzCorrections[104][2].SetLorentzConstRoughFunc(const_func, {-1.080});

   fLorentzCorrections[106][0].SetLorentzConstRoughFunc(const_func, {+4.481});
   fLorentzCorrections[106][1].SetLorentzConstRoughFunc(const_func, {-3.134});
   fLorentzCorrections[106][2].SetLorentzConstRoughFunc(const_func, {-1.955});

   fLorentzCorrections[107][0].SetLorentzConstRoughFunc(const_func, {+3.461});
   fLorentzCorrections[107][1].SetLorentzConstRoughFunc(const_func, {-2.004});
   fLorentzCorrections[107][2].SetLorentzConstRoughFunc(const_func, {-1.505});

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

   fLorentzCorrections[103][0].SetLorentzConstFunc(lconst_func_103_100,{
       0.252,0.00198,-3.84e-5,-7.346e-8,-3.926e-8,
       0.1,-30,
       -43,10,
       });

   fLorentzCorrections[103][1].SetLorentzConstFunc(lconst_func_103_200,{
       0.2389,0.00236,4.1488e-6,-1.9095e-7,-3.9017e-9,
       0.226,-93.72,
       75,15,
       });

   fLorentzCorrections[103][2].SetLorentzConstFunc(lconst_func_103_300,{
       -0.1675,0.000824,3.958e-5,-3.4776e-8,-1.773e-9,
       0.3523,-0.00923,-5.0212e-5,4.93e-7,
       8.15,-0.2073,0.00536,4.673e-6,-4.03688e-7,
       });

   fLorentzCorrections[103][0].SetVDriftXFunc(const_func, {0.005});
   fLorentzCorrections[103][1].SetVDriftXFunc(const_func, {-0.0035});
   fLorentzCorrections[103][2].SetVDriftXFunc(const_func, {-0.002});

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
   //VdriftZ
   fLorentzCorrections[104][0].SetVDriftZFunc(const_func, {0.0105});
   fLorentzCorrections[104][1].SetVDriftZFunc(const_func, {0.010});
   fLorentzCorrections[104][2].SetVDriftZFunc(const_func, {0.010});
   //VdriftX
   fLorentzCorrections[104][0].SetVDriftXFunc(const_func, {0.004});
   fLorentzCorrections[104][1].SetVDriftXFunc(const_func, {-0.0029});
   fLorentzCorrections[104][2].SetVDriftXFunc(const_func, {-0.0019});
   //Lorentz function
   fLorentzCorrections[104][0].SetLorentzConstFunc(lconst_func_104_100);
   fLorentzCorrections[104][1].SetLorentzConstFunc(lconst_func_104_200);
   fLorentzCorrections[104][2].SetLorentzConstFunc(lconst_func_104_300);

   //GTR-Module106
   //t0
   fLorentzCorrections[106][0].SetT0Func(t0_func_106_100, {
         300, 279, -25, 29, 25, 20, 25, 300
         });
   fLorentzCorrections[106][1].SetT0Func(t0_func_106_200, {
         0.2, 220, 290, -85, -40, 50, 70
         });
   fLorentzCorrections[106][2].SetT0Func(t0_func_106_300, {
         210
         });
   //VdriftZ
   fLorentzCorrections[106][0].SetVDriftZFunc(const_func, {0.015});
   fLorentzCorrections[106][1].SetVDriftZFunc(const_func, {0.015});
   fLorentzCorrections[106][2].SetVDriftZFunc(const_func, {0.015});
   //VdriftX
   fLorentzCorrections[106][0].SetVDriftXFunc(const_func, {0.007});
   fLorentzCorrections[106][1].SetVDriftXFunc(const_func, {-0.005});
   fLorentzCorrections[106][2].SetVDriftXFunc(const_func, {-0.0025});
   //Lorentz function
   fLorentzCorrections[106][0].SetLorentzConstFunc(lconst_func_106_100);
   fLorentzCorrections[106][1].SetLorentzConstFunc(lconst_func_106_200);
   fLorentzCorrections[106][2].SetLorentzConstFunc(lconst_func_106_300);

   //GTR-Module107
   fLorentzCorrections[107][0].SetT0Func(t0_func_107_100_200_300, {
       60,
       0,
       20,
       6,
       17.5,
       155
     });

   fLorentzCorrections[107][1].SetT0Func(t0_func_107_100_200_300, {
       78,
       0,
       25,
       0,
       25,
       180
     });

   fLorentzCorrections[107][2].SetT0Func(t0_func_107_100_200_300, {
       80,
       0,
       40,
       0,
       40,
       180
     });

   fLorentzCorrections[107][0].SetVDriftZFunc(const_func, {0.013});
   fLorentzCorrections[107][1].SetVDriftZFunc(const_func, {0.018});
   fLorentzCorrections[107][2].SetVDriftZFunc(const_func, {0.020});

   fLorentzCorrections[107][0].SetLorentzConstFunc(lconst_func_107_100,{
       0.177,-0.0001986,0.000308,2.966e-7,-1.31e-7,
       -0.277,-44.39,
       });

   fLorentzCorrections[107][1].SetLorentzConstFunc(lconst_func_107_200,{
       -0.5813,0.000912,2.609e-6,-5.212e-9,1.856e-9,
       0.4,-80,
       0.65,-85,
       });

   fLorentzCorrections[107][2].SetLorentzConstFunc(nullptr);

   fLorentzCorrections[107][0].SetVDriftXFunc(const_func, {0.005});
   fLorentzCorrections[107][1].SetVDriftXFunc(const_func, {-0.0035});
   fLorentzCorrections[107][2].SetVDriftXFunc(const_func, {-0.002});

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

