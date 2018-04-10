#include "emailresolution.h"

EMAILDIRINFO	g_emailInfo;



bool EmailResolutionInit()
{
	//Read the values from EmailRes.config and populate DIRINFO structure
	FILE *stream;
	ConfigFileInfo CfgInfo;

	if((stream = fopen(EMAILRES_CONFIGFILE, "r")) != NULL)
	{	
		while(!feof(stream))
		{
			// BUG BUG - Fails to read properly when one of the values have a space
			// for ex cn=Recipients,ou=Ajay-Site,o=Verisign Inc,
			fscanf(stream, "%s	%s\n", CfgInfo.szName, CfgInfo.szValue);
			InitiliazeEmailConfigInfo(CfgInfo.szName, CfgInfo.szValue);

		}
	}
	else
	{
		return false;
	}
	
	return true;

}	

void InitiliazeEmailConfigInfo(char *szName,
					  char *szValue)
{
	if(strcmp(szName,"PROTOCOL") == 0)
	{
		int nProtocol;
		nProtocol = atoi(szValue);
		g_emailInfo.eProtocol = (VS_PROTOCOL)nProtocol;
	}
	else if(strcmp(szName, "SERVERNAME") == 0)
	{
		g_emailInfo.szServerName = (char *)malloc(strlen(szValue) + 1);
		strcpy(g_emailInfo.szServerName, szValue);
	}
	else if(strcmp(szName, "EMAILBASEDN") == 0)
	{
		g_emailInfo.szEmailBaseDn = (char *)malloc(strlen(szValue) + 1);
		strcpy(g_emailInfo.szEmailBaseDn, szValue);
	}
	else if(strcmp(szName, "EMAILATTRIBUTE") == 0)
	{
		g_emailInfo.szEmailAttribute = (char *)malloc(strlen(szValue) + 1);
		strcpy(g_emailInfo.szEmailAttribute, szValue);
	}
}

unsigned long EmailResolution(char *szSearchName,
							 char **szEmailAddress)
{
	LDAP *ld = NULL;
	unsigned int dwError = 0;

	ld = ldap_open(g_emailInfo.szServerName, LDAP_PORT);

	if(ld == NULL)
	{
		dwError = GetLastError();
		//printf("Call to ldap_open failed: error = %8x", dwError);
		return dwError;
	}

	dwError =  ldap_simple_bind_s(	ld,
									NULL,
									NULL);

	
//	dwError = ldap_bind_s( ld, NULL, NULL, LDAP_AUTH_NTLM );
	if(dwError != LDAP_SUCCESS)
	{	
		dwError = GetLastError();
		//printf("Call to ldap_simple_bind_s failed: error = 0x%x\n ", dwError);
		return dwError;
	}

	char *attrs[2];

	attrs[0] = g_emailInfo.szEmailAttribute;
	attrs[1] = NULL;

	char szFilter[256];
	sprintf(szFilter, "(cn=%s)", szSearchName);

	// Search for Full Name first
	//dwError = GetAttributeValue(ld, "cn=Recipients,ou=Ajay-Site,o=Verisign", LDAP_SCOPE_SUBTREE , "(cn=Ajay Jayaram)", attrs, 0, szEmailAddress);
	dwError = GetAttributeValue(ld, g_emailInfo.szEmailBaseDn, LDAP_SCOPE_SUBTREE , szFilter, attrs, 0, szEmailAddress);

	// If Full Name not found search for NickName (uid)
	if(dwError != 0)
	{
		sprintf(szFilter, "(uid=%s)", szSearchName);
		dwError = GetAttributeValue(ld, g_emailInfo.szEmailBaseDn, LDAP_SCOPE_SUBTREE , szFilter, attrs, 0, szEmailAddress);

		// If uid or alias not found search for email attribute
		if(dwError != 0)
		{
			sprintf(szFilter, "(%s=%s)", g_emailInfo.szEmailAttribute, szSearchName);
			dwError = GetAttributeValue(ld, g_emailInfo.szEmailBaseDn, LDAP_SCOPE_SUBTREE , szFilter, attrs, 0, szEmailAddress);
		}

		if(dwError != 0)
		{
			return dwError;
		}
	}

	return dwError;

	
}
