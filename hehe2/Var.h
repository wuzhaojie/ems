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
	void Release();												//��ʽ�ͷ��ڴ�
	void Print();										//�������	
	~Var();
};