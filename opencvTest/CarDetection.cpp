#include "CarDetection.h"

void CarDetection::carDetect(Mat& a){
	
	img = a.clone();

	if (showAll == 1) { showAllWindows = true; }
	else { showAllWindows = false; }
		
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	resize(img, img, Size(640, 480));

	imshow("input", img);
	drawOn = img.clone();
	
	cvt2GRAY(img);
	GaussianBlur(img, img, Size(5, 5), 3.5, 3.5);

	//cvt2EqualizeIntensity(img);
	adjustContrast(img, iValueForContrast, iValueForBrightness);
	//medianBlur(img, img, 11);

	DOH(showAllWindows, nw_blur, img);

	/*const string tbCar = "car detect trackbar";

	const string nw_cardetect = "car detect";
	const string nw_blur = "blur";
	const string nw_thresh_before = "thresh blobs";
	const string nw_canny = "canny lines";
		*/
	
	if (fgImg.empty()) {
		fgImg.create(img.size(), img.type());
	}

	bg_model->apply(img, blob);

	fgImg = Scalar::all(0);
	img.copyTo(fgImg, blob);
	bg_model->getBackgroundImage(bgImg);

	//imshow("bgimg", bgImg);

	threshold(blob, blob, minThresh, maxThresh, THRESH_BINARY);

	DOH(showAllWindows, nw_thresh_before, blob);

	findSolidLines(img);

	DOH(showAllWindows, nw_canny, img);

	RemoveBySize(blob, 500);
	ErodeDilate(blob, erodeAmount, dilateAmount, 2);
	findContours(blob, contours, ContourRetreivalMode, CV_CHAIN_APPROX_SIMPLE);
	
	/*  CV_RETR_EXTERNAL = 0,
		CV_RETR_LIST = 1,
		CV_RETR_CCOMP = 2,
		CV_RETR_TREE = 3,
		CV_RETR_FLOODFILL = 4 */
	
	/*	CV_CHAIN_CODE = 0,
		CV_CHAIN_APPROX_NONE = 1,
		CV_CHAIN_APPROX_SIMPLE = 2,
		CV_CHAIN_APPROX_TC89_L1 = 3,
		CV_CHAIN_APPROX_TC89_KCOS = 4,
		CV_LINK_RUNS = 5 */

	DOH(showAllWindows, nw_thresh_after, blob);

	vector<vector<Point> >hull(contours.size());

	for (int i = 0; i < contours.size(); i++) {
		convexHull(Mat(contours[i]), hull[i], false);
	}

	for (int i = 0; i < contours.size() && i < maxNumbShapes; i++) {

		//approxPolyDP(Mat(contours[i]), contours[i], 0, true);

		drawContours(drawOn, contours, i, Scalar(255, 0, 0), 2, 8, vector<Vec4i>(), 0, Point());
		drawContours(drawOn, hull, i, Scalar(0, 0, 255), 1, 8, vector<Vec4i>(), 0, Point());

		Point center = getShapeCenter(contours[i]);

		circle(drawOn, center, 2, Scalar(100, 255, 0), 2, 8, 0);
	}

	imshow(nw_cardetect, drawOn);
}

void CarDetection::trackPoints(vector<Point>& a) {



}

void CarDetection::findSolidLines(Mat& a) {

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

	Canny(a, a, cannyThresh1, cannyThresh2);

	vector<Vec4i> linesHlp;
	linesHlp.resize(10);

	HoughLinesP(a, linesHlp, linesRho, getR, linesThresh, linesMinLength, linesMaxGap);

	for (size_t i = 0; i < linesHlp.size(); i++) {

		Vec4i l = linesHlp[i];
		Point p1, p2;

		p1 = Point(l[0], l[1]);
		p2 = Point(l[2], l[3]);

		float angle = atan2(p1.y - p2.y, p1.x - p2.x) * getD;
		
		if (angle < 0) {angle = abs(angle) + 180;}

		if ((angle > minD1 && angle < maxD1) || (angle > minD2 && angle < maxD2)){
			line(drawOn, p1, p2, Scalar(255, 150, 0), 2, 8);
		}
		
	}
	frame++;
}

Mat CarDetection::getThreshold() {
	return blob;
}