#include <string>

#include "../include/fileshelp.h"

namespace _TEMP_ {
	// make variable for file management
	std::fstream frmXFile;
};

// fill variable name file
FILESHELP::FILESHELP(const char* nameFile) :
	namefile(nameFile) {}

// function for openFile in this script
void S_openFile(std::fstream& frmXFile, std::string& nameFile) {
	frmXFile.open(nameFile, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
	if(!frmXFile.is_open()) {
		frmXFile.close();
		frmXFile.open(nameFile, std::ios::trunc | std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
	}
}

// function for close file in this script
void S_closeFile(std::fstream& frmXFile) {
	frmXFile.close();
}

// function for open file
void FILESHELP::F_openFile() {
	// openfile
	S_openFile(_TEMP_::frmXFile, namefile);
}

// function for close file
void FILESHELP::F_closeFile() {
	// close file
	S_closeFile(_TEMP_::frmXFile);
}

// return fstream variable in this function
std::fstream& FILESHELP::getVarFile() {
	return _TEMP_::frmXFile;
}

bool FILESHELP::itsExist() {
	_TEMP_::frmXFile.open(namefile, std::ios::in | std::ios::out | std::ios::binary);
	if(!_TEMP_::frmXFile.is_open()) {
		_TEMP_::frmXFile.close();
		return 0;
	}
	_TEMP_::frmXFile.close();
	return 1;
}

std::string FILESHELP::getFile() {
	std::fstream inputFile;
	std::string _BUFFER_;

	inputFile.open(namefile, std::ios::in);
	if(!inputFile.is_open())
	{
		return "";
	}

	int indexes = 0;
	while(!inputFile.eof())
	{
		std::string _TEMP_;
		getline(inputFile, _TEMP_);

		if(indexes == 0) {
			_BUFFER_ += _TEMP_;
			indexes += 1;
		} else {
			_BUFFER_ += " " + _TEMP_;
		}
	}
	inputFile.close();

	return _BUFFER_;
}