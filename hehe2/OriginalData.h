#include <iostream>
#include <fstream>
using namespace std;

class OriginalData
{
public:
	int numBus;//�ڵ���
	int balanceBus;//ƽ��ڵ���
	int numBran;//֧·��Ŀ
	int numDes;//�������Ŀ
	int numNode;//���ɽڵ���Ŀ
	int numPv;//PV�ڵ���
	int numVar;//��������

	int numTran;//��ѹ����Ŀ

	int **RelateMatricinf;
	int *Pvinf;
	double **Branchinf;
	double **Nodeinf;
	double **Transinf;
	double **Varinf;
	double **Desinf;
	void InputOriginalData();
	void InputfoundationData(char *filename);
	void InputbranchData(char *filename);
	void InputdesData(char *filename);
	void InputloadData(char *filename);
	void InputPVData(char *filename);
	void InputvarData(char *filename);
	~OriginalData();
	OriginalData();
	void releaseoriginal();
};