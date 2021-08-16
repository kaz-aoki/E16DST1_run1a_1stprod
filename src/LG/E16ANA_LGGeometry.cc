#include <iostream>
#include <fstream>
#include "TMath.h"
#include "E16ANA_LGGeometry.hh"
#include <TVector3.h>

using namespace std;

const uint16_t block_list[38] = {0,1,2,3,4,5  ,10,11,12,13,14,15  ,20,21,22,23,24,25,26  ,30,31,32,33,34,35,36  ,40,41,42,43,44,45  ,50,51,52,53,54,55};
const uint16_t module_list[6] = {102, 103, 104, 106, 107, 108};
const double pi = 3.14;

void E16ANA_LGGeometry::MakeLGLocal(){
	for(int i=0; i<38; i++){//channel loop
	double lx = 0;
	double ly = 0;
	double lz = 0;
	double ltheta = 0;
	double lphi = 0;

	switch(int(block_list[i]/10)){
		case 0://BlockID 0-5
			lx = -1436;
			ly = -315;
			lz = (block_list[i]%10*2 -5)*882./14.;
			ltheta = (block_list[i]%10 - 2.5)*30./6.;
			lphi = -12.;
			break;
		case 1://BlockID 10-15
			lx = -1601;	
			ly = -209;
			lz = (block_list[i]%10*2 -5)*882./14.;
			ltheta = (block_list[i]%10 - 2.5)*30./6.;
			lphi = -7.;
			break;
		case 2://BlockID 20-26
			lx = -1757;
			ly = -83;
			lz = (block_list[i]%10*2 -6)*882./14.;
			ltheta = (block_list[i]%10 - 3)*30./7.;
			lphi = -3.;
			break;	
		case 3://BlockID 30-36
			lx = -1757;
                        ly = 83;
			lz = (block_list[i]%10*2 -6)*882./14.;
			ltheta = (block_list[i]%10 - 3)*30./7.;
			lphi = 3.;
			break;
		case 4://BlockID 40-45
			lx = -1601;
			ly = 209;
			lz = (block_list[i]%10*2 -5)*882./14.;
			ltheta = (block_list[i]%10 - 2.5)*30./6.;
			lphi = 7.;
			break;
		case 5://BlockID 50-55
			lx = -1436;
			ly = 315;
			lz = (block_list[i]%10*2 -5)*882./14.;
			ltheta = (block_list[i]%10 - 2.5)*30./6.;
			lphi = 12.;
			break;
		default:
			break;
	}	


	localposition* localpos = new localposition;
	//localposition localpos;
	localpos->Y = ly;
	localpos->X = lx;
	localpos->Z = lz;
	localpos->R = abs(lx);
	localpos->Theta = ltheta;
	localpos->Phi = lphi;

	//cout<<localpos.R<<endl;
	uint16_t channel = block_list[i];
	//(* this->LGLocalGeometry)[channel] =  localpos;
	(* this->LGLocalGeometry)[channel] =  localpos;
	//delete localpos;
	}//channel loop
	 auto test = (* LGLocalGeometry)[30];
	 
         cout<<test->R<<endl;
}


void E16ANA_LGGeometry::MakeLGGlobal(){
	MakeLGLocal();
	for(int i=0; i<6; i++){
		double theta_module = (module_list[i]-102)*30.;
		double sin = TMath::Sin(theta_module*TMath::Pi()/180.);
		double cos = TMath::Cos(theta_module*TMath::Pi()/180.);
		for(int j=0; j<38; j++){
			uint16_t block = uint16_t(block_list[j]);
			//localposition* localpos = (* this->LGLocalGeometry)[block];		
			localposition* localpos = (* LGLocalGeometry)[block];		
			double lx = localpos->X;
			double ly = localpos->Y;
			double lz = localpos->Z;
			double lr = localpos->R;
			double ltheta = localpos->Theta;
			double lphi= localpos->Phi;
			//cout<<"local"<<localpos->R<<endl;
			double gx = lx*cos - lz*sin;
			double gy = ly;
			double gz = lx*sin + lz*cos;

			E16ANA_LGGeometry::globalposition* globalpos = new E16ANA_LGGeometry::globalposition;
			//E16ANA_LGGeometry::globalposition globalpos;
	        	globalpos->X = gx;
       		 	globalpos->Y = gy;
        		globalpos->Z = gz;
        		globalpos->R = lr;
        		globalpos->Theta = ltheta + theta_module;
        		globalpos->Phi = lphi;

		        string key = to_string(module_list[i])+to_string(block_list[j]);
       			//(* this->LGGlobalGeometry)[key] =  globalpos;
       			(* this -> LGGlobalGeometry)[key] =  globalpos;
			//cout<<block<<" "<<globalpos.R <<endl;
			//delete localpos;
			}
		}
		
		auto test = (* LGGlobalGeometry)["10630"];
		cout<<"test"<<test->R<<endl;


	}


E16ANA_LGGeometry::localposition* E16ANA_LGGeometry::GetLocalPosition(uint16_t channel){
	auto posptr = ((* LGLocalGeometry)[channel]);
        return posptr;
        }

E16ANA_LGGeometry::globalposition* E16ANA_LGGeometry::GetGlobalPosition(uint16_t module, uint16_t channel){
        string key = to_string(module) + to_string(channel);
	//auto posptr = ((* LGGlobalGeometry)[key]);
	auto posptr = LGGlobalGeometry -> at(key);
	//cout<<"get"<< posptr->R <<endl;
	return posptr;
        }


TVector3 E16ANA_LGGeometry::GetLocalPosForE16ANA(uint16_t channel){//210816nakasuga

	double lx = -10000.;
	double ly = -10000.;
	double lz = -10000.;

	switch(int(channel/10)){
		case 0://BlockID 0-5
			lz = -1436;
			ly = -315;
			lx = (channel%10*2 -5)*882./14.;
			break;
		case 1://BlockID 10-15
			lz = -1601;	
			ly = -209;
			lx = (channel%10*2 -5)*882./14.;
			break;
		case 2://BlockID 20-26
			lz = -1757;
			ly = -83;
			lx = (channel%10*2 -6)*882./14.;
			break;	
		case 3://BlockID 30-36
			lz = -1757;
                        ly = 83;
			lx = (channel%10*2 -6)*882./14.;
			break;
		case 4://BlockID 40-45
			lz = -1601;
			ly = 209;
			lx = (channel%10*2 -5)*882./14.;
			break;
		case 5://BlockID 50-55
			lz = -1436;
			ly = 315;
			lx = (channel%10*2 -5)*882./14.;
			break;
		default:
			break;
	}	

	TVector3 lpsana(lx,ly,lz);
	return lpsana;

}
