#include "E16DST_GTRConnection.hh"

#include <iostream>
#include <fstream>
#include <map>
using namespace std;

E16DST_APVPinAssign::E16DST_APVPinAssign(const std::string &apv_file)
{
   apv_to_ex.resize(n_apv_channels, "EX1");
   apv_to_exch.resize(n_apv_channels, -1);
   OpenApvFile(apv_file);
}

E16DST_GTRPinAssign::E16DST_GTRPinAssign(const std::string &gtr_file)
{
   OpenGTRFile(gtr_file);
}

#if 0
filenames["apv_pin"] = "geometry/apv_pin.dat";
filenames["gtr1_pin"] = "geometry/gtr1_pin.dat";
filenames["gtr2_pin"] = "geometry/gtr2_pin.dat";
filenames["gtr3_pin"] = "geometry/gtr3_pin.dat";

#endif
E16DST_GTRConnection::E16DST_GTRConnection(const map<string, string> &filenames)
{
   apv_pin_assign = std::make_unique<E16DST_APVPinAssign>(filenames.at("apv_pin"));
   // layer id is 1 origin
   gtr_pin_assign[1] = std::make_unique<E16DST_GTRPinAssign>(filenames.at("gtr1_pin"));
   gtr_pin_assign[2] = std::make_unique<E16DST_GTRPinAssign>(filenames.at("gtr2_pin"));
   gtr_pin_assign[3] = std::make_unique<E16DST_GTRPinAssign>(filenames.at("gtr3_pin"));

   for (int i = 0; i < n_mezz; i++) {
      ex_to_connector[i].resize(n_chips);
      ex_to_layerid[i].resize(n_chips);
   }
   srs_to_moduleid.resize(n_mezz);
   for (int i = 0; i < n_mezz; i++) {
      srs_to_moduleid[i].resize(n_chips / 2, -1);
   }
   OpenGTRConnectionFile(filenames.at("connectionA"), apv_name_to_connectorA, apv_name_to_layeridA);
   OpenGTRConnectionFile(filenames.at("connectionB"), apv_name_to_connectorB, apv_name_to_layeridB);
   OpenSRSConnectionFile(filenames.at("srs"));
   for (int i = 0; i < n_mezz; i++) {
      for (int j = 0; j < n_chips; j++) {
         int module_id = srs_to_moduleid[i][j / 2];
         int isA = E16DST_GTRConnection::GTRsegmentA[module_id % 100];
         std::string apv_name = chip_to_apv[i][j];
         // std::cout << i << " " << j << " " << apv_name << " " << isA << std::endl;
         if (apv_name == "") {
            continue;
         }
         if (isA) {
            if (j % 2 == 0) {
               ex_to_connector[i][j]["EX1"] = apv_name_to_connectorA[apv_name + "EX1"];
               ex_to_layerid[i][j]["EX1"] = apv_name_to_layeridA[apv_name + "EX1"];
               ex_to_connector[i][j]["EX2"] = apv_name_to_connectorA[apv_name + "EX2"];
               ex_to_layerid[i][j]["EX2"] = apv_name_to_layeridA[apv_name + "EX2"];
               ex_to_connector[i][j]["EX3"] = apv_name_to_connectorA[apv_name + "EX3"];
               ex_to_layerid[i][j]["EX3"] = apv_name_to_layeridA[apv_name + "EX3"];
            } else {
               ex_to_connector[i][j]["EX1"] = apv_name_to_connectorA[apv_name + "EX4"];
               ex_to_layerid[i][j]["EX1"] = apv_name_to_layeridA[apv_name + "EX4"];
               ex_to_connector[i][j]["EX2"] = apv_name_to_connectorA[apv_name + "EX5"];
               ex_to_layerid[i][j]["EX2"] = apv_name_to_layeridA[apv_name + "EX5"];
               ex_to_connector[i][j]["EX3"] = apv_name_to_connectorA[apv_name + "EX6"];
               ex_to_layerid[i][j]["EX3"] = apv_name_to_layeridA[apv_name + "EX6"];
            }
         } else {
            if (j % 2 == 0) {
               ex_to_connector[i][j]["EX1"] = apv_name_to_connectorB[apv_name + "EX1"];
               ex_to_layerid[i][j]["EX1"] = apv_name_to_layeridB[apv_name + "EX1"];
               ex_to_connector[i][j]["EX2"] = apv_name_to_connectorB[apv_name + "EX2"];
               ex_to_layerid[i][j]["EX2"] = apv_name_to_layeridB[apv_name + "EX2"];
               ex_to_connector[i][j]["EX3"] = apv_name_to_connectorB[apv_name + "EX3"];
               ex_to_layerid[i][j]["EX3"] = apv_name_to_layeridB[apv_name + "EX3"];
            } else {
               ex_to_connector[i][j]["EX1"] = apv_name_to_connectorB[apv_name + "EX4"];
               ex_to_layerid[i][j]["EX1"] = apv_name_to_layeridB[apv_name + "EX4"];
               ex_to_connector[i][j]["EX2"] = apv_name_to_connectorB[apv_name + "EX5"];
               ex_to_layerid[i][j]["EX2"] = apv_name_to_layeridB[apv_name + "EX5"];
               ex_to_connector[i][j]["EX3"] = apv_name_to_connectorB[apv_name + "EX6"];
               ex_to_layerid[i][j]["EX3"] = apv_name_to_layeridB[apv_name + "EX6"];
            }
         }
         // std::cout << " EX1:" << ex_to_connector[i][j]["EX1"]
         //           << " EX2:" << ex_to_connector[i][j]["EX2"]
         //           << " EX3:" << ex_to_connector[i][j]["EX3"]
         //           << std::endl;
      }
   }
#if 0	
	int gtrisA = E16DST_GTRConnection::GTRsegmentA[gtrmoduleID%100 ];	
	if(gtrisA){
	OpenGTRConnectionFile(filenames["connectionA"]);
	}
	else{
	OpenGTRConnectionFile(filenames["connectionB"]);
	}
#endif
}
const int E16DST_GTRConnection::GTRsegmentA[11] = {
   // B-A-B-A-B, A, B-A-B-A-B
   0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0};

