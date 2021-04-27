#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "../../app/include/sound.h"

// function sound prototype of constructor
void sound::tone(double Hz_Ss, int duration_Ss) {
    Hz_S = Hz_Ss;
    duration_S = duration_Ss;

    // play wave
    Beep((double)Hz_S, (int)duration_S * 10);
}