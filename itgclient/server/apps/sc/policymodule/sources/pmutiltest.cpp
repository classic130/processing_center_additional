#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "vspmutil.h"

VSPM_EXPORT void VSPM_DumpDescriptor(VSPM_Descriptor pmd, const char *fname);

void dumpItem(VSPM_Item item, int level) {

	int i = 0;
	char *name;
	char *value;
	VSPM_STATUS status;

	do {

		name = VSPM_GetName(item, &status);
		if (status != VSPM_STATUS_NO_ERROR) { 
			printf("Error %#x: when getting item name: %s\n", status, name);
			break;
		}

		value = VSPM_GetValue(item, &status);
		if (status == VSPM_NOT_FOUND) // it's ok if we get an empty value for the policy
			status = VSPM_STATUS_NO_ERROR;
		if (status != VSPM_STATUS_NO_ERROR) { 
			printf("Error %#x: when getting item value for item name: %s\n", status, name);
			break;
		}

		for (i= 0; i < level; i++)
			printf("    ");
		printf("%s : ", name);
		if (value)
			printf("%s", value);
		printf("\n");

	} while (0);

	if (name)
		VSPM_FreeString(name, &status);

	if (value)
		VSPM_FreeString(value, &status);

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

	name = VSPM_GetContainerName(container, &status);
	if (status != VSPM_STATUS_NO_ERROR)
		return;

	cntCount = VSPM_ContainerCount(container, &status);
	if (status != VSPM_STATUS_NO_ERROR)
		return;

	itmCount = VSPM_ItemCount(container, &status);
	if (status != VSPM_STATUS_NO_ERROR)
		return;

	version = VSPM_GetVersion(container, &status);
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
		item = VSPM_GetItem(container, i, &status);
		if (status != VSPM_STATUS_NO_ERROR)
			return;

		dumpItem(item, level + 1);
		if (item) {
			VSPM_FreeItem(item, &status);
			item = NULL;
			if (status != VSPM_STATUS_NO_ERROR) { 
				printf("Error %#x: when freeing item\n", status);
				break;
			}
		}
	}

	for (i = 0; i < cntCount; i++) {
		subcont = VSPM_GetContainer(container, i, &status);
		if (status != VSPM_STATUS_NO_ERROR)
			return;

		dumpContainer(subcont, level + 1);
		if (subcont) {
			VSPM_FreeContainer(subcont, &status);
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

void dump(VSPM_Descriptor fd) {

	int i = 0;
	int cntCount = 0;
	int itmCount = 0;
	VSPM_STATUS status;
	VSPM_Container container = NULL;
	VSPM_Item item = NULL;
	VSPM_Version version = NULL;

	cntCount = VSPM_ContainerCountFromDescriptor(fd, &status);
	if (status != VSPM_STATUS_NO_ERROR)
		return;

	printf("Policy file contains %d top containers\n", cntCount);

	itmCount = VSPM_ItemCountFromDescriptor(fd, &status);
	if (status != VSPM_STATUS_NO_ERROR)
		return;

	printf("Policy file contains %d top items\n", itmCount);

	version = VSPM_GetVersionFromDescriptor(fd, &status);
	if (status != VSPM_STATUS_NO_ERROR)
		return;

	printf("Policy file major version %d \n", version->major);
	printf("Policy file minor version %d \n", version->minor);

	VSPM_FreeVersion(version, &status);
	version = NULL;
	if (status != VSPM_STATUS_NO_ERROR) { 
		printf("Error %#x: when freeing version\n", status);
		return;
	}

	for (i = 0; i < itmCount; i++) {
		item = VSPM_GetItemFromDescriptor(fd, i, &status);
		if (status != VSPM_STATUS_NO_ERROR)
			return;

		dumpItem(item, 0);
		if (item) {
			VSPM_FreeItem(item, &status);
			item = NULL;
			if (status != VSPM_STATUS_NO_ERROR) { 
				printf("Error %#x: when freeing item\n", status);
				break;
			}
		}
	}

	for (i = 0; i < cntCount; i++) {
		container = VSPM_GetContainerFromDescriptor(fd, i, &status);
		if (status != VSPM_STATUS_NO_ERROR)
			return;

		dumpContainer(container, 0);
		if (container) {
			VSPM_FreeContainer(container, &status);
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


	if (argc < 2) {
		printf("Usage: %s policy_file_name [container name]\n\n", argv[0]);
		exit(1);
	}

	VSPM_Descriptor fd = VSPM_Open(argv[1], &status);
	if (status != VSPM_STATUS_NO_ERROR)
	{
		printf("Error %#x\n", status);
		exit((int)status);
	}

	dump(fd);

	if (argc > 2) {
		container = VSPM_GetContainerByNameFromDescriptor(fd, argv[2], &status);
		if (status == VSPM_STATUS_NO_ERROR) {
			dumpContainer(container, 0);
			VSPM_FreeContainer(container, &status);
			container = NULL;
		}
		else if (status == VSPM_NOT_FOUND) {
			printf("Cannot find container %s\n", argv[2]);
		}
		else {
			printf("Error %#x when searching for %s\n", status, argv[2]);
		}
	}

//	VSPM_DumpDescriptor(fd, "testdump");

	VSPM_Close(fd);
	return (int)status;
}