E16DST_GTRPinAssign::~E16DST_GTRPinAssign() {}

E16DST_APVPinAssign::~E16DST_APVPinAssign() {}

E16DST_GTRConnection::~E16DST_GTRConnection() {}

void E16DST_APVPinAssign::OpenApvFile(const std::string &fname)
{
   std::ifstream ifs(fname);

   // cout << "fnameOEPNAPVFILE = " << fname << endl;
   if (ifs.fail()) {
      std::cerr << "E16DST_GTRPinAssign::OpenApvFile() : file open fail, file_name = " << fname << std::endl;
      exit(1);
      // return;
   }
   while (1) {
      int apv_ch;
      int con_ch;
      std::string ex_name;
      ifs >> apv_ch >> ex_name >> con_ch;
      // std::cout << apv_ch << ex_name << con_ch << std::endl;
      if (ifs.eof())
         break;
      if (apv_ch >= n_apv_channels)
         continue;
      apv_to_ex[apv_ch] = ex_name;
      apv_to_exch[apv_ch] = con_ch;
   }
   return;
}

void E16DST_GTRPinAssign::OpenGTRFile(const std::string &fname)
{
   std::ifstream ifs(fname);
   if (ifs.fail()) {
      std::cerr << "E16DST_GTRPinAssign::OpenGTRFile() : file open fail, file_name = " << fname << std::endl;
      exit(1);
      // return;
   }
   while (1) {
      int strip_id;
      int con_ch;
      std::string con_name;
      ifs >> con_name >> con_ch >> strip_id;
      // std::cout << con_name << con_ch << strip_id << std::endl;
      if (ifs.eof())
         break;
      if (connector_to_strip.find(con_name) == connector_to_strip.end()) {
         connector_to_strip[con_name].resize(n_ex_channels, -1);
      }
      connector_to_strip[con_name][con_ch] = strip_id;
   }
   return;
}

