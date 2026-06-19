////////////////////////////////////////////////////////////////////////////////////
// class E16ANA_STSGeometry
//                                            K. Aoki
//
// The class is a singleton. It manages local coordinate of STS.
//
// Definition regarding the local coordinate system:
//
// P-side is front. Fix your view point so that you always look at the p-side surface.
// P-side Strip 0 is at the top left corner.
// N-side Strip 0 is on the right.
//
// 
//
////////////////////////////////////////////////////////////////////////////////////

#ifndef E16ANA_STSGeometry_h__
#define E16ANA_STSGeometry_h__

#include <cmath>

class E16ANA_STSGeometry{
 private:
  E16ANA_STSGeometry(){};
  static E16ANA_STSGeometry* pInstance;

 public:
  static E16ANA_STSGeometry* instance();
  static int verbosity;
  
  //const TVector3& GetLPos(int mod,int ch);

  std::pair<double, double> GetBotRef(int iStrip); // Get bottom reference point of iStrip on P-side.
  std::pair<double, double> GetTopRef(int iStrip); // Get top reference point of iStrip on P-side.

  bool IsValidStrip(int iStrip);
  bool IsActiveArea(const std::pair<double,double>& pos);
  bool IsZStrip(int iPStrip);
  bool IsNonZStrip(int iPStrip);

  double X2StripN(double x);
  double GetLocalX_fromN(double strip); // Get Local X from N-side strip number.

  std::pair<double, double> GetLocal(int iNStrip, int iPStrip);
  std::pair<double, double> GetLocalD(double x, double pstrip);

  double CalcX(std::pair<double,double>& ref, double y); // Find x so that (x,y) and ref are on a stereo angled line.
  double CalcY(std::pair<double,double>& ref, double x); // Find y so that (x,y) and ref are on a stereo angled line.

  double GetPosX_B(int iStrip, double y); // Calculate x from bottom reference point.
  double GetPosX_T(int iStrip, double y); // Calculate x from top reference point.

  double GetPosY_B(int iStrip, double x); // Calculate y from bottom ref point.
  double GetPosY_T(int iStrip, double x); // Calculate y from top ref point.

  int Ch2StripP(int iChannel); // Convert channel number to strip number on P-side.
  
  //  double GetPosY(int iStrip, double x);

 private:
  //TVector3 pos;
  // constants in mm;
  // constants for p side
  const double p_near_y = 29076.522/1000.; // Central Y of a pair of near pads 
  const double p_far_y = 26433.222/1000.;
  const double p_dy_eo = 881.10/1000.; // Distance in Y direction of even/odd pads.

  
  // I am not confident which strip is 0. But I am sure about strip 134. Everyhing is counted from 134.
  // stripN as defined in cad.
  //const double p134_BX = -29743.4275/1000.; Wrong by one strip.
  //const double p134_BY = -29657.080/1000.;
  const double p134_BX = -29686.7337/1000.;
  const double p134_BY = -29666.9955/1000.;
  //const double p134_TX = -21933.2660/1000.;  Wrong by one stipr
  //const double p134_TY = 29666.9945/1000.;
  const double p134_TX = -21875.2657/1000.;
  const double p134_TY = 29666.9945/1000.;

  public:
  
  const double p_phi = 7.5 /180.*3.14159265;
  const double p_tan_phi = tan(p_phi);
  const double error = -9999.;

  const double iStrip_start = 0;
  const double iStrip_end = 1023;
  const double iStrip_PB = 134;
  const double iPStrip_LeftBot = 134;
  const double StripPitch = 58./1000.;

  const double DX_active = 59650. / 1000.;
  const double DY_active = 59608. / 1000.;
  const double halfDX_active = DX_active / 2.;
  const double halfDY_active = DY_active / 2.;
};


#endif
