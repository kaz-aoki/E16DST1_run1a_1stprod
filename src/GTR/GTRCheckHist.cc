#include "GTR/GTRCheckHist.hh"
#include "TH1D.h"

GTRCheckHist::GTRCheckHist(){
    for(int m=100; m < 110; m++){
        for(int l=0; l<3; l++){
            h_cl_charge[m-100][l] = new TH1D(Form("cl_charge%d_%d",m, l), Form("cl_charge%d_%d",m, l),100, 0,3000);
            h_cl_local_x[m-100][l] = new TH1D(Form("cl_local_x%d_%d",m, l), Form("cl_local_x%d_%d",m, l),100, -50*(l+1), 50*(l+1));
            
           
        }
    }
}
GTRCheckHist::~GTRCheckHist(){
    
for(int m=100; m < 110; m++){
        for(int l=0; l<3; l++){
            delete h_cl_charge[m-100][l];
            delete h_cl_local_x[m-100][l];
        }
    }
}

void GTRCheckHist::Fill(E16DST_DST0Detector<E16DST_DST1GTRHit> *hits, E16DST_DST0Detector<E16DST_DST1GTRCluster> *clusters){
    std::cout << "cluster size : " << clusters->NumberOfHits() << std::endl;
    for(int i=0; i < clusters->NumberOfHits(); i++){
        E16DST_DST1GTRCluster &cl = clusters->Hit(i);
        if(cl.Type() == 0){
//        std::cout << "cluster id :: " << i << std::endl;
//        std::cout << "module id :: " << cl.ModuleId() << std::endl;
//        std::cout << "layer id :: " << cl.LayerId() << std::endl;
//        std::cout << "cluster charge :: " << cl.PeakSum() << std::endl;
        h_cl_charge[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.PeakSum());
        h_cl_local_x[cl.ModuleId()-100][cl.LayerId()]->Fill(cl.LocalX());
        }
    }
}
