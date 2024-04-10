#include "E16ANA_EIDEfficiency.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLine.h>

#include <TH1.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "TROOT.h"

int main(int argc, char* argv[]) {

  auto runtype = stoi(argv[1]);
  auto out_file_name = argv[2];
  auto out_root_name = argv[3];
  auto maxevent = stoi(argv[4]);
  auto in_file_name = argv[5];
  double hbdthr=-10000.;
  int hbdclthr=-10000;
  if(argc==8){
    hbdthr = stod(argv[6]);
    hbdclthr = stoi(argv[7]);
  }

  bool input=false;
  if(argc==5&&strlen(out_file_name)>4&&strlen(out_root_name)>5){
    //default
    input=false;
  }
  else if(argc==6&&strlen(out_file_name)>4&&strlen(out_root_name)>5&&strlen(in_file_name)>5){
    //supply input file
    input=true;
  }
  else if(argc==8&&strlen(out_file_name)>4&&strlen(out_root_name)>5&&strlen(in_file_name)>5){
    //supply input file & hbd threshold
    input=true;
  }
  else if(argc==8&&strlen(out_file_name)>4&&strlen(out_root_name)>5&&strlen(in_file_name)<4){
    //supply hbd threshold
    input=false;
  }
  else{
    std::cerr << "./bin [Ks:0, vmeson:1, eIDrev:3, eIDfwd:4] [out.pdf] [out.root] [maxevent]" << std::endl;
    return -1;
  }
   
  auto in_chain = new TChain("tree", "tree");

  if(argc==5||!input){
    if(runtype==0){
      // in_chain->Add("./out/root03a/trackselection_chisq30_fflag01.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root03a/trackselection_prod220212_chisq30.root");
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/rootphi/v60/*.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/rootphi/v58/track_run020928.root");
    }
    else if(runtype==1){
      // in_chain->Add("./out/root/trackselection_5e9*.root");
      // in_chain->Add("./out/root/trackselection_5e9rev_prod220131.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_5e9rev_prod220131_chisq20_modall_morino.root");
      //*******
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/v30/*.root");//vmeson
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/v33/*.root");//trigger study
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/v31/*.root");//trigger study
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDadd_22033101.root");//eID(LG+)
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDcalib_22031701.root");//eID(LG)
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDcalib_prod220216_22033104.root");//eID(HBD)
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDcalib_22032501.root");//gas
      //*******
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/rootphi/v36/*.root");//vmeson; production new
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/rootphi/v57/*.root");
    }
    else if(runtype==2){
      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_1e9FM*.root");
    }
    else if(runtype==3){
      // in_chain->Add("./out/root03a/trackselection_eIDcalib_chisq20_fflag01.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root03a/trackselection_eIDcalib_chisq20.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDadd_22033101.root");//eID(LG+)
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDcalib_22031701.root");//eID(LG)
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDcalib_prod220216_22033104.root");//eID(HBD)
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/trackselection_eIDcalib_22032501.root");//gas

      in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/v56/*.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/v59/track_run0302*.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/v59/track_run030300.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/v59/track_run030301.root");
      // in_chain->Add("/ccj/u/nakasuga/work/dst1ana/track/out/root/v59/track_run030302.root");
    }
  }
  else if(argc==6||argc==8){
    in_chain->Add(in_file_name);
  }


  E16ANA_EIDEfficiency* t = new E16ANA_EIDEfficiency(in_chain);
  if(argc!=8){
    if(runtype==1){hbdthr=7.;hbdclthr=2;}
    if(runtype==3){hbdthr=4.;hbdclthr=1;}
    if(runtype==0){hbdthr=0.;hbdclthr=1;}
    if(runtype==4){hbdthr=0.;hbdclthr=1;}
  }
  t->ResidualandEfficiency(runtype,maxevent,out_file_name,out_root_name,hbdthr,hbdclthr);
  
  delete in_chain;
  return 0;

}
