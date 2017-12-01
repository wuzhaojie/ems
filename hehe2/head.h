#pragma once
#ifndef HEAD_H
#define HEAD_H

#include "BackforePowerflow.h"

#define DECOMPOSE 1000
#define BIGNUM -9999
//#define MARGINLIMIT 0.1
#define SMALLNUM 0.00001

struct ControllableUnitData
{
	double *Pi;
	double *ci;
	double Shi;
	double deltiup;
	double deltidown;
	double PHi;
	double PLi;
	double RHi;
	double MOTi;
	double MDTi;
	double COM;
	double Pinit;
	double Invest;
	double k;
	double CDP;
	double CE;
	double *Q;
	double year;
	int Uinit;
	double Ramp;
	int Identifier;
	int type;
	char name[20];
	double a;
	double b;
	double c;
	double d;
	int curve;
	double fuelcost;

	double TOinit;
	double TDinit;

	bool *Uit;
	bool *openit;
	bool *closeit;
	double *Pit;
	double *Rit;
	double *Sit;
	double *Cit;
	double Pdelt;
	double Citsimplify;
	double aj_uplimit;
	double aj_downlimit;
	//double layer
	bool *Uitlay2;
	double *Pitlay2;
	double *Sitlay2;
	double *Citlay2;
	//total
	double *Pittotal;

	int ID32;
	int *levelIdentifier;
	double aloss;
	double *CostC;
	double *CostS;
	double *CostCOM;
	int nodenum;

	double OCCostC;
	double OCCostS;
	double OCCostCOM;
	int OCID32;
	int OCIdentifier;
	char OCname[20];

};
struct EnergyStorageData//需要区分充放电效率
{ 
	double PgHk;
	double PgLk;
	double PpHk;
	double PpLk;
	double VHk;
	double VLk;
	double yitag;
	double yitap;
	double Wk;
	double VHkset;
	double VLkset;
	double Invest;
	double year;
	int cyclenum;
	double MaintenanceCost;
	double Einit;
	double *VLksetschedule;
	double *VHksetschedule;
	double VLksetscheduleS;
	double VHksetscheduleS;
	int BC;
	int Identifier;
	int type;
	char name[40];
	double CostkWh;

	double VHkgridmargin;
	double VLkgridmargin;
	double VHkislandmargin;
	double VLkislandmargin;
	int outlimitLtime;
	int outlimitHtime;
	double outlimitLdemical;
	double outlimitHdemical;

	bool *Ugkt;
	bool *Upkt;
	double *Pkt;
	double *Vkt;
	double *Pgkt;
	double *Ppkt;
	double *Pdhkt;
	double *Pchkt;
	double *Rkt;
	bool *egkt;
	bool *epkt;
	double Pdelt;
	double Ramp;
	//double layer
	double *Pktlay2;
	double *Vktlay2;
	double *Pgktlay2;
	double *Ppktlay2;
	double *VLksetschedulelay2;
	double *VHksetschedulelay2;
	//total
	double *Pkttotal;
	double *Vkttotal;

	int ID32;
	int *levelIdentifier;

	double WkC;
	double aloss;
	double *CostC;
	int nodenum;
	//double MARGINLIMIT;
	double VHkgridMARGINLIMIT;
	double VLkgridMARGINLIMIT;
	double VHkislandMARGINLIMIT;
	double VLkislandMARGINLIMIT;
	double Wktemp;

	double OCCostC;
	int OCID32;
	int OCIdentifier;
	char OCname[20];
};
struct RenewableEnergyData
{
	double *PnewHt;
	double *PnewHttemp;
	double error;
	int Identifier;
	char name[20];
	int type;

	double *Pnewt;
	//duoble layer
	double *PnewHtlay2;
	double *Pnewtlay2;
	//total
	double *PnewHttotal;
	double *Pnewttotal;

	int ID32;
	int *levelIdentifier;
	double aloss;
	int nodenum;

	int OCID32;
	int OCIdentifier;
	char OCname[20];
};
struct GridData
{
	double *Buy;
	double *Sell;
	double *Buytemp;
	double *Selltemp;
	double Pbuymax;
	double Psellmax;
	double Ramp;

	bool *Ubuyt;
	bool *Usellt;
	double *Pbuyt;
	double *Psellt;
	double Pdelt;
	double *VirtualBuy;
	double *VirtualSell;
	//double layer
	double *Buylay2;
	double *Selllay2;
	double *VirtualBuylay2;
	double *VirtualSelllay2;
	double *Pbuytlay2;
	double *Pselltlay2;
	//total
	double *Buytotal;
	double *Selltotal;
	double *VirtualBuytotal;
	double *VirtualSelltotal;
	double *Pbuyttotal;
	double *Psellttotal;

