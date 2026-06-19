#include "E16DST_DST0.hh"
#include <cstring>
#include <iostream>

void E16DST_DST0Hit::SetIDs(uint16_t _moduleID, uint16_t _channelID)
{
   moduleID = _moduleID;
   channelID = _channelID;
}

void E16DST_DST0SSDHit::SetWaveform(int16_t _waveform[])
{
   memcpy(waveform, _waveform, sizeof(waveform));
}

void E16DST_DST0GTRHit::SetWaveform(int16_t _waveform[])
{
   memcpy(waveform, _waveform, sizeof(waveform));
}

void E16DST_DST0GTRHit::SetWaveform(const std::vector<int16_t> &_waveform)
{
   memset(waveform, 0x80, sizeof(waveform));
   int length = std::min(_waveform.size() * sizeof(int16_t), sizeof(waveform));
   memcpy(waveform, _waveform.data(), length);
}

void E16DST_DST0HBDHit::SetWaveform(int16_t _waveform[])
{
   memcpy(waveform, _waveform, sizeof(waveform));
}

void E16DST_DST0HBDHit::SetWaveform(const std::vector<int16_t> &_waveform)
{
   memset(waveform, 0x80, sizeof(waveform));
   int length = std::min(_waveform.size() * sizeof(int16_t), sizeof(waveform));
   memcpy(waveform, _waveform.data(), length);
}

void E16DST_DST0LGHit::SetWaveform(int16_t _waveform[])
{
   memcpy(waveform, _waveform, sizeof(waveform));
}

void E16DST_DST0LGHit::SetWaveform(const std::vector<int16_t> &_waveform)
{
   memset(waveform, 0x80, sizeof(waveform));
   int length = std::min(_waveform.size() * sizeof(int16_t), sizeof(waveform));
   memcpy(waveform, _waveform.data(), length);
}

void E16DST_DST0CTHit::SetWaveform(int16_t _waveform[])
{
   memcpy(waveform, _waveform, sizeof(waveform));
}

void E16DST_DST0CTHit::SetWaveform(const std::vector<int16_t> &_waveform)
{
   memset(waveform, 0x80, sizeof(waveform));
   int length = std::min(_waveform.size() * sizeof(int16_t), sizeof(waveform));
   memcpy(waveform, _waveform.data(), length);
}

template <class T>
int E16DST_DST0Detector<T>::Write(E16DST_File *fp)
{
   nHits = hits.size();
   int write_size = fp->write(reinterpret_cast<char *>(this), sizeof(E16DST_DST0DetectorHeader));
   int length = sizeof(T) * nHits;
   write_size += fp->write(reinterpret_cast<char *>(hits.data()), length);
   return write_size;
}

template <class T>
int E16DST_DST0Detector<T>::Read(E16DST_File *fp)
{
   int read_size = fp->read(reinterpret_cast<char *>(this), sizeof(E16DST_DST0DetectorHeader));
   hits.resize(nHits);
   read_size += fp->read(reinterpret_cast<char *>(hits.data()), sizeof(T) * nHits);
   return read_size;
}

template <class T>
void E16DST_DST0Detector<T>::Append(E16DST_DST0Detector<T> &rhs)
{
   // std::cout << "Append : lhs.nHits = " << NumberOfHits() << ", rhs.nHits = " << rhs.NumberOfHits() << std::endl;
   validFlag = 1;
   // std::copy(rhs.hits.begin(), rhs.hits.end(), std::back_inserter(hits));
   int n = rhs.NumberOfHits();
   for (int i = 0; i < n; i++) {
      hits.push_back(rhs.hits[i]);
   }
   nHits = hits.size();
}

template <class T>
int E16DST_DST0Scaler<T>::Write(E16DST_File *fp)
{
   nHits = hits.size();
   int write_size = fp->write(reinterpret_cast<char *>(this), sizeof(E16DST_DST0DetectorHeader) + sizeof(coarseTime) + sizeof(reserved));
   int length = sizeof(T) * nHits;
   write_size += fp->write(reinterpret_cast<char *>(hits.data()), length);
   return write_size;
}

