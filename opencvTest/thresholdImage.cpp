#include "thresholdImage.h"

using namespace cv;
using namespace std;

void threshImage::setvalues(int _minThresh, int _maxThresh) {
	minThresh = _minThresh;
	maxThresh = _maxThresh;
}

void threshImage::colorspace(Mat& a) {

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	cvtColor(a, cvtMat, CV_BGR2GRAY);
	
	imshow("gray", cvtMat);
	split(cvtMat, chans);

	blob = cvtMat.clone();

	//threshold_output = LuvChannels[2].clone();

	/*imshow("L channel", LuvChannels[0]);
	imshow("U channel", LuvChannels[1]);
	imshow("V channel", LuvChannels[2]);*/
}

void threshImage::carDetect(Mat& a) {

	if (fgImg.empty()) {
		fgImg.create(a.size(), a.type());
	}

	bg_model->apply(a, blob, 0);

	//GaussianBlur(blob, blob, Size(5, 5), 3.5, 3.5);
	threshold(blob, blob, minThresh, maxThresh, THRESH_BINARY);
	
	fgImg = Scalar::all(0);
	a.copyTo(fgImg, blob);

	bg_model->getBackgroundImage(bgImg);
	//findLines(a);

}


void threshImage::findLines(Mat& a) {
	cvtColor(a, cvtMat, CV_BGR2HSV);
	split(cvtMat, chans);
}

void threshImage::showChans() {

	if (!chans[0].empty()) {
		imshow("1", chans[0]);
		imshow("2", chans[1]);
		imshow("3", chans[2]);
	}
}

Mat threshImage::getThreshold() {
	return blob;
}