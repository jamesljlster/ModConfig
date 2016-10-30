#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ModConfig.h"
#include "modcfg_private.h" 
#include "modcfg_file_proc.h"

enum MODULE_STATUS
{
	MODULE_INIT,
	MODULE_TYPE,
	MODULE_NAME,
	MODULE_BLOCK_START,
	MODULE_BLOCK_END,
	MODULE_ASSIGN
};

enum MEMBER_STATUS
{
	MEMBER_INIT,
	MEMBER_NAME,
	MEMBER_EQUAL_CHAR,
	MEMBER_TEXT,
	MEMBER_END,
	MEMBER_ASSIGN
};

int modcfg_create(MODCFG* modPtr, char* filePath)
{
	int iResult;
	int retValue = MODCFG_NO_ERROR;
	int readAction;
	
	char tmpRead;
	int readBufLen = 0;
	char* readBuf = NULL;
	void* tmpPtr = NULL;
	FILE* fileRead;
	
	int moduleStatus;
	struct MODCFG_MODULE tmpModule;

	int memberStatus;
	struct MODCFG_MEMBER tmpMember;
	
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

	// Memory allocation: readBuf
	readBuf = (char*)malloc(sizeof(char));
	if(readBuf == NULL)
	{
		retValue = MODCFG_MEM_FAILED;
		goto RET;
	}
	else
	{
		readBuf[0] = '\0';
		readBufLen = 1;
	}

	// Reading
	moduleStatus = MODULE_INIT;
	memberStatus = MEMBER_INIT;
	readAction = READ_SIG;
	while(!feof(fileRead))
	{
		// Read a character
		tmpRead = modcfg_get_char(fileRead, readAction);
		if(tmpRead > 0)
			printf("%c", tmpRead);
	}

ERR:
	modcfg_delete((MODCFG*)modRef);
	*modPtr = NULL;

RET:
	if(readBuf != NULL)
		free(readBuf);

	if(tmpPtr != NULL)
		free(tmpPtr);

	if(fileRead != NULL)
		fclose(fileRead);
	
	return retValue;
}

