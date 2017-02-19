#pragma once

#ifndef CARDETECTION_H
#define CARDETECTION_H

#include "opencv2/core.hpp"
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/video/background_segm.hpp"
#include "opencv2/videoio.hpp"

#include <iostream>
#include <array>

#include "pointMath.h"
#include "colorspaceCvt.h"
#include "displayMats.h"
#include "shapeMats.h"

using namespace cv;
using namespace std;

class CarDetection {

private:

	string WINDOW_CARDETECT = "car detect";

	int erodeAmount = 5;
	int dilateAmount = 15;

	int minThresh = 10;
	int maxThresh = 255;

	vector<vector<Point> > contours;
	
	vector<Point> prevPoints;
	vector<Point> currPoints;
	
	vector<Vec4i> hierarchy;

	Mat InputImage, drawOn, lineMat, blob, bgImg, fgImg;
	Mat chans[3];

	Point pointArray[10];
	Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorKNN(100, 400, true);

public:

	Mat getThreshold();

	void carDetect(string imgName, int _minThresh, int _maxThresh);
	void findLines(Mat&a);
	void trackPoints(vector<Point>& foundPoints);
};


#endif // !CARDETECTION_H

