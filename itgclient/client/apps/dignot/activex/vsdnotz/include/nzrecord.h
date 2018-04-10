#ifndef __NZRECORD_
#define __NZRECORD_

class CNotarizationRecord
{
public:
	CNotarizationRecord();
	~CNotarizationRecord();

public:
	HRESULT OpenNotarizationRecord(const _bstr_t& i_bstrRecord, const BOOL i_bUrl, const _bstr_t& i_bstrUAgent, LPNzDetails o_NzDetailedInfo);

	HRESULT CreateNotarizationRecord(const _bstr_t& i_bstrDocument, const _bstr_t& i_bstrDescription, const _bstr_t& i_bstrRequestor,
									 const NzResponse& i_NotzResponse, LPBYTE* o_pbNzRecord, LPDWORD o_pdwNzRecordSize);

	HRESULT GetNotarizationRequestor(_bstr_t* o_pbstrRequestor);
	HRESULT GetNotarizedDocument(_bstr_t* o_pbstrDocument);
	HRESULT GetNotarizedDescription(_bstr_t* o_pbstrDescription);
	HRESULT GetNotarizationResponse(LPNzResponse o_pNzResponse);
	HRESULT GetRecordType(ResponseType* o_pRespType);

private:
	_bstr_t m_bstrDocument;
	_bstr_t m_bstrRcptDescription;
	_bstr_t m_bstrRequestor;
	ResponseType m_RespType;

	NzResponse m_NotzResponse;
};


// This is the old format in which we used to store the receipt files, also in the old format
// all octet strings are reversed because of the way simder used to behave
/* Open the record, the record is an ASN.1 structure having format
VSRecord ::= SEQUENCE
				{
					VS_Document		OCTET STRING,	// A URL. It contains the data that 
													// is notarized.
					VS_Signature	OCTET STRING,	// Signed response returned by the 									// notarization server.
					VS_Description	OCTET STRING,	// Description about VS_Document.
					VS_Requestor	OCTET STRING	// Requestor is the person who
													// makes the notarization request.
				} */


// The new format of the receipt contains only the 'VS_Signature' portion. Simder behave correctly
// ie does not reverse the octet strings since version 1.0.0.3 of this control onwards

#endif // __NZRECORD_