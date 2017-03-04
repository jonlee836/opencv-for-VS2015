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

	/*
	
	const string tbCar = "car detect trackbar";

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

		circle(drawOn, center, 2, Scalar(0, 255, 0), 2, 8, 0);
	}

	//cout << " frame : " << frame << " ";

	trackPoints(currPoints, drawOn);

	//cout << endl;

	currPoints.clear();
	frame++;

	imshow(nw_cardetect, drawOn);
}

void CarDetection::trackPoints(vector<Point>& a, Mat& draw) {

	vector <Point> validPoints;

	currPoints = a;

	int vpSize = validPoints.size();
	int cSize = currPoints.size();
	int pSize = prevPoints.size();

	if (currPoints.empty() && !prevPoints.empty()) {
		prevPoints.clear();
		currPoints.clear();
	}
	else if ((!currPoints.empty() && prevPoints.empty()) || (currPoints.empty() && prevPoints.empty())) {
		prevPoints = currPoints;
	}
	else if (!currPoints.empty() && !prevPoints.empty()){

		findVp(validPoints);

		if (!validPoints.empty()) {

			int total_NN = findFpNonNegIndex();

			// there are no foundPoints already, fill foundPoints[r][0] with values from validPoints			
			if (total_NN <= 0) {
				setFp_with_Vp(validPoints);
			}

			// there are already foundPoints, compare each vp with fp
			else {

				// fpIndex[fpRow] holds the last non-neg index position within each row in foundPoint[r][c]
				for (int r = 0; r < fpRow; r++) {

					if (fpIndex[r] >= 0) {

						// a value of 0 means there's only 1 non-neg in the row
						int c = fpIndex[r];

						for (int v = 0; v < validPoints.size(); v++) {

							// find point that matches
							int dist = getPointDist(foundPoints[r][c], validPoints[v]);

							if (dist <= disTol) {

								// when the final position of foundPoints[r][c] is filled iterate the car counter
								// and reset the current row
								//circle(draw, foundPoints[r][c], 2, Scalar(0, 255, 0), 5, 8, 0);
								fpLc[r] = 0;


								if (c + 1 >= fpCol) {

									// foundPoints start writing over itself
									resetFpRow(r);

									foundPoints[r][0] = validPoints[v];
									fpLastKnown[r] = validPoints[v];
									fpConfirmed[r] = true; 	

									//circle(draw, fpLastKnown[r], 2, Scalar(0, 255, 0), 5, 8, 0);
									//cout << " fp[" << r << "]" << "[" << c << "] = " << foundPoints[r][c] << endl;
									//cout << " vp[" << r << "] = " << validPoints[v] << " fpIndex " << fpIndex[r] << " " << endl;
								}
								else {
									foundPoints[r][c + 1] = validPoints[v];
									fpLastKnown[r] = validPoints[v];
								}
								// set to -1,-1 to denote validPoint[v] was used up by foundPoints[r][c]
								validPoints[v] = Point(-1, -1);

								break;

							}
							else if (dist > disTol && v + 1 >= validPoints.size()) {

								// If fpIndex[r] is the same size as fpCol that means the car is 
								// confirmed and it's safe to stop tracking.
								// Either way you reset the row at foundPoints[r]
								fpLc[r]++;

								if (fpConfirmed[r] == true) {

									if (fpLc[r] >= fpLostMax) {

										//cout << "dist = " << dist << " fp[" << r << "]" << "[" << c << "] = " << foundPoints[r][c] << endl;
										//cout << "dist = " << dist << " drawing at fpLastKnown[" << r << "] = " << fpLastKnown[r] << endl;
										
										CarsCounted++;
										cout << "cars counted : " << CarsCounted << endl;

										circle(draw, fpLastKnown[r], 2, Scalar(0, 0, 255), 8, 8, 0);										
										resetFpRow(r);
									}
								}
								else if (fpLc[r] >= fpLostMin && fpIndex[r] < fpLost_minIndex) {
									resetFpRow(r);
								}

							}
						}
					}					
				}				
				// remaining validPoints[v] that haven't been set to -1,-1 are put in foundPoints[r][0]
				setFp_with_Vp(validPoints);
			}		
		}
		else {

			// conditions for reseting a row in foundPoints[r]				
			for (int r = 0; r < fpRow; r++) {

				// if the row in foundPoint hasn't been confirmed aka 7 hits
				if (!fpConfirmed[r]) {

					// if it has been lost for fpLastMin number of frames and detected less than 5 frames in a row
					if (fpLc[r] >= fpLostMin && fpIndex[r] < fpLost_minIndex) {
						resetFpRow(r);
					}
					else {
						fpLc[r]++;
					}
				}				
			}
		}

		prevPoints = currPoints;
		currPoints.clear();
	}
}

int CarDetection::findFpNonNegIndex() {
	
	/*  

	example

	validPoints

	[0] 53,55

	[1] 99,99

	[2] 10,10

	--------------------------------------------

	foundPoints

	     [0]     [1]      [2]     [3]     [4]

	[0]  88,88  -1,-1    -1,-1   -1,-1   -1,-1
	   
	[1]  77,77  -1,-1    -1,-1   -1,-1   -1,-1

	[2]  20,10  -1,-1    -1,-1   -1,-1   -1,-1

	[3]  51,52  51,53    -1,-1   -1,-1   -1,-1

	[4]  93,95  94,96    98,99   -1,-1   -1,-1
	

	-------------------------------------------

	fpIndex

	[0] = -1

	[1] = -1

	[2] = 0

	[3] = 1

	[4] = 3
	

	Example Output

	fpIndex[3] = 1

	int c = fpIndex[3]

	validPoints[0] = 53,55
	foundPoints[3][c] = 51,53

	therefore

	foundPoints[3][2] would be set to validPoints[0]
	foundPoints[4][3] would be set to validPoints[1]

	foundPoints rows 0,1,2 are set to Point(-1,-1)	

	validPoints[0] are set to Point(-1,-1)
	validPoints[1] are set to Point(-1,-1)

	----------------------------------------

	validPoints[2] is therefore a new point to track

	The first element in foundpoints[r][0] that equals Point(-1,-1)
	is set to validPoints[2]

	*/

	int total = 0;

	for (int r = 0; r < fpRow; r++) {		
		
		int index = -1;
		bool hasNonNeg = false;		

		for (int c = 0; c < fpCol && foundPoints[r][c] != Point(-1,-1); c++) {
			index = c;
			hasNonNeg = true;
		}

		if (hasNonNeg == true) {
			fpIndex[r] = index;
			total++;
		}
	}

	return total;
}

