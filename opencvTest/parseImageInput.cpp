#include "parseImageInput.h"

parseImageInput::parseImageInput(string filepath_) {
	filepath = filepath_;
}

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

vector<string> parseImageInput::getfiles(wchar_t *folder)
{
	std::vector<std::string> vec;

	WIN32_FIND_DATA ffd;

	LPCWSTR foo = (LPCWSTR)folder;
	HANDLE handle = FindFirstFile(foo, &ffd);
	if (handle != INVALID_HANDLE_VALUE)
	{
		do {

			wstring tmp = ffd.cFileName;
			string newstr(tmp.begin(), tmp.end());

			// for whatever reason there 1 dot followed by another line with 2 dots. this makes the counter off by 2.
			if (newstr.length() > 5) {
				vec.push_back(newstr);
			}

		} while (FindNextFile(handle, &ffd));
		FindClose(handle);
	}
	else
	{
		OutputDebugString(L"Nothing to display \n");
	}

	FindClose(handle);

	return vec;
}

