#include "stdafx.h"
#include <iostream>
#include "sumyat\SuMyat.h"

using namespace std;
using namespace cv;

using namespace sumyat;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_RBUTTONDOWN)
	{
		cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MBUTTONDOWN)
	{
		cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
	}
}

//detect left mouse clicks while pressing the "CTRL" key ,
//right mouse clicks while pressing the "SHIFT" key and 
//movements of the mouse over the OpenCV window while pressing the "ALT" key. 
void CallBackFuncFlags(int event, int x, int y, int flags, void* userdata)
{
	if (flags == (EVENT_FLAG_CTRLKEY + EVENT_FLAG_LBUTTON))
	{
		cout << "Left mouse button is clicked while pressing CTRL key - position (" << x << ", " << y << ")" << endl;
	}
	else if (flags == (EVENT_FLAG_RBUTTON + EVENT_FLAG_SHIFTKEY))
	{
		cout << "Right mouse button is clicked while pressing SHIFT key - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MOUSEMOVE && flags == EVENT_FLAG_ALTKEY)
	{
		cout << "Mouse is moved over the window while pressing ALT key - position (" << x << ", " << y << ")" << endl;
	}
}

//will extract color information at a pixel location in an image.
void mouseEvents(int evt, int x, int y, int flags, void* param)
{
	Mat* rgb = (Mat*)param;
	if (evt == CV_EVENT_LBUTTONDOWN)
	{
		printf("%d %d: %d, %d, %d\n",
			x, y,
			(int)(*rgb).at<Vec3b>(y, x)[0],
			(int)(*rgb).at<Vec3b>(y, x)[1],
			(int)(*rgb).at<Vec3b>(y, x)[2]);
	}
}

void on_mouse(int e, int x, int y, int d, void *ptr)
{
	Point*p = (Point*)ptr;
	p->x = x;
	p->y = y;
	cout << *p;
}

void sumyat::ImageProcedure::mouseEventTest(string imagePath){

	img = imread(imagePath, CV_LOAD_IMAGE_UNCHANGED);

	//Create a window
	namedWindow("ImageDisplay", WINDOW_AUTOSIZE);

	Point p;
	//set the callback function for any mouse event
	setMouseCallback("ImageDisplay", CallBackFunc, NULL);
	//setMouseCallback("ImageDisplay", CallBackFuncFlags, NULL);
	//setMouseCallback("ImageDisplay", mouseEvents, &img);
	//setMouseCallback("ImageDisplay", on_mouse, &p);

	//show the image
	imshow("ImageDisplay", img);

	// Wait until user press some key
	waitKey(0);

	destroyWindow("ImageDisplay");
}

void on_trackbar(int, void*)
{
	alpha = (double)alpha_slider / alpha_slider_max;
	beta = (1.0 - alpha);

	addWeighted(src, alpha, img, beta, 0.0, dst1);

	imshow("Linear Blend", dst1);
}

void sumyat::ImageProcedure::trackBarTest(string imagePath1, string imagePath2){

	img = imread(imagePath1, CV_LOAD_IMAGE_UNCHANGED);
	src = imread(imagePath2, CV_LOAD_IMAGE_UNCHANGED);

	if (!img.data || !src.data) {
		cout << "Error loading image \n";
		return;
	}

	/// Initialize values
	alpha_slider = 0;

	/// Create Windows
	namedWindow("Linear Blend", 1);

	/// Create Trackbars
	createTrackbar("Alpha", "Linear Blend", &alpha_slider, alpha_slider_max, on_trackbar);

	/// Show some stuff
	on_trackbar(alpha_slider, 0);

	/// Wait until user press some key
	waitKey(0);

	destroyWindow("Linear Blend");

}