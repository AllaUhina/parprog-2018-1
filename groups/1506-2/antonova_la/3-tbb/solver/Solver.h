#ifndef _SOLVER_H
#define _SOLVER_H
#include "Postfix.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <omp.h>
#include <fstream>

const int MAX_ITER = 1000;
const double EPS = 0.0001;
const int PARAM_R = 2;

using namespace std;


struct Point // координаты точки в двумерном пространстве и значение функции в ней
{
	double x;
	double y;
	double z;
	Point()
	{
		x = y = z = 1;
	}
	Point(const Point& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
	}
	Point(double _x, double _y, double _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	Point operator =(Point p)
	{
		this->x = p.x; this->y = p.y; this->z = p.z;
		return *this;
	}
};

	vector<Point> InsertSort(Point a, vector<Point> b, bool is_x_dim);//¬ставка новой точки в вектор и его сортировка

	double CalculateMBigMax(vector<Point> p, size_t k, bool is_x_dim);// Ќаходит максимальное значение ћ среди всех последовательных пар в векторе точек по х или по y

	double CalculateMSmall(double M);//Ќаходит m дл€ уже вычисленного M в соотв. с алгоритмом

	vector<double> CalculateRs(double m, vector<Point> p, size_t k, bool is_x_dim);//¬ычисл€ет вектор значений R(i) - веро€тность нахождени€ минимума на интервале

	unsigned FindIntNumber(vector< double> Ri);//Ќаходит номер промежутка, соответствующего наибольшему значению веро€тности, нумераци€ с 1

	vector<Point> InsertYNext(TPostfix func, vector<Point> p, int t, double m, double _x);//¬ычисл€ет следующее значение координаты при х - фикс. и вставл€ет новую точку в вектор c учетом пересортировки

	double CalculateYMin(TPostfix func, double a, double b, double _x);//¬ычисл€ет координату y, соотв. минмальному значению функции при фиксированном х

	vector<Point> InsertXNext(TPostfix func, vector<Point> p, int t, double m, double a, double b);//¬ычисл€ет следующее значение координаты с вычислением оптимального y и вставл€ет новую точку в вектор c учетом пересортировки

	Point GlobalMinCalculation(TPostfix func, double a, double b);

	double FindMin(vector<double> mins);

#endif // !_SOLVER_H_
