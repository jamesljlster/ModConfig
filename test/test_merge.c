#include <stdio.h>

#include <ModConfig.h>
#include <modcfg_private.h>

#define MERGE_SRC1_PATH	"./merge_src1.txt"
#define MERGE_SRC2_PATH "./merge_src2.txt"

int main()
{
	int iResult;
	int retValue;

	MODCFG mod1 = NULL;
	MODCFG mod2 = NULL;

	// Read config file
	iResult = modcfg_create(&mod1, MERGE_SRC1_PATH);
	if(iResult != MODCFG_NO_ERROR)
	{
		printf("Read %s failed!\n", MERGE_SRC1_PATH);
		retValue = -1;
		goto RET;
	}

	iResult = modcfg_create(&mod2, MERGE_SRC2_PATH);
	if(iResult != MODCFG_NO_ERROR)
	{
		printf("Read %s failed!\n", MERGE_SRC2_PATH);
		retValue = -1;
		goto RET;
	}

	// Print module
	printf("%s :\n", MERGE_SRC1_PATH);
	modcfg_print_detail(mod1);
	printf("%s :\n", MERGE_SRC2_PATH);
	modcfg_print_detail(mod2);

	// Test merge
	iResult = modcfg_merge(&mod1, mod2);
	if(iResult != MODCFG_NO_ERROR)
	{
		printf("Merge failed\n");
		retValue = -1;
		goto RET;
	}

	// Print merged module
	printf("Merged:\n");
	modcfg_print_detail(mod1);

RET:
	if(mod1 != NULL)
		modcfg_delete(mod1);

	if(mod2 != NULL)
		modcfg_delete(mod2);

	return 0;
}
