#define E16DSTN_ReadStraightTree_cxx

#include "E16DSTN_ReadStraightTree.hh"
#include <string>
#include <map>
#include <array>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TROOT.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "TH1F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TVector3.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "math.h"
#include "unistd.h"
#include "TLegend.h"
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TLorentzVector.h"
#include "TVector.h"
#include "G4ThreeVector.hh"
#include <TCanvas.h>
#include <TStyle.h>
#include <algorithm>
#include <vector>
#include <TLatex.h>
//#include "TMLocal_StraightAnalyzer.hh"
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_StraightTrackNameSpace.hh"
#include "E16ANA_StraightTrack.hh"
#include "StraightTrackAnalyzerV0.h"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"
#include "E16ANA_LGConstant.hh"
#include "E16ANA_LGDeadChannel.hh"
#include "E16ANA_LGClustering.hh"
#include "E16ANA_LGStraightProj.hh"
#include "straightRoot.hh"
#include "E16ANA_CalibDBManager.hh"
#include <dirent.h>


int main (int argc, char** argv) {
	if(argc != 5){
		std::cout << "./bin/~~ [input_dir] [output.root] [maxevent] [pdf_name]" << std::endl;
		return 0;	
	}
	const char *dirname    = argv[1];
	std::string out_file = argv[2];
	int         maxevent    = stoi(argv[3]);
	TString pdf_name     = argv[4];
	TChain *chain        = new TChain("tree");
//   const char *dirname = "/work22/E16/mtomoki/run0c_wire/230929-wire-v1/afterkill_root/";
   DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(dirname)) != NULL) {
      while ((ent = readdir(dir)) != NULL) {
         TString filename = ent->d_name;
         if (filename.EndsWith(".root")) {
            TString filepath = TString::Format("%s/%s", dirname, filename.Data());
				std::cout << "Reading root file : " << filepath << std::endl;
            chain->Add(filepath);
         }
      }
        closedir(dir);
    } else {
        std::cout << "Could not open directory: " << dirname << std::endl;
        return 1;
    }

//	TFile *fin           = new TFile(in_file.c_str());
//	TTree *tree          = (TTree*)fin->Get("outtree");
	E16DSTN_ReadStraightTree *rt = new E16DSTN_ReadStraightTree(chain, out_file.c_str());//initialize
	int nevent           = chain->GetEntries();
	int print_cycle      = 10000;
	rt->DrawHist(chain, maxevent,  print_cycle, pdf_name);
	return 0;	
}

