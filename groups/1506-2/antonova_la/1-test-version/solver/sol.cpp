#include "Postfix.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <omp.h>
#include <fstream>

const int MAX_ITER = 1000;
const double EPS = 0.001;
const int PARAM_R = 2;

using namespace std;



struct Point //Координаты точки в двумерном пространстве и значение функции в ней
{
	double x;
	double y;
	double z;
	Point()
	{
		x = y = z = 0;
	}
	Point(double _x, double _y, double _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
};

vector<Point> InsertSort(Point a, vector<Point> b, bool is_x_dim)//Вставка новой точки в вектор и его сортировка
{
	b.push_back(a);
	size_t i = b.size() - 1;
	if (is_x_dim == true)
		while ((i > 0) && (b[i].x < b[i - 1].x))
		{
			swap(b[i], b[i - 1]);
			i--;
		}
	else
		while ((i > 0) && (b[i].y < b[i - 1].y))
		{
			swap(b[i], b[i - 1]);
			i--;
		}
	return b;
}

 double CalculateMBigMax(vector<Point> p, size_t k, bool is_x_dim)// Находит максимальное значение М среди всех последовательных пар в векторе точек по х или по y
{
	double M_MAX = 0;
	if (is_x_dim == true)
	{
		double M = 0;
		M_MAX = abs(p[1].z - p[0].z) / (p[1].x - p[0].x);
		for (size_t i = 1; i < k - 1; i++)
		{
			M = abs(p[i + 1].z - p[i].z) / (p[i + 1].x - p[i].x);
			if (M > M_MAX)
				M_MAX = M;
		}
	}
	else
	{
		double M;
		M_MAX = abs(p[1].z - p[0].z) / (p[1].y - p[0].y);
		for (size_t i = 1; i < k - 1; i++)
		{
			M = abs(p[i + 1].z - p[i].z) / (p[i + 1].y - p[i].y);
			if (M > M_MAX)
				M_MAX = M;
		}
	}
	return M_MAX;
}

 double CalculateMSmall( double M)//Находит m для уже вычисленного M в соотв. с алгоритмом
{
	if (M == 0)
		return 1;
	else
		return M * PARAM_R;
}

vector< double> CalculateRs( double m, vector<Point> p, size_t k, bool is_x_dim)//Вычисляет вектор значений R(i) - вероятность нахождения минимума на интервале
{
	vector< double> Ri;
	Ri.resize(k - 1);
	if (is_x_dim == true)
	{
		for (size_t i = 0; i < k - 1; i++)
		{
			Ri[i] = m*(p[i + 1].x - p[i].x) + ((p[i + 1].z - p[i].z)*(p[i + 1].z - p[i].z)) / (m*(p[i + 1].x - p[i].x)) - 2 * (p[i + 1].z + p[i].z);
		}
	}
	else
	{
		for (size_t i = 0; i < k - 1; i++)
		{
			Ri[i] = m*(p[i + 1].y - p[i].y) + ((p[i + 1].z - p[i].z)*(p[i + 1].z - p[i].z)) / (m*(p[i + 1].y - p[i].y)) - 2 * (p[i + 1].z + p[i].z);
		}
	}
	return Ri;
}

unsigned FindIntNumber(vector< double> Ri)//Находит номер промежутка, соответствующего наибольшему значению вероятности, нумерация с 1
{
	if (Ri.size() == 1)
		return 1;
	size_t t = 0;
	for (size_t i = 1; i < Ri.size(); i++)
	{
		if (Ri[i] > Ri[i - 1])
			t = i;
	}
	return t + 1;
}

vector<Point> InsertYNext(TPostfix func,vector<Point> p, int t,  double m,  double _x)//Вычисляет следующее значение координаты при х - фикс. и вставляет новую точку в вектор c учетом пересортировки
{
	Point new_point;
	new_point.x = _x;
	new_point.y = ((p[t - 1].y + p[t].y) / 2) - ((p[t].z - p[t - 1].z) / (2 * m));
	new_point.z = func.Calculate(_x, new_point.y);
	vector<Point> temp = InsertSort(new_point, p, false);
	return temp;
}

