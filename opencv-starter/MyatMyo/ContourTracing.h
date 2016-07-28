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
	static int current_thresh = 100;
	static int max_thresh = 255;
	static Mat src_convex;
	static Mat src_gray_convex;
	static RNG rng(12345);
	class ContourTracing{
	public:
		ContourTracing();
		~ContourTracing();
		static void findingContours(std::string);
		static void findingLargestContour(std::string);
		static void findingContoursOnVariousThreshold(std::string);
		static void approximatePolygonFromContours(std::string);
		static void bounding(std::string);
		static void boundingWithConvexHull(std::string);
		static void faceDetection();
	private:
		static void on_trackbar(int);
		static void convexHullThreshold(int, void*);
	};
}

#endif