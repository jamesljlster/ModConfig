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
//			strBufLen++;
//			allocTmp = realloc(strBuf, sizeof(char) * strBufLen);
//			if(allocTmp == NULL)
//			{
//				retValue = MODCFG_MEM_FAILED;
//				goto ERR;
//			}
//			else
//			{
//				strBuf = (char*)allocTmp;
//				allocTmp = NULL;
//
//				strBuf[strBufLen - 1] = '\0';
//				strBuf[strBufLen - 2] = src[procIndex];
//			}
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
//				strBufLen++;
//				allocTmp = realloc(strBuf, sizeof(char) * strBufLen);
//				if(allocTmp == NULL)
//				{
//					retValue = MODCFG_MEM_FAILED;
//					goto ERR;
//				}
//				else
//				{
//					strBuf = (char*)allocTmp;
//					allocTmp = NULL;
//
//					strBuf[strBufLen - 1] = '\0';
//					strBuf[strBufLen - 2] = src[procIndex];
//				}
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
