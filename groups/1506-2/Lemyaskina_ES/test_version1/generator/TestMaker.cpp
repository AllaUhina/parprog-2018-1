#define PI 3.1415926535
#define e 2.719 

#include <fstream>
#include <string.h>
#include <time.h>


using namespace std;

int main(int argc, char*argv[])
{


	srand(time(0));
	int numOfTest = rand() % 10 + 1;
		char* funct;
		double left, right;
		double answer;
		if (numOfTest == 1)
		{
			//Test 1
			funct = "ln(x)";
			left = 1;
			right = e;
			answer = 1;
			ofstream stream("../test/task/1.in",  ios::out|ios::binary);
			if (stream) {
				stream << funct << endl;
				stream << left << endl;
				stream << right << endl;
				stream.close();
			}
			else return -1;

			ofstream streamA("../test/answer/1.ans",  ios::out|ios::binary);
			if (streamA) {
				streamA << answer << endl;
				streamA.close();
			}
			else return -1;

		}
		else if (numOfTest == 2)
		{
			//Test 2
			funct = "x^5";
			left = 0;
			right = 12;
			answer = 497664;
			ofstream stream("../test/task/2.in",  ios::out|ios::binary);
			if (stream) {
				stream << funct << endl;
				stream << left << endl;
				stream << right << endl;
				stream.close();
			}
			else return -1;

			ofstream streamA("../test/answer/2.ans",  ios::out|ios::binary);
			if (streamA) {
				streamA << answer << endl;
				streamA.close();
			}
			else return -1;
		}
		else if (numOfTest == 3)
		{
			//Test 3
			funct = "5-x";
			left = -5;
			right = 5;
			answer = 50;
			ofstream stream("../test/task/3.in",  ios::out|ios::binary);
			if (stream) {
				stream << funct <<endl;
				stream << left << endl;
				stream << right << endl;
				stream.close();
			}
			else return -1;

			ofstream streamA("../test/answer/3.ans",  ios::out|ios::binary);
			if (streamA) {
				streamA << answer << endl;
				streamA.close();
			}
			else return -1;
		}
		else if (numOfTest == 4)
		{
			//Test 4
			funct = "10-sqrt(x)";
			left = -11;
			right = 7;
			answer = 50;
			ofstream stream("../test/task/4.in",  ios::out|ios::binary);
			if (stream) {
				stream << funct << endl;
				stream << left << endl;
				stream << right << endl;
				stream.close();
			}
			else return -1;

			ofstream streamA("../test/answer/4.ans",  ios::out|ios::binary);
			if (streamA) {
				streamA << answer << endl;
				streamA.close();
			}
			else return -1;

		}
		else if (numOfTest == 5)
		{
			//Test 5
			funct = "sin(x)";
			left = 0;
			right = PI / 2;
			answer = 1;
			ofstream stream("../test/task/5.in",  ios::out|ios::binary);
			if (stream) {
				stream << funct << endl;
				stream << left << endl;
				stream << right << endl;
				stream.close();
			}
			else return -1;

			ofstream streamA("../test/answer/5.ans",  ios::out|ios::binary);
			if (streamA) {
				streamA << answer << endl;
				streamA.close();
			}
			else return -1;

		}
		else if (numOfTest == 6)
		{
			//Test 6
			funct = "cos(x)-sin(x)";
			left = 0;
			right = PI;
			answer = -2;
			ofstream stream("../test/task/6.in",  ios::out|ios::binary);
			if (stream) {
				stream << funct << endl;
				stream << left << endl;
				stream << right << endl;
				stream.close();
			}
			else return -1;

			ofstream streamA("../test/answer/6.ans",  ios::out|ios::binary);
			if (streamA) {
				streamA << answer << endl;
				streamA.close();
			}
			else return -1;

		}
		else if (numOfTest == 7)
		{
			//Test 7
			funct = "tg(x)/2";
			left = 0;
			right = PI / 3;
			answer = 0.69315;
			ofstream stream("../test/task/7.in",  ios::out|ios::binary);
			if (stream) {
				stream << funct << endl;
				stream << left << endl;
				stream << right << endl;
				stream.close();
			}
			else return -1;

			ofstream streamA("../test/answer/7.ans",  ios::out|ios::binary);
			if (streamA) {
				streamA << answer << endl;
				streamA.close();
			}
			else return -1;

		}
		else if (numOfTest == 8)
		{
			//Test 8
			funct = "x+1";
			left = 0;
			right = 7;
			answer = 31.5;
			ofstream stream("../test/task/8.in",  ios::out|ios::binary);
			if (stream) {
				stream << funct << endl;
				stream << left << endl;
				stream << right << endl;
				stream.close();
			}
			else return -1;

			ofstream streamA("../test/answer/8.ans",  ios::out|ios::binary);
			if (streamA) {
				streamA << answer << endl;
				streamA.close();
			}
			else return -1;

		}
		else if (numOfTest == 9)
		{
			//Test 9
			funct = "x^7-2*x^6+x^5-6*x^4+11*x^3-34*x^2+2*x-1";
			left = 0;
			right = 10;
			answer = (-1)*(2694 / 35);
			ofstream stream("../test/task/9.in",  ios::out|ios::binary);
			if (stream) {
				stream << funct << endl;
				stream << left << endl;
				stream << right << endl;
				stream.close();
			}
			else return -1;

			ofstream streamA("../test/answer/9.ans",  ios::out|ios::binary);
			if (streamA) {
				streamA << answer << endl;
				streamA.close();
			}
			else return -1;

		}
		else if (numOfTest == 10)
		{
			//Test 10
			funct = "2*x-4x^2";
			left = -8;
			right = 43;
			answer = -104907;
			ofstream stream("../test/task/10.in",  ios::out|ios::binary);
			if (stream) {
				stream << funct << endl;
				stream << left << endl;
				stream << right << endl;
				stream.close();
			}
			else return -1;

			ofstream streamA("../test/answer/10.ans",  ios::out|ios::binary);
			if (streamA) {
				streamA << answer << endl;
				streamA.close();
			}
			else return -1;

		}
	
	return numOfTest;
}