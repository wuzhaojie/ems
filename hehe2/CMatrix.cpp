//===============================================================================//
//
//								矩阵类 CMatrix
//							M×N的满阵，实数类型
//
//													编制：西安交大  王建学
//																	2004.9.15		
//===============================================================================//
//空间释放问题已经得到解决	2007.10
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
void CMatrix::Release()					//显式释放内存
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
void CMatrix::Print(ofstream f)							//重载输出矩阵	
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
CMatrix CMatrix::T()				//转置
{
	CMatrix mt;
	mt.Initialize(N,M);
	for(int i=1;i<=M;i++)
		for(int j=1;j<=N;j++)
			mt.PMatrix[j][i]=PMatrix[i][j];
	return (mt);
}
//===============================================================================//
CMatrix CMatrix::Invert()			//求逆阵 前提：须是方阵	 思路：1列1列通过解方程方法求出
{
	int i,j;
	if(M!=N)	{	cout<<"必须是方阵才能求逆！"<<endl;	EXIT;}
	CMatrix mt;
	mt.Initialize(M,M);
	
	double* pEquationLeft;
	double *EquationRight=new double[M+1];             //三角分解时所求方程中等式右边的向量 
	double *EquationLeft=new double[M+1];              //三角分解时所求方程中等式左边的代求变量的偏移量 

	double **A=new double*[M+1];						//三角分解时所求方程中等式左边的系数矩阵
	for(int i=0;i<=M;i++)
		A[i]=new double[M+1];
	
	for(i=1;i<=M;i++)
		for(int j=1;j<=M;j++)
			A[i][j]=PMatrix[i][j]; 

	Equation Eq(M);
	for(i=1;i<=M;i++)
	{
		//构成一个向量，这个向量只有第i个元素等于1，其他元素等于0
		for(int j=1;j<=M;j++)EquationRight[j]=0;
		EquationRight[i]=1;
		
		pEquationLeft=Eq.FullMatrixLUDecompose(EquationRight,A);

		for(j=1;j<=M;j++)
		{
			EquationLeft[j]=*pEquationLeft;
			mt.PMatrix[j][i]=EquationLeft[j];			//是一列，特征是列数同而行数不一样
			pEquationLeft++;	
		}
	}
			
	delete[]EquationRight,EquationLeft,pEquationLeft;
	for(	i=0;i<=M;i++)delete[]A[i];		delete[] A;
	
	return (mt);
}
//===============================================================================//
CMatrix CMatrix::Mul(double c)										//矩阵乘以常数	
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
	if(PMatrix==NULL)							//释放内存	
	{
		PMatrix=(double **)new double[M+1];		//重新开辟内存  解决指针悬挂问题
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
void CMatrix::SetBlock(int x,int y,CMatrix &a)//将小矩阵a赋给从(x,y)点开始的矩阵块
{
	if(x+a.M-1>M||y+a.N-1>N||x<=0||y<=0)	EXIT;

	for(int i=1;i<=a.M;i++)
		for(int j=1;j<=a.N;j++)
			PMatrix[i+x-1][j+y-1]=a.PMatrix[i][j];	
}
//===============================================================================//
void CMatrix::TSetBlock(int x,int y,CMatrix &a)//将小矩阵a赋给从(x,y)点开始的矩阵块
{
	SetBlock(x,y,a.T());
}
//===============================================================================//
void CMatrix::Add(int x,int y,double fValue)						//将value与矩阵点(x,y)相加，结果存在矩阵点(x,y)中
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
void CMatrix::SetZero()					//将矩阵清零
{
	for(int i=1;i<=M;i++)
		for(int j=1;j<=N;j++)
			PMatrix[i][j]=0;
}
//===============================================================================//

