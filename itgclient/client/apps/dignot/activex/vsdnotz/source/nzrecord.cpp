#include "stdafx.h"
#include <comutil.h>
#include "ptav3.h"
#include "notarize.h"
#include "nzutils.h"
#include "nzrecord.h"
#include "nzerrs.h"
#include "nzmacros.h"
#include "nzdatacc.h"
#include "nzdefines.h"
#include "basedercollection.h"
#include "basederhierarchy.h"
#include "sequence.h"
#include "octetstring.h"

// Constructor
CNotarizationRecord::CNotarizationRecord()
{
	m_bstrDocument = "";
	m_bstrRcptDescription = "";
	m_bstrRequestor = "";
	
	m_NotzResponse.Initialize();
}


// Destructor
CNotarizationRecord::~CNotarizationRecord()
{
	m_bstrDocument = "";
	m_bstrRcptDescription = "";
	m_bstrRequestor = "";
	
	m_NotzResponse.Clear();
}


HRESULT CNotarizationRecord::OpenNotarizationRecord(const _bstr_t& i_bstrRecord, const BOOL i_bUrl, const _bstr_t& i_bstrUAgent, LPNzDetails o_NzDetailedInfo)
{
	HRESULT hr = S_OK;
	CDataAccess DAccObject, DAWriteObject;
	PBYTE pbRawRecordData = NULL, pbRecord = NULL;
	BYTE pbReadBuffer[MAX_READ_SIZE];
	DWORD dwRecordLen = 0, dwRawRecordDataLen = 0, dwReadBuffer = 0, dwBytesRead = 0;
	CBaseDERHierarchy *pNzRecordHy = NULL;
	_bstr_t bstrTempFile = "";

	m_bstrDocument = "";
	m_bstrRcptDescription = "";
	m_bstrRequestor = "";

	m_NotzResponse.Clear();

	do
	{
		if(!i_bstrRecord)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(i_bstrRecord == _bstr_t(""))
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		if(i_bUrl)
		{
			// Create a temporary file in which the record will be written
			hr = _CreateTempFile(&bstrTempFile);
			CHECK_HRESULT_BREAK

			hr = DAWriteObject.Open(bstrTempFile, ACCESS_OVERWRITE);
			CHECK_HRESULT_BREAK

			// Get the record
			hr = DAccObject.Open(i_bstrRecord, ACCESS_READ, i_bstrUAgent);
			CHECK_HRESULT_BREAK

			do
			{
				dwReadBuffer = sizeof(pbReadBuffer);
				hr = DAccObject.Read(pbReadBuffer, &dwReadBuffer);
				CHECK_HRESULT_BREAK

				if(dwReadBuffer == 0)
					break;

				hr = DAWriteObject.Write(pbReadBuffer, dwReadBuffer);
				CHECK_HRESULT_BREAK

				dwBytesRead += dwReadBuffer;

			}while(dwReadBuffer != 0);

			CHECK_HRESULT_BREAK

			DAccObject.Close();
			DAWriteObject.Close();

			// Now read the record in memory
			dwRawRecordDataLen = dwBytesRead;
			pbRawRecordData = (PBYTE)malloc(dwRawRecordDataLen);
			CHECK_MEM_BREAK(pbRawRecordData)

			hr = DAccObject.Open(bstrTempFile);
			CHECK_HRESULT_BREAK

			dwBytesRead = 0;

			do
			{
				dwReadBuffer = sizeof(pbReadBuffer);
				hr = DAccObject.Read(pbReadBuffer, &dwReadBuffer);
				CHECK_HRESULT_BREAK

				memcpy(pbRawRecordData + dwBytesRead, pbReadBuffer, dwReadBuffer);
				dwBytesRead += dwReadBuffer;

			}while(dwReadBuffer != 0);

			DAccObject.Close();

			CHECK_HRESULT_BREAK
		}
		else
		{
			dwRawRecordDataLen = lstrlen((TCHAR*)i_bstrRecord);
			pbRawRecordData = (PBYTE)malloc(dwRawRecordDataLen);
			CHECK_MEM_BREAK(pbRawRecordData)

			memcpy(pbRawRecordData, (PBYTE)(TCHAR*)i_bstrRecord, dwRawRecordDataLen);
		}

		// The record and its length is saved for Save Document and Receipt purposes.
		o_NzDetailedInfo->pbRawRecordData = (PBYTE) malloc (dwRawRecordDataLen * sizeof (PBYTE));
		memcpy(o_NzDetailedInfo->pbRawRecordData, pbRawRecordData, dwRawRecordDataLen);
		o_NzDetailedInfo->dwRawRecordDataLen = dwRawRecordDataLen;

		// Check if the receipt is base64 encoded
		if(IsBase64Encoded((PBYTE)pbRawRecordData, dwRawRecordDataLen))
		{
			// Base64 decode the data
			_Base64Decode((char *)pbRawRecordData, dwRawRecordDataLen, NULL, &dwRecordLen);
			pbRecord = (PBYTE)malloc(dwRecordLen);
			CHECK_MEM_BREAK(pbRecord)

			_Base64Decode((char *)pbRawRecordData, dwRawRecordDataLen, (char *)pbRecord, &dwRecordLen);
		}
		else
		{
			dwRecordLen = dwRawRecordDataLen;
			pbRecord = (PBYTE)malloc(dwRecordLen);
			CHECK_MEM_BREAK(pbRecord)

			memcpy(pbRecord, pbRawRecordData, dwRecordLen);
		}

		// The data can either be in the old format which includes extra information or it can be
		// in the new format which just contains the notarization server response
		CBaseDERCollection NzRecordCn(dwRecordLen, pbRecord);
		pNzRecordHy = new CBaseDERHierarchy(NzRecordCn);
		CHECK_MEM_BREAK(pNzRecordHy)

		if(pNzRecordHy->dwErrorCode)
		{
			hr = E_NZRECORDDECODERR;
			break;
		}

		_DERTree *pRecordDTree = &(pNzRecordHy->m_DERTree);
		CHECK_TREE_NODE(pRecordDTree, SEQUENCE)

		// For old format of record the right DER tree will be an octet string, for new format
		// it is a sequence
		if(pRecordDTree->rightDERTree == NULL)
		{
			hr = E_NZINVALIDNODE;
			break;
		}

		if(pRecordDTree->rightDERTree->currentBaseDER == NULL)
		{
			hr = E_NZINVALIDNODE;
			break;
		}

		if(pRecordDTree->rightDERTree->currentBaseDER->Type == OCTET_STRING)
		{
			// Reverse all the octet strings since receipt stored in old format were created
			// using the old version of simder

			m_RespType = RT_NZRECORD;

			// Point to the 'Document' string
			_DERTree *pDocDTree = pRecordDTree->rightDERTree;
			CHECK_TREE_NODE(pDocDTree, OCTET_STRING)

			reverseit(pDocDTree->currentBaseDER->pbData, pDocDTree->currentBaseDER->cbData);

			m_bstrDocument = (WCHAR*)pDocDTree->currentBaseDER->pbData;

			// Point to the signature
			_DERTree *pSigDTree = pDocDTree->nextDERTree;
			CHECK_TREE_NODE(pSigDTree, OCTET_STRING)

			m_NotzResponse.pbNzResponse = (PBYTE)malloc(pSigDTree->currentBaseDER->cbData);
			CHECK_MEM_BREAK(m_NotzResponse.pbNzResponse)

			m_NotzResponse.dwNzResponse = pSigDTree->currentBaseDER->cbData;

			reverseit(pSigDTree->currentBaseDER->pbData, pSigDTree->currentBaseDER->cbData);

			memcpy(m_NotzResponse.pbNzResponse, pSigDTree->currentBaseDER->pbData, m_NotzResponse.dwNzResponse);

			// Point to the description
			_DERTree *pDescDTree = pSigDTree->nextDERTree;
			CHECK_TREE_NODE(pDescDTree, OCTET_STRING)

			reverseit(pDescDTree->currentBaseDER->pbData, pDescDTree->currentBaseDER->cbData);

			m_bstrRcptDescription = (WCHAR*)pDescDTree->currentBaseDER->pbData;

			// Point to the requestor
			_DERTree *pReqDTree = pDescDTree->nextDERTree;
			CHECK_TREE_NODE(pReqDTree, OCTET_STRING)

			reverseit(pReqDTree->currentBaseDER->pbData, pReqDTree->currentBaseDER->cbData);

			m_bstrRequestor = (WCHAR*)pReqDTree->currentBaseDER->pbData;
		}
		else
		{
			m_RespType = RT_NZRESPONSE;

			m_bstrDocument = "";

			m_NotzResponse.pbNzResponse = (PBYTE)malloc(dwRecordLen);
			CHECK_MEM_BREAK(m_NotzResponse.pbNzResponse)

			m_NotzResponse.dwNzResponse = dwRecordLen;
			memcpy(m_NotzResponse.pbNzResponse, pbRecord, dwRecordLen);

			m_bstrRcptDescription = "";
			m_bstrRequestor = "";
		}

	}while(0);

	DAccObject.Close();
	DAWriteObject.Close();

	FREE_MEMORY(pbRecord)
	FREE_MEMORY(pbRawRecordData)

	// Delete the temporary record file
	if(bstrTempFile != _bstr_t(""))
		DeleteFile(bstrTempFile);

	// If not able to decode the blob then do not call delete as simder crashes in the 
	// destructor
	if(hr != E_NZRECORDDECODERR)
		DELETE_MEMORY(pNzRecordHy)

	if(hr == E_NZINVALIDNODE)
		hr = E_NZRECFORMATERR;

	return hr;
}



