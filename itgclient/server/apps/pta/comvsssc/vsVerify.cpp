// vsVerify.cpp : Implementation of CvsVerify
/******************************************************************************
**
** vsVerify.cpp
**
** Implementation for CvsVerify class, which is a COM wrapper for 
** Signature Verification Library
**
** Authors:
** Bin Zou (bzou@verisign.com)
** Siddharth Bajaj (sbajaj@verisign.com)
**
** Last Modified : 10/02/01
*******************************************************************************/

#include "stdio.h"
#include "stdarg.h"
#include "stdafx.h"
#include "Comvsssc.h"
#include "vsVerify.h"
#include "ssc_api.h"
#include <comdef.h>
#define MAX_BUF_LENGTH 2048
#define ERROR_COM_SAFEARRAY_ACCESS_DATA 1
#define ERROR_COM_DATA_ERROR 2

/* Global variables */
FILE * globalLogFP;

/* Function declarations */
int InitializeFromConfigFile (const char *configFileName, void (*logFn)(char *fmt, ...), int *nCheckCrl);
int comvsscErrorString(char *errorString, DWORD errorCode);
int Bytes2SafeArrayVariant(unsigned char* pdata, int len, VARIANT* data);
int Strings2SafeArrayVariant(char** pdata, int len, VARIANT* data);
int SafeArrayVariant2Bytes(VARIANT* data, int len, unsigned char* pdata);
void vsLogInfoMessage(char *fmt, ...);
void LogEvent(LPCTSTR pFormat, ...);



/////////////////////////////////////////////////////////////////////////////
// CvsVerify


CvsVerify::CvsVerify()
{
    HKEY hkey = 0, *phkey = 0;
	BYTE logFileName[_MAX_PATH], configFileName[_MAX_PATH];
	DWORD type = 0;
	DWORD valueLen = _MAX_PATH;
	VSVAL_UserCtx userCtx = {0};

	/* TODO If Initialize failed how do we handle that? */
	

	do {
		m_nInitStatus = 0;
		strcpy ((char*)logFileName, "");
		strcpy ((char*)configFileName, "");
		/* Read ISAPI options from registry. */
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, COMVSSSC_REGISTRY_KEY, 0,
						 KEY_READ, &hkey)!=ERROR_SUCCESS) {
		  m_nInitStatus = VSVERIFY_ERROR_REGISTRY;
		  break;
		}
		phkey = &hkey;
		valueLen = _MAX_PATH;
		if (RegQueryValueEx(*phkey, "comvsssc-log-name",  0, &type, (unsigned char*)logFileName, 
							&valueLen)==ERROR_SUCCESS && type==REG_SZ) {
			//open the file etc.
			globalLogFP = 0;
	   		globalLogFP = fopen((const char*)logFileName, "a");
		}

		valueLen = _MAX_PATH;
		if (RegQueryValueEx(*phkey, "comvsssc-cfg-name",  0, &type, (unsigned char*)configFileName, 
							&valueLen)==ERROR_SUCCESS && type==REG_SZ) {

			if (globalLogFP==0)
				m_nInitStatus = InitializeFromConfigFile ((const char*)configFileName, 0, &m_nCrlCheck);
			else
				m_nInitStatus = InitializeFromConfigFile ((const char*)configFileName, vsLogInfoMessage, &m_nCrlCheck);
			if (m_nInitStatus) break;
		}		
		else {
			m_nInitStatus = VSVERIFY_ERROR_REGISTRY;
			break;
		}

		m_nInitStatus = VSVAL_Init (&m_valSdk, &userCtx, VAL_SDK_CURRENT_VERSION);
		if (m_nInitStatus) break;

	} while (0);

	if (m_nInitStatus != 0) {		
		if (m_nInitStatus == VSVERIFY_ERROR_REGISTRY) {
			LogEvent("\r\nThere was an error in initializing the comvsssc control. \
			      You need to run the loadreg.exe program before you start the \
				  comvsssc service. \r\nError code %d(0x%x)", m_nInitStatus, m_nInitStatus);
		} else {
			LogEvent("\r\nThere was an error in initializing the comvsssc control. \
			      \r\nConfig file - %s. \r\nLog file - %s. \r\nThe error code is %d (0x%x)",\
				  configFileName, logFileName, m_nInitStatus, m_nInitStatus);
		}
	}
	return;
}


CvsVerify::~CvsVerify(){
	if (globalLogFP) {
	   fclose (globalLogFP);
	   globalLogFP = 0;
	}
	VSVAL_Final (m_valSdk);
}


STDMETHODIMP CvsVerify::vPKIGetB64RevocationStatus(BSTR b64Cert, 
												   VARIANT *certStatus, 
												   VARIANT *userName, 
												   int *retCode)
{

	char* pUserName  = NULL ; 	
	unsigned char* pcert;
	long mCertLen = 0;
	int mCertStatus = 0;
	*retCode =0;


	if (m_nInitStatus != 0) {
		return GetErrDescription(m_nInitStatus);
	}

	try {
		do {
			_bstr_t	 tbstrTemp;
			_bstr_t  bstr64Cert(b64Cert) ;
			char* pb64Cert = (char*) (bstr64Cert) ;

			//call SCC_API
			*retCode = vsPKIUnBase64Alloc( &pcert , (int *) &mCertLen , pb64Cert);		
			if(*retCode) {
				*retCode = VSVERIFY_ERROR_B64DECODE;
				break;
			}

			*retCode = vsPKIGetRevocationStatus ( (unsigned char*) pcert , 
													mCertLen , 
													&mCertStatus, 
													&pUserName);
			if(*retCode)
				break;

			*certStatus = _variant_t((long) mCertStatus); 
			tbstrTemp = (char*)pUserName;
			_variant_t var_username((char*) tbstrTemp);
			::VariantCopy(userName, &var_username);

		} while(0);

		vsPKIFree(pUserName);
		vsPKIFree(pcert);

		if (*retCode)
			return GetErrDescription(*retCode);
	}
	
	catch(_com_error e)
	{	
		return Error((BSTR)e.Description());
	}
	return S_OK;
}



