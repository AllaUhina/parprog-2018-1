#include "Solver.h"
#include "Postfix.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;



int main(int argc, char** argv)
{
	string path_to_test = argv[1];
	ifstream test_stream(path_to_test, ios::in | ios::binary);
	if (!test_stream) {
		return 2;
	}
	string function; double left_border, right_border;
	test_stream >> function;
	test_stream >> left_border;
	test_stream >> right_border;
	test_stream.close();
	Point result;
	TPostfix p; p.PutInfix(function); p.ToPostfix();
	result = GlobalMinCalculation(p, left_border, right_border);
	//Выводим результаты
	char path_to_result[] = "results/result_00.rslt";
	int path_test_length = sizeof(path_to_test) / sizeof(char);
	int path_res_length = sizeof(path_to_result) / sizeof(char);

	int testInd;
	for (int ind = 0; ind < path_test_length; ++ind)
	{
		if (path_to_test[ind] == '_')
		{
			testInd = ind + 1;
			break;
		}
	}

	int resInd;
	for (int ind = 0; ind < path_res_length; ++ind)
	{
		if (path_to_result[ind] == '_')
		{
			resInd = ind + 1;
			break;
		}
	}

	path_to_result[resInd] = path_to_test[testInd];
	path_to_result[resInd + 1] = path_to_test[testInd + 1];

	std::ofstream result_stream(path_to_result, ios::out | ios::binary);
	if (!result_stream) {
		return 3;
	}
	result_stream << result.x << endl;
	result_stream << result.y << endl;
	result_stream << result.z << endl;
	result_stream.close();
	return 0;

}