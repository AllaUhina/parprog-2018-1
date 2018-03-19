// viewer.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	FILE *stream;
	FILE *stream2;

	const char* FName = "..\\typer\\matr.bin";
	const char* FName1 = "matr.txt";
	const char* FName2 = "..\\solver\\matr.out";

	fopen_s(&stream, FName, "rb");
	fopen_s(&stream2, FName2, "rb");

	int N;
	double *A, *B, *C;

	fread(&N, sizeof(N), 1, stream);

	A = new double[N * N];
	B = new double[N * N];
	C = new double[N * N];

	fread(A, sizeof(*A), N * N, stream);
	fread(B, sizeof(*B), N * N, stream);
	fread(C, sizeof(*C), N * N, stream2);

	ofstream out;
	out.open(FName1);
	out << N << endl;

	out << endl;
	out << "Matrix A:" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			out << A[i*N + j] << "  ";
		out << endl;
	}

	out << endl;
	out << "Matrix B:" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			out << B[i*N + j] << "  ";
		out << endl;
	}

	out << endl;
	out << "Matrix C:" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			out << C[i*N + j] << "  ";
		out << endl;
	}
	out.close();

	fclose(stream);
	fclose(stream2);
}

