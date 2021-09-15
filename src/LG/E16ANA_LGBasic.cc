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
  double t0 = t0map[module][block];
  return t0;
}

double E16ANA_LGBasic::GetGain(uint16_t module, uint16_t block){
  double gain = gainmap[module][block];
  return gain;
}

void E16ANA_LGBasic::LGWFPeak(double* dat, double* peak, int* peakx, double* timing){

  for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){//peak search
    if(dat[cell]>*peak){
      if( E16ANA_LGConstant::kPeakSearchStart<cell && cell<E16ANA_LGConstant::kPeakSearchEnd ){
	*peak = dat[cell];
	*peakx = cell;
      }
    }
  }//peak search
  //std::cout<<"peakheight:"<<peakheight<<std::endl;
  //std::cout<<"peaktime:"<<peaktime<<std::endl;

  for(int i=0;i<E16ANA_LGConstant::kTimingSearchRegion;i++){//timing search
    int cell = *peakx - i;
    double peakhalf = *peak/2.;
    if(cell<0||cell>E16DST_Constant::NSamplesLG){
      *timing=E16DST_DST1Constant::kInvalidValue;
      break;
    }
    if(dat[cell]>*peak){
      *timing=E16DST_DST1Constant::kInvalidValue;
      break;
    }
    if(!(cell==*peakx)&&dat[cell]<peakhalf){
      *timing=(peakhalf-dat[cell])*(1./E16ANA_LGConstant::kTimeScale)/(dat[cell+1]-dat[cell])+cell;
      if(cell==(*peakx-1)){//remove the event like spike noise
	*timing=-10000;
      }
      break;
    }
    }//timing search


}

void E16ANA_LGBasic::LGWFBaseline(double* dat, int peakx, double* baseline, double* baselinerms){

  double baseline_sum = 0.;
  double baseline_sq_sum = 0.;
  int nb=0;
  for(int cell=(peakx+E16ANA_LGConstant::kBaselineStart); cell<(peakx+E16ANA_LGConstant::kBaselineEnd); cell++){
    if(cell<0||cell>E16DST_Constant::NSamplesLG){
      continue;
    }
    baseline_sum += dat[cell];
    baseline_sq_sum += dat[cell]*dat[cell];
    nb++;
  }
  *baseline = baseline_sum/(double)nb;
  *baselinerms = sqrt( baseline_sq_sum/(double)nb - (*baseline)*(*baseline) );
  //std::cout<<"baseline:"<<baseline<<std::endl;
  //std::cout<<"baselinerms:"<<baselinerms<<std::endl;

}

void E16ANA_LGBasic::LGWFIntegral(double* dat, int peakx, double baseline, double* integral, int* falltime){

  double integral_sum = 0.;
  bool peakcheck = false;
  int fallcount = 0;
  *falltime = peakx+E16ANA_LGConstant::kIntegralEnd;
  for(int cell=(peakx+E16ANA_LGConstant::kIntegralStart); cell<(peakx+E16ANA_LGConstant::kIntegralEnd); cell++){
    if(cell<0||cell>E16DST_Constant::NSamplesLG){
      integral_sum = E16DST_DST1Constant::kInvalidValue;
      *integral = E16DST_DST1Constant::kInvalidValue;
      return;
    }
    integral_sum += dat[cell]-baseline;
    if((dat[cell]-baseline)<(dat[peakx]-baseline)*0.1&&peakcheck==false&&cell>peakx){//get falltime
      if(fallcount>1){
	std::cout<<"FalltimeSearch is failed."<<std::endl;
	continue;
      }
      *falltime = cell;
      fallcount += 1;
      if(fallcount>1){
	peakcheck=true;
      }
    }//get falltime
  }//cell loop
  *integral = integral_sum/50./E16ANA_LGConstant::kTimeScale;//[pC]
    //std::cout<<"integral:"<<integral<<std::endl;

}

