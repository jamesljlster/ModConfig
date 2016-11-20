#include <stdlib.h>
#include <string.h>

#include "ModConfig.h"

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
