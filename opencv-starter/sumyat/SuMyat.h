#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\opencv.hpp>
using namespace std;


namespace sumyat{
	using namespace cv;
	static double thresh = 127.0;
	static double maxVal = 255.0;
	static int blockSize = 11;
	const int alpha_slider_max = 100;
	static int alpha_slider;
	static double alpha;
	static double beta;
	static Mat img, src, dst1, dst2, dst3, dst4, dst5;
	class ImageProcedure
	{
	public:
		ImageProcedure();
		~ImageProcedure();		
		static void golbalThresholdTest(string imagePath);
		static void adaptiveThresholdTest(string imagePath);	
		static void mouseEventTest(string imagePath);
		static void trackBarTest(string imagePath1,string imagePath2);

	private:

	};
}
