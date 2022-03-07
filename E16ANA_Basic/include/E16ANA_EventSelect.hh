#ifndef E16ANA_EVENT_SELECT_HH
#define E16ANA_EVENT_SELECT_HH

#include <iostream>
#include <string>
#include <vector>

class E16ANA_EventSelect {
 public:
  E16ANA_EventSelect() {}
  ~E16ANA_EventSelect() {}
  bool ReadConstantData(int run_id);
  bool ReadConstantDataByLocal(int run_id, std::string index_file_name);
  int RunId() { return run_id; }
  bool IsSelectedEventID(int _event_id) {
    for (const auto& id : selected_event_ids) {
      if (id == _event_id) {
        return true;
      }
    }
    return false;
  }
  int NumSelectedEventIDs() { return selected_event_ids.size(); }
  int SelectedEventID(int n) { return selected_event_ids[n]; }
  std::vector<int>& SelectedEventIDs() { return selected_event_ids; }
  void Print() {
    for (const auto& id : selected_event_ids) {
      std::cout << id << std::endl;
    }
  }
 private:
  bool ReadConstantDataCore(int _run_id, std::string _index_file_name);
  int run_id;
  std::vector<int> selected_event_ids;
};

#endif // E16ANA_EVENT_SELECT_HH
