#include "../include/color.h"

#ifdef _WIN32
void getColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
#else
void getColor(std::string& cmd, int color) {
    std::string temp = "\033[1;" + std::to_string(color) + "m" + cmd + "\033[0m";
    cmd = temp;
}
#endif