void E16DST_GTRConnection::OpenSRSConnectionFile(const std::string &fname)
{
   std::ifstream ifs(fname);
   if (ifs.fail()) {
      std::cerr << "E16DST_GTRConnection::OpenSRSConnectionFile() : file open fail, file_name = " << fname << std::endl;
      exit(1);
      // return;
   }
   int i = 0;
   while (1) {
      i++;
      // cerr << "i = " << i << endl;
      int mezz_id;
      int srs_ch;
      int module_id;
      std::string apv_name;
      ifs >> mezz_id >> srs_ch >> module_id >> apv_name;
      if (ifs.eof())
         break;
      // cerr << mezz_id << " " << srs_ch << " " << module_id << " " << apv_name << endl;
      // apv_to_srs[mezz_id][apv_name] = srs_ch;
      chip_to_apv[mezz_id][srs_ch * 2] = apv_name;
      chip_to_apv[mezz_id][srs_ch * 2 + 1] = apv_name;
      // cerr << "apv to srs finished" << endl;
      srs_to_moduleid[mezz_id][srs_ch] = module_id;
      // cerr << "srs to module id finished " << endl;
   }
   return;
}

/*
void E16DST_GTRConnection::OpenSRSFile(std::string fname){
   std::ifstream ifs(fname.c_str());
   if(ifs.fail()){
      return;
   }
   while(1){
      int srs_ch;
      //int chip_id;
      std::string apv_name;
      ifs >> srs_ch >> apv_name;
      if(ifs.eof()) break;
      apv_to_srs[apv_name] = srs_ch;
   }
   return;
}
*/

