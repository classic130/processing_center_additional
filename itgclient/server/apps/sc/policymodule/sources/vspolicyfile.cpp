/*
$Revision: 1.1.2.1 $
$Header: /cvs/itgclient/server/apps/sc/policymodule/sources/Attic/vspolicyfile.cpp,v 1.1.2.1 2001/09/06 22:32:38 ajayaram Exp $
*/

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1999. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "vspmutilP.h"
#include "vspolicyfile.h"

static int addSubContainer (VSPolicyFile &fp, VSContainer *container, char *lastError);

int addSubContainer (VSPolicyFile &fp, VSContainer *container, char *lastError)
{
        int status = 0;
        VSContainer *subContainer;
        VSNvp *nvp;
        char *name;
        int nameLen;
        char *value;
        int valueLen;
        char op;

        while (fp.getNext(&name, &nameLen, &op, &value, &valueLen))
        {
                switch (op)
                {
                case '{':
                        subContainer = new VSContainer(container, name, nameLen);
                        if (subContainer)
                        {
                                container->addContainer(subContainer);
                                status = addSubContainer(fp, subContainer, lastError);
                        }
                        else
                        {
                                sprintf(lastError, "Out of memory at line %d", fp.lineNum());
                                status = ENOMEM;
                        }
                        break;
                case '}':
                        return 0;
                        break;
                case ':':
                        nvp = new VSNvp(container, name, nameLen, (unsigned char *)value, valueLen);
                        if (nvp == NULL)
                        {
                                sprintf(lastError, "Out of memory at line %d", fp.lineNum());
                                status = ENOMEM;
                        }
                        else 
                                container->addItem(nvp);
                        break;
                default:
                        status = EINVAL;
                        sprintf(lastError, "Invalid token [%c] found at line %d", op, fp.lineNum());
                        break;
                }
                if (status)
                        break;
        }
        if (status)
        {
                sprintf(lastError, "No closing bracket for section %s", container->name());
                status = EINVAL;
        }
        return status;
}


////////////////////////////////////////////////////////////////////
int VSPolicyFile::checkFileFormat(VSContainer *container)
////////////////////////////////////////////////////////////////////
{
	int status = 0;
	unsigned int cookieNameLen = strlen(SPEC_COOKIE);
	unsigned char cookie[10];
	unsigned short major = 0;
	unsigned short minor = 0;

	cookie[0] = '\0';
	fgets((char *)cookie, sizeof(cookie), _fp);
	if (strlen((const char *)cookie) < 8)
		return (status = VSPM_INVALID_FILE_FORMAT);

	if (strncmp((const char*)cookie, SPEC_COOKIE, cookieNameLen) != 0)
		return (status = VSPM_INVALID_FILE_FORMAT);

	// Retrieve the major version number
	if (isdigit(cookie[cookieNameLen]))
		major = cookie[cookieNameLen] - '0';
	else
		return (status = VSPM_INVALID_FILE_FORMAT);
	
	if (isdigit(cookie[cookieNameLen + 1]))
		major = major * 10 + (cookie[cookieNameLen + 1] - '0');
	else
		return (status = VSPM_INVALID_FILE_FORMAT);
	
	// Retrieve the minor version number
	if (isdigit(cookie[cookieNameLen + 2]))
		minor = cookie[cookieNameLen + 2] - '0';
	else
		return (status = VSPM_INVALID_FILE_FORMAT);
	
	if (isdigit(cookie[cookieNameLen + 3]))
		minor = minor * 10 + (cookie[cookieNameLen + 3] - '0');
	else
		return (status = VSPM_INVALID_FILE_FORMAT);
	
	if (major > MAJOR_VERSION)
		return (status = VSPM_NOT_SUPPORTED_FILE_FORMAT);

	container->setMajorVersion(major);
	container->setMinorVersion(minor);

	return status;
}


////////////////////////////////////////////////////////////////////
int VSPolicyFile::createRootContainer(VSContainer *root, const char *pathname, char *lastError)
////////////////////////////////////////////////////////////////////
{
        VSContainer *container;
        VSNvp *item;
        VSPolicyFile fp(pathname, lastError);
        char *name;
        int nameLen;
        char *value;
        int valueLen;
        char op;
        int status;

        status = fp.status();
        if (status)
                return status;

	// Check whether the file has the right version cookie
	status = fp.checkFileFormat(root);
	if (status)
		return status;

        while (fp.getNext(&name, &nameLen, &op, &value, &valueLen))
        {
                switch (op)
                {
                case '{':
                        container = new VSContainer(root, name, nameLen);
                        if (container)
                        {
                                root->addContainer(container);
                                status = addSubContainer(fp, container, lastError);
                        }
                        else
                        {
                                sprintf(lastError, "Out of memory at line %d", fp.lineNum());
                                status = ENOMEM;
                        }
                        break;
                case ':':
                        item = new VSNvp(root, name, nameLen, (unsigned char *)value, valueLen);
                        if (item == NULL)
                        {
                                sprintf(lastError, "Out of memory at line %d", fp.lineNum());
                                status = ENOMEM;
                        }
                        else
                                root->addItem(item);
                        break;
                default:
                        status = EINVAL;
                        sprintf(lastError, "Invalid token [%c] found at line %d", op, fp.lineNum());
                        break;
                }
                if (status)
                        break;
        }

        return status;
}

