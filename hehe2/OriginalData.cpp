#include "OriginalData.h"
OriginalData::OriginalData()
{
	Branchinf=NULL;
	Desinf=NULL;
	Nodeinf=NULL;
	Pvinf=NULL;
	Varinf=NULL;
	RelateMatricinf=NULL;
	Transinf=NULL;
}
OriginalData::~OriginalData()
{
	/*for(int i=0;i<=numBran;i++)
	{
		delete[] Branchinf[i];
	}
	delete[] Branchinf;
	for(int i=0;i<=numDes;i++)
	{
		delete[] Desinf[i];
	}
	delete[] Desinf;
	for(int i=0;i<=numNode;i++)
	{
		delete[] Nodeinf[i];
	}
	delete[] Nodeinf;
	delete[] Pvinf;
	for(int i=0;i<=numVar;i++)
	{
		delete[] Varinf[i];
	}
	delete[] Varinf;
	for(int i=0;i<=numBus;i++)
	{
		delete[] RelateMatricinf[i];
	}
	delete[] RelateMatricinf;
	for(int i=0;i<=numTran;i++)
	{
		delete[] Transinf[i];
	}
	delete[] Transinf;*/
}
void OriginalData::releaseoriginal()
{
	if (Branchinf!=NULL)
	{
		for(int i=0;i<=numBran;i++)
		{
			delete[] Branchinf[i];
		}
		delete[] Branchinf;
		Branchinf=NULL;
	}
	if (Desinf!=NULL)
	{
		for(int i=0;i<=numDes;i++)
		{
			delete[] Desinf[i];
		}
		delete[] Desinf;
		Desinf=NULL;
	}
	if (Nodeinf!=NULL)
	{
		for(int i=0;i<=numNode;i++)
		{
			delete[] Nodeinf[i];
		}
		delete[] Nodeinf;
		Nodeinf=NULL;
	}
	if (Pvinf!=NULL)
	{
		delete[] Pvinf;
		Pvinf=NULL;
	}
	if (Varinf!=NULL)
	{
		for(int i=0;i<=numVar;i++)
		{
			delete[] Varinf[i];
		}
		delete[] Varinf;
		Varinf=NULL;
	}
	if (RelateMatricinf!=NULL)
	{
		for(int i=0;i<=numBus;i++)
		{
			delete[] RelateMatricinf[i];
		}
		delete[] RelateMatricinf;
		RelateMatricinf=NULL;
	}
	if (Transinf!=NULL)
	{
		for(int i=0;i<=numTran;i++)
		{
			delete[] Transinf[i];
		}
		delete[] Transinf;
		Transinf=NULL;
	}
}
void OriginalData::InputOriginalData()
{
	int i,j,k;
	int tempi,tempj;
/*	ifstream inputFile(filename);
	if(!inputFile)
	{
		cerr<<"can't open file!"<<endl;
		exit(0);
	}

//	inputFile>>numBus>>numNode>>numBran>>numTran>>numVar>>numDes;

	inputFile>>numBus>>balanceBus>>numBran>>numDes>>numNode>>numPv>>numVar;


	Branchinf=(double **)new double[numBran+1];
	for(i=0;i<=numBran;i++)
		Branchinf[i]=new double[6+1];

	for (i=1;i<=numBran;i++)
		for (j=1;j<=6;j++)
			inputFile>>Branchinf[i][j];


	Desinf=(double **)new double[numDes+1];
	for(i=0;i<=numDes;i++)
		Desinf[i]=new double[7+1+1];

	for (i=1;i<=numDes;i++)
		for (j=1;j<=7+1;j++)
			inputFile>>Desinf[i][j];	




	Nodeinf=(double **)new double[numNode+1];
	for(i=0;i<=numNode;i++)
		Nodeinf[i]=new double[4+1+1];

	for (i=1;i<=numNode;i++)
		for (j=1;j<=4+1;j++)
			inputFile>>Nodeinf[i][j];

	Pvinf=new int[numPv+1];
	for (i=1;i<=numPv;i++)
	{
		inputFile>>Pvinf[i];
	}


	Varinf=(double **)new double[numVar+1];
	for(i=0;i<=numVar;i++)
		Varinf[i]=new double[2+1];

	for (i=1;i<=numVar;i++)
		for (j=1;j<=2;j++)
			inputFile>>Varinf[i][j];

*/
	RelateMatricinf=(int **)new int[numBus+1];
	for(i=0;i<=numBus;i++)
		RelateMatricinf[i]=new int[numBus+1];

	for (i=1;i<=numBus;i++)
		for (j=1;j<=numBus;j++)
		  RelateMatricinf[i][j]=0;

	numTran=0;
	for (i=1;i<=numBran;i++)
	{
		tempi=Branchinf[i][2];
		tempj=Branchinf[i][3];
		RelateMatricinf[tempi][tempj]=1;
		RelateMatricinf[tempj][tempi]=1;

		if (Branchinf[i][6]<0)
		{
			numTran++;
		}
	}



	Transinf=(double **)new double[numTran+1];
	for(i=0;i<=numTran;i++)
		Transinf[i]=new double[7+1];

	j=0;
	for (i=1;i<=numBran;i++)
	{
		if (Branchinf[i][6]<0)
		{
			j++;
			for (k=1;k<=6;k++)
			{
				Transinf[j][k]=Branchinf[i][k];
			}
			Transinf[j][7]=i;
		}
	}




/*
	for (i=1;i<=numBran;i++)
	{
		tempi=Branchinf[i][2];
		tempj=Branchinf[i][3];
		RelateMatricinf[tempi][tempj]=1;
		RelateMatricinf[tempj][tempi]=1;
	}
	*/
}