void CarDetection::findVp(vector<Point>& vp) {
	
	// compare prev with curr points, if they pass the check they are added to vp

	for (int r = 0; r < currPoints.size(); r++) {
		for (int c = 0; c < prevPoints.size(); c++) {
			if (getPointDist(currPoints[r], prevPoints[c]) <= disTol) {
				vp.push_back(currPoints[r]);
			}
		}		
	}
}

void CarDetection::setFp_with_Vp(vector<Point>& vp) {

	int vit = 0;

	for (int r = 0; r < fpRow && vit < vp.size(); r++) {		
		if (vp[vit] != Point(-1, -1)) {
			foundPoints[r][0] = vp[vit];
		}		
		vit++;
	}
}

void CarDetection::resetFp() {
	for (int r = 0; r < fpRow; r++) {
		for (int c = 0; c < fpCol; c++) {
			foundPoints[r][c] = Point(-1,-1);
		}
		fpLc[r] = 0;
		fpIndex[r] = -1;
		fpConfirmed[r] = false; 
		fpLastKnown[r] = Point(-1, -1);		
	}
}

void CarDetection::resetFpRow(int r) {
	for (int c = 0; c < fpCol; c++) {
		foundPoints[r][c] = neg;
	}
	fpLc[r] = 0;
	fpIndex[r] = -1;
	fpConfirmed[r] = false;
	fpLastKnown[r] = Point(-1, -1);
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

	HoughLinesP(a, linesHlp, linesRho, getR, linesThresh, linesMinLength, linesMaxGap);

	for (size_t i = 0; i < linesHlp.size(); i++) {

		Vec4i l = linesHlp[i];
		Point p1, p2;

		p1 = Point(l[0], l[1]);
		p2 = Point(l[2], l[3]);

		float angle = atan2(p1.y - p2.y, p1.x - p2.x) * getD;
		
		if (angle < 0) {angle = abs(angle) + 180;}

		if ((angle > minD1 && angle < maxD1) || 
			(angle > minD2 && angle < maxD2))
		{
			line(drawOn, p1, p2, Scalar(255, 150, 0), 2, 8);
		}
	}


}

Mat CarDetection::getThreshold() {
	return blob;
}