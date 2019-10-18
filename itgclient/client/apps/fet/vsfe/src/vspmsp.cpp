/*
 * $Revision: 1.1.2.1 $
 * $Header: /cvs/itgclient/client/apps/fet/vsfe/src/Attic/vspmsp.cpp,v 1.1.2.1 2000/02/25 01:37:35 aranade Exp $
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

#ifndef WIN32
#include <dlfcn.h>
#else
#include <windows.h>
#include <windowsx.h>
#endif


#include "vspmspP.h"
#include "vspolicyfile.h"

extern void UpdatePolicies(VSContainer *, VSPM_STATUS *);

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
VSPM_STATUS parseUrl(const char *url,   char **protocol,
                           char **host, char **port, char **res) 
////////////////////////////////////////////////////////////////////
{

	VSPM_STATUS status = VSPM_STATUS_NO_ERROR;

	char *myProtocol = NULL;
	char *myHost = NULL;
	char *myPort = NULL;
	char *myRes = NULL;
	char *ptr = NULL;
	char *ptr2 = NULL;
	char *ptr3 = NULL;
	unsigned int len1 = 0, len2 = 0, len3 = 0;

	do {

		if (NULL == url)
			break;

		if ((ptr = strstr(url, "://")) == NULL) {
			len1 = strlen(url);
			myRes = (char *) malloc(len1 + 1);
			if (NULL == myRes) {
				status = VSPM_OUT_OF_MEMORY;
				break;
			}

			memcpy(myRes, url, len1);
			myRes[len1] = '\0';
		}
		else {
			len1 = strlen(url);
			len2 = strlen(ptr);
			myProtocol = (char *) malloc(len1 - len2 + 1);
			if (NULL == myProtocol) {
				status = VSPM_OUT_OF_MEMORY;
				break;
			}

			memcpy(myProtocol, url, len1 - len2);
			myProtocol[(len1 - len2)] = '\0';

			if (len2 == 3) {
				status = VSPM_INVALID_URL;
				break;
			}

			ptr += 3;

			/* If it is file protocol, just get the rest of the url */
			if ( ! strcmp(myProtocol, FILE_PROTOCOL)) {

				len2 = strlen(ptr);
				myRes = (char *) malloc(len2 + 1);

				if (NULL == myRes) {
					status = VSPM_OUT_OF_MEMORY;
					break;
				}

				memcpy(myRes, ptr, len2);
				myRes[len2] = '\0';

				break;

			}

			/* If it is not file protocol */

			if ((ptr2 = strchr(ptr, '/')) == NULL) {
				status = VSPM_INVALID_URL;
				break;
			}

			len2 = strlen(ptr2);
			myRes = (char *) malloc(len2 + 1);

			if (NULL == myRes) {
				status = VSPM_OUT_OF_MEMORY;
				break;
			}

			memcpy(myRes, ptr2, len2);
			myRes[len2] = '\0';

			if (ptr != ptr2) {

				if ((ptr3 = strchr(ptr, ':')) != NULL) {

					len1 = strlen(ptr);
					len2 = strlen(ptr2);
					len3 = strlen(ptr3);

					myHost = (char *) malloc(len1 - len3 + 1);

					if (NULL == myHost) {
						status = VSPM_OUT_OF_MEMORY;
						break;
					}

					memcpy(myHost, ptr, len1 - len3);
					myHost[(len1 - len3)] = '\0';

					myPort = (char *) malloc(len3 - len2 + 1);

					if (NULL == myPort) {
						status = VSPM_OUT_OF_MEMORY;
						break;
					}

					memcpy(myPort, ptr3, len3 - len2);
					myPort[(len3 - len2)] = '\0';

				}
				else {

					len1 = strlen(ptr);
					len2 = strlen(ptr2);

					myHost = (char *) malloc(len1 - len2 + 1);

					if (NULL == myHost) {
						status = VSPM_OUT_OF_MEMORY;
						break;
					}

					myHost[0] = '\0';
					strncpy(myHost, ptr, len1 - len2);

				}
			}
			
		}

	} while (0);

	if (status != VSPM_STATUS_NO_ERROR) {

		if (myProtocol)
			free(myProtocol);

		if (myHost)
			free(myHost);

		if (myPort)
			free(myPort);

		if (myRes)
			free(myRes);

	}
	else {

		if ((NULL != myProtocol) && (NULL != protocol))
			*protocol = myProtocol;

		if ((NULL != myHost) && (NULL != host))
			*host = myHost;

		if ((NULL != myPort) && (NULL != port))
			*port = myPort;

		if ((NULL != myRes) && (NULL != res))
			*res = myRes;

	}

	return status;

}


