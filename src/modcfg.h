/**
 *	@author		Zheng-Ling Lai <jamesljlster@gmail.com>
 *	@copyright	Copyright 2016-2017 Zheng-Ling Lai. All Rights Reserved.
**/

#ifndef _MODCONFIG_H_
#define _MODCONFIG_H_

/** Definition of return values from ModConfig functions. */
enum MODCFG_RETURN_VALUE
{
	MODCFG_NO_ERROR		= 0,	/*!< No error. */
	MODCFG_MEM_FAILED	= -1,	/*!< Memory allocation failed. */
	MODCFG_FILE_FAILED	= -2,	/*!< Open file failed. */
	MODCFG_SYNTAX_ERROR	= -3,	/*!< There exists syntax error(s) in given config file. */
	MODCFG_NOT_FOUND	= -4,	/*!< Element not found in current config data. */
	MODCFG_CONFLICT		= -5,	/*!< Conflict content with same ID or name. */
	MODCFG_WRONG_TYPE	= -6,	/*!< Doing operation on incompatible module. */
	MODCFG_PARSE_FAILED	= -7	/*!< Parsing failed. */
};

typedef void* MODCFG;

#ifdef __cplusplus
extern "C" {
#endif

int modcfg_create(MODCFG* modPtr, const char* filePath);
/**
 *	@fn		int modcfg_create(MODCFG* modPtr, const char* filePath);
 *	@brief	Create a config data with given config file path.
 *	@param	modPtr:		Pointer of config data.
 *	@param	filePath:	Path to config file.
 *	@return	Return value could be described by #MODCFG_RETURN_VALUE.
 */

int modcfg_append(MODCFG* modPtr, const char* filePath);
/**
 *	@fn		int modcfg_append(MODCFG* modPtr, const char* filePath);
 *	@brief	Append a config data with given config file path.
 *	@param	modPtr:		Pointer of config data.
 *	@param	filePath;	Path to config file.
 *	@return	Return value could be described by #MODCFG_RETURN_VALUE.
 */

int modcfg_delete(MODCFG mod);
/**
 *	@fn		int modcfg_delete(MODCFG mod);
 *	@brief	Delete a config data.
 *	@param	mod:	Config data.
 *	@return	Return value could be described by #MODCFG_RETURN_VALUE.
 */

int modcfg_clone(MODCFG* dstModPtr, MODCFG srcMod);
/**
 *	@fn		int modcfg_clone(MODCFG* dstModPtr, MODCFG srcMod);
 *	@brief	Clone a config data.
 *	@param	dstModPtr:	Pointer of destination config data.
 *	@param	srcMod:		Source config data.
 *	@return	Return value could be described by #MODCFG_RETURN_VALUE.
 */

int modcfg_merge(MODCFG* dstModPtr, MODCFG srcMod);
/**
 *	@fn		int modcfg_merge(MODCFG* dstModPtr, MODCFG srcMod);
 *	@brief	Merge config data.
 *	@param	dstModPtr:	Pointer of destination config data.
 *	@param	srcMod:		Source config data.
 *	@return	Return value could be described by #MODCFG_RETURN_VALUE.
 */

const char* modcfg_get_content(MODCFG mod, const char* moduleName, const char* memberName);
/**
 *	@fn		const char* modcfg_get_content(MODCFG mod, const char* moduleName, const char* memberName);
 *	@brief	Get content with given module name and member name.
 *	@param	mod:		Config data.
 *	@param	moduleName:	Module name.
 *	@param	memberName:	Member name.
 *	@return	If succeed, the function would return the pointer of content, else return NULL.
 */

int modcfg_parse_content_int(int* resultPtr, MODCFG mod, const char* moduleName, const char* memberName, int numBase);
/**
 *	@fn		int modcfg_parse_content_int(MODCFG mod, const char* moduleName, const char* memberName, int numBase);
 *	@brief	Get and parse content as integer with given module name and member name.
 *	@param	mod:		Config data.
 *	@param	resultPtr:	Result variable pointer.
 *	@param	moduleName:	Module name.
 *	@param	memberName:	Member name.
 *	@param	numBase:	Base of integer.
 *	@return	Return value could be described by #MODCFG_RETURN_VALUE.
 */

int modcfg_parse_content_double(double* resultPtr, MODCFG mod, const char* moduleName, const char* memberName);
/**
 *	@fn		int modcfg_parse_content_double(MODCFG mod, double* resultPtr, const char* moduleName, const char* memberName);
 *	@brief	Get and parse content as real number with given module name and member name.
 *	@param	mod:		Config data.
 *	@param	resultPtr:	Result variable pointer.
 *	@param	moduleName:	Module name.
 *	@param	memberName:	Member name.
 *	@return	Return value could be described by #MODCFG_RETURN_VALUE.
 */

const char* modcfg_get_item(MODCFG mod, const char* listName, int index);
/**
 *	@fn 	const char* modcfg_get_item(MODCFG mod, const char* listName, int index);
 *	@brief	Get item with given list name and index.
 *	@param	mod:		Config data.
 *	@param	listName:	List name.
 *	@param	index:		Item index.
 *	@retuen	if succeed, the function would return the pointer of content, else return NULL.
 */

int modcfg_get_list_length(MODCFG mod, const char* listName);
/**
 *	@fn		int modcfg_get_list_length(MODCFG mod, const char* listName);
 *	@brief	Get list length (item amount) with given list name.
 *	@param	mod:		Config data.
 *	@param	listName:	List name.
 *	@return	If succeed, the function would return the length of the list, else return a number small then zero.
 */

void modcfg_print_detail(MODCFG mod);
/**
 *	@fn		void modcfg_print_detail(MODCFG mod);
 *	@brief	Print details of config file.
 *	@param	mod:	Config data.
 */

const char* modcfg_get_error_msg(int retValue);
/**
 *	@fn		const char* modcfg_get_error_msg(int retValue);
 *	@brief	Get error message with given return value.
 *	@param	retValue:	Target return value that trying to parsing.
 *	@return Constant string pointer that contains parsing message.
 */

#ifdef __cplusplus
}
#endif

#endif
