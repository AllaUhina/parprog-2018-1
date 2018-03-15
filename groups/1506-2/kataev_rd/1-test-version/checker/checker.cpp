#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cmath>

using namespace cv;

int main(int argc, char *argv[])
{
	Mat inFileRaw, inFileCustom;

	for (int i = 0; i < 10; i++)
	{
		inFileRaw = imread(argv[1], CV_LOAD_IMAGE_COLOR);
		inFileCustom = imread(argv[2], CV_LOAD_IMAGE_COLOR);

		Mat outFileCV(inFileCustom.size(), CV_8UC3);
		GaussianBlur(inFileCustom, outFileCV, Size(3, 3), 1.5, 1.5, BORDER_DEFAULT);

		float similarity = 0.0;

		for (int i = 0; i < inFileCustom.rows; i++)
		{
			for (int j = 0; j < inFileCustom.cols; j++)
			{
				similarity += pow(inFileCustom.at<uchar>(i, j) - outFileCV.at<uchar>(i, j), 2);
			}
		}

		return 1.0 - sqrt(similarity) / (inFileCustom.rows * inFileCustom.cols);

		imwrite("newCV.jpg", outFileCV);
	}

return 0;
}