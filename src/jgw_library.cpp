/* Library C++ */
#include <iostream>
// for lubrary include for linux
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>

// Library C
#include <stdio.h>
#include <stdlib.h>

// Library C++
#include <queue>
#include <cmath>

#include "../include/jgw.h"

#ifdef _WIN32
	// function sound prototype of constructor
	void jgw_sound::tone(double Hz_Ss, int duration_Ss) {
	    Hz_S = Hz_Ss;
	    duration_S = duration_Ss;

	    // play wave
	    Beep((double)Hz_S, (int)duration_S * 10);
	}
#else
	// structure of BeepObject
	struct BeepObject
	{
	    double freq;
	    int samplesLeft;
	};

	// class for beeper
	class Beeper {
	    private:
	        double v;
	        std::queue<BeepObject> beeps;
	    public:
	        Beeper();
	        ~Beeper();
	        void beep(double freq, int duration);
	        void generateSamples(Sint16 *stream, int length);
	        void wait();
	};

	// function audio callback
	void audio_callback(void*, Uint8*, int);

	// variable for settings
	const int AMPLITUDE = 28000;
	const int FREQUENCY = 44100;

	// function contructor prototype
	Beeper::Beeper() {
	    SDL_AudioSpec desiredSpec;

	    desiredSpec.freq = FREQUENCY;
	    desiredSpec.format = AUDIO_S16SYS;
	    desiredSpec.channels = 1;
	    desiredSpec.samples = 2048;
	    desiredSpec.callback = audio_callback;
	    desiredSpec.userdata = this;

	    SDL_AudioSpec obtainedSpec;

	    // you might want to look for errors here
	    SDL_OpenAudio(&desiredSpec, &obtainedSpec);

	    // start play audio
	    SDL_PauseAudio(0);
	}

	// function deconstructor prototype
	Beeper::~Beeper() {
	    SDL_CloseAudio();
	}

	// function generate sample
	void Beeper::generateSamples(Sint16 *stream, int length)
	{
	    int i = 0;
	    while (i < length) {

	        if (beeps.empty()) {
	            while (i < length) {
	                stream[i] = 0;
	                i++;
	            }
	            return;
	        }
	        BeepObject& bo = beeps.front();

	        int samplesToDo = std::min(i + bo.samplesLeft, length);
	        bo.samplesLeft -= samplesToDo - i;

	        while (i < samplesToDo) {
	            stream[i] = AMPLITUDE * std::sin(v * 2 * M_PI / FREQUENCY);
	            i++;
	            v += bo.freq;
	        }

	        if (bo.samplesLeft == 0) {
	            beeps.pop();
	        }
	    }
	}

	// function prototype beepe
	void Beeper::beep(double freq, int duration)
	{
	    BeepObject bo;
	    bo.freq = freq;
	    bo.samplesLeft = duration * FREQUENCY / 1000;

	    SDL_LockAudio();
	    beeps.push(bo);
	    SDL_UnlockAudio();
	}

	// function protype wait
	void Beeper::wait()
	{
	    int size;
	    do {
	        SDL_Delay(20);
	        SDL_LockAudio();
	        size = beeps.size();
	        SDL_UnlockAudio();
	    } while (size > 0);

	}

	// function prototype audio_callback
	void audio_callback(void *_beeper, Uint8 *_stream, int _length)
	{
	    Sint16 *stream = (Sint16*) _stream;
	    int length = _length / 2;
	    Beeper* beeper = (Beeper*) _beeper;

	    beeper->generateSamples(stream, length);
	}

	// function sound prototype of constructor
	void jgw_sound::tone(double Hz_Ss, int duration_Ss) {
	    Hz_S = Hz_Ss;
	    duration_S = duration_Ss;

	    SDL_Init(SDL_INIT_AUDIO);

	    // Duration
	    int duration = duration_S * 10;
	    double Hz = Hz_S;

	    // Varibale Beeper
	    Beeper b;
	    b.beep(Hz, duration);
	    b.wait();
	}
#endif

