#include <stdio.h>

#include <ModConfig.h>

#define TEST_PATH	"./dev.txt"

int main()
{
	int i, j;
	int iResult;
	MODCFG mod = NULL;
	int strCount;
	char** strList;

	char* test = "Hello world = new world! \"Fool fool fool\" lololo /dev/tnt0 \"/dev/tnt1\"";

	iResult = modcfg_str_extract(&strList, &strCount, test);
	if(iResult != MODCFG_NO_ERROR)
	{
		printf("Extract string failed!\n");
		return -1;
	}
	else
	{
		for(iResult = 0; iResult < strCount; iResult++)
		{
			printf("%s\n", strList[iResult]);
		}
	}

	for(i = 0; i < strCount; i++)
	{
		free(strList[i]);
	}
	free(strList);

	iResult = modcfg_create(&mod, TEST_PATH);
	if(iResult != MODCFG_NO_ERROR)
	{
		printf("modcfg_create() failed with error: %d\n", iResult);
		return -1;
	}

	modcfg_delete(mod);

	return 0;
}