/*
I/P -	
O/P -
Return -	
Working -	
*/
HRESULT CNotarizationRecord::CreateNotarizationRecord(const _bstr_t& i_bstrDocument, const _bstr_t& i_bstrDescription, const _bstr_t& i_bstrRequestor,
													  const NzResponse& NotzResponse, LPBYTE* o_pbNzRecord, LPDWORD o_pdwNzRecordSize)
{
	HRESULT hr = S_OK;

	do
	{
		if(!i_bstrDocument || !i_bstrRequestor || !o_pbNzRecord || !o_pdwNzRecordSize)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(NotzResponse.dwNzResponse == 0 || !NotzResponse.pbNzResponse || i_bstrDocument == _bstr_t("") || i_bstrRequestor == _bstr_t(""))
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		*o_pbNzRecord = NULL;
		*o_pdwNzRecordSize = 0;

		/* Construct the record, the record is an ASN.1 structure having format
		VSRecord ::= SEQUENCE
						{
							VS_Document		OCTET STRING,	// A URL. It contains the path to  
															// the data that is notarized.
							VS_Signature	OCTET STRING,	// Signed response returned by the 									// notarization server.
							VS_Description	OCTET STRING,	// Description about VS_Document.
							VS_Requestor	OCTET STRING	// Requestor is the person who
															// makes the notarization request.
						} */
		CSequence NzRecord;
		COctetString Document(((wcslen(i_bstrDocument) + 1)*sizeof(WCHAR)), (PBYTE)(WCHAR*)i_bstrDocument);
		COctetString Signature(NotzResponse.dwNzResponse, NotzResponse.pbNzResponse);
		COctetString Description(((wcslen(i_bstrDescription) + 1)*sizeof(WCHAR)), (PBYTE)(WCHAR*)i_bstrDescription);
		COctetString Requestor(((wcslen(i_bstrRequestor) + 1)*sizeof(WCHAR)), (PBYTE)(WCHAR*)i_bstrRequestor);

		NzRecord = Document;
		NzRecord += Signature;
		NzRecord += Description;
		NzRecord += Requestor;

		*o_pbNzRecord = (PBYTE)malloc((NzRecord.BaseDERBlob)->cbData);
		CHECK_MEM_BREAK(*o_pbNzRecord)

		*o_pdwNzRecordSize = (NzRecord.BaseDERBlob)->cbData;
		memcpy(*o_pbNzRecord, (NzRecord.BaseDERBlob)->pbData, *o_pdwNzRecordSize);

	}while(0);

	return hr;
}