	int gridnum;
	double aloss;
	double *CostBS;

	double OCCostBS;
};
struct LoadData
{
	int Identifier;
	double error;
	int level;
	double *Pdt;
	int type;
	char name[20];

	bool *Ucutx;
	double leveltemp;
	int levelorder;
	bool *Scutx;
	double Scut;
	//double layer
	double *Pdtlay2;
	bool *Ucutxlay2;
	//taotal
	double *Pdttotal;
	bool *Ucutxtotal;

	int ID32;
	int *levelIdentifier;
	//loadcut
	double Sumload;
	bool Uscut;
	double aloss;
	double *CostCut;
	int nodenum;

	double OCCostCut;
	int OCID32;
	int OCIdentifier;
	char OCname[20];
};
struct VirtualLoadData
{
	int *levelIdentifier;
	double *Pdt;
	bool *Ucutx;
	//double layer
	double *Pdtlay2;
	bool *Ucutxlay2;
	//taotal
	double *Pdttotal;
	bool *Ucutxtotal;
	double aloss;
};

//存储默认值
struct ControllableUnitDataDefault
{
	double Shi;
	double deltiup;
	double deltidown;
	double RHi;
	double MOTi;
	double MDTi;
	double COM;
	double Invest;
	double k;
	double *Q;
	double year;
	double Ramp;
	int type;
	char name[10];
	double a;
	double b;
	double c;
	double d;
	double fuelcost;
};
struct EnergyStorageDataDefault
{ 
	double PgLk;
	double PpLk;
	double yitag;
	double yitap;
	double Wk;
	double Invest;
	double year;
	int cyclenum;
	double MaintenanceCost;
	int type;
	char name[10];
	double VHkgridmargin;
	double VLkgridmargin;
	double VHkislandmargin;
	double VLkislandmargin;
	double Ramp;
	//double MARGINLIMIT;
	double VHkgridMARGINLIMIT;
	double VLkgridMARGINLIMIT;
	double VHkislandMARGINLIMIT;
	double VLkislandMARGINLIMIT;
};
struct RenewableEnergyDataDefault
{
	double error;
	char name[10];
	int type;
};
struct GridDataDefault
{
	double Pbuymax;
	double Psellmax;
	double Ramp;
};
struct LoadDataDefault
{
	double error;
	int level;
	char name[10];
};

class SCHEDULE
{ 
public:
	int controllableunitnum;
	int node;
	int energystoragenum;
	int renewableenergynum;
	int T;
	int Ttotal;
	int Tlay2;
	int loadnum;
	int mglevel;
	int *mglevelnum;
	int virtualloadnum;
	ControllableUnitData *Controllableunitdata;
	EnergyStorageData *Energystoragedata;
	RenewableEnergyData *Renewableenergydata;
	GridData Griddata;
	LoadData *Loaddata;
	VirtualLoadData *Virtualloaddata;
	BackforePowerflow pf;
    double *Prt;
	double *Pd1t;
	double **Pktout,**Pitout,**Pnewtout,*Pdtout,**Citout,**Sitout;
	int **Uitset;
	double **Vsoet;
	double **Pdhktout,**Pchktout;
	//double *CostkWh;
	double *errorvalue;
	double *errorvaluetotal;
	double *errorvaluelay2;
	int errorlength;
	double errorvaluemax;
	double errorvaluemaxS;
	double energysumBC;
	double energysumBH;
	double energysumBL;
	double pollutionnum;
	double *V;
	double *Qgrid;
	double CEgrid;
	double Pcutcost[4];
	double Pcutlevel[4];
	double Tminite;
	int **Ucutxset;
	int gridislanddecision;
	int modeldecision;
	double *Pbuytout;
	double *Pselltout;

	ControllableUnitDataDefault *Controllableunitdatadefault;
	EnergyStorageDataDefault *Energystoragedatadefault;
	RenewableEnergyDataDefault *Renewableenergydatadefault;
	GridDataDefault Griddatadefault;
	LoadDataDefault Loaddatadefault;
	int nodedefault,pollutionnumdefault,controllabletypenum,storagetypenum,renewabletypemun;
	int Pcutleveldefault;
	double Pcutcostdefault;
	double *Qgriddefault;
	double *Vdefault;

	int onearray;
	int controllableunitnumarray;
	int energystoragenumarray;
	int renewableenergynumarray;
	int loadnumarray; 
	int valurearrayall;
	int virtualnumarray;
	int lossnumarray;

	double *Pcutxt;
	//total 
	double *Prttotal;
	double *Pd1ttotal;
	//double layer
	double *Prtlay2;
	double *Pd1tlay2;

