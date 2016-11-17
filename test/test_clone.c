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
	free(dstMember.idStr);
	free(dstMember.content);

	printf("Test module clone\n");
	srcModule.modName = "TestModule";
	srcModule.modType = "module";
	srcModule.memberCount = 1;
	srcModule.memberList = &srcMember;

	return 0;
}

