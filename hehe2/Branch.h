#include "MyComplex.h"
//#define phase 3;

class Branch
{
public:
	int M,N;													//
											//
	int num;
	int i;
	int j;
	int type;
	Complex *loss;
	Complex *PQi;//线路两端功率
	Complex *PQj;
	Complex *Is;
	Complex *Ie;
	Complex **Z;
	Complex **B;
	double lossa;

public:
	Branch();
	void Initialize(int);
	void Release();												//显式释放内存
    void Print();										//输出矩阵	
	~Branch();
};