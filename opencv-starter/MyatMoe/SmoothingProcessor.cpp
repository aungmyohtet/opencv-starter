#include "stdafx.h"
#include "SmoothingProcessor.h"

using namespace std;
using namespace cv;

Mat src; Mat dst;

void prepareImgToSmooth(string imagePath);
int displayImages(string title);

int::smoothingProc::HomogeneousSmoothing(string imagePath) {

	prepareImgToSmooth(imagePath);
	blur(src, dst, Size(5, 5));
	displayImages("Homogenous Smoothing");
	//waitKey(0);
	return 0;
}

int::smoothingProc::GaussianSmoothing(string imagePath) {
	prepareImgToSmooth(imagePath);
	GaussianBlur(src, dst, Size(7, 7), 0, 0);
	displayImages("Gaussian Smoothing");
	//waitKey(0);
	return 0;
}

int::smoothingProc::MedianSmoothing(string imagePath) {
	prepareImgToSmooth(imagePath);
	medianBlur(src, dst, 5);
	displayImages("Median Smoothing");
	//waitKey(0);
	return 0;
}

int::smoothingProc::BilateralSmoothing(string imagePath) {
	prepareImgToSmooth(imagePath);
	bilateralFilter(src, dst, 11, 100, 100);
	displayImages("Bilateral Smoothing");
	//waitKey(0);
	return 0;
}

void prepareImgToSmooth(string imagePath) {
	src = imread(imagePath, CV_LOAD_IMAGE_UNCHANGED);
	dst = src.clone();
}

int displayImages(string title) {
	namedWindow("Original Image", WINDOW_AUTOSIZE);
	namedWindow(title, WINDOW_AUTOSIZE);

	imshow("Original Image", src);
	imshow(title, dst);

	waitKey(0);

	return 0;

}