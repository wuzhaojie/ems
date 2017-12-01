#include "MyComplex.h"
//#define phase 3;

class Node
{
public:
	int M,N;													//
	//
	int num;
	int lev;
	int pare;
	int bran;
	Complex *U;
	Complex *I;
	Complex *PQ;
	double ID32;

public:
	Node();
	void Initialize(int);
	void Release();												//显式释放内存
	void Print();										//输出矩阵	
	~Node();
};