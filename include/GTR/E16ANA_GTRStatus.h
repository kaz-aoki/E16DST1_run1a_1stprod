#ifndef E16ANA_GTRStatus_h
#define E16ANA_GTRStatus_h
#include "E16DST_DST0.hh"
#include "E16DST_DST1Constant.hh"

class E16ANA_GTRASDDeadChannel;
class E16ANA_GTRGEMDeadArea;
class E16ANA_GTR100GEMDeadArea;
class E16ANA_GTR200GEMDeadArea;
class E16ANA_GTR300GEMDeadArea;
class E16ANA_GTRAPVDeadChannel;

class E16ANA_GTRStatus {
protected:
	enum {
		n_modules = E16DST_DST1Constant::n_gtr_modules, 
		n_ychs =    E16DST_DST1Constant::n_gtr_asd_chs,
		n_layers =  E16DST_DST1Constant::n_gtr_layers,
		n_axes   =  E16DST_DST1Constant::n_gtr_axes,
		n_strips_100x = E16DST_DST1Constant::nstrips_100x,
		n_strips_100y = 144,//ya + yb
		n_strips_200x = E16DST_DST1Constant::nstrips_200x,
		n_strips_200y = E16DST_DST1Constant::nstrips_200y,
		n_strips_300x = E16DST_DST1Constant::nstrips_300x,
		n_strips_300y = E16DST_DST1Constant::nstrips_300y,
		ok_flag = 0,
		dead_flag = 1,
	 	noisy_flag = 2, 
		hot_flag = 3
	};
public:
	E16ANA_GTRStatus(const int id);
	~E16ANA_GTRStatus();
	bool Is300YOK(const int module_id, const int ch);
	int  StatusYch(const int module_id, const int ch);
//	bool IsOK(const int module_id, const int layer_id, const int ch_x, const int ch_y);
	int GTRStatus (const int module_id, const int layer, const double lx, const double ly);
	int GTRXStatus(const int module_id, const int layer, const double lx                 );
	int GTRYStatus(const int module_id, const int layer, const double lx, const double ly);
	E16ANA_GTRASDDeadChannel* ASDDeadChannel(){return asd_dead;}
	E16ANA_GTR100GEMDeadArea* GEMDeadArea100(){return gem_dead_100;}
	E16ANA_GTR200GEMDeadArea* GEMDeadArea200(){return gem_dead_200;}
	E16ANA_GTR300GEMDeadArea* GEMDeadArea300(){return gem_dead_300;}
	E16ANA_GTRAPVDeadChannel* APVDeadChannel(){return apv_dead;}
	void Init();

private:
	int status_ych[n_modules][n_ychs];
	E16ANA_GTRASDDeadChannel *asd_dead;
    E16ANA_GTR100GEMDeadArea *gem_dead_100;
    E16ANA_GTR200GEMDeadArea *gem_dead_200;
    E16ANA_GTR300GEMDeadArea *gem_dead_300;
	E16ANA_GTRAPVDeadChannel *apv_dead;
};	


class E16ANA_GTRASDDeadChannel {
	
public:
	E16ANA_GTRASDDeadChannel();
	~E16ANA_GTRASDDeadChannel();
    bool ReadFile(const char* filename);
	bool ReadDeadChannelData(const int runID);
    bool IsOK(const int module_id, const int ch);
    bool IsDead(const int module_id, const int ch);
    bool IsNoisy(const int module_id, const int ch);
    bool IsHot(const int module_id, const int ch);
	int Status(const int module_id, const int ch);
	void Init();
//	bool IsValidID(const int module_id, const int ch);
	
private:
	enum {
		n_modules = E16DST_DST1Constant::n_gtr_modules, 
		n_ychs = E16DST_DST1Constant::n_gtr_asd_chs,
		ok_flag = 0,
		dead_flag = 1,
	 	noisy_flag = 2, 
		hot_flag = 3
	};
	int status_asd[n_modules][n_ychs];

};

class E16ANA_GTRGEMDeadArea {
public:
	E16ANA_GTRGEMDeadArea(int _n_gem_strip_x, int _n_gem_strip_y);
	~E16ANA_GTRGEMDeadArea();
	bool ReadFile(const char *filename, int xy);
	//virtual bool ReadDeadChannelData(const int runID);
	//bool Is300YOK(const int module_id, const int strip_ch);
    virtual void Init();
    bool IsXOK(const int module_id, const int ch);
    bool IsXOK(const int module_id, const double lx_mm);
    bool IsYOK(const int module_id, const int ch);
    bool IsYOK(const int module_id, const double ly_mm);
protected:
    int n_gem_strip_x;
    int n_gem_strip_y;
	enum {
		n_modules = E16DST_DST1Constant::n_gtr_modules, 
		//n_ychs = E16DST_DST1Constant::n_gtr_asd_chs,
		ok_flag = 0,
		dead_flag = 1,
	 	noisy_flag = 2, 
		hot_flag = 3
	};
	//int status_gem_x[n_modules][n_gem_strip_x];
	//int status_gem_y[n_modules][n_gem_strip_y];
	std::vector<std::vector<int>> status_gem_x;
	std::vector<std::vector<int>> status_gem_y;
};

