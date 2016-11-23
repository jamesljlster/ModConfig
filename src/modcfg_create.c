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
	int modType;
	int retValue = MODCFG_NO_ERROR;
	
	int strCount = 0;
	char** strList = NULL;
	struct STR_TREE* strTree = NULL;
	struct MODCFG_STRUCT* modStruct = NULL;

	struct MODCFG_MEMBER tmpMember;
	struct MODCFG_MODULE tmpModule;

	// Create string tree
	iResult = modcfg_create_str_tree(&strTree, filePath);
	if(iResult != MODCFG_NO_ERROR)
	{
		retValue = iResult;
		goto RET;
	}

	// Checking
	if(strTree->childCount <= 0)
	{
		retValue = MODCFG_SYNTAX_ERROR;
		goto ERR;
	}

	// Memory allocation: module structure
	modStruct = (struct MODCFG_STRUCT*)malloc(sizeof(struct MODCFG_STRUCT));
	if(modStruct == NULL)
	{
		retValue = MODCFG_MEM_FAILED;
		goto ERR;
	}

	// Extract string tree to module
	for(i = 0; i < strTree->strCount; i++)
	{
		iResult = modcfg_str_extract(&strList, &strCount, strTree->child[i].header);
		if(iResult != MODCFG_NO_ERROR)
		{
			retValue = iResult;
			goto ERR;
		}

		// Checking
		if(strCount != 2)
		{
			retValue = MODCFG_SYNTAX_ERROR;
			goto ERR;
		}
		
		// Assign string to temp module
		tmpModule.modType = strList[0];
		tmpModule.modName = strList[1];

		// Free string list
		free(strList);
		strList = NULL;
		strCount = 0;

		// Append members to temp module
		for(j = 0; j < strTree->child[i].childCount; j++)
		{
			// Extract strings
			iResult = modcfg_str_extract(&strList, &strCount, strTree->child[i].strList[j]);
			if(iResult != MODCFG_NO_ERROR)
			{
				retValue = iResult;
				goto ERR;
			}

			// Checking
			if(strCount > 2)
			{
				retValue = MODCFG_SYNTAX_ERROR;
				goto RET;
			}

			// Assign string to temp member
			tmpMember.idStr = strList[0];
			if(strCount > 1)
			{
				tmpMember.content = strList[1];
			}

			// Free string list
			free(strList);
			strList = NULL;
			strCount = 0;

			// Append temp member to temp module
			iResult = modcfg_append_member(&tmpModule, &tmpMember);
			if(iResult != MODCFG_NO_ERROR)
			{
				retValue = iResult;
				goto RET;
			}
		}

		// Append tempt module to struct
		iResult = modcfg_append_module(modStruct, &tmpModule);
		if(iResult != MODCFG_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}
	}

	// Assign value
	*modPtr = modStruct;

	goto RET;

ERR:
	modcfg_delete_module(&tmpModule);
	modcfg_delete_member(&tmpMember);
	modcfg_delete(modStruct);

RET:
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

