#ifndef JGW_COMPILE_WAV_H
#define JGW_COMPILE_WAV_H

/* Library C++ */
#include <fstream>
#include <string>

// class Sine Oscillator
class SineOscillator {
    float frequency, amplitude, angle = 0.0f, offset = 0.0f;
public:
    SineOscillator(float freq, float amp);

    void update(float freq, float amp);

    float process();
};

// write file for wav compile
void writeToFile(std::ofstream &file, int value, float size);

// function start compile into wav format
void StartConvert(std::string nameFile);

class JGW_COMPILE_WAV {
public:
	int main(int argc, const char** argv);
};

#endif // JGW_COMPILE_WAV_H