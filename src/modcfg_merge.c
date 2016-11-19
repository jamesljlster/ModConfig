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

int modcfg_merge_module(struct MODCFG_MODULE* dst, struct MODCFG_MODULE* src)
{
	int i;
	int iResult;
	int retValue;
	
	int cmpLen;
	int srcLen, dstLen;

	struct MODCFG_MEMBER* ptr = NULL;
	void* allocTmp = NULL;

	for(i = 0; i < src->memberCount; i++)
	{
		// Try to find same member
		ptr = modcfg_search_member(dst, src->memberList[i].idStr);
		if(ptr == NULL)
		{
			// Insert new member
			// Memory allocation: New space for new member
			allocTmp = realloc(dst->memberList, sizeof(struct MODCFG_MEMBER) * (dst->memberCount + 1));
			if(allocTmp == NULL)
			{
				retValue = MODCFG_MEM_FAILED;
				goto RET;
			}
			else
			{
				dst->memberCount++;
				dst->memberList = (struct MODCFG_MEMBER*)allocTmp;
				allocTmp = NULL;

				dst->memberList[dst->memberCount - 1].idStr = NULL;
				dst->memberList[dst->memberCount - 1].content = NULL;
			}

			// Clone new member to new space
			iResult = modcfg_clone_member(&dst->memberList[dst->memberCount - 1], &src->memberList[i]);
			if(iResult != MODCFG_NO_ERROR)
			{
				retValue = iResult;
				goto RET;
			}
		}
		else
		{
			// Check if destination string is empty
			if(ptr->content == NULL)
			{
				// Copy content
				ptr->content = modcfg_str_clone(src->memberList[i].content);
				if(ptr->content == NULL)
				{
					retValue = MODCFG_MEM_FAILED;
					goto RET;
				}
			}
			else
			{
				// Checking if content string is same
				dstLen = strlen(ptr->content);
				srcLen = strlen(src->memberList[i].content);
				if(dstLen != srcLen)
				{
					retValue = MODCFG_CONFLICT;
					goto RET;
				}
				
				iResult = strncmp(ptr->content, src->memberList[i].content, cmpLen);
				if(iResult != 0)
				{
					retValue = MODCFG_CONFLICT;
					goto RET;
				}
			}
		}	
	}

RET:
	if(allocTmp != NULL)
		free(allocTmp);

	return retValue;
}

int modcfg_merge_struct(struct MODCFG_STRUCT* dst, struct MODCFG_STRUCT* src)
{
	int i;
	int iResult;
	int retValue;
	
	int cmpLen;
	int srcLen, dstLen;

	struct MODCFG_MODULE* ptr = NULL;
	void* allocTmp = NULL;

	for(i = 0; i < src->modCount; i++)
	{
		// Try to find same struct
		ptr = modcfg_search_module(dst, src->modList[i].modName);
		if(ptr == NULL)
		{
			// Insert new module
			// Memory allocation: New space for new member
			allocTmp = realloc(dst->modList, sizeof(struct MODCFG_MODULE) * (dst->modCount + 1));
			if(allocTmp == NULL)
			{
				retValue = MODCFG_MEM_FAILED;
				goto RET;
			}
			else
			{
				dst->modCount++;
				dst->modList = (struct MODCFG_MODULE*)allocTmp;
				allocTmp = NULL;

				dst->modList[dst->modCount - 1].modName = NULL;
				dst->modList[dst->modCount - 1].modType = NULL;
				dst->modList[dst->modCount - 1].memberCount = NULL;
				dst->modList[dst->modCount - 1].memberList = NULL;
			}

			// Clone new member to new space
			iResult = modcfg_clone_module(&dst->modList[dst->modCount - 1], &src->modList[i]);
			if(iResult != MODCFG_NO_ERROR)
			{
				retValue = iResult;
				goto RET;
			}
		}
		else
		{
			// Check if module type string is empty
			if(ptr->modType == NULL)
			{
				// Copy content
				ptr->modType = modcfg_str_clone(src->modList[i].modType);
				if(ptr->modType == NULL)
				{
					retValue = MODCFG_MEM_FAILED;
					goto RET;
				}
			}
			else
			{
				// Checking if type string is same
				dstLen = strlen(ptr->modType);
				srcLen = strlen(src->modList[i].modType);
				if(dstLen != srcLen)
				{
					retValue = MODCFG_CONFLICT;
					goto RET;
				}
				
				iResult = strncmp(ptr->modType, src->modList[i].modType, cmpLen);
				if(iResult != 0)
				{
					retValue = MODCFG_CONFLICT;
					goto RET;
				}
			}

			// Merge module
			iResult = modcfg_merge_module(ptr, &src->modList[i]);
			if(iResult != MODCFG_NO_ERROR);
			{
				retValue = iResult;
				goto RET;
			}
		}	
	}

RET:
	if(allocTmp != NULL)
		free(allocTmp);

	return retValue;
}

