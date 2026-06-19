#ifndef E16DST_DST0_HH
#define E16DST_DST0_HH

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <vector>

#include "E16DST_Constant.hh"
#include "E16DST_File.hh"

// dst0 file will be directly written from these classes.
// In dst0, byte boundary of 2 (byte) is used.
#pragma pack(2)

class E16DST_DST0Hit {
public:
   E16DST_DST0Hit(){}
   ~E16DST_DST0Hit(){}
   void SetIDs(uint16_t _moduleID, uint16_t _channelID);
   uint16_t ModuleID() { return moduleID; };
   uint16_t ChannelID() { return channelID; };

protected:
   uint16_t moduleID;  // 0-10, 100-110, 200-210 for lower/middle/upper deck
   uint16_t channelID; // stripID(SSD, GTR) or padID(HBD) or blockID(LG)
};


//////  BELOW ARE FOR OLD SSD.
/////
class E16DST_DST0SSDHit : public E16DST_DST0Hit { // Silicon Strip Detector
public:
   E16DST_DST0SSDHit(){}
   ~E16DST_DST0SSDHit(){}
   void SetTDC(uint32_t _tdc) { tdc = _tdc; };
   void SetWaveform(int16_t _waveform[]);
   uint32_t TDC() { return tdc; };
   uint16_t StripID() { return channelID; };
   int16_t *Waveform() { return waveform; };

private:
   uint32_t tdc;
   int16_t waveform[E16DST_Constant::NSamplesSSD];
};
///// ABOVE ARE FOR OLD SSD.

// ASIC 0-15
class E16DST_DST0STSHit : public E16DST_DST0Hit { // STS. Silicon Tracking System
public:
  E16DST_DST0STSHit(){}
  ~E16DST_DST0STSHit(){}
  void SetTDC(uint16_t _tdc) { tdc = _tdc; };
  void SetADC(uint16_t _adc) { adc = _adc;  };
  void SetElink(uint16_t _elink) { elink = _elink; };
  void SetPN(uint16_t _pn ) { pn = _pn; };
  void SetIDs(uint16_t _moduleID, uint16_t _channelID, uint16_t _elink) {
    E16DST_DST0Hit::SetIDs(_moduleID,_channelID);
    elink = _elink;
  };
  void SetGeriTimestamp(uint64_t _geriTimestamp) { geriTimestamp = _geriTimestamp; }
  uint64_t GeriTimestamp() { return geriTimestamp; }

  uint16_t TDC() { return tdc; };
  bool     TDCinvalid() const { return ( tdc == 0xffff );}
  uint16_t TDCL10b() { return tdc&0b1111111111; }
  uint16_t ADC() { return adc; };
  bool     ADCinvalid() const { return (adc == 0xffff); }
  uint16_t ChannelID() { return channelID; };
  uint16_t Elink() { return elink; };
  uint16_t PN() { return pn; };

  // TO PRESERVE BACKWARD COMPATIBILITY.
  uint16_t EventMissed() { return (eventMissed&0xff) ; }   
  void SetEventMissed(uint16_t _em) {
    _em = _em & 0xff;
    eventMissed = eventMissed&0xff00;
    eventMissed += (_em&0xff); }
  void SetE16sts(int _e16sts) {
    _e16sts = _e16sts & 0xff;
    eventMissed = (eventMissed & 0xffff);
    eventMissed += (_e16sts<<8);
  }
  uint16_t E16sts() { return ( (eventMissed & 0xff00)>>8 ); }
  
private:
  uint16_t tdc{0xffff};    // 14bit tdc
  uint16_t adc{0xffff};    // 5bit adc
  uint16_t elink{0xffff};  // elink
  uint16_t pn{0xffff};     // p0n1
  uint16_t eventMissed{0}; // eventMissed
  uint64_t geriTimestamp{0xffffffffffffffffL};
};


