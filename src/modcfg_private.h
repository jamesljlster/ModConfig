#ifndef _MODCFG_PRIVATE_H_ 
#define _MODCFG_PRIVATE_H_

struct MODCFG_MEMBER
{
	char* idStr;
	char* content;
};

struct MODCFG_MODULE
{
	char* modName;
	char* modType;

	int memberCount;
	struct MODCFG_MEMBER* memberList;
};

struct MODCFG_STRUCT
{
	int modCount;
	struct MODCFG_MODULE* modList;
};

#ifdef __cplusplus
extern "C" {
#endif

char* modcfg_str_clone(char* src);
int modcfg_clone_member(struct MODCFG_MEMBER* dst, struct MODCFG_MEMBER* src);
int modcfg_clone_module(struct MODCFG_MODULE* dst, struct MODCFG_MODULE* src);

#ifdef __cplusplus
}
#endif

#endif
