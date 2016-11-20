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

	// Extract string tree to module
	for(i = 0; i < modStruct->modCount; i++)
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
		
		// Assign string
		modStruct->modList[i].modType = strList[0];
		modStruct->modList[i].modName = strList[1];
		
		// Free string list
		free(strList);
		strList = NULL;
		strCount = 0;

		// Process member
		for(j = 0; j < modStruct->modList[i].memberCount; j++)
		{
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
				goto ERR;
			}

			// Assign string
			modStruct->modList[i].memberList[j].idStr = strList[0];
			if(strCount > 1)
				modStruct->modList[i].memberList[j].content = strList[1];

			// Free string list
			free(strList);
			strList = NULL;
			strCount = 0;
		}
	}

	// Assign value
	*modPtr = modStruct;

	goto RET;

ERR:
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

