#include <fstream>
#include <string>

struct TaskGSA
{
    std::string function;
    double left_border;
    double right_border;

    unsigned int num_iter;
    double eps;
};

int main (int argc, char* argv[])
{
    //  Task #0
    {
        TaskGSA task;
        task.function = "x^2";
        task.left_border = -30;
        task.right_border = 30;

        task.num_iter = 1000000;
        task.eps = 0.0001;

        std::ofstream task_stream("../bin/tasks/task_00", std::ios::out | std::ios::binary);

        task_stream << task.function << std::endl;
        task_stream << task.left_border << std::endl;
        task_stream << task.right_border << std::endl;

        task_stream << task.num_iter << std::endl;
        task_stream << task.eps << std::endl;

        task_stream.close();
    }
    //  Task #1
    {
        TaskGSA task;
        task.function = "sin(x)";
        task.left_border = -30;
        task.right_border = 30;

        task.num_iter = 1000000;
        task.eps = 0.0001;

        std::ofstream task_stream("../bin/tasks/task_01", std::ios::out | std::ios::binary);

        task_stream << task.function << std::endl;
        task_stream << task.left_border << std::endl;
        task_stream << task.right_border << std::endl;

        task_stream << task.num_iter << std::endl;
        task_stream << task.eps << std::endl;

        task_stream.close();
    }
    //  Task #2
    {
        TaskGSA task;
        task.function = "(x/4)*cos(x)";
        task.left_border = 0;
        task.right_border = 30;

        task.num_iter = 1000000;
        task.eps = 0.0001;

        std::ofstream task_stream("../bin/tasks/task_02", std::ios::out | std::ios::binary);

        task_stream << task.function << std::endl;
        task_stream << task.left_border << std::endl;
        task_stream << task.right_border << std::endl;

        task_stream << task.num_iter << std::endl;
        task_stream << task.eps << std::endl;

        task_stream.close();
    }
    //  Task #3
    {
        TaskGSA task;
        task.function = "(x*sin((x^(0.5)))+cos(x)*x)/4";
        task.left_border = 0;
        task.right_border = 70;

        task.num_iter = 1000000;
        task.eps = 0.0001;

        std::ofstream task_stream("../bin/tasks/task_03", std::ios::out | std::ios::binary);

        task_stream << task.function << std::endl;
        task_stream << task.left_border << std::endl;
        task_stream << task.right_border << std::endl;

        task_stream << task.num_iter << std::endl;
        task_stream << task.eps << std::endl;

        task_stream.close();
    }
    //  Task #4
    {
        TaskGSA task;
        task.function = "(2^x)*sin(x)";
        task.left_border = 0;
        task.right_border = 20;

        task.num_iter = 1000000;
        task.eps = 0.0001;

        std::ofstream task_stream("../bin/tasks/task_04", std::ios::out | std::ios::binary);

        task_stream << task.function << std::endl;
        task_stream << task.left_border << std::endl;
        task_stream << task.right_border << std::endl;

        task_stream << task.num_iter << std::endl;
        task_stream << task.eps << std::endl;

        task_stream.close();
    }
    //  Task #5
    {
        TaskGSA task;
        task.function = "(10*x*sin((x^(0.5)))+cos(x)*x)/100";
        task.left_border = 0;
        task.right_border = 1000;

        task.num_iter = 10000000;
        task.eps = 0.0001;

        std::ofstream task_stream("../bin/tasks/task_05", std::ios::out | std::ios::binary);

        task_stream << task.function << std::endl;
        task_stream << task.left_border << std::endl;
        task_stream << task.right_border << std::endl;

        task_stream << task.num_iter << std::endl;
        task_stream << task.eps << std::endl;

        task_stream.close();
    }

    //  Task #6
    {
        TaskGSA task;
        task.function = "(x*sin((x^(0.5)))+cos(x)*x*10)/100";
        task.left_border = 0;
        task.right_border = 1000;

        task.num_iter = 10000000;
        task.eps = 0.0001;

        std::ofstream task_stream("../bin/tasks/task_06", std::ios::out | std::ios::binary);

        task_stream << task.function << std::endl;
        task_stream << task.left_border << std::endl;
        task_stream << task.right_border << std::endl;

        task_stream << task.num_iter << std::endl;
        task_stream << task.eps << std::endl;

        task_stream.close();
    }

    //  Task #7
    {
        TaskGSA task;
        task.function = "(x*sin((x^(0.5)))+cos(x/10)*x)/100";
        task.left_border = 0;
        task.right_border = 1000;

        task.num_iter = 1000000;
        task.eps = 0.0001;

        std::ofstream task_stream("../bin/tasks/task_07", std::ios::out | std::ios::binary);

        task_stream << task.function << std::endl;
        task_stream << task.left_border << std::endl;
        task_stream << task.right_border << std::endl;

        task_stream << task.num_iter << std::endl;
        task_stream << task.eps << std::endl;

        task_stream.close();
    }

    //  Task #8
    {
        TaskGSA task;
        task.function = "cos(x)";
        task.left_border = 0;
        task.right_border = 1000;

        task.num_iter = 10000;
        task.eps = 0.0001;

        std::ofstream task_stream("../bin/tasks/task_08", std::ios::out | std::ios::binary);

        task_stream << task.function << std::endl;
        task_stream << task.left_border << std::endl;
        task_stream << task.right_border << std::endl;

        task_stream << task.num_iter << std::endl;
        task_stream << task.eps << std::endl;

        task_stream.close();
    }

    //  Task #9
    {
        TaskGSA task;
        task.function = "4";
        task.left_border = -1000;
        task.right_border = 1000;

        task.num_iter = 100000;
        task.eps = 0.0001;

        std::ofstream task_stream("../bin/tasks/task_09", std::ios::out | std::ios::binary);

        task_stream << task.function << std::endl;
        task_stream << task.left_border << std::endl;
        task_stream << task.right_border << std::endl;

        task_stream << task.num_iter << std::endl;
        task_stream << task.eps << std::endl;

        task_stream.close();
    }

    return 0;
}