////////////////////////////////////////////////////////////////////
VSPM_STATUS openUrl(const char *url, VSContainer **container) 
////////////////////////////////////////////////////////////////////
{
	VSPM_STATUS status = VSPM_STATUS_NO_ERROR;
	VSContainer *myContainer = NULL;
	char * protocol = NULL;
	char * host = NULL;
	char * port = NULL;
	char * res = NULL;

	do {

		status = parseUrl(url, &protocol, &host, &port, &res);

		if (status != VSPM_STATUS_NO_ERROR)
			break;

		if (NULL != protocol) {

			if (! strcmp(protocol, FILE_PROTOCOL)) {

				if (! res) {
					status = VSPM_INVALID_URL;
					break;
				}

				status = openFileUrl(res, &myContainer);
			}
			else {
				/* In the future we can add other protocol support */
				status = VSPM_NOT_SUPPORTED_PROTOCOL;
				break;
			}

		}
		else {

			status = openFileUrl(res, &myContainer);

		}

	} while (0);

	if (status == VSPM_STATUS_NO_ERROR) {

		*container = myContainer;

	}

	if (protocol)
		free(protocol);

	if (host)
		free(host);

	if (port)
		free(port);

	if (res)
		free(res);

	return status;

}


////////////////////////////////////////////////////////////////////
VSPM_STATUS openFileUrl(const char *pathname, VSContainer **container) 
////////////////////////////////////////////////////////////////////
{

	VSPM_STATUS status = VSPM_STATUS_NO_ERROR;
	VSContainer *root = NULL;
	int syserr;

	do {

		root = new VSContainer(NULL, pathname, strlen(pathname));
		if (root == NULL)
    	{
            status = VSPM_OUT_OF_MEMORY;
            break;
    	}
    	syserr = VSPolicyFile::createRootContainer(root, pathname, lastError);

    	switch (syserr)
    	{
    	case 0:
            status = VSPM_STATUS_NO_ERROR;
            break;
    	case ENOMEM:
            status = VSPM_OUT_OF_MEMORY;
            break;
    	case EINVAL:
            status = VSPM_INVALID_TOKEN;
            break;
    	default:
            status = VSPM_CANNOT_OPEN_FILE;
    	}

    	if (syserr)
    	{
			printf("%s\n", lastError);
            delete root;
            root = NULL;
    	}
		else {
			*container = root;
		}

	} while (0);

    return status;

}


////////////////////////////////////////////////////////////////////
char * getDefaultPolicyConfigUrl (VSPM_STATUS * status)
////////////////////////////////////////////////////////////////////
{

	char *defaultConf = NULL;
	char *ecasInstallDir = NULL;

	do {

		ecasInstallDir = getenv(ECASINSTALL);
		if ((NULL == ecasInstallDir) || (strlen(ecasInstallDir) == 0)) {
			defaultConf = (char *) malloc(strlen(FILE_PROTOCOL) +
										  strlen(PROTOCOL_DELIMITER) +
										  strlen(DEFAULT_ECAS_INSTALL) +
										  strlen(DEFAULT_POLICY_CONFIG) + 1);
			if (NULL == defaultConf) {
				*status = VSPM_OUT_OF_MEMORY;
				break;
			}

			memset(defaultConf, 0, (strlen(FILE_PROTOCOL) +
									strlen(PROTOCOL_DELIMITER) +
									strlen(DEFAULT_ECAS_INSTALL) +
									strlen(DEFAULT_POLICY_CONFIG) + 1));
			strcpy(defaultConf, FILE_PROTOCOL);
			strcat(defaultConf, PROTOCOL_DELIMITER);
			strcat(defaultConf, DEFAULT_ECAS_INSTALL);
			strcat(defaultConf, DEFAULT_POLICY_CONFIG);

		}
		else {

			defaultConf = (char *) malloc(strlen(FILE_PROTOCOL) +
										  strlen(PROTOCOL_DELIMITER) +
										  strlen(ecasInstallDir) +
										  strlen(DEFAULT_POLICY_CONFIG + 1));

			if (NULL == defaultConf) {
				*status = VSPM_OUT_OF_MEMORY;
				break;
			}

			memset(defaultConf, 0, (strlen(FILE_PROTOCOL) +
									strlen(PROTOCOL_DELIMITER) +
									strlen(ecasInstallDir) +
									strlen(DEFAULT_POLICY_CONFIG) + 1));
			strcpy(defaultConf, FILE_PROTOCOL);
			strcat(defaultConf, PROTOCOL_DELIMITER);
			strcat(defaultConf, ecasInstallDir);
			strcat(defaultConf, DEFAULT_POLICY_CONFIG);

		}

	} while (0);

	if (*status != VSPM_STATUS_NO_ERROR) {

		if (defaultConf) {
			free(defaultConf);
			defaultConf = NULL;
		}
	}

	return defaultConf;

}