class E16DST_DST0STSGlobal : public E16DST_DST0Hit { // STS. Silicon Tracking System
public:
  E16DST_DST0STSGlobal(){}
  ~E16DST_DST0STSGlobal(){}
  //void set_l1_trgtype(uint16_t _l1_trgtype) { l1_trgtype = _l1_trgtype; }
  //uint16_t get_l1_trgtype() { return 0;l1_trgtype; }
  void set_l1_trgtype(uint16_t _l1_trgtype) { ; }
  uint16_t get_l1_trgtype() { return 0; }
  void set_e16sts(uint16_t _e16sts) { e16sts = _e16sts; }
  uint16_t get_e16sts() { return e16sts; }
  void set_trgtype(uint16_t _trgtype) { trgtype = _trgtype; }
  uint16_t get_trgtype() { return trgtype; }
  void set_gbt(uint16_t _gbt) { gbt = _gbt; }
  uint16_t get_gbt() { return gbt; }
  void set_port(uint16_t _port) { port = _port; }
  uint16_t get_port() { return port; }
  void set_trg_num_emu2geri(uint16_t _trg_num_emu2geri) { trg_num_emu2geri = _trg_num_emu2geri; }
  uint16_t get_trg_num_emu2geri() { return trg_num_emu2geri; }
  void set_trgtyp_rcv_count(uint32_t _trgtyp_rcv_count) { trgtyp_rcv_count = _trgtyp_rcv_count;}
  uint32_t get_trgtyp_rcv_count() { return trgtyp_rcv_count; }
  void set_trgdata_rcv_count(uint32_t _trgdata_rcv_count) { trgdata_rcv_count = _trgdata_rcv_count; }
  uint32_t get_trgdata_rcv_count() { return trgdata_rcv_count; }
  void set_trglocal_count(uint32_t _trglocal_count) { trglocal_count = _trglocal_count; }
  uint32_t get_trglocal_count() { return trglocal_count; }
  void set_l1_geritimestamp(uint64_t _l1_geritimestamp) { l1_geritimestamp = _l1_geritimestamp; }
  uint64_t get_l1_geritimestamp() { return l1_geritimestamp; }
  void set_ut3timestamp(uint64_t _ut3timestamp){ ut3timestamp = _ut3timestamp; }
  uint64_t get_ut3timestamp() { return ut3timestamp; }
  void set_ut3spill(uint32_t _ut3spill) { ut3spill = _ut3spill; }
  uint32_t get_ut3spill() { return ut3spill;}
  void set_ut3event(uint32_t _ut3event) { ut3event = _ut3event; }
  uint64_t get_emu_timestamp() { return emu_timestamp; }
  void set_emu_timestamp(uint64_t _emu_timestamp) { emu_timestamp = _emu_timestamp; }
private:
  //uint16_t l1_trgtype;
  uint16_t e16sts;
  uint16_t trgtype;
  uint16_t gbt;
  uint16_t port;
  uint16_t trg_num_emu2geri;
  uint32_t trgtyp_rcv_count;
  uint32_t trgdata_rcv_count;
  uint32_t trglocal_count;
  uint64_t l1_geritimestamp;
  uint64_t ut3timestamp;
  uint32_t ut3spill;
  uint32_t ut3event;
  uint64_t emu_timestamp;
  
};


class E16DST_DST0GTRHit : public E16DST_DST0Hit { // Gem TRacker
public:
   E16DST_DST0GTRHit(){}
   ~E16DST_DST0GTRHit(){}

   void SetTimeStamp(uint32_t _timeStamp) { timeStamp = _timeStamp; };
   void SetTDC(uint32_t _tdc) { tdc = _tdc; };
   void SetLayerID(uint16_t _layerID) { layerID = _layerID; };
   void SetWaveform(int16_t _waveform[]);
   void SetWaveform(const std::vector<int16_t> &_waveform);
   uint16_t StripID() { return channelID; };
   uint32_t TimeStamp() { return timeStamp; };
   uint32_t TDC() { return tdc; };
   uint16_t LayerID() { return layerID; };
   int16_t *Waveform() { return waveform; };

private:
   uint32_t timeStamp; // local time stamp added by SRS-ATCA
   uint32_t tdc;       // time interval between trigger timing and first clock from trigger timing
   uint16_t layerID;   // 0, 1, 2=outer
   int16_t waveform[E16DST_Constant::NSamplesGTR];
};

class E16DST_DST0HBDHit : public E16DST_DST0Hit { // Hadron Blind Detector
public:
   E16DST_DST0HBDHit(){}
   ~E16DST_DST0HBDHit(){}

   void SetTimeStamp(uint32_t _timeStamp) { timeStamp = _timeStamp; };
   void SetTDC(uint32_t _tdc) { tdc = _tdc; };
   void SetWaveform(int16_t _waveform[]);
   void SetWaveform(const std::vector<int16_t> &_waveform);
   uint16_t PadID() { return channelID; };
   uint32_t TimeStamp() { return timeStamp; };
   uint32_t TDC() { return tdc; };
   int16_t *Waveform() { return waveform; };

private:
   uint32_t timeStamp;
   uint32_t tdc;
   int16_t waveform[E16DST_Constant::NSamplesHBD];
};

class E16DST_DST0LGHit : public E16DST_DST0Hit { // Lead Grass calorimeter
public:
   E16DST_DST0LGHit(){}
   ~E16DST_DST0LGHit(){}

   // void SetTimeStamp(uint64_t _timeStamp) { timeStamp = _timeStamp; };
   void SetTIC(uint32_t _triggerIntervalCounter) { triggerIntervalCounter = _triggerIntervalCounter; };
   void SetWSR(uint16_t _writeShiftRegister) { writeShiftRegister = _writeShiftRegister; };
   void SetStopCell(uint16_t _stopCell) { stopCell = _stopCell; };
   void SetQDC(int32_t _integralByFPGA) { integralByFPGA = _integralByFPGA; };
   void SetBaseLine(int16_t _baseLine) { baseLine = _baseLine; };
   void SetWaveform(int16_t _waveform[]);
   void SetWaveform(const std::vector<int16_t> &_waveform);

