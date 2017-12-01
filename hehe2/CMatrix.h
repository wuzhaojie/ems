//===============================================================================//
//
//								矩阵类 CMatrix
//					M×N的二维满阵，实数类型  也可以表示向量
//
//													编制：西安交大  王建学
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

#define EXIT {printf("......矩阵不匹配!\n");exit(0);}			//exit(0); 对应头文件 <stdlib.h>

class CMatrix
{
public:
	int M,N;													//M*N 的矩阵
	double **PMatrix;											//PMatrix 存实数数据  满阵形式

public:
	CMatrix();
	CMatrix(CMatrix &);
	void Initialize(int,int);
	void Release();												//显式释放内存
	~CMatrix();

	CMatrix T();												//转置操作
	CMatrix Invert();											//矩阵取逆			
	CMatrix Mul(double);										//矩阵乘以常数			
	void operator = (CMatrix &);									//赋值操作，不能用友元，需定义为成员函数  
	friend CMatrix operator + (CMatrix &,CMatrix &);				//
	friend CMatrix operator - (CMatrix &,CMatrix &);				//
	friend CMatrix operator * (CMatrix &,CMatrix &);				//
	
	void SetBlock(int x,int y,CMatrix &a);						//将小矩阵a赋给从(x,y)点开始的矩阵块
	void TSetBlock(int x,int y,CMatrix &a);						//将小矩阵a转置后赋给从(x,y)点开始的矩阵块
	void Add(int x,int y,double fValue);						//将value与矩阵点(x,y)相加，结果存在矩阵点(x,y)中
	void MaxMinMatrix(double& Max,double &Min);					//返回矩阵最大最小值
	void SetZero();												//将矩阵清零
	
	void CMatrix::Print();										//输出矩阵	
	void CMatrix::Print(ofstream f);							//重载输出矩阵	
};

#endif CMatrix_H

/*

main()			//矩阵类测试用句
{
  	cout<<"				△△矩阵测试△△	                "<<endl;
	CMatrix M;		M.Initialize(2,3);
	M.PMatrix[1][1]=1;		M.PMatrix[1][2]=3;		M.PMatrix[1][3]=5;	
	M.PMatrix[2][1]=2;		M.PMatrix[2][2]=4;		M.PMatrix[2][3]=8;	
//	M.PMatrix[3][1]=7;		M.PMatrix[3][2]=9;		M.PMatrix[3][3]=2;	
	cout<<"				矩阵A	                "<<endl;
	M.Print();

	CMatrix MM;		MM.Initialize(2,3);
	cout<<"				赋值		                "<<endl;
	MM=M;
	MM.Print();	

	CMatrix MM1;	MM1.Initialize(3,2);
	cout<<"				转置		                "<<endl;
	MM1=M.T();
	MM1.Print();
	cout<<"				转置再装置	                "<<endl;
	((M.T()).T()).Print();

	cout<<"				乘以常数 3	                "<<endl;
	(M.Mul(3)).Print();
	
	CMatrix M0;		M0.Initialize(2,3);
	M0.PMatrix[1][1]=2;		M0.PMatrix[1][2]=6;		M0.PMatrix[1][3]=10;	
	M0.PMatrix[2][1]=4;		M0.PMatrix[2][2]=8;		M0.PMatrix[2][3]=16;	
	cout<<"				矩阵B	                "<<endl;
	M0.Print();

	CMatrix MM2;	MM2.Initialize(2,3);
	MM2=M+M0;
	cout<<"				矩阵A+B	                "<<endl;
	MM2.Print();
	
	CMatrix MM3;	MM3.Initialize(2,3);
	MM3=M-M0;
	cout<<"				矩阵A-B	                "<<endl;
	MM3.Print();

	CMatrix M1;		M1.Initialize(3,2);
	M1.PMatrix[1][1]=2;		M1.PMatrix[1][2]=4;		
	M1.PMatrix[2][1]=1;		M1.PMatrix[2][2]=3;
	M1.PMatrix[3][1]=3;		M1.PMatrix[3][2]=1;	
	cout<<"				矩阵C	                "<<endl;
	M1.Print();

	CMatrix MM4;	MM4.Initialize(2,2);
	MM4=M*M1;
	cout<<"				矩阵A*C	                "<<endl;
	MM4.Print();

	CMatrix MM5;	MM5.Initialize(3,3);
	MM5=M1*M;
	cout<<"				矩阵C*A	                "<<endl;
	MM5.Print();
	
	CMatrix M2;		M2.Initialize(2,2);
	M2.PMatrix[1][1]=20;		M2.PMatrix[1][2]=40;		
	M2.PMatrix[2][1]=10;		M2.PMatrix[2][2]=30;
	cout<<"				矩阵D	                "<<endl;
	M2.Print();

	cout<<"				矩阵块D 从(1,2)赋给A	                "<<endl;
	M.SetBlock(1,2,M2);
	M.Print();

	cout<<"				矩阵块D转置后 从(1,2)赋给A	                "<<endl;
	M.TSetBlock(1,2,M2);
	M.Print();
}
 */