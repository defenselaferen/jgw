// include standard library C++
#include <iostream>
// include library c
#include <stdio.h>
// include library string
// and library stdlib, memory, cstdio, stdexception, map, array, vector
#include <string>
#include <stdlib.h>
#include <memory>
#include <cstdio>
#include <stdexcept>
#include <map>
#include <array>
#include <vector>

// If Windows including direct and Windows
#ifdef _WIN32
    #include <direct.h>
    #include <Windows.h>
    #define GetCurrentDir _getcwd
#else
    // If This Linux
    #include <unistd.h>
    #include <dirent.h>
    #define GetCurrentDir getcwd
 #endif