class E16ANA_GTR100GEMDeadArea;
class E16ANA_GTR200GEMDeadArea;
class E16ANA_GTR300GEMDeadArea;

class E16ANA_GTR100GEMDeadArea : public E16ANA_GTRGEMDeadArea {
public:
	E16ANA_GTR100GEMDeadArea()
	: E16ANA_GTRGEMDeadArea(1,1){
	};	
	~E16ANA_GTR100GEMDeadArea(){};	
	bool ReadDeadChannelData(const int runID);
private:
};
class E16ANA_GTR200GEMDeadArea : public E16ANA_GTRGEMDeadArea {
public:
	E16ANA_GTR200GEMDeadArea()
	: E16ANA_GTRGEMDeadArea(4,4){
	};	
	~E16ANA_GTR200GEMDeadArea(){};	
	bool ReadDeadChannelData(const int runID);
private:
};

class E16ANA_GTR300GEMDeadArea : public E16ANA_GTRGEMDeadArea {
public:
	E16ANA_GTR300GEMDeadArea()
	: E16ANA_GTRGEMDeadArea(12,24){
	};	
	~E16ANA_GTR300GEMDeadArea(){};	
	bool ReadDeadChannelData(const int runID);
private:
};

class E16ANA_GTRAPVDeadChannel {
public:
	E16ANA_GTRAPVDeadChannel();
	~E16ANA_GTRAPVDeadChannel();
	bool ReadDeadChannelData(const int runID);
	bool ReadFile(const char *filename);
    virtual void Init();
//    bool IsXOK(const int module_id, const int ch);
//    bool IsXOK(const int module_id, const double lx_mm);
//    bool IsYOK(const int module_id, const int ch);
//    bool IsYOK(const int module_id, const double ly_mm);
//	bool IsOK (const int module_id, const int layer, const int ch_x, const int ch_y);
	int Status  (const int module_id, const int layer, const int ch_x, const int ch_y);
	int XStatus (const int module_id, const int layer, const int ch_x                );
	int YStatus (const int module_id, const int layer,                 const int ch_y);
protected:
    int n_apv_strip_x;
    int n_apv_strip_y;
	enum {
		n_modules = E16DST_DST1Constant::n_gtr_modules, 
		//n_ychs = E16DST_DST1Constant::n_gtr_asd_chs,
		n_ychs =    E16DST_DST1Constant::n_gtr_asd_chs,
		n_layers =  E16DST_DST1Constant::n_gtr_layers,
		n_axes   =  E16DST_DST1Constant::n_gtr_axes,
		n_strips_100x = E16DST_DST1Constant::nstrips_100x,
		n_strips_100y = 144,//ya + yb
		n_strips_200x = E16DST_DST1Constant::nstrips_200x,
		n_strips_200y = E16DST_DST1Constant::nstrips_200y,
		n_strips_300x = E16DST_DST1Constant::nstrips_300x,
		n_strips_300y = E16DST_DST1Constant::nstrips_300y,
		ok_flag = 0,
		dead_flag = 1,
	 	noisy_flag = 2, 
		hot_flag = 3
	};
	//int status_gem_x[n_modules][n_gem_strip_x];
	//int status_gem_y[n_modules][n_gem_strip_y];
	std::vector<std::vector<std::vector<std::vector<int>>>> status_apv;
};

//class E16ANA_GTR100APVDeadChannel;
//class E16ANA_GTR200APVDeadChannel;
//class E16ANA_GTR300APVDeadChannel;

//class E16ANA_GTR100APVDeadChannel : public E16ANA_GTRAPVDeadChannel {
//public:
//	E16ANA_GTR100APVDeadChannel()
//	: E16ANA_GTRAPVDeadChannel(288,144){
//	};	
//	~E16ANA_GTR100APVDeadChannel(){};	
//	bool ReadDeadChannelData(const int runID);
//private:
//};
//class E16ANA_GTR200APVDeadChannel : public E16ANA_GTRAPVDeadChannel {
//public:
//	E16ANA_GTR200APVDeadChannel()
//	: E16ANA_GTRAPVDeadChannel(576,144){
//	};	
//	~E16ANA_GTR200APVDeadChannel(){};	
//	bool ReadDeadChannelData(const int runID);
//private:
//};
//class E16ANA_GTR300APVDeadChannel : public E16ANA_GTRAPVDeadChannel {
//public:
//	E16ANA_GTR300APVDeadChannel()
//	: E16ANA_GTRAPVDeadChannel(864,216){
//	};	
//	~E16ANA_GTR300APVDeadChannel(){};	
//	bool ReadDeadChannelData(const int runID);
//private:
//};






#endif //E16ANA_GTRStatus_h
