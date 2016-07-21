#include "stdafx.h"
#include "MyatMyo\MyatMyo.h"

void myatmyo::EdgeDetection::sobelEdgeDetection(std::string imagePath) {
	Mat src, src_gray;
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	Mat grad;
	double minVal, maxVal;

	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	src = imread(imagePath, CV_LOAD_IMAGE_UNCHANGED);
	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", src);

	// Smooting
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	// GrayScale
	cvtColor(src, src_gray, CV_BGR2GRAY);

	/// Gradient X
	Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	//Sobel(src_gray, grad_x, ddepth, 1, 0);
	convertScaleAbs(grad_x, abs_grad_x);
	namedWindow("Grad X", CV_WINDOW_AUTOSIZE);
	imshow("Grad X", abs_grad_x);

	/// Gradient Y
	Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	//Sobel(src_gray, grad_y, ddepth, 0, 1);
	convertScaleAbs(grad_y, abs_grad_y);
	namedWindow("Grad Y", CV_WINDOW_AUTOSIZE);
	imshow("Grad Y", abs_grad_y);

	/// Total Gradient (approximate) Gradient x + Gradient y
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	namedWindow("Sobel - grad X + Y", CV_WINDOW_AUTOSIZE);
	imshow("Sobel - grad X + Y", grad);

	// minimum and maximum intensities
	minMaxLoc(grad, &minVal, &maxVal);
	cout << "minVal : " << minVal << endl << "maxVal : " << maxVal << endl;

	waitKey(0);
}

void myatmyo::EdgeDetection::laplaceEdgeDetection(std::string imagePath) {

	Mat src, src_gray, dst;
	Mat abs_dst;

	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	/// Load an image
	src = imread(imagePath, CV_LOAD_IMAGE_UNCHANGED);
	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", src);

	/// Smooting
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	/// Grayscale
	cvtColor(src, src_gray, CV_BGR2GRAY);

	/// Apply Laplace function
	Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);

	/// Show what you got
	namedWindow("Laplace", CV_WINDOW_AUTOSIZE);
	imshow("Laplace", abs_dst);

	waitKey(0);
}

Mat src, src_gray;
Mat dst;

int lowThreshold = 0;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;

void myatmyo::EdgeDetection::cannyEdgeDetection(std::string imagePath) {

	src = imread(imagePath, CV_LOAD_IMAGE_UNCHANGED);
	namedWindow("Original", CV_WINDOW_AUTOSIZE);
	imshow("Original", src);

	// Smooting
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	// Grayscale
	cvtColor(src, src_gray, CV_BGR2GRAY);

	// Create a window
	namedWindow("Canny", CV_WINDOW_AUTOSIZE);

	// Create a Trackbar for user to enter threshold
	createTrackbar("Min Threshold:", "Canny", &lowThreshold, max_lowThreshold, CannyThreshold);

	// Show the image
	CannyThreshold(0, 0);

	// Wait until user exit program by pressing a key
	waitKey(0);
}

void myatmyo::EdgeDetection::CannyThreshold(int, void*) {

	// Apply Canny function
	Canny(src_gray, dst, lowThreshold, lowThreshold*ratio, kernel_size);

	imshow("Canny", dst);
}

void myatmyo::EdgeDetection::sobelLaplaceCanny(std::string imagePath) {

	Mat src, src_gray;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	string src_name = "Source";
	string sobel_name = "Sobel";
	string canny_name = "Canny";
	string laplace_name = "Laplace";

	src = imread("E:\\Myat Myo Lwin\\Software\\java\\opencv\\sources\\samples\\data\\lena.jpg");


	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, COLOR_RGB2GRAY);

	namedWindow(src_name, WINDOW_AUTOSIZE);
	namedWindow(sobel_name, WINDOW_AUTOSIZE);
	namedWindow(canny_name, WINDOW_AUTOSIZE);
	namedWindow(laplace_name, WINDOW_AUTOSIZE);

	//This is for source image.
	imshow(src_name, src);

	//This is for sobel edge detection.
	Mat sobel_dst;
	Mat sobel_abs_dst;
	Sobel(src_gray, sobel_dst, ddepth, 1, 1, kernel_size);
	convertScaleAbs(sobel_dst, sobel_abs_dst);
	imshow(sobel_name, sobel_abs_dst);

	//This is for laplace edge detection.
	Mat laplace_dst;
	Mat laplace_abs_dst;
	Laplacian(src_gray, laplace_dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(laplace_dst, laplace_abs_dst);
	imshow(laplace_name, laplace_abs_dst);

	//This is for canny edge detection.
	Mat canny_dst;
	Canny(src_gray, canny_dst, 50, 200, kernel_size);
	imshow(canny_name, canny_dst);

	waitKey(0);
}