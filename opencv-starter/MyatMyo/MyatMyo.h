#ifndef MYATMYO_EDGEDETECTION_H
#define MYATMYO_EDGEDETECTION_H

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

namespace myatmyo {
	class EdgeDetection{
	public:
		EdgeDetection();
		~EdgeDetection();
		static void sobelEdgeDetection();
		static void laplaceEdgeDetection();
		static void cannyEdgeDetection();
		static void sobelLaplaceCanny();
	private:
		static void CannyThreshold(int, void*);
	};
}

#endif