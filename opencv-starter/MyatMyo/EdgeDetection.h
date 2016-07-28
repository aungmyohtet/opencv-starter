#ifndef MYATMYO_EDGEDETECTION_H
#define MYATMYO_EDGEDETECTION_H

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

namespace myatmyo {
	static Mat src, src_gray;
	static Mat dst;
	static int lowThreshold = 0;
	static int const max_lowThreshold = 100;
	static int ratio = 3;
	static int kernel_size = 3;
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