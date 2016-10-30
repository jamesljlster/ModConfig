#ifndef _MODCFG_PRIVATE_H_ 
#define _MODCFG_PRIVATE_H_

struct MODCFG_MEMBER
{
	char* idStr;
	char* content;
};

struct MODCFG_MODULE
{
	char* moduleName;

	int memberCount;
	struct MODCFG_MEMBER* memberList;
};

struct MODCFG_STRUCT
{
	int modCount;
	struct MODCFG_MODULE* modList;
};

#endif
