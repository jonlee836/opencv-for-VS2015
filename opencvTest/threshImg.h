#pragma once

#ifndef COLORSPACECVT_H
#define COLORSPACECVT_H

#include "opencv2/core.hpp"
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/video/background_segm.hpp"
#include "opencv2/videoio.hpp"

#include <iostream>
#include <array>

using namespace cv;
using namespace std;

void cvt2HSV(Mat& a);
void cvt2HLS(Mat& a);
void cvt2LUV(Mat& a);
void cvt2LAB(Mat& a);
void cvt2GRAY(Mat& a);

void cvt2EqualizeImg(Mat& a);

void cvt2EqualizeIntensity(Mat& inputImage);
void adjustContrast(Mat& a, int contrastAdj, int brightAdj);

void DogSaliency(Mat& a);

#endif // COLORSPACECVT_H