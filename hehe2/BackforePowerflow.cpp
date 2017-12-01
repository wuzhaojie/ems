
#include <fstream>

#include <iomanip>
#include "BackforePowerflow.h"
#include "MyComplex.h"
#include "CMatrix.h"
#define pi 3.1415926;
BackforePowerflow::BackforePowerflow()
{
	branchloss=NULL;
	node=NULL;
	branch=NULL;
	tran=NULL;
	des=NULL;
	var=NULL;
	Ztran=NULL;
	Tmatrix=NULL;
	level=NULL;
	Dgnode=NULL;
	pvrecord=NULL;
	Xmatr=NULL;
	Power=NULL;
	vPower=NULL;
}
BackforePowerflow::~BackforePowerflow()
{
	/*delete[] branchloss;
	delete[] node;
	delete[] branch;
	delete[] tran;
	delete[] des;
	delete[] var;
	for(int i=0;i<=Phase;i++)
	{
		delete[] Ztran[i];
		delete[] Tmatrix[i];
	}
	delete[] Ztran;
	delete[] Tmatrix;
	for(int i=0;i<=Data.numBus;i++)
	{
		delete[] level[i];
		delete[] Dgnode[i];
	}
	delete[] level;
	delete[] Dgnode;
	delete[] pvrecord;
	for (int i=1;i<=pvnumtemp*Phase;i++)
	{
		delete[] Xmatr[i];
	}
	delete[] Xmatr;
	delete[] Power;
	delete[] vPower;*/
}
void BackforePowerflow::releaseflow()
{
	Data.releaseoriginal();
	if (branchloss!=NULL)
	{
		delete[] branchloss;
		branchloss=NULL;
	}
	if (node!=NULL)
	{
		delete[] node;
		node=NULL;
	}
	if (branch!=NULL)
	{
		delete[] branch;
		branch=NULL;
	}
	if (tran!=NULL)
	{
		delete[] tran;
		tran=NULL;
	}
	if (des!=NULL)
	{
		delete[] des;
		des=NULL;
	}
	if (var!=NULL)
	{
		delete[] var;
		var=NULL;
	}
	//delete[] branch;
	//delete[] tran;
	//delete[] des;
	//delete[] var;
	if (Ztran!=NULL)
	{
		for(int i=0;i<=Phase;i++)
		{
			delete[] Ztran[i];
			//delete[] Tmatrix[i];
		}
		delete[] Ztran;
		//delete[] Tmatrix;
		Ztran=NULL;
	}
	if (Tmatrix!=NULL)
	{
		for(int i=0;i<=Phase;i++)
		{
			//delete[] Ztran[i];
			delete[] Tmatrix[i];
		}
		//delete[] Ztran;
		delete[] Tmatrix;
		Tmatrix=NULL;
	}
	if (level!=NULL)
	{
		for(int i=0;i<=Data.numBus;i++)
		{
			delete[] level[i];
			//delete[] Dgnode[i];
		}
		delete[] level;
		//delete[] Dgnode;
		level=NULL;
	}
	if (Dgnode!=NULL)
	{
		for (int i=1;i<=Data.numDes;i++)
		{
			delete[] Dgnode[i];
		}
		delete[] Dgnode;
		Dgnode=NULL;
	}
	if (pvrecord!=NULL)
	{
		delete[] pvrecord;
		pvrecord=NULL;
	}
	if (Xmatr!=NULL)
	{
		for (int i=1;i<=pvnumtemp*Phase;i++)
		{
			delete[] Xmatr[i];
		}
		delete[] Xmatr;
		Xmatr=NULL;
	}
	if (Power!=NULL)
	{
		delete[] Power;
		Power=NULL;
	}
	if (vPower!=NULL)
	{
		delete[] vPower;
		vPower=NULL;
	}
}
void BackforePowerflow::Initilization(int gridislandflag)//初始化，读取文本文件中的节点，线路，负荷，变压器，分布式电源，无功补偿装置等信息，并存入专门的数据节构当中
{

	int i,j,k;
	int num;
//	int *S0;
	if(gridislandflag==0)
	{
		Data.InputfoundationData("flow_foudationgrid.txt");
	}
	else
	{
		Data.InputfoundationData("flow_foudationisland.txt");
	}
	
	Data.InputbranchData("flow_branch.txt");
	Data.InputdesData("flow_des.txt");
	Data.InputloadData("flow_load.txt");
	Data.InputPVData("flow_PV.txt");
	Data.InputvarData("flow_var.txt");
	Data.InputOriginalData();
	Phase=1;
	root=Data.balanceBus;
	Sbase=100;
	//netflag=0;//0island,1grid
	netflag=1-gridislandflag;

	/*PL=new double *[Data.numNode+1];
	for (i=0;i<=Data.numNode;i++)
	{
		PL[i]=new double [Tschedule+1];
	}
	PG=new double *[Data.numDes+1];
	for (i=0;i<=Data.numNode;i++)
	{
		PG[i]=new double [Tschedule+1];
	}*/
	branchloss=new double [Data.numBran+1];

	node=new Node[Data.numBus+1];
	for (i=1;i<=Data.numBus;i++)//编号
	{
		node[i].Initialize(Phase);
		node[i].num=i;
	}
	for (i=1;i<=Data.numDes;i++)//分布式电源ID32
	{
		num=Data.Desinf[i][2];//%分布式电源所在节点号
		node[num].ID32=Data.Desinf[i][8];
		//cout<<num<<" "<<node[num].ID32<<endl;

	}
	for (i=1;i<=Data.numNode;i++)//节点自带负荷ID32
	{
		num=Data.Nodeinf[i][1];
		node[num].ID32=Data.Nodeinf[i][5];
		//cout<<num<<" "<<node[num].ID32<<endl;
	}/**/

	for (i=1;i<=Data.numNode;i++)//节点自带负荷
	{
		num=Data.Nodeinf[i][1];
		for (j=1;j<=Phase;j++)
		{
			node[num].PQ[j].set(Data.Nodeinf[i][2]/Phase,Data.Nodeinf[i][3]/Phase);
		}
	}

	branch=new Branch[Data.numBran+1];
	for (i=1;i<=Data.numBran;i++)//%1、支路编号
	{
		branch[i].Initialize(Phase);
		branch[i].num=i;
	}

	for (i=1;i<=Data.numBran;i++)
	{
//		num=Data.Branchinf[i][1];
		if (Data.Branchinf[i][6]<0)
		{
			branch[i].type=2;
		}

//		branch[i].type=Data.Branchinf[i][7];
		branch[i].i=Data.Branchinf[i][2];
		branch[i].j=Data.Branchinf[i][3];
		for (j=1;j<=Phase;j++)
		{
			for (k=1;k<=Phase;k++)
			{
				if (k==j)
				{
					branch[i].Z[j][k].set(Data.Branchinf[i][4],Data.Branchinf[i][5]);//%2、标幺支路阻抗
					branch[i].B[j][k].set(0,Data.Branchinf[i][6]);
				}
			}
		}
	}


	tran=new Tran[Data.numTran+1];
	for (i=1;i<=Data.numTran;i++)
	{
		tran[i].Initialize(Phase);
		tran[i].num=i;
	}
	for (i=1;i<=Data.numTran;i++)
	{
//		num=Data.Transinf[i][1];
		tran[i].Ti=Data.Transinf[i][2];//%始节点
		tran[i].Tj=Data.Transinf[i][3];//%未节点
		tran[i].K=-1*Data.Transinf[i][6];//%变压器变比
//		tran[i].angle=Data.Transinf[i][7];//%变压器相角
//		tran[i].zeroi=Data.Transinf[i][8];//零序分量常数
//		tran[i].zeroj=Data.Transinf[i][9];//零序分量常数
		tran[i].brannum=Data.Transinf[i][7];//变压器的支路编号
		for (j=1;j<=Phase;j++)
		{
			for (k=1;k<=Phase;k++)
			{
				if (k==j)
				{
					tran[i].Z[j][k].set(Data.Transinf[i][4],Data.Transinf[i][5]);//%归算到j侧的阻抗
				}			
			}
		}
	}

	des=new Des[Data.numDes+1];
	for (i=1;i<=Data.numDes;i++)
	{
		des[i].Initialize(Phase);
		des[i].num=i;
	}
	for (i=1;i<=Data.numDes;i++)
	{
		num=Data.Desinf[i][1];//%分布式电源编号
		des[num].nodenum=Data.Desinf[i][2];//%分布式电源所在节点号
//		des[num].type=Data.Desinf[i][3];//%Dg的类型
		for (j=1;j<=Phase;j++)
		{
			des[num].V[j]=Data.Desinf[i][5];//%Dg的电压
			des[num].P[j]=Data.Desinf[i][3]/Phase;//Dg的无功
			des[num].Q[j]=Data.Desinf[i][4]/Phase;//Dg的有功
			des[num].Qmin[j]=Data.Desinf[i][6]/Phase;//Dg的Ｑmin
			des[num].Qmax[j]=Data.Desinf[i][7]/Phase;//Dg的Ｑmax
		}
	}

	for (i=1;i<=Data.numPv;i++)//Dg的类型
	{
		num=Data.Pvinf[i];
		des[num].type=2;
	}

	var=new Var[Data.numVar+1];
	for (i=1;i<=Data.numVar;i++)//无功补偿器编号
	{
		var[i].Initialize(Phase);
		var[i].num=i;
	}
	for (i=1;i<=Data.numVar;i++)
	{
//		num=Data.Varinf[i][1];
		var[i].nodenum=Data.Varinf[i][1];//无功补偿器编号
		for (j=1;j<=Phase;j++)
		{
			var[i].Q[j].set(0,-Data.Varinf[i][2]/Phase);//%无功补偿，注意流出节点为正方向
		}
	}

	Ztran=(Complex **)new Complex[Phase+1];//初始化变压器的阻抗转换矩阵
	for(i=0;i<=Phase;i++)
		Ztran[i]=new Complex[Phase+1];

	Tmatrix=(Complex **)new Complex[Phase+1];//初始化转换矩阵
	for(i=0;i<=Phase;i++)
		Tmatrix[i]=new Complex[Phase+1];


	for (i=1;i<=Data.numTran;i++)
	{
		//cout<<tran[i].Ti<<endl;
		//cout<<tran[i].Tj<<endl;
		//cout<<tran[i].K<<endl;
		//cout<<tran[i].angle<<endl;
		//cout<<tran[i].zeroi<<endl;
		//cout<<tran[i].zeroj<<endl;
		//cout<<tran[i].brannum<<endl;
		for (j=1;j<=Phase;j++)
		{
			for (k=1;k<=Phase;k++)
			{
				if (k==j)
				{
					//cout<<tran[i].Z[j][k]<<endl;
				}			
			}
		}
	}

}

