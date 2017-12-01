//===============================================================================//
//
//								���� Equation�����
//							N��N������ʵ������
//
//													���ƣ���������  DXY WJX
//																	2004.9.15		
//===============================================================================//
#include "Equation.h"

//===============================================================================//
Equation::Equation(int n_)
{
	N=n_;
}
//===============================================================================//
Equation::~Equation(){}
//����������������������������������������������������������������������������������������
//                 �������Ƿֽ�ĳ���˵�����������ĵ� 
//������������������������������������������������������������������������������������������
//===============================================================================//
//����LU�ֽ�  ���ڷǶԳ�ϵ������ķ������ �磺����ϵͳ�г����������
double* Equation::FullMatrixLUDecompose(double* constant,double** coefficient)
{
    int nd=N;

	int i,r,k;
	double SumL,Sumu,Sumy,Sumx;
	double* pLU;
    double **u=new double*[nd+1];
	for(i=0;i<=nd;i++)
		u[i]=new double[nd+1];

	double **l=new double*[nd+1];
	for(i=0;i<=nd;i++)
		l[i]=new double[nd+1];

	double *midleVariable=new double[nd+1];
	
	double *unknow=new double[nd+1];
    
    /*for(i=1;i<=nd;i++)	
	{
        constant[i]=0;
        for(r=1;r<=nd;r++)
            constant[i]-=-coefficient[i][r];
	}*/

    for(i=1;i<=nd;i++)//initiate
	{
        for(r=1;r<=nd;r++)
		{
            l[i][r]=0;
            u[i][r]=0;
        }
        midleVariable[i]=0;
		unknow[i]=0;
    }

    for(i=1;i<=nd;i++)
	{
        u[1][i]=coefficient[1][i];
        if(i>=2)
		{
			l[i][1]=coefficient[i][1]/u[1][1];
		}
    }

    for(r=2;r<=nd;r++)
	{
        for(i=r;i<=nd;i++)
		{
            Sumu=0;
            for(k=1;k<=r-1;k++)
                Sumu+=l[r][k]*u[k][i];
            u[r][i]=coefficient[r][i]-Sumu;
        }
        for(i=r+1;i<=nd;i++)
		{
            SumL=0;
            if(r!=nd)
			{
                for(k=1;k<=r-1;k++)
				{
                    SumL+=l[i][k]*u[k][r];
                    l[i][r]=(coefficient[i][r]-SumL)/u[r][r];
                }
            }
        }
    }
    midleVariable[1]=constant[1];

    for(i=2;i<=nd;i++)
	{
        Sumy=0;
        for(k=1;k<=i-1;k++)
            Sumy+=l[i][k]*midleVariable[k];
        midleVariable[i]=constant[i]-Sumy;
    }

    unknow[nd]=midleVariable[nd]/u[nd][nd];

    for(i=nd-1;i>=1;i--)
	{
        Sumx=0;
        for(k=i+1;k<=nd;k++)
            Sumx+=u[i][k]*unknow[k];
        unknow[i]=(midleVariable[i]-Sumx)/u[i][i];
    }

    pLU=&unknow[1];
	return pLU;											//		

	for(i=0;i<=nd;i++)delete []u[i];			delete []u;
	for(i=0;i<=nd;i++)delete []l[i];			delete []l;
	delete []midleVariable;		delete []unknow;
}
//===============================================================================//
//����LDL�ֽ�  ���ڶԳ�ϵ������ķ������ �磺����ϵͳ���ڵ������������
double* Equation::FullMatrixLDLDecompose(double* constant,double** coefficient)
{
    int nd=N;
	int i,r,k;
    double SumL, Sumd,Sumy,Sumx;
	double* pLDL;

	double *midleVariable;
	midleVariable=new double[nd+1];

	double *unknow=new double[nd+1];
	
	double **low=new double*[nd+1];
	for(i=0;i<=nd;i++)
		low[i]=new double[nd+1];

	double *diagonal=new double[nd+1];

    

//�ֽ���������Ǿ���low�����ͶԽǾ���diagonal������ֵ
    for(i=1;i<=nd;i++)
	{
        diagonal[i]=0;
        for(r=1;r<=nd;r++)
            low[i][r]=0;
	}

	/*for(i=1;i<=nd;i++)
	{
      constant[i]=0;
        for(r=1;r<=nd;r++)
           constant[i]+=coefficient[i][r];
    }*/

    for(i=1;i<=nd;i++)
	{
        Sumd=0;
        for(k=1;k<=i-1;k++)
		{
            SumL=0;
            for(r=1;r<=k-1;r++)
                SumL+=low[i][r]*diagonal[r]*low[k][r];
            low[i][k]=(coefficient[i][k]-SumL)/diagonal[k];
            Sumd+=low[i][k]*low[i][k]*diagonal[k];
        }
        diagonal[i]=coefficient[i][i]-Sumd;
    }
    
//ǰ��
    midleVariable[1]=constant[1];
    for(i=2;i<=nd;i++)
	{
        Sumy=0;
        for(k=1;k<=i-1;k++)
            Sumy+=low[i][k]*midleVariable[k];
        midleVariable[i]=constant[i]-Sumy;
    }
    
//�ش�
    unknow[nd]=midleVariable[nd]/diagonal[nd];
    for(i=nd-1;i>=1;i--)
	{
        Sumx=0;
        for(k=i+1;k<=nd;k++)
            Sumx+=low[k][i]*unknow[k];
        unknow[i]=midleVariable[i]/diagonal[i]-Sumx;
    }
    pLDL=&unknow[1];
	return pLDL;

	delete []midleVariable;					delete []unknow;	
	for(i=0;i<=nd;i++)delete []low[i];		delete []low;
	delete []diagonal;
}