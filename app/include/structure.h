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