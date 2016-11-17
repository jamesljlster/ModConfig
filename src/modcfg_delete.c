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
	int i, j;
	struct MODCFG_STRUCT* modRef = (struct MODCFG_STRUCT*)modPtr;
	
	// Checking
	if(modPtr == NULL)
	{
		return MODCFG_NO_ERROR;
	}

	modcfg_delete_struct(modRef);

//	// Free module
//	for(i = 0; i < modRef->modCount; i++)
//	{
//		// Free member
//		for(j = 0; j < modRef->modList[i].memberCount; j++)
//		{
//			if(modRef->modList[i].memberList[j].idStr != NULL)
//				free((void*)modRef->modList[i].memberList[j].idStr);
//			
//			if(modRef->modList[i].memberList[j].content != NULL)
//				free((void*)modRef->modList[i].memberList[j].content);
//		}
//		if(modRef->modList[i].memberList != NULL)
//			free(modRef->modList[i].memberList);
//
//		// Free module name
//		if(modRef->modList[i].modName != NULL)
//			free((void*)modRef->modList[i].modName);
//		
//		if(modRef->modList[i].modType != NULL)
//			free((void*)modRef->modList[i].modType);
//	}
//	if(modRef->modList != NULL)
//		free(modRef->modList);
//
//	// Free struct
//	free((void*)modRef);

	return MODCFG_NO_ERROR;
}
