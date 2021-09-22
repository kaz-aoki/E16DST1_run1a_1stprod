#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
//#include <boost/program_options.hpp>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_SSDcalib.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DefaultFilePath.hh"

//----arimizu include----
#include <TH1I.h>
#include <TH1D.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TStyle.h>
//----end arimizu include----

using namespace std;
//namespace  bpo = boost::program_options;


//----arimizu----
int c_mid(int mid){
  int m=-1;
  if(mid==102||mid==103||mid==104){
    m=mid-102;
  }
  if(mid==106||mid==107||mid==108){
    m=mid-106+3;
  }
  return m;
}
//----arimizu----


int main(int argc, char* argv[]) {
  if (argc != 5) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst0] [output.dst1] [run ID] [max physics event (all: -1)] " << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  auto run_id        = stoi(argv[3]);
  auto max_event     = stoi(argv[4]);
  //  bpo::variables_map vm;
  //  string in_file_name;
  //  string out_file_name;
  //  int run_num;

  //  bpo::options_description command_options("command options");
  //  command_options.add_options()
  //    ("in",                           bpo::value<string>(&in_file_name),                                                                "Input file name (string)\n")
  //    ("out",                          bpo::value<string>(&out_file_name),                                                               "Output file name (string)\n")
  //    ("coincidence-map-file-w-mag0",  bpo::value<string>(&coincidence_map_files[0])->default_value(string(CoincidenceMapWMagFile0)),    "Coincidence map file w/ mag 0 (string)\n");
  //    ("coincidence-map-file-w-mag1",  bpo::value<string>(&coincidence_map_files[1])->default_value(string(CoincidenceMapWMagFile1)),    "Coincidence map file w/ mag 1 (string)\n");
  //    ("coincidence-map-file-w-mag2",  bpo::value<string>(&coincidence_map_files[2])->default_value(string(CoincidenceMapWMagFile2)),    "Coincidence map file w/ mag 2 (string)\n");
  //    ("coincidence-map-file-w-mag3",  bpo::value<string>(&coincidence_map_files[3])->default_value(string(CoincidenceMapWMagFile3)),    "Coincidence map file w/ mag 3 (string)\n");
  //    ("coincidence-map-file-w-mag4",  bpo::value<string>(&coincidence_map_files[4])->default_value(string(CoincidenceMapWMagFile4)),    "Coincidence map file w/ mag 4 (string)\n");
  //    ("coincidence-map-file-w-mag5",  bpo::value<string>(&coincidence_map_files[5])->default_value(string(CoincidenceMapWMagFile5)),    "Coincidence map file w/ mag 5 (string)\n");
  //    ("coincidence-map-file-wo-mag0", bpo::value<string>(&coincidence_map_files[6])->default_value(string(CoincidenceMapWoMagFile0)),   "Coincidence map file w/o mag 0 (string)\n");
  //    ("coincidence-map-file-wo-mag1", bpo::value<string>(&coincidence_map_files[7])->default_value(string(CoincidenceMapWoMagFile1)),   "Coincidence map file w/o mag 1 (string)\n");
  //    ("coincidence-map-file-wo-mag2", bpo::value<string>(&coincidence_map_files[8])->default_value(string(CoincidenceMapWoMagFile2)),   "Coincidence map file w/o mag 2 (string)\n");
  //    ("coincidence-map-file-wo-mag3", bpo::value<string>(&coincidence_map_files[9])->default_value(string(CoincidenceMapWoMagFile3)),   "Coincidence map file w/o mag 3 (string)\n");
  //    ("coincidence-map-file-wo-mag4", bpo::value<string>(&coincidence_map_files[10])->default_value(string(CoincidenceMapWoMagFile4)),  "Coincidence map file w/o mag 4 (string)\n");
  //    ("coincidence-map-file-wo-mag5", bpo::value<string>(&coincidence_map_files[11])->default_value(string(CoincidenceMapWoMagFile5)),  "Coincidence map file w/o mag 5 (string)\n");
  //    ("trigger-gtr-channel-map",      bpo::value<string>(&trigger_channel_map_files[0])->default_value(string(TriggerChannelMapFile0)), "Trigger GTR channel map file (string)\n");
  //    ("trigger-hbd-channel-map",      bpo::value<string>(&trigger_channel_map_files[1])->default_value(string(TriggerChannelMapFile1)), "Trigger HBD channel map file (string)\n");
  //    ("trigger-lg-channel-map",       bpo::value<string>(&trigger_channel_map_files[2])->default_value(string(TriggerChannelMapFile2)), "Trigger LG channel map file (string)\n");
  //
  //  auto file_check = [&vm, &in_file_name, &out_file_name]() {
  //    if (in_file_name.empty()) {
  //      throw invalid_argument("Invalid input file name: "s + in_file_name);
  //    }
  //    if (out_file_name.empty()) {
  //      throw invalid_argument("Invalid output file name: "s + out_file_name);
  //    }
  //  };

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
  auto trigger_param = new E16ANA_TriggerCalibParam();
  trigger_param->ReadConstantData(calib.CurrentRunID());
  E16ANA_GTRcalibPedestal gtrped;
  //  gtrped.ReadCalibData( calib.CurrentRunID() );

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));



  //----arimizu plot----
  const int n_module = 6;
  const int c_canv[6]={2,4,6,1,3,5};
  const int c_module[9]={-1,2,1,0,-1,3,4,5,-1};

  TString output_pdf_name = "ssdfit.pdf";
  TString output_pdf_name0 = "ssdfit_noPedestal.pdf";

  TH1I *h_HitID[n_module];
  for(int i=0; i<n_module; i++){
    h_HitID[i] = new TH1I(Form("hitID[%d]",i),"h",768,0,768);
  }
  TH1D *h_Timing;
  h_Timing = new TH1D("timing","h",400,-100,300);
  TH1D *h_HitTime;
  h_HitTime = new TH1D("hit time","h",150,-50,100);
  TH1D *h_PeakTime;
  h_PeakTime = new TH1D("peak time","h",400,-100,300);
  TH1D *h_PeakHeight;
  h_PeakHeight = new TH1D("peak height","h",400,-100,300);
  TH1D *h0_HitTime;
  h0_HitTime = new TH1D("hit time","h",150,-50,100);
  TH1D *h0_PeakTime;
  h0_PeakTime = new TH1D("peak time","h",400,-100,300);
  TH1D *h0_PeakHeight;
  h0_PeakHeight = new TH1D("peak height","h",400,-100,300);

  TH1D *c_HitID[n_module];
  for(int i=0; i<n_module; i++){
    c_HitID[i] = new TH1D(Form("c- hitID[%d]",i),"h",60,0,60);
  }
  TH1D *c_Timing;
  c_Timing = new TH1D("c- Timing","h",400,-100,300);
  TH1D *c_PeakSum;
  c_PeakSum = new TH1D("c- PeakSum","h",400,-100,300);
  TH1D *c_TDC;
  c_TDC = new TH1D("c- TDC","h",400,-100,300);
  TH1D *c_TanTheta;
  c_TanTheta = new TH1D("c- TanTheta","h",200,-100,100);
  TH1D *c_ClusterSize;
  c_ClusterSize = new TH1D("c- ClusterSize","h",400,-100,300);
  //----end arimizu plot----



  
  auto dst0 = new E16DST_DST0();


  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }
  //  E16ANA_GTRPedestal *gtr_pedestal = new E16ANA_GTRPedestal();
  //  gtr_pedestal->Read(argv[5]);
  //  auto dst1 = new E16DST_DST1();
  //  auto dst1 = new E16DST_DST0();
  //  if (!dst1->Open(out_file_name, E16DST_DST0::WriteMode)) {
  //    std::cerr << "Cannot open output file: " << out_file_name << std::endl;
  //    return -1;
  //   }

