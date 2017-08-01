#include <stdlib.h>

#include "modcfg.h"
#include "modcfg_private.h"

#include "debug.h"

int modcfg_parse_content_int(int* resultPtr, MODCFG mod, char* moduleName, char* memberName, int numBase)
{
	int retValue = MODCFG_NO_ERROR;
	int tmpConvert;
	const char* member;
	char* tmpPtr = NULL;

	// Get member content
	member = modcfg_get_content(mod, moduleName, memberName);
	if(member == NULL)
	{
		LOG("%s not found in %s setting", memberName, moduleName);
		retValue = MODCFG_NOT_FOUND;
		goto RET;
	}

	tmpConvert = strtol(member, &tmpPtr, numBase);
	if(tmpPtr == member)
	{
		LOG("Failed to convert %s to integer", member);
		retValue = MODCFG_PARSE_FAILED;
		goto RET;
	}
	
	// Assing value
	*resultPtr = tmpConvert;

RET:
	return retValue;
}

int modcfg_parse_content_double(double* resultPtr, MODCFG mod, char* moduleName, char* memberName)
{
	int retValue = MODCFG_NO_ERROR;
	double tmpConvert;
	const char* member;
	char* tmpPtr = NULL;

	// Get member content
	member = modcfg_get_content(mod, moduleName, memberName);
	if(member == NULL)
	{
		LOG("%s not found in %s setting", memberName, moduleName);
		retValue = MODCFG_NOT_FOUND;
		goto RET;
	}

	tmpConvert = strtod(member, &tmpPtr);
	if(tmpPtr == member)
	{
		LOG("Failed to convert %s to double", member);
		retValue = MODCFG_PARSE_FAILED;
		goto RET;
	}
	
	// Assing value
	*resultPtr = tmpConvert;

RET:
	return retValue;
}

