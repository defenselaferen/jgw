#ifndef JGW_PLAY_H
#define JGW_PLAY_H

/* Library C++ */
#include <vector>
#include <string>
#include "structure.h"

class JGW_PLAY {
private:
	// function SetStructRefrenchToZero
	void SetStructRefrenchToZero(std::vector<compileSound>& __BUFF__);
private:
	// function PrintDev
	void PrintDev(int& index, double& SSH_Z, float& CCS_Z);
private:
	// function startMusic
	void StartMusic(std::string nameFile);
public:
	int main(int argc, const char** argv);
};

#endif // JGW_PLAY_H