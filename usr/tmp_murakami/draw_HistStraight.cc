#include "E16DSTN_ReStraightV2.hh"
#include <fstream>

int main (int argc, char** argv) {
	if(argc != 7){
		std::cout << "./bin/~~ [input_list.txt] [output.root] [start_ev] [end_ev] [residual_layer] [pdf_name]" << std::endl;
		return 0;	
	}
   std::string in_file   = argv[1];
	std::string out_file  = argv[2];
	int         start_event  = stoi(argv[3]);
	int         end_event  = stoi(argv[4]);
	int         residual_layer      = stoi(argv[5]);
	TString pdf_name      = argv[6];

	TChain *chain = new TChain("tree");
	std::string line;
	std::ifstream infile(in_file);
   if (!infile.is_open()) {
      std::cerr << "Error: Could not open "  << in_file << std::endl;
      return 0;
   }
   while (std::getline(infile, line)) {
           chain->Add(line.c_str());
   }
   infile.close();
   std::cout << "Number of files in TChain: " << chain->GetListOfFiles()->GetEntries() << std::endl;


//   TFile *fin = new TFile(in_file.c_str());
//   TTree *tree = (TTree*)fin->Get("tree");

//	TFile *fin           = new TFile(in_file.c_str());
//	TTree *tree          = (TTree*)fin->Get("outtree");
	std::vector<TVector3> dummy;
//	E16DSTN_ReStraightV2 *rt = new E16DSTN_ReStraightV2(tree, out_file.c_str(), nullptr, nullptr, nullptr, dummy);//initialize
	E16DSTN_ReStraightV2 *rt = new E16DSTN_ReStraightV2(chain, out_file.c_str(), nullptr, nullptr, nullptr, dummy);//initialize
	int print_cycle      = 1000;
   
	rt->DrawHist(chain, start_event, end_event,  print_cycle, residual_layer, pdf_name);
	
	return 0;	
}