void E16DST_GTRConnection::OpenGTRConnectionFile(const std::string &fname,
                                                 std::unordered_map<std::string, std::string> &apv_name_to_connector,
                                                 std::unordered_map<std::string, int> &apv_name_to_layerid)
{ // originally OpenConnectionFile
   std::ifstream ifs(fname);
   if (ifs.fail()) {
      std::cerr << "E16DST_GTRPinAssign::OpenGTRConnectionFile() : file open fail, file_name = " << fname << std::endl;
      exit(1);
      // return;
   }
   std::vector<std::string> apv_name_v;
   std::vector<int> gtr_id_v;
   std::vector<int> length_v;
   std::vector<std::string> ex_name_v;
   std::vector<std::string> con_name_v;
   while (1) {
      std::string apv_name;
      int gtr_id;
      int length;
      std::string ex_name;
      std::string con_name;
      ifs >> apv_name >> ex_name >> gtr_id >> con_name >> length;
      apv_name_v.push_back(apv_name);
      gtr_id_v.push_back(gtr_id);
      ex_name_v.push_back(ex_name);
      con_name_v.push_back(con_name);
      length_v.push_back(length);
      if (ifs.eof())
         break;
      apv_name += ex_name;
      apv_name_to_connector[apv_name] = con_name;
      apv_name_to_layerid[apv_name] = gtr_id;
      // :std::cout << apv_name << " " << gtr_id << " " << con_name << std::endl;
   }
#ifdef PRINT_EX
   // 100 X
   int start = 0;
   int end = 6;
   // std::cout << "GTR100-X" << std::endl;
   std::cout << std::endl;
   for (int i = start; i < end; i++) {
      std::cout << con_name_v[i] << "\t";
   }
   std::cout << std::endl;
   for (int i = start; i < end; i++) {
      std::cout << length_v[i] << "\t";
   }
   std::cout << std::endl;
   for (int i = start; i < end; i++) {
      std::cout << apv_name_v[i] << "-" << ex_name_v[i] << "\t";
   }
   std::cout << std::endl;
   // 100 YR
   start = 6;
   end = 9;
   // std::cout << "GTR100-YR" << std::endl;
   std::cout << std::endl;
   for (int i = start; i < end; i++) {
      std::cout << con_name_v[i] << "\t";
   }
   std::cout << std::endl;
   for (int i = start; i < end; i++) {
      std::cout << length_v[i] << "\t";
   }
   std::cout << std::endl;
   for (int i = start; i < end; i++) {
      std::cout << apv_name_v[i] << "-" << ex_name_v[i] << "\t";
   }
   std::cout << std::endl;
   // 100 YL
   // std::cout << "GTR100-YL" << std::endl;
   std::cout << std::endl;
   start = 9;
   end = 12;
   for (int i = start; i < end; i++) {
      std::cout << con_name_v[i] << "\t";
   }
   std::cout << std::endl;
   for (int i = start; i < end; i++) {
      std::cout << length_v[i] << "\t";
   }
   std::cout << std::endl;
   for (int i = start; i < end; i++) {
      std::cout << apv_name_v[i] << "-" << ex_name_v[i] << "\t";
   }
   std::cout << std::endl;
   // 200 X
   // std::cout << "GTR200-X" << std::endl;
   std::cout << std::endl;
   start = 12;
   end = 24;
   for (int i = start; i < end; i++) {
      std::cout << con_name_v[i] << "\t";
   }
   std::cout << std::endl;
   for (int i = start; i < end; i++) {
      std::cout << length_v[i] << "\t";
   }
   std::cout << std::endl;
   for (int i = start; i < end; i++) {
      std::cout << apv_name_v[i] << "-" << ex_name_v[i] << "\t";
   }
   std::cout << std::endl;
   // 200 Y
   // std::cout << "GTR200-Y" << std::endl;
   std::cout << std::endl;
   start = 24;
   end = 29;
   for (int i = start; i < end; i++) {
      std::cout << con_name_v[i] << "\t";
   }
   std::cout << std::endl;
   for (int i = start; i < end; i++) {
      std::cout << length_v[i] << "\t";
   }
   std::cout << std::endl;
   for (int i = start; i < end; i++) {
      std::cout << apv_name_v[i] << "-" << ex_name_v[i] << "\t";
   }
   std::cout << std::endl;
   // 300 X
   // std::cout << "GTR300-X" << std::endl;
   std::cout << std::endl;
   start = 29;
   end = 29 + 18;
   for (int i = start; i < end; i++) {
      std::cout << con_name_v[i] << "\t";
   }
   std::cout << std::endl;
   for (int i = start; i < end; i++) {
      std::cout << length_v[i] << "\t";
   }
   std::cout << std::endl;
   for (int i = start; i < end; i++) {
      std::cout << apv_name_v[i] << "-" << ex_name_v[i] << "\t";
   }
   std::cout << std::endl;
   // 300 Y
   // std::cout << "GTR300-Y" << std::endl;
   std::cout << std::endl;
   start = 29 + 18;
   end = 29 + 18 + 7;
   for (int i = start; i < end; i++) {
      std::cout << con_name_v[i] << "\t";
   }
   std::cout << std::endl;
   for (int i = start; i < end; i++) {
      std::cout << length_v[i] << "\t";
   }
   std::cout << std::endl;
   for (int i = start; i < end; i++) {
      std::cout << apv_name_v[i] << "-" << ex_name_v[i] << "\t";
   }
   std::cout << std::endl;
   std::cout << std::endl;
#endif
   return;
}

int E16DST_GTRPinAssign::GetStripID(const std::string &con_name, int ex_ch) const
{
   if (con_name == "") {
      return -1;
   }
   if (connector_to_strip.find(con_name) == connector_to_strip.end()) {
      return -1;
   }
   return connector_to_strip.at(con_name)[ex_ch];
}

