#include "stdafx.h"
#include "hninnayecho/hninnayecho.h"
#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

void hninnayecho::ImageProcessing::changeBrightness(std::string imagePath) {
	double alpha; /**< Simple contrast control */
	int beta;  /**< Simple brightness control */
	Mat image = imread(imagePath, CV_LOAD_IMAGE_UNCHANGED); //read the image data from the file path given
	Mat new_image = Mat::zeros(image.size(), image.type());
	
	std::cout << " Basic Linear Transforms " << std::endl;
	std::cout << "-------------------------" << std::endl;
	std::cout << "* Enter the alpha value [1.0-3.0]: "; std::cin >> alpha;
	std::cout << "* Enter the beta value [0-100]: "; std::cin >> beta;

	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			/*for (int c = 0; c < 3; c++)
			{
				new_image.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta);
			}*/
			new_image.at<Vec3b>(y, x)[0] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[0]) + beta);
			new_image.at<Vec3b>(y, x)[1] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[1]) + beta);
			new_image.at<Vec3b>(y, x)[2] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[2]) + beta);
		}
	}
 
	namedWindow("Original Image", 1);
	namedWindow("New Image", 1);

	imshow("Original Image", image);
	imshow("New Image", new_image);

	waitKey(0);

	destroyWindow("MyWindow");
}

void hninnayecho::ImageProcessing::drawimage(){

	Mat img(500, 500, CV_8UC3, Scalar(255, 255, 255));
	int thickness = 2;
	int lineType = -1;
	line(img, Point(50, 50), Point(150, 150), Scalar(0, 0, 0), 1, 4);

	ellipse(img, Point(300, 350), Size(75, 50), 60, 0, 360, Scalar(0, 0, 0), CV_FILLED, -1);

	ellipse(img, Point(200, 200), Size(25, 80), 0, 0, 360, Scalar(0, 0, 0), 2, 16);

	vector<Point> contour;
	contour.push_back(Point(75, 50));
	contour.push_back(Point(300, 50));
	contour.push_back(Point(350, 200));
	const cv::Point *pts = (const cv::Point*) Mat(contour).data;
	int npts = Mat(contour).rows;

	//polylines(Mat& img, const Point** pts, const int* npts, int ncontours, bool isClosed, const Scalar& color, int thickness = 1, int lineType = 8, int shift = 0)
	polylines(img, &pts, &npts, 1, true, Scalar(0, 210, 100), 1, CV_AA, 0);

	//ellipse(Mat& img, Point center, Size axes, double angle, double startAngle, double endAngle, const Scalar& color, int thickness = 1, int lineType = 8, int shift = 0)
	//for half ellipse
	ellipse(img,  Point(150, 400), Size(30, 30), 90, 0, 180, Scalar(0, 0, 0), 2);

	//rectangle(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness = 1, int lineType = 8, int shift = 0)
	rectangle(img, Point(80, 50), Point(200, 100), Scalar(0, 0, 0), 1, 8, 0);
	//opposite point p1 and p2

	//putText(Mat& img, const string& text, Point org, int fontFace, double fontScale, Scalar color, int thickness = 1, int lineType = 8)
	putText(img, "OpenCV Testing", Point(250, 470), CV_FONT_NORMAL, 1, Scalar(0, 0, 0), 1, 16);
	 
	namedWindow("Image", 1);
	imshow("Image", img);
	waitKey(0);

	destroyWindow("MyWindow");

}

int hninnayecho::ImageProcessing::readingVideoFile(std::string video){

	VideoCapture cap(video); // open the video file for reading

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}

	double fps = cap.get(CV_CAP_PROP_POS_MSEC); //get the frames per seconds of the video

	cout << "Frame per seconds : " << fps << endl;

	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	while (1)
	{
		Mat frame;

		bool bSuccess = cap.read(frame); // read a new frame from video


		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read the frame from video file" << endl;
			break;
		}

		imshow("MyVideo", frame); //show the frame in "MyVideo" window

		if (waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	VideoCapture();

	return 0;
}

int hninnayecho::ImageProcessing::readingVideoCamera(){
	VideoCapture cap(0); // open the video camera no. 0

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video cam" << endl;
		return -1;
	}

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	cout << "Frame size : " << dWidth << " x " << dHeight << endl;

	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	while (1)
	{
		Mat frame;

		bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		imshow("MyVideo", frame); //show the frame in "MyVideo" window

		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	return 0;
}

int hninnayecho::ImageProcessing::readingWritingVideo(){

	VideoCapture cap(0); // open the video camera no. 0

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "ERROR: Cannot open the video file" << endl;
		return -1;
	}

	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
	

	cout << "Frame Size = " << dWidth << "x" << dHeight << endl;

	Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));

	VideoWriter oVideoWriter("E:\\videotesting\\MyVideo.avi", CV_FOURCC('M', 'P', '4', '2'), 20, frameSize, true); //initialize the VideoWriter object 

	if (!oVideoWriter.isOpened()) //if not initialize the VideoWriter successfully, exit the program
	{
		cout << "ERROR: Failed to write the video" << endl;
		return -1;
	}

	while (1)
	{

		Mat frame;

		bool bSuccess = cap.read(frame); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "ERROR: Cannot read a frame from video file" << endl;
			break;
		}

		oVideoWriter.write(frame); //writer the frame into the file

		imshow("MyVideo", frame); //show the frame in "MyVideo" window

		if (waitKey(10) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	return 0;
}

void hninnayecho::ImageProcessing::writeImagetoFile(){

	Mat frame;

	vector<int> compression_params;
	//vector that stores the compression parameters of the image
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	//specify the compression technique
	compression_params.push_back(100); //specify the compression quality

	int photocount = 0; //initialize image counter
	int key;

	VideoCapture cap(0); //open camera no.0  0=internal 1=external
	while ((key = waitKey(30)) != 27) //wait 30 milliseconds and check for esc key
	{
		cap >> frame; //save captured image to frame variable
		imshow("Camera", frame); //show image on window named Camera
		if (key == 'c')
		{
			photocount++;// increment image number for each capture
			imshow("Captured", frame);
			imwrite("E:\\videotesting\\MyImage.jpg", frame, compression_params);
		}

	}
}

void hninnayecho::ImageProcessing::linedetection(std::string image){

	Mat src = imread(image, 0);

	Mat dst, cdst;
	Canny(src, dst, 50, 200, 3);
	cvtColor(dst, cdst, CV_GRAY2BGR);

	//vector<Vec2f> lines;
	// //detect lines
	//HoughLines(dst, lines, 1, CV_PI/180, 200, 0, 0 );

	// draw lines
	/*for( size_t i = 0; i < lines.size(); i++ )
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
		
	}*/
	vector<Vec4i> lines;
	HoughLinesP(dst, lines, 1, CV_PI / 180, 170, 50, 10);
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
	}
	
	imshow("source", src);
	imshow("detected lines", cdst);

	waitKey();
}

void hninnayecho::ImageProcessing::testTutorial(){
	//VideoCapture cap("E:\\WAKU WAKU VIDEO\\Waku Waku Japanese - Language Lesson 1- Meeting People.mp4");
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
			if (area > 500) {
				Rect bounding_rect = boundingRect(contours[i]);
				rectangle(frame, bounding_rect, Scalar(0, 255, 0), 2, 8, 0);

				putText(frame, "detect " + to_string(contours.size()), Point(50, 50), CV_FONT_NORMAL, 1, Scalar(0, 0, 255), 1, 16);
			}
		}

		imshow("MyVideo", frame); //show the frame in "MyVideo" window

		if (waitKey(30) == 27) {

			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
	VideoCapture();
}



