#ifndef __MODCFG_MSG_H__
#define __MODCFG_MSG_H__

enum MODCFG_RETVAL_MSG
{
	MODCFG_NO_ERROR_MSG,
	MODCFG_MEM_FAILED_MSG,
	MODCFG_FILE_FAILED_MSG,
	MODCFG_SYNTAX_ERROR_MSG,
	MODCFG_NOT_FOUND_MSG,
	MODCFG_CONFLICT_MSG,
	MODCFG_WRONG_TYPE_MSG,

	MODCFG_NOT_RETVAL_MSG
};

extern char* modcfg_error_msg[];

#endif
