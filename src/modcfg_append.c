#include <stdlib.h>
#include <string.h>

#include "ModConfig.h"
#include "modcfg_private.h"

int modcfg_append(MODCFG* modPtr, char* filePath)
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
	int retValue = MODCFG_NO_ERROR;
	void* allocTmp = NULL;	

	// Memory allocation
	allocTmp = realloc(dst->memberList, sizeof(struct MODCFG_MEMBER) * (dst->memberCount + 1));
	if(allocTmp == NULL)
	{
		retValue = MODCFG_MEM_FAILED;
		goto RET;
	}
	else
	{
		dst->memberCount += 1;
		dst->memberList = (struct MODCFG_MEMBER*)allocTmp;
		allocTmp = NULL;

		dst->memberList[dst->memberCount - 1].idStr = src->idStr;
		dst->memberList[dst->memberCount - 1].content = src->content;

		src->idStr = NULL;
		src->content = NULL;
	}

	goto RET;

RET:
	if(allocTmp != NULL)
		free(allocTmp);

	return retValue;
}

int modcfg_append_module(struct MODCFG_STRUCT* dst, struct MODCFG_MODULE* src)
{
	int retValue = MODCFG_NO_ERROR;
	void* allocTmp = NULL;

	// Memory allocation
	allocTmp = realloc(dst->modList, sizeof(struct MODCFG_MODULE) * (dst->modCount + 1));
	if(allocTmp == NULL)
	{
		retValue = MODCFG_MEM_FAILED;
		goto RET;
	}
	else
	{
		dst->modCount += 1;
		dst->modList = (struct MODCFG_MODULE*)allocTmp;
		allocTmp = NULL;

		dst->modList[dst->modCount - 1].modName = src->modName;
		dst->modList[dst->modCount - 1].modType = src->modType;
		dst->modList[dst->modCount - 1].memberCount = src->memberCount;
		dst->modList[dst->modCount - 1].memberList = src->memberList;

		src->modName = NULL;
		src->modType = NULL;
		src->memberCount = 0;
		src->memberList = NULL;
	}

	goto RET;

RET:
	if(allocTmp != NULL)
		free(allocTmp);

	return retValue;
}

