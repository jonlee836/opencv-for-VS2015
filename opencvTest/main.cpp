#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <filesystem>
#include <iostream>
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

const char* keys =
{
	"{ b build | | print complete build info }"
	"{ h help  | | print this help           }"
};

int main(int argc, char** argv)
{

	string inputPath = "C:/opencv/projects/car detection/M6_Motorway_Traffic/";
	wchar_t *directory = L"C:/opencv/projects/car detection/M6_Motorway_Traffic/*.*";

	int totalframes;
	bool playAll = true;
	char chCheckForEscKey = 0;
	
	/*"C:\\opencv\\projects\\people detection\\peopleWalking.avi"
	C:\opencv\projects\car detection\M6_Motorway_Traffic
	parseVideoInput a(inputPath);
	a.check_filepath();*/

	vector<string> imagepathArray;

	cv::Mat InputImage;
	cv::VideoCapture InputStream;
	parseImageInput imgIO(inputPath);
	threshImage threshImg;
	imagepathArray = imgIO.getfiles(directory);

	for (unsigned int i = 0; i < imagepathArray.size(); i++){
		cout << imagepathArray[i] << endl;
	}

	cout << "number of images : " << imagepathArray.size() << endl;
	/*parseImageInput imgIO(inputPath);
	imgIO.ListAllFilesInDir();
	totalframes = imgIO.get_filenames();*/

	/*while (true){

		int k = waitKey(100);

		if (char(k) == 'q') {break;}
		else if (char(k) == 'b' ) {
			
		}
		else if (char(k) == 't') {
			if (playAll == true) {playAll = false;}
			else                 {playAll = true;}
		}
		else if (playAll == true) {
			InputImage = a.getVideoInput();
			threshImg.colorspace(InputImage);
			cv::imshow("imgFrame", InputImage);
		}
	}*/

	return(0);

}
