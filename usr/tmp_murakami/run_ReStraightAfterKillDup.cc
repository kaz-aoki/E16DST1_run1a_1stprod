//#define E16DSTN_ReadStraightTree_cxx
#define E16DSTN_PosCorrection_cxx
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
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TVector3.h"
#include <vector>
//#include "TMLocal_StraightAnalyzer.hh"
#include "E16ANA_GeometryV2.hh"
#include "E16ANA_StraightTrackNameSpace.hh"
#include "E16ANA_StraightTrack.hh"
#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"
#include "E16ANA_LGConstant.hh"
#include "E16ANA_LGDeadChannel.hh"
#include "E16ANA_LGClustering.hh"
#include "E16ANA_LGStraightProj.hh"
//#include "straightRoot.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16DSTN_PosCorrection.hh"
#include "E16DST_DST1DefaultFilePath.hh.in"


int main (int argc, char** argv) {
	if(argc != 5){
		std::cout << "./bin/~~ [input.root] [output.root] [max_analyzed_event] [removed_layer]" << std::endl;
		return 0;	
	}
	std::string in_file  = argv[1];
	std::string out_file = argv[2];
	int max_event        = stoi(argv[3]);
	int removed_layer    = stoi(argv[4]);
	TFile *fin           = new TFile(in_file.c_str());
	TTree *tree          = (TTree*)fin->Get("outtree");
	//E16DSTN_ReadStraightTree *rt = new E16DSTN_ReadStraightTree(tree, out_file.c_str());
	//rt->SetRemovedLayer(removed_layer);
	E16DSTN_PosCorrection *pc = new E16DSTN_PosCorrection(tree, out_file.c_str());
	int nevent           = tree->GetEntries();
	int print_cycle      = 1000;
	bool vertex_xy_fix_flag = false;
   bool py_fix_flag = false;
	bool vetex_z_fix_flag = false;
	bool isWire = true;
	auto geom = new E16ANA_GeometryV2(static_cast <std::string>(GeometryFile));
	std::cout << static_cast<std::string>(GeometryFile) << std::endl;
	pc->SetGeom(geom);
	E16ANA_StraightMultiTrack *fitter = new E16ANA_StraightMultiTrack(geom, 1);
	pc->SetFitter(fitter);
	pc->SetRemovedLayer(removed_layer);
	pc->PosCoLoop(tree, print_cycle, max_event, vertex_xy_fix_flag, py_fix_flag, vetex_z_fix_flag, isWire );
	pc->FileOut()->Write();
	return 0;	
}





