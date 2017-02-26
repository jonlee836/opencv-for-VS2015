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

#include "CarDetection.h"

#include "threshImg.h"
#include "displayMats.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{

	string cmdInput;

	string inputPath = "C:/opencv/projects/car detection/M6_Motorway_Traffic/";
	wchar_t *directory = L"C:/opencv/projects/car detection/M6_Motorway_Traffic/*.*";
	
	//string inputPath = "C:/opencv/projects/plane detection/";
	//wchar_t *directory = L"C:/opencv/projects/plane detection/*.*";

	bool Allimg = true;

	vector<string> imagepathArray;

	cv::Mat InputImage;

	parseImageInput imgIO(inputPath);
	imagepathArray = imgIO.getfiles(directory);

	CarDetection findcar;

	for (int i = 0; i < imagepathArray.size();) {

		string name = inputPath + imagepathArray[i];

		while (true) {

			int k = waitKey(10);

			if (char(k) == '`') {
				
				do {
					getline(cin, cmdInput);
				}
				while (cmdInput.empty());

				cmdInput.clear();
			}
			
			if (char(k) == '1') { // re-process current frame
				Allimg = false;
				findcar.carDetect(name);
			}
			else if (char(k) == '2') { Allimg = true; } // run all images / video forward
			else if (char(k) == 'b' && i > 1) {
				i--;
				findcar.carDetect(name);
				break;
			}
			else if (char(k) == 'n' && i < imagepathArray.size()) { // next frame
				if (i == imagepathArray.size() - 1) { i = 0; }
				else { i++; break; }
			}
			else if (char(k) == 'q') { return 0; }  // quit
			else if (Allimg == true) {

				findcar.carDetect(name);
				i++;
				if (i == imagepathArray.size()) { i = 0; }
				break;
			}

		}
	}

	cout << "number of images : " << imagepathArray.size() << endl;

	return(0);

}
