#pragma once

#ifndef ANALYZEPOINTS_H
#define ANALYZEPOINTS_H

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

class analyzePoints {

private:

	int minArea = 300;

public:

	void findPoints(Mat& drawOn, Mat& a);
};


#endif // !ANALYZEPOINTS_H

