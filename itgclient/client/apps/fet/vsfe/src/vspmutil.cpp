/*
 * $Revision: 1.1.2.1 $
 * $Header: /cvs/itgclient/client/apps/fet/vsfe/src/Attic/vspmutil.cpp,v 1.1.2.1 2000/02/25 01:37:37 aranade Exp $
*/

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1999. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "vspmutilP.h"
#include "vspolicyfile.h"

typedef int Boolean;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifdef WIN32
#define SAMESTR !stricmp
#else
#define SAMESTR !strcasecmp
#endif

//!!!! Should try not to use this global buffer, it's not MT-safe !!!!
static char lastError[1024];


////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Descriptor VSPM_Open(const char *pathname,
        VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSContainer *root = NULL;
	int syserr;

	root = new VSContainer(NULL, pathname, strlen(pathname));
	if (root == NULL)
        {
                *status = VSPM_OUT_OF_MEMORY;
                return (VSPM_Descriptor)NULL;
        }
        syserr = VSPolicyFile::createRootContainer(root, pathname, lastError);

        switch (syserr)
        {
        case 0:
                *status = VSPM_STATUS_NO_ERROR;
                break;
        case ENOMEM:
                *status = VSPM_OUT_OF_MEMORY;
                break;
        case EINVAL:
                *status = VSPM_INVALID_TOKEN;
                break;
        default:
                *status = VSPM_CANNOT_OPEN_FILE;
        }
        if (syserr)
        {
		printf("%s\n", lastError);
                delete root;
                root = NULL;
        }
        return (VSPM_Descriptor)root;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void VSPM_DumpDescriptor(VSPM_Descriptor pmd, const char *fname)
////////////////////////////////////////////////////////////////////
{
        VSContainer *root = (VSContainer *)pmd;
        if (root)
        {
                FILE *fp = fopen(fname, "w");
                if (fp)
                {
                        root->print(fp, 0);
                        fclose(fp);
                }
        }
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void VSPM_DumpContainer(VSPM_Container cnt, const char *fname)
////////////////////////////////////////////////////////////////////
{
        VSContainer *container = (VSContainer *)cnt;
        if (container)
        {
                FILE *fp = fopen(fname, "w");
                if (fp)
                {
                        container->print(fp, 0);
                        fclose(fp);
                }
        }
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void VSPM_Close (VSPM_Descriptor pmd)
////////////////////////////////////////////////////////////////////
{
        VSContainer *root = (VSContainer *)pmd;
        if (root)
                delete root;

}


#if 0
////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Version
        VSPM_GetVersionFromDescriptor (
                VSPM_Descriptor pmd,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSContainer *root = (VSContainer *)pmd;
	VSPM_Version version = NULL;

	if (!root) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return (VSPM_Version)NULL;
	}

	version = (VSPM_Version)malloc(sizeof(struct _VSPM_Version));
	version->major = root->getMajorVersion();
	version->minor = root->getMinorVersion();

	*status = VSPM_STATUS_NO_ERROR;
	
	return version;
		
}
#endif

////////////////////////////////////////////////////////////////////
VSPM_EXPORT unsigned int
        VSPM_ContainerCountFromDescriptor (
                VSPM_Descriptor pmd,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSContainer *root = (VSContainer *)pmd;

	if (!root) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return 0;
	}

	*status = VSPM_STATUS_NO_ERROR;

	return root->countContainer();
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT unsigned int
        VSPM_ItemCountFromDescriptor (
                VSPM_Descriptor pmd,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSContainer *root = (VSContainer *)pmd;

	if (!root) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return 0;
	}

	*status = VSPM_STATUS_NO_ERROR;

	return root->countItem();
}



