#include "postfix.h"
#include "stack.h"
#include "cmath"


int TPostfix::IsOperation(string &str, int &i)
{
	for (int j = 0; j <9; j++)
	{
		if (j == 4)
			if (str.substr(i, 3) == "sin") return 4;
		if (j == 5)
			if (str.substr(i, 3) == "cos") return 5;
		if (str[i] == operation[j][0]) return j;
	}
	return -1;
}

int TPostfix::GetPriority(string &str)
{
	int i = 0;
	while (str != operation[i])
		i++;
	return priority[i];
}



void TPostfix::ToPostfix()
{
	string token = infix;
	TStack<string> operations;
	string str, output, operationTop;
	int size = infix.size(), operationIndex, p, m;

	for (int i = 0; i < size; i++)
	{
		if (token[i] == '(')
		{
			operations.Push("(");
			continue;
		}
		if (token[i] == ')')
		{
			str = operations.Pop();
			while (str != "(")
			{
				output += str;
				str = operations.Pop();
			}
			continue;
		}

		operationIndex = IsOperation(token, i);
		if (operationIndex == -1) //если символ не операция
		{
			p = 0;
			m = i;
			do
			{
				m++;
				p++;
				if (m == size)
					break;
				operationIndex = IsOperation(token, m);


			} while (operationIndex == -1);
			output += token.substr(i, p) + " ";
			i = i + p - 1;

		}
		else  //если операция 
		{

			if (operationIndex == 4 || operationIndex == 5) i += 2;
			if (operations.IsEmpty())
			{
				operations.Push(operation[operationIndex]);
				continue;
			}

			operationTop = operations.GetTop();
			str = operation[operationIndex];
			if (operationTop == str)
			{
				operations.Push(str);
				continue;
			}

			if (GetPriority(str) >= GetPriority(operationTop))
				operations.Push(str);
			else
			{
				while (GetPriority(str) <= GetPriority(operationTop) && !(operations.IsEmpty()))
				{
					output += operations.Pop();
					if (operations.IsEmpty())
					{
						continue;
					}
					operationTop = operations.GetTop();
				}
				operations.Push(str);
			}
		}
	}
	while (!operations.IsEmpty())
		output += operations.Pop();
	postfix = output;
}

double TPostfix::Calculate(double X, double Y)
{
	if (postfix == "Not exist")
	{
		cout << "Eror" << endl;
		return 0;
	}
	int OperationIndex;
	TStack <double> stack;
	string str;
	double tmp, var1, var2;
	int p, size = postfix.size();
	int i = 0;
	while (i < size)
	{
		OperationIndex = IsOperation(postfix, i);
		if (OperationIndex == -1)
		{
			p = 0;
			do
			{
				p++;
				if (i + p == size)
					break;
			} while (postfix[i + p] != ' ');
			str = postfix.substr(i, p);
			if (str == "x") tmp = X;
				else if (str == "y") tmp = Y;
					else tmp = atof(str.c_str());
			i = i + p;
			stack.Push(tmp);
			i++;
			continue;
		}
		else
		{

			var1 = stack.Pop();
			if (OperationIndex == 4)
			{
				i = i + 2;
				stack.Push(sin((var1*3.14159265359) / 180));
				i++;
				continue;
			}
			if (OperationIndex == 5)
			{
				i = i + 2;
				stack.Push(cos((var1*3.14159265) / 180));
				i++;
				continue;
			}
			var2 = stack.Pop();
			switch (OperationIndex)
			{
			case 0:
			{
				var1 += var2;
				stack.Push(var1);
				i++;
				break;
			}
			case 1:
			{
				var1 = var2 - var1;
				stack.Push(var1);
				i++;
				break;
			}
			case 2:
			{
				var1 *= var2;
				stack.Push(var1);
				i++;
				break;
			}
			case 3:
			{
				if (var1 == 0)
				{
					cout << "Ошибка: в процессе вычисления происходит деление на 0" << endl;
					return 0;
				}
				var1 = var2 / var1;
				stack.Push(var1);
				i++;
				break;
			}
			case 8:
			{
				var1 = pow(var2, var1);
				stack.Push(var1);
				i++;

				break;
			}
			}
		}
	}
	return stack.Pop();
}

