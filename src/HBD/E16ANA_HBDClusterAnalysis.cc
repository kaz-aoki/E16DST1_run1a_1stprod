#include "E16ANA_HBDClusterAnalysis.hh"
#include "E16ANA_HBDGeometry.hh"
#include "E16ANA_HBDChannelManager.hh"

#include <cstring>
#include <vector>
#include <algorithm>

E16ANA_HBDClusterAnalysis::E16ANA_HBDClusterAnalysis(const int _module_id): module_id(_module_id)
{
}

E16ANA_HBDClusterAnalysis::E16ANA_HBDClusterAnalysis()
{
}

E16ANA_HBDClusterAnalysis::~E16ANA_HBDClusterAnalysis()
{
}

void E16ANA_HBDClusterAnalysis::Clear()
{
  for(int i=0; i<n_pads; i++){
    adc[i].clear();
    pe[i].clear();
    tdc[i].clear();
    hit_dstid[i].clear();
  }
  hit_padid.clear();
  clusters.clear();
}

void E16ANA_HBDClusterAnalysis::SetData(const int _module_id, const int pad_id, const double _adc, const double _pe, const double _tdc, const int dst_id)
{
  SetData(_module_id, pad_id, _adc, _pe, _tdc);
  hit_dstid[pad_id].push_back(dst_id);
}

void E16ANA_HBDClusterAnalysis::SetData(const int _module_id, const int pad_id, const double _adc, const double _pe, const double _tdc)
{
  if(E16ANA_HBDChannelManager::IsValidPadID(pad_id) && module_id == _module_id){
    hit_padid.push_back(pad_id);
    adc[pad_id].push_back(_adc);
    pe[pad_id].push_back(_pe);
    tdc[pad_id].push_back(_tdc);
  }
}

bool E16ANA_HBDClusterAnalysis::DoClustering()
{
  //make the size of hit_dstid same to adc[], pe[], tdc[]
  for(int i=0; i<n_pads; i++){
    if(hit_dstid[i].size() != adc[i].size()){
      hit_dstid[i].resize(adc[i].size(), -1);//-1 is invalid id for dst id
    }
  }
  
  //erase duplicates of any element.
  std::sort(hit_padid.begin(), hit_padid.end());
  hit_padid.erase(std::unique(hit_padid.begin(), hit_padid.end()), hit_padid.end());
  
  //clustering
  int cid = 0;
  for(;;){
    if( hit_padid.empty() ) break;
    hbd_cluster cluster;
    cluster.module_id = module_id;
    cluster.cid = cid;
    cluster.sadc = 0.;
    cluster.spe = 0.;
    cluster.time_diff = 0;
    cluster.size = 0;
    for(int i=0; i<3; i++){
      cluster.lpos_w_adc[i] = -10000.;
      cluster.lpos_w_pe[i] = -10000.;
    }
    int n_call = 0;
    
    if( !SubClustering(hit_padid[0], cluster, n_call) ) return false;
    
    CalcTimeDiff(cluster);
    CalcLocalPositionWADCWeight(cluster);
    CalcLocalPositionWPEWeight(cluster);
    CalcMaxADCPadID(cluster);
    CalcMaxADC(cluster);
    CalcMaxPEPadID(cluster);
    CalcMaxPE(cluster);
    CalcAverageTime(cluster);
    
    clusters.push_back(cluster);
    cid++;
  }
  
  return true;
}

