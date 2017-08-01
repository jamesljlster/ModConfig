#include <stdio.h>

#include <modcfg.h>

int main(int argc, char* argv[])
{
	int i;
	int iResult;
	MODCFG mod = NULL;

	for(i = 1; i < argc; i++)
	{
		iResult = modcfg_create(&mod, argv[i]);
		if(iResult != MODCFG_NO_ERROR)
		{
			printf("modcfg_create() failed with error: %d\n", iResult);
			return -1;
		}

		printf("%s:\n", argv[i]);
		modcfg_print_detail(mod);

		modcfg_delete(mod);
	}

	return 0;
}
