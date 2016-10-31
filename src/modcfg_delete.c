#include <stdlib.h>

#include "ModConfig.h"
#include "modcfg_private.h"

int modcfg_delete(MODCFG modPtr)
{
	int i, j;
	struct MODCFG_STRUCT* modRef = (struct MODCFG_STRUCT*)modPtr;
	
	// Checking
	if(modPtr == NULL)
	{
		return MODCFG_NO_ERROR;
	}

	// Free module
	for(i = 0; i < modRef->modCount; i++)
	{
		// Free member
		for(j = 0; j < modRef->modList[i].memberCount; j++)
		{
			if(modRef->modList[i].memberList[j].idStr != NULL)
				free((void*)modRef->modList[i].memberList[j].idStr);
			
			if(modRef->modList[i].memberList[j].content != NULL)
				free((void*)modRef->modList[i].memberList[j].content);
		}

		// Free module name
		if(modRef->modList[i].modName != NULL)
			free((void*)modRef->modList[i].modName);
		
		if(modRef->modList[i].modType != NULL)
			free((void*)modRef->modList[i].modType);
	}

	// Free struct
	free((void*)modRef);

	return MODCFG_NO_ERROR;
}
