// generator.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <cstdio> 
#include <random> 
#include <ctime> 
#include <chrono>
#include <fstream>      //Для работы с файлом
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

int n_tests[] = { 1, 2, 2, 3, 4, 5, 10, 50, 70, 80, 100,500,1000};
int main(int argc, char * argv[]) 
{ 
	FILE* stream;
	// перенаправляем поток stdout в файл matr.in 
	freopen_s(&stream,"matr.in", "wb", stdout); 

	// создаём генератор случайных чисел с seed равным количеству времени с начала эпохи 
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count()); 

	// создаём равномерное распределение случайной величины типа double в диапазоне 
	// [-10000, 10000] 
	uniform_real_distribution <double> distribution(-1e4, 1e4); 

	// задаём размер матриц 
	int N = 1000; 

	// если передали номер теста в аргументах командной строки, то берём размер из n_tests 
	if (argc > 1)
	{
		N = n_tests[atoi(argv[1])];
	}

	// записываем в matr.in бинарном виде размерность матриц 
	fwrite(&N, sizeof (N), 1, stdout); 
	
	// создаём временный массив для строки матрицы 
	double * cur = new double[N]; 
	
	// генерируем первую матрицу 
	for(int i = 0; i < N; i++) 
	{ 
		// заполняем случайными числами из равномерного распределения очередную строку матрицы 
		for(int j = 0; j < N; j++) 
			cur[j] = distribution(generator); 
		// записываем строку в бинарном виде в файл 
		fwrite(cur, sizeof (*cur),N, stdout); 
	} 
	// аналогично генерируем вторую матрицу 
	for (int i = 0; i < N; i++) 
	{ 
		for (int j = 0; j < N; j++) 
			cur[j] = distribution(generator); 
		fwrite(cur, sizeof (*cur), N, stdout); 
	} return 0; 
}

