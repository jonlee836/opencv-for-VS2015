#pragma once

#ifndef POINTMATH_H
#define POINTMATH_H

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include <array>

using namespace cv;
using namespace std;

bool checkEdgeDist(Point& a, int dist2Edge, int imgWidth, int imgHeight);

Point getMidpoint(Point a, Point b);
Point getShapeCenter(vector <Point>& contour);

bool is2dPointArrayNeg(array<array<Point, 10>, 30 > a);
bool isVPin2dPointArray(array<array<Point, 10>, 30 > a);

Point reset2dPointArrayRow(array<array<Point, 10>, 30 > a, int rr);

double getPointdist(Point& a, Point& b);

#endif // POINTMATH_H
