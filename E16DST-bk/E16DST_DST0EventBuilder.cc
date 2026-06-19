#include "E16DST_DST0EventBuilder.hh"

#include <algorithm>
#include <sstream>
#include <iomanip>

E16DST_DST0EventBuilder::E16DST_DST0EventBuilder(int _n_required, std::string file_name)
   : n_required(_n_required), buffer_size(2000), max_event_per_file(-1), file_number(0), num_iteration(0)
{
   discard_inconsistent_event = false;
   no_split = true;
   dst0 = new E16DST_DST0();
   if (!dst0->Open(file_name, E16DST_DST0::WriteMode)) {
      exit(1);
   }
}

E16DST_DST0EventBuilder::E16DST_DST0EventBuilder(int _n_required, std::string _file_name_prefix, std::string _file_extension)
   : n_required(_n_required), buffer_size(2000), file_name_prefix(_file_name_prefix), file_extension(_file_extension), max_event_per_file(-1), file_number(0), num_iteration(0)
{
   discard_inconsistent_event = false;
   no_split = false;
   dst0 = new E16DST_DST0();
}

E16DST_DST0EventBuilder::~E16DST_DST0EventBuilder()
{
   delete dst0;
}

std::string E16DST_DST0EventBuilder::GetFileName(){
   if (no_split || (max_event_per_file <= 0)) {
      return file_name_prefix + file_extension;
   }
   std::ostringstream ss;
   ss << std::setw(4) << std::setfill('0') << file_number;
   file_number++;
   return file_name_prefix + "_" + ss.str() + file_extension;
}

void E16DST_DST0EventBuilder::SetEventFragment(int fragment_id, E16DST_DST0Event *event_fragment)
{
   int id = event_fragment->EventID();
   if (event_buffer.find(id) != event_buffer.end()) { // found
      event_buffer[id].SetEventFragment(fragment_id, event_fragment);
   } else { // not found
      event_buffer[id].SetEventType(event_fragment->EventType());
      event_buffer[id].SetNumberOfRequired(n_required);
      event_buffer[id].SetEventFragment(fragment_id, event_fragment);
   }
}

void E16DST_DST0EventBuilder::BuiltEvent::SetEventFragment(int fragment_id, E16DST_DST0Event *event_fragment)
{
   if (first_fragment) {
      event->HeaderCopy(event_fragment);
      first_fragment = false;
   }
   int id = event_fragment->EventID();
   if (set_flag[fragment_id]) {
      std::cerr << "Error. E16DST_DST0EventBuilder : FragmentID = " << fragment_id << ", EventID = " << id
                << " is overlapped." << std::endl;
      error_flag = true;
      return;
   }
   set_flag[fragment_id] = 1;
   n_fragments++;
   if (!event->Append(event_fragment)) {
      error_flag = true;
   }
}

void E16DST_DST0EventBuilder::WriteIfComplete(int id)
{
   BuiltEvent &e = event_buffer[id];
   if (e.IsComplete(n_required)) {
      if (!(e.error_flag && discard_inconsistent_event)) {
         // std::cerr << "E16DST_DST0EventBuilder : EventID = " << id << " is complete." << std::endl;
         this->WriteAnEvent(e.event);
      }
      event_buffer.erase(id);
   }
}

void E16DST_DST0EventBuilder::ProcessIncompleteEvent(int id, BuiltEvent &e){
   // print error message
   std::cerr << "Error. E16DST_DST0EventBuilder : EventID = " << id
             << " is incomplete. IDs of missing fragments are";
   for (int i = 0; i < n_required; i++) {
      if (!e.set_flag[i]) {
         std::cerr << " " << i;
      }
   }
   std::cerr << std::endl;
   // file write or not
   if (!discard_inconsistent_event) {
      this->WriteAnEvent(e.event);
   }
}

void E16DST_DST0EventBuilder::ProcessErroneousEvent(int id, BuiltEvent &e){
   std::cerr << "Error. E16DST_DST0EventBuilder : EventID = " << id << ", EventHeader mismatch detected." << std::endl;
   if (!discard_inconsistent_event) {
      this->WriteAnEvent(e.event);
   }
}

void E16DST_DST0EventBuilder::WriteAllEventInBuffer()
{
   std::map<int, BuiltEvent>::iterator itr; // auto itr = event_buffer.begin();
   std::cerr << "event_buffer size = " << event_buffer.size() << std::endl;
   if (event_buffer.empty()) {
      return;
   }
   for (itr = event_buffer.begin(); itr != event_buffer.end(); itr++) {
      int id = itr->first;
      if (itr->second.error_flag) {
         ProcessErroneousEvent(id, itr->second);
      } else if (itr->second.IsComplete(n_required)) {
         this->WriteAnEvent(itr->second.event);
      } else {
         ProcessIncompleteEvent(id, itr->second);
      }
   }
   event_buffer.clear();
}

void E16DST_DST0EventBuilder::WriteHalfOfBuffer()
{
   std::map<int, BuiltEvent>::iterator itr; // auto itr = event_buffer.begin();
   std::cerr << "event_buffer size = " << event_buffer.size() << std::endl;
   int current_buffer_size = event_buffer.size();
   if (current_buffer_size <= buffer_size / 2) {
      return;
   }
   for (itr = event_buffer.begin(); itr != event_buffer.end();) {
      int id = itr->first;
      if (itr->second.error_flag) {
         ProcessErroneousEvent(id, itr->second);
      } else if (itr->second.IsComplete(n_required)) {
         this->WriteAnEvent(itr->second.event);
      } else {
         ProcessIncompleteEvent(id, itr->second);
      }
      itr = event_buffer.erase(itr);
      current_buffer_size = event_buffer.size();
      if (current_buffer_size <= buffer_size / 2) {
         std::cerr << "event_buffer size = " << event_buffer.size() << std::endl;
         return;
      }
   }
}

void E16DST_DST0EventBuilder::WriteAnEvent(E16DST_DST0Event *event)
{
   static bool first = true;
   if (!no_split && first) {
      std::string file_name = GetFileName();
      std::cout << file_name << std::endl;
      if (!dst0->Open(file_name, E16DST_DST0::WriteMode)) {
         exit(1);
      }
      first = false;
   }
   if (!no_split && max_event_per_file > 0) {
      if (num_iteration >= max_event_per_file) {
         dst0->Close();
         std::string f = GetFileName();
         if (!dst0->Open(f, E16DST_DST0::WriteMode)) {
            exit(1);
         }
         num_iteration = 0;
      }
   }
   dst0->WriteAnEvent(event);
   num_iteration++;
   return;
}

void E16DST_DST0EventBuilder::WriteAnEvent(uint16_t type, E16DST_DST0Event *event)
{
   dst0->WriteAnEvent(type, event);
}