template <class T>
int E16DST_DST0Scaler<T>::Read(E16DST_File *fp)
{
   int read_size = fp->read(reinterpret_cast<char *>(this), sizeof(E16DST_DST0DetectorHeader) + sizeof(coarseTime) + sizeof(reserved));
   hits.resize(nHits);
   read_size += fp->read(reinterpret_cast<char *>(hits.data()), sizeof(T) * nHits);
   return read_size;
}

template <class T>
void E16DST_DST0Scaler<T>::Append(E16DST_DST0Scaler<T> &rhs)
{
   // std::cout << "Append : lhs.nHits = " << NumberOfHits() << ", rhs.nHits = " << rhs.NumberOfHits() << std::endl;
   if (!validFlag) {
      validFlag = 1;
      coarseTime = rhs.coarseTime;
      reserved = rhs.reserved;
   }
   // std::copy(rhs.hits.begin(), rhs.hits.end(), std::back_inserter(hits));
   int n = rhs.NumberOfHits();
   for (int i = 0; i < n; i++) {
      hits.push_back(rhs.hits[i]);
   }
   nHits = hits.size();
}

int E16DST_DST0UT3::Write(E16DST_File *fp)
{
   return fp->write(reinterpret_cast<char *>(this), sizeof(E16DST_DST0UT3));
}

int E16DST_DST0UT3::Read(E16DST_File *fp)
{
   return fp->read(reinterpret_cast<char *>(this), sizeof(E16DST_DST0UT3));
}

void E16DST_DST0UT3::Copy(E16DST_DST0UT3 &rhs)
{
   memcpy(reinterpret_cast<void *>(this), reinterpret_cast<void *>(&rhs), sizeof(E16DST_DST0UT3));
}

bool E16DST_DST0EventHeader::IsConsistentWith(E16DST_DST0EventHeader &rhs){
   bool is_consistent = true;
   is_consistent &= (spillID == rhs.spillID);
   is_consistent &= (eventID == rhs.eventID);
   is_consistent &= (timeStamp == rhs.timeStamp);
   return is_consistent;
}

bool E16DST_DST0EventHeader::Append(E16DST_DST0EventHeader &rhs)
{
   if (this->IsConsistentWith(rhs)) {
      // simple memery copy
      // memcpy(reinterpret_cast<void *>(this), reinterpret_cast<void *>(&rhs),
      //        sizeof(E16DST_DST0EventHeader) - sizeof(TriggerData));

      // default (invalid) values are 0xffff....
      // Thus, if lhs or rhs has valid values, the valid values are assigned.
      runNumber = runNumber & rhs.runNumber;
      eventIDInSpill = eventIDInSpill & rhs.eventIDInSpill;
      timeStampInSpill = timeStampInSpill & rhs.timeStampInSpill;
      unixTime = unixTime & rhs.unixTime;

      if (rhs.triggerData.validFlag) {
         memcpy(reinterpret_cast<void *>(&triggerData), reinterpret_cast<void *>(&(rhs.triggerData)), sizeof(TriggerData));
      }
      return true;
   }
   return false;
}

E16DST_DST0EventType::E16DST_DST0EventType() : version(E16DST_DST0::Version) {
}

E16DST_DST0Event::E16DST_DST0Event() {}
E16DST_DST0Event::~E16DST_DST0Event() {}

int E16DST_DST0Event::Write(E16DST_File *fp)
{
   return fp->write(reinterpret_cast<char *>(&header), sizeof(E16DST_DST0EventHeader));
}

int E16DST_DST0Event::Read(E16DST_File *fp)
{
   return fp->read(reinterpret_cast<char *>(&header), sizeof(E16DST_DST0EventHeader));
}

int E16DST_DST0Event::Serialize(char *buffer, int buffer_size){
   E16DST_DST0EventType event_type;
   event_type.SetEventType(this->EventType());
   memcpy(buffer, reinterpret_cast<char *>(&event_type), sizeof(E16DST_DST0EventType));
   int data_size = sizeof(E16DST_DST0EventType);
   E16DST_MemoryBuffer fp(buffer + sizeof(E16DST_DST0EventType), buffer_size);
   data_size += this->Write(&fp);
   return data_size;
}

