// solver.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <omp.h>
using namespace std;

FILE *f;

void ParallelMatrMatrMult(double * A, double * B, double * C, int N, int BlockCount, int BlockSize);

int main(int argc, char * argv[]) {

	int N;
	double *A, *B, *C;

	//stdin to matr.in
	freopen_s(&f, "..\\..\\tests\\19", "rb", stdin);
	//stdout to matr.out
	freopen_s(&f, "matr.out", "wb", stdout);
	//Size of matrix
	fread(&N, sizeof(N), 1, stdin);

	A = new double[N * N];
	B = new double[N * N];
	C = new double[N * N];

	//read matrix A
	fread(A, sizeof(*A), N * N, stdin);
	//read matrix B
	fread(B, sizeof(*B), N * N, stdin);

	for (int i = 0; i < N*N; i++)
	{
		C[i] = 0.0;
	}

	int ProcNum = 4; //Number of processes

	//If enter the number of processes
	if (argc > 1)
	{
		ProcNum = atoi(argv[1]);
	}

	if (N*N < ProcNum)
	{
		ProcNum = N*N;
	}

	double TimeStart, TimeFinal, Time; //Time
	int BlockCount = int(sqrt((double)ProcNum)); //Number of blocks
	int BlockSize = N / BlockCount; //Size of blocks

	//Check number of processes
	if (ProcNum != BlockCount*BlockCount)
	{
		fprintf(f, "Invalid number of process.The root of %d %s", ProcNum, "is not an integer");
		exit(1);
	}

	omp_set_num_threads(ProcNum);

	//If a size of blocks is not an integer
	if ((N*N > ProcNum) && (N%BlockCount != 0))
	{
		int newN = (BlockSize + 1)*BlockCount;
		double*newA = new double[newN * newN];
		double*newB = new double[newN * newN];
		double*newC = new double[newN * newN];
		BlockSize = newN / BlockCount;
		
		for (int i = 0; i < newN*newN; i++)
		{
			newA[i] = 0.0;
			newB[i] = 0.0;
			newC[i] = 0.0;
		}
		
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				newA[i*newN + j] = A[i*N + j];
				newB[i*newN + j] = B[i*N + j];
			}
		}

		TimeStart = omp_get_wtime();
		ParallelMatrMatrMult(newA, newB, newC, newN, BlockCount, BlockSize);
		TimeFinal = omp_get_wtime();
		Time = TimeFinal - TimeStart;
		//Write a result to matrix C
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				C[i*N + j] = newC[i*newN + j];
			}
		}
	}
	else
	{
		TimeStart = omp_get_wtime();
		ParallelMatrMatrMult(A, B, C, N, BlockCount, BlockSize);
		TimeFinal = omp_get_wtime();
		Time = TimeFinal - TimeStart;
	}

	//Write a result to matr.out
	fwrite(&Time, sizeof(Time), 1, stdout);
	fwrite(C, sizeof(*C), N * N, stdout);
	return 0;
}

void ParallelMatrMatrMult(double * A, double * B, double * C, int N, int BlockCount, int BlockSize)
{
#pragma omp parallel
	{
		int ProcRank = omp_get_thread_num();
		int Row = (int)(ProcRank / BlockCount);
		int Column = ProcRank%BlockCount;
		for (int i = 0; i < BlockCount; i++) //iterations
		{
			for (int j = Row*BlockSize; j < (Row + 1)*BlockSize; j++) //Rows
			{
				for (int k = Column*BlockSize; k < (Column + 1)*BlockSize; k++) //Columns
				{
					for (int p = i*BlockSize; p < (i + 1)*BlockSize; p++)
					{
						C[j*N + k] += A[j*N + p] * B[p*N + k];
					}
				}
			}
		}
	}
}