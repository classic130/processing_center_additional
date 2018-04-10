#ifdef WIN32
//#include "stdafx.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "vspmsp.h"
#include "vspmsmp.h"

//VSPM_EXPORT void VSPM_DumpDescriptor(VSPM_Descriptor pmd, const char *fname);

void dumpItem(VSPM_Item item, int level) {

	int i = 0;
	char *name;
	char *value;
	VSPM_STATUS status;

	do {

		name = VSPMSP_GetName(item, &status);
		if (status != VSPM_STATUS_NO_ERROR) { 
			printf("Error %#x: when getting item name\n", status);
			break;
		}

		value = VSPMSP_GetValue(item, &status);
		if (status != VSPM_STATUS_NO_ERROR) { 
			printf("Error %#x: when getting item value\n", status);
			break;
		}

		for (i= 0; i < level; i++)
			printf("    ");
		printf("%s : ", name);
		printf("%s\n", value);

	} while (0);

}

void dumpContainer(VSPM_Container container, int level) {

	int i = 0;
	int cntCount = 0;
	int itmCount = 0;
	VSPM_STATUS status;
	VSPM_Container subcont = NULL;
	VSPM_Item item = NULL;
	VSPM_Version version = NULL;
	char *name = NULL;

	name = VSPMSP_GetContainerName(container, &status);
	if (status != VSPM_STATUS_NO_ERROR)
		return;

	cntCount = VSPMSP_ContainerCount(container, &status);
	if (status != VSPM_STATUS_NO_ERROR)
		return;

	itmCount = VSPMSP_ItemCount(container, &status);
	if (status != VSPM_STATUS_NO_ERROR)
		return;

	version = VSPMSP_GetVersion(container, &status);
	if (status != VSPM_STATUS_NO_ERROR)
		return;

	//printf("major version %d \n", version->major);
	//printf("minor version %d \n", version->minor);

	for (i = 0; i < level; i++)
		printf("    ");
	printf("%s {\n", name);

	for (i = 0; i < level+1; i++)
		printf("    ");
	printf("item count %d \n", itmCount);

	for (i = 0; i < level+1; i++)
		printf("    ");
	printf("container count %d \n", cntCount);

	for (i = 0; i < level+1; i++)
		printf("    ");
	printf("major version %d \n", version->major);

	for (i = 0; i < level+1; i++)
		printf("    ");
	printf("minor version %d \n", version->minor);

	for (i = 0; i < itmCount; i++) {
		item = VSPMSP_GetItem(container, i, &status);
		if (status != VSPM_STATUS_NO_ERROR)
			return;

		dumpItem(item, level + 1);
		if (item) {
			item = NULL;
			if (status != VSPM_STATUS_NO_ERROR) { 
				printf("Error %#x: when freeing item\n", status);
				break;
			}
		}
	}

	for (i = 0; i < cntCount; i++) {
		subcont = VSPMSP_GetContainer(container, i, &status);
		if (status != VSPM_STATUS_NO_ERROR)
			return;

		dumpContainer(subcont, level + 1);
		if (subcont) {
			subcont = NULL;
			if (status != VSPM_STATUS_NO_ERROR) { 
				printf("Error %#x: when freeing container\n", status);
				break;
			}
		}
	}

	for (i = 0; i < level; i++)
		printf("    ");
	printf("}\n", name);
	return;
}

void dump(VSPM_Container fd) {

	int i = 0;
	int cntCount = 0;
	int itmCount = 0;
	VSPM_STATUS status;
	VSPM_Container container = NULL;
	VSPM_Item item = NULL;
	VSPM_Version version = NULL;

	cntCount = VSPMSP_ContainerCount(fd, &status);
	if (status != VSPM_STATUS_NO_ERROR)
		return;

	printf("Policy file contains %d top containers\n", cntCount);

	itmCount = VSPMSP_ItemCount(fd, &status);
	if (status != VSPM_STATUS_NO_ERROR)
		return;

	printf("Policy file contains %d top items\n", itmCount);

	version = VSPMSP_GetVersion(fd, &status);
	if (status != VSPM_STATUS_NO_ERROR)
		return;

	printf("Policy file major version %d \n", version->major);
	printf("Policy file minor version %d \n", version->minor);

	version = NULL;
	if (status != VSPM_STATUS_NO_ERROR) { 
		printf("Error %#x: when freeing version\n", status);
		return;
	}

	for (i = 0; i < itmCount; i++) {
		item = VSPMSP_GetItem(fd, i, &status);
		if (status != VSPM_STATUS_NO_ERROR)
			return;

		dumpItem(item, 0);
		if (item) {
			item = NULL;
			if (status != VSPM_STATUS_NO_ERROR) { 
				printf("Error %#x: when freeing item\n", status);
				break;
			}
		}
	}

	for (i = 0; i < cntCount; i++) {
		container = VSPMSP_GetContainer(fd, i, &status);
		if (status != VSPM_STATUS_NO_ERROR)
			return;

		dumpContainer(container, 0);
		if (container) {
			container = NULL;
			if (status != VSPM_STATUS_NO_ERROR) { 
				printf("Error %#x: when freeing container\n", status);
				break;
			}
		}
	}

	return;
}

main(int argc, char *argv[])
{
	VSPM_STATUS status;
	VSPM_Container container = NULL;
	char *locale;

	/* This is required to allow proper I18N message handling */
	locale = setlocale(LC_ALL, "");

	if (!locale)
		printf("Cannot operate in the requested locale.\nContinuing in the C locale.\n");


	if (argc < 4) {
		printf("Usage: %s config_file policy_template output_policy [custom_policy]\n\n", argv[0]);
		exit(1);
	}

	VSPM_Descriptor fd = VSPMSP_OpenConfig(argv[1], &status);
	if (status != VSPM_STATUS_NO_ERROR)
	{
		printf("Error %#x\n", status);
		exit((int)status);
	}

//	dump(fd);

	if (argc == 5) {
		VSPMSP_GeneratePolicy(fd, argv[2], argv[4], argv[3], &status);
	}
	else {
		VSPMSP_GeneratePolicy(fd, argv[2], NULL, argv[3], &status);
	}

	if (status != VSPM_STATUS_NO_ERROR) {
		printf("%s return status is %x \n", argv[0], status);
	}

//	VSPM_DumpDescriptor(fd, "testdump");

	VSPMSP_Close(fd);
	return (int)status;
}
