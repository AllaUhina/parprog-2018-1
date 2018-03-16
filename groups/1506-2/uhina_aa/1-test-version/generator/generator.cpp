// generator.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <cstdio> 
#include <random> 
#include <ctime> 
#include <chrono>
#include <fstream>      //��� ������ � ������
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

int n_tests[] = { 1, 2, 2, 3, 4, 5, 10, 50, 70, 80, 100,500,1000};
int main(int argc, char * argv[]) 
{ 
	FILE* stream;
	// �������������� ����� stdout � ���� matr.in 
	freopen_s(&stream,"matr.in", "wb", stdout); 

	// ������ ��������� ��������� ����� � seed ������ ���������� ������� � ������ ����� 
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count()); 

	// ������ ����������� ������������� ��������� �������� ���� double � ��������� 
	// [-10000, 10000] 
	uniform_real_distribution <double> distribution(-1e4, 1e4); 

	// ����� ������ ������ 
	int N = 1000; 

	// ���� �������� ����� ����� � ���������� ��������� ������, �� ���� ������ �� n_tests 
	if (argc > 1)
	{
		N = n_tests[atoi(argv[1])];
	}

	// ���������� � matr.in �������� ���� ����������� ������ 
	fwrite(&N, sizeof (N), 1, stdout); 
	
	// ������ ��������� ������ ��� ������ ������� 
	double * cur = new double[N]; 
	
	// ���������� ������ ������� 
	for(int i = 0; i < N; i++) 
	{ 
		// ��������� ���������� ������� �� ������������ ������������� ��������� ������ ������� 
		for(int j = 0; j < N; j++) 
			cur[j] = distribution(generator); 
		// ���������� ������ � �������� ���� � ���� 
		fwrite(cur, sizeof (*cur),N, stdout); 
	} 
	// ���������� ���������� ������ ������� 
	for (int i = 0; i < N; i++) 
	{ 
		for (int j = 0; j < N; j++) 
			cur[j] = distribution(generator); 
		fwrite(cur, sizeof (*cur), N, stdout); 
	} return 0; 
}

