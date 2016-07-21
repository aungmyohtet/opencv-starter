#include "stdafx.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

namespace smoothingProc {
	using namespace cv;

	Mat src;
	Mat dst;
	class SmoothingProcessor {
		private :

		public :
			SmoothingProcessor();
			~SmoothingProcessor();
			int HomogeneousSmoothing(std::string imagePath);
			int GaussianSmoothing(std::string imagePath);
			int MedianSmoothing(std::string imagePath);
			int BilateralSmoothing(std::string imagePath);
	};	
}