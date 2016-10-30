#ifndef _MODCFG_FILE_PROC_H_ 
#define	_MODCFG_FILE_PROC_H_

#include <stdio.h>
#include "modcfg_private.h"

#define LF				0x0A
#define CR				0x0D
#define ASCII_MIN_SIG	0x20
#define ASCII_MAX_SIG	0x7E

enum READ_CHAR_TYPE
{
	READ_ALL,		// Read all type character
	READ_SIG		// Read signaficant character
};

#ifdef __cplusplus
extern "C" {
#endif

char modcfg_get_char(FILE* fileRead, int readAction);
int modcfg_get_string(FILE* fileRead, char** bufRef, int* bufLenRef, char stopChar);

#ifdef __cplusplus
}
#endif

#endif
