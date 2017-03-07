#pragma once

#ifndef POINTMATH_H
#define POINTMATH_H

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include <array>

using namespace cv;
using namespace std;

const double getR = CV_PI / 180;
const double getD = 180 / CV_PI;

bool checkEdgeDist(Point& a, int dist2Edge, int imgWidth, int imgHeight);
bool is2dPointArrayNeg(array<array<Point, 10>, 30 > a);

Point getMidpoint(Point a, Point b);
Point getShapeCenter(vector <Point>& contour);
Point reset2dPointArrayRow(array<array<Point, 10>, 30 > a, int rr);
int getDegrees(Point a, Point b);

double getPointDist(Point& a, Point& b);

float getRadians2Degrees(Point a, Point b);

#endif // POINTMATH_H
