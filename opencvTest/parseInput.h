#pragma once

#ifndef PARSEINPUT_H
#define PARSEINPUT_H

#include <iostream>
#include <string>
#include<conio.h> 

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\videoio\videoio.hpp>

using namespace cv;
using namespace std;

class parseInput {

private:

	int frameCount = -1;
	int currFramePos = -1;
	int Input_Width = -1;
	int Input_Height = -1;

	String filepath;

	VideoCapture InputStream;

public:

	parseInput(String filepath_);

	bool check_filepath();
	bool isStreamOpen();

	int getCurrframe();

	Mat getVideoInput();

};

#endif // !PARSEINPUT_H
