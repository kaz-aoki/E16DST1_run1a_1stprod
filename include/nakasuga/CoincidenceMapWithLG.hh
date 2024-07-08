#ifndef CoincidenceMapWithLG_h
#define CoincidenceMapWithLG_h

#include <vector>
#include <utility>

class CoincidenceMapWithLG{

public:
  CoincidenceMapWithLG(char *_filename);
  ~CoincidenceMapWithLG();
  std::vector<int> GetLGCoincidenceChannelsWithHBD(int hbd_module_id, int hbd_tile_id);
  std::vector<int> GetHBDCoincidenceChannelsWithLG(int lg_module_id, int lg_block_id);
  
private:
  char *filename;
  std::vector<std::pair<int, int>> coin;
};

class SearchLGCh{
  
public :
  SearchLGCh(int target_) : target(target_){};
  bool operator()(const std::pair<int, int> pair) const{
    return target == pair.first;
  };
  
private:
  int target;
};

class SearchHBDCh{
  
public :
  SearchHBDCh(int target_) : target(target_){};
  bool operator()(const std::pair<int, int> pair) const{
    return target == pair.second;
  };
  
private:
  int target;
};
#endif // CoincidenceMapWithLG_h
