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

int main(int argc, char** argv)
{

	string inputPath = "C:/opencv/projects/car detection/M6_Motorway_Traffic/";
	wchar_t *directory = L"C:/opencv/projects/car detection/M6_Motorway_Traffic/*.*";

	bool Allimg = true;
	char chCheckForEscKey = 0;

	/*"C:\\opencv\\projects\\people detection\\peopleWalking.avi"
	C:\opencv\projects\car detection\M6_Motorway_Traffic
	parseVideoInput a(inputPath);
	a.check_filepath();*/

	vector<string> imagepathArray;

	cv::Mat InputImage;
	cv::VideoCapture InputStream;

	threshImage threshImg;

	parseImageInput imgIO(inputPath);
	imagepathArray = imgIO.getfiles(directory);

	for (int i = 0; i < imagepathArray.size();) {

		string name = inputPath + imagepathArray[i];

		while (true) {
			int k = waitKey(1);

			if (char(k) == '1') { // re-process current frame
				Allimg = false;

				string name = inputPath + imagepathArray[i];
				cout << name << endl;

				InputImage = imread(name);
				threshImg.colorspace(InputImage);

				//i++;
			}
			else if (char(k) == '2') { Allimg = true; }
			else if (char(k) == 'b' && i > 1) {
				i--;
				name = inputPath + imagepathArray[i];
				InputImage = imread(name);
				
				threshImg.colorspace(InputImage);

				break;
			}
			else if (char(k) == 'n' && i < imagepathArray.size()) {i++; break; }
			else if (char(k) == 'q') { return 0; }
			else if (Allimg == true) {

				string name = inputPath + imagepathArray[i];

				cout << name << endl;

				InputImage = imread(name);
				imshow("img", InputImage);

				threshImg.colorspace(InputImage);

				i++;

				break;
			}
		}
	}

	cout << "number of images : " << imagepathArray.size() << endl;

	return(0);

}
