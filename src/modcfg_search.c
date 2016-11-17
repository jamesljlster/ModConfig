#include <string.h>

#include "ModConfig.h"
#include "modcfg_private.h"

struct MODCFG_MEMBER* modcfg_search_member(struct MODCFG_MODULE* target, char* name)
{
	int i;
	int iResult;
	int cmpLen;
	int srcLen, argLen;
	struct MODCFG_MEMBER* ptr = NULL;

	argLen = strlen(name);
	for(i = 0; i < target->memberCount; i++)
	{
		srcLen = strlen(target->memberList[i].idStr);
		if(srcLen != argLen)
			continue;

		cmpLen = (argLen <= srcLen) ? argLen : srcLen;
		iResult = strncmp(target->memberList[i].idStr, name, cmpLen);
		if(iResult == 0)
		{
			ptr = &target->memberList[i];
			break;
		}
	}

	return ptr;
}

struct MODCFG_MODULE* modcfg_search_module(struct MODCFG_STRUCT* target, char* name)
{
	int i;
	int iResult;
	int cmpLen;
	int srcLen, argLen;
	struct MODCFG_MODULE* ptr = NULL;

	argLen = strlen(name);
	for(i = 0; i < target->modCount; i++)
	{
		srcLen = strlen(target->modList[i].modName);
		if(srcLen != argLen)
			continue;

		cmpLen = (argLen <= srcLen) ? argLen : srcLen;
		iResult = strncmp(target->modList[i].modName, name, cmpLen);
		if(iResult == 0)
		{
			ptr = &target->modList[i];
			break;
		}
	}

	return ptr;
}

