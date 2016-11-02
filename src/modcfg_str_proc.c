#include <stdlib.h>

#include "ModConfig.h"

int modcfg_str_append(char** strBufPtr, int* strBufLenPtr, char appendChar)
{
	int tmpStrBufLen = *strBufLenPtr;
	char* tmpStrBuf = *strBufPtr;
	void* allocTmp = NULL;

	// Append character to string buffer
	tmpStrBufLen++;
	allocTmp = realloc(tmpStrBuf, sizeof(char) * tmpStrBufLen);
	if(allocTmp == NULL)
	{
		return MODCFG_MEM_FAILED;
	}
	else
	{
		tmpStrBuf = (char*)allocTmp;
		tmpStrBuf[tmpStrBufLen - 1] = '\0';
		tmpStrBuf[tmpStrBufLen - 2] = appendChar;
	}

	// Assign Value
	*strBufPtr = tmpStrBuf;
	*strBufLenPtr = tmpStrBufLen;

	return MODCFG_NO_ERROR;
}
