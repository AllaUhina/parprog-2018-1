#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <iterator>
#include <algorithm>

#include "tbb/task_scheduler_init.h"
#include "tbb/tick_count.h"
#include "tbb/parallel_sort.h"
#include "tbb/parallel_reduce.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "tbb/concurrent_priority_queue.h"

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
        auto start_time = tbb::tick_count::now();
        answer.minX = task.left_border;
        answer.minY = f(task.left_border);

        auto finish_time = tbb::tick_count::now();

        report.d_time = (finish_time - start_time).seconds();
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
				bool operator<(const Characteristic& ch) const {
					return (R < ch.R);
				}
    };

	tbb::task_scheduler_init init(tbb::task_scheduler_init::deferred);
    int num_threads = tbb::task_scheduler_init::default_num_threads();
    init.initialize(num_threads);
    report.num_threads = num_threads;

    std::vector<Point> points(k);
    tbb::concurrent_priority_queue<Characteristic> q_maxCh(num_threads);
	std::vector<Characteristic> maxCh(num_threads);

    auto start_time = tbb::tick_count::now();

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

        tbb::parallel_sort(points.begin(), points.begin() + i, [](const Point &a, const Point &b) {
            return a.x < b.x;
        });

	class computing_M
	{
		const std::vector<Point> p_vec;
		double max_M;
	public:
		explicit computing_M(std::vector<Point> pv, double m): p_vec(pv), max_M(m)
		{	}
		computing_M(const computing_M& cm, tbb::split): p_vec(cm.p_vec), max_M(cm.max_M)
		{	}
		void operator()(const tbb::blocked_range<int> &r) {
			int begin = r.begin(), end = r.end();
			for (int j = begin; j <= end; ++j) {
    auto M = (fabs(p_vec[j].y - p_vec[j - 1].y)) / (p_vec[j].x - p_vec[j - 1].x);
    max_M = (M > max_M) ? M : max_M;
			}
		}
		void join(const computing_M& cm) {
			max_M = (cm.max_M > max_M) ? cm.max_M : max_M;
		}
		double Result() {
			return max_M;
		}
	} maxM_comput(points, maxM);
	tbb::parallel_reduce(tbb::blocked_range<int>(1, i, num_threads - 1), maxM_comput);
	maxM = maxM_comput.Result();

        if (maxM > 0) {
            m = r * maxM;
        }

		q_maxCh.clear();
		tbb::parallel_for(tbb::blocked_range<int>(1, i, num_threads - 1),
			[&](const tbb::blocked_range<int>& r) {
				int begin = r.begin(), end = r.end();
				Characteristic current_ch;
				for (int j = begin; j <= end; ++j) {
					current_ch.R = m * (points[j].x - points[j - 1].x) +
												((points[j].y - points[j - 1].y) * (points[j].y - points[j - 1].y))
												/ (m * (points[j].x - points[j - 1].x)) -
												2 * (points[j].y + points[j - 1].y);
					current_ch.iter = j;
					q_maxCh.push(current_ch);
				}
			});

		for (int j = num_threads - 1; j >= 0; --j) {
			q_maxCh.try_pop(maxCh[j]);
		}
        if (fabs(points[maxCh[0].iter].x - points[maxCh[0].iter - 1].x) < eps) {
            break;
        }


		class computing_minPoint
		{
			std::vector<Point> p_vec;
			const std::vector<Characteristic> chvec;
			const int i;
            const double m;
			Point min_point;
		public:
			explicit computing_minPoint(std::vector<Point> pv, std::vector<Characteristic> chv, Point minP, int iter, double _m):
			p_vec(pv), chvec(chv), min_point(minP), i(iter), m(_m) {	}
			computing_minPoint(const computing_minPoint& cm, tbb::split):
			p_vec(cm.p_vec), chvec(cm.chvec), min_point(cm.min_point), i(cm.i), m(cm.m) {	}
			void operator()(const tbb::blocked_range<int> &r) {
				int begin = r.begin(), end = r.end();
				for (int current_thread = begin; current_thread <= end; ++current_thread) {
					Point newPoint;
                    newPoint.x = 0.5 * (p_vec[chvec[current_thread].iter].x + p_vec[chvec[current_thread].iter - 1].x)
                                 - 0.5 * (p_vec[chvec[current_thread].iter].y - p_vec[chvec[current_thread].iter - 1].y) / m;
                    newPoint.y = f(newPoint.x);
                    p_vec[i + 1 + current_thread] = newPoint;
					min_point = (newPoint.y < min_point.y) ? newPoint : min_point;
				}
			}
			void join(const computing_minPoint& cm) {
				min_point = (cm.min_point.y < min_point.y) ? cm.min_point : min_point;
			}
			std::pair<Point, std::vector<Point>> Result() {
				std::pair<Point, std::vector<Point>> res;
                res.first = min_point; res.second = p_vec;
                return res;
			}
		} minP_comput(points, maxCh, minPoint, i, m);
        
		tbb::parallel_reduce(tbb::blocked_range<int>(0, num_threads, num_threads - 1), minP_comput);
		std::pair<Point, std::vector<Point>> res = minP_comput.Result();
		minPoint = res.first;
		points = res.second;

        ++num_iter;
    }

    auto finish_time = tbb::tick_count::now();

    report.d_time = (finish_time - start_time).seconds();
    report.num_iter = num_iter;

    answer.minX = minPoint.x;
    answer.minY = minPoint.y;
    return answer;
}
