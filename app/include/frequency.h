// script of frequency.hpp
#ifndef JGW_FREQUENCY_H
#define JGW_FREQUENCY_H

/* Library C++ */
#include <map>
#include <string>

#define LengthPolar 60

// class freq
class freq {
private:
	// make variable settings
	bool check; // variable settings check
public:
	// variable map
	// All variable solfège
	std::map<std::string, std::string> solf;
public:
	// function boolean parameter
	freq(bool check);
};

#endif // end of JGW_FREQUENCY_H