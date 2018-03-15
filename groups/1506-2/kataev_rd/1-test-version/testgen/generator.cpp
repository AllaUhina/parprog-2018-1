#include <iostream>
#include <fstream>
#include <random>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	std::random_device rand;
	std::default_random_engine generator(rand());
	std::uniform_real_distribution<float> distribution(1, 1.9);

	for (int i = 0; i < 10; i++)
	{
		float sigma = 0;
		string pictureFileName, testFileName;
		pictureFileName = to_string(i) + ".jpg";
		testFileName = "../../Tests/test" + to_string(i) + ".bin";
		sigma = distribution(generator);

		ofstream testFile;
		testFile.open(testFileName, ios::out | ios::app | ios::binary);
		testFile << pictureFileName << endl << sigma;
		testFile.close();
	}
	return 0;
}