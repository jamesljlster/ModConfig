#include <stdio.h>

#include "ModConfig.h"
#include "modcfg_private.h"

void modcfg_print_module(MODCFG mod)
{
	int i, j;
	struct MODCFG_STRUCT* modRef = (struct MODCFG_STRUCT*)mod;

	for(i = 0; i < modRef->modCount; i++)
	{
		printf("Type: %s, Name: %s\n", modRef->modList[i].modType, modRef->modList[i].modName);

		for(j = 0; j < modRef->modList[i].memberCount; j++)
		{
			printf("%s = %s\n", modRef->modList[i].memberList[j].idStr, modRef->modList[i].memberList[j].content);
		}

		printf("\n");
	}
}
