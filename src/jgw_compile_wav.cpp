#include <iostream>
#include <cstring>
#include <ios>
#include <cmath>
#include <vector>

#include "../app/include/jgw_compile_wav.h"
#include "../app/include/structure.h"

// variable for settings
const int sampleRate = 44100;
const int bitDepth = 16;

int JGW_COMPILE_WAV::main(int argc, const char* argv[]) {
	for(int i = 0; i < argc; i++) {
		StartConvert(argv[i]);
	}
	return 0;
}

// function proccess from SineOscillator in prototype
float SineOscillator::process() {
    auto sample = amplitude * sin(angle);
    angle += offset;
    return sample;
}

// contructor function from SineOscillator in prototype
SineOscillator::SineOscillator(float freq, float amp)
    : frequency(freq), amplitude(amp) {
    offset = 2 * M_PI * frequency / sampleRate;
}

// function update from SineOscillator in prototype
void SineOscillator::update(float freq, float amp) {
    frequency = freq;
    amplitude = amp;

    offset = 2 * M_PI * frequency / sampleRate;
}

// function write file in prototype
void writeToFile(std::ofstream &file, int value, float size) {
    file.write(reinterpret_cast<const char*> (&value), size);
}

// function start convert in prototype
void StartConvert(std::string nameFile) {
    std::fstream inputFile;
    inputFile.open(nameFile, std::ios::in | std::ios::binary | std::ios::ate);
    std::vector<compileSound> compilingSoundGet;

    for(int i = 0; i < ((int)inputFile.tellg()); i += 1)
    {
        compileSound _BUFF_;
        inputFile.seekg(i * sizeof(compileSound));

        inputFile.read((char*)&_BUFF_, sizeof(compileSound));
        
        for(int j = 0; j < _BUFF_.duplicate; j++) {
            compilingSoundGet.push_back(_BUFF_);
        }
    }

    compilingSoundGet[compilingSoundGet.size() - 1].S_HZ = 0;
    compilingSoundGet[compilingSoundGet.size() - 1].D_DURATION = 0;
    inputFile.close();

    int duration = 0;
    for(int i = 0; i < compilingSoundGet.size(); i++) {
        duration += (((float)compilingSoundGet[i].D_DURATION * 10) / ((float)1000));
    }
    duration += 1;

    std::ofstream audioFile;
    audioFile.open(nameFile + ".wav", std::ios::binary);
    SineOscillator sineOscillator(((float)compilingSoundGet[0].S_HZ), 0.5);

    //Header chunk
    audioFile << "RIFF";
    audioFile << "----";
    audioFile << "WAVE";

    // Format chunk
    audioFile << "fmt ";
    writeToFile(audioFile, 16, 4);
    writeToFile(audioFile, 1, 2);
    writeToFile(audioFile, 1, 2);
    writeToFile(audioFile, sampleRate, 4);
    writeToFile(audioFile, sampleRate * bitDepth / 8, 4 );
    writeToFile(audioFile, bitDepth / 8, 2);
    writeToFile(audioFile, bitDepth, 2);

    //Data chunk
    audioFile << "data";
    audioFile << "----";

    int preAudioPosition = audioFile.tellp();
    int much = (((int)sampleRate * duration) / compilingSoundGet.size()); 
    int indexs = 0;

    auto maxAmplitude = pow(2, bitDepth - 1) - 1;
    for(int i = 0; i < sampleRate * duration; i++ ) {
        sineOscillator.update(((float)compilingSoundGet[((int)i / much)].S_HZ), 0.5);
        auto sample = sineOscillator.process();
        int intSample = static_cast<int> (sample * maxAmplitude);
        writeToFile(audioFile, intSample, 2);
    }
    int postAudioPosition = audioFile.tellp();

    audioFile.seekp(preAudioPosition - 4);
    writeToFile(audioFile, postAudioPosition - preAudioPosition, 4);

    audioFile.seekp(4, std::ios::beg);
    writeToFile(audioFile, postAudioPosition - 8, 4);

    audioFile.close();
}