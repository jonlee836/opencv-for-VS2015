#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <filesystem>
#include <iostream>
#include <chrono>
#include <conio.h>
#include <string>
#include <Windows.h>
#include <experimental/filesystem>

#include "parseVideoInput.h"
#include "parseImageInput.h"

#include "analyzePoints.h"
#include "thresholdImage.h"

using namespace std;
using namespace cv;

namespace fs = std::tr2::sys;

void runDetection(String name, Mat& InputImage, threshImage& threshImg, analyzePoints& srtPts) {
	InputImage = imread(name);
	
	resize(InputImage, InputImage, Size(640, 480));

	imshow("input", InputImage);
	//threshImg.colorspace(InputImage);
	threshImg.fgbgDetect(InputImage);

	Mat binary = threshImg.getThreshold();
	imshow("binary", binary);
	srtPts.findPoints(InputImage, binary);
}

int main(int argc, char** argv)
{
	
	string inputPath = "C:/opencv/projects/car detection/M6_Motorway_Traffic/";
	wchar_t *directory = L"C:/opencv/projects/car detection/M6_Motorway_Traffic/*.*";
	
	//string inputPath = "C:/opencv/projects/plane detection/";
	//wchar_t *directory = L"C:/opencv/projects/plane detection/*.*";

	bool Allimg = true;
	char chCheckForEscKey = 0;

	vector<string> imagepathArray;

	cv::Mat InputImage;
	cv::VideoCapture InputStream;

	analyzePoints srtPts;
	parseImageInput imgIO(inputPath);
	imagepathArray = imgIO.getfiles(directory);

	threshImage threshImg;

	for (int i = 0; i < imagepathArray.size();) {

		string name = inputPath + imagepathArray[i];

		while (true) {
			int k = waitKey(1);

			if (char(k) == '1') { // re-process current frame
				Allimg = false;

				string name = inputPath + imagepathArray[i];
				cout << name << endl;
				runDetection(name, InputImage, threshImg, srtPts);

				//i++;
			}
			else if (char(k) == '2') { Allimg = true; }
			else if (char(k) == 'b' && i > 1) {
				i--;
				runDetection(name, InputImage, threshImg, srtPts);

				break;
			}
			else if (char(k) == 'n' && i < imagepathArray.size()) {
				if (i == imagepathArray.size() - 1) {
					i = 0;
				}
				else {
					i++; 
					break;
				}
			}
			else if (char(k) == 'q') { return 0; }
			else if (Allimg == true) {

				string name = inputPath + imagepathArray[i];

				cout << name << endl;

				runDetection(name, InputImage, threshImg, srtPts);

				i++;
				
				if (i == imagepathArray.size()) {
					i = 0;
				}

				break;
			}
		}
	}

	cout << "number of images : " << imagepathArray.size() << endl;

	return(0);

}
