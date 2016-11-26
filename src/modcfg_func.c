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

	// Check module type
	if(modcfg_get_type_id(modulePtr->modType) != MODCFG_TYPE_MODULE)
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

const char* modcfg_get_item(MODCFG mod, char* listName, int index)
{
	struct MODCFG_STRUCT* modRef = (struct MODCFG_STRUCT*)mod;
	struct MODCFG_MODULE* modulePtr = NULL;

	// Find module
	modulePtr = modcfg_search_module(modRef, listName);
	if(modulePtr == NULL)
	{
		return NULL;
	}

	// Check module type
	if(modcfg_get_type_id(modulePtr->modType) != MODCFG_TYPE_LIST)
	{
		return NULL;
	}

	if(index > modulePtr->memberCount - 1)
	{
		return NULL;
	}
	else
	{
		return (const char*)modulePtr->memberList[index].idStr;
	}
}

int modcfg_get_list_length(MODCFG mod, char* listName)
{
	struct MODCFG_STRUCT* modRef = (struct MODCFG_STRUCT*)mod;
	struct MODCFG_MODULE* modulePtr = NULL;

	// Find module
	modulePtr = modcfg_search_module(modRef, listName);
	if(modulePtr == NULL)
	{
		return MODCFG_NOT_FOUND;
	}
	
	// Check module type
	if(modcfg_get_type_id(modulePtr->modType) != MODCFG_TYPE_LIST)
	{
		return MODCFG_WRONG_TYPE;
	}

	return modulePtr->memberCount;
}

