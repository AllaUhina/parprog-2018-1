// test1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "tbb/tick_count.h"
using namespace tbb;

FILE *f;

//Functor
class MatrMatrMultPP
{
	const double *A, *B;
	double *C;
	int const BlockCount, BlockSize;
	int N;
public:
	MatrMatrMultPP(double *tA, double *tB, double *tC, int tBlockCount, int tBlockSize, int tN) : A(tA), B(tB), C(tC), BlockCount(tBlockCount), BlockSize(tBlockSize), N(tN) {}
	
	void operator() (const blocked_range<int>& r) const
	{
		int begin = r.begin(), end = r.end();

		for (int i = begin; i != end; i++)
		{
			int Row = (int)(i / BlockCount);
			int Column = i%BlockCount;
			for (int t = 0; t < BlockCount; t++) //iterations
			{
				for (int j = Row*BlockSize; j < (Row + 1)*BlockSize; j++) //Rows
				{
					for (int k = Column*BlockSize; k < (Column + 1)*BlockSize; k++) //Columns
					{
						for (int p = t*BlockSize; p < (t + 1)*BlockSize; p++)
						{
							C[j*N + k] += A[j*N + p] * B[p*N + k];
						}
					}
				}
			}
		}
	}
};

int main()
{
	int N;
	double *A, *B, *C;

	//stdin to matr.in
	freopen_s(&f, "..\\..\\tests\\5", "rb", stdin);
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

	if (N*N < ProcNum)
	{
		ProcNum = N*N;
	}
	double Time;
	tick_count TimeStart, TimeFinal;

	int BlockCount = int(sqrt((double)ProcNum)); //Number of blocks
	int BlockSize = N / BlockCount; //Size of blocks

	//Check number of processes
	if (ProcNum != BlockCount*BlockCount)
	{
		fprintf(f, "Invalid number of process.The root of %d %s", ProcNum, "is not an integer");
		exit(1);
	}

	task_scheduler_init init(ProcNum);
	int grainsize = 1; //portion for the process

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

		TimeStart = tick_count::now();
		parallel_for(blocked_range<int>(0, ProcNum, grainsize), MatrMatrMultPP(newA, newB, newC, BlockCount, BlockSize, newN));
		TimeFinal = tick_count::now();

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				C[i*N + j] = newC[i*newN + j];
			}
		}
		delete[]newA;
		delete[]newB;
		delete[]newC;
	}
	else
	{
		TimeStart = tick_count::now();
		parallel_for(blocked_range<int>(0, ProcNum, grainsize), MatrMatrMultPP(A, B, C, BlockCount, BlockSize, N));
		TimeFinal = tick_count::now();
	}
	Time = (TimeFinal - TimeStart).seconds();

	//Write a result to matr.out
	fwrite(&Time, sizeof(Time), 1, stdout);
	fwrite(C, sizeof(*C), N * N, stdout);

	//Freeing memory
	delete[]A;
	delete[]B;
	delete[]C; 
    return 0;
}