int BackforePowerflow::check(int k,int *Matr,int N)//检查是否存在于数组Matr里
{
	int flag;
	flag=0;
	int i;
	for (i=1;i<=N;i++)
	{
		if (Matr[i]==k)
		{
			flag=1;
			break;
		}
	}
    return flag;
}

int BackforePowerflow::findbranch(int a,int b)//%查找分支编号
{
	int bran;
	bran=0;
	int i;
	for (i=1;i<=Data.numBran;i++)
	{
//		if ((Data.Branchinf[i][2]==a && Data.Branchinf[i][3]==b) ||(Data.Branchinf[i][2]==b && Data.Branchinf[i][3]==a) )
		if ((branch[i].i==a && branch[i].j==b) ||(branch[i].i==b && branch[i].j==a)) 
		{
			bran=branch[i].num;
			break;
		}
	}
	return bran;
}


void BackforePowerflow::Levelset()//%安排节点分层
{
	int i,j,k;
	int num;
	int *S0;
	int temproot;

	S0=new int[Data.numBus+2];//%保存已被安排层数的节点，最后一个值为节点个数
	for (i=1;i<=Data.numBus+1;i++)
	{
		S0[i]=0;
	}

	level=(int **)new int[Data.numBus+1];
	for(i=0;i<=Data.numBus;i++)
		level[i]=new int[Data.numBus+2];
	for (i=1;i<=Data.numBus;i++)
	{
		for (j=1;j<=Data.numBus+1;j++)
		{
			level[i][j]=0;
		}
	}

	S0[Data.numBus+1]=S0[Data.numBus+1]+1;
	num=S0[Data.numBus+1];
	S0[num]=root;
	nlevel=1;
	level[nlevel][Data.numBus+1]=level[nlevel][Data.numBus+1]+1;
	level[nlevel][1]=root;//%初始化根节点

	node[root].lev=nlevel;
	for (j=1;j<=Data.numBus;j++)
	{
		if (Data.RelateMatricinf[root][j]!=0 && check(j,S0,S0[Data.numBus+1])==0)
		{
				level[nlevel+1][Data.numBus+1]=level[nlevel+1][Data.numBus+1]+1;
				num=level[nlevel+1][Data.numBus+1];
				level[nlevel+1][num]=j;
	
				S0[Data.numBus+1]=S0[Data.numBus+1]+1;
				num=S0[Data.numBus+1];
				S0[num]=j;
				
				node[j].pare=root;
				node[j].bran=findbranch(j,root);
				node[j].lev=nlevel+1;
		}
	}

	while (level[nlevel+1][Data.numBus+1]!=0)//%如果下层还有节点，则继续向下搜索
	{
		nlevel=nlevel+1;// %更新层数
		for (i=1;i<=level[nlevel][Data.numBus+1];i++)
		{
			temproot=level[nlevel][i];
			for (j=1;j<=Data.numBus;j++)
			{
				if (Data.RelateMatricinf[temproot][j]!=0 && check(j,S0,S0[Data.numBus+1])==0)//如果两节点相联，且不在已搜索过的节点中
				{
					level[nlevel+1][Data.numBus+1]=level[nlevel+1][Data.numBus+1]+1;//该层节点数加１
					num=level[nlevel+1][Data.numBus+1];
					level[nlevel+1][num]=j;//%在该层保存该节点

					S0[Data.numBus+1]=S0[Data.numBus+1]+1;//%该节点成为已搜索过的节点加入集合SO当中
					num=S0[Data.numBus+1];
					S0[num]=j;

					node[j].pare=temproot;
					node[j].bran=findbranch(j,temproot);
					node[j].lev=nlevel+1;
				}
			}
		}
	}


	for (i=1;i<=Data.numBus;i++)
	{
		//cout<<i<<'\t'<<node[i].pare<<endl;
	}
	delete[] S0;


}

double BackforePowerflow::mini(double a, double b)//求两个数的较小值
{
	double val;
	val=a;
	if (a>b)
	{
		val=b;
	}
	return val;
}

double BackforePowerflow::maxi(double a, double b)//求两个数的较大值
{
	double val;
	val=a;
	if (a<b)
	{
		val=b;
	}
	return val;
}

int BackforePowerflow::findTrans(int bran)//判断支路是否为变压器支路
{
	int trannum;
	int i;
	trannum=0;
	for (i=1;i<=Data.numTran;i++)
	{
		if (tran[i].brannum==bran)
		{
			trannum=tran[i].num;
			break;
		}
	}
	return trannum;
	
}

