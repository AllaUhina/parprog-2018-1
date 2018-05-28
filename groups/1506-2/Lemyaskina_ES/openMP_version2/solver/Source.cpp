#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <./postfix.h>
#include <process.h>
#include <errno.h>
#include <omp.h>
#include <time.h>


#define NMax 1000000
#define numOfTest 10
#define ompNum 1

using namespace std;


double F(string funct, double x0)
{
	TPostfix integ;
		integ=funct;
	integ.GetInfix();
	integ.GetPostfix();
	integ.Calculate(x0);
	return integ.Calculate(x0);
}

double Integral(string funct,double left,double right,double num)
{
		double sum = 0;
		double len = abs((right - left) / num); //длина кусочка
		double tleft = left, tright = tleft + len; //границы кусочка
		for (int k = 0; k < num; k++)
		{
			sum += (F(funct, tright) + F(funct, tleft))*(tright - tleft) / 2;
			tleft += len;
			tright += len;
		}
	return sum;
}

int main(int argc,char* argv[])
{


	double right, left;
	string funct;
	double pogr = 0.0000001;
	double numOfIter = 10000;
	string path="../test/task/5.in";
	if (argc > 1)
		path = argv[1];

	ifstream functionS(path, ios::in | ios::binary);//поток для результата
	if (functionS)
	{	
	functionS >> funct;
	functionS >> left;
	functionS >> right;
	}
		else return -10;//не открыта задача
	int num = numOfIter;
	int k = 0;
	double res = 0;
		double time;
		omp_set_num_threads(ompNum);
		int prnum = num / ompNum;//число обрабатываемых итераций
		double tlen = (right - left) / ompNum;//размер области
		time = omp_get_wtime();
#pragma omp parallel for reduction(+:res)
		for (int i = 0; i < ompNum; i++)
		{
			double tleft = i*tlen + left;
			double tright = tleft + tlen;
			res = Integral(funct, tleft, tright, prnum); //вычисление с указанным количеством итераций
		}
		time = omp_get_wtime() - time;
	string tmp;
	for (int i = 1; i <= numOfTest; i++) //кусок, в котором ищется номер задачи
	{
		string d = "../test/task/" + to_string(i) + ".in";
		if (path == d)
		{
			tmp = to_string(i);
			if (i<10)
			tmp.resize(1);
			else tmp.resize(2);
		break;
		}
	}

	string pathRes = "../test/result/" + tmp+ ".result" ;
	string pathAns = "../test/answer/" + tmp + ".ans";
	ofstream streamA(pathRes, ios::out | ios::binary);
	if (streamA) {
		streamA << res << endl;
		streamA << ompNum << endl; 
		streamA << time << endl; //сколько потребовалось времени
		streamA.close();
	}
	else return -1;

	system("pause");
	return 0;
}