////////////////////////////////////////////////////////////////////
char * getDefaultPolicyTemplateUrl (VSPM_STATUS * status)
////////////////////////////////////////////////////////////////////
{

	char *defaultTemplate = NULL;
	char *ecasInstallDir = NULL;

	do {

		ecasInstallDir = getenv(ECASINSTALL);
		if ((NULL == ecasInstallDir) || (strlen(ecasInstallDir) == 0)) {
			defaultTemplate = (char *) malloc(strlen(FILE_PROTOCOL) +
										  strlen(PROTOCOL_DELIMITER) +
										  strlen(DEFAULT_ECAS_INSTALL) +
										  strlen(DEFAULT_POLICY_TEMPLATE) + 1);
			if (NULL == defaultTemplate) {
				*status = VSPM_OUT_OF_MEMORY;
				break;
			}

			memset(defaultTemplate, 0, (strlen(FILE_PROTOCOL) +
									strlen(PROTOCOL_DELIMITER) +
									strlen(DEFAULT_ECAS_INSTALL) +
									strlen(DEFAULT_POLICY_TEMPLATE) + 1));
			strcpy(defaultTemplate, FILE_PROTOCOL);
			strcat(defaultTemplate, PROTOCOL_DELIMITER);
			strcat(defaultTemplate, DEFAULT_ECAS_INSTALL);
			strcat(defaultTemplate, DEFAULT_POLICY_TEMPLATE);

		}
		else {

			defaultTemplate = (char *) malloc(strlen(FILE_PROTOCOL) +
										  strlen(PROTOCOL_DELIMITER) +
										  strlen(ecasInstallDir) +
										  strlen(DEFAULT_POLICY_TEMPLATE + 1));

			if (NULL == defaultTemplate) {
				*status = VSPM_OUT_OF_MEMORY;
				break;
			}

			memset(defaultTemplate, 0, (strlen(FILE_PROTOCOL) +
									strlen(PROTOCOL_DELIMITER) +
									strlen(ecasInstallDir) +
									strlen(DEFAULT_POLICY_TEMPLATE) + 1));
			strcpy(defaultTemplate, FILE_PROTOCOL);
			strcat(defaultTemplate, PROTOCOL_DELIMITER);
			strcat(defaultTemplate, ecasInstallDir);
			strcat(defaultTemplate, DEFAULT_POLICY_TEMPLATE);

		}

	} while (0);

	if (*status != VSPM_STATUS_NO_ERROR) {

		if (defaultTemplate) {
			free(defaultTemplate);
			defaultTemplate = NULL;
		}
	}

	return defaultTemplate;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Descriptor VSPMSP_OpenConfig(const char *configUrl,
        VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSContainer *configCnt = NULL;
	char *defaultConf = NULL;

	do {

		if (NULL == configUrl) {

			defaultConf = getDefaultPolicyConfigUrl(status);
			if (*status != VSPM_STATUS_NO_ERROR)
				break;
	
			if (NULL == defaultConf) {
				*status = VSPM_OUT_OF_MEMORY;
				break;
			}

			*status = openUrl(defaultConf, &configCnt);

		}
		else {

			*status = openUrl(configUrl, &configCnt);

		}

	} while (0);

	if (defaultConf)
		free(defaultConf);

    return (VSPM_Descriptor) configCnt;

}



////////////////////////////////////////////////////////////////////
VSContainer * openPolicyTemplate(const char *templateUrl,
        VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSPM_STATUS myStatus = VSPM_STATUS_NO_ERROR;

	char *defaultTemplateUrl = NULL;
	VSContainer *templateCnt = NULL;

	do {

		/* Policy template has to be available, either a user-supplied one
		 * or the default one
		 */
		if (templateUrl) {

			myStatus = openUrl(templateUrl, &templateCnt);
			if (myStatus != VSPM_STATUS_NO_ERROR)
				break;

		}
		else {

			defaultTemplateUrl = getDefaultPolicyTemplateUrl (&myStatus);
			if (myStatus != VSPM_STATUS_NO_ERROR)
				break;

			myStatus = openUrl(defaultTemplateUrl, &templateCnt);
			if (myStatus != VSPM_STATUS_NO_ERROR)
				break;
		}

	} while (0);

	if (defaultTemplateUrl)
		free(defaultTemplateUrl);


	return templateCnt;
}


////////////////////////////////////////////////////////////////////
VSContainer * openPolicy(const char *policyUrl,
        VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSPM_STATUS myStatus = VSPM_STATUS_NO_ERROR;

	VSContainer *policyCnt = NULL;

	do {

		if (policyUrl) {

			myStatus = openUrl(policyUrl, &policyCnt);
			if (myStatus != VSPM_STATUS_NO_ERROR)
				break;

		}
		else {
			myStatus = VSPM_CANNOT_OPEN_FILE;
			break;
		}

	} while (0);

	*status = myStatus;

	return policyCnt;

}


////////////////////////////////////////////////////////////////////
int getVersionHandling(VSContainer *configCnt, VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSPM_STATUS myStatus = VSPM_STATUS_NO_ERROR;

	VSNvp *verFlagItem = NULL;
	const unsigned char * verFlagStr = NULL;
	int verFlag = _VSPM_USE_CUSTOM;

	do {

		if (NULL == configCnt) {
			myStatus = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		verFlagItem = (VSNvp *) configCnt->searchItem(VSPM_VERSION_HANDLING);
		if (! verFlagItem) {
			verFlag = _VSPM_USE_CUSTOM;
		}
		else {

			verFlagStr = verFlagItem->value();
			if (! verFlagStr) {

				verFlag = _VSPM_USE_CUSTOM;

			}
			else {

				if (! strcmp((const char *)verFlagStr, VSPM_DEFAULT)) {

					verFlag = _VSPM_USE_CUSTOM;

				}
				else if (! strcmp((const char *)verFlagStr, VSPM_USE_NEWER)) {

					verFlag = _VSPM_USE_NEWER;

				}
				else if (! strcmp((const char *)verFlagStr, VSPM_USE_CUSTOM)) {

					verFlag = _VSPM_USE_CUSTOM;

				}
				else if (! strcmp((const char *)verFlagStr, VSPM_USE_TEMPLATE)) {

					verFlag = _VSPM_USE_TEMPLATE;

				}
				else {

					myStatus = VSPM_NOT_SUPPORTED_VALUE;
					break;
				}
			}
		}
	} while (0);

	*status = myStatus;

	return verFlag;

}


////////////////////////////////////////////////////////////////////
VSContainer * mergePolicy(VSContainer * configCnt,
                                 VSContainer * templateCnt,
                                 VSContainer * policyCnt,
                                 VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSPM_STATUS myStatus = VSPM_STATUS_NO_ERROR;

	int verFlag = _VSPM_USE_CUSTOM;

	VSContainer *templateCntPtr = NULL;
	VSContainer *policyCntPtr = NULL;
	VSContainer *mergedCnt = NULL;
	VSContainer *mergedCntPtr = NULL;
	VSContainer *nvpCntPtr = NULL;

	unsigned int tcMaj = 0, tcMin = 0;
	unsigned int pcMaj = 0, pcMin = 0;
	unsigned int tNumCont = 0;
	unsigned int pNumCont = 0;
	char *tcName = NULL;
	char *pcName = NULL;

	unsigned int i = 0;

	do {

/*		if (NULL == configCnt) {
			myStatus = VSPM_INVALID_DESCRIPTOR;
			break;
		}
*/
		if ((NULL == templateCnt) && (NULL == policyCnt)) {
			myStatus = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		/* custom policy is optional */
		if (policyCnt) {

			mergedCnt = (VSContainer *) policyCnt->duplicate(policyCnt->dad(), VS_DUP_ALL);
			if (! mergedCnt) {
				myStatus = VSPM_OUT_OF_MEMORY;
				break;
			}

			verFlag= getVersionHandling(configCnt, &myStatus);
			if (myStatus != VSPM_STATUS_NO_ERROR)
				break;
			
			/* Merge the template and the custom policy for further processing */
			tNumCont = templateCnt->countContainer();
			pNumCont = mergedCnt->countContainer();

			templateCntPtr = (VSContainer *) templateCnt->firstContainer();
			for (i= 0; i < tNumCont; i++) {

				tcMaj = templateCntPtr->getMajorVersion();
				tcMin = templateCntPtr->getMinorVersion();
				tcName = (char *) templateCntPtr->name();

				mergedCntPtr = (VSContainer *) mergedCnt->searchContainer(tcName);
				if (NULL == mergedCntPtr) {

					mergedCntPtr =
						(VSContainer *) templateCntPtr->duplicate(templateCntPtr->dad(), VS_DUP_ONE);
					if (! mergedCntPtr) {
						myStatus = VSPM_OUT_OF_MEMORY;
						break;
					}
					mergedCnt->addContainer(mergedCntPtr);
					mergedCntPtr = NULL;

				}
				else {

					pcMaj = mergedCntPtr->getMajorVersion();
					pcMin = mergedCntPtr->getMinorVersion();

					/* MAJOR WORK */
					/* If version is different, need to resolve it */


				}

				templateCntPtr = (VSContainer *) templateCnt->nextContainer();
			}

		}
		else {

			mergedCnt = (VSContainer *) templateCnt->duplicate(templateCnt->dad(), VS_DUP_ALL);
			if (! mergedCnt) {
				myStatus = VSPM_OUT_OF_MEMORY;
				break;
			}

		}

		/* Add the name value pair to the merged policy */
/*		nvpCntPtr = (VSContainer *) configCnt->searchContainer(VSPM_NVP_CONTAINER);
		if (nvpCntPtr) {
			nvpCntPtr = (VSContainer *) nvpCntPtr->duplicate(nvpCntPtr->dad(), VS_DUP_ONE);
			if (! nvpCntPtr) {
				myStatus = VSPM_OUT_OF_MEMORY;
				break;
			}

			mergedCnt->addContainer(nvpCntPtr);

		}
*/

	} while (0);

	*status = myStatus;

	if (myStatus != VSPM_STATUS_NO_ERROR) {
		
		if (mergedCnt) {
			delete mergedCnt;
			mergedCnt = NULL;
		}

	}

    return mergedCnt;

}

	
////////////////////////////////////////////////////////////////////
VSPM_STATUS invokeModuleCallBack(VSContainer *module, VSContainer *policy)
////////////////////////////////////////////////////////////////////
{
	VSPM_STATUS status = VSPM_STATUS_NO_ERROR;
	VSNvp *libItem = NULL;
	VSNvp *funcItem = NULL;
	char * libName = NULL;
	char * funcName = NULL;

#ifndef WIN32
	void *libHandle = NULL;
#else
	HINSTANCE libHandle = NULL;
#endif

	void (*callBackFunc)(VSPM_Container, VSPM_STATUS *) = NULL;

	do {

		libItem = (VSNvp *) module->searchItem(VSPM_LIBRARY_ITEM);
		if (! libItem) {
			status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		libName = (char *) libItem->value();
		if (! libName) {
			status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		funcItem = (VSNvp *) module->searchItem(VSPM_CALLBACK_FUNC_ITEM);
		if (! funcItem) {
			status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		funcName = (char *) funcItem->value();
		if (! funcName) {
			status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

#ifndef WIN32
		/* load and get a handle on the module library */
		libHandle = dlopen(libName, RTLD_LAZY);
		if (! libHandle) {
			fprintf(stderr, "dlopen failed: %s\n", dlerror());
			status = VSPM_CANNOT_OPEN_FILE;
			break;
		}

		/* obtain the call back func ptr */
		callBackFunc =
			(void (*)(VSPM_Container, VSPM_STATUS *)) dlsym(libHandle, funcName);
		if (! callBackFunc) {
			fprintf(stderr, "dlsym failed: %s\n", dlerror());
			status = VSPM_NOT_FOUND;
			break;
		}
#else
		libHandle = LoadLibrary(libName);

		if (! libHandle) {
			fprintf(stderr, "LoadLibrary failed: %x\n", GetLastError());
			status = VSPM_CANNOT_OPEN_FILE;
			break;
		}

		/* obtain the call back func ptr */
		callBackFunc =
			(void (*)(VSPM_Container, VSPM_STATUS *)) GetProcAddress(libHandle, funcName);
		if (! callBackFunc) {
			fprintf(stderr, "GetProcAddress failed: %x\n", GetLastError());
			status = VSPM_NOT_FOUND;
			break;
		}
#endif

		/* invoke the call back func */
		(*callBackFunc) ((VSPM_Container)policy, &status);


#ifndef WIN32
		/* remove the module library */
		if (dlclose(libHandle) != 0) {
			fprintf(stderr, "dlclose failed %s\n", dlerror());
			status = VSPM_INVALID_DESCRIPTOR;
			break;
		}
#else
		if (FreeLibrary(libHandle) == 0) {
			fprintf(stderr, "FreeLibrary failed %x\n", GetLastError());
			status = VSPM_INVALID_DESCRIPTOR;
			break;
		}
#endif
		libHandle = NULL;

	} while (0);


#ifndef WIN32
	if (libHandle)
		dlclose(libHandle);
#else
	if (libHandle)
		FreeLibrary(libHandle);
#endif


	return status;

}


////////////////////////////////////////////////////////////////////
void writePolicy(const char *outUrl, VSContainer *policyCnt, VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	FILE *outFp = NULL;
	char *protocol = NULL;
	char *host = NULL;
	char *port = NULL;
	char *res = NULL;
	VSContainer *policyCntPtr = NULL;
	int i = 0;
	int numCont = 0;

	do {

		if (! policyCnt) {
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		if (! outUrl) {
			*status = VSPM_INVALID_VALUE;
			break;
		}

		*status = parseUrl(outUrl, &protocol, &host, &port, &res);

		if (*status != VSPM_STATUS_NO_ERROR)
			break;

		if (NULL != protocol) {

			if (! strcmp(protocol, FILE_PROTOCOL)) {

				if (! res) {
					*status = VSPM_INVALID_URL;
					break;
				}
				
			}
			else {
				*status = VSPM_NOT_SUPPORTED_PROTOCOL;
				break;
			}
		}
					
		outFp = fopen(res, "w");
		if (outFp == NULL) {
			*status = VSPM_CANNOT_OPEN_FILE;
			break;
		}
				
		fprintf(outFp, "VSPM0101\n\n");

		numCont = policyCnt->countContainer();
		if (! numCont)
			break;

		policyCntPtr = (VSContainer *) policyCnt->firstContainer();
		policyCntPtr->print(outFp, 0, 0);
		for (i = 1; i < numCont; i++) {

			policyCntPtr = (VSContainer *) policyCnt->nextContainer();
			policyCntPtr->print(outFp, 0, 0);

		}


	} while (0);

	if (protocol)
		free(protocol);

	if (host)
		free(host);

	if (port)
		free(port);

	if (res)
		free(res);

	if (outFp)
		fclose(outFp);

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void VSPMSP_Close (VSPM_Descriptor pmd)
////////////////////////////////////////////////////////////////////
{
		VSContainer *root = (VSContainer *)pmd;
		if (root)
			delete root;

}



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



////////////////////////////////////////////////////////////////////
VSPM_EXPORT void VSPMSP_AddNVPToDescriptor ( VSPM_Descriptor cfd,
                                         const unsigned char * name,
                                         unsigned int nameLen, 
                                         const unsigned char * value,
                                         unsigned int valueLen, 
                                         VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSContainer *config = (VSContainer *) cfd;
	VSNvp *nvpItem = NULL;
	VSContainer *nvpCnt = NULL;

	do {

		*status = VSPM_STATUS_NO_ERROR;

		if (! config) {
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		nvpCnt = (VSContainer *) config->searchContainer(VSPM_NVP_CONTAINER);
		if (! nvpCnt) {
			nvpCnt = new VSContainer(config, VSPM_NVP_CONTAINER, strlen(VSPM_NVP_CONTAINER));
			if (! nvpCnt) {
				*status = VSPM_OUT_OF_MEMORY;
				break;
			}

			config->addContainer(nvpCnt);
		}

		nvpItem = new VSNvp(nvpCnt, (const char*)name, nameLen, value, valueLen);
		if (! nvpCnt) {
			*status = VSPM_OUT_OF_MEMORY;
			break;
		}

		nvpCnt->addItem(nvpItem);

	} while(0);
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void VSPMSP_GeneratePolicy ( VSPM_Descriptor cfd,
                                         const char * templateUrl,
                                         const char * policyUrl,
                                         const char * outUrl,
                                         VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *configCnt = (VSContainer *) cfd;
	VSContainer *templateCnt = NULL;
	VSContainer *policyCnt = NULL;
	VSContainer *mergedCnt = NULL;
	VSContainer *moduleCnt = NULL;
	VSContainer *moduleCntPtr = NULL;
	int moduleCount = 0;
	int i = 0;

	do {

		*status = VSPM_STATUS_NO_ERROR;

	/*	if (! configCnt) {
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}
	*/
		/* Open policy template */
		templateCnt = openPolicyTemplate(templateUrl, status);
		if (*status != VSPM_STATUS_NO_ERROR) {
			templateCnt = NULL;
			break;
		}

		/* Open custom policy */
		if (policyUrl) {
			policyCnt = openPolicy(policyUrl, status);
			if (*status != VSPM_STATUS_NO_ERROR) {
				policyCnt = NULL;
				*status = VSPM_STATUS_NO_ERROR;
			}
		}

		/* Merge the template with the custom policy */
		mergedCnt = mergePolicy(configCnt, templateCnt, policyCnt, status);
		if (*status != VSPM_STATUS_NO_ERROR) {
			mergedCnt = NULL;
			break;
		}

		/* For each module, open the library and invoke the call back */
/*		moduleCnt = (VSContainer *) configCnt->searchContainer(VSPM_MODULE_CONTAINER);
		if (moduleCnt) {

			moduleCount = moduleCnt->countContainer();

			for (i = 0; i < moduleCount; i++) {
				if (i) {
					moduleCntPtr = (VSContainer *) moduleCnt->nextContainer();
				}
				else {
					moduleCntPtr = (VSContainer *) moduleCnt->firstContainer();
				}

				if (! moduleCntPtr) {
					*status = VSPM_INVALID_DESCRIPTOR;
					break;
				}

				*status = invokeModuleCallBack(moduleCntPtr, mergedCnt);
				if (*status != VSPM_STATUS_NO_ERROR) 
					break;

			}

		}
*/

		UpdatePolicies(mergedCnt, status);

		/* Write out the policy to file */
		if (*status == VSPM_STATUS_NO_ERROR) {

			/* Remove the NVP container from the result */
			VSPMSP_DeleteContainerByName(mergedCnt, VSPM_NVP_CONTAINER, strlen(VSPM_NVP_CONTAINER), status);

			writePolicy(outUrl, mergedCnt, status);

		}

	} while (0);

	if (templateCnt) {
		delete templateCnt;
		templateCnt = NULL;
	}

	if (policyCnt)
		delete policyCnt;

	if (mergedCnt)
		delete mergedCnt;


}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Version
        VSPMSP_GetVersion (
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
VSPM_EXPORT void
        VSPMSP_SetVersion (
                VSPM_Container cnt,
				unsigned int maj,
				unsigned int min,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSContainer *container = (VSContainer *)cnt;

	VSPM_Version version = NULL;

	if (!container) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return;
	}

	container->setMajorVersion(maj);
	container->setMinorVersion(min);

	*status = VSPM_STATUS_NO_ERROR;
		
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT unsigned int
        VSPMSP_ContainerCount (
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
        VSPMSP_ItemCount (
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
        VSPMSP_GetContainerName (
                VSPM_Container cnt,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *container = (VSContainer *)cnt;
	unsigned char *name = NULL;
	unsigned char *retName = NULL;
	int len = 0;

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

		len = strlen((const char *)name);
		retName = (unsigned char *) malloc(len + 1);
		if (! retName) {

			*status = VSPM_OUT_OF_MEMORY;
		}
		else {

			memcpy(retName, name, len);
			retName[len] = '\0';

		}

	}

	return retName;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT unsigned int
        VSPMSP_GetContainerNameLength (
                VSPM_Container cnt,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *container = (VSContainer *)cnt;
	unsigned char *name = NULL;
	unsigned int retVal = 0;

	if (!container) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return 0;
	}

	*status = VSPM_STATUS_NO_ERROR;

	name = (unsigned char *)container->name();
	if (! name) {

		*status = VSPM_INVALID_DESCRIPTOR;

	}
	else {

		retVal = strlen((const char *)name);

	}

	return retVal;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void
        VSPMSP_SetContainerName (
                VSPM_Container cnt,
				const unsigned char * cntName,
				unsigned int cntNameLen,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *container = (VSContainer *)cnt;
	unsigned char *oldName = NULL;

	do {

		if (!container) {
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		oldName = (unsigned char *) container->name();
		if (! oldName) {
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		*status = VSPM_STATUS_NO_ERROR;

		if ((! cntName) || (0 == cntNameLen)) {

			*status = VSPM_INVALID_VALUE;
			break;

		}

		/* Short circuit this operation, because nothing is changed */
		if (!strcmp((const char *) oldName, (const char *) cntName))
			break;

		container->setName((const char *) cntName);
		oldName = (unsigned char *) container->name();

		/* if the value didn't change, something is wrong */
		if ((! oldName) || (!strcmp((const char *) oldName, (const char *) cntName))) {
			*status = VSPM_OUT_OF_MEMORY;
			break;
		}

	} while (0);

	return;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Container
        VSPMSP_GetContainerByName (
                VSPM_Container cnt,
                const char* name, 
				unsigned int nameLen,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *container = (VSContainer *)cnt;
	VSContainer *retCnt = NULL;
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

	if (container) {
		retCnt = container;
	}

	if (compStr)
		free(compStr);

	return (VSPM_Descriptor) retCnt;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void
        VSPMSP_DeleteContainerByName (
                VSPM_Container cnt,
                const char* name, 
				unsigned int nameLen,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *container = (VSContainer *)cnt;
	VSContainer *pContainer = container;
	char *subStr = NULL, *compStr = NULL, *tmpStr = NULL;
	int len = 0;

	if (! container) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return ;
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

	if (container) {
		pContainer->deleteContainer(container);
		container = NULL;
	}

	if (compStr)
		free(compStr);

	return;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Container
        VSPMSP_GetContainer (
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
		retCont = container;
	}

	return (VSPM_Container)retCont;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void
        VSPMSP_SetContainer (
                VSPM_Container cnt,
                unsigned int index, 
				VSPM_Container newCnt,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *parent = (VSContainer *)cnt;
	VSContainer *container = NULL;
	VSContainer *newContainer = (VSContainer *)newCnt;
	int i = 0;

	if (!parent) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return;
	}

	*status = VSPM_STATUS_NO_ERROR;

	if ((0 > index) || (parent->countContainer() <= index)) {
		*status = VSPM_INDEX_OUT_OF_RANGE;
		return;
	}
	
	parent->insertContainer(newContainer, index);
	parent->deleteContainerAt(index);

	return;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void
        VSPMSP_AddContainer (
                VSPM_Container cnt,
				VSPM_Container newCnt,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *parent = (VSContainer *)cnt;
	VSContainer *newContainer = (VSContainer *)newCnt;
	int i = 0;

	if (!parent) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return;
	}

	if (! newContainer) {
		*status = VSPM_INVALID_VALUE;
		return;
	}

	*status = VSPM_STATUS_NO_ERROR;

	parent->addContainer(newContainer);

	return;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void
        VSPMSP_DeleteContainer (
                VSPM_Container cnt,
                unsigned int index, 
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *parent = (VSContainer *)cnt;
	VSContainer *container = NULL;
	int i = 0;

	if (!parent) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return;
	}

	*status = VSPM_STATUS_NO_ERROR;

	if ((0 > index) || (parent->countContainer() <= index)) {
		*status = VSPM_INDEX_OUT_OF_RANGE;
		return;
	}
	
	parent->deleteContainerAt(index);

	return;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Item
        VSPMSP_GetItemByName (
                VSPM_Container cnt,
                const char* name, 
				unsigned int nameLen,
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
		retItem = item;
	}

	return (VSPM_Item)retItem;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void
        VSPMSP_SetItemByName (
                VSPM_Container cnt,
                const char* name, 
				unsigned int nameLen,
				VSPM_Item newItm,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *container = (VSContainer *)cnt;
	VSNvp *item = NULL;
	VSNvp *newItem = (VSNvp *)newItm;

	if (!container) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return;
	}

	if (! newItem) {
		*status = VSPM_INVALID_VALUE;
		return;
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
		container->deleteItem(item);
		container->addItem(newItem);
	}
	else {
		container->addItem(newItem);
	}

	return ;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Item
        VSPMSP_GetItem (
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
		retItem = item;
	}

	return (VSPM_Item)retItem;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void
        VSPMSP_SetItem (
                VSPM_Container cnt,
                unsigned int index, 
				VSPM_Item newItm,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *parent = (VSContainer *)cnt;
	VSNvp *newItem = (VSNvp *)newItm;
	int i = 0;

	if (!parent) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return;
	}

	if (! newItem) {
		*status = VSPM_INVALID_VALUE;
		return;
	}

	*status = VSPM_STATUS_NO_ERROR;

	if ((0 > index) || (parent->countContainer() <= index)) {
		*status = VSPM_INDEX_OUT_OF_RANGE;
		return;
	}
	
	parent->insertItem(newItem, index);
	parent->deleteItemAt(index);

	return;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void
        VSPMSP_AddItem (
                VSPM_Container cnt,
				VSPM_Item newItm,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *parent = (VSContainer *)cnt;
	VSNvp *newItem = (VSNvp *)newItm;
	int i = 0;

	if (!parent) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return;
	}

	if (! newItem) {
		*status = VSPM_INVALID_VALUE;
		return;
	}

	*status = VSPM_STATUS_NO_ERROR;

	parent->addItem(newItem);

	return;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void
        VSPMSP_DeleteItemByName (
                VSPM_Container cnt,
                const char* name, 
				unsigned int nameLen,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *container = (VSContainer *)cnt;
	VSNvp *item = NULL;

	if (!container) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return;
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
		container->deleteItem(item);
	}

	return ;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void
        VSPMSP_DeleteItem (
                VSPM_Container cnt,
                unsigned int index, 
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *parent = (VSContainer *)cnt;
	int i = 0;

	if (!parent) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return;
	}

	*status = VSPM_STATUS_NO_ERROR;

	if ((0 > index) || (parent->countContainer() <= index)) {
		*status = VSPM_INDEX_OUT_OF_RANGE;
		return;
	}
	
	parent->deleteItemAt(index);

	return;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT unsigned char *
        VSPMSP_GetName (
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
VSPM_EXPORT unsigned int
        VSPMSP_GetNameLength (
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
		return 0;
	}

	if ((name = (char *)item->name()) != NULL) {
		len = strlen(name);
	}
	else {
		*status = VSPM_NOT_FOUND;
	}
	
	return (unsigned int) len;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void
        VSPMSP_SetName (
                VSPM_Item itm,
				const unsigned char * name,
				unsigned int nameLen,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSNvp *item = (VSNvp *)itm;
	unsigned char * oldName = NULL;
	int len = 0;

	do {

		if (! item) {
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		oldName = (unsigned char *) item->name();

		*status = VSPM_STATUS_NO_ERROR;

		if ((! name) || (0 == nameLen)) {

			*status = VSPM_INVALID_VALUE;
			break;

		}

		/* Short circuit this operation, because nothing is changed */
		if (oldName && (!strcmp((const char *)oldName, (const char *)name)))
			break;

		item->setName((const char *)name);
		oldName = (unsigned char *) item->name();

		/* if the value didn't change, something is wrong */
		if ((! oldName) || (strcmp((const char *)oldName, (const char *)name) != 0)) {
			*status = VSPM_OUT_OF_MEMORY;
			break;
		}

	} while (0);
	
	return;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT unsigned char *
        VSPMSP_GetValue (
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
VSPM_EXPORT unsigned int
        VSPMSP_GetValueLength (
                VSPM_Item itm,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSNvp *item = (VSNvp *)itm;
	char *value = NULL;
	int len = 0;

	*status = VSPM_STATUS_NO_ERROR;

	if (!item) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return 0;
	}

	if ((value = (char *)item->value()) != NULL) {
		len = item->valueLen();
	}
	else {
		*status = VSPM_NOT_FOUND;
	}
	
	return (unsigned int) len;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT void
        VSPMSP_SetValue (
                VSPM_Item itm,
				const unsigned char * value,
				unsigned int valueLen,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{

	VSNvp *item = (VSNvp *)itm;
	unsigned char * oldValue = NULL;
	int len = 0;

	do {

		if (! item) {
			*status = VSPM_INVALID_DESCRIPTOR;
			break;
		}

		oldValue = (unsigned char *) item->value();

		*status = VSPM_STATUS_NO_ERROR;

		if ((! value) || (0 == valueLen)) {

			*status = VSPM_INVALID_VALUE;
			break;

		}

		/* Short circuit this operation, because nothing is changed */
		/* The old value can be null, thus short circuit it if it is null */
		if ( oldValue && (!strcmp((const char *)oldValue, (const char *)value)))
			break;

		item->setValue(value, valueLen);
		oldValue = NULL;
		oldValue = (unsigned char *) item->value();

		/* if the value didn't change, something is wrong */
		if ((! oldValue) || (strcmp((const char *)oldValue, (const char *)value) != 0)) {
			*status = VSPM_OUT_OF_MEMORY;
			break;
		}

	} while (0);
	
	return;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT unsigned char *
        VSPMSP_DescribeStatus (
                VSPM_Descriptor pmd,
                VSPM_STATUS status)
////////////////////////////////////////////////////////////////////
{
	return NULL;
}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Container
        VSPM_AllocContainer (
				VSPM_Container parent,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSContainer *container = NULL;

	if (! parent) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return NULL;
	}

	container = new VSContainer((VSNode *)parent, "untitled", strlen("untitled"));
	if (! container) {
		*status = VSPM_OUT_OF_MEMORY;
		return NULL;
	}

	*status = VSPM_STATUS_NO_ERROR;

	return (VSPM_Container) container;

}


////////////////////////////////////////////////////////////////////
VSPM_EXPORT VSPM_Item
        VSPM_AllocItem (
				VSPM_Container parent,
                VSPM_STATUS *status)
////////////////////////////////////////////////////////////////////
{
	VSNvp *item = NULL;

	if (! parent) {
		*status = VSPM_INVALID_DESCRIPTOR;
		return NULL;
	}

	item = new VSNvp((VSNode *)parent, "untitled", strlen("untitled"));
	if (! item) {
		*status = VSPM_OUT_OF_MEMORY;
		return NULL;
	}

	*status = VSPM_STATUS_NO_ERROR;

	return (VSPM_Item) item;
}

