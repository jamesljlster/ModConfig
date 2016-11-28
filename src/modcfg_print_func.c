#include <stdio.h>

#include "modcfg.h"
#include "modcfg_private.h"

void modcfg_print_detail(MODCFG mod)
{
	struct MODCFG_STRUCT* modRef = (struct MODCFG_STRUCT*)mod;
	
	modcfg_print_struct(modRef);
}

void modcfg_print_member(struct MODCFG_MEMBER* src)
{
	printf("%s", src->idStr);

	if(src->content != NULL)
		printf(" = %s", src->content);
	
	printf(";\n");
}

void modcfg_print_module(struct MODCFG_MODULE* src)
{
	int i;

	printf("%s %s {\n", src->modType, src->modName);
	for(i = 0; i < src->memberCount; i++)
	{
		printf("    ");
		modcfg_print_member(&src->memberList[i]);
	}
	printf("}\n");
}

void modcfg_print_struct(struct MODCFG_STRUCT* src)
{
	int i;

	for(i = 0; i < src->modCount; i++)
	{
		modcfg_print_module(&src->modList[i]);
		printf("\n");
	}
}


