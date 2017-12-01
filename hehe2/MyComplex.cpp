//===============================================================================//
//
//								复数类 Complex
//									实数类型
//注：对网上源程序进行改进
//													编制：西安交大  王建学
//																	2007.12.10		
//===============================================================================//
#include "MyComplex.h"

//===============================================================================//
void Complex::operator =(Complex& ob) //复数赋值
{
	re=ob.real();
	im=ob.imag();
}

//===============================================================================//
Complex& Complex::operator +(Complex& ob)
//重载函数：复数加法运算
{
    Complex *result=new Complex(re+ob.re,im+ob.im);
    return *result;
}

//===============================================================================//
Complex& Complex::operator -(Complex& ob)
//重载函数：复数减法运算
{
    Complex *result=new Complex(re-ob.re,im-ob.im);
    return *result;
}

//===============================================================================//
Complex& Complex::operator *(Complex& ob)
//重载函数：复数乘法运算
{
    Complex *result=new Complex(re*ob.re-im*ob.im,im*ob.re+re*ob.im);
    return *result;
}

//===============================================================================//
Complex& Complex::operator /(Complex& ob)
//重载函数：复数除法运算
{
    double d=ob.re*ob.re+ob.im*ob.im;
    Complex *result=new Complex((re*ob.re+im*ob.im)/d,(im*ob.re-re*ob.im)/d);
    return *result;
}

//===============================================================================//
ostream& operator<<(ostream& os,Complex& ob)
//友元函数：重载<<，将复数ob输出到输出流对象os中
{
    if(ob.im!=0)
        return os<<ob.re<<((ob.im>=0.0)?"+":"-")<<fabs(ob.im)<<"i";
    else
        return os<<ob.re;
}

//===============================================================================//
istream& operator>>(istream& is,Complex& ob)
//友元函数：重载>>，从输入流对象is中输入复数ob
{
    cout<<"Enter the real number:";
    cin>>ob.re;
    cout<<"Enter the  imaginary number:";
    cin>>ob.im;
    return is; 
}
//===============================================================================//
Complex& Complex::conjugate()							//取共扼
{
	Complex *result=new Complex(re,-im);
    return *result;
}

//===============================================================================//


/*

void main()
{
	int choose;
	cout<<"  －－－－－复数类－－－－－－ \n\n"<<endl;
 
    Complex cmplx1;     //第一个构造函数
    cout<<"Z(1)="<<cmplx1<<endl;

    Complex cmplx2(2);    //第二个构造函数
    cout<<"Z(2)="<<cmplx2<<endl;

    Complex cmplx3(6.0,8.0);   //第三个构造函数
    cout<<"Z(3)="<<cmplx3<<endl;
	cout<<"Z(3)模值:	"<<cmplx3.mod()<<endl;
	cout<<"Z(3)共扼:	"<<cmplx3.conjugate()<<endl;

	cmplx1.set(2.0,1);
    cout<<"Z(1)="<<cmplx1<<endl;

	//  cin>>cmplx1;     //通过流函数输入复数
    //	cout<<"Z(1)="<<cmplx1<<endl;

    cout<<"Z(1)+Z(3)=("<<cmplx1<<")+("<<cmplx3<<")="<<cmplx1+cmplx3<<endl;
    cout<<"Z(1)/Z(3)=("<<cmplx1<<")/("<<cmplx3<<")="<<cmplx1/cmplx3<<endl;

	cmplx2=cmplx2+cmplx3;
	//cmplx2=cmplx1*2;
    cout<<"Z(2)=Z(1)+Z(3)="<<cmplx2<<endl;
    cin>>choose;
	cout<<endl;
}
*/