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

void cvt2EqualizeIntensity(Mat& inputImage) {
	if (inputImage.channels() >= 3) {

		cvtColor(inputImage, inputImage, CV_BGR2Luv);

		vector<Mat> channels;
		split(inputImage, channels);

		equalizeHist(channels[0], channels[0]);
		merge(channels, inputImage);

		cvtColor(inputImage, inputImage, CV_Luv2BGR);
	}
}