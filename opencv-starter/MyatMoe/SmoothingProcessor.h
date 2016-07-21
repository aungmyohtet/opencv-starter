#include "stdafx.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

namespace smoothingProc {

	
	class SmoothingProcessor {
		private :
			cv::Mat src;
			cv::Mat dst;
		public :
			SmoothingProcessor();
			~SmoothingProcessor();
			void setSrc(std::string path);
			cv::Mat getSrc();
			void setDst(cv::Mat source);
			cv::Mat getDst();
			int HomogeneousSmoothing(std::string imagePath);
			int GaussianSmoothing(std::string imagePath);
			int MedianSmoothing(std::string imagePath);
			int BilateralSmoothing(std::string imagePath);
			void displayImages(std::string title);
	};	
}