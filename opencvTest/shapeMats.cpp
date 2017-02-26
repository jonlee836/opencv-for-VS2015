#include "shapeMats.h"

void RemoveBySize(Mat& a, int minArea) {
	Mat temp = a.clone();
	vector<vector <Point> > contours;

	findContours(temp, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	for (int i = 0; i < contours.size(); i++) {
		double area = contourArea(contours[i]);
		if (area <= minArea) {
			drawContours(a, contours, i, Scalar(0), CV_FILLED, 8);
		}
	}
}

void ErodeDilate(Mat& a, int ea, int da, int shape) {
	
	/*
		MORPH_RECT = 0, //!< a rectangular structuring element:  \f[E_{ij}=1\f]
		MORPH_CROSS = 1, //!< a cross-shaped structuring element:
						 //!< \f[E_{ij} =  \fork{1}{if i=\texttt{anchor.y} or j=\texttt{anchor.x}}{0}{otherwise}\f]
		MORPH_ELLIPSE = 2 //!< an elliptic structuring element, that is, a filled ellipse inscribed
						  //!< into the rectangle Rect(0, 0, esize.width, 0.esize.height)
	*/

	if (ea <= 0) { ea = 1; }
	if (da <= 0) { da = 1; }

	Mat erodeElement = getStructuringElement(shape, Size(ea, ea));
	Mat dilateElement = getStructuringElement(shape, Size(da, da));

	erode(a, a, erodeElement);
	dilate(a, a, dilateElement);

}