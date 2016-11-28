#include <stdio.h>

#include <modcfg.h>
#include <modcfg_private.h>

#define MERGE_SRC1_PATH	"./merge_src1.txt"
#define MERGE_SRC2_PATH "./merge_src2.txt"

int main()
{
	int i;
	int iResult;
	int retValue;

	char* modFile[2] = {
		MERGE_SRC1_PATH,
		MERGE_SRC2_PATH
	};

	MODCFG mod = NULL;

	// Read config file
	for(i = 0; i < 2; i++)
	{
		iResult = modcfg_append(&mod, modFile[i]);
		if(iResult != MODCFG_NO_ERROR)
		{
			printf("Read %s failed!\n", modFile[i]);
			retValue = -1;
			goto RET;
		}
	}

	// Print module
	printf("Append %s and %s\n", modFile[0], modFile[1]);
	modcfg_print_detail(mod);

RET:
	if(mod != NULL)
		modcfg_delete(mod);

	return 0;
}
