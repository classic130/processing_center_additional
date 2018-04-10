#include "stdafx.h"
#include <comutil.h>
#include "certmgmt.h"
#include "propsht.h"
#include "sign.h"
#include "util.h"
#include "macros.h"
#include "ptav3.h"
#include "certmgmt.h"
#include "settings.h"
#include "ptaiface.h"
#include "vsserrs.h"
#include "resource.h"
#include "datacc.h"
#include "pkcs7engine.h"


HRESULT SignFile(LPTimeSettings i_pTimeSettings)
{
	HRESULT hr = S_OK;
	IVSPTA* pVSPTA = NULL;
	_bstr_t* ptbstrSelFiles = NULL, bstrSignature = "", bstrSignatureFile = "";
	DWORD dwNumFiles = 0, dwFileSize = 0, dwSignature = 0, dwDocSisPkcs7Sig = 0, dwPKCS7Size = 0;
	DWORD dwContentSize = 0;
	CRegSettings usrSettings;
	VARIANT varAlgId, varSignature, varToSign;
	CDataAccess DAReadObj, DAWriteObj;
	SYSTEMTIME UTCTime;
	DATE dateSign;
	UDATE udateSign;
	PKCS7SignInfo pkcsSignInfoImageFile, pkcsSignInfoSignature;
	PBYTE pbSignature = NULL, pbDocSisPkcs7Sig = NULL, pbFile = NULL;

	CoInitialize(NULL);

	VariantInit(&varAlgId);
	VariantInit(&varSignature);
	VariantInit(&varToSign);
	
	pkcsSignInfoImageFile.Initialize();
	pkcsSignInfoSignature.Initialize();

	do
	{
		// Get user settings from the registry
		hr = usrSettings.Read();
		CHECK_HRESULT_BREAK

		// First get the list of file(s) to be signed
		if(usrSettings.m_bstrCodeType == _bstr_t("CableModem"))
			hr = GetOpenFileNames(IDS_OPENFILE_TITLE, IDS_FILE_FILTER, TRUE, &ptbstrSelFiles, &dwNumFiles);
		else
			if(usrSettings.m_bstrCodeType == _bstr_t("SignOp"))
				hr = GetOpenFileNames(IDS_OPENFILE_TITLE, IDS_FILE_FILTER2, TRUE, &ptbstrSelFiles, &dwNumFiles);

		CHECK_HRESULT_BREAK

		usrSettings.m_CertOp = CERT_COSIGN;

		// Initialize PTA with the user settings and get a pointer to PTA interface
		hr = InitializePTA(usrSettings, &pVSPTA);
		CHECK_HRESULT_BREAK

		if(usrSettings.m_dwDisplayDigID)
			hr = pVSPTA->SelIDForChallenge();
		else
			hr = pVSPTA->SelIDForTrans();

		CHECK_HRESULT_BREAK

		// Specify the signing time, convert the local time to UTC time first
		hr = GetUTCTime(i_pTimeSettings, &UTCTime);
		CHECK_HRESULT_BREAK
		
		udateSign.st = UTCTime;
		udateSign.wDayOfYear = 0;

		if(VarDateFromUdate(&udateSign, 0, &dateSign) != S_OK)
		{
			hr = E_VSSCODE_DATE_ERR;
			break;
		}
		
		hr = pVSPTA->put_SignDate(dateSign);
		CHECK_HRESULT_BREAK

		// Set up the hash alg
		varAlgId.vt = VT_I2;
		if(_strnicmp(usrSettings.m_bstrHashAlg, "MD5", 3) == 0)
			varAlgId.iVal = SCRIPT_HASH_MD5_WITHAUTHATTR;	
		else
			if(_strnicmp(usrSettings.m_bstrHashAlg, "MD2", 3) == 0)
				varAlgId.iVal = SCRIPT_HASH_MD2_WITHAUTHATTR;
			else
				if(_strnicmp(usrSettings.m_bstrHashAlg, "SHA1", 4) == 0)
					varAlgId.iVal = SCRIPT_HASH_SHA1_WITHAUTHATTR;
				else
				{
					hr = E_VSSCODE_INVALIDALG;
					break;
				}

		// For each selected file, sign it and stuff the signature in a new file
		for(UINT i = 0; i < dwNumFiles; i++)
		{
			hr = DAReadObj.Open(ptbstrSelFiles[i]);
			CHECK_HRESULT_BREAK

			hr = DAReadObj.GetSize(&dwFileSize);
			CHECK_HRESULT_BREAK

			// Allocate memory for the file size and read entire file at once
			pbFile = (PBYTE) malloc(dwFileSize);
			CHECK_MEM_BREAK(pbFile)

			hr = DAReadObj.Read(pbFile, &dwFileSize);
			CHECK_HRESULT_BREAK

			DAReadObj.Close();

			// Parse the file read, the file is assumed to be a PKCS#7 signed data + signed content
			// Determine where the content begins, according to DOCSIS the content will
			// immediately follow the PKCS#7 detached signature
			hr = GetPKCS7Length(pbFile, dwFileSize, &dwPKCS7Size);
			CHECK_HRESULT_BREAK

			hr = ParsePKCS7SignedData(pbFile, dwPKCS7Size, &pkcsSignInfoImageFile);
			CHECK_HRESULT_BREAK

			// Check if we got the certificates, signer info and content from the image file
			if(pkcsSignInfoImageFile.pbCertList == NULL)
			{
				hr = E_VSSCODE_NOCERTSPRESENT;
				break;
			}

			if(pkcsSignInfoImageFile.pbSignerInfo == NULL)
			{
				hr = E_VSSCODE_NOSIGNERINFO;
				break;
			}

			// Create the buffer in which we will place the content that is to be signed
			dwContentSize = dwFileSize - dwPKCS7Size;

			varToSign.vt = VT_ARRAY | VT_UI1;
			varToSign.parray = SafeArrayCreateVector(VT_UI1, 0, dwContentSize);
			CHECK_MEM_BREAK(varToSign.parray)

			memcpy(varToSign.parray->pvData, pbFile + dwPKCS7Size, dwContentSize);

			// Sign the content, content is the actual image + any certificate(if present)
			hr = pVSPTA->SignTransaction(&varToSign, &varAlgId, &varSignature);
			CHECK_HRESULT_BREAK

			// The signature is base64 encoded, decode it first
			bstrSignature = varSignature.bstrVal;
			_Base64Decode(bstrSignature, bstrSignature.length(), NULL, &dwSignature);
			
			pbSignature = (PBYTE)malloc(dwSignature);
			CHECK_MEM_BREAK(pbSignature)

			_Base64Decode(bstrSignature, bstrSignature.length(), (char*)pbSignature, &dwSignature);

			// Parse the signature and get the PKCS#7 info from it
			hr = ParsePKCS7SignedData(pbSignature, dwSignature, &pkcsSignInfoSignature);
			CHECK_HRESULT_BREAK

			// Construct the DOCSIS compatible PKCS#7 signed data from the 2 pkcs7 infos
			hr = CreateDocSisPKCS7Sig(pkcsSignInfoImageFile, pkcsSignInfoSignature, usrSettings.m_bstrHashAlg, &pbDocSisPkcs7Sig, &dwDocSisPkcs7Sig);
			CHECK_HRESULT_BREAK

			// Create the O/P file, file name is input file name suffixed with "-clsigned-date"
			hr = GetSignatureFileName(ptbstrSelFiles[i], usrSettings.m_bstrCodeType, bstrSignatureFile);
			CHECK_HRESULT_BREAK
		
			hr = DAWriteObj.Open(bstrSignatureFile, ACCESS_WRITE);
			if(hr == E_VSSCODE_DOCEXISTS)
			{
				if(ShowErrorMessage(hr, bstrSignatureFile, ERR_QUES) == TRUE)
					hr = DAWriteObj.Open(bstrSignatureFile, ACCESS_OVERWRITE);
			}

			CHECK_HRESULT_BREAK

			// First add the signature
			hr = DAWriteObj.Write(pbDocSisPkcs7Sig, dwDocSisPkcs7Sig);
			CHECK_HRESULT_BREAK

			// Now append the contents
			hr = DAWriteObj.Write(pbFile + dwPKCS7Size, dwContentSize);
			CHECK_HRESULT_BREAK

			DAWriteObj.Close();

			FREE_MEMORY(pbDocSisPkcs7Sig)
			FREE_MEMORY(pbSignature)
			FREE_MEMORY(pbFile)

			VariantClear(&varSignature);
			VariantInit(&varSignature);

			VariantClear(&varToSign);
			VariantInit(&varToSign);

			pkcsSignInfoImageFile.Clear();
			pkcsSignInfoSignature.Clear();

		}	// end for

	}while(0);

	FREE_MEMORY(pbDocSisPkcs7Sig)
	FREE_MEMORY(pbSignature)
	FREE_MEMORY(pbFile)

	pkcsSignInfoImageFile.Clear();
	pkcsSignInfoSignature.Clear();

	DAReadObj.Close();
	DAWriteObj.Close();
	
	if(ptbstrSelFiles)
	{
		delete[] ptbstrSelFiles;
		ptbstrSelFiles = NULL;
	}

	UnInitializePTA(pVSPTA);

	VariantClear(&varAlgId);
	VariantClear(&varSignature);
	VariantClear(&varToSign);
	
	CoUninitialize();

	if(hr != S_OK)
		_LogErrorMsg("SignFile().", "Error occured while signing file.", NULL, hr);

	return hr;
}



