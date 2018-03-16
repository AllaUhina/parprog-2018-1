// viewer.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
using namespace std;

FILE *stream;

FILE *stream1;

int main()
{
	const char* FName = "C:\\uhina_aa\\1-test-version\\typer\\matr.bin";       //Путь к файлу
	const char* FName1 = "matr.txt";
	const char* FName2 = "C:\\uhina_aa\\1-test-version\\solver\\matr.out";
	/*freopen_s(&stream,, "r", stdin);
	freopen_s(&stream1,"matr.txt", "w", stdout);*/
	int N;
	double *A, *B, *C;

	

	/**/

	ifstream in(FName, ios::binary);
	in.read((char*)&N, sizeof(N));
	A = new double[N * N];
	B = new double[N * N];
	C = new double[N * N];
	for (int i = 0; i < N*N; i++)
	{
		in.read((char*)&A[i], sizeof(A[i]));
	}
	
	for (int i = 0; i < N*N; i++)
	{
		in.read((char*)&B[i], sizeof(B[i]));
	}

	in.close();

	ifstream in2(FName2, ios::binary);
	for (int i = 0; i < N*N; i++)
	{
		in2.read((char*)&C[i], sizeof(C[i]));
	}
	in2.close();

	ofstream out;
	out.open(FName1);
	out<<N<<endl;

	out << endl;
	out << "Matrix A:" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			out << A[i*N + j]<<"  ";
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
}

