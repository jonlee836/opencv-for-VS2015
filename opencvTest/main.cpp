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
			cv::imshow("imgFrame", INPUT_IMAGE);
		}

	}


	/*InputStream.open("C:\\opencv\\projects\\people detection\\peopleWalking.avi");

	int Input_Width = static_cast<int>(InputStream.get(CV_CAP_PROP_FRAME_WIDTH));
	int Input_Height = static_cast<int>(InputStream.get(CV_CAP_PROP_FRAME_HEIGHT));

	if (!InputStream.isOpened()){
		std::cout << "\nerror reading video file" << std::endl << std::endl;
		_getch();
		return(0);
	}

	if (InputStream.get(CV_CAP_PROP_FRAME_COUNT) < 1) {
		std::cout << "\nerror: video file must have at least one frame";
		_getch();
		return(0);
	}

	InputStream.read(INPUT_IMAGE);
	cv::imshow("imgFrame", INPUT_IMAGE);*/

	//while (InputStream.isOpened() && chCheckForEscKey != 27) {

	//	cv::imshow("imgFrame", INPUT_IMAGE);
	//	if ((InputStream.get(CV_CAP_PROP_POS_FRAMES) + 1) < InputStream.get(CV_CAP_PROP_FRAME_COUNT)) {       // if there is at least one more frame
	//		InputStream.read(INPUT_IMAGE);                            // read it
	//	}
	//	else {                                                  // else
	//		std::cout << "end of video\n";                      // show end of video message
	//		break;                                              // and jump out of while loop
	//	}
	//	chCheckForEscKey = cv::waitKey(100);      // get key press in case user pressed esc
	//}

	return(0);

}