void BackforePowerflow::Ztranmatrix(int r1,int r2,double angle,double Tk,Complex **Z,int HLtype)//%计算出变压器高低压侧的电压电流转换矩阵，r1和r2分别为高低压侧的零序电流的流通指示，为1是为可流通
{
	/*
	%变压器变换矩阵测试
    %angle=pi/6;%Y0/delta
    %k=1;%变比
    %TVtype为电流或电压转换指示，1为电流，2为电压
    %HLtype为向高压侧或低压侧转换指示，1为高压侧，2为低压侧
    */
	int i,j,k;
	double alpha;
	double pai;
	Complex **A;
	Complex **B;
	Complex **C;
	Complex **D;
	Complex **tempM1;
//	Complex **tempM2;
	Complex temp1;
	Complex temp2;
	Complex temp3;


	A=(Complex **)new Complex[Phase+1];
	for(i=0;i<=Phase;i++)
		A[i]=new Complex[Phase+1];

	B=(Complex **)new Complex[Phase+1];
	for(i=0;i<=Phase;i++)
		B[i]=new Complex[Phase+1];

	C=(Complex **)new Complex[Phase+1];
	for(i=0;i<=Phase;i++)
		C[i]=new Complex[Phase+1];

	D=(Complex **)new Complex[Phase+1];
	for(i=0;i<=Phase;i++)
		D[i]=new Complex[Phase+1];

	tempM1=(Complex **)new Complex[Phase+1];
	for(i=0;i<=Phase;i++)
		tempM1[i]=new Complex[Phase+1];

/*	tempM2=(Complex **)new Complex[Phase+1];
	for(i=0;i<=Phase;i++)
		tempM2[i]=new Complex[Phase+1];
		*/

	pai=pi;
	alpha=pai/3*2;
	if (Phase==3)
	{
		temp1.set(1/(3*Tk)*cos(-angle),1/(3*Tk)*sin(-angle));
		temp2.set(1/(3*Tk)*cos(angle),1/(3*Tk)*sin(angle));
		temp3.set(1/(3*Tk)*r1,0);
		A[1][1]=temp1+temp2+temp3;
		A[2][2]=A[1][1];
		A[3][3]=A[1][1];

		temp1.set(1/(3*Tk)*cos(-angle+alpha),1/(3*Tk)*sin(-angle+alpha));
		temp2.set(1/(3*Tk)*cos(angle+2*alpha),1/(3*Tk)*sin(angle+2*alpha));
		temp3.set(1/(3*Tk)*r1,0);
		A[1][2]=temp1+temp2+temp3;
		A[2][3]=A[1][2];
		A[3][1]=A[1][2];

		temp1.set(1/(3*Tk)*cos(-angle+2*alpha),1/(3*Tk)*sin(-angle+2*alpha));
		temp2.set(1/(3*Tk)*cos(angle+alpha),1/(3*Tk)*sin(angle+alpha));
		temp3.set(1/(3*Tk)*r1,0);
		A[1][3]=temp1+temp2+temp3;
		A[2][1]=A[1][3];
		A[3][2]=A[1][3];


		temp1.set(1/(3*Tk)*cos(-angle),1/(3*Tk)*sin(-angle));
		temp2.set(1/(3*Tk)*cos(angle),1/(3*Tk)*sin(angle));
		temp3.set(1/(3*Tk)*r2,0);
		B[1][1]=temp1+temp2+temp3;
		B[2][2]=B[1][1];
		B[3][3]=B[1][1];

		temp1.set(1/(3*Tk)*cos(-angle+2*alpha),1/(3*Tk)*sin(-angle+2*alpha));
		temp2.set(1/(3*Tk)*cos(angle+alpha),1/(3*Tk)*sin(angle+alpha));
		temp3.set(1/(3*Tk)*r2,0);
		B[1][2]=temp1+temp2+temp3;
		B[2][3]=B[1][2];
		B[3][1]=B[1][2];
		
		temp1.set(1/(3*Tk)*cos(-angle+alpha),1/(3*Tk)*sin(-angle+alpha));
		temp2.set(1/(3*Tk)*cos(angle+2*alpha),1/(3*Tk)*sin(angle+2*alpha));
		temp3.set(1/(3*Tk)*r2,0);
		B[1][3]=temp1+temp2+temp3;
		B[2][1]=B[1][3];
		B[3][2]=B[1][3];

		temp1.set(Tk/3*cos(-angle),Tk/3*sin(-angle));
		temp2.set(Tk/3*cos(angle),Tk/3*sin(angle));
		temp3.set(Tk/3*r1,0);
		C[1][1]=temp1+temp2+temp3;
		C[2][2]=C[1][1];
		C[3][3]=C[1][1];

		temp1.set(Tk/3*cos(-angle+alpha),Tk/3*sin(-angle+alpha));
		temp2.set(Tk/3*cos(angle+2*alpha),Tk/3*sin(angle+2*alpha));
		temp3.set(Tk/3*r1,0);
		C[1][2]=temp1+temp2+temp3;
		C[2][3]=C[1][2];
		C[3][1]=C[1][2];

		temp1.set(Tk/3*cos(-angle+2*alpha),Tk/3*sin(-angle+2*alpha));
		temp2.set(Tk/3*cos(angle+alpha),Tk/3*sin(angle+alpha));
		temp3.set(Tk/3*r1,0);
		C[1][3]=temp1+temp2+temp3;
		C[2][1]=C[1][3];
		C[3][2]=C[1][3];

		temp1.set(Tk/3*cos(-angle),Tk/3*sin(-angle));
		temp2.set(Tk/3*cos(angle),Tk/3*sin(angle));
		temp3.set(Tk/3*r2,0);
		D[1][1]=temp1+temp2+temp3;
		D[2][2]=D[1][1];
		D[3][3]=D[1][1];

		temp1.set(Tk/3*cos(-angle+2*alpha),Tk/3*sin(-angle+2*alpha));
		temp2.set(Tk/3*cos(angle+alpha),Tk/3*sin(angle+alpha));
		temp3.set(Tk/3*r2,0);
		D[1][2]=temp1+temp2+temp3;
		D[2][3]=D[1][2];
		D[3][1]=D[1][2];

		temp1.set(Tk/3*cos(-angle+alpha),Tk/3*sin(-angle+alpha));
		temp2.set(Tk/3*cos(angle+2*alpha),Tk/3*sin(angle+2*alpha));
		temp3.set(Tk/3*r2,0);
		D[1][3]=temp1+temp2+temp3;
		D[2][1]=D[1][3];
		D[3][2]=D[1][3];
	}
	else
	{
		temp1.set(1/Tk*cos(-angle),1/Tk*sin(-angle));
		A[1][1]=temp1;
		temp1.set(1/Tk*cos(angle),1/Tk*sin(angle));
		B[1][1]=temp1;
		temp1.set(Tk*cos(-angle),Tk*sin(-angle));
		C[1][1]=temp1;
		temp1.set(Tk*cos(angle),Tk*sin(angle));
		D[1][1]=temp1;
	}



	for (i=1;i<=Phase;i++)
	{
		for (j=1;j<=Phase;j++)
		{
			Ztran[i][j].set(0,0);
			tempM1[i][j].set(0,0);
		}
	}

	if (HLtype==1)
	{
		for (i=1;i<=Phase;i++)
		{
			for (j=1;j<=Phase;j++)
			{
				for (k=1;k<=Phase;k++)
				{
					tempM1[i][j]=tempM1[i][j]+C[i][k]*Z[k][j];
				}
			}
		}

		for (i=1;i<=Phase;i++)
		{
			for (j=1;j<=Phase;j++)
			{
				for (k=1;k<=Phase;k++)
				{
					Ztran[i][j]=Ztran[i][j]+tempM1[i][k]*D[k][j];
				}
			}
		}		
	} 
	else
	{
		for (i=1;i<=Phase;i++)
		{
			for (j=1;j<=Phase;j++)
			{
				for (k=1;k<=Phase;k++)
				{
					tempM1[i][j]=tempM1[i][j]+B[i][k]*Z[k][j];
				}
			}
		}

		for (i=1;i<=Phase;i++)
		{
			for (j=1;j<=Phase;j++)
			{
				for (k=1;k<=Phase;k++)
				{
					Ztran[i][j]=Ztran[i][j]+tempM1[i][k]*A[k][j];
				}
			}
		}	
	}
	for(int i=0;i<=Phase;i++)
	{
		delete[] A[i];
		delete[] B[i];
		delete[] C[i];
		delete[] D[i];
		delete[] tempM1[i];
	}
	delete[] A;
	delete[] B;
	delete[] C;
	delete[] D;
	delete[] tempM1;


/*	for (i=1;i<=Phase;i++)
	{
		for (j=1;j<=Phase;j++)
		{
			cout<<Ztran[i][j]<<'\t';
		}
		cout<<endl;
	}
*/

}

int BackforePowerflow::findDgnode(int *S0,int a)//%查找编号为a的节点是否在SO当中
{
	int colume;
	int num;
	int val;
	num=S0[Data.numDes+1];
	val=0;
	for (int i=1;i<=num;i++)
	{
		if (a==S0[i])
		{
			val=1;
			break;
		}
	}
	return val;
	
}



void BackforePowerflow::Dgnodeset()//%统计出带有分布式电源的节点上Dg的个数其类型
{
	int *S0;
	int i,j;
	int nodenum;
	int num;
	S0=new int[Data.numDes+2];
	for (i=1;i<=Data.numDes+1;i++)
	{
		S0[i]=0;
	}
	Dgnode=(int **)new int[Data.numDes+1];
	for (i=1;i<=Data.numDes;i++)
	{
		Dgnode[i]=new int[Data.numDes+3];
	}
	for (i=1;i<=Data.numDes;i++)
	{
		for (j=1;j<=Data.numDes+2;j++)
		{
			Dgnode[i][j]=0;
		}
	}

	for (i=1;i<=Data.numDes;i++)
	{
//		nodenum=Data.Desinf[i][2];
		nodenum=des[i].nodenum;
		if (findDgnode(S0,nodenum)==0)
		{
			S0[Data.numDes+1]=S0[Data.numDes+1]+1;
			num=S0[Data.numDes+1];
			S0[num]=nodenum;
		}
	}

	nDgnode=S0[Data.numDes+1];
	for (i=1;i<=nDgnode;i++)
	{
		Dgnode[i][Data.numDes+1]=S0[i];
		for (j=1;j<=Data.numDes;j++)
		{
//			if (Data.Desinf[j][2]==S0[i])
			if (des[j].nodenum==S0[i])
			{
				Dgnode[i][Data.numDes+2]=Dgnode[i][Data.numDes+2]+1;
				num=Dgnode[i][Data.numDes+2];
//				Dgnode[i][num]=Data.Desinf[j][1];
				Dgnode[i][num]=des[j].num;
			}
		}
	}

	for (i=1;i<=Data.numDes;i++)
	{
		for (j=1;j<=Data.numDes+2;j++)
		{
			//cout<<Dgnode[i][j]<<'\t';
		}
		//cout<<endl;
	}
	delete[] S0;
}

