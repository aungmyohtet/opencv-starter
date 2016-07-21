#include "stdafx.h"
#include "SmoothingProcessor.h"

using namespace std;
using namespace smoothingProc;

void prepareImgToSmooth(string imagePath);
int displayImages(string title);

smoothingProc::SmoothingProcessor::SmoothingProcessor() {

}

smoothingProc::SmoothingProcessor::~SmoothingProcessor() {

}

int::smoothingProc::SmoothingProcessor::HomogeneousSmoothing(string imagePath) {

	prepareImgToSmooth(imagePath);
	//void blur(InputArray src, OutputArray dst, Size ksize, Point anchor=Point(-1,-1), int borderType=BORDER_DEFAULT )
	blur(src, dst, Size(5, 5));
	displayImages("Homogenous Smoothing");
	//waitKey(0);
	return 0;
}

int::smoothingProc::SmoothingProcessor::GaussianSmoothing(string imagePath) {
	prepareImgToSmooth(imagePath);
	//GaussianBlur(InputArray  src, OutputArray  dst, Size  ksize, double  sigmaX, double  sigmaY=0, int  borderType = BORDER_DEFAULT )
	GaussianBlur(src, dst, Size(7, 7), 0, 0);
	displayImages("Gaussian Smoothing");
	//waitKey(0);
	return 0;
}

int::smoothingProc::SmoothingProcessor::MedianSmoothing(string imagePath) {
	prepareImgToSmooth(imagePath);
	//void medianBlur(InputArray src, OutputArray dst, int ksize)
	medianBlur(src, dst, 5);
	displayImages("Median Smoothing");
	//waitKey(0);
	return 0;
}

int::smoothingProc::SmoothingProcessor::BilateralSmoothing(string imagePath) {
	prepareImgToSmooth(imagePath);
	//void  bilateralFilter(InputArray src, OutputArray dst, int d, double sigmaColor, double sigmaSpace, intborderType=BORDER_DEFAULT)
	bilateralFilter(src, dst, 11, 100, 100);
	displayImages("Bilateral Smoothing");
	//waitKey(0);
	return 0;
}

void prepareImgToSmooth(string imagePath) {
	using namespace smoothingProc;
	src = imread(imagePath, CV_LOAD_IMAGE_UNCHANGED);
	dst = src.clone();
}

int displayImages(string title) {
	namedWindow("Original Image", WINDOW_AUTOSIZE);
	namedWindow(title, WINDOW_AUTOSIZE);
	using namespace smoothingProc;
	imshow("Original Image", src);
	imshow(title, dst);

	waitKey(0);

	return 0;

}