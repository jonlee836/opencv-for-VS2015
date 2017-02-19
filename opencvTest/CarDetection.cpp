#include "CarDetection.h"

void CarDetection::carDetect(string imgName){

	img = imread(imgName);
	
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	resize(img, img, Size(640, 480));

	imshow("input", img);
	drawOn = img.clone();

	//medianBlur(img, img, 5);
	imshow("after  blur", img);

	cvt2GRAY(img);
	adjustContrast(img, iValueForContrast, iValueForBrightness);
	GaussianBlur(img, img, Size(5, 5), 3.5, 3.5);
	
	if (fgImg.empty()) {
		fgImg.create(img.size(), img.type());
	}

	bg_model->apply(img, blob, 0);

	threshold(blob, blob, minThresh, maxThresh, THRESH_BINARY);

	imshow("blob before", blob);

	fgImg = Scalar::all(0);
	img.copyTo(fgImg, blob);

	bg_model->getBackgroundImage(bgImg);

	Mat bgImgCopy = img.clone();
	findSolidLines(bgImgCopy);

	//threshold(bgImg, bgImgCopy, minThresh, maxThresh, THRESH_BINARY);
	//imshow("bgImg thresh", bgImgCopy);

	//RemoveBySize(blob, 200);

	ErodeDilate(blob, erodeAmount, dilateAmount);
	findContours(blob, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	imshow("blob after", blob);
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

	imshow(WINDOW_CARDETECT, drawOn);
}

void CarDetection::trackPoints(vector<Point>& a) {
	
}

void CarDetection::findSolidLines(Mat& a) {
	vector<Vec4f> lines;

	/*
	HoughLines

	arg 1.) input image
	arg 2.) output lines

	Each line is represented by a 2 element vector of rho and theta.
	rho is the distance from coordinate origin (0,0 aka the top left corner of the image. This is just how opencv works)
	
	arg 3.) rho : Distance resolution of the accumulator in pixels.
	arg 4.) theta : Angle resolution of the accumulator in radians.
	arg 5.) threshold : Only those lines with X number of votes
	*/
	Canny(a, a, 50, 150);
	//HoughLines(a, lines, 1, CV_PI / 180, 150);
	HoughLinesP(a, lines, 5, CV_PI / 180, 80, 30, 50);

	for (size_t i = 0; i < lines.size(); i++) {

		Point pt1, pt2;

		float rho = lines[i][0];
		float theta = lines[i][1];
					
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;

		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));

		line(drawOn, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(255, 255, 255), 3, 8);
		//line(drawOn, pt1, pt2, Scalar(255,255,255), 1, CV_AA);
	}
}

Mat CarDetection::getThreshold() {
	return blob;
}