#include "thresholdImage.h"

using namespace cv;
using namespace std;

void threshImage::colorspace(Mat& a) {

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	cvtColor(a, cvtMat, CV_BGR2HSV);
	split(cvtMat, LuvChannels);

	threshold_output = LuvChannels[2].clone();

	//imshow("L channel", LuvChannels[0]);
	//imshow("U channel", LuvChannels[1]);
	//imshow("V channel", LuvChannels[2]);
}

void threshImage::RemoveBySize(Mat& a, int minArea) {
	Mat temp = a.clone();
	vector<vector <Point> > contours;

	findContours(temp, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	for (int i = 0; i < contours.size(); i++) {
		double area = contourArea(contours[i]);
		if (area <= minArea) {
			drawContours(a, contours, i, Scalar(0), CV_FILLED, 8);
		}
	}
}

void threshImage::display_thresh() {
	imshow("drawn on", threshold_output);
}

Mat threshImage::getThreshold() {
	return threshold_output;
}