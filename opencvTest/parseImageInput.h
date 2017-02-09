#pragma once

#ifndef PARSEIMAGEINPUT_H
#define PARSEIMAGEINPUT_H

#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include<conio.h> 

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <experimental/filesystem> 

namespace fs = std::tr2::sys;

using namespace cv;
using namespace std;

class parseImageInput {

private:

	vector <string> imgNames;

	unsigned int totalFrames = 0;

	int currFramePos = -1;
	int Input_Width = -1;
	int Input_Height = -1;

	String filepath;

public:

	parseImageInput(String filepath_);

	vector<string> getfiles(string folder);
	int get_filenames();

};

#endif // !PARSEVIDEOINPUT_H