STDMETHODIMP CvsVerify::vPKIParseB64PKCS7(/*[in]*/ BSTR b64Pkcs7, 
										  /*[out]*/ VARIANT*  hash , 
										  /*[out]*/ VARIANT* hashLen, 
										  /*[out]*/ VARIANT* outAlgorithm , 
										  /*[out]*/ VARIANT* b64Cert, 
										  /*[out]*/ VARIANT* certStatus , 
										  /*[out,retval]*/ int* retCode)
{

	unsigned char* phash = new unsigned char[64];
	unsigned char *ppkcs7;
	char *pb64Cert = NULL;
	long pkcs7Len;
	int  mHashLen,  mOutAlgorithm, mCertLen, mCertStatus;
	char* pcert ;
	*retCode = 0;


	if (m_nInitStatus != 0) {
		return GetErrDescription(m_nInitStatus);
	}

	try{
		do 
		{

			_bstr_t	 tbstrTemp;

			_bstr_t  bstr64Pkcs7(b64Pkcs7) ;
			char* pb64Pkcs7 = (char*) (bstr64Pkcs7) ;

			//call SCC_API
			*retCode = vsPKIUnBase64Alloc( &ppkcs7 , (int *) &pkcs7Len , pb64Pkcs7);		
			if(*retCode) {
				*retCode = VSVERIFY_ERROR_B64DECODE;
				break;
			}

			//call SSC_API            
			if (m_nCrlCheck == 0) {
				*retCode = vsPKIParsePKCS7((unsigned char*)  ppkcs7 , 
											pkcs7Len, 
											phash , 
											&mHashLen , 
											&mOutAlgorithm, 
											(unsigned char**) &pcert , 
											&mCertLen , 
											0);
				mCertStatus = CS_REVOCATION_UNKNOWN;
			}
			else
				*retCode = vsPKIParsePKCS7((unsigned char*)  ppkcs7 , 
											pkcs7Len, 
											phash , 
											&mHashLen , 
											&mOutAlgorithm, 
											(unsigned char**) &pcert, 
											&mCertLen , 
											&mCertStatus);

			if(*retCode)
				break;

			*hashLen = _variant_t((long) mHashLen);
			*outAlgorithm = _variant_t((long) mOutAlgorithm);
			*certStatus = _variant_t((long) mCertStatus);

			*retCode = vsPKIBase64Alloc((char**) &pb64Cert, 
										(unsigned char*)pcert, 
										mCertLen);
			if(*retCode)
				break;
			
			tbstrTemp = pb64Cert;
			_variant_t var_cert((char*)tbstrTemp);
			::VariantCopy(b64Cert, &var_cert);

			if((*retCode =Bytes2SafeArrayVariant(phash,mHashLen, hash))) {
				break;
			}			
			
		}while (0);
		vsPKIFree(pb64Cert);
		vsPKIFree(ppkcs7);
		vsPKIFree(pcert);

		if (*retCode)
			return GetErrDescription(*retCode);

	}
	catch(_com_error e)
	{	
		return Error((BSTR)e.Description());
	}
	return S_OK;
}




STDMETHODIMP CvsVerify::vPKICompareMsgHash(BSTR msg, 
										   int msgLen, 
										   int outAlgorithm, 
										   VARIANT *hash, 
										   int hashLen, 
										   int *retCode)
{
	unsigned char* phash;
	
	*retCode = 0;
	if (m_nInitStatus != 0) {
		return GetErrDescription(m_nInitStatus);
	}

	try{
		do
		{
			char* pmsg = _bstr_t(msg) ;

			phash = (unsigned char*) malloc(hashLen+1);
			if(*retCode = SafeArrayVariant2Bytes(hash,hashLen,phash)) {
				return S_OK;
			}

			*retCode = vsPKICompareMsgHash((unsigned char*) pmsg, 
											msgLen, 
											outAlgorithm, 
											(unsigned char*) phash, 
											hashLen ) ;
		} while (0);

		if(*retCode) 
			return GetErrDescription(*retCode);
	}
	catch(_com_error e)
	{	
		return Error((BSTR)e.Description());
	}

	return S_OK;
}




STDMETHODIMP CvsVerify::vPKIVerifyB64PKCS7(/*[in]*/ BSTR b64Pkcs7, 
										   /*[in]*/ BSTR msg,  
										   /*[in]*/ int msgLen,  
										   /*[out]*/ VARIANT* hash,  
										   /*[out]*/ VARIANT* hashLen,  
										   /*[out]*/ VARIANT* outAlgorithm, 
										   /*[out]*/ VARIANT* b64Cert, 
										   /*[out]*/ VARIANT* certStatus, 
										   /*[out,retval]*/ int* retCode)
{
	unsigned char* phash = new unsigned char[64];
	unsigned char *ppkcs7, *pb64Cert=NULL;
	long pkcs7Len=0;
	char * mMsg;	
	int  mHashLen,  mOutAlgorithm, mCertLen, mCertStatus;
	char* pcert;

	*retCode=0;
	if (m_nInitStatus != 0) {
		return GetErrDescription(m_nInitStatus);
	} 

	try 
	{
		do 
		{
			_bstr_t bstrMsg(msg);
			mMsg = ( char*) bstrMsg;


			_bstr_t  bstr64Pkcs7(b64Pkcs7) ;
			char* pb64Pkcs7 = (char*) (bstr64Pkcs7) ;

			*retCode = vsPKIUnBase64Alloc( &ppkcs7, (int *) &pkcs7Len, pb64Pkcs7);		
			if(*retCode) {
				*retCode = VSVERIFY_ERROR_B64DECODE;
				break;
			}

			//call SSC_API
			if (m_nCrlCheck == 0) {
				*retCode = vsPKIVerifyPKCS7((unsigned char*)  ppkcs7 , pkcs7Len, 
										(unsigned char*) mMsg,msgLen,
										phash , &mHashLen , &mOutAlgorithm, 
										(unsigned char**) &pcert , &mCertLen , 0);
				mCertStatus = CS_REVOCATION_UNKNOWN;
			} else {
				*retCode = vsPKIVerifyPKCS7((unsigned char*)  ppkcs7 , pkcs7Len, 
										(unsigned char*) mMsg,msgLen,
										phash , &mHashLen , &mOutAlgorithm, 
										(unsigned char**) &pcert , &mCertLen , &mCertStatus);
			}
			if(*retCode)
				break;

			*hashLen = _variant_t((long) mHashLen);
			*outAlgorithm = _variant_t((long) mOutAlgorithm);
			*certStatus = _variant_t((long) mCertStatus);
			if((*retCode =Bytes2SafeArrayVariant(phash,mHashLen, hash))) {
				break;
			}
			*retCode = vsPKIBase64Alloc((char**) &pb64Cert, (unsigned char*)pcert, mCertLen);
			if(*retCode) 
				break;

			*b64Cert = _variant_t((char*) pb64Cert);

		} while (0);

		vsPKIFree(pb64Cert);
		vsPKIFree(ppkcs7);
		vsPKIFree(pcert);

		if(*retCode) {
			return GetErrDescription(*retCode);
		}

	}
	catch(_com_error e)
	{	
			return S_OK;
	}
	return S_OK;
}



