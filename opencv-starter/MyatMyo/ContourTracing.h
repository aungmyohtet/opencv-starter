#ifndef MYATMYO_CONTOURTRACING_H
#define MYATMYO_CONTOURTRACING_H

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

namespace myatmyo {
	static Mat image_contour;
	static Mat gray_contour;
	static int thresh_contour = 100;
	class ContourTracing{
	public:
		ContourTracing();
		~ContourTracing();
		static void findingContours(std::string);
		static void findingLargestContour(std::string);
		static void findingContoursOnVariousThreshold(std::string);
		static void approximatePolygonFromContours(std::string);
		static void bounding(std::string);
	private:
		static void on_trackbar(int);
	};
}

#endif