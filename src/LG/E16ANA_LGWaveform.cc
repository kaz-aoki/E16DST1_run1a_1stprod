#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <TH1.h>
#include <TGraph.h>
#include <TSpectrum.h>

#include "E16ANA_LGBasic.hh"
#include "E16ANA_LGWaveform.hh"
#include "E16DST_DST1Constant.hh"
#include "E16ANA_LGConstant.hh"

#include "E16ANA_CalibDBManager.hh"
#include "E16DST_DST1DefaultFilePath.hh"

#include <algorithm>
#include <unordered_map>   

using namespace E16ANA_LGConstant;


void E16ANA_LGWaveform::Peak(double* dat, double* peak, int* peakx, double* timing){

  for(int cell=5; cell<E16DST_Constant::NSamplesLG; cell++){//peak search
    if(dat[cell]>*peak){
      if( E16ANA_LGConstant::kPeakSearchStart<cell && cell<E16ANA_LGConstant::kPeakSearchEnd ){
	*peak = dat[cell];
	*peakx = cell;
      }
    }
  }//peak search

  for(int i=0;i<E16ANA_LGConstant::kTimingSearchRegion;i++){//timing search
    int cell = *peakx - i;
    double peakhalf = *peak/2.;
    if(cell<0||cell>E16DST_Constant::NSamplesLG){
      *timing=E16DST_DST1Constant::kInvalidValue;
      break;
    }
    if(dat[cell]>*peak){
      *timing=E16DST_DST1Constant::kInvalidValue;
      break;
    }
    if(!(cell==*peakx)&&dat[cell]<peakhalf){
      *timing=(peakhalf-dat[cell])*(1./E16ANA_LGConstant::kTimeScale)/(dat[cell+1]-dat[cell])+cell;
      if(cell==(*peakx-1)){//remove the event like spike noise
	*timing=-10000;
      }
      break;
    }
    }//timing search


}

void E16ANA_LGWaveform::Baseline(double* dat, int peakx, double* baseline, double* baselinerms){

  double baseline_sum = 0.;
  double baseline_sq_sum = 0.;
  int nb=0;
  for(int cell=(peakx+E16ANA_LGConstant::kBaselineStart); cell<(peakx+E16ANA_LGConstant::kBaselineEnd); cell++){
    if(cell<0||cell>E16DST_Constant::NSamplesLG){
      continue;
    }
    baseline_sum += dat[cell];
    baseline_sq_sum += dat[cell]*dat[cell];
    nb++;
  }
  *baseline = baseline_sum/(double)nb;
  *baselinerms = sqrt( baseline_sq_sum/(double)nb - (*baseline)*(*baseline) );

}

void E16ANA_LGWaveform::Integral(double* dat, int peakx, double baseline, double* integral, int* falltime){

  double integral_sum = 0.;
  bool peakcheck = false;
  int fallcount = 0;
  *falltime = peakx+E16ANA_LGConstant::kIntegralEnd;
  for(int cell=(peakx+E16ANA_LGConstant::kIntegralStart); cell<(peakx+E16ANA_LGConstant::kIntegralEnd); cell++){
    if(cell<0||cell>E16DST_Constant::NSamplesLG){
      integral_sum = E16DST_DST1Constant::kInvalidValue;
      *integral = E16DST_DST1Constant::kInvalidValue;
      return;
    }
    integral_sum += dat[cell]-baseline;
    if((dat[cell]-baseline)<(dat[peakx]-baseline)*0.1&&peakcheck==false&&cell>peakx){//get decay_time
      if(fallcount>1){
	std::cout<<"FalltimeSearch is failed."<<std::endl;
	continue;
      }
      *falltime = cell;
      fallcount += 1;
      if(fallcount>1){
	peakcheck=true;
      }
    }
  }//cell loop
  *integral = integral_sum/50./E16ANA_LGConstant::kTimeScale;//[pC]

}