STDMETHODIMP CvsVerify::vPKIBase64Alloc(VARIANT *b64String, 
										VARIANT *data, 
										int len, 
										int *retCode)
{
	unsigned char *pdata;
	char *pb64String;

	*retCode=0;
	if (m_nInitStatus != 0) {
		return GetErrDescription(m_nInitStatus);
	} 

	try
	{
		do 
		{
			_bstr_t		tbstrTemp;
			
			pdata = (unsigned char*) malloc(len+1);
			*retCode = SafeArrayVariant2Bytes(data,len, pdata);
			if(*retCode) 
				break;
 
			//call SSC_API
			*retCode = vsPKIBase64Alloc((char**) &pb64String, pdata, len);
			if(*retCode) 
				break;

			tbstrTemp = (char*)pb64String;
			_variant_t var_b64((char*)tbstrTemp);
			::VariantCopy(b64String, &var_b64);

		} while (0);
		vsPKIFree(pb64String);
		free(pdata);

		if (*retCode)
			return GetErrDescription(*retCode);
	}
	catch(_com_error e)
	{	
		return Error((BSTR)e.Description());
	}

	return S_OK;
}



STDMETHODIMP CvsVerify::vPKIUnBase64Alloc(VARIANT *data, 
										  VARIANT *len, 
										  BSTR b64String, 
										  int *retCode)
{

	unsigned char* pdata = NULL;
	unsigned char* b64pdata = NULL;
	long mLen = 0;

	*retCode = 0;
	if (m_nInitStatus != 0) {
		return GetErrDescription(m_nInitStatus);
	}

	try
	{
		do 
		{
			if (!data)
			{
				*retCode = ERROR_COM_DATA_ERROR; 
				return S_OK;
			}
        
			_bstr_t  bstr64String(b64String) ;
			char* pb64String = (char*) (bstr64String) ;

			//call SCC_API
			*retCode = vsPKIUnBase64Alloc( &pdata , (int *) &mLen , pb64String);  
			if(*retCode)
				break;
			
			//the lenght of the data
			*len = _variant_t((long) mLen);
			if(!(*retCode = Bytes2SafeArrayVariant(pdata, (int) mLen, data))) {
				break;
			}
		} while (0);

		vsPKIFree(pdata);
		if(*retCode)
			return GetErrDescription(*retCode);
	}
	catch(_com_error e)
	{	
		/* LogEvent("exception vPKIUnBase64Alloc:%s", e.Description());*/
		return Error((BSTR)e.Description());
	}

	return S_OK;
}



