#include <stdlib.h>
#include <string.h>

#include "modcfg.h"
#include "modcfg_private.h"

#include "debug.h"

int modcfg_append(MODCFG* modPtr, const char* filePath)
{
	int iResult;
	int retValue = MODCFG_NO_ERROR;
	MODCFG tmpMod = NULL;

	// Checking
	if(*modPtr == NULL)
	{
		iResult = modcfg_create(modPtr, filePath);
		retValue = iResult;
		goto RET;
	}
	else
	{
		iResult = modcfg_create(&tmpMod, filePath);
		if(iResult != MODCFG_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}

		iResult = modcfg_merge(modPtr, tmpMod);
		if(iResult != MODCFG_NO_ERROR)
		{
			retValue = iResult;
			goto RET;
		}
	}

RET:
	if(tmpMod != NULL)
		modcfg_delete(tmpMod);

	return retValue;
}

int modcfg_append_member(struct MODCFG_MODULE* dst, struct MODCFG_MEMBER* src)
{
	int iResult;
	int retValue = MODCFG_NO_ERROR;
	struct MODCFG_MODULE tmpModule;
	
	LOG("enter");

	// Set temp module
	tmpModule.modName = dst->modName;
	tmpModule.modType = dst->modType;
	tmpModule.memberCount = 1;
	tmpModule.memberList = src;

	// Merge temp module to dst module
	iResult = modcfg_merge_module(dst, &tmpModule);
	if(iResult != MODCFG_NO_ERROR)
	{
		retValue = iResult;
	}
	else
	{
		modcfg_delete_member(src);
	}

	LOG("exit");

	return retValue;
}

int modcfg_append_module(struct MODCFG_STRUCT* dst, struct MODCFG_MODULE* src)
{
	int iResult;
	int retValue = MODCFG_NO_ERROR;
	struct MODCFG_STRUCT tmpStruct;

	// Set temp struct
	tmpStruct.modCount = 1;
	tmpStruct.modList = src;

	// Merge temp struct to dst struct
	iResult = modcfg_merge_struct(dst, &tmpStruct);
	if(iResult != MODCFG_NO_ERROR)
	{
		retValue = iResult;
	}
	else
	{
		modcfg_delete_module(src);
	}

	return retValue;
}

