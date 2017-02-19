#include "shapeMats.h"

void RemoveBySize(Mat& a, int minArea) {
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

void ErodeDilate(Mat& a, int ea, int da) {

	if (ea <= 0) { ea = 1; }
	if (da <= 0) { da = 1; }

	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(ea, ea));
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(da, da));

	erode(a, a, erodeElement);
	dilate(a, a, dilateElement);

}