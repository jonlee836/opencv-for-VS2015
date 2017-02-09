#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <filesystem>
#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
#include <algorithm>
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

	std::vector<std::wstring> vec;

	wchar_t *directory = L"C:/opencv/projects/car detection/M6_Motorway_Traffic/*.*";
	WIN32_FIND_DATA ffd;
	HANDLE handle = FindFirstFile(directory, &ffd);
	if (handle != INVALID_HANDLE_VALUE)
	{
		do {
			vec.push_back(ffd.cFileName);
		} while (FindNextFile(handle, &ffd));
		FindClose(handle);
	}
	else
	{
		OutputDebugString(L"Nothing to display \n");
	}

	for (unsigned int i = 0; i < vec.size(); i++)
	{
		string foo(vec[i].begin(), vec[i].end());
		cout << foo << endl;
	}

	cout << vec.size() << endl;
	getchar();

	//int totalframes;
	//bool playAll = true;
	//char chCheckForEscKey = 0;
	//
	//"C:\\opencv\\projects\\people detection\\peopleWalking.avi"
	//C:\opencv\projects\car detection\M6_Motorway_Traffic
	//parseVideoInput a(inputPath);
	//a.check_filepath();

	//string inputPath = "C:/opencv/projects/car detection/M6_Motorway_Traffic";
	//vector <string> imagepathArray;

	//cv::Mat InputImage;
	//cv::VideoCapture InputStream;

	//threshImage threshImg;

	//const char *cstr1a = "Hello Out There.";

	//basic_string <char> str1a(inputPath);

	//cout << "The string initialized by C-string cstr1a is: " << str1a << endl;

	//fs::path::string_type foo = "C:/opencv/projects/car detection/M6_Motorway_Traffic";

	//parseImageInput imgIO(inputPath);

	/*int i = std::count_if(fs::directory_iterator(str1a),
		fs::directory_iterator(),
		[](const fs::directory_entry& e) {
		cout << e << endl;
		return e.path().extension() == ".jpg";
	});*/

	//for (auto& p : fs::directory_iterator(inputPath)){
	//	path foo(inputPath);
	//	std::cout << p.path() << '\n';
	//}

	//cout << "The string initialized by C-string cstr1a is: " << str1a << endl;

	//parseImageInput imgIO(inputPath);
	//imgIO.ListAllFilesInDir();
	//totalframes = imgIO.get_filenames();

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
