#ifdef __cplusplus
#include <iostream>
#include <string>
#endif

#ifdef _WIN32
    #include <windows.h>
    void getColor(WORD color);
#else
    #define F_BLACK 30
    #define F_RED 31
    #define F_GREEN 32
    #define F_YELLOW 33
    #define F_BLUE 34
    #define F_MAGENTA 35
    #define F_CYAN 36
    #define F_WHITE 37

    #define reseting 0
    #define bolds 1
    #define brights 1
    #define underlines 4
    #define inverses 7
    #define boldes  21
    #define bright_off  21
    #define underline_offes 24
    #define inverse_offes 27
    void getColor(std::string& cmd, int color);
#endif
