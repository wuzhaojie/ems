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
	Complex *PQi;//��·���˹���
	Complex *PQj;
	Complex *Is;
	Complex *Ie;
	Complex **Z;
	Complex **B;
	double lossa;

public:
	Branch();
	void Initialize(int);
	void Release();												//��ʽ�ͷ��ڴ�
    void Print();										//�������	
	~Branch();
};