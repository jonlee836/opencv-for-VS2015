#pragma once

#ifndef PARSEIMAGEINPUT_H
#define PARSEIMAGEINPUT_H

#include <iostream>
#include <string>
#include<conio.h> 

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <experimental/filesystem> 

using namespace cv;
using namespace std;

class parseImageInput {

private:

	unsigned int totalFrames = 1;
	int currFramePos = -1;
	int Input_Width = -1;
	int Input_Height = -1;

	String filepath;

	vector <string> imagepathArray;

public:

	parseImageInput(String filepath_);

	int get_filenames();

};

#endif // !PARSEVIDEOINPUT_H
