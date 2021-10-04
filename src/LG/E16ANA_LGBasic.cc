#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <TH1.h>
#include <TSpectrum.h>

#include "E16ANA_LGBasic.hh"
#include "E16DST_DST1Constant.hh"
#include "E16ANA_LGConstant.hh"

#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1DefaultFilePath.hh"

#include <algorithm>
#include <unordered_map>   

using namespace E16ANA_LGConstant;

TGraph* E16ANA_LGBasic::gtmpl = nullptr;
int E16ANA_LGBasic::ngtmpl = E16DST_DST1Constant::kInvalidValue;
double E16ANA_LGBasic::gtmplx[200] = {E16DST_DST1Constant::kInvalidValue};
double E16ANA_LGBasic::gtmply[200] = {E16DST_DST1Constant::kInvalidValue};
double E16ANA_LGBasic::tmplwidth = E16DST_DST1Constant::kInvalidValue;

E16ANA_LGBasic::E16ANA_LGBasic(){

}

void E16ANA_LGBasic::SetMap(){
  //unordered_map<string, ch_pp*> mapdata;

        E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();
	FILE* fp_map = calib.CalibFileOpenBinary("LG-specmap", calib.CurrentRunID() );
	if ( fp_map==NULL ) {
		std::cout<<"[Error] spec map file is not found !"<<std::endl;
		exit(1);
	}

	while( feof(fp_map)==0 ){
	ch_pp spec;
	fread((char*)&spec,sizeof(spec),1,fp_map);
	std::string key = std::to_string(spec.MODULE)+std::to_string(spec.BLOCK);	

	int key_ip = spec.IP;	
	double typeflag = spec.WF_TYPE;
	if(typeflag == 0){
		spec.WF_TYPE =0.44;
		}
	if(typeflag == 1){
                spec.WF_TYPE = 0.27;
                }
	//cout<<" IP "<<key_ip<<" factor"<<spec.WF_TYPE<<endl;
	ch_pp* specpoint = new ch_pp;
	*specpoint=spec;
	//(* this->lgdatamap)[key] =  specpoint;
	//(* this->lgdatamap_ip)[key_ip] =  specpoint;
	int mod = spec.MODULE;
	int blk = spec.BLOCK;
	if(!(0<=mod&&mod<110&&0<=blk&&blk<60&&0<=key_ip&&key_ip<100)){
	  std::cerr<<"read invalid ID in specmap file"<<std::endl;
	  exit(1);
	}
	else{
	  lgspecmap[mod][blk] = *specpoint;
	  lgspecmap_ip[key_ip] = *specpoint;
	}
	//delete specpoint;
	}//while loop
	fclose(fp_map);
	
}

E16ANA_LGBasic::ch_pp* E16ANA_LGBasic::GetSpec(uint16_t module, uint16_t block){
  //std::string key = std::to_string(module)+std::to_string(block);
  //auto spec = (* this->lgdatamap)[key];
  E16ANA_LGBasic::ch_pp* spec = &lgspecmap[module][block];
  return spec;
}

E16ANA_LGBasic::ch_pp* E16ANA_LGBasic::GetSpec(int ip){
  //auto spec = (* this->lgdatamap_ip)[ip];
  E16ANA_LGBasic::ch_pp* spec = &lgspecmap_ip[ip];
  return spec;  
}

void E16ANA_LGBasic::SetCalibMap(){

        E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();
	FILE* fp_t0 = calib.CalibFileOpenBinary("LG-t0bych", calib.CurrentRunID() );
	if ( fp_t0==NULL ) {
		std::cout<<"[Error] t0 map file is not found !"<<std::endl;
		exit(1);
	}
	int module, block;
	double t0_mean;
	double t0_sigma;
	while( feof(fp_t0)==0 ){
	  fscanf(fp_t0, "%d %d %lf %lf", &module, &block, &t0_mean, &t0_sigma );
	  if(!(0<=module&&module<110&&0<=block&&block<60)){
	    std::cerr<<"read invalid ID in t0map file"<<std::endl;
	    exit(1);
	  }
	  else{
	    t0map[module][block] = t0_mean;
	  }
	}//while loop
	fclose(fp_t0);

	FILE* fp_gain = calib.CalibFileOpenBinary("LG-gainbych", calib.CurrentRunID() );
	if ( fp_gain==NULL ) {
		std::cout<<"[Error] gain map file is not found !"<<std::endl;
		exit(1);
	}
	double gain_mean;
	double gain_sigma;
	while( feof(fp_gain)==0 ){
	  fscanf(fp_gain, "%d %d %lf %lf", &module, &block, &gain_mean, &gain_sigma );
	  if(!(0<=module&&module<110&&0<=block&&block<60)){
	    std::cerr<<"read invalid ID in gainmap file"<<std::endl;
	    exit(1);
	  }
	  else{
	    gainmap[module][block] = gain_mean;
	  }
	}//while loop
	fclose(fp_gain);

}

double E16ANA_LGBasic::GetT0(uint16_t module, uint16_t block){
  double t0 = t0map[module][block];//[ns]
  return t0;
}

double E16ANA_LGBasic::GetGain(uint16_t module, uint16_t block){
  double gain = gainmap[module][block];
  return gain;
}

void E16ANA_LGBasic::SetTemplate(){

  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();
  FILE* fp_wf = calib.CalibFileOpenBinary("LG-WFtemplate", calib.CurrentRunID() );
  if ( fp_wf==NULL ) {
    std::cout<<"[Error] wf template file is not found !"<<std::endl;
    exit(1);
  }

  double xt, yt;
  std::vector<double> x;
  std::vector<double> y;
  int j=0;
  int peakx;
  double peaky;
  while( feof(fp_wf)==0 ){
    fscanf(fp_wf, "%lf %lf", &xt, &yt );
    x.push_back(xt);
    y.push_back(yt);
    gtmplx[j] = xt;
    gtmply[j] = yt;
    if(xt==0){
      peakx = j;
      peaky = yt;
    }
    j++;
  }
  ngtmpl = j;

  gtmpl = new TGraph(110,&x[0],&y[0]);

  for(int i=0;i<20;i++){
    int cell = peakx - i;
    double peakhalf = peaky/2.;
    if((cell!=peakx)&&y[cell]<peakhalf){
      tmplwidth=(peakhalf-y[cell])/(y[cell+1]-y[cell])+ cell - peakx;
      break;
    }
  }
  //std::cout<<"TEMPLATE WIDTH "<<tmplwidth<<std::endl;

  fclose(fp_wf);
}

void E16ANA_LGBasic::ReadDeadChannelData(){

  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();
  FILE* fp_dc = calib.CalibFileOpenBinary("LG-deadch", calib.CurrentRunID() );
  if ( fp_dc==NULL ) {
    std::cout<<"[Error] dead channel map file is not found !"<<std::endl;
    exit(1);
  }
  int module, block;
  int ch_status;
  while( feof(fp_dc)==0 ){
    fscanf(fp_dc, "%d %d %d", &module, &block, &ch_status );
    if(!(0<=module&&module<110&&0<=block&&block<60)){
      std::cerr<<"read invalid ID in dead channel map file"<<std::endl;
      exit(1);
    }
    else{
      deadchmap[module][block] = ch_status;
    }
  }
  fclose(fp_dc);

}

int E16ANA_LGBasic::DeadChannelStatus(uint16_t module, uint16_t block){
  int status = deadchmap[module][block];
  return status;
}
