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
#include "threshImg.h"
#include "displayMats.h"
#include "shapeMats.h"

using namespace cv;
using namespace std;

class CarDetection {

private:

	string WINDOW_CARDETECT = "car detect";
	const string TRACKBAR_CARDETECT = "car detect trackbar";
	
	int minThresh = 10;
	int maxThresh = 255;

	int iValueForContrast = 400;
	int iValueForBrightness = 0;

	int erodeAmount = 5;
	int dilateAmount = 15;

	vector<vector<Point> > contours;
	
	vector<Point> prevPoints, currPoints;
	vector<Vec4i> hierarchy;

	Mat img, drawOn, lineMat, blob, bgImg, fgImg;
	Mat chans[3];

	Point pointArray[10];
	Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorKNN(500, 400, true);

public:
	
	CarDetection::CarDetection() {

		namedWindow(TRACKBAR_CARDETECT);

		createTrackbar("minThresh", TRACKBAR_CARDETECT, &minThresh, 255);
		createTrackbar("maxThresh", TRACKBAR_CARDETECT, &maxThresh, 255);

		createTrackbar("contrast", TRACKBAR_CARDETECT, &iValueForContrast, 400);
		createTrackbar("brightness", TRACKBAR_CARDETECT, &iValueForBrightness, 400);
		
		createTrackbar("erode", TRACKBAR_CARDETECT, &erodeAmount, 20);
		createTrackbar("dilate", TRACKBAR_CARDETECT, &dilateAmount, 20);

	}

	/*void MyCallbackForBrightness(int iValueForBrightness, void *userData) {
		Mat dst;
		int iValueForContrast = *(static_cast<int*>(userData));

		int iBrightness = iValueForBrightness - 50;
		double dContrast = iValueForContrast / 50.0;
		
		if (!img.empty()) {
			img.convertTo(dst, -1, dContrast, iBrightness);
		}
		
	}*/

	Mat getThreshold();

	void carDetect(string imgName);
	void findSolidLines(Mat&a);
	void trackPoints(vector<Point>& foundPoints);
};


#endif // !CARDETECTION_H

