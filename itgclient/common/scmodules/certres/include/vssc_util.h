#ifndef __VSSC_UTIL_H_
#define __VSSC_UTIL_H_

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#include <winldap.h>

enum VS_PROTOCOL { HTTP=1, VS_LDAP=2};

typedef struct ConfigFileInfo
{
	char		szName[256];
	char		szValue[256];
}ConfigFileInfo;

unsigned long GetAttributeValueBin(
					LDAP *ld,
					char *base,
					unsigned long scope,
					char *filter,
					char *attrs[],
					unsigned long attrsonly,
					unsigned char **pbAttribValue,
					unsigned int *cbAttribValue
					);

unsigned long GetAttributeValue(
					LDAP *ld,
					char *base,
					unsigned long scope,
					char *filter,
					char *attrs[],
					unsigned long attrsonly,
					char **szAttributeValue
					);

#endif //__VSSC_UTIL_H_