HRESULT OnlySignFile(LPTimeSettings i_pTimeSettings)
{
	HRESULT hr = S_OK;
	IVSPTA* pVSPTA = NULL;
	_bstr_t* ptbstrSelFiles = NULL, bstrSignature = "", bstrSignatureFile = "";
	VARIANT varAlgId, varToSign, varSignature;
	SYSTEMTIME UTCTime;
	DATE dateSign;
	UDATE udateSign;
	DWORD dwNumFiles = 0, dwFileSize = 0, dwSignature = 0;
	CRegSettings usrSettings;
	CDataAccess DAReadObj, DAWriteObj;
	PBYTE pbSignature = NULL;

	CoInitialize(NULL);

	VariantInit(&varAlgId);
	VariantInit(&varToSign);
	VariantInit(&varSignature);

	do
	{
		// First get the list of file(s) to be signed
		hr = GetOpenFileNames(IDS_OPENFILE_TITLE2, IDS_FILE_FILTER2, TRUE, &ptbstrSelFiles, &dwNumFiles);
		CHECK_HRESULT_BREAK

		// Get user settings from the registry
		hr = usrSettings.Read();
		CHECK_HRESULT_BREAK

		usrSettings.m_CertOp = CERT_SIGNONLY;

		// Initialize PTA with the user settings and get a pointer to PTA interface
		hr = InitializePTA(usrSettings, &pVSPTA);
		CHECK_HRESULT_BREAK

		if(usrSettings.m_dwDisplayDigID)
			hr = pVSPTA->SelIDForChallenge();
		else
			hr = pVSPTA->SelIDForTrans();

		CHECK_HRESULT_BREAK

		// Specify the signing time, convert the local time to UTC time first
		hr = GetUTCTime(i_pTimeSettings, &UTCTime);
		CHECK_HRESULT_BREAK
		
		udateSign.st = UTCTime;
		udateSign.wDayOfYear = 0;

		if(VarDateFromUdate(&udateSign, 0, &dateSign) != S_OK)
		{
			hr = E_VSSCODE_DATE_ERR;
			break;
		}
		
		hr = pVSPTA->put_SignDate(dateSign);
		CHECK_HRESULT_BREAK

		// Set up the hash alg
		varAlgId.vt = VT_I2;
		if(_strnicmp(usrSettings.m_bstrHashAlg, "MD5", 3) == 0)
			varAlgId.iVal = SCRIPT_HASH_MD5_WITHAUTHATTR;	
		else
			if(_strnicmp(usrSettings.m_bstrHashAlg, "MD2", 3) == 0)
				varAlgId.iVal = SCRIPT_HASH_MD2_WITHAUTHATTR;
			else
				if(_strnicmp(usrSettings.m_bstrHashAlg, "SHA1", 4) == 0)
					varAlgId.iVal = SCRIPT_HASH_SHA1_WITHAUTHATTR;
				else
				{
					hr = E_VSSCODE_INVALIDALG;
					break;
				}

		for(UINT i = 0; i < dwNumFiles; i++)
		{
			hr = DAReadObj.Open(ptbstrSelFiles[i]);
			CHECK_HRESULT_BREAK

			hr = DAReadObj.GetSize(&dwFileSize);
			CHECK_HRESULT_BREAK

			// Allocate memory for the file size and read entire file at once, the entire file is to be
			// signed
			varToSign.vt = VT_ARRAY | VT_UI1;
			varToSign.parray = SafeArrayCreateVector(VT_UI1, 0, dwFileSize);
			CHECK_MEM_BREAK(varToSign.parray)

			hr = DAReadObj.Read((unsigned char*)varToSign.parray->pvData, &dwFileSize);
			CHECK_HRESULT_BREAK

			DAReadObj.Close();

			// Sign the content
			hr = pVSPTA->SignTransaction(&varToSign, &varAlgId, &varSignature);
			CHECK_HRESULT_BREAK

			// The signature is base64 encoded, decode it first
			bstrSignature = varSignature.bstrVal;
			_Base64Decode(bstrSignature, bstrSignature.length(), NULL, &dwSignature);

			pbSignature = (PBYTE)malloc(dwSignature);
			CHECK_MEM_BREAK(pbSignature)

			_Base64Decode(bstrSignature, bstrSignature.length(), (char*)pbSignature, &dwSignature);

			// Create the O/P file, file name is input file name suffixed with ".signed-date"
			hr = GetSignatureFileName(ptbstrSelFiles[i], usrSettings.m_bstrCodeType, bstrSignatureFile);
			CHECK_HRESULT_BREAK

			hr = DAWriteObj.Open(bstrSignatureFile, ACCESS_WRITE);
			if(hr == E_VSSCODE_DOCEXISTS)
			{
				if(ShowErrorMessage(hr, bstrSignatureFile, ERR_QUES) == TRUE)
					hr = DAWriteObj.Open(bstrSignatureFile, ACCESS_OVERWRITE);
			}

			CHECK_HRESULT_BREAK

			// First add the signature
			hr = DAWriteObj.Write(pbSignature, dwSignature);
			CHECK_HRESULT_BREAK

			// Now append the contents
			hr = DAWriteObj.Write((unsigned char*)varToSign.parray->pvData, dwFileSize);
			CHECK_HRESULT_BREAK

			DAWriteObj.Close();

			FREE_MEMORY(pbSignature)

			VariantClear(&varSignature);
			VariantInit(&varSignature);

			VariantClear(&varToSign);
			VariantInit(&varToSign);

		}	// end for

	}while(0);

	FREE_MEMORY(pbSignature)

	DAReadObj.Close();
	DAWriteObj.Close();

	if(ptbstrSelFiles)
	{
		delete[] ptbstrSelFiles;
		ptbstrSelFiles = NULL;
	}

	UnInitializePTA(pVSPTA);

	VariantClear(&varAlgId);
	VariantClear(&varToSign);
	VariantClear(&varSignature);

	CoUninitialize();

	if(hr != S_OK)
		_LogErrorMsg("SignFile().", "Error occured while signing file for single signature.", NULL, hr);

	return hr;
}