int E16ANA_LGBasic::LGWFPeakSearch(double* dat, double* xpos, double* ypos){

  TH1F *h = new TH1F("h","h",kTPeakSearchRegion,0,kTPeakSearchRegion);
  TSpectrum* s = new TSpectrum(20);//max_npeaks

  int na=0;
  for(int cell=kTPeakSearchStart; cell<kTPeakSearchEnd; cell++){//peak search
    h->Fill(na,(int)dat[cell]);
    na++;
  }//peak search

  int npeaks = s->Search(h, 3, "new", 0.2);

  for(int i=0; i<20; i++){
    xpos[i] = s->GetPositionX()[i];
    ypos[i] = s->GetPositionY()[i];
  }

  delete h;
  delete s;

  /*
  for(int i=0;i<E16ANA_LGConstant::kTimingSearchRegion;i++){//timing search
    int cell = *peakx - i;
    double peakhalf = *peak/2.;
    if(cell<0||cell>E16DST_Constant::NSamplesLG){
      *timing=E16DST_DST1Constant::kInvalidValue;
      break;
    }
    if(dat[cell]>*peak){
      *timing=E16DST_DST1Constant::kInvalidValue;
      break;
    }
    if(!(cell==*peakx)&&dat[cell]<peakhalf){
      *timing=(peakhalf-dat[cell])*(1./E16ANA_LGConstant::kTimeScale)/(dat[cell+1]-dat[cell])+cell;
      if(cell==(*peakx-1)){//remove the event like spike noise
	*timing=-10000;
      }
      break;
    }
    }//timing search
  */

  return npeaks;

}



/*
void E16ANA_LGBasic::MakeMap(){


        //drs4assign
        E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();
	FILE* fp_ip_pp = calib.CalibFileOpenText("LG-drs4assign", calib.CurrentRunID() );
	if ( fp_ip_pp==NULL ) {
		std::cout<<"[Error] pp map file is not found !"<<std::endl;
		exit(1);
	}
	std::vector<E16ANA_LGBasic::ip_pp> ip_pp_map;
	while( feof(fp_ip_pp)==0 ){
	  E16ANA_LGBasic::ip_pp ip_pp;
	  fscanf(fp_ip_pp, "%d %d %d %d", &(ip_pp.IP), &(ip_pp.PP), &(ip_pp.VTH_TYPE), &(ip_pp.WF_TYPE) );
	  ip_pp_map.push_back(ip_pp);
	//std::cout<<(ip_pp.IP)<<" "<<(ip_pp.PP)<<" "<<(ip_pp.VTH_TYPE)<<" "<<(ip_pp.WF_TYPE)<<std::endl;
	}        	
	fclose(fp_ip_pp);
	//drs4assign


	//timeoffset
	FILE* fp_ip_time = calib.CalibFileOpenText("LG-timeoffset", calib.CurrentRunID() );
        if ( fp_ip_time==NULL ) {
                std::cout<<"[Error] timing map file is not found !"<<std::endl;
                exit(1);
        }
	int ip;
	double time;
	double wfmean;
	while( feof(fp_ip_time)==0 ){
	  fscanf(fp_ip_time, "%d %f %f", &ip, &wfmean, &time);
	  //ifs_ip_time>>ip>>wfmean>>time;
	  auto ip_time_vector = std::find_if(std::begin(ip_pp_map),std::end(ip_pp_map),[ip](const E16ANA_LGBasic::ip_pp& val){
	      return (val.IP==ip);
	    });
	  if(!(ip_time_vector==ip_pp_map.end())){
	    (ip_time_vector->TIME)	=  time;	
	  }
	}
	fclose(fp_ip_time);
	//timeoffset


	//channelmap
#if 0
        FILE* fp_ch_pp = calib.CalibFileOpenText("LG-channelmap", calib.CurrentRunID() );
	if ( fp_ch_pp==NULL ) {
		std::cout<<"[Error] ch map file is not found !"<<std::endl;
		exit(1);
	}

	fstream fout;
	fout.open(file_binary(), ios::binary | ios::out);

	while( feof(fp_ch_pp)==0 ){
	  ch_pp ch_pp;
          fscanf(fp_ch_pp, "%s %d %d %d %d %d %d %d %d", &(ch_pp.LorR), &(ch_pp.DEG), &(ch_pp.BLID), &(ch_pp.MODULE), &(ch_pp.BLOCK), &(ch_pp.PP), &(ch_pp.DRS4CH), &(ch_pp.TRIGID), &(ch_pp.HVCH) );
        int pp = ch_pp.PP;	
	auto ip_pp_vector = std::find_if(std::begin(ip_pp_map),std::end(ip_pp_map),[pp](const E16ANA_LGBasic::ip_pp& val){
		return (val.PP==pp);
			});

	if(!(ip_pp_vector==ip_pp_map.end())){
	ch_pp.VTH_TYPE = ip_pp_vector->VTH_TYPE;
	ch_pp.WF_TYPE = ip_pp_vector->WF_TYPE;
	ch_pp.IP = ip_pp_vector->IP;
	ch_pp.TIME = ip_pp_vector->TIME;
	fout.write((char*)&ch_pp, sizeof(ch_pp));
	}
	}
	fout.close();
	fclose(fp_ch_pp);

#else

        FILE* fp_ch_pp = calib.CalibFileOpenText("LG-channelmap", calib.CurrentRunID() );
	if ( fp_ch_pp==NULL ) {
		std::cout<<"[Error] ch map file is not found !"<<std::endl;
		exit(1);
	}

	//fstream fout;
	//fout.open(file_binary(), ios::binary | ios::out);

	while( feof(fp_ch_pp)==0 ){
	  ch_pp ch_pp;
          fscanf(fp_ch_pp, "%s %d %d %d %d %d %d %d %d", &(ch_pp.LorR), &(ch_pp.DEG), &(ch_pp.BLID), &(ch_pp.MODULE), &(ch_pp.BLOCK), &(ch_pp.PP), &(ch_pp.DRS4CH), &(ch_pp.TRIGID), &(ch_pp.HVCH) );
        int pp = ch_pp.PP;	
	auto ip_pp_vector = std::find_if(std::begin(ip_pp_map),std::end(ip_pp_map),[pp](const E16ANA_LGBasic::ip_pp& val){
		return (val.PP==pp);
			});

	if(!(ip_pp_vector==ip_pp_map.end())){
	ch_pp.VTH_TYPE = ip_pp_vector->VTH_TYPE;
	ch_pp.WF_TYPE = ip_pp_vector->WF_TYPE;
	ch_pp.IP = ip_pp_vector->IP;
	ch_pp.TIME = ip_pp_vector->TIME;
	//fout.write((char*)&ch_pp, sizeof(ch_pp));
	}
	}
	//fout.close();
	fclose(fp_ch_pp);

#endif
}
*/




