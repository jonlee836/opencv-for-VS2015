#pragma once

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;

static Point origin;
static Rect selection;

static bool selectObject = false;
static bool selectionComplete = false;

void onMouseSelect(int event, int x, int y, int, void* image);
