#pragma once

#ifndef CARDETECTION_H
#define CARDETECTION_H

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

	// POINT COUNTER
	//  --------------------------------------------------------------------------------------------------

	// max distance between points, between frames
	static const int disTol = 15;

	static const int fpLost_minIndex = 2;
	static const int fpLostMin = 3;
	static const int fpLostMax = 10;

	static const int fpRow = 30; 	// fpRow max amount of points it can track at a time
	static const int fpCol = 7; // points tracked
	
	bool fpConfirmed[fpRow];
	/*
		keeps track of whether or not foundPoints has written over itself because it reached the point limit aka fpCol
	*/

	int fpIndex[fpRow];
	/*
		if foundPoints[fpRow][0] is non-neg aka Point(-1,-1)
		fpIndex keeps track of the next non-neg
		therefore fpIndex[5] = 2 
		means foundPoints[5][0] through foundPoints[5][2] is non neg
	*/
	
	int fpLc[fpRow];
	/*
		If fpLc[fpRow] prevents (hopefully) the tracker from getting confused if it loses a target for a few frames
	*/

	int fpAngles_writeOverIndex = 0;
	/*
		When fpAngles[fpRow] 
	*/

	float fpAngles[fpRow];
	/*		
		Measures the angle of objects as they travel in the image
	*/

	Point fpLastKnown[fpRow];
	Point foundPoints[fpRow][fpCol];

	vector<Point> currPoints, prevPoints;

	Point neg = Point(-1, -1);
	int CarsCounted = 0;
	
	//-----------------------------------------------------------------------------------------------------------------

	Vec4i carlines[fpRow];

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
	int linesThresh = 160;
	int linesMinLength = 40;
	int linesMaxGap = 360;

	int cannyThresh1 = 50;
	int cannyThresh2 = 150;

	int minD1 = 60;
	int maxD1 = 360;

	int minD2 = 240;
	int maxD2 = 300;

	const double getR = CV_PI / 180;
	const double getD = 180 / CV_PI;

	const int DEGREES = 360;

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	Mat img, drawOn, lineMat, blob, bgImg, fgImg;
	Mat chans[3];

	Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2(50);

public:

	CarDetection::CarDetection() {
	
		//resetFp();
		// fill array with -1,-1 to note it's empty
		/*Point a = Point(-1, -1);
		for (int i = 0; i < foundPoints.size(); i++) {
			for (int k = 0; k < foundPoints[i].size(); k++) {
				foundPoints[i][k] = a;
				cout << foundPoints[i][k] << endl;
			}
		}*/

		for (int r = 0; r < fpRow; r++) {
			for (int c = 0; c < fpCol; c++) {
				foundPoints[r][c] = Point(-1, -1);
			}
			fpLc[r] = 0;
			fpIndex[r] = -1;
			fpConfirmed[r] = false;
			fpLastKnown[r] = Point(-1, -1);
		}

		for (int c = 0; c < fpRow; c++) {
			fpAngles[c] = -1.0;
		}

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
	void trackPoints(vector<Point>& foundPoints, Mat& draw);
	void findMotionLines(int r);

	int findFpNonNegIndex();

	void resetFp();
	void resetFpRow(int r);
	void setFp_with_Vp(vector<Point>& vp);
	void findVp(vector<Point>& vp);
	

};


#endif // !CARDETECTION_H