#if 0 
int E16DST_GTRConnection::GetStripID(int mezz_id, int chip_id, int apv_ch){
	if(chip_id >= n_chips || apv_ch >= n_apv_channels){
		return -1;
	}
	std::string ex_name = apv_pin_assign->GetEXName(apv_ch);
	//std::cout << ex_name << std::endl;
	int ex_ch = apv_pin_assign->GetEXChannel(apv_ch);
	//std::cout << ex_name << " " << ex_ch << std::endl;
	if(ex_to_connector[chip_id].find(ex_name) == ex_to_connector[chip_id].end() || ex_ch >= n_ex_channels){
		return -1;
	}
	std::string con_name = ex_to_connector[chip_id][ex_name];
	//std::cout << ex_name << " " << ex_ch << " " << con_name << std::endl;
	int layerid = GetLayerID(0,chip_id, apv_ch);
	//std::cout << ex_name << " " << ex_ch << " " << con_name << " " << layerid << std::endl;
	return gtr_pin_assign[layerid-1]->GetStripID(con_name, ex_ch);//from GTRPinAssign
}

int E16DST_GTRConnection::GetLayerID(int mezz_ip, int chip_id, int apv_ch){
	if(chip_id >= n_chips || apv_ch >= n_apv_channels){
		return -1;
	}
	1std::string ex_name = apv_pin_assign->GetEXName(apv_ch);
	int ex_ch = apv_pin_assign->GetEXChannel(apv_ch);
	if(ex_to_layerid[chip_id].find(ex_name) == ex_to_layerid[chip_id].end() || ex_ch >= n_ex_channels){
		return -1;
	}
	return ex_to_layerid[chip_id][ex_name];
}

#endif
/////////
int E16DST_GTRConnection::GetModuleID(int mezz_id, int chip_id, int apv_ch) const
{
   if (mezz_id >= n_mezz || chip_id >= n_chips) {
      return -1;
   }
   int temp_srs_ch = chip_id / 2;

   //	cout << "temp_srs_ch = " << temp_srs_ch << endl;
   //	cout << "srs_to_moduleid = " <<  srs_to_moduleid[mezz_id][temp_srs_ch];
   return srs_to_moduleid.at(mezz_id)[temp_srs_ch];
}

IDset_GTRhit E16DST_GTRConnection::GetIDset(int mezz_id, int chip_id, int apv_ch) const
{
   IDset_GTRhit idset(-1);

   if (mezz_id >= n_mezz || chip_id >= n_chips || apv_ch >= n_apv_channels) {
      return idset;
   }
   idset.moduleID = GetModuleID(mezz_id, chip_id, apv_ch);
   std::string ex_name = apv_pin_assign->GetEXName(apv_ch);
   int ex_ch = apv_pin_assign->GetEXChannel(apv_ch);
   // std::cout << mezz_id << " " << chip_id << " " << apv_ch << " -> " << ex_name << " " << ex_ch << std::endl;
   if (ex_to_layerid[mezz_id][chip_id].find(ex_name) == ex_to_layerid[mezz_id][chip_id].end() ||
       ex_ch >= n_ex_channels) {
      return idset; // error
   }
   idset.layerID = ex_to_layerid[mezz_id][chip_id].at(ex_name);

   if (ex_to_connector[mezz_id][chip_id].find(ex_name) == ex_to_connector[mezz_id][chip_id].end() ||
       ex_ch >= n_ex_channels) {
      return idset;
   }
   std::string con_name = ex_to_connector[mezz_id][chip_id].at(ex_name);
   idset.stripID = gtr_pin_assign[idset.layerID]->GetStripID(con_name, ex_ch); // from GTRPinAssign;
   // std::cout << "    -> " << con_name << " " << idset.layerID << " " << idset.stripID << std::endl;

   idset.layerID--;
   return idset;
}

// GETmoduleid-> judge a,b  -> ex_to layer id used for layer id ->
