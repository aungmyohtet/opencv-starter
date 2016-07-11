#ifndef ZIPC_IMAGEPROCEDURE_H
#define ZIPC_IMAGEPROCEDURE_H

#include "stdafx.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"

namespace zipc {
	class ImageProcedure
	{
	public:
		ImageProcedure();
		~ImageProcedure();
		static void displayImage(std::string imagePath);

	private:

	};

}

#endif