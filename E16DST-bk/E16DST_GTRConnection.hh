#ifndef E16DST_GTRPinAssign_h
#define E16DST_GTRPinAssign_h

#include <array>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class E16DST_APVPinAssign {
public:
   // E16DST_APVPinAssign(std::string apv_file, std::string gtr_file, std::string connection_file);
   E16DST_APVPinAssign(const std::string &apv_file);
   ~E16DST_APVPinAssign();
   std::string GetEXName(int ch) { return apv_to_ex[ch]; };
   int GetEXChannel(int ch) { return apv_to_exch[ch]; };
   int GetInputChannel(int apv_ch)
   {
      int exch = apv_to_exch[apv_ch];
      std::string exname = apv_to_ex[apv_ch];
      if (exname == "EX2") {
         exch += n_ex_channels;
      } else if (exname == "EX3") {
         exch += n_ex_channels * 2;
      }
      return exch;
   };

private:
   enum {
      n_chips = 24,
      n_apv_channels = 128,
      // n_ex = 6,
      n_ex_channels = 48
   };
   std::vector<std::string> apv_to_ex; // ApvCh:0-127 -> EX1, EX2, or EX3
   std::vector<int> apv_to_exch;       // ApvCh:0-127 -> ConnCh:0-47
   void OpenApvFile(const std::string &fname);
};

class E16DST_GTRPinAssign {
public:
   // E16DST_GTRPinAssign(std::string apv_file, std::string gtr_file, std::string connection_file);
   E16DST_GTRPinAssign(const std::string &gtr_file);
   ~E16DST_GTRPinAssign();
   int GetStripID(const std::string &conn_name, int ex_ch) const;

private:
   enum {
      n_chips = 24,
      n_apv_channels = 128,
      // n_ex = 6,
      n_ex_channels = 48
   };
   std::unordered_map<std::string, std::vector<int>> connector_to_strip; // ConnName + ConnCh -> StripId
   void OpenGTRFile(const std::string &fname);
};

struct IDset_GTRhit {
   int moduleID;
   int layerID;
   int stripID;
   IDset_GTRhit(int i)
   {
      moduleID = i;
      layerID = i;
      stripID = i;
   }
   IDset_GTRhit() : IDset_GTRhit(-1) {}
};

class E16DST_GTRConnection {
public:
   E16DST_GTRConnection(const std::map<std::string, std::string> &filenames);
   ~E16DST_GTRConnection();
   //	int GetStripID(int mezz_id, int chip_id, int apv_ch);
   //	int GetLayerID(int mezz_id, int chip_id, int apv_ch);
   int GetModuleID(int mezz_id, int chip_id, int apv_ch) const;

   IDset_GTRhit GetIDset(int mezz_id, int chip_id, int apv_ch) const;
   // int GetChannelId(int gtr_id, int strip_id);
   // int GetApvId(int gtr_id, int strip_id);

   static const int GTRsegmentA[11];

private:
   enum {
      n_chips = 24, // changed from 16
      n_mezz = 8,
      n_apv_channels = 128,
      // n_ex = 6,
      n_ex_channels = 48,
   };
   // int apv_to_connector[n_channels];
   std::unordered_map<std::string, std::string> apv_name_to_connectorA;               // ex. b-EX3 -> Y3
   std::unordered_map<std::string, std::string> apv_name_to_connectorB;               // ex. d-EX1 -> X8
   std::unordered_map<std::string, int> apv_name_to_layeridA;                         // ex. b-EX3 -> layer = 0
   std::unordered_map<std::string, int> apv_name_to_layeridB;                         // ex. d-EX1 -> layer = 2
   std::vector<std::unordered_map<std::string, std::string>> ex_to_connector[n_mezz]; // ChipId + EX -> ConnName
   std::vector<std::unordered_map<std::string, int>> ex_to_layerid[n_mezz];           // ChipId + EX -> GTR
   // std::map<std::string, int> apv_to_srs[n_mezz];                            // APV name -> SRS channel
   std::string chip_to_apv[n_mezz][n_chips];
   std::vector<std::vector<int>> srs_to_moduleid; // srs_ch + mezzanineid -> moduleid
   // std::map<int, std::string> moduleid_to_gtrtype;// moduleID -> GTRType

   std::unique_ptr<E16DST_APVPinAssign> apv_pin_assign;
   std::array<std::unique_ptr<E16DST_GTRPinAssign>, 4> gtr_pin_assign;
   //	E16DST_GTRPinAssign *gtr_pin_assignA[3];
   //	E16DST_GTRPinAssign *gtr_pin_assignB[3];

   void OpenSRSConnectionFile(const std::string &fname);
   void OpenGTRTypeFile(const std::string &fname);
   void OpenGTRConnectionFile(const std::string &fname, std::unordered_map<std::string, std::string> &apv_name_to_connector,
                              std::unordered_map<std::string, int> &apv_name_to_layerid);
   // void OpenGTRConnectionFileB(std::string fname);
   void OpenAPVConnectionFile(const std::string &fname); //
};

#endif // E16DST_GTRPinAssign_h
