#include <stdlib.h>
#include <string.h>

#include "ModConfig.h"
#include "modcfg_file_proc.h"

#include "debug.h"

char* modcfg_str_type[MODCFG_TYPE_AMOUNT] = {
	"module",
	"list"
};

int modcfg_get_type_id(char* src)
{
	int i;
	int retValue = MODCFG_NOT_FOUND;
	
	LOG("enter");
	
	for(i = 0; i < MODCFG_TYPE_AMOUNT; i++)
	{
		if(modcfg_strcmp(src, modcfg_str_type[i]) == 0)
			retValue = i;
	}

	LOG("exit");

	return retValue;
}

int modcfg_strcmp(char* src1, char* src2)
{
	int iResult;
	int retValue = MODCFG_NO_ERROR;
	int len1, len2;

	len1 = strlen(src1);
	len2 = strlen(src2);
	if(len1 != len2)
	{
		retValue = MODCFG_CONFLICT;
	}
	else
	{
		iResult = strncmp(src1, src2, len1);
		if(iResult != 0)
		{
			retValue = MODCFG_CONFLICT;
		}
	}

	return retValue;
}

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

int modcfg_str_extract(char*** strListPtr, int* strCountPtr, char* src)
{
	int iResult;
	int retValue = MODCFG_NO_ERROR;
	
	int finished = 0;
	int forceRead = 0;
	int procIndex = 0;

	int strCount = 0;
	char** strList = NULL;
	int strBufLen = 1;
	char* strBuf = NULL;
	void* allocTmp = NULL;

	// Processing
	while(finished == 0)
	{
		if(src[procIndex] == '"')
		{
			if(strBuf != NULL)
			{
				strCount++;
				allocTmp = realloc(strList, sizeof(char*) * strCount);
				if(allocTmp == NULL)
				{
					retValue = MODCFG_MEM_FAILED;
					goto ERR;
				}
				else
				{
					strList = (char**)allocTmp;
					allocTmp = NULL;
					strList[strCount - 1] = strBuf;
					
					strBuf = NULL;
					strBufLen = 1;
				}
			}

			forceRead = 1 - forceRead;
			procIndex++;
			continue;
		}

		if(forceRead == 1)
		{
			iResult = modcfg_str_append(&strBuf, &strBufLen, src[procIndex]);
			if(iResult != MODCFG_NO_ERROR)
			{
				retValue = iResult;
				goto ERR;
			}
		}
		else
		{
			switch(src[procIndex])
			{
			case '\0':
				finished = 1;

			case ' ':
			case '=':
				if(strBuf != NULL)
				{
					strCount++;
					allocTmp = realloc(strList, sizeof(char*) * strCount);
					if(allocTmp == NULL)
					{
						retValue = MODCFG_MEM_FAILED;
						goto ERR;
					}
					else
					{
						strList = (char**)allocTmp;
						allocTmp = NULL;
						strList[strCount - 1] = strBuf;
						
						strBuf = NULL;
						strBufLen = 1;
					}
				}
				break;

			default:
				iResult = modcfg_str_append(&strBuf, &strBufLen, src[procIndex]);
				if(iResult != MODCFG_NO_ERROR)
				{
					retValue = iResult;
					goto ERR;
				}
			}
		}

		procIndex++;
	}

	// Assign value
	*strListPtr = strList;
	*strCountPtr = strCount;
	
	goto RET;

ERR:
	for(procIndex = 0; procIndex < strCount; procIndex++)
	{
		if(strList[procIndex] != NULL)
			free(strList[procIndex]);
	}

	if(strList != NULL)
		free(strList);

RET:
	if(allocTmp != NULL)
		free(allocTmp);

	if(strBuf != NULL)
		free(strBuf);

	return retValue;
}

