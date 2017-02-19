#include "CarDetection.h"

void CarDetection::carDetect(string imgName,int _minThresh, int _maxThresh){

	minThresh = _minThresh;
	maxThresh = _maxThresh;

	InputImage = imread(imgName);
	
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	resize(InputImage, InputImage, Size(640, 480));

	imshow("input image before", InputImage);

	cvt2EqualizeIntensity(InputImage);

	//imshow("input equalized", InputImage);

	drawOn = InputImage.clone();

	if (fgImg.empty()) {
		fgImg.create(InputImage.size(), InputImage.type());
	}

	bg_model->apply(InputImage, blob, 0);

	GaussianBlur(blob, blob, Size(5, 5), 3.5, 3.5);
	threshold(blob, blob, minThresh, maxThresh, THRESH_BINARY);
	
	fgImg = Scalar::all(0);
	InputImage.copyTo(fgImg, blob);

	bg_model->getBackgroundImage(bgImg);

	RemoveBySize(blob, 200);

	ErodeDilate(blob, erodeAmount, dilateAmount);

	findContours(blob, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	vector<vector<Point> >hull(contours.size());

	for (int i = 0; i < contours.size(); i++) {
		convexHull(Mat(contours[i]), hull[i], false);
	}

	for (int i = 0; i < contours.size(); i++) {
		
		approxPolyDP(Mat(contours[i]), contours[i], 0, true);
		drawContours(drawOn, contours, i, Scalar(255, 0, 0), 2, 8, vector<Vec4i>(), 0, Point());
		drawContours(drawOn, hull, i, Scalar(0, 0, 255), 2, 8, vector<Vec4i>(), 0, Point());
		Point center = getShapeCenter(contours[i]);

		circle(drawOn, center, 2, Scalar(100, 255, 0), 2, 8, 0);
	}

	displayMat(WINDOW_CARDETECT, drawOn);

}

void CarDetection::trackPoints(vector<Point>& a) {
	
}

void CarDetection::findLines(Mat& a) {
	cvtColor(a, lineMat, CV_BGR2HSV);
	split(lineMat, chans);
}

Mat CarDetection::getThreshold() {
	return blob;
}