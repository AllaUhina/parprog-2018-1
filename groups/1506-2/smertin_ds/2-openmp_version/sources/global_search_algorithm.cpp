#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

#include <omp.h>

#include "./tofunction/tofunction.h"

struct TaskGSA {
    std::string function;
    double left_border;
    double right_border;

    unsigned int num_iter;
    double eps;
} task;

struct AnswerGSA {
    double minX;
    double minY;
} answer;

struct ReportGSA
{
    double d_time;
    int num_iter;
    int num_threads;
} report;

ToFunction toFunc;

double f(double);

AnswerGSA methodGSA();

int main(int argc, char *argv[]) {
    const char *path_of_test = "../bin/tasks/task_09";

    if (argc > 1) {
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
    char path_of_report[] = "../bin/reports/report_00";

    int path_task_length = sizeof(path_of_answer) / sizeof(char);
    int path_answ_length = sizeof(path_of_answer) / sizeof(char);
    int path_rep_length = sizeof(path_of_report) / sizeof(char);

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

    int ind_rep;
    for (int ind = 0; ind < path_rep_length; ++ind) {
        if (path_of_report[ind] == '_') {
            ind_rep = ind + 1;
            break;
        }
    }

    path_of_report[ind_rep] = path_of_answer[ind_answ] = path_of_test[ind_task];
    path_of_report[ind_rep + 1] = path_of_answer[ind_answ + 1] = path_of_test[ind_task + 1];

    std::ofstream answer_stream(path_of_answer, std::ios::out | std::ios::binary);
    if (!answer_stream) {
        std::cout << "open " << path_of_answer << " error" << std::endl;
        return 1;
    }
    answer_stream << answer.minX << std::endl;
    answer_stream << answer.minY << std::endl;

    answer_stream.close();

    std::ofstream report_stream(path_of_report, std::ios::out | std::ios::binary);
    if (!answer_stream) {
        std::cout << "open " << path_of_report << " error" << std::endl;
        return 1;
    }
    report_stream << report.num_threads << std::endl;
    report_stream << report.d_time << std::endl;
    report_stream << report.num_iter << std::endl;

    report_stream.close();

    return 0;
}

double f(double x) {
    toFunc.Calculate(x);
}

AnswerGSA methodGSA() {
    if (task.function.find('x') == std::string::npos) {
        auto start_time = omp_get_wtime();
        answer.minX = task.left_border;
        answer.minY = f(task.left_border);

        auto finish_time = omp_get_wtime();

        report.d_time = finish_time - start_time;
        report.num_iter = 0;

        return answer;
    }
    const double a = task.left_border;
    const double b = task.right_border;
    double eps = task.eps;
    int k = task.num_iter;

    const double r = 3;
    double m = 1;
    double maxM = 0;
    double M;

    struct Point {
        double x;
        double y;

        Point &operator=(const Point &p) {
            this->x = p.x;
            this->y = p.y;
            return *this;
        }
    };
    struct Characteristic {
        double R;
        int iter;
    };

    auto num_threads = omp_get_max_threads();
    omp_set_num_threads(num_threads);

    report.num_threads = num_threads;

    std::vector<Point> points(k);
    std::vector<Characteristic> maxCh(num_threads);

    auto start_time = omp_get_wtime();

    points[0].x = a;
    points[num_threads].x = b;
    points[0].y = f(a);
    points[num_threads].y = f(b);
    Point minPoint = (points[0].y < points[num_threads].y) ? points[0] : points[num_threads];

    auto step = (b - a) / num_threads;
    Point current_point = points[0];
    for (int j = 1; j < num_threads; ++j) {
        current_point.x += step;
        current_point.y = f(current_point.x);
        points[j] = current_point;

        minPoint = (current_point.y < minPoint.y) ? current_point : minPoint;
    }

    int num_iter = 0;
    for (int i = num_threads; i < k - 1 - num_threads; i += num_threads) {

        std::sort(points.begin(), points.begin() + i, [](const Point &a, const Point &b) {
            return a.x < b.x;
        });

#pragma omp parallel for private(M) reduction(max : maxM)
        for (int j = 1; j <= i; ++j) {
            M = (fabs(points[j].y - points[j - 1].y)) / (points[j].x - points[j - 1].x);
            maxM = (M > maxM) ? M : maxM;
        }

        if (maxM > 0) {
            m = r * maxM;
        }
#pragma omp parallel
        {
#pragma omp for
            for (int j = 0; j < num_threads; ++j) {
                maxCh[j].R = 0;
                maxCh[j].iter = 1;
            }
            Characteristic current_ch;
#pragma omp for
            for (int j = 1; j <= i; ++j) {
                current_ch.R = m * (points[j].x - points[j - 1].x) +
                               ((points[j].y - points[j - 1].y) * (points[j].y - points[j - 1].y))
                               / (m * (points[j].x - points[j - 1].x)) -
                               2 * (points[j].y + points[j - 1].y);
                current_ch.iter = j;

                if (j == 1) {
                    maxCh[j - 1] = current_ch;
                } else {
                    int ins_id;
                    for (ins_id = 0; ins_id < num_threads; ++ins_id) {
                        if (current_ch.R > maxCh[ins_id].R) {
                            if (ins_id == num_threads - 1) {
                                maxCh[ins_id] = current_ch;
                            } else {
                                for (int move_iter = num_threads - 1; move_iter > ins_id; --move_iter) {
                                    maxCh[move_iter] = maxCh[move_iter - 1];
                                }
                                maxCh[ins_id] = current_ch;
                            }
                            break;
                        }
                    }
                }
            }
        }

        if (fabs(points[maxCh[0].iter].x - points[maxCh[0].iter - 1].x) < eps) {
            break;
        }

#pragma omp parallel
        {
            auto current_thread = omp_get_thread_num();
            Point newPoint;
            newPoint.x = 0.5 * (points[maxCh[current_thread].iter].x + points[maxCh[current_thread].iter - 1].x)
                         - 0.5 * (points[maxCh[current_thread].iter].y - points[maxCh[current_thread].iter - 1].y) / m;
            newPoint.y = f(newPoint.x);
            points[i + 1 + current_thread] = newPoint;

#pragma omp critical
            {
                minPoint = (newPoint.y < minPoint.y) ? newPoint : minPoint;
            }
        }
        ++num_iter;
    }

    auto finish_time = omp_get_wtime();

    report.d_time = finish_time - start_time;
    report.num_iter = num_iter;

    answer.minX = minPoint.x;
    answer.minY = minPoint.y;
    return answer;
}
