#include "pointMath.h"

bool checkEdgeDist(Point& a, int dist2Edge, int imgWidth, int imgHeight) {
	if (a.x <= dist2Edge || a.x >= imgWidth - dist2Edge ||
		a.y <= dist2Edge ||	a.y >= imgHeight - dist2Edge){
		return true;
	}
}

Point getMidpoint(Point a, Point b) {
	return Point((a.x + b.x) / 2, (a.y + b.y) / 2);
}

Point getShapeCenter(vector <Point>& contour) {
	Rect a = boundingRect(Mat(contour));
	Point objCenter = a.br() + a.tl();

	objCenter.x /= 2;
	objCenter.y /= 2;

	return objCenter;
}

bool is2dPointArrayNeg(array<array<Point, 10>, 30 > a) {
	for (int r = 0; r < a.size(); r++) {
		for (int c = 0; c < a[r].size(); c++) {
			a[r][c] = Point(-1, -1);
		}
	}
}

Point reset2dPointArrayRow(array<array<Point, 10>, 30 > a, int rr) {
	for (int c = 0; c < a[rr].size(); c++) {
		a[rr][c] = Point(-1, -1);
	}
}

double getPointDist(Point& a, Point& b) {
	return norm(a - b);
}