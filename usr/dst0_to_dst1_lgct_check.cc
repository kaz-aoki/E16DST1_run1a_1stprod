#include <iostream>
#include <TROOT.h>
#include <TH1.h>
#include <TFile.h>
#include <TTree.h>
// #include <boost/program_options.hpp>

#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRcalib.hh"
#include "E16ANA_TriggerCalib.hh"
#include "E16DST_DST0.hh"
#include "E16DST_DST1.hh"
#include "E16DST_DST1DetectorFactory.hh"
#include "E16DST_DST1DefaultFilePath.hh"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"
#include "E16ANA_LGConstant.hh"
#include "E16ANA_LGDeadChannel.hh"
#include "E16ANA_LGClustering.hh"
#include "E16ANA_LGCheckHist.hh"
#include "E16ANA_CTBasic.hh"
#include "E16ANA_CTWaveform.hh"
#include "E16ANA_CTConstant.hh"
#include "E16ANA_CTCheckHist.hh"
#include "E16DST_Constant.hh"

using namespace std;
// namespace  bpo = boost::program_options;

// #define WF_ON
#define TRG_ON
#define LGDST1_ON

int main(int argc, char* argv[]) {
  if (argc != 6) {
    cerr << "Invalid argc: " << argc << endl;
    cerr << "./bin [input.dst0] [output.dst1] [hist.pdf] [run ID] [max physics event (all: -1)] " << endl;
    return -1;
  }
  auto in_file_name  = argv[1];
  auto out_file_name = argv[2];
  auto out_pdf_name  = argv[3];
  auto run_id        = stoi(argv[4]);
  auto max_event     = stoi(argv[5]);

  TFile *fout = new TFile(out_file_name,"recreate");
  TTree *tree = new TTree("tree","tree");
  // std::ofstream frun("runinfo.txt");

  uint16_t lgmodule, lgblock;
  int ct0module, ct0block, ct1module, ct1block;
  int lgpeaktime, ct0peaktime, ct1peaktime;
  float lgpeakheight, lgtiming, lgbaseline, lgbaselinerms, trg_lg_hit_t, ct0peakheight, ct0timing, ct0baseline, ct0baselinerms, trg_ct0_hit_t, ct1peakheight, ct1timing, ct1baseline, ct1baselinerms, trg_ct1_hit_t;
  bool lgdst1flag, lgtrg, lgtrgwtrk;
  double lgwaveform[E16DST_Constant::NSamplesLG];
  double ct0waveform[E16DST_Constant::NSamplesCT];
  double ct1waveform[E16DST_Constant::NSamplesCT];

  int run, event, spill, timestampinspill;
  bool sl, sr, sl2, sr2, im3, im2;

  tree->Branch("Run",&run,"Run/I");
  tree->Branch("Event",&event,"Event/I");
  tree->Branch("Spill",&spill,"Spill/I");
  tree->Branch("TimeStampInSpill",&timestampinspill,"TimeStampInSpill/I");
  tree->Branch("SL",&sl,"SL/O");
  tree->Branch("SR",&sr,"SR/O");
  tree->Branch("SL2",&sl2,"SL2/O");
  tree->Branch("SR2",&sr2,"SR2/O");
  tree->Branch("IM3",&im3,"IM3/O");
  tree->Branch("IM2",&im2,"IM2/O");

  tree->Branch("LGModule",&lgmodule,"LGModule/s");
  tree->Branch("LGBlock",&lgblock,"LGBlock/s");
  tree->Branch("LGPeakHeight",&lgpeakheight,"LGPeakHeight/F");
  tree->Branch("LGPeakTime",&lgpeaktime,"LGPeakTime/I");
  tree->Branch("LGTiming",&lgtiming,"LGTiming/F");
  tree->Branch("LGBaseline",&lgbaseline,"LGBaseline/F");
  tree->Branch("LGBaselineRms",&lgbaselinerms,"LGBaselineRms/F");
  tree->Branch("CT0Module",&ct0module,"CT0Module/I");
  tree->Branch("CT0Block",&ct0block,"CT0Block/I");
  tree->Branch("CT0PeakHeight",&ct0peakheight,"CT0PeakHeight/F");
  tree->Branch("CT0PeakTime",&ct0peaktime,"CT0PeakTime/I");
  tree->Branch("CT0Timing",&ct0timing,"CT0Timing/F");
  tree->Branch("CT0Baseline",&ct0baseline,"CT0Baseline/F");
  tree->Branch("CT0BaselineRms",&ct0baselinerms,"CT0BaselineRms/F");
  tree->Branch("CT1Module",&ct1module,"CT1Module/I");
  tree->Branch("CT1Block",&ct1block,"CT1Block/I");
  tree->Branch("CT1PeakHeight",&ct1peakheight,"CT1PeakHeight/F");
  tree->Branch("CT1PeakTime",&ct1peaktime,"CT1PeakTime/I");
  tree->Branch("CT1Timing",&ct1timing,"CT1Timing/F");
  tree->Branch("CT1Baseline",&ct1baseline,"CT1Baseline/F");
  tree->Branch("CT1BaselineRms",&ct1baselinerms,"CT1BaselineRms/F");
#ifdef WF_ON
  tree->Branch("LGWaveform",lgwaveform,Form("LGWaveform[%d]/D",E16DST_Constant::NSamplesLG));
  tree->Branch("CT0Waveform",ct0waveform,Form("CT0Waveform[%d]/D",E16DST_Constant::NSamplesCT));
  tree->Branch("CT1Waveform",ct1waveform,Form("CT1Waveform[%d]/D",E16DST_Constant::NSamplesCT));
#endif
  tree->Branch("LGDst1Flag",&lgdst1flag,"LGDst1Flag/O");
  tree->Branch("LGTrgTiming",&trg_lg_hit_t,"LGTrgTiming/F");
  tree->Branch("LGTrg",&lgtrg,"LGTrg/O");
  tree->Branch("LGTrgwTRK",&lgtrgwtrk,"LGTrgwTRK/O");

  auto& calib = E16ANA_CalibDBManager::Instance();
  calib.SetRunID(run_id);
#ifdef TRG_ON
  E16ANA_TriggerCalibParam trigger_param;
  trigger_param.ReadConstantData(calib.CurrentRunID());
  bool TrigIsAWmax = trigger_param.IsMaximumWidth();
  int TrigAWmax = trigger_param.MaximumWidth();
  int TrigAWmin = trigger_param.MinimumWidth();
  int TrigTW = trigger_param.TimeWidth();
  if(!TrigIsAWmax){TrigAWmax=10000;}
  std::cout<<TrigIsAWmax<<" "<<TrigAWmax<<" "<<TrigAWmin<<" "<<TrigTW<<std::endl;
#else
  bool TrigIsAWmax = false;
  int TrigAWmax = -10000;
  int TrigAWmin = -10000;
  int TrigTW = -10000;
#endif

  // E16ANA_GTRcalibPedestal gtrped;
  // gtrped.ReadCalibData( calib.CurrentRunID() );
  E16ANA_LGBasic lgbasic;
  E16ANA_LGDeadChannel lgdead;
  lgbasic.SetMap();
  lgbasic.SetCalibMap();//it is necessary to use energy deposit and calibrated timing.
  lgbasic.SetTemplate();
  lgdead.ReadDeadChannelData();
  E16ANA_CTBasic ctbasic;
  ctbasic.SetMap();

  auto geometry = new E16ANA_GeometryV2(static_cast<std::string>(GeometryFile));
  
  // auto record = new E16DST_DST1PhysicsRecord();
  auto dst0 = new E16DST_DST0();
  if (!dst0->Open(in_file_name, E16DST_DST0::ReadMode)) {
    std::cerr << "### Cannot open file ###" << std::endl;
    return -1;
  }
  E16DST_DST1PhysicsRecord record;

  // auto *lghists = new E16ANA_LGCheckHist();
  auto *cthists = new E16ANA_CTCheckHist();

  int n_event = 0;
  int n_physics_event = 0;
  while (dst0->ReadAnEvent()) {
    if (max_event != -1 && n_physics_event >= max_event) {
      break;
    }
    if (n_event % 1000 == 0) {
      cout << "Number of event: " << n_event << endl;
    }
    auto event_type = dst0->EventType();
    if (event_type == E16DST_DST0EventType::Physics) {
      auto event0 = dynamic_cast<E16DST_DST0PhysicsEvent*>(dst0->Event());
      // frun<<"Physics:"<<event0->RunNumber()<<" "<<event0->SpillID()<<" "<<event0->EventIDInSpill()<<" "<<event0->EventID()<<" "<<event0->UnixTime()<<" "<<event0->TimeStamp()<<" "<<event0->TimeStampInSpill()<<std::endl;
      // auto& ssd_hits0         = event0->SSD();
      // auto& gtr_hits0         = event0->GTR();
      // auto& hbd_hits0         = event0->HBD();
      auto& ct_hits0          = event0->CT();
      auto& lg_hits0          = event0->LG();
      auto& trigger_gtr_hits0 = event0->TriggerGTR();
      auto& trigger_hbd_hits0 = event0->TriggerHBD();
      auto& trigger_ct_hits0  = event0->TriggerCT();
      auto& trigger_lg_hits0  = event0->TriggerLG();
      // std::cout<<event0->LG().NumberOfHits()<<" "<<event0->TriggerLG().NumberOfHits()<<std::endl;
      auto event_id = event0->EventID();

#ifdef LGDST1_ON
      E16DST_DST1LGFactory(lg_hits0, &record.LG(), 0, geometry); // w/ fit
      record.LG().AddHitAndClusterIds();
      record.LG().UpdatePtrs();
#endif
#ifdef TRG_ON
#ifdef TMP_NIM_TRIGGER
      auto time_stamp = event0->TimeStamp();
      E16DST_DST1TriggerFactory(time_stamp, trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record.Trigger());
#else // TMP_NIM_TRIGGER
      E16DST_DST1TriggerFactory(trigger_param, event0->TriggerGTR(), event0->TriggerHBD(), event0->TriggerLG(), event0->UT3(), &record.Trigger());
#endif // TMP_NIM_TRIGGER
      record.Trigger().AddHitAndClusterIDs();
      record.Trigger().UpdatePtrs();
#endif

//// Check begin
//// LG

//run
      run = run_id;
      event = event0->EventID();
      spill = event0->SpillID();
      timestampinspill = event0->TimeStampInSpill();
      int slflag = event0->UT3().NIMFlag(0);
      int srflag = event0->UT3().NIMFlag(1);
      int sl2flag = event0->UT3().NIMFlag(0);//to be updated!!!!
      int sr2flag = event0->UT3().NIMFlag(1);//to be updated!!!!
      int im3flag = event0->UT3().NIMFlag(6);
      int im2flag = event0->UT3().NIMFlag(6);//to be updated!!!!
      if(slflag==0 ){sl  = false;} else{sl  = true;}
      if(srflag==0 ){sr  = false;} else{sr  = true;}
      if(sl2flag==0){sl2 = false;} else{sl2 = true;}
      if(sr2flag==0){sr2 = false;} else{sr2 = true;}
      if(im3flag==0){im3 = false;} else{im3 = true;}
      if(im2flag==0){im2 = false;} else{im2 = true;}

      int n_dst1hits = 0;
      int n_dst1trghits = 0;
      bool dst1hitflag[10][56];
      bool dst1trghitflag[10][56];
      float dst1trghitt[10][56];
      bool dst1trgtrkhitflag[10][56];
      for(int i=0;i<10;i++){
	for(int j=0;j<56;j++){
	  dst1hitflag[i][j] = false;
	  dst1trghitflag[i][j] = false;
	  dst1trghitt[i][j] = -10000.;
	  dst1trgtrkhitflag[i][j] = false;
	}
      }

//dst1hit
#ifdef LGDST1_ON
      auto& lg_hits1 = record.LG().Hits();
      int n_lghits = lg_hits1.size();
      if (lg_hits1.size() != 0) {
      	for(int i=0;i<n_lghits;i++){
      	  auto& lghit = lg_hits1[i];
      	  int tmod = lghit.ModuleId();
      	  int tblk = lghit.ChannelId();
	  if(lghit.PeakHeight()>30){//!!!!!!!!!!!!!!!!!!!!!!
	    dst1hitflag[tmod-100][tblk] = true;
	    n_dst1hits++;
	  }
      	}
      }
#endif

//dst1trghit
      int n_trg_lg_hits = record.Trigger().NumLGHits();
      for(int itrg=0;itrg<n_trg_lg_hits;itrg++){
	auto& trghit = record.Trigger().LGHit(itrg);
	int tmod = trghit.ModuleId();
	int tblk = trghit.ChannelId();
	dst1trghitflag[tmod-100][tblk] = true;
	dst1trghitt[tmod-100][tblk] = trghit.Timing();
	// if(trghit.Timing()>3120&&trghit.Timing()<3150){//!!!!!!!!!!!!!!!!!!!!!!
	  n_dst1trghits++;
	// }
      }

      int n_trg_tracks = record.Trigger().NumTrackSets();
      for(int i=0;i<n_trg_tracks;i++){
	auto& track_set1 = record.Trigger().TrackSet(i);
	auto& trghit1 = record.Trigger().LGHit(track_set1.LGHitOrder(0));
	for(int j=i+1;j<n_trg_tracks;j++){
	  auto& track_set2 = record.Trigger().TrackSet(j);
	  auto& trghit2 = record.Trigger().LGHit(track_set2.LGHitOrder(0));
	  int tmod1 = trghit1.ModuleId();
	  int tblk1 = trghit1.ChannelId();
	  float tt1 = trghit1.Timing();
	  int tmod2 = trghit2.ModuleId();
	  int tblk2 = trghit2.ChannelId();
	  float tt2 = trghit2.Timing();
	  int d1x = (tmod1-100)*7+(tblk1)%10;
	  int d1y = (tblk1)/10;
	  int d2x = (tmod2-100)*7+(tblk2)%10;
	  int d2y = (tblk2)/10;
	  int dist = (d2x-d1x)*(d2x-d1x)+(d2y-d1y)*(d2y-d1y);
	  if( (tt1==0||tt2==0) && fabs(tt1-tt2)<TrigTW && dist>TrigAWmin && dist<TrigAWmax ){
	    dst1trgtrkhitflag[tmod1-100][tblk1];
	    dst1trgtrkhitflag[tmod2-100][tblk2];
	  }
	}
      }

//cthit
      const int CTNMOD = E16ANA_CTCheckHist::GetNMOD();
      const int CTNCH = E16ANA_CTCheckHist::GetNCH();
      int ctpeaktimeall[CTNMOD][CTNCH];
      float ctpeakheightall[CTNMOD][CTNCH];
      float cttimingall[CTNMOD][CTNCH];
      float ctbaselineall[CTNMOD][CTNCH];
      float ctbaselinermsall[CTNMOD][CTNCH];
      double ctwaveformall[CTNMOD][CTNCH][E16DST_Constant::NSamplesCT];
      for (int n_hit = 0; n_hit < ct_hits0.NumberOfHits(); ++n_hit) {
	auto hit0 = ct_hits0.Hit(n_hit);
	uint16_t ctmodule = hit0.ModuleID();
	uint16_t ctblock = hit0.ChannelID();

	auto ctspec = ctbasic.GetSpec(ctmodule,ctblock);
	double wftype = ctspec->WF_TYPE;

	double wf[E16DST_Constant::NSamplesCT];
	for(int cell=0; cell<E16DST_Constant::NSamplesCT; cell++){
	  int ph = hit0.Waveform()[cell];
	  wf[cell] = ph;
	}
	E16ANA_LGWaveform::RemoveSpike(wf);
	for(int cell=0; cell<E16DST_Constant::NSamplesCT; cell++){
	  wf[cell] = wf[cell]*wftype;
	}

	E16ANA_CTWaveform* ctwf = new E16ANA_CTWaveform();
	ctwf->SimpleMethod(wf); // 700 event/sec @1e10

	int index_m = E16ANA_CTCheckHist::ModuleToIndex((int)ctmodule);
	int index_b = E16ANA_CTCheckHist::BlockToIndex((int)ctmodule,(int)ctblock);
	ctpeaktimeall[index_m][index_b] = ctwf->GetPeakx();
	cttimingall[index_m][index_b] = ctwf->GetTiming();
	ctpeakheightall[index_m][index_b] = ctwf->GetPeak();
	ctbaselineall[index_m][index_b] = ctwf->GetBaseline();
	ctbaselinermsall[index_m][index_b] = ctwf->GetBaselineRms();
	for(int cell=0; cell<E16DST_Constant::NSamplesCT; cell++){
	  ctwaveformall[index_m][index_b][cell] = wf[cell];
	}

	delete ctwf;

      }

//dst0hit
      for (int n_hit = 0; n_hit < lg_hits0.NumberOfHits(); ++n_hit) {
	auto hit0 = lg_hits0.Hit(n_hit);
	lgmodule = hit0.ModuleID();
	lgblock = hit0.BlockID();

	if( !E16ANA_CTCheckHist::LGwCT((int)lgmodule, (int)lgblock) ){
	  continue;
	}

	auto lgspec = lgbasic.GetSpec(lgmodule,lgblock);
	double wftype = lgspec->WF_TYPE;

	for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
	  int ph = hit0.Waveform()[cell];
	  lgwaveform[cell] = ph;
	}
	E16ANA_LGWaveform::RemoveSpike(lgwaveform);
	for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
	  lgwaveform[cell] = lgwaveform[cell]*wftype;
	}

	E16ANA_LGWaveform* lgwf = new E16ANA_LGWaveform();
	lgwf->SimpleMethod(lgwaveform); // 700 event/sec @1e10

	lgtiming = lgwf->GetTiming();
	lgpeakheight = lgwf->GetPeak();
	lgpeaktime = lgwf->GetPeakx();
	lgbaseline = lgwf->GetBaseline();
	lgbaselinerms = lgwf->GetBaselineRms();

	lgdst1flag = dst1hitflag[lgmodule-100][lgblock];
	lgtrg = dst1trghitflag[lgmodule-100][lgblock];
	lgtrgwtrk = dst1trgtrkhitflag[lgmodule-100][lgblock];
	trg_lg_hit_t = dst1trghitt[lgmodule-100][lgblock];

	//ct0
	ct0module = E16ANA_CTCheckHist::LGToCT0Module((int)lgmodule);
	ct0block  = E16ANA_CTCheckHist::LGToCT0Block((int)lgmodule,(int)lgblock);
	if( E16ANA_CTCheckHist::IsValidBlockId(ct0module,ct0block) ){
	  int index_m0 = E16ANA_CTCheckHist::ModuleToIndex(ct0module);
	  int index_b0 = E16ANA_CTCheckHist::BlockToIndex(ct0module,ct0block);
	  ct0timing = cttimingall[index_m0][index_b0];
	  ct0peakheight = ctpeakheightall[index_m0][index_b0];
	  ct0peaktime = ctpeaktimeall[index_m0][index_b0];
	  ct0baseline = ctbaselineall[index_m0][index_b0];
	  ct0baselinerms = ctbaselinermsall[index_m0][index_b0];
	  for(int cell=0; cell<E16DST_Constant::NSamplesCT; cell++){
	    ct0waveform[cell] = ctwaveformall[index_m0][index_b0][cell];
	  }
	}
	else{
	  ct0timing = -10000.;
	  ct0peakheight = -10000.;
	  ct0peaktime = -10000;
	  ct0baseline = -10000.;
	  ct0baselinerms = -10000.;
	  for(int cell=0; cell<E16DST_Constant::NSamplesCT; cell++){
	    ct0waveform[cell] = -10000.;
	  }
	}

	//ct1
	ct1module = E16ANA_CTCheckHist::LGToCT1Module((int)lgmodule);
	ct1block  = E16ANA_CTCheckHist::LGToCT1Block((int)lgmodule,(int)lgblock);
	if( E16ANA_CTCheckHist::IsValidBlockId(ct1module,ct1block) ){
	  int index_m1 = E16ANA_CTCheckHist::ModuleToIndex(ct1module);
	  int index_b1 = E16ANA_CTCheckHist::BlockToIndex(ct1module,ct1block);
	  ct1timing = cttimingall[index_m1][index_b1];
	  ct1peakheight = ctpeakheightall[index_m1][index_b1];
	  ct1peaktime = ctpeaktimeall[index_m1][index_b1];
	  ct1baseline = ctbaselineall[index_m1][index_b1];
	  ct1baselinerms = ctbaselinermsall[index_m1][index_b1];
	  for(int cell=0; cell<E16DST_Constant::NSamplesCT; cell++){
	    ct1waveform[cell] = ctwaveformall[index_m1][index_b1][cell];
	  }
	}
	else{
	  ct1timing = -10000.;
	  ct1peakheight = -10000.;
	  ct1peaktime = -10000;
	  ct1baseline = -10000.;
	  ct1baselinerms = -10000.;
	  for(int cell=0; cell<E16DST_Constant::NSamplesCT; cell++){
	    ct1waveform[cell] = -10000.;
	  }
	}

	tree->Fill();

	// if(peakheight>20&&trg_lg_hit_t>3050&&trg_lg_hit_t<3200){
	// if(peakheight>25&&peakheight<180&&trg_lg_hit_t>3120&&trg_lg_hit_t<3150){
	// if(peakheight>25&&peakheight<180&&dst1flag&&timing>70&&timing<130){//tmp, wotrg
	// if(dst1flag){
	// if(trg_lg_hit_t==0&&ct0peakheight>20.){
	if(trg_lg_hit_t==0){
	  cthists->Fill(ct0module,ct0block,ct0peakheight,ct0peaktime,ct0timing,ct0baseline,ct0baselinerms,-10000.,-10000);
	}
	// if(trg_lg_hit_t==0&&ct1peakheight>20.){
	if(trg_lg_hit_t==0 && E16ANA_CTCheckHist::IsValidBlockId(ct1module,ct1block)){
	  cthists->Fill(ct1module,ct1block,ct1peakheight,ct1peaktime,ct1timing,ct1baseline,ct1baselinerms,-10000.,-10000);
	}
	if(ct0peakheight>50.){
	  cthists->FillNhits(ct0module,ct0block,1);
	}
	else{
	  cthists->FillNhits(ct0module,ct0block,0);
	}
	if(ct1peakheight>50.){
	  cthists->FillNhits(ct1module,ct1block,1);
	}
	else{
	  cthists->FillNhits(ct1module,ct1block,0);
	}
	// if(trg&&trg_lg_hit_t!=0){
	  // cthists->FillTimeCorrelation(module,block,peaktime,trg_lg_hit_t);
	// }
	// if(trg_lg_hit_t==0){
	// if(dst1flag&&peakheight>30.){
	//   lghists->SetWaveform(module,block,waveform);
	// }

	delete lgwf;

      }

    } else if (event_type == E16DST_DST0EventType::Scaler) {
      auto event0 = dynamic_cast<E16DST_DST0ScalerEvent*>(dst0->Event());
      // frun<<"Scaler: "<<event0->RunNumber()<<" "<<event0->SpillID()<<" "<<event0->EventIDInSpill()<<" "<<event0->EventID()<<" "<<event0->UnixTime()<<" "<<event0->TimeStamp()<<" "<<event0->TimeStampInSpill()<<std::endl;
//      dst1->WriteAnEvent(event0);
    } else if (event_type == E16DST_DST0EventType::SpillStart) {
      auto event0 = dynamic_cast<E16DST_DST0SpillStartEvent*>(dst0->Event());
      // frun<<"SpillS: "<<event0->RunNumber()<<" "<<event0->SpillID()<<" "<<event0->EventIDInSpill()<<" "<<event0->EventID()<<" "<<event0->UnixTime()<<" "<<event0->TimeStamp()<<" "<<event0->TimeStampInSpill()<<std::endl;
//      dst1->WriteAnEvent(event0);
    } else if (event_type == E16DST_DST0EventType::SpillEnd) {
      auto event0 = dynamic_cast<E16DST_DST0SpillEndEvent*>(dst0->Event());
      // frun<<"SpillE: "<<event0->RunNumber()<<" "<<event0->SpillID()<<" "<<event0->EventIDInSpill()<<" "<<event0->EventID()<<" "<<event0->UnixTime()<<" "<<event0->TimeStamp()<<" "<<event0->TimeStampInSpill()<<std::endl;
//      dst1->WriteAnEvent(event0);
    } else {
      std::cerr << "Invalid Event Type: " << event_type << std::endl;
      return -1;
    }
    ++n_event;
    ++n_physics_event;
  }

  TString pdfout = Form("%s",out_pdf_name);
  TCanvas* c = new TCanvas("c","c",1400,700);
  c->SaveAs(pdfout+"[","pdf");
  cthists->Draw(pdfout,c);
  cthists->Draw2D(pdfout,c);
  cthists->DrawEach(pdfout,c);
  // cthists->DrawEachTimeCorrelation(pdfout,c);
  c->SaveAs(pdfout+"]","pdf");

  // TString wfpdfout = Form("%s",out_wf_pdf_name);
  // lghists->DrawWaveform(wfpdfout);

  fout->Write();
  fout->Close();

  delete geometry;
  delete dst0;
//  dst1->Close();
  return 0;
}