 double CalculateYMin(TPostfix func, double a,  double b,  double _x)//Вычисляет координату y, соотв. минмальному значению функции при фиксированном х
{
	vector<Point> points(2);
	vector<Point> temp(2);
	vector< double> Ri(1);
	size_t k = 2;
	float M = 0, m = 0, stop_flag = 1;
	size_t t = 0;

	//Задаем начальные точки и значения функции в них
	points[0].x = _x; points[0].y = a; points[0].z = func.Calculate(_x, a);
	points[1].x = _x; points[1].y = b; points[1].z = func.Calculate(_x, b);

	while ((k < MAX_ITER) && (stop_flag > EPS))//Пока не получим больше 1000 точек или удовлетворительную точность
	{
		//Вычисляем М для всех имеющихся на данном шаге промежутков
		M = CalculateMBigMax(points, k, false);
		//Для вычисленного М вычисляем m
		m = CalculateMSmall(M);
		//Для каждого промежутка вычисляем вероятность нахождения минимума
		Ri = CalculateRs(m, points, k, false);
		//Ищем номер промежутка с наибольшей вероятностью (первый в случае нескольких наибольших)
		t = FindIntNumber(Ri);
		//Вычисление условия остановки
		stop_flag = points[t].y - points[t - 1].y;
		//Служебное расширение временного вектора
		temp.resize(k);
		//Генерируем следующее значение координаты и добавляем точку с такой координатой и вычисленным
		//значением целевой функции в вектор точек с его последующей пересортировкой
		temp = InsertYNext(func,points, t, m, _x);
		points = temp;
		//Количество точек в векторе увеличивается на 1
		k++;

	}
	//Пересчитываем номер нужного нам промежутка для последней сработавшей итерации

	//Вычисляем М для всех имеющихся на данном шаге промежутков
	M = CalculateMBigMax(points, k, false);
	//Для вычисленного М вычисляем m
	m = CalculateMSmall(M);
	//Для каждого промежутка вычисляем вероятность нахождения минимума
	Ri = CalculateRs(m, points, k, false);
	//Ищем номер промежутка с наибольшей вероятностью (первый в случае нескольких наибольших)
	t = FindIntNumber(Ri);

	//возвращаем один из концов интервала(точку) с наибольшей вероятностью нахождения в нем минимума,
	//полученный на последнем шаге перед остановкой цикла
	return points[t].y;

}

vector<Point> InsertXNext(TPostfix func, vector<Point> p, int t, float m, float a, float b)//Вычисляет следующее значение координаты с вычислением оптимального y и вставляет новую точку в вектор c учетом пересортировки
{
	Point new_point;
	new_point.x = (p[t - 1].x + p[t].x) / 2 - (p[t].z - p[t - 1].z) / (2 * m);
	new_point.y = CalculateYMin(func,a, b, new_point.x);
	new_point.z = func.Calculate(new_point.x, new_point.y);
	vector<Point> temp = InsertSort(new_point, p, true);
	return temp;

}

Point GlobalMinCalculation(TPostfix func, double a, double b)
{
	/*Алгоритм Глобального Поиска для двумерной функции
	Нахождение минимума функции на квадрате [a,b]. Целевая функция g(x,y) должна удовлетворять обобщенному
	условию Липшица на всем квадрате поиска
	*/
	vector<Point> points(2);
	vector<Point> temp(2);
	vector<double> Ri(1);
	size_t k = 2;
	double M = 0, m = 0, stop_flag = 1;
	size_t t = 0;


	//Задаем начальные точки и значения функции в них
	points[0].x = a;
	points[1].x = b;
	points[0].y = CalculateYMin(func, a, b, a);
	points[1].y = CalculateYMin(func, a, b, b);
	points[0].z = func.Calculate(a, points[0].y);
	points[1].z = func.Calculate(b, points[1].y);

	while ((k < MAX_ITER) && (stop_flag > EPS))//Пока не получим больше 1000 точек или удовлетворительную точность
	{
		//Вычисляем М для всех имеющихся на данном шаге промежутков
		M = CalculateMBigMax(points, k, true);
		//Для вычисленного М вычисляем m
		m = CalculateMSmall(M);
		//Для каждого промежутка вычисляем вероятность нахождения минимума
		Ri = CalculateRs(m, points, k, true);
		//Ищем номер промежутка с наибольшей вероятностью (первый в случае нескольких наибольших)
		t = FindIntNumber(Ri);
		//Вычисление условия остановки
		stop_flag = points[t].x - points[t - 1].x;
		//Генерируем следующее значение координаты и добавляем точку с такой координатой и вычисленным
		//значением целевой функции в вектор точек с его последующей пересортировкой
		temp = InsertXNext(func,points, t, m, a, b);
		points = temp;
		//Количество точек в векторе увеличивается на 1
		k++;

	}
	//Пересчитываем номер нужного нам промежутка для последней сработавшей итерации

	//Вычисляем М для всех имеющихся на данном шаге промежутков
	M = CalculateMBigMax(points, k, true);
	//Для вычисленного М вычисляем m
	m = CalculateMSmall(M);
	//Для каждого промежутка вычисляем вероятность нахождения минимума
	Ri = CalculateRs(m, points, k, true);
	//Ищем номер промежутка с наибольшей вероятностью (первый в случае нескольких наибольших)
	t = FindIntNumber(Ri);

	//возвращаем один из концов интервала(точку) с наибольшей вероятностью нахождения в нем минимума,
	//полученный на последнем шаге перед остановкой цикла
	return points[t];
}

