#include <fstream>
#include <iostream>
#include <string>

struct TaskGSA
{
    std::string function;
    double left_border;
    double right_border;

    unsigned int num_iter;
    double eps;
};

struct AnswerGSA
{
    double minX;
    double minY;
};

int main (int argc, char* argv[])
{
    const char* task_path;
    const char* answer_path;
    const char* result_path;
    if (argc == 4) {
        task_path = argv[1];
        answer_path = argv[2];
        result_path = argv[3];
    } else {
        return 1;
    }

    TaskGSA task;
    AnswerGSA answer;
    AnswerGSA result;

//=============================================================================
    std::ifstream task_stream(task_path, std::ios::in | std::ios::binary);
    if (!task_stream) {
        std::cout << "open " << task_path << " error" << std::endl;
        return 1;
    }
    task_stream >> task.function;
    task_stream >> task.left_border;
    task_stream >> task.right_border;
    task_stream >> task.num_iter;
    task_stream >> task.eps;
    task_stream.close();
//=============================================================================
    std::ifstream answer_stream(answer_path, std::ios::in | std::ios::binary);
    if (!answer_stream) {
        std::cout << "open " << answer_path << " error" << std::endl;
        return 1;
    }
    answer_stream >> answer.minX;
    answer_stream >> answer.minY;
    answer_stream.close();
//=============================================================================
    std::ifstream result_stream(result_path, std::ios::in | std::ios::binary);
    if (!result_stream) {
        std::cout << "open " << result_path << " error" << std::endl;
        return 1;
    }
    result_stream >> result.minX;
    result_stream >> result.minY;
    result_stream.close();
//=============================================================================
    std::cout << "\nTASK:" << std::endl;
    std::cout << "\tfunction: " << task.function << std::endl;
    std::cout << "\tleft border: " << task.left_border << std::endl;
    std::cout << "\tright border " << task.right_border << std::endl;
    std::cout << "\tnumber of iterations: " << task.num_iter << std::endl;
    std::cout << "\taccuracy: " << task.eps << std::endl;

    std::cout << "\nRESULT OF THE METHOD:" << std::endl;
    std::cout << "\t(" << result.minX << ", " << result.minY << ")" << std::endl;

    std::cout << "\nCORRECT ANSWER:" << std::endl;
    std::cout << "\t(" << answer.minX << ", " << answer.minY << ")" << std::endl;

    if ( ((answer.minY < result.minY + task.eps) && (answer.minY > result.minY - task.eps))
      || ((answer.minX < result.minX + task.eps) && (answer.minX > result.minX - task.eps)) ){
        std::cout << "\n\t\033[1;32mOK\033[0m\n" << std::endl;
    } else {
        std::cout << "\n\t\033[1;31mFAIL\033[0m\n" << std::endl;
    }

    return 0;
}
