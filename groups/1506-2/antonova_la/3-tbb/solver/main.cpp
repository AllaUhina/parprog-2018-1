#include "Solver.h"
#include "Postfix.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "tbb/tbb.h"
#include "tbb/parallel_reduce.h"


using namespace tbb;
using namespace std;

class my_range
 {
	private:
		double my_begin;
		double my_end;
		double my_grainsize;
	public:
		my_range(const my_range& m)
		{
			my_begin = m.begin();
			my_end = m.end();
			my_grainsize = m.grainsize();
		}
		my_range(double begin, double end, double grainsize = 1)
		{
			my_begin = begin;
			my_end = end;
			my_grainsize = grainsize;
		}
		my_range(my_range& m, split)
		{
			double new_begin, new_end;
			new_begin = m.begin() + m.grainsize();
			new_end = m.end();
			my_begin = new_begin;
			my_end = new_end;
			my_grainsize = m.grainsize();
			m.my_end = new_begin;
		}
		~my_range() {}
		double begin() const { return my_begin; }
		double end() const { return  my_end; }
		double grainsize() const { return my_grainsize; }
		bool is_divisible()
		{
			return my_end > my_begin + 0.00002;
		}
		bool empty() const
		{
			return my_end == my_begin;
		}
				
};

class myTbb
{
private:
	int ProcNum;
	TPostfix func;
	Point res;
	double a, b;

public:
	explicit myTbb(TPostfix f, int procN,double _a, double _b)
	{
		func = f;
		ProcNum = procN;
		a = _a;
		b = _b;
		
	}

	myTbb(myTbb& m, split)
	{
		func = m.func;
		ProcNum = m.ProcNum;
		a = m.a;
		b = m.b;
		res = m.res;
	}

	void operator()(const  blocked_range<double>& r)
	{
		int left_border = r.begin();
		int right_border = r.end();
		res = GlobalMinCalculation(func, left_border, right_border);
	}

	void join(const myTbb& rhs)
	{
		if (rhs.res.z < res.z)
			res = rhs.res;
	}
	
	Point Result()
	{
		return res;
	}
};



int main(int argc, char** argv)
{
	string path_to_test = argv[1];
	ifstream test_stream(path_to_test, ios::in | ios::binary);
	if (!test_stream)
	{
		return 2;
	}
	int ProcNum = argv[2];
	task_scheduler_init init(ProcNum);
	string function; double left_border, right_border;
	test_stream >> function;
	test_stream >> left_border;
	test_stream >> right_border;
	test_stream.close();
	/*Point result;*/
	TPostfix p; p.PutInfix(function); p.ToPostfix();
	tick_count t0 = tick_count::now(); 
	myTbb result(p, ProcNum, left_border, right_border);
	parallel_reduce(blocked_range<double>(left_border, right_border, (right_border - left_border) / ProcNum), result);
	tick_count t1 = tick_count::now();

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
	result_stream << result.Result().x << endl;
	result_stream << result.Result().y << endl;
	result_stream << result.Result().z << endl;
	result_stream << (t1 - t0).seconds() <<"s"<< endl;
	result_stream.close();
	return 0;

}