

#include <stdio.h>
//#include <cstdio>
#include <iostream>
//using namespace std;
#include "lp_lib.h"
#include "head.h"
//#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
//#include<stdio.h> 
#include <cstring>
#include <cmath>
//#include <vector> 
#include<iomanip>
using namespace std;
#define CHECKPOINTER(p){if(p==NULL)\
{printf_s("insufficient memory\n");exit(1);}}
const int judgedefault=-99;
#define ESSENTIAL(p){if(p==judgedefault)\
{printf_s("请输入必需数据：");exit(1);}}
#define NON_ESSENTIAL(p,pdefault){if(p==judgedefault)\
{p=pdefault;}}
/*#define NON_ESSENTIALCHR(p,pdefault){char s[10];\
	sprintf_s(s,"%d",judgedefault);\
	if(string(p)==string(s)){strcpy_s(p,pdefault);}}*/
#define NON_ESSENTIALCHR(p,pdefault){char s[10];\
	sprintf_s(s,"%d",judgedefault);\
	if(strcmp(p,s)==0){strcpy_s(p,pdefault);}}

//ILOSTLBEGIN


#if defined FORTIFY
#include "lp_fortify.h"
int EndOfPgr(int i)
{
	exit(i);
}
#endif

void press_ret(void)
{
#if !defined NORETURN
	printf("[return]");
	getchar();
#endif
}




void SCHEDULE::inputfoundationdata()
{
	ifstream fin("microgrid_foudation.txt");
	if (!fin)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fin.ignore(1024,'*');
	fin>>controllableunitnum>>node>>energystoragenum>>renewableenergynum>>loadnum>>Ttotal>>pollutionnum>>mglevel;
	mglevelnum=new int[mglevel];
	CHECKPOINTER(mglevelnum);
	for(int i=0;i<mglevel;i++)
	{
		fin>>mglevelnum[i];
	}
	virtualloadnum=0;
	if(mglevel==1)
	{
		virtualloadnum=0;
	}
	else
	{
		for(int i=1;i<mglevel;i++)
		{
			virtualloadnum+=mglevelnum[i];
		}
	}
	fin.close(); 
}
void SCHEDULE::inputstaticdata()
{
	ifstream fin1("controllable_unit.txt");
	if (!fin1)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fin1.ignore(10240,'*');
	for(int i=0;i<controllableunitnum;i++)
	{
		fin1>>Controllableunitdata[i].Identifier>>Controllableunitdata[i].ID32>>Controllableunitdata[i].name>>Controllableunitdata[i].type>>Controllableunitdata[i].curve;
		for(int j=0;j<node;j++)
		{
			fin1>>Controllableunitdata[i].Pi[j];
		}
		for(int j=0;j<node;j++)
		{
			fin1>>Controllableunitdata[i].ci[j];
		}
		fin1>>Controllableunitdata[i].a>>Controllableunitdata[i].b>>Controllableunitdata[i].c>>Controllableunitdata[i].d>>Controllableunitdata[i].fuelcost;
		fin1>>Controllableunitdata[i].Shi>>Controllableunitdata[i].deltiup>>Controllableunitdata[i].deltidown>>Controllableunitdata[i].PHi>>Controllableunitdata[i].PLi>>Controllableunitdata[i].RHi>>Controllableunitdata[i].MOTi>>Controllableunitdata[i].MDTi>>Controllableunitdata[i].COM
			>>Controllableunitdata[i].Invest>>Controllableunitdata[i].year>>Controllableunitdata[i].k>>Controllableunitdata[i].Ramp;
		for(int j=0;j<pollutionnum;j++)
		{
			fin1>>Controllableunitdata[i].Q[j];
		}
	}
	fin1.close(); 
	ifstream fin2("energy_storage.txt");
	if (!fin2)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fin2.ignore(10240,'*');
	for(int i=0;i<energystoragenum;i++)
	{
		fin2>>Energystoragedata[i].Identifier>>Energystoragedata[i].ID32>>Energystoragedata[i].name>>Energystoragedata[i].type>>Energystoragedata[i].PgHk>>Energystoragedata[i].PgLk>>Energystoragedata[i].PpHk>>Energystoragedata[i].PpLk>>Energystoragedata[i].VHk>>Energystoragedata[i].VLk>>Energystoragedata[i].yitag>>Energystoragedata[i].yitap>>Energystoragedata[i].Wk;
		fin2>>Energystoragedata[i].Invest>>Energystoragedata[i].MaintenanceCost>>Energystoragedata[i].year>>Energystoragedata[i].cyclenum;
		fin2>>Energystoragedata[i].VHkgridmargin>>Energystoragedata[i].VLkgridmargin>>Energystoragedata[i].VHkislandmargin>>Energystoragedata[i].VLkislandmargin;
		fin2>>Energystoragedata[i].VHkgridMARGINLIMIT>>Energystoragedata[i].VLkgridMARGINLIMIT>>Energystoragedata[i].VHkislandMARGINLIMIT>>Energystoragedata[i].VLkislandMARGINLIMIT;
		//fin2>>Energystoragedata[i].Ramp;
	}
	fin2.close(); 
	ifstream fin3("pollution.txt");
	if (!fin3)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fin3.ignore(1024,'*');
	for(int i=0;i<pollutionnum;i++)
	{
		fin3>>Qgrid[i];
	}
	//fin3.ignore(1024,'*');
	for(int i=0;i<pollutionnum;i++)
	{
		fin3>>V[i];
	}
	fin3.close(); 
	ifstream fin4("powergrid_microgrid.txt");
	if (!fin4)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fin4.ignore(1024,'*');
	fin4>>Griddata.gridnum>>Griddata.Pbuymax>>Griddata.Psellmax;
	fin4>>Griddata.Ramp;
	fin4.close(); 
	ifstream fin5("load.txt");
	if (!fin5)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fin5.ignore(1024,'*');
	for(int i=0;i<4;i++)
	{
		fin5>>Pcutlevel[i]>>Pcutcost[i];
	}
	//fin5.ignore(1024,'*');
	for(int j=0;j<loadnum;j++)
	{
		fin5>>Loaddata[j].Identifier>>Loaddata[j].ID32>>Loaddata[j].name>>Loaddata[j].error>>Loaddata[j].level;
	}
	fin5.close(); 
	ifstream fin6("renewable_energy.txt");
	if (!fin6)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fin6.ignore(1024,'*');
	for(int i=0;i<renewableenergynum;i++)
	{
		fin6>>Renewableenergydata[i].Identifier>>Renewableenergydata[i].ID32>>Renewableenergydata[i].name>>Renewableenergydata[i].type>>Renewableenergydata[i].error;
	}
	fin6.close();

	ifstream fin7("levelidentifier.txt");
	if (!fin7)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fin7.ignore(1024,'*');
	for(int i=0;i<controllableunitnum+energystoragenum+loadnum+renewableenergynum;i++)
	{
		fin7>>Levelclassify[i]>>LevelID32[i]>>LevelIdentify[i]>>LevelIdentifynext[i];
	}
	fin7.close();
}
void SCHEDULE::levelsearch()
{
	int iser;
	int ilel;
		for(int i=0;i<controllableunitnum;i++)
		{
			ilel=0;
			iser=0;
			while(Levelclassify[iser]!=1||Controllableunitdata[i].ID32!=LevelID32[iser]&&iser<controllableunitnum+energystoragenum+loadnum+renewableenergynum)
			{
				iser++;
			}
			Controllableunitdata[i].levelIdentifier[ilel]=LevelIdentify[iser];
			Controllableunitdata[i].levelIdentifier[ilel+1]=LevelIdentifynext[iser];
			for(int inum=1;inum<mglevel;inum++)
			{
				if (Controllableunitdata[i].levelIdentifier[ilel+1]>0)
				{
					iser=0;
				while(Controllableunitdata[i].levelIdentifier[ilel+1]!=LevelIdentify[iser]&&iser<controllableunitnum+energystoragenum+loadnum+renewableenergynum)
				{
					iser++;
				}
				ilel++;
				Controllableunitdata[i].levelIdentifier[ilel]=LevelIdentify[iser];
				Controllableunitdata[i].levelIdentifier[ilel+1]=LevelIdentifynext[iser];
				}
				
			}
			if (ilel!=mglevel-1)
			{
				for (int ic=0;ic<ilel+1;ic++)
				{
					Controllableunitdata[i].levelIdentifier[mglevel-1-ic]=Controllableunitdata[i].levelIdentifier[ilel-ic];
				}
				for (int ic=0;ic<mglevel-1-ilel;ic++)
				{
					Controllableunitdata[i].levelIdentifier[ic]=0;
				}
			}
		}
		for(int i=0;i<energystoragenum;i++)
		{
			ilel=0;
			iser=0;
			while(Levelclassify[iser]!=2||Energystoragedata[i].ID32!=LevelID32[iser]&&iser<controllableunitnum+energystoragenum+loadnum+renewableenergynum)
			{
				iser++;
			}
			Energystoragedata[i].levelIdentifier[ilel]=LevelIdentify[iser];
			Energystoragedata[i].levelIdentifier[ilel+1]=LevelIdentifynext[iser];
			for(int inum=1;inum<mglevel;inum++)
			{
				if (Energystoragedata[i].levelIdentifier[ilel+1]>0)
				{
					iser=0;
				while(Energystoragedata[i].levelIdentifier[ilel+1]!=LevelIdentify[iser]&&iser<controllableunitnum+energystoragenum+loadnum+renewableenergynum)
				{
					iser++;
				}
				ilel++;
				Energystoragedata[i].levelIdentifier[ilel]=LevelIdentify[iser];
				Energystoragedata[i].levelIdentifier[ilel+1]=LevelIdentifynext[iser];
				}
				
			}
			if (ilel!=mglevel-1)
			{
				for (int ic=0;ic<ilel+1;ic++)
				{
					Energystoragedata[i].levelIdentifier[mglevel-1-ic]=Energystoragedata[i].levelIdentifier[ilel-ic];
				}
				for (int ic=0;ic<mglevel-1-ilel;ic++)
				{
					Energystoragedata[i].levelIdentifier[ic]=0;
				}
			}
		}
		for(int i=0;i<loadnum;i++)
		{
			ilel=0;
			iser=0;
			while(Levelclassify[iser]!=3||Loaddata[i].ID32!=LevelID32[iser]&&iser<controllableunitnum+energystoragenum+loadnum+renewableenergynum)
			{
				iser++;
			}
			Loaddata[i].levelIdentifier[ilel]=LevelIdentify[iser];
			Loaddata[i].levelIdentifier[ilel+1]=LevelIdentifynext[iser];
			for(int inum=1;inum<mglevel;inum++)
			{
				if (Loaddata[i].levelIdentifier[ilel+1]>0)
				{
					iser=0;
				while(Loaddata[i].levelIdentifier[ilel+1]!=LevelIdentify[iser]&&iser<controllableunitnum+energystoragenum+loadnum+renewableenergynum)
				{
					iser++;
				}
				ilel++;
				Loaddata[i].levelIdentifier[ilel]=LevelIdentify[iser];
				Loaddata[i].levelIdentifier[ilel+1]=LevelIdentifynext[iser];
				}
				
			}
			if (ilel!=mglevel-1)
			{
				for (int ic=0;ic<ilel+1;ic++)
				{
					Loaddata[i].levelIdentifier[mglevel-1-ic]=Loaddata[i].levelIdentifier[ilel-ic];
				}
				for (int ic=0;ic<mglevel-1-ilel;ic++)
				{
					Loaddata[i].levelIdentifier[ic]=0;
				}
			}
		}
		for(int i=0;i<renewableenergynum;i++)
		{
			ilel=0;
			iser=0;
			while(Levelclassify[iser]!=4||Renewableenergydata[i].ID32!=LevelID32[iser]&&iser<controllableunitnum+energystoragenum+loadnum+renewableenergynum)
			{
				iser++;
			}
			Renewableenergydata[i].levelIdentifier[ilel]=LevelIdentify[iser];
			Renewableenergydata[i].levelIdentifier[ilel+1]=LevelIdentifynext[iser];
			for(int inum=1;inum<mglevel;inum++)
			{
				if (Renewableenergydata[i].levelIdentifier[ilel+1]>0)
				{
					iser=0;
				while(Renewableenergydata[i].levelIdentifier[ilel+1]!=LevelIdentify[iser]&&iser<controllableunitnum+energystoragenum+loadnum+renewableenergynum)
				{
					iser++;
				}
				ilel++;
				Renewableenergydata[i].levelIdentifier[ilel]=LevelIdentify[iser];
				Renewableenergydata[i].levelIdentifier[ilel+1]=LevelIdentifynext[iser];
				}
				
			}
			if (ilel!=mglevel-1)
			{
				for (int ic=0;ic<ilel+1;ic++)
				{
					Renewableenergydata[i].levelIdentifier[mglevel-1-ic]=Renewableenergydata[i].levelIdentifier[ilel-ic];
				}
				for (int ic=0;ic<mglevel-1-ilel;ic++)
				{
					Renewableenergydata[i].levelIdentifier[ic]=0;
				}
			}
		}
		int **temp;
		temp=new int *[mglevel];
		CHECKPOINTER(temp);
		for(int i=0;i<mglevel;i++)
		{
			temp[i]=new int [controllableunitnum+energystoragenum+loadnum+renewableenergynum];
			CHECKPOINTER(temp[i]);
		}
		int inorder;
		for (int i=0;i<mglevel/2.0;i++)
		{
			for (int i1=0;i1<controllableunitnum;i1++)
			{
				inorder=Controllableunitdata[i1].levelIdentifier[i];
				Controllableunitdata[i1].levelIdentifier[i]=Controllableunitdata[i1].levelIdentifier[mglevel-1-i];
				Controllableunitdata[i1].levelIdentifier[mglevel-1-i]=inorder;
			}
			for (int i1=0;i1<energystoragenum;i1++)
			{
				inorder=Energystoragedata[i1].levelIdentifier[i];
				Energystoragedata[i1].levelIdentifier[i]=Energystoragedata[i1].levelIdentifier[mglevel-1-i];
				Energystoragedata[i1].levelIdentifier[mglevel-1-i]=inorder;
			}
			for (int i1=0;i1<loadnum;i1++)
			{
				inorder=Loaddata[i1].levelIdentifier[i];
				Loaddata[i1].levelIdentifier[i]=Loaddata[i1].levelIdentifier[mglevel-1-i];
				Loaddata[i1].levelIdentifier[mglevel-1-i]=inorder;
			}
			for (int i1=0;i1<renewableenergynum;i1++)
			{
				inorder=Renewableenergydata[i1].levelIdentifier[i];
				Renewableenergydata[i1].levelIdentifier[i]=Renewableenergydata[i1].levelIdentifier[mglevel-1-i];
				Renewableenergydata[i1].levelIdentifier[mglevel-1-i]=inorder;
			}
		}
		for (int i=0;i<mglevel;i++)
		{
			for (int i1=0;i1<controllableunitnum;i1++)
			{
				temp[i][i1]=Controllableunitdata[i1].levelIdentifier[i];
			}
			for (int i1=0;i1<energystoragenum;i1++)
			{
				temp[i][i1+controllableunitnum]=Energystoragedata[i1].levelIdentifier[i];
			}
			for (int i1=0;i1<loadnum;i1++)
			{
				temp[i][i1+controllableunitnum+energystoragenum]=Loaddata[i1].levelIdentifier[i];
			}
			for (int i1=0;i1<renewableenergynum;i1++)
			{
				temp[i][i1+controllableunitnum+energystoragenum+loadnum]=Renewableenergydata[i1].levelIdentifier[i];
			}
		}
		int ix=0;
		int iy=0;
		for (int i=0;i<mglevel;i++)
		{
			ix=0;
			for (int i1=0;i1<controllableunitnum+energystoragenum+loadnum+renewableenergynum;i1++)
			{
				if (i1==0)
				{
					if (temp[i][i1]>0)
					{
						Levelnumtoreal[i][ix]=temp[i][i1];
						ix++;
					}
				}
				else
				{
					iy=1;
					for (int i2=0;i2<i1;i2++)
					{
						if (temp[i][i1]<=0||temp[i][i1]==temp[i][i2])
						{
							iy=0;
							break;
						}
					}
					if (iy>0)
					{
						Levelnumtoreal[i][ix]=temp[i][i1];
						ix++;
					}
				}

			}
		}

		/*for (int i=0;i<mglevel;i++)
		{
			for (int i1=0;i1<controllableunitnum+energystoragenum+loadnum+renewableenergynum;i1++)
			{
				cout<<temp[i][i1]<<" ";
			}
			cout<<endl;
		}*/
	for(int I=0;I<virtualloadnum;I++)
	{
		for(int Ix=0;Ix<mglevel;Ix++)
		{
			Virtualloaddata[I].levelIdentifier[Ix]=0;
		}
	}
	int I=0;
	//Virtualloaddata[0].levelIdentifier[0]=0;
	for(int Ix=1;Ix<mglevel;Ix++)
	{
		for(int Iy=0;Iy<mglevelnum[Ix];Iy++)
		{
			Virtualloaddata[I].levelIdentifier[Ix]=Levelnumtoreal[Ix][Iy];
			//cout<<Virtualloaddata[I].levelIdentifier[Ix]<<" ";
			I++;
		}
		//cout<<endl;
	}
	for(int I=0;I<virtualloadnum;I++)
	{
		for(int Ix=0;Ix<mglevel;Ix++)
		{
			if(Virtualloaddata[I].levelIdentifier[Ix]>0)
			{
				for (int i1=0;i1<controllableunitnum+energystoragenum+loadnum+renewableenergynum;i1++)
				{
					if(Virtualloaddata[I].levelIdentifier[Ix]==temp[Ix][i1])
					{
						for(int k=0;k<Ix;k++)
						{
							Virtualloaddata[I].levelIdentifier[k]=temp[k][i1];
						}
						break;
					}
				}
			}
			//cout<<Virtualloaddata[I].levelIdentifier[Ix]<<" ";
		}//cout<<endl;
	}

		for(int i=0;i<mglevel;i++)
		{
			delete[] temp[i];
		}
		delete[] temp;
		/*for (int i=0;i<mglevel;i++)
		{
			for (int i1=0;i1<mglevelnum[i]+1;i1++)
			{
				cout<<Levelnumtoreal[i][i1]<<" ";
			}
			cout<<endl;
		}*/

}
void SCHEDULE::inputdynamicdata()
{
	int temp;
	ifstream fin1("renewable_energy_dynamic.txt");
	if (!fin1)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fin1.ignore(1024,'*');
	for(int i=0;i<renewableenergynum;i++)
	{
		fin1>>temp;
		fin1>>Renewableenergydata[temp-1].ID32;
		for(int j=0;j<Ttotal;j++)
		{
			fin1>>Renewableenergydata[temp-1].PnewHttotal[j];
		}
	}
	fin1.close();
	ifstream fin2("reserve_dynamic.txt");
	if (!fin2)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fin2.ignore(1024,'*');
	fin2>>Griddata.gridnum;
	for(int i=0;i<Ttotal;i++)
	{
		fin2>>Prttotal[i];
	}
	fin2.close();
	ifstream fin3("load_dynamic.txt");
	if (!fin3)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fin3.ignore(1024,'*');
	for(int j=0;j<loadnum;j++)
	{
		fin3>>temp;
		fin3>>Loaddata[temp-1].ID32;
		for(int i=0;i<Ttotal;i++)
		{
			fin3>>Loaddata[temp-1].Pdttotal[i];
		}
	}
	fin3.close();
	ifstream fin4("electricity_price.txt");
	if (!fin4)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fin4.ignore(1024,'*');
	for(int i=0;i<Ttotal;i++)
	{
		fin4>>Griddata.Buytotal[i];
	}
	//fin4.ignore(1024,'*');
	for(int i=0;i<Ttotal;i++)
	{
		fin4>>Griddata.Selltotal[i];
	}
	fin4.close();

	for(int j=0;j<Ttotal;j++)
	{
		Pd1ttotal[j]=0;
		for(int i=0;i<loadnum;i++)
		{
			Pd1ttotal[j]+=Loaddata[i].Pdttotal[j];
		}
	}

	totaltolay1_data();
}

void SCHEDULE::inputinitdata()
{
	inputfoundationdata();
	totaltolay1_T();
	initc();
	inputstaticdata();
	inputdefaultvalue();
	defaultvalue();

	for(int i=0;i<controllableunitnum;i++)
	{
		if(Controllableunitdata[i].curve==1)
		{
			consumptioncurve(i);
		}
	}
	for(int i=0;i<controllableunitnum;i++)
	{
		for(int j=0;j<node;j++)
		{
			Controllableunitdata[i].Pi[j]=Controllableunitdata[i].Pi[j];
			Controllableunitdata[i].ci[j]=Controllableunitdata[i].ci[j]*Controllableunitdata[i].fuelcost;
		}
	}
	/*energystoragenumga=0;
	for(int i=0;i<energystoragenum;i++)
	{
		if((Energystoragedata[i].type/1000)%10==1)
		{
			energystoragenumga++;
		}
	}*/
	//ga.initc(controllableunitnum,energystoragenumga,energystoragenum,T,loadnum);////
}
void SCHEDULE::inputdecisiondata()
{
	ifstream fin("decisiondata.txt");
	if (!fin)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fin.ignore(1024,'*');
	fin>>gridislanddecision;
	//fin.ignore(1024,'*');
	fin>>modeldecision;
	fin>>updatelossdecision;
	fin.close();
}
void SCHEDULE::inputdefaultvalue()
{
	ifstream fin("diagram.txt");
	if (!fin)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	fin.ignore(1024,'*');
	fin>>nodedefault>>pollutionnumdefault;
	fin.ignore(1024,'*');
	fin>>controllabletypenum>>storagetypenum>>renewabletypemun;

	Controllableunitdatadefault=new ControllableUnitDataDefault[controllabletypenum];
	CHECKPOINTER(Controllableunitdatadefault);
	for(int i=0;i<controllabletypenum;i++)
	{
		Controllableunitdatadefault[i].Q=new double[pollutionnumdefault];
		CHECKPOINTER(Controllableunitdatadefault[i].Q);
	}
	Energystoragedatadefault=new EnergyStorageDataDefault[storagetypenum];
	CHECKPOINTER(Energystoragedatadefault);
	Renewableenergydatadefault=new RenewableEnergyDataDefault[renewabletypemun];
	CHECKPOINTER(Renewableenergydatadefault);
	Vdefault=new double [pollutionnumdefault];
	CHECKPOINTER(Vdefault);
	Qgriddefault=new double [pollutionnumdefault];
	CHECKPOINTER(Qgriddefault);

	fin.ignore(1024,'*');
	for(int i=0;i<controllabletypenum;i++)
	{
		fin>>Controllableunitdatadefault[i].type>>Controllableunitdatadefault[i].name>>Controllableunitdatadefault[i].a>>Controllableunitdatadefault[i].b>>Controllableunitdatadefault[i].c>>Controllableunitdatadefault[i].d
			>>Controllableunitdatadefault[i].fuelcost>>Controllableunitdatadefault[i].Shi>>Controllableunitdatadefault[i].deltiup>>Controllableunitdatadefault[i].deltidown
			>>Controllableunitdatadefault[i].RHi>>Controllableunitdatadefault[i].MOTi>>Controllableunitdatadefault[i].MDTi>>Controllableunitdatadefault[i].COM>>Controllableunitdatadefault[i].Invest
			>>Controllableunitdatadefault[i].year>>Controllableunitdatadefault[i].k>>Controllableunitdatadefault[i].Ramp;
		for(int j=0;j<pollutionnum;j++)
		{
			fin>>Controllableunitdatadefault[i].Q[j];
		}
	}
	fin.ignore(1024,'*');
	for(int i=0;i<storagetypenum;i++)
	{
		fin>>Energystoragedatadefault[i].type>>Energystoragedatadefault[i].name>>Energystoragedatadefault[i].PgLk>>Energystoragedatadefault[i].PpLk>>Energystoragedatadefault[i].yitag>>Energystoragedatadefault[i].yitap>>Energystoragedatadefault[i].Wk;
		fin>>Energystoragedatadefault[i].Invest>>Energystoragedatadefault[i].MaintenanceCost>>Energystoragedatadefault[i].year>>Energystoragedatadefault[i].cyclenum;
		fin>>Energystoragedatadefault[i].VHkgridmargin>>Energystoragedatadefault[i].VLkgridmargin>>Energystoragedatadefault[i].VHkislandmargin>>Energystoragedatadefault[i].VLkislandmargin;
		fin>>Energystoragedatadefault[i].VHkgridMARGINLIMIT>>Energystoragedatadefault[i].VLkgridMARGINLIMIT>>Energystoragedatadefault[i].VHkislandMARGINLIMIT>>Energystoragedatadefault[i].VLkislandMARGINLIMIT;
		//fin>>Energystoragedatadefault[i].MARGINLIMIT;
	}
	fin.ignore(1024,'*');
	for(int i=0;i<renewabletypemun;i++)
	{
		fin>>Renewableenergydatadefault[i].type>>Renewableenergydatadefault[i].name>>Renewableenergydatadefault[i].error;
	}
	fin.ignore(1024,'*');
	for(int i=0;i<pollutionnumdefault;i++)
	{
		fin>>Qgriddefault[i];
	}
	fin.ignore(1024,'*');
	for(int i=0;i<pollutionnumdefault;i++)
	{
		fin>>Vdefault[i];
	}
	fin.ignore(1024,'*');
	fin>>Griddatadefault.Pbuymax>>Griddatadefault.Psellmax;
	fin>>Griddatadefault.Ramp;
	fin.ignore(1024,'*');
	fin>>Pcutleveldefault>>Pcutcostdefault;
	fin.ignore(1024,'*');
	fin>>Loaddatadefault.name>>Loaddatadefault.error>>Loaddatadefault.level;

	fin.close();
}
void SCHEDULE::defaultvalue()
{
	ESSENTIAL(controllableunitnum);NON_ESSENTIAL(node,nodedefault);ESSENTIAL(energystoragenum);ESSENTIAL(renewableenergynum);ESSENTIAL(loadnum);ESSENTIAL(T);NON_ESSENTIAL(pollutionnum,pollutionnumdefault);
	for(int i=0;i<controllableunitnum;i++)
	{
		for(int i1=0;i1<controllabletypenum;i1++)
		{
			if(Controllableunitdata[i].type==Controllableunitdatadefault[i1].type)
			{
							NON_ESSENTIALCHR(Controllableunitdata[i].name,Controllableunitdatadefault[i1].name);
				ESSENTIAL(Controllableunitdata[i].Identifier);ESSENTIAL(Controllableunitdata[i].type);ESSENTIAL(Controllableunitdata[i].curve);
				if(Controllableunitdata[i].curve==1)
				{
					NON_ESSENTIAL(Controllableunitdata[i].a,Controllableunitdatadefault[i1].a);NON_ESSENTIAL(Controllableunitdata[i].b,Controllableunitdatadefault[i1].b);NON_ESSENTIAL(Controllableunitdata[i].c,Controllableunitdatadefault[i1].c);NON_ESSENTIAL(Controllableunitdata[i].d,Controllableunitdatadefault[i1].d);
				}
				else
				{
					for(int j=0;j<node;j++)
					{
						ESSENTIAL(Controllableunitdata[i].Pi[j]);
					}
					for(int j=0;j<node;j++)
					{
						ESSENTIAL(Controllableunitdata[i].ci[j]);
					}
				}
				NON_ESSENTIAL(Controllableunitdata[i].fuelcost,Controllableunitdatadefault[i1].fuelcost);NON_ESSENTIAL(Controllableunitdata[i].Shi,Controllableunitdatadefault[i1].Shi);NON_ESSENTIAL(Controllableunitdata[i].deltiup,Controllableunitdatadefault[i1].deltiup);NON_ESSENTIAL(Controllableunitdata[i].deltidown,Controllableunitdatadefault[i1].deltidown);ESSENTIAL(Controllableunitdata[i].PHi);ESSENTIAL(Controllableunitdata[i].PLi);
				NON_ESSENTIAL(Controllableunitdata[i].RHi,Controllableunitdatadefault[i1].RHi);NON_ESSENTIAL(Controllableunitdata[i].MOTi,Controllableunitdatadefault[i1].MOTi);NON_ESSENTIAL(Controllableunitdata[i].MDTi,Controllableunitdatadefault[i1].MDTi);NON_ESSENTIAL(Controllableunitdata[i].COM,Controllableunitdatadefault[i1].COM);
				NON_ESSENTIAL(Controllableunitdata[i].Invest,Controllableunitdatadefault[i1].Invest);NON_ESSENTIAL(Controllableunitdata[i].year,Controllableunitdatadefault[i1].year);NON_ESSENTIAL(Controllableunitdata[i].k,Controllableunitdatadefault[i1].k);NON_ESSENTIAL(Controllableunitdata[i].Ramp,Controllableunitdatadefault[i1].Ramp);
				for(int j=0;j<pollutionnum;j++)
				{
					NON_ESSENTIAL(Controllableunitdata[i].Q[j],Controllableunitdatadefault[i1].Q[j]);
				}
			}
		}
	}

	for(int i=0;i<energystoragenum;i++)
	{
		for(int i1=0;i1<storagetypenum;i1++)
		{
			if(Energystoragedata[i].type==Energystoragedatadefault[i1].type)
			{
								NON_ESSENTIALCHR(Energystoragedata[i].name,Energystoragedatadefault[i1].name);
				ESSENTIAL(Energystoragedata[i].Identifier);ESSENTIAL(Energystoragedata[i].type);ESSENTIAL(Energystoragedata[i].PgHk);NON_ESSENTIAL(Energystoragedata[i].PgLk,Energystoragedatadefault[i1].PgLk);ESSENTIAL(Energystoragedata[i].PpHk);NON_ESSENTIAL(Energystoragedata[i].PpLk,Energystoragedatadefault[i1].PpLk);
				ESSENTIAL(Energystoragedata[i].VHk);ESSENTIAL(Energystoragedata[i].VLk);NON_ESSENTIAL(Energystoragedata[i].yitag,Energystoragedatadefault[i1].yitag);NON_ESSENTIAL(Energystoragedata[i].yitap,Energystoragedatadefault[i1].yitap);NON_ESSENTIAL(Energystoragedata[i].Wk,Energystoragedatadefault[i1].Wk);
				NON_ESSENTIAL(Energystoragedata[i].Invest,Energystoragedatadefault[i1].Invest);NON_ESSENTIAL(Energystoragedata[i].MaintenanceCost,Energystoragedatadefault[i1].MaintenanceCost);NON_ESSENTIAL(Energystoragedata[i].year,Energystoragedatadefault[i1].year);NON_ESSENTIAL(Energystoragedata[i].cyclenum,Energystoragedatadefault[i1].cyclenum);
				NON_ESSENTIAL(Energystoragedata[i].VHkgridmargin,Energystoragedatadefault[i1].VHkgridmargin);NON_ESSENTIAL(Energystoragedata[i].VLkgridmargin,Energystoragedatadefault[i1].VLkgridmargin);NON_ESSENTIAL(Energystoragedata[i].VHkislandmargin,Energystoragedatadefault[i1].VHkislandmargin);NON_ESSENTIAL(Energystoragedata[i].VLkislandmargin,Energystoragedatadefault[i1].VLkislandmargin);
				NON_ESSENTIAL(Energystoragedata[i].VHkgridMARGINLIMIT,Energystoragedatadefault[i1].VHkgridMARGINLIMIT);NON_ESSENTIAL(Energystoragedata[i].VLkgridMARGINLIMIT,Energystoragedatadefault[i1].VLkgridMARGINLIMIT);NON_ESSENTIAL(Energystoragedata[i].VHkislandMARGINLIMIT,Energystoragedatadefault[i1].VHkislandMARGINLIMIT);NON_ESSENTIAL(Energystoragedata[i].VLkislandMARGINLIMIT,Energystoragedatadefault[i1].VLkislandMARGINLIMIT);
				//NON_ESSENTIAL(Energystoragedata[i].MARGINLIMIT,Energystoragedatadefault[i1].MARGINLIMIT);
			}
		}
	}

	for(int i=0;i<pollutionnum;i++)
	{
		NON_ESSENTIAL(Qgrid[i],Qgriddefault[i]);
	}
	for(int i=0;i<pollutionnum;i++)
	{
		NON_ESSENTIAL(V[i],Vdefault[i]);
	}
	ESSENTIAL(Griddata.Pbuymax);ESSENTIAL(Griddata.Psellmax);NON_ESSENTIAL(Griddata.Ramp,Griddatadefault.Ramp);

	for(int i=0;i<4;i++)
	{
		ESSENTIAL(Pcutlevel[i]);NON_ESSENTIAL(Pcutcost[i],Pcutcostdefault);
	}
	for(int j=0;j<loadnum;j++)
	{
				NON_ESSENTIALCHR(Loaddata[j].name,Loaddatadefault.name);
		ESSENTIAL(Loaddata[j].Identifier);NON_ESSENTIAL(Loaddata[j].error,Loaddatadefault.error);NON_ESSENTIAL(Loaddata[j].level,Loaddatadefault.level);
	}

	for(int i=0;i<renewableenergynum;i++)
	{
		for(int i1=0;i1<renewabletypemun;i1++)
		{
			if(Renewableenergydata[i].type==Renewableenergydatadefault[i1].type)
			{
								NON_ESSENTIALCHR(Renewableenergydata[i].name,Renewableenergydatadefault[i1].name);
				ESSENTIAL(Renewableenergydata[i].Identifier);ESSENTIAL(Renewableenergydata[i].type);NON_ESSENTIAL(Renewableenergydata[i].error,Renewableenergydatadefault[i1].error);
			}
		}
	}
}
void SCHEDULE::totaltolay1_T()
{
	if(Ttotal<24)
	{
		T=Ttotal;
		Tlay2=1;
	}
	else
	{
		T=24;
		Tlay2=Ttotal/24;
	}
}
void SCHEDULE::totaltolay1_data()
{
	for(int i=0;i<renewableenergynum;i++)
	{
		for(int j=0;j<T;j++)
		{
			//Renewableenergydata[i].PnewHt[j]=Renewableenergydata[i].PnewHttotal[j*Tlay2+Tlay2-1];
			Renewableenergydata[i].PnewHt[j]=0;
			for(int j2=0;j2<Tlay2;j2++)
			{
				Renewableenergydata[i].PnewHt[j]+=Renewableenergydata[i].PnewHttotal[j*Tlay2+j2];
			}
			Renewableenergydata[i].PnewHt[j]=Renewableenergydata[i].PnewHt[j]/Tlay2;
		}
	}
	for(int j=0;j<T;j++)
	{
		//Prt[j]=Prttotal[j*Tlay2+Tlay2-1];
		Prt[j]=0;
		for(int j2=0;j2<Tlay2;j2++)
		{
			Prt[j]+=Prttotal[j*Tlay2+j2];
		}
		Prt[j]=Prt[j]/Tlay2;
	}
	for(int i=0;i<loadnum;i++)
	{
		for(int j=0;j<T;j++)
		{
			//Loaddata[i].Pdt[j]=Loaddata[i].Pdttotal[j*Tlay2+Tlay2-1];
			Loaddata[i].Pdt[j]=0;
			for(int j2=0;j2<Tlay2;j2++)
			{
				Loaddata[i].Pdt[j]+=Loaddata[i].Pdttotal[j*Tlay2+j2];
			}
			Loaddata[i].Pdt[j]=Loaddata[i].Pdt[j]/Tlay2;
		}
	}
	for(int j=0;j<T;j++)
	{
		//Griddata.Buy[j]=Griddata.Buytotal[j*Tlay2+Tlay2-1];
		Griddata.Buy[j]=0;
		for(int j2=0;j2<Tlay2;j2++)
		{
			Griddata.Buy[j]+=Griddata.Buytotal[j*Tlay2+j2];
		}
		Griddata.Buy[j]=Griddata.Buy[j]/Tlay2;
	}
	for(int j=0;j<T;j++)
	{
		//Griddata.Sell[j]=Griddata.Selltotal[j*Tlay2+Tlay2-1];
		Griddata.Sell[j]=0;
		for(int j2=0;j2<Tlay2;j2++)
		{
			Griddata.Sell[j]+=Griddata.Selltotal[j*Tlay2+j2];
		}
		Griddata.Sell[j]=Griddata.Sell[j]/Tlay2;
	}
	for(int j=0;j<T;j++)
	{
		//Griddata.VirtualBuy[j]=Griddata.VirtualBuytotal[j*Tlay2+Tlay2-1];
		Griddata.VirtualBuy[j]=0;
		for(int j2=0;j2<Tlay2;j2++)
		{
			Griddata.VirtualBuy[j]+=Griddata.VirtualBuytotal[j*Tlay2+j2];
		}
		Griddata.VirtualBuy[j]=Griddata.VirtualBuy[j]/Tlay2;
	}
	for(int j=0;j<T;j++)
	{
		//Griddata.VirtualSell[j]=Griddata.VirtualSelltotal[j*Tlay2+Tlay2-1];
		Griddata.VirtualSell[j]=0;
		for(int j2=0;j2<Tlay2;j2++)
		{
			Griddata.VirtualSell[j]+=Griddata.VirtualSelltotal[j*Tlay2+j2];
		}
		Griddata.VirtualSell[j]=Griddata.VirtualSell[j]/Tlay2;
	}

	for(int j=0;j<T;j++)
	{
		//Pd1t[j]=Pd1ttotal[j*Tlay2+Tlay2-1];
		Pd1t[j]=0;
		for(int j2=0;j2<Tlay2;j2++)
		{
			Pd1t[j]+=Pd1ttotal[j*Tlay2+j2];
		}
		Pd1t[j]=Pd1t[j]/Tlay2;
	}
}
void SCHEDULE::totaltolay2_data(int Ttemp,int xlay2)
{
	for(int i=0;i<renewableenergynum;i++)
	{
		for(int j=0;j<Ttemp;j++)
		{
			Renewableenergydata[i].PnewHtlay2[j]=Renewableenergydata[i].PnewHttotal[Ttemp*xlay2+j];
		}
	}
	for(int j=0;j<Ttemp;j++)
	{
		Prtlay2[j]=Prttotal[Ttemp*xlay2+j];
	}
	for(int i=0;i<loadnum;i++)
	{
		for(int j=0;j<Ttemp;j++)
		{
			Loaddata[i].Pdtlay2[j]=Loaddata[i].Pdttotal[Ttemp*xlay2+j];
		}
	}
	for(int j=0;j<Ttemp;j++)
	{
		Griddata.Buylay2[j]=Griddata.Buytotal[Ttemp*xlay2+j];
	}
	for(int j=0;j<Ttemp;j++)
	{
		Griddata.Selllay2[j]=Griddata.Selltotal[Ttemp*xlay2+j];
	}
	for(int j=0;j<Ttemp;j++)
	{
		Griddata.VirtualBuylay2[j]=Griddata.VirtualBuytotal[Ttemp*xlay2+j];
	}
	for(int j=0;j<Ttemp;j++)
	{
		Griddata.VirtualSelllay2[j]=Griddata.VirtualSelltotal[Ttemp*xlay2+j];
	}

	for(int j=0;j<Ttemp;j++)
	{
		Pd1tlay2[j]=Pd1ttotal[Ttemp*xlay2+j];
	}
	for(int j=0;j<Ttemp;j++)
	{
		errorvaluelay2[j]=errorvaluetotal[Ttemp*xlay2+j];
	}
}
/*
void SCHEDULE::totaltolay2_data_level(int Ttemp,int xlay2)
{
	for(int i=0;i<renewableenergynum;i++)
	{
		for(int j=0;j<Ttemp;j++)
		{
			Renewableenergydata[i].PnewHtlay2[j]=Renewableenergydata[i].PnewHttotal[Ttemp*xlay2+j];
		}
	}
	for(int j=0;j<Ttemp;j++)
	{
		Prtlay2[j]=Prttotal[Ttemp*xlay2+j];
	}
	for(int i=0;i<loadnum;i++)
	{
		for(int j=0;j<Ttemp;j++)
		{
			Loaddata[i].Pdtlay2[j]=Loaddata[i].Pdttotal[Ttemp*xlay2+j];
		}
	}
	for(int j=0;j<Ttemp;j++)
	{
		Griddata.Buylay2[j]=Griddata.Buytotal[Ttemp*xlay2+j];
	}
	for(int j=0;j<Ttemp;j++)
	{
		Griddata.Selllay2[j]=Griddata.Selltotal[Ttemp*xlay2+j];
	}
	for(int j=0;j<Ttemp;j++)
	{
		Griddata.VirtualBuylay2[j]=Griddata.VirtualBuytotal[Ttemp*xlay2+j];
	}
	for(int j=0;j<Ttemp;j++)
	{
		Griddata.VirtualSelllay2[j]=Griddata.VirtualSelltotal[Ttemp*xlay2+j];
	}

	for(int j=0;j<Ttemp;j++)
	{
		Pd1tlay2[j]=Pd1ttotal[Ttemp*xlay2+j];
	}
	for(int i=0;i<virtualloadnum;i++)
	{
		for(int J=0;J<Ttemp;J++)
		{
			Virtualloaddata[i].Pdtlay2[J]=Virtualloaddata[i].Pdttotal[Ttemp*xlay2+J];
		}
	}
}*/
SCHEDULE::~SCHEDULE()
{

	for(int i=0;i<controllableunitnum;i++)
	{
		delete[] Controllableunitdata[i].Pi;
		delete[] Controllableunitdata[i].ci;
		delete[] Controllableunitdata[i].Q;
		delete[] Controllableunitdata[i].Uit;
		delete[] Controllableunitdata[i].openit;
		delete[] Controllableunitdata[i].closeit;
		delete[] Controllableunitdata[i].Pit;
		delete[] Controllableunitdata[i].Rit;
		delete[] Controllableunitdata[i].Sit;
		delete[] Controllableunitdata[i].Cit;
		//lay2
		delete[] Controllableunitdata[i].Uitlay2;
		delete[] Controllableunitdata[i].Pitlay2;
		delete[] Controllableunitdata[i].Sitlay2;
		delete[] Controllableunitdata[i].Citlay2;
		//total
		delete[] Controllableunitdata[i].Pittotal;
		//
		delete[] Controllableunitdata[i].levelIdentifier;
		delete[] Controllableunitdata[i].CostC;
		delete[] Controllableunitdata[i].CostS;
		delete[] Controllableunitdata[i].CostCOM;
	}
	delete[] Controllableunitdata;
	for(int i=0;i<energystoragenum;i++)
	{
		delete[] Energystoragedata[i].Ugkt;
		delete[] Energystoragedata[i].Upkt;
		delete[] Energystoragedata[i].Pkt;
		delete[] Energystoragedata[i].Vkt;
		delete[] Energystoragedata[i].Pgkt;
		delete[] Energystoragedata[i].Ppkt;
		delete[] Energystoragedata[i].Pdhkt;
		delete[] Energystoragedata[i].Pchkt;
		delete[] Energystoragedata[i].Rkt;
		delete[] Energystoragedata[i].egkt;
		delete[] Energystoragedata[i].epkt;
		//lay2
		delete[] Energystoragedata[i].Pktlay2;
		delete[] Energystoragedata[i].Vktlay2;
		delete[] Energystoragedata[i].Pgktlay2;
		delete[] Energystoragedata[i].Ppktlay2;
		//total
		delete[] Energystoragedata[i].Pkttotal;
		delete[] Energystoragedata[i].Vkttotal;
		//
		delete[] Energystoragedata[i].levelIdentifier;

		delete[] Energystoragedata[i].VLksetschedule;
		delete[] Energystoragedata[i].VHksetschedule;
		delete[] Energystoragedata[i].VLksetschedulelay2;
		delete[] Energystoragedata[i].VHksetschedulelay2;
		delete[] Energystoragedata[i].CostC;
	}
	delete[] Energystoragedata;

	for(int i=0;i<renewableenergynum;i++)
	{
		delete[] Renewableenergydata[i].PnewHt;
		delete[] Renewableenergydata[i].PnewHttemp;
		delete[] Renewableenergydata[i].Pnewt;
		//total
		delete[] Renewableenergydata[i].PnewHttotal;
		delete[] Renewableenergydata[i].Pnewttotal;
		//lay2
		delete[] Renewableenergydata[i].PnewHtlay2;
		delete[] Renewableenergydata[i].Pnewtlay2;
		//
		delete[] Renewableenergydata[i].levelIdentifier;
	}
	delete[] Renewableenergydata;
	delete[] Prt;
	delete[] Pd1t;
	//total
	delete[] Prttotal;
	delete[] Pd1ttotal;
	//lay2
	delete[] Prtlay2;
	delete[] Pd1tlay2;

	delete[] Griddata.Buy;
	delete[] Griddata.Sell;
	delete[] Griddata.Buytemp;
	delete[] Griddata.Selltemp;
	delete[] Griddata.Ubuyt;
	delete[] Griddata.Usellt;
	delete[] Griddata.Pbuyt;
	delete[] Griddata.Psellt;
	delete[] Griddata.VirtualBuy;
	delete[] Griddata.VirtualSell;
	//total
	delete[] Griddata.Buytotal;
	delete[] Griddata.Selltotal;
	delete[] Griddata.VirtualBuytotal;
	delete[] Griddata.VirtualSelltotal;
	delete[] Griddata.Pbuyttotal;
	delete[] Griddata.Psellttotal;
	//lay2
	delete[] Griddata.Buylay2;
	delete[] Griddata.Selllay2;
	delete[] Griddata.VirtualBuylay2;
	delete[] Griddata.VirtualSelllay2;
	delete[] Griddata.Pbuytlay2;
	delete[] Griddata.Pselltlay2;
	delete[] Griddata.CostBS;

	for(int i=0;i<energystoragenum;i++)
	{
		delete[] Pktout[i];
		delete[] Pdhktout[i];
		delete[] Pchktout[i];
	}
	delete[] Pktout;
	delete[] Pdhktout;
	delete[] Pchktout;
	for(int i=0;i<controllableunitnum;i++)
	{
		delete[] Pitout[i];
		delete[] Citout[i];
		delete[] Sitout[i];
	}
	delete[] Citout;
	delete[] Sitout;
	delete[] Pitout;
	for(int i=0;i<renewableenergynum;i++)
	{
		delete[] Pnewtout[i];
	}
	delete[] Pnewtout;
	delete[] Pdtout;
	for(int i=0;i<controllableunitnum;i++)
	{
		delete[] Uitset[i];
	}
	delete[] Uitset;
	for(int i=0;i<loadnum;i++)
	{
		delete[] Ucutxset[i];
	}
	delete[] Ucutxset;
	for(int i=0;i<energystoragenum;i++)
	{
		delete[] Vsoet[i];

	}
	delete[] Vsoet;

	delete[] errorvalue;
	delete[] errorvaluetotal;
	delete[] errorvaluelay2;
	delete[] V;
	delete[] Qgrid;
	//	delete[] CostkWh;
	for(int i=0;i<loadnum;i++)
	{
		delete[] Loaddata[i].Pdt;
		delete[] Loaddata[i].Ucutx;
		//		delete[] Loaddata[i].Pcutxt;
		//		delete[] Loaddata[i].Udtdeltp;
		//		delete[] Loaddata[i].Udtdeltm;
		//		delete[] Loaddata[i].Pdtdeltp;
		//		delete[] Loaddata[i].Pdtdeltm;
		delete[] Loaddata[i].Scutx;

		//total
		delete[] Loaddata[i].Pdttotal;
		delete[] Loaddata[i].Ucutxtotal;
		//lay2
		delete[] Loaddata[i].Pdtlay2;
		delete[] Loaddata[i].Ucutxlay2;
		//
		delete[] Loaddata[i].levelIdentifier;
		delete[] Loaddata[i].CostCut;
	}
	delete[] Loaddata;
	delete[] Pselltout;
	delete[] Pbuytout;

	//default
	for(int i=0;i<controllabletypenum;i++)
	{
		delete[] Controllableunitdatadefault[i].Q;
	}
	delete[] Controllableunitdatadefault;
	delete[] Energystoragedatadefault;
	delete[] Renewableenergydatadefault;
	delete[] Vdefault;
	delete[] Qgriddefault;
	delete[] Pcutxt;
	/*for(int i=0;i<controllableunitnum+energystoragenum+1;i++)
	{
		delete[] Crateall[i];
	}
	delete[] Crateall;
	delete[] Crateall1;
	delete[] Crateall1order;
	delete[] Crateall1order2;
*/
	delete[] mglevelnum;

	for(int i=0;i<virtualloadnum;i++)
	{
		delete[] Virtualloaddata[i].Pdt;
		delete[] Virtualloaddata[i].Ucutx;
		//total
		delete[] Virtualloaddata[i].Pdttotal;
		delete[] Virtualloaddata[i].Ucutxtotal;
		//lay2
		delete[] Virtualloaddata[i].Pdtlay2;
		delete[] Virtualloaddata[i].Ucutxlay2;
		//
		delete[] Virtualloaddata[i].levelIdentifier;
	}
	delete[] Virtualloaddata;
	//ajust
	/*for(int i=0;i<controllableunitnum;i++)
	{
	delete[] Crateall_unit[i];
	}
	delete[] Crateall_unit;
	delete[] Alllevel_unit;
	delete[] Alllevelorder_unit;*/
	delete[] LevelID32;
	delete[] LevelIdentify;
	delete[] LevelIdentifynext;
	for(int i=0;i<mglevel;i++)
	{
		delete[] Levelnumtoreal[i];
	}
	delete[] Levelnumtoreal;
	delete[] Levelclassify;
}
void SCHEDULE::consumptioncurve(int i)
{
	double deltpi=(Controllableunitdata[i].PHi-Controllableunitdata[i].PLi)/(node-1);
	Controllableunitdata[i].Pi[0]=Controllableunitdata[i].PLi;
	for(int j=0;j<node;j++)
	{
		Controllableunitdata[i].ci[j]=Controllableunitdata[i].a+Controllableunitdata[i].b*Controllableunitdata[i].Pi[j]+Controllableunitdata[i].c*Controllableunitdata[i].Pi[j]*Controllableunitdata[i].Pi[j]+Controllableunitdata[i].d*Controllableunitdata[i].Pi[j]*Controllableunitdata[i].Pi[j]*Controllableunitdata[i].Pi[j];
		if(j<node-1)
		{
			Controllableunitdata[i].Pi[j+1]=Controllableunitdata[i].Pi[j]+deltpi;
		}
	}
}
void SCHEDULE::cyclecost()
{
	for(int i=0;i<controllableunitnum;i++)
	{
		Controllableunitdata[i].CDP=Controllableunitdata[i].Invest/(Controllableunitdata[i].year*Controllableunitdata[i].k);
	}
	for(int i=0;i<controllableunitnum;i++)
	{
		Controllableunitdata[i].CE=0;
		for(int j=0;j<pollutionnum;j++)
		{
			Controllableunitdata[i].CE +=V[j]*Controllableunitdata[i].Q[j];
		}
	}
	CEgrid=0;
	for(int j=0;j<pollutionnum;j++)
	{
		CEgrid +=V[j]*Qgrid[j];
	}

	for(int i=0;i<energystoragenum;i++)
	{
		Energystoragedata[i].CostkWh=(Energystoragedata[i].Invest*Energystoragedata[i].VHk+Energystoragedata[i].MaintenanceCost*Energystoragedata[i].VHk)/(2*Energystoragedata[i].cyclenum*(Energystoragedata[i].VHk-Energystoragedata[i].VLk));
	}
}
void SCHEDULE::errorcalculate()
{
	errorlength=6;
	for(int J=0;J<Ttotal;J++)
	{
		errorvaluetotal[J]=0;
		if(J<=Ttotal-errorlength)
		{
			for(int I=0;I<loadnum;I++)
			{
				for(int J1=J;J1<J+errorlength;J1++)
				{
					errorvaluetotal[J] +=Loaddata[I].Pdttotal[J1]*Loaddata[I].error*1.0/Tlay2;
				}
			}
			for(int I=0;I<renewableenergynum;I++)
			{
				for(int J1=J;J1<J+errorlength;J1++)
				{
					errorvaluetotal[J] +=Renewableenergydata[I].error*Renewableenergydata[I].PnewHttotal[J1]*1.0/Tlay2;
				}
			}
		}
		else
		{
			for(int I=0;I<loadnum;I++)
			{
				for(int J1=J;J1<Ttotal;J1++)
				{
					errorvaluetotal[J] +=Loaddata[I].Pdttotal[J1]*Loaddata[I].error*1.0/Tlay2;
				}
				for(int J1=0;J1<errorlength-(Ttotal-J);J1++)
				{
					errorvaluetotal[J] +=Loaddata[I].Pdttotal[J1]*Loaddata[I].error*1.0/Tlay2;
				}
			}
			for(int I=0;I<renewableenergynum;I++)
			{
				for(int J1=J;J1<Ttotal;J1++)
				{
					errorvaluetotal[J] +=Renewableenergydata[I].error*Renewableenergydata[I].PnewHttotal[J1]*1.0/Tlay2;
				}
				for(int J1=0;J1<errorlength-(Ttotal-J);J1++)
				{
					errorvaluetotal[J] +=Renewableenergydata[I].error*Renewableenergydata[I].PnewHttotal[J1]*1.0/Tlay2;
				}
			}
		}
		//cout<<errorvaluetotal[J]<<" ";
	}

	for(int J=0;J<T;J++)
	{
		errorvalue[J]=errorvaluetotal[J*Tlay2];
		for(int J1=1;J1<Tlay2;J1++)
		{
			if(errorvalue[J]<errorvaluetotal[J*Tlay2+J1])
			{errorvalue[J]=errorvaluetotal[J*Tlay2+J1];}
		}
	}
	
	errorvaluemaxS=errorvaluetotal[0];
	for(int J=1;J<Ttotal;J++)
	{
		if(errorvaluetotal[J]<errorvaluemaxS)
		{errorvaluemaxS=errorvaluetotal[J];}
	}/**/
	energysumBH=0;
	energysumBL=0;
	energysumBC=0;
	for(int I=0;I<energystoragenum;I++)
	{
		energysumBC +=Energystoragedata[I].VHk;
		if((Energystoragedata[I].type/1000)%10==1)
		{energysumBH +=Energystoragedata[I].VHk;
		energysumBL +=Energystoragedata[I].VLk;}
	}
}
void SCHEDULE::initc()
{
	Controllableunitdata=new ControllableUnitData[controllableunitnum];
	CHECKPOINTER(Controllableunitdata);
	for(int i=0;i<controllableunitnum;i++)
	{
		Controllableunitdata[i].Pi=new double[node];
		CHECKPOINTER(Controllableunitdata[i].Pi);
		Controllableunitdata[i].ci=new double[node];
		CHECKPOINTER(Controllableunitdata[i].ci);
		Controllableunitdata[i].Q=new double[pollutionnum];
		CHECKPOINTER(Controllableunitdata[i].Q);
		Controllableunitdata[i].Uit=new bool[T];
		CHECKPOINTER(Controllableunitdata[i].Uit);
		Controllableunitdata[i].openit=new bool[T];
		CHECKPOINTER(Controllableunitdata[i].openit);
		Controllableunitdata[i].closeit=new bool[T];
		CHECKPOINTER(Controllableunitdata[i].closeit);
		Controllableunitdata[i].Pit=new double[T];
		CHECKPOINTER(Controllableunitdata[i].Pit);
		Controllableunitdata[i].Rit=new double[T];
		CHECKPOINTER(Controllableunitdata[i].Rit);
		Controllableunitdata[i].Sit=new double[T];
		CHECKPOINTER(Controllableunitdata[i].Sit);
		Controllableunitdata[i].Cit=new double[T];
		CHECKPOINTER(Controllableunitdata[i].Cit);
		//lay2
		Controllableunitdata[i].Uitlay2=new bool[Tlay2];
		CHECKPOINTER(Controllableunitdata[i].Uitlay2);
		Controllableunitdata[i].Pitlay2=new double[Tlay2];
		CHECKPOINTER(Controllableunitdata[i].Pitlay2);
		Controllableunitdata[i].Sitlay2=new double[Tlay2];
		CHECKPOINTER(Controllableunitdata[i].Sitlay2);
		Controllableunitdata[i].Citlay2=new double[Tlay2];
		CHECKPOINTER(Controllableunitdata[i].Citlay2);
		//total
		Controllableunitdata[i].Pittotal=new double[Ttotal];
		CHECKPOINTER(Controllableunitdata[i].Pittotal);
		//
		Controllableunitdata[i].levelIdentifier=new int[mglevel+1];
		CHECKPOINTER(Controllableunitdata[i].levelIdentifier);
		Controllableunitdata[i].CostC=new double[Ttotal];
		CHECKPOINTER(Controllableunitdata[i].CostC);
		Controllableunitdata[i].CostS=new double[Ttotal];
		CHECKPOINTER(Controllableunitdata[i].CostS);
		Controllableunitdata[i].CostCOM=new double[Ttotal];
		CHECKPOINTER(Controllableunitdata[i].CostCOM);
	}
	Energystoragedata=new EnergyStorageData[energystoragenum];
	CHECKPOINTER(Energystoragedata);
	for(int i=0;i<energystoragenum;i++)
	{
		Energystoragedata[i].Ugkt=new bool [T];
		CHECKPOINTER(Energystoragedata[i].Ugkt);
		Energystoragedata[i].Upkt=new bool [T];
		CHECKPOINTER(Energystoragedata[i].Upkt);
		Energystoragedata[i].Pkt=new double [T];
		CHECKPOINTER(Energystoragedata[i].Pkt);
		Energystoragedata[i].Vkt=new double [T];
		CHECKPOINTER(Energystoragedata[i].Vkt);
		Energystoragedata[i].Pgkt=new double [T];
		CHECKPOINTER(Energystoragedata[i].Pgkt);
		Energystoragedata[i].Ppkt=new double [T];
		CHECKPOINTER(Energystoragedata[i].Ppkt);
		Energystoragedata[i].Pdhkt=new double [T];
		CHECKPOINTER(Energystoragedata[i].Pdhkt);
		Energystoragedata[i].Pchkt=new double [T];
		CHECKPOINTER(Energystoragedata[i].Pchkt);
		Energystoragedata[i].Rkt=new double [T];
		CHECKPOINTER(Energystoragedata[i].Rkt);
		Energystoragedata[i].egkt=new bool [T];
		CHECKPOINTER(Energystoragedata[i].egkt);
		Energystoragedata[i].epkt=new bool [T];
		CHECKPOINTER(Energystoragedata[i].epkt);
		//lay2
		Energystoragedata[i].Pktlay2=new double [Tlay2];
		CHECKPOINTER(Energystoragedata[i].Pktlay2);
		Energystoragedata[i].Vktlay2=new double [Tlay2];
		CHECKPOINTER(Energystoragedata[i].Vktlay2);
		Energystoragedata[i].Pgktlay2=new double [Tlay2];
		CHECKPOINTER(Energystoragedata[i].Pgktlay2);
		Energystoragedata[i].Ppktlay2=new double [Tlay2];
		CHECKPOINTER(Energystoragedata[i].Ppktlay2);
		//total
		Energystoragedata[i].Pkttotal=new double [Ttotal];
		CHECKPOINTER(Energystoragedata[i].Pkttotal);
		Energystoragedata[i].Vkttotal=new double [Ttotal];
		CHECKPOINTER(Energystoragedata[i].Vkttotal);
		//
		Energystoragedata[i].levelIdentifier=new int[mglevel+1];
		CHECKPOINTER(Energystoragedata[i].levelIdentifier);

		Energystoragedata[i].VLksetschedule=new double [T];
		CHECKPOINTER(Energystoragedata[i].VLksetschedule);
		Energystoragedata[i].VHksetschedule=new double [T];
		CHECKPOINTER(Energystoragedata[i].VHksetschedule);
		Energystoragedata[i].VLksetschedulelay2=new double [Tlay2];
		CHECKPOINTER(Energystoragedata[i].VLksetschedulelay2);
		Energystoragedata[i].VHksetschedulelay2=new double [Tlay2];
		CHECKPOINTER(Energystoragedata[i].VHksetschedulelay2);
		Energystoragedata[i].CostC=new double [Ttotal];
		CHECKPOINTER(Energystoragedata[i].CostC);

	}
	Renewableenergydata=new RenewableEnergyData[renewableenergynum];
	CHECKPOINTER(Renewableenergydata);
	for(int i=0;i<renewableenergynum;i++)
	{ 
		Renewableenergydata[i].PnewHt=new double[T];
		CHECKPOINTER(Renewableenergydata[i].PnewHt);
		Renewableenergydata[i].PnewHttemp=new double[T];
		CHECKPOINTER(Renewableenergydata[i].PnewHttemp);
		Renewableenergydata[i].Pnewt=new double[T];
		CHECKPOINTER(Renewableenergydata[i].Pnewt);
		//total
		Renewableenergydata[i].PnewHttotal=new double[Ttotal];
		CHECKPOINTER(Renewableenergydata[i].PnewHttotal);
		Renewableenergydata[i].Pnewttotal=new double[Ttotal];
		CHECKPOINTER(Renewableenergydata[i].Pnewttotal);
		//lay2
		Renewableenergydata[i].PnewHtlay2=new double[Tlay2];
		CHECKPOINTER(Renewableenergydata[i].PnewHtlay2);
		Renewableenergydata[i].Pnewtlay2=new double[Tlay2];
		CHECKPOINTER(Renewableenergydata[i].Pnewtlay2);
		//
		Renewableenergydata[i].levelIdentifier=new int[mglevel+1];
		CHECKPOINTER(Renewableenergydata[i].levelIdentifier);
	}
	Prt=new double[T];
	CHECKPOINTER(Prt);
	//total
	Prttotal=new double[Ttotal];
	CHECKPOINTER(Prttotal);
	//lay2
	Prtlay2=new double[Tlay2];
	CHECKPOINTER(Prtlay2);
	Pktout=new double *[energystoragenum];
	CHECKPOINTER(Pktout);
	Pdhktout=new double *[energystoragenum];
	CHECKPOINTER(Pdhktout);
	Pchktout=new double *[energystoragenum];
	CHECKPOINTER(Pchktout);
	Vsoet=new double *[energystoragenum];
	CHECKPOINTER(Vsoet);
	for(int i=0;i<energystoragenum;i++)
	{
		Pktout[i]=new double [T];
		CHECKPOINTER(Pktout[i]);
		Pdhktout[i]=new double [T];
		CHECKPOINTER(Pdhktout[i]);
		Pchktout[i]=new double [T];
		CHECKPOINTER(Pchktout[i]);
		Vsoet[i]=new double [T];
		CHECKPOINTER(Vsoet[i]);

	}
	Pd1t=new double[T];
	CHECKPOINTER(Pd1t);
	//total
	Pd1ttotal=new double[Ttotal];
	CHECKPOINTER(Pd1ttotal);
	//lay2
	Pd1tlay2=new double[Tlay2];
	CHECKPOINTER(Pd1tlay2);

	Griddata.Buy=new double[T];
	CHECKPOINTER(Griddata.Buy);
	Griddata.Sell=new double[T];
	CHECKPOINTER(Griddata.Sell);
	Griddata.Buytemp=new double[T];
	CHECKPOINTER(Griddata.Buytemp);
	Griddata.Selltemp=new double[T];
	CHECKPOINTER(Griddata.Selltemp);
	Griddata.Ubuyt=new bool[T];
	CHECKPOINTER(Griddata.Ubuyt);
	Griddata.Usellt=new bool[T];
	CHECKPOINTER(Griddata.Usellt);
	Griddata.Pbuyt=new double[T];
	CHECKPOINTER(Griddata.Pbuyt);
	Griddata.Psellt=new double[T];
	CHECKPOINTER(Griddata.Psellt);
	Griddata.VirtualBuy=new double[T];
	CHECKPOINTER(Griddata.VirtualBuy);
	Griddata.VirtualSell=new double[T];
	CHECKPOINTER(Griddata.VirtualSell);
	//total
	Griddata.Buytotal=new double[Ttotal];
	CHECKPOINTER(Griddata.Buytotal);
	Griddata.Selltotal=new double[Ttotal];
	CHECKPOINTER(Griddata.Selltotal);
	Griddata.VirtualBuytotal=new double[Ttotal];
	CHECKPOINTER(Griddata.VirtualBuytotal);
	Griddata.VirtualSelltotal=new double[Ttotal];
	CHECKPOINTER(Griddata.VirtualSelltotal);
	Griddata.Pbuyttotal=new double[Ttotal];
	CHECKPOINTER(Griddata.Pbuyttotal);
	Griddata.Psellttotal=new double[Ttotal];
	CHECKPOINTER(Griddata.Psellttotal);
	//lay2
	Griddata.Buylay2=new double[Tlay2];
	CHECKPOINTER(Griddata.Buylay2);
	Griddata.Selllay2=new double[Tlay2];
	CHECKPOINTER(Griddata.Selllay2);
	Griddata.VirtualBuylay2=new double[Tlay2];
	CHECKPOINTER(Griddata.VirtualBuylay2);
	Griddata.VirtualSelllay2=new double[Tlay2];
	CHECKPOINTER(Griddata.VirtualSelllay2);
	Griddata.Pbuytlay2=new double[Tlay2];
	CHECKPOINTER(Griddata.Pbuytlay2);
	Griddata.Pselltlay2=new double[Tlay2];
	CHECKPOINTER(Griddata.Pselltlay2);
	Griddata.CostBS=new double[Ttotal];
	CHECKPOINTER(Griddata.CostBS);

	errorvalue=new double [T];
	CHECKPOINTER(errorvalue);
	errorvaluetotal=new double [Ttotal];
	CHECKPOINTER(errorvaluetotal);
	errorvaluelay2=new double [Tlay2];
	CHECKPOINTER(errorvaluelay2);

	V=new double [pollutionnum];
	CHECKPOINTER(V);
	Qgrid=new double [pollutionnum];
	CHECKPOINTER(Qgrid);

	Loaddata=new LoadData[loadnum];
	CHECKPOINTER(Loaddata);
	for(int i=0;i<loadnum;i++)
	{
		Loaddata[i].Pdt=new double [T];
		CHECKPOINTER(Loaddata[i].Pdt);
		Loaddata[i].Ucutx=new bool [T];
		CHECKPOINTER(Loaddata[i].Ucutx);
		//		Loaddata[i].Pcutxt=new double [T];
		//		CHECKPOINTER(Loaddata[i].Pcutxt);
		//		Loaddata[i].Udtdeltp=new bool [T];
		//		CHECKPOINTER(Loaddata[i].Udtdeltp);
		//		Loaddata[i].Udtdeltm=new bool [T];
		//		CHECKPOINTER(Loaddata[i].Udtdeltm);
		//		Loaddata[i].Pdtdeltp=new double [T];
		//		CHECKPOINTER(Loaddata[i].Pdtdeltp);
		//		Loaddata[i].Pdtdeltm=new double [T];
		//		CHECKPOINTER(Loaddata[i].Pdtdeltm);
		Loaddata[i].Scutx=new bool [T];
		CHECKPOINTER(Loaddata[i].Scutx);
		//total
		Loaddata[i].Pdttotal=new double [Ttotal];
		CHECKPOINTER(Loaddata[i].Pdttotal);
		Loaddata[i].Ucutxtotal=new bool [Ttotal];
		CHECKPOINTER(Loaddata[i].Ucutxtotal);
		//lay2
		Loaddata[i].Pdtlay2=new double [Tlay2];
		CHECKPOINTER(Loaddata[i].Pdtlay2);
		Loaddata[i].Ucutxlay2=new bool [Tlay2];
		CHECKPOINTER(Loaddata[i].Ucutxlay2);
		//
		Loaddata[i].levelIdentifier=new int[mglevel+1];
		CHECKPOINTER(Loaddata[i].levelIdentifier);
		Loaddata[i].CostCut=new double [Ttotal];
		CHECKPOINTER(Loaddata[i].CostCut);
	}
	Pbuytout=new double [T];
	CHECKPOINTER(Pbuytout);
	Pselltout=new double [T];
	CHECKPOINTER(Pselltout);


	Pitout=new double *[controllableunitnum];
	CHECKPOINTER(Pitout);
	Citout=new double *[controllableunitnum];
	CHECKPOINTER(Citout);
	Sitout=new double *[controllableunitnum];
	CHECKPOINTER(Sitout);
	for(int i=0;i<controllableunitnum;i++)
	{
		Pitout[i]=new double [T];
		CHECKPOINTER(Pitout[i]);
		Citout[i]=new double [T];
		CHECKPOINTER(Citout[i]);
		Sitout[i]=new double [T];
		CHECKPOINTER(Sitout[i]);
	}

	Pnewtout=new double *[renewableenergynum];
	CHECKPOINTER(Pnewtout);
	for(int i=0;i<renewableenergynum;i++)
	{
		Pnewtout[i]=new double [T];
		CHECKPOINTER(Pnewtout[i]);
	}

	Pdtout=new double[T];
	CHECKPOINTER(Pdtout);

	//	CostkWh=new double[energystoragenum];
	//	CHECKPOINTER(CostkWh);

	Uitset=new int *[controllableunitnum];
	CHECKPOINTER(Uitset);
	for(int i=0;i<controllableunitnum;i++)
	{
		Uitset[i]=new int [T];
		CHECKPOINTER(Uitset[i]);
	}
	Ucutxset=new int *[loadnum];
	CHECKPOINTER(Ucutxset);
	for(int i=0;i<loadnum;i++)
	{
		Ucutxset[i]=new int [T];
		CHECKPOINTER(Ucutxset[i]);
	}
	Pcutxt=new double [T];
	CHECKPOINTER(Pcutxt);
/*
	Crateall=new double *[controllableunitnum+energystoragenum+1];
	CHECKPOINTER(Crateall);
	for(int i=0;i<controllableunitnum+energystoragenum+1;i++)
	{
		Crateall[i]=new double [node];
		CHECKPOINTER(Crateall[i]);
	}
	Crateall1=new double [controllableunitnum*node+energystoragenum+1];
	CHECKPOINTER(Crateall1);
	Crateall1order=new int [controllableunitnum*node+energystoragenum+1];
	CHECKPOINTER(Crateall1order);
	Crateall1order2=new int [controllableunitnum*node+energystoragenum+1];
	CHECKPOINTER(Crateall1order2);
*/
	Virtualloaddata=new VirtualLoadData[virtualloadnum];
	CHECKPOINTER(Virtualloaddata);
	for(int i=0;i<virtualloadnum;i++)
	{
		Virtualloaddata[i].Pdt=new double [T];
		CHECKPOINTER(Virtualloaddata[i].Pdt);
		Virtualloaddata[i].Ucutx=new bool [T];
		CHECKPOINTER(Virtualloaddata[i].Ucutx);
		//total
		Virtualloaddata[i].Pdttotal=new double [Ttotal];
		CHECKPOINTER(Virtualloaddata[i].Pdttotal);
		Virtualloaddata[i].Ucutxtotal=new bool [Ttotal];
		CHECKPOINTER(Virtualloaddata[i].Ucutxtotal);
		//lay2
		Virtualloaddata[i].Pdtlay2=new double [Tlay2];
		CHECKPOINTER(Virtualloaddata[i].Pdtlay2);
		Virtualloaddata[i].Ucutxlay2=new bool [Tlay2];
		CHECKPOINTER(Virtualloaddata[i].Ucutxlay2);
		//
		Virtualloaddata[i].levelIdentifier=new int[mglevel+1];
		CHECKPOINTER(Virtualloaddata[i].levelIdentifier);
	}
	LevelID32=new int [controllableunitnum+energystoragenum+loadnum+renewableenergynum];
	CHECKPOINTER(LevelID32);
	LevelIdentify=new int [controllableunitnum+energystoragenum+loadnum+renewableenergynum];
	CHECKPOINTER(LevelIdentify);
	LevelIdentifynext=new int [controllableunitnum+energystoragenum+loadnum+renewableenergynum];
	CHECKPOINTER(LevelIdentifynext);
	Levelnumtoreal=new int *[mglevel];
	CHECKPOINTER(Levelnumtoreal);
	for(int i=0;i<mglevel;i++)
	{
		Levelnumtoreal[i]=new int [mglevelnum[i]];
		CHECKPOINTER(Levelnumtoreal[i]);
	}
	Levelclassify=new int [controllableunitnum+energystoragenum+loadnum+renewableenergynum];
	CHECKPOINTER(Levelclassify);

}

void SCHEDULE::setchangeinit()//IloModel model
{
	//IloEnv env = model.getEnv();
	int temp;
	ifstream fin("changeinit.txt");
	if (!fin)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fin.ignore(1024,'*');
	for(int I=0;I<controllableunitnum;I++)
	{
		fin>>temp;
		fin>>Controllableunitdata[temp-1].ID32;
		fin>>Controllableunitdata[temp-1].Pinit>>Controllableunitdata[temp-1].Uinit>>Controllableunitdata[temp-1].TOinit>>Controllableunitdata[temp-1].TDinit;
	}
	//fin.ignore(1024,'*');
	for(int I=0;I<energystoragenum;I++)
	{
		fin>>temp;
		fin>>Energystoragedata[temp-1].ID32;
		fin>>Energystoragedata[temp-1].Einit;
	}
	fin.close(); 
}

void SCHEDULE::setchangeinit_lay2(int xlay2)//IloModel model
{
	if(xlay2==0)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//Controllableunitdata[I].Uinit=Controllableunitdata[I].Uit[0];
			//fin>>Controllableunitdata[temp-1].Pinit>>Controllableunitdata[temp-1].Uinit>>Controllableunitdata[temp-1].TOinit>>Controllableunitdata[temp-1].TDinit;
		}
		for(int I=0;I<energystoragenum;I++)
		{
			//fin>>Energystoragedata[temp-1].Einit;
			//model.add(Vkt[I][T-1]-Pdhkt[I][T-1]*24/T+Pchkt[I][T-1]*24/T-Vkt[I][temp]==Energystoragedata[I].Wk);
			Energystoragedata[I].Wk=Energystoragedata[I].Ppkt[0]*Energystoragedata[I].yitap-Energystoragedata[I].Pgkt[0]/Energystoragedata[I].yitag;
			//cout<<"Energystoragedata[I].Wk:"<<Energystoragedata[I].Wk<<endl;
		}

	}
	else
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			Controllableunitdata[I].Pinit=Controllableunitdata[I].Pit[xlay2-1];
			Controllableunitdata[I].Uinit=Controllableunitdata[I].Uit[xlay2-1];
		}
		for(int I=0;I<energystoragenum;I++)
		{
			//Energystoragedata[I].Einit=Energystoragedata[I].Vkt[xlay2-1];
			Energystoragedata[I].Einit=Energystoragedata[I].Vktlay2[Tlay2-1];//上一个时间段的vkt
			Energystoragedata[I].Wk=Energystoragedata[I].Ppkt[xlay2]*Energystoragedata[I].yitap-Energystoragedata[I].Pgkt[xlay2]/Energystoragedata[I].yitag;
			//Energystoragedata[I].Wk=0;
			//Energystoragedata[I].outlimitLtime=0;
			//Energystoragedata[I].outlimitHtime=0;
			//cout<<"Wk:"<<Energystoragedata[I].Wk<<endl;
		}
	}
	//value of end
	for(int I=0;I<controllableunitnum;I++)
	{
		Controllableunitdata[I].Pitlay2[Tlay2-1]=Controllableunitdata[I].Pit[xlay2];
		Controllableunitdata[I].Uitlay2[Tlay2-1]=Controllableunitdata[I].Uit[xlay2];
		//cout<<"Controllableunitdata[I].Uitlay2[Tlay2-1]:"<<Controllableunitdata[I].Uitlay2[Tlay2-1]<<endl;
	}
	for(int I=0;I<energystoragenum;I++)
	{
		Energystoragedata[I].Pktlay2[Tlay2-1]=Energystoragedata[I].Pkt[xlay2];//
		//Energystoragedata[I].Vktlay2[Tlay2-1]=Energystoragedata[I].Vkt[xlay2];
		//cout<<"Energystoragedata[I].Vktlay2[xlay2-1]:"<<Energystoragedata[I].Vkt[xlay2-1]<<endl;
		//cout<<"Energystoragedata[I].Vktlay2[xlay2]:"<<Energystoragedata[I].Vkt[xlay2]<<endl;
	}
	for(int i=0;i<loadnum;i++)
	{
		Loaddata[i].Ucutxlay2[Tlay2-1]=Loaddata[i].Ucutx[xlay2];
	}
	Griddata.Pbuytlay2[Tlay2-1]=Griddata.Pbuyt[xlay2];
	Griddata.Pselltlay2[Tlay2-1]=Griddata.Psellt[xlay2];

}

void SCHEDULE::setmodelinit_lay2(lprec *lp,int Ttemp,int xlay2)
{
	int colno1[1];
	double row1[1];
	int colno2[2];
	double row2[2];
	if(xlay2<T-1)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			if(Controllableunitdata[I].Pitlay2[Tlay2-1]<Controllableunitdata[I].Pit[xlay2+1])
			{
				//Controllableunitdata[I].Pitlay2[Tlay2-1];
				colno1[0]=onearray*Ttemp+I*Ttemp+Tlay2-1+1;
				row1[0]=1;
				//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, Controllableunitdata[I].Pitlay2[Tlay2-1]);
				//Controllableunitdata[I].Uitlay2[Tlay2-1]
				colno1[0]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+Tlay2-1+1;
				row1[0]=1;
				add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Controllableunitdata[I].Uitlay2[Tlay2-1]);
			}
			else if(Controllableunitdata[I].Pitlay2[Tlay2-1]>Controllableunitdata[I].Pit[xlay2+1])
			{
				//Controllableunitdata[I].Pitlay2[Tlay2-1];
				colno1[0]=onearray*Ttemp+I*Ttemp+Tlay2-1+1;
				row1[0]=1;
				//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, Controllableunitdata[I].Pitlay2[Tlay2-1]);
				//Controllableunitdata[I].Uitlay2[Tlay2-1]
				colno1[0]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+Tlay2-1+1;
				row1[0]=1;
				add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Controllableunitdata[I].Uitlay2[Tlay2-1]);
			}
			else
			{
				//Controllableunitdata[I].Pitlay2[Tlay2-1];
				colno1[0]=onearray*Ttemp+I*Ttemp+Tlay2-1+1;
				row1[0]=1;
				//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Controllableunitdata[I].Pitlay2[Tlay2-1]);
				//Controllableunitdata[I].Uitlay2[Tlay2-1]
				colno1[0]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+Tlay2-1+1;
				row1[0]=1;
				add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Controllableunitdata[I].Uitlay2[Tlay2-1]);
			}

		}
		if(Griddata.Pbuytlay2[Tlay2-1]<Griddata.Pbuyt[xlay2+1])
		{
			colno1[0]=2*Ttemp+Tlay2-1+1;
			row1[0]=1;
			//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, Griddata.Pbuytlay2[Tlay2-1]);
		}
		else if(Griddata.Pbuytlay2[Tlay2-1]>Griddata.Pbuyt[xlay2+1])
		{
			colno1[0]=2*Ttemp+Tlay2-1+1;
			row1[0]=1;
			//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, Griddata.Pbuytlay2[Tlay2-1]);
		}
		else
		{
			colno1[0]=2*Ttemp+Tlay2-1+1;
			row1[0]=1;
			//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Griddata.Pbuytlay2[Tlay2-1]);
		}
		if(Griddata.Pselltlay2[Tlay2-1]<Griddata.Psellt[xlay2+1])
		{
			colno1[0]=3*Ttemp+Tlay2-1+1;
			row1[0]=1;
			//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, Griddata.Pselltlay2[Tlay2-1]);
		}
		else if(Griddata.Pselltlay2[Tlay2-1]>Griddata.Psellt[xlay2+1])
		{
			colno1[0]=3*Ttemp+Tlay2-1+1;
			row1[0]=1;
			//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, Griddata.Pselltlay2[Tlay2-1]);
		}
		else
		{
			colno1[0]=3*Ttemp+Tlay2-1+1;
			row1[0]=1;
			//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Griddata.Pselltlay2[Tlay2-1]);
		}
	}
	else
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//Controllableunitdata[I].Pitlay2[Tlay2-1]=Controllableunitdata[I].Pit[xlay2];;
			//colno1[0]=onearray*Ttemp+I*Ttemp+Tlay2-1+1;
			//row1[0]=1;
			//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Controllableunitdata[I].Pitlay2[Tlay2-1]);
			//Controllableunitdata[I].Uitlay2[Tlay2-1]
			colno1[0]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+Tlay2-1+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Controllableunitdata[I].Uitlay2[Tlay2-1]);
		}
		//Griddata.Pbuytlay2[Tlay2-1]=Griddata.Pbuyt[xlay2];
		//Griddata.Pselltlay2[Tlay2-1]=Griddata.Psellt[xlay2];
		colno1[0]=2*Ttemp+Tlay2-1+1;
		row1[0]=1;
		//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Griddata.Pbuytlay2[Tlay2-1]);
		colno1[0]=3*Ttemp+Tlay2-1+1;
		row1[0]=1;
		//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Griddata.Pselltlay2[Tlay2-1]);
	}

	for(int J=0;J<Ttemp;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//Controllableunitdata[I].Uitlay2[Tlay2-1]
			colno1[0]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Controllableunitdata[I].Uitlay2[Tlay2-1]);
		}
		for(int I=0;I<energystoragenum;I++)
		{
			//Energystoragedata[I].Pktlay2[Tlay2-1]=Energystoragedata[I].Pkt[xlay2];
			//Energystoragedata[I].Vktlay2[Tlay2-1]=Energystoragedata[I].Vkt[xlay2];
			//colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+I*Ttemp+J+1;
			//row1[0]=1;
			//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Controllableunitdata[I].Pitlay2[Tlay2-1]);
		}
		for(int I=0;I<loadnum;I++)
		{
			//Loaddata[i].Ucutxlay2[Tlay2-1]=Loaddata[i].Ucutx[xlay2];
			colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, Loaddata[I].Ucutxlay2[Tlay2-1]);//GE
		}
		
		//hehe////
	/*	for(int I=0;I<loadnum;I++)
		{
			//Loaddata[i].Ucutxlay2[Tlay2-1]=Loaddata[i].Ucutx[xlay2];
			colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Loaddata[I].Ucutxlay2[Tlay2-1]);//GE
		}
		//cout<<Loaddata[3].Ucutxlay2[Tlay2-1]<<endl;
		colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+3*Ttemp+J+1;
		row1[0]=1;
		add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);
		for(int I=13;I<loadnum;I++)
		{
			//Loaddata[i].Ucutxlay2[Tlay2-1]=Loaddata[i].Ucutx[xlay2];
			colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Loaddata[I].Ucutxlay2[Tlay2-1]);//GE
		}
		for(int I=0;I<12;I++)
		{
			//Loaddata[i].Ucutxlay2[Tlay2-1]=Loaddata[i].Ucutx[xlay2];
			colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Loaddata[I].Ucutxlay2[Tlay2-1]);//GE
		}
		colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+12*Ttemp+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 1);//GE*/
	}
	for(int I=0;I<loadnum;I++)//时段内切负荷一致
	{
		colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
			+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+0+1;
		row2[0]=1;
		for(int J=1;J<Ttemp;J++)
		{
			colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1;
			row2[1]=-1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, 0);
		}
	}
	if(xlay2>0)
	{
		for(int I=0;I<loadnum;I++)//切负荷波动
		{
			//model.add(Sit[I][0]>=Controllableunitdata[I].Shi*(Uit[I][0]-Controllableunitdata[I].Uinit));
			colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualloadnum*2*Ttemp+I+1;
			row2[0]=1;
			colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+0+1;
			row2[1]=-10;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, -10*Loaddata[I].Ucutx[xlay2-1]);
		}
	}

}
void SCHEDULE::setmodelinit1_lay2(lprec *lp,int Ttemp,int xlay2)
{
	int colno1[1];
	double row1[1];
	int colno2[2];
	double row2[2];
	if(xlay2<T-1)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//Controllableunitdata[I].Uitlay2[Tlay2-1]
			colno1[0]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+Tlay2-1+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, Controllableunitdata[I].Uitlay2[Tlay2-1]);

		}
	}
	else
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//Controllableunitdata[I].Uitlay2[Tlay2-1]
			colno1[0]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+Tlay2-1+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, Controllableunitdata[I].Uitlay2[Tlay2-1]);
		}
	}

	for(int J=0;J<Ttemp;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//Controllableunitdata[I].Uitlay2[Tlay2-1]
			colno1[0]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J+1;
			 row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, Controllableunitdata[I].Uitlay2[Tlay2-1]);
		}
		for(int I=0;I<energystoragenum;I++)
		{
			//Energystoragedata[I].Pktlay2[Tlay2-1]=Energystoragedata[I].Pkt[xlay2];
			//Energystoragedata[I].Vktlay2[Tlay2-1]=Energystoragedata[I].Vkt[xlay2];
			//colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+I*Ttemp+J+1;
			//row1[0]=1;
			//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Controllableunitdata[I].Pitlay2[Tlay2-1]);
		}
		for(int I=0;I<loadnum;I++)
		{
			//Loaddata[i].Ucutxlay2[Tlay2-1]=Loaddata[i].Ucutx[xlay2];
			colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1;
			row1[0]=1;
			//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 1);/*Loaddata[I].Ucutxlay2[Tlay2-1]*/
		}
	}
	for(int I=0;I<loadnum;I++)//时段内切负荷一致，1>0
	{
		if(xlay2==0)
		{
			for(int J=1;J<Ttemp;J++)
			{
				colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J-1+1;
				row2[0]=1;
				colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1;
				row2[1]=-1;
				add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
			}
		}
		else
		{
			colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+0+1;
			row2[0]=1;
			for(int J=1;J<Ttemp;J++)
			{
				
				colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1;
				row2[1]=-1;
				add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, 0);
			}
		}
	}/**/
	if(xlay2>0)
	{
		for(int I=0;I<loadnum;I++)//切负荷波动
		{
			//model.add(Sit[I][0]>=Controllableunitdata[I].Shi*(Uit[I][0]-Controllableunitdata[I].Uinit));
			colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualloadnum*2*Ttemp+I+1;
			row2[0]=1;
			colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+0+1;
			row2[1]=-10;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, -10*Loaddata[I].Ucutxlay2[Ttemp-1]);
		}
	}/**/

}
void SCHEDULE::setmodelinit12_lay2(lprec *lp,int Ttemp,int xlay2)
{
	int colno1[1];
	double row1[1];
	int colno2[2];
	double row2[2];
	if(xlay2<T-1)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//Controllableunitdata[I].Uitlay2[Tlay2-1]
			colno1[0]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+Tlay2-1+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Controllableunitdata[I].Uitlay2[Tlay2-1]);

		}
	}
	else
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//Controllableunitdata[I].Uitlay2[Tlay2-1]
			colno1[0]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+Tlay2-1+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Controllableunitdata[I].Uitlay2[Tlay2-1]);
		}
	}

	for(int J=0;J<Ttemp;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//Controllableunitdata[I].Uitlay2[Tlay2-1]
			//colno1[0]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J+1;
			// row1[0]=1;
			//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Controllableunitdata[I].Uitlay2[Tlay2-1]);
		}
		for(int I=0;I<energystoragenum;I++)
		{
			//Energystoragedata[I].Pktlay2[Tlay2-1]=Energystoragedata[I].Pkt[xlay2];
			//Energystoragedata[I].Vktlay2[Tlay2-1]=Energystoragedata[I].Vkt[xlay2];
			//colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+I*Ttemp+J+1;
			//row1[0]=1;
			//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Controllableunitdata[I].Pitlay2[Tlay2-1]);
		}
		for(int I=0;I<loadnum;I++)
		{
			//Loaddata[i].Ucutxlay2[Tlay2-1]=Loaddata[i].Ucutx[xlay2];
			colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, Loaddata[I].Ucutxlay2[J]);/*Loaddata[I].Ucutxlay2[Tlay2-1]*/
		}
	}
	for(int I=0;I<loadnum;I++)//时段内切负荷一致，1>0
	{
		if(xlay2==0)
		{
			for(int J=1;J<Ttemp;J++)
			{
				colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J-1+1;
				row2[0]=1;
				colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1;
				row2[1]=-1;
				add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
			}
		}
		else
		{
			colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+0+1;
			row2[0]=1;
			for(int J=1;J<Ttemp;J++)
			{
				
				colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1;
				row2[1]=-1;
				add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, 0);
			}
		}
	}/**/
	if(xlay2>0)
	{
		for(int I=0;I<loadnum;I++)//切负荷波动
		{
			//model.add(Sit[I][0]>=Controllableunitdata[I].Shi*(Uit[I][0]-Controllableunitdata[I].Uinit));
			colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualloadnum*2*Ttemp+I+1;
			row2[0]=1;
			colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+0+1;
			row2[1]=-10;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, -10*Loaddata[I].Ucutxlay2[Ttemp-1]);
		}
	}/**/

}
void SCHEDULE::outputobject()
{
	inputOC();
		double OCCost_controlC=0;
		double OCCost_controlS=0;
		double OCCost_controlCOM=0;
		double OCCost_storage=0;
		double OCCost_load=0;
		double OCCost_buysell=0;
		double OCCost_all=0;
	if(OCdecision>0)
	{
		calculateOC();


			for(int I=0;I<controllableunitnum;I++)
			{
				OCCost_controlC+=Controllableunitdata[I].OCCostC;
				OCCost_controlS+=Controllableunitdata[I].OCCostS;
				OCCost_controlCOM+=Controllableunitdata[I].OCCostCOM;
			}
			for(int I=0;I<energystoragenum;I++)
			{
				OCCost_storage+=Energystoragedata[I].OCCostC;
			}
			for(int I=0;I<loadnum;I++)
			{
				OCCost_load+=Loaddata[I].OCCostCut;
			}
			OCCost_buysell+=Griddata.OCCostBS;
		OCCost_all=OCCost_controlC+OCCost_controlS+OCCost_controlCOM+OCCost_storage+OCCost_load+OCCost_buysell;
	}

	double Cost_controlC=0;
	double Cost_controlS=0;
	double Cost_controlCOM=0;
	double Cost_storage=0;
	double Cost_load=0;
	double Cost_buysell=0;
	double Cost_all=0;
	for(int J=0;J<Ttotal;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			Cost_controlC+=Controllableunitdata[I].CostC[J];
			Cost_controlS+=Controllableunitdata[I].CostS[J];
			Cost_controlCOM+=Controllableunitdata[I].CostCOM[J];
		}
		for(int I=0;I<energystoragenum;I++)
		{
			Cost_storage+=Energystoragedata[I].CostC[J];
		}
		for(int I=0;I<loadnum;I++)
		{
			Cost_load+=Loaddata[I].CostCut[J];
		}
		Cost_buysell+=Griddata.CostBS[J];
	}
	Cost_all=Cost_controlC+Cost_controlS+Cost_controlCOM+Cost_storage+Cost_load+Cost_buysell;
	ofstream fout("outputobjectresult.txt");
	if (!fout)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fout<<"可控机组燃料成本 "<<endl<<"可控机组启动成本 "<<"可控机组维护等成本 "<<"蓄电池成本 "<<"切负荷成本 购售电成本"<<endl;
	fout<<Cost_controlC<<" "<<Cost_controlS<<" "<<Cost_controlCOM<<" ";
	fout<<Cost_storage<<" ";
	fout<<Cost_load<<" ";
	fout<<Cost_buysell<<" ";
	fout<<Cost_all<<endl;
	if(OCdecision>0)
	{
		fout<<OCCost_controlC<<" "<<OCCost_controlS<<" "<<OCCost_controlCOM<<" ";
		fout<<OCCost_storage<<" ";
		fout<<OCCost_load<<" ";
		fout<<OCCost_buysell<<" ";
		fout<<OCCost_all<<endl;
	}
	else
	{
		fout<<"无原模式"<<endl;
	}
	fout.close(); 
	if(OCdecision>0)
	{
		for(int i=0;i<controllableunitnum;i++)
		{
			delete[] OCPit[i];
		}
		delete[] OCPit;
		for(int i=0;i<energystoragenum;i++)
		{
			delete[] OCPkt[i];
		}
		delete[] OCPkt;
		for(int i=0;i<renewableenergynum;i++)
		{
			delete[] OCPnewt[i];
		}
		delete[] OCPnewt;
		for(int i=0;i<loadnum;i++)
		{
			delete[] OCPloadt[i];
		}
		delete[] OCPloadt;
		delete[] OCPCCt;
	}
}
void SCHEDULE::outputtxt_lay2()
{
	ofstream fout1("output_new.txt");
	if (!fout1)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fout1<<"新能源机组："<<endl<<"编号 "<<"ID32 "<<"设备名称 "<<"新能源机组发电功率"<<endl;
	for(int i=0;i<renewableenergynum;i++)
	{
		fout1<<Renewableenergydata[i].Identifier<<"  "<<Renewableenergydata[i].ID32<<"  "<<Renewableenergydata[i].name<<"  ";
		for(int j=0;j<Ttotal;j++)
		{
			//		fout<<setiosflags(ios::fixed)<<setprecision(1)<<Renewableenergydata[i].Pnewt[j]<<" ";
			fout1<<setiosflags(ios::fixed)<<setprecision(1)<<Renewableenergydata[i].Pnewttotal[j]<<" ";
		}
		fout1<<endl;
	}
	fout1.close(); 
	ofstream fout2("output_storage.txt");
	if (!fout2)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fout2<<"储能单元："<<endl<<"编号 "<<"ID32 "<<"设备名称 "<<"储能单元充放电功率"<<endl;
	for(int I=0;I<energystoragenum;I++)
	{
		fout2<<Energystoragedata[I].Identifier<<"  "<<Energystoragedata[I].ID32<<"  "<<Energystoragedata[I].name<<"  ";
		for(int J=0;J<Ttotal;J++)
		{
			fout2<<setiosflags(ios::fixed)<<setprecision(1)<<Energystoragedata[I].Pkttotal[J]<<" ";
		}
		fout2<<endl;
	}
	fout2.close(); 
	ofstream fout3("output_unit.txt");
	if (!fout3)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fout3<<"可控机组："<<endl<<"编号 "<<"ID32 "<<"设备名称 "<<"可控机组发电功率"<<endl;
	for(int i=0;i<controllableunitnum;i++)//2222222222222222
	{
		fout3<<Controllableunitdata[i].Identifier<<"  "<<Controllableunitdata[i].ID32<<"  "<<Controllableunitdata[i].name<<"  ";
		for(int j=0;j<Ttotal;j++)
		{
			fout3<<setiosflags(ios::fixed)<<setprecision(1)<<Controllableunitdata[i].Pittotal[j]<<" ";
		}
		fout3<<endl;
	}
	fout3.close(); 
	ofstream fout4("output_load.txt");
	if (!fout4)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fout4<<"负荷："<<endl<<"编号 "<<"ID32 "<<"负荷名称 "<<"是否切负荷"<<endl;
	for(int i=0;i<loadnum;i++)//
	{
		//		fout<<loadIdentifier[i]<<"  ";
		fout4<<Loaddata[i].Identifier<<"  "<<Loaddata[i].ID32<<"  "<<Loaddata[i].name<<"  ";
		for(int j=0;j<Ttotal;j++)
		{
			fout4<<setiosflags(ios::fixed)<<setprecision(1)<<Loaddata[i].Ucutxtotal[j]<<" ";
		}
		fout4<<endl;
	}
	fout4.close(); 
	ofstream fout5("output_price.txt");
	if (!fout5)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	//fout5<<"与大电网之间的购售电:"<<endl;
	for(int j=0;j<Ttotal;j++)
	{
		//fout<<Griddata.Pbuyt[j]-Griddata.Psellt[j]<<" ";
		fout5<<setiosflags(ios::fixed)<<setprecision(1)<<Griddata.Pbuyttotal[j]-Griddata.Psellttotal[j]<<" ";
	}
	fout5.close(); 

}

void SCHEDULE::schedulgriddo_levelp(int x)
{
	lprec *lp;
	lpprepare_levelp(T);
	lp=make_lp(0,valurearrayall);
	set_add_rowmode(lp,TRUE);
	cyclecost();
	errorcalculate();
	initlpsolve(lp);
	//getlossa();
	setchangeinit();
	gridisland(lp,0);//0 grid,1 island
	allconstraint(lp,x);
	int rnum=0;
	punishrelative=0;
	VIRTUALlevelIdentifier();
	for(int Ix=1;Ix<mglevel;Ix++)
	{
		for(int Iy=0;Iy<mglevelnum[Ix];Iy++)
		{
			//VIRTUALGRIDconstraint(lp,T,mglevel-Ix,Iy+1);
			VIRTUALGRIDconstraint(lp,T,mglevel-Ix,Iy);
			punishrelative +=relativetemp;
			rnum++;
		}
	}/**/
	if(rnum==0)
	{rnum=1;}
	punishrelative=punishrelative/rnum;
	object_levelp(lp,0,x);//0 grid,1 island
	set_add_rowmode(lp, FALSE);
	set_break_at_first(lp, TRUE);//找到的第一个解
	solvestate=solveit(lp);
	//cout<<"solvestate:"<<solvestate<<endl;
	scheduletodispachgriddata(lp);
	//outputtxt();
	delete_lp(lp);

	if(solvestate!=0&&solvestate!=1)
	{
		lprec *lp;
		lpprepare_levelp(T);
		lp=make_lp(0,valurearrayall);
		set_add_rowmode(lp,TRUE);
		//cyclecost();
		//errorcalculate();
		initlpsolve(lp);
		//getlossa();
		//setchangeinit();
		gridisland(lp,0);//0 grid,1 island
		allconstraint(lp,x);
		int rnum=0;
		punishrelative=0;
		VIRTUALlevelIdentifier();
		for(int Ix=1;Ix<mglevel-1;Ix++)
		{
			for(int Iy=0;Iy<mglevelnum[Ix];Iy++)
			{
				//VIRTUALGRIDconstraint(lp,T,mglevel-Ix,Iy+1);
				VIRTUALGRIDconstraint(lp,T,mglevel-Ix,Iy);
				punishrelative +=relativetemp;
				rnum++;
			}
		}/**/
		if(rnum==0)
		{rnum=1;}
		punishrelative=punishrelative/rnum;
		object_levelp(lp,0,x);//0 grid,1 island
		set_add_rowmode(lp, FALSE);
		set_break_at_first(lp, TRUE);//找到的第一个解
		solvestate=solveit(lp);
		scheduletodispachgriddata(lp);
		//outputtxt();
		delete_lp(lp);
	}

}
void SCHEDULE::schedulgriddolay2_levelp(int x,int xlay2)
{
	lprec *lp;
	lpprepare_levelp_islandp(Tlay2);
	lp=make_lp(0,valurearrayall);
	set_add_rowmode(lp,TRUE);
	totaltolay2_data(Tlay2,xlay2);
	initlpsolve_lay2(lp,Tlay2);
	//getlossa();
	//set_obj(lp,10,24/T);
	setchangeinit_lay2(xlay2);//order of lay2
	setmodelinit_lay2(lp,Tlay2,xlay2);
	gridisland_lay2(lp,0,Tlay2);//0 grid,1 island
	allconstraint_lay2_islandp(lp,Tlay2);
	int rnum=0;
	punishrelative=0;
	VIRTUALlevelIdentifier();
	for(int Ix=1;Ix<mglevel;Ix++)
	{
	for(int Iy=0;Iy<mglevelnum[Ix];Iy++)
	{
	//VIRTUALGRIDconstraint(lp,Tlay2,mglevel-Ix,Iy+1);
	VIRTUALGRIDconstraint(lp,Tlay2,mglevel-Ix,Iy);
	punishrelative +=relativetemp;
			rnum++;
	}
	}/**/
	if(rnum==0)
	{rnum=1;}
	punishrelative=punishrelative/rnum;
	object_lay2_levelp(lp,0,x,Tlay2);//0 grid,1 island
	set_add_rowmode(lp, FALSE);
	set_scaling(lp, SCALE_MEAN);
	set_break_at_first(lp, TRUE);//找到的第一个解
	solvestate=solveit(lp);
	//cout<<"solvestate:"<<solvestate<<endl;
	//write_lp(lp,"lpp.lp");
	if(solvestate==0||solvestate==1)
	{
		scheduletodispachgriddata_lay2(lp,Tlay2);
		getobject_lay2(Tlay2,xlay2);//get object result
		lay2tototaldata_lay2(Tlay2,xlay2);
	}
	delete_lp(lp);

	if(solvestate!=0&&solvestate!=1)
	{
		lprec *lp;
		lpprepare_levelp_islandp(Tlay2);
		lp=make_lp(0,valurearrayall);
		set_add_rowmode(lp,TRUE);
		//totaltolay2_data(Tlay2,xlay2);
		initlpsolve_lay2(lp,Tlay2);
		//getlossa();
		//set_obj(lp,10,24/T);
		//setchangeinit_lay2(xlay2);//order of lay2
		setmodelinit_lay2(lp,Tlay2,xlay2);
		gridisland_lay2(lp,0,Tlay2);//0 grid,1 island
		allconstraint_lay2_islandp(lp,Tlay2);
		int rnum=0;
		punishrelative=0;
		VIRTUALlevelIdentifier();
		for(int Ix=1;Ix<mglevel;Ix++)
		{
		for(int Iy=0;Iy<mglevelnum[Ix];Iy++)
		{
		//VIRTUALGRIDconstraint(lp,Tlay2,mglevel-Ix,Iy+1);
		VIRTUALGRIDconstraint(lp,Tlay2,mglevel-Ix,Iy);
		punishrelative +=relativetemp;
				rnum++;
		}
		}/**/
		if(rnum==0)
		{rnum=1;}
		punishrelative=punishrelative/rnum;
		object_lay2_levelp(lp,0,x,Tlay2);//0 grid,1 island
		set_add_rowmode(lp, FALSE);
		set_scaling(lp, SCALE_MEAN);
		set_break_at_first(lp, TRUE);//找到的第一个解
		solvestate=solveit(lp);
		//write_lp(lp,"lpp.lp");
		scheduletodispachgriddata_lay2(lp,Tlay2);
		getobject_lay2(Tlay2,xlay2);//get object result
		lay2tototaldata_lay2(Tlay2,xlay2);
		delete_lp(lp);
	}
}

void SCHEDULE::schedulislanddo_levelp(int x)
{
	lprec *lp;
	lpprepare_levelp(T);
	lp=make_lp(0,valurearrayall);
	set_add_rowmode(lp,TRUE);
	cyclecost();
	errorcalculate();
	initlpsolve(lp);
	setchangeinit();
	gridisland(lp,1);//0 grid,1 island
	allconstraint(lp,x);//?
	VIRTUALlevelIdentifier();
	int rnum=0;
	punishrelative=0;
	for(int Ix=1;Ix<mglevel;Ix++)  //mglevel
	{
		for(int Iy=0;Iy<mglevelnum[Ix];Iy++)
		{
			VIRTUALGRIDconstraint(lp,T,mglevel-Ix,Iy);
			punishrelative +=relativetemp;
			rnum++;
		}
	}
	if(rnum==0)
	{rnum=1;}
	punishrelative=punishrelative/rnum;/**/
	punishrelative=1;
	getloadcut(lp);
	object_levelp(lp,1,x);//0 grid,1 island//?
	//set_obj(lp,10,1);
	set_add_rowmode(lp, FALSE);
	//set_scaling(lp, SCALE_MEAN);
	set_break_at_first(lp, TRUE);//找到的第一个解
	solvestate=solveit(lp);
	//cout<<"solvestate:"<<solvestate<<endl;
	//write_lp(lp,"lp.lp");
	scheduletodispachislanddata(lp);
	//outputtxt();
	delete_lp(lp);

	if(solvestate!=0&&solvestate!=1)
	{
		lprec *lp;
		lpprepare_levelp(T);
		lp=make_lp(0,valurearrayall);
		set_add_rowmode(lp,TRUE);
		//cyclecost();
		//errorcalculate();
		initlpsolve(lp);
		//setchangeinit();
		gridisland(lp,1);//0 grid,1 island
		allconstraint(lp,x);//?
		VIRTUALlevelIdentifier();
		int rnum=0;
		punishrelative=0;
		for(int Ix=1;Ix<mglevel-1;Ix++)  //mglevel
		{
			for(int Iy=0;Iy<mglevelnum[Ix];Iy++)
			{
				VIRTUALGRIDconstraint(lp,T,mglevel-Ix,Iy);
				punishrelative +=relativetemp;
				rnum++;
			}
		}
		if(rnum==0)
		{rnum=1;}
		punishrelative=punishrelative/rnum;/**/
		punishrelative=1;
		getloadcut(lp);
		object_levelp(lp,1,x);//0 grid,1 island//?
		//set_obj(lp,10,1);
		set_add_rowmode(lp, FALSE);
		//set_scaling(lp, SCALE_MEAN);
		set_break_at_first(lp, TRUE);//找到的第一个解
		solvestate=solveit(lp);
		//cout<<"solvestate:"<<solvestate<<endl;
		//write_lp(lp,"lp.lp");
		scheduletodispachislanddata(lp);
		//outputtxt();
		delete_lp(lp);
		if(solvestate!=0&&solvestate!=1&&x==0)
		{
			lprec *lp;
			lpprepare_levelp(T);
			lp=make_lp(0,valurearrayall);
			set_add_rowmode(lp,TRUE);
			//cyclecost();
			//errorcalculate();
			initlpsolve(lp);
			//setchangeinit();
			gridisland(lp,1);//0 grid,1 island
			allconstraint(lp,x);//?
			VIRTUALlevelIdentifier();
			punishrelative=1;
			getloadcut(lp);
			object_levelp(lp,1,x);//0 grid,1 island//?
			set_add_rowmode(lp, FALSE);
			//set_scaling(lp, SCALE_MEAN);
			set_break_at_first(lp, TRUE);//找到的第一个解
			solvestate=solveit(lp);
			//cout<<"solvestate:"<<solvestate<<endl;
			//write_lp(lp,"lp.lp");
			scheduletodispachislanddata(lp);
			//outputtxt();
			delete_lp(lp);
		}
	}

}

void SCHEDULE::schedulislanddolay2_levelp(int x,int xlay2)
{
	lprec *lp;
	lpprepare_levelp_islandp(Tlay2);
	lp=make_lp(0,valurearrayall);
	set_add_rowmode(lp,TRUE);
	totaltolay2_data(Tlay2,xlay2);
	initlpsolve_lay2(lp,Tlay2);
	//getlossa();
	setchangeinit_lay2(xlay2);//order of lay2
	//setmodelinit_lay2(lp,Tlay2,xlay2);
	int rnum=0;
	switch(x)
	{
	case 0:
		setmodelinit_lay2(lp,Tlay2,xlay2);

		gridisland_lay2(lp,1,Tlay2);//0 grid,1 island
		allconstraint_lay2_islandp(lp,Tlay2);
		VIRTUALlevelIdentifier();
		punishrelative=0;
		rnum=0;
		for(int Ix=1;Ix<mglevel;Ix++)
		{
			for(int Iy=0;Iy<mglevelnum[Ix];Iy++)
			{
				//VIRTUALGRIDconstraint(lp,Tlay2,mglevel-Ix,Iy+1);
				VIRTUALGRIDconstraint(lp,Tlay2,mglevel-Ix,Iy);
				punishrelative +=relativetemp;
				rnum++;
			}
		}
		if(rnum==0)
		{rnum=1;}
		punishrelative=punishrelative/rnum;

		object_lay2_levelp(lp,1,x,Tlay2);//0 grid,1 island
		set_add_rowmode(lp, FALSE);
		//set_scaling(lp, SCALE_MEAN);
		set_break_at_first(lp, TRUE);//找到的第一个解
		solvestate=solveit(lp);
		//cout<<"solvestate:"<<solvestate<<endl;
		//write_lp(lp,"lplay2.lp");
		if(solvestate==0||solvestate==1)
		{
			scheduletodispachislanddata_lay2(lp,Tlay2);
			getobject_lay2(Tlay2,xlay2);//get object result
			lay2tototaldata_lay2(Tlay2,xlay2);
		}
		delete_lp(lp);
		if(solvestate!=0&&solvestate!=1)
		{
			lprec *lp;
			lpprepare_levelp_islandp(Tlay2);
			lp=make_lp(0,valurearrayall);
			set_add_rowmode(lp,TRUE);
			//totaltolay2_data(Tlay2,xlay2);
			initlpsolve_lay2(lp,Tlay2);
			//getlossa();
			//setchangeinit_lay2(xlay2);//order of lay2
			setmodelinit_lay2(lp,Tlay2,xlay2);

			gridisland_lay2(lp,1,Tlay2);//0 grid,1 island
			allconstraint_lay2_islandp(lp,Tlay2);
			VIRTUALlevelIdentifier();
			punishrelative=0;
			rnum=0;
			for(int Ix=1;Ix<mglevel-1;Ix++)
			{
				for(int Iy=0;Iy<mglevelnum[Ix];Iy++)
				{
					//VIRTUALGRIDconstraint(lp,Tlay2,mglevel-Ix,Iy+1);
					VIRTUALGRIDconstraint(lp,Tlay2,mglevel-Ix,Iy);
					punishrelative +=relativetemp;
					rnum++;
				}
			}
			if(rnum==0)
			{rnum=1;}
			punishrelative=punishrelative/rnum;

			object_lay2_levelp(lp,1,x,Tlay2);//0 grid,1 island
			set_add_rowmode(lp, FALSE);
			//set_scaling(lp, SCALE_MEAN);
			set_break_at_first(lp, TRUE);//找到的第一个解
			solvestate=solveit(lp);
			//cout<<"solvestate:"<<solvestate<<endl;
			//write_lp(lp,"lplay2.lp");
			if(solvestate==0||solvestate==1)
			{
				scheduletodispachislanddata_lay2(lp,Tlay2);
				getobject_lay2(Tlay2,xlay2);//get object result
				lay2tototaldata_lay2(Tlay2,xlay2);
			}
			delete_lp(lp);
		}
		break;
	case 1:
		setmodelinit1_lay2(lp,Tlay2,xlay2);

		gridisland_lay2(lp,1,Tlay2);//0 grid,1 island
		allconstraint_lay2_islandp(lp,Tlay2);
		punishrelative=1;

		VIRTUALlevelIdentifier();
		punishrelative=0;
		rnum=0;
		for(int Ix=1;Ix<mglevel;Ix++)
		{
			for(int Iy=0;Iy<mglevelnum[Ix];Iy++)
			{
				//VIRTUALGRIDconstraint(lp,Tlay2,mglevel-Ix,Iy+1);
				VIRTUALGRIDconstraint(lp,Tlay2,mglevel-Ix,Iy);
				punishrelative +=relativetemp;
				rnum++;
			}
		}
		if(rnum==0)
		{rnum=1;punishrelative=1;}
		punishrelative=punishrelative/rnum;/**/

		object_lay2_levelp(lp,1,x,Tlay2);//0 grid,1 island
		set_add_rowmode(lp, FALSE);
		//set_scaling(lp, SCALE_MEAN);
		set_break_at_first(lp, TRUE);//找到的第一个解
		solvestate=solveit(lp);
		//write_lp(lp,"lplay2.lp");
		if(solvestate==0||solvestate==1)
		{
			scheduletodispachislanddata_lay2(lp,Tlay2);
			getobject_lay2(Tlay2,xlay2);//get object result
			lay2tototaldata_lay2(Tlay2,xlay2);
		}
		delete_lp(lp);
		if(solvestate!=0&&solvestate!=1)
		{
			lprec *lp;
			lpprepare_levelp_islandp(Tlay2);
			lp=make_lp(0,valurearrayall);
			set_add_rowmode(lp,TRUE);
			//totaltolay2_data(Tlay2,xlay2);
			initlpsolve_lay2(lp,Tlay2);
			//getlossa();
			//setchangeinit_lay2(xlay2);//order of lay2
			setmodelinit1_lay2(lp,Tlay2,xlay2);

			gridisland_lay2(lp,1,Tlay2);//0 grid,1 island
			allconstraint_lay2_islandp(lp,Tlay2);
			punishrelative=1;

			VIRTUALlevelIdentifier();
			punishrelative=0;
			rnum=0;
			for(int Ix=1;Ix<mglevel-1;Ix++)
			{
				for(int Iy=0;Iy<mglevelnum[Ix];Iy++)
				{
					//VIRTUALGRIDconstraint(lp,Tlay2,mglevel-Ix,Iy+1);
					VIRTUALGRIDconstraint(lp,Tlay2,mglevel-Ix,Iy);
					punishrelative +=relativetemp;
					rnum++;
				}
			}
			if(rnum==0)
			{rnum=1;punishrelative=1;}
			punishrelative=punishrelative/rnum;/**/

			object_lay2_levelp(lp,1,x,Tlay2);//0 grid,1 island
			set_add_rowmode(lp, FALSE);
			//set_scaling(lp, SCALE_MEAN);
			set_break_at_first(lp, TRUE);//找到的第一个解
			solvestate=solveit(lp);
			//write_lp(lp,"lplay2.lp");
			if(solvestate==0||solvestate==1)
			{
				scheduletodispachislanddata_lay2(lp,Tlay2);
				getobject_lay2(Tlay2,xlay2);//get object result
				lay2tototaldata_lay2(Tlay2,xlay2);
			}
			delete_lp(lp);
		}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	default:
		break;
	}
	
}

void SCHEDULE::islanddo_levelpunish()
{
	schedulislanddo_levelp(modeldecision);
	for(int Xlay2=0;Xlay2<T;Xlay2++)
	{
		schedulislanddolay2_levelp(modeldecision,Xlay2);
	}
	outputtxt_lay2();
	outputobject();
}
void SCHEDULE::griddo_levelpunish()
{
	schedulgriddo_levelp(modeldecision);
	for(int Xlay2=0;Xlay2<T;Xlay2++)
	{
		schedulgriddolay2_levelp(modeldecision,Xlay2);
	}
	outputtxt_lay2();
	outputobject();
}

void SCHEDULE::SumE()
{
	SumPdpt=new double[T];
	CHECKPOINTER(SumPdpt);
	SumPdp=0;
	for(int J=0;J<Ttotal;J++)
	{
		for(int I=0;I<renewableenergynum;I++)
		{
			SumPdp +=Renewableenergydata[I].PnewHttotal[J]*24/Ttotal;
		}
		for(int I=0;I<controllableunitnum;I++)
		{
			SumPdp +=Controllableunitdata[I].PHi*24/Ttotal;
		}
	}
	for(int I=0;I<loadnum;I++)
	{
		Loaddata[I].Sumload=0;
		for(int J=0;J<Ttotal;J++)
		{
			Loaddata[I].Sumload +=Loaddata[I].Pdttotal[J]*24/Ttotal;
		}
	}
	for(int J=0;J<T;J++)
	{
		SumPdpt[J]=0;
		for(int I=0;I<renewableenergynum;I++)
		{
			SumPdpt[J] +=Renewableenergydata[I].PnewHt[J]*24/T;
		}
		for(int I=0;I<controllableunitnum;I++)
		{
			SumPdpt[J] +=Controllableunitdata[I].PHi*24/T;
		}
	}
	SumVLksetschedule=0;
	SumVHksetschedule=0;
	SumEinit=0;
	SumPgH=0;
	SumPpH=0;
	Aveyitag=0;
	Aveyitap=0;
	AveCostkWh=0;
	SumWk=0;
	int temp=0;
	for(int I=0;I<energystoragenum;I++)
	{
		if((Energystoragedata[I].type/1000)%10==1)
		{
		SumVLksetschedule +=Energystoragedata[I].VLksetscheduleS;
		SumVHksetschedule +=Energystoragedata[I].VHksetscheduleS;
		if(Energystoragedata[I].Einit<Energystoragedata[I].VLksetscheduleS)
		{
			SumEinit +=Energystoragedata[I].VLksetscheduleS;
		}
		else if(Energystoragedata[I].Einit>Energystoragedata[I].VHksetscheduleS)
		{
			SumEinit +=Energystoragedata[I].VHksetscheduleS;
		}
		else
		{
			SumEinit +=Energystoragedata[I].Einit;
		}
		SumPgH +=Energystoragedata[I].PgHk;
		SumPpH +=Energystoragedata[I].PpHk;
		Aveyitag +=Energystoragedata[I].yitag;
		Aveyitap +=Energystoragedata[I].yitap;
		AveCostkWh +=Energystoragedata[I].CostkWh;
		SumWk +=Energystoragedata[I].Wk;
		}
		else
		{
			temp++;
		}
	}
	Aveyitag=Aveyitag/(energystoragenum-temp);
	Aveyitap=Aveyitap/(energystoragenum-temp);
	AveCostkWh=AveCostkWh/(energystoragenum-temp);
}
void SCHEDULE::Sum_object(lprec *lp,int y,int x)
{	
	switch(x)
	{
	case 0:
		switch(y)
		{
		case 0://grid
			break;
		case 1:	//island
			for(int I=0;I<loadnum;I++)
			{
				//set_obj(lp,I+1,Loaddata[I].Sumload*Pcutcost[Loaddata[I].level-1]);
				for(int J=0;J<T;J++)
				{
					//set_obj(lp,loadnum+I*T+J+1,Loaddata[I].Pdt[J]*Pcutcost[Loaddata[I].level-1]);

					set_obj(lp,loadnum+1*loadnum*T+I*T+J+1,0.5);//波动Pcutcost[1]/2.0
					if(Loaddata[I].level==1)
					{
						set_obj(lp,loadnum+I*T+J+1,Loaddata[I].Pdt[J]*Pcutcost[Loaddata[I].level-1]+(24.0-J)*1);//切前面的负荷代价大
					}
					else
					{
						set_obj(lp,loadnum+I*T+J+1,Loaddata[I].Pdt[J]*Pcutcost[Loaddata[I].level-1]);
					}
				}
			}
			for(int J=0;J<T;J++)
			{
				set_obj(lp,loadnum+(loadnumarray*loadnum)*T+J+1,AveCostkWh*24.0/T/Aveyitag);
				set_obj(lp,loadnum+(loadnumarray*loadnum)*T+1*T+J+1,AveCostkWh*24.0/T*Aveyitap);
			}
				set_obj(lp,loadnum+(loadnumarray*loadnum)*T+6*T+0+1,(Pcutcost[0]+Pcutcost[1])/2.0);//

			break;
		default:
			break;
		}break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	default:
		break;
	}

}
void SCHEDULE::Sum_lpprepare()
{
	loadnumarray=2;
	energystoragenumarray=5+2;//
	valurearrayall=loadnum+(loadnumarray*loadnum)*T+energystoragenumarray*T;
}
void SCHEDULE::Sum_initlpsolve(lprec *lp)
{
	for(int I=0;I<loadnum;I++)
	{
		set_binary(lp, I+1, TRUE);
		for(int J=0;J<T;J++)
		{
			set_binary(lp, loadnum+I*T+J+1, TRUE);
		}
	}
	for(int J=0;J<T;J++)
	{
		set_binary(lp, loadnum+(loadnumarray*loadnum)*T+2*T+J+1, TRUE);
		set_binary(lp, loadnum+(loadnumarray*loadnum)*T+3*T+J+1, TRUE);
	}
}
void SCHEDULE::Sum_constraint(lprec *lp)
{
	int colno1[1];
	double row1[1];
	int colno2[2];
	double row2[2];
	int colno3[3];
	double row3[3];
	int colno4[4];
	double row4[4];
	int colno5[5];
	double row5[5];
	int* colnosump;
	double* rowsump;
	int* colnosumpt;
	double* rowsumpt;
	int* colnosumcut;
	double* rowsumcut;
	colnosump=new int[loadnum];
	CHECKPOINTER(colnosump);
	rowsump=new double[loadnum];
	CHECKPOINTER(rowsump);
	colnosumpt=new int[loadnum+2];
	CHECKPOINTER(colnosumpt);
	rowsumpt=new double[loadnum+2];
	CHECKPOINTER(rowsumpt);
	colnosumcut=new int[T-1];
	CHECKPOINTER(colnosumcut);
	rowsumcut=new double[T-1];
	CHECKPOINTER(rowsumcut);
	double temp=0;

	for(int I=0;I<loadnum;I++)
	{	
		colnosump[I]=I+1;
		rowsump[I]=Loaddata[I].Sumload;
		temp +=Loaddata[I].Sumload;
	}
	//add_constraintex(lp, loadnum, rowsump, colnosump, GE, temp-SumPdp);//cut more
	for(int J=0;J<T;J++)
	{
		temp=0;
		for(int I=0;I<loadnum;I++)
		{
			colnosumpt[I]=loadnum+I*T+J+1;
			rowsumpt[I]=Loaddata[I].Pdt[J];
			temp +=Loaddata[I].Pdt[J];
		}
		colnosumpt[loadnum]=loadnum+(loadnumarray*loadnum)*T+J+1;
		rowsumpt[loadnum]=1;
		colnosumpt[loadnum+1]=loadnum+(loadnumarray*loadnum)*T+1*T+J+1;
		rowsumpt[loadnum+1]=-1;
		add_constraintex(lp, loadnum+2, rowsumpt, colnosumpt, GE, temp-SumPdpt[J]);//ge eq
	}

	for(int J=0;J<T;J++)
	{
		for(int I=0;I<loadnum;I++)
		{
			colno2[0]=loadnum+I*T+J+1;
			row2[0]=1;
			colno2[1]=I+1;
			row2[1]=-1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, 0);
		}
	}
	for(int I=0;I<loadnum;I++)//切负荷波动
	{
		colno2[0]=loadnum+1*loadnum*T+I*T+0+1;
		row2[0]=1;
		colno2[1]=loadnum+I*T+0+1;
		row2[1]=-1;
		add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, 0);
		for(int J=1;J<T;J++)
		{
			//model.add(Sit[I][J]>=Controllableunitdata[I].Shi*(Uit[I][J]-Uit[I][J-1]));
			colno3[0]=loadnum+1*loadnum*T+I*T+J+1;
			row3[0]=1;
			colno3[1]=loadnum+I*T+J+1;
			row3[1]=-1;
			colno3[2]=loadnum+I*T+J-1+1;
			row3[2]=1;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, GE, 0);
			colno3[0]=loadnum+1*loadnum*T+I*T+J+1;
			row3[0]=1;
			colno3[1]=loadnum+I*T+J+1;
			row3[1]=1;
			colno3[2]=loadnum+I*T+J-1+1;
			row3[2]=-1;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, GE, 0);

			colnosumcut[J-1]=loadnum+1*loadnum*T+I*T+J+1;
			rowsumcut[J-1]=1;
		}
		add_constraintex(lp, (T-1), rowsumcut, colnosumcut, LE, 2.1);
		/*if(Loaddata[I].level==1&&I<13)
		{
			for(int J=0;J<T;J++)
			{
				colno1[0]=loadnum+I*T+J+1;
				row1[0]=1;
				add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);
			}
		}*/
	}

	for(int J=0;J<T;J++)
	{
		//model.add(Ugkt[I][J]+Upkt[I][J]<=1);
		colno2[0]=loadnum+(loadnumarray*loadnum)*T+2*T+J+1;
		row2[0]=1;
		colno2[1]=loadnum+(loadnumarray*loadnum)*T+3*T+J+1;
		row2[1]=1;
		add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 1);
		//model.add(Pgkt[I][J]<=Energystoragedata[I].PgHk*Ugkt[I][J]);
		//model.add(Ppkt[I][J]<=Energystoragedata[I].PpHk*Upkt[I][J]);
		colno2[0]=loadnum+(loadnumarray*loadnum)*T+2*T+J+1;
		row2[0]=-SumPgH;
		colno2[1]=loadnum+(loadnumarray*loadnum)*T+0*T+J+1;
		row2[1]=1;
		add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
		colno2[0]=loadnum+(loadnumarray*loadnum)*T+3*T+J+1;
		row2[0]=-SumPpH;
		colno2[1]=loadnum+(loadnumarray*loadnum)*T+1*T+J+1;
		row2[1]=1;
		add_constraintex(lp, 2, row2, colno2, LE, 0);
		//model.add(Energystoragedata[I].VLksetschedule<=Vkt[I][J]);
		//model.add(Vkt[I][J]<=Energystoragedata[I].VHksetschedule);
		colno1[0]=loadnum+(loadnumarray*loadnum)*T+4*T+J+1;
		row1[0]=1;
		add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, SumVLksetschedule);
		colno1[0]=loadnum+(loadnumarray*loadnum)*T+4*T+J+1;
		row1[0]=1;
		add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, SumVHksetschedule);

		if(J>0)
		{

			//model.add(Vkt[I][J]==Vkt[I][J-1]-Pdhkt[I][J]*24/T+Pchkt[I][J]*24/T);
			colno4[0]=loadnum+(loadnumarray*loadnum)*T+4*T+J+1;
			row4[0]=-1;
			colno4[1]=loadnum+(loadnumarray*loadnum)*T+4*T+J-1+1;
			row4[1]=1;
			colno4[2]=loadnum+(loadnumarray*loadnum)*T+0*T+J+1;
			row4[2]=-24.0/T/Aveyitag;
			colno4[3]=loadnum+(loadnumarray*loadnum)*T+1*T+J+1;
			row4[3]=Aveyitap*24.0/T;
			add_constraintex(lp, sizeof(colno4) / sizeof(*colno4), row4, colno4, EQ, 0);
		}
		else
		{
			colno3[0]=loadnum+(loadnumarray*loadnum)*T+4*T+J+1;
			row3[0]=-1;
			colno3[1]=loadnum+(loadnumarray*loadnum)*T+0*T+J+1;
			row3[1]=-24.0/T/Aveyitag;
			colno3[2]=loadnum+(loadnumarray*loadnum)*T+1*T+J+1;
			row3[2]=Aveyitap*24.0/T;
			add_constraintex(lp, 3, row3, colno3, EQ, -SumEinit);
		}
	}
	//model.add(Vkt[I][T-1]-Pdhkt[I][0]*24/T+Pchkt[I][0]*24/T-Vkt[I][temp]==Energystoragedata[I].Wk);
	//Wkc
	set_lowbo(lp, loadnum+(loadnumarray*loadnum)*T+5*T+0+1, BIGNUM);
		//model.add(Vkt[I][T-1]-Pdhkt[I][0]*24/T+Pchkt[I][0]*24/T-Vkt[I][temp]==Energystoragedata[I].Wk);
		//Energystoragedata[28].Wk=0;
		colno5[0]=loadnum+(loadnumarray*loadnum)*T+4*T+T-1+1;
		row5[0]=1;
		colno5[1]=loadnum+(loadnumarray*loadnum)*T+4*T+0+1;
		row5[1]=-1;

		colno5[2]=loadnum+(loadnumarray*loadnum)*T+0*T+0+1;
		row5[2]=-24.0/T/Aveyitag;
		colno5[3]=loadnum+(loadnumarray*loadnum)*T+1*T+0+1;
		row5[3]=Aveyitap*24.0/T;
		colno5[4]=loadnum+(loadnumarray*loadnum)*T+5*T+0+1;
		row5[4]=1;
		add_constraintex(lp, sizeof(colno5) / sizeof(*colno5), row5, colno5, EQ, SumWk);

		colno2[0]=loadnum+(loadnumarray*loadnum)*T+5*T+0+1;
		row2[0]=-1;
		colno2[1]=loadnum+(loadnumarray*loadnum)*T+6*T+0+1;
		row2[1]=1;
		add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, 0);
/*
		colno4[0]=loadnum+(loadnumarray*loadnum)*T+4*T+T-1+1;
	row4[0]=1;
	colno4[1]=loadnum+(loadnumarray*loadnum)*T+4*T+0+1;
	row4[1]=-1;
	colno4[2]=loadnum+(loadnumarray*loadnum)*T+0*T+0+1;
	row4[2]=-24.0/T/Aveyitag;
	colno4[3]=loadnum+(loadnumarray*loadnum)*T+1*T+0+1;
	row4[3]=Aveyitap*24.0/T;
	add_constraintex(lp, sizeof(colno4) / sizeof(*colno4), row4, colno4, EQ, SumWk);*/

	delete[] colnosump;
	delete[] rowsump;
	delete[] colnosumpt;
	delete[] rowsumpt;
	delete[] colnosumcut;
	delete[] rowsumcut;

}
void SCHEDULE::Sum_islandschedule()
{
	for(int I=0;I<energystoragenum;I++)
	{
		if((Energystoragedata[I].type/1000)%10==1&&errorvaluemaxS<(energysumBH-energysumBL)/2&&errorvaluemaxS<(energysumBH-energysumBL)*Energystoragedata[I].VLkislandmargin)
		{
			//Energystoragedata[I].VLksetscheduleS=Energystoragedata[I].VLk+errorvaluemaxS*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
			//Energystoragedata[I].VHksetscheduleS=Energystoragedata[I].VHk-errorvaluemaxS*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
			Energystoragedata[I].VLksetscheduleS=Energystoragedata[I].VLk;
			Energystoragedata[I].VHksetscheduleS=Energystoragedata[I].VHk;

		}
		else if((Energystoragedata[I].type/1000)%10==2)
		{
			Energystoragedata[I].VLksetscheduleS=0;
			Energystoragedata[I].VHksetscheduleS=0;
		}
		else
		{
			//Energystoragedata[I].VLksetscheduleS=Energystoragedata[I].VLk+Energystoragedata[I].VLkislandmargin*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
			//Energystoragedata[I].VHksetscheduleS=Energystoragedata[I].VHk-Energystoragedata[I].VHkislandmargin*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
			Energystoragedata[I].VLksetscheduleS=Energystoragedata[I].VLk;
			Energystoragedata[I].VHksetscheduleS=Energystoragedata[I].VHk;
		}
	}
}
void SCHEDULE::Sum_Odata(lprec *lp)
{
	double* outputrow;
	outputrow=new double[valurearrayall];
	CHECKPOINTER(outputrow);
	get_variables(lp,outputrow);
	get_objective(lp);
	//cout<<"object"<<get_objective(lp)<<endl;
	double vkt[24];
	for(int I=0;I<loadnum;I++)
	{
		Loaddata[I].Uscut=outputrow[I];
		for(int J=0;J<T;J++)
		{
			Loaddata[I].Ucutx[J]=outputrow[loadnum+I*T+J];
		}
	}
	for(int J=0;J<T;J++)
	{
		vkt[J]=outputrow[loadnum+(loadnumarray*loadnum)*T+4*T+J];
	}
	delete[] outputrow;
	delete[] SumPdpt;
}
void SCHEDULE::Sum_do(int x)
{
	lprec *lp;
	cyclecost();
	errorcalculate();
	setchangeinit();
	Sum_islandschedule();
	SumE();
	Sum_lpprepare();
	lp=make_lp(0,valurearrayall);
	set_add_rowmode(lp,TRUE);
	Sum_initlpsolve(lp);
	Sum_object(lp,1,x);//0 grid,1 island
	Sum_constraint(lp);
	set_add_rowmode(lp, FALSE);
	//set_scaling(lp, SCALE_MEAN);
	//set_presolve(lp, PRESOLVE_LINDEP , get_presolveloops(lp));
	//set_solutionlimit(lp, 1); 
	//set_solutionlimit(lp, 2); 
	//set_bb_floorfirst(lp, BRANCH_CEILING); 
	//set_bb_floorfirst(lp, BRANCH_FLOOR);
	//set_presolve(lp, PRESOLVE_ROWS | PRESOLVE_COLS | PRESOLVE_LINDEP, get_presolveloops(lp));//预处理
	set_break_at_first(lp, TRUE);//找到的第一个解
	//set_bb_rule(lp, NODE_PSEUDONONINTSELECT);
	//set_simplextype(lp, SIMPLEX_PRIMAL_PRIMAL);
	solveit(lp);
	//write_lp(lp,"lpsum.lp");
	Sum_Odata(lp);
	delete_lp(lp);
}
void SCHEDULE::getloadcut(lprec *lp)
{
	int colno1[1];
	double row1[1];
	int colno3[3];
	double row3[3];
	int* colnosumcut;
	double* rowsumcut;
	colnosumcut=new int[T-1];
	CHECKPOINTER(colnosumcut);
	rowsumcut=new double[T-1];
	CHECKPOINTER(rowsumcut);
	for(int I=0;I<loadnum;I++)
	{
		for(int J=0;J<T;J++)
		{
			colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
				+renewableenergynumarray*renewableenergynum*T+I*T+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, Loaddata[I].Ucutx[J]);//Loaddata[I].Ucutx[J]
			/*colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
				+renewableenergynumarray*renewableenergynum*T+16*T+0+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);//Loaddata[I].Ucutx[J]*/
		}
	}
	/*for(int I=0;I<loadnum;I++)
	{
		for(int J=11;J<16;J++)
		{
				colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+I*T+J+1;
				row1[0]=1;
				add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Loaddata[I].Ucutx[J]);//Loaddata[I].Ucutx[J]
		}
	}*/
	for(int I=0;I<loadnum;I++)//切负荷波动
	{
		for(int J=1;J<T;J++)
		{
			//model.add(Sit[I][J]>=Controllableunitdata[I].Shi*(Uit[I][J]-Uit[I][J-1]));
			//model.add(Sit[I][0]>=Controllableunitdata[I].Shi*(Uit[I][0]-Controllableunitdata[I].Uinit));
			colno3[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
				+renewableenergynumarray*renewableenergynum*T+loadnum*T+I*T+J+1;
			row3[0]=1;
			colno3[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
				+renewableenergynumarray*renewableenergynum*T+I*T+J+1;
			row3[1]=-1;
			colno3[2]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
				+renewableenergynumarray*renewableenergynum*T+I*T+J;
			row3[2]=1;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, GE, 0);
			colno3[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
				+renewableenergynumarray*renewableenergynum*T+loadnum*T+I*T+J+1;
			row3[0]=1;
			colno3[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
				+renewableenergynumarray*renewableenergynum*T+I*T+J+1;
			row3[1]=1;
			colno3[2]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
				+renewableenergynumarray*renewableenergynum*T+I*T+J;
			row3[2]=-1;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, GE, 0);

			colnosumcut[J-1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
				+renewableenergynumarray*renewableenergynum*T+loadnum*T+I*T+J+1;
			rowsumcut[J-1]=1;
		}
		if(modeldecision==0)
		{
			add_constraintex(lp, (T-1), rowsumcut, colnosumcut, LE, 3.1);
		}
	}
	delete[] colnosumcut;
	delete[] rowsumcut;
}

int SCHEDULE::solveit(lprec *lp)
{
	int solvestateh=0;
	//print_lp(lp);
	//set_bb_depthlimit(lp, 0.1);
	set_mip_gap(lp, TRUE, 0.1); //误差
	set_timeout(lp, 160);
	//set_verbose(lp, IMPORTANT);
	set_verbose(lp, CRITICAL);
	solvestateh=solve(lp);
	return solvestateh;
}

void SCHEDULE::lpprepare_levelp(int Ttemp)
{
	onearray=10;
	controllableunitnumarray=11;
	energystoragenumarray=11+2;
	renewableenergynumarray=1+1;
	loadnumarray=2;//add
	virtualnumarray=2;//add
	lossnumarray=1;//add
	valurearrayall=(onearray+(controllableunitnumarray-2)*controllableunitnum+(node+node-1)*controllableunitnum
		+energystoragenumarray*energystoragenum+renewableenergynumarray*renewableenergynum+loadnumarray*loadnum+virtualloadnum*virtualnumarray)*Ttemp
		+lossnumarray*(controllableunitnum+energystoragenum+renewableenergynum+loadnum+virtualloadnum+1)*Ttemp+Ttemp;
}
void SCHEDULE::lpprepare_levelp_islandp(int Ttemp)
{
	onearray=10;
	controllableunitnumarray=11;
	energystoragenumarray=11+2;
	renewableenergynumarray=1+1;
	loadnumarray=2;//add
	virtualnumarray=2;//add
	lossnumarray=1;//add
	valurearrayall=(onearray+(controllableunitnumarray-2)*controllableunitnum+(node+node-1)*controllableunitnum
		+energystoragenumarray*energystoragenum+renewableenergynumarray*renewableenergynum+loadnumarray*loadnum+virtualloadnum*virtualnumarray)*Ttemp+loadnum
		+lossnumarray*(controllableunitnum+energystoragenum+renewableenergynum+loadnum+virtualloadnum+1)*Ttemp+Ttemp+Ttemp;//?loadnum 
}


void SCHEDULE::allconstraint(lprec *lp,int x)//y=0yuanlai
{
	CONTROLLABLEUNITconstraint(lp);
	CONTROLLABLEUNITconsumptionsimplify(lp);
	ENERGYSTORAGEconstraint(lp,x);
	RENEWABLEENERGYconstraint(lp);
	OVERALLBALANCEconstraint(lp);
	LOSSconstraint(lp);
}

void SCHEDULE::allconstraint_lay2_islandp(lprec *lp,int Ttemp)//y=0yuanlai
{
	CONTROLLABLEUNITconstraint_lay2(lp,Ttemp);
	CONTROLLABLEUNITconsumptionsimplify_lay2(lp,Ttemp);
	ENERGYSTORAGEconstraint_lay2_islandp(lp,Ttemp);
	RENEWABLEENERGYconstraint_lay2_islandp(lp,Ttemp);
	OVERALLBALANCEconstraint_lay2(lp,Ttemp);
	LOSSconstraint_lay2(lp,Ttemp);
}
void SCHEDULE::initlpsolve(lprec *lp)
{
	for(int J=0;J<T;J++)
	{
		set_int(lp,4*T+J+1,TRUE);
		set_upbo(lp,4*T+J+1,1);
		set_int(lp,5*T+J+1,TRUE);
		set_upbo(lp,5*T+J+1,1);
		set_int(lp,8*T+J+1,TRUE);
		set_upbo(lp,8*T+J+1,1);
		set_int(lp,9*T+J+1,TRUE);
		set_upbo(lp,9*T+J+1,1);
	}
	for(int J=0;J<T;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			set_int(lp,onearray*T+4*controllableunitnum*T+I*T+J+1,TRUE);
			set_upbo(lp,onearray*T+4*controllableunitnum*T+I*T+J+1,1);
			set_int(lp,onearray*T+7*controllableunitnum*T+I*T+J+1,TRUE);
			set_upbo(lp,onearray*T+7*controllableunitnum*T+I*T+J+1,1);
			set_int(lp,onearray*T+8*controllableunitnum*T+I*T+J+1,TRUE);
			set_upbo(lp,onearray*T+8*controllableunitnum*T+I*T+J+1,1);
			for(int I1=0;I1<node;I1++)
			{
				//set_upbo(lp,onearray*T+(controllableunitnumarray-2)*controllableunitnum*T+I1*controllableunitnum*T+I*T+J+1,1);
				set_upbo(lp,onearray*T+(controllableunitnumarray-2)*controllableunitnum*T+I*node*T+I1*T+J+1,1);
			}
			for(int I1=0;I1<node-1;I1++)
			{
				//set_int(lp,onearray*T+(controllableunitnumarray-2+node)*controllableunitnum*T+I1*controllableunitnum*T+I*T+J+1,TRUE);
				//set_upbo(lp,onearray*T+(controllableunitnumarray-2+node)*controllableunitnum*T+I1*controllableunitnum*T+I*T+J+1,1);
				//onearray*T+(controllableunitnumarray-2)*controllableunitnum*T+node*controllableunitnum*T+I*(node-1)*T+I1*T+J+1
				//set_int(lp,onearray*T+(controllableunitnumarray-2+node)*controllableunitnum*T+I*(node-1)*T+I1*T+J+1,TRUE);
				//set_upbo(lp,onearray*T+(controllableunitnumarray-2+node)*controllableunitnum*T+I*(node-1)*T+I1*T+J+1,1);
				set_binary(lp, onearray*T+(controllableunitnumarray-2+node)*controllableunitnum*T+I*(node-1)*T+I1*T+J+1, TRUE);
			}
		}
	}
	for(int J=0;J<T;J++)
	{
		for(int I=0;I<energystoragenum;I++)
		{
			set_int(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+7*energystoragenum*T+I*T+J+1,TRUE);
			set_upbo(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+7*energystoragenum*T+I*T+J+1,1);
			set_int(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+8*energystoragenum*T+I*T+J+1,TRUE);
			set_upbo(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+8*energystoragenum*T+I*T+J+1,1);
			set_int(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+9*energystoragenum*T+I*T+J+1,TRUE);
			set_upbo(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+9*energystoragenum*T+I*T+J+1,1);
			set_int(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+10*energystoragenum*T+I*T+J+1,TRUE);
			set_upbo(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+10*energystoragenum*T+I*T+J+1,1);
		}
	}
	for(int J=0;J<T;J++)
	{
		for(int I=0;I<loadnum;I++)
		{
			set_int(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynumarray*renewableenergynum*T+I*T+J+1,TRUE);
			set_upbo(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynumarray*renewableenergynum*T+I*T+J+1,1);
			set_binary(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynumarray*renewableenergynum*T+loadnum*T+I*T+J+1,TRUE);
			//set_upbo(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynumarray*renewableenergynum*T+loadnum*T+I*T+J+1,1);
			//set_int(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynumarray*renewableenergynum*T+loadnum*T+I*T+J+1,TRUE);
			//set_upbo(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynumarray*renewableenergynum*T+loadnum*T+I*T+J+1,0);
		}
	}
	for(int J=0;J<T;J++)
	{
		set_lowbo(lp, J+1, BIGNUM);
	}

}
void SCHEDULE::initlpsolve_lay2(lprec *lp,int Ttemp)
{
	for(int J=0;J<Ttemp;J++)
	{
		set_int(lp,4*Ttemp+J+1,TRUE);
		set_upbo(lp,4*Ttemp+J+1,1);
		set_int(lp,5*Ttemp+J+1,TRUE);
		set_upbo(lp,5*Ttemp+J+1,1);
		set_int(lp,8*Ttemp+J+1,TRUE);
		set_upbo(lp,8*Ttemp+J+1,1);
		set_int(lp,9*Ttemp+J+1,TRUE);
		set_upbo(lp,9*Ttemp+J+1,1);
	}
	for(int J=0;J<Ttemp;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			set_int(lp,onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J+1,TRUE);
			set_upbo(lp,onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J+1,1);
			set_int(lp,onearray*Ttemp+7*controllableunitnum*Ttemp+I*Ttemp+J+1,TRUE);
			set_upbo(lp,onearray*Ttemp+7*controllableunitnum*Ttemp+I*Ttemp+J+1,1);
			set_int(lp,onearray*Ttemp+8*controllableunitnum*Ttemp+I*Ttemp+J+1,TRUE);
			set_upbo(lp,onearray*Ttemp+8*controllableunitnum*Ttemp+I*Ttemp+J+1,1);
			for(int I1=0;I1<node;I1++)
			{
				//set_upbo(lp,onearray*T+(controllableunitnumarray-2)*controllableunitnum*T+I1*controllableunitnum*T+I*T+J+1,1);
				set_upbo(lp,onearray*Ttemp+(controllableunitnumarray-2)*controllableunitnum*Ttemp+I*node*Ttemp+I1*Ttemp+J+1,1);
			}
			for(int I1=0;I1<node-1;I1++)
			{
				//set_int(lp,onearray*T+(controllableunitnumarray-2+node)*controllableunitnum*T+I1*controllableunitnum*T+I*T+J+1,TRUE);
				//set_upbo(lp,onearray*T+(controllableunitnumarray-2+node)*controllableunitnum*T+I1*controllableunitnum*T+I*T+J+1,1);
				//onearray*T+(controllableunitnumarray-2)*controllableunitnum*T+node*controllableunitnum*T+I*(node-1)*T+I1*T+J+1
				//set_int(lp,onearray*T+(controllableunitnumarray-2+node)*controllableunitnum*T+I*(node-1)*T+I1*T+J+1,TRUE);
				//set_upbo(lp,onearray*T+(controllableunitnumarray-2+node)*controllableunitnum*T+I*(node-1)*T+I1*T+J+1,1);
				set_binary(lp, onearray*Ttemp+(controllableunitnumarray-2+node)*controllableunitnum*Ttemp+I*(node-1)*Ttemp+I1*Ttemp+J+1, TRUE);
			}
		}
	}
	for(int J=0;J<Ttemp;J++)
	{
		for(int I=0;I<energystoragenum;I++)
		{
			set_int(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+7*energystoragenum*Ttemp+I*Ttemp+J+1,TRUE);
			set_upbo(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+7*energystoragenum*Ttemp+I*Ttemp+J+1,1);
			set_int(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+8*energystoragenum*Ttemp+I*Ttemp+J+1,TRUE);
			set_upbo(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+8*energystoragenum*Ttemp+I*Ttemp+J+1,1);
			set_int(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+9*energystoragenum*Ttemp+I*Ttemp+J+1,TRUE);
			set_upbo(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+9*energystoragenum*Ttemp+I*Ttemp+J+1,1);
			set_int(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+10*energystoragenum*Ttemp+I*Ttemp+J+1,TRUE);
			set_upbo(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+10*energystoragenum*Ttemp+I*Ttemp+J+1,1);
		}
	}
	for(int J=0;J<Ttemp;J++)
	{
		for(int I=0;I<loadnum;I++)
		{
			set_int(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1,TRUE);
			set_upbo(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1,1);
		}
	}
	for(int J=0;J<Ttemp;J++)
	{
		set_lowbo(lp, J+1, BIGNUM);
	}

}

void SCHEDULE::object_levelp(lprec *lp,int y,int x)
{
	for(int J=0;J<T;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//obj1 +=Cit[I][J]*24/T+Sit[I][J]+Controllableunitdata[I].COM*Pit[I][J]*24/T+Controllableunitdata[I].CDP*Pit[I][J]*24/T+Controllableunitdata[I].CE*Pit[I][J]*24/T;
			set_obj(lp,onearray*T+2*controllableunitnum*T+I*T+J+1,24.0/T);
			set_obj(lp,onearray*T+3*controllableunitnum*T+I*T+J+1,1);
			set_obj(lp,onearray*T+0*controllableunitnum*T+I*T+J+1,(Controllableunitdata[I].COM+Controllableunitdata[I].CDP+Controllableunitdata[I].CE)*24.0/T);
			//cout<<(Controllableunitdata[I].COM+Controllableunitdata[I].CDP+Controllableunitdata[I].CE)*24.0/T<<endl;
			if(J>0)
			{
				//obj1 +=Controllableunitdata[I].Ramp*Pitdeltp[I][J]+Controllableunitdata[I].Ramp*Pitdeltm[I][J];
				set_obj(lp,onearray*T+5*controllableunitnum*T+I*T+J+1,Controllableunitdata[I].Ramp);
				set_obj(lp,onearray*T+6*controllableunitnum*T+I*T+J+1,Controllableunitdata[I].Ramp);
			}
		}

		for(int I=0;I<energystoragenum;I++)
		{
			set_obj(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+1*energystoragenum*T+I*T+J+1,Energystoragedata[I].CostkWh*24.0/T/Energystoragedata[I].yitag);
			set_obj(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+J+1,Energystoragedata[I].CostkWh*24.0/T*Energystoragedata[I].yitap);
		}/**/
	
	}
	switch(x)
	{
	case 0:
		switch(y)
		{
		case 0:
			//obj=IloMinimize(env,obj4); 
			for(int J=0;J<T;J++)
			{
				//set_obj(lp,2*T+J+1,(Griddata.Buy[J]+CEgrid)*24.0/T);
				//set_obj(lp,3*T+J+1,(-Griddata.Sell[J]-CEgrid)*24.0/T);
				//set_obj(lp,2*T+J+1,CEgrid*24.0/T);
				//set_obj(lp,3*T+J+1,-CEgrid*24.0/T);
				set_obj(lp,2*T+J+1,Griddata.Buy[J]*24.0/T);
				set_obj(lp,3*T+J+1,-Griddata.Sell[J]*24.0/T);
				if(J>0)
				{
					set_obj(lp,6*T+J+1,Griddata.Ramp);
					set_obj(lp,7*T+J+1,Griddata.Ramp);
				}
				for(int I=0;I<virtualloadnum;I++)
				{
					set_obj(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualloadnum*T+I*T+J+1,(Griddata.Ramp+SMALLNUM)*0.1/punishrelative*24.0/T);
				}
			}
			
			break;
		case 1:	
			//obj=IloMinimize(env,obj5); 
			for(int J=0;J<T;J++)
			{
				//set_obj(lp,1*T+J+1,24.0/T);
				for(int I=0;I<loadnum;I++)
				{
					if(Loaddata[I].level==1)
					{
						set_obj(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynumarray*renewableenergynum*T+I*T+J+1,Loaddata[I].Pdt[J]*Pcutcost[Loaddata[I].level-1]*24.0/T+(24.0-J)*1.0*2); //
					}
					else
					{
						set_obj(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynumarray*renewableenergynum*T+I*T+J+1,Loaddata[I].Pdt[J]*Pcutcost[Loaddata[I].level-1]*24.0/T);
					}
				}
				
				for(int I=0;I<virtualloadnum;I++)
				{
					set_obj(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualloadnum*T+I*T+J+1,(Griddata.Ramp+SMALLNUM)*0.1/punishrelative*24.0/T);
				}
				for(int I=0;I<loadnum;I++)
				{
					set_obj(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynumarray*renewableenergynum*T+loadnum*T+I*T+J+1,0.5*0.1);//切负荷波动Pcutcost[1]
					if(Loaddata[I].level==1)
					{
						//set_obj(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynumarray*renewableenergynum*T+I*T+J+1,(24.0-J)*1.0*2);//切前面的负荷代价大
					}
				}
				for(int I=0;I<renewableenergynum;I++)
				{
					set_obj(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynum*T+I*T+J+1,Pcutcost[0]*24.0/T);
				}
			}
			for(int I=0;I<energystoragenum;I++)
			{
				set_obj(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+12*energystoragenum*T+I*T+0+1,(Pcutcost[0]+Pcutcost[1])/2.0);//
			}/**/
			
			break;
		default:
			break;
		}break;
	case 1:
		switch(y)
		{
		case 0:
			//obj=IloMinimize(env,obj4); 
			for(int J=0;J<T;J++)
			{
				//set_obj(lp,2*T+J+1,(Griddata.Buy[J]+CEgrid)*24.0/T);
				//set_obj(lp,3*T+J+1,(-Griddata.Sell[J]-CEgrid)*24.0/T);
				//set_obj(lp,2*T+J+1,CEgrid*24.0/T);
				//set_obj(lp,3*T+J+1,-CEgrid*24.0/T);
				set_obj(lp,2*T+J+1,Griddata.Buy[J]*24.0/T);
				set_obj(lp,3*T+J+1,-Griddata.Sell[J]*24.0/T);
				if(J>0)
				{
					set_obj(lp,6*T+J+1,Griddata.Ramp);
					set_obj(lp,7*T+J+1,Griddata.Ramp);
				}
				for(int I=0;I<virtualloadnum;I++)
				{
					set_obj(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualloadnum*T+I*T+J+1,(Griddata.Ramp+SMALLNUM)*0.1/punishrelative*24.0/T);
				}
			}
			
			break;
		case 1:	
			//obj=IloMinimize(env,obj5); 
			for(int J=0;J<T;J++)
			{
				set_obj(lp,1*T+J+1,24.0/T);
				set_obj(lp,1*T+J+1,(24.0-J)*2.0);//切前面的负荷代价大
				for(int I=0;I<virtualloadnum;I++)
				{
					set_obj(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualloadnum*T+I*T+J+1,(Griddata.Ramp+SMALLNUM)*0.1/punishrelative*24.0/T);
				}
				for(int I=0;I<loadnum;I++)
				{
					set_obj(lp,onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynumarray*renewableenergynum*T+loadnum*T+I*T+J+1,Pcutcost[1]);//切负荷波动
				}/**/
			}
			break;
		default:
			break;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	default:
		break;
	}

}
void SCHEDULE::object_lay2_levelp(lprec *lp,int y,int x,int Ttemp)
{
	double Punishbase=0;
	double Punishunit=0;
	for(int J=0;J<Ttemp;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//obj1 +=Cit[I][J]*24/T+Sit[I][J]+Controllableunitdata[I].COM*Pit[I][J]*24/T+Controllableunitdata[I].CDP*Pit[I][J]*24/T+Controllableunitdata[I].CE*Pit[I][J]*24/T;
			set_obj(lp,onearray*Ttemp+2*controllableunitnum*Ttemp+I*Ttemp+J+1,1.0/Ttemp);
			set_obj(lp,onearray*Ttemp+3*controllableunitnum*Ttemp+I*Ttemp+J+1,1);
			set_obj(lp,onearray*Ttemp+0*controllableunitnum*Ttemp+I*Ttemp+J+1,(Controllableunitdata[I].COM+Controllableunitdata[I].CDP+Controllableunitdata[I].CE)*1.0/Ttemp);
			if(J>0)
			{
				//obj1 +=Controllableunitdata[I].Ramp*Pitdeltp[I][J]+Controllableunitdata[I].Ramp*Pitdeltm[I][J];
				set_obj(lp,onearray*Ttemp+5*controllableunitnum*Ttemp+I*Ttemp+J+1,Controllableunitdata[I].Ramp);
				set_obj(lp,onearray*Ttemp+6*controllableunitnum*Ttemp+I*Ttemp+J+1,Controllableunitdata[I].Ramp);
			}
		}
		for(int I=0;I<energystoragenum;I++)
		{
			//obj6 +=CostkWh[I]*Pdhkt[I][J]*24/T+CostkWh[I]*Pchkt[I][J]*24/T;
			set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+1*energystoragenum*Ttemp+I*Ttemp+J+1,Energystoragedata[I].CostkWh*1.0/Ttemp/Energystoragedata[I].yitag);
			set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+2*energystoragenum*Ttemp+I*Ttemp+J+1,Energystoragedata[I].CostkWh*1.0/Ttemp*Energystoragedata[I].yitap);
		}
		if(J>0)
		{
			//obj7 +=Griddata.Ramp*Pdtdeltp[J]+Griddata.Ramp*Pdtdeltm[J];
			//set_obj(lp,6*T+J+1,Griddata.Ramp);
			//set_obj(lp,7*T+J+1,Griddata.Ramp);
		}
		//set_obj(lp,onearray*T+0*controllableunitnum*T+0*T+J+1,24/T);
	}
	//obj4=obj1+obj2+obj6+obj7+obj10;//grid
	//obj5=obj1+obj3+obj6;//island
	switch(x)
	{
	case 0:
		switch(y)
		{
		case 0:
			//obj=IloMinimize(env,obj4); 
			for(int J=0;J<Ttemp;J++)
			{
				//set_obj(lp,2*T+J+1,(Griddata.Buy[J]+CEgrid)*24.0/T);
				//set_obj(lp,3*T+J+1,(-Griddata.Sell[J]-CEgrid)*24.0/T);
				//set_obj(lp,2*T+J+1,CEgrid*24.0/T);
				//set_obj(lp,3*T+J+1,-CEgrid*24.0/T);
				set_obj(lp,2*Ttemp+J+1,Griddata.Buylay2[J]*1.0/Ttemp);
				set_obj(lp,3*Ttemp+J+1,-Griddata.Selllay2[J]*1.0/Ttemp);
				if(J>0)
				{
					set_obj(lp,6*Ttemp+J+1,Griddata.Ramp);
					set_obj(lp,7*Ttemp+J+1,Griddata.Ramp);
				}
				for(int I=0;I<virtualloadnum;I++)
				{
					set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualloadnum*Ttemp+I*Ttemp+J+1,(Griddata.Ramp+SMALLNUM)*0.1*1.0/Ttemp);//0.01
				}
			}

			Punishbase=Griddata.Buylay2[0];
			for(int J=0;J<Tlay2;J++)
			{
				if(Punishbase<Griddata.Buylay2[J])
				{
					Punishbase=Griddata.Buylay2[J];
				}
			}
			for(int J=0;J<Ttemp;J++)
			{
				//set_obj(lp,1*Ttemp+J+1,1.0/Ttemp);
				for(int I=0;I<virtualloadnum;I++)
				{
					//set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualloadnum*Ttemp+I*Ttemp+J+1,Griddata.Ramp*0.1/punishrelative*1.0/Ttemp);
				}
				for(int I=0;I<renewableenergynum;I++)
				{
					set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynum*Ttemp+I*Ttemp+J+1,4*Punishbase*1.0/Ttemp);
				}
			}
			for(int I=0;I<energystoragenum;I++)
			{
				set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+12*energystoragenum*Ttemp+I*Ttemp+0+1,2.5*Punishbase);
				//set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+11*energystoragenum*Ttemp+I*Ttemp+0+1,2.5*Energystoragedata[I].CostkWh);
				
			}
			for(int I=0;I<loadnum;I++)
			{
				//set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualloadnum*2*Ttemp+I+1,1.0);
			}
			break;
		case 1:	
			//obj=IloMinimize(env,obj5); 
			for(int I=0;I<energystoragenum;I++)
			{
				Punishbase +=Energystoragedata[I].CostkWh;
			}
			Punishbase=Punishbase/energystoragenum;
			for(int I=0;I<controllableunitnum;I++)
			{
				if(Punishunit<(Controllableunitdata[I].ci[node-1]-Controllableunitdata[I].ci[0])/(Controllableunitdata[I].Pi[node-1]-Controllableunitdata[I].Pi[0]))
				{
					Punishunit=(Controllableunitdata[I].ci[node-1]-Controllableunitdata[I].ci[0])/(Controllableunitdata[I].Pi[node-1]-Controllableunitdata[I].Pi[0]);
				}
			}
			for(int J=0;J<Ttemp;J++)
			{
				set_obj(lp,1*Ttemp+J+1,1.0/Ttemp);
				for(int I=0;I<virtualloadnum;I++)
				{
					//set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualloadnum*Ttemp+I*Ttemp+J+1,(Griddata.Ramp+SMALLNUM)/punishrelative*1.0/Ttemp);//绝对值惩罚项改为相对值*0.1
				}
				for(int I=0;I<renewableenergynum;I++)
				{
					set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynum*Ttemp+I*Ttemp+J+1,4*Punishbase*1.0/Ttemp);
				}
				//duoyu
				set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
							+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualnumarray*virtualloadnum*Ttemp+loadnum
							+controllableunitnum*Ttemp+energystoragenum*Ttemp+renewableenergynum*Ttemp+loadnum*Ttemp+virtualloadnum*Ttemp+Ttemp*2+J+1,2*Punishbase*1.0/Ttemp);
			}
			for(int I=0;I<energystoragenum;I++)
			{
				if(Punishunit>Energystoragedata[I].CostkWh)
				{
					set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+12*energystoragenum*Ttemp+I*Ttemp+0+1,0.5*Punishunit);
					set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+11*energystoragenum*Ttemp+I*Ttemp+0+1,0.55*Punishunit); //2.5 
				}
				else
				{
					set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+12*energystoragenum*Ttemp+I*Ttemp+0+1,1*Energystoragedata[I].CostkWh);
					set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+11*energystoragenum*Ttemp+I*Ttemp+0+1,2.5*Energystoragedata[I].CostkWh); //2.5 
				}
			}
			for(int I=0;I<loadnum;I++)
			{
				set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualloadnum*2*Ttemp+I+1,2.0*5);
			}
			break;
		default:
			break;
		}break;
	case 1:
		switch(y)
		{
		case 0:
			//obj=IloMinimize(env,obj4); 
			for(int J=0;J<Ttemp;J++)
			{
				//set_obj(lp,2*T+J+1,(Griddata.Buy[J]+CEgrid)*24.0/T);
				//set_obj(lp,3*T+J+1,(-Griddata.Sell[J]-CEgrid)*24.0/T);
				//set_obj(lp,2*T+J+1,CEgrid*24.0/T);
				//set_obj(lp,3*T+J+1,-CEgrid*24.0/T);
				set_obj(lp,2*Ttemp+J+1,Griddata.Buylay2[J]*1.0/Ttemp);
				set_obj(lp,3*Ttemp+J+1,-Griddata.Selllay2[J]*1.0/Ttemp);
				if(J>0)
				{
					set_obj(lp,6*Ttemp+J+1,Griddata.Ramp);
					set_obj(lp,7*Ttemp+J+1,Griddata.Ramp);
				}
				for(int I=0;I<virtualloadnum;I++)
				{
					set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualloadnum*Ttemp+I*Ttemp+J+1,(Griddata.Ramp+SMALLNUM)*0.1*1.0/Ttemp);//0.01
				}
			}

			Punishbase=Griddata.Buylay2[0];
			for(int J=0;J<Tlay2;J++)
			{
				if(Punishbase<Griddata.Buylay2[J])
				{
					Punishbase=Griddata.Buylay2[J];
				}
			}
			for(int J=0;J<Ttemp;J++)
			{
				//set_obj(lp,1*Ttemp+J+1,1.0/Ttemp);
				for(int I=0;I<virtualloadnum;I++)
				{
					//set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualloadnum*Ttemp+I*Ttemp+J+1,Griddata.Ramp*0.1/punishrelative*1.0/Ttemp);
				}
				for(int I=0;I<renewableenergynum;I++)
				{
					set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynum*Ttemp+I*Ttemp+J+1,4*Punishbase*1.0/Ttemp);
				}
			}
			for(int I=0;I<energystoragenum;I++)
			{
				set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+12*energystoragenum*Ttemp+I*Ttemp+0+1,2.5*Punishbase);
			}
			for(int I=0;I<loadnum;I++)
			{
				//set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualloadnum*2*Ttemp+I+1,1.0);
			}
			break;
		case 1:	
			//obj=IloMinimize(env,obj5); 
			for(int I=0;I<energystoragenum;I++)
			{
				Punishbase +=Energystoragedata[I].CostkWh;
			}
			Punishbase=Punishbase/energystoragenum;
			for(int I=0;I<controllableunitnum;I++)
			{
				if(Punishunit<(Controllableunitdata[I].ci[node-1]-Controllableunitdata[I].ci[0])/(Controllableunitdata[I].Pi[node-1]-Controllableunitdata[I].Pi[0]))
				{
					Punishunit=(Controllableunitdata[I].ci[node-1]-Controllableunitdata[I].ci[0])/(Controllableunitdata[I].Pi[node-1]-Controllableunitdata[I].Pi[0]);
				}
			}
			for(int J=0;J<Ttemp;J++)
			{
				set_obj(lp,1*Ttemp+J+1,1.0/Ttemp);
				for(int I=0;I<virtualloadnum;I++)
				{
					set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualloadnum*Ttemp+I*Ttemp+J+1,(Griddata.Ramp+SMALLNUM)/punishrelative*1.0/Ttemp);//绝对值惩罚项改为相对值*0.1
				}
				for(int I=0;I<renewableenergynum;I++)
				{
					set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynum*Ttemp+I*Ttemp+J+1,4*Punishbase*1.0/Ttemp);
				}
				//duoyu
				set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
							+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualnumarray*virtualloadnum*Ttemp+loadnum
							+controllableunitnum*Ttemp+energystoragenum*Ttemp+renewableenergynum*Ttemp+loadnum*Ttemp+virtualloadnum*Ttemp+Ttemp*2+J+1,4.5*Punishbase*1.0/Ttemp);
			}
			for(int I=0;I<energystoragenum;I++)
			{
				if(Punishunit>Energystoragedata[I].CostkWh)
				{
					set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+12*energystoragenum*Ttemp+I*Ttemp+0+1,0.5*Punishunit);
					set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+11*energystoragenum*Ttemp+I*Ttemp+0+1,0.55*Punishunit); 
				}
				else
				{
					set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+12*energystoragenum*Ttemp+I*Ttemp+0+1,1*Energystoragedata[I].CostkWh);
					set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+11*energystoragenum*Ttemp+I*Ttemp+0+1,2.5*Energystoragedata[I].CostkWh); //2.2 
				}
			}
			for(int I=0;I<loadnum;I++)
			{
				set_obj(lp,onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualloadnum*2*Ttemp+I+1,1.0);
			}/**/
			break;
		default:
			break;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	default:
		break;
	}

}

void SCHEDULE::gridisland(lprec *lp,int y)
{
	int colno1[1];
	double row1[1];
	switch(y)
	{
	case 0:
		//Grid.constraint(model,Griddata,Pd1t,T,Pbuyt,Psellt,Ubuyt,Usellt,Pdt,Pdtdeltp,Pdtdeltm,Udtdeltp,Udtdeltm);
		GRIDconstraint(lp);
		for(int J=0;J<T;J++)
		{
			for(int I=0;I<energystoragenum;I++)
			{
				/*Energystoragedata[I].outlimitLtime=0;
				Energystoragedata[I].outlimitHtime=0;
				Energystoragedata[I].outlimitLdemical=0;
				Energystoragedata[I].outlimitHdemical=0;*/
				if((Energystoragedata[I].type/1000)%10==1&&errorvalue[J]<(energysumBH-energysumBL)/2&&errorvalue[J]<(energysumBH-energysumBL)*Energystoragedata[I].VLkgridmargin&&errorvalue[J]<(energysumBH-energysumBL)*Energystoragedata[I].VHkgridmargin)
				{
					Energystoragedata[I].VLksetschedule[J]=Energystoragedata[I].VLk+errorvalue[J]*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
					Energystoragedata[I].VHksetschedule[J]=Energystoragedata[I].VHk-errorvalue[J]*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
					if (errorvalue[J]/(energysumBH-energysumBL)<Energystoragedata[I].VLkgridMARGINLIMIT)
					{
						Energystoragedata[I].VLksetschedule[J]=Energystoragedata[I].VLk+Energystoragedata[I].VLkgridMARGINLIMIT*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
						//Energystoragedata[I].VHksetschedule[J]=Energystoragedata[I].VHk-Energystoragedata[I].VHkgridMARGINLIMIT*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
					}
					if (errorvalue[J]/(energysumBH-energysumBL)<Energystoragedata[I].VHkgridMARGINLIMIT)
					{
						//Energystoragedata[I].VLksetschedule[J]=Energystoragedata[I].VLk+Energystoragedata[I].VLkgridMARGINLIMIT*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
						Energystoragedata[I].VHksetschedule[J]=Energystoragedata[I].VHk-Energystoragedata[I].VHkgridMARGINLIMIT*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
					}
				}
				else if((Energystoragedata[I].type/1000)%10==2)
				{
					Energystoragedata[I].VLksetschedule[J]=Energystoragedata[I].VLk;
					Energystoragedata[I].VHksetschedule[J]=Energystoragedata[I].VHk;
					//for(int J=0;J<T;J++)
					//{
						//model.add(Ugkt[I][J]==0);
						//model.add(Upkt[I][J]==0);
						colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+7*energystoragenum*T+I*T+J+1;
						row1[0]=1;
						add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);
						colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+8*energystoragenum*T+I*T+J+1;
						row1[0]=1;
						add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);
					//}
				}
				else
				{
					Energystoragedata[I].VLksetschedule[J]=Energystoragedata[I].VLk+errorvalue[J]*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
					Energystoragedata[I].VHksetschedule[J]=Energystoragedata[I].VHk-errorvalue[J]*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
					if(errorvalue[J]>=(energysumBH-energysumBL)*Energystoragedata[I].VLkgridmargin)
					{
						Energystoragedata[I].VLksetschedule[J]=Energystoragedata[I].VLk+Energystoragedata[I].VLkgridmargin*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
					}
					if(errorvalue[J]>=(energysumBH-energysumBL)*Energystoragedata[I].VHkgridmargin)
					{
						Energystoragedata[I].VHksetschedule[J]=Energystoragedata[I].VHk-Energystoragedata[I].VHkgridmargin*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
					}
				}
				//cout<<Energystoragedata[I].outlimitLdemical<<endl;
			}
		}

		for(int I=0;I<energystoragenum;I++)
		{
			Energystoragedata[I].outlimitLtime=0;
			Energystoragedata[I].outlimitHtime=0;
			Energystoragedata[I].outlimitLdemical=0;
			Energystoragedata[I].outlimitHdemical=0;
			if(Energystoragedata[I].VLksetschedule[0]-Energystoragedata[I].Einit>Energystoragedata[I].PpHk*Energystoragedata[I].yitap*24/T)
			{
				Energystoragedata[I].outlimitLtime=1;
				Energystoragedata[I].outlimitHtime=0;
				int Jw=1;
				while(Energystoragedata[I].VLksetschedule[Jw]-Energystoragedata[I].Einit>Energystoragedata[I].PpHk*Energystoragedata[I].yitap*24/T*(1+Jw)&&Jw<T)
				{
					Energystoragedata[I].outlimitLtime++;
					Jw++;
				}

			}
			else if(Energystoragedata[I].Einit-Energystoragedata[I].VHksetschedule[0]>Energystoragedata[I].PgHk/Energystoragedata[I].yitag*24/T)
			{
				Energystoragedata[I].outlimitHtime=1;
				Energystoragedata[I].outlimitLtime=0;
				int Jw=1;
				while(Energystoragedata[I].Einit-Energystoragedata[I].VHksetschedule[Jw]>Energystoragedata[I].PgHk/Energystoragedata[I].yitag*24/T*(1+Jw)&&Jw<T)
				{
					Energystoragedata[I].outlimitHtime++;
					Jw++;
				}
				
			}
			Energystoragedata[I].outlimitLdemical=((Energystoragedata[I].VLksetschedule[0]-Energystoragedata[I].Einit)/(Energystoragedata[I].PpHk*Energystoragedata[I].yitap*24/T));
			Energystoragedata[I].outlimitHdemical=(Energystoragedata[I].Einit-Energystoragedata[I].VHksetschedule[0])/(Energystoragedata[I].PgHk/Energystoragedata[I].yitag*24/T);
			//cout<<Energystoragedata[I].outlimitLtime<<" "<<Energystoragedata[I].outlimitLdemical<<" ";
		}

		break;
	case 1:	//孤网
		for(int J=0;J<T;J++)
		{
			//r1[J]=IloRange(env,0,Pdt[J],Pd1t[J]);
			colno1[0]=J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
			colno1[0]=J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, Pd1t[J]);
		}
		for(int J=0;J<T;J++)
		{
			for(int I=0;I<energystoragenum;I++)
			{
				Energystoragedata[I].outlimitLtime=0;
				Energystoragedata[I].outlimitHtime=0;
				Energystoragedata[I].outlimitLdemical=0;
				Energystoragedata[I].outlimitHdemical=0;
				if((Energystoragedata[I].type/1000)%10==1&&errorvalue[J]<(energysumBH-energysumBL)/2&&errorvalue[J]<(energysumBH-energysumBL)*Energystoragedata[I].VLkislandmargin&&errorvalue[J]<(energysumBH-energysumBL)*Energystoragedata[I].VHkislandmargin)
				{
					Energystoragedata[I].VLksetschedule[J]=Energystoragedata[I].VLk+errorvalue[J]*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
					Energystoragedata[I].VHksetschedule[J]=Energystoragedata[I].VHk-errorvalue[J]*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
					if (errorvalue[J]/(energysumBH-energysumBL)<Energystoragedata[I].VLkislandMARGINLIMIT)
					{
						Energystoragedata[I].VLksetschedule[J]=Energystoragedata[I].VLk+Energystoragedata[I].VLkislandMARGINLIMIT*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
						//Energystoragedata[I].VHksetschedule[J]=Energystoragedata[I].VHk-Energystoragedata[I].VHkislandMARGINLIMIT*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
					}
					if (errorvalue[J]/(energysumBH-energysumBL)<Energystoragedata[I].VHkislandMARGINLIMIT)
					{
						//Energystoragedata[I].VLksetschedule[J]=Energystoragedata[I].VLk+Energystoragedata[I].VLkislandMARGINLIMIT*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
						Energystoragedata[I].VHksetschedule[J]=Energystoragedata[I].VHk-Energystoragedata[I].VHkislandMARGINLIMIT*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
					}
				}
				else if((Energystoragedata[I].type/1000)%10==2)
				{
					Energystoragedata[I].VLksetschedule[J]=Energystoragedata[I].VLk;
					Energystoragedata[I].VHksetschedule[J]=Energystoragedata[I].VHk;
					//for(int J=0;J<T;J++)
					//{
						//model.add(Ugkt[I][J]==0);
						//model.add(Upkt[I][J]==0);
						colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+7*energystoragenum*T+I*T+J+1;
						row1[0]=1;
						add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);
						colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+8*energystoragenum*T+I*T+J+1;
						row1[0]=1;
						add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);
					//}
				}
				else
				{
					Energystoragedata[I].VLksetschedule[J]=Energystoragedata[I].VLk+errorvalue[J]*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
					Energystoragedata[I].VHksetschedule[J]=Energystoragedata[I].VHk-errorvalue[J]*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
					if(errorvalue[J]>=(energysumBH-energysumBL)*Energystoragedata[I].VLkislandmargin)
					{
						Energystoragedata[I].VLksetschedule[J]=Energystoragedata[I].VLk+Energystoragedata[I].VLkislandmargin*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
					}
					if(errorvalue[J]>=(energysumBH-energysumBL)*Energystoragedata[I].VHkislandmargin)
					{
						Energystoragedata[I].VHksetschedule[J]=Energystoragedata[I].VHk-Energystoragedata[I].VHkislandmargin*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
					}
					
				}
				//cout<<Energystoragedata[I].VLksetschedule[J]<<" "<<Energystoragedata[I].VHksetschedule[J]<<" ";
			}
		}
		for(int I=0;I<energystoragenum;I++)
		{
			if(Energystoragedata[I].VLksetschedule[0]-Energystoragedata[I].Einit>Energystoragedata[I].PpHk*Energystoragedata[I].yitap*24/T)
			{
				Energystoragedata[I].outlimitLtime=1;
				Energystoragedata[I].outlimitHtime=0;
				int Jw=1;
				while(Energystoragedata[I].VLksetschedule[Jw]-Energystoragedata[I].Einit>Energystoragedata[I].PpHk*Energystoragedata[I].yitap*24/T*(1+Jw)&&Jw<T)
				{
					Energystoragedata[I].outlimitLtime++;
					Jw++;
				}

			}
			else if(Energystoragedata[I].Einit-Energystoragedata[I].VHksetschedule[0]>Energystoragedata[I].PgHk/Energystoragedata[I].yitag*24/T)
			{
				Energystoragedata[I].outlimitHtime=1;
				Energystoragedata[I].outlimitLtime=0;
				int Jw=1;
				while(Energystoragedata[I].Einit-Energystoragedata[I].VHksetschedule[Jw]>Energystoragedata[I].PgHk/Energystoragedata[I].yitag*24/T*(1+Jw)&&Jw<T)
				{
					Energystoragedata[I].outlimitHtime++;
					Jw++;
				}
				
			}
			Energystoragedata[I].outlimitLdemical=((Energystoragedata[I].VLksetschedule[0]-Energystoragedata[I].Einit)/(Energystoragedata[I].PpHk*Energystoragedata[I].yitap*24/T));
			Energystoragedata[I].outlimitHdemical=(Energystoragedata[I].Einit-Energystoragedata[I].VHksetschedule[0])/(Energystoragedata[I].PgHk/Energystoragedata[I].yitag*24/T);
		}

		int *colno2;
		double *row2;
		int *colno3;
		double *row3;
		colno2=new int[loadnum+1];
		CHECKPOINTER(colno2);
		row2=new double[loadnum+1];
		CHECKPOINTER(row2);
		colno3=new int[loadnum+1];
		CHECKPOINTER(colno3);
		row3=new double[loadnum+1];
		CHECKPOINTER(row3);
		//int hehe[6];

		for(int J=0;J<T;J++)
		{
			for(int I=0;I<loadnum;I++)
			{
				//Pcuthandel +=Loaddata[I].Pdt[J]*Ucutx[I][J];//没有设定Pcutx时间I,J
				//Pcutcosthandel +=Loaddata[I].Pdt[J]*Ucutx[I][J]*Pcutcost[Loaddata[I].level];//
				colno2[I]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+I*T+J+1;
				row2[I]=Loaddata[I].Pdt[J];
				colno3[I]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+I*T+J+1;
				row3[I]=Loaddata[I].Pdt[J]*Pcutcost[Loaddata[I].level-1];
				//cout<<Loaddata[I].Pdt[J]*Pcutcost[Loaddata[I].level]<<endl;
			}
			colno2[loadnum]=J+1;
			row2[loadnum]=1;
			colno3[loadnum]=1*T+J+1;
			row3[loadnum]=-1;

			//add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, Pd1t[J]);
			add_constraintex(lp, loadnum+1, row2, colno2, EQ, Pd1t[J]);
			//add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, EQ, 0);
			add_constraintex(lp, loadnum+1, row3, colno3, EQ, 0);
			//model.add(Pd1t[J]-Pdt[J]==Pcuthandel);
			//model.add(Pcutxt[J]==Pcutcosthandel);
		}
		delete[] colno2;
		delete[] row2;
		delete[] colno3;
		delete[] row3;
		//jiaohuangonglv 
		for(int J=0;J<T;J++)
		{
			Pbuytout[J]=0;
			Pselltout[J]=0;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}		
}

void SCHEDULE::gridisland_lay2(lprec *lp,int y,int Ttemp)
{
	int colno1[1];
	double row1[1];
	switch(y)
	{
	case 0:
		GRIDconstraint_lay2(lp,Ttemp);
		for(int J=0;J<Ttemp;J++)
		{
			for(int I=0;I<energystoragenum;I++)
			{
				Energystoragedata[I].outlimitLtime=0;
				Energystoragedata[I].outlimitHtime=0;
				Energystoragedata[I].outlimitLdemical=0;
				Energystoragedata[I].outlimitHdemical=0;
				if((Energystoragedata[I].type/1000)%10==1&&errorvaluelay2[J]<(energysumBH-energysumBL)/2&&errorvaluelay2[J]<(energysumBH-energysumBL)*Energystoragedata[I].VLkgridmargin&&errorvaluelay2[J]<(energysumBH-energysumBL)*Energystoragedata[I].VHkgridmargin)
				{
					Energystoragedata[I].VLksetschedulelay2[J]=Energystoragedata[I].VLk+errorvaluelay2[J]*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
					Energystoragedata[I].VHksetschedulelay2[J]=Energystoragedata[I].VHk-errorvaluelay2[J]*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
					if (errorvaluelay2[J]/(energysumBH-energysumBL)<Energystoragedata[I].VLkgridMARGINLIMIT)
					{
						Energystoragedata[I].VLksetschedulelay2[J]=Energystoragedata[I].VLk+Energystoragedata[I].VLkgridMARGINLIMIT*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
						//Energystoragedata[I].VHksetschedulelay2[J]=Energystoragedata[I].VHk-Energystoragedata[I].VHkgridMARGINLIMIT*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
					}
					if (errorvaluelay2[J]/(energysumBH-energysumBL)<Energystoragedata[I].VHkgridMARGINLIMIT)
					{
						//Energystoragedata[I].VLksetschedulelay2[J]=Energystoragedata[I].VLk+Energystoragedata[I].VLkgridMARGINLIMIT*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
						Energystoragedata[I].VHksetschedulelay2[J]=Energystoragedata[I].VHk-Energystoragedata[I].VHkgridMARGINLIMIT*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
					}
				}
				else if((Energystoragedata[I].type/1000)%10==2)
				{
					Energystoragedata[I].VLksetschedulelay2[J]=Energystoragedata[I].VLk;
					Energystoragedata[I].VHksetschedulelay2[J]=Energystoragedata[I].VHk;
					//for(int J=0;J<T;J++)
					//{
						//model.add(Ugkt[I][J]==0);
						//model.add(Upkt[I][J]==0);
						colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+7*energystoragenum*Ttemp+I*Ttemp+J+1;
						row1[0]=1;
						add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);
						colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+8*energystoragenum*Ttemp+I*Ttemp+J+1;
						row1[0]=1;
						add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);
					//}
				}
				else
				{
					Energystoragedata[I].VLksetschedulelay2[J]=Energystoragedata[I].VLk+errorvaluelay2[J]*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
					Energystoragedata[I].VHksetschedulelay2[J]=Energystoragedata[I].VHk-errorvaluelay2[J]*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
					if(errorvaluelay2[J]>=(energysumBH-energysumBL)*Energystoragedata[I].VLkgridmargin)
					{
						Energystoragedata[I].VLksetschedulelay2[J]=Energystoragedata[I].VLk+Energystoragedata[I].VLkgridmargin*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
					}
					if(errorvaluelay2[J]>=(energysumBH-energysumBL)*Energystoragedata[I].VHkgridmargin)
					{
						Energystoragedata[I].VHksetschedulelay2[J]=Energystoragedata[I].VHk-Energystoragedata[I].VHkgridmargin*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
					}
					
				}
				//cout<<Energystoragedata[I].outlimitLdemical<<endl;
			}
		}
		for(int I=0;I<energystoragenum;I++)
		{
			if(Energystoragedata[I].VLksetschedulelay2[0]-Energystoragedata[I].Einit>Energystoragedata[I].PpHk*Energystoragedata[I].yitap*1/Ttemp)
			{
				Energystoragedata[I].outlimitLtime=1;
				Energystoragedata[I].outlimitHtime=0;
				int Jw=1;
				while(Energystoragedata[I].VLksetschedulelay2[Jw]-Energystoragedata[I].Einit>Energystoragedata[I].PpHk*Energystoragedata[I].yitap*1/Ttemp*(1+Jw)&&Jw<Ttemp)
				{
					Energystoragedata[I].outlimitLtime++;
					Jw++;
				}

			}
			else if(Energystoragedata[I].Einit-Energystoragedata[I].VHksetschedulelay2[0]>Energystoragedata[I].PgHk/Energystoragedata[I].yitag*1/Ttemp)
			{
				Energystoragedata[I].outlimitHtime=1;
				Energystoragedata[I].outlimitLtime=0;
				int Jw=1;
				while(Energystoragedata[I].Einit-Energystoragedata[I].VHksetschedulelay2[Jw]>Energystoragedata[I].PgHk/Energystoragedata[I].yitag*1/Ttemp*(1+Jw)&&Jw<Ttemp)
				{
					Energystoragedata[I].outlimitHtime++;
					Jw++;
				}
				
			}
			Energystoragedata[I].outlimitLdemical=((Energystoragedata[I].VLksetschedulelay2[0]-Energystoragedata[I].Einit)/(Energystoragedata[I].PpHk*Energystoragedata[I].yitap*1/Ttemp));
			Energystoragedata[I].outlimitHdemical=(Energystoragedata[I].Einit-Energystoragedata[I].VHksetschedulelay2[0])/(Energystoragedata[I].PgHk/Energystoragedata[I].yitag*1/Ttemp);
		}

		/*
		for(int I=0;I<energystoragenum;I++)
		{
			Energystoragedata[I].outlimitLtime=0;
			Energystoragedata[I].outlimitHtime=0;
			Energystoragedata[I].outlimitLdemical=0;
			Energystoragedata[I].outlimitHdemical=0;
			if((Energystoragedata[I].type/1000)%10 ==1)
			{
				if(Energystoragedata[I].VLksetschedule-Energystoragedata[I].Einit>Energystoragedata[I].PpHk*Energystoragedata[I].yitap*1/Ttemp)
				{
					Energystoragedata[I].outlimitLtime=(int)(Energystoragedata[I].VLksetschedule-Energystoragedata[I].Einit)/(Energystoragedata[I].PpHk*Energystoragedata[I].yitap*1/Ttemp);
					Energystoragedata[I].outlimitHtime=0;
				}
				else if(Energystoragedata[I].Einit-Energystoragedata[I].VHksetschedule>Energystoragedata[I].PgHk/Energystoragedata[I].yitag*1/Ttemp)
				{
					Energystoragedata[I].outlimitHtime=(int)(Energystoragedata[I].Einit-Energystoragedata[I].VHksetschedule)/(Energystoragedata[I].PgHk/Energystoragedata[I].yitag*1/Ttemp);
					Energystoragedata[I].outlimitLtime=0;
				}
				Energystoragedata[I].outlimitLdemical=((Energystoragedata[I].VLksetschedule-Energystoragedata[I].Einit)/(Energystoragedata[I].PpHk*Energystoragedata[I].yitap*1/Ttemp));
				Energystoragedata[I].outlimitHdemical=(Energystoragedata[I].Einit-Energystoragedata[I].VHksetschedule)/(Energystoragedata[I].PgHk/Energystoragedata[I].yitag*1/Ttemp);
			}
			else
			{
				for(int J=0;J<Ttemp;J++)
				{
					colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+7*energystoragenum*Ttemp+I*Ttemp+J+1;
					row1[0]=1;
					add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);
					colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+8*energystoragenum*Ttemp+I*Ttemp+J+1;
					row1[0]=1;
					add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);
				}
			}
		}*/

		break;
	case 1:	//孤网
		/*for(int J=0;J<Ttemp;J++)
		{
		//r1[J]=IloRange(env,0,Pdt[J],Pd1t[J]);
		colno1[0]=J+1;
		row1[0]=1;
		add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
		colno1[0]=J+1;
		row1[0]=1;
		add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, Pd1tlay2[J]);
		}*/
		for(int J=0;J<Ttemp;J++)
		{
			for(int I=0;I<energystoragenum;I++)
			{
				Energystoragedata[I].outlimitLtime=0;
				Energystoragedata[I].outlimitHtime=0;
				Energystoragedata[I].outlimitLdemical=0;
				Energystoragedata[I].outlimitHdemical=0;
				if((Energystoragedata[I].type/1000)%10==1&&errorvaluelay2[J]<(energysumBH-energysumBL)/2&&errorvaluelay2[J]<(energysumBH-energysumBL)*Energystoragedata[I].VLkislandmargin&&errorvaluelay2[J]<(energysumBH-energysumBL)*Energystoragedata[I].VHkislandmargin)
				{
					Energystoragedata[I].VLksetschedulelay2[J]=Energystoragedata[I].VLk+errorvaluelay2[J]*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
					Energystoragedata[I].VHksetschedulelay2[J]=Energystoragedata[I].VHk-errorvaluelay2[J]*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
					if (errorvaluelay2[J]/(energysumBH-energysumBL)<Energystoragedata[I].VLkislandMARGINLIMIT)
					{
						Energystoragedata[I].VLksetschedulelay2[J]=Energystoragedata[I].VLk+Energystoragedata[I].VLkislandMARGINLIMIT*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
						//Energystoragedata[I].VHksetschedulelay2[J]=Energystoragedata[I].VHk-Energystoragedata[I].VHkislandMARGINLIMIT*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
					}
					if (errorvaluelay2[J]/(energysumBH-energysumBL)<Energystoragedata[I].VHkislandMARGINLIMIT)
					{
						//Energystoragedata[I].VLksetschedulelay2[J]=Energystoragedata[I].VLk+Energystoragedata[I].VLkislandMARGINLIMIT*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
						Energystoragedata[I].VHksetschedulelay2[J]=Energystoragedata[I].VHk-Energystoragedata[I].VHkislandMARGINLIMIT*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
					}
				}
				else if((Energystoragedata[I].type/1000)%10==2)
				{
					Energystoragedata[I].VLksetschedulelay2[J]=Energystoragedata[I].VLk;
					Energystoragedata[I].VHksetschedulelay2[J]=Energystoragedata[I].VHk;
					//for(int J=0;J<T;J++)
					//{
						//model.add(Ugkt[I][J]==0);
						//model.add(Upkt[I][J]==0);
						colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+7*energystoragenum*Ttemp+I*Ttemp+J+1;
						row1[0]=1;
						add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);
						colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+8*energystoragenum*Ttemp+I*Ttemp+J+1;
						row1[0]=1;
						add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);
					//}
				}
				else
				{
					Energystoragedata[I].VLksetschedulelay2[J]=Energystoragedata[I].VLk+errorvaluelay2[J]*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
					Energystoragedata[I].VHksetschedulelay2[J]=Energystoragedata[I].VHk-errorvaluelay2[J]*(Energystoragedata[I].VHk-Energystoragedata[I].VLk)/(energysumBH-energysumBL);
					if(errorvaluelay2[J]>=(energysumBH-energysumBL)*Energystoragedata[I].VLkislandmargin)
					{
						Energystoragedata[I].VLksetschedulelay2[J]=Energystoragedata[I].VLk+Energystoragedata[I].VLkislandmargin*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
					}
					if(errorvaluelay2[J]>=(energysumBH-energysumBL)*Energystoragedata[I].VHkislandmargin)
					{
						Energystoragedata[I].VHksetschedulelay2[J]=Energystoragedata[I].VHk-Energystoragedata[I].VHkislandmargin*(Energystoragedata[I].VHk-Energystoragedata[I].VLk);
					}
				}
				//cout<<Energystoragedata[I].outlimitLdemical<<endl;
				//hehe
				Energystoragedata[I].VLksetschedulelay2[J]=Energystoragedata[I].VLksetschedulelay2[J]-(Energystoragedata[I].VLksetschedulelay2[J]-Energystoragedata[I].VLk)*0;//松弛
				Energystoragedata[I].VHksetschedulelay2[J]=Energystoragedata[I].VHksetschedulelay2[J]+(Energystoragedata[I].VHk-Energystoragedata[I].VHksetschedulelay2[J])*0;
			}
		}
		for(int I=0;I<energystoragenum;I++)
		{
			if(Energystoragedata[I].VLksetschedulelay2[0]-Energystoragedata[I].Einit>Energystoragedata[I].PpHk*Energystoragedata[I].yitap*1/Ttemp)
			{
				Energystoragedata[I].outlimitLtime=1;
				Energystoragedata[I].outlimitHtime=0;
				int Jw=1;
				while(Energystoragedata[I].VLksetschedulelay2[Jw]-Energystoragedata[I].Einit>Energystoragedata[I].PpHk*Energystoragedata[I].yitap*1/Ttemp*(1+Jw)&&Jw<Ttemp)
				{
					Energystoragedata[I].outlimitLtime++;
					Jw++;
				}

			}
			else if(Energystoragedata[I].Einit-Energystoragedata[I].VHksetschedulelay2[0]>Energystoragedata[I].PgHk/Energystoragedata[I].yitag*1/Ttemp)
			{
				Energystoragedata[I].outlimitHtime=1;
				Energystoragedata[I].outlimitLtime=0;
				int Jw=1;
				while(Energystoragedata[I].Einit-Energystoragedata[I].VHksetschedulelay2[Jw]>Energystoragedata[I].PgHk/Energystoragedata[I].yitag*1/Ttemp*(1+Jw)&&Jw<Ttemp)
				{
					Energystoragedata[I].outlimitHtime++;
					Jw++;
				}
				
			}
			Energystoragedata[I].outlimitLdemical=((Energystoragedata[I].VLksetschedulelay2[0]-Energystoragedata[I].Einit)/(Energystoragedata[I].PpHk*Energystoragedata[I].yitap*1/Ttemp));
			Energystoragedata[I].outlimitHdemical=(Energystoragedata[I].Einit-Energystoragedata[I].VHksetschedulelay2[0])/(Energystoragedata[I].PgHk/Energystoragedata[I].yitag*1/Ttemp);
		}

		int *colno2;
		double *row2;
		int *colno3;
		double *row3;
		colno2=new int[loadnum+1];
		CHECKPOINTER(colno2);
		row2=new double[loadnum+1];
		CHECKPOINTER(row2);
		colno3=new int[loadnum+1];
		CHECKPOINTER(colno3);
		row3=new double[loadnum+1];
		CHECKPOINTER(row3);
		int hehe[6];

		for(int J=0;J<Ttemp;J++)
		{
			for(int I=0;I<loadnum;I++)
			{
				//Pcuthandel +=Loaddata[I].Pdt[J]*Ucutx[I][J];//没有设定Pcutx时间I,J
				//Pcutcosthandel +=Loaddata[I].Pdt[J]*Ucutx[I][J]*Pcutcost[Loaddata[I].level];//
				colno2[I]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1;
				row2[I]=Loaddata[I].Pdtlay2[J];
				colno3[I]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1;
				row3[I]=Loaddata[I].Pdtlay2[J]*Pcutcost[Loaddata[I].level-1];
			}
			colno2[loadnum]=J+1;
			row2[loadnum]=1;
			colno3[loadnum]=1*Ttemp+J+1;
			row3[loadnum]=-1;

			//add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, Pd1t[J]);
			add_constraintex(lp, loadnum+1, row2, colno2, EQ, Pd1tlay2[J]);
			//add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, EQ, 0);
			add_constraintex(lp, loadnum+1, row3, colno3, EQ, 0);
			//model.add(Pd1t[J]-Pdt[J]==Pcuthandel);
			//model.add(Pcutxt[J]==Pcutcosthandel);
		}
		delete[] colno2;
		delete[] row2;
		delete[] colno3;
		delete[] row3;
		//jiaohuangonglv 
		for(int J=0;J<Ttemp;J++)
		{
			//Pbuytout[J]=0;
			//Pselltout[J]=0;
			Griddata.Pbuytlay2[J]=0;
			Griddata.Pselltlay2[J]=0;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}		
}

void SCHEDULE::scheduletodispachgriddata(lprec *lp)
{
	double* outputrow;
	outputrow=new double[valurearrayall];
	CHECKPOINTER(outputrow);
	get_variables(lp,outputrow);
	get_objective(lp);
	//cout<<"object"<<get_objective(lp)<<endl;
	for(int J=0;J<T;J++)
	{
		//Pdtout[J]=cplex.getValue(Pdt[J]);
		//Pbuytout[J]=cplex.getValue(Pbuyt[J]);
		//Pselltout[J]=cplex.getValue(Psellt[J]);
		Pdtout[J]=outputrow[J];
		Pbuytout[J]=outputrow[2*T+J];
		Pselltout[J]=outputrow[3*T+J];
		Griddata.Pbuyt[J]=outputrow[2*T+J];
		Griddata.Psellt[J]=outputrow[3*T+J];
		for(int I=0;I<controllableunitnum;I++)
		{
			//Uitset[I][J]=cplex.getValue(Uit[I][J]);
			//Pitout[I][J]=cplex.getValue(Pit[I][J]);
			Uitset[I][J]=outputrow[onearray*T+4*controllableunitnum*T+I*T+J];
			Pitout[I][J]=outputrow[onearray*T+0*controllableunitnum*T+I*T+J];
			Controllableunitdata[I].Uit[J]=outputrow[onearray*T+4*controllableunitnum*T+I*T+J];
			Controllableunitdata[I].Pit[J]=outputrow[onearray*T+0*controllableunitnum*T+I*T+J];
		}
		for(int I=0;I<energystoragenum;I++)
		{
			//Vsoet[I][J]=cplex.getValue(Vkt[I][J]);
			//Pdhktout[I][J]=cplex.getValue(Pdhkt[I][J]);
			//Pchktout[I][J]=cplex.getValue(Pchkt[I][J]);
			//Pktout[I][J]=Pdhktout[I][J]-Pchktout[I][J];
			Vsoet[I][J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+J];
			Pdhktout[I][J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+1*energystoragenum*T+I*T+J];
			Pchktout[I][J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+J];
			//Pktout[I][J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+0*energystoragenum*T+I*T+J];
			Pktout[I][J]=Pdhktout[I][J]-Pchktout[I][J];
			Energystoragedata[I].Vkt[J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+J];
			Energystoragedata[I].Pgkt[J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+1*energystoragenum*T+I*T+J];
			Energystoragedata[I].Ppkt[J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+J];
			//Energystoragedata[I].Pkt[J]=Energystoragedata[I].Pgkt[J]-Energystoragedata[I].Ppkt[J];
			Energystoragedata[I].Pkt[J]=Pktout[I][J];
			
		}
		for(int I=0;I<renewableenergynum;I++)
		{
			//Pnewtout[I][J]=cplex.getValue(Pnewt[I][J]);
			Pnewtout[I][J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+0*T+I*T+J];
			Renewableenergydata[I].Pnewt[J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+0*T+I*T+J];
		}
		for(int I=0;I<loadnum;I++)
		{
			Ucutxset[I][J]=0;
			Loaddata[I].Ucutx[J]=Ucutxset[I][J];
		}
	}
	delete[] outputrow;

}
void SCHEDULE::scheduletodispachislanddata(lprec *lp)
{
	double* outputrow;
	outputrow=new double[valurearrayall];
	CHECKPOINTER(outputrow);
	//cout<<valurearrayall<<endl;
	//double zit[4][3][144];
	//double temp1,temp2,temp3,temp4;
	get_variables(lp,outputrow);
	get_objective(lp);
	//cout<<"object"<<get_objective(lp)<<endl;
	double a[24];
	for(int J=0;J<T;J++)
	{
		//Pdtout[J]=cplex.getValue(Pdt[J]);
		Pdtout[J]=outputrow[J];
		//cout<<outputrow[1*T+J]<<endl;
		Griddata.Pbuyt[J]=0;
		Griddata.Psellt[J]=0;
		for(int I=0;I<controllableunitnum;I++)
		{
			//Uitset[I][J]=cplex.getValue(Uit[I][J]);
			//Pitout[I][J]=cplex.getValue(Pit[I][J]);
			Uitset[I][J]=outputrow[onearray*T+4*controllableunitnum*T+I*T+J];
			Pitout[I][J]=outputrow[onearray*T+0*controllableunitnum*T+I*T+J];
			Controllableunitdata[I].Uit[J]=outputrow[onearray*T+4*controllableunitnum*T+I*T+J];
			Controllableunitdata[I].Pit[J]=outputrow[onearray*T+0*controllableunitnum*T+I*T+J];
			/*for(int I1=0;I1<node;I1++)
			{
				zit[I1][I][J]=outputrow[onearray*T+(controllableunitnumarray-2)*controllableunitnum*T+I*node*T+I1*T+J];
			}*/
		}
		for(int I=0;I<energystoragenum;I++)
		{
			//Vsoet[I][J]=cplex.getValue(Vkt[I][J]);
			//Pdhktout[I][J]=cplex.getValue(Pgkt[I][J]);
			//Pchktout[I][J]=cplex.getValue(Ppkt[I][J]);
			//Pktout[I][J]=Pdhktout[I][J]-Pchktout[I][J];
			Vsoet[I][J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+J];
			Pdhktout[I][J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+1*energystoragenum*T+I*T+J];
			Pchktout[I][J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+J];
			//Pktout[I][J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+0*energystoragenum*T+I*T+J];
			Pktout[I][J]=Pdhktout[I][J]-Pchktout[I][J];
			//Pktout[I][J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+J];
			Energystoragedata[I].Vkt[J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+J];
			Energystoragedata[I].Pgkt[J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+1*energystoragenum*T+I*T+J];
			Energystoragedata[I].Ppkt[J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+J];
			//Energystoragedata[I].Pkt[J]=Energystoragedata[I].Pgkt[J]-Energystoragedata[I].Ppkt[J];
			Energystoragedata[I].Pkt[J]=Pktout[I][J];
			//double a=-1;
			//a=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+12*energystoragenum*T+I*T+0];
			//cout<<"a:"<<a<<" ";
		}
		for(int I=0;I<renewableenergynum;I++)
		{
			//Pnewtout[I][J]=cplex.getValue(Pnewt[I][J]);
			Pnewtout[I][J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+0*T+I*T+J];
			Renewableenergydata[I].Pnewt[J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+0*T+I*T+J];
		}
		for(int I=0;I<loadnum;I++)
		{
			//Ucutxset[I][J]=cplex.getValue(Ucutx[I][J]);
			Ucutxset[I][J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynumarray*renewableenergynum*T+I*T+J];
			//Loaddata[I].Ucutx[J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynumarray*renewableenergynum*T+I*T+J];
			Loaddata[I].Ucutx[J]=Ucutxset[I][J];
		}
		//loss
		a[J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualnumarray*virtualloadnum*T
					+controllableunitnum*T+energystoragenum*T+renewableenergynum*T+loadnum*T+virtualloadnum*T+T+J];
		//cout<<a[J]<<" "<<endl;

	}
	//cout<<Loaddata[3].Ucutx[6]<<endl;
	delete[] outputrow;
}

void SCHEDULE::scheduletodispachgriddata_lay2(lprec *lp,int Ttemp)
{
	double* outputrow;
	outputrow=new double[valurearrayall];
	CHECKPOINTER(outputrow);
	get_variables(lp,outputrow);
	get_objective(lp);
	//cout<<"object"<<get_objective(lp)<<endl;
	//double temp=0;
	for(int J=0;J<Ttemp;J++)
	{
		//Pdtout[J]=cplex.getValue(Pdt[J]);
		//Pbuytout[J]=cplex.getValue(Pbuyt[J]);
		//Pselltout[J]=cplex.getValue(Psellt[J]);
		//Pdtout[J]=outputrow[J];
		//Pbuytout[J]=outputrow[2*T+J];
		//Pselltout[J]=outputrow[3*T+J];
		Griddata.Pbuytlay2[J]=outputrow[2*Ttemp+J];
		Griddata.Pselltlay2[J]=outputrow[3*Ttemp+J];
		for(int I=0;I<controllableunitnum;I++)
		{
			//Uitset[I][J]=cplex.getValue(Uit[I][J]);
			//Pitout[I][J]=cplex.getValue(Pit[I][J]);
			//Uitset[I][J]=outputrow[onearray*T+4*controllableunitnum*T+I*T+J];
			//Pitout[I][J]=outputrow[onearray*T+0*controllableunitnum*T+I*T+J];
			Controllableunitdata[I].Uitlay2[J]=outputrow[onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J];
			Controllableunitdata[I].Pitlay2[J]=outputrow[onearray*Ttemp+0*controllableunitnum*Ttemp+I*Ttemp+J];
			Controllableunitdata[I].Sitlay2[J]=outputrow[onearray*Ttemp+3*controllableunitnum*Ttemp+I*Ttemp+J];
			Controllableunitdata[I].Citlay2[J]=outputrow[onearray*Ttemp+2*controllableunitnum*Ttemp+I*Ttemp+J];
		}
		for(int I=0;I<energystoragenum;I++)
		{
			//Vsoet[I][J]=cplex.getValue(Vkt[I][J]);
			//Pdhktout[I][J]=cplex.getValue(Pdhkt[I][J]);
			//Pchktout[I][J]=cplex.getValue(Pchkt[I][J]);
			//Pktout[I][J]=Pdhktout[I][J]-Pchktout[I][J];
			//Vsoet[I][J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+J];
			//Pdhktout[I][J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+1*energystoragenum*T+I*T+J];
			//Pchktout[I][J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+J];
			//Pktout[I][J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+0*energystoragenum*T+I*T+J];
			//Pktout[I][J]=Pdhktout[I][J]-Pchktout[I][J];
			Energystoragedata[I].Vktlay2[J]=outputrow[onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+5*energystoragenum*Ttemp+I*Ttemp+J];
			Energystoragedata[I].Pgktlay2[J]=outputrow[onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+1*energystoragenum*Ttemp+I*Ttemp+J];
			Energystoragedata[I].Ppktlay2[J]=outputrow[onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+2*energystoragenum*Ttemp+I*Ttemp+J];
			Energystoragedata[I].Pktlay2[J]=Energystoragedata[I].Pgktlay2[J]-Energystoragedata[I].Ppktlay2[J];
			//Energystoragedata[I].WkC=outputrow[onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+11*energystoragenum*Ttemp+I*Ttemp+0];
			//Energystoragedata[I].Pkt[J]=Pktout[I][J];
			//cout<<Energystoragedata[I].Pktlay2[J]<<" ";
			//temp+=Energystoragedata[I].Pktlay2[J];
		}
		for(int I=0;I<renewableenergynum;I++)
		{
			//Pnewtout[I][J]=cplex.getValue(Pnewt[I][J]);
			//Pnewtout[I][J]=outputrow[onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+0*T+I*T+J];
			Renewableenergydata[I].Pnewtlay2[J]=outputrow[onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+0*Ttemp+I*Ttemp+J];
			//cout<<Renewableenergydata[I].Pnewtlay2[J]<<" ";
			//temp+=Renewableenergydata[I].Pnewtlay2[J];
		}
		for(int I=0;I<loadnum;I++)
		{
			//Ucutxset[I][J]=0;
			Loaddata[I].Ucutxlay2[J]=0;
		}
	}
	delete[] outputrow;

}

void SCHEDULE::scheduletodispachislanddata_lay2(lprec *lp,int Ttemp)
{
	double* outputrow;
	outputrow=new double[valurearrayall];
	CHECKPOINTER(outputrow);
	get_variables(lp,outputrow);
	get_objective(lp);
	//cout<<"object"<<get_objective(lp)<<endl;
	//double temp=0.1;
	for(int J=0;J<Ttemp;J++)
	{
		for(int I=0;I<energystoragenum;I++)
		{
			//Vsoet[I][J]=cplex.getValue(Vkt[I][J]);
			//Pdhktout[I][J]=cplex.getValue(Pgkt[I][J]);
			//Pchktout[I][J]=cplex.getValue(Ppkt[I][J]);
			//Pktout[I][J]=Pdhktout[I][J]-Pchktout[I][J];
			Energystoragedata[I].Vktlay2[J]=outputrow[onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+5*energystoragenum*Ttemp+I*Ttemp+J];
			Energystoragedata[I].Pgktlay2[J]=outputrow[onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+1*energystoragenum*Ttemp+I*Ttemp+J];
			Energystoragedata[I].Ppktlay2[J]=outputrow[onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+2*energystoragenum*Ttemp+I*Ttemp+J];
			Energystoragedata[I].Pktlay2[J]=Energystoragedata[I].Pgktlay2[J]-Energystoragedata[I].Ppktlay2[J];
			Energystoragedata[I].WkC=outputrow[onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+11*energystoragenum*Ttemp+I*Ttemp+0];
			//cout<<Energystoragedata[I].Vktlay2[J]<<" ";
			//temp+=Energystoragedata[I].Pktlay2[J];
			//double a=0;
			//a=outputrow[onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+12*energystoragenum*Ttemp+I*Ttemp+J];
			//cout<<a<<" ";
		}
	}
	for(int J=0;J<Ttemp;J++)
	{
		//Pdtout[J]=cplex.getValue(Pdt[J]);
		//Pdtout[J]=outputrow[J];
		for(int I=0;I<controllableunitnum;I++)
		{
			//Uitset[I][J]=cplex.getValue(Uit[I][J]);
			//Pitout[I][J]=cplex.getValue(Pit[I][J]);
			Controllableunitdata[I].Uitlay2[J]=outputrow[onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J];
			Controllableunitdata[I].Pitlay2[J]=outputrow[onearray*Ttemp+0*controllableunitnum*Ttemp+I*Ttemp+J];
			Controllableunitdata[I].Sitlay2[J]=outputrow[onearray*Ttemp+3*controllableunitnum*Ttemp+I*Ttemp+J];
			Controllableunitdata[I].Citlay2[J]=outputrow[onearray*Ttemp+2*controllableunitnum*Ttemp+I*Ttemp+J];
		}
		for(int I=0;I<renewableenergynum;I++)
		{
			//Pnewtout[I][J]=cplex.getValue(Pnewt[I][J]);
			Renewableenergydata[I].Pnewtlay2[J]=outputrow[onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+0*Ttemp+I*Ttemp+J];
			double a=0;
			a=outputrow[onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynum*Ttemp+I*Ttemp+J];
			//cout<<a<<" ";
			if(a>0)
			{
				for(int Ie=0;Ie<energystoragenum;Ie++)
				{
					if(Energystoragedata[Ie].Vktlay2[J]<Energystoragedata[Ie].VHksetschedulelay2[J]&&Energystoragedata[Ie].Ppktlay2[J]<Energystoragedata[Ie].PpHk)
					{
						if(Energystoragedata[Ie].Pktlay2[J]>0)
						{
							double Vtemp=0;
							if(Energystoragedata[Ie].Pgktlay2[J]>a)
							{
								Energystoragedata[Ie].Pktlay2[J]=Energystoragedata[Ie].Pktlay2[J]-a;
								Energystoragedata[Ie].Pgktlay2[J]=Energystoragedata[Ie].Pgktlay2[J]-a;
								Renewableenergydata[I].Pnewtlay2[J]=Renewableenergydata[I].Pnewtlay2[J]+a;
								//Energystoragedata[Ie].Vktlay2[J]=Energystoragedata[Ie].Vktlay2[J]+a/Ttemp/Energystoragedata[Ie].yitag;
								Energystoragedata[Ie].WkC=Energystoragedata[Ie].WkC-a/Ttemp/Energystoragedata[Ie].yitag;
								a=0;
								Vtemp=a/Ttemp/Energystoragedata[Ie].yitag;
								for(int Je=J;Je<Ttemp;Je++)
								{
									Energystoragedata[Ie].Vktlay2[Je]=Energystoragedata[Ie].Vktlay2[Je]+Vtemp;
								}
								break;
							}
							else
							{
								Energystoragedata[Ie].Pktlay2[J]=Energystoragedata[Ie].Pktlay2[J]-Energystoragedata[Ie].Pgktlay2[J];
								Energystoragedata[Ie].Pgktlay2[J]=Energystoragedata[Ie].Pgktlay2[J]-Energystoragedata[Ie].Pgktlay2[J];
								Renewableenergydata[I].Pnewtlay2[J]=Renewableenergydata[I].Pnewtlay2[J]+Energystoragedata[Ie].Pgktlay2[J];
								//Energystoragedata[Ie].Vktlay2[J]=Energystoragedata[Ie].Vktlay2[J]+Energystoragedata[Ie].Pgktlay2[J]/Ttemp/Energystoragedata[Ie].yitag;
								Energystoragedata[Ie].WkC=Energystoragedata[Ie].WkC-Energystoragedata[Ie].Pgktlay2[J]/Ttemp/Energystoragedata[Ie].yitag;
								a=a-Energystoragedata[Ie].Pgktlay2[J];
								Vtemp=Energystoragedata[Ie].Pgktlay2[J]/Ttemp/Energystoragedata[Ie].yitag;
								for(int Je=J;Je<Ttemp;Je++)
								{
									Energystoragedata[Ie].Vktlay2[Je]=Energystoragedata[Ie].Vktlay2[Je]+Vtemp;
								}
							}
							
						}
					}
				}
				for(int Ie=0;Ie<energystoragenum;Ie++)
				{
					if(Energystoragedata[Ie].Vktlay2[J]<Energystoragedata[Ie].VHksetschedulelay2[J]&&Energystoragedata[Ie].Ppktlay2[J]<Energystoragedata[Ie].PpHk)
					{
						if(Energystoragedata[Ie].Pktlay2[J]<=0)
						{
							double temp=0;
							if(Energystoragedata[Ie].PpHk-Energystoragedata[Ie].Ppktlay2[J]>a)
							{
								temp=a;
							}
							else
							{
								temp=Energystoragedata[Ie].PpHk-Energystoragedata[Ie].Ppktlay2[J];
							}
							if((Energystoragedata[Ie].VHksetschedulelay2[J]-Energystoragedata[Ie].Vktlay2[J])*Ttemp/Energystoragedata[Ie].yitap>temp)
							{
								temp=temp;
							}
							else
							{
								temp=(Energystoragedata[Ie].VHksetschedulelay2[J]-Energystoragedata[Ie].Vktlay2[J])*Ttemp/Energystoragedata[Ie].yitap;
							}
								Energystoragedata[Ie].Pktlay2[J]=Energystoragedata[Ie].Pktlay2[J]-temp;
								Energystoragedata[Ie].Ppktlay2[J]=Energystoragedata[Ie].Ppktlay2[J]+temp;
								Renewableenergydata[I].Pnewtlay2[J]=Renewableenergydata[I].Pnewtlay2[J]+temp;
								//Energystoragedata[Ie].Vktlay2[J]=Energystoragedata[Ie].Vktlay2[J]+temp/Ttemp*Energystoragedata[Ie].yitap;
								Energystoragedata[Ie].WkC=Energystoragedata[Ie].WkC-temp/Ttemp*Energystoragedata[Ie].yitap;
								a=a-temp;
								//for(int Je=0;Je<Ttemp;Je++)
								//{
								//cout<<Energystoragedata[Ie].Vktlay2[Je]<<" ";
								//}
								for(int Je=J;Je<Ttemp;Je++)
								{
									Energystoragedata[Ie].Vktlay2[Je]=Energystoragedata[Ie].Vktlay2[Je]+temp/Ttemp*Energystoragedata[Ie].yitap;
									//cout<<Energystoragedata[Ie].Vktlay2[Je]<<" ";
								}
								if(a<=0)
								{
									break;
								}
						}
					}
				}
				
			}
		}
		for(int I=0;I<loadnum;I++)
		{
			//Ucutxset[I][J]=cplex.getValue(Ucutx[I][J]);
			Loaddata[I].Ucutxlay2[J]=outputrow[onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J];
		}
	}
	delete[] outputrow;
}
void SCHEDULE::inputOC()
{
	ifstream fin1("OC_foundation.txt");
	if (!fin1)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	fin1>>OCdecision>>OCT>>OCdeltT;
	fin1.close(); 

	if(OCdecision>0)
	{
		/*double **OCPit;
		double **OCPkt;
		double **OCPnewt;
		double **OCPloadt;
		double *OCPCCt;*/
		OCPit=new double *[controllableunitnum];
		CHECKPOINTER(OCPit);
		for(int i=0;i<controllableunitnum;i++)
		{
			OCPit[i]=new double [OCT];
			CHECKPOINTER(OCPit[i]);

		}
		OCPkt=new double *[energystoragenum];
		CHECKPOINTER(OCPkt);
		for(int i=0;i<energystoragenum;i++)
		{
			OCPkt[i]=new double [OCT];
			CHECKPOINTER(OCPkt[i]);

		}
		OCPnewt=new double *[renewableenergynum];
		CHECKPOINTER(OCPnewt);
		for(int i=0;i<renewableenergynum;i++)
		{
			OCPnewt[i]=new double [OCT];
			CHECKPOINTER(OCPnewt[i]);

		}
		OCPloadt=new double *[loadnum];
		CHECKPOINTER(OCPloadt);
		for(int i=0;i<loadnum;i++)
		{
			OCPloadt[i]=new double [OCT];
			CHECKPOINTER(OCPloadt[i]);

		}
		OCPCCt=new double [OCT];
		CHECKPOINTER(OCPCCt);
		ifstream fin2("OC_unit.txt");
		if (!fin2)
		{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
		for(int i=0;i<controllableunitnum;i++)
		{
			fin2>>Controllableunitdata[i].OCIdentifier>>Controllableunitdata[i].OCID32>>Controllableunitdata[i].OCname;
			for(int j=0;j<OCT;j++)
			{
				fin2>>OCPit[i][j];
			}
		}
		fin2.close(); 
		ifstream fin3("OC_storage.txt");
		if (!fin3)
		{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
		for(int i=0;i<energystoragenum;i++)
		{
			fin3>>Energystoragedata[i].OCIdentifier>>Energystoragedata[i].OCID32>>Energystoragedata[i].OCname;
			for(int j=0;j<OCT;j++)
			{
				fin3>>OCPkt[i][j];
			}
		}
		fin3.close(); 
		ifstream fin4("OC_new.txt");
		if (!fin4)
		{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
		for(int i=0;i<renewableenergynum;i++)
		{
			fin4>>Renewableenergydata[i].OCIdentifier>>Renewableenergydata[i].OCID32>>Renewableenergydata[i].OCname;
			for(int j=0;j<OCT;j++)
			{
				fin4>>OCPnewt[i][j];
			}
		}
		fin4.close(); 
		ifstream fin5("OC_load.txt");
		if (!fin5)
		{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
		for(int i=0;i<loadnum;i++)
		{
			fin5>>Loaddata[i].OCIdentifier>>Loaddata[i].OCID32>>Loaddata[i].OCname;
			for(int j=0;j<OCT;j++)
			{
				fin5>>OCPloadt[i][j];
			}
		}
		fin5.close(); 
		ifstream fin6("OC_price.txt");
		if (!fin6)
		{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
			for(int j=0;j<OCT;j++)
			{
				fin6>>OCPCCt[j];
			}
		fin6.close(); 
	}
}
void SCHEDULE::calculateOC()
{
	
	for(int i=0;i<controllableunitnum;i++)
	{
		Controllableunitdata[i].OCCostC=0;
		Controllableunitdata[i].OCCostS=0;
		Controllableunitdata[i].OCCostCOM=0;
		int h;
		for(int h1=0;h1<controllableunitnum;h1++)
		{
			if(Controllableunitdata[i].ID32==Controllableunitdata[h1].OCID32)
			{
				h=h1;
				break;
			}
		}
		for(int j=0;j<OCT;j++)
		{
			if(OCPit[i][j]>=Controllableunitdata[h].Pi[0])
			{
				Controllableunitdata[i].OCCostC += ((OCPit[i][j]-Controllableunitdata[h].Pi[0])*(Controllableunitdata[h].ci[node-1]-Controllableunitdata[h].ci[0])/(Controllableunitdata[h].Pi[node-1]-Controllableunitdata[h].Pi[0])+Controllableunitdata[h].ci[0])*OCdeltT;
			}
			if(j==0)
			{
				if(OCPit[i][j]>0&&Controllableunitdata[h].Uinit==0)
				{
					Controllableunitdata[i].OCCostS += Controllableunitdata[h].Shi;
				}
			}
			else
			{
				if(OCPit[i][j]>0&&OCPit[i][j-1]==0)
				{
					Controllableunitdata[i].OCCostS += Controllableunitdata[h].Shi;
				}
			}
			Controllableunitdata[i].OCCostCOM +=OCPit[i][j]*(Controllableunitdata[h].COM+Controllableunitdata[h].CDP+Controllableunitdata[h].CE)*1.0*OCdeltT;
		}
	}
	for(int i=0;i<energystoragenum;i++)
	{
		Energystoragedata[i].OCCostC=0;
		int h;
		for(int h1=0;h1<energystoragenum;h1++)
		{
			if(Energystoragedata[i].ID32==Energystoragedata[h1].OCID32)
			{
				h=h1;
				break;
			}
		}
		for(int j=0;j<OCT;j++)
		{
			if(OCPkt[i][j]>0)
			{
				Energystoragedata[i].OCCostC += OCPkt[i][j]*Energystoragedata[h].CostkWh*1.0*OCdeltT/Energystoragedata[h].yitag;
			}
			else
			{
				Energystoragedata[i].OCCostC += -OCPkt[i][j]*Energystoragedata[h].CostkWh*1.0*OCdeltT*Energystoragedata[h].yitap;
			}
		}
	}
	if(gridislanddecision==0)
	{
		Griddata.OCCostBS=0;
		for(int j=0;j<OCT;j++)
		{
			if(OCPCCt[j]>0)
			{
				Griddata.OCCostBS +=OCPCCt[j]*Griddata.Buytotal[j]*1.0*OCdeltT;
			}
			else
			{
				Griddata.OCCostBS +=OCPCCt[j]*Griddata.Selltotal[j]*1.0*OCdeltT;
			}
		}
		for(int i=0;i<loadnum;i++)
		{
			Loaddata[i].OCCostCut=0;
		}
	}
	else
	{
		for(int i=0;i<loadnum;i++)
		{
			Loaddata[i].OCCostCut=0;
			int h;
			for(int h1=0;h1<loadnum;h1++)
			{
				if(Loaddata[i].ID32==Loaddata[h1].OCID32)
				{
					h=h1;
					break;
				}
			}
			for(int j=0;j<OCT;j++)
			{
				Loaddata[i].OCCostCut +=OCPloadt[i][j]*Loaddata[h].Pdttotal[j]*Pcutcost[Loaddata[h].level-1]*1.0*OCdeltT;
			}
		}
		Griddata.OCCostBS=0;
	}

}
void SCHEDULE::getobject_lay2(int Ttemp,int xlay2)
{
	for(int J=0;J<Ttemp;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			Controllableunitdata[I].CostC[xlay2*Ttemp+J]=Controllableunitdata[I].Citlay2[J]*1.0/Ttemp;
			Controllableunitdata[I].CostS[xlay2*Ttemp+J]=Controllableunitdata[I].Sitlay2[J];
			Controllableunitdata[I].CostCOM[xlay2*Ttemp+J]=Controllableunitdata[I].Pitlay2[J]*(Controllableunitdata[I].COM+Controllableunitdata[I].CDP+Controllableunitdata[I].CE)*1.0/Ttemp;
		}
		for(int I=0;I<energystoragenum;I++)
		{
			Energystoragedata[I].CostC[xlay2*Ttemp+J]=Energystoragedata[I].Pgktlay2[J]*Energystoragedata[I].CostkWh*1.0/Ttemp/Energystoragedata[I].yitag+Energystoragedata[I].Ppktlay2[J]*Energystoragedata[I].CostkWh*1.0/Ttemp*Energystoragedata[I].yitap;
		}
		for(int I=0;I<loadnum;I++)
		{
			Loaddata[I].CostCut[xlay2*Ttemp+J]=Loaddata[I].Ucutxlay2[J]*Loaddata[I].Pdtlay2[J]*Pcutcost[Loaddata[I].level-1]*1.0/Ttemp;
		}
		Griddata.CostBS[xlay2*Ttemp+J]=Griddata.Pbuytlay2[J]*Griddata.Buylay2[J]*1.0/Ttemp-Griddata.Pselltlay2[J]*Griddata.Selllay2[J]*1.0/Ttemp;
	}
}

void SCHEDULE::lay2tototaldata_lay2(int Ttemp,int X)
{
	for(int J=0;J<Ttemp;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//Controllableunitdata[I].Uittotal[Ttemp*X+J]=Controllableunitdata[I].Uitlay2[J];
			Controllableunitdata[I].Pittotal[Ttemp*X+J]=Controllableunitdata[I].Pitlay2[J];
		}
		for(int I=0;I<energystoragenum;I++)
		{
			Energystoragedata[I].Vkttotal[Ttemp*X+J]=Energystoragedata[I].Vktlay2[J];
			//Energystoragedata[I].Pgkttotal[Ttemp*X+J]=Energystoragedata[I].Pgktlay2[J];
			//Energystoragedata[I].Ppkttotal[Ttemp*X+J]=Energystoragedata[I].Ppktlay2[J];
			Energystoragedata[I].Pkttotal[Ttemp*X+J]=Energystoragedata[I].Pktlay2[J];
		}
		for(int I=0;I<renewableenergynum;I++)
		{
			Renewableenergydata[I].Pnewttotal[Ttemp*X+J]=Renewableenergydata[I].Pnewtlay2[J];
		}
		for(int I=0;I<loadnum;I++)
		{
			Loaddata[I].Ucutxtotal[Ttemp*X+J]=Loaddata[I].Ucutxlay2[J];
		}
		Griddata.Pbuyttotal[Ttemp*X+J]=Griddata.Pbuytlay2[J];

		Griddata.Psellttotal[Ttemp*X+J]=Griddata.Pselltlay2[J];

		//hehe
		loss[Ttemp*X+J]=losslay2[J];
	}
}

void SCHEDULE::CONTROLLABLEUNITconstraint(lprec *lp)//与cplex中的类的配合还要改,x=0时是schedule
{
	//int* colno1;
	//double* row1;
	//int* colno2;
	//double* row2;
	int colno1[1];
	double row1[1];
	int colno2[2];
	double row2[2];
	int colno3[3];
	double row3[3];
	int colno4[4];
	double row4[4];
	for(int J=0;J<T;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//model.add(Controllableunitdata[I].PLi*Uit[I][J]<=Pit[I][J]);
			//model.add(Pit[I][J]<=Controllableunitdata[I].PHi*Uit[I][J]);
			//model.add(Rit[I][J]==(Controllableunitdata[I].PHi*Uit[I][J]-Pit[I][J]));
			//model.add(0<=Rit[I][J]);
			//model.add(999999999*Uit[I][J]-Pit[I][J]>=0);

			colno2[0]=onearray*T+I*T+J+1;
			row2[0]=-1;
			colno2[1]=onearray*T+4*controllableunitnum*T+I*T+J+1;
			row2[1]=Controllableunitdata[I].PLi;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
			colno2[0]=onearray*T+I*T+J+1;
			row2[0]=-1;
			colno2[1]=onearray*T+4*controllableunitnum*T+I*T+J+1;
			row2[1]=Controllableunitdata[I].PHi;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, 0);
			/*colno3[0]=onearray*T+I*T+J+1;
			row3[0]=1;
			colno3[1]=onearray*T+4*controllableunitnum*T+I*T+J+1;
			row3[1]=-Controllableunitdata[I].PHi;
			colno3[2]=onearray*T+1*controllableunitnum*T+I*T+J+1;
			row3[2]=1;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, EQ, 0);*/
			colno1[0]=onearray*T+1*controllableunitnum*T+I*T+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
			colno2[0]=onearray*T+I*T+J+1;
			row2[0]=-1;
			colno2[1]=onearray*T+4*controllableunitnum*T+I*T+J+1;
			row2[1]=999999999;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, 0);
			double TOmin=Controllableunitdata[I].MOTi*T/24;
			if(Controllableunitdata[I].MOTi*T/24>T-J)
			{
				TOmin=T-J;
			}
			double TDmin=Controllableunitdata[I].MDTi*T/24;
			if(Controllableunitdata[I].MDTi*T/24>T-J)
			{
				TDmin=T-J;
			}
			int* colnoclosev1;
			double* rowclosev1;
			int* colnoopenv1;
			double* rowopenv1;
			int* colnoclosev2;
			double* rowclosev2;
			int* colnoopenv2;
			double* rowopenv2;
			int icount=0;
			int iclose1=0;
			int iopen1=0;
			for(int J1=J+1;J1<T;J1++)
			{
				if(J1<=J-1+Controllableunitdata[I].MOTi*T/24)
				{
					iclose1++;
				}
				if(J1<=J-1+Controllableunitdata[I].MDTi*T/24)
				{
					iopen1++;
				}
			}
			colnoclosev1=new int[iclose1+1];
			CHECKPOINTER(colnoclosev1);
			rowclosev1=new double[iclose1+1];
			CHECKPOINTER(rowclosev1);
			colnoopenv1=new int[iopen1+1];
			CHECKPOINTER(colnoopenv1);
			rowopenv1=new double[iopen1+1];
			CHECKPOINTER(rowopenv1);
			colnoclosev2=new int[iclose1+2];
			CHECKPOINTER(colnoclosev2);
			rowclosev2=new double[iclose1+2];
			CHECKPOINTER(rowclosev2);
			colnoopenv2=new int[iopen1+2];
			CHECKPOINTER(colnoopenv2);
			rowopenv2=new double[iopen1+2];
			CHECKPOINTER(rowopenv2);

			int iclose=0;
			int iopen=0;
			for(int J1=J+1;J1<T;J1++)
			{
				if(J1<=J-1+Controllableunitdata[I].MOTi*T/24)
				{
					//closeithandel +=Uit[I][J1];
					colnoclosev1[iclose]=onearray*T+4*controllableunitnum*T+I*T+J1+1;
					rowclosev1[iclose]=1;
					colnoclosev2[iclose]=onearray*T+4*controllableunitnum*T+I*T+J1+1;
					rowclosev2[iclose]=1;
					iclose++;
				}
				if(J1<=J-1+Controllableunitdata[I].MDTi*T/24)
				{
					//openithandel +=1-Uit[I][J1];
					colnoopenv1[iopen]=onearray*T+4*controllableunitnum*T+I*T+J1+1;
					rowopenv1[iopen]=-1;
					colnoopenv2[iopen]=onearray*T+4*controllableunitnum*T+I*T+J1+1;
					rowopenv2[iopen]=-1;
					iopen++;
					icount++;
				}
			}
			if(J>0)
			{
				//model.add(Pit[I][J]-Pit[I][J-1]<=Controllableunitdata[I].deltiup*24/T);
				//model.add(Pit[I][J-1]-Pit[I][J]<=Controllableunitdata[I].deltidown*24/T);
				colno2[0]=onearray*T+I*T+J+1;
				row2[0]=1;
				colno2[1]=onearray*T+I*T+J-1+1;
				row2[1]=-1;
				add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, Controllableunitdata[I].deltiup*24.0/T);
				colno2[0]=onearray*T+I*T+J+1;
				row2[0]=-1;
				colno2[1]=onearray*T+I*T+J-1+1;
				row2[1]=1;
				add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, Controllableunitdata[I].deltidown*24.0/T);

				//model.add(closeithandel>=(Uit[I][J]-Uit[I][J-1])*TOmin);
				//model.add(openithandel>=(Uit[I][J-1]-Uit[I][J])*TDmin);
				colnoclosev2[iclose]=onearray*T+4*controllableunitnum*T+I*T+J+1;
				rowclosev2[iclose]=-TOmin+1;
				iclose++;
				colnoclosev2[iclose]=onearray*T+4*controllableunitnum*T+I*T+J-1+1;
				rowclosev2[iclose]=TOmin;
				//add_constraintex(lp, sizeof(colnoclosev2) / sizeof(*colnoclosev2), rowclosev2, colnoclosev2, GE, 0);
				add_constraintex(lp, iclose1+2, rowclosev2, colnoclosev2, GE, 0);
				//cout<<sizeof(colno2) / sizeof(*colno2)<<endl;
				colnoopenv2[iopen]=onearray*T+4*controllableunitnum*T+I*T+J+1;
				rowopenv2[iopen]=TDmin-1;
				iopen++;
				colnoopenv2[iopen]=onearray*T+4*controllableunitnum*T+I*T+J-1+1;
				rowopenv2[iopen]=-TDmin;
				//add_constraintex(lp, sizeof(colnoopenv2) / sizeof(*colnoopenv2), rowopenv2, colnoopenv2, GE, -icount);
				add_constraintex(lp, iopen1+2, rowopenv2, colnoopenv2, GE, -icount-1);
			}
			else
			{
				//model.add(Pit[I][J]-Controllableunitdata[I].Pinit<=Controllableunitdata[I].deltiup*24/T);
				//model.add(Controllableunitdata[I].Pinit-Pit[I][J]<=Controllableunitdata[I].deltidown*24/T);
				colno1[0]=onearray*T+I*T+J+1;
				row1[0]=1;
				add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, Controllableunitdata[I].deltiup*24/T+Controllableunitdata[I].Pinit);
				colno1[0]=onearray*T+I*T+J+1;
				row1[0]=-1;
				add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, Controllableunitdata[I].deltidown*24/T-Controllableunitdata[I].Pinit);
				//model.add(closeithandel>=(Uit[I][J]-Controllableunitdata[I].Uinit)*TOmin);
				//model.add(openithandel>=(Controllableunitdata[I].Uinit-Uit[I][J])*TDmin);
				colnoclosev1[iclose1]=onearray*T+4*controllableunitnum*T+I*T+J+1;
				rowclosev1[iclose1]=-TOmin+1;
				//add_constraintex(lp, sizeof(colnoclosev1) / sizeof(*colnoclosev1), rowclosev1, colnoclosev1, GE, -Controllableunitdata[I].Uinit*TOmin);
				add_constraintex(lp, iclose1+1, rowclosev1, colnoclosev1, GE, -Controllableunitdata[I].Uinit*TOmin);
				colnoopenv1[iopen1]=onearray*T+4*controllableunitnum*T+I*T+J+1;
				rowopenv1[iopen1]=TDmin-1;
				//add_constraintex(lp, sizeof(colnoopenv1) / sizeof(*colnoopenv1), rowopenv1, colnoopenv1, GE, Controllableunitdata[I].Uinit*TDmin-icount);
				add_constraintex(lp, iopen1+1, rowopenv1, colnoopenv1, GE, Controllableunitdata[I].Uinit*TDmin-icount-1);
			}
			delete[] colnoclosev1;
			delete[] rowclosev1;
			delete[] colnoopenv1;
			delete[] rowopenv1;
			delete[] colnoclosev2;
			delete[] rowclosev2;
			delete[] colnoopenv2;
			delete[] rowopenv2;

		}
	}

	for(int I=0;I<controllableunitnum;I++)
	{
		if(Controllableunitdata[I].Uinit==1&&Controllableunitdata[I].TOinit<Controllableunitdata[I].MOTi)
		{
			//model.add(Uit[I][0]==1);
			colno1[0]=onearray*T+4*controllableunitnum*T+I*T+0+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 1);
		}
		else if(Controllableunitdata[I].Uinit==0&&Controllableunitdata[I].TDinit<Controllableunitdata[I].MDTi)
		{
			//model.add(Uit[I][0]==0);
			colno1[0]=onearray*T+4*controllableunitnum*T+I*T+0+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);
		}
		for(int J=1;J<T;J++)
		{	
			//model.add(Pitdeltp[I][J]>=0);
			//model.add(Pitdeltm[I][J]>=0);
			//model.add(Pitdeltp[I][J]<=Uitdeltp[I][J]*Controllableunitdata[I].deltiup*24/T);
			// model.add(Pitdeltm[I][J]<=Uitdeltm[I][J]*Controllableunitdata[I].deltidown*24/T);
			// model.add(Uitdeltp[I][J]+Uitdeltm[I][J]<=1);
			//model.add(Pit[I][J]-Pit[I][J-1]==Pitdeltp[I][J]-Pitdeltm[I][J]);
			colno1[0]=onearray*T+5*controllableunitnum*T+I*T+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
			colno1[0]=onearray*T+6*controllableunitnum*T+I*T+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
			colno2[0]=onearray*T+5*controllableunitnum*T+I*T+J+1;
			row2[0]=1;
			colno2[1]=onearray*T+7*controllableunitnum*T+I*T+J+1;
			row2[1]=-Controllableunitdata[I].deltiup*24/T;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
			colno2[0]=onearray*T+6*controllableunitnum*T+I*T+J+1;
			row2[0]=1;
			colno2[1]=onearray*T+8*controllableunitnum*T+I*T+J+1;
			row2[1]=-Controllableunitdata[I].deltidown*24/T;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
			colno2[0]=onearray*T+7*controllableunitnum*T+I*T+J+1;
			row2[0]=1;
			colno2[1]=onearray*T+8*controllableunitnum*T+I*T+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 1);
			colno4[0]=onearray*T+I*T+J+1;
			row4[0]=1;
			colno4[1]=onearray*T+I*T+J-1+1;
			row4[1]=-1;
			colno4[2]=onearray*T+5*controllableunitnum*T+I*T+J+1;
			row4[2]=-1;
			colno4[3]=onearray*T+6*controllableunitnum*T+I*T+J+1;
			row4[3]=1;
			add_constraintex(lp, sizeof(colno4) / sizeof(*colno4), row4, colno4, EQ, 0);
		}
	}
//备用
	for(int J=0;J<T;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			colno3[0]=onearray*T+4*controllableunitnum*T+I*T+J+1;
			row3[0]=Controllableunitdata[I].PHi;
			colno3[1]=onearray*T+I*T+J+1;
			row3[1]=-1;
			colno3[2]=onearray*T+1*controllableunitnum*T+I*T+J+1;
			row3[2]=-1;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, GE, 0);
			colno1[0]=onearray*T+1*controllableunitnum*T+I*T+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, Controllableunitdata[I].deltiup*24.0/T);
		}
	}

}

void SCHEDULE::CONTROLLABLEUNITconstraint_lay2(lprec *lp,int Ttemp)//与cplex中的类的配合还要改,x=0时是schedule
{
	int colno1[1];
	double row1[1];
	int colno2[2];
	double row2[2];
	int colno3[3];
	double row3[3];
	int colno4[4];
	double row4[4];
	for(int J=0;J<Ttemp;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//model.add(Controllableunitdata[I].PLi*Uit[I][J]<=Pit[I][J]);
			//model.add(Pit[I][J]<=Controllableunitdata[I].PHi*Uit[I][J]);
			//model.add(Rit[I][J]==(Controllableunitdata[I].PHi*Uit[I][J]-Pit[I][J]));
			//model.add(0<=Rit[I][J]);
			//model.add(999999999*Uit[I][J]-Pit[I][J]>=0);

			colno2[0]=onearray*Ttemp+I*Ttemp+J+1;
			row2[0]=-1;
			colno2[1]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row2[1]=Controllableunitdata[I].PLi;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
			colno2[0]=onearray*Ttemp+I*Ttemp+J+1;
			row2[0]=-1;
			colno2[1]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row2[1]=Controllableunitdata[I].PHi;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, 0);
			/*colno3[0]=onearray*Ttemp+I*Ttemp+J+1;
			row3[0]=1;
			colno3[1]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row3[1]=-Controllableunitdata[I].PHi;
			colno3[2]=onearray*Ttemp+1*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row3[2]=1;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, EQ, 0);*/
			colno1[0]=onearray*Ttemp+1*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
			colno2[0]=onearray*Ttemp+I*Ttemp+J+1;
			row2[0]=-1;
			colno2[1]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row2[1]=999999999;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, 0);

			if(J>0)
			{
				//model.add(Pit[I][J]-Pit[I][J-1]<=Controllableunitdata[I].deltiup*24/T);
				//model.add(Pit[I][J-1]-Pit[I][J]<=Controllableunitdata[I].deltidown*24/T);
				colno2[0]=onearray*Ttemp+I*Ttemp+J+1;
				row2[0]=1;
				colno2[1]=onearray*Ttemp+I*Ttemp+J-1+1;
				row2[1]=-1;
				add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, Controllableunitdata[I].deltiup*1.0/Ttemp);
				colno2[0]=onearray*Ttemp+I*Ttemp+J+1;
				row2[0]=-1;
				colno2[1]=onearray*Ttemp+I*Ttemp+J-1+1;
				row2[1]=1;
				add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, Controllableunitdata[I].deltidown*1.0/Ttemp);
			}
			else
			{
				//model.add(Pit[I][J]-Controllableunitdata[I].Pinit<=Controllableunitdata[I].deltiup*24/T);
				//model.add(Controllableunitdata[I].Pinit-Pit[I][J]<=Controllableunitdata[I].deltidown*24/T);
				colno1[0]=onearray*Ttemp+I*Ttemp+J+1;
				row1[0]=1;
				add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, Controllableunitdata[I].deltiup*1.0/Ttemp+Controllableunitdata[I].Pinit);
				colno1[0]=onearray*Ttemp+I*Ttemp+J+1;
				row1[0]=-1;
				add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, Controllableunitdata[I].deltidown*1.0/Ttemp-Controllableunitdata[I].Pinit);
			}
		}
	}

	for(int I=0;I<controllableunitnum;I++)
	{
		for(int J=1;J<Ttemp;J++)
		{	
			//model.add(Pitdeltp[I][J]>=0);
			//model.add(Pitdeltm[I][J]>=0);
			//model.add(Pitdeltp[I][J]<=Uitdeltp[I][J]*Controllableunitdata[I].deltiup*24/T);
			// model.add(Pitdeltm[I][J]<=Uitdeltm[I][J]*Controllableunitdata[I].deltidown*24/T);
			// model.add(Uitdeltp[I][J]+Uitdeltm[I][J]<=1);
			//model.add(Pit[I][J]-Pit[I][J-1]==Pitdeltp[I][J]-Pitdeltm[I][J]);
			colno1[0]=onearray*Ttemp+5*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
			colno1[0]=onearray*Ttemp+6*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
			colno2[0]=onearray*Ttemp+5*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row2[0]=1;
			colno2[1]=onearray*Ttemp+7*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row2[1]=-Controllableunitdata[I].deltiup*1.0/Ttemp;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
			colno2[0]=onearray*Ttemp+6*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row2[0]=1;
			colno2[1]=onearray*Ttemp+8*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row2[1]=-Controllableunitdata[I].deltidown*1.0/Ttemp;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
			colno2[0]=onearray*Ttemp+7*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row2[0]=1;
			colno2[1]=onearray*Ttemp+8*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 1);
			colno4[0]=onearray*Ttemp+I*Ttemp+J+1;
			row4[0]=1;
			colno4[1]=onearray*Ttemp+I*Ttemp+J-1+1;
			row4[1]=-1;
			colno4[2]=onearray*Ttemp+5*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row4[2]=-1;
			colno4[3]=onearray*Ttemp+6*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row4[3]=1;
			add_constraintex(lp, sizeof(colno4) / sizeof(*colno4), row4, colno4, EQ, 0);
		}
	}
//备用
	for(int J=0;J<Ttemp;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			colno3[0]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row3[0]=Controllableunitdata[I].PHi;
			colno3[1]=onearray*Ttemp+I*Ttemp+J+1;
			row3[1]=-1;
			colno3[2]=onearray*Ttemp+1*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row3[2]=-1;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, GE, 0);
			colno1[0]=onearray*Ttemp+1*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, Controllableunitdata[I].deltiup*1.0/Ttemp);
		}
	}
}

void SCHEDULE::CONTROLLABLEUNITconsumption(lprec *lp)//与cplex中的类的配合还要改
{
	int colno2[2];
	double row2[2];
	int colno3[3];
	double row3[3];
	int* colnopitv;
	double* rowpitv;
	int* colnocitv;
	double* rowcitv;
	int* colnozitv;
	double* rowzitv;
	int* colnoyitv;
	double* rowyitv;
	colnopitv=new int[node+1];
	CHECKPOINTER(colnopitv);
	rowpitv=new double[node+1];
	CHECKPOINTER(rowpitv);
	colnocitv=new int[node+1];
	CHECKPOINTER(colnocitv);
	rowcitv=new double[node+1];
	CHECKPOINTER(rowcitv);
	colnozitv=new int[node+1];
	CHECKPOINTER(colnozitv);
	rowzitv=new double[node+1];
	CHECKPOINTER(rowzitv);
	colnoyitv=new int[node];
	CHECKPOINTER(colnoyitv);
	rowyitv=new double[node];
	CHECKPOINTER(rowyitv);
	for(int J=0;J<T;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//IloExpr Pitnode1(env);
			//IloExpr Citnode1(env);
			//IloExpr zitnode(env);
			//IloExpr yitnode(env);

			for(int I1=0;I1<node;I1++)
			{
				//Pitnode1+=Controllableunitdata[I].Pi[I1]*zit[I1][I][J];
				//Citnode1+=Controllableunitdata[I].ci[I1]*zit[I1][I][J];
				//zitnode+=zit[I1][I][J];
				colnopitv[I1]=onearray*T+(controllableunitnumarray-2)*controllableunitnum*T+I*node*T+I1*T+J+1;
				rowpitv[I1]=Controllableunitdata[I].Pi[I1];
				colnocitv[I1]=onearray*T+(controllableunitnumarray-2)*controllableunitnum*T+I*node*T+I1*T+J+1;
				rowcitv[I1]=Controllableunitdata[I].ci[I1];
				colnozitv[I1]=onearray*T+(controllableunitnumarray-2)*controllableunitnum*T+I*node*T+I1*T+J+1;
				rowzitv[I1]=1;
				if(I1==0)
				{
					//model.add(zit[I1][I][J]<=yit[I1][I][J]);
					colno2[0]=onearray*T+(controllableunitnumarray-2)*controllableunitnum*T+I*node*T+I1*T+J+1;
					row2[0]=1;
					colno2[1]=onearray*T+(controllableunitnumarray-2)*controllableunitnum*T+node*controllableunitnum*T+I*(node-1)*T+I1*T+J+1;
					row2[1]=-1;
					add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
				}
				else if(I1==node-1)
				{
					//model.add(zit[I1][I][J]<=yit[I1-1][I][J]);
					colno2[0]=onearray*T+(controllableunitnumarray-2)*controllableunitnum*T+I*node*T+I1*T+J+1;
					row2[0]=1;
					colno2[1]=onearray*T+(controllableunitnumarray-2)*controllableunitnum*T+node*controllableunitnum*T+I*(node-1)*T+(I1-1)*T+J+1;
					row2[1]=-1;
					add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
				}
				else
				{
					//model.add(zit[I1][I][J]<=yit[I1-1][I][J]+yit[I1][I][J]);
					colno3[0]=onearray*T+(controllableunitnumarray-2)*controllableunitnum*T+I*node*T+I1*T+J+1;
					row3[0]=1;
					colno3[1]=onearray*T+(controllableunitnumarray-2)*controllableunitnum*T+node*controllableunitnum*T+I*(node-1)*T+(I1-1)*T+J+1;
					row3[1]=-1;
					colno3[2]=onearray*T+(controllableunitnumarray-2)*controllableunitnum*T+node*controllableunitnum*T+I*(node-1)*T+I1*T+J+1;
					row3[2]=-1;
					add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, LE, 0);
				}
			}
			for(int I1=0;I1<node-1;I1++)
			{
				//yitnode+=yit[I1][I][J];
				colnoyitv[I1]=onearray*T+(controllableunitnumarray-2)*controllableunitnum*T+node*controllableunitnum*T+I*(node-1)*T+I1*T+J+1;
				rowyitv[I1]=1;
			}
			//model.add(Pit[I][J]==Pitnode1);
			//model.add(Cit[I][J]==Citnode1);
			//model.add(1*Uit[I][J]==zitnode);
			colnopitv[node]=onearray*T+I*T+J+1;
			rowpitv[node]=-1;
			colnocitv[node]=onearray*T+2*controllableunitnum*T+I*T+J+1;
			rowcitv[node]=-1;
			colnozitv[node]=onearray*T+4*controllableunitnum*T+I*T+J+1;
			rowzitv[node]=-1;
			add_constraintex(lp, node+1, rowpitv, colnopitv, EQ, 0);
			add_constraintex(lp, node+1, rowcitv, colnocitv, EQ, 0);
			add_constraintex(lp, node+1, rowzitv, colnozitv, EQ, 0);

			//model.add(1*Uit[I][J]==yitnode);
			colnoyitv[node-1]=onearray*T+4*controllableunitnum*T+I*T+J+1;
			rowyitv[node-1]=-1;
			add_constraintex(lp, node, rowyitv, colnoyitv, EQ, 0);
			//Pitnode1.end();
			//Citnode1.end();
			//zitnode.end();
			//yitnode.end();
		}
	}
	delete[] colnopitv;
	delete[] rowpitv;
	delete[] colnocitv;
	delete[] rowcitv;
	delete[] colnozitv;
	delete[] rowzitv;
	delete[] colnoyitv;
	delete[] rowyitv;
	for(int I=0;I<controllableunitnum;I++)
	{

		for(int J=1;J<T;J++)
		{
			//model.add(Sit[I][J]>=Controllableunitdata[I].Shi*(Uit[I][J]-Uit[I][J-1]));
			//model.add(Sit[I][0]>=Controllableunitdata[I].Shi*(Uit[I][0]-Controllableunitdata[I].Uinit));
			colno3[0]=onearray*T+3*controllableunitnum*T+I*T+J+1;
			row3[0]=1;
			colno3[1]=onearray*T+4*controllableunitnum*T+I*T+J+1;
			row3[1]=-Controllableunitdata[I].Shi;
			colno3[2]=onearray*T+4*controllableunitnum*T+I*T+J-1+1;
			row3[2]=Controllableunitdata[I].Shi;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, GE, 0);
			colno2[0]=onearray*T+3*controllableunitnum*T+I*T+0+1;
			row2[0]=1;
			colno2[1]=onearray*T+4*controllableunitnum*T+I*T+0+1;
			row2[1]=-Controllableunitdata[I].Shi;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, -Controllableunitdata[I].Shi*Controllableunitdata[I].Uinit);
		}
	}

}

void SCHEDULE::CONTROLLABLEUNITconsumption_lay2(lprec *lp,int Ttemp)//与cplex中的类的配合还要改
{
	int colno2[2];
	double row2[2];
	int colno3[3];
	double row3[3];
	int* colnopitv;
	double* rowpitv;
	int* colnocitv;
	double* rowcitv;
	int* colnozitv;
	double* rowzitv;
	int* colnoyitv;
	double* rowyitv;
	colnopitv=new int[node+1];
	CHECKPOINTER(colnopitv);
	rowpitv=new double[node+1];
	CHECKPOINTER(rowpitv);
	colnocitv=new int[node+1];
	CHECKPOINTER(colnocitv);
	rowcitv=new double[node+1];
	CHECKPOINTER(rowcitv);
	colnozitv=new int[node+1];
	CHECKPOINTER(colnozitv);
	rowzitv=new double[node+1];
	CHECKPOINTER(rowzitv);
	colnoyitv=new int[node];
	CHECKPOINTER(colnoyitv);
	rowyitv=new double[node];
	CHECKPOINTER(rowyitv);
	for(int J=0;J<Ttemp;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//IloExpr Pitnode1(env);
			//IloExpr Citnode1(env);
			//IloExpr zitnode(env);
			//IloExpr yitnode(env);

			for(int I1=0;I1<node;I1++)
			{
				//Pitnode1+=Controllableunitdata[I].Pi[I1]*zit[I1][I][J];
				//Citnode1+=Controllableunitdata[I].ci[I1]*zit[I1][I][J];
				//zitnode+=zit[I1][I][J];
				colnopitv[I1]=onearray*Ttemp+(controllableunitnumarray-2)*controllableunitnum*Ttemp+I*node*Ttemp+I1*Ttemp+J+1;
				rowpitv[I1]=Controllableunitdata[I].Pi[I1];
				colnocitv[I1]=onearray*Ttemp+(controllableunitnumarray-2)*controllableunitnum*Ttemp+I*node*Ttemp+I1*Ttemp+J+1;
				rowcitv[I1]=Controllableunitdata[I].ci[I1];
				colnozitv[I1]=onearray*Ttemp+(controllableunitnumarray-2)*controllableunitnum*Ttemp+I*node*Ttemp+I1*Ttemp+J+1;
				rowzitv[I1]=1;
				if(I1==0)
				{
					//model.add(zit[I1][I][J]<=yit[I1][I][J]);
					colno2[0]=onearray*Ttemp+(controllableunitnumarray-2)*controllableunitnum*Ttemp+I*node*Ttemp+I1*Ttemp+J+1;
					row2[0]=1;
					colno2[1]=onearray*Ttemp+(controllableunitnumarray-2)*controllableunitnum*Ttemp+node*controllableunitnum*Ttemp+I*(node-1)*Ttemp+I1*Ttemp+J+1;
					row2[1]=-1;
					add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
				}
				else if(I1==node-1)
				{
					//model.add(zit[I1][I][J]<=yit[I1-1][I][J]);
					colno2[0]=onearray*Ttemp+(controllableunitnumarray-2)*controllableunitnum*Ttemp+I*node*Ttemp+I1*Ttemp+J+1;
					row2[0]=1;
					colno2[1]=onearray*Ttemp+(controllableunitnumarray-2)*controllableunitnum*Ttemp+node*controllableunitnum*Ttemp+I*(node-1)*Ttemp+(I1-1)*Ttemp+J+1;
					row2[1]=-1;
					add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
				}
				else
				{
					//model.add(zit[I1][I][J]<=yit[I1-1][I][J]+yit[I1][I][J]);
					colno3[0]=onearray*Ttemp+(controllableunitnumarray-2)*controllableunitnum*Ttemp+I*node*Ttemp+I1*Ttemp+J+1;
					row3[0]=1;
					colno3[1]=onearray*Ttemp+(controllableunitnumarray-2)*controllableunitnum*Ttemp+node*controllableunitnum*Ttemp+I*(node-1)*Ttemp+(I1-1)*Ttemp+J+1;
					row3[1]=-1;
					colno3[2]=onearray*Ttemp+(controllableunitnumarray-2)*controllableunitnum*Ttemp+node*controllableunitnum*Ttemp+I*(node-1)*Ttemp+I1*Ttemp+J+1;
					row3[2]=-1;
					add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, LE, 0);
				}
			}
			for(int I1=0;I1<node-1;I1++)
			{
				//yitnode+=yit[I1][I][J];
				colnoyitv[I1]=onearray*Ttemp+(controllableunitnumarray-2)*controllableunitnum*Ttemp+node*controllableunitnum*Ttemp+I*(node-1)*Ttemp+I1*Ttemp+J+1;
				rowyitv[I1]=1;
			}
			//model.add(Pit[I][J]==Pitnode1);
			//model.add(Cit[I][J]==Citnode1);
			//model.add(1*Uit[I][J]==zitnode);
			colnopitv[node]=onearray*Ttemp+I*Ttemp+J+1;
			rowpitv[node]=-1;
			colnocitv[node]=onearray*Ttemp+2*controllableunitnum*Ttemp+I*Ttemp+J+1;
			rowcitv[node]=-1;
			colnozitv[node]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J+1;
			rowzitv[node]=-1;
			add_constraintex(lp, node+1, rowpitv, colnopitv, EQ, 0);
			add_constraintex(lp, node+1, rowcitv, colnocitv, EQ, 0);
			add_constraintex(lp, node+1, rowzitv, colnozitv, EQ, 0);

			//model.add(1*Uit[I][J]==yitnode);
			colnoyitv[node-1]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J+1;
			rowyitv[node-1]=-1;
			add_constraintex(lp, node, rowyitv, colnoyitv, EQ, 0);
			//Pitnode1.end();
			//Citnode1.end();
			//zitnode.end();
			//yitnode.end();
		}
	}
	delete[] colnopitv;
	delete[] rowpitv;
	delete[] colnocitv;
	delete[] rowcitv;
	delete[] colnozitv;
	delete[] rowzitv;
	delete[] colnoyitv;
	delete[] rowyitv;
	for(int I=0;I<controllableunitnum;I++)
	{

		for(int J=1;J<T;J++)
		{
			//model.add(Sit[I][J]>=Controllableunitdata[I].Shi*(Uit[I][J]-Uit[I][J-1]));
			//model.add(Sit[I][0]>=Controllableunitdata[I].Shi*(Uit[I][0]-Controllableunitdata[I].Uinit));
			colno3[0]=onearray*Ttemp+3*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row3[0]=1;
			colno3[1]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row3[1]=-Controllableunitdata[I].Shi;
			colno3[2]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J-1+1;
			row3[2]=Controllableunitdata[I].Shi;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, GE, 0);
			colno2[0]=onearray*Ttemp+3*controllableunitnum*Ttemp+I*Ttemp+0+1;
			row2[0]=1;
			colno2[1]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+0+1;
			row2[1]=-Controllableunitdata[I].Shi;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, -Controllableunitdata[I].Shi*Controllableunitdata[I].Uinit);
		}
	}

}

void SCHEDULE::CONTROLLABLEUNITconsumptionsimplify(lprec *lp)//与cplex中的类的配合还要改
{
	int colno2[2];
	double row2[2];
	int colno3[3];
	double row3[3];
	/*
	for(int I=0;I<controllableunitnum;I++)
	{
	Controllableunitdata[I].Citsimplify=0;
	for(int I1=0;I1<node;I1++)
	{
	Controllableunitdata[I].Citsimplify=Controllableunitdata[I].Citsimplify+Controllableunitdata[I].ci[I1]/Controllableunitdata[I].Pi[I1];
	}
	}
	*/
	for(int I=0;I<controllableunitnum;I++)
	{
		for(int J=0;J<T;J++)
		{
			colno3[0]=onearray*T+2*controllableunitnum*T+I*T+J+1;
			row3[0]=1;
			colno3[1]=onearray*T+I*T+J+1;
			row3[1]=-(Controllableunitdata[I].ci[node-1]-Controllableunitdata[I].ci[0])/(Controllableunitdata[I].Pi[node-1]-Controllableunitdata[I].Pi[0]);
			colno3[2]=onearray*T+4*controllableunitnum*T+I*T+J+1;
			row3[2]=-(Controllableunitdata[I].ci[0]-(Controllableunitdata[I].ci[node-1]-Controllableunitdata[I].ci[0])/(Controllableunitdata[I].Pi[node-1]-Controllableunitdata[I].Pi[0])*Controllableunitdata[I].Pi[0]);
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, EQ, 0);
			/*	colno2[0]=onearray*T+2*controllableunitnum*T+I*T+J+1;
			row2[0]=1;
			colno2[1]=onearray*T+I*T+J+1;
			row2[1]=-(Controllableunitdata[I].ci[1]-Controllableunitdata[I].ci[0])/(Controllableunitdata[I].Pi[1]-Controllableunitdata[I].Pi[0]);
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, Controllableunitdata[I].ci[0]-(Controllableunitdata[I].ci[1]-Controllableunitdata[I].ci[0])/(Controllableunitdata[I].Pi[1]-Controllableunitdata[I].Pi[0])*Controllableunitdata[I].Pi[0]);
			*/
			/*	colno2[0]=onearray*T+2*controllableunitnum*T+I*T+J+1;
			row2[0]=1;
			colno2[1]=onearray*T+I*T+J+1;
			row2[1]=-(Controllableunitdata[I].ci[node-1])/(Controllableunitdata[I].Pi[node-1]);
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, 0);*/
		}
	}
	for(int I=0;I<controllableunitnum;I++)
	{
		colno2[0]=onearray*T+3*controllableunitnum*T+I*T+0+1;
		row2[0]=1;
		colno2[1]=onearray*T+4*controllableunitnum*T+I*T+0+1;
		row2[1]=-Controllableunitdata[I].Shi;
		add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, -Controllableunitdata[I].Shi*Controllableunitdata[I].Uinit);
		for(int J=1;J<T;J++)
		{
			//model.add(Sit[I][J]>=Controllableunitdata[I].Shi*(Uit[I][J]-Uit[I][J-1]));
			//model.add(Sit[I][0]>=Controllableunitdata[I].Shi*(Uit[I][0]-Controllableunitdata[I].Uinit));
			colno3[0]=onearray*T+3*controllableunitnum*T+I*T+J+1;
			row3[0]=1;
			colno3[1]=onearray*T+4*controllableunitnum*T+I*T+J+1;
			row3[1]=-Controllableunitdata[I].Shi;
			colno3[2]=onearray*T+4*controllableunitnum*T+I*T+J-1+1;
			row3[2]=Controllableunitdata[I].Shi;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, GE, 0);
		}
	}

}

void SCHEDULE::CONTROLLABLEUNITconsumptionsimplify_lay2(lprec *lp,int Ttemp)//与cplex中的类的配合还要改
{
	int colno2[2];
	double row2[2];
	int colno3[3];
	double row3[3];
	for(int I=0;I<controllableunitnum;I++)
	{
		for(int J=0;J<Ttemp;J++)
		{
			colno3[0]=onearray*Ttemp+2*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row3[0]=1;
			colno3[1]=onearray*Ttemp+I*Ttemp+J+1;
			row3[1]=-(Controllableunitdata[I].ci[node-1]-Controllableunitdata[I].ci[0])/(Controllableunitdata[I].Pi[node-1]-Controllableunitdata[I].Pi[0]);
			colno3[2]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row3[2]=-(Controllableunitdata[I].ci[0]-(Controllableunitdata[I].ci[node-1]-Controllableunitdata[I].ci[0])/(Controllableunitdata[I].Pi[node-1]-Controllableunitdata[I].Pi[0])*Controllableunitdata[I].Pi[0]);
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, EQ, 0); 
		}
	}
	for(int I=0;I<controllableunitnum;I++)
	{
		colno2[0]=onearray*Ttemp+3*controllableunitnum*Ttemp+I*Ttemp+0+1;
		row2[0]=1;
		colno2[1]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+0+1;
		row2[1]=-Controllableunitdata[I].Shi;
		add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, -Controllableunitdata[I].Shi*Controllableunitdata[I].Uinit);
		for(int J=1;J<Ttemp;J++)
		{
			//model.add(Sit[I][J]>=Controllableunitdata[I].Shi*(Uit[I][J]-Uit[I][J-1]));
			//model.add(Sit[I][0]>=Controllableunitdata[I].Shi*(Uit[I][0]-Controllableunitdata[I].Uinit));
			colno3[0]=onearray*Ttemp+3*controllableunitnum*Ttemp+I*Ttemp+J+1;

			row3[0]=1;
			colno3[1]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J+1;
			row3[1]=-Controllableunitdata[I].Shi;
			colno3[2]=onearray*Ttemp+4*controllableunitnum*Ttemp+I*Ttemp+J-1+1;
			row3[2]=Controllableunitdata[I].Shi;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, GE, 0);
		}
	}

}

void SCHEDULE::ENERGYSTORAGEconstraint(lprec *lp,int x)//与cplex中的类的配合还要改
{
	int colno1[1];
	double row1[1];
	int colno2[2];
	double row2[2];
	int colno3[3];
	double row3[3];
	int colno4[4];
	double row4[4];
	int colno5[5];
	double row5[5];
	int* colnoUgktv;
	double* rowUgktv;
	int* colnoUpktv;
	double* rowUpktv;
	colnoUgktv=new int[energystoragenum+1];
	CHECKPOINTER(colnoUgktv);
	rowUgktv=new double[energystoragenum+1];
	CHECKPOINTER(rowUgktv);
	colnoUpktv=new int[energystoragenum+1];
	CHECKPOINTER(colnoUpktv);
	rowUpktv=new double[energystoragenum+1];
	CHECKPOINTER(rowUpktv);
	for(int J=0;J<T;J++)
	{
		int mark=0;
		for(int I=0;I<energystoragenum;I++)
		{
			//model.add(Ugkt[I][J]+Upkt[I][J]<=1);
			//model.add(Upkt[I][J]<=energystoragenum*(1-egkt[I][J]));
			//model.add(Ugkt[I][J]<=energystoragenum*(1-epkt[I][J]));
			colno2[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+7*energystoragenum*T+I*T+J+1;
			row2[0]=1;
			colno2[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+8*energystoragenum*T+I*T+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 1);
			colno2[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+8*energystoragenum*T+I*T+J+1;
			row2[0]=1;
			colno2[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+9*energystoragenum*T+I*T+J+1;
			row2[1]=energystoragenum;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, energystoragenum);
			colno2[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+7*energystoragenum*T+I*T+J+1;
			row2[0]=1;
			colno2[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+10*energystoragenum*T+I*T+J+1;
			row2[1]=energystoragenum;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, energystoragenum);/**/
			//model.add(Energystoragedata[I].PgLk*Ugkt[I][J]<=Pgkt[I][J]);
			//model.add(Pgkt[I][J]<=Energystoragedata[I].PgHk*Ugkt[I][J]);
			//model.add(Energystoragedata[I].PpLk*Upkt[I][J]<=Ppkt[I][J]);
			//model.add(Ppkt[I][J]<=Energystoragedata[I].PpHk*Upkt[I][J]);
			colno2[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+7*energystoragenum*T+I*T+J+1;
			row2[0]=Energystoragedata[I].PgLk;
			colno2[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+1*energystoragenum*T+I*T+J+1;
			row2[1]=-1;
			add_constraintex(lp, 2, row2, colno2, LE, 0);
			colno2[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+7*energystoragenum*T+I*T+J+1;
			row2[0]=-Energystoragedata[I].PgHk;
			colno2[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+1*energystoragenum*T+I*T+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
			colno2[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+8*energystoragenum*T+I*T+J+1;
			row2[0]=Energystoragedata[I].PpLk;
			colno2[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+J+1;
			row2[1]=-1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
			colno2[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+8*energystoragenum*T+I*T+J+1;
			row2[0]=-Energystoragedata[I].PpHk;
			colno2[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+J+1;
			row2[1]=1;
			add_constraintex(lp, 2, row2, colno2, LE, 0);

			if(J<Energystoragedata[I].outlimitLtime)
			{
				//model.add(Energystoragedata[I].Einit+Energystoragedata[I].PpHk*Energystoragedata[I].yitap*24/T*(J+1)<=Vkt[I][J]);
				colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+J+1;
				row1[0]=1;
				add_constraintex(lp, 1, row1, colno1, GE, Energystoragedata[I].Einit+Energystoragedata[I].PpHk*Energystoragedata[I].yitap*24/T*(J+1));

				}
			else if(J<Energystoragedata[I].outlimitHtime)//0
			{
				//model.add(Vkt[I][J]<=Energystoragedata[I].Einit-Energystoragedata[I].PgHk/Energystoragedata[I].yitag*24/T*(J+1));
				colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+J+1;
				row1[0]=1;
				add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, Energystoragedata[I].Einit-Energystoragedata[I].PgHk/Energystoragedata[I].yitag*24/T*(J+1));
			}
			else
			{
				//model.add(Energystoragedata[I].VLksetschedule<=Vkt[I][J]);
				//model.add(Vkt[I][J]<=Energystoragedata[I].VHksetschedule);

				colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+J+1;
				row1[0]=1;
				add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, Energystoragedata[I].VLksetschedule[J]);
				colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+J+1;
				row1[0]=1;
				add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, Energystoragedata[I].VHksetschedule[J]);
				
				if((J-Energystoragedata[I].outlimitLdemical>0)&&(J-Energystoragedata[I].outlimitHdemical>0))
				{
					mark++;
					//cout<<"a";
				}
			}

			if(J>0)
			{
				//model.add(Vkt[I][J]==Vkt[I][J-1]-Pdhkt[I][J]*24/T+Pchkt[I][J]*24/T);
				colno4[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+J+1;
				row4[0]=-1;
				colno4[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+J-1+1;
				row4[1]=1;
				colno4[2]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+1*energystoragenum*T+I*T+J+1;
				row4[2]=-24.0/T/Energystoragedata[I].yitag;
				colno4[3]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+J+1;
				row4[3]=Energystoragedata[I].yitap*24.0/T;
				add_constraintex(lp, sizeof(colno4) / sizeof(*colno4), row4, colno4, EQ, 0);
			}
			else
			{
				//model.add(Vkt[I][J]==Energystoragedata[I].Einit-Pdhkt[I][J]*24/T+Pchkt[I][J]*24/T);
				colno3[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+J+1;
				row3[0]=-1;
				colno3[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+1*energystoragenum*T+I*T+J+1;
				row3[1]=-24.0/T/Energystoragedata[I].yitag;//
				colno3[2]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+J+1;
				row3[2]=Energystoragedata[I].yitap*24.0/T;//
				add_constraintex(lp, 3, row3, colno3, EQ, -Energystoragedata[I].Einit);
			}

		}
		if(mark>=energystoragenum)
		{
			for(int I=0;I<energystoragenum;I++)
			{
				for(int I1=0;I1<energystoragenum;I1++)//不同储能充放电互斥
				{
					//Ugkthandel +=Ugkt[I1][J];
					//Upkthandel +=Upkt[I1][J];
					colnoUgktv[I1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+7*energystoragenum*T+I1*T+J+1;
					rowUgktv[I1]=1;
					colnoUpktv[I1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+8*energystoragenum*T+I1*T+J+1;
					rowUpktv[I1]=1;
				}
				//model.add(Ugkthandel<=energystoragenum*egkt[I][J]);
				//model.add(Upkthandel<=energystoragenum*epkt[I][J]);
				colnoUgktv[energystoragenum]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+9*energystoragenum*T+I*T+J+1;
				rowUgktv[energystoragenum]=-energystoragenum;
				add_constraintex(lp, energystoragenum+1, rowUgktv, colnoUgktv, LE, 0);
				colnoUpktv[energystoragenum]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+10*energystoragenum*T+I*T+J+1;
				rowUpktv[energystoragenum]=-energystoragenum;
				add_constraintex(lp, energystoragenum+1, rowUpktv, colnoUpktv, LE, 0);/**/
			}
		}
	}
	delete[] colnoUgktv;
	delete[] rowUgktv;
	delete[] colnoUpktv;
	delete[] rowUpktv;
	if(gridislanddecision==0)
	{
		for(int I=0;I<energystoragenum;I++)
		{
			int temp=0;
			if(Energystoragedata[I].outlimitLtime>0)
			{
				temp=Energystoragedata[I].outlimitLtime;
			}
			if(Energystoragedata[I].outlimitHtime>0)
			{
				temp=Energystoragedata[I].outlimitHtime;
			}
			double tempdemical=0;
			if(Energystoragedata[I].outlimitLdemical>0)
			{
				tempdemical=Energystoragedata[I].outlimitLdemical;
			}
			if(Energystoragedata[I].outlimitHdemical>0)
			{
				tempdemical=Energystoragedata[I].outlimitHdemical;
			}
			if(tempdemical>0)//>0
			{
				/*//model.add(Vkt[I][T-1]-Vkt[I][temp]==Energystoragedata[I].Wk);
				colno2[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+T-1+1;
				row2[0]=1;
				colno2[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+temp+1;
				row2[1]=-1;
				add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, Energystoragedata[I].Wk);*/
				//model.add(Vkt[I][T-1]-Vkt[I][temp]==Energystoragedata[I].Wk);
				colno2[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+T-1+1;
				row2[0]=-1;
				colno2[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+temp+1;
				row2[1]=1;
				add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, -Energystoragedata[I].Wk);
				if(Energystoragedata[I].outlimitHdemical>0)
				{
					colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+T-1+1;
					row1[0]=1;
					add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Energystoragedata[I].VHksetschedule[temp]);
				}
			}
			else
			{
				/*//model.add(Vkt[I][T-1]-Pdhkt[I][0]*24/T+Pchkt[I][0]*24/T-Vkt[I][temp]==Energystoragedata[I].Wk);
				colno4[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+T-1+1;
				row4[0]=1;
				colno4[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+temp+1;
				row4[1]=-1;
				colno4[2]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+1*energystoragenum*T+I*T+temp+1;
				row4[2]=-24.0/T/Energystoragedata[I].yitag;
				colno4[3]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+temp+1;
				row4[3]=Energystoragedata[I].yitap*24.0/T;
				add_constraintex(lp, sizeof(colno4) / sizeof(*colno4), row4, colno4, EQ, Energystoragedata[I].Wk);*/
				//model.add(Vkt[I][T-1]-Pdhkt[I][0]*24/T+Pchkt[I][0]*24/T-Vkt[I][temp]==Energystoragedata[I].Wk);
				colno4[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+T-1+1;
				row4[0]=-1;
				colno4[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+temp+1;
				row4[1]=1;
				colno4[2]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+1*energystoragenum*T+I*T+temp+1;
				row4[2]=24.0/T/Energystoragedata[I].yitag;
				colno4[3]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+temp+1;
				row4[3]=-Energystoragedata[I].yitap*24.0/T;
				add_constraintex(lp, sizeof(colno4) / sizeof(*colno4), row4, colno4, EQ, -Energystoragedata[I].Wk);

			}
		}
	}
	else
	{
		switch(x)
		{
		case 0:
			for(int I=0;I<energystoragenum;I++)
			{
				int temp=0;
				if(Energystoragedata[I].outlimitLtime>0)
				{
					temp=Energystoragedata[I].outlimitLtime;
				}
				if(Energystoragedata[I].outlimitHtime>0)
				{
					temp=Energystoragedata[I].outlimitHtime;
				}
				double tempdemical=0;
				if(Energystoragedata[I].outlimitLdemical>0)
				{
					tempdemical=Energystoragedata[I].outlimitLdemical;
				}
				if(Energystoragedata[I].outlimitHdemical>0)
				{
					tempdemical=Energystoragedata[I].outlimitHdemical;
				}
				if(tempdemical>0)//>0
				{
					//model.add(Vkt[I][T-1]-Vkt[I][temp]==Energystoragedata[I].Wk);
					if(Energystoragedata[I].outlimitHdemical>0)
					{
						colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+T-1+1;
						row1[0]=1;
						add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, Energystoragedata[I].VHksetschedule[temp]);
					}
					/*//wkc
					set_lowbo(lp, onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+11*energystoragenum*T+I*T+0+1, BIGNUM);
					colno3[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+T-1+1;
					row3[0]=1;
					colno3[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+temp+1;
					row3[1]=-1;
					colno3[2]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+11*energystoragenum*T+I*T+0+1;
					row3[2]=1;
					add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, EQ, Energystoragedata[I].Wk);*/
					//wkc
					set_lowbo(lp, onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+11*energystoragenum*T+I*T+0+1, BIGNUM);
					colno3[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+T-1+1;
					row3[0]=-1;
					colno3[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+temp+1;
					row3[1]=1;
					colno3[2]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+11*energystoragenum*T+I*T+0+1;
					row3[2]=-1;
					add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, EQ, -Energystoragedata[I].Wk);

					colno2[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+11*energystoragenum*T+I*T+0+1;
					row2[0]=-1;
					colno2[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+12*energystoragenum*T+I*T+0+1;
					row2[1]=1;
					add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, 0);
				}
				else
				{
					/*//model.add(Vkt[I][T-1]-Pdhkt[I][0]*24/T+Pchkt[I][0]*24/T-Vkt[I][temp]==Energystoragedata[I].Wk);
					//wkc
					set_lowbo(lp, onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+11*energystoragenum*T+I*T+0+1, BIGNUM);
					colno5[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+T-1+1;
					row5[0]=1;
					colno5[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+temp+1;
					row5[1]=-1;
					colno5[2]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+1*energystoragenum*T+I*T+temp+1;
					row5[2]=-24.0/T/Energystoragedata[I].yitag;
					colno5[3]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+temp+1;
					row5[3]=Energystoragedata[I].yitap*24.0/T;
					colno5[4]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+11*energystoragenum*T+I*T+0+1;
					row5[4]=1;
					add_constraintex(lp, sizeof(colno5) / sizeof(*colno5), row5, colno5, EQ, Energystoragedata[I].Wk);*/
					//model.add(Vkt[I][T-1]-Pdhkt[I][0]*24/T+Pchkt[I][0]*24/T-Vkt[I][temp]==Energystoragedata[I].Wk);
					//wkc充放电正负
					set_lowbo(lp, onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+11*energystoragenum*T+I*T+0+1, BIGNUM);
					colno5[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+T-1+1;
					row5[0]=-1;
					colno5[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+temp+1;
					row5[1]=1;
					colno5[2]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+1*energystoragenum*T+I*T+temp+1;
					row5[2]=24.0/T/Energystoragedata[I].yitag;
					colno5[3]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+temp+1;
					row5[3]=-Energystoragedata[I].yitap*24.0/T;
					colno5[4]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+11*energystoragenum*T+I*T+0+1;
					row5[4]=-1;
					add_constraintex(lp, sizeof(colno5) / sizeof(*colno5), row5, colno5, EQ, -Energystoragedata[I].Wk);

					colno2[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+11*energystoragenum*T+I*T+0+1;
					row2[0]=-1;
					colno2[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+12*energystoragenum*T+I*T+0+1;
					row2[1]=1;
					add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, 0);
				}
			}
			break;
		case 1:
			
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		default:
			break;
		}
	}
	
	
//备用
	for(int J=0;J<T;J++)
	{
		for(int I=0;I<energystoragenum;I++)
		{
			colno3[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+1*energystoragenum*T+I*T+J+1;
			row3[0]=-1;
			colno3[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+J+1;
			row3[1]=1;
			colno3[2]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+6*energystoragenum*T+I*T+J+1;
			row3[2]=-1;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, GE, -Energystoragedata[I].PgHk);
			colno3[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+5*energystoragenum*T+I*T+J+1;
			row3[0]=1.0/(24.0/T)*Energystoragedata[I].yitag;
			colno3[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+J+1;
			row3[1]=1;
			colno3[2]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+6*energystoragenum*T+I*T+J+1;
			row3[2]=-1;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, GE, Energystoragedata[I].VLk/(24.0/T)*Energystoragedata[I].yitag);
		}
	}/**/
	//hehe
	/*for(int J=7;J<16;J++)
	{
			colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+0*T+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0.1);
	}*/
	/*colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+2*T+22+1;
	row1[0]=1;
	add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);*/
}

void SCHEDULE::ENERGYSTORAGEconstraint_lay2_islandp(lprec *lp,int Ttemp)
{
	int colno1[1];
	double row1[1];
	int colno2[2];
	double row2[2];
	int colno3[3];
	double row3[3];
	int colno4[4];
	double row4[4];
	int colno5[5];
	double row5[5];
	int* colnoUgktv;
	double* rowUgktv;
	int* colnoUpktv;
	double* rowUpktv;
	colnoUgktv=new int[energystoragenum+1];
	CHECKPOINTER(colnoUgktv);
	rowUgktv=new double[energystoragenum+1];
	CHECKPOINTER(rowUgktv);
	colnoUpktv=new int[energystoragenum+1];
	CHECKPOINTER(colnoUpktv);
	rowUpktv=new double[energystoragenum+1];
	CHECKPOINTER(rowUpktv);
	double Wkmark1=0;
		double Wkmark2=0;
	for(int J=0;J<Ttemp;J++)//
	{
		int mark=0;
		
		for(int I=0;I<energystoragenum;I++)
		{
			//model.add(Ugkt[I][J]+Upkt[I][J]<=1);
			//model.add(Upkt[I][J]<=energystoragenum*(1-egkt[I][J]));
			//model.add(Ugkt[I][J]<=energystoragenum*(1-epkt[I][J]));
			colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+7*energystoragenum*Ttemp+I*Ttemp+J+1;
			row2[0]=1;
			colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+8*energystoragenum*Ttemp+I*Ttemp+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 1);
			colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+8*energystoragenum*Ttemp+I*Ttemp+J+1;
			row2[0]=1;
			colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+9*energystoragenum*Ttemp+I*Ttemp+J+1;
			row2[1]=energystoragenum;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, energystoragenum);
			colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+7*energystoragenum*Ttemp+I*Ttemp+J+1;
			row2[0]=1;
			colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+10*energystoragenum*Ttemp+I*Ttemp+J+1;
			row2[1]=energystoragenum;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, energystoragenum);
			//model.add(Energystoragedata[I].PgLk*Ugkt[I][J]<=Pgkt[I][J]);
			//model.add(Pgkt[I][J]<=Energystoragedata[I].PgHk*Ugkt[I][J]);
			//model.add(Energystoragedata[I].PpLk*Upkt[I][J]<=Ppkt[I][J]);
			//model.add(Ppkt[I][J]<=Energystoragedata[I].PpHk*Upkt[I][J]);
			colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+7*energystoragenum*Ttemp+I*Ttemp+J+1;
			row2[0]=Energystoragedata[I].PgLk;
			colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+1*energystoragenum*Ttemp+I*Ttemp+J+1;
			row2[1]=-1;
			add_constraintex(lp, 2, row2, colno2, LE, 0);
			colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+7*energystoragenum*Ttemp+I*Ttemp+J+1;
			row2[0]=-Energystoragedata[I].PgHk;
			colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+1*energystoragenum*Ttemp+I*Ttemp+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
			colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+8*energystoragenum*Ttemp+I*Ttemp+J+1;
			row2[0]=Energystoragedata[I].PpLk;
			colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+2*energystoragenum*Ttemp+I*Ttemp+J+1;
			row2[1]=-1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
			colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+8*energystoragenum*Ttemp+I*Ttemp+J+1;
			row2[0]=-Energystoragedata[I].PpHk;
			colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+2*energystoragenum*Ttemp+I*Ttemp+J+1;
			row2[1]=1;
			add_constraintex(lp, 2, row2, colno2, LE, 0);

			if(J<Energystoragedata[I].outlimitLtime)
			{
				//model.add(Energystoragedata[I].Einit+Energystoragedata[I].PpHk*Energystoragedata[I].yitap*24/T*(J+1)<=Vkt[I][J]);
				colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+5*energystoragenum*Ttemp+I*Ttemp+J+1;
				row1[0]=1;
				add_constraintex(lp, 1, row1, colno1, GE, Energystoragedata[I].Einit+Energystoragedata[I].PpHk*Energystoragedata[I].yitap*1.0/Ttemp*(J+1));
				//cout<<Energystoragedata[I].outlimitLtime<<" "<<Energystoragedata[I].Einit<<" "<<Energystoragedata[I].PpHk*Energystoragedata[I].yitap*1.0/Ttemp*(J+1)<<endl;
			}
			else if(J<Energystoragedata[I].outlimitHtime)//0
			{
				//model.add(Vkt[I][J]<=Energystoragedata[I].Einit-Energystoragedata[I].PgHk/Energystoragedata[I].yitag*24/T*(J+1));
				colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+5*energystoragenum*Ttemp+I*Ttemp+J+1;
				row1[0]=1;
				add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, Energystoragedata[I].Einit-Energystoragedata[I].PgHk/Energystoragedata[I].yitag*1.0/Ttemp*(J+1));
			}
			else
			{
				//model.add(Energystoragedata[I].VLksetschedule<=Vkt[I][J]);
				//model.add(Vkt[I][J]<=Energystoragedata[I].VHksetschedule);

				colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+5*energystoragenum*Ttemp+I*Ttemp+J+1;
				row1[0]=1;
				add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, Energystoragedata[I].VLksetschedulelay2[J]-(Energystoragedata[I].VLksetschedulelay2[J]-Energystoragedata[I].VLk)*0);//松弛一下
				colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+5*energystoragenum*Ttemp+I*Ttemp+J+1;
				row1[0]=1;
				add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, Energystoragedata[I].VHksetschedulelay2[J]+(Energystoragedata[I].VHk-Energystoragedata[I].VHksetschedulelay2[J])*0);
				if(Energystoragedata[I].Wk>0)
				{
					Wkmark1=Energystoragedata[I].Wk/((Energystoragedata[I].PpHk*Energystoragedata[I].yitap)/Ttemp);
				}
				else
				{
					Wkmark1=Energystoragedata[I].Wk/((Energystoragedata[I].PgHk/Energystoragedata[I].yitag)/Ttemp);
				}
				//Wkmark1=Energystoragedata[I].Wk/((Energystoragedata[I].PpHk*Energystoragedata[I].yitap+Energystoragedata[I].PgHk/Energystoragedata[I].yitag)/Ttemp);
				if((J-Energystoragedata[I].outlimitLdemical>0)&&(J-Energystoragedata[I].outlimitHdemical>0))
				{
					if((Wkmark1*Wkmark2>=0||(J-fabs(Wkmark1)>0))&&(J-fabs(Wkmark2)>=0))
					{
						mark++;
					}
				}
				else
				{
					if(J==0)
					{
						//double temp=Energystoragedata[I].Wk/((Energystoragedata[I].PpHk*Energystoragedata[I].yitap+Energystoragedata[I].PgHk/Energystoragedata[I].yitag)/Ttemp);
						double temp=0;
						if(Energystoragedata[I].Wk>0)
						{
							temp=Energystoragedata[I].Wk/((Energystoragedata[I].PpHk*Energystoragedata[I].yitap)/Ttemp);
						}
						else
						{
							temp=Energystoragedata[I].Wk/((Energystoragedata[I].PgHk/Energystoragedata[I].yitag)/Ttemp);
						}
						if(fabs(temp)>fabs(Wkmark2))
						{
							Wkmark2=temp;
						}
						//Wkmark2=Energystoragedata[I].WkC/((Energystoragedata[I].PpHk*Energystoragedata[I].yitap+Energystoragedata[I].PgHk/Energystoragedata[I].yitag)/Ttemp);
					}
				}
			}

			if(J>0)
			{
				//model.add(Vkt[I][J]==Vkt[I][J-1]-Pdhkt[I][J]*24/T+Pchkt[I][J]*24/T);
				colno4[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+5*energystoragenum*Ttemp+I*Ttemp+J+1;
				row4[0]=-1;
				colno4[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+5*energystoragenum*Ttemp+I*Ttemp+J-1+1;
				row4[1]=1;
				colno4[2]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+1*energystoragenum*Ttemp+I*Ttemp+J+1;
				row4[2]=-1.0/Ttemp/Energystoragedata[I].yitag;
				colno4[3]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+2*energystoragenum*Ttemp+I*Ttemp+J+1;
				row4[3]=Energystoragedata[I].yitap*1.0/Ttemp;
				add_constraintex(lp, sizeof(colno4) / sizeof(*colno4), row4, colno4, EQ, 0);/**/
			}
			else
			{
				//model.add(Vkt[I][J]==Energystoragedata[I].Einit-Pdhkt[I][J]*24/T+Pchkt[I][J]*24/T);
				colno3[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+5*energystoragenum*Ttemp+I*Ttemp+J+1;
				row3[0]=-1;
				colno3[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+1*energystoragenum*Ttemp+I*Ttemp+J+1;
				row3[1]=-1.0/Ttemp/Energystoragedata[I].yitag;//
				colno3[2]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+2*energystoragenum*Ttemp+I*Ttemp+J+1;
				row3[2]=Energystoragedata[I].yitap*1.0/Ttemp;//
				add_constraintex(lp, 3, row3, colno3, EQ, -Energystoragedata[I].Einit);
			}

		}
		if(mark>=energystoragenum)
		{
			/*for(int I=0;I<energystoragenum;I++)
			{
				for(int I1=0;I1<energystoragenum;I1++)
				{
					//Ugkthandel +=Ugkt[I1][J];
					//Upkthandel +=Upkt[I1][J];
					colnoUgktv[I1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+7*energystoragenum*Ttemp+I1*Ttemp+J+1;
					rowUgktv[I1]=1;
					colnoUpktv[I1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+8*energystoragenum*Ttemp+I1*Ttemp+J+1;
					rowUpktv[I1]=1;
				}
				//model.add(Ugkthandel<=energystoragenum*egkt[I][J]);
				//model.add(Upkthandel<=energystoragenum*epkt[I][J]);
				colnoUgktv[energystoragenum]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+9*energystoragenum*Ttemp+I*Ttemp+J+1;
				rowUgktv[energystoragenum]=-energystoragenum;
				add_constraintex(lp, energystoragenum+1, rowUgktv, colnoUgktv, LE, 0);
				colnoUpktv[energystoragenum]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+10*energystoragenum*Ttemp+I*Ttemp+J+1;
				rowUpktv[energystoragenum]=-energystoragenum;
				add_constraintex(lp, energystoragenum+1, rowUpktv, colnoUpktv, LE, 0);
			}*///不用约束
		}
	}
	delete[] colnoUgktv;
	delete[] rowUgktv;
	delete[] colnoUpktv;
	delete[] rowUpktv;
	for(int I=0;I<energystoragenum;I++)
	{
		int temp=0;
		if(Energystoragedata[I].outlimitLtime>0)
		{
			temp=Energystoragedata[I].outlimitLtime;
		}
		if(Energystoragedata[I].outlimitHtime>0)
		{
			temp=Energystoragedata[I].outlimitHtime;
		}
		double tempdemical=0;
		if(Energystoragedata[I].outlimitLdemical>0)
		{
			tempdemical=Energystoragedata[I].outlimitLdemical;
		}
		if(Energystoragedata[I].outlimitHdemical>0)
		{
			tempdemical=Energystoragedata[I].outlimitHdemical;
		}
		set_lowbo(lp, onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+11*energystoragenum*Ttemp+I*Ttemp+0+1, BIGNUM);
		//model.add(Vkt[I][T-1]-Pdhkt[I][0]*24/T+Pchkt[I][0]*24/T-Vkt[I][temp]==Energystoragedata[I].Wk);
		//Energystoragedata[28].Wk=0;
		colno5[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+5*energystoragenum*Ttemp+I*Ttemp+Ttemp-1+1;
		row5[0]=-1;
		colno5[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+5*energystoragenum*Ttemp+I*Ttemp+0+1;
		row5[1]=1;
		colno5[2]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+1*energystoragenum*Ttemp+I*Ttemp+0+1;
		row5[2]=1.0/Ttemp/Energystoragedata[I].yitag;
		colno5[3]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+2*energystoragenum*Ttemp+I*Ttemp+0+1;
		row5[3]=-Energystoragedata[I].yitap*1.0/Ttemp;
		colno5[4]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+11*energystoragenum*Ttemp+I*Ttemp+0+1;
		row5[4]=-1;
		add_constraintex(lp, sizeof(colno5) / sizeof(*colno5), row5, colno5, EQ, -Energystoragedata[I].Wk-Energystoragedata[I].WkC);

		colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+11*energystoragenum*Ttemp+I*Ttemp+0+1;
		row2[0]=-1;
		colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+12*energystoragenum*Ttemp+I*Ttemp+0+1;
		row2[1]=1;
		add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, 0);
	}
//备用
	for(int J=0;J<Ttemp;J++)
	{
		for(int I=0;I<energystoragenum;I++)
		{
			colno3[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+1*energystoragenum*Ttemp+I*Ttemp+J+1;
			row3[0]=-1;
			colno3[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+2*energystoragenum*Ttemp+I*Ttemp+J+1;
			row3[1]=1;
			colno3[2]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+6*energystoragenum*Ttemp+I*Ttemp+J+1;
			row3[2]=-1;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, GE, -Energystoragedata[I].PgHk);
			colno3[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+5*energystoragenum*Ttemp+I*Ttemp+J+1;
			row3[0]=1.0/(1.0/Ttemp)*Energystoragedata[I].yitag;
			colno3[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+2*energystoragenum*Ttemp+I*Ttemp+J+1;
			row3[1]=1;
			colno3[2]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+6*energystoragenum*Ttemp+I*Ttemp+J+1;
			row3[2]=-1;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, GE, Energystoragedata[I].VLk/(1.0/Ttemp)*Energystoragedata[I].yitag);
		}
	}
}

void SCHEDULE::GRIDconstraint(lprec *lp)//与cplex中的类的配合还要改
{
	int colno1[1];
	double row1[1];
	int colno2[2];
	double row2[2];
	int colno3[3];
	double row3[3];
	int colno4[4];
	double row4[4];
	for(int J=0;J<T;J++)
	{	
		//model.add(Pbuyt[J]>=0);
		//model.add(Psellt[J]>=0);
		//model.add(Pbuyt[J]<=Ubuyt[J]*Griddata.Pbuymax);
		//model.add(Psellt[J]<=Usellt[J]*Griddata.Psellmax);
		colno1[0]=2*T+J+1;
		row1[0]=1;
		add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
		colno1[0]=3*T+J+1;
		row1[0]=1;
		add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
		colno2[0]=2*T+J+1;
		row2[0]=1;
		colno2[1]=4*T+J+1;
		row2[1]=-Griddata.Pbuymax;
		add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
		colno2[0]=3*T+J+1;
		row2[0]=1;
		colno2[1]=5*T+J+1;
		row2[1]=-Griddata.Psellmax;
		add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
		//model.add(Ubuyt[J]+Usellt[J]<=1);
		colno2[0]=4*T+J+1;
		row2[0]=1;
		colno2[1]=5*T+J+1;
		row2[1]=1;
		add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 1);
		//model.add(Pd1t[J]-Pdt[J]==Pbuyt[J]-Psellt[J]);
		colno3[0]=J+1;
		row3[0]=-1;
		colno3[1]=2*T+J+1;
		row3[1]=-1;
		colno3[2]=3*T+J+1;
		row3[2]=1;
		add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, EQ, -Pd1t[J]);

		if(J>0)
		{
			//model.add(Pdtdeltp[J]>=0);
			//model.add(Pdtdeltm[J]>=0);
			colno1[0]=6*T+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
			colno1[0]=7*T+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
			//model.add(Pdtdeltp[J]<=Udtdeltp[J]*(Griddata.Pbuymax+Griddata.Psellmax));
			//model.add(Pdtdeltm[J]<=Udtdeltm[J]*(Griddata.Pbuymax+Griddata.Psellmax));
			//model.add(Udtdeltp[J]+Udtdeltm[J]<=1);
			colno2[0]=6*T+J+1;
			row2[0]=1;
			colno2[1]=8*T+J+1;
			row2[1]=-(Griddata.Pbuymax+Griddata.Psellmax);
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
			colno2[0]=7*T+J+1;
			row2[0]=1;
			colno2[1]=9*T+J+1;
			row2[1]=-(Griddata.Pbuymax+Griddata.Psellmax);
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
			colno2[0]=8*T+J+1;
			row2[0]=1;
			colno2[1]=9*T+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 1);

			//model.add(Pd1t[J]-Pdt[J]-Pd1t[J-1]+Pdt[J-1]==Pdtdeltp[J]-Pdtdeltm[J]);
			colno4[0]=J+1;
			row4[0]=-1;
			colno4[1]=J-1+1;
			row4[1]=1;
			colno4[2]=6*T+J+1;
			row4[2]=-1;
			colno4[3]=7*T+J+1;
			row4[3]=1;
			add_constraintex(lp, sizeof(colno4) / sizeof(*colno4), row4, colno4, EQ, Pd1t[J-1]-Pd1t[J]);
		}
	}
	for(int J=0;J<T;J++)
	{
		for(int I=0;I<loadnum;I++)
		{
			//Ucutx[I][J]
			colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
				+renewableenergynumarray*renewableenergynum*T+I*T+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);
		}
	}
}
void SCHEDULE::GRIDconstraint_lay2(lprec *lp,int Ttemp)//与cplex中的类的配合还要改
{
	int colno1[1];
	double row1[1];
	int colno2[2];
	double row2[2];
	int colno3[3];
	double row3[3];
	int colno4[4];
	double row4[4];
	for(int J=0;J<Ttemp;J++)
	{	
		//model.add(Pbuyt[J]>=0);
		//model.add(Psellt[J]>=0);
		//model.add(Pbuyt[J]<=Ubuyt[J]*Griddata.Pbuymax);
		//model.add(Psellt[J]<=Usellt[J]*Griddata.Psellmax);
		colno1[0]=2*Ttemp+J+1;
		row1[0]=1;
		add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
		colno1[0]=3*Ttemp+J+1;
		row1[0]=1;
		add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
		colno2[0]=2*Ttemp+J+1;
		row2[0]=1;
		colno2[1]=4*Ttemp+J+1;
		row2[1]=-Griddata.Pbuymax;
		add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
		colno2[0]=3*Ttemp+J+1;
		row2[0]=1;
		colno2[1]=5*Ttemp+J+1;
		row2[1]=-Griddata.Psellmax;
		add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
		//model.add(Ubuyt[J]+Usellt[J]<=1);
		colno2[0]=4*Ttemp+J+1;
		row2[0]=1;
		colno2[1]=5*Ttemp+J+1;
		row2[1]=1;
		add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 1);
		//model.add(Pd1t[J]-Pdt[J]==Pbuyt[J]-Psellt[J]);
		colno3[0]=J+1;
		row3[0]=-1;
		colno3[1]=2*Ttemp+J+1;
		row3[1]=-1;
		colno3[2]=3*Ttemp+J+1;
		row3[2]=1;
		add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, EQ, -Pd1tlay2[J]);

		if(J>0)
		{
			//model.add(Pdtdeltp[J]>=0);
			//model.add(Pdtdeltm[J]>=0);
			colno1[0]=6*Ttemp+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
			colno1[0]=7*Ttemp+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
			//model.add(Pdtdeltp[J]<=Udtdeltp[J]*(Griddata.Pbuymax+Griddata.Psellmax));
			//model.add(Pdtdeltm[J]<=Udtdeltm[J]*(Griddata.Pbuymax+Griddata.Psellmax));
			//model.add(Udtdeltp[J]+Udtdeltm[J]<=1);
			colno2[0]=6*Ttemp+J+1;
			row2[0]=1;
			colno2[1]=8*Ttemp+J+1;
			row2[1]=-(Griddata.Pbuymax+Griddata.Psellmax);
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
			colno2[0]=7*Ttemp+J+1;
			row2[0]=1;
			colno2[1]=9*Ttemp+J+1;
			row2[1]=-(Griddata.Pbuymax+Griddata.Psellmax);
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 0);
			colno2[0]=8*Ttemp+J+1;
			row2[0]=1;
			colno2[1]=9*Ttemp+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, LE, 1);

			//model.add(Pd1t[J]-Pdt[J]-Pd1t[J-1]+Pdt[J-1]==Pdtdeltp[J]-Pdtdeltm[J]);
			colno4[0]=J+1;
			row4[0]=-1;
			colno4[1]=J-1+1;
			row4[1]=1;
			colno4[2]=6*Ttemp+J+1;
			row4[2]=-1;
			colno4[3]=7*Ttemp+J+1;
			row4[3]=1;
			add_constraintex(lp, sizeof(colno4) / sizeof(*colno4), row4, colno4, EQ, Pd1tlay2[J-1]-Pd1tlay2[J]);
		}
	}
	for(int J=0;J<Ttemp;J++)
	{
		for(int I=0;I<loadnum;I++)
		{
			//Ucutx[I][J]
			colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);
		}
	}
}
void SCHEDULE::VIRTUALlevelIdentifier()//false
{
	/*int I=0;
	double temp=DECOMPOSE;
	if(mglevel>1)
	{
	Virtualloaddata[0].levelIdentifier[0]=0;
	}
	for(int Ix=1;Ix<mglevel;Ix++)
	{
		for(int Iy=0;Iy<mglevelnum[Ix];Iy++)
		{
			//Virtualloaddata[I].levelIdentifier=(Ix+1)*pow(temp,mglevel)+(Iy+1)*pow(temp,mglevel-Ix-1);
			Virtualloaddata[I].levelIdentifier[Ix-1]=Iy+1;
			//cout<<"Virtualloaddata[I].levelIdentifier:"<<Virtualloaddata[I].levelIdentifier<<endl;
			I++;
		}
	}*/
}
void SCHEDULE::VIRTUALGRIDconstraint(lprec *lp,int Ttemp,int Wlevel,int Xlevel)
{
	int colno1[1];
	double row1[1];
	int colno2[2];
	double row2[2];
	int *colnovirtual;
	double *rowvirtual;
	int Xnum=0;
	/*
	int DEtempu=1;
	int DEtempd=1;
	int i=1;
	while(i<Wlevel)
	{
		DEtempu=DEtempu*DECOMPOSE;
		i++;
	}*/
	//DEtempd=DEtempu/DECOMPOSE;
	for(int I=0;I<renewableenergynum;I++)
	{
		if(Renewableenergydata[I].levelIdentifier[mglevel-Wlevel]==Levelnumtoreal[mglevel-Wlevel][Xlevel])
		{
			Xnum++;
		}
	}
	for(int I=0;I<controllableunitnum;I++)
	{
		if(Controllableunitdata[I].levelIdentifier[mglevel-Wlevel]==Levelnumtoreal[mglevel-Wlevel][Xlevel])
		{
			Xnum++;
		}
	}
	for(int I=0;I<energystoragenum;I++)
	{
		if(Energystoragedata[I].levelIdentifier[mglevel-Wlevel]==Levelnumtoreal[mglevel-Wlevel][Xlevel])
		{
			Xnum++;
			Xnum++;
			//cout<<Levelnumtoreal[mglevel-Wlevel][Xlevel]<<" ";
		}
	}//cout<<endl;
	for(int I=0;I<loadnum;I++)
	{
		if(Loaddata[I].levelIdentifier[mglevel-Wlevel]==Levelnumtoreal[mglevel-Wlevel][Xlevel])
		{
			Xnum++;
		}
	}
	colnovirtual=new int[Xnum+1];
	CHECKPOINTER(colnovirtual);
	rowvirtual=new double[Xnum+1];
	CHECKPOINTER(rowvirtual);

	relativetemp=0;
	for(int J=0;J<Ttemp;J++)
	{	
		Xnum=0;
		double loadsum=0;
		for(int I=0;I<renewableenergynum;I++)
		{
			if(Renewableenergydata[I].levelIdentifier[mglevel-Wlevel]==Levelnumtoreal[mglevel-Wlevel][Xlevel])
			{
				//Renewableenergydata[I].Pnewt[J]=0;
				colnovirtual[Xnum]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+I*Ttemp+J+1;
				rowvirtual[Xnum]=1;
				Xnum++;
				
				if(Ttemp==T)
				{
					relativetemp +=Renewableenergydata[I].PnewHt[J];
				}
				else
				{
					relativetemp +=Renewableenergydata[I].PnewHtlay2[J];
				}
			}
		}
		for(int I=0;I<controllableunitnum;I++)
		{
			if(Controllableunitdata[I].levelIdentifier[mglevel-Wlevel]==Levelnumtoreal[mglevel-Wlevel][Xlevel])
			{
				//pit,uit=0
				colnovirtual[Xnum]=onearray*Ttemp+I*Ttemp+J+1;
				rowvirtual[Xnum]=1;
				Xnum++;
			}
		}
		for(int I=0;I<energystoragenum;I++)
		{
			if(Energystoragedata[I].levelIdentifier[mglevel-Wlevel]==Levelnumtoreal[mglevel-Wlevel][Xlevel])
			{
				//pgkt,ppkt=0
				colnovirtual[Xnum]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+1*energystoragenum*Ttemp+I*Ttemp+J+1;
				rowvirtual[Xnum]=1;
				Xnum++;
				colnovirtual[Xnum]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+2*energystoragenum*Ttemp+I*Ttemp+J+1;
				rowvirtual[Xnum]=-1;
				Xnum++;
			}
		}
		for(int I=0;I<loadnum;I++)
		{
			if(Loaddata[I].levelIdentifier[mglevel-Wlevel]==Levelnumtoreal[mglevel-Wlevel][Xlevel])
			{
				if(Ttemp==T)
				{
					colnovirtual[Xnum]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
						+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1;
					rowvirtual[Xnum]=Loaddata[I].Pdt[J];
					loadsum+=Loaddata[I].Pdt[J];
				}
				else
				{
					colnovirtual[Xnum]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
						+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1;
					rowvirtual[Xnum]=Loaddata[I].Pdtlay2[J];//
					loadsum+=Loaddata[I].Pdtlay2[J];
				}
				Xnum++;
				if(Ttemp==T)
				{
					relativetemp -=Loaddata[I].Pdt[J];
				}
				else
				{
					relativetemp -=Loaddata[I].Pdtlay2[J];
				}
				
			}
		}
		//cout<<virtualloadnum<<endl;
		for(int I=0;I<virtualloadnum;I++)
		{
			if((mglevel-Wlevel<mglevel-1&&Virtualloaddata[I].levelIdentifier[mglevel-Wlevel]==Levelnumtoreal[mglevel-Wlevel][Xlevel]&&Virtualloaddata[I].levelIdentifier[mglevel-Wlevel+1]==0)||(mglevel-Wlevel==mglevel-1&&Virtualloaddata[I].levelIdentifier[mglevel-Wlevel]==Levelnumtoreal[mglevel-Wlevel][Xlevel]))
			{
				set_lowbo(lp, onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+I*Ttemp+J+1, BIGNUM);
				colnovirtual[Xnum]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+I*Ttemp+J+1;
				rowvirtual[Xnum]=-1;
				add_constraintex(lp, Xnum+1, rowvirtual, colnovirtual, EQ, loadsum);//loadsum

				//Ppunisht>0,Pvirtualt
				colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualloadnum*Ttemp+I*Ttemp+J+1;
				row1[0]=1;
				add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
				colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualloadnum*Ttemp+I*Ttemp+J+1;
				row2[0]=1;
				colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+I*Ttemp+J+1;
				row2[1]=-1;
				add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, 0);/**/
				colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualloadnum*Ttemp+I*Ttemp+J+1;
				row2[0]=1;
				colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+I*Ttemp+J+1;
				row2[1]=1;
				add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, GE, 0);
			}
			//cout<<Virtualloaddata[I].levelIdentifier[mglevel-Wlevel]<<" ";
		}

	}
	relativetemp=fabs(relativetemp/Ttemp);
	delete[] colnovirtual;
	delete[] rowvirtual;
}
void SCHEDULE::RENEWABLEENERGYconstraint(lprec *lp)
{
	int colno1[1];
	double row1[1];
	int colno2[2];
	double row2[2];
	for(int I=0;I<renewableenergynum;I++)
	{
		for(int J=0;J<T;J++)
		{
			//model.add(Pnewt[I][J] >=0);
			//model.add(Renewableenergydata[I].PnewHt[J]>=Pnewt[I][J]);
			colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+I*T+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
			colno1[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+I*T+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, Renewableenergydata[I].PnewHt[J]);

			colno2[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+I*T+J+1;
			row2[0]=1;
			colno2[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+renewableenergynum*T+I*T+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, Renewableenergydata[I].PnewHt[J]);
		}
	}
}

void SCHEDULE::RENEWABLEENERGYconstraint_lay2_islandp(lprec *lp,int Ttemp)
{
	int colno1[1];
	double row1[1];
	int colno2[2];
	double row2[2];
	for(int I=0;I<renewableenergynum;I++)
	{
		for(int J=0;J<Ttemp;J++)
		{
			//model.add(Pnewt[I][J] >=0);
			//model.add(Renewableenergydata[I].PnewHt[J]>=Pnewt[I][J]);
			colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+I*Ttemp+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
			colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+I*Ttemp+J+1;
			row1[0]=1;
			add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, LE, Renewableenergydata[I].PnewHtlay2[J]);
			colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+I*Ttemp+J+1;
			row2[0]=1;
			colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynum*Ttemp+I*Ttemp+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, Renewableenergydata[I].PnewHtlay2[J]);
			colno1[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+renewableenergynum*Ttemp+I*Ttemp+J+1;//==0
			row1[0]=1;
			//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, EQ, 0);
		}
	}

}
void SCHEDULE::LOSSconstraint(lprec *lp)
{
	int colno2[2];
	double row2[2];
	int colno3[3];
	double row3[3];
	int* colnopltv;
	double* rowpltv;
	colnopltv=new int[controllableunitnum+energystoragenum+renewableenergynum+loadnum+virtualloadnum+1+1];
	CHECKPOINTER(colnopltv);
	rowpltv=new double[controllableunitnum+energystoragenum+renewableenergynum+loadnum+virtualloadnum+1+1];
	CHECKPOINTER(rowpltv);
	
	for(int J=0;J<T;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//Pithandel +=Pit[I][J];
			colno2[0]=onearray*T+I*T+J+1;
			row2[0]=-Controllableunitdata[I].aloss;
			colno2[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualnumarray*virtualloadnum*T+I*T+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, 0);
			colnopltv[I]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualnumarray*virtualloadnum*T+I*T+J+1;
			rowpltv[I]=1;
		}
		for(int I=0;I<energystoragenum;I++)
		{
			//Pkthandel +=Pgkt[I][J]-Ppkt[I][J];
			colno3[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+1*energystoragenum*T+I*T+J+1;
			row3[0]=-Energystoragedata[I].aloss;
			colno3[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+J+1;
			row3[1]=-Energystoragedata[I].aloss;
			colno3[2]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualnumarray*virtualloadnum*T+controllableunitnum*T+I*T+J+1;
			row3[2]=1;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, EQ, 0);

			colnopltv[controllableunitnum+I]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualnumarray*virtualloadnum*T+controllableunitnum*T+I*T+J+1;
			rowpltv[controllableunitnum+I]=1;
		}
		for(int I=0;I<renewableenergynum;I++)
		{
			//	Pnewthandel +=Pnewt[I][J];
			colno2[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+I*T+J+1;
			row2[0]=-Renewableenergydata[I].aloss;
			colno2[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualnumarray*virtualloadnum*T
					+controllableunitnum*T+energystoragenum*T+I*T+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, 0);

			colnopltv[controllableunitnum+energystoragenum+I]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualnumarray*virtualloadnum*T
					+controllableunitnum*T+energystoragenum*T+I*T+J+1;
			rowpltv[controllableunitnum+energystoragenum+I]=1;
		}
		for(int I=0;I<loadnum;I++)
		{
			colno2[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
				+renewableenergynumarray*renewableenergynum*T+I*T+J+1;
			row2[0]=Loaddata[I].aloss*Loaddata[I].Pdt[J];
			colno2[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualnumarray*virtualloadnum*T
					+controllableunitnum*T+energystoragenum*T+renewableenergynum*T+I*T+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, Loaddata[I].aloss*Loaddata[I].Pdt[J]);

			colnopltv[controllableunitnum+energystoragenum+renewableenergynum+I]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualnumarray*virtualloadnum*T
					+controllableunitnum*T+energystoragenum*T+renewableenergynum*T+I*T+J+1;
			rowpltv[controllableunitnum+energystoragenum+renewableenergynum+I]=1;
		}
		for(int I=0;I<virtualloadnum;I++)
		{
			//Ppunisht>0,Pvirtualt
			colno2[0]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
				+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualloadnum*T+I*T+J+1;//
			row2[0]=-Virtualloaddata[I].aloss;
			colno2[1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualnumarray*virtualloadnum*T
					+controllableunitnum*T+energystoragenum*T+renewableenergynum*T+loadnum*T+I*T+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, 0);

			colnopltv[controllableunitnum+energystoragenum+renewableenergynum+loadnum+I]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualnumarray*virtualloadnum*T
					+controllableunitnum*T+energystoragenum*T+renewableenergynum*T+loadnum*T+I*T+J+1;
			rowpltv[controllableunitnum+energystoragenum+renewableenergynum+loadnum+I]=1;
		}
		//Pbuy Psell
		colno3[0]=2*T+J+1;
		row3[0]=-Griddata.aloss;
		colno3[1]=3*T+J+1;
		row3[1]=-Griddata.aloss;
		colno3[2]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualnumarray*virtualloadnum*T
					+controllableunitnum*T+energystoragenum*T+renewableenergynum*T+loadnum*T+virtualloadnum*T+J+1;
		row3[2]=1;
		add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, EQ, 0);

		colnopltv[controllableunitnum+energystoragenum+renewableenergynum+loadnum+virtualloadnum]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualnumarray*virtualloadnum*T
					+controllableunitnum*T+energystoragenum*T+renewableenergynum*T+loadnum*T+virtualloadnum*T+J+1;
		rowpltv[controllableunitnum+energystoragenum+renewableenergynum+loadnum+virtualloadnum]=1;
			//all
		colnopltv[controllableunitnum+energystoragenum+renewableenergynum+loadnum+virtualloadnum+1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualnumarray*virtualloadnum*T
					+controllableunitnum*T+energystoragenum*T+renewableenergynum*T+loadnum*T+virtualloadnum*T+T+J+1;
		rowpltv[controllableunitnum+energystoragenum+renewableenergynum+loadnum+virtualloadnum+1]=-1;
		add_constraintex(lp, controllableunitnum+energystoragenum+renewableenergynum+loadnum+virtualloadnum+1+1, rowpltv, colnopltv, EQ, 0);//EQ LE
	}
	delete[] colnopltv;
	delete[] rowpltv;

}
void SCHEDULE::LOSSconstraint_lay2(lprec *lp,int Ttemp)
{
	int colno2[2];
	double row2[2];
	int colno3[3];
	double row3[3];
	int* colnopltv;
	double* rowpltv;
	colnopltv=new int[controllableunitnum+energystoragenum+renewableenergynum+loadnum+virtualloadnum+1+1];
	CHECKPOINTER(colnopltv);
	rowpltv=new double[controllableunitnum+energystoragenum+renewableenergynum+loadnum+virtualloadnum+1+1];
	CHECKPOINTER(rowpltv);
	
	for(int J=0;J<Ttemp;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			//Pithandel +=Pit[I][J];
			colno2[0]=onearray*Ttemp+I*Ttemp+J+1;
			row2[0]=-Controllableunitdata[I].aloss;
			colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualnumarray*virtualloadnum*Ttemp+loadnum+I*Ttemp+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, 0);
			colnopltv[I]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualnumarray*virtualloadnum*Ttemp+loadnum+I*Ttemp+J+1;
			rowpltv[I]=1;
		}
		for(int I=0;I<energystoragenum;I++)
		{
			//Pkthandel +=Pgkt[I][J]-Ppkt[I][J];
			colno3[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+1*energystoragenum*Ttemp+I*Ttemp+J+1;
			row3[0]=-Energystoragedata[I].aloss;
			colno3[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+2*energystoragenum*Ttemp+I*Ttemp+J+1;
			row3[1]=-Energystoragedata[I].aloss;
			colno3[2]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualnumarray*virtualloadnum*Ttemp+loadnum+controllableunitnum*Ttemp+I*Ttemp+J+1;
			row3[2]=1;
			add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, EQ, 0);

			colnopltv[controllableunitnum+I]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualnumarray*virtualloadnum*Ttemp+loadnum+controllableunitnum*Ttemp+I*Ttemp+J+1;
			rowpltv[controllableunitnum+I]=1;
		}
		for(int I=0;I<renewableenergynum;I++)
		{
			//	Pnewthandel +=Pnewt[I][J];
			colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+I*Ttemp+J+1;
			row2[0]=-Renewableenergydata[I].aloss;
			colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualnumarray*virtualloadnum*Ttemp+loadnum
					+controllableunitnum*Ttemp+energystoragenum*Ttemp+I*Ttemp+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, 0);

			colnopltv[controllableunitnum+energystoragenum+I]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualnumarray*virtualloadnum*Ttemp+loadnum
					+controllableunitnum*Ttemp+energystoragenum*Ttemp+I*Ttemp+J+1;
			rowpltv[controllableunitnum+energystoragenum+I]=1;
		}
		for(int I=0;I<loadnum;I++)
		{
			colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+I*Ttemp+J+1;
			row2[0]=Loaddata[I].aloss*Loaddata[I].Pdt[J];
			colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualnumarray*virtualloadnum*Ttemp+loadnum
					+controllableunitnum*Ttemp+energystoragenum*Ttemp+renewableenergynum*Ttemp+I*Ttemp+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, Loaddata[I].aloss*Loaddata[I].Pdt[J]);

			colnopltv[controllableunitnum+energystoragenum+renewableenergynum+I]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualnumarray*virtualloadnum*Ttemp+loadnum
					+controllableunitnum*Ttemp+energystoragenum*Ttemp+renewableenergynum*Ttemp+I*Ttemp+J+1;
			rowpltv[controllableunitnum+energystoragenum+renewableenergynum+I]=1;
		}
		for(int I=0;I<virtualloadnum;I++)
		{
			//Ppunisht>0,Pvirtualt
			colno2[0]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
				+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualloadnum*Ttemp+I*Ttemp+J+1;
			row2[0]=-Virtualloaddata[I].aloss;
			if(I>6)
			{row2[0]=0;
			}
			colno2[1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualnumarray*virtualloadnum*Ttemp+loadnum
					+controllableunitnum*Ttemp+energystoragenum*Ttemp+renewableenergynum*Ttemp+loadnum*Ttemp+I*Ttemp+J+1;
			row2[1]=1;
			add_constraintex(lp, sizeof(colno2) / sizeof(*colno2), row2, colno2, EQ, 0);

			colnopltv[controllableunitnum+energystoragenum+renewableenergynum+loadnum+I]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualnumarray*virtualloadnum*Ttemp+loadnum
					+controllableunitnum*Ttemp+energystoragenum*Ttemp+renewableenergynum*Ttemp+loadnum*Ttemp+I*Ttemp+J+1;
			rowpltv[controllableunitnum+energystoragenum+renewableenergynum+loadnum+I]=1;
		}
		//Pbuy Psell
		colno3[0]=2*Ttemp+J+1;
		row3[0]=-Griddata.aloss;
		colno3[1]=3*Ttemp+J+1;
		row3[1]=-Griddata.aloss;
		colno3[2]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualnumarray*virtualloadnum*Ttemp+loadnum
					+controllableunitnum*Ttemp+energystoragenum*Ttemp+renewableenergynum*Ttemp+loadnum*Ttemp+virtualloadnum*Ttemp+J+1;
		row3[2]=1;
		add_constraintex(lp, sizeof(colno3) / sizeof(*colno3), row3, colno3, EQ, 0);

		colnopltv[controllableunitnum+energystoragenum+renewableenergynum+loadnum+virtualloadnum]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualnumarray*virtualloadnum*Ttemp+loadnum
					+controllableunitnum*Ttemp+energystoragenum*Ttemp+renewableenergynum*Ttemp+loadnum*Ttemp+virtualloadnum*Ttemp+J+1;
		rowpltv[controllableunitnum+energystoragenum+renewableenergynum+loadnum+virtualloadnum]=1;
			//all
		colnopltv[controllableunitnum+energystoragenum+renewableenergynum+loadnum+virtualloadnum+1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualnumarray*virtualloadnum*Ttemp+loadnum
					+controllableunitnum*Ttemp+energystoragenum*Ttemp+renewableenergynum*Ttemp+loadnum*Ttemp+virtualloadnum*Ttemp+Ttemp+J+1;
		rowpltv[controllableunitnum+energystoragenum+renewableenergynum+loadnum+virtualloadnum+1]=-1;
		add_constraintex(lp, controllableunitnum+energystoragenum+renewableenergynum+loadnum+virtualloadnum+1+1, rowpltv, colnopltv, EQ, 0);//EQ LE
	}
	delete[] colnopltv;
	delete[] rowpltv;

}
void SCHEDULE::inputscheduleloss()//输入一天的计算数据
{
	int a,b,num;
	char c[20];

	ifstream fin1("output_load.txt");
	if (!fin1)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	for (int i=1;i<=pf.Data.numNode;i++)
	{
		fin1>>a;
		fin1>>b;
		fin1>>c;
		num=i;
		for (int k=1;k<=pf.Data.numNode;k++)
		{
			if(b==pf.Data.Nodeinf[k][5])
			{
				num=k;
				break;
			}
		}
		for(int j=1;j<=Ttotal;j++)
		{
			fin1>>PL[num][j];
			PL[num][j]=(1-PL[num][j])*Loaddata[num-1].Pdttotal[j-1];
		}
		//cout<<num<<endl;
	}
	fin1.close();
	ifstream fin2("output_new.txt");
	if (!fin2)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	for (int i=1;i<=renewableenergynum;i++)
	{
		fin2>>a;
		fin2>>b;
		fin2>>c;
		num=i;
		for (int k=1;k<=pf.Data.numDes;k++)
		{
			if(b==pf.Data.Desinf[k][8])
			{
				num=k;
				break;
			}
		}
		for(int j=1;j<=Ttotal;j++)
		{
			fin2>>PG[num][j];
		}
		//cout<<num<<endl;
	}
	fin2.close();
	ifstream fin3("output_storage.txt");
	if (!fin3)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	for (int i=1;i<=energystoragenum;i++)
	{
		fin3>>a;
		fin3>>b;
		fin3>>c;
		num=i;
		for (int k=1;k<=pf.Data.numDes;k++)
		{
			if(b==pf.Data.Desinf[k][8])
			{
				num=k;
				break;
			}
		}
		for(int j=1;j<=Ttotal;j++)
		{
			fin3>>PG[num][j];
		}
		//cout<<num<<endl;
	}
	fin3.close();
	ifstream fin4("output_unit.txt");
	if (!fin4)
	{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
	for (int i=1;i<=controllableunitnum;i++)
	{
		fin4>>a;
		fin4>>b;
		fin4>>c;
		num=i;
		for (int k=1;k<=pf.Data.numDes;k++)
		{
			if(b==pf.Data.Desinf[k][8])
			{
				num=k;
				break;
			}
		}
		for(int j=1;j<=Ttotal;j++)
		{
			fin4>>PG[num][j];
		}
	}
	fin4.close();

}
void SCHEDULE::calculateloss()
{
	pf.Initilization(gridislanddecision);//gridislanddecision
	int num;
	//double lossa[14+1];
	double **Vdginf;
	Vdginf=(double **)new double[pf.Data.numDes+1];
	for(int i=0;i<=pf.Data.numDes;i++)
		Vdginf[i]=new double[3+1];

	for(int i=1;i<=pf.Data.numDes;i++)
	{
		Vdginf[i][1]=i;
		Vdginf[i][3]=0;
	}

	PL=new double *[pf.Data.numNode+1];
	for (int i=0;i<=pf.Data.numNode;i++)
	{
		PL[i]=new double [Ttotal+1];
	}
	PG=new double *[pf.Data.numDes+1];
	for (int i=0;i<=pf.Data.numDes;i++)
	{
		PG[i]=new double [Ttotal+1];
	}
	lossa=new double [pf.Data.numBran+1];
	inputscheduleloss();//输入日前调度数据
	for(int i=1;i<pf.Data.numBran+1;i++)
	{
		lossa[i]=0;
	}
	for(int j=1;j<=Ttotal;j++)
	{
	for(int i=1;i<=pf.Data.numNode;i++)
	{
		num=pf.Data.Nodeinf[i][1];
		pf.node[num].PQ[1].set(PL[i][j]/100,0);//100
	}
	for(int i=1;i<=pf.Data.numDes;i++)
	{
		Vdginf[i][2]=PG[i][j]/100;
	}
	pf.Levelset();
	pf.formalX();
	pf.Dgnodeset();
	pf.dgset(Vdginf);
	pf.calculate(1);
	pf.output();
	for(int i=1;i<pf.Data.numBran+1;i++)
	{
		lossa[i]+=pf.branchloss[i]/Ttotal;
	}
	}
	for(int i=1;i<pf.Data.numBran+1;i++)
	{
		pf.branch[i].lossa=lossa[i];
		//cout<<lossa[i]<<" "<<pf.branch[i].lossa<<endl;
	}
	losssearch();
	outputlossa();
	for(int i=0;i<pf.Data.numDes+1;i++)
	{
		delete[] Vdginf[i];
	}
	delete[] Vdginf;
	for(int i=0;i<pf.Data.numNode+1;i++)
	{
		delete[] PL[i];
	}
	delete[] PL;
	for(int i=0;i<pf.Data.numDes+1;i++)
	{
		delete[] PG[i];
	}
	delete[] PG;
	delete[] lossa;
/*	*/
}
void SCHEDULE::losssearch()
{
	//寻找对应关系
	if(gridislanddecision==0)
	{
		Griddata.aloss=pf.branch[pf.Data.balanceBus].lossa;
	}
	else
	{
		Griddata.aloss=0;
	}
	for(int I=0;I<controllableunitnum;I++)
	{
		for(int i=1;i<pf.Data.numBran+1;i++)
		{
			if(Controllableunitdata[I].ID32==pf.node[pf.branch[i].i].ID32)
			{
				Controllableunitdata[I].aloss=pf.branch[i].lossa;
				Controllableunitdata[I].nodenum=pf.branch[i].j;
				break;
			}
			else if(Controllableunitdata[I].ID32==pf.node[pf.branch[i].j].ID32)
			{
				Controllableunitdata[I].aloss=pf.branch[i].lossa;
				Controllableunitdata[I].nodenum=pf.branch[i].i;
				break;
			}
			
		}
		//cout<<Controllableunitdata[I].aloss<<endl;
	}
	for(int I=0;I<energystoragenum;I++)
	{
		for(int i=1;i<pf.Data.numBran+1;i++)
		{
			if(Energystoragedata[I].ID32==pf.node[pf.branch[i].i].ID32)
			{
				Energystoragedata[I].aloss=pf.branch[i].lossa;
				Energystoragedata[I].nodenum=pf.branch[i].j;
				break;
			}
			else if(Energystoragedata[I].ID32==pf.node[pf.branch[i].j].ID32)
			{
				Energystoragedata[I].aloss=pf.branch[i].lossa;
				Energystoragedata[I].nodenum=pf.branch[i].i;
				break;
			}
			
		}
		//cout<<Energystoragedata[I].aloss<<endl;
	}
	for(int I=0;I<renewableenergynum;I++)
	{
		for(int i=1;i<pf.Data.numBran+1;i++)
		{
			if(Renewableenergydata[I].ID32==pf.node[pf.branch[i].i].ID32)
			{
				Renewableenergydata[I].aloss=pf.branch[i].lossa;
				Renewableenergydata[I].nodenum=pf.branch[i].j;
				break;
			}
			else if(Renewableenergydata[I].ID32==pf.node[pf.branch[i].j].ID32)
			{
				Renewableenergydata[I].aloss=pf.branch[i].lossa;
				Renewableenergydata[I].nodenum=pf.branch[i].i;
				break;
			}
			
		}
		//cout<<Renewableenergydata[I].aloss<<endl;
	}
	for(int I=0;I<loadnum;I++)
	{
		for(int i=1;i<pf.Data.numBran+1;i++)
		{
			if(Loaddata[I].ID32==pf.node[pf.branch[i].i].ID32)
			{
				Loaddata[I].aloss=pf.branch[i].lossa;
				Loaddata[I].nodenum=pf.branch[i].j;
				break;
			}
			else if(Loaddata[I].ID32==pf.node[pf.branch[i].j].ID32)
			{
				Loaddata[I].aloss=pf.branch[i].lossa;
				Loaddata[I].nodenum=pf.branch[i].i;
				break;
			}
			
		}
		//cout<<Loaddata[I].aloss<<endl;
	}
	int* temp;
	temp=new int [mglevel];
	for(int I=0;I<virtualloadnum;I++)
	{
		//int temp=-1;
		for(int Imgl=0;Imgl<mglevel;Imgl++)
		{
			temp[mglevel-Imgl-1]=-1;
			if(Virtualloaddata[I].levelIdentifier[mglevel-Imgl-1]>0)
			{
				for(int Icon=0;Icon<controllableunitnum;Icon++)
				{
					if((Imgl>0&&Controllableunitdata[Icon].levelIdentifier[mglevel-Imgl-1]==Virtualloaddata[I].levelIdentifier[mglevel-Imgl-1]&&Controllableunitdata[Icon].levelIdentifier[mglevel-Imgl-1+1]==0)||(Imgl==0&&Controllableunitdata[Icon].levelIdentifier[mglevel-Imgl-1]==Virtualloaddata[I].levelIdentifier[mglevel-Imgl-1]))
					{
						temp[mglevel-Imgl-1]=Controllableunitdata[Icon].nodenum;
						break;
					}
				}
				if(temp[mglevel-Imgl-1]<0)
				{
					for(int Iene=0;Iene<energystoragenum;Iene++)
					{
						//if(Energystoragedata[Iene].levelIdentifier[mglevel-Imgl-1]==Virtualloaddata[I].levelIdentifier[mglevel-Imgl-1]&&Energystoragedata[Iene].levelIdentifier[mglevel-Imgl-1]!=0)
						if((Imgl>0&&Energystoragedata[Iene].levelIdentifier[mglevel-Imgl-1]==Virtualloaddata[I].levelIdentifier[mglevel-Imgl-1]&&Energystoragedata[Iene].levelIdentifier[mglevel-Imgl-1+1]==0)||(Imgl==0&&Energystoragedata[Iene].levelIdentifier[mglevel-Imgl-1]==Virtualloaddata[I].levelIdentifier[mglevel-Imgl-1]))
						{
							temp[mglevel-Imgl-1]=Energystoragedata[Iene].nodenum;
							break;
						}
					}
				}
				if(temp[mglevel-Imgl-1]<0)
				{
					for(int Iren=0;Iren<renewableenergynum;Iren++)
					{
						//if(Renewableenergydata[Iren].levelIdentifier[mglevel-Imgl-1]==Virtualloaddata[I].levelIdentifier[mglevel-Imgl-1]&&Renewableenergydata[Iren].levelIdentifier[mglevel-Imgl-1]!=0)
						if((Imgl>0&&Renewableenergydata[Iren].levelIdentifier[mglevel-Imgl-1]==Virtualloaddata[I].levelIdentifier[mglevel-Imgl-1]&&Renewableenergydata[Iren].levelIdentifier[mglevel-Imgl-1+1]==0)||(Imgl==0&&Renewableenergydata[Iren].levelIdentifier[mglevel-Imgl-1]==Virtualloaddata[I].levelIdentifier[mglevel-Imgl-1]))
						{
							temp[mglevel-Imgl-1]=Renewableenergydata[Iren].nodenum;
							break;
						}
					}
				}
				if(temp[mglevel-Imgl-1]<0)
				{
					for(int Iloa=0;Iloa<loadnum;Iloa++)
					{
						//if(Loaddata[Iloa].levelIdentifier[mglevel-Imgl-1]==Virtualloaddata[I].levelIdentifier[mglevel-Imgl-1]&&Loaddata[Iloa].levelIdentifier[mglevel-Imgl-1]!=0)
						if((Imgl>0&&Loaddata[Iloa].levelIdentifier[mglevel-Imgl-1]==Virtualloaddata[I].levelIdentifier[mglevel-Imgl-1]&&Loaddata[Iloa].levelIdentifier[mglevel-Imgl-1+1]==0)||(Imgl==0&&Loaddata[Iloa].levelIdentifier[mglevel-Imgl-1]==Virtualloaddata[I].levelIdentifier[mglevel-Imgl-1]))
						{
							temp[mglevel-Imgl-1]=Loaddata[Iloa].nodenum;
							break;
						}
					}
				}
				//break;//Imgl
			}
		}

		for(int Imgl=0;Imgl<mglevel-1;Imgl++)
		{
			if(Virtualloaddata[I].levelIdentifier[mglevel-Imgl-1]>0)
			{
				for(int i=1;i<pf.Data.numBran+1;i++)
				{
					if((temp[mglevel-Imgl-1]==pf.branch[i].i||temp[mglevel-Imgl-1]==pf.branch[i].j))
					{
						if((temp[mglevel-Imgl-1-1]==pf.branch[i].i||temp[mglevel-Imgl-1-1]==pf.branch[i].j||temp[mglevel-Imgl-1-1]==-1))
						{
							Virtualloaddata[I].aloss=pf.branch[i].lossa;
							break;
						}
					}
				}
				break;
			}
			
		}
	}
	delete[] temp;
}
void SCHEDULE::getlossa0()
{
	Griddata.aloss=0;
	for(int I=0;I<controllableunitnum;I++)
	{
		Controllableunitdata[I].aloss=0;
	}
	for(int I=0;I<energystoragenum;I++)
	{
		Energystoragedata[I].aloss=0;
	}
	for(int I=0;I<renewableenergynum;I++)
	{
		Renewableenergydata[I].aloss=0;
	}
	for(int I=0;I<loadnum;I++)
	{
		Loaddata[I].aloss=0;
	}
	for(int I=0;I<virtualloadnum;I++)
	{
		Virtualloaddata[I].aloss=0;
	}
}
void SCHEDULE::getlossa()
{
	/*for(int I=0;I<controllableunitnum;I++)
	{
		Controllableunitdata[I].aloss=0.01;
	}
	for(int I=0;I<energystoragenum;I++)
	{
		Energystoragedata[I].aloss=0;
	}
	for(int I=0;I<renewableenergynum;I++)
	{
		Renewableenergydata[I].aloss=0.01;
	}
	for(int I=0;I<loadnum;I++)
	{
		Loaddata[I].aloss=0.01;
	}
	for(int I=0;I<virtualloadnum;I++)
	{
		Virtualloaddata[I].aloss=0.01;
	}
	Loaddata[0].aloss=0.00071;
	Loaddata[1].aloss=0.00075;
	Loaddata[2].aloss=0.00098;
	Loaddata[3].aloss=0.00121;
	Loaddata[4].aloss=0.00028;
	Loaddata[5].aloss=0.00036;
	Loaddata[6].aloss=0.00120;
	Loaddata[7].aloss=0.00135;
	Loaddata[8].aloss=0.00148;
	Renewableenergydata[0].aloss=0.00260;
	Renewableenergydata[1].aloss=0.00276;
	Loaddata[0].aloss=0.000709029;
	Loaddata[1].aloss=0.000745438;
	Loaddata[2].aloss=0.000976133;
	Loaddata[3].aloss=0.0012131;
	Loaddata[4].aloss=0.000282803;
	Loaddata[5].aloss=0.000359544;
	Loaddata[6].aloss=0.00119486;
	Loaddata[7].aloss=0.00135294;
	Loaddata[8].aloss=0.00148068;
	Renewableenergydata[0].aloss=0.00260439;
	Renewableenergydata[1].aloss=0.00276986;*/
	if(gridislanddecision==0)
	{
		ifstream fin1("branchlossgrid.txt");
		if (!fin1)
		{cout <<"\n不能打开这个文件 "<<endl; exit(1);}//检查文件的数据个数
		fin1>>Griddata.aloss;
		for(int I=0;I<controllableunitnum;I++)
		{
			fin1>>Controllableunitdata[I].aloss;
		}
		for(int I=0;I<energystoragenum;I++)
		{
			fin1>>Energystoragedata[I].aloss;
		}
		for(int I=0;I<renewableenergynum;I++)
		{
			fin1>>Renewableenergydata[I].aloss;
		}
		for(int I=0;I<loadnum;I++)
		{
			fin1>>Loaddata[I].aloss;
		}
		for(int I=0;I<virtualloadnum;I++)
		{
			fin1>>Virtualloaddata[I].aloss;
		}
		fin1.close();
	}
	else
	{
		ifstream fin1("branchlossisland.txt");
		if (!fin1)
		{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
		fin1>>Griddata.aloss;
		for(int I=0;I<controllableunitnum;I++)
		{
			fin1>>Controllableunitdata[I].aloss;
		}
		for(int I=0;I<energystoragenum;I++)
		{
			fin1>>Energystoragedata[I].aloss;
		}
		for(int I=0;I<renewableenergynum;I++)
		{
			fin1>>Renewableenergydata[I].aloss;
		}
		for(int I=0;I<loadnum;I++)
		{
			fin1>>Loaddata[I].aloss;
		}
		for(int I=0;I<virtualloadnum;I++)
		{
			fin1>>Virtualloaddata[I].aloss;
		}
		fin1.close();
	}

}
void SCHEDULE::outputlossa()
{
	if(gridislanddecision==0)
	{
		ofstream fout("branchlossgrid.txt");
		if (!fout)
		{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
		fout<<Griddata.aloss<<endl;
		for(int I=0;I<controllableunitnum;I++)
		{
			fout<<Controllableunitdata[I].aloss<<" ";
		}
		fout<<endl;
		for(int I=0;I<energystoragenum;I++)
		{
			fout<<Energystoragedata[I].aloss<<" ";
		}
		fout<<endl;
		for(int I=0;I<renewableenergynum;I++)
		{
			fout<<Renewableenergydata[I].aloss<<" ";
		}
		fout<<endl;
		for(int I=0;I<loadnum;I++)
		{
			fout<<Loaddata[I].aloss<<" ";
		}
		fout<<endl;
		for(int I=0;I<virtualloadnum;I++)
		{
			fout<<Virtualloaddata[I].aloss<<" ";
		}
		fout<<endl;
		fout.close();
	}
	else
	{
		ofstream fout("branchlossisland.txt");
		if (!fout)
		{cout <<"\n不能打开这个文件 "<<endl; exit(1);}
		fout<<Griddata.aloss<<endl;
		for(int I=0;I<controllableunitnum;I++)
		{
			fout<<Controllableunitdata[I].aloss<<" ";
		}
		fout<<endl;
		for(int I=0;I<energystoragenum;I++)
		{
			fout<<Energystoragedata[I].aloss<<" ";
		}
		fout<<endl;
		for(int I=0;I<renewableenergynum;I++)
		{
			fout<<Renewableenergydata[I].aloss<<" ";
		}
		fout<<endl;
		for(int I=0;I<loadnum;I++)
		{
			fout<<Loaddata[I].aloss<<" ";
		}
		fout<<endl;
		for(int I=0;I<virtualloadnum;I++)
		{
			fout<<Virtualloaddata[I].aloss<<" ";
		}
		fout<<endl;
		fout.close();
	}
	
}

void SCHEDULE::OVERALLBALANCEconstraint(lprec *lp)
{
	int colno1[1];
	double row1[1];
	int* colnoprtv;
	double* rowprtv;
	int* colnopdtv;
	double* rowpdtv;
	colnoprtv=new int[controllableunitnum+energystoragenum];
	CHECKPOINTER(colnoprtv);
	rowprtv=new double[controllableunitnum+energystoragenum];
	CHECKPOINTER(rowprtv);
	colnopdtv=new int[controllableunitnum+energystoragenum*2+renewableenergynum+1+1];
	CHECKPOINTER(colnopdtv);
	rowpdtv=new double[controllableunitnum+energystoragenum*2+renewableenergynum+1+1];
	CHECKPOINTER(rowpdtv);
	for(int J=0;J<T;J++)
	{
		//model.add(Pdt[J] >=0);
		colno1[0]=J+1;
		row1[0]=1;
		//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, 0);
		//IloExpr Pithandel(env);
		//IloExpr Pkthandel(env);
		//IloExpr Rithandel(env);
		//IloExpr Rkthandel(env);
		//IloExpr Pnewthandel(env);
		//IloExpr Pcuthandel(env);
		for(int I=0;I<controllableunitnum;I++)
		{
			//Pithandel +=Pit[I][J];
			//Rithandel +=Rit[I][J];	
			colnopdtv[I]=onearray*T+I*T+J+1;
			rowpdtv[I]=1;
			colnoprtv[I]=onearray*T+1*controllableunitnum*T+I*T+J+1;
			rowprtv[I]=1;
		}
		for(int I=0;I<energystoragenum;I++)
		{
			//Pkthandel +=Pgkt[I][J]-Ppkt[I][J];
			//Rkthandel +=Rkt[I][J];
			colnopdtv[controllableunitnum+I]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+1*energystoragenum*T+I*T+J+1;
			rowpdtv[controllableunitnum+I]=1;
			colnopdtv[controllableunitnum+energystoragenum+I]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+2*energystoragenum*T+I*T+J+1;
			rowpdtv[controllableunitnum+energystoragenum+I]=-1;
			colnoprtv[controllableunitnum+I]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+6*energystoragenum*T+I*T+J+1;
			rowprtv[controllableunitnum+I]=1;
		}
		for(int I=0;I<renewableenergynum;I++)
		{
			//	Pnewthandel +=Pnewt[I][J];
			colnopdtv[controllableunitnum+energystoragenum*2+I]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T+I*T+J+1;
			rowpdtv[controllableunitnum+energystoragenum*2+I]=1;
		}

		//model.add(Rithandel+Rkthandel>=Prt[J]);
		//model.add(Pithandel+Pkthandel+Pnewthandel==Pdt[J]);
		add_constraintex(lp, controllableunitnum+energystoragenum, rowprtv, colnoprtv, GE, Prt[J]);
		colnopdtv[controllableunitnum+energystoragenum*2+renewableenergynum]=J+1;
		rowpdtv[controllableunitnum+energystoragenum*2+renewableenergynum]=-1;
		colnopdtv[controllableunitnum+energystoragenum*2+renewableenergynum+1]=onearray*T+(controllableunitnumarray-2+node+node-1)*controllableunitnum*T+energystoragenumarray*energystoragenum*T
					+renewableenergynumarray*renewableenergynum*T+loadnumarray*loadnum*T+virtualnumarray*virtualloadnum*T
					+controllableunitnum*T+energystoragenum*T+renewableenergynum*T+loadnum*T+virtualloadnum*T+T+J+1;;
		rowpdtv[controllableunitnum+energystoragenum*2+renewableenergynum+1]=-1;//
		add_constraintex(lp, controllableunitnum+energystoragenum*2+renewableenergynum+1+1, rowpdtv, colnopdtv, GE, 0);//EQ GE
	}
	delete[] colnoprtv;
	delete[] rowprtv;
	delete[] colnopdtv;
	delete[] rowpdtv;


}

void SCHEDULE::OVERALLBALANCEconstraint_lay2(lprec *lp,int Ttemp)
{
	int colno1[1];
	double row1[1];
	int* colnoprtv;
	double* rowprtv;
	int* colnopdtv;
	double* rowpdtv;
	colnoprtv=new int[controllableunitnum+energystoragenum];
	CHECKPOINTER(colnoprtv);
	rowprtv=new double[controllableunitnum+energystoragenum];
	CHECKPOINTER(rowprtv);
	colnopdtv=new int[controllableunitnum+energystoragenum*2+renewableenergynum+1+1+1];
	CHECKPOINTER(colnopdtv);
	rowpdtv=new double[controllableunitnum+energystoragenum*2+renewableenergynum+1+1+1];
	CHECKPOINTER(rowpdtv);
	for(int J=0;J<Ttemp;J++)
	{
		//model.add(Pdt[J] >=0);
		colno1[0]=J+1;
		row1[0]=1;
		//add_constraintex(lp, sizeof(colno1) / sizeof(*colno1), row1, colno1, GE, BIGNUM);
		//IloExpr Pithandel(env);
		//IloExpr Pkthandel(env);
		//IloExpr Rithandel(env);
		//IloExpr Rkthandel(env);
		//IloExpr Pnewthandel(env);
		//IloExpr Pcuthandel(env);
		for(int I=0;I<controllableunitnum;I++)
		{
			//Pithandel +=Pit[I][J];
			//Rithandel +=Rit[I][J];	
			colnopdtv[I]=onearray*Ttemp+I*Ttemp+J+1;
			rowpdtv[I]=1;
			colnoprtv[I]=onearray*Ttemp+1*controllableunitnum*Ttemp+I*Ttemp+J+1;
			rowprtv[I]=1;
		}
		for(int I=0;I<energystoragenum;I++)
		{
			//Pkthandel +=Pgkt[I][J]-Ppkt[I][J];
			//Rkthandel +=Rkt[I][J];
			colnopdtv[controllableunitnum+I]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+1*energystoragenum*Ttemp+I*Ttemp+J+1;
			rowpdtv[controllableunitnum+I]=1;
			colnopdtv[controllableunitnum+energystoragenum+I]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+2*energystoragenum*Ttemp+I*Ttemp+J+1;
			rowpdtv[controllableunitnum+energystoragenum+I]=-1;
			colnoprtv[controllableunitnum+I]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+6*energystoragenum*Ttemp+I*Ttemp+J+1;
			rowprtv[controllableunitnum+I]=1;
		}
		for(int I=0;I<renewableenergynum;I++)
		{
			//	Pnewthandel +=Pnewt[I][J];
			colnopdtv[controllableunitnum+energystoragenum*2+I]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp+I*Ttemp+J+1;
			rowpdtv[controllableunitnum+energystoragenum*2+I]=1;
		}

		//model.add(Rithandel+Rkthandel>=Prt[J]);
		//model.add(Pithandel+Pkthandel+Pnewthandel==Pdt[J]);
		add_constraintex(lp, controllableunitnum+energystoragenum, rowprtv, colnoprtv, GE, Prtlay2[J]);
		colnopdtv[controllableunitnum+energystoragenum*2+renewableenergynum]=J+1;
		rowpdtv[controllableunitnum+energystoragenum*2+renewableenergynum]=-1;
		colnopdtv[controllableunitnum+energystoragenum*2+renewableenergynum+1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualnumarray*virtualloadnum*Ttemp+loadnum
					+controllableunitnum*Ttemp+energystoragenum*Ttemp+renewableenergynum*Ttemp+loadnum*Ttemp+virtualloadnum*Ttemp+Ttemp+J+1;
		rowpdtv[controllableunitnum+energystoragenum*2+renewableenergynum+1]=-1;
		//多余
		colnopdtv[controllableunitnum+energystoragenum*2+renewableenergynum+1+1]=onearray*Ttemp+(controllableunitnumarray-2+node+node-1)*controllableunitnum*Ttemp+energystoragenumarray*energystoragenum*Ttemp
					+renewableenergynumarray*renewableenergynum*Ttemp+loadnumarray*loadnum*Ttemp+virtualnumarray*virtualloadnum*Ttemp+loadnum
					+controllableunitnum*Ttemp+energystoragenum*Ttemp+renewableenergynum*Ttemp+loadnum*Ttemp+virtualloadnum*Ttemp+Ttemp*2+J+1;
		rowpdtv[controllableunitnum+energystoragenum*2+renewableenergynum+1+1]=-1;
		if(modeldecision==0)
		{
			add_constraintex(lp, controllableunitnum+energystoragenum*2+renewableenergynum+1+1+1, rowpdtv, colnopdtv, GE, 0);//EQ GE
		}
		else
		{
			add_constraintex(lp, controllableunitnum+energystoragenum*2+renewableenergynum+1+1+1, rowpdtv, colnopdtv, EQ, 0);//EQ GE
		}
	}
	delete[] colnoprtv;
	delete[] rowprtv;
	delete[] colnopdtv;
	delete[] rowpdtv;


}

void SCHEDULE::set0()
{
	for(int J=0;J<T;J++)
	{
		for(int I=0;I<controllableunitnum;I++)
		{
			Controllableunitdata[I].Uit[J]=0;
			Controllableunitdata[I].Pit[J]=0;
		}
		for(int I=0;I<energystoragenum;I++)
		{
			Energystoragedata[I].Vkt[J]=0;
			Energystoragedata[I].Pgkt[J]=0;
			Energystoragedata[I].Ppkt[J]=0;
			Energystoragedata[I].Pkt[J]=0;
			Energystoragedata[I].WkC=0;
		}
		for(int I=0;I<renewableenergynum;I++)
		{
			Renewableenergydata[I].Pnewt[J]=0;
		}
		for(int I=0;I<loadnum;I++)
		{
			Loaddata[I].Ucutx[J]=0;
		}
	}

}
void SCHEDULE::decision()
{
	if(updatelossdecision>0)
	{
		for(int I=0;I<energystoragenum;I++)
		{
			Energystoragedata[I].Wktemp=Energystoragedata[I].Wk;
		}
		getlossa0();
		switch(gridislanddecision)
		{
		case 0:
			griddo_levelpunish();
			break;
		case 1:
			if(modeldecision==0)
			{
				Sum_do(0);
			}
			islanddo_levelpunish();
			break;
		default:
			break;
		} /**/
		calculateloss();//计算线损系数
		pf.releaseflow();
		getlossa();
		set0();
		for(int I=0;I<energystoragenum;I++)
		{
			Energystoragedata[I].Wk=Energystoragedata[I].Wktemp;
		}
		switch(gridislanddecision)
		{
		case 0:
			griddo_levelpunish();
			break;
		case 1:
			if(modeldecision==0)
			{
				Sum_do(0);
			}
			islanddo_levelpunish();
			break;
		default:
			break;
		}
		/**/
	}
	else
	{
		getlossa();
		switch(gridislanddecision)
		{
		case 0:
			griddo_levelpunish();
			break;
		case 1:
			if(modeldecision==0)
			{
				Sum_do(0);
			}
			islanddo_levelpunish();
			break;
		default:
			break;
		}
	}
	
}

int main (int argc, char **argv)
{
	SCHEDULE schedule;
	
	schedule.inputinitdata();
	schedule.inputdynamicdata();
	schedule.inputdecisiondata();
	schedule.set0();
	schedule.levelsearch();
	schedule.decision();
	cout<<"计算结束"<<endl;
	exit(0);/**/
}
