#ifndef E16DST_DST0EVENTBUILDER_HH
#define E16DST_DST0EVENTBUILDER_HH

#include "E16DST_DST0.hh"

#include <map>
#include <vector>
#include <iostream>

class E16DST_DST0EventBuilder {
public:
   E16DST_DST0EventBuilder(int _n_required, std::string file_name);
   E16DST_DST0EventBuilder(int _n_required, std::string _file_name_prefix, std::string _file_extension);
   ~E16DST_DST0EventBuilder();
   void SetBufferSize(int _buffer_size) { buffer_size = _buffer_size; };
   void SetEventFragment(int fragment_id, E16DST_DST0Event *event_fragment);
   void WriteIfComplete(int id); // "id" used for event building here is "event_id"
   void WriteAllEventInBuffer();
   void WriteAnEvent(uint16_t type, E16DST_DST0Event *event);
   void SetDiscardInconsistentEvent(bool flag) { discard_inconsistent_event = flag; };
   bool IsBufferFull() { return (int)event_buffer.size() >= buffer_size; };
   void WriteHalfOfBuffer();
   void SetMaxEventPerFile(int m){
      max_event_per_file = m;
   };

private:
   const int n_required;
   int buffer_size;
   E16DST_DST0 *dst0;
   std::string file_name_prefix;
   std::string file_extension;
   int max_event_per_file;
   int file_number;
   bool no_split;
   int num_iteration;
   struct BuiltEvent {
      E16DST_DST0Event *event;
      int n_fragments;
      std::vector<int> set_flag;
      bool error_flag;
      bool first_fragment;

      BuiltEvent()
      {
         //event = new E16DST_DST0Event();
         n_fragments = 0;
         error_flag = false;
         first_fragment = true;
      };
      ~BuiltEvent() { delete event; };
      void SetEventType(uint16_t event_type) { event = E16DST_DST0EventFactory::Create(event_type); };
      void SetNumberOfRequired(int _n_required) { set_flag.resize(_n_required); };
      bool IsComplete(int _n_required) {
         if (event->EventType() == E16DST_DST0EventType::Physics) {
            return (_n_required == n_fragments);
         }
         return (n_fragments >= 1);
      };
      void SetEventFragment(int fragment_id, E16DST_DST0Event *event_fragment);
   };
   bool discard_inconsistent_event;
   std::map<int, BuiltEvent> event_buffer;
   void ProcessIncompleteEvent(int id, BuiltEvent &e);
   void ProcessErroneousEvent(int id, BuiltEvent &e);
   std::string GetFileName();
   void WriteAnEvent(E16DST_DST0Event *event);

};

#endif // E16DST_DST0EVENTBUILDER_HH
