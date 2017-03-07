#include "pointMath.h"

bool checkEdgeDist(Point& a, int dist2Edge, int imgWidth, int imgHeight) {
	if (a.x <= dist2Edge || a.x >= imgWidth - dist2Edge ||
		a.y <= dist2Edge ||	a.y >= imgHeight - dist2Edge){
		return true;
	}
}

bool is2dPointArrayNeg(array<array<Point, 10>, 30 > a) {
	for (int r = 0; r < a.size(); r++) {
		for (int c = 0; c < a[r].size(); c++) {
			a[r][c] = Point(-1, -1);
		}
	}
}

Point getMidpoint(Point a, Point b) {
	return Point((a.x + b.x) / 2, (a.y + b.y) / 2);
}

Point getShapeCenter(vector <Point>& contour) {

	//Moments moment01 = moments(contour, false);

	//Point objCenter = Point(moment01.m10 / moment01.m00, moment01.m01 / moment01.m00);

	Rect a = boundingRect(Mat(contour));
	Point objCenter = a.br() + a.tl();

	objCenter.x /= 2;
	objCenter.y /= 2;

	return objCenter;
}

Point reset2dPointArrayRow(array<array<Point, 10>, 30 > a, int rr) {
	for (int c = 0; c < a[rr].size(); c++) {
		a[rr][c] = Point(-1, -1);
	}
}

float getRadians2Degrees(Point a, Point b) {
	float angle = atan2(a.y - b.y, a.x - b.x) * getD;

	float val = (b.y - a.y) / (b.x - a.x);           // calculate slope between the two points
	
	//val = val - pow(val, 3) / 3 + pow(val, 5) / 5; // find arc tan of the slope using taylor series approximation
	val = ((int)(val * getD)) % 360;               // Convert the angle in radians to degrees
	
	if (b.x < a.x) val += 180;
	if (val < 0) val = 360 + val;

	return val;

}

double getPointDist(Point& a, Point& b) {
	double distance = norm(a - b);

	return distance;
}