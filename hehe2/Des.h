#include "MyComplex.h"
//#define phase 3;

class Des
{
public:
	int M,N;													//
	//
	int num;
	int type;
	int nodenum;

	double *V;
	double *P;
	double *Q;
	double *Qmin;
	double *Qmax;
	//	Complex *PQ;

public:
	Des();
	void Initialize(int);
	void Release();												//��ʽ�ͷ��ڴ�
	void Print();										//�������	
	~Des();
};