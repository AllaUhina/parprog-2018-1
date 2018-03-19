// generator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <cstdio> 
#include <random> 
#include <ctime> 
#include <chrono>
#include <fstream>
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

int n_tests[] = { 1, 2, 2, 3, 4, 5, 10, 50, 70, 80, 100,500,1000};
int main(int argc, char * argv[]) 
{ 
	FILE* stream; 
	freopen_s(&stream,"matr.in", "wb", stdout); 

	// generator random
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count()); 
	// uniform random
	uniform_real_distribution <double> distribution(-1e4, 1e4); 

	// Razmernost matrix
	int N = 1000; 

	if (argc > 1)
	{
		N = n_tests[atoi(argv[1])];
	}

	// Razmernost to matr.in
	fwrite(&N, sizeof (N), 1, stdout); 
	
	double * cur = new double[N]; 
	
	// generate matrix A
	for(int i = 0; i < N; i++) 
	{ 
		for(int j = 0; j < N; j++) 
			cur[j] = distribution(generator); 
		fwrite(cur, sizeof (*cur),N, stdout); 
	} 

	// generate matrix B 
	for (int i = 0; i < N; i++) 
	{ 
		for (int j = 0; j < N; j++) 
			cur[j] = distribution(generator); 
		fwrite(cur, sizeof (*cur), N, stdout); 
	} return 0; 
}

