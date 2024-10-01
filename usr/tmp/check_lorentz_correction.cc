#include "E16ANA_CalibDBManager.hh"
#include "E16ANA_GTRLorentzCorrection.hh"

int main(int argc, char **argv){
   if (argc < 3) {
      std::cout << "Usage: " << argv[0] << " {run_id} {module_id}" << std::endl;
      return 0;
   }
   int run_id = atoi(argv[1]);
   int module_id = atoi(argv[2]);
   auto &calib = E16ANA_CalibDBManager::Instance();
   calib.SetRunID(run_id);
   auto &lc_manager = E16ANA_GTRLorentzCorrectionManager::Instance();

   auto check = [&](int m, int l){
      std::cout << m << "-Layer" << l << std::endl;
      for (int i=0; i<6; i++) {
         for (int j=0; j<6; j++) {
            TVector3 lpos((i*20-50)*(l+1), (j*20-50)*(l+1), 0);
            //TVector3 corrected_lpos = lc_manager.CorrectLocalPos(m,l,lpos,180,TVector3(0.1,0,1));
            //corrected_lpos.Print();
            lc_manager.PrintParams(m,l,lpos);
         }
      }
   };
#if 0
   check(103,0);
   check(103,1);
   check(103,2);
   check(104,0);
   check(104,1);
   check(104,2);
#endif
   check(module_id,0);
   check(module_id,1);
   check(module_id,2);
   return 0;
}
