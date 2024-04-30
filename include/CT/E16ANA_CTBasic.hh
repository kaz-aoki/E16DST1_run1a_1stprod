#ifndef E16ANA_CTBasic_h
#define E16ANA_CTBasic_h

#include <vector>
// #include "E16DST_DST0.hh"
#include "E16DST_Constant.hh"
#include "E16ANA_CalibDBManager.hh"
// #include "E16DST_DST1Constant.hh"
#include <unordered_map>
#include <iostream>
#include <set>
using namespace std;



class E16ANA_CTBasic
{

public:

  //E16ANA_CTBasic(){};
E16ANA_CTBasic();

struct ch_pp{
        char LorR;
        int DEG;
        int BLID;
        int MODULE;
        int BLOCK;
        int PP;
        int DRS4CH;
        int TRIGID;
        int HVCH;
        int IP;
        int TIME;
        int VTH_TYPE;
        double WF_TYPE;
        };


void SetMap();
// void SetCalibMap();
// void SetTemplate();
// void ReadDeadChannelData();

ch_pp* GetSpec(uint16_t module, uint16_t block);
ch_pp* GetSpec(int ip);
// double GetT0(uint16_t module, uint16_t block);
// double GetGain(uint16_t module, uint16_t block);
// int DeadChannelStatus(uint16_t module, uint16_t block);

~E16ANA_CTBasic(){
};
protected:

struct ip_pp{
        int IP;
        int PP;
        int TIME;
        int VTH_TYPE;
        int WF_TYPE;
        };

  // static TGraph* gtmpl;
  // static int ngtmpl;
  // static double gtmplx[E16DST_Constant::NSamplesCT];
  // static double gtmply[E16DST_Constant::NSamplesCT];
  // static double tmplwidth; //[cell]

private:

ch_pp ctspecmap[110][60];
ch_pp ctspecmap_ip[100];
// double t0map[110][60];
// double gainmap[110][60];
// int deadchmap[110][60];

};



#endif //E16ANA_CTBasic_h
