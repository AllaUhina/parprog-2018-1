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

//bool TPostfix::CheckChars()
//{
//	char now;
//	for (int i = 0; i < infix.size(); i++)
//	{
//		now = infix[i];
//		if (!((now > 39 && now < 58) || now == 's' || now == 'c' || now == '^'||now=='x'||now=='y'))
//		{
//			cout << "Введён недопустимый символ" << endl;
//			return false;
//		}
//		if (now == 'c' || now == 's')
//		{
//			if (infix.substr(i, 3) == "cos" || infix.substr(i, 3) == "sin")
//				i += 2;
//			else
//			{
//				cout << "Введена недопустимая функция" << endl;
//				return false;
//			}
//		}
//		if (now == 46)
//			infix[i] = ',';
//	}
//	return true;
//}
//
//bool TPostfix::CheckOperations()
//{
//	string inf = infix, str = " ";
//	int opIndex1, opIndex2;
//	int size = infix.size();
//	int i, j, p, q, count = 0, check = 0;
//
//	opIndex1 = IsOperation(inf, i = 0);
//	if (opIndex1 > -1 && opIndex1 < 4 || opIndex1 == 8 || opIndex1 == 7) return false;
//	for (int i = 0; i < size; i++)
//	{
//		opIndex1 = IsOperation(inf, i);
//		if (opIndex1 != -1)
//		{
//			opIndex2 = IsOperation(inf, j = i + 1);
//			if (opIndex1 < 4)
//			{
//				if (opIndex2>-1 && opIndex2 < 4 || opIndex2>6)
//				{
//					cout << "После операции не может быть операции или закрывающей скобки" << endl;
//					return false;
//				}
//				if (opIndex2 > -1 && opIndex2 < 4 && opIndex2 != 6 || inf[i + 1] == 0)
//				{
//					cout << "Отсутствует операнд после операции" << endl;
//					return false;
//				}
//				continue;
//			}
//			if (opIndex1 == 4)
//			{
//				i += 2;
//				if (inf[i + 1] != '(')
//				{
//					cout << "Отсутсвует параметр функции sin" << endl;
//					return false;
//				}
//				continue;
//			}
//			if (opIndex1 == 5)
//			{
//				i += 2;
//				if (inf[i + 1] != '(')
//				{
//
//					cout << "Отсутсвует параметр функции cos " << endl;
//					return false;
//				}
//				continue;
//			}
//			if (opIndex1 == 6)
//			{
//				if (opIndex2>-1 && opIndex2<4 || opIndex2 == 7 || opIndex2 == 8)
//				{
//
//					cout << "После открывающей скобки не может быть операции " << endl;
//					return false;
//				}
//				count++;
//				continue;
//			}
//			if (opIndex1 == 7)
//			{
//				if (opIndex2 > -1 && opIndex2 < 4 || opIndex2 >5 && opIndex2<9)
//				{
//					count--;
//					continue;
//				}
//				if (inf[i + 1] == NULL)
//				{
//					count--;
//					continue;
//				}
//				cout << "После закрывающей скобки  не должно быть операнда, открывающей скобки или функций" << endl;
//				return false;
//			}
//			if (opIndex1 == 8)
//			{
//				if (opIndex2 == 8)
//				{
//					cout << "После '^' не может ^" << endl;
//					return false;
//				}
//				continue;
//			}
//		}
//		else
//		{
//			p = 0;
//			q = i;
//			do
//			{
//				p++;
//				q++;
//				opIndex1 = IsOperation(inf, q);
//				if (q == size)
//					break;
//			} while (opIndex1 == -1);
//			str = inf.substr(i, p);
//			check = 0;
//			for (int p = 0; p < str.size(); p++)
//			{
//				if (str[p] == ',')
//				{
//					check++;
//					continue;
//				}
//				if (check > 1)
//				{
//					cout << "Неправильная запись операнда" << endl;
//					return false;
//				}
//			}
//			i = i + p - 1;
//			if (IsOperation(inf, q = i + 1) == 6)
//			{
//				cout << "После операнда не может быть открывающей скобки" << endl;
//				return false;
//			}
//		}
//	}
//	if (count != 0)
//	{
//		cout << "Присутствуют лишние скобки" << endl;
//		return false;
//	}
//	return true;
//}

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
				stack.Push(sin((var1*3.14159265) / 180));
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

