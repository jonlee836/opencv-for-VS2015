#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <filesystem>
#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>
#include <experimental/filesystem>

#include "parseVideoInput.h"
#include "parseImageInput.h"
#include "analyzePoints.h"
#include "thresholdImage.h"
#include "tinydir.h"

namespace fs  = std::tr2::sys;
using namespace cv;

const char* keys =
{
	"{ b build | | print complete build info }"
	"{ h help  | | print this help           }"
};

int main(int argc, char** argv)
{

	int totalframes;
	bool playAll = true;
	char chCheckForEscKey = 0;
	
	//"C:\\opencv\\projects\\people detection\\peopleWalking.avi"
	//C:\opencv\projects\car detection\M6_Motorway_Traffic
	//parseVideoInput a(inputPath);
	//a.check_filepath();

	String inputPath = "C:/opencv/projects/car detection/M6_Motorway_Traffic";
	vector <string> imagepathArray;

	cv::Mat InputImage;
	cv::VideoCapture InputStream;
	
	//cout << "The string initialized by C-string cstr1a is: " << str1a << endl;

	//fs::path::string_type foo = "C:/opencv/projects/car detection/M6_Motorway_Traffic";
	threshImage threshImg;
	parseImageInput imgIO(inputPath);
	//imgIO.ListAllFilesInDir();
	totalframes = imgIO.get_filenames();

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