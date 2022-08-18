#include <iostream>

#include "E16DST_DST0.hh"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "./bin input.dst0" << endl;
    return -1;
  }
  auto in_file_name = argv[1];

  FILE* fp = fopen(in_file_name, "r");
  if (!fp) {
    cerr << "cannot open file: " << in_file_name << endl;
    return -1;
  }
  fclose(fp);

  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    cerr << "cannot open file as DST0: " << in_file_name << endl;
    return -1;
  }

  int n_events = 0;
  while(dst0->ReadAnEvent()) {
    ++n_events;
  }
  cout << "number of events: " << n_events << endl;

  delete dst0;
  return 0;
}
