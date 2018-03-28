#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

#include "./tofunction/tofunction.h"

struct TaskGSA
{
    std::string function;
    double left_border;
    double right_border;

    unsigned int num_iter;
    double eps;
} task;

struct AnswerGSA
{
    double minX;
    double minY;
} answer;

ToFunction toFunc;

double f(double);
void methodGSA();

int main(int argc, char* argv[])
{
    const char* path_of_test = "../bin/tasks/task_07";

    if (argc > 1){
        path_of_test = argv[1];
    }

    std::ifstream task_stream(path_of_test, std::ios::in | std::ios::binary);
    if (!task_stream) {
        std::cout << "open " << path_of_test << " error" << std::endl;
        return 1;
    }
    task_stream >> task.function;
    task_stream >> task.left_border;
    task_stream >> task.right_border;
    task_stream >> task.num_iter;
    task_stream >> task.eps;
    task_stream.close();

    toFunc.SetFunction(task.function);
//=============================================================================
    methodGSA();
//=============================================================================

    char path_of_answer[] = "../bin/results/result_00";
    int path_task_length = sizeof(path_of_answer) / sizeof(char);
    int path_answ_length = sizeof(path_of_answer) / sizeof(char);

    int ind_task;
    for (int ind = 0; ind < path_task_length; ++ind) {
        if (path_of_test[ind] == '_') {
            ind_task = ind + 1;
            break;
        }
    }

    int ind_answ;
    for (int ind = 0; ind < path_answ_length; ++ind) {
        if (path_of_answer[ind] == '_') {
            ind_answ = ind + 1;
            break;
        }
    }

    path_of_answer[ind_answ] = path_of_test[ind_task];
    path_of_answer[ind_answ + 1] = path_of_test[ind_task + 1];

    std::ofstream answer_stream(path_of_answer, std::ios::out | std::ios::binary);
    if (!answer_stream) {
        std::cout << "open " << path_of_answer << " error" << std::endl;
        return 1;
    }
    answer_stream << answer.minX << std::endl;
    answer_stream << answer.minY << std::endl;

    answer_stream.close();

	return 0;
}

double f(double x)
{
    toFunc.Calculate(x);
}

void methodGSA()
{
	const double a = task.left_border;
	const double b = task.right_border;
    double eps = task.eps;
	int k = task.num_iter;

    const double r = 3;
	double m = 1;
	double maxM = 0;
	double M;

    struct Point
    {
        double x;
        double y;
        void operator=(const Point& p)
        {
            x = p.x;
            y = p.y;
        }
    };
	std::vector<Point> points;
	double R;
	double maxR = 0;
	int maxIR = 0;

	Point minPoint;
    Point left_point, right_point;

	left_point.x = a; right_point.x = b;
    left_point.y = f(left_point.x); right_point.y = f(right_point.x);
    points.push_back(left_point); points.push_back(right_point);

    minPoint = (left_point.y < right_point.y) ? left_point : right_point;

	for (int i = 1; i < k - 1; ++i)
	{
        std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
            return a.x < b.x;
        });

		for (int j = 1; j <= i; ++j)
		{
			M = (fabs(points[j].y - points[j - 1].y)) / (points[j].x - points [j - 1].x);
			if (M > maxM)
			{
				maxM = M;
			}
		}

		if (maxM > 0)
		{
			m = r * maxM;
		}

		maxR = 0;
		maxIR = 1;
		for (int j = 1; j <= i; ++j)
		{
			R = m * (points[j].x - points[j - 1].x) + (pow((points[j].y - points[j - 1].y), 2))
				/ (m * (points[j].x - points[j - 1].x)) - 2 * (points[j].y + points[j - 1].y);

			if (R > maxR)
			{
				maxR = R;
				maxIR = j;
			}
		}

		if (fabs(points[maxIR].x - points[maxIR - 1].x) < eps)
		{
			break;
		}

        Point newPoint;
        newPoint.x = 0.5 * (points[maxIR].x + points[maxIR - 1].x)
                   - 0.5 * (points[maxIR].y - points[maxIR - 1].y) / m;
        newPoint.y = f(newPoint.x);
        points.push_back(newPoint);

        minPoint = (newPoint.y < minPoint.y) ? newPoint : minPoint;
	}

    answer.minX = minPoint.x;
    answer.minY = minPoint.y;
}
