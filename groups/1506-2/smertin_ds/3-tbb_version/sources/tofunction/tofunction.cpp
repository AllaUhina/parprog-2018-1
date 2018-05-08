#include "tofunction.h"

template<typename ValType>//потому что в STL для stack нет метода извлечения элемента с последующим его удалением
ValType ToFunction::get(std::stack<ValType> &st)
{
    ValType res = st.top();//элемент на вершине
    st.pop();//элемент удаляется
    return res;
}

void ToFunction::DeleteSpace(std::string Line)
{
    for (std::string::iterator Line_Iter = Line.begin();Line_Iter != Line.end();++Line_Iter)
        if (*Line_Iter == ' ')
        {
            Line.erase(Line_Iter);
            Line_Iter--;
        }
}

std::string ToFunction::CutInfix(std::string Line)
{
    std::string CutIn = "";
    std::string temp = "";
    bool Check = false;
    bool CheckForName = false;

    if (Priority(Line[0])==2)
        Line = Line.insert(0, "0");
    else if (Priority(Line[0]) == 3 || Priority(Line[0]) == 4)
        throw Error_1001;
    for (std::string::iterator it = Line.begin(); it != Line.end(); ++it)
    {
        if ((*it >= 'a') && (*it <= 'z') && (*it != 'x'))
        {
            CheckForName = true;
            temp += *it;
            Check = true;
        }
        else if (CheckForName && *it!='(')
            temp += *it;
        else
            if (*it != '(')
            {
                CutIn += *it;
            }
        if (*it == '(')
        {
            CheckForName = false;
            if (*(it + 1) == ')')
                throw Error_1000;
            if ((*(it + 1) == '-')||(*(it + 1)=='+'))
            {
                Line = Line.insert(1 + std::distance(Line.begin(), it), "0");
                if(!Check)
                    CutIn += '(';
            }
            if (Check)
            {
                if (temp == "sin")
                    CutIn += "s(";
                else if (temp == "cos")
                    CutIn += "c(";
                else if (temp == "tg")
                    CutIn += "t(";
                else if (temp == "ctg")
                    CutIn += "k(";
                else if (temp == "ln")
                    CutIn += "l(";
                else if (temp == "log10")
                    CutIn += "b(";
                else if (temp == "log2")
                    CutIn += "d(";
                else if (temp == "abs")
                    CutIn += "a(";
                else
                    throw Error_1002;
                temp = "";
                Check = false;
            }
        }
    }
    if (temp != "")
        throw Error_1002;
    CutIn += '\0';
    return CutIn;
}
int ToFunction::Priority(char Operation)
{
    if (Operation == '(')
        return 0;
    else if (Operation == ')')
        return 1;
    else if ((Operation == '+') || (Operation == '-'))
        return 2;
    else if ((Operation == '*') || (Operation == '/'))
        return 3;
    else if (Operation == '^')
        return 4;
    else if ((Operation == 's') || (Operation == 'c') || (Operation == 'l') || (Operation == 't') ||
        (Operation == 'k') || (Operation == 'b') || (Operation == 'd') || (Operation == 'a'))
        return 5;
    else if ((Operation >= '0') && (Operation <= '9') || (Operation == '.')) //если символ - составляющее числа
        return -1;
    else if (Operation == ' ')
        return -2;
    else if (Operation == 'x')
        return -4;
    else //символ находится в таблице ASCII и не принадлежит множеству {'(', ')', '+', '-', '*', '/', '.', ' ', '0'...'9'}
        return -3;
};

std::string ToFunction::InfiToPost(void)
{
    std::stack<char> Operator;
    std::string Post = "";
    bool NumbCheck = false;
    bool VarCheck = false;
    if (Infix[0] == '.')
        throw Error_1001;
    for (std::string::iterator it = Infix.begin(); it != Infix.end(); ++it) {
        int priority = Priority(*it);
        if (*it == '\0')
            break;
        if (priority == -1) {
            if ((*it == '.') && ((*(it + 1) == '.')||Priority(*(it + 1))!=-1))
                throw Error_1001;
            if ((*it == '.') && (it != Infix.begin() && Priority(*(it - 1)) != -1))
                throw Error_1001;
            if (!VarCheck) {
                Post += *it;
                if (!NumbCheck)
                    NumbCheck = true;
            }
            else
                throw Error_1001;
        }
        else if (priority == -4)
        {
            if (!NumbCheck) {
                Post += *it;
                if (!VarCheck) VarCheck = true;
            }
            else
                throw Error_1001;
        }
        else {
            if (priority >= 2 && (priority != 5 &&((*(it + 1)) == '\0' || Priority(*(it + 1)) >= 2&& Priority(*(it + 1))!=5)))
                throw Error_1001;
            static int oldOp = -1;
            if (NumbCheck || VarCheck) {
                NumbCheck = false;
                VarCheck = false;
                Post += " ";
            }
            if (priority == 1) {
                while (Operator.size()!=0 && Priority(Operator.top()) != 0) {
                    Post += get(Operator);
                }
                if(Operator.size()!=0)
                    get(Operator);
            }
            else if (priority == 0 || priority > oldOp || Operator.empty()) {
                oldOp = *it;
                Operator.push(oldOp);
            }
            else {
                while ((!Operator.empty())&&(Priority(Operator.top()) >= priority)) {
                    Post += get(Operator);
                }
                Post += " ";
                oldOp = *it;
                Operator.push(oldOp);
            }
        }
    }
    while (Operator.empty() == false)//извлечь из стека все операции, которые остались
        Post += get(Operator);
    Post += '\0';

    return Post;
};