int E16ANA_LGWaveform::PeakSearch(double* dat, double t0, double* mwf, double* peakxs, double* peakys){

  TH1F *h = new TH1F("h","h",200,0.5,200.5);
  TSpectrum* s = new TSpectrum(30);//max_npeaks
  double dwf[E16DST_Constant::NSamplesLG];
  double fr_peakxs[30];//full region
  double fr_peakys[30];//full region
  int nps;
  std::vector<double> pxs;
  std::vector<double> pys;

  //set waveform
  for(int cell=0; cell<E16DST_Constant::NSamplesLG; cell++){
    if(cell==0){ dwf[cell] = dat[cell]; }
    else{ dwf[cell] = dat[cell] - dat[cell-1]; }
    mwf[cell] = dat[cell];
    if( cell>1&&cell<(E16DST_Constant::NSamplesLG-1) ){
      if((dat[cell-1]+dat[cell+1])/2.*1.5<dat[cell] || (dat[cell-1]+dat[cell+1])/2.*0.5>dat[cell] ){//remove spike
	mwf[cell]=(dat[cell-2]+dat[cell+2])/2.;
      }
    }
    h->SetBinContent(cell,mwf[cell]);
  }

  //N peaks search
  int fr_npeaks = s->Search(h, 2, "new", 0.1);

  for(int i=0; i<fr_npeaks; i++){
    fr_peakxs[i] = s->GetPositionX()[i];
    fr_peakys[i] = s->GetPositionY()[i];
  }

  //+ my peaksearch
  nps = 0;
  pxs.clear();
  pys.clear();
  for(int j=5; j<(E16DST_Constant::NSamplesLG-5); j++){
    int th = dat[j]*0.1;
    if( dwf[j-4]>=0&&dwf[j-3]>=0&&dwf[j-2]>=0&&dwf[j-1]>=0&&dwf[j]>0 &&
        dwf[j+1]<=0&&dwf[j+2]<=0&&dwf[j+3]<=0&&dwf[j+4]<=0 &&
        dat[j]>10 ){
      pxs.push_back(j);
      pys.push_back(dat[j]);
      nps++;
    }
  }
  int pstype = 0;//peak search type. 0: use TSpectrum, 1: my algorithm
  if(fr_npeaks>3){
    pstype = 1;
    fr_npeaks = nps;
    for(int i=0; i<fr_npeaks; i++){
      fr_peakxs[i] = pxs[i];
      fr_peakys[i] = pys[i];
    }
  }

  /*get offset
  double ibg = 0;
  int nbg = 0;
  int pxmin = 200;
  int pxmax = 0;
  for(int p=0; p<rnp; p++){
    if(rpx[p]<pxmin){
      pxmin=rpx[p];
    }
    if(rpx[p]>pxmax){
      pxmax=rpx[p];
    }
  }

  for(int p=pxmin-50; p<pxmax-10; p++){
    //for(int p=0; p<200; p++){
    if(abs(p-px[0])<10||abs(p-px[1])<10||(abs(p-px[2]))<10){
      continue;
    }
    if(abs(data[p])<2){
      ibg+=dat[p];
      nbg+=1;
    }
  }
  
  double bg = ibg/double(nbg);
  */




  //get N peaks at trigger timing
  int npeaks = 0;
  for(int i=0; i<fr_npeaks; i++){
    if( t0-20<fr_peakxs[i] && fr_peakxs[i]<t0+20 ){
      peakxs[npeaks] = fr_peakxs[i];
      peakys[npeaks] = fr_peakys[i];
      npeaks++;
    }
  }

  delete h;
  delete s;

  return npeaks;

}


void E16ANA_LGWaveform::SetTemplate(){

  E16ANA_CalibDBManager& calib=E16ANA_CalibDBManager::Instance();
  FILE* fp_wf = calib.CalibFileOpenBinary("LG-WFtemplate", calib.CurrentRunID() );
  if ( fp_wf==NULL ) {
    std::cout<<"[Error] wf template file is not found !"<<std::endl;
    exit(1);
  }

  double xt, yt;
  std::vector<double> x;
  std::vector<double> y;
  while( feof(fp_wf)==0 ){
    fscanf(fp_wf, "%lf %lf", &xt, &yt );
    x.push_back(xt);
    y.push_back(yt);
  }

  gtmpl = new TGraph(110,&x[0],&y[0]);

  fclose(fp_wf);
}

double E16ANA_LGWaveform::Template1(double* x, double* par){

  return (gtmpl->Eval((x[0]-par[0])*par[1]))*par[2]/140.+par[3];

}

double E16ANA_LGWaveform::Template2(double* x, double* par){

  return (gtmpl->Eval((x[0]-par[0])*par[1]))*par[2]/140.+(gtmpl->Eval((x[0]-par[3])*par[4]))*par[5]/140.+par[6];

}

double E16ANA_LGWaveform::Template3(double* x, double* par){

  return (gtmpl->Eval((x[0]-par[0])*par[1]))*par[2]/140. + (gtmpl->Eval((x[0]-par[3])*par[4]))*par[5]/140. + (gtmpl->Eval((x[0]-par[6])*par[7]))*par[8]/140.+par[9];

}


