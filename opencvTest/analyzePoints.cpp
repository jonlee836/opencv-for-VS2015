#include "analyzePoints.h"

using namespace cv;
using namespace std;
	
void analyzePoints::findPoints(Mat& drawOn, Mat& threshold_output) {

	RemoveBySize(threshold_output, 50);

	//Mat dilateElement = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(5, 5));
	erode(threshold_output, threshold_output, erodeElement);

	//dilate(threshold_output, threshold_output, dilateElement);

	//imshow("binary", threshold_output);


	findContours(threshold_output, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	vector<vector<Point> >hull(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		convexHull(Mat(contours[i]), hull[i], false);
	}

	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours[i], 0, true);

		//drawContours(drawOn, contours, i, Scalar(255, 0, 0), 2, 8, vector<Vec4i>(), 0, Point());
		drawContours(drawOn, hull, i, Scalar(0, 0, 255), 4, 8, vector<Vec4i>(), 0, Point());
	}

	// Show in a window
	imshow("on original", drawOn);

}

Point analyzePoints::getMidpoint(Point a, Point b){  
  return Point((a.x+b.x)/2, (a.y+b.y)/2);
}

void analyzePoints::RemoveBySize(Mat& a, int minArea) {
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