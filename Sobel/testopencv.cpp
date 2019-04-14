// testopencv.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <ctime>
#include <math.h>
#include <cstdlib>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat image, gx, gy;
	image = imread("a.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		
	if (!image.data) // Check for invalid input
	{		 cout << "Could not open or find the image" << std::endl; return -1;}
	
	//OpenCV Func
	/// Generate grad_x and grad_y
	Mat grad_x, grad_y, gradiant;
	Mat abs_grad_x, abs_grad_y;
	int ddepth = CV_16S;

	// Gradient X
	Sobel(image, grad_x, ddepth, 1, 0, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	// Gradient Y
	Sobel(image, grad_y, ddepth, 0, 1, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	// Approximation
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, gradiant);

	/*
	//Not OpenCV Func
	Scalar intensity;
	gx = image.clone();
	copyMakeBorder(gx, gx, 0.05*image.rows, 0.05*image.rows, 0.05*image.cols, 0.05*image.cols, BORDER_DEFAULT);
	gy = image.clone();
	copyMakeBorder(gy, gy, 0.05*image.rows, 0.05*image.rows, 0.05*image.cols, 0.05*image.cols, BORDER_DEFAULT);
	int x, y = 0;
	for (x = 1; x < image.cols-1; x++) {
		double sum_1 = 0;
		for (int i = 0; i < 3; i++) {
			if (i == 2) {
				intensity = gx.at<uchar>(Point(x - 1, y + i));
				sum_1 += intensity.val[0] * (-2);
				intensity = gx.at<uchar>(Point(x + 1, y + i));
				sum_1 += intensity.val[0] * 2;
			}
			else {
				intensity = gx.at<uchar>(Point(x - 1, y + i));
				sum_1 += intensity.val[0] * (-1);
				intensity = gx.at<uchar>(Point(x + 1, y + i));
				sum_1 += intensity.val[0];
			}
		}
		gx.at<uchar>(Point(x, y)) = (int)sum_1;
		for (y = 1; y < image.rows-1; y++) {
			double sum_2 = 0;
			for (int i = 0; i < 3; i++) {
				if (i == 2) {
					intensity = gy.at<uchar>(Point(x + i, y - 1));
					sum_2 += intensity.val[0] * (-2);
					intensity = gy.at<uchar>(Point(x + i, y - 1));
					sum_2 += intensity.val[0] * 2;
				}
				else {
					intensity = gy.at<uchar>(Point(x + i, y + 1));
					sum_2 += intensity.val[0] * (-1);
					intensity = gy.at<uchar>(Point(x + i, y + 1));
					sum_2 += intensity.val[0];
				}
			}
			gy.at<uchar>(Point(x, y)) = (int)sum_2;
			intensity = gx.at<uchar>(Point(x, y));
			image.at<uchar>(Point(x, y)) = (int)(sqrt(pow((int)sum_2, 2) + pow(intensity.val[0], 2)));
		}
	}*/
	namedWindow("Gradiant", WINDOW_AUTOSIZE);
	imshow("Gradiant", gradiant);

	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image); // Show our image inside it.

	waitKey(0); // Wait for a keystroke in the window
	return 0;
}

