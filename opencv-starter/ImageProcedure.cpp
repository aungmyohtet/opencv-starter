#include "stdafx.h"
#include "ImageProcedure.h"
using namespace std;
using namespace cv;

zipc::ImageProcedure::ImageProcedure() {

}

zipc::ImageProcedure::~ImageProcedure() {

}

void zipc::ImageProcedure::displayImage(std::string imagePath) {
	Mat img = imread(imagePath, CV_LOAD_IMAGE_UNCHANGED); //read the image data from the file path given

	if (img.empty()) //check whether the image is loaded or not
	{
		cout << "Error : Image cannot be loaded..!!" << endl;
		//system("pause"); //wait for a key press
		return;
	}

	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	imshow("MyWindow", img); //display the image which is stored in the 'img' in the "MyWindow" window

	waitKey(0); //wait infinite time for a keypress

	destroyWindow("MyWindow"); //destroy the window with the name, "MyWindow"
}
