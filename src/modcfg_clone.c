#include <stdlib.h>
#include <string.h>

#include "modcfg.h"
#include "modcfg_private.h" 

#include "debug.h"

int modcfg_clone(MODCFG* dstModPtr, MODCFG srcMod)
{
	int iResult;
	int retValue = MODCFG_NO_ERROR;
	struct MODCFG_STRUCT* modStruct = NULL;
	struct MODCFG_STRUCT* modSrcRef = (struct MODCFG_STRUCT*)srcMod;

	// Memory allocation: Module structure
	modStruct = (struct MODCFG_STRUCT*)malloc(sizeof(struct MODCFG_STRUCT));
	if(modStruct == NULL)
	{
		retValue = MODCFG_MEM_FAILED;
		goto RET;
	}
	else
	{
		modStruct->modCount = 0;
		modStruct->modList = NULL;
	}

	// Clone structure
	iResult = modcfg_clone_struct(modStruct, modSrcRef);
	if(iResult != MODCFG_NO_ERROR)
	{
		retValue = iResult;
		goto ERR;
	}

	// Assign value
	*dstModPtr = (MODCFG)modStruct;
	
	goto RET;

ERR:
	modcfg_delete(modStruct);

RET:
	return retValue;
}

char* modcfg_str_clone(char* src)
{
	char* dst;

	dst = (char*)malloc(sizeof(char) * (strlen(src) + 1));
	if(dst == NULL)
	{
		return NULL;
	}
	else
	{
		memset(dst, 0, sizeof(char) * (strlen(src) + 1));
	}

	memcpy(dst, src, sizeof(char) * (strlen(src) + 1));

	return dst;
}

int modcfg_clone_member(struct MODCFG_MEMBER* dst, struct MODCFG_MEMBER* src)
{
	int retValue = MODCFG_NO_ERROR;
	
	LOG("enter");
	
	if(src->idStr != NULL)
	{
		dst->idStr = modcfg_str_clone(src->idStr);
		if(dst->idStr == NULL)
		{
			retValue = MODCFG_MEM_FAILED;
			goto RET;
		}
	}
	else
	{
		dst->idStr = NULL;
	}

	if(src->content != NULL)
	{
		dst->content = modcfg_str_clone(src->content);
		if(dst->content == NULL)
		{
			retValue = MODCFG_MEM_FAILED;
			goto RET;
		}
	}
	else
	{
		dst->content = NULL;
	}

	goto RET;

ERR:
	modcfg_delete_member(dst);
	
RET:
	LOG("exit");
	return retValue;
}

int modcfg_clone_module(struct MODCFG_MODULE* dst, struct MODCFG_MODULE* src)
{
	int i;
	int iResult;
	int retValue = MODCFG_NO_ERROR;
	
	dst->modName = modcfg_str_clone(src->modName);
	dst->modType = modcfg_str_clone(src->modType);
	if(dst->modName == NULL || dst->modType == NULL)
	{
		retValue = MODCFG_MEM_FAILED;
		goto RET;
	}

	dst->memberList = (struct MODCFG_MEMBER*)malloc(sizeof(struct MODCFG_MEMBER) * src->memberCount);
	if(dst->memberList == NULL)
	{
		retValue = MODCFG_MEM_FAILED;
		goto RET;
	}
	else
	{
		dst->memberCount = src->memberCount;
		for(i = 0; i < src->memberCount; i++)
		{
			dst->memberList[i].idStr = NULL;
			dst->memberList[i].content = NULL;
		}
	}
	
	for(i = 0; i < src->memberCount; i++)
	{
		iResult = modcfg_clone_member(&dst->memberList[i], &src->memberList[i]);
		if(iResult != MODCFG_NO_ERROR)
		{
			retValue = iResult;
			goto ERR;
		}
	}
	
	goto RET;

ERR:
	modcfg_delete_module(dst);

RET:
	return retValue;
}

int modcfg_clone_struct(struct MODCFG_STRUCT* dst, struct MODCFG_STRUCT* src)
{
	int i;
	int iResult;
	int retValue = MODCFG_NO_ERROR;
	
	dst->modList = (struct MODCFG_MODULE*)malloc(sizeof(struct MODCFG_MODULE) * src->modCount);
	if(dst->modList == NULL)
	{
		retValue = MODCFG_MEM_FAILED;
		goto RET;
	}
	else
	{
		dst->modCount = src->modCount;
		for(i = 0; i < src->modCount; i++)
		{
			dst->modList[i].modName = NULL;
			dst->modList[i].modType = NULL;
			dst->modList[i].memberCount = 0;
			dst->modList[i].memberList = NULL;
		}
	}

	for(i = 0; i < src->modCount; i++)
	{
		iResult = modcfg_clone_module(&dst->modList[i], &src->modList[i]);
		if(iResult != MODCFG_NO_ERROR)
		{
			retValue = iResult;
			goto ERR;
		}
	}

	goto RET;

ERR:
	modcfg_delete_struct(dst);

RET:
	return retValue;
}

