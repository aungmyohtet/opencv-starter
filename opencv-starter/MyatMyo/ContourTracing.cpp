#include "stdafx.h"
#include "MyatMyo\ContourTracing.h"

using namespace myatmyo;

/*
Finding Contours Example and method Explaination
http://opencvexamples.blogspot.com/2013/09/find-contour.html
Mode of Finding Contours
http://docs.opencv.org/master/d9/d8b/tutorial_py_contours_hierarchy.html#gsc.tab=0
*/
void myatmyo::ContourTracing::findingContours(std::string imagePath) {

	Mat image;
	Mat gray;

	image = imread(imagePath, CV_LOAD_IMAGE_UNCHANGED);

	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", image);

	cvtColor(image, gray, CV_BGR2GRAY);
	Canny(gray, gray, 100, 200, 3);
	vector<vector<Point> > contours;
	findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	Mat drawing = Mat::zeros(gray.size(), CV_8UC1);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(255, 255, 255);
		drawContours(drawing, contours, i, color);
	}
	imshow("CV_RETR_LIST", drawing);

	cvtColor(image, gray, CV_BGR2GRAY);
	Canny(gray, gray, 100, 200, 3);
	contours.clear();
	findContours(gray, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	drawing = Mat::zeros(gray.size(), CV_8UC1);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(255, 255, 255);
		drawContours(drawing, contours, i, color);
	}
	imshow("CV_RETR_EXTERNAL", drawing);

	cvtColor(image, gray, CV_BGR2GRAY);
	Canny(gray, gray, 100, 200, 3);
	contours.clear();
	findContours(gray, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	drawing = Mat::zeros(gray.size(), CV_8UC1);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(255, 255, 255);
		drawContours(drawing, contours, i, color);
	}
	imshow("CV_RETR_CCOMP", drawing);

	cvtColor(image, gray, CV_BGR2GRAY);
	Canny(gray, gray, 100, 200, 3);
	contours.clear();
	findContours(gray, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	drawing = Mat::zeros(gray.size(), CV_8UC1);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(255, 255, 255);
		drawContours(drawing, contours, i, color);
	}
	imshow("CV_RETR_TREE", drawing);

	waitKey(0);
}