STDMETHODIMP CvsVerify::vPKIParseB64Cert(/*[in]*/ BSTR b64Cert, 
										  /*[out]*/ VARIANT* emailAddress, 
										  /*[out]*/ VARIANT* commonName, 
										  /*[out]*/ VARIANT* title, 
										  /*[out]*/ VARIANT* uniqueID, 
										  /*[out]*/ VARIANT* address, 
										  /*[out]*/ VARIANT* organization, 
										  /*[out]*/ VARIANT* organizationUnits, 
										  /*[out]*/ VARIANT* orgUnitCount, 
										  /*[out]*/ VARIANT* issuerOrganization, 
										  /*[out]*/ VARIANT* issuerLocality, 
										  /*[out]*/ VARIANT* issuerCountry, 
										  /*[out]*/ VARIANT* issuerCommonName, 
										  /*[out]*/ VARIANT* issuerOrganizationUnits, 
										  /*[out]*/ VARIANT* issuerOrgUnitCount, 
										  /*[out]*/ VARIANT* notBefore, 
										  /*[out]*/ VARIANT* notAfter, 
										  /*[out,retval]*/ int* retCode)
{
	VS_SSC_CertFields *certFields;

	*retCode = 0;
	if (m_nInitStatus != 0) {
		return GetErrDescription(m_nInitStatus);
	}

	try{
		do 
		{
			_bstr_t		tbstrTemp;
        
			_bstr_t  bstr64Cert(b64Cert) ;
			char* pb64String = (char*) (bstr64Cert) ;		

			//call SCC_API
			*retCode = vsPKIParseB64Cert(&certFields, pb64String);
			if(*retCode)
				break;

			if (certFields->emailAddress)
			{
				tbstrTemp = (char*) certFields->emailAddress;
				_variant_t var_emailaddress((char*) tbstrTemp);
				::VariantCopy (emailAddress , &var_emailaddress);
			}

			
			if (certFields->commonName)
			{
				tbstrTemp =	(char*) certFields->commonName;
				_variant_t var_cn((char*) tbstrTemp);
				::VariantCopy (commonName, &var_cn);
			}

			if (certFields->uniqueID) {
				tbstrTemp = (char*)certFields->uniqueID;
				_variant_t var_uniq((char*) tbstrTemp);
				::VariantCopy(uniqueID, &var_uniq);
			}

			if (certFields->title)
			{
				tbstrTemp = (char*)certFields->title;
				_variant_t var_title((char*) tbstrTemp);
				::VariantCopy(title, &var_title);
			}


			if (certFields->address)
			{
				tbstrTemp = certFields->address;
				_variant_t var_address((char*) tbstrTemp);
				::VariantCopy(address, &var_address);
			}

			if (certFields->organization)
			{
				tbstrTemp = certFields->organization;
				_variant_t var_org((char*) tbstrTemp);
				::VariantCopy(organization, &var_org);
			}

			_variant_t var_oucount((long) certFields->orgUnitCount);
			::VariantCopy(orgUnitCount, &var_oucount);


			if (certFields->orgUnitCount > 0 && certFields->organizationUnits) {
				Strings2SafeArrayVariant(certFields->organizationUnits, 
										 certFields->orgUnitCount, 
										 organizationUnits);
			}
			
			if (certFields->issuerOrganization) 
			{
				tbstrTemp = certFields->issuerOrganization;
				_variant_t var_issorg((char*) tbstrTemp);
				::VariantCopy(issuerOrganization, &var_issorg);
			}

			if (certFields->issuerLocality) 
			{
				tbstrTemp = certFields->issuerLocality;
				_variant_t var_issloc((char*) tbstrTemp);
				::VariantCopy(issuerLocality, &var_issloc);
			}

			if (certFields->issuerCountry) 
			{
				tbstrTemp = certFields->issuerCountry;
				_variant_t var_isscountry((char*) tbstrTemp);
				::VariantCopy(issuerCountry, &var_isscountry);
			}

			if (certFields->issuerCommonName) {
				tbstrTemp = certFields->issuerCommonName;
				_variant_t var_isscn((char*) tbstrTemp);
				::VariantCopy(issuerCommonName, &var_isscn);
			}

			_variant_t var_issoucount((long) certFields->issuerOrgUnitCount);
			::VariantCopy(issuerOrgUnitCount, &var_issoucount);


			if (certFields->issuerOrgUnitCount > 0 && certFields->issuerOrganizationUnits) {
				Strings2SafeArrayVariant(certFields->issuerOrganizationUnits, 
										 certFields->issuerOrgUnitCount, 
										 issuerOrganizationUnits);
			}

			if (certFields->notAfter) {
				tbstrTemp = certFields->notAfter;
				_variant_t var_notafter((char*) tbstrTemp);
				::VariantCopy(notAfter, &var_notafter);
			}

			if (certFields->notBefore) {
				tbstrTemp = certFields->notBefore;
				_variant_t var_notbefore((char*) tbstrTemp);
				::VariantCopy(notBefore, &var_notbefore);
			}

			vsPKIFreeCertFields (certFields);
		} while (0);

		if (*retCode)
			return GetErrDescription(*retCode);

	}
	catch(_com_error e)
	{	
		/*LogEvent("exception vPKIParseB64Cert:%s", e.Description());*/
		return Error((BSTR)e.Description());
	}

	return S_OK;

}


