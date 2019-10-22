#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2) { return 4; }
	string path_to_result=argv[1];
	string path_to_answer=argv[2];
	double resultX, resultY, resultZ, answerX, answerY, answerZ;

	ifstream res(path_to_result, ios::in | ios::binary);
	ifstream answ(path_to_result, ios::in | ios::binary);
	if (res&&answ)
	{
		res >> resultX;
		res >> resultY;
		res >> resultZ;
		answ >> answerX;
		answ >> answerY;
		answ >> answerZ;
		res.close();
		answ.close();
		if (abs(resultZ - answerZ) < 0.001)	return 1;
		else return 0;
	}
	else
	{
		if (!res) return 2;
		if (!answ) return 3;
	}
	return 0;
}