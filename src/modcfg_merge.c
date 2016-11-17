#include <stdlib.h>
#include <string.h>

#include "ModConfig.h"
#include "modcfg_private.h" 

int modcfg_merge(MODCFG* dstModPtr, MODCFG srcMod)
{
	int i, j;
	int iResult;
	int retValue = MODCFG_NO_ERROR;
	
	char* srcStr;
	char* cmpStr;
	void* allocTmp = NULL;

	MODCFG tmpMod;

	// Clone module
	iResult = modcfg_clone(&tmpMod, *dstModPtr);
	if(iResult != MODCFG_NO_ERROR)
	{
		retValue = iResult;
		goto RET;
	}

ERR:

RET:
	if(allocTmp != NULL)
		free(allocTmp);

	return retValue;
}

