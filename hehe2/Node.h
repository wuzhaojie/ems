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
	void Release();												//��ʽ�ͷ��ڴ�
	void Print();										//�������	
	~Node();
};