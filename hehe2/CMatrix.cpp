//===============================================================================//
//
//								������ CMatrix
//							M��N������ʵ������
//
//													���ƣ���������  ����ѧ
//																	2004.9.15		
//===============================================================================//
//�ռ��ͷ������Ѿ��õ����	2007.10
//===============================================================================//

#include "CMatrix.h"
#include "Equation.h"
/*
#include <math.h>

#include <stdio.h>
#include <fstream>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
*/

//===============================================================================//
CMatrix::CMatrix()
{
	PMatrix=NULL;
}
CMatrix::CMatrix(CMatrix &mt)
{
	M=mt.M;
	N=mt.N;
	Initialize(M,N);
	int i;
	int j;
	for(i=1;i<=M;i++)
		for(j=1;j<=N;j++)
			PMatrix[i][j]=mt.PMatrix[i][j];	
}

//===============================================================================//
void CMatrix::Initialize(int m_,int n_)
{
	M=m_;
	N=n_;
	int i;
	PMatrix=(double **)new double[M+1];
	for(i=0;i<=M;i++)
		PMatrix[i]=new double[N+1];
	for(i=1;i<=M;i++)
		for(int j=1;j<=N;j++)
			PMatrix[i][j]=0.0;
}
//===============================================================================//
CMatrix::~CMatrix()
{
	Release();
}
//===============================================================================//
void CMatrix::Release()					//��ʽ�ͷ��ڴ�
{
	if (PMatrix!=NULL)
	{
		for(int i=0;i<=M;i++)
			delete []PMatrix[i]; 
		delete []PMatrix;	
		PMatrix=NULL;
		
	}
}//===============================================================================//
void CMatrix::Print()
{
	double f1;
	for(int i=1;i<=M;i++)
	{
		for(int j=1;j<=N;j++)
		{
			f1=PMatrix[i][j];
			if(fabs(f1)<1.0e-7)f1=0;
			//cout<<f1<<"  ";
		}
		//cout<<endl;
	}
}
//===============================================================================//
void CMatrix::Print(ofstream f)							//�����������	
{
	double f1;
	for(int i=1;i<=M;i++)
	{
		for(int j=1;j<=N;j++)
		{
			f1=PMatrix[i][j];
			if(fabs(f1)<1.0e-7)f1=0;
			f<<f1<<"  ";
		}
		f<<endl;
	}
}

