#include <stdio.h>

#include <ModConfig.h>

#define TEST_PATH	"./dev.txt"

int main()
{
	int i, j;
	int iResult;
	MODCFG mod = NULL;
	MODCFG clone = NULL;

	iResult = modcfg_create(&mod, TEST_PATH);
	if(iResult != MODCFG_NO_ERROR)
	{
		printf("modcfg_create() failed with error: %d\n", iResult);
		return -1;
	}

	iResult = modcfg_clone(&clone, mod);
	if(iResult != MODCFG_NO_ERROR)
	{
		printf("modcfg_clone() failed with error: %d\n", iResult);
		return -1;
	}
	
	printf("Src Mod:\n");
	modcfg_print_detail(mod);
	printf("Clone Mod:\n");
	modcfg_print_detail(clone);

	printf("Get device from IR: %s\n", modcfg_get_content(clone, "IR", "device"));
	
	modcfg_delete(mod);
	modcfg_delete(clone);

	return 0;
}