/*ash ver
void E16ANA_LGBasic::MakeMap(){

	//channelmap

	//read calib_files old ver
	std::ifstream ifs_ip_pp(file_drs4assign());
	if (!ifs_ip_pp) {
		std::cout<<"[Error] pp map file is not found !"<<std::endl;
		exit(1);
	}
	std::vector<E16ANA_LGBasic::ip_pp> ip_pp_map;
        	
	while(!ifs_ip_pp.eof()){
	E16ANA_LGBasic::ip_pp ip_pp;
	ifs_ip_pp>>ip_pp.IP>>ip_pp.PP>>ip_pp.VTH_TYPE>>ip_pp.WF_TYPE;
        ip_pp_map.push_back(ip_pp);
	//std::cout<<"making..."<<ip_pp.IP<<std::endl;
	}

	//std::ifstream ifs_ch_pp("/e16/u/ashikaga/work/run0b/operation/map/channelmap/ch_pp_20200522_run0.txt");
	std::ifstream ifs_ch_pp(file_channelmap());
	if (!ifs_ch_pp) {
		std::cout<<"[Error] ch map file is not found !"<<std::endl;
		exit(1);
	}

	//std::ifstream ifs_ip_time("/e16/u/ashikaga/work/run0b/operation/map/timeoffset/timeoffset_20201219_tagtime829.txt");
	std::ifstream ifs_ip_time(file_timeoffset());
        if (!ifs_ip_time) {
                std::cout<<"[Error] timing map file is not found !"<<std::endl;
                exit(1);
        }

	int ip;
	double time;
	double wfmean;
	while(!ifs_ip_time.eof()){
		ifs_ip_time>>ip>>wfmean>>time;
		//cout<<ip <<" "<< wfmean<<" "<<time<<endl;
		auto ip_time_vector = std::find_if(std::begin(ip_pp_map),std::end(ip_pp_map),[ip](const E16ANA_LGBasic::ip_pp& val){
		return (val.IP==ip);
		});
	 if(!(ip_time_vector==ip_pp_map.end())){
		(ip_time_vector->TIME)	=  time;	
		}
	}

	fstream fout;
	//fout.open("/e16/u/ashikaga/work/run0b/operation/map/binary/map.dat", ios::binary | ios::out);
	fout.open(file_binary(), ios::binary | ios::out);

	while(!ifs_ch_pp.eof()){
	ch_pp ch_pp;
	ifs_ch_pp>>ch_pp.LorR>>ch_pp.DEG>>ch_pp.BLID>>ch_pp.MODULE>>ch_pp.BLOCK>>ch_pp.PP>>ch_pp.DRS4CH>>ch_pp.TRIGID>>ch_pp.HVCH;
        int pp = ch_pp.PP;	
	auto ip_pp_vector = std::find_if(std::begin(ip_pp_map),std::end(ip_pp_map),[pp](const E16ANA_LGBasic::ip_pp& val){
		return (val.PP==pp);
			});

	if(!(ip_pp_vector==ip_pp_map.end())){
	ch_pp.VTH_TYPE = ip_pp_vector->VTH_TYPE;
	ch_pp.WF_TYPE = ip_pp_vector->WF_TYPE;
	ch_pp.IP = ip_pp_vector->IP;
	ch_pp.TIME = ip_pp_vector->TIME;
	fout.write((char*)&ch_pp, sizeof(ch_pp));
	}
	}
	fout.close();
}

void E16ANA_LGBasic::SetMap(){
	unordered_map<string, ch_pp*> mapdata;

	fstream fmap;
	fmap.open(file_binary(), ios::binary | ios::in);

	while(!fmap.eof()){
	ch_pp spec;
	fmap.read((char*)&spec, sizeof(spec));
	std::string key = std::to_string(spec.MODULE)+std::to_string(spec.BLOCK);	
	//ipmap[key] = spec.IP;
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
	(* this->lgdatamap)[key] =  specpoint;
	(* this->lgdatamap_ip)[key_ip] =  specpoint;
	//delete specpoint;
	}

	}
*/	

