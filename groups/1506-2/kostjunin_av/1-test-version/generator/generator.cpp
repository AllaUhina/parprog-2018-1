// generator.cpp : Defines the entry point for the console application.
//

#include <cstdio> 
#include <random> 
#include <chrono> 
#include <iostream>
#include <functional>

unsigned test[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 100, 200, 300, 400, 500,
600, 700, 800, 900, 1000, 2000, 5000, 10000, 50000, 100000, 200000, 500000, 1000000 };

int main(int argc, char * argv[])
{
	//argv[1] - имя/номер теста
	//argv[2] - необязательный параметр - для особых случаев
	//1 - все числа одинаковые
	//2 - отсортированный массив
	//3 - массив отсортирован в обратном порядке
	if (argc == 1)
	{
		std::cerr << "too little args";
		return argc;
	}

	//перенаправляем поток stdout в файл
	//имя файла задается при запуске программы
	freopen(argv[1], "wb", stdout);

	//размер массива 
	unsigned long long N = 1000;
	// если передали номер теста в аргументах командной строки, то берём размер из заготовленного заранее массива test
	if (argc > 1)
	{
		//если в аргументах был передан номер теста, берем соответствующий размер из массива
		auto n = atoi(argv[1]);
		if (n > 0 && n < sizeof(test)/sizeof(*test))
			N = test[n];
	}
	// записываем в бинарном виде размер массива 
	fwrite(&N, sizeof(N), 1, stdout);


	std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

	// создаём равномерное распределение случайной величины типа long double в диапазоне [LLONG_MIN, LLONG_MAX] 
	long double left = LLONG_MIN, right = LLONG_MAX;
	if (argc > 2 && atoi(argv[2]) == 1)
		left = right = N;//все элементы одинаковые
	std::uniform_real_distribution<long double> distribution(left, right);


	long double * arr = new long double[N];

	//заполняем массив случайными числами
	std::generate(arr, arr + N, std::bind(distribution, std::ref(generator)));


	if (argc > 2)
	{
		switch (atoi(argv[2]))
		{
		case 1: break;
		case 2: //отсортируем массив
			std::sort(arr, arr + N);
			break;
		case 3: //отсортируем массив в обратном порядке
			std::sort(arr, arr + N);
			std::reverse(arr, arr + N);
			break;
		}
	}

	fwrite(arr, sizeof(*arr), N, stdout);//вывод массива в файл

	fclose(stdout);

	//std::cerr << "arr[" << N << "] = ";
	//if (N <= 10)
	//{
	//	std::for_each(arr, arr + N, [](auto var) { std::cerr << var; });
	//	std::cerr << std::endl;
	//}
	return 0;