   uint16_t BlockID() { return channelID; };
   // uint64_t TimeStamp() { return timeStamp; };
   uint32_t TIC() { return triggerIntervalCounter; };
   uint16_t WSR() { return writeShiftRegister; };
   uint16_t StopCell() { return stopCell; };
   int32_t QDC() { return integralByFPGA; };
   int16_t BaseLine() { return baseLine; };
   int16_t *Waveform() { return waveform; };

private:
   // uint64_t timeStamp;
   uint32_t triggerIntervalCounter; // TIC
   uint16_t writeShiftRegister;     // WSR
   uint16_t stopCell;
   int32_t integralByFPGA; // QDC
   int16_t baseLine;
   int16_t waveform[E16DST_Constant::NSamplesLG];
};

class E16DST_DST0CTHit : public E16DST_DST0Hit { // Charged particle Timing counter
public:
   E16DST_DST0CTHit(){}
   ~E16DST_DST0CTHit(){}

   // void SetTimeStamp(uint64_t _timeStamp) { timeStamp = _timeStamp; };
   void SetTIC(uint32_t _triggerIntervalCounter) { triggerIntervalCounter = _triggerIntervalCounter; };
   void SetWSR(uint16_t _writeShiftRegister) { writeShiftRegister = _writeShiftRegister; };
   void SetStopCell(uint16_t _stopCell) { stopCell = _stopCell; };
   void SetQDC(int32_t _integralByFPGA) { integralByFPGA = _integralByFPGA; };
   void SetBaseLine(int16_t _baseLine) { baseLine = _baseLine; };
   void SetWaveform(int16_t _waveform[]);
   void SetWaveform(const std::vector<int16_t> &_waveform);

   // uint64_t TimeStamp() { return timeStamp; };
   uint32_t TIC() { return triggerIntervalCounter; };
   uint16_t WSR() { return writeShiftRegister; };
   uint16_t StopCell() { return stopCell; };
   int32_t QDC() { return integralByFPGA; };
   int16_t BaseLine() { return baseLine; };
   int16_t *Waveform() { return waveform; };

private:
   // uint64_t timeStamp;
   uint32_t triggerIntervalCounter; // TIC
   uint16_t writeShiftRegister;     // WSR
   uint16_t stopCell;
   int32_t integralByFPGA; // QDC
   int16_t baseLine;
   int16_t waveform[E16DST_Constant::NSamplesCT];
};

// MRPC
class E16DST_DST0MRPCHit : public E16DST_DST0Hit { // Multi-gap Resistive Plate Chamber
public:
   E16DST_DST0MRPCHit(){}
   ~E16DST_DST0MRPCHit(){}
   void SetTDC(uint32_t _tdc_leading, uint32_t _tdc_trailing) {
      tdc_leading = _tdc_leading;
      tdc_trailing = _tdc_trailing;
   };
   uint32_t TDCLeading(){ return tdc_leading; };
   uint32_t TDCTrailing(){ return tdc_trailing; };

private:
   uint32_t tdc_leading;
   uint32_t tdc_trailing;
};

class E16DST_DST0ESCHit : public E16DST_DST0Hit { // Event Start Counter
public:
   E16DST_DST0ESCHit(){}
   ~E16DST_DST0ESCHit(){}
   void SetTDC(uint32_t _tdc_leading, uint32_t _tdc_trailing) {
      tdc_leading = _tdc_leading;
      tdc_trailing = _tdc_trailing;
   };
   uint32_t TDCLeading(){ return tdc_leading; };
   uint32_t TDCTrailing(){ return tdc_trailing; };

private:
   uint32_t tdc_leading;
   uint32_t tdc_trailing;
};

class E16DST_DST0TSCHit : public E16DST_DST0Hit { // Track Start Counter
public:
   E16DST_DST0TSCHit(){}
   ~E16DST_DST0TSCHit(){}
   void SetTDC(uint32_t _tdc_leading, uint32_t _tdc_trailing) {
      tdc_leading = _tdc_leading;
      tdc_trailing = _tdc_trailing;
   };
   uint32_t TDCLeading(){ return tdc_leading; };
   uint32_t TDCTrailing(){ return tdc_trailing; };

private:
   uint32_t tdc_leading;
   uint32_t tdc_trailing;
};
// MRPC

class E16DST_DST0TriggerHit : public E16DST_DST0Hit {
public:
   E16DST_DST0TriggerHit(){}
   ~E16DST_DST0TriggerHit(){}
   uint32_t Time() { return time; };
   void SetTime(uint32_t _time) { time = _time; };
   int16_t HitNumber() { return hit_number; };
   void SetHitNumber(int16_t _hit_number) { hit_number = _hit_number; };

private:
   uint32_t time; // coarseTime + fineTime
   int16_t hit_number;
};

class E16DST_DST0ScalerHit : public E16DST_DST0Hit {
public:
   E16DST_DST0ScalerHit(){}
   ~E16DST_DST0ScalerHit(){}
   uint32_t Scaler() { return scaler; };
   uint32_t ShortScaler() { return shortScaler; };
   uint32_t ShortScalerTime() { return shortScalerTime; };
   void SetScaler(uint32_t _scaler) { scaler = _scaler; };
   void SetShortScaler(uint32_t _shortScaler) { shortScaler = _shortScaler; };
   void SetShortScalerTime(uint32_t _shortScalerTime) { shortScalerTime = _shortScalerTime; };

private:
   uint32_t scaler;          // is reset at spill start (end?)
   uint32_t shortScaler;     // is reset every 1 ms, short-term scaler?, periodically cleared scaler?
   uint32_t shortScalerTime; // time interval between trigger timing and the latest reset timing
   // single_rate = shortScaler / shortScalerTime * some_factor
};

