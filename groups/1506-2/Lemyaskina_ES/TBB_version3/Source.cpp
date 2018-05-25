#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <process.h>
#include <errno.h>
#include <omp.h>
#include <time.h>
#include "postfix.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "tbb/tbb.h"
#include "tbb/parallel_reduce.h"
#include "tbb/tick_count.h"
#include "tbb/task_group.h"




using namespace std;
using namespace tbb;

double F(string funct, double x0)
{
	TPostfix integ;
	integ = funct;
	integ.GetInfix();
	integ.GetPostfix();
	integ.Calculate(x0);
	return integ.Calculate(x0);
}

//double Integral(string funct, double left, double right, int num)
//{
//	double sum = 0;
//	double len = abs((right - left) / num); //äëèíà êóñî÷êà
//	double tleft = left, tright = tleft + len; //ãðàíèöû êóñî÷êà
//	for (int k = 0; k < num; k++)
//	{
//		sum += (F(funct, tright) + F(funct, tleft))*(tright - tleft) / 2;
//		tleft += len;
//		tright += len;
//	}
//	return sum;
//}




int main(int argc, char* argv[])
{
	int numOfThreads = 2;
	task_scheduler_init init(numOfThreads);
	int numOfTest = 10;
	double right, left;
	string funct;
	double len; 
	double numOfIter = 100000;
	string path = "../test/task/9.in";
	if (argc > 1)
		path = argv[1];

	ifstream functionS(path, ios::in | ios::binary);//ïîòîê äëÿ ðåçóëüòàòà
	if (functionS)
	{
		functionS >> funct;
		functionS >> left;
		functionS >> right;
	}
	else return -10;//íå îòêðûòà çàäà÷à
	tick_count time0,time;
	time0 = tick_count::now();
	len = (right - left) / numOfIter;
	auto total = parallel_reduce(blocked_range<double>(left, right), 0.0, 
		[&](blocked_range<double> r, double sum)
	{
		sum = 0;
		for (double i = r.begin(); i < r.end(); i=i+len)
		{
			sum += (F(funct, i+len) + F(funct, i))*(len) / 2;
		} 
		return sum;
	}, plus<double>());
	time = tick_count::now();
	double dtime = (time - time0).seconds();
	string tmp;
	for (int i = 1; i <= numOfTest; i++)
	{
		string d = "../test/task/" + to_string(i) + ".in";
		if (path == d)
		{
			tmp = to_string(i);
			if (i < 10)
				tmp.resize(1);
			else tmp.resize(2);
			break;
		}
	}
	string pathRes = "../test/result/" + tmp + "_TBB.result";
	string pathAns = "../test/answer/" + tmp + ".ans"; 
	ofstream streamA(pathRes, ios::out | ios::binary);
	if (streamA) {
		streamA << total << endl;
		streamA << numOfThreads << endl;
		streamA << dtime << endl;
		streamA.close();
	}
	else return -1;

	system("pause");
	return 0;
}