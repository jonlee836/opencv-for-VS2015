#pragma once

#ifndef THRESHOLDIMAGE_H
#define THRESHOLDIMAGE_H

#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <array>

using namespace cv;
using namespace std;

class threshImage {

private:

	Mat threshold_output, cvtMat;
	Mat LuvChannels[3];
	Point pointArray[10];

public:

	void colorspace(Mat& a);
	void RemoveBySize(Mat& a, int minArea);
	void display_thresh();

	Mat getThreshold();
};


#endif // !THRESHOLDIMAGE_H