void BackforePowerflow::formalX()//%形成pv节点之间的电抗矩阵
{
	int **pvnodes;
	int i,j,k;
	int m,n;
	int pvnum;
	int numdg;
	int num;
	int nodenum;
	int levelnum;
	int nk;
	int tempnum1,tempnum2,tempnum3;
	int trannum;
	int **nodeX;
	Complex **Zplus;
	numdg=Data.numDes;
	pvrecord=new int[Data.numDes+2];//%保存pv节点，最后一个存放其数量
	pvnodes=(int **)new int[Data.numDes+1];//%保存每个pv节点到根节点的节点，最后一个存放节点数
	for (i=1;i<=Data.numDes;i++)
	{
		pvnodes[i]=new int[nlevel+2];
	}
	pvnum=0;

	for (i=1;i<=numdg;i++)
	{
//		if (Data.Desinf[i][3]==2 && Data.Desinf[i][2]!=root)
		if (des[i].type==2 && des[i].nodenum!=root)
		{
			pvnum=pvnum+1;//%统计pv电源个数
			pvrecord[pvnum]=des[i].num;//%将电源编号顺次存起来
		}
	}
	pvrecord[numdg+1]=pvnum;

	nodeX=(int **)new int[pvnum+1];//%保存矩阵X中的相关节点
	for (i=1;i<=pvnum;i++)
	{
		nodeX[i]=new int[pvnum+1];
	}

	Xmatr=(double **)new double[pvnum*Phase+1];
	for (i=1;i<=pvnum*Phase;i++)
	{
		Xmatr[i]=new double[pvnum*Phase+1];
	}
	pvnumtemp=pvnum;
	for (i=1;i<=pvnum*Phase;i++)
	{
		for (j=1;j<=pvnum*Phase;j++)
		{
			Xmatr[i][j]=0;
		}
	}

	for (i=1;i<=pvnum;i++)
	{
		num=pvrecord[i];
		nodenum=des[num].nodenum;
		levelnum=node[nodenum].lev;

		pvnodes[i][nlevel+1]=levelnum;//%第i个pv节点最后一个数保存包括其在内的母节点数
		for (j=levelnum;j>=1;j--)//%依次推下去
		{
			pvnodes[i][j]=nodenum;
			nodenum=node[nodenum].pare;
		}
	}

	for (i=1;i<=pvnum;i++)
	{
		for (j=1;j<=pvnum;j++)
		{
			num=mini(pvnodes[i][nlevel+1],pvnodes[j][nlevel+1]);
			for (k=1;k<=num;k++)
			{
				if (pvnodes[i][k]==pvnodes[j][k])//%若两pv节点支路从开头起数第k个数相同，则保存该点号到nodeX(i,j)
				{
					nodeX[i][j]=pvnodes[i][k];				
				}
				else//%若不相同，则跳出k循环
				{
					break;
				}
			}
		}
	}

	for (i=1;i<=pvnum;i++)//%nodeX矩阵为对称阵，将其下三角部分填满
	{
		for (j=1;j<=i-1;j++)
		{
			nodeX[i][j]=nodeX[j][i];
		}
	}

	Zplus=(Complex **)new Complex[Phase+1];
	for(i=0;i<=Phase;i++)
		Zplus[i]=new Complex[Phase+1];



	for (i=1;i<=pvnum;i++)
	{
		for (j=1;j<=pvnum;j++)
		{
			num=nodeX[i][j];
			nk=0;

			for(m=1;m<=Phase;m++)
				for(n=1;n<=Phase;n++)
					Zplus[m][n].set(0,0);

			for (k=1;k<=pvnodes[i][nlevel+1];k++)//%nk用来记载节点num为第多少位
			{
				if (pvnodes[i][k]==num)
				{
					nk=nk+1;
					break;
				} 
				else
				{
					nk=nk+1;
				}
			}


			for (k=1;k<=pvnodes[i][nlevel+1];k++)
			{
				tempnum1=pvnodes[i][k];
				if (tempnum1!=root)
				{
					tempnum2=node[tempnum1].pare;
					tempnum3=node[tempnum1].bran;

					if (branch[tempnum3].type==2)//%若为变压器线路
					{
						trannum=findTrans(branch[tempnum3].num);//%找到树枝对应的变压器编号
							if (tempnum2==tran[trannum].Ti && tempnum1==tran[trannum].Tj)//%如果母节点为高压侧，子节点为低压侧
							{
								Ztranmatrix(tran[trannum].zeroi,tran[trannum].zeroj,tran[trannum].angle,tran[trannum].K,Zplus,2);//%从高压侧到低压侧的阻抗转换矩阵
								for (m=1;m<=Phase;m++)
								{
									for (n=1;n<=Phase;n++)
									{
										Zplus[m][n]=Ztran[m][n];
									}
								}

								if (k<=nk)
								{
									for (m=1;m<=Phase;m++)
									{
										for (n=1;n<=Phase;n++)
										{
											Zplus[m][n]=Zplus[m][n]+tran[trannum].Z[m][n];
										}
									}
								}
							} 
							else if(tempnum2=tran[trannum].Tj &&tempnum1==tran[trannum].Ti)//%如果母节点为低压侧，子节点为高压侧
							{
								if (k<=nk)
								{
									for (m=1;m<=Phase;m++)
									{
										for (n=1;n<=Phase;n++)
										{
											Zplus[m][n]=Zplus[m][n]+tran[trannum].Z[m][n];
										}
									}
								}

								Ztranmatrix(tran[trannum].zeroi,tran[trannum].zeroj,tran[trannum].angle,tran[trannum].K,Zplus,1);//%从低压侧到高压侧的阻抗转换矩阵
								for (m=1;m<=Phase;m++)
								{
									for (n=1;n<=Phase;n++)
									{
										Zplus[m][n]=Ztran[m][n];
									}
								}
							}
					}
					else//%若为普通线路
					{
						if (k<=nk)
						{
							for (m=1;m<=Phase;m++)
							{
								for (n=1;n<=Phase;n++)
								{
									Zplus[m][n]=Zplus[m][n]+branch[tempnum3].Z[m][n];//%将Zplus存入到Ｘ矩阵中
								}
							}
						}
					}
				}
			}

			for (m=1;m<=Phase;m++)
			{
				for (n=1;n<=Phase;n++)
				{
					Xmatr[Phase*(i-1)+m][Phase*(j-1)+n]=Zplus[m][n].imag();
					//cout<<Xmatr[Phase*(i-1)+m][Phase*(j-1)+n]<<'\t';
				}			
				//cout<<endl;
			}
		}
	}
	for (int i=1;i<=Data.numDes;i++)
	{
		delete[] pvnodes[i];
	}
	delete[] pvnodes;
	for (int i=1;i<=pvnum;i++)
	{
		delete[] nodeX[i];
	}
	delete[] nodeX;
	for(int i=0;i<=Phase;i++)
	{
		delete[] Zplus[i];
	}
	delete[] Zplus;
		

}

void BackforePowerflow::dgset(double **Vdginf)//%给分布式电源出力赋值
{
	int i,j;
	int num;
	for (i=1;i<=Data.numDes;i++)
	{
		num=Vdginf[i][1];//%分布式电源编号
		if (des[num].type==2)//%若为PV节点
		{
			for (j=1;j<=Phase;j++)
			{
				des[num].P[j]=Vdginf[i][2]/Phase;//%分布式电源的有功
				des[num].Qmax[j]=tan(acos(0.5))*des[num].P[j];
				des[num].Q[j]=0.5*(des[num].Qmax[j]+des[num].Qmin[j]);
			}
			
		}
		else if (des[num].type==1)//%若为PQ节点
		{
			for (j=1;j<=Phase;j++)
			{
				des[num].P[j]=Vdginf[i][2]/Phase;//%分布式电源的有功
//				des[num].Q[j]=tan(acos(1.0))*des[num].P[j];//%分布式电源的无功
				des[num].Q[j]=Vdginf[i][3]/Phase;//%分布式电源的无功
			}
		}
	}
}


