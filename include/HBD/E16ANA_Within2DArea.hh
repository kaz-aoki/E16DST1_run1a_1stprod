#ifndef E16ANA_Within2DArea_h
#define E16ANA_Within2DArea_h

#include "E16ANA_Within2DArea.hh"
#include <vector>

class E16ANA_Within2DArea {
  
public:
  E16ANA_Within2DArea(const std::vector<double> _vx, const std::vector<double> _vy);
  E16ANA_Within2DArea();
  ~E16ANA_Within2DArea();
  void SetArea(const std::vector<double> _vx, const std::vector<double> _vy);
  static bool IsWithin2DArea(const std::vector<double> vertex_x, const std::vector<double> vertex_y,
			     const double px, const double py);
  bool IsWithin2DArea(const double px, const double py);
  
private:
  std::vector<double> vx;
  std::vector<double> vy;

};

#endif // E16ANA_Within2DArea_h
