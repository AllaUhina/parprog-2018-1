#include <iostream>
#include <string>
#include <math.h>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	string resultPath = argv[1];
	string answerPath = argv[2];
	string pogrStr = argv[3];
	double pogr = stod(pogrStr);
	double resultD, answerD;//��������� ��������

	ifstream resultS(resultPath, ios::in | ios::binary);//����� ��� ����������
	ifstream answerS(answerPath, ios::in | ios::binary);//����� ��� ������
	if (answerS)
		if (resultS)
		{
			resultS >> resultD;
			answerS >> answerD;
			resultS.close();
			answerS.close();
			if (abs(resultD - answerD) < pogr)

				return 10;//���������
			else return 0;//�� ���������
		}
		else return -1;//�� ������ �����
	else return -10;//�� ������ ���������
	return 0;
}