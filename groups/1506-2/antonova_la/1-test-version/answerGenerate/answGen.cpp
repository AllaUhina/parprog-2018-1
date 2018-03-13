#include <string>
#include <fstream>
#include <iostream>

using namespace std;


int main(int argc, char* argv[])
{

			
		ofstream answ_stream("answers/answer_00.answ", ios::out | ios::binary);
		if (answ_stream)
		{
			answ_stream << -1.95199 << endl;
			answ_stream << -15 << endl;
			answ_stream << -27016 << endl;
			answ_stream.close();
		}


		ofstream answ_stream1("answers/answer_01.answ", ios::out | ios::binary);
		if (answ_stream1)
		{
			answ_stream1 << -5 << endl;
			answ_stream1 << -5 << endl;
			answ_stream1 << -15810 << endl;
			answ_stream1.close();
		}

		ofstream answ_stream2("answers/answer_02.answ", ios::out | ios::binary);
		if (answ_stream2)
		{
			answ_stream2 << -20 << endl;
			answ_stream2 << 0.7653 << endl;
			answ_stream2 << -19.989 << endl;
			answ_stream2.close();
		}
		ofstream answ_stream3("answers/answer_03.answ", ios::out | ios::binary);
		if (answ_stream)
		{
			answ_stream3 << -5 << endl;
			answ_stream3 << -5 << endl;
			answ_stream3 << -78 << endl;
			answ_stream3.close();
		}
		ofstream answ_stream4("answers/answer_04.answ", ios::out | ios::binary);
		if (answ_stream)
		{
			answ_stream4 << -1.637 << endl;
			answ_stream4 << -10 << endl;
			answ_stream4 << -8015.5 << endl;
			answ_stream4.close();
		}
		ofstream answ_stream5("answers/answer_05.answ", ios::out | ios::binary);
		if (answ_stream)
		{
			answ_stream5 << -2 << endl;
			answ_stream5 << -15 << endl;
			answ_stream5 << -27016 << endl;
			answ_stream5.close();
		}
	/*Большие тесты*/
		return 0;
}