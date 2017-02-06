#include "parseInput.h"

using namespace cv;
using namespace std;

parseInput::parseInput(String filepath_) {
	filepath = filepath_;
}

bool parseInput::check_filepath() {

	InputStream.open(filepath);

	if (!InputStream.isOpened()) {
		std::cout << "\nerror reading video file" << std::endl << std::endl;
		_getch();

		return false;
	}

	if (InputStream.get(CV_CAP_PROP_FRAME_COUNT) < 1) {
		std::cout << "\nerror: video file must have at least one frame";
		_getch();

		return false;
	}

	Input_Width = static_cast<int>(InputStream.get(CV_CAP_PROP_FRAME_WIDTH));
	Input_Height = static_cast<int>(InputStream.get(CV_CAP_PROP_FRAME_HEIGHT));

	frameCount = InputStream.get(CV_CAP_PROP_FRAME_COUNT);

	cout << "frame count : " << frameCount << endl;
	cout << "frame width : " << Input_Width << endl;
	cout << "frame height : " << Input_Height << endl;

	return true;
}

bool parseInput::isStreamOpen() {

	if (InputStream.isOpened()) {
		return true;
	}
	else {
		return false;
	}
}

int parseInput::getCurrframe() {
	return currFramePos;
}

Mat parseInput::getVideoInput()
{
	Mat inputImg;

	InputStream.read(inputImg);

	currFramePos = InputStream.get(CV_CAP_PROP_POS_FRAMES);

	cout << "current frame : " << currFramePos << endl;

	return inputImg;
}