#include "postfix.h"
#include "stack.h"

const int OPER_IN_ALL = 13; //всего операций
const int PROH_ALL = 25; //всего проверок

bool TPostfix::IsCorrect(string &str)
{
	if (!(str[0] == 40 || str[0] == 41 || 65 <= str[0] <= 90 || 97 <= str[0] <= 122)) // '(' ')' 'A'-'Z' 'a'-'z' 
		return 0;
	int a = (str.length() - 1);
	if (!(str[a] == 40 || str[a] == 41 || 65 <= str[a] <= 90 || 97 <= str[a] <= 122))
		return 0;
	int left = 0;
	int right = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
			left++;
		if (str[i] == ')')
			right++;
	}
	if (left != right)
		return 0;
	string proh[PROH_ALL];
	proh[0] = "(+";
	proh[1] = "(-";
	proh[2] = "(*";
	proh[3] = "(/";
	proh[4] = "()";
	proh[5] = "++";
	proh[6] = "+-";
	proh[7] = "+*";
	proh[8] = "+/";
	proh[9] = "+)";
	proh[10] = "-+";
	proh[11] = "--";
	proh[12] = "-*";
	proh[13] = "-/";
	proh[14] = "-)";
	proh[15] = "*+";
	proh[16] = "*-";
	proh[17] = "**";
	proh[18] = "*/";
	proh[19] = "*)";
	proh[20] = "/+";
	proh[21] = "/-";
	proh[22] = "/*";
	proh[23] = "//";
	proh[24] = "/)";
	for (int i = 0; i < PROH_ALL; i++)
		if (str.find(proh[i]) != -1)
			return 0;
	return 1;
}

bool TPostfix::IsNumber(string &str)
{
	int dots = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '.')
			dots++;
		if (!(str[i] >= '.' && str[i] <= '9'))
			return 0;
	}
	if (dots > 1)
		return 0;
	return 1;
}

int TPostfix::TheTable(const string &str, int IsNeed) {
	/* Таблица операций
	IsNeed =	0 - является ли переменной, 1 - приоритет	*/
	if (str == "")
		return 0;

	string TOperations[OPER_IN_ALL]; //операции
	TOperations[0] = '+';
	TOperations[1] = '-';
	TOperations[2] = '*';
	TOperations[3] = '/';
	TOperations[4] = '(';
	TOperations[5] = ')';
	TOperations[6] = "sin";
	TOperations[7] = "cos";
	TOperations[8] = "tg";
	TOperations[9] = "ctg";
	TOperations[10] = "sqrt";
	TOperations[11] = "ln";
	TOperations[12] = "^";

	int TPriority[OPER_IN_ALL];		//приоритет
	TPriority[0] = 1;
	TPriority[1] = 1;
	TPriority[2] = 2;
	TPriority[3] = 2;
	TPriority[4] = 0;
	TPriority[5] = -1;
	TPriority[6] = 3;
	TPriority[7] = 3;
	TPriority[8] = 3;
	TPriority[9] = 3;
	TPriority[10] = 3;
	TPriority[11] = 3;
	TPriority[12] = 3;

	switch (IsNeed)
	{
	case 0:
		for (int i = 0; i < OPER_IN_ALL; i++)
			if (str.compare(TOperations[i]) == 0)
				return 1;
		return 0;
		break;
	case 1:
		for (int i = 0; i < OPER_IN_ALL; i++)
			if (str.compare(TOperations[i]) == 0)
				return TPriority[i];
		return -1;			
		break;
	default:
		throw("Invalid second variable in the function TheTable"); 
		break;
	}
}

TPostfix& TPostfix::operator=(string &str) {
	if (!IsCorrect(str))
		throw("String is not correct");

	infix = str;
	ToPostfix();
}

void TPostfix::ToOpTable(string &str)
{
	for (int i = 0; i < OpTable.size(); i++)
		if (OpTable[i].compare(str) == 0)
			return;
	OpTable.push_back(str);
}