/*
	This methods parses v3Extensions such as Key Usage, Enhanced Key Usage, 
	Subject Alt Name, CDP.
*/
STDMETHODIMP CvsVerify::vPKIParseB64CertEx(/*[in]*/ BSTR b64Cert, 
										  /*[out]*/ VARIANT* emailAddress, 
										  /*[out]*/ VARIANT* commonName, 
										  /*[out]*/ VARIANT* title, 
										  /*[out]*/ VARIANT* uniqueID, 
										  /*[out]*/ VARIANT* address, 
										  /*[out]*/ VARIANT* organization, 
										  /*[out]*/ VARIANT* organizationUnits, 
										  /*[out]*/ VARIANT* orgUnitCount, 
										  /*[out]*/ VARIANT* issuerOrganization, 
										  /*[out]*/ VARIANT* issuerLocality, 
										  /*[out]*/ VARIANT* issuerCountry, 
										  /*[out]*/ VARIANT* issuerCommonName, 
										  /*[out]*/ VARIANT* issuerOrganizationUnits, 
										  /*[out]*/ VARIANT* issuerOrgUnitCount, 
										  /*[out]*/ VARIANT* notBefore, 
										  /*[out]*/ VARIANT* notAfter, 
										  /*[out]*/ VARIANT* keyUsage, 
										  /*[out]*/ VARIANT* extendedKeyUsage, 
										  /*[out]*/ VARIANT* sanDirectoryNames, 
										  /*[out]*/ VARIANT* sanDirectoryNameCount, 
										  /*[out]*/ VARIANT* sanRFC822Names, 
										  /*[out]*/ VARIANT* sanRFC822NameCount, 
										  /*[out]*/ VARIANT* sanDNSNames, 
										  /*[out]*/ VARIANT* sanDNSNameCount, 
										  /*[out]*/ VARIANT* sanURIs, 
										  /*[out]*/ VARIANT* sanURICount, 
										  /*[out]*/ VARIANT* sanUPNs, 
										  /*[out]*/ VARIANT* sanUPNCount, 
										  /*[out]*/ VARIANT* sanGUIDs, 
										  /*[out]*/ VARIANT* sanGUIDCount, 
										  /*[out]*/ VARIANT* cdpDpnDirectoryNames, 
										  /*[out]*/ VARIANT* cdpDpnDirectoryNameCount, 
										  /*[out]*/ VARIANT* cdpDpnRFC822Names, 
										  /*[out]*/ VARIANT* cdpDpnRFC822NameCount, 
										  /*[out]*/ VARIANT* cdpDpnDNSNames, 
										  /*[out]*/ VARIANT* cdpDpnDNSNameCount, 
										  /*[out]*/ VARIANT* cdpDpnURIs, 
										  /*[out]*/ VARIANT* cdpDpnURICount, 
										  /*[out]*/ VARIANT* cdpDpnUPNs, 
										  /*[out]*/ VARIANT* cdpDpnUPNCount, 
										  /*[out]*/ VARIANT* cdpDpnGUIDs, 
										  /*[out]*/ VARIANT* cdpDpnGUIDCount, 
										  /*[out]*/ VARIANT* cdpCrlIssuerDirectoryNames, 
										  /*[out]*/ VARIANT* cdpCrlIssuerDirectoryNameCount, 
										  /*[out]*/ VARIANT* cdpCrlIssuerRFC822Names, 
										  /*[out]*/ VARIANT* cdpCrlIssuerRFC822NameCount, 
										  /*[out]*/ VARIANT* cdpCrlIssuerDNSNames, 
										  /*[out]*/ VARIANT* cdpCrlIssuerDNSNameCount, 
										  /*[out]*/ VARIANT* cdpCrlIssuerURIs, 
										  /*[out]*/ VARIANT* cdpCrlIssuerURICount, 
										  /*[out]*/ VARIANT* cdpCrlIssuerUPNs, 
										  /*[out]*/ VARIANT* cdpCrlIssuerUPNCount, 
										  /*[out]*/ VARIANT* cdpCrlIssuerGUIDs, 
										  /*[out]*/ VARIANT* cdpCrlIssuerGUIDCount, 
										  /*[out,retval]*/ int* retCode)
{
	VS_SSC_CertFields *certFields;

	*retCode = 0;
	if (m_nInitStatus != 0) {
		return GetErrDescription(m_nInitStatus);
	}

	try{
		do 
		{
			_bstr_t		tbstrTemp;
        
			_bstr_t  bstr64Cert(b64Cert) ;
			char* pb64String = (char*) (bstr64Cert) ;		

			//call SCC_API
			*retCode = vsPKIParseB64Cert(&certFields, pb64String);
			if(*retCode)
				break;

			if (certFields->emailAddress)
			{
				tbstrTemp = (char*) certFields->emailAddress;
				_variant_t var_emailaddress((char*) tbstrTemp);
				::VariantCopy (emailAddress , &var_emailaddress);
			}

			
			if (certFields->commonName)
			{
				tbstrTemp =	(char*) certFields->commonName;
				_variant_t var_cn((char*) tbstrTemp);
				::VariantCopy (commonName, &var_cn);
			}

			if (certFields->uniqueID) {
				tbstrTemp = (char*)certFields->uniqueID;
				_variant_t var_uniq((char*) tbstrTemp);
				::VariantCopy(uniqueID, &var_uniq);
			}

			if (certFields->title)
			{
				tbstrTemp = (char*)certFields->title;
				_variant_t var_title((char*) tbstrTemp);
				::VariantCopy(title, &var_title);
			}


			if (certFields->address)
			{
				tbstrTemp = certFields->address;
				_variant_t var_address((char*) tbstrTemp);
				::VariantCopy(address, &var_address);
			}

			if (certFields->organization)
			{
				tbstrTemp = certFields->organization;
				_variant_t var_org((char*) tbstrTemp);
				::VariantCopy(organization, &var_org);
			}

			_variant_t var_oucount((long) certFields->orgUnitCount);
			::VariantCopy(orgUnitCount, &var_oucount);


			if (certFields->orgUnitCount > 0 && certFields->organizationUnits) {
				Strings2SafeArrayVariant(certFields->organizationUnits, 
										 certFields->orgUnitCount, 
										 organizationUnits);
			}
			
			if (certFields->issuerOrganization) 
			{
				tbstrTemp = certFields->issuerOrganization;
				_variant_t var_issorg((char*) tbstrTemp);
				::VariantCopy(issuerOrganization, &var_issorg);
			}

			if (certFields->issuerLocality) 
			{
				tbstrTemp = certFields->issuerLocality;
				_variant_t var_issloc((char*) tbstrTemp);
				::VariantCopy(issuerLocality, &var_issloc);
			}

			if (certFields->issuerCountry) 
			{
				tbstrTemp = certFields->issuerCountry;
				_variant_t var_isscountry((char*) tbstrTemp);
				::VariantCopy(issuerCountry, &var_isscountry);
			}

			if (certFields->issuerCommonName) {
				tbstrTemp = certFields->issuerCommonName;
				_variant_t var_isscn((char*) tbstrTemp);
				::VariantCopy(issuerCommonName, &var_isscn);
			}

			_variant_t var_issoucount((long) certFields->issuerOrgUnitCount);
			::VariantCopy(issuerOrgUnitCount, &var_issoucount);


			if (certFields->issuerOrgUnitCount > 0 && certFields->issuerOrganizationUnits) {
				Strings2SafeArrayVariant(certFields->issuerOrganizationUnits, 
										 certFields->issuerOrgUnitCount, 
										 issuerOrganizationUnits);
			}

			if (certFields->notAfter) {
				tbstrTemp = certFields->notAfter;
				_variant_t var_notafter((char*) tbstrTemp);
				::VariantCopy(notAfter, &var_notafter);
			}

			if (certFields->notBefore) {
				tbstrTemp = certFields->notBefore;
				_variant_t var_notbefore((char*) tbstrTemp);
				::VariantCopy(notBefore, &var_notbefore);
			}

			if (certFields->v3Extensions.vsKeyUsage.szKeyUsage) {
				tbstrTemp = certFields->v3Extensions.vsKeyUsage.szKeyUsage;
				_variant_t var_keyusage((char*) tbstrTemp);
				::VariantCopy(keyUsage, &var_keyusage);
			}

			if (certFields->v3Extensions.vsExtendedKeyUsage.szExtendedKeyUsage) {
				tbstrTemp = certFields->v3Extensions.vsExtendedKeyUsage.szExtendedKeyUsage;
				_variant_t var_exkeyusage((char*) tbstrTemp);
				::VariantCopy(extendedKeyUsage, &var_exkeyusage);
			}

			_variant_t var_sandirnamecount((long) certFields->v3Extensions.vsSubjectAltName.GeneralNames.nDirectoryNameCount);
			::VariantCopy(sanDirectoryNameCount, &var_sandirnamecount);

			if (certFields->v3Extensions.vsSubjectAltName.GeneralNames.nDirectoryNameCount > 0 && certFields->v3Extensions.vsSubjectAltName.GeneralNames.szDirectoryName) {
				Strings2SafeArrayVariant(certFields->v3Extensions.vsSubjectAltName.GeneralNames.szDirectoryName, 
										 certFields->v3Extensions.vsSubjectAltName.GeneralNames.nDirectoryNameCount, 
										 sanDirectoryNames);
			}

			_variant_t var_sanrfc822namecount((long) certFields->v3Extensions.vsSubjectAltName.GeneralNames.nRFC822NameCount);
			::VariantCopy(sanRFC822NameCount, &var_sanrfc822namecount);

			if (certFields->v3Extensions.vsSubjectAltName.GeneralNames.nRFC822NameCount > 0 && certFields->v3Extensions.vsSubjectAltName.GeneralNames.szRFC822Name) {
				Strings2SafeArrayVariant(certFields->v3Extensions.vsSubjectAltName.GeneralNames.szRFC822Name, 
										 certFields->v3Extensions.vsSubjectAltName.GeneralNames.nRFC822NameCount, 
										 sanRFC822Names);
			}

			_variant_t var_sandnsnamecount((long) certFields->v3Extensions.vsSubjectAltName.GeneralNames.nDNSNameCount);
			::VariantCopy(sanDNSNameCount, &var_sandnsnamecount);

			if (certFields->v3Extensions.vsSubjectAltName.GeneralNames.nDNSNameCount > 0 && certFields->v3Extensions.vsSubjectAltName.GeneralNames.szDNSName) {
				Strings2SafeArrayVariant(certFields->v3Extensions.vsSubjectAltName.GeneralNames.szDNSName, 
										 certFields->v3Extensions.vsSubjectAltName.GeneralNames.nDNSNameCount, 
										 sanDNSNames);
			}

			_variant_t var_sanuricount((long) certFields->v3Extensions.vsSubjectAltName.GeneralNames.nUniformResourceIdentifierCount);
			::VariantCopy(sanURICount, &var_sanuricount);

			if (certFields->v3Extensions.vsSubjectAltName.GeneralNames.nUniformResourceIdentifierCount > 0 && certFields->v3Extensions.vsSubjectAltName.GeneralNames.szUniformResourceIdentifier) {
				Strings2SafeArrayVariant(certFields->v3Extensions.vsSubjectAltName.GeneralNames.szUniformResourceIdentifier, 
										 certFields->v3Extensions.vsSubjectAltName.GeneralNames.nUniformResourceIdentifierCount, 
										 sanURIs);
			}

			_variant_t var_sanupncount((long) certFields->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameUPNCount);
			::VariantCopy(sanUPNCount, &var_sanupncount);

			if (certFields->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameUPNCount > 0 && certFields->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameUPN) {
				Strings2SafeArrayVariant(certFields->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameUPN, 
										 certFields->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameUPNCount, 
										 sanUPNs);
			}

			_variant_t var_sanguidcount((long) certFields->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameGUIDCount);
			::VariantCopy(sanGUIDCount, &var_sanguidcount);

			if (certFields->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameGUIDCount > 0 && certFields->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameGUID) {
				Strings2SafeArrayVariant(certFields->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameGUID, 
										 certFields->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameGUIDCount, 
										 sanGUIDs);
			}

			if(certFields->v3Extensions.vsCDP.nDPNamePresent)
			{

				_variant_t var_cdpDpndirnamecount((long) certFields->v3Extensions.vsCDP.distributionPointName.nDirectoryNameCount);
				::VariantCopy(cdpDpnDirectoryNameCount, &var_cdpDpndirnamecount);

				if (certFields->v3Extensions.vsCDP.distributionPointName.nDirectoryNameCount > 0 && certFields->v3Extensions.vsCDP.distributionPointName.szDirectoryName) {
					Strings2SafeArrayVariant(certFields->v3Extensions.vsCDP.distributionPointName.szDirectoryName, 
											 certFields->v3Extensions.vsCDP.distributionPointName.nDirectoryNameCount, 
											 cdpDpnDirectoryNames);
				}

				_variant_t var_cdpDpnrfc822namecount((long) certFields->v3Extensions.vsCDP.distributionPointName.nRFC822NameCount);
				::VariantCopy(cdpDpnRFC822NameCount, &var_cdpDpnrfc822namecount);

				if (certFields->v3Extensions.vsCDP.distributionPointName.nRFC822NameCount > 0 && certFields->v3Extensions.vsCDP.distributionPointName.szRFC822Name) {
					Strings2SafeArrayVariant(certFields->v3Extensions.vsCDP.distributionPointName.szRFC822Name, 
											 certFields->v3Extensions.vsCDP.distributionPointName.nRFC822NameCount, 
											 cdpDpnRFC822Names);
				}

				_variant_t var_cdpDpndnsnamecount((long) certFields->v3Extensions.vsCDP.distributionPointName.nDNSNameCount);
				::VariantCopy(cdpDpnDNSNameCount, &var_cdpDpndnsnamecount);

				if (certFields->v3Extensions.vsCDP.distributionPointName.nDNSNameCount > 0 && certFields->v3Extensions.vsCDP.distributionPointName.szDNSName) {
					Strings2SafeArrayVariant(certFields->v3Extensions.vsCDP.distributionPointName.szDNSName, 
											 certFields->v3Extensions.vsCDP.distributionPointName.nDNSNameCount, 
											 cdpDpnDNSNames);
				}

				_variant_t var_cdpDpnuricount((long) certFields->v3Extensions.vsCDP.distributionPointName.nUniformResourceIdentifierCount);
				::VariantCopy(cdpDpnURICount, &var_cdpDpnuricount);

				if (certFields->v3Extensions.vsCDP.distributionPointName.nUniformResourceIdentifierCount > 0 && certFields->v3Extensions.vsCDP.distributionPointName.szUniformResourceIdentifier) {
					Strings2SafeArrayVariant(certFields->v3Extensions.vsCDP.distributionPointName.szUniformResourceIdentifier, 
											 certFields->v3Extensions.vsCDP.distributionPointName.nUniformResourceIdentifierCount, 
											 cdpDpnURIs);
				}

				_variant_t var_cdpDpnupncount((long) certFields->v3Extensions.vsCDP.distributionPointName.nOtherNameUPNCount);
				::VariantCopy(cdpDpnUPNCount, &var_cdpDpnupncount);

				if (certFields->v3Extensions.vsCDP.distributionPointName.nOtherNameUPNCount > 0 && certFields->v3Extensions.vsCDP.distributionPointName.szOtherNameUPN) {
					Strings2SafeArrayVariant(certFields->v3Extensions.vsCDP.distributionPointName.szOtherNameUPN, 
											 certFields->v3Extensions.vsCDP.distributionPointName.nOtherNameUPNCount, 
											 cdpDpnUPNs);
				}

				_variant_t var_cdpDpnguidcount((long) certFields->v3Extensions.vsCDP.distributionPointName.nOtherNameGUIDCount);
				::VariantCopy(cdpDpnGUIDCount, &var_cdpDpnguidcount);

				if (certFields->v3Extensions.vsCDP.distributionPointName.nOtherNameGUIDCount > 0 && certFields->v3Extensions.vsCDP.distributionPointName.szOtherNameGUID) {
					Strings2SafeArrayVariant(certFields->v3Extensions.vsCDP.distributionPointName.szOtherNameGUID, 
											 certFields->v3Extensions.vsCDP.distributionPointName.nOtherNameGUIDCount, 
											 cdpDpnGUIDs);
				}
			}

			if(certFields->v3Extensions.vsCDP.nCRLIssuerPresent)
			{

				_variant_t var_cdpCrldirnamecount((long) certFields->v3Extensions.vsCDP.cRLIssuerName.nDirectoryNameCount);
				::VariantCopy(cdpCrlIssuerDirectoryNameCount, &var_cdpCrldirnamecount);

				if (certFields->v3Extensions.vsCDP.cRLIssuerName.nDirectoryNameCount > 0 && certFields->v3Extensions.vsCDP.cRLIssuerName.szDirectoryName) {
					Strings2SafeArrayVariant(certFields->v3Extensions.vsCDP.cRLIssuerName.szDirectoryName, 
											 certFields->v3Extensions.vsCDP.cRLIssuerName.nDirectoryNameCount, 
											 cdpCrlIssuerDirectoryNames);
				}

				_variant_t var_cdpCrlrfc822namecount((long) certFields->v3Extensions.vsCDP.cRLIssuerName.nRFC822NameCount);
				::VariantCopy(cdpCrlIssuerRFC822NameCount, &var_cdpCrlrfc822namecount);

				if (certFields->v3Extensions.vsCDP.cRLIssuerName.nRFC822NameCount > 0 && certFields->v3Extensions.vsCDP.cRLIssuerName.szRFC822Name) {
					Strings2SafeArrayVariant(certFields->v3Extensions.vsCDP.cRLIssuerName.szRFC822Name, 
											 certFields->v3Extensions.vsCDP.cRLIssuerName.nRFC822NameCount, 
											 cdpCrlIssuerRFC822Names);
				}

				_variant_t var_cdpCrldnsnamecount((long) certFields->v3Extensions.vsCDP.cRLIssuerName.nDNSNameCount);
				::VariantCopy(cdpCrlIssuerDNSNameCount, &var_cdpCrldnsnamecount);

				if (certFields->v3Extensions.vsCDP.cRLIssuerName.nDNSNameCount > 0 && certFields->v3Extensions.vsCDP.cRLIssuerName.szDNSName) {
					Strings2SafeArrayVariant(certFields->v3Extensions.vsCDP.cRLIssuerName.szDNSName, 
											 certFields->v3Extensions.vsCDP.cRLIssuerName.nDNSNameCount, 
											 cdpCrlIssuerDNSNames);
				}

				_variant_t var_cdpCrluricount((long) certFields->v3Extensions.vsCDP.cRLIssuerName.nUniformResourceIdentifierCount);
				::VariantCopy(cdpCrlIssuerURICount, &var_cdpCrluricount);

				if (certFields->v3Extensions.vsCDP.cRLIssuerName.nUniformResourceIdentifierCount > 0 && certFields->v3Extensions.vsCDP.cRLIssuerName.szUniformResourceIdentifier) {
					Strings2SafeArrayVariant(certFields->v3Extensions.vsCDP.cRLIssuerName.szUniformResourceIdentifier, 
											 certFields->v3Extensions.vsCDP.cRLIssuerName.nUniformResourceIdentifierCount, 
											 cdpCrlIssuerURIs);
				}

				_variant_t var_cdpCrlupncount((long) certFields->v3Extensions.vsCDP.cRLIssuerName.nOtherNameUPNCount);
				::VariantCopy(cdpCrlIssuerUPNCount, &var_cdpCrlupncount);

				if (certFields->v3Extensions.vsCDP.cRLIssuerName.nOtherNameUPNCount > 0 && certFields->v3Extensions.vsCDP.cRLIssuerName.szOtherNameUPN) {
					Strings2SafeArrayVariant(certFields->v3Extensions.vsCDP.cRLIssuerName.szOtherNameUPN, 
											 certFields->v3Extensions.vsCDP.cRLIssuerName.nOtherNameUPNCount, 
											 cdpCrlIssuerUPNs);
				}

				_variant_t var_cdpCrlguidcount((long) certFields->v3Extensions.vsCDP.cRLIssuerName.nOtherNameGUIDCount);
				::VariantCopy(cdpCrlIssuerGUIDCount, &var_cdpCrlguidcount);

				if (certFields->v3Extensions.vsCDP.cRLIssuerName.nOtherNameGUIDCount > 0 && certFields->v3Extensions.vsCDP.cRLIssuerName.szOtherNameGUID) {
					Strings2SafeArrayVariant(certFields->v3Extensions.vsCDP.cRLIssuerName.szOtherNameGUID, 
											 certFields->v3Extensions.vsCDP.cRLIssuerName.nOtherNameGUIDCount, 
											 cdpCrlIssuerGUIDs);
				}
			}

			vsPKIFreeCertFields (certFields);
		} while (0);

		if (*retCode)
			return GetErrDescription(*retCode);

	}
	catch(_com_error e)
	{	
		/*LogEvent("exception vPKIParseB64Cert:%s", e.Description());*/
		return Error((BSTR)e.Description());
	}

	return S_OK;

}

