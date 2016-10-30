#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "modcfg_file_proc.h"

int modcfg_get_string(FILE* fileRead, char** bufRef, int* bufLenRef, char stopChar)
{
	int bufLen;
	char* buf;
	void* tmpPtr;
	
	return 0;
}

char modcfg_get_char(FILE* fileRead, int readAction)
{	
	int iResult;
	int readCount;
	char tmpRead;
	
	// Read a character
	readCount = 1;
	iResult = fread((void*)&tmpRead, sizeof(char), readCount, fileRead);
	if(iResult != readCount)
		goto ERR;

	if(readAction == READ_ALL)
		goto RET;

	// Determint if character is signaficant
	if(tmpRead >= ASCII_MIN_SIG && tmpRead <= ASCII_MAX_SIG)
		goto RET;

ERR:
	return -1;

RET:
	return tmpRead;
}

