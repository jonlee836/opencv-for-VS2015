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

	for (int i = 0; i < contours.size() && i < 1000; i++) {
		
		approxPolyDP(Mat(contours[i]), contours[i], 0, true);

		drawContours(drawOn, contours, i, Scalar(255, 0, 0), 2, 8, vector<Vec4i>(), 0, Point());
		drawContours(drawOn, hull, i, Scalar(0, 0, 255), 1, 8, vector<Vec4i>(), 0, Point());

		Point center = getShapeCenter(contours[i]);
		currPoints.push_back(center);

		circle(drawOn, center, 2, Scalar(100, 255, 0), 2, 8, 0);
	}

	trackPoints(currPoints);

	imshow(nw_cardetect, drawOn);
}

void CarDetection::trackPoints(vector<Point>& a) {

	/*
		cout << endl;
		cout << "at frame " << frame << endl;
		cout << c << " curr point " << currPoints[c] << endl;
		cout << "    " << p << " prev point " << prevPoints[p] << " distance = " << dist << endl;
	*/
	cout << "at frame " << frame << endl;

	vector <Point> validPoints;

	if (!prevPoints.empty()) {
		for (int c = 0; c < currPoints.size(); c++) {
			for (int p = 0; p < prevPoints.size(); p++) {
				double dist = getPointdist(currPoints[c], prevPoints[p]);

				if (dist <= CarCountDistanceTolerance) {
					validPoints.push_back(currPoints[c]);
				}
			}
		}

		// foundPoints[r][0] being -1,-1 indicates the rest of the row is empty

		int vIt = 0;
		for (int r = 0; r < foundPoints.size(); r++) {
			if (foundPoints[r][0] == Point(-1, -1)) {
				foundPoints[r][0] = validPoints[vIt];
				vIt++;
			}
		}
		
		/*
			compare to previous found points points

			foundPoints

					[0]       [1]       [2]       [3]       [4]       [5]       [6] -----> up to CarMaxCount
			[0]   (10,10)   (15,15) 
			[1]
			[2]
			[3]
			[4]

		*/
		
		for (int r = 0; r < foundPoints.size(); r++) {
			for (int c = 0; c < foundPoints[r].size(); c++) {
				if (foundPoints[r][c] == Point(-1, -1) && c >= 1) {

				}
				for (int v = 0; v < validPoints.size(); v++) {
					// compare foundPoints to validPoints (currPoints vs prevPoints)
					double dist = getPointdist(foundPoints[r][c], validPoints[v]);

					if (dist <= CarCountDistanceTolerance && dist > 0) {
						cout << "[" << r << "]" << "[" << c << "] "  << "dist passed " << endl;
						// fill row with -1,-1 to show it's been cleared

						if (c == foundPoints[r].size() - 1) {
							for (int z = 0; z < foundPoints[r].size(); z++) {
								foundPoints[r][z] = Point(-1, -1);
							}
							CarsCounted++;
							cout << " Cars Counted " << CarsCounted << endl;
						}
						else {
							foundPoints[r][c] = validPoints[v];
						}
						cout << validPoints[v] << endl;

					}
				}
			}
		}

		prevPoints = currPoints;
		currPoints.clear();
	}
	else {
		prevPoints = a;
	}

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