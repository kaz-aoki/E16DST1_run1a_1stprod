#include "STS/E16ANA_STSGeometry.hh"
#include <iostream>

//static E16ANA_STSGeometry* E16ANA_STSGeometry::pInstance = NULL;
E16ANA_STSGeometry* E16ANA_STSGeometry::pInstance = NULL;

E16ANA_STSGeometry* E16ANA_STSGeometry::instance(){
    if (pInstance == NULL )  pInstance = new E16ANA_STSGeometry();
    return pInstance;
  }


std::pair<double, double> E16ANA_STSGeometry::GetBotRef(int iStrip){
  std::pair<double, double> result(error,error);
  if ( ! IsValidStrip(iStrip) ) return result;
  if ( iStrip >= iStrip_PB ) {
    result.first = p134_BX + StripPitch * (iStrip-iStrip_PB);
    result.second = p134_BY;
    return result;
  }
  result.first = p134_BX + StripPitch * (iStrip + (iStrip_end-iStrip_PB)+1 );
  result.second = p134_BY;
  return result;
}

std::pair<double, double> E16ANA_STSGeometry::GetTopRef(int iStrip){
  std::pair<double, double> result(error,error);
  if (! IsValidStrip(iStrip) ) return result;
  result.first = p134_TX + (iStrip - iStrip_PB)*StripPitch;
  result.second = p134_TY;
  return result;
}

bool E16ANA_STSGeometry::IsValidStrip(int iStrip)
{
  if (iStrip < iStrip_start ) return false;
  if (iStrip > iStrip_end) return false;
  return true;  
}

bool E16ANA_STSGeometry::IsActiveArea(std::pair<double,double>& pos)
{
  if ( fabs(pos.first)>DX_active ) return false;
  if ( fabs(pos.second)>DY_active) return false;
  return true;
}

// GetPosX_B and GetPosX_T agrees well <0.001
double E16ANA_STSGeometry::GetPosX_B(int iStrip, double y){
  auto pos = GetBotRef(iStrip);
  return CalcX(pos,y);
}

double E16ANA_STSGeometry::GetPosX_T(int iStrip, double y){
  auto pos = GetTopRef(iStrip);
  return CalcX(pos,y);
}

double E16ANA_STSGeometry::CalcX(std::pair<double, double>& ref, double y){
  double dy = y - ref.second;
  if ( fabs(dy) < 0.0000000001 ) return ref.first;
  double x = ref.first + dy*p_tan_phi;
  return x;
}

double E16ANA_STSGeometry::CalcY(std::pair<double, double>& ref, double x){
  double dx = x - ref.first;
  if ( fabs(dx) < 0.0000000001 ) return ref.second;
  double y = ref.second + dx/p_tan_phi;
  return y;
}

double E16ANA_STSGeometry::GetPosY_B(int iStrip, double x){
  auto pos = GetBotRef(iStrip);
  return CalcY(pos,x);
}

double E16ANA_STSGeometry::GetPosY_T(int iStrip, double x){
  auto pos = GetTopRef(iStrip);
  return CalcY(pos,x);
}

/*
double E16ANA_STSGeometry::GetLocal(int mod,int ch){
  double x = 9999;
  if ( ch >= 2048 ) return x;
  int strip = ch - 1024;
  x = 1024*58./1000.; // return in mm.
  return x;
}
*/

int E16ANA_STSGeometry::Ch2StripP(int iChannel){
  // This method works.
  if ( iChannel < 0 || iChannel > 1023 ) return -1;

  int iStrip = -1;
  if ( (iChannel % 2)==0 ) {
    iStrip = iChannel;
  } else {
    iStrip = iChannel + 2;
    if ( iStrip > 1023 ) iStrip = 1;
  }
  return iStrip;
}

double E16ANA_STSGeometry::GetLocalX_fromN(double iNStrip)
{
  if (! IsValidStrip(iNStrip) ) return error;
  double x = -((double)iNStrip - 511.5)*StripPitch;
  return x;
}

double E16ANA_STSGeometry::X2StripN(double x)
{
  return ( -x/StripPitch + 511.5 );
}

std::pair<double, double> E16ANA_STSGeometry::GetLocal(int iNStrip, int iPStrip){
  double x = GetLocalX_fromN(iNStrip);
  std::pair<double,double> posb(x,GetPosY_B(iPStrip,x));
  std::pair<double,double> post(x,GetPosY_T(iPStrip,x));
  bool bOK = IsActiveArea(posb);
  bool tOK = IsActiveArea(post);

  if ( bOK && tOK && IsZStrip(iPStrip) ) {
    std::cout << "Intersect points based on Top and bottom OK but P-side is Z strip" << std::endl;
  }
  if ( bOK ) return posb;
  if ( tOK ) return post;
  return std::pair<double,double>(error,error);
}

bool E16ANA_STSGeometry::IsZStrip(int iPStrip)
{
  // 0-133
  if ( iPStrip < iStrip_start ) return false;
  if ( iPStrip < iStrip_PB ) return true;
  return false;
}

bool E16ANA_STSGeometry::IsNonZStrip(int iPStrip)
{
  // 134-1023.
  if ( iPStrip < iStrip_PB ) return false;
  if ( iPStrip > iStrip_end ) return false;
  return true;
}