bool E16ANA_HBDClusterAnalysis::SubClustering(const int pad_id, hbd_cluster &cluster, int &n_call)
{
  n_call++;
  
  if(n_call > n_pads){
    std::cerr<<"ERROR: Too large cluster size"<<std::endl;
    return false;
  }
  
  //add pad into cluster and erase the pad from hit_padid
  std::vector<double>::iterator max_itr;
  int max_index = 0;
  if(adc[pad_id].size() > 1){
    max_itr = std::max_element(adc[pad_id].begin(), adc[pad_id].end());
    max_index = std::distance(adc[pad_id].begin(), max_itr);
  }
  cluster.sadc += adc[pad_id].at(max_index);
  cluster.spe += pe[pad_id].at(max_index);
  cluster.id.push_back(pad_id);
  cluster.adc.push_back(adc[pad_id].at(max_index));
  cluster.pe.push_back(pe[pad_id].at(max_index));
  cluster.tdc.push_back(tdc[pad_id].at(max_index));
  cluster.dst_id.push_back(hit_dstid[pad_id].at(max_index));
  cluster.size++;
  
  for(int i=0; i<adc[pad_id].size(); i++){
    if(i == max_index) continue;
    cluster.pileup_id.push_back(pad_id);
    cluster.pileup_adc.push_back(adc[pad_id].at(i));
    cluster.pileup_pe.push_back(pe[pad_id].at(i));
    cluster.pileup_tdc.push_back(tdc[pad_id].at(i));
    cluster.pileup_dst_id.push_back(hit_dstid[pad_id].at(i));
  }
  hit_padid.erase(std::remove(hit_padid.begin(), hit_padid.end(), pad_id), hit_padid.end());
  
  //get neighboring pad
  std::vector<int> neighboring_id;
  E16ANA_HBDChannelManager::GetNeighboringPadID(pad_id, neighboring_id);
  
  //clustering
  for(auto neighbor : neighboring_id){
    if(std::find(hit_padid.begin(), hit_padid.end(), neighbor) != hit_padid.end()){
      if( !SubClustering(neighbor, cluster, n_call) ) return false;
    }
  }
  
  return true;
}

void E16ANA_HBDClusterAnalysis::ShowClusters()
{
  for(auto c : clusters){
    std::cerr<<"----------------------------------------"<<std::endl;
    std::cerr<<"module ID / cluster ID: "<<c.module_id<<" / "<<c.cid<<std::endl;
    std::cerr<<"size / sadc / spe / time_diff / fastest"<<std::endl;
    std::cerr<<c.size<<" / "<<c.sadc<<" / "<<c.spe<<" / "<<c.time_diff<<" / "<<c.fastest_tdc<<std::endl;
    std::cerr<<"local pos w adc: "<<c.lpos_w_adc[0]<<" "<<c.lpos_w_adc[1]<<" "<<c.lpos_w_adc[2]<<std::endl;
    std::cerr<<"local pos w pe: "<<c.lpos_w_pe[0]<<" "<<c.lpos_w_pe[1]<<" "<<c.lpos_w_pe[2]<<std::endl;
    std::cerr<<std::endl;
    std::cerr<<"member pad IDs / adc / pe / tdc / dstid: "<<std::endl;
    for(int j=0; j<c.id.size(); j++){
      std::cerr<<c.id.at(j)<<" / "<<c.adc.at(j)<<" / "<<c.pe.at(j)<<" / "<<c.tdc.at(j)<<" / "<<c.dst_id.at(j)<<std::endl;
    }
    std::cerr<<std::endl;
    std::cerr<<"pileup pad IDs / adc / pe / tdc / dstid: "<<std::endl;
    for(int j=0; j<c.pileup_id.size(); j++){
      std::cerr<<c.pileup_id.at(j)<<" / "<<c.pileup_adc.at(j)<<" / "<<c.pileup_pe.at(j)<<" / "<<c.pileup_tdc.at(j)<<" / "<<c.pileup_dst_id.at(j)<<std::endl;
    }
    std::cerr<<"----------------------------------------"<<std::endl;
  }
}

E16ANA_HBDClusterAnalysis::hbd_cluster E16ANA_HBDClusterAnalysis::GetMaxADCCluster(std::vector<hbd_cluster> &_clusters)
{
  double sadc = -10000.;
  int counter = 0;
  int i = -1;
  for(auto e : _clusters){
    if( sadc < e.sadc ){
      i = counter;
    }
    counter++;
  }
  return _clusters.at(i);
}

E16ANA_HBDClusterAnalysis::hbd_cluster E16ANA_HBDClusterAnalysis::GetMaxSizeCluster(std::vector<hbd_cluster> &_clusters)
{
  int size = -1;
  int counter = 0;
  int i = -1;
  for(auto e : _clusters){
    if( size < e.size ){
      i = counter;
    }
    counter++;
  }
  return _clusters.at(i);
}

