#ifndef E16DAQ_SRSATCAChannelMap_h
#define E16DAQ_SRSATCAChannelMap_h

#include <map>
#include <sstream>
#include <fstream>
#include <string>

class SRSATCAChannelMap {
public:
   enum { GTR, HBD, Unknown };
   SRSATCAChannelMap(const std::string &filename)
   {
      std::ifstream ifs(filename);
      if (ifs.fail()) {
         std::cerr << "SRSATCAChannelMap : failed to open file: " << filename << std::endl;
         std::exit(1);
      }
      while (!ifs.eof()) {
         std::string buf;
         std::getline(ifs, buf);
         if (buf[0] == '#' || buf.empty()) {
            continue;
         }
         std::istringstream iss(buf);
         std::string ip_address, detector_name;
         int mezzanine_id;
         iss >> ip_address >> detector_name >> mezzanine_id;
         if (!ip_address.empty()) {
            channel_map[ip_address].second = mezzanine_id;
            if (detector_name == "GTR") {
               channel_map[ip_address].first = GTR;
            } else if (detector_name == "HBD") {
               channel_map[ip_address].first = HBD;
            } else {
               channel_map[ip_address].first = Unknown;
               channel_map[ip_address].second = -10000;
            }
         }
      }
   };
   ~SRSATCAChannelMap(){};
   std::pair<int, int> GetDetectorTypeAndBoardID(const std::string &board_ip)
   {
      if (channel_map.find(board_ip) == channel_map.end()) {
         return std::pair<int, int>(Unknown, -10000);
      }
      return channel_map[board_ip];
   };
   std::vector<std::string> GetBoardIPList()
   {
      std::vector<std::string> ret;
      for (auto &ip : channel_map) {
         ret.push_back(ip.first);
      }
      return ret;
   }

private:
   std::map<std::string, std::pair<int, int>> channel_map;
};

#endif
