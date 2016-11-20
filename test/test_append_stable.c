#include <stdio.h>

#include <ModConfig.h>
#include <modcfg_private.h>

#define MERGE_SRC1_PATH	"./merge_src1.txt"
#define MERGE_SRC2_PATH "./merge_src2.txt"

int main()
{
	int i;
	int retValue;

	char* modFile[2] = {
		MERGE_SRC1_PATH,
		MERGE_SRC2_PATH
	};

	MODCFG mod = NULL;

	while(1)
	{
		// Read config file
		for(i = 0; i < 2; i++)
		{
			modcfg_append(&mod, modFile[i]);
		}

		modcfg_delete(mod);
		mod = NULL;
	}

	return 0;
}