//string channelmap_path = "/e16/u/nakasuga/E16/DST1/E16DST1/lg_calibfiles/ch_pp_20200522_run0.txt";
//string drs4assign_path = "/e16/u/nakasuga/E16/DST1/E16DST1/lg_calibfiles/pp_map_20210214_run0b.txt";
//string drs4assign_path_run0a = "/e16/u/nakasuga/E16/DST1/E16DST1/lg_calibfiles/pp_map_20200522_run0.txt";
//string timeoffset_path = "/e16/u/nakasuga/E16/DST1/E16DST1/lg_calibfiles/timeoffset_20210220_tagtime3132.txt";
//string binary_path = "/e16/u/nakasuga/E16/DST1/E16DST1/lg_calibfiles/map.dat";
//auto lg_calib_file_path = static_cast<std::string>(LGCalibFilePath);
//string channelmap_path       = lg_calib_file_path + "/ch_pp_20200522_run0.txt";
//string drs4assign_path       = lg_calib_file_path + "/pp_map_20210214_run0b.txt";
//string drs4assign_path_run0a = lg_calib_file_path + "/pp_map_20200522_run0.txt";
//string timeoffset_path       = lg_calib_file_path + "/timeoffset_20210220_tagtime3132.txt";
//string binary_path           = lg_calib_file_path + "/map.dat";


//string channelmap_path = "/e16/u/nakasuga/E16/DST1/E16DST1/lg_calibfiles/ch_pp_20200522_run0.txt";
//string drs4assign_path = "/e16/u/nakasuga/E16/DST1/E16DST1/lg_calibfiles/pp_map_20210214_run0b.txt";
//string drs4assign_path = "/e16/u/nakasuga/E16/DST1/E16DST1/E16ANA_CalibDB/calib_database/LG/drs4assign/210818/LG-drs4assign-run39999-210818.txt";
//string drs4assign_path_run0a = "/e16/u/nakasuga/E16/DST1/E16DST1/lg_calibfiles/pp_map_20200522_run0.txt";
//string timeoffset_path = "/e16/u/nakasuga/E16/DST1/E16DST1/lg_calibfiles/timeoffset_20210220_tagtime3132.txt";
	//string binary_path = "/e16/u/nakasuga/E16/DST1/E16DST1/lg_calibfiles/map.dat";
/*
string E16ANA_LGBasic::file_channelmap(){
	return channelmap_path;
}

string E16ANA_LGBasic::file_drs4assign(){
	return drs4assign_path;
}

string E16ANA_LGBasic::file_drs4assign_run0a(){
	return drs4assign_path_run0a;
}

string E16ANA_LGBasic::file_timeoffset(){
        return timeoffset_path;
}

string E16ANA_LGBasic::file_binary(){
	return binary_path;
}
*/
