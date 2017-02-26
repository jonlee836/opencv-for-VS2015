#include "displayMats.h"

void displayMat(string& windowName, Mat& a){
	if (!a.empty()) {
		imshow(windowName, a);
	}
}

void displayMatChans(string& windowName, vector<Mat>& a) {

	if (!a.empty() && a.size() == 3) {
		imshow(windowName+" 1", a[0]);
		imshow(windowName+" 2", a[1]);
		imshow(windowName+" 3", a[2]);
	}
}

void DOH(bool a, string windowName, Mat& img) {
	if (a == true) {
		imshow(windowName, img);
	}
	else {
		destroyWindow(windowName);
	}
}