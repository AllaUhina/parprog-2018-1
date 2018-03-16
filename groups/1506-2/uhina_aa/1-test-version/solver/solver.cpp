// solver.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

FILE *f;

void MatrMatrMult(double * A, double * B, double * C, int N);

int main(int argc, char * argv[]) {

	int N;
	double *A, *B, *C;

	// �������������� ����� stdin � ���� matr.in
	freopen_s(&f,"C:\\uhina_aa\\1-test-version\\generator\\matr.in", "rb", stdin);
	// �������������� ����� stdout � ���� matr.out
	freopen_s(&f,"matr.out", "wb", stdout);
	// c�������� ����������� ������
	fread(&N, sizeof(N), 1, stdin);

	A = new double[N * N]; 
	B = new double[N * N]; 
	C = new double[N * N];

	// c�������� ������� �
	fread(A, sizeof(*A), N * N, stdin);
	// c�������� ������� �
	fread(B, sizeof(*B), N * N, stdin);

	MatrMatrMult(A, B, C, N); 
	
	//���������� ��������� � matr.out
	fwrite(C, sizeof(*C), N * N, stdout);
	return 0;
}

void MatrMatrMult(double * A, double * B, double * C, int N)
{
	int i, j, k;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			C[i * N + j] = 0.0;
			for (k = 0; k < N; k++)
				C[i * N + j] += A[i * N + k] * B[k * N + j];
		}
	}
}