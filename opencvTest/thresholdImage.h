#pragma once

#ifndef THRESHOLDIMAGE_H
#define THRESHOLDIMAGE_H

#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/video/background_segm.hpp"
#include "opencv2/videoio.hpp"

#include <iostream>
#include <array>

using namespace cv;
using namespace std;

class threshImage {

private:

	Mat blob, cvtMat, bgImg, fgImg;
	Mat LuvChannels[3];
	Point pointArray[10];

	Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorKNN().dynamicCast<BackgroundSubtractor>();

public:

	Mat getThreshold();

	void colorspace(Mat& a);
	void fgbgDetect(Mat& a);

	void display_thresh();

};


#endif // !THRESHOLDIMAGE_H

