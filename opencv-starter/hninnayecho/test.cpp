#include "stdafx.h"
#include "hninnayecho/hninnayecho.h"
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;


void hninnayecho::ImageProcessing::test(){
	
	int a = saturate_cast<uchar>(266);
	cout << a << endl;
	cout << "testing";
}


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
