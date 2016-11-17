#include <stdlib.h>

#include "ModConfig.h"
#include "modcfg_private.h"

void modcfg_delete_member(struct MODCFG_MEMBER* target)
{
	if(target->idStr != NULL)
	{
		free(target->idStr);
		target->idStr = NULL;
	}

	if(target->content != NULL)
	{
		free(target->content);
		target->content = NULL;
	}
}

void modcfg_delete_module(struct MODCFG_MODULE* target)
{
	int i;

	if(target->modName != NULL)
	{
		free(target->modName);
		target->modName = NULL;
	}

	if(target->modType != NULL)
	{
		free(target->modType);
		target->modType = NULL;
	}

	if(target->memberList != NULL)
	{
		for(i = 0; i < target->memberCount; i++)
		{
			modcfg_delete_member(&target->memberList[i]);
		}
		free(target->memberList);
		target->memberList = NULL;
		target->memberCount = 0;
	}
}

void modcfg_delete_struct(struct MODCFG_STRUCT* target)
{
	int i;

	if(target->modList != NULL)
	{
		for(i = 0; i < target->modCount; i++)
		{
			modcfg_delete_module(&target->modList[i]);
		}
		free(target->modList);
		target->modList = NULL;
		target->modCount = 0;
	}
}

int modcfg_delete(MODCFG modPtr)
{
	struct MODCFG_STRUCT* modRef = (struct MODCFG_STRUCT*)modPtr;
	
	// Checking
	if(modPtr == NULL)
	{
		return MODCFG_NO_ERROR;
	}
	
	if(modRef != NULL)
	{
		modcfg_delete_struct(modRef);
		free(modRef);
	}

	return MODCFG_NO_ERROR;
}
