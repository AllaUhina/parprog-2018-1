#include <string>
#include <fstream>
#include <iostream>

using namespace std;


	int main(int argc, char* argv[])
	{
		string function;
		double left_border, right_border;
		string path_to_test = argv[1];
		int path_test_length = sizeof(path_to_test) / sizeof(char);
		int testInd;
		for (int ind = 0; ind < path_test_length; ++ind)
		{
			if (path_to_test[ind] == '_')
			{
				testInd = ind + 1;
				break;
			}
		}
		string c;
		int num=0;
		if (path_to_test[testInd] == '0') c[0] = path_to_test[testInd + 1];
		else {
			c[0] = path_to_test[testInd];
			c[1]= path_to_test[testInd+1];
		}
		num = atof(c.c_str());
		/*for (int num = 0; num < 10; num++)
		{*/
			if (num == 0)
			{
				function = "4*x^2+8*y^3+16*x";
				left_border = -15;
				right_border = 15;
				ofstream test_stream("tests/test_00.tst", ios::out | ios::binary);
				if (test_stream) {
					test_stream << function << endl;
					test_stream << left_border << endl;
					test_stream << right_border << endl;
					test_stream.close();
					return num;
				}
				else return 404;
			}


			if (num == 1)
			{
				function = "x^3-y^6+2*x*y-10";
				left_border = -5;
				right_border = 5;
				ofstream test_stream("tests/test_01.tst", ios::out | ios::binary);
				if (test_stream) {
					test_stream << function << endl;
					test_stream << left_border << endl;
					test_stream << right_border << endl;
					test_stream.close();
					return num;
				}
				else return 404;
			}

			if (num == 2)
			{
				function = "cos(4*y-1)*x";
				left_border = -20;
				right_border = 20;
				ofstream test_stream("tests/test_02.tst", ios::out | ios::binary);
				if (test_stream) {
					test_stream << function << endl;
					test_stream << left_border << endl;
					test_stream << right_border << endl;
					test_stream.close();
					return num;
				}
				else return 404;
			}

			if (num == 3)
			{
				function = "cos(0.1*y)+12*x-x^2+6";
				left_border = -5;
				right_border = 5;
				ofstream test_stream("tests/test_03.tst", ios::out | ios::binary);
				if (test_stream) {
					test_stream << function << endl;
					test_stream << left_border << endl;
					test_stream << right_border << endl;
					test_stream.close();
					return num;
				}
				else return 404;
			}


			if (num == 4)
			{
				function = "4*x^2+8*y^3+16*x";
				left_border = -10;
				right_border = 10;
				ofstream test_stream("tests/test_04.tst", ios::out | ios::binary);
				if (test_stream) {
					test_stream << function << endl;
					test_stream << left_border << endl;
					test_stream << right_border << endl;
					test_stream.close();
					return num;
				}
				else return 404;
			}

			/*Большие тесты*/
			if (num == 5)
			{
				function = "(x+2*y-7)^2+(2*x+y-5)^2";
				left_border = -1000;
				right_border = 1000;
				ofstream test_stream("tests/test_05.tst", ios::out | ios::binary);
				if (test_stream) {
					test_stream << function << endl;
					test_stream << left_border << endl;
					test_stream << right_border << endl;
					test_stream.close();
					return num;
				}
				else return 404;
			}

			if (num == 6)
			{
				function = "six(x+y)+(x-y)^2-1.5*x+2.5*y+1";
				left_border = -1000;
				right_border = 1000;
				ofstream test_stream2("tests/test_06.tst", ios::out | ios::binary);
				if (test_stream2) {
					test_stream2 << function << endl;
					test_stream2 << left_border << endl;
					test_stream2 << right_border << endl;
					test_stream2.close();
					return num;
				}
				else return 404;
			}
			if (num == 7)
			{
				function = "100*(y-x^2)^2+(1-x^2)";
				left_border = -1000;
				right_border = 1000;
				ofstream test_stream2("tests/test_07.tst", ios::out | ios::binary);
				if (test_stream2) {
					test_stream2 << function << endl;
					test_stream2 << left_border << endl;
					test_stream2 << right_border << endl;
					test_stream2.close();
					return num;
				}
				else return 404;
			}
			if (num == 8)
			{
				function = "100*(y-x^3)^2-(1-x)^2";
				left_border = -1000;
				right_border = 1000;
				ofstream test_stream2("tests/test_08.tst", ios::out | ios::binary);
				if (test_stream2) {
					test_stream2 << function << endl;
					test_stream2 << left_border << endl;
					test_stream2 << right_border << endl;
					test_stream2.close();
					return num;
				}
				else return 404;
			}
			if (num == 9)
			{
				function = "2*x^2-1.05*x^4+(x^6)/6+x*y+y^2";
				left_border = -1000;
				right_border = 1000;
				ofstream test_stream2("tests/test_09.tst", ios::out | ios::binary);
				if (test_stream2) {
					test_stream2 << function << endl;
					test_stream2 << left_border << endl;
					test_stream2 << right_border << endl;
					test_stream2.close();
					return num;
				}
				else return 404;
			}
		/*}*/


		return 100;
}	