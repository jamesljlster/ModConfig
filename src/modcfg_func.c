#include <string.h>

#include "ModConfig.h"
#include "modcfg_private.h"

const char* modcfg_get_content(MODCFG mod, char* moduleName, char* memberName)
{
	struct MODCFG_STRUCT* modRef = (struct MODCFG_STRUCT*)mod;
	struct MODCFG_MODULE* modulePtr = NULL;
	struct MODCFG_MEMBER* memberPtr = NULL;

	// Find module
	modulePtr = modcfg_search_module(modRef, moduleName);
	if(modulePtr == NULL)
	{
		return NULL;
	}

	// Find member
	memberPtr = modcfg_search_member(modulePtr, memberName);
	if(memberPtr == NULL)
	{
		return NULL;
	}
	else
	{
		return (const char*)memberPtr->content;
	}
}

