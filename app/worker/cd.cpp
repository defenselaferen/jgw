#include "../include/CCM_Header.h"
#include "../include/cd.h"

void cd(std::vector<std::string>& prms) {
    #ifdef _WIN32
        SetCurrentDirectoryA(prms[1].c_str());
    #else
        {
        	auto temp = chdir(prms[1].c_str());
        }
    #endif
}