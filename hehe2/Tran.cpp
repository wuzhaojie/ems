#include "Tran.h"

Tran::Tran()
{
	Z=NULL;
	Ie=NULL;
	//PQ=NULL;
	//	B=NULL;
}

//===============================================================================//
void Tran::Initialize(int n_)
{
	M=n_;
	N=n_;
	num=0;
	Ti=1;
	Tj=1;
	K=1;
	angle=0;
	zeroi=1;
	zeroj=1;
	brannum=0;

	int i;
	int j;


	Z=(Complex **)new Complex[M+1];
	for(i=0;i<=M;i++)
		Z[i]=new Complex[N+1];
	for(i=1;i<=M;i++)
		for(j=1;j<=N;j++)
			Z[i][j].set(0,0);

	Ie=new Complex[M+1];
	for (i=1;i<=M;i++)
		Ie[i].set(0,0);

}
//===============================================================================//
Tran::~Tran()
{
	Release();
}
//===============================================================================//
void Tran::Release()					//ÏÔÊ½ÊÍ·ÅÄÚ´æ
{
	if (Z!=NULL)
	{
		for(int i=0;i<=M;i++)
			delete []Z[i]; 
		delete []Z;	
		Z=NULL;
	}

	if (Ie!=NULL)
	{
		delete []Ie;	
		Ie=NULL;
	}
}

void Tran::Print()
{

}