#ifndef E16DST_STSCHANNELMAP_HH
#define E16DST_STSCHANNELMAP_HH

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <array>

class STSChannel{
public:
  int e16sts;
  int gbt;
  int gtype;
  int gi;
  int mod;
  int pn;
  int papb;
  STSChannel():e16sts(-1),gbt(-1),gtype(-1),gi(-1),mod(-1),pn(-1),papb(-1){;}
};

class E16DST_STSChannelMap {
private:
  static constexpr int last_e16sts = 2;
  static constexpr int ngbt = 7;
  static constexpr int ng = 2;
  std::array<std::array<std::array<STSChannel,ng>,ngbt>,last_e16sts+1> sts_channel_map; //[e16sts][gbt][ig]
  static constexpr int nasic = 8;
  std::array<std::array<int,nasic>,2> sts_elink_general_map; // [a0b1][elink(0-7)]
  int verbosity{0}; // 1: error 10: debug
  
  void MakeMap(std::string_view sts_gbt_file, std::string_view sts_elink_file);
public:
  E16DST_STSChannelMap(std::string_view sts_gbt_file, std::string_view sts_elink_file);
  ~E16DST_STSChannelMap() = default;

  int Getig(int e16sts,int gbt,int elink) const;
  int GetModule(int e16sts,int gbt, int elink) const;
  int GetPN(int e16sts,int gbt, int elink) const;
  int GetAsic(int e16sts,int gbt, int elink) const;
  int GetAsicSub(int ab,int elink) const;
  int GetVerbosity() const { return verbosity; }
  void SetVerbosity(int _verb) { verbosity = _verb;}
};

#endif // E16DST_STSCHANNELMAP_HH
