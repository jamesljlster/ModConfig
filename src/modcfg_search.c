#include <string.h>

#include "modcfg.h"
#include "modcfg_private.h"

struct MODCFG_MEMBER* modcfg_search_member(struct MODCFG_MODULE* target, char* name)
{
	int i;
	int iResult;
	int srcLen, cmpLen;
	struct MODCFG_MEMBER* ptr = NULL;

	cmpLen = strlen(name);
	for(i = 0; i < target->memberCount; i++)
	{
		srcLen = strlen(target->memberList[i].idStr);
		if(srcLen != cmpLen)
			continue;

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
	int srcLen, cmpLen;
	struct MODCFG_MODULE* ptr = NULL;

	cmpLen = strlen(name);
	for(i = 0; i < target->modCount; i++)
	{
		srcLen = strlen(target->modList[i].modName);
		if(srcLen != cmpLen)
			continue;

		iResult = strncmp(target->modList[i].modName, name, cmpLen);
		if(iResult == 0)
		{
			ptr = &target->modList[i];
			break;
		}
	}

	return ptr;
}

