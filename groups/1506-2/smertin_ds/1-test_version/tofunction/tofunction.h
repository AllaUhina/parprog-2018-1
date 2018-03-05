#ifndef TOFUNCTION_H
#define TOFUNCTION_H

#define Error_1000 1000 // incorrect brackets
#define Error_1001 1001 // incorrect string
#define Error_1002 1002 // incorrect functions
#define Error_1003 1003 // divide by zero
#define Error_1004 1004 // logarithm <=0

#include <string>
#include <stack>
#include <cmath>

class ToFunction {
 private:
    std::string Infix;
    std::string Postfix;

    template<typename ValType>
    ValType get(std::stack<ValType> &);
    std::string CutInfix(std::string);
    void DeleteSpace(std::string);
    bool CheckBrackets(std::string&);

    int Priority(char);

    std::string InfiToPost(void);

    double CalcBin(double, double, char);
    double StandartFunc(double,char);
    double CalcPost(double);
 public:
    ToFunction(std::string);
    ToFunction();
    ~ToFunction() {}
    void SetFunction(std::string);
    std::string GetFunction(void);
    double Calculate(const double&);
};

#endif // TOFUNCTION_H
