#include "Des.h"

Des::Des()
{
	V=NULL;
	P=NULL;
	Q=NULL;
	Qmin=NULL;
	Qmax=NULL;
	//PQ=NULL;
	//	B=NULL;
}

//===============================================================================//
void Des::Initialize(int n_)
{
	M=n_;
	N=n_;
	num=0;
	nodenum=0;
	type=1;

	int i;
//	int j;

	V=new double[M+1];
	for (i=1;i<=M;i++)
		V[i]=1;

	P=new double[M+1];
	for (i=1;i<=M;i++)
		P[i]=0;

	Q=new double[M+1];
	for (i=1;i<=M;i++)
		Q[i]=0;

	Qmin=new double[M+1];
	for (i=1;i<=M;i++)
		Qmin[i]=0;

	Qmax=new double[M+1];
	for (i=1;i<=M;i++)
		Qmax[i]=0;
}
//===============================================================================//
Des::~Des()
{
	Release();
}
//===============================================================================//
void Des::Release()					//ÏÔÊ½ÊÍ·ÅÄÚ´æ
{
	if (V!=NULL)
	{
		delete []V;	
		V=NULL;
	}
	if (P!=NULL)
	{
		delete []P;	
		P=NULL;
	}
	if (Q!=NULL)
	{
		delete []Q;	
		Q=NULL;
	}
	if (Qmin!=NULL)
	{
		delete []Qmin;	
		Qmin=NULL;
	}
	if (Qmax!=NULL)
	{
		delete []Qmax;	
		Qmax=NULL;
	}
}

void Des::Print()
{

}