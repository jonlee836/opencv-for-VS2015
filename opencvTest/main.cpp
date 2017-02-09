#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <filesystem>
#include <iostream>
#include <conio.h>
#include <string>

#include <direct.h>

#include "parseVideoInput.h"
#include "analyzePoints.h"
#include "thresholdImage.h"

using namespace cv;

const char* keys =
{
	"{ b build | | print complete build info }"
	"{ h help  | | print this help           }"
};

int main(int argc, char** argv)
{

	bool playAll = true;
	char chCheckForEscKey = 0;
	
	//"C:\\opencv\\projects\\people detection\\peopleWalking.avi"
	//C:\opencv\projects\car detection\M6_Motorway_Traffic

	String inputPath = "C:\opencv\projects\car detection\M6_Motorway_Traffic";

	cv::Mat InputImage;
	cv::VideoCapture InputStream;

	threshImage threshImg;
	parseVideoInput a(inputPath);
	a.check_filepath();

	for (int i = 1; i < argc;) {
		String name = argv[i];
		cout << name << endl;
	}

	while (true){

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
	}

	return(0);

}