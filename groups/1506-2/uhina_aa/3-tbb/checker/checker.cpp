// checker.cpp: ���������� ����� ����� ��� ����������� ����������.
//
#include "stdafx.h"
#include <cstdio> 
#include <cmath> 
#include <string>

using namespace std;
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
DE = Deadly Error = ������ ����������� ������� 
*/

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
		 // To inform the testing system that the decision has received one verdict
		void write_verdict(verdict v) 
		{ 
			write_type(ext_cls::VERDICT); 
			fwrite(&v, sizeof (v), 1, bur); 
		}
		 // Write messege from checker
		 // Use only latin simbols
		void write_message(string str) 
		{ 
			write_type(ext_cls::MESSAGE); 
			int l = str.size (); 
			fwrite(&l, sizeof (l), 1, bur); 
			fwrite (&str[0], sizeof (str[0]), l, bur); 
		}
		 //Write time
		void write_time(char* str, long long x)
		{
			write_type(ext_cls::TIME);
			fprintf(bur, "\nTime(%s)= %d", str, x);
		}
		 //Write speedup
		void write_speedup(double x)
		{
			write_type(ext_cls::TIME);
			fprintf(bur, "\nAcceleration= %.3f", x);
		}
} checker_result;

int main() 
{ 
	FILE * inFile;
	fopen_s(&inFile,"..\\tests\\1", "rb");
	FILE * outFile;
	fopen_s(&outFile,"..\\solver\\matr.out", "rb");
	FILE * answFile;
	fopen_s(&answFile,"..\\answer\\1.ans", "rb");
	
	int n;
	fread(&n, sizeof (n), 1, inFile);
		   
	//Correct answer and result of solver
	double * ans = new double[n * n], *res = new double[n * n]; 
	double ans_time, res_time;

	//Time and result of solver
	fread(&res_time, sizeof(res_time), 1, outFile);
	fread(res, sizeof (*res), n * n, outFile);

	//Time and correct answer
	fread(&ans_time, sizeof(ans_time), 1, answFile);
	fread(ans, sizeof (*ans), n * n, answFile);

	//Calculate a error
	double diff = 0.0; 
	for (int i = 0; i < n * n; i++)
	{
		diff += (ans[i] - res[i]) * (ans[i] - res[i]);
	}
		  
	//Check a error
	if (diff < 1e-6) 
	{ 
		checker_result.write_message ("AC(Accepted). Numbers are equal."); 
		checker_result.write_verdict (verdict::AC); 
	}
	else 
	{ 
		checker_result.write_message ("WA(Wrong Answer). Output is not correct."); 
		checker_result.write_verdict (verdict::WA); 
	}
	
	//Write time
	checker_result.write_time("Parallel", res_time * 1e7);
	checker_result.write_time("Serial", ans_time * 1e7);
	//Write speedup
	if (res_time<ans_time)
	{
		double speedup = ans_time / res_time;
		checker_result.write_speedup(speedup);
	}

	fclose(answFile); 
	fclose(outFile);
	return 0;
}
