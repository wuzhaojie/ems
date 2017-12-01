#include "Var.h"

Var::Var()
{
	//Z=NULL;
	Q=NULL;
	//PQ=NULL;
	//	B=NULL;
}

//===============================================================================//
void Var::Initialize(int n_)
{
	M=n_;
	N=n_;
	num=0;
	nodenum=0;

	int i;
//	int j;

	Q=new Complex[M+1];
	for (i=1;i<=M;i++)
		Q[i].set(0,0);

}
//===============================================================================//
Var::~Var()
{
	Release();
}
//===============================================================================//
void Var::Release()					//ÏÔÊ½ÊÍ·ÅÄÚ´æ
{
	if (Q!=NULL)
	{
		delete []Q;	
		Q=NULL;
	}
}

void Var::Print()
{

}