class E16DST_DST0DetectorHeader {
public:
   E16DST_DST0DetectorHeader(){}
   ~E16DST_DST0DetectorHeader(){}
   void SetValidFlag(uint32_t _validFlag) { validFlag = _validFlag; };
   uint32_t ValidFlag() { return validFlag; };

protected:
   uint32_t validFlag;
   int32_t nHits;
};

template <class T>
class E16DST_DST0Detector : public E16DST_DST0DetectorHeader {
public:
   using value_type = T;
   E16DST_DST0Detector(){}
   ~E16DST_DST0Detector(){}
   template <class... Args> void EmplaceBack(Args&&... args) { hits.emplace_back(std::forward<decltype(args)>(args)...); }
#if __cplusplus >= 201703L
   template <class... Args> T& EmplaceBack(Args&&... args) { return emplace_back(std::forward<decltype(args)>(args)...); }
#endif
   void Resize(int n) { hits.resize(n); };
   void Reserve(int n) { hits.reserve(n); };
   void PushBack() { hits.push_back(T()); };
   void PushBack(const T &hit) { hits.push_back(hit); };
   void Clear()
   {
      validFlag = 0;
      hits.clear();
   };
   T &Back() { return hits.back(); };
   T &Hit(int i) { return hits[i]; };
   int NumberOfHits() { return hits.size(); };
   int Write(E16DST_File *fp);
   int Read(E16DST_File *fp);
   void Append(E16DST_DST0Detector<T> &rhs);
   int GetEventSize() const { return sizeof(E16DST_DST0DetectorHeader) + sizeof(T)*hits.size(); }

private:
   std::vector<T> hits;
};

template <class T>
class E16DST_DST0Scaler : public E16DST_DST0DetectorHeader {
public:
   E16DST_DST0Scaler(){}
   ~E16DST_DST0Scaler(){}
   void Resize(int n) { hits.resize(n); };
   void Reserve(int n) { hits.reserve(n); };
   void PushBack() { hits.push_back(T()); };
   void PushBack(const T &hit) { hits.push_back(hit); };
   void Clear()
   {
      validFlag = 0;
      hits.clear();
   };
   T &Back() { return hits.back(); };
   T &Hit(int i) { return hits[i]; };
   int NumberOfHits() { return hits.size(); };
   int Write(E16DST_File *fp);
   int Read(E16DST_File *fp);
   void Append(E16DST_DST0Scaler<T> &rhs);
   int GetEventSize() const { return sizeof(E16DST_DST0DetectorHeader) + sizeof(coarseTime) + sizeof(reserved) +  sizeof(T)*hits.size(); }

   uint16_t CoarseTime() { return coarseTime; };
   // uint16_t BusyTime() { return busyTime; };
   void SetCoarseTime(uint16_t _coarseTime) { coarseTime = _coarseTime; };
   // void SetBusyTime(uint16_t _busyTime) { busyTime = _busyTime; };

private:
   uint16_t coarseTime;
   uint16_t reserved;
   // uint16_t busyTime; // busy time of merger?
   std::vector<T> hits;
};

struct E16DST_DST0UT3Hitmap {
   uint8_t GTR[E16DST_Constant::NModules][E16DST_Constant::NTriggerChannelsGTR];
   uint8_t HBD[E16DST_Constant::NModules][E16DST_Constant::NTriggerChannelsHBD];
   uint8_t LG[E16DST_Constant::NModules][E16DST_Constant::NTriggerChannelsLG];
};

class E16DST_DST0UT3Track {
public:
   E16DST_DST0UT3Track(){}
   E16DST_DST0UT3Track(uint32_t _channelID, int64_t _time)
   {
      channelID = _channelID;
      time = _time;
   };
   ~E16DST_DST0UT3Track(){}
   uint32_t ChannelID() { return channelID; };
   uint32_t Time() { return time; };
   void Set(uint32_t _channelID, int64_t _time)
   {
      channelID = _channelID;
      time = _time;
   };

private:
   uint32_t channelID;
   int64_t time;
};

class E16DST_DST0UT3 {
public:
   E16DST_DST0UT3(){}
   ~E16DST_DST0UT3(){}
   int GetEventSize() const { return sizeof(E16DST_DST0UT3); }
   int Write(E16DST_File *fp);
   int Read(E16DST_File *fp);
   void Copy(E16DST_DST0UT3 &rhs);
   void Clear() { memset(reinterpret_cast<char *>(this), 0, sizeof(E16DST_DST0UT3)); };