/******************************************************************************
**
** Function GetErrDescription 
** This function creates an HRESULT object given an error code
**
** Input paramters : 
** nErrorCode : error code
**
** Output parameters : none
** 
** Returns : HRESULT - error object
**
******************************************************************************/

HRESULT CvsVerify::GetErrDescription(int nErrCode)
{
	char errorString[PTA_LARGE_BUF_MAX];

	if (nErrCode > VSVAL_ERR_BASE && nErrCode < VSVAL_ERR_MAX) {
			VSVAL_ErrorString(m_valSdk, errorString, PTA_LARGE_BUF_MAX, nErrCode, 0);	
	} 
	else
		comvsscErrorString(errorString, nErrCode);

	if (nErrCode < 0x80000000)
		nErrCode += 0x80000000;
	
	return CvsVerify::Error(_T(errorString), IID_IvsVerify, nErrCode);
}


/************************************************************************************
**
** Utility functions
**
************************************************************************************/
void vsLogInfoMessage(char *fmt, ...) {

  char infoBuf[PTA_LARGE_BUF_MAX];
  PTATIME currentTime;
  char *timeBuf = 0;
  va_list ap;
  va_start(ap, fmt);

  if (globalLogFP==0) return;
    (void) vsprintf(infoBuf, fmt, ap);
    va_end(ap);

    pta_time(&currentTime);
    timeBuf = asctime(localtime((const time_t *) &currentTime));
    pta_make_newline_null(timeBuf);

    fprintf(globalLogFP, "[%s] info: %s\n", timeBuf, infoBuf);
	fflush(globalLogFP);
	return;
}



