// solver.cpp : Defines the entry point for the console application.
//




#include <cstdio> 
#include <omp.h> 
#include <iostream>
#include <string>
#include <exception>
#include <algorithm>

//#include "MyQSort.h"
//#include "Standard.h"

void MyQSort(long double * arr, unsigned long long size);
void StandardSort(long double* arr, unsigned long long size);

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		std::cerr << "too little args";
		return argc;
	}

	//argv[1] - имя теста
	//argv[2] - количество потоков(необязательный аргумент)

	std::string test_name = argv[1];//имя теста

	int num_threads = 1;
	if (argc > 2)
		num_threads = atoi(argv[2]);


	auto filein = freopen(argv[1], "rb", stdin);					//входные данные
	if (!filein)
	{
		std::cerr << "input file not found" << std::endl;
		return 1;
	}


	auto name = test_name + ".ans";
	FILE * out = fopen(name.c_str(), "wb");		//выходные данные("ответ участника") - результат работы написанной функции сортировки
	auto name1 = test_name + ".txt";
	FILE * answer = fopen(name1.c_str(), "wb");	//правильный ответ("ответ жюри") - результат работы эталонной функции сортировки

	unsigned long long N = 0;//размер массива
	fread(&N, sizeof(N), 1, stdin);//считываем размер массива
	long double * arr = new long double[N];
	fread(arr, sizeof(*arr), N, stdin);//считываем массив
	fclose(stdin);
	long double * arr1 = new long double[N];//массив для эталонной функции
	memcpy(arr1, arr, sizeof(*arr) * N);


	omp_set_num_threads(num_threads);//количество потоков
									 //решение задачи сортировки - результат записывается в "выходные данные"
	try
	{
		double time = omp_get_wtime();
		MyQSort(arr, N);
		time = omp_get_wtime() - time;

		fwrite(&time, sizeof(time), 1, out);//записываем время работы сортировки
		fwrite(arr, sizeof(*arr), N, out);//записываем результат работы сортировки

		std::cerr << "time = " << time << " is sorted? - " << std::boolalpha << std::is_sorted(arr, arr + sizeof(arr) / sizeof(*arr)) << std::endl;
	}
	catch (std::exception e)
	{
		fwrite(e.what(), 1, strlen(e.what()), out);
	}
	fclose(out);

	omp_set_num_threads(1);
	//решение задачи сортировки - результат записывается в "правильный ответ.txt"
	try
	{
		double time = omp_get_wtime();
		StandardSort(arr1, N);
		time = omp_get_wtime() - time;

		fwrite(&time, sizeof(time), 1, answer);//записываем время работы сортировки
		fwrite(arr1, sizeof(*arr1), N, answer);//записываем результат работы сортировки

		std::cerr << "time = " << time << " is sorted? - " << std::boolalpha << std::is_sorted(arr1, arr1 + sizeof(arr1) / sizeof(*arr1)) << std::endl;
	}
	catch (std::exception e)
	{
		fwrite(e.what(), 1, strlen(e.what()), answer);
	}
	fclose(answer);


	return 0;
}