   uint32_t ValidFlag() { return validFlag; };
   uint16_t TriggerFlag() { return triggerFlag; };
   uint16_t TriggerType() { return triggerType; };
   uint32_t TriggerTime() { return triggerTime; };
   uint8_t *NIMFlag() { return nimFlag; };
   uint8_t NIMFlag(int i) { return nimFlag[i]; };
   uint32_t *NIMScaler() { return nimScaler; };
   uint32_t NIMScaler(int i) { return nimScaler[i]; };
   uint32_t *TriggerAccept() { return triggerAccept; };
   uint32_t TriggerAccept(int i) { return triggerAccept[i]; };
   uint32_t *PhysicsTriggerRequest() { return physicsTriggerRequest; };
   uint32_t PhysicsTriggerRequest(int i) { return physicsTriggerRequest[i]; };
   uint32_t *PhysicsTriggerAccept() { return physicsTriggerAccept; };
   uint32_t PhysicsTriggerAccept(int i) { return physicsTriggerAccept[i]; };
   
   int32_t NumberOfHits() { return nHits; };
   E16DST_DST0TriggerHit &Hit(int i) { return hit[i]; };
   int32_t NumberOfTracks() { return nTracks; };
   E16DST_DST0TriggerHit &Track(int i) { return track[i]; };
   E16DST_DST0UT3Hitmap &Hitmap() { return hitmap; };
   E16DST_DST0UT3Hitmap &HitmapOld() { return hitmapOld; };

   void SetTriggerInformation(uint16_t _triggerFlag, uint16_t _triggerType, uint32_t _triggerTime)
   {
      triggerFlag = _triggerFlag;
      triggerType = _triggerType;
      triggerTime = _triggerTime;
   };
   void SetValidFlag(uint32_t _validFlag) { validFlag = _validFlag; };
   void SetNIMFlag(uint8_t _nimFlag[]) { memcpy(nimFlag, _nimFlag, sizeof(nimFlag)); };
   void SetNIMScaler(uint32_t _nimScaler[]) { memcpy(nimScaler, _nimScaler, sizeof(nimScaler)); };
   void SetTriggerAccept(uint32_t _triggerAccept[]) { memcpy(triggerAccept, _triggerAccept, sizeof(triggerAccept)); };
   void SetPhysicsTriggerRequest(uint32_t _physicsTriggerRequest[]) { memcpy(physicsTriggerRequest, _physicsTriggerRequest, sizeof(physicsTriggerRequest)); };
   void SetPhysicsTriggerAccept(uint32_t _physicsTriggerAccept[]) { memcpy(physicsTriggerAccept, _physicsTriggerAccept, sizeof(physicsTriggerAccept)); };
   void SetNumberOfHits(int32_t _nHits) { nHits = _nHits; };
   void SetNumberOfTracks(int32_t _nTracks) { nTracks = _nTracks; };

private:
   uint32_t validFlag;
   uint16_t triggerFlag; // valid in PhysicsEvent
   uint16_t triggerType; // valid in PhysicsEvent
   uint32_t triggerTime; // valid in PhysicsEvent
   uint8_t nimFlag[E16DST_Constant::NNIMFlagsUT3]; // valid in PhysicsEvent
   uint32_t nimScaler[E16DST_Constant::NNIMScalersUT3]; // valid in PhysicsEvent and ScalerEvent
   uint32_t triggerAccept[E16DST_Constant::NTriggerTypes]; // valid in ScalerEvent
   uint32_t physicsTriggerRequest[E16DST_Constant::NPhysicsTriggerTypes]; // valid in ScalerEvent
   uint32_t physicsTriggerAccept[E16DST_Constant::NPhysicsTriggerTypes]; // valid in ScalerEvent
   int32_t nHits; // valid in PhysicsEvent
   int32_t nTracks; // valid in PhysicsEvent
   E16DST_DST0TriggerHit hit[E16DST_Constant::NTracksMaxUT3]; // valid in PhysicsEvent
   E16DST_DST0TriggerHit track[E16DST_Constant::NTracksMaxUT3]; // valid in PhysicsEvent
   E16DST_DST0UT3Hitmap hitmap; // valid in PhysicsEvent
   E16DST_DST0UT3Hitmap hitmapOld; // valid in PhysicsEvent
};

class E16DST_DST0EventHeader {
public:
   class TriggerData {
   public:
      TriggerData() : validFlag(0){};
      ~TriggerData(){}
      void Clear() { validFlag = 0; };
      uint32_t validFlag;
      uint32_t mrgBusyTime[E16DST_Constant::NMergers];
      uint32_t ut3BusyTime;
      uint32_t totalBusyTime;
   };
   E16DST_DST0EventHeader()
      : runNumber(0xffffffff), spillID(0xffffffff), eventIDInSpill(0xffffffff), eventID(0xffffffff),
        unixTime(0xffffffff), timeStamp(0xffffffffffffffff), timeStampInSpill(0xffffffffffffffff),
        triggerData(){};
   ~E16DST_DST0EventHeader(){}
   void Clear()
   {
      runNumber = 0xffffffff;
      spillID = 0xffffffff;
      eventIDInSpill = 0xffffffff;
      eventID = 0xffffffff;
      unixTime = 0xffffffff;
      timeStamp = 0xffffffffffffffff;
      timeStampInSpill = 0xffffffffffffffff;
   };
   bool Append(E16DST_DST0EventHeader &rhs);
   bool IsConsistentWith(E16DST_DST0EventHeader &rhs);

