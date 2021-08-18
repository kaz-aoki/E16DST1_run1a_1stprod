#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "E16ANA_LGBasic.hh"
#include "E16ANA_CalibDBManager.hh"

#include <algorithm>
#include <unordered_map>   

using namespace std;



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
	//channelmap

	/*read calib_files old ver
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
	*/
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

E16ANA_LGBasic::ch_pp* E16ANA_LGBasic::GetSpec(uint16_t module, uint16_t block){
	std::string key = std::to_string(module)+std::to_string(block);
	auto spec = (* this->lgdatamap)[key];
	return spec;  
		}

E16ANA_LGBasic::ch_pp* E16ANA_LGBasic::GetSpec(int ip){
	auto spec = (* this->lgdatamap_ip)[ip];
	return spec;  
		}




//string channelmap_path = "/e16/u/nakasuga/E16/DST1/E16DST1/lg_calibfiles/ch_pp_20200522_run0.txt";
//string drs4assign_path = "/e16/u/nakasuga/E16/DST1/E16DST1/lg_calibfiles/pp_map_20210214_run0b.txt";
//string drs4assign_path = "/e16/u/nakasuga/E16/DST1/E16DST1/E16ANA_CalibDB/calib_database/LG/drs4assign/210818/LG-drs4assign-run39999-210818.txt";
//string drs4assign_path_run0a = "/e16/u/nakasuga/E16/DST1/E16DST1/lg_calibfiles/pp_map_20200522_run0.txt";
//string timeoffset_path = "/e16/u/nakasuga/E16/DST1/E16DST1/lg_calibfiles/timeoffset_20210220_tagtime3132.txt";
string binary_path = "/e16/u/nakasuga/E16/DST1/E16DST1/lg_calibfiles/map.dat";
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
*/
string E16ANA_LGBasic::file_binary(){
	return binary_path;
}

