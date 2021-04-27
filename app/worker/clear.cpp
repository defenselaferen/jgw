#include "../include/CCM_Header.h"
#include "../include/clear.h"

void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        std::cout << "\033[2J\033[1;1H" << std::endl;
    #endif
}