void myatmyo::ContourTracing::findingLargestContour(std::string imagePath) {

	Mat src; Mat gray;
	int largest_area = 0;
	int largest_contour_index = 0;
	Rect bounding_rect;
	vector<vector<Point>> contours; // Vector for storing contour

	src = imread(imagePath, CV_LOAD_IMAGE_COLOR);
	cvtColor(src, gray, CV_BGR2GRAY);
	threshold(gray, gray, 200, 255, THRESH_BINARY_INV); //Threshold the gray
	imshow("gray", gray);

	findContours(gray, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	// iterate through each contour.
	for (int i = 0; i< contours.size(); i++) {

		//  Find the area of contour
		double area = contourArea(contours[i], false);
		cout << i << " area  " << area << endl;

		if (area > largest_area){

			largest_area = area;
			// Store the index of largest contour
			largest_contour_index = i;
			// Find the bounding rectangle for biggest contour
			bounding_rect = boundingRect(contours[i]);
		}
	}

	//Draw the contour and rectangle
	drawContours(src, contours, largest_contour_index, Scalar(0, 0, 0), CV_FILLED, 8);
	rectangle(src, bounding_rect, Scalar(0, 255, 0), 2, 8, 0);
	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", src);
	waitKey(0);

}

void myatmyo::ContourTracing::findingContoursOnVariousThreshold(std::string imagePath) {

	image_contour = imread(imagePath, CV_LOAD_IMAGE_UNCHANGED);

	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", image_contour);
	namedWindow("Result", CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar("Threshold", "Result", &current_thresh, max_thresh, on_trackbar);
	on_trackbar(0);
	waitKey(0);
}

void myatmyo::ContourTracing::on_trackbar(int) {

	vector<vector<Point> > contours;
	Mat drawing = Mat::zeros(image_contour.size(), CV_8UC1);

	cvtColor(image_contour, gray_contour, CV_BGR2GRAY);
	threshold(gray_contour, gray_contour, current_thresh, max_thresh, THRESH_BINARY_INV);
	
	findContours(gray_contour, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
	
	for (int i = 0; i< contours.size(); i++) {

		Scalar color = Scalar(255, 255, 255);
		drawContours(drawing, contours, i, color);

	}

	imshow("Result", drawing);
}

void myatmyo::ContourTracing::approximatePolygonFromContours(std::string imagePath) {

	Mat image;
	Mat gray;
	Mat resultImg;
	vector<vector<Point> > contours;
	vector<Point> result;

	image = imread(imagePath, CV_LOAD_IMAGE_UNCHANGED);

	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", image);

	cvtColor(image, gray, CV_BGR2GRAY);
	threshold(gray, gray, 200, 255, THRESH_BINARY_INV);

	findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	resultImg = Mat::zeros(image.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++) {
		result.clear();
		//obtain a sequence of points of contour, pointed by the variable 'contour'
		approxPolyDP(contours[i], result, 3, true);

		if (result.size() >= 5) {

			const cv::Point *pts = (const cv::Point*) Mat(result).data;
			int npts = Mat(result).rows;
			//polylines(Mat& img, const Point** pts, const int* npts, int ncontours, bool isClosed, const Scalar& color, int thickness = 1, int lineType = 8, int shift = 0)
			polylines(resultImg, &pts, &npts, 1, true, Scalar(0, 255, 0), 1, CV_AA, 0);
		}
	}

	namedWindow("Approximate Polygon");
	imshow("Approximate Polygon", resultImg);

	waitKey(0);
}

void myatmyo::ContourTracing::bounding(std::string imagePath) {

	Mat src; Mat gray;
	int largest_area = 0;
	int largest_contour_index = 0;
	Rect bounding_rect;
	RotatedRect rotateRec;
	RotatedRect elip;
	vector<vector<Point>> contours;
	Point2f center;
	float radius;
	Point2f vertices[4];

	src = imread(imagePath, CV_LOAD_IMAGE_COLOR);
	imshow("Original", src);

	cvtColor(src, gray, CV_BGR2GRAY);
	threshold(gray, gray, 200, 255, THRESH_BINARY_INV); //Threshold the gray

	findContours(gray, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	drawContours(src, contours, largest_contour_index, Scalar(0, 255, 127), CV_FILLED, 8);

	// iterate through each contour.
	for (int i = 0; i< contours.size(); i++) {

		//  Find the area of contour
		double area = contourArea(contours[i], false);
		cout << "contourArea " << i << " = " << area << endl;

		//  Find the arcLenght of contour
		double length = arcLength(contours[i], true);
		cout << "arcLength " << i << " = " << length << endl;

		//Enclosing Circle
		minEnclosingCircle(contours[i], center, radius);
		circle(src, center, (int)radius, Scalar(173, 255, 47), 2, 8, 0);

		//Enclosing Ellipse
		if (contours[i].size() > 4) {

			elip = fitEllipse(contours[i]);
			ellipse(src, elip, (255, 69, 0), 2);
		}

		//Bounding Rectangle
		bounding_rect = boundingRect(contours[i]);
		rectangle(src, bounding_rect, Scalar(255, 0, 255), 2, 8, 0);

		//Bounding fixRectangle
		rotateRec = minAreaRect(contours[i]);
		rotateRec.points(vertices);

		for (int i = 0; i < 4; i++) {
			line(src, vertices[i], vertices[(i + 1) % 4], Scalar(255, 192, 203), 2, 8, 0);
		}

		//Drawing fitLine
		Vec4f lines;
		fitLine(Mat(contours[i]), lines, 2, 0, 0.01, 0.01);
		int lefty = (-lines[2] * lines[1] / lines[0]) + lines[3];
		int righty = ((gray.cols - lines[2])*lines[1] / lines[0]) + lines[3];
		line(src, Point(gray.cols - 1, righty), Point(0, lefty), Scalar(255, 0, 0), 2);

	}

	namedWindow("Bounding-Enclosing-Fitline", CV_WINDOW_AUTOSIZE);
	imshow("Bounding-Enclosing-Fitline", src);
	waitKey(0);

}

void myatmyo::ContourTracing::boundingWithConvexHull(std::string imagePath) {

	/// Load source image and convert it to gray
	src_convex = imread("E:\\opencvprojects\\opencv-starter\\images\\momiji.jpg", CV_LOAD_IMAGE_COLOR);
	//src = imread("C:\\Users\\DELL\\Desktop\\car.jpg", CV_LOAD_IMAGE_COLOR);

	///Convert image to gray and blur it
	cvtColor(src_convex, src_gray_convex, CV_BGR2GRAY);
	blur(src_gray_convex, src_gray_convex, Size(3, 3));

	/// Create Window
	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", src_convex);

	createTrackbar("Threshold:", "Original", &current_thresh, max_thresh, convexHullThreshold);
	convexHullThreshold(0, 0);

	waitKey(0);

}

void myatmyo::ContourTracing::convexHullThreshold(int, void*)
{
	Mat src_copy = src_convex.clone();
	Mat threshold_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// Detect edges using Threshold
	threshold(src_gray_convex, threshold_output, current_thresh, max_thresh, THRESH_BINARY);

	/// Find contours
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Find the convex hull object for each contour
	vector<vector<Point> >hull(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		convexHull(Mat(contours[i]), hull[i], false);
	}

	/// Draw contours + hull results
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}

	/// Show in a window
	namedWindow("Convex Hull", CV_WINDOW_AUTOSIZE);
	imshow("Convex Hull", drawing);
}