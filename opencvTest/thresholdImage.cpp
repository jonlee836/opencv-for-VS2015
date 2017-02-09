#include "thresholdImage.h"

using namespace cv;
using namespace std;

void threshImage::colorspace(Mat& a) {

	cv::imshow("window", a);

	cvtColor(a, a, CV_BGR2HSV);
	//imshow("gray", a);
	split(a, LuvChannels);

	imshow("L channel", LuvChannels[0]);
	imshow("U channel", LuvChannels[1]);
	imshow("V channel", LuvChannels[2]);

}