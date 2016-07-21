#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\opencv.hpp>
using namespace std;


namespace sumyat{
	using namespace cv;
	double const thresh = 127;
	double const maxVal = 255;
	double const blockSize = 11;
	Mat img, src, dst1, dst2, dst3, dst4, dst5;
	class ImageProcedure
	{
	public:
		ImageProcedure();
		~ImageProcedure();		
		static void golbalThresholdTest(string imagePath);
		static void adaptiveThresholdTest(string imagePath);

	private:

	};
}
