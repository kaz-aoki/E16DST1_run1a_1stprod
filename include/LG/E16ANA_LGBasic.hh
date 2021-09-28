#ifndef E16ANA_LGBasic_h
#define E16ANA_LGBasic_h

#include <vector>
#include "E16DST_DST0.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1Constant.hh"
#include "E16ANA_LGConstant.hh"
#include <unordered_map>
#include <iostream>
#include <set>
using namespace std;



class E16ANA_LGBasic
{

public:

  //E16ANA_LGBasic(){};
E16ANA_LGBasic();

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
void SetCalibMap();
void SetTemplate();
void ReadDeadChannelData();

ch_pp* GetSpec(uint16_t module, uint16_t block);
ch_pp* GetSpec(int ip);
double GetT0(uint16_t module, uint16_t block);
double GetGain(uint16_t module, uint16_t block);
int DeadChannelStatus(uint16_t module, uint16_t block);

~E16ANA_LGBasic(){
};
protected:

struct ip_pp{
        int IP;
        int PP;
        int TIME;
        int VTH_TYPE;
        int WF_TYPE;
        };

  static TGraph* gtmpl;
  static int ngtmpl;
  static double gtmplx[200];
  static double gtmply[200];
  static double tmplwidth; //[cell]

private:

ch_pp lgspecmap[110][60];
ch_pp lgspecmap_ip[100];
double t0map[110][60];
double gainmap[110][60];
int deadchmap[110][60];

};



#endif //E16ANA_LGBasic_h
