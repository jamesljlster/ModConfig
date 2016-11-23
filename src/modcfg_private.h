#ifndef _MODCFG_PRIVATE_H_ 
#define _MODCFG_PRIVATE_H_

enum MODCFG_TYPE
{
	MODCFG_TYPE_MODULE,
	MODCFG_TYPE_LIST
};

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

struct MODCFG_MEMBER* modcfg_search_member(struct MODCFG_MODULE* target, char* name);
struct MODCFG_MODULE* modcfg_search_module(struct MODCFG_STRUCT* target, char* name);

char* modcfg_str_clone(char* src);

int modcfg_append_member(struct MODCFG_MODULE* dst, struct MODCFG_MEMBER* src);
int modcfg_append_module(struct MODCFG_STRUCT* dst, struct MODCFG_MODULE* src);

int modcfg_merge_module(struct MODCFG_MODULE* dst, struct MODCFG_MODULE* src);
int modcfg_merge_struct(struct MODCFG_STRUCT* dst, struct MODCFG_STRUCT* src);

int modcfg_clone_member(struct MODCFG_MEMBER* dst, struct MODCFG_MEMBER* src);
int modcfg_clone_module(struct MODCFG_MODULE* dst, struct MODCFG_MODULE* src);
int modcfg_clone_struct(struct MODCFG_STRUCT* dst, struct MODCFG_STRUCT* src);

void modcfg_delete_member(struct MODCFG_MEMBER* target);
void modcfg_delete_module(struct MODCFG_MODULE* target);
void modcfg_delete_struct(struct MODCFG_STRUCT* target);

void modcfg_print_member(struct MODCFG_MEMBER* src);
void modcfg_print_module(struct MODCFG_MODULE* src);
void modcfg_print_struct(struct MODCFG_STRUCT* src);

#ifdef __cplusplus
}
#endif

#endif
