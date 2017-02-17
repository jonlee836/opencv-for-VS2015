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

#endif // DISPLAYMATH_H