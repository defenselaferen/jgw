#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "../app/include/helper.h"
#include "../app/include/util.h"
#include "../app/include/jgw_play.h"
#include "../app/include/jgw_compile_wav.h"
#include "../app/include/jgw_compile.h"
#include "../app/include/jgw_compile_exec.h"

int main(int argc, const char* argv[]) {
	// variable args renamed from argv variable
	const char* args[argc - 1];

	// fill empty variable in args array
	for(int i = 1; i < argc; i++) {
		args[i - 2] = argv[i];
	}

	// variable for giving in class
	int argc_args = argc - 2;

	// check argc
	switch(argc) {
		case 1: {
			printf("Giving Parmeter (--play, --compile, --compile-wav) <filepath>\n");
			/* End Of Program And Clean */
			{
				(void)argc;
				(void)argv;
			}
			return 0;
		}
		break;
		case 2: {
			printf("Giving Parmeter <filepath>\n");
			/* End Of Program And Clean */
			{
				(void)argc;
				(void)argv;
			}
			return 0;
		}
		break;
	}

	// CHECK
	// IF PLAY
	std::string argvs = argv[1];
	if(argvs == "--play")
	{
		JGW_PLAY jgp;
		jgp.main(argc_args, args);
	}

	// IF COMPILER
	else if(argvs == "--compile")
	{
		JGW_COMPILE jgc;
		jgc.main(argc_args, args);
	}

	// IF COMPILE WAV
	else if(argvs == "--compile-wav")
	{
		JGW_COMPILE_WAV jcw;
		jcw.main(argc_args, args);
	}

	// IF COMPILE TO EXECUTABLE
	else if(argvs == "--compile-exec")
	{
		COMPILE_EXEC CPE;
		CPE.main(argc_args, args);
	}

	// IF NOT EXIST
	else
	{
		std::cout << "Undefined Parameter 1 : " << argv[1] << std::endl;
	}

	/* End Of Program And Clean */
	{
		(void)argc;
		(void)argv;
	}
	return 0;
}