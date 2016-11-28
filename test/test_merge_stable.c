#include <stdio.h>

#include <modcfg.h>
#include <modcfg_private.h>

#define MERGE_SRC1_PATH	"./merge_src1.txt"
#define MERGE_SRC2_PATH "./merge_src2.txt"

int main()
{
	MODCFG mod1 = NULL;
	MODCFG mod2 = NULL;
	
	while(1)
	{
		// Read config file
		modcfg_create(&mod1, MERGE_SRC1_PATH);
		modcfg_create(&mod2, MERGE_SRC2_PATH);

		// Test merge
		modcfg_merge(&mod1, mod2);

		// Print merged module
		modcfg_delete(mod1);
		modcfg_delete(mod2);
	}

	return 0;
}
