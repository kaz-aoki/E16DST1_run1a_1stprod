#ifndef E16ANA_SimulatedHits_hh
#define E16ANA_SimulatedHits_hh

#include <TVector3.h>
#include "E16ANA_GTRTemplatePulseCalib.hh"

// Added in 2025 Feb. by mtomoki 
// GTRSimulatedHit's' saves the waveform 
// STSSimulatedHit' '   saves the cluster info itself.(not waveform or so on.)
//

struct GTRSimulatedCluster {
      int mid;
      int lid;
      double cluster_timing;
      std::vector<int> pedestals;
      std::vector<int> strip_ids;
      std::vector<std::vector<double>> waveforms;//sim.
      std::vector<std::vector<double>> dst0_waveforms;//dst0
      std::vector<std::vector<double>> merged_waveforms;// sim+dst0-pedestal
      size_t csize;
      GTRSimulatedCluster(int _mid, int _lid, std::vector<int> _strip_ids, std::vector<std::vector<double>> _waveforms, double _ct )
      : mid(_mid), lid(_lid), strip_ids(std::move(_strip_ids)), waveforms(std::move(_waveforms)), cluster_timing(_ct) {
      if (strip_ids.size() == waveforms.size()) {
          csize = strip_ids.size();
          } else {
          throw std::runtime_error("Mismatch: strip_ids and waveforms sizes are different");
          }
          pedestals.resize(csize);
          dst0_waveforms.resize(csize,   std::vector<double>(E16ANA_GTRTemplatePulseCalib::n_gtr_samples, 0));
          merged_waveforms.resize(csize, std::vector<double>(E16ANA_GTRTemplatePulseCalib::n_gtr_samples, 0));
      }
};



class E16ANA_GTRSimulatedHits {
public:
   E16ANA_GTRSimulatedHits(){}
   ~E16ANA_GTRSimulatedHits(){}

   void Clear(){
      simulated_clusters.clear();
      for(int l=0; l<3;l++){
         mid_list[l] = -999;
      }
   }
   void PushBackSimulatedCluster(const GTRSimulatedCluster &sim){
      simulated_clusters.push_back(sim);
   }
   std::vector<GTRSimulatedCluster>& GetClusterOnAChamber (int mid, int lid) ;
   std::vector<GTRSimulatedCluster>& GetClusterAll () {return simulated_clusters;};
   const std::vector<double> &GetFadc(int mid, int lid, int sid) const;
   void SetModuleIDList(int mid, int lid){mid_list[lid] = mid;};
   int  ModuleID(int lid){return mid_list[lid];};
   //void SetFilledStripID(int lid, int sid);
   //std::vector<int> FilledStripID(int lid) {return sid_list[lid]};

private:
   std::vector<GTRSimulatedCluster> simulated_clusters; 
   std::vector<GTRSimulatedCluster> return_box;//just for return of functions
   std::array<int, 3> mid_list;
    
};


//class E16ANA_GTRSimulatedHits {
//public:
//   E16ANA_GTRSimulatedHits(){}
//   ~E16ANA_GTRSimulatedHits(){}
//   struct DismissedMockCluster {
//      int mock_id;
//      int mid;
//      int lid;
//      std::vector<int> sids;
//      std::vector<std::vector<int>> waveforms;
//      //std::vector<std::array<int, E16ANA_GTRTemplatePulseCalib::n_gtr_samples>> waveforms;
//   };
//   void Clear(){
//      fadc.clear();
//      missed_fadc.clear();
//      for(int i=0;  i<3;i++){
//         mid_list[i]=-999;
//         sid_list[i].clear();
//      }
//   }
//   static std::string MakeKey(int mid, int lid, int sid);
//   std::array<int, E16ANA_GTRTemplatePulseCalib::n_gtr_samples>  GetFadc(int mid, int lid, int sid) const;
//   void SetFadc(int mid, int lid, int sid, const std::array<int, E16ANA_GTRTemplatePulseCalib::n_gtr_samples>& waveform);
//   void SetDismissedFadc(int mock_id, int mid, int lid, const std::vector<int>& sids,const std::vector<std::vector<int>>& waveform);
//   
////   static std::string MakeKey_trackid(int mid, int lid);
////   void SetMockTrackID(int mid, int lid, int track_id);
////   int GetMockTrackID(int mid, int lid);
//
//   std::vector<std::pair<int, std::array<int, E16ANA_GTRTemplatePulseCalib::n_gtr_samples>>> GetFadcOnChamber(int mid, int lid) const;
//   std::vector<int> GetFilledSids(int mid, int lid) const;
//   void SetModuleIDList(int mid, int lid){mid_list[lid] = mid;};
//   int ModuleID(int lid){return mid_list[lid];};
//   std::vector<DismissedMockCluster>& GetMissedFadc() { return missed_fadc; }
//
//
//
//   //void SetFilledStripID(int lid, int sid);
//   //std::vector<int> FilledStripID(int lid) {return sid_list[lid]};
//
//private:
//   //key(mid, lid, sid) ---- sid = x+y  ex.)GTR100(0, 431)
//   std::unordered_map<std::string, std::array<int, E16ANA_GTRTemplatePulseCalib::n_gtr_samples>> fadc;
//   std::vector<DismissedMockCluster> missed_fadc;
//   std::array<int, 3> mid_list;//GTR100, GTR200, GTR300
//   std::array<std::vector<int>, 3> sid_list;//GTR100, GTR200, GTR300
//   ////key(mid, lid)
//   //std::unordered_map<std::string, int> mock_id;
//};
//
class E16ANA_STSSimulatedHit {
public:
   E16ANA_STSSimulatedHit(){}
   ~E16ANA_STSSimulatedHit(){}
   void SetModuleID(int _mid){mid = _mid;}
   void SetCogPosX(double _lx){lpos_x = _lx;}
   void SetTiming(double _t){tdc = _t;}
   void SetPeakSum(double _adc){adc_sum = _adc;}
   int    ModuleID() {return mid;}
   double CogPosX() {return lpos_x;}
   double Timing(){return tdc;}
  double PeakSum(){return adc_sum;}
   void SetMockTrackID(int i){mock_id = i;}
   int MockTrackID(){return mock_id;}


private:
   int mid;
   double lpos_x;
   TVector3 gpos;
   double tdc;
   double adc_sum;
   int mock_id;

};



class E16ANA_SimulatedHits {
public:
   E16ANA_SimulatedHits(){};
   ~E16ANA_SimulatedHits(){};
   E16ANA_GTRSimulatedHits* &GTR(int mock_id){ return gtr_hits[mock_id];};
   std::vector<E16ANA_GTRSimulatedHits*> &GTR(){ return gtr_hits;};
   std::vector<E16ANA_STSSimulatedHit*> &STS(){ return sts_hits;};
   E16ANA_STSSimulatedHit*  &STS(int mock_id){ return sts_hits[mock_id];};
   void Clear();
   //SetNMockTracks(int i) {n_mock_tracks = i;};
   //NMockTracks() {return n_mock_tracks;};
private:
   std::vector<E16ANA_GTRSimulatedHits*>  gtr_hits;//each mock has each GTR SIM
   std::vector<E16ANA_STSSimulatedHit*>   sts_hits;
   //int n_mock_tracks;
};
#endif
