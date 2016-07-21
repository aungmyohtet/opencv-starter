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

int hninnayecho::ImageProcessing::writeImagetoFile(){
	Mat img(650, 600, CV_16UC3, Scalar(0, 50000, 50000)); //create an image ( 3 channels, 16 bit image depth, 650 high, 600 wide, (0, 50000, 50000) assigned for Blue, Green and Red plane respectively. )

	if (img.empty()) //check whether the image is loaded or not
	{
		cout << "ERROR : Image cannot be loaded..!!" << endl;
		//system("pause"); //wait for a key press
		return -1;
	}

	vector<int> compression_params; //vector that stores the compression parameters of the image

	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY); //specify the compression technique

	compression_params.push_back(98); //specify the compression quality



	bool bSuccess = imwrite("E:\\videotesting\\TestImage.jpg", img, compression_params); //write the image to file



	if (!bSuccess)

	{

		cout << "ERROR : Failed to save the image" << endl;

		//system("pause"); //wait for a key press

	}

	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	imshow("MyWindow", img); //display the image which is stored in the 'img' in the "MyWindow" window

	waitKey(0);  //wait for a keypress

	destroyWindow("MyWindow"); //destroy the window with the name, "MyWindow"
}
