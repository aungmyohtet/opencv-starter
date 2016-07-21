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

void SmoothingProcessor::setSrc(std::string path) {
	this->src = cv::imread(path, CV_LOAD_IMAGE_UNCHANGED);
}

cv::Mat SmoothingProcessor::getSrc() {
	return this->src;
}

void SmoothingProcessor::setDst(cv::Mat source) {
	this->dst = source.clone();
}

cv::Mat SmoothingProcessor::getDst() {
	return this->dst;
}

int::smoothingProc::SmoothingProcessor::HomogeneousSmoothing(string imagePath) {

	//prepareImagesToSmooth
	this->setSrc(imagePath);
	this->setDst(this->getSrc());
	//void blur(InputArray src, OutputArray dst, Size ksize, Point anchor=Point(-1,-1), int borderType=BORDER_DEFAULT )
	blur(getSrc(), getDst(), cv::Size(5, 5));
	this->displayImages("Homogenous Smoothing");
	//waitKey(0);
	return 0;
}

int::smoothingProc::SmoothingProcessor::GaussianSmoothing(string imagePath) {
	this->setSrc(imagePath);
	this->setDst(this->getSrc());
	//GaussianBlur(InputArray  src, OutputArray  dst, Size  ksize, double  sigmaX, double  sigmaY=0, int  borderType = BORDER_DEFAULT )
	GaussianBlur(getSrc(), getDst(), cv::Size(7, 7), 0, 0);
	this->displayImages("Gaussian Smoothing");
	//waitKey(0);
	return 0;
}

int::smoothingProc::SmoothingProcessor::MedianSmoothing(string imagePath) {
	this->setSrc(imagePath);
	this->setDst(this->getSrc());
	//void medianBlur(InputArray src, OutputArray dst, int ksize)
	medianBlur(getSrc(), getDst(), 5);
	this->displayImages("Median Smoothing");
	//waitKey(0);
	return 0;
}

int::smoothingProc::SmoothingProcessor::BilateralSmoothing(string imagePath) {
	this->setSrc(imagePath);
	this->setDst(this->getSrc());
	//void  bilateralFilter(InputArray src, OutputArray dst, int d, double sigmaColor, double sigmaSpace, intborderType=BORDER_DEFAULT)
	bilateralFilter(getSrc(), getDst(), 11, 100, 100);
	this->displayImages("Bilateral Smoothing");
	//waitKey(0);
	return 0;
}


void::smoothingProc::SmoothingProcessor::displayImages(string title) {
	cv::namedWindow("Original Image", cv::WINDOW_AUTOSIZE);
	cv::namedWindow(title, cv::WINDOW_AUTOSIZE);
	using namespace smoothingProc;
	cv::imshow("Original Image", this->getSrc());
	cv::imshow(title, this->getDst());
	cv::waitKey(0);

}