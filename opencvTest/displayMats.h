#pragma once

#ifndef DISPLAYMATH_H
#define DISPLAYMATH_

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

void displayMat(string& windowName, Mat& a);
void displayMatChans(string& windowName, vector<Mat>& a);

void DOH(bool a, string windowName, Mat& img); // Display Or Hide
void drawCrosshair(Mat& drawOn, Point centerPoint, Scalar outline, Scalar color, int xSpacing, int ySpacing, int flag);

#endif // DISPLAYMATH_H