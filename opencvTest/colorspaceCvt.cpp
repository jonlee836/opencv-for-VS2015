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
