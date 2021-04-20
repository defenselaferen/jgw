/* Library C++ */
#include <iostream>

#include "../app/include/sound.h"
#include "../app/include/structure.h"
#include "../app/include/fileshelp.h"
#include "../app/include/jgw_play.h"

void JGW_PLAY::SetStructRefrenchToZero(std::vector<compileSound>& __BUFF__)
{
	__BUFF__[__BUFF__.size() - 1].S_HZ = 0;
	__BUFF__[__BUFF__.size() - 1].D_DURATION = 0;
}

void JGW_PLAY::PrintDev(int& index, double& SSH_Z, float& CCS_Z)
{
	std::cout << index + 1 << ". " << (double)SSH_Z << "Hz | ";
	std::cout << CCS_Z << "ms" << std::endl;
}

void JGW_PLAY::StartMusic(std::string nameFile)
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
		
		for(int j = 0; j < _BUFF_.duplicate; j++) {
			compilingSoundGet.push_back(_BUFF_);
		}
	}

	SetStructRefrenchToZero(compilingSoundGet);

	for(int i = 0; i < compilingSoundGet.size(); i++)
	{
		#ifdef _DEV
			PrintDev(i, compilingSoundGet[i].S_HZ, compilingSoundGet[i].D_DURATION);
		#endif
		sound snd;
		snd.tone((double)compilingSoundGet[i].S_HZ, (int)compilingSoundGet[i].D_DURATION);
	}
	FSH_I.F_closeFile();
}

int JGW_PLAY::main(int argc, const char* argv[]) {
	for(int i = 0; i < argc; i++) {
		StartMusic(argv[i]);
	}
	return 0;
}