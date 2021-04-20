// script of filehelp.hpp

#ifndef _FILESHELP_HPP
#define _FILESHELP_HPP

/* Library C++ */
#include <ios>
#include <fstream>

// class FILESHELP
class FILESHELP {
private:
	// variable settings in here
	std::string namefile; // variable namefile
public:
	// function constructor for fill variable FILESHELP
	FILESHELP(const char* nameFile);
public:
	// function open and close file
	// function for open file
	void F_openFile();
	// function for close file
	void F_closeFile();
public:
	// return refrencf fstream variable
	std::fstream& getVarFile();
public:
	// function for check file its exist
	bool itsExist();
public:
	// function for get all string file
	std::string getFile();
};

#endif // _FILESHELP_HPP