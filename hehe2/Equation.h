//===============================================================================//
//
//								���� Equation�����
//								N��N������ʵ������
//
//													���ƣ���������  DXY
//																	2004.9.15		
//===============================================================================//

#ifndef MyEquation_H
#define MyEquation_H

class Equation  
{
public:
	int N;								//��N�����̣���ô�ұ�ʸ����N��1 ���ϵ��������N��N

	Equation(int n_);
	virtual ~Equation();

	double* FullMatrixLUDecompose(double* constant,double** coefficient);
	double* FullMatrixLDLDecompose(double* constant,double** coefficient);

	//					���ϡ�跽��	
	/*
	SpareStructure m_USpare;
	double* SpareLDLfilldata(int wide,int* Jjs,int* Jj,double* constant,double* Ja,double* JD);
	void SpareLDLDeconpose(int wide,int* Jjs,int* Jj);
	SpareStructure m_LSpare;
	int* Formitoj(int rowNumber,int columnNumber,int Spare_element_Number,int* jtoiJis, int* jtoiJi,int* jtoiJjs);
	int* Formjtoi(int wide,int* jtoiJjs, int* jtoiJj,int* jtoiJis);
	void SpareLUDecompose(int wide,int* Jlowjs, int* Jupjs,int* Jlowj,int* Jupj);
	double* SpareLUfilldata(int wide,double* constant,double* Jlowa,double* Jupa,double* JD,int* Jlowjs,int* Jupjs,int* Jlowj,int* Jupj);
	*/
};
#endif MyEquation_H

/*
main()
{
//=================================================================================//
	cout<<"				===���������===	                "<<endl;
	Equation Eq(2),Eq1(2);
	double* pEquationLeft;
	// nd=TotalVariableNumber+2*BusNumber;
	int nd=2;
	double *EquationRight=new double[nd+1];             //���Ƿֽ�ʱ���󷽳��е�ʽ�ұߵ����� 
	double *EquationLeft=new double[nd+1];              //���Ƿֽ�ʱ���󷽳��е�ʽ��ߵĴ��������ƫ���� 

	double **A=new double*[nd+1];                //���Ƿֽ�ʱ���󷽳��е�ʽ��ߵ�ϵ������
	for(int i=0;i<=nd;i++)
		A[i]=new double[nd+1];
	
	cout<<"				�Գ�ϵ�����󷽳����	                "<<endl;
	//�Գ�ϵ�����󷽳����
	//4*x1	+	x2	=3.0
	//x1	+	4*x2=4.5
	//x1=0.5	x2=1.0
	EquationRight[1]=3;		EquationRight[2]=4.5;
	A[1][1]=4;	A[1][2]=1;
	A[2][1]=1;	A[2][2]=4;

	pEquationLeft=Eq.FullMatrixLDLDecompose(EquationRight,A);
    for(i=1;i<=nd;i++)
	{
		EquationLeft[i]=*pEquationLeft;
		pEquationLeft++;
		cout<<"���̵�"<<i<<"����֮��	"<<EquationLeft[i]<<endl;
	}

	cout<<"				һ��ϵ�����󷽳����	                "<<endl;
	//һ��ϵ�����󷽳����
	//4*x1+x2=3
	//3*x1+2*x2=3.5
	//x1=0.5	x2=1.0
	EquationRight[1]=3;		EquationRight[2]=3.5;
	A[1][1]=4;	A[1][2]=1;
	A[2][1]=3;	A[2][2]=2;
	pEquationLeft=Eq1.FullMatrixLUDecompose(EquationRight,A);
    for(i=1;i<=nd;i++)
	{
		EquationLeft[i]=*pEquationLeft;
		pEquationLeft++;
		cout<<"���̵�"<<i<<"����֮��	"<<EquationLeft[i]<<endl;
	}
}
*/