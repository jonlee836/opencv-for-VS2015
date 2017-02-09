#include "thresholdImage.h"

using namespace cv;
using namespace std;

void threshImage::colorspace(Mat& a) {

	cvtColor(a, a, CV_BGR2Luv);
	split(a, LuvChannels);

	imshow("L channel", LuvChannels[0]);
	imshow("U channel", LuvChannels[1]);
	imshow("V channel", LuvChannels[2]);

}