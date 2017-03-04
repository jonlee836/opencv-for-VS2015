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
	if (a == true && !img.empty()) {
		imshow(windowName, img);
	}
	else {
		destroyWindow(windowName);
	}
}

void drawCrosshair(Mat& drawOn, Point centerPoint, Scalar outline, Scalar color, int xSpacing, int ySpacing, int flag) {

	if (centerPoint != Point(-1, -1)) {
		
		Scalar colorBlack = Scalar(0);
		Scalar colorGreen = Scalar(0, 255, 0);

		int xSpacing = 7;
		int ySpacing = 7;
		int xLength = 20;
		int yLength = 20;

		int x = centerPoint.x;
		int y = centerPoint.y;

		rectangle(drawOn, Point(x, y - ySpacing), Point(x, y - yLength), colorBlack, 3, CV_AA, 0);
		rectangle(drawOn, Point(x, y + ySpacing), Point(x, y + yLength), colorBlack, 3, CV_AA, 0);
		rectangle(drawOn, Point(x - xSpacing, y), Point(x - xLength, y), colorBlack, 3, CV_AA, 0);
		rectangle(drawOn, Point(x + xSpacing, y), Point(x + xLength, y), colorBlack, 3, CV_AA, 0);

		rectangle(drawOn, Point(x, y - ySpacing), Point(x, y - yLength), colorGreen, 2, CV_AA, 0);
		rectangle(drawOn, Point(x, y + ySpacing), Point(x, y + yLength), colorGreen, 2, CV_AA, 0);
		rectangle(drawOn, Point(x - xSpacing, y), Point(x - xLength, y), colorGreen, 2, CV_AA, 0);
		rectangle(drawOn, Point(x + xSpacing, y), Point(x + xLength, y), colorGreen, 2, CV_AA, 0);

		rectangle(drawOn, Point(x - 50, y - 50), Point(x + 50, y + 50), Scalar(0), 3, CV_AA, 0);
		rectangle(drawOn, Point(x - 50, y - 50), Point(x + 50, y + 50), colorGreen, 2, CV_AA, 0);

	}

}
