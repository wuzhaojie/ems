#include "OriginalData.h"
#include "Branch.h"
#include "Node.h"
#include "Tran.h"
#include "Var.h"
#include "Des.h"
#include "MyComplex.h"


class BackforePowerflow
{
public:
	int Phase;
	int root;
	double Sbase;
	int nlevel;
	int netflag;
	int **level;
	double **Xmatr;
	Complex **Ztran;
	Complex **Tmatrix;
	int *pvrecord;
	int **Dgnode;
	int nDgnode;
	OriginalData Data;
	Branch *branch;
	Node *node;
	Tran *tran;
	Var *var;
	Des *des;
	double *Power;
	double *vPower;
	Complex dI;
	//hehe
	//double PL[9+1][144+1];
    //double PG[4+1][144+1];
	double *branchloss;
	//double **PL;
	//double **PG;
	int pvnumtemp;

	void Initilization(int);
	double mini(double,double);
	double maxi(double,double);
	int check(int,int *,int);
	int findbranch(int,int);
	int findTrans(int);
	int findDgnode(int*,int);
	void Ztranmatrix(int,int,double,double,Complex**,int);
	void Tranmatrix(int,int,double,double,int,int);
	void Dgnodeset();
	void Levelset();
	void formalX();
	void dgset(double **);
	void pvaddQ();
	void calculate(double);
	void output();
	//void inputschedule();
	~BackforePowerflow();
	BackforePowerflow();
	void releaseflow();
	
protected:
private:
};