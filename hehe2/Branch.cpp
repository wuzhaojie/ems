#include "Branch.h"

Branch::Branch()
{
	Z=NULL;
	Is=NULL;
	Ie=NULL;
	B=NULL;
	loss=NULL;
	PQi=NULL;
	PQj=NULL;
}

//===============================================================================//
void Branch::Initialize(int n_)
{
	M=n_;
	N=n_;
	num=0;
	type=1;
	i=1;
	j=1;
	lossa=0;

	int k;
	int l;

	loss=new Complex[M+1];
	for (k=0;k<=M;k++)
		loss[k].set(0,0);

	PQi=new Complex[M+1];
	for (k=0;k<=M;k++)
		PQi[k].set(0,0);

	PQj=new Complex[M+1];
	for (k=0;k<=M;k++)
		PQj[k].set(0,0);

	Z=(Complex **)new Complex[M+1];
	for(k=0;k<=M;k++)
		Z[k]=new Complex[N+1];
	for(k=1;k<=M;k++)
		for(l=1;l<=N;l++)
			Z[k][l].set(0,0);

	B=(Complex **)new Complex[M+1];
	for(k=0;k<=M;k++)
		B[k]=new Complex[N+1];
	for(k=1;k<=M;k++)
		for(l=1;l<=N;l++)
			B[k][l].set(0,0);

//	for (k=0;k<=M;k++)
		Is=new Complex[M+1];
		for (k=1;k<=M;k++)
			Is[k].set(0,0);

		Ie=new Complex[M+1];
		for (k=1;k<=M;k++)
			Ie[k].set(0,0);

}
//===============================================================================//
Branch::~Branch()
{
	Release();
}
//===============================================================================//
void Branch::Release()					//ÏÔÊ½ÊÍ·ÅÄÚ´æ
{
	if (Z!=NULL)
	{
		for(int k=0;k<=M;k++)
			delete []Z[k]; 
		delete []Z;	
		Z=NULL;
	}

	if (B!=NULL)
	{
		for(int k=0;k<=M;k++)
			delete []B[k]; 
		delete []B;	
		B=NULL;
	}

	if (Is!=NULL)
	{
		delete []Is;	
		Is=NULL;
	}

	if (Ie!=NULL)
	{
		delete []Ie;	
		Ie=NULL;
	}
	if (loss!=NULL)
	{
		delete []loss;	
		loss=NULL;
	}
	if (PQi!=NULL)
	{
		delete []PQi;	
		PQi=NULL;
	}
	if (PQj!=NULL)
	{
		delete []PQj;	
		PQj=NULL;
	}
}

void Branch::Print()
{
	Complex f1;
	for(int k=1;k<=M;k++)
	{
		for(int l=1;l<=N;l++)
		{
			f1=Z[k][l];
			//cout<<f1<<endl;
		}
		//cout<<endl;
	}
}