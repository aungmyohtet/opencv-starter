#include "stdafx.h"
#include <iostream>
#include <string>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

namespace myatMoe {
	void hi();
	int testTutorial();

	class AffineTranform
	{
	public:
		AffineTranform();
		~AffineTranform();
		static void affineTransform(std::string imagePath);
	};
}