   uint32_t runNumber; // reserved
   uint32_t spillID; // 1-origin
   uint32_t eventIDInSpill; // 1-origin (SpillStartEvent has 1, PhysicsEvent has 2, 3, 4, ...)
   uint32_t eventID; // 1-origin
   uint32_t unixTime; // reserved
   uint64_t timeStamp; // time stamp distributed by UT3
   uint64_t timeStampInSpill; // time from spill start trigger
   TriggerData triggerData; // this should be located at the last of this class
};

class E16DST_DST0EventType {
public:
   enum {
      Physics,    // Main trigger
      Scaler,     // Monitor trigger
      SpillStart, // Spill trigger
      SpillEnd,   // Spill trigger (with different trigger type)
      NEventTypes //
   };
   E16DST_DST0EventType();
   E16DST_DST0EventType(uint16_t _version) : version(_version){};
   ~E16DST_DST0EventType(){}
   void SetEventType(uint16_t type) { eventType = type; };
   uint16_t Version() { return version; };
   uint16_t EventType() { return eventType; };

private:
   uint16_t version;
   uint16_t eventType;
};

class E16DST_DST0Event {
public:
   E16DST_DST0Event();
   virtual ~E16DST_DST0Event();
#if __cplusplus < 201703L
   int GetEventSizeImpl() const { return 0; }
   template <class Head, class... Tail>  int GetEventSizeImpl(const Head& head, const Tail&... tail) const { return head.GetEventSize() + GetEventSizeImpl(tail...); }
#else 
   template <class... Args> int GetEventSizeImpl(const Args&... args) const { return (... + args.GetEventSize()); }
#endif
   virtual int GetEventSize() const { return sizeof(E16DST_DST0EventHeader); }
   virtual int Write(E16DST_File *fp);
   virtual int Read(E16DST_File *fp);
   virtual bool Append(E16DST_DST0Event *_another_event) = 0;
   virtual uint16_t EventType() = 0;
   virtual void Clear() { header.Clear(); };

   uint32_t RunNumber() { return header.runNumber; };
   uint32_t SpillID() { return header.spillID; };
   uint32_t EventIDInSpill() { return header.eventIDInSpill; };
   uint32_t EventID() { return header.eventID; };
   uint32_t UnixTime() { return header.unixTime; };
   uint64_t TimeStamp() { return header.timeStamp; };
   uint64_t TimeStampInSpill() { return header.timeStampInSpill; };
   uint32_t MergerBusyTime(int i) { return header.triggerData.mrgBusyTime[i]; };
   uint32_t UT3BusyTime() { return header.triggerData.ut3BusyTime; };
   uint32_t TotalBusyTime() { return header.triggerData.totalBusyTime; };
   void SetRunNumber(uint32_t _runNumber) { header.runNumber = _runNumber; };
   void SetSpillID(uint32_t _spillID) { header.spillID = _spillID; };
   void SetEventIDInSpill(uint32_t _eventIDInSpill) { header.eventIDInSpill = _eventIDInSpill; };
   void SetEventID(uint32_t _eventID) { header.eventID = _eventID; };
   void SetUnixTime(uint32_t _unixTime) { header.unixTime = _unixTime; };
   void SetTimeStamp(uint64_t _timeStamp) { header.timeStamp = _timeStamp; };
   void SetTimeStampInSpill(uint64_t _timeStampInSpill) { header.timeStampInSpill = _timeStampInSpill; };
   void SetMrgBusyTime(uint32_t _MrgBusyTime[])
   {
      memcpy(header.triggerData.mrgBusyTime, _MrgBusyTime, sizeof(header.triggerData.mrgBusyTime));
   };
   void SetUt3BusyTime(uint32_t _Ut3BusyTime) { header.triggerData.ut3BusyTime = _Ut3BusyTime; };
   void SetTotalBusyTime(uint32_t _TotalBusyTime) { header.triggerData.totalBusyTime = _TotalBusyTime; };
   void SetTriggerDataValidFlag(uint32_t _validFlag) { header.triggerData.validFlag = _validFlag; };
   void HeaderCopy(E16DST_DST0Event *another) { this->header = another->header; };

   int Serialize(char *buffer, int buffer_size);

protected:
   E16DST_DST0EventHeader header;
};

class E16DST_DST0PhysicsEvent : public E16DST_DST0Event {
public:
   E16DST_DST0PhysicsEvent();
   ~E16DST_DST0PhysicsEvent();
  int GetEventSize() const override { return E16DST_DST0Event::GetEventSize() + GetEventSizeImpl(sts, ssd, gtr, hbd, lg, ct, mrpc, esc, tsc, trigger_gtr, trigger_hbd, trigger_lg, scaler_gtr, scaler_hbd, scaler_hbd, scaler_lg, ut3); } 

   int Write(E16DST_File *fp);
   int Read(E16DST_File *fp);
   void Clear();
   bool Append(E16DST_DST0Event *_another_event);
   uint16_t EventType() { return E16DST_DST0EventType::Physics; };