HRESULT GetSignatureFileName(_bstr_t& i_bstrImageFileName, const _bstr_t& i_bstrCodeType, _bstr_t& o_bstrSignFile)
{
	HRESULT hr = S_OK;
	WCHAR* pwImageFile = NULL;
	TCHAR* pszFormattedDate = NULL;
	_bstr_t tbstrSignFileName = "";
	INT nFormatDataSize = 0;
	DWORD dwError = 0;

	do
	{
		pwImageFile = i_bstrImageFileName.copy();
		CHECK_MEM_BREAK(pwImageFile)

		for(INT i = i_bstrImageFileName.length() - 1; i >= 0; i--)
		{
			if(pwImageFile[i] == L'.')
			{
				pwImageFile[i] = NULL;
				break;
			}
		}

		if(i_bstrCodeType == _bstr_t("CableModem"))
		{
			o_bstrSignFile = pwImageFile;
			o_bstrSignFile += "-clsigned-";
		}
		else
		{
			o_bstrSignFile = i_bstrImageFileName;
			o_bstrSignFile += ".signed-";
		}

		// Add the date now
		nFormatDataSize = GetDateFormat(_GetDefaultLangID(), 0, NULL, "MMddyyyy", NULL, 0);
		if(nFormatDataSize == 0)
		{
			dwError = GetLastError();
			_LogErrorMsg("GetSignatureFileName().", "GetDateFormat() failed for size.", NULL, dwError);
			hr = E_VSSCODE_GETDATEFORMAT;
			break;
		}

		pszFormattedDate = (TCHAR*)malloc(nFormatDataSize);
		CHECK_MEM_BREAK(pszFormattedDate)

		nFormatDataSize = GetDateFormat(_GetDefaultLangID(), 0, NULL, "MMddyyyy", pszFormattedDate, nFormatDataSize);
		if(nFormatDataSize == 0)
		{
			dwError = GetLastError();
			_LogErrorMsg("GetSignatureFileName().", "GetDateFormat() failed.", NULL, dwError);
			hr = E_VSSCODE_GETDATEFORMAT;
			break;
		}

		o_bstrSignFile += pszFormattedDate;

		if(i_bstrCodeType == _bstr_t("CableModem"))
			o_bstrSignFile += ".img";

	}while(0);


	FREE_MEMORY(pszFormattedDate)
	SYS_FREE_MEMORY(pwImageFile)

	if(hr != S_OK)
		_LogErrorMsg("GetSignatureFileName().", "Error obtaining file name.", NULL, hr);

	return hr;
}