bool ToFunction::CheckBrackets(std::string &Line)
{
    std::stack<int> Brackets;
    bool result = true;

    for (std::string::iterator Line_Iter = Line.begin();Line_Iter != Line.end();++Line_Iter)
    {
        if ((Line_Iter != Line.end()) && (*Line_Iter != '(') && (*Line_Iter != ')'))
            continue;

        if (*Line_Iter == '(')
            Brackets.push(1);
        else if (*Line_Iter == ')')
        {
            if (Brackets.empty())
            {
                result = false;
                break;
            }
            else
                get(Brackets);
        }
    }
    if (!Brackets.empty())
        result = false;
    return result;
}

double ToFunction::CalcBin(double Fir, double Sec, char Op)
{
    if (Op == '-')
        return Fir - Sec;
    else if (Op == '+')
        return Fir + Sec;
    else if (Op == '*')
        return Fir * Sec;
    else if (Op == '/')
        if (Sec != 0)
            return Fir / Sec;
        else
            throw Error_1003;
    else if (Op == '^')
        return pow(Fir, Sec);
}

double ToFunction::StandartFunc(double Fir,char Op)
{
    if (Op == 's')
        return sin(Fir);
    else if (Op == 'a')
        return abs(Fir);
    else if (Op == 'c')
        return cos(Fir);
    else if (Op == 't')
        return tan(Fir);
    else if (Op == 'k')
        if (tan(Fir) != 0)
            return 1 / tan(Fir);
        else
            throw Error_1003;
    else if (Op == 'l')
        if (Fir > 0)
            return log(Fir);
        else
            throw Error_1004;
    else if (Op == 'b')
        if (Fir > 0)
            return log10(Fir);
        else
            throw Error_1004;
    else if (Op == 'd')
        if (Fir > 0)
            return log2(Fir);
        else
            throw Error_1004;
}
double ToFunction::CalcPost(double x)
{
    std::stack<double> Numbers;
    std::string CurrNumbString = "";
    double CurrNumbDouble = 0;

    for (std::string::iterator Line_Iter = Postfix.begin();Line_Iter != Postfix.end();++Line_Iter)
    {
        if (Priority(*Line_Iter) == -2)//если пробел
            Line_Iter++;
        if (*Line_Iter == 'x')
        {
            Numbers.push(x);
            Line_Iter++;
        }
        while ((Line_Iter != Postfix.end()) && (Priority(*Line_Iter) == -1))//запись числа из строки в числовую строку
        {
            CurrNumbString += *Line_Iter;
            Line_Iter++;
        }
        CurrNumbString += '\0';
        if (CurrNumbString[0] != '\0')//перевод числовой строки в double
            Numbers.push(stod(CurrNumbString));
        CurrNumbString = "";
        if (Priority(*Line_Iter) > 0)//если операция
        {
            if (Priority(*Line_Iter) != 5)
            {
                CurrNumbDouble = CalcBin(get(Numbers), get(Numbers), *Line_Iter);
                Numbers.push(CurrNumbDouble);
            }
            else
            {
                CurrNumbDouble = StandartFunc(get(Numbers), *Line_Iter);
                Numbers.push(CurrNumbDouble);
            }

        }
    }
    return get(Numbers);
}

ToFunction::ToFunction(std::string Line)
{
    SetFunction(Line);
}

ToFunction::ToFunction() {
}

void ToFunction::SetFunction(std::string Line)
{
    if (CheckBrackets(Line))
    {
        DeleteSpace(Line);
        Infix = CutInfix(Line);
        Postfix = InfiToPost();
    }
    else
        throw Error_1000;
}

std::string ToFunction::GetFunction(void)
{
    return Infix;
}
double ToFunction::Calculate(const double& x)
{
    if (Infix == "")
        throw Error_1004;
    else
        return CalcPost(x);
}