namespace _TEMP_ {
	// make variable for file management
	std::fstream frmXFile;
};

// fill variable name file
FILESHELP::FILESHELP(const char* nameFile) :
	namefile(nameFile) {}

// function for openFile in this script
void S_openFile(std::fstream& frmXFile, std::string& nameFile) {
	frmXFile.open(nameFile, std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
	if(!frmXFile.is_open()) {
		frmXFile.close();
		frmXFile.open(nameFile, std::ios::trunc | std::ios::in | std::ios::out | std::ios::ate | std::ios::binary);
	}
}

// function for close file in this script
void S_closeFile(std::fstream& frmXFile) {
	frmXFile.close();
}

// function for open file
void FILESHELP::F_openFile() {
	// openfile
	S_openFile(_TEMP_::frmXFile, namefile);
}

// function for close file
void FILESHELP::F_closeFile() {
	// close file
	S_closeFile(_TEMP_::frmXFile);
}

// return fstream variable in this function
std::fstream& FILESHELP::getVarFile() {
	return _TEMP_::frmXFile;
}

bool FILESHELP::itsExist() {
	_TEMP_::frmXFile.open(namefile, std::ios::in | std::ios::out | std::ios::binary);
	if(!_TEMP_::frmXFile.is_open()) {
		_TEMP_::frmXFile.close();
		return 0;
	}
	_TEMP_::frmXFile.close();
	return 1;
}

std::string FILESHELP::getFile() {
	std::fstream inputFile;
	std::string _BUFFER_;

	inputFile.open(namefile, std::ios::in);
	if(!inputFile.is_open())
	{
		return "";
	}

	int indexes = 0;
	while(!inputFile.eof())
	{
		std::string _TEMP_;
		getline(inputFile, _TEMP_);

		if(indexes == 0) {
			_BUFFER_ += _TEMP_;
			indexes += 1;
		} else {
			_BUFFER_ += " " + _TEMP_;
		}
	}
	inputFile.close();

	return _BUFFER_;
}

void JGW_PLAYS::SetStructRefrenchToZero(std::vector<compileSound>& __BUFF__)
{
	__BUFF__[__BUFF__.size() - 1].S_HZ = 0;
	__BUFF__[__BUFF__.size() - 1].D_DURATION = 0;
}

void JGW_PLAYS::PrintDev(int index, double SSH_Z, float CCS_Z)
{
	std::cout << index + 1 << ". " << (double)SSH_Z << "Hz | ";
	std::cout << CCS_Z << "ms" << std::endl;
}

void JGW_PLAYS::StartMusic(std::string nameFile)
{
	FILESHELP FSH_I(nameFile.c_str());
	switch(FSH_I.itsExist()) {
		case false: {
			std::cout << "Undefined File Name : " << nameFile << std::endl;
		}
		break;
	}

	FSH_I.F_openFile();
	std::vector<compileSound> compilingSoundGet;

	for(int i = 0; i < FSH_I.getVarFile().tellg(); i += 1)
	{
		compileSound _BUFF_;
		FSH_I.getVarFile().seekg(i * sizeof(compileSound));

		FSH_I.getVarFile().read((char*)&_BUFF_, sizeof(compileSound));
		
		for(unsigned int j = 0; j < _BUFF_.duplicate; j++) {
			compilingSoundGet.push_back(_BUFF_);
		}
	}

	SetStructRefrenchToZero(compilingSoundGet);

	for(unsigned int i = 0; i < compilingSoundGet.size(); i++)
	{
		#ifdef _DEV
			PrintDev((int)i, (double)compilingSoundGet[i].S_HZ, (float)compilingSoundGet[i].D_DURATION);
		#endif
		jgw_sound snd;
		snd.tone((double)compilingSoundGet[i].S_HZ, (float)compilingSoundGet[i].D_DURATION);
	}
	FSH_I.F_closeFile();
}

int JGW_PLAYS::play(int argc, const char* argv[]) {
	for(int i = 0; i < argc; i++) {
		StartMusic(argv[i]);
	}
	return 0;
}