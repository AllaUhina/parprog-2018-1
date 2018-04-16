// answer.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <omp.h>
using namespace std;

FILE *f;


int main(int argc, char * argv[]) {

	int N;
	double *A, *B, *C;

	freopen_s(&f, "..\\tests\\1", "rb", stdin);
	freopen_s(&f, "answer.txt", "wb", stdout);

	//Razmernost
	fread(&N, sizeof(N), 1, stdin);

	A = new double[N * N];
	B = new double[N * N];
	C = new double[N * N];

	//matrix A
	fread(A, sizeof(*A), N * N, stdin);
	//matrix B
	fread(B, sizeof(*B), N * N, stdin);

	double time = omp_get_wtime();
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			C[i * N + j] = 0.0;
			for (int k = 0; k < N; k++)
				C[i * N + j] += A[i * N + k] * B[k * N + j];
		}
	}
	time = omp_get_wtime() - time;

	//write a result to answer.txt
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(C, sizeof(*C), N * N, stdout);
	return 0;
}


