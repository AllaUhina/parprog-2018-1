#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
#include <fstream>
#include <./postfix.h>
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

	double len = ((right - left) / num);
	double tleft = left, tright = tleft + len;
	double sum = 0;

	
	for (int i=0;i<num;i++)
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
	double numOfIter = 1000;
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
		else return -1;//не открыта задача
		if (right < left)
	throw invalid_argument("Right is lower than a left. \n");
	int num = numOfIter;
	double res=0;
	int k = 0;
	double resnext = 10000;
	res = Integral(funct, left, right, num); //вычисление с указанным количеством итераций
	path.resize(path.size() - 3); //записать ответ с номером задачи
	string tmp = path[path.(size)-1];
	string pathRes = "../test/result" +tmp+ ".result";

	ofstream streamA(pathRes, ios::out | ios::binary);
	if (streamA) {
		streamA << res << endl;
		streamA.close();
	}
	else return -1;
	return 0;
}