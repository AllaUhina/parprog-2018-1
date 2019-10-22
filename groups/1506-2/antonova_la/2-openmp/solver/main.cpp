#include "Solver.h"
#include "Postfix.h"
#include <omp.h>
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
	int ProcRank, ProcNum=stoi(argv[2]);
	double left_b, right_b;
	string function; double left_border, right_border;
	omp_set_num_threads(ProcNum);
	test_stream >> function;
	test_stream >> left_border;
	test_stream >> right_border;
	test_stream.close();
	Point result,global_res;
	TPostfix p; p.PutInfix(function); p.ToPostfix();
	auto start_time = omp_get_wtime();
	#pragma omp parallel private(p,left_b, right_b,ProcRank,result) shared(left_border,right_border,ProcNum) 
	{
		p.PutInfix(function); p.ToPostfix();
		ProcRank = omp_get_thread_num();
		left_b = left_border + (right_border - left_border) / ProcNum*ProcRank;
		right_b = left_border + (right_border - left_border) / ProcNum*(ProcRank + 1);
		result = GlobalMinCalculation(p, left_b, right_b);
#pragma omp barrier
#pragma omp single
		{
			global_res = result;
		}
#pragma omp critical 
		{
			if (result.z < global_res.z)
				global_res = result;
		}
	}
	auto finish_time = omp_get_wtime();
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
	result_stream << global_res .x << endl;
	result_stream << global_res.y << endl;
	result_stream << global_res.z << endl;
	result_stream << finish_time - start_time <<"s"<< endl;
	result_stream.close();
	return 0;

}