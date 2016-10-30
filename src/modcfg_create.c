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
	
	struct STR_TREE* strTree = NULL;
	
	// Create string tree
	iResult = modcfg_create_str_tree(&strTree, filePath);
	if(iResult != MODCFG_NO_ERROR)
	{
		retValue = iResult;
		goto RET;
	}
	
	goto RET;
ERR:

RET:
	if(strTree != NULL)
		modcfg_delete_str_tree(strTree);

	return retValue;
}