void OriginalData::InputfoundationData(char *filename)
{
	int i,j,k;
	int tempi,tempj;
	ifstream inputFile(filename);
	if(!inputFile)
	{
		cerr<<"can't open file!"<<endl;
		exit(0);
	}
	inputFile>>numBus>>balanceBus>>numBran>>numDes>>numNode>>numPv>>numVar;

}
void OriginalData::InputbranchData(char *filename)
{
	int i,j,k;
	int tempi,tempj;
	ifstream inputFile(filename);
	if(!inputFile)
	{
		cerr<<"can't open file!"<<endl;
		exit(0);
	}
	Branchinf=(double **)new double[numBran+1];
	for(i=0;i<=numBran;i++)
		Branchinf[i]=new double[6+1];

	for (i=1;i<=numBran;i++)
		for (j=1;j<=6;j++)
			inputFile>>Branchinf[i][j];

}
void OriginalData::InputdesData(char *filename)
{
	int i,j,k;
	int tempi,tempj;
	ifstream inputFile(filename);
	if(!inputFile)
	{
		cerr<<"can't open file!"<<endl;
		exit(0);
	}
	Desinf=(double **)new double[numDes+1];
	for(i=0;i<=numDes;i++)
		Desinf[i]=new double[7+1+1];

	for (i=1;i<=numDes;i++)
		for (j=1;j<=7+1;j++)
			inputFile>>Desinf[i][j];	


}
void OriginalData::InputloadData(char *filename)
{
	int i,j,k;
	int tempi,tempj;
	ifstream inputFile(filename);
	if(!inputFile)
	{
		cerr<<"can't open file!"<<endl;
		exit(0);
	}
	Nodeinf=(double **)new double[numNode+1];
	for(i=0;i<=numNode;i++)
		Nodeinf[i]=new double[4+1+1];

	for (i=1;i<=numNode;i++)
		for (j=1;j<=4+1;j++)
			inputFile>>Nodeinf[i][j];


}
void OriginalData::InputPVData(char *filename)
{
	int i,j,k;
	int tempi,tempj;
	ifstream inputFile(filename);
	if(!inputFile)
	{
		cerr<<"can't open file!"<<endl;
		exit(0);
	}
	Pvinf=new int[numPv+1];
	for (i=1;i<=numPv;i++)
	{
		inputFile>>Pvinf[i];
	}

}
void OriginalData::InputvarData(char *filename)
{
	int i,j,k;
	int tempi,tempj;
	ifstream inputFile(filename);
	if(!inputFile)
	{
		cerr<<"can't open file!"<<endl;
		exit(0);
	}
	Varinf=(double **)new double[numVar+1];
	for(i=0;i<=numVar;i++)
		Varinf[i]=new double[2+1];

	for (i=1;i<=numVar;i++)
		for (j=1;j<=2;j++)
			inputFile>>Varinf[i][j];
}