//===============================================================================//
CMatrix CMatrix::T()				//ת��
{
	CMatrix mt;
	mt.Initialize(N,M);
	for(int i=1;i<=M;i++)
		for(int j=1;j<=N;j++)
			mt.PMatrix[j][i]=PMatrix[i][j];
	return (mt);
}
//===============================================================================//
CMatrix CMatrix::Invert()			//������ ǰ�᣺���Ƿ���	 ˼·��1��1��ͨ���ⷽ�̷������
{
	int i,j;
	if(M!=N)	{	cout<<"�����Ƿ���������棡"<<endl;	EXIT;}
	CMatrix mt;
	mt.Initialize(M,M);
	
	double* pEquationLeft;
	double *EquationRight=new double[M+1];             //���Ƿֽ�ʱ���󷽳��е�ʽ�ұߵ����� 
	double *EquationLeft=new double[M+1];              //���Ƿֽ�ʱ���󷽳��е�ʽ��ߵĴ��������ƫ���� 

	double **A=new double*[M+1];						//���Ƿֽ�ʱ���󷽳��е�ʽ��ߵ�ϵ������
	for(int i=0;i<=M;i++)
		A[i]=new double[M+1];
	
	for(i=1;i<=M;i++)
		for(int j=1;j<=M;j++)
			A[i][j]=PMatrix[i][j]; 

	Equation Eq(M);
	for(i=1;i<=M;i++)
	{
		//����һ���������������ֻ�е�i��Ԫ�ص���1������Ԫ�ص���0
		for(int j=1;j<=M;j++)EquationRight[j]=0;
		EquationRight[i]=1;
		
		pEquationLeft=Eq.FullMatrixLUDecompose(EquationRight,A);

		for(j=1;j<=M;j++)
		{
			EquationLeft[j]=*pEquationLeft;
			mt.PMatrix[j][i]=EquationLeft[j];			//��һ�У�����������ͬ��������һ��
			pEquationLeft++;	
		}
	}
			
	delete[]EquationRight,EquationLeft,pEquationLeft;
	for(	i=0;i<=M;i++)delete[]A[i];		delete[] A;
	
	return (mt);
}
//===============================================================================//
CMatrix CMatrix::Mul(double c)										//������Գ���	
{
	CMatrix mt;
	mt.Initialize(M,N);
	for(int i=1;i<=M;i++)
		for(int j=1;j<=N;j++)
			mt.PMatrix[i][j]=c*PMatrix[i][j];
	return (mt);
}
//===============================================================================//
void CMatrix::operator = (CMatrix &m)
{
	if(m.M!=M || m.N!=N)EXIT;
	int i;
	if(PMatrix==NULL)							//�ͷ��ڴ�	
	{
		PMatrix=(double **)new double[M+1];		//���¿����ڴ�  ���ָ����������
		for(i=0;i<=M;i++)
			PMatrix[i]=new double[N+1];
	}
	for(i=1;i<=M;i++)
		for(int j=1;j<=N;j++)
			PMatrix[i][j]=m.PMatrix[i][j];	
}
//===============================================================================//
CMatrix operator +(CMatrix &a,CMatrix &b)
{
	if((a.M!=b.M)||(a.N!=b.N))EXIT;
	CMatrix c;
	c.Initialize(a.M,a.N);
	for(int i=1;i<=a.M;i++)
		for(int j=1;j<=a.N;j++)
			c.PMatrix[i][j]=a.PMatrix[i][j]+b.PMatrix[i][j];	
	return(c);
}
//===============================================================================//
CMatrix operator -(CMatrix &a, CMatrix &b)
{
	if((a.M!=b.M)||(a.N!=b.N))EXIT;
	CMatrix c;
	c.Initialize(a.M,a.N);

	for(int i=1;i<=a.M;i++)
		for(int j=1;j<=a.N;j++)
			c.PMatrix[i][j]=a.PMatrix[i][j]-b.PMatrix[i][j];	
	return(c);
}
//===============================================================================//
CMatrix operator *(CMatrix &a,CMatrix &b)
{
	if(a.N!=b.M)EXIT;
	CMatrix c;
	c.Initialize(a.M,b.N);

	for(int i=1;i<=c.M;i++)
		for(int j=1;j<=c.N;j++)
		{
			c.PMatrix[i][j]=0;
			for(int k=1;k<=a.N;k++)
				c.PMatrix[i][j]+=a.PMatrix[i][k]*b.PMatrix[k][j];
		}
	return(c);
}
//===============================================================================//
void CMatrix::SetBlock(int x,int y,CMatrix &a)//��С����a������(x,y)�㿪ʼ�ľ����
{
	if(x+a.M-1>M||y+a.N-1>N||x<=0||y<=0)	EXIT;

	for(int i=1;i<=a.M;i++)
		for(int j=1;j<=a.N;j++)
			PMatrix[i+x-1][j+y-1]=a.PMatrix[i][j];	
}
//===============================================================================//
void CMatrix::TSetBlock(int x,int y,CMatrix &a)//��С����a������(x,y)�㿪ʼ�ľ����
{
	SetBlock(x,y,a.T());
}
//===============================================================================//
void CMatrix::Add(int x,int y,double fValue)						//��value������(x,y)��ӣ�������ھ����(x,y)��
{
	PMatrix[x][y]+=fValue;
}
//===============================================================================//
void CMatrix::MaxMinMatrix(double &Max,double &Min)
{
	Max=-1E10;	Min=1E10;
	for(int i=1;i<=M;i++)
		for(int j=1;j<=N;j++)
		{
			if(PMatrix[i][j]>Max)Max=PMatrix[i][j];
			if(PMatrix[i][j]<Min)Min=PMatrix[i][j];
		}
}
//===============================================================================//
void CMatrix::SetZero()					//����������
{
	for(int i=1;i<=M;i++)
		for(int j=1;j<=N;j++)
			PMatrix[i][j]=0;
}
//===============================================================================//

