#define _USE_MATH_DEFINES
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "tbb/blocked_range2d.h"
#include "tbb/parallel_for.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/tick_count.h"

using namespace cv;
using namespace std;
using namespace tbb;

int control(int in, int a, int b)
{
	if (in < a)
		return a;
	if (in > b)
		return b;
	else return in;
}

//class with an operator containin actual gaussian filtering
//filtering code same as linear/OpenMP
class Gausser
{
private:
	Mat &in;
	Mat &out;
	double **gaussCore;
	int width, height, radius;
public:
	Gausser(Mat& _inPic, Mat& _outPic, double** _gaussCore, int _width, int _height, int _radius) : in(_inPic), out(_outPic), gaussCore(_gaussCore), width(_width), height(_height), radius(_radius) {}

	void operator()(const blocked_range2d<size_t, size_t>& r) const
	{
		size_t colStart = r.cols().begin();
		size_t colStop = r.cols().end();
		size_t rowStart = r.rows().begin();
		size_t rowStop = r.rows().end();

		for (size_t i = rowStart; i < rowStop; ++i)
		{
			for (size_t j = colStart; j < colStop; ++j)
			{
				double blue = 0, green = 0, red = 0;

				for (int t = -radius; t <= radius; t++)
				{
					for (int k = -radius; k <= radius; k++)
					{
						int currX = control(i + t, 0, height - 1);
						int currY = control(j + k, 0, width - 1);
						Vec3b neighborCol = in.at<Vec3b>(currX, currY);
						blue += neighborCol.val[0] * gaussCore[t + radius][k + radius];
						green += neighborCol.val[1] * gaussCore[t + radius][k + radius];
						red += neighborCol.val[2] * gaussCore[t + radius][k + radius];
					}
				}
				Vec3b col(control(blue, 0, 255), control(green, 0, 255), control(red, 0, 255));
				out.at<Vec3b>(i, j) = col;
			}
		}
	}
};

int main(int argc, char *argv[])
{
	int size = 3;
	int radius = size / 2;
	float sigma = 0;
	double sum = 0;
	int i = 0;
	string testName, picPathRaw, fileName, picName;

	string outputPathCustom = "../../CustomResults/";
	picPathRaw = "../../SourceImgs/";
	string tstStr = string(argv[1]);
	testName = "../../Tests/" + tstStr;

	//test file read
	ifstream testFile;
	testFile.open(testName, ios::in | ios::binary);
	testFile >> picName;
	testFile >> sigma;

	fileName = outputPathCustom + picName;

	Mat inFile;
	inFile = imread(picPathRaw + picName, CV_LOAD_IMAGE_COLOR);
	Mat outFile(inFile.size(), CV_8UC3);

	//gaussian kernel initialization and normalization
	double **gaussCore = new double*[size];
	for (int i = 0; i < size; i++)
		gaussCore[i] = new double[size];

	for (i = -radius; i <= radius; i++)
	{
		for (int j = -radius; j <= radius; j++)
		{
			gaussCore[i + radius][j + radius] = exp(-(i*i + j * j) / (sigma * sigma));
			sum += gaussCore[i + radius][j + radius];
		}

	}

	for (i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			gaussCore[i][j] /= sum;
		}
	}

	int height = inFile.rows;
	int width = inFile.cols;

	//initialize TBB
	task_scheduler_init init(6);

	tick_count t1, t2;
	double time;

	t1 = tick_count::now();

	//begin the filtering process
	auto func = Gausser(inFile, outFile, gaussCore, width, height, radius);
	parallel_for(blocked_range2d<size_t, size_t>(0, height, 0, width), func);

	t2 = tick_count::now();
	tick_count::interval_t res = t2 - t1;
	time = res.seconds();

	cout << endl << "DONE IN " << time;

	imwrite(fileName, outFile);

	for (int i = 0; i < 3; i++)
		delete[] gaussCore[i];
	delete[] gaussCore;

	return 0;
}