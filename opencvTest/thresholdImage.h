#pragma once

#ifndef THRESHOLDIMAGE_H
#define THRESHOLDIMAGE_H

#include "opencv2/core.hpp"
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/video/background_segm.hpp"
#include "opencv2/videoio.hpp"

#include <iostream>
#include <array>

using namespace cv;
using namespace std;

class threshImage {

private:

	Mat blob, cvtMat, bgImg, fgImg;
	Mat chans[3];
	Point pointArray[10];

	Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorKNN(100, 400, true);

public:

	Mat getThreshold();

	void colorspace(Mat& a);
	void carDetect(Mat& a);
	void findLines(Mat& a);

	void showChans();
};


#endif // !THRESHOLDIMAGE_H

