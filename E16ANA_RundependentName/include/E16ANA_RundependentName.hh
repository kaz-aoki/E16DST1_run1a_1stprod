//2021-09-12, uploaded by yokkaich
//E16ANA_RundependentName.hh 210912 by S. Yokkaichi
//    Last modified at <2021-09-12 22:19:31 >
//



#ifndef E16ANA_RundependentName_HH
#define E16ANA_RundependentName_HH

#include <string>
#include <map>


class E16ANA_RundependentName{
public:
  static E16ANA_RundependentName& Instance();

private:
  //singleton : locate private to suppress copying
  E16ANA_RundependentName( const E16ANA_RundependentName& );
  E16ANA_RundependentName( );
  static E16ANA_RundependentName singleton;

  //keep a status
  std::map<std::string, int> runidCache;
  std::map<std::string, std::string> nameCache;

  //utility
  std::string UNCHENGED;
  std::string SearchIndexFileForName(std::string indexfilename, int runID);

public:
  std::string ReadNameWithRunID(int irunID, std::string key, std::string path="");
  // key :  geometry, fieldmap
  // return "unchanged" when the runID or filename is unchanged
  // path:  return  (path + name in file) if exist

};


#endif //E16ANA_RundependentInfo_HH

