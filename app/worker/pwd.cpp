#include "../include/CCM_Header.h"
#include "../include/pwd.h"
#include "../include/color.h"
#include "../include/exec1.h"

void pwd() {
    #ifdef _WIN32
        char buffer[MAX_PATH];
        GetModuleFileNameA(NULL, buffer, MAX_PATH);
        std::string::size_type pos = std::string(buffer).find_last_of("\\/");

        std::string linkDir = std::string(buffer).substr(0, pos);
        getColor(14);
        std::cout << linkDir << std::endl;
        getColor(15);
    #else
        std::string _Briffing = exec1("pwd");
        getColor(_Briffing, F_YELLOW);
        std::cout << _Briffing << std::endl;
        getColor(_Briffing, reseting);
    #endif
}
