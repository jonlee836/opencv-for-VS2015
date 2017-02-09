#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <filesystem>
#include <iostream>
#include <conio.h>
#include <string>
#include <algorithm>

#include "parseVideoInput.h"
#include "parseImageInput.h"
#include "analyzePoints.h"
#include "thresholdImage.h"
#include <experimental/filesystem>

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

	cv::Mat InputImage;
	cv::VideoCapture InputStream;

	threshImage threshImg;
	
	const char *cstr1a = "Hello Out There.";

	basic_string <char> str1a(inputPath);
	
	//cout << "The string initialized by C-string cstr1a is: " << str1a << endl;

	//fs::path::string_type foo = "C:/opencv/projects/car detection/M6_Motorway_Traffic";

	//parseImageInput imgIO(inputPath);

	int i = std::count_if(fs::directory_iterator(str1a),
		fs::directory_iterator(),
		[](const fs::directory_entry& e) {
		return e.path().extension() == ".jpg";
	});

	std::cout << "input path : " << inputPath << " " << i << std::endl;

	/*for (auto& p : fs::directory_iterator(inputPath))
		std::cout << p << '\n';
	*/
	//totalframes = imgIO.get_filenames();
	//cout << "C:\\opencv\\projects\\car detection\\M6_Motorway_Traffic" << " " << totalframes << '\n';
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