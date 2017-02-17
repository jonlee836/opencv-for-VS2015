#pragma once

#ifndef POINTMATH_H
#define POINTMATH_H

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

bool checkEdgeDist(Point& a, int dist2Edge, int imgWidth, int imgHeight);

void RemoveBySize(Mat& a, int minArea);

Point getMidpoint(Point a, Point b);
Point getShapeCenter(vector <Point>& contour);

#endif // POINTMATH_H