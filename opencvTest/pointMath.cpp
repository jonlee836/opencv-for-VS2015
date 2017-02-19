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

double getPointdist(Point& a, Point& b) {
	return norm(a - b);
}