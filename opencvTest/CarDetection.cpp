#include "CarDetection.h"

void CarDetection::carDetect(string imgName){

	img = imread(imgName);
	
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	resize(img, img, Size(640, 480));

	imshow("input", img);
	drawOn = img.clone();
	
	cvt2GRAY(img);
	adjustContrast(img, iValueForContrast, iValueForBrightness);
	//medianBlur(img, img, 11);

	GaussianBlur(img, img, Size(5, 5), 3.5, 3.5);
	imshow("after  blur", img);

	if (fgImg.empty()) {
		fgImg.create(img.size(), img.type());
	}

	bg_model->apply(img, blob, 0);

	fgImg = Scalar::all(0);
	img.copyTo(fgImg, blob);

	bg_model->getBackgroundImage(bgImg);

	threshold(blob, blob, minThresh, maxThresh, THRESH_BINARY);
	imshow("blob before", blob);

	Mat bgImgCopy = img.clone();
	findSolidLines(bgImgCopy);

	//threshold(bgImg, bgImgCopy, minThresh, maxThresh, THRESH_BINARY);
	//imshow("bgImg thresh", bgImgCopy);

	RemoveBySize(blob, 500);

	ErodeDilate(blob, erodeAmount, dilateAmount);
	findContours(blob, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	imshow("blob after", blob);
	vector<vector<Point> >hull(contours.size());

	for (int i = 0; i < contours.size(); i++) {
		convexHull(Mat(contours[i]), hull[i], false);
	}

	for (int i = 0; i < contours.size(); i++) {
		
		//approxPolyDP(Mat(contours[i]), contours[i], 0, true);

		drawContours(drawOn, contours, i, Scalar(255, 0, 0), 2, 8, vector<Vec4i>(), 0, Point());
		drawContours(drawOn, hull, i, Scalar(0, 0, 255), 1, 8, vector<Vec4i>(), 0, Point());

		Point center = getShapeCenter(contours[i]);

		circle(drawOn, center, 2, Scalar(100, 255, 0), 2, 8, 0);
	}

	imshow(WINDOW_CARDETECT, drawOn);
}

void CarDetection::trackPoints(vector<Point>& a){
	
}

void CarDetection::findSolidLines(Mat& a) {
	
	vector<Vec2f> lines;

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
	imshow("canny", a);
	
	// If linesRho is 0 it crashes
	if (linesRho <= 0) { linesRho = 1; }

	HoughLines(a, lines, linesRho, getR, linesThresh, 0, 0);

	//for (size_t i = 0; i < lines.size(); i++) {

	//	Point pt1, pt2;

	//	float rho = lines[i][0];
	//	float theta = lines[i][1];

	//	double a = cos(theta), b = sin(theta);
	//	double x0 = a*rho, y0 = b*rho;

	//	pt1.x = cvRound(x0 + 1000 * (-b));
	//	pt1.y = cvRound(y0 + 1000 * (a));
	//	pt2.x = cvRound(x0 - 1000 * (-b));
	//	pt2.y = cvRound(y0 - 1000 * (a));

	//	/*if (i == 0) { cout << "***************ON FRAME " << frame << " *************************" << endl; }

	//	cout << "rho = " << rho << " theta = " << theta << endl;
	//	cout << "a = cos(theta) " << a << " b = sin(theta) " << b << endl;
	//	cout << "x0 = a*roh " << x0 << " y0 = b*rho " << y0 << endl;
	//	cout << "pts " << pt1 << ", " << pt2 << endl << endl;*/

	//	//vertical
	//	/*if (theta > getR * 150 || theta < getR * 40) {
	//		line(drawOn, pt1, pt2, Scalar(0, 0, 255), 1, 8);
	//	}*/

	//	/*if (theta > CV_PI / 180 * 80 && theta < CV_PI / 180 * 100){
	//		line(drawOn, pt1, pt2, Scalar(0, 155, 255), 1, 8);
	//	}*/

	//	//line(drawOn, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(255, 150, 0), 2, 8);
	//}

	vector<Vec4f> linesHlp;
	HoughLinesP(a, linesHlp, linesRho, getR, linesThresh, linesMinLength, linesMaxGap);

	for (size_t i = 0; i < linesHlp.size(); i++) {

		Point pt1, pt2;

		float rho = linesHlp[i][0];
		float theta = linesHlp[i][1];
					
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;

		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));

		/*if (i == 0) { cout << "***************ON FRAME " << frame << " *************************" << endl; }

		cout << "rho = " << rho << " theta = " << theta << endl;
		cout << "a = cos(theta) " << a << " b = sin(theta) " << b << endl;
		cout << "x0 = a*roh " << x0 << " y0 = b*rho " << y0 << endl;
		cout << "pts " << pt1 << ", " << pt2 << endl << endl;*/
				
		if (theta < 120 && theta > 60)
		{
			cout << "point x0 = " << x0 << " point y0 = " << y0 << endl;
			cout << "rho = " << rho << " theta = " << theta << endl;
			cout << "a = cos(theta) " << a << " b = sin(theta) " << b << endl;
			cout << "x0 = a*roh " << x0 << " y0 = b*rho " << y0 << endl;
			cout << "pts " << pt1 << ", " << pt2 << endl << endl;

			line(drawOn, Point(linesHlp[i][0], linesHlp[i][1]), Point(linesHlp[i][2], linesHlp[i][3]), Scalar(255, 150, 0), 2, 8);
		}	
	}
	frame++;
}

Mat CarDetection::getThreshold() {
	return blob;
}