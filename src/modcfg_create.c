#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ModConfig.h"
#include "modcfg_private.h" 
#include "modcfg_file_proc.h"

#include "debug.h"

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

	LOG("enter");

	// Zero memory
	tmpMember.idStr = NULL;
	tmpMember.content = NULL;

	tmpModule.modName = NULL;
	tmpModule.modType = NULL;
	tmpModule.memberCount = 0;
	tmpModule.memberList = 0;

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
	else
	{
		modStruct->modCount = 0;
		modStruct->modList = NULL;
	}

	// Extract string tree to module
	for(i = 0; i < strTree->childCount; i++)
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
			LOG("header str count: %d", strCount);
			retValue = MODCFG_SYNTAX_ERROR;
			goto ERR;
		}
		else
		{
			modType = modcfg_get_type_id(strList[0]);
			if(modType < 0)
			{
				LOG("modcfg_get_type_id() failed");
				retValue = MODCFG_SYNTAX_ERROR;
				goto ERR;
			}
		}
		
		// Assign string to temp module
		tmpModule.modType = strList[0];
		tmpModule.modName = strList[1];

		// Free string list
		free(strList);
		strList = NULL;
		strCount = 0;

		// Append members to temp module
		for(j = 0; j < strTree->child[i].strCount; j++)
		{
			// Extract strings
			iResult = modcfg_str_extract(&strList, &strCount, strTree->child[i].strList[j]);
			if(iResult != MODCFG_NO_ERROR)
			{
				retValue = iResult;
				goto ERR;
			}

			// Checking
			LOG("modType = %d", modType);
			switch(modType)
			{
				case MODCFG_TYPE_MODULE:
					if(strCount > 2)
					{
						retValue = MODCFG_SYNTAX_ERROR;
						goto ERR;
					}
					break;

				case MODCFG_TYPE_LIST:
					if(strCount > 1)
					{
						retValue = MODCFG_SYNTAX_ERROR;
						goto ERR;
					}
					break;

				default:
					retValue = MODCFG_SYNTAX_ERROR;
					goto ERR;
			}

			// Assign string to temp member
			tmpMember.idStr = strList[0];
			if(strCount > 1)
			{
				tmpMember.content = strList[1];
			}
			else
			{
				tmpMember.content = NULL;
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
	LOG("error dealing");

	modcfg_delete_module(&tmpModule);
	modcfg_delete_member(&tmpMember);
	modcfg_delete(modStruct);

RET:
	LOG("Cleanup");

	for(i = 0; i < strCount; i++)
	{
		if(strList[i] != NULL)
			free(strList[i]);
	}

	if(strList != NULL)
		free(strList);

	if(strTree != NULL)
		modcfg_delete_str_tree(strTree);
	
	LOG("exit");

	return retValue;
}