void E16ANA_HBDClusterAnalysis::CalcTimeDiff(hbd_cluster &cluster)
{
  double diff = 0.;
  double fastest = 10000.;
  double latest = -1.;
  
  if( cluster.size == 1){
    fastest = cluster.tdc[0];
    latest = cluster.tdc[0];
    diff = 0.;
  }
  if( cluster.size >= 2){
    for(auto t : cluster.tdc){
      if(t < fastest){
	fastest = t;
      }
      if(t > latest){
	latest = t;
      }
    }
    diff = latest - fastest;
  }
  
  cluster.fastest_tdc = fastest;
  cluster.time_diff = diff;
}

void E16ANA_HBDClusterAnalysis::CalcLocalPositionWADCWeight(hbd_cluster &cluster)
{
  double lpos[3] = {0., 0., 0.};
  double sadc = cluster.sadc;
  std::vector<int> id = cluster.id;
  for(int i=0; i<id.size(); i++){
    double buf[3];
    E16ANA_HBDGeometry::GetPadLocalCOG(cluster.module_id, id.at(i), buf);
    for(int j=0; j<3; j++){
      if (j < 2) {
        lpos[j] += buf[j]*cluster.adc.at(i)/sadc;
      } else {
        lpos[j] = 0.;
      }
    }
  }
  
  for(int i=0; i<3; i++){
    cluster.lpos_w_adc[i] = lpos[i];
  }
}

void E16ANA_HBDClusterAnalysis::CalcLocalPositionWPEWeight(hbd_cluster &cluster)
{
  double lpos[3] = {0., 0., 0.};
  double spe = cluster.spe;
  std::vector<int> id = cluster.id;
  for(int i=0; i<id.size(); i++){
    double buf[3];
    E16ANA_HBDGeometry::GetPadLocalCOG(cluster.module_id, id.at(i), buf);
    for(int j=0; j<3; j++){
      lpos[j] += buf[j]*cluster.pe.at(i)/spe;
    }
  }
  
  for(int i=0; i<3; i++){
    cluster.lpos_w_pe[i] = lpos[i];
  }
}

void E16ANA_HBDClusterAnalysis::CalcMaxADCPadID(hbd_cluster &cluster)
{
  std::vector<double>::iterator max_itr;
  int max_index = 0;
  max_itr = std::max_element(cluster.adc.begin(), cluster.adc.end());
  max_index = std::distance(cluster.adc.begin(), max_itr);
  
  cluster.max_adc_id = cluster.id.at(max_index);
}

void E16ANA_HBDClusterAnalysis::CalcMaxPEPadID(hbd_cluster &cluster)
{
  std::vector<double>::iterator max_itr;
  int max_index = 0;
  max_itr = std::max_element(cluster.pe.begin(), cluster.pe.end());
  max_index = std::distance(cluster.pe.begin(), max_itr);

  cluster.max_pe_id = cluster.id.at(max_index);
}

void E16ANA_HBDClusterAnalysis::CalcMaxADC(hbd_cluster &cluster)
{
  std::vector<double>::iterator max_itr;
  int max_index = 0;
  max_itr = std::max_element(cluster.adc.begin(), cluster.adc.end());
  max_index = std::distance(cluster.adc.begin(), max_itr);
  
  cluster.max_adc = cluster.adc.at(max_index);
}

void E16ANA_HBDClusterAnalysis::CalcMaxPE(hbd_cluster &cluster)
{
  std::vector<double>::iterator max_itr;
  int max_index = 0;
  max_itr = std::max_element(cluster.pe.begin(), cluster.pe.end());
  max_index = std::distance(cluster.pe.begin(), max_itr);
  
  cluster.max_pe = cluster.pe.at(max_index);
}

void E16ANA_HBDClusterAnalysis::CalcAverageTime(hbd_cluster &cluster)
{
  cluster.average_time = 0.;
  for(auto t : cluster.tdc){
    cluster.average_time += t;
  }
  cluster.average_time = cluster.average_time/cluster.tdc.size();
}
