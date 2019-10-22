#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <vector>
#include "stack.h"
#include <math.h>
#include <iostream>

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	vector<string> OpTable; //вектор переменных

							
	bool IsNumber(string &str);   //проверка является ли операнд числом
	bool IsCorrect(string &str);  //проверка на корректность строки
	void ToOpTable(string &str);
	void ToStack(TStack<string> &stack, string &str); //работа со стеком операций
	void ToPostfix();
	int TheTable(const string &str, int IsNeed); //таблица операций, их приоритетов, количество операндов
public:
	TPostfix() { infix = "String is empty"; };
	TPostfix& operator=(string &str);
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	double Calculate(double point); // Ввод переменных, вычисление по постфиксной форме
};

#endif