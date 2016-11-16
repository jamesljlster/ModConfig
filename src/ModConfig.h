#ifndef _MODCONFIG_H_
#define _MODCONFIG_H_

enum MODCFG_RETURN_VALUE
{
	MODCFG_NO_ERROR		= 0,
	MODCFG_MEM_FAILED	= -1,
	MODCFG_FILE_FAILED	= -2,
	MODCFG_SYNTAX_ERROR	= -3,
	MODCFG_NOT_FOUND	= -4,
	MODCFG_CONFLICT		= -5
};

typedef void* MODCFG;

#ifdef __cplusplus
extern "C" {
#endif

int modcfg_create(MODCFG* modPtr, char* filePath);
int modcfg_append(MODCFG* modPtr, char* filePath);
int modcfg_delete(MODCFG mod);

int modcfg_clone(MODCFG* dstModPtr, MODCFG srcMod);
int modcfg_merge(MODCFG* dstModPtr, MODCFG srcMod);

const char* modcfg_get_content(MODCFG mod, char* moduleName, char* memberName);
void modcfg_print_module(MODCFG mod);

#ifdef __cplusplus
}
#endif

#endif
