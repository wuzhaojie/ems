#include "MyComplex.h"
//#define phase 3;

class Var
{
public:
	int M,N;													//
	//
	int num;
	int nodenum;
	Complex *Q;


public:
	Var();
	void Initialize(int);
	void Release();												//显式释放内存
	void Print();										//输出矩阵	
	~Var();
};