#include <stdio.h>

#include <modcfg.h>

#define TEST_PATH	"./num.txt"

int main()
{
	int tmpValue;
	double tmpdValue;
	int iResult;
	MODCFG mod = NULL;

	iResult = modcfg_create(&mod, TEST_PATH);
	if(iResult != MODCFG_NO_ERROR)
	{
		printf("modcfg_create() failed with error: %d\n", iResult);
		return -1;
	}

	modcfg_print_detail(mod);

	// get int
	iResult = modcfg_parse_content_int(&tmpValue, mod, "num", "int", 10);
	if(iResult < 0)
	{
		printf("modcfg_parse_content_int() failed with error: %s\n", modcfg_get_error_msg(iResult));
		return -1;
	}
	else
	{
		printf("parse int: %d\n", tmpValue);
	}
	
	// get hex_int
	iResult = modcfg_parse_content_int(&tmpValue, mod, "num", "hex_int", 16);
	if(iResult < 0)
	{
		printf("modcfg_parse_content_int() failed with error: %s\n", modcfg_get_error_msg(iResult));
		return -1;
	}
	else
	{
		printf("parse hex_int: %d\n", tmpValue);
	}
	

	// get o_int
	iResult = modcfg_parse_content_int(&tmpValue, mod, "num", "o_int", 8);
	if(iResult < 0)
	{
		printf("modcfg_parse_content_int() failed with error: %s\n", modcfg_get_error_msg(iResult));
		return -1;
	}
	else
	{
		printf("parse o_int: %d\n", tmpValue);
	}

	// get realnum
	iResult = modcfg_parse_content_double(&tmpdValue, mod, "num", "realnum");
	if(iResult < 0)
	{
		printf("modcfg_parse_content_double() failed with error: %s\n", modcfg_get_error_msg(iResult));
		return -1;
	}
	else
	{
		printf("parse realnum: %lf\n", tmpdValue);
	}
	
	modcfg_delete(mod);

	return 0;
}
