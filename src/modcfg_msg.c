#include <stdlib.h>

#include "modcfg.h"
#include "modcfg_msg.h"

char* modcfg_error_msg[] = {
	"No error",
	"Memory allocation failed",
	"Open file failed",
	"There exists syntax error(s) in given config file",
	"Element not found in current config data",
	"Conflict content with same ID or name",
	"Doing operation on incompatible module",
	"Parsing failed",

	"Not a return value in ModConfig library"
};

const char* modcfg_get_error_msg(int retValue)
{
	const char* retPtr = NULL;

	if(retValue > 0)
	{
		retPtr = modcfg_error_msg[MODCFG_NO_ERROR_MSG];
	}
	else
	{
		switch(retValue)
		{
			case MODCFG_NO_ERROR:
				retPtr = modcfg_error_msg[MODCFG_NO_ERROR_MSG];
				break;

			case MODCFG_MEM_FAILED:
				retPtr = modcfg_error_msg[MODCFG_MEM_FAILED_MSG];
				break;

			case MODCFG_FILE_FAILED:
				retPtr = modcfg_error_msg[MODCFG_FILE_FAILED_MSG];
				break;

			case MODCFG_SYNTAX_ERROR:
				retPtr = modcfg_error_msg[MODCFG_SYNTAX_ERROR_MSG];
				break;

			case MODCFG_NOT_FOUND:
				retPtr = modcfg_error_msg[MODCFG_NOT_FOUND_MSG];
				break;

			case MODCFG_CONFLICT:
				retPtr = modcfg_error_msg[MODCFG_CONFLICT_MSG];
				break;

			case MODCFG_WRONG_TYPE:
				retPtr = modcfg_error_msg[MODCFG_WRONG_TYPE_MSG];
				break;

			case MODCFG_PARSE_FAILED:
				retPtr = modcfg_error_msg[MODCFG_PARSE_FAILED_MSG];
				break;

			default:
				retPtr = modcfg_error_msg[MODCFG_NOT_RETVAL_MSG];
		}
	}

	return retPtr;
}


