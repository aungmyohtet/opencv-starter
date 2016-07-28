#include "stdafx.h"
#include "MyatMoe\MyatMoe.h"

using namespace cv;
using namespace std;

int myatMoe::testTrackMotion()
{
	//VideoCapture cap("E:\\Japanese Language Learning\\Waku Waku Japanese   Lesson 16 Japanese Exclusive Words (1).mp4");
	VideoCapture cap(0);
	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video file" << endl;
	}

	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	Mat firstframe;
	Mat frame; Mat deltaframe;

	while (1)
	{
		if (!cap.read(frame)) {

			cout << "Cannot read the frame from video file" << endl;
			break;
		}

		Mat frameBinary;
		cvtColor(frame, frameBinary, CV_BGR2GRAY);
		GaussianBlur(frameBinary, frameBinary, Size(7, 7), 0, 0);

		if (firstframe.empty()) {
			firstframe = frameBinary;
		}

		absdiff(firstframe, frameBinary, deltaframe);
		threshold(deltaframe, deltaframe, 25, 255, THRESH_BINARY);

		dilate(deltaframe, deltaframe, MORPH_CROSS);//MORPH_RECT//MORPH_ELLIPSE

		vector<vector<Point>> contours;
		findContours(deltaframe, contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		//drawContours(src, contours, largest_contour_index, Scalar(0, 255, 127), 8);

		for (int i = 0; i < contours.size(); i++) {

			int area = contourArea(contours[i], false);
			if (area > 2000) {
				Rect bounding_rect = boundingRect(contours[i]);
				rectangle(frame, bounding_rect, Scalar(0, 255, 0), 2, 8, 0);

				putText(frame, "detect " + to_string(contours.size()), Point(50, 50), CV_FONT_NORMAL, 1, Scalar(0, 0, 255), 1, 16);
			}
		}

		imshow("MyVideo", frame); //show the frame in "MyVideo" window
		firstframe = frameBinary;
		if (waitKey(30) == 27) {

			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	VideoCapture();

	return EXIT_SUCCESS;
}