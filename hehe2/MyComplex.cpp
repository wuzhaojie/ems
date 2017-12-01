//===============================================================================//
//
//								������ Complex
//									ʵ������
//ע��������Դ������иĽ�
//													���ƣ���������  ����ѧ
//																	2007.12.10		
//===============================================================================//
#include "MyComplex.h"

//===============================================================================//
void Complex::operator =(Complex& ob) //������ֵ
{
	re=ob.real();
	im=ob.imag();
}

//===============================================================================//
Complex& Complex::operator +(Complex& ob)
//���غ����������ӷ�����
{
    Complex *result=new Complex(re+ob.re,im+ob.im);
    return *result;
}

//===============================================================================//
Complex& Complex::operator -(Complex& ob)
//���غ�����������������
{
    Complex *result=new Complex(re-ob.re,im-ob.im);
    return *result;
}

//===============================================================================//
Complex& Complex::operator *(Complex& ob)
//���غ����������˷�����
{
    Complex *result=new Complex(re*ob.re-im*ob.im,im*ob.re+re*ob.im);
    return *result;
}

//===============================================================================//
Complex& Complex::operator /(Complex& ob)
//���غ�����������������
{
    double d=ob.re*ob.re+ob.im*ob.im;
    Complex *result=new Complex((re*ob.re+im*ob.im)/d,(im*ob.re-re*ob.im)/d);
    return *result;
}

//===============================================================================//
ostream& operator<<(ostream& os,Complex& ob)
//��Ԫ����������<<��������ob��������������os��
{
    if(ob.im!=0)
        return os<<ob.re<<((ob.im>=0.0)?"+":"-")<<fabs(ob.im)<<"i";
    else
        return os<<ob.re;
}

//===============================================================================//
istream& operator>>(istream& is,Complex& ob)
//��Ԫ����������>>��������������is�����븴��ob
{
    cout<<"Enter the real number:";
    cin>>ob.re;
    cout<<"Enter the  imaginary number:";
    cin>>ob.im;
    return is; 
}
//===============================================================================//
Complex& Complex::conjugate()							//ȡ����
{
	Complex *result=new Complex(re,-im);
    return *result;
}

//===============================================================================//


/*

void main()
{
	int choose;
	cout<<"  ���������������࣭���������� \n\n"<<endl;
 
    Complex cmplx1;     //��һ�����캯��
    cout<<"Z(1)="<<cmplx1<<endl;

    Complex cmplx2(2);    //�ڶ������캯��
    cout<<"Z(2)="<<cmplx2<<endl;

    Complex cmplx3(6.0,8.0);   //���������캯��
    cout<<"Z(3)="<<cmplx3<<endl;
	cout<<"Z(3)ģֵ:	"<<cmplx3.mod()<<endl;
	cout<<"Z(3)����:	"<<cmplx3.conjugate()<<endl;

	cmplx1.set(2.0,1);
    cout<<"Z(1)="<<cmplx1<<endl;

	//  cin>>cmplx1;     //ͨ�����������븴��
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