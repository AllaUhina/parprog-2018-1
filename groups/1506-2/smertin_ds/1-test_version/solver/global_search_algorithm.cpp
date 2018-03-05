#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "tofunction/tofunction.h"

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
    const char* path_of_test = "../tasks/task_00.task";

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

    char path_of_answer[] = "../answers/answer_00.answ";
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

	double* x = new double[k];
	double R;
	double maxR = 0;
	int maxIR = 0;

	double minF;
	double minX;

	x[0] = a; x[1] = b;

	if (f(x[0]) < f(x[1]))
	{
		minF = f(x[0]);
		minX = x[0];
	}
	else
	{
		minF = f(x[1]);
		minX = x[1];
	}


	for (int i = 1; i < k - 1; ++i)
	{
		for (int j = 0; j < i; ++j)
			for (int l = 0; l < i - j; ++l)
				if (x[l] > x[l + 1])
					std::swap(x[l], x[l + 1]);

		for (int j = 1; j <= i; ++j)
		{
			M = (fabs(f(x[j]) - f(x[j - 1]))) / (x[j] - x[j - 1]);
			if (M > maxM)
			{
				maxM = M;
			}
		}

		if (maxM > 0)
		{
			m = r*maxM;
		}

		maxR = 0;
		maxIR = 1;
		for (int j = 1; j <= i; ++j)
		{
			R = m * (x[j] - x[j - 1]) + (pow((f(x[j]) - f(x[j - 1])), 2))
				/ (m * (x[j] - x[j - 1])) - 2 * (f(x[j]) + f(x[j - 1]));

			if (R > maxR)
			{
				maxR = R;
				maxIR = j;
			}
		}

		if (fabs(x[maxIR] - x[maxIR - 1]) < eps)
		{
			break;
		}

		x[i + 1] = 0.5 * (x[maxIR] + x[maxIR - 1])
                   - 0.5 * (f(x[maxIR]) - f(x[maxIR - 1])) / m;

		if (f(x[i + 1]) < minF)
		{
			minF = f(x[i + 1]);
			minX = x[i + 1];
		}
	}

    delete[] x;

    answer.minX = minX;
    answer.minY = minF;
}