E16DST_DST0PhysicsEvent::E16DST_DST0PhysicsEvent() : E16DST_DST0Event()
{
   Clear();
}
E16DST_DST0PhysicsEvent::~E16DST_DST0PhysicsEvent() {}

void E16DST_DST0PhysicsEvent::Clear()
{
   E16DST_DST0Event::Clear();
   sts.Clear();
   stsg.Clear();
   ssd.Clear();
   gtr.Clear();
   hbd.Clear();
   lg.Clear();
   ct.Clear();
   mrpc.Clear();
   esc.Clear();
   tsc.Clear();
   trigger_gtr.Clear();
   trigger_hbd.Clear();
   trigger_lg.Clear();
   trigger_ct.Clear();
   scaler_gtr.Clear();
   scaler_hbd.Clear();
   scaler_lg.Clear();
   scaler_ct.Clear();
   ut3.Clear();
}

int E16DST_DST0PhysicsEvent::Write(E16DST_File *fp)
{
   int write_size = fp->write(reinterpret_cast<char *>(&header), sizeof(E16DST_DST0EventHeader));
   write_size += sts.Write(fp);
   write_size += stsg.Write(fp);
   write_size += ssd.Write(fp);
   write_size += gtr.Write(fp);
   write_size += hbd.Write(fp);
   write_size += lg.Write(fp);
   write_size += ct.Write(fp);
   write_size += mrpc.Write(fp);
   write_size += esc.Write(fp);
   write_size += tsc.Write(fp);
   write_size += trigger_gtr.Write(fp);
   write_size += trigger_hbd.Write(fp);
   write_size += trigger_lg.Write(fp);
   write_size += trigger_ct.Write(fp);
   write_size += scaler_gtr.Write(fp);
   write_size += scaler_hbd.Write(fp);
   write_size += scaler_lg.Write(fp);
   write_size += scaler_ct.Write(fp);
   write_size += ut3.Write(fp);
   return write_size;
}

int E16DST_DST0PhysicsEvent::Read(E16DST_File *fp)
{
   this->Clear();
   int read_size = fp->read(reinterpret_cast<char *>(&header), sizeof(E16DST_DST0EventHeader));
   read_size += sts.Read(fp);
   read_size += stsg.Read(fp);
   read_size += ssd.Read(fp);
   read_size += gtr.Read(fp);
   read_size += hbd.Read(fp);
   read_size += lg.Read(fp);
   read_size += ct.Read(fp);
   read_size += mrpc.Read(fp);
   read_size += esc.Read(fp);
   read_size += tsc.Read(fp);
   read_size += trigger_gtr.Read(fp);
   read_size += trigger_hbd.Read(fp);
   read_size += trigger_lg.Read(fp);
   read_size += trigger_ct.Read(fp);
   read_size += scaler_gtr.Read(fp);
   read_size += scaler_hbd.Read(fp);
   read_size += scaler_lg.Read(fp);
   read_size += scaler_ct.Read(fp);
   read_size += ut3.Read(fp);
   return read_size;
}