 double FindMin(vector< double> mins)
{
	 double true_min = 0;
	for (size_t i = 0; i < mins.size() - 1; i++)
	{
		if (mins[i + 1] < mins[i])
			true_min = mins[i + 1];
	}
	return true_min;
}

int main(int argc, char** argv)
{
	string path_to_test ="tests/test_00";
	ifstream test_stream(path_to_test, ios::in | ios::binary);
	if (!test_stream) {
		cout << "open " << path_to_test << " error" << endl;
		cout << '`';
		return 1;
	}
	string function; double left_border, right_border;
	test_stream >> function;
	test_stream >> left_border;
	test_stream >> right_border;
	test_stream.close();
	Point result;
	TPostfix p; p.PutInfix(function); p.ToPostfix();
	result = GlobalMinCalculation(p, left_border, right_border);
	//Выводим результаты
	char path_of_answer[] = "../results/result_00.rslt";
	int path_task_length = sizeof(path_of_answer) / sizeof(char);
	int path_answ_length = sizeof(path_of_answer) / sizeof(char);

	int ind_task;
	for (int ind = 0; ind < path_task_length; ++ind) 
	{
		if (path_to_test[ind] == '_') 
		{
			ind_task = ind + 1;
			break;
		}
	}

	int ind_answ;
	for (int ind = 0; ind < path_answ_length; ++ind) 
	{
		if (path_of_answer[ind] == '_') 
		{
			ind_answ = ind + 1;
			break;
		}
	}

	path_of_answer[ind_answ] = path_to_test[ind_task];
	path_of_answer[ind_answ + 1] = path_to_test[ind_task + 1];

	std::ofstream answer_stream(path_of_answer, ios::out | ios::binary);
	if (!answer_stream) {
		std::cout << "open " << path_of_answer << " error" << endl;
		return 1;
	}
	answer_stream << result.x << endl;
	answer_stream << result.y << endl;
	answer_stream << result.z << endl;

	answer_stream.close();
	
	cin >> left_border;
	
	return 0;

}