#include "STS/E16ANA_STSAnalyzer.hh"
#include "E16DST_DST1.hh"


void E16ANA_STSAnalyzer::clusterize(std::vector<E16DST_DST1STSHit>& hits1, std::vector<E16DST_DST1STSCluster>& clusters1){
  sort(hits1);
  
  if ( hits1.size() == 0 ) return;
  
  for( auto& hit : hits1 ) {
    

  }
}

void E16ANA_STSAnalyzer::sort(std::vector<E16DST_DST1STSHit>& hits1){
    if ( hits1.size() > 0 ){
    auto judge = [](auto& hita, auto& hitb)->bool{
      if ( hita.ModuleId() != hitb.ModuleId() ) {
	return ( hita.ModuleId() < hitb.ModuleId() );
      }else{
	if ( hita.PN() != hitb.PN() ) {
	  return (hita.PN() < hitb.PN());
	}else {
	  if ( hita.StripId() != hitb.StripId() ) {
	    return (hita.StripId() < hitb.StripId() );
	  }
	}
      }
      return false;
    };
    std::sort(hits1.begin(),hits1.end(),judge);
  }
}