   E16DST_DST0Detector<E16DST_DST0STSHit> &STS() { return sts; };
   E16DST_DST0Detector<E16DST_DST0STSGlobal> &STSG() { return stsg; };
   E16DST_DST0Detector<E16DST_DST0SSDHit> &SSD() { return ssd; };
   E16DST_DST0Detector<E16DST_DST0GTRHit> &GTR() { return gtr; };
   E16DST_DST0Detector<E16DST_DST0HBDHit> &HBD() { return hbd; };
   E16DST_DST0Detector<E16DST_DST0LGHit> &LG() { return lg; };
   E16DST_DST0Detector<E16DST_DST0CTHit> &CT() { return ct; };
   E16DST_DST0Detector<E16DST_DST0MRPCHit> &MRPC() { return mrpc; };
   E16DST_DST0Detector<E16DST_DST0ESCHit> &ESC() { return esc; };
   E16DST_DST0Detector<E16DST_DST0TSCHit> &TSC() { return tsc; };
   E16DST_DST0Detector<E16DST_DST0TriggerHit> &TriggerGTR() { return trigger_gtr; };
   E16DST_DST0Detector<E16DST_DST0TriggerHit> &TriggerHBD() { return trigger_hbd; };
   E16DST_DST0Detector<E16DST_DST0TriggerHit> &TriggerLG() { return trigger_lg; };
   E16DST_DST0Detector<E16DST_DST0TriggerHit> &TriggerCT() { return trigger_ct; };
   E16DST_DST0Scaler<E16DST_DST0ScalerHit> &ScalerGTR() { return scaler_gtr; };
   E16DST_DST0Scaler<E16DST_DST0ScalerHit> &ScalerHBD() { return scaler_hbd; };
   E16DST_DST0Scaler<E16DST_DST0ScalerHit> &ScalerLG() { return scaler_lg; };
   E16DST_DST0Scaler<E16DST_DST0ScalerHit> &ScalerCT() { return scaler_ct; };
   E16DST_DST0UT3 &UT3() { return ut3; };

private:
   E16DST_DST0Detector<E16DST_DST0STSHit> sts;
   E16DST_DST0Detector<E16DST_DST0STSGlobal> stsg;
   E16DST_DST0Detector<E16DST_DST0SSDHit> ssd;
   E16DST_DST0Detector<E16DST_DST0GTRHit> gtr;
   E16DST_DST0Detector<E16DST_DST0HBDHit> hbd;
   E16DST_DST0Detector<E16DST_DST0LGHit> lg;
   E16DST_DST0Detector<E16DST_DST0CTHit> ct;
   E16DST_DST0Detector<E16DST_DST0MRPCHit> mrpc;
   E16DST_DST0Detector<E16DST_DST0ESCHit> esc;
   E16DST_DST0Detector<E16DST_DST0TSCHit> tsc;
   E16DST_DST0Detector<E16DST_DST0TriggerHit> trigger_gtr;
   E16DST_DST0Detector<E16DST_DST0TriggerHit> trigger_hbd;
   E16DST_DST0Detector<E16DST_DST0TriggerHit> trigger_lg;
   E16DST_DST0Detector<E16DST_DST0TriggerHit> trigger_ct;
   E16DST_DST0Scaler<E16DST_DST0ScalerHit> scaler_gtr;
   E16DST_DST0Scaler<E16DST_DST0ScalerHit> scaler_hbd;
   E16DST_DST0Scaler<E16DST_DST0ScalerHit> scaler_lg;
   E16DST_DST0Scaler<E16DST_DST0ScalerHit> scaler_ct;
   E16DST_DST0UT3 ut3;
};

class E16DST_DST0ScalerEvent : public E16DST_DST0Event {
public:
   E16DST_DST0ScalerEvent();
   ~E16DST_DST0ScalerEvent();
   int GetEventSize() const override { return E16DST_DST0Event::GetEventSize() + GetEventSizeImpl(scaler_gtr, scaler_hbd, scaler_lg, ut3); } 
   int Write(E16DST_File *fp);
   int Read(E16DST_File *fp);
   void Clear();
   bool Append(E16DST_DST0Event *_another_event);
   uint16_t EventType() { return E16DST_DST0EventType::Scaler; };

   E16DST_DST0Scaler<E16DST_DST0ScalerHit> &ScalerGTR() { return scaler_gtr; };
   E16DST_DST0Scaler<E16DST_DST0ScalerHit> &ScalerHBD() { return scaler_hbd; };
   E16DST_DST0Scaler<E16DST_DST0ScalerHit> &ScalerLG() { return scaler_lg; };
   E16DST_DST0Scaler<E16DST_DST0ScalerHit> &ScalerCT() { return scaler_ct; };
   E16DST_DST0UT3 &UT3() { return ut3; };

private:
   E16DST_DST0Scaler<E16DST_DST0ScalerHit> scaler_gtr;
   E16DST_DST0Scaler<E16DST_DST0ScalerHit> scaler_hbd;
   E16DST_DST0Scaler<E16DST_DST0ScalerHit> scaler_lg;
   E16DST_DST0Scaler<E16DST_DST0ScalerHit> scaler_ct;
   E16DST_DST0UT3 ut3;
};

