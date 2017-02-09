#include "parseVideoInput.h"

using namespace cv;
using namespace std;

parseVideoInput::parseVideoInput(String filepath_) {
	filepath = filepath_;
}

bool parseVideoInput::check_filepath() {

	InputStream.open(filepath);

	if (!InputStream.isOpened()) {
		std::cout << "\nerror reading video file" << std::endl << std::endl;

		return false;
	}

	if (InputStream.get(CV_CAP_PROP_FRAME_COUNT) < 1) {
		std::cout << "\nerror: video file must have at least one frame";

		return false;
	}

	frameCount = InputStream.get(CV_CAP_PROP_FRAME_COUNT);

	return true;
}

bool parseVideoInput::isStreamOpen() {

	if (InputStream.isOpened()) {
		return true;
	}
	else {
		return false;
	}
}

int parseVideoInput::getCurrframe() {
	return currFramePos;
}

Mat parseVideoInput::getVideoInput()
{
	Mat inputImg;

	InputStream.read(inputImg);

	currFramePos = InputStream.get(CV_CAP_PROP_POS_FRAMES);

	cout << "current frame : " << currFramePos << endl;

	return inputImg;
}