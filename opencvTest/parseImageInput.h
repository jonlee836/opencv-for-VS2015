#pragma once

#ifndef PARSEIMAGEINPUT_H
#define PARSEIMAGEINPUT_H

#include <iostream>
#include <vector>
#include <string>
#include<conio.h> 
#include <filesystem>
#include <Windows.h>
#include <conio.h>

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <experimental/filesystem> 

using namespace std;
namespace fs = std::tr2::sys;

class parseImageInput {

private:

	vector <string> imgNames;

	unsigned int totalFrames = 0;

	int currFramePos = -1;
	int Input_Width = -1;
	int Input_Height = -1;

	string filepath;

public:

	parseImageInput(string filepath_);

	vector<string> getfiles(wchar_t *folder);
	//int get_filenames();

};

#endif // !PARSEIMAGEINPUT_H
