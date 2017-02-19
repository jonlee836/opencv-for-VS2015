#include "threshImg.h"

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

void cvt2Chans(Mat& a, vector<Mat>& b, int type) {

	switch (type) {
		case 1:
			cvt2LUV(a);
			split(a, b);
			break;

		case 2:
			cvt2HSV(a);
			split(a, b);
			break;

		case 3:
			cvt2HLS(a);
			split(a, b);
			break;

		case 4:
			cvt2LAB(a);
			split(a, b);
			break;
		
		default:
			cout << "ERROR : int must be between 1 and 4" << endl;
			cout << "1 = LUV" << endl;
			cout << "2 = HSV" << endl;
			cout << "3 = HLS" << endl;
			cout << "4 = LAB" << endl;
	}

}

void adjustContrast(Mat& a, int contrastAdj, int brightAdj) {
	double conVal = contrastAdj * 0.01;
	int briVal = brightAdj - 200;
	a.convertTo(a, -1, conVal, briVal);
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
		Mat ycrcb;

		cvtColor(inputImage, ycrcb, CV_BGR2YCrCb);

		vector<Mat> channels;
		split(ycrcb, channels);

		equalizeHist(channels[0], channels[0]);

		merge(channels, ycrcb);

		cvtColor(ycrcb, inputImage, CV_YCrCb2BGR);
	}
}