void BackforePowerflow::pvaddQ()//计算pv结点应补充的功率
{
	int i,j;
	int pvnum;
	int tempnum;
	int tempnum1;
	int tempnum2;
	pvnum=pvrecord[Data.numDes+1];

	double *Vset;
	Complex *Vk;
	Vset=new double[pvnum*Phase+1];//%Vset为pv节点的电压设定值
	Vk=new Complex[pvnum*Phase+1];//%Vk为其对应节点的电压值

	for (i=1;i<=pvnum*Phase;i++)
	{
		Vset[i]=0;
		Vk[i].set(0,0);
	}

	for (i=1;i<=pvnum;i++)
	{
		tempnum1=pvrecord[i];//%pv分布式电源编号
		for (j=1;j<=Phase;j++)
		{
			Vset[Phase*(i-1)+j]=des[tempnum1].V[j];
		}

		tempnum2=des[tempnum1].nodenum;//%pv节点编号
		for (j=1;j<=Phase;j++)
		{
			Vk[Phase*(i-1)+j]=node[tempnum2].U[j];
		}
		
	}

	CMatrix deltQ;
	CMatrix X;
	CMatrix Vgap;
	deltQ.Initialize(pvnum*Phase,1);
	X.Initialize(pvnum*Phase,pvnum*Phase);
	Vgap.Initialize(pvnum*Phase,1);

	for (i=1;i<=pvnum*Phase;i++)
	{
		for (j=1;j<=pvnum*Phase;j++)
		{
			X.PMatrix[i][j]=Xmatr[i][j];
		}
	}

	for (i=1;i<=pvnum*Phase;i++)
	{
		Vgap.PMatrix[i][1]=Vset[i]*(Vset[i]-Vk[i].mod());
	}

	Vgap.Print();
	deltQ=X.Invert()*Vgap;//%求出pv节点所应补的无功
	deltQ.Print();

	for (i=1;i<=pvnum;i++)
	{
		tempnum=pvrecord[i];
		for (j=1;j<=Phase;j++)
		{
			des[tempnum].Q[j]=des[tempnum].Q[j]+deltQ.PMatrix[Phase*(i-1)+j][1];//%求出pv节点最终发出的无功
		}

		for (j=1;j<=Phase;j++)//%限制其无功在最大和最小范围内
		{
			if (des[tempnum].Q[j]>des[tempnum].Qmax[j])
			{
				des[tempnum].Q[j]=des[tempnum].Qmax[j];
			} 
			else if(des[tempnum].Q[j]<des[tempnum].Qmin[j])
			{
				des[tempnum].Q[j]=des[tempnum].Qmin[j];
			}
		}
	}
	delete[] Vset;
	delete[] Vk;


}


void BackforePowerflow::Tranmatrix(int r1,int r2,double angle,double Tk,int IVtype,int HLtype)//%计算出变压器高低压侧的电压电流转换矩阵，r1和r2分别为高低压侧的零序电流的流通指示，为1是为可流通
{
	int i,j,k;
	double alpha;
	double pai;
	Complex **A;
	Complex **B;
	Complex **C;
	Complex **D;
//	Complex **tempM1;
//	Complex **tempM2;
	Complex temp1;
	Complex temp2;
	Complex temp3;


	A=(Complex **)new Complex[Phase+1];
	for(i=0;i<=Phase;i++)
		A[i]=new Complex[Phase+1];

	B=(Complex **)new Complex[Phase+1];
	for(i=0;i<=Phase;i++)
		B[i]=new Complex[Phase+1];

	C=(Complex **)new Complex[Phase+1];
	for(i=0;i<=Phase;i++)
		C[i]=new Complex[Phase+1];

	D=(Complex **)new Complex[Phase+1];
	for(i=0;i<=Phase;i++)
		D[i]=new Complex[Phase+1];



/*	tempM2=(Complex **)new Complex[Phase+1];
	for(i=0;i<=Phase;i++)
		tempM2[i]=new Complex[Phase+1];
		*/

	pai=pi;
	alpha=pai/3*2;
	if (Phase==3)
	{
		temp1.set(1/(3*Tk)*cos(-angle),1/(3*Tk)*sin(-angle));
		temp2.set(1/(3*Tk)*cos(angle),1/(3*Tk)*sin(angle));
		temp3.set(1/(3*Tk)*r1,0);
		A[1][1]=temp1+temp2+temp3;
		A[2][2]=A[1][1];
		A[3][3]=A[1][1];

		temp1.set(1/(3*Tk)*cos(-angle+alpha),1/(3*Tk)*sin(-angle+alpha));
		temp2.set(1/(3*Tk)*cos(angle+2*alpha),1/(3*Tk)*sin(angle+2*alpha));
		temp3.set(1/(3*Tk)*r1,0);
		A[1][2]=temp1+temp2+temp3;
		A[2][3]=A[1][2];
		A[3][1]=A[1][2];

		temp1.set(1/(3*Tk)*cos(-angle+2*alpha),1/(3*Tk)*sin(-angle+2*alpha));
		temp2.set(1/(3*Tk)*cos(angle+alpha),1/(3*Tk)*sin(angle+alpha));
		temp3.set(1/(3*Tk)*r1,0);
		A[1][3]=temp1+temp2+temp3;
		A[2][1]=A[1][3];
		A[3][2]=A[1][3];


		temp1.set(1/(3*Tk)*cos(-angle),1/(3*Tk)*sin(-angle));
		temp2.set(1/(3*Tk)*cos(angle),1/(3*Tk)*sin(angle));
		temp3.set(1/(3*Tk)*r2,0);
		B[1][1]=temp1+temp2+temp3;
		B[2][2]=B[1][1];
		B[3][3]=B[1][1];

		temp1.set(1/(3*Tk)*cos(-angle+2*alpha),1/(3*Tk)*sin(-angle+2*alpha));
		temp2.set(1/(3*Tk)*cos(angle+alpha),1/(3*Tk)*sin(angle+alpha));
		temp3.set(1/(3*Tk)*r2,0);
		B[1][2]=temp1+temp2+temp3;
		B[2][3]=B[1][2];
		B[3][1]=B[1][2];
		
		temp1.set(1/(3*Tk)*cos(-angle+alpha),1/(3*Tk)*sin(-angle+alpha));
		temp2.set(1/(3*Tk)*cos(angle+2*alpha),1/(3*Tk)*sin(angle+2*alpha));
		temp3.set(1/(3*Tk)*r2,0);
		B[1][3]=temp1+temp2+temp3;
		B[2][1]=B[1][3];
		B[3][2]=B[1][3];

		temp1.set(Tk/3*cos(-angle),Tk/3*sin(-angle));
		temp2.set(Tk/3*cos(angle),Tk/3*sin(angle));
		temp3.set(Tk/3*r1,0);
		C[1][1]=temp1+temp2+temp3;
		C[2][2]=C[1][1];
		C[3][3]=C[1][1];

		temp1.set(Tk/3*cos(-angle+alpha),Tk/3*sin(-angle+alpha));
		temp2.set(Tk/3*cos(angle+2*alpha),Tk/3*sin(angle+2*alpha));
		temp3.set(Tk/3*r1,0);
		C[1][2]=temp1+temp2+temp3;
		C[2][3]=C[1][2];
		C[3][1]=C[1][2];

		temp1.set(Tk/3*cos(-angle+2*alpha),Tk/3*sin(-angle+2*alpha));
		temp2.set(Tk/3*cos(angle+alpha),Tk/3*sin(angle+alpha));
		temp3.set(Tk/3*r1,0);
		C[1][3]=temp1+temp2+temp3;
		C[2][1]=C[1][3];
		C[3][2]=C[1][3];

		temp1.set(Tk/3*cos(-angle),Tk/3*sin(-angle));
		temp2.set(Tk/3*cos(angle),Tk/3*sin(angle));
		temp3.set(Tk/3*r2,0);
		D[1][1]=temp1+temp2+temp3;
		D[2][2]=D[1][1];
		D[3][3]=D[1][1];

		temp1.set(Tk/3*cos(-angle+2*alpha),Tk/3*sin(-angle+2*alpha));
		temp2.set(Tk/3*cos(angle+alpha),Tk/3*sin(angle+alpha));
		temp3.set(Tk/3*r2,0);
		D[1][2]=temp1+temp2+temp3;
		D[2][3]=D[1][2];
		D[3][1]=D[1][2];

		temp1.set(Tk/3*cos(-angle+alpha),Tk/3*sin(-angle+alpha));
		temp2.set(Tk/3*cos(angle+2*alpha),Tk/3*sin(angle+2*alpha));
		temp3.set(Tk/3*r2,0);
		D[1][3]=temp1+temp2+temp3;
		D[2][1]=D[1][3];
		D[3][2]=D[1][3];
	}
	else
	{
		temp1.set(1/Tk*cos(-angle),1/Tk*sin(-angle));
		A[1][1]=temp1;
		temp1.set(1/Tk*cos(angle),1/Tk*sin(angle));
		B[1][1]=temp1;
		temp1.set(Tk*cos(-angle),Tk*sin(-angle));
		C[1][1]=temp1;
		temp1.set(Tk*cos(angle),Tk*sin(angle));
		D[1][1]=temp1;
	}



	for (i=1;i<=Phase;i++)
	{
		for (j=1;j<=Phase;j++)
		{
			Tmatrix[i][j].set(0,0);
		}
	}

	if (IVtype==1 && HLtype==1)//%电流，高压侧
	{
		for (i=1;i<=Phase;i++)
		{
			for (j=1;j<=Phase;j++)
			{
				Tmatrix[i][j]=A[i][j];
			}
		}
	}
	else if (IVtype==2 && HLtype==1)//%电压，高压侧
	{
		for (i=1;i<=Phase;i++)
		{
			for (j=1;j<=Phase;j++)
			{
				Tmatrix[i][j]=C[i][j];
			}
		}
	}
	else if (IVtype==1 && HLtype==2)//%电流，低压侧
	{
		for (i=1;i<=Phase;i++)
		{
			for (j=1;j<=Phase;j++)
			{
				Tmatrix[i][j]=D[i][j];
			}
		}
	}
	else if (IVtype==2 && HLtype==2)//%电压，低压侧
	{
		for (i=1;i<=Phase;i++)
		{
			for (j=1;j<=Phase;j++)
			{
				Tmatrix[i][j]=B[i][j];
			}
		}
	}
	for(int i=0;i<=Phase;i++)
	{
		delete[] A[i];
		delete[] B[i];
		delete[] C[i];
		delete[] D[i];
	}
	delete[] A;
	delete[] B;
	delete[] C;
	delete[] D;

}