bool E16DST_DST0PhysicsEvent::Append(E16DST_DST0Event *_another_event)
{
   E16DST_DST0PhysicsEvent *another_event = dynamic_cast<E16DST_DST0PhysicsEvent *>(_another_event);
   if (another_event == nullptr) {
      return false;
   }
   if (!header.Append(another_event->header)) {
      std::cerr << "Header mismatch is detected. EventID = " << this->EventID() << std::endl;
      std::cerr << "TimeStamp = " << this->TimeStamp() << ", " << another_event->TimeStamp() << std::endl;
      std::cerr << "SpillID = " << this->SpillID() << ", " << another_event->SpillID() << std::endl;
      std::cerr << "RunNumber = " << this->RunNumber() << ", " << another_event->RunNumber() << std::endl;
      std::cerr << "EventIDInSpill = " << this->EventIDInSpill() << ", " << another_event->EventIDInSpill()
                << std::endl;
      std::cerr << "UnixTime = " << this->UnixTime() << ", " << another_event->UnixTime() << std::endl;
      return false;
   }
   sts.Append(another_event->sts);
   stsg.Append(another_event->stsg);
   ssd.Append(another_event->ssd);
   gtr.Append(another_event->gtr);
   hbd.Append(another_event->hbd);
   lg.Append(another_event->lg);
   ct.Append(another_event->ct);
   mrpc.Append(another_event->mrpc);
   esc.Append(another_event->esc);
   tsc.Append(another_event->tsc);
   trigger_gtr.Append(another_event->trigger_gtr);
   trigger_hbd.Append(another_event->trigger_hbd);
   trigger_lg.Append(another_event->trigger_lg);
   trigger_ct.Append(another_event->trigger_ct);
   scaler_gtr.Append(another_event->scaler_gtr);
   scaler_hbd.Append(another_event->scaler_hbd);
   scaler_lg.Append(another_event->scaler_lg);
   scaler_ct.Append(another_event->scaler_ct);
   if (!ut3.ValidFlag() && another_event->ut3.ValidFlag()) {
      ut3.Copy(another_event->ut3);
   }
   return true;
}

E16DST_DST0ScalerEvent::E16DST_DST0ScalerEvent() : E16DST_DST0Event()
{
   Clear();
}
E16DST_DST0ScalerEvent::~E16DST_DST0ScalerEvent() {}

void E16DST_DST0ScalerEvent::Clear()
{
   E16DST_DST0Event::Clear();
   scaler_gtr.Clear();
   scaler_hbd.Clear();
   scaler_lg.Clear();
   scaler_ct.Clear();
   ut3.Clear();
}

int E16DST_DST0ScalerEvent::Write(E16DST_File *fp)
{
   int write_size = fp->write(reinterpret_cast<char *>(&header), sizeof(E16DST_DST0EventHeader));
   write_size += scaler_gtr.Write(fp);
   write_size += scaler_hbd.Write(fp);
   write_size += scaler_lg.Write(fp);
   write_size += scaler_ct.Write(fp);
   write_size += ut3.Write(fp);
   return write_size;
}

int E16DST_DST0ScalerEvent::Read(E16DST_File *fp)
{
   this->Clear();
   int read_size = fp->read(reinterpret_cast<char *>(&header), sizeof(E16DST_DST0EventHeader));
   read_size += scaler_gtr.Read(fp);
   read_size += scaler_hbd.Read(fp);
   read_size += scaler_lg.Read(fp);
   read_size += scaler_ct.Read(fp);
   read_size += ut3.Read(fp);
   return read_size;
}

bool E16DST_DST0ScalerEvent::Append(E16DST_DST0Event *_another_event)
{
   E16DST_DST0ScalerEvent *another_event = dynamic_cast<E16DST_DST0ScalerEvent *>(_another_event);
   if (another_event == nullptr) {
      return false;
   }
   if (!header.Append(another_event->header)) {
      std::cerr << "Header mismatch is detected. EventID = " << this->EventID() << std::endl;
      return false;
   }
   scaler_gtr.Append(another_event->scaler_gtr);
   scaler_hbd.Append(another_event->scaler_hbd);
   scaler_lg.Append(another_event->scaler_lg);
   scaler_ct.Append(another_event->scaler_ct);
   if (!ut3.ValidFlag() && another_event->ut3.ValidFlag()) {
      ut3.Copy(another_event->ut3);
   }
   return true;
}

int E16DST_DST0SpillStartEvent::Write(E16DST_File *fp)
{
   int write_size = fp->write(reinterpret_cast<char *>(&header), sizeof(E16DST_DST0EventHeader));
   write_size += fp->write(reinterpret_cast<char *>(&nEventsInSpill), sizeof(uint32_t));
   write_size += fp->write(reinterpret_cast<char *>(&shotNumber), sizeof(uint32_t));
   return write_size;
}