/////////////////////////////////////////////////////////////////////////////
// Strings2SafeArrayVariant
// converting byte array to a safearray of variants

int Strings2SafeArrayVariant(char** pdata, int len, VARIANT* data) {

		
		LPSAFEARRAY psa;
		SAFEARRAYBOUND rgsabound[]  = {len,0}; //  elements, 0-based
		_bstr_t		tbstrTemp;

		VariantInit(data);

		psa = SafeArrayCreate(VT_VARIANT, 1, rgsabound);

		//Plug references to the data into the SAFEARRAY
		LPVARIANT rgElems;
		if (FAILED(SafeArrayAccessData(psa,(LPVOID*)&rgElems)))
		{
			 //LogEvent("ERROR_COM_SAFEARRAY_ACCESS_DATA");
 			 return ERROR_COM_SAFEARRAY_ACCESS_DATA;
		}
		//declare each string as VARIANT			

		for ( int i = 0; i< len; i++) {
			VARIANT vData;
			VariantInit(&vData);
			V_VT(&vData) = VT_BSTR;
			tbstrTemp = (char*)pdata[i];
			vData.bstrVal = tbstrTemp.copy();
			rgElems[i] = vData;
		}
        SafeArrayUnaccessData(psa);
        V_VT(data) = VT_ARRAY | VT_VARIANT;
        V_ARRAY(data) = psa;
		return 0;
}



