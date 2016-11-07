#ifndef _MODCFG_PTR_STACK_H_
#define _MODCFG_PTR_STACK_H_

struct MODCFG_PSTACK	//	Pointer stack for ModConfig
{
	void** stack;
	int stackSize;
	int top;
};

#ifdef __cplusplus
extern "C" {
#endif

int modcfg_pstack_create(struct MODCFG_PSTACK* pstackPtr);

int modcfg_pstack_push(struct MODCFG_PSTACK* pstack, void* ptr);
void* modcfg_pstack_pop(struct MODCFG_PSTACK* pstack);

int modcfg_pstack_delete(struct MODCFG_PSTACK* pstack);

#ifdef __cplusplus
}
#endif

#endif
