#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ModConfig.h"
#include "modcfg_private.h" 
#include "modcfg_file_proc.h"

int modcfg_create(MODCFG* modPtr, char* filePath)
{
	int iResult;
	int readStatus = READ_INIT;
	int retValue = MODCFG_NO_ERROR;
	void* tmpPtr = NULL;
	FILE* fileRead;

	struct MODCFG_STRUCT* modRef = NULL;
	
	// Open file
	fileRead = fopen(filePath, "r");
	if(fileRead == NULL)
	{
		retValue = MODCFG_FILE_FAILED;
		goto RET;
	}
	else
	{
		fseek(fileRead, 0, SEEK_END);
		rewind(fileRead);
	}

	// Memory allocation: ModConfig structure;
	modRef = (struct MODCFG_STRUCT*)malloc(sizeof(struct MODCFG_STRUCT));
	if(modRef == NULL)
	{
		retValue = MODCFG_MEM_FAILED;
		goto RET;
	}
	else
	{
		modRef->modCount = 0;
		modRef->modList = NULL;
	}

	// Reading
	while(!feof(fileRead))
	{
		switch(readStatus)
		{
		case READ_INIT:
			// Memory allocation: module structure
			tmpPtr = realloc(modRef->modList, sizeof(modRef->modCount + 1) * sizeof(struct MODCFG_MODULE));
			if(tmpPtr == NULL)
			{
				retValue = MODCFG_MEM_FAILED;
				goto ERR;
			}
			else
			{
				modRef->modList = (struct MODCFG_MODULE*)tmpPtr;
				modRef->modCount++;
				tmpPtr = NULL;
			}

			iResult = modcfg_read_module(&modRef->modList[modRef->modCount - 1], fileRead);
			if(iResult != MODCFG_NO_ERROR)
			{
				retValue = iResult;
				goto ERR;
			}

		case READ_BLOCK_END:
			readStatus = READ_INIT;
			break;

		default:
			retValue = MODCFG_SYNTAX_ERROR;
			goto ERR;
		}
	}

	if(readStatus != READ_BLOCK_END)
	{
		retValue = MODCFG_SYNTAX_ERROR;
		goto ERR;
	}

ERR:
	modcfg_delete((MODCFG*)modRef);
	*modPtr = NULL;

RET:
	if(tmpPtr != NULL)
		free(tmpPtr);

	if(fileRead != NULL)
		fclose(fileRead);
	
	return retValue;
}