//  TFile* froot = new TFile(out_file_name,"recreate");
//  TH1F* hlgph = new TH1F("hlgph","LGPeak",10000,0,1000);
//  TH1I* hlgpt = new TH1I("hlgpt","LGPeakTime",20000,-10000,10000);
//  TH1F* hlgtm = new TH1F("hlgtm","LGTiming",20000,-10000,10000);
//  TH1F* hlgbs = new TH1F("hlgbs","LGBaseline",20000,-10000,10000);
//  TH1F* hlgbr = new TH1F("hlgbr","LGBaselineRms",20000,-10000,10000);
//  TH1F* hlgit = new TH1F("hlgit","LGIntegral",20000,-10000,10000);

  int n_event = 0;
  int n_physics_event = 0;

  auto record = new E16DST_DST1PhysicsRecord();
  while (dst0->ReadAnEvent()) {
    if (max_event != -1 && n_physics_event >= max_event) {
      break;
    }
    if (n_event % 1000 == 0) {
      cout << "Number of event: " << n_event << endl;
    }
    auto event_type = dst0->EventType();
    //    dst1->SetEventType(event_type);
    if (event_type == E16DST_DST0EventType::Physics) {
      auto event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());

      //      auto event1 = dynamic_cast<E16DST_DST1PhysicsEvent*>(dst1->Event());

      auto& ssd_hits0         = event0->SSD();
      auto& gtr_hits0         = event0->GTR();
      auto& hbd_hits0         = event0->HBD();
      auto& lg_hits0          = event0->LG();
      auto& trigger_gtr_hits0 = event0->TriggerGTR();
      auto& trigger_hbd_hits0 = event0->TriggerHBD();
      auto& trigger_lg_hits0  = event0->TriggerLG();
      auto timestamp         = event0->TimeStamp();
      vector<E16DST_DST1SSDHit> hits;
      vector<E16DST_DST1SSDCluster> clusters;
      E16DST_DST1SSDFactory(ssd_hits0, &hits, &clusters);
      //E16DST_DST1GTRHitAndClusterFactory(gtr_hits0, &event1->GTRHits(), &event1->GTRClusters());
      //E16DST_DST1HBDFactory(hbd_hits0, &event1->HBDHits(), &event1->HBDClusters());
      //E16DST_DST1LGHitAndClusterFactorylg_hits0,   event1->LGHits(),  event1->LGClusters());
      //E16DST_DST1LGFactory(lg_hits0,   &event1->LGHits(),  &event1->LGClusters());
      //E16DST_DST1LGFactoryDST1Detector(lg_hits0,   &event1->LG());
      //E16DST_DST1TriggerFactory(event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), timestamp, &event1->Trigger());
      //event1->Trigger().SetValidFlag(1);


      //----arimizu plot----

      int n_ssd_clusterhits = clusters.size();
      for(int i=0; i<n_ssd_clusterhits; i++){
	auto &c1=clusters[i];
	int n = c1.NumHits();
	int m = c1.ModuleId();
	c_HitID[c_mid(m)]->Fill(c1.CogPos());
	c_Timing->Fill(c1.Timing());
	c_PeakSum->Fill(c1.PeakSum());
	c_TDC->Fill(c1.TdcPos());
	c_TanTheta->Fill(c1.TanTheta());
      }
      auto n_ssd_hits = hits.size();
      for(int n_hit=0; n_hit < n_ssd_hits; n_hit++){
	auto &hit = hits[n_hit];
	h_HitTime->Fill(hit.HitTime());
	h_PeakTime->Fill(hit.PeakTime());
	h_PeakHeight->Fill(hit.PeakHeight());
	for(int module=0; module<n_module; module++){
	  if(c_module[hit.ModuleId()-101]==module){
	    h_HitID[module]->Fill(hit.ChannelId());
	  }
	  else{
	    //	    cout << "!!!!" << endl;
	  }
	}
      }


      // E16ANA_SSDcalibPedestal ssdped;
      // ssdped.ReadCalibData(calib.CurrentRunID());
      // E16ANA_SSDcalibTimeConstant ssdtime;
      // ssdtime.ReadConstantData(calib.CurrentRunID());
      // double offset = ssdtime.TDCoffset();
      // double timegain = ssdtime.TDCtimeGain();

      // int n_max = ssd_hits0.NumberOfHits();
      // TF1 *f_fit[n_max];
      // vector<vector<int>> adc;
      // vector<vector<double>> time;
      // adc.resize(n_max);
      // time.resize(n_max);

      // for(int i=0; i<n_max; i++){
      // 	f_fit[i] = new TF1("fitfunc", "[1]*(x-[2])/[0]*exp(-(x-[2])/[0])",0,200);
      // 	E16DST_DST0SSDHit &h0 = ssd_hits0.Hit(i);
      // 	int mid = h0.ModuleID();
      // 	int sid = h0.StripID();
      // 	adc.at(i).resize(8);
      // 	time.at(i).resize(8);
      // 	for(int j=0; j<8; j++){
      // 	  adc.at(i).at(j) = h0.Waveform()[j] - ssdped.Pedestal(c_mid(mid), sid, j);
      // 	  time.at(i).at(j) = 25*j + (h0.TDC()-offset)*timegain;
      // 	}
      // }
      // //      cout << "adc.at(0).at(0)=" << adc.at(0).at(0) << endl;
	
      // TCanvas *c2 = new TCanvas("c2","c2",0,0,1000,700);
      // c2->SaveAs(output_pdf_name+"[","pdf");
      // c2->Clear();
      // c2->Divide(5,5);
      // int i=0;
      // int k=0;
      // int max;
      // max = event1->SSDHits().NumberOfHits();
      // while(i<25){
      // 	if(k>=max){
      // 	  break;
      // 	}
      // 	auto &hit = event1->SSDHits().Hit(k);

      // 	//	cout << "peaktime=" << hit.PeakTime() << endl;
      // 	// if(hit.PeakTime()!=140){
      // 	//   //	  cout << "peak=" << hit.PeakTime() << endl;
      // 	//   c2->cd(i+1);
      // 	//   double ADC[8];
      // 	//   double TIME[8];
      // 	//   for(int j=0;j<8;j++){
      // 	//     ADC[j] = adc.at(k).at(j);
      // 	//     TIME[j] = time.at(k).at(j);
      // 	//   }
      // 	//   TGraph* gr = new TGraph(8, TIME, ADC);
      // 	//   gr->Draw("AP");
      // 	//   f_fit[i] -> SetParameter(0,hit.PeakTime());
      // 	//   f_fit[i] -> SetParameter(1,hit.PeakHeight());
      // 	//   f_fit[i] -> SetParameter(2,hit.HitTime());
      // 	//   f_fit[i] -> Draw("same");
      // 	//   i++;
      // 	// }
      // 	k++;
      // }
      // c2->SaveAs(output_pdf_name,"pdf");
      // c2->SaveAs(output_pdf_name+"]","pdf");     


      //----end arimizu plot----

      // Check begin
      auto event_id = event0->EventID();
      cout << "Event ID: " << event_id << endl;
      // SSD

      // GTR
      // cout << "Number of event: " << n_event << endl << endl;
      // auto n_gtr_hits = event1->GTRHits().NumberOfHits();
      // cout << "Number of GTR hits: " << n_gtr_hits << endl;
      // for (int n_hit = 0; n_hit < n_gtr_hits; ++n_hit) {
      //   auto hit = event1->GTRHits().Hit(n_hit);
      //   hit.Print();
      // }
      // auto n_gtr_clusters = event1->GTRClusters().NumberOfHits();
      // cout << endl << endl;
      // cout << "Number of GTR clusters: " << n_gtr_clusters << endl;
      // for (int n_cluster = 0; n_cluster < n_gtr_clusters; ++n_cluster) {
      //   auto cluster = event1->GTRClusters().Hit(n_cluster);
      //   cluster.Print();
      // }
      
      // HBD

      // LG
      // if (event1->LGHits().NumberOfHits() != 0) {
      //   auto lghit = event1->LGHits().Hit(0);                                                          
      //   lghit.Print();                                                                                 
      //   std::cout<<"LPos:("<<lghit.LocalPos(*geometry).X()<< ","<<lghit.LocalPos(*geometry).Y()<<","<<lghit.LocalPos(*geometry).Z()<<")"<<std::endl;  
      //   std::cout<<"GPos:("<<lghit.GlobalPos(*geometry).X()<< ","<<lghit.GlobalPos(*geometry).Y()<<","<<lghit.GlobalPos(*geometry).Z()<<")"<<std::endl;     
      // }

      // trigger
      //      event1->Trigger().Print(*geometry);

      // other
      //      event1->GTR().Print();
      //
      //      if (event1->LG().NumHits() != 0) {
      //        auto lghit = event1->LG().Hit(0);                                                          
      //        lghit.Print();                                                                                 
      //        std::cout<<"LPos:("<<lghit.LocalPos(*geometry).X()<< ","<<lghit.LocalPos(*geometry).Y()<<","<<lghit.LocalPos(*geometry).Z()<<")"<<std::endl;  
      //        std::cout<<"GPos:("<<lghit.GlobalPos(*geometry).X()<< ","<<lghit.GlobalPos(*geometry).Y()<<","<<lghit.GlobalPos(*geometry).Z()<<")"<<std::endl;     
      //      }

      cout << endl << endl;
      // Check end

      //      dst1->WriteAnEvent();
    } else if (event_type == E16DST_DST0EventType::Scaler) {
      auto event0 = dynamic_cast<E16DST_DST0ScalerEvent*>(dst0->Event());
      //      dst1->WriteAnEvent(event0);
    } else if (event_type == E16DST_DST0EventType::SpillStart) {
      auto event0 = dynamic_cast<E16DST_DST0SpillStartEvent*>(dst0->Event());
      //      dst1->WriteAnEvent(event0);
    } else if (event_type == E16DST_DST0EventType::SpillEnd) {
      auto event0 = dynamic_cast<E16DST_DST0SpillEndEvent*>(dst0->Event());
      //      dst1->WriteAnEvent(event0);
    } else {
      std::cerr << "Invalid Event Type: " << event_type << std::endl;
      return -1;
    }
    ++n_event;
    ++n_physics_event;
  }


  //----arimizu plot----
  TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,700);
  TString plotname = "ssd_plot.pdf";
  c1->SaveAs(plotname+"[","pdf");
  
  c1->Clear();
  c1->Divide(2,3);
  for(int module=0; module<n_module; module++){
    c1->cd(c_canv[module]);
    h_HitID[module]->Draw();
  }
  c1->SaveAs(plotname,"pdf");

  c1->Clear();
  gStyle->SetOptStat("nermou");
  h_HitTime->Draw();
  c1->SaveAs(plotname,"pdf");

  c1->Clear();
  h_PeakTime->Draw();
  c1->SaveAs(plotname,"pdf");

  c1->Clear();
  h_PeakHeight->Draw();
  c1->SaveAs(plotname,"pdf");

  c1->Clear();
  c1->Divide(2,3);
  for(int module=0; module<n_module; module++){
    c1->cd(c_canv[module]);
    c_HitID[module]->Draw();
  }
  c1->SaveAs(plotname,"pdf");

  c1->Clear();
  c_Timing->Draw();
  c1->SaveAs(plotname,"pdf");

  c1->Clear();
  c_PeakSum->Draw();
  c1->SaveAs(plotname,"pdf");

  c1->Clear();
  c_TDC->Draw();
  c1->SaveAs(plotname,"pdf");

  c1->Clear();
  c_TanTheta->Draw();
  c1->SaveAs(plotname,"pdf");

  c1->Clear();
  c_ClusterSize->Draw();
  c1->SaveAs(plotname,"pdf");

  c1->SaveAs(plotname+"]","pdf");

  //----end arimizu plot----







  delete geometry;
  delete dst0;
  //  dst1->Close();
  return 0;
}
