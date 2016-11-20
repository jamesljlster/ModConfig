#include <stdio.h>
#include <stdlib.h>

#include <ModConfig.h>
#include <modcfg_private.h>

int main()
{
	char* strsrc = "Hello World! Oh Oh Oh";
	char* strdst = NULL;

	struct MODCFG_MEMBER srcMember;
	struct MODCFG_MEMBER dstMember;

	struct MODCFG_MODULE srcModule;
	struct MODCFG_MODULE dstModule;

	struct MODCFG_STRUCT srcStruct;
	struct MODCFG_STRUCT dstStruct;

	printf("Test string clone\n");
	strdst = modcfg_str_clone(strsrc);
	printf("Src:\t%s\n", strsrc);
	printf("Dst:\t%s\n", strdst);
	printf("\n");
	free(strdst);
	
	printf("Test member clone\n");
	srcMember.idStr = "TestMember";
	srcMember.content = "Test Content";
	modcfg_clone_member(&dstMember, &srcMember);
	printf("Src Member: ");
	modcfg_print_member(&srcMember);
	printf("Dst Member: ");
	modcfg_print_member(&dstMember);
	printf("\n");
	modcfg_delete_member(&dstMember);

	printf("Test module clone\n");
	srcModule.modName = "TestModule";
	srcModule.modType = "module";
	srcModule.memberCount = 1;
	srcModule.memberList = &srcMember;
	modcfg_clone_module(&dstModule, &srcModule);
	printf("Src Module:\n");
	modcfg_print_module(&srcModule);
	printf("Dst Module:\n");
	modcfg_print_module(&dstModule);
	printf("\n");
	modcfg_delete_module(&dstModule);

	printf("Test struct clone\n");
	srcStruct.modCount = 1;
	srcStruct.modList = &srcModule;
	modcfg_clone_struct(&dstStruct, &srcStruct);
	printf("Src Struct:\n");
	modcfg_print_struct(&srcStruct);
	printf("Dst Struct:\n");
	modcfg_print_struct(&dstStruct);
	printf("\n");
	modcfg_delete_struct(&dstStruct);

	return 0;
}