int E16DST_DST0SpillStartEvent::Read(E16DST_File *fp)
{
   this->Clear();
   int read_size = fp->read(reinterpret_cast<char *>(&header), sizeof(E16DST_DST0EventHeader));
   read_size += fp->read(reinterpret_cast<char *>(&nEventsInSpill), sizeof(uint32_t));
   read_size += fp->read(reinterpret_cast<char *>(&shotNumber), sizeof(uint32_t));
   return read_size;
}

bool E16DST_DST0SpillStartEvent::Append(E16DST_DST0Event *_another_event)
{
   E16DST_DST0SpillStartEvent *another_event = dynamic_cast<E16DST_DST0SpillStartEvent *>(_another_event);
   if (another_event == nullptr) {
      return false;
   }
   if (!header.Append(another_event->header)) {
      std::cerr << "Header mismatch is detected. EventID = " << this->EventID() << std::endl;
      return false;
   }
   nEventsInSpill = nEventsInSpill & another_event->nEventsInSpill;
   shotNumber = shotNumber & another_event->shotNumber;
   return true;
}

E16DST_DST0Header::E16DST_DST0Header()
   : version(E16DST_DST0::Version), nEventTypes(E16DST_DST0EventType::NEventTypes),
     nSamplesSSD(E16DST_Constant::NSamplesSSD), nSamplesGTR(E16DST_Constant::NSamplesGTR),
     nSamplesHBD(E16DST_Constant::NSamplesHBD), nSamplesLG(E16DST_Constant::NSamplesLG),
     nSamplesCT(E16DST_Constant::NSamplesCT)
{
   magic_word[0] = 'd';
   magic_word[1] = 's';
   magic_word[2] = 't';
   magic_word[3] = '0';
	 startYear  = 0xffffffff;
	 startMonth = 0xffffffff;
	 startDay   = 0xffffffff;
	 startHour  = 0xffffffff;
	 startMin   = 0xffffffff;
	 startSec   = 0xffffffff;
}

E16DST_DST0Header::~E16DST_DST0Header() {}

int E16DST_DST0Header::Write(E16DST_File *fp)
{
   return fp->write(reinterpret_cast<char *>(this), sizeof(E16DST_DST0Header));
}

int E16DST_DST0Header::Read(E16DST_File *fp)
{
   return fp->read(reinterpret_cast<char *>(this), sizeof(E16DST_DST0Header));
}

bool E16DST_DST0Header::Check()
{
   if (magic_word[0] != 'd' || magic_word[1] != 's' || magic_word[2] != 't' || magic_word[3] != '0') {
      std::cerr << "E16DST_DST0Header::Check() : wrong magic. "
                << "Data : " << magic_word[0] << magic_word[1] << magic_word[2] << magic_word[3] << ", Program : dst0"
                << std::endl;
      return false;
   }
   if (version != E16DST_DST0::Version) {
      std::cerr << "E16DST_DST0Header::Check() : Version is incosistent. "
                << "Data : " << version << ", Program : " << E16DST_DST0::Version << std::endl;
      return false;
   }
   if (nEventTypes != E16DST_DST0EventType::NEventTypes) {
      std::cerr << "E16DST_DST0Header::Check() : NEventTypes is incosistent. "
                << "Data : " << nEventTypes << ", Program : " << E16DST_DST0EventType::NEventTypes << std::endl;
      return false;
   }
   if (nSamplesSSD != E16DST_Constant::NSamplesSSD) {
      std::cerr << "E16DST_DST0Header::Check() : NSamplesSSD is incosistent. "
                << "Data : " << nSamplesSSD << ", Program : " << E16DST_Constant::NSamplesSSD << std::endl;
      return false;
   }
   if (nSamplesGTR != E16DST_Constant::NSamplesGTR) {
      std::cerr << "E16DST_DST0Header::Check() : NSamplesGTR is incosistent. "
                << "Data : " << nSamplesGTR << ", Program : " << E16DST_Constant::NSamplesGTR << std::endl;
      return false;
   }
   if (nSamplesHBD != E16DST_Constant::NSamplesHBD) {
      std::cerr << "E16DST_DST0Header::Check() : NSamplesHBD is incosistent. "
                << "Data : " << nSamplesHBD << ", Program : " << E16DST_Constant::NSamplesHBD << std::endl;
      return false;
   }
   if (nSamplesLG != E16DST_Constant::NSamplesLG) {
      std::cerr << "E16DST_DST0Header::Check() : NSamplesLG is incosistent. "
                << "Data : " << nSamplesLG << ", Program : " << E16DST_Constant::NSamplesLG << std::endl;
      return false;
   }
   if (nSamplesCT != E16DST_Constant::NSamplesCT) {
      std::cerr << "E16DST_DST0Header::Check() : NSamplesCT is incosistent. "
                << "Data : " << nSamplesCT << ", Program : " << E16DST_Constant::NSamplesCT << std::endl;
      return false;
   }
   return true;
}

