#include <iostream>
#include <fstream>
#include <string>

#include "E16ANA_ErrorMessage.hh"
#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_SSDcalib.hh"

using namespace std;

int main(int argc, char* argv[]){

  std::string txt = ".txt";
  std::string date1 = argv[1];
  std::string date2 = argv[2];
  std::string filepath1 = "/e16/u/arimizu/calibdata/run0c/VME01/MeanRms_2021";
  std::string filepath2 = "/e16/u/arimizu/calibdata/run0c/VME02/MeanRms_2021";
  std::string filename1 = filepath1 + date1 + txt;
  std::string filename2 = filepath2 + date2 + txt;

  std::string dat = ".dat";
  std::string pedestal_run0c = "pedestal_run0c_";
  std::string file_number = argv[3];
  std::string output_filename = pedestal_run0c + file_number + dat;

  std::ifstream ifs1; //R side
  std::ifstream ifs2; //L side
  ifs1.open(filename1.c_str());
  if(ifs1.fail()){
    std::cerr << "fail to open file1" << std::endl;
  }
  ifs2.open(filename2.c_str());
  if(ifs2.fail()){
    std::cerr << "fail to open file2" << std::endl;
  }

  const int n_APVmodule = 6;// APVDAQ-module for each(L/R) side
  const int n_chip_half = 3;// APV chip for an APVDAQ-module
  const int n_strip = 128;
  const int n_sample = 8;

  //apvmodule[0-5], apvchip[0-2], strip[0-127], sample[0-7] ped/sigma
  double ped1  [n_APVmodule][n_chip_half][n_strip][n_sample]={0};
  double sigma1[n_APVmodule][n_chip_half][n_strip][n_sample]={0};
  double ped2  [n_APVmodule][n_chip_half][n_strip][n_sample]={0};
  double sigma2[n_APVmodule][n_chip_half][n_strip][n_sample]={0};

  for(int APVmodule=0; APVmodule<n_APVmodule; APVmodule++){
    for(int chip=0; chip<n_chip_half; chip++){
      for(int strip=0; strip<n_strip; strip++){
	for(int sample=0; sample<n_sample; sample++){
	  ifs1 >> ped1[APVmodule][chip][strip][sample] >> sigma1[APVmodule][chip][strip][sample];
	  ifs2 >> ped2[APVmodule][chip][strip][sample] >> sigma2[APVmodule][chip][strip][sample];
	}
      }
    }
  }

  const int n_module = 6;//SSD sensor
  const int n_module_half = 3;//SSD sensor for each(L/R) side
  const int n_chip = 6;// APV chip for a SSD sensor
  
  double ped_mod  [n_module][n_chip*n_strip][n_sample];
  double sigma_mod[n_module][n_chip*n_strip][n_sample];

  for(int APVmodule=0; APVmodule<n_APVmodule; APVmodule++){
    for(int chip=0; chip<n_chip_half; chip++){
      for(int strip=0; strip<n_strip; strip++){
	for(int sample=0; sample<n_sample; sample++){
	  int i = (APVmodule-APVmodule%2)/2;
	  int j = (n_chip_half*(APVmodule%2)+chip)*n_strip + strip;
	  //R side 
	  ped_mod  [i][j][sample] = ped1  [APVmodule][chip][strip][sample];
	  sigma_mod[i][j][sample] = sigma1[APVmodule][chip][strip][sample];
	  //L side
	  ped_mod  [i + n_module_half][j][sample] = ped2  [APVmodule][chip][strip][sample];
	  sigma_mod[i + n_module_half][j][sample] = sigma2[APVmodule][chip][strip][sample];

	  // cout << "R-ped["<<i<<"]["<<j<<"]["<<sample<<"]=" << ped_mod[i][j][sample] << endl;
	  // cout << "R-sigma["<<i<<"]["<<j<<"]["<<sample<<"]=" << sigma_mod[i][j][sample] << endl;
	  // cout << "L-ped["<<i+n_module_half<<"]["<<j<<"]["<<sample<<"]=" << ped_mod[i+n_module_half][j][sample] << endl;
	  // cout << "L-sigma["<<i+n_module_half<<"]["<<j<<"]["<<sample<<"]=" << sigma_mod[i+n_module_half][j][sample] << endl;
	}
      }
    }
  }

  for(int i=0;i<6;i++){
    for(int j=0;j<768;j++){
      for(int k=0;k<8;k++){
  	cout << "ped["<<i<<"]["<<j<<"]["<<k<<"]=" << ped_mod[i][j][k] << endl;
      }
    }
  }
  for(int i=0;i<6;i++){
    for(int j=0;j<768;j++){
      for(int k=0;k<8;k++){
  	cout << "sigma["<<i<<"]["<<j<<"]["<<k<<"]=" << sigma_mod[i][j][k] << endl;
      }
    }
  }

  E16ANA_SSDcalibPedestal ssdped;
  ssdped.WriteCalibData(output_filename.c_str(), (double***)ped_mod, (double***)sigma_mod);


  return 0;

}

