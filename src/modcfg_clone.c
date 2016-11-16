#include <stdlib.h>
#include <string.h>

#include "ModConfig.h"
#include "modcfg_private.h" 

char* modcfg_str_clone(char* src);
int modcfg_clone_member(struct MODCFG_MEMBER* dst, struct MODCFG_MEMBER* src);
int modcfg_clone_module(struct MODCFG_MODULE* dst, struct MODCFG_MODULE* src);

int modcfg_clone(MODCFG* dstModPtr, MODCFG srcMod)
{
	int i, j;
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
		modStruct->modCount = modSrcRef->modCount;
		modStruct->modList = (struct MODCFG_MODULE*)malloc(sizeof(struct MODCFG_MODULE) * modSrcRef->modCount);
	}

	// Assign value
	*dstModPtr = (MODCFG)modStruct;
	
	goto RET;

ERR:
	if(modStruct != NULL)
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

	dst->idStr = modcfg_str_clone(src->idStr);
	dst->content = modcfg_str_clone(src->content);
	
	if(dst->idStr == NULL || dst->content == NULL)
	{
		retValue = MODCFG_MEM_FAILED;
		goto ERR;
	}
	else
	{
		goto RET;
	}

ERR:
	if(dst->idStr != NULL)
		free(dst->idStr);

	if(dst->content != NULL)
		free(dst->content);

RET:
	return retValue;
}

int modcfg_clone_module(struct MODCFG_MODULE* dst, struct MODCFG_MODULE* src);


