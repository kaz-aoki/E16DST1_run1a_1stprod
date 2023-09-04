#ifndef E16ANA_HBDTH2Hex_h
#define E16ANA_HBDTH2Hex_h

#include <E16ANA_HBDConstant.hh>

#include <TH2Poly.h>

#include <string>

class E16ANA_HBDTH2Hex : public TH2Poly
{
  
public:
  E16ANA_HBDTH2Hex(const int module_id);
  E16ANA_HBDTH2Hex(const int module_id, const char *name, const char *title);
  E16ANA_HBDTH2Hex(std::string state);
  ~E16ANA_HBDTH2Hex();
  Int_t Fill(Double_t x, Double_t y, Double_t weight) override;
  int Fill(const int pad_id, const double weight);
  int FindBin(const double x, const double y);// bin number - 1 = pad id, x, y should be local coordinate
  void DrawWLocalCoordinate(char *option);//DO NOT USE with other histgrams together 
  
private:
  void SetHBDHexBin();
  bool IsXAxisReverse(){return (x_direction == -1) ? true : false;};
  bool IsXAxisNormal(){return (x_direction == 1) ? true : false;};
  bool IsYAxisReverse(){return (y_direction == -1) ? true : false;};
  bool IsYAxisNormal(){return (y_direction == 1) ? true : false;};

  int module_id;
  int x_direction;// 1: normal x-axis left to right, -1: reverse x-axis right to left
  int y_direction;// 1: normal y-axis bottom to top, -1: reverse y-axis top to bottom
  int n_pad_x = HBD_Board_Constant::n_pad_x;// number of pads in a row
  int n_pad_y = HBD_Board_Constant::n_pad_y;// number of pads in a column
  int n_pad = E16DST_Constant::NPadsHBD;// number of pads in one module
  double a = HBD_Board_Constant::hex_pad_length;// effective hexgonal pad length [mm] 10.+0.5/sqrt(3.)

  // origin of the board coordinate. board coordinate origin is "sticked" to pad ID 0. Even board is rotated.
  // While local coordinate is defined with respect to the board center.
  //
  //         pad ID 0
  //         _________
  //        /         \     * is the origin of the board
  //       /           \              /|\y
  //      /             \              |
  //      ---------------*      x <----|
  //            2a
};

#endif // E16ANA_HBDTH2Hex_h
