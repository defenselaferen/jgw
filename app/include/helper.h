#ifndef JGW_HELPER_H
#define JGW_HELPER_H

enum _IF_S {
	IF_FALSE = 1,
	IF_TRUE
};

typedef enum _IF_S IF_S;

IF_S IF_T(int _SOURCE_BOOLEAN_);

#endif // JGW_HELPER_H