////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Container
        VSPM_GetContainerByNameFromDescriptor (
                VSPM_Descriptor pmd,
                const char* name, 
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *root = (VSContainer *)pmd;
	VSContainer *container = NULL;
	VSContainer *retCont = NULL;
	char *subStr = NULL, *compStr = NULL, *tmpStr = NULL;
	int len = 0;

	if (!root) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return (VSPM_Container)NULL;
	}

	*status = VSPM_STATUS_NO_ERROR;

	container = root;
	subStr = tmpStr = (char *)name;

	do {
		if ((subStr = strchr((const char*)tmpStr, SCOPE_CHAR)) != NULL) {
			len = strlen((const char*)tmpStr) - strlen((const char*)subStr);
			compStr = (char *)malloc(len + 1);
			if (!compStr) {
				*status = VSPM_OUT_OF_MEMORY;
				break;
			}
			memcpy(compStr, tmpStr, len);
			compStr[len] = '\0';

			tmpStr = ++subStr;

		}
		else {
			len = strlen(tmpStr);
			compStr = (char *)malloc(len + 1);
			if (!compStr) {
				*status = VSPM_OUT_OF_MEMORY;
				break;
			}
			memcpy(compStr, tmpStr, len);
			compStr[len] = '\0';
		}

		if (!compStr) {
			*status = VSPM_NOT_FOUND;
			break;
		}

		container = (VSContainer *)container->searchContainer(compStr);

		free(compStr);
		compStr = NULL;

		if (!container) {
			*status = VSPM_NOT_FOUND;
			break;
		}

	} while (subStr != NULL);

	if (compStr)
		free(compStr);

	if (container) {
		retCont = (VSContainer *)container->duplicate(container->dad(), VS_DUP_ONE);
		if (!retCont) {
			*status = VSPM_OUT_OF_MEMORY;
		}
	}

	return (VSPM_Container)retCont;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Container
        VSPM_GetContainerFromDescriptor (
                VSPM_Descriptor pmd,
                unsigned int index, 
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *root = (VSContainer *)pmd;
	VSContainer *container = NULL;
	VSContainer *retCont = NULL;
	unsigned int i = 0;

	if (!root) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return (VSPM_Container)NULL;
	}

	*status = VSPM_STATUS_NO_ERROR;

	if ((0 > index) || (root->countContainer() <= index)) {
		*status = VSPM_INDEX_OUT_OF_RANGE;
		return (VSPM_Container)NULL;
	}
	
	container = (VSContainer *)root->firstContainer();
	for (i = 1; i <= index; i++) {
		if (!container) {
			*status = VSPM_NOT_FOUND;
			break;
		}
		container = (VSContainer *)root->nextContainer();
	}

	if (container) {
		retCont = (VSContainer *)container->duplicate(container->dad(), VS_DUP_ONE);
		if (!retCont) {
			*status = VSPM_OUT_OF_MEMORY;
		}
	}

	return (VSPM_Container)retCont;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Item
        VSPM_GetItemByNameFromDescriptor (
                VSPM_Descriptor pmd,
                const char* name, 
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *root = (VSContainer *)pmd;
	VSNvp *item = NULL;
	VSNvp *retItem = NULL;

	if (!root) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return (VSPM_Item)NULL;
	}

	*status = VSPM_STATUS_NO_ERROR;

	do {
		item = (VSNvp *)root->searchItem(name);

		if (!item) {
			*status = VSPM_NOT_FOUND;
			break;
		}

	} while (0);

	if (item) {
		retItem = (VSNvp *)item->duplicate(item->dad(), VS_DUP_ONE);
		if (!retItem) {
			*status = VSPM_OUT_OF_MEMORY;
		}
	}

	return (VSPM_Item)retItem;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Item
        VSPM_GetItemFromDescriptor (
                VSPM_Descriptor pmd,
                unsigned int index, 
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *root = (VSContainer *)pmd;
	VSNvp *item = NULL;
	VSNvp *retItem = NULL;
	unsigned int i = 0;

	if (!root) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return (VSPM_Item)NULL;
	}

	*status = VSPM_STATUS_NO_ERROR;

	if ((0 > index) || (root->countItem() <= index)) {
		*status = VSPM_INDEX_OUT_OF_RANGE;
		return (VSPM_Item)NULL;
	}
	
	item = (VSNvp *)root->firstItem();
	for (i = 1; i <= index; i++) {
		if (!item) {
			*status = VSPM_NOT_FOUND;
			break;
		}
		item = (VSNvp *)root->nextItem();
	}

	if (item) {
		retItem = (VSNvp *)item->duplicate(item->dad(), VS_DUP_ONE);
		if (!retItem) {
			*status = VSPM_OUT_OF_MEMORY;
		}
	}

	return (VSPM_Item)retItem;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Version
        VSPM_GetVersion (
                VSPM_Container cnt,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSContainer *container = (VSContainer *)cnt;

	VSPM_Version version = NULL;

	if (!container) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return (VSPM_Version)NULL;
	}

	version = (VSPM_Version)malloc(sizeof(struct _VSPM_Version));
	version->major = container->getMajorVersion();
	version->minor = container->getMinorVersion();

	*status = VSPM_STATUS_NO_ERROR;
		
	return version;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT unsigned int
        VSPM_ContainerCount (
                VSPM_Container cnt,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSContainer *container = (VSContainer *)cnt;

	if (!container) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return 0;
	}

	*status = VSPM_STATUS_NO_ERROR;

	return container->countContainer();
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT unsigned int
        VSPM_ItemCount (
                VSPM_Container cnt,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSContainer *container = (VSContainer *)cnt;

	if (!container) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return 0;
	}

	*status = VSPM_STATUS_NO_ERROR;

	return container->countItem();
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT unsigned char *
        VSPM_GetContainerName (
                VSPM_Container cnt,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *container = (VSContainer *)cnt;
	unsigned char * name = NULL;
	unsigned char * retName = NULL;

	if (!container) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return NULL;
	}


	*status = VSPM_STATUS_NO_ERROR;

	name = (unsigned char *)container->name();
	if (! name) {

		*status = VSPM_INVALID_DESCRIPTOR;

	}
	else {

		retName = (unsigned char *) malloc(strlen((const char *)name) + 1);
		if (! retName) {

			*status = VSPM_OUT_OF_MEMORY;
		}
		else {

			retName[0] = '\0';
			strcpy((char *)retName, (const char *)name);

		}

	}

	return retName;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Container
        VSPM_GetContainerByName (
                VSPM_Container cnt,
                const char* name, 
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *container = (VSContainer *)cnt;
	VSContainer *retCont = NULL;
	char *subStr = NULL, *compStr = NULL, *tmpStr = NULL;
	int len = 0;

	if (!container) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return (VSPM_Container)NULL;
	}

	*status = VSPM_STATUS_NO_ERROR;

	container = container;
	subStr = tmpStr = (char *)name;

	do {
		if ((subStr = strchr(tmpStr, SCOPE_CHAR)) != NULL) {
			len = strlen(tmpStr) - strlen(subStr);
			compStr = (char *)malloc(len + 1);
			if (!compStr) {
				*status = VSPM_OUT_OF_MEMORY;
				break;
			}
			memcpy(compStr, tmpStr, len);
			compStr[len] = '\0';

			tmpStr = ++subStr;

		}
		else {
			len = strlen(tmpStr);
			compStr = (char *)malloc(len + 1);
			if (!compStr) {
				*status = VSPM_OUT_OF_MEMORY;
				break;
			}
			memcpy(compStr, tmpStr, len);
			compStr[len] = '\0';
		}

		if (!compStr) {
			*status = VSPM_NOT_FOUND;
			break;
		}

		container = (VSContainer *)container->searchContainer(compStr);

		free(compStr);
		compStr = NULL;

		if (!container) {
			*status = VSPM_NOT_FOUND;
			break;
		}

	} while (subStr != NULL);

	if (compStr)
		free(compStr);

	if (container) {
		retCont = (VSContainer *)container->duplicate(container->dad(), VS_DUP_ONE);
		if (!retCont) {
			*status = VSPM_OUT_OF_MEMORY;
		}
	}

	return (VSPM_Container)retCont;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Container
        VSPM_GetContainer (
                VSPM_Container cnt,
                unsigned int index, 
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *parent = (VSContainer *)cnt;
	VSContainer *container = NULL;
	VSContainer *retCont = NULL;
	unsigned int i = 0;

	if (!parent) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return (VSPM_Container)NULL;
	}

	*status = VSPM_STATUS_NO_ERROR;

	if ((0 > index) || (parent->countContainer() <= index)) {
		*status = VSPM_INDEX_OUT_OF_RANGE;
		return (VSPM_Container)NULL;
	}
	
	container = (VSContainer *)parent->firstContainer();
	for (i = 1; i <= index; i++) {
		if (!container) {
			*status = VSPM_NOT_FOUND;
			break;
		}
		container = (VSContainer *)parent->nextContainer();
	}

	if (container) {
		retCont = (VSContainer *)container->duplicate(container->dad(), VS_DUP_ONE);
		if (!retCont) {
			*status = VSPM_OUT_OF_MEMORY;
		}
	}

	return (VSPM_Container)retCont;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Item
        VSPM_GetItemByName (
                VSPM_Container cnt,
                const char* name, 
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *container = (VSContainer *)cnt;
	VSNvp *item = NULL;
	VSNvp *retItem = NULL;

	if (!container) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return (VSPM_Item)NULL;
	}

	*status = VSPM_STATUS_NO_ERROR;

	do {
		item = (VSNvp *)container->searchItem(name);

		if (!item) {
			*status = VSPM_NOT_FOUND;
			break;
		}

	} while (0);

	if (item) {
		retItem = (VSNvp *)item->duplicate(item->dad(), VS_DUP_ONE);
		if (!retItem) {
			*status = VSPM_OUT_OF_MEMORY;
		}
	}

	return (VSPM_Item)retItem;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Item
        VSPM_GetItem (
                VSPM_Container cnt,
                unsigned int index, 
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *container = (VSContainer *)cnt;
	VSNvp *item = NULL;
	VSNvp *retItem = NULL;
	unsigned int i = 0;

	if (!container) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return (VSPM_Item)NULL;
	}

	*status = VSPM_STATUS_NO_ERROR;

	if ((0 > index) || (container->countItem() <= index)) {
		*status = VSPM_INDEX_OUT_OF_RANGE;
		return (VSPM_Item)NULL;
	}
	
	item = (VSNvp *)container->firstItem();
	for (i = 1; i <= index; i++) {
		if (!item) {
			*status = VSPM_NOT_FOUND;
			break;
		}
		item = (VSNvp *)container->nextItem();
	}

	if (item) {
		retItem = (VSNvp *)item->duplicate(item->dad(), VS_DUP_ONE);
		if (!retItem) {
			*status = VSPM_OUT_OF_MEMORY;
		}
	}

	return (VSPM_Item)retItem;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT unsigned char *
        VSPM_GetName (
                VSPM_Item itm,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSNvp *item = (VSNvp *)itm;
	char *name = NULL, *dupName = NULL;
	int len = 0;

	*status = VSPM_STATUS_NO_ERROR;

	if (!item) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return NULL;
	}

	if ((name = (char *)item->name()) != NULL) {
		len = strlen(name);
		dupName = (char *)malloc(len + 1);
		if (dupName) {
			memcpy(dupName, name, len);
			dupName[len] = '\0';
		}
		else
			*status = VSPM_OUT_OF_MEMORY;
	}
	else {
		*status = VSPM_NOT_FOUND;
	}
	
	return (unsigned char *)dupName;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT unsigned char *
        VSPM_GetValue (
                VSPM_Item itm,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSNvp *item = (VSNvp *)itm;
	char *value = NULL, *dupValue = NULL;
	int len = 0;

	*status = VSPM_STATUS_NO_ERROR;

	if (!item) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return NULL;
	}

	if ((value = (char *)item->value()) != NULL) {
		len = item->valueLen();
		dupValue = (char *)malloc(len + 1);
		if (dupValue) {
			memcpy(dupValue, value, len);
			dupValue[len] = '\0';
		}
		else
			*status = VSPM_OUT_OF_MEMORY;
	}
	else {
		*status = VSPM_NOT_FOUND;
	}
	
	return (unsigned char *)dupValue;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT unsigned char *
        VSPM_DescribeStatus (
                VSPM_Descriptor pmd,
                VSPM_STATUS status)