/*
I/P -	
O/P -
Return -	
Working -	
*/
HRESULT CNotarizationRecord::GetNotarizationRequestor(_bstr_t* o_pbstrRequestor)
{
	if(!o_pbstrRequestor)
		return E_NZEMPTYARGS;

	if(m_bstrRequestor == _bstr_t(""))
		return E_NZRECORDNOTOPENED;

	*o_pbstrRequestor = m_bstrRequestor.copy();

	return S_OK;
}


/*
I/P -	
O/P -
Return -	
Working -	
*/
HRESULT CNotarizationRecord::GetNotarizedDocument(_bstr_t* o_pbstrDocument)
{
	if(!o_pbstrDocument)
		return E_NZEMPTYARGS;

	if(m_bstrDocument == _bstr_t(""))
		return E_NZRECORDNOTOPENED;

	*o_pbstrDocument = m_bstrDocument.copy();

	return S_OK;
}



/*
I/P -	
O/P -
Return -	
Working -	
*/
HRESULT CNotarizationRecord::GetNotarizedDescription(_bstr_t* o_pbstrDescription)
{
	if(!o_pbstrDescription)
		return E_NZEMPTYARGS;

	//if(m_bstrRcptDescription == _bstr_t(""))
	//	return E_NZRECORDNOTOPENED;

	*o_pbstrDescription = m_bstrRcptDescription.copy();

	return S_OK;
}


/*
I/P -	
O/P -
Return -	
Working -	
*/
HRESULT CNotarizationRecord::GetNotarizationResponse(LPNzResponse o_pNzResponse)
{
	if(!o_pNzResponse)
		return E_NZEMPTYARGS;

	if(m_NotzResponse.dwNzResponse == 0 || !m_NotzResponse.pbNzResponse)
		return E_NZRECORDNOTOPENED;

	o_pNzResponse->pbNzResponse = (PBYTE)malloc(m_NotzResponse.dwNzResponse);
	if(!(o_pNzResponse->pbNzResponse))
		return E_OUTOFMEMORY;

	o_pNzResponse->dwNzResponse = m_NotzResponse.dwNzResponse;
	memcpy(o_pNzResponse->pbNzResponse, m_NotzResponse.pbNzResponse, o_pNzResponse->dwNzResponse);

	return S_OK;
}


HRESULT CNotarizationRecord::GetRecordType(ResponseType* o_pRespType)
{
	if(!o_pRespType)
		return E_NZEMPTYARGS;

	*o_pRespType = m_RespType;

	return S_OK;
}