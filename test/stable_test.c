#include <stdio.h>

#include <modcfg.h>

#define TEST_PATH	"./dev.txt"

int main()
{
	int iResult;
	MODCFG mod = NULL;
	
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