class E16DST_DST0SpillStartEvent : public E16DST_DST0Event {
public:
   E16DST_DST0SpillStartEvent() : 
      nEventsInSpill(0xffffffff),
      shotNumber(0xffffffff)
   {
   };
   virtual ~E16DST_DST0SpillStartEvent(){}
   int GetEventSize() const override { return E16DST_DST0Event::GetEventSize() + sizeof(uint32_t)*2; }
   virtual int Write(E16DST_File *fp);
   virtual int Read(E16DST_File *fp);
   virtual void Clear(){
      nEventsInSpill = 0xffffffff;
      shotNumber = 0xffffffff;
   };
   virtual bool Append(E16DST_DST0Event *_another_event);
   virtual uint16_t EventType() { return E16DST_DST0EventType::SpillStart; };
   void SetNumberOfEventsInSpill(uint32_t _nEventsInSpill) { nEventsInSpill = _nEventsInSpill; };
   void SetShotNumber(uint32_t _shotNumber) { shotNumber = _shotNumber; };
   uint32_t NumberOfEventsInSpill(){ return nEventsInSpill; };
   uint32_t ShotNumber(){ return shotNumber; };
private:
   uint32_t nEventsInSpill; // number of events in spill
   uint32_t shotNumber; // shot number provided by Hadron beam-line group (2020-07-11 reserved region)
};

class E16DST_DST0SpillEndEvent : public E16DST_DST0SpillStartEvent {
public:
   E16DST_DST0SpillEndEvent(){}
   ~E16DST_DST0SpillEndEvent(){}
   //void Clear(){};
   //bool Append(E16DST_DST0Event *_another_event) { return false; };
   uint16_t EventType() { return E16DST_DST0EventType::SpillEnd; };
};

union E16DST_DST0Header {
   int8_t buffer[E16DST_Constant::DST0HeaderSize];
   struct {
      int8_t magic_word[4];
      uint32_t version;
      uint32_t nEventTypes;
      uint32_t nSamplesSSD;
      uint32_t nSamplesGTR;
      uint32_t nSamplesHBD;
      uint32_t nSamplesLG;
      uint32_t nSamplesCT;
      uint32_t startYear;
      uint32_t startMonth;
      uint32_t startDay;
      uint32_t startHour;
      uint32_t startMin;
      uint32_t startSec;
      uint8_t trgVer[4];
   };
   E16DST_DST0Header();
   ~E16DST_DST0Header();
   int Write(E16DST_File *fp);
   int Read(E16DST_File *fp);
   bool Check(); // consistency check between data and program
   void SetStartTime(uint16_t _hour, uint16_t _min, uint16_t _sec);
   void SetStartTime(uint16_t _year, uint8_t _month, uint8_t _day, uint8_t _hour, uint8_t _min, uint8_t _sec);
   void SetTrgVer(uint32_t _trgVer);
};

class E16DST_DST0 {
public:
   enum {
      Version = 6, // should be incremented when a major update is implemented
      WriteMode = 0,
      ReadMode = 1
   };
   enum {
      Auto,
      NonCompressed,
      ZlibGzip,
      ZSTD
   };
   E16DST_DST0();
   ~E16DST_DST0();
   bool Open(std::string file_name, int open_mode, int compress_mode = Auto);
   void Close() { if (file) file->close(); };
   E16DST_DST0Event *Event() { return event; };
   uint16_t EventType() { return eventType.EventType(); };
   int GetEventSize() const { return sizeof(E16DST_DST0EventType) + event->GetEventSize(); }
   void SetEventType(uint16_t type);
   void WriteAnEvent() { WriteAnEvent(file); };
   int ReadAnEvent() { return ReadAnEvent(file); };
   void WriteAnEvent(uint16_t type, E16DST_DST0Event *_event);
   void WriteAnEvent(E16DST_DST0Event *_event) { WriteAnEvent(_event->EventType(), _event); };
   void SetStartTime(uint16_t _hour, uint16_t _min, uint16_t _sec) { header.SetStartTime(_hour, _min, _sec); };
   void SetStartTime(uint16_t _year, uint8_t _month, uint8_t _day, uint8_t _hour, uint8_t _min, uint8_t _sec) {
      header.SetStartTime(_year, _month, _day, _hour, _min, _sec);
   };
   void SetTrgVer(uint32_t _trgVer) { header.SetTrgVer(_trgVer); };

private:
   //int open_mode;
   E16DST_DST0Header header;
   E16DST_DST0EventType eventType;
   E16DST_DST0Event *event;
   E16DST_DST0Event *eventFactory[E16DST_DST0EventType::NEventTypes];
   E16DST_File *file{nullptr};
   void WriteAnEvent(E16DST_File *fp);
   int ReadAnEvent(E16DST_File *fp);
};

#pragma pack() // byte boundary of default values

class E16DST_DST0EventFactory {
public:
   static E16DST_DST0Event* Create(uint16_t event_type);
   static E16DST_DST0Event* Create(char *buffer, int buffer_size);
private:
};

#endif // E16DST_DST0_HH
