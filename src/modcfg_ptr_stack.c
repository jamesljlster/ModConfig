#include <stdlib.h>

#include "modcfg.h"
#include "modcfg_ptr_stack.h"

int modcfg_pstack_create(struct MODCFG_PSTACK* pstack)
{
	pstack->stack = NULL;
	pstack->stackSize = 0;
	pstack->top = -1;
	
	return MODCFG_NO_ERROR;
}

int modcfg_pstack_push(struct MODCFG_PSTACK* pstack, void* ptr)
{
	int retValue = MODCFG_NO_ERROR;
	void* allocTmp = NULL;
	
	if(pstack->top == pstack->stackSize - 1)
	{
		allocTmp = realloc((void*)pstack->stack, sizeof(void*) * (pstack->stackSize + 1));
		if(allocTmp == NULL)
		{
			retValue = MODCFG_MEM_FAILED;
			goto RET;
		}
		else
		{
			pstack->stackSize++;
			pstack->stack = (void**)allocTmp;
			allocTmp = NULL;
		}
	}
	
	pstack->top++;
	pstack->stack[pstack->top] = ptr;

RET:
	if(allocTmp != NULL)
		free(allocTmp);

	return retValue;
}

void* modcfg_pstack_pop(struct MODCFG_PSTACK* pstack)
{
	void* retPtr;

	if(pstack->top < 0)
	{
		retPtr = NULL;
	}
	else
	{
		retPtr = pstack->stack[pstack->top];
		pstack->top--;
	}

	return retPtr;
}

int modcfg_pstack_delete(struct MODCFG_PSTACK* pstack)
{
	if(pstack->stack != NULL)
	{
		free(pstack->stack);
		pstack->stack = NULL;
	}

	pstack->top = -1;
	pstack->stackSize = 0;

	return MODCFG_NO_ERROR;
}