int E16ANA_LGWaveform::Fit(double* dat, double* mwf, int npeaks, double* peakxs, double* peakys){

  /*
  double x[E16DST_Constant::NSamplesLG];
  double ex[E16DST_Constant::NSamplesLG] = {0.};
  double ey[E16DST_Constant::NSamplesLG];
  for(int i=0;i<E16DST_Constant::NSamplesLG){
    x[i] = i;
    ey[i]=mwf[i]*0.05+1.2;
  }
  TGraphErrors* wf = new TGraphErrors(200,x,&mwf[0],ex,ey);



      //************fit****************************************
  TF1* temp1 = new TF1("temp1",Template1,0,200,4);
  TF1* temp2 = new TF1("temp2",Template2,0,200,7);
  TF1* temp3 = new TF1("temp3",Template3,0,200,10);


      if(rnp==0||rnp>3){//don't fit because there are noise or low_ph
      //if(rfnpeaks==0||rfnpeaks>3){//don't fit because there are noise or low_ph

	if(rnp==0){
	//if(rfnpeaks==0){
	  if(count[0]<100){
	    ca[0][count[0]] = new TCanvas(Form("ca0%d",count[0]),Form("ca0%d",count[0]),700,500);
	    wf->Draw("APL");
	    wf->SetTitle(Form("tim%f",timeparam));
	    if(count[0]==0){ca[0][count[0]]->Print(out0+"[","pdf");}
	    ca[0][count[0]]->Print(out0,"pdf");
	    if(count[0]==99){ca[0][count[0]]->Print(out0+"]","pdf");}
	  }
	  else{wf->Delete();}
	  count[0]++;
	}
	else{//rnp>3
	  if(count[4]<4){
	    ca[4][count[4]] = new TCanvas(Form("ca4%d",count[4]),Form("ca4%d",count[4]),700,500);
	    wf->Draw("APL");
	    wf->SetTitle(Form("tim%f",timeparam));
	    if(count[4]==0){ca[4][count[4]]->Print(out4+"[","pdf");}
	    ca[4][count[4]]->Print(out4,"pdf");
	    if(count[4]==3){ca[4][count[4]]->Print(out4+"]","pdf");}
	  }
	  else{wf->Delete();}
	  count[4]++;
	}

	continue;
      }

      ci->cd();
      gStyle->SetOptFit(1111);
      wf->Draw("APL");
      Double_t chi2,Ndof,baseline;
      Double_t m1,m2,m3,m4,m5;
      Double_t s1,s2,s3,s4,s5;
      Double_t v1,v2,v3,v4,v5;

      if(rnp==1){
	//if(rfnpeaks==1){
	temp1->SetParameters(rpx[0],0.95,rp[0]-bg,bg);		
	//temp1->SetParLimits(2,rp[0]-15,rp[0]+15);
	temp1->SetParLimits(1,0,2);
	//temp1->SetParLimits(3,bg-2,bg+2);
	//wf->Fit("temp1","Q","Q",peakx-15,peakx+30);
	wf->Fit("temp1","Q","Q",pxmin-20,pxmax+30);
	chi2 = temp1->GetChisquare();
	Ndof = temp1->GetNDF();
	//chi2_ndf->Fill(abs(chi2/double(Ndof)-1.));

	m1 = temp1->GetParameter(0);
	s1 = temp1->GetParameter(1);
	v1 = temp1->GetParameter(2);
	baseline = temp1->GetParameter(3);
	fout1<<m1<<"  "<<s1<<"  "<<v1<<"  "<<baseline<<std::endl;
	if(count[1]==99){fout1<<"**********************************"<<std::endl;}

	if(count[1]<100){//draw
	ca[1][count[1]] = new TCanvas(Form("ca1%d",count[1]),Form("ca1%d",count[1]),700,500);
	wf->Draw("APL");
	wf->SetTitle(Form("tim%f",timeparam));
	hw->Draw("same");
	if(count[1]==0){ca[1][count[1]]->Print(out1+"[","pdf");}
	ca[1][count[1]]->Print(out1,"pdf");
	if(count[1]==99){ca[1][count[1]]->Print(out1+"]","pdf");}
	}//draw
	count[1]++;
      }

      if(rnp==2){
	//if(rfnpeaks==2){
        temp2->SetParameters(rpx[0],0.95,rp[0]-bg, rpx[1],0.95,rp[1]-bg,bg);                            
	temp2->SetParLimits(0,rpx[0]-15,rpx[0]+15);
	temp2->SetParLimits(1,0,2);
	temp2->SetParLimits(2,rp[0]-50,rp[0]+50);
	temp2->SetParLimits(3,rpx[1]-15,rpx[1]+15);
	temp2->SetParLimits(4,0,2);
	temp2->SetParLimits(5,rp[1]-50,rp[1]+50);
	//temp2->SetParLimits(6,bg-2,bg+2);
        //wf->Fit("temp2","Q","Q",peakx-15,peakx+30);
        wf->Fit("temp2","Q","Q",rpx[0]-20,rpx[0]+30);
	chi2 = temp2->GetChisquare();
	Ndof = temp2->GetNDF();
	//chi2_ndf->Fill(abs(chi2/double(Ndof)-1.));

	m1 = temp2->GetParameter(0);
	s1 = temp2->GetParameter(1);
	v1 = temp2->GetParameter(2);
	m2 = temp2->GetParameter(3);
	s2 = temp2->GetParameter(4);
	v2 = temp2->GetParameter(5);
	baseline = temp2->GetParameter(6);
	fout2<<m1<<"  "<<s1<<"  "<<v1<<"  "<<baseline<<std::endl;
	fout2<<m2<<"  "<<s2<<"  "<<v2<<"  "<<baseline<<std::endl;
	if(count[2]==99){fout2<<"**********************************"<<std::endl;}

	if(count[2]<100){
	ca[2][count[2]] = new TCanvas(Form("ca2%d",count[2]),Form("ca2%d",count[2]),700,500);
	wf->Draw("APL");
	wf->SetTitle(Form("tim%f",timeparam));
	hw->Draw("same");
	if(count[2]==0){ca[2][count[2]]->Print(out2+"[","pdf");}
	ca[2][count[2]]->Print(out2,"pdf");
	if(count[2]==99){ca[2][count[2]]->Print(out2+"]","pdf");}
	}
	count[2]++;
      }
      if(rnp==3){
	//if(rfnpeaks==3){
        temp3->SetParameters(rpx[0],0.95,rp[0]-bg, rpx[1],0.95,rp[1]-bg, rpx[2],0.95,rp[2]-bg, bg);
	temp3->SetParLimits(0,rpx[0]-15,rpx[0]+15);
	//temp3->SetParLimits(2,rp[0]-15,rp[0]+15);
	temp3->SetParLimits(1,0,2);
	temp3->SetParLimits(3,rpx[1]-15,rpx[1]+15);
	//temp3->SetParLimits(5,rp[1]-15,rp[1]+15);
	temp3->SetParLimits(4,0,2);
	temp3->SetParLimits(6,rpx[2]-15,rpx[2]+15);
	//temp3->SetParLimits(8,rp[2]-15,rp[2]+15);
	temp3->SetParLimits(7,0,2);
	//temp3->SetParLimits(9,bg-2,bg+2);
	//wf->Fit("temp3","Q","Q",peakx-15,peakx+30);
	wf->Fit("temp3","Q","Q",rpx[0]-20,rpx[0]+30);
	chi2 = temp3->GetChisquare();
        Ndof = temp3->GetNDF();
        //chi2_ndf->Fill(abs(chi2/double(Ndof)-1.));

	m1 = temp3->GetParameter(0);
	s1 = temp3->GetParameter(1);
	v1 = temp3->GetParameter(2);
	m2 = temp3->GetParameter(3);
	s2 = temp3->GetParameter(4);
	v2 = temp3->GetParameter(5);
	m3 = temp3->GetParameter(6);
	s3 = temp3->GetParameter(7);
	v3 = temp3->GetParameter(8);
	baseline = temp3->GetParameter(9);
	fout3<<m1<<"  "<<s1<<"  "<<v1<<"  "<<baseline<<std::endl;
	fout3<<m2<<"  "<<s2<<"  "<<v2<<"  "<<baseline<<std::endl;
	fout3<<m3<<"  "<<s3<<"  "<<v3<<"  "<<baseline<<std::endl;
	if(count[3]==99){fout3<<"**********************************"<<std::endl;}

	if(count[3]<10){
	ca[3][count[3]] = new TCanvas(Form("ca3%d",count[3]),Form("ca3%d",count[3]),700,500);
	wf->Draw("APL");
	wf->SetTitle(Form("tim%f",timeparam));
	hw->Draw("same");
	if(count[3]==0){ca[3][count[3]]->Print(out3+"[","pdf");}
	ca[3][count[3]]->Print(out3,"pdf");
	if(count[3]==9){ca[3][count[3]]->Print(out3+"]","pdf");}
	}
	count[3]++;
      }


  */

  return npeaks;

}
