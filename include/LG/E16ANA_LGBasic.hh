#ifndef E16ANA_LGBasic_h
#define E16ANA_LGBasic_h

#include <vector>
#include "E16DST_DST0.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1Constant.hh"
#include "E16ANA_LGConstant.hh"
//#include "LGDST0ANA.h"
#include <unordered_map>
#include <iostream>
#include <set>
using namespace std;



class E16ANA_LGBasic
{

public:

E16ANA_LGBasic(){};

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


//static E16ANA_LGBasic* lgbasic = new E16ANA_LGBasic();
//void LGSetUp();
void MakeMap();
void SetMap();

unordered_map<string, ch_pp*>*  lgdatamap = new unordered_map<string, ch_pp*>;

unordered_map<int, ch_pp*>*  lgdatamap_ip = new unordered_map<int, ch_pp*>;

  //ch_pp lgdatamap[10][60];
  //ch_pp lgdatamap_ip[50];

ch_pp* GetSpec(uint16_t module, uint16_t block);
ch_pp* GetSpec(int ip);

void LGWFPeak(double* dat, double* peak, int* peakx, double* timing);
void LGWFBaseline(double* dat, int peakx, double* baseline, double* baselinerms);
void LGWFIntegral(double* dat, int peakx, double baseline, double* integral, int* falltime);

  //string file_channelmap();
  //string file_drs4assign();
  //string file_drs4assign_run0a();
  //string file_timeoffset();
  //string file_binary();


~E16ANA_LGBasic(){
	//lgdatamap->clear();
	delete lgdatamap;
	delete lgdatamap_ip;
	//lgdatamap_ip->clear();
};
protected:

struct ip_pp{
        int IP;
        int PP;
        int TIME;
        int VTH_TYPE;
        int WF_TYPE;
        };

private:


};



#endif //E16ANA_LGBasic_h