////////////////////////////////////////////////////////////////////
{
	char * statusMsg = NULL;

	statusMsg = (char *) malloc (2048);
	if (! statusMsg)
		return NULL;

	switch (status) {
	case VSPM_STATUS_NO_ERROR:
		strcpy(statusMsg, "No error");
		break;
	case VSPM_CANNOT_OPEN_FILE:
		strcpy(statusMsg, "Cannot open file");
		break;
	case VSPM_INVALID_TOKEN:
		strcpy(statusMsg, "Invalid token in the policy file");
		break;
	case VSPM_NO_CLOSE_SESSION:
		strcpy(statusMsg, "Missing closing bracket in the policy file");
		break;
	case VSPM_OUT_OF_MEMORY:
		strcpy(statusMsg, "Operation failed due to failure when allocating memory");
		break;
	case VSPM_INVALID_DESCRIPTOR:
		strcpy(statusMsg, "Invalid descriptor or container");
		break;
	case VSPM_NOT_FOUND:
		strcpy(statusMsg, "Requested item not found");
		break;
	case VSPM_INVALID_TEXT:
		strcpy(statusMsg, "Invalid text value");
		break;
	case VSPM_INVALID_T61:
		strcpy(statusMsg, "Invalid T61 value");
		break;
	case VSPM_INVALID_EMAIL:
		strcpy(statusMsg, "Invalid e-mail value");
		break;
	case VSPM_INVALID_NUMBER:
		strcpy(statusMsg, "Invalid number value");
		break;
	case VSPM_INVALID_BASE64:
		strcpy(statusMsg, "Invalid BASE64 value");
		break;
	case VSPM_INVALID_PHONE:
		strcpy(statusMsg, "Invalid phone value");
		break;
	case VSPM_INVALID_DATE:
		strcpy(statusMsg, "Invalid date value");
		break;
	case VSPM_INVALID_TYPE:
		strcpy(statusMsg, "Invalid data type");
		break;
	case VSPM_FIELD_REQUIRED:
		strcpy(statusMsg, "Missing a required field");
		break;
	case VSPM_FIELD_TOO_SHORT:
		strcpy(statusMsg, "Data value is shorter than the minimum length");
		break;
	case VSPM_FIELD_TOO_LONG:
		strcpy(statusMsg, "Data value is longer than the minimum length");
		break;
	case VSPM_INVALID_VERSION:
		strcpy(statusMsg, "Invalid version number");
		break;
	case VSPM_INDEX_OUT_OF_RANGE:
		strcpy(statusMsg, "The given index is out of range");
		break;
	case VSPM_INVALID_FILE_FORMAT:
		strcpy(statusMsg, "The file format is invalid");
		break;
	case VSPM_NOT_SUPPORTED_FILE_FORMAT:
		strcpy(statusMsg, "The file format is not supported");
		break;
	case VSPM_INVALID_PASSCODE:
		strcpy(statusMsg, "The passcode value is invalid");
		break;
	case VSPM_NOT_SUPPORTED_FEATURE:
		strcpy(statusMsg, "The feature is not supported");
		break;
	case VSPM_INVALID_CRS_URL:
		strcpy(statusMsg, "The crs url is not valid");
		break;
	default:
		strcpy(statusMsg, "Unknown error condition");
		break;

	}

	return (unsigned char *) statusMsg;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void
        VSPM_FreeVersion (
                VSPM_Version ver,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	*status = VSPM_STATUS_NO_ERROR;

	if (!ver) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return;
	}

	free(ver);

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void
        VSPM_FreeContainer (
                VSPM_Container cnt,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSContainer *container = (VSContainer *)cnt;
	*status = VSPM_STATUS_NO_ERROR;


	if (!container) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return;
	}

	delete container;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void
        VSPM_FreeItem (
                VSPM_Item itm,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	*status = VSPM_STATUS_NO_ERROR;

	VSNvp *item = (VSNvp *)itm;

	if (!item) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return;
	}

	delete item;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void
        VSPM_FreeString (
                unsigned char * str,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	*status = VSPM_STATUS_NO_ERROR;

	if (!str) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return;
	}

	free(str);
}

