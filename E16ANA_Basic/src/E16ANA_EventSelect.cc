#include "E16ANA_EventSelect.hh"

#include <fstream>
#include <iostream>
#include <sstream>

#include "E16ANA_CalibDBManager.hh"

bool E16ANA_EventSelect::ReadConstantDataCore(int _run_id, std::string _index_file_name) {
  run_id = _run_id;
  auto& calib = E16ANA_CalibDBManager::Instance();
  bool flag = true;
  auto in_file_ptr = calib.CalibStreamOpenTextByLocalName(_index_file_name);
  if (in_file_ptr == nullptr) {
    return false;
  }
  auto& in_file = *in_file_ptr;
  auto map = calib.ReadFileWithNumberKey(in_file);
  auto item = map.lower_bound(run_id);
  std::stringstream ss;
  ss << static_cast<std::string>(item->second);
  selected_event_ids.clear();
  int tmp_int;
  while (ss >> tmp_int) {
    selected_event_ids.emplace_back(tmp_int);
  }
  in_file.close();
  delete in_file_ptr;
  return flag;
}

bool E16ANA_EventSelect::ReadConstantData(int run_id) {
  auto& calib = E16ANA_CalibDBManager::Instance();
  auto index_file_name = calib.SearchForIndexFileName("event-select");
  return ReadConstantDataCore(run_id, index_file_name);
}

bool E16ANA_EventSelect::ReadConstantDataByLocal(int run_id, std::string index_file_name) {
  return ReadConstantDataCore(run_id, index_file_name);
}