HRESULT GetPKCS7Length(PBYTE i_pbData, DWORD i_dwData, LPDWORD o_pdwPKCS7Size)
{
	HRESULT hr = S_OK;
	DWORD dwLenOctets = 0,dwTemp = 0;

	do
	{
		if(!i_pbData || !o_pdwPKCS7Size)
		{
			hr = E_VSSCODE_EMPTYARGS;
			break;
		}

		if(i_dwData == 0)
		{
			hr = E_VSSCODE_INVALIDARGS;
			break;
		}

		*o_pdwPKCS7Size = 0;

		if(i_dwData < 2)
		{
			hr = E_VSSCODE_INVALID_PKCS7;
			break;
		}

		// Check if we have a SEQUENCE at the beginning
		if(i_pbData[0] != 0x30)
		{
			hr = E_VSSCODE_INVALID_PKCS7;
			break;
		}

		// Check if we have indefinite length encoding
		if(i_pbData[1] == 0x80)
		{
			hr = E_VSSCODE_INDEFINITE_ENC;
			break;
		}

		// If Bit 8 of i_pbData[1] is 0 then then bits 1 to 7 give length of the PKCS#7
		// If Bit 8 is 1 then bits 1 to 7 give the number of length octets
		if((i_pbData[1] & 0x80) == 0)
			*o_pdwPKCS7Size = i_pbData[1] + 2;
		else
		{
			dwLenOctets = i_pbData[1] &0x3f;

			// Check if we have enough length octets
			if(i_dwData < dwLenOctets + 2) 
			{
				hr = E_VSSCODE_INVALID_PKCS7;
				break;
			}

			// Get the actual length now
			for(INT i = dwLenOctets + 1, j = 0; i > 1; i--, j++)
			{
				dwTemp = 1;
				dwTemp = dwTemp << (j*8);
				*o_pdwPKCS7Size += dwTemp * i_pbData[i];
			}

			*o_pdwPKCS7Size += 2 + dwLenOctets;
		}

		// Check if the amount of data indicated by '*o_pdwPKCS7Size' actually exists
		if(*o_pdwPKCS7Size >= i_dwData)
		{
			*o_pdwPKCS7Size = 0;
			hr = E_VSSCODE_INVALID_PKCS7;
			break;
		}

	}while(0);

	if(hr != S_OK)
		_LogErrorMsg("GetPKCS7Length().", "Error getting length of signed data.", NULL, hr);

	return hr;
}