void E16DST_DST0Header::SetStartTime(uint16_t _hour, uint16_t _min, uint16_t _sec)
{
	startHour = static_cast<uint32_t>(_hour);
	startMin  = static_cast<uint32_t>(_min);
	startSec  = static_cast<uint32_t>(_sec);
}

void E16DST_DST0Header::SetStartTime(uint16_t _year, uint8_t _month, uint8_t _day, uint8_t _hour, uint8_t _min, uint8_t _sec)
{
	startYear  = static_cast<uint32_t>(_year);
	startMonth = static_cast<uint32_t>(_month);
	startDay   = static_cast<uint32_t>(_day);
	startHour  = static_cast<uint32_t>(_hour);
	startMin   = static_cast<uint32_t>(_min);
	startSec   = static_cast<uint32_t>(_sec);
}

void E16DST_DST0Header::SetTrgVer(uint32_t _trgVer)
{
   for (int i = 0; i < 4; ++i) {
      trgVer[i] = _trgVer % 0x100;
			_trgVer /= 0x100;
   }
}

E16DST_DST0::E16DST_DST0() : eventType(Version), event(nullptr)
{
   for (int i = 0; i < E16DST_DST0EventType::NEventTypes; i++) {
      eventFactory[i] = nullptr;
   }
   eventFactory[E16DST_DST0EventType::Physics] = new E16DST_DST0PhysicsEvent();
   eventFactory[E16DST_DST0EventType::Scaler] = new E16DST_DST0ScalerEvent();
   eventFactory[E16DST_DST0EventType::SpillStart] = new E16DST_DST0SpillStartEvent();
   eventFactory[E16DST_DST0EventType::SpillEnd] = new E16DST_DST0SpillEndEvent();
}

E16DST_DST0::~E16DST_DST0()
{
   for (int i = 0; i < E16DST_DST0EventType::NEventTypes; i++) {
      if (eventFactory[i] != nullptr) {
         delete eventFactory[i];
         eventFactory[i] = nullptr;
      }
   }
}

bool E16DST_DST0::Open(std::string file_name, int open_mode, int compress_mode)
{
   if (compress_mode == Auto) {
      if (file_name.find(".gz") != std::string::npos) {
         std::cerr << "E16DST_DST0::Open : ZlibGzip mode" << std::endl;
         file = new E16DST_GZFile();
      } else if (file_name.find(".zst") != std::string::npos) {
         std::cerr << "E16DST_DST0::Open : ZSTD mode" << std::endl;
         file = new E16DST_ZSTDFile();
      } else {
         std::cerr << "E16DST_DST0::Open : NonCompressed mode" << std::endl;
         file = new E16DST_FileStream();
      }
   } else if (compress_mode == NonCompressed) {
      std::cerr << "E16DST_DST0::Open : NonCompressed mode" << std::endl;
      file = new E16DST_FileStream();
   } else if (compress_mode == ZlibGzip) {
      std::cerr << "E16DST_DST0::Open : ZlibGzip mode" << std::endl;
      file = new E16DST_GZFile();
   } else if (compress_mode == ZSTD) {
      std::cerr << "E16DST_DST0::Open : ZSTD mode" << std::endl;
      file = new E16DST_ZSTDFile();
   } else {
      std::cerr << "Unknown compress mode : " << compress_mode << std::endl;
      return false;
   }
   if (open_mode == WriteMode) {
      file->open(file_name, E16DST_File::WriteMode);
      if (!file->good()) {
         std::cerr << "Failed to open file : " << file_name << std::endl;
         return false;
      }
      header.Write(file);
      return true;
   }
   if (open_mode == ReadMode) {
      file->open(file_name, E16DST_File::ReadMode);
      if (!file->good()) {
         std::cerr << "Failed to open file : " << file_name << std::endl;
         return false;
      }
      int read_size = header.Read(file);

      if (read_size < (int)sizeof(E16DST_DST0Header)) {
         std::cerr << "Input file is too small (smaller than size of E16DST_DST0Header)." << std::endl;
         return false;
      }
      return header.Check();
   }
   return false;
}