void BackforePowerflow::calculate(double ration)//%可以输出无功的前推回带法
{
	int i,j,k;
	int n,m;
	int num;
	int tempnum1,tempnum2,tempnum3;
	int trannum;
	int rootdgnum;
	double maxerror;
	double temperror;
	Complex cons;
	Complex *tempU;
	Complex *tempnodeU;
	cons.set(0.5,0);
	tempU=new Complex[Phase+1];
	tempnodeU=new Complex[Phase+1];
	
	Power=new double[Data.numDes+2];
	vPower=new double[Data.numDes+2];
	for (i=1;i<=Data.numDes+1;i++)
	{
		Power[i]=0;
		vPower[i]=0;
	}
	
	for (n=1;n<=30;n++)
	{
		maxerror=-10;//%每次前推回代都初始化最大误差
		pvaddQ();
		for (m=1;m<=Data.numBus;m++)//%每次循环都先初始化节点电流值
		{
			for (k=1;k<=Phase;k++)
			{
				node[m].I[k]=(node[m].PQ[k]/node[m].U[k]).conjugate();
				node[m].I[k].set(ration*node[m].I[k].real(),ration*node[m].I[k].imag());
			}

			for (i=1;i<=Data.numVar;i++)//%无功补偿搜索
			{
				if (m==var[i].nodenum)
				{
					for (k=1;k<=Phase;k++)
					{
						node[m].I[k]=node[m].I[k]+(var[i].Q[k]/node[m].U[k]).conjugate();
					}
				}
			}

			for (i=1;i<=nDgnode;i++)
			{
				if (m==Dgnode[i][Data.numDes+1])
				{
					for (j=1;j<=Dgnode[i][Data.numDes+2];j++)
					{
						num=Dgnode[i][j];
//						if (des[num].type==2)
//						{
							for (k=1;k<=Phase;k++)
							{
								dI.set(-des[num].P[k],-des[num].Q[k]);
								dI=(dI/node[m].U[k]).conjugate();
								node[m].I[k]=node[m].I[k]+dI;
							}
//						}
					}
					break;
				}
			}

		}

		for (i=1;i<=Phase;i++)
		{
			//cout<<node[2].I[i]<<'\t';
		}
		//cout<<endl;
		for (i=1;i<=Phase;i++)
		{
			//cout<<node[3].I[i]<<'\t';
		}
		//cout<<endl;

		for (i=1;i<=Phase;i++)//%初始化根节点的电流值  
		{
			node[root].I[i].set(0,0);
		}

		for (j=nlevel;j>=2;j--)//%回代电流
		{
			for (k=1;k<=level[j][Data.numBus+1];k++)
			{
				tempnum1=level[j][k];
				tempnum2=node[tempnum1].pare;
				tempnum3=node[tempnum1].bran;
				if (branch[tempnum3].type==2)//%若为变压器线路
				{
					trannum=findTrans(branch[tempnum3].num);//%找到树枝对应的变压器编号
					if (tempnum2==tran[trannum].Ti &&tempnum1==tran[trannum].Tj)//%如果母节点为高压侧，子节点为低压侧
					{
						for (int l=1;l<=Phase;l++)
						{
							branch[tempnum3].Ie[l]=node[tempnum1].I[l];
						}

						Tranmatrix(tran[trannum].zeroi,tran[trannum].zeroj,tran[trannum].angle,tran[trannum].K,1,1);//%从低压侧到高压侧的电流转换矩阵

						for (int l=1;l<=Phase;l++)
						{
							for (int p=1;p<=Phase;p++)
							{
								//cout<<Tmatrix[l][p]<<'\t';
							}
						}
						//cout<<endl;

						for (int l=1;l<=Phase;l++)
						{
							branch[tempnum3].Is[l].set(0,0);
							for (int p=1;p<=Phase;p++)
							{
								branch[tempnum3].Is[l]=branch[tempnum3].Is[l]+Tmatrix[l][p]*branch[tempnum3].Ie[p];
								
							}
							//cout<<branch[tempnum3].Is[l]<<'\t';
							//cout<<endl;
						}

						for (int l=1;l<=Phase;l++)
						{
							node[tempnum2].I[l]=node[tempnum2].I[l]+branch[tempnum3].Is[l];
							//cout<<node[tempnum2].I[l]<<'\t';
							
						}
						//cout<<endl;
					} 
					else if(tempnum2==tran[trannum].Tj &&tempnum1==tran[trannum].Ti)//%如果母节点为低压侧，子节点为高压侧
					{
						for (int l=1;l<=Phase;l++)
						{
							branch[tempnum3].Ie[l]=node[tempnum1].I[l];
						}

						Tranmatrix(tran[trannum].zeroi,tran[trannum].zeroj,tran[trannum].angle,tran[trannum].K,1,2);//%从高压侧到低压侧的电流转换矩阵

						for (int l=1;l<=Phase;l++)
						{
							for (int p=1;p<=Phase;p++)
							{
								//cout<<Tmatrix[l][p]<<'\t';
							}
						}

						for (int l=1;l<=Phase;l++)
						{
							branch[tempnum3].Is[l].set(0,0);
							for (int p=1;p<=Phase;p++)
							{
								branch[tempnum3].Is[l]=branch[tempnum3].Is[l]+Tmatrix[l][p]*branch[tempnum3].Ie[p];
							}
							//cout<<branch[tempnum3].Is[l]<<'\t';
						}
						//cout<<endl;

						for (int l=1;l<=Phase;l++)
						{
							node[tempnum2].I[l]=node[tempnum2].I[l]+branch[tempnum3].Is[l];
						}
					}
				}
				else//%若为普通线路
				{
					for (int l=1;l<=Phase;l++)
					{
						branch[tempnum3].Ie[l]=node[tempnum1].I[l];
					}

					
					for (int l=1;l<=Phase;l++)
					{
						branch[tempnum3].Is[l].set(0,0);
						branch[tempnum3].Is[l]=branch[tempnum3].Is[l]+branch[tempnum3].Ie[l];
						for (int p=1;p<=Phase;p++)
						{
							branch[tempnum3].Is[l]=branch[tempnum3].Is[l]+branch[tempnum3].B[l][p]*(node[tempnum1].U[p]+node[tempnum2].U[p])*cons;
							
						}
						//cout<<branch[tempnum3].Is[l]<<'\t';
						//cout<<endl;
					}

					for (int l=1;l<=Phase;l++)
					{
						node[tempnum2].I[l]=node[tempnum2].I[l]+branch[tempnum3].Is[l];
						//cout<<node[tempnum2].I[l]<<'\t';
					}
					
					//cout<<endl;
				}
			}
		}

		for (j=2;j<=nlevel;j++)//%前推电压
		{
			for (k=1;k<=level[j][Data.numBus+1];k++)
			{
				tempnum1=level[j][k];
				tempnum2=node[tempnum1].pare;
				tempnum3=node[tempnum1].bran;

				for (int l=1;l<=Phase;l++)
				{
					tempU[l]=node[tempnum1].U[l];
					//cout<<tempU[l]<<'\t';
				}
				//cout<<endl;

				if (branch[tempnum3].type==2)//%若为变压器线路
				{
					trannum=findTrans(branch[tempnum3].num);//%找到树枝对应的变压器编号
					if (tempnum2==tran[trannum].Ti &&tempnum1==tran[trannum].Tj)
					{
						Tranmatrix(tran[trannum].zeroi,tran[trannum].zeroj,tran[trannum].angle,tran[trannum].K,2,2);//%如果母节点为高压侧，子节点为低压侧
						for (int l=1;l<=Phase;l++)
						{
							node[tempnum1].U[l].set(0,0);
							for (int p=1;p<=Phase;p++)
							{
								node[tempnum1].U[l]=node[tempnum1].U[l]+Tmatrix[l][p]*node[tempnum2].U[p]-branch[tempnum3].Z[l][p]*branch[tempnum3].Ie[p];
							}
							//cout<<node[tempnum1].U[l]<<'\t';
						}
						//cout<<endl;
					}
					else if (tempnum2==tran[trannum].Tj &&tempnum1==tran[trannum].Ti)//%如果母节点为低压侧，子节点为高压侧
					{
						Tranmatrix(tran[trannum].zeroi,tran[trannum].zeroj,tran[trannum].angle,tran[trannum].K,2,1);//%从低压侧到高压侧的电压转换矩阵
						for (int l=1;l<=Phase;l++)
						{
							tempnodeU[l].set(0,0);
							tempnodeU[l]=tempnodeU[l]+node[tempnum2].U[l];
							for (int p=1;p<=Phase;p++)
							{
								tempnodeU[l]=tempnodeU[l]-branch[tempnum3].Z[l][p]*branch[tempnum3].Is[p];
							}
							//cout<<tempnodeU[l]<<'\t';
						}
						//cout<<endl;

						for (int l=1;l<=Phase;l++)
						{
							node[tempnum1].U[l].set(0,0);
							//node[tempnum1].U[l]=node[tempnum1].U[l];
							for (int p=1;p<=Phase;p++)
							{
								node[tempnum1].U[l]=node[tempnum1].U[l]+Tmatrix[l][p]*tempnodeU[p];
							}
							//cout<<node[tempnum1].U[l]<<'\t';
						}
						//cout<<endl;

					}
				} 
				else//%若为普通线路
				{
					for (int l=1;l<=Phase;l++)
					{
						node[tempnum1].U[l].set(0,0);
						node[tempnum1].U[l]=node[tempnum1].U[l]+node[tempnum2].U[l];
						for (int p=1;p<=Phase;p++)
						{
							node[tempnum1].U[l]=node[tempnum1].U[l]-branch[tempnum3].Z[l][p]*branch[tempnum3].Is[p]-branch[tempnum3].B[l][p]*node[tempnum2].U[p]*cons;
						}
						//cout<<node[tempnum1].U[l]<<'\t';
					}
					//cout<<endl;
				}

				
				for (int l=1;l<=Phase;l++)
				{
					temperror=(node[tempnum1].U[l]-tempU[l]).mod();
					if (temperror>maxerror)
					{
						maxerror=temperror;
					}
				}
			}
		}

		if (maxerror<0.0001)//%收敛判断
		{
			break;
		}
		
	}


	//////////////////////////
	for (j=nlevel;j>=2;j--)//%回代电流
	{
		for (k=1;k<=level[j][Data.numBus+1];k++)
		{
			tempnum1=level[j][k];
			tempnum2=node[tempnum1].pare;
			tempnum3=node[tempnum1].bran;
	        for (int l=1;l<=Phase;l++)
		    {
				branch[tempnum3].loss[l]=node[tempnum2].U[l]*branch[tempnum3].Is[l].conjugate()-node[tempnum1].U[l]*branch[tempnum3].Ie[l].conjugate();
				branch[tempnum3].PQi[l]=node[tempnum2].U[l]*branch[tempnum3].Is[l].conjugate();
				branch[tempnum3].PQj[l]=node[tempnum1].U[l]*branch[tempnum3].Ie[l].conjugate();
			//cout<<branch[tempnum3].loss[l]<<" "<<node[tempnum2].U[l]<<" "<<branch[tempnum3].Is[l]<<" ";
			}
			//cout<<endl;

		}
	}





	////////////////////////////

	//cons.set(Sbase,0);
	rootdgnum=0;
	//Power=new double[Data.numDes+2];
	for (i=1;i<=Data.numDes+1;i++)
	{
		Power[i]=0;
	}
	//vPower=new double[Data.numDes+2];
	for (i=1;i<=Data.numDes+1;i++)
	{
		vPower[i]=0;
	}

	if (netflag==1)//%若为并网状态，将主网的有功和无功保存在第numDg个位置
	{
		for (i=1;i<=Phase;i++)
		{
			Power[Data.numDes+1]=Power[Data.numDes+1]+(node[root].U[i]*node[root].I[i].conjugate()).real()*Sbase+node[root].PQ[i].real()*Sbase;//%最终从电网得出的有功，需要加上该节点的负荷
			//cout<<(node[root].U[i]*node[root].I[i].conjugate())<<'\t';
			//cout<<node[root].PQ[i].real()<<'\t';
			//cout<<endl;
			vPower[Data.numDes+1]=vPower[Data.numDes+1]+(node[root].U[i]*node[root].I[i].conjugate()).imag()*Sbase+node[root].PQ[i].imag()*Sbase;
		}

		for (i=1;i<=Data.numDes;i++)
		{
			for (j=1;j<=Phase;j++)
			{
				Power[i]=Power[i]+des[i].P[j]*Sbase;
				vPower[i]=vPower[i]+des[i].Q[j]*Sbase;
			}
		}

	} 
	else//%若为孤网状态，将平衡节点的功率保存在numDg个位置
	{
		for (i=1;i<=Phase;i++)
		{
			Power[Data.numDes+1]=Power[Data.numDes+1]+(node[root].U[i]*node[root].I[i].conjugate()).real()*Sbase+node[root].PQ[i].real()*Sbase;
			vPower[Data.numDes+1]=vPower[Data.numDes+1]+(node[root].U[i]*node[root].I[i].conjugate()).imag()*Sbase+node[root].PQ[i].imag()*Sbase;
		}

		for (i=1;i<=nDgnode;i++)
		{
			if (root==Dgnode[i][Data.numDes+1])//%从保存分布式电源的节点里寻找
			{
				rootdgnum=Dgnode[i][1];
				for (j=1;j<=Dgnode[i][Data.numDes+2];j++)//%主要是将该节点中的pv节点定为了平衡机，好先算出该节点其它机的功率，最后再算他发出的的功率，因为平衡节点只能计算出节点全部发出的功率
				{
					num=Dgnode[i][j];
					if (des[num].type==2)
					{
						rootdgnum=num;
						break;
					}
				}

				Power[rootdgnum]=Power[Data.numDes+1];//%先将平衡机的功率定义为平衡节点的功率，再慢慢减去其它机发出的功率，最终即为其所发功率。
				vPower[rootdgnum]=vPower[Data.numDes+1];

				for (j=1;j<=Dgnode[i][Data.numDes+2];j++)
				{
					num=Dgnode[i][j];
					if (rootdgnum!=num)
					{
						Power[num]=0;
						for (k=1;k<=Phase;k++)
						{
							Power[num]=Power[num]+des[num].P[k]*Sbase;
						}
						vPower[num]=0;
						for (k=1;k<=Phase;k++)
						{
							vPower[num]=vPower[num]+des[num].Q[k]*Sbase;
						}

						Power[rootdgnum]=Power[rootdgnum]-Power[num];
						vPower[rootdgnum]=vPower[rootdgnum]-vPower[num];
					}
				}
			} 
			else//%若根节点不为该节点，则该节点上的分布式电源各算各发出的功率
			{
				for (j=1;j<=Dgnode[i][Data.numDes+2];j++)
				{
					num=Dgnode[i][j];

					Power[num]=0;
					for (k=1;k<=Phase;k++)
					{
						Power[num]=Power[num]+des[num].P[k]*Sbase;
					}
					vPower[num]=0;
					for (k=1;k<=Phase;k++)
					{
						vPower[num]=vPower[num]+des[num].Q[k]*Sbase;
					}
				}
			}
		}
	}

	for (i=1;i<=Data.numDes+1;i++)
	{
		//cout<<Power[i]<<'\t';
	}
	//cout<<endl;

	for (i=1;i<=Data.numDes+1;i++)
	{
		//cout<<vPower[i]<<'\t';
	}
	//cout<<endl;
	delete[] tempU;
	delete[] tempnodeU;
}


