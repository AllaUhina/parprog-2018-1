#include "Solver.h"


vector<Point> InsertSort(Point a, vector<Point> b, bool is_x_dim)//������� ����� ����� � ������ � ��� ����������
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

 double CalculateMBigMax(vector<Point> p, size_t k, bool is_x_dim)// ������� ������������ �������� � ����� ���� ���������������� ��� � ������� ����� �� � ��� �� y
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

 double CalculateMSmall( double M)//������� m ��� ��� ������������ M � �����. � ����������
{
	if (M == 0)
		return 1;
	else
		return M * PARAM_R;
}

vector< double> CalculateRs( double m, vector<Point> p, size_t k, bool is_x_dim)//��������� ������ �������� R(i) - ����������� ���������� �������� �� ���������
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

unsigned FindIntNumber(vector< double> Ri)//������� ����� ����������, ���������������� ����������� �������� �����������, ��������� � 1
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

vector<Point> InsertYNext(TPostfix func,vector<Point> p, int t,  double m,  double _x)//��������� ��������� �������� ���������� ��� � - ����. � ��������� ����� ����� � ������ c ������ ��������������
{
	Point new_point;
	new_point.x = _x;
	new_point.y = ((p[t - 1].y + p[t].y) / 2) - ((p[t].z - p[t - 1].z) / (2 * m));
	new_point.z = func.Calculate(_x, new_point.y);
	vector<Point> temp = InsertSort(new_point, p, false);
	return temp;
}

 double CalculateYMin(TPostfix func, double a,  double b,  double _x)//��������� ���������� y, �����. ����������� �������� ������� ��� ������������� �
{
	vector<Point> points(2);
	vector<Point> temp(2);
	vector< double> Ri(1);
	size_t k = 2;
	float M = 0, m = 0, stop_flag = 1;
	size_t t = 0;

	//������ ��������� ����� � �������� ������� � ���
	points[0].x = _x; points[0].y = a; points[0].z = func.Calculate(_x, a);
	points[1].x = _x; points[1].y = b; points[1].z = func.Calculate(_x, b);

	while ((k < MAX_ITER) && (stop_flag > EPS))//���� �� ������� ������ 1000 ����� ��� ������������������ ��������
	{
		//��������� � ��� ���� ��������� �� ������ ���� �����������
		M = CalculateMBigMax(points, k, false);
		//��� ������������ � ��������� m
		m = CalculateMSmall(M);
		//��� ������� ���������� ��������� ����������� ���������� ��������
		Ri = CalculateRs(m, points, k, false);
		//���� ����� ���������� � ���������� ������������ (������ � ������ ���������� ����������)
		t = FindIntNumber(Ri);
		//���������� ������� ���������
		stop_flag = points[t].y - points[t - 1].y;
		//��������� ���������� ���������� �������
		temp.resize(k);
		//���������� ��������� �������� ���������� � ��������� ����� � ����� ����������� � �����������
		//��������� ������� ������� � ������ ����� � ��� ����������� ���������������
		temp = InsertYNext(func,points, t, m, _x);
		points = temp;
		//���������� ����� � ������� ������������� �� 1
		k++;

	}
	//������������� ����� ������� ��� ���������� ��� ��������� ����������� ��������

	//��������� � ��� ���� ��������� �� ������ ���� �����������
	M = CalculateMBigMax(points, k, false);
	//��� ������������ � ��������� m
	m = CalculateMSmall(M);
	//��� ������� ���������� ��������� ����������� ���������� ��������
	Ri = CalculateRs(m, points, k, false);
	//���� ����� ���������� � ���������� ������������ (������ � ������ ���������� ����������)
	t = FindIntNumber(Ri);

	//���������� ���� �� ������ ���������(�����) � ���������� ������������ ���������� � ��� ��������,
	//���������� �� ��������� ���� ����� ���������� �����
	return points[t].y;

}

vector<Point> InsertXNext(TPostfix func, vector<Point> p, int t, double m, double a, double b)//��������� ��������� �������� ���������� � ����������� ������������ y � ��������� ����� ����� � ������ c ������ ��������������
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
	/*�������� ����������� ������ ��� ��������� �������
	���������� �������� ������� �� �������� [a,b]. ������� ������� g(x,y) ������ ������������� �����������
	������� ������� �� ���� �������� ������
	*/
	vector<Point> points(2);
	vector<Point> temp(2);
	vector<double> Ri(1);
	size_t k = 2;
	double M = 0, m = 0, stop_flag = 1;
	size_t t = 0;


	//������ ��������� ����� � �������� ������� � ���
	points[0].x = a;
	points[1].x = b;
	points[0].y = CalculateYMin(func, a, b, a);
	points[1].y = CalculateYMin(func, a, b, b);
	points[0].z = func.Calculate(a, points[0].y);
	points[1].z = func.Calculate(b, points[1].y);

	while ((k < MAX_ITER) && (stop_flag > EPS))//���� �� ������� ������ 1000 ����� ��� ������������������ ��������
	{
		//��������� � ��� ���� ��������� �� ������ ���� �����������
		M = CalculateMBigMax(points, k, true);
		//��� ������������ � ��������� m
		m = CalculateMSmall(M);
		//��� ������� ���������� ��������� ����������� ���������� ��������
		Ri = CalculateRs(m, points, k, true);
		//���� ����� ���������� � ���������� ������������ (������ � ������ ���������� ����������)
		t = FindIntNumber(Ri);
		//���������� ������� ���������
		stop_flag = points[t].x - points[t - 1].x;
		//���������� ��������� �������� ���������� � ��������� ����� � ����� ����������� � �����������
		//��������� ������� ������� � ������ ����� � ��� ����������� ���������������
		temp = InsertXNext(func,points, t, m, a, b);
		points = temp;
		//���������� ����� � ������� ������������� �� 1
		k++;

	}
	//������������� ����� ������� ��� ���������� ��� ��������� ����������� ��������

	//��������� � ��� ���� ��������� �� ������ ���� �����������
	M = CalculateMBigMax(points, k, true);
	//��� ������������ � ��������� m
	m = CalculateMSmall(M);
	//��� ������� ���������� ��������� ����������� ���������� ��������
	Ri = CalculateRs(m, points, k, true);
	//���� ����� ���������� � ���������� ������������ (������ � ������ ���������� ����������)
	t = FindIntNumber(Ri);

	//���������� ���� �� ������ ���������(�����) � ���������� ������������ ���������� � ��� ��������,
	//���������� �� ��������� ���� ����� ���������� �����
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

