#include <iostream>
#include <string>
#include <fstream>
#include <ios>
#include <array>
#include <vector>
#include <cstring>

#include "../../app/include/util.h"
#include "../../app/include/jgw_compile_exec.h"
#include "../../app/include/structure.h"

std::string source_code_complets;
std::string source_code_main;

void init_source_code() {
	std::array<std::string, 24> source_code_array = {
		"#include <iostream>\n",
		"#include <string>\n",
		"#include <windows.h>\n",
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
		source_code_main,
		"\n",
		"// function sound prototype of constructor\n"
		"void sound::tone(double Hz_Ss, int duration_Ss) {\n",
		"    Hz_S = Hz_Ss;\n",
		"    duration_S = duration_Ss;\n",
		"\n",
		"    // play wave\n",
		"    Beep((double)Hz_S, (int)duration_S * 10);\n",
		"}"
	};
	for(int i = 0; i < ((int)sizeof(source_code_array) / sizeof(std::string)); i++) {
		source_code_complets += source_code_array[i];
	}
}

void startCompile(std::string nameFile) {
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

    std::vector<std::string> source_code_main_vector;
    source_code_main_vector.push_back("int main(int argc, const char* argv[]){\n");

    source_code_main_vector.push_back("\tsound snd;\n");
    for(unsigned int i = 0; i < compilingSoundGet.size(); i++) {
    	source_code_main_vector.push_back("\tsnd.tone(" + std::to_string((double)compilingSoundGet[i].S_HZ) + ", " + std::to_string((int)compilingSoundGet[i].D_DURATION) + ");\n");
    }

    source_code_main_vector.push_back("\t{\n");
    source_code_main_vector.push_back("\t\t(void)argc;\n");
    source_code_main_vector.push_back("\t\t(void)argv;\n");
    source_code_main_vector.push_back("\t}\n");
    source_code_main_vector.push_back("\treturn 0;\n");
    source_code_main_vector.push_back("}\n");

    for(unsigned int i = 0; i < source_code_main_vector.size(); i++) {
    	source_code_main += source_code_main_vector[i];
    }

    init_source_code();
    {
    	std::fstream code_compile;
    	code_compile.open(nameFile + ".cpp", std::ios::trunc | std::ios::out);
    	code_compile << source_code_complets;
    	code_compile.close();

    	std::string cmd = "g++ " + nameFile + ".cpp " + 
    					"-O3 -o " + nameFile + ".exe";
		{
			auto empt = system(cmd.c_str());
		}
    	cmd = "del " + nameFile + ".cpp";
    	{
			auto empt = system(cmd.c_str());
		}
    }
}

int COMPILE_EXEC::main(int argc, const char* argv[]) {
	for(int i = 0; i < argc; i++) {
		startCompile(argv[i]);
	}
	{
		(void)argc;
		(void)argv;
	}
	return 0;
}