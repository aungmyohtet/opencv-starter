#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
namespace hninnayecho {
	class ImageProcessing
	{
	public:
		ImageProcessing();
		~ImageProcessing();
		static void changeBrightness(std::string image);
		static void test();

	};

}