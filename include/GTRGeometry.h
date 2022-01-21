#ifndef GTRGeometry_hh
#define GTRGeometry_hh 1

/*
#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLine.h>
#include <TTree.h>
#include <TGraph.h>
#include <TWbox.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TLatex.h>
#include <TFile.h>
*/
//#include <iterator>

#include <vector>

#include "E16ANA_GTRStripAnalyzer.h"
#include "E16ANA_GTRAnalyzer2.h"
#include "E16ANA_GTRPedestal.h"
//#include "OnlineGTRHistV0.h"
#include "E16DST_DST0.hh"
#include "E16DST_Constant.hh"
//#include "LGgeometry.h"
//#include "LGBasic.h"
//#include "LGDST0ANA.h"

//#include "E16ANA_ParamManager.hh"
#include "E16ANA_ErrorMessage.hh"
#include "E16ANA_Geometry.hh"
#include "E16ANA_GeometryV2.hh"


class GTRGeometry {
public:
	GTRGeometry();
	~GTRGeometry();
	//----yokkaichi--------------
	inline int ModuleID_2013to2020_33(int id )
	{
   	const int moduleID_2013to2020_33[33] = {
      	10, 110, 210, 9, 109, 209, 8, 108, 208, 7, 107, 207, 6, 106, 206, 
      	5, 105, 205,
      	4,  104, 204, 3, 103, 203, 2, 102, 202, 1, 101, 201, 0, 100, 200 };
	   return  moduleID_2013to2020_33[ id ];
	}
	inline int ModuleID_2020to2013_33(int id ){//GTR,SSD
	   const int module_id_kawama33[3][11] = {
      	{30, 27, 24, 21, 18, 15, 12, 9, 6, 3, 0},
      	{31, 28, 25, 22, 19, 16, 13, 10, 7, 4, 1},
      	{32, 29, 26, 23, 20, 17, 14, 11, 8, 5, 2}};
   	return module_id_kawama33[ id / 100][id % 100];
	}
	inline int ModuleID_2013to2020_27( int id ){// //LG,HBD
	   const int moduleID_2013to2020_27[27] = {
	      9, 109, 209, 8, 108, 208, 7, 107, 207,  6, 106, 206, 
	      5, 105, 205, 
	      4, 104, 204, 3, 103, 203, 2, 102, 202,  1, 101, 201};
	   return  moduleID_2013to2020_27[ id ];
	}
	inline int ModuleID_2020to2013_27(int id ){//LG,HBD
	   const int module_id_kawama27[3][9] = {
	      {24, 21, 18, 15, 12, 9, 6, 3, 0 },
      	{25, 22, 19, 16, 13, 10, 7, 4, 1},
      	{26, 23, 20, 17, 14, 11, 8, 5, 2}};
   	int id2=(id %100) -1;
   	return module_id_kawama27[ id / 100][ id2 ];
	}
	void FillGeometry();
	void loadGTRGeometry(E16ANA_GeometryV2* geom, int gtrModuleNo);
	void SetGTRModuleID(int m_id){
		gtr_module_id = m_id;
	};
	void SetGTRCenterAngle(int l_id, double phi){
		GTR_center_angle[l_id] = phi;
	};
	void SetGTRCenterRadius(int l_id, double radius){
		GTR_center_radius[l_id] = radius;
	};
	TVector2 getGTRCenter(E16ANA_GeometryV2* geom, int moduleID, int gtrLayerID );
	//Int_t gtrSizeToLayerID(Int_t layersize);

private:
	int  gtr_module_id;
   double GTR_center_angle[2];
   double GTR_center_radius[2];
};

//--------------------------------------------------
/*
   char* E16calibfilename = "./E16CalibFiles-local.cfg";
   E16ANA_ParamManager* paramMgr= new E16ANA_ParamManager( E16calibfilename );
   char* fieldmapname = paramMgr->GetMapFileName();
   E16INFO("field map filename in paramfile:%s",fieldmapname);
   char* geomfilename = paramMgr->GetGeomFileName();
   E16INFO("geom filename in paramfile:%s",geomfilename);
   E16ANA_GeometryV2* geom_v2 = new E16ANA_GeometryV2( geomfilename );

   vector<_line> v_lines;
*/

#endif //GTRGeometry_hh
