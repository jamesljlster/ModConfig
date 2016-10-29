#ifndef _MODCONFIG_FILEPROC_H_
#define	_MODCONFIG_FILEPROC_H_

#include <stdio.h>
#include "ModConfig_Private.h"

#define LF				0x0A
#define CR				0x0D
#define ASCII_MIN_SIG	0x21
#define ASCII_MAX_SIG	0x7E

enum READ_STATUS
{
	READ_INIT,
	READ_MODULE_TYPE,
	READ_MODULE_NAME,
	READ_BLOCK_START,
	READ_MEMBER_NAME,
	READ_MEMBER_ASSIGN,
	READ_MEMBER_TEXT,
	READ_MEMBER_END,
	READ_BLOCK_END
};

#ifdef __cplusplus
extern "C" {
#endif

int modcfg_read_module(struct MODCFG_MODULE* modModRef, FILE* fileRead);

#ifdef __cplusplus
}
#endif

#endif
