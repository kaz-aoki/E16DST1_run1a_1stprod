#include "STS/E16ANA_STSAnalyzer.hh"
#include "E16DST_DST1.hh"
#include <algorithm>

//#define STS_VERB

void E16ANA_STSAnalyzer::clusterize(std::vector<E16DST_DST1STSHit>& hits1, std::vector<E16DST_DST1STSCluster>& clusters1){
  if ( hits1.size() == 0 ) return; // no hits to be clusterized.
  sort(hits1);

  std::vector<E16ANA_STSCluster> vec_cluster;

  // 1st clustering
  for( auto& hit : hits1 ) {
    if (vec_cluster.size() == 0 ){
      vec_cluster.emplace_back();
      vec_cluster.back().hits.push_back(hit);
      continue;
    }
    auto& lasthit = vec_cluster.back().hits.back();
    if ( lasthit.ModuleId() == hit.ModuleId() &&
	 lasthit.PN() == hit.PN() ) {
      if ( lasthit.StripId() + 1 == hit.StripId() ||
	   lasthit.StripId() == hit.StripId() ) {
	vec_cluster.back().hits.push_back(hit);
	continue;
      }
    }
    vec_cluster.emplace_back();
    vec_cluster.back().hits.push_back(hit);
  }

#ifdef STS_VERB
  std::for_each(begin(vec_cluster),end(vec_cluster),
		[](auto& x){
		  x.show();
		});
#endif

  // 2nd clustering.
  for( int iclus = 0; iclus < vec_cluster.size(); iclus++ ){
    if ( vec_cluster[iclus].hits.size() <= 1 ) continue;
    
    auto judge_less = [](const auto& a, const auto& b){
      return a.TDC() < b.TDC();
    };
    
    auto minmax = std::minmax_element(vec_cluster[iclus].hits.begin(),vec_cluster[iclus].hits.end(),judge_less);
    if ( fabs(minmax.second->TDC() - minmax.first->TDC()) < param.tdc_window ) continue; 
#ifdef STS_VERB
    std::cout << "ALERT: maybe different event :" << minmax.first->TDC() << " VS " << minmax.second->TDC() << std::endl;
#endif
     // There is more than a hit that has different TDCs.
    vec_cluster.emplace_back();
    for( int ihit = 0; ihit < vec_cluster[iclus].hits.size();){
      if ( fabs(vec_cluster[iclus].hits[ihit].TDC() - minmax.first->TDC()) > param.tdc_window){
	if (minmax.first->TDC() < param.tdc_window ) {
	  // have to search for the other side of TDC.
#ifdef STS_VERB
	  std::cout << "TDC is less than window. Have to look for the other side of TDC also." << std::endl;
#endif
	  if ( fabs( vec_cluster[iclus].hits[ihit].TDC()-minmax.first->TDC()- 0x3fff ) < param.tdc_window ) {
	    // OK.
#ifdef STS_VERB
	    std::cout << vec_cluster[iclus].hits[ihit].TDC() << " is compared to minimum TDC " << minmax.first->TDC() << " and grouped into the same as minmum" << std::endl;
#endif
	    ihit++; continue;
	  }
	}
	auto iterhit = vec_cluster[iclus].hits.begin() + ihit;
	vec_cluster.back().hits.push_back(*iterhit);
	vec_cluster[iclus].hits.erase(iterhit);
	continue;
      }
      ihit++; // pass
    }
  }

  
  // remove same tdc hits.
  for( int iclus = 0; iclus < vec_cluster.size(); iclus++ ){
    if ( vec_cluster[iclus].hits.size() <= 1 ) continue;
    for ( int ihit = 0; ihit < vec_cluster[iclus].hits.size()-1; ihit++ ){
      auto& hita = vec_cluster[iclus].hits[ihit];
      auto& hitb = vec_cluster[iclus].hits[ihit+1];
      if ( hita.StripId() == hitb.StripId() ){
#ifdef STS_VERB
	cout << "Same TDC pair found. stripID=" << hita.StripId() << std::endl;
#endif
	if ( hita.TDC()== hitb.TDC() ) {
	  if ( hita.ADC() > hitb.ADC() ) {
	    auto iter = vec_cluster[iclus].hits.begin()+ihit+1;
	    vec_cluster[iclus].hits.erase(iter);
	    ihit--;
	  }else{
	    auto iter = vec_cluster[iclus].hits.begin()+ihit;
	    vec_cluster[iclus].hits.erase(iter);
	    ihit--;
	  }
	}
      }
    }
  }

#ifdef STS_VERB
  std::cout << "AFTER DIVIDING CLUSTERS according to TDC" << std::endl;
  std::for_each(begin(vec_cluster),end(vec_cluster),
		[](auto& x){
		  x.show();
		});
#endif

  // fill DST1STSCluster
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
	  }else{
	    // if ( tdc != tdc ) {
	    // return tdc < tdc
	    // }
	  }
	}
      }
      return false;
    };
    std::sort(hits1.begin(),hits1.end(),judge);
  }
}

