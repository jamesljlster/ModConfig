#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ModConfig.h"
#include "modcfg_private.h" 
#include "modcfg_file_proc.h"

int modcfg_create(MODCFG* modPtr, char* filePath)
{
	int i, j;
	int iResult;
	int retValue = MODCFG_NO_ERROR;
	
	int strCount = 0;
	char** strList = NULL;
	struct STR_TREE* strTree = NULL;
	struct MODCFG_STRUCT* modStruct = NULL;

	// Create string tree
	iResult = modcfg_create_str_tree(&strTree, filePath);
	if(iResult != MODCFG_NO_ERROR)
	{
		retValue = iResult;
		goto RET;
	}

	printf("create str tree succeed\n");

	// Checking
	if(strTree->childCount <= 0)
	{
		retValue = MODCFG_SYNTAX_ERROR;
		goto ERR;
	}

	printf("checking passed\n");

	// Memory allocation: module structure
	modStruct = (struct MODCFG_STRUCT*)malloc(sizeof(struct MODCFG_STRUCT));
	if(modStruct == NULL)
	{
		retValue = MODCFG_MEM_FAILED;
		goto ERR;
	}

	printf("module structure created\n");
	
	modStruct->modCount = strTree->childCount;
	modStruct->modList = (struct MODCFG_MODULE*)malloc(sizeof(struct MODCFG_MODULE) * strTree->childCount);
	if(modStruct->modList == NULL)
	{
		retValue = MODCFG_MEM_FAILED;
		goto ERR;
	}
	else
	{
		for(i = 0; i < modStruct->modCount; i++)
		{
			modStruct->modList[i].modType = NULL;
			modStruct->modList[i].modName = NULL;	
			modStruct->modList[i].memberList = NULL;
			modStruct->modList[i].memberCount = 0;
		}
	}

	for(i = 0; i < modStruct->modCount; i++)
	{
		modStruct->modList[i].memberCount = strTree->child[i].strCount;
		modStruct->modList[i].memberList = (struct MODCFG_MEMBER*)malloc(sizeof(struct MODCFG_MEMBER) * strTree->child[i].strCount);
		if(modStruct->modList[i].memberList == NULL)
		{
			retValue = MODCFG_MEM_FAILED;
			goto ERR;
		}
		else
		{
			for(j = 0; j < modStruct->modList[i].memberCount; j++)
			{
				modStruct->modList[i].memberList[j].idStr = NULL;
				modStruct->modList[i].memberList[j].content = NULL;
			}
		}
	}

	// Assign value
	*modPtr = modStruct;

	goto RET;

ERR:
	printf("ERR\n");
	modcfg_delete(modStruct);

RET:
	printf("debug\n");

	for(i = 0; i < strCount; i++)
	{
		if(strList[i] != NULL)
			free(strList[i]);
	}

	if(strList != NULL)
		free(strList);

	if(strTree != NULL)
		modcfg_delete_str_tree(strTree);

	return retValue;
}

int modcfg_str_extract(char*** strListPtr, int* strCountPtr, char* src)
{
	int retValue = MODCFG_NO_ERROR;

	int forceRead = 0;
	int procIndex = 0;

	int strCount = 0;
	char** strList = NULL;
	int strBufLen = 1;
	char* strBuf = NULL;
	void* allocTmp = NULL;

	// Processing
	while(src[procIndex] != '\0')
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
			strBufLen++;
			allocTmp = realloc(strBuf, sizeof(char) * strBufLen);
			if(allocTmp == NULL)
			{
				retValue = MODCFG_MEM_FAILED;
				goto ERR;
			}
			else
			{
				strBuf = (char*)allocTmp;
				allocTmp = NULL;

				strBuf[strBufLen - 1] = '\0';
				strBuf[strBufLen - 2] = src[procIndex];
			}
		}
		else
		{
			switch(src[procIndex])
			{
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
				strBufLen++;
				allocTmp = realloc(strBuf, sizeof(char) * strBufLen);
				if(allocTmp == NULL)
				{
					retValue = MODCFG_MEM_FAILED;
					goto ERR;
				}
				else
				{
					strBuf = (char*)allocTmp;
					allocTmp = NULL;

					strBuf[strBufLen - 1] = '\0';
					strBuf[strBufLen - 2] = src[procIndex];
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