	//loadcut
	double SumPdp;
	double SumVLksetschedule;
	double SumVHksetschedule;
	double SumEinit;
	double SumPgH;
	double SumPpH;
	double SumWk;
	double Aveyitag;
	double Aveyitap;
	double AveCostkWh;
	double *SumPdpt;

	//微网分级编号
	int *LevelID32;
	int *LevelIdentify;
	int *LevelIdentifynext;
	int **Levelnumtoreal;
	int *Levelclassify;
	//惩罚项相对值
	double punishrelative;
	double relativetemp;

	//double PL[9+1][144+1];
    //double PG[4+1][144+1];
	double **PL;
	double **PG;
	double *lossa;
	int updatelossdecision;

	//hehe
	double loss[96];
	double losslay2[4];

	int solvestate;
	int OCdecision;
	int OCT;
	double OCdeltT;
	double **OCPit;
	double **OCPkt;
	double **OCPnewt;
	double **OCPloadt;
	double *OCPCCt;
public:
	void inputinitdata();
	void initc();
	~SCHEDULE();
	//void outputtxt();
	void cyclecost();
	void setchangeinit();
	void errorcalculate();
	void inputdecisiondata();
	void decision();
	void inputfoundationdata();
	void inputstaticdata();
	void inputdynamicdata();
	void defaultvalue();
	void consumptioncurve(int);
	void inputdefaultvalue();

	int solveit(lprec*);
	void gridisland(lprec*,int);
	void scheduletodispachgriddata(lprec*);
	void scheduletodispachislanddata(lprec*);
	void CONTROLLABLEUNITconstraint(lprec*);
	void CONTROLLABLEUNITconsumption(lprec*);
	void ENERGYSTORAGEconstraint(lprec*,int);
	void GRIDconstraint(lprec*);
	void RENEWABLEENERGYconstraint(lprec*);
	void OVERALLBALANCEconstraint(lprec*);
	void LOSSconstraint(lprec*);
	
	void allconstraint(lprec*,int);
	void initlpsolve(lprec*);
	void getlossa();

	void set0();
	void CONTROLLABLEUNITconsumptionsimplify(lprec*);

	//void outputtxtlp();

	void totaltolay1_T();
	void totaltolay1_data();
	void totaltolay2_data(int,int);
	void initlpsolve_lay2(lprec*,int);

	void setchangeinit_lay2(int);
	void gridisland_lay2(lprec*,int,int);
	void GRIDconstraint_lay2(lprec*,int);

	void CONTROLLABLEUNITconstraint_lay2(lprec*,int);
	void CONTROLLABLEUNITconsumptionsimplify_lay2(lprec*,int);

	void CONTROLLABLEUNITconsumption_lay2(lprec*,int);

	void OVERALLBALANCEconstraint_lay2(lprec*,int);
	void LOSSconstraint_lay2(lprec*,int);
	void scheduletodispachislanddata_lay2(lprec*,int);
	void outputtxt_lay2();
	void lay2tototaldata_lay2(int,int);
	void setmodelinit_lay2(lprec*,int,int);
	void setmodelinit1_lay2(lprec*,int,int);
	void setmodelinit12_lay2(lprec*,int,int);

	void scheduletodispachgriddata_lay2(lprec*,int);

	//void totaltolay2_data_level(int,int);
	//void Pd1t_data(int,int);

	void VIRTUALGRIDconstraint(lprec*,int,int,int);
	void VIRTUALlevelIdentifier();
	void islanddo_levelpunish();
	void schedulislanddo_levelp(int);
	void schedulislanddolay2_levelp(int,int);
	void lpprepare_levelp(int);
	void object_lay2_levelp(lprec*,int,int,int);
	void object_levelp(lprec*,int,int);

	void griddo_levelpunish();
	void schedulgriddo_levelp(int);
	void schedulgriddolay2_levelp(int,int);

	void SumE();
	void Sum_object(lprec*,int,int);
	void Sum_constraint(lprec*);
	void Sum_lpprepare();
	void Sum_initlpsolve(lprec*);
	void Sum_do(int);
	void Sum_Odata(lprec*);
	void getloadcut(lprec*);
	void ENERGYSTORAGEconstraint_lay2_islandp(lprec*,int);
	void allconstraint_lay2_islandp(lprec*,int);
	void lpprepare_levelp_islandp(int);
	void RENEWABLEENERGYconstraint_lay2_islandp(lprec*,int);
	void Sum_islandschedule();

	void levelsearch();
	void getobject_lay2(int,int);
	void outputobject();
	void calculateloss();
	void inputscheduleloss();
	void outputlossa();
	void losssearch();
	void getlossa0();

	void inputOC();
	void calculateOC();

};


#endif