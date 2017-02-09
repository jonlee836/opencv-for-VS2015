#pragma once

#ifndef THRESHOLDIMAGE_H
#define THRESHOLDIMAGE_H

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>

#include <iostream>
#include <array>

using namespace cv;
using namespace std;

class threshImage {

private:

	Mat LuvChannels[3];
	Point pointArray[10];

public:

	void colorspace(Mat& a);

};


#endif // !THRESHOLDIMAGE_H

