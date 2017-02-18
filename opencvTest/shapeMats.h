#pragma once

#ifndef SHAPEMATS_H
#define SHAPEMATS_H

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

void RemoveBySize(Mat& a, int minArea);

#endif // SHAPEMATS_H