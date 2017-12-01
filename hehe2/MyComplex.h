//===============================================================================//
//
//								复数类 Complex
//									实数类型
//注：对网上源程序进行改进
//													编制：西安交大  王建学
//																	2007.12.10		
//===============================================================================//
#ifndef MyComplex_H
#define MyComplex_H

#include<iostream>
//#include<stdio.h>
#include <math.h>
using namespace std;
class Complex
{
public:
    Complex(){re=im=0;}							//不带参数的构造函数
    Complex(double r){re=r;im=0;}				//只置实部的构造函数
    Complex(double r,double i){re=r;im=i;}		//分别置实部和虚部的构造函数
    Complex(Complex& ob){re=ob.re;im=ob.im;};

    double real(){return re;}					//取复数实部
    double imag(){return im;}					//取复数虚部 

    void set(double r,double i){re=r;im=i;}		//VIP 给复数赋值
    void setReal(double r){re=r;}				//修改复数实部
    void setImag(double i){im=i;}				//修改复数虚部

    void operator=(Complex& ob);			//复数赋值 {re=ob.re;im=ob.im;}
    Complex& operator+(Complex& ob);			//函数重载：复数的四则运算
    Complex& operator-(Complex& ob);
    Complex& operator*(Complex& ob);
    Complex& operator/(Complex& ob);

	//-----高级功能--------
	double mod() {return sqrt(re*re+im*im);}		//求模
	double angle(){return atan(im/re);	}			//求角度
	Complex& conjugate();							//取共扼

    friend ostream& operator<<(ostream& os,Complex& c); //友元函数：重载流输入流输出
    friend istream& operator>>(istream& is,Complex& c);

private:
    double re,im;          //复数的实部和虚部
};






/*
template<class T>
    class complex {
public:
    typedef T value_type;
    T real() const;
    T imag() const;
    complex(const T& re = 0, const T& im = 0);
    complex(const complex& x);
    complex& operator=(const complex& rhs);
    complex& operator+=(const complex& rhs);
    complex& operator-=(const complex& rhs);
    complex& operator*=(const complex& rhs);
    complex& operator/=(const complex& rhs);
    complex& operator=(const T& rhs);
    complex& operator=(const T& rhs);
    complex& operator+=(const T& rhs);
    complex& operator-=(const T& rhs);
    complex& operator*=(const T& rhs);
    complex& operator/=(const T& rhs);
    friend complex<T>
        operator+(const complex<T>& lhs, const T& rhs);
    friend complex<T>
        operator+(const T& lhs, const complex<T>& rhs);
    friend complex<T>
        operator-(const complex<T>& lhs, const T& rhs);
    friend complex<T>
        operator-(const T& lhs, const complex<T>& rhs);
    friend complex<T>
        operator*(const complex<T>& lhs, const T& rhs);
    friend complex<T>
        operator*(const T& lhs, const complex<T>& rhs);
    friend complex<T>
        operator/(const complex<T>& lhs, const T& rhs);
    friend complex<T>
        operator/(const T& lhs, const complex<T>& rhs);
    friend bool operator==(const complex<T>& lhs, const T& rhs);
    friend bool operator==(const T& lhs, const complex<T>& rhs);
    friend bool operator!=(const complex<T>& lhs, const T& rhs);
    friend bool operator!=(const T& lhs, const complex<T>& rhs);
    };
*/




#endif MyComplex_H