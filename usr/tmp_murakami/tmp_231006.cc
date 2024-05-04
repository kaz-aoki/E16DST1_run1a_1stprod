

#include <TChain.h>
#include <TH1F.h>
#include <TFile.h>
#include <TString.h>
#include <iostream>
#include <dirent.h>  // For directory listing

int main() {
    // Define the directory containing the ROOT files
	const char *dirname = "/work22/E16/mtomoki/run0c_tmp_trackana/231002-trackana-v0/root/";
   // Define the name of the tree and branch
   const char *treeName =    "tree_em";
   const char *branchName  = "ee_mass";
   const char *branchName1 = "pipi_mass";
   const char *branchName2 = "pip_mass";
   const char *branchName3 = "kk_mass";
   const char *branchName4 = "ee_mass_at_best_tgt";
   const char *branchName5 = "pipi_mass_at_best_tgt";
   const char *branchName6 = "pip_mass_at_best_tgt";
   const char *branchName7 = "kk_mass_at_best_tgt";
   // Create a TChain to hold the data from all files
   TChain *chain = new TChain(treeName);
   // Add all ROOT files from the specified directory to the chain
	DIR *dir;
   struct dirent *ent;
   if ((dir = opendir(dirname)) != NULL) {
   	while ((ent = readdir(dir)) != NULL) {
      	TString filename = ent->d_name;
         if (filename.EndsWith(".root")) {
  				TString filepath = TString::Format("%s/%s", dirname, filename.Data());
            chain->Add(filepath);
         }
      }
    closedir(dir);
	} else {
         std::cout << "Could not open directory: " << dirname << std::endl;
    return 1;
   }
   // Check if the branch exists in the chain
             TBranch *branch = chain->FindBranch(branchName);
             TBranch *branch1= chain->FindBranch(branchName1);
             TBranch *branch2= chain->FindBranch(branchName2);
             TBranch *branch3= chain->FindBranch(branchName3);
             TBranch *branch4= chain->FindBranch(branchName4);
             TBranch *branch5= chain->FindBranch(branchName5);
             TBranch *branch6= chain->FindBranch(branchName6);
             TBranch *branch7= chain->FindBranch(branchName6);
                 if (!branch) {
                         std::cout << "Branch " << branchName << " not found!" << std::endl;
                                 return 1;
                         }
          // Create a histogram to hold the sum of the branch data
           TH1F *hist = new TH1F("hist",  "ee_mass", 100, 0, 2.5);  // Adjust binning as needed
           TH1F *hist1= new TH1F("hist1", "pipi_mass", 100, 0, 2.5);  // Adjust binning as needed
           TH1F *hist2= new TH1F("hist2", "pip_mass", 100, 0, 2.5);  // Adjust binning as needed
           TH1F *hist3= new TH1F("hist3", "kk_mass", 100, 0, 2.5);  // Adjust binning as needed
           TH1F *hist4= new TH1F("hist4", "ee_mass_best", 100, 0, 2.5);  // Adjust binning as needed
           TH1F *hist5= new TH1F("hist5", "pipi_mass_best", 100, 0, 2.5);  // Adjust binning as needed
           TH1F *hist6 = new TH1F("hist6", "pip_mass_best", 100, 0, 2.5);  // Adjust binning as needed
           TH1F *hist7 = new TH1F("hist7", "kk_mass_best", 100, 0, 2.5);  // Adjust binning as needed
               // Loop over all entries in the chain and fill the histogram
            std::vector<double> *branchValue = 0;
            std::vector<double> *branchValue1 = 0;
            std::vector<double> *branchValue2 = 0;
            std::vector<double> *branchValue3 = 0;
            std::vector<double> *branchValue4 = 0;
            std::vector<double> *branchValue5 = 0;
            std::vector<double> *branchValue6 = 0;
            std::vector<double> *branchValue7 = 0;
				chain->SetBranchAddress(branchName, &branchValue);
				chain->SetBranchAddress(branchName1, &branchValue1);
				chain->SetBranchAddress(branchName2, &branchValue2);
				chain->SetBranchAddress(branchName3, &branchValue3);
				chain->SetBranchAddress(branchName4, &branchValue4);
				chain->SetBranchAddress(branchName5, &branchValue5);
				chain->SetBranchAddress(branchName6, &branchValue6);
				chain->SetBranchAddress(branchName7, &branchValue7);
    			Long64_t nentries = chain->GetEntries();
        for (Long64_t i = 0; i < nentries; i++) {
                if(i%10000 == 0 ) std::cout << "event " << i << std::endl;
                chain->GetEntry(i);
					 for(int j=0; j< branchValue->size();j++){
                hist->Fill((*branchValue)[j]);
					}
					for(int j=0; j< branchValue1->size();j++){
                   hist1->Fill((*branchValue1)[j]);
					}
					for(int j=0; j< branchValue2->size();j++){
                   hist2->Fill((*branchValue2)[j]);
					}
					for(int j=0; j< branchValue3->size();j++){
                   hist3->Fill((*branchValue3)[j]);
					}
					for(int j=0; j< branchValue4->size();j++){
                   hist4->Fill((*branchValue4)[j]);
					}
					for(int j=0; j< branchValue5->size();j++){
                   hist5->Fill((*branchValue5)[j]);
					}
					for(int j=0; j< branchValue6->size();j++){
                   hist6->Fill((*branchValue6)[j]);
					}
					for(int j=0; j< branchValue7->size();j++){
                   hist7->Fill((*branchValue7)[j]);
					}

        }
// Save the histogram to a new ROOT file
     TFile *outfile = new TFile("output.root", "RECREATE");
     hist->Write();
     hist1->Write();
     hist2->Write();
     hist3->Write();
     hist4->Write();
     hist5->Write();
     hist6->Write();
     hist7->Write();
     outfile->Close();
// Cleanup
     delete hist;
     delete chain;
     delete outfile;

     return 0;
}

