#include <stdio.h>
#include <modcfg.h>

int main()
{
	int i;

	for(i = 2; i > -10; i--)
	{
		printf("With return value: %d, error message is: %s.\n", i, modcfg_get_error_msg(i));
	}

	return 0;
}
