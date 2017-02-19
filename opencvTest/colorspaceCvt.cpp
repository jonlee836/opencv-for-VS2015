#include "colorspaceCvt.h"

void cvt2HSV(Mat& a) {
	cvtColor(a, a, CV_BGR2HSV);
}

void cvt2HLS(Mat& a) {
	cvtColor(a, a, CV_BGR2HLS);
}

void cvt2LUV(Mat& a) {
	cvtColor(a, a, CV_BGR2Luv);
}

void cvt2LAB(Mat& a) {
	cvtColor(a, a, CV_BGR2Lab);
}

void cvt2GRAY(Mat& a) {
	cvtColor(a, a, CV_BGR2GRAY);
}

void cvt2EqualizeImg(Mat& a) {

	vector<Mat> chans;

	split(a, chans);

	for (int i = 0; i < 3; i++) {
		chans[i].convertTo(chans[i], CV_8UC1);
		equalizeHist(chans[i], chans[i]);
	}

	merge(chans, a);

}

Mat cvt2EqualizeIntensity(const Mat& inputImage) {
	if (inputImage.channels() >= 3) {
		Mat ycrcb;

		cvtColor(inputImage, ycrcb, CV_BGR2YCrCb);

		vector<Mat> channels;
		split(ycrcb, channels);

		equalizeHist(channels[0], channels[0]);

		Mat result;
		merge(channels, ycrcb);

		cvtColor(ycrcb, result, CV_YCrCb2BGR);

		return result;
	}
	return Mat();
}