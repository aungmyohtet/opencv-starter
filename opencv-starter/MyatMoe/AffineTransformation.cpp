#include "stdafx.h"
#include "MyatMoe\MyatMoe.h"

using namespace myatMoe;
using namespace cv;
using namespace std;

AffineTranform::AffineTranform()
{
}

AffineTranform::~AffineTranform()
{
}

void AffineTranform::affineTransform(string imagePath) {

	Point2f srcThreePoints[3], dstThreePoints[3];

	Mat warp_mat(2, 3, CV_32FC1);
	
	/// Load the image
	Mat source = imread(imagePath, 1);	

	/** Rotating the image before Warp */

	/// Compute a rotation matrix with respect to the center of the image
	Point center = Point(source.cols / 2, source.rows / 2);
	//Point center = Point(source.cols, source.rows);
	double angle = -50.0;
	double scale = 1.0;

	/// Get the rotation matrix with the specifications above
	Mat rot_mat = getRotationMatrix2D(center, angle, scale);

	Mat warp_rotate_dst;
	/// Rotate the source image
	warpAffine(source, warp_rotate_dst, rot_mat, source.size(), INTER_LINEAR, BORDER_REPLICATE);

	/// Set the dst image the same type and size as src
	Mat warp_dst = Mat::zeros(source.rows, source.cols, source.type());

	/// Set your 3 points to calculate the  Affine Transform
	/*srcThreePoints[0] = Point2f(0, 0);
	srcThreePoints[1] = Point2f(static_cast<float>(source.cols - 1), 0);
	srcThreePoints[2] = Point2f(0, (static_cast<float>(source.rows - 1)));*/

	srcThreePoints[0] = Point2f(0, 0);
	srcThreePoints[1] = Point2f(static_cast<float>(source.cols - 1), 0);
	srcThreePoints[2] = Point2f(0, (static_cast<float>(source.rows - 1)));

	dstThreePoints[0] = Point2f(source.cols*0.0f, source.rows*0.33f);
	dstThreePoints[1] = Point2f(source.cols*0.85f, source.rows*0.25f);
	//dstThreePoints[2] = Point2f(source.cols*0.35f, source.rows);
	dstThreePoints[2] = Point2f(source.cols*0.15f, source.rows*0.7f);

	/// Get the Affine Transform
	warp_mat = getAffineTransform(srcThreePoints, dstThreePoints);

	/// Apply the Affine Transform just found to the src image
	warpAffine(source, warp_dst, warp_mat, warp_dst.size());

	/// Show what you got
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", source);

	namedWindow("Rotate Image", CV_WINDOW_AUTOSIZE);
	imshow("Rotate Image", warp_rotate_dst);

	namedWindow("Transformed Image", CV_WINDOW_AUTOSIZE);
	imshow("Transformed Image", warp_dst);

	/// Wait until user exits the program
	waitKey(0);
}

/*
	void warpAffine( InputArray src, OutputArray dst, InputArray M, Size dsize,
					int flags = INTER_LINEAR, int bordreMode=BORDER_CONSTANT, const Scalar& borderValue=Scalar() )
	This OpenCV function applies affine transformation to an image.

	Arguments - 
	src - Source Image
	dst - Destination image which should have the same type as the source image(The transformed image is stored in this location)
	M - 2x3 affine transformation matrix
	dsize - Size of the destination image
	flags - Interpolation methods 
	borderMode - pixel extrapolation method. 
	(Try these values; BORDER_REPLICATE, BORDER_CONSTANT, BORDER_REFLECT, BORDER_WRAP, BORDER_REFLECT_101, BORDER_TRANSPARENT and BORDER_ISOLATED)
	borderValue - If you use BORDER_CONSTANT for borderMode, this argument define the value used for the border
*/

/*
	Mat getRotationMatrix2D( Point2f center, double angle, double scale )

	This function returns 2x3 affine transformation matrix for the 2D rotation.

	Arguments -

	center - The center of the rotation of the the source image. 
	angle - Angle of rotation in degrees (Positive values for counter-clockwise direction and negative values for clockwise rotation)
	scale - The scaling factor of the image. (Scaling factor of 1 means its original size)
*/