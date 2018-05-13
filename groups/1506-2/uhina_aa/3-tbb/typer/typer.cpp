// typer.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
using namespace std;

FILE *stream;

FILE *stream1;

int main()
{
	const char* FName = "matr.txt";
	int N;
	double *A, *B;

	//read from matr.txt to N, matrix A and B
	ifstream fin(FName);
	fin >> N;
	A = new double[N * N];
	B = new double[N * N];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fin >> A[i*N+j];
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			fin >> B[i*N + j];
		}
	}
	fin.close();

	freopen_s(&stream,"matr.bin", "wb", stdout); 
	 
	fwrite(&N, sizeof (N), 1, stdout); 
	double * cur = new double[N]; 

	for(int i = 0; i < N; i++) 
	{ 
		for(int j = 0; j < N; j++) 
			cur[j] = A[i*N + j];
		fwrite(cur, sizeof (*cur), N, stdout); 
	} 

	for (int i = 0; i < N; i++) 
	{ 
		for (int j = 0; j < N; j++) 
			cur[j] = B[i*N + j];
		fwrite(cur, sizeof (*cur), N, stdout); 
	}

	/*for (int j = 0; j < N*N; j++)
	{
		cout << A[j];
	}
	for (int j = 0; j < N*N; j++)
	{
		cout << B[j];
	}*/
    return 0;
}

