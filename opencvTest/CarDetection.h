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

	const string tbCar = "car detect trackbar";
	const string nw_cardetect = "car detect";
	const string nw_blur = "blur";
	const string nw_thresh_before = "thresh blobs before";
	const string nw_thresh_after = "thresh blobs after";
	const string nw_canny = "canny lines";

	bool showAllWindows = false;

	int showAll = 0;
	int frame = 0;

	const int maxNumbShapes = 20;
	const int CarCountDistanceTolerance = 40;
	const int CarMaxCount = 7; // car moved 7 frames in a row
	
	int ContourRetreivalMode = 0;
	int ContourApproximationMethods = 2;

	int minThresh = 250;
	int maxThresh = 255;
	int bgThresh = 400;

	int iValueForContrast = 400;
	int iValueForBrightness = 0;

	int erodeAmount = 0;
	int dilateAmount = 15;

	int linesRho = 1;
	int linesTheta = 180;
	int linesThresh = 40;
	int linesMinLength = 40;
	int linesMaxGap = 360;

	int cannyThresh1 = 50;
	int cannyThresh2 = 150;

	int minD1 = 60; int maxD1 = 360;
	int minD2 = 240; int maxD2 = 300;

	const double getR = CV_PI / 180;
	const double getD = 180 / CV_PI;
	const int DEGREES = 360;

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	vector<Point> currPoints, prevPoints;
	vector<vector<Point> > foundPoints;

	Mat img, drawOn, lineMat, blob, bgImg, fgImg;
	Mat chans[3];

	Point pointArray[10];
	Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2(50);

public:

	CarDetection::CarDetection() {

		namedWindow(tbCar, WINDOW_NORMAL);

		namedWindow(nw_cardetect, WINDOW_NORMAL);
		namedWindow(nw_blur, WINDOW_NORMAL);
		namedWindow(nw_thresh_before, WINDOW_NORMAL);
		namedWindow(nw_thresh_after, WINDOW_NORMAL);
		namedWindow(nw_canny, WINDOW_NORMAL);

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
		createTrackbar("show all", tbCar, &showAll, 1);

		createTrackbar("ContourRetreivalMode", tbCar, &ContourRetreivalMode, 0);
		createTrackbar("ContourApproximationMethods", tbCar, &ContourApproximationMethods, 2);
		createTrackbar("bg thresh", tbCar, &bgThresh, 2000);

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

	void carDetect(Mat& a);
	void findSolidLines(Mat&a);
	void trackPoints(vector<Point>& foundPoints);
	
};


#endif // !CARDETECTION_H

