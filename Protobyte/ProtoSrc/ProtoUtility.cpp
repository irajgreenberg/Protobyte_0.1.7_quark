/*!  \brief  ProtoUtility2.cpp: 
 Utility class, all static functions, includes i/o
 ProtoUtility2.cpp
 Protobyte Library v02
 
 Created by Ira on 9/14/13.
 Copyright (c) 2013 Ira Greenberg. All rights reserved.
 
 Library Usage:
 This work is licensed under the Creative Commons
 Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 To view a copy of this license, visit
 http://creativecommons.org/licenses/by-nc-sa/3.0/
 or send a letter to Creative Commons,
 444 Castro Street, Suite 900,
 Mountain View, California, 94041, USA.
 
 This notice must be retained any source distribution.
 
 \ingroup common
 This class is part of the group common (update)
 \sa NO LINK
 */

#include "ProtoUtility.h"

using namespace ijg;


// static function implementations
std::string ProtoUtility::getPathToOutput() {
	// 1. ensure path is to resources directory
	char cCurrentPath[FILENAME_MAX];

#if defined (__APPLE__)
	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		std::cout << "error loading from relative directory" << std::endl;
		//return errno;
	}
#elif defined(_WIN32) || defined(_WIN64)
	//char full[_MAX_PATH];
	if (_fullpath(cCurrentPath, "", FILENAME_MAX) != NULL) {
		printf("");
	}
	else {
		printf("Invalid path\n");
	}

#endif

	// NOTE - make workspace project relative instead of using default derivedData path in Library
	//std::cout << "cCurrentPath = " << cCurrentPath << std::endl;
	cCurrentPath[sizeof(cCurrentPath)-1] = '\0'; /* not really required */
	
	std::string temp;
	std::string cp;
#if defined (__APPLE__)
	temp = cCurrentPath;;
	cp = "../../../../output/" + temp;
#elif defined(_WIN32) || defined(_WIN64)
	temp = cCurrentPath;;
	//cp = temp+"\\..\\..\\Protobyte\\output\\";
	cp = temp+"\\..\\Output\\";
#endif

	return cp;

}

std::string ProtoUtility::getPathToResources(){

		// 1. ensure path is to resources directory
		char cCurrentPath[FILENAME_MAX];

#if defined (__APPLE__)
		if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
		{
			std::cout << "error loading from relative directory" << std::endl;
			//return errno;
		}
#elif defined(_WIN32) || defined(_WIN64)
		//char full[_MAX_PATH];
		if (_fullpath(cCurrentPath, "", FILENAME_MAX) != NULL) {
			printf("");
		}
		else {
			printf("Invalid path\n");
		}

#endif

		// NOTE - make workspace project relative instead of using default derivedData path in Library
		//std::cout << "cCurrentPath = " << cCurrentPath << std::endl;
		cCurrentPath[sizeof(cCurrentPath)-1] = '\0'; /* not really required */
		std::string cp = cCurrentPath; //cast char[] to string
#if defined(_WIN32) || defined(_WIN64)
		// need to escape backslashes with themselves, ick
		std::string pathExtension = "\\resources\\";
#else
		// osx/posix use "normal" directory dividers
		std::string pathExtension = "/resources/";

#endif

		std::string pathURL = cp + pathExtension;
		return pathURL;

}

std::string ProtoUtility::getBuildPath(){
    
	//*_fullpath(
	//	char *absPath,
	//	const char *relPath,
	//	size_t maxLength
	//	);
	char cCurrentPath[FILENAME_MAX];
#if defined(_WIN32) || defined (_WIN64)
	
	//getFullPath(cCurrentPath, "resources/imgs/vascular.JPG");
	//std::cout << "cCurrentPath = " << cCurrentPath << std::endl;

	//char full[_MAX_PATH];
	if (_fullpath(cCurrentPath, "", _MAX_PATH) != NULL) {
		printf("");
	}
	else {
		printf("Invalid path\n");
	}
#elif defined(__APPLE__)
	// 1. ensure path is to resources directory
	//char cCurrentPath[FILENAME_MAX];
	//GetCurrentDirectory();
	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		std::cout << "error loading from relative directory" << std::endl;
		//return errno;
	}
	// NOTE - make workspace project relative instead of using default derivedData path in Library
	//std::cout << "cCurrentPath = " << cCurrentPath << std::endl;
	cCurrentPath[sizeof(cCurrentPath)-1] = '\0'; /* not really required */
	

#endif

	
	std::string cp = cCurrentPath; //cast char[] to string
    return cp;
}

// get string from file (char* URL input)
std::string ProtoUtility::load(const char* data) {
	//trace("data =", data);
    std::ifstream file(data);
    std::string line, block;
    if (file.is_open()) {
        
        while (!file.eof()) {
            std::getline(file, line);
            block.append(line);
            block.append(std::string("\n"));
        }
        file.close();
        return block;
    } else {
        std::cout << "Unable to open file";
    }
    // never reached - added to squelch ide warning
    return 0;
}





// get string from file (string URL input)
const std::string ProtoUtility::load(std::string data){
    const char *charData = data.c_str();
    return load(charData);
}

// loads image data in .raw format
void ProtoUtility::load(const std::string& url, int w, int h, unsigned char* data) {
    
    FILE * file;
    
    // open texture data
#if defined(_WIN32) || defined (_WIN64)
	//file = fopen_s(url.c_str(), "rb");
	// from: http://social.msdn.microsoft.com/Forums/vstudio/en-US/fac75a89-dc1b-4b3a-b365-1ac151eee63e/using-fopens-again?forum=vcgeneral
	errno_t e = fopen_s( &file, url.c_str(), "rb" );
	if (e != 0) printf("Error Loading File"); // an error occurred
#elif defined(__APPLE__)
	file = fopen(url.c_str(), "rb");
#endif
    
    if (file == NULL) std::cout << "no file data";
    
    // read texture data
    fread(data, w * h * 3, 1, file);
    fclose(file);
    
}

std::vector<std::string> ProtoUtility::getFileNames(std::string dir){
	std::vector<std::string> fileNames;
#if defined(_WIN32) || defined (_WIN64)
    WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	TCHAR szDir[MAX_PATH];
	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;

	

	// Prepare string for use with FindFile functions.  First, copy the
	// string to a buffer, then append '\*' to the directory name.

	StringCchCopy(szDir, MAX_PATH, dir.c_str());
	StringCchCat(szDir, MAX_PATH, TEXT("*"));

	// Find the first file in the directory.

	hFind = FindFirstFile(szDir, &ffd);


	// List all the files in the directory with some info about them.

	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
			//std::string fn(ffd.cFileName);
			//trace(fn);
			//fileNames.push_back(fn);

		}
		else
		{
			filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;
			//_tprintf(TEXT("  %s   %ld bytes\n"), ffd.cFileName, filesize.QuadPart);
			fileNames.push_back(ffd.cFileName);
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	FindClose(hFind);
#endif

	return fileNames;
}



