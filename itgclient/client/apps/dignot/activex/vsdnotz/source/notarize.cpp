#include "stdafx.h"
#include <wininet.h>
#include <comutil.h>
#include "ptav3.h"
#include "ptaerrs.h"
#include "vsps_defines.h"
#include "integrate.h"			// From bsafelite
#include "datatypes.h"			// From simder
#include "sequence.h"			
#include "universalinteger.h"
#include "objectidentifier.h"
#include "octetstring.h"
#include "boolean.h"
#include "basedercollection.h"
#include "basederhierarchy.h"
#include "taggedvalue.h"
#include "notarize.h"
#include "nzutils.h" 
#include "nzdefines.h"
#include "nzmacros.h"
#include "nzerrs.h"
#include "resource.h"
#include <winerror.h>

// Constructor
CNotarization::CNotarization(IVSPTA* i_pVSPta/*, BOOL i_bShowDigID*/)

{
	// For a record verification operation no PTA pointer will be passed in
	if(i_pVSPta)
	{
		m_pVSPta = i_pVSPta;
		m_pVSPta->AddRef();
	}
	else
		m_pVSPta = NULL;

	//m_bShowDigID = i_bShowDigID;
}


// Destructor
CNotarization::~CNotarization()
{
	RELEASE_INTERFACE_PTR(m_pVSPta)

	//m_bShowDigID = 0;
}


/*
I/P -	'i_bstrDocument'	:	Is the path of document to be notarized. A URL can be specified
								over here.
		'i_bstrDescription'	:	Can either be some description about the notarization operation,
								or can be the file name.
		'i_bstrHashAlg'	:	Is the hash algorithm to be used while hashing the document, the
							notarization server must support this algorithm.
O/P -	'o_pNotzRequest'	:	Contains an ASN.1 encoded notarization request. Only the
								'pbNzRequest' and 'dwNzRequest' members of this structure are
								filled by this function.
Return -	An hresult indicating success of the operation.
Working -	This function generates a notarization request which is recognized by the 
			notarization server. It uses the simder library functions to construct the ASN.1
			structure. It used the bsafelite library functions to generate random number.
*/
HRESULT CNotarization::CreateNotarizationRequest(const _bstr_t& i_bstrDocument, PBYTE i_pbHashVal, const _bstr_t& i_bstrDescription, const _bstr_t& i_bstrHashAlg, const _bstr_t& i_bstrUserAgent, LPNzRequest o_pNotzRequest)
{
	HRESULT hr = S_OK;
	PBYTE pbHash = NULL;
	DWORD dwHashLen = 0;
	_bstr_t bstrHashOID = "", tbstrUserAgent = "";
	TCHAR *pDescription = NULL;

	do
	{
		if(!i_bstrDescription || !i_bstrHashAlg || !o_pNotzRequest)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		// Either one should be present
		if(i_bstrDocument == _bstr_t("") && !i_pbHashVal)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(i_bstrHashAlg == _bstr_t(""))
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		o_pNotzRequest->dwNzRequest = 0;
		o_pNotzRequest->pbNzRequest = NULL;

		o_pNotzRequest->dwNzNonce = 0;
		o_pNotzRequest->pbNzNonce = 0;

		if(_strnicmp(i_bstrHashAlg, "MD2", 3) == 0)
		{
			bstrHashOID = szOID_RSA_MD2;
			dwHashLen = HASH_MD2_LENGTH;
		}
		else
			if(_strnicmp(i_bstrHashAlg, "MD4", 3) == 0)
			{
				bstrHashOID = szOID_RSA_MD4;
				dwHashLen = HASH_MD4_LENGTH;
			}
			else
   				if(_strnicmp(i_bstrHashAlg, "MD5", 3) == 0)
				{
					bstrHashOID = szOID_RSA_MD5;
					dwHashLen = HASH_MD5_LENGTH;
				}
				else
					if(_strnicmp(i_bstrHashAlg, "SHA1", 4) == 0)
					{
						bstrHashOID = szOID_OIWSEC_sha1;
						dwHashLen = HASH_SHA1_LENGTH;
					}
					else
					{
						hr = E_NZINVALIDALG;
						break;
					}

		if(!i_pbHashVal)
		{
			hr = _HashDocument(i_bstrDocument, bstrHashOID, i_bstrUserAgent, &pbHash, &dwHashLen);
			CHECK_HRESULT_BREAK

#if 0	// new simder fix
			// Reverse the hash before passing it to the Simder for encoding as an octet string,
			// this is because simder reverses the octet string. The notarization server stores 
			// this reversed octet string. Later when doing a Web based verification the hashes
			// don't compare as they are reversed

			BYTE tmpHash;
			for(UINT i = 0; i < dwHashLen/2; i++)
			{
				tmpHash = pbHash[i];
				pbHash[i] = pbHash[dwHashLen - i - 1];
				pbHash[dwHashLen - i - 1] = tmpHash;
			}
#endif
		}
					

		/* Construct the ASN needed for a notarization request
		   NotarizationReq ::= SEQUENCE  {
										version	INTEGER		{ v1(1) },
										messageImprint		MessageImprint,
										--a hash algorithm OID and the hash value of the data to be
										--time stamped
										reqPolicy			PolicyInformation	OPTIONAL,
										nonce               INTEGER				OPTIONAL,
										certReq             BOOLEAN             DEFAULT FALSE,
										extensions          [0] IMPLICIT Extensions  OPTIONAL
									 }*/

		CSequence NotarizationReq;
		CSequence MsgImprint;
		CSequence AlgIdentifier;
		CBoolean BoolTrue(TRUE);
		USHORT uVersion = NZ_VERSION;

		CUniversalInteger NzServerVersion(1, (PBYTE)&uVersion);
		CObjectIdentifier AlgId(lstrlen(bstrHashOID), (PBYTE)(TCHAR*)bstrHashOID);

		AlgIdentifier += AlgId;
		MsgImprint += AlgIdentifier;

		if(!i_pbHashVal)
		{
			COctetString HashData(dwHashLen, pbHash);
			MsgImprint += HashData;
		}
		else
		{
			COctetString HashData(dwHashLen, (unsigned char *)i_pbHashVal);
			MsgImprint += HashData;
		}
		
		// Generate a random nonce, used to prevent replay attack
		o_pNotzRequest->pbNzNonce = (PBYTE)malloc(NONCE_DATA_SIZE);
		CHECK_MEM_BREAK(o_pNotzRequest->pbNzNonce)

		o_pNotzRequest->dwNzNonce = NONCE_DATA_SIZE;
		
		if(GenerateRandomBlock(o_pNotzRequest->pbNzNonce, NONCE_DATA_SIZE) != 0)
		{
			hr = E_NZGENRANDOMERR;
			break;
		}

		CUniversalInteger RandomData(NONCE_DATA_SIZE, o_pNotzRequest->pbNzNonce);

		/* Create the 'Extension' that contains the document name (description)
		Extension         ::=   SEQUENCE {
											extnId            EXTENSION.&id ({ExtensionSet}),
											critical          BOOLEAN DEFAULT FALSE,
											extnValue         OCTET STRING }
											-- contains a DER encoding of a value of type
		*/

		CSequence Extension;
		CObjectIdentifier ObjIdDocExt(lstrlen(DOC_EXT_OID), (PBYTE)DOC_EXT_OID);

		pDescription = (TCHAR*) malloc(lstrlen(i_bstrDescription) + 1);
		CHECK_MEM_BREAK(pDescription)

		lstrcpy(pDescription, i_bstrDescription);

#if 0	// new simder fix
		// Reverse the description before passing it to the COctet constructor
		_strrev(pDescription);
#endif

		// Description is itself an octet string
		COctetString Description(((lstrlen(pDescription))*sizeof(TCHAR)), (PBYTE)(TCHAR*)pDescription);

#if 0	// new simder fix
		// Reverse the description
		BYTE tmpDesc, *pbDesc;
		UINT nDescLen = Description.BaseDERBlob->cbData;
		pbDesc = Description.BaseDERBlob->pbData;
		for(UINT i = 0; i < nDescLen/2; i++)
		{
			tmpDesc = pbDesc[i];
			pbDesc[i] = pbDesc[nDescLen - i - 1];
			pbDesc[nDescLen - i - 1] = tmpDesc;
		}
#endif

		COctetString EncDesc(Description.BaseDERBlob->cbData, Description.BaseDERBlob->pbData);

		Extension += ObjIdDocExt;
		Extension += EncDesc;

		CTaggedValue Tag(CONTEXT_SPECIFIC, CONSTRUCTED, 0, 0, *(Extension.BaseDERBlob));


		/* Create the 'PolicyInformation' for the authentic document request
		PolicyInformation ::= SEQUENCE {
											policyIdentifier	CertPolicyId,
											policyQualifiers	SEQUENCE SIZE (1..MAX) OF
											PolicyQualifierInfo OPTIONAL }

		Just encoding the CertPolicyId which is an OBJECT IDENTIFIER
		*/
		CSequence PolicyInfo;
		CObjectIdentifier ObjIdAuthDoc(lstrlen(AUTHDOC_POLICY_OID), (PBYTE)AUTHDOC_POLICY_OID);
		PolicyInfo += ObjIdAuthDoc;

		NotarizationReq += NzServerVersion;
		NotarizationReq += MsgImprint;
		NotarizationReq += PolicyInfo;
		NotarizationReq += RandomData;
		NotarizationReq += BoolTrue;
		NotarizationReq += Tag;

		o_pNotzRequest->pbNzRequest = (PBYTE)malloc((NotarizationReq.BaseDERBlob)->cbData);
		CHECK_MEM_BREAK(o_pNotzRequest->pbNzRequest)

		o_pNotzRequest->dwNzRequest = (NotarizationReq.BaseDERBlob)->cbData;
		memcpy(o_pNotzRequest->pbNzRequest, (NotarizationReq.BaseDERBlob)->pbData, (NotarizationReq.BaseDERBlob)->cbData);

#if 0
		DWORD dwBytesWritten;
		HANDLE hTemp = CreateFile("c:\\temp\\req.txt", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
								FILE_ATTRIBUTE_ARCHIVE, NULL);
		
		WriteFile(hTemp, o_pNotzRequest->pbNzRequest, o_pNotzRequest->dwNzRequest, &dwBytesWritten, NULL);

		CloseHandle(hTemp);
#endif

	}while(0);


	FREE_MEMORY(pDescription)
	FREE_MEMORY(pbHash)

	return hr;
}



