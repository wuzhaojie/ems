#include <iostream>
#include <fstream>
using namespace std;

class OriginalData
{
public:
	int numBus;//节点数
	int balanceBus;//平衡节点编号
	int numBran;//支路数目
	int numDes;//发电机数目
	int numNode;//负荷节点数目
	int numPv;//PV节点数
	int numVar;//电容器数

	int numTran;//变压器数目

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