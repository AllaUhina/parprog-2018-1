// checker.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <cstdio> 
#include <cmath> 
#include <string>

using namespace std;

// Используется для взаимодействия с тестирующей системой //////////////////////////////////////////////////////////////////////////////////////////// 
/* 
// Checker может устанавливать вот эти три вердикта: 
AC = Accepted = Решение выдаёт корректный результат на данном тесте 
WA = Wrong Answer = Решение выдаёт некорректный результат на данном тесте 
PE = Presentation Error = Ошибка формата выходных данных
// Остальные вердикты checker не может устанавливать 
NO = No verdict = Вердикт отсутствует 
CE = Compilation Error = Ошибка компиляции 
ML = Memory Limit Exceeded = Превышено ограничение по памяти 
TL = Time Limit Exceeded = Превышено ограничение по времени работы 
RE = Runtime Error = Ошибка времени исполнения программы 
IL = Idle Limit Exceeded = Превышено время простоя (бездействия) программы 
DE = Deadly Error = Ошибка тестирующей системы */ 


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
		 // Сообщить тестирующей системе, что решение получило один из вердиктов verdict 
		void write_verdict(verdict v) 
		{ 
			write_type(ext_cls::VERDICT); 
			fwrite(&v, sizeof (v), 1, bur); 
		}
		 // Написать сообщение от checker'a пользователю. 
		 // Например, что решение верное, или неверное. 
		 // Использовать только латинские буквы и знаки препинания 
		void write_message(string str) 
		{ 
			write_type(ext_cls::MESSAGE); 
			int l = str.size (); 
			fwrite(&l, sizeof (l), 1, bur); 
			fwrite (&str[0], sizeof (str[0]), l, bur); 
		}
		 // Сообщить тестирующей системе время работы программы участника, 
		 // вычисленное с помощью before_code 
		 // x имеет размерность 100 нс = 10 ^ (-7) сек 
		void write_time(long long x) 
		{ 
			write_type(ext_cls::TIME); 
			fwrite(&x, sizeof (x), 1, bur); 
		}
		 // Сообщить тестирующей системе, память затребованную программой участника 
		void write_memory(unsigned long long x) 
		{ 
			write_type(ext_cls::MEMORY); 
			fwrite(&x, sizeof (x), 1, bur); 
		} 
} checker_result;

int main() 
{ 
	// Открываем файл входных данных, файл выходных данных и ответ участника 
	FILE * inFile;
	fopen_s(&inFile,"C:\\uhina_aa\\1-test-version\\generator\\matr.in", "rb");
	FILE * outFile;
	fopen_s(&outFile,"C:\\uhina_aa\\1-test-version\\solver\\matr.out", "rb");
	FILE * answFile;
	fopen_s(&answFile,"C:\\uhina_aa\\1-test-version\\answer\\answer.txt", "rb");
	
	int n; 
	// Считываем размерность матриц 
	fread(&n, sizeof (n), 1, inFile);
		   
	// Выделяем память для матрицы ответа жюри и ответа участника 
	double * ans = new double[n * n], *res = new double[n * n]; 

	// Считываем полученную матрицу 
	fread(res, sizeof (*res), n * n, outFile);

	// Считываем правильный ответ
	fread(ans, sizeof (*ans), n * n, answFile);

		   // Вычисляем ошибку, как квадрат нормы разности решений 
	double diff = 0.0; 
	for (int i = 0; i < n * n; i++)
	{
		diff += (ans[i] - res[i]) * (ans[i] - res[i]);
	}
		  
	// Проверяем, что ошибка мала, тогда сообщаем, что решение корректно, иначе - некорректно. 
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