/*
I/P -	'i_bstrHashAlg'	:	The hash algorithm used for signing the request. This is a string
							which is mapped to an integer value understood by the PTA, as the
							PTA is used to perform the signature operation.
		'io_pNotzRequest'	:	Contains the notarization request to be signed in the 'pbNzRequest'
								member.
O/P -	'io_pNotzRequest'	:	Contains the signed notarization request in the 'pbSignedNzRequest'
								member.
Return -	An hresult indicating success of the operation.
Working -	Uses the PTA to sign the notarization request.
*/
HRESULT CNotarization::SignNotarizationRequest(const _bstr_t& i_bstrHashAlg, LPNzRequest io_pNotzRequest)
{
	HRESULT hr = S_OK;
	VARIANT varNzRequest, varAlgID, varNzRequestSig;
	_bstr_t bstrSignature = "";

	VariantInit(&varNzRequest);
	VariantInit(&varAlgID);
	VariantInit(&varNzRequestSig);

	do
	{
		if(!i_bstrHashAlg || !io_pNotzRequest)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		io_pNotzRequest->dwSignedNzRequest = 0;
		io_pNotzRequest->pbSignedNzRequest = NULL;

		if(io_pNotzRequest->dwNzRequest == 0 || !io_pNotzRequest->pbNzRequest)
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		varAlgID.vt = VT_I2;
		if(_strnicmp(i_bstrHashAlg, "MD5", 3) == 0)
			varAlgID.iVal = SCRIPT_HASH_MD5;	
		else
			if(_strnicmp(i_bstrHashAlg, "MD2", 3) == 0)
				varAlgID.iVal = SCRIPT_HASH_MD2;
			else
				if(_strnicmp(i_bstrHashAlg, "SHA1", 4) == 0)
					varAlgID.iVal = SCRIPT_HASH_SHA1;
				else
				{
					hr = E_NZINVALIDALG;
					break;
				}

		varNzRequest.vt = VT_ARRAY | VT_UI1;
		varNzRequest.parray = SafeArrayCreateVector(VT_UI1, 0, io_pNotzRequest->dwNzRequest);
		CHECK_MEM_BREAK(varNzRequest.parray)

		memcpy(varNzRequest.parray->pvData, io_pNotzRequest->pbNzRequest, io_pNotzRequest->dwNzRequest);

		hr = m_pVSPta->SignTransaction(&varNzRequest, &varAlgID, &varNzRequestSig);
		if(hr != S_OK)
		{
			_LogErrorMsg("CNotarization::SignNotarizationRequest().", "PTA SignTransaction() failed.", NULL, hr);
			hr = E_NZSIGNERR;
			break;
		}
		
		bstrSignature = varNzRequestSig.bstrVal;

		// Base64 decode the signed response
		_Base64Decode(bstrSignature, bstrSignature.length(), NULL, &io_pNotzRequest->dwSignedNzRequest);
		io_pNotzRequest->pbSignedNzRequest = (PBYTE)malloc(io_pNotzRequest->dwSignedNzRequest);
		CHECK_MEM_BREAK(io_pNotzRequest->pbSignedNzRequest)

		_Base64Decode(bstrSignature, bstrSignature.length(), (char*)io_pNotzRequest->pbSignedNzRequest, &io_pNotzRequest->dwSignedNzRequest);

	}while(0);

	VariantClear(&varNzRequest);
	VariantClear(&varAlgID);
	VariantClear(&varNzRequestSig);

	return hr;
}


