#include "Node.h"

Node::Node()
{
	U=NULL;
	I=NULL;
	PQ=NULL;
//	B=NULL;
}

//===============================================================================//
void Node::Initialize(int n_)
{
	M=n_;
	N=n_;
	num=0;
	lev=1;
	pare=0;
	bran=0;
	int i;
//	int j;
	ID32=0;


	//	for (i=0;i<=M;i++)
	U=new Complex[M+1];
	for (i=1;i<=M;i++)
		U[i].set(1,0);

	I=new Complex[M+1];
	for (i=1;i<=M;i++)
		I[i].set(0,0);

	PQ=new Complex[M+1];
	for (i=1;i<=M;i++)
		PQ[i].set(0,0);
}
//===============================================================================//
Node::~Node()
{
	Release();
}
//===============================================================================//
void Node::Release()					//ÏÔÊ½ÊÍ·ÅÄÚ´æ
{


	if (U!=NULL)
	{
		delete []U;	
		U=NULL;
	}

	if (I!=NULL)
	{
		delete []I;	
		I=NULL;
	}

	if (PQ!=NULL)
	{
		delete []PQ;	
		PQ=NULL;
	}
}

void Node::Print()
{

}