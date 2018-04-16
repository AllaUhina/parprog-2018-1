#include <string>
#include <fstream>
#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{

		//4*x^2+8*y^3+16*x
		ofstream answ_stream("answers/answer_00.answ", ios::out | ios::binary);
		if (answ_stream)
		{
			answ_stream << -1.95199 << endl;
			answ_stream << -15 << endl;
			answ_stream << -27016 << endl;
			answ_stream.close();
		}

		//x^3-y^6+2*x*y-10
		ofstream answ_stream1("answers/answer_01.answ", ios::out | ios::binary);
		if (answ_stream1)
		{
			answ_stream1 << -5 << endl;
			answ_stream1 << -5 << endl;
			answ_stream1 << -15810 << endl;
			answ_stream1.close();
		}

		//cos(4*y-1)*x
		ofstream answ_stream2("answers/answer_02.answ", ios::out | ios::binary);
		if (answ_stream2)
		{
			answ_stream2 << -20 << endl;
			answ_stream2 << 0.7653 << endl;
			answ_stream2 << -19.989 << endl;
			answ_stream2.close();
		}

		//cos(0.1*y)+12*x-x^2+6
		ofstream answ_stream3("answers/answer_03.answ", ios::out | ios::binary);
		if (answ_stream)
		{
			answ_stream3 << -5 << endl;
			answ_stream3 << -5 << endl;
			answ_stream3 << -78 << endl;
			answ_stream3.close();
		}

		//4*x^2+8*y^3+16*x
		ofstream answ_stream4("answers/answer_04.answ", ios::out | ios::binary);
		if (answ_stream)
		{
			answ_stream4 << -1.637 << endl;
			answ_stream4 << -10 << endl;
			answ_stream4 << -8015.5 << endl;
			answ_stream4.close();
		}
		
		
		//Большие тесты

		//(x+2*y-7)^2 + (2*x+y-5)^2
		ofstream answ_stream5("answers/answer_05.answ", ios::out | ios::binary);
		if (answ_stream5)
		{
			answ_stream5 << 1<< endl;
			answ_stream5 << 3 << endl;
			answ_stream5 << 0 << endl;
			answ_stream5.close();
		}
		
		//six(x + y) + (x - y) ^ 2 - 1.5*x + 2.5*y + 1
		ofstream answ_stream6("answers/answer_06.answ", ios::out | ios::binary);
		if (answ_stream6)
		{
			answ_stream6 << -0.54719 << endl;
			answ_stream6 << -1.54719 << endl;
			answ_stream6 << -1.9133 << endl;
			answ_stream6.close();
		}

		//100 * (y - x ^ 2) ^ 2 + (1 - x ^ 2)
		ofstream answ_stream7("answers/answer_07.answ", ios::out | ios::binary);
		if (answ_stream7)
		{
			answ_stream7 << 1 << endl;
			answ_stream7 << 1 << endl;
			answ_stream7 << 0 << endl;
			answ_stream7.close();
		}

		//100 * (y - x ^ 3) ^ 2 - (1 - x) ^ 2
		ofstream answ_stream8("answers/answer_08.answ", ios::out | ios::binary);
		if (answ_stream8)
		{
			answ_stream8 << 1<< endl;
			answ_stream8 << 1 << endl;
			answ_stream8 << 0 << endl;
			answ_stream8.close();
		}

		//2 * x ^ 2 - 1.05*x ^ 4 + (x ^ 6) / 6 + x*y + y ^ 2
		ofstream answ_stream9("answers/answer_09.answ", ios::out | ios::binary);
		if (answ_stream9)
		{
			answ_stream9 << 0 << endl;
			answ_stream9 << 0 << endl;
			answ_stream9 << 0 << endl;
			answ_stream9.close();
		}
		return 0;
}