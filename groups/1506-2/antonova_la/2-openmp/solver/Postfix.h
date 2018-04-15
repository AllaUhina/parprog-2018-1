#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <iostream>

using namespace std;

#define MaxSizeString 1000


class TPostfix
{
	string infix;
	string postfix;
	string operation[9];
	char priority[9];

public:
	TPostfix() //����������� �� ��������
	{
		infix = "a+b";
		postfix = "Not exist";
		operation[0] = "+"; priority[0] = 1;
		operation[1] = "-"; priority[1] = 1;
		operation[2] = "*"; priority[2] = 2;
		operation[3] = "/"; priority[3] = 2;
		operation[4] = "sin"; priority[4] = 3;
		operation[5] = "cos"; priority[5] = 3;
		operation[6] = "("; priority[6] = 0;
		operation[7] = ")"; priority[7] = 0;
		operation[8] = "^"; priority[8] = 3;

	}

	int IsOperation(string &str, int &i); //�������� ��������
	int GetPriority(string &str); //�������� ��������� ��������
	void PutInfix(string &inf) { infix = inf; };
	//bool CheckInfix() { return (CheckChars() && CheckOperations()); }; //����� �������� 
	//bool CheckChars(); //�������� ��������� ��������
	//bool CheckOperations(); //�������� ��������
	void ToPostfix(); //������� ������ � ����������� �����
	double Calculate(double x, double y); //  ���������� �� ����������� �����
	string GetInfix() { return infix; } //������ � ��������� ������
	string GetPostfix() { return postfix; } //������ � ����������� ������

};

#endif
#pragma once
