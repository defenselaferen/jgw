#include "../include/CCM_Header.h"
#include "../include/exit.h"

void exit() {
    #ifdef _WIN32
        std::exit(0);
    #else
        std::exit(0);
    #endif
}