/////////////////////////////////////////////////////////////////////////////
// Bytes2SafeArrayVariant
// converting byte array to a safearray of variants

int Bytes2SafeArrayVariant(unsigned char* pdata, int len, VARIANT* data) {

		
		LPSAFEARRAY psa;
		SAFEARRAYBOUND rgsabound[]  = { len,0}; //  elements, 0-based
		VariantInit(data);

		psa = SafeArrayCreate(VT_VARIANT, 1, rgsabound);

		//Plug references to the data into the SAFEARRAY
		LPVARIANT rgElems;
		if (FAILED(SafeArrayAccessData(psa,(LPVOID*)&rgElems)))
		{
			 //LogEvent("ERROR_COM_SAFEARRAY_ACCESS_DATA");
 			 return ERROR_COM_SAFEARRAY_ACCESS_DATA;
		}
		//declare each byte as VARIANT

		VARIANT vData;
		VariantInit(&vData);

		for ( int i = 0; i< len; i++) {
			V_VT(&vData) = VT_UI1;
			V_UI1(&vData) = *(pdata+i);
			rgElems[i] = vData;
		}
        SafeArrayUnaccessData(psa);
        V_VT(data) = VT_ARRAY | VT_VARIANT;
        V_ARRAY(data) = psa;
		return 0;
}

///////////////////////////////////////////////////////////////////////////////
//	SafeArrayVariant2Bytes
//	convert Safearray of variant to byte array

int SafeArrayVariant2Bytes(VARIANT* data, int len, unsigned char* pdata) {
		
		if(!(V_VT(data) == VT_ARRAY | VT_VARIANT)||!(V_ARRAY(data))) {
			return ERROR_COM_DATA_ERROR;
		}

		//Plug references to the data into the SAFEARRAY
		LPVARIANT rgElems;
		if (FAILED(SafeArrayAccessData(V_ARRAY(data),(LPVOID*)&rgElems)))
		{
			 return ERROR_COM_SAFEARRAY_ACCESS_DATA;
		}
				
		for(int i = 0; i <len; i++) {
			*(pdata+i) = (unsigned char) V_UI1(&rgElems[i]);
		}
        SafeArrayUnaccessData(V_ARRAY(data));

		return 0;
}

void LogEvent(LPCTSTR pFormat, ...)
 {

    TCHAR    chMsg[256];
    HANDLE  hEventSource;
    LPTSTR  lpszStrings[1];	

    va_list pArg;

    va_start(pArg, pFormat);
    (void) vsprintf(chMsg, pFormat, pArg);
    va_end(pArg);

    lpszStrings[0] = chMsg;

    /* Get a handle to use with ReportEvent(). */
    hEventSource = RegisterEventSource(NULL, "comvsssc");
    if (hEventSource != NULL)
    {
        /* Write to event log. */
        ReportEvent(hEventSource, 
					EVENTLOG_ERROR_TYPE, 
					0, 
					1, 
					NULL, 
					1,
					0, 
					//(LPCTSTR*) &lpszStrings[0], 
					(const char**)lpszStrings,
					NULL);
        DeregisterEventSource(hEventSource);
    }

}
