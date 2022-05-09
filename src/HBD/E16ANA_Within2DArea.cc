#include "E16ANA_Within2DArea.hh"

#include <vector>
#include <iostream>

E16ANA_Within2DArea::E16ANA_Within2DArea(const std::vector<double> _vx, const std::vector<double> _vy):
  vx(_vx), vy(_vy)
{
}

E16ANA_Within2DArea::E16ANA_Within2DArea()
{
}

E16ANA_Within2DArea::~E16ANA_Within2DArea()
{
}

void E16ANA_Within2DArea::SetArea(const std::vector<double> _vx, const std::vector<double> _vy)
{
  vx.clear();
  vy.clear();
  vx = _vx;
  vy = _vy;
}

bool E16ANA_Within2DArea::IsWithin2DArea(const std::vector<double> vertex_x, const std::vector<double> vertex_y, const double px, const double py)
{
  int n_crossings = 0;
  double t;
  std::vector<double> x;
  std::vector<double> y;
  
  if(vertex_x.size() == vertex_y.size() && vertex_x.size()>=3){
    x = vertex_x;
    y = vertex_y;
    x.push_back(vertex_x.at(0));// n polygon: x.at(0) == x.at(n+1)
    y.push_back(vertex_y.at(0));// n polygon: x.at(0) == x.at(n+1)

    for(int i=0; i<x.size()-1; i++){
      if( (y.at(i) <= py && y.at(i+1) > py)
	  ||(y.at(i) > py && y.at(i+1) <= py) ){
	t = (py - y.at(i))/(y.at(i+1)-y.at(i));
	if(px < (x.at(i)+t*(x.at(i+1)-x.at(i)))){
	  n_crossings++;
	}
      }
    }
  }
  
  return n_crossings%2==1 ? true : false;
}

bool E16ANA_Within2DArea::IsWithin2DArea(const double px, const double py)
{
  int n_crossings = 0;
  double t;
  
  if(vx.size() == vy.size() && vx.size()>=3){
    for(int i=0; i<vx.size()-1; i++){
      if( (vy.at(i) <= py && vy.at(i+1) > py)
	  ||(vy.at(i) > py && vy.at(i+1) <= py) ){
	t = (py - vy.at(i))/(vy.at(i+1)-vy.at(i));
	if(px < (vx.at(i)+t*(vx.at(i+1)-vx.at(i)))){
	  n_crossings++;
	}
      }
    }
  }
  
  return n_crossings%2==1 ? true : false;
}
