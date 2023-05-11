#include "E16ANA_StraightTrack.hh"
#include "E16ANA_StraightTrackNameSpace.hh"

using namespace E16ANA_StraightTrackNameSpace;

E16ANA_StraightTrackFit::E16ANA_StraightTrackFit(){
}
E16ANA_StraightTrackFit::~E16ANA_StraightTrackFit(){
}


void E16ANA_StraightTrackFit::Clear(){
	for(int i = 0; i < Hits.size(); i++){
		delete Hits[i];
	}
	Hits.clear();
}

void E16ANA_StraightTrackFit::AddHit(G4ThreeVector &lpos, double sigma, int mid, int lid, int axis, const E16ANA_DetectorGeometry *geom, double rphi){
	Hit_t *h = new Hit_t(lid, lpos, sigma, geom, rphi);
	Hits.push_back(h);
//	G4ThreeVector lpos = (lpos, 0, 0);	
//	G4ThreeVector gpos = G4ThreeVector(geom->GetGPos(lpos));	
//	G4ThreeVector rpos = G4ThreeVector(gpos.rotateY(rphi));
//	fit_samples.push_back(TVector2(rpos.z(), rpos.x()));
}

void E16ANA_StraightTrackFit::Fit(){
	std::vector<TVector2> fit_samples;
	std::vector<double> sigmas;
	fit_samples.clear();
	sigmas.clear();
	for(int i = 0; i < Hits.size(); i++){
		Hit_t *h = Hits[i];
//		std::cout << "rphi =  " << h->rphi << std::endl;
//		std::cout << "lpos = " << h->lpos.x() << ", " << h->lpos.y()<< ", " << h->lpos.z() << std::endl; 
		G4ThreeVector gpos = G4ThreeVector(h->geom->GetGPos(h->lpos));	
		G4ThreeVector rpos = G4ThreeVector(gpos.rotateY(h->rphi));	
		h->rot_pos = rpos;
//		std::cout << "layer  = " << h->layer << std::endl;
		fit_samples.push_back(TVector2(rpos.z(), rpos.x()));
		sigmas.push_back(h->sigma);
	}
	std::vector<long double> &&results = LeastSquareMethod(fit_samples, sigmas);//return chi2, a, b
	chi2 = results[0];
	fit_a = results[1];
	fit_b = results[2];	
	for(int i = 0; i < Hits.size(); i++){
		Hit_t *h = Hits[i];
		h->residual = (h->rot_pos.x() - (h->rot_pos.z() * fit_b + fit_a));
	}
	results.clear();
}

double E16ANA_StraightTrackFit::FitResidual(int lid){
	for(int i = 0; i < Hits.size(); i++){
		if(Hits[i]->layer == lid){
//		std::cout << "chi2  = " << chi2 << std::endl;
//		std::cout << "fit a  = " << fit_a << std::endl;
//		std::cout << "fit b  = " << fit_b << std::endl;
//		std::cout << "rpos x = " << Hits[i]->rot_pos.x() << std::endl;
//		std::cout << "rpos z = " << Hits[i]->rot_pos.z() << std::endl;
//		std::cout << "hits residual "<<  Hits[i]->residual << std::endl;
			return Hits[i]->residual;
		}
	}
}

G4ThreeVector E16ANA_StraightTrackFit::FitGPos(int lid){
	for(int i = 0; i < Hits.size() ; i++){
		if(Hits[i] -> layer == lid){
			return Hits[i]->fit_gpos;
		}
	}
}
std::vector<long double> E16ANA_StraightTrackFit::LeastSquareMethod(std::vector<TVector2> &tv_v_pos, std::vector<double> sigma_x){
	int v_size = tv_v_pos.size();
	int v_sig_size = sigma_x.size();
	if(v_size != sigma_x.size()){
			std::cout << " sizes of vectors btw positions and sigmas are different  " << std::endl;
			std::cout << "size of pos vec = " << v_size << std::endl;
			std::cout << "size of sigma vec = " << v_sig_size << std::endl;}
	double wt=0, t=0, sx=0, sy=0, st2=0, ss = 0, sxoss = 0;
	double sx2=0, sxy=0;
	//double a=0, b=0, siga=0, sigb=0, chi2=0;//a+bx
	for(int i = 0; i < v_size; i++){
		wt = 1.0 /sigma_x[i]/sigma_x[i];
		ss  += wt;
		sx  += tv_v_pos[i].X() * wt ;
		sy  += tv_v_pos[i].Y() * wt ;
		sx2 += tv_v_pos[i].X() *tv_v_pos[i].X() * wt ;
		sxy += tv_v_pos[i].Y() *tv_v_pos[i].X() * wt ;
	}
	double a = (sx*sxy-sx2*sy)/(sx*sx-ss*sx2);
	double b = (sx*sy-ss*sxy)/(sx*sx-ss*sx2);
	/*
	sxoss = sx/ss;
	for(int i=0; i < v_size; i++ ){
		t = (tv_v_pos[i].X() -sxoss)/sigma_x[i];
		st2 += t*t;
		b += t*tv_v_pos[i].Y()/sigma_x[i]; 
	}
	b /= st2;
	a = (sy-sx*b)/ss;
	siga = sqrt((1.0 + sx*sx/(ss*st2)/ss));
	sigb = sqrt(1.0/st2);
	*/
	double chi2 = 0.0;
	for(int i=0; i < v_size; i++){
		chi2 += sqr((tv_v_pos[i].Y()- a-(b*tv_v_pos[i].X()))/sigma_x[i]);
//		q = Gammq(0.5 * (n_sample-2), 0.5* (chi2));
	}
	std::vector<long double> lst_sq_results;
	lst_sq_results.clear();
	lst_sq_results.push_back(chi2);
	lst_sq_results.push_back(a);
	lst_sq_results.push_back(b);
	for(int i = 0; i<v_size; i++){
		lst_sq_results.push_back(tv_v_pos[i].Y()- a-(b*tv_v_pos[i].X()));
	}
	return lst_sq_results;
}

