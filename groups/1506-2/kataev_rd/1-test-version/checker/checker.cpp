#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
	Mat inFileRaw, inFileCustom;
	string testName, picName, picPathRaw, picPathCustom, outputPathCV;
	float sigma;

	for (int i = 0; i < 10; i++)
	{
		picPathRaw = "../../SourceImgs/";
		picPathCustom = "../../CustomResults/";
		outputPathCV = "../../CVResults/";

		testName = "../../Tests/test" + to_string(i) + ".bin";
		ifstream testFile;
		testFile.open(testName, ios::in | ios::binary);
		//testFile.seekg(0, ios::end);
		
		testFile >> picName;
		cout << picName << endl;
		testFile >> sigma;
		cout << sigma << endl;

		inFileRaw = imread(picPathRaw + picName, CV_LOAD_IMAGE_COLOR);
		inFileCustom = imread(picPathCustom + picName, CV_LOAD_IMAGE_COLOR);

		Mat outFileCV(inFileCustom.size(), CV_8UC3);
		
		GaussianBlur(inFileRaw, outFileCV, Size(3, 3), sigma, 0, BORDER_DEFAULT);

		//	float similarity = 0.0;

		//	for (int i = 0; i < inFileCustom.rows; i++)
		//	{
		//		for (int j = 0; j < inFileCustom.cols; j++)
		//		{
		//			similarity += pow(inFileCustom.at<uchar>(i, j) - outFileCV.at<uchar>(i, j), 2);
		//		}
		//	}

		//	return 1.0 - sqrt(similarity) / (inFileCustom.rows * inFileCustom.cols);

		imwrite(outputPathCV + picName, outFileCV);

		testFile.close();
		testFile.clear();
	}

	return 0;
}