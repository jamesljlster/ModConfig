#include <stdio.h>

#include <ModConfig.h>
#include <modcfg_private.h>

int main()
{
	char* strsrc = "Hello World! Oh Oh Oh";
	char* strdst = NULL;

	printf("Test string clone\n");
	strdst = modcfg_str_clone(strsrc);
	printf("Src:\t%s\n", strsrc);
	printf("Dst:\t%s\n", strdst);

	return 0;
}