void TPostfix::ToStack(TStack<string> &stack, string &str) //стек операций
{
	if (str[0] == '(')
	{
		stack.PutIn(str);
		return;
	}
	if (stack.IsEmpty() == 1)
	{
		stack.PutIn(str);
		return;
	}
	string LastOp = stack.GetValue();
	if (TheTable(str, 1) <= TheTable(LastOp, 1))
	{
		while (TheTable(str, 1) <= TheTable(LastOp, 1))
		{
			if (LastOp[0] == '(')
				return;
			postfix = postfix + LastOp + " ";
			stack.PutOut();
			if (!stack.IsEmpty())
				LastOp = stack.GetValue();
			else
			{
				break;
			}
		}
		stack.PutIn(str);
	}
	else
	{
		stack.PutIn(str);
		return;
	}
}

void TPostfix::ToPostfix()
{
	TStack<string> stack;
	string str, tmp;
	for (int i = 0; i < infix.length(); i++)
	{
		tmp = infix[i];
		if (TheTable(str, 0) == 1)
		{
			ToStack(stack, str);
			str.clear();
		}
		if (TheTable(tmp, 0) == 1)
		{
			if (str.length() != 0)
			{
				ToOpTable(str);
				postfix = postfix + str + " ";
				str.clear();
			}
			ToStack(stack, tmp);
		}
		else
			str = str + tmp;
		tmp.clear();
	}
	if (str.length() != 0)
	{
		if (TheTable(str, 0) == 1)
			throw("Invalid string");
		else
		{
			ToOpTable(str);
			postfix = postfix + str + " ";
		}
	}
	while (!stack.IsEmpty())
	{
		if (stack.GetValue()[0] == '(')
		{
			stack.PutOut();
			continue;
		}
		postfix = postfix + stack.PutOut() + " ";
	}
}

double TPostfix::Calculate(double point)
{
	double* OpValue = new double[OpTable.size()];
	
	setlocale(LC_ALL, "C");
	for (int i = 0; i < OpTable.size(); i++)
	{
		if (IsNumber(OpTable[i]))
		{
			
			OpValue[i] = stod(OpTable[i]);
		}
		else
		{
			OpValue[i] = point;
		}
	}
	setlocale(LC_ALL, "Russian");
	string str;
	TStack<double> calc;
	for (int i = 0; i < postfix.length() - 1; i++)
	{
		str.clear();
		while (postfix[i] != ' ')
			str = str + postfix[i++];
		if (!TheTable(str, 0))
		{
			for (int j = 0; j < OpTable.size(); j++)
				if (OpTable[j] == str)
				{
					calc.PutIn(OpValue[j]);
					break;
				}
		}
		else
		{
			if (calc.IsEmpty())
				throw("String is not correct");
			if (str == "+")
			{
				calc.PutIn(calc.PutOut() + calc.PutOut());
				continue;
			}
			if (str == "-")
			{
				double right = calc.PutOut();
				double left = calc.PutOut();
				calc.PutIn(left - right);
				continue;
			}
			if (str == "*")
			{
				calc.PutIn(calc.PutOut() * calc.PutOut());
				continue;
			}
			if (str == "/")
			{
				double right = calc.PutOut();
				double left = calc.PutOut();
				calc.PutIn(left / right);
				continue;
			}
			if (str == "sin")
			{
				calc.PutIn(sin(calc.PutOut()));
				continue;
			}
			if (str == "cos")
			{
				calc.PutIn(cos(calc.PutOut()));
				continue;
			}
			if (str == "tg")
			{
				calc.PutIn(sin(calc.GetValue()) / cos(calc.PutOut()));
				continue;
			}
			if (str == "ctg")
			{
				calc.PutIn(cos(calc.GetValue()) / sin(calc.PutOut()));
				continue;
			}
			if (str == "sqrt")
			{
				calc.PutIn(sqrt(calc.PutOut()));
				continue;
			}
			if (str == "ln")
			{
				calc.PutIn(log(calc.PutOut()));
				continue;
			}
			if (str == "^")
			{
				double st = calc.PutOut();
				double x = calc.PutOut();
				calc.PutIn(pow(x,st));
				continue;
			}
		}
	}
	delete[] OpValue;
	double res = calc.PutOut();
	if (!calc.IsEmpty())
		throw("String is not correct");
	return res;
}