/*
I/P -	'i_bstrServer'	:	Is the fully qualified path of the server, must be of the form
							http(s)://server:[port]/cgi.
		'i_pNotzRequest'	:	Contains the signed notarization request, the members 'dwSignedNzRequest'
								and 'pbSignedNzRequest' should be valid.
O/P -	'o_pNotzResponse'	:	Is the response from the notarization server. The response is
								ASN.1 encoded, it contains the status of the operation and a
								signed response.
Return -	An hresult indicating success of the operation.
Working -	This function does an http post of the signed notarization request to the server.
			Uses the wininet api for http functionality.
*/
HRESULT CNotarization::SendNotarizationRequest(const _bstr_t& i_bstrServer, const LPNzRequest i_pNotzRequest, LPNzResponse o_pNotzResponse)
{
	HRESULT hr = S_OK;
	_bstr_t bstrServerName = "", bstrServerObject = "";
	HINTERNET hOpen = NULL, hConnect = NULL, hRequest = NULL;
	DWORD dwLastError = 0, dwPortNum = 0, dwStatusCode = 0, dwStatusCodeSize = 0;
	DWORD dwNzRespDataSize = 0, dwNzRespBufOffset = 0;
	TCHAR szNzRespBuf[MAX_NZ_RESPONZE], szNzRespData[MAX_READ_SIZE];

	do
	{
		if(!i_bstrServer || !i_pNotzRequest || !o_pNotzResponse)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		o_pNotzResponse->dwNzResponse = 0;
		o_pNotzResponse->pbNzResponse = NULL;

		if(i_pNotzRequest->dwSignedNzRequest == 0 || !i_pNotzRequest->pbSignedNzRequest ||
		   i_bstrServer == _bstr_t(""))
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		// Get the server name, cgi name and the port to which we need to connect
		hr = _ParseServerPath(i_bstrServer, &bstrServerName, &bstrServerObject, &dwPortNum);
		CHECK_HRESULT_BREAK

		hOpen = InternetOpen("", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
		if(!hOpen)
		{
			dwLastError = GetLastError();
			_LogErrorMsg("CNotarization::SendNotarizationRequest().", "InternetOpen() failed.", NULL, dwLastError);
			hr = E_NZINETOPENERR;
			break;
		}

		hConnect = InternetConnect(hOpen, bstrServerName, (USHORT)dwPortNum, "", "", INTERNET_SERVICE_HTTP, 0, 0);
		if(!hConnect)
		{
			dwLastError = GetLastError();
			_LogErrorMsg("CNotarization::SendNotarizationRequest().", "InternetConnect() failed.", NULL, dwLastError);
			hr = E_NZINETCONNECTERR;
			break;
		}

		// Changed http/1.1 -> http/1.0 because it was not working on IE3.02
		hRequest = HttpOpenRequest(hConnect, "POST", bstrServerObject, TEXT("HTTP/1.0")/*TEXT("HTTP/1.1")*/, NULL, NULL,
								   INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE, NULL);
		if(!hRequest)
		{
			dwLastError = GetLastError();
			_LogErrorMsg("CNotarization::SendNotarizationRequest().", "HttpOpenRequest() failed.", NULL, dwLastError);
			hr = E_NZINETREQUESTERR;
			break;
		}

		if(!HttpSendRequest(hRequest, NZ_CONTENT_TYPE, lstrlen(NZ_CONTENT_TYPE), (LPVOID)i_pNotzRequest->pbSignedNzRequest, i_pNotzRequest->dwSignedNzRequest))
		{
			dwLastError = GetLastError();
			_LogErrorMsg("CNotarization::SendNotarizationRequest().", "HttpSendRequest() failed.", NULL, dwLastError);
			hr = E_NZINETSENDERR;
			break;
		}

		dwStatusCodeSize = sizeof(DWORD);
		if(!HttpQueryInfo(hRequest, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &dwStatusCode, &dwStatusCodeSize, NULL))
		{
			dwLastError = GetLastError();
			_LogErrorMsg("CNotarization::SendNotarizationRequest().", "HttpQueryInfo() failed.", NULL, dwLastError);
			hr = E_NZINETQUERYERR;
			break;
		}

		if(dwStatusCode != HTTP_STATUS_OK)
		{
			_LogErrorMsg("CNotarization::SendNotarizationRequest().", "Server error occured.", NULL, dwStatusCode);
			hr = E_NZINETBADSTAT;
			break;
		}

		do
		{
			if(!InternetReadFile(hRequest, (LPVOID)szNzRespData, MAX_READ_SIZE, &dwNzRespDataSize))
			{
				dwLastError = GetLastError();
				_LogErrorMsg("CNotarization::SendNotarizationRequest().", "InternetReadFile() failed.", NULL, dwLastError);
				hr = E_NZINETREADERR;
				break;
			}

			if(!dwNzRespDataSize)	// No more bytes to read
				break;	
			
			if((dwNzRespBufOffset +  dwNzRespDataSize) > MAX_NZ_RESPONZE)
			{
				_LogErrorMsg("CNotarization::SendNotarizationRequest().", "Buffer size less then available data.", NULL, dwLastError);
				hr = E_NZBUFOVERFLOW;
				break;
			}

			memcpy(szNzRespBuf + dwNzRespBufOffset, szNzRespData, dwNzRespDataSize);

			dwNzRespBufOffset += dwNzRespDataSize;

		}while(1);
		
		CHECK_HRESULT_BREAK

		o_pNotzResponse->pbNzResponse = (PBYTE)malloc(dwNzRespBufOffset);
		CHECK_MEM_BREAK(o_pNotzResponse->pbNzResponse)

		o_pNotzResponse->dwNzResponse = dwNzRespBufOffset;
		memcpy(o_pNotzResponse->pbNzResponse, szNzRespBuf, dwNzRespBufOffset);

	}while(0);

	CLOSE_INET_HANDLE(hRequest)
	CLOSE_INET_HANDLE(hConnect)
	CLOSE_INET_HANDLE(hOpen)
	
	return hr;
}



/*
I/P -	'i_bstrDocument'	:	The document against which the notarization response is to be 
								verified.
		'i_pNzResponse'	:	Is the notarization response. Contains the notarization server
							response and a signed response containing notarization details.
		'i_dwValidateFlag'	:	Are the flags which specify whether chain validation is to be 
								done and what kind of revocation checking is required. See the 
								'REV_' flags.
O/P -	'o_pNzDetails'	:	Is a structure which contains details like the version, serial,
							time etc. present in the notarization response.
Return -	An hresult indicating success of the operation.
Working -	Verifies the response returned by the notarization server. Does a chain validation and 
			CRL checking if specified, uses simder library functions to decode the ASN.1 response
			structure. Compares the hash of 'i_pDocument' with that present in the response.
			Fills in 'o_pNzDetails' with the information present in the response.
*/
HRESULT CNotarization::VerifyNotarizationResponse(const _bstr_t& i_bstrDocument, PBYTE i_pbHashVal, 
												  const LPNzResponse i_pNzResponse, const DWORD i_dwValidateFlag, 
												  const _bstr_t& i_bstrRevocationInfo, const _bstr_t& i_bstrUserAgent, 
												  LPNzDetails o_pNzDetails)
{
	HRESULT hr = S_OK;
	CBaseDERHierarchy *pNzResponseHy = NULL, *pNzInfoHy = NULL;
	BYTE *pbNzData = NULL, *pbNzInfo = NULL, *pbHashVal = NULL, *pbDocumentHashVal = NULL, *pbTSRequest = NULL;
	WCHAR* wcDefaultValue = NULL;
	DWORD dwNzInfo = 0, dwDocumentHashSize = 0, dwTSRequest = 0;
	LPTSTR pAlgObjID = NULL;

	do
	{
		if(!i_pNzResponse || !o_pNzDetails)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		// Either one should be present
		if(i_bstrDocument == _bstr_t("") && !i_pbHashVal)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		//o_pNzDetails->Initialize();

		if(i_pNzResponse->dwNzResponse == 0 || !i_pNzResponse->pbNzResponse)
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		/*	The response has the following structure
			NotarizationResp ::= SEQUENCE 
									{
										status PKIStatusInfo,
										timeStampToken TimStampToken	OPTIONAL
									} 

			The token is a signed data.	*/
		CBaseDERCollection NzResponseCn(i_pNzResponse->dwNzResponse, i_pNzResponse->pbNzResponse);
		pNzResponseHy = new CBaseDERHierarchy(NzResponseCn);
		CHECK_MEM_BREAK(pNzResponseHy)

		if(pNzResponseHy->dwErrorCode)
		{
			hr = E_NZRESPONSEDECODERR;
			break;
		}

		// Point to the top level sequence
		_DERTree *pRespDTree = &(pNzResponseHy->m_DERTree);
		CHECK_TREE_NODE(pRespDTree, SEQUENCE)

		// Serialize the response
		CSequence ResponseSeq, *pResponseSeq = NULL;
		pResponseSeq = (CSequence*)pRespDTree->currentBaseDER;
		ResponseSeq += *pResponseSeq;

		// Store the response in the 'o_pNzDetails' structure, this is used during creation of 
		// the html file to be posted to the notarization server
		o_pNzDetails->pbTimeStampToken = (PBYTE)malloc(ResponseSeq.cbData);
		CHECK_MEM_BREAK(o_pNzDetails->pbTimeStampToken)

		memcpy(o_pNzDetails->pbTimeStampToken, ResponseSeq.pbData, ResponseSeq.cbData);
		o_pNzDetails->dwTimeStampToken = ResponseSeq.cbData;

		// Point to the status sequence
		_DERTree *pStatSeqDTree = pRespDTree->rightDERTree;
		CHECK_TREE_NODE(pStatSeqDTree, SEQUENCE)

		// Point to the status
		/*	The status information has the following format
			PKIStatusInfo ::= SEQUENCE
								{
									status			PKIStatus
									statusString	PKIFreeText		OPTIONAL
									failInfo		PKIFailureInfo	OPTIONAL
								}
		*/
		_DERTree *pStatDTree = pStatSeqDTree->rightDERTree;
		CHECK_TREE_NODE(pStatDTree, UNIVERSAL_INTEGER)

		pbNzData = (PBYTE)malloc(pStatDTree->currentBaseDER->cbData);
		CHECK_MEM_BREAK(pbNzData)

		memcpy(pbNzData, pStatDTree->currentBaseDER->pbData, pStatDTree->currentBaseDER->cbData);
		o_pNzDetails->NzResponseStatus = (NZRespStatus)(*pbNzData);

		FREE_MEMORY(pbNzData)

		// If an error occurs then obtain the 'statusString' and 'failInfo' from the server 
		// response and display it on the UI. eg. 'statusString' could be 'the certificate has
		// expired'.
		if(o_pNzDetails->NzResponseStatus != GRANTED)
		{
			hr = E_NZFAILED;

			// Check if the server has returned an error string
			_DERTree *pStatInfoDTree = pStatDTree->nextDERTree;
			_DERTree *pStatFailInfoDTree = NULL;
			
			if(!pStatInfoDTree)
				break;

			if(!pStatInfoDTree->currentBaseDER)
				break;

			// Check if 'statusString' is available
			if(pStatInfoDTree->currentBaseDER->Type == SEQUENCE)
			{
				_DERTree *pStatStringDTree = pStatInfoDTree->rightDERTree;

				CHECK_TREE_NODE_NO_HRESULT(pStatStringDTree, UTF8_STRING)

				pbNzData = (PBYTE)malloc(pStatStringDTree->currentBaseDER->cbData + 1);
				CHECK_MEM_BREAK(pbNzData)

				memcpy(pbNzData, pStatStringDTree->currentBaseDER->pbData, pStatStringDTree->currentBaseDER->cbData);
				pbNzData[pStatStringDTree->currentBaseDER->cbData] = '\0';

				o_pNzDetails->bstrStatusMsg = (TCHAR*)pbNzData;

				FREE_MEMORY(pbNzData)

				pStatFailInfoDTree = pStatInfoDTree->nextDERTree;
			}
			else
				pStatFailInfoDTree = pStatInfoDTree;
			
			// Check if 'failInfo' is available
			CHECK_TREE_NODE_NO_HRESULT(pStatFailInfoDTree, BIT_STRING)

			pbNzData = (PBYTE)malloc(pStatFailInfoDTree->currentBaseDER->cbData);
			CHECK_MEM_BREAK(pbNzData)

			memcpy(pbNzData, pStatFailInfoDTree->currentBaseDER->pbData, pStatFailInfoDTree->currentBaseDER->cbData);
			
			o_pNzDetails->dwFailInfo = (*pbNzData);

			FREE_MEMORY(pbNzData)

			_LogErrorMsg("CNotarization::VerifyNotarizationResponse", o_pNzDetails->bstrStatusMsg, NULL, o_pNzDetails->dwFailInfo);

			break;
		}

		// Point to the signature
		_DERTree *pSignatureDTree = pStatSeqDTree->nextDERTree;
		CHECK_TREE_NODE(pSignatureDTree, SEQUENCE)

		// Serialize the signature
		CSequence SignatureSeq, *pSignatureSeq = NULL;
		pSignatureSeq = (CSequence*)pSignatureDTree->currentBaseDER;
		SignatureSeq += *pSignatureSeq;

		// Store the signature in the 'o_pNzDetails' structure, this is used during creation of 
		// the html file to be posted to the notarization server
		//o_pNzDetails->pbTimeStampToken = (PBYTE)malloc(SignatureSeq.cbData);
		//CHECK_MEM_BREAK(o_pNzDetails->pbTimeStampToken)

		//memcpy(o_pNzDetails->pbTimeStampToken, SignatureSeq.pbData, SignatureSeq.cbData);
		//o_pNzDetails->dwTimeStampToken = SignatureSeq.cbData;

		hr = _VerifyAttachedSignature(SignatureSeq.pbData, SignatureSeq.cbData, i_dwValidateFlag, i_bstrRevocationInfo, &pbNzInfo, &dwNzInfo, &o_pNzDetails->bstrNzAuthorityName);
		CHECK_HRESULT_BREAK

		/* Decode the notarization information. It is of the form
				NZInfo ::= SEQUENCE  {     
										version		INTEGER  { v1(1) },
										policy      TSAPolicyId,
										messageImprint		MessageImprint,
										-- MUST have the same value as the similar field in TimeStampReq     
										serialNumber		INTEGER,
										-- Time Stamps users MUST be ready to accommodate integers up to 160 bits.     
										genTime		GeneralizedTime,
										accuracy    Accuracy		OPTIONAL,
										ordering    BOOLEAN         DEFAULT FALSE,
										nonce       INTEGER         OPTIONAL,
										-- MUST be present if the similar field was present 
										-- in TimeStampReq. In that case it MUST have the same value.
										tsa         [0] GeneralName OPTIONAL,
										extensions  [1] IMPLICIT	Extensions   OPTIONAL
									  }
		*/
		CBaseDERCollection NzInfoCn(dwNzInfo, pbNzInfo);
		pNzInfoHy = new CBaseDERHierarchy(NzInfoCn);
		CHECK_MEM_BREAK(pNzInfoHy)

		if(pNzInfoHy->dwErrorCode)
		{
			hr = E_NZINFODECODERR;
			break;
		}

		// Point to the top level sequence
		_DERTree *pNzInfoDTree = &(pNzInfoHy->m_DERTree);
		CHECK_TREE_NODE(pNzInfoDTree, SEQUENCE)

		// Point to the version info
		_DERTree *pVerDTree = pNzInfoDTree->rightDERTree;
		CHECK_TREE_NODE(pVerDTree, UNIVERSAL_INTEGER)

		pbNzData = (PBYTE)malloc(pVerDTree->currentBaseDER->cbData);
		CHECK_MEM_BREAK(pbNzData)

		memcpy(pbNzData, pVerDTree->currentBaseDER->pbData, pVerDTree->currentBaseDER->cbData);
		o_pNzDetails->dwNzVersion = (DWORD)(*pbNzData);

		FREE_MEMORY(pbNzData)

		if(o_pNzDetails->dwNzVersion != NZ_VERSION)	// We support only version '1'
		{
			hr = E_NZINVALIDVER;
			break;
		}

		// Point to the policy info
		_DERTree *pPolyDTree = pVerDTree->nextDERTree;
		CHECK_TREE_NODE(pPolyDTree, SEQUENCE)

		// Point to the policy OID for Authentic Document
		_DERTree *pAuthDocDTree = pPolyDTree->rightDERTree;
		CHECK_TREE_NODE(pAuthDocDTree, OBJECT_IDENTIFIER)

		o_pNzDetails->pbAuthDocPolicy = (PBYTE)malloc(pAuthDocDTree->currentBaseDER->cbData);
		CHECK_MEM_BREAK(o_pNzDetails->pbAuthDocPolicy)

		o_pNzDetails->dwAuthDocPolicy = pAuthDocDTree->currentBaseDER->cbData;
		memcpy(o_pNzDetails->pbAuthDocPolicy, pAuthDocDTree->currentBaseDER->pbData, pAuthDocDTree->currentBaseDER->cbData);

		// Point to the message hash(imprint)
		_DERTree *pHashDTree = pPolyDTree->nextDERTree;
		CHECK_TREE_NODE(pHashDTree, SEQUENCE)


		// Point to the algorithm identifier within the message hash
		_DERTree *pAlgDTree = pHashDTree->rightDERTree;
		CHECK_TREE_NODE(pAlgDTree, SEQUENCE)


		// Point to the object id of the algorithm
		_DERTree *pAlgObjIDTree = pAlgDTree->rightDERTree;
		CHECK_TREE_NODE(pAlgObjIDTree, OBJECT_IDENTIFIER)

		pAlgObjID = (LPTSTR)malloc(pAlgObjIDTree->currentBaseDER->cbData + 1);
		CHECK_MEM_BREAK(pAlgObjID)

		memcpy(pAlgObjID, pAlgObjIDTree->currentBaseDER->pbData, pAlgObjIDTree->currentBaseDER->cbData);
		pAlgObjID[pAlgObjIDTree->currentBaseDER->cbData] = '\0';

		// Point to the message hash data
		_DERTree *pHashValDTree = pAlgDTree->nextDERTree;
		CHECK_TREE_NODE(pHashValDTree, OCTET_STRING)

		pbHashVal = (PBYTE)malloc(pHashValDTree->currentBaseDER->cbData);
		CHECK_MEM_BREAK(pbHashVal)

		memcpy(pbHashVal, pHashValDTree->currentBaseDER->pbData, pHashValDTree->currentBaseDER->cbData);

		if(!i_pbHashVal)
		{
#if 0	// new simder fix
			// Reverse the hash obtained from Simder,
			// this is because simder reverses the octet string. So our hash comparison will fail
			// if we dont do so.
			BYTE tmpHash;
			UINT nHashLen = pHashValDTree->currentBaseDER->cbData;
			for(UINT i = 0; i < nHashLen/2; i++)
			{
				tmpHash = pbHashVal[i];
				pbHashVal[i] = pbHashVal[nHashLen - i - 1];
				pbHashVal[nHashLen - i - 1] = tmpHash;
			}
#endif

			// Hash the file and compare the hash with the one above
			hr = _HashDocument(i_bstrDocument, pAlgObjID, i_bstrUserAgent, &pbDocumentHashVal, &dwDocumentHashSize);
			CHECK_HRESULT_BREAK
		}
		else		
		{
			if(lstrcmpi(pAlgObjID, szOID_RSA_MD2) == 0)
				dwDocumentHashSize = HASH_MD2_LENGTH;
			else
				if(lstrcmpi(pAlgObjID, szOID_RSA_MD4) == 0)
					dwDocumentHashSize = HASH_MD4_LENGTH;
				else
   					if(lstrcmpi(pAlgObjID, szOID_RSA_MD5) == 0)
						dwDocumentHashSize = HASH_MD5_LENGTH;
					else
						if(lstrcmpi(pAlgObjID, szOID_OIWSEC_sha1) == 0)
							dwDocumentHashSize = HASH_SHA1_LENGTH;
						else
						{
							hr = E_NZINVALIDALG;
							break;
						}			
		}
		
		if(dwDocumentHashSize == pHashValDTree->currentBaseDER->cbData)
		{
			if(i_pbHashVal)
			{
				if(memcmp(i_pbHashVal, pbHashVal, dwDocumentHashSize) != 0)
					o_pNzDetails->bDocumentModified = TRUE;
			}
			else
			{
				if(memcmp(pbDocumentHashVal, pbHashVal, dwDocumentHashSize) != 0)
					o_pNzDetails->bDocumentModified = TRUE;
			}
		}
		else
			o_pNzDetails->bDocumentModified = TRUE;
		
		// Point to the serial number now
		_DERTree *pSerNumDTree = pHashDTree->nextDERTree;
		CHECK_TREE_NODE(pSerNumDTree, UNIVERSAL_INTEGER)

		o_pNzDetails->pbSerialNum = (PBYTE)malloc(pSerNumDTree->currentBaseDER->cbData);
		CHECK_MEM_BREAK(o_pNzDetails->pbSerialNum)

		o_pNzDetails->dwSerialNum = pSerNumDTree->currentBaseDER->cbData;
		memcpy(o_pNzDetails->pbSerialNum, pSerNumDTree->currentBaseDER->pbData, o_pNzDetails->dwSerialNum);

		// Point to time when timestamp was generated
		_DERTree *pGenTimeDTree = pSerNumDTree->nextDERTree;

		CHECK_TREE_NODE(pGenTimeDTree, GENERALIZED_TIME)

		hr = _GetFormattedTime(pGenTimeDTree->currentBaseDER->pbData, pGenTimeDTree->currentBaseDER->cbData, &o_pNzDetails->NzFormattedSysTime);
		CHECK_HRESULT_BREAK

		// Point to the nonce, before the nonce occurs there are 2 optional values that
		// may occur, check for these
		_DERTree *pNonceDTree = pGenTimeDTree->nextDERTree;
		if(!pNonceDTree)
			break;

		if(!(pNonceDTree->currentBaseDER))
			break;
		
		if(pNonceDTree->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			pNonceDTree = pNonceDTree->nextDERTree;

			if(!pNonceDTree)
				break;

			if(!(pNonceDTree->currentBaseDER))
				break;

			if(pNonceDTree->currentBaseDER->Type != UNIVERSAL_INTEGER)
			{
				pNonceDTree = pNonceDTree->nextDERTree;

				if(!pNonceDTree)
					break;

				if(!(pNonceDTree->currentBaseDER))
					break;
		
			}
		}

		if(pNonceDTree->currentBaseDER->Type == UNIVERSAL_INTEGER)
		{
			o_pNzDetails->pbNonce = (PBYTE)malloc(pNonceDTree->currentBaseDER->cbData);
			CHECK_MEM_BREAK(o_pNzDetails->pbNonce)

			o_pNzDetails->dwNonce = pNonceDTree->currentBaseDER->cbData;
			memcpy(o_pNzDetails->pbNonce, pNonceDTree->currentBaseDER->pbData, o_pNzDetails->dwNonce);
		}

		// For the authentic document an extension has been added that contains the entire timestamp
		// request, get this value and use it to obtain the signer certificate information.
		_DERTree *pExtDTree = pNonceDTree->nextDERTree;
		if(!pExtDTree)
		{
			hr = E_NZINVALIDNODE;
			break;
		}

		if(!(pExtDTree->currentBaseDER))
		{
			hr = E_NZINVALIDNODE;
			break;
		}

		// Check if we have the 'tsa general name', it has an IMPLICIT tag, if present skip it
		if(pExtDTree->currentBaseDER->TagNumber == 0)
		{
			pExtDTree = pExtDTree->nextDERTree;

			if(!pExtDTree)
			{
				hr = E_NZINVALIDNODE;
				break;
			}

			if(!(pExtDTree->currentBaseDER))
			{
				hr = E_NZINVALIDNODE;
				break;
			}
		}

		// The extensions have an EXPLICIT tag
		if(pExtDTree->currentBaseDER->TagNumber != 1)
		{
			hr = E_NZINVALIDNODE;
			break;
		}

		/*
			Extensions        ::=   SEQUENCE SIZE (1..MAX) OF Extension

			Extension         ::=   SEQUENCE {
												extnId            EXTENSION.&id ({ExtensionSet}),
												critical          BOOLEAN DEFAULT FALSE,
												extnValue         OCTET STRING }
											-- contains a DER encoding of a value of type
		*/

		_DERTree *pOidSeqDTree = pExtDTree->rightDERTree;
		CHECK_TREE_NODE(pOidSeqDTree, SEQUENCE)

		_DERTree *pOidDTree = pOidSeqDTree->rightDERTree;
		CHECK_TREE_NODE(pOidDTree, OBJECT_IDENTIFIER)

		if(pOidDTree->currentBaseDER->cbData != (UINT)lstrlen(SIGNATURE_EXT_OID))
		{
			hr = E_NZINVALIDNODE;
			break;
		}
		
		if(memcmp(pOidDTree->currentBaseDER->pbData, SIGNATURE_EXT_OID, pOidDTree->currentBaseDER->cbData) != 0)
		{
			hr = E_NZINVALIDNODE;
			break;
		}

		_DERTree *pExtValueDTree = pOidDTree->nextDERTree;

		// Check if extension has the 'critical' encoding
		if(!pExtValueDTree)
		{
			hr = E_NZINVALIDNODE;
			break;
		}

		if(!(pExtValueDTree->currentBaseDER))
		{
			hr = E_NZINVALIDNODE;
			break;
		}

		if(pExtValueDTree->currentBaseDER->Type == BOOLEAN)
			pExtValueDTree = pExtValueDTree->nextDERTree;


		CHECK_TREE_NODE(pExtValueDTree, OCTET_STRING)

#if 0	// new simder fix
		// Reverse the hash obtained from Simder, this is because simder reverses the octet string
		BYTE tmpSig;
		UINT nSigLen = pExtValueDTree->currentBaseDER->cbData;
		PBYTE tmpSigVal = pExtValueDTree->currentBaseDER->pbData;
		for(UINT i = 0; i < nSigLen/2; i++)
		{
			tmpSig = tmpSigVal[i];
			tmpSigVal[i] = tmpSigVal[nSigLen - i - 1];
			tmpSigVal[nSigLen - i - 1] = tmpSig;
		}
#endif

		hr = _VerifyAttachedSignature(pExtValueDTree->currentBaseDER->pbData, pExtValueDTree->currentBaseDER->cbData, 0, "", &pbTSRequest, &dwTSRequest, &o_pNzDetails->bstrNzRequestor);
		if(hr != S_OK)
		{
			hr = E_NZINVALIDNODE;
			break;
		}

		// Get the 'description' from the request. The 'description' is encoded in the notarization
		// 'request'. Initially the 'description' was stored in the receipt, with the new receipt 
		// format that just stores the notarization response the 'description' need to be obtained
		// from the 'request' which is sent back from the notarization server in the response
		hr = OpenNotarizationRequest(pbTSRequest, dwTSRequest, &o_pNzDetails->bstrDescription);
		if(hr != S_OK)
		{
			hr = E_NZINVALIDNODE;
			break;
		}
		
	}while(0);

	FREE_MEMORY(pbTSRequest)
	FREE_MEMORY(pbDocumentHashVal)
	FREE_MEMORY(pbHashVal)
	FREE_MEMORY(pAlgObjID)
	FREE_MEMORY(pbNzData)
	FREE_MEMORY(pbNzInfo)

	// If simder is not able to decode the blobs then do no free them as there is a crash
	// in their destructor
	if(hr != E_NZINFODECODERR)
		DELETE_MEMORY(pNzInfoHy)

	if(hr != E_NZRESPONSEDECODERR)
		DELETE_MEMORY(pNzResponseHy)

	if(hr == E_NZINVALIDNODE)
		hr = E_NZPARSENZRESPONSE;

	return hr;
}


/*
I/P -	
O/P -	
Return -	An hresult indicating success of the operation.
Working -	A function to open a notarization request. Normally we only need to construct a request
			but we may also need to open it if we need some data encoded in the request. This 
			function was added when the receipt format was changed to store only the notarization
			response. Our notarization response also contain the notarization request(because of
			the special auth doc policy OID that we are encoding in the request).
			Currently the function only returns the description that was encoded in the request, it
			can be modified to return more data.
*/
HRESULT CNotarization::OpenNotarizationRequest(const PBYTE i_pbNzRequest, const DWORD i_dwNzRequest, _bstr_t* o_pbstrDescription)
{
	HRESULT hr = S_OK;
	CBaseDERHierarchy *pNzRequestHy = NULL, *pNzDescriptionHy = NULL;
	TCHAR *pszDescription = NULL;

	do
	{
		if(!i_pbNzRequest || !o_pbstrDescription)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(i_dwNzRequest == 0)
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		*o_pbstrDescription = "";

		/* ASN for a notarization request
		   NotarizationReq ::= SEQUENCE  {
										version	INTEGER		{ v1(1) },
										messageImprint		MessageImprint,
										--a hash algorithm OID and the hash value of the data to be
										--time stamped
										reqPolicy			PolicyInformation	OPTIONAL,
										nonce               INTEGER				OPTIONAL,
										certReq             BOOLEAN             DEFAULT FALSE,
										extensions          [0] IMPLICIT Extensions  OPTIONAL
									 }*/
		CBaseDERCollection NzRequestCn(i_dwNzRequest, (unsigned char *)i_pbNzRequest);
		pNzRequestHy = new CBaseDERHierarchy(NzRequestCn);
		CHECK_MEM_BREAK(pNzRequestHy)

		if(pNzRequestHy->dwErrorCode)
		{
			hr = E_NZREQUESTDECODERR;
			break;
		}

		// Point to the top level sequence
		_DERTree *pRequestDTree = &(pNzRequestHy->m_DERTree);
		CHECK_TREE_NODE(pRequestDTree, SEQUENCE)

		// Point to the version number
		_DERTree *pVersionDTree = pRequestDTree->rightDERTree;
		CHECK_TREE_NODE(pVersionDTree, UNIVERSAL_INTEGER)

		// Point to the messageImprint sequence
		_DERTree *pMsgImprintDTree = pVersionDTree->nextDERTree;
		CHECK_TREE_NODE(pMsgImprintDTree, SEQUENCE)

		// Point to the reqPolicy sequence
		_DERTree *pPolicyDTree = pMsgImprintDTree->nextDERTree;
		CHECK_TREE_NODE(pPolicyDTree, SEQUENCE)

		// Point to the nonce
		_DERTree *pNonceDTree = pPolicyDTree->nextDERTree;
		CHECK_TREE_NODE(pNonceDTree, UNIVERSAL_INTEGER)

		// Point to the certReq
		_DERTree *pCertReqDTree = pNonceDTree->nextDERTree;
		CHECK_TREE_NODE(pCertReqDTree, BOOLEAN)

		// Point to the extensions
		_DERTree *pExtDTree = pCertReqDTree->nextDERTree;
		
		// The extension is implicitly tagged, it contains the description
		if(pExtDTree->currentBaseDER->TagNumber != 0)
		{
			hr = E_NZINVALIDNODE;
			break;
		}

		// Point to the object identifier sequence identifying the type of extension
		_DERTree *pOidSeqDTree = pExtDTree->rightDERTree;
		CHECK_TREE_NODE(pOidSeqDTree, SEQUENCE)

		// Point to the object identifier now
		_DERTree *pOidDTree = pOidSeqDTree->rightDERTree;
		CHECK_TREE_NODE(pOidDTree, OBJECT_IDENTIFIER)

		if(pOidDTree->currentBaseDER->cbData != (UINT)lstrlen(DOC_EXT_OID))
		{
			hr = E_NZINVALIDNODE;
			break;
		}
		
		if(memcmp(pOidDTree->currentBaseDER->pbData, DOC_EXT_OID, pOidDTree->currentBaseDER->cbData) != 0)
		{
			hr = E_NZINVALIDNODE;
			break;
		}	

		// Point to the data of the extension, it is encoded as an octet string
		_DERTree *pExtDataTree = pOidDTree->nextDERTree;
		CHECK_TREE_NODE(pExtDataTree, OCTET_STRING)

		CBaseDERCollection NzDescriptionCn(pExtDataTree->currentBaseDER->cbData, (unsigned char *)pExtDataTree->currentBaseDER->pbData);
		pNzDescriptionHy = new CBaseDERHierarchy(NzDescriptionCn);
		CHECK_MEM_BREAK(pNzDescriptionHy)

		if(pNzDescriptionHy->dwErrorCode)
		{
			hr = E_NZINFODECODERR;
			break;
		}

		// Point to the decoded data, this is the description that was encoded while sending the
		// notarization request
		_DERTree *pDescriptionDTree = &(pNzDescriptionHy->m_DERTree);
		CHECK_TREE_NODE(pDescriptionDTree, OCTET_STRING)

		//_DERTree *pDescriptionDTree = pExtDataTree->nextDERTree;

		pszDescription = (TCHAR*)malloc(pDescriptionDTree->currentBaseDER->cbData + 1);
		CHECK_MEM_BREAK(pszDescription)

		memcpy(pszDescription, pDescriptionDTree->currentBaseDER->pbData, pDescriptionDTree->currentBaseDER->cbData);
		pszDescription[pDescriptionDTree->currentBaseDER->cbData] = NULL;

		*o_pbstrDescription = pszDescription;
			
	}while(0);

	FREE_MEMORY(pszDescription)

	// If simder is not able to decode the blobs then do no free them as there is a crash
	// in their destructor
	if(hr != E_NZRESPONSEDECODERR)
		DELETE_MEMORY(pNzRequestHy)

	if(hr != E_NZINFODECODERR)
		DELETE_MEMORY(pNzDescriptionHy)

	if(hr != S_OK)
		_LogErrorMsg("CNotarization::OpenNotarizationRequest().", "Error opening the notarization request.", NULL, hr);

	return hr;
}


VOID NzRequest::Initialize()
{
	pbNzRequest = NULL;
	dwNzRequest = NULL;

	pbNzNonce = NULL;
	dwNzNonce = NULL;

	pbSignedNzRequest = NULL;
	dwSignedNzRequest = NULL;
}


VOID NzRequest::Clear()
{
	if(pbNzRequest)
	{
		free(pbNzRequest);
		pbNzRequest = NULL;
	}

	dwNzRequest = 0;

	if(pbNzNonce)
	{
		free(pbNzNonce);
		pbNzNonce = NULL;
	}
	
	dwNzNonce = 0;

	if(pbSignedNzRequest)
	{
		free(pbSignedNzRequest);
		pbSignedNzRequest = NULL;
	}

	dwSignedNzRequest = 0;
}


VOID NzResponse::Initialize()
{
	pbNzResponse = NULL;
	dwNzResponse = 0;
}


VOID NzResponse::Clear()
{
	if(pbNzResponse)
	{
		free(pbNzResponse);
		pbNzResponse = NULL;
	}

	dwNzResponse = 0;
}


VOID NzDetails::Initialize()
{
	NzResponseStatus = REJECTION;

	bstrStatusMsg = "";

	dwFailInfo = -1;

	dwNzVersion = 0;

	pbSerialNum = NULL;
	dwSerialNum = 0;

	pbNonce = NULL;
	dwNonce = 0;

	bstrNzAuthorityName = "";
	bstrNzDocumentName = "";
	bstrDescription = "";
	bstrNzRequestor = "";

	tbstrUserAgent = "";

	pbRawRecordData = NULL;
	dwRawRecordDataLen = 0;

	bDocumentModified = FALSE;

	memset(&NzFormattedSysTime, 0, sizeof(NzFormattedSysTime));

	pbTimeStampToken = NULL;
	dwTimeStampToken = 0;

	pbAuthDocPolicy = NULL;
	dwAuthDocPolicy = 0;
}


VOID NzDetails::Clear()
{
	NzResponseStatus = REJECTION;

	bstrStatusMsg = "";

	dwFailInfo = -1;

	dwNzVersion = 0;

	if(pbSerialNum)
	{
		free(pbSerialNum);
		pbSerialNum = NULL;
	}

	dwSerialNum = 0;

	if(pbNonce)
	{
		free(pbNonce);
		pbNonce = NULL;
	}

	dwNonce = 0;

	bstrNzAuthorityName = "";
	bstrNzDocumentName = "";
	bstrDescription = "";
	bstrNzRequestor = "";

	tbstrUserAgent = "";

	if (pbRawRecordData)
	{
		free(pbRawRecordData);
		pbRawRecordData = NULL;
	}

	dwRawRecordDataLen = 0;

	bDocumentModified = FALSE;

	memset(&NzFormattedSysTime, 0, sizeof(NzFormattedSysTime));

	if(pbTimeStampToken)
	{
		free(pbTimeStampToken);
		pbTimeStampToken = NULL;
	}

	dwTimeStampToken = 0;

	if(pbAuthDocPolicy)
	{
		free(pbAuthDocPolicy);
		pbAuthDocPolicy = NULL;
	}

	dwAuthDocPolicy = 0;
}


/*
I/P - 
O/P - 
Return - 
Working -
*/
_bstr_t _HandleError(const HRESULT i_hResult, LPNzDetails i_pNotzDetails)
{
	UINT iErrStringId = 0;
	WCHAR *wcErrString = NULL;
	TCHAR *cErrString = NULL;
	_bstr_t bstrErrString = "";

	switch(i_hResult)
	{
		case E_VS_STORAGE_CORRUPT:
		{
			iErrStringId = IDS_PROFILE_CORRUPT;
			break;
		}

		case E_CERTNOMATCHCRIT :
		case E_PROFDOESNOTEXIST :
		case E_CERTNOTFOUND :
		{
			iErrStringId = IDS_CERT_INVALID;
			break;
		}

		case E_CERTMATCHBUTEXP :
		{
			iErrStringId = IDS_CERT_EXP;
			break;
		}

		case E_NZCDPABSENT :
		{
			iErrStringId = IDS_CDP_ABSENT;
			break;
		}

		case E_NZCDPFETCH :
		{
			iErrStringId = IDS_CDP_GET_ERR;
			break;
		}

		case E_NZDOCSHARE :
		{
			iErrStringId = IDS_DOC_SHARE_ERR;
			break;
		}

		case E_NZDOCEXISTS :
		{
			iErrStringId = IDS_DOC_EXISTS;
			break;
		}

		case E_NZDOCNOACCESS :
		{
			iErrStringId = IDS_DOC_NOACCESS;
			break;
		}

		case E_NZRCPTCREATERR :
		{
			iErrStringId = IDS_RCPTFILE_ERR;
			break;
		}

		case E_NZRECFORMATERR :
		{
			iErrStringId = IDS_INVALID_RECORD_FORMAT;
			break;
		}

		case E_NZRECORDFILESIZERR :
		{
			iErrStringId = IDS_INVALID_RECORD_SIZE;
			break;
		}

		case E_NZINVALIDNONCE :
		{
			iErrStringId = IDS_INVALID_NONCE;
			break;
		}

		case E_NZINVALIDVER :
		{
			iErrStringId = IDS_INVALID_VER;
			break;
		}

		case E_NZPARSENZRESPONSE :
		{
			iErrStringId = IDS_PARSE_RESP_ERR;
			break;
		}

		case E_NZINETREADERR :
		case E_NZBUFOVERFLOW :
		{
			iErrStringId = IDS_INET_READ_ERR;
			break;
		}

		case E_NZINETOPENERR :
		case E_NZINETCONNECTERR :
		case E_NZINETREQUESTERR :
		case E_NZINETSENDERR :
		{
			iErrStringId = IDS_INET_SEND_ERR;
			break;
		}

		case E_NZINETQUERYERR :
		{
			iErrStringId = IDS_INET_QUERY_ERR;
			break;
		}

		case E_NZINETBADSTAT :
		{
			iErrStringId = IDS_NZ_BAD_STAT;
			break;
		}

		case E_NZCAUTHNEEDED :
		{
			iErrStringId = IDS_CLIENT_AUTH_ERR;
			break;
		}

		case E_NZSECCERT :
		{
			iErrStringId = IDS_SEC_CERT_ERR;
			break;
		}

		case E_NZINVALIDPATH :
		{
			iErrStringId = IDS_INVALID_NZ_SERVER_PATH;
			break;
		}

		case E_NZSIGNERR :
		{
			iErrStringId = IDS_SIGN_ERR;
			break;
		}

		case E_NZHASHBEGINERR :
		case E_NZHASHDATAERR :
		case E_NZHASHENDERR :
		{
			iErrStringId = IDS_HASH_ERR;
			break;
		}

		case E_NZGENRANDOMERR :
		{
			iErrStringId = IDS_RANDOM_GEN_ERR;
			break;
		}

		case E_OUTOFMEMORY :
		{
			iErrStringId = IDS_MEM_ERR;
			break;
		}

		case E_NZINVALIDALG :
		{
			iErrStringId = IDS_INVALID_ALG;
			break;
		}

		case E_NZFAILED :
		{
			iErrStringId = IDS_NZSERVER_ERR;
			break;
		}

		case E_NZNOISSUER :
		case E_NZNOTRUSTED :
		{
			iErrStringId = IDS_NOT_TRUSTED;
			break;
		}

		case E_NZISSUEREVOKED :
		case E_NZCERTREVOKED :
		{
			iErrStringId = IDS_CERT_REVOKED;
			break;
		}


		case E_NZSELFSIGNED :
		{
			iErrStringId = IDS_SELF_SIGNED;
			break;
		}
		
		case E_NZREVTYPENOTSUPPORTED :
		case E_NZADDCRLERR :
		case E_NZCRYPTDECODERR :
		case E_NZCRYPTCONTEXT :
		case E_NZSIGVERIFYERR :
		{
			iErrStringId = IDS_SIG_VERIFY_ERR;
			break;
		}

		case E_NZINVALIDPOLICY :
		{
			iErrStringId = IDS_INVALID_POLICY;
			break;
		}

		case S_OK :
		{
			iErrStringId = IDS_NZ_COMPLETE;
			break;
		}

		default :
		{
			return bstrErrString;
		}

	}	// switch(i_hResult)

	if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), iErrStringId, &wcErrString) != S_OK)
	{
		_LogErrorMsg("CVSNZ::_HandleError().", "Error loading string.", NULL, 0);
		wcErrString = NULL;
	}

	bstrErrString = (wcErrString == NULL) ? _bstr_t("") : wcErrString;

	// Give detailed error to user if possible
	if(i_pNotzDetails)
	{
		switch(i_hResult)
		{
			case E_NZFAILED :
			{
				// Map the failure info to a user friendly error message if possible
				bstrErrString = _MapFailInfo(i_pNotzDetails);
				break;
			}

			case E_NZDOCSHARE :
			case E_NZDOCEXISTS :
			case E_NZDOCNOACCESS :
			{
				if(i_pNotzDetails->bstrNzDocumentName != _bstr_t("") && bstrErrString != _bstr_t(""))
				{
					cErrString = (TCHAR*)malloc(lstrlen((LPCTSTR)i_pNotzDetails->bstrNzDocumentName) + lstrlen((LPCTSTR)bstrErrString) + 1);
					if(!cErrString)
						break;

					wsprintf(cErrString, (LPCTSTR)bstrErrString, (LPCTSTR)i_pNotzDetails->bstrNzDocumentName);

					bstrErrString = cErrString;

					FREE_MEMORY(cErrString)
				}

				break;
			}
			
		}	// switch(i_hResult)
	}
	
	FREE_MEMORY(wcErrString)
	FREE_MEMORY(cErrString)

	return bstrErrString;
}


#if 0
		DWORD dwBytesWritten;
		HANDLE hTemp = CreateFile("c:\\temp\\resp1.txt", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
								FILE_ATTRIBUTE_ARCHIVE, NULL);
		
		WriteFile(hTemp, i_pNzResponse->pbNzResponse, i_pNzResponse->dwNzResponse, &dwBytesWritten, NULL);

		CloseHandle(hTemp);
#endif
