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

//	char* test = "Hello=\"Fool fool fool\" \"/dev/tnt1\"";
//
//	iResult = modcfg_str_extract(&strList, &strCount, test);
//	if(iResult != MODCFG_NO_ERROR)
//	{
//		printf("Extract string failed!\n");
//		return -1;
//	}
//	else
//	{
//		printf("strCount = %d\n", strCount);
//		for(iResult = 0; iResult < strCount; iResult++)
//		{
//			printf("%s\n", strList[iResult]);
//		}
//	}
//
//	for(i = 0; i < strCount; i++)
//	{
//		free(strList[i]);
//	}
//	free(strList);
	
	while(1)
	{
		iResult = modcfg_create(&mod, TEST_PATH);
		if(iResult != MODCFG_NO_ERROR)
		{
			printf("modcfg_create() failed with error: %d\n", iResult);
			return -1;
		}
		
		modcfg_delete(mod);
	}

	return 0;
}
