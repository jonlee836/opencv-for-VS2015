#include "parseImageInput.h"

//parseImageInput::parseImageInput(string filepath_) {
//	filepath = filepath_;
//}
//
//int parseImageInput::get_filenames()
//{
//	basic_string <char> filepath_bs(filepath);
//
//	totalFrames = std::count_if(fs::directory_iterator(filepath), fs::directory_iterator(), [](const fs::directory_entry& e){
//		return e.path().extension() == ".jpg";
//	});
//
//	return totalFrames;
//}

//vector<string> parseImageInput::getfiles(string folder)
//{
//	vector<string> names;
//	string search_path = folder + "/*.*";
//
//	WIN32_FIND_DATA fd;
//	HANDLE hFind = ::FindFirstFile((LPWSTR)search_path.c_str, &fd);
//	if (hFind != INVALID_HANDLE_VALUE) {
//		do {
//			// read all (real) files in current folder
//			// , delete '!' read other 2 default folder . and ..
//			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
//				
//				wchar_t* foo = fd.cFileName;
//				wstring ws(foo);
//				string bar(ws.begin(), ws.end());
//
//				names.push_back(bar);
//
//				cout << bar << endl;
//
//			}
//		} while (::FindNextFile(hFind, &fd));
//		::FindClose(hFind);
//	}
//	return names;
//}