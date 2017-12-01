//===============================================================================//
//
//								������ Complex
//									ʵ������
//ע��������Դ������иĽ�
//													���ƣ���������  ����ѧ
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
    Complex(){re=im=0;}							//���������Ĺ��캯��
    Complex(double r){re=r;im=0;}				//ֻ��ʵ���Ĺ��캯��
    Complex(double r,double i){re=r;im=i;}		//�ֱ���ʵ�����鲿�Ĺ��캯��
    Complex(Complex& ob){re=ob.re;im=ob.im;};

    double real(){return re;}					//ȡ����ʵ��
    double imag(){return im;}					//ȡ�����鲿 

    void set(double r,double i){re=r;im=i;}		//VIP ��������ֵ
    void setReal(double r){re=r;}				//�޸ĸ���ʵ��
    void setImag(double i){im=i;}				//�޸ĸ����鲿

    void operator=(Complex& ob);			//������ֵ {re=ob.re;im=ob.im;}
    Complex& operator+(Complex& ob);			//�������أ���������������
    Complex& operator-(Complex& ob);
    Complex& operator*(Complex& ob);
    Complex& operator/(Complex& ob);

	//-----�߼�����--------
	double mod() {return sqrt(re*re+im*im);}		//��ģ
	double angle(){return atan(im/re);	}			//��Ƕ�
	Complex& conjugate();							//ȡ����

    friend ostream& operator<<(ostream& os,Complex& c); //��Ԫ���������������������
    friend istream& operator>>(istream& is,Complex& c);

private:
    double re,im;          //������ʵ�����鲿
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