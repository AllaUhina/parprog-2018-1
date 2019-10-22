#include <functional>
#include <random>
#include <omp.h> 


namespace
{
	int partition(long double* arr, unsigned long long l, unsigned long long r)
	{
		static std::random_device gen;
		std::uniform_int_distribution<unsigned long long> dist(l, r);

		long double sup = arr[dist(gen)];
		unsigned long long i = l;
		unsigned long long k = r;

		for (;;)
		{
			while (arr[i] < sup)
				i++;
			while (arr[k] > sup)
				k--;

			if (i >= k)
				return k;

			std::swap(arr[i++], arr[k--]);
		}
	}

	void qsort(long double* arr, unsigned long long l, unsigned long long r)
	{
		if (l < r)
		{
			int n = partition(arr, l, r);
			qsort(arr, l, n);
			qsort(arr, n + 1, r);
		}
	}
}

void MyQSort(long double * arr, unsigned long long size)
{
	qsort(arr, 0, size - 1);
}

