#include "MyComplex.h"
//#define phase 3;

class Tran
{
public:
	int M,N;													//
	//
	int num;
	int Ti;
	int Tj;
	double K;
	double angle;
	int zeroi;
	int zeroj;
	int brannum;
	Complex **Z;
	Complex *Ie;
//	Complex *PQ;

public:
	Tran();
	void Initialize(int);
	void Release();												//显式释放内存
	void Print();										//输出矩阵	
	~Tran();
};