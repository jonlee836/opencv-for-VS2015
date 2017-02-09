#include "parseImageInput.h"

using namespace cv;
using namespace std;

parseImageInput::parseImageInput(String filepath_) {
	filepath = filepath_;
}

int parseImageInput::get_filenames()
{
	namespace stdfs = std::experimental::filesystem;

	std::vector<std::string> filenames;

	const stdfs::directory_iterator end{};

	//for (stdfs::directory_iterator iter{ path }; iter != end; ++iter)
	//{
	//	// comment out if all names (names of directories tc.) are required
	//	totalFrames++;
	//}

	return totalFrames;
}