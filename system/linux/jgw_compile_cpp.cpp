#include <iostream>
#include <string>
#include <fstream>
#include <ios>
#include <array>
#include <vector>
#include <cstring>

#include "../../app/include/util.h"
#include "../../app/include/jgw_compile_cpp.h"
#include "../../app/include/structure.h"
#include "../../app/include/ccm.h"

std::string source_code_complets_v2;
std::string source_code_main_v2;

void startCompile_v2(std::string nameFile) {
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

    std::vector<std::string> source_code_main_v2_vector;
    source_code_main_v2_vector.push_back("int main(int argc, const char* argv[]){\n");

    source_code_main_v2_vector.push_back("\tsound snd;\n");
    for(unsigned int i = 0; i < compilingSoundGet.size(); i++) {
    	source_code_main_v2_vector.push_back("\tsnd.tone(" + std::to_string((double)compilingSoundGet[i].S_HZ) + ", " + std::to_string((int)compilingSoundGet[i].D_DURATION) + ");\n");
    }

    source_code_main_v2_vector.push_back("\t{\n");
    source_code_main_v2_vector.push_back("\t\t(void)argc;\n");
    source_code_main_v2_vector.push_back("\t\t(void)argv;\n");
    source_code_main_v2_vector.push_back("\t}\n");
    source_code_main_v2_vector.push_back("\treturn 0;\n");
    source_code_main_v2_vector.push_back("}\n");

    for(unsigned int i = 0; i < source_code_main_v2_vector.size(); i++) {
    	source_code_main_v2 += source_code_main_v2_vector[i];
    }

    std::array<std::string, 154> source_code_array = {
		"#include <iostream>\n",
		"#include <string>\n",
		"// for lubrary include for linux\n",
		"#include <SDL2/SDL.h>\n",
		"#include <SDL2/SDL_audio.h>\n",
		"// Library C++\n",
		"#include <queue>\n",
		"#include <cmath>\n",
		"\n",
		"// structure of BeepObject\n",
		"struct BeepObject\n",
		"{\n",
		"    double freq;\n",
		"    int samplesLeft;\n",
		"};\n",
		"\n",
		"class sound {\n",
		"private:\n",
		"	// make variable for Hz_S\n",
		"	double Hz_S; // variable for frequency (Hz)\n",
		"	int duration_S; // variable for duration (cs)\n",
		"public:\n",
		"	// function constructor\n",
		"	void tone(double Hz_Ss, int duration_Ss);\n",
		"};\n",
		"\n",
		"// class for beeper\n"
		"class Beeper {\n"
		"    private:\n",
		"        double v;\n",
		"        std::queue<BeepObject> beeps;\n",
		"    public:\n",
		"        Beeper();\n",
		"        ~Beeper();\n",
		"        void beep(double freq, int duration);\n",
		"        void generateSamples(Sint16 *stream, int length);\n",
		"        void wait();\n",
		"};\n",
		"\n",
		"// function audio callback\n",
		"void audio_callback(void*, Uint8*, int);\n",
		"\n",
		"// variable for settings\n",
		"const int AMPLITUDE = 28000;\n",
		"const int FREQUENCY = 44100;\n",
		"\n",
		source_code_main_v2,
		"\n",
		"// function contructor prototype\n",
		"Beeper::Beeper() {\n",
		"    SDL_AudioSpec desiredSpec;\n",
		"\n",
		"    desiredSpec.freq = FREQUENCY;\n",
		"    desiredSpec.format = AUDIO_S16SYS;\n",
		"    desiredSpec.channels = 1;\n",
		"    desiredSpec.samples = 2048;\n",
		"    desiredSpec.callback = audio_callback;\n",
		"    desiredSpec.userdata = this;\n",
		"\n",
		"    SDL_AudioSpec obtainedSpec;\n",
		"\n",
		"    // you might want to look for errors here\n",
		"    SDL_OpenAudio(&desiredSpec, &obtainedSpec);\n",
		"\n",
		"    // start play audio\n",
		"    SDL_PauseAudio(0);\n",
		"}\n",
		"\n",
		"// function deconstructor prototype\n",
		"Beeper::~Beeper() {\n",
		"    SDL_CloseAudio();\n",
		"}\n",
		"\n",
		"// function generate sample\n",
		"void Beeper::generateSamples(Sint16 *stream, int length)\n",
		"{\n",
		"    int i = 0;\n",
		"    while (i < length) {\n",
		"\n",
		"        if (beeps.empty()) {\n",
		"            while (i < length) {\n",
		"                stream[i] = 0;\n",
		"                i++;\n",
		"            }\n",
		"            return;\n",
		"        }\n",
		"        BeepObject& bo = beeps.front();\n",
		"\n",
		"        int samplesToDo = std::min(i + bo.samplesLeft, length);\n",
		"        bo.samplesLeft -= samplesToDo - i;\n",
		"\n",
		"        while (i < samplesToDo) {\n",
		"            stream[i] = AMPLITUDE * std::sin(v * 2 * M_PI / FREQUENCY);\n",
		"            i++;\n",
		"            v += bo.freq;\n",
		"        }\n",
		"\n",
		"        if (bo.samplesLeft == 0) {\n",
		"            beeps.pop();\n",
		"        }\n",
		"	}\n",
		"}\n",
		"\n",
		"// function prototype beepe\n",
		"void Beeper::beep(double freq, int duration)\n",
		"{\n",
		"    BeepObject bo;\n",
		"    bo.freq = freq;\n",
		"    bo.samplesLeft = duration * FREQUENCY / 1000;\n",

		"    SDL_LockAudio();\n",
		"    beeps.push(bo);\n",
		"    SDL_UnlockAudio();\n",
		"}\n",

		"// function protype wait\n",
		"void Beeper::wait()\n",
		"{\n",
		"    int size;\n",
		"    do {\n",
		"        SDL_Delay(20);\n",
		"        SDL_LockAudio();\n",
		"        size = beeps.size();\n",
		"        SDL_UnlockAudio();\n",
		"    } while (size > 0);\n",
		"\n",
		"}\n",
		"\n",
		"// function prototype audio_callback\n"
		"void audio_callback(void *_beeper, Uint8 *_stream, int _length)\n",
		"{\n"
		"    Sint16 *stream = (Sint16*) _stream;\n",
		"    int length = _length / 2;\n",
		"    Beeper* beeper = (Beeper*) _beeper;\n",
		"\n",
		"    beeper->generateSamples(stream, length);\n",
		"}\n",
		"\n",
		"// function sound prototype of constructor\n"
		"void sound::tone(double Hz_Ss, int duration_Ss) {\n"
		"    Hz_S = Hz_Ss;\n"
		"    duration_S = duration_Ss;\n"
		"\n",
		"    SDL_Init(SDL_INIT_AUDIO);\n"
		"\n",
		"    // Duration\n"
		"    int duration = duration_S * 10;\n"
		"    double Hz = Hz_S;\n"
		"\n",
		"    // Varibale Beeper\n",
		"    Beeper b;\n",
		"    b.beep(Hz, duration);\n",
		"    b.wait();\n",
		"}"
	};
	for(int i = 0; i < ((int)sizeof(source_code_array) / sizeof(std::string)); i++) {
		source_code_complets_v2 += source_code_array[i];
	}

    {
    	std::fstream code_compile;
    	code_compile.open(nameFile + "_S.cpp", std::ios::trunc | std::ios::out);
    	code_compile << source_code_complets_v2;
    	code_compile.close();
	    
	std::string cmd = "g++ " + nameFile + "_S.cpp " + 
    					"-O2 `sdl2-config --cflags --libs` -o " + nameFile + ".cpp";
    	ExecutableRun(cmd);
    	cmd = "rm -rf " + nameFile + "_S.cpp";
    	ExecutableRun(cmd);
    }
}

int COMPILE_CPP::main(int argc, const char* argv[]) {
	for(int i = 0; i < argc; i++) {
		startCompile_v2(argv[i]);
	}
	{
		(void)argc;
		(void)argv;
	}
	return 0;
}