void BackforePowerflow::output()//%可以输出无功的前推回带法
{
	for(int i=1;i<Data.numBran+1;i++)
	{
		branchloss[i]=abs(branch[i].loss[1].real()/(branch[i].PQi[1].real()+branch[i].PQj[1].real()+0.00000000000001)*2);
		//cout<<branchloss[i]<<" ";
	}
/*
	double generationP, generationQ,loadP,loadQ,lossP,lossQ;
	int i,j;
	int num;
	double **Pg;
	double **Qg;
	double **Pij;
	double **Qij;
	Complex *PQij0;
	Complex *PQij1;
	PQij0=new Complex [Data.numBran+1];
	PQij1=new Complex [Data.numBran+1];
	
	Pij=new double *[Data.numBran+1];
	//CHECKPOINTER(Pij);
	Qij=new double *[Data.numBran+1];
	//CHECKPOINTER(Qij);
	for(int i=0;i<Data.numBran+1;i++)
	{
		Pij[i]=new double [2];
		//CHECKPOINTER(Pij[i]);
		Qij[i]=new double [2];
		//CHECKPOINTER(Qij[i]);
	}

	for(int i=1;i<Data.numBran+1;i++)
	{
		Pij[i][0]=0;
		Qij[i][0]=0;
		Pij[i][1]=0;
		Qij[i][1]=0;
		PQij0[i].set(0,0);
		PQij1[i].set(0,0);
		//cout<<branch[i].i<<" "<<branch[i].j<<endl;

		if(branch[i].type==1)
		{
			for (int j=1;j<=Phase;j++)
			{
				PQij0[i]=PQij0[i]+branch[i].Is[j].conjugate()*node[branch[i].i].U[j];
				PQij1[i]=PQij1[i]+branch[i].Ie[j].conjugate()*node[branch[i].j].U[j];
				//PQij0[i]=branch[i].loss[j];
				//PQij1[i].set(0,0);
			}
		}
		else
		{
			for (int j=1;j<=Phase;j++)
			{
				PQij0[i]=PQij0[i]+branch[i].Is[j].conjugate()*node[branch[i].i].U[j];
				PQij1[i]=PQij1[i]+branch[i].Ie[j].conjugate()*node[branch[i].j].U[j];
			}
		}
		Pij[i][0]=PQij0[i].real();
		Qij[i][0]=PQij0[i].imag();
		Pij[i][1]=PQij1[i].real();
		Qij[i][1]=PQij1[i].imag();
	}
	for(int i=1;i<Data.numBran+1;i++)
	{
		branchloss[i]=abs(branch[i].loss[1].real()/(Pij[i][0]+Pij[i][1]+0.00000000000001)*2);
	}
	

	Pg=(double **)new double[Data.numBus+1];
	for (i=1;i<=Data.numBus;i++)
	{
		Pg[i]=new double[Phase+1];
	}

	Qg=(double **)new double[Data.numBus+1];
	for (i=1;i<=Data.numBus;i++)
	{
		Qg[i]=new double[Phase+1];
	}

	for (i=1;i<=Data.numBus;i++)
	{
		for (j=1;j<=Phase;j++)
		{
			Pg[i][j]=0;
			Qg[i][j]=0;
		}
	}

	for (i=1;i<=Data.numDes;i++)
	{
		num=des[i].nodenum;
		for (j=1;j<=Phase;j++)
		{
			Pg[num][j]=Pg[num][j]+des[i].P[j];
			Qg[num][j]=Qg[num][j]+des[i].Q[j];
		}
	}
	
	fstream outputfile;
	outputfile.open("Result.txt",ios::out);
	outputfile<<"**********************"<<"母线标准试验系统前推回代法潮流计算结果************************\n";
	outputfile<<"-----------------------------------------------------------------------------------------------\n";
	outputfile<<"总有功发电\t"<<"总有功发电\t"<<"总有功负荷\t"<<"总无功负荷\t"<<"总有功网损\t"<<"总无功网损"<<"\n";

	generationP=0;
	generationQ=0;
	loadP=0;
	loadQ=0;
	lossP=0;
	lossQ=0;
	if (netflag==1)
	{
		for (i=1;i<=Data.numDes+1;i++)
		{
			generationP=generationP+Power[i];
			generationQ=generationQ+vPower[i];
		}
	}
	else
	{
		for (i=1;i<=Data.numDes;i++)
		{
			generationP=generationP+Power[i];
			generationQ=generationQ+vPower[i];
		}
	}

		for (i=1;i<=Data.numBus;i++)
		{
			for (j=1;j<=Phase;j++)
			{
				loadP=loadP+node[i].PQ[j].real()*Sbase;
				loadQ=loadQ+node[i].PQ[j].imag()*Sbase;
			}
		}

		lossP=generationP-loadP;
		lossQ=generationQ-loadQ;

		outputfile.setf(ios::right);
		outputfile.setf(ios::fixed);
		outputfile<<setw(9)<<setprecision(6)<<generationP<<"\t";
		outputfile<<setw(9)<<setprecision(6)<<generationQ<<"\t";
		outputfile<<setw(9)<<setprecision(6)<<loadP<<"\t";
		outputfile<<setw(9)<<setprecision(6)<<loadQ<<"\t";
		outputfile<<setw(9)<<setprecision(6)<<lossP<<"\t";
		outputfile<<setw(9)<<setprecision(6)<<lossQ<<endl;
		outputfile.unsetf(ios::fixed);
		//outputfile.open("Result.txt",ios::out);
	outputfile<<"-----------------------------------------------------------------------------------------------\n";
	outputfile<<"线路节点编号\t"<<"节点始端有功发电\t"<<"节点始端无功发电\t"<<"节点终端有功负荷\t"<<"节点终端无功负荷\t"<<"节点有功网损\t"<<"节点无功网损\t"<<"节点有功网损系数"<<"\n";
	for(int i=1;i<Data.numBran+1;i++)
	{
		outputfile.setf(ios::right);
		outputfile.setf(ios::fixed);
		outputfile<<setw(9)<<setprecision(6)<<branch[i].num<<"\t";
		outputfile<<setw(9)<<setprecision(6)<<Pij[i][0]<<"\t";
		outputfile<<setw(9)<<setprecision(6)<<Qij[i][0]<<"\t";
		outputfile<<setw(9)<<setprecision(6)<<Pij[i][1]<<"\t";
		outputfile<<setw(9)<<setprecision(6)<<Qij[i][1]<<"\t";
		outputfile<<setw(9)<<setprecision(6)<<abs(Pij[i][0]-Pij[i][1])<<"\t";
		outputfile<<setw(9)<<setprecision(6)<<abs(Qij[i][0]-Qij[i][1])<<"\t";
		outputfile<<setw(9)<<setprecision(6)<<abs(abs(Pij[i][0]-Pij[i][1])/(Pij[i][0]+Pij[i][1]+0.00000000000001)*2)<<endl;
		outputfile.unsetf(ios::fixed);
		branchloss[i]=abs(branch[i].loss[1].real()/(Pij[i][0]+Pij[i][1]+0.00000000000001)*2);
		//branchloss[i]=(node[i].U[j]*branch[i].Is[j].conjugate());
	}

		outputfile<<"节点\t"<<"电压幅值V\t"<<" 电压相角a\t"<<"有功Pg\t\t"<<"无功Qg\t\t"<<"有功Pi\t\t"<<"无功Qi\n";

		outputfile.setf(ios::right);
		for (i=1;i<=Data.numBus;i++)
		{
			for (j=1;j<=Phase;j++)
			{
				outputfile<<i<<"\t";
				outputfile.setf(ios::fixed);
				outputfile<<setw(9)<<setprecision(6)<<node[i].U[j].mod()<<"\t";
				outputfile<<setw(10)<<setprecision(6)<<node[i].U[j].angle()*180/3.1415926<<"\t";
				outputfile<<setw(9)<<setprecision(6)<<Pg[i][j]<<"\t";
				outputfile<<setw(9)<<setprecision(6)<<Qg[i][j]<<"\t";
				outputfile<<setw(9)<<setprecision(6)<<node[i].PQ[j].real()<<"\t";
				outputfile<<setw(9)<<setprecision(6)<<node[i].PQ[j].imag()<<endl;
				outputfile.unsetf(ios::fixed);
			}
		}

	for(int i=0;i<Data.numBran+1;i++)
	{
		delete[] Pij[i];
	}
	delete[] Pij;
	delete[] Qij;
	delete[] PQij0;
	delete[] PQij1;*/
}
/*
void BackforePowerflow::inputschedule()//输入一天的计算数据
{
	int a,b;

	ifstream fin1("load_dynamic.txt");
	if (!fin1)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	for (int i=1;i<=Data.numNode;i++)
	{
		fin1>>a;
		fin1>>b;
		for(int j=0;j<144;j++)
		{
			fin1>>PL[i][j];
		}
	}
	fin1.close();
	ifstream fin2("energy_dynamic.txt");
	if (!fin2)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	for (int i=1;i<=Data.numDes;i++)
	{
		fin2>>a;
		fin2>>b;
		for(int j=0;j<144;j++)
		{
			fin2>>PG[i][j];
		}
	}
	fin2.close();

}*/