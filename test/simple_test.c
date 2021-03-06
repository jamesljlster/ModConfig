#include <stdio.h>

#include <modcfg.h>

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

	iResult = modcfg_create(&mod, TEST_PATH);
	if(iResult != MODCFG_NO_ERROR)
	{
		printf("modcfg_create() failed with error: %d\n", iResult);
		return -1;
	}

	modcfg_print_detail(mod);

	printf("Get device from IR: %s\n", modcfg_get_content(mod, "IR", "device"));
	printf("Get item 1 form List2: %s\n", modcfg_get_item(mod, "List2", 1));

	modcfg_delete(mod);

	return 0;
}
