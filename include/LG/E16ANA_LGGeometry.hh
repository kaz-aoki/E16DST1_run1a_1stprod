#include <map>
#include <string>
#include <vector>
#include "TArrayD.h"
#include <TCanvas.h>
#include <unordered_map>
#include <TVector3.h>

using namespace std;

class E16ANA_LGGeometry
{
 private:


 public:
 E16ANA_LGGeometry(){};

 void MakeLGLocal();
 void MakeLGGlobal();

 struct globalposition{
	double X;
	double Y;
	double Z;
        double R;
        double Theta;
        double Phi;
        };
 struct localposition{
	double X;
	double Y;
	double Z;
        double R;
        double Theta;
        double Phi;
        };


 unordered_map<uint16_t, localposition*> *LGLocalGeometry = new unordered_map<uint16_t, localposition*>;
 unordered_map<string, globalposition*> *LGGlobalGeometry = new unordered_map<string, globalposition*>;
 
 ~ E16ANA_LGGeometry(){
	delete LGLocalGeometry;
	delete LGGlobalGeometry;
//	LGLocalGeometry->clear();
//	LGGlobalGeometry->clear();
	};

localposition* GetLocalPosition(uint16_t channel);
globalposition* GetGlobalPosition(uint16_t module, uint16_t channel);

TVector3 GetLocalPosForE16ANA(uint16_t channel);



/*localposition* GetLocalPosition(uint16_t channel){
	//auto posptr = ((* this->LGLocalGeometry)[channel]);
	auto posptr = ((* LGLocalGeometry)[channel]);
	return posptr;	
	}


globalposition* GetGlobalPosition(uint16_t module, uint16_t channel){
	string key = to_string(module) + to_string(channel);
	//auto posptr = ((* this->LGGlobalGeometry)[key]);
	auto posptr = ((* LGGlobalGeometry)[key]);
	cout<<posptr->Y<<endl;
	return posptr;	
	}
*/

};
