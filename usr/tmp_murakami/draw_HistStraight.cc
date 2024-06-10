#include "E16DSTN_ReStraightV2.hh"

int main (int argc, char** argv) {
	if(argc != 6){
		std::cout << "./bin/~~ [input.root] [output.root] [maxevent] [residual_layer] [pdf_name]" << std::endl;
		return 0;	
	}
   std::string in_file   = argv[1];
	std::string out_file  = argv[2];
	int         maxevent  = stoi(argv[3]);
	int         residual_layer      = stoi(argv[4]);
	TString pdf_name      = argv[5];
//   const char *dirname = "/work22/E16/mtomoki/run0c_wire/230929-wire-v1/afterkill_root/";
//
//
//
  TFile *fin = new TFile(in_file.c_str());
  TTree *tree = (TTree*)fin->Get("tree");

//	TFile *fin           = new TFile(in_file.c_str());
//	TTree *tree          = (TTree*)fin->Get("outtree");
	std::vector<TVector3> dummy;
	E16DSTN_ReStraightV2 *rt = new E16DSTN_ReStraightV2(tree, out_file.c_str(), nullptr, nullptr, dummy);//initialize
	int print_cycle      = 1000;
   
	rt->DrawHist(tree, maxevent,  print_cycle, residual_layer, pdf_name);
	
	return 0;	
}

