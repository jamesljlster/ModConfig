#ifndef _MODCFG_FILE_PROC_H_ 
#define	_MODCFG_FILE_PROC_H_

#include <stdio.h>
#include "modcfg_private.h"

#define LF				0x0A
#define CR				0x0D
#define ASCII_MIN_SIG	0x20
#define ASCII_MAX_SIG	0x7E

enum READ_CHAR_TYPE
{
	READ_ALL,		// Read all type character
	READ_SIG		// Read signaficant character
};

struct STR_TREE
{
	int strCount;
	char** strList;

	int childCount;
	struct STR_TREE* child;

	char* header;
};

#ifdef __cplusplus
extern "C" {
#endif

int modcfg_create_str_tree(struct STR_TREE** strTreeRef, char* filePath);
void modcfg_delete_str_tree(struct STR_TREE* strTree);
void print_str_tree(struct STR_TREE* strTree);
char modcfg_get_char(FILE* fileRead, int readAction);
int modcfg_str_extract(char*** strListPtr, int* strCountPtr, char* src);

#ifdef __cplusplus
}
#endif

#endif
