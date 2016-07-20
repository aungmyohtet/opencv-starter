#include "stdafx.h"
#include "sumyat\SuMyat.h"
#include <iostream>
#include <opencv2\opencv.hpp>
using namespace std;
using namespace cv;
double const thresh = 127;
double const maxVal = 255;
double const blockSize = 11;
Mat img, src, dst1, dst2, dst3, dst4, dst5;

void sumyat::ImageProcedure::golbalThresholdTest(string imagePath){
	img = imread(imagePath, CV_LOAD_IMAGE_UNCHANGED);
	cvtColor(img, src, CV_BGR2GRAY);

	threshold(src, dst1, thresh, maxVal, THRESH_BINARY);
	threshold(src, dst2, thresh, maxVal, THRESH_BINARY_INV);
	threshold(img, dst3, thresh, maxVal, THRESH_TOZERO);
	threshold(img, dst4, thresh, maxVal, THRESH_TOZERO_INV);
	threshold(img, dst5, thresh, maxVal, THRESH_TRUNC);

	namedWindow("OriginalWindow", CV_WINDOW_AUTOSIZE);
	namedWindow("GrayWindow", CV_WINDOW_AUTOSIZE);
	namedWindow("Threshold_Binary_Window", CV_WINDOW_AUTOSIZE);
	namedWindow("Threshold_Binary_INV_Window", CV_WINDOW_AUTOSIZE);
	namedWindow("Threshold_TOZERO_Window", CV_WINDOW_AUTOSIZE);
	namedWindow("Threshold_TOZERO_INV_Window", CV_WINDOW_AUTOSIZE);
	namedWindow("Threshold_TRUNC_Window", CV_WINDOW_AUTOSIZE);

	imshow("OriginalWindow", img);
	imshow("GrayWindow", src);
	imshow("Threshold_Binary_Window", dst1);
	imshow("Threshold_Binary_INV_Window", dst2);
	imshow("Threshold_TOZERO_Window", dst3);
	imshow("Threshold_TOZERO_INV_Window", dst4);
	imshow("Threshold_TRUNC_Window", dst5);

	waitKey(0);

	destroyWindow("OriginalWindow");
	destroyWindow("GrayWindow");
	destroyWindow("Threshold_Binary_Window");
	destroyWindow("Threshold_Binary_INV_Window");
	destroyWindow("Threshold_TOZERO_Window");
	destroyWindow("Threshold_TOZERO_INV_Window");
	destroyWindow("Threshold_TRUNC_Window");
}

void sumyat::ImageProcedure::adaptiveThresholdTest(string imagePath){
	img = imread(imagePath, CV_LOAD_IMAGE_UNCHANGED);
	cvtColor(img, src, CV_BGR2GRAY);

	adaptiveThreshold(src, dst1, maxVal, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, blockSize, 2);
	adaptiveThreshold(src, dst2, maxVal, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, blockSize, 2);
	adaptiveThreshold(src, dst3, maxVal, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, blockSize, 2);
	adaptiveThreshold(src, dst4, maxVal, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, blockSize, 2);

	namedWindow("Original Window", CV_WINDOW_AUTOSIZE);
	namedWindow("Gray Window", CV_WINDOW_AUTOSIZE);
	namedWindow("AdapMean+Binary Window", CV_WINDOW_AUTOSIZE);
	namedWindow("AdapGaussian+Binary Window", CV_WINDOW_AUTOSIZE);
	namedWindow("AdapMean+BinaryInv Window", CV_WINDOW_AUTOSIZE);
	namedWindow("AdapGaussian+BinaryInv Window", CV_WINDOW_AUTOSIZE);

	imshow("Original Window", img);
	imshow("Gray Window", src);
	imshow("AdapMean+Binary Window", dst1);
	imshow("AdapGaussian+Binary Window", dst2);
	imshow("AdapMean+BinaryInv Window", dst3);
	imshow("AdapGaussian+BinaryInv Window", dst4);

	waitKey(0);

	destroyWindow("Original Window");
	destroyWindow("Gray Window");
	destroyWindow("AdapMean+Binary Window");
	destroyWindow("AdapGaussian+Binary Window");
	destroyWindow("AdapMean+BinaryInv Window");
	destroyWindow("AdapGaussian+BinaryInv Window");
}