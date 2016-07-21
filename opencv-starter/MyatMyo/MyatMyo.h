#ifndef MYATMYO_EDGEDETECTION_H
#define MYATMYO_EDGEDETECTION_H

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

namespace myatmyo {
	Mat src, src_gray;
	Mat dst;

	int lowThreshold = 0;
	int const max_lowThreshold = 100;
	int ratio = 3;
	int kernel_size = 3;
	class EdgeDetection{
	public:
		EdgeDetection();
		~EdgeDetection();
		static void sobelEdgeDetection(std::string);
		static void laplaceEdgeDetection(std::string);
		static void cannyEdgeDetection(std::string);
		static void sobelLaplaceCanny(std::string);
	private:
		static void CannyThreshold(int, void*);
	};
}

#endif