#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2\opencv.hpp>
using namespace std;

namespace sumyat{
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