void E16DST_DST0::SetEventType(uint16_t type)
{
   eventType.SetEventType(type);
   event = eventFactory[type];
}

void E16DST_DST0::WriteAnEvent(E16DST_File *fp)
{
   if (!fp) {
      std::cerr << "pointer to E16DST_File is null" << std::endl;
      return;
   }
   fp->write(reinterpret_cast<char *>(&eventType), sizeof(E16DST_DST0EventType));
   if (event != nullptr) {
      event->Write(fp);
   } else {
      std::cerr << "EventType is not set." << std::endl;
   }
}

int E16DST_DST0::ReadAnEvent(E16DST_File *fp)
{
   if (!fp) {
      std::cerr << "pointer to E16DST_File is null" << std::endl;
      return 0;
   }
   int read_size = fp->read(reinterpret_cast<char *>(&eventType), sizeof(E16DST_DST0EventType));
   // std::cerr << "Version : " << eventType.Version() << ", Type : " << eventType.EventType() << std::endl;
   if (read_size < (int)sizeof(E16DST_DST0EventType)) {
      //std::cerr << "eof" << std::endl;
      return 0;
   }
   if (eventType.Version() != Version) {
      std::cerr << "Version disagreement is detected. Data : " << eventType.Version() << ", Program : " << Version
                << std::endl;
      return 0;
   }
   if (eventType.EventType() >= E16DST_DST0EventType::NEventTypes) {
      std::cerr << "Invalid EventType. Data : " << eventType.EventType()
                << ", Max : " << E16DST_DST0EventType::NEventTypes << std::endl;
      return 0;
   }
   event = eventFactory[eventType.EventType()];
   read_size += event->Read(fp);
   // std::cerr << "read_size = " << read_size << std::endl;
   return read_size;
}

void E16DST_DST0::WriteAnEvent(uint16_t type, E16DST_DST0Event *_event)
{
   SetEventType(type);
   event = _event;
   WriteAnEvent(file);
}

E16DST_DST0Event* E16DST_DST0EventFactory::Create(uint16_t event_type){
   E16DST_DST0Event *event = nullptr;
   switch (event_type) {
      case E16DST_DST0EventType::Physics:
         event = new E16DST_DST0PhysicsEvent();
         break;
      case E16DST_DST0EventType::Scaler:
         event = new E16DST_DST0ScalerEvent();
         break;
      case E16DST_DST0EventType::SpillStart:
         event = new E16DST_DST0SpillStartEvent();
         break;
      case E16DST_DST0EventType::SpillEnd:
         event = new E16DST_DST0SpillEndEvent();
         break;
      default:
         std::cerr << "E16DST_DST0EventFactory : Invalid event type = " << event_type << std::endl;
         break;
   }
   return event;
}

E16DST_DST0Event* E16DST_DST0EventFactory::Create(char *buffer, int buffer_size){
   E16DST_DST0EventType event_type;
   memcpy(reinterpret_cast<char *>(&event_type), buffer, sizeof(event_type));
   E16DST_DST0Event *event = E16DST_DST0EventFactory::Create(event_type.EventType());
   E16DST_MemoryBuffer fp(buffer + sizeof(event_type), buffer_size);
   event->Read(&fp);
   return event;
}

