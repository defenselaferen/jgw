#ifndef JGW_H
#define JGW_H

/* jgw.h
 * 
 * this header for library development jgw
 * for read file binary note music
 */

/* Library C++ */
#include <vector>
#include <string>

#ifdef _WIN32
	#ifdef __cplusplus
		extern "C" {
	#endif

	#ifdef BUILD_LIBRARY_JGW
		#define JGW __declspec(dllexport)
	#else
		#define JGW __declspec(dllimport)
	#endif
#endif

#ifndef JGW_STRUCTURES_H
#define JGW_STRUCTURES_H

	// structure
	struct _CompileSound { // variable for scripting
		double S_HZ; // variable for frequency (Hz)
		float D_DURATION; // variable duration sound (cs)
		unsigned int duplicate = 1; // variable to know how many duplicate
	};

	typedef struct _CompileSound compileSound;

#endif //JGW_STRUCTURES_H

// script of sound.hpp
#ifndef JGW_SOUNDS_H
#define JGW_SOUNDS_H

	class jgw_sound {
	private:
		// make variable for Hz_S
		double Hz_S; // variable for frequency (Hz)
		int duration_S; // variable for duration (cs)
	public:
		// function constructor
		void tone(double Hz_Ss, int duration_Ss);
	};

#endif // end of JGW_SOUNDS_H

#ifndef JGW_PLAYS_H
#define JGW_PLAYS_H

	/* Library C++ */
	#include <vector>
	#include <string>

	class JGW_PLAYS {
	private:
		// function SetStructRefrenchToZero
		void SetStructRefrenchToZero(std::vector<compileSound>& __BUFF__);
	private:
		// function PrintDev
		void PrintDev(int index, double SSH_Z, float CCS_Z);
	private:
		// function startMusic
		void StartMusic(std::string nameFile);
	public:
		int play(int argc, const char** argv);
	};

#endif // JGW_PLAYS_H

// script of filehelp.hpp

#ifndef _FILESHELP_HPP
#define _FILESHELP_HPP

	/* Library C++ */
	#include <ios>
	#include <fstream>

	// class FILESHELP
	class FILESHELP {
	private:
		// variable settings in here
		std::string namefile; // variable namefile
	public:
		// function constructor for fill variable FILESHELP
		FILESHELP(const char* nameFile);
	public:
		// function open and close file
		// function for open file
		void F_openFile();
		// function for close file
		void F_closeFile();
	public:
		// return refrencf fstream variable
		std::fstream& getVarFile();
	public:
		// function for check file its exist
		bool itsExist();
	public:
		// function for get all string file
		std::string getFile();
	};

#endif // _FILESHELP_HPP

#ifdef _WIN32
	#ifdef __cplusplus
		}
	#endif
#endif

#endif