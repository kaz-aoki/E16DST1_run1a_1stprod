#ifndef E16ANA_GTRStatus_h
#define E16ANA_GTRStatus_h
#include "E16DST_DST0.hh"
#include "E16DST_DST1Constant.hh"

class E16ANA_GTRASDDeadChannel;
class E16ANA_GTRGEMDeadArea;
class E16ANA_GTRStatus {
protected:
	enum {
		n_modules = E16DST_DST1Constant::n_gtr_modules, 
		n_ychs = E16DST_DST1Constant::n_gtr_asd_chs,
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
	E16ANA_GTRASDDeadChannel* ASDDeadChannel(){return asd_dead;}
	E16ANA_GTRGEMDeadArea* GEMDeadArea(){return gem_dead;}
	void Init();

private:
	int status_ych[n_modules][n_ychs];
	E16ANA_GTRASDDeadChannel *asd_dead;
    E16ANA_GTRGEMDeadArea *gem_dead;

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
	E16ANA_GTRGEMDeadArea();
	~E16ANA_GTRGEMDeadArea();
	bool ReadFile(const char *filename);
	bool ReadDeadChannelData(const int runID);
	bool Is300YOK(const int module_id, const int strip_ch);
    void Init();
private:
	enum {
		n_modules = E16DST_DST1Constant::n_gtr_modules, 
		n_ychs = E16DST_DST1Constant::n_gtr_asd_chs,
		ok_flag = 0,
		dead_flag = 1,
	 	noisy_flag = 2, 
		hot_flag = 3
	};
	int status_300gem_x[n_modules][12];
	int status_300gem_y[n_modules][n_ychs];
};


#endif //E16ANA_GTRStatus_h
