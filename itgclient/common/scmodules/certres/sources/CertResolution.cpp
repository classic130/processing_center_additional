#include "CertResolution.h"

// Global Variables
DIRINFO			g_dirInfo;



bool CertResolutionInit()
{
	//Read the values from CertRes.config and populate DIRINFO structure
	FILE *stream;
	ConfigFileInfo CfgInfo;

	if((stream = fopen(CERTRES_CONFIGFILE, "r")) != NULL)
	{	
		while(!feof(stream))
		{
			// BUG BUG - Fails to read properly when one of the values have a space
			// for ex cn=Recipients,ou=Ajay-Site,o=Verisign Inc,
			fscanf(stream, "%s	%s\n", CfgInfo.szName, CfgInfo.szValue);
			InitiliazeCertConfigInfo(CfgInfo.szName, CfgInfo.szValue);

		}
	}
	else
	{
		return false;
	}
	
	return true;

}

void InitiliazeCertConfigInfo(char *szName,
					  char *szValue)
{

	if(strcmp(szName,"PROTOCOL") == 0)
	{
		int nProtocol;
		nProtocol = atoi(szValue);
		g_dirInfo.eProtocol = (VS_PROTOCOL)nProtocol;
	}
	else if(strcmp(szName, "SERVERNAME") == 0)
	{
		g_dirInfo.szServerName = (char *)malloc(strlen(szValue) + 1);
		strcpy(g_dirInfo.szServerName, szValue);
	}
	else if(strcmp(szName, "ENDUSERBASEDN") == 0)
	{
		g_dirInfo.szEndUserBaseDN = (char *)malloc(strlen(szValue) + 1);
		strcpy(g_dirInfo.szEndUserBaseDN, szValue);
	}
	else if(strcmp(szName, "CABASEDN") == 0)
	{
		g_dirInfo.szCABaseDN = (char *)malloc(strlen(szValue) + 1);
		strcpy(g_dirInfo.szCABaseDN, szValue);
	}
	else if(strcmp(szName, "EMAILATTRIBUTE") == 0)
	{
		g_dirInfo.szEmailAttribute = (char *)malloc(strlen(szValue) + 1);
		strcpy(g_dirInfo.szEmailAttribute, szValue);
	}
	else if(strcmp(szName, "USERCERTATTRIBUTE") == 0)
	{
		g_dirInfo.szUserCertAttribute = (char *)malloc(strlen(szValue) + 1);
		strcpy(g_dirInfo.szUserCertAttribute, szValue);
	}
	else if(strcmp(szName, "ISSUERDNATTRIBUTE") == 0)
	{
		g_dirInfo.szIssuerDNAttribute = (char *)malloc(strlen(szValue) + 1);
		strcpy(g_dirInfo.szIssuerDNAttribute, szValue);
	}
	else if(strcmp(szName, "CACERTATTRIBUTE") == 0)
	{
		g_dirInfo.szCACertAttribute = (char *)malloc(strlen(szValue) + 1);
		strcpy(g_dirInfo.szCACertAttribute, szValue);
	}
	else if(strcmp(szName, "MYCERTATTRIBUTE") == 0)
	{
		g_dirInfo.szMyCertAttribute = (char *)malloc(strlen(szValue) + 1);
		strcpy(g_dirInfo.szMyCertAttribute, szValue);
	}

		
}


// This function returns the whole cert chain - this function will be called for signing operation.
// It is assumed that the userCertificate attributes contains the full chain

// This function returns the end user cert only (X.509). 
// The Ldap search for the Certificate can return one of the following
// 1) X.509
// 2) A Certs-only PKCS#7 wth only the X.509 certificate of end use
// 3) A certs-only PKCS#7 with X509 cert of end user along with X.509 certs
//    of all itermediate CAs. We will also assume that X.509 cert for the end-user
//    will be the fiers one in this PKCS#7

