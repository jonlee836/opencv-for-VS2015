#include "thresholdImage.h"

using namespace cv;
using namespace std;

void threshImage::colorspace(Mat& a) {

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	cvtColor(a, cvtMat, CV_BGR2GRAY);
	
	imshow("gray", cvtMat);
	split(cvtMat, LuvChannels);

	blob = cvtMat.clone();

	//threshold_output = LuvChannels[2].clone();

	/*imshow("L channel", LuvChannels[0]);
	imshow("U channel", LuvChannels[1]);
	imshow("V channel", LuvChannels[2]);*/
}

void threshImage::fgbgDetect(Mat& a) {

	if (fgImg.empty()) {
		fgImg.create(a.size(), a.type());
	}

	bg_model->apply(fgImg, blob, true);

	GaussianBlur(blob, blob, Size(5, 5), 3, 3);
	threshold(blob, blob, 100, 255, THRESH_BINARY);
	
	fgImg = a.clone();

	// Why was it like this
	//	a.copyTo(fgImg, blob);
	// in my motion sensor code for the tk1?
	// And why did it work at all?

	//a.copyTo(fgImg);

	bg_model->getBackgroundImage(bgImg);
}

void threshImage::display_thresh() {
	imshow("drawn on", blob);
}

Mat threshImage::getThreshold() {
	return blob;
}