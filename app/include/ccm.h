#ifdef __cplusplus
// #including library
#include <string>

// Check if CCM_H its exist or not
// If Not Exist This script run

    #ifndef CCM_H
    #define CCM_H

        // If Windows x32 and x64
        #ifdef _WIN32
            // Windows Header File
            #include "windows.h"
        #else
            // Linux Header File
            #include "linux.h"
        #endif

    #endif

#endif