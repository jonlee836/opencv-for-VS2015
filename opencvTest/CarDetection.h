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

	int frame = 0;

	string WINDOW_CARDETECT = "car detect";
	const string tbCar = "car detect trackbar";
	
	int minThresh = 10;
	int maxThresh = 255;

	int iValueForContrast = 400;
	int iValueForBrightness = 0;

	int erodeAmount = 5;
	int dilateAmount = 15;

	int linesRho = 1;
	int linesTheta = 180;
	int linesThresh = 125;
	int linesMinLength = 40;
	int linesMaxGap = 200;

	int cannyThresh1 = 50;
	int cannyThresh2 = 150;

	int minD1 = 60; int maxD1 = 120;
	int minD2 = 240; int maxD2 = 300;

	const double getR = CV_PI / 180;
	const double getD = 180 / CV_PI;
	const int DEGREES = 360;

	vector<vector<Point> > contours;
	
	vector<Point> prevPoints, currPoints;
	vector<Vec4i> hierarchy;

	Mat img, drawOn, lineMat, blob, bgImg, fgImg;
	Mat chans[3];

	Point pointArray[10];
	Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorKNN(500, 400, true);

public:

	CarDetection::CarDetection() {

		namedWindow(tbCar, WINDOW_NORMAL);

		createTrackbar("minThresh", tbCar, &minThresh, 255);
		createTrackbar("maxThresh", tbCar, &maxThresh, 255);

		createTrackbar("contrast", tbCar, &iValueForContrast, 400);
		createTrackbar("brightness", tbCar, &iValueForBrightness, 400);
		
		createTrackbar("erode", tbCar, &erodeAmount, 20);
		createTrackbar("dilate", tbCar, &dilateAmount, 20);

		createTrackbar("Rho", tbCar, &linesRho, 200);
		createTrackbar("Theta", tbCar, &linesTheta, 200);

		createTrackbar("Thresh", tbCar, &linesThresh, 300);
		createTrackbar("MinLength", tbCar, &linesMinLength, 300);

		createTrackbar("MaxGap", tbCar, &linesMaxGap, 300);

		createTrackbar("canny thresh1", tbCar, &cannyThresh1, 300);
		createTrackbar("canny thresh2", tbCar, &cannyThresh2, 300);

		createTrackbar("minD 1", tbCar, &minD1, DEGREES);
		createTrackbar("maxD 1", tbCar, &maxD1, DEGREES);
		createTrackbar("minD 2", tbCar, &minD2, DEGREES);
		createTrackbar("maxD 2", tbCar, &maxD2, DEGREES);

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