unsigned long MyCertResolution(char *szEmailAddress,
							  unsigned int *cbMyUserCertificate, unsigned char **pbMyUserCertificate)
{
	LDAP *ld = NULL;
	unsigned int dwError = 0;
	char *szMyUserCertificate = NULL;

	ld = ldap_open(g_dirInfo.szServerName, LDAP_PORT);

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

	attrs[0] = g_dirInfo.szMyCertAttribute;
	attrs[1] = NULL;

	char szFilter[256];
	sprintf(szFilter, "(%s=%s)", g_dirInfo.szEmailAttribute, szEmailAddress);

	unsigned char *pbMyUserCert = NULL;
	unsigned int cbMyUserCert = 0;

	dwError = GetAttributeValueBin(ld, g_dirInfo.szEndUserBaseDN, LDAP_SCOPE_SUBTREE ,
		szFilter, attrs, 0, &pbMyUserCert, &cbMyUserCert);

	if(cbMyUserCert==0)
		return dwError;

	//char *szMyUserCert = (char *)malloc( cbMyUserCert + 1);
	//memcpy(szMyUserCert, pbMyUserCert, cbMyUserCert);
	//szMyUserCert[cbMyUserCert] = '\0';

	//char *pbBytes  = NULL; //= (unsigned char *)malloc(cbMyUserCert/2);
	//int cbByte = 0;

	//Hascii2Bin(szMyUserCert, &pbBytes, &cbByte);


	// BUGBUG - Check if pbData is X509 if not process it before sending it back
	*pbMyUserCertificate = (unsigned char*)malloc(cbMyUserCert);
	memcpy(*pbMyUserCertificate, pbMyUserCert, cbMyUserCert);

	*cbMyUserCertificate = cbMyUserCert;
	
	//if(pbBytes)
	//	free(pbBytes);

	//if(szMyUserCert)
	//	free(szMyUserCert);

	if(pbMyUserCert)
		free(pbMyUserCert);

	return dwError;

}

// This function returns the complete cert chain - this function will be called for encryption operation.
// It is assumed that the userSMIMECertificate attributes contains the full chain

unsigned long UserCertResolution(char *szEmailAddress,
							  unsigned int *cbUserCertificate, unsigned char **pbUserCertificate)
{
	LDAP *ld = NULL;
	unsigned int dwError = 0;

	char *szUserCertificate = NULL;

	ld = ldap_open(g_dirInfo.szServerName, LDAP_PORT);


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

	attrs[0] = g_dirInfo.szUserCertAttribute;
	attrs[1] = NULL;

	char szFilter[256];
	sprintf(szFilter, "(%s=%s)", g_dirInfo.szEmailAttribute, szEmailAddress);

	unsigned char *pbUserCert = NULL;
	unsigned int cbUserCert = 0;

	dwError = GetAttributeValueBin(ld, g_dirInfo.szEndUserBaseDN, LDAP_SCOPE_SUBTREE ,
		szFilter, attrs, 0, &pbUserCert, &cbUserCert);

	if(cbUserCert==0)
		return dwError;

	//char *szUserCert = (char *)malloc( cbUserCert + 1);
	//memcpy(szUserCert, pbUserCert, cbUserCert);
	//szUserCert[cbUserCert] = '\0';

	//char *pbBytes = NULL; // = (unsigned char *)malloc(cbUserCert/2);
	//int cbByte = 0;


    //Hascii2Bin(szUserCert, &pbBytes, &cbByte);

	//*cbUserCertificate = cbByte;

 
	*pbUserCertificate = (unsigned char*)malloc(cbUserCert);
	memcpy(*pbUserCertificate, pbUserCert, cbUserCert);
	*cbUserCertificate = cbUserCert;

	//if(pbBytes)
	//	free(pbBytes);

	//if(szUserCert)
	//	free(szUserCert);

	if(pbUserCert)
		free(pbUserCert);

	return dwError;

}

int Hascii2Bin(char *hasc,
			   char **OutBuf,
			   int *OutLen)
{
	int status = 0;
	PCHAR data;
	unsigned int i = 0;
	int binNum;

	do {
		*OutLen = (unsigned int)(strlen(hasc)+1)/2;
		if (*OutLen > 0) {
			data = (char *) malloc (*OutLen);
			memset(data, 0, *OutLen);
			if (data != NULL) {
				while ((int)i < *OutLen) {
					status = sscanf (&hasc[2 * i], "%2x", &binNum);
					data[i] = (char)binNum;
					i++;
				}

			} else {
				*OutLen = 0;
			}
		} else {
				*OutBuf = NULL;
		}

	} while (0);
  *OutBuf = data;
  return(status);
}
