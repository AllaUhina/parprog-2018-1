// checker.cpp: ���������� ����� ����� ��� ����������� ����������.
//
#include "stdafx.h"
#include <cstdio> 
#include <cmath> 
#include <string>

using namespace std;

// ������������ ��� �������������� � ����������� �������� //////////////////////////////////////////////////////////////////////////////////////////// 
/* 
// Checker ����� ������������� ��� ��� ��� ��������: 
AC = Accepted = ������� ����� ���������� ��������� �� ������ ����� 
WA = Wrong Answer = ������� ����� ������������ ��������� �� ������ ����� 
PE = Presentation Error = ������ ������� �������� ������
// ��������� �������� checker �� ����� ������������� 
NO = No verdict = ������� ����������� 
CE = Compilation Error = ������ ���������� 
ML = Memory Limit Exceeded = ��������� ����������� �� ������ 
TL = Time Limit Exceeded = ��������� ����������� �� ������� ������ 
RE = Runtime Error = ������ ������� ���������� ��������� 
IL = Idle Limit Exceeded = ��������� ����� ������� (�����������) ��������� 
DE = Deadly Error = ������ ����������� ������� */ 


enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };
class result 
{
private: FILE * bur; 
public: enum ext_cls 
{ NO = 1, VERDICT, MESSAGE, TIME, MEMORY }; 
		result(bool read = false) 
		{ 
			if (read) 
				fopen_s(&bur,"result.txt", "r"); 
			else 
				fopen_s(&bur,"result.txt", "w");
		} 
		~result() 
		{ 
			fclose(bur); 
		} 
		void write_type(ext_cls t) 
		{ 
			fwrite(&t, sizeof(t), 1, bur); 
		}
		 // �������� ����������� �������, ��� ������� �������� ���� �� ��������� verdict 
		void write_verdict(verdict v) 
		{ 
			write_type(ext_cls::VERDICT); 
			fwrite(&v, sizeof (v), 1, bur); 
		}
		 // �������� ��������� �� checker'a ������������. 
		 // ��������, ��� ������� ������, ��� ��������. 
		 // ������������ ������ ��������� ����� � ����� ���������� 
		void write_message(string str) 
		{ 
			write_type(ext_cls::MESSAGE); 
			int l = str.size (); 
			fwrite(&l, sizeof (l), 1, bur); 
			fwrite (&str[0], sizeof (str[0]), l, bur); 
		}
		 // �������� ����������� ������� ����� ������ ��������� ���������, 
		 // ����������� � ������� before_code 
		 // x ����� ����������� 100 �� = 10 ^ (-7) ��� 
		void write_time(long long x) 
		{ 
			write_type(ext_cls::TIME); 
			fwrite(&x, sizeof (x), 1, bur); 
		}
		 // �������� ����������� �������, ������ ������������� ���������� ��������� 
		void write_memory(unsigned long long x) 
		{ 
			write_type(ext_cls::MEMORY); 
			fwrite(&x, sizeof (x), 1, bur); 
		} 
} checker_result;

int main() 
{ 
	// ��������� ���� ������� ������, ���� �������� ������ � ����� ��������� 
	FILE * inFile;
	fopen_s(&inFile,"C:\\uhina_aa\\1-test-version\\generator\\matr.in", "rb");
	FILE * outFile;
	fopen_s(&outFile,"C:\\uhina_aa\\1-test-version\\solver\\matr.out", "rb");
	FILE * answFile;
	fopen_s(&answFile,"C:\\uhina_aa\\1-test-version\\answer\\answer.txt", "rb");
	
	int n; 
	// ��������� ����������� ������ 
	fread(&n, sizeof (n), 1, inFile);
		   
	// �������� ������ ��� ������� ������ ���� � ������ ��������� 
	double * ans = new double[n * n], *res = new double[n * n]; 

	// ��������� ���������� ������� 
	fread(res, sizeof (*res), n * n, outFile);

	// ��������� ���������� �����
	fread(ans, sizeof (*ans), n * n, answFile);

		   // ��������� ������, ��� ������� ����� �������� ������� 
	double diff = 0.0; 
	for (int i = 0; i < n * n; i++)
	{
		diff += (ans[i] - res[i]) * (ans[i] - res[i]);
	}
		  
	// ���������, ��� ������ ����, ����� ��������, ��� ������� ���������, ����� - �����������. 
	if (diff < 1e-6) 
	{ 
		checker_result.write_message ("AC. Numbers are equal."); 
		checker_result.write_verdict (verdict::AC); 
	}
	else 
	{ 
		checker_result.write_message ("WA. Output is not correct."); 
		checker_result.write_verdict (verdict::WA); 
	}

	fclose(answFile); 
	fclose(outFile);
	return 0;
}
