#include <string.h>

#include "ModConfig.h"
#include "modcfg_private.h"

const char* modcfg_get_content(MODCFG mod, char* moduleName, char* memberName)
{
	int i;
	int iResult;
	int cmpLen;
	int srcLen, argLen;
	int modIndex, memberIndex;
	struct MODCFG_STRUCT* modRef = (struct MODCFG_STRUCT*)mod;

	// Find module index
	modIndex = -1;
	for(i = 0; i < modRef->modCount; i++)
	{
		srcLen = strlen(modRef->modList[i].modName);
		argLen = strlen(moduleName);
		
		if(srcLen != argLen)
			continue;

		iResult = strncmp(modRef->modList[i].modName, moduleName, srcLen);
		if(iResult == 0)
			modIndex = i;
	}

	// Checking
	if(modIndex == -1)
		return NULL;

	// Find member index
	memberIndex = -1;
	for(i = 0; i < modRef->modList[modIndex].memberCount; i++)
	{
		srcLen = strlen(memberName);
		argLen = strlen(modRef->modList[modIndex].memberList[i].idStr);
		
		if(srcLen != argLen)
			continue;

		iResult = strncmp(modRef->modList[modIndex].memberList[i].idStr, memberName, srcLen);
		if(iResult == 0)
			memberIndex = i;
	}

	// Checking
	if(memberIndex == -1)
		return NULL;
	
	return (const char*)modRef->modList[modIndex].memberList[memberIndex].content;
}

