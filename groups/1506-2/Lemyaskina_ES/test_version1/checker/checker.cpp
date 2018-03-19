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
	double resultD, answerD;//численные значения

	ifstream resultS(resultPath, ios::in | ios::binary);//поток для результата
	ifstream answerS(answerPath, ios::in | ios::binary);//поток для ответа
	if (answerS)
		if (resultS)
		{
			resultS >> resultD;
			answerS >> answerD;
			resultS.close();
			answerS.close();
			if (abs(resultD - answerD) < pogr)

				return 10;//совпадают
			else return 0;//не совпадают
		}
		else return -1;//не открыт ответ
	else return -10;//не открыт результат
	return 0;
}