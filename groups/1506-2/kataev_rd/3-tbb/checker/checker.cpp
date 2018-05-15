#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace cv;
using namespace std;

//функция метрики SSIM для сравнения изображений
double SSIM(Mat source1, Mat source2)
{
	double C = 0.01;
	double averageSource = 0, averageSource2 = 0;
	double sigma1 = 0.0, sigma2 = 0.0, sigma12 = 0.0;

	//вычисление среднего для 1-го изображения
	for (int i = 0; i < source1.rows; ++i)
		for (int j = 0; j <source1.cols; ++j)
			averageSource += source1.at<uchar>(i, j);
	averageSource /= (source1.rows * source1.cols);

	//вычисление среднего для 2-го изображения
	for (int i = 0; i < source2.rows; ++i)
		for (int j = 0; j <source2.cols; ++j)
			averageSource2 += source2.at<uchar>(i, j);
	averageSource2 /= (source2.rows * source2.cols);

	//вычисление дисперсий (сигма)
	for (int i = 0; i < source1.rows; ++i)
		for (int j = 0; j <source1.cols; ++j)
		{
			sigma1 += pow((double)(source1.at<uchar>(i, j) - averageSource), 2);
			sigma2 += pow((double)(source2.at<uchar>(i, j) - averageSource2), 2);
			sigma12 += (source1.at<uchar>(i, j) - averageSource)*(source2.at<uchar>(i, j) - averageSource2);
		}

	sigma1 /= (source1.rows * source1.cols - 1);
	sigma1 = sqrt(sigma1);

	sigma2 /= (source2.rows * source2.cols - 1);
	sigma2 = sqrt(sigma2);

	sigma12 /= (source1.rows * source1.cols - 1);

	double l, c, s;

	l = (2 * averageSource * averageSource2 + C) / (averageSource * averageSource + averageSource2 * averageSource2 + C);
	c = (2 * sigma1 * sigma2 + C) / (sigma1 * sigma1 + sigma2 * sigma2 + C);
	s = (sigma12 + C) / (sigma1 * sigma2 + C);

	return l * c * s;
}

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
		
		//чтение файла задания
		ifstream testFile;
		testFile.open(testName, ios::in | ios::binary);
		testFile >> picName;
		testFile >> sigma;

		//загрузка изображений на основании информации из задания
		inFileRaw = imread(picPathRaw + picName, CV_LOAD_IMAGE_COLOR);
		inFileCustom = imread(picPathCustom + picName, CV_LOAD_IMAGE_COLOR);
		Mat outFileCV(inFileCustom.size(), CV_8UC3);

		//применение к исходному изображению стандартной функции OpenCV
		GaussianBlur(inFileRaw, outFileCV, Size(3, 3), sigma, 0, BORDER_DEFAULT);

		//сравнение изображений, полученных OpenCV и solver и печать результата
		double similarity = SSIM(inFileCustom, outFileCV);

		cout << "Now testing image: " << i << endl;
		cout << "Sigma: " << sigma << endl << "Similarity: " << similarity << endl;
		if (similarity >= 0.99)
			cout << "PASS!" << endl << endl;
		else cout << "FAIL!" << endl << endl;

		//запись изображения, полученного функцией OpenCV
		imwrite(outputPathCV + picName, outFileCV);

		testFile.close();
		testFile.clear();
	}

	return 0;
}