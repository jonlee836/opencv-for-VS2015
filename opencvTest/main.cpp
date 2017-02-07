#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>
#include<conio.h> 

#include "parseInput.h"
#include "analyzePoints.h"
#include "thresholdImage.h"

using namespace cv;

const char* keys =
{
	"{ b build | | print complete build info }"
	"{ h help  | | print this help           }"
};

int main(int argc, const char* argv[])
{

	bool playAll = true;
	char chCheckForEscKey = 0;

	double FPS = 10.0;

	String inputPath = "C:\\opencv\\projects\\people detection\\peopleWalking.avi";

	cv::Mat INPUT_IMAGE;
	cv::VideoCapture InputStream;

	parseInput a(inputPath);
	a.check_filepath();

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
			INPUT_IMAGE = a.getVideoInput();
			cvtColor(INPUT_IMAGE, INPUT_IMAGE, CV_BGR2Luv);
			cv::imshow("imgFrame", INPUT_IMAGE);
		}
	}

	return(0);

}