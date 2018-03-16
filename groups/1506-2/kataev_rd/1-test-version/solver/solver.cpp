#define _USE_MATH_DEFINES
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace cv;
using namespace std;

//функция для проверки невыхода за определенные границы (наиболее актуальна для значений пикселей)
int control(int in, int a, int b)
{
	if (in < a)
		return a;
	if (in > b)
		return b;
	else return in;
}

int main(int argc, char *argv[])
{	

	int size = 3;
	int radius = size / 2;
	float sigma = 0;
	double sum = 0;
	string testName, picPathRaw, fileName, picName;

	//загрузка изображения и создание выходного
	string outputPathCustom = "../../CustomResults/";
	picPathRaw = "../../SourceImgs/";

	string tstStr = string(argv[1]);

	testName = "../../Tests/" + tstStr;
	ifstream testFile;
	testFile.open(testName, ios::in | ios::binary);

	testFile >> picName;
	cout << picName << endl;
	testFile >> sigma;
	cout << sigma << endl;

	fileName = outputPathCustom + picName;

	Mat inFile;
	inFile = imread(picPathRaw + picName, CV_LOAD_IMAGE_COLOR);
	Mat outFile(inFile.size(), CV_8UC3);
	
	//создание, заполнение и нормировка ядра
	double **gaussCore = new double*[size];
	for (int i = 0; i < size; i++)
		gaussCore[i] = new double[size];

	for (int i = -radius; i <= radius; i++)
	{
		for (int j = -radius; j <= radius; j++)
		{
			gaussCore[i + radius][j + radius] = exp(-(i*i+j*j) / (sigma * sigma));
			sum += gaussCore[i + radius][j + radius];
		}
		
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			gaussCore[i][j] /= sum;
		}
	}

	//применение фильтра
	double blue = 0, green = 0, red = 0;
	int currX = 0, currY = 0;

	for (int i = 0; i < inFile.rows; i++)
	{
		for (int j = 0; j < inFile.cols; j++)
		{
			blue = 0;
			green = 0;
			red = 0;
			for (int t = -radius; t <= radius; t++)
			{
				for (int k = -radius; k <= radius; k++)
				{
					currX = control(i + t, 0, inFile.rows - 1);
					currY = control(j + k, 0, inFile.cols - 1);
					Vec3b neighborCol = inFile.at<Vec3b>(currX, currY);
					blue += neighborCol.val[0] * gaussCore[t + radius][k + radius];
					green += neighborCol.val[1] * gaussCore[t + radius][k + radius];
					red += neighborCol.val[2] * gaussCore[t + radius][k + radius];
				}
			}
			Vec3b col(control(blue, 0, 255), control(green, 0, 255), control(red, 0, 255));
			outFile.at<Vec3b>(i, j) = col;
		}
	}

	imwrite(fileName, outFile);

	for (int i = 0; i < 3; i++)
		delete[] gaussCore[i];
	delete[] gaussCore;

	return 0;
}