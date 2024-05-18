#define E16DSTN_ReadStraightTree_cxx
#include "E16DSTN_ReadStraightTree.hh"
#include "E16DSTN_StraightParameter.hh"
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
//#include "straightRoot.hh"
#include "E16ANA_CalibDBManager.hh"


int main (int argc, char** argv) {
	if(argc != 6){
		std::cout << "./bin/~~ [input.root] [output.root] [max_analyzed_event] [tgtSW (0=Extargets, 1=wire)] [removed_layer]" << std::endl;
		return 0;	
	}
	std::string in_file  = argv[1];
	std::string out_file = argv[2];
	int max_event        = stoi(argv[3]);
	int tgtSW            = stoi(argv[4]);
	int removed_layer    = stoi(argv[5]);
	TFile *fin           = new TFile(in_file.c_str());
	TTree *tree          = (TTree*)fin->Get("tree");
	E16DSTN_ReadStraightTree *rt = new E16DSTN_ReadStraightTree(tree, out_file.c_str());
	if(tgtSW != 1 ){
		std::cout << "Experimental targets ver has not been developed yet " << std::endl;
	}
	rt->SetTgtKind(tgtSW);
	rt->SetRemovedLayer(removed_layer);
	int nevent           = tree->GetEntries();
	int print_cycle      = 1;
	rt->Loop(tree, print_cycle, max_event);
	rt->FileOut()->Write();
	return 0;	
}





