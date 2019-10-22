#ifndef _SOLVER_H
#define _SOLVER_H
#include "Postfix.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <omp.h>
#include <fstream>

const int MAX_ITER = 10000;
const double EPS = 0.0001;
const int PARAM_R = 2;

using namespace std;


struct Point //���������� ����� � ��������� ������������ � �������� ������� � ���
{
	double x;
	double y;
	double z;
	Point()
	{
		x = y = z = 0;
	}
	Point(double _x, double _y, double _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
};

vector<Point> InsertSort(Point a, vector<Point> b, bool is_x_dim);//������� ����� ����� � ������ � ��� ����������

double CalculateMBigMax(vector<Point> p, size_t k, bool is_x_dim);// ������� ������������ �������� � ����� ���� ���������������� ��� � ������� ����� �� � ��� �� y

double CalculateMSmall(double M);//������� m ��� ��� ������������ M � �����. � ����������

vector<double> CalculateRs(double m, vector<Point> p, size_t k, bool is_x_dim);//��������� ������ �������� R(i) - ����������� ���������� �������� �� ���������

unsigned FindIntNumber(vector< double> Ri);//������� ����� ����������, ���������������� ����������� �������� �����������, ��������� � 1

vector<Point> InsertYNext(TPostfix func, vector<Point> p, int t, double m, double _x);//��������� ��������� �������� ���������� ��� � - ����. � ��������� ����� ����� � ������ c ������ ��������������

double CalculateYMin(TPostfix func, double a, double b, double _x);//��������� ���������� y, �����. ����������� �������� ������� ��� ������������� �

vector<Point> InsertXNext(TPostfix func, vector<Point> p, int t, double m, double a, double b);//��������� ��������� �������� ���������� � ����������� ������������ y � ��������� ����� ����� � ������ c ������ ��������������

Point GlobalMinCalculation(TPostfix func, double a, double b);

double FindMin(vector<double> mins);

#endif // !_SOLVER_H_
