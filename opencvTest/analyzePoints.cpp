#include "analyzePoints.h"
#include "pointMath.h"

void analyzePoints::findPoints(Mat& drawOn, Mat& threshold_output) {

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	RemoveBySize(threshold_output, 200);

	//Mat dilateElement = getStructuringElement(MORPH_RECT, Size(5, 5));
	//Mat erodeElement = getStructuringElement(MORPH_RECT, Size(25, 25));
	//erode(threshold_output, threshold_output, erodeElement);
	//dilate(threshold_output, threshold_output, dilateElement);

	//imshow("binary", threshold_output);

	findContours(threshold_output, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	vector<vector<Point> >hull(contours.size());

	for (int i = 0; i < contours.size(); i++){
		convexHull(Mat(contours[i]), hull[i], false);
	}

	for (int i = 0; i < contours.size(); i++)
	{
		/*approxPolyDP(Mat(contours[i]), contours[i], 0, true);
		drawContours(drawOn, contours, i, Scalar(255, 0, 0), 2, 8, vector<Vec4i>(), 0, Point());*/
		drawContours(drawOn, hull, i, Scalar(0, 0, 255), 2, 8, vector<Vec4i>(), 0, Point());
		Point center = getShapeCenter(contours[i]);

		circle(drawOn, center, 2, Scalar(100, 255, 0), 2, 8, 0);

	}

	// Show in a window
	imshow("on original", drawOn);

}
//circle(Mat& img, Point center, int radius, const Scalar& color, int thickness = 1, int lineType = 8, int shift = 0)¶