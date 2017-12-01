//===============================================================================//
//
//								������ CMatrix
//					M��N�Ķ�ά����ʵ������  Ҳ���Ա�ʾ����
//
//													���ƣ���������  ����ѧ
//																	2004.9.15		
//===============================================================================//
#ifndef CMatrix_H
#define CMatrix_H


#include <math.h>

#include <stdio.h>
#include <fstream>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define EXIT {printf("......����ƥ��!\n");exit(0);}			//exit(0); ��Ӧͷ�ļ� <stdlib.h>

class CMatrix
{
public:
	int M,N;													//M*N �ľ���
	double **PMatrix;											//PMatrix ��ʵ������  ������ʽ

public:
	CMatrix();
	CMatrix(CMatrix &);
	void Initialize(int,int);
	void Release();												//��ʽ�ͷ��ڴ�
	~CMatrix();

	CMatrix T();												//ת�ò���
	CMatrix Invert();											//����ȡ��			
	CMatrix Mul(double);										//������Գ���			
	void operator = (CMatrix &);									//��ֵ��������������Ԫ���趨��Ϊ��Ա����  
	friend CMatrix operator + (CMatrix &,CMatrix &);				//
	friend CMatrix operator - (CMatrix &,CMatrix &);				//
	friend CMatrix operator * (CMatrix &,CMatrix &);				//
	
	void SetBlock(int x,int y,CMatrix &a);						//��С����a������(x,y)�㿪ʼ�ľ����
	void TSetBlock(int x,int y,CMatrix &a);						//��С����aת�ú󸳸���(x,y)�㿪ʼ�ľ����
	void Add(int x,int y,double fValue);						//��value������(x,y)��ӣ�������ھ����(x,y)��
	void MaxMinMatrix(double& Max,double &Min);					//���ؾ��������Сֵ
	void SetZero();												//����������
	
	void CMatrix::Print();										//�������	
	void CMatrix::Print(ofstream f);							//�����������	
};

#endif CMatrix_H

/*

main()			//����������þ�
{
  	cout<<"				����������ԡ���	                "<<endl;
	CMatrix M;		M.Initialize(2,3);
	M.PMatrix[1][1]=1;		M.PMatrix[1][2]=3;		M.PMatrix[1][3]=5;	
	M.PMatrix[2][1]=2;		M.PMatrix[2][2]=4;		M.PMatrix[2][3]=8;	
//	M.PMatrix[3][1]=7;		M.PMatrix[3][2]=9;		M.PMatrix[3][3]=2;	
	cout<<"				����A	                "<<endl;
	M.Print();

	CMatrix MM;		MM.Initialize(2,3);
	cout<<"				��ֵ		                "<<endl;
	MM=M;
	MM.Print();	

	CMatrix MM1;	MM1.Initialize(3,2);
	cout<<"				ת��		                "<<endl;
	MM1=M.T();
	MM1.Print();
	cout<<"				ת����װ��	                "<<endl;
	((M.T()).T()).Print();

	cout<<"				���Գ��� 3	                "<<endl;
	(M.Mul(3)).Print();
	
	CMatrix M0;		M0.Initialize(2,3);
	M0.PMatrix[1][1]=2;		M0.PMatrix[1][2]=6;		M0.PMatrix[1][3]=10;	
	M0.PMatrix[2][1]=4;		M0.PMatrix[2][2]=8;		M0.PMatrix[2][3]=16;	
	cout<<"				����B	                "<<endl;
	M0.Print();

	CMatrix MM2;	MM2.Initialize(2,3);
	MM2=M+M0;
	cout<<"				����A+B	                "<<endl;
	MM2.Print();
	
	CMatrix MM3;	MM3.Initialize(2,3);
	MM3=M-M0;
	cout<<"				����A-B	                "<<endl;
	MM3.Print();

	CMatrix M1;		M1.Initialize(3,2);
	M1.PMatrix[1][1]=2;		M1.PMatrix[1][2]=4;		
	M1.PMatrix[2][1]=1;		M1.PMatrix[2][2]=3;
	M1.PMatrix[3][1]=3;		M1.PMatrix[3][2]=1;	
	cout<<"				����C	                "<<endl;
	M1.Print();

	CMatrix MM4;	MM4.Initialize(2,2);
	MM4=M*M1;
	cout<<"				����A*C	                "<<endl;
	MM4.Print();

	CMatrix MM5;	MM5.Initialize(3,3);
	MM5=M1*M;
	cout<<"				����C*A	                "<<endl;
	MM5.Print();
	
	CMatrix M2;		M2.Initialize(2,2);
	M2.PMatrix[1][1]=20;		M2.PMatrix[1][2]=40;		
	M2.PMatrix[2][1]=10;		M2.PMatrix[2][2]=30;
	cout<<"				����D	                "<<endl;
	M2.Print();

	cout<<"				�����D ��(1,2)����A	                "<<endl;
	M.SetBlock(1,2,M2);
	M.Print();

	cout<<"				�����Dת�ú� ��(1,2)����A	                "<<endl;
	M.TSetBlock(1,2,M2);
	M.Print();
}
 */